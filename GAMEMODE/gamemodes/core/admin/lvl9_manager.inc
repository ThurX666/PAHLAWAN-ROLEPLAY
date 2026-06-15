YCMD:oreco(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 9)
	    return PermissionError(playerid);
	
	new player[24], PlayerName[MAX_PLAYER_NAME];
	if(sscanf(params, "s[24]", player))
		return SUM(playerid, "/oreco [name]");

	foreach(new ii : Player)
	{
		if(AccountData[ii][IsLoggedIn] && AccountData[ii][pSpawned])
		{
			GetPlayerName(ii, PlayerName, MAX_PLAYER_NAME);

			if(strfind(PlayerName, player, true) != -1)
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sedang online, gunakan '/reco' terhadapnya!");
		}
	}
	new query[512];
	mysql_format(g_SQL, query, sizeof(query), "SELECT `pID` FROM `player_characters` WHERE `Char_Name`='%e'", player);
	mysql_pquery(g_SQL, query, "OResetEconomy", "is", playerid, player);
	return 1;
}

YCMD:schedulemt(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 9)
		return PermissionError(playerid);

	static string[144];
	if(!GM[Maintenance])
	{
		new minutes;
		if(sscanf(params, "d", minutes)) return SUM(playerid, "/schedulemt [menit]");

		if(minutes < 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal 3 menit!");

		GM[Maintenance] = true;
		GM[MTTime] = gettime() + (minutes * 60);

		format(string, sizeof(string), "[Maintenance] %s telah menjadwalkan maintenance pada %s", AccountData[playerid][pAdminname], ReturnDate(GM[MTTime]));
		SendClientMessageToAll(Y_LIGHTRED, string);
	}
	else
	{
		GM[Maintenance] = false;
		GM[MTTime] = 0;

		format(string, sizeof(string), "[Maintenance] %s telah membatalkan jadwal maintenance, happy roleplay.", AccountData[playerid][pAdminname]);
		SendClientMessageToAll(Y_LIGHTRED, string);
	}
	return 1;
}

