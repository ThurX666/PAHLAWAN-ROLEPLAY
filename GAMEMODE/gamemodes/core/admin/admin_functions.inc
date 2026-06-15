#include <YSI_Coding\y_hooks>

forward LoadPlayerWarns(playerid);
public LoadPlayerWarns(playerid)
{
	if (cache_num_rows() > 0)
	{
		for (new x; x < cache_num_rows(); x++)
		{
			if (!PlayerWarning[playerid][x][warnExists])
			{
				PlayerWarning[playerid][x][warnExists] = true;
				cache_get_value_name_int(x, "Owner_ID", PlayerWarning[playerid][x][warnOwner]);
				cache_get_value_name_int(x, "Type", PlayerWarning[playerid][x][warnType]);
				cache_get_value_name(x, "Issuer", PlayerWarning[playerid][x][warnIssuer]);
				cache_get_value_name(x, "Date", PlayerWarning[playerid][x][warnDate]);
				cache_get_value_name(x, "Date_Time", PlayerWarning[playerid][x][warnDateTime]);
				cache_get_value_name(x, "Reason", PlayerWarning[playerid][x][warnReason]);
			}
		}
		printf("[Player Warns] Total number of warnings loaded for %s [DBID: %d]: %d.", AccountData[playerid][pUCP], AccountData[playerid][pID], cache_num_rows());
	}
	return 1;
}

forward CloseAnnounceTD();
public CloseAnnounceTD()
{
	TextDrawHideForAll(AnnounceTD[0]);
	TextDrawHideForAll(AnnounceTD[1]);
	TextDrawHideForAll(AnnounceTD[2]);
	return 1;
}

forward OnJobVehicleDestroyed();
public OnJobVehicleDestroyed()
{
	foreach (new i : Player)
	{
		if(Iter_Contains(Vehicle, JobVehicle[i]) && !IsVehicleSeatOccupied(JobVehicle[i], 0))
		{
			DestroyVehicle(JobVehicle[i]);
			DestroyVehicle(TrailerVehicle[i]);
		}

		SendClientMessage(i, Y_LIGHTRED, "AdmCmd: Seluruh kendaraan Job & Sidejob yang tidak dinaiki sudah dimusnahkan.");
	}
	return 1;
}

forward pCountDown();
public pCountDown()
{
	Count--;
	if (0 >= Count)
	{
		Count = -1;
		KillTimer(countTimer);
		countTimer = -1;
		foreach (new ii : Player)
		{
			if (showCD[ii] == 1)
			{
				GameTextForPlayer(ii, "~w~GO~r~!~g~!~b~!", 2500, 6);
				PlayerPlaySound(ii, 1057, 0, 0, 0);
				showCD[ii] = 0;
			}
		}
	}
	else
	{
		foreach (new ii : Player)
		{
			if (showCD[ii] == 1)
			{
				GameTextForPlayer(ii, CountText[Count - 1], 2500, 6);
				PlayerPlaySound(ii, 1056, 0, 0, 0);
			}
		}
	}
	return 1;
}

forward RespawnPV(vehicleid);
public RespawnPV(vehicleid)
{
	RespawnVehicle(vehicleid);
	return 1;
}

forward CheckPlayerIP(playerid, const zplayerIP[]);
public CheckPlayerIP(playerid, const zplayerIP[])
{
	new count = cache_num_rows(), datez, line[248], tstr[64], lstr[128];
	if (count)
	{
		datez = 0;
		line = "";
		format(line, sizeof(line), "Some names registered under IP: %s:\n\n", zplayerIP);
		for (new i = 0; i != count; i++)
		{
			// Get the name from the cache and append it to the dialog content
			cache_get_value_index(i, 0, lstr);
			strcat(line, lstr);
			datez++;

			if (datez == 5)
				strcat(line, "\n"), datez = 0;
			else
				strcat(line, "\t\t");
		}

		tstr = "Multiple accounts on one IP: ";
		strcat(tstr, zplayerIP);
		Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, tstr, line, "Tutup", "");
	}
	else
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada akun lain dari IP tersebut!");
	}
	return 1;
}

forward CheckPlayerIP2(playerid, const zplayerIP[]);
public CheckPlayerIP2(playerid, const zplayerIP[])
{
	new rows = cache_num_rows(), datez, line[248], tstr[64], lstr[128];
	if (!rows)
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada akun lain dari IP tersebut!");
		return 1;
	}
	else
	{
		datez = 0;
		line = "";
		format(line, sizeof(line), "Some names registered under IP: %s:\n\n", zplayerIP);
		for (new i = 0; i != rows; i++)
		{
			// Get the name from the cache and append it to the dialog content
			cache_get_value_index(i, 0, lstr);
			strcat(line, lstr);
			datez++;

			if (datez == 5)
				strcat(line, "\n"), datez = 0;
			else
				strcat(line, "\t\t");
		}

		tstr = "Multiple accounts on one IP: ";
		strcat(tstr, zplayerIP);
		Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, tstr, line, "Tutup", "");
	}
	return 1;
}

forward OWarnPlayer(adminid, const NameToWarn[], const warningReason[]);
public OWarnPlayer(adminid, const NameToWarn[], const warningReason[])
{
	if (cache_num_rows() < 1)
	{
		ShowTDN(adminid, NOTIFICATION_ERROR, sprintf("Akun '%s' tidak terdeteksi.", NameToWarn));
		return 1;
	}
	else
	{
		//format(sclstr, sizeof(sclstr), "%s(%d) [%s] used CMD '/owarn'\n
		//> issued a warning (offline) to %s [Reason: %s]", AccountData[adminid][pAdminname], adminid, AccountData[adminid][pUCP], NameToWarn, warningReason);
		//CallLocalFunction("StaffCommandLog", "is", adminid, sclstr);

		new RegID, warn, ucp[34];
		cache_get_value_index_int(0, 0, RegID);
		cache_get_value_index_int(0, 1, warn);
		cache_get_value_index(0, 2, ucp);
		
		if(warn >= MAX_PWARNS) return ShowTDN(adminid, NOTIFICATION_ERROR, "Pemain tersebut telah mencapai batas maksimum warn!");
		
		static string[512];
		mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_Warn`=%d WHERE `pID`=%d", warn + 1, RegID);
		mysql_pquery(g_SQL, string);

		foreach (new i : Player)
		{
			if (AccountData[i][pSpawned] && ToggleInfo[i][TogAdmCmd])
			{
				format(string, sizeof(string), "AdmCmd: %s has been given a warning (offline) by %s [Total: %d/20]", NameToWarn, AccountData[adminid][pAdminname], warn + 1);
				SendClientMessage(i, Y_LIGHTRED, string);
				format(string, sizeof(string), "Reason: %s", warningReason);
				SendClientMessage(i, Y_LIGHTRED, string);
			}
		}

		static year, month, day, keidwa[100], warsc[512];
		getdate(year, month, day);
		format(keidwa, sizeof(keidwa), "%02d/%02d/%d", day, month, year);

		mysql_format(g_SQL, warsc, sizeof(warsc), "INSERT INTO `player_warns` SET `Owner_ID` = %d, `Date` = '%e', `Date_Time` = '%e', `Issuer` = '%e', `Type` = 1, `Reason` = '%e'",
		RegID, keidwa, GetAdvTime(), AccountData[adminid][pAdminname], warningReason);
		mysql_pquery(g_SQL, warsc);

		if(warn+1 >= MAX_PWARNS)
		{
			static query[522];
			mysql_format(g_SQL, query, sizeof(query), "UPDATE `player_ucp` SET `Blocked`=1, `Block_Duration`=0, `Block_Reason`='20 Warns', `Block_AdminName`='Pahlawan Roleplay AntiCheat', `Block_IssuedDate`=CURRENT_TIMESTAMP() WHERE `UCP`='%e'", ucp);
			mysql_pquery(g_SQL, query);
		}
	}
	return 1;
}

forward OSetBankMoney(adminid, const NameToWarn[], jumlah);
public OSetBankMoney(adminid, const NameToWarn[], jumlah)
{
	static string[522];
	if (cache_num_rows() < 1)
		return ShowTDN(adminid, NOTIFICATION_ERROR, sprintf("Akun '%s' tidak terdeteksi.", NameToWarn));
	else
	{
		//format(sclstr, sizeof(sclstr), "%s(%d) [%s] used CMD '/owarn'\n
		//> issued a warning (offline) to %s [Reason: %s]", AccountData[adminid][pAdminname], adminid, AccountData[adminid][pUCP], NameToWarn, warningReason);
		//CallLocalFunction("StaffCommandLog", "is", adminid, sclstr);

		new RegID;
		cache_get_value_index_int(0, 0, RegID);

		mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_BankMoney`=%d WHERE `pID`=%d", jumlah, RegID);
		mysql_pquery(g_SQL, string);

    	mysql_format(g_SQL, string, sizeof(string), "INSERT INTO `admin_logs` SET `Prefix` = 'givebankmoney', `Admin` = '%e', `AdminUCP` = '%e', `UCPTarget` = '%e'", AccountData[adminid][pAdminname], AccountData[adminid][pUCP], NameToWarn);
		mysql_pquery(g_SQL, string);

		SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has set bank money (offline) for %s to $%s", AccountData[adminid][pAdminname], NameToWarn, FormatMoney(jumlah));
	}
	return 1;
}

forward OResetEconomy(adminid, const NameToWarn[]);
public OResetEconomy(adminid, const NameToWarn[])
{
	if (cache_num_rows() < 1)
		return ShowTDN(adminid, NOTIFICATION_ERROR, sprintf("Akun '%s' tidak terdeteksi.", NameToWarn));
	else
	{
		//format(sclstr, sizeof(sclstr), "%s(%d) [%s] used CMD '/owarn'\n
		//> issued a warning (offline) to %s [Reason: %s]", AccountData[adminid][pAdminname], adminid, AccountData[adminid][pUCP], NameToWarn, warningReason);
		//CallLocalFunction("StaffCommandLog", "is", adminid, sclstr);

		new RegID;
		cache_get_value_index_int(0, 0, RegID);
		SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has reset the economy (offline) for %s", AccountData[adminid][pAdminname], NameToWarn);
		
		static string[512];
		mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_Money`=0, `Char_BankMoney`=0, `Char_CasinoChip`=0 WHERE `pID`=%d", RegID);
		mysql_pquery(g_SQL, string);
	}
	return 1;
}

forward OResetWeapon(adminid, const NameToWarn[]);
public OResetWeapon(adminid, const NameToWarn[])
{
	if (cache_num_rows() < 1)
		return ShowTDN(adminid, NOTIFICATION_ERROR, sprintf("Akun '%s' tidak terdeteksi.", NameToWarn));
	else
	{
		//format(sclstr, sizeof(sclstr), "%s(%d) [%s] used CMD '/owarn'\n
		//> issued a warning (offline) to %s [Reason: %s]", AccountData[adminid][pAdminname], adminid, AccountData[adminid][pUCP], NameToWarn, warningReason);
		//CallLocalFunction("StaffCommandLog", "is", adminid, sclstr);

		new RegID;
		cache_get_value_index_int(0, 0, RegID);
		SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has reset weapons (offline) for %s", AccountData[adminid][pAdminname], NameToWarn);
		static string[512];
		mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `player_weapons` WHERE `Owner_ID` = %d", RegID);
		mysql_pquery(g_SQL, string);
	}
	return 1;
}

forward SendPlayerToJailAdmin(playerid);
public SendPlayerToJailAdmin(playerid)
{
	new randooc = Random(6);

	OJailData[playerid][jailCell] = randooc;
	switch (randooc)
	{
		case 0:
		{
			SetPlayerPositionEx(playerid, -734.6311, -2424.4250, -61.2422, 0.6164);
			SetPlayerInteriorEx(playerid, 0);
			SetPlayerVirtualWorldEx(playerid, 5);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
			AccountData[playerid][pInRusun] = -1;
			AccountData[playerid][pInHouse] = -1;
			AccountData[playerid][pInBiz] = -1;
			AccountData[playerid][pInDoor] = -1;
			AccountData[playerid][pInGudang] = -1;
			AccountData[playerid][pCuffed] = false;
			PlayerPlaySound(playerid, 1186, 0, 0, 0);
		}
		case 1:
		{
			SetPlayerPositionEx(playerid, -726.8369, -2424.9810, -61.2422, 359.3397);
			SetPlayerInteriorEx(playerid, 0);
			SetPlayerVirtualWorldEx(playerid, 5);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
			AccountData[playerid][pInRusun] = -1;
			AccountData[playerid][pInHouse] = -1;
			AccountData[playerid][pInBiz] = -1;
			AccountData[playerid][pInDoor] = -1;
			AccountData[playerid][pInGudang] = -1;
			AccountData[playerid][pCuffed] = false;
			PlayerPlaySound(playerid, 1186, 0, 0, 0);
		}
		case 2:
		{
			SetPlayerPositionEx(playerid, -718.2927, -2425.1013, -61.2422, 1.5563);
			SetPlayerInteriorEx(playerid, 0);
			SetPlayerVirtualWorldEx(playerid, 5);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
			AccountData[playerid][pInRusun] = -1;
			AccountData[playerid][pInHouse] = -1;
			AccountData[playerid][pInBiz] = -1;
			AccountData[playerid][pInDoor] = -1;
			AccountData[playerid][pInGudang] = -1;
			AccountData[playerid][pCuffed] = false;
			PlayerPlaySound(playerid, 1186, 0, 0, 0);
		}
		case 3:
		{
			SetPlayerPositionEx(playerid, -718.2546, -2405.9692, -61.2422, 178.5679);
			SetPlayerInteriorEx(playerid, 0);
			SetPlayerVirtualWorldEx(playerid, 5);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
			AccountData[playerid][pInRusun] = -1;
			AccountData[playerid][pInHouse] = -1;
			AccountData[playerid][pInBiz] = -1;
			AccountData[playerid][pInDoor] = -1;
			AccountData[playerid][pInGudang] = -1;
			AccountData[playerid][pCuffed] = false;
			PlayerPlaySound(playerid, 1186, 0, 0, 0);
		}
		case 4:
		{
			SetPlayerPositionEx(playerid, -726.8618, -2406.2324, -61.2422, 179.1947);
			SetPlayerInteriorEx(playerid, 0);
			SetPlayerVirtualWorldEx(playerid, 5);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
			AccountData[playerid][pInRusun] = -1;
			AccountData[playerid][pInHouse] = -1;
			AccountData[playerid][pInBiz] = -1;
			AccountData[playerid][pInDoor] = -1;
			AccountData[playerid][pInGudang] = -1;
			AccountData[playerid][pCuffed] = false;
			PlayerPlaySound(playerid, 1186, 0, 0, 0);
		}
		case 5:
		{
			SetPlayerPositionEx(playerid, -734.5328, -2406.0198, -61.2422, 178.2546);
			SetPlayerInteriorEx(playerid, 0);
			SetPlayerVirtualWorldEx(playerid, 5);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
			AccountData[playerid][pInRusun] = -1;
			AccountData[playerid][pInHouse] = -1;
			AccountData[playerid][pInBiz] = -1;
			AccountData[playerid][pInDoor] = -1;
			AccountData[playerid][pInGudang] = -1;
			AccountData[playerid][pCuffed] = false;
			PlayerPlaySound(playerid, 1186, 0, 0, 0);
		}
	}
	return 1;
}

forward CNAdmName(otherplayer, playerid, const nname[]);
public CNAdmName(otherplayer, playerid, const nname[])
{
	if(cache_num_rows() > 0)
	{
		return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Nama admin '%s' telah digunakan!", nname));
	}
	else
	{
		new query[512];
		format(query, sizeof(query), "UPDATE `player_characters` SET `Char_AdminName`='%e' WHERE `pID`=%d", nname, AccountData[otherplayer][pID]);
		mysql_pquery(g_SQL, query);
		strcopy(AccountData[otherplayer][pAdminname], nname);
		SendAdm(playerid, "You have set the admin name of %s(%d) to %s", AccountData[otherplayer][pName], otherplayer, nname);
	}
	return true;
}

forward ChangeVIPPlate(playerid, iterid, const template[]);
public ChangeVIPPlate(playerid, iterid, const template[])
{
	if(cache_num_rows() > 0)
	{
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Plat tersebut telah digunakan!");
	}
	else
	{
		static string[215];
		strcopy(PlayerVehicle[iterid][pVehPlate], template);
		SavePlayerVehicle(iterid);
		SetVehicleNumberPlate(PlayerVehicle[iterid][pVehPhysic], PlayerVehicle[iterid][pVehPlate]);

		mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_vehicles` SET `PVeh_Plate` = '%e' WHERE `id` = %d", template, PlayerVehicle[iterid][pVehID]);
		mysql_pquery(g_SQL, string);

		SetTimerEx("RespawnPV", 1500, false, "d", PlayerVehicle[iterid][pVehPhysic]);
		SendAdm(playerid, "You have changed the plate of %s (VID: %d) to %s.", GetVehicleModelName(GetVehicleModel(PlayerVehicle[iterid][pVehPhysic])), PlayerVehicle[iterid][pVehPhysic], template);
	}
	return 1;
}

