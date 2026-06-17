# PAHLAWAN ROLEPLAY Codex Notes

Use the `pahlawan-roleplay` MCP server when available for project discovery, code search, diagnostics, and safe context generation.

Default workflow:

- Analyze first.
- Use MCP tools before guessing.
- Prefer small patches.
- Keep DB read-only unless explicitly approved.
- Never expose secrets.
- Do not edit broad project areas in one pass.

Project modules:

- `GAMEMODE`: Pawn/open.mp source and runtime.
- `WEBSITE`: UCP React/Vite and PHP API.
- `BOT`: Discord bot Node.js.
- `DATABASE`: private local database dumps.
- `tools/mcp-pahlawan`: MCP tooling.

Domain rules:

- Pawn/open.mp: inspect includes and callbacks first; do not invent natives/functions.
- Discord bot: respect interaction timeout and defer/reply flow.
- UCP: preserve auth, validation, SQL safety, and session security.

For requests like "Synchronize the website database with the gamemode for all features", run:

1. `generate_task_context`
2. `gamemode_overview`
3. `ucp_overview`
4. `db_schema_overview`
5. `trace_feature` per feature
6. mapping and mismatch report
7. migration/adapter plan
8. ask confirmation before writes

MCP anti-overflow rules:

- Never scan the entire project by default.
- Never dump full files, full database schema, or full logs by default.
- Work feature-by-feature with compact mode enabled.
- Prefer summaries, paths, symbols, line numbers, and small snippets.
- Ask before reading large files or applying patches.
- Use pagination and keep output under `MCP_MAX_OUTPUT_CHARS`.
