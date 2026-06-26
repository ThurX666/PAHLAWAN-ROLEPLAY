# VPS Provider Guide — PAHLAWAN ROLEPLAY

> **OpenSpec:** `vps-pterodactyl-infrastructure`
> **Tujuan:** Panduan memilih + order VPS yang sesuai spec di [`VPS_SETUP_GUIDE.md`](./VPS_SETUP_GUIDE.md).
> **Spek target:** 2 vCPU (Ryzen 9 7900 / setara), 4 GB DDR5, 50 GB NVMe, 10 Gbit/s shared.
> **Budget:** ≤ €20 / bulan (~$22 USD).

---

## 0. Spek yang Harus Dicari

| Item | Minimum | Ideal | Catatan |
|---|---|---|---|
| vCPU | 2 core | 2 core Ryzen 9 7900 / EPYC 7002 series | Single-thread penting buat SA-MP server |
| RAM | 4 GB DDR5 | 4 GB DDR5 ECC | 3.7GB terpakai (panel + wings + mysql + 3 service), buffer 300MB |
| Storage | 50 GB NVMe | 50 GB NVMe SSD | Docker images + repo + DB butuh ~25GB |
| Network | 1 Gbit/s | 10 Gbit/s shared | Throughput bukan masalah; latency ke player yang penting |
| OS | Ubuntu 22.04 LTS x86_64 | Ubuntu 22.04 LTS | Pterodactyl official support |
| Region | Asia-Pacific | Singapore / Hong Kong | Latency ke ID ~30-80ms |
| IPv4 | 1 dedicated | 1 dedicated | Bukan shared NAT |
| DDoS protection | Opsional | Basic included | Buat Alpha tanpa, tapi nice-to-have |

---

## 1. Opsi Provider (urut prioritas)

### 1.1. Tier 1 — Rekomendasi

#### A. **VibeGames vServer** — pilihan utama jika ingin Anti-DDoS bawaan

> User memilih kandidat provider: https://vibegames.com/vserver karena ada **Anti DDoS Protection**. Ini cocok untuk game server publik karena trafik SA-MP/open.mp rentan kena flood, query spam, dan attack ke port game.

- **Website:** https://vibegames.com/vserver
- **DDoS:** Anti-DDoS Protection tersedia di halaman produk. Tetap cek detail paket sebelum checkout: kapasitas mitigation, lokasi scrubbing, apakah UDP game traffic dilindungi, dan apakah ada filtering panel.
- **OS yang harus dipilih:** **Ubuntu 22.04 LTS x86_64**.
- **Spek minimum:** 2 vCPU, 4 GB RAM, 50 GB NVMe/SSD, IPv4 dedicated.
- **Region:** pilih region paling dekat ke player Indonesia jika tersedia. Jika region Eropa saja, latency lebih tinggi tapi masih bisa untuk roleplay.
- **Catatan:** Anti-DDoS provider tidak menggantikan firewall host. Tetap pakai UFW/iptables hardening di [`VPS_SETUP_GUIDE.md`](./VPS_SETUP_GUIDE.md) dan setup lengkap di [`SETUP_GUIDE.md`](../openspec/changes/vps-pterodactyl-infrastructure/SETUP_GUIDE.md).

**Order flow VibeGames:**
1. Buka https://vibegames.com/vserver.
2. Pilih paket vServer dengan minimal **2 vCPU / 4 GB RAM / 50 GB storage**.
3. Pastikan fitur **Anti DDoS Protection** tercantum di paket/checkout.
4. Pilih OS: **Ubuntu 22.04 LTS**.
5. Pilih region terdekat ke Indonesia jika tersedia.
6. Tambahkan SSH public key jika panel mendukung. Jika tidak, pakai initial root password sementara lalu harden SSH setelah login pertama.
7. Checkout dan bayar.
8. Catat data berikut di password manager:
   ```txt
   VPS_PROVIDER        = VibeGames
   VPS_PRODUCT_URL     = https://vibegames.com/vserver
   VPS_PLAN            = <nama paket>
   VPS_REGION          = <region>
   VPS_IPV4            = <IP publik>
   DDOS_PROTECTION     = included/enabled
   VPS_ORDER_DATE      = <tanggal>
   VPS_RENEWAL_DATE    = <tanggal>
   ```
