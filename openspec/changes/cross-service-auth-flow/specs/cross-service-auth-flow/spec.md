# cross-service-auth-flow

## ADDED

### `player_ucp` Schema (Single Source of Truth)

Database table `player_ucp` menjadi satu-satunya tabel autentikasi untuk semua service (UCP, SA-MP, Bot).

```sql
CREATE TABLE IF NOT EXISTS player_ucp (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(32) NOT NULL UNIQUE,
    password VARCHAR(255) NOT NULL,          -- bcrypt hash
    email VARCHAR(128) NOT NULL,
    verified TINYINT(1) DEFAULT 0,
    otp_code VARCHAR(6) DEFAULT NULL,
    otp_expiry DATETIME DEFAULT NULL,
    discord_id VARCHAR(32) DEFAULT NULL,
    admin_level INT DEFAULT 0,
    last_login DATETIME DEFAULT NULL,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    INDEX idx_username (username),
    INDEX idx_email (email)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
```

### `player_characters` Schema (Character Storage)

```sql
CREATE TABLE IF NOT EXISTS player_characters (
    id INT AUTO_INCREMENT PRIMARY KEY,
    ucp_id INT NOT NULL,
    char_name VARCHAR(32) NOT NULL UNIQUE,
    skin INT DEFAULT 0,
    age INT DEFAULT 18,
    origin VARCHAR(64) DEFAULT 'Los Santos',
    gender TINYINT(1) DEFAULT 0,            -- 0 = male, 1 = female
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (ucp_id) REFERENCES player_ucp(id) ON DELETE CASCADE,
    INDEX idx_ucp_id (ucp_id),
    INDEX idx_char_name (char_name)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
```

### `auth.php` API Endpoints

#### POST action=register

Request:
```
username=string, password=string, email=string, device=string, ip=string, location=string
```

Success Response (201):
```json
{"status": "pending", "message": "Registrasi berhasil. Silakan cek email untuk kode verifikasi.", "cooldown": 1800}
```

Error Responses:
- 400: `{"status": "error", "message": "Username sudah terdaftar."}`
- 400: `{"status": "error", "message": "Email sudah digunakan."}`
- 400: `{"status": "error", "message": "Username hanya boleh huruf, angka, dan underscore (3-20 karakter)."}`

#### POST action=login

Request:
```
username=string, password=string, device=string, ip=string, location=string
```

Success Response (200):
```json
{"status": "success", "username": "PlayerName", "admin_level": 0, "is_discord_linked": false}
```

Pending Response (200):
```json
{"status": "unverified", "registered_user": "PlayerName", "cooldown": 1200, "message": "Akun belum diverifikasi."}
```

Discord Required Response (200):
```json
{"status": "discord_required", "username": "PlayerName", "message": "Harap hubungkan akun Discord."}
```

Error Response:
- 400: `{"status": "error", "message": "Username atau password salah."}`

#### POST action=verify

Request:
```
username=string, otp_code=string
```

Success Response (200):
```json
{"status": "success", "message": "Akun berhasil diverifikasi. Silakan login."}
```

Error Responses:
- 400: `{"status": "error", "message": "Kode verifikasi salah atau kadaluarsa."}`
- 404: `{"status": "error", "message": "Akun tidak ditemukan."}`

### `character.php` API Endpoint (NEW)

#### POST create

Request (multipart/form-data + session cookie):
```
char_name=string, skin=int, age=int, origin=string, gender=int
```

Success Response (201):
```json
{"status": "success", "message": "Karakter berhasil dibuat.", "char_name": "John_Doe"}
```

Error Responses:
- 401: `{"status": "error", "message": "Anda harus login terlebih dahulu."}`
- 400: `{"status": "error", "message": "Nama karakter hanya boleh huruf, angka, dan underscore (3-20 karakter)."}`
- 409: `{"status": "error", "message": "Nama karakter sudah digunakan."}`
- 400: `{"status": "error", "message": "Maksimal 3 karakter per akun."}`

#### GET list

