# Local Tooling Health Checklist

Last checked: 2026-06-26

## Status

| Area | Status | Notes |
| --- | --- | --- |
| Project root | OK | `PROJECT_ROOT` points to this repository. |
| MCP mode | OK | Read-only defaults are active. |
| Secret redaction | OK | `MCP_REDACT_SECRETS=true`. |
| File writes via MCP | OK | Disabled by default. |
| Database writes via MCP | OK | Disabled by default. |
| UCP frontend build | OK | `npm run build` passed from `WEBSITE`. |
| UCP PHP standalone contracts | OK | Safe standalone contract tests passed with XAMPP PHP. |
| UCP preview smoke | OK | Local Vite preview returned HTTP 200 for `/` and main JS asset. |
| MySQL MCP connection | Not configured | Keep disabled until a read-only local DB user is intentionally configured. |
| Pawn compiler MCP | Not configured | Configure only when ready to run repeatable GAMEMODE compile checks. |

## Recommended Next Setup

1. Configure Pawn compiler path for MCP so GAMEMODE changes can be validated repeatably.
2. Configure a read-only MySQL user for MCP only if DB-backed diagnostics are needed.
3. Keep MCP write flags disabled for normal work.
4. Run XAMPP runtime smoke only after syncing `C:\xampp\htdocs\pahlawan_roleplay` from repository-owned artifacts.

## Safe Defaults

- Do not expose `.env`, tokens, Discord credentials, webhook URLs, OTPs, cookies, or private database dumps.
- Do not run database writes or migrations without explicit approval.
- Do not treat XAMPP runtime as source of truth.
