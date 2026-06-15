forward LoadCharacterData(playerid);
public LoadCharacterData(playerid)
{
	static jadmn[MAX_PLAYER_NAME], jrson[60], dtag[41], 
	regdate[50], lastlogin[50], string[168], tempname[25], tmporigin[32], tmpucp[22];
	if(cache_num_rows() > 0)
	{
		AccountData[playerid][IsLoggedIn] = true;
		
		cache_get_value_name_int(0, "pID", AccountData[playerid][pID]);

		cache_get_value_name(0, "Char_RegisterDate", regdate);
		strcopy(AccountData[playerid][pRegisterDate], regdate);
		cache_get_value_name(0, "Char_LastLogin", lastlogin);
		strcopy(AccountData[playerid][pLastLogin], lastlogin);

		cache_get_value_name_int(0, "Char_SSN", AccountData[playerid][pSSN]);

		cache_get_value_name(0, "Char_Name", tempname);
		strcopy(AccountData[playerid][pName], tempname);

		cache_get_value_name(0, "Char_DonatorTag", dtag);
		strcopy(DonatorData[playerid][pDTag], dtag);
		cache_get_value_name_int(0, "Char_Apprentice", AccountData[playerid][pApprentice]);
		cache_get_value_name_int(0, "Char_Steward", AccountData[playerid][pSteward]);
		cache_get_value_name_int(0, "Char_StewTime", AccountData[playerid][pStewardTime]);

		cache_get_value_name_int(0, "Char_VIP", AccountData[playerid][pVIP]);
		cache_get_value_name_int(0, "Char_VIPTime", AccountData[playerid][pVIPTime]);

		cache_get_value_name_int(0, "Char_DirtyMoney", AccountData[playerid][pDirtyMoney]);
		cache_get_value_name_int(0, "Char_Money", AccountData[playerid][pMoney]);
		cache_get_value_name_int(0, "Char_BankMoney", AccountData[playerid][pBankMoney]);
		cache_get_value_name_int(0, "Char_BankNumber", AccountData[playerid][pBankNumber]);
		cache_get_value_name_int(0, "Char_CasinoChip", AccountData[playerid][pCasinoChip]);

		cache_get_value_name_float(0, "Char_PosX", AccountData[playerid][pPos][0]);
		cache_get_value_name_float(0, "Char_PosY", AccountData[playerid][pPos][1]);
		cache_get_value_name_float(0, "Char_PosZ", AccountData[playerid][pPos][2]);
		cache_get_value_name_float(0, "Char_PosA", AccountData[playerid][pPos][3]);

		cache_get_value_name_float(0, "Char_Health", AccountData[playerid][pHealth]);
		cache_get_value_name_float(0, "Char_Armor", AccountData[playerid][pArmor]);

		cache_get_value_name_int(0, "Char_WID", AccountData[playerid][pWorld]);
		cache_get_value_name_int(0, "Char_IntID", AccountData[playerid][pInterior]);

		cache_get_value_name_int(0, "Char_Age", AccountData[playerid][pAge]);

		cache_get_value_name(0, "Char_Origin", tmporigin);
		strcopy(AccountData[playerid][pOrigin], tmporigin);
		cache_get_value_name_int(0, "Char_Gender", AccountData[playerid][pGender]);
		cache_get_value_name_int(0, "Char_BodyHeight", AccountData[playerid][pBodyHeight]);
		cache_get_value_name_int(0, "Char_BodyWeight", AccountData[playerid][pBodyWeight]);
		cache_get_value_name_int(0, "Char_Skin", AccountData[playerid][pSkin]);

		cache_get_value_name_int(0, "Char_Level", AccountData[playerid][pLevel]);
		cache_get_value_name_int(0, "Char_Uniform", AccountData[playerid][pUniform]);
		cache_get_value_name_int(0, "Char_Job", AccountData[playerid][pJob]);
		cache_get_value_name_int(0, "Char_FightStyle", AccountData[playerid][pFightingStyle]);

		cache_get_value_name_int(0, "Char_InDoor", AccountData[playerid][pInDoor]);
		cache_get_value_name_int(0, "Char_InHouse", AccountData[playerid][pInHouse]);
		cache_get_value_name_int(0, "Char_InBiz", AccountData[playerid][pInBiz]);
		cache_get_value_name_int(0, "Char_InRusun", AccountData[playerid][pInRusun]);

		cache_get_value_name_int(0, "Char_Hunger", AccountData[playerid][pHunger]);
		cache_get_value_name_int(0, "Char_Thirst", AccountData[playerid][pThirst]);
		cache_get_value_name_int(0, "Char_Stress", AccountData[playerid][pStress]);

		cache_get_value_name_int(0, "Char_Faction", AccountData[playerid][pFaction]);
		cache_get_value_name_int(0, "Char_FactionRank", AccountData[playerid][pFactionRank]);
		cache_get_value_name_int(0, "Char_Badge", AccountData[playerid][pBadge]);

		cache_get_value_name_int(0, "Char_OnDuty", AccountData[playerid][pOnDuty]);
		cache_get_value_name_int(0, "Char_UsingUniform", AccountData[playerid][pIsUsingUniform]);

		cache_get_value_name_int(0, "Char_Family", AccountData[playerid][pFamily]);
		cache_get_value_name_int(0, "Char_FamilyRank", AccountData[playerid][pFamilyRank]);

		//get jail data
		cache_get_value_name_int(0, "Char_Jailed", OJailData[playerid][jailed]);
		cache_get_value_name_int(0, "Char_JailCell", OJailData[playerid][jailCell]);

		cache_get_value_name(0, "Char_JailAdmin", jadmn);
		strcopy(OJailData[playerid][jailAdmin], jadmn);

		cache_get_value_name_int(0, "Char_JailTime", OJailData[playerid][jailTime]);
		cache_get_value_name_int(0, "Char_JailDur", OJailData[playerid][jailDur]);

		cache_get_value_name(0, "Char_JailReason", jrson);
		strcopy(OJailData[playerid][jailReason], jrson);

		cache_get_value_name_int(0, "Char_JailFine", OJailData[playerid][jailFine]);

		cache_get_value_name_int(0, "Char_Arrest", AccountData[playerid][pArrested]);
		cache_get_value_name_int(0, "Char_ArrestTime", AccountData[playerid][pArrestTime]);

		cache_get_value_name_int(0, "Char_ComServing", AccountData[playerid][pHowMuchComServing]);

		cache_get_value_name_int(0, "Char_Warn", AccountData[playerid][pWarn]);

		cache_get_value_name_int(0, "Char_TogPM", ToggleInfo[playerid][TogPM]);
		cache_get_value_name_int(0, "Char_TogGOOC", ToggleInfo[playerid][TogGOOC]);
		cache_get_value_name_int(0, "Char_TogLogin", ToggleInfo[playerid][TogLogin]);
		cache_get_value_name_int(0, "Char_TogLevel", ToggleInfo[playerid][TogLevel]);
		cache_get_value_name_int(0, "Char_TogAdv", ToggleInfo[playerid][TogAdv]);
		cache_get_value_name_int(0, "Char_TogAdmCmd", ToggleInfo[playerid][TogAdmCmd]);

		cache_get_value_name_int(0, "Char_XmasGiftTime", AccountData[playerid][pXmasGiftTime]);

		cache_get_value_name_float(0, "Char_RenderSetting", AccountData[playerid][pRenderSetting]);

		cache_get_value_name_int(0, "Char_KTP", AccountData[playerid][pHasKTP]);
		cache_get_value_name_int(0, "Char_KTPTime", AccountData[playerid][pKTPTime]);
		cache_get_value_name_int(0, "Char_Radio", PlayerVoiceData[playerid][pHasRadio]);
		cache_get_value_name_int(0, "Char_Earphone", AccountData[playerid][pEarphone]);
		cache_get_value_name_int(0, "Char_Boombox", AccountData[playerid][pBoombox]);
		cache_get_value_name_int(0, "Char_HuntingRifle", AccountData[playerid][pHasHuntingRifle]);

		cache_get_value_name_int(0, "Char_HasGudangID", AccountData[playerid][pHasGudangID]);
		cache_get_value_name_int(0, "Char_GudangRentTime", AccountData[playerid][pGudangRentTime]);

		cache_get_value_name_int(0, "Char_Knockdown", AccountData[playerid][pKnockdown]);
		cache_get_value_name_int(0, "Char_KnockdownTime", AccountData[playerid][pKnockdownTime]);
		
		cache_get_value_name_int(0, "Char_GVL1Lic", AccountData[playerid][pGVL1Lic]);
		cache_get_value_name_int(0, "Char_GVL1LicTime", AccountData[playerid][pGVL1LicTime]);

		cache_get_value_name_int(0, "Char_GVL2Lic", AccountData[playerid][pGVL2Lic]);
		cache_get_value_name_int(0, "Char_GVL2LicTime", AccountData[playerid][pGVL2LicTime]);

		cache_get_value_name_int(0, "Char_MBLic", AccountData[playerid][pMBLic]);
		cache_get_value_name_int(0, "Char_MBLicTime", AccountData[playerid][pMBLicTime]);
		
		cache_get_value_name_int(0, "Char_BLic", AccountData[playerid][pBLic]);
		cache_get_value_name_int(0, "Char_BLicTime", AccountData[playerid][pBLicTime]);

		cache_get_value_name_int(0, "Char_Air1Lic", AccountData[playerid][pAir1Lic]);
		cache_get_value_name_int(0, "Char_Air1LicTime", AccountData[playerid][pAir1LicTime]);

		cache_get_value_name_int(0, "Char_Air2Lic", AccountData[playerid][pAir2Lic]);
		cache_get_value_name_int(0, "Char_Air2LicTime", AccountData[playerid][pAir2LicTime]);

		cache_get_value_name_int(0, "Char_FirearmLic", AccountData[playerid][pFirearmLic]);
		cache_get_value_name_int(0, "Char_FirearmLicTime", AccountData[playerid][pFirearmLicTime]);

		cache_get_value_name_int(0, "Char_HuntingLic", AccountData[playerid][pHuntingLic]);
		cache_get_value_name_int(0, "Char_HuntingLicTime", AccountData[playerid][pHuntingLicTime]);

		cache_get_value_name_int(0, "Char_MowingDelay", AccountData[playerid][pMowingSidejobDelay]);
		cache_get_value_name_int(0, "Char_SweeperDelay", AccountData[playerid][pSweeperSidejobDelay]);
		cache_get_value_name_int(0, "Char_ForkliftDelay", AccountData[playerid][pForkliftSidejobDelay]);
		cache_get_value_name_int(0, "Char_TrashCollectorDelay", AccountData[playerid][pTrashCollectorDelay]);
		cache_get_value_name_int(0, "Char_PizzaDelay", AccountData[playerid][pPizzaSidejobDelay]);
		cache_get_value_name_int(0, "Char_TaxMinute", AccountData[playerid][pTaxMinute]);

		cache_get_value_name_int(0, "Char_HouseSharedID", AccountData[playerid][pHouseSharedID]);
		
		cache_get_value_name_int(0, "Char_TutorialPassed", AccountData[playerid][pTutorialPassed]);
		cache_get_value_name_int(0, "Char_Hours", AccountData[playerid][pHours]);
		cache_get_value_name_int(0, "Char_Minutes", AccountData[playerid][pMinutes]);
		cache_get_value_name_int(0, "Char_Seconds", AccountData[playerid][pSeconds]);
		cache_get_value_name_int(0, "Char_SlipSalary", AccountData[playerid][pSlipSalary]);
		cache_get_value_name_int(0, "Char_WaterInBucket", AccountData[playerid][pWaterInBucket]);

		cache_get_value_name(0, "Char_UCP", tmpucp);
		strcopy(AccountData[playerid][pUCP], tmpucp);

		mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `inventory` WHERE `Owner_ID` = %d LIMIT %d", AccountData[playerid][pID], MAX_INVENTORY);
		mysql_pquery(g_SQL, string, "LoadPlayerItems", "i", playerid);

		mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `player_weapons` WHERE `Owner_ID` = %d LIMIT 1", AccountData[playerid][pID]);
		mysql_pquery(g_SQL, string, "LoadPlayerWeapons", "i", playerid);

		mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `gudang_brankas` WHERE `Owner` = %d LIMIT %d", AccountData[playerid][pID], MAX_GUDANG_ITEMS);
		mysql_pquery(g_SQL, string, "LoadGudangBrankas", "i", playerid);

		mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `rusun_brankas` WHERE `Owner` = %d LIMIT %d", AccountData[playerid][pID], MAX_RUSUN_ITEMS);
		mysql_pquery(g_SQL, string, "LoadRusunBrankas", "i", playerid);

		mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `house_brankas` WHERE `Owner` = %d LIMIT %d", AccountData[playerid][pID], MAX_HOUSE_ITEMS);
		mysql_pquery(g_SQL, string, "LoadHouseBrankas", "i", playerid);

		mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `invoices` WHERE `Owner` = %d LIMIT %d", AccountData[playerid][pID], MAX_INVOICES);
		mysql_pquery(g_SQL, string, "LoadPlayerInvoices", "i", playerid);

		mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `player_warns` WHERE `Owner_ID` = %d LIMIT 100", AccountData[playerid][pID]);
		mysql_pquery(g_SQL, string, "LoadPlayerWarns", "i", playerid);

		mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `player_phones` WHERE `phoneOwner` = %d LIMIT 1", AccountData[playerid][pID]);
		mysql_pquery(g_SQL, string, "LoadPlayerPhone", "i", playerid);

		mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `phone_contacts` WHERE `contactOwnerID` = %d LIMIT %d", AccountData[playerid][pID], MAX_CONTACTS);
		mysql_pquery(g_SQL, string, "LoadPlayerContact", "i", playerid);

		mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `documents` WHERE `Owner_ID` = %d", AccountData[playerid][pID]);
		mysql_pquery(g_SQL, string, "LoadPlayerDocuments", "i", playerid);

		EditingWeapon[playerid] = 0;

		mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `gunpos` WHERE `Owner` = %d LIMIT 1", AccountData[playerid][pID]);
		mysql_pquery(g_SQL, string, "OnWeaponsLoaded", "d", playerid);
		
		Streamer_SetRadiusMultiplier(STREAMER_TYPE_OBJECT, AccountData[playerid][pRenderSetting], playerid);
		SetPlayerName(playerid, AccountData[playerid][pName]);

		//CallLocalFunction("PlayerLoginLog", "i", playerid);

		if(AccountData[playerid][pHealth] < 5.0) AccountData[playerid][pHealth] = 100.00;

		mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `player_clothes` WHERE `Owner`=%d", AccountData[playerid][pID]);
		mysql_pquery(g_SQL, string, "LoadPlayerClothes", "i", playerid);

		mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `player_toys` WHERE `Owner`='%e' LIMIT 1", AccountData[playerid][pName]);
		mysql_pquery(g_SQL, string, "LoadPlayerFashion", "i", playerid);
		
		mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `avtreasure` WHERE `Owner_ID` = %d LIMIT 1", AccountData[playerid][pID]);
		mysql_pquery(g_SQL, string, "LoadPlayerAVTreasure", "i", playerid);

		/*
		static fileName[144];
		format(fileName, sizeof(fileName), "PlayerEvent/%d.ini", AccountData[playerid][pID]);
		if(!dini_Exists(fileName))
		{
            dini_Create(fileName);
			dini_IntSet(fileName, "Pumpkin", 0);
		}
		else
		{
			AccountData[playerid][pPumpkins] = dini_Int(fileName, "Pumpkin");
		}
		*/
		
		RefreshMapJob(playerid);
		
		GetPlayerCountry(playerid, AccountData[playerid][pCountry], MAX_COUNTRY_LENGTH);
		GetPlayerCity(playerid, AccountData[playerid][pCity], MAX_CITY_LENGTH);
		
		SetPlayerFightingStyle(playerid, AccountData[playerid][pFightingStyle]);
		
		foreach(new i : Player)
		{
			if(ToggleInfo[i][TogLogin] && AccountData[i][pSpawned])
			{
				SendClientMessageEx(i, X11_GREY, "** %s[%d] telah terkoneksi ke dalam server (%s, %s).", AccountData[playerid][pName], playerid, AccountData[playerid][pCity], AccountData[playerid][pCountry]);
			}
		}

		if(AccountData[playerid][pFaction] != FACTION_NONE) //jika anggota fraksi
		{
			mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `demand_vehicles` WHERE `ownerid` = %d LIMIT 1", AccountData[playerid][pID]);
			mysql_pquery(g_SQL, string, "LoadPlayerFactVeh", "i", playerid);
		}
		else //jika bukan anggota fraksi
		{
			for(new x; x < MAX_FACTIONS; x++)
			{
				DestroyVehicle(PlayerFactionVehicle[playerid][x]);
			}
			LSPDPlayerCallsign[playerid][0] = EOS;

			mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `demand_vehicles` WHERE `ownerid` = %d", AccountData[playerid][pID]);
			mysql_pquery(g_SQL, string);
		}

		AVC_PConnected[playerid] = true;

		// Select Spawn System
		SpawnPlayerAtLocation(playerid, PlayerSelectSpawnTD[playerid]);

		mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `player_vehicles` WHERE `PVeh_Owner` = %d", AccountData[playerid][pID]);
		mysql_pquery(g_SQL, string, "LoadPlayerVehicle", "i", playerid);
	}
	else
	{
		Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Problem", 
		"Karkater anda tidak dapat kami temukan, database error!", "Tutup", "");
		KickEx(playerid);
	}
    return 1;
}