9. Setelah VPS aktif, lanjut ke [`VPS_SETUP_GUIDE.md`](./VPS_SETUP_GUIDE.md) dan jalankan hardening firewall tingkat lanjut.

#### B. **Hetzner Cloud** — CPX11 (€14.40/mo diskon)

> Spek kuat dan murah, tapi region Eropa/US sehingga latency ke Indonesia lebih tinggi daripada SG/ID provider.

- **Region tersedia:** Falkenstein (DE), Nuremberg (DE), Ashburn (US), Hillsboro (US). **TIDAK ADA Singapore.**
- **Latency ke Jakarta dari DE:** ~200-250ms (playable untuk roleplay, agak laggy untuk combat).
- **Harga:** €18.00/mo normal, **€14.40/mo dengan diskon** (promo recurring, biasanya untuk plan baru).
- **DDoS:** Included untuk semua Cloud.
- **Billing:** Per jam, bisa cancel kapan saja. Bayar via kartu kredit / PayPal / SEPA.
- **Sign-up:** https://www.hetzner.com/cloud
- **Keunggulan:** Quality hardware bagus, harga paling kompetitif, dokumentasi lengkap.

**Order flow Hetzner:**
1. Buka https://www.hetzner.com/cloud
2. Sign up (email + password), verifikasi email.
3. Pilih lokasi: **Falkenstein** atau **Nuremberg** (pilih salah satu).
4. Image: **Ubuntu 22.04** (atau 24.04 lalu turunkan manual).
5. Type: **CPX11** (2 vCPU / 4GB / 50GB / 10Gbit).
6. Volume: skip (storage 50GB cukup).
7. Network: IPv4 only (IPv6 opsional).
8. SSH key: paste public key kamu (`cat ~/.ssh/id_ed25519.pub`).
9. Name: `pahlawan-roleplay`.
10. Klik **Create & Buy Now**.
11. Setelah beberapa detik → server provisioned, IP muncul di dashboard.

#### C. **Vultr** — Cloud Compute ($24/mo)

- **Region Singapore:** ✅ Tersedia (`sgp1`).
- **Spek setara:** 2 vCPU / 4GB RAM / 80GB NVMe / 1 Gbit/s.
- **Harga:** $24/mo (atau $0.018/jam). Promo new user sering $100 free credit.
- **OS:** Ubuntu 22.04 LTS tersedia.
- **Sign-up:** https://www.vultr.com
- **Latency ke Jakarta:** ~30-50ms (routing SG bagus).
- **DDoS:** Opsional add-on $10/mo.

**Order flow Vultr:**
1. Sign up di vultr.com, verifikasi email + kartu.
2. Klik **Deploy New Server** (tombol +).
3. Server Type: **Cloud Compute** (shared CPU).
4. Location: **Singapore** (sgp1).
5. Image: **Ubuntu 22.04 LTS x64**.
6. Size: **2 vCPU / 4GB RAM / 80GB SSD** ($24/mo).
7. Klik **Deploy Now**.
8. Tunggu 30-60 detik, IP muncul di dashboard.

#### C. **DigitalOcean** — Basic Droplet ($24/mo)

- **Region Singapore:** ✅ Tersedia (`sgp1`).
- **Spek setara:** 2 vCPU / 4GB RAM / 80GB SSD / 2 Gbit/s.
- **Harga:** $24/mo (atau $0.01853/jam). New user $200 free credit (60 hari).
- **OS:** Ubuntu 22.04 LTS.
- **Sign-up:** https://www.digitalocean.com
- **Latency:** ~40-60ms.
- **DDoS:** Tidak included di basic droplet.

