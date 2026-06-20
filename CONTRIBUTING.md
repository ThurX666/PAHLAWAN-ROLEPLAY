# Contributing to PAHLAWAN ROLEPLAY

Terima kasih. Repo ini menerima kontribusi yang kecil, jelas, dan aman.

## Aturan Utama

- Jangan commit secret, `.env`, token, cookie, session, OTP, dump database, atau credential lain.
- Jangan ubah runtime behavior di luar scope PR.
- Jangan campur banyak fitur besar dalam satu PR.
- Untuk perubahan menengah atau berisiko, cek OpenSpec lebih dulu.

## Workflow Kontribusi

1. Fork atau buat branch kerja dari branch terbaru.
2. Pilih scope yang kecil dan reviewable.
3. Cek apakah ada OpenSpec change aktif atau spec utama yang relevan.
4. Lakukan perubahan seperlunya.
5. Jalankan validasi yang relevan.
6. Baca ulang diff sebelum membuka PR.

## Branch dan PR

- Gunakan nama branch yang deskriptif
- Jelaskan tujuan, scope, risiko, dan hasil validasi di PR
- Jika ada perubahan docs/spec, sebutkan spec yang relevan

## Style Aman

- Jangan expose nilai private di contoh config
- Gunakan placeholder pada file tracked
- Pertahankan perubahan tetap sempit
- Untuk gamemode Pawn, cek include, callback, dan flow yang sudah ada sebelum menambah kode
- Untuk bot Discord, hormati flow `deferReply`, `reply`, dan `editReply`
- Untuk website/UCP, jaga auth flow, validasi server-side, dan session safety

## Checklist Sebelum PR

- Scope sesuai tujuan
- Tidak ada secret atau file privat ikut staged
- Tidak ada perubahan runtime yang tidak direncanakan
- Diff sudah dibaca ulang
- Validasi relevan sudah dijalankan

## Diskusi

Untuk ide fitur besar, bug lintas modul, atau perubahan arsitektur, buka issue dulu sebelum coding besar agar scope dan risk bisa disepakati.
