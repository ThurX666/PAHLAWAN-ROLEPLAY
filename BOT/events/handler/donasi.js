const {
    ModalBuilder,
    TextInputBuilder,
    TextInputStyle,
    ActionRowBuilder,
    EmbedBuilder,
    PermissionFlagsBits,
    ButtonBuilder,
    ButtonStyle,
    ChannelType
} = require('discord.js');

const config = require('../../config.json');

const {
    createTicket,
    getTicketByChannel,
    updateTicketStatus,
    deleteTicket,
    formatWaktuIndonesia
} = require('../../utils/ticketStore');


//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//
//  SHOW DONASI MODAL
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//

async function showDonasiModal(interaction) {

    const modal = new ModalBuilder()
        .setCustomId('donasi_ticket_modal')
        .setTitle('☀️ FORM DONASI Pahlawan');

    const jenisDonasiInput = new TextInputBuilder()
        .setCustomId('jenis_donasi')
        .setLabel('🎁 Jenis Donasi')
        .setPlaceholder('VIP / Rumah / Kendaraan / Bisnis')
        .setStyle(TextInputStyle.Short)
        .setRequired(true)
        .setMaxLength(100);

    const jumlahInput = new TextInputBuilder()
        .setCustomId('jumlah')
        .setLabel('📦 Jumlah')
        .setPlaceholder('1 Unit / 2 Item / 5 Paket')
        .setStyle(TextInputStyle.Short)
        .setRequired(true)
        .setMaxLength(50);

    const metodeInput = new TextInputBuilder()
        .setCustomId('metode')
        .setLabel('💳 Metode Pembayaran')
        .setPlaceholder('DANA / OVO / GOPAY / QRIS')
        .setStyle(TextInputStyle.Short)
        .setRequired(true)
        .setMaxLength(50);

    const catatanInput = new TextInputBuilder()
        .setCustomId('catatan')
        .setLabel('📝 Catatan Tambahan')
        .setPlaceholder('Tambahkan catatan jika diperlukan...')
        .setStyle(TextInputStyle.Paragraph)
        .setRequired(false)
        .setMaxLength(500);

    modal.addComponents(
        new ActionRowBuilder().addComponents(jenisDonasiInput),
        new ActionRowBuilder().addComponents(jumlahInput),
        new ActionRowBuilder().addComponents(metodeInput),
        new ActionRowBuilder().addComponents(catatanInput)
    );

    await interaction.showModal(modal);
}


//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//
//  HANDLE DONASI MODAL
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//