#### D. **Linode (Akamai)** — Dedicated 4GB ($24/mo)

- **Region Singapore:** ✅ Tersedia (`ap-southeast`).
- **Spek setara:** 2 vCPU dedicated / 4GB / 80GB NVMe / 1 Gbit/s.
- **Harga:** $24/mo (atau $0.018/jam).
- **OS:** Ubuntu 22.04 LTS.
- **Sign-up:** https://www.linode.com

#### E. **Contabo** — Cloud VPS 4 (€8.99/mo, paling murah)

- **Region Singapore:** ✅ Tersedia.
- **Spek setara:** 4 vCPU / 8GB RAM / 100GB SSD / 32 TB traffic (overspeced).
- **Harga:** €8.99/mo — jauh lebih murah dari kompetitor. Trade-off: CPU shared, bukan Ryzen 9.
- **OS:** Ubuntu 22.04 LTS.
- **Sign-up:** https://contabo.com
- **Catatan:** IP reputation sering rendah (email bisa masuk spam kalau pakai SMTP dari sini), tapi untuk SA-MP + web OK.

### 1.2. Tier 2 — Alternatif kalau Tier 1 penuh / mahal

| Provider | Region terdekat ke ID | Spek setara | Harga | Catatan |
|---|---|---|---|---|
| **UpCloud** | Singapore | 2 vCPU / 4GB / 80GB | €20/mo | MaxIOPS storage, kualitas bagus |
| **Kamatera** | Hong Kong | 2 vCPU / 4GB / 40GB | $30/mo | Free trial 30 hari |
| **OVH** | Singapore (SG-1) | 2 vCPU / 4GB / 40GB | €22/mo | Provider besar, support banyak |
| **IDCloudHost** | Indonesia (Jakarta) | 2 vCPU / 4GB / 50GB | Rp 150rb/bln | Latency <10ms ke user ID, tapi IP reputation sedang |

### 1.3. Tier 3 — Free / Trial (cuma untuk dev/test, jangan production)

- **Oracle Cloud Free Tier** — 4 vCPU ARM / 24GB RAM, free selamanya (always-free). Region: Tokyo, Seoul, Singapore. Bagus untuk test. **Limitations:** proses sign-up ketat (kartu kredit divalidasi), capacity not guaranteed.
- **Google Cloud Free Tier** — e2-micro 2 vCPU shared / 1GB, 30 hari. Spek kurang.
- **AWS Free Tier** — t2.micro 1GB, 12 bulan. Spek kurang.

---

## 2. Decision Matrix

| Kriteria | VibeGames vServer | Hetzner CPX11 | Vultr Singapore | DO Singapore | Linode SG | Contabo SG |
|---|---|---|---|---|---|---|
| **Harga** | Cek paket aktif | ⭐⭐⭐⭐⭐ €14.40 | ⭐⭐⭐ $24 | ⭐⭐⭐ $24 | ⭐⭐⭐ $24 | ⭐⭐⭐⭐⭐ €8.99 |
| **Latency ke ID** | Tergantung region | ⭐⭐ 200-250ms | ⭐⭐⭐⭐⭐ 30-50ms | ⭐⭐⭐⭐ 40-60ms | ⭐⭐⭐⭐⭐ 30-50ms | ⭐⭐⭐⭐ 50-80ms |
| **CPU quality** | Cek paket aktif | ⭐⭐⭐⭐⭐ Ryzen 9 7900 | ⭐⭐⭐ shared | ⭐⭐⭐ shared | ⭐⭐⭐⭐ dedicated | ⭐⭐ shared |
| **DDoS** | ⭐⭐⭐⭐⭐ Anti-DDoS included | ⭐⭐⭐⭐⭐ included | ⭐⭐ add-on $10 | ⭐⭐ none | ⭐⭐⭐ basic | ⭐⭐ none |
| **Support 24/7** | Cek SLA/support | ⭐⭐⭐⭐⭐ | ⭐⭐⭐⭐ | ⭐⭐⭐⭐ | ⭐⭐⭐⭐ | ⭐⭐⭐ |
| **Billing** | Cek checkout | Per jam | Per jam | Per jam | Per jam | Per bulan |
| **Best for** | Game server publik yang perlu Anti-DDoS bawaan | Budget player <10 | Latency-sensitive | Brand trust | Dedicated CPU | Absolute cheapest |

