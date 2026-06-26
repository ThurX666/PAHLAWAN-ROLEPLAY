# improve-auth-ui-flow — Proposal

## Why

Halaman authentication UCP (Login, Register, Forgot Password, OTP Verify, Discord Link) saat ini sudah fungsional dan backend berjalan stabil. Namun dari sisi UI/UX, terdapat beberapa masalah yang menurunkan kesan profesional dan identitas brand PHRP:

### Masalah UI Saat Ini

1. **Inkonsistensi visual antar halaman auth** — Setiap form auth memiliki spacing, animasi, dan layout yang sedikit berbeda. VerifyForm menggunakan `slideInUp`, form lain `fadeIn`. Border radius dan padding tidak seragam.

2. **Tidak ada design system/token terpusat** — Warna, spacing, shadow, dan typography langsung di-hardcode sebagai Tailwind utility di setiap komponen. Mengubah theme berarti mengedit semua file satu per satu.

3. **Dark theme kurang premium** — Background `#050505`/`#121212` sudah gelap, tetapi belum memanfaatkan crimson/gold sebagai accent yang kuat. Kesan "gaming roleplay dashboard" belum terasa.

4. **InputGroup kurang polished** — Error state hanya menampilkan teks kecil `text-[10px]`. Tidak ada focus ring yang jelas. Password toggle icon kurang visible di dark mode.

5. **Responsive mobile kurang optimal** — Di mobile, container auth mengambil `h-[100dvh]` tanpa scrollable area yang nyaman. Server status bar overlay bisa menimpa konten. Spacer `-mb-9` adalah hack yang fragile.

6. **Error modal terlalu agresif** — Error ditampilkan sebagai full-screen modal overlay (`z-[100]`), bahkan untuk error login sederhana. Ini mengganggu flow user.

7. **Flow antar halaman terputus** — Tidak ada progress indicator atau breadcrumb visual. User tidak tahu posisinya di flow register → verify → discord.

8. **Copywriting campuran bahasa** — Beberapa teks Inggris ("Welcome Back", "Create Account"), beberapa Indonesia ("Akses Ditolak", "Kembali ke Halaman Login"). Perlu konsistensi.

9. **ForgotPasswordForm menggunakan `alert()`** — Setelah reset password berhasil, menggunakan `alert()` browser native — sangat tidak profesional.

10. **DiscordLinkForm tidak ada tombol kembali** — Jika user masuk ke halaman Discord link, tidak ada cara untuk kembali ke login tanpa refresh.

## What Changes

Melakukan UI/UX overhaul pada **seluruh halaman auth** dengan pendekatan:

- **Membuat design token system** — CSS custom properties untuk warna PHRP (crimson, gold, dark slate), spacing scale, border radius, shadow, dan typography.
- **Redesign auth container layout** — Memperbaiki responsive behavior, scroll handling, spacer hack, dan split-panel layout.
- **Improve setiap form component** — Konsistensi animasi, spacing, error/success state, visual hierarchy, dan copywriting.
- **Membuat shared UI primitives** — Button, Alert, Badge component yang reusable di seluruh auth flow.
- **Memperbaiki mobile experience** — Touch-friendly inputs, proper safe area handling, readable server status.
- **Progress indicator** — Visual step indicator untuk flow register → verify → discord.

### Yang TIDAK berubah:
- Endpoint API (`auth.php`, `register.php`, `verify.php`, `resend_otp.php`, `forgot.php`, `discord_link.php`)
- FormData body format dan `credentials: 'include'`
- Login handler logic (`handleLoginSubmit`)
- Register success flow (`handleRegisterSuccess`)
- Discord OAuth callback logic
- OTP cooldown/timer logic
- Device info detection
- Slideshow data dan auto-rotate
- `AuthView` type union
- Preview/simulation mode logic
- `config.ts`, `types.ts`
- Backend PHP files
- Database queries
- Session/token management

## Capabilities

### Modified Capabilities
- `auth-ui-login`: Redesign login form dengan dark theme premium, konsisten spacing, improved error state
- `auth-ui-register`: Redesign register form dengan visual hierarchy yang lebih baik, password strength hint
- `auth-ui-forgot-password`: Redesign forgot password dengan step indicator, menghapus `alert()` native
- `auth-ui-verify-otp`: Redesign OTP verification dengan individual digit input style, improved timer display
- `auth-ui-discord-link`: Redesign Discord link page dengan back navigation, improved Discord branding
- `auth-container`: Redesign main auth container, responsive layout, server status bar, logo placement
- `auth-input-group`: Improve InputGroup dengan better focus state, error display, dark mode visibility
- `auth-error-modal`: Redesign error notification — inline alert instead of full-screen modal untuk error ringan

