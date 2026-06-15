/*
forward SendDiscordPrivate(othername[], randverify, username[], usertag[]);
public SendDiscordPrivate(othername[], randverify, username[], usertag[])
{
    new DCC_Channel:channelprivate, DCC_Embed:mailembed, isifield[522];

    channelprivate = DCC_GetCreatedPrivateChannel();

    mailembed = DCC_CreateEmbed("PAHLAWAN", "", .color = 0xFF91A4, .footer_text = "Pintu Theater #1", .footer_icon_url = "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663", .image_url = "https://cdn.discordapp.com/attachments/1019532074119593984/1019827155154239549/Ticket_Arivena_Final-01.png");
    format(isifield, sizeof(isifield), "Yang terhormat, **%s#%s**.\n\n\
    Mohon perhatian anda, pengambilan Karcis Theater berhasil dilakukan.\n\
    Gunakan UCP untuk login ke dalam server!\n\
    Segera masuk ke Ruangan Theater melalui Pintu Theater #1 **(login in-game)** dan masukkan kode verifikasi di atas!", username, usertag, othername);
    DCC_SetEmbedDescription(mailembed, isifield);
    format(isifield, sizeof(isifield), "```%s```", othername);
    DCC_AddEmbedField(mailembed, "**UCP:**", isifield, true);
    format(isifield, sizeof(isifield), "```%d```", randverify);
    DCC_AddEmbedField(mailembed, "**Verification Code:**", isifield, false);
    DCC_AddEmbedField(mailembed, "**IP Server:**", "```"TEXT_IPADDRESS"```", true);
    DCC_AddEmbedField(mailembed, "**Port:**", "```"TEXT_IPPORT"```", true);
    DCC_SetEmbedThumbnail(mailembed, "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663");
    
    DCC_SendChannelEmbedMessage(channelprivate, mailembed);
    return 1;
}

forward SendDiscordPrivate(mail[]);
public SendDiscordPrivate(mail[])
{
    new DCC_Channel:channelprivate;

    channelprivate = DCC_GetCreatedPrivateChannel();

    new privatefield[522], DCC_Embed:embedprivate, isifieldpvt[522];
    embedprivate = DCC_CreateEmbed("U.S CITIZENSHIP AND IMMIGRATION SERVICES", "", .color = 0x00FFFF, .footer_text = "U.S Department Of Homeland Security", .image_url = "https://cdn.discordapp.com/attachments/956852798828478464/960351405393195099/unknown.png");
    format(privatefield, sizeof(privatefield), "Dear, %s#%s.\n\nNickname: %s\nBerhasil didaftarkan, gunakan verify code untuk verifikasi di in-game!", username, usertag, othername);
    DCC_SetEmbedDescription(embedprivate, privatefield);

    format(isifieldpvt, sizeof(isifieldpvt), "%s", othername);
    DCC_AddEmbedField(embedprivate, "Nickname", isifieldpvt, true);

    format(isifieldpvt, sizeof(isifieldpvt), "%d", randverify);
    DCC_AddEmbedField(embedprivate, "Verification Code", isifieldpvt, true);

    DCC_SendChannelMessage(channelprivate, mail);
}

forward ResendDiscordCode(othername[], randverify, username[], usertag[]);
public ResendDiscordCode(othername[], randverify, username[], usertag[])
{
    new DCC_Channel:channelprivate, DCC_Embed:mailembed, isifield[522];

    channelprivate = DCC_GetCreatedPrivateChannel();

    mailembed = DCC_CreateEmbed("PAHLAWAN", "", .color = 0xFF91A4, .footer_text = "Pintu Theater #1", .footer_icon_url = "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663", .image_url = "https://cdn.discordapp.com/attachments/1019532074119593984/1019827155154239549/Ticket_Arivena_Final-01.png");
    format(isifield, sizeof(isifield), "Yang terhormat, **%s#%s**.\n\n\
    Anda meminta pengiriman DM ulang.\n\
    Mohon perhatikan dengan baik, gunakan UCP untuk login ke dalam server!\n\
    Segera masuk ke Ruangan Theater melalui Pintu Theater #1 **(login in-game)** dan masukkan kode verifikasi di atas!", username, usertag, othername);
    DCC_SetEmbedDescription(mailembed, isifield);
    format(isifield, sizeof(isifield), "```%s```", othername);
    DCC_AddEmbedField(mailembed, "**UCP:**", isifield, true);
    format(isifield, sizeof(isifield), "```%d```", randverify);
    DCC_AddEmbedField(mailembed, "**Verification Code:**", isifield, false);
    DCC_AddEmbedField(mailembed, "**IP Server:**", "```"TEXT_IPADDRESS"```", true);
    DCC_AddEmbedField(mailembed, "**Port:**", "```"TEXT_IPPORT"```", true);
    DCC_SetEmbedThumbnail(mailembed, "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663");
    
    DCC_SendChannelEmbedMessage(channelprivate, mailembed);
    return 1;
}

DCMD:online(user, channel, params[])
{
    new DCC_Embed:csvstr, fieldfill[522];
    csvstr = DCC_CreateEmbed("PAHLAWAN", "", .color = 0xFF91A4, .footer_text = "Lobby Theater", .footer_icon_url = "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663", .image_url = "");
    format(fieldfill, sizeof(fieldfill), ":busts_in_silhouette: Jumlah Aktor yang sedang bermain peran saat ini adalah %d orang.", Iter_Count(Player));
    DCC_AddEmbedField(csvstr, "Mohon perhatian anda!", fieldfill, false);
    DCC_SetEmbedThumbnail(csvstr, "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663");
    DCC_SendChannelEmbedMessage(channel, csvstr);
    return 1;
}

DCMD:resendcode(user, channel, params[])
{
    if(channel != RSCODECH)
    {
        DCC_SendChannelMessage(channel, ":x: Mohon maaf, kamu tidak bisa menggunakan CMD tersebut di channel ini!");
        return 1;
    }

    new userIdstr[DCC_ID_SIZE], query[512], tempUCP[30], vercode, username[DCC_USERNAME_SIZE], usertag[128];
    DCC_GetUserId(user, userIdstr, DCC_ID_SIZE);
    DCC_GetUserName(user, username);
    DCC_GetUserDiscriminator(user, usertag);

    mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM whitelists WHERE discordid='%e' LIMIT 1", userIdstr);
    mysql_query(g_SQL, query);
    new rows = cache_num_rows();

    if(rows)
	{
        cache_get_value_name(0, "ucp", tempUCP);
        cache_get_value_name_int(0, "verify", vercode);

        if(vercode == -1)
        {
            format(query, sizeof(query), ":x: Mohon maaf, %s#%s akun UCP kamu telah melakukan verifikasi kode di dalam in-game!", username, usertag);
            DCC_SendChannelMessage(channel, query);
            return 1;
        }

        format(query, sizeof(query), ":white_check_mark: Hai, %s#%s silahkan cek DM kamu!", username, usertag);
        DCC_SendChannelMessage(channel, query);

        //DCC_CreatePrivateChannel(user, "ResendDiscordCode", "sdss", tempUCP, vercode, username, usertag);

        new mail[512];
        format(mail, 512, "```c\nSelamat Karakter anda di Arivena Theater berhasil didaftarkan\nGunakan UCP untuk login di dalam server!\nUCP: %s\nVerification Code: %d\n\
        IP Address:"TEXT_IPADDRESS"\n\
        Port:"TEXT_IPPORT"\n\
        Segera login dan masukkan kode verifikasi di atas!```", tempUCP, vercode);
        DCC_CreatePrivateChannel(user, "SendDiscordPrivate", "s", mail);
    }
    else
    {
        format(query, sizeof(query), ":x: Hai, %s#%s sepertinya kamu belum mengambil karcis!", username, usertag);
        DCC_SendChannelMessage(channel, query);
    }
    return 1;
}

DCMD:register(user, channel, params[])
{
    new othername[25];

    new username[DCC_USERNAME_SIZE], usertag[128];

    if(channel != WLCHANNS)
    {
        DCC_SendChannelMessage(channel, ":x: Anda tidak dapat mengambil Karcis Theater di channel ini!");
        embedsang = DCC_CreateEmbed("ARIVENA THEATER", "", .color = 0xFF91A4, .footer_text = "Lobby Theater", .footer_icon_url = "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663", .image_url = "https://media.discordapp.net/attachments/1011813979460481124/1019259296283885690/unknown.png");
        DCC_AddEmbedField(embedsang, "Mohon perhatian anda!", ":x: Anda tidak dapat mengambil Karcis Theater di channel ini, dipersilakan untuk menggunakannya di dalam channel yang sesuai.", false);
        DCC_SetEmbedThumbnail(embedsang, "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663");
        DCC_SendChannelEmbedMessage(channel, embedsang);
        return 1;
    }

	if(sscanf(params, "s[25]", othername))
	{
        DCC_SendChannelMessage(channel, ":x: Format pengambilan Karcis Theater salah, gunakan `!register [nama ucp]`");
        
        embedsang = DCC_CreateEmbed("ARIVENA THEATER", "", .color = 0xFF91A4, .footer_text = "Loket Karcis Theater", .footer_icon_url = "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663", .image_url = "https://media.discordapp.net/attachments/1012271786911612938/1012547240163803156/Desktop_Wallpaper.png?width=1178&height=662");
        DCC_GetUserName(user, username);
        DCC_GetUserDiscriminator(user, usertag);
        format(isifield, sizeof(isifield), "Mohon perhatian anda, **%s#%s**.\n\nFormat pengambilan Karcis Theater salah, dipersilakan untuk memeriksa kembali!", username, usertag);
        DCC_SetEmbedDescription(embedsang, isifield);
        DCC_AddEmbedField(embedsang, "Berdasarkan hasil pemeriksaan kami:", ":x: Format bot cmd tidak lengkap. Gunakan `!register [nama ucp]` dan jangan masukkan nama karakter untuk didaftarkan!", false);
        DCC_SetEmbedThumbnail(embedsang, "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663");
        DCC_SendChannelEmbedMessage(WLCHANNS, embedsang);
        return 1;
	}

    if(strlen(othername) < 5)
    {
        DCC_SendChannelMessage(channel, ":x: Nama UCP terlalu singkat, minimal **5 huruf/karakter** dan jangan gunakan spasi!");

        
        embedsang = DCC_CreateEmbed("ARIVENA THEATER", "", .color = 0xFF91A4, .footer_text = "Loket Karcis Theater", .footer_icon_url = "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663", .image_url = "https://media.discordapp.net/attachments/1012271786911612938/1012547240163803156/Desktop_Wallpaper.png?width=1178&height=662");
        DCC_GetUserName(user, username);
        DCC_GetUserDiscriminator(user, usertag);
        format(isifield, sizeof(isifield), "Mohon perhatian anda, **%s#%s**.\n\nFormat pengambilan Karcis Theater salah, dipersilakan untuk memeriksa kembali!", username, usertag);
        DCC_SetEmbedDescription(embedsang, isifield);
        DCC_AddEmbedField(embedsang, "Berdasarkan hasil pemeriksaan kami:", ":x: Nama UCP terlalu singkat, minimal **5 huruf/karakter**, `!register [nama ucp]` dan jangan masukkan nama karakter untuk didaftarkan!", false);
        DCC_SetEmbedThumbnail(embedsang, "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663");
        DCC_SendChannelEmbedMessage(WLCHANNS, embedsang);
        return 1;
    }

    if(IsRoleplayName(othername))
    {
        DCC_SendChannelMessage(channel, ":x: Gunakan format yang benar, `!register [nama ucp]` dan jangan masukkan nama karakter untuk didaftarkan!");

        
        embedsang = DCC_CreateEmbed("ARIVENA THEATER", "", .color = 0xFF91A4, .footer_text = "Loket Karcis Theater", .footer_icon_url = "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663", .image_url = "https://media.discordapp.net/attachments/1012271786911612938/1012547240163803156/Desktop_Wallpaper.png?width=1178&height=662");
        DCC_GetUserName(user, username);
        DCC_GetUserDiscriminator(user, usertag);
        format(isifield, sizeof(isifield), "Mohon perhatian anda, **%s#%s**.\n\nFormat pengambilan Karcis Theater salah, dipersilakan untuk memeriksa kembali!", username, usertag);
        DCC_SetEmbedDescription(embedsang, isifield);
        DCC_AddEmbedField(embedsang, "Berdasarkan hasil pemeriksaan kami:", ":x: Gunakan format yang benar, `!register [nama ucp]` dan jangan masukkan nama karakter untuk didaftarkan!", false);
        DCC_SetEmbedThumbnail(embedsang, "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663");
        DCC_SendChannelEmbedMessage(WLCHANNS, embedsang);
        return 1;
    }

    new query[512];
    mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM whitelists WHERE ucp='%e' LIMIT 1", othername);
    mysql_query(g_SQL, query);
    new rows = cache_num_rows();

    if(rows)
	{
        format(query, sizeof(query), ":x: Nama UCP %s tersebut sudah terdaftar di database kami, mohon gunakan nama yang lain!", othername);
        DCC_SendChannelMessage(channel, query);
        
        embedsang = DCC_CreateEmbed("ARIVENA THEATER", "", .color = 0xFF91A4, .footer_text = "Loket Karcis Theater", .footer_icon_url = "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663", .image_url = "https://media.discordapp.net/attachments/1012271786911612938/1012547240163803156/Desktop_Wallpaper.png?width=1178&height=662");
        DCC_GetUserName(user, username);
        DCC_GetUserDiscriminator(user, usertag);
        format(isifield, sizeof(isifield), "Mohon perhatian anda, **%s#%s**.\n\nUCP: **%s**\nTidak dapat didaftarkan karena nama UCP tersebut telah terdaftar!", username, usertag, othername);
        DCC_SetEmbedDescription(embedsang, isifield);
        DCC_AddEmbedField(embedsang, "Berdasarkan hasil pencarian kami:", ":x: Nama UCP tersebut sudah terdaftar di database kami, mohon gunakan nama yang lain!", false);
        DCC_SetEmbedThumbnail(embedsang, "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663");
        DCC_SendChannelEmbedMessage(WLCHANNS, embedsang);
        return 1;
    }

    new userIdstr[DCC_ID_SIZE];
    DCC_GetUserId(user, userIdstr, DCC_ID_SIZE);

    mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM whitelists WHERE discordid='%e' LIMIT 1", userIdstr);
    mysql_query(g_SQL, query);
    if(cache_num_rows() > 0)
    {
        format(query, sizeof(query), ":x: Hai %s#%d, anda sudah pernah mendaftar dan tidak bisa lagi mengambil Karcis!", username, usertag);
        DCC_SendChannelMessage(channel, query);

        embedsang = DCC_CreateEmbed("ARIVENA THEATER", "", .color = 0xFF91A4, .footer_text = "Loket Karcis Theater", .footer_icon_url = "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663", .image_url = "https://media.discordapp.net/attachments/1012271786911612938/1012547240163803156/Desktop_Wallpaper.png?width=1178&height=662");
        DCC_GetUserName(user, username);
        DCC_GetUserDiscriminator(user, usertag);
        format(isifield, sizeof(isifield), "Mohon perhatian anda, **%s#%s**.\n\nUCP: **%s**\nAnda tidak dapat mengambil Karcis Theater karena anda sudah pernah mengambilnya!", username, usertag, othername);
        DCC_SetEmbedDescription(embedsang, isifield);
        DCC_AddEmbedField(embedsang, "Berdasarkan hasil pencarian kami:", ":x: Anda sudah pernah mendaftar dan tidak bisa lagi membuat akun UCP!", false);
        DCC_SetEmbedThumbnail(embedsang, "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663");
        DCC_SendChannelEmbedMessage(WLCHANNS, embedsang);
        return 1;
    }
    
    new randverify;

    randverify = RandomEx(11111, 99999);

    new sequery[512], frmtname[25];
    mysql_format(g_SQL, sequery, sizeof(sequery), "INSERT INTO `whitelists` (`ucp`, `nickadmin`, `adutyname`, `verify`, `date`, `discordid`) VALUES ('%e', 'Bot', 'Bot', '%d', CURRENT_TIMESTAMP(), '%e')", othername, randverify, userIdstr);
	mysql_pquery(g_SQL, sequery);

    format(query, sizeof(query), ":white_check_mark: UCP %s telah berhasil didaftarkan!", othername);
    DCC_SendChannelMessage(channel, query);

    
    embedsang = DCC_CreateEmbed("ARIVENA THEATER", "", .color = 0xFF91A4, .footer_text = "Pintu Theater #1", .footer_icon_url = "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663", .image_url = "https://cdn.discordapp.com/attachments/1019532074119593984/1019827155154239549/Ticket_Arivena_Final-01.png");
    DCC_GetUserName(user, username);
    DCC_GetUserDiscriminator(user, usertag);
    format(isifield, sizeof(isifield), "Mohon perhatian anda, **%s#%s**.\n\nUCP: **%s**\nBerhasil didaftarkan, kini anda telah resmi memiliki Karcis Theater. Selamat datang!", username, usertag, othername);
    DCC_SetEmbedDescription(embedsang, isifield);
    DCC_AddEmbedField(embedsang, "Berdasarkan formulir pengambilan Karcis yang anda ajukan:", ":white_check_mark: Anda dinyatakan diterima menjadi Aktor (pemain peran) di Arivena Theater, selamat datang!", false);
    DCC_SetEmbedThumbnail(embedsang, "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663");
    DCC_SendChannelEmbedMessage(WLCHANNS, embedsang);

    new DCC_Role: assignrole; //DCC_Role: removerole;
	assignrole = DCC_FindRoleById("1011797579723440178"); // nah di sini buat id role
    DCC_AddGuildMemberRole(guildid, user, assignrole);

    //removerole = DCC_FindRoleById("1011809102437044395"); //id role yang akan dicabut
    //DCC_RemoveGuildMemberRole(guildid, user, removerole);

    format(frmtname, sizeof(frmtname), "Warga | %s", othername);
    DCC_SetGuildMemberNickname(guildid, user, frmtname);

    new mail[512];
	format(mail, 512, "```c\nSelamat Karakter anda di Arivena Theater berhasil didaftarkan\nGunakan UCP untuk login di dalam server!\nUCP: %s\nVerification Code: %d\n\
    IP Address:"TEXT_IPADDRESS"\n\
    Port:"TEXT_IPPORT"\n\
    Segera login dan masukkan kode verifikasi di atas!```", othername, randverify);
    DCC_CreatePrivateChannel(user, "SendDiscordPrivate", "s", mail);
    return 1;
}

DCMD:dih(user, channel, params[])
{
    new DCC_Embed:embedsang, isifield[522];

    embedsang = DCC_CreateEmbed("SURAT PERNYATAAN PERASAAN", "", .color = 0xFF91A4, .footer_text = "- By mhyunata (your future husband)", .footer_icon_url = "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663", .image_url = "https://cdn.discordapp.com/attachments/1011815023422746697/1021240998266941490/unknown.png");
    format(isifield, sizeof(isifield), "Hai, kamu cantikku <@904724421313441803>");
    DCC_SetEmbedDescription(embedsang, isifield);
    DCC_AddEmbedField(embedsang, "Kamu kesayanganku,", ":heart: Selama aku mengenal kamu, aku mengira bahwa kamu begitu langka di bumi ini. Bagiku tidak ada yang seperti kamu, bagaimana cara kamu bercanda, bergurau, tertawa dan cara kamu yang begitu estetik dalam suasana ngambek dan kesal.\n\
    Mungkin kamu memang agak ngeselin tapi bagiku justru itu nilai tambah untuk sisi sweet yang ada pada dirimu. Aku tak tahu harus bagaimana lagi menguraikan kata-kata untuk menggambarkan pesona dan kepribadianmu, intinya adalah aku nyaman di dekatmu.\n\
    Aku bahagia bisa mengenal kamu dan aku harap kita bisa selangkah lebih maju dari ini semua. Aku berharap kita menjadi suatu pribadi yang saling melengkapi antara kita berdua, hanya kamu, hanya aku dan cinta kita.", false);
    DCC_AddEmbedField(embedsang, "QS. Ar-Rum : 21", ":heart: 'Dan di antara tanda-tanda kekuasaan-Nya ialah Dia menciptakan untukmu isteri-isteri dari jenismu sendiri, supaya kamu cenderung dan merasa tenteram kepadanya, dan dijadikan-Nya diantaramu rasa kasih dan sayang. Sesungguhnya pada yang demikian itu benar-benar terdapat tanda-tanda bagi kaum yang berfikir.'", false);
    DCC_SetEmbedThumbnail(embedsang, "https://cdn.discordapp.com/attachments/1011815023422746697/1021240998266941490/unknown.png");
    DCC_SendChannelEmbedMessage(channel, embedsang);
    return 1;
}
*/

