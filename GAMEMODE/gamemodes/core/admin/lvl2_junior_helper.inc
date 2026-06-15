YCMD:goto(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 2)
        return PermissionError(playerid);

    new otherid;
    if (sscanf(params, "d", otherid))
        return SUM(playerid, "/goto [playerid]");

    if (!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    static string[144];
    SendPlayerToPlayer(playerid, otherid);
    format(string, sizeof(string), "AdmCmd: %s teleported to your position.", AccountData[playerid][pAdminname]);
    SendClientMessage(otherid, Y_LIGHTRED, string);

    return 1;
}

YCMD:gotols(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 2)
		return PermissionError(playerid);

	AccountData[playerid][pInRusun] = -1;
	AccountData[playerid][pInHouse] = -1;
	AccountData[playerid][pInBiz] = -1;
	AccountData[playerid][pInDoor] = -1;
	AccountData[playerid][pInGudang] = -1;

    SetPlayerPositionEx(playerid, 1475.0045,-1697.1842,14.0469,177.6616);
    SetPlayerVirtualWorldEx(playerid, 0);
	SetPlayerInteriorEx(playerid, 0);
	return 1;
}

YCMD:spectate(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 2)
     	return PermissionError(playerid);

    if (!isnull(params) && !strcmp(params, "off", true))
    {
        if (GetPlayerState(playerid) != PLAYER_STATE_SPECTATING || AccountData[playerid][pSpec] == INVALID_PLAYER_ID)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini tidak sedang dalam mode spec!");

        SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pSkin], AccountData[playerid][pPos][0], AccountData[playerid][pPos][1], AccountData[playerid][pPos][2], AccountData[playerid][pPos][3], 0, 0, 0, 0, 0, 0);
        TogglePlayerSpectating(playerid, false);

        PlayerSpectatePlayer(playerid, INVALID_PLAYER_ID);
        PlayerSpectateVehicle(playerid, INVALID_VEHICLE_ID);
		AccountData[playerid][pSpec] = INVALID_PLAYER_ID;

        PlayerTextDrawHide(playerid, SpecInfoTD[playerid]);
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah keluar dari mode spectator.");
        return 1;
    }

	new otherid;
    if (sscanf(params, "d", otherid))
    	return SUM(playerid, "/spec [playerid] (Use '/spec off' to exit spectator mode)");

    if (!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

	if (otherid == playerid)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat spec diri sendiri!");

    if (AccountData[playerid][pAdmin] < AccountData[otherid][pAdmin])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat spec admin yang lebih tinggi!");

	if (!AccountData[otherid][pSpawned])
	    return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Player %s(%i) belum spawn!", AccountData[otherid][pName], otherid));

    if (GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
    {
        GetPlayerPos(playerid, AccountData[playerid][pPos][0], AccountData[playerid][pPos][1], AccountData[playerid][pPos][2]);
        GetPlayerFacingAngle(playerid, AccountData[playerid][pPos][3]);

        AccountData[playerid][pInterior] = GetPlayerInterior(playerid);
        AccountData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);
    }
    SetPlayerInterior(playerid, GetPlayerInterior(otherid));
    SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(otherid));
    
    TogglePlayerSpectating(playerid, true);

    static string[144];

    new Float:health, Float:armour, keys, ups, lefts, Float:vhealth;
    GetPlayerHealth(otherid, health);
    GetPlayerArmour(otherid, armour);
    GetPlayerKeys(otherid, keys, ups, lefts);
    if(IsPlayerInAnyVehicle(otherid) && Iter_Contains(Vehicle, GetPlayerVehicleID(otherid)))
	{
		new vID = GetVehicleModel(GetPlayerVehicleID(otherid));
        PlayerSpectateVehicle(playerid, GetPlayerVehicleID(otherid));
		if (GetPlayerState(otherid) == PLAYER_STATE_DRIVER)
	    {
            GetVehicleHealth(GetPlayerVehicleID(otherid), vhealth);
            format(string, sizeof(string), "%s (%d)~n~HP: %.2f~n~AP: %.2f~n~vHP: %.2f~n~Cash: $%s~n~World: %d // Int: %d~n~Keys: %d %d %d~n~FPS: %d // Ping: %d", AccountData[otherid][pName], otherid, health, armour, vhealth, FormatMoney(AccountData[otherid][pMoney]), GetPlayerVirtualWorld(otherid), GetPlayerInterior(otherid), keys, ups, lefts, GetPlayerFPS(otherid), GetPlayerPing(otherid));
            PlayerTextDrawSetString(playerid, SpecInfoTD[playerid], string);
            PlayerTextDrawShow(playerid, SpecInfoTD[playerid]);

			SendAdm(playerid, "You are spectating %s(%i) who is currently driving %s(%d).", AccountData[otherid][pName], otherid, GetVehicleModelName(vID), GetPlayerVehicleID(otherid));
		}
		else
		{
            format(string, sizeof(string), "%s (%d)~n~HP: %.2f~n~AP: %.2f~n~Cash: $%s~n~World: %d // Int: %d~n~Keys: %d %d %d~n~FPS: %d // Ping: %d", AccountData[otherid][pName], otherid, health, armour, FormatMoney(AccountData[otherid][pMoney]), GetPlayerVirtualWorld(otherid), GetPlayerInterior(otherid), keys, ups, lefts, GetPlayerFPS(otherid), GetPlayerPing(otherid));
            PlayerTextDrawSetString(playerid, SpecInfoTD[playerid], string);
            PlayerTextDrawShow(playerid, SpecInfoTD[playerid]);

		    SendAdm(playerid, "You are spectating %s(%i) who is a passenger in %s(%d).", AccountData[otherid][pName], otherid, GetVehicleModelName(vID), GetPlayerVehicleID(otherid));
		}
	}
    else
	{
        PlayerSpectatePlayer(playerid, otherid);
        format(string, sizeof(string), "%s (%d)~n~HP: %.2f~n~AP: %.2f~n~Cash: $%s~n~World: %d // Int: %d~n~Keys: %d %d %d~n~FPS: %d // Ping: %d", AccountData[otherid][pName], otherid, health, armour, FormatMoney(AccountData[otherid][pMoney]), GetPlayerVirtualWorld(otherid), GetPlayerInterior(otherid), keys, ups, lefts, GetPlayerFPS(otherid), GetPlayerPing(otherid));
        PlayerTextDrawSetString(playerid, SpecInfoTD[playerid], string);
        PlayerTextDrawShow(playerid, SpecInfoTD[playerid]);
	}
    AccountData[playerid][pSpec] = otherid;
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s is spectating %s (%d).", AccountData[playerid][pAdminname], AccountData[otherid][pName], otherid);
    return 1;
}

