const { EmbedBuilder } = require('discord.js');

const giveawayHandler = require('./handler/giveaway');
const reportHandler = require('./handler/report');
const requestHandler = require('./handler/request');
const verifHandler = require('./handler/verifikasi');
const paymentHandler = require('./handler/payment');
const ticketHandler = require('./handler/donasi');
const staffAttendance = require('./handler/staffAttendance');

async function safeInteractionReply(interaction, payload) {

try {

    if (!interaction.isRepliable())
        return;

    if (
        interaction.deferred ||
        interaction.replied
    ) {
        return interaction.followUp(payload);
    }

    return interaction.reply(payload);

} catch (error) {

    if (
        error?.code === 40060 ||
        error?.code === 10062
    ) {
        return;
    }

    console.error(
        '[INTERACTION REPLY ERROR]',
        error
    );
}

}

async function handleInteractionError(interaction, error) {

    console.error('========== ERROR ==========');
    console.error(error);
    console.error(error?.stack);
    console.error('===========================');

    await safeInteractionReply(interaction, {
        content: '❌ Terjadi kesalahan saat memproses interaksi.',
        flags: 64
    });


console.error(
    '[INTERACTION ERROR]',
    error
);

async function safeInteractionReply(interaction, payload) {
    try {

        if (!interaction.isRepliable()) return;

        if (interaction.replied) {
            return await interaction.followUp(payload);
        }

        if (interaction.deferred) {
            return await interaction.editReply(payload);
        }

        return await interaction.reply(payload);

    } catch (error) {

        if (
            error?.code === 40060 ||
            error?.code === 10062
        ) return;

        console.error(
            '[INTERACTION REPLY ERROR]',
            error
        );
    }
}


}

