## ADDED Requirements

### Requirement: Repository email runtime is authoritative
The Website/UCP repository SHALL remain the source of truth for email and OTP behavior, and synchronization from the deployed XAMPP tree SHALL be limited to reviewed dependency or template capability without replacing newer repository auth, session, preview, cooldown, attempt-limit, or verification behavior.

#### Scenario: XAMPP and repository files differ
- **WHEN** an email or OTP file differs between XAMPP and the repository
- **THEN** the implementation compares the behavior and preserves the repository version unless a specific missing capability is approved

### Requirement: PHPMailer dependency is reproducible
The Website/UCP SHALL declare PHPMailer as a managed Composer dependency and SHALL load it through a Website-root `vendor/autoload.php` path that works in both repository and flattened deployment layouts.

#### Scenario: Composer dependency is installed
- **WHEN** the mail runtime initializes in a supported layout
- **THEN** it loads PHPMailer from the Website-root Composer autoloader without requiring an untracked XAMPP-only source directory

#### Scenario: Mail dependency is unavailable
- **WHEN** SMTP delivery is requested and no approved PHPMailer loader is available
- **THEN** the request fails closed with a sanitized dependency error and does not report successful delivery

### Requirement: SMTP configuration is environment-first
The mail runtime SHALL obtain SMTP host, port, encryption, username, password, sender address, and sender name through the unified `app_config.php` environment loader, and committed configuration examples SHALL contain placeholders rather than private values.

#### Scenario: SMTP is fully configured
- **WHEN** SMTP mode is selected and all required environment values are present
- **THEN** the shared mailer uses those environment values for delivery

#### Scenario: SMTP configuration is incomplete
- **WHEN** SMTP mode is selected but a required setting is unavailable
- **THEN** the mail runtime returns a sanitized configuration failure without exposing any configured value

### Requirement: Local real SMTP delivery is supported
The Website/UCP SHALL allow real SMTP delivery in local development when `APP_ENV=local`, `UCP_LOCAL_MAIL_MODE=smtp`, the PHPMailer dependency is available, and complete private SMTP configuration is present.

#### Scenario: Developer selects local SMTP mode
- **WHEN** a developer runs the local PHP runtime with local SMTP mode and valid private configuration
- **THEN** registration, login verification, resend, forgot-password, welcome, and reset-success email operations use real SMTP rather than preview output

### Requirement: OTP preview is strictly local
OTP preview SHALL be available only when `APP_ENV=local` and `UCP_LOCAL_MAIL_MODE=preview`, and SHALL NOT be returned, logged as preview output, or used as a delivery substitute in any non-local environment.

#### Scenario: Approved local preview is active
- **WHEN** both local preview conditions are satisfied
- **THEN** SMTP is bypassed and the existing local-only preview mechanism may provide the OTP for development verification

#### Scenario: Preview is requested outside local mode
- **WHEN** preview mode is configured while `APP_ENV` is not `local`
- **THEN** the mail runtime rejects preview behavior and does not expose the OTP

### Requirement: Production requires real mail delivery
Production SHALL require a loadable PHPMailer dependency, complete SMTP configuration, and real delivery attempts, and SHALL fail closed when these prerequisites or the send operation fail.

#### Scenario: Production prerequisites are missing
- **WHEN** production processes an email-backed OTP operation without complete mail prerequisites
- **THEN** the endpoint reports delivery failure, does not claim that mail was sent, and does not expose preview data

#### Scenario: Production SMTP succeeds
- **WHEN** production has complete configuration and the provider accepts the message
- **THEN** the endpoint may report that the email operation succeeded while OTP verification remains mandatory

### Requirement: Email flows preserve authentication controls
Registration OTP, login re-verification, resend OTP, OTP verification, forgot-password OTP, password reset, welcome email, and reset-success email integration SHALL preserve existing OTP generation, persistence, expiry, cooldown, attempt limits, password checks, and session creation behavior.

#### Scenario: Mail delivery implementation changes
- **WHEN** the shared mail dependency or transport configuration is updated
- **THEN** authentication and verification semantics remain unchanged and no flow bypasses OTP validation

### Requirement: XAMPP pending-registration divergence is not imported
This change SHALL NOT adopt the XAMPP `ucp_pending_registrations` implementation because it requires database schema outside the approved scope.

#### Scenario: Registration code is synchronized
- **WHEN** the repository and XAMPP registration implementations are compared
- **THEN** the repository persistence model is retained and no schema or migration is added

### Requirement: Mail diagnostics and tests are secret-safe
Mail readiness diagnostics and automated tests SHALL expose only status, selected loader type, bounded path information, and sanitized failure categories, and SHALL NOT expose SMTP credentials, private addresses, OTP values, cookies, sessions, or provider response secrets.

#### Scenario: Operator checks mail readiness
- **WHEN** a diagnostic or contract test reports mail configuration status
- **THEN** it reports only non-secret readiness information

### Requirement: Email templates remain functional across flows
The shared mail runtime SHALL provide HTML and plain-text content for verification, welcome, forgot-password, and reset-success messages without embedding private configuration values.

#### Scenario: A supported email is rendered
- **WHEN** a supported mail flow constructs its message
- **THEN** the output includes the expected flow-specific subject and content placeholders without exposing unrelated secrets
