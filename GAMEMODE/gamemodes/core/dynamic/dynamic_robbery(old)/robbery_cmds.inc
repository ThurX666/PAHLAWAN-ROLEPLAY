YCMD:addrobbery(playerid, params[], help)
{
    new robberyid = Iter_Free(Robberies), robskin, rbrstr[522];
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);
    if(sscanf(params, "d", robskin)) return SUM(playerid, "/addrobbery [robbery skin]");

    RobberyData[robberyid][robberySkin] = robskin;
    GetPlayerPos(playerid, RobberyData[robberyid][robberyPos][0], RobberyData[robberyid][robberyPos][1], RobberyData[robberyid][robberyPos][2]);
    GetPlayerFacingAngle(playerid, RobberyData[robberyid][robberyPos][3]);
    RobberyData[robberyid][robberyWorld] = GetPlayerVirtualWorld(playerid);
    RobberyData[robberyid][robberyInterior] = GetPlayerInterior(playerid);

    RobberyData[robberyid][robberyRobbed] = false;
    RobberyData[robberyid][robberyHandsup] = false;
    RobberyData[robberyid][robberyAimTime] = -1;
    RobberyData[robberyid][robberyTime] = 0;
    RobberyData[robberyid][robberyActor] = CreateDynamicActor(RobberyData[robberyid][robberySkin], RobberyData[robberyid][robberyPos][0], RobberyData[robberyid][robberyPos][1], RobberyData[robberyid][robberyPos][2], RobberyData[robberyid][robberyPos][3], 1, 100.0, RobberyData[robberyid][robberyWorld], RobberyData[robberyid][robberyInterior], -1, 300.00, -1, 0);

    Iter_Add(Robberies, robberyid);

    mysql_format(g_SQL, rbrstr, sizeof(rbrstr), "INSERT INTO `robberies` SET `ID`=%d, `Robbery_Skin`=%d, `Robbery_X`='%f', `Robbery_Y`='%f', `Robbery_Z`='%f', `Robbery_A`='%f', \
    Robbery_World=%d, Robbery_Interior=%d", robberyid, RobberyData[robberyid][robberyActor], RobberyData[robberyid][robberyPos][0], RobberyData[robberyid][robberyPos][1], RobberyData[robberyid][robberyPos][2],
    RobberyData[robberyid][robberyPos][3], RobberyData[robberyid][robberyWorld], RobberyData[robberyid][robberyInterior]);
    mysql_pquery(g_SQL, rbrstr, "OnRobberyCreated", "ii", playerid, robberyid);
    return 1;
}

YCMD:editrobbery(playerid, params[], help)
{
    new robberyid, type[24], string[128];
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);
    if(sscanf(params, "ds[24]S()[128]", robberyid, type, string)) return SUM(playerid, "/editrobbery [id] [name]~n~pos, skin");
    if(!Iter_Contains(Robberies, robberyid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Robbery tersebut tidak valid!");

    if(!strcmp(type, "pos", true))
    {
        GetPlayerPos(playerid, RobberyData[robberyid][robberyPos][0], RobberyData[robberyid][robberyPos][1], RobberyData[robberyid][robberyPos][2]);
        GetPlayerFacingAngle(playerid, RobberyData[robberyid][robberyPos][3]);
        RobberyData[robberyid][robberyWorld] = GetPlayerVirtualWorld(playerid);
        RobberyData[robberyid][robberyInterior] = GetPlayerInterior(playerid);

        SetPlayerPos(playerid, RobberyData[robberyid][robberyPos][0]-1.0, RobberyData[robberyid][robberyPos][1], RobberyData[robberyid][robberyPos][2]);

        Robbery_Save(robberyid);
        Robbery_Refresh(robberyid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s menetapkan posisi untuk Robbery ID: %d.", AccountData[playerid][pAdminname], robberyid);
    }
    else if(!strcmp(type, "skin", true))
    {
        new robbskin;

        if(sscanf(string, "d", robbskin)) return SUM(playerid, "/editrobbery [id] [skin] [skin id]");

        if (robbskin < 0 || robbskin > 311)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid skin ID (0 - 311)");

        RobberyData[robberyid][robberySkin] = robbskin;

        Robbery_Save(robberyid);
        Robbery_Refresh(robberyid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s menetapkan Skin untuk Robbery ID: %d menjadi %d.", AccountData[playerid][pAdminname], robberyid, robbskin);
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
	SetPlayerPositionEx(playerid, RobberyData[id][robberyPos][0], RobberyData[id][robberyPos][1], RobberyData[id][robberyPos][2], -90);
    SetPlayerInteriorEx(playerid, RobberyData[id][robberyInterior]);
    SetPlayerVirtualWorldEx(playerid, RobberyData[id][robberyWorld]);

    AccountData[playerid][pInDoor] = -1;
	AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
	AccountData[playerid][pInRusun] = -1;
    AccountData[playerid][pInGudang] = -1;
	SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s teleportasi ke Robbery ID: %d.", AccountData[playerid][pAdminname], id);
	return 1;
}

YCMD:removerobbery(playerid, params[], help)
{
    new robberyid, strgbg[128];
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);
    if(sscanf(params, "d", robberyid)) return SUM(playerid, "/removerobbery [id]");
    if(!Iter_Contains(Robberies, robberyid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Robbery tersebut tidak valid!");

    RobberyData[robberyid][robberySkin] = 0;
    RobberyData[robberyid][robberyPos][0] = RobberyData[robberyid][robberyPos][1] = RobberyData[robberyid][robberyPos][2] = RobberyData[robberyid][robberyPos][3] = 0.0;
    RobberyData[robberyid][robberyWorld] = 0;
    RobberyData[robberyid][robberyInterior] = 0;

    RobberyData[robberyid][robberyRobbed] = false;
    RobberyData[robberyid][robberyHandsup] = false;
    RobberyData[robberyid][robberyAimTime] = -1;
    RobberyData[robberyid][robberyTime] = 0;

    if(DestroyDynamicActor(RobberyData[robberyid][robberyActor]))
    {
        RobberyData[robberyid][robberyActor] = STREAMER_TAG_ACTOR: INVALID_STREAMER_ID;
    }

    Iter_Remove(Robberies, robberyid);
    mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `robberies` WHERE `ID` = %d", robberyid);
    mysql_pquery(g_SQL, strgbg);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s menghapus Robbery ID: %d.", AccountData[playerid][pAdminname], robberyid);
    return 1;
}