forward SendDiscordPrivate(const mail[]);
public SendDiscordPrivate(const mail[])
{
    new DCC_Channel:channelprivate;

    channelprivate = DCC_GetCreatedPrivateChannel();

    DCC_SendChannelMessage(channelprivate, mail);
    return 1;
}

DCMD:online(user, channel, params[])
{
    new DCC_Embed:csvstr, fieldfill[522];
    csvstr = DCC_CreateEmbed("ARIVENA THEATER", "", .color = 0xFF91A4, .footer_text = "Lobby Theater", .footer_icon_url = "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663", .image_url = "");
    format(fieldfill, sizeof(fieldfill), ":busts_in_silhouette: Jumlah Aktor yang sedang bermain peran saat ini adalah %d orang.", Iter_Count(Player));
    DCC_AddEmbedField(csvstr, "Mohon perhatian anda!", fieldfill, false);
    DCC_SetEmbedThumbnail(csvstr, "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663");
    DCC_SendChannelEmbedMessage(channel, csvstr);
    return 1;
}

DCMD:resendcode(user, channel, params[])
{
    if(channel != RSCODECH)
    {
        DCC_SendChannelMessage(channel, ":x: Mohon maaf, kamu tidak bisa menggunakan CMD tersebut di channel ini!");
        return 1;
    }

    new userIdstr[DCC_ID_SIZE], query[512], tempUCP[30], vercode, username[DCC_USERNAME_SIZE], usertag[128];
    DCC_GetUserId(user, userIdstr, DCC_ID_SIZE);
    DCC_GetUserName(user, username);
    DCC_GetUserDiscriminator(user, usertag);

    mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `whitelists` WHERE `discordid`='%e' LIMIT 1", userIdstr);
    mysql_query(g_SQL, query);
    new rows = cache_num_rows();

    if(rows)
	{
        cache_get_value_name(0, "ucp", tempUCP);
        cache_get_value_name_int(0, "verify", vercode);

        if(vercode == -1)
        {
            format(query, sizeof(query), ":x: Mohon maaf, %s#%s akun UCP kamu telah melakukan verifikasi kode di dalam in-game!", username, usertag);
            DCC_SendChannelMessage(channel, query);
            return 1;
        }

        format(query, sizeof(query), ":white_check_mark: Hai, %s#%s silahkan cek DM kamu!", username, usertag);
        DCC_SendChannelMessage(channel, query);

        new mail[512];
        format(mail, 512, "Selamat Karakter anda di Pahlawan Roleplay Theater berhasil didaftarkan\nGunakan UCP untuk login di dalam server!\nUCP: %s\nVerification Code: %d\n\
        IP Address:"TEXT_IPADDRESS"\n\
        Port:"TEXT_IPPORT"\n\
        Segera login dan masukkan kode verifikasi di atas!", tempUCP, vercode);
        DCC_CreatePrivateChannel(user, "SendDiscordPrivate", "s", mail);
    }
    else
    {
        format(query, sizeof(query), ":x: Hai, %s#%s sepertinya kamu belum mengambil karcis!", username, usertag);
        DCC_SendChannelMessage(channel, query);
    }
    return 1;
}

