## 1. Deployment package and env contract planning

- [x] 1.1 Audit the current Website/UCP deployable artifacts for repo layout and flattened XAMPP layout without changing runtime files.
- [x] 1.2 Define the production package checklist, including frontend build output, PHP API files, vendor/composer readiness, and private deployment-only artifacts.
- [x] 1.3 Define the local vs production env contract, including tracked example files, private `.env`, required readiness categories, and forbidden secret exposure.

## 2. Runtime mapping and diagnostic planning

- [x] 2.1 Map repository Website paths to the approved XAMPP/htdocs runtime paths and document required post-sync checks.
- [ ] 2.2 Inventory existing secret-safe diagnostics for API health, session/auth, email runtime, and bounded read-only validation.
- [ ] 2.3 Identify any missing runbook-only documentation or diagnostic gaps that must be addressed before launch, without implementing runtime changes yet.

## 3. Authorized smoke validation runbook

- [ ] 3.1 Define the ordered post-deploy validation sequence for frontend availability, API reachability, session/auth continuity, email runtime readiness, and bounded asset checks.
- [ ] 3.2 Define the authorized operator inputs, preconditions, and evidence format for smoke validation without recording secrets.
- [ ] 3.3 Define failure classification, stop conditions, and escalation guidance for smoke validation anomalies.

## 4. Rollback and launch readiness

- [ ] 4.1 Define rollback triggers and the release components that must be restored for a failed deployment.
- [ ] 4.2 Define the rollback verification checklist that confirms the previous release is healthy again.
- [ ] 4.3 Define the final launch readiness checklist and sign-off criteria for community launch.

## 5. Final validation and handoff

- [ ] 5.1 Validate the OpenSpec change artifacts and ensure proposal, design, spec delta, and tasks remain aligned.
- [ ] 5.2 Confirm the change does not require BOT runtime, Pawn/gamemode, or database schema scope.
- [ ] 5.3 Prepare the change for implementation approval without starting runtime modifications.
