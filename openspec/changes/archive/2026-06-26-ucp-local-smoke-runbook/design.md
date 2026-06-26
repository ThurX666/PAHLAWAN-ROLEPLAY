## Context

The repository already distinguishes source-of-truth development from flattened XAMPP runtime validation. The runbook should make those modes easy to execute without copying secrets, dumping private data, or treating XAMPP as source.

## Goals / Non-Goals

**Goals:**
- Provide a short checklist for repo development, build validation, and XAMPP smoke validation.
- Make allowed evidence and stop conditions explicit.
- Keep the runbook aligned with existing UCP local workflow and production deployment specs.

**Non-Goals:**
- Do not automate runtime sync.
- Do not add npm, PHP, Composer, database, or CI dependencies.
- Do not read or write `.env`, private dumps, cookies, OTPs, or credentials.

## Decisions

- Use a single markdown runbook instead of scripts; this avoids encoding local paths, secrets, and operator-specific XAMPP state.
- Keep checks mode-based rather than feature-based; operators choose repo, build, or XAMPP mode first.
- Record pass/fail evidence only; no screenshots or logs are required unless a failure needs bounded redacted evidence.

## Risks / Trade-offs

- Manual checks can be skipped → The runbook includes stop conditions and a small evidence table.
- XAMPP state can drift → The runbook treats XAMPP only as runtime target and requires reset/resync when stale.
- Diagnostics can leak secrets → The runbook bans secret, OTP, cookie, token, and full-log capture.
