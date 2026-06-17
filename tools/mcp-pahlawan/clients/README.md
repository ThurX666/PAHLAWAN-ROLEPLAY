# PAHLAWAN ROLEPLAY MCP Client Setup

All clients use the same local MCP server through stdio:

```text
node tools/mcp-pahlawan/dist/index.js
```

Build it first:

```powershell
cd "C:\Users\guyub\Documents\PAHLAWAN ROLEPLAY\tools\mcp-pahlawan"
npm install
npm run build
```

## Safe Defaults

Every example keeps writes disabled:

```env
MCP_ALLOW_WRITE_FILES=false
MCP_ALLOW_WRITE_DB=false
MCP_REDACT_SECRETS=true
MCP_DEFAULT_MODE=readonly
```

Do not add secrets, tokens, database passwords, Discord tokens, webhook URLs, or API keys to client config files.

## Codex

Use `clients/codex/config.example.toml`.

Place it in project `.codex/config.toml` only when this project is trusted, or copy the server block to `C:\Users\guyub\.codex\config.toml`.

If the exact Codex MCP config schema differs in your installed version, verify with current Codex docs and keep the same command, args, and env values.

## Cursor

Use `clients/cursor/mcp.example.json`.

Cursor may support global or project-level MCP configuration depending on the installed version and settings. Use an absolute Windows path if Cursor is not launched from the repo root.

## Claude

Use `clients/claude/mcp.example.json`.

Claude Desktop and Claude Code use MCP JSON-style server definitions. Claude Code may also provide CLI commands to add MCP servers depending on the installed version.

## Google Antigravity

Use `clients/antigravity/mcp.example.json`.

Use stdio transport if supported by your local Antigravity setup. Exact config placement can differ by version, so keep the same command, args, and env values when adapting it.

## Recommended Workflow

For broad requests like syncing website database features with the gamemode, do not edit immediately. Use:

1. `generate_task_context`
2. `gamemode_overview`
3. `ucp_overview`
4. `db_schema_overview`
5. `trace_feature` per detected feature
6. produce a mapping table and mismatch report
7. generate migration/adapter plan
8. ask for confirmation before writes
9. apply changes feature-by-feature
