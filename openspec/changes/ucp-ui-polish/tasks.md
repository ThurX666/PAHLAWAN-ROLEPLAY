# UCP UI Polish — Tasks

## 1. Design Token & Foundation

- [x] **1.1** Define CSS custom properties di `index.css` (palette, spacing, radius, shadow, font)
- [x] **1.2** Buat `theme.ts` utility untuk baca CSS var dari TypeScript
- [x] **1.3** Ganti semua inline hex color di komponen dengan CSS var
- [x] **1.4** Setup responsive breakpoint utility classes

## 2. Auth Page Redesign

- [x] **2.1** Redesign `Auth.tsx` layout: split screen (branding kiri, form kanan)
- [x] **2.2** Mobile layout: full-screen form + logo
- [x] **2.3** Polish `LoginForm.tsx` — spacing, typography, error states
- [x] **2.4** Polish `RegisterForm.tsx` — spacing, typography, validation feedback
- [x] **2.5** Polish `VerifyForm.tsx` — OTP input styling, timer visual
- [x] **2.6** Polish `ForgotPasswordForm.tsx` — consistent dengan form lainnya
- [x] **2.7** Polish `DiscordLinkForm.tsx` — branding, CTA button
- [x] **2.8** Flow indicator: step progress bar antar auth view

## 3. Dashboard

- [ ] **3.1** Redesign server stats cards (icon + value + label)
- [ ] **3.2** Redesign karakter summary section (card grid)
- [ ] **3.3** Polish recharts activity chart (colors, tooltip, axis)
- [ ] **3.4** Empty state untuk user baru (belum punya karakter)
- [ ] **3.5** Loading skeleton untuk dashboard data

## 4. Character Pages

- [ ] **4.1** Polish `CharacterList.tsx` — card layout, avatar placeholder, faction badge
- [ ] **4.2** Polish `CharacterDetail.tsx` — stats display, inventory grid
- [ ] **4.3** Polish `CharacterStory.tsx` — story timeline, CTA button

## 5. Navigation & Layout

- [ ] **5.1** Redesign `Layout.tsx` sidebar — logo, menu items, user profile footer
- [ ] **5.2** Mobile responsive: hamburger → drawer
- [ ] **5.3** Active nav state indicator + inbox badge

## 6. Settings & Misc

- [ ] **6.1** Polish `Settings.tsx` — tab layout, form consistency
- [ ] **6.2** Polish `Donation.tsx` — card pricing, CTA
- [ ] **6.3** Polish `TicketSystem.tsx` — list + detail view

## 7. Micro-interactions & Polish

- [ ] **7.1** Add hover/focus transitions (card scale, button glow, nav highlight)
- [ ] **7.2** Toast notification system (sukses/error/info)
- [ ] **7.3** Page transition (fade/slide antar route)

## 8. Validation & QA

- [ ] **8.1** Mobile responsive test — iPhone SE, Pixel, iPad (Chrome DevTools)
- [ ] **8.2** Color contrast check (WCAG AA minimum)
- [ ] **8.3** Cross-browser smoke: Chrome, Firefox, Edge
- [ ] **8.4** Update ROADMAP.md Alpha Test checklist
