# PAHLAWAN ROLEPLAY — VPS + Pterodactyl Infrastructure Setup Guide

> **Change:** `vps-pterodactyl-infrastructure` (OpenSpec)
> **Phase:** Alpha (ROADMAP Pre-Alpha → Alpha Test)
> **Deadline:** 31 Juli 2026 (setup selesai sebelum Alpha Test **1 Agustus 2026**)
> **Pemilik guide:** Operator yang akan melakukan deploy
> **Cara pakai:** Ikuti langkah dari atas ke bawah. Setiap bagian menulis `[Task X.Y]` yang merujuk ke task di `tasks.md` OpenSpec ini. Centang task di `tasks.md` setelah langkah selesai diverifikasi.
>
> **Dokumen terkait di repo ini:**
> - `docs/VPS_PROVIDER_GUIDE.md` — detail pilihan VPS provider + harga + decision matrix.
> - `docs/DOMAIN_PROVIDER_GUIDE.md` — detail beli domain, DNS setup, dan SSL.
> - `docs/SMTP_PROVIDER_GUIDE.md` — detail pilih/beli SMTP provider dan setup email Panel/UCP.
> - `docs/scripts/bootstrap-vps.sh` — script pra-install (cek OS, generate password awal).
> - `docs/eggs/egg-samp-server.json` — egg SA-MP siap import (install-on-creation).
> - `docs/eggs/egg-ucp-website.json` — egg UCP siap import.
> - `docs/eggs/egg-discord-bot.json` — egg Bot siap import.
> - `docs/PTERODACTYL_OPERATIONS.md` — operasional harian (start/stop/restart/deploy).
>
> **Dokumen OpenSpec 1-1 dengan guide ini:**
> - `openspec/changes/vps-pterodactyl-infrastructure/proposal.md`
> - `openspec/changes/vps-pterodactyl-infrastructure/design.md`
> - `openspec/changes/vps-pterodactyl-infrastructure/tasks.md`
> - `openspec/changes/vps-pterodactyl-infrastructure/specs/vps-pterodactyl-infrastructure/spec.md`

---

## Daftar Isi

