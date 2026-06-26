# Domain Provider Guide — PAHLAWAN ROLEPLAY

> **OpenSpec:** `vps-pterodactyl-infrastructure`
> **Tujuan:** Panduan memilih + membeli domain untuk infrastruktur PAHLAWAN ROLEPLAY (Panel + UCP + SA-MP server).
> **Dokumen terkait:** [`VPS_PROVIDER_GUIDE.md`](./VPS_PROVIDER_GUIDE.md) — panduan pilih VPS. [`VPS_SETUP_GUIDE.md`](./VPS_SETUP_GUIDE.md) — setup server setelah domain siap.

---

## 0. Kenapa Butuh Domain Sendiri?

Domain sendiri memberikan 4 hal:
1. **HTTPS via Let's Encrypt / Cloudflare Origin Cert** — tanpa domain, cuma bisa HTTP (atau self-signed yang bikin browser warning).
2. **Identitas server** — `panel.pahlawan-roleplay.id` lebih profesional daripada `<IP>:8080`.
3. **DNS fleksibel** — bisa pindah VPS / ganti IP kapan saja tanpa kasih IP baru ke user.
4. **Email branded** — `noreply@pahlawan-roleplay.id` lebih dipercaya daripada Gmail.

---

## 1. Subdomain yang Akan Dipakai

Pilih 1 nama domain utama, lalu setup subdomain untuk tiap service:

| Subdomain | Tujuan | Tipe DNS |
|---|---|---|
| `panel.<domain>` | Pterodactyl Panel | A record, Cloudflare Proxied |
| `ucp.<domain>` (atau `@`) | UCP Website | A record, Cloudflare Proxied |
| `samp.<domain>` | SA-MP server | A record, **DNS-only** (no proxy) |
| `api.<domain>` | (opsional) API UCP | A record, Cloudflare Proxied |
| `mail.<domain>` | SMTP host (jika pakai mail server sendiri) | A record |
| `@` (root) | Default landing / redirect ke UCP | A record, Cloudflare Proxied |

---

## 2. Pilih Registrar

### 2.1. Tier 1 — Rekomendasi

| Registrar | Alasan | Harga / tahun (≈) |
|---|---|---|
| **Cloudflare Registrar** | Harga at-cost (tanpa mark-up), WHOIS privacy gratis, DNS cepat. | Sesuai TLD (sering paling murah) |
| **Niagahoster** (ID) | IDR, dukungan Bahasa Indonesia. `.id`/`.my.id`/`.com`. Bisa bayar QRIS / transfer bank lokal. | Rp 100k – 250k |
| **Namecheap** | UI bersih, WHOIS privacy gratis untuk banyak TLD. | USD 9 – 13 |
| **Porkbun** | Murah untuk TLD populer. | USD 5 – 12 |
| **IDCloudHost** | Lokal ID, support Bahasa Indonesia. | Rp 100k – 200k |

**Rekomendasi utama:** **Cloudflare Registrar** jika tidak butuh TLD Indonesia. **Niagahoster / IDCloudHost** jika ingin `.id` (perlu KTP/KITAS).

### 2.2. TLD yang Disarankan

| TLD | Cocok untuk | Harga / tahun |
|---|---|---|
| `.com` | Universal, paling familiar. | USD 9 – 12 |
| `.id` | Identitas Indonesia, perlu KTP. | Rp 200k – 300k |
| `.my.id` | Sub-domain `.my.id` gratis untuk warga negara Indonesia (via subdomain provider). | Gratis / murah |
| `.net` | Alternatif `.com`. | USD 10 – 12 |
| `.xyz` | Murah, modern. | USD 2 – 5 |
| `.com.id` | Combo Indonesia + `.com` feel. | Rp 150k – 200k |

**Rekomendasi utama:** `.com` untuk universal, `.my.id` jika gratis, `.id` jika mau identitas kuat.

---

## 3. Langkah Beli (Contoh Cloudflare)

