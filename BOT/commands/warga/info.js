const { SlashCommandBuilder, EmbedBuilder } = require('discord.js');
const { pool, getPool } = require('../../PHRP-AI/utils/database');

module.exports = {
    data: new SlashCommandBuilder()
        .setName('info')
        .setDescription('Cari informasi player berdasarkan username UCP')
        .addStringOption(option =>
            option.setName('username')
                .setDescription('Username UCP player')
                .setRequired(true)
        ),
    async execute(interaction) {
        const username = interaction.options.getString('username');
        await interaction.deferReply();

        try {
            const db = getPool ? getPool() : pool;
            if (!db) {
                return interaction.editReply('❌ Database tidak tersedia.');
            }

            // Query player_ucp
            const [ucpRows] = await db.query(
                'SELECT ID, UCP, Verify_Status, admin_level, vip_status, vip_time, gold, Register_Date, Last_Login, discord_id FROM player_ucp WHERE UCP = ? LIMIT 1',
                [username]
            );

            if (ucpRows.length === 0) {
                return interaction.editReply(`❌ Player **${username}** tidak ditemukan di database.`);
            }

            const ucp = ucpRows[0];

            // Query player_characters
            const [charRows] = await db.query(
                'SELECT Char_Name, Char_Level, Char_Faction, Char_Skin FROM player_characters WHERE Char_UCP = ?',
                [username]
            );

            // Build embed
            const embed = new EmbedBuilder()
                .setTitle(`📋 Player Info — ${ucp.UCP}`)
                .setColor(ucp.admin_level > 0 ? '#FF0000' : '#00FF00')
                .addFields(
                    {
                        name: '🆔 UCP ID',
                        value: String(ucp.ID),
                        inline: true
                    },
                    {
                        name: '✅ Verified',
                        value: ucp.Verify_Status === 1 ? '✅ Yes' : '❌ No',
                        inline: true
                    },
                    {
                        name: '👑 Admin Level',
                        value: ucp.admin_level > 0 ? `Level ${ucp.admin_level}` : 'Pemain Biasa',
                        inline: true
                    },
                    {
                        name: '💎 VIP',
                        value: ucp.vip_status && ucp.vip_status !== 'NONE' ? `${ucp.vip_status} (${ucp.vip_time}s)` : 'None',
                        inline: true
                    },
                    {
                        name: '🪙 Gold',
                        value: `${ucp.gold || 0} GC`,
                        inline: true
                    },
                    {
                        name: '🔗 Discord',
                        value: ucp.discord_id ? '✅ Linked' : '❌ Not Linked',
                        inline: true
                    },
                    {
                        name: '📅 Registered',
                        value: ucp.Register_Date ? String(ucp.Register_Date).substring(0, 19) : 'N/A',
                        inline: true
                    },
                    {
                        name: '🕐 Last Login',
                        value: ucp.Last_Login ? String(ucp.Last_Login).substring(0, 19) : 'N/A',
                        inline: true
                    },
                    {
                        name: `🎭 Characters (${charRows.length})`,
                        value: charRows.length > 0
                            ? charRows.map(c => `• ${c.Char_Name} (Lv.${c.Char_Level})`).join('\n')
                            : 'Belum ada karakter',
                        inline: false
                    }
                )
                .setFooter({ text: 'PAHLAWAN ROLEPLAY — Cross-Service Auth' })
                .setTimestamp();

            return interaction.editReply({ embeds: [embed] });

        } catch (error) {
            console.error('[/info] Error:', error);
            return interaction.editReply('❌ Terjadi kesalahan saat query database.');
        }
    },
};
