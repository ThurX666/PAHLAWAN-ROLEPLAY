import { z } from "zod";
import type { ToolDefinition } from "../types.js";
import { dbFindTables, dbSafeQuery, dbSchemaOverview } from "../utils/database.js";
import { searchCode } from "../utils/fileSearch.js";

export const databaseTools: ToolDefinition[] = [
  {
    name: "db_schema_overview",
    description: "Connect to MySQL/MariaDB in read-only mode and list tables, columns, keys, and indexes.",
    schema: z.object({
      keyword: z.string().optional(),
      maxTables: z.number().int().min(1).max(200).default(30),
    }),
    inputSchema: {
      type: "object",
      properties: {
        keyword: { type: "string" },
        maxTables: { type: "number", default: 30 },
      },
      additionalProperties: false,
    },
    handler(input, { config }) {
      return dbSchemaOverview(config, { keyword: input.keyword, maxTables: input.maxTables });
    },
  },
  {
    name: "db_find_tables",
    description: "Search database tables/columns by keyword.",
    schema: z.object({
      keyword: z.string().min(1),
    }),
    inputSchema: {
      type: "object",
      required: ["keyword"],
      properties: { keyword: { type: "string" } },
      additionalProperties: false,
    },
    async handler(input, { config }) {
      try {
        return await dbFindTables(config, input.keyword);
      } catch (error) {
        return {
          dbUnavailable: String(error instanceof Error ? error.message : error),
          sqlFileHits: await searchCode(config, input.keyword, { module: "database", extensions: [".sql", ".txt"], limit: 60, contextLines: 1 }),
        };
      }
    },
  },
  {
    name: "db_safe_query",
    description: "Execute read-only SELECT queries only. Destructive SQL and multi-statements are blocked.",
    schema: z.object({
      query: z.string().min(1),
      maxRows: z.number().int().min(1).max(500).optional(),
    }),
    inputSchema: {
      type: "object",
      required: ["query"],
      properties: {
        query: { type: "string" },
        maxRows: { type: "number", default: 50 },
      },
      additionalProperties: false,
    },
    handler(input, { config }) {
      return dbSafeQuery(config, input.query, input.maxRows ?? config.limits.maxDbRows);
    },
  },
  {
    name: "db_migration_plan",
    description: "Generate a SQL migration plan and rollback sketch without executing SQL.",
    schema: z.object({
      changeRequest: z.string().min(2),
    }),
    inputSchema: {
      type: "object",
      required: ["changeRequest"],
      properties: { changeRequest: { type: "string" } },
      additionalProperties: false,
    },
    async handler(input, { config }) {
      const related = await searchCode(config, input.changeRequest, {
        module: "all",
        extensions: [".sql", ".txt", ".php", ".pwn", ".inc", ".js", ".ts", ".tsx"],
        limit: 80,
        contextLines: 1,
      });
      return {
        changeRequest: input.changeRequest,
        related,
        plan: [
          "Identify affected tables and columns from existing schema/code.",
          "Draft forward migration SQL with explicit column types, indexes, and defaults.",
          "Draft rollback SQL where possible.",
          "Update gamemode queries/callbacks, UCP API handlers, and bot queries together.",
          "Test on a copied local database before production.",
        ],
        execution: "No SQL was executed. This tool only plans migrations.",
      };
    },
  },
];
