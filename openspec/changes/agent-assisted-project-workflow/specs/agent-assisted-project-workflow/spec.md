## ADDED Requirements

### Requirement: Work starts with the correct planning gate
The agent-assisted workflow SHALL check active OpenSpec changes before implementation, SHALL follow an active approved change when one exists, and SHALL propose a new OpenSpec change before medium-risk or high-risk work when no active change exists.

#### Scenario: Active OpenSpec change exists
- **WHEN** the operator asks for implementation work and an active OpenSpec change exists
- **THEN** the workflow uses that change as the implementation scope before editing project files

#### Scenario: No active OpenSpec change for risky work
- **WHEN** the operator asks for medium-risk or high-risk work and no active OpenSpec change exists
- **THEN** the workflow creates or proposes an OpenSpec change before implementation begins

#### Scenario: Low-risk direct fix
- **WHEN** the operator asks for a trivial low-risk fix that does not affect secrets, database state, deployment, auth, payment, runtime sync, or cross-module behavior
- **THEN** the workflow may proceed directly after bounded inspection

### Requirement: MCP inspection remains bounded and secret-safe
The agent-assisted workflow SHALL use the PAHLAWAN MCP tools for project overview, feature tracing, logs, database schema, and diagnostics before guessing structure, and SHALL keep database operations read-only unless the operator explicitly approves a write or migration.

#### Scenario: Feature work needs project context
- **WHEN** feature work touches GAMEMODE, WEBSITE, BOT, DATABASE, or multiple modules
- **THEN** the workflow gathers bounded MCP context before choosing files to inspect or edit

#### Scenario: Database context is needed
- **WHEN** a task needs database evidence
- **THEN** the workflow uses read-only schema or SELECT diagnostics and does not expose secrets, private dumps, tokens, passwords, OTPs, cookies, or full table dumps

### Requirement: Validation matches the touched surface
The agent-assisted workflow SHALL choose the smallest useful validation for the changed surface, including Pawn compile checks for GAMEMODE, targeted UCP build or browser smoke checks for WEBSITE, bot command or interaction checks for BOT, and OpenSpec validation for planning-only changes.

#### Scenario: UCP runtime behavior changes
- **WHEN** a change affects UCP frontend, PHP API, auth/session, email runtime, or deployment behavior
- **THEN** the workflow records bounded build or smoke evidence without capturing secrets or private session values

#### Scenario: Planning-only change
- **WHEN** a change only updates OpenSpec or workflow documentation
- **THEN** the workflow validates OpenSpec readiness and does not run unrelated app/runtime checks

### Requirement: Security review is required at trust boundaries
The agent-assisted workflow SHALL use installed security review skills or equivalent checks before handing off changes that affect authentication, sessions, authorization, SQL, file uploads, Discord interactions, deployment, environment handling, or AI provider calls.

#### Scenario: Trust boundary changes
- **WHEN** a change modifies a trust boundary or secret-handling path
- **THEN** the workflow performs a focused security review before GitHub handoff or deployment recommendation

### Requirement: GitHub handoff is review-ready
The agent-assisted workflow SHALL use GitHub handoff skills only after scope, changed files, validation evidence, and known skipped checks are summarized, and SHALL avoid committing secrets, runtime-only files, database dumps, or broad unrelated changes.

#### Scenario: Work is ready for review
- **WHEN** implementation and validation are complete
- **THEN** the workflow summarizes changed files, validation, skipped checks, and risks before any commit, push, or pull request action
