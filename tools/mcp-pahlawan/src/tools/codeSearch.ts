import { z } from "zod";
import type { ToolDefinition } from "../types.js";
import { moduleSchema } from "../types.js";
import { readTextFileSlice, searchCode, type SearchHit } from "../utils/fileSearch.js";
import { boundedLimit, pageItems, resolveOffset } from "../utils/pagination.js";
import { safeResolve } from "../utils/pathSafety.js";
import { findRelatedOpenSpecChanges } from "../utils/openspec.js";

function extensionList(input?: string): string[] | undefined {
  if (!input) return undefined;
  return input
    .split(",")
    .map((item) => item.trim())
    .filter(Boolean)
    .map((item) => (item.startsWith(".") ? item : `.${item}`));
}

function maybeStripSnippets<T extends { context?: string[] }>(hits: T[], includeSnippets: boolean): T[] {
  return includeSnippets ? hits : hits.map(({ context: _context, ...rest }) => rest as T);
}

async function findSymbols(
  config: Parameters<ToolDefinition["handler"]>[1]["config"],
  keyword: string,
  extensions: string[],
  patterns: RegExp[],
  limit: number,
  offset: number,
) {
  const hits = await searchCode(config, keyword, {
    module: "all",
    extensions,
    limit: (offset + limit) * 3,
    contextLines: 2,
  });
  return hits
    .filter((hit) => patterns.some((pattern) => pattern.test(hit.text)))
    .slice(offset, offset + limit);
}

const stopWords = new Set(["and", "the", "for", "with", "from", "this", "that", "atau", "dan", "yang", "untuk", "mode"]);

function featureTerms(value: string): string[] {
  return Array.from(new Set(
    value
      .split(/[^\p{L}\p{N}_/-]+/u)
      .map((term) => term.trim())
      .filter((term) => term.length > 2 && !stopWords.has(term.toLowerCase())),
  )).slice(0, 6);
}

function moduleForFile(file: string): "gamemode" | "website" | "bot" | "database" | "logs" {
  if (file.startsWith("GAMEMODE/logs/") || /\.log$/i.test(file)) return "logs";
  if (file.startsWith("GAMEMODE/")) return "gamemode";
  if (file.startsWith("WEBSITE/")) return "website";
  if (file.startsWith("BOT/")) return "bot";
  return "database";
}

function dedupeHits(hits: SearchHit[]): SearchHit[] {
  const seen = new Set<string>();
  return hits.filter((hit) => {
    const key = `${hit.file}:${hit.line}`;
    if (seen.has(key)) return false;
    seen.add(key);
    return true;
  });
}

