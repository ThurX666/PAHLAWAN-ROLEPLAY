//#include <YSI_Coding\y_hooks>

forward OnServerOnline();
public OnServerOnline()
{
    new DCC_Embed:embedonl, description[512];

    embedonl = DCC_CreateEmbed("PAHLAWAN ROLEPLAY", "", .color = 0xFF91A4, .footer_text = "Penjaga Pintu Theater #1", .footer_icon_url = "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663", .image_url = "https://cdn.discordapp.com/attachments/1019532074119593984/1019825997727662130/onlinecut.png");
    format(description, sizeof(description), 
    "**SEBELUM BERMAIN WAJIB BACA:\n\
    <#1011812617624494090>\n\
    <#1011812655700389899>\n\
    <#1011812678366400583>\n**");
    DCC_SetEmbedDescription(embedonl, description);

    DCC_SetEmbedThumbnail(embedonl, "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663");
    DCC_SendChannelEmbedMessage(ANNOUNCEMENT, embedonl);
    DCC_SendChannelMessage(ANNOUNCEMENT, "<@&1011797579723440178>");
    return 1;
}

forward OnServerOffline();
public OnServerOffline()
{
    new DCC_Embed:embedmt, description[512];

    embedmt = DCC_CreateEmbed("ARIVENA THEATER", "", .color = 0xFF91A4, .footer_text = "Penjaga Pintu Theater #1", .footer_icon_url = "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663", .image_url = "https://cdn.discordapp.com/attachments/1019532074119593984/1019825997308252240/offlinecut.png");
    format(description, sizeof(description), 
    "**SEBELUM BERMAIN WAJIB BACA:\n\
    <#1011812617624494090>\n\
    <#1011812655700389899>\n\
    <#1011812678366400583>\n**");
    DCC_SetEmbedDescription(embedmt, description);
    DCC_SetEmbedThumbnail(embedmt, "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663");
    DCC_SendChannelEmbedMessage(ANNOUNCEMENT, embedmt);
    DCC_SendChannelMessage(ANNOUNCEMENT, "<@&1011797579723440178>");
    return 1;
}

