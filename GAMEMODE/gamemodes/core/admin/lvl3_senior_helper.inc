YCMD:gethere(playerid, params[], help)
{
    new otherid;

    if(AccountData[playerid][pAdmin] < 3)
        return PermissionError(playerid);

    if (sscanf(params, "d", otherid))
        return SUM(playerid, "/gethere [playerid]");

    if (!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    if (otherid == playerid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya terhadap diri sendiri!");

    if (!AccountData[playerid][pSpawned] || !AccountData[otherid][pSpawned])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda/Pemain tersebut belum spawn!");

    if (OJailData[playerid][jailed] || OJailData[otherid][jailed])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda/Pemain tersebut sedang di jail admin!");

    static string[144];
    SendPlayerToPlayer(otherid, playerid);
    format(string, sizeof(string), "AdmCmd: %s teleported you to their position.", AccountData[playerid][pAdminname]);
    SendClientMessage(otherid, Y_LIGHTRED, string);
    SendAdm(playerid, "You have teleported %s to your position.", AccountData[otherid][pName]);
    return 1;
}

YCMD:slap(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 3)
		return PermissionError(playerid);
			
	new Float:POS[3], otherid;
	if (sscanf(params, "d", otherid))
	    return SUM(playerid, "/slap [playerid]");

	if (!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

	GetPlayerPos(otherid, POS[0], POS[1], POS[2]);
	SetPlayerPos(otherid, POS[0], POS[1], POS[2] + 9.0);
	if (IsPlayerInAnyVehicle(otherid)) 
	{
		RemovePlayerFromVehicle(otherid);
	}
	SendAdm(playerid, "You have used '/slap' on %s(%d).", AccountData[otherid][pName], otherid);

	PlayerPlaySound(otherid, 1130, 0.0, 0.0, 0.0);

	return 1;
}

YCMD:freeze(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 3)
        return PermissionError(playerid);

    new otherid;
    if (sscanf(params, "d", otherid))
        return SUM(playerid, "/freeze [playerid]");

    if (!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    AccountData[playerid][pFreeze] = true;

    static string[144];
    TogglePlayerControllable(otherid, false);
    format(string, sizeof(string), "AdmCmd: %s froze your movement.", AccountData[playerid][pAdminname]);
    SendClientMessage(otherid, Y_LIGHTRED, string);
    SendAdm(playerid, "You have froze %s(%d).",AccountData[otherid][pName], otherid);

    return 1;
}

YCMD:unfreeze(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 3)
     	return PermissionError(playerid);

	new otherid;
    if(sscanf(params, "d", otherid))
        return SUM(playerid, "/unfreeze [playerid]");

    if(!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    AccountData[playerid][pFreeze] = false;

	static string[144];
    TogglePlayerControllable(otherid, true);
	format(string, sizeof(string), "AdmCmd: %s has allowed your movement.", AccountData[playerid][pAdminname]);
	SendClientMessage(otherid, Y_LIGHTRED, string);
	SendAdm(playerid, "You have allowed the movement of %s(%d).", AccountData[otherid][pName], otherid);

	return 1;
}

YCMD:getip(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 3)
        return PermissionError(playerid);

    new otherid, PlayerIP[16], giveplayer[24];
    if (sscanf(params, "d", otherid))
        return SUM(playerid, "/getip [playerid]");

    if (!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    static string[144];
    if (AccountData[otherid][pAdmin] >= 6) {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melihat IP admin lebih tinggi!");
        format(string, sizeof(string), "AdmCmd: %s(%i) attempted to view your IP Address.", AccountData[playerid][pAdminname], playerid);
        SendClientMessage(otherid, Y_LIGHTRED, string);
        return 1;
    }

    GetPlayerName(otherid, giveplayer, sizeof(giveplayer));
    GetPlayerIp(otherid, PlayerIP, sizeof(PlayerIP));

    format(string, sizeof(string), "AdmCmd: IP Address of %s(%i): %s", giveplayer, otherid, PlayerIP);
    SendClientMessage(playerid, Y_LIGHTRED, string);
    return 1;
}

YCMD:akaip(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 3)
        return PermissionError(playerid);

    new query[128];
    if (isnull(params))
        return SUM(playerid, "/akaip [IP]");

    mysql_format(g_SQL, query, sizeof(query), "SELECT `UCP` FROM `player_ucp` WHERE `IP`='%e'", params);
    mysql_pquery(g_SQL, query, "CheckPlayerIP2", "is", playerid, params);
    return 1;
}

YCMD:checkucp(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 3)
        return PermissionError(playerid);

    new name[22];
    if (sscanf(params, "s[22]", name))
        return SUM(playerid, "/checkucp [ucp name]");

    // Load User Data
    new cVar[500];
    new cQuery[600];

    strcat(cVar, "ID, UCP, IP, Register_Date, Last_Login");

    mysql_format(g_SQL, cQuery, sizeof(cQuery), "SELECT %s FROM `player_ucp` WHERE `UCP`='%e' LIMIT 1", cVar, name);
    mysql_pquery(g_SQL, cQuery, "CheckingUCP", "is", playerid, name);
    return 1;
}

