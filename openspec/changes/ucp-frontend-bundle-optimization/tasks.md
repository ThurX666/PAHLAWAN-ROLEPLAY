## 1. Baseline And Split Strategy

- [x] 1.1 Convert top-level `App.tsx` screen imports for `Auth`, `Donation`, `TicketSystem`, `CharacterStoryPage`, `CharacterDetail`, `AdminPanel`, and `Requests` into approved lazy-loading boundaries with safe loading fallbacks.
- [x] 1.2 Keep `WEBSITE/index.tsx`, fetch credential behavior, and existing auth/session orchestration unchanged while introducing those lazy boundaries.
- [x] 1.3 Rebuild the frontend and compare emitted chunks to confirm the initial bundle is reduced before moving to nested optimizations.

## 2. Heavy Nested Dependency Isolation

- [x] 2.1 Defer `recharts` usage behind lazy boundaries for dashboard and admin chart modules where feasible without changing user-visible behavior.
- [x] 2.2 Defer `react-easy-crop` usage so cropper code loads only when the related donation or character-photo modal is opened.
- [x] 2.3 Audit `@google/genai` frontend service imports and either defer them behind explicit actions or remove accidental runtime usage in a separate bounded follow-up if they are not needed.

## 3. Verification

- [x] 3.1 Run `npm run build` in `WEBSITE` and record the new chunk layout plus any remaining warnings.
- [ ] 3.2 Verify login, session continuity, dashboard navigation, donation flow, ticket flow, settings flow, character detail flow, and admin access still behave the same after lazy loading.
- [x] 3.3 Run `openspec validate ucp-frontend-bundle-optimization --type change` and `git diff --check` before requesting review of the implementation patch.