**Rekomendasi:**

| Situasi | Pilihan |
|---|---|
| Mau game server lebih aman dari flood/DDoS dan provider sudah punya Anti-DDoS | **VibeGames vServer** |
| Spek persis kayak screenshot + budget ketat, latency bukan prioritas | **Hetzner CPX11** |
| Mau latency bagus ke player ID, budget $24 OK | **Vultr Singapore** |
| Trial / dev dulu, baru production nanti | **Oracle Cloud Free Tier** (selama free) → VibeGames/Vultr/Hetzner untuk prod |
| Spek tinggi dengan harga paling murah | **Contabo Cloud VPS 4** |
| Player Indonesia, latency #1 priority | VibeGames region terdekat / Vultr SG / Linode SG |

---

## 3. Comparison Total Cost 1 Tahun

| Provider | Plan | Harga/bulan | 1 tahun | Diskon tahunan? |
|---|---|---|---|---|
| Hetzner CPX11 | 2v/4G/50G | €14.40 | €172.80 | Tidak ada diskon tambahan, tapi billing per jam jadi prorated |
| Vultr SGP1 | 2v/4G/80G | $24 | $288 | Tidak |
| DO Singapore | 2v/4G/80G | $24 | $288 | Tidak |
| Linode SG | 2v/4G/80G | $24 | $288 | Tidak |
| Contabo SG | 4v/8G/100G | €8.99 | €107.88 | Diskon ~10% kalau bayar tahunan |

---

## 4. Sebelum Order — Checklist Pra-Beli

- [ ] **Budget disetujui** untuk 3-6 bulan minimum (commitment agar Alpha–Beta lancar).
- [ ] **Akun provider dibuat**, email terverifikasi, payment method valid.
- [ ] **SSH key sudah di-generate** di laptop lokal:
  ```bash
  ssh-keygen -t ed25519 -C "pahlawan-roleplay-vps"
  cat ~/.ssh/id_ed25519.pub   # copy paste ke provider panel
  ```
- [ ] **Hostname direncanakan:** mis. `pahlawan-roleplay.id` atau `pahlawan.my.id` (akan dibahas di [`DOMAIN_PROVIDER_GUIDE.md`](./DOMAIN_PROVIDER_GUIDE.md)).
- [ ] **Backup payment method kedua** (kartu kedua / PayPal) — kalau primary gagal di tengah bulan.
- [ ] **Provider memenuhi spek target** (lihat tabel §1).

---

## 5. Setelah Order — Tindakan Pertama

1. **Cek email** untuk IP address + root password (kalau tidak pakai SSH key).
2. **Login SSH pertama:**
   ```bash
   ssh root@<VPS_IP>
   ```
3. **Cek spek benar:**
   ```bash
   nproc          # harus 2
   free -h        # harus 4GB
   df -h          # harus 50GB+
   lsb_release -a # harus Ubuntu 22.04
   ```
4. **Lanjut ke [`VPS_SETUP_GUIDE.md`](./VPS_SETUP_GUIDE.md)** §3 untuk hardening OS.

---

## 6. FAQ

### Q: Hetzner ga ada Singapore, gimana?
Pakai Vultr/DO/Linode Singapore. Budget $24 vs €14.40 cuma beda ~$10/bulan, worth untuk latency.