async function handleDonasiModal(interaction) {

    await interaction.deferReply({
        ephemeral: true
    });

    try {

        const jenisDonasi =
            interaction.fields.getTextInputValue('jenis_donasi');

        const jumlah =
            interaction.fields.getTextInputValue('jumlah');

        const metode =
            interaction.fields.getTextInputValue('metode');

        const catatan =
            interaction.fields.getTextInputValue('catatan') ||
            'Tidak ada catatan';

        //━━━━━━━━━━━━━━━━━━//
        // CATEGORY CHECK
        //━━━━━━━━━━━━━━━━━━//

        if (!config.category || !config.category.donasi) {

            console.log('❌ Config category donasi belum diisi!');

            return interaction.editReply({
                content:
                    '❌ ID category donasi belum diatur di config.json'
            });
        }

        const ticketCategory =
            await interaction.guild.channels.fetch(
                config.category.donasi
            ).catch(() => null);

        if (!ticketCategory) {

            console.log(
                `❌ Category tidak ditemukan: ${config.category.donasi}`
            );

            return interaction.editReply({
                content:
                    '❌ Category donasi tidak ditemukan!'
            });
        }

        if (ticketCategory.type !== ChannelType.GuildCategory) {

            return interaction.editReply({
                content:
                    '❌ ID yang diberikan bukan category!'
            });
        }

        //━━━━━━━━━━━━━━━━━━//
        // CLEAN CHANNEL NAME
        //━━━━━━━━━━━━━━━━━━//

        const cleanUsername = interaction.user.username
            .toLowerCase()
            .replace(/[^a-z0-9]/g, '');

        const channelName =
            `donasi-${cleanUsername}`.slice(0, 90);

        //━━━━━━━━━━━━━━━━━━//
        // CHECK DUPLICATE
        //━━━━━━━━━━━━━━━━━━//

        const existingChannel =
            interaction.guild.channels.cache.find(
                c =>
                    c.name === channelName &&
                    c.parentId === ticketCategory.id
            );

        if (existingChannel) {

            return interaction.editReply({
                content:
                    `❌ Kamu masih memiliki ticket donasi!\n📂 ${existingChannel}`
            });
        }

        //━━━━━━━━━━━━━━━━━━//
        // CREATE CHANNEL
        //━━━━━━━━━━━━━━━━━━//

        const ticketChannel =
            await interaction.guild.channels.create({

                name: channelName,

                type: ChannelType.GuildText,

                parent: ticketCategory.id,

                topic:
                    `Pahlawan Donasi | ${interaction.user.tag} | ${jenisDonasi}`,

                permissionOverwrites: [

                    {
                        id: interaction.guild.id,
                        deny: [
                            PermissionFlagsBits.ViewChannel
                        ]
                    },

                    {
                        id: interaction.user.id,
                        allow: [
                            PermissionFlagsBits.ViewChannel,
                            PermissionFlagsBits.SendMessages,
                            PermissionFlagsBits.ReadMessageHistory
                        ]
                    },

                    {
                        id: config.role.admin,
                        allow: [
                            PermissionFlagsBits.ViewChannel,
                            PermissionFlagsBits.SendMessages,
                            PermissionFlagsBits.ReadMessageHistory,
                            PermissionFlagsBits.ManageMessages
                        ]
                    }
                ]
            });

        console.log(
            `✅ Ticket donasi dibuat: ${ticketChannel.name}`
        );

        //━━━━━━━━━━━━━━━━━━//
        // SAVE DATA
        //━━━━━━━━━━━━━━━━━━//

        const ticketData = {

            customer_id: interaction.user.id,
            customer_name: interaction.user.tag,

            product: jenisDonasi,
            quantity: jumlah,

            payment_method: metode,
            notes: catatan,

            budget: 0,

            channel_id: ticketChannel.id,
            channel_name: ticketChannel.name
        };

        const newTicket = createTicket(ticketData);

        if (!newTicket) {

            await ticketChannel.delete();

            return interaction.editReply({
                content:
                    '❌ Gagal menyimpan data ticket!'
            });
        }

        //━━━━━━━━━━━━━━━━━━//
        // EMBED
        //━━━━━━━━━━━━━━━━━━//

        const ticketEmbed = new EmbedBuilder()

            .setColor('#FFD700')

            .setAuthor({
                name: 'Pahlawan ROLEPLAY • DONATION SYSTEM'
            })

            .setTitle(
                `🎁 DONASI TICKET • ${newTicket.order_id}`
            )

            .setDescription(
                '💛 Terima kasih telah mendukung Pahlawan Roleplay.\n\nAdmin akan segera memproses ticket donasi Anda.'
            )

            .addFields(

                {
                    name: '👤 Donatur',
                    value: `<@${interaction.user.id}>`,
                    inline: true
                },

                {
                    name: '🎁 Jenis Donasi',
                    value: `\`${jenisDonasi}\``,
                    inline: true
                },

                {
                    name: '📦 Jumlah',
                    value: `\`${jumlah}\``,
                    inline: true
                },

                {
                    name: '💳 Pembayaran',
                    value: `\`${metode}\``,
                    inline: true
                },

                {
                    name: '📝 Catatan',
                    value: catatan,
                    inline: false
                },

                {
                    name: '📌 Status',
                    value: '🟡 Menunggu Konfirmasi',
                    inline: true
                },

                {
                    name: '📅 Dibuat',
                    value: formatWaktuIndonesia(new Date()),
                    inline: true
                }
            )

            .setFooter({
                text:
                    `☀️ Donation ID • ${newTicket.order_id}`
            })

            .setTimestamp();

        //━━━━━━━━━━━━━━━━━━//
        // BUTTONS
        //━━━━━━━━━━━━━━━━━━//

        const buttonRow = new ActionRowBuilder()
            .addComponents(

                new ButtonBuilder()
                    .setCustomId(
                        `complete_ticket_${ticketChannel.id}`
                    )
                    .setLabel('✅ Terima Donasi')
                    .setStyle(ButtonStyle.Success),

                new ButtonBuilder()
                    .setCustomId(
                        `close_ticket_${ticketChannel.id}`
                    )
                    .setLabel('🔒 Tutup Ticket')
                    .setStyle(ButtonStyle.Danger)
            );

        //━━━━━━━━━━━━━━━━━━//
        // SEND MESSAGE
        //━━━━━━━━━━━━━━━━━━//

        await ticketChannel.send({

            content:
                `📢 <@${interaction.user.id}> | <@&${config.role.admin}>`,

            embeds: [ticketEmbed],

            components: [buttonRow]
        });

        //━━━━━━━━━━━━━━━━━━//
        // SUCCESS REPLY
        //━━━━━━━━━━━━━━━━━━//

        await interaction.editReply({

            content:
                `✅ Ticket donasi berhasil dibuat!\n\n📂 Channel: ${ticketChannel}\n🎫 ID Donasi: \`${newTicket.order_id}\``
        });

    } catch (error) {

        console.error(
            '❌ Error create donasi ticket:',
            error
        );

        await interaction.editReply({
            content:
                '❌ Terjadi kesalahan saat membuat ticket donasi!'
        });
    }
}


//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//
// ✅ COMPLETE DONASI
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//