### New Capabilities
- `auth-design-tokens`: CSS custom properties untuk PHRP brand colors, spacing, typography
- `auth-flow-indicator`: Visual step/progress indicator untuk multi-step auth flows

## Impact

### Scope Halaman yang Disentuh
| File | Tipe Perubahan |
|------|---------------|
| `WEBSITE/Auth.tsx` | Layout, container, error display, slideshow styling |
| `WEBSITE/components/auth/LoginForm.tsx` | UI redesign, copywriting |
| `WEBSITE/components/auth/RegisterForm.tsx` | UI redesign, copywriting |
| `WEBSITE/components/auth/ForgotPasswordForm.tsx` | UI redesign, remove `alert()`, step indicator |
| `WEBSITE/components/auth/VerifyForm.tsx` | UI redesign, OTP input style |
| `WEBSITE/components/auth/DiscordLinkForm.tsx` | UI redesign, add back navigation |
| `WEBSITE/components/auth/InputGroup.tsx` | Focus state, error display, dark mode |
| `WEBSITE/index.html` | Design tokens CSS, mungkin font tambahan |

### Halaman yang TIDAK Disentuh
| File | Alasan |
|------|--------|
| `WEBSITE/App.tsx` | Auth gate logic sudah benar |
| `WEBSITE/components/Layout.tsx` | Post-login layout, di luar scope |
| `WEBSITE/components/Dashboard.tsx` | Post-login page |
| `WEBSITE/config.ts` | Config tidak perlu diubah |
| `WEBSITE/types.ts` | Interface tidak berubah |
| `WEBSITE/public/api/*.php` | Backend tidak disentuh |
| `WEBSITE/components/auth/SimulationInfo.tsx` | Preview widget, prioritas rendah |
| Semua file di `components/admin/` | Admin panel, di luar scope |
| Semua file di `components/dashboard/` | Dashboard, di luar scope |
| Semua file di `components/settings/` | Settings, di luar scope |

### Risiko Perubahan

| Risiko | Level | Mitigasi |
|--------|-------|----------|
| Tailwind class changes merusak layout existing | **Medium** | Test visual di setiap breakpoint sebelum dan sesudah |
| Dark/light mode inconsistency | **Low** | Design tokens memastikan konsistensi otomatis |
| Form submission behavior berubah | **Low** | Tidak mengubah handler/logic, hanya UI wrapper |
| Discord OAuth redirect break | **Low** | `window.location.href` redirect tidak disentuh |
| Mobile scroll behavior regression | **Medium** | Test di actual mobile viewport, bukan hanya DevTools |
| Slideshow performance | **Low** | Tidak mengubah slideshow logic, hanya CSS refinement |
| Asset loading break | **Low** | Path asset (`logo1.png`, slideshow images) tidak diubah |

## Arah Desain

### Theme & Identity
- **Dark theme utama** — Background `#0a0a0f` to `#121218` gradient
- **Crimson primary** — `#991b1b` (dark red) untuk accent utama, `#dc2626` untuk hover/active
- **Gold secondary** — `#d97706` untuk highlight, badge, premium indicator
- **Dark slate** — `#1a1a2e` untuk card/panel background
- **Clean typography** — Inter (already loaded), weight hierarchy: 800 headers, 600 labels, 400 body

### Visual Style
- Gaming roleplay dashboard — tegas, clean, tidak berlebihan
- Glassmorphism ringan pada card (backdrop-blur, subtle border)
- Micro-animations: fade-in, subtle slide, focus ring pulse
- Tidak ada particle effects, parallax, atau animasi berat
- Consistent 8px spacing grid
- Border radius: 12px cards, 10px inputs, 8px buttons

### Component Consistency
- Button: crimson gradient primary, ghost secondary, discord blue tertiary
- Input: dark background, subtle border, red focus ring, left icon
- Alert: inline banner (tidak full-screen modal), color-coded (red error, green success, amber warning)
- Card: dark glass panel, 1px border, subtle shadow
- Link: underline on hover, gold accent color

### Responsive Strategy
- Mobile-first
- Single column on mobile (< 768px), split panel on desktop (≥ 768px)
- Slideshow panel hidden on mobile (existing behavior, tetap)
- Server status bar: smaller pill on mobile, expandable on desktop
- Touch targets minimum 44px
