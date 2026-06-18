## 0. Story Review Planning Package

- [x] 0.1 Audit `ucp_character_stories`, player story submission, Admin Stories review flow, admin authorization, and existing browser-only mock analysis.
- [x] 0.2 Select Story Review as the first bounded Website/UCP NVIDIA NIM task and define its server-loaded-input and human-review boundaries.
- [x] 0.3 Define `analyze_story`, `get_story_review`, and `get_story_matches` contracts and the Analyze/Re-Analyze/View Analysis/View Similar Stories UI states.
- [x] 0.4 Generate an unexecuted SQL migration under `DATABASE/migrations/` for `ucp_story_reviews` and `ucp_story_review_matches` and align the tracked story schema reference.
- [x] 0.5 Add Story Review capability requirements and validation scenarios to this change.
- [x] 0.6 Audit Discord Bot/PHRP-AI NVIDIA configuration and record `https://integrate.api.nvidia.com/v1` with `deepseek-ai/deepseek-v4-flash` as the Website/UCP default baseline without exposing credentials.

## 1. Configuration and Contract

- [x] 1.1 For the selected Story Review task and admin level 5 role, capability-test the Bot-derived default model `deepseek-ai/deepseek-v4-flash` and approve request limits and production rate/token budgets before enabling provider traffic.
- [x] 1.2 Document server-only AI configuration for local/development and production, including preferred `nvidia` selection, blank secret placeholders, `https://integrate.api.nvidia.com/v1` and `deepseek-ai/deepseek-v4-flash` as defaults, explicit override rules, timeouts, output bounds, rate limits, and disabled-by-default fallback.
- [x] 1.3 Define shared message and option types for `sendMessage(messages, options)`, including normalized output and error categories compatible with the Discord bot contract.
- [x] 1.4 Add configuration validation that rejects unsupported providers, unsafe endpoints, missing required production settings, and any attempt to source provider credentials from frontend-visible variables.

## 2. Website/UCP Provider Gateway

- [x] 2.1 Implement the server-side provider interface and NVIDIA NIM adapter with Bot-aligned defaults (`https://integrate.api.nvidia.com/v1`, `deepseek-ai/deepseek-v4-flash`), retaining explicit server-side overrides and containing provider-specific request/response normalization inside the adapter.
- [x] 2.2 Implement authenticated `analyze_story`, `get_story_review`, and `get_story_matches` actions using the existing session/auth flow and `ucp_require_admin(5)`.
- [x] 2.3 Enforce per-task authorization, input/output limits, timeouts, account and task rate limits, and appropriate IP/session abuse controls before provider execution.
- [x] 2.4 Add structured privacy-aware logging for request IDs, task, provider, model, actor reference, latency, result category, usage metadata, validation failures, and rate-limit events without logging secrets or full content by default.
- [x] 2.5 Implement bounded retry classification, safe provider error mapping, deterministic unavailable states, and optional explicit per-task fallback that remains disabled unless fully configured.
- [x] 2.6 Add local disabled/mock behavior that permits UI development without live credentials and production checks that fail safely when AI configuration is incomplete.

## 3. Website Frontend Integration

- [x] 3.1 Implement a provider-neutral frontend API adapter that calls the authenticated UCP AI gateway and satisfies the existing Website `sendMessage(messages, options)` service boundary without accepting provider credentials or endpoints.
- [x] 3.2 Replace Admin Stories browser mock analysis with Analyze Story, Re-Analyze Story, View Analysis, and View Similar Stories states while preserving manual status actions.
- [x] 3.3 Verify Website dependencies and generated frontend assets contain no browser-side NVIDIA, OpenAI, Groq, Google GenAI, or equivalent provider SDK usage and no provider credentials.

## 4. Discord Bot Compatibility

