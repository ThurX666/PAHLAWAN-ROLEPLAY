---
version: alpha
name: PHRP-UCP-Design-System
description: >
  Design contract for the Pahlawan Roleplay User Control Panel (UCP).
  A premium gaming client-area with crimson/gold identity, light-first auth surfaces,
  dark-first dashboard surfaces, and a clean professional tone.

colors:
  primary: "#d71920"
  primary-hover: "#ef2a2a"
  primary-dark: "#9f121f"
  primary-soft: "#fff1f1"
  on-primary: "#ffffff"
  accent-gold: "#d88912"
  accent-gold-light: "#fbbf24"
  accent-gold-dark: "#92400e"
  ink: "#161616"
  body: "#55565b"
  muted: "#7a7c83"
  canvas: "#fbf8f5"
  surface-white: "#ffffff"
  surface-soft: "#f5f0ea"
  surface-input: "#fbfaf8"
  hairline: "rgba(15,23,42,0.08)"
  hairline-strong: "rgba(15,23,42,0.12)"
  surface-deep: "#0a0a0f"
  surface-base: "#0e0e14"
  surface-card: "#121218"
  surface-panel: "#1a1a24"
  surface-elevated: "#22222e"
  surface-input-dark: "#16161e"
  hairline-dark: "rgba(255,255,255,0.10)"
  hairline-dark-strong: "rgba(255,255,255,0.05)"
  danger: "#dc2626"
  danger-dark: "#9f121f"
  danger-soft: "#fff1f1"
  success: "#16a34a"
  success-soft: "#f0fdf4"
  warning: "#d97706"
  warning-soft: "#fffbeb"
  discord: "#5865F2"
  discord-hover: "#4752C4"

typography:
  display-lg:
    fontFamily: "Inter, ui-sans-serif, system-ui, sans-serif"
    fontSize: 34px
    fontWeight: 800
    lineHeight: 1.15
    letterSpacing: -0.02em
  heading-xl:
    fontFamily: "Inter, ui-sans-serif, system-ui, sans-serif"
    fontSize: 26px
    fontWeight: 700
    lineHeight: 1.25
    letterSpacing: 0px
  heading-md:
    fontFamily: "Inter, ui-sans-serif, system-ui, sans-serif"
    fontSize: 22px
    fontWeight: 700
    lineHeight: 1.30
    letterSpacing: 0px
  heading-sm:
    fontFamily: "Inter, ui-sans-serif, system-ui, sans-serif"
    fontSize: 16px
    fontWeight: 700
    lineHeight: 1.35
    letterSpacing: 0px
  body-md:
    fontFamily: "Inter, ui-sans-serif, system-ui, sans-serif"
    fontSize: 14px
    fontWeight: 400
    lineHeight: 1.50
    letterSpacing: 0px
  body-sm:
    fontFamily: "Inter, ui-sans-serif, system-ui, sans-serif"
    fontSize: 13px
    fontWeight: 400
    lineHeight: 1.50
    letterSpacing: 0px
  caption:
    fontFamily: "Inter, ui-sans-serif, system-ui, sans-serif"
    fontSize: 12px
    fontWeight: 500
    lineHeight: 1.35
    letterSpacing: 0px
  micro:
    fontFamily: "Inter, ui-sans-serif, system-ui, sans-serif"
    fontSize: 10px
    fontWeight: 700
    lineHeight: 1.00
    letterSpacing: 0.2em
  eyebrow:
    fontFamily: "Inter, ui-sans-serif, system-ui, sans-serif"
    fontSize: 10px
    fontWeight: 700
    lineHeight: 1.00
    letterSpacing: 0.2em
  button-md:
    fontFamily: "Inter, ui-sans-serif, system-ui, sans-serif"
    fontSize: 14px
    fontWeight: 700
    lineHeight: 1.25
    letterSpacing: 0px
  code-md:
    fontFamily: "JetBrains Mono, ui-monospace, monospace"
    fontSize: 14px
    fontWeight: 400
    lineHeight: 1.50
    letterSpacing: 0px
  code-sm:
    fontFamily: "JetBrains Mono, ui-monospace, monospace"
    fontSize: 12px
    fontWeight: 400
    lineHeight: 1.40
    letterSpacing: 0px

