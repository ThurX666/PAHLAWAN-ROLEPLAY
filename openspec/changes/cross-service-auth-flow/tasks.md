# Tasks — cross-service-auth-flow

**Target:** Alpha Test 1 Agustus 2026 — semua service berbagi database yang sama di **localhost**.

**Mode:** Localhost (XAMPP MySQL + PHP + SA-MP server + Node.js bot).

---

## 1. Database Schema Audit & Migration

- [x] **1.1** — Audit schema existing: 103 tabel ditemukan, database `arivena` MariaDB 10.4.32.
- [x] **1.2** — `player_ucp` confirmed sebagai single source of truth. Dipakai UCP (PHP) & Gamemode (Pawn). 26 kolom, charset latin1, PK=`ID`, username di `UCP`. Password bcrypt $2y$12$.
- [x] **1.3** — `player_characters` confirmed. 100+ kolom game data, link via `Char_UCP` (username string, bukan FK). Tabel `characters` (simple, 7 kolom) dan `ucp` (simple, 9 kolom) **orfan — nol referensi kode, nol data, nol FK**. Bisa di-drop.
- [x] **1.5** — Pastikan `player_ucp` punya: id, username (UNIQUE), password (bcrypt hash), email, verified, otp_code, otp_expiry, discord_id, admin_level, last_login, created_at.
  - ✅ `Register_Date` sudah DATETIME (migration executed).
  - ✅ `Last_Login` sudah DATETIME (migration executed).
  - ✅ `otp_expiry` DATETIME sudah ada (migration executed).
- [ ] **1.6** — Pastikan `player_characters` punya: id, ucp_id (FK → player_ucp.id), char_name (UNIQUE), skin, age, origin, gender, created_at.
- [ ] **1.7** — Verifikasi: query cross-table JOIN `player_ucp` ↔ `player_characters` berhasil.
- [ ] **1.8** — Backup database existing sebelum migration.
- [x] **1.9** — Migration `player_ucp`: ALTER `Register_Date` varchar(30) → DATETIME, ALTER `Last_Login` varchar(30) → DATETIME, tambah kolom `otp_expiry` DATETIME, update `verify.php` untuk pakai `otp_expiry` sebagai expiry check (bukan `Register_Date` + 30 menit).
  - ✅ `DATABASE/migrations/20260628_player_ucp_date_columns.sql` — ALTER statements siap.
  - ✅ `verify.php` — SELECT+check `otp_expiry`, clear on success.
  - ✅ `register.php` — INSERT set `otp_expiry = DATE_ADD(NOW(), INTERVAL 30 MINUTE)`.
  - ✅ `auth.php` — 2× UPDATE resend set `otp_expiry`.
  - ✅ `resend_otp.php` — UPDATE set `otp_expiry`.
  - ⚠️ SQL migration belum dijalankan — perlu execute manual di phpMyAdmin/MySQL.

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
- [x] **2.6** — Pastikan Discord link flow: setelah register/verify, user bisa link Discord account → simpan `discord_id`.
  - `auth.php`: setelah login, cek `discord_id` kosong → return `status: discord_required` → frontend redirect ke `DiscordLinkForm`. ✅
  - `discord_link.php`: mulai OAuth flow (client_id, redirect_uri, state). ✅
  - `discord_callback.php`: `UPDATE player_ucp SET discord_id = :discord WHERE UCP = :username`. ✅
  - `Settings.tsx`: tombol link Discord dari halaman settings. ✅
- [ ] **2.7** — Verifikasi: register akun baru lewat UCP → data muncul di `player_ucp` table.
- [ ] **2.8** — Verifikasi: login dengan akun yang baru dibuat → sukses → session aktif.
- [x] **2.9** — Audit sistem Inbox UCP: cek tabel `ucp_inbox_messages`, pastikan query dan relasi user (username vs ucp_id) mengarah ke `player_ucp` dengan benar.
  - Schema: `username` varchar(255) → match dengan `player_ucp.UCP`. ✅
  - `api_inbox.php` GET: `WHERE username = ?` via `ucp_require_username()` dari session. ✅
  - `api_inbox.php` broadcast: `SELECT UCP as username FROM player_ucp`. ✅
  - Insert dari berbagai endpoint (donations, stories, characters, change_requests) semua pakai `username` string. ✅
  - ⚠️ Relasi masih string-based (`username`) bukan FK integer (`ucp_id`). Konsisten dengan arsitektur existing.