export const codeSearchTools: ToolDefinition[] = [
  {
    name: "search_code",
    description: "Search code across allowed project folders with module, extension, and keyword filters.",
    schema: z.object({
      keyword: z.string().min(1),
      module: moduleSchema,
      extension: z.string().optional(),
      limit: z.number().int().min(1).max(200).optional(),
      maxResults: z.number().int().min(1).max(200).optional(),
      cursor: z.number().int().min(0).default(0),
      offset: z.number().int().min(0).optional(),
      includeSnippets: z.boolean().optional(),
    }),
    inputSchema: {
      type: "object",
      required: ["keyword"],
      properties: {
        keyword: { type: "string" },
        module: { type: "string", enum: ["gamemode", "website", "bot", "database", "docs", "logs", "all"] },
        extension: { type: "string", description: "Single extension or comma-separated extensions, e.g. .pwn,.inc" },
        limit: { type: "number", default: 10 },
        maxResults: { type: "number", description: "Deprecated alias for limit." },
        cursor: { type: "number", default: 0 },
        offset: { type: "number" },
        includeSnippets: { type: "boolean", default: false },
      },
      additionalProperties: false,
    },
    async handler(input, { config }) {
      const limit = boundedLimit(input.limit ?? input.maxResults, config.limits.maxSearchResults, config.limits.maxSearchResults);
      const offset = resolveOffset(input.cursor, input.offset);
      const hits = await searchCode(config, input.keyword, {
        module: input.module,
        extensions: extensionList(input.extension),
        limit: limit + 1,
        offset,
        contextLines: 2,
      });
      return pageItems(maybeStripSnippets(hits, input.includeSnippets ?? config.defaults.includeSnippets), offset, limit, hits.length > limit);
    },
  },
  {
    name: "find_pawn_symbol",
    description: "Find Pawn functions, callbacks, commands, enums, defines, stocks, and publics.",
    schema: z.object({
      symbol: z.string().min(1),
      limit: z.number().int().min(1).max(200).optional(),
      maxResults: z.number().int().min(1).max(200).optional(),
      cursor: z.number().int().min(0).default(0),
      offset: z.number().int().min(0).optional(),
      includeSnippets: z.boolean().optional(),
    }),
    inputSchema: {
      type: "object",
      required: ["symbol"],
      properties: {
        symbol: { type: "string" },
        limit: { type: "number", default: 10 },
        maxResults: { type: "number", description: "Deprecated alias for limit." },
        cursor: { type: "number", default: 0 },
        offset: { type: "number" },
        includeSnippets: { type: "boolean", default: false },
      },
      additionalProperties: false,
    },
    async handler(input, { config }) {
      const limit = boundedLimit(input.limit ?? input.maxResults, config.limits.maxSearchResults, config.limits.maxSearchResults);
      const offset = resolveOffset(input.cursor, input.offset);
      const hits = await findSymbols(
        config,
        input.symbol,
        [".pwn", ".inc"],
        [/^\s*(public|stock|forward|native)\s+/i, /^\s*(CMD|YCMD|COMMAND):/i, /^\s*#define\s+/i, /^\s*enum\b/i, /On[A-Z][A-Za-z0-9_]+\s*\(/],
        limit + 1,
        offset,
      );
      return pageItems(maybeStripSnippets(hits, input.includeSnippets ?? config.defaults.includeSnippets), offset, limit, hits.length > limit);
    },
  },
  {
    name: "find_node_symbol",
    description: "Find JavaScript/TypeScript functions, exports, classes, routes, Discord commands, and handlers.",
    schema: z.object({
      symbol: z.string().min(1),
      module: moduleSchema,
      limit: z.number().int().min(1).max(200).optional(),
      maxResults: z.number().int().min(1).max(200).optional(),
      cursor: z.number().int().min(0).default(0),
      offset: z.number().int().min(0).optional(),
      includeSnippets: z.boolean().optional(),
    }),
    inputSchema: {
      type: "object",
      required: ["symbol"],
      properties: {
        symbol: { type: "string" },
        module: { type: "string", enum: ["gamemode", "website", "bot", "database", "docs", "logs", "all"] },
        limit: { type: "number", default: 10 },
        maxResults: { type: "number", description: "Deprecated alias for limit." },
        cursor: { type: "number", default: 0 },
        offset: { type: "number" },
        includeSnippets: { type: "boolean", default: false },
      },
      additionalProperties: false,
    },
    async handler(input, { config }) {
      const limit = boundedLimit(input.limit ?? input.maxResults, config.limits.maxSearchResults, config.limits.maxSearchResults);
      const offset = resolveOffset(input.cursor, input.offset);
      const hits = await searchCode(config, input.symbol, {
        module: input.module,
        extensions: [".js", ".cjs", ".mjs", ".ts", ".tsx", ".jsx"],
        limit: (offset + limit + 1) * 3,
        contextLines: 2,
      });
      const filtered = hits
        .filter((hit) =>
          /^\s*(export\s+)?(async\s+)?function\s+/i.test(hit.text) ||
          /^\s*(export\s+)?class\s+/i.test(hit.text) ||
          /^\s*(export\s+)?const\s+\w+/i.test(hit.text) ||
          /\.(get|post|put|delete|patch)\s*\(/i.test(hit.text) ||
          /SlashCommandBuilder|interactionCreate|client\.on|module\.exports|exports\./i.test(hit.text),
        )
        .slice(offset, offset + limit + 1);
      return pageItems(maybeStripSnippets(filtered, input.includeSnippets ?? config.defaults.includeSnippets), offset, limit, filtered.length > limit);
    },
  },
  {
    name: "trace_feature",
    description: "Search related files/functions/tables across gamemode, UCP, bot, and database for a feature name.",
    schema: z.object({
      feature: z.string().min(2),
      module: z.enum(["gamemode", "website", "bot", "database", "logs", "all"]).default("all"),
      maxFiles: z.number().int().min(1).max(100).optional(),
      maxResults: z.number().int().min(1).max(50).optional(),
      limit: z.number().int().min(1).max(50).optional(),
      cursor: z.number().int().min(0).default(0),
      offset: z.number().int().min(0).optional(),
      includeSnippets: z.boolean().optional(),
      includeFullContent: z.boolean().default(false),
      depth: z.enum(["shallow", "medium", "deep"]).default("shallow"),
    }),
    inputSchema: {
      type: "object",
      required: ["feature"],
      properties: {
        feature: { type: "string" },
        module: { type: "string", enum: ["gamemode", "website", "bot", "database", "logs", "all"], default: "all" },
        maxFiles: { type: "number", default: 25 },
        maxResults: { type: "number", default: 10 },
        limit: { type: "number", default: 10 },
        cursor: { type: "number", default: 0 },
        offset: { type: "number" },
        includeSnippets: { type: "boolean", default: false },
        includeFullContent: { type: "boolean", default: false },
        depth: { type: "string", enum: ["shallow", "medium", "deep"], default: "shallow" },
      },
      additionalProperties: false,
    },
    async handler(input, { config }) {
      const relatedOpenSpecChanges = findRelatedOpenSpecChanges(config, input.feature);
      const terms = featureTerms(input.feature);
      const limit = boundedLimit(input.limit ?? input.maxResults, config.limits.maxSearchResults, config.limits.maxSearchResults);
      const maxFiles = boundedLimit(input.maxFiles, config.limits.maxFeatureFiles, config.limits.maxFeatureFiles);
      const offset = resolveOffset(input.cursor, input.offset);
      const modules = input.module === "all"
        ? (["gamemode", "website", "bot", "database", "logs"] as const)
        : [input.module];
      const extensions = [".pwn", ".inc", ".js", ".ts", ".tsx", ".php", ".sql", ".txt", ".json", ".log"];
      const allHits: SearchHit[] = [];
      for (const term of terms) {
        for (const moduleName of modules) {
          allHits.push(...await searchCode(config, term, {
            module: moduleName,
            extensions,
            limit: Math.min(limit + 1, maxFiles),
            contextLines: input.depth === "shallow" ? 0 : 1,
          }));
        }
      }
      const ranked = dedupeHits(allHits).slice(0, maxFiles);
      const selected = ranked.slice(offset, offset + limit + 1);
      const visiblePage = selected.slice(0, limit);
      const includeSnippets = input.includeSnippets ?? config.defaults.includeSnippets;
      const grouped = Object.fromEntries(modules.map((moduleName) => [
        moduleName,
        maybeStripSnippets(visiblePage.filter((hit) => moduleForFile(hit.file) === moduleName), includeSnippets),
      ]));
      const content = input.includeFullContent
        ? await Promise.all(visiblePage.slice(0, 3).map(async (hit) => ({
            file: hit.file,
            content: await readTextFileSlice(config, safeResolve(config, hit.file), {
              startLine: hit.line,
              maxLines: Math.min(40, config.limits.maxFileReadLines),
              includeContent: true,
            }),
          })))
        : undefined;
      return {
        feature: input.feature,
        openspec: {
          exists: relatedOpenSpecChanges.length > 0,
          relatedChanges: relatedOpenSpecChanges.map((change) => ({
            changeId: change.changeId,
            matchedTerms: change.matchedTerms,
            proposalSummary: change.proposalSummary,
            paths: change.paths,
          })),
        },
        terms,
        depth: input.depth,
        groups: grouped,
        pagination: {
          offset,
          limit,
          returned: visiblePage.length,
          truncated: selected.length > limit,
          nextCursor: selected.length > limit ? offset + visiblePage.length : null,
        },
        ...(content ? { explicitlyRequestedContent: content } : {}),
        omitted: ranked.length >= maxFiles ? `Related files were capped at MCP_MAX_FEATURE_FILES=${maxFiles}.` : null,
        suggestedNextToolCalls: visiblePage.slice(0, 5).map((hit) => ({
          tool: "read_project_file",
          arguments: { filePath: hit.file, symbolName: hit.text, includeContent: false },
        })),
      };
    },
  },
];
