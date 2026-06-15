const fs = require('fs');
const path = require('path');
const { 
    ModalBuilder, 
    TextInputBuilder, 
    TextInputStyle, 
    ActionRowBuilder, 
    EmbedBuilder, 
    ButtonBuilder, 
    ButtonStyle 
} = require('discord.js');

// ================= DATABASE PATH =================
const GIVEAWAY_DB = path.join(__dirname, '../../data/giveaways.json');

// ================= INIT DATABASE =================
function initDatabase() {
    if (!fs.existsSync(path.join(__dirname, '../../data'))) {
        fs.mkdirSync(path.join(__dirname, '../../data'), { recursive: true });
    }
    if (!fs.existsSync(GIVEAWAY_DB)) {
        fs.writeFileSync(GIVEAWAY_DB, JSON.stringify([], null, 2));
    }
}
initDatabase();

// ================= READ/WRITE =================
function readGiveaways() {
    const data = fs.readFileSync(GIVEAWAY_DB, 'utf8');
    return JSON.parse(data);
}

function writeGiveaways(giveaways) {
    fs.writeFileSync(GIVEAWAY_DB, JSON.stringify(giveaways, null, 2));
}

// ================= GENERATE ID =================
function generateId() {
    return Date.now().toString(36) + Math.random().toString(36).substr(2, 5);
}

// ================= PARSE DURATION =================
function parseDuration(durationStr) {
    if (!durationStr || typeof durationStr !== 'string') {
        throw new Error('Duration string is required');
    }
    
    const parts = durationStr.trim().split(/\s+/);
    if (parts.length < 2) {
        throw new Error('Invalid duration format. Use: "angka satuan" (contoh: "30 menit")');
    }
    
    const number = parseInt(parts[0]);
    if (isNaN(number) || number <= 0) {
        throw new Error('Duration number must be a positive integer');
    }
    
    const unit = parts[1].toLowerCase();
    let multiplier = 60000;
    
    if (unit.includes('jam')) {
        multiplier = 3600000;
    } else if (unit.includes('hari')) {
        multiplier = 86400000;
    } else if (unit.includes('detik')) {
        multiplier = 1000;
    } else if (!unit.includes('menit')) {
        throw new Error('Invalid time unit. Use: menit, jam, hari, detik');
    }
    
    return number * multiplier;
}

// ================= CRUD OPERATIONS =================
function createGiveaway(data) {
    const giveaways = readGiveaways();
    const newGiveaway = {
        id: generateId(),
        ...data,
        status: 'active',
        participants: [],
        winners: [],
        created_at: new Date().toISOString()
    };
    giveaways.push(newGiveaway);
    writeGiveaways(giveaways);
    return newGiveaway;
}

function getGiveaway(id) {
    const giveaways = readGiveaways();
    return giveaways.find(g => g.id === id);
}

function getGiveawayByMessage(messageId) {
    const giveaways = readGiveaways();
    return giveaways.find(g => g.message_id === messageId && g.status === 'active');
}

function addParticipant(id, userId) {
    const giveaways = readGiveaways();
    const index = giveaways.findIndex(g => g.id === id);
    
    if (index === -1) return false;
    if (giveaways[index].status !== 'active') return false;
    if (giveaways[index].participants.includes(userId)) return false;
    
    giveaways[index].participants.push(userId);
    writeGiveaways(giveaways);
    return true;
}

function removeParticipant(id, userId) {
    const giveaways = readGiveaways();
    const index = giveaways.findIndex(g => g.id === id);
    
    if (index === -1) return false;
    if (!giveaways[index].participants.includes(userId)) return false;
    
    giveaways[index].participants = giveaways[index].participants.filter(p => p !== userId);
    writeGiveaways(giveaways);
    return true;
}

function endGiveaway(id, winners) {
    const giveaways = readGiveaways();
    const index = giveaways.findIndex(g => g.id === id);
    
    if (index === -1) return false;
    
    giveaways[index].status = 'ended';
    giveaways[index].winners = winners;
    giveaways[index].ended_at = new Date().toISOString();
    writeGiveaways(giveaways);
    return true;
}

function cancelGiveaway(id) {
    const giveaways = readGiveaways();
    const index = giveaways.findIndex(g => g.id === id);
    
    if (index === -1) return false;
    
    giveaways[index].status = 'cancelled';
    writeGiveaways(giveaways);
    return true;
}

function setWinners(id, winners) {
    const giveaways = readGiveaways();
    const index = giveaways.findIndex(g => g.id === id);
    
    if (index === -1) return false;
    
    giveaways[index].winners = winners;
    writeGiveaways(giveaways);
    return true;
}

