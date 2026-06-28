# UCP UI Polish — Improve Website UI/UX untuk Alpha Test

## Why

Alpha Test 1 Agustus 2026 adalah momen pertama tim internal melihat dan menggunakan UCP secara
menyeluruh. Kesan pertama menentukan kepercayaan terhadap project. Saat ini UCP sudah
fungsional (auth, dashboard, karakter, settings, donations, tickets) tetapi UI masih barebone —
inline style tanpa design system, tidak branded, dan belum responsive optimal. Polish UI
sebelum Alpha Test = investasi kecil yang meningkatkan kepuasan tim internal dan membuat
UCP layak ditunjukkan ke calon pemain.

## What Changes

1. **Design token & color system** — Brand palette Pahlawan RP (gold, dark, accent) sebagai
   CSS custom properties atau Tailwind config, ganti inline hex yang tersebar.
2. **Responsive layout** — Mobile-first breakpoint untuk Dashboard, CharacterList,
   CharacterDetail, Settings, Auth. Saat ini layout cenderung fixed-width.
3. **Auth page redesign** — Halaman login/register/verify/forgot/discord yang lebih modern,
   tambah ilustrasi/branding, flow indicator yang jelas.
4. **Dashboard polish** — Server stats card, karakter summary, aktivitas chart yang lebih rapi
   dengan spacing dan typography konsisten.
5. **Navigation & Layout** — Sidebar/navbar yang lebih branded, loading states, empty states,
   micro-interactions (hover, transition).
6. **Typography & spacing** — Consistent font scale, heading hierarchy, spacing system.

## Non-Goals

- Tidak rewrite seluruh frontend (tetap React + Vite)
- Tidak ganti library utama (lucide-react, recharts, react-easy-crop)
- Tidak tambah fitur bisnis baru (hanya visual polish)
- Tidak ubah API backend

## Anchor

- ROADMAP: Alpha Test — "Improve UI website UCP (responsive, branding, UX polish)"
- Related: cross-service-auth-flow (auth sudah stabil, UI menyusul)

## Risks

- Polish bisa terasa subjektif — patok pada best practice modern (spacing, typography, color
  contrast, mobile responsive)
- Jangan over-polish sampai telat Alpha Test — iterasi 2-3 hari, stop saat "good enough"
