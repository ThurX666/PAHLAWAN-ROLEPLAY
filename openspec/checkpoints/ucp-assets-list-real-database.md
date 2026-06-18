# ucp-assets-list-real-database Checkpoint

## What Was Implemented

- Added read-only asset list integration for houses, businesses, and families through `api_overview.php?action=assets`.
- Preserved the existing frontend list response shape with safe `null` and `"Unknown"` fallbacks for unconfirmed fields.
- Kept the scope limited to asset list behavior only, without asset detail changes, gamemode changes, migrations, or database writes.

## Files Changed

- `WEBSITE/public/api/api_overview.php`
- `WEBSITE/src/components/admin/assets/AssetList.tsx`
- `openspec/specs/ucp-asset-lists/spec.md`
- `openspec/changes/archive/2026-06-18-ucp-assets-list-real-database/`

## Verification Results

- PHP lint passed with `C:\xampp\php\php.exe -l WEBSITE/public/api/api_overview.php`
- `vite build` passed
- `git diff --check` passed
- OpenSpec validation passed before archive and after archive
- OpenSpec archive completed successfully on `2026-06-18`

## Runtime Smoke Test Limitation

- Manual browser/API smoke test is still unconfirmed.
- The previous request URL returned `404 Not Found`: `http://127.0.0.1/WEBSITE/public/api/api_overview.php?...`
- The likely issue is Apache/XAMPP web root mapping, not a confirmed code error.
- The correct runtime URL depends on where `WEBSITE/public` is actually served from in the local Apache setup.

## Manual Runtime Test Instructions

- Determine the real local base URL for `WEBSITE/public`.
- Then test:
- `<base-url>/api/api_overview.php?action=assets&type=houses`
- `<base-url>/api/api_overview.php?action=assets&type=businesses`
- `<base-url>/api/api_overview.php?action=assets&type=families`
- Expected result: JSON response, no PHP warnings leaked, no sensitive fields, and safe error handling if a table or column is missing.

## Next Recommended OpenSpec Change

- Start a separate OpenSpec change for runtime validation and any follow-up fixes only after the correct local web root mapping is confirmed.
