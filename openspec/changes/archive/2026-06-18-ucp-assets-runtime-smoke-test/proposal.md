## Why

The UCP asset list endpoints need a confirmed local runtime URL before any implementation work proceeds. A bounded smoke test reduces the risk of patching the wrong web root or misdiagnosing an environment issue as an application bug.

## What Changes

- Confirm the correct local runtime URL that serves `WEBSITE/public`.
- Smoke test the read-only asset endpoints for `houses`, `businesses`, and `families`.
- Record the expected behavior for 200 responses versus 404 responses caused by local web-root routing.
- Keep feature code, gamemode, schema, and migrations out of scope unless a real code bug is confirmed and separately approved.

## Capabilities

### New Capabilities
- `ucp-assets-runtime-smoke-test`: Defines the read-only runtime URL validation and asset endpoint smoke-test workflow for the local UCP environment.

### Modified Capabilities

## Impact

Affected systems are the local XAMPP or PHP web runtime for `WEBSITE/public`, the `api_overview.php` read-only endpoints, and the OpenSpec planning artifacts for this verification step.
