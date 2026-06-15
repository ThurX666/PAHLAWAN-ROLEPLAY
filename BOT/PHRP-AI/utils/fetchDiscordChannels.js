const { Client, GatewayIntentBits } = require("discord.js");
const fs = require("fs");
const path = require("path");

const CHANNELS_PATH = path.join(__dirname, "..", "config", "channels.json");

// Inisialisasi client Discord
const client = new Client({
  intents: [GatewayIntentBits.Guilds],
});

/**
 * Fungsi untuk mendapatkan semua channel dari server
 * dan menyimpannya di file channels.json
 */
client.once("ready", async () => {
  console.log(`${client.user.tag} terhubung ke Discord.`);

  try {
    // Ganti 'GUILD_ID' dengan ID server Discord kamu
    const guildId = "GUILD_ID";
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

    // Simpan ke channels.json
    fs.writeFileSync(CHANNELS_PATH, JSON.stringify(channelData, null, 2));
    console.log("Semua channel berhasil diambil dan disimpan.");
  } catch (error) {
    console.error("Terjadi error saat mengambil channel:", error);
  } finally {
    client.destroy();
  }
});

// Login ke Discord dengan Bot Token
const token = "YOUR_BOT_TOKEN";
client.login(token);