function pickRandomWinners(participants, count) {
    const shuffled = [...participants];
    for (let i = shuffled.length - 1; i > 0; i--) {
        const j = Math.floor(Math.random() * (i + 1));
        [shuffled[i], shuffled[j]] = [shuffled[j], shuffled[i]];
    }
    return shuffled.slice(0, count);
}

// ================= SCHEDULE GIVEAWAY END =================
function scheduleGiveawayEnd(client, giveawayId, durationMs, guildId) {
    setTimeout(async () => {
        try {
            const giveaway = getGiveaway(giveawayId);
            if (!giveaway || giveaway.status !== 'active') return;
            
            const guild = await client.guilds.fetch(guildId);
            const channel = await guild.channels.fetch(giveaway.channel_id);
            const message = await channel.messages.fetch(giveaway.message_id);
            
            const winners = pickRandomWinners(giveaway.participants, giveaway.winners_count);
            endGiveaway(giveawayId, winners);
            
            const winnerMentions = winners.length > 0 
                ? winners.map(id => `<@${id}>`).join(', ')
                : 'Tidak ada peserta';
            
            const updatedEmbed = EmbedBuilder.from(message.embeds[0])
                .setColor(0x00FF00)
                .setFooter({ text: '✅ Giveaway telah berakhir' });
            
            const disabledButton = new ButtonBuilder()
                .setCustomId('giveaway_ended')
                .setLabel('🎉 Giveaway Berakhir')
                .setStyle(ButtonStyle.Secondary)
                .setDisabled(true);
            
            const row = new ActionRowBuilder().addComponents(disabledButton);
            
            await message.edit({ embeds: [updatedEmbed], components: [row] });
            
            await channel.send({
                content: `🎉 **WINNER ANNOUNCEMENT** 🎉\n\n**Hadiah:** ${giveaway.prize}\n**Pemenang:** ${winnerMentions}\n\nSelamat kepada para pemenang! 🎊`
            });
            
        } catch (error) {
            console.error('Error ending giveaway:', error);
        }
    }, durationMs);
}

// ================= MODAL & BUTTON HANDLERS =================
async function showCreateModal(interaction) {
    const modal = new ModalBuilder()
        .setCustomId('giveaway_create_modal')
        .setTitle('🎉 Buat Giveaway');
    
    const prizeInput = new TextInputBuilder()
        .setCustomId('prize')
        .setLabel('Hadiah Giveaway')
        .setStyle(TextInputStyle.Short)
        .setPlaceholder('Contoh: Discord Nitro 1 Month')
        .setRequired(true);
    
    const durationInput = new TextInputBuilder()
        .setCustomId('duration')
        .setLabel('Durasi (contoh: 30 menit)')
        .setStyle(TextInputStyle.Short)
        .setPlaceholder('30 menit / 2 jam / 7 hari')
        .setRequired(true);
    
    const winnersInput = new TextInputBuilder()
        .setCustomId('winners')
        .setLabel('Jumlah Pemenang')
        .setStyle(TextInputStyle.Short)
        .setPlaceholder('1')
        .setRequired(true);
    
    const descriptionInput = new TextInputBuilder()
        .setCustomId('description')
        .setLabel('Deskripsi (opsional)')
        .setStyle(TextInputStyle.Paragraph)
        .setPlaceholder('Deskripsi tentang giveaway...')
        .setRequired(false);
    
    modal.addComponents(
        new ActionRowBuilder().addComponents(prizeInput),
        new ActionRowBuilder().addComponents(durationInput),
        new ActionRowBuilder().addComponents(winnersInput),
        new ActionRowBuilder().addComponents(descriptionInput)
    );
    
    await interaction.showModal(modal);
}