YCMD:removepv(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);

    new vehid, query[512];
    if (sscanf(params, "d", vehid))
        return SUM(playerid, "/removepv [VID]~n~Use /avehlist to find another player's vehicle VID!");

    if (!IsValidVehicle(vehid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Vehicle ID!");

    foreach(new i : PvtVehicles)
    {
        if (vehid == PlayerVehicle[i][pVehPhysic])
        {
            SendAdm(playerid, "You have removed a private vehicle with VID: %d (DBID: %d).", vehid, PlayerVehicle[i][pVehID]);
            SetVehicleNeonLights(PlayerVehicle[i][pVehPhysic], false, PlayerVehicle[i][pVehNeon], 0);

            PlayerVehicle[i][pVehHandbraked] = false;

            DestroyVehicle(PlayerVehicle[i][pVehPhysic]);
            mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `vehicle_bagasi` WHERE `Veh_DBID`=%d", PlayerVehicle[i][pVehID]);
            mysql_pquery(g_SQL, query);
            mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `vehicle_holster` WHERE `Veh_DBID`=%d", PlayerVehicle[i][pVehID]);
            mysql_pquery(g_SQL, query);
            mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `player_vehicles` WHERE `id` = %d", PlayerVehicle[i][pVehID]);
            mysql_pquery(g_SQL, query);

            mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `vtoys` WHERE `Veh_DBID`=%d", PlayerVehicle[i][pVehID]);
            mysql_pquery(g_SQL, query);

            for(new x; x < 6; x++)
            {
                vtData[i][x][vtoy_modelid] = 0;
                vtData[i][x][vtoy_text][0] = EOS;
                strcopy(vtData[i][x][vtoy_font], "Arial");
                vtData[i][x][vtoy_fontsize] = 11;
                vtData[i][x][vtoy_fontcolor][0] = 255;
                vtData[i][x][vtoy_fontcolor][1] = 0;
                vtData[i][x][vtoy_fontcolor][2] = 0;
                vtData[i][x][vtoy_fontcolor][3] = 0;
                vtData[i][x][vtoy_fontcolor][4] = 0;
                vtData[i][x][vtoy_objectcolor][0] = 255;
                vtData[i][x][vtoy_objectcolor][1] = 0;
                vtData[i][x][vtoy_objectcolor][2] = 0;
                vtData[i][x][vtoy_objectcolor][3] = 0;
                vtData[i][x][vtoy_objectcolor][4] = 0;
                vtData[i][x][vtoy_x] = 0.0;
                vtData[i][x][vtoy_y] = 0.0;
                vtData[i][x][vtoy_z] = 0.0;
                vtData[i][x][vtoy_rx] = 0.0;
                vtData[i][x][vtoy_ry] = 0.0;
                vtData[i][x][vtoy_rz] = 0.0;
            }

            for(new x; x < MAX_BAGASI_ITEMS; x++)
            {
                VehicleBagasi[i][x][vehicleBagasiExists] = false;
                VehicleBagasi[i][x][vehicleBagasiID] = 0;
                VehicleBagasi[i][x][vehicleBagasiVDBID] = 0;
                VehicleBagasi[i][x][vehicleBagasiTemp][0] = EOS;
                VehicleBagasi[i][x][vehicleBagasiModel] = 0;
                VehicleBagasi[i][x][vehicleBagasiQuant] = 0;
            }

            for(new z; z < 3; z++)
            {
                VehicleHolster[i][vHolsterTaken][z] = false;
                VehicleHolster[i][vHolsterID][z] = -1;
                VehicleHolster[i][vHolsterWeaponID][z] = 0;
                VehicleHolster[i][vHolsterWeaponAmmo][z] = 0;
            }
            Iter_Remove(PvtVehicles, i);
        }
    }
    return 1;
}

YCMD:setgender(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);

    new targetid, gender;
    if (sscanf(params, "dd", targetid, gender))
        return SUM(playerid, "/setgender [playerid] [1. Male | 2. Female]");

    if (!IsPlayerConnected(targetid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    
    if (!AccountData[targetid][IsLoggedIn])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    AccountData[targetid][pGender] = gender;
    SendClientMessageEx(targetid, Y_LIGHTRED, "AdmCmd: %s has set your character gender.", AccountData[playerid][pAdminname]);
    SendAdm(playerid, "You have set %s(%d) gender to %d", AccountData[targetid][pName], targetid, gender);
    return 1;
}

YCMD:setstock(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

	new type[24], somt[128];
	if(sscanf(params, "s[24]S()[128]", type, somt))
        return SUM(playerid, "/setstock [name] (komponen)");

	if(!strcmp(type, "komponen", true))
    {
		new value;
		if(sscanf(somt, "d", value))
			return SUM(playerid, "/setstock component [ammount]");

		GM[g_ComponentStock] = value;

		SendAdm(playerid, "You have set Komponen stock to %d.", value);
	}
	return 1;
}

YCMD:backup(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

	foreach(new id : FarmPlants) if(id != INVALID_ITERATOR_SLOT)
	{
		FarmPlant_Save(id);
	}
	
	static string[144];
	format(string, sizeof(string), "AdmCmd: %s telah menyimpan semua data server (backup).", AccountData[playerid][pAdminname]);
	
	foreach(new i : Player) if(AccountData[i][pSpawned])
	{
		Anticheat[i][acImmunity] = gettime() + 5;
		UpdateAccountData(i);
		SendClientMessage(i, Y_LIGHTRED, string);
	}
	return 1;
}

YCMD:dynhelp(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9)
		return PermissionError(playerid);
    
    Dialog_Show(playerid, "AdminDynamicHelp", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Dynamic Help", 
    "Dynamic Type\tDescription\n\
    Dynamic Actor\tContains commands related to dynamic actors\n\
    "GRAY"Dynamic Bike Rental\t"GRAY"Contains commands related to dynamic bicycle rentals\n\
    Dynamic Door\tContains commands related to dynamic doors/teleport doors\n\
    "GRAY"Dynamic Fivem Label\t"GRAY"Contains commands related to dynamic FiveM Label text\n\
    Dynamic Garage\tContains commands related to dynamic garages\n\
    "GRAY"Dynamic Garbage\t"GRAY"Contains commands related to dynamic garbage bins\n\
    Dynamic Cannabis\tContains commands related to dynamic cannabis plants\n\
    "GRAY"Dynamic Robbery\t"GRAY"Contains commands related to dynamic shop robberies\n\
    Dynamic Shop\tContains commands related to dynamic shops\n\
	"GRAY"Dynamic Button\t"GRAY"Contains commands related to dynamic door buttons", "Pilih", "Batal");
    return 1;
}

/*
YCMD:ahide(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);
		
	if(AccountData[playerid][pHiddenAdmin])
	{
		AccountData[playerid][pHiddenAdmin] = false;
		SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Status hidden anda telah dicabut.");
	}
	else
	{
		AccountData[playerid][pHiddenAdmin] = true;
		SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Status hidden anda telah diaktifkan.");
	}
	return 1;
}
*/

YCMD:changeplate(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);

    new vid, newplate[64], query[158];
    if(sscanf(params, "ds[64]", vid, newplate))
        return SUM(playerid, "/changeplate [vid] [plate]");

    if(!IsValidVehicle(vid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Vehicle tersebut tidak valid!");

    foreach(new i : PvtVehicles)
    {
        if(PlayerVehicle[i][pVehPhysic] == vid)
        {
            mysql_format(g_SQL, query, sizeof(query), "SELECT `PVeh_Plate` FROM `player_vehicles` WHERE `PVeh_Plate`='%e'", newplate);
            mysql_pquery(g_SQL, query, "ChangeVIPPlate", "ids", playerid, i, newplate);
            return 1;
        }
    }
    ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut bukan jenis kendaraan pribadi!");
    return 1;
}

YCMD:changephnumber(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);

    new otherid, newphnumb[22], query[158];
    if(sscanf(params, "us[22]", otherid, newphnumb))
        return SUM(playerid, "/changephnumber [playerid] [number]");

    if(!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if(!AccountData[otherid][pSpawned])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut belum spawn!");
    if(!IsNumericEx(newphnumb))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya dapat memuat angka!");
    if(strlen(newphnumb) < 4 || strlen(newphnumb) > 10)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Nomor hanya dapat berjumlah 4 - 10!");

    mysql_format(g_SQL, query, sizeof(query), "SELECT `phoneNumber` FROM `player_phones` WHERE `phoneNumber`='%e'", newphnumb);
    mysql_pquery(g_SQL, query, "ChangeVIPPHNumber", "iis", playerid, otherid, newphnumb);
    return 1;
}

YCMD:changebanknumber(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 9)
		return PermissionError(playerid);

	new otherid, newbrek[7], query[158];
	if(sscanf(params, "us[7]", otherid, newbrek))
        return SUM(playerid, "/changebanknumber [playerid] [number]");

	if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(!AccountData[otherid][pSpawned]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut belum spawn!");
    if(strlen(newbrek) < 4 || strlen(newbrek) > 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Nomor rekening harus berjumlah 4 - 6 digit!");
	mysql_format(g_SQL, query, sizeof(query), "SELECT `Char_BankNumber` FROM `player_characters` WHERE `Char_BankNumber`=%d", strval(newbrek));
    mysql_pquery(g_SQL, query, "ChangeVIPBankNumber", "iid", playerid, otherid, strval(newbrek));
	return 1;
}

YCMD:setstressall(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);

    new amount;
	if(sscanf(params, "d", amount))
        return SUM(playerid, "/setstressall [amount]");
    
	static string[215];
    foreach(new i : Player)
    {
        if(IsPlayerConnected(i))
        {
            if(AccountData[i][pSpawned])
            {
				SetPlayerDrunkLevel(i, 0);
                AccountData[i][pStress] = amount;

	            mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_Stress` = %d WHERE `pID` = %d", amount, AccountData[i][pID]);
                mysql_pquery(g_SQL, string);

                format(string, sizeof(string), "AdmCmd: %s has set the stress for all characters to %d.", AccountData[playerid][pAdminname], amount);
				SendClientMessage(i, Y_LIGHTRED, string);
            }
        }
    }
    return 1;
}

YCMD:setarmorall(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);

    new Float:amount;
	if(sscanf(params, "f", amount))
        return SUM(playerid, "/setarmorall [amount]");
    
	static string[215];
    foreach(new i : Player)
    {
        if(IsPlayerConnected(i))
        {
            if(AccountData[i][pSpawned])
            {
                AccountData[i][pArmor] = amount;

                if(amount > 100)
                {
                    SetPlayerArmourEx(i, 100);
	                mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_Armor` = '98' WHERE `pID` = %d", amount, AccountData[i][pID]);
                    mysql_pquery(g_SQL, string);
                }
                else
                {
                    SetPlayerArmourEx(i, amount);
	                mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_Armor` = '%.3f' WHERE `pID` = %d", amount, AccountData[i][pID]);
                    mysql_pquery(g_SQL, string);
                }

                format(string, sizeof(string), "AdmCmd: %s has set the armor for all characters to %.2f.", AccountData[playerid][pAdminname], amount);
				SendClientMessage(i, Y_LIGHTRED, string);
            }
        }
    }
    return 1;
}

YCMD:sethbeall(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);

    new amount;
	if(sscanf(params, "d", amount))
        return SUM(playerid, "/sethbeall [amount]");
    
	static string[215];
    foreach(new i : Player)
    {
        if(IsPlayerConnected(i))
        {
            if(AccountData[i][pSpawned])
            {
                AccountData[i][pHunger] = amount;
	            AccountData[i][pThirst] = amount;
	            mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_Hunger` = %d, `Char_Thirst` = %d WHERE `pID` = %d", amount, amount, AccountData[i][pID]);
                mysql_pquery(g_SQL, string);

	            SetPlayerDrunkLevel(i, 0);

                format(string, sizeof(string), "AdmCmd: %s has set the Hunger and Thirst for all characters to %d.", AccountData[playerid][pAdminname], amount);
				SendClientMessage(i, Y_LIGHTRED, string);
            }
        }
    }
    return 1;
}

YCMD:gethereall(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 9)
     	return PermissionError(playerid);

	static string[144];
	foreach(new i : Player)
    {
        if(IsPlayerConnected(i))
        {
            if(AccountData[i][pSpawned])
            {
				if(!OJailData[i][jailed])
				{
					if(!AccountData[i][pArrested])
					{
						SendPlayerToPlayer(i, playerid);
						format(string, sizeof(string), "AdmCmd: %s has teleported all characters to their positions.", AccountData[playerid][pAdminname]);
						SendClientMessage(i, Y_LIGHTRED, string);
					}
				}
            }
        }
    }
	return 1;
}