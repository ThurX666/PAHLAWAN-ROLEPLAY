/**
 * PHRP-AI Database Connector
 * 
 * Terhubung ke database MySQL server SA-MP.
 * Konfigurasi database ada di config.json utama (root directory).
 * 
 * TABEL YANG DIDUKUNG (berdasarkan dump database PHRP):
 * - player_ucp      → Akun/UCP pemain
 * - player_characters → Karakter pemain
 * - ucp             → UCP alternatif
 * - player_bans     → Player banned
 * - biz             → Bisnis
 * - houses          → Rumah
 * - families        → Family/grup
 * - player_vehicles → Kendaraan pemain
 */

const mysql = require("mysql2/promise");
const fs = require("fs");
const path = require("path");

const CONFIG_PATH = path.join(__dirname, "..", "..", "config.json");

let pool = null;

// ============================================================
// WHITELIST — Hanya tabel ini yang bisa di-query
// ============================================================
const ALLOWED_TABLES = new Set([
  "player_ucp", "player_characters", "ucp",
  "player_bans", "biz", "houses", "families", "player_vehicles",
  "player_weapons", "inventory", "shops",
  "faction_brankas", "faction_garages", "faction_logs", "faction_vaultlogs",
  "doors", "atms", "bankpoints", "lockers", "vaults", "armouries",
]);

// ============================================================
// KOLOM SENSITIF — Otomatis dihapus dari hasil query
// ============================================================
const SENSITIVE_COLUMNS = new Set([
  "password", "pass", "hash", "hashed_password", "salt",
  "ip", "Char_IP", "last_ip", "reg_ip", "register_ip", "player_ip",
  "email", "email_address", "player_email", "Email",
  "auth_token", "session_key", "api_key",
  "pin", "pin_code", "security_code",
  "credit", "credit_card", "bank_account",
  "secret_key", "reset_token",
]);

/**
 * Load konfigurasi database dari config.json
 */
function getDatabaseConfig() {
  if (!fs.existsSync(CONFIG_PATH)) {
    throw new Error("File config.json tidak ditemukan di root!");
  }

  const raw = fs.readFileSync(CONFIG_PATH, "utf-8");
  const data = JSON.parse(raw);

  if (!data.database) {
    throw new Error(
      "Konfigurasi database tidak ditemukan di config.json!"
    );
  }

  return data.database;
}

/**
 * Validasi bahwa query hanya SELECT dan target tabel ada di whitelist.
 */
function validateQuery(sql) {
  const trimmed = sql.trim();

  // 1. Hanya SELECT yang diizinkan
  if (!/^\s*SELECT\s/i.test(trimmed)) {
    throw new Error("SECURITY: Hanya query SELECT yang diizinkan.");
  }

  // 2. Tolak keyword berbahaya
  const dangerous = [
    "INTO", "INSERT", "UPDATE", "DELETE", "DROP", "ALTER", "CREATE",
    "TRUNCATE", "EXEC", "EXECUTE", "CALL", "LOAD", "GRANT", "REVOKE",
    "RENAME", "REPLACE", "SET", "SHOW", "DESCRIBE", "DESC",
    "INFORMATION_SCHEMA", "MYSQL", "PG_SLEEP", "SLEEP", "BENCHMARK",
    "UNION", "--", "/*", "*/", "||", "&&",
  ];

  const upper = trimmed.toUpperCase();
  for (const keyword of dangerous) {
    if (upper.includes(keyword)) {
      throw new Error(`SECURITY: Query mengandung keyword terlarang: "${keyword}"`);
    }
  }

  // 3. Validasi tabel yang ditarget ada di whitelist
  const tableMatch = trimmed.match(/\bFROM\s+`?(\w+)`?\s*/i);
  if (tableMatch) {
    const tableName = tableMatch[1].toLowerCase();
    if (!ALLOWED_TABLES.has(tableName)) {
      throw new Error(
        `SECURITY: Tabel "${tableName}" tidak diizinkan.`
      );
    }
  }

  return true;
}

/**
 * Filter kolom sensitif dari hasil query.
 */
function filterSensitiveData(rows) {
  if (!rows || rows.length === 0) return rows;

  return rows.map((row) => {
    const filtered = { ...row };
    for (const col of Object.keys(filtered)) {
      if (SENSITIVE_COLUMNS.has(col.toLowerCase())) {
        delete filtered[col];
      }
    }
    return filtered;
  });
}

/**
 * Inisialisasi koneksi pool ke database
 */
async function initPool() {
  if (pool) return pool;

  const dbConfig = getDatabaseConfig();

  try {
    pool = mysql.createPool({
      host: dbConfig.host,
      port: dbConfig.port || 3306,
      user: dbConfig.user,
      password: dbConfig.password,
      database: dbConfig.name,
      charset: dbConfig.charset || "utf8mb4",
      waitForConnections: true,
      connectionLimit: 5,
      queueLimit: 0,
      enableKeepAlive: true,
      keepAliveInitialDelay: 10000,
    });

    const connection = await pool.getConnection();
    console.log(`[PHRP-AI-DB] Connected to MySQL: ${dbConfig.host}:${dbConfig.port}/${dbConfig.name}`);
    connection.release();

    return pool;
  } catch (err) {
    console.error(`[PHRP-AI-DB] Failed to connect: ${err.message}`);
    pool = null;
    throw err;
  }
}

