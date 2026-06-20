# WEBSITE/UCP Local Development Workflow

Dokumen ini menetapkan workflow local development PC untuk Website/UCP dengan boundary tegas antara repo utama dan runtime XAMPP lokal.

## 1. Boundary repo vs XAMPP

### Source of truth

- Repo utama tetap di `C:\Users\guyub\Documents\PAHLAWAN ROLEPLAY`
- Area kerja Website/UCP yang ditrack ada di `WEBSITE\`
- Semua perubahan source code dilakukan di repo, bukan di `htdocs`

### Target runtime lokal

- XAMPP hanya target runtime/deploy lokal:
  - `C:\xampp\htdocs\pahlawan_roleplay`
- Isi `htdocs` dianggap hasil sync/copy runtime dari repo
- Perubahan manual di `htdocs` dianggap drift lokal dan tidak menjadi source of truth

### Hasil audit boundary saat ini

Repo `WEBSITE` saat ini memuat:

- source frontend: `App.tsx`, `Auth.tsx`, `components\`, `services\`, `utils\`
- frontend build output: `dist\`
- runtime web root repo: `public\`
- PHP API repo: `public\api\`
- runtime uploads repo: `public\uploads\`
- test/helper lokal: `tests\`
- env examples: `.env.local.example`, `.env.production.example`, `env.example`

Target XAMPP saat ini memuat:

- runtime API: `api\`
- frontend static runtime: `assets\`, `index.html`
- runtime uploads/data lokal: `uploads\`, `music\`, `qrcode\`
- private runtime config: `.env`
- helper runtime lokal lama: `check_db.php`, `test_settings.php`

### Yang tidak boleh diedit langsung di XAMPP

- `C:\xampp\htdocs\pahlawan_roleplay\api\`
- `C:\xampp\htdocs\pahlawan_roleplay\assets\`
- `C:\xampp\htdocs\pahlawan_roleplay\index.html`
- file hasil build/sync lain yang berasal dari repo

Jika ada kebutuhan patch pada runtime XAMPP, perbaiki dulu di repo lalu sync ulang ke target runtime.

## 2. Workflow mode yang direkomendasikan

### Mode A: frontend development harian

Gunakan saat mengerjakan UI, routing, state, dan integrasi API frontend.

- jalankan dari `WEBSITE`:
  - `npm run dev`
- frontend dev server menjadi mode utama iterasi
- API tetap diarahkan ke PHP runtime lokal dari repo

Pakai mode ini ketika:

- sedang coding harian
- butuh HMR/refresh cepat
- belum perlu mensimulasikan output deploy

### Mode B: source-of-truth PHP/API testing

Gunakan saat memverifikasi endpoint PHP langsung dari source repo.

- jalankan dari root repo:
  - `php -S 127.0.0.1:8000 -t WEBSITE/public`

Pakai mode ini ketika:

- menguji behavior API dari source repo
- memeriksa auth/session/local preview
- ingin memastikan test tidak bergantung pada sync XAMPP

### Mode C: production-build validation lokal

Gunakan saat ingin memastikan hasil frontend build siap dipakai runtime flattened.

- jalankan dari `WEBSITE`:
  - `npm run build`

Pakai mode ini ketika:

- akan validasi output deploy-style
- akan sync/copy ke XAMPP
- perlu memastikan `dist\` terbaru sesuai source repo

### Mode D: XAMPP deployed-style validation

Gunakan hanya setelah build/sync siap.

- jalankan via XAMPP Apache
- target validasi:
  - layout flattened
  - static asset hasil build
  - API runtime hasil copy
  - local smoke pasca-sync

Pakai mode ini ketika:

- ingin membuktikan runtime lokal ala deploy
- ingin cek hasil copy ke `htdocs`
- perlu verifikasi boundary repo vs runtime target

## 3. Local `.env` handling

### Aturan umum

- `WEBSITE\.env` bersifat private dan tidak boleh di-commit
- tracked template hanya:
  - `WEBSITE\.env.local.example`
  - `WEBSITE\.env.production.example`
  - `WEBSITE\env.example`
- `C:\xampp\htdocs\pahlawan_roleplay\.env` juga private dan hanya untuk runtime lokal XAMPP

### Local repo development

Untuk dev harian:

- isi `WEBSITE\.env` dari template local
- gunakan:
  - `APP_ENV=local`
  - `VITE_API_BASE_URL=api`
  - `VITE_DEV_API_PROXY_TARGET=http://127.0.0.1:8000`

### Local preview

OTP preview lokal hanya boleh aktif bila keduanya benar:

