## Context

`npm run build` in `WEBSITE` currently produces one primary application chunk, `dist/assets/index-D8S_1beG.js`, at about 1,254.30 kB minified and 327.18 kB gzip, which triggers Vite's `(!) Some chunks are larger than 500 kB after minification` warning. The current app uses a single entry (`WEBSITE/index.tsx`) that mounts `App.tsx`, and `App.tsx` eagerly imports all major user areas up front, including `Dashboard`, `CharacterList`, `CharacterDetail`, `CharacterStoryPage`, `Donation`, `TicketSystem`, `Settings`, `Auth`, `AdminPanel`, and `Requests`.

The heaviest likely secondary paths are concentrated in:
- Admin views, especially `components/admin/AdminPanel.tsx`, `AdminSetup.tsx`, `AdminStories.tsx`, and donations/admin overview children.
- Donation and character-detail flows that pull in `react-easy-crop` through `PaymentModal.tsx` and `CharacterDetail.tsx`.
- Chart components that pull in `recharts` through `dashboard/ActivityChart.tsx` and `admin/overview/EconomyChart.tsx`.
- Frontend AI helper files that import `@google/genai` under `WEBSITE/services`.

The change must remain planning-only for now. It must not modify PHP API logic, auth logic, gamemode/Pawn, database schema, or secrets, and it must not change production behavior.

## Goals / Non-Goals

**Goals:**
- Define safe bundle split boundaries for the current single-entry UCP frontend.
- Prefer lazy loading at user-visible navigation boundaries where behavior remains unchanged after load completes.
- Isolate heavy optional dependencies so they are not part of the initial authenticated or unauthenticated path unless required.
- Establish measurable validation for a future implementation pass.

**Non-Goals:**
- Editing application code in this change.
- Changing PHP endpoints, auth/session rules, or database behavior.
- Solving the warning only by raising `chunkSizeWarningLimit`.
- Reworking UI flow, permissions, or feature ownership.

## Decisions

- Use top-level React lazy loading for major view boundaries instead of starting with `manualChunks`.
  Rationale: the current architecture already switches views by `activeTab` in `App.tsx`, so lazy-loading those screen modules is the lowest-risk way to stop shipping every screen on first load. `manualChunks` may still be useful later, but it is a bundler-level override and should be a secondary optimization after code-level boundaries exist.

- Preserve `WEBSITE/index.tsx` and the fetch credential shim unchanged.
  Rationale: the entry file is small and owns global fetch behavior for API credentials. Moving that logic into lazy chunks would create unnecessary risk around auth/session behavior.

- Split optional authenticated screens before splitting foundational shared UI.
  Rationale: high-value candidates are `AdminPanel`, `TicketSystem`, `Donation`, `CharacterDetail`, `CharacterStoryPage`, and `Requests`, because they are not needed for the first paint of every session. Core layout, config, and session bootstrap should remain eager until chunk boundaries are proven safe.

- Split heavy nested dependencies behind interaction-level boundaries inside secondary screens.
  Rationale: `react-easy-crop` should load only when a crop modal is opened, and `recharts` should load only when chart-bearing screens render. This keeps the initial bundle smaller even if the parent screen itself remains moderately large.

- Treat frontend AI helper imports as optional or cleanup candidates, not initial-path dependencies.
  Rationale: `WEBSITE/services/geminiService.ts` and `WEBSITE/services/storyService.ts` import `@google/genai`, but current evidence does not show them as required for initial app bootstrap. A future implementation should verify call sites and either defer these modules behind explicit actions or remove accidental runtime imports that are not used.

- Validate success by build output and unchanged behavior, not by warning suppression.
  Rationale: the target is safe bundle reduction. A future implementation must confirm chunk reductions through `npm run build` and preserve the same auth flow, tab navigation, and API interactions.

## Risks / Trade-offs

- [Lazy boundaries around auth or session bootstrap could change login behavior] -> Keep `index.tsx`, config usage, fetch credential behavior, and current auth/session orchestration unchanged during the first implementation pass.
- [Over-splitting shared components can increase request overhead and hurt repeat navigation] -> Start with coarse screen-level boundaries, then add nested splits only for clearly heavy modules such as charts and crop modals.
- [Admin-only or rarely used features may still pull heavy shared libraries into common chunks] -> Verify dependency placement after each split and only consider `manualChunks` after code-level lazy imports are in place.
- [Production warning may persist if only one or two screens are split] -> Prioritize the largest secondary screens first: admin, donation, tickets, character detail, and chart-bearing pages.
- [Unused or accidental runtime imports can hide inside helper modules] -> Audit actual usage of `@google/genai` and similar dependencies during implementation before deciding between lazy loading and cleanup.

## Migration Plan

- No deployment or migration action is part of this planning-only change.
- Future implementation should land as a frontend-only patch, run `npm run build`, compare emitted chunk structure, and verify navigation across auth, dashboard, donation, tickets, settings, and admin screens.
- Rollback strategy for future implementation is to revert the lazy-import changes if any navigation, loading, or auth regression appears.

## Open Questions

- Which lazy-loading fallback UX is already acceptable in this frontend for tab-level and modal-level loading states?
- Is `WEBSITE/Auth.tsx` or `WEBSITE/components/Auth.tsx` the authoritative auth component path for the current production entry, and can duplicate auth files be reduced later without changing behavior?
- Are the `@google/genai` frontend service imports reachable in the live UI, or are they currently dormant code that can be cleaned up in a separate follow-up?
