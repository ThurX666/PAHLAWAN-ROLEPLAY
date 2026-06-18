## 1. OpenSpec Definition

- [ ] 1.1 Finalize the proposal for the approved local/dev UCP auth workflow separation.
- [ ] 1.2 Add the new `ucp-local-auth-dev-flow` delta spec covering local commands, env requirements, production expectations, OTP preview limits, manual login/session checks, and post-login smoke-test URLs.
- [ ] 1.3 Validate that the spec scope excludes API logic, auth logic, gamemode changes, schema changes, migrations, secret commits, and production auth weakening.

## 2. Documentation Planning

- [ ] 2.1 Map which example env or documentation files, if any, need follow-up updates to reflect the approved local workflow without committing private values.
- [ ] 2.2 Define the required local `.env` placeholders and production-only expectations for any follow-up docs/examples patch.
- [ ] 2.3 Define the warning language that future docs/examples must include about never committing `.env` files with secrets.

## 3. Verification Planning

- [ ] 3.1 Define the manual local login and session test flow, including the OTP preview preconditions.
- [ ] 3.2 Define the post-login asset smoke-test URLs that should be checked after successful local authentication.
- [ ] 3.3 Run OpenSpec validation and `git diff --check`, then report the planning artifacts and next implementation prompt.