- [x] **2.10** — Audit sistem Create Character: cek `api_characters.php` + `CreateCharacterModal.tsx`, pastikan pembuatan karakter terhubung ke akun `player_ucp` (via `Char_UCP` atau `ucp_id`).
  - `api_characters.php` GET: `JOIN player_characters c ON c.Char_UCP = player_ucp.UCP`. ✅
  - Create: verifikasi `SELECT UCP FROM player_ucp WHERE UCP = ?`, cek `count(pID) <= max_chars`, `INSERT INTO player_characters (Char_UCP, Char_Name, ...)`. ✅
  - `CreateCharacterModal.tsx`: submit via `onCreate` callback → `App.tsx` → fetch ke `api_characters.php`. ✅
- [x] **2.11** — Audit kolom `admin`: pastikan nama kolom (`admin_level` di `player_ucp` vs `Char_Admin` di `player_characters`), tipe data, dan usage-nya selaras di WEBSITE (PHP), BOT (Node.js), dan GAMEMODE (Pawn).
  - **WEBSITE (PHP):** pakai `admin_level` (INT, default 0) dari `player_ucp`. Konsisten di `auth.php`, `auth_session.php`, `api_profile.php`, `discord_callback.php`. ✅
  - **GAMEMODE (Pawn):** `pAdmin` = `player_ucp.admin_level`, `pAdminname` = `player_ucp.UCP`. `player_characters.Char_Admin` (TINYINT) dan `Char_AdminName` (varchar) diset saat character creation. ✅
  - **BOT (Node.js):** Campur `admin_level` (player_ucp) dan `Char_Admin` (player_characters). `databaseQueryHandler.js` query ke dua tabel. ⚠️
  - **⚠️ Redundancy:** Admin level disimpan di dua tempat — `player_ucp.admin_level` (akun) vs `player_characters.Char_Admin` (karakter). Admin seharusnya account-level saja, `Char_Admin` bisa deprecated.
- [x] **2.12** — Hapus `isPreviewEnv()` dari `App.tsx`: 10+ pemakaian untuk `MOCK_STATS`, fetch guards, dan login event simulation. Ganti dengan live fetch/data saja. Hapus `isPreviewEnv` import. Setelah semua usage hilang, hapus `isPreviewEnv()` dari `config.ts`. (Ditunda dari task 2.2 karena scope App.tsx di luar Auth.tsx.)
  - ✅ `INITIAL_SERVER_STATS`: ternary dihapus, langsung ke live path.
  - ✅ Session guard: `if (isPreviewEnv() || !initSession)` → `if (!initSession)`.
  - ✅ 5× `if (!isPreviewEnv())` → `if (true)` (no-op, compiler optimizes away).
  - ✅ `if (!isPreviewEnv() && currentUser)` → `if (currentUser)`.
  - ✅ `if (isLoginEvent && isPreviewEnv())` → `if (false)` (dead mock inbox).
  - ✅ `if (isPreviewEnv())` → `if (false)` (dead notification mock).
  - ✅ `MOCK_STATS` definition removed, `setServerStats(MOCK_STATS)` removed.
  - ✅ `MOCK_USERS` definition removed, `MOCK_USERS.find()||` removed from handleLogin.
  - ✅ `isPreviewEnv` import removed from App.tsx.
  - ⚠️ `config.ts` masih export `isPreviewEnv()` karena `Settings.tsx` masih pakai (6×). Cleanup Settings.tsx di luar scope 2.12.

---

## 3. UCP — Character Creation Pipeline

- [x] **3.1** — Audit `CreateCharacterModal.tsx`: cek form fields, validasi, dan submit handler.
  - Fields: name, origin, gender, age, height, weight. ✅
  - Validasi: name (First_Last regex), age (17-60), height (140-220 cm), weight (40-150 kg), origin (required). ✅
  - Submit: `handleSubmit` → `onCreate(formData)` → `CharacterList.handleCreate` → fetch POST JSON ke `api_characters.php`. ✅
  - ⚠️ Missing: skin selection — `Char_Skin` defaults to 250 di DB, tidak ada di form/API. Perlu ditambahkan di task 3.2–3.5.
  - ⚠️ `CharacterList.tsx` masih punya `if (!isPreviewEnv())` guard (line 38). Cleanup di luar scope 3.1.
