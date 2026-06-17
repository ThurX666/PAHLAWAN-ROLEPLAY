import path from "node:path";
import { fileURLToPath } from "node:url";
import dotenv from "dotenv";
import { assertInsideRoot } from "./utils/pathSafety.js";

const packageRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
dotenv.config({ path: path.join(packageRoot, ".env"), quiet: true });

function boolEnv(name: string, fallback: boolean): boolean {
  const value = process.env[name];
  if (value === undefined || value === "") return fallback;
  return ["1", "true", "yes", "on"].includes(value.toLowerCase());
}

function numberEnv(name: string, fallback: number): number {
  const value = Number(process.env[name]);
  return Number.isFinite(value) && value > 0 ? value : fallback;
}

function defaultProjectRoot(): string {
  return path.resolve(packageRoot, "../..");
}

function resolveProjectPath(root: string, value: string | undefined, fallback: string): string {
  const raw = value && value.trim() ? value.trim() : fallback;
  const resolved = path.isAbsolute(raw) ? path.resolve(raw) : path.resolve(root, raw);
  return assertInsideRoot(root, resolved);
}

export interface AppConfig {
  packageRoot: string;
  projectRoot: string;
  dirs: {
    gamemode: string;
    website: string;
    bot: string;
    database: string;
    logs: string;
  };
  mysql: {
    host?: string;
    port: number;
    user?: string;
    password?: string;
    database?: string;
  };
  pawn: {
    compilerPath?: string;
    compileArgs?: string;
  };
  safety: {
    allowWriteFiles: boolean;
    allowWriteDb: boolean;
    maxFileSizeBytes: number;
    redactSecrets: boolean;
    defaultMode: "readonly" | "write-enabled";
  };
  limits: {
    maxSearchResults: number;
    maxFileReadLines: number;
    maxLogLines: number;
    maxDbRows: number;
    maxSnippetLines: number;
    maxOutputChars: number;
    maxSchemaTables: number;
    maxFeatureFiles: number;
  };
  defaults: {
    includeSnippets: boolean;
    compactMode: boolean;
  };
}

export function loadConfig(): AppConfig {
  const root = path.resolve(process.env.PROJECT_ROOT || defaultProjectRoot());
  const projectRoot = assertInsideRoot(path.dirname(root), root);

  return {
    packageRoot,
    projectRoot,
    dirs: {
      gamemode: resolveProjectPath(projectRoot, process.env.GAMEMODE_DIR, "GAMEMODE"),
      website: resolveProjectPath(projectRoot, process.env.WEBSITE_DIR, "WEBSITE"),
      bot: resolveProjectPath(projectRoot, process.env.BOT_DIR, "BOT"),
      database: resolveProjectPath(projectRoot, process.env.DATABASE_DIR, "DATABASE"),
      logs: resolveProjectPath(projectRoot, process.env.LOGS_DIR, "GAMEMODE/logs"),
    },
    mysql: {
      host: process.env.MYSQL_HOST || undefined,
      port: numberEnv("MYSQL_PORT", 3306),
      user: process.env.MYSQL_USER || undefined,
      password: process.env.MYSQL_PASSWORD || undefined,
      database: process.env.MYSQL_DATABASE || undefined,
    },
    pawn: {
      compilerPath: process.env.PAWN_COMPILER_PATH || undefined,
      compileArgs: process.env.PAWN_COMPILE_ARGS || undefined,
    },
    safety: {
      allowWriteFiles: boolEnv("MCP_ALLOW_WRITE_FILES", false),
      allowWriteDb: boolEnv("MCP_ALLOW_WRITE_DB", false),
      maxFileSizeBytes: numberEnv("MCP_MAX_FILE_SIZE_KB", 512) * 1024,
      redactSecrets: boolEnv("MCP_REDACT_SECRETS", true),
      defaultMode: process.env.MCP_DEFAULT_MODE === "write-enabled" ? "write-enabled" : "readonly",
    },
    limits: {
      maxSearchResults: numberEnv("MCP_MAX_SEARCH_RESULTS", 10),
      maxFileReadLines: numberEnv("MCP_MAX_FILE_READ_LINES", 120),
      maxLogLines: numberEnv("MCP_MAX_LOG_LINES", 80),
      maxDbRows: numberEnv("MCP_MAX_DB_ROWS", 20),
      maxSnippetLines: numberEnv("MCP_MAX_SNIPPET_LINES", 5),
      maxOutputChars: numberEnv("MCP_MAX_OUTPUT_CHARS", 8_000),
      maxSchemaTables: numberEnv("MCP_MAX_SCHEMA_TABLES", 20),
      maxFeatureFiles: numberEnv("MCP_MAX_FEATURE_FILES", 25),
    },
    defaults: {
      includeSnippets: boolEnv("MCP_DEFAULT_INCLUDE_SNIPPETS", false),
      compactMode: boolEnv("MCP_COMPACT_MODE", true),
    },
  };
}
