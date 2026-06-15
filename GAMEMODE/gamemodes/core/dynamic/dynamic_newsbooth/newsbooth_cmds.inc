YCMD:addnewsstand(playerid, params[], help)
{
    new query[512], nwsbtid = Iter_Free(NewsBooths); // yang tadinya masih baru dibikin
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    if(nwsbtid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah dynamic Newspaper Stand sudah maksimal!");

    GetPlayerPos(playerid,  NewsStandData[nwsbtid][Pos][0],  NewsStandData[nwsbtid][Pos][1],  NewsStandData[nwsbtid][Pos][2]); //ketika diget maka akan diisi wpx, wpy, wpz nya menjadi koordinat kita saat ini.

    NewsStandData[nwsbtid][Pos][3] = NewsStandData[nwsbtid][Pos][4] = NewsStandData[nwsbtid][Pos][5] = 0.0;
    NewsStandData[nwsbtid][Interior] = GetPlayerInterior(playerid);
    NewsStandData[nwsbtid][World] = GetPlayerVirtualWorld(playerid);

    NewsStandData[nwsbtid][Object] = CreateDynamicObject(1285, NewsStandData[nwsbtid][Pos][0], NewsStandData[nwsbtid][Pos][1], NewsStandData[nwsbtid][Pos][2], NewsStandData[nwsbtid][Pos][3], NewsStandData[nwsbtid][Pos][4], NewsStandData[nwsbtid][Pos][5], NewsStandData[nwsbtid][World], NewsStandData[nwsbtid][Interior], -1, 100.0, 100.0, -1);
    NewsStandData[nwsbtid][Label] = CreateDynamic3DTextLabel("[Kotak Koran]\n"WHITE"Gunakan "YELLOW"'/read' "WHITE"untuk membaca koran!\nHarga: "GREEN"$25.75", 0xc0c0c8A6, NewsStandData[nwsbtid][Pos][0], NewsStandData[nwsbtid][Pos][1], NewsStandData[nwsbtid][Pos][2]+0.85, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, NewsStandData[nwsbtid][World], NewsStandData[nwsbtid][Interior], -1, 10.0, -1, 0);
	
	Iter_Add(NewsBooths, nwsbtid); //ini memasukkan id baru ke dalam kelompok.

    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `newsstands` SET `id`='%d', `X`='%f', `Y`='%f', `Z`='%f', `Rx`='%f', `Ry`='%f', `Rz`='%f', `Interior`='%d', `World`='%d'", nwsbtid, NewsStandData[nwsbtid][Pos][0], NewsStandData[nwsbtid][Pos][1], NewsStandData[nwsbtid][Pos][2], NewsStandData[nwsbtid][Pos][3], NewsStandData[nwsbtid][Pos][4], NewsStandData[nwsbtid][Pos][5], GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
	mysql_pquery(g_SQL, query, "OnNewsStandCreated", "ii", playerid, nwsbtid);
    return 1;
}

YCMD:gotonewsstand(playerid, params[], help)
{
	new id;
	if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);
		
	if(sscanf(params, "d", id))
		return SUM(playerid, "/gotonewsstand [id]");

	if(!Iter_Contains(NewsBooths, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Newspaper Stand ID!");
	SetPlayerPositionEx(playerid, NewsStandData[id][Pos][0], NewsStandData[id][Pos][1], NewsStandData[id][Pos][2], NewsStandData[id][Pos][5]);
    SetPlayerInteriorEx(playerid, NewsStandData[id][Interior]);
    SetPlayerVirtualWorldEx(playerid, NewsStandData[id][World]);

    AccountData[playerid][pInDoor] = -1;
	AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
	AccountData[playerid][pInRusun] = -1;
    AccountData[playerid][pInGudang] = -1;
	return 1;
}

YCMD:editnewsstand(playerid, params[], help)
{
	new id; 

    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

	if(sscanf(params, "d", id))
    {
        SUM(playerid, "/editnewsstand [id]");
        return 1;
    }

	if(!Iter_Contains(NewsBooths, id)) 
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Newspaper Stand ID!");

	if(!IsPlayerInRangeOfPoint(playerid, 30.0, NewsStandData[id][Pos][0], NewsStandData[id][Pos][1], NewsStandData[id][Pos][2])) 
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan Newspaper Stand ID tersebut!");

    if(AccountData[playerid][EditingNewsStandID] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang mengedit newspaper stand!");

    if(!IsPlayerInRangeOfPoint(playerid, 30.0, NewsStandData[id][Pos][0], NewsStandData[id][Pos][1], NewsStandData[id][Pos][2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan Newspaper Stand ID tersebut!");
    if(NewsStand_BeingEdited(id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "That Newspaper Stand ID sedang diedit oleh admin lain!");

    AccountData[playerid][EditingNewsStandID] = id;
    EditDynamicObject(playerid, NewsStandData[id][Object]);

    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s edited the position of Newspaper Stand ID: %d.", AccountData[playerid][pAdminname], id);
    return 1;
}

YCMD:removenewsstand(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

	new id, strgbg[128];
	if(sscanf(params, "i", id)) return SUM(playerid, "/removenewsstand [id]");
	if(!Iter_Contains(NewsBooths, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Newspaper Stand ID!");

    if(NewsStand_BeingEdited(id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Newspaper Stand ID tersebut sedang diedit oleh admin lain!");

    if(DestroyDynamic3DTextLabel(NewsStandData[id][Label]))
        NewsStandData[id][Label] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    if(DestroyDynamicObject(NewsStandData[id][Object]))
        NewsStandData[id][Object] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;

    NewsStandData[id][Pos][0] = NewsStandData[id][Pos][1] = NewsStandData[id][Pos][2] = NewsStandData[id][Pos][3] = NewsStandData[id][Pos][4] = NewsStandData[id][Pos][5] = 0.0;
    NewsStandData[id][Interior] = NewsStandData[id][World] = 0;
    Iter_Remove(NewsBooths, id);

    mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `newsstands` WHERE `id` = %d", id);
    mysql_pquery(g_SQL, strgbg);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s removed Newspaper Stand with ID: %d.", AccountData[playerid][pAdminname], id);
	return 1;
}

YCMD:read(playerid, params[], help)
{
    new id = NewsStand_Nearest(playerid);

    if(id == -1)  return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan Newspaper Stand manapun!");
    if(AccountData[playerid][pMoney] < 25) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang tidak cukup untuk membaca koran!");
    TakePlayerMoneyEx(playerid, 25);

    ShowItemBox(playerid, "Cash", "Removed $25x", 1212, 4);

    SendRPMeAboveHead(playerid, "Membayar dan mengambil untuk dibaca koran.");
    SelectTextDraw(playerid, 0xff91a4cc);
    ShowKoranTD(playerid);

    SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Gunakan "CMDEA"'/cursor' "WHITE"jika mouse hilang dari layar/textdraw tidak bisa ditekan!");
    return 1;
}