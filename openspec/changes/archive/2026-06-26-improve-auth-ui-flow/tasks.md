# improve-auth-ui-flow — Tasks

## Phase 1: Audit & Foundation

- [x] 1.1 Audit struktur auth page — identifikasi semua file, props, state, flow antar view
- [x] 1.2 Audit komponen/style yang sudah ada — catat semua Tailwind classes, color tokens, spacing, animation yang dipakai
- [x] 1.3 Buat design token system — CSS custom properties di `index.html` untuk PHRP brand colors (crimson, gold, dark slate), spacing scale, border radius, shadow, typography weights

## Phase 2: Shared Components & Auth Container

- [x] 2.1 Improve `InputGroup.tsx` — better focus ring, error state display, dark mode icon visibility, consistent sizing
- [x] 2.2 Desain ulang layout auth container (`Auth.tsx`) — perbaiki responsive split-panel, scroll handling, hapus spacer hack (`-mb-9`), improve server status bar placement
- [x] 2.3 Redesign error notification — ubah dari full-screen modal overlay ke inline alert banner untuk error ringan, tetap gunakan modal untuk error critical/blocking
- [x] 2.4 Improve slideshow panel styling — subtle refinements pada gradient overlay, text shadow, indicator dots (tanpa mengubah data/logic)

## Phase 3: Individual Form Pages

- [x] 3.1 Improve Login page (`LoginForm.tsx`) — redesign layout, typography hierarchy, button styling, copywriting konsistensi bahasa Indonesia, link styling
- [x] 3.2 Improve Register page (`RegisterForm.tsx`) — redesign layout, visual field grouping, password requirement hints, consistent copywriting
- [x] 3.3 Improve Forgot Password page (`ForgotPasswordForm.tsx`) — step indicator (step 1: email, step 2: OTP + new password), hapus `alert()` native diganti inline success message, consistent styling
- [x] 3.4 Improve OTP Email Verification page (`VerifyForm.tsx`) — redesign OTP input (individual digit cells or cleaner mono input), improve timer display, better success/error states
- [x] 3.5 Improve Discord Link page (`DiscordLinkForm.tsx`) — add back navigation button, improve Discord brand card, consistent container styling

## Phase 4: Polish & Flow

- [x] 4.1 Tambahkan flow/progress indicator — visual breadcrumb atau step dots untuk multi-step flows (register → verify → discord)
- [x] 4.2 Konsistensi animasi — semua form menggunakan transition yang sama (fade + subtle slide)
- [x] 4.3 Konsistensi copywriting — semua teks auth ke Bahasa Indonesia yang konsisten, tone profesional

## Phase 4.5: Premium Visual Upgrade

- [x] 4.5.1 Update design tokens di index.html (Dark UI only)
- [x] 4.5.2 Redesign background & panel container di Auth.tsx
- [x] 4.5.3 Polish form components (LoginForm, RegisterForm, dll) proporsi & CTA

## Phase 4.6: Corrective Visual Fix

