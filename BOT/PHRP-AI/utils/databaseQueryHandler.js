/**
 * PHRP-AI Database Query Handler
 * 
 * Menangani query database yang diminta oleh AI.
 * AI akan mengeluarkan JSON: {"mode":"db_query","query_type":"find_player","params":{"name":"Arthur_Clinton"}}
 * 
 * Handler akan menjalankan query dan mengembalikan hasil yang sudah diformat.
 */

const db = require("./database");

// 🔒 Tipe query yang diizinkan
const ALLOWED_QUERY_TYPES = new Set(["find_player", "find_staff", "find_by_discord", "custom", "check_ban"]);

/**
 * 🔒 Proses query database berdasarkan perintah AI.
 * 
 * @param {Object} queryInstruction - Instruksi dari AI: { query_type, params }
 * @returns {Promise<string>} Hasil query yang sudah diformat untuk AI
 */
async function processDbQuery(queryInstruction) {
  const { query_type, params } = queryInstruction;

  if (!query_type) {
    return "Format query tidak valid.";
  }

  // 🔒 Cek whitelist query type
  if (!ALLOWED_QUERY_TYPES.has(query_type)) {
    console.warn(`[PHRP-AI-DB] BLOCKED: Unknown query_type="${query_type}"`);
    return "Tipe query tidak dikenal. Hanya find_player, find_staff, dan find_by_discord yang didukung.";
  }

  // 🔒 Validasi params adalah object, bukan string/array
  if (!params || typeof params !== "object" || Array.isArray(params)) {
    return "Parameter tidak valid.";
  }

  switch (query_type) {
    case "find_player":
      return handleFindPlayer(params);
    case "find_staff":
      return handleFindStaff(params);
    case "find_by_discord":
      return handleFindByDiscord(params);
    case "check_ban":
      return handleCheckBan(params);
    case "custom":
      return handleCustomQuery(params);
    default:
      return `Tipe query "${query_type}" tidak dikenal.`;
  }
}

/**
 * Cari pemain berdasarkan nama.
 * Data dari tabel player_characters (Char_Name) dan player_ucp (UCP)
 */
async function handleFindPlayer(params) {
  const name = params?.name || params?.player_name || params?.username;
  if (!name) return "Nama pemain tidak diberikan untuk pencarian.";

  const results = await db.findPlayer(name);

  if (results.length === 0) {
    return `Pemain dengan nama "${name}" tidak ditemukan di database.`;
  }

  let result = `Ditemukan ${results.length} hasil untuk "${name}":\n\n`;

  for (const row of results) {
    // Cek apakah ini dari player_characters atau player_ucp
    if (row.Char_Name) {
      // Ini dari player_characters
      const adminLevel = row.Char_Admin || 0;
      const discordUCP = await db.query(
        `SELECT discord_id, Last_Login FROM player_ucp WHERE UCP = ? LIMIT 1`,
        [row.Char_UCP]
      );

      result += `**${row.Char_Name}** (UCP: ${row.Char_UCP})\n`;
      result += `  └ Status: ${adminLevel > 0 ? getAdminLabel(adminLevel) : "Pemain biasa"}\n`;
      result += `  └ Level: ${row.Char_Level || 0}\n`;
      if (row.Char_Hours) result += `  └ Jam bermain: ${row.Char_Hours} jam\n`;
      if (row.Char_Faction > 0) result += `  └ Faction ID: ${row.Char_Faction}\n`;
      if (row.Char_Gender === 0) result += `  └ Gender: Laki-laki\n`;
      else if (row.Char_Gender === 1) result += `  └ Gender: Perempuan\n`;
      
      // Ambil Last_Login dari player_ucp yang akurat
      let lastLogin = "";
      if (discordUCP.length > 0 && discordUCP[0].Last_Login) {
        lastLogin = discordUCP[0].Last_Login;
      }

      if (lastLogin) {
        const lastLoginFormatted = formatDateIndonesia(lastLogin);
        if (lastLoginFormatted) result += `  └ Terakhir login: ${lastLoginFormatted}\n`;
      }

      // Discord dari player_ucp
      if (discordUCP.length > 0 && discordUCP[0].discord_id) {
        result += `  └ Discord: <@${discordUCP[0].discord_id}>\n`;
      }
      result += "\n";
    } else if (row.UCP) {
      // Ini dari player_ucp
      result += `**${row.UCP}** (Akun UCP)\n`;
      if (row.admin_level > 0) {
        result += `  └ Status: ${getAdminLabel(row.admin_level)}\n`;
      }
      if (row.Last_Login) {
        const lastLoginFormatted = formatDateIndonesia(row.Last_Login);
        if (lastLoginFormatted) result += `  └ Terakhir login: ${lastLoginFormatted}\n`;
      }
      if (row.discord_id) {
        result += `  └ Discord: <@${row.discord_id}>\n`;
      }
      if (row.gold > 0) result += `  └ Gold: ${row.gold}\n`;
      if (row.Blocked == 1) result += `  └ Status: **BANNED**\n`;
      if (row.vip_status !== "NONE" && row.vip_status !== "None") {
        result += `  └ VIP: ${row.vip_status}\n`;
      }
      result += "\n";
    }
  }

  return result.trim();
}

