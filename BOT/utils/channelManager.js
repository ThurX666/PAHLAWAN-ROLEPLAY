const fs = require("fs");
const path = require("path");

const CHANNELS_PATH = path.join(__dirname, "..", "config", "channels.json");

let channelsCache = null;

/**
 * Load semua channel dari config/channels.json
 */
function loadChannels() {
  if (!fs.existsSync(CHANNELS_PATH)) {
    console.error("[ChannelManager] File config/channels.json tidak ditemukan!");
    return {};
  }

  const raw = fs.readFileSync(CHANNELS_PATH, "utf-8");
  const data = JSON.parse(raw);

  // Filter hanya yang punya ID valid
  const valid = {};
  for (const [key, val] of Object.entries(data)) {
    if (val.id && val.id.trim() !== "") {
      valid[key] = val;
    }
  }

  console.log(`[ChannelManager] Loaded ${Object.keys(valid).length}/${Object.keys(data).length} valid channels.`);
  return valid;
}

/**
 * Dapatkan channel map (key -> id)
 */
function getChannelMap() {
  if (!channelsCache) {
    channelsCache = loadChannels();
  }
  return channelsCache;
}

/**
 * Dapatkan ID channel berdasarkan key
 * @param {string} key - route key (register, help, report, dll)
 * @returns {string|null} Discord channel ID atau null jika tidak ditemukan
 */
function getChannelId(key) {
  const map = getChannelMap();
  return map[key]?.id || null;
}

/**
 * Format mention Discord untuk channel
 * @param {string} key
 * @returns {string} Mention string seperti <#123456789> atau string kosong
 */
function getChannelMention(key) {
  const id = getChannelId(key);
  return id ? `<#${id}>` : "";
}

/**
 * Dapatkan daftar semua route key yang valid (yang punya ID)
 * @returns {string[]}
 */
function getValidRouteKeys() {
  return Object.keys(getChannelMap());
}

/**
 * Format list semua channel untuk dimasukkan ke system prompt.
 * @returns {string} formatted string
 */
function formatChannelListForPrompt() {
  const channels = getChannelMap();
  const lines = Object.entries(channels).map(([key, val]) => {
    return `  - "${key}" → #${val.name} (${val.description})`;
  });
  return lines.join("\n");
}

/**
 * Refresh cache (panggil setelah edit channels.json)
 */
function refreshCache() {
  channelsCache = null;
  console.log("[ChannelManager] Cache refreshed.");
}

module.exports = {
  getChannelMap,
  getChannelId,
  getChannelMention,
  getValidRouteKeys,
  formatChannelListForPrompt,
  refreshCache,
};