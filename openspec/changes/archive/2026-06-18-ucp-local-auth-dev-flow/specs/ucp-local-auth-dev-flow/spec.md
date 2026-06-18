## ADDED Requirements

### Requirement: Local development commands are defined for both UCP runtimes
The local UCP workflow SHALL define `npm run dev -- --host 0.0.0.0 --port 3000` from the `WEBSITE` directory as the approved frontend command for `http://localhost:3000/`, and SHALL define `php -S 127.0.0.1:8000 -t WEBSITE/public` from the repo root as the approved PHP API command for `http://127.0.0.1:8000/api`, so local testing uses the repo-root sources without mixing in production runtime assumptions.

#### Scenario: Developer starts the local UCP stack
- **WHEN** a developer follows the approved local workflow
- **THEN** the workflow specifies one local frontend command and one local PHP API command, with the expected local URLs for each runtime

### Requirement: Local environment values are explicit and non-production
The local UCP workflow SHALL define the required local environment values as `VITE_API_BASE_URL=api`, `VITE_DEV_API_PROXY_TARGET=http://127.0.0.1:8000`, `APP_ENV=local`, `UCP_ALLOWED_ORIGINS=http://localhost:3000,http://127.0.0.1:3000`, and a local-only `UCP_LOCAL_MAIL_MODE` value, and SHALL require that committed example files use placeholders rather than real secrets.

#### Scenario: Developer prepares local environment configuration
- **WHEN** a developer creates local environment values for the website
- **THEN** the workflow identifies the required local settings and does not require any committed secret value

### Requirement: Production environment expectations remain strict
The workflow SHALL define production expectations separately from local development, SHALL require production values to use the published API URL and production origin, SHALL require real SMTP and real OTP email delivery in production, SHALL set `APP_ENV=production`, SHALL use `UCP_LOCAL_MAIL_MODE=smtp`, SHALL NOT permit OTP preview in production, and SHALL NOT weaken production authentication behavior.

#### Scenario: Production environment is documented
- **WHEN** the workflow describes production configuration expectations
- **THEN** it keeps production mail delivery on real SMTP, forbids OTP preview exposure, and preserves the existing auth boundary

### Requirement: OTP preview is limited to safe local conditions
The workflow SHALL treat OTP preview as valid only when `APP_ENV=local` and `UCP_LOCAL_MAIL_MODE=preview`, and SHALL define that any other environment or mail mode uses non-preview behavior.

#### Scenario: Local OTP preview is enabled
- **WHEN** a developer uses OTP preview during local testing
- **THEN** the workflow requires both local-only conditions before preview output is considered allowed

### Requirement: Manual login and session verification flow is defined
The workflow SHALL define a manual local verification flow for login and session behavior, including starting both runtimes, loading `http://localhost:3000/`, authenticating through the website, confirming the post-login session state survives normal page navigation or refresh, and using preview OTP only under the approved local conditions.

#### Scenario: Developer verifies local authentication flow
- **WHEN** a developer performs the documented local login/session test
- **THEN** the workflow provides ordered steps to verify login success, session continuity, and the local-only OTP preview path when applicable

### Requirement: Post-login asset smoke-test targets are explicit
The workflow SHALL define the bounded asset smoke-test URLs `http://127.0.0.1:8000/api/api_overview.php?action=assets&type=houses`, `http://127.0.0.1:8000/api/api_overview.php?action=assets&type=businesses`, and `http://127.0.0.1:8000/api/api_overview.php?action=assets&type=families` to check after a successful local login, using the approved local API runtime and keeping the verification read-only.

#### Scenario: Developer performs post-login asset smoke test
- **WHEN** local authentication succeeds
- **THEN** the workflow identifies the asset smoke-test URLs to verify after login and keeps the checks limited to read-only requests

### Requirement: Secret-handling warning is mandatory
The workflow SHALL include an explicit warning that `.env` files with secrets, SMTP credentials, or other private runtime values MUST NOT be committed to the repository.

#### Scenario: Developer reviews env guidance
- **WHEN** a developer reads the local or production environment guidance
- **THEN** the workflow warns that secret-bearing `.env` files must stay uncommitted
