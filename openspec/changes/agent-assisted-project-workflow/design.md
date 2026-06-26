## Context

PAHLAWAN ROLEPLAY has project rules in `AGENTS.md`, OpenSpec as the planning source of truth, a local MCP server for bounded project inspection, and newly installed Codex skills for security and GitHub workflows. The missing piece is a single daily workflow that tells the agent and operator which tool class to use first, when to stop, and what evidence is safe to keep.

## Goals / Non-Goals

**Goals:**
- Make OpenSpec-first work sequencing explicit for medium/high-risk work.
- Keep MCP usage bounded, compact, and read-only for database/log inspection unless explicitly approved.
- Add security, browser smoke, and GitHub handoff gates to the normal workflow.
- Keep generated evidence secret-safe and small enough for review.

**Non-Goals:**
- Do not change application behavior, runtime files, database schemas, deploy targets, or secrets.
- Do not add new plugins, services, package dependencies, or CI jobs in this change.
- Do not replace existing OpenSpec specs for UCP deployment, local workflow, auth, email OTP, assets, or AI provider behavior.

## Decisions

- Use OpenSpec as the first workflow gate for medium/high-risk changes; direct edits remain acceptable only for trivial, low-risk fixes. Alternative considered: rely on ad-hoc chat planning, rejected because project rules already make OpenSpec authoritative.
- Use MCP as the first inspection layer for project, DB, logs, and feature tracing; shell reads are reserved for bounded OpenSpec/docs edits or when MCP lacks coverage. Alternative considered: broad filesystem scanning, rejected because it risks noise and secret exposure.
- Use installed security skills before deployment-facing UCP/BOT changes, not on every tiny typo fix. Alternative considered: mandatory security review for every task, rejected because it slows low-risk work.
- Use browser smoke checks only when UI/runtime behavior changes or a runbook requires evidence. Alternative considered: always run browser automation, rejected because many workflow/doc changes have no UI surface.
- Use GitHub handoff skills only after local scope is clear and changes are ready for review. Alternative considered: push early by default, rejected because OpenSpec and local validation should come first.

## Risks / Trade-offs

- Workflow becomes too heavy for tiny fixes → Keep direct low-risk path explicit.
- Security checks produce broad recommendations → Tie them to touched modules and trust boundaries only.
- Smoke evidence leaks sensitive data → Record status, route/path, timestamps, and pass/fail only.
- External plugins increase supply-chain risk → Prefer installed trusted skills and require approval before adding new write-capable integrations.
