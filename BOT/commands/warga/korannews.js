const {
    SlashCommandBuilder,
    EmbedBuilder,
    PermissionFlagsBits
} = require('discord.js');

const CHANNEL_KORAN_ID = '962333588219641916';
const ROLE_WARGA_ID = '1060416860677472266';

module.exports = {

    data: new SlashCommandBuilder()
        .setName('korannews')
        .setDescription('📰 Menerbitkan berita resmi Dominik City')
        .addStringOption(option =>
            option
                .setName('judul')
                .setDescription('Judul berita')
                .setRequired(true)
        )
        .addStringOption(option =>
            option
                .setName('isi')
                .setDescription('Isi berita')
                .setRequired(true)
        )
        .addAttachmentOption(option =>
            option
                .setName('gambar')
                .setDescription('Gambar berita')
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
                CHANNEL_KORAN_ID
            );

        if (!channel) {

            return interaction.reply({
                content:
                    '❌ Channel koran tidak ditemukan.',
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

            .setColor('#FFD700')

            .setAuthor({
                name: '📰 DOMINIK CITY TIMES',
                iconURL:
                    interaction.guild.iconURL({
                        forceStatic: false
                    }) ||
                    interaction.client.user.displayAvatarURL()
            })

            .setTitle(
                `🗞️ BREAKING NEWS | ${judul.toUpperCase()}`
            )

            .setDescription(
                [
                    '━━━━━━━━━━━━━━━━━━━━━━',
                    '🏙️ **KORAN RESMI DOMINIK CITY**',
                    '',
                    `${isi}`,
                    '',
                    '━━━━━━━━━━━━━━━━━━━━━━',
                    '',
                    '📢 Informasi resmi untuk seluruh warga kota.'
                ].join('\n')
            )

            .addFields(
                {
                    name: '👨‍💼 REPORTER',
                    value: `${interaction.user}`,
                    inline: true
                },
                {
                    name: '📅 TANGGAL TERBIT',
                    value: tanggal,
                    inline: true
                },
                {
                    name: '🕒 WAKTU TERBIT',
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
                    '📰 Dominik City Times • Official Newspaper of Dominik Roleplay',
                iconURL:
                    interaction.client.user.displayAvatarURL()
            })

            .setTimestamp();

        if (gambar) {

            embed.setImage(gambar.url);

        }

        await channel.send({

            content:
                `📢 <@&${ROLE_WARGA_ID}>\n\n` +
                `📰 **EDISI BARU DOMINIK CITY TIMES TELAH TERBIT!**`,

            embeds: [embed]

        });

        await interaction.reply({

            content:
                '✅ Berita koran berhasil diterbitkan.',

            ephemeral: true

        });

    }

};