YCMD:spec(playerid, params[], help) = spectate;

YCMD:astats(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 2)
		return PermissionError(playerid);

	new otherid;
	if (sscanf(params, "d", otherid))
        return SUM(playerid, "/astats [playerid]");

	if (!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

	if (!AccountData[otherid][IsLoggedIn])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut belum login!");

	ShowPlayerStats(playerid, otherid);

	return 1;
}

YCMD:ostats(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 2)
		return PermissionError(playerid);
			
	new name[24];
	if(sscanf(params, "s[24]", name))
	    return SUM(playerid, "/ostats [Nick_Name]");

 	foreach(new i : Player) if(IsPlayerConnected(i))
	{
		if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned])
		{
			if(!strcmp(name, AccountData[i][pName], true)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sedang online, gunakan ~b~/astats");
		}
	}

	// Load User Data
    new cVar[1200];
    new cQuery[1200];

	strcat(cVar, "pID, Char_UCP, Char_Name, Char_Birthday, Char_Origin, Char_Gender, Char_BodyHeight,");
	strcat(cVar, "Char_BodyWeight, Char_Job, Char_Faction, Char_FactionRank, Char_Family, Char_FamilyRank, Char_Money, Char_BankMoney, Char_CasinoChip, Char_DirtyMoney, Char_Health, Char_Armor, Char_Hunger, Char_Thirst, Char_Stress, Char_Warn, Char_Level, Char_Hours, Char_Minutes, Char_Seconds, Char_Admin, Char_Steward, Char_StewTime, Char_VIP, Char_VIPTime,");
	strcat(cVar, "Char_Skin, Char_WID, Char_IntID, Char_InHouse, Char_InDoor, Char_InRusun, Char_LastLogin, Char_RegisterDate");

	mysql_format(g_SQL, cQuery, sizeof(cQuery), "SELECT %s FROM `player_characters` WHERE `Char_Name`='%e' LIMIT 1", cVar, name);
	mysql_pquery(g_SQL, cQuery, "LoadStats", "is", playerid, name);
	return 1;
}

