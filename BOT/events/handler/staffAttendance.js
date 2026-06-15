const { EmbedBuilder } = require('discord.js');
const fs = require('fs');
const path = require('path');
const config = require('../../config.json');

const staffFile = path.join(
__dirname,
'../../data/staffon.json'
);

function loadData() {
try {

    if (!fs.existsSync(staffFile)) {
        fs.writeFileSync(staffFile, '{}');
    }

    const raw = fs.readFileSync(
        staffFile,
        'utf8'
    );

    return JSON.parse(raw);

} catch (err) {

    console.error(
        '[STAFF LOAD ERROR]',
        err
    );

    return {};
}

}

function saveData(data) {
try {

    fs.writeFileSync(
        staffFile,
        JSON.stringify(data, null, 2)
    );

} catch (err) {

    console.error(
        '[STAFF SAVE ERROR]',
        err
    );
}

}

function getWIB() {

return new Date().toLocaleString(
    'id-ID',
    {
        timeZone: 'Asia/Jakarta'
    }
);

}

module.exports = {

async execute(interaction) {

    try {

        if (!interaction.isButton()) return;

        if (
            interaction.customId !== 'on_staff' &&
            interaction.customId !== 'off_staff'
        ) {
            return;
        }

        const data = loadData();
        const userId = interaction.user.id;

        const logChannel =
            interaction.client.channels.cache.get(
                config.staffLogChannel
            );

        // =========================
        // ON STAFF
        // =========================

        if (interaction.customId === 'on_staff') {

            if (data[userId]) {

                return interaction.reply({
                    content:
                        '❌ Kamu sudah ON STAFF.',
                    ephemeral: true
                });

            }

            data[userId] = {
                username: interaction.user.tag,
                startTime: Date.now(),
                waktuMasuk: getWIB()
            };

            saveData(data);

            console.log(
                '[STAFF ON]',
                interaction.user.tag
            );

            await interaction.reply({
                embeds: [
                    new EmbedBuilder()
                        .setColor('Green')
                        .setTitle(
                            '🟢 STAFF ON DUTY'
                        )
                        .setDescription(
                            `👤 Staff: ${interaction.user}\n` +
                            `🕒 Masuk: ${getWIB()}`
                        )
                ],
                ephemeral: true
            });

            if (logChannel) {

                await logChannel.send({
                    embeds: [
                        new EmbedBuilder()
                            .setColor('Green')
                            .setTitle(
                                '🟢 STAFF MASUK TUGAS'
                            )
                            .setDescription(
                                `👤 Staff: ${interaction.user}\n` +
                                `🆔 ID: ${interaction.user.id}\n` +
                                `🕒 Waktu: ${getWIB()}`
                            )
                    ]
                });

            }

            return;
        }

        // =========================
        // OFF STAFF
        // =========================

        if (interaction.customId === 'off_staff') {

            if (!data[userId]) {

                return interaction.reply({
                    content:
                        '❌ Kamu belum ON STAFF.',
                    ephemeral: true
                });

            }

            const startTime =
                data[userId].startTime;

            const duration =
                Math.floor(
                    (Date.now() - startTime) /
                    1000
                );

            const hours =
                Math.floor(duration / 3600);

            const minutes =
                Math.floor(
                    (duration % 3600) / 60
                );

            const seconds =
                duration % 60;

            const totalTime =
                `${hours} Jam ${minutes} Menit ${seconds} Detik`;

            delete data[userId];

            saveData(data);

            console.log(
                '[STAFF OFF]',
                interaction.user.tag
            );

            await interaction.reply({
                embeds: [
                    new EmbedBuilder()
                        .setColor('Red')
                        .setTitle(
                            '🔴 STAFF OFF DUTY'
                        )
                        .setDescription(
                            `👤 Staff: ${interaction.user}\n` +
                            `⏰ Durasi: ${totalTime}`
                        )
                ],
                ephemeral: true
            });

            if (logChannel) {

                await logChannel.send({
                    embeds: [
                        new EmbedBuilder()
                            .setColor('Red')
                            .setTitle(
                                '🔴 STAFF SELESAI TUGAS'
                            )
                            .setDescription(
                                `👤 Staff: ${interaction.user}\n` +
                                `🆔 ID: ${interaction.user.id}\n` +
                                `⏰ Durasi: ${totalTime}`
                            )
                    ]
                });

            }

            return;
        }

    } catch (err) {

        console.error(
            '[STAFF ATTENDANCE ERROR]',
            err
        );

        if (
            !interaction.replied &&
            !interaction.deferred
        ) {

            await interaction.reply({
                content:
                    '❌ Terjadi kesalahan pada sistem staff.',
                ephemeral: true
            });

        }

    }

}

};