# ucp-asset-lists Specification

## Purpose
TBD - created by archiving change ucp-assets-list-real-database. Update Purpose after archive.
## Requirements
### Requirement: House list uses confirmed database data
The system SHALL read house list records from `houses`, SHALL NOT treat `Type` as price, and SHALL return `price: null` and `locked: null` when those columns are not confirmed. Location SHALL use confirmed coordinates or `"Unknown"`.

#### Scenario: House fields are incomplete
- **WHEN** a house record has no confirmed price, lock, or display-location column
- **THEN** the API returns the real ID and owner with safe null or `"Unknown"` fallbacks

### Requirement: Business list exposes safe fields only
The system SHALL read business list records from `biz` and expose only ID, name, owner, type, price, money or balance, and a safe location. Auction, employee, product, and private internal fields MUST NOT be returned.

#### Scenario: Business list request succeeds
- **WHEN** an authorized admin requests the business asset list
- **THEN** the API returns only the approved safe business fields

### Requirement: Family list hides private financial data
The system SHALL read family list records from `families`, SHALL expose safe identity and bank fields, SHALL NOT expose `DirtyMoney`, and SHALL return `level: null` when no level column is confirmed.

#### Scenario: Family has no confirmed level
- **WHEN** a family record is returned without a confirmed level column
- **THEN** the response contains `level: null` and no dirty-money value

### Requirement: Asset list UI is null-safe
The frontend MUST preserve the existing list response shape and MUST render loading, error, empty, null, and unknown values without crashing.

#### Scenario: API returns null fields
- **WHEN** price, locked, level, or location is null or unknown
- **THEN** the list renders a safe placeholder and remains usable

### Requirement: Integration remains read-only and scoped
The implementation MUST use read-only queries and MUST NOT add asset details, migrations, database writes, gamemode changes, secret output, or file deletion.

#### Scenario: Change is implemented
- **WHEN** the asset list patch is applied
- **THEN** only the approved list API and necessary list UI code are changed