1. Buka https://www.cloudflare.com/products/registrar/ → klik **Register a domain**.
2. Cari nama domain yang tersedia (mis. `pahlawanroleplay.com`).
3. Pilih periode: **1 tahun** dulu, nonaktifkan auto-renew (kontrol manual).
4. Buat akun Cloudflare jika belum punya, atau login.
5. Bayar via kartu kredit / debit / PayPal.
6. Setelah sukses, domain akan muncul di **Account → Registrar → Domains**.
7. **Nonaktifkan auto-renew** di settings (recommended untuk kontrol).

---

## 4. Setup DNS — Cloudflare

Login ke Cloudflare Dashboard → klik domain → **DNS** → **Records**:

### 4.1. Tambahkan Record

| Type | Name | Content (IP VPS) | Proxy | TTL |
|---|---|---|---|---|
| A | `@` | `<VPS_IP>` | Proxied (orange cloud) | Auto |
| A | `panel` | `<VPS_IP>` | Proxied | Auto |
| A | `ucp` | `<VPS_IP>` | Proxied | Auto |
| A | `api` | `<VPS_IP>` | Proxied | Auto |
| A | `samp` | `<VPS_IP>` | **DNS only** (gray cloud) | Auto |

> **Catatan SA-MP:** Client SA-MP tidak support Cloudflare proxy. Record `samp` harus **DNS only** agar player bisa connect langsung ke IP VPS di port 7777.

### 4.2. Propagasi DNS

Setelah record ditambah, propagasi butuh 1-5 menit (Cloudflare biasanya instan).

Test dari laptop:

```bash
nslookup panel.pahlawan-roleplay.id
# Harus return IP VPS via Cloudflare proxy (bukan IP asli)

nslookup samp.pahlawan-roleplay.id
# Harus return IP VPS asli
```

### 4.3. Email Routing (Opsional, Gratis)

Cloudflare punya fitur **Email Routing** gratis:
- **Forward** email dari `noreply@<domain>` ke Gmail pribadi Anda.
- Berguna untuk menerima notifikasi VPS / panel tanpa expose Gmail.

Setup di Cloudflare Dashboard → **Email** → **Email Routing** → **Add records & enable**.

---

## 5. SSL / HTTPS — Cloudflare Origin Certificate (Rekomendasi)

### 5.1. Pilih Mode SSL

| Mode | Cocok untuk | Trade-off |
|---|---|---|
| **Cloudflare Origin Certificate** | VPS di belakang Cloudflare proxy | TLS ke Cloudflare edge (free). Tidak end-to-end ke user, tapi untuk SA-MP/UCP cukup. |
| **Let's Encrypt via Certbot** | VPS publik, tidak pakai Cloudflare proxy | TLS end-to-end, tapi SA-MP tetap IP only. |
| **Cloudflare Full (Strict) + Origin Cert** | Rekomendasi untuk setup ini | TLS user → Cloudflare edge. TLS Cloudflare → VPS pakai Origin Cert (paling aman + free). |

**Rekomendasi:** Cloudflare Origin Certificate (Full Strict).

### 5.2. Generate Origin Certificate

1. Cloudflare Dashboard → domain → **SSL/TLS** → **Origin Server** → **Create Certificate**.
2. Pilih:
   - Private key type: **RSA (2048)** (kompatibel luas)
   - Hostnames: `*.pahlawan-roleplay.id` dan `pahlawan-roleplay.id` (atau spesifik: `panel.pahlawan-roleplay.id`, `ucp.pahlawan-roleplay.id`)
   - Certificate validity: **15 years** (Cloudflare max)
3. Klik **Create** → copy **Certificate (PEM)** dan **Private Key**.

### 5.3. Install di VPS

```bash
sudo mkdir -p /etc/nginx/ssl
sudo nano /etc/nginx/ssl/pahlawan-roleplay.id.pem
# Paste Origin Certificate (PEM)

sudo nano /etc/nginx/ssl/pahlawan-roleplay.id.key
# Paste Private Key

sudo chmod 600 /etc/nginx/ssl/pahlawan-roleplay.id.key
sudo chmod 644 /etc/nginx/ssl/pahlawan-roleplay.id.pem
```

### 5.4. Set Cloudflare SSL Mode

Cloudflare Dashboard → **SSL/TLS** → **Overview** → pilih **Full (Strict)**.

Test SSL di https://www.ssllabs.com/ssltest/ → target rating **A** atau **A+**.

---