/**
 * EKSEKUSI QUERY AMAN — Hanya SELECT, parameterized, filter sensitif
 */
async function query(sql, params = []) {
  validateQuery(sql);

  if (!pool) {
    await initPool();
  }

  try {
    const [rows] = await pool.execute(sql, params);
    return filterSensitiveData(rows);
  } catch (err) {
    console.error(`[PHRP-AI-DB] Query error: ${err.message}`);
    throw err;
  }
}

/**
 * 🔒 Cari pemain berdasarkan nama karakter (Char_Name di player_characters).
 * Juga cari di player_ucp berdasarkan UCP.
 */
async function findPlayer(playerName) {
  // Validasi input
  if (!/^[\w\s_-]+$/.test(playerName)) {
    console.warn(`[PHRP-AI-DB] Invalid player name rejected: ${playerName}`);
    return [];
  }

  const results = [];

  // 1. Cari di player_characters berdasarkan Char_Name
  try {
    const chars = await query(
      `SELECT * FROM player_characters WHERE Char_Name LIKE ? LIMIT 5`,
      [`%${playerName}%`]
    );
    results.push(...chars);
  } catch { /* skip */ }

  // 2. Cari di player_ucp berdasarkan UCP
  try {
    const ucps = await query(
      `SELECT * FROM player_ucp WHERE UCP LIKE ? LIMIT 5`,
      [`%${playerName}%`]
    );
    results.push(...ucps);
  } catch { /* skip */ }

  return results;
}

/**
 * 🔒 Cari staff/admin — cek Char_Admin di player_characters
 */
async function findStaff(playerName) {
  if (!/^[\w\s_-]+$/.test(playerName)) {
    console.warn(`[PHRP-AI-DB] Invalid staff name rejected: ${playerName}`);
    return [];
  }

  try {
    const rows = await query(
      `SELECT * FROM player_characters WHERE Char_Name LIKE ? AND Char_Admin > 0 LIMIT 5`,
      [`%${playerName}%`]
    );
    return rows;
  } catch {
    return [];
  }
}

/**
 * 🔒 Cari pemain berdasarkan discord_id.
 * Cari di player_ucp.discord_id dan ucp.discord_id
 */
async function findPlayerByDiscord(discordId) {
  const cleanId = discordId.toString().replace(/\D/g, "");
  if (!cleanId || cleanId.length < 10) {
    console.warn(`[PHRP-AI-DB] Invalid discord ID rejected: ${discordId}`);
    return [];
  }

  const results = [];

  // 1. Cari di player_ucp
  try {
    const ucps = await query(
      `SELECT * FROM player_ucp WHERE discord_id = ? LIMIT 5`,
      [cleanId]
    );
    results.push(...ucps);
  } catch { /* skip */ }

  // 2. Cari di ucp
  try {
    const ucps = await query(
      `SELECT * FROM ucp WHERE discord_id = ? LIMIT 5`,
      [cleanId]
    );
    results.push(...ucps);
  } catch { /* skip */ }

  // 3. Cari karakter dari player_ucp yang ditemukan
  for (const ucp of results) {
    try {
      const chars = await query(
        `SELECT * FROM player_characters WHERE Char_UCP = ? LIMIT 5`,
        [ucp.UCP || ucp.username]
      );
      results.push(...chars);
    } catch { /* skip */ }
  }

  return results;
}

/**
 * 🔒 Cek status banned pemain
 */
async function checkBan(playerName) {
  try {
    // Cek di player_bans berdasarkan name
    const bans = await query(
      `SELECT * FROM player_bans WHERE name LIKE ? LIMIT 1`,
      [`%${playerName}%`]
    );
    if (bans.length > 0) return bans[0];
  } catch { /* skip */ }

  // Cek Blocked di player_ucp
  try {
    const blocked = await query(
      `SELECT * FROM player_ucp WHERE UCP LIKE ? AND Blocked = 1 LIMIT 1`,
      [`%${playerName}%`]
    );
    if (blocked.length > 0) {
      return {
        name: blocked[0].UCP,
        reason: blocked[0].Block_Reason || "No reason",
        admin: blocked[0].Block_AdminName || "Server",
      };
    }
  } catch { /* skip */ }

  return null;
}

/**
 * Get status koneksi database.
 */
async function getConnectionStatus() {
  try {
    if (!pool) {
      await initPool();
    }
    const connection = await pool.getConnection();
    connection.release();
    return { connected: true, message: "Database terhubung" };
  } catch (err) {
    return { connected: false, message: `Database tidak terhubung: ${err.message}` };
  }
}

/**
 * Tutup semua koneksi pool.
 */
async function closePool() {
  if (pool) {
    await pool.end();
    pool = null;
    console.log("[PHRP-AI-DB] Connection pool closed.");
  }
}

module.exports = {
  initPool,
  query,
  findPlayer,
  findStaff,
  findPlayerByDiscord,
  checkBan,
  getConnectionStatus,
  closePool,
};