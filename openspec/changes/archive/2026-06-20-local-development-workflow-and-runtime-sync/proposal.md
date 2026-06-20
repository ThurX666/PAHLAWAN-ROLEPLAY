## Why

Workflow local development Pahlawan Roleplay di PC perlu distandarkan agar repo utama tetap aman sebagai source of truth, sementara XAMPP hanya dipakai sebagai target runtime lokal. Tanpa aturan yang jelas tentang kapan memakai `npm run dev`, kapan build frontend, kapan sync ke `htdocs`, dan bagaimana menangani `.env` private serta rollback runtime lokal, update harian mudah menimbulkan drift atau merusak workspace.

## What Changes

- Tambah capability workflow local development Website/UCP yang mendefinisikan boundary repo vs XAMPP runtime, alur frontend dev/build, alur PHP API lokal, handling `.env` private, checklist testing lokal, dan strategi sync/copy ke runtime XAMPP.
- Definisikan kapan developer memakai `npm run dev`, `npm run build`, PHP built-in server, dan kapan runtime XAMPP lokal memang perlu dipakai.
- Definisikan checklist reset/rollback runtime lokal agar developer bisa memperbarui runtime XAMPP tanpa memindahkan repo utama dan tanpa mengubah source of truth.
- Tegaskan bahwa private `.env`, credential, token, session, cookie, OTP, SMTP detail, dan provider error tidak boleh masuk repo atau log workflow yang ditrack.

## Capabilities

### New Capabilities
- `ucp-local-development-workflow`: Workflow local development PC untuk Website/UCP dengan boundary repo-vs-XAMPP, frontend/PHP runtime flow, testing checklist, sync runtime lokal, dan local rollback/reset guidance.

### Modified Capabilities
- None.

## Impact

- OpenSpec artifacts untuk workflow local development Website/UCP.
- Dokumentasi operasional repo `C:\Users\guyub\Documents\PAHLAWAN ROLEPLAY` dan target runtime lokal `C:\xampp\htdocs\pahlawan_roleplay`.
- Checklist penggunaan `npm run dev`, `npm run build`, PHP built-in server, XAMPP Apache, sync/copy runtime, dan reset lokal.
- Tidak mengubah BOT runtime, Pawn/gamemode, database schema, migration, atau behavior runtime yang sudah ada.
