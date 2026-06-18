# WEBSITE Local and Production Workflow

This directory contains the UCP frontend and the PHP API document root used for local development.

## Do Not Commit Secrets

`WEBSITE/.env` is local or deployment-only runtime state. Do not commit `.env` files or any secret-bearing values such as SMTP credentials, API keys, cookies, OTPs, or private database passwords.

The PHP configuration bootstrap supports both repository layout `WEBSITE/public/api` and a flattened deployment layout `<deployment-root>/api`. The environment file is always resolved from the Website runtime root: `WEBSITE/.env` in the repository and `<deployment-root>/.env` in a flattened deployment such as `C:\xampp\htdocs\pahlawan_roleplay\.env`. It does not fall back to `C:\xampp\htdocs\.env`. Process-level environment variables take priority over file values, including explicitly blank values used to fail closed.

Use only the example files in this directory as templates:
- `.env.local.example`
- `.env.production.example`
- `env.example`

## Local Development

Prerequisites:
- Node.js and npm
- PHP available on your shell path

Local runtime targets:
- Frontend: `http://localhost:3000/`
- PHP API: `http://127.0.0.1:8000/api`

Setup:
1. From `WEBSITE`, install dependencies with `npm install`.
2. Copy `.env.local.example` to `.env` and fill only local/private values.
3. Start the PHP API from the repo root:

```powershell
php -S 127.0.0.1:8000 -t WEBSITE/public
```

4. Start the frontend from `WEBSITE`:

```powershell
npm run dev -- --host 0.0.0.0 --port 3000
```

Required local env values:
- `VITE_API_BASE_URL=api`
- `VITE_DEV_API_PROXY_TARGET=http://127.0.0.1:8000`
- `APP_ENV=local`
- `UCP_LOCAL_MAIL_MODE=preview`
- `UCP_ALLOWED_ORIGINS=http://localhost:3000,http://127.0.0.1:3000,http://localhost:5173,http://127.0.0.1:5173`

During pre-launch development, local UCP testing may use the currently configured real development database `arivena`. Treat it as development data: avoid destructive operations unless they are explicitly approved and backed up. After production launch, create a separate local/dev database. Production player data must never be reused for destructive tests, resets, fixtures, migration experiments, or failure simulations.

Local OTP preview rule:
- OTP preview is allowed only when `APP_ENV=local` and `UCP_LOCAL_MAIL_MODE=preview`.
- If you are not intentionally testing local OTP preview, switch to a non-preview local mode before testing other mail behavior.

## Production Expectations

Production must remain separate from local development:
- `APP_ENV=production`
- `UCP_LOCAL_MAIL_MODE=smtp`
- `VITE_API_BASE_URL` must point to the published API URL
- `UCP_ALLOWED_ORIGINS` must be the published frontend origin
- Real SMTP is required for OTP delivery
- OTP preview must never be enabled or exposed in production

Use `.env.production.example` only as a placeholder template. Fill real deployment values outside the repository.

## Story Review NVIDIA NIM

The Website/UCP backend contains a server-only NVIDIA NIM adapter compatible with `sendMessage(messages, options)`. Its defaults match Discord Bot/PHRP-AI:

- provider: `nvidia`
- base URL: `https://integrate.api.nvidia.com/v1`
- model: `deepseek-ai/deepseek-v4-flash`

The approved local and production environment templates set both `AI_ENABLED=true` and `AI_STORY_REVIEW_ENABLED=true`. Local production-like testing may use real NVIDIA NIM. Provider traffic runs only when the private runtime also has a valid server-side key and approved provider/model/base URL configuration. A missing or invalid credential, missing/unapproved model, unapproved HTTPS base URL, or invalid provider response fails closed before a partial AI review is persisted.

`NVIDIA_NIM_API_KEY` must be injected only into the PHP server environment or private `WEBSITE/.env`. Never expose provider credentials, models, or endpoints as browser-controlled values and never use a `VITE_` prefix for AI secrets. Overrides must also be listed in `AI_ALLOWED_MODELS` or `AI_ALLOWED_BASE_URLS`.

Story Review sends only the selected database-loaded story text and trusted rubric instructions to the provider. Plagiarism matches, account/reviewer data, IDs, cookies, sessions, and secrets remain local.

The server contract accepts ordered `{ role, content }` messages and bounded options named `task`, `model`, `maxTokens`, `temperature`, and `responseFormat`. Cross-provider fallback remains disabled through `AI_FALLBACK_ENABLED=false`. Rate limits, privacy-aware logs, strict response validation, immutable review history, and manual approval authority remain mandatory whenever provider traffic is enabled.

