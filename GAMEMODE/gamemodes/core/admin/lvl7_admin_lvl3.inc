YCMD:togooc(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 7)
        return PermissionError(playerid);

    switch(TogOOC)
    {
        case false:
        {
            SendClientMessageToAllEx(Y_PAHLAWAN, "<!> "WHITE"Pengurus "RED"%s "WHITE"telah membuka chat global OOC.", AccountData[playerid][pAdminname]);
            TogOOC = true;

            //format(sclstr, sizeof(sclstr), "%s(%d) [%s] used the '/togooc' command\n\
            //> opened global OOC chat", AccountData[playerid][pAdminname], playerid, AccountData[playerid][pUCP]);
            //CallLocalFunction("StaffCommandLog", "is", playerid, sclstr);
        }
        case true:
        {
            SendClientMessageToAllEx(Y_PAHLAWAN, "<!> "WHITE"Pengurus "RED"%s "WHITE"telah menutup chat global OOC.", AccountData[playerid][pAdminname]);
            TogOOC = false;

            //format(sclstr, sizeof(sclstr), "%s(%d) [%s] used the '/togooc' command\n\
            //> closed global OOC chat", AccountData[playerid][pAdminname], playerid, AccountData[playerid][pUCP]);
            //CallLocalFunction("StaffCommandLog", "is", playerid, sclstr);
        }
    }
    return 1;
}