rounded:
  none: 0px
  xs: 4px
  sm: 6px
  md: 9px
  lg: 10px
  xl: 12px
  2xl: 16px
  3xl: 24px
  full: 9999px

spacing:
  xxs: 2px
  xs: 4px
  sm: 8px
  md: 16px
  lg: 24px
  xl: 32px
  xxl: 48px
  section: 64px
  safe: "env(safe-area-inset-bottom)"

components:
  button-primary:
    backgroundColor: "{colors.primary}"
    textColor: "{colors.on-primary}"
    typography: "{typography.button-md}"
    rounded: "{rounded.md}"
    padding: "14px 24px"
    height: 48px
  button-primary-hover:
    backgroundColor: "{colors.primary-hover}"
    textColor: "{colors.on-primary}"
    typography: "{typography.button-md}"
    rounded: "{rounded.md}"
  button-primary-disabled:
    backgroundColor: "{colors.primary}"
    textColor: "{colors.on-primary}"
    typography: "{typography.button-md}"
    rounded: "{rounded.md}"
  button-secondary:
    backgroundColor: "{colors.surface-white}"
    textColor: "{colors.ink}"
    typography: "{typography.button-md}"
    rounded: "{rounded.md}"
    padding: "12px 20px"
    height: 44px
  button-discord:
    backgroundColor: "{colors.discord}"
    textColor: "{colors.on-primary}"
    typography: "{typography.button-md}"
    rounded: "{rounded.xl}"
    padding: "12px 24px"
    height: 48px
  text-input:
    backgroundColor: "{colors.surface-input}"
    textColor: "{colors.ink}"
    typography: "{typography.body-md}"
    rounded: "{rounded.xl}"
    padding: "12px 16px"
    height: 48px
  text-input-focused:
    backgroundColor: "{colors.surface-white}"
    textColor: "{colors.ink}"
    rounded: "{rounded.xl}"
  text-input-error:
    backgroundColor: "{colors.danger-soft}"
    textColor: "{colors.ink}"
    rounded: "{rounded.xl}"
  card-default:
    backgroundColor: "{colors.surface-white}"
    textColor: "{colors.ink}"
    typography: "{typography.body-md}"
    rounded: "{rounded.xl}"
    padding: "{spacing.lg}"
  card-dark:
    backgroundColor: "{colors.surface-card}"
    textColor: "{colors.on-primary}"
    typography: "{typography.body-md}"
    rounded: "{rounded.xl}"
    padding: "{spacing.lg}"
  alert-error:
    backgroundColor: "{colors.danger-soft}"
    textColor: "{colors.danger-dark}"
    typography: "{typography.body-sm}"
    rounded: "{rounded.lg}"
    padding: "12px 16px"
  alert-success:
    backgroundColor: "{colors.success-soft}"
    textColor: "#166534"
    typography: "{typography.body-sm}"
    rounded: "{rounded.lg}"
    padding: "12px 16px"
  alert-warning:
    backgroundColor: "{colors.warning-soft}"
    textColor: "{colors.accent-gold-dark}"
    typography: "{typography.body-sm}"
    rounded: "{rounded.lg}"
    padding: "12px 16px"
  badge-status:
    backgroundColor: "{colors.surface-white}"
    textColor: "{colors.body}"
    typography: "{typography.micro}"
    rounded: "{rounded.xl}"
    padding: "8px 16px"
  status-pill:
    backgroundColor: "rgba(255,255,255,0.92)"
    textColor: "{colors.body}"
    typography: "{typography.caption}"
    rounded: "{rounded.xl}"
    padding: "8px 16px"
---

# PHRP UCP Design System

## Overview

Pahlawan Roleplay UCP is a **premium gaming User Control Panel** for a GTA-style SA-MP roleplay server. The product should feel **serious, cinematic, and elegant** — like a high-end game hosting client-area, not a corporate SaaS dashboard and not a flashy arcade site.

The visual identity is built on three pillars:

1. **Crimson primary** (`{colors.primary}`) — bold, confident action color. Used for CTAs, focus rings, links, and brand accents.
2. **Gold accent** (`{colors.accent-gold}`) — premium, warm highlight. Used sparingly for version badges, accent lines, and secondary emphasis.
3. **Warm neutral canvas** (`{colors.canvas}`) — clean off-white (`#fbf8f5`) background that avoids the sterile feel of pure white.

