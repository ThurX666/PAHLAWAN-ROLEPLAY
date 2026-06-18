## ADDED Requirements

### Requirement: NVIDIA NIM is the preferred AI provider
PAHLAWAN ROLEPLAY AI architecture SHALL designate NVIDIA NIM as the preferred provider while preserving a provider-neutral adapter boundary.

#### Scenario: Default provider direction
- **WHEN** a new Website/UCP AI feature or deployment configuration is documented
- **THEN** NVIDIA NIM is identified as the preferred provider
- **AND** callers depend on the provider-neutral adapter rather than NVIDIA-specific request code

### Requirement: AI provider credentials remain server-side
The system MUST load provider credentials only in trusted server-side runtimes and MUST NOT expose them through frontend source, frontend environment variables, bundles, API responses, logs, or committed configuration examples.

#### Scenario: Frontend production build
- **WHEN** the Website frontend is built for any environment
- **THEN** the resulting browser assets contain no NVIDIA, OpenAI, Groq, or other provider credential
- **AND** no provider secret is supplied through a `VITE_` variable

#### Scenario: Configuration example
- **WHEN** AI environment/configuration documentation is committed
- **THEN** provider secret fields are blank or described by name only
- **AND** no usable secret value is included

### Requirement: Website AI requests use an authenticated backend gateway
The Website frontend SHALL send AI feature requests to an authenticated Website/UCP backend gateway and MUST NOT call NVIDIA NIM or another model provider directly.

#### Scenario: Authenticated AI request
- **WHEN** an authorized signed-in user invokes an enabled AI feature
- **THEN** the frontend sends a validated task request through the existing UCP authentication/session boundary
- **AND** the backend performs the provider call

#### Scenario: Unauthenticated AI request
- **WHEN** a request reaches the AI gateway without a valid authenticated session
- **THEN** the gateway rejects it before any provider request is made

### Requirement: Gateway uses a bot-compatible provider contract
The server-side gateway provider abstraction SHALL support `sendMessage(messages, options)` with ordered role/content messages and bounded provider-neutral options, returning normalized text or a normalized failure.

#### Scenario: NVIDIA adapter invocation
- **WHEN** the gateway dispatches an approved task to NVIDIA NIM
- **THEN** it invokes an adapter compatible with `sendMessage(messages, options)`
- **AND** provider-specific request and response details remain inside the adapter

#### Scenario: Bot compatibility review
- **WHEN** the Website gateway contract is implemented
- **THEN** its message ordering, role/content shape, option naming semantics, and string response are compared with the Discord bot provider contract
- **AND** compatibility differences are documented without changing bot runtime behavior

### Requirement: Public gateway requests are task-oriented and constrained
The gateway MUST accept only allowlisted AI task identifiers and validated task inputs, while trusted prompts and unrestricted provider controls remain server-owned.

#### Scenario: Supported task
- **WHEN** an authorized request names an enabled task with valid bounded input
- **THEN** the server constructs trusted messages and approved options for that task

#### Scenario: Provider control injection
- **WHEN** a client attempts to set a provider key, provider endpoint, arbitrary system message, unsupported model, or unbounded generation option
- **THEN** the gateway rejects or ignores the field according to its validation contract
- **AND** no unsafe value reaches the provider adapter

### Requirement: Provider switching is controlled through server configuration
The system SHALL allow the active provider, model, approved endpoint, and operational limits to be selected through server-side environment/configuration without requiring a frontend code change.

#### Scenario: Explicit provider selection
- **WHEN** an operator selects a supported provider through valid server configuration
- **THEN** the gateway resolves the corresponding adapter
- **AND** the frontend request contract remains unchanged

#### Scenario: Unsupported provider selection
- **WHEN** server configuration names an unsupported provider
- **THEN** configuration validation fails safely or the AI feature remains disabled
- **AND** the system does not silently route to an unspecified provider

### Requirement: Website NVIDIA defaults align with Discord Bot/PHRP-AI
The Website/UCP NVIDIA adapter SHALL default to the audited Discord Bot/PHRP-AI NVIDIA configuration: base URL `https://integrate.api.nvidia.com/v1` and model `deepseek-ai/deepseek-v4-flash`. Website/UCP MUST keep its credentials and runtime configuration server-side and MUST NOT modify or depend on Bot configuration files at runtime.

