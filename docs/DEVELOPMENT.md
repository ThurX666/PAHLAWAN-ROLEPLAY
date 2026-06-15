# Development Workflow

Dokumen ini jadi pegangan kerja lokal untuk PAHLAWAN ROLEPLAY. Repo tetap private, tapi credential dan file runtime tetap di-ignore supaya aman.

## Codex dan MCP

Project ini punya konfigurasi MCP lokal di `.codex/config.toml`.

MCP yang aktif untuk project:

- `context7` - membaca dokumentasi library/framework yang terbaru lewat MCP.

MCP/plugin yang sudah aktif dari konfigurasi Codex user:

- GitHub - bantu cek repo, PR, issue, dan workflow GitHub.
- Browser - bantu test website lokal lewat browser Codex.
- Node REPL - bantu analisis JavaScript/JSON tanpa mengubah file project.

Setelah mengubah `.codex/config.toml`, restart Codex atau buka thread baru kalau MCP belum muncul.

## Struktur Kerja

- `BOT` - Discord bot Node.js.
- `WEBSITE` - UCP React/Vite dan backend PHP di `public/api`.
- `GAMEMODE` - SA-MP/Pawn gamemode dan runtime server.
- `DATABASE` - dump database lokal. Isi folder ini di-ignore.
- `docs` - catatan alur dan dokumentasi project.

## Website

Jalankan dari folder `WEBSITE`:

```powershell
npm install
npm run dev -- --host 127.0.0.1 --port 5173
```

Build production:

```powershell
npm run build
```

File lokal penting:

- `WEBSITE/.env`
- `WEBSITE/public/api/config.php`

Keduanya tidak boleh di-commit.

## Bot

Jalankan dari folder `BOT`:

```powershell
npm install
npm start
```

File lokal penting:

- `BOT/config.json`
- `BOT/config/*.json`
- `BOT/PHRP-AI/config/*.json`
- `BOT/data/*.json`

File tersebut di-ignore karena bisa berisi token Discord, API key AI, channel ID, dan data runtime.

## Gamemode

Source utama:

- `GAMEMODE/gamemodes/main.pwn`
- `GAMEMODE/gamemodes/core`
- `GAMEMODE/gamemodes/utils`
- `GAMEMODE/pawno/include`

Runtime lokal penting:

- `GAMEMODE/server.cfg`
- `GAMEMODE/plugins`
- `GAMEMODE/scriptfiles`
- hasil compile `.amx`

File runtime dan binary server tidak di-commit. Saat mengubah gamemode, edit source `.pwn` dan `.inc`, lalu compile secara lokal dengan Pawn compiler yang sesuai.

## Database

Dump database disimpan lokal di:

```text
DATABASE/phrp.sql
```

Isi folder `DATABASE` di-ignore kecuali `.gitkeep`. Jangan commit dump database asli karena bisa berisi data akun, karakter, inventory, password hash, IP, atau data internal server.

## Git Workflow

Alur kerja yang disarankan:

```powershell
git status
git checkout -b codex/nama-pekerjaan
git add .
git commit -m "deskripsi singkat"
git push -u origin codex/nama-pekerjaan
```

Untuk perubahan kecil langsung di `main` masih bisa, tapi untuk edit besar seperti sistem UCP, bot, database, atau gamemode, lebih rapi pakai branch baru.

## Checklist Sebelum Commit

- Jalankan build atau test yang relevan.
- Cek `git status --ignored` kalau ragu ada file rahasia.
- Pastikan tidak ada `.env`, config, token, dump database, log, binary, atau `.amx` ikut staged.
- Baca ulang diff dengan `git diff --cached`.
