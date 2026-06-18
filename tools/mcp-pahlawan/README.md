# MCP PAHLAWAN ROLEPLAY

Local MCP server untuk membantu AI coding clients bekerja aman dan cepat di project PAHLAWAN ROLEPLAY.

## OpenSpec workflow authority

OpenSpec is the source of truth for feature planning and requirements. MCP remains the support layer for context, diagnostics, search, database/log/code inspection, and validation.

- Check active OpenSpec changes before coding.
- If a related change exists, read it first and implement only its approved scope.
- Do not generate a competing feature plan when OpenSpec already exists.
- For medium/high-risk work without OpenSpec, propose creating a change first.
- Keep patches small and feature-scoped.
- Do not scan the entire project or dump full files, schemas, logs, or OpenSpec artifacts by default.
- Do not delete files, run migrations, or write database data without explicit approval.

OpenSpec-aware tools:

- `openspec_overview`
- `openspec_read_change`
- `openspec_task_status`

Server ini memakai **stdio transport** sebagai default agar portable untuk:

- OpenAI Codex
- Cursor
- Claude Code / Claude Desktop style MCP clients
- Google Antigravity

Tool logic tidak bergantung pada client tertentu. Perbedaan client hanya ada di contoh config dan dokumentasi.

## Folder Structure

```text
tools/mcp-pahlawan/
  .env.example
  README.md
  package.json
  tsconfig.json
  clients/
    README.md
    codex/config.example.toml
    cursor/mcp.example.json
    claude/mcp.example.json
    antigravity/mcp.example.json
  examples/
    codex-config.toml
    mcp-client-config.json
    prompts.md
  src/
    index.ts
    config.ts
    types.ts
    tools/
    utils/
```

## Installation

```powershell
cd "C:\Users\guyub\Documents\PAHLAWAN ROLEPLAY\tools\mcp-pahlawan"
npm install
npm run build
```

Test import/build lokal:

```powershell
node -e "const cfg=await import('./dist/config.js'); const mod=await import('./dist/tools/index.js'); console.log(mod.tools.length, cfg.loadConfig().projectRoot)"
```

Test MCP via stdio client smoke test:

```powershell
node -e "import { Client } from '@modelcontextprotocol/sdk/client/index.js'; import { StdioClientTransport } from '@modelcontextprotocol/sdk/client/stdio.js'; const t=new StdioClientTransport({command:'node',args:['dist/index.js'],env:{...process.env,PROJECT_ROOT:'C:/Users/guyub/Documents/PAHLAWAN ROLEPLAY'}}); const c=new Client({name:'smoke',version:'0.0.0'}); await c.connect(t); const tools=await c.listTools(); console.log(tools.tools.length); await c.close();"
```

Running `npm start` directly is allowed, but it will wait for an MCP client because this server communicates over stdio.

Compact-mode checks:

```powershell
npm run mcp:health
npm run mcp:test-compact
```

## Environment

Copy local env only if needed:

```powershell
Copy-Item .env.example .env
```

Safe defaults:

```env
PROJECT_ROOT=
GAMEMODE_DIR=
WEBSITE_DIR=
BOT_DIR=
DATABASE_DIR=
LOGS_DIR=
MCP_ALLOW_WRITE_FILES=false
MCP_ALLOW_WRITE_DB=false
MCP_REDACT_SECRETS=true
MCP_MAX_FILE_SIZE_KB=512
MCP_MAX_SEARCH_RESULTS=10
MCP_MAX_FILE_READ_LINES=120
MCP_MAX_LOG_LINES=80
MCP_MAX_DB_ROWS=20
MCP_MAX_SNIPPET_LINES=5
MCP_MAX_OUTPUT_CHARS=8000
MCP_MAX_SCHEMA_TABLES=20
MCP_MAX_FEATURE_FILES=25
MCP_DEFAULT_INCLUDE_SNIPPETS=false
MCP_COMPACT_MODE=true
MCP_DEFAULT_MODE=readonly
```

Do not commit `.env`.

## Client Setup

All client examples run the same compiled entry file:

```text
tools/mcp-pahlawan/dist/index.js
```

