import fs from "node:fs";
import path from "node:path";
import { z } from "zod";
import type { AppConfig } from "../config.js";
import type { ToolDefinition } from "../types.js";
import { assertInsideRoot } from "../utils/pathSafety.js";

type ClientName = "codex" | "cursor" | "claude" | "antigravity";
type ClientMode = "readonly" | "write-enabled";

const clientSchema = z.enum(["codex", "cursor", "claude", "antigravity"]);
const modeSchema = z.enum(["readonly", "write-enabled"]).default("readonly");

function normalizePathForConfig(filePath: string): string {
  return filePath.replace(/\\/g, "/");
}

function compiledEntry(config: AppConfig, projectRoot = config.projectRoot): string {
  return normalizePathForConfig(path.join(projectRoot, "tools", "mcp-pahlawan", "dist", "index.js"));
}

function envFor(projectRoot: string, mode: ClientMode, allowDbWrite = false): Record<string, string> {
  const root = normalizePathForConfig(projectRoot);
  return {
    PROJECT_ROOT: root,
    GAMEMODE_DIR: "GAMEMODE",
    WEBSITE_DIR: "WEBSITE",
    BOT_DIR: "BOT",
    DATABASE_DIR: "DATABASE",
    LOGS_DIR: "GAMEMODE/logs",
    MCP_ALLOW_WRITE_FILES: mode === "write-enabled" ? "true" : "false",
    MCP_ALLOW_WRITE_DB: allowDbWrite ? "true" : "false",
    MCP_REDACT_SECRETS: "true",
    MCP_MAX_FILE_SIZE_KB: "512",
    MCP_MAX_SEARCH_RESULTS: "10",
    MCP_MAX_FILE_READ_LINES: "120",
    MCP_MAX_LOG_LINES: "80",
    MCP_MAX_DB_ROWS: "20",
    MCP_MAX_SNIPPET_LINES: "5",
    MCP_MAX_OUTPUT_CHARS: "8000",
    MCP_MAX_SCHEMA_TABLES: "20",
    MCP_MAX_FEATURE_FILES: "25",
    MCP_DEFAULT_INCLUDE_SNIPPETS: "false",
    MCP_COMPACT_MODE: "true",
    MCP_DEFAULT_MODE: mode,
  };
}

function jsonConfig(client: Exclude<ClientName, "codex">, projectRoot: string, mode: ClientMode): string {
  const server: Record<string, unknown> = {
    command: "node",
    args: [compiledEntry({ projectRoot } as AppConfig, projectRoot)],
    env: envFor(projectRoot, mode),
  };
  if (client === "claude") {
    server.type = "stdio";
  }
  return JSON.stringify({ mcpServers: { "pahlawan-roleplay": server } }, null, 2);
}

function tomlConfig(projectRoot: string, mode: ClientMode): string {
  const env = envFor(projectRoot, mode);
  const lines = [
    "# PAHLAWAN ROLEPLAY MCP for Codex",
    "# Use project-scoped config only for trusted projects.",
    "# Keep read-only mode by default; edit PROJECT_ROOT and path values for your machine.",
    "",
    "[mcp_servers.pahlawan-roleplay]",
    'command = "node"',
    `args = ["${compiledEntry({ projectRoot } as AppConfig, projectRoot)}"]`,
    "enabled = true",
    "startup_timeout_sec = 30",
    "tool_timeout_sec = 120",
    "",
    "[mcp_servers.pahlawan-roleplay.env]",
    ...Object.entries(env).map(([key, value]) => `${key} = "${value.replace(/\\/g, "\\\\")}"`),
    "",
    "# If your installed Codex version expects different key names, keep the same command, args, and env values.",
  ];
  return lines.join("\n");
}

function clientConfig(client: ClientName, projectRoot: string, mode: ClientMode): string {
  if (client === "codex") return tomlConfig(projectRoot, mode);
  return jsonConfig(client, projectRoot, mode);
}

