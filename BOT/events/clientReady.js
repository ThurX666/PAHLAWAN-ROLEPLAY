module.exports = {
  name: ["clientReady"],
  once: true,
  async execute(client) {
    console.log(`Ready!!! ${client.user.tag} is logged in and online.`);

    // Mengambil semua channel dari server Discord dan menyimpannya ke file
    const CHANNELS_PATH = require("path").join(__dirname, "../PHRP-AI/config/channels.json");
    const fs = require("fs");

    const { guildId } = require("../config.json"); // Mengambil guildId dari config.json
    try {
      const guild = await client.guilds.fetch(guildId);
      const channels = await guild.channels.fetch();

      const channelData = {};
      channels.forEach((channel) => {
        if (channel.type === 0 || channel.type === 2) {
          // Hanya menyimpan text dan voice channels
          channelData[channel.name] = {
            id: channel.id,
            name: channel.name,
            description: channel.topic || "Tidak ada deskripsi",
          };
        }
      });

      fs.writeFileSync(CHANNELS_PATH, JSON.stringify(channelData, null, 2));
      console.log(`[clientReady] Semua channel berhasil diambil dan disimpan.`);
    } catch (error) {
      console.error("[clientReady] Gagal mengambil channel Discord:", error);
    }

    if (typeof client.checkVerifications === "function") {
      try {
        await client.checkVerifications();
      } catch (error) {
        console.error(`[clientReady][VerificationWatcher]: Gagal menjalankan pemeriksaan awal verifikasi.`, error);
      }

      setInterval(client.checkVerifications, 1000 * 10);
    }

    const updatePresence = () => {
      const targetDate = new Date("2026-11-01T00:00:00");
      const now = new Date();
      const diff = targetDate - now;

      let activityName = "PHRP is LIVE! 🚀";
      if (diff > 0) {
        const days = Math.floor(diff / (1000 * 60 * 60 * 24));
        const hours = Math.floor((diff % (1000 * 60 * 60 * 24)) / (1000 * 60 * 60));
        const minutes = Math.floor((diff % (1000 * 60 * 60)) / (1000 * 60));
        const seconds = Math.floor((diff % (1000 * 60)) / 1000);

        activityName = `Launch: ${days}d ${hours}h ${minutes}m ${seconds}s remaining!`;
      }

      // Validasi keberadaan shard 0 sebelum memperbarui kehadiran
      if (client.ws.shards.has(0)) {
        client.user.setPresence({
          activities: [{ 
            name: activityName, 
            type: 0 // 0 itu 'PLAYING'
          }],
          status: "idle",
        });
      } else {
        console.error("[clientReady] Gagal memperbarui kehadiran: Shard 0 tidak ditemukan.");
      }
    };

    // Jalankan pertama kali saat bot ready
    updatePresence();
    // Update setiap 10 detik agar detik terasa dinamis tanpa kena rate-limit
    setInterval(() => {
      try {
        updatePresence();
      } catch (error) {
        console.error("[updatePresence] Gagal memperbarui presence:", error);
      }
    }, 1000 * 10);

    //console.log(`API Latency: ${client.ws.ping}ms`);
  },
};