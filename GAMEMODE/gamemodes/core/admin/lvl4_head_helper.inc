YCMD:getveh(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 4)
        return PermissionError(playerid);

    new vehid, Float:posisiX, Float:posisiY, Float:posisiZ, driverid;
    if (sscanf(params, "d", vehid))
        return SUM(playerid, "/getveh [vehid] (Use /avehlist to find vehid)");

    if (vehid == INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Vehicle ID!");
    if (!IsValidVehicle(vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Vehicle ID!");
    GetPlayerPos(playerid, posisiX, posisiY, posisiZ);
    SendAdm(playerid, "You have pulled VID: %d to %s.", vehid, GetLocation(posisiX, posisiY, posisiZ));
    SetVehiclePos(vehid, posisiX, posisiY, posisiZ + 0.5);

    driverid = GetVehicleDriver(vehid);
    if (driverid != INVALID_PLAYER_ID)
        Anticheat[GetVehicleDriver(vehid)][acImmunity] = gettime() + 5;
    SetVehicleVirtualWorldEx(vehid, GetPlayerVirtualWorld(playerid));
    LinkVehicleToInteriorEx(vehid, GetPlayerInterior(playerid));
    return 1;
}

YCMD:aeject(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 4)
		return PermissionError(playerid);

	new otherid, vID;
	if (sscanf(params, "d", otherid))
	    return SUM(playerid, "/aeject [playerid]");

	if (!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

	if (!IsPlayerInAnyVehicle(otherid))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak berada di dalam kendaraan!");

	static string[144];
	vID = GetVehicleModel(GetPlayerVehicleID(otherid));
	format(string, sizeof(string), "AdmCmd: %s has forcibly ejected you from %s.", AccountData[playerid][pAdminname], GetVehicleModelName(vID));
	SendClientMessage(otherid, X11_LIGHTBLUE, string);
	SendAdm(playerid, "You have forcibly ejected %s(%d) from %s.", AccountData[otherid][pName], otherid, GetVehicleModelName(vID));
	RemovePlayerFromVehicle(otherid);

	return 1;
}

YCMD:setvw(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 4)
        return PermissionError(playerid);
	
	new jumlah, otherid;
	if(sscanf(params, "dd", otherid, jumlah))
        return SUM(playerid, "/setvw [playerid] [virtual world]");
	
	if(!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
		
	SetPlayerVirtualWorldEx(otherid, jumlah);

	static string[144];
	format(string, sizeof(string), "AdmCmd: %s has set your Virtual World ID.", AccountData[playerid][pAdminname]);
	SendClientMessage(otherid, Y_LIGHTRED, string);
	SendAdm(playerid, "You have set VWID %s(%d) - %d.", AccountData[otherid][pName], otherid, jumlah);
	
	return 1;
}

YCMD:setint(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 4)
        return PermissionError(playerid);

    new giveplayerid, int;
    if(sscanf(params, "dd", giveplayerid, int)) return SUM(playerid, "/setint [playerid] [interiorid]");

    if(!IsPlayerConnected(giveplayerid))
    	return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    SetPlayerInterior(giveplayerid, int);

	static string[144];
    format(string, sizeof(string), "AdmCmd: %s has set your Interior ID.", AccountData[playerid][pAdminname]);
	SendClientMessage(giveplayerid, Y_LIGHTRED, string);
	SendAdm(playerid, "You have set INT ID %s(%d) - %d.", AccountData[giveplayerid][pName], giveplayerid, int);
    
	return 1;
}

YCMD:owarn(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 4)
	    return PermissionError(playerid);

	new player[24], tmp[50], PlayerName[MAX_PLAYER_NAME];
	if(sscanf(params, "s[24]s[50]", player, tmp))
		return SUM(playerid, "/owarn [name] [reason]");

	if(strlen(tmp) > 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Maksimum reason adalah 50 karakter!");

	foreach(new ii : Player)
	{
		GetPlayerName(ii, PlayerName, MAX_PLAYER_NAME);

	    if(!strcmp(PlayerName, player, true))
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sedang online, gunakan '/warn' terhadapnya!");

	}
	new query[512];
	mysql_format(g_SQL, query, sizeof(query), "SELECT `pID`, `Char_Warn`, `Char_UCP` FROM `player_characters` WHERE `Char_Name`='%e'", player);
	mysql_pquery(g_SQL, query, "OWarnPlayer", "iss", playerid, player, tmp);
	return 1;
}

YCMD:ptp(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 4)
        return PermissionError(playerid);

    new otherid, targetmanid;

    if (sscanf(params, "dd", otherid, targetmanid))
        return SUM(playerid, "/ptp [otherid] [targetid]");

    if (!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "otherid tidak terkoneksi ke server!");

    if (!IsPlayerConnected(targetmanid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "targetmanid tidak terkoneksi ke server!");

    if (!AccountData[playerid][pSpawned] || !AccountData[otherid][pSpawned] || !AccountData[targetmanid][pSpawned])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda/kedua Pemain tersebut belum spawn!");

    if (OJailData[playerid][jailed] || OJailData[otherid][jailed] || OJailData[targetmanid][jailed])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda/kedua Pemain tersebut sedang di jail admin!");

    static string[144];
    SendPlayerToPlayer(otherid, targetmanid);
    format(string, sizeof(string), "AdmCmd: %s sent you to %s.", AccountData[playerid][pAdminname], AccountData[targetmanid][pName]);
    SendClientMessage(otherid, Y_LIGHTRED, string);
    format(string, sizeof(string), "AdmCmd: %s sent %s to you.", AccountData[playerid][pAdminname], AccountData[otherid][pName]);
    SendClientMessage(targetmanid, Y_LIGHTRED, string);
    SendAdm(playerid, "You have sent %s(%d) to %s(%d)", AccountData[otherid][pName], otherid, AccountData[targetmanid][pName], targetmanid);

    return 1;
}

YCMD:ban(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 4)
        return PermissionError(playerid);

    new ban_time, datez, tmp[64], otherid;
    if (sscanf(params, "ids[64]", otherid, datez, tmp))
        return SUM(playerid, "/ban [ID] [duration (days) 0 for permanent] [reason]");

    if (!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    if (datez < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Mohon masukkan durasi ban yang valid!");

    if (datez > 1 || datez < 1 && AccountData[playerid][pAdmin] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda hanya dapat memberikan ban selama 1 hari!");

    if (otherid == playerid)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya terhadap diri sendiri!");

    static string[144];
    if(AccountData[otherid][pAdmin] > AccountData[playerid][pAdmin])
    {
        format(string, sizeof(string), "AdmCmd: %s attempted to ban you.", AccountData[playerid][pAdminname]);
        SendClientMessage(otherid, Y_LIGHTRED, string);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya terhadap admin lebih tinggi!");
        return 1;
    }
    new PlayerIP[16], giveplayer[24];

    GetPlayerName(otherid, giveplayer, sizeof(giveplayer));
    GetPlayerIp(otherid, PlayerIP, sizeof(PlayerIP));

    if (datez != 0)
    {
        foreach (new i : Player) if (AccountData[i][pSpawned] && ToggleInfo[i][TogAdmCmd])
        {
            format(string, sizeof(string), "AdmCmd: %s set a ban status on %s(%d) for %d days.", AccountData[playerid][pAdminname], AccountData[otherid][pName], otherid, datez);
            SendClientMessage(i, Y_LIGHTRED, string);
            format(string, sizeof(string), "Reason: %s", tmp);
            SendClientMessage(i, Y_LIGHTRED, string);
        }
    }
    else
    {
        foreach (new i : Player) if (AccountData[i][pSpawned] && ToggleInfo[i][TogAdmCmd])
        {
            format(string, sizeof(string), "AdmCmd: %s set a permanent ban status on %s(%d).", AccountData[playerid][pAdminname], AccountData[otherid][pName], otherid);
            SendClientMessage(i, Y_LIGHTRED, string);
            format(string, sizeof(string), "Reason: %s", tmp);
            SendClientMessage(i, Y_LIGHTRED, string);
        }
    }
    BanPlayerMSG(otherid, playerid, tmp);
    if (datez != 0)
    {
        format(string, sizeof(string), "[Banned] This ban status will automatically expire in %d days.", datez);
        SendClientMessage(otherid, X11_LIGHTBLUE, string);
        ban_time = gettime() + (datez * 86400);
    }
    else
    {
        SendClientMessage(otherid, X11_LIGHTBLUE, "[Banned] This ban status is permanent; request an unban on Discord!");
        ban_time = datez;
    }
    new query[248];
    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `player_bans`(`name`, `ip`, `admin`, `reason`, `ban_date`, `ban_expire`) VALUES ('%e', '%e', '%e', '%e', %i, %d)", giveplayer, PlayerIP, AccountData[playerid][pAdminname], tmp, gettime(), ban_time);
    mysql_pquery(g_SQL, query);

    static year, month, day, keidwa[100], warsc[512];
    getdate(year, month, day);
    format(keidwa, sizeof(keidwa), "%02d/%02d/%d", day, month, year);

    for (new id; id < 100; ++id)
    {
        if (!PlayerWarning[otherid][id][warnExists])
        {
            PlayerWarning[otherid][id][warnExists] = true;
            PlayerWarning[otherid][id][warnOwner] = AccountData[otherid][pID];
            PlayerWarning[otherid][id][warnType] = 3;
            strcopy(PlayerWarning[otherid][id][warnIssuer], AccountData[playerid][pAdminname]);
            strcopy(PlayerWarning[otherid][id][warnDate], keidwa);
            strcopy(PlayerWarning[otherid][id][warnDateTime], GetAdvTime());
            strcopy(PlayerWarning[otherid][id][warnReason], tmp);
            break;
        }
    }

    mysql_format(g_SQL, warsc, sizeof(warsc), "INSERT INTO `player_warns` SET `Owner_ID` = %d, `Date` = '%e', `Date_Time` = '%e', `Issuer` = '%e', `Type` = 3, `Reason` = '%e'",
        AccountData[otherid][pID], keidwa, GetAdvTime(), AccountData[playerid][pAdminname], tmp);
    mysql_pquery(g_SQL, warsc);

    KickEx(otherid);
    return 1;
}

YCMD:acuff(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 4)
        return PermissionError(playerid);

    new otherid;
    if (sscanf(params, "i", otherid))
        return SUM(playerid, "/acuff [playerid]");

    if (!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    if (otherid == playerid)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya terhadap diri sendiri!");

    if (GetPlayerState(otherid) != PLAYER_STATE_ONFOOT)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut harus berjalan kaki!");

    if (AccountData[otherid][pCuffed])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sedang diborgol!");

    AccountData[otherid][pCuffed] = true;

    GameTextForPlayer(otherid, "~r~Terborgol", 3500, 3);
    SetPlayerSpecialAction(otherid, SPECIAL_ACTION_CUFFED);

    static string[144];
    format(string, sizeof(string), "AdmCmd: "RED"%s "WHITE"has handcuffed you.", AccountData[playerid][pAdminname]);
    SendClientMessage(otherid, X11_LIGHTBLUE, string);

    SendAdm(playerid, "You have handcuffed "YELLOW"%s(%d).", AccountData[otherid][pName], otherid);

    return 1;
}

YCMD:auncuff(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 4)
        return PermissionError(playerid);

    new otherid;
    if (sscanf(params, "i", otherid))
        return SUM(playerid, "/auncuff [playerid]");

    if (!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    if (!AccountData[otherid][pCuffed])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak sedang diborgol!");

    AccountData[otherid][pCuffed] = false;
    GameTextForPlayer(otherid, "~g~Borgol terlepas", 3500, 3);
    SetPlayerSpecialAction(otherid, SPECIAL_ACTION_NONE);

    static string[144];
    format(string, sizeof(string), "AdmCmd: %s has released your handcuffs.", AccountData[playerid][pAdminname]);
    SendClientMessage(otherid, Y_LIGHTRED, string);
    SendAdm(playerid, "You have released %s's handcuffs.", AccountData[otherid][pName]);

    return 1;
}

YCMD:jetpack(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 4)
        return PermissionError(playerid);
	
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);
	return 1;
}

YCMD:unjail(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 4)
        return PermissionError(playerid);

    new otherid;
    if(sscanf(params, "d", otherid))
        return SUM(playerid, "/unjail [playerid]");

    if(!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    if(!OJailData[otherid][jailed])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak sedang di jail admin!");

    OJailData[otherid][jailed] = false;
    OJailData[otherid][jailCell] = -1;
    OJailData[otherid][jailAdmin][0] = EOS;
    OJailData[otherid][jailTime] = 0;
    OJailData[otherid][jailDur] = 0;
    OJailData[otherid][jailReason][0] = EOS;
    OJailData[otherid][jailFine] = 0;
    SetPlayerInteriorEx(otherid, 0);
    SetPlayerVirtualWorldEx(otherid, 0);

    SetPlayerPositionEx(otherid, 1479.7563,-1709.2994,14.0469,178.8976);
    SetPlayerSpecialAction(otherid, SPECIAL_ACTION_NONE);
    ClearAnimations(otherid, true);

    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has released %s from admin jail.", AccountData[playerid][pAdminname], AccountData[otherid][pName]);
    return 1;
}

YCMD:sendveh(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 4)
        return PermissionError(playerid);

    new otherid, vehid, Float:x, Float:y, Float:z, driverid;
    if (sscanf(params, "dd", otherid, vehid))
        return SUM(playerid, "/sendveh [playerid] [vehid] (Use /avehlist to find vehid)");

    if (!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if (!IsValidVehicle(vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Vehicle ID!");

    GetPlayerPos(otherid, x, y, z);
    SetVehiclePos(vehid, x, y, z + 0.5);

    driverid = GetVehicleDriver(vehid);
    if (driverid != INVALID_PLAYER_ID)
        Anticheat[GetVehicleDriver(vehid)][acImmunity] = gettime() + 5;
    SetVehicleVirtualWorldEx(vehid, GetPlayerVirtualWorld(otherid));
    LinkVehicleToInteriorEx(vehid, GetPlayerInterior(otherid));
    SendAdm(playerid, "You have sent VID: %d to %s(%d) at %s.", vehid, AccountData[otherid][pName], otherid, GetLocation(x, y, z));
    return 1;
}

YCMD:gotoco(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 4)
        return PermissionError(playerid);

    new Float: pos[3], int;
    if (sscanf(params, "fffd", pos[0], pos[1], pos[2], int)) return SUM(playerid, "/gotoco [x-axis] [y-axis] [z-axis] [interior id]");

    AccountData[playerid][pInRusun] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInGudang] = -1;

    SetPlayerPositionEx(playerid, pos[0], pos[1], pos[2], 0.0);
    SetPlayerInterior(playerid, int);
    return 1;
}

YCMD:adveh(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 4) return PermissionError(playerid);

    for(new i; i < MAX_ADMIN_VEHICLES; i++)
    {
        DestroyVehicle(GM[adminV][i]);
        GM[adminV][i] = INVALID_VEHICLE_ID;
    }
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has destroyed all admin vehicles!", AccountData[playerid][pAdminname]);
    return 1;
}

