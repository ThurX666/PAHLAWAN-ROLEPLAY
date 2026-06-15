const { 
  SlashCommandBuilder,
  ActionRowBuilder,
  ButtonBuilder,
  ButtonStyle,
  EmbedBuilder
} = require('discord.js');

const config = require('../../config.json');

module.exports = {
  data: new SlashCommandBuilder()
    .setName('payment')
    .setDescription('💳 Sistem pembayaran Pahlawan Roleplay'),

  async execute(interaction) {

    // ============================================
    // VALIDASI DEVELOPER
    // ============================================
    if (!config.developerIds.includes(interaction.user.id)) {

      const errorEmbed = new EmbedBuilder()
    .setColor(0xFF0000)

    .setAuthor({
        name: '❌ AKSES DITOLAK',
        iconURL: interaction.user.displayAvatarURL()
    })

    .setTitle('⚔️ PAHLAWAN ROLEPLAY • ACCESS DENIED')

    .setDescription(
        `🚫 **AKSES DITOLAK**

        Hanya **Developer Pahlawan Roleplay**
        yang dapat menggunakan command ini.

        ━━━━━━━━━━━━━━━━━━

        ⚠️ Kamu tidak memiliki izin
        untuk menjalankan perintah tersebut.`
    )

    .setFooter({
        text: '⚔️ Pahlawan Roleplay • Security System',
        iconURL: interaction.guild.iconURL()
    })

    .setTimestamp();

      return interaction.reply({
        embeds: [errorEmbed],
        flags: 64
      });
    }

    // ============================================
    // MAIN EMBED
    // ============================================
    const embed = new EmbedBuilder()

    .setColor(0xFFD700)

    .setAuthor({
        name: '⚔️ Pahlawan Roleplay',
        iconURL: interaction.guild.iconURL()
    })

    .setTitle('💳 PAHLAWAN ROLEPLAY • PAYMENT CENTER')

    .setDescription(
        `━━━━━━━━━━━━━━━━━━

        💳 **SELAMAT DATANG DI PAYMENT CENTER**
        Pahlawan Roleplay

        Silakan pilih metode pembayaran
        yang tersedia pada menu di bawah.

        ━━━━━━━━━━━━━━━━━━

        📌 **INSTRUKSI PEMBAYARAN**
        > 1️⃣ Pilih metode pembayaran
        > 2️⃣ Transfer sesuai nominal yang diberikan
        > 3️⃣ Simpan dan screenshot bukti transfer
        > 4️⃣ Kirim bukti pembayaran kepada Admin

        ━━━━━━━━━━━━━━━━━━

        ⚠️ **PERATURAN PEMBAYARAN**
        > • Transfer wajib sesuai tujuan
        > • Bukti transfer palsu = Blacklist Permanent
        > • Simpan bukti pembayaran hingga transaksi selesai
        > • Konfirmasi hanya kepada Staff/Admin resmi

        ━━━━━━━━━━━━━━━━━━

        💛 Terima kasih telah mendukung
        perkembangan Pahlawan Roleplay.

        ⚔️ Dukungan kalian membantu server
        tetap berkembang dan memberikan
        pengalaman roleplay yang lebih baik.

        ━━━━━━━━━━━━━━━━━━`
    )

    .setFooter({
        text: '⚔️ Pahlawan Roleplay • Official Payment Center',
        iconURL: interaction.guild.iconURL()
    })

    .setTimestamp();

    // ============================================
    // BUTTONS
    // ============================================
    const row = new ActionRowBuilder()
      .addComponents(

        new ButtonBuilder()
          .setCustomId('payment_dana')
          .setLabel('DANA')
          .setEmoji('💙')
          .setStyle(ButtonStyle.Success),

        new ButtonBuilder()
          .setCustomId('payment_gopay')
          .setLabel('GOPAY')
          .setEmoji('🟢')
          .setStyle(ButtonStyle.Success),

        new ButtonBuilder()
          .setCustomId('payment_ovo')
          .setLabel('OVO')
          .setEmoji('🟣')
          .setStyle(ButtonStyle.Primary),

        new ButtonBuilder()
          .setCustomId('payment_qris')
          .setLabel('QRIS')
          .setEmoji('📷')
          .setStyle(ButtonStyle.Secondary)
      );

    // ============================================
    // SEND
    // ============================================
    await interaction.reply({
      embeds: [embed],
      components: [row]
    });
  }
};