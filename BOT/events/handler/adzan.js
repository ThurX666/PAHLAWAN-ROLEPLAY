const { EmbedBuilder } = require("discord.js");
const axios = require("axios");

module.exports = {
    name: "ready",
    once: false,
    async execute(client) {
        startAdzanSystem(client);
    }
};

function startAdzanSystem(client) {
    console.log("🕌 Sistem Adzan dimulai...");

    let lastSent = "";

    async function sholat() {
        try {

            const { data } = await axios.get(
                "https://api.aladhan.com/v1/timingsByCity",
                {
                    params: {
                        city: "Cirebon",
                        country: "Indonesia",
                        method: 11
                    },
                    timeout: 10000
                }
            );

            const t = data.data.timings;

            // Get current time in Asia/Jakarta timezone
            const now = new Date();
            const jakartaTime = new Date(now.toLocaleString("en-US", { timeZone: "Asia/Jakarta" }));

            const cur =
                String(jakartaTime.getHours()).padStart(2, "0") +
                ":" +
                String(jakartaTime.getMinutes()).padStart(2, "0");

            const list = {
                SUBUH: t.Fajr,
                DZUHUR: t.Dhuhr,
                ASHAR: t.Asr,
                MAGHRIB: t.Maghrib,
                ISYA: t.Isha
            };

            const config = require("../../config.json");

            const ch = await client.channels
                .fetch(config.channel.sholat)
                .catch(() => null);

            if (!ch) return;

            for (const [name, time] of Object.entries(list)) {

                const jamSholat = time.slice(0, 5);

                if (cur === jamSholat) {

                    const jakartaDate = new Date(now.toLocaleString("en-US", { timeZone: "Asia/Jakarta" }));
                    const uniqueKey = `${jakartaDate.toDateString()}-${name}-${cur}`;

                    if (lastSent === uniqueKey) continue;

                    lastSent = uniqueKey;

                    const embed = new EmbedBuilder()
                        .setColor("#39FF14")
                        .setTitle("🕌✨ WAKTU SHOLAT TELAH TIBA ✨🕌")
                        .setDescription(`
                            📢 **ADZAN ${name}**

                            ⏰ Waktu sholat telah masuk.

                            🙏 Jangan lupa menunaikan ibadah bagi yang menjalankan.

                            ━━━━━━━━━━━━━━

                            🤲 Semoga Allah SWT menerima segala amal ibadah kita.

                            ━━━━━━━━━━━━━━

                            ✨ Selamat beribadah dan semoga harimu penuh keberkahan.
                            `)
                        .setFooter({
                            text: "Pahlawan Roleplay • Islamic Reminder",
                            iconURL: "https://media.discordapp.net/attachments/1513604476865609788/1513604622797770933/logo3.png?ex=6a2855a7&is=6a270427&hm=5902561759e780738de44026e4da8955a8ac2f7ebf3281c376fc192a688366e9&=&format=webp&quality=lossless&width=869&height=856"
                        })
                        .setTimestamp();

                    await ch.send({
                        content: "**📢 HALLO PARA WARGA #Pahlawan**",
                        embeds: [embed]
                    });

                    console.log(`✅ Adzan ${name} terkirim (${cur})`);
                }
            }

        } catch (err) {
            console.error("❌ Error Adzan:");
            console.error(err.response?.data || err.message);
        }
    }

    sholat();

    setInterval(sholat, 60000);
}