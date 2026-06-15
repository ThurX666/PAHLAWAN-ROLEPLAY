YCMD:adddoor(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);
	
	new did = Iter_Free(Doors), query[248];
	if(did <= -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah dynamic doors telah mencapai batas maksimum!");
	new name[128];
	if(sscanf(params, "s[128]", name)) return SUM(playerid, "/adddoor [name]");
	strcopy(DoorData[did][dName], name);
	GetPlayerPos(playerid, DoorData[did][dExtposX], DoorData[did][dExtposY], DoorData[did][dExtposZ]);
	GetPlayerFacingAngle(playerid, DoorData[did][dExtposA]);
	DoorData[did][dExtvw] = GetPlayerVirtualWorld(playerid);
	DoorData[did][dExtint] = GetPlayerInterior(playerid);
	DoorData[did][dPass][0] = EOS;
	DoorData[did][dIcon] = 19197;
	DoorData[did][dLocked] = 0;
	DoorData[did][dAdmin] = 0;
	DoorData[did][dVip] = 0;
	DoorData[did][dFaction] = 0;
	DoorData[did][dFamily] = -1;
	DoorData[did][dIntvw] = 0;
	DoorData[did][dIntint] = 0;
	DoorData[did][dIntposX] = 0;
	DoorData[did][dIntposY] = 0;
	DoorData[did][dIntposZ] = 0;
	DoorData[did][dIntposA] = 0;
	
    Doors_Rebuild(did);
	Iter_Add(Doors, did);

	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `doors` SET `ID`=%d, `extvw`=%d, `extint`=%d, `extposx`='%f', `extposy`='%f', `extposz`='%f', `extposa`='%f', `name`='%e'", did, DoorData[did][dExtvw], DoorData[did][dExtint], DoorData[did][dExtposX], DoorData[did][dExtposY], DoorData[did][dExtposZ], DoorData[did][dExtposA], name);
	mysql_pquery(g_SQL, query, "OnDoorsCreated", "ii", playerid, did);
	return 1;
}

YCMD:gotodoor(playerid, params[], help)
{
	new did;
	if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);
		
	if(sscanf(params, "d", did))
		return SUM(playerid, "/gotodoor [id]");
	if(!Iter_Contains(Doors, did)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Door ID tersebut tidak valid!");
	SetPlayerPositionEx(playerid, DoorData[did][dExtposX], DoorData[did][dExtposY], DoorData[did][dExtposZ], DoorData[did][dExtposA]);
    SetPlayerInteriorEx(playerid, DoorData[did][dExtint]);
    SetPlayerVirtualWorldEx(playerid, DoorData[did][dExtvw]);

    AccountData[playerid][pInDoor] = -1;
	AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
	AccountData[playerid][pInRusun] = -1;
    AccountData[playerid][pInGudang] = -1;
	return 1;
}