export const clientTools: ToolDefinition[] = [
  {
    name: "client_config_overview",
    description: "Explain how to connect this MCP server to Codex, Cursor, Claude, and Antigravity.",
    schema: z.object({}),
    inputSchema: { type: "object", properties: {}, additionalProperties: false },
    handler(_input, { config }) {
      return {
        transport: "stdio",
        entryFile: compiledEntry(config),
        defaultMode: config.safety.defaultMode,
        clients: [
          {
            client: "codex",
            configExample: "tools/mcp-pahlawan/clients/codex/config.example.toml",
            note: "Use .codex/config.toml only when this project is trusted. Restart Codex after editing.",
          },
          {
            client: "cursor",
            configExample: "tools/mcp-pahlawan/clients/cursor/mcp.example.json",
            note: "Can be configured globally or per project depending on Cursor setup.",
          },
          {
            client: "claude",
            configExample: "tools/mcp-pahlawan/clients/claude/mcp.example.json",
            note: "Claude Desktop and Claude Code use MCP JSON; Claude Code may also provide CLI add commands depending on version.",
          },
          {
            client: "antigravity",
            configExample: "tools/mcp-pahlawan/clients/antigravity/mcp.example.json",
            note: "Use stdio if supported. Exact placement depends on installed Antigravity version.",
          },
        ],
        safeDefaults: envFor(config.projectRoot, "readonly"),
      };
    },
  },
  {
    name: "generate_client_config",
    description: "Generate recommended MCP config for Codex, Cursor, Claude, or Antigravity.",
    schema: z.object({
      client: clientSchema,
      projectRoot: z.string().min(1),
      mode: modeSchema,
      allowDbWrite: z.boolean().default(false),
    }),
    inputSchema: {
      type: "object",
      required: ["client", "projectRoot"],
      properties: {
        client: { type: "string", enum: ["codex", "cursor", "claude", "antigravity"] },
        projectRoot: { type: "string" },
        mode: { type: "string", enum: ["readonly", "write-enabled"], default: "readonly" },
        allowDbWrite: { type: "boolean", default: false },
      },
      additionalProperties: false,
    },
    handler(input, { config }) {
      const resolvedRoot = path.resolve(input.projectRoot);
      assertInsideRoot(path.dirname(resolvedRoot), resolvedRoot);
      const mode: ClientMode = input.mode;
      const text = input.client === "codex"
        ? tomlConfig(resolvedRoot, mode)
        : JSON.stringify({
          mcpServers: {
            "pahlawan-roleplay": {
              ...(input.client === "claude" ? { type: "stdio" } : {}),
              command: "node",
              args: [compiledEntry(config, resolvedRoot)],
              env: envFor(resolvedRoot, mode, input.allowDbWrite),
            },
          },
        }, null, 2);

      return {
        client: input.client,
        mode,
        dbWritesEnabled: input.allowDbWrite,
        warning: input.allowDbWrite
          ? "Database write flag was requested. This MCP server still exposes read-only query tools by default; add DB write tools only with explicit approval."
          : "Database writes remain disabled.",
        config: text,
      };
    },
  },
  {
    name: "validate_mcp_environment",
    description: "Validate required environment variables, project root, compiled entry file, Node version, and safe mode settings.",
    schema: z.object({}),
    inputSchema: { type: "object", properties: {}, additionalProperties: false },
    handler(_input, { config }) {
      const entry = path.join(config.projectRoot, "tools", "mcp-pahlawan", "dist", "index.js");
      const warnings = [];
      if (!process.env.PROJECT_ROOT) warnings.push("PROJECT_ROOT is not set; server is using inferred root.");
      if (!fs.existsSync(config.projectRoot)) warnings.push("PROJECT_ROOT does not exist.");
      if (!fs.existsSync(entry)) warnings.push("Compiled MCP entry file is missing. Run npm run build in tools/mcp-pahlawan.");
      if (config.safety.allowWriteFiles) warnings.push("MCP_ALLOW_WRITE_FILES is enabled.");
      if (config.safety.allowWriteDb) warnings.push("MCP_ALLOW_WRITE_DB is enabled.");
      if (!config.safety.redactSecrets) warnings.push("MCP_REDACT_SECRETS is disabled.");
      const nodeMajor = Number(process.versions.node.split(".")[0]);
      if (!Number.isFinite(nodeMajor) || nodeMajor < 18) warnings.push("Node.js 18+ is recommended.");
      return {
        nodeVersion: process.version,
        projectRoot: config.projectRoot,
        entryFile: normalizePathForConfig(entry),
        entryExists: fs.existsSync(entry),
        requiredEnv: {
          PROJECT_ROOT: Boolean(process.env.PROJECT_ROOT),
          MCP_ALLOW_WRITE_FILES: process.env.MCP_ALLOW_WRITE_FILES ?? "false",
          MCP_ALLOW_WRITE_DB: process.env.MCP_ALLOW_WRITE_DB ?? "false",
          MCP_REDACT_SECRETS: process.env.MCP_REDACT_SECRETS ?? "true",
          MCP_DEFAULT_MODE: config.safety.defaultMode,
        },
        warnings,
      };
    },
  },
  {
    name: "mcp_token_budget_report",
    description: "Show current output limits and recommend efficient tool usage for low-token workflows.",
    schema: z.object({}),
    inputSchema: { type: "object", properties: {}, additionalProperties: false },
    handler(_input, { config }) {
      return {
        limits: config.limits,
        compactModeDefault: config.defaults.compactMode,
        recommendations: [
          "Use project_overview before broad searches.",
          "Use generate_task_context for compact task packs.",
          "Use search_code with includeSnippets=false for first pass.",
          "Use read_project_file with startLine and maxLines for focused reads.",
          "Use db_find_tables before db_schema_overview on large databases.",
          "Use read_recent_logs defaults to get warnings/errors only.",
          "Raise MCP_MAX_OUTPUT_CHARS only temporarily when needed.",
        ],
        broadRequestWorkflow: [
          "generate_task_context",
          "gamemode_overview",
          "ucp_overview",
          "db_schema_overview",
          "trace_feature per detected feature",
          "produce mapping and mismatch table",
          "generate migration/adapter plan",
          "ask confirmation before writes",
        ],
      };
    },
  },
];
