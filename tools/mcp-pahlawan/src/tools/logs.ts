import { z } from "zod";
import type { ToolDefinition } from "../types.js";
import { searchCode } from "../utils/fileSearch.js";
import { listLogCandidates, readRecentLogs } from "../utils/logReader.js";
import { findRelatedOpenSpecChanges } from "../utils/openspec.js";

export const logTools: ToolDefinition[] = [
  {
    name: "read_recent_logs",
    description: "Read recent logs from configured log folders with redaction and warning/error extraction.",
    schema: z.object({
      filter: z.enum(["gamemode", "crashdetect", "mysql", "ucp", "bot", "all"]).default("all"),
      maxBytes: z.number().int().min(512).max(65536).default(12000),
      limit: z.number().int().min(1).max(1000).optional(),
      maxLines: z.number().int().min(1).max(1000).optional(),
      level: z.enum(["error", "warn", "all"]).default("warn"),
      keyword: z.string().optional(),
      since: z.string().optional(),
      includeInfo: z.boolean().default(false),
      cursor: z.number().int().min(0).default(0),
      offset: z.number().int().min(0).optional(),
    }),
    inputSchema: {
      type: "object",
      properties: {
        filter: { type: "string", enum: ["gamemode", "crashdetect", "mysql", "ucp", "bot", "all"], default: "all" },
        maxBytes: { type: "number", default: 12000 },
        limit: { type: "number", default: 80 },
        maxLines: { type: "number", description: "Deprecated alias for limit." },
        level: { type: "string", enum: ["error", "warn", "all"], default: "warn" },
        keyword: { type: "string" },
        since: { type: "string", description: "ISO date/time; files older than this are skipped." },
        includeInfo: { type: "boolean", default: false },
        cursor: { type: "number", default: 0 },
        offset: { type: "number" },
      },
      additionalProperties: false,
    },
    handler(input, { config }) {
      return readRecentLogs(config, input.filter, {
        maxBytes: input.maxBytes,
        maxLines: input.limit ?? input.maxLines,
        level: input.level,
        keyword: input.keyword,
        since: input.since,
        includeInfo: input.includeInfo,
        cursor: input.cursor,
        offset: input.offset,
      });
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
      const relatedOpenSpecChanges = findRelatedOpenSpecChanges(config, input.issue);
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
        openspecAuthority: {
          relatedChanges: relatedOpenSpecChanges.map((change) => ({
            changeId: change.changeId,
            proposalSummary: change.proposalSummary,
            requirements: change.requirements,
            paths: change.paths,
          })),
          rule: relatedOpenSpecChanges.length > 0
            ? "Diagnosis may explain evidence and fixes but must not override the related OpenSpec requirements."
            : "No related OpenSpec change detected.",
        },
        code,
        logs: await readRecentLogs(config, input.module === "website" ? "ucp" : input.module === "all" ? "all" : input.module, {
          maxBytes: 12_000,
          maxLines: config.limits.maxLogLines,
          level: "warn",
        }).catch((error) => ({
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
