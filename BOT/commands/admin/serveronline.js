const {
    SlashCommandBuilder,
    EmbedBuilder,
    PermissionFlagsBits
} = require('discord.js');

const config = require('../../config.json');

module.exports = {

    data: new SlashCommandBuilder()

        .setName('serveronline')

        .setDescription(
            '🟢 Mengirim status server online'
        )

        .setDefaultMemberPermissions(
            PermissionFlagsBits.Administrator
        ),

    async execute(interaction) {

        // =========================
        // 🌐 CONFIG
        // =========================

        const host =
            config.serverHost ||
            'coming Soon';

        const version =
            config.serverVersion ||
            '0.120n/0.3DL';

        // =========================
        // ✨ EMBED
        // =========================

        const embed = new EmbedBuilder()

        .setColor('#39ff14')

        .setAuthor({

            name: '⚔️ Pahlawan Roleplay',

            iconURL:
                interaction.guild.iconURL({
                    forceStatic: false
                }) ||
                interaction.client.user.displayAvatarURL()

        })

        .setTitle('🟢 SERVER ONLINE')

        .setDescription(
            [
                '╔════════════════════╗',
                '✅ **SERVER TELAH ONLINE** ✅',
                '╚════════════════════╝',
                '',
                '🎮 Server Pahlawan Roleplay',
                'sudah dapat dimainkan kembali.',
                '',
                '🚀 Selamat bermain dan nikmati',
                'pengalaman roleplay terbaik!'
            ].join('\n')
        )

        .addFields(

            {
                name: '🖥 HOST SERVER',
                value: `>>> \`${host}\``,
                inline: true
            },

            {
                name: '📦 VERSION',
                value: `>>> \`${version}\``,
                inline: true
            },

            {
                name: '📡 STATUS',
                value: '>>> 🟢 Online',
                inline: false
            }

        )

        .setImage(
            'https://media.discordapp.net/attachments/1513604476865609788/1513604622797770933/logo3.png?ex=6a2855a7&is=6a270427&hm=5902561759e780738de44026e4da8955a8ac2f7ebf3281c376fc192a688366e9&=&format=webp&quality=lossless&width=869&height=856'
        )

        .setThumbnail(
            interaction.guild.iconURL({
                forceStatic: false
            })
        )

        .setFooter({

            text: '⚔️ Pahlawan Roleplay • Server Status',

            iconURL:
                interaction.client.user.displayAvatarURL()

        })

        .setTimestamp();

        // =========================
        // 🚀 SEND MESSAGE
        // =========================

        await interaction.reply({

            content:
                '📢 @everyone\n' +
                '🟢 Server Pahlawan Roleplay sekarang sudah Online!',

            embeds: [embed]

        });

    }

};