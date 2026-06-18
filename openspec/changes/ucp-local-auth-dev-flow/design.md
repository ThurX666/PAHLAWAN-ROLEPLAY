## Context

The repository already separates the UCP frontend source in `WEBSITE` and the PHP API runtime under `WEBSITE/public/api`, and the user has provided the intended local runtime endpoints: `http://localhost:3000/` for the frontend and `http://127.0.0.1:8000/api` for the PHP API. Existing example env files already distinguish local and production values, and local OTP preview is only acceptable when `APP_ENV=local` and `UCP_LOCAL_MAIL_MODE=preview`. This change is planning-only and must not alter API logic, auth logic, production OTP delivery, gamemode code, schema, migrations, or the external XAMPP deployment tree.

## Goals / Non-Goals

**Goals:**
- Define one approved local UCP workflow that developers can follow without mixing local and production configuration.
- Preserve the current production expectation that OTP is delivered through real SMTP and is never exposed through a preview channel.
- Document the local login/session verification flow, including OTP preview preconditions and post-login asset smoke-test targets.
- Establish the environment and documentation constraints that any later implementation or docs patch must satisfy.

**Non-Goals:**
- Changing PHP API behavior, frontend auth flow, session logic, OTP generation, or OTP validation.
- Relaxing any production auth or mail-delivery control.
- Editing `C:\\xampp\\htdocs\\pahlawan_roleplay`, modifying gamemode/Pawn, or changing database schema or migrations.
- Committing real secrets or requiring committed `.env` files.

## Decisions

- Model this as a new OpenSpec capability instead of modifying an existing asset-list capability, because the change governs operational workflow and environment boundaries rather than list-response behavior.
- Treat local and production as explicitly separate operating modes. The spec will require concrete local values for development and separate production expectations so later docs or examples cannot blur them.
- Pin the local commands to the repo-root workflow already implied by the project: run the frontend from `WEBSITE` with `npm run dev -- --host 0.0.0.0 --port 3000`, and run the PHP API from repo root with `php -S 127.0.0.1:8000 -t WEBSITE/public`. This matches the current Vite port and the user-provided local API URL.
- Keep OTP preview as a local-only diagnostic behavior guarded by both environment conditions, rather than a generic development convenience. This preserves the security boundary the user described and prevents any requirement that could normalize OTP exposure outside local development.
- Define the manual verification flow in terms of commands, env prerequisites, login/session checks, and bounded post-login URLs instead of implementation details. That keeps the change reviewable now and leaves runtime code untouched.
- Pin the local env expectations to placeholder-safe values already reflected by example files: `VITE_API_BASE_URL=api`, `VITE_DEV_API_PROXY_TARGET=http://127.0.0.1:8000`, `APP_ENV=local`, `UCP_ALLOWED_ORIGINS=http://localhost:3000,http://127.0.0.1:3000`, and `UCP_LOCAL_MAIL_MODE=preview` only when OTP preview is intentionally being tested.
- Limit future docs/env-example work to examples only, with no committed private values. The planning artifacts should explicitly require placeholder-only examples and a warning against committing secrets.

## Risks / Trade-offs

- [Developers reuse local env values in production] -> The spec will require distinct production expectations, real SMTP delivery, and an explicit no-secret-commit warning.
- [OTP preview behavior is misread as acceptable outside local] -> The spec will require both `APP_ENV=local` and `UCP_LOCAL_MAIL_MODE=preview` before preview is considered valid.
- [Manual smoke testing drifts from the runtime actually used by developers] -> The spec will pin the local frontend URL, local API URL, and the post-login asset smoke-test URLs.
- [Future implementation expands into auth or API changes] -> The tasks will keep work scoped to docs/examples/spec alignment first and separate any later code work into a follow-up implementation change.
