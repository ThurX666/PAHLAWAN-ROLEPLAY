## Why

PAHLAWAN ROLEPLAY currently has a provider-neutral website AI service contract and a Discord bot provider layer that already supports NVIDIA NIM, but there is no shared architecture defining how future UCP AI features must reach the provider securely. Standardizing this direction now prevents browser-side credentials and SDKs from returning while keeping website and bot integrations compatible and configurable.

## What Changes

- Establish NVIDIA NIM as the preferred AI provider for PAHLAWAN ROLEPLAY AI features.
- Define an authenticated server-side Website/UCP AI gateway; the browser calls this gateway and never calls NVIDIA or another model provider directly.
- Standardize the provider-facing contract around `sendMessage(messages, options)` so website backend adapters remain compatible with the Discord bot provider abstraction.
- Require provider selection, model settings, endpoints, and credentials to be supplied through server-side environment/configuration with safe local/development and production expectations.
- Require rate limiting, authorization, input limits, abuse controls, privacy-aware structured logging, and operational observability at the gateway.
- Define safe unavailable-provider behavior, including bounded retries, timeouts, user-safe errors, and explicitly configured fallback or feature degradation.
- Prohibit browser-side AI SDK dependencies and provider credentials.
- Produce planning and implementation tasks only; this change does not modify feature code, bot runtime behavior, gamemode/Pawn, or database schema.

## Capabilities

### New Capabilities

- `shared-ai-provider-gateway`: Defines the preferred NVIDIA NIM provider direction, authenticated Website/UCP gateway, bot-compatible provider contract, secure configuration, operational controls, and safe fallback behavior.

### Modified Capabilities

None.

## Impact

- Future implementation will affect the Website/UCP PHP backend gateway, frontend API client integration, server-side environment/config documentation, and shared AI adapter conventions.
- The Discord bot provider implementation remains behaviorally unchanged in this planning change, but its `sendMessage(messages, options)` contract is the compatibility baseline.
- Future frontend work must continue without browser AI SDK packages or provider secrets.
- No gamemode/Pawn, database schema, migrations, or runtime feature behavior is changed by this proposal.
