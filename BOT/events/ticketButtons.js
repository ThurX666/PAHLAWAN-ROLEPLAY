const {
    Events,
    PermissionsBitField,
    ChannelType,
    ActionRowBuilder,
    ButtonBuilder,
    ButtonStyle,
    EmbedBuilder
} = require('discord.js');

const config = require('../config.json');

// ================= CONFIG =================
const ADMIN_ROLE_ID = config.ticketpanel.ROLE_ADMIN_ID;
const CATEGORY_ID = config.ticketpanel.CATEGORY_ID;
// ==========================================

module.exports = {
    name: Events.InteractionCreate,

    async execute(interaction) {

        if (!interaction.isButton()) return;

        // ================= INFO BUTTON =================
        if (interaction.customId === 'ticket_info') {

            const infoEmbed = new EmbedBuilder()
                .setColor('#f7c65f')
                .setTitle('📌 INFORMASI TICKET')
                .setDescription(
                    `**Pahlawan Roleplay Ticket System**\n\n` +

                    `📢 **Saran Update**\n` +
                    `> Gunakan untuk memberikan ide, fitur baru, atau update server.\n\n` +

                    `💬 **Kritik & Saran**\n` +
                    `> Gunakan untuk memberikan masukan atau kritik terhadap server.\n\n` +

                    `⚠️ **Peraturan Ticket**\n` +
                    `• Jangan spam ticket\n` +
                    `• Gunakan bahasa yang sopan\n` +
                    `• Jelaskan dengan detail\n` +
                    `• Hormati staff yang membantu\n\n` +

                    `Terima kasih telah membantu perkembangan Pahlawan Roleplay ❤️`
                )
                .setFooter({
                    text: 'Pahlawan Roleplay System'
                })
                .setTimestamp();

            return interaction.reply({
                embeds: [infoEmbed],
                ephemeral: true
            });
        }

        // ================= CREATE TICKET =================
        if (
            interaction.customId === 'ticket_update' ||
            interaction.customId === 'ticket_kritik'
        ) {

            // VALIDASI ROLE
            const adminRole = interaction.guild.roles.cache.get(ADMIN_ROLE_ID);

            if (!adminRole) {
                return interaction.reply({
                    content: '❌ Role admin tidak ditemukan.',
                    ephemeral: true
                });
            }

            // VALIDASI CATEGORY
            const category = interaction.guild.channels.cache.get(CATEGORY_ID);

            if (!category) {
                return interaction.reply({
                    content: '❌ Category ticket tidak ditemukan.',
                    ephemeral: true
                });
            }

            // ================= CEK TICKET =================
            const existing = interaction.guild.channels.cache.find(
                c =>
                    c.topic === interaction.user.id &&
                    c.parentId === CATEGORY_ID
            );

            if (existing) {
                return interaction.reply({
                    content:
                        `❌ Kamu masih memiliki ticket terbuka:\n${existing}`,
                    ephemeral: true
                });
            }

            // ================= TYPE =================
            const type =
                interaction.customId === 'ticket_update'
                    ? 'update'
                    : 'kritik';

            const typeName =
                interaction.customId === 'ticket_update'
                    ? '📢 Saran Update'
                    : '💬 Kritik & Saran';

            // ================= CREATE CHANNEL =================
            const channel = await interaction.guild.channels.create({
                name: `${type}-${interaction.user.username}`
                    .toLowerCase()
                    .replace(/[^a-z0-9-]/g, ''),

                type: ChannelType.GuildText,
                parent: CATEGORY_ID,
                topic: interaction.user.id,

                permissionOverwrites: [
                    {
                        id: interaction.guild.id,
                        deny: [
                            PermissionsBitField.Flags.ViewChannel
                        ]
                    },
                    {
                        id: interaction.user.id,
                        allow: [
                            PermissionsBitField.Flags.ViewChannel,
                            PermissionsBitField.Flags.SendMessages,
                            PermissionsBitField.Flags.ReadMessageHistory,
                            PermissionsBitField.Flags.AttachFiles
                        ]
                    },
                    {
                        id: adminRole.id,
                        allow: [
                            PermissionsBitField.Flags.ViewChannel,
                            PermissionsBitField.Flags.SendMessages,
                            PermissionsBitField.Flags.ReadMessageHistory,
                            PermissionsBitField.Flags.ManageChannels,
                            PermissionsBitField.Flags.AttachFiles
                        ]
                    }
                ]
            });

            // ================= BUTTON CLOSE =================
            const row = new ActionRowBuilder()
                .addComponents(
                    new ButtonBuilder()
                        .setCustomId('close_ticket')
                        .setLabel('Close Ticket')
                        .setEmoji('🔒')
                        .setStyle(ButtonStyle.Danger)
                );

            // ================= EMBED =================
            const embed = new EmbedBuilder()
                .setColor('#00ff99')
                .setAuthor({
                    name: `${interaction.user.username}`,
                    iconURL: interaction.user.displayAvatarURL({
                        dynamic: true
                    })
                })
                .setTitle('🎫 TICKET BERHASIL DIBUAT')
                .setDescription(
                    `Halo ${interaction.user} 👋\n\n` +

                    `Terima kasih telah membuat ticket **${typeName}**.\n\n` +

                    `📝 Silahkan kirim detail request, kritik, atau saran kamu dengan jelas.\n` +
                    `📌 Team staff Pahlawan Roleplay akan membantu secepat mungkin.\n\n` +

                    `⚠️ Mohon jangan spam ticket.`
                )
                .setThumbnail(interaction.guild.iconURL({ dynamic: true }))
                .setFooter({
                    text: 'Pahlawan Roleplay Ticket System',
                    iconURL: interaction.client.user.displayAvatarURL()
                })
                .setTimestamp();

            // ================= SEND =================
            await channel.send({
                content:
                    `||<@&${adminRole.id}>|| • ${interaction.user}`,
                embeds: [embed],
                components: [row]
            });

            // ================= REPLY =================
            return interaction.reply({
                embeds: [
                    new EmbedBuilder()
                        .setColor('#00ff99')
                        .setDescription(
                            `✅ Ticket berhasil dibuat:\n${channel}`
                        )
                ],
                ephemeral: true
            });
        }

        // ================= CLOSE TICKET =================
        if (interaction.customId === 'close_ticket') {

            const closeEmbed = new EmbedBuilder()
                .setColor('#ff0000')
                .setTitle('🔒 Ticket Ditutup')
                .setDescription(
                    `Ticket akan ditutup dalam **5 detik**.\n\n` +
                    `Terima kasih telah menggunakan Pahlawan Roleplay Ticket ❤️`
                )
                .setFooter({
                    text: 'Pahlawan Roleplay System'
                })
                .setTimestamp();

            await interaction.reply({
                embeds: [closeEmbed]
            });

            setTimeout(async () => {

                try {
                    await interaction.channel.delete();
                } catch (err) {
                    console.log(err);
                }

            }, 5000);
        }
    }
};