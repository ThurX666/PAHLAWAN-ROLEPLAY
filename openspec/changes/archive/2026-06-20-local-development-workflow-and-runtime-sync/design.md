## Context

Repo utama Pahlawan Roleplay tetap berada di `C:\Users\guyub\Documents\PAHLAWAN ROLEPLAY` dan tidak boleh dipindahkan ke XAMPP. Namun kebutuhan lokal sehari-hari mencampur beberapa mode kerja: frontend Vite dev server, frontend production build lokal, PHP built-in server dari repo, dan runtime flattened XAMPP di `C:\xampp\htdocs\pahlawan_roleplay`. Tanpa workflow yang eksplisit, developer bisa salah memperlakukan XAMPP sebagai source of truth, menimpa runtime lokal tanpa checklist, atau memakai mode dev/build yang tidak sesuai tujuan test.

Stakeholder utama change ini adalah developer lokal dan operator local test. Constraint utama:
- repo tetap source of truth
- XAMPP hanya target runtime lokal, bukan tempat coding utama
- private `.env` tetap private
- tidak boleh mengubah runtime behavior
- tidak boleh melebar ke BOT runtime, Pawn/gamemode, atau database schema

## Goals / Non-Goals

**Goals:**
- Mendefinisikan workflow local development PC yang konsisten untuk repo utama, frontend dev/build, PHP API lokal, local `.env`, testing checklist, sync ke XAMPP, dan reset/rollback runtime lokal.
- Menentukan kapan memakai `npm run dev`, `npm run build`, PHP built-in server, dan kapan benar-benar perlu menjalankan runtime XAMPP lokal.
- Menentukan boundary yang jelas antara source code di repo dan hasil sync/copy runtime lokal di `htdocs`.
- Menyediakan dasar OpenSpec agar implementasi dokumentasi/checklist berikutnya bisa dikerjakan tanpa ambiguity.

**Non-Goals:**
- Tidak memindahkan repo utama ke XAMPP.
- Tidak membuat automation sync/deploy script pada change ini.
- Tidak mengubah endpoint, auth flow, BOT runtime, Pawn/gamemode, atau database schema.
- Tidak membahas bootstrap VPS production; itu tetap future change terpisah.

## Decisions

### 1. Pisahkan mode kerja repo-dev dan runtime-XAMPP
- Keputusan: repo utama tetap menjadi tempat coding, sedangkan XAMPP hanya runtime target yang menerima hasil sync/copy seperlunya.
- Alasan: ini menjaga source of truth tetap bersih dan mencegah drift local runtime menjadi "repo kedua".
- Alternatif:
  - Coding langsung di `htdocs`: ditolak karena rawan drift dan sulit ditrack.

### 2. Bedakan dev-flow dan build-flow frontend
- Keputusan: `npm run dev` dipakai untuk iterasi frontend harian yang butuh HMR/proxy lokal, sedangkan `npm run build` dipakai hanya untuk validasi production build lokal atau saat akan sync runtime flattened.
- Alasan: kebutuhan debugging harian berbeda dari kebutuhan mensimulasikan runtime deployed.
- Alternatif:
  - Selalu build untuk setiap perubahan: ditolak karena terlalu lambat untuk iterasi harian.

### 3. Tetapkan PHP built-in server sebagai baseline local API source-of-truth
- Keputusan: `php -S 127.0.0.1:8000 -t WEBSITE/public` dari repo menjadi baseline untuk test source code lokal, sementara XAMPP Apache hanya dipakai saat perlu memverifikasi runtime flattened local.
- Alasan: built-in server paling langsung menguji source repo tanpa sync tambahan.
- Alternatif:
  - Selalu pakai XAMPP untuk semua test: ditolak karena membuat dev flow tergantung pada sync runtime.

### 4. Dokumentasikan reset/rollback runtime lokal sebagai langkah aman
- Keputusan: rollback/reset local runtime harus menjadi bagian workflow, bukan catatan tambahan.
- Alasan: developer perlu cara aman untuk membuang runtime local yang stale tanpa menyentuh repo.
- Alternatif:
  - Mengandalkan hapus/copy manual tanpa checklist: ditolak karena rawan salah sasaran.

## Risks / Trade-offs

- [Developer tetap mengedit runtime XAMPP langsung] -> Mitigasi: runbook harus menegaskan repo sebagai source of truth dan `htdocs` sebagai target sync saja.
- [Build flow dan dev flow tercampur] -> Mitigasi: dokumentasikan kapan pakai `npm run dev` vs `npm run build` secara eksplisit.
- [Local runtime stale setelah sync parsial] -> Mitigasi: tambahkan reset/rollback runtime lokal dan checklist post-sync minimum.
- [`.env` private ikut terbawa ke repo atau log] -> Mitigasi: tegaskan aturan track-vs-private dan evidence/log lokal yang aman.

## Migration Plan

1. Tambahkan proposal, design, spec delta, dan task checklist untuk workflow local development.
2. Review boundary repo vs XAMPP target dengan owner/developer lokal.
3. Implementasi dokumentasi/checklist dilakukan setelah change ini di-approve.
4. Setelah implementasi selesai, developer lokal memakai workflow standar untuk iterasi harian dan validasi runtime lokal.

## Open Questions

- Apakah local database akan tetap memakai development DB yang ada atau perlu baseline reset/clone workflow terpisah?
- Folder/file apa saja yang paling aman untuk disync ke XAMPP secara manual saat validasi runtime flattened?
- Apakah local sync ke XAMPP nantinya perlu helper script terpisah, atau cukup runbook manual pada tahap awal?