async function handleComplete(interaction) {

    await interaction.deferReply({
        ephemeral: true
    });

    try {

        if (
            !interaction.member.roles.cache.has(
                config.role.admin
            )
        ) {

            return interaction.editReply({
                content:
                    '❌ Hanya admin yang dapat menerima donasi!'
            });
        }

        const channelId =
            interaction.customId.replace(
                'complete_ticket_',
                ''
            );

        const ticket =
            getTicketByChannel(channelId);

        if (!ticket) {

            return interaction.editReply({
                content:
                    '❌ Ticket tidak ditemukan!'
            });
        }

        updateTicketStatus(channelId, 'done');

        const successEmbed = new EmbedBuilder()

            .setColor('#2ECC71')

            .setTitle(
                '✅ DONASI BERHASIL DIKONFIRMASI'
            )

            .setDescription(
                '💛 Terima kasih telah mendukung Pahlawan Roleplay.'
            )

            .addFields(

                {
                    name: '👤 Donatur',
                    value: `<@${ticket.customer_id}>`,
                    inline: true
                },

                {
                    name: '🎁 Jenis',
                    value: ticket.product,
                    inline: true
                },

                {
                    name: '📦 Jumlah',
                    value: ticket.quantity,
                    inline: true
                },

                {
                    name: '👮 Diterima Oleh',
                    value: `<@${interaction.user.id}>`,
                    inline: true
                },

                {
                    name: '📅 Waktu',
                    value:
                        formatWaktuIndonesia(new Date()),
                    inline: true
                }
            )

            .setTimestamp();

        await interaction.message.edit({

            embeds: [successEmbed],

            components: [

                new ActionRowBuilder()
                    .addComponents(

                        new ButtonBuilder()
                            .setCustomId('done')
                            .setLabel('✅ Donasi Diterima')
                            .setStyle(ButtonStyle.Success)
                            .setDisabled(true),

                        new ButtonBuilder()
                            .setCustomId(
                                `close_ticket_${channelId}`
                            )
                            .setLabel('🔒 Tutup Ticket')
                            .setStyle(ButtonStyle.Danger)
                    )
            ]
        });

        await interaction.channel.send({
            content:
                `🎉 Donasi berhasil diterima oleh <@${interaction.user.id}>`
        });

        await interaction.editReply({
            content:
                '✅ Donasi berhasil dikonfirmasi!'
        });

    } catch (error) {

        console.error(error);

        await interaction.editReply({
            content:
                '❌ Terjadi error saat memproses donasi!'
        });
    }
}


//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//
// 🔒 CLOSE TICKET
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//

async function handleClose(interaction) {

    const channelId =
        interaction.customId.replace(
            'close_ticket_',
            ''
        );

    const ticket =
        getTicketByChannel(channelId);

    if (!ticket) {

        return interaction.reply({
            content:
                '❌ Ticket tidak ditemukan!',
            ephemeral: true
        });
    }

    const modal = new ModalBuilder()

        .setCustomId(
            `close_reason_${channelId}`
        )

        .setTitle(
            '🔒 Tutup Ticket Donasi'
        );

    const reasonInput = new TextInputBuilder()

        .setCustomId('close_reason')

        .setLabel('📝 Alasan Penutupan')

        .setPlaceholder(
            'Contoh: Donasi selesai'
        )

        .setStyle(TextInputStyle.Paragraph)

        .setRequired(false);

    modal.addComponents(
        new ActionRowBuilder()
            .addComponents(reasonInput)
    );

    await interaction.showModal(modal);
}


//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//
// 📁 HANDLE CLOSE MODAL
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//

async function handleCloseModal(interaction) {

    await interaction.deferReply({
        ephemeral: true
    });

    try {

        const channelId =
            interaction.customId.replace(
                'close_reason_',
                ''
            );

        const reason =
            interaction.fields.getTextInputValue(
                'close_reason'
            ) || 'Tidak ada alasan';

        const ticket =
            getTicketByChannel(channelId);

        if (!ticket) {

            return interaction.editReply({
                content:
                    '❌ Ticket tidak ditemukan!'
            });
        }

        const channel =
            interaction.guild.channels.cache.get(
                channelId
            );

        if (!channel) {

            return interaction.editReply({
                content:
                    '❌ Channel ticket tidak ditemukan!'
            });
        }

        const closeEmbed = new EmbedBuilder()

            .setColor('#E74C3C')

            .setTitle(
                '🔒 TICKET DONASI DITUTUP'
            )

            .setDescription(
                '⏳ Channel akan dihapus dalam 5 detik.'
            )

            .addFields(

                {
                    name: '🎫 Donation ID',
                    value: ticket.order_id,
                    inline: true
                },

                {
                    name: '👤 Ditutup Oleh',
                    value:
                        `<@${interaction.user.id}>`,
                    inline: true
                },

                {
                    name: '📝 Alasan',
                    value: reason
                }
            )

            .setTimestamp();

        await channel.send({
            embeds: [closeEmbed]
        });

        setTimeout(async () => {

            try {

                await channel.delete();

                deleteTicket(channelId);

            } catch (err) {

                console.error(
                    '❌ Error delete ticket:',
                    err
                );
            }

        }, 5000);

        await interaction.editReply({
            content:
                '✅ Ticket berhasil ditutup!'
        });

    } catch (error) {

        console.error(error);

        await interaction.editReply({
            content:
                '❌ Terjadi error saat menutup ticket!'
        });
    }
}


module.exports = {
    showDonasiModal,
    handleDonasiModal,
    handleComplete,
    handleClose,
    handleCloseModal
};