## Current Architecture (Before)

```
┌─────────────────────┐  ┌─────────────────────┐  ┌─────────────────────┐
│    UCP Website       │  │   SA-MP Gamemode     │  │   Discord Bot       │
│  (React + PHP)       │  │   (Pawn + MySQL)     │  │   (Node.js)         │
│                      │  │                      │  │                     │
│ Auth.tsx             │  │ account_regist.inc    │  │ index.js            │
│  ├─ LoginForm        │  │  ├─ CheckPlayerUCP()  │  │  ├─ ClientReady     │
│  ├─ RegisterForm     │  │  ├─ OnPasswordHashed()│  │  └─ Commands        │
│  ├─ VerifyForm       │  │  ├─ OnPlayerRegister()│  │                     │
│  ├─ ForgotPassword   │  │  ├─ InsertPlayerName()│  │ DB: mysql2/promise   │
│  └─ DiscordLink      │  │  └─ OnLoginPassCheck()│  │                     │
│                      │  │                      │  │                     │
│ auth.php (API)       │  │ ui_loginscreen.inc    │  │                     │
│  ├─ action=login     │  │  (TextDraw splash)    │  │                     │
│  ├─ action=register  │  │                      │  │                     │
│  ├─ action=verify    │  │ LoginBox TD           │  │                     │
│  └─ action=discord   │  │  (TextDraw input)     │  │                     │
│                      │  │                      │  │                     │
│ auth_session.php     │  │                      │  │                     │
│  └─ PHP $_SESSION    │  │                      │  │                     │
│                      │  │                      │  │                     │
│ Database? ❌ isolated │  │ Database? ❌ isolated │  │ Database? ⚠️ partial │
└─────────────────────┘  └─────────────────────┘  └─────────────────────┘
```

**Masalah:**
- UCP auth pakai PHP session + auth.php, gamemode auth pakai Pawn callbacks + MySQL query terpisah
- Tidak jelas apakah UCP dan gamemode baca/tulis ke tabel yang sama
- Character creation di UCP (CreateCharacterModal) hanya UI — belum ada endpoint backend
- Bot Discord terkoneksi DB tapi belum ada integrasi auth flow
- Preview/dummy mode di UCP: login pakai hardcoded `admin`/`player` bukan query DB beneran

## Target Architecture (After — Localhost)

```
┌──────────────────────────────────────────────────────────────────────┐
│                        Shared MySQL Database                         │
│                                                                      │
│  player_ucp                player_characters        (existing tables)│
│  ┌──────────────────┐     ┌──────────────────┐                      │
│  │ id (PK)          │     │ id (PK)          │                      │
│  │ username (UNIQUE) │────▶│ ucp_id (FK)      │                      │
│  │ password (bcrypt) │     │ char_name (UNIQUE)│                     │
│  │ email             │     │ skin             │                      │
│  │ verified (bool)   │     │ age              │                      │
│  │ otp_code          │     │ origin           │                      │
│  │ otp_expiry        │     │ created_at       │                      │
│  │ discord_id        │     │ ...              │                      │
│  │ admin_level       │     └──────────────────┘                      │
│  │ last_login        │                                              │
│  │ created_at        │                                              │
│  └──────────────────┘                                              │
└──────────────────────────────────────────────────────────────────────┘
         ▲                    ▲                      ▲
         │                    │                      │
┌────────┴────────┐  ┌────────┴────────┐  ┌─────────┴───────┐
│  UCP Website     │  │  SA-MP Server   │  │  Discord Bot    │
│  localhost:5173  │  │  localhost:7777 │  │  (token dev)    │
│                  │  │                 │  │                 │
│ Auth.tsx         │  │ OnPlayerConnect │  │ Ready event     │
│  ├─ fetch()      │  │  └─ CheckUCP()  │  │  └─ DB connect  │
│  │  auth.php ────┼──┼──▶ player_ucp   │  │                 │
│  │  POST action  │  │                 │  │ Commands:       │
│  │               │  │ OnDialogResponse│  │  └─ /info       │
│  └───────────────┘  │  └─ LoginBox    │  │                 │
│                     │     └─ bcrypt   │  │                 │
│ CreateCharacter     │     check ──────┼──┼─▶ player_ucp    │
│  └─ POST API ───────┼──▶ player_      │  │                 │
│                     │    characters    │  │                 │
│                     │                 │  │                 │
│                     │ OnPlayerSpawn   │  │                 │
│                     │  └─ LoadChar()  │  │                 │
│                     │     └─ query ◀──┼──┼─ player_        │
│                     │        characters│  │ characters     │
└────────────────────┘  └────────────────┘  └────────────────┘
```

