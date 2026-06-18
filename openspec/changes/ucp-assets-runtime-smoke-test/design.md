## Context

The repository already has a main spec for `ucp-asset-lists`, but this task is limited to verifying the local runtime path and smoke testing the existing read-only endpoints before any feature edits. The main uncertainty is whether failures come from XAMPP or web-root mapping versus real application code.

## Goals / Non-Goals

**Goals:**
- Identify the local URL that correctly serves `WEBSITE/public`.
- Exercise the three asset endpoints through the runtime, not by reading code alone.
- Distinguish environment-level 404s from confirmed endpoint defects.
- Preserve a clear approval gate before any patching.

**Non-Goals:**
- Editing PHP, frontend, gamemode, bot, or database code.
- Changing schema, migrations, or runtime configuration.
- Expanding the test scope beyond the three requested endpoints.

## Decisions

- Validate the runtime from the deployed local web root instead of assuming the Vite or source directory path. This is the only way to confirm the user-facing URL.
- Treat HTTP 404 as an environment diagnosis problem first. The requested workflow explicitly limits 404 handling to XAMPP or web-root path checks.
- Use read-only HTTP requests against `api_overview.php?action=assets&type=<type>` and capture status plus compact response evidence.
- If an endpoint resolves but fails with an application error, stop at reporting and request approval before any code patch.

## Risks / Trade-offs

- [Local runtime differs from source layout] -> Verify actual XAMPP document root and served path before interpreting endpoint failures.
- [Endpoint requires auth or local dependencies] -> Record the response as part of the smoke test and avoid speculative fixes.
- [Operational change tracked as a new capability] -> Keep the spec narrowly scoped to verification behavior so it remains reviewable and does not overlap implementation changes.
