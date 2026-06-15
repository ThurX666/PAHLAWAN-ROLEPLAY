const {
    SlashCommandBuilder,
    EmbedBuilder,
    PermissionFlagsBits
} = require('discord.js');

const config = require('../../config.json');

// =========================================
// FORMAT WAKTU INDONESIA
// =========================================
function formatWaktuIndonesia(date) {
    return new Intl.DateTimeFormat('id-ID', {
        weekday: 'long',
        day: 'numeric',
        month: 'long',
        year: 'numeric',
        hour: '2-digit',
        minute: '2-digit',
        second: '2-digit',
        timeZone: 'Asia/Jakarta'
    }).format(date);
}

// =========================================
// GENERATE STARS
// =========================================
function generateStars(rating) {
    return '⭐'.repeat(rating) + '✩'.repeat(5 - rating);
}

module.exports = {

    data: new SlashCommandBuilder()

        .setName('rating')
        .setDescription('⭐ Berikan penilaian kepada staff Pahlawan Roleplay')

        .addUserOption(option =>
            option.setName('admin')
                .setDescription('👑 Pilih staff admin')
                .setRequired(true))

        .addIntegerOption(option =>
            option.setName('rate')
                .setDescription('⭐ Rating dari 1 - 5')
                .setRequired(true)
                .setMinValue(1)
                .setMaxValue(5))

        .addStringOption(option =>
            option.setName('alasan')
                .setDescription('📝 Alasan memberikan rating')
                .setRequired(true))

        .addStringOption(option =>
            option.setName('note')
                .setDescription('📌 Catatan tambahan')
                .setRequired(false)),

    async execute(interaction) {

        try {

            const targetAdmin = interaction.options.getUser('admin');
            const rating = interaction.options.getInteger('rate');
            const alasan = interaction.options.getString('alasan');
            const note =
                interaction.options.getString('note') ||
                'Tidak ada catatan tambahan.';

            // =========================================
            // FETCH MEMBER
            // =========================================
            const memberTarget = await interaction.guild.members
                .fetch(targetAdmin.id)
                .catch(() => null);

            // =========================================
            // VALIDASI ROLE ADMIN
            // =========================================
            if (
                !memberTarget ||
                !memberTarget.roles.cache.has(config.role.admin)
            ) {

                return interaction.reply({
                    embeds: [
                        new EmbedBuilder()

                            .setColor('#ff0000')

                            .setTitle('❌ STAFF TIDAK VALID')

                            .setDescription(
                                `User tersebut bukan bagian
                                dari staff Pahlawan Roleplay.`
                            )

                            .setFooter({
                                text: 'Pahlawan Roleplay • Rating System'
                            })

                            .setTimestamp()
                    ],
                    ephemeral: true
                });
            }

            // =========================================
            // CEGAH SELF RATING
            // =========================================
            if (targetAdmin.id === interaction.user.id) {

                return interaction.reply({
                    embeds: [
                        new EmbedBuilder()

                            .setColor('#ff0000')

                            .setTitle('❌ TIDAK BISA')

                            .setDescription(
                                `Kamu tidak dapat memberikan
                                rating untuk diri sendiri.`
                            )

                            .setFooter({
                                text: 'Pahlawan Roleplay • Rating System'
                            })

                            .setTimestamp()
                    ],
                    ephemeral: true
                });
            }

            await interaction.deferReply({
                ephemeral: true
            });

            // =========================================
            // CHANNEL RATING
            // =========================================
            const ratingChannel =
                interaction.client.channels.cache.get(
                    config.channel.rating
                );

            if (!ratingChannel) {

                return interaction.editReply({
                    content: '❌ Channel rating tidak ditemukan.'
                });
            }

            // =========================================
            // COLOR BY RATING
            // =========================================
            let embedColor = '#E74C3C';

            if (rating >= 4) embedColor = '#2ECC71';
            else if (rating === 3) embedColor = '#F1C40F';

            const stars = generateStars(rating);

            // =========================================
            // MAIN EMBED
            // =========================================
            const embed = new EmbedBuilder()

                .setColor(embedColor)

                .setAuthor({
                    name: 'Pahlawan ROLEPLAY • STAFF RATING SYSTEM',
                    iconURL: interaction.guild.iconURL({
                        dynamic: true
                    })
                })

                .setTitle('🌟 PENILAIAN STAFF SERVER 🌟')

                .setThumbnail(
                    targetAdmin.displayAvatarURL({
                        dynamic: true,
                        size: 512
                    })
                )

                .setDescription(
                    `💛 Terima kasih telah memberikan
                    penilaian kepada staff Pahlawan Roleplay.

                    Feedback dari warga sangat membantu
                    meningkatkan kualitas pelayanan server.`
                )

                .addFields(

                    {
                        name: '👑 Staff Admin',
                        value: `${targetAdmin}`,
                        inline: true
                    },

                    {
                        name: '👤 Warga',
                        value: `${interaction.user}`,
                        inline: true
                    },

                    {
                        name: '⭐ Rating',
                        value: `\`${rating}/5\`\n${stars}`,
                        inline: true
                    },

                    {
                        name: '📝 Review / Alasan',
                        value: `>>> ${alasan}`,
                        inline: false
                    },

                    {
                        name: '📌 Catatan Tambahan',
                        value: `>>> ${note}`,
                        inline: false
                    },

                    {
                        name: '📅 Waktu',
                        value: `\`${formatWaktuIndonesia(new Date())}\``,
                        inline: false
                    }
                )

                .setFooter({
                    text: '@Pahlawan Roleplay • Staff Rating',
                    iconURL:
                        interaction.client.user.displayAvatarURL()
                })

                .setTimestamp();

            // =========================================
            // SEND EMBED
            // =========================================
            const msg = await ratingChannel.send({
                embeds: [embed]
            });

            // =========================================
            // AUTO REACT
            // =========================================
            const reacts = ['⭐', '🔥', '💛'];

            for (const react of reacts) {
                await msg.react(react).catch(() => {});
            }

            // =========================================
            // SUCCESS EMBED
            // =========================================
            const successEmbed = new EmbedBuilder()

                .setColor('#2ECC71')

                .setTitle('✅ Rating Berhasil Dikirim')

                .setDescription(
                    `Terima kasih ${interaction.user}
                    telah memberikan penilaian kepada staff.

                    Feedback kamu berhasil dipublikasikan
                    ke channel rating Pahlawan Roleplay.`
                )

                .addFields(

                    {
                        name: '👑 Staff',
                        value: `${targetAdmin}`,
                        inline: true
                    },

                    {
                        name: '⭐ Rating',
                        value: `${stars}`,
                        inline: true
                    },

                    {
                        name: '📝 Review',
                        value: `>>> ${alasan}`,
                        inline: false
                    }
                )

                .setFooter({
                    text: '☀️ Terima kasih atas partisipasi kamu 💛'
                })

                .setTimestamp();

            // =========================================
            // EDIT REPLY
            // =========================================
            await interaction.editReply({
                embeds: [successEmbed]
            });

        } catch (error) {

            console.error(error);

            const errorMessage =
                '❌ Terjadi kesalahan saat mengirim rating.';

            if (interaction.deferred || interaction.replied) {

                await interaction.editReply({
                    content: errorMessage
                });

            } else {

                await interaction.reply({
                    content: errorMessage,
                    ephemeral: true
                });
            }
        }
    }
};