The auth surface (Login, Register, Forgot Password, OTP Verify, Discord Link) uses a **light-first** design: warm off-white canvas, white form cards, and crimson interactive states. The post-auth dashboard uses a **dark-first** design with `{colors.surface-deep}` through `{colors.surface-elevated}`.

Design tokens are defined in `index.html` as CSS custom properties (`:root`) and Tailwind `theme.extend` configuration.

## Colors

### Light Mode (Auth & Canvas)

| Token | Value | Role |
|---|---|---|
| `{colors.primary}` | `#d71920` | CTAs, focus rings, active links, brand accent |
| `{colors.primary-hover}` | `#ef2a2a` | CTA hover state |
| `{colors.primary-dark}` | `#9f121f` | CTA gradient end, pressed state, eyebrow text |
| `{colors.primary-soft}` | `#fff1f1` | Error alert background, soft highlight |
| `{colors.accent-gold}` | `#d88912` | Version badge, accent line end, secondary emphasis |
| `{colors.canvas}` | `#fbf8f5` | Page background (body) |
| `{colors.surface-white}` | `#ffffff` | Cards, form containers, inner panels |
| `{colors.surface-input}` | `#fbfaf8` | Input field backgrounds |
| `{colors.ink}` | `#161616` | Primary text |
| `{colors.body}` | `#55565b` | Secondary text, descriptions |
| `{colors.muted}` | `#7a7c83` | Placeholder text, disabled labels |
| `{colors.hairline}` | `rgba(15,23,42,0.08)` | Subtle borders, dividers |
| `{colors.hairline-strong}` | `rgba(15,23,42,0.12)` | Card borders, visible dividers |

### Dark Mode (Dashboard & Admin)

| Token | Value | Role |
|---|---|---|
| `{colors.surface-deep}` | `#0a0a0f` | Deepest background, page canvas |
| `{colors.surface-base}` | `#0e0e14` | Main content background |
| `{colors.surface-card}` | `#121218` | Cards, panels, stat widgets |
| `{colors.surface-panel}` | `#1a1a24` | Nested panels, header bars |
| `{colors.surface-elevated}` | `#22222e` | Elevated elements, dropdowns |
| `{colors.surface-input-dark}` | `#16161e` | Input fields in dark mode |
| `{colors.hairline-dark}` | `rgba(255,255,255,0.10)` | Standard dark borders |
| `{colors.hairline-dark-strong}` | `rgba(255,255,255,0.05)` | Subtle dark dividers |

### Semantic Status

| Token | Value | Role |
|---|---|---|
| `{colors.danger}` | `#dc2626` | Error states, destructive actions |
| `{colors.success}` | `#16a34a` | Success states, online indicator |
| `{colors.warning}` | `#d97706` | Warning states, pending actions |
| `{colors.discord}` | `#5865F2` | Discord brand integration |

Do not introduce one-off hex values in feature code. Add the value to the token system in `index.html` first, then reference it via `ph-{name}` Tailwind class or `var(--ph-{name})` CSS variable.

## Typography

The type system uses **Inter** for all UI text and **JetBrains Mono** for code, OTP inputs, version badges, and data values.

| Level | Size | Weight | Use |
|---|---|---|---|
| `{typography.display-lg}` | 34px / 800 | Extrabold | Auth slide titles, hero headings |
| `{typography.heading-xl}` | 26px / 700 | Bold | Auth form titles |
| `{typography.heading-md}` | 22px / 700 | Bold | Page titles (auth forms), section headers |
| `{typography.heading-sm}` | 16px / 700 | Bold | Card titles, group labels |
| `{typography.body-md}` | 14px / 400 | Regular | Default body text, descriptions |
| `{typography.body-sm}` | 13px / 400 | Regular | Alert text, helper text, form hints |
| `{typography.caption}` | 12px / 500 | Medium | Metadata, timestamps, table subtext |
| `{typography.micro}` | 10px / 700 | Bold + 0.2em tracking | Status values, player counts, version tags |
| `{typography.eyebrow}` | 10px / 700 | Bold + 0.2em track + uppercase | Kicker labels above form titles (`.ph-eyebrow`) |
| `{typography.button-md}` | 14px / 700 | Bold | Button labels, CTA text |
| `{typography.code-md}` | 14px / 400 (Mono) | Regular | OTP input, server IP display |
| `{typography.code-sm}` | 12px / 400 (Mono) | Regular | Small code/data values |

