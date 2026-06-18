## Context

The Discord bot already contains an AI provider abstraction with Groq, OpenAI, NVIDIA NIM, and custom adapters. Its NVIDIA implementation uses the OpenAI-compatible base URL `https://integrate.api.nvidia.com/v1`, and `BOT/PHRP-AI/config/app.json` currently selects provider `nvidia` with model `deepseek-ai/deepseek-v4-flash`. Its public provider contract is `sendMessage(messages, options) -> Promise<string>`.

The Website frontend previously contained dormant `@google/genai` usage. Task 2.3 of `ucp-frontend-bundle-optimization` removed that dependency and left a provider-neutral TypeScript interface with the same `sendMessage(messages, options)` shape. The frontend currently has no configured provider, which is the correct safe state until an authenticated backend gateway exists.

This design covers a future PHP UCP gateway, shared provider conventions, and the first bounded feature: Admin Panel Story Review. It must preserve UCP authentication and session security, keep provider credentials outside the browser, avoid changes to current bot runtime behavior and gamemode, and keep database changes limited to generated, unexecuted SQL.

## Goals / Non-Goals

**Goals:**

- Make NVIDIA NIM the preferred provider for new PAHLAWAN ROLEPLAY AI features.
- Default Website/UCP Story Review to the same NVIDIA NIM base URL and model currently selected by Discord Bot/PHRP-AI.
- Define a server-side Website/UCP gateway that authenticates and authorizes every AI request.
- Keep the internal provider adapter compatible with `sendMessage(messages, options)`.
- Keep provider, model, endpoint, timeout, and fallback choices configurable without frontend changes.
- Define rate limiting, abuse controls, logging, privacy, failure behavior, and environment documentation.
- Preserve the ability to add or select another provider through explicit server configuration.
- Load story content from `ucp_character_stories` on the server using an authorized story identifier.
- Persist immutable analysis history and database-derived plagiarism matches for admin review.

**Non-Goals:**

- Implementing the Website/UCP gateway or connecting existing UI features.
- Changing the Discord bot's active provider, model, configuration format, or runtime behavior.
- Adding browser-side AI SDKs or exposing raw provider credentials.
- Modifying gamemode/Pawn or database data.
- Executing migrations or implementing live NVIDIA NIM calls in this planning step.
- Building chat assistants, free-form prompting, player-facing AI, or automatic story approval.
- Defining provider-specific billing commitments or selecting final production quotas.

## Current Story Review Audit

- Story text is stored in `ucp_character_stories.content`, keyed by `id` and linked to `player_characters.pID` through `character_id`.
- Player submission uses `api_stories_upload.php`, enforces ownership plus a 300-word/3-paragraph minimum, upserts one story per character in application logic, and sets both story and character status to Pending.
- Admin review uses `AdminStories.tsx` and `api_admin_stories.php`, requires admin level 5, lists all stories, and manually applies Active, Revision, or Rejected with feedback and inbox/admin-log side effects.
- The current Admin Stories “AI Analysis” is browser-only: mock story records, randomized Jaccard plagiarism scoring, basic punctuation/capitalization checks, and no persisted review history.
- The repository dump and original `stories_sql.txt` omitted `ucp_character_stories.username`, while upload and admin-review code already insert/select it. The tracked schema reference is now aligned, and the generated manual migration adds and backfills this compatibility column.
- `story_sql.txt` is a divergent legacy schema draft containing `photo_path` and a non-persisted plagiarism column; it is not treated as the canonical migration source for this feature.

## Decisions

### 1. NVIDIA NIM is preferred, while the adapter boundary remains provider-neutral

New deployments SHALL default their documented provider direction to `nvidia`. The gateway implementation will resolve a server-side provider adapter and call:

```text
sendMessage(messages, options) -> string
```

`messages` uses ordered `{ role, content }` records. `options` carries bounded provider-neutral controls such as task identifier, model override where authorized, maximum output tokens, temperature, response format, timeout, and request metadata. Provider-specific fields must remain inside the NVIDIA adapter rather than leaking into callers.

This matches the bot's existing abstraction and permits later provider switching through configuration. Direct NVIDIA calls from React were rejected because they expose credentials, bypass UCP authorization, and duplicate provider logic in the browser.

