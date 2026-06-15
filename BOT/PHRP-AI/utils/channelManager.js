/**
 * PHRP-AI Channel Manager
 * Mengelola semua channel Discord yang bisa dirujuk AI.
 * Tinggal tambah/edit di config/channels.json, AI otomatis paham.
 */

const fs = require("fs");
const path = require("path");

const CHANNELS_PATH = path.join(__dirname, "../config/channels.json");

let channelsCache = null;

function loadChannels() {
  if (!fs.existsSync(CHANNELS_PATH)) {
    console.error("[PHRP-AI] File config/channels.json tidak ditemukan!");
    return {};
  }

  const raw = fs.readFileSync(CHANNELS_PATH, "utf-8");
  const data = JSON.parse(raw);

  const valid = {};
  for (const [key, val] of Object.entries(data)) {
    if (val.id && val.id.trim() !== "") {
      const normalizedKey = key.replace(/[^\w\s]/g, "").toLowerCase(); // Normalize key
      valid[normalizedKey] = val;
    }
  }

  return valid;
}

function getChannelMap() {
  if (!channelsCache) {
    channelsCache = loadChannels();
  }
  return channelsCache;
}

const detectIntent = require("./intentDetector"); // Import Intent Detector

function getChannelId(key) {
  const map = getChannelMap();
  const normalizedKey = key.replace(/[^\w\s]/g, "").toLowerCase(); // Normalize search key

  // Detect intent from key
  const detectedIntent = detectIntent(normalizedKey);
  if (detectedIntent?.category) {
    const intentMatches = Object.entries(map).find(([_, val]) => 
      val.categoryName.toLowerCase() === detectedIntent.category.toLowerCase()
    );
    if (intentMatches) {
      const [_, selectedChannel] = intentMatches;
      return {
        id: selectedChannel.id,
        categoryId: selectedChannel.categoryId,
        categoryName: selectedChannel.categoryName,
        displayChannels: Object.entries(map)
          .filter(([_, val]) => val.categoryId === selectedChannel.categoryId)
          .map(([name, _]) => name),
      };
    }
  }

  // Exact match
  if (map[normalizedKey]) {
    return {
      id: map[normalizedKey].id,
      categoryId: map[normalizedKey].categoryId,
      categoryName: map[normalizedKey].categoryName,
      displayChannels: Object.entries(map)
        .filter(([_, val]) => val.categoryId === map[normalizedKey].categoryId)
        .map(([name, _]) => name),
    };
  }

  // Fuzzy match
  const matches = Object.entries(map)
    .map(([key, val]) => {
      const keyScore = key.includes(normalizedKey) ? 2 : 0;
      const nameScore = val.name && val.name.toLowerCase().includes(normalizedKey) ? 5 : 0;
      const descriptionScore = val.description && val.description.toLowerCase().includes(normalizedKey) ? 3 : 0;
      const totalScore = keyScore + nameScore + descriptionScore;
      return { key, val, totalScore };
    })
    .filter((entry) => entry.totalScore > 0)
    .sort((a, b) => b.totalScore - a.totalScore); // Sort by relevance score

  if (matches.length > 0) {
    const fVal = matches[0].val; // Select match with highest score
    return {
      id: fVal.id,
      categoryId: fVal.categoryId,
      categoryName: fVal.categoryName,
      displayChannels: Object.entries(map)
        .filter(([_, val]) => val.categoryId === fVal.categoryId)
        .map(([name, _]) => name),
    };
  }

  if (matches.length > 0) {
    const [fKey, fVal] = matches[0];
    return {
      id: fVal.id,
      categoryId: fVal.categoryId,
      categoryName: fVal.categoryName,
      displayChannels: Object.entries(map)
        .filter(([_, val]) => val.categoryId === fVal.categoryId)
        .map(([name, _]) => name),
    };
  }

  return null;
}

/**
 * Format mention channel yang bisa diklik: <#channel_id>
 */
function getChannelMention(key) {
const id = getChannelId(key)?.id;

if (id) {
  return `<#${id}>`; // Return channel mention with ID
}

const map = getChannelMap();
const channelData = Object.values(map).find((val) =>
  val.name?.toLowerCase().includes(normalizedKey) || val.description?.toLowerCase().includes(normalizedKey)
);

return channelData
  ? `**[Channel "** <#${channelData.id}> **"]**` // Return clickable channel mention even for fallback
  : `**[Channel tidak diketemukan untuk input "${key}"]**`;
}

function getValidRouteKeys() {
  return Object.keys(getChannelMap());
}

function formatChannelListForPrompt() {
  const channels = getChannelMap();
  const lines = Object.entries(channels).map(([key, val]) => {
    return `  - "${key}" → #${val.name} (${val.description})`;
  });
  return lines.join("\n");
}

function refreshCache() {
  channelsCache = null;
  console.log("[PHRP-AI] Channel cache refreshed.");
}

module.exports = {
  getChannelMap,
  getChannelId,
  getChannelMention,
  getValidRouteKeys,
  formatChannelListForPrompt,
  refreshCache,
};