DCMD:register(user, channel, params[])
{
    new othername[25];

    new username[DCC_USERNAME_SIZE], usertag[128];

    if(channel != 1285923567657156670)
    {
        DCC_SendChannelMessage(channel, ":x: Anda tidak dapat mengambil Karcis Theater di channel ini!");
        return 1;
    }

	if(sscanf(params, "s[25]", othername))
	{
        DCC_SendChannelMessage(channel, ":x: Format pengambilan Karcis Theater salah, gunakan `!register [nama ucp]`");
        return 1;
	}

    if(strlen(othername) < 5 || strlen(othername) > 24)
    {
        DCC_SendChannelMessage(channel, ":x: Nama UCP terlalu singkat, minimal **5 huruf/karakter** dan maksimal **24 huruf/karakter** serta jangan gunakan spasi!");
        return 1;
    }

    if(IsRoleplayName(othername))
    {
        DCC_SendChannelMessage(channel, ":x: Gunakan format yang benar, `!register [nama ucp]` dan jangan masukkan nama karakter untuk didaftarkan!");
        return 1;
    }

    new query[512];
    mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `whitelists` WHERE `ucp`='%e' LIMIT 1", othername);
    mysql_query(g_SQL, query);
    new rows = cache_num_rows();

    if(rows)
	{
        format(query, sizeof(query), ":x: Nama UCP %s tersebut sudah terdaftar di database kami, mohon gunakan nama yang lain!", othername);
        DCC_SendChannelMessage(channel, query);
        return 1;
    }

    new userIdstr[DCC_ID_SIZE];
    DCC_GetUserId(user, userIdstr, DCC_ID_SIZE);
    DCC_GetUserName(user, username);
    DCC_GetUserDiscriminator(user, usertag);

    mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `whitelists` WHERE `discordid`='%e' LIMIT 1", userIdstr);
    mysql_query(g_SQL, query);
    if(cache_num_rows() > 0)
    {
        format(query, sizeof(query), ":x: Hai %s#%s, anda sudah pernah mendaftar dan tidak bisa lagi mengambil Karcis!", username, usertag);
        DCC_SendChannelMessage(channel, query);
        return 1;
    }
    
    new randverify;

    randverify = RandomEx(11111, 99999);

    new sequery[512], frmtname[25];
    mysql_format(g_SQL, sequery, sizeof(sequery), "INSERT INTO `whitelists` (`ucp`, `nickadmin`, `adutyname`, `verify`, `date`, `discordid`) VALUES ('%e', 'Bot', 'Bot', '%d', CURRENT_TIMESTAMP(), '%e')", othername, randverify, userIdstr);
	mysql_pquery(g_SQL, sequery);

    format(query, sizeof(query), ":white_check_mark: UCP %s telah berhasil didaftarkan!", othername);
    DCC_SendChannelMessage(channel, query);

    new DCC_Role: assignrole, DCC_Role: removerole;
	assignrole = DCC_FindRoleById("1011797579723440178"); // nah di sini buat id role
    DCC_AddGuildMemberRole(guildid, user, assignrole);

    removerole = DCC_FindRoleById("1017838364449321080"); //id role yang akan dicabut
    DCC_RemoveGuildMemberRole(guildid, user, removerole);

    format(frmtname, sizeof(frmtname), "Warga | %s", othername);
    DCC_SetGuildMemberNickname(guildid, user, frmtname);

    new mail[512];
	format(mail, 512, "Selamat Karakter anda di Pahlawan Roleplay berhasil didaftarkan\nGunakan UCP untuk login di dalam server!\nUCP: %s\nVerification Code: %d\n\
    IP Address:"TEXT_IPADDRESS"\n\
    Port:"TEXT_IPPORT"\n\
    Segera login dan masukkan kode verifikasi di atas!", othername, randverify);
    DCC_CreatePrivateChannel(user, "SendDiscordPrivate", "s", mail);
    return 1;
}

