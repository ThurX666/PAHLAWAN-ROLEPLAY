/**
 * PHRP-AI Chat History Manager
 * Menyimpan riwayat percakapan per user.
 * Otomatis hapus jika tidak ada aktivitas selama 10 menit.
 */

const TIMEOUT_MS = 10 * 60 * 1000; // 10 menit
const MAX_HISTORY_PER_USER = 5; // max pasang chat (user+assistant) per user

const sessions = new Map();

function cleanupExpiredSessions() {
  const now = Date.now();
  const time = new Date().toLocaleString("id-ID", { timeZone: "Asia/Jakarta" });
  console.time(`[${time}] [LOG] Session Cleanup Duration`);
  let cleaned = 0;

  for (const [userId, session] of sessions.entries()) {
    if (now - session.lastActivity > TIMEOUT_MS) {
      sessions.delete(userId);
      cleaned++;
    }
  }

  if (cleaned > 0) {
    console.log(`[${time}] [PHRP-AI] Cleaned ${cleaned} expired session(s). Active: ${sessions.size}`);
    console.timeEnd(`[${time}] [LOG] Session Cleanup Duration`);
  }
}

setInterval(cleanupExpiredSessions, 2 * 60 * 1000);

function getHistory(userId) {
  const session = sessions.get(userId);
  const time = new Date().toLocaleString("id-ID", { timeZone: "Asia/Jakarta" });
  if (!session) return [];

  if (Date.now() - session.lastActivity > TIMEOUT_MS) {
    sessions.delete(userId);
    console.log(`[${time}] [PHRP-AI] Session ${userId} expired (10min inactivity).`);
    return [];
  }

  return session.messages;
}

function addMessage(userId, role, content) {
  const time = new Date().toLocaleString("id-ID", { timeZone: "Asia/Jakarta" });
  console.log(`[${time}] [LOG] Adding message for session ${userId}: [Role: ${role}] [Content: ${content.slice(0, 50)}...]`);
  let session = sessions.get(userId);
  if (!session) {
    session = { messages: [], lastActivity: Date.now() };
    sessions.set(userId, session);
  }

  session.lastActivity = Date.now();
  session.messages.push({ role, content });

  if (session.messages.length > MAX_HISTORY_PER_USER * 2) {
    session.messages = session.messages.slice(-MAX_HISTORY_PER_USER * 2);
  }
}

function addConversation(userId, userMessage, assistantMessage) {
  addMessage(userId, "user", userMessage);
  addMessage(userId, "assistant", assistantMessage);
}

function clearHistory(userId) {
  const time = new Date().toLocaleString("id-ID", { timeZone: "Asia/Jakarta" });
  sessions.delete(userId);
  console.log(`[${time}] [PHRP-AI] Cleared session for ${userId}.`);
}

function clearAllHistory() {
  const time = new Date().toLocaleString("id-ID", { timeZone: "Asia/Jakarta" });
  sessions.clear();
  console.log(`[${time}] [PHRP-AI] All sessions cleared.`);
}

function getFormattedHistory(userId) {
  const history = getHistory(userId);
  return history.filter((m) => m.role === "user" || m.role === "assistant").slice(-MAX_HISTORY_PER_USER * 2);
}

module.exports = {
  getHistory,
  addMessage,
  addConversation,
  clearHistory,
  clearAllHistory,
  getFormattedHistory,
  cleanupExpiredSessions,
};