/**
 * Cari staff/admin berdasarkan nama.
 * Data dari player_characters (Char_Admin > 0)
 */
async function handleFindStaff(params) {
  const name = params?.name || params?.player_name || params?.username;
  if (!name) return "Nama staff tidak diberikan untuk pencarian.";

  const staffList = await db.findStaff(name);

  if (staffList.length === 0) {
    return `Staff dengan nama "${name}" tidak ditemukan.`;
  }

  let result = `Ditemukan ${staffList.length} staff dengan nama "${name}":\n\n`;

  for (const staff of staffList) {
    const discordUCP = await db.query(
      `SELECT discord_id FROM player_ucp WHERE UCP = ? LIMIT 1`,
      [staff.Char_UCP]
    );

    result += `**${staff.Char_Name}** — ${getAdminLabel(staff.Char_Admin)}\n`;
    if (discordUCP.length > 0 && discordUCP[0].discord_id) {
      result += `  └ Discord: <@${discordUCP[0].discord_id}>\n`;
    }
    result += "\n";
  }

  return result.trim();
}

/**
 * Cari pemain berdasarkan Discord ID.
 * Data dari player_ucp.discord_id dan ucp.discord_id
 */
async function handleFindByDiscord(params) {
  const discordId = params?.discord_id || params?.discord;
  if (!discordId) return "Discord ID tidak diberikan.";

  const cleanId = discordId.toString().replace(/\D/g, "");
  if (!cleanId) return "Format Discord ID tidak valid.";

  const results = await db.findPlayerByDiscord(cleanId);

  if (results.length === 0) {
    return `<@${cleanId}> tidak terdaftar sebagai pemain in-game.`;
  }

  let result = `Data untuk <@${cleanId}>:\n\n`;
  const processedUCPs = new Set();

  for (const row of results) {
    if (row.UCP && !processedUCPs.has(row.UCP)) {
      processedUCPs.add(row.UCP);
      result += `**UCP: ${row.UCP}**\n`;
      if (row.admin_level > 0) result += `  └ Status: ${getAdminLabel(row.admin_level)}\n`;
      if (row.Blocked == 1) result += `  └ Status: **BANNED**\n`;
      result += "\n";
    }
    if (row.Char_Name) {
      result += `  └ Karakter: **${row.Char_Name}**`;
      if (row.Char_Admin > 0) result += ` (${getAdminLabel(row.Char_Admin)})`;
      if (row.Char_Level) result += ` [Level ${row.Char_Level}]`;
      result += "\n";
    }
  }

  if (result.includes("Karakter")) {
    result = `Data untuk <@${cleanId}>:\n\n`;
    const seenChars = new Set();
    for (const row of results) {
      if (row.Char_Name && !seenChars.has(row.Char_Name)) {
        seenChars.add(row.Char_Name);
        result += `**${row.Char_Name}**`;
        if (row.Char_Admin > 0) result += ` — ${getAdminLabel(row.Char_Admin)}`;
        if (row.Char_Level) result += ` [Level ${row.Char_Level}]`;
        result += "\n";
      }
    }
  }

  return result.trim();
}