#### Scenario: Default Website NVIDIA configuration
- **WHEN** Website/UCP Story Review is configured for NVIDIA without an explicitly approved model or endpoint override
- **THEN** the server uses `https://integrate.api.nvidia.com/v1`
- **AND** uses `deepseek-ai/deepseek-v4-flash`

#### Scenario: Explicit server-side override
- **WHEN** an operator configures a supported and explicitly approved provider, model, or endpoint override on the Website/UCP server
- **THEN** the gateway may use that override without a frontend code change
- **AND** no provider control or credential is exposed to the browser

#### Scenario: Bot runtime isolation
- **WHEN** Website/UCP loads or changes its AI runtime configuration
- **THEN** it does not read, write, or mutate `BOT/PHRP-AI/config/app.json` at runtime
- **AND** Discord Bot provider behavior remains unchanged

### Requirement: Gateway enforces rate limits and abuse controls
The gateway MUST apply authorization, input limits, output limits, timeout limits, and rate limits before or during provider execution, with controls scoped by task and authenticated actor and supplemented by IP/session controls where appropriate.

#### Scenario: Rate limit exceeded
- **WHEN** an actor exceeds the configured limit for an AI task
- **THEN** the gateway rejects the request without calling the provider
- **AND** returns a stable retry-later response without exposing internal limits unnecessarily

#### Scenario: Oversized or malformed input
- **WHEN** task input is malformed, unsupported, or exceeds configured bounds
- **THEN** the gateway rejects it before provider execution
- **AND** records a safe validation or abuse event

#### Scenario: Privileged task authorization
- **WHEN** a user without the required role invokes an administrative or review-oriented AI task
- **THEN** the gateway denies the request before provider execution

### Requirement: AI logging is operational and privacy-aware
The gateway SHALL produce structured operational logs sufficient to diagnose availability, latency, rate limiting, and provider failures while excluding credentials, session secrets, and full prompt or response content by default.

#### Scenario: Completed provider request
- **WHEN** a provider request completes
- **THEN** the system logs request metadata including request ID, task, provider, model identifier, latency, result category, and available usage metadata
- **AND** does not log provider credentials or full content by default

#### Scenario: Provider error
- **WHEN** a provider request fails
- **THEN** the system logs a normalized error category and correlation metadata
- **AND** redacts authorization data, provider error secrets, prompts, and responses

### Requirement: Provider unavailability fails safely
The gateway MUST use bounded timeouts and retries, MUST return user-safe errors, and MUST provide deterministic feature degradation when the provider is unavailable.

#### Scenario: Transient NVIDIA failure
- **WHEN** NVIDIA NIM returns a retryable transient failure
- **THEN** the adapter performs no more than the configured bounded retries with backoff
- **AND** stops when the timeout or retry budget is exhausted

#### Scenario: Non-retryable provider failure
- **WHEN** the provider returns an authentication, invalid-request, policy, or quota failure classified as non-retryable
- **THEN** the gateway does not retry blindly
- **AND** returns a normalized unavailable or configuration error without exposing provider details

#### Scenario: Fallback is not configured
- **WHEN** NVIDIA NIM is unavailable and no approved fallback provider is explicitly configured
- **THEN** the task fails closed or returns its deterministic unavailable state
- **AND** no alternate provider is selected implicitly

#### Scenario: Approved fallback is configured
- **WHEN** NVIDIA NIM is unavailable and the environment and task explicitly authorize a configured fallback provider
- **THEN** the gateway may invoke that provider through the same adapter contract
- **AND** records that fallback occurred without exposing credentials

### Requirement: Local and production AI configuration are distinct and documented
The project SHALL document safe local/development and production expectations for AI configuration.

#### Scenario: Local development without credentials
- **WHEN** a developer runs the Website/UCP locally without a provider credential
- **THEN** AI features remain disabled or use an explicit deterministic mock/stub
- **AND** no browser credential or committed secret is required

#### Scenario: Production configuration
- **WHEN** AI is enabled in production
- **THEN** provider credentials are injected outside the repository
- **AND** authentication, TLS, provider/model validation, timeouts, output bounds, rate limits, logging, and safe failure behavior are enabled

### Requirement: Browser-side AI SDK dependencies are prohibited
The Website frontend MUST NOT depend on provider AI SDKs for model access.

#### Scenario: Frontend dependency review
- **WHEN** Website dependencies and imports are reviewed after AI gateway implementation
- **THEN** no NVIDIA, OpenAI, Groq, Google GenAI, or equivalent browser-side provider SDK is used to call a model
- **AND** frontend AI features use the authenticated UCP API client path
