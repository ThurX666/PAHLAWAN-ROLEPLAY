## ADDED Requirements

### Requirement: Repository remains the only local source of truth
The local Website/UCP workflow SHALL keep `C:\\Users\\guyub\\Documents\\PAHLAWAN ROLEPLAY` as the only source of truth for tracked code, and SHALL treat `C:\\xampp\\htdocs\\pahlawan_roleplay` only as a local runtime target for sync or copy operations.

#### Scenario: Developer updates local runtime
- **WHEN** a developer needs to test the flattened local runtime in XAMPP
- **THEN** the workflow uses the repository as the source and treats the XAMPP tree only as a runtime target

### Requirement: Frontend dev flow and build flow are distinct
The local workflow SHALL define `npm run dev` from `WEBSITE` as the default frontend development mode for rapid iteration, and SHALL define `npm run build` as the local production-build validation mode to use before a flattened runtime sync or production-like local verification.

#### Scenario: Developer is iterating on frontend changes
- **WHEN** the developer is making routine UI or API-integration changes
- **THEN** the workflow uses `npm run dev` instead of requiring a production build on every change

#### Scenario: Developer prepares a flattened local runtime
- **WHEN** the developer wants to validate the deployed-style frontend locally
- **THEN** the workflow requires `npm run build` before syncing the build output to the XAMPP runtime target

### Requirement: PHP built-in server is the baseline local API workflow
The local workflow SHALL define the PHP built-in server from the repository as the baseline API runtime for source-of-truth development, and SHALL use XAMPP Apache only when the developer explicitly needs a flattened local runtime validation.

#### Scenario: Developer tests API code directly from the repository
- **WHEN** the developer needs to validate Website/PHP API source changes
- **THEN** the workflow starts the PHP built-in server from the repository rather than requiring a sync to XAMPP first

### Requirement: Local environment handling is explicit and private
The local workflow SHALL distinguish tracked env example files from private local `.env`, SHALL define which local values are required for frontend and API development, and SHALL forbid committing private runtime values or treating the XAMPP runtime as an env source of truth.

#### Scenario: Developer prepares local environment configuration
- **WHEN** the developer sets up or updates local runtime variables
- **THEN** the workflow uses tracked examples only as templates and keeps real values only in private `.env`

### Requirement: Local runtime sync and rollback are documented
The local workflow SHALL define when a developer syncs or copies repository output to the local XAMPP runtime, SHALL define the minimum post-sync checks, and SHALL define a bounded rollback/reset path that restores a clean local runtime without modifying the repository source.

#### Scenario: Developer needs to reset a stale local runtime
- **WHEN** the local XAMPP runtime no longer matches the repository expectation
- **THEN** the workflow provides a reset or rollback path that refreshes the runtime target from repository-owned artifacts without moving or rewriting the repository itself

### Requirement: Local testing checklist is mode-aware
The local workflow SHALL define a testing checklist that distinguishes repo-based development checks, production-build validation checks, and flattened XAMPP runtime checks, and SHALL identify which checks are appropriate for each mode.

#### Scenario: Developer chooses a local test path
- **WHEN** the developer decides whether to run repo-based development checks or flattened runtime validation
- **THEN** the workflow identifies the correct commands, runtime mode, and smoke checks for that local objective
