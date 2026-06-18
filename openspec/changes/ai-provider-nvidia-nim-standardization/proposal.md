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
- Select the UCP Admin Panel Story Review System as the first bounded NVIDIA NIM feature.
- Define persisted story analysis and plagiarism-match records, task-oriented API contracts, and the admin review UI states.
- Produce planning artifacts and SQL migration/schema scripts only; this change does not implement runtime AI calls, execute migrations, modify bot runtime behavior, or modify gamemode/Pawn.

## Capabilities

### New Capabilities

- `shared-ai-provider-gateway`: Defines the preferred NVIDIA NIM provider direction, authenticated Website/UCP gateway, bot-compatible provider contract, secure configuration, operational controls, and safe fallback behavior.
- `story-review-system`: Defines server-side story analysis, database-backed plagiarism comparison, persisted review history, task-oriented admin endpoints, and Admin Panel review states.

### Modified Capabilities

None.

## Impact

- Future implementation will affect the Website/UCP PHP backend gateway, `api_admin_stories.php` integration surface, Admin Stories UI, frontend types/API client integration, server-side environment/config documentation, and shared AI adapter conventions.
- The database plan adds `story_reviews` and `story_review_matches` without changing `ucp_character_stories` content ownership or the existing manual approve/revision/reject workflow.
- The Discord bot provider implementation remains behaviorally unchanged in this planning change, but its `sendMessage(messages, options)` contract is the compatibility baseline.
- Future frontend work must continue without browser AI SDK packages or provider secrets.
- No gamemode/Pawn or runtime feature behavior is changed by this proposal. SQL is generated but is not executed automatically.
