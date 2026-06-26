## 1. VPS Procurement

- [ ] 1.1 Pilih VPS provider dan order plan: 2 vCPU Ryzen 9 7900, 4GB DDR5, 50GB NVMe, 10Gbit/s.
- [ ] 1.2 Pilih OS: **Ubuntu 22.04 LTS** (64-bit).
- [ ] 1.3 Pilih region: **Singapore** (prioritas latency ke player base Indonesia, ~30–50ms). Jika provider tidak punya Singapore dengan spek Ryzen 9 + 10Gbit/s + harga yang sama, fallback ke **Frankfurt/Amsterdam** (latency 200–250ms, masih playable untuk roleplay).
- [ ] 1.4 Selesaikan pembayaran dan tunggu provisioning (target: < 5 menit).
- [ ] 1.5 Catat IP address VPS, username root, dan initial password/key.
- [ ] 1.6 SSH ke VPS: `ssh root@<VPS_IP>` dan ganti password root segera.
- [ ] 1.7 Buat user non-root: `adduser pahlawan` + `usermod -aG sudo pahlawan`.
- [ ] 1.8 Setup SSH key authentication untuk user `pahlawan`, disable password login di `/etc/ssh/sshd_config`.
- [ ] 1.9 Update sistem: `apt update && apt upgrade -y`.
- [ ] 1.10 Setup firewall dasar: `ufw allow 22,80,443,7777,9999,2087/tcp` + `ufw enable`.
    - 22 = SSH
    - 80 = HTTP (UCP website)
    - 443 = HTTPS (nanti setelah domain)
    - 7777 = SA-MP server
    - 9999 = SA-MP server (query port / secondary)
    - 2087 = Pterodactyl Panel (atau 443 jika pakai domain)

## 2. MySQL 8.0 Setup (Host)

- [ ] 2.1 Install MySQL 8.0: `apt install mysql-server -y`.
- [ ] 2.2 Jalankan `mysql_secure_installation` — set root password kuat, remove anonymous users, disable remote root, remove test DB.
- [ ] 2.3 Edit `/etc/mysql/mysql.conf.d/mysqld.cnf`:
    - Set `bind-address = 0.0.0.0` (agar bisa diakses dari Docker container).
    - Set `innodb_buffer_pool_size = 256M` (hemat RAM).
    - Set `max_connections = 50` (Alpha scale).
- [ ] 2.4 Restart MySQL: `systemctl restart mysql`.
- [ ] 2.5 Buat database dan user untuk Pterodactyl Panel:
    ```sql
    CREATE DATABASE panel;
    CREATE USER 'pterodactyl'@'localhost' IDENTIFIED BY '<strong_password>';
    GRANT ALL PRIVILEGES ON panel.* TO 'pterodactyl'@'localhost';
    ```
- [ ] 2.6 Buat database dan user untuk PAHLAWAN game/web/bot:
    ```sql
    CREATE DATABASE arivena;
    CREATE USER 'pahlawan'@'%' IDENTIFIED BY '<strong_password>';
    GRANT ALL PRIVILEGES ON arivena.* TO 'pahlawan'@'%';
    FLUSH PRIVILEGES;
    ```
- [ ] 2.7 Import schema awal dari `DATABASE/phrp.sql` (jika tersedia): `mysql arivena < /path/to/phrp.sql`.
- [ ] 2.8 Test koneksi dari host: `mysql -u pahlawan -p arivena` — harus berhasil.

## 3. Pterodactyl Panel Installation

- [ ] 3.1 Install prerequisites:
    ```bash
    apt install -y php8.1 php8.1-{common,cli,gd,mysql,mbstring,bcmath,xml,fpm,curl,zip} \
        php8.1-intl php8.1-sqlite3 php8.1-tokenizer \
        curl tar unzip git composer nginx redis-server
    ```
- [ ] 3.2 Download Pterodactyl Panel:
    ```bash
    mkdir -p /var/www/pterodactyl
    cd /var/www/pterodactyl
    curl -Lo panel.tar.gz https://github.com/pterodactyl/panel/releases/latest/download/panel.tar.gz
    tar -xzvf panel.tar.gz
    chmod -R 755 storage/* bootstrap/cache/
    ```
- [ ] 3.3 Setup Composer dependencies:
    ```bash
    cp .env.example .env
    composer install --no-dev --optimize-autoloader
    php artisan key:generate --force
    ```
- [ ] 3.4 Jalankan installer interaktif:
    ```bash
    php artisan p:environment:setup
    # App URL: http://<VPS_IP>:8080 (atau domain jika ada)
    # Timezone: Asia/Jakarta
    
    php artisan p:environment:database
    # Host: localhost, Port: 3306, DB: panel, User: pterodactyl
    
    php artisan p:environment:mail
    # Pilih SMTP (atau log driver untuk Alpha)
    
    php artisan migrate --seed --force
    ```
- [ ] 3.5 Buat admin user:
    ```bash
    php artisan p:user:make
    # Email, username, name, password
    ```
