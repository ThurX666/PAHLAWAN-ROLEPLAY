# PAHLAWAN ROLEPLAY Agent Instructions

Project root: `C:\Users\guyub\Documents\PAHLAWAN ROLEPLAY`

## Project Structure

- `GAMEMODE` — SA-MP/open.mp Pawn source, includes, filterscripts, plugins, logs, compile output.
  - Entry: `gamemodes/main.pwn`
  - Includes: `gamemodes/core/*.inc` (account, admin, business, faction, etc.)
  - Compiler: `pawno/pawncc.exe`
- `WEBSITE` — UCP React/Vite frontend + PHP API backend.
  - Frontend: `Auth.tsx`, `App.tsx`, `components/`
  - Backend: `public/api/*.php` (auth.php, auth_session.php, api_characters.php, etc.)
  - Dev server: `npm run dev` (Vite, port 5173)
- `BOT` — Discord bot Node.js (discord.js v14, mysql2).
  - Entry: `index.js`
  - Commands: `commands/admin/`, `events/`
  - Config: `config.json`
- `DATABASE` — SQL dumps + migrations. Private.
  - Main dump: `phrp.sql` (103 tables, MariaDB 10.4.32, database `arivena`)
- `tools/mcp-pahlawan` — Local MCP server for project analysis.
- `openspec/` — OpenSpec changes and specs.

## Compile Command (Pawn)

```bash
cmd //c 'pawno\pawncc.exe gamemodes\main.pwn -ogamemodes\main.amx -ipawno\include -ipawno\pawno\include'
```

Run from `GAMEMODE` directory. Must use `cmd //c` (not direct bash) because Pawn compiler needs Windows path separators.

## Database

- Engine: MariaDB 10.4.32 (XAMPP)
- Database: `arivena`
- Tables: 103 total
- Key tables:
  - `player_ucp` — UCP accounts (26 cols, PK=ID, username=UCP, password=bcrypt $2y$12$)
  - `player_characters` — Character data (100+ cols, link via Char_UCP string)
  - `ucp_*` — UCP subsystem tables (stories, tickets, donations, etc.)
- Orphan tables (safe to drop): `ucp`, `characters`

## MCP Server (pahlawan-roleplay)

- Config v2: MySQL connected, Pawn compiler enabled, compact mode OFF, snippets ON.
- Read-only mode (`MCP_ALLOW_WRITE_FILES=false`, `MCP_ALLOW_WRITE_DB=false`).
- Use `mcp__pahlawan_roleplay__*` tools for project context, search, schema, logs, feature tracing, OpenSpec.
- MCP output is full (no compression) — 9router handles compression externally.
- For file writes, use `patch` or `write_file` tools, not MCP.

## OpenSpec

Active changes:
- `vps-pterodactyl-infrastructure` — VPS + Pterodactyl setup (8/71 tasks done)
- `cross-service-auth-flow` — Cross-service auth unification (3/54 tasks done)

Rules:
- OpenSpec is the source of truth for feature planning.
- Before coding, check `openspec_overview` + `openspec_task_status`.
- Stay within approved scope of active change.
- Do not create competing plans when OpenSpec exists.
- If no OpenSpec exists and task is medium/high risk, propose creating one first.

## Workflow Rules

- Analyze first; do not edit broad areas immediately.
- Use MCP tools before guessing project structure or flow.
- Prefer small, reviewable patches.
- Never edit everything at once.
- Never expose `.env`, tokens, passwords, Discord tokens, webhook URLs, API keys.
- Keep database operations read-only unless user explicitly approves.
- For Pawn, inspect existing includes and callbacks before adding code.
- For UCP, preserve auth flow, validation, SQL safety, session security.
- For Discord bot, respect interaction timeout, deferReply/reply/editReply rules.
- For broad sync tasks, generate mapping + migration plans before editing.

## Recommended Task Flow

1. `openspec_overview` — check active changes
2. `openspec_task_status` — find next task
3. `generate_task_context` — gather related files/functions/tables
4. `gamemode_overview` / `ucp_overview` / `bot_overview` — understand module
5. `trace_feature` — trace feature across services
6. `db_schema_overview` — check relevant tables
7. Read only necessary files (use MCP `read_project_file` with line limits)
8. Make targeted patches via `patch` tool
9. Validate (compile, test, check)
10. Commit + push after each logical chunk

## Runtime Artifacts (gitignored, never commit)

- `.playwright-cli/` — browser QA artifacts
- `GAMEMODE/logs/` — runtime logs
- `WEBSITE/node_modules/` — npm deps
- `BOT/node_modules/` — npm deps
- `*.env` — secrets
- `DATABASE/phrp.sql` — contains user data