YCMD:adjveh(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 4)
        return PermissionError(playerid);

    SetTimer("OnJobVehicleDestroyed", 30000, false);
    SendClientMessageToAllEx(Y_LIGHTRED, "AdmCmd: %s akan menghancurkan kendaraan Job & Sidejob yang tidak dinaiki selama 30 detik.", AccountData[playerid][pAdminname]);
    return 1;
}

YCMD:setskin(playerid, params[], help)
{
    new
        skinid,
        otherid;

    if(AccountData[playerid][pAdmin] < 4)
        return PermissionError(playerid);

    if(sscanf(params, "ud", otherid, skinid))
        return SUM(playerid, "/setskin [playerid/Part Of Name] [skin id]");

    if(!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    if(skinid < 0 || skinid > 311)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid skin ID (0 - 311)");

    SetPlayerSkin(otherid, skinid);
    AccountData[otherid][pSkin] = skinid;

    static string[144];
    format(string, sizeof(string), "AdmCmd: %s has set your character's skin to %d.",AccountData[playerid][pAdminname], skinid);
    SendClientMessage(otherid, Y_LIGHTRED, string);
    SendAdm(playerid, "You have set the skin for %s(%d) to %d.", AccountData[otherid][pName], otherid, skinid);
    return 1;
}

YCMD:sendto(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 4)
		return PermissionError(playerid);

	new otherid, type[24];
	if(sscanf(params, "ds[24]", otherid, type))
		return SUM(playerid, "/sendto [playerid] [ls/asuransi/rs/ikea/karnaval/showroom/balkot/bandara/pelabuhan]");

	if(!IsPlayerConnected(otherid))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	
	static string[144];
	if(!strcmp(type, "ls", true))
    {
		AccountData[otherid][pInRusun] = -1;
		AccountData[otherid][pInHouse] = -1;
		AccountData[otherid][pInBiz] = -1;
		AccountData[otherid][pInDoor] = -1;
		AccountData[otherid][pInGudang] = -1;

		SetPlayerPositionEx(otherid, 1482.0356, -1724.5726, 13.5469, 0.0);
		SetPlayerVirtualWorldEx(otherid, 0);
		SetPlayerInteriorEx(otherid, 0);
		
		format(string, sizeof(string), "AdmCmd: You have been teleported to Los Santos by %s.", AccountData[playerid][pAdminname]);
		SendClientMessage(otherid, Y_LIGHTRED, string);
		SendAdm(playerid, "You have teleported %s(%i) to Los Santos.", AccountData[otherid][pName], otherid);
	}
	else if(!strcmp(type, "asuransi", true))
    {
		AccountData[otherid][pInRusun] = -1;
		AccountData[otherid][pInHouse] = -1;
		AccountData[otherid][pInBiz] = -1;
		AccountData[otherid][pInDoor] = -1;
		AccountData[otherid][pInGudang] = -1;

		SetPlayerPositionEx(otherid, -389.5509,2230.9001,42.4297, 0.0);
		SetPlayerVirtualWorldEx(otherid, 0);
		SetPlayerInteriorEx(otherid, 0);

		format(string, sizeof(string), "AdmCmd: You have been teleported to asuransi by %s.", AccountData[playerid][pAdminname]);
		SendClientMessage(otherid, Y_LIGHTRED, string);
		SendAdm(playerid, "You have teleported %s(%i) to asuransi.", AccountData[otherid][pName], otherid);
	}
	else if(!strcmp(type, "rs", true))
    {
		AccountData[otherid][pInRusun] = -1;
		AccountData[otherid][pInHouse] = -1;
		AccountData[otherid][pInBiz] = -1;
		AccountData[otherid][pInDoor] = -1;
		AccountData[otherid][pInGudang] = -1;

		SetPlayerPositionEx(otherid, 1743.8606,-1171.2920,23.8281, 1.2817);
		SetPlayerVirtualWorldEx(otherid, 0);
		SetPlayerInteriorEx(otherid, 0);

		format(string, sizeof(string), "AdmCmd: You have been teleported to rumah sakit by %s.", AccountData[playerid][pAdminname]);
		SendClientMessage(otherid, Y_LIGHTRED, string);
		SendAdm(playerid, "You have teleported %s(%i) to rumah sakit.", AccountData[otherid][pName], otherid);
	}
	else if(!strcmp(type, "ikea", true))
    {
		AccountData[otherid][pInRusun] = -1;
		AccountData[otherid][pInHouse] = -1;
		AccountData[otherid][pInBiz] = -1;
		AccountData[otherid][pInDoor] = -1;
		AccountData[otherid][pInGudang] = -1;

		SetPlayerPositionEx(otherid, 2817.5532,-1087.9933,30.7399,88.9927);
		SetPlayerVirtualWorldEx(otherid, 0);
		SetPlayerInteriorEx(otherid, 0);

		format(string, sizeof(string), "AdmCmd: You have been teleported to ikea by %s.", AccountData[playerid][pAdminname]);
		SendClientMessage(otherid, Y_LIGHTRED, string);
		SendAdm(playerid, "You have teleported %s(%i) to ikea.", AccountData[otherid][pName], otherid);
	}
	else if(!strcmp(type, "karnaval", true))
    {
		AccountData[otherid][pInRusun] = -1;
		AccountData[otherid][pInHouse] = -1;
		AccountData[otherid][pInBiz] = -1;
		AccountData[otherid][pInDoor] = -1;
		AccountData[otherid][pInGudang] = -1;

		SetPlayerPositionEx(otherid, 380.7771,-2026.2224,7.8359,181.3164);
		SetPlayerVirtualWorldEx(otherid, 0);
		SetPlayerInteriorEx(otherid, 0);

		format(string, sizeof(string), "AdmCmd: You have been teleported to karnaval by %s.", AccountData[playerid][pAdminname]);
		SendClientMessage(otherid, Y_LIGHTRED, string);
		SendAdm(playerid, "You have teleported %s(%i) to karnaval.", AccountData[otherid][pName], otherid);
	}
	else if(!strcmp(type, "showroom", true))
    {
		AccountData[otherid][pInRusun] = -1;
		AccountData[otherid][pInHouse] = -1;
		AccountData[otherid][pInBiz] = -1;
		AccountData[otherid][pInDoor] = -1;
		AccountData[otherid][pInGudang] = -1;

		SetPlayerPositionEx(otherid, 395.3554,-1341.3446,14.7684,31.4033);
		SetPlayerVirtualWorldEx(otherid, 0);
		SetPlayerInteriorEx(otherid, 0);

		format(string, sizeof(string), "AdmCmd: You have been teleported to showroom by %s.", AccountData[playerid][pAdminname]);
		SendClientMessage(otherid, Y_LIGHTRED, string);
		SendAdm(playerid, "You have teleported %s(%i) to showroom.", AccountData[otherid][pName], otherid);
	}
	else if(!strcmp(type, "balkot", true))
    {
		AccountData[otherid][pInRusun] = -1;
		AccountData[otherid][pInHouse] = -1;
		AccountData[otherid][pInBiz] = -1;
		AccountData[otherid][pInDoor] = -1;
		AccountData[otherid][pInGudang] = -1;

		SetPlayerPositionEx(otherid, 1255.9501,-2048.1375,59.7302,31.0483);
		SetPlayerVirtualWorldEx(otherid, 0);
		SetPlayerInteriorEx(otherid, 0);

		format(string, sizeof(string), "AdmCmd: You have been teleported to balai kota by %s.", AccountData[playerid][pAdminname]);
		SendClientMessage(otherid, Y_LIGHTRED, string);
		SendAdm(playerid, "You have teleported %s(%i) to balai kota.", AccountData[otherid][pName], otherid);
	}
    else if(!strcmp(type, "bandara", true))
    {
		AccountData[otherid][pInRusun] = -1;
		AccountData[otherid][pInHouse] = -1;
		AccountData[otherid][pInBiz] = -1;
		AccountData[otherid][pInDoor] = -1;
		AccountData[otherid][pInGudang] = -1;

		SetPlayerPositionEx(otherid, 1682.8850,-2242.6370,13.5469,180.7440);
		SetPlayerVirtualWorldEx(otherid, 0);
		SetPlayerInteriorEx(otherid, 0);

		format(string, sizeof(string), "AdmCmd: You have been teleported to bandara by %s.", AccountData[playerid][pAdminname]);
		SendClientMessage(otherid, Y_LIGHTRED, string);
		SendAdm(playerid, "You have teleported %s(%i) to bandara.", AccountData[otherid][pName], otherid);
	}
    else if(!strcmp(type, "pelabuhan", true))
    {
		AccountData[otherid][pInRusun] = -1;
		AccountData[otherid][pInHouse] = -1;
		AccountData[otherid][pInBiz] = -1;
		AccountData[otherid][pInDoor] = -1;
		AccountData[otherid][pInGudang] = -1;

		SetPlayerPositionEx(otherid, 2717.9348,-2513.8723,17.3672,2.3617);
		SetPlayerVirtualWorldEx(otherid, 0);
		SetPlayerInteriorEx(otherid, 0);

		format(string, sizeof(string), "AdmCmd: You have been teleported to pelabuhan by %s.", AccountData[playerid][pAdminname]);
		SendClientMessage(otherid, Y_LIGHTRED, string);
		SendAdm(playerid, "You have teleported %s(%i) to pelabuhan.", AccountData[otherid][pName], otherid);
	}
	return 1;
}

