# Local Validation Matrix

Dokumen ini merangkum validasi lokal minimum untuk `GAMEMODE`, `WEBSITE`, `BOT`, OpenSpec, dan MCP tanpa mengubah runtime behavior atau membuka secret.

## Aturan Umum

- Jangan publish atau salin `.env`, token, credential, cookie, session, OTP, webhook URL, API key, atau dump database ke file tracked.
- Jalankan check terkecil yang relevan dengan area yang disentuh.
- Jangan menjalankan database write, migrasi, bot login, atau sync XAMPP tanpa persetujuan eksplisit.
- Treat `C:\xampp\htdocs\pahlawan_roleplay` sebagai runtime target, bukan source of truth.

## Matrix

| Area | Check minimum | Kapan wajib | Expected outcome | Evidence terbaru |
| --- | --- | --- | --- | --- |
| OpenSpec | `openspec validate --specs --strict` | Perubahan planning/spec/docs workflow | Semua spec valid | 11 passed, 0 failed |
| MCP | `health_check` dan `validate_mcp_environment` | Sebelum broad analysis | Read-only, redact secrets, write DB/files disabled | OK; MySQL/Pawn compiler MCP belum configured |
| `WEBSITE` frontend | `npm run build` dari `WEBSITE` | Ubah frontend UCP | Vite build selesai tanpa error | Pass; 2449 modules transformed |
| `WEBSITE` preview | `npm run preview` lalu cek `/` dan asset utama | Setelah build atau UI change | HTTP 200 untuk halaman dan asset utama | Pass; `/` dan JS utama HTTP 200 |
| `WEBSITE` PHP contracts | Jalankan standalone tests dengan XAMPP PHP | Ubah PHP helper/config/API contract | Test mandiri lulus tanpa DB live write | Pass; 6 standalone tests lulus |
| `WEBSITE` API live | Jalankan endpoint lokal dengan private env | Hanya jika API runtime berubah dan env aman tersedia | Endpoint sehat tanpa expose secret | Belum dijalankan |
| `BOT` syntax | `node --check` semua JS non-`node_modules` | Ubah BOT JS | Tidak ada syntax error | Pass; 60 JS files checked |
| `BOT` runtime | `npm start` | Hanya jika token/target Discord aman dikonfirmasi | Bot start tanpa secret leak | Belum dijalankan |
| `GAMEMODE` compile | `pawncc.exe` ke output temp | Ubah Pawn source/include | Compile sukses tanpa error baru | Pass; 19 existing warnings |
| `GAMEMODE` runtime | Boot server lokal | Hanya jika plugin/config runtime aman tersedia | Server start untuk smoke dasar | Belum dijalankan |
| `DATABASE` | MCP/schema/read-only SELECT | Ubah DB-backed feature | Evidence read-only dan bounded | DB MCP belum configured |

## Perintah Aman yang Sudah Dipakai

### UCP build

```powershell
cd WEBSITE
npm run build
```

### UCP standalone PHP contracts

```powershell
cd WEBSITE
C:\xampp\php\php.exe .\tests\app_config_contract_test.php
C:\xampp\php\php.exe .\tests\discord_config_contract_test.php
C:\xampp\php\php.exe .\tests\email_otp_endpoint_contract_test.php
C:\xampp\php\php.exe .\tests\email_runtime_diagnostic_contract_test.php
C:\xampp\php\php.exe .\tests\mail_runtime_contract_test.php
C:\xampp\php\php.exe .\tests\story_review_ai_contract_test.php
```

### BOT syntax

```powershell
Get-ChildItem .\BOT -Recurse -Filter *.js |
  Where-Object { $_.FullName -notmatch '\\node_modules\\' } |
  ForEach-Object { node --check $_.FullName }
```

### GAMEMODE compile to temp

```powershell
cd GAMEMODE
$outDir = Join-Path $env:TEMP ('phrp-pawn-compile-' + [guid]::NewGuid().ToString('N'))
New-Item -ItemType Directory -Force $outDir | Out-Null
.\pawno\pawncc.exe .\gamemodes\main.pwn -i.\pawno\include -i.\gamemodes -o"$outDir\main.amx"
Remove-Item -LiteralPath $outDir -Recurse -Force
```

## Skipped Until Ready

- XAMPP runtime smoke: run only after runtime target is synced from repository artifacts.
- BOT live startup: run only after token safety and target Discord environment are confirmed.
- DB live checks: run only with read-only DB user and bounded queries.
- Pawn warning cleanup: handle under a focused OpenSpec change if warnings become maintenance work.
