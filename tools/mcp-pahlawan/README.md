# MCP PAHLAWAN ROLEPLAY

Local MCP server untuk membantu AI coding agent memahami project PAHLAWAN ROLEPLAY dengan aman.

Server ini bersifat project-scoped dan hanya boleh mengakses file di dalam `PROJECT_ROOT`.

## Fitur

- Discovery struktur `GAMEMODE`, `WEBSITE`, `BOT`, `DATABASE`, dan `docs`.
- Search kode Pawn, PHP, JavaScript, TypeScript, SQL, JSON, dan dokumen.
- Analisis callback Pawn, dialog, TextDraw, UCP auth, Discord interaction, dan flow fitur.
- Read file dengan path guard dan redaksi secret.
- Tool write patch/create file tersedia, tapi default mati.
- Database MySQL/MariaDB read-only.
- Compile gamemode hanya lewat compiler yang dikonfigurasi.
- Log diagnostics tanpa expose secret.
- Changelog bahasa Indonesia untuk Discord.

## Struktur Folder

```text
tools/mcp-pahlawan/
  .env.example
  README.md
  package.json
  tsconfig.json
  examples/
    codex-config.toml
    mcp-client-config.json
    prompts.md
  src/
    index.ts
    config.ts
    types.ts
    tools/
      bot.ts
      codeSearch.ts
      database.ts
      files.ts
      gamemode.ts
      index.ts
      logs.ts
      project.ts
      ucp.ts
      workflow.ts
    utils/
      compileRunner.ts
      database.ts
      fileSearch.ts
      logReader.ts
      pathSafety.ts
      redact.ts
```

## Install

Dari folder ini:

```powershell
cd "C:\Users\guyub\Documents\PAHLAWAN ROLEPLAY\tools\mcp-pahlawan"
npm install
npm run build
```

## Konfigurasi Env

Buat `.env` lokal dari `.env.example` kalau ingin menjalankan manual:

```powershell
Copy-Item .env.example .env
```

Default aman:

```env
MCP_ALLOW_WRITE_FILES=false
MCP_ALLOW_WRITE_DB=false
MCP_REDACT_SECRETS=true
```

Jangan commit `.env`.

## Menjalankan Manual

```powershell
npm run build
npm start
```

MCP server memakai STDIO, jadi saat dijalankan langsung terminal akan menunggu client MCP. Itu normal.

## Connect ke Codex

Tambahkan config ini ke project `.codex/config.toml` atau global `C:\Users\guyub\.codex\config.toml`.

Contoh project-scoped:

```toml
[mcp_servers.pahlawan_roleplay]
command = "node"
args = ["tools/mcp-pahlawan/dist/index.js"]
enabled = true
startup_timeout_sec = 30
tool_timeout_sec = 120

[mcp_servers.pahlawan_roleplay.env]
PROJECT_ROOT = "C:\\Users\\guyub\\Documents\\PAHLAWAN ROLEPLAY"
MCP_ALLOW_WRITE_FILES = "false"
MCP_ALLOW_WRITE_DB = "false"
MCP_REDACT_SECRETS = "true"
MCP_MAX_FILE_SIZE_KB = "512"
```

Setelah config ditambahkan, restart Codex atau buka thread baru. Di Codex CLI/TUI, gunakan `/mcp` untuk mengecek server aktif.

## Connect ke Cursor / Claude-style Client

```json
{
  "mcpServers": {
    "pahlawan-roleplay": {
      "command": "node",
      "args": [
        "tools/mcp-pahlawan/dist/index.js"
      ],
      "env": {
        "PROJECT_ROOT": "C:/Users/guyub/Documents/PAHLAWAN ROLEPLAY",
        "MCP_ALLOW_WRITE_FILES": "false",
        "MCP_ALLOW_WRITE_DB": "false",
        "MCP_REDACT_SECRETS": "true",
        "MCP_MAX_FILE_SIZE_KB": "512"
      }
    }
  }
}
```

Jika client dijalankan bukan dari root repo, gunakan path absolut untuk `args`:

```json
"args": [
  "C:/Users/guyub/Documents/PAHLAWAN ROLEPLAY/tools/mcp-pahlawan/dist/index.js"
]
```

## Tool Utama

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

Logs dan workflow:

- `read_recent_logs`
- `diagnose_issue`
- `generate_task_context`
- `generate_changelog`
- `health_check`

## Keamanan

- Path traversal seperti `../` diblokir.
- Akses di luar `PROJECT_ROOT` diblokir.
- Binary, build output, `.git`, `node_modules`, cache, dan file besar tidak ikut search.
- Secret direduksi dari `.env`, config, JSON, JS/TS, PHP, Pawn, SQL, dan output logs.
- Query database hanya menerima `SELECT`.
- Query multi-statement dan SQL destructive diblokir.
- Compile gamemode hanya menjalankan `PAWN_COMPILER_PATH` yang dikonfigurasi.
- File write harus memenuhi dua syarat:
  - input tool berisi `confirmWrite: true`
  - env `MCP_ALLOW_WRITE_FILES=true`
- Sebelum write patch, server membuat backup file.

## Contoh Prompt

```text
Use the Pahlawan MCP to trace the business auction system across gamemode, UCP, bot, and database. Summarize related files, functions, tables, and risks.
```

```text
Use the Pahlawan MCP to diagnose why /bizmenu does not detect nearby business. Read related Pawn code, database schema, and logs. Do not edit files yet.
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
