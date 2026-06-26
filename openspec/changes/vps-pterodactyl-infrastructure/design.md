## Context

PAHLAWAN ROLEPLAY terdiri dari 3 service yang harus jalan bersamaan:
- **SA-MP/open.mp Server** — Pawn gamemode, koneksi MySQL, plugin (streamer, sscanf, bcrypt, YSI).
- **UCP Website** — React/Vite frontend + PHP native backend di `public/api`, butuh Nginx + PHP-FPM + MySQL.
- **Discord Bot** — Node.js (v20+), Discord.js v14, koneksi MySQL untuk PHRP-AI module.

Ketiga service perlu shared MySQL database (`player_ucp`, `player_characters`, dll). VPS target punya 2 vCPU Ryzen 9 7900, 4GB DDR5, 50GB NVMe. Pterodactyl dipilih sebagai control panel karena menyediakan UI terpisah per service, auto-restart, resource limits, dan console access.

## Goals / Non-Goals

**Goals:**
- Dokumentasi langkah demi langkah dari beli VPS sampai semua service jalan di Pterodactyl.
- Semua service bisa di-start/stop/restart dari Pterodactyl UI tanpa SSH.
- Shared MySQL yang konsisten antara gamemode, web, dan bot.
- Environment variable management yang aman (tidak hardcoded, tidak di-commit).
- Resource allocation yang sesuai batas 4GB RAM.

**Non-Goals:**
- Tidak mengubah source code GAMEMODE, WEBSITE, atau BOT.
- Tidak setup CI/CD pipeline (itu task terpisah di ROADMAP `deployment-automation`).
- Tidak setup domain/SSL certificate (bisa ditambah setelah Alpha).
- Tidak setup external monitoring (Pterodactyl built-in monitoring cukup untuk Alpha).
- Tidak setup backup otomatis (manual backup acceptable untuk Alpha).

## Decisions

### 1. VPS Provider dan Spesifikasi

**Keputusan:** Gunakan VPS dengan spesifikasi 2 vCPU Ryzen 9 7900, 4GB DDR5, 50GB NVMe, 10Gbit/s network.

**Alternatif dipertimbangkan:** VPS dengan 8GB+ RAM. Ditolak karena budget dan resource 4GB cukup untuk Alpha (5-10 players). Bisa upgrade ke plan lebih tinggi sebelum Beta/RC.

### 2. OS: Ubuntu 22.04 LTS

**Keputusan:** Ubuntu 22.04 LTS sebagai host OS.

**Alasan:** Pterodactyl officially supported di Ubuntu 20.04/22.04. LTS = long-term security updates. Familiar untuk sysadmin. Package manager `apt` stabil.

**Alternatif dipertimbangkan:** Debian 12 — lebih ringan tapi Pterodactyl docs lebih lengkap untuk Ubuntu. AlmaLinux/Rocky — Pterodactyl support ada tapi komunitas lebih kecil.

### 3. Region: Singapore (preferred), fallback Eropa

**Keputusan:** Pilih region **Singapore** sebagai prioritas utama, fallback ke Eropa (Frankfurt/Amsterdam) bila Singapore tidak tersedia dengan spek target.

**Alasan:** Player base Indonesia terkoneksi lewat routing Singapore dengan latency ~30–50ms (vs 200–250ms dari Eropa). Roleplay butuh chat real-time dan SA-MP heartbeat sensitif ke ping. Target spek (2 vCPU Ryzen 9 7900, 4GB DDR5, 50GB NVMe, 10Gbit/s) lebih mudah ditemukan di provider Eropa; beberapa provider punya Singapore DC dengan spek identik atau setara.

**Alternatif dipertimbangkan:** Frankfurt/Amsterdam — latency 200–250ms masih playable tapi terasa lag untuk roleplay intensive. Tetap jadi fallback kalau Singapore tidak tersedia di provider pilihan atau harga terlalu tinggi.

### 4. Pterodactyl Panel + Wings di Host yang Sama

**Keputusan:** Install Pterodactyl Panel dan Wings daemon di VPS yang sama dengan service.

