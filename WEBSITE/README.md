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
1. From `WEBSITE`, install frontend dependencies with `npm install`.
2. If you will use local SMTP mode, install PHP dependencies with Composer so `WEBSITE/vendor/autoload.php` exists.
3. Copy `.env.local.example` to `.env` and fill only local/private values.
4. Start the PHP API from the repo root:

```powershell
php -S 127.0.0.1:8000 -t WEBSITE/public
```

5. Start the frontend from `WEBSITE`:

```powershell
npm run dev -- --host 0.0.0.0 --port 3000
```

Required local env values:
- `VITE_API_BASE_URL=api`
- `VITE_DEV_API_PROXY_TARGET=http://127.0.0.1:8000`
- `APP_ENV=local`
- `UCP_LOCAL_MAIL_MODE=preview`
- `UCP_LOCAL_OTP_RESEND_COOLDOWN_SECONDS` only for authorized local preview smoke tests, for example `0`
- `UCP_ALLOWED_ORIGINS=http://localhost:3000,http://127.0.0.1:3000,http://localhost:5173,http://127.0.0.1:5173`
- `SMTP_HOST`, `SMTP_PORT`, `SMTP_ENCRYPTION`, `SMTP_FROM_EMAIL`, `SMTP_FROM_NAME`, `SMTP_USER`, and `SMTP_PASS` only when intentionally testing real local SMTP delivery

During pre-launch development, local UCP testing may use the currently configured real development database `arivena`. Treat it as development data: avoid destructive operations unless they are explicitly approved and backed up. After production launch, create a separate local/dev database. Production player data must never be reused for destructive tests, resets, fixtures, migration experiments, or failure simulations.

Local OTP preview rule:
- OTP preview is allowed only when `APP_ENV=local` and `UCP_LOCAL_MAIL_MODE=preview`.
- Optional resend cooldown override is allowed only under that same local preview combination.
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

## Email Runtime Deployment Package

Deployment package email runtime harus mengikuti kontrak berikut:

1. Dependensi PHPMailer utama dipasang melalui Composer di root `WEBSITE`, lalu deployment membawa `vendor/autoload.php`.
2. Layout repo memakai `WEBSITE/vendor/autoload.php`.
3. Layout flattened deployment memakai `<deployment-root>/vendor/autoload.php`.
4. Fallback legacy `api/PHPMailer/src` hanya dipertahankan sementara selama transisi deployment lama. Deployment baru tetap mengutamakan Composer.
5. File private `.env` harus berada di root runtime Website:
   - repo: `WEBSITE/.env`
   - flattened deployment: `<deployment-root>/.env`
6. Kunci SMTP yang wajib diisi di private `.env`:
   - `SMTP_HOST`
   - `SMTP_PORT`
   - `SMTP_ENCRYPTION`
   - `SMTP_FROM_EMAIL`
   - `SMTP_FROM_NAME`
   - `SMTP_USER`
   - `SMTP_PASS`
7. Local preview hanya valid saat `APP_ENV=local` dan `UCP_LOCAL_MAIL_MODE=preview`.
8. Override `UCP_LOCAL_OTP_RESEND_COOLDOWN_SECONDS` hanya boleh dipakai untuk smoke test local preview terotorisasi.
9. Production wajib `APP_ENV=production` dan `UCP_LOCAL_MAIL_MODE=smtp`, tanpa preview atau override cooldown lokal.

Sebelum sync deployment, verifikasi:
- `WEBSITE/.env` tetap di-ignore dengan `git check-ignore WEBSITE/.env`
- `composer validate` lolos
- `openspec validate ucp-email-otp-runtime-sync --type change` lolos
- `git diff --check` lolos

## Email Runtime Diagnostic Endpoint

`WEBSITE/public/api/test_email.php` sekarang hanya endpoint diagnostik aman:

- tidak mengirim email
- hanya menampilkan status hadir/tidak hadir konfigurasi
- tidak menampilkan nilai SMTP, OTP, cookie, session, token, atau provider error
- via HTTP hanya boleh dipakai admin level 10 di local mode
- via CLI hanya untuk inspeksi diagnostik lokal

Jika butuh cek runtime:

```powershell
php WEBSITE/public/api/test_email.php
```

Respons hanya berisi metadata readiness seperti mode delivery, status loader, dan field SMTP yang masih kosong.

## Authorized Manual Smoke Test

Smoke test manual email/OTP harus dilakukan secara terotorisasi dan tanpa membocorkan OTP atau credential:

1. Pastikan `WEBSITE/.env` private tidak ikut commit.
2. Tentukan mode test:
   - local preview: `APP_ENV=local`, `UCP_LOCAL_MAIL_MODE=preview`
   - local SMTP nyata: `APP_ENV=local`, `UCP_LOCAL_MAIL_MODE=smtp`
   - production-like SMTP: `APP_ENV=production`, `UCP_LOCAL_MAIL_MODE=smtp`
   - optional local preview resend override: `UCP_LOCAL_OTP_RESEND_COOLDOWN_SECONDS=0`
3. Verifikasi diagnostik aman:
   - `php WEBSITE/public/api/test_email.php`
4. Uji flow `register`.
5. Uji flow `resend_otp`.
6. Uji flow `forgot_password`.
7. Uji flow `verify_otp`.
8. Untuk mode preview, baca OTP hanya dari preview lokal privat yang sudah diizinkan. Jangan salin OTP ke source, test file, atau commit.
9. Untuk mode SMTP nyata, cukup verifikasi pesan berhasil diterima. Jangan simpan isi inbox, credential, atau header provider ke repo.
10. Jika mail gagal di production-like mode, endpoint harus fail closed dan tidak boleh mengklaim email berhasil terkirim.

Untuk local preview smoke test yang lebih stabil dari PowerShell lokal:

1. Buka terminal PowerShell terpisah.
2. Start PHP server secara manual di foreground:

```powershell
php -S 127.0.0.1:8000 -t "C:\Users\guyub\Documents\PAHLAWAN ROLEPLAY\WEBSITE\public"
```

3. Dari terminal lain, jalankan helper smoke test:

```powershell
powershell -ExecutionPolicy Bypass -File "C:\Users\guyub\Documents\PAHLAWAN ROLEPLAY\WEBSITE\tests\local_email_preview_smoke.ps1"
```

4. Secara default script memverifikasi flow `register` lalu `verify`, kemudian `forgot`, dan memisahkan target `resend` ke akun unverified lain agar tidak bentrok dengan akun yang sudah diverifikasi.
5. Script hanya mencetak `status`, kategori hasil, dan pesan yang sudah disanitasi untuk flow `register`, `resend`, `forgot`, dan `verify`, tanpa mencetak OTP mentah.
6. Untuk membuktikan `resend` secara penuh dengan akun existing yang memang sudah lewat cooldown:

```powershell
powershell -ExecutionPolicy Bypass -File "C:\Users\guyub\Documents\PAHLAWAN ROLEPLAY\WEBSITE\tests\local_email_preview_smoke.ps1" -ResendIdentifier "nama_akun_unverified"
```

7. Untuk menyiapkan target resend unverified yang aman dipakai ulang tanpa flow verify, gunakan mode khusus:

```powershell
powershell -ExecutionPolicy Bypass -File "C:\Users\guyub\Documents\PAHLAWAN ROLEPLAY\WEBSITE\tests\local_email_preview_smoke.ps1" -ResendOnly -CreateUnverifiedResendTarget
```

8. Salin field `resend_target_identifier` dari output JSON. Field ini aman karena hanya identifier akun uji, bukan OTP atau secret.
9. Jika local preview override diaktifkan dengan `UCP_LOCAL_OTP_RESEND_COOLDOWN_SECONDS=0`, Anda dapat langsung menjalankan ulang tanpa menunggu cooldown.
10. Jika override tidak diaktifkan, tunggu cooldown resend lewat lalu jalankan ulang:

```powershell
powershell -ExecutionPolicy Bypass -File "C:\Users\guyub\Documents\PAHLAWAN ROLEPLAY\WEBSITE\tests\local_email_preview_smoke.ps1" -ResendOnly -ResendIdentifier "<identifier>"
```

11. Mode `-ResendOnly` tidak menjalankan flow `verify`, sehingga target resend tetap unverified.
12. Jika `resend` pada target baru masih melaporkan `resend blocked by cooldown`, itu berarti override belum aktif atau target lama masih dalam cooldown.
13. Jika endpoint belum siap, script berhenti dengan pesan readiness yang aman.
14. Jika `register` tidak mengembalikan `local_preview`, hentikan pengujian dan cek kembali `APP_ENV=local` serta `UCP_LOCAL_MAIL_MODE=preview`.

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
- Real SMTP and OTP delivery are allowed locally when `UCP_LOCAL_MAIL_MODE=smtp`, valid `SMTP_HOST`, `SMTP_PORT`, `SMTP_ENCRYPTION`, `SMTP_FROM_EMAIL`, `SMTP_FROM_NAME`, `SMTP_USER`, and `SMTP_PASS` values exist, and PHPMailer is available from `WEBSITE/vendor/autoload.php` or, during deployment transition only, the legacy `api/PHPMailer/src` fallback.
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
