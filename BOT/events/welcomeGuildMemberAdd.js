const { EmbedBuilder } = require('discord.js');
const config = require('../config.json');

module.exports = {
    name: 'guildMemberAdd',

    async execute(member) {

        const channel = member.guild.channels.cache.get(config.channel.joinLog);

        if (!channel) {
            return console.log('❌ Channel welcome tidak ditemukan!');
        }

        setTimeout(async () => {

            try {

                //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//
                // ⚔️ Pahlawan ROLEPLAY STATS
                //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//

                const totalMembers =
                    member.guild.memberCount;

                const botCount =
                    member.guild.members.cache
                        .filter(m => m.user.bot).size;

                const humanCount =
                    totalMembers - botCount;

                const humanPercentage =
                    Math.round((humanCount / totalMembers) * 100);

                const botPercentage =
                    100 - humanPercentage;

                //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//
                // 🕒 ACCOUNT AGE
                //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//

                const accountAge =
                    Math.floor(
                        (Date.now() - member.user.createdTimestamp) /
                        (1000 * 60 * 60 * 24)
                    );

                //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//
                // 🎨 DYNAMIC COLOR
                //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//

                let embedColor = 0xFFD54F;

                if (accountAge < 7) {
                    embedColor = 0xE74C3C;
                }

                else if (accountAge < 30) {
                    embedColor = 0xF39C12;
                }

                else if (accountAge < 365) {
                    embedColor = 0x2ECC71;
                }

                else {
                    embedColor = 0xF1C40F;
                }

                //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//
                // 🛡️ SECURITY STATUS
                //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//

                let securityStatus = '✅ Akun Aman';

                if (accountAge < 7) {
                    securityStatus = '⚠️ Akun Sangat Baru';
                }

                else if (accountAge < 30) {
                    securityStatus = '🟡 Akun Baru';
                }

                //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//
                // ⚔️ Pahlawan WELCOME EMBED
                //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//

                const welcomeEmbed = new EmbedBuilder()

                    .setColor(embedColor)

                    .setAuthor({
                        name: `${member.guild.name} • Pahlawan Welcome`,
                        iconURL:
                            member.guild.iconURL({ dynamic: true })
                    })

                    .setTitle('⚔️ SELAMAT DATANG DI Pahlawan ROLEPLAY 🌴')

                    .setDescription(
                        [
                            `✨ Halo ${member.user}, selamat datang di kota paling cerah dan ramai di **Pahlawan Roleplay**!`,
                            ``,
                            `🚗 Nikmati pengalaman roleplay realistis, komunitas aktif, dan berbagai event seru setiap hari.`,
                            ``,
                            `🌴 Semoga betah dan selamat menikmati perjalanan roleplay kamu di Pahlawan City!`
                        ].join('\n')
                    )

                    .addFields(

                        {
                            name: '👤 INFORMASI WARGA',
                            value:
                                `> 🧑 Username: \`${member.user.tag}\`\n` +
                                `> 🆔 User ID: \`${member.id}\`\n` +
                                `> 🛡️ Status Akun: ${securityStatus}\n` +
                                `> 📅 Umur Akun: \`${accountAge} hari\``,
                            inline: false
                        },

                        {
                            name: '🕒 INFORMASI WAKTU',
                            value:
                                `> 📌 Akun Dibuat: <t:${Math.floor(member.user.createdTimestamp / 1000)}:F>\n` +
                                `> 🚪 Bergabung: <t:${Math.floor(Date.now() / 1000)}:R>`,
                            inline: false
                        },

                        {
                            name: '📊 STATISTIK Pahlawan CITY',
                            value:
                                `> 👥 Total Warga: \`${totalMembers.toLocaleString('id-ID')}\`\n` +
                                `> 🧑 Member: \`${humanCount.toLocaleString('id-ID')}\` (${humanPercentage}%)\n` +
                                `> 🤖 Bot: \`${botCount.toLocaleString('id-ID')}\` (${botPercentage}%)\n` +
                                `> 🌟 Member Ke: \`#${totalMembers.toLocaleString('id-ID')}\``,
                            inline: false
                        },

                        {
                            name: '✅ LANGKAH SELANJUTNYA',
                            value:
                                `> 📌 Silakan lakukan verifikasi terlebih dahulu.\n` +
                                `> 🔐 <#1068569235976093827>\n\n` +
                                `> 📖 Setelah verifikasi, baca seluruh rules server.`,
                            inline: false
                        },

                        {
                            name: '📜 RULES SERVER',
                            value:
                                `> 📘 <#835820688718823454>\n` +
                                `> 📘 <#772429756180070412>\n` +
                                `> 📘 <#835831372756549642>\n` +
                                `> 📘 <#854676382213865472>`,
                            inline: false
                        }
                    )

                    .setThumbnail(
                        member.user.displayAvatarURL({
                            dynamic: true,
                            size: 512
                        })
                    )

                    .setImage(
                        'https://media.discordapp.net/attachments/1513604476865609788/1513604622797770933/logo3.png?ex=6a2855a7&is=6a270427&hm=5902561759e780738de44026e4da8955a8ac2f7ebf3281c376fc192a688366e9&=&format=webp&quality=lossless&width=869&height=856'
                    )

                    .setFooter({
                        text: '⚔️ Pahlawan Roleplay • Welcome System',
                        iconURL:
                            member.guild.iconURL({ dynamic: true })
                    })

                    .setTimestamp();

                //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//
                // 🚀 SEND MESSAGE
                //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//

                const msg = await channel.send({

                    content:
                        `🌴 WELCOME TO Pahlawan CITY ${member.user} ⚔️`,

                    embeds: [welcomeEmbed]
                });

                //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//
                // ❤️ REACTION
                //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//

                const reacts = ['⚔️', '🛡️', '❤️'];

                for (const react of reacts) {
                    await msg.react(react).catch(() => {});
                }

                console.log(
                    `✅ ${member.user.tag} berhasil masuk Pahlawan Roleplay`
                );

            } catch (error) {

                console.error(
                    '❌ Error Pahlawan Welcome System:',
                    error
                );

            }

        }, 1500);
    }
};