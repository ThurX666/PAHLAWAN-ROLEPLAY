# VPS Setup Guide — PAHLAWAN ROLEPLAY

> Ringkasan operator dari setup VPS + Pterodactyl. Untuk versi **lengkap langkah-demi-langkah**, lihat `openspec/changes/vps-pterodactyl-infrastructure/SETUP_GUIDE.md`.
> OpenSpec change: `vps-pterodactyl-infrastructure`.

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
| 8080-8090/tcp | Pterodactyl allocation range | Publik (saat pakai IP) |

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

1. **PAHLAWAN SA-MP Server** (`egg-samp-server.json`)
   - Image: `pahlawan/samp:latest` (Ubuntu 22.04 + SA-MP binaries + plugins)
   - Startup: `./samp03svr`
   - Memory: 512 MB, Disk: 5 GB, Port: 7777

2. **PAHLAWAN UCP Website** (`egg-ucp-website.json`)
   - Image: `pahlawan/ucp:latest` (Nginx + PHP-FPM 8.1 + Node 20)
   - Startup: build Vite + start PHP-FPM + Nginx
   - Memory: 512 MB, Disk: 5 GB, Port: 80

3. **PAHLAWAN Discord Bot** (`egg-discord-bot.json`)
   - Image: `pahlawan/bot:latest` (Node 20)
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
| `/var/lib/pterodactyl/volumes/<id>/` | Per-service files (symlink ke repo) |
| `/opt/pterodactyl-images/` | Custom Docker images (source) |
| `/etc/nginx/sites-available/pterodactyl.conf` | Nginx vhost |
| `/etc/nginx/ssl/` | Origin SSL certificate |

## Referensi Cepat

- **Setup lengkap langkah-demi-langkah**: `openspec/changes/vps-pterodactyl-infrastructure/SETUP_GUIDE.md`
- **SMTP provider untuk email Panel/UCP**: [docs/SMTP_PROVIDER_GUIDE.md](SMTP_PROVIDER_GUIDE.md)
- **Operasional harian (start/stop/restart/deploy)**: `docs/PTERODACTYL_OPERATIONS.md`
- **OpenSpec tasks**: `openspec/changes/vps-pterodactyl-infrastructure/tasks.md`
- **OpenSpec spec**: `openspec/changes/vps-pterodactyl-infrastructure/specs/vps-pterodactyl-infrastructure/spec.md`

---

## 10 Langkah Paling Penting (Urutan Kritis)

Jika cuma ingat 10 hal, ingat ini:

1. **Beli VPS** dengan spek 2 vCPU / 4 GB / 50 GB NVMe di region Singapore, OS Ubuntu 22.04.
2. **Setup user non-root + SSH key**, disable password login di SSH.
3. **Setup firewall UFW** hanya untuk port yang dipakai (22, 80, 443, 3306-local, 7777, 8080-8090).
4. **Install MySQL 8.0 di host** (bukan container) dengan bind-address 0.0.0.0.
5. **Install Pterodactyl Panel + Wings** di VPS yang sama, dengan Node resource limit 3584 MB.
6. **Setup Cloudflare DNS** dengan A record untuk `panel`, `ucp`, `samp` (samp DNS-only).
7. **Setup Cloudflare Origin SSL Certificate** di Nginx untuk HTTPS.
8. **Clone repo** ke `/opt/pahlawan-roleplay/` di VPS.
9. **Buat 3 custom Docker images** (`pahlawan/samp`, `pahlawan/ucp`, `pahlawan/bot`) dan **import 3 eggs**.
10. **Set env var sensitive via Panel UI** (Discord token, DB password), **JANGAN** commit ke repo.

---

Setelah setup selesai, langsung ke `docs/PTERODACTYL_OPERATIONS.md` untuk cara start/stop/restart service, deploy update, dan troubleshooting sehari-hari.