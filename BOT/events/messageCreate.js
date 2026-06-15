const phrp = require("../PHRP-AI");
const intent = require("../PHRP-AI/utils/intentDetector");

function cleanAIResponse(text) {
  if (!text) return text;
  let cleaned = text.trim();
  cleaned = cleaned.replace(/\[QUERY:[^\]]+\]/g, "").trim();
  const jsonMatch = cleaned.match(/\{[\s\S]*\}/);
  if (jsonMatch) {
    try {
      const obj = JSON.parse(jsonMatch[0]);
      if (obj.message && typeof obj.message === "string") return obj.message;
    } catch (e) {}
  }
  return cleaned;
}

function detectAIQuery(rawResponse) {
  const match = rawResponse.match(/\[QUERY:([\w_]+):([^\]]+)\]/);
  if (!match) return null;
  return { type: match[1], value: match[2].trim() };
}

module.exports = {
  name: "messageCreate",

  async execute(message, client) {
    if (message.author.id === client.user.id || message.author.bot) return;
    if (message.channel.id === "835762642844778496" || message.channel.id === "1128750866795593788") {
      const userId = message.author.id;
      const userMessage = message.content;

      const safeReply = async (targetMessage, payload) => {
        const base = typeof payload === "string" ? { content: payload } : { ...payload };
        try {
          return await targetMessage.reply(base);
        } catch (err) {
          const hasUnknownReference =
            (err && err.code === 50035 && err.rawError && err.rawError.errors && err.rawError.errors.message_reference !== undefined) ||
            err.code === 10008;
          if (!hasUnknownReference) throw err;
          const fallback = { ...base };
          const mention = (targetMessage.author && targetMessage.author.toString) ? targetMessage.author.toString() : "";
          if (fallback.content) fallback.content = (mention ? `${mention} ` : "") + fallback.content;
          else if (mention) fallback.content = mention;
          return targetMessage.channel.send(fallback);
        }
      };

      const sendResponse = async (text) => {
        text = cleanAIResponse(text);
        const MAX = 1995;
        if (text.length > MAX) {
          await safeReply(message, text.slice(0, MAX) + "...");
          await safeReply(message, "..." + text.slice(MAX));
        } else {
          await safeReply(message, text);
        }
        phrp.addMessage(userId, "assistant", text.slice(0, MAX));
      };

      const executeDBQuery = async (type, value) => {
        const params = type === "find_by_discord" ? { discord_id: value } : { name: value };
        return await phrp.processDbQuery({ query_type: type, params });
      };

      try {
        await message.channel.sendTyping();

        phrp.addMessage(userId, "user", userMessage);

        // FAST-PATH 1: Discord ID
        if (/^\d{17,20}$/.test(userMessage.trim())) {
          const dbResult = await executeDBQuery("find_by_discord", userMessage.trim());
          if (dbResult.includes("tidak terdaftar") || dbResult.includes("tidak ditemukan")) {
            await sendResponse("Hmm, Discord ID <@" + userMessage.trim() + "> belum terdaftar sebagai pemain di PHRP nih. Coba aja daftar dulu ya 😄");
          } else {
            await sendResponse(dbResult.replace(/^.*?(?=\*\*)/s, "").trim() || dbResult);
          }
          return;
        }

        // FAST-PATH 2: Route
        const routeKey = intent.detectRouteIntent(userMessage);
        if (routeKey) {
          const mention = phrp.getChannelMention(routeKey);
          if (mention) {
            await sendResponse("Silakan menuju ke channel " + mention + " untuk info lebih lanjut 😄");
            return;
          }
        }

        // FAST-PATH 3: IP
        if (intent.detectIpQuery(userMessage)) {
          await sendResponse("IP server PHRP: **" + phrp.getServerAddress() + "**. Connect aja bro! 🚗💨");
          return;
        }

        // FAST-PATH 4: Info umum
        if (intent.detectGeneralInfo(userMessage)) {
          await sendResponse("PHRP tuh server SA-MP yang didirikan 1 November 2020 sama ThurX. Komunitasnya aktif banget, banyak event seru! 😄");
          return;
        }

        // FAST-PATH 5: Casual chat
        if (intent.isCasualChat(userMessage)) {
          const r = ["Halo juga bro! Ada yang bisa saya bantu soal PHRP? 🫡","Hei! Mau tau info apa tentang server hari ini? 😄","Yoo! Ada yang bisa dibantu? 😎"];
          await sendResponse(r[Math.floor(Math.random() * r.length)]);
          return;
        }

        // === Tanya AI 1x — AI decide perlu query atau engga ===
        const knowledgeDB = phrp.getKnowledgeDB();
        const relevant = phrp.retrieveRelevantKnowledge(userMessage, knowledgeDB, 3);
        const knowledgeContext = phrp.formatKnowledgeContext(relevant);
        const fullSystemPrompt = phrp.buildFullPrompt(knowledgeContext);

        const history = phrp.getFormattedHistory(userId);
        const messages = [
          { role: "system", content: fullSystemPrompt },
          ...history.slice(-6),
          { role: "user", content: userMessage }
        ];

        let raw = await phrp.sendMessage(messages);
        if (!raw) {
          await sendResponse("Maaf bro, saya lagi error nih. Coba ulangi lagi ya 😅");
          return;
        }

        const aiQuery = detectAIQuery(raw);
        if (aiQuery) {
          // Langsung query DB dan format tanpa panggil AI lagi (hemat 1 API call)
          const dbResult = await executeDBQuery(aiQuery.type, aiQuery.value);

          // Format langsung tanpa AI kedua
          const cleaned = dbResult.replace(/^.*?(?=\*\*)/s, "").trim() || dbResult;
          await sendResponse(cleaned);
          return;
        }

        await sendResponse(raw);

      } catch (error) {
        console.error("[ERROR]", error.message);
        if (error.response) {
          console.error(error.response.status, error.response.data);
          await safeReply(message, "Oops, terjadi kesalahan. Mohon coba lagi nanti. :robot::satellite:");
        } else {
          await safeReply(message, "Oops, terjadi kesalahan. Kami akan segera memperbaikinya. :robot::tools:");
        }
      }
    }
  },
};