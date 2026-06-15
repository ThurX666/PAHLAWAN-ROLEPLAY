const {
    EmbedBuilder
} = require('discord.js');

const staffData = new Map();

const LOG_CHANNEL_ID = 'ISI_CHANNEL_LOGS';

function formatIndonesia() {
    return new Date().toLocaleString('id-ID', {
        timeZone: 'Asia/Jakarta',
        day: '2-digit',
        month: 'long',
        year: 'numeric',
        hour: '2-digit',
        minute: '2-digit',
        second: '2-digit'
    });
}

module.exports = {
    name: 'interactionCreate',

    async execute(interaction) {

        if (!interaction.isButton()) return;

        if (
            interaction.customId !== 'on_staff' &&
            interaction.customId !== 'off_staff'
        ) return;

        const userId = interaction.user.id;

        // ==================
        // ON STAFF
        // ==================
        if (interaction.customId === 'on_staff') {

            if (staffData.has(userId)) {
                return interaction.reply({
                    content: '❌ Kamu sudah ON STAFF.',
                    ephemeral: true
                });
            }

            const startTime = Date.now();

            staffData.set(userId, startTime);

            const embed = new EmbedBuilder()
                .setColor('Green')
                .setTitle('🟢 STAFF ON DUTY')
                .setDescription(
                    `👤 Staff: ${interaction.user}\n` +
                    `📅 Tanggal: ${formatIndonesia()}`
                )
                .setTimestamp();

            await interaction.reply({
                embeds: [embed],
                ephemeral: true
            });

            const logChannel =
                interaction.client.channels.cache.get(LOG_CHANNEL_ID);

            if (logChannel) {
                logChannel.send({
                    embeds: [
                        new EmbedBuilder()
                            .setColor('Green')
                            .setTitle('🟢 STAFF MASUK TUGAS')
                            .setDescription(
                                `👤 Staff: ${interaction.user}\n` +
                                `🆔 ID: ${interaction.user.id}\n` +
                                `📅 Waktu: ${formatIndonesia()}`
                            )
                    ]
                });
            }
        }

        // ==================
        // OFF STAFF
        // ==================
        if (interaction.customId === 'off_staff') {

            if (!staffData.has(userId)) {
                return interaction.reply({
                    content: '❌ Kamu belum ON STAFF.',
                    ephemeral: true
                });
            }

            const startTime = staffData.get(userId);
            const endTime = Date.now();

            const duration = Math.floor(
                (endTime - startTime) / 1000
            );

            const hours = Math.floor(duration / 3600);
            const minutes = Math.floor((duration % 3600) / 60);
            const seconds = duration % 60;

            const totalTime =
                `${hours} Jam ${minutes} Menit ${seconds} Detik`;

            staffData.delete(userId);

            const embed = new EmbedBuilder()
                .setColor('Red')
                .setTitle('🔴 STAFF OFF DUTY')
                .setDescription(
                    `👤 Staff: ${interaction.user}\n` +
                    `⏰ Durasi: ${totalTime}\n` +
                    `📅 Tanggal: ${formatIndonesia()}`
                )
                .setTimestamp();

            await interaction.reply({
                embeds: [embed],
                ephemeral: true
            });

            const logChannel =
                interaction.client.channels.cache.get(LOG_CHANNEL_ID);

            if (logChannel) {
                logChannel.send({
                    embeds: [
                        new EmbedBuilder()
                            .setColor('Red')
                            .setTitle('🔴 STAFF SELESAI TUGAS')
                            .setDescription(
                                `👤 Staff: ${interaction.user}\n` +
                                `🆔 ID: ${interaction.user.id}\n` +
                                `⏰ Durasi: ${totalTime}\n` +
                                `📅 Waktu: ${formatIndonesia()}`
                            )
                    ]
                });
            }
        }
    }
};