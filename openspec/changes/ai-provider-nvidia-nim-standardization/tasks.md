## 0. Story Review Planning Package

- [x] 0.1 Audit `ucp_character_stories`, player story submission, Admin Stories review flow, admin authorization, and existing browser-only mock analysis.
- [x] 0.2 Select Story Review as the first bounded Website/UCP NVIDIA NIM task and define its server-loaded-input and human-review boundaries.
- [x] 0.3 Define `analyze_story`, `get_story_review`, and `get_story_matches` contracts and the Analyze/Re-Analyze/View Analysis/View Similar Stories UI states.
- [x] 0.4 Generate an unexecuted SQL migration for `story_reviews` and `story_review_matches` and align the tracked story schema reference.
- [x] 0.5 Add Story Review capability requirements and validation scenarios to this change.

## 1. Configuration and Contract

- [ ] 1.1 For the selected Story Review task and admin level 5 role, approve the NVIDIA NIM model, request limits, and production rate/token budgets before enabling provider traffic.
- [ ] 1.2 Document server-only AI configuration for local/development and production, including preferred `nvidia` selection, blank secret placeholders, model/endpoint settings, timeouts, output bounds, rate limits, and disabled-by-default fallback.
- [ ] 1.3 Define shared message and option types for `sendMessage(messages, options)`, including normalized output and error categories compatible with the Discord bot contract.
- [ ] 1.4 Add configuration validation that rejects unsupported providers, unsafe endpoints, missing required production settings, and any attempt to source provider credentials from frontend-visible variables.

## 2. Website/UCP Provider Gateway

- [ ] 2.1 Implement the server-side provider interface and NVIDIA NIM adapter using the approved OpenAI-compatible endpoint, with provider-specific request/response normalization contained inside the adapter.
- [ ] 2.2 Implement authenticated `analyze_story`, `get_story_review`, and `get_story_matches` actions using the existing session/auth flow and `ucp_require_admin(5)`.
- [ ] 2.3 Enforce per-task authorization, input/output limits, timeouts, account and task rate limits, and appropriate IP/session abuse controls before provider execution.
- [ ] 2.4 Add structured privacy-aware logging for request IDs, task, provider, model, actor reference, latency, result category, usage metadata, validation failures, and rate-limit events without logging secrets or full content by default.
- [ ] 2.5 Implement bounded retry classification, safe provider error mapping, deterministic unavailable states, and optional explicit per-task fallback that remains disabled unless fully configured.
- [ ] 2.6 Add local disabled/mock behavior that permits UI development without live credentials and production checks that fail safely when AI configuration is incomplete.

## 3. Website Frontend Integration

- [ ] 3.1 Implement a provider-neutral frontend API adapter that calls the authenticated UCP AI gateway and satisfies the existing Website `sendMessage(messages, options)` service boundary without accepting provider credentials or endpoints.
- [ ] 3.2 Replace Admin Stories browser mock analysis with Analyze Story, Re-Analyze Story, View Analysis, and View Similar Stories states while preserving manual status actions.
- [ ] 3.3 Verify Website dependencies and generated frontend assets contain no browser-side NVIDIA, OpenAI, Groq, Google GenAI, or equivalent provider SDK usage and no provider credentials.

## 4. Discord Bot Compatibility

- [ ] 4.1 Compare the Website gateway message roles, option semantics, normalized string result, and error handling with `BOT/PHRP-AI/utils/aiProvider.js`.
- [ ] 4.2 Document any compatibility adapter needed for runtime-specific configuration while leaving the bot's active provider, model, configuration files, and runtime behavior unchanged.

## 5. Validation and Operational Tests

- [ ] 5.1 Test authenticated success, unauthenticated rejection, unauthorized task access, malformed and oversized input rejection, and unsupported client-supplied provider controls.
- [ ] 5.2 Test per-account/task rate limiting and confirm rejected traffic does not call NVIDIA NIM.
- [ ] 5.3 Test timeout, retryable failure, non-retryable failure, missing configuration, fallback-disabled, and explicitly configured fallback behavior without exposing provider details.
- [ ] 5.4 Verify logs contain required operational metadata while excluding credentials, authorization/session data, full prompts, and full responses.
- [ ] 5.5 Run the Website production build, relevant backend checks, secret/bundle inspection, `openspec validate ai-provider-nvidia-nim-standardization --type change`, and `git diff --check`.

## 6. Story Review Persistence and Comparison

- [ ] 6.1 Review and manually apply `20260618_story_review_system.sql`; do not add it to automatic migration execution.
- [x] 6.2 Load the selected story and character ownership relationship from the database; reject browser-provided story content and invalid identifiers.
- [x] 6.3 Compute word count, character count, content hash, and versioned local similarity against other database stories in bounded batches.
- [x] 6.4 Persist immutable `story_reviews` rows and ranked `story_review_matches`, including the threshold and provider/model metadata used.
- [x] 6.5 Mark reviews stale when the stored story hash differs, and create a new row for every re-analysis.
- [ ] 6.6 Validate structured NVIDIA scores are numeric and bounded to `0..100`; never let AI output change story status automatically.
