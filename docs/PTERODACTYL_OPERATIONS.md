# Pterodactyl Operations — PAHLAWAN ROLEPLAY

> Panduan operasional harian: start/stop/restart service, deploy update, cek log, troubleshooting umum.
> Untuk setup awal, lihat `docs/VPS_SETUP_GUIDE.md` dan `openspec/changes/vps-pterodactyl-infrastructure/SETUP_GUIDE.md`.

---

## Daftar Isi

1. [Akses Pterodactyl Panel](#1-akses-pterodactyl-panel)
2. [Start / Stop / Restart Service](#2-start--stop--restart-service)
3. [Cek Log Service](#3-cek-log-service)
4. [Deploy Update Code](#4-deploy-update-code)
5. [Update Environment Variable](#5-update-environment-variable)
6. [Backup Database](#6-backup-database)
7. [Restart Stack Inflight (Panel/Wings/MySQL)](#7-restart-stack-inflight-panelwingsmysql)
8. [Troubleshooting Umum](#8-troubleshooting-umum)
9. [Kontak Darurat](#9-kontak-darurat)

---

## 1. Akses Pterodactyl Panel

**URL**: https://panel.pahlawan-roleplay.id

Login dengan akun admin yang dibuat saat setup. Jika lupa password:

```bash
# SSH ke VPS, lalu:
cd /var/www/pterodactyl
sudo php artisan p:user:make
# Ikuti prompt untuk buat admin baru atau reset
```

---

## 2. Start / Stop / Restart Service

### Lewat Panel UI (Cara Utama)

1. Login Panel.
2. **Servers** di sidebar.
3. Klik nama service yang mau dikontrol (contoh: `PAHLAWAN SA-MP Server`).
4. Header button:
   - **Start** (hijau) — nyalakan service.
   - **Stop** (merah) — matikan service (graceful shutdown).
   - **Restart** (kuning) — stop lalu start lagi.
   - **Kill** (merah gelap) — paksa mati (gunakan hanya jika Stop hang).

### Lewat CLI (Untuk SSH User)

```bash
# List semua server ID
sudo ls /var/lib/pterodactyl/volumes/

# Stop/Start server via Wings (ganti <server_id>)
sudo docker stop <container_name>      # stop
sudo docker start <container_name>     # start
sudo docker restart <container_name>   # restart
```

Atau via Pterodactyl API:

```bash
# Set API key dulu di Panel -> Account -> API Credentials
export PANEL_URL="https://panel.pahlawan-roleplay.id"
export API_KEY="ptla_xxx..."

curl -X POST "$PANEL_URL/api/client/servers/<server_id>/power" \
    -H "Authorization: Bearer $API_KEY" \
    -H "Content-Type: application/json" \
    -d '{"signal":"start"}'    # signal: start | stop | restart | kill
```

---

## 3. Cek Log Service

### Lewat Panel UI

1. Servers → klik service → tab **Console**.
2. Logs real-time ditampilkan di sini.
3. Bisa di-scroll ke atas dengan panah, atau download raw dengan klik ikon **Download Log**.

### Lewat CLI (Untuk Log Host-Level)

```bash
# Pterodactyl Panel log
sudo tail -f /var/log/nginx/pterodactyl.access.log
sudo tail -f /var/log/nginx/pterodactyl.error.log

# Wings daemon log
sudo journalctl -u wings -f

# Pterodactyl queue worker
sudo journalctl -u pteroq -f

# MySQL
sudo tail -f /var/log/mysql/error.log

# Docker container (per server)
sudo docker logs -f <container_name>
```

---

## 4. Deploy Update Code

### 4.1. Update dari Git Repository

```bash
# SSH ke VPS
ssh pahlawan@<VPS_IP>

cd /opt/pahlawan-roleplay

# Pull perubahan terbaru
git fetch origin
git pull origin main

# Lihat apa yang berubah
git log --oneline -10
git diff --stat HEAD~1
```

### 4.2. SA-MP Server Update

```bash
cd /opt/pahlawan-roleplay/GAMEMODE

# Jika ada perubahan .pwn (Pawn source), perlu recompile
docker run --rm -v "$PWD":/src -w /src ghcr.io/pawn-lang/pawncc:latest \
    pawncc gamemodes/main.pwn -o gamemodes/main.amx

# Restart SA-MP dari Panel UI (Servers -> klik server -> Restart)
```

### 4.3. UCP Website Update

```bash
# Tidak perlu rebuild manual — UCP egg auto-build saat container start.

# Trigger rebuild dengan restart dari Panel UI
# Servers -> PAHLAWAN UCP Website -> Restart
# Container akan re-run npm install + npm run build saat startup.
```

### 4.4. Discord Bot Update

```bash
# Restart dari Panel UI untuk trigger npm install ulang
# Servers -> PAHLAWAN Discord Bot -> Restart
```

### 4.5. Rollback Jika Update Bermasalah

```bash
cd /opt/pahlawan-roleplay
git log --oneline -5      # lihat commit
git checkout <commit_hash> -- .   # checkout versi lama (working tree)
git pull                  # refresh ke main lagi setelah fix

# Lalu restart service terkait dari Panel
```

---

## 5. Update Environment Variable

### Lewat Panel UI (Untuk Service)

1. Servers → klik service → tab **Startup**.
2. Scroll ke bagian **Environment Variables**.
3. Edit nilai (contoh: `DB_PASS`, `DISCORD_TOKEN`).
4. Klik **Save**.
5. **Restart** service untuk env var baru di-load.

### Lewat CLI (Untuk Panel Sendiri)

```bash
sudo nano /var/www/pterodactyl/.env
# Edit, save, exit

cd /var/www/pterodactyl
sudo php artisan config:clear
sudo php artisan cache:clear
sudo systemctl restart pteroq
```

### Lewat CLI (Untuk Service, langsung edit file)

```bash
# SA-MP
sudo nano /opt/pahlawan-roleplay/GAMEMODE/server.cfg

# UCP (env file)
sudo nano /opt/pahlawan-roleplay/WEBSITE/.env

# Bot
sudo nano /opt/pahlawan-roleplay/BOT/config.json
```

**Setelah edit via CLI, restart service dari Panel UI.**

---

## 6. Backup Database

### Manual Backup

```bash
# Backup semua database
sudo mysqldump --all-databases --single-transaction --quick --lock-tables=false \
    -u root -p | gzip > /root/backup-$(date +%Y%m%d-%H%M%S).sql.gz

# Backup spesifik PAHLAWAN database saja
sudo mysqldump arivena --single-transaction -u root -p | \
    gzip > /root/arivena-backup-$(date +%Y%m%d-%H%M%S).sql.gz

# List backup
ls -lh /root/*.sql.gz
```

### Restore

```bash
# Decompress dan restore
gunzip < /root/arivena-backup-YYYYMMDD-HHMMSS.sql.gz | \
    sudo mysql -u root -p arivena
```

### Auto Backup (Opsional, Recommended untuk Beta)

```bash
sudo crontab -e
# Tambah baris:
0 3 * * * /usr/bin/mysqldump arivena --single-transaction -u root -p<PASSWORD> | gzip > /root/arivena-auto-$(date +\%Y\%m\%d).sql.gz
```

> **Catatan keamanan:** Jangan taruh password MySQL plain text di cron. Solusi lebih aman: buat file `.my.cnf` di `/root/` dengan credentials, chmod 600.

---

## 7. Restart Stack Inflight (Panel/Wings/MySQL)

### Panel tidak bisa diakses

```bash
sudo systemctl status nginx pteroq
sudo systemctl restart nginx
sudo systemctl restart pteroq

# Cek log
sudo tail -n 100 /var/log/nginx/pterodactyl.error.log
sudo journalctl -u pteroq -n 100 --no-pager
```

### Wings node status merah (disconnected)

```bash
sudo systemctl status wings
sudo systemctl restart wings
sleep 5
sudo systemctl status wings

# Test
sudo docker ps   # harus ada container server
```

### MySQL down

```bash
sudo systemctl status mysql
sudo systemctl restart mysql

# Cek error
sudo tail -n 50 /var/log/mysql/error.log
```

### Docker daemon down

```bash
sudo systemctl status docker
sudo systemctl start docker
sudo systemctl restart wings
```

---

## 8. Troubleshooting Umum

### 8.1. Service Tidak Mau Start dari Panel

**Cek di:**
1. Panel → Servers → klik server → tab **Console** → lihat log error.
2. SSH → `sudo docker logs <container_name>` → lihat log lengkap.

**Penyebab umum:**
- **Port sudah dipakai**: `bind: address already in use` → cek `sudo netstat -tlnp | grep <port>`.
- **Environment variable kosong** (DB_PASS / DISCORD_TOKEN) → cek tab **Startup**.
- **Symlink rusak**: cek `ls -la /var/lib/pterodactyl/volumes/<server_id>/` harus pointing ke `/opt/pahlawan-roleplay/...`.
- **Disk penuh**: `df -h` di host → Panel tab **Resource** → disk usage.

### 8.2. OOM Killed

**Gejala:** Service tiba-tiba mati, di syslog: `Out of memory: Killed process`.

**Cek:**
```bash
dmesg | grep -i "oom\|killed"
```

**Solusi:**
- Kurangi memory limit di Panel → Server → **Resource Limits**.
- Cek service lain yang makan RAM: `sudo docker stats`.
- Upgrade VPS ke plan 8 GB jika sering OOM.

### 8.3. SA-MP Server Tidak Bisa Connect

**Cek:**
1. Port 7777 listening?
   ```bash
   sudo netstat -tlnp | grep 7777
   # Harus ada docker container listen di 0.0.0.0:7777
   ```
2. Firewall UFW allow 7777/tcp + 7777/udp?
   ```bash
   sudo ufw status | grep 7777
   ```
3. Plugin streamer/sscanf loaded di log? (saat start, console SA-MP menampilkan "Loaded plugin ...").
4. Server.cfg `bind` benar? `bind 0.0.0.0` untuk listen semua interface.

### 8.4. UCP Website Blank / 502 Bad Gateway

**Cek:**
1. Container running?
   ```bash
   sudo docker ps | grep ucp
   ```
2. Nginx config error?
   ```bash
   sudo docker exec -it <ucp_container> nginx -t
   ```
3. PHP-FPM running?
   ```bash
   sudo docker exec -it <ucp_container> service php8.1-fpm status
   ```
4. Vite build artifact ada?
   ```bash
   sudo docker exec -it <ucp_container> ls -lh /home/container/dist/
   ```

**Solusi cepat:**
- Stop → Start ulang dari Panel UI (trigger rebuild).
- Cek log error di Panel → Console.

### 8.5. Discord Bot Offline / Crash

**Cek:**
1. Token valid?
   - Buka Discord Developer Portal → Bot → cek token.
   - Bandingkan dengan env var di Panel → Server → **Startup** → `DISCORD_TOKEN`.
2. Internet VPS ke Discord gateway OK?
   ```bash
   curl -I https://discord.com/api/v10/gateway
   # 200 atau 429 OK
   ```
3. MySQL accessible dari container?
   ```bash
   sudo docker exec -it <bot_container> bash
   apt-get update && apt-get install -y default-mysql-client
   mysql -h 172.17.0.1 -u pahlawan -p<PASS> arivena -e "SELECT 1;"
   ```

### 8.6. Pterodactyl Queue Worker Mati

```bash
sudo systemctl status pteroq
sudo systemctl restart pteroq
sudo journalctl -u pteroq -n 100 --no-pager
```

Biasanya queue worker mati karena Redis down. Cek:
```bash
sudo systemctl status redis-server
sudo systemctl restart redis-server
sudo systemctl restart pteroq
```

### 8.7. Disk Penuh

```bash
# Cek penggunaan
df -h
sudo du -sh /var/lib/docker/    # Docker images & containers
sudo du -sh /var/log/            # Logs
sudo du -sh /root/*.sql.gz       # Backups

# Cleanup Docker
sudo docker system prune -a --volumes   # HATI-HATI: hapus semua stopped containers, unused images, volumes

# Hapus backup lama
sudo rm /root/*.sql.gz.old

# Rotate logs
sudo journalctl --vacuum-time=7d
```

### 8.8. Nginx Restart Gagal Setelah Edit Config

```bash
sudo nginx -t   # Test config syntax
# Fix error yang ditampilkan, lalu:
sudo systemctl restart nginx
```

---

## 9. Kontak Darurat

(Template — sesuaikan dengan tim Anda)

| Peran | Nama | Telegram | Email |
|---|---|---|---|
| Owner / Sysadmin | (nama) | @username | email@domain |
| Dev Lead | (nama) | @username | email@domain |
| Panel Admin | (nama) | @username | email@domain |

**Provider support:**
- VPS: link support di dashboard provider
- Domain registrar (Cloudflare): https://dash.cloudflare.com → Support
- SMTP (Zoho): https://www.zoho.com/mail/help.html

---

## Cheat Sheet — 5 Perintah Darurat Paling Sering Dipakai

```bash
# 1. Cek status semua service
sudo systemctl status nginx mysql wings pteroq redis-server

# 2. Restart service via CLI (kalau Panel hang)
sudo docker ps                # list container
sudo docker restart <name>    # restart container

# 3. Tail log service (real-time)
sudo docker logs -f <name>

# 4. Disk usage check
df -h && sudo du -sh /var/lib/docker/

# 5. Test MySQL dari container
sudo docker run --rm mysql:8.0 mysql -h 172.17.0.1 -u pahlawan -p<PASS> arivena -e "SELECT 1;"
```

---

**Update guide ini** setiap ada perubahan setup. Simpan versi terbaru di Git bersama kode (JANGAN taruh kredensial di file).