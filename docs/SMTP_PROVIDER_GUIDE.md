# SMTP Provider Guide — PAHLAWAN ROLEPLAY

> **OpenSpec:** `vps-pterodactyl-infrastructure`
> **Tujuan:** Panduan memilih, membeli, dan mengonfigurasi SMTP provider untuk email Pterodactyl Panel dan UCP PAHLAWAN ROLEPLAY.
> **Dokumen terkait:** [`DOMAIN_PROVIDER_GUIDE.md`](./DOMAIN_PROVIDER_GUIDE.md), [`VPS_SETUP_GUIDE.md`](./VPS_SETUP_GUIDE.md), [`PTERODACTYL_OPERATIONS.md`](./PTERODACTYL_OPERATIONS.md).

---

## 0. Kenapa Perlu SMTP Provider?

SMTP dipakai untuk:

- Email admin Pterodactyl Panel.
- Reset password Pterodactyl.
- Email OTP / verifikasi akun UCP.
- Notifikasi sistem UCP (opsional): donation, ticket, story review.

**Jangan kirim email langsung dari VPS** untuk production karena:

- IP VPS sering punya reputasi rendah.
- Port 25 sering diblok provider.
- Email mudah masuk spam jika SPF/DKIM/DMARC tidak benar.
- Mengelola mail server sendiri lebih rumit daripada pakai provider.

---

## 1. Rekomendasi Provider

| Provider | Cocok Untuk | Free Tier | Harga Lanjutan | Catatan |
|---|---|---:|---:|---|
| **Brevo** | UCP OTP + notifikasi volume kecil/menengah | 300 email/hari | Mulai ± USD 9/bulan | Paling cocok untuk transactional email pemula. UI mudah. |
| **Resend** | Developer-friendly transactional email | 100 email/hari / 3.000 bulan | Mulai ± USD 20/bulan | API modern, setup domain mudah. |
| **Zoho Mail** | Email mailbox branded (`admin@domain`) + SMTP basic | Free plan terbatas | Mulai ± USD 1/user/bulan | Bagus untuk alamat email tim, bukan khusus high-volume OTP. |
| **Mailgun** | Transactional email teknis | Trial terbatas | Pay-as-you-go | Bagus, tapi setup billing/domain lebih teknis. |
| **Amazon SES** | Volume besar, paling murah | Tidak praktis untuk pemula | ± USD 0.10 / 1.000 email | Murah, tapi verifikasi production access lebih ribet. |
| **Gmail SMTP** | Testing lokal | Gratis | Gratis | Tidak direkomendasikan untuk production; rate-limit dan sering blocked. |

## 2. Rekomendasi Final

Untuk PAHLAWAN ROLEPLAY:

### Opsi A — Simpel dan Aman untuk Alpha/Beta: **Brevo**

Pilih Brevo jika ingin cepat jalan untuk OTP UCP dan panel email.

- Free tier cukup untuk Alpha/Beta: **300 email/hari**.
- SMTP credentials mudah dibuat.
- Dashboard jelas untuk melihat email delivered/bounced.
- Tidak perlu setup mailbox penuh.

### Opsi B — Jika Butuh Email Branded Tim: **Zoho Mail + Brevo**

Gunakan kombinasi:

- **Zoho Mail** untuk mailbox manusia:
  - `admin@<domain>`
  - `support@<domain>`
  - `infra@<domain>`
- **Brevo** untuk email otomatis:
  - OTP UCP
  - reset password
  - notifikasi sistem

### Opsi C — Production Besar: **Amazon SES**

Pakai SES nanti kalau volume email sudah besar dan tim sudah siap handle deliverability.

---

## 3. Domain Email yang Dipakai

Disarankan pakai alamat berikut:

| Email | Tujuan |
|---|---|
| `noreply@<domain>` | OTP UCP, reset password, notifikasi otomatis |
| `admin@<domain>` | Admin Pterodactyl / panel owner |
| `support@<domain>` | Bantuan player / tiket |
| `infra@<domain>` | Notifikasi VPS, Cloudflare, Pterodactyl infra |

Contoh jika domain `pahlawan-roleplay.id`:

```txt
noreply@pahlawan-roleplay.id
admin@pahlawan-roleplay.id
support@pahlawan-roleplay.id
infra@pahlawan-roleplay.id
```

---

## 4. Setup Brevo SMTP (Rekomendasi Utama)

### 4.1. Buat Akun Brevo

1. Buka https://www.brevo.com/
2. Klik **Sign up free**.
3. Daftar pakai email utama project.
4. Verifikasi email.
5. Lengkapi profil:
   - Company/Project: `PAHLAWAN ROLEPLAY`
   - Website: `https://<domain>`
   - Use case: Transactional emails / SMTP.

### 4.2. Tambahkan Sender Domain

1. Masuk Brevo Dashboard.
2. Buka **Settings** → **Senders & IP** → **Domains**.
3. Klik **Add a domain**.
4. Masukkan domain: `<domain>` (contoh `pahlawan-roleplay.id`).
5. Brevo akan memberi record DNS untuk SPF, DKIM, dan tracking.

