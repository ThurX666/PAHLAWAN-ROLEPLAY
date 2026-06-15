YCMD:addbasement(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 9)
		return PermissionError(playerid);
	
	new bmid = Iter_Free(Basement), query[512];
	if(bmid == -1)  return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah dynamic basement telah mencapai batas maksimum!");
	
    new bmtype, name[128];
	if(sscanf(params, "ds[128]", bmtype, name)) return SUM(playerid, "/addbasement [type] [name]");
	
    switch(bmtype)
    {
        case 1: //basement 1
        {
            BasementData[bmid][bmIntposX] = -1746.1633;
            BasementData[bmid][bmIntposY] = 981.9204;
            BasementData[bmid][bmIntposZ] = 17.4730;
            BasementData[bmid][bmIntposA] = 270.5701;

            BasementData[bmid][bmInexitX] = -1746.0602;
            BasementData[bmid][bmInexitY] = 987.4948;
            BasementData[bmid][bmInexitZ] = 17.9581;
        }
        case 2: //basement 2
        {
            BasementData[bmid][bmIntposX] = 2486.1899;
            BasementData[bmid][bmIntposY] = 2374.8669;
            BasementData[bmid][bmIntposZ] = 6.9827;
            BasementData[bmid][bmIntposA] = 270.4950;

            BasementData[bmid][bmInexitX] = 2486.1829;
            BasementData[bmid][bmInexitY] = 2379.4070;
            BasementData[bmid][bmInexitZ] = 6.9822;
        }
    }
    strcopy(BasementData[bmid][bmName], name);
	GetPlayerPos(playerid, BasementData[bmid][bmExtposX], BasementData[bmid][bmExtposY], BasementData[bmid][bmExtposZ]);
	GetPlayerFacingAngle(playerid, BasementData[bmid][bmExtposA]);
	BasementData[bmid][bmExtvw] = GetPlayerVirtualWorld(playerid);
	BasementData[bmid][bmExtint] = GetPlayerInterior(playerid);

	BasementData[bmid][bmPass][0] = EOS;
	BasementData[bmid][bmIcon] = 19130;
	BasementData[bmid][bmLocked] = 0;
	BasementData[bmid][bmAdmin] = 0;
	BasementData[bmid][bmVip] = 0;
	BasementData[bmid][bmFaction] = 0;
	BasementData[bmid][bmFamily] = 0;

    BasementData[bmid][bmOutexitX] = 0.0;
    BasementData[bmid][bmOutexitY] = 0.0;
    BasementData[bmid][bmOutexitZ] = 0.0;

	BasementData[bmid][bmIntvw] = bmid+1;
	BasementData[bmid][bmIntint] = 0;
    
    Basement_Rebuild(bmid);
    Basement_Refresh(bmid);
	Iter_Add(Basement, bmid);

	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `basement` SET `ID`=%d, `extvw`=%d, `extint`=%d, `extposx`='%f', `extposy`='%f', `extposz`='%f', `extposa`='%f', `inexitx`='%f', `inexity`='%f', `inexitz`='%f', `name`='%e'", bmid, BasementData[bmid][bmExtvw], BasementData[bmid][bmExtint], BasementData[bmid][bmExtposX], BasementData[bmid][bmExtposY], BasementData[bmid][bmExtposZ], BasementData[bmid][bmExtposA], BasementData[bmid][bmInexitX], BasementData[bmid][bmInexitY], BasementData[bmid][bmInexitZ], name);
	mysql_pquery(g_SQL, query, "OnBasementCreated", "i", bmid);
	return 1;
}