## 6. Setup Email SPF, DKIM, DMARC (Reputasi)

Supaya email dari `noreply@<domain>` tidak masuk spam:

### 6.1. SPF Record

Tambah TXT record di Cloudflare DNS:

| Type | Name | Value |
|---|---|---|
| TXT | `@` | `v=spf1 include:_spf.google.com include:zoho.com ~all` |

(Sesuaikan `include:` dengan SMTP provider Anda.)

### 6.2. DKIM

Generate DKIM di dashboard SMTP provider (Zoho / Brevo / Resend), lalu tambahkan TXT record:

| Type | Name | Value |
|---|---|---|
| TXT | `zmail._domainkey` | (DKIM value dari SMTP dashboard) |

### 6.3. DMARC

| Type | Name | Value |
|---|---|---|
| TXT | `_dmarc` | `v=DMARC1; p=quarantine; rua=mailto:dmarc@<domain>` |

Test di https://mxtoolbox.com/spf.aspx dan https://mxtoolbox.com/dkim.aspx.

---

## 7. Sebelum Lanjut — Checklist Pra-Setup VPS

- [ ] Domain dibeli & WHOIS valid.
- [ ] DNS propagated (`nslookup` mengembalikan IP benar).
- [ ] A record `panel`, `ucp` = `<VPS_IP>` (Cloudflare Proxied).
- [ ] A record `samp` = `<VPS_IP>` (DNS only).
- [ ] Cloudflare SSL/TLS mode = **Full (Strict)**.
- [ ] Origin Certificate generated & disimpan di VPS (`/etc/nginx/ssl/`).
- [ ] (Opsional) Email Routing aktif untuk forward ke Gmail.
- [ ] (Opsional) SPF + DKIM + DMARC records ditambahkan.

---

## 8. Next Step

Setelah domain siap, lanjut ke:
- [`VPS_PROVIDER_GUIDE.md`](./VPS_PROVIDER_GUIDE.md) — beli VPS.
- [`VPS_SETUP_GUIDE.md`](./VPS_SETUP_GUIDE.md) — setup server + Pterodactyl + 3 service.

---

## 9. FAQ

### Q: `.id` butuh KTP?
Ya, untuk mendaftarkan `.id` (second-level domain) butuh KTP / KITAS / paspor Indonesia. `.co.id` butuh badan usaha (PT/CV). Alternatif gratis: subdomain `my.id` (warga negara Indonesia) atau `.com` / `.net` (tanpa syarat).

### Q: Bisa pakai domain gratis Freenom / No-IP?
Tidak direkomendasikan untuk production. Freenom sudah tidak menerima domain baru sejak 2023. No-IP / DuckDNS hanya untuk subdomain gratis yang sering expire / tidak stabil. Beli domain murah (.xyz USD 2/thn) lebih aman.

### Q: Apakah IPv6-only VPS perlu record AAAA juga?
Tambahkan AAAA record untuk IPv6 jika VPS punya IPv6 publik. Tapi SA-MP client hanya support IPv4, jadi untuk `samp` wajib ada A record.

### Q: Apakah Cloudflare proxy akan memperlambat SA-MP?
Tidak, karena `samp` di-set DNS-only (gray cloud). Cloudflare proxy cuma untuk HTTP/HTTPS traffic (panel, ucp, api).

### Q: Bisa pakai Cloudflare Registrar + DNS eksternal lain?
Bisa, tapi tidak direkomendasikan. Pakai Cloudflare untuk kedua-nya (registrar + DNS) paling simpel. Bisa juga daftar domain di Niagahoster lalu pointing nameserver ke Cloudflare.

---

Simpan informasi ini setelah order:

```
DOMAIN_REGISTRAR   = <nama registrar>
DOMAIN_NAME        = pahlawan-roleplay.id
DOMAIN_EXPIRY      = <tanggal>
NAMESERVERS        = <ns1.cloudflare.com, ns2.cloudflare.com>
CF_ACCOUNT_EMAIL   = <email akun Cloudflare>
ORIGIN_CERT_PATH   = /etc/nginx/ssl/pahlawan-roleplay.id.pem
ORIGIN_KEY_PATH    = /etc/nginx/ssl/pahlawan-roleplay.id.key
```