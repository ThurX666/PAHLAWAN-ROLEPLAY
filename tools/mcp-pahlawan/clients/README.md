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

## Configuration (v2 — Max Performance)

Config v2 dirancang untuk **maximal output tanpa kompresi MCP**. Kompresi ditangani oleh 9router compression tools, jadi MCP harus output full.

### Yang ditambahkan dari v1:

| Group | Env Var | Value | Alasan |
|-------|---------|-------|--------|
| **MySQL** | `MYSQL_HOST` | `127.0.0.1` | Enable `db_schema_overview`, `db_safe_query`, `db_find_tables` |
| | `MYSQL_USER` | `root` | XAMPP default |
| | `MYSQL_DATABASE` | `arivena` | Database PAHLAWAN |
| **Pawn** | `PAWN_COMPILER_PATH` | `GAMEMODE/pawno/pawncc.exe` | Enable `compile_gamemode` |
| | `PAWN_COMPILE_ARGS` | `gamemodes/main.pwn -ogamemodes/main.amx -ipawno/include -ipawno/pawno/include` | Compile args |
| **Limits** | `MCP_MAX_OUTPUT_CHARS` | `100000` | 12.5x dari default 8000 |
| | `MCP_MAX_FILE_READ_LINES` | `1000` | 8x dari default 120 |
| | `MCP_MAX_SEARCH_RESULTS` | `50` | 5x dari default 10 |
| | `MCP_MAX_DB_ROWS` | `100` | 5x dari default 20 |
| | `MCP_MAX_SCHEMA_TABLES` | `103` | Cover semua tabel di `arivena` |
| | `MCP_MAX_FILE_SIZE_KB` | `8192` | 16x dari default 512 |
| | `MCP_MAX_LOG_LINES` | `500` | 6x dari default 80 |
| | `MCP_MAX_SNIPPET_LINES` | `30` | 6x dari default 5 |
| | `MCP_MAX_FEATURE_FILES` | `50` | 2x dari default 25 |
| **Output** | `MCP_COMPACT_MODE` | `false` | No compression — 9router handles it |
| | `MCP_DEFAULT_INCLUDE_SNIPPETS` | `true` | Always include code snippets |

### Safety (tidak berubah):

```env
MCP_ALLOW_WRITE_FILES=false
MCP_ALLOW_WRITE_DB=false
MCP_REDACT_SECRETS=true
MCP_DEFAULT_MODE=readonly
```

## Client Config Files

| Client | File | Format |
|--------|------|--------|
| Generic | `examples/mcp-client-config.json` | JSON |
| Claude Desktop / Claude Code | `clients/claude/mcp.example.json` | JSON |
| Cursor | `clients/cursor/mcp.example.json` | JSON |
| Google Antigravity | `clients/antigravity/mcp.example.json` | JSON |
| OpenAI Codex | `clients/codex/config.example.toml` | TOML |

## Codex

Use `clients/codex/config.example.toml`.

Place it in project `.codex/config.toml` only when this project is trusted, or copy the server block to `C:\Users\guyub\.codex\config.toml`.

## Cursor

Use `clients/cursor/mcp.example.json`.

Cursor may support global or project-level MCP configuration. Use absolute Windows path if Cursor is not launched from the repo root.

## Claude

Use `clients/claude/mcp.example.json`.

Claude Desktop and Claude Code use MCP JSON-style server definitions.

## Google Antigravity

Use `clients/antigravity/mcp.example.json`.

Use stdio transport if supported.

## Recommended Workflow

For broad requests like syncing website database features with the gamemode:

1. `generate_task_context`
2. `gamemode_overview`
3. `ucp_overview`
4. `db_schema_overview`
5. `trace_feature` per detected feature
6. produce a mapping table and mismatch report
7. generate migration/adapter plan
8. ask for confirmation before writes
9. apply changes feature-by-feature