All heading text uses `text-gray-900 dark:text-white`. Body text uses `text-gray-600 dark:text-gray-300`. Muted text uses `text-gray-400 dark:text-gray-500`.

## Layout

### Spacing Scale

Use the `{spacing}` tokens for all gutters, padding, and margins:

| Token | Value | Use |
|---|---|---|
| `{spacing.xs}` | 4px | Icon-to-text gaps, tight padding |
| `{spacing.sm}` | 8px | Input padding, compact gaps |
| `{spacing.md}` | 16px | Form field gaps, card padding base |
| `{spacing.lg}` | 24px | Section gaps, card padding |
| `{spacing.xl}` | 32px | Between sections |
| `{spacing.xxl}` | 48px | Major section separators |
| `{spacing.section}` | 64px | Page-level vertical rhythm |

### Auth Layout

- **Desktop (≥ 768px):** 50/50 split — left roleplay slideshow panel, right white form card. Max card width `1180px`, card height `720px`.
- **Mobile (< 768px):** Form and server status only. Left slideshow hidden. Form area scrollable.
- Right panel inner card: `max-w-[430px]`, centered, wrapped in `.ph-auth-panel-inner` surface.

### Dashboard Layout

- Fixed left sidebar (`w-64`) on desktop, bottom tab bar on mobile.
- Content area uses `p-4 md:p-6` padding with `max-w-7xl` container.
- Cards arranged in CSS Grid with responsive columns.

## Elevation & Depth

| Surface | Shadow | Implementation |
|---|---|---|
| Card (light) | `shadow-sm` | `0 1px 2px rgba(0,0,0,0.05)` |
| Card (elevated) | `shadow-lg` | Standard Tailwind `shadow-lg` |
| Auth inner panel | `.ph-auth-panel-inner` | `0 18px 44px rgba(22,23,29,0.09), 0 1px 2px rgba(22,23,29,0.05)` |
| Auth card container | `.ph-shadow-card` | `0 18px 48px rgba(22,23,29,0.10)` |
| Primary CTA | `.ph-btn-primary` | `0 10px 18px rgba(159,18,31,0.18)` + inset highlights |
| Primary CTA hover | `.ph-btn-primary:hover` | `0 12px 24px rgba(159,18,31,0.22)` + translateY(-1px) |
| Crimson glow | `.ph-shadow-glow-crimson` | `0 10px 22px rgba(215,25,32,0.16)` |
| Status pill | `.ph-status-pill` | `0 10px 28px rgba(22,23,29,0.06), 0 1px 2px rgba(22,23,29,0.04)` |

Borders separate surfaces more than shadows. Use `border border-gray-200 dark:border-white/10` for standard card edges. Reserve shadows for elevated elements (modals, dropdowns, CTAs, status pill).

## Shapes

| Token | Value | Use |
|---|---|---|
| `{rounded.xs}` | 4px | Badges, tags, small indicators |
| `{rounded.sm}` | 6px | Inline code, small pills |
| `{rounded.md}` | 9px | Buttons (`.ph-btn-primary`) |
| `{rounded.lg}` | 10px | Inputs, alerts, small cards |
| `{rounded.xl}` | 12px | Cards, form containers, status pill |
| `{rounded.2xl}` | 16px | Larger cards, modals |
| `{rounded.3xl}` | 24px | Auth container (desktop) |
| `{rounded.full}` | 9999px | Avatars, circular indicators, progress dots |

Auth container uses `{rounded.3xl}` on desktop, `{rounded.none}` on mobile (full-bleed). Form inputs use `{rounded.xl}`. Primary buttons use `{rounded.md}`.

## Components

### Button Primary (`.ph-btn-primary`)

Crimson gradient CTA with inset highlight and multi-layer shadow. Used for all primary actions (Login, Register, Verify, Reset, Link Discord).

