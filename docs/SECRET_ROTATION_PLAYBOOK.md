# Secret Rotation and Repo Exposure Playbook

Dokumen ini menetapkan langkah aman jika ada indikasi secret exposure di repo public PAHLAWAN ROLEPLAY.

## High Priority Secret Types

- Discord bot token
- OpenAI, NVIDIA, atau provider API key lain
- credential database
- SMTP credential
- session atau cookie secret
- webhook secret
- file `.env` privat dan isi setaranya

## Kapan Perlu Rotasi Preventif

Lakukan rotasi preventif jika salah satu kondisi berikut terjadi:

- secret pernah dipakai sebelum repo menjadi public
- secret sempat tersimpan di file tracked, log, screenshot, atau paste eksternal
- ada indikasi maintainer atau contributor salah commit file privat
- ada keraguan apakah secret pernah dibagikan ke lingkungan yang tidak terkontrol
- provider atau platform terkait merekomendasikan rotasi berkala

## Respons Jika Ada Indikasi Exposure

1. Jangan publikasikan nilai secret di issue, PR, chat, atau commit.
2. Catat hanya `path`, jenis indikasi, `risk level`, dan rekomendasi aksi.
3. Verifikasi apakah temuan adalah secret nyata, placeholder, fixture test, atau env reference.
4. Jika ada kemungkinan secret valid terekspos, lakukan rotasi di sistem privat terkait secepat mungkin.
5. Hapus atau ganti nilai sensitif dari file tracked melalui PR terpisah yang aman.
6. Review scope dampak: current tree, branch terkait, history, dan sistem eksternal yang memakai secret tersebut.
7. Dokumentasikan hasil triage tanpa menuliskan nilai secret.

## Format Laporan Aman

Gunakan format berikut saat melaporkan temuan:

- `path`: lokasi file atau area terdampak
- `jenis indikasi`: misalnya token, API key, credential database, secret env, atau webhook
- `risk level`: rendah, sedang, atau tinggi
- `rekomendasi`: rotasi, removal, placeholder replacement, atau review lanjutan

Jangan pernah menuliskan nilai secret, potongan token, credential parsial, atau URL ber-credential.

## Guardrail Kontributor

- gunakan placeholder aman pada file tracked
- simpan secret runtime hanya di file privat seperti `.env` lokal atau secret manager yang sesuai
- baca ulang diff sebelum PR untuk memastikan tidak ada secret atau file privat ikut staged
- jika ragu, hentikan push dan minta review maintainer

## Catatan Operasional

- playbook ini tidak mengubah runtime behavior
- rotasi secret dilakukan di lingkungan privat, bukan di repo public
- scan otomatis seperti Gitleaks atau TruffleHog boleh dipakai sebagai second-opinion read-only jika maintainer menyetujui
