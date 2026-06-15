const { SlashCommandBuilder, EmbedBuilder } = require('discord.js');

module.exports = {
  data: new SlashCommandBuilder()
    .setName('help')
    .setDescription('📖 Bantuan & Panduan Server SA-MP Roleplay'),

  async execute(interaction) {

    const embed = new EmbedBuilder()
      .setColor('#ff0000')
      .setTitle('🚔 SA-MP Pahlawan ROLEPLAY | PLAYER GUIDE')
      .setDescription(
        `Selamat datang di server **SA-MP Pahlawan Roleplay**!\n` +
        `Gunakan channel di bawah ini untuk kebutuhan kamu sebagai warga.\n\n` +
        `📌 Semua command dibuat untuk membantu kamu bermain lebih nyaman!`
      )

      .addFields(
        {
          name: '📢 INFORMASI SERVER',
          value: `Cek update & info penting di <#785485108903673868>`,
        },
        {
          name: '🧑‍💼 KARAKTER & ROLEPLAY',
          value:
            `• Gunakan <#1089201373360435310> untuk daftar karakter\n` +
            `• Gunakan /stats untuk melihat profil karakter\n` +
            `• Jaga roleplay realistis (No FailRP, No RDM)`,
        },
        {
          name: '🛒 ECONOMY & SHOP',
          value:
            `• /shop → membeli item & kebutuhan\n` +
            `• /job → mencari pekerjaan\n` +
            `• /bank → akses uang & transfer`,
        },
        {
          name: '🎮 PLAYER SYSTEM',
          value:
            `• leaderboard pemain terbaik <#961615900371480586>\n` +
            `• /stats → statistik karakter\n` +
            `• Cek kota → <#961615900371480586>`,
        },
        {
          name: '📩 SUPPORT & REPORT',
          value:
            `• /report → lapor player bug, dan Sebagainya\n` +
            `• /ask → pertanyaan kepada admin \n` +
            `• Gunakan ticket di <#903310619506249798>\n` +
            `• Admin akan merespon secepat mungkin`,
        },
        {
          name: '⚠️ RULES PENTING',
          value:
            `• Dilarang RDM / VDM\n` +
            `• Dilarang Abuse Bug\n` +
            `• Hormati player lain\n` +
            `• Ikuti alur RP dengan benar`,
        }
      )

      .setFooter({ text: '🚔 SA-MP Pahlawan Roleplay • Stay in Character' })
      .setTimestamp();

    await interaction.reply({
        embeds: [embed]
    });
  }
};