Response (200):
```json
{
  "status": "success",
  "characters": [
    {"id": 1, "char_name": "John_Doe", "skin": 0, "age": 25, "origin": "Los Santos", "gender": 0, "created_at": "2026-07-01T12:00:00Z"},
    {"id": 2, "char_name": "Jane_Doe", "skin": 1, "age": 22, "origin": "San Fierro", "gender": 1, "created_at": "2026-07-02T15:30:00Z"}
  ]
}
```

### In-Game Login Flow (SA-MP)

1. `OnPlayerConnect` → `CheckPlayerUCP()` → query `player_ucp` WHERE `username` = player name.
2. Player enters password via `LoginBox` dialog.
3. `OnLoginPassCheck()` → bcrypt verify password hash dari `player_ucp.password`.
4. If verified = 0 → pesan error "Akun belum diverifikasi. Cek email Anda."
5. If verified = 1 → load characters dari `player_characters` WHERE `ucp_id` = user ID.
6. If characters exist → dialog list untuk pilih karakter.
7. If no characters → dialog "Buat karakter dulu di website (localhost:5173)".
8. Character terpilih → spawn.

### Discord Bot Slash Command — `/info`

Command: `/info [username]`

Response Embed:
```
Title: Player Info — {username}
Fields:
- UCP ID: {id}
- Verified: ✅/❌
- Admin Level: {admin_level}
- Last Login: {last_login}
- Characters: {count} ({list of names})
- Discord Linked: ✅/❌
```

Bot hanya READ-ONLY — tidak bisa insert/update/delete data.

### Localhost Development Environment

| Service    | URL / Port            | Config                         |
|------------|-----------------------|--------------------------------|
| MySQL      | localhost:3306        | Shared — semua service connect |
| Apache/PHP | localhost:80          | XAMPP htdocs → WEBSITE/public  |
| UCP Vite   | localhost:5173        | `npm run dev` dari WEBSITE/    |
| SA-MP      | localhost:7777        | `samp-server.exe`              |
| Bot        | Discord token (dev)   | `npm start` dari BOT/          |

## MODIFIED

### `ucp-local-auth-dev-flow` (Existing Spec)

- **Sebelum:** UCP punya preview/dummy mode login (`admin`/`player` hardcoded).
- **Sesudah:** Preview mode dihapus. UCP selalu fetch ke `auth.php` yang terhubung ke database shared.

### Auth.tsx (Frontend)

- **Sebelum:** `isPreviewEnv()` check → simulasi login 1 detik.
- **Sesudah:** Selalu jalankan `fetch('auth.php')` — tidak ada lagi mode preview.

### `account_regist.inc` (Gamemode)

- **Sebelum:** Query tabel akun yang mungkin terpisah dari UCP.
- **Sesudah:** Semua query mengarah ke `player_ucp` table.

## REMOVED

- **Preview/Dummy auth mode** di UCP (`isPreviewEnv()` fallback di `Auth.tsx`).
- **Hardcoded credentials** (`admin`, `player`).
- **Tabel akun duplikat** — jika ada tabel akun terpisah di gamemode, migrate ke `player_ucp` lalu drop.

---

## Acceptance Criteria

1. User bisa register di UCP → data tersimpan di `player_ucp`.
2. User bisa verify OTP via email → `verified` jadi 1.
3. User bisa login di UCP → session aktif.
4. User bisa login di SA-MP dengan username + password yang sama → sukses.
5. User `unverified` ditolak login in-game dengan pesan jelas.
6. User bisa buat karakter di UCP → tersimpan di `player_characters`.
7. User bisa lihat karakter yang dibuat di UCP dari dalam game (character selection).
8. User bisa pilih karakter → spawn.
9. Max 3 karakter per akun — karakter ke-4 ditolak.
10. Duplicate character name ditolak.
11. Bot Discord bisa query data user via `/info`.
12. Semua service connect ke database shared yang sama di localhost.
13. Tidak ada hardcoded credentials atau mode preview yang tersisa.