DCMD:dih(user, channel, params[])
{
    new DCC_Embed:embedsang, isifield[522];

    embedsang = DCC_CreateEmbed("SURAT PERNYATAAN PERASAAN", "", .color = 0xFF91A4, .footer_text = "- By mhyunata (your future husband)", .footer_icon_url = "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663", .image_url = "https://cdn.discordapp.com/attachments/1011815023422746697/1021240998266941490/unknown.png");
    format(isifield, sizeof(isifield), "Hai, kamu cantikku <@904724421313441803>");
    DCC_SetEmbedDescription(embedsang, isifield);
    DCC_AddEmbedField(embedsang, "Kamu kesayanganku,", ":heart: Selama aku mengenal kamu, aku mengira bahwa kamu begitu langka di bumi ini. Bagiku tidak ada yang seperti kamu, bagaimana cara kamu bercanda, bergurau, tertawa dan cara kamu yang begitu estetik dalam suasana ngambek dan kesal.\n\
    Mungkin kamu memang agak ngeselin tapi bagiku justru itu nilai tambah untuk sisi sweet yang ada pada dirimu. Aku tak tahu harus bagaimana lagi menguraikan kata-kata untuk menggambarkan pesona dan kepribadianmu, intinya adalah aku nyaman di dekatmu.\n\
    Aku bahagia bisa mengenal kamu dan aku harap kita bisa selangkah lebih maju dari ini semua. Aku berharap kita menjadi suatu pribadi yang saling melengkapi antara kita berdua, hanya kamu, hanya aku dan cinta kita.", false);
    DCC_AddEmbedField(embedsang, "QS. Ar-Rum : 21", ":heart: 'Dan di antara tanda-tanda kekuasaan-Nya ialah Dia menciptakan untukmu isteri-isteri dari jenismu sendiri, supaya kamu cenderung dan merasa tenteram kepadanya, dan dijadikan-Nya diantaramu rasa kasih dan sayang. Sesungguhnya pada yang demikian itu benar-benar terdapat tanda-tanda bagi kaum yang berfikir.'", false);
    DCC_SetEmbedThumbnail(embedsang, "https://cdn.discordapp.com/attachments/1011815023422746697/1021240998266941490/unknown.png");
    DCC_SendChannelEmbedMessage(channel, embedsang);
    return 1;
}

