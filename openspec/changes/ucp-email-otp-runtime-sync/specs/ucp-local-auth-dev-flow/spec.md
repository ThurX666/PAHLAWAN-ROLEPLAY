## MODIFIED Requirements

### Requirement: Local environment values are explicit and non-production
The local UCP workflow SHALL define the required local environment values as `VITE_API_BASE_URL=api`, `VITE_DEV_API_PROXY_TARGET=http://127.0.0.1:8000`, `APP_ENV=local`, `UCP_ALLOWED_ORIGINS=http://localhost:3000,http://127.0.0.1:3000`, and an explicit `UCP_LOCAL_MAIL_MODE` of either `preview` or `smtp`, and SHALL require that committed example files use placeholders rather than real secrets.

#### Scenario: Developer prepares local preview configuration
- **WHEN** a developer selects local OTP preview
- **THEN** the workflow requires `APP_ENV=local`, `UCP_LOCAL_MAIL_MODE=preview`, and no committed secret value

#### Scenario: Developer prepares local SMTP configuration
- **WHEN** a developer selects real local email delivery
- **THEN** the workflow requires `APP_ENV=local`, `UCP_LOCAL_MAIL_MODE=smtp`, a loadable mail dependency, and complete private SMTP environment values

### Requirement: Production environment expectations remain strict
The workflow SHALL define production expectations separately from local development, SHALL require production values to use the published API URL and production origin, SHALL require a managed mail dependency plus complete real SMTP configuration and real OTP email delivery in production, SHALL set `APP_ENV=production`, SHALL use `UCP_LOCAL_MAIL_MODE=smtp`, SHALL NOT permit OTP preview in production, and SHALL NOT weaken production authentication behavior.

#### Scenario: Production environment is documented
- **WHEN** the workflow describes production configuration expectations
- **THEN** it requires the mail dependency and real SMTP delivery, forbids OTP preview exposure, fails closed when mail prerequisites are absent, and preserves the existing auth boundary

### Requirement: OTP preview is limited to safe local conditions
The workflow SHALL treat OTP preview as valid only when `APP_ENV=local` and `UCP_LOCAL_MAIL_MODE=preview`, SHALL allow local real delivery only when `APP_ENV=local` and `UCP_LOCAL_MAIL_MODE=smtp`, and SHALL define that any non-local environment uses non-preview behavior.

#### Scenario: Local OTP preview is enabled
- **WHEN** a developer uses OTP preview during local testing
- **THEN** the workflow requires both local-only conditions before preview output is considered allowed

#### Scenario: Local real SMTP is enabled
- **WHEN** a developer uses SMTP delivery during local testing
- **THEN** preview output remains disabled and the workflow requires dependency and SMTP readiness

### Requirement: Manual login and session verification flow is defined
The workflow SHALL define a manual local verification flow for login and session behavior, including starting both runtimes, loading `http://localhost:3000/`, authenticating through the website, confirming the post-login session state survives normal page navigation or refresh, and obtaining the OTP through either configured real local SMTP or preview only under the approved local conditions.

#### Scenario: Developer verifies local authentication with preview
- **WHEN** a developer performs the documented login/session test in local preview mode
- **THEN** the workflow provides ordered steps to obtain the OTP from the private local preview channel, verify login success, and confirm session continuity

#### Scenario: Developer verifies local authentication with SMTP
- **WHEN** a developer performs the documented login/session test in local SMTP mode
- **THEN** the workflow provides ordered steps to confirm real email receipt, verify login success, and confirm session continuity
