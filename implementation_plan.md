# Implementation Plan

## Overview

Membuat panduan langkah demi langkah (step-by-step manual guide) untuk menyelesaikan setup dan konfigurasi seluruh tools yang direkomendasikan dalam dokumen PDF "Strategi Optimalisasi Pengembangan Multi-Proyek PAHLAWAN-ROLEPLAY" — termasuk konfigurasi Cline, RTK, MCP servers, dan OpenSpec — berdasarkan kondisi aktual proyek yang sudah terinstall sebagian.

## Kondisi Aktual yang Terverifikasi

Berdasarkan investigasi sistem, berikut status saat ini:

| Komponen | Status | Detail |
|----------|--------|--------|
| **OpenSpec CLI** | ✅ **Terinstall** | `@fission-ai/openspec@1.4.1` (global npm) |
| **RTK (Rust Token Killer)** | ✅ **Terinstall** | `C:\Tools\rtk\rtk.exe` v0.42.4 |
| **OpenSpec di Proyek** | ⚠️ **Parsial** | Folder `openspec/` sudah ada dengan changes, checkpoints, specs — tapi **tidak ada** `openspec/config.yaml` |
| **Cline VS Code Extension** | ❌ **Belum terinstall** | Tidak ditemukan ekstensi Cline/Claude-dev di VS Code |
| **.clinerules** | ❌ **Belum ada** | RTK belum diinisialisasi untuk Cline |
| **MCP Servers** | ❌ **Belum dikonfigurasi** | Filesystem, MySQL, Playwright, Brave Search belum disetup |
| **OpenSpec VS Code Extensions** | ❌ **Belum terinstall** | Tidak ada ekstensi `AngDrew.openspec-vscode` atau `Codder13.openspec` |
| **RTK Inspector VS Code** | ❌ **Belum terinstall** | Tidak ada ekstensi `petermefrandsen.rtk-inspector` |
| **DeepSeek API Key** | ❌ **Tidak diketahui** | Perlu dicek apakah sudah dimiliki |

## Step-by-Step Manual Guide

### Bagian 1: Setup Awal Lingkungan

#### Step 1: Install VS Code Extensions untuk AI Agent

1. Buka VS Code → Extensions (Ctrl+Shift+X)
2. Cari dan install ekstensi **"Cline"** (publisher: saoudrizwan.claude-dev)
   - Ini adalah AI agent utama yang akan mengerjakan task secara otonom
   - Alternatif: jika ingin yang lebih ringan, install **"Roo Code"** sebagai cadangan
3. Cari dan install ekstensi **"OpenSpec"** oleh **AngDrew** (`AngDrew.openspec-vscode`)
   - Untuk visual dashboard dan "Ralph Loop" automation
   - Alternatif: **"OpenSpec"** oleh **Codder13** (`Codder13.openspec`) — lebih simpel, integrasi CodeLens
4. Cari dan install ekstensi **"RTK Inspector"** (`petermefrandsen.rtk-inspector`)
   - Untuk memonitor penghematan token RTK langsung dari VS Code

#### Step 2: Konfigurasi DeepSeek V4 Flash di Cline

1. Buka VS Code → Klik ikon Cline di Activity Bar (sebelah kiri)
2. Klik gear icon (Settings) di panel Cline
3. Pada **API Provider**, pilih: **"DeepSeek"** atau **"OpenAI Compatible"**
4. Masukkan **DeepSeek API Key** (dari dashboard DeepSeek)
5. Pada **Model ID**, isi: `deepseek-chat`
   - Catatan: model `deepseek-chat` secara otomatis merujuk ke V4/V4 Flash di gateway DeepSeek
6. Jika pakai "OpenAI Compatible":
   - **Base URL**: `https://api.deepseek.com/v1`
   - **API Key**: [DeepSeek API Key kamu]
   - **Model**: `deepseek-chat`
7. Simpan pengaturan

#### Step 3: Inisialisasi RTK untuk Cline

1. Buka terminal (PowerShell sebagai Administrator):
   ```powershell
   # Verifikasi RTK sudah terinstall
   rtk --version
   # Output: rtk 0.42.4
   
   # Inisialisasi RTK untuk agent Cline
   # Ini akan membuat file .clinerules di direktori proyek
   rtk init --agent cline
   ```
