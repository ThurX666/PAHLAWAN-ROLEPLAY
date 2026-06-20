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
