import { z } from "zod";
import type { ToolDefinition } from "../types.js";
import { getOutputMetrics, isCompactMode, setCompactMode } from "../utils/runtimeState.js";

const knownRiskyTools = [
  { tool: "project_overview", risk: "recursive project inventory" },
  { tool: "gamemode_overview", risk: "large Pawn/include inventory" },
  { tool: "ucp_overview", risk: "API/auth hit inventory" },
  { tool: "bot_overview", risk: "command/config/code inventory" },
  { tool: "read_project_file", risk: "file content when explicitly enabled" },
  { tool: "db_schema_overview", risk: "schema columns/indexes" },
  { tool: "read_recent_logs", risk: "multi-file log tails" },
  { tool: "trace_feature", risk: "cross-module search multiplication" },
  { tool: "generate_task_context", risk: "task-term search multiplication" },
];

function usageSequence(task: string): Array<{ step: number; tool: string; arguments: Record<string, unknown> }> {
  const lower = task.toLowerCase();
  const sequence: Array<{ step: number; tool: string; arguments: Record<string, unknown> }> = [];
  if (lower.includes("/") || lower.includes("command") || lower.includes("pawn") || lower.includes("biz")) {
    sequence.push({ step: sequence.length + 1, tool: "find_pawn_symbol", arguments: { symbol: task, limit: 10, includeSnippets: false } });
  }
  sequence.push({
    step: sequence.length + 1,
    tool: "trace_feature",
    arguments: { feature: task, maxFiles: 25, maxResults: 10, includeSnippets: false, depth: "shallow" },
  });
  if (/database|table|schema|business|auction|account|character/i.test(task)) {
    sequence.push({ step: sequence.length + 1, tool: "db_find_tables", arguments: { keyword: task.split(/\s+/).pop() ?? task } });
  }
  if (/bug|error|fail|crash|detect|timeout|unknown/i.test(task)) {
    sequence.push({ step: sequence.length + 1, tool: "read_recent_logs", arguments: { keyword: task.split(/\s+/).pop() ?? task, maxLines: 80 } });
  }
  sequence.push({
    step: sequence.length + 1,
    tool: "generate_task_context",
    arguments: { task, limit: 10, includeSnippets: false },
  });
  return sequence;
}

export const diagnosticTools: ToolDefinition[] = [
  {
    name: "mcp_context_health_check",
    description: "Check current MCP output limits, compact mode, risky tools, and recent output sizes.",
    schema: z.object({}),
    inputSchema: { type: "object", properties: {}, additionalProperties: false },
    handler(_input, { config }) {
      const warnings = [];
      if (config.limits.maxOutputChars > 8_000) warnings.push("MCP_MAX_OUTPUT_CHARS is above the recommended 8000.");
      if (config.limits.maxSearchResults > 10) warnings.push("MCP_MAX_SEARCH_RESULTS is above the recommended 10.");
      if (config.limits.maxFileReadLines > 120) warnings.push("MCP_MAX_FILE_READ_LINES is above the recommended 120.");
      if (!isCompactMode(config)) warnings.push("Compact mode is disabled; hard safety limits still apply.");
      return {
        compactMode: isCompactMode(config),
        limits: config.limits,
        defaults: config.defaults,
        riskyTools: knownRiskyTools,
        recentOutputSizes: getOutputMetrics().slice(0, 20),
        warnings,
        recommendedLimits: {
          MCP_MAX_SEARCH_RESULTS: 10,
          MCP_MAX_FILE_READ_LINES: 120,
          MCP_MAX_LOG_LINES: 80,
          MCP_MAX_DB_ROWS: 20,
          MCP_MAX_SNIPPET_LINES: 5,
          MCP_MAX_OUTPUT_CHARS: 8000,
          MCP_MAX_SCHEMA_TABLES: 20,
          MCP_MAX_FEATURE_FILES: 25,
        },
        unboundedOutputs: [],
      };
    },
  },
  {
    name: "mcp_compact_mode",
    description: "Show or change runtime compact mode. Hard output safety limits remain active when disabled.",
    schema: z.object({
      enabled: z.boolean().optional(),
    }),
    inputSchema: {
      type: "object",
      properties: { enabled: { type: "boolean" } },
      additionalProperties: false,
    },
    handler(input, { config }) {
      const enabled = input.enabled === undefined ? isCompactMode(config) : setCompactMode(input.enabled);
      return {
        enabled,
        hardSafetyLimitsActive: true,
        note: enabled
          ? "Compact mode forces bounded arrays and strings across all tools."
          : "Compact mode is disabled for this process, but MCP_MAX_OUTPUT_CHARS and tool-specific limits remain active.",
      };
    },
  },
  {
    name: "mcp_tool_usage_guide",
    description: "Return a compact recommended MCP tool sequence for a task without executing it.",
    schema: z.object({
      task: z.string().min(2),
    }),
    inputSchema: {
      type: "object",
      required: ["task"],
      properties: { task: { type: "string" } },
      additionalProperties: false,
    },
    handler(input) {
      return {
        task: input.task,
        compactModeOnly: true,
        sequence: usageSequence(input.task),
        rules: [
          "Do not read full files during discovery.",
          "Use cursor/offset for additional results.",
          "Request bounded content only after a relevant symbol or line is known.",
          "Do not write files or database data without explicit approval.",
        ],
      };
    },
  },
];