YCMD:dveh(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 4)
        return PermissionError(playerid);

    new impstr[144];

    if (IsPlayerInAnyVehicle(playerid))
    {
        new vehid = GetPlayerVehicleID(playerid);

        foreach (new i : Player)
        {
            if (vehid == JobVehicle[i])
            {
                DestroyVehicle(JobVehicle[i]);
            }

            if (vehid == TrailerVehicle[i])
            {
                DestroyVehicle(TrailerVehicle[i]);
            }

            if (vehid == FactionHeliVeh[i])
            {
                DestroyVehicle(FactionHeliVeh[i]);
            }

            if (vehid == g_CarstealCarPhysic[i])
            {
                foreach (new x : LSPDDuty)
                {
                    if (DestroyDynamicMapIcon(AccountData[i][g_CarstealIcon][x]))
                        AccountData[i][g_CarstealIcon][x] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
                }

                DestroyVehicle(g_CarstealCarPhysic[i]);
            }
            if (vehid == EventVehicle[i])
            {
                DestroyVehicle(EventVehicle[i]);
            }

            if (vehid == ShowroomVeh[i])
            {
                DestroyVehicle(ShowroomVeh[i]);
            }

            if (vehid == PlayerFactionVehicle[i][AccountData[i][pFaction]])
            {
                LSPDPlayerCallsign[i][0] = EOS;
                DestroyVehicle(PlayerFactionVehicle[i][AccountData[i][pFaction]]);

                static string[168];
                mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `demand_vehicles` WHERE `ownerid` = %d", AccountData[i][pID]);
                mysql_pquery(g_SQL, string);
            }
        }

        for (new i; i < MAX_ADMIN_VEHICLES; i++)
        {
            if (vehid == GM[adminV][i])
            {
                DestroyVehicle(GM[adminV][i]);
            }
        }

        foreach (new pv : PvtVehicles)
        {
            if (vehid == PlayerVehicle[pv][pVehPhysic])
            {
                if (PlayerVehicle[pv][pVehRental] > -1 || PlayerVehicle[pv][pVehRentTime] > 0)
                {
                    PlayerVehicle[pv][pVehRental] = -1;
                    PlayerVehicle[pv][pVehRentTime] = 0;

                    SetVehicleNeonLights(PlayerVehicle[pv][pVehPhysic], false, PlayerVehicle[pv][pVehNeon], 0);

                    DestroyVehicle(PlayerVehicle[pv][pVehPhysic]);

                    PlayerVehicle[pv][pVehHandbraked] = false;

                    mysql_format(g_SQL, impstr, sizeof(impstr), "DELETE FROM `vehicle_bagasi` WHERE `Veh_DBID`=%d", PlayerVehicle[pv][pVehID]);
                    mysql_pquery(g_SQL, impstr);
                    mysql_format(g_SQL, impstr, sizeof(impstr), "DELETE FROM `vehicle_holster` WHERE `Veh_DBID`=%d", PlayerVehicle[pv][pVehID]);
                    mysql_pquery(g_SQL, impstr);
                    mysql_format(g_SQL, impstr, sizeof(impstr), "DELETE FROM `player_vehicles` WHERE `id` = %d", PlayerVehicle[pv][pVehID]);
                    mysql_pquery(g_SQL, impstr);
                    mysql_format(g_SQL, impstr, sizeof(impstr), "DELETE FROM `vtoys` WHERE `Veh_DBID`=%d", PlayerVehicle[pv][pVehID]);
                    mysql_pquery(g_SQL, impstr);

                    for(new x; x < MAX_BAGASI_ITEMS; x++)
					{
						VehicleBagasi[pv][x][vehicleBagasiExists] = false;
						VehicleBagasi[pv][x][vehicleBagasiID] = 0;
						VehicleBagasi[pv][x][vehicleBagasiVDBID] = 0;
						VehicleBagasi[pv][x][vehicleBagasiTemp][0] = EOS;
						VehicleBagasi[pv][x][vehicleBagasiModel] = 0;
						VehicleBagasi[pv][x][vehicleBagasiQuant] = 0;
					}

                    for(new z; z < 3; z++)
					{
						VehicleHolster[pv][vHolsterTaken][z] = false;
						VehicleHolster[pv][vHolsterID][z] = -1;
						VehicleHolster[pv][vHolsterWeaponID][z] = 0;
						VehicleHolster[pv][vHolsterWeaponAmmo][z] = 0;
					}

                    Iter_Remove(PvtVehicles, pv);
                }
                else
                {
                    PlayerVehicle[pv][pVehHandbraked] = false;
                    PlayerVehicle[pv][pVehInsuranced] = true;
                    DestroyVehicle(PlayerVehicle[pv][pVehPhysic]);

                    mysql_format(g_SQL, impstr, sizeof(impstr), "UPDATE `player_vehicles` SET `PVeh_Insuranced` = 1 WHERE `id`=%d",PlayerVehicle[pv][pVehID]);
                    mysql_pquery(g_SQL, impstr);
                }
            }
        }
        SendAdm(playerid, "Anda telah menghancurkan kendaraan VID %d.", vehid);
    }
    else
    {
        new tvid;
        if (sscanf(params, "d", tvid)) return SUM(playerid, "/dveh [vehicle id]");
        if (!IsValidVehicle(tvid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Vehicle ID!");

        foreach (new i : Player)
        {
            if (tvid == JobVehicle[i])
            {
                DestroyVehicle(JobVehicle[i]);
            }

            if (tvid == TrailerVehicle[i])
            {
                DestroyVehicle(TrailerVehicle[i]);
            }

            if (tvid == FactionHeliVeh[i])
            {
                DestroyVehicle(FactionHeliVeh[i]);
            }

            if (tvid == g_CarstealCarPhysic[i])
            {
                foreach (new x : LSPDDuty)
                {
                    if (DestroyDynamicMapIcon(AccountData[i][g_CarstealIcon][x]))
                        AccountData[i][g_CarstealIcon][x] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
                }
                DestroyVehicle(g_CarstealCarPhysic[i]);
            }

            if (tvid == EventVehicle[i])
            {
                DestroyVehicle(EventVehicle[i]);
            }

            if (tvid == ShowroomVeh[i])
            {
                DestroyVehicle(ShowroomVeh[i]);
            }

            if (tvid == PlayerFactionVehicle[i][AccountData[i][pFaction]])
            {
                LSPDPlayerCallsign[i][0] = EOS;
                DestroyVehicle(PlayerFactionVehicle[i][AccountData[i][pFaction]]);

                static string[168];
                mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `demand_vehicles` WHERE `ownerid` = %d", AccountData[i][pID]);
                mysql_pquery(g_SQL, string);
            }
        }

        for (new i; i < MAX_ADMIN_VEHICLES; i++)
        {
            if (tvid == GM[adminV][i])
            {
                DestroyVehicle(GM[adminV][i]);
            }
        }

        foreach (new pv : PvtVehicles)
        {
            if(PlayerVehicle[pv][pVehPhysic] == tvid)
            {
                if(PlayerVehicle[pv][pVehRental] > -1 || PlayerVehicle[pv][pVehRentTime] > 0)
                {
                    PlayerVehicle[pv][pVehRental] = -1;
                    PlayerVehicle[pv][pVehRentTime] = 0;

                    SetVehicleNeonLights(PlayerVehicle[pv][pVehPhysic], false, PlayerVehicle[pv][pVehNeon], 0);

                    DestroyVehicle(PlayerVehicle[pv][pVehPhysic]);

                    PlayerVehicle[pv][pVehHandbraked] = false;

                    mysql_format(g_SQL, impstr, sizeof(impstr), "DELETE FROM `vehicle_bagasi` WHERE `Veh_DBID`=%d", PlayerVehicle[pv][pVehID]);
				    mysql_pquery(g_SQL, impstr);
				    mysql_format(g_SQL, impstr, sizeof(impstr), "DELETE FROM `vehicle_holster` WHERE `Veh_DBID`=%d", PlayerVehicle[pv][pVehID]);
				    mysql_pquery(g_SQL, impstr);
                    mysql_format(g_SQL, impstr, sizeof(impstr), "DELETE FROM `player_vehicles` WHERE `id` = %d", PlayerVehicle[pv][pVehID]);
                    mysql_pquery(g_SQL, impstr);
                    mysql_format(g_SQL, impstr, sizeof(impstr), "DELETE FROM `vtoys` WHERE `Veh_DBID`=%d", PlayerVehicle[pv][pVehID]);
                    mysql_pquery(g_SQL, impstr);

                    for(new x; x < MAX_BAGASI_ITEMS; x++)
					{
						VehicleBagasi[pv][x][vehicleBagasiExists] = false;
						VehicleBagasi[pv][x][vehicleBagasiID] = 0;
						VehicleBagasi[pv][x][vehicleBagasiVDBID] = 0;
						VehicleBagasi[pv][x][vehicleBagasiTemp][0] = EOS;
						VehicleBagasi[pv][x][vehicleBagasiModel] = 0;
						VehicleBagasi[pv][x][vehicleBagasiQuant] = 0;
					}

                    for(new z; z < 3; z++)
					{
						VehicleHolster[pv][vHolsterTaken][z] = false;
						VehicleHolster[pv][vHolsterID][z] = -1;
						VehicleHolster[pv][vHolsterWeaponID][z] = 0;
						VehicleHolster[pv][vHolsterWeaponAmmo][z] = 0;
					}

                    Iter_Remove(PvtVehicles, pv);
                }
                else
                {
                    PlayerVehicle[pv][pVehInsuranced] = true;

                    SetVehicleNeonLights(PlayerVehicle[pv][pVehPhysic], false, PlayerVehicle[pv][pVehNeon], 0);

                    PlayerVehicle[pv][pVehHandbraked] = false;

                    DestroyVehicle(PlayerVehicle[pv][pVehPhysic]);

                    mysql_format(g_SQL, impstr, sizeof(impstr), "UPDATE `player_vehicles` SET `PVeh_Insuranced` = 1 WHERE `id`=%d",PlayerVehicle[pv][pVehID]);
                    mysql_pquery(g_SQL, impstr);
                }
            }
        }
        SendAdm(playerid, "Anda telah menghancurkan kendaraan VID %d.", tvid);
    }
    return 1;
}