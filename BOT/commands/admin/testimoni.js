const {
    SlashCommandBuilder,
    EmbedBuilder,
    AttachmentBuilder,
    PermissionFlagsBits
} = require('discord.js');

const fs = require('fs');
const fsp = require('fs').promises;
const path = require('path');

const config = require('../../config.json');

const testimonialsPath = path.join(
    __dirname,
    '../../data/testimonials.json'
);

const uploadsDir = path.join(
    __dirname,
    '../../uploads'
);

// ==============================
// 📁 CREATE FOLDER & DATABASE
// ==============================

if (!fs.existsSync(uploadsDir)) {
    fs.mkdirSync(uploadsDir, {
        recursive: true
    });
}

if (!fs.existsSync(testimonialsPath)) {
    fs.writeFileSync(
        testimonialsPath,
        '[]'
    );
}

module.exports = {

    data: new SlashCommandBuilder()

        .setName('testimoni')

        .setDescription(
            '📦 Buat testimoni transaksi Pahlawan Roleplay'
        )

        .addUserOption(option =>
            option
                .setName('pembeli')
                .setDescription('🛒 User pembeli')
                .setRequired(true)
        )

        .addStringOption(option =>
            option
                .setName('produk')
                .setDescription('📦 Nama produk')
                .setRequired(true)
        )

        .addStringOption(option =>
            option
                .setName('harga')
                .setDescription('💰 Harga produk')
                .setRequired(true)
        )

        .addAttachmentOption(option =>
            option
                .setName('bukti')
                .setDescription('🖼 Upload bukti transfer')
                .setRequired(true)
        )

        .setDefaultMemberPermissions(
            PermissionFlagsBits.Administrator
        ),

    async execute(interaction) {

        try {

            await interaction.deferReply({
                ephemeral: true
            });

            // ==============================
            // 📥 GET DATA
            // ==============================

            const buyer =
                interaction.options.getUser('pembeli');

            const product =
                interaction.options.getString('produk');

            const price =
                interaction.options.getString('harga');

            const attachment =
                interaction.options.getAttachment('bukti');

            const seller = interaction.user;

            // ==============================
            // 🖼 VALIDASI GAMBAR
            // ==============================

            if (
                !attachment.contentType?.startsWith('image/')
            ) {

                return interaction.editReply({
                    content:
                        '❌ File harus berupa gambar.'
                });

            }

            // ==============================
            // 📚 LOAD DATABASE
            // ==============================

            let testimonials = [];

            try {

                const data =
                    await fsp.readFile(
                        testimonialsPath,
                        'utf8'
                    );

                testimonials = JSON.parse(data);

                if (!Array.isArray(testimonials)) {
                    testimonials = [];
                }

            } catch {

                testimonials = [];

            }

            const testimonialId =
                testimonials.length + 1;

            // ==============================
            // 💾 SAVE IMAGE
            // ==============================

            const ext =
                path.extname(attachment.name) || '.png';

            const fileName =
                `testimoni-${Date.now()}${ext}`;

            const filePath =
                path.join(uploadsDir, fileName);

            const response =
                await fetch(attachment.url);

            if (!response.ok) {

                throw new Error(
                    'Gagal download gambar'
                );

            }

            const buffer = Buffer.from(
                await response.arrayBuffer()
            );

            fs.writeFileSync(filePath, buffer);

            // ==============================
            // 💾 SAVE DATABASE
            // ==============================

            testimonials.push({

                id: testimonialId,

                seller: seller.id,

                buyer: buyer.id,

                product,

                price,

                image: fileName,

                createdAt: Date.now()

            });

            await fsp.writeFile(
                testimonialsPath,
                JSON.stringify(
                    testimonials,
                    null,
                    2
                )
            );

            // ==============================
            // 🕒 FORMAT WAKTU
            // ==============================

            const now = new Date();

            const formattedDate =
                now.toLocaleDateString(
                    'id-ID',
                    {
                        weekday: 'long',
                        day: 'numeric',
                        month: 'long',
                        year: 'numeric',
                        timeZone: 'Asia/Jakarta'
                    }
                );

            const formattedTime =
                now.toLocaleTimeString(
                    'id-ID',
                    {
                        hour: '2-digit',
                        minute: '2-digit',
                        timeZone: 'Asia/Jakarta'
                    }
                );

            // ==============================
            // 💰 FORMAT HARGA
            // ==============================

            const formattedPrice =
                Number(price.replace(/\D/g, ''))
                    .toLocaleString('id-ID');

            // ==============================
            // 🖼 ATTACHMENT
            // ==============================

            const imageAttachment =
                new AttachmentBuilder(filePath);

            // ==============================
            // ✨ EMBED
            // ==============================

            const embed = new EmbedBuilder()

            .setColor('#FFD700')

            .setAuthor({
                name: '⚔️ Pahlawan Roleplay',
                iconURL:
                    interaction.guild.iconURL({
                        forceStatic: false
                    }) ||
                    interaction.client.user.displayAvatarURL()
            })

            .setTitle(
                `🧾 TESTIMONI #${testimonialId}`
            )

            .setDescription(
                [
                    '╔════════════════╗',
                    '✨ **TRANSAKSI BERHASIL** ✨',
                    '╚════════════════╝',
                    '',
                    'Terima kasih telah melakukan transaksi',
                    'di **Pahlawan Roleplay** ⚔️'
                ].join('\n')
            )

            .addFields(

                {
                    name: '🧑‍💼 PENJUAL',
                    value: `>>> <@${seller.id}>`,
                    inline: true
                },

                {
                    name: '🛒 PEMBELI',
                    value: `>>> <@${buyer.id}>`,
                    inline: true
                },

                {
                    name: '💰 HARGA',
                    value: `>>> Rp ${formattedPrice}`,
                    inline: true
                },

                {
                    name: '📦 PRODUK',
                    value: `>>> ${product}`,
                    inline: false
                },

                {
                    name: '📅 TANGGAL',
                    value: `>>> ${formattedDate}\n⏰ ${formattedTime} WIB`,
                    inline: false
                }

            )

            .setImage(
                `attachment://${fileName}`
            )

            .setThumbnail(
                interaction.guild.iconURL({
                    forceStatic: false
                })
            )

            .setFooter({
                text: '⚔️ Pahlawan Roleplay • Trusted Store',
                iconURL:
                    interaction.client.user.displayAvatarURL()
            })

            .setTimestamp();

            // ==============================
            // 📢 CHANNEL TESTIMONI
            // ==============================

            const channelId =
                config.testimoniChannel;

            if (!channelId) {

                return interaction.editReply({
                    content:
                        '❌ ID channel testimoni belum diatur di config.json'
                });

            }

            let channel = null;

            try {

                channel =
                    interaction.guild.channels.cache.get(
                        channelId
                    );

                if (!channel) {

                    channel =
                        await interaction.guild.channels.fetch(
                            channelId
                        );

                }

            } catch (err) {

                console.log(
                    '❌ ERROR FETCH CHANNEL:',
                    err
                );

            }

            if (!channel) {

                return interaction.editReply({
                    content:
                        '❌ Channel testimoni tidak ditemukan.'
                });

            }

            // ==============================
            // 🚀 SEND EMBED
            // ==============================

            await channel.send({

                content:
                    '💬 Testimoni baru telah dikirim!',

                embeds: [embed],

                files: [imageAttachment]

            });

            // ==============================
            // ✅ SUCCESS
            // ==============================

            await interaction.editReply({

                content:
                    '✅ Berhasil mengirim testimoni ke channel.'

            });

        } catch (error) {

            console.log(
                '🔥 ERROR TESTIMONI:',
                error
            );

            if (
                interaction.deferred ||
                interaction.replied
            ) {

                await interaction.editReply({

                    content:
                        '❌ Terjadi kesalahan saat membuat testimoni.'

                });

            } else {

                await interaction.reply({

                    content:
                        '❌ Terjadi kesalahan.',

                    ephemeral: true

                });

            }

        }

    }

};