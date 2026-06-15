/**
 * PHRP-AI — Sistem AI Modular untuk Pahlawan Roleplay
 *
 * Semua komponen AI sudah dipisah secara modular:
 *
 * PHRP-AI/
 * ├── config/
 * │   └── channels.json       # Daftar channel Discord (isi ID channel disini)
 * ├── knowledge/
 * │   ├── server-info.md      # Info dasar server
 * │   ├── rules.md            # Peraturan server
 * │   ├── commands.md         # Daftar command in-game
 * │   └── factions.md         # Info faction-faction
 * ├── prompts/
 * │   └── system-prompt.md    # System prompt untuk AI
 * └── utils/
 *     ├── knowledgeLoader.js  # Load & retrieve knowledge dari file .md
 *     ├── channelManager.js   # Load & manage channel dari config JSON
 *     ├── promptLoader.js     # Load & compose system prompt
 *     └── chatHistory.js      # Chat history per-user dengan auto-expire
 *
 * Cara pakai di event handler:
 *   const phrp = require("../PHRP-AI");
 *   const prompt = phrp.buildFullPrompt(knowledgeContext);
 *   const history = phrp.getFormattedHistory(userId);
 *   const mention = phrp.getChannelMention("register"); // return <#channelId>
 */

const knowledgeLoader = require("./utils/knowledgeLoader");
const channelManager = require("./utils/channelManager");
const promptLoader = require("./utils/promptLoader");
const chatHistory = require("./utils/chatHistory");
const aiProvider = require("./utils/aiProvider");
const serverConfig = require("./utils/serverConfig");
const database = require("./utils/database");
const dbQueryHandler = require("./utils/databaseQueryHandler");

module.exports = {
  // Knowledge
  getKnowledgeDB: knowledgeLoader.getKnowledgeDB,
  retrieveRelevantKnowledge: knowledgeLoader.retrieveRelevantKnowledge,
  formatKnowledgeContext: knowledgeLoader.formatKnowledgeContext,

  // Channels
  getChannelMap: channelManager.getChannelMap,
  getChannelId: channelManager.getChannelId,
  getChannelMention: channelManager.getChannelMention,
  getValidRouteKeys: channelManager.getValidRouteKeys,
  formatChannelListForPrompt: channelManager.formatChannelListForPrompt,
  refreshChannels: channelManager.refreshCache,

  // Prompt
  loadSystemPrompt: promptLoader.loadSystemPrompt,
  buildFullPrompt: promptLoader.buildFullPrompt,

  // Chat History
  getHistory: chatHistory.getHistory,
  getFormattedHistory: chatHistory.getFormattedHistory,
  addMessage: chatHistory.addMessage,
  addConversation: chatHistory.addConversation,
  clearHistory: chatHistory.clearHistory,
  clearAllHistory: chatHistory.clearAllHistory,

  // AI Provider
  sendMessage: aiProvider.sendMessage,
  setProvider: aiProvider.setProvider,
  getActiveProvider: aiProvider.getActiveProvider,
  getAvailableProviders: aiProvider.getAvailableProviders,
  reloadConfig: aiProvider.reloadConfig,

  // Server Config
  getServerConfig: serverConfig.getServerConfig,
  getServerAddress: serverConfig.getServerAddress,
  refreshServerConfig: serverConfig.refreshCache,

  // Database
  initDatabase: database.initPool,
  query: database.query,
  findPlayer: database.findPlayer,
  findStaff: database.findStaff,
  findPlayerByDiscord: database.findPlayerByDiscord,
  checkBan: database.checkBan,
  getConnectionStatus: database.getConnectionStatus,
  closePool: database.closePool,
  processDbQuery: dbQueryHandler.processDbQuery,
};