### Codex

Use:

```text
tools/mcp-pahlawan/clients/codex/config.example.toml
```

Project-scoped config is recommended only when this repo is trusted. If your installed Codex MCP schema differs, verify with current Codex docs and keep the same command, args, and env values.

### Cursor

Use:

```text
tools/mcp-pahlawan/clients/cursor/mcp.example.json
```

Cursor config can be global or project-level depending on your Cursor setup. Use absolute Windows paths when Cursor is not launched from repo root.

### Claude

Use:

```text
tools/mcp-pahlawan/clients/claude/mcp.example.json
```

Claude Desktop and Claude Code style clients use `mcpServers`. Claude Code may also support CLI commands for adding MCP servers depending on version.

### Antigravity

Use:

```text
tools/mcp-pahlawan/clients/antigravity/mcp.example.json
```

Use stdio if supported by your local Antigravity setup. Exact placement and config file location may depend on installed version.

## Security Mode

Read-only is default.

- `MCP_ALLOW_WRITE_FILES=false`
- `MCP_ALLOW_WRITE_DB=false`
- `MCP_DEFAULT_MODE=readonly`

Write-enabled mode:

- requires `MCP_ALLOW_WRITE_FILES=true`
- write tools still require `confirmWrite: true`
- patch writes create a backup first
- database writes remain disabled unless explicitly configured and implemented later

Database mode:

- `db_safe_query` accepts `SELECT` only
- destructive SQL and multi-statements are blocked
- sensitive columns are redacted

Secret redaction:

- `.env`, JSON config, tokens, Discord tokens, webhook URLs, API keys, database passwords, salts, and auth headers are redacted.

## Low Token Design

Defaults are intentionally small:

- search results: 10
- file read lines: 120
- log lines: 80
- DB rows: 20
- snippet lines: 5
- schema tables: 20
- feature files: 25
- output chars: 8000
- snippets disabled by default
- compact mode enabled by default

Use these parameters when supported:

- `maxResults`
- `maxLines`
- `maxBytes`
- `includeSnippets`
- `cursor`
- `offset`
- `startLine`
- `limit`

`read_project_file` is outline-first. It returns metadata and detected includes/imports, defines, enums, callbacks, functions, classes, commands, routes, handlers, dialog IDs, and sections. File content is returned only with `includeContent: true`, and remains bounded by line and character limits.

Recommended sequence:

1. `project_overview`
2. `generate_task_context`
3. targeted `search_code`
4. focused `read_project_file`
5. module-specific analyzer

Avoid full-file reads unless explicitly needed.

When using MCP:

- Never scan the entire project by default.
- Never dump full files by default.
- Never dump the full database schema by default.
- Never dump full logs by default.
- Work feature-by-feature.
- Use compact mode by default.
- Prefer summaries, paths, symbols, line numbers, and small snippets.
- Ask before reading large files.
- Ask before applying patches.
- Use pagination for large results.
- Keep output under `MCP_MAX_OUTPUT_CHARS`.

## Main Tools

Client:

- `client_config_overview`
- `generate_client_config`
- `validate_mcp_environment`
- `mcp_token_budget_report`
- `mcp_context_health_check`
- `mcp_compact_mode`
- `mcp_tool_usage_guide`

Discovery:

- `project_overview`
- `list_project_modules`
- `find_project_file`

Search:

- `search_code`
- `find_pawn_symbol`
- `find_node_symbol`
- `trace_feature`

File:

- `read_project_file`
- `write_project_patch`
- `create_project_file`

Gamemode:

- `gamemode_overview`
- `compile_gamemode`
- `parse_pawn_compile_log`
- `analyze_pawn_callback_flow`
- `find_dialog_ids`
- `find_textdraw_usage`

UCP:

- `ucp_overview`
- `list_ucp_routes`
- `analyze_ucp_auth`
- `generate_ucp_feature_plan`

Bot:

- `bot_overview`
- `list_discord_commands`
- `analyze_discord_interaction_flow`
- `generate_bot_feature_plan`

Database:

