## Context

The repository and deployed XAMPP API trees contain the same email entry points, but they are not equivalent:

- `forgot.php`, `test_email.php`, `auth_session.php`, and `config.php` are identical.
- The repository versions of `auth.php`, `resend_otp.php`, `verify.php`, and `mailer_helper.php` are newer and include unified `app_config.php` loading, local-preview policy, dependency diagnostics, and safer fail-closed branches that are absent from XAMPP.
- XAMPP contains `api/PHPMailer/src` with PHPMailer 7.0.2, while the repository has neither that directory nor Composer metadata or `vendor/autoload.php`. The repository mail helper therefore cannot perform real SMTP delivery even when credentials are configured.
- XAMPP `register.php` uses `ucp_pending_registrations`; the repository writes pending verification state through the existing `player_ucp` model. Importing the XAMPP registration implementation would require an unapproved schema dependency and could regress the current verified auth contract.
- Both mail helpers currently hardcode Gmail transport host, implicit TLS, and port while reading credentials from env-backed variables. The credentials are not to be copied from XAMPP.

The implementation must treat the repository as authoritative and use XAMPP only to identify missing runtime packaging and potentially useful templates. It must support both repository layout (`WEBSITE/public/api`) and flattened deployment layout (`<deployment-root>/api`) through the existing `app_config.php` root resolution.

## Goals / Non-Goals

**Goals:**

- Make real SMTP delivery available in local development when a developer explicitly configures SMTP and selects SMTP mode.
- Keep preview output available only under the two-key local policy: `APP_ENV=local` and `UCP_LOCAL_MAIL_MODE=preview`.
- Require real SMTP and a loadable PHPMailer dependency in production, with secret-safe failure diagnostics.
- Preserve login re-verification, registration OTP, resend, verify, forgot-password, password-reset-success, cooldown, attempt-limit, and session behavior.
- Establish a reproducible PHPMailer dependency and loader contract for repository and flattened deployment layouts.
- Add contract tests that prove preview cannot activate outside local mode and that production cannot report success when mail prerequisites are absent.

**Non-Goals:**

- Editing or synchronizing files back into `C:\xampp\htdocs\pahlawan_roleplay`.
- Copying SMTP credentials, private `.env` values, runtime logs, OTP values, cookies, or sessions.
- Adopting the XAMPP `ucp_pending_registrations` registration model.
- Changing database schema, migrations, password hashing, OTP generation, OTP expiry, resend limits, session handling, or approval behavior.
- Modifying BOT, Pawn, or unrelated Website/UCP features.

## Decisions

### 1. Sync by capability, not by copying XAMPP files

The implementation SHALL preserve repository versions as the base and import only confirmed missing runtime capability. XAMPP auth files are older than the repository equivalents and omit local-preview and unified-config protections.

Alternative considered: overwrite repo email files with XAMPP versions. Rejected because it would remove newer safeguards and reintroduce deployment-specific assumptions.

### 2. Manage PHPMailer with Composer

Add repository-owned Composer metadata for `phpmailer/phpmailer` and load it through `vendor/autoload.php`. Official PHPMailer guidance recommends Composer and autoloading; manual `src` requires are a fallback only.

The loader SHALL resolve the Website root from `app_config.php` and check the corresponding Composer autoloader in both supported layouts:

```text
Repository: WEBSITE/vendor/autoload.php
Flattened:  <deployment-root>/vendor/autoload.php
```

A temporary legacy fallback to `api/PHPMailer/src/{Exception,PHPMailer,SMTP}.php` MAY be retained only to support an existing deployment during transition. New repository deployments SHALL use Composer-managed files. The XAMPP `PHPMailer` directory and its files SHALL NOT be copied blindly into source control.

### 3. Move all transport settings behind app_config.php

`mailer_helper.php` SHALL read bounded configuration through `app_env()` rather than embedding provider-specific transport choices:

- `SMTP_HOST`
- `SMTP_PORT`
- `SMTP_ENCRYPTION`
- `SMTP_USER`
- `SMTP_PASS`
- `SMTP_FROM_EMAIL`
- `SMTP_FROM_NAME`
- optional timeout/debug controls with safe defaults

