## Why

ROADMAP menetapkan deadline **Alpha Test 1 Agustus 2026** dimana tim internal harus bisa register, login, buat karakter, dan bermain di server. Ketiga service (SA-MP server, Discord bot, UCP website) harus jalan di satu tempat yang mudah di-manage. Tanpa infrastructure yang jelas, deployment jadi manual, error-prone, dan sulit di-restart kalau server down. Pterodactyl dipilih sebagai control panel karena menyediakan UI untuk start/stop/restart tiap service secara terpisah, auto-restart on crash, dan resource isolation per server.

## What Changes

- Definisikan spesifikasi VPS minimum untuk menampung ketiga service + Pterodactyl panel + MySQL.
- Definisikan langkah pembelian VPS: OS, region, network, dan storage.
- Definisikan pilihan provider VPS yang punya Anti-DDoS bawaan (contoh kandidat: VibeGames vServer) serta firewall hardening tambahan.
- Definisikan pembelian/setup domain, DNS, SSL, dan SMTP provider untuk Panel/UCP.
- Definisikan instalasi Pterodactyl panel + Wings daemon dari nol sampai functional.
- Definisikan 3 custom Pterodactyl egg JSON siap-import: SA-MP/open.mp server, UCP website (Nginx + PHP-FPM), Discord bot (Node.js).
- Definisikan shared MySQL setup yang bisa diakses semua service.
- Definisikan environment variable management per service.
- Definisikan deployment flow: dari git clone atau upload folder lokal ke VPS (`rsync`, `tar + scp`, SFTP), sync ke Pterodactyl volumes, sampai service jalan dan bisa di-kontrol dari Pterodactyl UI.

## Capabilities

### New Capabilities
- `vps-pterodactyl-infrastructure`: End-to-end setup VPS dari pembelian sampai Pterodactyl panel operational dengan 3 service eggs (SA-MP, web, bot) dan shared MySQL, siap untuk Alpha Test.

### Modified Capabilities
- Tidak ada. Change ini tidak mengubah kode GAMEMODE, WEBSITE, BOT, atau DATABASE.

## Impact

- **Infrastructure**: Menambah dokumentasi setup VPS, domain, SMTP, firewall, Pterodactyl, dan upload project ke VPS.
- **Deployment**: Operator bisa deploy, start, stop, restart tiap service dari Pterodactyl UI.
- **Database**: Shared MySQL instance di-host di VPS yang sama, bukan external DB service.
- **Tidak mengubah**: Source code Pawn, TypeScript/React, PHP, Node.js bot, atau schema database.
- **Resource**: VPS target 2 vCPU / 4GB DDR5 / 50GB NVMe cukup untuk Alpha (5-10 concurrent players).
