const { 
    EmbedBuilder, 
    ActionRowBuilder, 
    ButtonBuilder, 
    ButtonStyle 
} = require('discord.js');

const config = require('../../config.json');

const PAYMENT_COLORS = {
    success: 0xFFD54F,
    error: 0xE74C3C,
    primary: 0xF39C12
};

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//
// ❌ ERROR EMBED
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//

function createErrorEmbed(method) {

    return new EmbedBuilder()

        .setColor(PAYMENT_COLORS.error)

        .setAuthor({
            name: 'Pahlawan Roleplay • Payment Center'
        })

        .setTitle('❌ METODE PEMBAYARAN TIDAK TERSEDIA')

        .setDescription(
            [
                `Metode pembayaran **${method.toUpperCase()}** sedang tidak tersedia.`,
                '',
                'Silakan gunakan metode pembayaran lainnya',
                'atau hubungi admin Pahlawan Roleplay.'
            ].join('\n')
        )

        .addFields(
            {
                name: '📌 Status',
                value: '🔴 Offline / Tidak Tersedia',
                inline: true
            },
            {
                name: '🛠️ Solusi',
                value: 'Hubungi admin untuk bantuan',
                inline: true
            }
        )

        .setFooter({
            text: 'Pahlawan Roleplay • Premium Payment'
        })

        .setTimestamp();
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//
// 💳 PAYMENT EMBED
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//

function createPaymentEmbed(method, paymentData) {

    const isObject =
        typeof paymentData === 'object' &&
        paymentData !== null;

    const value = isObject
        ? (paymentData.nomor || paymentData.image || '')
        : paymentData;

    const nama = isObject
        ? (paymentData.nama || '')
        : '';

    const paymentName = method.toUpperCase();

    const embed = new EmbedBuilder()

        .setColor(PAYMENT_COLORS.success)

        .setAuthor({
            name: 'Pahlawan Roleplay • Payment System'
        })

        .setTitle(`💳 PEMBAYARAN ${paymentName}`)

        .setDescription(
            [
                'Terima kasih telah mendukung Pahlawan Roleplay ❤️',
                '',
                'Silakan lakukan pembayaran sesuai',
                'informasi yang tersedia di bawah ini.'
            ].join('\n')
        )

        .setFooter({
            text: 'Pahlawan Roleplay • Kirim bukti transfer ke admin'
        })

        .setTimestamp();

    //━━━━━━━━━━━━━━━━━━//
    // 📷 QRIS
    //━━━━━━━━━━━━━━━━━━//

    if (method === 'qris') {

        embed

            .addFields(
                {
                    name: '📌 Cara Pembayaran',
                    value:
                        [
                            '• Scan QRIS di bawah',
                            '• Masukkan nominal pembayaran',
                            '• Selesaikan transaksi',
                            '• Kirim bukti transfer ke admin'
                        ].join('\n'),
                    inline: false
                },

                {
                    name: '👤 Atas Nama',
                    value: nama || 'Pahlawan Roleplay',
                    inline: true
                },

                {
                    name: '💎 Status',
                    value: '🟢 Aktif',
                    inline: true
                }
            )

            .setImage(value);

        return embed;
    }

    //━━━━━━━━━━━━━━━━━━//
    // 💳 PAYMENT NUMBER
    //━━━━━━━━━━━━━━━━━━//

    embed.addFields(

        {
            name: '👤 Atas Nama',
            value: nama || 'Pahlawan Roleplay',
            inline: true
        },

        {
            name: '💎 Status',
            value: '🟢 Aktif',
            inline: true
        },

        {
            name: '📱 Nomor Pembayaran',
            value: `\`\`\`${value}\`\`\``,
            inline: true 
        },

        {
            name: '📋 Instruksi',
            value:
                [
                    '• Transfer sesuai nominal',
                    '• Simpan bukti pembayaran',
                    '• Kirim bukti transfer kepada admin',
                    '• Tunggu proses konfirmasi'
                ].join('\n'),
            inline: false
        }
    );

    return embed;
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//
// 🎛️ HANDLE PAYMENT BUTTON
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━//

async function handlePaymentButton(interaction) {

    try {

        const method =
            interaction.customId.replace('payment_', '');

        //━━━━━━━━━━━━━━━━━━//
        // 📦 GET PAYMENT DATA
        //━━━━━━━━━━━━━━━━━━//

        const paymentData =
            config.payment?.[method];

        //━━━━━━━━━━━━━━━━━━//
        // ❌ VALIDASI
        //━━━━━━━━━━━━━━━━━━//

        if (!paymentData) {

            return interaction.reply({
                embeds: [createErrorEmbed(method)],
                ephemeral: true
            });
        }

        const isObject =
            typeof paymentData === 'object' &&
            paymentData !== null;

        const value = isObject
            ? (paymentData.nomor || paymentData.image || '')
            : paymentData;

        if (!value || value.trim() === '') {

            return interaction.reply({
                embeds: [createErrorEmbed(method)],
                ephemeral: true
            });
        }

        //━━━━━━━━━━━━━━━━━━//
        // 🎨 CREATE EMBED
        //━━━━━━━━━━━━━━━━━━//

        const paymentEmbed =
            createPaymentEmbed(method, paymentData);

        //━━━━━━━━━━━━━━━━━━//
        // 🔘 BUTTONS
        //━━━━━━━━━━━━━━━━━━//

        const components = [];

        if (method !== 'qris') {

            const row = new ActionRowBuilder()

                .addComponents(

                    new ButtonBuilder()
                        .setCustomId(`copy_${method}`)
                        .setLabel('📋 SALIN NOMOR')
                        .setStyle(ButtonStyle.Secondary),

                    new ButtonBuilder()
                        .setCustomId('payment_done')
                        .setLabel('✅ SUDAH TRANSFER')
                        .setStyle(ButtonStyle.Success)
                );

            components.push(row);
        }

        //━━━━━━━━━━━━━━━━━━//
        // 📤 SEND EMBED
        //━━━━━━━━━━━━━━━━━━//

        await interaction.reply({

            embeds: [paymentEmbed],

            components,

            ephemeral: true
        });

    } catch (error) {

        console.error('[PAYMENT ERROR]', error);

        const errorEmbed = new EmbedBuilder()

            .setColor(PAYMENT_COLORS.error)

            .setTitle('❌ TERJADI KESALAHAN')

            .setDescription(
                [
                    'Sistem pembayaran Pahlawan Roleplay',
                    'sedang mengalami gangguan.',
                    '',
                    'Silakan coba lagi beberapa saat.'
                ].join('\n')
            )

            .setFooter({
                text: 'Pahlawan Roleplay • Payment System'
            })

            .setTimestamp();

        if (interaction.replied || interaction.deferred) {

            await interaction.followUp({
                embeds: [errorEmbed],
                ephemeral: true
            });

        } else {

            await interaction.reply({
                embeds: [errorEmbed],
                ephemeral: true
            });
        }
    }
}

module.exports = {
    handlePaymentButton
};