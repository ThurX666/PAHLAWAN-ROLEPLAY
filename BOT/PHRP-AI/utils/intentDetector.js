/**
 * PHRP-AI Intent Detector
 * Mendeteksi intent dari percakapan user dan response AI.
 * Tujuannya: AI tidak perlu pusing mikirin format JSON, AI tinggal ngobrol natural.
 * Bot yang handle routing & database query.
 */

/**
 * Cek apakah user menanyakan tentang pemain tertentu (nama in-game).
 * Contoh: "siapa Arthur_Clinton?", "Arthur_Clinton admin gak?", "cek player Arthur"
 * 
 * PENTING: Harus ngecek apakah teks itu DISCORD ID atau bukan.
 * Discord ID: 17-19 digit angka, misal 737722980309794866
 * Nama SA-MP: biasanya ada underscore atau huruf + angka, misal Arthur_Clinton
 */
function detectPlayerQuery(userMessage) {
  if (!userMessage) return null;

  // Kalau pesan HANYA angka 17-19 digit, anggap sebagai Discord ID, BUKAN player query
  // (biar intent.find_by_discord yang handle)
  if (/^\d{17,20}$/.test(userMessage.trim())) {
    return null;
  }

  // Filter token: hanya anggap sebagai nama player kalau TIDAK terlihat seperti angka murni
  // atau kata ganti orang / kata-kata umum Indonesia
  const COMMON_STOPWORDS = new Set([
    "aku", "kamu", "kami", "kita", "mereka", "dia", "ini", "itu",
    "sih", "ya", "ga", "gak", "nggak", "yaudah", "lah", "kok", "sih",
    "kan", "dong", "deh", "tuh", "ni", "aja", "saja", "kok", "koq",
    "sich", "si", "doang", "ajah", "bahkan", "juga", "tetapi", "tapi",
    "kenapa", "gimana", "bagaimana", "dimana", "kapan", "siapa", "apa",
    "mana", "sini", "situ", "situ", "sekarang", "tadi", "nanti", "besok"
  ]);

  const isLikelyName = (str) => {
    if (!str) return false;
    if (/^\d+$/.test(str)) return false; // angka murni, bukan nama
    if (str.length < 3) return false;
    if (str.length > 30) return false;
    // Harus mengandung minimal 1 huruf
    if (!/[a-zA-Z]/.test(str)) return false;
    // BUKAN stopword Indonesia
    if (COMMON_STOPWORDS.has(str.toLowerCase())) return false;
    return true;
  };

  const playerPatterns = [
    /siapa\s+([A-Za-z][\w]{2,})/i,
    /cek\s+(player|pemain|user|orang|nick)\s+([A-Za-z][\w]{2,})/i,
    /([A-Za-z][\w_]{3,})\s+(admin|staff|mod|owner|helper)\s*(gk|ga|nggak|tidak)?/i,
    /cari\s+(player|pemain|orang)\s+([A-Za-z][\w]{2,})/i,
    /info\s+(player|pemain)\s+([A-Za-z][\w]{2,})/i,
    /status\s+([A-Za-z][\w_]{3,})/i,
  ];

  for (const pattern of playerPatterns) {
    const match = userMessage.match(pattern);
    if (match) {
      const name = match[match.length - 1];
      if (isLikelyName(name)) {
        return name;
      }
    }
  }

  return null;
}

/**
 * Cek apakah user menanyakan channel/lokasi tertentu.
 * Contoh: "dimana daftar?", "channel register dimana?", "cara daftar"
 */
function detectRouteIntent(userMessage) {
  const routePatterns = [
    { keywords: ["daftar", "register", "registrasi", "buat akun", "bikin akun"], key: "register" },
    { keywords: ["bantuan", "help", "tolong", "bantu"], key: "help" },
    { keywords: ["lapor", "report", "laporkan"], key: "report" },
    { keywords: ["aturan", "rules", "peraturan", "larangan"], key: "rules" },
    { keywords: ["obrol", "umum", "chat", "ngobrol", "general"], key: "general" },
    { keywords: ["info", "informasi", "pengumuman"], key: "info" },
    { keywords: ["faction", "recruitment", "rekrut", "gabung faction"], key: "faction-recruitment" },
    { keywords: ["saran", "masukan", "suggest"], key: "suggestions" },
    { keywords: ["support", "dukungan", "teknis"], key: "support" },
    { keywords: ["giveaway", "event", "hadiah"], key: "giveaway" },
  ];

  const lower = userMessage.toLowerCase();

  // Prioritaskan "dimana", "channel", "di mana"
  const hasWhere = /\b(dimana|di mana|channel|dimana|kemana|ke mana)\b/i.test(lower);

  for (const route of routePatterns) {
    const matchKeyword = route.keywords.some(kw => lower.includes(kw));
    if (matchKeyword && hasWhere) {
      return route.key;
    }
    // Juga detect "cara daftar", "gimana daftar" tanpa kata "dimana"
    if (matchKeyword && /\b(cara|gimana|bagaimana)\b/i.test(lower)) {
      return route.key;
    }
  }

  return null;
}

/**
 * Cek apakah user hanya ngobrol santai / salam.
 */
function isCasualChat(userMessage) {
  const casualPatterns = [
    /^halo/i, /^hey/i, /^hei/i, /^hai/i, /^hi/i, /^test/i, /^tes/i,
    /^p$/i, /^bot$/i, /^siang/i, /^pagi/i, /^malam/i, /^sore/i,
    /^makasih/i, /^terima kasih/i, /^thanks/i, /^thx/i,
    /^dadah/i, /^bye/i, /^sampai jumpa/i, /^daah/i,
    /^apa kabar/i, /^gmn kabar/i, /^kabar/i,
    /^yoi/i, /^yo/i, /^gas/i,
    /^ok/i, /^oke/i, /^okey/i, /^okedeh/i,
    /^nice/i, /^mantap/i, /^mantul/i,
  ];

  return casualPatterns.some(p => p.test(userMessage.trim()));
}

/**
 * Cek apakah pesan user menanyakan IP server.
 */
function detectIpQuery(userMessage) {
  const lower = userMessage.toLowerCase();
  const ipPatterns = [
    /\bip\b/, /\balamat\b.*\bserver\b/, /\bconnection\b/, /\bconnect\b/,
    /\bport\b/, /\bplay\b/, /\bmain\b/, /\bmasuk\b.*\bserver\b/,
  ];
  return ipPatterns.some(p => p.test(lower));
}

/**
 * Cek apakah user menanyakan tentang info umum server.
 */
function detectGeneralInfo(userMessage) {
  const lower = userMessage.toLowerCase();
  const infoPatterns = [
    /tentang\s+server/i, /info\s+server/i, /server\s+ini/i,
    /ceritain\s+tentang/i, /jelasin\s+tentang/i,
    /perkenalan/i, /kenalan/i,
    /apa\s+itu\s+phrp/i, /phrp\s+itu\s+apa/i,
  ];
  return infoPatterns.some(p => p.test(lower));
}

module.exports = {
  detectPlayerQuery,
  detectRouteIntent,
  isCasualChat,
  detectIpQuery,
  detectGeneralInfo,
};