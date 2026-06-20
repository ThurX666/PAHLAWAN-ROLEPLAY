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

## 9. Ordered authorized smoke validation runbook

Bagian ini berlaku untuk baseline Website/UCP/API. BOT, database operation yang mengubah state, dan game server/Pterodactyl tetap di checklist terpisah.

### 9.1 Local/dev smoke

Boleh untuk development:

1. pastikan local runtime memakai repo source
2. cek `session.php` setelah login lokal
3. cek `test_email.php` hanya di local/CLI
4. cek bounded asset endpoint admin setelah auth
5. gunakan helper local preview hanya jika `APP_ENV=local` dan `UCP_LOCAL_MAIL_MODE=preview`

Tidak boleh dipakai sebagai bukti launch production.

### 9.2 Production admin/operator smoke

Urutan minimum pasca-deploy:

1. **Pre-deploy hold point**
   - release package sudah final
   - package checklist bagian 3 sudah lolos
   - private `.env` target sudah disiapkan
   - operator yang berwenang sudah ditentukan

2. **Package checks**
   - frontend publish artifact tersedia
   - `api/` runtime tersedia
   - `vendor/autoload.php` tersedia
   - artifact private tidak ikut package tracked

3. **Env readiness checks**
   - private `.env` berada di runtime root yang benar
   - env example tidak dipakai sebagai live secret file
   - mode runtime sesuai production contract
   - diagnostic readiness yang aman dapat diakses oleh admin/operator terotorisasi

4. **Post-deploy API/bootstrap checks**
   - akses `api_admin_setup.php?action=get_discord_config_status` sebagai admin 10
   - catat hanya `status`, readiness, bootstrap status, dan source/path metadata yang aman
   - jangan menyalin nilai secret

5. **Auth/session smoke**
   - login dengan akun uji terotorisasi
   - cek `session.php`
   - refresh/navigasi satu kali untuk memastikan continuity minimum

6. **Bounded feature smoke**
   - cek `discord_check.php` bila flow Discord memang bagian dari launch path
   - cek `api_overview.php?action=assets&type=houses`
   - cek `api_overview.php?action=assets&type=businesses`
   - cek `api_overview.php?action=assets&type=families`

7. **Mail/runtime readiness smoke**
   - untuk production gunakan readiness metadata dan hasil flow terotorisasi
   - jangan gunakan `test_email.php` sebagai endpoint HTTP production
   - jangan catat OTP, credential, provider error, atau payload sensitif

8. **Operator decision point**
   - tandai pass/fail per langkah
   - jika ada critical fail, hentikan launch progression

### 9.3 Tidak boleh dipakai untuk production smoke

- `test_email.php` via HTTP production
- `test_db_integration.php`
- `setup_database.php`
- `migrate.php`
- local preview helper/output OTP
- endpoint atau output yang membuka host game server, database detail, provider error, atau nilai env sensitif

## 10. Operator inputs, preconditions, dan evidence format

### Inputs minimum

- release identifier atau build label
- target environment: `local-dev` atau `production`
- target runtime host/path
- operator username
- akun uji terotorisasi untuk smoke auth/session
- keputusan package vendor: packaged-from-repo

### Preconditions minimum

- release package sudah dibekukan untuk sesi deploy
- private `.env` target sudah disiapkan di luar repo
- akses admin/operator ke UCP tersedia
- jalur rollback kandidat release sebelumnya sudah diketahui
- tidak ada migration/schema step yang ikut sesi ini

### Evidence format

Catat evidence hanya dalam format ringkas berikut:

| Field | Isi |
| --- | --- |
| release_id | label release/build |
| environment | local-dev / production |
| operator | username operator |
| runtime_target | host/path runtime |
| check_name | nama langkah smoke |
| result | pass / fail / blocked |
| timestamp | waktu UTC atau WIB yang konsisten |
| safe_notes | metadata aman tanpa secret |

Contoh `safe_notes` yang boleh:

- `bootstrap_status=ready`
- `mail_loader=composer`
- `session_check=pass`
- `assets_houses=status_success`

Contoh yang tidak boleh:

- isi `.env`
- OTP
- cookie/session id
- SMTP host/user/pass detail
- provider error body

## 11. Failure classification dan escalation

### 11.1 Failure classification

| Kategori | Contoh sinyal | Default action |
| --- | --- | --- |
| package failure | artifact `dist`/`api`/`vendor` tidak lengkap | stop deploy, rebuild package |
| env/config failure | bootstrap/env readiness tidak sesuai contract | hold launch, fix env, recheck |
| frontend build/static failure | frontend publish path gagal load | stop launch, redeploy frontend artifact |
| API/runtime failure | endpoint bootstrap/admin smoke tidak reachable/invalid | hold launch, inspect runtime, retry terbatas |
| auth/session failure | login/session continuity gagal | hold launch, jangan buka public access |
| mail/SMTP failure | readiness mail gagal atau flow mail fail closed | hold launch bila flow launch bergantung email |
| DB connectivity failure | API tidak bisa reach DB atau bootstrap status error | stop launch, inspect DB/runtime connectivity |

### 11.2 Escalation path

1. **Retry**
   - hanya untuk failure yang jelas transient
   - maksimal satu retry terotorisasi setelah penyebab awal diidentifikasi

2. **Hold launch**
   - dipakai jika failure belum jelas, berdampak auth/runtime, atau butuh koreksi env/package
   - public launch tidak boleh dilanjutkan

3. **Rollback**
   - dipakai jika runtime production sudah berubah dan smoke critical gagal
   - kembali ke release tervalidasi sebelumnya

4. **Owner sign-off**
   - wajib untuk membuka launch kembali setelah hold/rollback
   - wajib juga bila operator ingin menerima risk yang tidak termasuk standard pass criteria