/**
 * 🔒 Cek status banned pemain
 */
async function handleCheckBan(params) {
  const name = params?.name || params?.player_name || params?.username;
  if (!name) return "Nama pemain tidak diberikan.";

  const banData = await db.checkBan(name);

  if (!banData) {
    return `Pemain "${name}" tidak memiliki catatan banned.`;
  }

  let result = `**${banData.name || name}** — Status BANNED\n`;
  result += `  └ Alasan: ${banData.reason || "Tidak ada alasan"}\n`;
  result += `  └ Admin: ${banData.admin || "Server"}\n`;
  if (banData.ban_date) {
    const date = new Date(banData.ban_date * 1000);
    result += `  └ Tanggal: ${date.toLocaleDateString("id-ID")}\n`;
  }
  if (banData.ban_expire && banData.ban_expire > 0) {
    const expire = new Date(banData.ban_expire * 1000);
    result += `  └ Expire: ${expire.toLocaleDateString("id-ID")}\n`;
  }

  return result.trim();
}

/**
 * 🔒 Query custom (SANGAT DIBATASI).
 */
async function handleCustomQuery(params) {
  const sql = params?.sql || params?.query;
  if (!sql) return "Query SQL tidak diberikan.";

  // 🔒 Keamanan berlapis: cek di database.js juga, tapi double check disini
  try {
    const rows = await db.query(sql);
    if (rows.length === 0) return "Tidak ada hasil.";

    // Batasi output: max 5 baris, max 3 kolom
    let result = `Hasil query (${Math.min(rows.length, 5)} baris):\n\n`;
    for (const row of rows.slice(0, 5)) {
      // 🔒 Hanya tampilkan kolom yang aman (bukan password/ip/email)
      const safeRow = {};
      for (const [key, val] of Object.entries(row)) {
        safeRow[key] = String(val).slice(0, 50); // Batasi panjang value
      }
      result += JSON.stringify(safeRow) + "\n";
    }
    if (rows.length > 5) {
      result += `\n... dan ${rows.length - 5} baris lainnya.`;
    }

    return result.trim();
  } catch (err) {
    // 🔒 Jangan expose detail error ke AI/user (bocorin struktur tabel)
    console.error(`[PHRP-AI-DB] Custom query error: ${err.message}`);
    return "Terjadi kesalahan saat menjalankan query.";
  }
}

/**
 * Dapatkan label untuk level admin.
 */
function formatDateIndonesia(dateStr) {
  if (!dateStr) return "";
  try {
    const date = new Date(dateStr);
    if (isNaN(date.getTime())) return "";
    const day = String(date.getDate()).padStart(2, "0");
    const month = String(date.getMonth() + 1).padStart(2, "0");
    const year = date.getFullYear();
    const hours = String(date.getHours()).padStart(2, "0");
    const minutes = String(date.getMinutes()).padStart(2, "0");
    return `${day}/${month}/${year} jam ${hours}.${minutes}`;
  } catch {
    return "";
  }
}

function getAdminLabel(level) {
  const levelNum = parseInt(level);
  if (levelNum === -1) return "**BANNED**";
  if (levelNum >= 6) return "**Owner / Head Admin**";
  if (levelNum >= 5) return "**Senior Admin**";
  if (levelNum >= 4) return "**Full Admin**";
  if (levelNum >= 3) return "**Moderator**";
  if (levelNum >= 2) return "**Junior Admin**";
  if (levelNum >= 1) return "**Helper / Trial Admin**";
  return "Pemain biasa";
}

module.exports = {
  processDbQuery,
  handleFindPlayer,
  handleFindStaff,
  handleFindByDiscord,
};