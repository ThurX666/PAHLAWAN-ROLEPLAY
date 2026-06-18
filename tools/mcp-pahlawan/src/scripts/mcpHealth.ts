import { loadConfig } from "../config.js";
import { tools } from "../tools/index.js";
import { isCompactMode } from "../utils/runtimeState.js";

const config = loadConfig();
const requiredTools = [
  "search_code",
  "read_project_file",
  "read_recent_logs",
  "db_schema_overview",
  "db_safe_query",
  "trace_feature",
  "generate_task_context",
  "mcp_context_health_check",
  "mcp_compact_mode",
  "mcp_tool_usage_guide",
  "openspec_overview",
  "openspec_read_change",
  "openspec_task_status",
];
const toolNames = new Set(tools.map((tool) => tool.name));
const missing = requiredTools.filter((name) => !toolNames.has(name));

const report = {
  ok: missing.length === 0 && config.safety.defaultMode === "readonly" && isCompactMode(config),
  compactMode: isCompactMode(config),
  defaultMode: config.safety.defaultMode,
  limits: config.limits,
  missingTools: missing,
  toolCount: tools.length,
};

console.log(JSON.stringify(report, null, 2));
if (!report.ok) process.exitCode = 1;