forward LoadCharacter(playerid);
public LoadCharacter(playerid) //jika sudah berhasil memasukkan password maka karakter list akan ditampilkan
{
    // 1. TAMBAHKAN DEKLARASI VARIABEL QUERY
    new query[512]; 

    PlayerUID[playerid] = 0;
    PlayerUCP[playerid][0] = EOS;
    PlayerUCPVipStatus[playerid][0] = EOS;
    PlayerUCPVipTime[playerid] = 0;
    PlayerUCPGold[playerid] = 0;

    if (cache_num_rows() > 0)
    {
        // 2. UBAH 'i' MENJADI '0' (Karena hanya membaca baris pertama dari data UCP)
        cache_get_value_name_int(0, "ID", PlayerUID[playerid]);
        cache_get_value_name(0, "UCP", PlayerUCP[playerid]);
        cache_get_value_name(0, "vip_status", PlayerUCPVipStatus[playerid]);
        cache_get_value_name_int(0, "vip_time", PlayerUCPVipTime[playerid]);
        cache_get_value_name_int(0, "gold", PlayerUCPGold[playerid]);
    }

    // Query yang sudah di-update dengan DATE_FORMAT
	mysql_format(g_SQL, query, sizeof(query), "SELECT `pID`, DATE_FORMAT(`Char_LastLogin`, '%%d-%%m-%%Y_%%H:%%i:%%s') AS `Char_LastLogin`, UNIX_TIMESTAMP(`Char_LastLogin`) AS `unix_login`, `Char_Name`, `Char_Level`, `Char_Money`, `Char_BankMoney`, `Char_Skin`, `Char_PosX`, `Char_PosY`, `Char_PosZ`, `Char_PosA` FROM `player_characters` WHERE `Char_UCP` = '%e' LIMIT %d", AccountData[playerid][pUCP], MAX_CHARS);
    mysql_pquery(g_SQL, query, "LoadCharacter2", "i", playerid);
    
    return 1;
}

