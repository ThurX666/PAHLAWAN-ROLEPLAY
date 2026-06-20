## ADDED Requirements

### Requirement: Production deployment package checklist is explicit
The Website/UCP production workflow SHALL define a deployment package checklist that explicitly identifies the required frontend build output, PHP API files, Composer/vendor readiness strategy, tracked env example files, and the private deployment-only artifacts that MUST NOT be committed.

#### Scenario: Operator prepares a deployable package
- **WHEN** an operator prepares a production deployment from the repository
- **THEN** the workflow identifies which tracked artifacts must be present, which private artifacts remain deployment-only, and whether Composer dependencies are packaged before sync or built on-host

### Requirement: Local and production environment contracts are separated
The workflow SHALL define separate local and production environment contracts, SHALL distinguish tracked example files from private `.env` files, and SHALL require production validation to confirm presence and readiness of required keys without exposing their values.

#### Scenario: Operator reviews environment readiness
- **WHEN** an operator verifies a local or production runtime before deploy
- **THEN** the workflow identifies the required environment categories, keeps secret values private, and forbids using tracked example files as live secret stores

### Requirement: Repo and XAMPP layout mapping is documented
The workflow SHALL define the approved mapping between the repository Website layout and the flattened XAMPP/htdocs runtime layout, including runtime root, `api` path, vendor location, public build output, and `.env` resolution expectations.

#### Scenario: Operator syncs repository output to XAMPP
- **WHEN** a deployment is prepared for `C:\\xampp\\htdocs\\pahlawan_roleplay`
- **THEN** the workflow identifies where repository artifacts must land in the flattened runtime and which paths must be checked after sync

### Requirement: Authorized smoke validation is secret-safe
The workflow SHALL define an authorized post-deploy smoke validation sequence for frontend build availability, API health, auth/session continuity, email runtime readiness, and bounded read-only checks, and SHALL require that diagnostics expose only status, path, and readiness information rather than secrets.

#### Scenario: Operator runs post-deploy smoke validation
- **WHEN** an authorized operator validates a newly deployed Website/UCP runtime
- **THEN** the workflow provides ordered smoke checks for frontend, API, session/auth, and email readiness without exposing `.env`, OTP, credentials, cookies, session values, or provider error detail

### Requirement: Rollback checklist is mandatory
The workflow SHALL define a rollback checklist that identifies the trigger conditions for rollback, the package/runtime elements that must be restored, and the minimum verification that confirms the previous release is healthy again.

#### Scenario: Post-deploy smoke validation fails
- **WHEN** a critical deployment validation step fails
- **THEN** the workflow provides explicit rollback steps and a bounded verification sequence for the restored release

### Requirement: Launch readiness checklist is explicit
The workflow SHALL define a launch readiness checklist that gates community launch on deploy verification status, package readiness, env readiness, smoke validation completion, and rollback preparedness.

#### Scenario: Reviewer decides whether the release is launch-ready
- **WHEN** the operator presents the deployment result for approval
- **THEN** the workflow provides a checklist that shows whether the release is ready to launch, needs remediation, or must be rolled back