YCMD:acharlist(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 3)
        return PermissionError(playerid);

    new name[22];
    if (sscanf(params, "s[22]", name))
        return SUM(playerid, "/acharlist [ucp name]");

    new cQuery[512];
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "SELECT * FROM `player_ucp` WHERE `UCP`='%e' LIMIT 1", name);
    mysql_pquery(g_SQL, cQuery, "CheckingCharList", "is", playerid, name);
    return 1;
}

YCMD:rveh(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 3)
		return PermissionError(playerid);

	new vehid, Float:posX, Float:posY, Float:posZ;
	if(sscanf(params, "d", vehid)) return SUM(playerid, "/rveh [vehicleid] (Use /avehlist to find the vehicle ID)");

	if (vehid == INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Vehicle ID!");
    if (!IsValidVehicle(vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Vehicle ID!");
	GetVehiclePos(vehid, posX, posY, posZ);
	if(IsVehicleEmpty(vehid))
	{
		SetTimerEx("RespawnPV", 1000, false, "d", vehid);
		SendAdm(playerid, "You have respawned Vehicle ID: %d (%s).", vehid, GetLocation(posX, posY, posZ));
	}
	else ShowTDN(playerid, NOTIFICATION_ERROR, "Vehicle ID tersebut sedang digunakan!");
	return 1;
}

YCMD:arevive(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 3)
        return PermissionError(playerid);

    new otherid;
    if(sscanf(params, "d", otherid))
        return SUM(playerid, "/arevive [playerid]");

    if(!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    if(AccountData[otherid][pKnockdown] == false)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak sedang pingsan!");

    HideKnockTD(otherid);
    SetPlayerHealthEx(otherid, 100.0);
    AccountData[otherid][pKnockdown] = false;
    AccountData[otherid][pKnockdownTime] = 0;
    AccountData[otherid][pHunger] = 50;
    AccountData[otherid][pThirst] = 50;
    AccountData[otherid][pStress] = 0;

    DeathCause[otherid][Bruised] = false;
    DeathCause[otherid][Shoted] = false;
    DeathCause[otherid][Burns] = false;
    DeathCause[otherid][Drown] = false;
    DeathCause[otherid][Fallen] = false;

    new frmtsql[215];
    mysql_format(g_SQL, frmtsql, sizeof(frmtsql), "UPDATE `player_characters` SET `Char_Knockdown` = 0, `Char_KnockdownTime` = 0, `Char_Hunger` = 50, `Char_Thirst` = 50, `Char_Stress` = 0 WHERE `pID` = %d", AccountData[otherid][pID]);
    mysql_pquery(g_SQL, frmtsql);

    StopRunningAnimation(otherid);

    SendAdm(playerid, "You have revived %s(%d).", AccountData[otherid][pName], otherid);

    static string[144];
    format(string, sizeof(string), "AdmCmd: %s has revived your character.",AccountData[playerid][pAdminname]);
    SendClientMessage(otherid, Y_LIGHTRED, string);
    return 1;
}

YCMD:sethp(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 3)
        return PermissionError(playerid);

    new Float:amount, otherid;
    if(sscanf(params, "uf", otherid, amount))
        return SUM(playerid, "/sethp [playerid/name] [amount]");

    if(!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    SetPlayerHealthEx(otherid, amount);

    static string[144];
    format(string, sizeof(string), "AdmCmd: %s has set your character's health to %.2f.",AccountData[playerid][pAdminname], amount);
    SendClientMessage(otherid, Y_LIGHTRED, string);

    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set %s (%d) health to %.2f.", AccountData[playerid][pAdminname], AccountData[otherid][pName], otherid, amount);
    return 1;
}

YCMD:setarmor(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 3)
        return PermissionError(playerid);

    new Float:amount, otherid;
    if (sscanf(params, "uf", otherid, amount))
        return SUM(playerid, "/setam [playerid/name] [amount]");

    if (!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    if (amount > 100.0)
    {
        SetPlayerArmourEx(otherid, 100.0);
    }
    else
    {
        SetPlayerArmourEx(otherid, amount);
    }
    static string[144];
    format(string, sizeof(string), "AdmCmd: %s has set your character's armor to %.2f.", AccountData[playerid][pAdminname], amount);
    SendClientMessage(otherid, Y_LIGHTRED, string);

    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set %s (%d) armor to %.2f.", AccountData[playerid][pAdminname], AccountData[otherid][pName], otherid, amount);
    return 1;
}
YCMD:setam(playerid, params[], help) = setarmor;

YCMD:getin(playerid, params[], help)
{
    new vid;
    if(AccountData[playerid][pAdmin] < 3)
        return PermissionError(playerid);

    if (sscanf(params, "d", vid)) return SUM(playerid, "/getin [vehicleid]");
    if (!IsValidVehicle(vid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Vehicle ID!");

    PutPlayerInVehicleEx(playerid, vid, 0);
    return 1;
}

YCMD:takeoutveh(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 3)
        return PermissionError(playerid);

    new otherid;
    if(sscanf(params, "d", otherid)) return SUM(playerid, "/takeoutveh [playerid]");
    if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if(!AccountData[otherid][pSpawned]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut belum spawn!");

    new bool:found = false, msg2[1618];
    format(msg2, sizeof(msg2), "Model [Database ID]\tPlate\t/ Status\n");
    foreach (new i : PvtVehicles)
    {
        if (PlayerVehicle[i][pVehOwnerID] == AccountData[otherid][pID] && PlayerVehicle[i][pVehPhysic] == INVALID_VEHICLE_ID)
        {
            if (strcmp(PlayerVehicle[i][pVehPlate], "-")) // If it has a valid plate
            {
                if (PlayerVehicle[i][pVehRentTime] != 0) // If it's a rental vehicle with a plate
                {
                    format(msg2, sizeof(msg2), "%s%s [%d]\t%s\t/ %s\n", msg2, GetVehicleModelName(PlayerVehicle[i][pVehModelID]), PlayerVehicle[i][pVehID], PlayerVehicle[i][pVehPlate], GetMyVehicleStatus(i));
                    found = true;
                }
                else // If it's not a rental but has a plate
                {
                    format(msg2, sizeof(msg2), "%s%s [%d]\t%s\t/ Dimiliki / %s\n", msg2, GetVehicleModelName(PlayerVehicle[i][pVehModelID]), PlayerVehicle[i][pVehID], PlayerVehicle[i][pVehPlate], GetMyVehicleStatus(i));
                    found = true;
                }
            }
            else // If it has no plate
            {
                if (PlayerVehicle[i][pVehRentTime] != 0) // If it's a rental vehicle with no plate
                {
                    format(msg2, sizeof(msg2), "%s%s [%d]\tNo Plate\t/ %s\n", msg2, GetVehicleModelName(PlayerVehicle[i][pVehModelID]), PlayerVehicle[i][pVehID], GetMyVehicleStatus(i));
                    found = true;
                }
                else // If it's not a rental and has no plate
                {
                    format(msg2, sizeof(msg2), "%s%s [%d]\tNo Plate\t/ Dimiliki / %s\n", msg2, GetVehicleModelName(PlayerVehicle[i][pVehModelID]), PlayerVehicle[i][pVehID], GetMyVehicleStatus(i));
                    found = true;
                }
            }
        }
    }
    if (found)
        Dialog_Show(playerid, "AdmTakeoutVeh", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Keluarkan Kendaraan", msg2, "Pilih", "Tutup");
    else
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Keluarkan Kendaraan", "Tidak ada kendaraan milik pemain tersebut yang dapat dikeluarkan!", "Tutup", "");

    AccountData[playerid][pTempValue] = otherid;
    return 1;
}

YCMD:cd(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 3)
        return PermissionError(playerid);

    if(Count != -1)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Countdown sedang dimulai!");

    Count = 6;
    countTimer = SetTimer("pCountDown", 1000, true);

    foreach(new ii : Player)
    {
        showCD[ii] = 1;
    }
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has started the global countdown.", AccountData[playerid][pAdminname]);
    return 1;
}

YCMD:gotoveh(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 3)
		return PermissionError(playerid);

	new vehid, Float:posX, Float:posY, Float:posZ;
	if(sscanf(params, "d", vehid)) 
		return SUM(playerid, "/gotoveh [vehicleid] (Use /avehlist to find the vehicle ID)");

	if (vehid == INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Vehicle ID!");
    if (!IsValidVehicle(vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Vehicle ID!");
	
	AccountData[playerid][pInRusun] = -1;
	AccountData[playerid][pInHouse] = -1;
	AccountData[playerid][pInBiz] = -1;
	AccountData[playerid][pInDoor] = -1;
	AccountData[playerid][pInGudang] = -1;

	GetVehiclePos(vehid, posX, posY, posZ);
	SetPlayerPositionEx(playerid, posX, posY, posZ+3.0, 0.0);
	SetPlayerInteriorEx(playerid, VehicleCore[vehid][vInterior]);
	SetPlayerVirtualWorldEx(playerid, VehicleCore[vehid][vWorld]);

	return 1;
}

YCMD:avehlist(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 3)
		return PermissionError(playerid);

	new otherid;
	if(sscanf(params, "i", otherid)) return SUM(playerid, "/avehlist [playerid]");
	if(otherid == INVALID_PLAYER_ID || !IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi di server!");

	new bool:found = false, msg2[1618];
	format(msg2, sizeof(msg2), "VID\tModel [Database ID]\tPlate\t/ Rental / Status\n");
	foreach(new i : PvtVehicles)
	{
		if(PlayerVehicle[i][pVehOwnerID] == AccountData[otherid][pID])
		{
			if(strcmp(PlayerVehicle[i][pVehPlate], "-")) // If it has a plate
			{
				if(PlayerVehicle[i][pVehRentTime] != 0) // If it's a rental and has a plate
				{
					format(msg2, sizeof(msg2), "%s%s\t%s [%d]\t%s\t/ %s / %s\n", msg2,  (PlayerVehicle[i][pVehPhysic] == INVALID_VEHICLE_ID) ? ("[Not Spawned]") : (sprintf("[%d]", PlayerVehicle[i][pVehPhysic])), GetVehicleModelName(PlayerVehicle[i][pVehModelID]), PlayerVehicle[i][pVehID], PlayerVehicle[i][pVehPlate], ReturnTimelapse(gettime(), PlayerVehicle[i][pVehRentTime], ""YELLOW"Rental Expired"WHITE""), GetMyVehicleStatus(i));
					found = true;
				}
				else // If it's not a rental but has a plate
				{
					format(msg2, sizeof(msg2), "%s%s\t%s [%d]\t%s\t/ Dimiliki / %s\n", msg2, (PlayerVehicle[i][pVehPhysic] == INVALID_VEHICLE_ID) ? ("[Not Spawned]") : (sprintf("[%d]", PlayerVehicle[i][pVehPhysic])), GetVehicleModelName(PlayerVehicle[i][pVehModelID]), PlayerVehicle[i][pVehID], PlayerVehicle[i][pVehPlate], GetMyVehicleStatus(i));
					found = true;
				}
			}
			else // If it doesn't have a plate
			{
				if(PlayerVehicle[i][pVehRentTime] != 0) // If it's a rental but doesn't have a plate
				{
					format(msg2, sizeof(msg2), "%s%s\t%s [%d]\tTidak Ada Plat\t/ %s / %s\n", msg2, (PlayerVehicle[i][pVehPhysic] == INVALID_VEHICLE_ID) ? ("[Not Spawned]") : (sprintf("[%d]", PlayerVehicle[i][pVehPhysic])), GetVehicleModelName(PlayerVehicle[i][pVehModelID]), PlayerVehicle[i][pVehID], ReturnTimelapse(gettime(), PlayerVehicle[i][pVehRentTime], ""YELLOW"Rental Expired"WHITE""), GetMyVehicleStatus(i));
					found = true;
				}
				else // If it's not a rental and doesn't have a plate
				{
					format(msg2, sizeof(msg2), "%s%s\t%s [%d]\tTidak Ada Plat\t/ Dimiliki / %s\n", msg2, (PlayerVehicle[i][pVehPhysic] == INVALID_VEHICLE_ID) ? ("[Not Spawned]") : (sprintf("[%d]", PlayerVehicle[i][pVehPhysic])), GetVehicleModelName(PlayerVehicle[i][pVehModelID]), PlayerVehicle[i][pVehID], GetMyVehicleStatus(i));
					found = true;
				}
			}
		}
	}
	if(found)
		Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Vehicle Ownership", msg2, "Tutup", "");
	else
		Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Vehicle Ownership", "You do not own any vehicles!", "Tutup", "");
	
	return 1;
}

YCMD:reloadweap(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 3)
        return PermissionError(playerid);

    new otherid;
    if (sscanf(params, "d", otherid))
        return SUM(playerid, "/reloadweap [playerid]");

    if (!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    SetWeapons(otherid);

    static string[144];
    format(string, sizeof(string), "AdmCmd: %s has reloaded your weapons.", AccountData[playerid][pAdminname]);
    SendClientMessage(otherid, Y_LIGHTRED, string);

    SendAdm(playerid, "You have reloaded weapons for %s(%d).", AccountData[otherid][pName], otherid);

    return 1;
}