**Alasan:** Satu VPS = satu biaya. Untuk Alpha dengan 5-10 players, overhead Pterodactyl (~512MB RAM) masih manageable. Wings butuh Docker, dan service jalan di container.

**Resource budget:**
| Komponen | RAM Estimate |
|---|---|
| OS + Docker | ~512MB |
| Pterodactyl Panel | ~256MB |
| MySQL 8.0 | ~512MB |
| SA-MP Server | ~512MB |
| Nginx + PHP-FPM | ~256MB |
| Node.js Bot | ~256MB |
| Buffer | ~1.7GB |
| **Total** | **~4GB** |

### 5. MySQL di Host, Bukan Container

**Keputusan:** Install MySQL 8.0 langsung di host OS, bukan di Docker container.

**Alasan:** Pterodactyl sendiri butuh MySQL untuk panel database. Shared instance = hemat RAM. Service di container connect ke host MySQL via Docker bridge network (`172.17.0.1` atau hostname `host.docker.internal`).

**Alternatif dipertimbangkan:** MySQL di container terpisah — lebih isolated tapi overhead RAM lebih besar (~256MB extra) dan complexity network bertambah. Tidak worth untuk Alpha.

### 6. Pterodactyl Eggs: Custom, Bukan Community

**Keputusan:** Buat 3 custom eggs daripada pakai community eggs.

**Alasan:**
- **SA-MP/open.mp** — Community egg biasanya generic, tidak include plugin dan include files spesifik PAHLAWAN.
- **UCP Website** — Butuh Nginx + PHP-FPM combo yang spesifik, bukan generic PHP egg.
- **Discord Bot** — Butuh Node.js 20+ dan custom start script.

**Egg definitions:**
1. `egg-samp-server.json` — SA-MP server binary, auto-compile .pwn → .amx (optional), plugin loader, server.cfg template.
2. `egg-ucp-website.json` — Nginx reverse proxy + PHP-FPM 8.2, build Vite frontend, serve static + API.
3. `egg-discord-bot.json` — Node.js 20 LTS, `npm install` on startup, `node index.js` sebagai entry.

### 7. Git Deploy Strategy

**Keputusan:** Clone repo di VPS, symlink/copy ke Pterodactyl server directories.

**Flow:**
1. SSH ke VPS, clone repo ke `/opt/pahlawan-roleplay/`.
2. Pterodactyl server mount ke subfolder repo (atau copy saat deploy).
3. Untuk update: `git pull` + rebuild (jika perlu) + restart dari panel.

**Alternatif dipertimbangkan:** Upload file manual via SFTP — lebih simple tapi tidak traceable dan mudah out-of-sync. CI/CD push — ideal tapi masuk scope `deployment-automation` change terpisah.

## Risks / Trade-offs

### 4GB RAM Tight untuk 3 Service + Panel
**Risk:** OOM killer bisa kill service kalau usage spike.
**Mitigasi:** Set memory limit di setiap Pterodactyl server. Monitor RAM usage. Upgrade VPS plan sebelum Beta kalau perlu.

### Single Point of Failure
**Risk:** VPS down = semua service down.
**Mitigasi:** Acceptable untuk Alpha. Pertimbangkan failover/redundancy di RC.

### MySQL Host vs Container Network Complexity
**Risk:** Container connect ke host MySQL butuh network config yang benar.
**Mitigasi:** Gunakan `172.17.0.1` (Docker bridge gateway) sebagai MySQL host di env var container. Test koneksi sebelum start service.

### No SSL/Domain di Alpha
**Risk:** UCP website jalan di HTTP, bukan HTTPS.
**Mitigasi:** Acceptable untuk internal Alpha. Tambah domain + Let's Encrypt sebelum Beta.

### Pterodactyl + Docker Storage Overhead
**Risk:** Docker images makan storage dari 50GB NVMe.
**Mitigasi:** Prune unused images berkala. SA-MP image kecil (~200MB). Nginx+PHP ~150MB. Node.js ~300MB. Total ~1GB Docker images. 50GB lebih dari cukup.
