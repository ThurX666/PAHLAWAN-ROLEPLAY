# Tasks — cross-service-auth-flow

**Target:** Alpha Test 1 Agustus 2026 — semua service berbagi database yang sama di **localhost**.

**Mode:** Localhost (XAMPP MySQL + PHP + SA-MP server + Node.js bot).

---

## 1. Database Schema Audit & Migration

- [x] **1.1** — Audit schema existing: 103 tabel ditemukan, database `arivena` MariaDB 10.4.32.
- [x] **1.2** — `player_ucp` confirmed sebagai single source of truth. Dipakai UCP (PHP) & Gamemode (Pawn). 26 kolom, charset latin1, PK=`ID`, username di `UCP`. Password bcrypt $2y$12$.
- [x] **1.3** — `player_characters` confirmed. 100+ kolom game data, link via `Char_UCP` (username string, bukan FK). Tabel `characters` (simple, 7 kolom) dan `ucp` (simple, 9 kolom) **orfan — nol referensi kode, nol data, nol FK**. Bisa di-drop.
- [ ] **1.4** — Buat migration script jika schema perlu diselaraskan (tambah kolom, ubah tipe, dll).
- [ ] **1.5** — Pastikan `player_ucp` punya: id, username (UNIQUE), password (bcrypt hash), email, verified, otp_code, otp_expiry, discord_id, admin_level, last_login, created_at.
- [ ] **1.6** — Pastikan `player_characters` punya: id, ucp_id (FK → player_ucp.id), char_name (UNIQUE), skin, age, origin, gender, created_at.
- [ ] **1.7** — Verifikasi: query cross-table JOIN `player_ucp` ↔ `player_characters` berhasil.
- [ ] **1.8** — Backup database existing sebelum migration.

---

## 2. UCP — Unifikasi ke Shared Database

- [x] **2.1** — Audit `auth.php`: cek action login, register, verify, forgot_password, discord_link — pastikan semuanya query ke tabel `player_ucp`.
  - `auth.php` (login): SELECT dari `player_ucp` WHERE UCP/Email, `password_verify()`, cek `Verify_Status`, cek `discord_id`. ✅
  - `register.php`: `password_hash(PASSWORD_BCRYPT, cost=12)`, INSERT ke `player_ucp` (UCP, Email, Password, Verify_Status=0, Verify_Code). ✅
  - `verify.php`: SELECT dari `player_ucp`, UPDATE `Verify_Status=1` + `Verify_Code=-1` setelah OTP match. ✅
  - `forgot.php`: SELECT `reset_token`/`reset_expires`, UPDATE password baru dengan `password_hash(PASSWORD_BCRYPT)`. ✅
  - Discord link: cek `discord_id` di `auth.php` login flow → redirect ke discord link. ✅
- [x] **2.2** — Hapus/deprecate dummy/preview mode di `Auth.tsx` — ganti jadi selalu fetch ke `auth.php` (live DB).
  - `WEBSITE/Auth.tsx`: branch `isPreviewEnv()` (admin/player hardcoded) dihapus, import `isPreviewEnv` dihapus. ✅
  - `WEBSITE/components/Auth.tsx`: branch `isPreviewEnv()` dihapus, import `isPreviewEnv` dihapus. ✅
  - `localAuthPreview` (QA mode dengan server preview) tetap dipertahankan — bukan dummy mode.
  - `config.ts`: `isPreviewEnv()` tetap ada karena masih dipakai `App.tsx` untuk server stats & fetch guard.
