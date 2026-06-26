# PAHLAWAN ROLEPLAY Docs Index

Use this index to pick the right project guide without reading every document.

## Start Here

| Need | Open |
| --- | --- |
| Decide how an agent should work safely | [Agent-Assisted Workflow](AGENT_ASSISTED_WORKFLOW.md) |
| Pick the smallest safe validation | [Local Validation Matrix](LOCAL_VALIDATION_MATRIX.md) |
| Check local tool readiness | [Local Tooling Health](LOCAL_TOOLING_HEALTH.md) |
| Understand the project layout | [Project Overview](PROJECT_OVERVIEW.md) |
| Follow general development rules | [Development](DEVELOPMENT.md) |

## Area Guides

| Area | Guide | Use When |
| --- | --- | --- |
| UCP / Website | [UCP Local Smoke Runbook](UCP_LOCAL_SMOKE_RUNBOOK.md) | Validating repo, build, or XAMPP-mode UCP work |
| BOT | [Bot Health Checklist](BOT_HEALTH_CHECKLIST.md) | Checking Discord bot syntax and interaction safety |
| GAMEMODE | [Gamemode Health Checklist](GAMEMODE_HEALTH_CHECKLIST.md) | Running safe Pawn compile validation |
| DATABASE | [Database Policy](DATABASE_POLICY.md) | Planning DB-related work without unsafe writes |
| Secrets | [Secret Rotation Playbook](SECRET_ROTATION_PLAYBOOK.md) | Handling possible secret exposure or rotation |
| Public safety | [Public Repo Safety Check](PUBLIC_REPO_SAFETY_CHECK.md) | Checking ignore rules before public push |
| Licensing | [Subproject License Policy](../SUBPROJECT_LICENSES.md) | Checking folder-level license scope and exclusions |

## Default Safe Workflow

1. Check OpenSpec active changes first.
2. Use MCP for bounded project context before guessing file flow.
3. Choose the smallest validation from the local matrix.
4. Keep DB operations read-only unless a write/migration is explicitly approved.
5. Record only secret-safe evidence.
6. Summarize changed files, validation, skipped checks, and risks before handoff.

## Do Not Record

Never record `.env`, tokens, passwords, Discord credentials, webhook URLs, OTPs, cookies, session values, private database rows, full dumps, or full runtime logs.
