YCMD:akill(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 5)
        return PermissionError(playerid);

	new otherid;
	if(sscanf(params, "d", otherid))
	    return SUM(playerid, "/akill [playerid]");

    if(!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

	SetPlayerHealth(otherid, 0.0);

	SendAdm(playerid, "You have forcely killed %s(%d).", AccountData[otherid][pName], otherid);

	return 1;
}

YCMD:ojail(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 5)
        return PermissionError(playerid);

    new player[24], datez, tmp[64], PlayerName[MAX_PLAYER_NAME];
    if (sscanf(params, "s[24]ds[64]", player, datez, tmp))
        return SUM(playerid, "/ojail [name] [minutes] [reason]");

    if (strlen(tmp) > 32) return ShowTDN(playerid, NOTIFICATION_ERROR, "Reason maksimum adalah 32 karakter!");
    if (datez < 1)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal waktu jail adalah 1 menit!");

    foreach (new ii : Player) {
        GetPlayerName(ii, PlayerName, MAX_PLAYER_NAME);

        if (strfind(PlayerName, player, true) != -1)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sedang online, gunakan '/jail'!");
    }
    new query[512];
    mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `player_characters` WHERE `Char_Name`='%e'", player);
    mysql_pquery(g_SQL, query, "OSendPlayerToJailAdmin", "issd", playerid, player, tmp, datez);
    return 1;
}

YCMD:resetweap(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 5)
        return PermissionError(playerid);

    new otherid;
    if (sscanf(params, "d", otherid))
        return SUM(playerid, "/resetweap [playerid]");

    if (!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    ResetPlayerWeaponsEx(otherid);

    static string[144];
    format(string, sizeof(string), "AdmCmd: %s has reset all your weapons.", AccountData[playerid][pAdminname]);
    SendClientMessage(otherid, Y_LIGHTRED, string);

    SendAdm(playerid, "You have reset weapons for %s(%d).", AccountData[otherid][pName], otherid);

    return 1;
}

YCMD:fine(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 5)
        return PermissionError(playerid);

    new money, reason[64], otherid;
    if (sscanf(params, "dds[64]", otherid, money, reason))
        return SUM(playerid, "/fine [playerid] [amount] [reason]");

    if (!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    TakePlayerMoneyEx(otherid, money);

    static string[144];
    foreach (new i : Player) if (AccountData[i][pSpawned] && ToggleInfo[i][TogAdmCmd])
    {
        format(string, sizeof(string), "AdmCmd: %s(%d) has been fined by %s for $%s", AccountData[otherid][pName], otherid, AccountData[playerid][pAdminname], FormatMoney(money));
        SendClientMessage(i, Y_LIGHTRED, string);
        format(string, sizeof(string), "Reason: %s", reason);
        SendClientMessage(i, Y_LIGHTRED, string);
    }

    return 1;
}

YCMD:rpschooltext(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 5)
	    return PermissionError(playerid);

    new string[144];

    if(sscanf(params, "s[144]", string)) return SUM(playerid, "/rpschooltext [text]");

    ReplaceText(string, "(n)", "\n");
    ReplaceText(string, "(r)", "{FF0000}"); // red
    ReplaceText(string, "(b)", "{0E0101}"); // black
    ReplaceText(string, "(y)", "{FFFF00}"); // yellow
    ReplaceText(string, "(bl)", "{0000FF}"); // blue
    ReplaceText(string, "(g)", "{00FF00}"); // green
    ReplaceText(string, "(o)", "{FFA500}"); // orange
    ReplaceText(string, "(w)", "{FFFFFF}"); // white

    SetDynamicObjectMaterialText(RPSchoolText, 0, string, 120, "Arial", 15, 1, 0xFFFFFFFF, 0x00000000, 1);
    return 1;
}

YCMD:resetcd(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 5)
		return PermissionError(playerid);

	new otherid;
	if(sscanf(params, "d", otherid)) return SUM(playerid, "/resetcd [playerid]");

	if(!IsPlayerConnected(otherid) && !AccountData[otherid][pSpawned]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut belum spawn/tidak terkoneksi ke server!");

	AccountData[otherid][pMowingSidejobDelay] = 0;
	AccountData[otherid][pSweeperSidejobDelay] = 0;
	AccountData[otherid][pForkliftSidejobDelay] = 0;
	AccountData[otherid][pPizzaSidejobDelay] = 0;

	static string[144];
	format(string, sizeof(string), "AdmCmd: %s has reset your character's side job cooldowns.", AccountData[playerid][pAdminname]);
	SendClientMessage(otherid, Y_LIGHTRED, string);
	SendAdm(playerid, "You reset the side job cooldowns for %s(%d).", AccountData[otherid][pName], otherid);
	return 1;
}

