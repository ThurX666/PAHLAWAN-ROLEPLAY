/**
 * DISCORD SERVER VERIFICATION — Role Gate (Captcha)
 * ===================================================
 * Flow ini MEMBERIKAN ROLE DISCORD setelah user memasukkan kode captcha.
 * Ini BUKAN Discord Account Link ke UCP.
 *
 * Untuk linking UCP ↔ Discord (menulis player_ucp.discord_id),
 * lihat: WEBSITE/public/api/discord_callback.php
 *
 * Dependency: ../../utils/verificationGaptcha.js (generate/save/validate kode)
 * Output:     Tambah role verified, hapus role unverified, log verifikasi.
 * DB:         Tidak menyentuh player_ucp.
 */
const {
    EmbedBuilder,
    ModalBuilder,
    TextInputBuilder,
    TextInputStyle,
    ActionRowBuilder
} = require('discord.js');

const config = require('../../config.json');

const {
    generateVerificationCode,
    saveVerificationCode,
    deleteVerificationCode,
    isValidCode
} = require('../../utils/verificationGaptcha.js');

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//
// ⚔️ FORMAT WAKTU INDONESIA
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//

function formatTanggal() {

    const now = new Date();

    const hari = [
        'Minggu',
        'Senin',
        'Selasa',
        'Rabu',
        'Kamis',
        'Jumat',
        'Sabtu'
    ];

    const bulan = [
        'Januari',
        'Februari',
        'Maret',
        'April',
        'Mei',
        'Juni',
        'Juli',
        'Agustus',
        'September',
        'Oktober',
        'November',
        'Desember'
    ];

    return `${hari[now.getDay()]}, ${now.getDate()} ${bulan[now.getMonth()]} ${now.getFullYear()} • ${now.getHours().toString().padStart(2, '0')}:${now.getMinutes().toString().padStart(2, '0')}:${now.getSeconds().toString().padStart(2, '0')} WIB`;
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//
// 📝 LOG VERIFIKASI
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//

async function logVerification(interaction, code, status) {

    try {

        const logChannelId = config.channel?.verifikasiLog;

        if (!logChannelId) return;

        const logChannel =
            interaction.guild.channels.cache.get(logChannelId);

        if (!logChannel) return;

        let statusText = '❌ GAGAL';
        let color = 0xED4245;

        if (status === 'success') {

            statusText = '✅ BERHASIL';
            color = 0x57F287;

        } else if (status === 'wrong_code') {

            statusText = '❌ KODE SALAH';
            color = 0xFAA61A;
        }

        const embed = new EmbedBuilder()

            .setColor(color)

            .setAuthor({
                name: '⚔️ Pahlawan ROLEPLAY • VERIFICATION LOG',
                iconURL:
                    interaction.guild.iconURL({ dynamic: true })
            })

            .setTitle('📋 LOG VERIFIKASI PLAYER')

            .addFields(

                {
                    name: '👤 Player',
                    value: `${interaction.user}`,
                    inline: true
                },

                {
                    name: '🆔 User ID',
                    value: `\`${interaction.user.id}\``,
                    inline: true
                },

                {
                    name: '📊 Status',
                    value: statusText,
                    inline: true
                },

                {
                    name: '🔑 Kode',
                    value: `\`${code}\``,
                    inline: false
                },

                {
                    name: '📅 Waktu',
                    value: formatTanggal(),
                    inline: false
                }
            )

            .setThumbnail(
                interaction.user.displayAvatarURL({
                    dynamic: true
                })
            )

            .setFooter({
                text: 'Pahlawan ROLEPLAY • SECURITY SYSTEM'
            })

            .setTimestamp();

        await logChannel.send({
            embeds: [embed]
        });

    } catch (error) {

        console.error(
            '❌ Error logging verification:',
            error
        );
    }
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//
// 🔑 AMBIL KODE
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//

async function handleAmbilKode(interaction) {

    const memberRole =
        interaction.guild.roles.cache.get(config.role.member);

    if (
        memberRole &&
        interaction.member.roles.cache.has(memberRole.id)
    ) {

        return interaction.reply({

            content:
                '❌ Kamu sudah terverifikasi dan memiliki akses server.',

            flags: 64
        });
    }

    const userId = interaction.user.id;

    const code = generateVerificationCode();

    const { expires } =
        saveVerificationCode(userId, code, 5);

    try {

        const dmEmbed = new EmbedBuilder()

            .setColor(0xFDCB58)

            .setAuthor({
                name: '⚔️ Pahlawan ROLEPLAY'
            })

            .setTitle('🔑 KODE VERIFIKASI SERVER')

            .setDescription(
                [
                    'Halo warga Pahlawan 👋',
                    '',
                    'Gunakan kode berikut untuk menyelesaikan verifikasi server.',
                    '',
                    `## \`${code}\``,
                    '',
                    '━━━━━━━━━━━━━━━━━━',
                    '',
                    '### 📌 Cara Verifikasi',
                    '> 1. Kembali ke server',
                    '> 2. Klik tombol **Masukkan Kode**',
                    '> 3. Input kode di atas',
                    '',
                    '### ⚠️ Informasi Penting',
                    `> • Kode berlaku <t:${Math.floor(expires / 1000)}:R>`,
                    '> • Kode hanya dapat digunakan 1x',
                    '> • Jangan bagikan kode ini ke siapa pun',
                    '',
                    '━━━━━━━━━━━━━━━━━━',
                    '',
                    '✨ Selamat bermain di Pahlawan Roleplay!'
                ].join('\n')
            )

            .setThumbnail(
                interaction.guild.iconURL({ dynamic: true })
            )

            .setFooter({
                text: 'Pahlawan ROLEPLAY • VERIFICATION SYSTEM'
            })

            .setTimestamp();

        await interaction.user.send({
            embeds: [dmEmbed]
        });

        const successEmbed = new EmbedBuilder()

            .setColor(0x57F287)

            .setDescription(
                [
                    '## ✅ KODE BERHASIL DIKIRIM',
                    '',
                    '> Silakan cek DM kamu untuk melihat kode verifikasi.'
                ].join('\n')
            );

        await interaction.reply({
            embeds: [successEmbed],
            flags: 64
        });

    } catch (error) {

        const errorEmbed = new EmbedBuilder()

            .setColor(0xED4245)

            .setDescription(
                [
                    '## ❌ GAGAL MENGIRIM DM',
                    '',
                    '> Pastikan DM kamu terbuka lalu coba lagi.'
                ].join('\n')
            );

        await interaction.reply({
            embeds: [errorEmbed],
            flags: 64
        });
    }
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//
// ⌨️ SHOW MODAL INPUT KODE
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//

async function handleMasukkanKode(interaction) {

    const memberRole =
        interaction.guild.roles.cache.get(config.role.member);

    if (
        memberRole &&
        interaction.member.roles.cache.has(memberRole.id)
    ) {

        return interaction.reply({

            content:
                '❌ Kamu sudah terverifikasi dan memiliki akses server.',

            flags: 64
        });
    }

    const modal = new ModalBuilder()

        .setCustomId('verif_modal_input')

        .setTitle('⚔️ Verifikasi Pahlawan');

    const codeInput = new TextInputBuilder()

        .setCustomId('verif_kode_input')

        .setLabel('🔑 Masukkan Kode Verifikasi')

        .setPlaceholder('Contoh: A1B2C3')

        .setStyle(TextInputStyle.Short)

        .setMinLength(6)

        .setMaxLength(6)

        .setRequired(true);

    modal.addComponents(
        new ActionRowBuilder().addComponents(codeInput)
    );

    await interaction.showModal(modal);
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//
// ✅ HANDLE SUBMIT VERIFIKASI
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//

async function handleVerifikasiModal(interaction) {

    if (interaction.customId !== 'verif_modal_input')
        return;

    const userId = interaction.user.id;

    const inputCode =
        interaction.fields
            .getTextInputValue('verif_kode_input')
            .toUpperCase();

    const valid =
        isValidCode(userId, inputCode);

    await logVerification(
        interaction,
        inputCode,
        valid ? 'success' : 'wrong_code'
    );

    if (!valid) {

        deleteVerificationCode(userId);

        const wrongEmbed = new EmbedBuilder()

            .setColor(0xED4245)

            .setTitle('❌ VERIFIKASI GAGAL')

            .setDescription(
                [
                    '> Kode salah atau sudah expired.',
                    '',
                    '> Klik tombol **Ambil Kode** untuk mendapatkan kode baru.'
                ].join('\n')
            )

            .setFooter({
                text: 'Pahlawan ROLEPLAY • SECURITY'
            });

        return interaction.reply({
            embeds: [wrongEmbed],
            flags: 64
        });
    }

    try {

        deleteVerificationCode(userId);

        const memberRole =
            interaction.guild.roles.cache.get(
                config.role.member
            );

        if (!memberRole)
            throw new Error('Role member tidak ditemukan.');

        await interaction.member.roles.add(memberRole);

        const successEmbed = new EmbedBuilder()

            .setColor(0x57F287)

            .setAuthor({
                name: '⚔️ Pahlawan ROLEPLAY'
            })

            .setTitle('🎉 VERIFIKASI BERHASIL')

            .setDescription(
                [
                    `Selamat ${interaction.user} 👋`,
                    '',
                    '> Kamu berhasil menyelesaikan verifikasi server.',
                    `> Role **${memberRole.name}** telah diberikan.`,
                    '',
                    '✨ Selamat bermain & nikmati pengalaman roleplay terbaik di Pahlawan Roleplay.'
                ].join('\n')
            )

            .setThumbnail(
                interaction.user.displayAvatarURL({
                    dynamic: true
                })
            )

            .setFooter({
                text: 'WELCOME TO Pahlawan ROLEPLAY'
            })

            .setTimestamp();

        await interaction.reply({
            embeds: [successEmbed],
            flags: 64
        });

        //━━━━━━━━━━━━━━━━━━//
        // 📩 DM SUCCESS
        //━━━━━━━━━━━━━━━━━━//

        try {

            const dmSuccess = new EmbedBuilder()

                .setColor(0x57F287)

                .setTitle('⚔️ Welcome To Pahlawan Roleplay')

                .setDescription(
                    [
                        'Verifikasi berhasil dilakukan.',
                        '',
                        `Sekarang kamu sudah memiliki akses penuh ke server **${interaction.guild.name}**.`,
                        '',
                        '🎭 Selamat roleplay & semoga betah bersama komunitas Pahlawan.'
                    ].join('\n')
                )

                .setTimestamp();

            await interaction.user.send({
                embeds: [dmSuccess]
            });

        } catch (e) {}
        
    } catch (error) {

        console.error(
            '❌ Error verifikasi:',
            error
        );

        const errorEmbed = new EmbedBuilder()

            .setColor(0xED4245)

            .setDescription(
                [
                    '## ❌ TERJADI KESALAHAN',
                    '',
                    '> Gagal memproses verifikasi.',
                    '> Silakan hubungi staff server.'
                ].join('\n')
            );

        await interaction.reply({
            embeds: [errorEmbed],
            flags: 64
        });
    }
}

module.exports = {
    handleAmbilKode,
    handleMasukkanKode,
    handleVerifikasiModal
};