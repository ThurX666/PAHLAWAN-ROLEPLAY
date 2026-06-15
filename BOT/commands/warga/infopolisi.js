const {
    SlashCommandBuilder,
    EmbedBuilder,
    PermissionFlagsBits
} = require('discord.js');

const CHANNEL_POLISI_ID = '962333482644815932';
const ROLE_WARGA_ID = '1060416860677472266';

module.exports = {

    data: new SlashCommandBuilder()
        .setName('infopolisi')
        .setDescription('🚔 Mengumumkan informasi resmi kepolisian')
        .addStringOption(option =>
            option
                .setName('judul')
                .setDescription('Judul informasi')
                .setRequired(true)
        )
        .addStringOption(option =>
            option
                .setName('isi')
                .setDescription('Isi informasi')
                .setRequired(true)
        )
        .addAttachmentOption(option =>
            option
                .setName('gambar')
                .setDescription('Lampiran gambar')
                .setRequired(true)
        )
        .setDefaultMemberPermissions(
            PermissionFlagsBits.ManageMessages
        ),

    async execute(interaction) {

        const judul =
            interaction.options.getString('judul');

        const isi =
            interaction.options.getString('isi');

        const gambar =
            interaction.options.getAttachment('gambar');

        const channel =
            interaction.guild.channels.cache.get(
                CHANNEL_POLISI_ID
            );

        if (!channel) {

            return interaction.reply({
                content:
                    '❌ Channel informasi kepolisian tidak ditemukan.',
                ephemeral: true
            });

        }

        const now = new Date();

        const tanggal =
            now.toLocaleDateString(
                'id-ID',
                {
                    weekday: 'long',
                    day: 'numeric',
                    month: 'long',
                    year: 'numeric',
                    timeZone: 'Asia/Jakarta'
                }
            );

        const jam =
            now.toLocaleTimeString(
                'id-ID',
                {
                    hour: '2-digit',
                    minute: '2-digit',
                    timeZone: 'Asia/Jakarta'
                }
            );

        const embed = new EmbedBuilder()

            .setColor('#003366')

            .setAuthor({
                name: '🚔 DOMINIK POLICE DEPARTMENT',
                iconURL:
                    interaction.guild.iconURL({
                        forceStatic: false
                    }) ||
                    interaction.client.user.displayAvatarURL()
            })

            .setTitle(
                `🚨 INFORMASI KEPOLISIAN | ${judul.toUpperCase()}`
            )

            .setDescription(
                [
                    '━━━━━━━━━━━━━━━━━━━━━━',
                    '🚔 **PENGUMUMAN RESMI KEPOLISIAN DOMINIK**',
                    '',
                    `${isi}`,
                    '',
                    '━━━━━━━━━━━━━━━━━━━━━━',
                    '',
                    '📢 Informasi resmi dari Departemen Kepolisian untuk seluruh warga Dominik.'
                ].join('\n')
            )

            .addFields(
                {
                    name: '👮 PETUGAS',
                    value: `${interaction.user}`,
                    inline: true
                },
                {
                    name: '📅 TANGGAL',
                    value: tanggal,
                    inline: true
                },
                {
                    name: '🕒 WAKTU',
                    value: `${jam} WIB`,
                    inline: true
                }
            )

            .setThumbnail(
                interaction.guild.iconURL({
                    forceStatic: true
                })
            )

            .setFooter({
                text:
                    '🚔 Dominik Police Department • Serve & Protect',
                iconURL:
                    interaction.client.user.displayAvatarURL()
            })

            .setTimestamp();

        if (gambar) {

            embed.setImage(gambar.url);

        }

        await channel.send({

            content:
                `🚨 <@&${ROLE_WARGA_ID}>\n\n` +
                `📢 **PENGUMUMAN RESMI DARI DOMINIK POLICE DEPARTMENT**`,

            embeds: [embed]

        });

        await interaction.reply({

            content:
                '✅ Informasi kepolisian berhasil dipublikasikan.',

            ephemeral: true

        });

    }

};