- [Cara Pakai Guide Ini (Wajib Dibaca Kalau Masih Awam)](#cara-pakai-guide-ini-wajib-dibaca-kalau-masih-awam)
0. [Sebelum Mulai — Yang Perlu Disiapkan](#0-sebelum-mulai--yang-perlu-disiapkan)
1. [Beli Domain](#1-beli-domain)
2. [Beli VPS](#2-beli-vps)
3. [Hardening Host OS](#3-hardening-host-os) `[Task 1.6 – 1.10]`
4. [Setup MySQL 8.0 di Host](#4-setup-mysql-80-di-host) `[Task 2.1 – 2.8]`
5. [Setup Email (SMTP) untuk Panel + UCP](#5-setup-email-smtp-untuk-panel--ucp)
6. [Setup Pterodactyl Panel](#6-setup-pterodactyl-panel) `[Task 3.1 – 3.10]`
7. [Setup Wings (Node Agent)](#7-setup-wings-node-agent) `[Task 4.1 – 4.6]`
8. [Setup Domain, DNS, dan Reverse Proxy Nginx](#8-setup-domain-dns-dan-reverse-proxy-nginx)
9. [Setup SSL / Let's Encrypt](#9-setup-ssl--lets-encrypt)
10. [Setup Repository / Upload Project ke VPS](#10-setup-repository--upload-project-ke-vps) `[Task 6.1 – 6.6]`
11. [Setup 3 Custom Pterodactyl Eggs](#11-setup-3-custom-pterodactyl-eggs) `[Task 5.1.1 – 5.3.4]`
12. [Environment Variable per Service](#12-environment-variable-per-service)
13. [Smoke Test End-to-End](#13-smoke-test-end-to-end) `[Task 7.1 – 7.6]`
14. [Troubleshooting Umum](#14-troubleshooting-umum)
15. [Checklist Sebelum Go-Live Alpha](#15-checklist-sebelum-go-live-alpha)

---

## Cara Pakai Guide Ini (Wajib Dibaca Kalau Masih Awam)

Guide ini panjang karena dibuat sebagai **runbook dari nol sampai jalan**. Cara paling aman memakainya:

1. **Jangan lompat-lompat.** Ikuti urutan dari bagian 0 sampai 15.
2. **Satu command block = satu langkah.** Copy command, paste ke terminal, tunggu selesai, baru lanjut.
3. **Kalau ada placeholder seperti `<VPS_IP>` atau `<DOMAIN>`**, ganti dengan nilai asli Anda dan **hapus tanda `<` `>`**.
   - Contoh salah: `ssh root@<123.123.123.123>`
   - Contoh benar: `ssh root@123.123.123.123`
4. **Kalau command diawali `sudo`**, artinya command butuh akses admin/root di VPS.
5. **Kalau ada kata “opsional”**, boleh dilewati untuk Alpha, tapi baca dulu risikonya.
6. **Setiap selesai satu bagian besar**, cek bagian “Expected result”. Kalau hasilnya beda, jangan lanjut dulu — perbaiki di bagian troubleshooting.
7. **Jangan simpan password/token di repo.** Simpan di password manager (Bitwarden/1Password/KeePass).

### Simbol yang Dipakai

| Simbol | Artinya |
|---|---|
| `<VPS_IP>` | IP publik VPS, contoh `123.123.123.123` |
| `<domain>` | Domain Anda, contoh `pahlawan-roleplay.id` |
| `<GAME_DB_PASSWORD>` | Password database game/UCP/bot |
| `<PANEL_DB_PASSWORD>` | Password database Pterodactyl panel |
| `<BREVO_SMTP_KEY>` | SMTP key dari Brevo/SMTP provider |
| `<YOUR_PUBLIC_IP>` | IP internet rumah/kantor Anda untuk allowlist SSH |

### Glossary Singkat

| Istilah | Penjelasan pemula |
|---|---|
| **VPS** | Komputer server sewaan di internet. Semua service akan jalan di sini. |
| **Pterodactyl Panel** | Dashboard web untuk start/stop/restart server game, web UCP, dan bot. |
| **Wings** | Agent Pterodactyl di VPS yang menjalankan container Docker. |
| **Docker container** | “Kotak” isolasi untuk menjalankan service agar tidak saling ganggu. |
| **Egg** | Template Pterodactyl untuk jenis server tertentu (SA-MP, UCP, Bot). |
| **UFW** | Firewall simpel di Ubuntu. Dipakai untuk membuka/menutup port. |
| **MySQL bind-address** | Pengaturan alamat yang boleh didengar MySQL. Tetap harus dilindungi firewall. |
| **SMTP** | Server pengirim email untuk OTP, reset password, dan notifikasi. |
| **DNS** | Pengarah domain/subdomain ke IP VPS. |
| **Cloudflare Proxy** | Proteksi dan reverse proxy untuk HTTP/HTTPS. Tidak boleh dipakai untuk SA-MP port. |

### Stop Point yang Aman

Kalau Anda capek atau mau berhenti sementara, berhentilah di salah satu titik ini:

- Setelah VPS bisa SSH pakai user `pahlawan`.
- Setelah firewall dan Fail2Ban aktif.
- Setelah MySQL bisa login dari host.
- Setelah Pterodactyl Panel bisa dibuka.
- Setelah Wings node hijau.
- Setelah masing-masing service berhasil start sekali.

Jangan berhenti di tengah-tengah edit file config atau setelah firewall diubah tapi belum dites.

---

## 0. Sebelum Mulai — Yang Perlu Disiapkan

Siapkan hal-hal berikut **sebelum** masuk VPS, supaya alur kerja tidak terputus:

| Item | Keterangan | Sumber |
|---|---|---|
| **Kartu kredit / debit / e-wallet** | Untuk bayar domain dan VPS | — |
| **Email baru khusus infra** (mis. `infra@pahlawan-roleplay.id`) | Untuk notifikasi VPS, domain registrar, panel admin, SMTP | Gmail / Zoho Mail / domain-email |
| **Akun GitHub** dengan akses ke repo PAHLAWAN ROLEPLAY | Untuk clone & pull | Sudah ada (sesuai `AGENTS.md`) |
| **Akun Cloudflare** (gratis) | Untuk DNS + proxy + cache (opsional tapi direkomendasikan) | https://dash.cloudflare.com/sign-up |
| **Akun SMTP provider** | Lihat bagian 5 | Lihat bagian 5 |
| **Password manager** (Bitwarden / 1Password / KeePass) | Untuk simpan semua kredensial | — |
| **Client SSH** di laptop lokal | Windows: built-in OpenSSH di PowerShell / Windows Terminal. macOS / Linux: sudah ada. | — |
| **SFTP client** (opsional) | WinSCP / FileZilla / VS Code Remote-SSH | — |

**Prinsip keamanan:**
- **Jangan** catat password / token di file `.md` atau di Git.
- Semua kredensial disimpan di password manager (1Password / Bitwarden).
- Dokumentasi ini hanya menulis **placeholder** seperti `<PASSWORD>`, `<DOMAIN>`, dst.

---

## 1. Beli Domain

> **Dokumen lengkap:** lihat [`docs/DOMAIN_PROVIDER_GUIDE.md`](../../../docs/DOMAIN_PROVIDER_GUIDE.md) untuk perbandingan registrar, harga IDR/USD, dan setup DNS detail.

### 1.1. Pilih Registrar

Rekomendasi (dari yang paling umum untuk gamer Indonesia):

| Registrar | Alasan | Biaya / tahun (≈) |
|---|---|---|
| **Cloudflare Registrar** | Hargaat-cost (tanpa mark-up), WHOIS privacy gratis, DNS cepat. | Sesuai TLD (sering paling murah) |
| **Niagahoster** (ID) | IDR, dukungan Bahasa Indonesia, .id/.my/.com/.my.id. | Rp 100k – 250k |
| **Namecheap** | UI bersih, WHOIS privacy gratis untuk banyak TLD. | USD 9 – 13 |
| **Porkbun** | Murah untuk TLD populer, UI simpel. | USD 5 – 12 |

**Rekomendasi utama: Cloudflare** — harga paling transparan, integrasi DNS sekali klik.

### 1.2. Pilih Nama Domain

Saran nama untuk PAHLAWAN ROLEPLAY (sesuaikan):

- **Top-level:** `pahlawan-roleplay.id` (Indonesia, perlu KTP/KITAS), `pahlawanroleplay.com`, `pahlawanrp.com`, `pahlawancrp.my.id` (sub-domain `my.id` gratis untuk warga negara Indonesia).
- **Subdomain** yang akan dipakai:

  | Subdomain | Tujuan |
  |---|---|
  | `panel.<domain>` | Pterodactyl Panel |
  | `ucp.<domain>` (atau root) | UCP Website |
  | `samp.<domain>` (atau A record) | SA-MP server (IP publik tetap utama) |
  | `api.<domain>` | API UCP (opsional) |

### 1.3. Langkah Beli Domain (contoh Cloudflare)

1. Buka https://www.cloudflare.com/products/registrar/ → klik **Register a domain**.
2. Cari nama domain yang tersedia.
3. Tambahkan ke keranjang, bayar 1 tahun (perpanjang otomatis/non-aktif, rekomendasi: **non-aktif auto-renew** agar kontrol manual).
4. Setelah bayar, masuk ke **Cloudflare Dashboard → Account → Registrar → Domains** → klik domain → copy **nameservers** yang diberikan (mis. `anderson.ns.cloudflare.com`, `mary.ns.cloudflare.com`).
5. Simpan nameserver di password manager.

> **Catatan:** Jika beli di registrar lain (Niagahoster, Namecheap), setelah beli:
> - Masuk ke panel domain → **Nameservers** → ganti ke nameserver Cloudflare (jika ingin pakai Cloudflare DNS).
> - Atau langsung pakai DNS default registrar dan lewati Cloudflare.

---

## 2. Beli VPS

> **Dokumen lengkap:** lihat [`docs/VPS_PROVIDER_GUIDE.md`](../../../docs/VPS_PROVIDER_GUIDE.md) untuk **decision matrix per provider**, harga realistis (Hetzner €14.40/bln untuk spek persis, Vultr SG $24/bln, dll), dan langkah order detail per provider. Dokumen ini hanya merangkum.

### 2.1. Spesifikasi Minimum `[Task 1.1]`

| Komponen | Minimum | Ideal | Alasan |
|---|---|---|---|
| **CPU** | 2 vCPU | 2 vCPU AMD Ryzen 9 7900 | SA-MP single-threaded, butuh high single-core. Ryzen 9 7900 single-core lebih kencang dari Xeon lama. |
| **RAM** | 4 GB DDR5 | 4 GB DDR5 (atau 8 GB) | Cukup untuk Alpha (5-10 players). 8 GB untuk Beta/RC. |
| **Storage** | 50 GB NVMe | 80 GB NVMe | SA-MP image ~200MB + UCP image ~150MB + Node image ~300MB + logs + DB. |
| **Network** | 1 Gbit/s shared | 10 Gbit/s shared | SA-MP heartbeat sensitif ke packet loss. 10 Gbit/s memberi headroom. |
| **IPv4** | 1 dedicated | 1 dedicated | SA-MP butuh IPv4 publik (IPv6 belum didukung client SA-MP standar). |

### 2.2. OS `[Task 1.2]`

- **Ubuntu 22.04 LTS** (64-bit) — `Ubuntu 22.04 x86_64`.
- Pterodactyl official support untuk Ubuntu 20.04 / 22.04.
- LTS = security update sampai April 2027.

### 2.3. Region `[Task 1.3]`

| Prioritas | Region | Latency ke Indonesia | Alasan |
|---|---|---|---|
| **#1 (default)** | **Singapore (SG)** | 30 – 50 ms | Routing terdekat, default peering ke provider ID. |
| **#2 (fallback)** | **Frankfurt / Amsterdam** | 200 – 250 ms | Lebih mudah dapat spek Ryzen 9 7900 + 10 Gbit/s. Masih playable untuk roleplay, sedikit lag untuk chat intensif. |
| **#3 (fallback terakhir)** | **Tokyo / Hong Kong** | 70 – 100 ms | Alternatif Asia, beberapa provider punya spek setara. |

### 2.4. Pilih Provider

Rekomendasi praktis untuk kondisi sekarang:

| Provider | Kapan dipilih | Catatan pemula |
|---|---|---|
| **VibeGames vServer** | Jika prioritas keamanan game server dan ingin Anti-DDoS bawaan | Kandidat utama Anda. Pastikan paket punya Anti DDoS Protection, Ubuntu 22.04, IPv4 dedicated, minimal 2 vCPU/4GB/50GB. |
| **Vultr Singapore** | Jika prioritas latency ke Indonesia | UI ramah pemula dan region Singapore. DDoS biasanya add-on. |
| **Hetzner CPX11** | Jika prioritas harga murah + spek kuat | Latency Eropa ke Indonesia lebih tinggi, tapi budget bagus. |
| **Linode Singapore** | Jika ingin CPU dedicated dan latency SG | Lebih premium. |
| **Contabo SG** | Jika ingin murah dengan spek besar | CPU shared dan reputasi IP kadang kurang bagus untuk email. |

**Rekomendasi utama untuk Anda saat ini: VibeGames vServer**, karena sudah ada Anti-DDoS Protection. Setelah order, tetap ikuti bagian **3.6 Advanced Firewall & DDoS Hardening** — Anti-DDoS provider dan firewall VPS harus saling melengkapi.

> **Catatan kontainer vs KVM:** Pilih **KVM / VPS biasa**, bukan container LXC / OpenVZ. Pterodactyl Wings butuh Docker, dan Docker paling aman/stabil di VPS KVM.

### 2.5. Langkah Order

1. Buka website provider → **Sign Up** → verifikasi email.
2. Pilih region (Singapore).
3. Pilih plan: sesuai spek 2 vCPU / 4 GB / 50 GB+ NVMe.
4. Pilih OS: **Ubuntu 22.04 LTS x64**.
5. (Opsional) Aktifkan **automatic backups** ($1-2/bulan extra) — opsional, backup manual via `mysqldump` cukup untuk Alpha.
6. Masukkan hostname: mis. `pahlawan-vps-01.pahlawan-roleplay.id` (atau `srv1.pahlawan-roleplay.id`).
7. Pilih **SSH Key** (lihat 2.6) atau set **root password** otomatis.
8. Bayar dan klik **Deploy**.
9. Catat **IP address** `[Task 1.5]` — disimpan di password manager.

### 2.6. Generate SSH Key di Laptop Lokal `[Task 1.8]`

Sebelum konek ke VPS, generate SSH key pair di laptop:

**Windows (PowerShell):**
```powershell
ssh-keygen -t ed25519 -C "guyub@pahlawan-roleplay" -f $HOME\.ssh\pahlawan_vps
type $HOME\.ssh\pahlawan_vps.pub
```

**macOS / Linux:**
```bash
ssh-keygen -t ed25519 -C "guyub@pahlawan-roleplay" -f ~/.ssh/pahlawan_vps
cat ~/.ssh/pahlawan_vps.pub
```

- Output dari `cat ...pub` = **public key** (yang di-paste ke VPS).
- File `pahlawan_vps` (tanpa `.pub`) = **private key** (JANGAN dishare, simpan aman).

Saat order VPS, jika provider mendukung inject SSH key, paste public key di field tersebut. Jika tidak, akan di-paste manual setelah login pertama (lihat 3.3).

### 2.7. Login Pertama `[Task 1.4, 1.5]`

```bash
ssh root@<VPS_IP>
```

- Masukkan root password (atau otomatis pakai key).
- Provider akan tampil **MOTD** / welcome — itu artinya VPS sudah provisioned.

---

## 3. Hardening Host OS

### 3.1. Update Sistem `[Task 1.9]`

```bash
apt update && apt upgrade -y
apt install -y ufw fail2ban unattended-upgrades apt-listchanges rsync curl wget nano
```

Aktifkan auto security update:

```bash
dpkg-reconfigure -plow unattended-upgrades
# Pilih "Yes"
```

### 3.2. Set Timezone

```bash
timedatectl set-timezone Asia/Jakarta
timedatectl status
```

### 3.3. Buat User Non-Root + SSH Key `[Task 1.7, 1.8]`

```bash
# Buat user 'pahlawan' dengan home dir
adduser pahlawan
# Masukkan password kuat (disimpan di password manager)

# Tambahkan ke group sudo
usermod -aG sudo pahlawan

# Setup SSH key untuk user pahlawan
mkdir -p /home/pahlawan/.ssh
chmod 700 /home/pahlawan/.ssh

# Paste public key (dari laptop lokal)
nano /home/pahlawan/.ssh/authorized_keys
# Paste isi file pahlawan_vps.pub
chmod 600 /home/pahlawan/.ssh/authorized_keys
chown -R pahlawan:pahlawan /home/pahlawan/.ssh
```

### 3.4. Disable Password Login + Root Login `[Task 1.8]`

```bash
sudo cp /etc/ssh/sshd_config /etc/ssh/sshd_config.bak
sudo nano /etc/ssh/sshd_config
```

Cari dan set:

```
PermitRootLogin no
PasswordAuthentication no
PubkeyAuthentication yes
ChallengeResponseAuthentication no
UsePAM yes
X11Forwarding no
AllowUsers pahlawan
```

Test config & restart SSH:

```bash
sudo sshd -t
sudo systemctl restart sshd
```

**PENTING:** Buka terminal baru, login pakai SSH key:

```bash
ssh pahlawan@<VPS_IP>
```

Jangan tutup sesi SSH lama sampai sesi baru sukses login.

### 3.5. Setup Firewall (UFW) `[Task 1.10]`

```bash
sudo ufw default deny incoming
sudo ufw default allow outgoing

sudo ufw allow 22/tcp    comment "SSH"
sudo ufw allow 80/tcp    comment "HTTP (UCP website)"
sudo ufw allow 443/tcp   comment "HTTPS (UCP + Panel setelah domain)"
sudo ufw allow 7777/tcp  comment "SA-MP Server TCP"
sudo ufw allow 7777/udp  comment "SA-MP Server UDP"
sudo ufw allow 9999/tcp  comment "SA-MP Query / Secondary TCP (optional)"
sudo ufw allow 9999/udp  comment "SA-MP Query / Secondary UDP (optional)"
sudo ufw allow 8080/tcp  comment "Pterodactyl Panel HTTP (pre-domain)"
sudo ufw allow 8443/tcp  comment "Pterodactyl Panel HTTPS (jika pakai self-signed)"

sudo ufw enable
sudo ufw status verbose
```

**Expected result:** `sudo ufw status verbose` menampilkan `Status: active` dan rule untuk `22`, `80`, `443`, `7777/tcp`, `7777/udp`. Kalau SSH tiba-tiba putus, login ulang dari terminal baru. Jangan tutup terminal lama sebelum login baru berhasil.

> **Catatan Pterodactyl Panel:**
> - **Sebelum domain:** panel di `http://<VPS_IP>:8080` — buka port 8080.
> - **Setelah domain + Nginx reverse proxy:** panel di `https://panel.<domain>` lewat port 443. Tutup 8080.
> - **Wings daemon:** pakai Docker internal network (port 8080 di container, host listen di port allocation range `8080-8090`). Buka range di UFW:
>   ```bash
>   sudo ufw allow 8080:8090/tcp comment "Pterodactyl server allocations"
>   ```

### 3.6. Advanced Firewall & DDoS Hardening (Direkomendasikan untuk VibeGames)

> VibeGames vServer sudah menyediakan **Anti DDoS Protection**, tetapi firewall host tetap wajib. Provider-level Anti-DDoS membantu menyaring flood besar sebelum masuk VPS; firewall host membantu membatasi service yang benar-benar boleh diakses, rate-limit koneksi, dan mengurangi efek scan/bruteforce.
>
> **Mode pemula:** Jalankan dulu bagian 3.5 UFW + 3.7 Fail2Ban. Bagian 3.6 ini bisa dijalankan setelah Anda sudah yakin SSH tidak putus dan Panel berjalan. Jika ragu, kerjakan 3.6.1–3.6.4 dulu; 3.6.5 iptables rate-limit boleh ditunda sampai server mulai public.

#### 3.6.1. Prinsip Port Exposure

| Port | Public? | Catatan |
|---|---:|---|
| `22/tcp` | Ya, tapi dibatasi | SSH key-only; jika sudah punya IP rumah/kantor statis, batasi hanya IP tersebut. |
| `80/tcp` | Ya | Redirect HTTP → HTTPS untuk web/panel. |
| `443/tcp` | Ya | HTTPS untuk panel/UCP. |
| `7777/tcp+udp` | Ya | SA-MP/open.mp game port. |
| `9999/tcp+udp` | Opsional | Query/secondary; buka hanya jika gamemode memang butuh. |
| `3306/tcp` | Tidak public | MySQL hanya host + Docker bridge; jangan expose internet. |
| `8080/tcp` | Sementara | Hanya sebelum domain/SSL; tutup setelah panel pakai `https://panel.<domain>`. |
| `8080-8090/tcp` | Opsional | Pterodactyl allocation range; buka hanya range yang benar-benar dipakai. |

#### 3.6.2. Batasi SSH ke IP Tertentu (Jika Memungkinkan)

Jika IP internet operator stabil, ganti rule SSH public dengan allowlist:

```bash
# Cek IP publik laptop/operator
curl -4 ifconfig.me

# Hapus rule SSH public lama jika ada
sudo ufw delete allow 22/tcp || true

# Allow SSH hanya dari IP operator
sudo ufw allow from <YOUR_PUBLIC_IP>/32 to any port 22 proto tcp comment "SSH admin only"
sudo ufw status numbered
```

Jika IP operator dinamis, tetap buka 22/tcp tetapi gunakan:
- SSH key-only.
- `PermitRootLogin no`.
- Fail2Ban.
- Password panjang untuk user sudo.

#### 3.6.3. Jangan Expose MySQL ke Internet

Walaupun `bind-address = 0.0.0.0` diperlukan agar Docker container bisa akses MySQL host, firewall harus membatasi port 3306 hanya dari Docker bridge:

```bash
# Pastikan tidak ada allow 3306 public
sudo ufw delete allow 3306/tcp || true

# Allow dari Docker default bridge subnet saja
sudo ufw allow from 172.17.0.0/16 to any port 3306 proto tcp comment "MySQL from Docker bridge only"

# Optional jika Docker network custom digunakan, cek subnet:
docker network inspect bridge | grep Subnet
```

#### 3.6.4. Rate-Limit SSH dan Web Burst

```bash
# UFW built-in rate limit untuk SSH
sudo ufw limit 22/tcp comment "Rate-limit SSH"

# Kernel sysctl hardening dasar
sudo tee /etc/sysctl.d/99-pahlawan-network-hardening.conf >/dev/null <<'EOF'
# Basic network hardening for VPS game server
net.ipv4.tcp_syncookies = 1
net.ipv4.tcp_max_syn_backlog = 4096
net.ipv4.tcp_synack_retries = 3
net.ipv4.tcp_syn_retries = 3
net.ipv4.icmp_echo_ignore_broadcasts = 1
net.ipv4.icmp_ignore_bogus_error_responses = 1
net.ipv4.conf.all.rp_filter = 1
net.ipv4.conf.default.rp_filter = 1
net.ipv4.conf.all.accept_redirects = 0
net.ipv4.conf.default.accept_redirects = 0
net.ipv4.conf.all.send_redirects = 0
net.ipv4.conf.default.send_redirects = 0
net.ipv4.conf.all.accept_source_route = 0
net.ipv4.conf.default.accept_source_route = 0
EOF
sudo sysctl --system
```

#### 3.6.5. iptables Rate-Limit untuk SA-MP/open.mp Port

> **Catatan:** Rule ini mitigasi query/connection spam kecil-menengah. Flood besar tetap harus ditangani Anti-DDoS provider. Jangan terlalu agresif karena bisa memutus player legit.

```bash
# Allow established traffic
sudo iptables -A INPUT -m conntrack --ctstate ESTABLISHED,RELATED -j ACCEPT

# Drop invalid packets
sudo iptables -A INPUT -m conntrack --ctstate INVALID -j DROP

# Rate-limit new TCP connection ke SA-MP port 7777 per IP
sudo iptables -A INPUT -p tcp --dport 7777 -m conntrack --ctstate NEW \
  -m recent --set --name SAMP_TCP --rsource
sudo iptables -A INPUT -p tcp --dport 7777 -m conntrack --ctstate NEW \
  -m recent --update --seconds 10 --hitcount 20 --name SAMP_TCP --rsource \
  -j DROP

# Rate-limit UDP burst ke SA-MP port 7777
sudo iptables -A INPUT -p udp --dport 7777 -m hashlimit \
  --hashlimit-name SAMP_UDP --hashlimit-above 60/second --hashlimit-burst 120 \
  --hashlimit-mode srcip --hashlimit-srcmask 32 -j DROP

# Simpan iptables agar survive reboot
sudo apt install -y iptables-persistent
sudo netfilter-persistent save
```

Rollback jika rule terlalu agresif:

```bash
sudo iptables -D INPUT -p tcp --dport 7777 -m conntrack --ctstate NEW -m recent --set --name SAMP_TCP --rsource || true
sudo iptables -D INPUT -p tcp --dport 7777 -m conntrack --ctstate NEW -m recent --update --seconds 10 --hitcount 20 --name SAMP_TCP --rsource -j DROP || true
sudo iptables -D INPUT -p udp --dport 7777 -m hashlimit --hashlimit-name SAMP_UDP --hashlimit-above 60/second --hashlimit-burst 120 --hashlimit-mode srcip --hashlimit-srcmask 32 -j DROP || true
sudo netfilter-persistent save
```

#### 3.6.6. Nginx Rate Limit untuk Panel/UCP

Tambahkan di `/etc/nginx/nginx.conf` dalam block `http { ... }`:

```nginx
limit_req_zone $binary_remote_addr zone=login_limit:10m rate=5r/s;
limit_req_zone $binary_remote_addr zone=api_limit:10m rate=20r/s;
limit_conn_zone $binary_remote_addr zone=conn_limit:10m;
```

Lalu di server block panel/UCP:

```nginx
# Limit koneksi per IP
limit_conn conn_limit 30;

# General API limit
location /api/ {
    limit_req zone=api_limit burst=40 nodelay;
    try_files $uri $uri/ /index.php?$query_string;
}

# Login/auth endpoint lebih ketat (sesuaikan path aktual UCP)
location ~* /(login|register|otp|auth) {
    limit_req zone=login_limit burst=10 nodelay;
    try_files $uri $uri/ /index.php?$query_string;
}
```

Test dan reload:

```bash
sudo nginx -t
sudo systemctl reload nginx
```

#### 3.6.7. Monitoring Saat Diserang

```bash
# Koneksi aktif terbanyak per IP
sudo ss -tun state established | awk '{print $5}' | cut -d: -f1 | sort | uniq -c | sort -nr | head

# UDP/TCP listen
sudo ss -tulpen

# Log UFW
sudo tail -f /var/log/ufw.log

# Docker stats
sudo docker stats

# Nginx top IP
sudo awk '{print $1}' /var/log/nginx/access.log | sort | uniq -c | sort -nr | head
```

Jika ada IP abusive kecil-menengah:

```bash
sudo ufw deny from <ABUSIVE_IP> comment "temporary block abusive IP"
```

Untuk flood besar, buka ticket ke VibeGames dan minta mereka cek/aktifkan mitigation profile untuk game UDP/TCP port `7777`.

### 3.7. Fail2Ban (Anti-Brute-Force)

```bash
sudo systemctl enable --now fail2ban
sudo nano /etc/fail2ban/jail.local
```

Isi:

```ini
[DEFAULT]
bantime = 3600
findtime = 600
maxretry = 5

[sshd]
enabled = true
port = 22
filter = sshd
logpath = /var/log/auth.log
```

```bash
sudo systemctl restart fail2ban
sudo fail2ban-client status sshd
```

### 3.8. Reboot Test

```bash
sudo reboot
```

Tunggu 30 detik, lalu SSH lagi:

```bash
ssh pahlawan@<VPS_IP>
```

Konfirmasi:

```bash
whoami        # pahlawan
sudo whoami   # root (sudo OK)
df -h         # storage OK
free -h       # RAM OK
```

### 3.9. Pra-install Helper (Opsional)

Sebelum lanjut, opsional jalankan helper pre-flight dari `docs/scripts/bootstrap-vps.sh`:

```bash
scp C:/Users/guyub/Documents/PAHLAWAN\ ROLEPLAY/docs/scripts/bootstrap-vps.sh \
    pahlawan@<VPS_IP>:~/

ssh pahlawan@<VPS_IP>
chmod +x bootstrap-vps.sh
sudo ./bootstrap-vps.sh            # generate password awal + folder /opt
sudo ./bootstrap-vps.sh --dry-run  # lihat apa yang akan dijalankan tanpa eksekusi
```

> **Catatan:** Script ini hanya pra-install (cek OS Ubuntu 22.04, generate random password DB ke `/opt/pahlawan-roleplay/.secrets-bootstrap` mode 600). Lanjutkan manual sesuai langkah di bawah untuk instalasi MySQL/Panel/Wings/etc.

---

## 4. Setup MySQL 8.0 di Host

### 4.1. Install MySQL `[Task 2.1]`

```bash
sudo apt install mysql-server -y
```

### 4.2. Secure Installation `[Task 2.2]`

```bash
sudo mysql_secure_installation
```

Jawaban:

```
- Validate password component? Y
- Password validation policy: STRONG (2)
- Set root password: <set ROOT_MYSQL_PASSWORD kuat>
- Remove anonymous users? Y
- Disallow root login remotely? Y
- Remove test database? Y
- Reload privilege tables? Y
```

Simpan `<ROOT_MYSQL_PASSWORD>` di password manager.

### 4.3. Konfigurasi Network + Resource `[Task 2.3]`

```bash
sudo nano /etc/mysql/mysql.conf.d/mysqld.cnf
```

Cari `[mysqld]` section, tambahkan / ubah:

```ini
[mysqld]
bind-address = 0.0.0.0
mysqlx-bind-address = 0.0.0.0
innodb_buffer_pool_size = 256M
max_connections = 50
table_open_cache = 2000
sort_buffer_size = 2M
join_buffer_size = 2M
thread_cache_size = 8
query_cache_size = 0
query_cache_type = 0
character-set-server = utf8mb4
collation-server = utf8mb4_unicode_ci
default-authentication-plugin = mysql_native_password
```

Restart:

```bash
sudo systemctl restart mysql
sudo systemctl status mysql
```

### 4.4. Buat Database Panel `[Task 2.5]`

```bash
sudo mysql -u root -p
```

```sql
CREATE DATABASE panel CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
CREATE USER 'pterodactyl'@'localhost' IDENTIFIED BY '<PANEL_DB_PASSWORD>';
GRANT ALL PRIVILEGES ON panel.* TO 'pterodactyl'@'localhost';
FLUSH PRIVILEGES;
EXIT;
```

### 4.5. Buat Database PAHLAWAN `[Task 2.6]`

Login sebagai root lagi:

```bash
sudo mysql -u root -p
```

```sql
CREATE DATABASE arivena CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
CREATE USER 'pahlawan'@'localhost' IDENTIFIED BY '<GAME_DB_PASSWORD>';
CREATE USER 'pahlawan'@'%' IDENTIFIED BY '<GAME_DB_PASSWORD>';
GRANT ALL PRIVILEGES ON arivena.* TO 'pahlawan'@'localhost';
GRANT ALL PRIVILEGES ON arivena.* TO 'pahlawan'@'%';
FLUSH PRIVILEGES;
EXIT;
```

> **Catatan keamanan:** User `pahlawan@'%'` butuh akses dari Docker container (IP `172.17.0.1` = host). Untuk production yang lebih ketat, ganti `'%'` jadi `'172.17.0.%'` (subnet Docker bridge), tapi Alpha setup pakai `'%'` cukup.

### 4.6. Import Schema Awal `[Task 2.7]`

```bash
# Upload file .sql dari lokal ke VPS (gunakan scp)
# Dari laptop lokal:
scp C:/Users/guyub/Documents/PAHLAWAN\ ROLEPLAY/DATABASE/phrp.sql pahlawan@<VPS_IP>:/tmp/phrp.sql

# Di VPS:
ls -lh /tmp/phrp.sql

# Import (jika schema tersedia)
sudo mysql -u root -p arivena < /tmp/phrp.sql
sudo mysql -u root -p -e "USE arivena; SHOW TABLES;"
```

> **Catatan:** Folder `DATABASE/` repo lokal berisi dump privat. Jika dump belum ada di repo, lewati langkah ini. Schema akan dibuat otomatis oleh SA-MP server saat start (plugin MySQL create-on-start) atau via migration manual.

### 4.7. Test Koneksi `[Task 2.8]`

```bash
mysql -u pahlawan -p arivena
# Masukkan <GAME_DB_PASSWORD>
# SHOW TABLES;
# EXIT;
```

Test dari container (siapkan untuk bagian 11):

```bash
docker run --rm -it mysql:8.0 mysql -h 172.17.0.1 -u pahlawan -p<PANEL_DB_PASSWORD> arivena -e "SELECT 1;"
```

---

## 5. Setup Email (SMTP) untuk Panel + UCP

> **Dokumen lengkap:** lihat [`docs/SMTP_PROVIDER_GUIDE.md`](../../../docs/SMTP_PROVIDER_GUIDE.md) untuk panduan memilih/membeli provider SMTP (Brevo, Zoho, Resend, Mailgun, Amazon SES), setup SPF/DKIM/DMARC, pembuatan SMTP key, dan test `swaks` dari VPS.

Pterodactyl dan UCP butuh SMTP untuk email verifikasi, reset password, notifikasi donasi, dll.

### 5.1. Pilih SMTP Provider

| Provider | Free Tier | Biaya Lanjutan | Alasan |
|---|---|---|---|
| **Zoho Mail** (personal) | 5 user gratis (jika pakai domain sendiri) | USD 1/user/bulan | Bagus untuk domain email, IMAP/SMTP gratis |
| **Brevo (ex-Sendinblue)** | 300 email/hari gratis | USD 9/bulan | Cocok untuk volume tinggi |
| **Mailgun** | 100 email/hari gratis | USD 0.80 / 1k email | Developer-friendly, API jelas |
| **Resend** | 100 email/hari, 3000/bulan | USD 20/bulan | Modern API, free tier ok |
| **Amazon SES** | 62,000 email/bulan (jika di EC2) | USD 0.10 / 1k | Sangat murah untuk volume tinggi |
| **Gmail SMTP** | 500 email/hari | Gratis | Untuk testing, TIDAK untuk production. Sering di-rate-limit. |

**Rekomendasi utama:**
- **Untuk infra `panel@<domain>`** → **Zoho Mail** (free, branded email).
- **Untuk UCP verifikasi & notifikasi volume** → **Brevo** atau **Resend**.

### 5.2. Setup Email di Domain Sendiri (contoh Zoho)

1. Beli / setup domain (bagian 1).
2. Buka https://www.zoho.com/mail/ → Sign Up → pilih **Free Plan** untuk personal.
3. Add domain Anda → verify ownership (TXT record di Cloudflare DNS).
4. Zoho akan minta setup **MX records** (lihat di dashboard mereka) — tambahkan di Cloudflare.
5. Buat akun: `infra@<domain>` (untuk Pterodactyl) dan `noreply@<domain>` (untuk UCP).
6. Catat SMTP credentials:
   - Host: `smtp.zoho.com`
   - Port: `465` (SSL) atau `587` (STARTTLS)
   - User: `infra@<domain>`
   - Password: app-specific password (generate di Zoho dashboard → Security → App Passwords).

### 5.3. Setup SPF, DKIM, DMARC (Reputasi Email)

Tambahkan TXT record di Cloudflare DNS:

| Type | Name | Value |
|---|---|---|
| TXT | `@` | `v=spf1 include:zoho.com ~all` |
| TXT | `zmail._domainkey` | (DKIM value dari Zoho dashboard) |
| TXT | `_dmarc` | `v=DMARC1; p=quarantine; rua=mailto:dmarc@<domain>` |

Test di https://mxtoolbox.com/spf.aspx dan https://mxtoolbox.com/dkim.aspx setelah propagasi.

### 5.4. Test SMTP dari VPS

```bash
sudo apt install -y swaks
swaks --to you@gmail.com \
      --from infra@<domain> \
      --server smtp.zoho.com \
      --port 587 \
      --auth LOGIN \
      --auth-user infra@<domain> \
      --auth-password <ZohoAppPassword> \
      --tls
```

Cek inbox Gmail — kalau email masuk, SMTP siap dipakai di Pterodactyl.

### 5.5. Simpan untuk Nanti

Catat di password manager (JANGAN di file):

```
SMTP Panel:
  MAIL_HOST=smtp.zoho.com
  MAIL_PORT=587
  MAIL_USERNAME=infra@pahlawan-roleplay.id
  MAIL_PASSWORD=<app-password>
  MAIL_ENCRYPTION=tls
  MAIL_FROM_ADDRESS=infra@pahlawan-roleplay.id
  MAIL_FROM_NAME="PAHLAWAN ROLEPLAY Panel"
```

---

## 6. Setup Pterodactyl Panel

### 6.1. Install Prerequisites `[Task 3.1]`

Pterodactyl butuh PHP 8.1 + extension, Redis, Composer, Nginx.

```bash
# Add PHP 8.1 repo (Ubuntu 22.04 default = PHP 8.1)
sudo apt install -y software-properties-common
sudo add-apt-repository -y ppa:ondrej/php
sudo apt update

# Install PHP 8.1 + extensions
sudo apt install -y \
    php8.1 php8.1-cli php8.1-gd php8.1-mysql php8.1-mbstring \
    php8.1-bcmath php8.1-xml php8.1-fpm php8.1-curl php8.1-zip \
    php8.1-intl php8.1-sqlite3 php8.1-tokenizer

# Tools lain
sudo apt install -y curl tar unzip git composer nginx redis-server

# Verifikasi
php -v
composer --version
nginx -v
redis-server --version
```

### 6.2. Download Panel `[Task 3.2]`

```bash
sudo mkdir -p /var/www/pterodactyl
cd /var/www/pterodactyl
sudo curl -Lo panel.tar.gz https://github.com/pterodactyl/panel/releases/latest/download/panel.tar.gz
sudo tar -xzvf panel.tar.gz
sudo rm panel.tar.gz
sudo chmod -R 755 storage/* bootstrap/cache/
```

### 6.3. Composer Install `[Task 3.3]`

```bash
sudo cp .env.example .env
sudo composer install --no-dev --optimize-autoloader
sudo php artisan key:generate --force
```

### 6.4. Konfigurasi Environment `[Task 3.4]`

#### App URL & Timezone

```bash
sudo php artisan p:environment:setup
```

Jawaban:

```
APP_URL: http://<VPS_IP>:8080   (nanti diganti https://panel.<domain>)
APP_TIMEZONE: Asia/Jakarta
CACHE_DRIVER: redis
SESSION_DRIVER: redis
QUEUE_CONNECTION: redis
```

#### Database

```bash
sudo php artisan p:environment:database
```

Jawaban:

```
Host: 127.0.0.1
Port: 3306
Database: panel
Username: pterodactyl
Password: <PANEL_DB_PASSWORD>
```

#### Mail (SMTP)

```bash
sudo php artisan p:environment:mail
```

Jawaban:

```
Driver: smtp
Host: smtp.zoho.com
Port: 587
Username: infra@<domain>
Password: <ZohoAppPassword>
Encryption: tls
From Address: infra@<domain>
From Name: PAHLAWAN ROLEPLAY Panel
```

### 6.5. Migrate Database + Seed

```bash
sudo php artisan migrate --seed --force
```

### 6.6. Buat Admin User `[Task 3.5]`

```bash
sudo php artisan p:user:make
```

Jawaban:

```
Email: admin@<domain>   (atau email Anda)
Username: admin
Name: Admin Pahlawan
Password: <PANEL_ADMIN_PASSWORD>
```

### 6.7. Set Ownership `[Task 3.6]`

```bash
sudo chown -R www-data:www-data /var/www/pterodactyl/*
```

### 6.8. Setup Queue Worker `[Task 3.7]`

```bash
sudo nano /etc/systemd/system/pteroq.service
```

Isi:

```ini
[Unit]
Description=Pterodactyl Queue Worker
After=redis-server.service

[Service]
User=www-data
Group=www-data
Restart=always
ExecStart=/usr/bin/php /var/www/pterodactyl/artisan queue:work --queue=high,standard,low --sleep=3 --tries=3 --max-time=3600

[Install]
WantedBy=multi-user.target
```

Aktifkan:

```bash
sudo systemctl enable --now pteroq
sudo systemctl status pteroq
```

### 6.9. Setup Cron `[Task 3.8]`

```bash
sudo crontab -u www-data -e
# Tambah baris:
* * * * * php /var/www/pterodactyl/artisan schedule:run >> /dev/null 2>&1
```

### 6.10. Nginx Reverse Proxy `[Task 3.9]`

```bash
sudo nano /etc/nginx/sites-available/pterodactyl.conf
```

Isi (port 8080, sementara sebelum ada domain):

```nginx
server {
    listen 8080;
    server_name _;

    root /var/www/pterodactyl/public;
    index index.php;

    access_log /var/log/nginx/pterodactyl.access.log;
    error_log /var/log/nginx/pterodactyl.error.log;

    client_max_body_size 100M;
    client_body_timeout 120s;
    sendfile off;

    location / {
        try_files $uri $uri/ /index.php?$query_string;
    }

    location ~ \.php$ {
        fastcgi_split_path_info ^(.+\.php)(/.+)$;
        fastcgi_pass unix:/run/php/php8.1-fpm.sock;
        fastcgi_index index.php;
        fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
        include fastcgi_params;
    }

    location ~ /\.ht {
        deny all;
    }
}
```

Hapus default site, aktifkan pterodactyl:

```bash
sudo rm /etc/nginx/sites-enabled/default
sudo ln -s /etc/nginx/sites-available/pterodactyl.conf /etc/nginx/sites-enabled/

# Tambah www-data ke Nginx group (untuk access socket PHP-FPM)
sudo usermod -aG www-data www-data

sudo nginx -t
sudo systemctl restart nginx
sudo systemctl status nginx
```

### 6.11. Verifikasi Panel `[Task 3.10]`

Buka browser di laptop:

```
http://<VPS_IP>:8080
```

Harus muncul **Pterodactyl Panel login page**. Login pakai admin yang dibuat di 6.6.

---

## 7. Setup Wings (Node Agent)

### 7.1. Install Docker `[Task 4.1]`

```bash
curl -sSL https://get.docker.com/ | CHANNEL=stable sudo bash
sudo systemctl enable --now docker
docker --version
```

Tambah user `pahlawan` ke group docker (opsional, untuk debug):

```bash
sudo usermod -aG docker pahlawan
# Logout-login ulang biar efek
```

### 7.2. Download Wings Binary `[Task 4.2]`

```bash
sudo mkdir -p /etc/pterodactyl
sudo curl -L -o /usr/local/bin/wings \
    "https://github.com/pterodactyl/wings/releases/latest/download/wings_linux_amd64"
sudo chmod u+x /usr/local/bin/wings

# Test
wings --version
```

### 7.3. Buat Location & Node di Panel UI `[Task 4.3]`

1. Login ke Pterodactyl Panel `http://<VPS_IP>:8080`.
2. Klik ikon **Settings (gear)** → **Locations** → **Create New**:
   - Short code: `VPS-SG` (atau `VPS-EU`)
   - Description: `PAHLAWAN VPS Singapore`
3. Klik **Nodes** → **Create New**:

| Field | Value |
|---|---|
| Name | `pahlawan-node-01` |
| Location | `VPS-SG` |
| FQDN | `<VPS_IP>` (nanti diganti hostname domain) |
| Scheme | `http` (nanti `https` setelah SSL) |
| Behind Proxy | `No` |
| Total Memory | `3584` MB (sisa 4096 - 512 untuk OS + Panel) |
| Total Disk | `45000` MB (sisa 50000 - 5000 untuk OS) |
| Daemon Server File Directory | `/var/lib/pterodactyl/volumes` |
| Daemon SFTP File Directory | `/var/lib/pterodactyl/.sftp` |
| Daemon Port | `8080` (default) |

4. Klik **Create Node**.
5. Klik tab **Configuration** → salin YAML ke clipboard.

### 7.4. Paste Config & Setup Wings Service `[Task 4.4, 4.5]`

Di VPS:

```bash
sudo nano /etc/pterodactyl/config.yml
# Paste YAML dari panel, save & exit
```

Setup systemd service:

```bash
sudo nano /etc/systemd/system/wings.service
```

Isi:

```ini
[Unit]
Description=Pterodactyl Wings Daemon
After=docker.service
Requires=docker.service
PartOf=docker.service

[Service]
User=root
WorkingDirectory=/etc/pterodactyl
LimitNOFILE=4096
PIDFile=/var/run/wings/pid
ExecStart=/usr/local/bin/wings
Restart=on-failure
StartLimitInterval=180
StartLimitBurst=30
RestartSec=5s

[Install]
WantedBy=multi-user.target
```

Aktifkan:

```bash
sudo mkdir -p /var/run/wings
sudo systemctl enable --now wings
sudo systemctl status wings
```

### 7.5. Verifikasi Node `[Task 4.6]`

Di Panel UI → **Nodes** → `pahlawan-node-01` → cek indikator **heartbeat** harus hijau (connected).

Cek juga di VPS:

```bash
sudo systemctl status wings
sudo docker ps   # harus kosong (belum ada container server)
```

---

## 8. Setup Domain, DNS, dan Reverse Proxy Nginx

### 8.1. Setup DNS Record di Cloudflare

Login ke Cloudflare Dashboard → klik domain → **DNS** → **Records**:

| Type | Name | Content | Proxy | TTL |
|---|---|---|---|---|
| A | `@` | `<VPS_IP>` | Proxied (orange cloud) | Auto |
| A | `panel` | `<VPS_IP>` | Proxied | Auto |
| A | `ucp` | `<VPS_IP>` | Proxied | Auto |
| A | `api` | `<VPS_IP>` | Proxied | Auto |

> **Catatan SA-MP:** Client SA-MP tidak support Cloudflare proxy (perlu direct IP). Untuk record samp, gunakan **A record DNS-only (gray cloud)**:
> | A | `samp` | `<VPS_IP>` | **DNS only** | Auto |
>
> Player connect ke `samp.pahlawan-roleplay.id:7777`.

Propagasi DNS butuh 1-5 menit. Test:

```bash
nslookup panel.pahlawan-roleplay.id
nslookup samp.pahlawan-roleplay.id
```

### 8.2. Update Pterodactyl FQDN ke Domain

Di Panel UI → **Nodes** → `pahlawan-node-01` → **Settings**:
- FQDN: ganti dari `<VPS_IP>` ke `panel.pahlawan-roleplay.id`
- Scheme: ubah ke `https`
- Save → restart wings di VPS:

```bash
sudo systemctl restart wings
```

### 8.3. Update APP_URL di `.env` Panel

```bash
sudo nano /var/www/pterodactyl/.env
# Cari APP_URL=http://<VPS_IP>:8080
# Ganti jadi APP_URL=https://panel.pahlawan-roleplay.id

cd /var/www/pterodactyl
sudo php artisan config:clear
sudo php artisan cache:clear
```

### 8.4. Nginx Server Block untuk Panel (HTTPS via Cloudflare)

Karena pakai Cloudflare proxy, sertifikat SSL dari Cloudflare terminate di edge. Backend Nginx cukup dengar HTTP di localhost.

```bash
sudo nano /etc/nginx/sites-available/pterodactyl.conf
```

Ganti jadi:

```nginx
# Panel Pterodactyl - via Cloudflare proxy
server {
    listen 80;
    server_name panel.pahlawan-roleplay.id;

    # Hanya terima request dari Cloudflare IPs (opsional tapi direkomendasikan)
    # allow 173.245.48.0/20;
    # allow 103.21.244.0/22;
    # ... (full Cloudflare IPs di https://www.cloudflare.com/ips/)
    # deny all;

    root /var/www/pterodactyl/public;
    index index.php;

    access_log /var/log/nginx/pterodactyl.access.log;
    error_log /var/log/nginx/pterodactyl.error.log;

    client_max_body_size 100M;
    client_body_timeout 120s;
    sendfile off;

    location / {
        try_files $uri $uri/ /index.php?$query_string;
    }

    location ~ \.php$ {
        fastcgi_split_path_info ^(.+\.php)(/.+)$;
        fastcgi_pass unix:/run/php/php8.1-fpm.sock;
        fastcgi_index index.php;
        fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
        include fastcgi_params;
    }

    location ~ /\.ht {
        deny all;
    }
}
```

Restart:

```bash
sudo nginx -t
sudo systemctl reload nginx
```

### 8.5. Tutup Port 8080 di UFW (Sekarang Pakai 80/443 via Domain)

```bash
sudo ufw delete allow 8080/tcp
sudo ufw status
```

---

## 9. Setup SSL / Let's Encrypt

### 9.1. Pilih Mode SSL

| Mode | Cocok untuk | Trade-off |
|---|---|---|
| **Cloudflare Origin Certificate** | VPS di belakang Cloudflare proxy | TLS ke Cloudflare edge (free). Tidak end-to-end ke user, tapi untuk SA-MP/UCP cukup. |
| **Let's Encrypt via Certbot** | VPS publik, tidak pakai Cloudflare proxy | TLS end-to-end, tapi SA-MP tetap IP only. |
| **Cloudflare Full (Strict) + Origin Cert** | Rekomendasi untuk setup ini | TLS user → Cloudflare edge (universal cert Cloudflare). TLS Cloudflare → VPS pakai Origin Cert (paling aman + free). |

**Rekomendasi: pakai Cloudflare Origin Certificate** — paling simpel untuk setup di belakang Cloudflare.

### 9.2. Generate Cloudflare Origin Certificate

1. Cloudflare Dashboard → klik domain → **SSL/TLS** → **Origin Server** → **Create Certificate**.
2. Pilih:
   - Private key type: **RSA (2048)**
   - Hostnames: `*.pahlawan-roleplay.id` dan `pahlawan-roleplay.id` (atau domain spesifik: `panel.pahlawan-roleplay.id`, `ucp.pahlawan-roleplay.id`).
   - Certificate validity: **15 years** (Cloudflare max).
3. Klik **Create** → copy **Certificate (PEM)** dan **Private Key**.

### 9.3. Simpan Cert di VPS

```bash
sudo mkdir -p /etc/nginx/ssl
sudo nano /etc/nginx/ssl/pahlawan-roleplay.id.pem
# Paste Origin Certificate (PEM)

sudo nano /etc/nginx/ssl/pahlawan-roleplay.id.key
# Paste Private Key

sudo chmod 600 /etc/nginx/ssl/pahlawan-roleplay.id.key
sudo chmod 644 /etc/nginx/ssl/pahlawan-roleplay.id.pem
```

### 9.4. Set Cloudflare SSL Mode

Dashboard Cloudflare → domain → **SSL/TLS** → **Overview** → pilih **Full (Strict)**.

### 9.5. Nginx HTTPS Server Block

```bash
sudo nano /etc/nginx/sites-available/pterodactyl.conf
```

Replace dengan:

```nginx
# Panel Pterodactyl
server {
    listen 80;
    server_name panel.pahlawan-roleplay.id;
    return 301 https://$host$request_uri;
}

server {
    listen 443 ssl http2;
    server_name panel.pahlawan-roleplay.id;

    ssl_certificate /etc/nginx/ssl/pahlawan-roleplay.id.pem;
    ssl_certificate_key /etc/nginx/ssl/pahlawan-roleplay.id.key;
    ssl_protocols TLSv1.2 TLSv1.3;
    ssl_ciphers HIGH:!aNULL:!MD5;
    ssl_prefer_server_ciphers on;
    ssl_session_cache shared:SSL:10m;
    ssl_session_timeout 10m;

    root /var/www/pterodactyl/public;
    index index.php;

    access_log /var/log/nginx/pterodactyl.access.log;
    error_log /var/log/nginx/pterodactyl.error.log;

    client_max_body_size 100M;
    client_body_timeout 120s;
    sendfile off;

    location / {
        try_files $uri $uri/ /index.php?$query_string;
    }

    location ~ \.php$ {
        fastcgi_split_path_info ^(.+\.php)(/.+)$;
        fastcgi_pass unix:/run/php/php8.1-fpm.sock;
        fastcgi_index index.php;
        fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
        include fastcgi_params;
    }

    location ~ /\.ht {
        deny all;
    }
}
```

```bash
sudo nginx -t
sudo systemctl reload nginx
```

### 9.6. Verifikasi

- Buka `https://panel.pahlawan-roleplay.id` → harus redirect dari HTTP ke HTTPS, tampil **Pterodactyl Panel**.
- Test SSL di https://www.ssllabs.com/ssltest/ → rating A atau A+.

---

## 10. Setup Repository / Upload Project ke VPS

Bagian ini menjawab pertanyaan paling penting: **bagaimana cara memindahkan folder project PAHLAWAN ROLEPLAY dari laptop ke VPS lalu dipakai oleh Pterodactyl**.

Target akhir bagian ini:

```txt
/opt/pahlawan-roleplay/
├── GAMEMODE/
├── WEBSITE/
├── BOT/
├── DATABASE/
├── docs/
├── openspec/
└── ...file repo lain
```

Setelah folder ini ada di VPS, file service akan di-copy/sync ke volume Pterodactyl:

```txt
/var/lib/pterodactyl/volumes/<samp_server_id>/  <- isi GAMEMODE/
/var/lib/pterodactyl/volumes/<ucp_server_id>/   <- isi WEBSITE/
/var/lib/pterodactyl/volumes/<bot_server_id>/   <- isi BOT/
```

### 10.0. Pilih Metode Upload Project

| Metode | Cocok Untuk | Kelebihan | Kekurangan |
|---|---|---|---|
| **Metode A — Git clone** | Repo sudah ada di GitHub dan akses deploy key siap | Paling rapi untuk update jangka panjang (`git pull`) | Butuh setup deploy key GitHub |
| **Metode B — rsync dari laptop** | Mau upload folder lokal langsung dan punya Git Bash/WSL/Linux/macOS | Bisa exclude file besar/rahasia, update berikutnya cepat | Windows native PowerShell tidak selalu punya rsync |
| **Metode C — tar/zip + scp** | Pemula Windows yang ingin cara paling jelas | Mudah dipahami: compress → upload → extract | Upload ulang bisa besar/lama |

**Rekomendasi untuk Anda:**

- Untuk setup pertama kalau masih awam: **Metode C (tar/zip + scp)**.
- Untuk update berikutnya: **Metode A (git pull)** kalau repo sudah private/aman, atau **Metode B (rsync)** kalau masih pakai folder lokal.

> **PENTING sebelum upload:** Jangan upload file rahasia/berat yang tidak dibutuhkan runtime, seperti `.git/`, `.hermes/`, `node_modules/`, log, cache, database dump private, dan token production. Daftar exclude ada di bawah.

### 10.0.1. Buat Folder Target di VPS

Jalankan di VPS:

```bash
ssh pahlawan@<VPS_IP>

sudo mkdir -p /opt/pahlawan-roleplay
sudo chown -R pahlawan:pahlawan /opt/pahlawan-roleplay
```

**Expected result:** folder `/opt/pahlawan-roleplay` ada dan user `pahlawan` bisa menulis ke folder itu.

---

### 10.0.2. Metode A — Git Clone dari GitHub (Paling Rapi untuk Update)

Gunakan metode ini kalau repo sudah ada di GitHub dan deploy key sudah di-setup.

### 10.1. Generate Deploy Key `[Task 6.1]`

SSH ke VPS sebagai `pahlawan`, generate key khusus untuk git:

```bash
ssh pahlawan@<VPS_IP>

ssh-keygen -t ed25519 -C "pahlawan-vps-deploy@pahlawan-roleplay" \
    -f ~/.ssh/pahlawan_github_deploy
cat ~/.ssh/pahlawan_github_deploy.pub
```

**Tambahkan public key ke GitHub:**
1. Login GitHub → repo PAHLAWAN ROLEPLAY → **Settings** → **Deploy keys** → **Add deploy key**.
2. Title: `pahlawan-vps-deploy`
3. Key: paste output `cat ...pub`.
4. Allow write access: **YES** (kalau mau push dari VPS; NO kalau read-only).
5. **Add key**.

Tambahkan ke SSH agent:

```bash
nano ~/.ssh/config
```

Isi:

```
Host github.com
    HostName github.com
    User git
    IdentityFile ~/.ssh/pahlawan_github_deploy
    IdentitiesOnly yes
```

```bash
chmod 600 ~/.ssh/config
ssh -T git@github.com
# Harus muncul: "Hi PAHLAWAN-ROLEPLAY! You've successfully authenticated..."
```

### 10.2. Clone Repo `[Task 6.2]`

```bash
sudo mkdir -p /opt/pahlawan-roleplay
sudo chown pahlawan:pahlawan /opt/pahlawan-roleplay
cd /opt/pahlawan-roleplay

# Ganti URL dengan repo PAHLAWAN ROLEPLAY asli
git clone git@github.com:<ORG_OR_USER>/<REPO_NAME>.git .

# Verifikasi
ls -la
# Harus ada: AGENTS.md, GAMEMODE/, WEBSITE/, BOT/, DATABASE/, tools/, openspec/
```

### 10.2.1. Metode B — Upload Folder Lokal Pakai rsync

Gunakan metode ini jika laptop Anda punya **Git Bash**, **WSL**, **Linux**, atau **macOS**.

Jalankan dari laptop lokal (bukan dari VPS):

```bash
cd "C:/Users/guyub/Documents/PAHLAWAN ROLEPLAY"

rsync -avz --delete \
  --exclude ".git/" \
  --exclude ".hermes/" \
  --exclude "node_modules/" \
  --exclude "WEBSITE/node_modules/" \
  --exclude "WEBSITE/dist/" \
  --exclude "BOT/node_modules/" \
  --exclude "BOT/.cache/" \
  --exclude "GAMEMODE/logs/" \
  --exclude "*.log" \
  --exclude "*.tmp" \
  --exclude "*.bak" \
  --exclude "DATABASE/*.sql" \
  ./ pahlawan@<VPS_IP>:/opt/pahlawan-roleplay/
```

**Penjelasan pemula:**

- `./` = isi folder project lokal yang sedang dibuka.
- `/opt/pahlawan-roleplay/` = folder tujuan di VPS.
- `--exclude` = file/folder yang tidak ikut upload.
- `--delete` = file di VPS yang sudah tidak ada di lokal akan dihapus juga. Ini bagus untuk sync, tapi pastikan path tujuan benar.

**Expected result:** command selesai tanpa error dan di VPS ada folder `GAMEMODE`, `WEBSITE`, `BOT`:

```bash
ssh pahlawan@<VPS_IP>
ls -la /opt/pahlawan-roleplay
```

---

### 10.2.2. Metode C — Upload Folder Lokal Pakai tar + scp (Paling Mudah untuk Pemula Windows)

Gunakan metode ini jika Anda ingin cara sederhana: compress folder → upload → extract.

#### Step 1 — Buat archive dari laptop lokal

Jalankan di **Git Bash / WSL / Linux / macOS** dari folder project:

```bash
cd "C:/Users/guyub/Documents/PAHLAWAN ROLEPLAY"

tar \
  --exclude='.git' \
  --exclude='.hermes' \
  --exclude='node_modules' \
  --exclude='WEBSITE/node_modules' \
  --exclude='WEBSITE/dist' \
  --exclude='BOT/node_modules' \
  --exclude='BOT/.cache' \
  --exclude='GAMEMODE/logs' \
  --exclude='*.log' \
  --exclude='*.tmp' \
  --exclude='*.bak' \
  --exclude='DATABASE/*.sql' \
  -czf pahlawan-roleplay-upload.tar.gz .
```

Jika memakai PowerShell dan tidak punya `tar` GNU, gunakan 7-Zip/WinRAR untuk membuat `.zip`, tetapi pastikan exclude folder berat/rahasia di atas.

#### Step 2 — Upload archive ke VPS

```bash
scp pahlawan-roleplay-upload.tar.gz pahlawan@<VPS_IP>:/tmp/
```

#### Step 3 — Extract di VPS

```bash
ssh pahlawan@<VPS_IP>

sudo mkdir -p /opt/pahlawan-roleplay
sudo chown -R pahlawan:pahlawan /opt/pahlawan-roleplay

tar -xzf /tmp/pahlawan-roleplay-upload.tar.gz -C /opt/pahlawan-roleplay
rm /tmp/pahlawan-roleplay-upload.tar.gz
```

#### Step 4 — Verifikasi struktur folder di VPS

```bash
ls -la /opt/pahlawan-roleplay

# Harus ada minimal:
ls -la /opt/pahlawan-roleplay/GAMEMODE
ls -la /opt/pahlawan-roleplay/WEBSITE
ls -la /opt/pahlawan-roleplay/BOT
```

**Expected result:** tiga folder service ada di VPS. Jika tidak ada, kemungkinan archive dibuat dari folder yang salah.

---

### 10.2.3. Metode D — Upload Manual via SFTP (Alternatif GUI)

Jika Anda lebih nyaman GUI:

1. Install **WinSCP** atau **FileZilla**.
2. Connect:
   - Host: `<VPS_IP>`
   - User: `pahlawan`
   - Auth: SSH key / password sementara
3. Buka folder remote: `/opt/pahlawan-roleplay/`.
4. Upload folder:
   - `GAMEMODE/`
   - `WEBSITE/`
   - `BOT/`
   - `docs/`
   - `openspec/`
   - file root penting seperti `README.md`, `ROADMAP.md`, `AGENTS.md`
5. Jangan upload:
   - `.git/`
   - `.hermes/`
   - `node_modules/`
   - log/cache
   - dump database private
   - token/password production

Metode GUI ini boleh untuk awal, tapi untuk update berikutnya lebih baik pakai `git pull` atau `rsync`.

---

### 10.3. Setup Environment Files `[Task 6.3]`

```bash
cd /opt/pahlawan-roleplay

# --- WEBSITE/.env ---
cp WEBSITE/.env.example WEBSITE/.env
nano WEBSITE/.env
```

Isi placeholder (sesuaikan dengan runtime production):

```env
# Database
DB_HOST=172.17.0.1
DB_PORT=3306
DB_NAME=arivena
DB_USER=pahlawan
DB_PASS=<GAME_DB_PASSWORD>

# App
APP_URL=https://ucp.pahlawan-roleplay.id
APP_ENV=production
APP_DEBUG=false
APP_KEY=<generate via: php artisan key:generate>

# Email / SMTP
MAIL_MAILER=smtp
MAIL_HOST=smtp.zoho.com
MAIL_PORT=587
MAIL_USERNAME=noreply@<domain>
MAIL_PASSWORD=<ZohoAppPassword>
MAIL_ENCRYPTION=tls
MAIL_FROM_ADDRESS=noreply@<domain>
MAIL_FROM_NAME="PAHLAWAN ROLEPLAY"

# Discord OAuth (jika dipakai)
DISCORD_CLIENT_ID=<client_id>
DISCORD_CLIENT_SECRET=<client_secret>
DISCORD_REDIRECT_URI=https://ucp.pahlawan-roleplay.id/auth/discord/callback

# AI Provider (PHRP-AI)
AI_PROVIDER=groq
AI_API_KEY=<provider_key>
```

```bash
# --- BOT/config.json ---
nano BOT/config.json
```

**Ganti** semua nilai yang perlu untuk production:
- `token`: token Discord bot (JANGAN tulis di sini, paste manual lalu hapus dari history).
- `clientId`, `guildId`: dari Discord Developer Portal.
- `server.ip`: ganti `127.0.0.1` jadi `samp.pahlawan-roleplay.id` (atau `<VPS_IP>`).
- `server.port`: `7777`.
- `database.host`: `172.17.0.1` (Docker host gateway).
- `database.password`: `<GAME_DB_PASSWORD>`.

> **PERHATIAN:** Repo GitHub TIDAK BOLEH berisi token / password sungguhan. `BOT/config.json` di repo saat ini berisi token asli — **segera rotate token Discord** di Discord Developer Portal setelah deploy, dan **gunakan env var atau secret manager** untuk production (lihat 12.3).

```bash
# --- BOT/PHRP-AI/config/*.json (jika ada) ---
nano BOT/PHRP-AI/config/*.json
# Isi API key AI provider
```

```bash
# --- GAMEMODE/server.cfg ---
nano GAMEMODE/server.cfg
```

Sesuaikan:

```
hostname PAHLAWAN ROLEPLAY [Alpha]
port 7777
maxplayers 50
lanmode 0
bind 0.0.0.0

# MySQL connection (kalau pakai plugin mysql)
mysql_host 172.17.0.1
mysql_port 3306
mysql_user pahlawan
mysql_password <GAME_DB_PASSWORD>
mysql_database arivena

# Plugins
plugins streamer.so sscanf.so mysql.so bcrypt.so
```

### 10.4. Compile Gamemode `[Task 6.4]`

```bash
cd /opt/pahlawan-roleplay/GAMEMODE

# Cek apakah ada binary pre-compiled
ls gamemodes/main.amx 2>/dev/null && echo "Already compiled" || echo "Need compile"

# Jika perlu compile, install pawncc
sudo apt install -y build-essential
# Pawn compiler biasanya di folder pawno/ atau di-include via Docker

# Cara 1: Pakai pawncc dari Docker image
docker run --rm -v "$PWD":/src -w /src ghcr.io/pawn-lang/pawncc:latest \
    pawncc gamemodes/main.pwn -o gamemodes/main.amx

# Cara 2: Pre-compiled .amx yang sudah ada di repo (lihat di git LFS atau releases)
# Copy dari release artifact ke gamemodes/main.amx
```

Verifikasi:

```bash
ls -lh gamemodes/main.amx
file gamemodes/main.amx
```

### 10.5. Copy/Sync File ke Pterodactyl Volumes `[Task 6.5, 6.6]`

Pterodactyl menyimpan file server di `/var/lib/pterodactyl/volumes/<server_id>/`. Untuk pemula, **pakai metode copy/sync**, bukan symlink, karena lebih mudah dipahami dan tidak mudah salah path.

Cari `<server_id>` di Panel UI:

1. Panel → Admin → Servers.
2. Klik server (SA-MP / UCP / Bot).
3. Lihat UUID/ID di URL atau tab Settings.
4. Cocokkan folder di VPS:
   ```bash
   sudo ls -lah /var/lib/pterodactyl/volumes/
   ```

Setelah ID ketemu, sync file:

```bash
# Ganti <samp_server_id>, <ucp_server_id>, <bot_server_id> dengan folder UUID yang benar.
# Perhatikan tanda slash / di akhir source: artinya isi folder yang dicopy, bukan folder induknya.

sudo rsync -a --delete /opt/pahlawan-roleplay/GAMEMODE/ \
  /var/lib/pterodactyl/volumes/<samp_server_id>/

sudo rsync -a --delete /opt/pahlawan-roleplay/WEBSITE/ \
  /var/lib/pterodactyl/volumes/<ucp_server_id>/

sudo rsync -a --delete /opt/pahlawan-roleplay/BOT/ \
  /var/lib/pterodactyl/volumes/<bot_server_id>/

# Permission container user Pterodactyl. Jika panel memakai user berbeda, cek docs Pterodactyl/Wings.
sudo chown -R 988:988 /var/lib/pterodactyl/volumes/<samp_server_id>/
sudo chown -R 988:988 /var/lib/pterodactyl/volumes/<ucp_server_id>/
sudo chown -R 988:988 /var/lib/pterodactyl/volumes/<bot_server_id>/
```

**Expected result:** setelah buka File Manager di Panel, file gamemode/website/bot terlihat langsung di root server masing-masing.

> **Update berikutnya:** setiap selesai `git pull` di `/opt/pahlawan-roleplay`, ulangi `rsync` hanya untuk service yang berubah, lalu restart service dari Panel.

---

## 11. Setup 3 Custom Pterodactyl Eggs

> **File canonical:** repo sudah berisi 3 egg JSON siap-import di `docs/eggs/`:
> - `docs/eggs/egg-samp-server.json`
> - `docs/eggs/egg-ucp-website.json`
> - `docs/eggs/egg-discord-bot.json`
>
> Ketiganya menggunakan **filosofi install-on-creation**: Pterodactyl run `installation script` (di dalam field `scripts.installation` JSON) sekali waktu server pertama kali dibuat. Script akan `apt install` dependencies, download SA-MP binaries / plugin dari GitHub release, dst. **Tidak perlu build custom Docker image** — pakai base image `ubuntu:22.04` atau `node:20-bookworm-slim` yang sudah ada di Docker Hub.
>
> Bagian ini menjelaskan dua hal: (a) kenapa filosofi install-on-creation lebih cocok untuk VPS 4GB, dan (b) cara pakai file `docs/eggs/*.json` plus tweak yang perlu Anda lakukan di Panel setelah import.

### 11.0. Kenapa Pakai Install-Script, Bukan Custom Docker Image

| Pendekatan | Trade-off |
|---|---|
| **Custom Docker image (image-baked)** — apa yang ditulis di versi pertama guide ini | Lebih reproducible, tapi butuh `docker build` di VPS + push ke registry. Makan RAM & disk untuk build. |
| **Install-on-creation script** ✅ (dipakai di `docs/eggs/`) | Pterodactyl run script sekali saat server pertama dibuat. Lebih simpel untuk VPS 4GB. Container image tetap base (`ubuntu:22.04`). |

### 11.0.1. Setup Docker Network (untuk akses Host MySQL)

Sebelum membuat eggs, pastikan container bisa akses MySQL host:

```bash
docker network ls
# Default 'bridge' network gateway = 172.17.0.1
docker network inspect bridge | grep Gateway
```

Saat membuat server di Panel, di tab **Network**, set:
- **Network Mode**: `bridge` (default)
- Tambahkan **aliases** atau gunakan `172.17.0.1` sebagai DB host di env var container.

### 11.1. SA-MP Server Egg `[Task 5.1.1 – 5.1.4]`

#### 11.1.1. Yang Dilakukan Install Script

Lihat field `scripts.installation` di `docs/eggs/egg-samp-server.json`. Script otomatis:

1. `apt install` dependencies: `wget`, `lib32gcc-s1`, `lib32stdc++6`, `lib32z1`, `unzip`, `mysql-client`.
2. Buat direktori `/mnt/server/{plugins,scriptfiles,pawno,pawno/include}`.
3. Download SA-MP server 0.3.7-R3 binaries.
4. Download plugin:
   - `streamer.so` v2.9.4 (samp-incognito)
   - `sscanf.so` v2.13.5 (Y-Less)
   - `bcrypt.so` v1.4.0 (Sreyas-Sreelal)
5. `chmod +x` binaries & plugins.
6. **Anda perlu tambahkan `mysql.so`** secara manual setelah install pertama (lihat 11.1.4).

#### 11.1.2. Variable yang Tersedia di Egg

| Variable | Default | Editable | Keterangan |
|---|---|---|---|
| `SERVER_NAME` | "PAHLAWAN ROLEPLAY \| Pre-Alpha" | Ya | Ditulis ke `server.cfg` via install script |
| `RCON_PASSWORD` | "ChangeMe123!" | Ya | **WAJIB diganti** sebelum production |
| `MYSQL_HOST` | "172.17.0.1" | Ya | Host MySQL |
| `MYSQL_PORT` | 3306 | Ya | Port MySQL |
| `MYSQL_DATABASE` | "pahlawan" | Ya | DB name (samakan dengan yg dibuat di MySQL) |
| `MYSQL_USER` | "pahlawan_app" | Ya | DB user |
| `MYSQL_PASSWORD` | "" | Ya (sensitive) | **WAJIB diisi** via Panel UI |
| `MAX_PLAYERS` | 50 | Ya | Max players |
| `GAMEMODE` | "pahlawan" | Ya | Nama file `.amx` tanpa extension |

#### 11.1.3. Import Egg & Buat Server

1. Login Panel `https://panel.pahlawan-roleplay.id`.
2. **Admin → Nests → Import Egg** → upload `docs/eggs/egg-samp-server.json`.
3. Pilih **Nest**: `SA-MP` (buat baru jika belum ada).
4. **Import**.
5. **Servers → Create New**:
   - Name: `PAHLAWAN SA-MP Server`
   - Owner: admin
   - Egg: `SA-MP Server`
   - Memory: **512 MB**
   - Disk: **5000 MB**
   - Port Allocation: Primary **7777 TCP+UDP**
6. Di tab **Startup**:
   - `RCON_PASSWORD` → ganti ke password kuat (jangan pakai default "ChangeMe123!")
   - `MYSQL_DATABASE` → `arivena` (samakan dengan step 4.5)
   - `MYSQL_USER` → `pahlawan`
   - `MYSQL_PASSWORD` → `<GAME_DB_PASSWORD>` dari step 4.5
7. **Save**. Server creation akan trigger **install script** (~2-5 menit, download binaries & plugins).
8. Cek tab **Console** → harus muncul log `[install] SA-MP server installed.`

#### 11.1.4. Tambahkan Plugin MySQL Manual (Setelah Install Pertama)

Egg canonical tidak otomatis download `mysql.so` (karena versi plugin MySQL R41+ kurang stabil untuk SA-MP). Install manual setelah server pertama start:

```bash
# SSH ke VPS, lalu exec ke container SA-MP
sudo docker ps | grep samp
sudo docker exec -it <samp_container> bash

# Di dalam container:
cd /home/container/plugins  # atau /mnt/server/plugins
wget -q https://github.com/pBlueG/SA-MP-MySQL/releases/download/R41-4/mysql-R41-linux.so -O mysql.so
chmod +x mysql.so
exit
```

Lalu edit `GAMEMODE/server.cfg` di repo untuk tambahkan `mysql` ke plugins line:

```
plugins streamer.so sscanf.so mysql.so bcrypt.so
```

Restart SA-MP dari Panel UI.

> **Alternatif:** Jika `mysql.so` R41+ bermasalah, pakai plugin `mysql-plugin-R5` dari pBlueG, atau ganti ke **open.mp** server (database connector built-in, no plugin needed). Lihat https://github.com/openmultiplayer/openmp-server.

---

### 11.2. UCP Website Egg `[Task 5.2.1 – 5.2.4]`

#### 11.2.1. Yang Dilakukan Install Script

Lihat `docs/eggs/egg-ucp-website.json`. Install script otomatis:

1. `apt install` nginx + PHP-FPM 8.1 + extensions (`mysql`, `mbstring`, `curl`, `xml`, `bcmath`, `zip`, `intl`) + Node.js 20 (via NodeSource) + Composer.
2. Konfigurasi Nginx serve `/home/container/dist` (Vite output) sebagai static.
3. Reverse proxy `/api/*.php` ke PHP-FPM via TCP `127.0.0.1:9000`.
4. Start PHP-FPM & Nginx.

> **Catatan penting:** PHP-FPM versi 8.1 di Ubuntu 22.04 = `php8.1-fpm`. Jika container pakai `ubuntu:22.04` dan install via `apt install php-fpm`, **mungkin dapat PHP 8.3** (default di 22.04). Verifikasi dan pin ke 8.1 via PPA Ondřej jika `WEBSITE/.env` butuh PHP 8.1 spesifik. Lihat juga `WEBSITE/composer.json` untuk constraint PHP.

#### 11.2.2. Variable

| Variable | Default | Keterangan |
|---|---|---|
| `APP_URL` | `https://ucp.pahlawan-roleplay.id` | URL publik UCP |
| `DB_HOST` | `172.17.0.1` | Host MySQL |
| `DB_PORT` | `3306` | Port MySQL |
| `DB_NAME` | `arivena` | DB name |
| `DB_USER` | `pahlawan` | DB user |
| `DB_PASS` | "" | **Wajib diisi via Panel** |

#### 11.2.3. Import & Buat Server

1. **Admin → Nests → Import Egg** → upload `docs/eggs/egg-ucp-website.json`.
2. **Servers → Create New**:
   - Name: `PAHLAWAN UCP Website`
   - Memory: **512 MB** (atau **1024 MB** jika Vite build butuh lebih)
   - Disk: **5000 MB**
   - Port: **80**
3. Tab **Startup**:
   - `DB_PASS` → `<GAME_DB_PASSWORD>`
4. **Save** (trigger install ~5-10 menit untuk install Nginx, PHP, Node 20, npm install, `npm run build`).
5. Cek Console → harus muncul `nginx` (startup marker di egg JSON).

#### 11.2.4. Tweak Setelah Install Pertama

Setelah container running, exec ke dalam:

```bash
sudo docker exec -it <ucp_container> bash

# Cek PHP-FPM jalan
service php8.1-fpm status || service php-fpm status

# Cek Nginx
nginx -t

# Cek Vite build output
ls -lh /home/container/dist/index.html
```

Jika Nginx error "502 Bad Gateway" → cek PHP-FPM socket/port:
```bash
ls -la /run/php/  # cari php-fpm.sock
# ATAU
ss -tlnp | grep 9000   # cek PHP-FPM listen TCP
```

Sesuaikan Nginx config di `/etc/nginx/sites-available/default` (di dalam container).

---

### 11.3. Discord Bot Egg `[Task 5.3.1 – 5.3.4]`

#### 11.3.1. Yang Dilakukan Install Script

Lihat `docs/eggs/egg-discord-bot.json`. Install script otomatis:

1. `apt install` `ca-certificates` (untuk HTTPS ke Discord gateway).
2. Start command: `npm install --omit=dev && node index.js`.

#### 11.3.2. Variable

| Variable | Default | Keterangan |
|---|---|---|
| `DB_HOST` | `172.17.0.1` | Host MySQL |
| `DB_PORT` | `3306` | |
| `DB_NAME` | `arivena` | |
| `DB_USER` | `pahlawan` | |
| `DB_PASS` | "" | **Wajib diisi via Panel** |
| `DISCORD_TOKEN` | "" | **Wajib diisi via Panel** (sangat sensitif) |

> **Catatan penting:** `BOT/config.json` di repo saat ini menyimpan token Discord plain text. Sebelum deploy production, **WAJIB rotate token** di Discord Developer Portal (Bot → Reset Token) — token yang ada di repo dianggap compromised. Token baru di-input via env var `DISCORD_TOKEN` di Panel UI, **JANGAN** ditulis ke file di repo.

#### 11.3.3. Import & Buat Server

1. **Admin → Nests → Import Egg** → upload `docs/eggs/egg-discord-bot.json`.
2. **Servers → Create New**:
   - Name: `PAHLAWAN Discord Bot`
   - Memory: **384 MB**
   - Disk: **2000 MB**
3. Tab **Startup**:
   - `DB_PASS` → `<GAME_DB_PASSWORD>`
   - `DISCORD_TOKEN` → token baru dari Discord Developer Portal
4. **Save** (trigger install ~1-3 menit untuk `npm install --omit=dev`).

#### 11.3.4. Patching `BOT/config.json` untuk Baca Env Var

Karena `BOT/index.js` baca dari `config.json`, tambahkan patch di egg atau di entrypoint container agar `DISCORD_TOKEN` env var override isi `config.json`. Cara simpel:

Tambahkan variable **Command Override** di Panel → Server → **Startup**:

```bash
if [ -n "$DISCORD_TOKEN" ]; then
  sed -i "s/\"token\": \"[^\"]*\"/\"token\": \"$DISCORD_TOKEN\"/" config.json
fi
npm install --omit=dev --no-audit --no-fund && node index.js
```

Atau edit `BOT/index.js` di repo agar baca `process.env.DISCORD_TOKEN` duluan sebelum `config.json.token` (perubahan kode, commit terpisah).

---

## 12. Environment Variable per Service

### 12.1. SA-MP Server (GAMEMODE)

Disimpan di:
- `GAMEMODE/server.cfg` (di repo, tidak sensitive) — hostname, port, plugins.
- Container env vars (di Panel UI) — port, maxplayers.

### 12.2. UCP Website

- `WEBSITE/.env` (di repo) — semua non-sensitive (DB host, app URL).
- Container env vars (di Panel UI) — `DB_PASS` (sensitive), optional override `APP_URL`.

**Rotate App Key setiap fresh deploy:**

```bash
# Di VPS, lalu di dalam container UCP setelah start:
docker exec -it <ucp_container> bash
cd /home/container
php artisan key:generate --force
# Catat APP_KEY baru di password manager, update di Panel env vars
```

### 12.3. Discord Bot

- `BOT/config.json` (di repo) — semua **non-sensitive** (channel IDs, guild ID, payment numbers, role IDs).
- Container env vars (di Panel UI) — `DISCORD_TOKEN` (sensitive), `DB_PASS` (sensitive).

> **Best practice:** Setelah deploy production, **rotate Discord bot token** di Discord Developer Portal (Bot → Reset Token). Token yang ada di `BOT/config.json` repo saat ini HARUS dianggap compromised — jangan dipakai di production.

### 12.4. Pterodactyl Panel

Disimpan di `/var/www/pterodactyl/.env` di host. Backup setelah setiap perubahan:

```bash
sudo cp /var/www/pterodactyl/.env /root/pterodactyl-env-backup-$(date +%Y%m%d).env
sudo chmod 600 /root/pterodactyl-env-backup-*.env
```

---

## 13. Smoke Test End-to-End

Setelah semua server dibuat di Panel dan env var diisi.

### 13.1. Verifikasi Pre-Start `[Task 7.1]`

```bash
# Di VPS:
sudo systemctl status mysql
# Active: active (running)

sudo systemctl status wings
# Active: active (running)

sudo systemctl status pteroq
# Active: active (running)

sudo systemctl status nginx
# Active: active (running)

# Panel UI:
# - Nodes -> Heartbeat green
# - Servers -> semua "Offline" (belum start)
```

### 13.2. Start SA-MP Server `[Task 7.2]`

1. Panel → **Servers** → `PAHLAWAN SA-MP Server` → **Start**.
2. Tunggu 10-30 detik. Console harus muncul:
   ```
   Loaded logfix: ...
   Number of player slots currently in use: 0
   ```
3. Tidak boleh ada `Error` atau `Fatal`.
4. Test dari laptop dengan SA-MP client:
   ```
   Buka SA-MP -> Add Server -> samp.pahlawan-roleplay.id:7777
   ```

### 13.3. Start UCP Website `[Task 7.3]`

1. Panel → `PAHLAWAN UCP Website` → **Start**.
2. Tunggu 1-3 menit (npm install + vite build butuh waktu).
3. Console harus muncul:
   ```
   [UCP] Installing PHP dependencies...
   [UCP] Installing Node dependencies...
   [UCP] Building Vite frontend...
   nginx
   ```
4. Test dari VPS:
   ```bash
   curl -I https://ucp.pahlawan-roleplay.id
   # HTTP/2 200
   ```
5. Test dari laptop browser: buka `https://ucp.pahlawan-roleplay.id` → harus muncul landing page UCP.

### 13.4. Start Discord Bot `[Task 7.4]`

1. Panel → `PAHLAWAN Discord Bot` → **Start**.
2. Tunggu 30-60 detik (npm install + Discord handshake).
3. Console harus muncul: `ClientReady` atau `Logged in` (lihat egg startup marker).
4. Test di Discord: bot harus online (status hijau). Coba command `/help` atau command dasar lain.

### 13.5. Smoke Test Semua `[Task 7.5]`

| Test | Expected | Hasil |
|---|---|---|
| Buka `https://panel.pahlawan-roleplay.id` | Pterodactyl login muncul | ☐ |
| Login ke Panel dengan admin | Dashboard muncul | ☐ |
| Buka `https://ucp.pahlawan-roleplay.id` | UCP landing page muncul | ☐ |
| Di UCP, klik tombol "Login" / "Daftar" | Form auth muncul, bisa register | ☐ |
| Connect SA-MP client ke `samp.pahlawan-roleplay.id:7777` | Server list, bisa join, ada karakter | ☐ |
| Di Discord, bot status online | Online (hijau) | ☐ |
| Ketik `/help` atau command dasar di Discord | Bot merespons | ☐ |
| Buka `https://panel.pahlawan-roleplay.id/admin/servers` | Lihat 3 server: SA-MP, UCP, Bot, semua "Running" | ☐ |

### 13.6. Test Stop/Restart `[Task 7.6]`

1. Klik **Stop** pada SA-MP server di Panel → tunggu sampai status "Offline".
2. Klik **Start** lagi → harus restart bersih.
3. Ulangi untuk UCP dan Bot.

---

## 14. Troubleshooting Umum

### 14.1. OOM Killer Kill Service

**Gejala:** Service tiba-tiba mati, log di dmesg: `Out of memory: Killed process`.

**Solusi:**
```bash
dmesg | grep -i "oom\|killed process"
```

Kurangi memory limit di Pterodactyl server (lihat Panel → Server → Resource Limits). Atau upgrade VPS plan ke 8 GB.

### 14.2. MySQL Connection Refused dari Container

**Gejala:** Service log: `ECONNREFUSED 172.17.0.1:3306`.

**Solusi:**
```bash
# Cek MySQL listening
sudo netstat -tlnp | grep 3306
# Harus ada 0.0.0.0:3306 (atau 172.17.0.1:3306)

# Cek bind-address
sudo grep bind-address /etc/mysql/mysql.conf.d/mysqld.cnf
# Harus: bind-address = 0.0.0.0

# Test dari host
mysql -u pahlawan -p arivena -h 127.0.0.1

# Test dari container
docker run --rm mysql:8.0 mysql -h 172.17.0.1 -u pahlawan -p<PASS> arivena -e "SELECT 1;"
```

Jika `bind-address = 127.0.0.1` (default), ganti jadi `0.0.0.0` dan restart MySQL.

### 14.3. Plugin SA-MP Tidak Ditemukan

**Gejala:** Log: `Failed (plugins/streamer.so: cannot open shared object file)`.

**Solusi:**
```bash
# Cek isi plugin di volume server SA-MP (ganti <samp_server_id>)
sudo ls -la /var/lib/pterodactyl/volumes/<samp_server_id>/plugins/

# Harus ada streamer.so, sscanf.so, bcrypt.so, dan mysql.so jika gamemode pakai MySQL plugin.
# Cek arsitektur plugin (harus Linux ELF, bukan .dll Windows)
sudo file /var/lib/pterodactyl/volumes/<samp_server_id>/plugins/*.so

# Jika plugin hilang, upload/copy plugin Linux .so ke folder plugins lalu set permission:
sudo chmod +x /var/lib/pterodactyl/volumes/<samp_server_id>/plugins/*.so
sudo chown -R 988:988 /var/lib/pterodactyl/volumes/<samp_server_id>/plugins/
```

Jika plugin tetap gagal load, cek `server.cfg` apakah line `plugins` memakai nama file yang benar, misalnya:

```cfg
plugins streamer.so sscanf.so mysql.so bcrypt.so
```

### 14.4. npm install Gagal di Container UCP/Bot

**Gejala:** `npm ERR! network` atau `EACCES`.

**Solusi:**
```bash
# Cek Disk usage di Panel -> Server -> Resource
df -h

# Cek Memory di container
free -h

# Cek network (jika pakai Cloudflare proxy, NPM registry mungkin diblock sementara)
docker exec -it <container> bash
curl -I https://registry.npmjs.org/
# Harus 200 OK
```

### 14.5. Docker Daemon Down

**Gejala:** Wings log: `Cannot connect to Docker daemon`.

**Solusi:**
```bash
sudo systemctl status docker
sudo systemctl start docker
sudo systemctl restart wings
```

### 14.6. Panel Tidak Bisa Diakses Setelah Ubah Domain

**Solusi:**
```bash
sudo nano /var/www/pterodactyl/.env
# Pastikan APP_URL=https://panel.pahlawan-roleplay.id (bukan IP)

cd /var/www/pterodactyl
sudo php artisan config:clear
sudo php artisan cache:clear
sudo php artisan route:clear

# Restart queue worker
sudo systemctl restart pteroq
```

### 14.7. UCP `vite build` Out of Memory

**Gejala:** `Killed` saat `npm run build`.

**Solusi:** Tambah memory limit UCP server dari 512 MB ke 1024 MB. Atau set `NODE_OPTIONS=--max-old-space-size=512` di env var container.

### 14.8. SSL Certificate Error di Panel / UCP

**Gejala:** Browser: `NET::ERR_CERT_AUTHORITY_INVALID`.

**Solusi:** Konfirmasi Cloudflare SSL mode = **Full (Strict)**, dan Origin Certificate sudah di-paste benar di `/etc/nginx/ssl/`.

```bash
sudo nginx -t
sudo systemctl reload nginx
```

---

## 15. Checklist Sebelum Go-Live Alpha

Print checklist ini dan centang saat persiapan Alpha Test 1 Agustus 2026.

### 15.1. Infrastructure

- [ ] VPS 2 vCPU / 4 GB / 50 GB NVMe sudah online
- [ ] OS Ubuntu 22.04 LTS terinstall
- [ ] Region Singapore (atau fallback EU)
- [ ] Non-root user `pahlawan` dengan SSH key
- [ ] Password login disabled di SSH
- [ ] Fail2Ban aktif
- [ ] UFW firewall aktif, port sesuai list
- [ ] Auto security update aktif

### 15.2. Domain & DNS

- [ ] Domain dibeli dan WHOIS valid
- [ ] Cloudflare DNS configured: A record `@`, `panel`, `ucp`, `samp`
- [ ] Cloudflare proxy aktif untuk HTTP traffic (panel, ucp, api)
- [ ] DNS-only untuk `samp` (SA-MP)
- [ ] SSL/TLS mode = Full (Strict)
- [ ] Origin Certificate generated & terinstall
- [ ] SPF, DKIM, DMARC records setup

### 15.3. Database

- [ ] MySQL 8.0 terinstall di host
- [ ] `mysql_secure_installation` selesai
- [ ] bind-address = 0.0.0.0
- [ ] Database `panel` untuk Pterodactyl
- [ ] Database `arivena` untuk PAHLAWAN
- [ ] User `pterodactyl@localhost` dan `pahlawan@%`
- [ ] Schema `arivena` terimport (jika ada dump)

### 15.4. Pterodactyl

- [ ] Panel terinstall di `/var/www/pterodactyl`
- [ ] Queue worker `pteroq` aktif
- [ ] Cron job schedule:run aktif
- [ ] Nginx reverse proxy untuk Panel berjalan
- [ ] Panel bisa diakses di `https://panel.<domain>`
- [ ] Admin user dibuat dan login OK
- [ ] Wings terinstall di `/usr/local/bin/wings`
- [ ] Wings service aktif dan auto-restart
- [ ] Node di Panel heartbeat hijau (connected)
- [ ] SSL/TLS handshake antara Wings dan Panel OK

### 15.5. Egg Files & Runtime Dependencies

- [ ] `docs/eggs/egg-samp-server.json` siap import dan valid JSON
- [ ] `docs/eggs/egg-ucp-website.json` siap import dan valid JSON
- [ ] `docs/eggs/egg-discord-bot.json` siap import dan valid JSON
- [ ] SA-MP plugins Linux `.so` tersedia di volume server (`streamer.so`, `sscanf.so`, `mysql.so`, `bcrypt.so` jika dipakai)
- [ ] UCP runtime berhasil install Node/PHP dependency saat startup pertama
- [ ] Bot runtime berhasil `npm install` saat startup pertama

### 15.6. Eggs & Servers

- [ ] Egg `PAHLAWAN SA-MP Server` terimport
- [ ] Egg `PAHLAWAN UCP Website` terimport
- [ ] Egg `PAHLAWAN Discord Bot` terimport
- [ ] Server SA-MP dibuat (memory 512 MB, port 7777)
- [ ] Server UCP dibuat (memory 512 MB, port 80)
- [ ] Server Bot dibuat (memory 384 MB)
- [ ] File repo sudah di-copy/sync via `rsync` ke volume masing-masing server
- [ ] Permission volume masing-masing server sudah `988:988`

### 15.7. Environment Variables

- [ ] `WEBSITE/.env` DB credentials bener
- [ ] `WEBSITE/.env` SMTP credentials bener
- [ ] `WEBSITE/.env` APP_KEY generated
- [ ] `BOT/config.json` non-sensitive fields bener
- [ ] Discord token di-rotate (jangan pakai token dari repo)
- [ ] Discord token di-set via Pterodactyl env var
- [ ] `GAMEMODE/server.cfg` hostname, port, plugins bener

### 15.8. Email/SMTP

- [ ] SMTP provider aktif (Zoho / Brevo / Resend)
- [ ] Test kirim email dari VPS berhasil
- [ ] Pterodactyl `.env` MAIL_* configured
- [ ] UCP `.env` MAIL_* configured

### 15.9. Smoke Test Passed

- [ ] Panel login OK
- [ ] UCP website terbuka di `https://ucp.<domain>`
- [ ] SA-MP server connect dari client
- [ ] Bot online di Discord
- [ ] Stop/Restart semua service dari Panel OK

### 15.10. Security

- [ ] Semua password disimpan di password manager (bukan di Git)
- [ ] `BOT/config.json` di repo TIDAK berisi token production
- [ ] `WEBSITE/.env` di repo TIDAK berisi password production
- [ ] SSH password login disabled
- [ ] Fail2Ban aktif dan punya banned IPs
- [ ] UFW ports sesuai kebutuhan
- [ ] MySQL root tidak bisa diakses dari network (hanya localhost)
- [ ] Auto security update aktif

### 15.11. Dokumentasi

- [ ] `docs/VPS_SETUP_GUIDE.md` tersedia untuk operator baru
- [ ] `docs/PTERODACTYL_OPERATIONS.md` tersedia untuk daily ops
- [ ] Semua kredensial ada di password manager
- [ ] Backup `.env` Panel dan Pterodactyl config di `/root/`

### 15.12. OpenSpec

- [ ] Semua task di `tasks.md` OpenSpec sudah di-check (61 tasks)
- [ ] `validation.md` di OpenSpec ditulis dengan hasil smoke test
- [ ] Change di-archive setelah Alpha sukses

---

## Lampiran A. Resource Budget Visual

```
Total 4 GB RAM
├── OS + system services       ~512 MB
├── Docker daemon              ~150 MB
├── Pterodactyl Panel          ~256 MB
├── Pterodactyl Queue worker   ~100 MB
├── Nginx                      ~50 MB
├── MySQL 8.0                  ~512 MB
├── Redis                      ~50 MB
├── ─── buffer system ───      ~320 MB
└── Container services:
    ├── SA-MP Server           ~512 MB (limit)
    ├── UCP Website            ~512 MB (limit)
    └── Discord Bot            ~384 MB (limit)
                              ─────
                              3,358 MB total
                              ~640 MB headroom untuk spike
```

Upgrade ke **8 GB plan** sebelum Beta Test jika:
- Lebih dari 20 concurrent players.
- `free -h` consistently shows < 500 MB available.
- dmesg menunjukkan OOM kills.

---

## Lampiran B. Path & File Reference

| Path | Tujuan |
|---|---|
| `/opt/pahlawan-roleplay/` | Git clone dari repo PAHLAWAN |
| `/var/www/pterodactyl/` | Pterodactyl Panel (Laravel) |
| `/etc/pterodactyl/config.yml` | Wings daemon config |
| `/etc/pterodactyl/queues/` | Pterodactyl queue storage (auto-managed) |
| `/etc/nginx/sites-available/pterodactyl.conf` | Nginx vhost untuk Panel |
| `/etc/nginx/ssl/` | Origin SSL certificates (Cloudflare) |
| `/etc/systemd/system/wings.service` | Wings daemon systemd |
| `/etc/systemd/system/pteroq.service` | Pterodactyl queue systemd |
| `/var/lib/pterodactyl/volumes/<server_id>/` | Per-server files hasil `rsync` dari repo |
| `docs/eggs/` | Egg JSON canonical yang di-import ke Pterodactyl |
| `/var/log/nginx/` | Nginx logs |
| `/var/log/mysql/` | MySQL logs |
| `~/AppData/Local/hermes/skills/` (Windows laptop) | Password manager / dokumen lokal |

---

## Lampiran C. Referensi External

- **Pterodactyl Docs**: https://pterodactyl.io/project/introduction.html
- **Wings Installation**: https://pterodactyl.io/wings/1.0/installing.html
- **Cloudflare Origin Cert**: https://developers.cloudflare.com/ssl/origin-configuration/origin-ca/
- **Let's Encrypt**: https://letsencrypt.org/getting-started/
- **SA-MP Linux Server**: https://samp.fandom.com/wiki/Linux_Server
- **open.mp Server**: https://open.mp/docs/server-linux/
- **MySQL 8.0 Docs**: https://dev.mysql.com/doc/refman/8.0/en/
- **Ubuntu 22.04 Server Guide**: https://ubuntu.com/server/docs

---

**Akhir guide.** Setelah semua checklist di bagian 15 terpenuhi, sistem siap untuk **Alpha Test 1 Agustus 2026**.

Lanjutkan ke `docs/PTERODACTYL_OPERATIONS.md` untuk panduan operasional harian (start/stop/restart, deploy update, troubleshooting ringkas).