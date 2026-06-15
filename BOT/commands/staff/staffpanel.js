const {
SlashCommandBuilder,
EmbedBuilder,
ActionRowBuilder,
ButtonBuilder,
ButtonStyle,
PermissionFlagsBits
} = require('discord.js');

module.exports = {
data: new SlashCommandBuilder()
.setName('staffpanel')
.setDescription('Membuat panel jam operasional staff')
.setDefaultMemberPermissions(
PermissionFlagsBits.Administrator
),

async execute(interaction) {

    const embed = new EmbedBuilder()
        .setColor('#c90f37')
        .setTitle('🕒 JAM OPERASIONAL STAFF')
        .setDescription(
            [
                'Silahkan gunakan tombol di bawah ini untuk mencatat jam operasional staff.',
                '',
                '🟢 **ON STAFF** → Mulai bertugas',
                '🔴 **OFF STAFF** → Selesai bertugas',
                '',
                '> Semua aktivitas akan tercatat pada channel logs staff.'
            ].join('\n')
        )
        .setFooter({
            text: `${interaction.guild.name} • Sistem Staff`
        })
        .setTimestamp();

    const row = new ActionRowBuilder()
        .addComponents(
            new ButtonBuilder()
                .setCustomId('on_staff')
                .setLabel('ON STAFF')
                .setEmoji('🟢')
                .setStyle(ButtonStyle.Success),

            new ButtonBuilder()
                .setCustomId('off_staff')
                .setLabel('OFF STAFF')
                .setEmoji('🔴')
                .setStyle(ButtonStyle.Danger)
        );

    await interaction.reply({
        embeds: [embed],
        components: [row]
    });
}

};
