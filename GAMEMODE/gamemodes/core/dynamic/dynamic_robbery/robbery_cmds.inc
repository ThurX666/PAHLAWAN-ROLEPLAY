YCMD:addrobbery(playerid, params[], help)
{
    new rbid = Iter_Free(Robberies);
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);
    if(rbid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah dynamic robbery sudah mencapai maksimum!");

    GetPlayerPos(playerid, RobberyData[rbid][rsafePos][0], RobberyData[rbid][rsafePos][1], RobberyData[rbid][rsafePos][2]);
    GetPlayerFacingAngle(playerid, RobberyData[rbid][rsafePos][5]);
    RobberyData[rbid][rsafePos][3] = 0.0;
    RobberyData[rbid][rsafePos][4] = 0.0;
    RobberyData[rbid][rsafeWorld] = GetPlayerVirtualWorld(playerid);
    RobberyData[rbid][rsafeInterior] = GetPlayerInterior(playerid);

    RobberyData[rbid][rsafeObject] = CreateDynamicObject(2332, RobberyData[rbid][rsafePos][0], RobberyData[rbid][rsafePos][1], RobberyData[rbid][rsafePos][2], RobberyData[rbid][rsafePos][3], RobberyData[rbid][rsafePos][4], RobberyData[rbid][rsafePos][5], RobberyData[rbid][rsafeWorld], RobberyData[rbid][rsafeInterior], -1, 30.00, 30.00, -1);
    
    Iter_Add(Robberies, rbid);

    new rbbryft[528];
    mysql_format(g_SQL, rbbryft, sizeof(rbbryft), "INSERT INTO `robberies` SET `ID`=%d, `Robbery_X`='%f', `Robbery_Y`='%f', `Robbery_Z`='%f', `Robbery_RX`='%f', `Robbery_RY`='%f', `Robbery_RZ`='%f', `Robbery_World`=%d, `Robbery_Interior`=%d",
    rbid, RobberyData[rbid][rsafePos][0], RobberyData[rbid][rsafePos][1], RobberyData[rbid][rsafePos][2], RobberyData[rbid][rsafePos][3], RobberyData[rbid][rsafePos][4], RobberyData[rbid][rsafePos][5], RobberyData[rbid][rsafeWorld], RobberyData[rbid][rsafeInterior]);
    mysql_pquery(g_SQL, rbbryft, "OnRobberyCreated", "ii", playerid, rbid);
    return 1;
}

YCMD:editrobbery(playerid, params[], help)
{
    new rbid, type[24], string[128];
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);
    if(sscanf(params, "ds[24]S()[128]", rbid, type, string)) return SUM(playerid, "/editrobbery [id] [type]~n~pos, vw, int");
    if(!Iter_Contains(Robberies, rbid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Robbery tersebut tidak valid!");
    
    if(!strcmp(type, "pos", true))
    {
        if(AccountData[playerid][EditingRobberyID] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang berada dalam mode editing!");

        if(!IsPlayerInRangeOfPoint(playerid, 30.0, RobberyData[rbid][rsafePos][0], RobberyData[rbid][rsafePos][1], RobberyData[rbid][rsafePos][2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan dynamic Robbery tersebut!");
        if(Robbery_BeingEdited(rbid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Robbery tersebut sedang diedit oleh admin lainnya!");

		AccountData[playerid][EditingRobberyID] = rbid;
		EditDynamicObject(playerid, RobberyData[rbid][rsafeObject]);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s mengedit posisi untuk Robbery ID: %d.", AccountData[playerid][pAdminname], rbid);
    }
    else if(!strcmp(type, "vw", true))
    {
        new vwid;

        if(sscanf(string, "d", vwid)) return SUM(playerid, "/editrobbery [id] [vw] [world id]");

        if(vwid < -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "World ID tersebut tidak valid!");
        RobberyData[rbid][rsafeWorld] = vwid;

        Robbery_Save(rbid);
        Robbery_Refresh(rbid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s mengedit virtual world untuk Robbery ID: %d menjadi %d.", AccountData[playerid][pAdminname], rbid, vwid);
    }
    else if(!strcmp(type, "int", true))
    {
        new intid;

        if(sscanf(string, "d", intid)) return SUM(playerid, "/editrobbery [id] [int] [interior id]");

        if(intid < -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Interior ID tersebut tidak valid!");
        RobberyData[rbid][rsafeInterior] = intid;

        Robbery_Save(rbid);
        Robbery_Refresh(rbid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s mengedit interior id untuk Robbery ID: %d menjadi %d.", AccountData[playerid][pAdminname], rbid, intid);
    }
    return 1;
}

YCMD:gotorobbery(playerid, params[], help)
{
    new id;
	if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);
		
	if(sscanf(params, "d", id))
		return SUM(playerid, "/gotorobbery [id]");

	if(!Iter_Contains(Robberies, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Robbery tersebut tidak valid!");
	SetPlayerPositionEx(playerid, RobberyData[id][rsafePos][0], RobberyData[id][rsafePos][1], RobberyData[id][rsafePos][2], -90);
    SetPlayerInteriorEx(playerid, RobberyData[id][rsafeInterior]);
    SetPlayerVirtualWorldEx(playerid, RobberyData[id][rsafeWorld]);

    AccountData[playerid][pInDoor] = -1;
	AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
	AccountData[playerid][pInRusun] = -1;
    AccountData[playerid][pInGudang] = -1;
	return 1;
}

YCMD:removerobbery(playerid, params[], help)
{
    new rbid, strgbg[128];
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);
    if(sscanf(params, "d", rbid)) return SUM(playerid, "/removerobbery [id]");
    if(!Iter_Contains(Robberies, rbid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Robbery tersebut tidak valid!");

    RobberyData[rbid][rsafePos][0] = RobberyData[rbid][rsafePos][1] = RobberyData[rbid][rsafePos][2] = RobberyData[rbid][rsafePos][3] = 0.0;
    RobberyData[rbid][rsafePos][4] = RobberyData[rbid][rsafePos][5] = 0.0;
    RobberyData[rbid][rsafeWorld] = 0;
    RobberyData[rbid][rsafeInterior] = 0;

    if(DestroyDynamicObject(RobberyData[rbid][rsafeObject]))
        RobberyData[rbid][rsafeObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

    Iter_Remove(Robberies, rbid);
    mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `robberies` WHERE `ID` = %d", rbid);
    mysql_pquery(g_SQL, strgbg);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s menghapus Robbery ID: %d.", AccountData[playerid][pAdminname], rbid);
    return 1;
}