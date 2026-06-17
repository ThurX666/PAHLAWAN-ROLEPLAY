import { z } from "zod";
import type { ToolDefinition } from "../types.js";
import { searchCode } from "../utils/fileSearch.js";
import { listLogCandidates, readRecentLogs } from "../utils/logReader.js";

export const logTools: ToolDefinition[] = [
  {
    name: "read_recent_logs",
    description: "Read recent logs from configured log folders with redaction and warning/error extraction.",
    schema: z.object({
      filter: z.enum(["gamemode", "crashdetect", "mysql", "ucp", "bot", "all"]).default("all"),
      maxBytes: z.number().int().min(512).max(65536).default(12000),
      maxLines: z.number().int().min(1).max(1000).optional(),
    }),
    inputSchema: {
      type: "object",
      properties: {
        filter: { type: "string", enum: ["gamemode", "crashdetect", "mysql", "ucp", "bot", "all"], default: "all" },
        maxBytes: { type: "number", default: 12000 },
        maxLines: { type: "number", default: 200 },
      },
      additionalProperties: false,
    },
    handler(input, { config }) {
      return readRecentLogs(config, input.filter, input.maxBytes, input.maxLines ?? config.limits.maxLogLines);
    },
  },
  {
    name: "diagnose_issue",
    description: "Gather related code, logs, DB hints, and safe next steps for a described issue without applying changes.",
    schema: z.object({
      issue: z.string().min(2),
      module: z.enum(["gamemode", "website", "bot", "database", "all"]).default("all"),
    }),
    inputSchema: {
      type: "object",
      required: ["issue"],
      properties: {
        issue: { type: "string" },
        module: { type: "string", enum: ["gamemode", "website", "bot", "database", "all"], default: "all" },
      },
      additionalProperties: false,
    },
    async handler(input, { config }) {
      const terms: string[] = Array.from(
        new Set<string>(input.issue.split(/\s+/).filter((term: string) => term.length > 2)),
      ).slice(0, 6);
      const code = [];
      for (const term of terms) {
        code.push({
          term,
          hits: await searchCode(config, term, {
            module: input.module,
            extensions: [".pwn", ".inc", ".php", ".js", ".ts", ".tsx", ".sql", ".txt"],
            limit: Math.min(config.limits.maxSearchResults, 25),
            contextLines: 1,
          }),
        });
      }
      return {
        issue: input.issue,
        code,
        logs: await readRecentLogs(config, input.module === "website" ? "ucp" : input.module === "all" ? "all" : input.module, 12000, config.limits.maxLogLines).catch((error) => ({
          unavailable: String(error instanceof Error ? error.message : error),
        })),
        logCandidates: await listLogCandidates(config),
        likelyNextSteps: [
          "Confirm exact reproduction steps.",
          "Inspect related code hits before patching.",
          "Check latest log warnings/errors for the same timestamp.",
          "If database is involved, inspect schema with db_find_tables or db_schema_overview.",
          "Generate a task context before editing.",
        ],
      };
    },
  },
];
