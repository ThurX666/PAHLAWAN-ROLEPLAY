const {
SlashCommandBuilder,
EmbedBuilder,
PermissionFlagsBits
} = require('discord.js');

const CHANNEL_PEMERINTAH_ID = '962333556770766858';
const ROLE_WARGA_ID = '1060416860677472266';

module.exports = {

data: new SlashCommandBuilder()
    .setName('infopemerintah')
    .setDescription('🏛️ Mengumumkan informasi resmi pemerintah')
    .addStringOption(option =>
        option
            .setName('judul')
            .setDescription('Judul pengumuman')
            .setRequired(true)
    )
    .addStringOption(option =>
        option
            .setName('isi')
            .setDescription('Isi pengumuman')
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

    const judul = interaction.options.getString('judul');
    const isi = interaction.options.getString('isi');
    const gambar = interaction.options.getAttachment('gambar');

    const channel =
        interaction.guild.channels.cache.get(
            CHANNEL_PEMERINTAH_ID
        );

    if (!channel) {

        return interaction.reply({
            content:
                '❌ Channel informasi pemerintah tidak ditemukan.',
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

        .setColor('#1E8449')

        .setAuthor({
            name: '🏛️ PEMERINTAH KOTA DOMINIK',
            iconURL:
                interaction.guild.iconURL({
                    forceStatic: false
                }) ||
                interaction.client.user.displayAvatarURL()
        })

        .setTitle(
            `📜 PENGUMUMAN RESMI | ${judul.toUpperCase()}`
        )

        .setDescription(
            [
                '━━━━━━━━━━━━━━━━━━━━━━',
                '🏛️ **PEMERINTAH KOTA DOMINIK**',
                '',
                `${isi}`,
                '',
                '━━━━━━━━━━━━━━━━━━━━━━',
                '',
                '📢 Informasi resmi dari Pemerintah Kota Dominik untuk seluruh masyarakat.'
            ].join('\n')
        )

        .addFields(
            {
                name: '👔 PEJABAT',
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
                '🏛️ Pemerintah Kota Dominik • Melayani Masyarakat',
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
            `🏛️ **PENGUMUMAN RESMI PEMERINTAH KOTA DOMINIK**`,

        embeds: [embed]

    });

    await interaction.reply({

        content:
            '✅ Informasi pemerintah berhasil dipublikasikan.',

        ephemeral: true

    });

}

};
