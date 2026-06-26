# PAHLAWAN ROLEPLAY Agent Instructions

Project structure:

- `GAMEMODE` contains SA-MP/open.mp Pawn source, includes, filterscripts, runtime config, plugins, logs, and compile output.
- `WEBSITE` contains the UCP React/Vite frontend and PHP API backend.
- `BOT` contains the Discord bot Node.js project.
- `DATABASE` contains local database dumps and must remain private.
- `tools/mcp-pahlawan` contains the local MCP server for safe project analysis.

Hermes-specific MCP setup (registered as `pahlawan-roleplay`):

- Use the `mcp__pahlawan_roleplay__*` tools for project context, search, schema,
  logs, feature tracing, and OpenSpec inspection. They are safer and faster
  than running generic `search_files` / `read_file` / `terminal` against the
  full repo because they honor `MCP_MAX_OUTPUT_CHARS`, redaction, and
  per-module scoping.
- Before coding any feature, run `mcp__pahlawan_roleplay__openspec_overview`
  and `mcp__pahlawan_roleplay__openspec_task_status` for any related active
  change. If one exists, read it first and stay inside its approved scope.
- For broad tasks, follow the recommended flow below instead of scanning the
  whole repo. Each tool already enforces compact mode by default.
- The MCP server is read-only (`MCP_DEFAULT_MODE=readonly`,
  `MCP_ALLOW_WRITE_FILES=false`, `MCP_ALLOW_WRITE_DB=false`). Do not ask it to
  mutate files or the database — use the file/terminal tools and get explicit
  user approval before any write.

Runtime artifacts to ignore:

- `.playwright-cli/` (browser CLI tool QA artifacts) is already gitignored at
  both the root and `WEBSITE/` levels. Never commit its contents.

Workflow rules:

- OpenSpec is the source of truth for feature planning and requirements.
- MCP is the context, diagnostics, search, database/log/code inspection, and validation support layer.
- Before coding, always check active OpenSpec changes.
- If an OpenSpec change exists, read it first and implement only within its approved scope.
- Do not create a competing plan when OpenSpec already exists.
- If no OpenSpec exists and the task is medium/high risk, propose creating one first.
- Analyze first; do not edit broad areas immediately.
- Use MCP tools before guessing project structure or flow.
- Prefer small, reviewable patches.
- Never edit everything at once.
- Never expose `.env`, tokens, database passwords, Discord tokens, webhook URLs, API keys, or private dumps.
- Keep database operations read-only unless the user explicitly approves a migration/write.
- For Pawn/open.mp, inspect existing includes and callbacks before adding code. Do not invent natives or functions.
- For Discord bot work, respect interaction timeout, `deferReply`, `reply`, `editReply`, and double-reply rules.
- For UCP work, preserve auth flow, validation, SQL safety, and session security.
- For broad sync tasks, generate mapping and migration plans before editing.

Recommended broad-task flow:

1. Run `generate_task_context`.
2. Run `gamemode_overview`.
3. Run `ucp_overview`.
4. Run `db_schema_overview`.
5. Run `trace_feature` for each relevant feature.
6. Produce a database-feature mapping table.
7. Detect mismatches across gamemode, UCP, bot, and database.
8. Generate a migration/adapter plan.
9. Ask for confirmation before writing files.
10. Apply changes feature-by-feature.

MCP context rules:

- Never scan the entire project by default.
- Never dump full files, the full database schema, or full logs by default.
- Work feature-by-feature with compact mode enabled.
- Prefer summaries, paths, symbols, line numbers, and small snippets.
- Ask before reading large files or applying patches.
- Use pagination for large results.
- Keep every tool response under `MCP_MAX_OUTPUT_CHARS`.
- Do not delete files, run migrations, or write database data without explicit approval.
