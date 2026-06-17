import mysql from "mysql2/promise";
import type { AppConfig } from "../config.js";
import { redactObject, isSensitiveKey } from "./redact.js";

function hasDbConfig(config: AppConfig): boolean {
  return Boolean(config.mysql.host && config.mysql.user && config.mysql.database);
}

async function getConnection(config: AppConfig): Promise<mysql.Connection> {
  if (!hasDbConfig(config)) {
    throw new Error("MySQL config is incomplete. Set MYSQL_HOST, MYSQL_USER, and MYSQL_DATABASE.");
  }

  return mysql.createConnection({
    host: config.mysql.host,
    port: config.mysql.port,
    user: config.mysql.user,
    password: config.mysql.password,
    database: config.mysql.database,
    multipleStatements: false,
  });
}

export function ensureReadOnlySql(sql: string): string {
  const trimmed = sql.trim().replace(/;+\s*$/, "");
  if (trimmed.includes(";")) {
    throw new Error("Multi-statement SQL is blocked");
  }
  if (!/^select\b/i.test(trimmed)) {
    throw new Error("Only SELECT queries are allowed");
  }
  if (/\b(insert|update|delete|drop|alter|truncate|create|grant|revoke|replace|merge|call|load|outfile|infile)\b/i.test(trimmed)) {
    throw new Error("Destructive or side-effect SQL keyword is blocked");
  }
  return trimmed;
}

export function redactRows(rows: unknown[]): unknown[] {
  return rows.map((row) => {
    if (!row || typeof row !== "object") return row;
    const output: Record<string, unknown> = {};
    for (const [key, value] of Object.entries(row)) {
      output[key] = isSensitiveKey(key) ? "[REDACTED]" : redactObject(value);
    }
    return output;
  });
}

const sensitiveColumn = /(password|pass|hash|salt|token|secret|api[_-]?key|email|ip|hwid|serial)/i;
const importantColumn = /(^id$|_id$|name|title|type|status|owner|created|updated|date|level|amount|price|active)/i;

export interface SchemaOverviewOptions {
  tableKeyword?: string;
  tables?: string[];
  includeColumns?: boolean;
  includeIndexes?: boolean;
  includeSensitive?: boolean;
  limit?: number;
  offset?: number;
}

