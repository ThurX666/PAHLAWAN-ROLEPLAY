# Local Validation Matrix

Dokumen ini merangkum validasi lokal minimum untuk area `GAMEMODE`, `WEBSITE`, dan `BOT` tanpa mengubah runtime behavior.

## Aturan Umum

- secret dan file privat seperti `.env`, token, credential, cookie, session, OTP, dan dump database tidak boleh dipublish atau disalin ke file tracked
- gunakan placeholder aman di file example atau dokumen
- jalankan hanya check yang relevan dengan area yang sedang dikerjakan

## Matrix

| Area | Dependency utama | Check minimum | Status | Expected outcome |
| --- | --- | --- | --- | --- |
| `GAMEMODE` | Pawn compiler lokal, include `GAMEMODE/pawno/include`, source `GAMEMODE/gamemodes/main.pwn` | compile gamemode lokal dengan toolchain Pawn yang biasa dipakai project | wajib jika mengubah gamemode | compile selesai tanpa error baru dan output `.amx` lokal terbentuk |
| `GAMEMODE` | runtime server lokal, plugin lokal, `server.cfg` privat | boot server lokal singkat bila environment tersedia | opsional | server bisa start untuk smoke check dasar tanpa perlu publish file runtime |
| `WEBSITE` | Node.js, npm, `WEBSITE/package.json` | dari `WEBSITE`: `npm install` lalu `npm run build` | wajib jika mengubah frontend UCP | build frontend selesai tanpa error |
| `WEBSITE` | PHP lokal, private `WEBSITE/.env`, API di `WEBSITE/public/api` | jalankan API lokal, misalnya `php -S 127.0.0.1:8000 -t WEBSITE/public` | hanya jika environment tersedia | endpoint PHP bisa dimuat lokal dengan config privat yang tetap di luar repo |
| `WEBSITE` | workflow lokal UCP, template env tracked | cocokkan setup dengan `WEBSITE/LOCAL_DEVELOPMENT_WORKFLOW.md` dan file example | wajib untuk perubahan docs/setup | setup tetap konsisten dan tidak meminta secret dimasukkan ke repo |
| `BOT` | Node.js, npm, `BOT/package.json` | dari `BOT`: `npm install` | wajib jika mengubah dependency atau docs setup bot | dependency bot dapat dipasang lokal tanpa menambah file privat ke repo |
| `BOT` | private `BOT/config.json` dan config runtime lain | jalankan `npm start` hanya jika config privat lokal tersedia | hanya jika environment tersedia | bot dapat start lokal tanpa menuliskan token atau credential ke file tracked |

## Catatan Per Area

### GAMEMODE

- fokus minimum adalah memastikan source `.pwn` masih bisa di-compile secara lokal
- `server.cfg`, plugin runtime, dan `scriptfiles` tetap privat atau runtime-only

### WEBSITE

- `WEBSITE/.env` tetap privat dan tidak boleh di-commit
- jika local SMTP, OAuth, atau provider AI belum tersedia, cukup lakukan check build frontend dan review docs setup

### BOT

- `BOT/config.json`, `BOT/config/*.json`, dan `BOT/PHRP-AI/config/*.json` tetap privat
- jika token Discord atau provider key belum tersedia, jangan memaksa startup penuh; cukup validasi dependency dan docs setup

## Kapan Matrix Ini Dipakai

- saat reviewer ingin memahami validasi minimum lintas area repo
- saat contributor baru butuh jalur setup aman tanpa membocorkan secret
- saat perubahan hanya menyentuh satu area dan tidak perlu menjalankan seluruh stack