### 4.3. Tambahkan DNS Records di Cloudflare

Cloudflare → domain → **DNS** → **Records**.

Tambahkan record yang diberikan Brevo. Biasanya bentuknya seperti:

| Type | Name | Value | Proxy |
|---|---|---|---|
| TXT | `@` atau domain root | `v=spf1 include:spf.brevo.com ~all` | DNS only |
| TXT/CNAME | `brevo._domainkey` atau selector DKIM | Value dari Brevo | DNS only |
| CNAME | tracking domain (opsional) | Value dari Brevo | DNS only |

> **Penting:** DNS record email harus **DNS only**, jangan Cloudflare proxied.

Jika sebelumnya sudah ada SPF dari Zoho/Gmail, gabungkan dalam satu SPF record. Contoh:

```txt
v=spf1 include:spf.brevo.com include:zoho.com include:_spf.google.com ~all
```

**Jangan buat 2 SPF record berbeda** untuk domain yang sama. Itu bisa bikin SPF invalid.

### 4.4. Verifikasi Domain di Brevo

1. Tunggu 1–15 menit setelah tambah DNS.
2. Di Brevo, klik **Authenticate this domain** / **Verify**.
3. Pastikan status SPF dan DKIM menjadi verified.

Test DNS dari laptop:

```bash
nslookup -type=TXT <domain>
nslookup -type=TXT brevo._domainkey.<domain>
```

### 4.5. Buat SMTP Key

1. Brevo Dashboard → **SMTP & API**.
2. Tab **SMTP**.
3. Klik **Generate a new SMTP key**.
4. Name: `pahlawan-production`.
5. Copy SMTP key sekali saja dan simpan di password manager.

SMTP detail Brevo:

```txt
MAIL_MAILER=smtp
MAIL_HOST=smtp-relay.brevo.com
MAIL_PORT=587
MAIL_USERNAME=<brevo_login_email_or_smtp_login>
MAIL_PASSWORD=<BREVO_SMTP_KEY>
MAIL_ENCRYPTION=tls
MAIL_FROM_ADDRESS=noreply@<domain>
MAIL_FROM_NAME="PAHLAWAN ROLEPLAY"
```

### 4.6. Test SMTP dari VPS

Install `swaks`:

```bash
sudo apt update
sudo apt install -y swaks
```

Kirim test email:

```bash
swaks --to your-personal-email@gmail.com \
  --from noreply@<domain> \
  --server smtp-relay.brevo.com \
  --port 587 \
  --auth LOGIN \
  --auth-user <BREVO_SMTP_LOGIN> \
  --auth-password '<BREVO_SMTP_KEY>' \
  --tls \
  --header "Subject: PAHLAWAN SMTP Test" \
  --body "SMTP test dari VPS PAHLAWAN ROLEPLAY berhasil."
```

Expected:

- `250 OK` dari SMTP server.
- Email masuk ke inbox/spam Gmail.
- Di Brevo dashboard, email muncul sebagai delivered atau sent.

---

## 5. Setup Zoho Mail (Mailbox Branded)

Gunakan Zoho jika ingin email manusia seperti `admin@domain` dan `support@domain`.

### 5.1. Buat Akun Zoho Mail

1. Buka https://www.zoho.com/mail/
2. Pilih plan Free / Mail Lite.
3. Tambahkan domain `<domain>`.
4. Ikuti verifikasi domain via TXT record.

### 5.2. Tambahkan MX Records

Cloudflare DNS → hapus MX lama jika ada → tambahkan MX dari Zoho, biasanya:

| Type | Name | Mail server | Priority |
|---|---|---|---:|
| MX | `@` | `mx.zoho.com` | 10 |
| MX | `@` | `mx2.zoho.com` | 20 |
| MX | `@` | `mx3.zoho.com` | 50 |

### 5.3. Tambahkan SPF/DKIM

SPF contoh:

```txt
v=spf1 include:zoho.com ~all
```

Jika Brevo juga dipakai:

```txt
v=spf1 include:spf.brevo.com include:zoho.com ~all
```

DKIM: generate dari Zoho Admin Console, lalu tambah TXT record sesuai instruksi Zoho.

### 5.4. Buat Mailbox

Buat mailbox:

- `admin@<domain>`
- `support@<domain>`
- `infra@<domain>`

Untuk SMTP Zoho:

```txt
MAIL_HOST=smtp.zoho.com
MAIL_PORT=587
MAIL_USERNAME=infra@<domain>
MAIL_PASSWORD=<ZOHO_APP_PASSWORD>
MAIL_ENCRYPTION=tls
MAIL_FROM_ADDRESS=infra@<domain>
MAIL_FROM_NAME="PAHLAWAN ROLEPLAY"
```

> **Catatan:** Pakai **App Password**, bukan password login utama.

---

## 6. DMARC (Wajib untuk Deliverability)

Tambahkan TXT record DMARC di Cloudflare:

| Type | Name | Value |
|---|---|---|
| TXT | `_dmarc` | `v=DMARC1; p=quarantine; rua=mailto:dmarc@<domain>; fo=1` |

