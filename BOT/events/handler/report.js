const {
    ChannelType,
    PermissionsBitField,
    EmbedBuilder,
    ActionRowBuilder,
    ButtonBuilder,
    ButtonStyle,
    StringSelectMenuBuilder
} = require('discord.js');

const fs = require('fs');
const path = require('path');

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//
//  Pahlawan ROLEPLAY REPORT SYSTEM
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//

const activeReports = new Map();
const closeCooldowns = new Map();

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//
// 📂 TRANSCRIPT FOLDER
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//

const TRANSCRIPT_DIR =
    path.join(__dirname, '../../transcripts');

if (!fs.existsSync(TRANSCRIPT_DIR)) {

    fs.mkdirSync(TRANSCRIPT_DIR, {
        recursive: true
    });
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//
// 🕒 FORMAT WIB
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//

function getWIBDate() {

    const date = new Date();

    const options = {

        timeZone: 'Asia/Jakarta',

        year: 'numeric',
        month: 'long',
        day: 'numeric',

        hour: '2-digit',
        minute: '2-digit',
        second: '2-digit',

        hour12: false
    };

    return date.toLocaleString('id-ID', options);
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//
// 📂 CATEGORY NAME
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//

function getCategoryName(category) {

    const categories = {

        player: '🚨 REPORT PLAYER',
        rtm: '💸 REPORT RTM',
        bug: '🐞 BUG REPORT',
        admin: '🛡️ REPORT ADMIN'
    };

    return categories[category] || category;
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//
// 📋 CREATE TRANSCRIPT
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//

async function createTranscript(channel) {

    const messages =
        await channel.messages.fetch({ limit: 100 });

    const logMessages = messages
        .reverse()
        .map(msg => {

            return `[${new Date(msg.createdAt).toLocaleString('id-ID')}] ${msg.author.tag}: ${msg.content || '(embed/attachment)'}`;

        }).join('\n');

    const fileName =
        `Pahlawan-report-${channel.name}-${Date.now()}.txt`;

    const filePath =
        path.join(TRANSCRIPT_DIR, fileName);

    fs.writeFileSync(filePath, logMessages, 'utf8');

    return {
        fileName,
        filePath
    };
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//
// 🔄 RESET SELECT MENU
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//

async function resetSelectMenu(interaction) {

    try {

        const resetSelectMenu =
            new StringSelectMenuBuilder()

                .setCustomId('report_category_select')

                .setPlaceholder(
                    '📂 Pilih kategori report Pahlawan RP'
                )

                .addOptions([

                    {
                        label: 'REPORT PLAYER',
                        description:
                            'Laporkan player yang melanggar rules',
                        value: 'player',
                        emoji: '🚨'
                    },

                    {
                        label: 'REPORT RTM',
                        description:
                            'Laporkan transaksi ilegal',
                        value: 'rtm',
                        emoji: '💸'
                    },

                    {
                        label: 'BUG REPORT',
                        description:
                            'Laporkan bug atau error server',
                        value: 'bug',
                        emoji: '🐞'
                    },

                    {
                        label: 'REPORT ADMIN',
                        description:
                            'Laporkan admin abuse',
                        value: 'admin',
                        emoji: '🛡️'
                    }
                ]);

        const resetRow =
            new ActionRowBuilder()
                .addComponents(resetSelectMenu);

        await interaction.message.edit({
            components: [resetRow]
        });

    } catch (e) {

        console.log(
            '❌ Gagal reset select menu:',
            e.message
        );
    }
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//
// 🎫 CREATE REPORT CHANNEL
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//

async function createReportChannel(interaction, category) {

    const config =
        require('../../config.json');

    //━━━━━━━━━━━━━━━━━━//
    // 🔄 RESET MENU
    //━━━━━━━━━━━━━━━━━━//

    await resetSelectMenu(interaction);

    //━━━━━━━━━━━━━━━━━━//
    // ❌ DOUBLE TICKET
    //━━━━━━━━━━━━━━━━━━//

    if (activeReports.has(interaction.user.id)) {

        const errorEmbed =
            new EmbedBuilder()

                .setColor(0xE74C3C)

                .setTitle(
                    '❌ REPORT MASIH AKTIF'
                )

                .setDescription(
                    [
                        'Kamu masih memiliki',
                        'report ticket yang aktif.',
                        '',
                        'Silakan tutup report sebelumnya',
                        'terlebih dahulu.'
                    ].join('\n')
                )

                .setFooter({
                    text:
                        ' Pahlawan Roleplay • Report System'
                })

                .setTimestamp();

        await interaction.reply({
            embeds: [errorEmbed],
            ephemeral: true
        });

        return null;
    }

    //━━━━━━━━━━━━━━━━━━//
    // 📂 DATA CHANNEL
    //━━━━━━━━━━━━━━━━━━//

    const categoryName =
        getCategoryName(category);

    const channelName =
        `・report-${category}-${interaction.user.username}`
            .toLowerCase()
            .replace(/[^a-z0-9-]/g, '')
            .slice(0, 90);

    let parentCategory = null;

    if (config.category?.report) {

        parentCategory =
            interaction.guild.channels.cache.get(
                config.category.report
            );
    }

    //━━━━━━━━━━━━━━━━━━//
    // 👮 ADMIN ROLE
    //━━━━━━━━━━━━━━━━━━//

    const adminRoleId =
        config.role.admin;

    const adminRole =
        await interaction.guild.roles
            .fetch(adminRoleId)
            .catch(() => null);

    if (!adminRole) {

        const errorEmbed =
            new EmbedBuilder()

                .setColor(0xE74C3C)

                .setTitle(
                    '❌ ROLE ADMIN TIDAK DITEMUKAN'
                )

                .setDescription(
                    'Pastikan ID role admin di config.json sudah benar.'
                );

        await interaction.reply({
            embeds: [errorEmbed],
            ephemeral: true
        });

        return null;
    }

    //━━━━━━━━━━━━━━━━━━//
    // 🏗️ CREATE CHANNEL
    //━━━━━━━━━━━━━━━━━━//

    const channel =
        await interaction.guild.channels.create({

            name: channelName,

            type: ChannelType.GuildText,

            parent: parentCategory,

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
                        PermissionsBitField.Flags.ReadMessageHistory
                    ]
                },

                {
                    id: adminRole.id,
                    allow: [
                        PermissionsBitField.Flags.ViewChannel,
                        PermissionsBitField.Flags.SendMessages,
                        PermissionsBitField.Flags.ReadMessageHistory
                    ]
                }
            ]
        });

    activeReports.set(
        interaction.user.id,
        channel.id
    );

    //━━━━━━━━━━━━━━━━━━//
    // 🎨 MAIN EMBED
    //━━━━━━━━━━━━━━━━━━//

    const embed =
        new EmbedBuilder()

            .setColor(0xF39C12)

            .setAuthor({
                name:
                    ' Pahlawan Roleplay • Official Report'
            })

            .setTitle(
                '📋 REPORT TICKET BERHASIL DIBUAT'
            )

            .setDescription(
                [
                    'Terima kasih telah membuat laporan.',
                    '',
                    'Staff Pahlawan Roleplay',
                    'akan segera membantu dan',
                    'memproses report kamu.'
                ].join('\n')
            )

            .addFields(

                {
                    name: '👤 Pelapor',
                    value: `<@${interaction.user.id}>`,
                    inline: true
                },

                {
                    name: '📂 Kategori',
                    value: categoryName,
                    inline: true
                },

                {
                    name: '📅 Dibuat Pada',
                    value: getWIBDate(),
                    inline: false
                },

                {
                    name: '📌 Status',
                    value: '🟡 Menunggu Staff',
                    inline: true
                }
            )

            .setFooter({
                text:
                    ' Pahlawan Roleplay • Report Center'
            })

            .setTimestamp();

    //━━━━━━━━━━━━━━━━━━//
    // 🔘 BUTTON
    //━━━━━━━━━━━━━━━━━━//

    const closeButton =
        new ButtonBuilder()

            .setCustomId('close_report_ticket')

            .setLabel('🔒 TUTUP TICKET')

            .setStyle(ButtonStyle.Danger);

    const row =
        new ActionRowBuilder()
            .addComponents(closeButton);

    //━━━━━━━━━━━━━━━━━━//
    // 📤 SEND
    //━━━━━━━━━━━━━━━━━━//

    await channel.send({

        content:
            `📢 <@${interaction.user.id}> | <@&${adminRoleId}>`,

        embeds: [embed],

        components: [row]
    });

    //━━━━━━━━━━━━━━━━━━//
    // ✅ SUCCESS EMBED
    //━━━━━━━━━━━━━━━━━━//

    const successEmbed =
        new EmbedBuilder()

            .setColor(0x2ECC71)

            .setTitle(
                '✅ REPORT BERHASIL DIBUAT'
            )

            .setDescription(
                [
                    `📂 Kategori: ${categoryName}`,
                    `🔗 Channel: ${channel}`,
                    '',
                    'Silakan jelaskan kronologi',
                    'dan kirim bukti laporan.'
                ].join('\n')
            )

            .setFooter({
                text:
                    ' Pahlawan Roleplay • Report System'
            })

            .setTimestamp();

    await interaction.reply({
        embeds: [successEmbed],
        ephemeral: true
    });

    return channel;
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//
// 🔒 HANDLE CLOSE TICKET
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//

async function handleCloseTicket(interaction) {

    const channel =
        interaction.channel;

    //━━━━━━━━━━━━━━━━━━//
    // ❌ VALIDASI CHANNEL
    //━━━━━━━━━━━━━━━━━━//

    if (!channel.name.startsWith('report-')) {

        const errorEmbed =
            new EmbedBuilder()

                .setColor(0xE74C3C)

                .setDescription(
                    '❌ Ini bukan channel report.'
                );

        return interaction.reply({
            embeds: [errorEmbed],
            ephemeral: true
        });
    }

    //━━━━━━━━━━━━━━━━━━//
    // ⏳ COOLDOWN
    //━━━━━━━━━━━━━━━━━━//

    if (closeCooldowns.has(channel.id)) {

        const errorEmbed =
            new EmbedBuilder()

                .setColor(0xE74C3C)

                .setDescription(
                    '❌ Ticket sedang dalam proses penutupan.'
                );

        return interaction.reply({
            embeds: [errorEmbed],
            ephemeral: true
        });
    }

    const config =
        require('../../config.json');

    const isReporter =
        activeReports.get(interaction.user.id) ===
        channel.id;

    const isAdmin =
        interaction.member.roles.cache.has(
            config.role.admin
        );

    if (!isReporter && !isAdmin) {

        const errorEmbed =
            new EmbedBuilder()

                .setColor(0xE74C3C)

                .setDescription(
                    '❌ Hanya pelapor atau admin yang bisa menutup ticket.'
                );

        return interaction.reply({
            embeds: [errorEmbed],
            ephemeral: true
        });
    }

    //━━━━━━━━━━━━━━━━━━//
    // ⏳ COUNTDOWN
    //━━━━━━━━━━━━━━━━━━//

    closeCooldowns.set(channel.id, true);

    let countdown = 5;

    const embed =
        new EmbedBuilder()

            .setColor(0xF1C40F)

            .setTitle(
                '⏳ TICKET AKAN DITUTUP'
            )

            .setDescription(
                `Ticket akan ditutup dalam **${countdown}** detik.\n\nKlik tombol batal jika ingin membatalkan penutupan.`
            )

            .setFooter({
                text:
                    ' Pahlawan Roleplay • Report System'
            })

            .setTimestamp();

    const cancelButton =
        new ButtonBuilder()

            .setCustomId('cancel_close_report')

            .setLabel('❌ BATALKAN')

            .setStyle(ButtonStyle.Secondary);

    const row =
        new ActionRowBuilder()
            .addComponents(cancelButton);

    const countdownMsg =
        await interaction.reply({

            embeds: [embed],

            components: [row],

            fetchReply: true
        });

    //━━━━━━━━━━━━━━━━━━//
    // ⏲️ INTERVAL
    //━━━━━━━━━━━━━━━━━━//

    const interval = setInterval(async () => {

        countdown--;

        if (countdown <= 0) {

            clearInterval(interval);

            closeCooldowns.delete(channel.id);

            //━━━━━━━━━━━━━━//
            // 📋 TRANSCRIPT
            //━━━━━━━━━━━━━━//

            const {
                fileName,
                filePath
            } = await createTranscript(channel);

            try {

                for (const [uid, cid] of activeReports) {

                    if (cid === channel.id) {

                        const reporter =
                            await interaction.client.users.fetch(uid);

                        await reporter.send({

                            content:
                                `📋 Transcript report \`${channel.name}\` telah ditutup.`,

                            files: [
                                {
                                    attachment: filePath,
                                    name: fileName
                                }
                            ]
                        }).catch(() => {});

                        break;
                    }
                }

            } catch (e) {}

            //━━━━━━━━━━━━━━//
            // 🗑️ DELETE DATA
            //━━━━━━━━━━━━━━//

            for (const [userId, ticketChannelId] of activeReports) {

                if (ticketChannelId === channel.id) {

                    activeReports.delete(userId);

                    break;
                }
            }

            setTimeout(() => {

                try {

                    fs.unlinkSync(filePath);

                } catch (e) {}

            }, 5000);

            await channel.delete();

        } else {

            const updatedEmbed =
                EmbedBuilder.from(embed)

                    .setDescription(
                        `Ticket akan ditutup dalam **${countdown}** detik.\n\nKlik tombol batal jika ingin membatalkan penutupan.`
                    );

            await countdownMsg.edit({

                embeds: [updatedEmbed],

                components: [row]

            }).catch(() => {});
        }

    }, 1000);

    //━━━━━━━━━━━━━━━━━━//
    // ❌ CANCEL BUTTON
    //━━━━━━━━━━━━━━━━━━//

    const filter = (btn) =>
        btn.customId === 'cancel_close_report' &&
        btn.user.id === interaction.user.id;

    const collector =
        countdownMsg.createMessageComponentCollector({

            filter,

            time: 5000
        });

    collector.on('collect', async (btn) => {

        clearInterval(interval);

        closeCooldowns.delete(channel.id);

        const cancelEmbed =
            new EmbedBuilder()

                .setColor(0x2ECC71)

                .setTitle(
                    '✅ PENUTUPAN DIBATALKAN'
                )

                .setDescription(
                    'Ticket tetap aktif dan bisa digunakan kembali.'
                )

                .setFooter({
                    text:
                        ' Pahlawan Roleplay • Report System'
                })

                .setTimestamp();

        await btn.update({

            embeds: [cancelEmbed],

            components: []
        });

        setTimeout(() => {

            countdownMsg.delete().catch(() => {});

        }, 3000);
    });
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//
// 📦 EXPORT
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//

module.exports = {

    activeReports,

    getWIBDate,

    getCategoryName,

    createReportChannel,

    handleCloseTicket,

    resetSelectMenu
};