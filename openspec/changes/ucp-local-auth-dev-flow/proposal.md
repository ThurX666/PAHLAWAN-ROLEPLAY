## Why

The UCP currently has enough local-only behavior to support development, but the local workflow is not formalized as an approved spec. That creates avoidable risk of mixing local and production environment values, mis-testing login/session behavior, or weakening OTP handling while trying to debug the website locally.

## What Changes

- Define the approved local development commands for the PHP API runtime and the Vite frontend runtime.
- Define the required local environment values for frontend origin, API base URL, `APP_ENV`, and local mail behavior.
- Define the production environment expectations that must remain separate from local development, including real SMTP delivery and no OTP preview exposure.
- Define the allowed local OTP preview workflow, limited to `APP_ENV=local` and `UCP_LOCAL_MAIL_MODE=preview`.
- Define the manual login/session verification flow and the post-login asset smoke-test URLs to use during local testing.
- Require a clear warning that `.env` files with secrets or private values must not be committed.
- Keep API logic, auth logic, gamemode code, database schema, migrations, and production auth behavior out of scope for this planning change.

## Capabilities

### New Capabilities
- `ucp-local-auth-dev-flow`: Defines the approved local and production environment workflow for testing UCP login, session persistence, OTP preview, and post-login asset smoke tests without changing authentication behavior.

### Modified Capabilities

## Impact

Affected systems are the OpenSpec planning artifacts for UCP local development, the `WEBSITE` local frontend and PHP API runtime commands, and the example environment documentation that may later be updated to match the approved workflow. No production auth behavior, API logic, database schema, gamemode code, or secrets are changed by this proposal.