/*
forward PlayerIncomingConnection(playerid, ip_address[], port);
public PlayerIncomingConnection(playerid, ip_address[], port)
{
    new DCC_Embed:embedconn, dclogin[512];

    embedconn = DCC_CreateEmbed("ARIVENA THEATER", "", .color = 0xFF91A4, .footer_text = "Penjaga Pintu Theater #1", .footer_icon_url = "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663", .image_url = "");
    format(dclogin, sizeof(dclogin), "**(ID: %d)** akan tiba di Arivena Theater `[%s:%i]`", playerid, ip_address, port);
    DCC_AddEmbedField(embedconn, ":globe_with_meridians: **| Incoming**", dclogin, false);
    DCC_SetEmbedThumbnail(embedconn, "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663");
    DCC_SendChannelEmbedMessage(CONNECT, embedconn);
    return 1;
}

forward PlayerConnectingLog(playerid);
public PlayerConnectingLog(playerid)
{
    new DCC_Embed:embedconn, dclogin[512];

    embedconn = DCC_CreateEmbed("ARIVENA THEATER", "", .color = 0xFF91A4, .footer_text = "Penjaga Pintu Theater #1", .footer_icon_url = "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663", .image_url = "");
    format(dclogin, sizeof(dclogin), "Penjaga sedang memeriksa Karcis Theater milik **%s (ID: %d)** di Pintu Theater #1", AccountData[playerid][pUCP], playerid);
    DCC_AddEmbedField(embedconn, ":tickets: **| Checking**", dclogin, false);
    DCC_SetEmbedThumbnail(embedconn, "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663");
    DCC_SendChannelEmbedMessage(CONNECT, embedconn);
    return 1;
}

forward PlayerKickedBlockedUCPLog(playerid);
public PlayerKickedBlockedUCPLog(playerid)
{
    new DCC_Embed:embedconn, dclogin[512];

    embedconn = DCC_CreateEmbed("ARIVENA THEATER", "", .color = 0xFF91A4, .footer_text = "Penjaga Pintu Theater #1", .footer_icon_url = "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663", .image_url = "");
    format(dclogin, sizeof(dclogin), "Penjaga melarang masuk **%s (ID: %d)** karena Karcis Theater nya terblokir di Pintu Theater #1", AccountData[playerid][pUCP], playerid);
    DCC_AddEmbedField(embedconn, ":no_entry_sign: **| Blocking**", dclogin, false);
    DCC_SetEmbedThumbnail(embedconn, "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663");
    DCC_SendChannelEmbedMessage(CONNECT, embedconn);
    return 1;
}

forward PlayerKickedNotWhitelistedLog(playerid);
public PlayerKickedNotWhitelistedLog(playerid)
{
    new DCC_Embed:embedconn, dclogin[512];

    embedconn = DCC_CreateEmbed("ARIVENA THEATER", "", .color = 0xFF91A4, .footer_text = "Penjaga Pintu Theater #1", .footer_icon_url = "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663", .image_url = "");
    format(dclogin, sizeof(dclogin), "Penjaga melarang masuk **%s (ID: %d)** karena tidak memiliki Karcis Theater.", AccountData[playerid][pUCP], playerid);
    DCC_AddEmbedField(embedconn, ":no_entry_sign: **| Blocking**", dclogin, false);
    DCC_SetEmbedThumbnail(embedconn, "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663");
    DCC_SendChannelEmbedMessage(CONNECT, embedconn);
    return 1;
}

forward StaffCommandLog(playerid, commandstxt[]);
public StaffCommandLog(playerid, commandstxt[])
{
    new DCC_Embed:embedconn, tanggal, bulan, tahun, jam, menit, detik, sccstr[128];

    getdate(tahun, bulan, tanggal);
    gettime(jam, menit, detik);

    embedconn = DCC_CreateEmbed("ARIVENA THEATER", "", .color = 0xFF91A4, .footer_text = "", .footer_icon_url = "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663", .image_url = "");
    DCC_AddEmbedField(embedconn, ":eye: **| Staff CMD**", commandstxt, false);

    format(sccstr, sizeof(sccstr), "%02d/%02d/%d | %02d:%02d:%02d WIB", tanggal, bulan, tahun, jam, menit, detik);
    DCC_SetEmbedFooter(embedconn, sccstr, "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663");
    DCC_SetEmbedThumbnail(embedconn, "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663");
    DCC_SendChannelEmbedMessage(STAFFCMD, embedconn);
    return 1;
}

forward PlayerLoginLog(playerid);
public PlayerLoginLog(playerid)
{
	new DCC_Embed:embedlogin, dclogin[555], country[MAX_COUNTRY_LENGTH], city[MAX_CITY_LENGTH];
    
    GetPlayerCountry(playerid, country, MAX_COUNTRY_LENGTH);
	GetPlayerCity(playerid, city, MAX_CITY_LENGTH);
	
    embedlogin = DCC_CreateEmbed("ARIVENA THEATER", "", .color = 0xFF91A4, .footer_text = "Penjaga Pintu Theater #1", .footer_icon_url = "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663", .image_url = "");
    format(dclogin, sizeof(dclogin), "**%s** telah masuk ke dalam Pintu Theater #1\n\
    **UCP: %s**\n\
    **Player ID:** %d\n\
    **Kota:** %s\n\
    **Negara:** %s", 
    AccountData[playerid][pName],
    AccountData[playerid][pUCP],
    playerid,
    city,
    country);
    DCC_AddEmbedField(embedlogin, ":white_check_mark: **| Join**", dclogin, false);
    DCC_SetEmbedThumbnail(embedlogin, "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663");
    DCC_SendChannelEmbedMessage(CONNECT, embedlogin);
    return 1;
}


hook OnPlayerDisconnect(playerid, reason)
{
    new DCC_Embed:embeddisc, dclogin[512], reastr[64], country[MAX_COUNTRY_LENGTH], city[MAX_CITY_LENGTH];
    
    GetPlayerCountry(playerid, country, MAX_COUNTRY_LENGTH);
	GetPlayerCity(playerid, city, MAX_CITY_LENGTH);

    new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);

    switch(reason)
    {
        case 0: { reastr = "Crash/Timeout"; }
        case 1: { reastr = "Quit/Keluar"; }
        case 2: { reastr = "Kick/Banned"; }
    }

    embeddisc = DCC_CreateEmbed("ARIVENA THEATER", "", .color = 0xFF91A4, .footer_text = "Penjaga Pintu Theater #1", .footer_icon_url = "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663", .image_url = "");
    format(dclogin, sizeof(dclogin), "**%s** telah keluar dari Pintu Theater #1 (Reason: %s)\n\
    **UCP: %s**\n\
    **Nama Karakter:** %s\n\
    **Player ID:** %d\n\
    **Level:** %d\n\
    **Lokasi Terakhir:** %s\n\
    **Uang Saku:** $%s\n\
    **Uang Bank:** $%s",
    AccountData[playerid][pName],
    reastr,
    AccountData[playerid][pUCP],
    AccountData[playerid][pName],
    playerid,
    AccountData[playerid][pLevel],
    GetLocation(x, y, z),
    FormatMoney(AccountData[playerid][pMoney]),
    FormatMoney(AccountData[playerid][pBankMoney]));

    DCC_AddEmbedField(embeddisc, ":no_entry: **| Leave**", dclogin, false);
    DCC_SetEmbedThumbnail(embeddisc, "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663");
    DCC_SendChannelEmbedMessage(CONNECT, embeddisc);
	return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
    new Float:x, Float:y, Float:z, DCC_Embed:deathembed, deathlogmsg[512];
    GetPlayerPos(playerid, x, y, z);

    if(killerid == INVALID_PLAYER_ID)
    {
        deathembed = DCC_CreateEmbed("ARIVENA THEATER", "", .color = 0xFF91A4, .footer_text = "Penjaga Pintu Theater #1", .footer_icon_url = "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663", .image_url = "");
        format(deathlogmsg, sizeof(deathlogmsg), 
        "**%s** mati karena ulah diri sendiri. (%s)\n\
        **Pembunuh: Digigit Naga**\t**Korban: %s**\n\
        **UCP:** N/A\t**UCP:** %s\n\
        **ID:** N/A\t**ID:** %d\n\
        **Level:** N/A\t**Level:** %d\n\
        **Lokasi:** %s",
        AccountData[playerid][pName],
        ReturnWeaponName(reason),
        AccountData[playerid][pName],
        AccountData[playerid][pUCP],
        playerid,
        AccountData[playerid][pLevel],
        GetLocation(x, y, z));

        DCC_AddEmbedField(deathembed, ":skull: **| Mati**", deathlogmsg, false);
        DCC_SetEmbedThumbnail(deathembed, "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663");
        DCC_SendChannelEmbedMessage(DEATH, deathembed);
    }
    else
    {
        deathembed = DCC_CreateEmbed("ARIVENA THEATER", "", .color = 0xFF91A4, .footer_text = "Penjaga Pintu Theater #1", .footer_icon_url = "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663", .image_url = "");
        format(deathlogmsg, sizeof(deathlogmsg), 
        "**%s** membunuh **%s**. (%s)\n\
        **Pembunuh: %s**\t**Korban: %s**\n\
        **UCP:** %s\t**UCP:** %s\n\
        **ID:** %d\t**ID:** %d\n\
        **Level:** %d\t**Level:** %d\n\
        **Lokasi:** %s",
        AccountData[killerid][pName],
        AccountData[playerid][pName],
        ReturnWeaponName(AccountData[killerid][pWeapon]),
        AccountData[killerid][pName],
        AccountData[playerid][pName],
        AccountData[killerid][pUCP],
        AccountData[playerid][pUCP],
        killerid,
        playerid,
        AccountData[killerid][pLevel],
        AccountData[playerid][pLevel],
        GetLocation(x, y, z));

        DCC_AddEmbedField(deathembed, ":skull: **| Mati**", deathlogmsg, false);
        DCC_SetEmbedThumbnail(deathembed, "https://media.discordapp.net/attachments/1012271786911612938/1012547423199055902/Logo_Transparent.png?width=663&height=663");
        DCC_SendChannelEmbedMessage(DEATH, deathembed);
    }
    return 1;
}*/