YCMD:editdoor(playerid, params[], help)
{
    static
        did,
        type[24],
        string[128];

    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    if(sscanf(params, "ds[24]S()[128]", did, type, string)) return SUM(playerid, "/editdoor [id] [type]~n~location, interior, password, name, locked, admin, vip, faction, family, virtual, pickup, remove");
	
    if(!Iter_Contains(Doors, did)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Door ID tersebut tidak valid!");

    if(!strcmp(type, "location", true))
    {
		GetPlayerPos(playerid, DoorData[did][dExtposX], DoorData[did][dExtposY], DoorData[did][dExtposZ]);
		GetPlayerFacingAngle(playerid, DoorData[did][dExtposA]);

        DoorData[did][dExtvw] = GetPlayerVirtualWorld(playerid);
		DoorData[did][dExtint] = GetPlayerInterior(playerid);
        Doors_Save(did);
		Doors_Refresh(did);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set exterior location for Doors ID: %d.", AccountData[playerid][pAdminname], did);
    }
    else if(!strcmp(type, "interior", true))
    {
        GetPlayerPos(playerid, DoorData[did][dIntposX], DoorData[did][dIntposY], DoorData[did][dIntposZ]);
		GetPlayerFacingAngle(playerid, DoorData[did][dIntposA]);

        DoorData[did][dIntvw] = GetPlayerVirtualWorld(playerid);
		DoorData[did][dIntint] = GetPlayerInterior(playerid);
        Doors_Save(did);
		Doors_Refresh(did);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set interior location for Doors ID: %d.", AccountData[playerid][pAdminname], did);
    }
	else if(!strcmp(type, "password", true))
    {
        new password[32];

        if(sscanf(string, "s[32]", password)) return SUM(playerid, "/editdoor [id] [password] [entrance pass]~n~Enter 'none' to disable the door password!");

        strcopy(DoorData[did][dPass], password);
        
        if(!strcmp(password, "none", true)) 
        {
            DoorData[did][dPass][0] = EOS;
        }
        Doors_Save(did);
		Doors_Refresh(did);
        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set a password for Doors ID: %d as \"%s\"", AccountData[playerid][pAdminname], did, password);
    }
	else if(!strcmp(type, "name", true))
    {
        new name[128];

        if(sscanf(string, "s[128]", name))
            return SUM(playerid, "/editdoor [id] [name] [new name]");

        strcopy(DoorData[did][dName], name);

        Doors_Save(did);
		Doors_Refresh(did);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set a name for Doors ID: %d as \"%s\".", AccountData[playerid][pAdminname], did, name);
    }
	else if(!strcmp(type, "locked", true))
    {
        new locked;

        if(sscanf(string, "d", locked))
            return SUM(playerid, "/editdoor [id] [locked] [locked 0/1]");

        if(locked < 0 || locked > 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Use 0 to unlock, 1 to lock!");

        DoorData[did][dLocked] = locked;
        Doors_Save(did);
		Doors_Refresh(did);

        if(locked) {
            SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s locked exterior Doors ID: %d.", AccountData[playerid][pAdminname], did);
        } else {
            SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s unlocked exterior Doors ID: %d.", AccountData[playerid][pAdminname], did);
        }
    }
	else if(!strcmp(type, "admin", true))
    {
        new level;

        if(sscanf(string, "d", level))
            return SUM(playerid, "/editdoor [id] [admin] [level]");

        if(level < 0 || level > 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Level admin 0 - 6!");

        DoorData[did][dAdmin] = level;
        Doors_Save(did);
		Doors_Refresh(did);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set Doors ID: %d only for admin level %d.", AccountData[playerid][pAdminname], did, level);
    }
	else if(!strcmp(type, "vip", true))
    {
        new level;

        if(sscanf(string, "d", level))
            return SUM(playerid, "/editdoor [id] [VIP] [level]");

        if(level < 0 || level > 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Level VIP 0 - 3!");

        DoorData[did][dVip] = level;
        Doors_Save(did);
		Doors_Refresh(did);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set Doors ID: %d only for VIP level %d.", AccountData[playerid][pAdminname], did, level);
    }
	else if(!strcmp(type, "faction", true))
    {
        new fid;

        if(sscanf(string, "d", fid))
            return SUM(playerid, "/editdoor [id] [faction] [faction id]");

        if(fid < 0 || fid > MAX_FACTIONS - 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Faction ID!");

        DoorData[did][dFaction] = fid;
        Doors_Save(did);
		Doors_Refresh(did);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set Doors ID: %d only for faction ID: %d.", AccountData[playerid][pAdminname], did, fid);
    }
	else if(!strcmp(type, "family", true))
    {
        new fid;

        if(sscanf(string, "d", fid))
            return SUM(playerid, "/editdoor [id] [family] [family id]");

        if(fid < -1 || fid > 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Masukkan family ID antara -1 dan 100!");

        DoorData[did][dFamily] = fid;
        Doors_Save(did);
		Doors_Refresh(did);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set Doors ID: %d only for family ID %d.", AccountData[playerid][pAdminname], did, fid);
    }
    else if(!strcmp(type, "virtual", true))
    {
        new worldid;

        if(sscanf(string, "d", worldid))
            return SUM(playerid, "/editdoor [id] [virtual] [interior world]");

        DoorData[did][dExtvw] = worldid;

        Doors_Save(did);
		Doors_Refresh(did);
        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set the virtual world for interior Doors ID: %d to %d.", AccountData[playerid][pAdminname], did, worldid);
    }
	else if(!strcmp(type, "pickup", true))
    {
        new pckdoor;

        if(sscanf(string, "d", pckdoor))
            return SUM(playerid, "/editdoor [id] [pickup] [pickupid]");

        DoorData[did][dIcon] = pckdoor;

        Doors_Save(did);
		Doors_Refresh(did);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s changed the pickup shape for Doors ID: %d to \"%d\".", AccountData[playerid][pAdminname], did, pckdoor);
    }
	else if(!strcmp(type, "remove", true))
    {
		if(DestroyDynamic3DTextLabel(DoorData[did][dLabelext]))
            DoorData[did][dLabelext] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

		if(DestroyDynamicPickup(DoorData[did][dPickupext]))
            DoorData[did][dPickupext] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

		if(DestroyDynamic3DTextLabel(DoorData[did][dLabelint]))
            DoorData[did][dLabelint] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

		if(DestroyDynamicPickup(DoorData[did][dPickupint]))
            DoorData[did][dPickupint] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;
			
		DoorData[did][dExtposX] = 0;
		DoorData[did][dExtposY] = 0;
		DoorData[did][dExtposZ] = 0;
		DoorData[did][dExtposA] = 0;
		DoorData[did][dExtvw] = 0;
		DoorData[did][dExtint] = 0;
		DoorData[did][dPass][0] = EOS;
		DoorData[did][dIcon] = 0;
		DoorData[did][dLocked] = 0;
		DoorData[did][dAdmin] = 0;
		DoorData[did][dVip] = 0;
		DoorData[did][dFaction] = 0;
		DoorData[did][dFamily] = -1;
		DoorData[did][dIntvw] = 0;
		DoorData[did][dIntint] = 0;
		DoorData[did][dIntposX] = 0;
		DoorData[did][dIntposY] = 0;
		DoorData[did][dIntposZ] = 0;
		DoorData[did][dIntposA] = 0;

		DoorData[did][dPickupext] = -1;
		DoorData[did][dPickupint] = -1;
		
		Iter_Remove(Doors, did);
		new query[128];
		mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `doors` WHERE `ID`=%d", did);
		mysql_pquery(g_SQL, query);
        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has deleted Doors ID: %d.", AccountData[playerid][pAdminname], did);
	}
    return 1;
}