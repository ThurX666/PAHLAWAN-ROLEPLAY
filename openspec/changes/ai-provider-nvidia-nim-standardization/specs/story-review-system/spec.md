## ADDED Requirements

### Requirement: Story Review is the only initially approved NVIDIA NIM feature
The Website/UCP SHALL use NVIDIA NIM only for the Admin Panel Story Review task in the initial implementation and MUST NOT expose chat, free-form prompt, or player-facing AI functionality.

#### Scenario: Unsupported AI feature
- **WHEN** a client requests chat, arbitrary completion, or another unapproved AI task
- **THEN** the backend rejects the request before provider execution

### Requirement: Story analysis uses database-loaded content
The backend MUST load the selected story from `ucp_character_stories` after authenticating and authorizing the admin. It MUST NOT analyze story text supplied only by browser state.

#### Scenario: Analyze persisted story
- **WHEN** an admin level 5 or higher requests `analyze_story` with a valid story identifier
- **THEN** the backend loads the current story and character identifiers from the database
- **AND** uses that stored content for deterministic metrics and NVIDIA NIM analysis

#### Scenario: Client supplies story content
- **WHEN** an analysis request includes browser-supplied story text
- **THEN** the backend rejects or ignores that field
- **AND** no client-supplied text replaces the database record

### Requirement: Story analysis produces bounded review metrics
Each completed review SHALL contain word count, character count, readability score, grammar score, roleplay quality score, plagiarism score, and overall score. All score fields MUST be normalized to `0..100`.

#### Scenario: Valid completed analysis
- **WHEN** deterministic analysis and the NVIDIA rubric complete successfully
- **THEN** the backend persists all required counts and scores
- **AND** returns the normalized persisted review

#### Scenario: Invalid provider score
- **WHEN** NVIDIA NIM returns a missing, non-numeric, or out-of-range score
- **THEN** the backend rejects the provider result as invalid
- **AND** does not persist a partial completed review

### Requirement: Plagiarism comparison uses existing database stories
The backend SHALL compare the selected story against other `ucp_character_stories` records using a versioned deterministic server-side algorithm, excluding the selected story.

#### Scenario: Similar stories found
- **WHEN** comparison produces candidate matches
- **THEN** the backend stores ranked similarity percentages and matched story identifiers
- **AND** returns the configured top matches through `get_story_matches`

#### Scenario: Threshold classification
- **WHEN** a match similarity is at or above the configured threshold
- **THEN** the response marks the match as flagged
- **AND** the threshold used is preserved with the parent review

#### Scenario: Provider privacy boundary
- **WHEN** plagiarism comparison runs
- **THEN** comparison stories remain within the UCP server and database boundary
- **AND** they are not sent to NVIDIA NIM

### Requirement: Review history is immutable and detects stale content
The system SHALL insert a new review for every completed re-analysis and SHALL retain prior reviews. Each review MUST store a hash of the analyzed story content.

#### Scenario: Story changed after review
- **WHEN** the current database story hash differs from the review hash
- **THEN** `get_story_review` identifies the review as stale
- **AND** the Admin Panel offers Re-Analyze Story

#### Scenario: Re-analysis
- **WHEN** an authorized admin re-analyzes a story
- **THEN** a new review and new match rows are created
- **AND** earlier review records remain unchanged

### Requirement: Story Review API is task-oriented and admin-only
The backend SHALL expose `analyze_story`, `get_story_review`, and `get_story_matches` actions and MUST authorize each action with the existing admin session at minimum level 5.

#### Scenario: Unauthorized request
- **WHEN** an unauthenticated user or an account below admin level 5 invokes a Story Review action
- **THEN** the request is rejected before database analysis or provider execution

#### Scenario: Review retrieval
- **WHEN** an authorized admin requests a review or its matches
- **THEN** the backend returns only normalized review data and joined display metadata
- **AND** does not expose provider credentials, trusted prompts, or raw provider responses

### Requirement: AI review remains advisory
Story Review results MUST NOT automatically change `ucp_character_stories.status` or `player_characters.story_status`.

#### Scenario: Analysis completes
- **WHEN** a review is persisted
- **THEN** the existing manual Active, Revision, and Rejected controls remain authoritative
- **AND** no story status changes until an authorized admin performs the existing review action

#### Scenario: Provider unavailable
- **WHEN** NVIDIA NIM is disabled or unavailable
- **THEN** the Admin Panel shows a safe unavailable or retry state
- **AND** manual story review remains usable

### Requirement: Admin Panel exposes explicit review states
The Admin Stories detail view SHALL provide Analyze Story, Re-Analyze Story, View Analysis, and View Similar Stories interactions backed by persisted server data.

#### Scenario: No review exists
- **WHEN** an authorized admin opens a story without a persisted review
- **THEN** the UI offers Analyze Story

#### Scenario: Review exists
- **WHEN** a current review exists
- **THEN** the UI displays all required metrics, notes, provider/model metadata, reviewer, and timestamp
- **AND** offers Re-Analyze Story and View Similar Stories
