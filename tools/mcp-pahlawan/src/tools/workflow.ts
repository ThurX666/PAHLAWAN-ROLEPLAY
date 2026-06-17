import { execFile } from "node:child_process";
import fs from "node:fs";
import path from "node:path";
import { promisify } from "node:util";
import { z } from "zod";
import type { ToolDefinition } from "../types.js";
import { searchCode, type SearchHit } from "../utils/fileSearch.js";
import { listLogCandidates } from "../utils/logReader.js";
import { boundedLimit, pageItems, resolveOffset } from "../utils/pagination.js";
import { relativePath } from "../utils/pathSafety.js";

const execFileAsync = promisify(execFile);

async function git(args: string[], cwd: string): Promise<string> {
  const { stdout } = await execFileAsync("git", args, { cwd, windowsHide: true, maxBuffer: 1024 * 1024 });
  return stdout;
}

const contextStopWords = new Set(["and", "the", "for", "with", "from", "into", "this", "that", "only", "do", "not", "dan", "yang", "untuk"]);

function taskTerms(task: string): string[] {
  return Array.from(new Set(
    task
      .split(/[^\p{L}\p{N}_/-]+/u)
      .map((term) => term.trim())
      .filter((term) => term.length > 2 && !contextStopWords.has(term.toLowerCase())),
  )).slice(0, 6);
}

function uniqueHits(hits: SearchHit[]): SearchHit[] {
  const seen = new Set<string>();
  return hits.filter((hit) => {
    const key = `${hit.file}:${hit.line}`;
    if (seen.has(key)) return false;
    seen.add(key);
    return true;
  });
}

