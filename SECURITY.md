# Security Policy

## Supported Status

Repo ini aktif dikembangkan, tetapi belum semua area memiliki hardening dan coverage yang sama. Prioritas utama saat ini adalah:

- pencegahan secret leak
- hardening auth/session UCP
- review konfigurasi publik vs privat
- validasi workflow release dan maintenance

## Cara Melapor

Jangan laporkan secret, credential, token, cookie, session, OTP, atau langkah eksploit detail di issue publik.

Untuk laporan security:

1. Kirim laporan privat ke maintainer inti melalui kanal privat yang disepakati.
2. Sertakan ringkasan dampak, komponen terdampak, langkah reproduksi minimum, dan saran mitigasi jika ada.
3. Tunggu konfirmasi sebelum mempublikasikan detail.

Jika belum ada kanal privat yang diumumkan di repo, buka issue publik tanpa detail eksploit dan minta kontak disclosure privat.

Untuk indikasi secret exposure dan rotasi preventif, ikuti [docs/SECRET_ROTATION_PLAYBOOK.md](/C:/Users/guyub/Documents/PAHLAWAN%20ROLEPLAY/docs/SECRET_ROTATION_PLAYBOOK.md).

## Yang Tidak Boleh Dipublish

- `.env`
- token Discord
- API key
- credential database
- SMTP credential
- cookie, session, OTP
- dump database privat
- log yang berisi data sensitif
- nilai live di file example atau config tracked

## Ruang Lingkup Sensitif

- `BOT/config.json`
- `BOT/PHRP-AI/config/*.json`
- `WEBSITE/.env`
- `WEBSITE/public/api/config.php`
- `WEBSITE/public/api/config.php.example` harus tetap placeholder-only
- `GAMEMODE/server.cfg`
- `DATABASE/*`

Untuk `DATABASE`, hanya schema, migration, example SQL aman, dan fixture dummy/test yang boleh ada di repo public. Lihat [docs/DATABASE_POLICY.md](/C:/Users/guyub/Documents/PAHLAWAN%20ROLEPLAY/docs/DATABASE_POLICY.md).

## Secret Rotation

Secret high priority yang harus mendapat perhatian tercepat:

- token Discord bot
- OpenAI, NVIDIA, atau provider API key lain
- credential database
- SMTP credential
- session atau cookie secret
- webhook secret
- file `.env` privat dan isi setaranya

Jika ada indikasi exposure atau keraguan terhadap riwayat penggunaan secret, lakukan triage dan rotasi preventif sesuai [docs/SECRET_ROTATION_PLAYBOOK.md](/C:/Users/guyub/Documents/PAHLAWAN%20ROLEPLAY/docs/SECRET_ROTATION_PLAYBOOK.md).

## Responsible Disclosure

Maintainer berusaha meninjau laporan valid secepat mungkin, memverifikasi dampak, menyiapkan perbaikan, lalu mengumumkan secara aman bila perlu. Mohon beri waktu untuk triage dan mitigasi sebelum disclosure publik.
