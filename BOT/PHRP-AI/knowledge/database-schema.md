# Struktur Database SA-MP Server PHRP

Berdasarkan dump database server PHRP per 8 Juni 2026.

## Tabel Utama Pemain

### `player_ucp` — Tabel Akun / UCP Pemain
| Kolom | Tipe | Keterangan |
|---|---|---|
| `ID` | int(11) | ID unik akun |
| `UCP` | varchar(22) | Nama akun UCP |
| `Email` | varchar(128) | Email pendaftaran |
| `discord_id` | varchar(50) | **ID Discord** (untuk tag: <@discord_id>) |
| `IP` | varchar(24) | IP address |
| `Password` | varchar(64) | Password (hashed) |
| `admin_level` | int(11) | **Level admin** (0 = player, 1+ = staff) |
| `vip_status` | varchar(50) | Status VIP |
| `vip_time` | int(11) | Sisa waktu VIP |
| `gold` | int(11) | Gold / premium points |
| `Register_Date` | varchar(30) | Tanggal registrasi |
| `Last_Login` | varchar(30) | Terakhir login |
| `Blocked` | tinyint(3) | Status banned (0 = tidak, 1 = dibanned) |
| `Block_Reason` | varchar(128) | Alasan ban |
| `Block_AdminName` | varchar(24) | Admin yang ban |

### `player_characters` — Tabel Karakter Pemain
| Kolom | Tipe | Keterangan |
|---|---|---|
| `pID` | int(11) | ID karakter |
| `Char_UCP` | varchar(22) | Nama UCP pemilik |
| `Char_Name` | varchar(64) | **Nama karakter in-game** |
| `Char_Admin` | tinyint(3) | **Level admin karakter** (0 = biasa, 1+ = staff) |
| `Char_AdminName` | varchar(24) | Nama admin (jika staff) |
| `Char_Level` | int(10) | Level karakter |
| `Char_Money` | bigint(20) | Uang IC |
| `Char_BankMoney` | bigint(20) | Uang di bank |
| `Char_BankNumber` | int(10) | Nomor rekening bank |
| `Char_Faction` | tinyint(3) | **ID faction** (0 = tidak punya faction) |
| `Char_FactionRank` | int(10) | Rank di faction |
| `Char_Skin` | mediumint(8) | Skin ID |
| `Char_Gender` | tinyint(3) | Gender (0 = laki, 1 = perempuan) |
| `Char_Age` | int(11) | Usia karakter |
| `Char_Origin` | varchar(64) | Asal / negara |
| `Char_Hours` | int(10) | Total jam bermain |
| `Char_RegisterDate` | varchar(30) | Tanggal registrasi karakter |
| `Char_LastLogin` | varchar(30) | Terakhir login |
| `Char_IP` | varchar(24) | IP terakhir |
| `Char_Jailed` | int(10) | Status jailed |
| `Char_JailReason` | varchar(60) | Alasan jail |
| `Char_Warn` | tinyint(3) | Jumlah warning |
| `Char_DinarPoints` | int(10) | Dinar points |
| `Char_DCTime` | bigint(20) | Last DC time |
| `Char_VIP` | tinyint(3) | Status VIP |
| `Char_VIPTime` | bigint(20) | Sisa waktu VIP |
| `Char_DonatorTag` | varchar(128) | Tag donator |

### `ucp` — Tabel UCP Alternatif
| Kolom | Tipe | Keterangan |
|---|---|---|
| `uid` | int(10) | ID unik |
| `username` | varchar(32) | Nama UCP |
| `email` | varchar(128) | Email |
| `discord_id` | varchar(32) | **ID Discord** |
| `password` | varchar(100) | Password |

## Tabel Staff / Admin
- `admin_logs` — Log aktivitas admin (Prefix, Admin, AdminUCP, UCPTarget)
- `player_characters.Char_Admin` — Level admin karakter (0 = biasa, 10 = owner)

## Tabel Faction
- `faction_brankas` — Brankas faction (FID, Item, Model, Quantity)
- `faction_garages` — Garasi faction (id, type, name)
- `faction_logs` — Log faction
- `faction_vaultlogs` — Log vault faction
- `families` — Tabel family/grup (ID, LeaderID, LeaderName, Name, Money, DirtyMoney)

## Tabel Bisnis
- `biz` — Tabel bisnis (ID, Name, OwnerID, OwnerName, Money, Type, Price, ProdStock0-10, ProdPrice0-10)

## Tabel Rumah
- `houses` — Tabel rumah (ID, OwnerID, OwnerName, X, Y, Z, Type, World, Interior)
- `rusun` — Tabel rusun/apartment (ID, Name, OwnerName, OwnerID, Cost_30Day)

## Tabel Kendaraan
- `player_vehicles` — Kendaraan pemain (id, PVeh_Owner, PVeh_ModelID, PVeh_Price, PVeh_Plate, PVeh_Fuel, PVeh_Locked)
- `demand_vehicles` — Kendaraan demand/pekerjaan

## Tabel Banned
- `player_bans` — Player banned (id, name, ip, admin, reason, ban_expire, ban_date)

## Tabel Inventory
- `inventory` — Inventory pemain (Owner_ID, invent_Item, invent_Model, invent_Quantity)
- `player_weapons` — Senjata pemain (Owner_ID, Type1-13, Gun1-13, Ammo1-13)

## Tabel Lainnya
- `shops` — Shop point (type: 1=toko biasa, 2=24/7, 3=hardware, 4=clothing)
- `doors` — Door interior
- `basement` — Basement
- `atms` — ATM points
- `bankpoints` — Bank points
- `lockers` — Locker points
- `vaults` — Vault points
- `armouries` — Armoury points
- `garbages` — Tempat sampah
- `kanabis` — Tanaman kanabis
- `trees` — Pohon
- `ores` — Batu tambang
- `dynamic_deer` — Rusa buruan
- `farmplants` — Tanaman pertanian
- `crafttables` — Meja crafting
- `fcrafts` — Faction crafting

## Catatan Query untuk AI
- Tabel karakter: `player_characters` (cari berdasarkan `Char_Name`)
- Tabel akun: `player_ucp` (cari berdasarkan `UCP`)
- Discord ID ada di: `player_ucp.discord_id` dan `ucp.discord_id`
- Level admin ada di: `player_characters.Char_Admin` dan `player_ucp.admin_level`
- Format mention Discord: `<@discord_id>`
- Gunakan `LIKE` untuk pencarian parsial nama
- ALL SELECT queries only — safety first