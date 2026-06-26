# Agent-Assisted Project Workflow

Use this checklist before asking an agent to change PAHLAWAN ROLEPLAY. It keeps work fast, reviewable, and safe around secrets, database data, runtime folders, Pawn callbacks, UCP auth, and Discord interactions.

## 1. Choose the Work Path

- Use the direct-fix path only for trivial, low-risk edits that do not touch secrets, database state, deployment, auth/session, runtime sync, cross-module behavior, Discord interaction timing, or Pawn callback flow.
- Use OpenSpec first for medium/high-risk work, broad sync work, deployment work, database-related work, auth/session work, BOT command behavior, or GAMEMODE systems.
- If an active OpenSpec change exists, implement only inside that approved scope before creating another plan.
- If no active OpenSpec change exists and risk is medium/high, propose a new change before editing files.

## 2. Inspect with MCP First

- Start with compact MCP context for project overview, feature tracing, logs, schema, diagnostics, or callback flow before guessing structure.
- Keep database usage read-only unless a migration/write is explicitly approved.
- Prefer bounded summaries, symbols, file paths, line numbers, and small snippets.
- Do not dump `.env`, tokens, Discord credentials, webhook URLs, API keys, OTPs, cookies, private database dumps, or full logs.

## 3. Validate the Touched Surface

- OpenSpec/docs only: validate the OpenSpec change and inspect the changed documentation.
- GAMEMODE/Pawn: inspect related callbacks/includes first, then run the configured Pawn compile check when available.
- WEBSITE/UCP: use the smallest relevant check: targeted build, API health, auth/session flow, or browser smoke check.
- BOT: verify command/event flow and Discord reply/defer/editReply timing before handoff.
- DATABASE: use schema/read-only evidence and produce a migration/rollback plan before any approved write.
- GitHub handoff: summarize changed files, validation, skipped checks, and risks before commit, push, or PR.

## 4. Security Gate

Run a focused security review before handoff when a change touches:

- Authentication, sessions, authorization, OTP, email runtime, or password flows.
- SQL, migrations, database access, imports, exports, or admin-only data.
- File uploads, filesystem paths, deployment packages, `.env` handling, or runtime sync.
- Discord commands/interactions, webhook handling, role permissions, or bot tokens.
- AI provider calls, prompt inputs, API keys, model routing, or external service integrations.

## 5. Secret-Safe Evidence

Good evidence includes:

- Command/check name, pass/fail status, affected route/path/module, and timestamp when useful.
- Browser smoke result without cookies, session values, OTPs, credentials, or private user data.
- Read-only database result counts or schema names, not full private rows.
- Log excerpts only when redacted and bounded to the issue.

Never record secrets, tokens, passwords, webhook URLs, OTPs, cookies, full `.env`, full database dumps, or broad runtime logs.

## 6. Handoff Checklist

Before final handoff, report:

- Changed files and why each changed.
- Validation completed and exact skipped checks.
- Security review status when trust boundaries were touched.
- Database/runtime impact: `none`, `read-only`, or `approved write/migration`.
- Next recommended action: archive OpenSpec, run smoke test, commit, push, open PR, or deploy.