- [x] **2.3** — Pastikan `auth.php` action=register menyimpan password dengan `password_hash($password, PASSWORD_BCRYPT)`. **Done — verified in `register.php` line 22: cost=12.**
- [x] **2.4** — Pastikan `auth.php` action=login menggunakan `password_verify()`. **Done — verified in `auth.php` line 43.**
- [x] **2.5** — Pastikan OTP verify flow: generate code → simpan ke `player_ucp.otp_code` + `otp_expiry` → kirim email via PHPMailer.
  - OTP generate: `mt_rand(1, 999999)` 6-digit. Simpan ke `player_ucp.Verify_Code` (int). ✅
  - Expiry: pakai `Register_Date` + 30 menit (varchar → strtotime). Di-reset ke CURRENT_TIMESTAMP tiap resend OTP. ✅
  - Email: `sendVerificationEmail()` via PHPMailer SMTP (`mailer_helper.php`). Support multi-context (register, resend, new_device, new_ip, reauth). ✅
  - Cooldown: 1800 detik via `Register_Date` timestamp check. ✅
  - Max attempts: 3 `OTP_Attempts` sebelum blocked. ✅
  - ⚠️ `Register_Date` masih varchar(30), bukan DATETIME. `otp_expiry` kolom belum ada — migrasi ada di task 1.5.
- [ ] **2.6** — Pastikan Discord link flow: setelah register/verify, user bisa link Discord account → simpan `discord_id`.
- [ ] **2.7** — Verifikasi: register akun baru lewat UCP → data muncul di `player_ucp` table.
- [ ] **2.8** — Verifikasi: login dengan akun yang baru dibuat → sukses → session aktif.
- [ ] **2.9** — Audit sistem Inbox UCP: cek tabel `ucp_inbox_messages`, pastikan query dan relasi user (username vs ucp_id) mengarah ke `player_ucp` dengan benar.
- [ ] **2.10** — Audit sistem Create Character: cek `api_characters.php` + `CreateCharacterModal.tsx`, pastikan pembuatan karakter terhubung ke akun `player_ucp` (via `Char_UCP` atau `ucp_id`).
- [ ] **2.11** — Audit kolom `admin`: pastikan nama kolom (`admin_level` di `player_ucp` vs `Char_Admin` di `player_characters`), tipe data, dan usage-nya selaras di WEBSITE (PHP), BOT (Node.js), dan GAMEMODE (Pawn).
- [ ] **2.12** — Hapus `isPreviewEnv()` dari `App.tsx`: 10+ pemakaian untuk `MOCK_STATS`, fetch guards, dan login event simulation. Ganti dengan live fetch/data saja. Hapus `isPreviewEnv` import. Setelah semua usage hilang, hapus `isPreviewEnv()` dari `config.ts`. (Ditunda dari task 2.2 karena scope App.tsx di luar Auth.tsx.)

---

## 3. UCP — Character Creation Pipeline

- [ ] **3.1** — Audit `CreateCharacterModal.tsx`: cek form fields, validasi, dan submit handler.
- [ ] **3.2** — Buat API endpoint baru: `WEBSITE/public/api/character.php` — handle POST create character.
- [ ] **3.3** — Endpoint `character.php`: validasi session (user harus login), validasi input (nama 3-20 chars, alphanumeric), cek max 3 karakter.
- [ ] **3.4** — Endpoint `character.php`: INSERT ke `player_characters` dengan `ucp_id` dari session user.
- [ ] **3.5** — Hubungkan `CreateCharacterModal` submit ke `fetch('api/character.php')`.
- [ ] **3.6** — Verifikasi: login UCP → buka CreateCharacter → isi form → submit → data muncul di `player_characters`.
- [ ] **3.7** — Verifikasi: coba buat karakter ke-4 → ditolak (max 3).
- [ ] **3.8** — Verifikasi: coba buat karakter dengan nama yang sama → ditolak (UNIQUE constraint).

---

## 4. SA-MP Gamemode — Login dengan Shared DB

