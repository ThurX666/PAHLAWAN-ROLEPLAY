import { execFile } from "node:child_process";
import fs from "node:fs";
import path from "node:path";
import { promisify } from "node:util";
import { z } from "zod";
import type { ToolDefinition } from "../types.js";
import { searchCode } from "../utils/fileSearch.js";
import { listLogCandidates } from "../utils/logReader.js";
import { relativePath } from "../utils/pathSafety.js";

const execFileAsync = promisify(execFile);

async function git(args: string[], cwd: string): Promise<string> {
  const { stdout } = await execFileAsync("git", args, { cwd, windowsHide: true, maxBuffer: 1024 * 1024 });
  return stdout;
}

export const workflowTools: ToolDefinition[] = [
  {
    name: "generate_task_context",
    description: "Generate a compact AI context pack for a task: related files, functions, DB hints, routes/commands, risks, and patch plan.",
    schema: z.object({
      task: z.string().min(2),
      module: z.enum(["gamemode", "website", "bot", "database", "all"]).default("all"),
      maxResults: z.number().int().min(1).max(50).optional(),
    }),
    inputSchema: {
      type: "object",
      required: ["task"],
      properties: {
        task: { type: "string" },
        module: { type: "string", enum: ["gamemode", "website", "bot", "database", "all"], default: "all" },
        maxResults: { type: "number", default: 30 },
      },
      additionalProperties: false,
    },
    async handler(input, { config }) {
      const terms: string[] = Array.from(
        new Set<string>(input.task.split(/\s+/).filter((term: string) => term.length > 2)),
      ).slice(0, 8);
      const perTermLimit = Math.min(input.maxResults ?? config.limits.maxSearchResults, 50);
      const related = [];
      for (const term of terms) {
        related.push({
          term,
          hits: await searchCode(config, term, {
            module: input.module,
            extensions: [".pwn", ".inc", ".php", ".js", ".ts", ".tsx", ".sql", ".json", ".txt"],
            limit: perTermLimit,
            contextLines: 1,
          }),
        });
      }
      return {
        task: input.task,
        module: input.module,
        related,
        knownRisks: [
          "Do not edit generated/runtime files.",
          "Keep secrets and config files out of Git.",
          "For Pawn, check callbacks and includes before adding code.",
          "For UCP, validate input server-side and preserve auth flow.",
          "For bot, respect Discord interaction response timing.",
          "For DB, plan migration and rollback before applying SQL.",
        ],
        suggestedPatchPlan: [
          "Read the most relevant files.",
          "Make the smallest scoped change.",
          "Run module-specific verification.",
          "Inspect git diff for secrets/runtime artifacts.",
        ],
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
        changedFiles,
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
