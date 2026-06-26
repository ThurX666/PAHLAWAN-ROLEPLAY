# VPS Setup Guide — PAHLAWAN ROLEPLAY

> Ringkasan operator dari setup VPS + Pterodactyl. Untuk versi **lengkap langkah-demi-langkah**, lihat `openspec/changes/vps-pterodactyl-infrastructure/SETUP_GUIDE.md`.
> OpenSpec change: `vps-pterodactyl-infrastructure`.

## Untuk Pemula: Mulai dari Mana?

Kalau ini pertama kali setup VPS, urutan baca yang paling gampang:

1. [`DOMAIN_PROVIDER_GUIDE.md`](DOMAIN_PROVIDER_GUIDE.md) — beli domain dan arahkan DNS.
2. [`VPS_PROVIDER_GUIDE.md`](VPS_PROVIDER_GUIDE.md) — pilih/order VPS (kandidat utama: VibeGames vServer Anti-DDoS).
3. [`SMTP_PROVIDER_GUIDE.md`](SMTP_PROVIDER_GUIDE.md) — setup email untuk OTP/reset password.
4. [`openspec/changes/vps-pterodactyl-infrastructure/SETUP_GUIDE.md`](../openspec/changes/vps-pterodactyl-infrastructure/SETUP_GUIDE.md) — ikuti command dari atas ke bawah.
5. [`PTERODACTYL_OPERATIONS.md`](PTERODACTYL_OPERATIONS.md) — setelah semua jalan, pakai ini untuk operasi harian.

**Tips:** Jangan langsung copy semua command sekaligus. Jalankan satu blok, cek hasilnya, baru lanjut.

## TL;DR Arsitektur

```
+---------------------------------------------------------------+
|                  VPS (Ubuntu 22.04)                           |
|  Region: Singapore (atau fallback EU)                         |
|  2 vCPU / 4 GB DDR5 / 50 GB NVMe / 10 Gbit                   |
|                                                               |
|  +---------------+    +-----------------+   +---------------+ |
|  | MySQL 8.0     |    | Pterodactyl     |   | Nginx +       | |
|  | (host)        |    | Panel           |   | PHP-FPM 8.1   | |
|  | :3306         |    | https://panel.  |   | (host)        | |
|  +-------+-------+    +--------+--------+   +-------+-------+ |
|          |                     |                    |         |
|          | 172.17.0.1          |                    |         |
|          +---------------------+--------------------+         |
|                                |                              |
|                       +--------v---------+                    |
|                       | Docker (Wings)   |                    |
|                       +---+----+----+----+                    |
|                           |    |    |                         |
|                       +---v+ +--v-+ +v----+                   |
|                       |SA-M| |UCP| |Bot |                    |
|                       |512M| |512| |384M|                    |
|                       +----+ +---+ +----+                    |
+---------------------------------------------------------------+
```

## Domain Architecture

| Subdomain | Tujuan | Proxy |
|---|---|---|
| `panel.pahlawan-roleplay.id` | Pterodactyl Panel | Cloudflare (Proxied) |
| `ucp.pahlawan-roleplay.id` | UCP Website | Cloudflare (Proxied) |
| `samp.pahlawan-roleplay.id` | SA-MP server (IP only) | DNS-only (no proxy) |
| `api.pahlawan-roleplay.id` | (opsional) API UCP | Cloudflare (Proxied) |

## Port Reference

| Port | Service | Akses |
|---|---|---|
| 22/tcp | SSH | Publik (via key only) |
| 80/tcp | HTTP (redirect ke HTTPS) | Publik |
| 443/tcp | HTTPS (Panel + UCP via Nginx) | Publik |
| 3306/tcp | MySQL 8.0 | Localhost + Docker bridge |
| 7777/tcp+udp | SA-MP Server | Publik |
| 9999/tcp | SA-MP secondary | Publik |
| 8081/tcp | UCP container (Nginx reverse-proxy internal) | Lokal (host Nginx ke 127.0.0.1:8081) |

## Stack Singkat

| Layer | Komponen | Sumber |
|---|---|---|
| OS | Ubuntu 22.04 LTS | VPS provider |
| Web server | Nginx 1.18+ | apt |
| App server (Panel) | PHP 8.1 + Laravel | apt + composer |
| App server (UCP) | PHP-FPM 8.1 + Vite-built static | apt + npm |
| Database | MySQL 8.0 | apt |
| Cache/Queue | Redis | apt |
| Container | Docker | get.docker.com |
| Panel agent | Pterodactyl Wings | GitHub release |
| Reverse proxy | Nginx + Cloudflare Origin Cert | self-config |

## 3 Service Custom Eggs