- [x] 4.1 Compare the Website gateway message roles, option semantics, normalized string result, error handling, and default NVIDIA model/base URL with `BOT/PHRP-AI/utils/aiProvider.js` and `BOT/PHRP-AI/config/app.json`.
- [x] 4.2 Document any compatibility adapter needed for independent runtime-specific configuration, verify Website defaults match the audited Bot values, and leave the bot's active provider, model, configuration files, credentials, and runtime behavior unchanged.

## 5. Validation and Operational Tests

- [x] 5.1 Test authenticated success, unauthenticated rejection, unauthorized task access, malformed and oversized input rejection, and unsupported client-supplied provider controls.
- [x] 5.2 Test per-account/task rate limiting and confirm rejected traffic does not call NVIDIA NIM.
- [x] 5.3 Test timeout, retryable failure, non-retryable failure, missing configuration, fallback-disabled, and explicitly configured fallback behavior without exposing provider details.
- [x] 5.4 Verify logs contain required operational metadata while excluding credentials, authorization/session data, full prompts, and full responses.
- [x] 5.5 Run the Website production build, relevant backend checks, secret/bundle inspection, `openspec validate ai-provider-nvidia-nim-standardization --type change`, and `git diff --check`.

## 6. Story Review Persistence and Comparison

- [x] 6.1 Review and manually apply `DATABASE/migrations/20260618_story_review_system.sql` to the exact database returned by the Website runtime's `SELECT DATABASE()`; verify `ucp_character_stories` exists in that schema before import and verify `ucp_story_reviews` and `ucp_story_review_matches` there afterward. Inspect any old non-prefixed tables separately and do not drop them automatically.
- [x] 6.2 Load the selected story and character ownership relationship from the database; reject browser-provided story content and invalid identifiers.
- [x] 6.3 Compute word count, character count, content hash, and versioned local similarity against other database stories in bounded batches.
- [x] 6.4 Persist immutable `ucp_story_reviews` rows and ranked `ucp_story_review_matches`, including the threshold and provider/model metadata used.
- [x] 6.5 Mark reviews stale when the stored story hash differs, and create a new row for every re-analysis.
- [x] 6.6 Validate structured NVIDIA scores are numeric and bounded to `0..100`; never let AI output change story status automatically.

## Operator Acknowledgment Before Archive

- Acknowledged on 2026-06-19: one unintended NVIDIA NIM request occurred during missing-key testing because the local test process inherited the private server configuration.
- The request created immutable Story Review record `review_id=6` for `story_id=1`. The record is retained as audit history and must not be deleted or rewritten.
- No provider credential was printed, logged, committed, or added to frontend assets.
- The request did not change the story approval status; manual approval authority remains unchanged.
- The test process was stopped, subsequent failure tests used offline or deliberately invalid provider configuration, and no further live provider request was authorized.

## Final Environment Policy Before Archive

- Approved on 2026-06-19: local and production examples enable NVIDIA NIM Story Review through `AI_ENABLED=true` and `AI_STORY_REVIEW_ENABLED=true` when a valid private server-side key is configured.
- Runtime source defaults remain fail-safe; credentials remain blank in tracked examples, fallback remains disabled, and invalid or missing configuration fails closed.
- Rate limits, privacy-safe logging, strict response validation, deterministic local plagiarism, immutable history, and manual story approval authority remain required.
- Pre-launch local testing may use the configured `arivena` development database and real external services. After launch, a separate local/dev database is required, and production player data must not be used for destructive testing.
- Local SMTP/OTP requires PHPMailer plus private SMTP credentials.
- Website Discord OAuth/guild settings use private `.env` values first through the standardized `DISCORD_*` names, with existing `ucp_system_settings` values retained as fallback and diagnostics restricted to presence/source/readiness metadata.
- Website DB, SMTP, Discord, and AI settings use one environment bootstrap that resolves `WEBSITE/.env` for repository `public/api` execution and `<deployment-root>/.env` for flattened `api` deployments; bootstrap diagnostics expose paths/status only.
