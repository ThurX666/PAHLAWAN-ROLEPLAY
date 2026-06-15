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

const activeRequests = new Map();
const closeCooldowns = new Map();

const TRANSCRIPT_DIR = path.join(__dirname, '../../transcripts');
if (!fs.existsSync(TRANSCRIPT_DIR)) fs.mkdirSync(TRANSCRIPT_DIR, { recursive: true });

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

function getCategoryName(category) {
const categories = {

    creator: '🎨 REQUEST CREATOR',

    bisnis: '💼 REQUEST BISNIS',

    pc: '🖥️ REQUEST PLAYER PC',

    import: '📦 REQUEST IMPORT',

    faction: '🏢 REQUEST FACTION',

    workshop: '🔧 REQUEST WORKSHOP',

    refund: '💸 REQUEST REFUND',

    unban: '🛡️ REQUEST UNBAN / BANDING'
};

return categories[category] || category;
}

async function createTranscript(channel) {
    const messages = await channel.messages.fetch({ limit: 100 });
    const logMessages = messages.reverse().map(msg =>
        `[${new Date(msg.createdAt).toLocaleString('id-ID')}] ${msg.author.tag}: ${msg.content || '(embed/attachment)'}`
    ).join('\n');
    const fileName = `transcript-${channel.name}-${Date.now()}.txt`;
    const filePath = path.join(TRANSCRIPT_DIR, fileName);
    fs.writeFileSync(filePath, logMessages, 'utf8');
    return { fileName, filePath };
}

async function resetSelectMenu(interaction) {

    try {

        const resetMenu = new StringSelectMenuBuilder()

            .setCustomId('request_category_select')

            .setPlaceholder('📋 Pilih layanan request Pahlawan Roleplay')

            .addOptions([

                {
                    label: 'REQUEST CREATOR',
                    description: 'Pengajuan menjadi Creator Pahlawan RP',
                    value: 'creator',
                    emoji: '🎨'
                },

                {
                    label: 'REQUEST BISNIS',
                    description: 'Pengajuan bisnis atau usaha roleplay',
                    value: 'bisnis',
                    emoji: '💼'
                },

                {
                    label: 'REQUEST PLAYER PC',
                    description: 'Pengajuan whitelist player PC',
                    value: 'pc',
                    emoji: '🖥️'
                },

                {
                    label: 'REQUEST IMPORT',
                    description: 'Import kendaraan atau item roleplay',
                    value: 'import',
                    emoji: '📦'
                },

                {
                    label: 'REQUEST FACTION',
                    description: 'Pengajuan faction resmi server',
                    value: 'faction',
                    emoji: '🏢'
                },

                {
                    label: 'REQUEST WORKSHOP',
                    description: 'Pengajuan workshop atau bengkel',
                    value: 'workshop',
                    emoji: '🔧'
                },

                {
                    label: 'REQUEST REFUND',
                    description: 'Pengajuan refund item atau transaksi',
                    value: 'refund',
                    emoji: '💸'
                },

                {
                    label: 'REQUEST UNBAN / BANDING',
                    description: 'Banding atau pengajuan unban server',
                    value: 'unban',
                    emoji: '🛡️'
                }
            ]);

        const row = new ActionRowBuilder()
            .addComponents(resetMenu);

        await interaction.message.edit({
            components: [row]
        });

        } catch (e) {

            console.log(
                'Gagal reset request menu:',
                e.message
            );
        }
    }