async function handleGiveawayModal(interaction, client) {
    await interaction.deferReply({ ephemeral: true });
    
    const prize = interaction.fields.getTextInputValue('prize');
    const duration = interaction.fields.getTextInputValue('duration');
    const winners = interaction.fields.getTextInputValue('winners');
    const description = interaction.fields.getTextInputValue('description') || 'Tidak ada deskripsi';
    
    const timeRegex = /^(\d+)\s+(menit|jam|hari|detik)$/i;
    if (!timeRegex.test(duration)) {
        return interaction.editReply({
            content: '❌ **Format waktu salah!** Gunakan format: `angka` + `satuan` (contoh: `30 menit`, `2 jam`, `7 hari`)'
        });
    }
    
    const winnersCount = parseInt(winners);
    if (isNaN(winnersCount) || winnersCount < 1 || winnersCount > 100) {
        return interaction.editReply({
            content: '❌ **Jumlah pemenang harus angka 1-100!**'
        });
    }
    
    let durationMs;
    try {
        durationMs = parseDuration(duration);
    } catch (error) {
        return interaction.editReply({
            content: `❌ **Error parsing waktu: ${error.message}**`
        });
    }
    
    const endsAt = new Date(Date.now() + durationMs);
    const timestamp = Math.floor(endsAt.getTime() / 1000);
    
    const embed = new EmbedBuilder()
        .setColor(0x5865F2)
        .setTitle(prize)
        .setDescription(description)
        .addFields(
            { name: 'Berakhir', value: `<t:${timestamp}:R> (<t:${timestamp}:f>)`, inline: false },
            { name: 'Host', value: `<@${interaction.user.id}>`, inline: true },
            { name: 'Pemenang', value: `${winnersCount}`, inline: true },
            { name: 'Entries', value: '`0`', inline: true }
        )
        .setFooter({ text: 'Klik tombol di bawah untuk ikut giveaway!' })
        .setTimestamp(endsAt);
    
    const button = new ButtonBuilder()
        .setCustomId('giveaway_join')
        .setLabel('🎉 Ikuti Giveaway')
        .setStyle(ButtonStyle.Primary);
    
    const row = new ActionRowBuilder().addComponents(button);
    const message = await interaction.channel.send({ embeds: [embed], components: [row] });
    
    const giveaway = createGiveaway({
        guild_id: interaction.guild.id,
        channel_id: interaction.channel.id,
        message_id: message.id,
        host_id: interaction.user.id,
        prize: prize,
        description: description,
        winners_count: winnersCount,
        duration: durationMs,
        ends_at: endsAt.toISOString()
    });
    
    const updatedEmbed = EmbedBuilder.from(embed)
        .addFields({ name: 'ID', value: `\`${giveaway.id}\``, inline: true });
    
    await message.edit({ embeds: [updatedEmbed] });
    scheduleGiveawayEnd(client, giveaway.id, durationMs, interaction.guild.id);
    
    await interaction.editReply({
        content: `✅ **Giveaway berhasil dibuat!**\nID: \`${giveaway.id}\``
    });
}

async function handleJoinGiveaway(interaction) {
    await interaction.deferReply({ ephemeral: true });
    
    const giveaway = getGiveawayByMessage(interaction.message.id);
    
    if (!giveaway) {
        return interaction.editReply({
            content: '❌ **Giveaway tidak ditemukan atau sudah berakhir!**'
        });
    }
    
    if (giveaway.status !== 'active') {
        return interaction.editReply({
            content: `❌ **Giveaway sudah ${giveaway.status === 'ended' ? 'selesai' : 'dibatalkan'}!**`
        });
    }
    
    if (giveaway.participants.includes(interaction.user.id)) {
        const row = new ActionRowBuilder().addComponents(
            new ButtonBuilder()
                .setCustomId(`giveaway_leave_${giveaway.id}`)
                .setLabel('🚪 Keluar Giveaway')
                .setStyle(ButtonStyle.Danger)
        );
        
        return interaction.editReply({
            content: '⚠️ **Kamu sudah mengikuti giveaway ini!**\nKlik tombol di bawah jika ingin keluar.',
            components: [row]
        });
    }
    
    const success = addParticipant(giveaway.id, interaction.user.id);
    if (!success) {
        return interaction.editReply({
            content: '❌ **Gagal mengikuti giveaway!**'
        });
    }
    
    const updatedGiveaway = getGiveaway(giveaway.id);
    
    // Update embed entries
    try {
        const embed = EmbedBuilder.from(interaction.message.embeds[0]);
        const fields = embed.data.fields || [];
        
        let entriesFieldIndex = fields.findIndex(f => 
            f.name === 'Entries' || (f.value && f.value.match(/`\d+`/))
        );
        
        if (entriesFieldIndex !== -1) {
            fields[entriesFieldIndex].value = `\`${updatedGiveaway.participants.length}\``;
            embed.setFields(fields);
            await interaction.message.edit({ embeds: [embed] });
        }
    } catch (error) {
        console.error('Error updating embed:', error);
    }
    
    await interaction.editReply({
        content: '✅ **Kamu berhasil mengikuti giveaway!**\nSemoga beruntung! 🍀'
    });
}

async function handleLeaveGiveaway(interaction) {
    await interaction.deferReply({ ephemeral: true });
    
    const giveawayId = interaction.customId.replace('giveaway_leave_', '');
    const giveaway = getGiveaway(giveawayId);
    
    if (!giveaway) {
        return interaction.editReply({
            content: '❌ **Giveaway tidak ditemukan!**'
        });
    }
    
    const success = removeParticipant(giveaway.id, interaction.user.id);
    if (!success) {
        return interaction.editReply({
            content: '❌ **Kamu tidak terdaftar dalam giveaway ini!**'
        });
    }
    
    const updatedGiveaway = getGiveaway(giveaway.id);
    
    // Update embed entries
    try {
        const channel = interaction.guild.channels.cache.get(giveaway.channel_id);
        if (channel) {
            const message = await channel.messages.fetch(giveaway.message_id).catch(() => null);
            if (message && message.embeds.length > 0) {
                const embed = EmbedBuilder.from(message.embeds[0]);
                const fields = embed.data.fields || [];
                
                const entriesFieldIndex = fields.findIndex(f => 
                    f.name === 'Entries' || (f.value && f.value.match(/`\d+`/))
                );
                
                if (entriesFieldIndex !== -1) {
                    fields[entriesFieldIndex].value = `\`${updatedGiveaway.participants.length}\``;
                    embed.setFields(fields);
                    await message.edit({ embeds: [embed] });
                }
            }
        }
    } catch (error) {
        console.error('Error updating embed:', error);
    }
    
    await interaction.editReply({
        content: '✅ **Kamu telah keluar dari giveaway.**'
    });
}

