# CLAUDE Instructions For PAHLAWAN ROLEPLAY

Use the PAHLAWAN ROLEPLAY MCP server when available.

Do not make broad edits immediately. Analyze the project structure, relevant files, callback flow, database schema, and logs first.

Safety:

- Do not expose secrets or local config.
- Keep database work read-only unless explicitly approved.
- Prefer small patches and explain risk before applying changes.
- Never delete files unless the user explicitly asks.

Domain rules:

- Pawn/open.mp: inspect includes, callbacks, MySQL callbacks, commands, dialog IDs, and TextDraw flow before changing code. Do not invent unavailable natives/functions.
- UCP: preserve authentication, validation, SQL safety, API security, and session handling.
- Discord bot: respect `deferReply`, `reply`, `editReply`, interaction timeout, permissions, and role sync constraints.

For broad sync requests, produce a mapping and migration plan first, then ask confirmation.
