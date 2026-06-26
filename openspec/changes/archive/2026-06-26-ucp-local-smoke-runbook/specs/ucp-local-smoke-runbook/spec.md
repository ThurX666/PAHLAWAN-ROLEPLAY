## ADDED Requirements

### Requirement: Local smoke checks are mode-based
The UCP local smoke runbook SHALL separate repo development checks, production-build checks, and flattened XAMPP runtime checks so the operator can choose the smallest validation that matches the current work mode.

#### Scenario: Operator validates source changes
- **WHEN** the operator validates UCP source changes from the repository
- **THEN** the runbook identifies repo-mode checks without requiring XAMPP sync first

#### Scenario: Operator validates flattened runtime
- **WHEN** the operator validates the local XAMPP runtime
- **THEN** the runbook identifies build and runtime checks that treat XAMPP as a target, not source of truth

### Requirement: Smoke evidence is secret-safe
The UCP local smoke runbook SHALL define evidence that records status, mode, route or module, and pass/fail result without exposing `.env`, tokens, passwords, cookies, OTPs, session values, provider error details, private rows, or full logs.

#### Scenario: Operator records smoke result
- **WHEN** a local smoke check passes or fails
- **THEN** the runbook records only bounded secret-safe evidence

### Requirement: Stop conditions prevent unsafe validation
The UCP local smoke runbook SHALL define stop conditions for missing private environment configuration, stale XAMPP runtime, failed build, broken API health, failed auth/session continuity, unsafe diagnostics, and any required database write.

#### Scenario: Stop condition occurs
- **WHEN** a stop condition occurs during validation
- **THEN** the runbook stops further validation and directs the operator to fix or resync before continuing