2. Verifikasi file `.clinerules` sudah terbentuk:
   ```powershell
   Get-ChildItem -Path ".clinerules" -ErrorAction SilentlyContinue
   ```
3. Edit file `.clinerules` untuk memastikan instruksi RTK aktif:
   - Buka `.clinerules`
   - Tambahkan/pastikan ada aturan agar AI selalu memprioritaskan perintah dengan prefix `rtk`
   - Contoh isi:
     ```
     # RTK Instructions
     - Always use `rtk` prefix for shell commands when possible (e.g., `rtk ls .`, `rtk read file.pwn`, `rtk grep "pattern" .`)
     - Use `rtk git status` instead of `git status`
     - Use `rtk git diff` instead of `git diff`
     - Use `rtk read <file>` instead of `cat <file>` or reading raw files
     - This reduces token consumption by 60-90%
     ```

#### Step 4: Inisialisasi/Reinisialisasi OpenSpec

1. Buka terminal dan jalankan:
   ```powershell
   cd C:\Users\guyub\Documents\PAHLAWAN ROLEPLAY
   
   # Inisialisasi ulang OpenSpec untuk membuat config.yaml
   openspec init
   ```
   **CATATAN**: Karena folder `openspec/` sudah ada, perintah `openspec init` mungkin menolak. Jika terjadi error:
   
2. **Solusi jika openspec init gagal**:
   ```powershell
   # Backup dulu folder openspec yang sudah ada
   Move-Item -Path "openspec" -Destination "openspec-backup"
   
   # Init ulang
   openspec init
   
   # Pindahkan specs, changes, checkpoints dari backup ke yang baru
   Copy-Item -Path "openspec-backup\changes\*" -Destination "openspec\changes\" -Recurse
   Copy-Item -Path "openspec-backup\checkpoints\*" -Destination "openspec\checkpoints\" -Recurse
   Copy-Item -Path "openspec-backup\specs\*" -Destination "openspec\specs\" -Recurse
   
   # Hapus backup setelah selesai
   Remove-Item -Path "openspec-backup" -Recurse
   ```

3. Setelah `openspec/config.yaml` terbentuk, edit isinya:
   ```powershell
   code openspec/config.yaml
   ```
   Isi dengan konfigurasi berikut:
   ```yaml
   schema: spec-driven
   project:
     name: PAHLAWAN-ROLEPLAY
     tech_stack:
       gamemode_samp:
         language: Pawn
         compiler: pawncc 3.10
         conventions: "Gunakan YSI Library (y_inline, y_commands, y_groups) jika memungkinkan. Deklarasikan variabel pemain di dalam enum PlayerData."
       ucp_website:
         language: TypeScript
         framework: "Laravel 11 / React"
         styling: "Tailwind CSS"
         architecture: "Repository Pattern with Controller Isolation"
       discord_bot:
         runtime: "Node.js (v20+)"
         library: "Discord.js v14"
         architecture: "Event-driven Handler with Slash Commands"
     database:
       dialect: MySQL
       primary_key: "UUID (UCP) / Auto-Increment ID (SAMP Players Table)"
   ```

### Bagian 2: Setup MCP Servers

#### Step 5: Setup Filesystem MCP Server

Filesystem MCP diperlukan agar Cline bisa membaca/menulis file di proyek.

1. Buka VS Code → Klik ikon Cline → Settings (gear icon)
2. Scroll ke **MCP Servers** section
3. Klik **"Add MCP Server"**
4. Isi:
   - **Name**: `filesystem`
   - **Type**: `command`
   - **Command**: `npx`
   - **Args**:
     ```
     -y
     @modelcontextprotocol/server-filesystem
     C:\Users\guyub\Documents\PAHLAWAN ROLEPLAY
     ```
5. Klik **Save**
6. Restart Cline

#### Step 6: Setup MySQL MCP Server (Read-Only untuk Produksi)

Untuk koneksi read-only ke database VPS SAMP (aman, tidak bisa write).

