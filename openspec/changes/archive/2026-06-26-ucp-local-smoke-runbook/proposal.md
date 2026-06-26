## Why

Existing UCP workflow specs define local development, XAMPP runtime validation, and secret-safe smoke checks, but operators still need one practical checklist they can follow before/after local sync. This change turns the approved workflow into a compact runbook without changing application behavior.

## What Changes

- Add a docs-only local UCP smoke runbook for repo mode, production-build mode, and flattened XAMPP mode.
- Define secret-safe evidence to record after each check.
- Define stop conditions that prevent accidental secret exposure, stale runtime validation, or database writes.
- Keep runtime sync, DB writes, credentials, and deployment changes out of scope.

## Capabilities

### New Capabilities
- `ucp-local-smoke-runbook`: Covers the practical checklist for local UCP smoke validation across repo, build, and XAMPP runtime modes.

### Modified Capabilities

## Impact

- Adds documentation and OpenSpec artifacts only.
- Does not modify WEBSITE code, XAMPP runtime files, database state, BOT, GAMEMODE, secrets, or package dependencies.
