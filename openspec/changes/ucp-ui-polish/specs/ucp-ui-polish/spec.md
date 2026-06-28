# UCP UI Polish — Spec

> Phase: Alpha (ROADMAP Pre-Alpha → Alpha Test)

## Requirements

### Requirement: Design token system
CSS custom properties sebagai single source of truth untuk semua warna, spacing, radius,
shadow, dan typography. Tidak ada hardcoded hex/rgb di komponen React.

### Requirement: Responsive layout
Semua halaman UCP harus usable di mobile (320px+), tablet, dan desktop. Layout adaptif
dengan CSS media queries — bukan zoom-out atau horizontal scroll.

### Requirement: Branded auth page
Halaman login/register memiliki branding Pahlawan RP yang jelas: logo, nama server, tagline.
Form styling konsisten dengan error/loading/success states.

### Requirement: Consistent component styling
Card, button, input, modal, toast — semua pakai token dari design system. Tidak ada komponen
yang "beda sendiri".

### Requirement: Micro-interactions
Hover, focus, active, transition pada elemen interaktif. Minimal 200ms ease transition pada
semua color/background/transform change.

### Requirement: Loading & empty states
Setiap komponen yang fetch data punya loading skeleton. Setiap list/kosong punya empty state
dengan ilustrasi dan CTA.

### Requirement: Accessibility minimum
Color contrast WCAG AA (4.5:1 untuk text normal, 3:1 untuk large text). Focus ring visible
pada semua input dan button.
