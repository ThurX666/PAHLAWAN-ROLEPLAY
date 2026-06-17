# Example Prompts

```text
Use the Pahlawan MCP to trace the business auction system across gamemode, UCP, bot, and database. Summarize related files, functions, tables, and risks.
```

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

```text
Use the Pahlawan MCP to inspect the Discord bot interaction flow and find why Unknown interaction happens. Focus on deferReply, reply, editReply, and command execution time.
```

```text
Use the Pahlawan MCP to generate a safe implementation plan for UCP character dashboard connected to the existing database.
```

```text
Use the Pahlawan MCP to compile the gamemode and parse errors. Suggest the smallest safe patch.
```

```text
Use Pahlawan MCP to trace feature: business auction.

Compact mode only.
No full file reads.
No database writes.
Return a compact context pack first.
After I approve, suggest a small patch.
```
