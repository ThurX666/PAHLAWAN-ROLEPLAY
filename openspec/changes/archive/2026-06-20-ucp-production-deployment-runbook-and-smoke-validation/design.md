## Context

Website/UCP saat ini sudah memiliki baseline env-first configuration, email/OTP runtime yang fail-closed, dan local smoke flow yang lebih aman. Namun deploy production masih rawan drift karena operator perlu menyelaraskan beberapa hal sekaligus: hasil build frontend, package PHP/Composer, layout repo vs XAMPP/htdocs, file private `.env`, dan validasi auth/session/email pasca-deploy. Tantangan utamanya bukan fitur baru di runtime, melainkan memastikan operator memiliki prosedur yang konsisten, aman, dan dapat diaudit sebelum launch komunitas.

Stakeholder utama untuk change ini adalah operator deploy, admin UCP, dan reviewer release. Constraint utama:
- repo tetap source of truth
- XAMPP runtime hanya target deploy, bukan planning source
- tidak boleh menambah langkah yang membuka secret
- tidak boleh memaksa perubahan schema, migration, BOT runtime, atau Pawn/gamemode

## Goals / Non-Goals

**Goals:**
- Mendefinisikan runbook production deployment UCP yang mencakup package checklist, env contract, layout mapping, authorized smoke validation, rollback, dan launch readiness.
- Memisahkan dengan jelas mana artifact yang boleh ditrack di repo dan mana yang hanya boleh ada di private deployment runtime.
- Menentukan urutan verifikasi pasca-deploy yang aman untuk session/auth, email runtime readiness, build output, dan API diagnostics.
- Menyediakan dasar OpenSpec agar implementasi dokumentasi/automation berikutnya bisa dikerjakan bertahap tanpa ambiguity.

**Non-Goals:**
- Tidak mengimplementasikan script deploy otomatis pada change ini.
- Tidak mengubah endpoint, auth flow, email runtime, BOT runtime, Pawn/gamemode, atau database schema.
- Tidak menyimpan atau memvalidasi nilai secret production secara langsung.
- Tidak mengganti XAMPP dengan stack deployment baru.

## Decisions

### 1. Gunakan capability baru khusus runbook deployment
- Keputusan: buat capability baru `ucp-production-deployment-runbook`.
- Alasan: fokus change ini adalah operational launch readiness, bukan perubahan requirement dari local auth flow atau email runtime yang sudah ada.
- Alternatif yang dipertimbangkan:
  - Memodifikasi `ucp-local-auth-dev-flow`: ditolak karena scope capability itu lokal/dev-oriented.
  - Memodifikasi `ucp-email-otp-runtime`: ditolak karena runbook deployment lebih luas dari mail runtime saja.

### 2. Pisahkan checklist menjadi enam domain operasional
- Keputusan: requirement dibagi menjadi package/dependency readiness, env contract, layout sync, authorized smoke validation, rollback, dan launch readiness.
- Alasan: domain ini cocok dengan tahapan deploy nyata dan memudahkan apply phase dipecah kecil-kecil.
- Alternatif:
  - Checklist tunggal panjang: ditolak karena sulit diverifikasi dan rawan miss langkah.

### 3. Gunakan secret-safe diagnostics sebagai sumber verifikasi
- Keputusan: semua verifikasi pasca-deploy harus memakai readiness/health metadata dan bounded smoke requests, bukan output secret atau dump runtime.
- Alasan: production launch perlu bukti readiness tanpa membuka `.env`, credential, OTP, cookie, session, atau provider response detail.
- Alternatif:
  - Menyalin `.env` atau output penuh endpoint untuk verifikasi: ditolak karena tidak aman.

### 4. Jadikan rollback sebagai requirement eksplisit, bukan catatan tambahan
- Keputusan: rollback plan menjadi requirement setara dengan deploy dan smoke validation.
- Alasan: launch komunitas butuh keputusan go/no-go yang cepat jika smoke test gagal, tanpa improvisasi operator.
- Alternatif:
  - Rollback hanya disebut di README/deployment notes: ditolak karena terlalu lemah sebagai source of truth.

## Risks / Trade-offs

- [Runbook terlalu umum] → Mitigasi: requirement dan task harus menyebut layout repo, XAMPP/htdocs, build/vendor, dan endpoint smoke yang konkret.
- [Operator menganggap smoke validation mengizinkan akses secret] → Mitigasi: spec secara eksplisit membatasi output hanya ke status/path/readiness yang aman.
- [Scope melebar ke automation/deploy script] → Mitigasi: tandai automation sebagai non-goal untuk change ini.
- [Kebutuhan production berbeda antar host] → Mitigasi: runbook fokus pada kontrak minimum dan langkah verifikasi yang tetap valid di layout XAMPP saat ini.

- [Composer tidak tersedia di semua host] → Mitigasi: runbook harus membedakan vendor built on-host vs packaged-before-sync sebagai keputusan deploy yang eksplisit.

## Migration Plan

1. Tambahkan proposal, design, spec delta, dan task checklist untuk runbook deployment production.
2. Review requirement dengan operator deploy agar layout repo dan XAMPP target sudah sesuai.
3. Implementasi dokumentasi/checklist/diagnostic improvements hanya setelah change ini di-approve.
4. Saat change implementasi berikutnya selesai, lakukan smoke validation terotorisasi sesuai runbook sebelum production launch.
5. Jika deploy gagal, ikuti rollback checklist untuk mengembalikan package dan runtime ke release sebelumnya yang tervalidasi.

## Open Questions

- Apakah package deploy production akan selalu dibangun dari repo lokal lalu disync ke XAMPP, atau sebagian dependency tetap dibangun on-host?
- Endpoint readiness mana yang sudah cukup untuk production smoke tanpa perlu penambahan diagnostic baru?
- Apakah launch komunitas memerlukan freeze checklist terpisah untuk admin/operator di luar runbook UCP ini?
