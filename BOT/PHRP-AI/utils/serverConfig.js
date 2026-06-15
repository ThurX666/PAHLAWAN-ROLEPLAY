/**
 * PHRP-AI Server Config Reader
 * Membaca IP dan port server dari config.json utama (root directory).
 * 
 * Config.json letak: ../config.json (relatif dari folder PHRP-AI/utils/)
 * Struktur: { "server": { "ip": "127.0.0.1", "port": "7777" } }
 */

const fs = require("fs");
const path = require("path");

const CONFIG_PATH = path.join(__dirname, "..", "..", "config.json");

let serverConfigCache = null;

function loadServerConfig() {
  if (!fs.existsSync(CONFIG_PATH)) {
    console.warn("[PHRP-AI/utils/serverConfig.js] File config.json tidak ditemukan di root!");
    return { ip: "127.0.0.1", port: "7777" };
  }

  try {
    const raw = fs.readFileSync(CONFIG_PATH, "utf-8");
    const data = JSON.parse(raw);

    if (data.server && data.server.ip && data.server.port) {
      console.log(`[PHRP-AI] Server config loaded: ${data.server.ip}:${data.server.port}`);
      return data.server;
    }

    console.warn("[PHRP-AI/utils/serverConfig.js] config.json tidak memiliki field server.ip atau server.port, pakai default.");
    return { ip: "127.0.0.1", port: "7777" };
  } catch (err) {
    console.error("[PHRP-AI/utils/serverConfig.js] Gagal parse config.json:", err.message);
    return { ip: "127.0.0.1", port: "7777" };
  }
}

function getServerConfig() {
  if (!serverConfigCache) {
    serverConfigCache = loadServerConfig();
  }
  return serverConfigCache;
}

/**
 * Dapatkan string "IP:Port" untuk ditampilkan ke user.
 */
function getServerAddress() {
  const config = getServerConfig();
  return `${config.ip}:${config.port}`;
}

/**
 * Format info server untuk di-inject ke system prompt.
 */
function formatServerInfoForPrompt() {
  const config = getServerConfig();
  return `IP: ${config.ip}\nPort: ${config.port}\nAlamat server: ${config.ip}:${config.port}`;
}

/**
 * Refresh cache (panggil setelah edit config.json)
 */
function refreshCache() {
  serverConfigCache = null;
  console.log("[PHRP-AI] Server config cache refreshed.");
}

module.exports = {
  getServerConfig,
  getServerAddress,
  formatServerInfoForPrompt,
  refreshCache,
};