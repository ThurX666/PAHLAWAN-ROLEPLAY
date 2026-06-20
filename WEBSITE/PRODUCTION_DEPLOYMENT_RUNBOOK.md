# WEBSITE/UCP Production Deployment Runbook

Dokumen ini adalah baseline runbook deployment production untuk Website/UCP. Fokus dokumen ini hanya pada package checklist, env contract, layout mapping, dan asumsi target deploy. Dokumen ini tidak mengubah runtime behavior dan tidak menggantikan private operator notes.

## 1. Source of truth dan target deploy

- Repo tetap source of truth untuk Website/UCP.
- Target deploy saat ini diasumsikan layout flattened XAMPP:
  - runtime root: `C:\xampp\htdocs\pahlawan_roleplay`
  - API root: `C:\xampp\htdocs\pahlawan_roleplay\api`
- Private `.env` hanya boleh berada di runtime root target:
  - repo local: `WEBSITE/.env`
  - XAMPP deploy: `C:\xampp\htdocs\pahlawan_roleplay\.env`
- XAMPP runtime bukan source of truth planning. Perubahan manual di target deploy harus dianggap drift dan disinkronkan kembali ke repo lewat change terpisah bila memang disetujui.

## 2. Keputusan Composer/vendor

Keputusan baseline untuk launch:

- Composer dependency PHP HARUS dipaketkan dari repo, bukan menjadi syarat build on-host.
- Artifact deploy harus membawa:
  - `WEBSITE/vendor/`
  - `WEBSITE/composer.json`
  - `WEBSITE/composer.lock`
- `composer install` on-host boleh dipakai hanya sebagai recovery path terotorisasi jika package vendor yang tervalidasi tidak tersedia, dan tetap harus mengikuti `composer.lock`.
- Legacy fallback `api/PHPMailer/src` hanya dianggap compatibility fallback transisi, bukan baseline package production baru.

Alasan:

- lebih repeatable untuk launch komunitas
- tidak bergantung pada Composer CLI di host production
- mengurangi risiko drift dependency antar host

## 3. Deployment package checklist

### Wajib ikut deployment

Frontend:

- hasil build `WEBSITE/dist/`

Backend/API:

- `WEBSITE/public/api/`
- file PHP pendukung di bawah `WEBSITE/public/` yang memang dipakai runtime web
- `WEBSITE/vendor/`
- `WEBSITE/composer.json`
- `WEBSITE/composer.lock`

Konfigurasi contoh/dokumen:

- `WEBSITE/.env.production.example`
- `WEBSITE/env.example`
- dokumen runbook ini bila operator ingin menyimpannya bersama release notes internal

### Wajib ada di host, tetapi tidak boleh ikut commit

- private `WEBSITE/.env` atau private `.env` di runtime deploy
- credential SMTP
- credential/provider key
- cookie/session runtime
- log runtime private

### Tidak boleh dijadikan package production

- `WEBSITE/node_modules/`
- `WEBSITE/tests/`
- local `.runtime-logs/`
- file helper smoke/test yang hanya relevan untuk local development
- secret file atau dump apa pun

## 4. Mapping repo ke layout XAMPP

Asumsi deploy flattened:

| Repo source | Target XAMPP |
| --- | --- |
| `WEBSITE/dist/*` | `C:\xampp\htdocs\pahlawan_roleplay\` |
| `WEBSITE/public/api/*` | `C:\xampp\htdocs\pahlawan_roleplay\api\` |
| `WEBSITE/vendor/*` | `C:\xampp\htdocs\pahlawan_roleplay\vendor\` |
| `WEBSITE/.env` private | `C:\xampp\htdocs\pahlawan_roleplay\.env` private |

Catatan:

- jangan arahkan `.env` ke `C:\xampp\htdocs\.env`
- jangan jadikan `WEBSITE/public/api/PHPMailer/src` sebagai baseline package baru
- hasil `dist` adalah web root deploy, bukan folder `public/` mentah

## 5. Env contract local vs production

### Local contract

Wajib eksplisit:

- `APP_ENV=local`
- `VITE_API_BASE_URL=api`
- `VITE_DEV_API_PROXY_TARGET=http://127.0.0.1:8000`
- `UCP_ALLOWED_ORIGINS` local
- `UCP_LOCAL_MAIL_MODE=preview` atau `smtp`

Opsional khusus test:

- `UCP_LOCAL_OTP_RESEND_COOLDOWN_SECONDS=0` hanya untuk authorized local preview smoke

### Production contract

Wajib eksplisit:

- `APP_ENV=production`
- `UCP_LOCAL_MAIL_MODE=smtp`
- `VITE_API_BASE_URL` ke URL API publish yang benar
- `UCP_ALLOWED_ORIGINS` ke origin frontend publish
- SMTP lengkap di private `.env`
- provider/server credential hanya di private `.env` atau process environment

### Track vs private

Boleh ditrack:

- `.env.local.example`
- `.env.production.example`
- `env.example`

Tidak boleh ditrack:

- `.env`
- nilai secret nyata
- token, credential, OTP, cookie, session, provider error detail

## 6. Pre-deploy verification sebelum smoke runtime

Sebelum mulai smoke test runtime nyata, operator harus memastikan:

1. frontend build production sudah tersedia di `WEBSITE/dist`
2. `vendor/autoload.php` tersedia
3. package deploy berisi `dist`, `public/api`, `vendor`, `composer.json`, `composer.lock`
4. private `.env` target deploy sudah disiapkan di runtime root
5. env example tidak dipakai sebagai file secret live
6. target XAMPP path yang dipakai sesuai mapping runbook ini

Jika salah satu poin di atas belum jelas, jangan mulai smoke test runtime nyata.

## 7. Inventory endpoint diagnostic dan readiness

Klasifikasi berikut hanya untuk keperluan operator/reviewer launch. Endpoint yang mengubah state tidak dianggap diagnostic production walaupun saat ini dibatasi admin.

### Aman untuk production admin/operator

1. `api_admin_setup.php?action=get_discord_config_status`
   - auth: admin level 10
   - kegunaan: bootstrap status config + Discord readiness
   - sifat: secret-safe
   - catatan: hanya mengembalikan presence/source/readiness, bukan nilai secret

2. `session.php` dengan sesi admin/operator yang valid
   - auth: sesi aktif
   - kegunaan: cek continuity session/auth minimum
   - sifat: bounded
   - catatan: hanya mengembalikan `username` dan `admin_level`, cukup untuk smoke auth tanpa dump session

3. `api_overview.php?action=assets&type=houses|businesses|families`
   - auth: admin level 5
   - kegunaan: bounded read-only asset smoke setelah login
   - sifat: aman untuk smoke operasional terbatas
   - catatan: jangan dipakai sebagai full health endpoint; ini validasi data read-only pasca-auth

4. `discord_check.php`
   - auth: sesi aktif atau pending session yang sesuai
   - kegunaan: cek apakah akun target sudah linked Discord
   - sifat: bounded
   - catatan: cukup untuk smoke flow auth/Discord, tidak mengekspos token

### Hanya local/dev

1. `test_email.php`
   - auth: admin level 10 via HTTP, atau CLI
   - local-only via HTTP
   - kegunaan: mail runtime diagnostic tanpa mengirim email
   - sifat: secret-safe, tetapi dibatasi local/CLI

2. `api_overview.php?action=server_info`
   - auth: tidak dibatasi admin di kode saat ini
   - kegunaan: cocok untuk local/dev check atau informasi publik terbatas
   - catatan: karena memuat `ip_address` server game, jangan jadikan production admin diagnostic baseline tanpa review tambahan

### Tidak boleh dipakai untuk production diagnostic baseline

1. `test_db_integration.php`
   - auth: admin level 10
   - alasan: mengekspos host/port/database dan sample counts yang terlalu detail untuk baseline production launch

2. `setup_database.php`
   - auth: admin level 10
   - alasan: menjalankan integration path yang mengubah state database; bukan diagnostic read-only

3. `migrate.php`
   - auth: admin level 10
   - alasan: memaksa migration/integration; tidak boleh menjadi bagian smoke validation launch

### Catatan secret-safe

- `api_admin_setup.php?action=get_discord_config_status` dan `test_email.php` saat ini sudah paling dekat dengan diagnostic production-grade karena berbasis readiness metadata.
- `session.php` aman untuk smoke auth minimum, tetapi bukan endpoint readiness administratif lengkap.
- Endpoint yang mengandung host game server, sample row count, atau trigger integrasi database harus diperlakukan di luar baseline production smoke.

## 8. Gap analysis sebelum launch

### Package gap

- Runbook package checklist sudah ada.
- Belum ada manifest release formal yang menyatakan versi package frontend/API/vendor untuk setiap release candidate.
- Belum ada keputusan apakah BOT deployment package akan didokumentasikan di dokumen terpisah atau satu family runbook terpisah.

### Env gap

- Kontrak local vs production untuk Website/UCP sudah terdokumentasi.
- Belum ada checklist readiness production yang dibagi per service:
  - Website/UCP frontend
  - Website PHP API
  - BOT
  - database
- Belum ada format evidence yang disepakati untuk membuktikan private `.env` siap tanpa membuka nilainya.

### Runtime layout gap

- Local Windows/XAMPP development sudah punya asumsi jelas.
- Production target sudah bergeser ke Linux VPS, sehingga mapping deploy final untuk production belum boleh lagi berasumsi XAMPP flattened layout.
- Perlu runbook tahap berikutnya untuk layout Linux VPS:
  - web root/frontend publish path
  - PHP runtime/service model
  - vendor path
  - private `.env` path
  - restart/reload procedure

### Diagnostic gap

- Diagnostic inventory sudah terpetakan.
- Belum ada satu endpoint production-grade khusus admin yang menggabungkan health bootstrap, auth smoke, dan bounded runtime checks dalam satu checklist operasional.
- `api_overview.php?action=server_info` masih ambigu untuk production baseline karena mengekspos alamat game server.

### Smoke validation gap

- Urutan smoke test terotorisasi belum disusun penuh untuk production VPS.
- Belum ada evidence template yang menentukan output mana yang cukup dicatat operator setelah deploy.
- Belum ada pemisahan formal antara:
  - smoke Website/UCP/API
  - smoke BOT
  - smoke database connectivity
  - smoke game server via Pterodactyl-managed runtime

### Rollback / sign-off gap

- Trigger rollback dan sign-off belum ditulis rinci.
- Belum ada definisi siapa yang berwenang memberi:
  - deploy go/no-go
  - rollback approval
  - final launch sign-off

### Linux VPS production gap

- Production target Linux VPS sudah diputuskan, tetapi runbook ini baru cukup untuk baseline package/env, belum untuk langkah operasi host.
- Belum ada keputusan formal mengenai:
  - process manager/service supervisor untuk PHP/BOT
  - web server/reverse proxy layout
  - log location dan rotation
  - backup/restore path untuk release rollback

### Pterodactyl / game-server management gap

- Pterodactyl Panel + Wings boleh dipakai untuk manajemen game server, tetapi bukan baseline deploy Website/UCP/API/BOT.
- Runbook saat ini harus menganggap game server checklist terpisah dari Website/UCP/API/BOT.
- Belum ada dokumen terpisah yang mendefinisikan boundary antara:
  - VPS production untuk website/api/bot/database
  - node/host game server yang dikelola Pterodactyl
  - dependency antar dua domain itu saat launch komunitas