- [ ] 3.6 Set permissions:
    ```bash
    chown -R www-data:www-data /var/www/pterodactyl/*
    ```
- [ ] 3.7 Setup queue worker systemd service:
    ```bash
    # Buat /etc/systemd/system/pteroq.service
    # User=www-data, ExecStart=php /var/www/pterodactyl/artisan queue:work --queue=high,standard,low --sleep=3 --tries=3
    systemctl enable --now pteroq
    ```
- [ ] 3.8 Setup cron job:
    ```bash
    # crontab -e (untuk www-data)
    * * * * * php /var/www/pterodactyl/artisan schedule:run >> /dev/null 2>&1
    ```
- [ ] 3.9 Configure Nginx reverse proxy untuk Pterodactyl Panel di port 8080:
    ```nginx
    # /etc/nginx/sites-available/pterodactyl.conf
    server {
        listen 8080;
        server_name _;
        root /var/www/pterodactyl/public;
        index index.php;
        # ... standard Laravel Nginx config
    }
    ```
    `ln -s /etc/nginx/sites-available/pterodactyl.conf /etc/nginx/sites-enabled/`
    `nginx -t && systemctl reload nginx`
- [ ] 3.10 Buka `http://<VPS_IP>:8080` di browser — Pterodactyl login page harus muncul.

## 4. Wings (Pterodactyl Node) Installation

- [ ] 4.1 Install Docker:
    ```bash
    curl -sSL https://get.docker.com/ | CHANNEL=stable bash
    systemctl enable --now docker
    ```
- [ ] 4.2 Download Wings binary:
    ```bash
    mkdir -p /etc/pterodactyl
    curl -L -o /usr/local/bin/wings "https://github.com/pterodactyl/wings/releases/latest/download/wings_linux_amd64"
    chmod u+x /usr/local/bin/wings
    ```
- [ ] 4.3 Di Pterodactyl Panel UI:
    - Masuk ke **Admin → Locations** → buat location "VPS-EU".
    - Masuk ke **Admin → Nodes** → **Create New**.
    - Isi: Name, Location, FQDN (`<VPS_IP>`), Scheme (HTTP), Behind Proxy (No), Total Memory (3584 MB — sisakan untuk OS+Panel), Total Disk (45000 MB — sisakan untuk OS).
    - Klik **Create Node** → copy **Configuration** (YAML).
- [ ] 4.4 Paste konfigurasi ke `/etc/pterodactyl/config.yml` di VPS.
- [ ] 4.5 Setup Wings systemd service:
    ```bash
    # Buat /etc/systemd/system/wings.service
    # ExecStart=/usr/local/bin/wings
    systemctl enable --now wings
    ```
- [ ] 4.6 Di Panel, cek node status harus berubah jadi hijau (connected).

## 5. Custom Pterodactyl Eggs

### 5.1 SA-MP Server Egg

- [ ] 5.1.1 Buat Docker image untuk SA-MP server:
    - Base: `ubuntu:22.04` atau `debian:bookworm-slim`.
    - Install: `libmariadb-dev`, `libssl-dev`, runtime dependencies.
    - Copy SA-MP server binaries (`samp03svr`/`samp-server.exe`, plugins, `server.cfg` template).
    - Entry script: jalankan `./samp03svr` (atau open.mp equivalent).
- [ ] 5.1.2 Buat egg definition JSON (`egg-samp-server.json`):
    - Docker image: custom SA-MP image di atas.
    - Startup command: `./samp03svr` atau open.mp server binary.
    - Variables: `SERVER_PORT` (default 7777), `MAX_PLAYERS` (default 50), `MAP_NAME`, `GAME_MODE` (main).
    - File directory: mount ke repo `GAMEMODE/`.
- [ ] 5.1.3 Import egg ke Pterodactyl Panel: **Admin → Nests → Import Egg**.
- [ ] 5.1.4 Buat server di Panel: pilih egg SA-MP, assign memory 512MB, disk 5GB.

### 5.2 UCP Website Egg

- [ ] 5.2.1 Buat Docker image untuk UCP website:
    - Base: `nginx:1.25-alpine` + PHP-FPM 8.2.
    - Install: `php82-php-fpm`, `php82-php-mysql`, `php82-php-mbstring`, `php82-php-curl`, `php82-php-json`, Node.js 20 (untuk Vite build), Composer.
    - Entry script: build Vite frontend (`npm install && npm run build`), start PHP-FPM, start Nginx.
    - Nginx config: serve `WEBSITE/dist` sebagai static, proxy `WEBSITE/public/api` ke PHP-FPM.
- [ ] 5.2.2 Buat egg definition JSON (`egg-ucp-website.json`):
    - Docker image: custom UCP image.
    - Startup command: `/start.sh` (build + nginx + php-fpm).
    - Variables: `APP_URL`, `DB_HOST` (172.17.0.1), `DB_PORT` (3306), `DB_NAME` (arivena), `DB_USER` (pahlawan), `DB_PASS`.
    - Port: 80 (HTTP).