forward LoadCharacter2(playerid);
public LoadCharacter2(playerid)
{
    if (cache_num_rows() < 1)
    {
        Dialog_Show(playerid, "DialogUnused", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Tidak Ada Karakter!", "Harap buat karakter baru di: {FFFF00}https://ucp.pahlawanroleplay.my.id", "Tutup", "");
        KickEx(playerid);
        return 1;
    }

    // ===============================================
    // LOOP RESET VARIABEL
    // ===============================================
    for (new i = 0; i < MAX_CHARS; i ++)
    {
        PlayerCharID[playerid][i] = 0;
        PlayerChar[playerid][i][0] = EOS;
        PlayerCharLevel[playerid][i] = 1;
        PlayerCharCash[playerid][i] = 0;
        PlayerCharBank[playerid][i] = 0;
        PlayerCharSkin[playerid][i] = 0;
        PlayerCharLastLogin[playerid][i][0] = EOS;
        
        PlayerCharLastLoginUnix[playerid][i] = 0; // <-- BARU: Reset variabel UNIX
        
        PlayerSelectCharTD[playerid] = 0;
        PlayerCharLastSpawnX[playerid][i] = 0.0;
        PlayerCharLastSpawnY[playerid][i] = 0.0;
        PlayerCharLastSpawnZ[playerid][i] = 0.0;
        PlayerCharLastSpawnA[playerid][i] = 0.0;
    }

    // ===============================================
    // LOOP PENGAMBILAN DATA
    // ===============================================
    for (new i = 0; i < cache_num_rows(); i ++)
    {
        cache_get_value_name_int(i, "pID", PlayerCharID[playerid][i]);
        cache_get_value_name(i, "Char_Name", PlayerChar[playerid][i]);
        cache_get_value_name_int(i, "Char_Level", PlayerCharLevel[playerid][i]);
        cache_get_value_name_int(i, "Char_Money", PlayerCharCash[playerid][i]);
        cache_get_value_name_int(i, "Char_BankMoney", PlayerCharBank[playerid][i]);
        cache_get_value_name_int(i, "Char_Skin", PlayerCharSkin[playerid][i]);
        
        // Panggil teks VARCHAR asli untuk TextDraw
        cache_get_value_name(i, "Char_LastLogin", PlayerCharLastLogin[playerid][i]); 
        // Panggil alias 'unix_login' untuk sistem (Integer)
        cache_get_value_name_int(i, "unix_login", PlayerCharLastLoginUnix[playerid][i]); 

        cache_get_value_name_float(i, "Char_PosX", PlayerCharLastSpawnX[playerid][i]);
        cache_get_value_name_float(i, "Char_PosY", PlayerCharLastSpawnY[playerid][i]);
        cache_get_value_name_float(i, "Char_PosZ", PlayerCharLastSpawnZ[playerid][i]);
        cache_get_value_name_float(i, "Char_PosA", PlayerCharLastSpawnA[playerid][i]);
    }

    StopLoginTimeout(playerid);

	for (new i = 0; i < 15; i ++)
    {
        SendClientMessage(playerid, X11_WHITE, "");
    }

	StartLoginLobbyTransition(playerid);

	//ShowCharacterList(playerid);
    return 1;
}

StartLoginLobbyTransition(playerid)
{
	if(pLoginTransitionTimer[playerid] != -1)
	{
		KillTimer(pLoginTransitionTimer[playerid]);
		pLoginTransitionTimer[playerid] = -1;
	}

	CancelSelectTextDraw(playerid);
	HideLoginScreenTD(playerid);
	HideThurXProjectTD(playerid);
	ShowThurXProjectTD(playerid);
	EnterCharacterLobby(playerid);

	pLoginTransitionTimer[playerid] = SetTimerEx("OnLoginLobbyTransitionDone", 3000, false, "i", playerid);
	return 1;
}

forward OnLoginLobbyTransitionDone(playerid);
public OnLoginLobbyTransitionDone(playerid)
{
	pLoginTransitionTimer[playerid] = -1;

	if(!IsPlayerConnected(playerid))
		return 0;

	HideThurXProjectTD(playerid);
	OnLoadLobbyRoom(playerid, LobbyVirtualWorld[playerid]);
	return 1;
}

EnterCharacterLobby(playerid)
{
	new vw = playerid + 1000;

	InCharSelection[playerid] = true;
	LobbyVirtualWorld[playerid] = vw;

	SetPlayerVirtualWorld(playerid, vw);
	SetPlayerInterior(playerid, 2);
	SetPlayerPos(playerid, 1855.000000, -1590.000000, 31.000000);
	SetPlayerFacingAngle(playerid, 0.0);
	TogglePlayerControllable(playerid, false);
	CancelSelectTextDraw(playerid);

	LastCharCam[playerid] = PlayerSelectCharTD[playerid];
	SetLobbySelectCharCamera(playerid, PlayerSelectCharTD[playerid]);

	CreateLobbyActor(playerid);
	Streamer_Update(playerid, -1);
	RefreshLobbyActorAnimations(playerid);
	return 1;
}

forward OnLoadLobbyRoom(playerid, vw);
public OnLoadLobbyRoom(playerid, vw)
{
	HideThurXProjectTD(playerid);
	ShowSelectCharTD(playerid, PlayerSelectCharTD[playerid]); //bug
	SelectTextDraw(playerid, 0x191919FF);
	return 1;
}