YCMD:jaillist(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 2)
        return PermissionError(playerid);

    new count = 0, line3[512];
    foreach (new i : Player)
    {
        if (OJailData[i][jailed])
        {
            format(line3, sizeof(line3), "%s\n"WHITE"%s(ID: %d) [Jail Time: %d seconds]", line3, AccountData[i][pName], i, OJailData[i][jailTime]);
            count++;
        }
    }
    if (count > 0)
    {
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Jail Player", line3, "Tutup", "");
    }
    else
    {
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Jail Player", "No players currently jailed!", "Tutup", "");
    }

    return 1;
}

YCMD:ntag(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 2)
		return PermissionError(playerid);

	new hhs[158];

	switch(AccountData[playerid][pToggleNameID])
	{
		case false:
		{
			AccountData[playerid][pToggleNameID] = true;

			foreach(new i : Player) if(i != playerid)
			{
				if(AccountData[i][pSpawned] && AccountData[i][IsLoggedIn])
				{
					format(hhs, sizeof(hhs), "%s\n%s [%d]\n"RED"%.2f "WHITE"| "GRAY"%.2f", AccountData[i][pName], AccountData[i][pUCP], i, AccountData[i][pHealth], AccountData[i][pArmor]);
					AccountData[playerid][pNameIDLabel][i] = CreateDynamic3DTextLabel(hhs, Y_WHITE, 0.0, 0.0, 0.6, 100.5, i, INVALID_VEHICLE_ID, 0, -1, -1, playerid, 100.5, -1, 0);
				}
			}
			ShowTDN(playerid, NOTIFICATION_INFO, "Nametag player ~g~aktif.");
		}
		case true:
		{
			AccountData[playerid][pToggleNameID] = false;

			foreach(new i : Player) if(i != playerid)
			{
				if(AccountData[i][pSpawned] && AccountData[i][IsLoggedIn])
				{
					if(DestroyDynamic3DTextLabel(AccountData[playerid][pNameIDLabel][i]))
						AccountData[playerid][pNameIDLabel][i] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
				}
			}

			ShowTDN(playerid, NOTIFICATION_INFO, "Nametag player ~r~tidak aktif.");
		}
	}
	return 1;
}

YCMD:warn(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 2)
		return PermissionError(playerid);

	new otherid, reason[64];
    if(sscanf(params, "ds[64]", otherid, reason))
        return SUM(playerid, "/warn [playerid] [reason]");

    if(!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

	if(strlen(reason) > 64) return ShowTDN(playerid, NOTIFICATION_ERROR, "Maksimum reason adadlah 64 karakter!");

    if(AccountData[otherid][pAdmin] > AccountData[playerid][pAdmin])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya terhadap admin lebih tinggi!");

	if(AccountData[otherid][pWarn] >= MAX_PWARNS)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut telah mencapai batas maksimum warn!");

	AccountData[otherid][pWarn]++;

	static string[144];
	foreach(new i : Player) if(AccountData[i][pSpawned] && ToggleInfo[i][TogAdmCmd])
	{
		format(string, sizeof(string), "AdmCmd: %s(%i) has been warned by %s [Total: %d/20]", AccountData[otherid][pName], otherid, AccountData[playerid][pAdminname], AccountData[otherid][pWarn]);
		SendClientMessage(i, Y_LIGHTRED, string);
		format(string, sizeof(string), "Reason: %s", reason);
		SendClientMessage(i, Y_LIGHTRED, string);
	}

    ShowWarningTD(otherid, AccountData[playerid][pAdminname], reason);

	static year, month, day, keidwa[100], warsc[512];
	getdate(year, month, day);
	format(keidwa, sizeof(keidwa), "%02d/%02d/%d", day, month, year);

	for(new id; id < 100; ++id)
	{
		if(!PlayerWarning[otherid][id][warnExists])
		{
			PlayerWarning[otherid][id][warnExists] = true;
			PlayerWarning[otherid][id][warnOwner] = AccountData[otherid][pID];
			PlayerWarning[otherid][id][warnType] = 1;
			strcopy(PlayerWarning[otherid][id][warnIssuer], AccountData[playerid][pAdminname]);
			strcopy(PlayerWarning[otherid][id][warnDate], keidwa);
			strcopy(PlayerWarning[otherid][id][warnDateTime], GetAdvTime());
			strcopy(PlayerWarning[otherid][id][warnReason], reason);
			break;
		}
	}

	mysql_format(g_SQL, warsc, sizeof(warsc), "INSERT INTO `player_warns` SET `Owner_ID` = %d, `Date` = '%e', `Date_Time` = '%e', `Issuer` = '%e', `Type` = 1, `Reason` = '%e'",
	AccountData[otherid][pID], keidwa, GetAdvTime(), AccountData[playerid][pAdminname], reason);
	mysql_pquery(g_SQL, warsc);

	if(AccountData[otherid][pWarn] >= MAX_PWARNS)
	{
		static query[522];
		mysql_format(g_SQL, query, sizeof(query), "UPDATE `player_ucp` SET `Blocked`=1, `Block_Duration`=0, `Block_Reason`='20 Warns', `Block_AdminName`='Pahlawan Roleplay AntiCheat', `Block_IssuedDate`=CURRENT_TIMESTAMP() WHERE `UCP`='%e'", AccountData[otherid][pUCP]);
		mysql_pquery(g_SQL, query);
		return KickEx(otherid);
	}

	return 1;
}