1. Buka Cline Settings → MCP Servers → Add MCP Server
2. Isi:
   - **Name**: `mysql-readonly`
   - **Type**: `command`
   - **Command**: `npx`
   - **Args**:
     ```
     -y
     @benborla29/mcp-server-mysql
     ```
3. Buat file konfigurasi `.env.mysql-readonly` di root proyek:
   ```
   MYSQL_HOST=your-vps-ip
   MYSQL_PORT=3306
   MYSQL_USER=readonly_user
   MYSQL_PASSWORD=your_password
   MYSQL_DATABASE=your_database
   MYSQL_SSH=true
   MYSQL_SSH_HOST=your-vps-ip
   MYSQL_SSH_PORT=22
   MYSQL_SSH_USER=root
   MYSQL_SSH_PRIVATE_KEY=~/.ssh/id_rsa
   ```
   **PERINGATAN**: File `.env.*` jangan di-commit ke git. Pastikan sudah di `.gitignore`.

#### Step 7: Setup MySQL MCP Server (Write untuk Local Dev)

Untuk koneksi ke database lokal (localhost) untuk development fitur baru.

1. Cline Settings → MCP Servers → Add MCP Server
2. Isi:
   - **Name**: `mysql-write-local`
   - **Type**: `command`
   - **Command**: `npx`
   - **Args**:
     ```
     -y
     @benborla29/mcp-server-mysql
     ```
3. Buat file konfigurasi `.env.mysql-local`:
   ```
   MYSQL_HOST=localhost
   MYSQL_PORT=3306
   MYSQL_USER=root
   MYSQL_PASSWORD=local_password
   MYSQL_DATABASE=pahlawan_dev
   ```

#### Step 8: Setup Playwright MCP Server

Untuk testing UI UCP secara otomatis (simulasi browser).

1. Pastikan Node.js sudah terinstall (v18+)
2. Cline Settings → MCP Servers → Add MCP Server
3. Isi:
   - **Name**: `playwright`
   - **Type**: `command`
   - **Command**: `npx`
   - **Args**:
     ```
     -y
     @playwright/mcp
     ```
4. Install browser Chromium untuk Playwright:
   ```powershell
   npx playwright install chromium
   ```

#### Step 9: Setup Brave Search MCP Server

Untuk mencari dokumentasi online.

