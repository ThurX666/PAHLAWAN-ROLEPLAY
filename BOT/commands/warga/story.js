const {
    SlashCommandBuilder,
    EmbedBuilder,
    ActionRowBuilder,
    ButtonBuilder,
    ButtonStyle,
    ModalBuilder,
    TextInputBuilder,
    TextInputStyle
} = require('discord.js');

// ======================
// SETTING MANUAL (NO CONFIG)
// ======================
const ADMIN_ROLE_ID = '936871651612688424';
const STORY_CHANNEL_ID = '897080180076597309'; // ganti ini

module.exports = {
    data: new SlashCommandBuilder()
        .setName('story')
        .setDescription('Submit Character Story')

        .addStringOption(o =>
            o.setName('nama').setDescription('Nama Character').setRequired(true))

        .addIntegerOption(o =>
            o.setName('level').setDescription('Level Character').setRequired(true))

        .addStringOption(o =>
            o.setName('gender')
                .setDescription('Jenis Kelamin')
                .addChoices(
                    { name: 'Laki-Laki', value: 'Laki-Laki' },
                    { name: 'Perempuan', value: 'Perempuan' }
                )
                .setRequired(true))

        .addStringOption(o =>
            o.setName('kota').setDescription('Kota Kelahiran').setRequired(true))

        .addStringOption(o =>
            o.setName('tanggal_lahir').setDescription('Tanggal Lahir').setRequired(true))

        .addAttachmentOption(o =>
            o.setName('ss_stats').setDescription('Screenshot Stats').setRequired(true))

        .addAttachmentOption(o =>
            o.setName('ss_tab').setDescription('Screenshot TAB').setRequired(true))

        .addStringOption(o =>
            o.setName('story').setDescription('Link Story').setRequired(true)),

    async execute(interaction) {

        const nama = interaction.options.getString('nama');
        const level = interaction.options.getInteger('level');
        const gender = interaction.options.getString('gender');
        const kota = interaction.options.getString('kota');
        const tanggal = interaction.options.getString('tanggal_lahir');
        const story = interaction.options.getString('story');

        const stats = interaction.options.getAttachment('ss_stats');
        const tab = interaction.options.getAttachment('ss_tab');

        const embed = new EmbedBuilder()
            .setColor('#f1c40f')
            .setAuthor({
                name: 'Character Story Registration'
            })
            .setTitle('📁 Character Story Registration')
            .setDescription(
                `🔵 **Informasi Karakter**\n` +
                `**Nama:** ${nama}\n` +
                `**Level:** ${level}\n` +
                `**Gender:** ${gender}\n` +
                `**Kota Lahir:** ${kota}\n` +
                `**Tanggal Lahir:** ${tanggal}\n\n` +

                `📂 **Dokumen Pendukung**\n` +
                `📊 [Screenshot Stats](${stats.url})\n` +
                `📋 [Screenshot TAB](${tab.url})\n\n` +

                `📝 **Character Story**\n` +
                `(${story})`
            )
            .setThumbnail(stats.url)
            .setImage(tab.url)
            .setFooter({
                text: `Diajukan oleh ${interaction.user.username}`
            })
            .setTimestamp();

        const buttons = new ActionRowBuilder().addComponents(
            new ButtonBuilder()
                .setCustomId(`approve_${interaction.user.id}`)
                .setLabel('Approve')
                .setStyle(ButtonStyle.Success)
                .setEmoji('🟢'),

            new ButtonBuilder()
                .setCustomId(`reject_${interaction.user.id}`)
                .setLabel('Reject')
                .setStyle(ButtonStyle.Danger)
                .setEmoji('🔴')
        );

        const channel = interaction.guild.channels.cache.get(STORY_CHANNEL_ID);

        if (!channel) {
            return interaction.reply({
                content: '❌ Channel story tidak ditemukan.',
                ephemeral: true
            });
        }

        const msg = await channel.send({
            content: `${interaction.user} - Story baru telah diajukan!`,
            embeds: [embed],
            components: [buttons]
        });

        await interaction.reply({
            content: `✅ Story **${nama}** berhasil dikirim ke staff.`,
            ephemeral: true
        });

        // ======================
        // BUTTON HANDLER
        // ======================
        const collector = msg.createMessageComponentCollector();

        collector.on('collect', async i => {

            const isAdmin = i.member.roles.cache.has(ADMIN_ROLE_ID);
            if (!isAdmin) {
                return i.reply({
                    content: '❌ Kamu tidak punya izin.',
                    ephemeral: true
                });
            }

            // ======================
            // APPROVE
            // ======================
            if (i.customId.startsWith('approve_')) {

                embed.setColor('Green')
                    .setDescription(`🟢 **STATUS: APPROVED** oleh ${i.user.tag}`);

                await msg.edit({ embeds: [embed], components: [] });

                const userId = i.customId.split('_')[1];
                const user = await interaction.client.users.fetch(userId);

                await user.send({
                    content: `🟢 Story kamu telah **DISETUJUI** oleh staff!`
                }).catch(() => null);

                return i.reply({
                    content: '✅ Approved!',
                    ephemeral: true
                });
            }

            // ======================
            // REJECT (OPEN MODAL)
            // ======================
            if (i.customId.startsWith('reject_')) {

                const modal = new ModalBuilder()
                    .setCustomId(`reject_modal_${i.customId.split('_')[1]}`)
                    .setTitle('Reject Reason');

                const reasonInput = new TextInputBuilder()
                    .setCustomId('reason')
                    .setLabel('Alasan Reject')
                    .setStyle(TextInputStyle.Paragraph)
                    .setRequired(true);

                modal.addComponents(
                    new ActionRowBuilder().addComponents(reasonInput)
                );

                return i.showModal(modal);
            }
        });

        // ======================
        // MODAL HANDLER (REJECT)
        // ======================
        interaction.client.on('interactionCreate', async modalInt => {

            if (!modalInt.isModalSubmit()) return;
            if (!modalInt.customId.startsWith('reject_modal_')) return;

            const userId = modalInt.customId.split('_')[2];
            const reason = modalInt.fields.getTextInputValue('reason');

            const user = await interaction.client.users.fetch(userId);

            embed.setColor('Red')
                .setDescription('🔴 **STATUS: REJECTED**')
                .addFields({
                    name: '❌ Reason',
                    value: reason
                });

            await msg.edit({ embeds: [embed], components: [] });

            await user.send({
                content: `🔴 Story kamu DITOLAK.\nAlasan: **${reason}**`
            }).catch(() => null);

            return modalInt.reply({
                content: '❌ Rejected + alasan terkirim.',
                ephemeral: true
            });
        });
    }
};