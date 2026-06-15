const { EmbedBuilder, ActionRowBuilder, ButtonBuilder, ButtonStyle } = require('discord.js');
const giveawayData = require('./giveawayData');

// Schedule timer untuk giveaway
function scheduleGiveawayEnd(client, giveawayId, durationMs, guildId) {
    console.log(`⏰ [SCHEDULE] Setting timer for giveaway ${giveawayId}`);
    
    setTimeout(async () => {
        console.log(`⏰ [TIMER] Timer fired for giveaway: ${giveawayId}`);
        
        const giveaway = giveawayData.getGiveaway(giveawayId);
        if (!giveaway || giveaway.status !== 'active') {
            console.log(`⏰ [TIMER] Giveaway tidak aktif atau tidak ditemukan`);
            return;
        }
        
        console.log(`⏰ [TIMER] Picking winners...`);
        const winners = giveawayData.pickRandomWinners(giveaway.participants, giveaway.winners_count);
        
        // Update database
        giveawayData.setWinners(giveawayId, winners);
        
        try {
            const guild = client.guilds.cache.get(guildId || giveaway.guild_id);
            const channel = guild?.channels.cache.get(giveaway.channel_id);
            
            if (!guild || !channel) {
                console.error(`⏰ [TIMER] Guild/Channel not found`);
                return;
            }
            
            const message = await channel.messages.fetch(giveaway.message_id).catch(() => null);
            if (!message) {
                console.error(`⏰ [TIMER] Message not found`);
                return;
            }
            
            // ========== UPDATE EMBED UTAMA ==========
            const originalEmbed = message.embeds[0];
            const updatedEmbed = EmbedBuilder.from(originalEmbed)
                .setColor(0x00FF00) // Ubah warna jadi hijau
                .setFooter({ text: '✅ Giveaway telah berakhir' })
                .setTimestamp(); // Update timestamp ke sekarang
            
            // Update field "Berakhir" untuk menunjukkan sudah selesai
            const fields = updatedEmbed.data.fields || [];
            const timeFieldIndex = fields.findIndex(f => f.name === 'Berakhir');
            
            if (timeFieldIndex !== -1) {
                const now = Math.floor(Date.now() / 1000);
                fields[timeFieldIndex].value = `Berakhir <t:${now}:R>`;
                updatedEmbed.setFields(fields);
            }
            
            // ========== DISABLE TOMBOL ==========
            const disabledButton = new ButtonBuilder()
                .setCustomId('giveaway_ended')
                .setLabel('✅ Giveaway Selesai')
                .setStyle(ButtonStyle.Secondary)
                .setDisabled(true);
            
            const disabledRow = new ActionRowBuilder().addComponents(disabledButton);
            
            // Update message
            await message.edit({ 
                embeds: [updatedEmbed], 
                components: [disabledRow] 
            });
            
            console.log(`✅ [TIMER] Updated main giveaway embed`);
            
            // ========== KIRIM PESAN PEMENANG ==========
            if (winners.length > 0) {
                const winnerMentions = winners.map(id => `<@${id}>`).join(', ');
                
                // Kirim pesan pemenang di channel yang sama
                await channel.send({
                    content: `🎉 **GIVEAWAY BERAKHIR** 🎉\n\n**Selamat kepada:**\n${winnerMentions}\n\nKamu memenangkan **${giveaway.prize}**!`
                });
            } else {
                await channel.send({
                    content: `🎉 **GIVEAWAY BERAKHIR** 🎉\n\n**Tidak ada pemenang** (tidak ada peserta yang mengikuti)`
                });
            }
            
            console.log(`✅ [TIMER] Giveaway ${giveawayId} ended successfully`);
            
        } catch (error) {
            console.error('⏰ [TIMER] Error ending giveaway:', error);
        }
    }, durationMs);
}

// Handle expired giveaways saat bot restart
async function checkExpiredGiveaways(client) {
    console.log('🔄 Checking for expired giveaways...');
    const activeGiveaways = giveawayData.getAllActiveGiveaways();
    
    for (const giveaway of activeGiveaways) {
        const endsAt = new Date(giveaway.ends_at).getTime();
        const now = Date.now();
        
        if (endsAt <= now) {
            console.log(`⏰ Giveaway ${giveaway.id} has expired, ending now...`);
            
            const winners = giveawayData.pickRandomWinners(giveaway.participants, giveaway.winners_count);
            giveawayData.setWinners(giveaway.id, winners);
            
            try {
                const guild = client.guilds.cache.get(giveaway.guild_id);
                const channel = guild?.channels.cache.get(giveaway.channel_id);
                
                if (guild && channel) {
                    const message = await channel.messages.fetch(giveaway.message_id).catch(() => null);
                    
                    if (message) {
                        // Update embed
                        const updatedEmbed = EmbedBuilder.from(message.embeds[0])
                            .setColor(0x00FF00)
                            .setFooter({ text: '✅ Giveaway telah berakhir' })
                            .setTimestamp();
                        
                        // Disable tombol
                        const disabledButton = new ButtonBuilder()
                            .setCustomId('giveaway_ended')
                            .setLabel('✅ Giveaway Selesai')
                            .setStyle(ButtonStyle.Secondary)
                            .setDisabled(true);
                        
                        const disabledRow = new ActionRowBuilder().addComponents(disabledButton);
                        
                        await message.edit({ 
                            embeds: [updatedEmbed], 
                            components: [disabledRow] 
                        });
                        
                        // Kirim pesan pemenang
                        if (winners.length > 0) {
                            const winnerMentions = winners.map(id => `<@${id}>`).join(', ');
                            await channel.send({
                                content: `🎉 **GIVEAWAY BERAKHIR** 🎉\n\n**Selamat kepada:**\n${winnerMentions}\n\nKamu memenangkan **${giveaway.prize}**!`
                            });
                        }
                    }
                }
                
                console.log(`✅ Ended expired giveaway: ${giveaway.id}`);
            } catch (error) {
                console.error(`Error ending expired giveaway ${giveaway.id}:`, error);
            }
        }
    }
}

module.exports = {
    scheduleGiveawayEnd,
    checkExpiredGiveaways
};