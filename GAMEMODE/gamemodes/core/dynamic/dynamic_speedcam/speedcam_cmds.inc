YCMD:addsc(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9)
		return PermissionError(playerid);

    new Float:maxspeed;
    if(sscanf(params, "f", maxspeed))
		return SUM(playerid, "/addsc [max speed]");

    new spid = Iter_Free(SpeedCams), trqqry[512];

    if(spid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah dynamic speed cam telah mencapai batas maksimum!");

    GetPlayerPos(playerid, SCamData[spid][scX], SCamData[spid][scY], SCamData[spid][scZ]);

    SCamData[spid][scVw] = GetPlayerVirtualWorld(playerid);
    SCamData[spid][scInt] = GetPlayerInterior(playerid);
    SCamData[spid][scSpeed] = maxspeed;

    SCamData[spid][scVehID] = INVALID_VEHICLE_ID;
    SCamData[spid][scVehSpeed] = 0.0;

    SpeedCam_Rebuild(spid);
	Iter_Add(SpeedCams, spid);

	mysql_format(g_SQL, trqqry, sizeof(trqqry), "INSERT INTO `speedcam` (`ID`, `scvw`, `scint`, `scx`, `scy`, `scz`, `scrx`, `scry`, `scrz`, `scspeed`) VALUES (%d, %d, %d, '%f', '%f', '%f', '%f', '%f', '%f', '%f')",
	spid, SCamData[spid][scVw], SCamData[spid][scInt], SCamData[spid][scX], SCamData[spid][scY], SCamData[spid][scZ], SCamData[spid][scRX], SCamData[spid][scRY], SCamData[spid][scRZ], SCamData[spid][scSpeed]);
	mysql_pquery(g_SQL, trqqry, "OnSpeedCamCreated", "ii", playerid, spid);
    return 1;
}

YCMD:editsc(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9)
		return PermissionError(playerid);

    static id, type[24], stredit[128];
    if(sscanf(params, "ds[24]S()[128]", id, type, stredit))
        return SUM(playerid, "/editsc [id] [type] (pos, max, interior, virtual)");

    if(!Iter_Contains(SpeedCams, id)) 
		return ShowTDN(playerid, NOTIFICATION_ERROR, "ID speed cam invalid!");

    if(!strcmp(type, "pos", true))
    {
		if(AccountData[playerid][EditingSCamID] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang berada dalam mode editing!");

        if(!IsPlayerInRangeOfPoint(playerid, 30.0, SCamData[id][scX], SCamData[id][scY], SCamData[id][scZ])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan speed cam ID tersebut!");
        if(SpeedCam_BeingEdited(id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Speed cam ID tersebut sedang diedit oleh admin lain!");

		AccountData[playerid][EditingSCamID] = id;
		EditDynamicObject(playerid, SCamData[id][scObject]);

		SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has edited speed cam ID: %d.", AccountData[playerid][pAdminname], id);
	}

	else if(!strcmp(type, "max", true))
    {
		new Float:value;

        if(sscanf(stredit, "f", value))
            return SUM(playerid, "/editsc [id] [max] [value]");

        SCamData[id][scSpeed] = value;
        SpeedCam_Save(id);
		SpeedCam_Refresh(id);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has set max speed cam ID: %d to %.0f.", AccountData[playerid][pAdminname], id, value);
	}

    else if(!strcmp(type, "interior", true))
    {
        GetPlayerPos(playerid, SCamData[id][scX], SCamData[id][scY], SCamData[id][scZ]);
		GetPlayerFacingAngle(playerid, SCamData[id][scRZ]);

        SCamData[id][scVw] = GetPlayerVirtualWorld(playerid);
		SCamData[id][scInt] = GetPlayerInterior(playerid);
        SpeedCam_Save(id);
		SpeedCam_Refresh(id);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has set interior speed cam ID: %d.", AccountData[playerid][pAdminname], id);
    }

	else if(!strcmp(type, "virtual", true))
    {
        new worldid;

        if(sscanf(stredit, "d", worldid))
            return SUM(playerid, "/editsc [id] [virtual] [interior world]");

        SCamData[id][scVw] = worldid;

        SpeedCam_Save(id);
		SpeedCam_Refresh(id);
        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has set virtual world speed cam ID: %d to %d.", AccountData[playerid][pAdminname], id, worldid);
    }
    return 1;
}

YCMD:removesc(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9)
		return PermissionError(playerid);
		
	new id, query[512];
	if(sscanf(params, "i", id)) return SUM(playerid, "/removesc [id]");
	if(!Iter_Contains(SpeedCams, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID speed cam invalid!");
	
	if(SpeedCam_BeingEdited(id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Speed Cam tersebut sedang diedit oleh admin lainnya!");
	
    if(DestroyDynamicObject(SCamData[id][scObject]))
        SCamData[id][scObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
    if(DestroyDynamic3DTextLabel(SCamData[id][scLabel]))
        SCamData[id][scLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
	
	SCamData[id][scX] = SCamData[id][scY] = SCamData[id][scZ] = SCamData[id][scRX] = SCamData[id][scRY] = SCamData[id][scRZ] = 0.0;
	SCamData[id][scInt] = SCamData[id][scVw] = 0;
    SCamData[id][scSpeed] = 0.0;
	Iter_Remove(SpeedCams, id);
	
	mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `speedcam` WHERE `id`=%d", id);
	mysql_pquery(g_SQL, query);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has removed speed cam ID: %d.", AccountData[playerid][pAdminname], id);
	return 1;
}