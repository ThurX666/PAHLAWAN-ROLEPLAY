## 1. Dependency And Configuration Foundation

- [ ] 1.1 Add repository-owned Composer metadata for `phpmailer/phpmailer`, generate the lock file, and confirm no credentials or private runtime values are added.
- [ ] 1.2 Extend Website environment examples with placeholder-only SMTP host, port, encryption, sender identity, username, and password settings.
- [ ] 1.3 Extend `app_config.php` diagnostics and mail configuration accessors to expose only readiness, loader type, and bounded path status.
- [ ] 1.4 Implement a Website-root Composer autoloader resolution for repository and flattened deployment layouts, with a documented temporary legacy `api/PHPMailer/src` fallback only if required.

## 2. Shared Mail Runtime

- [ ] 2.1 Refactor `mailer_helper.php` to construct PHPMailer from env-first transport configuration instead of hardcoded Gmail host, port, encryption, and sender settings.
- [ ] 2.2 Enforce the mail-mode matrix: local preview bypasses SMTP, local SMTP requires full readiness, and every non-local environment forbids preview.
- [ ] 2.3 Make dependency, configuration, transport, and provider failures fail closed with sanitized categories and without exposing message bodies, addresses, OTPs, or credentials.
- [ ] 2.4 Preserve HTML and plain-text templates for verification, welcome, forgot-password, and reset-success messages using the shared mailer construction path.

## 3. Email And OTP Caller Alignment

- [ ] 3.1 Verify registration email uses the repository `player_ucp` persistence flow and does not import the XAMPP `ucp_pending_registrations` dependency.
- [ ] 3.2 Align login re-verification and automatic resend branches with the shared delivery result while preserving device/location checks, attempt counts, cooldowns, and session behavior.
- [ ] 3.3 Align the explicit resend endpoint with local preview and real SMTP modes without changing OTP issuance or verification semantics.
- [ ] 3.4 Align forgot-password OTP and password-reset-success email handling with the same mode and failure policy.
- [ ] 3.5 Verify post-registration welcome email remains best-effort after successful verification and cannot roll back or bypass OTP verification.

## 4. Safety And Contract Tests

- [ ] 4.1 Add offline tests for repository and flattened Composer loader resolution, plus missing-dependency fail-closed behavior.
- [ ] 4.2 Add mode-matrix tests proving preview works only for `APP_ENV=local` plus `UCP_LOCAL_MAIL_MODE=preview`.
- [ ] 4.3 Add SMTP readiness tests for local and production using synthetic configuration without contacting an external provider.
- [ ] 4.4 Add caller contract tests for registration, login OTP, resend, forgot password, verification welcome email, and reset-success email.
- [ ] 4.5 Add negative checks proving diagnostics and responses do not expose credentials, private addresses, OTP values outside approved local preview, cookies, or session identifiers.
- [ ] 4.6 Restrict or replace `test_email.php` so production readiness can be diagnosed without an unauthenticated or unsolicited send path.

## 5. Documentation And Deployment Validation

- [ ] 5.1 Document Composer install/package steps for repo development and flattened XAMPP deployment, including the decision on whether `vendor` is built on-host or packaged before sync.
- [ ] 5.2 Document local preview, local real SMTP, and production SMTP environment contracts without including real values.
- [ ] 5.3 Run PHP lint and all email/OTP contract tests.
- [ ] 5.4 Perform an authorized local preview smoke test and an authorized local real-SMTP smoke test using private environment configuration.
- [ ] 5.5 Verify the flattened deployment layout resolves `.env`, Composer autoloading, templates, and secret-safe diagnostics before production enablement.
- [ ] 5.6 Run `openspec validate ucp-email-otp-runtime-sync --type change` and `git diff --check`.
