const {
SlashCommandBuilder,
EmbedBuilder,
PermissionFlagsBits
} = require('discord.js');

const CHANNEL_MEDIS_ID = '962333526169116742';
const ROLE_WARGA_ID = '1060416860677472266';

module.exports = {

data: new SlashCommandBuilder()
    .setName('infomedis')
    .setDescription('🏥 Mengumumkan informasi resmi rumah sakit')
    .addStringOption(option =>
        option
            .setName('judul')
            .setDescription('Judul pengumuman medis')
            .setRequired(true)
    )
    .addStringOption(option =>
        option
            .setName('isi')
            .setDescription('Isi pengumuman medis')
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
            CHANNEL_MEDIS_ID
        );

    if (!channel) {

        return interaction.reply({
            content:
                '❌ Channel informasi medis tidak ditemukan.',
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

        .setColor('#DC3545')

        .setAuthor({
            name: '🏥 DOMINIK MEDICAL CENTER',
            iconURL:
                interaction.guild.iconURL({
                    forceStatic: false
                }) ||
                interaction.client.user.displayAvatarURL()
        })

        .setTitle(
            `🚑 INFORMASI MEDIS | ${judul.toUpperCase()}`
        )

        .setDescription(
            [
                '━━━━━━━━━━━━━━━━━━━━━━',
                '🏥 **DOMINIK MEDICAL CENTER**',
                '',
                `${isi}`,
                '',
                '━━━━━━━━━━━━━━━━━━━━━━',
                '',
                '❤️ Informasi resmi dari Rumah Sakit Dominik untuk seluruh masyarakat.'
            ].join('\n')
        )

        .addFields(
            {
                name: '👨‍⚕️ PETUGAS MEDIS',
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
                '🏥 Dominik Medical Center • Saving Lives Every Day',
            iconURL:
                interaction.client.user.displayAvatarURL()
        })

        .setTimestamp();

    if (gambar) {

        embed.setImage(gambar.url);

    }

    await channel.send({

        content:
            `🚑 <@&${ROLE_WARGA_ID}>\n\n` +
            `🏥 **PENGUMUMAN RESMI DOMINIK MEDICAL CENTER**`,

        embeds: [embed]

    });

    await interaction.reply({

        content:
            '✅ Informasi medis berhasil dipublikasikan.',

        ephemeral: true

    });

}

};
