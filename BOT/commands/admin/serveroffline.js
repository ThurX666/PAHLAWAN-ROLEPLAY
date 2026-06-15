const {
    SlashCommandBuilder,
    EmbedBuilder,
    PermissionFlagsBits
} = require('discord.js');

const config = require('../../config.json');

module.exports = {

    data: new SlashCommandBuilder()

        .setName('serveroffline')

        .setDescription(
            '🔴 Mengirim status server offline'
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
            'COMING SOON';

        const version =
            config.serverVersion ||
            '0.120n/0.3DL';

        // =========================
        // ✨ EMBED
        // =========================

        const embed = new EmbedBuilder()

        .setColor('#ff2b2b')

        .setAuthor({

            name: '⚔️ Pahlawan Roleplay',

            iconURL:
                interaction.guild.iconURL({
                    forceStatic: false
                }) ||
                interaction.client.user.displayAvatarURL()

        })

        .setTitle('🔴 SERVER OFFLINE')

        .setDescription(
            [
                '╔════════════════════╗',
                '⚠️ **SERVER SEDANG OFFLINE** ⚠️',
                '╚════════════════════╝',
                '',
                '🚧 Server sedang maintenance',
                'atau mengalami gangguan teknis.',
                '',
                '🙏 Mohon tunggu informasi resmi',
                'dari tim Pahlawan Roleplay.'
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
                value: '>>> 🔴 Offline',
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
                '🔴 Server Pahlawan Roleplay sedang Offline.',

            embeds: [embed]

        });

    }

};