1. **PAHLAWAN SA-MP Server** (`docs/eggs/egg-samp-server.json`)
   - Model: import egg JSON, lalu Pterodactyl menjalankan install script saat server dibuat.
   - Base image: `ubuntu:22.04`.
   - Startup: `./samp03svr`.
   - Memory: 512 MB, Disk: 5 GB, Port: 7777

2. **PAHLAWAN UCP Website** (`docs/eggs/egg-ucp-website.json`)
   - Model: import egg JSON, install dependencies saat server dibuat.
   - Runtime: Nginx + PHP-FPM + Node 20.
   - Startup: build Vite + start PHP-FPM + Nginx
   - Memory: 512 MB, Disk: 5 GB, Port: 80

3. **PAHLAWAN Discord Bot** (`docs/eggs/egg-discord-bot.json`)
   - Model: import egg JSON.
   - Runtime: Node 20.
   - Startup: `npm install --production && node index.js`
   - Memory: 384 MB, Disk: 2 GB

## Akses Panel & URL Produksi

- **Pterodactyl Panel**: https://panel.pahlawan-roleplay.id
- **UCP Website**: https://ucp.pahlawan-roleplay.id
- **SA-MP Server**: `samp.pahlawan-roleplay.id:7777` (atau `<VPS_IP>:7777`)
- **Bot**: lihat status di Discord server

## File & Path Penting

| Path | Isi |
|---|---|
| `/opt/pahlawan-roleplay/` | Git repo (sumber semua file service) |
| `/var/www/pterodactyl/` | Pterodactyl Panel (Laravel) |
| `/etc/pterodactyl/config.yml` | Wings daemon config |
| `/var/lib/pterodactyl/volumes/<id>/` | Per-service files yang di-copy/sync dari repo via `rsync` |
| `docs/eggs/` | Egg JSON siap import ke Pterodactyl |
| `/etc/nginx/sites-available/pterodactyl.conf` | Nginx vhost |
| `/etc/nginx/ssl/` | Origin SSL certificate |

## Referensi Cepat

- **Setup lengkap langkah-demi-langkah**: `openspec/changes/vps-pterodactyl-infrastructure/SETUP_GUIDE.md`
- **SMTP provider untuk email Panel/UCP**: [docs/SMTP_PROVIDER_GUIDE.md](SMTP_PROVIDER_GUIDE.md)
- **Operasional harian (start/stop/restart/deploy)**: `docs/PTERODACTYL_OPERATIONS.md`
- **OpenSpec tasks**: `openspec/changes/vps-pterodactyl-infrastructure/tasks.md`
- **OpenSpec spec**: `openspec/changes/vps-pterodactyl-infrastructure/specs/vps-pterodactyl-infrastructure/spec.md`

---

## 12 Langkah Paling Penting (Urutan Kritis)

Jika cuma ingat beberapa hal, ingat ini:

1. **Beli VPS** dengan spek 2 vCPU / 4 GB / 50 GB NVMe di region terdekat, OS Ubuntu 22.04. Jika memakai VibeGames, pastikan **Anti DDoS Protection** aktif di paket.
2. **Setup user non-root + SSH key**, disable password login di SSH.
3. **Setup firewall UFW** hanya untuk port yang dipakai (22, 80, 443, 7777, 9999). Port 8081 (UCP container) dan 3306 (MySQL) hanya bind ke 127.0.0.1 / Docker bridge, tidak dibuka ke publik.
4. **Aktifkan advanced firewall & DDoS hardening** terutama jika memakai VibeGames vServer: SSH allowlist/rate-limit, MySQL hanya dari Docker bridge, sysctl hardening, iptables rate-limit untuk port SA-MP/open.mp, dan Nginx rate-limit.
5. **Install MySQL 8.0 di host** (bukan container) dengan bind-address 0.0.0.0.
6. **Install Pterodactyl Panel + Wings** di VPS yang sama, dengan Node resource limit 3584 MB.
7. **Setup Cloudflare DNS** dengan A record untuk `panel`, `ucp`, `samp` (samp DNS-only).
8. **Setup Cloudflare Origin SSL Certificate** di Nginx untuk HTTPS.
9. **Clone repo atau upload folder lokal** ke `/opt/pahlawan-roleplay/` di VPS (git clone, rsync, tar+scp, atau SFTP).
10. **Import 3 egg JSON** dari `docs/eggs/` untuk SA-MP, UCP, dan Discord bot.
11. **Copy/sync file repo ke Pterodactyl volumes** memakai `rsync` sesuai guide lengkap.
12. **Set env var sensitive via Panel UI** (Discord token, DB password), **JANGAN** commit ke repo.

---

Setelah setup selesai, langsung ke `docs/PTERODACTYL_OPERATIONS.md` untuk cara start/stop/restart service, deploy update, dan troubleshooting sehari-hari.