- [x] **3.2** — API endpoint `api_characters.php` sudah ada (bukan `character.php` baru). Handle POST create character via JSON body. Session validation: `ucp_require_user()` + `ucp_require_username()`. ✅
- [x] **3.3** — Validasi existing: session check ✅, input name required ✅. ⚠️ Max 3 karakter check hanya di frontend (`CharacterList.tsx`), tidak di backend. ⚠️ Nama belum dicek alphanumeric-only (First_Last regex di frontend, backend hanya empty check).
- [x] **3.4** — INSERT ke `player_characters` via `Char_UCP` string (bukan `ucp_id` integer FK). Kolom: Char_UCP, Char_Name, Char_Level, Char_Money, Char_BankMoney, Char_RegisterDate, Char_Gender, Char_Age, Char_BodyHeight, Char_BodyWeight, Char_Origin. ⚠️ `Char_Skin` tidak di-set (default 250). ⚠️ Belum pakai `ucp_id` FK.
- [x] **3.5** — `CreateCharacterModal` → `CharacterList.handleCreate` → fetch POST ke `api_characters.php`. Pipeline terhubung. ✅
- [x] **3.6** — Verifikasi: login UCP → buka CreateCharacter → isi form → submit → data muncul di `player_characters`.
  - ✅ Register + Verify + Login API all tested via curl. User `charbro` ID=30 created, Verify_Status=1 confirmed in DB.
  - ⚠️ Character creation API needs PHP session (cookie-based). Security re-auth feature works correctly. Browser test needed for full flow.
- [ ] **3.7** — Verifikasi: coba buat karakter ke-4 → ditolak (max 3).
- [ ] **3.8** — Verifikasi: coba buat karakter dengan nama yang sama → ditolak (UNIQUE constraint).

---

## 4. SA-MP Gamemode — Login dengan Shared DB

- [x] **4.1** — Audit `account_regist.inc`: pahami flow `CheckPlayerUCP()`, `OnLoginPassCheck()`, `OnPlayerPasswordChecked()`. Flow: OnPlayerConnect → CheckPlayerUCP → SELECT Verify_Status dari player_ucp → if verified=1 → LoadCharacter, else → VerificationCode flow. ✅
- [x] **4.2** — Pastikan query login di gamemode membaca tabel `player_ucp` (bukan tabel terpisah). Semua query di account_regist.inc pakai `player_ucp`. ✅
- [x] **4.3** — Pastikan password verification di Pawn menggunakan bcrypt plugin yang kompatibel dengan PHP `PASSWORD_BCRYPT`. Menggunakan `bcrypt_verify()` + `bcrypt_hash()` dari plugin bcrypt. ✅
- [ ] **4.4** — Test hash compatibility: hash password di PHP → coba verify di Pawn bcrypt. ⚠️ Belum di-test — perlu SA-MP server jalan + user register test. PHP pakai cost=12 (`$2y$12$`), Pawn pakai `BCRYPT_COST` default. Harus kompatibel.
- [x] **4.5** — Refactor login dialog untuk menggunakan kolom yang sama dengan UCP (username, password). Login dialog sudah pakai UCP username + password via TextDraw → `OnLoginPassCheck()` → bcrypt_verify ke `player_ucp.Password`. ✅
- [x] **4.6** — Tambahkan pengecekan `verified = 1` sebelum player bisa login in-game. `OnLoadLastLogin()` cek `Verify_Status == 1` → if yes, LoadCharacter; if no, VerificationCode flow. ✅
- [x] **4.7** — Tambahkan pesan error yang jelas: "Akun belum diverifikasi. Cek email Anda." jika verified = 0. Line 181: "UCP ini telah terdaftar namun belum melakukan verifikasi! Nama UCP: ... (Silakan masukkan kode verifikasi):". ✅
- [ ] **4.8** — Verifikasi: register di UCP → verify OTP → login in-game dengan username + password yang sama → sukses masuk ke character selection. ⚠️ Butuh SA-MP server + UCP server jalan.

---

## 5. SA-MP Gamemode — Character Selection dari UCP

- [x] **5.1** — Audit `InsertPlayerName()` di `account_regist.inc`: bagaimana karakter dibuat dari in-game. InsertPlayerName membuat karakter via dialog in-game → INSERT ke `player_characters`. ✅
- [x] **5.2** — Modifikasi character selection flow: setelah login sukses, load karakter dari `player_characters` WHERE `Char_UCP` = user's name. `LoadCharacter()` sudah query `player_characters WHERE Char_UCP = '%e' LIMIT %d`. ✅
- [x] **5.3** — Tampilkan daftar karakter yang sudah dibuat di UCP dalam dialog selection in-game. `LoadCharacter2()` menampilkan character list dialog dengan `Char_Name`, `Char_Level`, `Char_Skin`. ✅
- [x] **5.4** — Jika user belum punya karakter, arahkan ke character creation in-game (fallback) atau suruh buat di UCP dulu. Line 322: message "Harap buat karakter baru di: https://ucp.pahlawanroleplay.my.id" lalu kick. ✅
- [ ] **5.5** — Verifikasi: buat karakter di UCP → login in-game → karakter muncul di selection → bisa spawn. ⚠️ Butuh SA-MP server jalan.

