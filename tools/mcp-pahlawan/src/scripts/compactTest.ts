import assert from "node:assert/strict";
import { loadConfig } from "../config.js";
import { tools } from "../tools/index.js";
import { applyOutputBudget } from "../utils/outputBudget.js";
import { boundedLimit } from "../utils/pagination.js";
import { redactObject, redactText } from "../utils/redact.js";
import { isCompactMode } from "../utils/runtimeState.js";

const config = loadConfig();
const byName = new Map(tools.map((tool) => [tool.name, tool]));
const context = { config };

assert.equal(isCompactMode(config), true, "compact mode must be enabled by default");
assert.equal(config.safety.defaultMode, "readonly", "read-only mode must be the default");

const oversized = {
  items: Array.from({ length: 500 }, (_, index) => ({
    index,
    text: "x".repeat(500),
  })),
};
const budgeted = applyOutputBudget("synthetic_test", oversized, config);
assert.ok(budgeted.length <= config.limits.maxOutputChars, "output budget must cap serialized output");
assert.equal(JSON.parse(budgeted).truncated, true, "oversized output must report truncation");

const searchTool = byName.get("search_code");
assert.ok(searchTool, "search_code tool must exist");
const searchInput = searchTool.schema.parse({ keyword: "MCP", module: "docs", limit: config.limits.maxSearchResults });
const searchResult = await searchTool.handler(searchInput, context) as { items: unknown[] };
assert.ok(searchResult.items.length <= config.limits.maxSearchResults, "search result limit must be enforced");

const readTool = byName.get("read_project_file");
assert.ok(readTool, "read_project_file tool must exist");
const readInput = readTool.schema.parse({ filePath: "tools/mcp-pahlawan/README.md" });
const readResult = await readTool.handler(readInput, context) as { content?: string; outline?: unknown; totalLines?: number };
assert.equal(readResult.content, undefined, "file content must be omitted by default");
assert.ok(readResult.outline, "outline must be returned by default");
assert.ok((readResult.totalLines ?? 0) > 0, "file metadata must include total lines");

assert.equal(
  boundedLimit(config.limits.maxSchemaTables * 10, config.limits.maxSchemaTables, config.limits.maxSchemaTables),
  config.limits.maxSchemaTables,
  "schema table limit must be enforced",
);

const redactedText = redactText("DISCORD_TOKEN=abc.def.ghi\nAPI_KEY=secret-value");
assert.ok(!redactedText.includes("secret-value"), "text secrets must be redacted");
const redactedObject = redactObject({ password: "private", token: "private", safe: "value" });
assert.equal(redactedObject.password, "[REDACTED]", "password fields must be redacted");
assert.equal(redactedObject.token, "[REDACTED]", "token fields must be redacted");

const projectTool = byName.get("project_overview");
assert.ok(projectTool, "project_overview tool must exist");
const projectResult = await projectTool.handler(projectTool.schema.parse({}), context);
const projectOutput = applyOutputBudget("project_overview", projectResult, config);
assert.ok(projectOutput.length <= config.limits.maxOutputChars, "project overview must remain within output budget");
assert.ok(!projectOutput.includes("content\":"), "project overview must not return full file content");

const openspecOverviewTool = byName.get("openspec_overview");
assert.ok(openspecOverviewTool, "openspec_overview tool must exist");
const openspecOverview = await openspecOverviewTool.handler(openspecOverviewTool.schema.parse({}), context) as { detected?: boolean; activeChanges?: unknown[] };
assert.equal(openspecOverview.detected, true, "OpenSpec root must be detected");
assert.ok((openspecOverview.activeChanges?.length ?? 0) > 0, "active OpenSpec changes must be summarized");

console.log(JSON.stringify({
  ok: true,
  checks: [
    "max output chars",
    "search result limit",
    "outline-first file read",
    "schema table limit",
    "secret redaction",
    "compact mode default",
    "no full project content by default",
    "compact OpenSpec overview",
  ],
}, null, 2));