Committed examples SHALL contain placeholders only. Diagnostics SHALL report whether required fields and dependency paths are available, never their values.

### 4. Local SMTP and local preview are explicit, mutually understandable modes

- `APP_ENV=local` plus `UCP_LOCAL_MAIL_MODE=preview`: do not call SMTP; expose preview only through the already approved local response/log mechanism.
- `APP_ENV=local` plus `UCP_LOCAL_MAIL_MODE=smtp`: require the dependency and complete SMTP configuration, then attempt real delivery.
- Any non-local environment: preview is forbidden regardless of `UCP_LOCAL_MAIL_MODE`.
- Production: require SMTP mode, loadable dependency, and complete transport configuration; otherwise fail closed and do not claim that an OTP was sent.

### 5. Preserve OTP issuance and verification semantics

The change SHALL not alter OTP values, persistence, expiry, attempt counters, cooldowns, verification comparison, session creation, or password-reset authorization. Mail delivery failure must remain distinguishable from successful issuance without bypassing verification.

The repository versions of `auth.php`, `resend_otp.php`, and `verify.php` remain authoritative. `forgot.php` is identical across both trees and needs only policy alignment for local preview versus SMTP.

### 6. Registration remains on the repository data model

The XAMPP-only `ucp_pending_registrations` code is documented as a divergent implementation, not a sync candidate. Any future move to a pending-registration table requires a separate OpenSpec change with schema and migration approval.

### 7. Template sync is semantic and testable

Existing verification, welcome, forgot-password, and reset-success templates SHALL be preserved unless a bounded comparison identifies a non-secret presentation improvement. Tests SHALL verify subject/body generation and required placeholders without snapshots containing live addresses, OTPs, or credentials.

### 8. Test and diagnostic endpoints remain safe

Email diagnostics SHALL be local-only or CLI-oriented, shall use synthetic values, and shall not echo configuration secrets. Production checks shall validate readiness without sending an unsolicited test message unless explicitly invoked by an authorized operator.

## Risks / Trade-offs

- [Composer is unavailable on the XAMPP host] → Build/install dependencies from the repo deployment process and sync the generated `vendor` directory as a deployment artifact, or install Composer on the host; do not fall back to downloading untracked library files manually.
- [Legacy `api/PHPMailer` and Composer copies drift] → Prefer Composer first, log only the selected loader type/path status, and remove the legacy fallback in a later controlled deployment once all environments use `vendor`.
- [Local preview accidentally reaches production] → Enforce `APP_ENV=local` in code and contract tests independently of mail mode.
- [SMTP settings are incomplete or incompatible] → Validate host, port, encryption, sender, credentials, and dependency before send; fail closed with sanitized error categories.
- [Mail succeeds but endpoint state handling regresses] → Test each caller separately and keep OTP/session/database logic unchanged.
- [Registration implementations diverge further] → Explicitly document the XAMPP pending-table flow as excluded and keep schema changes out of this change.

## Migration Plan

1. Add Composer metadata and install PHPMailer in the repository development environment.
2. Extend env examples and `app_config.php`-backed mail configuration without committing real values.
3. Introduce the layout-aware autoloader with an optional legacy XAMPP fallback.
4. Centralize mailer construction and transport validation in `mailer_helper.php`.
5. Align registration, login re-verification, resend, forgot-password, welcome, and reset-success callers with the shared delivery result contract while preserving auth behavior.
6. Run PHP lint and offline contract tests for dependency, preview, SMTP readiness, production fail-closed behavior, and secret-safe diagnostics.
7. Test local preview, then local real SMTP with private configuration.
8. Build the deployment package with Composer dependencies and verify the flattened XAMPP layout before enabling production SMTP.

Rollback: revert the repository patch and deployment package together. Keep production mail disabled/fail-closed rather than reverting to OTP preview or bypassing verification.

## Open Questions

- Whether deployment automation can run `composer install --no-dev --classmap-authoritative` on the target host or must package `vendor` before synchronization.
- Whether the temporary `api/PHPMailer/src` fallback is required for the first production rollout or can be omitted after the deployment package is updated.
- Whether SMTP transport should default to the current Gmail-compatible host/port/encryption or require all three values explicitly in every environment.
