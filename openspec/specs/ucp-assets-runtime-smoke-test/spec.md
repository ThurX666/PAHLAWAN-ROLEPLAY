# ucp-assets-runtime-smoke-test Specification

## Purpose
Define the local verification workflow for confirming the repo-root UCP runtime URL and smoke testing the read-only asset list endpoints before or alongside implementation work.

## Requirements
### Requirement: Local UCP runtime URL is verified before asset endpoint diagnosis
The verification workflow SHALL confirm the local runtime URL that serves `WEBSITE/public` before interpreting smoke-test failures for UCP asset endpoints.

#### Scenario: Runtime URL is identified
- **WHEN** the local website runtime is inspected for the served document root
- **THEN** the verification result records the concrete base URL used for asset endpoint requests

### Requirement: Asset smoke test remains read-only and bounded
The verification workflow SHALL issue read-only requests to `api_overview.php?action=assets&type=houses`, `api_overview.php?action=assets&type=businesses`, and `api_overview.php?action=assets&type=families`, and SHALL NOT modify feature code, gamemode, schema, migrations, or files as part of the smoke test.

#### Scenario: Requested endpoints are tested
- **WHEN** the smoke test is executed
- **THEN** the result includes status outcomes for the three requested asset endpoints only

### Requirement: HTTP 404 is diagnosed as web-root routing first
If an asset smoke-test request returns HTTP 404, the verification workflow SHALL diagnose only the local XAMPP or web-root path mapping before any code-level conclusion is made.

#### Scenario: Endpoint request returns 404
- **WHEN** one of the asset endpoint requests returns HTTP 404
- **THEN** the report limits diagnosis to runtime path or document-root mapping and does not claim a feature bug

### Requirement: Confirmed application defects require approval before patching
If the smoke test confirms a real application bug after the runtime URL is validated, the workflow SHALL report the bug first and SHALL request approval before any code patch is applied.

#### Scenario: Non-404 application failure is confirmed
- **WHEN** a validated endpoint responds from the correct runtime URL with an application-level failure
- **THEN** the report identifies the bug and stops before implementation changes
