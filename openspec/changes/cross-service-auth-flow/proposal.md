## Why

ROADMAP menetapkan deadline **Alpha Test 1 Agustus 2026** dimana tim internal harus bisa **register, login, buat karakter, dan bermain** di server. Tiga service — SA-MP server, Discord bot, UCP website — harus bekerja dengan **satu database bersama** dan **satu sistem autentikasi**.

Saat ini autentikasi UCP (PHP session + auth.php) dan autentikasi in-game (Pawn account_regist.inc) berjalan **terpisah**. Tidak ada jaminan bahwa akun yang dibuat di UCP bisa dipakai login in-game, atau sebaliknya. Character creation di UCP (CreateCharacterModal.tsx) belum terhubung ke backend/database game. Bot Discord sudah punya koneksi DB tapi belum terintegrasi ke flow auth.

**Target:** Semua service berbagi satu source of truth di database yang sama, berjalan di **localhost** (development) dulu sebelum nanti deployment ke VPS.

## What Changes

- **Definisikan database schema terpadu**: `player_ucp` (akun) + `player_characters` (karakter) dengan relasi yang jelas.
- **Unifikasi auth flow UCP**: Pastikan `auth.php` + `auth_session.php` menyimpan akun ke tabel yang bisa diakses semua service.
- **Refactor login in-game**: Gamemode membaca dari tabel `player_ucp` yang sama, bukan tabel terpisah.
- **Character creation pipeline**: CreateCharacterModal di UCP → API endpoint → simpan ke `player_characters` → in-game bisa select karakter yang sudah dibuat.
- **Database sync**: Migration script jika diperlukan untuk menyelaraskan schema existing.
- **Bot Discord basic connection**: Bot connect ke database yang sama, verifikasi bisa query user/character data.
- **Localhost development**: Semua jalan di localhost — XAMPP (PHP/MySQL), SA-MP server (localhost:7777), bot Discord (token dev), UCP (Vite dev server).

## Capabilities

### New Capabilities
- `cross-service-auth-flow`: End-to-end auth flow dari register UCP → verify OTP → login UCP → create character → login in-game → spawn — semua pakai database yang sama, berjalan di localhost.

### Modified Capabilities
- `ucp-local-auth-dev-flow`: Existing spec untuk local auth preview di UCP — diperluas untuk connect ke shared database.
- Tidak ada perubahan ke `vps-pterodactyl-infrastructure` — change ini fokus di code/auth, bukan infrastructure.

## Impact

- **GAMEMODE**: `account_regist.inc` dan login dialog akan di-refactor untuk query tabel `player_ucp` (shared) bukan tabel lokal.
- **WEBSITE**: `auth.php`, komponen Auth, CreateCharacterModal dihubungkan ke database production (bukan dummy/preview).
- **BOT**: Bot Discord diverifikasi bisa connect dan query shared database (read-only untuk Alpha).
- **DATABASE**: Schema migration untuk memastikan `player_ucp` dan `player_characters` punya struktur yang konsisten.
- **Tidak mengubah**: Fitur non-auth (bisnis, inventory, faction, dll) — fokus hanya auth+character flow.
- **Resource**: Localhost — tidak ada resource constraint, bisa develop tanpa VPS.
