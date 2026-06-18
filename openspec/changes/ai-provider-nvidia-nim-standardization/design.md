## Context

The Discord bot already contains an AI provider abstraction with Groq, OpenAI, NVIDIA NIM, and custom adapters. Its NVIDIA implementation uses NVIDIA's OpenAI-compatible endpoint and the public provider contract is `sendMessage(messages, options) -> Promise<string>`.

The Website frontend previously contained dormant `@google/genai` usage. Task 2.3 of `ucp-frontend-bundle-optimization` removed that dependency and left a provider-neutral TypeScript interface with the same `sendMessage(messages, options)` shape. The frontend currently has no configured provider, which is the correct safe state until an authenticated backend gateway exists.

This design covers a future PHP UCP gateway and shared provider conventions. It must preserve UCP authentication and session security, keep provider credentials outside the browser, avoid changes to current bot runtime behavior, and avoid gamemode or database changes.

## Goals / Non-Goals

**Goals:**

- Make NVIDIA NIM the preferred provider for new PAHLAWAN ROLEPLAY AI features.
- Define a server-side Website/UCP gateway that authenticates and authorizes every AI request.
- Keep the internal provider adapter compatible with `sendMessage(messages, options)`.
- Keep provider, model, endpoint, timeout, and fallback choices configurable without frontend changes.
- Define rate limiting, abuse controls, logging, privacy, failure behavior, and environment documentation.
- Preserve the ability to add or select another provider through explicit server configuration.

**Non-Goals:**

- Implementing the Website/UCP gateway or connecting existing UI features.
- Changing the Discord bot's active provider, model, configuration format, or runtime behavior.
- Adding browser-side AI SDKs or exposing raw provider credentials.
- Modifying gamemode/Pawn, database schema, migrations, or database data.
- Defining provider-specific billing commitments or selecting final production quotas.

## Decisions

### 1. NVIDIA NIM is preferred, while the adapter boundary remains provider-neutral

New deployments SHALL default their documented provider direction to `nvidia`. The gateway implementation will resolve a server-side provider adapter and call:

```text
sendMessage(messages, options) -> string
```

`messages` uses ordered `{ role, content }` records. `options` carries bounded provider-neutral controls such as task identifier, model override where authorized, maximum output tokens, temperature, response format, timeout, and request metadata. Provider-specific fields must remain inside the NVIDIA adapter rather than leaking into callers.

This matches the bot's existing abstraction and permits later provider switching through configuration. Direct NVIDIA calls from React were rejected because they expose credentials, bypass UCP authorization, and duplicate provider logic in the browser.

### 2. The browser calls a task-oriented authenticated UCP endpoint

The frontend will call a same-origin or explicitly allowed UCP API endpoint using the existing authenticated session flow. The public HTTP request will identify an allowlisted AI task and provide validated task input. The server will build trusted system instructions and translate the request into `sendMessage(messages, options)`.

The browser will not be allowed to choose a provider, supply a provider key, set an arbitrary base URL, inject trusted system messages, or request unrestricted model parameters. A raw provider proxy was rejected because it would weaken authorization and abuse controls.

### 3. Credentials and provider configuration are server-side only

The Website/UCP runtime will read AI settings from non-public server environment/config. Documentation will define names equivalent to:

- `AI_PROVIDER=nvidia`
- `NVIDIA_NIM_API_KEY` with no example value
- `AI_MODEL`
- `AI_BASE_URL` defaulting internally to the approved NVIDIA NIM endpoint
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

## Risks / Trade-offs

- [A generic adapter can expose unsafe model controls] → Keep public requests task-oriented and enforce server-owned option allowlists and bounds.
- [Automatic provider fallback can change output quality or policy behavior] → Disable it by default and require explicit per-environment and per-task configuration.
- [Logging AI content can expose private roleplay applications or user data] → Log metadata by default and redact or omit request/response bodies.
- [In-memory rate limiting is not globally consistent across multiple instances] → Treat it as the no-schema baseline and use infrastructure controls or a separately approved shared store for scaled production.
- [Bot and Website configuration formats differ] → Standardize the adapter contract first and preserve runtime-specific config readers behind it.
- [NVIDIA's OpenAI-compatible behavior can differ by model] → Keep model defaults and provider-specific response normalization inside the NVIDIA adapter and validate the selected model in implementation.

## Migration Plan

1. Add server-side AI configuration documentation and safe example variable names with blank secret values.
2. Implement a PHP provider interface and NVIDIA NIM adapter behind `sendMessage(messages, options)`.
3. Implement authenticated, task-oriented UCP gateway routing with validation, authorization, rate limiting, logging, timeouts, and safe error mapping.
4. Add local mock/disabled behavior and production configuration validation.
5. Connect one bounded Website feature to the gateway without adding browser AI SDKs.
6. Verify secret scanning, frontend bundle contents, auth/session behavior, abuse controls, and provider-unavailable behavior.
7. Separately evaluate a bot configuration adapter only if alignment is needed; do not change its active runtime behavior as part of the initial Website implementation.

Rollback consists of disabling the affected AI task or gateway through server configuration and returning the deterministic unavailable state. No database rollback is required.

## Open Questions

- Which first Website/UCP AI task will be implemented and which account roles may invoke it?
- What production rate and token budgets are approved per task?
- Should production use application-level limiting, reverse-proxy limiting, or an existing shared cache before multi-instance deployment?
- Which NVIDIA NIM model will be the production default after capability, latency, and cost validation?
- Is any cross-provider fallback approved for production, or should all initial tasks fail closed when NVIDIA NIM is unavailable?