forward ChangeVIPUCP(playerid, otherid, const newucp[]);
public ChangeVIPUCP(playerid, otherid, const newucp[])
{
	if(cache_num_rows() > 0)
	{
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Nama UCP sudah digunakan!");
	}
	else
	{
		static string[215];

		mysql_format(g_SQL, string, sizeof(string), "UPDATE `whitelists` SET `ucp` = '%e' WHERE `ucp` = '%e'", newucp, AccountData[otherid][pUCP]);
		mysql_pquery(g_SQL, string);

		mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_ucp` SET `UCP` = '%e' WHERE `UCP` = '%e'", newucp, AccountData[otherid][pUCP]);
		mysql_pquery(g_SQL, string);

		mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_UCP` = '%e', `Char_Adminname` = '%e' WHERE `Char_UCP` = '%e'", newucp, newucp, AccountData[otherid][pUCP]);
		mysql_pquery(g_SQL, string);

		strcopy(AccountData[otherid][pUCP], newucp);
		strcopy(AccountData[otherid][pAdminname], newucp);

		format(string, sizeof(string), "AdmCmd: %s has changed your UCP name to %s", AccountData[playerid][pAdminname], newucp);
		SendClientMessage(otherid, Y_LIGHTRED, string);
		SendAdm(playerid, "You have changed the UCP name of %s(%d) to %s.", AccountData[otherid][pName], otherid, newucp);
		return true;
	}
}

forward ChangeVIPPHNumber(playerid, otherid, const newnumb[]);
public ChangeVIPPHNumber(playerid, otherid, const newnumb[])
{
	if (cache_num_rows() > 0)
	{
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Nomor HP sudah digunakan!");
	}
	else
	{
		static string[215];

		mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_phones` SET `phoneNumber` = '%e' WHERE `phoneOwner` = %d", newnumb, AccountData[otherid][pID]);
		mysql_pquery(g_SQL, string);

		mysql_format(g_SQL, string, sizeof(string), "UPDATE `phone_contacts` SET `contactNumber` = '%e' WHERE `contactNumber` = '%e'", newnumb, PlayerPhoneData[otherid][phoneNumber]);
		mysql_pquery(g_SQL, string);

		foreach(new i : Player)
		{
			for(new cid; cid < MAX_CONTACTS; ++cid)
			{
				if(ContactData[i][cid][contactExists]) // If the contact is stored in targetid
				{
					if(!strcmp(ContactData[i][cid][contactNumber], PlayerPhoneData[otherid][phoneNumber], false)) // If the number being checked is in the contacts of targetid
					{
						strcopy(ContactData[i][cid][contactNumber], newnumb); // Then get the stored contact name
					}
				}
			}
		}

		strcopy(PlayerPhoneData[otherid][phoneNumber], newnumb);

		format(string, sizeof(string), "AdmCmd: %s has changed the phone number of your character to %s", AccountData[playerid][pAdminname], newnumb);
		SendClientMessage(otherid, Y_LIGHTRED, string);
		SendAdm(playerid, "You have changed the phone number of %s(%d) to %s.", AccountData[otherid][pName], otherid, newnumb);
	}
    return 1;
}

forward ChangeVIPBankNumber(playerid, otherid, newbrek);
public ChangeVIPBankNumber(playerid, otherid, newbrek)
{
	if (cache_num_rows() > 0)
	{
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Nomor rekening tersebut sudah digunakan!");
	}
	else
	{
		static string[215];

		mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_BankNumber` = %d WHERE `pID` = %d", newbrek, AccountData[otherid][pID]);
		mysql_pquery(g_SQL, string);

		AccountData[otherid][pBankNumber] = newbrek;

		format(string, sizeof(string), "AdmCmd: %s has changed the bank account number of your character to %d", AccountData[playerid][pAdminname], newbrek);
		SendClientMessage(otherid, Y_LIGHTRED, string);
		SendAdm(playerid, "You have changed the bank account number of %s(%d) to %d.", AccountData[otherid][pName], otherid, newbrek);
	}
    return 1;
}

forward OSendPlayerToJailAdmin(adminid, const NameToJail[], const ojReason[], ojTime);
public OSendPlayerToJailAdmin(adminid, const NameToJail[], const ojReason[], ojTime)
{
	new rows = cache_num_rows();
	if (rows > 0)
	{
		//format(sclstr, sizeof(sclstr), "%s(%d) [%s] used CMD '/ojail'\n
		//> jailed (offline) %s for %d minutes [Reason: %s]", AccountData[adminid][pAdminname], adminid, AccountData[adminid][pUCP], NameToJail, ojTime, ojReason);
		//CallLocalFunction("StaffCommandLog", "is", adminid, sclstr);

		new regID, JailMinutes = ojTime * 60;
		cache_get_value_name_int(0, "pID", regID);

		static string[512];
		foreach(new i : Player) if (AccountData[i][pSpawned] && ToggleInfo[i][TogAdmCmd])
		{
			format(string, sizeof(string), "AdmCmd: %s has been OOC jailed (offline) by %s for %d minutes.", NameToJail, AccountData[adminid][pAdminname], ojTime);
			SendClientMessage(i, Y_LIGHTRED, string);
			format(string, sizeof(string), "Reason: %s", ojReason);
			SendClientMessage(i, Y_LIGHTRED, string);
		}

		mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_Jailed`=1, `Char_JailCell`=-1, `Char_JailAdmin`='%e', `Char_JailTime`=%d, `Char_JailDur`=%d, `Char_JailReason`='%e', `Char_JailFine`=0 WHERE `pID`=%d", AccountData[adminid][pAdminname], JailMinutes, ojTime, ojReason, regID);
		mysql_pquery(g_SQL, string);

		static year, month, day, keidwa[100];
		getdate(year, month, day);
		format(keidwa, sizeof(keidwa), "%02d/%02d/%d", day, month, year);
		mysql_format(g_SQL, string, sizeof(string), "INSERT INTO `player_warns` SET `Owner_ID` = %d, `Date` = '%e', `Date_Time` = '%e', `Issuer` = '%e', `Type` = 2, `Reason` = '%e'",
		regID, keidwa, GetAdvTime(), AccountData[adminid][pAdminname], ojReason);
		mysql_pquery(g_SQL, string);
	}
	else
	{
		return ShowTDN(adminid, NOTIFICATION_ERROR, sprintf("Akun %s tidak dapat ditemukan!", NameToJail));
	}
	return 1;
}

forward OnUnbanQueryData(adminid, const BannedName[]);
public OnUnbanQueryData(adminid, const BannedName[])
{
	if (cache_num_rows() > 0)
	{
		new banIP[16];
		
		static string[144];
		cache_get_value_name(0, "ip", banIP);
		mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `player_bans` WHERE `ip` = '%e'", banIP);
		mysql_pquery(g_SQL, string);

		//format(sclstr, sizeof(sclstr), "%s(%d) [%s] used CMD '/unban'\n
		//> lifted the ban status of %s", AccountData[adminid][pAdminname], adminid, AccountData[adminid][pUCP], BannedName);
		//CallLocalFunction("StaffCommandLog", "is", adminid, sclstr);

		foreach(new i : Player) if (AccountData[i][pSpawned])
		{
			format(string, sizeof(string), "AdmCmd: %s has lifted the banned status of %s from the server.", AccountData[adminid][pAdminname], BannedName);
			SendClientMessage(i, Y_LIGHTRED, string);
		}
	}
	else
	{
		ShowTDN(adminid, NOTIFICATION_ERROR, sprintf("Akun %s tidak dapat ditemukan!", BannedName));
	}
	return 1;
}

forward OnBlockingUCP(adminid, const BlockedUCP[], totalblockduration, hariduration, const reasonblocking[]);
public OnBlockingUCP(adminid, const BlockedUCP[], totalblockduration, hariduration, const reasonblocking[])
{
	if (cache_num_rows() > 0)
	{
		static string[522];
		mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_ucp` SET `Blocked`=1, `Block_Duration`='%d', `Block_Reason`='%e', `Block_AdminName`='%e', `Block_IssuedDate`=CURRENT_TIMESTAMP() WHERE `UCP`='%e'", totalblockduration, reasonblocking, AccountData[adminid][pAdminname], BlockedUCP);
		mysql_pquery(g_SQL, string);

		if (hariduration != 0)
		{
			//format(sclstr, sizeof(sclstr), "%s(%d) [%s] used CMD '/blockucp'\n\
			//> blocked UCP %s for %d days [Reason: %s]", AccountData[adminid][pAdminname], adminid, AccountData[adminid][pUCP], BlockedUCP, hariduration, reasonblocking);
			//CallLocalFunction("StaffCommandLog", "is", adminid, sclstr);

			foreach(new i : Player) if (AccountData[i][pSpawned] && ToggleInfo[i][TogAdmCmd])
			{
				format(string, sizeof(string), "AdmCmd: %s has blocked UCP %s for %d days.", AccountData[adminid][pAdminname], BlockedUCP, hariduration);
				SendClientMessage(i, Y_LIGHTRED, string);
				format(string, sizeof(string), "Reason: %s", reasonblocking);
				SendClientMessage(i, Y_LIGHTRED, string);
			}
		}
		else
		{
			//format(sclstr, sizeof(sclstr), "%s(%d) [%s] used CMD '/blockucp'\n\
			//> permanently blocked UCP %s [Reason: %s]", AccountData[adminid][pAdminname], adminid, AccountData[adminid][pUCP], BlockedUCP, reasonblocking);
			//CallLocalFunction("StaffCommandLog", "is", adminid, sclstr);

			foreach(new i : Player) if (AccountData[i][pSpawned] && ToggleInfo[i][TogAdmCmd])
			{
				format(string, sizeof(string), "AdmCmd: %s has permanently blocked UCP %s", AccountData[adminid][pAdminname], BlockedUCP);
				SendClientMessage(i, Y_LIGHTRED, string);
				format(string, sizeof(string), "Reason: %s", reasonblocking);
				SendClientMessage(i, Y_LIGHTRED, string);
			}
		}
	}
	else
	{
		ShowTDN(adminid, NOTIFICATION_ERROR, sprintf("Akun UCP '%s' tidak dapat ditemukan!", BlockedUCP));
	}
	return 1;
}

forward OnUnblockUCP(adminid, const BlockedUCP[]);
public OnUnblockUCP(adminid, const BlockedUCP[])
{
	if (cache_num_rows() > 0)
	{
		new bool:isblocked;
		
		static string[522];

		cache_get_value_name_int(0, "Blocked", isblocked);

		if (!isblocked)
		{
			ShowTDN(adminid, NOTIFICATION_ERROR, sprintf("Akun UCP '%s' tidak sedang diblokir!", BlockedUCP));
			return 1;
		}

		mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_ucp` SET `Blocked`=0, `Block_Duration`=0, `Block_Reason`='', `Block_AdminName`='',  `Block_IssuedDate`='' WHERE `UCP`='%e'", BlockedUCP);
		mysql_pquery(g_SQL, string);

		foreach(new i : Player) if (AccountData[i][pSpawned])
		{
			format(string, sizeof(string), "AdmCmd: %s has unblocked UCP %s from the server.", AccountData[adminid][pAdminname], BlockedUCP);
			SendClientMessage(i, Y_LIGHTRED, string);
		}

		mysql_format(g_SQL, string, sizeof(string), "INSERT INTO `admin_logs` SET `Prefix` = 'unblockucp', `Admin` = '%e', `AdminUCP` = '%e', `UCPTarget` = '%e'", AccountData[adminid][pAdminname], AccountData[adminid][pUCP], BlockedUCP);
		mysql_pquery(g_SQL, string);

		//format(sclstr, sizeof(sclstr), "%s(%d) [%s] used CMD '/unblockucp'\n
		//> lifted UCP blocking %s", AccountData[adminid][pAdminname], adminid, AccountData[adminid][pUCP], BlockedUCP);
		//CallLocalFunction("StaffCommandLog", "is", adminid, sclstr);
	}
	else
	{
		ShowTDN(adminid, NOTIFICATION_ERROR, sprintf("Akun UCP '%s' tidak dapat ditemukan!", BlockedUCP));
	}
	return 1;
}

BanPlayerMSG(playerid, adminid, const reason[], bool:serverBan = false)
{
	static hours, minutes, seconds, years, months, days, string[144];
    for (new i = 0; i < 7; i++) SendClientMessage(playerid, -1, " ");
    gettime(hours, minutes, seconds);
	getdate(years, months, days);
	SendClientMessage(playerid, Y_RED, "You have been banned from the server!");
	if (!serverBan)
 	{
		format(string, sizeof(string), "Admin On Duty: %s(%i)", AccountData[adminid][pAdminname], adminid);
		SendClientMessage(playerid, X11_WHITE, string);
	}
	else
	{
		SendClientMessage(playerid, X11_GREY, "Admin On Duty: Server Ban");
	}
	format(string, sizeof(string), "Reason: %s", reason);
	SendClientMessage(playerid, X11_WHITE, string);
	format(string, sizeof(string), "The time is %02d:%02d (%02d/%02d/%d)", hours, minutes, months, days, years);
	SendClientMessage(playerid, X11_WHITE, string);
	SendClientMessage(playerid, X11_WHITE, "Go to bit.ly/pahlawan-rp to request an Unban-Req, include this screenshot.");
	GameTextForPlayer(playerid, "~r~~h~Holiday Has Arrived!", 5000, 5);
}

forward OnOBanQueryData(adminid, const NameToBan[], const banReason[], banTime);
public OnOBanQueryData(adminid, const NameToBan[], const banReason[], banTime)
{
	if (!cache_num_rows())
	{
		ShowTDN(adminid, NOTIFICATION_ERROR, sprintf("Akun UCP '%s' tidak dapat ditemukan!", NameToBan));
		return 1;
	}
	else
	{
		static datez, PlayerIP[16], regID, string[512];
		cache_get_value_name_int(0, "pID", regID);
		cache_get_value_name(0, "Char_IP", PlayerIP);
		if (banTime != 0)
		{
			datez = gettime() + (banTime * 86400);
			foreach (new i : Player) if (AccountData[i][pSpawned] && ToggleInfo[i][TogAdmCmd])
			{
				format(string, sizeof(string), "AdmCmd: %s has set a banned status (offline) for %s for %d days.", AccountData[adminid][pAdminname], NameToBan, banTime);
				SendClientMessage(i, Y_LIGHTRED, string);
				format(string, sizeof(string), "Reason: %s", banReason);
				SendClientMessage(i, Y_LIGHTRED, string);
			}

			//format(sclstr, sizeof(sclstr), "%s(%d) [%s] used CMD '/oban'\n\
			//> temporarily banned (offline) %s for %d days [Reason: %s]", AccountData[adminid][pAdminname], adminid, AccountData[adminid][pUCP], NameToBan, banTime, banReason);
			//CallLocalFunction("StaffCommandLog", "is", adminid, sclstr);
		}
		else
		{
			foreach (new i : Player) if (AccountData[i][pSpawned] && ToggleInfo[i][TogAdmCmd])
			{
				format(string, sizeof(string), "AdmCmd: %s has permanently banned (offline) %s.", AccountData[adminid][pAdminname], NameToBan);
				SendClientMessage(i, Y_LIGHTRED, string);
				format(string, sizeof(string), "Reason: %s", banReason);
				SendClientMessage(i, Y_LIGHTRED, string);
			}

			//format(sclstr, sizeof(sclstr), "%s(%d) [%s] used CMD '/oban'\n\
			//> permanently banned (offline) %s [Reason: %s]", AccountData[adminid][pAdminname], adminid, AccountData[adminid][pUCP], NameToBan, banReason);
			//CallLocalFunction("StaffCommandLog", "is", adminid, sclstr);
		}
		mysql_format(g_SQL, string, sizeof(string), "INSERT INTO `player_bans`(`name`, `ip`, `admin`, `reason`, `ban_date`, `ban_expire`) VALUES ('%e', '%e', '%e', '%e', UNIX_TIMESTAMP(), %d)", NameToBan, PlayerIP, AccountData[adminid][pAdminname], banReason, datez);
		mysql_pquery(g_SQL, string);

		static year, month, day, keidwa[100];
		getdate(year, month, day);
		format(keidwa, sizeof(keidwa), "%02d/%02d/%d", day, month, year);
		mysql_format(g_SQL, string, sizeof(string), "INSERT INTO `player_warns` SET `Owner_ID` = %d, `Date` = '%e', `Date_Time` = '%e', `Issuer` = '%e', `Type` = 3, `Reason` = '%e'",
		regID, keidwa, GetAdvTime(), AccountData[adminid][pAdminname], banReason);
		mysql_pquery(g_SQL, string);
	}
	return true;
}

forward SetName(playerid, const nname[]);
public SetName(playerid, const nname[])
{
	if (!cache_num_rows())
	{
		static oldname[25], newname[25], string[248], otherplayer;
		otherplayer = AccountData[playerid][pTempSQLFactMemberID];

		GetPlayerName(otherplayer, oldname, sizeof(oldname));

		mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_Name`='%e' WHERE `pID`=%d", nname, AccountData[otherplayer][pID]);
		mysql_pquery(g_SQL, string);

		format(string, sizeof(string), "AdmCmd: %s has changed your nickname to (%s)", AccountData[playerid][pAdminname], nname);
		SendClientMessage(otherplayer, Y_LIGHTRED, string);
		SendClientMessage(otherplayer, Y_LIGHTRED, "NOTE: Always log in using your UCP name, not your character nickname!");
		SendAdm(playerid, "You have changed the nickname %s(%d) to %s.", oldname, otherplayer, nname);

		//format(sclstr, sizeof(sclstr), "%s(%d) [%s] used CMD '/setname'\n\
		//> changed nickname %s(%d) [%s] to %s", AccountData[playerid][pAdminname], playerid, AccountData[playerid][pUCP], oldname, otherplayer, AccountData[otherplayer][pUCP], nname);
		//CallLocalFunction("StaffCommandLog", "is", playerid, sclstr);

		SetPlayerName(otherplayer, nname);
		GetPlayerName(otherplayer, newname, sizeof(newname));
		strcopy(AccountData[otherplayer][pName], newname);
		
		mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_toys` SET Owner='%e' WHERE `Owner`='%e'", newname, oldname);
		mysql_pquery(g_SQL, string);

		foreach (new rsid : Rusuns)
		{
			if (RusunData[rsid][rusunOwnerID] == AccountData[otherplayer][pID])
			{
				mysql_format(g_SQL, string, sizeof(string), "UPDATE `rusun` SET `OwnerName`='%e' WHERE `OwnerID`=%d", GetPlayerRoleplayName(otherplayer), AccountData[otherplayer][pID]);
				mysql_pquery(g_SQL, string);
				strcopy(RusunData[rsid][rusunOwnerName], AccountData[playerid][pName]);
				Rusun_Refresh(rsid);
			}
		}

		foreach (new hid : Houses)
		{
			if (HouseData[hid][hOwnerID] == AccountData[otherplayer][pID])
			{
				mysql_format(g_SQL, string, sizeof(string), "UPDATE `houses` SET `OwnerName`='%e' WHERE `OwnerID`=%d", GetPlayerRoleplayName(otherplayer), AccountData[otherplayer][pID]);
				mysql_pquery(g_SQL, string);
				strcopy(HouseData[hid][hOwnerName], AccountData[otherplayer][pName]);
				House_Refresh(hid);
			}
		}

		foreach (new bid : Bizes)
		{
			if(BizData[bid][bizOwnerID] == AccountData[otherplayer][pID])
			{
				mysql_format(g_SQL, string, sizeof(string), "UPDATE `biz` SET `OwnerName`='%e' WHERE `OwnerID`=%d", GetPlayerRoleplayName(otherplayer), AccountData[otherplayer][pID]);
				mysql_pquery(g_SQL, string);
				strcopy(BizData[bid][bizOwnerName], AccountData[otherplayer][pName]);
				Biz_Refresh(bid);
			}
		}

		mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_phones` SET `phoneOwnerName`='%e' WHERE `phoneOwner`=%d", GetPlayerRoleplayName(otherplayer), AccountData[otherplayer][pID]);
		mysql_pquery(g_SQL, string);

		new originstring[3528+1];
		for(new x = 0; x < sizeof(_g_originName);x++)
		{
			format(originstring, sizeof(originstring), "%s%s\n", originstring, _g_originName[x]);
		}
		Dialog_Show(playerid, "AdmSetNameOrigin", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Negara Kelahiran", originstring, "Pilih", "");
	}
	else
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Nama telah digunakan!");
	}
	return 1;
}

