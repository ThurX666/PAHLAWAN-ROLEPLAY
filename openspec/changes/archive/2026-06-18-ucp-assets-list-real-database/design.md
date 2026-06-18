## Context

The existing asset list route partially queries real tables but maps unconfirmed columns into misleading UI fields. Asset detail responses remain simulated and are intentionally outside this change.

## Goals / Non-Goals

**Goals:**

- Return real, safe list data for houses, businesses, and families.
- Preserve the current JSON shape with explicit safe fallbacks.
- Keep the frontend null-safe.

**Non-Goals:**

- Asset detail integration.
- Schema changes, database writes, migrations, Pawn changes, or mock-file cleanup.

## Decisions

- Keep `api_overview.php?action=assets` as the integration point to minimize surface area.
- Validate asset type through an allowlist and use read-only SELECT statements.
- Prefer `null` or `"Unknown"` over invented values when schema fields are unconfirmed.
- Return only explicitly selected columns; do not use `SELECT *`.
- Adjust `AssetList.tsx` only where null-safe loading, error, or empty rendering requires it.

## Risks / Trade-offs

- [Live schema remains unverified] → Restrict queries to columns confirmed by existing PHP/Pawn references and return safe API errors.
- [House price and lock fields are unknown] → Return null rather than deriving them from `Type`.
- [Family level is unknown] → Return null.
- [Business location may lack a label] → Use confirmed coordinates or `"Unknown"`.
