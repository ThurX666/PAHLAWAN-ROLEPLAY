const { EmbedBuilder } = require('discord.js');

const config = require('../config.json');

module.exports = {
    name: 'guildMemberUpdate',
    once: false,

    async execute(oldMember, newMember) {

        try {

            //━━━━━━━━━━━━━━━━━━━━━━━━━━//
            // ⚔️ CHECK BOOSTER BARU
            //━━━━━━━━━━━━━━━━━━━━━━━━━━//

            const isNewBooster =
                !oldMember.premiumSince &&
                newMember.premiumSince;

            if (!isNewBooster) return;

            //━━━━━━━━━━━━━━━━━━━━━━━━━━//
            // 📂 AMBIL CHANNEL BOOST
            //━━━━━━━━━━━━━━━━━━━━━━━━━━//

            const boostChannel =
                newMember.guild.channels.cache.get(
                    config.channel.boost
                );

            if (!boostChannel) {

                return console.log(
                    '❌ Channel boost tidak ditemukan!'
                );
            }

            //━━━━━━━━━━━━━━━━━━━━━━━━━━//
            // 📊 DATA BOOST SERVER
            //━━━━━━━━━━━━━━━━━━━━━━━━━━//

            const totalBoost =
                newMember.guild.premiumSubscriptionCount || 0;

            const boostLevel =
                newMember.guild.premiumTier;

            //━━━━━━━━━━━━━━━━━━━━━━━━━━//
            // 🎨 EMBED BOOST
            //━━━━━━━━━━━━━━━━━━━━━━━━━━//

            const boostEmbed = new EmbedBuilder()

                .setColor('#FDB813')

                .setAuthor({
                    name:
                        '⚔️ Pahlawan ROLEPLAY • BOOSTER SYSTEM',
                    iconURL:
                        newMember.guild.iconURL({
                            dynamic: true
                        })
                })

                .setTitle('🚀 SERVER BOOST BARU MASUK!')

                .setThumbnail(
                    newMember.user.displayAvatarURL({
                        dynamic: true,
                        size: 1024
                    })
                )

                .setDescription(
                    [
                        `✨ Terima kasih ${newMember.user} telah melakukan **Server Boost** untuk Pahlawan Roleplay!`,
                        '',
                        '💎 Booster eksklusif berhasil aktif',
                        '🎁 Mendapatkan akses & benefit spesial booster',
                        '🔥 Support kamu membantu server terus berkembang',
                        '',
                        '━━━━━━━━━━━━━━━━━━',
                        '',
                        '🌴 Nikmati pengalaman roleplay terbaik bersama komunitas Pahlawan ⚔️'
                    ].join('\n')
                )

                .addFields(

                    {
                        name: '🚀 Total Boost',
                        value: `\`${totalBoost} Boost\``,
                        inline: true
                    },

                    {
                        name: '⭐ Boost Level',
                        value: `\`Level ${boostLevel}\``,
                        inline: true
                    },

                    {
                        name: '👤 Booster',
                        value: `${newMember.user}`,
                        inline: true
                    }
                )

                .setImage(
                    'https://media.discordapp.net/attachments/1513604476865609788/1513604622797770933/logo3.png?ex=6a2855a7&is=6a270427&hm=5902561759e780738de44026e4da8955a8ac2f7ebf3281c376fc192a688366e9&=&format=webp&quality=lossless&width=869&height=856'
                )

                .setFooter({
                    text:
                        'Pahlawan ROLEPLAY • THANK YOU BOOSTER ⚔️',
                    iconURL:
                        newMember.guild.iconURL({
                            dynamic: true
                        })
                })

                .setTimestamp();

            //━━━━━━━━━━━━━━━━━━━━━━━━━━//
            // 📨 SEND MESSAGE
            //━━━━━━━━━━━━━━━━━━━━━━━━━━//

            await boostChannel.send({

                content:
                    `🎉 WELCOME BOOSTER ${newMember.user} ⚔️`,

                embeds: [boostEmbed]
            });

            console.log(
                `✅ ${newMember.user.tag} berhasil boost Pahlawan Roleplay.`
            );

        } catch (error) {

            console.error(
                '❌ Error pada booster system:',
                error
            );
        }
    }
};