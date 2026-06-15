const {
    SlashCommandBuilder,
    ActionRowBuilder,
    StringSelectMenuBuilder,
    EmbedBuilder,
    PermissionFlagsBits
} = require('discord.js');

const config = require('../../config.json');

module.exports = {
    data: new SlashCommandBuilder()
        .setName('report')
        .setDescription('📋 Membuka panel official report Pahlawan Roleplay')
        .setDefaultMemberPermissions(PermissionFlagsBits.Administrator),

    async execute(interaction) {

        // =========================================
        // CHECK DEVELOPER ACCESS
        // =========================================
        if (
            !config.developerIds ||
            !config.developerIds.includes(interaction.user.id)
        ) {

            const deniedEmbed = new EmbedBuilder()

                .setColor('#ff0000')

                .setAuthor({
                    name: '❌ ACCESS DENIED',
                    iconURL: interaction.guild.iconURL({ dynamic: true })
                })

                .setTitle('⚔️ PAHLAWAN ROLEPLAY • SECURITY SYSTEM')

                .setDescription(
                    `🚫 **AKSES DITOLAK**

                    Kamu tidak memiliki izin untuk
                    menggunakan command ini.

                    ━━━━━━━━━━━━━━━━━━

                    🔒 Command ini hanya dapat digunakan
                    oleh **Developer Pahlawan Roleplay**.`
                )

                .setFooter({
                    text: '⚔️ Pahlawan Roleplay • Security System',
                    iconURL: interaction.guild.iconURL({ dynamic: true })
                })

                .setTimestamp();

            return interaction.reply({
                embeds: [deniedEmbed],
                ephemeral: true
            });
        }

        // =========================================
        // MAIN EMBED
        // =========================================
        const reportEmbed = new EmbedBuilder()

            .setColor('#FFD700')

            .setAuthor({
                name: '🛡️ PAHLAWAN ROLEPLAY • OFFICIAL REPORT SYSTEM',
                iconURL: interaction.guild.iconURL({ dynamic: true })
            })

            .setTitle('📋 PANEL REPORT RESMI')

            .setDescription(
                [
                '⚔️ Selamat datang di **Official Report System Pahlawan Roleplay**.',
                'Gunakan panel ini untuk melaporkan pelanggaran rules, bug server, atau tindakan yang merugikan pemain lain.',
                '',
                '━━━━━━━━━━━━━━━━━━',
                '',
                '👤 **REPORT PLAYER**',
                '> Laporkan player yang melanggar rules',
                '> seperti RK, PG, MG, Cheat, Exploit, Toxic, dan lainnya.',
                '',
                '💸 **REPORT RTM**',
                '> Laporkan aktivitas Real Money Trading',
                '> seperti jual beli uang, akun, kendaraan, atau item ilegal.',
                '',
                '🐞 **BUG REPORT**',
                '> Menemukan bug atau error pada server?',
                '> Sertakan bukti lengkap dan langkah reproduksi bug.',
                '',
                '🛡️ **REPORT ADMIN**',
                '> Laporkan admin yang abuse command,',
                '> tidak profesional, atau menyalahgunakan wewenang.',
                '',
                '━━━━━━━━━━━━━━━━━━',
                '',
                '⚠️ **PERATURAN REPORT**',
                '> • Dilarang membuat laporan palsu',
                '> • Dilarang spam report',
                '> • Dilarang memanipulasi bukti',
                '> • Semua laporan akan diperiksa Management',
                '',
                '━━━━━━━━━━━━━━━━━━',
                '',
                '📌 **FORMAT WAJIB REPORT**',
                '> 👤 Nama Pelapor',
                '> 🎯 Nama Terlapor',
                '> 📝 Kronologi Lengkap',
                '> 📷 Screenshot / Video Bukti',
                '> 🕒 Waktu Kejadian',
                '',
                '━━━━━━━━━━━━━━━━━━',
                '',
                '💡 Gunakan fitur report dengan bijak untuk menjaga kualitas roleplay dan kenyamanan seluruh warga **Pahlawan Roleplay**.'
                ].join('\n')
            )

            .setThumbnail(
                interaction.guild.iconURL({ dynamic: true })
            )

            .setFooter({
                text: `🛡️ Requested by ${interaction.user.username} • Pahlawan Roleplay`,
                iconURL: interaction.user.displayAvatarURL()
            })

            .setTimestamp();

        // =========================================
        // SELECT MENU
        // =========================================
        const reportMenu = new StringSelectMenuBuilder()

        .setCustomId('report_category_select')

        .setPlaceholder('📂 Pilih kategori laporan')

        .addOptions([

            {
                label: '👤 REPORT PLAYER',
                description: 'Laporkan player yang melanggar peraturan',
                value: 'report_player'
            },

            {
                label: '💸 REPORT RTM',
                description: 'Laporkan aktivitas Real Money Trading',
                value: 'report_rtm'
            },

            {
                label: '🐞 BUG REPORT',
                description: 'Laporkan bug, glitch, atau error server',
                value: 'report_bug'
            },

            {
                label: '🛡️ REPORT ADMIN',
                description: 'Laporkan penyalahgunaan wewenang admin',
                value: 'report_admin'
            }
        ]);

        const row = new ActionRowBuilder()
            .addComponents(reportMenu);

        // =========================================
        // SEND PANEL
        // =========================================
        await interaction.reply({
            embeds: [reportEmbed],
            components: [row]
        });

        // =========================================
        // SUCCESS MESSAGE
        // =========================================
        const successEmbed = new EmbedBuilder()

            .setColor('#00ff88')

            .setDescription(
                `✅ **SUCCESS**

                Panel report berhasil dikirim
                ke channel Pahlawan Roleplay.`
            );

        const msg = await interaction.followUp({
            embeds: [successEmbed],
            ephemeral: true
        });

        // =========================================
        // AUTO DELETE NOTIF
        // =========================================
        setTimeout(() => {
            msg.delete().catch(() => null);
        }, 3000);
    }
};