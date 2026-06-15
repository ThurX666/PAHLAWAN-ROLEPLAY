YCMD:hunt(playerid, params[], help)
{
    if(AccountData[playerid][pLevel] < 5)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda dapat memegang senjata jika sudah mencapai level 5 karakter!");

    if(IsPlayerHunting[playerid])
    {
        IsPlayerHunting[playerid] = false;
        ResetWeapon(playerid, 34);

        SendClientMessage(playerid, -1, "Anda telah keluar dari mode hunting.");
    }
    else
    {
        if(!IsPlayerInDynamicArea(playerid, HuntingZone)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di zona hunting!");

        if(!AccountData[playerid][pHasHuntingRifle]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki hunting rifle!");
        if(!PlayerHasItem(playerid, "Hunt Ammo")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki hunting ammo!");

        IsPlayerHunting[playerid] = true;
        GivePlayerWeaponEx(playerid, 34, Inventory_Count(playerid, "Hunt Ammo"), WEAPON_TYPE_PLAYER);
        SendClientMessage(playerid, -1, "Anda telah masuk ke dalam mode hunting.");
    }
    return 1;
}

YCMD:adddeer(playerid, params[], help)
{
    new deerid = Iter_Free(Deers);
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);
    if(deerid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah dynamic deer sudah mencapai batas maksimum!");
    if(!IsPlayerInDynamicArea(playerid, HuntingZone)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di zona hunting!");

    GetPlayerPos(playerid, DeerData[deerid][deerPos][0], DeerData[deerid][deerPos][1], DeerData[deerid][deerPos][2]);
    DeerData[deerid][deerPos][3] = 0.0;
    DeerData[deerid][deerPos][4] = 0.0;
    DeerData[deerid][deerPos][5] = 0.0;

    DeerData[deerid][deerObject] = CreateDynamicObject(19315, DeerData[deerid][deerPos][0], DeerData[deerid][deerPos][1], DeerData[deerid][deerPos][2], DeerData[deerid][deerPos][3], DeerData[deerid][deerPos][4], DeerData[deerid][deerPos][5], 0, 0, -1, 200.00, 200.00, HuntingZone);
    DeerData[deerid][deerLabel] = CreateDynamic3DTextLabel(""WHITE"Rusa\n"RED"Tersedia", 0xFFFFFFA6, DeerData[deerid][deerPos][0], DeerData[deerid][deerPos][1], DeerData[deerid][deerPos][2] + 1.0, 15.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 15.0, HuntingZone, 0);
    DeerData[deerid][deerShoted] = false;
    DeerData[deerid][deerConsficated] = false;
    DeerData[deerid][deerRespawnTime] = 0;

    Iter_Add(Deers, deerid);

    new dddstr[512];
    mysql_format(g_SQL, dddstr, sizeof(dddstr), "INSERT INTO `dynamic_deer` SET `ID`=%d, `X`='%f', `Y`='%f', `Z`='%f', `RX`='%f', `RY`='%f', `RZ`='%f'", deerid, DeerData[deerid][deerPos][0], DeerData[deerid][deerPos][1], DeerData[deerid][deerPos][2], DeerData[deerid][deerPos][3], DeerData[deerid][deerPos][4], DeerData[deerid][deerPos][5]);
    mysql_pquery(g_SQL, dddstr, "OnDeerCreated", "ii", playerid, deerid);
    return 1;
}

YCMD:editdeer(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new deerid;
    if(sscanf(params, "d", deerid)) return SUM(playerid, "/editdeer [id]");
    if(!Iter_Contains(Deers, deerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Deer ID tidak valid!");
    
    if(AccountData[playerid][EditingDeerID] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang berada di dalam mode editing!");

    if(!IsPlayerInRangeOfPoint(playerid, 30.0, DeerData[deerid][deerPos][0], DeerData[deerid][deerPos][1], DeerData[deerid][deerPos][2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan dynamic deer tersebut!");
    if(Deer_BeingEdited(deerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Deer tersebut sedang diedit oleh admin lain!");

    AccountData[playerid][EditingDeerID] = deerid;
    EditDynamicObject(playerid, DeerData[deerid][deerObject]);

    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s is editing the position for Deer ID: %d.", AccountData[playerid][pAdminname], deerid);
    return 1;
}

YCMD:gotodeer(playerid, params[], help)
{
    new id;
	if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);
		
	if(sscanf(params, "d", id))
		return SUM(playerid, "/gotodeer [id]");

	if(!Iter_Contains(Deers, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Deer ID tidak valid!");
	SetPlayerPositionEx(playerid, DeerData[id][deerPos][0], DeerData[id][deerPos][1], DeerData[id][deerPos][2], -90);
    SetPlayerInteriorEx(playerid, 0);
    SetPlayerVirtualWorldEx(playerid, 0);

    AccountData[playerid][pInDoor] = -1;
	AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
	AccountData[playerid][pInRusun] = -1;
    AccountData[playerid][pInGudang] = -1;
	SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s teleported to Deer ID: %d.", AccountData[playerid][pAdminname], id);
	return 1;
}

YCMD:removedeer(playerid, params[], help)
{
    new deerid, strgbg[128];
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);
    if(sscanf(params, "d", deerid)) return SUM(playerid, "/removedeer [id]");
    if(!Iter_Contains(Deers, deerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Deer ID tidak valid!");

    DeerData[deerid][deerPos][0] = DeerData[deerid][deerPos][1] = DeerData[deerid][deerPos][2] = DeerData[deerid][deerPos][3] = 0.0;
    DeerData[deerid][deerPos][4] = DeerData[deerid][deerPos][5] = 0.0;

    DeerData[deerid][deerShoted] = false;
    DeerData[deerid][deerConsficated] = false;
    DeerData[deerid][deerRespawnTime] = 0;

    if(DestroyDynamicObject(DeerData[deerid][deerObject]))
        DeerData[deerid][deerObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

    if(DestroyDynamic3DTextLabel(DeerData[deerid][deerLabel]))
        DeerData[deerid][deerLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    Iter_Remove(Deers, deerid);
    mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `dynamic_deer` WHERE `ID` = %d", deerid);
    mysql_pquery(g_SQL, strgbg);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s deleted Deer ID: %d.", AccountData[playerid][pAdminname], deerid);
    return 1;
}