### Q: Bisa pakai VPS gratis dulu untuk dev?
Ya, Oracle Cloud Always Free. Tapi IP reputation rendah, dan spek RAMnya 24GB (overspeced untuk 4GB target). Setup sama persis, tinggal beda di dashboard.

### Q: Kalau ping dari ID ke Hetzner DE 250ms, playable ga untuk roleplay?
Bisa, tapi terasa lag untuk combat cepat. Untuk roleplay chat-based (drive roleplay, kerja, bisnis) masih fine. SA-MP heartbeat masih ok di 250ms. Kalau player banyak komplain, switch ke Vultr SG nanti.

### Q: Hetzner billing per jam, kalau stop server bayarnya tetap?
Tidak, kalau kamu destroy server, billing berhenti. Tapi jangan lupa backup data sebelum destroy.

### Q: Bisa pakai Hetzner + Vultr bareng (HA / failover)?
Bisa, tapi di Alpha overkill. Sisa VPS pertama yang down = semua service down, fix manual.

### Q: IP reputation Contabo jelek, kenapa?
Contabo allocate IP block besar-besaran dari pool lama / recycled. Banyak spammer pakai sebelumnya. Untuk SMTP delivery dari Contabo akan sering masuk spam folder. Untuk SA-MP + web OK.

### Q: Payment IDR bisa?
Hetzner: EUR / USD via kartu / PayPal. Vultr: USD via kartu / PayPal / crypto. DO: USD via kartu / PayPal. Contabo: EUR via kartu / PayPal / kripto. Beberapa provider Indonesia (IDCloudHost, Biznet Gio) bisa QRIS / transfer bank lokal.

---

## 7. Rekomendasi Final untuk PAHLAWAN ROLEPLAY

Untuk **Alpha Test** (5-10 players internal, deadline 1 Agustus 2026):

**Opsi A (rekomendasi utama jika prioritas keamanan game server):** **VibeGames vServer**
- Sudah ada **Anti DDoS Protection** di halaman produk.
- Cocok untuk server game publik yang membuka port SA-MP/open.mp.
- Tetap wajib hardening firewall host karena Anti-DDoS provider hanya satu lapisan proteksi.
- Sebelum checkout, pastikan paket memenuhi minimal 2 vCPU / 4GB RAM / 50GB storage / Ubuntu 22.04.

**Opsi B (latency terbaik ke Indonesia):** **Vultr Singapore 2v/4G/80G ($24/mo)**
- Latency terbaik ke player ID (~30-50ms).
- Spek cukup.
- Billing per jam, bisa destroy kapan saja.
- Bisa upgrade ke plan lebih tinggi sebelum Beta.

**Opsi C (budget):** **Hetzner CPX11 €14.40/mo**
- Spek persis seperti screenshot, harga paling murah.
- Latency 200-250ms (masih playable tapi laggy).
- Pilih kalau budget super ketat dan latency bukan prioritas.

**Opsi D (premium):** **Linode Singapore 2v/4G/80G dedicated ($24/mo)**
- CPU dedicated (bukan shared).
- Cocok untuk Beta / RC saat player count naik.

---

## 8. Next Step

Setelah VPS dipesan dan IP dapat, lanjut ke:
- [`DOMAIN_PROVIDER_GUIDE.md`](./DOMAIN_PROVIDER_GUIDE.md) — beli domain
- [`VPS_SETUP_GUIDE.md`](./VPS_SETUP_GUIDE.md) — setup server

Simpan informasi ini setelah order:
```
VPS_PROVIDER        = <nama provider>
VPS_REGION          = <region>
VPS_IPV4            = <IP publik>
VPS_HOSTNAME        = <hostname VPS>
VPS_ROOT_PASSWORD   = <kalau pakai password>
VPS_PLAN            = <plan name + spek>
VPS_COST_PER_MONTH  = <harga>
VPS_ORDER_DATE      = <tanggal order>
VPS_RENEWAL_DATE    = <tanggal renewal>
```