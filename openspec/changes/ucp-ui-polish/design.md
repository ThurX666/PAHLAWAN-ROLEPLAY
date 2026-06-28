# UCP UI Polish — Design Notes

## Design Decisions

### 1. Design Token System
- **Approach:** CSS custom properties di `:root` (index.css) + komponen React baca token via
  CSS vars
- **Skip Tailwind** — tidak mau tambah build step dependency; CSS vars cukup untuk scope
  ini dan tetap performan tanpa purging concern
- **Palette:**
  ```
  --color-brand-gold: #D4A843
  --color-brand-dark: #0F1117
  --color-brand-darker: #060810
  --color-brand-accent: #E8C35C
  --color-surface: #1A1C24
  --color-surface-raised: #252836
  --color-text-primary: #F0F0F5
  --color-text-secondary: #8A8D9F
  --color-success: #34D399
  --color-danger: #F87171
  --color-warning: #FBBF24
  ```

### 2. Responsive Breakpoints
- Mobile: < 768px (single column, stacked cards, hamburger nav)
- Tablet: 768px–1024px (2-column grid where applicable)
- Desktop: > 1024px (sidebar + main content, multi-column)

### 3. Auth Page Redesign
- Layout: split screen — kiri branding/logo/ilustrasi, kanan form
- Mobile: full-screen form dengan logo di atas
- Flow indicator: step-by-step (Login → Verify → Dashboard, Register → OTP → Verify →
  Dashboard → Discord Link)
- Smooth transition antar view (fade/slide)

### 4. Dashboard Polish
- Server stats: 4 card grid (players online, uptime, faction, ekonomi) dengan icon lucide-react
- Character summary: card per karakter dengan avatar placeholder, level, faction badge
- Activity chart: recharts tetap dipakai, hanya styling yang diperbaiki
- Empty states: ilustrasi + CTA untuk user baru (belum punya karakter, belum link Discord)

### 5. Navigation
- Sidebar (desktop): logo Pahlawan RP, menu items dengan icon, user profile di bottom
- Topbar (mobile): hamburger → drawer menu
- Active state indicator, badge untuk notifikasi inbox
- Loading skeleton untuk data fetch

### 6. Micro-interactions
- Hover scale pada card dan button
- Transition 200ms ease pada color/background/transform
- Toast notification untuk sukses/error (ganti alert browser)

## Risks / Trade-offs

- **Tidak pakai Tailwind** → lebih banyak CSS manual, tapi tidak ada dependency baru dan
  output lebih kecil. Jika nanti project scale up, bisa migrate ke Tailwind bertahap.
- **CSS vars vs CSS-in-JS** → CSS vars dipilih karena zero-runtime, SSR-friendly, dan bisa
  dishare ke komponen via `var()` di inline style.
- **Breaking changes minimal** → hanya ganti styling, tidak ubah struktur komponen atau API
  call. Rollback mudah kalau ada issue.
