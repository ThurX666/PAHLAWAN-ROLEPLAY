const {
    SlashCommandBuilder,
    PermissionFlagsBits,
    ActionRowBuilder,
    ButtonBuilder,
    ButtonStyle,
    EmbedBuilder
} = require('discord.js');

module.exports = {

    data: new SlashCommandBuilder()
        .setName('ticketpanel')
        .setDescription('🎫 Membuka panel Ticket Pahlawan Roleplay')
        .setDefaultMemberPermissions(
            PermissionFlagsBits.Administrator
        ),

    async execute(interaction) {

        // ================= EMBED =================
        const embed = new EmbedBuilder()
            .setColor('#f7c65f')

            .setAuthor({
                name: '⚔️ Pahlawan Roleplay • Support Center',
                iconURL: interaction.guild.iconURL()
            })

            .setTitle('🎫 PAHLAWAN ROLEPLAY • SUPPORT CENTER')

            .setDescription(
                `⚔️ Selamat datang di **Support Center Pahlawan Roleplay**\n\n` +

                `Gunakan panel ini untuk menghubungi Staff dan Management\n` +
                `sesuai kebutuhan kamu. Tim kami akan membantu secepat mungkin.\n\n` +

                `━━━━━━━━━━━━━━━━━━\n\n` +

                `📢 **SARAN UPDATE SERVER**\n` +
                `> Kirim ide, fitur baru, atau update menarik\n` +
                `> untuk perkembangan server.\n\n` +

                `💬 **KRITIK & SARAN SERVER**\n` +
                `> Berikan masukan, kritik, atau evaluasi\n` +
                `> demi meningkatkan kualitas server.\n\n` +

                `━━━━━━━━━━━━━━━━━━\n\n` +

                `⚠️ **PERATURAN TICKET**\n` +
                `> • Gunakan ticket sesuai kategori\n` +
                `> • Dilarang spam ticket\n` +
                `> • Hormati Staff saat proses berlangsung\n` +
                `> • Sertakan informasi yang jelas\n\n` +

                `━━━━━━━━━━━━━━━━━━\n\n` +

                `💙 Terima kasih telah menjadi bagian dari\n` +
                `**Pahlawan Roleplay • Indonesia Roleplay Server**`
            )

            .setThumbnail(
                interaction.guild.iconURL({ dynamic: true })
            )

            .setImage(
                'https://media.discordapp.net/attachments/1513604476865609788/1513604622797770933/logo3.png?ex=6a2855a7&is=6a270427&hm=5902561759e780738de44026e4da8955a8ac2f7ebf3281c376fc192a688366e9&=&format=webp&quality=lossless&width=869&height=856'
            )

            .setFooter({
                text: '⚔️ Pahlawan Roleplay • Official Support Center',
                iconURL: interaction.client.user.displayAvatarURL()
            })

            .setTimestamp();

        // ================= BUTTON =================
        const row = new ActionRowBuilder()
            .addComponents(

                new ButtonBuilder()
                    .setCustomId('ticket_update')
                    .setLabel('Update Server')
                    .setEmoji('📢')
                    .setStyle(ButtonStyle.Primary),

                new ButtonBuilder()
                    .setCustomId('ticket_kritik')
                    .setLabel('Masukan Server')
                    .setEmoji('💬')
                    .setStyle(ButtonStyle.Success),

                new ButtonBuilder()
                    .setCustomId('ticket_info')
                    .setLabel('Peraturan')
                    .setEmoji('⚔️')
                    .setStyle(ButtonStyle.Secondary)
            );

        // ================= REPLY =================
        await interaction.reply({
            embeds: [embed],
            components: [row]
        });
    }
};