### 11.3 Stop conditions

Langsung hentikan progression launch bila terjadi salah satu:

- package incomplete
- bootstrap readiness error
- auth/session smoke fail
- DB connectivity fail
- mail readiness fail pada flow yang wajib aktif saat launch

## 12. Future change candidate

Change berikutnya yang direkomendasikan setelah runbook ini matang:

- `vps-linux-pterodactyl-production-bootstrap`

Scope future change:

- initial Linux VPS hardening
- SSH user dan firewall baseline
- Nginx / PHP-FPM / MariaDB / Node runtime setup
- Pterodactyl Panel + Wings untuk domain game server
- UCP deploy path di VPS production
- BOT service management
- backup / restore baseline

Catatan:

- change future ini tidak diimplementasikan sekarang
- Pterodactyl tetap diperlakukan terpisah dari baseline Website/UCP/API/BOT launch checklist saat ini

## 13. VPS purchase dan operator decision notes

Keputusan operasional saat ini:

- provider VPS production yang direncanakan: VibeGAMES Singapore
- nama server yang direkomendasikan: `pahlawan-prod-sg01`
- OS baseline yang direkomendasikan:
  - utama: Ubuntu 24.04 LTS
  - fallback: Ubuntu 22.04 LTS
- Windows tidak direkomendasikan untuk production Pterodactyl/Wings
- image Pterodactyl preinstall tidak diprioritaskan; baseline yang diinginkan adalah Ubuntu clean agar kontrol bootstrap penuh tetap ada
- metode login yang direkomendasikan:
  - utama: SSH key
  - fallback awal: password sementara sampai SSH key siap

Catatan boundary:

- VPS production adalah target runtime production, bukan tempat utama coding
- release package launch awal tetap dibuat dari PC repo utama
- Website/UCP/API/BOT/database tetap punya checklist deployment tersendiri
- game server yang nanti dikelola Pterodactyl tetap dipisahkan dari baseline runbook Website/UCP/API/BOT

## 14. Rollback triggers

Rollback wajib dipertimbangkan segera jika salah satu kondisi berikut terjadi setelah deploy atau saat smoke validation:

1. **Package incomplete**
   - artifact `dist`, `api`, `vendor`, `composer.json`, atau `composer.lock` tidak sesuai package checklist

2. **Env / bootstrap failure**
   - readiness config tidak sesuai production contract
   - private `.env` salah path atau runtime bootstrap tidak ready

3. **Frontend static failure**
   - frontend publish path gagal load
   - asset static utama tidak tersedia

4. **API / runtime failure**
   - endpoint bootstrap/admin smoke tidak reachable
   - runtime API merespons invalid untuk check baseline

5. **Auth / session failure**
   - login akun uji terotorisasi gagal
   - `session.php` tidak lolos continuity minimum

6. **DB connectivity failure**
   - API tidak bisa reach database
   - bootstrap/health menunjukkan failure yang memblokir runtime utama

7. **Mail readiness failure**
   - readiness mail gagal pada flow yang wajib aktif untuk launch
   - email-backed auth path fail closed pada jalur yang dibutuhkan saat launch

Jika salah satu kategori di atas terjadi dan tidak dapat dibenahi melalui satu retry terotorisasi, launch harus di-hold atau rollback.

## 15. Rollback verification checklist

Setelah rollback dilakukan, operator harus memverifikasi minimal:

1. previous release package berhasil dipulihkan
2. private `.env` target tetap preserved dan tidak tertimpa env example
3. runtime target mengarah ke release sebelumnya yang tervalidasi
4. auth/session smoke minimum lolos:
   - login akun uji terotorisasi
   - `session.php` pass
5. bounded asset smoke lolos:
   - `api_overview.php?action=assets&type=houses`
   - `api_overview.php?action=assets&type=businesses`
   - `api_overview.php?action=assets&type=families`
6. operator evidence rollback tercatat dalam format aman

Rollback tidak dianggap selesai hanya karena file lama sudah dikembalikan; smoke minimum pasca-rollback wajib lolos.

## 16. Final launch readiness checklist

Sebelum launch komunitas dibuka, checklist minimum berikut harus `pass`:

- VPS OS sudah dipilih:
  - Ubuntu 24.04 LTS, atau
  - fallback Ubuntu 22.04 LTS
- metode login admin host sudah dipilih:
  - SSH key preferred, atau
  - password sementara yang akan diganti/harden kemudian
- release package sudah final dan sesuai checklist
- private `.env` production sudah siap di target runtime yang benar
- akun admin/operator terotorisasi untuk smoke sudah siap
- rollback package / previous release candidate sudah siap
- smoke evidence sudah lengkap dan aman
- tidak ada critical blocker pada package, env, frontend, API, auth/session, DB, atau mail readiness

Jika salah satu butir di atas belum `pass`, launch harus tetap `hold`.

## 17. Sign-off criteria

Launch readiness dianggap lengkap hanya jika semua kriteria berikut terpenuhi:

1. **Owner sign-off**
   - owner/release authority menyetujui hasil smoke dan status risiko

2. **Operator sign-off**
   - operator deploy menyatakan package, env, dan bounded smoke sudah diverifikasi

3. **No secret exposure**
   - evidence dan catatan operasional tidak memuat `.env`, credential, token, session, cookie, OTP, SMTP detail, provider error, atau password VPS

4. **No critical blocker**
   - tidak ada blocker kritis pada package, runtime, auth/session, DB, frontend, atau mail readiness

5. **Rollback ready**
   - jalur rollback dan candidate previous release siap digunakan bila launch ditunda atau rollback diperlukan

Tanpa owner sign-off dan operator sign-off yang jelas, release tidak boleh dinyatakan launch-ready.
