# WEBSITE Local and Production Workflow

This directory contains the UCP frontend and the PHP API document root used for local development.

## Do Not Commit Secrets

`WEBSITE/.env` is local or deployment-only runtime state. Do not commit `.env` files or any secret-bearing values such as SMTP credentials, API keys, cookies, OTPs, or private database passwords.

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