## Data Flow — Cross-Service Auth

### 1. Register (UCP only)
```
User → RegisterForm → auth.php (action=register)
  → INSERT INTO player_ucp (username, password, email)
  → Generate OTP → Send email
  → Response: {status: 'pending', message: 'Check email'}
```

### 2. Verify OTP (UCP only)
```
User → VerifyForm → auth.php (action=verify)
  → SELECT otp_code FROM player_ucp WHERE username = ?
  → Match OTP → UPDATE player_ucp SET verified = 1
  → Response: {status: 'success'}
```

### 3. Login UCP (Web)
```
User → LoginForm → auth.php (action=login)
  → SELECT password, verified FROM player_ucp WHERE username = ?
  → bcrypt_verify(password, hash)
  → If !verified → redirect to verify
  → If verified → ucp_create_session() → set $_SESSION
  → Response: {status: 'success', username, admin_level}
```

### 4. Create Character (UCP)
```
User → CreateCharacterModal → POST /api/character.php (NEW)
  → SELECT COUNT(*) FROM player_characters WHERE ucp_id = ?
  → If < max_chars → INSERT INTO player_characters (...)
  → Response: {status: 'success', char_name}
```

### 5. Login In-Game (SA-MP)
```
Player → SA-MP connect → OnPlayerConnect
  → ShowLoginScreenTD() → LoginBox dialog
  → Player enters username + password
  → OnDialogResponse (LOGIN_BOX)
  → bcrypt_check(password, hash) via MySQL query ke player_ucp
  → If match → Load character list from player_characters
  → Player selects character → spawn
```

### 6. Bot Discord (Read-only for Alpha)
```
Bot starts → clientReady event
  → Connect to shared MySQL
  → Register slash commands
  → /info [username] → query player_ucp + player_characters
```

## Key Design Decisions

| Decision | Reason |
|----------|--------|
| **Satu tabel `player_ucp` untuk semua service** | Source of truth tunggal, tidak perlu sync antar tabel |
| **Password hashing: bcrypt** | Sudah ada di PHP (`password_hash`) dan Pawn (`bcrypt` plugin) |
| **Session UCP tetap PHP `$_SESSION`** | Tidak perlu JWT untuk Alpha — session cookie cukup untuk web |
| **In-game login: username + password via dialog** | SA-MP tidak bisa baca cookie/session UCP. Query DB langsung |
| **Character creation via UCP dulu, in-game pilih** | UX lebih baik — user bikin karakter di web dengan preview skin |
| **Max 3 karakter per akun** | Standar roleplay server |
| **OTP via email (PHPMailer/SMTP)** | Sudah ada di auth.php, tinggal dipastikan jalan di localhost |
| **Localhost development** | Tidak perlu domain/SSL/VPS — fokus di kode dan integrasi |

## Risks

| Risk | Mitigation |
|------|-----------|
| Schema mismatch antara tabel existing dan target | Audit dulu schema DB existing sebelum migration |
| Pawn bcrypt plugin tidak kompatibel dengan PHP bcrypt | Test hash compatibility: hash di PHP → verify di Pawn |
| UCP preview/dummy mode conflict dengan live DB | Tambahkan mode switch: `USE_LIVE_DB=true` di config |
| Character creation concurrency (duplikat nama) | UNIQUE constraint di DB + application-level check |
| Bot Discord token leak | Token dev di `.env`, tidak di-commit |
