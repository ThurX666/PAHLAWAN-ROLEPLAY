import { z } from "zod";
import type { ToolDefinition } from "../types.js";
import { dbFindTables, dbSafeQuery, dbSchemaOverview } from "../utils/database.js";
import { searchCode } from "../utils/fileSearch.js";
import { boundedLimit, resolveOffset } from "../utils/pagination.js";

export const databaseTools: ToolDefinition[] = [
  {
    name: "db_schema_overview",
    description: "Connect to MySQL/MariaDB in read-only mode and list tables, columns, keys, and indexes.",
    schema: z.object({
      keyword: z.string().optional(),
      tableKeyword: z.string().optional(),
      tables: z.array(z.string()).optional(),
      includeColumns: z.boolean().default(false),
      includeIndexes: z.boolean().default(false),
      includeSensitive: z.boolean().default(false),
      limit: z.number().int().min(1).max(200).optional(),
      maxTables: z.number().int().min(1).max(200).optional(),
      cursor: z.number().int().min(0).default(0),
      offset: z.number().int().min(0).optional(),
    }),
    inputSchema: {
      type: "object",
      properties: {
        keyword: { type: "string" },
        tableKeyword: { type: "string" },
        tables: { type: "array", items: { type: "string" } },
        includeColumns: { type: "boolean", default: false },
        includeIndexes: { type: "boolean", default: false },
        includeSensitive: { type: "boolean", default: false },
        limit: { type: "number", default: 20 },
        maxTables: { type: "number", description: "Deprecated alias for limit." },
        cursor: { type: "number", default: 0 },
        offset: { type: "number" },
      },
      additionalProperties: false,
    },
    handler(input, { config }) {
      return dbSchemaOverview(config, {
        tableKeyword: input.tableKeyword ?? input.keyword,
        tables: input.tables,
        includeColumns: input.includeColumns,
        includeIndexes: input.includeIndexes,
        includeSensitive: input.includeSensitive,
        limit: boundedLimit(input.limit ?? input.maxTables, config.limits.maxSchemaTables, config.limits.maxSchemaTables),
        offset: resolveOffset(input.cursor, input.offset),
      });
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
          sqlFileHits: await searchCode(config, input.keyword, {
            module: "database",
            extensions: [".sql", ".txt"],
            limit: config.limits.maxSearchResults,
            contextLines: 0,
          }),
        };
      }
    },
  },
  {
    name: "db_safe_query",
    description: "Execute read-only SELECT queries only. Destructive SQL and multi-statements are blocked.",
    schema: z.object({
      query: z.string().min(1),
      limit: z.number().int().min(1).max(500).optional(),
      maxRows: z.number().int().min(1).max(500).optional(),
      cursor: z.number().int().min(0).default(0),
      offset: z.number().int().min(0).optional(),
    }),
    inputSchema: {
      type: "object",
      required: ["query"],
      properties: {
        query: { type: "string" },
        limit: { type: "number", default: 20 },
        maxRows: { type: "number", description: "Deprecated alias for limit." },
        cursor: { type: "number", default: 0 },
        offset: { type: "number" },
      },
      additionalProperties: false,
    },
    handler(input, { config }) {
      return dbSafeQuery(
        config,
        input.query,
        boundedLimit(input.limit ?? input.maxRows, config.limits.maxDbRows, config.limits.maxDbRows),
        resolveOffset(input.cursor, input.offset),
      );
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
        limit: config.limits.maxSearchResults,
        contextLines: 0,
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