For the initial Website/UCP Story Review implementation, the audited Discord Bot/PHRP-AI NVIDIA configuration is the default configuration baseline:

- base URL: `https://integrate.api.nvidia.com/v1`
- model: `deepseek-ai/deepseek-v4-flash`

Website/UCP must not independently select another default model or base URL. Server operators may still configure an explicitly approved provider, model, or endpoint override without changing frontend code. Website/UCP does not read or mutate `BOT/PHRP-AI/config/app.json` at runtime, and this alignment does not change Discord Bot behavior.

### 2. The browser calls a task-oriented authenticated UCP endpoint

The frontend will call a same-origin or explicitly allowed UCP API endpoint using the existing authenticated session flow. The public HTTP request will identify an allowlisted AI task and provide validated task input. The server will build trusted system instructions and translate the request into `sendMessage(messages, options)`.

The browser will not be allowed to choose a provider, supply a provider key, set an arbitrary base URL, inject trusted system messages, or request unrestricted model parameters. A raw provider proxy was rejected because it would weaken authorization and abuse controls.

### 3. Credentials and provider configuration are server-side only

The Website/UCP runtime will read AI settings from non-public server environment/config. Documentation will define names equivalent to:

- `AI_PROVIDER=nvidia`
- `NVIDIA_NIM_API_KEY` with no example value
- `AI_STORY_REVIEW_MODEL`, defaulting to `deepseek-ai/deepseek-v4-flash`
- `AI_BASE_URL`, defaulting to `https://integrate.api.nvidia.com/v1`
- `AI_TIMEOUT_MS`, output-token limits, and rate-limit settings
- optional fallback provider settings, disabled unless explicitly configured

No provider key may use the `VITE_` prefix, be emitted into frontend bundles, be returned by config endpoints, or be committed in examples. The bot may retain its current configuration during this change; a later implementation may align names through a compatibility adapter without changing the public contract.

### 4. Local/development and production fail safely

Local development may run with AI disabled and deterministic mock/stub responses for UI development. Live NVIDIA calls require an explicitly supplied server-side credential and must never be silently enabled from frontend configuration.

Production requires an authenticated gateway, a configured provider and model, secret injection outside the repository, TLS at the public boundary, bounded timeouts and output sizes, rate limits, and operational logging. Missing or invalid production configuration disables the AI feature or fails startup/config validation according to the hosting model; it must not fall back to a browser key or embedded credential.

### 5. The gateway owns rate limiting and abuse controls

Every task will have server-defined input size, output size, model, temperature, and timeout bounds. Requests will be rate-limited by authenticated account and, where appropriate, IP/session and task. Authorization will restrict administrative or review-oriented tasks to eligible roles. The gateway will reject malformed requests, unsupported tasks, prompt-control fields, excessive payloads, and repeated abusive traffic before calling the provider.

Initial implementation must use controls that do not require a database schema change, such as application/runtime or infrastructure rate limiting. Persistent quota storage requires a separate approved change.

### 6. Logging is structured and privacy-aware

Operational logs will record request ID, task, provider, configured model identifier, authenticated actor identifier in an appropriate non-secret form, latency, result category, token/usage metadata when available, and rate-limit or provider errors.

Logs must not contain provider credentials, authorization headers, session tokens, full prompts, full model responses, or unnecessary character/application content by default. Any temporary content logging for diagnosis requires explicit development-only configuration and redaction.

### 7. Provider failure uses bounded, explicit fallback behavior

The adapter will apply a bounded timeout and only retry failures classified as transient, with a small configured retry count and backoff. Authentication errors, invalid requests, policy failures, and exhausted quotas will not be retried blindly.

If NVIDIA NIM remains unavailable, the gateway returns a stable internal error category and a user-safe response. Features that can degrade will show deterministic unavailable-state content or preserve manual workflow. Cross-provider fallback is allowed only when a fallback provider and its server-side credentials are explicitly configured and the task is approved for fallback; otherwise the request fails closed. Provider error bodies and credentials must not reach the frontend.

### 8. Browser-side AI SDK dependencies remain prohibited