YCMD:resetcdcarsteal(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 5)
		return PermissionError(playerid);

	if(g_CarstealCooldown == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Carsteal tidak dalam masa cooldown!");
	g_CarstealCooldown = 0;

	SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has reset the carsteal cooldown.", AccountData[playerid][pAdminname]);
	return 1;
}

YCMD:resetcdrobbery(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 5)
		return PermissionError(playerid);

	GM[ShopRobberyCooldown] = 0;

	SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has reset the shop robbery cooldown.", AccountData[playerid][pAdminname]);
	//format(sclstr, sizeof(sclstr), "%s(%d) [%s] used CMD '/resetcdrobbery'", AccountData[playerid][pAdminname], playerid, AccountData[playerid][pUCP]);
	//CallLocalFunction("StaffCommandLog", "is", playerid, sclstr);
	return 1;
}

YCMD:playnearsong(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 5)
        return PermissionError(playerid);

    new songname[128], tmp[512], Float:x, Float:y, Float:z;
    if (sscanf(params, "s[128]", songname))
        return SUM(playerid, "/playnearsong [link]");

    GetPlayerPos(playerid, x, y, z);
    format(tmp, sizeof(tmp), "%s", songname);
    foreach(new ii : Player)
    {
        if (IsPlayerInRangeOfPoint(ii, 35.0, x, y, z))
        {
            PlayAudioStreamForPlayer(ii, tmp, x, y, z, 35.0, 1);
            SendClientMessage(ii, Y_LIGHTRED, "AdmCmd: Gunakan '/stopsong' untuk memberhentikan musik admin.");
        }
    }
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s used the '/playnearsong' command.", AccountData[playerid][pAdminname]);
    return 1;
}

YCMD:sann(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 5)
        return PermissionError(playerid);

	new otherid, msg[64];
	if(sscanf(params, "is[64]", otherid, msg)) return SUM(playerid, "/sann [otherid] [message]");

	if(!IsPlayerConnected(otherid) && !AccountData[otherid][pSpawned]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Player belum spawn/tidak terkoneksi ke server!");

	GameTextForPlayer(otherid, msg, 5000, 4);
	ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mengirimkan pesan kepada Pemain tersebut.");
	return 1;
}

YCMD:settime(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 5)
        return PermissionError(playerid);

	new time;
	if(sscanf(params, "d", time))
		return SUM(playerid, "/settime [time]");

	static string[144];
	format(string, sizeof(string), "(Server) "WHITE"Pengurus "RED"%s "WHITE"telah mengganti waktu server.", AccountData[playerid][pAdminname]);

	SetWorldTime(time);
	WorldTime = time;
	foreach(new ii : Player)
	{
		SetPlayerTime(ii, time, 0);
		SendClientMessage(ii, Y_SERVER, string);
	}
	return 1;
}

YCMD:setweather(playerid, params[], help)
{
    new weatherid;

    if(AccountData[playerid][pAdmin] < 5)
        return PermissionError(playerid);

    if(sscanf(params, "d", weatherid))
        return SUM(playerid, "/setweather [weather ID]");

    SetWeather(weatherid);
	WorldWeather = weatherid;
	static string[144];
	format(string, sizeof(string), "(Server) "WHITE"Pengurus "RED"%s "WHITE"telah mengganti cuaca server.", AccountData[playerid][pAdminname]);
	foreach(new ii : Player)
	{
		SetPlayerWeather(ii, weatherid);
    	SendClientMessage(ii, Y_SERVER, string);
	}

    return 1;
}

YCMD:ginsu(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 5)
        return PermissionError(playerid);
        
    new countdown;
    if(sscanf(params, "d", countdown)) return SUM(playerid, "/ginsu [menit]");

    if(countdown < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat kurang dari 2 menit!");
    if(countdown > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat lebih dari 5 menit!");

    GM[GInsuTime] = countdown * 60;
    SendClientMessageToAllEx(Y_LIGHTRED, "AdmCmd: %s telah memulai %d menit asuransi keliling.", AccountData[playerid][pAdminname], GM[GInsuTime]/60);

    ShowAsuransiTD(sprintf("%d menit %d detik asuransi keliling.", GM[GInsuTime]/60%60, GM[GInsuTime]%3600%60));
    return 1;
}