- **Default:** gradient `#ef2a2a → #d71920 → #9f121f`, `border-radius: 9px`, `font-weight: 700`
- **Hover:** gradient `#ff5a5f → #d71920 → #b91422`, `translateY(-1px)`, stronger shadow
- **Disabled:** `opacity: 0.55`, `cursor: not-allowed`
- **Padding:** `py-3.5` (14px vertical), full width in auth forms

### Button Secondary

White surface with gray border. Used for "Back", "Cancel", "Resend OTP".

- **Default:** `bg-white border border-gray-200 rounded-xl`, `font-weight: 600`
- **Hover:** `bg-gray-50`, subtle border darkening

### Button Discord

Discord brand blue (`{colors.discord}`). Used exclusively for Discord link action.

- **Default:** `bg-[#5865F2]`, white text, `rounded-xl`
- **Hover:** `bg-[#4752C4]`, slight lift (`translateY(-0.5)`)

### Text Input (`.ph-input-focus`)

Off-white input with crimson focus ring. Shared across all auth forms via `InputGroup.tsx`.

- **Default:** `bg-[#fbfaf8] border border-gray-200 rounded-xl`, `py-3.5`
- **Focus:** `border-color: rgba(215,25,32,0.46)`, `box-shadow: 0 0 0 3px rgba(215,25,32,0.10)`, background turns `#ffffff`
- **Error:** `border-red-500`, `bg-red-50/10`, error text below input in `text-[10px]`

### Card

White surface card with subtle border and shadow. Used for dashboard panels, form containers, stat widgets.

- **Light:** `bg-white border border-gray-200 rounded-xl shadow-sm`
- **Dark:** `dark:bg-[#121218] dark:border-white/10`
- **Padding:** `p-4 md:p-6`

### Alert (`.ph-alert`)

Inline alert banner. Replaces the old full-screen error modal.

- **Error** (`.ph-alert-error`): `bg-rgba(255,241,241,0.95)`, `border: 1px solid rgba(215,25,32,0.18)`, text `#9f121f`
- **Success** (`.ph-alert-success`): `bg-rgba(240,253,244,0.95)`, `border: 1px solid rgba(22,163,74,0.18)`, text `#166534`
- **Warning** (`.ph-alert-warning`): `bg-rgba(255,251,235,0.95)`, `border: 1px solid rgba(216,137,18,0.22)`, text `#92400e`
- **Animation:** `authSlideDown 0.3s ease-out`

### Status Pill (`.ph-status-pill`)

Compact server status indicator in the auth right panel. Shows: Online/Offline status + player count + server IP.

- **Surface:** `rgba(255,255,255,0.92)`, `1px border rgba(15,23,42,0.10)`, subtle shadow
- **Layout:** 3-column grid, `rounded-xl`, separated by thin dividers
- **Icons:** `size={13}`, neutral gray color

### Eyebrow Kicker (`.ph-eyebrow`)

Small uppercase micro-text label above form titles. Color: `{colors.primary-dark}` (`#9f121f`).

- **Style:** `font-size: 10px`, `font-weight: 700`, `letter-spacing: 0.2em`, `text-transform: uppercase`
- **Usage:** "Secure Account Access", "Bergabung Bersama Kami", "Account Recovery", "Email Verification", "Tautan Berhasil"

## Do's and Don'ts

### Do

- Use semantic design tokens from this file. Reference them via `ph-{name}` Tailwind classes or `var(--ph-{name})` CSS variables.
- Reuse existing component classes: `.ph-btn-primary`, `.ph-input-focus`, `.ph-alert`, `.ph-status-pill`, `.ph-eyebrow`, `.ph-auth-panel-inner`, `.ph-page-vignette`, `.ph-scroll-thin`.
- Keep keyboard focus visible — the crimson focus ring (`ph-input-focus`) must remain on all interactive elements.
- Use Bahasa Indonesia consistently for all user-facing auth text.
- Use inline alerts (`.ph-alert`) for non-blocking errors. Reserve modals only for critical/destructive confirmations.
- Test at 390x844 (mobile), 900x1024 (tablet), and 1920x1080 (desktop) before shipping.
- Add new tokens to `index.html` `:root` and Tailwind `theme.extend` before using them in components.

### Don't

