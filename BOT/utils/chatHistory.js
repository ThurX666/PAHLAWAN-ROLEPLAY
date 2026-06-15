/**
 * Chat History Manager
 * Menyimpan riwayat percakapan per user.
 * Otomatis hapus jika tidak ada aktivitas selama 10 menit.
 */

const TIMEOUT_MS = 10 * 60 * 1000; // 10 menit
const MAX_HISTORY_PER_USER = 10; // max pasang chat (user+assistant) per user

// Map<userId, { messages: [], lastActivity: timestamp }>
const sessions = new Map();

/**
 * Bersihkan session yang sudah expired (timeout 10 menit)
 */
function cleanupExpiredSessions() {
  const now = Date.now();
  let cleaned = 0;

  for (const [userId, session] of sessions.entries()) {
    if (now - session.lastActivity > TIMEOUT_MS) {
      sessions.delete(userId);
      cleaned++;
    }
  }

  if (cleaned > 0) {
    console.log(`[ChatHistory] Cleaned ${cleaned} expired session(s). Active: ${sessions.size}`);
  }
}

// Jalankan cleanup setiap 2 menit
setInterval(cleanupExpiredSessions, 2 * 60 * 1000);

/**
 * Dapatkan history messages untuk user tertentu.
 * @param {string} userId
 * @returns {Array} array of {role, content}
 */
function getHistory(userId) {
  const session = sessions.get(userId);

  if (!session) {
    return [];
  }

  // Cek expired
  if (Date.now() - session.lastActivity > TIMEOUT_MS) {
    sessions.delete(userId);
    console.log(`[ChatHistory] Session ${userId} expired (10min inactivity).`);
    return [];
  }

  return session.messages;
}

/**
 * Tambah pesan ke history user.
 * @param {string} userId
 * @param {string} role - "user" | "assistant" | "system"
 * @param {string} content
 */
function addMessage(userId, role, content) {
  let session = sessions.get(userId);

  if (!session) {
    session = { messages: [], lastActivity: Date.now() };
    sessions.set(userId, session);
  }

  // Update timestamp
  session.lastActivity = Date.now();

  // Tambah pesan
  session.messages.push({ role, content });

  // Batasi jumlah history (buang yang paling lama)
  if (session.messages.length > MAX_HISTORY_PER_USER * 2) {
    session.messages = session.messages.slice(-MAX_HISTORY_PER_USER * 2);
  }
}

/**
 * Tambah pesan user + response assistant sekaligus.
 * @param {string} userId
 * @param {string} userMessage
 * @param {string} assistantMessage
 */
function addConversation(userId, userMessage, assistantMessage) {
  addMessage(userId, "user", userMessage);
  addMessage(userId, "assistant", assistantMessage);
}

/**
 * Hapus history user tertentu.
 * @param {string} userId
 */
function clearHistory(userId) {
  sessions.delete(userId);
  console.log(`[ChatHistory] Cleared session for ${userId}.`);
}

/**
 * Hapus semua session.
 */
function clearAllHistory() {
  sessions.clear();
  console.log("[ChatHistory] All sessions cleared.");
}

/**
 * Format history untuk dikirim ke API (OpenAI-compatible array).
 * @param {string} userId
 * @returns {Array} array of {role, content}
 */
function getFormattedHistory(userId) {
  const history = getHistory(userId);

  // Hanya kirim user & assistant messages (system prompt dikirim terpisah)
  return history.filter((m) => m.role === "user" || m.role === "assistant");
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