The Website package must not add NVIDIA, OpenAI, Groq, Google, or other browser AI SDKs for provider access. The frontend dependency surface is limited to the existing application/API client approach. Server-side implementation may use a suitable HTTP client or an OpenAI-compatible server SDK only after dependency and deployment compatibility are reviewed.

### 9. Story Review is the first approved Website/UCP AI task

The first task identifier is `story_review`. It is restricted to the existing Admin Panel story-review role boundary, currently enforced by `ucp_require_admin(5)`. The feature assists a human reviewer and never changes story status automatically.

The browser sends only identifiers and task intent. For analysis, the server accepts a bounded `story_id`, authorizes the admin, loads the current story and character relationship from `ucp_character_stories`, and constructs trusted analysis input. Browser-provided story text is rejected or ignored.

### 10. Analysis combines deterministic metrics with NVIDIA rubric scoring

The server computes word count and character count deterministically from the stored story. Plagiarism similarity is also computed server-side against other `ucp_character_stories` rows, excluding the selected story.

NVIDIA NIM is used only for the story-review rubric: grammar score, readability score, roleplay quality score, overall score, and concise review notes. The trusted prompt requires a strict structured result with each score bounded to `0..100`. The backend validates and normalizes the response before persistence. NVIDIA output is advisory and cannot approve, reject, or revise a story.

The Website/UCP server configuration (`AI_STORY_REVIEW_MODEL`) defaults to the Discord Bot/PHRP-AI model `deepseek-ai/deepseek-v4-flash`, and `AI_BASE_URL` defaults to `https://integrate.api.nvidia.com/v1`. These defaults must be capability-tested for the Story Review rubric before live traffic. An operator may select an explicitly approved override through server configuration, but no model name or endpoint is exposed as a frontend control or embedded in a migration.

### 11. Plagiarism comparison remains local to the database

The initial plagiarism detector normalizes text and calculates a deterministic similarity score for existing stories in bounded batches. Implementation may use token shingles plus Jaccard or cosine similarity, but must document the exact algorithm and version it as `analysis_version`.

Only the selected story is sent to NVIDIA NIM. Existing comparison stories are not sent to the provider. The threshold is server-configured through a setting equivalent to `AI_STORY_PLAGIARISM_THRESHOLD`, defaults to `50.00` until operators approve another value, and is stored with each review. The top five matches above zero similarity are persisted, while the API may label matches at or above the configured threshold as flagged.

### 12. Review history is immutable and detects stale analysis

Each successful analysis inserts a new `ucp_story_reviews` row. Re-analysis does not overwrite earlier reviews. `story_content_hash` records the SHA-256 hash of the analyzed database content so the API and UI can identify a review that predates a story edit.

`ucp_story_review_matches` stores ranked matches for one review. Both UCP-owned tables use the project `ucp_` prefix and are defined by `DATABASE/migrations/20260618_story_review_system.sql`. New tables use indexed logical references to the existing story, character, and UCP account identifiers. The migration avoids new foreign keys to legacy tables because the current schema does not consistently declare relational constraints; the review-to-match relation uses an internal foreign key with restricted deletion.

Older local environments may already contain non-prefixed `story_reviews` and `story_review_matches`. The migration and runtime do not alias, rename, copy, or drop those tables automatically. Operators must inspect row counts and preserve any legacy review data before planning a separate manual transfer or cleanup.

Before applying the prefixed migration, operators must:

1. Confirm the Website-selected schema with `SELECT DATABASE()`.
2. Confirm `ucp_character_stories` exists in that schema.
3. Inspect whether the old non-prefixed tables exist and record their row counts.
4. If either old table contains rows, stop and prepare a separate reviewed data-transfer plan before switching runtime traffic.
5. Import `DATABASE/migrations/20260618_story_review_system.sql`.
6. Verify `ucp_story_reviews` and `ucp_story_review_matches` exist before testing the API.

Old non-prefixed tables may be considered for manual cleanup only after their data is confirmed empty or transferred and the prefixed API path is verified. This change provides no destructive cleanup SQL.

### 13. The public API is task-oriented

A future authenticated endpoint, recommended as `WEBSITE/public/api/api_story_review.php`, exposes only:

- `analyze_story`: `POST` JSON with `story_id` and optional `force`. Returns a completed persisted review or a normalized disabled/unavailable error. A non-forced request may return the latest non-stale review.
- `get_story_review`: `GET` with `story_id` and optional `review_id`. Returns the latest or requested authorized review and an `is_stale` flag.
- `get_story_matches`: `GET` with `review_id`. Returns ranked matches with character display data loaded through joins.

Every action requires `ucp_require_admin(5)`. Responses never include provider credentials, raw provider payloads, trusted prompts, or unrestricted model controls.

### 14. Admin Stories gains explicit analysis states

The existing pending-story detail view will replace browser mock plagiarism and grammar checks with:

- **Analyze Story** when no persisted review exists.
- **Re-Analyze Story** when a review exists or is stale.
- **View Analysis** showing word count, character count, readability, grammar, roleplay, plagiarism, overall score, notes, model metadata, reviewer, and timestamp.
- **View Similar Stories** showing ranked matches and similarity percentages.

Manual Active, Revision, and Rejected actions remain separate. Analysis failure preserves the existing manual workflow and displays a retryable or unavailable state without losing reviewer feedback.

## Risks / Trade-offs

- [A generic adapter can expose unsafe model controls] → Keep public requests task-oriented and enforce server-owned option allowlists and bounds.
- [Automatic provider fallback can change output quality or policy behavior] → Disable it by default and require explicit per-environment and per-task configuration.
- [Logging AI content can expose private roleplay applications or user data] → Log metadata by default and redact or omit request/response bodies.
- [In-memory rate limiting is not globally consistent across multiple instances] → Treat it as the no-schema baseline and use infrastructure controls or a separately approved shared store for scaled production.
- [Bot and Website configuration formats differ] → Standardize the adapter contract first and preserve runtime-specific config readers behind it.
- [NVIDIA's OpenAI-compatible behavior can differ by model] → Keep model defaults and provider-specific response normalization inside the NVIDIA adapter and validate the selected model in implementation.

- [A story may change after analysis] → Store a content hash and mark prior reviews stale rather than presenting them as current.
- [Comparing every story can become expensive] → Use bounded database batches, indexed identifiers, a versioned local algorithm, and a top-match limit.
- [Model output may be malformed or overconfident] → Require strict structured output, validate every score, preserve manual authority, and fail without persisting partial results.

## Migration Plan

1. Add server-side AI configuration documentation and safe example variable names with blank secret values, defaulting the Website NVIDIA model/base URL to the audited Discord Bot/PHRP-AI values.
2. Implement a PHP provider interface and NVIDIA NIM adapter behind `sendMessage(messages, options)`.
3. Implement authenticated, task-oriented UCP gateway routing with validation, authorization, rate limiting, logging, timeouts, and safe error mapping.
4. Add local mock/disabled behavior and production configuration validation.
5. Apply the reviewed `DATABASE/migrations/20260618_story_review_system.sql` migration manually in an approved maintenance window.
6. Implement the Story Review actions, deterministic metrics, local plagiarism comparison, persistence, and admin UI states.
7. Connect only Story Review to NVIDIA NIM without adding browser AI SDKs.
8. Verify secret scanning, frontend bundle contents, auth/session behavior, stale-review behavior, abuse controls, and provider-unavailable behavior.
9. Verify the Website defaults remain aligned with the audited Bot NVIDIA model/base URL while keeping configuration loading independent and leaving Bot files and runtime behavior unchanged.

Rollback consists of disabling the Story Review AI task or gateway through server configuration and returning the deterministic unavailable state. The generated migration includes a commented destructive rollback section; it must never be run automatically because dropping review tables deletes audit history.

## Open Questions

- What production rate and token budgets are approved per task?
- Should production use application-level limiting, reverse-proxy limiting, or an existing shared cache before multi-instance deployment?
- Does `deepseek-ai/deepseek-v4-flash`, inherited from Discord Bot/PHRP-AI as the default, pass the Story Review capability, latency, structured-output, and cost validation required before live traffic?
- Is any cross-provider fallback approved for production, or should all initial tasks fail closed when NVIDIA NIM is unavailable?
- Which exact deterministic similarity algorithm and normalization rules are approved after representative Indonesian story testing?
