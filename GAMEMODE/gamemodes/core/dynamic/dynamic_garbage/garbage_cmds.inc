YCMD:addgarbage(playerid, params[], help)
{
	new type, id = Iter_Free(Garbages), Float:gx, Float:gy, 
    Float:gz, query[512];

    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

	if (sscanf(params, "d", type))
	{
	    SUM(playerid, "/addgarbage [type]~n~1. Dumpster (1) | 2. Dumpster (2) | 3. Dumpster (3) | 4. Dumpster (4) | 5. Trash Can");
		return 1;
	}
	if (type < 1 || type > 5)
	    return ShowTDN(playerid, NOTIFICATION_ERROR, "Pilih type 1 - 5!");
    
    if (id == -1)
	    return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah dynamic Garbage Bins telah mencapai batas maksimum!");

    // Create
    GetPlayerPos(playerid, gx, gy, gz);
    switch (type) 
    {
        case 1: GarbageData[id][garbageModel] = 1236;
		case 2: GarbageData[id][garbageModel] = 1227;
		case 3: GarbageData[id][garbageModel] = 1344;
		case 4: GarbageData[id][garbageModel] = 1345;
        case 5: GarbageData[id][garbageModel] = 1300;
    }
    GarbageData[id][garbagePos][0] = gx;
    GarbageData[id][garbagePos][1] = gy;
    GarbageData[id][garbagePos][2] = gz;
    GarbageData[id][garbagePos][3] = GarbageData[id][garbagePos][4] = GarbageData[id][garbagePos][5] = 0.0;
    GarbageData[id][garbageInterior] = GetPlayerInterior(playerid);
    GarbageData[id][garbageWorld] = GetPlayerVirtualWorld(playerid);

	GarbageData[id][garbageText3D] = CreateDynamic3DTextLabel("[Tempat Sampah]\n"WHITE"Tekan "RED"'Y' "WHITE"untuk pungut sampah!\nTekan "RED"ALT "WHITE"untuk bersembunyi\nDrop item disini untuk membuangnya!", X11_CYAN, GarbageData[id][garbagePos][0], GarbageData[id][garbagePos][1], GarbageData[id][garbagePos][2]+1.5, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, GarbageData[id][garbageWorld], GarbageData[id][garbageInterior], -1, 10.0, -1, 0);
	GarbageData[id][garbageObject] = CreateDynamicObject(GarbageData[id][garbageModel], GarbageData[id][garbagePos][0], GarbageData[id][garbagePos][1], GarbageData[id][garbagePos][2], GarbageData[id][garbagePos][3], GarbageData[id][garbagePos][4], GarbageData[id][garbagePos][5], GarbageData[id][garbageWorld], GarbageData[id][garbageInterior], -1, 100.0, 100.0);
    Iter_Add(Garbages, id);

	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `garbages` SET `id`=%d, `garbageModel`=%d, `garbageX`='%f', `garbageY`='%f', `garbageZ`='%f', `garbageRx`='%f', `garbageRy`='%f', `garbageRz`='%f', `garbageInterior`=%d, `garbageWorld`=%d", id, GarbageData[id][garbageModel], GarbageData[id][garbagePos][0], GarbageData[id][garbagePos][1], GarbageData[id][garbagePos][2], GarbageData[id][garbagePos][3], GarbageData[id][garbagePos][4], GarbageData[id][garbagePos][5], GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
	mysql_pquery(g_SQL, query, "OnGarbageCreated", "ii", playerid, id);
	return 1;
}