- [x] 4.6.1 Perbaiki solid background untuk form (clean premium dark:bg-[#121218] dan input dark:bg-[#16161e]) menghapus efek backdrop-blur setengah matang.
- [x] 4.6.2 Pastikan proporsi layout tidak terpotong (tambah padding container form di Auth.tsx)
- [x] 4.6.3 Update styling Fallback/Loading screen agar tidak terpengaruh light-mode (force background `#050505`).
- [x] 4.6.4 Perbaiki status server pill agar lebih kompak.

## Phase 4.7: Real Auth Visual Redesign

- [x] 4.7.1 Update `index.html` — light-mode alert variants (error/success/warning), premium thin scrollbar (gold/crimson), `.ph-auth-surface` warm gradient utility, `.ph-auth-accent-line` crimson/gold gradient, `.ph-scroll-thin` scrollbar styling
- [x] 4.7.2 Redesign `Auth.tsx` — premium right panel surface (warm gradient + accent line), status pill proportional & premium, logo reduced (w-32/w-36), flow indicator compact (h-6 w-6 circles), scroll area with thin scrollbar, error alert light-mode colors
- [x] 4.7.3 Polish `InputGroup.tsx` — off-white input bg (`bg-gray-50/60`), rounded-xl, subtle border, crimson focus ring, icon z-10, tighter padding (py-3)
- [x] 4.7.4 Polish `LoginForm.tsx` — CTA clean (shadow-sm, no glow), tighter spacing (space-y-3), consistent link styling
- [x] 4.7.5 Polish `RegisterForm.tsx` — reduced height (space-y-2.5, mb-3), info box cleaner (bg-ph-gold-50/60), consistent CTA
- [x] 4.7.6 Polish `ForgotPasswordForm.tsx` — reduced height (space-y-2.5/3), step indicator compact (w-8 divider), CTA no glow, translatePreviewMsg for API preview text
- [x] 4.7.7 Polish `VerifyForm.tsx` — mail icon smaller (w-12 h-12), OTP input premium (bg-gray-50/60, rounded-xl), CTA no glow, translatePreviewMsg for API preview text
- [x] 4.7.8 Polish `DiscordLinkForm.tsx` — reduced height (icon w-16 h-16, benefit cards p-3), removed drop-shadow glow, consistent CTA, "Mode Preview" → "Mode Pratinjau"
- [x] 4.7.9 Translate English debug text — "Local-only OTP preview is enabled..." → "Pratinjau OTP lokal aktif untuk lingkungan ini. Fitur ini dinonaktifkan di produksi." in ForgotPasswordForm & VerifyForm
- [x] 4.7.10 Validation — `npx vite build` passes, `npx tsc --noEmit` reports only pre-existing errors (import.meta.env types, module resolution, ServerStats/UserData types)

## Phase 4.8: Auth UI Major Visual Upgrade

- [x] 4.8.1 `index.html` — Added `dot-pattern` + `dot-pattern-light` + `diagonal-stripes` background utilities; upgraded `.ph-auth-surface` with layered radial gradients (crimson top-right + gold top-right + warm base); added new utility classes: `.ph-auth-panel-inner` (frosted inner card section with crimson border glow), `.ph-eyebrow` (kicker micro-text with crimson→gold gradient line), `.ph-btn-primary` (premium crimson CTA with inset highlight + multi-layer shadow + hover lift), `.ph-status-pill` (premium server status surface), `.ph-card-corner` (cinematic corner accents in 4 positions), `.ph-page-vignette` (PHRP vignette backdrop); strengthened `.ph-input-focus` to crimson/gold multi-ring with light/dark variants.
- [x] 4.8.2 `Auth.tsx` — Card enlarged from `max-w-5xl` (1024px) → `max-w-6xl` (1152px), height `680px` → `720px`; dramatic PHRP backdrop with crimson/gold radial glows + dot-pattern + grid-pattern + horizontal accent lines + vignette utility; 4 cinematic corner accents (gold TL/BR, crimson TR/BL); right panel inner card section wraps all form content (`.ph-auth-panel-inner`); eyebrow micro-text “User Control Panel” + `v1.0` version tag; premium status pill (`.ph-status-pill`); logo scaled up to `w-36/w-40` with subtle gold halo; slideshow top brand bar (PHRP logo + Est. 2024 + counter `01/05`); bigger slide icon (`w-14 h-14` + `size=26`); “Feature Highlight” pill badge; cinematic gradient layered with `mix-blend-overlay`; premium slide indicators with gradient active state + AUTO counter.
- [x] 4.8.3 `InputGroup.tsx` — Stronger border (`border-gray-300` light / `border-white/15` dark), `shadow-sm` + inset highlight, error state with red halo + crimson-700 tint; placeholder opacity reduced for better contrast; focus state uses enhanced `.ph-input-focus` (4px crimson ring + 1px crimson border in light, 4px gold ring + 1px gold border in dark).
- [x] 4.8.4 `LoginForm.tsx` — Eyebrow kicker “Secure Account Access”; title scaled to `text-[22px]/[26px]`; description with line break; CTA upgraded to `.ph-btn-primary` (`py-3.5`); divider “Atau” with gradient lines between sections; link hover uses crimson/gold accent.
- [x] 4.8.5 `RegisterForm.tsx` — Eyebrow kicker “Bergabung Bersama Kami”; info box upgraded to gradient `ph-gold-50/70 → ph-gold-100/30` with gold dot indicator + highlighted “kode OTP” word; CTA `.ph-btn-primary py-3.5 mt-2`; back-link hover micro-animation.
- [x] 4.8.6 `ForgotPasswordForm.tsx` — Eyebrow kicker “Account Recovery”; step indicator upgraded with numbered `01 Email` / `02 Reset Sandi`, gradient connector (gold→crimson), terminal dot; CTAs `.ph-btn-primary`.
- [x] 4.8.7 `VerifyForm.tsx` — Eyebrow kicker “Email Verification”; hero icon upgraded to `w-16 h-16` with crimson/gold glow + ring border + shadow; OTP input with stronger border + `shadow-sm` + `tracking-[0.6em]` + `text-[20px] font-bold`; label upgraded to uppercase eyebrow style; CTA `.ph-btn-primary`; resend button with stronger border + shadow.
- [x] 4.8.8 `DiscordLinkForm.tsx` — Eyebrow kickers (“Tautan Berhasil” / “Komunitas PHRP”); hero icon upgraded to `w-20 h-20` with blue glow + ring border + shadow (success state w-16); benefit cards with gradient icon containers + `shadow-sm`; CTA `.ph-btn-primary` for success; Discord link button kept Discord brand blue with stronger shadow.
- [x] 4.8.9 Validation — `npx vite build` passes; `npx tsc --noEmit` reports only pre-existing errors.

## Phase 4.9: Visual Simplification & Brand Correction

- [x] 4.9.1 `Auth.tsx` — Background simplified from 3 radial orbs (with pulse animation) → 2 static orbs (lower opacity, smaller blur); removed `bg-grid-pattern` overlay entirely; removed top + bottom horizontal accent lines; reduced `dot-pattern` opacity 70% → 30%; reduced card shadow intensity and border opacity.
- [x] 4.9.2 `Auth.tsx` — Card corner accents reduced from 22px (2px border) → 12px (1px border), more subtle frame indicator.
- [x] 4.9.3 `Auth.tsx` — Slideshow top brand bar simplified: removed PHRP star logo box + "PHRP" + "Est. 2024" text; kept only the small "01/05" counter pill (lighter bg-white/8 + border-white/10). Brand year moved to right panel header as subtle text "Est. 2020".
- [x] 4.9.4 `Auth.tsx` — Removed "Feature Highlight" pill badge with pulsing dot; reduced title weight from `text-4xl font-black uppercase italic` → `text-3xl font-extrabold` (no italic, no uppercase, more mature); reduced drop-shadow to `drop-shadow-md`; description border reduced from `border-l-[3px]` → `border-l-2`, opacity 100% → 70%.
- [x] 4.9.5 `Auth.tsx` — Slide icon reduced from `w-14 h-14 rounded-2xl shadow-2xl ring-1` → `w-12 h-12 rounded-xl shadow-lg` (no ring, no outer blur glow); removed `fill="currentColor"` (cleaner icon look).
- [x] 4.9.6 `Auth.tsx` — Removed slide indicator "AUTO" counter; removed blur glow on active indicator; active state changed from `w-12 bg-gradient-to-r from-gold-to-crimson` → `w-10 bg-ph-gold-400` (single solid color, simpler).
- [x] 4.9.7 `Auth.tsx` — Right panel header: removed "v1.0" tag; added "Est. 2020" subtle text next to the "User Control Panel" eyebrow kicker.
- [x] 4.9.8 `Auth.tsx` — Status pill: removed "Players count" section (with Users icon); kept just status (Online/Offline) + Server IP; status pill CSS made slimmer (no gradient, no gold border, simple flat surface).
- [x] 4.9.9 `Auth.tsx` — Logo scaled down from `w-36/w-40 max-h-16/max-h-20` → `w-32/w-36 max-h-14/max-h-16`; removed gold halo `bg-ph-gold-400/20 blur-2xl`; hover scale reduced from `1.04` → `1.03`; inner card section padding reduced from `px-7 py-6` → `px-6 py-5`, radius `rounded-2xl` → `rounded-xl`.
- [x] 4.9.10 `index.html` — `.ph-input-focus` simplified from dual-ring (3px + 1px) → single ring (3px only).
- [x] 4.9.11 `index.html` — `.ph-auth-panel-inner` made much lighter: removed warm gradient, removed crimson-tinted border, removed backdrop-blur, reduced shadow to just inset highlight + 1px subtle drop.
- [x] 4.9.12 `index.html` — `.ph-status-pill` changed from gold-tinted gradient (white→cream + gold border + gold glow) → flat neutral surface (white/70 + neutral border + single 1px shadow).
- [x] 4.9.13 `index.html` — `.ph-card-corner` reduced from 22px (2px border, 4px radius) → 12px (1px border, 2px radius) and inset 14px from edge.
- [x] 4.9.14 `index.html` — `.ph-page-vignette` reduced from 3 radial gradients (top + bottom-right + bottom-left) → 2 radial gradients (top + bottom-right) with lower opacity.
- [x] 4.9.15 `index.html` — Global scrollbar made subtle: width 5px → 4px, thumb color from gold/crimson → neutral gray (15% black / 10% white), hover stays crimson.
- [x] 4.9.16 `index.html` — `.ph-scroll-thin` (form area scrollbar) changed from gold tint → neutral tint to match global scrollbar.
- [x] 4.9.17 `VerifyForm.tsx` — Hero icon reduced from `w-16 h-16` with two-layer (outer blur glow + inner gradient) → single `w-14 h-14` flat container with `shadow-md`; Mail icon 28 → 26.
- [x] 4.9.18 `DiscordLinkForm.tsx` — Hero icons (both pre-success and success state) reduced from `w-20 h-20` / `w-16 h-16` with outer blur → single `w-16 h-16` / `w-14 h-14` flat containers with `shadow-md`; Discord icon 40 → 34; success Shield icon 30 → 28.
- [x] 4.9.19 `RegisterForm.tsx` — Info box gradient intensity reduced: from `bg-gradient-to-br from-ph-gold-50/70 to-ph-gold-100/30` + shadow → flat `bg-ph-gold-50/40` (no gradient, no shadow).
- [x] 4.9.20 Brand correction — `Est. 2024` → `Est. 2020` applied in: (a) `WEBSITE/components/Auth.tsx` (active production file, but text removed from slideshow top bar and moved to right panel header); (b) `WEBSITE/Auth.tsx` (dead code, updated for consistency).
- [x] 4.9.21 Validation — `npx vite build` passes; `npx tsc --noEmit` reports only pre-existing errors.

## Phase 4.10: Clean Professional Auth Polish

- [x] 4.10.1 `Auth.tsx` — Restored player online/count section in status pill (was removed in Phase 4.9 task 4.9.8). Section now shows: status indicator + `Users` icon + count from `serverStats?.players ?? 0` with "pemain" suffix (safe fallback when data is 0/undefined). Order is: Status → Players → IP.
- [x] 4.10.2 `Auth.tsx` — Status pill refined to be more professional: added responsive gap (`gap-2 md:gap-2.5`), dividers slightly taller (`h-3` → `h-3.5`), icons bumped from `size={11}` → `size={12}` for both `Users` and `Wifi` (better visibility). Text size kept at `text-[10px]` to remain compact. Pill still uses `.ph-status-pill` flat surface (no gradient, no glow).
- [x] 4.10.3 `Auth.tsx` — Left slideshow overlays subtly reduced so the image stays cinematic but more visible: layer 2 (left-to-right darken) `from-black/40` → `from-black/30 via-black/5`; full overlay top `from-black` → `from-black/70`, mid `via-black/60` → `via-black/50`; bottom 2/3 overlay top `from-black` → `from-black/85`, mid `via-black/70` → `via-black/60`. Text region remains readable thanks to `drop-shadow-md` and `text-white` / `text-gray-300/95`.
- [x] 4.10.4 `Auth.tsx` — Right panel inner card padding slightly increased so it doesn't feel too small or too far from the right panel header: `py-4 md:py-5` → `py-5 md:py-6`. The inner card is more substantial without making the form feel too narrow; `my-2` and `max-w-[420px]` kept unchanged.
- [x] 4.10.5 Brand consistency — `Est. 2020` preserved on the right panel header (line near `.ph-eyebrow`). No logo asset, font, or package changes. No status pill asset added.
- [x] 4.10.6 Form components — `LoginForm`, `RegisterForm`, `ForgotPasswordForm`, `VerifyForm`, `DiscordLinkForm` were NOT modified in this phase; current spacing, CTA sizing (`py-3.5`), and `.ph-scroll-thin` (4px neutral scrollbar) are sufficient. Main buttons are not cut.
- [x] 4.10.7 `index.html` — No CSS changes; existing `.ph-input-focus`, `.ph-auth-panel-inner`, `.ph-status-pill`, `.ph-card-corner`, `.ph-page-vignette`, `.ph-scroll-thin` tokens already cover the Phase 4.10 polish needs.
- [x] 4.10.8 `App.tsx` — Not modified; loading screen preserved.
- [x] 4.10.9 Dead-code `WEBSITE/Auth.tsx` — Not touched; it already had the Players section so production and dead-code stay visually consistent.
- [x] 4.10.10 Validation — `npx vite build` passes; `npx tsc --noEmit` reports only pre-existing errors (no new errors introduced by Phase 4.10).

## Phase 4.11: Clean Game Hosting Inspired Auth UI

- [x] 4.11.1 `Auth.tsx` — Removed 4 cinematic corner accents (`ph-card-corner tl/tr/bl/br`) entirely; replaced card border `border-ph-gold-600/20 dark:border-ph-crimson-900/30` → clean neutral `border-black/10 dark:border-white/[0.06]`. Card radius softened `md:rounded-[24px]` → `md:rounded-[18px]`. The card frame is no longer poster-like.
- [x] 4.11.2 `Auth.tsx` — Background simplified: removed second gold orb (`bg-ph-gold-600/[0.06]`) entirely; reduced crimson orb opacity 10% → 7%; reduced `bg-dot-pattern` opacity 30% → 16%. The backdrop is calmer, more dashboard, less cinematic.
- [x] 4.11.3 `Auth.tsx` — Slideshow no longer poster-style. Removed the colored `SlideIcon` (`w-12 h-12 rounded-xl` with gradient background) from the slide content. Removed `mix-blend-overlay` crimson/gold tint layer. Removed the second darken layer. Reduced overlay darkness: full top gradient removed, only bottom 2/3 kept (`from-black/70 via-black/40`). Counter pill (`bg-white/8 backdrop-blur border-white/10`) replaced with clean plain `01 / 05` mono text. Slide title reduced `text-3xl font-extrabold` → `text-[26px] font-bold` (no `drop-shadow-md`, no italic). Description removed `border-l-2 border-ph-gold-500/70 pl-3` accent. Slide indicator active color `bg-ph-gold-400 w-10` → `bg-white w-8` (white instead of gold accent, more neutral).
- [x] 4.11.4 `Auth.tsx` — Right panel header restructured for cleaner hierarchy: replaced the eyebrow-with-`Est. 2020`-inline layout with a clean two-column header row. Left: `User Control Panel` (gray uppercase kicker). Right: `Est. 2020` in `text-ph-crimson-700 dark:text-ph-gold-400` (visible, on-brand, not faded). Top accent line `h-[3px]` → `h-[2px]` and removed `shadow-[0_1px_6px_rgba(220,38,38,0.35)]` glow.
- [x] 4.11.5 `Auth.tsx` — Status pill cleaner & more readable: text bumped `text-[10px]` → `text-[11px]`; icons `size={12}` → `size={13}`; gaps `gap-2 md:gap-2.5` → `gap-3 md:gap-3.5`; dividers `h-3.5` → `h-4`; `rounded-full` → `rounded-md`; padding `px-3.5 py-1.5` → `px-4 py-2`; `Wifi` icon color `text-ph-gold-600` → neutral `text-gray-500 dark:text-gray-400`. Three sections (status, players, IP) preserved with clear visual hierarchy.
- [x] 4.11.6 `Auth.tsx` — Right panel inner card cleaner: `rounded-xl` → `rounded-lg` (smaller radius, less decorative); logo `mb-4` → `mb-5` for slightly more breathing room. Card still uses `.ph-auth-panel-inner` flat surface (no glow, no extra inset highlight).
- [x] 4.11.7 `Auth.tsx` — Removed unused `SlideIcon` local variable since the slide icon block was removed in 4.11.3. Icons in the `SLIDES` array data are kept for reference but no longer rendered.
- [x] 4.11.8 `index.html` — `.ph-eyebrow` simplified: removed `::before` line accent (crimson→gold gradient line) and the `gap: 6px` so the eyebrow is just clean text. Forms that use `.ph-eyebrow` (Login/Register/Forgot/Verify/Discord) now render without decorative line prefix.
- [x] 4.11.9 `index.html` — `.ph-status-pill` refined: background opacity 70% → 78% (slightly more solid), border 6% → 7%, shadow 1px → 1px 3px. Dark variant: background 60% → 70%. Pill is more readable and has a subtle elevated feel without being decorative.
- [x] 4.11.10 `index.html` — `.ph-auth-panel-inner` cleaned: removed inset highlight `inset 0 1px 0 rgba(...)` (light + dark variants). Card is now flat — no glow, no inset. Background opacity bumped 0.5 → 0.55 (slightly more solid surface). Inner card is professional, not frosted.
- [x] 4.11.11 `index.html` — `.ph-card-corner` CSS removed entirely (the rule was no longer used in the production `components/Auth.tsx`).
- [x] 4.11.12 `index.html` — `.ph-page-vignette` reduced from 2 radial gradients (top + bottom-right) → 1 (top only). Light opacity 6%/4% → 4%. Dark opacity 18%/10% → 14%. Backdrop is cleaner.
- [x] 4.11.13 `index.html` — `.ph-btn-primary` glow reduced for cleaner professional look: radius `12px` → `10px`; inset highlights opacity 0.18/0.25 → 0.14/0.20; drop shadow `2px 4px` → `1px 3px` and `6px 14px` → `4px 10px` (lighter). Hover state similarly dialed back. CTA still reads as strong red but no longer over-glowy.
- [x] 4.11.14 Form components (`LoginForm`, `RegisterForm`, `ForgotPasswordForm`, `VerifyForm`, `DiscordLinkForm`, `InputGroup`) — NOT modified in this phase. Spacing, CTA sizing, validation patterns, OTP input, Discord brand button all already clean from Phases 4.7–4.10. Buttons not cut.
- [x] 4.11.15 `App.tsx` — Not modified; loading screen preserved.
- [x] 4.11.16 Dead-code `WEBSITE/Auth.tsx` — Not touched per instructions; corner accents kept there for consistency with the file's existing style.
- [x] 4.11.17 Validation — `npx vite build` passes; `npx tsc --noEmit` reports only pre-existing errors (no new errors introduced by Phase 4.11).

## Phase 4.15: Light Premium Hosting x Roleplay Auth Layout

- [x] 4.15.1 `index.html` -- retuned auth tokens to light/off-white client-area direction, with logo-matched crimson base/dark/soft and restrained gold accent.
- [x] 4.15.2 `components/Auth.tsx` -- replaced dark-heavy dashboard shell with light split layout: left crimson roleplay image panel, right white/off-white form surface, compact server status, and mobile intro panel.
- [x] 4.15.3 `components/Auth.tsx` -- preserved `Est. 2020`, logo asset, slideshow assets, server status online/offline + players + IP, and added form-scroll reset on view changes to avoid cut-off forms.
- [x] 4.15.4 `InputGroup`, `LoginForm`, `RegisterForm`, `ForgotPasswordForm`, `VerifyForm`, `DiscordLinkForm` -- converted form visuals to clean light inputs/cards, crimson focus/CTA/link states, and roleplay UCP copy without API/payload/session changes.
- [x] 4.15.5 Browser preview -- checked initial dark-heavy state, then completed two edit/preview/polish cycles; checked desktop 1920x1080, tablet 900x1024, and mobile 390x844.
- [x] 4.15.6 Validation -- `npx vite build` passes; `npx tsc --noEmit` still fails on existing out-of-scope errors (`import.meta.env`, root dead-code Auth imports, ServerStats/UserData, PromoItem qty, TicketSystem comparisons).
- [x] 4.15.7 `App.tsx` -- not modified; loading screen preserved.
- [x] 4.15.8 Follow-up polish -- mobile now renders form/status only, desktop split is exact 50/50, and slideshow images render with original color (`opacity: 1`, normal blend mode) behind only a neutral readability gradient.
- [x] 4.15.9 Local fake auth preview tools -- added localhost/dev-only preview states for OTP verify, forgot-password reset, Discord link, and their success states so visual QA can run without live API mutations.

## Phase 5: Responsive & Testing

- [x] 5.1 Responsive check mobile (< 640px) — browser checked at 390x844: form/status only, no horizontal overflow, left slideshow hidden, visible buttons >= 40px, server status and logo visible.
- [x] 5.2 Responsive check tablet (640px - 1024px) — browser checked at 900x1024: split panel active, no horizontal overflow, left/right columns remain precise and status card visible.
- [x] 5.3 Responsive check desktop (> 1024px) — browser checked at 1920x1080: 1180px shell, 589px left column, no horizontal overflow, original-color slideshow images verified.
- [x] 5.4 Dark mode verification — auth UI is intentionally light-only for Phase 4.15; static check found no active auth `dark:` variants in production auth components, so dark class does not introduce competing dark-heavy auth styling.
- [x] 5.5 Light mode verification — browser checked login/register/forgot/verify/discord surfaces in the light off-white client-area direction.

## Phase 6: Validation & Documentation

- [x] 6.1 Validasi build (`npm run build`) — `npx vite build` passed after latest polish (`built in 11.85s`).
- [x] 6.2 Validasi dev server (`npm run dev`) — localhost preview opened successfully and `http://localhost:3000/` returned 200.
- [x] 6.3 Test login flow end-to-end (preview mode) — `preview` / `preview123` logged into dashboard with `PreviewPlayer`.
- [x] 6.4 Test register flow end-to-end (preview mode) — register -> verify OTP `123456` -> Discord preview link -> dashboard succeeded.
- [x] 6.5 Test forgot password flow (preview mode) — forgot -> preview reset step -> reset -> returned to login with no native alert.
- [x] 6.6 Test error states — empty validation, invalid preview credentials, and simulated network error all render inline; no full-screen modal/native dialog.
- [x] 6.7 Dokumentasi perubahan — added `openspec/changes/improve-auth-ui-flow/validation.md` plus desktop/mobile screenshot artifacts under `screenshots/`.
