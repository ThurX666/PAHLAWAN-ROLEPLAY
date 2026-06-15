YCMD:editrsign(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9)
		return PermissionError(playerid);
	
	if(AccountData[playerid][EditingRSignID] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sekarang berada di dalam mode editing!");

	new id;
	if(sscanf(params, "i", id)) return SUM(playerid, "/editrsign [id]");
	if(!Iter_Contains(RSigns, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID road sign invalid!");
	if(!IsPlayerInRangeOfPoint(playerid, 30.0, RoadsignData[id][rsignX], RoadsignData[id][rsignY], RoadsignData[id][rsignZ])) 
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan road sign ID tersebut!");
	if(RSign_BeingEdited(id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Road Sign tersebut sedang diedit oleh admin lain!");

	AccountData[playerid][EditingRSignID] = id;
	EditDynamicObject(playerid, RoadsignData[id][rsignObject]);
	return 1;
}

YCMD:addrsign(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 9)
		return PermissionError(playerid);
		
	new id = Iter_Free(RSigns);
	if(id <= -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah maksimum road sign telah tercapai!");

    ShowModelSelectionMenu(playerid, ObjRSign, "Pilih Object!");
	return 1;
}

YCMD:removersign(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9)
		return PermissionError(playerid);
		
	new id, query[512];
	if(sscanf(params, "i", id)) return SUM(playerid, "/removersign [id]");
	if(!Iter_Contains(RSigns, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID road sign invalid!");
	
	if(RSign_BeingEdited(id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Road Sign tersebut sedang diedit oleh admin lain!");
	
	if(DestroyDynamicObject(RoadsignData[id][rsignObject]))
		RoadsignData[id][rsignObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
	
	RoadsignData[id][rsignX] = RoadsignData[id][rsignY] = RoadsignData[id][rsignZ] = RoadsignData[id][rsignRX] = RoadsignData[id][rsignRY] = RoadsignData[id][rsignRZ] = 0.0;
	RoadsignData[id][rsignInt] = RoadsignData[id][rsignWorld] = 0;
	RoadsignData[id][rsignObjID] = -1;
	Iter_Remove(RSigns, id);
	
	mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `roadsigns` WHERE `id`=%d", id);
	mysql_pquery(g_SQL, query);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has removed road sign ID: %d.", AccountData[playerid][pAdminname], id);
	return 1;
}

YCMD:gotorsign(playerid, params[], help)
{
	new id;
	if(AccountData[playerid][pAdmin] < 3)
        return PermissionError(playerid);
		
	if(sscanf(params, "d", id))
		return SUM(playerid, "/gotorsign [id]");

	if(!Iter_Contains(RSigns, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID road sign invalid!");
	
	SetPlayerPositionEx(playerid, RoadsignData[id][rsignX], RoadsignData[id][rsignY], RoadsignData[id][rsignZ], 2.0);
    SetPlayerInterior(playerid, RoadsignData[id][rsignInt]);
    SetPlayerVirtualWorld(playerid, RoadsignData[id][rsignWorld]);

	AccountData[playerid][pInDoor] = -1;
	AccountData[playerid][pInHouse] = -1;
	AccountData[playerid][pInBiz] = -1;
	return 1;
}