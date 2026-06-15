YCMD:addrental(playerid, params[], help)
{
    new brid = Iter_Free(Rentals), query[522], name[64];

    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    if(sscanf(params, "s[64]", name)) return SUM(playerid, "/addrental [name]");

    if(brid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah dynamic rental telah mencapai batas maksimum!");

    GetPlayerPos(playerid, RentalData[brid][Pos][0], RentalData[brid][Pos][1], RentalData[brid][Pos][2]);

    GetPlayerPos(playerid, RentalData[brid][SpawnPos][0], RentalData[brid][SpawnPos][1], RentalData[brid][SpawnPos][2]);
    GetPlayerFacingAngle(playerid, RentalData[brid][SpawnPos][3]);
    RentalData[brid][Model][0] = 462;
    RentalData[brid][Model][1] = 586;
    RentalData[brid][Cost][0] = 5000;
    RentalData[brid][Cost][1] = 10000;
    
    strcopy(RentalData[brid][Name], name);
    RentalData[brid][World] = GetPlayerVirtualWorld(playerid);
    RentalData[brid][Interior] = GetPlayerInterior(playerid);

    static string[258];
    format(string, sizeof(string), "[Sewa Kendaraan]\n"CYAN"%s\n"GREEN"[Y] "WHITE"untuk membuka menu rental", RentalData[brid][Name]);

    RentalData[brid][Pickup] = CreateDynamicPickup(1239, 23, RentalData[brid][Pos][0], RentalData[brid][Pos][1], RentalData[brid][Pos][2], RentalData[brid][World], RentalData[brid][Interior], -1, 30.00, -1, 0);
    RentalData[brid][Label] = CreateDynamic3DTextLabel(string, 0xc0c0c8A6, RentalData[brid][Pos][0], RentalData[brid][Pos][1], RentalData[brid][Pos][2]+0.85, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, RentalData[brid][World], RentalData[brid][Interior], -1, 10.00, -1, 0);

    Iter_Add(Rentals, brid);

    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `rentals` (`ID`, `Name`, `Model1`, `Model2`, `Cost1`, `Cost2`, `PosX`, `PosY`, `PosZ`, `SpawnX`, `SpawnY`, `SpawnZ`, `SpawnA`, `World`, `Interior`) VALUES (%d, '%e', %d, %d, %d, %d, '%f', '%f', '%f', '%f', '%f', '%f', '%f', %d, %d)", brid, RentalData[brid][Name], RentalData[brid][Model][0], RentalData[brid][Model][1], RentalData[brid][Cost][0], RentalData[brid][Cost][1], RentalData[brid][Pos][0], RentalData[brid][Pos][1], RentalData[brid][Pos][2], RentalData[brid][SpawnPos][0], RentalData[brid][SpawnPos][1], RentalData[brid][SpawnPos][2], RentalData[brid][SpawnPos][3], RentalData[brid][World], RentalData[brid][Interior]);
	mysql_pquery(g_SQL, query, "OnRentalCreated", "ii", playerid, brid);
    return 1;
}

YCMD:editrental(playerid, params[], help)
{
    static
        brid,
        type[24],
        string[128];

    if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);

    if(sscanf(params, "ds[24]S()[128]", brid, type, string)) return SUM(playerid, "/editrental [id] [type] (pos, model1, model2, cost1, cost2, spawn)");
	
    if(!Iter_Contains(Rentals, brid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Rental ID tersebut tidak valid!");

    if(!strcmp(type, "pos", true))
    {
		GetPlayerPos(playerid, RentalData[brid][Pos][0], RentalData[brid][Pos][1], RentalData[brid][Pos][2]);

        RentalData[brid][World] = GetPlayerVirtualWorld(playerid);
		RentalData[brid][Interior] = GetPlayerInterior(playerid);
        Rental_Save(brid);
		Rental_Refresh(brid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set the position for Rental ID: %d.", AccountData[playerid][pAdminname], brid);
    }
    else if(!strcmp(type, "cost1", true))
    {
        new cost;

        if(sscanf(string, "d", cost))
            return SUM(playerid, "/editrental [id] [cost1] [price 1]");

        if(cost < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Harga tidak dapat kurang dari 0!");

        RentalData[brid][Cost][0] = cost;

        Rental_Save(brid);
		Rental_Refresh(brid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set price 1 for Rental ID: %d to $%s.", AccountData[playerid][pAdminname], brid, FormatMoney(cost));
    }
    else if(!strcmp(type, "cost2", true))
    {
        new cost2;

        if(sscanf(string, "d", cost2))
            return SUM(playerid, "/editrental [id] [cost2] [price 2]");

        if(cost2 < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Harga tidak dapat kurang dari 0!");

        RentalData[brid][Cost][1] = cost2;

        Rental_Save(brid);
		Rental_Refresh(brid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set price 2 for Rental ID: %d to $%s.", AccountData[playerid][pAdminname], brid, FormatMoney(cost2));
    }
    else if(!strcmp(type, "model1", true))
    {
        new mdl;

        if(sscanf(string, "d", mdl))
            return SUM(playerid, "/editrental [id] [model1] [modelid]");

        if(mdl < 400  || mdl > 611) return ShowTDN(playerid, NOTIFICATION_ERROR, "Model ID berkisar di antara 400 - 611");

        RentalData[brid][Model][0] = mdl;

        Rental_Save(brid);
		Rental_Refresh(brid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set model 1 for Rental ID: %d to %d.", AccountData[playerid][pAdminname], brid, mdl);
    }
    else if(!strcmp(type, "model2", true))
    {
        new mdl;

        if(sscanf(string, "d", mdl))
            return SUM(playerid, "/editrental [id] [model2] [modelid]");

        if(mdl < 400 || mdl > 611) return ShowTDN(playerid, NOTIFICATION_ERROR, "Model ID berkisar di antara 400 - 611");

        RentalData[brid][Model][1] = mdl;

        Rental_Save(brid);
		Rental_Refresh(brid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set model 2 for Rental ID: %d to %d.", AccountData[playerid][pAdminname], brid, mdl);
    }
    else if(!strcmp(type, "spawn", true))
    {
        if(IsPlayerInAnyVehicle(playerid))
        {
            new vid;
            GetVehiclePos(vid, RentalData[brid][SpawnPos][0],RentalData[brid][SpawnPos][1], RentalData[brid][SpawnPos][2]);
            GetVehicleZAngle(vid, RentalData[brid][SpawnPos][3]);
        }
        else
        {
            GetPlayerPos(playerid, RentalData[brid][SpawnPos][0],RentalData[brid][SpawnPos][1], RentalData[brid][SpawnPos][2]);
            GetPlayerFacingAngle(playerid, RentalData[brid][SpawnPos][3]);
        }

        Rental_Save(brid);
		Rental_Refresh(brid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set spawn location Rental ID: %d.", AccountData[playerid][pAdminname], brid);
    }
    return 1;
}

YCMD:removerental(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new brid, strgbg[512];

    if(sscanf(params, "d", brid)) return SUM(playerid, "/removerental [id]");

    if(!Iter_Contains(Rentals, brid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Rental ID tersebut tidak valid!");

    if(DestroyDynamicPickup(RentalData[brid][Pickup]))
    {
        RentalData[brid][Pickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;
    }

    if(DestroyDynamic3DTextLabel(RentalData[brid][Label]))
    {
        RentalData[brid][Label] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
    }

    RentalData[brid][Model][0] = 0;
    RentalData[brid][Model][1] = 0;
    
    RentalData[brid][Cost][0] = 0;
    RentalData[brid][Cost][1] = 0;

    RentalData[brid][Pos][0] = 0.0;
    RentalData[brid][Pos][1] = 0.0;
    RentalData[brid][Pos][2] = 0.0;
    RentalData[brid][SpawnPos][0] = 0.0;
    RentalData[brid][SpawnPos][1] = 0.0;
    RentalData[brid][SpawnPos][2] = 0.0;
    RentalData[brid][SpawnPos][3] = 0.0;

    RentalData[brid][World] = 0;
    RentalData[brid][Interior] = 0;

    Iter_Remove(Rentals, brid);

    mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `rentals` WHERE `ID` = %d", brid);
    mysql_pquery(g_SQL, strgbg);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s removed rental with ID: %d.", AccountData[playerid][pAdminname], brid);
    return 1;
}

YCMD:gotorental(playerid, params[], help)
{
	new id;
	if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);
		
	if(sscanf(params, "d", id))
		return SUM(playerid, "/gotorental [id]");

	if(!Iter_Contains(Rentals, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Rental ID tersebut tidak valid!");
	SetPlayerPositionEx(playerid, RentalData[id][Pos][0], RentalData[id][Pos][1], RentalData[id][Pos][2], 0.0);
    SetPlayerVirtualWorldEx(playerid, RentalData[id][World]);
    SetPlayerInteriorEx(playerid, RentalData[id][Interior]);

    AccountData[playerid][pInDoor] = -1;
	AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
	AccountData[playerid][pInRusun] = -1;
    AccountData[playerid][pInGudang] = -1;
	return 1;
}