function classifyHit(hit: SearchHit): string {
  if (/^(CMD|YCMD|COMMAND):/i.test(hit.text) || /SlashCommandBuilder|\.setName\s*\(/i.test(hit.text)) return "command";
  if (/\.(get|post|put|patch|delete)\s*\(|\/api\//i.test(hit.text) || hit.file.includes("/api/")) return "route";
  if (/^\s*(public|stock|forward|export|function|class)/i.test(hit.text)) return "symbol";
  if (/\b(select|from|join|insert|update)\b/i.test(hit.text) || hit.file.endsWith(".sql")) return "database";
  return "file";
}

export const workflowTools: ToolDefinition[] = [
  {
    name: "generate_task_context",
    description: "Generate a compact AI context pack for a task: related files, functions, DB hints, routes/commands, risks, and patch plan.",
    schema: z.object({
      task: z.string().min(2),
      module: z.enum(["gamemode", "website", "bot", "database", "all"]).default("all"),
      limit: z.number().int().min(1).max(50).optional(),
      maxResults: z.number().int().min(1).max(50).optional(),
      cursor: z.number().int().min(0).default(0),
      offset: z.number().int().min(0).optional(),
      includeSnippets: z.boolean().optional(),
    }),
    inputSchema: {
      type: "object",
      required: ["task"],
      properties: {
        task: { type: "string" },
        module: { type: "string", enum: ["gamemode", "website", "bot", "database", "all"], default: "all" },
        limit: { type: "number", default: 10 },
        maxResults: { type: "number", description: "Deprecated alias for limit." },
        cursor: { type: "number", default: 0 },
        offset: { type: "number" },
        includeSnippets: { type: "boolean", default: false },
      },
      additionalProperties: false,
    },
    async handler(input, { config }) {
      const terms = taskTerms(input.task);
      const limit = boundedLimit(input.limit ?? input.maxResults, config.limits.maxSearchResults, config.limits.maxSearchResults);
      const offset = resolveOffset(input.cursor, input.offset);
      const hits: SearchHit[] = [];
      for (const term of terms) {
        hits.push(...await searchCode(config, term, {
          module: input.module,
          extensions: [".pwn", ".inc", ".php", ".js", ".ts", ".tsx", ".sql", ".json", ".txt"],
          limit: Math.min(limit + 1, config.limits.maxFeatureFiles),
          contextLines: 0,
        }));
      }
      const related = uniqueHits(hits).slice(0, config.limits.maxFeatureFiles);
      const selected = related.slice(offset, offset + limit + 1);
      const visible = selected.slice(0, limit).map((hit) => input.includeSnippets ?? config.defaults.includeSnippets
        ? hit
        : ({ file: hit.file, line: hit.line, text: hit.text }));
      const byKind = (kind: string) => visible.filter((hit) => classifyHit(hit as SearchHit) === kind);
      const dbTables = Array.from(new Set(
        visible.flatMap((hit) => hit.text.match(/\b(?:from|join|into|update)\s+[`"]?([A-Za-z0-9_]+)/ig)?.map((match) => match.split(/\s+/).pop()?.replace(/[`"]/g, "")) ?? [])
          .filter((value): value is string => Boolean(value)),
      )).slice(0, config.limits.maxSchemaTables);
      return {
        taskSummary: input.task,
        module: input.module,
        relevantModules: Array.from(new Set(visible.map((hit) => hit.file.split("/")[0]))),
        relatedFiles: Array.from(new Set(visible.map((hit) => hit.file))).slice(0, config.limits.maxFeatureFiles),
        relatedFunctionsAndSymbols: byKind("symbol"),
        relatedDatabaseTables: dbTables,
        relatedRoutesAndCommands: [...byKind("route"), ...byKind("command")],
        supportingHits: visible,
        knownRisks: [
          "Do not edit generated/runtime files.",
          "Keep secrets and config files out of Git.",
          "For Pawn, check callbacks and includes before adding code.",
          "For UCP, validate input server-side and preserve auth flow.",
          "For bot, respect Discord interaction response timing.",
          "For DB, plan migration and rollback before applying SQL.",
        ],
        recommendedNextSteps: [
          "Inspect outlines for the highest-ranked files.",
          "Read only the relevant symbol or bounded line range.",
          "Verify schema/log evidence only if the feature depends on them.",
        ],
        suggestedFocusedToolCalls: visible.slice(0, 5).map((hit) => ({
          tool: "read_project_file",
          arguments: { filePath: hit.file, startLine: hit.line, maxLines: 40, includeContent: false },
        })),
        pagination: {
          offset,
          limit,
          returned: visible.length,
          truncated: selected.length > limit,
          nextCursor: selected.length > limit ? offset + visible.length : null,
        },
      };
    },
  },
  {
    name: "generate_changelog",
    description: "Analyze recent git changes or provided changed files and generate an Indonesian changelog suitable for Discord.",
    schema: z.object({
      changedFiles: z.array(z.string()).optional(),
      since: z.string().default("HEAD"),
    }),
    inputSchema: {
      type: "object",
      properties: {
        changedFiles: { type: "array", items: { type: "string" } },
        since: { type: "string", default: "HEAD" },
      },
      additionalProperties: false,
    },
    async handler(input, { config }) {
      let changedFiles: string[] | undefined = input.changedFiles;
      if (!changedFiles || changedFiles.length === 0) {
        const output = await git(["diff", "--name-only", input.since], config.projectRoot).catch(() => "");
        changedFiles = output.split(/\r?\n/).filter(Boolean);
      }
      const grouped = {
        gamemode: changedFiles.filter((file: string) => file.startsWith("GAMEMODE/")),
        website: changedFiles.filter((file: string) => file.startsWith("WEBSITE/")),
        bot: changedFiles.filter((file: string) => file.startsWith("BOT/")),
        database: changedFiles.filter((file: string) => file.startsWith("DATABASE/")),
        docs: changedFiles.filter((file: string) => file.startsWith("docs/") || file === "README.md"),
        tools: changedFiles.filter((file: string) => file.startsWith("tools/")),
      };
      return {
        changedFiles: changedFiles.slice(0, config.limits.maxFeatureFiles),
        discordChangelog: [
          "**Update PAHLAWAN ROLEPLAY**",
          grouped.gamemode.length ? `- Gamemode: ${grouped.gamemode.length} file diperbarui.` : null,
          grouped.website.length ? `- Website/UCP: ${grouped.website.length} file diperbarui.` : null,
          grouped.bot.length ? `- Bot Discord: ${grouped.bot.length} file diperbarui.` : null,
          grouped.database.length ? `- Database: ${grouped.database.length} file terkait database diperbarui.` : null,
          grouped.docs.length ? `- Dokumentasi: ${grouped.docs.length} file diperbarui.` : null,
          grouped.tools.length ? `- Tools: ${grouped.tools.length} file developer tooling diperbarui.` : null,
        ].filter(Boolean).join("\n"),
        grouped,
      };
    },
  },
  {
    name: "health_check",
    description: "Run non-destructive checks for folders, important files, optional DB/compiler config, dependencies, and MCP safety flags.",
    schema: z.object({}),
    inputSchema: { type: "object", properties: {}, additionalProperties: false },
    async handler(_input, { config }) {
      const importantFiles = [
        config.dirs.gamemode,
        path.join(config.dirs.gamemode, "gamemodes", "main.pwn"),
        config.dirs.website,
        path.join(config.dirs.website, "package.json"),
        config.dirs.bot,
        path.join(config.dirs.bot, "package.json"),
        config.dirs.database,
      ];
      return {
        projectRoot: config.projectRoot,
        checks: importantFiles.map((target) => ({
          target: relativePath(config, target),
          exists: fs.existsSync(target),
        })),
        mysqlConfigured: Boolean(config.mysql.host && config.mysql.user && config.mysql.database),
        pawnCompilerConfigured: Boolean(config.pawn.compilerPath),
        safety: config.safety,
        limits: config.limits,
        logs: await listLogCandidates(config),
        suggestions: [
          !config.safety.allowWriteFiles ? "File write tools are disabled by default. Keep this for normal analysis." : "File write tools are enabled. Use carefully.",
          !config.safety.allowWriteDb ? "Database write operations are disabled by default." : "Database write flag is enabled, but this server still exposes only read-only DB query tool.",
          "Set PROJECT_ROOT explicitly in MCP client config for predictable behavior.",
        ],
      };
    },
  },
];
