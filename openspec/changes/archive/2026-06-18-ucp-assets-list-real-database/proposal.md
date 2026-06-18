## Why

The UCP asset overview still returns incomplete or misleading values for houses, businesses, and families. The list endpoints need a small read-only integration that reflects confirmed database fields without inventing unavailable data.

## What Changes

- Read house, business, and family list data from their existing database tables.
- Preserve the current frontend response shape with explicit null or `"Unknown"` fallbacks for unconfirmed fields.
- Add null-safe loading, error, and empty rendering where the existing asset list requires it.
- Exclude asset details, database writes, migrations, gamemode changes, and file deletion.

## Capabilities

### New Capabilities

- `ucp-asset-lists`: Read-only UCP list views for houses, businesses, and families using confirmed safe database fields.

### Modified Capabilities

None.

## Impact

- Primary API: `WEBSITE/public/api/api_overview.php`
- Optional frontend adjustment: `WEBSITE/components/admin/overview/AssetList.tsx`
- Existing tables: `houses`, `biz`, and `families`
- No schema, Pawn, bot, or asset-detail changes
