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

export async function dbSchemaOverview(config: AppConfig, options: { keyword?: string; maxTables?: number } = {}): Promise<unknown> {
  const connection = await getConnection(config);
  try {
    const maxTables = Math.min(Math.max(options.maxTables ?? 30, 1), 200);
    const keyword = options.keyword?.trim();
    const tableWhere = keyword ? "AND table_name LIKE ?" : "";
    const tableParams = keyword ? [config.mysql.database, `%${keyword}%`, maxTables] : [config.mysql.database, maxTables];
    const [tables] = await connection.query<mysql.RowDataPacket[]>(
      `SELECT table_name AS tableName
       FROM information_schema.tables
       WHERE table_schema = ?
       ${tableWhere}
       ORDER BY table_name
       LIMIT ?`,
      tableParams,
    );
    const tableNames = tables.map((row) => row.tableName).filter(Boolean);
    if (tableNames.length === 0) {
      return { tables: [], columns: [], indexes: [], note: "No matching tables found." };
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

    const [indexes] = await connection.query<mysql.RowDataPacket[]>(
      `SELECT table_name AS tableName, index_name AS indexName, column_name AS columnName, non_unique AS nonUnique
       FROM information_schema.statistics
       WHERE table_schema = ? AND table_name IN (${placeholders})
       ORDER BY table_name, index_name, seq_in_index`,
      [config.mysql.database, ...tableNames],
    );

    return redactObject({ tables, columns, indexes, truncatedToTables: maxTables, keyword: keyword || null });
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
       LIMIT 200`,
      [config.mysql.database, like, like],
    );
    return redactObject(rows);
  } finally {
    await connection.end();
  }
}

export async function dbSafeQuery(config: AppConfig, sql: string, limit: number): Promise<unknown> {
  const safeSql = ensureReadOnlySql(sql);
  const boundedLimit = Math.min(Math.max(limit, 1), config.limits.maxDbRows);
  const limitedSql = /\blimit\s+\d+/i.test(safeSql) ? safeSql : `${safeSql} LIMIT ${boundedLimit}`;
  const connection = await getConnection(config);
  try {
    const [rows] = await connection.query<mysql.RowDataPacket[]>(limitedSql);
    return redactRows(rows);
  } finally {
    await connection.end();
  }
}