DCMD:forget(user, channel, params[])
{
    if(channel != FRGPW)
    {
        DCC_SendChannelMessage(channel, ":x: Mohon maaf, kamu tidak bisa menggunakan CMD tersebut di channel ini!");
        return 1;
    }

    new userIdstr[DCC_ID_SIZE], query[512], tempUCP[30], username[DCC_USERNAME_SIZE], usertag[128];
    DCC_GetUserId(user, userIdstr, DCC_ID_SIZE);
    DCC_GetUserName(user, username);
    DCC_GetUserDiscriminator(user, usertag);

    mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `whitelists` WHERE `discordid`='%e' LIMIT 1", userIdstr);
    mysql_query(g_SQL, query);
    new rows = cache_num_rows();

    if(rows)
	{
        cache_get_value_name(0, "ucp", tempUCP);

        format(query, sizeof(query), ":white_check_mark: Hai, %s#%s kami telah mengirim pesan melalui DM discord anda, harap dicek!", username, usertag);
        DCC_SendChannelMessage(channel, query);

        new mail[512], halah[251], randex = RandomEx(111111, 999999);
        mysql_format(g_SQL, halah, sizeof(halah), "UPDATE `whitelists` SET `recovery` = %d WHERE `ucp` = '%e'", randex, tempUCP);
        mysql_pquery(g_SQL, halah);
        format(mail, 512, "Anda telah meminta layanan lupa password.\nJika ini bukan anda, maka abaikan saja pesan ini!\nRecovery Code: %d\nMasuklah ke server dan masukkan Recovery Code untuk membuat ulang kata sandi!", randex);
        DCC_CreatePrivateChannel(user, "SendDiscordPrivate", "s", mail);
    }
    else
    {
        format(query, sizeof(query), ":x: Hai, %s#%s sepertinya kamu belum mengambil karcis!", username, usertag);
        DCC_SendChannelMessage(channel, query);
    }
    return 1;
}