async function createRequestChannel(interaction, category) {
    const config = require('../../config.json');
    await interaction.deferReply({ flags: 64 }); // ephemeral menggunakan flags

    await resetSelectMenu(interaction).catch(e => console.log('Reset menu error:', e));

    if (activeRequests.has(interaction.user.id)) {
        const errorEmbed = new EmbedBuilder()
            .setColor(0xFF0000)
            .setDescription('**GAGAL:** Kamu masih memiliki request yang aktif!\nTutup request sebelumnya terlebih dahulu.');
        await interaction.editReply({ embeds: [errorEmbed] });
        return null;
    }

    const categoryName = getCategoryName(category);
    const channelName = `request-${category}-${interaction.user.username.toLowerCase()}`;
    
    let parentCategory = null;
    if (config.category && config.category.request) {
        parentCategory = interaction.guild.channels.cache.get(config.category.request);
    }
    
    const adminRoleId = config.role.admin;
    const adminRole = await interaction.guild.roles.fetch(adminRoleId).catch(() => null);
    if (!adminRole) {
        const errorEmbed = new EmbedBuilder()
            .setColor(0xFF0000)
            .setDescription('**GAGAL:** Role admin tidak ditemukan! Pastikan ID role di config.json benar.');
        await interaction.editReply({ embeds: [errorEmbed] });
        return null;
    }

    const channel = await interaction.guild.channels.create({
        name: channelName,
        type: ChannelType.GuildText,
        parent: parentCategory,
        permissionOverwrites: [
            { id: interaction.guild.id, deny: [PermissionsBitField.Flags.ViewChannel] },
            { id: interaction.user.id, allow: [PermissionsBitField.Flags.ViewChannel, PermissionsBitField.Flags.SendMessages, PermissionsBitField.Flags.ReadMessageHistory] },
            { id: adminRole.id, allow: [PermissionsBitField.Flags.ViewChannel, PermissionsBitField.Flags.SendMessages, PermissionsBitField.Flags.ReadMessageHistory] }
        ]
    });

    activeRequests.set(interaction.user.id, channel.id);

    const content = `<@${interaction.user.id}> <@&${adminRoleId}>`;

    const embed = new EmbedBuilder()

    .setColor(0xFFD700)

    .setAuthor({
        name: 'Pahlawan Pahlawan ROLEPLAY • REQUEST CENTER',
        iconURL: interaction.guild.iconURL({ dynamic: true })
    })

    .setTitle('📩 Pahlawan ROLEPLAY REQUEST TICKET')

    .setDescription(
        [
            'Pahlawan Request ticket berhasil dibuat.',
            '',
            'Staff Pahlawan Roleplay akan segera',
            'membantu dan memproses request kamu.',
            '',
            '📌 Silakan jelaskan kebutuhan request',
            'dengan lengkap dan jelas.'
        ].join('\n')
    )

    .addFields(
        {
            name: '👤 Pemohon',
            value: `<@${interaction.user.id}>`,
            inline: true
        },

        {
            name: '📂 Jenis Request',
            value: categoryName,
            inline: true
        },

        {
            name: '📅 Tanggal Dibuat',
            value: getWIBDate(),
            inline: false
        },

        {
            name: '📌 Status',
            value: '🟡 Menunggu Staff',
            inline: true
        }
    )

    .setThumbnail(
        interaction.user.displayAvatarURL({
            dynamic: true,
            size: 512
        })
    )

    .setFooter({
        text: 'Pahlawan Pahlawan ROLEPLAY • REQUEST SYSTEM',
        iconURL: interaction.guild.iconURL({ dynamic: true })
    })

    .setTimestamp();

    const closeButton = new ButtonBuilder()

        .setCustomId('close_request_ticket')

        .setLabel('🔒 CLOSE TICKET')

        .setStyle(ButtonStyle.Danger);

    const row = new ActionRowBuilder()
        .addComponents(closeButton);

    await channel.send({
        content,
        embeds: [embed],
        components: [row]
    });

    const successEmbed = new EmbedBuilder()

        .setColor(0x00FF99)

        .setDescription(
            `✅ Request ticket berhasil dibuat!\n\n` +
            `📂 Jenis Request: ${categoryName}\n` +
            `🔗 Channel: ${channel}`
        )

        .setFooter({
            text: 'Pahlawan Pahlawan ROLEPLAY • REQUEST SYSTEM',
            iconURL: interaction.guild.iconURL({ dynamic: true })
        });

    await interaction.editReply({
        embeds: [successEmbed]
    });

    return channel;
}

