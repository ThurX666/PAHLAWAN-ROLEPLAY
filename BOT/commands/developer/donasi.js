const { SlashCommandBuilder, ActionRowBuilder, ButtonBuilder, ButtonStyle, EmbedBuilder } = require('discord.js');
const config = require('../../config.json');

module.exports = {
    data: new SlashCommandBuilder()
        .setName('donasi')
        .setDescription('Panel Tiket Donasi'),

    async execute(interaction) {
        if (!config.developerIds.includes(interaction.user.id)) {
            const errorEmbed = new EmbedBuilder()
                .setColor(0xFF0000)
                .setDescription('GAGAL: Hanya developer yang bisa menggunakan command ini!');
            return interaction.reply({ embeds: [errorEmbed], flags: 64 });
        }

        const embed = new EmbedBuilder()
            .setColor(0xFFD700)
            .setTitle('⚔️ PAHLAWAN ROLEPLAY • TIKET DONASI')

            .setDescription(
                '━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n' +
                '💛 Terima kasih telah mendukung perkembangan\n' +
                '**Pahlawan Roleplay**.\n\n' +

                '💸 Donasi akan digunakan untuk:\n' +
                '› Pengembangan fitur server\n' +
                '› Update dan inovasi terbaru\n' +
                '› Maintenance & kebutuhan operasional\n' +
                '› Event komunitas dan giveaway\n\n' +

                '🎁 Benefit Donatur:\n' +
                '› Role Donatur Eksklusif\n' +
                '› Reward In-Game Khusus\n' +
                '› Akses Benefit Donatur\n' +
                '› Dan berbagai keuntungan lainnya\n\n' +

                '━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n' +

                '📩 Tekan tombol di bawah untuk membuat\n' +
                'tiket donasi dan hubungi staff kami.\n\n' +

                '⚔️ Tim Pahlawan Roleplay akan segera\n' +
                'membantu proses donasi kamu.\n\n' +

                '━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━'
            )

            .setFooter({
                text: '⚔️ Pahlawan Roleplay • Donation Support',
                iconURL: interaction.client.user.displayAvatarURL()
            })

            .setTimestamp();

        const row = new ActionRowBuilder().addComponents(
            new ButtonBuilder()
                .setCustomId('create_donasi_ticket')
                .setLabel('Buat Tiket Donasi')
                .setStyle(ButtonStyle.Success)
        );

        await interaction.reply({
            embeds: [embed],
            components: [row]
        });
    }
};