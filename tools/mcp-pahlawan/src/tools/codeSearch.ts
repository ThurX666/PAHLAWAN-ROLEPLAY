import { z } from "zod";
import type { ToolDefinition } from "../types.js";
import { moduleSchema } from "../types.js";
import { searchCode } from "../utils/fileSearch.js";

function extensionList(input?: string): string[] | undefined {
  if (!input) return undefined;
  return input
    .split(",")
    .map((item) => item.trim())
    .filter(Boolean)
    .map((item) => (item.startsWith(".") ? item : `.${item}`));
}

async function findSymbols(
  config: Parameters<ToolDefinition["handler"]>[1]["config"],
  keyword: string,
  extensions: string[],
  patterns: RegExp[],
  limit: number,
) {
  const hits = await searchCode(config, keyword, {
    module: "all",
    extensions,
    limit: limit * 3,
    contextLines: 2,
  });
  return hits
    .filter((hit) => patterns.some((pattern) => pattern.test(hit.text)))
    .slice(0, limit);
}

export const codeSearchTools: ToolDefinition[] = [
  {
    name: "search_code",
    description: "Search code across allowed project folders with module, extension, and keyword filters.",
    schema: z.object({
      keyword: z.string().min(1),
      module: moduleSchema,
      extension: z.string().optional(),
      limit: z.number().int().min(1).max(200).default(50),
    }),
    inputSchema: {
      type: "object",
      required: ["keyword"],
      properties: {
        keyword: { type: "string" },
        module: { type: "string", enum: ["gamemode", "website", "bot", "database", "docs", "logs", "all"] },
        extension: { type: "string", description: "Single extension or comma-separated extensions, e.g. .pwn,.inc" },
        limit: { type: "number", default: 50 },
      },
      additionalProperties: false,
    },
    handler(input, { config }) {
      return searchCode(config, input.keyword, {
        module: input.module,
        extensions: extensionList(input.extension),
        limit: input.limit,
        contextLines: 2,
      });
    },
  },
  {
    name: "find_pawn_symbol",
    description: "Find Pawn functions, callbacks, commands, enums, defines, stocks, and publics.",
    schema: z.object({
      symbol: z.string().min(1),
      limit: z.number().int().min(1).max(200).default(80),
    }),
    inputSchema: {
      type: "object",
      required: ["symbol"],
      properties: {
        symbol: { type: "string" },
        limit: { type: "number", default: 80 },
      },
      additionalProperties: false,
    },
    handler(input, { config }) {
      return findSymbols(
        config,
        input.symbol,
        [".pwn", ".inc"],
        [/^\s*(public|stock|forward|native)\s+/i, /^\s*(CMD|YCMD|COMMAND):/i, /^\s*#define\s+/i, /^\s*enum\b/i, /On[A-Z][A-Za-z0-9_]+\s*\(/],
        input.limit,
      );
    },
  },
  {
    name: "find_node_symbol",
    description: "Find JavaScript/TypeScript functions, exports, classes, routes, Discord commands, and handlers.",
    schema: z.object({
      symbol: z.string().min(1),
      module: moduleSchema,
      limit: z.number().int().min(1).max(200).default(80),
    }),
    inputSchema: {
      type: "object",
      required: ["symbol"],
      properties: {
        symbol: { type: "string" },
        module: { type: "string", enum: ["gamemode", "website", "bot", "database", "docs", "logs", "all"] },
        limit: { type: "number", default: 80 },
      },
      additionalProperties: false,
    },
    async handler(input, { config }) {
      const hits = await searchCode(config, input.symbol, {
        module: input.module,
        extensions: [".js", ".cjs", ".mjs", ".ts", ".tsx", ".jsx"],
        limit: input.limit * 3,
        contextLines: 2,
      });
      return hits
        .filter((hit) =>
          /^\s*(export\s+)?(async\s+)?function\s+/i.test(hit.text) ||
          /^\s*(export\s+)?class\s+/i.test(hit.text) ||
          /^\s*(export\s+)?const\s+\w+/i.test(hit.text) ||
          /\.(get|post|put|delete|patch)\s*\(/i.test(hit.text) ||
          /SlashCommandBuilder|interactionCreate|client\.on|module\.exports|exports\./i.test(hit.text),
        )
        .slice(0, input.limit);
    },
  },
  {
    name: "trace_feature",
    description: "Search related files/functions/tables across gamemode, UCP, bot, and database for a feature name.",
    schema: z.object({
      feature: z.string().min(2),
      limitPerTerm: z.number().int().min(1).max(50).default(20),
    }),
    inputSchema: {
      type: "object",
      required: ["feature"],
      properties: {
        feature: { type: "string" },
        limitPerTerm: { type: "number", default: 20 },
      },
      additionalProperties: false,
    },
    async handler(input, { config }) {
      const terms: string[] = Array.from(
        new Set<string>(input.feature.split(/\s+/).map((term: string) => term.trim()).filter((term: string) => term.length > 2)),
      );
      const results = [];
      for (const term of terms) {
        results.push({
          term,
          hits: await searchCode(config, term, {
            module: "all",
            extensions: [".pwn", ".inc", ".js", ".ts", ".tsx", ".php", ".sql", ".txt", ".json"],
            limit: input.limitPerTerm,
            contextLines: 1,
          }),
        });
      }
      return {
        feature: input.feature,
        terms,
        results,
        guidance: [
          "Use these hits as a map before editing.",
          "For Pawn, inspect callbacks and includes before adding natives or new dependencies.",
          "For DB changes, generate a migration plan before applying SQL.",
          "For Discord bot changes, verify deferReply/reply/editReply timing.",
        ],
      };
    },
  },
];
