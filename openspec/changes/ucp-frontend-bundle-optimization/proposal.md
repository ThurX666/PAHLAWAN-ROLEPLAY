## Why

The UCP production build currently emits a single JavaScript chunk of about 1,254.30 kB minified (`dist/assets/index-*.js`) and triggers Vite's chunk-size warning above 500 kB. The current frontend entry eagerly imports auth, player, donation, ticket, admin, chart, and image-cropping screens into one bundle, so the project needs an approved reduction plan before any code changes are made.

## What Changes

- Document the current Vite production build warning and the single-entry frontend structure that produces it.
- Define a safe bundle-optimization capability for the UCP frontend that preserves existing auth flow, PHP API behavior, and production-visible behavior.
- Identify approved lazy-loading and code-splitting candidates at the tab, page, panel, modal, and heavy-component level.
- Define validation expectations for future implementation work, including production builds and post-change verification.

## Capabilities

### New Capabilities
- `ucp-frontend-bundle-optimization`: Defines how the UCP frontend may reduce initial bundle size through safe lazy loading and code splitting without changing auth, API contracts, or production behavior.

### Modified Capabilities

## Impact

Affected areas are the Vite production build for `WEBSITE`, the React frontend entry in `WEBSITE/index.tsx` and `WEBSITE/App.tsx`, and secondary frontend components such as admin panels, donation flows, ticket views, charts, and image-cropping screens. PHP API files, gamemode code, database schema, and secrets remain out of scope.