YCMD:ufo(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 7)
	    return PermissionError(playerid);

    if(!IsPlayerInAnyVehicle(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di dalam kendaraan!");

    new vid = GetPlayerVehicleID(playerid);
    if(GetVehicleModel(vid) == 520)
    {
        if(DestroyDynamicObject(UfoObjID[vid][0]))
            UfoObjID[vid][0] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
        
        if(DestroyDynamicObject(UfoObjID[vid][1]))
            UfoObjID[vid][1] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

        LinkVehicleToInterior(vid, 1);
        UfoObjID[vid][0] = CreateDynamicObject(18846, 0.0,0.0,-1000.0,0.0,0.0,0.0, -1, -1, -1, 200.00, 200.00, -1);
        AttachDynamicObjectToVehicle(UfoObjID[vid][0], vid, 0.000, -0.760, -1.280, 0.000, 0.000, 0.000);
        UfoObjID[vid][1] = CreateDynamicObject(19134, 0.0,0.0,-1000.0,0.0,0.0,0.0, -1, -1, -1, 200.00, 200.00, -1);
        AttachDynamicObjectToVehicle(UfoObjID[vid][1], vid, 0.000, -0.740, 0.679, 0.000, 90.000, 90.000);
    }
    return 1;
}

YCMD:dufo(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 7)
	    return PermissionError(playerid);
    
    if(!IsPlayerInAnyVehicle(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di dalam kendaraan!");

    new vid = GetPlayerVehicleID(playerid);
    if(GetVehicleModel(vid) == 520)
    {
        if(DestroyDynamicObject(UfoObjID[vid][0]))
            UfoObjID[vid][0] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
        
        if(DestroyDynamicObject(UfoObjID[vid][1]))
            UfoObjID[vid][1] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
        
        LinkVehicleToInterior(vid, 0);
    }
    return 1;
}

YCMD:setfaction(playerid, params[], help)
{
	new fid, rank, otherid;
    if(AccountData[playerid][pAdmin] < 7)
        return PermissionError(playerid);

    if(sscanf(params, "udd", otherid, fid, rank))
    {
		SUM(playerid, "/setfaction [playerid] [faction id] [rank] faction ID 0 untuk Kick");
        return 1;
    }

	if(!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    if(fid < 0 || fid > MAX_FACTIONS - 1)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid faction ID!");
	
	switch(fid)
	{
		case 0:
		{
			if(rank != 0)
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Set rank 0 untuk mengeluarkan player dari faction!");
		}
		case 1: //polda
		{
			if(rank < 1 || rank > 16)
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Polisi valid rank is 1- 16.");
		}
		case 2: //LSFD
		{
			if(rank < 1 || rank > 8)
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Paramedis valid rank is 1 - 8!");
		}
		case 3: //Burgershot
		{
			if(rank < 1 || rank > 10)
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Putri Deli valid rank is 1 - 10!");
		}
		case 4: //government
		{
			if(rank < 1 || rank > 7)
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemerintah valid rank is 1- 7.");
		}
		case 5: //bennys
		{
			if(rank < 1 || rank > 6)
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Bennys valid rank is 1 - 6!");
		}
		case 6: //Uber
		{
			if(rank < 1 || rank > 5)
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Uber valid rank is 1 - 5!");
		}
		case 7: //dinarbucks
		{
			if(rank < 1 || rank > 10)
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Pinky Tiger valid rank is 1 - 10!");
		}
		case 8: //fox 11
		{
			if(rank < 1 || rank > 8)
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Pewarta valid rank is 1 - 8!");
		}
        case 9: //automax
		{
			if(rank < 1 || rank > 6)
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Automax valid rank is 1 - 6!");
		}
        case 10: //handover
		{
			if(rank < 1 || rank > 6)
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Handover valid rank is 1 - 6!");
		}
        case 11: //plus arivena
		{
			if(rank < 1 || rank > 10)
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Sri Mersing valid rank is 1 - 10!");
		}
        case 12: //texas chicken
		{
			if(rank < 1 || rank > 10)
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Texas chicken valid rank is 1 - 10!");
		}
	}

	static string[158];
	if(fid == 0)
	{
		AccountData[otherid][pFaction] = 0;
		AccountData[otherid][pFactionRank] = 0;
		AccountData[otherid][pBadge] = 0;
		format(string, sizeof(string), "AdmCmd: %s has removed you from the faction.", AccountData[playerid][pAdminname]);
		SendClientMessage(otherid, Y_LIGHTRED, string);
	}
	else
	{
		AccountData[otherid][pFaction] = fid;
		AccountData[otherid][pFactionRank] = rank;
	}
	mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_Faction` = %d, `Char_FactionRank` = %d WHERE `pID` = %d", AccountData[otherid][pFaction], AccountData[otherid][pFactionRank], AccountData[otherid][pID]);
	mysql_pquery(g_SQL, string);

	format(string, sizeof(string), "AdmCmd: %s has assigned you to the faction %s with rank %s.", AccountData[playerid][pAdminname], GetFactionName(otherid), GetRankName(otherid));
	SendClientMessage(otherid, Y_LIGHTRED, string);

	SendAdm(playerid, "You have assigned %s(%d) to the %s faction with rank %s.", AccountData[otherid][pName], otherid, GetFactionName(otherid), GetRankName(otherid));
    
	return 1;
}

YCMD:setfamily(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 7)
		return PermissionError(playerid);
	
	new otherid, fmid, frank;
	if(sscanf(params, "udd", otherid, fmid, frank)) return SUM(playerid, "/setfamily [playerid] [family id] [rank 1 - 4]");
	if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(!Iter_Contains(Fams, fmid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid family ID!");
	if(frank < 1 || frank > 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Rank hanya dapat diisi 1 atau 6!");

	AccountData[otherid][pFamily] = fmid;
	AccountData[otherid][pFamilyRank] = frank;

	static string[158];
	mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_Family` = %d, `Char_FamilyRank` = %d WHERE `pID` = %d", AccountData[otherid][pFamily], AccountData[otherid][pFamilyRank], AccountData[otherid][pID]);
	mysql_pquery(g_SQL, string);

	format(string, sizeof(string), "AdmCmd: %s has assigned you to the family %s with rank %s.", AccountData[playerid][pAdminname], GetFamilyName(fmid), GetFamilyRankName(otherid));
	SendClientMessage(otherid, Y_LIGHTRED, string);

	SendAdm(playerid, "You have assigned %s(%d) to the %s family with rank %s.", AccountData[otherid][pName], otherid, GetFamilyName(fmid), GetFamilyRankName(otherid));
	return 1;
}

YCMD:kickfamily(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 7)
		return PermissionError(playerid);
	
	new otherid;
	if(sscanf(params, "u", otherid)) return SUM(playerid, "/kickfamily [playerid]");
	if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(AccountData[otherid][pFamily] < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut bukan anggota dari family official manapun!");

	AccountData[otherid][pFamily] = -1;
	AccountData[otherid][pFamilyRank] = 0;

	static string[158];
	mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_Family` = -1, `Char_FamilyRank` = 0 WHERE `pID` = %d", AccountData[otherid][pID]);
	mysql_pquery(g_SQL, string);

	format(string, sizeof(string), "AdmCmd: %s has removed you from the family.", AccountData[playerid][pAdminname]);
	SendClientMessage(otherid, Y_LIGHTRED, string);

	SendAdm(playerid, "You have removed %s(%d) from the family.", AccountData[otherid][pName], otherid);
	return 1;
}

YCMD:playsong(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 7)
        return PermissionError(playerid);

    new songname[128], tmp[512];
    if (sscanf(params, "s[128]", songname))
        return SUM(playerid, "/playsong [link]");

    format(tmp, sizeof(tmp), "%s", songname);
    foreach(new ii : Player)
    {
        PlayAudioStreamForPlayer(ii, tmp);
        SendClientMessage(ii, Y_LIGHTRED, "AdmCmd: Gunakan '/stopsong' untuk memberhentikan musik admin.");
    }
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s used the '/playsong' command.", AccountData[playerid][pAdminname]);
    return 1;
}

YCMD:giveweap(playerid, params[], help)
{
    static
        wgunid,
        typo,
        ammo;

    new otherid;
    if(AccountData[playerid][pAdmin] < 7)
        return PermissionError(playerid);

    if (sscanf(params, "uddI(250)", otherid, wgunid, typo, ammo))
        return SUM(playerid, "/giveweap [playerid/name] [wgunid] [type: 1. admin, 2. faction, 3. player] [ammo]");

    if (otherid == INVALID_PLAYER_ID)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    if (wgunid <= 0 || wgunid > 46 || (wgunid >= 19 && wgunid <= 21))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid weapon ID!");

    if(wgunid == 40 || wgunid == 39) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid weapon ID!");
    
    if(typo < 1 || typo > 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid type (1 - 3).");
    
    if (ammo < 1 || ammo > 500)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid ammo (1 - 500).");

    if(IsAFireArm(wgunid) && AccountData[otherid][pLevel] < 5)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut harus mencapai level 5!");

    GivePlayerWeaponEx(otherid, wgunid, ammo, typo);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has given %s a %s with %d rounds.", AccountData[playerid][pAdminname], AccountData[otherid][pName], ReturnWeaponName(wgunid), ammo);

    static string[522];
    mysql_format(g_SQL, string, sizeof(string), "INSERT INTO `admin_logs` SET `Prefix` = 'giveweap', `Admin` = '%e', `AdminUCP` = '%e', `UCPTarget` = '%e'", AccountData[playerid][pAdminname], AccountData[playerid][pUCP], AccountData[otherid][pName]);
	mysql_pquery(g_SQL, string);
    return 1;
}