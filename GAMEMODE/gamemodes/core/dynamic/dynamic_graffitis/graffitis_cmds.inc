YCMD:gototag(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new tgid;
    if(sscanf(params, "d", tgid)) return SUM(playerid, "/gototag [tgid]");

    if(!Iter_Contains(ServerTags, tgid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Graffiti Tag ID tersebut tidak valid!");
    SetPlayerPositionEx(playerid, GraffitiInfo[tgid][gfPos][0] - 5.5, GraffitiInfo[tgid][gfPos][1], GraffitiInfo[tgid][gfPos][2], -90);
    SetPlayerInteriorEx(playerid, GraffitiInfo[tgid][gfInt]);
    SetPlayerVirtualWorldEx(playerid, GraffitiInfo[tgid][gfVW]);

    AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInRusun] = -1;
    AccountData[playerid][pInGudang] = -1;
    return 1;
}

YCMD:edittag(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new tgid;
    if(sscanf(params, "d", tgid)) return SUM(playerid, "/edittag [tgid]");

    if(!Iter_Contains(ServerTags, tgid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Graffiti Tag ID tersebut tidak valid!");
    if(!IsPlayerInRangeOfPoint(playerid, 30.0, GraffitiInfo[tgid][gfPos][0], GraffitiInfo[tgid][gfPos][1], GraffitiInfo[tgid][gfPos][2])) 
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan Graffiti Tag ID tersebut!");
    if(Graffiti_BeingEdited(tgid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "That Graffiti Tag ID sedang diedit oleh admin lain!");

    if(!PlayerHasItem(playerid, "Pilox")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki pilox!");
    AccountData[playerid][pTempValue] = tgid;

    Dialog_Show(playerid, "GraffitiEdit", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Graffiti", 
    "Mohon masukkan tulisan graffiti yang ingin dibuat:\n\
    (n) = text akan berada di bawah/baris baru.\n\
    (r) = warna text merah.\n\
    (b) = warna text hitam.\n\
    (y) = warna text kuning.\n\
    (bl) = warna text biru.\n\
    (g) = warna text hijau.\n\
    (o) = warna text orange.\n\
    (w) = warna text putih.", "Input", "Batal");
    return 1;
}

YCMD:checktag(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new tgid;
    if(sscanf(params, "d", tgid)) return SUM(playerid, "/checktag [tgid]");
    if(!Iter_Contains(ServerTags, tgid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Graffiti Tag ID tersebut tidak valid!");

    static string[144];
    format(string, sizeof(string), "[Tag] "WHITE"%s", GraffitiInfo[tgid][gfText]);
    SendClientMessage(playerid, X11_PALEGREEN4, string);
    format(string, sizeof(string), "[Tag] "WHITE"Created by: "YELLOW"%s", GraffitiInfo[tgid][gfCreator]);
    SendClientMessage(playerid, X11_PALEGREEN4, string);
    return 1;
}