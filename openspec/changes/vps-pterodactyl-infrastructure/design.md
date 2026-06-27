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
- Tidak setup external monitoring berbayar/terpisah (Pterodactyl built-in monitoring + command troubleshooting cukup untuk Alpha).
- Tidak setup backup otomatis production-grade (manual backup acceptable untuk Alpha; cron backup optional untuk Beta).

**Scope tambahan yang sekarang masuk guide:**
- Pembelian domain + DNS + SSL Cloudflare/Origin Certificate.
- Pembelian/setup SMTP provider untuk email Panel/UCP.
- Upload folder project lokal ke VPS (`rsync`, `tar + scp`, SFTP) selain `git clone`.
- Advanced firewall/DDoS hardening untuk provider game server seperti VibeGames.

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

### 6. Pterodactyl Eggs: Custom JSON, Bukan Community

**Keputusan:** Buat 3 custom egg JSON siap-import (`docs/eggs/*.json`) daripada pakai community eggs. Egg memakai model **install-on-creation**: base image umum (`ubuntu:22.04` atau `node:20-bookworm-slim`) + installation script di egg, bukan custom Docker image manual.

**Alasan:**
- **SA-MP/open.mp** — Community egg biasanya generic, tidak include plugin dan include files spesifik PAHLAWAN.
- **UCP Website** — Butuh Nginx + PHP-FPM combo yang spesifik, bukan generic PHP egg.
- **Discord Bot** — Butuh Node.js 20+ dan custom start script.

**Egg definitions:**
1. `docs/eggs/egg-samp-server.json` — base `ubuntu:22.04`, installation script menyiapkan SA-MP binary/plugin dasar, startup `./samp03svr`.
2. `docs/eggs/egg-ucp-website.json` — Nginx + PHP-FPM + Node.js 20, build Vite frontend, serve static + API.
3. `docs/eggs/egg-discord-bot.json` — Node.js 20 LTS, `npm install --production` on startup, `node index.js` sebagai entry.

### 7. Repository Upload / Deploy Strategy

**Keputusan:** Sumber project ditempatkan di `/opt/pahlawan-roleplay/`, lalu di-copy/sync ke Pterodactyl volumes menggunakan `rsync`. Untuk memasukkan source ke VPS, operator boleh memilih: `git clone`, upload lokal via `rsync`, upload `tar + scp`, atau SFTP.

**Flow:**
1. SSH ke VPS, buat `/opt/pahlawan-roleplay/`.
2. Isi folder tersebut melalui salah satu metode: `git clone`, `rsync` dari laptop, `tar + scp`, atau SFTP.
3. Setup env/config production di `/opt/pahlawan-roleplay/`.
4. Copy/sync ke `/var/lib/pterodactyl/volumes/<server_id>/` menggunakan `rsync -a --delete` per service.
5. Untuk update: `git pull` atau upload ulang source lokal → `rsync` service terkait → restart dari Panel.

**Alternatif dipertimbangkan:**
- Symlink langsung ke repo — ditolak sebagai default karena lebih rawan salah path untuk pemula.
- Upload file manual via SFTP — tetap didokumentasikan sebagai opsi GUI, tapi update jangka panjang lebih baik memakai Git/rsync.
- CI/CD push — ideal tapi masuk scope `deployment-automation` change terpisah.

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

### Domain/SSL/SMTP Setup Bisa Membingungkan Pemula
**Risk:** Salah DNS/SSL/SMTP membuat Panel/UCP tidak bisa diakses atau email OTP tidak terkirim.
**Mitigasi:** Pisahkan guide domain (`docs/DOMAIN_PROVIDER_GUIDE.md`) dan SMTP (`docs/SMTP_PROVIDER_GUIDE.md`) dengan checklist dan test `swaks`.

### Pterodactyl + Docker Storage Overhead
**Risk:** Docker base images, volumes, npm cache, logs, dan backups makan storage dari 50GB NVMe.
**Mitigasi:** Prune unused Docker resources berkala, jangan upload `node_modules/` dan log/cache dari lokal, serta pantau `df -h`.

### Firewall / DDoS Misconfiguration
**Risk:** Port terlalu terbuka (MySQL public) atau firewall terlalu agresif (player tidak bisa connect).
**Mitigasi:** UFW default deny, MySQL hanya dari Docker bridge, SA-MP TCP+UDP dibuka, advanced iptables rate-limit dibuat opsional/bertahap, dan provider Anti-DDoS seperti VibeGames tetap dipakai sebagai lapisan depan.
