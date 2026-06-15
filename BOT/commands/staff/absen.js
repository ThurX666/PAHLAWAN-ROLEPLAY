const {
    SlashCommandBuilder,
    EmbedBuilder
} = require('discord.js');

const fs = require('fs');
const path = require('path');
const config = require('../../config.json');

const dataPath = path.join(
    __dirname,
    '../../data/attendance.json'
);

// =====================
// DATA
// =====================

if (!fs.existsSync(path.dirname(dataPath))) {
    fs.mkdirSync(path.dirname(dataPath), {
        recursive: true
    });
}

if (!fs.existsSync(dataPath)) {
    fs.writeFileSync(dataPath, '[]');
}

function loadData() {
    try {

        const raw = fs.readFileSync(
            dataPath,
            'utf8'
        );

        return JSON.parse(raw || '[]');

    } catch (err) {

        console.error(
            '[ATTENDANCE JSON ERROR]',
            err
        );

        fs.writeFileSync(
            dataPath,
            '[]'
        );

        return [];
    }
}

function saveData(data) {
    fs.writeFileSync(
        dataPath,
        JSON.stringify(data, null, 2)
    );
}

function formatDuration(seconds) {

    const days =
        Math.floor(seconds / 86400);

    const hours =
        Math.floor(
            (seconds % 86400) / 3600
        );

    const minutes =
        Math.floor(
            (seconds % 3600) / 60
        );

    const secs =
        seconds % 60;

    let result = [];

    if (days > 0)
        result.push(`${days} Hari`);

    if (hours > 0)
        result.push(`${hours} Jam`);

    if (minutes > 0)
        result.push(`${minutes} Menit`);

    if (secs > 0)
        result.push(`${secs} Detik`);

    return result.join(' ') || '0 Detik';
}

