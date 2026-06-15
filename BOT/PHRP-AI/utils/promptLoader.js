/**
 * PHRP-AI Prompt Loader
 * Load system prompt dari file markdown dan gabungkan dengan channel list + knowledge.
 */

const fs = require("fs");
const path = require("path");
const { formatChannelListForPrompt } = require("./channelManager");
const { formatServerInfoForPrompt } = require("./serverConfig");

const PROMPTS_DIR = path.join(__dirname, "..", "prompts");

function loadSystemPrompt() {
  const filePath = path.join(PROMPTS_DIR, "system-prompt.md");

  if (!fs.existsSync(filePath)) {
    console.error("[PHRP-AI] File prompts/system-prompt.md tidak ditemukan!");
    return "";
  }

  const content = fs.readFileSync(filePath, "utf-8");
  const clean = content.replace(/^# .+\n*/m, "").trim();

  console.log(`[PHRP-AI] System prompt loaded (${clean.length} chars).`);
  return clean;
}

/**
 * Build full prompt: base prompt + server info + channel list + knowledge context
 */
function buildFullPrompt(knowledgeContext) {
  const basePrompt = loadSystemPrompt();

  // Inject IP/Port server dari config.json
  const serverInfo = formatServerInfoForPrompt();
  const serverSection = `\n\nINFORMASI SERVER (dari config.json):\n${serverInfo}\n`;

  // Inject channel list
  const channelList = formatChannelListForPrompt();
  const channelSection = channelList
    ? `\n\nCHANNEL YANG TERSEDIA (route_key → channel):\n${channelList}\n`
    : "";

  let result = basePrompt + serverSection + channelSection;

  if (knowledgeContext) {
    result += "\n\n" + knowledgeContext;
  }

  return result;
}

module.exports = {
  loadSystemPrompt,
  buildFullPrompt,
};