- [ ] 5.2.3 Import egg ke Pterodactyl Panel.
- [ ] 5.2.4 Buat server di Panel: pilih egg UCP, assign memory 512MB, disk 5GB, port 80.

### 5.3 Discord Bot Egg

- [ ] 5.3.1 Buat Docker image untuk Discord bot:
    - Base: `node:20-bookworm-slim`.
    - Install: runtime dependencies.
    - Entry script: `npm install --production && node index.js`.
- [ ] 5.3.2 Buat egg definition JSON (`egg-discord-bot.json`):
    - Docker image: custom bot image.
    - Startup command: `npm install --production && node index.js`.
    - Variables: `DB_HOST` (172.17.0.1), `DB_PORT` (3306), `DB_NAME` (arivena), `DB_USER` (pahlawan), `DB_PASS`.
    - No external port needed (bot connects outbound to Discord gateway).
- [ ] 5.3.3 Import egg ke Pterodactyl Panel.
- [ ] 5.3.4 Buat server di Panel: pilih egg bot, assign memory 384MB, disk 2GB.

## 6. Repository Deploy ke VPS

- [ ] 6.1 SSH ke VPS, buat deploy key atau personal access token untuk git clone.
- [ ] 6.2 Clone repo:
    ```bash
    mkdir -p /opt/pahlawan-roleplay
    cd /opt/pahlawan-roleplay
    git clone <repo_url> .
    ```
- [ ] 6.3 Setup environment files:
    - `WEBSITE/.env` — isi dengan DB_HOST=172.17.0.1, DB_NAME=arivena, dll.
    - `BOT/config.json` — isi dengan Discord token, guild ID, channel IDs.
    - `BOT/PHRP-AI/config/*.json` — isi dengan AI provider keys.
    - `GAMEMODE/server.cfg` — sesuaikan hostname, port, maxplayers, plugins, database connection.
- [ ] 6.4 Compile gamemode (jika perlu):
    ```bash
    # Install pawncc atau pakai pre-compiled .amx
    cd GAMEMODE
    ./pawno/pawncc gamemodes/main.pwn -o gamemodes/main.amx
    ```
- [ ] 6.5 Symlink atau copy repo ke Pterodactyl server directories:
    ```bash
    # Pterodactyl stores server files in /var/lib/pterodactyl/volumes/<server_id>
    # Symlink approach:
    ln -sf /opt/pahlawan-roleplay/GAMEMODE /var/lib/pterodactyl/volumes/<samp_server_id>/
    ln -sf /opt/pahlawan-roleplay/WEBSITE /var/lib/pterodactyl/volumes/<ucp_server_id>/
    ln -sf /opt/pahlawan-roleplay/BOT /var/lib/pterodactyl/volumes/<bot_server_id>/
    ```
- [ ] 6.6 Pastikan permission benar: `chown -R 988:988 /opt/pahlawan-roleplay` (UID Pterodactyl container user).

## 7. Service Startup dan Smoke Test

- [ ] 7.1 Start MySQL: `systemctl status mysql` — harus active.
- [ ] 7.2 Start SA-MP server dari Pterodactyl Panel → cek console output:
    - "Loaded logfix" atau plugin output normal.
    - "Server is starting..." dan bind ke port 7777.
    - Tidak ada "Error" atau "Fatal" di log.
- [ ] 7.3 Start UCP website dari Pterodactyl Panel → cek:
    - `npm run build` selesai tanpa error.
    - PHP-FPM dan Nginx start.
    - `curl http://localhost` dari dalam container return 200.
- [ ] 7.4 Start Discord bot dari Pterodactyl Panel → cek:
    - `npm install` selesai.
    - "Client ready" atau equivalent di console.
    - Bot online di Discord guild.
- [ ] 7.5 Smoke test end-to-end:
    - Buka `http://<VPS_IP>` di browser → UCP website muncul.
    - Connect SA-MP client ke `<VPS_IP>:7777` → server list muncul.
    - Bot merespons `/help` atau command dasar di Discord.
- [ ] 7.6 Test stop/restart dari Panel untuk ketiga service — harus smooth.

## 8. Dokumentasi Operasional

- [ ] 8.1 Buat `docs/VPS_SETUP_GUIDE.md` berisi semua langkah di atas sebagai referensi operator.
- [ ] 8.2 Buat `docs/PTERODACTYL_OPERATIONS.md` berisi:
    - Cara start/stop/restart tiap service.
    - Cara deploy update (git pull + restart).
    - Cara cek log dari Panel.
    - Troubleshooting umum (OOM, MySQL connection refused, Docker issues).
- [ ] 8.3 Catat semua credentials di tempat aman (bukan di repo):
    - VPS SSH key/password.
    - Pterodactyl admin login.
    - MySQL root dan pahlawan user password.
    - Discord bot token.
    - Environment variable values.