module.exports = {
    data: new SlashCommandBuilder()
        .setName('attendance')
        .setDescription('Pahlawan Roleplay Attendance')

        .addSubcommand(sub =>
            sub
                .setName('absen')
                .setDescription('Mulai ON DUTY')
                .addAttachmentOption(option =>
                    option
                        .setName('foto')
                        .setDescription('Foto On Duty')
                        .setRequired(true)
                )
        )

        .addSubcommand(sub =>
            sub
                .setName('offduty')
                .setDescription('Selesaikan ON DUTY')
        )

        .addSubcommand(sub =>
            sub
                .setName('leaderboard')
                .setDescription('Leaderboard Bulanan')
        ),

    async execute(interaction) {

        if (
            !interaction.member.roles.cache.has(
                config.staffRoleId
            )
        ) {
            return interaction.reply({
                content:
                    '❌ Kamu tidak memiliki akses.',
                ephemeral: true
            });
        }

        const sub =
            interaction.options.getSubcommand();

        let data = loadData();

        const today =
            new Date()
                .toISOString()
                .split('T')[0];

        // =====================
        // ABSEN
        // =====================

        if (sub === 'absen') {

            const foto =
                interaction.options.getAttachment(
                    'foto'
                );

            if (
                !foto.contentType?.startsWith(
                    'image'
                )
            ) {
                return interaction.reply({
                    content:
                        '❌ File harus berupa gambar.',
                    ephemeral: true
                });
            }

            const activeDuty = data.find(
                x =>
                    x.userId ===
                        interaction.user.id &&
                    x.onDuty === true
            );

            if (activeDuty) {
                return interaction.reply({
                    content:
                        '❌ Kamu masih ON DUTY.',
                    ephemeral: true
                });
            }

            data.push({
                userId: interaction.user.id,
                username:
                    interaction.user.username,
                image: foto.url,
                date: today,
                startTime: Date.now(),
                endTime: null,
                totalSeconds: 0,
                onDuty: true
            });

            saveData(data);

            const embed =
                new EmbedBuilder()
                    .setColor('#ff0000')
                    .setTitle(
                        'Pahlawan ROLEPLAY'
                    )
                    .setDescription(
                        '🟢 Staff berhasil melakukan **ON DUTY**'
                    )
                    .addFields(
                        {
                            name: '👤 Staff',
                            value:
                                interaction.user.username,
                            inline: true
                        },
                        {
                            name: '📅 Tanggal',
                            value: today,
                            inline: true
                        }
                    )
                    .setImage(
                        foto.url
                    )
                    .setTimestamp();

            const channel =
                interaction.guild.channels.cache.get(
                    config.absenChannelId
                );

            if (channel) {
                await channel.send({
                    embeds: [embed]
                });
            }

            return interaction.reply({
                content:
                    '✅ ON DUTY berhasil dicatat.',
                ephemeral: true
            });
        }

        // =====================
        // OFF DUTY
        // =====================

        if (sub === 'offduty') {

            const duty = data.find(
                x =>
                    x.userId ===
                        interaction.user.id &&
                    x.onDuty === true
            );

            if (!duty) {
                return interaction.reply({
                    content:
                        '❌ Kamu belum ON DUTY.',
                    ephemeral: true
                });
            }

            duty.endTime = Date.now();

            const duration =
                duty.endTime -
                duty.startTime;

            const totalSeconds =
                Math.floor(
                    duration / 1000
                );

            duty.totalSeconds =
                totalSeconds;

            duty.onDuty = false;

            saveData(data);

            const embed =
                new EmbedBuilder()
                    .setColor('#FF0000')
                    .setTitle(
                        '🔴 OFF DUTY'
                    )
                    .addFields(
                        {
                            name: '👤 Staff',
                            value:
                                interaction.user.username
                        },
                        {
                            name:
                                '⏰ Total Duty',
                            value:
                                formatDuration(
                                    totalSeconds
                                )
                        }
                    )
                    .setTimestamp();

            const channel =
                interaction.guild.channels.cache.get(
                    config.absenChannelId
                );

            if (channel) {
                await channel.send({
                    embeds: [embed]
                });
            }

            return interaction.reply({
                embeds: [embed],
                ephemeral: true
            });
        }

        // =====================
        // LEADERBOARD
        // =====================

        if (sub === 'leaderboard') {

            const currentMonth =
                new Date().getMonth();

            const currentYear =
                new Date().getFullYear();

            const leaderboard = {};

            for (const entry of data) {

                const entryDate =
                    new Date(entry.date);

                if (
                    entryDate.getMonth() !==
                        currentMonth ||
                    entryDate.getFullYear() !==
                        currentYear
                ) continue;

                if (
                    !leaderboard[
                        entry.userId
                    ]
                ) {
                    leaderboard[
                        entry.userId
                    ] = {
                        username:
                            entry.username,
                        seconds: 0
                    };
                }

                leaderboard[
                    entry.userId
                ].seconds +=
                    entry.totalSeconds || 0;
            }

            const ranking =
                Object.values(
                    leaderboard
                )
                    .sort(
                        (a, b) =>
                            b.seconds -
                            a.seconds
                    )
                    .slice(0, 10);

            let description = '';

            ranking.forEach(
                (
                    user,
                    index
                ) => {

                    const medal =
                        index === 0
                            ? '🥇'
                            : index === 1
                            ? '🥈'
                            : index === 2
                            ? '🥉'
                            : '🏅';

                    description +=
                        `${medal} **#${index + 1}** ${user.username}\n` +
                        `⏰ ${formatDuration(user.seconds)}\n\n`;
                }
            );

            const embed =
                new EmbedBuilder()
                    .setColor(
                        '#ff0000'
                    )
                    .setTitle(
                        '🏆 LEADERBOARD STAFF BULAN INI'
                    )
                    .setDescription(
                        description ||
                            'Belum ada data attendance.'
                    )
                    .setTimestamp();

            return interaction.reply({
                embeds: [embed]
            });
        }
    }
};