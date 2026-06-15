# PAHLAWAN ROLEPLAY

Monorepo kerja untuk tiga bagian utama Pahlawan Roleplay:

- `BOT` - Discord bot Node.js untuk command, ticket, staff tools, dan PHRP-AI.
- `WEBSITE` - UCP React/Vite dengan backend PHP native di `public/api`.
- `GAMEMODE` - SA-MP/Pawn gamemode dan runtime server.
- `DATABASE` - Folder lokal untuk dump database utama MySQL/MariaDB. Isi dump di-ignore karena bisa berisi data penting.

## Setup Singkat

1. Import database lokal dari `DATABASE/phrp.sql` ke MySQL/MariaDB jika file dump tersedia di mesin ini.
2. Isi `BOT/config.json` untuk token, channel, payment, server, dan database bot.
3. Isi `BOT/PHRP-AI/config/app.json` untuk provider dan API key AI.
4. Isi `WEBSITE/.env` untuk `VITE_API_BASE_URL`.
5. Isi `WEBSITE/public/api/config.php` untuk database, SMTP, sosial media, dan query SA-MP.
6. Isi `GAMEMODE/server.cfg` untuk RCON/runtime server.
7. Sesuaikan konfigurasi database gamemode di `GAMEMODE/gamemodes/utils/utils_defines.inc`.

## Menjalankan

BOT:

```bash
cd BOT
npm install
npm start
```

WEBSITE:

```bash
cd WEBSITE
npm install
npm run dev
```

GAMEMODE:

Compile `GAMEMODE/gamemodes/main.pwn` dengan compiler Pawn/Pawno yang sesuai, lalu jalankan server dari folder `GAMEMODE`.

## Catatan Repo

File credential dan runtime tidak dimasukkan ke Git. Jangan commit `config.json`, `.env`, token bot, API key, database password, log, binary server, atau hasil compile `.amx`.