YCMD:unwarn(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 2)
		return PermissionError(playerid);

	new otherid, reason[64];
    if(sscanf(params, "ds[64]", otherid, reason))
        return SUM(playerid, "/unwarn [playerid] [reason]");

    if(!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

	if(AccountData[otherid][pWarn] == 0)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak memiliki warning!");

    AccountData[otherid][pWarn]--;

	static string[144];
	foreach(new i : Player) if(AccountData[i][pSpawned] && ToggleInfo[i][TogAdmCmd])
	{
		format(string, sizeof(string), "AdmCmd: %s has removed 1 warning from %s(%d).", AccountData[playerid][pAdminname], AccountData[otherid][pName], otherid);
		SendClientMessage(i, Y_LIGHTRED, string);
		format(string, sizeof(string), "Reason: %s", reason);
		SendClientMessage(i, Y_LIGHTRED, string);
	}
	return 1;
}

YCMD:kick(playerid, params[], help)
{
    static reason[64];

    if(AccountData[playerid][pAdmin] < 2)
        return PermissionError(playerid);

    new otherid;
    if (sscanf(params, "us[64]", otherid, reason))
        return SUM(playerid, "/kick [playerid/name] [reason]");

    if (!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    static string[144];

    ShowKickTD(otherid, AccountData[playerid][pAdminname], reason);

    foreach (new i : Player) if (AccountData[i][pSpawned] && ToggleInfo[i][TogAdmCmd]) {
        format(string, sizeof(string), "AdmCmd: %s(%d) has been kicked from the server by %s", AccountData[otherid][pName], otherid, AccountData[playerid][pAdminname]);
        SendClientMessage(i, Y_LIGHTRED, string);
        format(string, sizeof(string), "Reason: %s", reason);
        SendClientMessage(i, Y_LIGHTRED, string);
    }
    KickEx(otherid);
    return 1;
}

YCMD:jail(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 2)
        return PermissionError(playerid);

    new reason[64], timeSec, fine, otherid;
    if (sscanf(params, "dD(15)ds[64]", otherid, timeSec, fine, reason))
        return SUM(playerid, "/jail [playerid] [minutes] [fine] [reason]");

    if (!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke dalam server!");

    static string[144];
    if (OJailData[otherid][jailed]) 
    {
        format(string, sizeof(string), "[Jail] %s(%i) sedang dijail admin (Remaining %d minutes).", AccountData[otherid][pName], otherid, OJailData[otherid][jailTime] / 60);
        SendClientMessage(playerid, X11_LIGHTBLUE, string);
        SUM(playerid, "/unjail [playerid] untuk membebaskannya!");
        return 1;
    }

    if(!AccountData[otherid][pSpawned]) return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Player %s(%i) belum spawn!", AccountData[otherid][pName], otherid));

    if(strlen(reason) > 64)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Reason maksimum adalah 64 karakter!");
        
    if(timeSec < 1)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Waktu jail minimum adalah 1 menit!");

    if(timeSec > 30 && AccountData[playerid][pAdmin] < 3)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda hanya bisa memberikan waktu jail maksimum 30 menit!");

    if(timeSec > 60 && AccountData[playerid][pAdmin] < 4)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda hanya bisa memberikan waktu jail maksimum 60 menit!");
    
    if(timeSec > 120 && AccountData[playerid][pAdmin] < 5)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda hanya bisa memberikan waktu jail maksimum 120 menit!");

    OJailData[otherid][jailed] = true;
    strcopy(OJailData[otherid][jailAdmin], AccountData[playerid][pAdminname]);
    OJailData[otherid][jailTime] = timeSec * 60;
    OJailData[otherid][jailDur] = timeSec;
    strcopy(OJailData[otherid][jailReason], reason);
    OJailData[otherid][jailFine] = fine;        
    TakePlayerMoneyEx(otherid, fine);

    SendPlayerToJailAdmin(otherid);

    foreach (new i : Player)
    {
        if (AccountData[i][pSpawned] && ToggleInfo[i][TogAdmCmd]) {
            format(string, sizeof(string), "AdmCmd: %s(%i) has been OOC jailed by %s for %d minutes.", AccountData[otherid][pName], otherid, AccountData[playerid][pAdminname], timeSec);
            SendClientMessage(i, Y_LIGHTRED, string);
            format(string, sizeof(string), "Reason: %s", reason);
            SendClientMessage(i, Y_LIGHTRED, string);
        }
    }

    format(string, sizeof(string), "[Jail] Anda telah dijail OOC oleh %s selama %d menit, denda $%s [%s].", AccountData[playerid][pAdminname], timeSec, FormatMoney(fine), reason);
    SendClientMessage(otherid, Y_LIGHTRED, string);

    static year, month, day, keidwa[100], warsc[512];
    getdate(year, month, day);
    format(keidwa, sizeof(keidwa), "%02d/%02d/%d", day, month, year);

    for (new id; id < 100; ++id) {
        if (!PlayerWarning[otherid][id][warnExists]) {
            PlayerWarning[otherid][id][warnExists] = true;
            PlayerWarning[otherid][id][warnOwner] = AccountData[otherid][pID];
            PlayerWarning[otherid][id][warnType] = 2;
            strcopy(PlayerWarning[otherid][id][warnIssuer], AccountData[playerid][pAdminname]);
            strcopy(PlayerWarning[otherid][id][warnDate], keidwa);
            strcopy(PlayerWarning[otherid][id][warnDateTime], GetAdvTime());
            strcopy(PlayerWarning[otherid][id][warnReason], reason);
            break;
        }
    }

    mysql_format(g_SQL, warsc, sizeof(warsc), "INSERT INTO `player_warns` SET `Owner_ID` = %d, `Date` = '%e', `Date_Time` = '%e', `Issuer` = '%e', `Type` = 2, `Reason` = '%e'",
        AccountData[otherid][pID], keidwa, GetAdvTime(), AccountData[playerid][pAdminname], reason);
    mysql_pquery(g_SQL, warsc);

    return 1;
}

YCMD:fixes(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 2)
        return PermissionError(playerid);

    static string[1024];

    new count = 0;
    format(string, sizeof(string), "Player\tIssue\n");
    foreach (new i : Player) if (AccountData[i][pSpawned])
    {
        if(AccountData[i][pStuckRequest] > 0)
        {
            switch (AccountData[i][pStuckRequest])
            {
                case 1:
                {
                    format(string, sizeof(string), "%s"YELLOW"P%d: "WHITE"%s\tVisual Bug (WWID)\n", string, i, AccountData[i][pName]);
                }
                case 2:
                {
                    format(string, sizeof(string), "%s"YELLOW"P%d: "WHITE"%s\tCharacter Stuck\n", string, i, AccountData[i][pName]);
                }
                case 3:
                {
                    format(string, sizeof(string), "%s"YELLOW"P%d: "WHITE"%s\tCannot Move\n", string, i, AccountData[i][pName]);
                }
                case 4:
                {
                    format(string, sizeof(string), "%s"YELLOW"P%d: "WHITE"%s\tBug Balai Kota\n", string, i, AccountData[i][pName]);
                }
            }
            PlayerListitem[playerid][count++] = i;
        }
    }

    if (count > 0)
    {
        Dialog_Show(playerid, "FixesRequests", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Fix Request", string, "Pilih", "Batal");
    }
    else
    {
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Fix Request", "No active fix requests!", "Tutup", "");
    }
    return 1;
}

YCMD:afix(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 2)
        return PermissionError(playerid);

    if(!IsPlayerInAnyVehicle(playerid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di dalam kendaraan apapun!");

    new vid = GetPlayerVehicleID(playerid);
    foreach(new pv : PvtVehicles)
    {
        if(vid == PlayerVehicle[pv][pVehPhysic])
        {
            SetValidVehicleHealth(vid, VehicleCore[vid][vMaxHealth]);
            PlayerVehicle[pv][pVehHealth] = VehicleCore[vid][vMaxHealth];
            VehicleCore[vid][vIsBodyBroken] = false;
            UpdateVehicleDamageStatus(vid, 0, 0, 0, 0);
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah memperbaiki kendaraan ini!");
            return 1;
        }
    }
    SetValidVehicleHealth(vid, VehicleCore[vid][vMaxHealth]);
    VehicleCore[vid][vCoreHealth] = VehicleCore[vid][vMaxHealth];
    VehicleCore[vid][vIsBodyBroken] = false;
    UpdateVehicleDamageStatus(vid, 0, 0, 0, 0);
    ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah memperbaiki kendaraan ini!");

    //format(sclstr, sizeof(sclstr), "%s(%d) [%s] used the '/afix' command", AccountData[playerid][pAdminname], playerid, AccountData[playerid][pUCP]);
    //CallLocalFunction("StaffCommandLog", "is", playerid, sclstr);
    return 1;
}

YCMD:afuel(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 2)
        return PermissionError(playerid);

    if(!IsPlayerInAnyVehicle(playerid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di dalam kendaraan apapun!");

    VehicleCore[GetPlayerVehicleID(playerid)][vCoreFuel] = 100;
    ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mengisi ulang bahan bakar kendaraan ini!");

    //format(sclstr, sizeof(sclstr), "%s(%d) [%s] used the '/afuel' command", AccountData[playerid][pAdminname], playerid, AccountData[playerid][pUCP]);
    //CallLocalFunction("StaffCommandLog", "is", playerid, sclstr);
    return 1;
}

YCMD:setfuel(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 2) return PermissionError(playerid);

    new vehid, ammount;
    if(sscanf(params, "dd", vehid, ammount))
        return SUM(playerid, "/setfuel [vehicle id] [amount]");

    if(!IsValidVehicle(vehid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Vehicle ID!");

    VehicleCore[vehid][vCoreFuel] = ammount;
    SendAdm(playerid, "You have set the fuel for %s(%d) to %d.", GetVehicleModelName(GetVehicleModel(vehid)), vehid, ammount);
    return 1;
}

YCMD:veh(playerid, params[], help)
{
    static
        model[32],
        color1,
        color2;

    if(AccountData[playerid][pAdmin] < 2) return PermissionError(playerid);

    if(sscanf(params, "s[32]I(0)I(0)", model, color1, color2))
        return SUM(playerid, "/veh [model id/name] [color 1] [color 2]");

    if((model[0] = GetVehicleModelByName(model)) == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Model ID!");

    static
        Float:x,
        Float:y,
        Float:z,
        Float:a;

    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, a);

    for(new i; i < MAX_ADMIN_VEHICLES; i++)
    {
        if(GM[adminV][i] == INVALID_VEHICLE_ID)
        {
            GM[adminV][i] = CreateVehicle(model[0], x, y, z, a, color1, color2, 60000, false);
            VehicleCore[GM[adminV][i]][vCoreFuel] = 100;
            SetValidVehicleHealth(GM[adminV][i], 1000.0);
            VehicleCore[GM[adminV][i]][vCoreLocked] = false;
            VehicleCore[GM[adminV][i]][vMaxHealth] = 1000.0;
            VehicleCore[GM[adminV][i]][vIsBodyUpgraded] = false;
            VehicleCore[GM[adminV][i]][vIsBodyBroken] = false;
            SwitchVehicleEngine(GM[adminV][i], true);
            SwitchVehicleDoors(GM[adminV][i], false);

            if(GetPlayerInterior(playerid) != 0)
                LinkVehicleToInteriorEx(GM[adminV][i], GetPlayerInterior(playerid));

            if(GetPlayerVirtualWorld(playerid) != 0)
                SetVehicleVirtualWorldEx(GM[adminV][i], GetPlayerVirtualWorld(playerid));

            PutPlayerInVehicleEx(playerid, GM[adminV][i], 0);
            SetCameraBehindPlayer(playerid);
            SetVehicleParamsEx(GM[adminV][i], 1, 1, 0, 0, 0, 0, 0);
            SetVehicleNumberPlate(GM[adminV][i], ""RED"ADMIN");
            break;
        }

        if(i == (MAX_ADMIN_VEHICLES - 1))
        {
            ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan admin sudah mencapai (100). Mohon gunakan /adveh!");
        }
    }
    return 1;
}