Story Review provider traffic is limited per authenticated admin, per story, and by host-wide concurrent provider slots. Defaults are 3 requests per 5 minutes, 12 per hour, and 40 per day per admin; a 60-second story cooldown and 3 requests per story per hour; and 2 concurrent provider requests. State is stored outside the database using host-local locked files. Multi-host deployments require equivalent shared infrastructure limiting before production enablement.

Operational events are written as metadata-only JSON lines to `WEBSITE/.runtime-logs/ai-story-review.jsonl` by default. Logged fields are request ID, task, provider, model, numeric admin/story references, latency, result category, and provider token counts when available. Story content, prompts, responses, cookies, session data, authorization headers, and credentials are never accepted by the logger.

### Local External-Service Testing

- Real NVIDIA NIM Story Review is allowed locally when both AI flags are true and the private key exists.
- Real SMTP and OTP delivery are allowed locally when `UCP_LOCAL_MAIL_MODE=smtp`, valid `SMTP_USER`/`SMTP_PASS` values exist, and PHPMailer is installed under the server's expected dependency path.
- Website Discord configuration uses private `.env` values first: `DISCORD_CLIENT_ID`, `DISCORD_CLIENT_SECRET`, `DISCORD_BOT_TOKEN`, `DISCORD_GUILD_ID`, `DISCORD_ROLE_WARGA_ID`, and `DISCORD_REDIRECT_URI`.
- Existing `ucp_system_settings` values remain compatibility fallbacks when the corresponding `.env` value is blank. Admin Setup does not override a nonblank environment value.
- For local OAuth, register the exact callback `http://127.0.0.1:8000/api/discord_callback.php` in the Discord developer application and use the same value for `DISCORD_REDIRECT_URI`.
- Level-10 admins can inspect value-free Discord readiness metadata through `api_admin_setup.php?action=get_discord_config_status`. The response reports only presence/source/readiness, never IDs, tokens, or secrets.
- The same response includes configuration-bootstrap diagnostics: whether the environment file is readable, its resolved source path, runtime root, and bootstrap status. It never includes environment values.
- Keep `WEBSITE/.env` private and ignored. Do not place any external-service credential in frontend variables or tracked examples.

### Manual Secret Rotation and Enablement

Any provider key shared through chat or another messaging channel must be treated as compromised:

1. Revoke or delete the exposed key in NVIDIA's key-management interface.
2. Generate a new key with the minimum required access.
3. Keep provider traffic stopped while replacing the key; if the runtime is already active, temporarily set `AI_ENABLED=false` and `AI_STORY_REVIEW_ENABLED=false` until secret injection is complete.
4. Place the replacement value only in the private local or production `WEBSITE/.env` as `NVIDIA_NIM_API_KEY`. Never paste it into source, example files, logs, commands committed to shell history, or a `VITE_` variable.
5. Confirm `.env` remains ignored with `git check-ignore WEBSITE/.env`.
6. Configure the approved model/base URL allowlists and private rate-limit/log paths if deployment defaults are unsuitable.
7. Run PHP lint, the offline contract test, OpenSpec validation, and `git diff --check`.
8. Set `AI_ENABLED=true` and `AI_STORY_REVIEW_ENABLED=true`, restart only the Website/PHP runtime, and perform the authorized local or production verification.
9. Immediately disable both flags if schema validation, privacy logging, rate limiting, latency, token usage, persistence, stale detection, or manual approval behavior differs from the approved contract.

The Bot-derived model and live Story Review flow have passed the approved checks. Local and production may use the enabled environment baseline while a valid private key is configured and all safety controls remain active.

## Manual Login and Session Smoke Test

1. Start the PHP API and frontend with the commands above.
2. Open `http://localhost:3000/`.
3. Sign in with a valid local test account.
4. If the login flow requires OTP preview, confirm that preview is being used only under `APP_ENV=local` and `UCP_LOCAL_MAIL_MODE=preview`.
5. Confirm the post-login page loads successfully.
6. Navigate within the UCP and refresh the page once to verify the session remains valid.
7. Stop and investigate configuration drift if the browser is pointed at a production API URL, production origin, or non-local mail mode during local testing.

## Asset Endpoint Smoke Test After Admin Login

After a successful admin login, verify these read-only endpoints on the local PHP API runtime:
- `http://127.0.0.1:8000/api/api_overview.php?action=assets&type=houses`
- `http://127.0.0.1:8000/api/api_overview.php?action=assets&type=businesses`
- `http://127.0.0.1:8000/api/api_overview.php?action=assets&type=families`

These checks are for smoke testing only. They do not authorize PHP API changes, auth changes, gamemode changes, schema changes, or migration work.
