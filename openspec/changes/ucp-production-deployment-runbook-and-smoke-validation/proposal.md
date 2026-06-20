## Why

Pahlawan Roleplay sudah punya baseline runtime UCP yang lebih rapi, tetapi launch komunitas tetap berisiko tanpa runbook deployment yang eksplisit, checklist package/runtime yang konsisten, dan smoke validation terotorisasi yang bisa dijalankan tanpa membuka secret. Change ini dibutuhkan sekarang agar deploy production, sync ke XAMPP runtime, dan rollback bisa dilakukan secara repeatable sebelum traffic komunitas meningkat.

## What Changes

- Tambah capability runbook deployment production UCP yang mendefinisikan checklist package deploy, pemetaan layout repo ke XAMPP/htdocs, dan kontrak env production vs local.
- Definisikan validasi pasca-deploy yang aman untuk build frontend, vendor/composer readiness, API/runtime diagnostics, auth/session smoke, email runtime readiness, dan asset smoke checks tanpa membuka secret.
- Definisikan rollback checklist dan launch readiness checklist agar operator bisa menghentikan, memverifikasi, atau membatalkan deploy dengan langkah yang konsisten.
- Tegaskan bahwa semua smoke test production harus terotorisasi, bounded, dan tidak boleh membuka `.env`, credential, cookie, session, OTP, SMTP detail, atau provider error.

## Capabilities

### New Capabilities
- `ucp-production-deployment-runbook`: Runbook deployment production Website/UCP yang mencakup package checklist, env contract, XAMPP/runtime sync, authorized smoke validation, rollback, dan launch readiness.

### Modified Capabilities
- None.

## Impact

- OpenSpec artifacts untuk Website/UCP deployment dan operasi launch.
- Dokumentasi operasional untuk layout repo `WEBSITE/...` dan layout flattened deployment `C:\\xampp\\htdocs\\pahlawan_roleplay`.
- Checklist validasi untuk build frontend, vendor/composer readiness, API health/session/email diagnostics, dan smoke checks terotorisasi.
- Tidak mengubah BOT runtime, Pawn/gamemode, database schema, migration, atau behavior production yang sudah ada.
