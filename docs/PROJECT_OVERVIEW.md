# Project Overview

## BOT

Entry aktif BOT adalah `BOT/index.js`, sesuai `main` dan script `start` di `BOT/package.json`.

Alur utama:

- Auto-check dependency Node.
- Membuat Discord client dengan intents guild, message, content, dan member.
- Load semua command dari `BOT/commands`.
- Load semua event dari `BOT/events`.
- Login memakai `BOT/config.json`.
- Deploy slash command ke guild.
- Memuat modul `BOT/PHRP-AI` untuk knowledge, channel routing, AI provider, chat history, dan query database.

File `BOT/bot.js` terlihat seperti struktur lama karena mengarah ke `./src/functions`, sementara struktur itu tidak ada di project saat ini. Anggap bukan entry aktif kecuali nanti dibuktikan masih dipakai.

## WEBSITE

Website adalah React + Vite + TypeScript, dengan backend PHP native di `WEBSITE/public/api`.

Alur utama:

- Frontend membaca API base dari `WEBSITE/config.ts`.
- Auth memakai `auth.php`, `register.php`, `verify.php`, dan `resend_otp.php`.
- Dashboard membaca karakter, inbox, donation, story, request, dan statistik dari endpoint `api_*.php`.
- Upload tersimpan di `WEBSITE/public/uploads`, yang dianggap data runtime.
- Backend database global diatur di `WEBSITE/public/api/config.php`.

Tabel utama yang dipakai:

- `player_ucp`
- `player_characters`
- `ucp_transactions`
- `ucp_inbox_messages`
- `ucp_support_tickets`
- `ucp_support_messages`
- `ucp_character_stories`
- `ucp_system_settings`
- `ucp_online_players`

## GAMEMODE

Entry utama gamemode adalah `GAMEMODE/gamemodes/main.pwn`.

Alur utama:

- Include dependency Pawn dan plugin seperti MySQL, streamer, sscanf, bcrypt, YSI, textdraw-streamer, dan sampvoice.
- Include `utils/utils`, lalu `core/gmcore`.
- `OnGameModeInit()` memanggil `Database_Connect()`.
- Setelah koneksi database, gamemode load data dynamic dari banyak tabel seperti `doors`, `shops`, `biz`, `houses`, `families`, `faction_garages`, `speedcam`, dan lainnya.
- Account/player flow utama ada di `GAMEMODE/gamemodes/core/account`.

Kontrak database utama dengan website dan bot:

- `player_ucp` untuk akun UCP, password, OTP, verification, Discord link, admin level, VIP, dan gold.
- `player_characters` untuk karakter in-game.
- `player_bans` untuk status ban.
- Tabel `ucp_*` untuk fitur website.

## DATABASE

Dump database utama lokal berada di `DATABASE/phrp.sql` jika tersedia. Isi folder `DATABASE` di-ignore oleh Git karena bisa berisi data penting atau rahasia, sedangkan struktur folder dijaga dengan `.gitkeep`.

## Nested Git Backup

Metadata Git lama dari folder nested dipindahkan ke `.git-nested-backups/` agar repo utama bisa melacak isi `GAMEMODE` sebagai source biasa.

Backup yang tersedia:

- `.git-nested-backups/GAMEMODE.git`
- `.git-nested-backups/GAMEMODE-pawno-include.git`

Folder backup ini di-ignore oleh Git root. Jika suatu saat perlu memulihkan history lama, pindahkan kembali folder backup tersebut ke lokasi `.git` asalnya.

## Risiko Yang Perlu Dijaga

- Token/API key/password tidak boleh masuk Git.
- History nested Git sudah diamankan di `.git-nested-backups`, bukan dihapus.
- File `.amx`, binary plugin, log, dan data runtime sebaiknya tidak dijadikan source utama.
- Perubahan struktur tabel harus dicek terhadap tiga sisi sekaligus: website, bot, dan gamemode.