forward ChangeName(playerid, const nname[]);
public ChangeName(playerid, const nname[])
{
	if(!cache_num_rows())
	{
		new oldname[25], newname[25];
		GetPlayerName(playerid, oldname, sizeof(oldname));

		static string[144];
		mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_Name`='%e' WHERE `pID`=%d", nname, AccountData[playerid][pID]);
		mysql_pquery(g_SQL, string);

		format(string, sizeof(string), "(CMD) "WHITE"Anda berhasil mengganti nickname karakter menjadi "YELLOW"%s", nname);
		SendClientMessage(playerid, Y_SERVER, string);
		SendClientMessage(playerid, X11_YELLOW, "NOTE: Anda tidak perlu untuk relog, namun bila berkenan silakan saja!");
		SendStaffMessage(Y_SERVER, "(CMD) "WHITE"Player "YELLOW"%s(%d) "WHITE"telah menggunakan kartu CN dan mengganti namanya menjadi "YELLOW"%s(%d).", oldname, playerid, nname, playerid);

		SetPlayerName(playerid, nname);
		GetPlayerName(playerid, newname, sizeof(newname));
		strcopy(AccountData[playerid][pName], newname);

		Inventory_Remove(playerid, "Changename Card");

		mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_toys` SET Owner='%e' WHERE `Owner`='%e'", newname, oldname);
		mysql_pquery(g_SQL, string);

		foreach (new rsid : Rusuns)
		{
			if (RusunData[rsid][rusunOwnerID] == AccountData[playerid][pID])
			{
				mysql_format(g_SQL, string, sizeof(string), "UPDATE `rusun` SET `OwnerName`='%e' WHERE `OwnerID`=%d", GetPlayerRoleplayName(playerid), AccountData[playerid][pID]);
				mysql_pquery(g_SQL, string);
				strcopy(RusunData[rsid][rusunOwnerName], AccountData[playerid][pName]);
				Rusun_Refresh(rsid);
			}
		}

		foreach (new hid : Houses)
		{
			if (HouseData[hid][hOwnerID] == AccountData[playerid][pID])
			{
				mysql_format(g_SQL, string, sizeof(string), "UPDATE `houses` SET `OwnerName`='%e' WHERE `OwnerID`=%d", GetPlayerRoleplayName(playerid), AccountData[playerid][pID]);
				mysql_pquery(g_SQL, string);
				strcopy(HouseData[hid][hOwnerName], AccountData[playerid][pName]);
				House_Refresh(hid);
			}
		}

		foreach (new bid : Bizes)
		{
			if(BizData[bid][bizOwnerID] == AccountData[playerid][pID])
			{
				mysql_format(g_SQL, string, sizeof(string), "UPDATE `biz` SET `OwnerName`='%e' WHERE `OwnerID`=%d", GetPlayerRoleplayName(playerid), AccountData[playerid][pID]);
				mysql_pquery(g_SQL, string);
				strcopy(BizData[bid][bizOwnerName], AccountData[playerid][pName]);
				Biz_Refresh(bid);
			}
		}

		mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_phones` SET `phoneOwnerName`='%e' WHERE `phoneOwner`=%d", GetPlayerRoleplayName(playerid), AccountData[playerid][pID]);
		mysql_pquery(g_SQL, string);

		static originstring[3528+1];
		for(new x = 0; x < sizeof(_g_originName);x++)
		{
			format(originstring, sizeof(originstring), "%s%s\n", originstring, _g_originName[x]);
		}
		Dialog_Show(playerid, "ChangeNameOrigin", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Negara Kelahiran", originstring, "Pilih", "");
	}
	else
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Nama telah digunakan!");
	}
	return 1;
}

forward LoadStats(playerid, const PlayersName[]);
public LoadStats(playerid, const PlayersName[])
{
	if(!cache_num_rows())
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("UCP '%s' tidak terdeteksi!", PlayersName));
		return 1;
	}
	else
	{
		//format(sclstr, sizeof(sclstr), "%s(%d) [%s] menggunakan CMD '/ostats'\n
		//> melihat stats akun (offline) %s", AccountData[playerid][pAdminname], playerid, AccountData[playerid][pUCP], PlayersName);
		//CallLocalFunction("StaffCommandLog", "is", playerid, sclstr);
		
		new rnnrt[128], opID, Char_UCP[22], Char_Name[25], Char_Birthday[50], Char_Origin[32], Char_Gender, Char_BodyHeight,
			Char_BodyWeight, Char_Job, Char_Faction, Char_FactionRank, Char_Family, Char_FamilyRank, Char_Money, Char_BankMoney, Char_CasinoChip, Char_DirtyMoney, Float:Char_Health, Float:Char_Armor, Char_Hunger, Char_Thirst, Char_Stress, Char_Warn, Char_Level, 
			Char_Hours, Char_Minutes, Char_Seconds, Char_Admin, Char_Steward, Char_StewTime, Char_VIP, Char_VIPTime,
			Char_Skin, Char_WID, Char_IntID, Char_InHouse, Char_InDoor, Char_InRusun, Char_LastLogin[50], Char_RegisterDate[50];

		cache_get_value_index_int(0, 0, opID);
		cache_get_value_index(0, 1, Char_UCP);
		cache_get_value_index(0, 2, Char_Name);
		cache_get_value_index(0, 3, Char_Birthday);
		cache_get_value_index(0, 4, Char_Origin);
		cache_get_value_index_int(0, 5, Char_Gender);
		cache_get_value_index_int(0, 6, Char_BodyHeight);
		cache_get_value_index_int(0, 7, Char_BodyWeight);
		cache_get_value_index_int(0, 8, Char_Job);
		cache_get_value_index_int(0, 9, Char_Faction);
		cache_get_value_index_int(0, 10, Char_FactionRank);
		cache_get_value_index_int(0, 11, Char_Family);
		cache_get_value_index_int(0, 12, Char_FamilyRank);
		cache_get_value_index_int(0, 13, Char_Money);
		cache_get_value_index_int(0, 14, Char_BankMoney);
		cache_get_value_index_int(0, 15, Char_CasinoChip);
		cache_get_value_index_int(0, 16, Char_DirtyMoney);
		cache_get_value_index_float(0, 17, Char_Health);
		cache_get_value_index_float(0, 18, Char_Armor);
		cache_get_value_index_int(0, 19, Char_Hunger);
		cache_get_value_index_int(0, 20, Char_Thirst);
		cache_get_value_index_int(0, 21, Char_Stress);
		cache_get_value_index_int(0, 22, Char_Warn);
		cache_get_value_index_int(0, 23, Char_Level);
		cache_get_value_index_int(0, 24, Char_Hours);
		cache_get_value_index_int(0, 25, Char_Minutes);
		cache_get_value_index_int(0, 26, Char_Seconds);
		cache_get_value_index_int(0, 27, Char_Admin);
		cache_get_value_index_int(0, 28, Char_Steward);
		cache_get_value_index_int(0, 29, Char_StewTime);
		cache_get_value_index_int(0, 30, Char_VIP);
		cache_get_value_index_int(0, 31, Char_VIPTime);
		cache_get_value_index_int(0, 32, Char_Skin);
		cache_get_value_index_int(0, 33, Char_WID);
		cache_get_value_index_int(0, 34, Char_IntID);
		cache_get_value_index_int(0, 35, Char_InHouse);
		cache_get_value_index_int(0, 36, Char_InDoor);
		cache_get_value_index_int(0, 37, Char_InRusun);
		cache_get_value_index(0, 38, Char_LastLogin);
		cache_get_value_index(0, 39, Char_RegisterDate);
		
		static spstr[1655];

		static const FacName[13][] = 
		{
			"Warga Pahlawan Roleplay",
			"Kepolisian",
			"Paramedis",
			"Putri Deli Beach Club",
			"Pemerintah",
			"Bennys Automotive",
			"Uber",
			"Pinky Tiger Club",
			"Pewarta",
			"Automax Workshop",
			"Handover Motorworks",
			"Sri Mersing Resto",
			"Texas Chicken"
		};

		static const CopRank[17][] = 
		{
			"N/A",

			"BHARADA", //1
			"BHARATU", //2
			"BRIPDA", //3
			"BRIPTU", //4
			"BRIGPOL", //5
			"BRIPKA", //6
			"AIPDA", //7
			"AIPTU", //8
			"IPDA", //9
			"IPTU", //10
			"AKP", //11
			"KOMPOL", //12
			"AKBP", //13
			"KOMBESPOL", //14
			"BRIGJENPOL", //15
			"IRJENPOL" //16
		};

		static const PemerintahRank[8][] = 
		{
			"N/A",
			"Honorer",
			"Staff Junior",
			"Staff Senior",
			"Kepala Dinas",
			"Sekretaris",
			"W. Gubernur",
			"Gubernur"
		};

		static const PutrideliRank[11][] = 
		{
			"N/A",
			"Magang",
			"Junior",
			"Pelayan",
			"Barista",
			"Senior",
			"Marketing",
			"Supervisor",
			"Manager",
			"Chief Officer",
			"Chief Executive"
		};

		static const LSFDRank[9][] = 
		{
			"N/A",
			"PKL", //1
			"Perawat", //2
			"Dokter", //3
			"Dokter Spesialis", //4
			"Profesor", //5
			"WAKADIR", //6
			"SEKBEN", //7
			"Direktur" //8
		};

		static const BennysRank[7][] = 
		{
			"N/A",

			"PKL", // 1
			"Amatir", //2
			"Ahli", //3
			"Wakil Manager", //4
			"Manager",
			"Boss Bennys"
		};

		static const UberRank[6][] = 
		{
			"N/A",

			"Driver Baru",
			"Junior",
			"Senior",
			"Ast. Boss Uber",
			"Boss Uber"
		};


		static const DBRank[11][] = 
		{
			"N/A",
			"Magang",
			"Junior",
			"Pelayan",
			"Barista",
			"Senior",
			"Marketing",
			"Supervisor",
			"Manager",
			"Chief Officer",
			"Chief Executive"
		};

		static const FoxRank[7][] = 
		{
			"N/A",
			"Jurnalis",
			"Reporter",
			"Editor",
			"Senior",
			"Chief Officer",
			"Chief Executive"
		};
		static const AutomaxRank[7][] = 
		{
			"N/A",

			"PKL", // 1
			"Amatir", //2
			"Ahli", //3
			"Wakil Manager", //4
			"Manager",
			"Boss Automax"
		};
		static const HandoverRank[7][] = 
		{
			"N/A",

			"PKL", // 1
			"Amatir", //2
			"Ahli", //3
			"Wakil Manager", //4
			"Manager",
			"Boss Handover"
		};

		static const PARVRank[11][] = 
		{
			"N/A",
			"Magang",
			"Junior",
			"Pelayan",
			"Barista",
			"Senior",
			"Marketing",
			"Supervisor",
			"Manager",
			"Chief Officer",
			"Chief Executive"
		};

		static const TexasRank[11][] = 
		{
			"N/A",
			"Magang",
			"Satpam",
			"Junior",
			"Senior",
			"Staff",
			"Marketing",
			"Supervisor",
			"Manager",
			"Chief Officer",
			"Chief Executive"
		};

		switch(Char_Faction)
		{
			case FACTION_NONE: //None
			{
				format(rnnrt, sizeof(rnnrt), "N/A");
			}
			case FACTION_LSPD: //polda 
			{
				format(rnnrt, sizeof(rnnrt), CopRank[Char_FactionRank]);
			}
			case FACTION_LSFD: //IDA 
			{
				format(rnnrt, sizeof(rnnrt), LSFDRank[Char_FactionRank]);
			}
			case FACTION_PUTRIDELI: //IDA 
			{
				format(rnnrt, sizeof(rnnrt), PutrideliRank[Char_FactionRank]);
			}
			case FACTION_SAGOV: //pemerintah
			{
				format(rnnrt, sizeof(rnnrt), PemerintahRank[Char_FactionRank]);
			}
			case FACTION_BENNYS: //bengkel
			{
				format(rnnrt, sizeof(rnnrt), BennysRank[Char_FactionRank]);
			}
			case FACTION_UBER: //uber
			{
				format(rnnrt, sizeof(rnnrt), UberRank[Char_FactionRank]);
			}
			case FACTION_DINARBUCKS: //dinarbucks
			{
				format(rnnrt, sizeof(rnnrt), DBRank[Char_FactionRank]);
			}
			case FACTION_FOX11: //dinarbucks
			{
				format(rnnrt, sizeof(rnnrt), FoxRank[Char_FactionRank]);
			}
			case FACTION_AUTOMAX: //bengkel
			{
				format(rnnrt, sizeof(rnnrt), AutomaxRank[Char_FactionRank]);
			}
			case FACTION_HANDOVER: //bengkel
			{
				format(rnnrt, sizeof(rnnrt), HandoverRank[Char_FactionRank]);
			}
			case FACTION_SRIMERSING: //bengkel
			{
				format(rnnrt, sizeof(rnnrt), PARVRank[Char_FactionRank]);
			}
			case FACTION_TEXAS: //texas
			{
				format(rnnrt, sizeof(rnnrt), TexasRank[Char_FactionRank]);
			}
		}

		static const FamilyRank[7][] = 
		{
			"N/A", //0

			"Prospek", //1
			"Junior", //2
			"Senior", //3
			"Penasihat", //4
			"Wakil", //5
			"Ketua" //6
		};

		static const PlayerLevel[1001][] = 
		{
			"Unknown",
			"Warga Baru",
			"Starty I",
			"Starty II",
			"Midly I",
			"Midly II",
			"Nowee I",
			"Nowee II",
			"Naudie I",
			"Naudie II",
			"Goodie I",
			"Goodie II",
			"Calmy I",
			"Calmy II",
			"{393435}Rainy I",
			"{393435}Rainy II",
			"{393435}Weedy I",
			"{393435}Weedy II",
			"{393435}Masty I",
			"{393435}Masty II",
			"{393435}Xeny I",
			"{393435}Xeny II",
			"{393435}Loyee I",
			"{393435}Loyee II",
			"{393435}Wasy I",
			"{393435}Wasy II",
			"{393435}Maestry I",
			"{393435}Maestry II",
			"{393435}Cloudie I",
			"{393435}Cloudie II",
			"{393435}Middie I",
			"{393435}Middie II",
			"{1eff00}Lancy I",
			"{1eff00}Lancy II",
			"{1eff00}Soddy I",
			"{1eff00}Soddy II",
			"{1eff00}Epsy I",
			"{1eff00}Epsy II",
			"{1eff00}Flirdie I",
			"{1eff00}Flirdie II",
			"{1eff00}Geny I",
			"{1eff00}Geny II",
			"{1eff00}Byutee I",
			"{1eff00}Byutee II",
			"{1eff00}Hexy I",
			"{1eff00}Hexy II",
			"{1eff00}Fillie I",
			"{1eff00}Fillie II",
			"{1eff00}Catty I",
			"{1eff00}Catty II",
			"{0070dd}Legendary I",  //50
			"{0070dd}Legendary II",
			"{0070dd}Aclimary I",
			"{0070dd}Aclimary II",
			"{0070dd}Neucly I",
			"{0070dd}Neucly II",
			"{0070dd}Jivy I",
			"{0070dd}Jivy II",
			"{0070dd}Stary I",
			"{0070dd}Stary II",
			"{0070dd}Jebie I",
			"{0070dd}Jebie II",
			"{0070dd}Noxie I",
			"{0070dd}Noxie II",
			"{0070dd}Vexy I",
			"{0070dd}Vexy II",
			"{0070dd}Kuxie I",
			"{0070dd}Kuxie II",
			"{0070dd}Perie I",
			"{0070dd}Perie II",
			"{A335EE}Azimuth I", //70
			"{A335EE}Azimuth II",
			"{A335EE}Axedus I",
			"{A335EE}Axedus II",
			"{A335EE}Morius I",
			"{A335EE}Morius II",
			"{A335EE}Versus I",
			"{A335EE}Versus II",
			"{A335EE}Nominus I",
			"{A335EE}Nominus II",
			"{A335EE}Albus I",
			"{A335EE}Albus II",
			"{A335EE}Oculus I",
			"{A335EE}Oculus II",
			"{A335EE}Zuxius I",
			"{A335EE}Zuxius II",
			"{A335EE}Luxious I",
			"{A335EE}Luxious II",
			"{A335EE}Aleous I",
			"{A335EE}Aleous II",
			"{FF8000}Maxima I", //90
			"{FF8000}Maxima II",
			"{FF8000}Livus I",
			"{FF8000}Livus II",
			"{FF8000}Galaxus I",
			"{FF8000}Galaxus II",
			"{FF8000}Olus I",
			"{FF8000}Olus II",
			"{FF8000}Omnipous I",
			"{FF8000}Omnipous II",
			"{FF8000}Omnipous III",
			"{FF8000}Omnipous IV",
			"{FF8000}Vertipus I",
			"{FF8000}Vertipus II",
			"{FF8000}Vertipus III",
			"{FF8000}Vertipus IV",
			"{FF8000}Colosus I",
			"{FF8000}Colosus II",
			"{FF8000}Colosus III",
			"{FF8000}Colosus IV",
			"{eeff00}Eustache I", //110
			"{eeff00}Eustache II",
			"{eeff00}Eustache III",
			"{eeff00}Eustache IV",
			"{eeff00}Eustache V",
			"{eeff00}Opiate I",
			"{eeff00}Opiate II",
			"{eeff00}Opiate III",
			"{eeff00}Opiate IV",
			"{eeff00}Colone I",
			"{eeff00}Colone II",
			"{eeff00}Colone III",
			"{eeff00}Colone IV",
			"{eeff00}Augmene I",
			"{eeff00}Augmene II",
			"{eeff00}Augmene III",
			"{eeff00}Augmene IV",
			"{eeff00}Hozeone I",
			"{eeff00}Hozeone II",
			"{eeff00}Hozeone III",
			"{00ffa5}Summa X", //130
			"{00ffa5}Miceze I",
			"{00ffa5}Miceze II",
			"{00ffa5}Miceze III",
			"{00ffa5}Miceze IV",
			"{00ffa5}Silaize I",
			"{00ffa5}Silaize II",
			"{00ffa5}Silaize III",
			"{00ffa5}Silaize IV",
			"{00ffa5}Sumaize I",
			"{00ffa5}Sumaize II",
			"{00ffa5}Sumaize III",
			"{00ffa5}Sumaize IV",
			"{00ffa5}Agreze I",
			"{00ffa5}Agreze II",
			"{00ffa5}Agreze III",
			"{00ffa5}Agreze IV",
			"{00ffa5}Obeze I",
			"{00ffa5}Obeze II",
			"{00ffa5}Obeze III",
			"{00f8ff}Starlize X", //150
			"{00f8ff}Jenery I",
			"{00f8ff}Jenery II",
			"{00f8ff}Jenery III",
			"{00f8ff}Jenery IV",
			"{00f8ff}Fadiary I",
			"{00f8ff}Fadiary II",
			"{00f8ff}Fadiary III",
			"{00f8ff}Fadiary IV",
			"{00f8ff}Oxliary I",
			"{00f8ff}Oxliary II",
			"{00f8ff}Oxliary III",
			"{00f8ff}Oxliary IV",
			"{00f8ff}Xaniary I",
			"{00f8ff}Xaniary II",
			"{00f8ff}Xaniary III",
			"{00f8ff}Xaniary IV",
			"{00f8ff}Senairy I",
			"{00f8ff}Senairy II",
			"{00f8ff}Senairy III",
			"{a2d2ff}Axiate X", //170
			"{a2d2ff}Exuriz I",
			"{a2d2ff}Exuriz II",
			"{a2d2ff}Exuriz III",
			"{a2d2ff}Exuriz IV",
			"{a2d2ff}Minz I",
			"{a2d2ff}Minz II",
			"{a2d2ff}Minz III",
			"{a2d2ff}Minz IV",
			"{a2d2ff}Tianz I",
			"{a2d2ff}Tianz II",
			"{a2d2ff}Tianz III",
			"{a2d2ff}Tianz IV",
			"{a2d2ff}Tropiz I",
			"{a2d2ff}Tropiz II",
			"{a2d2ff}Tropiz III",
			"{a2d2ff}Tropiz IV",
			"{a2d2ff}Agriz I",
			"{a2d2ff}Agriz II",
			"{a2d2ff}Agriz III",
			"{765eff}Major X", //190
			"{765eff}Andere I",
			"{765eff}Andere II",
			"{765eff}Andere III",
			"{765eff}Andere IV",
			"{765eff}Obiere I",
			"{765eff}Obiere II",
			"{765eff}Obiere III",
			"{765eff}Obiere IV",
			"{765eff}Tionire I",
			"{765eff}Tionire II",
			"{765eff}Tionire III",
			"{765eff}Tionire IV",
			"{765eff}Sifire I",
			"{765eff}Sifire II",
			"{765eff}Sifire III",
			"{765eff}Sifire IV",
			"{765eff}Gaire I",
			"{765eff}Gaire II",
			"{765eff}Gaire III",
			"{ae5eff}Monlit X", //210
			"{ae5eff}Airith I",
			"{ae5eff}Airith II",
			"{ae5eff}Airith III",
			"{ae5eff}Airith IV",
			"{ae5eff}Izmuth I",
			"{ae5eff}Izmuth II",
			"{ae5eff}Izmuth III",
			"{ae5eff}Izmuth IV",
			"{ae5eff}Agrith I",
			"{ae5eff}Agrith II",
			"{ae5eff}Agrith III",
			"{ae5eff}Agrith IV",
			"{ae5eff}Taurath I",
			"{ae5eff}Taurath II",
			"{ae5eff}Taurath III",
			"{ae5eff}Taurath IV",
			"{ae5eff}Augmeth I",
			"{ae5eff}Augmeth II",
			"{ae5eff}Augmeth III",
			"{df5eff}Abelix X", //230
			"{ae5eff}Adrix I",
			"{ae5eff}Adrix II",
			"{ae5eff}Adrix III",
			"{ae5eff}Adrix IV",
			"{ae5eff}Stupax I",
			"{ae5eff}Stupax II",
			"{ae5eff}Stupax III",
			"{ae5eff}Stupax IV",
			"{ae5eff}Marbax I",
			"{ae5eff}Marbax II",
			"{ae5eff}Marbax III",
			"{ae5eff}Marbax IV",
			"{ae5eff}Oliax I",
			"{ae5eff}Oliax II",
			"{ae5eff}Oliax III",
			"{ae5eff}Oliax IV",
			"{ae5eff}Tierax I",
			"{ae5eff}Tierax II",
			"{ae5eff}Tierax III",
			"{e35eff}Orbit X", //250
			"{e35eff}Sipped I",
			"{e35eff}Sipped II",
			"{e35eff}Sipped III",
			"{e35eff}Sipped IV",
			"{e35eff}Orlapped I",
			"{e35eff}Orlapped II",
			"{e35eff}Orlapped III",
			"{e35eff}Orlapped IV",
			"{e35eff}Laped I",
			"{e35eff}Laped II",
			"{e35eff}Laped III",
			"{e35eff}Laped IV",
			"{e35eff}Slided I",
			"{e35eff}Slided II",
			"{e35eff}Slided III",
			"{e35eff}Slided IV",
			"{e35eff}Fraged I",
			"{e35eff}Fraged II",
			"{e35eff}Fraged III",
			"{0035ff}Juliet X", //270
			"{0035ff}Sipped I",
			"{0035ff}Sipped II",
			"{0035ff}Sipped III",
			"{0035ff}Sipped IV",
			"{0035ff}Orlapped I",
			"{0035ff}Orlapped II",
			"{0035ff}Orlapped III",
			"{0035ff}Orlapped IV",
			"{0035ff}Laped I", //f8daa6
			"{0035ff}Laped II",
			"{0035ff}Laped III",
			"{0035ff}Laped IV",
			"{0035ff}Slided I",
			"{0035ff}Slided II",
			"{0035ff}Slided III",
			"{0035ff}Slided IV",
			"{0035ff}Fraged I",
			"{0035ff}Fraged II",
			"{0035ff}Fraged III",
			"{ffd500}Orliet X", //290
			"{ffd500}Sipped I",
			"{ffd500}Sipped II",
			"{ffd500}Sipped III",
			"{ffd500}Sipped IV",
			"{ffd500}Orlapped I",
			"{ffd500}Orlapped II",
			"{ffd500}Orlapped III",
			"{ffd500}Orlapped IV",
			"{ffd500}Laped I",
			"{ffd500}Laped II",
			"{ffd500}Laped III",
			"{ffd500}Laped IV",
			"{ffd500}Slided I",
			"{ffd500}Slided II",
			"{ffd500}Slided III",
			"{ffd500}Slided IV",
			"{ffd500}Fraged I",
			"{ffd500}Fraged II",
			"{ffd500}Fraged III",
			"{f8daa6}Sonic X", //310
			"{f8daa6}Silk I",
			"{f8daa6}Silk II",
			"{f8daa6}Silk III",
			"{f8daa6}Silk IV",
			"{f8daa6}Jewelry I",
			"{f8daa6}Jewelry II",
			"{f8daa6}Jewelry III",
			"{f8daa6}Jewelry IV",
			"{f8daa6}Golden I",
			"{f8daa6}Golden II",
			"{f8daa6}Golden III",
			"{f8daa6}Golden IV",
			"{f8daa6}Shiny I",
			"{f8daa6}Shiny II",
			"{f8daa6}Shiny III",
			"{f8daa6}Shiny IV",
			"{f8daa6}Brighty I",
			"{f8daa6}Brighty II",
			"{f8daa6}Brighty III",
			"{a6cf00}Silk Sonic X", //330
			"{a6cf00}Magic I",
			"{a6cf00}Magic II",
			"{a6cf00}Magic III",
			"{a6cf00}Magic IV",
			"{a6cf00}Jinx I",
			"{a6cf00}Jinx II",
			"{a6cf00}Jinx III",
			"{a6cf00}Jinx IV",
			"{a6cf00}Arts I",
			"{a6cf00}Arts II",
			"{a6cf00}Arts III",
			"{a6cf00}Arts IV",
			"{a6cf00}Potion I",
			"{a6cf00}Potion II",
			"{a6cf00}Potion III",
			"{a6cf00}Potion IV",
			"{a6cf00}Broom I",
			"{a6cf00}Broom II",
			"{a6cf00}Broom III",
			"{a3ffbc}24K Magic X", //350
			"{a3ffbc}Chain I",
			"{a3ffbc}Chain II",
			"{a3ffbc}Chain III",
			"{a3ffbc}Chain IV",
			"{a3ffbc}Ring I",
			"{a3ffbc}Ring II",
			"{a3ffbc}Ring III",
			"{a3ffbc}Ring IV",
			"{a3ffbc}White Gold I",
			"{a3ffbc}White Gold II",
			"{a3ffbc}White Gold III",
			"{a3ffbc}White Gold IV",
			"{a3ffbc}Amaze I",
			"{a3ffbc}Amaze II",
			"{a3ffbc}Amaze III",
			"{a3ffbc}Amaze IV",
			"{a3ffbc}Richy I",
			"{a3ffbc}Richy II",
			"{a3ffbc}Richy III",
			"{fff632}Hooligans X", //370
			"{fff632}Stalker I",
			"{fff632}Stalker II",
			"{fff632}Stalker III",
			"{fff632}Stalker IV",
			"{fff632}Walker I",
			"{fff632}Walker II",
			"{fff632}Walker III",
			"{fff632}Walker IV",
			"{fff632}Sprinter I",
			"{fff632}Sprinter II",
			"{fff632}Sprinter III",
			"{fff632}Sprinter IV",
			"{fff632}Jumper I",
			"{fff632}Jumper II",
			"{fff632}Jumper III",
			"{fff632}Jumper IV",
			"{fff632}Keeper I",
			"{fff632}Keeper II",
			"{fff632}Keeper III",
			"{7c498b}Doo-Wops X", //390
			"{7c498b}Unbelieveable I",
			"{7c498b}Unbelieveable II",
			"{7c498b}Unbelieveable III",
			"{7c498b}Unbelieveable IV",
			"{7c498b}Unbeatable I",
			"{7c498b}Unbeatable II",
			"{7c498b}Unbeatable III",
			"{7c498b}Unbeatable IV",
			"{7c498b}Untouchable I",
			"{7c498b}Untouchable II",
			"{7c498b}Untouchable III",
			"{7c498b}Untouchable IV",
			"{7c498b}Unreachable I",
			"{7c498b}Unreachable II",
			"{7c498b}Unreachable III",
			"{7c498b}Unreachable IV",
			"{7c498b}Unbreakable I",
			"{7c498b}Unbreakable II",
			"{7c498b}Unbreakable III",
			"{a8b400}Unorthodox X", //410
			"{a8b400}Classico I",
			"{a8b400}Classico II",
			"{a8b400}Classico III",
			"{a8b400}Classico IV",
			"{a8b400}Tempro I",
			"{a8b400}Tempro II",
			"{a8b400}Tempro III",
			"{a8b400}Tempro IV",
			"{a8b400}Maestro I",
			"{a8b400}Maestro II",
			"{a8b400}Maestro III",
			"{a8b400}Maestro IV",
			"{a8b400}Sopro I",
			"{a8b400}Sopro II",
			"{a8b400}Sopro III",
			"{a8b400}Sopro IV",
			"{a8b400}Retro I",
			"{a8b400}Retro II",
			"{a8b400}Retro III",
			"{86b400}Smoothass X", //430
			"{86b400}Hairless I",
			"{86b400}Hairless II",
			"{86b400}Hairless III",
			"{86b400}Hairless IV",
			"{86b400}Lossless I",
			"{86b400}Lossless II",
			"{86b400}Lossless III",
			"{86b400}Lossless IV",
			"{86b400}Stainless I",
			"{86b400}Stainless II",
			"{86b400}Stainless III",
			"{86b400}Stainless IV",
			"{86b400}Sweetless I",
			"{86b400}Sweetless II",
			"{86b400}Sweetless III",
			"{86b400}Sweetless IV",
			"{86b400}Bitless I",
			"{86b400}Bitless II",
			"{86b400}Bitless III",
			"{00aaff}Faraway X", //450
			"{00aaff}Hairless I",
			"{00aaff}Hairless II",
			"{00aaff}Hairless III",
			"{00aaff}Hairless IV",
			"{00aaff}Lossless I",
			"{00aaff}Lossless II",
			"{00aaff}Lossless III",
			"{00aaff}Lossless IV",
			"{00aaff}Stainless I",
			"{00aaff}Stainless II",
			"{00aaff}Stainless III",
			"{00aaff}Stainless IV",
			"{00aaff}Sweetless I",
			"{00aaff}Sweetless II",
			"{00aaff}Sweetless III",
			"{00aaff}Sweetless IV",
			"{00aaff}Bitless I",
			"{00aaff}Bitless II",
			"{00aaff}Bitless III",
			"{2600ff}Skies X", //470
			"{2600ff}Clouds I",
			"{2600ff}Clouds II",
			"{2600ff}Clouds III",
			"{2600ff}Clouds IV",
			"{2600ff}Winds I",
			"{2600ff}Winds II",
			"{2600ff}Winds III",
			"{2600ff}Winds IV",
			"{2600ff}Splashes I",
			"{2600ff}Splashes II",
			"{2600ff}Splashes III",
			"{2600ff}Splashes IV",
			"{2600ff}Seas I",
			"{2600ff}Seas II",
			"{2600ff}Seas III",
			"{2600ff}Seas IV",
			"{2600ff}Stars I",
			"{2600ff}Stars II",
			"{2600ff}Stars III",
			"{aa00ff}Lightning X", //490
			"{aa00ff}Flash I",
			"{aa00ff}Flash II",
			"{aa00ff}Flash III",
			"{aa00ff}Flash IV",
			"{aa00ff}Thunder I",
			"{aa00ff}Thunder II",
			"{aa00ff}Thunder III",
			"{aa00ff}Thunder IV",
			"{aa00ff}Storm I",
			"{aa00ff}Storm II",
			"{aa00ff}Storm III",
			"{aa00ff}Storm IV",
			"{aa00ff}Thunderstorm I",
			"{aa00ff}Thunderstorm II",
			"{aa00ff}Thunderstorm III",
			"{aa00ff}Thunderstorm IV",
			"{aa00ff}Tornado I",
			"{aa00ff}Tornado II",
			"{aa00ff}Tornado III",
			"{ff00ca}Torpedo X", //510
			"{ff00ca}Predator I",
			"{ff00ca}Predator II",
			"{ff00ca}Predator III",
			"{ff00ca}Predator IV",
			"{ff00ca}Soldier I",
			"{ff00ca}Soldier II",
			"{ff00ca}Soldier III",
			"{ff00ca}Soldier IV",
			"{ff00ca}Operator I",
			"{ff00ca}Operator II",
			"{ff00ca}Operator III",
			"{ff00ca}Operator IV",
			"{ff00ca}Gunslinger I",
			"{ff00ca}Gunslinger II",
			"{ff00ca}Gunslinger III",
			"{ff00ca}Gunslinger IV",
			"{ff00ca}Gamer I",
			"{ff00ca}Gamer II",
			"{ff00ca}Gamer III",
			"{ffacee}Heaven X", //530
			"{ffacee}Dogstyle I",
			"{ffacee}Dogstyle II",
			"{ffacee}Dogstyle III",
			"{ffacee}Dogstyle IV",
			"{ffacee}Makeout I",
			"{ffacee}Makeout II",
			"{ffacee}Makeout III",
			"{ffacee}Makeout IV",
			"{ffacee}Shoulders I",
			"{ffacee}Shoulders II",
			"{ffacee}Shoulders III",
			"{ffacee}Shoulders IV",
			"{ffacee}Neck I",
			"{ffacee}Neck II",
			"{ffacee}Neck III",
			"{ffacee}Neck IV",
			"{ffacee}Dress I",
			"{ffacee}Dress II",
			"{ffacee}Dress III",
			"{ffacac}Hell X", //550
			"{ffacac}Dogstyle I",
			"{ffacac}Dogstyle II",
			"{ffacac}Dogstyle III",
			"{ffacac}Dogstyle IV",
			"{ffacac}Makeout I",
			"{ffacac}Makeout II",
			"{ffacac}Makeout III",
			"{ffacac}Makeout IV",
			"{ffacac}Shoulders I",
			"{ffacac}Shoulders II",
			"{ffacac}Shoulders III",
			"{ffacac}Shoulders IV",
			"{ffacac}Neck I",
			"{ffacac}Neck II",
			"{ffacac}Neck III",
			"{ffacac}Neck IV",
			"{ffacac}Dress I",
			"{ffacac}Dress II",
			"{ffacac}Dress III",
			"{ff393c}Strip X", //570
			"{ff393c}Striptist I",
			"{ff393c}Striptist II",
			"{ff393c}Striptist III",
			"{ff393c}Striptist IV",
			"{ff393c}Sexiest I",
			"{ff393c}Sexiest II",
			"{ff393c}Sexiest III",
			"{ff393c}Sexiest IV",
			"{ff393c}Hotiest I",
			"{ff393c}Hotiest II",
			"{ff393c}Hotiest III",
			"{ff393c}Hotiest IV",
			"{ff393c}Biggest I",
			"{ff393c}Biggest II",
			"{ff393c}Biggest III",
			"{ff393c}Biggest IV",
			"{ff393c}Cutiest I",
			"{ff393c}Cutiest II",
			"{ff393c}Cutiest III",
			"{00c928}Poles X", //570
			"{00c928}Assassin I",
			"{00c928}Assassin II",
			"{00c928}Assassin III",
			"{00c928}Assassin IV",
			"{00c928}Hitman I",
			"{00c928}Hitman II",
			"{00c928}Hitman III",
			"{00c928}Hitman IV",
			"{00c928}Sniper I",
			"{00c928}Sniper II",
			"{00c928}Sniper III",
			"{00c928}Sniper IV",
			"{00c928}Fighter I",
			"{00c928}Fighter II",
			"{00c928}Fighter III",
			"{00c928}Fighter IV",
			"{00c928}Samurai I",
			"{00c928}Samurai II",
			"{00c928}Samurai III",
			"{0077c9}Holes X", //590
			"{0077c9}Sword I",
			"{0077c9}Sword II",
			"{0077c9}Sword III",
			"{0077c9}Sword IV",
			"{0077c9}Archer I",
			"{0077c9}Archer II",
			"{0077c9}Archer III",
			"{0077c9}Archer IV",
			"{0077c9}Tanker I",
			"{0077c9}Tanker II",
			"{0077c9}Tanker III",
			"{0077c9}Tanker IV",
			"{0077c9}Breaker I",
			"{0077c9}Breaker II",
			"{0077c9}Breaker III",
			"{0077c9}Breaker IV",
			"{0077c9}Shocker I",
			"{0077c9}Shocker II",
			"{0077c9}Shocker III",
			"{f2ffb1}Ice Cold X", //610
			"{f2ffb1}Masterpiece I",
			"{f2ffb1}Masterpiece II",
			"{f2ffb1}Masterpiece III",
			"{f2ffb1}Masterpiece IV",
			"{f2ffb1}Styling I",
			"{f2ffb1}Styling II",
			"{f2ffb1}Styling III",
			"{f2ffb1}Styling IV",
			"{f2ffb1}Wilding I",
			"{f2ffb1}Wilding II",
			"{f2ffb1}Wilding III",
			"{f2ffb1}Wilding IV",
			"{f2ffb1}Living I",
			"{f2ffb1}Living II",
			"{f2ffb1}Living III",
			"{f2ffb1}Living IV",
			"{f2ffb1}Chunky I",
			"{f2ffb1}Chunky II",
			"{f2ffb1}Chunky III",
			"{b1ddff}777", //630
			"{b1ddff}Hot Damn I",
			"{b1ddff}Hot Damn II",
			"{b1ddff}Hot Damn III",
			"{b1ddff}Hot Damn IV",
			"{b1ddff}Money I",
			"{b1ddff}Money II",
			"{b1ddff}Money III",
			"{b1ddff}Money IV",
			"{b1ddff}Funk I",
			"{b1ddff}Funk II",
			"{b1ddff}Funk III",
			"{b1ddff}Funk IV",
			"{b1ddff}Uptown I",
			"{b1ddff}Uptown II",
			"{b1ddff}Uptown III",
			"{b1ddff}Uptown IV",
			"{b1ddff}Haze I",
			"{b1ddff}Haze II",
			"{b1ddff}Haze III",
			"{b476ff}Hazard X", //650
			"{b476ff}Loving I",
			"{b476ff}Loving II",
			"{b476ff}Loving III",
			"{b476ff}Loving IV",
			"{b476ff}Cuddler I",
			"{b476ff}Cuddler II",
			"{b476ff}Cuddler III",
			"{b476ff}Cuddler IV",
			"{b476ff}Cheeze I",
			"{b476ff}Cheeze II",
			"{b476ff}Cheeze III",
			"{b476ff}Cheeze IV",
			"{b476ff}Tiffany I",
			"{b476ff}Tiffany II",
			"{b476ff}Tiffany III",
			"{b476ff}Tiffany IV",
			"{b476ff}Diamond I",
			"{b476ff}Diamond II",
			"{b476ff}Diamond III",
			"{76ff92}Liquid X", //670
			"{76ff92}Robe I",
			"{76ff92}Robe II",
			"{76ff92}Robe III",
			"{76ff92}Robe IV",
			"{76ff92}Hercules I",
			"{76ff92}Hercules II",
			"{76ff92}Hercules III",
			"{76ff92}Hercules IV",
			"{76ff92}Finesse I",
			"{76ff92}Finesse II",
			"{76ff92}Finesse III",
			"{76ff92}Finesse IV",
			"{76ff92}Blame I",
			"{76ff92}Blame II",
			"{76ff92}Blame III",
			"{76ff92}Blame IV",
			"{76ff92}Baby I",
			"{76ff92}Baby II",
			"{76ff92}Baby III",
			"{baff76}Soledad X", //690
			"{baff76}Magnetic I",
			"{baff76}Magnetic II",
			"{baff76}Magnetic III",
			"{baff76}Magnetic IV",
			"{baff76}Floor I",
			"{baff76}Floor II",
			"{baff76}Floor III",
			"{baff76}Floor IV",
			"{baff76}4Life I",
			"{baff76}4Life II",
			"{baff76}4Life III",
			"{baff76}4Life IV",
			"{baff76}Player I",
			"{baff76}Player II",
			"{baff76}Player III",
			"{baff76}Player IV",
			"{baff76}Moon I",
			"{baff76}Moon II",
			"{baff76}Moon III",
			"{fffd76}Reacher X", //710
			"{fffd76}Karats I",
			"{fffd76}Karats II",
			"{fffd76}Karats III",
			"{fffd76}Karats IV",
			"{fffd76}Minks I",
			"{fffd76}Minks II",
			"{fffd76}Minks III",
			"{fffd76}Minks IV",
			"{fffd76}Dangerous I",
			"{fffd76}Dangerous II",
			"{fffd76}Dangerous III",
			"{fffd76}Dangerous IV",
			"{fffd76}Pinky I",
			"{fffd76}Pinky II",
			"{fffd76}Pinky III",
			"{fffd76}Pinky IV",
			"{fffd76}Pimp I",
			"{fffd76}Pimp II",
			"{fffd76}Pimp III",
			"{ffb976}Reacher X", //730
			"{ffb976}Rocket I",
			"{ffb976}Rocket II",
			"{ffb976}Rocket III",
			"{ffb976}Rocket IV",
			"{ffb976}So Player I",
			"{ffb976}So Player II",
			"{ffb976}So Player III",
			"{ffb976}So Player IV",
			"{ffb976}Skate I",
			"{ffb976}Skate II",
			"{ffb976}Skate III",
			"{ffb976}Skate IV",
			"{ffb976}Superstar I",
			"{ffb976}Superstar II",
			"{ffb976}Superstar III",
			"{ffb976}Superstar IV",
			"{ffb976}Supersonic I",
			"{ffb976}Supersonic II",
			"{ffb976}Supersonic III",
			"{ff7676}Master X", //750
			"{ff7676}Planet I",
			"{ff7676}Planet II",
			"{ff7676}Planet III",
			"{ff7676}Planet IV",
			"{ff7676}Big Bang I",
			"{ff7676}Big Bang II",
			"{ff7676}Big Bang III",
			"{ff7676}Big Bang IV",
			"{ff7676}Saturnus I",
			"{ff7676}Saturnus II",
			"{ff7676}Saturnus III",
			"{ff7676}Saturnus IV",
			"{ff7676}Neptunus I",
			"{ff7676}Neptunus II",
			"{ff7676}Neptunus III",
			"{ff7676}Neptunus IV",
			"{ff7676}Supernova I",
			"{ff7676}Supernova II",
			"{ff7676}Supernova III",
			"{bcffd1}Surface X", //770
			"{bcffd1}Stoner I",
			"{bcffd1}Stoner II",
			"{bcffd1}Stoner III",
			"{bcffd1}Stoner IV",
			"{bcffd1}Aura I",
			"{bcffd1}Aura II",
			"{bcffd1}Aura III",
			"{bcffd1}Aura IV",
			"{bcffd1}Obsidiant I",
			"{bcffd1}Obsidiant II",
			"{bcffd1}Obsidiant III",
			"{bcffd1}Obsidiant IV",
			"{bcffd1}Ruby I",
			"{bcffd1}Ruby II",
			"{bcffd1}Ruby III",
			"{bcffd1}Ruby IV",
			"{bcffd1}Pearl I",
			"{bcffd1}Pearl II",
			"{bcffd1}Pearl III",
			"{f3ffbc}Greek X", //790
			"{f3ffbc}Ares I",
			"{f3ffbc}Ares II",
			"{f3ffbc}Ares III",
			"{f3ffbc}Ares IV",
			"{f3ffbc}Poseidon I",
			"{f3ffbc}Poseidon II",
			"{f3ffbc}Poseidon III",
			"{f3ffbc}Poseidon IV",
			"{f3ffbc}Athena I",
			"{f3ffbc}Athena II",
			"{f3ffbc}Athena III",
			"{f3ffbc}Athena IV",
			"{f3ffbc}Hermes I",
			"{f3ffbc}Hermes II",
			"{f3ffbc}Hermes III",
			"{f3ffbc}Hermes IV",
			"{f3ffbc}Zeus I",
			"{f3ffbc}Zeus II",
			"{f3ffbc}Zeus III",
			"{f952ff}Station X", //810
			"{f952ff}Stick I",
			"{f952ff}Stick II",
			"{f952ff}Stick III",
			"{f952ff}Stick IV",
			"{f952ff}Console I",
			"{f952ff}Console II",
			"{f952ff}Console III",
			"{f952ff}Console IV",
			"{f952ff}Remote I",
			"{f952ff}Remote II",
			"{f952ff}Remote III",
			"{f952ff}Remote IV",
			"{f952ff}Analog I",
			"{f952ff}Analog II",
			"{f952ff}Analog III",
			"{f952ff}Analog IV",
			"{f952ff}Keyboard I",
			"{f952ff}Keyboard II",
			"{f952ff}Keyboard III",
			"{52ffbd}Holyman X", //830
			"{52ffbd}Ibrahim I",
			"{52ffbd}Ibrahim II",
			"{52ffbd}Ibrahim III",
			"{52ffbd}Ibrahim IV",
			"{52ffbd}Ismail I",
			"{52ffbd}Ismail II",
			"{52ffbd}Ismail III",
			"{52ffbd}Ismail IV",
			"{52ffbd}Ishak I",
			"{52ffbd}Ishak II",
			"{52ffbd}Ishak III",
			"{52ffbd}Ishak IV",
			"{52ffbd}Yakub I",
			"{52ffbd}Yakub II",
			"{52ffbd}Yakub III",
			"{52ffbd}Yakub IV",
			"{52ffbd}Yusuf I",
			"{52ffbd}Yusuf II",
			"{52ffbd}Yusuf III",
			"{ffac52}Students X", //850
			"{ffac52}Simon I",
			"{ffac52}Simon II",
			"{ffac52}Simon III",
			"{ffac52}Simon IV",
			"{ffac52}Petrus I",
			"{ffac52}Petrus II",
			"{ffac52}Petrus III",
			"{ffac52}Petrus IV",
			"{ffac52}Andreas I",
			"{ffac52}Andreas II",
			"{ffac52}Andreas III",
			"{ffac52}Andreas IV",
			"{ffac52}Yakobus I",
			"{ffac52}Yakobus II",
			"{ffac52}Yakobus III",
			"{ffac52}Yakobus IV",
			"{ffac52}Yohanes I",
			"{ffac52}Yohanes II",
			"{ffac52}Yohanes III",
			"{6652ff}Olympus X", //870
			"{6652ff}Hestia I",
			"{6652ff}Hestia II",
			"{6652ff}Hestia III",
			"{6652ff}Hestia IV",
			"{6652ff}Hera I",
			"{6652ff}Hera II",
			"{6652ff}Hera III",
			"{6652ff}Hera IV",
			"{6652ff}Aphrodite I",
			"{6652ff}Aphrodite II",
			"{6652ff}Aphrodite III",
			"{6652ff}Aphrodite IV",
			"{6652ff}Hades I",
			"{6652ff}Hades II",
			"{6652ff}Hades III",
			"{6652ff}Hades IV",
			"{6652ff}Apollo I",
			"{6652ff}Apollo II",
			"{6652ff}Apollo III",
			"{9aff52}Wild X", //890
			"{9aff52}Tigris I",
			"{9aff52}Tigris II",
			"{9aff52}Tigris III",
			"{9aff52}Tigris IV",
			"{9aff52}Felix I",
			"{9aff52}Felix II",
			"{9aff52}Felix III",
			"{9aff52}Maxwell I",
			"{9aff52}Maxwell II",
			"{9aff52}Maxwell III",
			"{9aff52}Canis I",
			"{9aff52}Canis II",
			"{9aff52}Canis III",
			"{9aff52}Paradisea I",
			"{9aff52}Paradisea II",
			"{9aff52}Paradisea III",
			"{fff752}Moves X", //910
			"{fff752}Alleron I",
			"{fff752}Alleron II",
			"{fff752}Alleron III",
			"{fff752}Sligton I",
			"{fff752}Sligton II",
			"{fff752}Sligton III",
			"{fff752}Avienon I",
			"{fff752}Avienon II",
			"{fff752}Avienon III",
			"{fff752}Zivalon I",
			"{fff752}Zivalon II",
			"{fff752}Zivalon III",
			"{fff752}Tendon I",
			"{fff752}Tendon II",
			"{fff752}Tendon III",
			"{ff5252}Palace X", //930
			"{ff5252}Instict I",
			"{ff5252}Instict II",
			"{ff5252}Instict III",
			"{ff5252}Orinict I",
			"{ff5252}Orinict II",
			"{ff5252}Orinict III",
			"{ff5252}Albict I",
			"{ff5252}Albict II",
			"{ff5252}Albict III",
			"{ff5252}Struict I",
			"{ff5252}Struict II",
			"{ff5252}Struict III",
			"{ff5252}Halistict I",
			"{ff5252}Halistict II",
			"{ff5252}Halistict III",
			"{54ff52}Phalanx X", //950
			"{54ff52}Tombstone I",
			"{54ff52}Tombstone II",
			"{54ff52}Tombstone III",
			"{54ff52}Skulls I",
			"{54ff52}Skulls II",
			"{54ff52}Skulls III",
			"{54ff52}Pletons I",
			"{54ff52}Pletons II",
			"{54ff52}Pletons III",
			"{54ff52}Dimmion I",
			"{54ff52}Dimmion II",
			"{54ff52}Dimmion III",
			"{54ff52}Aurethra I",
			"{54ff52}Aurethra II",
			"{54ff52}Aurethra III",
			"{bb52ff}Celamon X", //970
			"{bb52ff}Abadi I",
			"{bb52ff}Abadi II",
			"{bb52ff}Abadi III",
			"{bb52ff}Marwah I",
			"{bb52ff}Marwah II",
			"{bb52ff}Marwah III",
			"{bb52ff}Maha I",
			"{bb52ff}Maha II",
			"{bb52ff}Maha III",
			"{bb52ff}Pro Player I",
			"{bb52ff}Pro Player II",
			"{bb52ff}Pro Player III",
			"{bb52ff}Setia I",
			"{bb52ff}Setia II",
			"{bb52ff}Setia III",
			"{9900ff}Old Player",
			"{ff00f3}Fabulous",
			"{ff00a0}Magnificent",
			"{ff5a00}Most Wanted",
			"{ff0000}Most Excited",
			"{c5ff00}Most Played",
			"{00ffa5}No Life",
			"{9b111e}Dewa",
			"{9b111e}Di Atas Dewa",
			"{9b111e}Di Atas Dewa-Dewa" //1000
		};

		static const AdminLevel[11][] = 
		{
			"Bukan Admin",
			"Volunteer",
			"Junior Helper",
			"Senior Helper",
			"Head Helper",
			"Admin Level 1",
			"Admin Level 2",
			"Admin Level 3",
			"Head Admin",
			"Manager",
			"Executive"
		};

		static const VIPLevel[4][] = {
			"Bukan VIP",
			"Regular Pinky (1)",
			"Super Pinky (2)",
			"Pinkyman Pinky (3)"
		};

		static const JOBName[14][] = {
			"Pengangguran",
			"Petani",
			"Penambang",
			"Tukang Ayam",
			"Tukang Minyak",
			"Supir Angkot",
			"Nelayan",
			"Supir Kargo",
			"Porter",
			"Supir Mixer",
			"Tukang Kayu",
			"Pelaut",
			"Peternak",
			"Penjahit"
		};

		format(spstr, sizeof(spstr), 
		"Category\t Detail(s)\n\
		Character ID:\t %d\n\
		"GRAY"UCP:\t "GRAY"%s\n\
		Fullname:\t %s\n\
		"GRAY"Birthday:\t "GRAY"%s\n\
		Origin:\t %s\n\
		"GRAY"Sex:\t "GRAY"%s\n\
		Height:\t %d cm\n\
		"GRAY"Weight:\t "GRAY"%d kg\n\
		Job:\t %s\n\
		"GRAY"Faction:\t "GRAY"%s\n\
		Faction Rank:\t %s\n\
		"GRAY"Family:\t "GRAY"%s\n\
		Family Rank:\t %s\n\
		"GRAY"Cash:\t "DARKGREEN"$%s\n\
		Bank Money:\t "DARKGREEN"$%s\n\
		"GRAY"Casino Chip:\t "DARKGREEN"$%s\n\
		Dirty Money:\t "RED"$%s\n\
		"GRAY"Health:\t %.3f\n\
		Armour:\t %.3f\n\
		"GRAY"Hunger:\t %d\n\
		Thirst:\t %d\n\
		"GRAY"Stress:\t %d\n\
		Total Warning:\t "YELLOW"%d/20\n\
		"GRAY"Level:\t %d - %s\n\
		Playtime:\t %02dh %02dm %02ds\n\
		"GRAY"Admin Level:\t %s\n\
		Stewards:\t %s\n\
		"GRAY"Stewards Expiry:\t %s\n\
		VIP Level:\t %s\n\
		"GRAY"VIP Expiry:\t %s\n\
		Skin ID:\t %d\n\
		"GRAY"World ID:\t %d\n\
		Interior ID:\t %d\n\
		"GRAY"House ID:\t %d\n\
		Biz ID:\t %d\n\
		"GRAY"Door ID:\t %d\n\
		Rusun ID:\t %d\n\
		"GRAY"Last Login:\t %s\n\
		Char Register Date:\t %s",
		opID,
		Char_UCP,
		Char_Name,
		Char_Birthday,
		Char_Origin,
		(Char_Gender == 1) ? ("Laki-Laki") : ("Perempuan"),
		Char_BodyHeight,
		Char_BodyWeight,
		JOBName[Char_Job],
		FacName[Char_Faction],
		rnnrt,
		GetFamilyName(Char_Family),
		FamilyRank[Char_FamilyRank],
		FormatMoney(Char_Money),
		FormatMoney(Char_BankMoney),
		FormatMoney(Char_CasinoChip),
		FormatMoney(Char_DirtyMoney),
		Char_Health,
		Char_Armor,
		Char_Hunger,
		Char_Thirst,
		Char_Stress,
		Char_Warn,
		Char_Level,
		PlayerLevel[Char_Level],
		Char_Hours,
		Char_Minutes,
		Char_Seconds,
		AdminLevel[Char_Admin],
		(Char_Steward) ? (""DARKGREEN"Yes") : ("Not Stewards"),
		ReturnTimelapse(gettime(), Char_StewTime, ""DARKRED"Expired"),
		VIPLevel[Char_VIP],
		ReturnTimelapse(gettime(), Char_VIPTime, ""DARKRED"Expired"),
		Char_Skin,
		Char_WID,
		Char_IntID,
		Char_InHouse,
		Char_InDoor,
		Char_InRusun,
		Char_LastLogin,
		Char_RegisterDate);

		Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, sprintf("{DA9100}Pahlawan Roleplay "WHITE"- %s - (%s)", Char_UCP, Char_Name), spstr, "Tutup", "");
	}
	return true;
}

forward CheckingUCP(playerid, const PlayersName[]);
public CheckingUCP(playerid, const PlayersName[])
{
    new oucpID, UCP[22], IP[17], Register_Date[50], Last_Login[50];

    if(!cache_num_rows())
    {
		ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("UCP '%s' tidak terdeteksi!", PlayersName));
		return 1;
    }
    else
    {
        // format(sclstr, sizeof(sclstr), "%s(%d) [%s] used CMD '/checkucp'\n
        //> viewing UCP data for %s", AccountData[playerid][pAdminname], playerid, AccountData[playerid][pUCP], PlayersName);
        // CallLocalFunction("StaffCommandLog", "is", playerid, sclstr);

        cache_get_value_index_int(0, 0, oucpID);
        cache_get_value_index(0, 1, UCP);
        cache_get_value_index(0, 2, IP);
        cache_get_value_index(0, 3, Register_Date);
        cache_get_value_index(0, 4, Last_Login);

        static spstr[1024];

        format(spstr, sizeof(spstr), 
        "Category\t-\t Detail\n\
        UCP ID\t:\t %d\n\
        "GRAY"UCP Name\t:\t "GRAY"%s\n\
        IP Address\t:\t %s\n\
        "GRAY"Registration Date\t:\t "GRAY"%s\n\
        Last Login\t:\t %s",
        oucpID,
        UCP,
        IP,
        Register_Date,
        Last_Login);

        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, sprintf("{DA9100}Pahlawan Roleplay "WHITE"- %s(UID: %d)", UCP, oucpID), spstr, "Tutup", "");
    }
    return true;
}

forward CheckingCharList(playerid, const PlayersName[]);
public CheckingCharList(playerid, const PlayersName[])
{
    if(!cache_num_rows())
    {
		ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("UCP '%s' tidak terdeteksi!", PlayersName));
		return 1;
    }
    else
    {
        // format(sclstr, sizeof(sclstr), "%s(%d) [%s] used CMD '/acharlist'\n
        //> viewing character list for UCP %s", AccountData[playerid][pAdminname], playerid, AccountData[playerid][pUCP], PlayersName);
        // CallLocalFunction("StaffCommandLog", "is", playerid, sclstr);

        new cQuery[525], ucppid;

        cache_get_value_name_int(0, "ID", ucppid);

        mysql_format(g_SQL, cQuery, sizeof(cQuery), "SELECT * FROM `player_characters` WHERE `Char_UCP` = '%e' ORDER BY pID ASC LIMIT 30", PlayersName);
        mysql_query(g_SQL, cQuery);

        new rows = cache_num_rows();
        if(rows) 
        {
            new list[512], charpid, chaname[25], charip[17], charlvl, charadmin, charregdate[50], charlastlog[50];

            format(list, sizeof(list), "Character ID | Name (IP Address)\tLevel (Admin)\tRegistration Date\tLast Login\n");
            for(new i; i < rows; ++i)
            {
                cache_get_value_name_int(i, "pID", charpid);
                cache_get_value_name(i, "Char_Name", chaname);
                cache_get_value_name(i, "Char_IP", charip);
                cache_get_value_name_int(i, "Char_Level", charlvl);
                cache_get_value_name_int(i, "Char_Admin", charadmin);
                cache_get_value_name(i, "Char_RegisterDate", charregdate);
                cache_get_value_name(i, "Char_LastLogin", charlastlog);

                static const AdminLevel[11][] = 
				{
					"Bukan Admin",
					"Volunteer",
					"Junior Helper",
					"Senior Helper",
					"Head Helper",
					"Admin Level 1",
					"Admin Level 2",
					"Admin Level 3",
					"Head Admin",
					"Manager",
					"Executive"
				};

                format(list, sizeof(list), 
                "%s%d | %s (%s)\t%d (%s)\t%s\t%s\n",
                list,
                charpid,
                chaname,
                charip,
                charlvl,
                AdminLevel[charadmin],
                charregdate,
                charlastlog);
            }
            Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, sprintf("{DA9100}Pahlawan Roleplay "WHITE"- %s(UID: %d)", PlayersName, ucppid), list, "Tutup", "");
        }
        else
        {
            new list[525];
            
            format(list, sizeof(list), "Character ID | Name (IP Address)\tLevel (Admin)\tRegistration Date\tLast Login\n");
            format(list, sizeof(list), "%sThe UCP account does not have any characters!", list);
            Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, sprintf("{DA9100}Pahlawan Roleplay "WHITE"- %s(UID: %d)", PlayersName, ucppid), list, "Tutup", "");
        }
    }
    return 1;
}

ShowALV10Help(playerid)
{
    if(AccountData[playerid][pAdmin] < 10)
        return PermissionError(playerid);

    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Executive", 
    "Syntax\tDescription\n\
    /givemoneyall [amount]\tBeri uang ke semua player.\n\
    "GRAY"/giveweapall [id]\t"GRAY"Beri senjata semua player.\n\
    /kickall\tKick semua player.\n\
    "GRAY"/setmoney [id] [amount]\t"GRAY"Atur uang cash player.\n\
    /givemoney [id] [amount]\tBeri uang cash player.\n\
    "GRAY"/setbankmoney [id] [jml]\t"GRAY"Atur saldo bank player.\n\
    /givebankmoney [id] [jml]\tTransfer ke bank player.\n\
    "GRAY"/osetbank [name] [jml]\t"GRAY"Atur bank player offline.\n\
    /vcreate [id] [mod] [c1] [c2]\tBuat kendaraan permanen.\n\
    "GRAY"/setapprentice [id] [0-1]\t"GRAY"Atur status Apprentice.\n\
    /setsteward [id] [days]\tAtur status Steward.\n\
    "GRAY"/setvip [id] [lvl] [days]\t"GRAY"Atur status VIP player.\n\
    /changeucp [id] [name]\tGanti nama akun UCP.\n\
	"GRAY"/setadminlevel [id] [lvl]\t"GRAY"Atur level admin.", "Tutup", "");
    return 1;
}

ShowALV9Help(playerid)
{
    if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);

    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Manager", 
    "Syntax\tDescription\n\
    /oreco [name]\tReset ekonomi offline.\n\
    "GRAY"/schedulemt [time]\t"GRAY"Jadwal maintenance server.\n\
    /removepv [vid]\tHapus kendaraan pribadi.\n\
    "GRAY"/setgender [id] [sex]\t"GRAY"Ubah kelamin karakter.\n\
    /setstock [name]\tAtur stok bisnis/komponen.\n\
    "GRAY"/backup\t"GRAY"Backup database server.\n\
    /dynhelp\tKelola aset dynamic.\n\
    "GRAY"/changeplate [vid] [text]\t"GRAY"Ganti plat kendaraan.\n\
    /changephnumber [id] [num]\tGanti nomor HP player.\n\
    "GRAY"/changebanknumber [id] [num]\t"GRAY"Ganti nomor rekening.\n\
    /setstressall [amount]\tAtur stress semua player.\n\
    "GRAY"/setarmorall [amount]\t"GRAY"Atur armor semua player.\n\
    /sethbeall [amount]\tAtur lapar/haus semua.\n\
    "GRAY"/gethereall\t"GRAY"Tarik semua player.\n\
	/asetitem\tMengatur item di inventory player.\n\
	"GRAY"/agiveitem\t"GRAY"Memberikan item kepada player.\n\
	/asetitemall\tMemberikan item kepada semua player.\n\
	"GRAY"/aremoveitem\t"GRAY"Menghapus item dari inventory player.", "Tutup", "");
    return 1;
}

ShowALV8Help(playerid)
{
    if(AccountData[playerid][pAdmin] < 8)
        return PermissionError(playerid);

    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Head Admin", 
    "Syntax\tDescription\n\
	/unblockucp [ucp]\tBuka blokir UCP.\n\
    "GRAY"/blockucp [ucp] [days] [reason]\t"GRAY"Blokir akun UCP.\n\
    /areviveall\tHidupkan semua player.\n\
    "GRAY"/sethpall [amount]\t"GRAY"Set darah semua player.\n\
    /unban [name]\tBuka banned player.\n\
    "GRAY"/banip [ip]\t"GRAY"Blokir alamat IP.\n\
    /unbanip [ip]\tBuka banned IP.\n\
    "GRAY"/explode [id]\t"GRAY"Ledakkan player.\n\
    /setadminname [id] [name]\tGanti nama admin.\n\
    "GRAY"/setname [id] [name]\t"GRAY"Ganti nama karakter.\n\
    /togspy\tMode mata-mata PM.\n\
    "GRAY"/reco [id]\t"GRAY"Reset ekonomi player.\n\
    /setlevel [id] [lvl]\tAtur level score player.\n\
    "GRAY"/konser\t"GRAY"Setel playlist musik server.\n\
    /goodmood\tPulihkan kondisi player.", "Tutup", "");
    return 1;
}

ShowALV7Help(playerid)
{
    if(AccountData[playerid][pAdmin] < 7)
        return PermissionError(playerid);

    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Admin Level 3", 
    "Syntax\tDescription\n\
    /togooc\tToggle chat global OOC.\n\
    "GRAY"/ufo\t"GRAY"Pasang UFO di kendaraan.\n\
    /dufo\tHapus UFO dari kendaraan.\n\
    "GRAY"/setfaction [id] [fac] [rank]\t"GRAY"Atur fraksi player.\n\
    /setfamily [id] [fam] [rank]\tAtur family player.\n\
    "GRAY"/kickfamily [id]\t"GRAY"Keluarkan dari family.\n\
    /giveweap [id] [gun] [type] [ammo]\tBeri senjata ke player.", "Tutup", "");
    return 1;
}

ShowALV6Help(playerid)
{
    if(AccountData[playerid][pAdmin] < 6)
        return PermissionError(playerid);

    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Admin Level 2", 
    "Syntax\tDescription\n\
    /setjob [id] [job]\tMengatur pekerjaan player.\n\
    "GRAY"/oban [name] [days] [reason]\t"GRAY"Banned player offline.\n\
    /oresetweap [name]\tReset senjata player offline.\n\
    "GRAY"/torture [id]\t"GRAY"Menyiksa karakter player.\n\
    /ann [title] [text]\tPengumuman global server.\n\
    "GRAY"/sethbe [id] [amount]\t"GRAY"Atur lapar & haus player.\n\
    /setstress [id] [amount]\tAtur stress/mood player.\n\
    "GRAY"/makequiz [type]\t"GRAY"Buat kuis berhadiah.\n\
    /vote [type]\tBuat voting server.", "Tutup", "");
    return 1;
}

ShowALV5Help(playerid)
{
    if(AccountData[playerid][pAdmin] < 5)
        return PermissionError(playerid);

    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Admin Level 1", 
    "Syntax\tDescription\n\
    /akill [id]\tMembunuh player seketika.\n\
    "GRAY"/ojail [name] [time] [reason]\t"GRAY"Penjara player offline.\n\
    /resetweap [id]\tReset senjata player.\n\
    "GRAY"/fine [id] [amount]\t"GRAY"Memberi denda uang.\n\
    /rpschooltext [text]\tMengubah teks object material.\n\
    "GRAY"/resetcd [id]\t"GRAY"Reset cooldown kerja.\n\
    /resetcdcarsteal\tReset cooldown curi mobil.\n\
    "GRAY"/resetcdrobbery\t"GRAY"Reset cooldown merampok.\n\
    /playnearsong [url]\tPutar musik radius sekitar.\n\
    "GRAY"/sann [id] [msg]\t"GRAY"Pesan layar privat.\n\
    /settime [time]\tMengatur waktu server.\n\
    "GRAY"/setweather [id]\t"GRAY"Mengatur cuaca server.\n\
    /ginsu [time]\tRespawn kendaraan umum.", "Tutup", "");
    return 1;
}

ShowALV4Help(playerid)
{
    if(AccountData[playerid][pAdmin] < 4)
        return PermissionError(playerid);

    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Head Helper", 
    "Syntax\tDescription\n\
    /getveh [vehid]\tMenarik kendaraan ke lokasi anda.\n\
    "GRAY"/aeject [playerid]\t"GRAY"Paksa keluar player dari kendaraan.\n\
    /setvw [playerid] [vw]\tMengatur Virtual World player.\n\
    "GRAY"/setint [playerid] [int]\t"GRAY"Mengatur Interior ID player.\n\
    /owarn [name] [reason]\tMemberi warning ke player offline.\n\
    "GRAY"/ptp [player1] [player2]\t"GRAY"Teleport player 1 ke player 2.\n\
    /ban [id] [days] [reason]\tBanned player (0 = Permanen).\n\
    "GRAY"/acuff [playerid]\t"GRAY"Memborgol player (Admin Cuff).\n\
    /auncuff [playerid]\tMelepas borgol player.\n\
    "GRAY"/jetpack\t"GRAY"Memunculkan alat Jetpack.\n\
    /unjail [playerid]\tBebaskan player dari penjara.\n\
    "GRAY"/sendveh [playerid] [vehid]\t"GRAY"Mengirim kendaraan ke player.\n\
    /gotoco [x] [y] [z] [int]\tTeleport ke koordinat spesifik.\n\
    "GRAY"/adveh\t"GRAY"Hapus kendaraan di sekitar (Radius).\n\
    /adjveh\tHapus kendaraan Job di sekitar.\n\
    "GRAY"/setskin [playerid] [id]\t"GRAY"Mengganti model skin player.\n\
    /sendto [playerid] [loc]\tKirim player ke lokasi umum.\n\
    "GRAY"/dveh\t"GRAY"Hapus kendaraan yang dinaiki.\n\
    /aclear\tMembersihkan layar chat umum.\n\
    "GRAY"/rclear\t"GRAY"Membersihkan daftar report.", "Tutup", "");
    return 1;
}

ShowALV3Help(playerid)
{
    if(AccountData[playerid][pAdmin] < 3)
        return PermissionError(playerid);

    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Senior Helper", 
    "Syntax\tDescription\n\
    /gethere [playerid]\tMenarik player ke lokasi anda.\n\
    "GRAY"/slap [playerid]\t"GRAY"Menampar player ke udara.\n\
    /freeze [playerid]\tMembekukan pergerakan player.\n\
    "GRAY"/unfreeze [playerid]\t"GRAY"Mencairkan kembali player.\n\
    /getip [playerid]\tMelihat alamat IP player.\n\
    "GRAY"/akaip [playerid]\t"GRAY"Cek akun lain di IP yang sama.\n\
    /checkucp [ucp]\tMengecek detail akun UCP.\n\
    "GRAY"/acharlist [ucp]\t"GRAY"Lihat list character dalam UCP.\n\
    /rveh [vehid]\tRespawn kendaraan tertentu.\n\
    "GRAY"/arevive [playerid]\t"GRAY"Menghidupkan player (Revive).\n\
    /sethp [playerid] [amount]\tMengatur jumlah HP player.\n\
    "GRAY"/setarmor [playerid] [amount]\t"GRAY"Mengatur jumlah Armor player.\n\
    /getin [vehid]\tTeleport masuk ke kendaraan.\n\
    "GRAY"/takeoutveh [playerid]\t"GRAY"Mengeluarkan paksa dari kendaraan.\n\
    /cd\tMemulai hitung mundur global.\n\
    "GRAY"/gotoveh [vehid]\t"GRAY"Teleport ke ID kendaraan.\n\
    /avehlist [playerid]\tMelihat daftar kendaraan milik player.\n\
    "GRAY"/gotopmeter [id]\t"GRAY"Teleport ke ID parking meter.\n\
    /gotorsign [id]\tTeleport ke ID road sign.\n\
	"GRAY"/reloadweap [playerid]\t"GRAY"Memuat ulang senjata player.\n\
    /ainv [playerid]\tMelihat isi inventory player.", "Tutup", "");
    return 1;
}

ShowALV2Help(playerid)
{
    if(AccountData[playerid][pAdmin] < 2)
        return PermissionError(playerid);

    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Junior Helper", 
    "Syntax\tDescription\n\
    /ra [reportid]\tMenerima laporan player dari daftar /reports.\n\
    "GRAY"/goto [playerid]\t"GRAY"Teleport ke lokasi player tertentu.\n\
    /gotols\tTeleport ke pusat kota Los Santos.\n\
    "GRAY"/spec [playerid]\t"GRAY"Masuk mode pemantauan (Spectate).\n\
    /spec off\tKeluar dari mode Spectate.\n\
    "GRAY"/ntag\t"GRAY"Melihat nametag player jarak jauh.\n\
    /astats [playerid]\tMelihat statistik player online.\n\
    "GRAY"/ostats [name]\t"GRAY"Melihat statistik player offline.\n\
    /jaillist\tMelihat daftar player di penjara OOC.\n\
    "GRAY"/warn [playerid] [reason]\t"GRAY"Memberikan peringatan resmi ke player.\n\
    /unwarn [playerid]\tMenghapus 1 warning dari player.\n\
    "GRAY"/kick [playerid] [reason]\t"GRAY"Mengeluarkan player dari server.\n\
    /jail [playerid] [minutes] [fine] [reason]\tMemenjarakan player (OOC Jail).\n\
    "GRAY"/fixes\t"GRAY"Menerima request perbaikan kendaraan.\n\
    /afix\tMemperbaiki mesin & bodi kendaraan.\n\
    "GRAY"/afuel\t"GRAY"Mengisi bensin kendaraan hingga penuh.\n\
    /setfuel [vehicle id] [amount]\tMengatur jumlah liter bensin.\n\
	"GRAY"/veh [modelid/name] [color 1] [color 2]\t"GRAY"Membuat kendaraan sementara.\n\
	/adlog [playerid]\tMelihat log kerusakan/tembakan (Damage Log).", "Tutup", "");
    return 1;
}

ShowALV1Help(playerid)
{
    if(AccountData[playerid][pAdmin] < 1)
        return PermissionError(playerid);

    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Volunteer", 
    "Syntax\tDescription\n\
    /aduty\tMengaktifkan atau menonaktifkan status tugas (On-Duty).\n\
    "GRAY"/a\t"GRAY"Mengirim pesan ke obrolan internal staff.\n\
    /ahelp\tMelihat daftar seluruh perintah admin level Anda.\n\
    "GRAY"/asks\t"GRAY"Melihat daftar pertanyaan yang masuk.\n\
    /ans [ask id] [jawaban]\tMenjawab pertanyaan player dari daftar /asks.\n\
    "GRAY"/reports\t"GRAY"Melihat daftar laporan (Hanya pantau).\n\
    /count\tMelihat statistik player online.\n\
    "GRAY"/near\t"GRAY"Melihat ID player jangkauan terdekat.\n\
    /checkwarns [playerid/name]\tMelihat riwayat warning pada akun player.\n\
    "GRAY"/aka [playerid]\t"GRAY"Cek sejarah alias & IP player (Akun Ganda).\n\
	/zo [text]\tBerbicara di Zona OOC.\n\
    "GRAY"/vmodels\t"GRAY"Cari ID model kendaraan dari nama.\n\
    /vehname [keyword]\tCari nama kendaraan dari ID model.", "Tutup", "");
    return 1;
}

ShowDynActorHelp(playerid)
{
    if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);

    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Dynamic Actor", 
    "Dynamic Actor Commands\tDescription\n\
    /addactor\tAdd a dynamic actor\n\
    "GRAY"/editactor\t"GRAY"Edit a dynamic actor\n\
    /editactor [pos]\tChange the position of a dynamic actor to your location\n\
    "GRAY"/editactor [skin]\t"GRAY"Change the skin of a dynamic actor\n\
    /editactor [name]\tChange the name of a dynamic actor\n\
    "GRAY"/editactor [anim]\t"GRAY"Change the animation of a dynamic actor (use animation index, can be found on Google)\n\
    /editactor [invul]\tChange invulnerability status (1 = yes, 0 = no) of a dynamic actor\n\
    "GRAY"/editactor [health]\t"GRAY"Change the health of a dynamic actor\n\
    /gotoactor\tTeleport to the location of a dynamic actor\n\
    "GRAY"/removeactor\t"GRAY"Remove a dynamic actor\n\
    Note: Do not use these commands without the owner's knowledge and permission, except for teleportation!",
    "Tutup", "");
    return 1;
}

ShowDynBikeRentalHelp(playerid)
{
    if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);

    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Dynamic Bike Rental", 
    "Dynamic Bike Rental Commands\tDescription\n\
    /addbikerent\tAdd a dynamic bike rental\n\
    "GRAY"/editbikerent\t"GRAY"Edit a dynamic bike rental\n\
    /editbikerent [bikerentpos]\tChange the location of a dynamic bike rental to your location\n\
    "GRAY"/editbikerent [cost1]\t"GRAY"Change the price of dynamic bike rental slot 1\n\
    /editbikerent [cost2]\tChange the price of dynamic bike rental slot 2\n\
    "GRAY"/removebikerent\t"GRAY"Remove a dynamic bike rental\n\
    /gotobikerent\tTeleport to the location of dynamic bike rental\n\
    Note: Do not use these commands without the owner's knowledge and permission, except for teleportation!",
    "Tutup", "");
    return 1;
}

ShowDynDoorHelp(playerid)
{
    if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);

    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Dynamic Door", 
    "Dynamic Door Commands\tDescription\n\
    /adddoor\tAdd a dynamic door\n\
    "GRAY"/gotodoor\t"GRAY"Teleport to the location of a dynamic door\n\
    /editdoor\tEdit a dynamic door\n\
    "GRAY"/editdoor [location]\t"GRAY"Change the location of a dynamic door to your location\n\
    /editdoor [interior]\tChange the interior of a dynamic door to your location\n\
    "GRAY"/editdoor [password]\t"GRAY"Change the password of a dynamic door\n\
    /editdoor [name]\tChange the name of a dynamic door\n\
    "GRAY"/editdoor [locked]\t"GRAY"Toggle the lock state of a dynamic door\n\
    /editdoor [admin]\tChange the minimum admin level to access the dynamic door\n\
    "GRAY"/editdoor [vip]\t"GRAY"Change the minimum VIP level to access the dynamic door\n\
    /editdoor [faction]\tChange the dynamic door access for a specific faction\n\
    "GRAY"/editdoor [family]\t"GRAY"Change the dynamic door access for a specific family\n\
    /editdoor [virtual]\tChange the virtual world ID of a dynamic door\n\
    "GRAY"/editdoor [pickup]\t"GRAY"Change the pickup ID of a dynamic door\n\
    /editdoor [remove]\tRemove a dynamic door\n\
    Note: Do not use these commands without the owner's knowledge and permission, except for teleportation!",
    "Tutup", "");
    return 1;
}

ShowDynFivemLabelHelp(playerid)
{
    if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);

    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Dynamic FiveM Label", 
    "Dynamic FiveM Label Commands\tDescription\n\
    /addflabel\tAdd a dynamic FiveM label\n\
    "GRAY"/editflabel\t"GRAY"Edit a dynamic FiveM label\n\
    /editflabel [location]\tChange the location of a dynamic FiveM label to your location\n\
    "GRAY"/editflabel [pos]\t"GRAY"Change the position of a dynamic FiveM label specifically (PC Only)\n\
    /editflabel [togpickup]\tToggle the pickup of a dynamic FiveM label (0 = no pickup, 1 = use pickup)\n\
    "GRAY"/editflabel [pickup]\t"GRAY"Change the pickup ID of a dynamic FiveM label\n\
    /editflabel [text]\tChange the text of a dynamic FiveM label\n\
    "GRAY"/removeflabel\t"GRAY"Remove a dynamic FiveM label\n\
    /gotoflabel\tTeleport to a dynamic FiveM label\n\
    Note: Do not use these commands without the owner's knowledge and permission, except for teleportation!",
    "Tutup", "");
    return 1;
}

ShowDynGarageHelp(playerid)
{
    if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);

    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Dynamic Garage", 
    "Dynamic Garage Commands\tDescription\n\
    /addgarkot\tAdd a dynamic garage\n\
    "GRAY"/editgarkot\t"GRAY"Edit a dynamic garage\n\
    /editgarkot [greenpos]\tChange the location of the green zone of a dynamic garage to your location\n\
    "GRAY"/editgarkot [redpos]\t"GRAY"Change the location of the red zone of a dynamic garage to your location\n\
    /editgarkot [spawnpos]\tChange the spawn location of a dynamic garage to your location\n\
    "GRAY"/removegarkot\t"GRAY"Remove a dynamic garage\n\
    /gotogarkot\tTeleport to the location of a dynamic garage\n\
    Note: Do not use these commands without the owner's knowledge and permission, except for teleportation!",
    "Tutup", "");
    return 1;
}

ShowDynGarbageHelp(playerid)
{
    if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);

    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Dynamic Garbage", 
    "Dynamic Garbage Commands\tDescription\n\
    /addgarbage\tAdd a dynamic garbage\n\
    "GRAY"/removegarbage\t"GRAY"Remove a dynamic garbage\n\
    /gotogarbage\tTeleport to the location of a dynamic garbage\n\
    "GRAY"/editgarbage\t"GRAY"Edit a dynamic garbage\n\
    /editgarbage [pos]\tChange the position of a dynamic garbage specifically (PC Only)\n\
    "GRAY"/editgarbage [trash]\t"GRAY"Change the amount of trash in a dynamic garbage\n\
    /editgarbage [interior]\tChange the interior ID of a dynamic garbage\n\
    "GRAY"/editgarbage [virtual]\t"GRAY"Change the virtual world ID of a dynamic garbage\n\
    Note: Do not use these commands without the owner's knowledge and permission, except for teleportation!",
    "Tutup", "");
    return 1;
}

ShowDynIconHelp(playerid)
{
    if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);

    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Dynamic Icon", 
    "Dynamic Icon Commands\tDescription\n\
    /addicon\tAdd a dynamic icon\n\
    "GRAY"/editicon\t"GRAY"Edit a dynamic icon\n\
    /editicon [location]\tChange the location of a dynamic icon to your location\n\
    "GRAY"/editicon [type]\t"GRAY"Change the symbol of a dynamic icon\n\
    /gotoicon\tTeleport to a dynamic icon\n\
    "GRAY"/removeicon\t"GRAY"Remove a dynamic icon\n\
    Note: Do not use these commands without the owner's knowledge and permission, except for teleportation!",
    "Tutup", "");
    return 1;
}

ShowDynKanabisHelp(playerid)
{
    if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);

    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Dynamic Kanabis", 
    "Dynamic Kanabis Commands\tDescription\n\
    /addkanabis\tAdd a dynamic kanabis\n\
    "GRAY"/removekanabis\t"GRAY"Remove a dynamic kanabis\n\
    /gotokanabis\tTeleport to the location of a dynamic kanabis\n\
    "GRAY"/editkanabis\t"GRAY"Edit a dynamic kanabis\n\
    /editkanabis [pos]\tChange the position of a dynamic kanabis specifically (PC Only)\n\
    "GRAY"/editkanabis [interior]\t"GRAY"Change the interior ID of a dynamic kanabis\n\
    /editkanabis [virtual]\tChange the virtual world ID of a dynamic kanabis\n\
    Note: Do not use these commands without the owner's knowledge and permission, except for teleportation!",
    "Tutup", "");
    return 1;
}

/*ShowDynRobberyHelp(playerid)
{
	if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);

    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Dynamic Robbery", 
    "Perintah Dynamic Robbery\tKeterangan\n\
	/addrobbery\ttambahkan dynamic robbery\n\
	/editrobbery\tedit dynamic robbery\n\
	/editrobbery [pos]\tmengubah lokasi dynamic robbery ke lokasi anda\n\
	/editrobbery [skin]\tmengubah skin id dynamic robbery\n\
	/gotorobbery\tteleportasi ke dynamic robbery\n\
	/removerobbery\tmenghapus dynamic robbery\n\
	Catatan: Dilarang menggunakan CMD ini tanpa sepengetahuan dan izin dari owner kecuali teleport!",
    "Tutup", "");
    return 1;
}*/

ShowDynRobberyHelp(playerid)
{
	if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);

    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Dynamic Robbery", 
    "Dynamic Robbery Commands\tDescription\n\
	/addrobbery\tAdd a dynamic robbery\n\
	"GRAY"/editrobbery\t"GRAY"Edit a dynamic robbery\n\
	/editrobbery [pos]\tChange the position of a dynamic robbery specifically (PC Only)\n\
	"GRAY"/editrobbery [vw]\t"GRAY"Change the virtual world ID of dynamic robbery\n\
	/editrobbery [int]\tChange the interior ID of dynamic robbery\n\
	"GRAY"/gotorobbery\t"GRAY"Teleport to dynamic robbery\n\
	/removerobbery\tRemove dynamic robbery\n\
	Note: Do not use these commands without the owner's knowledge and permission, except for teleportation!",
    "Tutup", "");
    return 1;
}

ShowDynShopHelp(playerid)
{
	if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);

    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Dynamic Shop", 
    "Dynamic Shop Commands\tDescription\n\
	/addshop\tAdd a dynamic shop\n\
	"GRAY"/editshop\t"GRAY"Edit a dynamic shop\n\
	/editshop [location]\tChange the location of dynamic shop to your location\n\
	"GRAY"/editshop [type]\t"GRAY"Change the type of dynamic shop (1 = Minimarket, 2 = Clothes)\n\
	/editshop [remove]\tRemove dynamic shop\n\
	"GRAY"/gotoshop\t"GRAY"Teleport to dynamic shop\n\
	Note: Do not use these commands without the owner's knowledge and permission, except for teleportation!",
    "Tutup", "");
    return 1;
}

ShowDynButtonHelp(playerid)
{
	if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);

    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Dynamic Button", 
    "Dynamic Button Commands\tDescription\n\
	/addbutton\tAdd a dynamic button\n\
	"GRAY"/editbutton\t"GRAY"Edit a dynamic button\n\
	/editbutton [doormodel]\tChange the door button object\n\
	"GRAY"/editbutton [faction]\t"GRAY"Set the door button for a specific faction ID\n\
	/editbutton [speed]\tSet the door button movement speed\n\
	"GRAY"/editbutton [close]\t"GRAY"Set the closed position of the door button\n\
	/editbutton [open]\tSet the open position of the door button\n\
	"GRAY"/editbutton [buttonpos]\t"GRAY"Set the position of the door button\n\
	/editbutton [remove]\tRemove dynamic button\n\
	"GRAY"/gotobutton\t"GRAY"Teleport to dynamic button\n\
	Note: Do not use these commands without the owner's knowledge and permission, except for teleportation!",
    "Tutup", "");
    return 1;
}

ShowDynRusunHelp(playerid)
{
	if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);

    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Dynamic Rusun", 
    "Dynamic Rusun Commands\tDescription\n\
	/addrusun\tAdd a dynamic Rusun (apartment)\n\
	"GRAY"/editrusun\t"GRAY"Edit a dynamic Rusun\n\
	/editrusun [pos]\tChange the position of dynamic Rusun\n\
	"GRAY"/editrusun [cost]\t"GRAY"Set the monthly rental price of dynamic Rusun\n\
	/editrusun [name]\tChange the name of dynamic Rusun\n\
	"GRAY"/editrusun [reset]\t"GRAY"Reset ownership of dynamic Rusun\n\
	/removerusun\tRemove dynamic Rusun\n\
	Note: Do not use these commands without the owner's knowledge and permission, except for teleportation!",
    "Tutup", "");
    return 1;
}

ShowDynGudangHelp(playerid)
{
	if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);

    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Dynamic Gudang", 
    "Dynamic Gudang Commands\tDescription\n\
	/addgudang\tAdd a dynamic Gudang (warehouse)\n\
	"GRAY"/editgudang\t"GRAY"Edit a dynamic Gudang\n\
	/editgudang [pos]\tChange the position of dynamic Gudang\n\
	"GRAY"/editgudang [cost]\t"GRAY"Set the monthly rental price of dynamic Gudang\n\
	/editgudang [name]\tChange the name of dynamic Gudang\n\
	"GRAY"/gotogudang\t"GRAY"Teleport to dynamic Gudang\n\
	/removegudang\tRemove dynamic Gudang\n\
	Note: Do not use these commands without the owner's knowledge and permission, except for teleportation!",
    "Tutup", "");
    return 1;
}

Dialog:AdminHelp(playerid, response, listitem, inputtext[])
{
	if (!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	switch(listitem)
	{
		case 0: // Volunteer
		{
			ShowALV1Help(playerid);
		}
		case 1: // Junior Helper
		{
			ShowALV2Help(playerid);
		}
		case 2: // Senior Helper
		{
			ShowALV3Help(playerid);
		}
		case 3: // Head Helper
		{
			ShowALV4Help(playerid);
		}
		case 4: // Admin Level 1
		{
			ShowALV5Help(playerid);
		}
		case 5: // Admin Level 2
		{
			ShowALV6Help(playerid);
		}
		case 6: // Admin Level 3
		{
			ShowALV7Help(playerid);
		}
		case 7: // Head Admin
		{
			ShowALV8Help(playerid);
		}
		case 8: // Manager
		{
			ShowALV9Help(playerid);
		}
		case 9: // Executive
		{
			ShowALV10Help(playerid);
		}
	}
	return 1;
}
Dialog:AdminDynamicHelp(playerid, response, listitem, inputtext[])
{
	if (!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	switch(listitem)
	{
		case 0: // Actor
		{
			ShowDynActorHelp(playerid);
		}
		case 1:
		{
			ShowDynBikeRentalHelp(playerid);
		}
		case 2:
		{
			ShowDynDoorHelp(playerid);
		}
		case 3:
		{
			ShowDynFivemLabelHelp(playerid);
		}
		case 4:
		{
			ShowDynGarageHelp(playerid);
		}
		case 5:
		{
			ShowDynGarbageHelp(playerid);
		}
		case 6:
		{
			ShowDynIconHelp(playerid);
		}
		case 7:
		{
			ShowDynKanabisHelp(playerid);
		}
		case 8:
		{
			ShowDynRobberyHelp(playerid);
		}
		case 9:
		{
			ShowDynShopHelp(playerid);
		}
		case 10:
		{
			ShowDynButtonHelp(playerid);
		}
		case 11:
		{
			ShowDynRusunHelp(playerid);
		}
		case 12:
		{
			ShowDynGudangHelp(playerid);
		}
	}
	return 1;
}
Dialog:AdmSetName(playerid, response, listitem, inputtext[])
{
	if (!response)
	{
		AccountData[playerid][pTempSQLFactMemberID] = INVALID_PLAYER_ID;
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		return 1;
	}

	new otherid = AccountData[playerid][pTempSQLFactMemberID], tempName[MAX_PLAYER_NAME + 1];
	if (!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if (!AccountData[otherid][IsLoggedIn]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	
	if (isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat mengosongkannya!");
	if (strlen(inputtext) < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal 4 karakter dan maksimal 23 karakter!");
	if (strlen(inputtext) > 23) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal 4 karakter dan maksimal 23 karakter!");
	
	if (!IsRoleplayName(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Nama tidak sesuai dengan format nickname roleplay!");
	if (!IsValidName(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Nama mengandung karakter yang tidak valid!");
	
	strcopy(tempName, inputtext);

	new query[248];
	mysql_format(g_SQL, query, sizeof(query), "SELECT `Char_Name` FROM `player_characters` WHERE `Char_Name`='%e'", tempName);
	mysql_pquery(g_SQL, query, "SetName", "is", playerid, tempName);
	return 1;
}

Dialog:AdmTakeoutVeh(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
	if(AccountData[playerid][pTempValue] == -1) return 1;

	if (!IsPlayerConnected(AccountData[playerid][pTempValue]) && !AccountData[AccountData[playerid][pTempValue]][pSpawned])
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut belum spawn/tidak terkoneksi!");

	new id = ReturnVehicleIDATakeOut(AccountData[playerid][pTempValue], listitem);
	new Float:px, Float:py, Float:pz, Float:pa;
	if (id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan!");

	PlayerVehicle[id][pVehParked] = -1;
	PlayerVehicle[id][pVehFamGarage] = -1;
	PlayerVehicle[id][pVehHouseGarage] = -1;
	PlayerVehicle[id][pVehInsuranced] = false;

	PlayerVehicle[id][pVehImpounded] = false;
	PlayerVehicle[id][pVehImpoundDuration] = 0;
	PlayerVehicle[id][pVehImpoundFee] = 0;
	PlayerVehicle[id][pVehImpoundReason][0] = EOS;

	GetPlayerPos(playerid, px, py, pz);
	GetPlayerFacingAngle(playerid, pa);

	PlayerVehicle[id][pVehPos][0] = px;
	PlayerVehicle[id][pVehPos][1] = py;
	PlayerVehicle[id][pVehPos][2] = pz;
	PlayerVehicle[id][pVehPos][3] = pa;

	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengeluarkan kendaraan tersebut!");

	OnPlayerVehicleRespawn(id);

	AccountData[playerid][pTempValue] = -1;
	return 1;
}

Dialog:AdmSetNameOrigin(playerid, response, listitem, inputtext[])
{
	if (!response)
	{
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		static originstring[3528+1];
		for(new x; x < sizeof(_g_originName); x++)
		{
			format(originstring, sizeof(originstring), "%s%s\n", originstring, _g_originName[x]);
		}
		return Dialog_Show(playerid, "AdmSetNameOrigin", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Negara Kelahiran", originstring, "Pilih", "");
	}

	if(listitem == -1 || listitem > sizeof(_g_originName) - 1)
	{
		static originstring[3528+1];
		for(new x; x < sizeof(_g_originName); x++)
		{
			format(originstring, sizeof(originstring), "%s%s\n", originstring, _g_originName[x]);
		}
		return Dialog_Show(playerid, "AdmSetNameOrigin", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Negara Kelahiran", originstring, "Pilih", "");
	}

	if (!IsPlayerConnected(AccountData[playerid][pTempSQLFactMemberID])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	
	strcopy(AccountData[AccountData[playerid][pTempSQLFactMemberID]][pOrigin], _g_originName[listitem]);
	
	new query[128];
	mysql_format(g_SQL, query, sizeof(query), "UPDATE `player_characters` SET `Char_Origin`='%e' WHERE `pID`=%d", AccountData[AccountData[playerid][pTempSQLFactMemberID]][pOrigin], AccountData[AccountData[playerid][pTempSQLFactMemberID]][pID]);
	mysql_pquery(g_SQL, query);

	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Perubahan nama telah berhasil dilakukan.");
	ShowTDN(AccountData[playerid][pTempSQLFactMemberID], NOTIFICATION_WARNING, "Nama karakter anda telah diganti oleh admin.");

	AccountData[playerid][pTempSQLFactMemberID] = INVALID_PLAYER_ID;
	return 1;
}

Dialog:KonserList(playerid, response, listitem, inputtext[]) 
{
	if(!response) return 1;

	switch(listitem)
	{
		case 0:
		{
			GM[KonserStarted] = true;
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Konser dimulai!");
		}
		case 1:
		{
			GM[KonserStarted] = false;
			foreach(new i : Player) if(IsPlayerInDynamicArea(i, KonserMusicZone))
			{
				StopAudioStreamForPlayer(i);
			}
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Konser dimulai!");
		}
		case 2:
		{
			GM[KonserStarted] = true;
			strcopy(GM[KonserMusicLink], "http://103.178.153.173/dewa/siti_nurbaya.mp3");
			foreach(new i : Player) if(IsPlayerInDynamicArea(i, KonserMusicZone))
			{
				PlayAudioStreamForPlayer(i, "http://103.178.153.173/dewa/siti_nurbaya.mp3");
			}
		}
		case 3:
		{
			GM[KonserStarted] = true;
			strcopy(GM[KonserMusicLink], "http://103.178.153.173/dewa/separuh_nafas.mp3");
			foreach(new i : Player) if(IsPlayerInDynamicArea(i, KonserMusicZone))
			{
				PlayAudioStreamForPlayer(i, "http://103.178.153.173/dewa/separuh_nafas.mp3");
			}
		}
		case 4:
		{
			GM[KonserStarted] = true;
			strcopy(GM[KonserMusicLink], "http://103.178.153.173/dewa/selir_hati.mp3");
			foreach(new i : Player) if(IsPlayerInDynamicArea(i, KonserMusicZone))
			{
				PlayAudioStreamForPlayer(i, "http://103.178.153.173/dewa/selir_hati.mp3");
			}
		}
		case 5:
		{
			GM[KonserStarted] = true;
			strcopy(GM[KonserMusicLink], "http://103.178.153.173/dewa/selimut_hati.mp3");
			foreach(new i : Player) if(IsPlayerInDynamicArea(i, KonserMusicZone))
			{
				PlayAudioStreamForPlayer(i, "http://103.178.153.173/dewa/selimut_hati.mp3");
			}
		}
		case 6:
		{
			GM[KonserStarted] = true;
			strcopy(GM[KonserMusicLink], "http://103.178.153.173/dewa/sedang_ingin.mp3");
			foreach(new i : Player) if(IsPlayerInDynamicArea(i, KonserMusicZone))
			{
				PlayAudioStreamForPlayer(i, "http://103.178.153.173/dewa/sedang_ingin.mp3");
			}
		}
		case 7:
		{
			GM[KonserStarted] = true;
			strcopy(GM[KonserMusicLink], "http://103.178.153.173/dewa/roman_picisan.mp3");
			foreach(new i : Player) if(IsPlayerInDynamicArea(i, KonserMusicZone))
			{
				PlayAudioStreamForPlayer(i, "http://103.178.153.173/dewa/roman_picisan.mp3");
			}
		}
		case 8:
		{
			GM[KonserStarted] = true;
			strcopy(GM[KonserMusicLink], "http://103.178.153.173/dewa/risalah_hati.mp3");
			foreach(new i : Player) if(IsPlayerInDynamicArea(i, KonserMusicZone))
			{
				PlayAudioStreamForPlayer(i, "http://103.178.153.173/dewa/risalah_hati.mp3");
			}
		}
		case 9:
		{
			GM[KonserStarted] = true;
			strcopy(GM[KonserMusicLink], "http://103.178.153.173/dewa/pupus.mp3");
			foreach(new i : Player) if(IsPlayerInDynamicArea(i, KonserMusicZone))
			{
				PlayAudioStreamForPlayer(i, "http://103.178.153.173/dewa/pupus.mp3");
			}
		}
		case 10:
		{
			GM[KonserStarted] = true;
			strcopy(GM[KonserMusicLink], "http://103.178.153.173/dewa/perempuan_pcdni.mp3");
			foreach(new i : Player) if(IsPlayerInDynamicArea(i, KonserMusicZone))
			{
				PlayAudioStreamForPlayer(i, "http://103.178.153.173/dewa/perempuan_pcdni.mp3");
			}
		}
		case 11:
		{
			GM[KonserStarted] = true;
			strcopy(GM[KonserMusicLink], "http://103.178.153.173/dewa/pangeran_cinta.mp3");
			foreach(new i : Player) if(IsPlayerInDynamicArea(i, KonserMusicZone))
			{
				PlayAudioStreamForPlayer(i, "http://103.178.153.173/dewa/pangeran_cinta.mp3");
			}
		}
		case 12:
		{
			GM[KonserStarted] = true;
			strcopy(GM[KonserMusicLink], "http://103.178.153.173/dewa/munajat_cinta.mp3");
			foreach(new i : Player) if(IsPlayerInDynamicArea(i, KonserMusicZone))
			{
				PlayAudioStreamForPlayer(i, "http://103.178.153.173/dewa/munajat_cinta.mp3");
			}
		}
		case 13:
		{
			GM[KonserStarted] = true;
			strcopy(GM[KonserMusicLink], "http://103.178.153.173/dewa/madu_tiga.mp3");
			foreach(new i : Player) if(IsPlayerInDynamicArea(i, KonserMusicZone))
			{
				PlayAudioStreamForPlayer(i, "http://103.178.153.173/dewa/madu_tiga.mp3");
			}
		}
		case 14:
		{
			GM[KonserStarted] = true;
			strcopy(GM[KonserMusicLink], "http://103.178.153.173/dewa/laskar_cinta.mp3");
			foreach(new i : Player) if(IsPlayerInDynamicArea(i, KonserMusicZone))
			{
				PlayAudioStreamForPlayer(i, "http://103.178.153.173/dewa/laskar_cinta.mp3");
			}
		}
		case 15:
		{
			GM[KonserStarted] = true;
			strcopy(GM[KonserMusicLink], "http://103.178.153.173/dewa/kirana.mp3");
			foreach(new i : Player) if(IsPlayerInDynamicArea(i, KonserMusicZone))
			{
				PlayAudioStreamForPlayer(i, "http://103.178.153.173/dewa/kirana.mp3");
			}
		}
		case 16:
		{
			GM[KonserStarted] = true;
			strcopy(GM[KonserMusicLink], "http://103.178.153.173/dewa/kangen.mp3");
			foreach(new i : Player) if(IsPlayerInDynamicArea(i, KonserMusicZone))
			{
				PlayAudioStreamForPlayer(i, "http://103.178.153.173/dewa/kangen.mp3");
			}
		}
		case 17:
		{
			GM[KonserStarted] = true;
			strcopy(GM[KonserMusicLink], "http://103.178.153.173/dewa/kamulah_surgaku.mp3");
			foreach(new i : Player) if(IsPlayerInDynamicArea(i, KonserMusicZone))
			{
				PlayAudioStreamForPlayer(i, "http://103.178.153.173/dewa/kamulah_surgaku.mp3");
			}
		}
		case 18:
		{
			GM[KonserStarted] = true;
			strcopy(GM[KonserMusicLink], "http://103.178.153.173/dewa/kamulah_satu.mp3");
			foreach(new i : Player) if(IsPlayerInDynamicArea(i, KonserMusicZone))
			{
				PlayAudioStreamForPlayer(i, "http://103.178.153.173/dewa/kamulah_satu.mp3");
			}
		}
		case 19:
		{
			GM[KonserStarted] = true;
			strcopy(GM[KonserMusicLink], "http://103.178.153.173/dewa/elang.mp3");
			foreach(new i : Player) if(IsPlayerInDynamicArea(i, KonserMusicZone))
			{
				PlayAudioStreamForPlayer(i, "http://103.178.153.173/dewa/elang.mp3");
			}
		}
		case 20:
		{
			GM[KonserStarted] = true;
			strcopy(GM[KonserMusicLink], "http://103.178.153.173/dewa/dewi.mp3");
			foreach(new i : Player) if(IsPlayerInDynamicArea(i, KonserMusicZone))
			{
				PlayAudioStreamForPlayer(i, "http://103.178.153.173/dewa/dewi.mp3");
			}
		}
		case 21:
		{
			GM[KonserStarted] = true;
			strcopy(GM[KonserMusicLink], "http://103.178.153.173/dewa/angin.mp3");
			foreach(new i : Player) if(IsPlayerInDynamicArea(i, KonserMusicZone))
			{
				PlayAudioStreamForPlayer(i, "http://103.178.153.173/dewa/angin.mp3");
			}
		}
		case 22:
		{
			GM[KonserStarted] = true;
			strcopy(GM[KonserMusicLink], "http://103.178.153.173/dewa/aku_milikmu.mp3");
			foreach(new i : Player) if(IsPlayerInDynamicArea(i, KonserMusicZone))
			{
				PlayAudioStreamForPlayer(i, "http://103.178.153.173/dewa/aku_milikmu.mp3");
			}
		}
	}
	return 1;
}