Untuk awal, boleh pakai mode monitoring:

```txt
v=DMARC1; p=none; rua=mailto:dmarc@<domain>; fo=1
```

Setelah email stabil, naikkan ke:

```txt
v=DMARC1; p=quarantine; rua=mailto:dmarc@<domain>; fo=1
```

Production ketat:

```txt
v=DMARC1; p=reject; rua=mailto:dmarc@<domain>; fo=1
```

---

## 7. Konfigurasi di Pterodactyl Panel

File host:

```bash
sudo nano /var/www/pterodactyl/.env
```

Tambahkan / update:

```env
MAIL_MAILER=smtp
MAIL_HOST=smtp-relay.brevo.com
MAIL_PORT=587
MAIL_USERNAME=<BREVO_SMTP_LOGIN>
MAIL_PASSWORD=<BREVO_SMTP_KEY>
MAIL_ENCRYPTION=tls
MAIL_FROM_ADDRESS=noreply@<domain>
MAIL_FROM_NAME="PAHLAWAN ROLEPLAY Panel"
```

Apply:

```bash
cd /var/www/pterodactyl
sudo php artisan config:clear
sudo php artisan cache:clear
sudo systemctl restart pteroq
```

Test dari Panel:

1. Logout dari Pterodactyl.
2. Klik **Forgot Password**.
3. Masukkan email admin.
4. Pastikan email reset password masuk.

---

## 8. Konfigurasi di UCP Website

File repo VPS:

```bash
nano /opt/pahlawan-roleplay/WEBSITE/.env
```

Tambahkan / update:

```env
MAIL_MAILER=smtp
MAIL_HOST=smtp-relay.brevo.com
MAIL_PORT=587
MAIL_USERNAME=<BREVO_SMTP_LOGIN>
MAIL_PASSWORD=<BREVO_SMTP_KEY>
MAIL_ENCRYPTION=tls
MAIL_FROM_ADDRESS=noreply@<domain>
MAIL_FROM_NAME="PAHLAWAN ROLEPLAY"
```

Restart UCP dari Pterodactyl Panel:

1. Servers → `PAHLAWAN UCP Website`
2. Klik **Restart**
3. Cek console untuk error SMTP/PHP.

Test UCP:

- Register akun baru.
- Trigger email OTP.
- Pastikan email OTP terkirim.

---

## 9. Penyimpanan Secret

Simpan di password manager, bukan di Git:

```txt
SMTP_PROVIDER        = Brevo
SMTP_HOST            = smtp-relay.brevo.com
SMTP_PORT            = 587
SMTP_USERNAME        = <BREVO_SMTP_LOGIN>
SMTP_PASSWORD        = <BREVO_SMTP_KEY>
SMTP_FROM_ADDRESS    = noreply@<domain>
SMTP_FROM_NAME       = PAHLAWAN ROLEPLAY
BREVO_ACCOUNT_EMAIL  = <login email>
BREVO_DASHBOARD_URL  = https://app.brevo.com/
```

**Jangan pernah commit:**

- SMTP key
- app password Zoho
- `.env` production
- screenshot dashboard yang menampilkan key

---

## 10. Troubleshooting

### Email tidak masuk

Cek:

- Spam folder.
- Brevo dashboard → Transactional → Logs.
- SPF/DKIM domain status di Brevo.
- `MAIL_FROM_ADDRESS` harus domain yang sudah diverifikasi.

### SMTP authentication failed

Cek:

- Username SMTP benar (bukan selalu email login; lihat Brevo SMTP page).
- Password menggunakan SMTP key, bukan password akun.
- Port 587 + TLS.

### SPF invalid

Biasanya karena ada lebih dari satu TXT SPF record. Harus digabung menjadi satu:

```txt
v=spf1 include:spf.brevo.com include:zoho.com ~all
```

### Gmail menandai spam

Pastikan:

- SPF verified.
- DKIM verified.
- DMARC ada.
- Subject/body tidak spammy.
- Domain baru biasanya butuh warming-up, kirim sedikit dulu.

---

## 11. Checklist SMTP Setup

- [ ] Akun SMTP provider dibuat (rekomendasi: Brevo).
- [ ] Domain ditambahkan ke provider.
- [ ] SPF record ditambahkan.
- [ ] DKIM record ditambahkan.
- [ ] DMARC record ditambahkan.
- [ ] Domain status verified di provider.
- [ ] SMTP key dibuat dan disimpan di password manager.
- [ ] Test `swaks` dari VPS berhasil.
- [ ] Pterodactyl `.env` MAIL_* sudah diisi.
- [ ] Pterodactyl forgot password email berhasil.
- [ ] UCP `.env` MAIL_* sudah diisi.
- [ ] UCP OTP/register email berhasil.

---

## 12. Next Step

Setelah SMTP siap:

1. Lanjut setup VPS dari [`VPS_SETUP_GUIDE.md`](./VPS_SETUP_GUIDE.md).
2. Saat bagian email di setup guide, gunakan kredensial dari dokumen ini.
3. Setelah Pterodactyl dan UCP running, lakukan test reset password + OTP.
