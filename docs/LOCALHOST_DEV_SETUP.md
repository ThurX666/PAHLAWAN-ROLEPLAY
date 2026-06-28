# Localhost Development Setup — PAHLAWAN ROLEPLAY

Prerequisites: XAMPP v3.x (MariaDB 10.4 + Apache + PHP 8.2), Node.js v22

## 1. Start MySQL + Apache (XAMPP)

Buka XAMPP Control Panel → Start **MySQL** dan **Apache**.

## 2. Database

Database: `arivena` (MariaDB 10.4.32, 103 tables)

Koneksi default:
- Host: `127.0.0.1`
- User: `root`
- Password: (kosong)

Import schema jika belum ada:
```bash
mysql -u root arivena < DATABASE/phrp.sql
```

## 3. UCP Website

### Start PHP built-in server (port 8000):
```bash
cd WEBSITE/public
C:/xampp/php/php.exe -S 127.0.0.1:8000
```

### Start Vite dev server (port 5173):
```bash
cd WEBSITE
npm install   # jika belum
npm run dev
```

Vite proxies `/api/*` → `http://127.0.0.1:8000`.

UCP URL: `http://localhost:5173`

### Test Auth API:
```bash
# Register
curl -X POST http://127.0.0.1:8000/api/register.php \
  -d "action=register&username=test&password=Pass1234&email=test@test.com"

# Verify OTP (kode dari response)
curl -X POST http://127.0.0.1:8000/api/verify.php \
  -d "action=verify_otp&username=test&otp_code=123456&device=Windows&ip=127.0.0.1&location=Local"

# Login
curl -X POST http://127.0.0.1:8000/api/auth.php \
  -d "action=login&username=test&password=Pass1234&device=Windows&ip=127.0.0.1&location=Local"
```

## 4. SA-MP Server

⚠️ **Workflow:** GAMEMODE untuk coding/compile, ARIVENA50JT untuk runtime.
Server harus dijalankan dari `C:\Users\guyub\Downloads\ARIVENA50JT` karena
Windows Defender kadang blokir/menghapus file di direktori Documents.

### Compile gamemode:
```bash
cd C:/Users/guyub/Documents/PAHLAWAN\ ROLEPLAY/GAMEMODE
cmd //c 'pawno\pawncc.exe gamemodes\main.pwn -ogamemodes\main.amx -ipawno\include -ipawno\pawno\include'
```

### Copy AMX ke runtime:
```bash
cp C:/Users/guyub/Documents/PAHLAWAN\ ROLEPLAY/GAMEMODE/gamemodes/main.amx C:/Users/guyub/Downloads/ARIVENA50JT/gamemodes/main.amx
```

### Run server dari ARIVENA50JT:
```bash
cd C:/Users/guyub/Downloads/ARIVENA50JT
./samp-server.exe
```

Port: `7777`

## 5. Discord Bot

### Install & run:
```bash
cd BOT
npm install   # atau yarn
# Set token di config.json
npm start
```

Butuh: bot token di `config.json`, Discord guild.

## 6. MCP Server (pahlawan-roleplay)

### Build:
```bash
cd tools/mcp-pahlawan
npm install
npm run build
```

### Hermes Agent config di `~/.hermes/config.yaml`:
```yaml
mcp_servers:
  pahlawan-roleplay:
    command: node
    args:
      - C:/Users/guyub/Documents/PAHLAWAN ROLEPLAY/tools/mcp-pahlawan/dist/index.js
    env:
      PROJECT_ROOT: C:/Users/guyub/Documents/PAHLAWAN ROLEPLAY
      MYSQL_HOST: 127.0.0.1
      MYSQL_USER: root
      MYSQL_DATABASE: arivena
      PAWN_COMPILER_PATH: GAMEMODE/pawno/pawncc.exe
      ...
```

## Verification Checklist

- [ ] MySQL accessible via MCP (`db_safe_query`)
- [ ] PHP server responds (`curl localhost:8000`)
- [ ] Vite dev server (UCP at `localhost:5173`)
- [ ] SA-MP server starts + connects to MySQL
- [ ] Full auth flow: Register → Verify → Login