- `APP_ENV=local`
- `UCP_LOCAL_MAIL_MODE=preview`

Mode ini dipakai hanya untuk:

- smoke auth/email lokal yang terotorisasi
- test helper lokal yang aman

### Production-like local smoke

Jika ingin simulasi non-preview lokal:

- tetap gunakan `APP_ENV=local` untuk local machine
- ganti `UCP_LOCAL_MAIL_MODE=smtp` hanya jika SMTP lokal memang siap dan terotorisasi
- jangan ubah tracked env example menjadi berisi secret nyata

## 4. Strategi sync/copy repo ke XAMPP

### Sync yang direkomendasikan

Saat validasi runtime XAMPP, sinkronkan hanya artifact yang memang menjadi runtime deploy:

| Repo source | Target XAMPP | Catatan |
| --- | --- | --- |
| `WEBSITE\dist\*` | `C:\xampp\htdocs\pahlawan_roleplay\` | frontend static hasil build |
| `WEBSITE\public\api\*` | `C:\xampp\htdocs\pahlawan_roleplay\api\` | PHP API source |
| `WEBSITE\public\uploads\.keep` dan struktur folder kosong yang ditrack | `C:\xampp\htdocs\pahlawan_roleplay\uploads\` | hanya placeholder/struktur, bukan data user |

### Jangan disync dari repo

- `WEBSITE\node_modules\`
- `WEBSITE\tests\`
- `WEBSITE\.runtime-logs\`
- `WEBSITE\.env`
- dump/log private apa pun
- OTP/cookie/session/token/credential apa pun

### Jangan dihapus/ditimpa sembarang di XAMPP

- `C:\xampp\htdocs\pahlawan_roleplay\.env`
- `C:\xampp\htdocs\pahlawan_roleplay\uploads\` berisi data runtime lokal
- folder runtime lokal lain seperti `music\` dan `qrcode\` kecuali memang ada prosedur reset yang disengaja

### Catatan readiness dependency

- `WEBSITE\vendor\` saat ini belum tersedia di repo
- `C:\xampp\htdocs\pahlawan_roleplay\vendor\` juga belum tersedia
- target XAMPP masih punya fallback legacy `api\PHPMailer\src`

Implikasinya:

- workflow lokal saat ini aman untuk preview/local API smoke tanpa mengandalkan Composer vendor
- validasi runtime XAMPP yang membutuhkan Composer mailer belum boleh mengasumsikan `vendor\autoload.php` tersedia
- sinkronisasi awal tidak membuat atau memaksa vendor baru; itu tetap keputusan dependency/runtime terpisah

## 5. Reset / rollback runtime XAMPP lokal

Gunakan prosedur aman berikut jika runtime XAMPP stale atau rusak:

1. hentikan Apache/XAMPP atau pastikan tidak ada request aktif yang sedang diuji
2. jangan sentuh repo utama
3. backup lokal seperlunya untuk data runtime yang ingin dipertahankan:
   - `.env`
   - `uploads\`
   - `music\`
   - `qrcode\`
4. hapus atau timpa hanya artifact hasil sync yang berasal dari repo:
   - `assets\`
   - `index.html`
   - file di `api\` yang memang berasal dari repo
5. rebuild frontend dengan `npm run build` bila perlu
6. copy ulang artifact repo yang valid ke XAMPP
7. restore kembali private `.env` dan data runtime lokal yang memang harus dipertahankan

Prinsip reset:

- reset XAMPP tidak boleh mengubah repo
- reset XAMPP tidak boleh menghapus secret/private config tanpa backup sadar
- reset XAMPP tidak boleh dianggap pengganti perbaikan source repo

## 6. Minimum post-sync checks

Setelah sync/copy ke XAMPP, lakukan check minimum berikut:

1. `index.html` target berasal dari build terbaru
2. folder `assets\` target terisi
3. folder `api\` target tersedia dan endpoint dasar bisa diakses
4. private `.env` target tetap ada
5. smoke terbatas sesuai mode:
   - login/session minimum bila diperlukan
   - endpoint diagnostic aman yang memang diizinkan
   - tidak ada kebutuhan membuka secret/OTP/provider error

## 7. Kapan memakai mode tertentu

### Pakai `npm run dev`

- default frontend harian
- saat belum butuh build deploy-style

### Pakai `npm run build`

- sebelum sync ke XAMPP
- saat mau validasi hasil production build lokal

### Pakai PHP built-in server

- default untuk test API source repo
- default untuk smoke lokal yang harus mengikuti source of truth

### Pakai XAMPP Apache

- hanya untuk validasi deployed-style setelah copy/sync
- bukan tempat coding utama