export async function dbSchemaOverview(config: AppConfig, options: SchemaOverviewOptions = {}): Promise<unknown> {
  const connection = await getConnection(config);
  try {
    const limit = Math.min(Math.max(options.limit ?? config.limits.maxSchemaTables, 1), config.limits.maxSchemaTables);
    const offset = Math.max(options.offset ?? 0, 0);
    const keyword = options.tableKeyword?.trim();
    const requestedTables = (options.tables ?? []).map((table) => table.trim()).filter(Boolean).slice(0, config.limits.maxSchemaTables);
    const conditions: string[] = [];
    const params: unknown[] = [config.mysql.database];
    if (keyword) {
      conditions.push("table_name LIKE ?");
      params.push(`%${keyword}%`);
    }
    if (requestedTables.length > 0) {
      conditions.push(`table_name IN (${requestedTables.map(() => "?").join(",")})`);
      params.push(...requestedTables);
    }
    params.push(limit + 1, offset);
    const [tables] = await connection.query<mysql.RowDataPacket[]>(
      `SELECT table_name AS tableName
       FROM information_schema.tables
       WHERE table_schema = ?
       ${conditions.length > 0 ? `AND ${conditions.join(" AND ")}` : ""}
       ORDER BY table_name
       LIMIT ? OFFSET ?`,
      params,
    );
    const hasMore = tables.length > limit;
    const pageTables = tables.slice(0, limit);
    const tableNames = pageTables.map((row) => String(row.tableName)).filter(Boolean);
    if (tableNames.length === 0) {
      return { tables: [], offset, limit, nextCursor: null, note: "No matching tables found." };
    }
    const placeholders = tableNames.map(() => "?").join(",");

    const [columns] = await connection.query<mysql.RowDataPacket[]>(
      `SELECT table_name AS tableName, column_name AS columnName, column_type AS columnType,
              is_nullable AS nullable, column_key AS columnKey, extra
       FROM information_schema.columns
       WHERE table_schema = ? AND table_name IN (${placeholders})
       ORDER BY table_name, ordinal_position`,
      [config.mysql.database, ...tableNames],
    );

    const indexes = options.includeIndexes
      ? (await connection.query<mysql.RowDataPacket[]>(
          `SELECT table_name AS tableName, index_name AS indexName, column_name AS columnName, non_unique AS nonUnique
           FROM information_schema.statistics
           WHERE table_schema = ? AND table_name IN (${placeholders})
           ORDER BY table_name, index_name, seq_in_index`,
          [config.mysql.database, ...tableNames],
        ))[0]
      : [];

    const summaries = tableNames.map((tableName) => {
      const tableColumns = columns.filter((column) => column.tableName === tableName);
      const visibleColumns = tableColumns.filter((column) => options.includeSensitive || !sensitiveColumn.test(String(column.columnName)));
      const primaryKey = visibleColumns.find((column) => column.columnKey === "PRI")?.columnName ?? null;
      const selectedColumns = (options.includeColumns
        ? visibleColumns
        : visibleColumns.filter((column) => column.columnKey === "PRI" || importantColumn.test(String(column.columnName))))
        .slice(0, options.includeColumns ? 30 : 12)
        .map((column) => ({
          name: column.columnName,
          type: column.columnType,
          nullable: column.nullable === "YES",
          key: column.columnKey || null,
        }));
      const relationHints = visibleColumns
        .filter((column) => /_id$/i.test(String(column.columnName)) && column.columnKey !== "PRI")
        .slice(0, 8)
        .map((column) => `${column.columnName} may reference another table`);
      return {
        tableName,
        primaryKey,
        importantColumns: selectedColumns,
        relationHints,
        hiddenSensitiveColumnCount: tableColumns.length - visibleColumns.length,
        ...(options.includeIndexes
          ? { indexes: indexes.filter((index) => index.tableName === tableName).slice(0, 20) }
          : {}),
      };
    });

    return redactObject({
      tables: summaries,
      offset,
      limit,
      returned: summaries.length,
      truncated: hasMore,
      nextCursor: hasMore ? offset + summaries.length : null,
      filters: { tableKeyword: keyword || null, tables: requestedTables },
      note: options.includeColumns
        ? "Columns are capped per table; sensitive names remain hidden unless includeSensitive=true."
        : "Compact schema summary. Set includeColumns=true for bounded column details.",
    });
  } finally {
    await connection.end();
  }
}

export async function dbFindTables(config: AppConfig, keyword: string): Promise<unknown> {
  const connection = await getConnection(config);
  try {
    const like = `%${keyword}%`;
    const [rows] = await connection.query<mysql.RowDataPacket[]>(
      `SELECT table_name AS tableName, column_name AS columnName, column_type AS columnType, column_key AS columnKey
       FROM information_schema.columns
       WHERE table_schema = ?
         AND (table_name LIKE ? OR column_name LIKE ?)
       ORDER BY table_name, ordinal_position
       LIMIT ?`,
      [config.mysql.database, like, like, config.limits.maxSearchResults],
    );
    return redactObject(rows);
  } finally {
    await connection.end();
  }
}

export async function dbSafeQuery(config: AppConfig, sql: string, limit: number, offset = 0): Promise<unknown> {
  const safeSql = ensureReadOnlySql(sql);
  const boundedLimit = Math.min(Math.max(limit, 1), config.limits.maxDbRows);
  const connection = await getConnection(config);
  try {
    const [rows] = await connection.query<mysql.RowDataPacket[]>(
      `SELECT * FROM (${safeSql}) AS mcp_page LIMIT ? OFFSET ?`,
      [boundedLimit + 1, Math.max(offset, 0)],
    );
    const hasMore = rows.length > boundedLimit;
    const page = redactRows(rows.slice(0, boundedLimit));
    return {
      rows: page,
      offset,
      limit: boundedLimit,
      returned: page.length,
      truncated: hasMore,
      nextCursor: hasMore ? offset + page.length : null,
    };
  } finally {
    await connection.end();
  }
}
