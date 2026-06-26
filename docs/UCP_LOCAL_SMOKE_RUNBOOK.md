# UCP Local Smoke Runbook

Use this before or after local UCP work to choose the smallest safe validation. The repository remains the source of truth; `C:\xampp\htdocs\pahlawan_roleplay` is only a runtime target.

## 1. Pick One Mode

| Mode | Use When | Minimum Checks |
| --- | --- | --- |
| Repo dev | Editing frontend or PHP source | Frontend dev server, PHP API from repo, targeted page/API check |
| Build validation | Preparing production-like frontend output | `npm run build`, no secret capture, inspect build success only |
| XAMPP runtime | Checking flattened local runtime | Build already passed, runtime target synced, browser/API smoke check |

## 2. Repo Dev Checks

Run from `WEBSITE` when iterating on source code:

1. Start frontend dev mode with `npm run dev`.
2. Start the PHP API from the repository when API behavior is touched.
3. Open the affected page and confirm it loads without console-breaking UI errors.
4. For auth/session work, verify only the flow status: login form loads, request reaches API, response is handled.
5. For email/OTP work, verify readiness or endpoint status only; never record OTP values.

Stop if source checks require private `.env` values that are missing or unclear.

## 3. Build Checks

Run before XAMPP/runtime validation:

1. Run `npm run build` from `WEBSITE`.
2. Confirm the build exits successfully.
3. Confirm the generated output exists where the existing Vite config expects it.
4. Do not copy build output to XAMPP until the build passes.

Stop if the build fails, dependencies are missing, or output location is unclear.

## 4. XAMPP Runtime Checks

Use only after the runtime target has been refreshed from repository-owned artifacts:

1. Confirm `C:\xampp\htdocs\pahlawan_roleplay` is treated as target-only.
2. Open the local runtime URL and confirm the frontend loads.
3. Check API health/readiness using a bounded endpoint or page behavior.
4. Check auth/session continuity without recording credentials, cookies, session IDs, or private rows.
5. Check email runtime readiness without recording provider detail, OTPs, or secrets.
6. If asset-related work changed, perform a bounded read-only asset list check.

Stop if the runtime appears stale, points to the wrong path, requires database writes, or exposes secrets in diagnostics.

## 5. Secret-Safe Evidence

Record only this:

| Field | Example |
| --- | --- |
| Mode | Repo dev / Build / XAMPP runtime |
| Check | Frontend load / API health / Auth flow / Email readiness |
| Target | Route, endpoint name, or module name only |
| Result | Pass / Fail / Blocked |
| Note | Short redacted note, no secrets |

Never record `.env`, tokens, passwords, Discord credentials, webhook URLs, cookies, OTPs, session values, raw provider errors, full logs, private database rows, or dump files.

## 6. Handoff Format

Use this short summary after validation:

```text
UCP smoke result:
- Mode: <Repo dev | Build | XAMPP runtime>
- Checks: <short list>
- Result: <Pass | Fail | Blocked>
- Evidence: <bounded secret-safe notes>
- Skipped: <checks skipped and why>
- Next: <fix | resync | commit | deploy-readiness review>
```