async function handleCloseTicket(interaction) {
    const channel = interaction.channel;
    if (!channel.name.startsWith('request-')) {

        const errorEmbed = new EmbedBuilder()

            .setColor(0xFF3B30)

            .setDescription(
                '❌ Channel ini bukan ticket request Pahlawan Roleplay!'
            );

        return interaction.reply({
            embeds: [errorEmbed],
            flags: 64
        });
    }

    if (closeCooldowns.has(channel.id)) {

        const errorEmbed = new EmbedBuilder()

            .setColor(0xFF3B30)

            .setDescription(
                '⚠️ Ticket sedang dalam proses penutupan!'
            );

        return interaction.reply({
            embeds: [errorEmbed],
            flags: 64
        });
    }

    const config = require('../../config.json');

    const isRequester =
        activeRequests.get(interaction.user.id) === channel.id;

    const isAdmin =
        interaction.member.roles.cache.has(config.role.admin);

    if (!isRequester && !isAdmin) {

        const errorEmbed = new EmbedBuilder()

            .setColor(0xFF3B30)

            .setDescription(
                '❌ Hanya warga atau admin Pahlawan Roleplay\n' +
                'yang dapat menutup ticket ini!'
            );

        return interaction.reply({
            embeds: [errorEmbed],
            flags: 64
        });
    }

    closeCooldowns.set(channel.id, true);
    let countdown = 5;
    const embed = new EmbedBuilder()

        .setColor(0xffaa00)

        .setTitle('⏳ TICKET AKAN DITUTUP')

        .setDescription(
            `Ticket request akan ditutup dalam **${countdown}** detik...\n\n` +
            `Klik tombol **BATALKAN** untuk menghentikan proses penutupan ticket.`
        )

        .setFooter({
            text: 'Pahlawan Pahlawan ROLEPLAY • REQUEST SYSTEM',
            iconURL: interaction.guild.iconURL({ dynamic: true })
        })

        .setTimestamp();

    const cancelButton = new ButtonBuilder()

        .setCustomId('cancel_close_request')

        .setLabel('❌ BATALKAN')

        .setStyle(ButtonStyle.Secondary);

    const row = new ActionRowBuilder()
        .addComponents(cancelButton);

    const countdownMsg = await interaction.reply({
        embeds: [embed],
        components: [row],
        fetchReply: true,
        flags: 64
    });

    const interval = setInterval(async () => {
        countdown--;
        if (countdown <= 0) {
            clearInterval(interval);
            closeCooldowns.delete(channel.id);
            const { fileName, filePath } = await createTranscript(channel);

            for (const [uid, cid] of activeRequests) {
                if (cid === channel.id) {
                    const requester = await interaction.client.users.fetch(uid);
                    await requester.send({ content: `📋 **Transcript request ticket** \`${channel.name}\` telah ditutup.`, files: [{ attachment: filePath, name: fileName }] }).catch(() => {});
                    break;
                }
            }

            for (const [uid, cid] of activeRequests) if (cid === channel.id) { activeRequests.delete(uid); break; }
            
            // Perbaikan: gunakan fs.promises.unlink
            setTimeout(async () => {
                try {
                    await fs.promises.unlink(filePath);
                } catch (e) { /* ignore */ }
            }, 5000);
            
            await channel.delete();
        } else {
            const updatedEmbed = EmbedBuilder.from(embed).setDescription(`Ticket akan ditutup dalam **${countdown}** detik...\nKlik **BATALKAN** untuk membatalkan.`);
            await countdownMsg.edit({ embeds: [updatedEmbed], components: [row] }).catch(() => {});
        }
    }, 1000);

    const filter = (btn) =>
        btn.customId === 'cancel_close_request' &&
        btn.user.id === interaction.user.id;

    const collector =
        countdownMsg.createMessageComponentCollector({
            filter,
            time: 5000
        });

    collector.on('collect', async (btn) => {

        clearInterval(interval);

        closeCooldowns.delete(channel.id);

        const cancelEmbed = new EmbedBuilder()

            .setColor(0x00ff99)

            .setTitle('✅ PENUTUPAN DIBATALKAN')

            .setDescription(
                'Ticket request tetap aktif dan dapat digunakan kembali 🚀'
            )

            .setFooter({
                text: 'Pahlawan Pahlawan ROLEPLAY • REQUEST SYSTEM',
                iconURL: interaction.guild.iconURL({ dynamic: true })
            })

            .setTimestamp();

        await btn.update({
            embeds: [cancelEmbed],
            components: []
        });

        setTimeout(() =>
            countdownMsg.delete().catch(() => {}),
            3000
        );
    });
}

module.exports = {
    activeRequests,
    getWIBDate,
    getCategoryName,
    createRequestChannel,
    handleCloseTicket
};