- Hard-code hex colors in feature code when a semantic token exists (e.g., do not write `bg-[#121218]` — use `bg-ph-surface-card`).
- Hard-code Discord brand color `#5865F2` — use `bg-ph-discord` once the token is added to Tailwind config.
- Create new arbitrary font sizes (`text-[13px]`, `text-[10.5px]`) — use the typography scale or add a new named level.
- Create new arbitrary shadow expressions — use the documented elevation tokens or add a new named shadow.
- Remove or weaken the crimson focus ring on inputs.
- Use native `alert()` or `confirm()` dialogs — use `.ph-alert` inline alerts.
- Mix English and Indonesian in user-facing auth copy.
- Apply `backdrop-blur` to surfaces without a clear visual reason — prefer solid surfaces with subtle borders.
- Create one-off component variants (e.g., a "special" button) without documenting them here.

## Responsive Behavior

### Breakpoints

| Breakpoint | Width | Layout |
|---|---|---|
| Mobile | < 640px | Single column, bottom tab nav, form-only auth |
| Tablet | 640px–1023px | Two columns where needed, sidebar nav on larger tablets |
| Desktop | ≥ 1024px | Split-panel auth, sidebar nav, multi-column dashboard |

### Auth Responsive Rules

- **Mobile (< 768px):** Left slideshow panel is `hidden`. Right panel fills the screen. Server status visible as compact pill. Form area scrollable with `.ph-scroll-thin`.
- **Desktop (≥ 768px):** 50/50 split. Left panel shows roleplay slideshow (images at original color with neutral readability gradient). Right panel shows form card centered in available space.
- Auth card: `rounded-[24px]` on desktop, `rounded-none` on mobile (full-bleed).
- Touch targets: all buttons and interactive elements ≥ 40px height on mobile.

### Dashboard Responsive Rules

- Sidebar collapses to bottom tab bar on mobile.
- Stat cards use responsive grid: 1 column mobile, 2 columns tablet, 4 columns desktop.
- Tables use horizontal scroll on mobile.
- Admin panels use `flex-col md:flex-row` for responsive stacking.

## Animations

| Name | Duration | Easing | Use |
|---|---|---|---|
| `auth-fade-in` | 0.4s | ease-out | Auth container entrance |
| `auth-slide-up` | 0.4s | ease-out | Form content entrance |
| `auth-slide-down` | 0.25s | ease-out | Alert banner entrance |
| `auth-scale-in` | 0.3s | ease-out | Modal/dialog entrance |
| `float` | 6s | ease-in-out infinite | Decorative floating elements |
| `pulse-slow` | 4s | cubic-bezier(0.4,0,0.6,1) | Subtle pulsing backgrounds |
| CTA hover | 0.22s | cubic-bezier(0.2,0.8,0.2,1) | Button lift and shadow transition |

## Selection & Scrollbar

- **Selection:** `{colors.primary}` background, white text (`::selection`).
- **Global scrollbar:** 4px width, neutral thumb (`rgba(0,0,0,0.15)` light / `rgba(255,255,255,0.10)` dark), crimson hover.
- **Auth form scrollbar** (`.ph-scroll-thin`): thin native scrollbar, neutral tint.

## Known Gaps

- **`needs-design-decision`** — Dark mode for auth surfaces is not implemented. The auth UI is intentionally light-only. If dark-mode auth is needed, a new OpenSpec change should define the dark auth tokens and component states.
- **`needs-design-decision`** — Discord brand color `#5865F2` is used as raw Tailwind arbitrary value in 3 files. A `ph-discord` token should be added to `index.html` Tailwind config.
- **`needs-design-decision`** — Several dashboard/admin components still use raw hex dark-surface colors (`#0a0a0a`, `#121212`, `#151515`, `#1a1a1a`) instead of semantic `ph-surface-*` tokens. These should be batch-migrated.
- **`needs-design-decision`** — Typography uses many arbitrary pixel sizes (`text-[9px]`, `text-[10px]`, `text-[11px]`, `text-[13px]`, etc.). Named typography levels should be added to the scale for recurring sizes.
- **`needs-design-decision`** — Non-token shadow expressions are common (25+ unique `shadow-[...]` values). Named shadow tokens should be added for recurring patterns (glow-discord, glow-success, glow-danger, sidebar).
- **`needs-design-decision`** — `AdminSetup.tsx` contains an email template rendered entirely with inline `style={{}}` attributes. This should be extracted to a component or server-side template.