YCMD:gotobasement(playerid, params[], help)
{
	new bmid;
	if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);
		
	if(sscanf(params, "d", bmid))
		return SUM(playerid, "/gotobasement [id]");
	if(!Iter_Contains(Basement, bmid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Basement tersebut tidak valid!");
	SetPlayerPositionEx(playerid, BasementData[bmid][bmExtposX], BasementData[bmid][bmExtposY], BasementData[bmid][bmExtposZ], BasementData[bmid][bmExtposA]);
    SetPlayerInterior(playerid, BasementData[bmid][bmExtint]);
    SetPlayerVirtualWorld(playerid, BasementData[bmid][bmExtvw]);

    AccountData[playerid][pInDoor] = -1;
	AccountData[playerid][pInHouse] = -1;
	AccountData[playerid][pInBiz] = -1;
	return 1;
}

YCMD:editbasement(playerid, params[], help)
{
    static
        bmid,
        type[24],
        string[128];

    if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);

    if(sscanf(params, "ds[24]S()[128]", bmid, type, string))
    {
        SUM(playerid, "/editbasement [id] [type]");
        SendClientMessage(playerid, X11_GRAY, "OPTION: location, interior, inexit, outexit, password, name, locked, admin, vip, faction, family, virtual");
		SendClientMessage(playerid, X11_GRAY, "OPTION: pickup, delete");
        return 1;
    }
    if((bmid < 0 || bmid >= MAX_BASEMENT))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Basement tersebut tidak valid!");
	
    if(!Iter_Contains(Basement, bmid))  return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Basement tersebut tidak valid!");

    if(!strcmp(type, "location", true))
    {
		GetPlayerPos(playerid, BasementData[bmid][bmExtposX], BasementData[bmid][bmExtposY], BasementData[bmid][bmExtposZ]);
		GetPlayerFacingAngle(playerid, BasementData[bmid][bmExtposA]);

        BasementData[bmid][bmExtvw] = GetPlayerVirtualWorld(playerid);
		BasementData[bmid][bmExtint] = GetPlayerInterior(playerid);

        Streamer_SetItemPos(STREAMER_TYPE_CP, BasementData[bmid][bmEntranceCP], BasementData[bmid][bmExtposX], BasementData[bmid][bmExtposY], BasementData[bmid][bmExtposZ]);
        Streamer_SetIntData(STREAMER_TYPE_CP, BasementData[bmid][bmEntranceCP], E_STREAMER_WORLD_ID, BasementData[bmid][bmExtvw]);
		Streamer_SetIntData(STREAMER_TYPE_CP, BasementData[bmid][bmEntranceCP], E_STREAMER_INTERIOR_ID, BasementData[bmid][bmIntint]);
        
        Basement_Save(bmid);
		Basement_Refresh(bmid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s menetapkan lokasi eksterior untuk basement ID: %d.", AccountData[playerid][pAdminname], bmid);
    }
    else if(!strcmp(type, "interior", true))
    {
        if(IsPlayerInAnyVehicle(playerid))
        {
            GetVehiclePos(playerid, BasementData[bmid][bmIntposX], BasementData[bmid][bmIntposY], BasementData[bmid][bmIntposZ]);
		    GetVehicleZAngle(playerid, BasementData[bmid][bmIntposA]);
        }
        else
        {
            GetPlayerPos(playerid, BasementData[bmid][bmIntposX], BasementData[bmid][bmIntposY], BasementData[bmid][bmIntposZ]);
		    GetPlayerFacingAngle(playerid, BasementData[bmid][bmIntposA]);
        }

        BasementData[bmid][bmIntvw] = bmid+1;
		BasementData[bmid][bmIntint] = GetPlayerInterior(playerid);

        Basement_Save(bmid);
		Basement_Refresh(bmid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s menetapkan lokasi interior untuk basement ID: %d.", AccountData[playerid][pAdminname], bmid);
    }
    else if(!strcmp(type, "inexit", true))
    {
        if(IsPlayerInAnyVehicle(playerid))
        {
            GetVehiclePos(SavingVehID[playerid], BasementData[bmid][bmInexitX], BasementData[bmid][bmInexitY], BasementData[bmid][bmInexitZ]);
        }
        else
        {
            GetPlayerPos(playerid, BasementData[bmid][bmInexitX], BasementData[bmid][bmInexitY], BasementData[bmid][bmInexitZ]);
        }

        BasementData[bmid][bmIntvw] = bmid+1;
		BasementData[bmid][bmIntint] = GetPlayerInterior(playerid);

        Streamer_SetItemPos(STREAMER_TYPE_CP, BasementData[bmid][bmExitCP], BasementData[bmid][bmInexitX], BasementData[bmid][bmInexitY], BasementData[bmid][bmInexitZ]);
        
        Basement_Save(bmid);
		Basement_Refresh(bmid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s menetapkan lokasi in-exit untuk basement ID: %d.", AccountData[playerid][pAdminname], bmid);
    }
    else if(!strcmp(type, "outexit", true))
    {
        if(IsPlayerInAnyVehicle(playerid))
        {
            GetVehiclePos(SavingVehID[playerid], BasementData[bmid][bmOutexitX], BasementData[bmid][bmOutexitY], BasementData[bmid][bmOutexitZ]);
            GetVehicleZAngle(SavingVehID[playerid], BasementData[bmid][bmOutexitA]);
        }
        else
        {
            GetPlayerPos(playerid, BasementData[bmid][bmOutexitX], BasementData[bmid][bmOutexitY], BasementData[bmid][bmOutexitZ]);
            GetPlayerFacingAngle(playerid, BasementData[bmid][bmOutexitA]);
        }

        Basement_Save(bmid);
		Basement_Refresh(bmid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s menetapkan lokasi out-exit untuk basement ID: %d.", AccountData[playerid][pAdminname], bmid);
    }
	else if(!strcmp(type, "password", true))
    {
        new password[32];

        if(sscanf(string, "s[32]", password))
        {
			SUM(playerid, "/editbasement [id] [password] [entrance pass]");
			SendClientMessage(playerid, X11_GRAY, "Masukkan 'none' untuk menonaktifkan kata sandi pada pintu!");
			return 1;
		}

        if(!strcmp(password, "none", true)) 
        {
            BasementData[bmid][bmPass][0] = EOS;
        }
        else 
        {
            strcopy(BasementData[bmid][bmPass], password);
        }
        Basement_Save(bmid);
		Basement_Refresh(bmid);
        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s membuat kata sandi untuk basement ID: %d yaitu (%s)", AccountData[playerid][pAdminname], bmid, password);
    }
	else if(!strcmp(type, "name", true))
    {
        new name[128];

        if(sscanf(string, "s[128]", name))
            return SUM(playerid, "/editbasement [id] [name] [new name]");

        strcopy(BasementData[bmid][bmName], name);

        Basement_Save(bmid);
		Basement_Refresh(bmid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s menetapkan nama untuk basement ID: %d yaitu \"%s\".", AccountData[playerid][pAdminname], bmid, name);
    }
	else if(!strcmp(type, "locked", true))
    {
        new locked;

        if(sscanf(string, "d", locked))
            return SUM(playerid, "/editbasement [id] [locked] [locked 0/1]");

        if(locked < 0 || locked > 1){
            ShowTDN(playerid, NOTIFICATION_ERROR, "Masukkan 0 atau 1!");
            return SendClientMessage(playerid, X11_GRAY, "0 untuk membuka, 1 untuk mengunci!");}

        BasementData[bmid][bmLocked] = locked;
        Basement_Save(bmid);
		Basement_Refresh(bmid);

        if(locked) {
            SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s mengunci exterior basement ID: %d.", AccountData[playerid][pAdminname], bmid);
        } else {
            SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s membuka exterior basement ID: %d.", AccountData[playerid][pAdminname], bmid);
        }
    }
	else if(!strcmp(type, "admin", true))
    {
        new level;

        if(sscanf(string, "d", level))
            return SUM(playerid, "/editbasement [id] [admin] [level]");

        if(level < 0 || level > 6)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Masukkan 0 - 6 untuk level admin minimal!");

        BasementData[bmid][bmAdmin] = level;
        Basement_Save(bmid);
		Basement_Refresh(bmid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s menetapkan basement ID: %d hanya untuk admin level %d.", AccountData[playerid][pAdminname], bmid, level);
    }
	else if(!strcmp(type, "vip", true))
    {
        new level;

        if(sscanf(string, "d", level))
            return SUM(playerid, "/editbasement [id] [VIP] [level]");

        if(level < 0 || level > 3)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Masukkan 0 - 3 untuk level VIP minimal!");

        BasementData[bmid][bmVip] = level;
        Basement_Save(bmid);
		Basement_Refresh(bmid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s menetapkan basement ID: %d hanya untuk VIP level %d.", AccountData[playerid][pAdminname], bmid, level);
    }
	else if(!strcmp(type, "faction", true))
    {
        new fid;

        if(sscanf(string, "d", fid))
            return SUM(playerid, "/editbasement [id] [faction] [faction id]");

        if(fid < 0 || fid > 11)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Masukkan 0 - 11 untuk ID faction!");

        BasementData[bmid][bmFaction] = fid;
        Basement_Save(bmid);
		Basement_Refresh(bmid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s menetapkan basement ID: %d hanya untuk faction ID: %d.", AccountData[playerid][pAdminname], bmid, fid);
    }
	else if(!strcmp(type, "family", true))
    {
        new fid;

        if(sscanf(string, "d", fid))
            return SUM(playerid, "/editbasement [id] [family] [family id]");

        if(fid < 0 || fid > 9)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Masukkan 0 - 9 untuk ID family!");

        BasementData[bmid][bmFamily] = fid;
        Basement_Save(bmid);
		Basement_Refresh(bmid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s menetapkan basement ID: %d hanya untuk family ID %d.", AccountData[playerid][pAdminname], bmid, fid);
    }
    else if(!strcmp(type, "virtual", true))
    {
        new worlbmid;

        if(sscanf(string, "d", worlbmid))
            return SUM(playerid, "/editbasement [id] [virtual] [interior world]");

        BasementData[bmid][bmExtvw] = worlbmid;

        Basement_Save(bmid);
		Basement_Refresh(bmid);
        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s menetapkan virtual world untuk interior basement ID: %d menjadi %d.", AccountData[playerid][pAdminname], bmid, worlbmid);
    }
	else if(!strcmp(type, "pickup", true))
    {
        new pckbmt;

        if(sscanf(string, "d", pckbmt))
            return SUM(playerid, "/editbasement [id] [pickup] [pickupid]");

        BasementData[bmid][bmIcon] = pckbmt;

        Basement_Save(bmid);
		Basement_Refresh(bmid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s mengubah bentuk pickup dari basement ID: %d menjadi \"%d\".", AccountData[playerid][pAdminname], bmid, pckbmt);
    }
	else if(!strcmp(type, "remove", true))
    {
		if(DestroyDynamic3DTextLabel(BasementData[bmid][bmLabelext]))
            BasementData[bmid][bmLabelext] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
		if(DestroyDynamicPickup(BasementData[bmid][bmPickupext]))
            BasementData[bmid][bmPickupext] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;
		if(DestroyDynamic3DTextLabel(BasementData[bmid][bmLabelexit]))
            BasementData[bmid][bmLabelexit] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
		if(DestroyDynamicPickup(BasementData[bmid][bmPickupexit]))
            BasementData[bmid][bmPickupexit] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;
        if(DestroyDynamicCP(BasementData[bmid][bmEntranceCP]))
            BasementData[bmid][bmEntranceCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        if(DestroyDynamicCP(BasementData[bmid][bmExitCP]))
            BasementData[bmid][bmExitCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
			
		BasementData[bmid][bmExtposX] = 0;
		BasementData[bmid][bmExtposY] = 0;
		BasementData[bmid][bmExtposZ] = 0;
		BasementData[bmid][bmExtposA] = 0;
		BasementData[bmid][bmExtvw] = 0;
		BasementData[bmid][bmExtint] = 0;
        BasementData[bmid][bmName][0] = EOS;
        BasementData[bmid][bmPass][0] = EOS;
		BasementData[bmid][bmIcon] = 0;
		BasementData[bmid][bmLocked] = 0;
		BasementData[bmid][bmAdmin] = 0;
		BasementData[bmid][bmVip] = 0;
		BasementData[bmid][bmFaction] = 0;
		BasementData[bmid][bmFamily] = -1;

		BasementData[bmid][bmIntvw] = 0;
		BasementData[bmid][bmIntint] = 0;

		BasementData[bmid][bmIntposX] = 0;
		BasementData[bmid][bmIntposY] = 0;
		BasementData[bmid][bmIntposZ] = 0;
		BasementData[bmid][bmIntposA] = 0;

        BasementData[bmid][bmInexitX] = 0;
		BasementData[bmid][bmInexitY] = 0;
		BasementData[bmid][bmInexitZ] = 0;

        BasementData[bmid][bmOutexitX] = 0;
		BasementData[bmid][bmOutexitY] = 0;
		BasementData[bmid][bmOutexitZ] = 0;
		BasementData[bmid][bmOutexitA] = 0;
		
		Iter_Remove(Basement, bmid);
		new query[144];
		mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `basement` WHERE `ID`=%d", bmid);
		mysql_pquery(g_SQL, query);
        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s telah menghapus basement ID: %d.", AccountData[playerid][pAdminname], bmid);
	}
    return 1;
}