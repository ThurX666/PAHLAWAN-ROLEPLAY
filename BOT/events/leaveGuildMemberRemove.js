const { EmbedBuilder } = require('discord.js');

const config = require('../config.json');

module.exports = {
    name: 'guildMemberRemove',

    /**
     * @param {import('discord.js').GuildMember} member
     */

    async execute(member) {

        try {

            //━━━━━━━━━━━━━━━━━━━━━━━━━━//
            // GET CHANNEL
            //━━━━━━━━━━━━━━━━━━━━━━━━━━//

            const channel =
                member.guild.channels.cache.get(
                    config.channel.leaveLog
                );

            if (!channel) return;

            // Delay agar data stabil
            setTimeout(async () => {

                //━━━━━━━━━━━━━━━━━━━━━━━━━━//
                // ⏳ FORMAT DURASI
                //━━━━━━━━━━━━━━━━━━━━━━━━━━//

                const formatDuration = (ms) => {

                    const days =
                        Math.floor(
                            ms / (1000 * 60 * 60 * 24)
                        );

                    const hours =
                        Math.floor(
                            (ms / (1000 * 60 * 60)) % 24
                        );

                    const minutes =
                        Math.floor(
                            (ms / (1000 * 60)) % 60
                        );

                    const parts = [];

                    if (days)
                        parts.push(`${days} hari`);

                    if (hours)
                        parts.push(`${hours} jam`);

                    if (minutes)
                        parts.push(`${minutes} menit`);

                    return parts.length
                        ? parts.join(' ')
                        : 'Baru bergabung';
                };

                //━━━━━━━━━━━━━━━━━━━━━━━━━━//
                // 📋 MEMBER DATA
                //━━━━━━━━━━━━━━━━━━━━━━━━━━//

                const joinTimestamp =
                    member.joinedTimestamp;

                const now = Date.now();

                const stayDuration =
                    joinTimestamp
                        ? formatDuration(
                              now - joinTimestamp
                          )
                        : 'Tidak diketahui';

                const accountAgeDays =
                    Math.floor(
                        (
                            now -
                            member.user.createdTimestamp
                        ) /
                            (
                                1000 *
                                60 *
                                60 *
                                24
                            )
                    );

                //━━━━━━━━━━━━━━━━━━━━━━━━━━//
                // 📊 SERVER STATS
                //━━━━━━━━━━━━━━━━━━━━━━━━━━//

                const totalMembers =
                    member.guild.memberCount;

                const botCount =
                    member.guild.members.cache.filter(
                        m => m.user.bot
                    ).size;

                const humanCount =
                    totalMembers - botCount;

                //━━━━━━━━━━━━━━━━━━━━━━━━━━//
                // 🎨 DYNAMIC COLOR
                //━━━━━━━━━━━━━━━━━━━━━━━━━━//

                let embedColor = 0xED4245;

                if (joinTimestamp) {

                    const joinedDays =
                        Math.floor(
                            (
                                now -
                                joinTimestamp
                            ) /
                                (
                                    1000 *
                                    60 *
                                    60 *
                                    24
                                )
                        );

                    if (joinedDays >= 30)
                        embedColor = 0xFAA61A;

                    if (joinedDays >= 180)
                        embedColor = 0x57F287;
                }

                //━━━━━━━━━━━━━━━━━━━━━━━━━━//
                // 🌴 MAIN EMBED
                //━━━━━━━━━━━━━━━━━━━━━━━━━━//

                const embed = new EmbedBuilder()

                    .setColor(embedColor)

                    .setAuthor({
                        name:
                            'Pahlawan ROLEPLAY • LEAVE LOG',
                        iconURL:
                            member.guild.iconURL({
                                dynamic: true
                            })
                    })

                    .setTitle('👋 WARGA MENINGGALKAN KOTA')

                    .setDescription(
                        [
                            `✨ Selamat tinggal ${member.user}`,
                            '',
                            '> Terima kasih telah menjadi bagian dari Pahlawan Roleplay 🌴',
                            '',
                            '━━━━━━━━━━━━━━━━━━',
                            '',
                            '## 👤 INFORMASI PLAYER',
                            `> 👑 Username : \`${member.user.username}\``,
                            `> 🆔 User ID : \`${member.id}\``,
                            `> 📅 Bergabung : ${
                                joinTimestamp
                                    ? `<t:${Math.floor(joinTimestamp / 1000)}:F>`
                                    : '`Tidak diketahui`'
                            }`,
                            `> ⏳ Durasi : \`${stayDuration}\``,
                            `> 🚪 Keluar : <t:${Math.floor(now / 1000)}:R>`,
                            '',
                            '━━━━━━━━━━━━━━━━━━',
                            '',
                            '## 🔐 INFORMASI AKUN',
                            `> 📆 Akun Dibuat : <t:${Math.floor(member.user.createdTimestamp / 1000)}:F>`,
                            `> 📈 Umur Akun : \`${accountAgeDays} Hari\``,
                            '',
                            '━━━━━━━━━━━━━━━━━━',
                            '',
                            '## 📊 STATISTIK SERVER',
                            `> 👥 Total Member : \`${totalMembers.toLocaleString('id-ID')}\``,
                            `> 🧑 Player : \`${humanCount.toLocaleString('id-ID')}\``,
                            `> 🤖 Bot : \`${botCount.toLocaleString('id-ID')}\``
                        ].join('\n')
                    )

                    .setThumbnail(
                        member.user.displayAvatarURL({
                            dynamic: true,
                            size: 512
                        })
                    )

                    .setImage(
                        member.guild.bannerURL({
                            size: 1024
                        }) ||
                            'https://media.discordapp.net/attachments/1513604476865609788/1513604622797770933/logo3.png?ex=6a2855a7&is=6a270427&hm=5902561759e780738de44026e4da8955a8ac2f7ebf3281c376fc192a688366e9&=&format=webp&quality=lossless&width=869&height=856'
                    )

                    .setFooter({
                        text:
                            'Pahlawan ROLEPLAY • COMMUNITY SYSTEM',
                        iconURL:
                            member.guild.iconURL({
                                dynamic: true
                            })
                    })

                    .setTimestamp();

                //━━━━━━━━━━━━━━━━━━━━━━━━━━//
                // 📨 SEND MESSAGE
                //━━━━━━━━━━━━━━━━━━━━━━━━━━//

                const message =
                    await channel.send({
                        content:
                            '🌴 Pahlawan Roleplay Member Leave',
                        embeds: [embed]
                    });

                //━━━━━━━━━━━━━━━━━━━━━━━━━━//
                // ❤️ REACTION
                //━━━━━━━━━━━━━━━━━━━━━━━━━━//

                await message.react('👋');
                await message.react('⚔️');

                console.log(
                    `👋 ${member.user.tag} keluar dari Pahlawan Roleplay`
                );

            }, 1500);

        } catch (error) {

            console.error(
                '[Pahlawan LEAVE LOG ERROR]',
                error
            );
        }
    }
};