- [ ] **4.1** — Audit `account_regist.inc`: pahami flow `CheckPlayerUCP()`, `OnLoginPassCheck()`, `OnPlayerPasswordChecked()`.
- [ ] **4.2** — Pastikan query login di gamemode membaca tabel `player_ucp` (bukan tabel terpisah).
- [ ] **4.3** — Pastikan password verification di Pawn menggunakan bcrypt plugin yang kompatibel dengan PHP `PASSWORD_BCRYPT`.
- [ ] **4.4** — Test hash compatibility: hash password di PHP → coba verify di Pawn bcrypt.
- [ ] **4.5** — Refactor login dialog untuk menggunakan kolom yang sama dengan UCP (username, password).
- [ ] **4.6** — Tambahkan pengecekan `verified = 1` sebelum player bisa login in-game.
- [ ] **4.7** — Tambahkan pesan error yang jelas: "Akun belum diverifikasi. Cek email Anda." jika verified = 0.
- [ ] **4.8** — Verifikasi: register di UCP → verify OTP → login in-game dengan username + password yang sama → sukses masuk ke character selection.

---

## 5. SA-MP Gamemode — Character Selection dari UCP

- [ ] **5.1** — Audit `InsertPlayerName()` di `account_regist.inc`: bagaimana karakter dibuat dari in-game.
- [ ] **5.2** — Modifikasi character selection flow: setelah login sukses, load karakter dari `player_characters` WHERE `ucp_id` = user's ID.
- [ ] **5.3** — Tampilkan daftar karakter yang sudah dibuat di UCP dalam dialog selection in-game.
- [ ] **5.4** — Jika user belum punya karakter, arahkan ke character creation in-game (fallback) atau suruh buat di UCP dulu.
- [ ] **5.5** — Verifikasi: buat karakter di UCP → login in-game → karakter muncul di selection → bisa spawn.

---

## 6. Discord Bot — Basic Cross-Service Connection

- [ ] **6.1** — Pastikan `BOT/config.json` punya konfigurasi koneksi ke shared MySQL database (host: localhost).
- [ ] **6.2** — Verifikasi bot bisa start dan connect ke database (cek `clientReady.js`).
- [ ] **6.3** — Buat slash command `/info [username]` — query `player_ucp` + `player_characters` dan tampilkan info user.
- [ ] **6.4** — Pastikan bot hanya read-only ke database (tidak ada insert/update/delete dari bot).
- [ ] **6.5** — Verifikasi: bot online → `/info <username>` → tampilkan data user + karakter.

---

## 7. Localhost Integration Testing

- [ ] **7.1** — Setup XAMPP: pastikan MySQL dan Apache jalan.
- [ ] **7.2** — Setup database: import schema atau pastikan database existing bisa diakses.
- [ ] **7.3** — Setup SA-MP server: pastikan server bisa connect ke MySQL localhost.
- [ ] **7.4** — Setup UCP: jalankan `npm run dev` untuk Vite, pastikan fetch ke `auth.php` jalan.
- [ ] **7.5** — Setup bot: jalankan `node index.js` (atau `npm start`), pastikan bot connect ke Discord + MySQL.
- [ ] **7.6** — Full flow test: Register UCP → Verify OTP → Login UCP → Create Character → Login SA-MP → Pilih Karakter → Spawn.
- [ ] **7.7** — Edge case test: unverified account login in-game, wrong password, duplicate character name, max characters.
- [ ] **7.8** — Bot test: `/info` command dengan username yang baru dibuat.

---

## 8. Documentation

- [ ] **8.1** — Update `docs/LOCALHOST_DEV_SETUP.md` dengan langkah-langkah setup cross-service auth.
- [ ] **8.2** — Dokumentasikan schema database final (ERD atau tabel markdown).
- [ ] **8.3** — Dokumentasikan API endpoints: `auth.php`, `character.php`.
- [ ] **8.4** — Update ROADMAP.md: centang Pre-Alpha items yang selesai.

---

**Total: 58 tasks** (1.x: 8, 2.x: 12, 3.x: 8, 4.x: 8, 5.x: 5, 6.x: 5, 7.x: 8, 8.x: 4)
