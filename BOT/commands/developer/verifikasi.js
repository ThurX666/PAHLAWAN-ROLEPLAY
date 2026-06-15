const {
    SlashCommandBuilder,
    EmbedBuilder,
    ActionRowBuilder,
    ButtonBuilder,
    ButtonStyle
} = require('discord.js');

const config = require('../../config.json');

module.exports = {
    data: new SlashCommandBuilder()
        .setName('setup')
        .setDescription('Setup commands')
        .addSubcommand(subcommand =>
            subcommand
                .setName('verifikasi')
                .setDescription('Setup sistem verifikasi')
        ),

    async execute(interaction) {

        // Validasi developer
        if (
            !config.developerIds ||
            !Array.isArray(config.developerIds) ||
            !config.developerIds.includes(interaction.user.id)
        ) {
            return interaction.reply({
                content: '❌ Kamu tidak memiliki izin untuk menggunakan command ini!',
                ephemeral: true
            });
        }

        const subcommand = interaction.options.getSubcommand();

        if (subcommand === 'verifikasi') {

           const embed = new EmbedBuilder()
            .setColor('#00BFFF')

            .setAuthor({
                name: '⚔️ PAHLAWAN ROLEPLAY • VERIFICATION SYSTEM',
                iconURL: interaction.guild.iconURL({ dynamic: true })
            })

            .setTitle('✅ SISTEM VERIFIKASI RESMI')

            .setDescription(
                [
                    '⚔️ Selamat datang di **Pahlawan Roleplay**',
                    '',
                    'Untuk mendapatkan akses penuh ke seluruh channel dan fitur server, silakan selesaikan proses verifikasi terlebih dahulu.',
                    '',
                    '━━━━━━━━━━━━━━━━━━',
                    '',
                    '📋 **LANGKAH VERIFIKASI**',
                    '',
                    '1️⃣ Klik tombol **Ambil Kode**',
                    '2️⃣ Bot akan mengirim kode verifikasi ke DM kamu',
                    '3️⃣ Klik tombol **Masukkan Kode**',
                    '4️⃣ Masukkan kode yang diterima',
                    '5️⃣ Role member akan diberikan secara otomatis',
                    '',
                    '━━━━━━━━━━━━━━━━━━',
                    '',
                    '⚠️ **INFORMASI PENTING**',
                    '',
                    '• Kode berlaku selama **5 menit**',
                    '• Kode hanya dapat digunakan **1 kali**',
                    '• Jika kode salah atau kedaluwarsa, ambil kode baru',
                    '• Pastikan DM Discord kamu terbuka',
                    '• Member yang sudah terverifikasi tidak dapat verifikasi ulang',
                    '• Hubungi Staff apabila mengalami kendala',
                    '',
                    '━━━━━━━━━━━━━━━━━━',
                    '',
                    '🛡️ Sistem ini dibuat untuk menjaga keamanan dan kenyamanan seluruh warga Pahlawan Roleplay.'
                ].join('\n')
            )

            .setThumbnail(
                interaction.guild.iconURL({ dynamic: true })
            )

            .setFooter({
                text: '⚔️ Pahlawan Roleplay • Official Verification System',
                iconURL: interaction.guild.iconURL({ dynamic: true })
            })

            .setTimestamp();

            const row = new ActionRowBuilder()
                .addComponents(
                    new ButtonBuilder()
                        .setCustomId('verif_ambil_kode')
                        .setLabel('Ambil Kode')
                        .setEmoji('🔑')
                        .setStyle(ButtonStyle.Primary),

                    new ButtonBuilder()
                        .setCustomId('verif_masukkan_kode')
                        .setLabel('Masukkan Kode')
                        .setEmoji('⌨️')
                        .setStyle(ButtonStyle.Success)
                );

            await interaction.reply({
                embeds: [embed],
                components: [row]
            });
        }
    }
};