- `db_schema_overview`
- `db_find_tables`
- `db_safe_query`
- `db_migration_plan`

Logs/workflow:

- `read_recent_logs`
- `diagnose_issue`
- `generate_task_context`
- `generate_changelog`
- `health_check`

## Required Broad-Task Workflow

For broad requests such as:

```text
Synchronize the website database with the gamemode for all features.
```

Do not edit immediately. Follow:

1. Run `generate_task_context`.
2. Run `gamemode_overview`.
3. Run `ucp_overview`.
4. Run `db_schema_overview`.
5. Run `trace_feature` for each detected feature.
6. Produce a database-feature mapping table.
7. Detect mismatches between gamemode, website, bot, and database.
8. Generate a migration/adapter plan.
9. Ask for confirmation before writing files.
10. Apply changes feature-by-feature.

## Recommended Prompts

Analyze before editing:

```text
Use the Pahlawan MCP to generate a task context for this request. Do not edit files yet.
```

Trace feature:

```text
Use the Pahlawan MCP to trace the business auction system across gamemode, UCP, bot, and database. Summarize related files, functions, tables, and risks.
```

Diagnose issue:

```text
Use Pahlawan MCP in compact mode.

Task: Diagnose why /bizmenu does not detect nearby business.

Rules:
- Do not scan the entire project.
- Do not read full files.
- Use maxResults 10.
- Return only related files, functions, line numbers, database tables, and risks.
- Do not edit files yet.
```

Trace feature safely:

```text
Use Pahlawan MCP to trace feature: business auction.

Compact mode only.
No full file reads.
No database writes.
Return a compact context pack first.
After I approve, suggest a small patch.
```

Compile gamemode:

```text
Use the Pahlawan MCP to compile the gamemode and parse errors. Suggest the smallest safe patch.
```

Sync database:

```text
Use the Pahlawan MCP to map gamemode, UCP, bot, and database features. Produce mismatch and migration plan first. Do not edit files yet.
```

Generate UCP feature plan:

```text
Use the Pahlawan MCP to generate a safe implementation plan for UCP character dashboard connected to the existing database.
```

Debug Discord interaction:

```text
Use the Pahlawan MCP to inspect the Discord bot interaction flow and find why Unknown interaction happens. Focus on deferReply, reply, editReply, and command execution time.
```

## Troubleshooting

Node not found:

- Install Node.js 18+.
- Use absolute path to `node.exe` in client config if needed.

Wrong project root:

- Set `PROJECT_ROOT` explicitly.
- Use forward slashes in JSON examples or escaped backslashes in TOML.

MCP server not appearing:

- Run `npm run build`.
- Confirm `tools/mcp-pahlawan/dist/index.js` exists.
- Restart the AI client.
- Use `validate_mcp_environment`.

Permission denied:

- Use absolute paths.
- Ensure the AI client can execute `node`.
- Avoid placing secrets in client config.

Output too large:

- Lower `MCP_MAX_OUTPUT_CHARS`.
- Use `maxResults`, `maxLines`, `includeSnippets=false`, and pagination.
- Start with `generate_task_context`.
- Run `mcp_context_health_check` and keep compact mode enabled.

## Rebuild And Reconnect

```powershell
cd "C:\Users\guyub\Documents\PAHLAWAN ROLEPLAY\tools\mcp-pahlawan"
npm install
npm run build
npm run mcp:health
npm run mcp:test-compact
```

After rebuilding, keep the client command pointed at `tools/mcp-pahlawan/dist/index.js`, update the environment values from `.env.example` or the client examples, then fully restart Codex, Cursor, Claude, or Antigravity so the stdio MCP process is recreated.

Database connection failed:

- Check `MYSQL_HOST`, `MYSQL_PORT`, `MYSQL_USER`, and `MYSQL_DATABASE`.
- Keep `MYSQL_PASSWORD` in local env only.
- Use `db_find_tables` with keywords before schema overview.

Compiler not configured:

- Set `PAWN_COMPILER_PATH`.
- Set `PAWN_COMPILE_ARGS`.
- The server does not run arbitrary shell commands; only the configured compiler is allowed.
