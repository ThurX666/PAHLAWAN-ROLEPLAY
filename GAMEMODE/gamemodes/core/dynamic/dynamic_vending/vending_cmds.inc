YCMD:addvending(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9)
		return PermissionError(playerid);

    new type;
    if(sscanf(params, "d", type)) return SUM(playerid, "/addvending [type] (1. Drinks, 2. Snacks)");

    if(type < 1 || type > 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Type harus 1 atau 2");
    new vdid = Iter_Free(Vendings);

    GetPlayerPos(playerid, VendingData[vdid][venPos][0], VendingData[vdid][venPos][1], VendingData[vdid][venPos][2]);
    GetPlayerFacingAngle(playerid, VendingData[vdid][venPos][5]);

    VendingData[vdid][venPos][3] = 0.0;
    VendingData[vdid][venPos][4] = 0.0;
    VendingData[vdid][venInt] = GetPlayerInterior(playerid);
    VendingData[vdid][venWorld] = GetPlayerVirtualWorld(playerid);
    VendingData[vdid][venType] = type;

    Vending_Rebuild(vdid);
    Iter_Add(Vendings, vdid);

    static trqqry[600];
	mysql_format(g_SQL, trqqry, sizeof(trqqry), "INSERT INTO `vendings` (`ID`, `World`, `Interior`, `X`, `Y`, `Z`, `RX`, `RY`, `RZ`, `Type`) VALUES (%d, %d, %d, '%f', '%f', '%f', '%f', '%f', '%f', %d)",
	vdid, VendingData[vdid][venWorld], VendingData[vdid][venInt], VendingData[vdid][venPos][0], VendingData[vdid][venPos][1], VendingData[vdid][venPos][2], VendingData[vdid][venPos][3], VendingData[vdid][venPos][4], VendingData[vdid][venPos][5], VendingData[vdid][venType]);
	mysql_pquery(g_SQL, trqqry, "OnVendingCreated", "ii", playerid, vdid);
    return 1;
}

YCMD:editvending(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9)
		return PermissionError(playerid);

    new vdid;
    if(sscanf(params, "d", vdid)) return SUM(playerid, "/editvending [id]");

    if(!Iter_Contains(Vendings, vdid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Vending ID tidak valid!");

    if(AccountData[playerid][EditingVendingID] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang berada dalam mode editing!");

    if(!IsPlayerInRangeOfPoint(playerid, 30.0, VendingData[vdid][venPos][0], VendingData[vdid][venPos][1], VendingData[vdid][venPos][2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan vending ID tersebut!");
    if(Vending_BeingEdited(vdid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Vending ID tersebut sedang diedit oleh admin lain!");

    AccountData[playerid][EditingVendingID] = vdid;
    EditDynamicObject(playerid, VendingData[vdid][venObject]);

    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has edited vending ID: %d.", AccountData[playerid][pAdminname], vdid);
    return 1;
}

YCMD:gotovending(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9)
		return PermissionError(playerid);

    new vdid;
    if(sscanf(params, "d", vdid)) return SUM(playerid, "/editvending [id]");

    if(!Iter_Contains(Vendings, vdid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Vending ID tidak valid!");

    SetPlayerPositionEx(playerid, VendingData[vdid][venPos][0], VendingData[vdid][venPos][1], VendingData[vdid][venPos][2], VendingData[vdid][venPos][5]);
    SetPlayerInteriorEx(playerid, VendingData[vdid][venInt]);
    SetPlayerVirtualWorldEx(playerid, VendingData[vdid][venWorld]);

    AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInRusun] = -1;
    AccountData[playerid][pInGudang] = -1;
    return 1;
}

YCMD:removevending(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9)
		return PermissionError(playerid);

    new vdid;
    if(sscanf(params, "d", vdid)) return SUM(playerid, "/editvending [id]");

    if(!Iter_Contains(Vendings, vdid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Vending ID tidak valid!");

    if(Vending_BeingEdited(vdid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Vending ID tersebut sedang diedit oleh admin lainnya!");

    if(DestroyDynamicObject(VendingData[vdid][venObject]))
        VendingData[vdid][venObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
    
    if(DestroyDynamic3DTextLabel(VendingData[vdid][venLabel]))
        VendingData[vdid][venLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    VendingData[vdid][venPos][0] = VendingData[vdid][venPos][1] = VendingData[vdid][venPos][2] = VendingData[vdid][venPos][3] = VendingData[vdid][venPos][4] = VendingData[vdid][venPos][5] = 0.0;
    VendingData[vdid][venInt] = 0;
    VendingData[vdid][venWorld] = 0;
    VendingData[vdid][venType] = 0;

    Iter_Remove(Vendings, vdid);
    
    static query[144];
	mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `vendings` WHERE `id`=%d", vdid);
	mysql_pquery(g_SQL, query);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has removed vending ID: %d.", AccountData[playerid][pAdminname], vdid);
    return 1;
}