1. Daftar/dapatkan **Brave Search API Key** dari [brave.com/search/api](https://brave.com/search/api)
2. Cline Settings → MCP Servers → Add MCP Server
3. Isi:
   - **Name**: `brave-search`
   - **Type**: `command`
   - **Command**: `npx`
   - **Args**:
     ```
     -y
     @modelcontextprotocol/server-brave-search
     ```
4. Set environment variable:
   ```powershell
   $env:BRAVE_API_KEY="your-brave-api-key"
   ```
   Atau set permanent via Windows Environment Variables GUI:
   - Search "Environment Variables" di Start
   - Add System Variable: `BRAVE_API_KEY` = `your-api-key`

### Bagian 3: Integrasi & Testing

#### Step 10: Verifikasi Semua MCP Server Berjalan

1. Buka VS Code → Cline panel
2. Cek di bagian **MCP Servers**:
   - ✅ filesystem — Connected
   - ✅ mysql-readonly — Connected
   - ✅ mysql-write-local — Connected  (opsional, hanya jika butuh)
   - ✅ playwright — Connected
   - ✅ brave-search — Connected
3. Jika ada yang error, klik nama server untuk melihat log error

#### Step 11: Test RTK Berfungsi

1. Buka terminal PowerShell di proyek
2. Jalankan perintah test:
   ```powershell
   # Test gain (statistik penghematan)
   rtk gain
   
   # Test command dengan RTK
   rtk ls .
   
   # Test read file
   rtk read AGENTS.md
   
   # Test git status
   rtk git status
   ```
3. Buka RTK Inspector di VS Code (ikon baru di Activity Bar)
4. Verifikasi statistik penghematan muncul

#### Step 12: Test OpenSpec Berfungsi

1. Buka terminal:
   ```powershell
   # Cek status OpenSpec
   openspec --version
   
   # Coba explore mode (test tanpa mengubah file)
   openspec explore "analisis struktur database saat ini"
   
   # Atau lewat Cline: gunakan perintah di chat
   # /opsx:explore analisis struktur database saat ini
   ```
2. Pastikan folder `openspec/changes/` dan `openspec/specs/` masih intact

#### Step 13: Workflow Harian yang Direkomendasikan

Setelah semua setup selesai, workflow pengembangan harian:

1. **Mulai fitur baru**:
   - Di Cline chat: `/opsx:propose [nama-fitur]`
   - → OpenSpec bikin proposal, design, tasks.md

2. **Implementasi**:
   - Di Cline chat: `/opsx:apply`
   - → Cline baca tasks.md dan eksekusi step-by-step
   - Atau via "Ralph Loop" (jika pakai AngDrew extension):
     ```
     node ralph_opencode.mjs --attach http://localhost:4099 --change [nama-fitur] --count 2
     ```

3. **Testing**:
   - Cline otomatis panggil Playwright untuk test UI
   - Cline otomatis cek database via MCP mysql-readonly

4. **Selesai**:
   - `/opsx:archive`
   - → OpenSpec update specs utama dan archive perubahan

### Bagian 4: Troubleshooting & Catatan Penting

#### Masalah yang Mungkin Muncul

1. **Cline tidak muncul di VS Code**:
   - Pastikan ekstensi Cline terinstall dengan benar
   - Coba reload VS Code Window (Ctrl+Shift+P → "Reload Window")
   - Periksa VS Code version (minimal v1.85+)

2. **MCP Server gagal konek**:
   - Pastikan command `npx` tersedia (`npx --version`)
   - Cek log error di Cline → MCP Servers
   - Untuk MySQL: pastikan SSH key path benar

3. **RTK command not recognized**:
   - Pastikan `C:\Tools\rtk\` ada di PATH environment variable
   - Buka System Properties → Environment Variables → Edit PATH → Add `C:\Tools\rtk`

4. **OpenSpec init gagal karena folder sudah ada**:
   - Backup dulu folder `openspec/`
   - Hapus folder `openspec/`
   - Jalankan `openspec init`
   - Restore folder changes, checkpoints, specs dari backup

#### File yang Perlu Di-add ke .gitignore

Pastikan file-file ini tidak ter-commit:
- `.env.*` (semua file env)
- `.clinerules` (jika berisi konfigurasi lokal)
- `node_modules/`
- `rtk/` (cache RTK)

## Ringkasan Checklist

```
Bagian 1: Setup Awal
[x] Install VS Code Extensions (Cline, OpenSpec, RTK Inspector)
[x] Konfigurasi DeepSeek V4 Flash di Cline
[x] Inisialisasi RTK untuk Cline (rtk init --agent cline)
[x] Setup / re-init OpenSpec config.yaml

Bagian 2: Setup MCP Servers
[x] Setup Filesystem MCP Server — ✅ via cline_mcp_settings.json
[ ] ~~Setup MySQL Read-Only MCP~~ — disabled, isi credential VPS manual di JSON
[ ] ~~Setup MySQL Write MCP~~ — disabled, isi password local manual di JSON
[ ] Setup Playwright MCP — ✅ via JSON, tapi butuh `npx playwright install chromium`
[ ] ~~Setup Brave Search MCP~~ — disabled, butuh BRAVE_API_KEY

Bagian 3: Integrasi & Testing
[-] Verifikasi MCP server — restart VS Code/Cline untuk lihat status Connected
[x] Test RTK — ✅ 2.2K token saved (20.6%) dari 54 perintah
[-] Test OpenSpec — `/opsx:explore` hanya via Cline chat, tidak via CLI
[ ] Test workflow lengkap: propose → apply → archive (via Cline nanti)

Bagian 4: Finalisasi
[-] Update .gitignore — ✅ sudah mencakup .env.*, node_modules, *.local
[ ] Backup konfigurasi — ✅ semua config tersimpan (cline_mcp_settings.json, .clinerules, config.yaml)
[ ] Dokumentasikan API keys & credentials — manual oleh kamu
