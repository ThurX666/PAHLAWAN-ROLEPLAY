/**
 * PHRP-AI Database Status Checker
 * Otomatis cek koneksi database saat bot startup.
 */

const db = require("./database");
const config = require("../../config.json");

let isConnected = false;
let lastError = null;

async function checkDatabaseConnection() {
  console.log("\n🔌 [PHRP-AI/utils/dbStatus.js] Checking database connection...");
  
  if (!config.database) {
    console.log("[PHRP-AI/utils/dbStatus.js] ⚠️  Konfigurasi database tidak ditemukan di config.json");
    console.log("[PHRP-AI/utils/dbStatus.js] 💡 Tambahkan field 'database' di config.json:");
    console.log(`      "database": {
        "host": "127.0.0.1",
        "port": 3306,
        "user": "root",
        "password": "",
        "name": "samp_phrp"
      }`);
    isConnected = false;
    return false;
  }

  try {
    // Inisialisasi pool
    await db.initPool();
    
    // Test koneksi dengan ping sederhana
    const status = await db.getConnectionStatus();
    
    if (status.connected) {
      isConnected = true;
      lastError = null;
      console.log(`[PHRP-AI/utils/dbStatus.js] ✅ ${status.message}`);
      console.log(`[PHRP-AI/utils/dbStatus.js] 📊 Host: ${config.database.host}:${config.database.port}`);
      console.log(`[PHRP-AI/utils/dbStatus.js] 🗃️  Database: ${config.database.name}`);
      return true;
    } else {
      isConnected = false;
      lastError = status.message;
      console.log(`[PHRP-AI/utils/dbStatus.js] ❌ ${status.message}`);
      return false;
    }
  } catch (err) {
    isConnected = false;
    lastError = err.message;
    console.log(`[PHRP-AI/utils/dbStatus.js] ❌ Gagal terkoneksi: ${err.message}`);
    console.log(`[PHRP-AI/utils/dbStatus.js] 💡 Pastikan MySQL server berjalan dan kredensial di config.json benar`);
    return false;
  }
}

function getStatus() {
  return { isConnected, lastError };
}

module.exports = {
  checkDatabaseConnection,
  getStatus,
};