async function handleEndGiveaway(interaction) {
    await interaction.deferReply({ ephemeral: true });
    
    const giveawayId = interaction.options.getString('id');
    const giveaway = getGiveaway(giveawayId);
    
    if (!giveaway) {
        return interaction.editReply({
            content: '❌ **Giveaway tidak ditemukan!**\nPastikan ID giveaway benar.'
        });
    }
    
    if (giveaway.status !== 'active') {
        return interaction.editReply({
            content: `❌ **Giveaway sudah ${giveaway.status === 'ended' ? 'selesai' : 'dibatalkan'}!**`
        });
    }
    
    cancelGiveaway(giveawayId);
    
    const channel = interaction.guild.channels.cache.get(giveaway.channel_id);
    if (channel) {
        try {
            const message = await channel.messages.fetch(giveaway.message_id);
            const updatedEmbed = EmbedBuilder.from(message.embeds[0])
                .setColor(0xFF0000)
                .setFooter({ text: '❌ Giveaway dihentikan oleh host' });
            
            const disabledButton = new ButtonBuilder()
                .setCustomId('giveaway_cancelled')
                .setLabel('❌ Giveaway Dihentikan')
                .setStyle(ButtonStyle.Danger)
                .setDisabled(true);
            
            const row = new ActionRowBuilder().addComponents(disabledButton);
            await message.edit({ embeds: [updatedEmbed], components: [row] });
            
            await channel.send({
                content: `⏹️ **Giveaway telah dihentikan oleh <@${interaction.user.id}>**\n\nHadiah: ${giveaway.prize}\nID: \`${giveaway.id}\``
            });
            
        } catch (error) {
            console.error('Error updating giveaway:', error);
        }
    }
    
    await interaction.editReply({
        content: `✅ **Giveaway telah dihentikan!**\nHadiah: ${giveaway.prize}`
    });
}

async function handleRerollGiveaway(interaction) {
    await interaction.deferReply({ ephemeral: true });
    
    const giveawayId = interaction.options.getString('id');
    const giveaway = getGiveaway(giveawayId);
    
    if (!giveaway) {
        return interaction.editReply({
            content: '❌ **Giveaway tidak ditemukan!**\nPastikan ID giveaway benar.'
        });
    }
    
    if (giveaway.status !== 'ended') {
        return interaction.editReply({
            content: '❌ **Hanya giveaway yang sudah selesai yang bisa di-reroll!**'
        });
    }
    
    if (giveaway.participants.length === 0) {
        return interaction.editReply({
            content: '❌ **Tidak ada peserta untuk dipilih ulang!**'
        });
    }
    
    const newWinners = pickRandomWinners(giveaway.participants, giveaway.winners_count);
    setWinners(giveawayId, newWinners);
    
    const channel = interaction.guild.channels.cache.get(giveaway.channel_id);
    if (channel) {
        const winnerMentions = newWinners.length > 0 
            ? newWinners.map(id => `<@${id}>`).join(', ')
            : 'Tidak ada pemenang';
        
        await channel.send({
            content: `🔄 **PEMENANG DI-REROLL!**\n\n**Pemenang baru:** ${winnerMentions}\n\n**Giveaway:** ${giveaway.prize}\n**Di-reroll oleh:** <@${interaction.user.id}>\n**ID:** \`${giveaway.id}\``
        });
    }
    
    await interaction.editReply({
        content: `✅ **Pemenang berhasil dipilih ulang!**\n${newWinners.length} pemenang baru telah dipilih.`
    });
}

// ================= EXPORT SEMUA FUNGSI =================
module.exports = {
    // Database functions
    parseDuration,
    createGiveaway,
    getGiveaway,
    getGiveawayByMessage,
    addParticipant,
    removeParticipant,
    endGiveaway,
    cancelGiveaway,
    setWinners,
    pickRandomWinners,
    scheduleGiveawayEnd,
    
    // Handler functions
    showCreateModal,
    handleGiveawayModal,
    handleJoinGiveaway,
    handleLeaveGiveaway,
    handleEndGiveaway,
    handleRerollGiveaway
};