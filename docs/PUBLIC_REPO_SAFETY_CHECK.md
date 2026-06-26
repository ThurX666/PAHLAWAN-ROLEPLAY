# Public Repo Safety Check

Last checked: 2026-06-26

## Result

| Check | Result | Notes |
| --- | --- | --- |
| Secret/runtime ignore rules | OK | `.gitignore` blocks `.env`, bot config, DB dumps, XAMPP/build output, Pawn runtime binaries, logs, and uploads. |
| Tracked sensitive runtime files | OK | No tracked live `.env`, bot config, DB dump, `server.cfg`, runtime log, upload, or `.amx` output found. |
| Allowed tracked DB files | OK | `DATABASE/.gitkeep` and migration SQL are allowed. |
| Allowed tracked env docs | OK | `WEBSITE/.env.local.example` and `WEBSITE/.env.production.example` are examples only. |
| OpenSpec state | OK | No active change; main specs validate. |

## Checked Patterns

- `WEBSITE/.env`, `WEBSITE/.env.*`
- `BOT/config.json`, `BOT/config/*.json`, `BOT/PHRP-AI/config/*.json`
- `DATABASE/*` except `.gitkeep` and migrations
- `GAMEMODE/server.cfg`, logs, `.amx`, binaries, plugins, and compiler artifacts
- `WEBSITE/dist`, runtime logs, uploads, and migration markers

## Keep Before Public Push

- Run `git status --short --untracked-files=all`.
- Run a quick changed-file secret scan.
- Do not stage private runtime/config files even if they are useful locally.
- Keep database changes limited to reviewed migrations or dummy fixtures.
