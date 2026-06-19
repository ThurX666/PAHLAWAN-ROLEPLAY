## Why

Local Website/UCP OTP delivery currently falls back to local preview because the repository contains SMTP-aware mail code but does not contain the PHPMailer runtime dependency that exists in the deployed XAMPP reference tree. A bounded sync plan is needed to restore real SMTP delivery when configured without copying older XAMPP auth behavior, exposing credentials, weakening OTP verification, or making the deployment tree the source of truth.

## What Changes

- Record a file-by-file comparison between `WEBSITE/public/api` and the reference-only `C:\xampp\htdocs\pahlawan_roleplay\api` email and OTP implementation.
- Add a managed PHPMailer dependency and a deployment-layout-aware loader, preferring Composer autoloading over copying the XAMPP `PHPMailer/src` directory into application code.
- Keep SMTP configuration env-first through the unified `app_config.php`, including transport host, port, encryption, sender identity, and credentials.
- Permit real SMTP delivery in local mode when explicitly configured, while retaining OTP preview only when both `APP_ENV=local` and `UCP_LOCAL_MAIL_MODE=preview`.
- Require production to fail closed unless real SMTP configuration and the mail dependency are available; production must never expose or return OTP preview data.
- Preserve the repository's newer login OTP, resend OTP, verification, session, cooldown, and attempt-limit behavior.
- Keep the current repository registration persistence model for this change; do not import the XAMPP-only pending-registration flow because it depends on database schema outside the approved scope.
- Add bounded contract and runtime checks for registration, login re-verification, resend, forgot-password OTP, reset-success mail, template rendering, dependency loading, and secret-safe diagnostics.

## Capabilities

### New Capabilities

- `ucp-email-otp-runtime`: Defines dependency loading, environment policy, SMTP delivery, local preview restrictions, production fail-closed behavior, and verification expectations for Website/UCP email and OTP flows.

### Modified Capabilities

- `ucp-local-auth-dev-flow`: Clarifies that local testing may use either explicitly configured real SMTP or the local-only preview mode, while production requires real delivery and must reject preview behavior.

## Impact

Affected areas are `WEBSITE/public/api/app_config.php`, `config.php`, `mailer_helper.php`, registration/login/resend/verify/forgot-password endpoints, environment examples, PHP dependency metadata and loader paths, deployment documentation, and email contract tests. The XAMPP tree remains read-only reference material. BOT runtime, Pawn, database schema, migrations, OTP verification rules, and private `.env` values remain out of scope.