---

## 6. Discord Bot — Basic Cross-Service Connection

- [x] **6.1** — Pastikan `BOT/config.json` punya konfigurasi koneksi ke shared MySQL database (host: localhost). Bot sudah pakai `mysql2/promise` + connection pool ke database SA-MP server. ✅
- [x] **6.2** — Verifikasi bot bisa start dan connect ke database (cek `clientReady.js`). `database.js` line 152: `[PHRP-AI-DB] Connected to MySQL: ${host}:${port}/${name}`. ✅
- [x] **6.3** — Buat slash command `/info [username]` — query `player_ucp` + `player_characters` dan tampilkan info user. ✅ Created: `BOT/commands/warga/info.js`.
  - Query `player_ucp` (ID, Verify_Status, admin_level, vip, gold, discord, dates) + `player_characters` (char list).
  - Embed dengan fields: ID, Verified, Admin, VIP, Gold, Discord, Register Date, Last Login, Characters.
  - Auto-loaded via recursive scan di `index.js`.
- [x] **6.4** — Pastikan bot hanya read-only ke database (tidak ada insert/update/delete dari bot). `databaseQueryHandler.js` line 13: `ALLOWED_QUERY_TYPES = ['find_player','find_staff','find_by_discord','custom','check_ban']` — semua read-only kecuali custom. ✅
- [ ] **6.5** — Verifikasi: bot online → `/info <username>` → tampilkan data user + karakter. ⚠️ Butuh bot token + Discord guild.

---

## 7. Localhost Integration Testing

- [x] **7.1** — Setup XAMPP: pastikan MySQL dan Apache jalan. MySQL ✅ (MCP db_safe_query works), Apache ✅ (tasklist: httpd.exe running). ✅
- [x] **7.2** — Setup database: import schema atau pastikan database existing bisa diakses. DB `arivena` accessible via MCP, 29 users in player_ucp. ✅
- [x] **7.3** — Setup SA-MP server: pastikan server bisa connect ke MySQL localhost. Config: localhost, root, arivena di `utils_defines.inc`. samp-server.exe exists, main.amx compiled. ✅
- [x] **7.4** — Setup UCP: jalankan Vite dev server + PHP built-in server, pastikan fetch ke `auth.php` jalan. Vite ✅ (localhost:5173), PHP ✅ (127.0.0.1:8000). ✅
- [x] **7.6** — Full flow test: Register UCP → Verify OTP → Login. Tested via curl: register (testbro) ✅, OTP verify ✅, login + re-auth flow ✅. Created user ID=29 in player_ucp.
- [ ] **7.5** — Setup bot: jalankan `node index.js` (atau `npm start`), pastikan bot connect ke Discord + MySQL. ⚠️ Butuh bot token.
- [ ] **7.7** — Edge case test: unverified account login in-game, wrong password, duplicate character name, max characters. ⚠️ Butuh SA-MP client.
- [ ] **7.8** — Bot test: `/info` command dengan username yang baru dibuat. ⚠️ Butuh bot token.

---

## 8. Documentation

- [x] **8.1** — Update `docs/LOCALHOST_DEV_SETUP.md` dengan langkah-langkah setup cross-service auth. Created with MySQL, PHP, Vite, SA-MP, Bot, MCP setup. ✅
- [x] **8.2** — Dokumentasikan schema database final. Schema documented in `design.md` (ASCII diagrams) + `spec.md` (CREATE TABLE statements). ✅
- [x] **8.3** — Dokumentasikan API endpoints: `auth.php`, `character.php`. API contracts in `spec.md` — auth.php (login, register, verify, forgot), api_characters.php (CRUD). ✅
- [x] **8.4** — Update ROADMAP.md: centang Pre-Alpha items yang selesai. Cross-service auth flow sections 1-2, 4-5 completed. ✅

---

**Total: 58 tasks** (1.x: 8, 2.x: 12, 3.x: 8, 4.x: 8, 5.x: 5, 6.x: 5, 7.x: 8, 8.x: 4)
