const config = require('../../config.json');

const {
  Client,
  GatewayIntentBits,
  SlashCommandBuilder,
  EmbedBuilder,
  ActionRowBuilder,
  ButtonBuilder,
  ButtonStyle,
  ModalBuilder,
  TextInputBuilder,
  TextInputStyle,
  Events,
  Collection,
  MessageFlags
} = require('discord.js');

// ========================================
// CLIENT
// ========================================
const client = new Client({
  intents: [
    GatewayIntentBits.Guilds,
    GatewayIntentBits.GuildMessages
  ]
});

// ========================================
// DATA LELANG
// ========================================
const auctions = new Collection();

// ========================================
// READY
// ========================================
client.once(Events.ClientReady, async () => {

  console.log(`👑 ${client.user.tag} berhasil online sebagai Pahlawan Roleplay!`);

  const command = new SlashCommandBuilder()
    .setName('lelang')
    .setDescription('🏆 Membuka Sistem Lelang Pahlawan Roleplay');

  await client.application.commands.create(command);

console.log('✅ Slash Command /lelang Pahlawan Roleplay berhasil dibuat!');
});

// ========================================
// INTERACTION CREATE
// ========================================
client.on(Events.InteractionCreate, async (interaction) => {

  // ========================================
  // SLASH COMMAND
  // ========================================
  if (interaction.isChatInputCommand()) {

    if (interaction.commandName === 'lelang') {

      const embed = new EmbedBuilder()
      .setColor(0xFFD700)
      .setTitle('🦸 PAHLAWAN ROLEPLAY • SYSTEM LELANG')
      .setDescription(
        `🏆 **LELANG RESMI TELAH DIMULAI!**

        📢 Warga Pahlawan Roleplay dipersilakan
        mengikuti lelang dan memberikan penawaran terbaik.

        💸 Tekan tombol **BID SEKARANG**
        untuk memasukkan harga tawaran kamu.

        ━━━━━━━━━━━━━━━━━━

        🥇 **PENAWAR TERTINGGI**
        > Belum ada penawar.

        💰 **HARGA TERTINGGI**
        > Rp 0

        ━━━━━━━━━━━━━━━━━━

        📊 **LEADERBOARD BID**
        > Belum ada data penawaran.

        ━━━━━━━━━━━━━━━━━━

        ⚡ Jadilah penawar tertinggi
        dan menangkan lelang Pahlawan RP!`
    )

    .setFooter({
        text: '🦸 Pahlawan Roleplay • Auction System',
        iconURL: client.user.displayAvatarURL()
    })

    .setTimestamp();

      const buttons = new ActionRowBuilder()
      .addComponents(

        new ButtonBuilder()
            .setCustomId('bid_harga')
            .setLabel('⚡ BID SEKARANG')
            .setStyle(ButtonStyle.Success),

        new ButtonBuilder()
            .setCustomId('lihat_bid')
            .setLabel('📈 LEADERBOARD')
            .setStyle(ButtonStyle.Primary),

        new ButtonBuilder()
            .setCustomId('info_lelang')
            .setLabel('ℹ️ DETAIL')
            .setStyle(ButtonStyle.Secondary)
    );
      // ========================================
      // SEND MESSAGE
      // ========================================
      await interaction.reply({
        embeds: [embed],
        components: [buttons]
      });

      // ========================================
      // FETCH MESSAGE
      // ========================================
      const msg = await interaction.fetchReply();

      // ========================================
      // SAVE AUCTION
      // ========================================
      auctions.set(msg.id, {
        highestBid: 0,
        highestUser: null,
        bids: []
      });

      console.log(`✅ Auction Created: ${msg.id}`);
    }
  }

  // ========================================
  // BUTTON INTERACTION
  // ========================================
  if (interaction.isButton()) {

    // ========================================
    // BUTTON BID
    // ========================================
    if (interaction.customId === 'bid_harga') {

    const data = auctions.get(interaction.message.id);

    if (!data) {
        return interaction.reply({
            content: '❌ Data lelang tidak ditemukan.',
            flags: MessageFlags.Ephemeral
        });
    }

    const modal = new ModalBuilder()
        .setCustomId(`modal_bid_${interaction.message.id}`)
        .setTitle('⚔️ Pahlawan Roleplay • Pasang Tawaran');

    const input = new TextInputBuilder()
        .setCustomId('harga_input')
        .setLabel('Masukkan Nominal Tawaran')
        .setPlaceholder('Contoh: 500000')
        .setStyle(TextInputStyle.Short)
        .setRequired(true);

    const row = new ActionRowBuilder()
        .addComponents(input);

    modal.addComponents(row);

    await interaction.showModal(modal);
}

    // ========================================
    // BUTTON LEADERBOARD
    // ========================================
    if (interaction.customId === 'lihat_bid') {

      const data = auctions.get(interaction.message.id);

      if (!data) {
        return interaction.reply({
          content: '❌ Data lelang tidak ditemukan.',
          flags: MessageFlags.Ephemeral
        });
      }

      const leaderboard = data.bids.length
        ? data.bids
            .sort((a, b) => b.amount - a.amount)
            .slice(0, 10)
            .map((x, i) =>
              `#${i + 1} 👤 <@${x.userId}> • 💰 Rp ${x.amount.toLocaleString('id-ID')}`
            )
            .join('\n')
        : '> Belum ada penawar.';

      const embed = new EmbedBuilder()
      .setColor(0x5865F2)
      .setTitle('🏆 PAHLAWAN ROLEPLAY • TOP PENAWAR')
      .setDescription(leaderboard)

      .setFooter({
        text: '🏛️ Pahlawan Roleplay • Official Auction System',
        iconURL: client.user.displayAvatarURL()
    })

    .setTimestamp();

      await interaction.reply({
        embeds: [embed],
        flags: MessageFlags.Ephemeral
      });
    }

    // ========================================
    // BUTTON INFO
    // ========================================
    if (interaction.customId === 'info_lelang') {

      const embed = new EmbedBuilder()
    .setColor(0xF1C40F)
    .setTitle('📜 INFORMASI LELANG')
    .setDescription(
        `⚔️ **PERATURAN LELANG PAHLAWAN ROLEPLAY**

        • Bid harus lebih tinggi dari harga tertinggi saat ini.
        • Dilarang melakukan troll bid atau penawaran palsu.
        • Penawar tertinggi saat lelang berakhir akan menjadi pemenang.
        • Hormati seluruh peserta selama proses lelang berlangsung.
        • Keputusan panitia lelang bersifat final.

        ━━━━━━━━━━━━━━━━━━

        💡 Gunakan tombol **💰 PASANG TAWARAN**
        untuk memasukkan harga bid kamu.`
    )

    .setFooter({
        text: '⚔️ Pahlawan Roleplay • Auction Rules',
        iconURL: client.user.displayAvatarURL()
    })

    .setTimestamp();

      await interaction.reply({
        embeds: [embed],
        flags: MessageFlags.Ephemeral
      });
    }
  }

  // ========================================
  // MODAL SUBMIT
  // ========================================
  if (interaction.isModalSubmit()) {

    if (interaction.customId.startsWith('modal_bid_')) {

      const messageId = interaction.customId.replace('modal_bid_', '');

      const data = auctions.get(messageId);

      if (!data) {
        return interaction.reply({
          content: '❌ Lelang tidak ditemukan.',
          flags: MessageFlags.Ephemeral
        });
      }

      const harga = parseInt(
        interaction.fields.getTextInputValue('harga_input')
      );

      // ========================================
      // VALIDASI ANGKA
      // ========================================
      if (isNaN(harga)) {
        return interaction.reply({
          content: '❌ Harga harus berupa angka.',
          flags: MessageFlags.Ephemeral
        });
      }

      // ========================================
      // VALIDASI HARGA
      // ========================================
      if (harga <= data.highestBid) {
        return interaction.reply({
          content: `❌ Harga harus lebih tinggi dari Rp ${data.highestBid.toLocaleString('id-ID')}`,
          flags: MessageFlags.Ephemeral
        });
      }

      // ========================================
      // SAVE BID
      // ========================================
      data.highestBid = harga;
      data.highestUser = interaction.user.id;

      data.bids.push({
        userId: interaction.user.id,
        amount: harga
      });

      // ========================================
      // LEADERBOARD
      // ========================================
      const leaderboard = data.bids
        .sort((a, b) => b.amount - a.amount)
        .slice(0, 5)
        .map((x, i) =>
          `#${i + 1} 👤 <@${x.userId}> • 💰 Rp ${x.amount.toLocaleString('id-ID')}`
        )
        .join('\n');

      // ========================================
      // NEW EMBED
      // ========================================
      const newEmbed = new EmbedBuilder()
    .setColor(0x39FF14)
    .setTitle('⚔️ PAHLAWAN ROLEPLAY • LELANG BERLANGSUNG')
    .setDescription(
        `🏆 **LELANG MASIH BERLANGSUNG!**

        👑 **PENAWAR TERTINGGI**
        > <@${data.highestUser}>

        💰 **HARGA TERTINGGI**
        > Rp ${data.highestBid.toLocaleString('id-ID')}

        ━━━━━━━━━━━━━━━━━━

        📊 **LEADERBOARD BID**
        ${leaderboard}

        ━━━━━━━━━━━━━━━━━━

        ⚡ Siapa yang akan menjadi
        pemenang lelang Pahlawan RP?`
    )

    .setFooter({
        text: '⚔️ Pahlawan Roleplay • Auction System',
        iconURL: client.user.displayAvatarURL()
    })

    .setTimestamp();

      // ========================================
      // FETCH MESSAGE
      // ========================================
      const msg = await interaction.channel.messages.fetch(messageId);

      // ========================================
      // EDIT MESSAGE
      // ========================================
      await msg.edit({
        embeds: [newEmbed]
      });

      // ========================================
      // SUCCESS
      // ========================================
      await interaction.reply({
        content: `✅ Bid berhasil dipasang sebesar Rp ${harga.toLocaleString('id-ID')}`,
        flags: MessageFlags.Ephemeral
      });
    }
  }
});

// ========================================
// LOGIN
// ========================================
client.login(config.token);