YCMD:removegarbage(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

	new id, strgbg[128];
	if(sscanf(params, "i", id)) return SUM(playerid, "/removegarbage [id]");
	if(!Iter_Contains(Garbages, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Garbage Bin ID!");

    if(Garbage_BeingEdited(id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Garbage Bin ID tersebut sedang diedit oleh admin lain!");

    if(DestroyDynamic3DTextLabel(GarbageData[id][garbageText3D]))
        GarbageData[id][garbageText3D] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    if(DestroyDynamicObject(GarbageData[id][garbageObject]))
        GarbageData[id][garbageObject] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;

    GarbageData[id][garbagePos][0] = GarbageData[id][garbagePos][1] = GarbageData[id][garbagePos][2] = GarbageData[id][garbagePos][3] = GarbageData[id][garbagePos][4] = GarbageData[id][garbagePos][5] = 0.0;
    GarbageData[id][garbageInterior] = GarbageData[id][garbageWorld] = 0;
    Iter_Remove(Garbages, id);

    mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `garbages` WHERE `id` = %d", id);
    mysql_pquery(g_SQL, strgbg);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s removed Garbage Bin with ID: %d.", AccountData[playerid][pAdminname], id);
	return 1;
}

YCMD:gotogarbage(playerid, params[], help)
{
	new id;
	if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);
		
	if(sscanf(params, "d", id))
		return SUM(playerid, "/gotogarbage [id]");

	if(!Iter_Contains(Garbages, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Garbage Bin ID!");
	SetPlayerPositionEx(playerid, GarbageData[id][garbagePos][0], GarbageData[id][garbagePos][1], GarbageData[id][garbagePos][2], GarbageData[id][garbagePos][5]);
    SetPlayerInteriorEx(playerid, GarbageData[id][garbageInterior]);
    SetPlayerVirtualWorldEx(playerid, GarbageData[id][garbageWorld]);

    AccountData[playerid][pInDoor] = -1;
	AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
	AccountData[playerid][pInRusun] = -1;
    AccountData[playerid][pInGudang] = -1;
	return 1;
}

YCMD:editgarbage(playerid, params[], help)
{
	new id, type[24], stredit[128]; 

    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

	if(sscanf(params, "ds[24]S()[128]", id, type, stredit))
    {
        SUM(playerid, "/editgarbage [id] [type]~n~pos, interior, virtual");
        return 1;
    }

	if(!Iter_Contains(Garbages, id)) 
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Garbage Bin ID!");

	if(!IsPlayerInRangeOfPoint(playerid, 30.0, GarbageData[id][garbagePos][0], GarbageData[id][garbagePos][1], GarbageData[id][garbagePos][2])) 
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengat Garbage Bin ID tersebut!");

	if(!strcmp(type, "pos", true))
    {
		if(AccountData[playerid][EditingGarbageID] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang berada di dalam mode editing!");

        if(!IsPlayerInRangeOfPoint(playerid, 30.0, GarbageData[id][garbagePos][0], GarbageData[id][garbagePos][1], GarbageData[id][garbagePos][2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan tempat sampah tersebut!");
        if(Garbage_BeingEdited(id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "That Garbage Bin ID sedang diedit oleh admin lain!");

		AccountData[playerid][EditingGarbageID] = id;
		EditDynamicObject(playerid, GarbageData[id][garbageObject]);

		SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s edited the position of Garbage Bin ID: %d.", AccountData[playerid][pAdminname], id);
	}

	else if(!strcmp(type, "interior", true))
    {
        GetPlayerPos(playerid, GarbageData[id][garbagePos][0], GarbageData[id][garbagePos][1], GarbageData[id][garbagePos][2]);
		GetPlayerFacingAngle(playerid, GarbageData[id][garbagePos][5]);

        GarbageData[id][garbageWorld] = GetPlayerVirtualWorld(playerid);
		GarbageData[id][garbageInterior] = GetPlayerInterior(playerid);
        Garbage_Save(id);
		Garbage_Refresh(id);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set the interior status of Garbage Bin ID: %d.", AccountData[playerid][pAdminname], id);
    }

	else if(!strcmp(type, "virtual", true))
    {
        new worldid;

        if(sscanf(stredit, "d", worldid))
            return SUM(playerid, "/editgarbage [id] [virtual] [interior world]");

        GarbageData[id][garbageWorld] = worldid;

        Garbage_Save(id);
		Garbage_Refresh(id);
        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set the virtual world for Garbage Bin ID: %d to %d.", AccountData[playerid][pAdminname], id, worldid);
    }
	return 1;
}