const {
    SlashCommandBuilder,
    ActionRowBuilder,
    StringSelectMenuBuilder,
    EmbedBuilder,
    PermissionFlagsBits
} = require('discord.js');

module.exports = {
    data: new SlashCommandBuilder()
        .setName('request')
        .setDescription('📩 Membuka panel Request System Pahlawan Roleplay')
        .setDefaultMemberPermissions(PermissionFlagsBits.Administrator),

    async execute(interaction) {
        const config = require('../../config.json');

        // =========================
        // CHECK DEVELOPER
        // =========================
        if (
            !config.developerIds ||
            !config.developerIds.includes(interaction.user.id)
        ) {
            const noPermEmbed = new EmbedBuilder()
            .setColor('#ff3b30')

            .setAuthor({
                name: '🛡️ PAHLAWAN ROLEPLAY • SECURITY SYSTEM',
                iconURL: interaction.guild.iconURL({ dynamic: true })
            })

            .setTitle('🚫 ACCESS DENIED')

            .setDescription(
                [
                    '⚠️ **AKSES DITOLAK**',
                    '',
                    'Kamu tidak memiliki izin untuk',
                    'menggunakan command ini.',
                    '',
                    '━━━━━━━━━━━━━━━━━━━━━━',
                    '',
                    '🔒 Command ini hanya dapat digunakan',
                    'oleh **Owner & Developer**',
                    '**Pahlawan Roleplay**.',
                    '',
                    '🛡️ Sistem keamanan aktif untuk',
                    'melindungi server dan seluruh',
                    'fitur internal Pahlawan RP.',
                    '',
                    '━━━━━━━━━━━━━━━━━━━━━━'
                ].join('\n')
            )

            .setFooter({
                text: `⚔️ Requested by ${interaction.user.username} • Pahlawan Roleplay`,
                iconURL: interaction.user.displayAvatarURL()
            })

            .setTimestamp();

            return interaction.reply({
                embeds: [noPermEmbed],
                ephemeral: true
            });
        }

        // =========================
        // MAIN EMBED
        // =========================
        const requestEmbed = new EmbedBuilder()
            .setColor('#FFD700')

            .setAuthor({
                name: '⚔️ PAHLAWAN ROLEPLAY • REQUEST CENTER',
                iconURL: interaction.guild.iconURL({ dynamic: true })
            })

            .setTitle('📩 PANEL REQUEST RESMI')

            .setDescription(
                [
                    '⚔️ Selamat datang di **Request Center Pahlawan Roleplay**',
                    '',
                    '> Gunakan panel ini untuk mengajukan berbagai',
                    '> layanan dan kebutuhan resmi server.',
                    '',
                    '━━━━━━━━━━━━━━━━━━',
                    '',
                    '📋 **KATEGORI REQUEST**',
                    '',
                    '🎨 • Request Creator',
                    '💼 • Request Bisnis',
                    '🖥️ • Request Player PC',
                    '📦 • Request Import',
                    '🏢 • Request Faction',
                    '🔧 • Request Workshop',
                    '💸 • Request Refund',
                    '🛡️ • Request Unban / Banding',
                    '',
                    '━━━━━━━━━━━━━━━━━━',
                    '',
                    '⚠️ **PERATURAN REQUEST**',
                    '> • Gunakan fitur request dengan bijak',
                    '> • Dilarang spam ticket atau request',
                    '> • Dilarang membuat request palsu',
                    '> • Hormati Staff selama proses berlangsung',
                    '> • Sertakan informasi yang lengkap dan jelas',
                    '',
                    '━━━━━━━━━━━━━━━━━━',
                    '',
                    '💙 Terima kasih telah menjadi bagian dari',
                    '**Pahlawan Roleplay • Indonesia Roleplay Server**',
                    '',
                    '🏛️ Bersama kita membangun pengalaman',
                    'roleplay yang lebih baik untuk semua.'
                ].join('\n')
            )

            .setThumbnail(
                interaction.guild.iconURL({ dynamic: true })
            )

            .setImage(
                'https://media.discordapp.net/attachments/1513604476865609788/1513604622797770933/logo3.png?ex=6a2855a7&is=6a270427&hm=5902561759e780738de44026e4da8955a8ac2f7ebf3281c376fc192a688366e9&=&format=webp&quality=lossless&width=869&height=856'
            )

            .setFooter({
                text: '⚔️ Pahlawan Roleplay • Official Request Center',
                iconURL: interaction.guild.iconURL({ dynamic: true })
            })

            .setTimestamp();

        // =========================
        // SELECT MENU
        // =========================
        const requestMenu = new StringSelectMenuBuilder()

            .setCustomId('request_category_select')

            .setPlaceholder('⚔️ Pilih kategori request')

            .addOptions([

                {
                    label: 'Creator Request',
                    description: 'Pengajuan Creator resmi server',
                    value: 'request_creator',
                    emoji: '🎨'
                },

                {
                    label: 'Business Request',
                    description: 'Pengajuan bisnis atau usaha roleplay',
                    value: 'request_bisnis',
                    emoji: '💼'
                },

                {
                    label: 'Player PC Request',
                    description: 'Pengajuan whitelist pemain PC',
                    value: 'request_pc',
                    emoji: '🖥️'
                },

                {
                    label: 'Import Request',
                    description: 'Import kendaraan atau item',
                    value: 'request_import',
                    emoji: '📦'
                },

                {
                    label: 'Faction Request',
                    description: 'Pengajuan faction resmi',
                    value: 'request_faction',
                    emoji: '🏢'
                },

                {
                    label: 'Workshop Request',
                    description: 'Pengajuan workshop atau bengkel',
                    value: 'request_workshop',
                    emoji: '🔧'
                },

                {
                    label: 'Refund Request',
                    description: 'Pengajuan refund transaksi',
                    value: 'request_refund',
                    emoji: '💸'
                },

                {
                    label: 'Unban / Appeal',
                    description: 'Banding atau pengajuan unban',
                    value: 'request_unban',
                    emoji: '🛡️'
                }
            ]);

        const row = new ActionRowBuilder()
            .addComponents(requestMenu);

        // =========================
        // SEND PANEL
        // =========================
        await interaction.reply({
            embeds: [requestEmbed],
            components: [row]
        });

        // =========================
        // SUCCESS MESSAGE
        // =========================
        const successEmbed = new EmbedBuilder()
            .setColor('#57f287')
            .setDescription(
                [
                    '## ✅ Request Panel Berhasil Dibuat',
                    `> Panel request berhasil dikirim di channel ${interaction.channel}`
                ].join('\n')
            )
            .setTimestamp();

        const msg = await interaction.followUp({
            embeds: [successEmbed],
            ephemeral: true
        });

        setTimeout(() => {
            msg.delete().catch(() => {});
        }, 4000);
    }
};