const fs = require("fs");
const path = require("path");
const { formatChannelListForPrompt } = require("./channelManager");

const PROMPTS_DIR = path.join(__dirname, "..", "prompts");

/**
 * Load system prompt dari file markdown di folder prompts/.
 * File system-prompt.md adalah file utama yang selalu di-load.
 * File tambahan juga bisa di-load untuk komposisi prompt modular.
 */
function loadSystemPrompt() {
  const filePath = path.join(PROMPTS_DIR, "system-prompt.md");

  if (!fs.existsSync(filePath)) {
    console.error("[PromptLoader] File prompts/system-prompt.md tidak ditemukan!");
    return "";
  }

  const content = fs.readFileSync(filePath, "utf-8");

  // Hapus heading "# " di baris pertama (judul file)
  const clean = content.replace(/^# .+\n*/m, "").trim();

  console.log(`[PromptLoader] System prompt loaded (${clean.length} chars).`);
  return clean;
}

/**
 * Gabungkan system prompt dengan konteks knowledge + channel list.
 */
function buildFullPrompt(knowledgeContext) {
  const basePrompt = loadSystemPrompt();

  // Inject channel list dari config/channels.json
  const channelList = formatChannelListForPrompt();
  const channelSection = channelList
    ? `\n\nCHANNEL YANG TERSEDIA (route_key → channel):\n${channelList}\n`
    : "";

  let result = basePrompt + channelSection;

  if (knowledgeContext) {
    result += "\n\n" + knowledgeContext;
  }

  return result;
}

module.exports = {
  loadSystemPrompt,
  buildFullPrompt,
};