module.exports = {
name: 'interactionCreate',

async execute(interaction, client) {

    try {

        // ================= SLASH COMMAND =================

        if (interaction.isChatInputCommand()) {

            const command =
                client.commands.get(
                    interaction.commandName
                );

            if (!command) {
                return safeInteractionReply(
                    interaction,
                    {
                        content:
                            '❌ Command tidak ditemukan.',
                        flags: 64
                    }
                );
            }

            try {

                await command.execute(
                    interaction,
                    client
                );

            } catch (error) {

                await handleInteractionError(
                    interaction,
                    error
                );
            }

            return;
        }

        // ================= BUTTON =================

        if (interaction.isButton()) {

            try {
                if (interaction.customId === 'show_server_ip') {

                const embed = new EmbedBuilder()
                    .setColor('#f39c12')
                    .setAuthor({
                        name: 'Pahlawan Roleplay • Server Connection'
                    })
                    .setDescription(
                        `## 📶 Server IP Address

                        🔗 **Gunakan IP berikut untuk terhubung ke server Pahlawan Roleplay**

                        \`\`\`
                        Coming Soon
                        \`\`\`

                        ### 🇮🇩 Cara Bergabung
                        • Buka game dan masuk ke menu **Multiplayer**
                        • Masukkan IP server di atas
                        • Klik **Connect** dan mulai bermain

                        ### 🇬🇧 How to Join
                        • Open the game and go to **Multiplayer**
                        • Enter the server IP above
                        • Click **Connect** and enjoy the server

                        ⚠️ **Mengalami kendala koneksi?**
                        Silakan hubungi Staff melalui sistem ticket Discord.`
                    )
                    .setThumbnail(interaction.guild.iconURL({ dynamic: true }))
                    .setFooter({
                        text: 'Pahlawan Roleplay • Official Server Information'
                    })
                    .setTimestamp();

                return interaction.reply({
                    embeds: [embed],
                    ephemeral: true
                });
            }
                if (
                    interaction.customId ===
                        'on_staff' ||
                    interaction.customId ===
                        'off_staff'
                ) {
                    return staffAttendance.execute(
                        interaction
                    );
                }

                if (
                    interaction.customId ===
                    'giveaway_join'
                ) {
                    return giveawayHandler.handleJoinGiveaway(
                        interaction
                    );
                }

                if (
                    interaction.customId.startsWith(
                        'giveaway_leave_'
                    )
                ) {
                    return giveawayHandler.handleLeaveGiveaway(
                        interaction
                    );
                }

                if (
                    interaction.customId ===
                    'giveaway_create_btn'
                ) {
                    return giveawayHandler.showCreateModal(
                        interaction
                    );
                }

                if (
                    interaction.customId ===
                    'close_report_ticket'
                ) {
                    return reportHandler.handleCloseTicket(
                        interaction
                    );
                }

                if (
                    interaction.customId ===
                    'close_request_ticket'
                ) {
                    return requestHandler.handleCloseTicket(
                        interaction
                    );
                }

                if (
                    interaction.customId ===
                    'verif_ambil_kode'
                ) {
                    return verifHandler.handleAmbilKode(
                        interaction
                    );
                }

                if (
                    interaction.customId ===
                    'verif_masukkan_kode'
                ) {
                    return verifHandler.handleMasukkanKode(
                        interaction
                    );
                }

                if (
                    interaction.customId.startsWith(
                        'payment_'
                    )
                ) {
                    return paymentHandler.handlePaymentButton(
                        interaction
                    );
                }

                if (
                    interaction.customId ===
                    'create_donasi_ticket'
                ) {
                    return ticketHandler.showDonasiModal(
                        interaction
                    );
                }

                if (
                    interaction.customId.startsWith(
                        'complete_ticket_'
                    )
                ) {
                    return ticketHandler.handleComplete(
                        interaction
                    );
                }

                if (
                    interaction.customId.startsWith(
                        'close_ticket_'
                    )
                ) {
                    return ticketHandler.handleClose(
                        interaction
                    );
                }
                if (interaction.customId.startsWith('payment_')) {
                    return handlePaymentButton(interaction);
                }

                if (interaction.customId.startsWith('copy_')) {
                    return handleCopyButton(interaction);
                }

                if (interaction.customId === 'payment_done') {
                    return showPaymentModal(interaction);
                }
                
            } catch (error) {

                await handleInteractionError(
                    interaction,
                    error
                );
            }

            return;
        }

        // ================= MODAL =================

        if (interaction.isModalSubmit()) {

            try {

                if (
                    interaction.customId ===
                    'giveaway_create_modal'
                ) {
                    return giveawayHandler.handleGiveawayModal(
                        interaction,
                        client
                    );
                }

                if (
                    interaction.customId ===
                    'verif_modal_input'
                ) {
                    return verifHandler.handleVerifikasiModal(
                        interaction
                    );
                }

                if (
                    interaction.customId ===
                    'donasi_ticket_modal'
                ) {
                    return ticketHandler.handleDonasiModal(
                        interaction
                    );
                }

                if (
                    interaction.customId.startsWith(
                        'close_reason_'
                    )
                ) {
                    return ticketHandler.handleCloseModal(
                        interaction
                    );
                }

            } catch (error) {

                await handleInteractionError(
                    interaction,
                    error
                );
            }

            return;
        }

        // ================= SELECT MENU =================

        if (
            interaction.isStringSelectMenu()
        ) {

            try {

                if (
                    interaction.customId ===
                    'report_category_select'
                ) {
                    return reportHandler.createReportChannel(
                        interaction,
                        interaction.values[0]
                    );
                }

                if (
                    interaction.customId ===
                    'request_category_select'
                ) {
                    return requestHandler.createRequestChannel(
                        interaction,
                        interaction.values[0]
                    );
                }

            } catch (error) {

                await handleInteractionError(
                    interaction,
                    error
                );
            }
        }

    } catch (error) {

        console.error(
            '[INTERACTION CREATE FATAL]',
            error
        );
    }
}

};
