const {
    SlashCommandBuilder,
    EmbedBuilder,
    ActionRowBuilder,
    ButtonBuilder,
    ButtonStyle
} = require('discord.js');

const SERVER_IP = 'Coming Soon';

module.exports = {
    data: new SlashCommandBuilder()
        .setName('serverinfo')
        .setDescription('Menampilkan informasi koneksi server'),

    async execute(interaction) {

        const embed = new EmbedBuilder()
            .setColor('#ff0000')
            .setAuthor({
                name: 'Pahlawan Roleplay Roleplay • Server Connection Info'
            })
            .setDescription(
                `🌐 **Connect to Server**

                🖥️ **IP Address - Alamat Server**
                🇮🇩 Gunakan tombol di bawah untuk mendapatkan IP server kami.
                🇬🇧 Click the button below to reveal our server IP address.

                📌 **Cara Connect - How to Connect**
                🇮🇩 1. Buka game dan pilih menu Multiplayer
                🇮🇩 2. Masukkan IP yang kamu dapatkan pada kolom alamat server
                🇮🇩 3. Klik Connect dan mulai bermain!

                🇬🇧 Open the game → Multiplayer → Enter the IP → Connect & Play

                ⚠️ **Kendala Koneksi?**
                🇮🇩 Jika kamu tidak bisa masuk ke server, hubungi Staff melalui ticket.

                🇬🇧 If you're unable to connect, contact our Staff via the ticket system.`
            )
            .setFooter({
                text: '© Pahlawan Roleplay • Server Info'
            })
            .setTimestamp();

        const row = new ActionRowBuilder()
            .addComponents(
                new ButtonBuilder()
                    .setCustomId('show_server_ip')
                    .setLabel('Show IP (Lihat IP & Port Server)')
                    .setEmoji('📶')
                    .setStyle(ButtonStyle.Primary)
            );

        await interaction.reply({
            embeds: [embed],
            components: [row]
        });
    }
};