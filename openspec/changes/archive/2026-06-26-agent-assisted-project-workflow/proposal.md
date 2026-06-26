## Why

PAHLAWAN ROLEPLAY now uses OpenSpec, MCP diagnostics, Codex skills, browser checks, and GitHub helpers, but the daily order of use is not yet captured as a single safe workflow. A small workflow capability will make future feature work faster while preserving the project's secret, database, runtime, Pawn, UCP, and bot safety rules.

## What Changes

- Define a daily agent-assisted workflow for choosing OpenSpec, MCP, security review, browser smoke checks, and GitHub handoff steps.
- Define when work may proceed directly, when a new OpenSpec change is required, and when to stop for confirmation.
- Define bounded validation evidence for UCP/browser checks without exposing secrets, database dumps, cookies, OTPs, or tokens.
- Define a plugin/skill usage policy that favors installed trusted skills and avoids write-capable external integrations unless explicitly approved.

## Capabilities

### New Capabilities
- `agent-assisted-project-workflow`: Covers the safe daily workflow for agent-assisted planning, implementation, validation, review, and handoff across PAHLAWAN ROLEPLAY.

### Modified Capabilities

## Impact

- Affects workflow documentation and future task sequencing only.
- Does not change GAMEMODE, WEBSITE, BOT, DATABASE, runtime files, schemas, secrets, or deployment behavior.
- Uses existing installed skills and MCP tools; no new dependencies or services are required.
