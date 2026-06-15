/* Functions */
FixText(text[])
{
    new len = strlen(text);
    if(len > 1)
    {
        for (new i = 0; i < len; i++)
        {
            if(text[i] == 92)
            {
                if(text[i+1] == 'n')
                {
                    text[i] = '\n';
                    for (new j = i+1; j < len; j++) text[j] = text[j+1], text[j+1] = 0;
                    continue;
                }
                if(text[i+1] == 't')
                {
                    text[i] = '\t';
                    for (new j = i+1; j < len-1; j++) text[j] = text[j+1], text[j+1] = 0;
                    continue;
                }
                if(text[i+1] == 92)
                {
                    text[i] = 92;
                    for (new j = i+1; j < len-1; j++) text[j] = text[j+1], text[j+1] = 0;
                }
            }
        }
    }
    return 1;
}

GetName(playerid)
{
	new name[MAX_PLAYER_NAME];
 	GetPlayerName(playerid,name,sizeof(name));
	return name;
}

Database_Connect()
{
	new MySQLOpt: option_id = mysql_init_options();
	mysql_set_option(option_id, POOL_SIZE, 12);
	g_SQL = mysql_connect(DATABASE_ADDRESS, DATABASE_USERNAME, DATABASE_PASSWORD, DATABASE_NAME, option_id);

	if(mysql_errno(g_SQL) != 0)
	{
	    print("[MySQL] Koneksi ke database dinyatakan gagal!");
	}
	else
	{
		print("[MySQL] Koneksi ke database berhasil!");
		AntiDDOSActivate();
	}
}

IsPlayerSpawned(playerid)
{
	new pstate = GetPlayerState(playerid);
	switch(pstate) 
	{
		case PLAYER_STATE_ONFOOT.. PLAYER_STATE_PASSENGER, PLAYER_STATE_SPAWNED: 
		{
			return true;
		}
	}
	return false;
}

IsValidPassword(const name[])
{
	new len = strlen(name);

	for(new ch = 0; ch != len; ch++)
	{
		switch(name[ch])
		{
			case 'A' .. 'Z', 'a' .. 'z', '0' .. '9', ']', '[', '(', ')', '_', '.', '@', '#': continue;
			default: return false;
		}
	}
	return true;
}

IsRoleplayName(const name[]) 
{
    if(!name[0] || strfind(name, "_") == -1)
        return 0;

    else for (new i = 0, len = strlen(name); i != len; i ++) {
    if((i == 0) && (name[i] < 'A' || name[i] > 'Z'))
            return 0;

        else if((i != 0 && i < len  && name[i] == '_') && (name[i + 1] < 'A' || name[i + 1] > 'Z'))
            return 0;

        else if((name[i] < 'A' || name[i] > 'Z') && (name[i] < 'a' || name[i] > 'z') && name[i] != '_' && name[i] != '.')
            return 0;
    }
    return 1;
}

IsValidName(const name[])
{
	new len = strlen(name);

	for(new ch = 0; ch != len; ch++)
	{
		switch(name[ch])
		{
			case 'A' .. 'Z', 'a' .. 'z', '0' .. '9', ']', '[', '(', ')', '_', '.': continue;
			default: return false;
		}
	}
	return true;
}

// GetPlayerPacketLoss(playerid, &Float:packetLoss)
// {
//     /* Returns the packetloss percentage of the given playerid - Made by Fusez */

//     if(!IsPlayerConnected(playerid))
//     {
//         return 0;
//     }

//     new nstats[400+1], nstats_loss[20], start, end;
//     GetPlayerNetworkStats(playerid, nstats, sizeof (nstats));

//     start = strfind(nstats, "Packetloss", true);
//     end = strfind(nstats, "%", true, start);

//     strmid(nstats_loss, nstats, start+12, end, sizeof (nstats_loss));
//     packetLoss = floatstr(nstats_loss);
//     return 1;
// }

Float:GetPlayerPacketLoss(playerid) //the stock
{
	new stats[401], stringstats[70];//those are the variables we will need in the stock
	GetPlayerNetworkStats(playerid, stats, sizeof(stats));//this one will get the net stats
	new len = strfind(stats, "Packetloss: ");//and this one will get the packetloss
	new Float:packetloss = 0.0;//the float for the packetloss
	if(len != -1)
	{
		strmid(stringstats, stats, len, strlen(stats));
		new len2 = strfind(stringstats, "%");
		if(len != -1)
		{
			strdel(stats, 0, strlen(stats));
			strmid(stats, stringstats, len2-3, len2);
			packetloss = floatstr(stats);
		}
	}
	return packetloss;
}

GetPlayerRoleplayName(playerid) 
{
	new
		sz_playerName[MAX_PLAYER_NAME],
		i_pos;

	strcopy(sz_playerName, AccountData[playerid][pName]);
	while ((i_pos = strfind(sz_playerName, "_", false, i_pos)) != -1) sz_playerName[i_pos] = ' ';
	return sz_playerName;
}

GetPlayerRoleplayNameOffline(const nickname[])
{
	new
		sz_playerName[MAX_PLAYER_NAME],
		i_pos;

	strcopy(sz_playerName, nickname);
	while ((i_pos = strfind(sz_playerName, "_", false, i_pos)) != -1) sz_playerName[i_pos] = ' ';
	return sz_playerName;
}

IsUCPLoggedIn(playerid, const name[]) 
{
    foreach(new i : Player) if(i != playerid)
	{
		if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned]) 
		{
			if(!strcmp(AccountData[i][pUCP], name, true))
			{
				return true;
			}
		}
	}
    return false;
}

IsPlayerNearPlayer(playerid, targetid, Float:radius)
{
	static
		Float:fX,
		Float:fY,
		Float:fZ;

	GetPlayerPos(targetid, fX, fY, fZ);

	return (GetPlayerInterior(playerid) == GetPlayerInterior(targetid) && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(targetid)) && IsPlayerInRangeOfPoint(playerid, radius, fX, fY, fZ);
}

IsPlayerNearVehicle(playerid, vehicleid, Float:radius)
{
	static
		Float:fX,
		Float:fY,
		Float:fZ;

	GetVehiclePos(vehicleid, fX, fY, fZ);

	return (GetPlayerInterior(playerid) == VehicleCore[vehicleid][vInterior] && GetPlayerVirtualWorld(playerid) == VehicleCore[vehicleid][vWorld] && IsPlayerInRangeOfPoint(playerid, radius, fX, fY, fZ));
}

ColouredText(const text[])
{
    new
        epos = -1,
        string[144]
    ;
    strmid(string, text, 0, 128, (sizeof(string) - 16));

    while((epos = strfind(string, "#", true, (epos + 1))) != -1)
    {
        new
            i = (epos + 1),
            hexCount
        ;
        for( ; ((string[i] != 0) && (hexCount < 6)); ++i, ++hexCount)
        {
            if(!(('a' <= string[i] <= 'f') || ('A' <= string[i] <= 'F') || ('0' <= string[i] <= '9')))
            {
                    break;
            }
        }
        if((hexCount == 6) && !(hexCount < 6))
        {
            string[epos] = '{';
            strins(string, "}", i);
        }
    }
    return string;
}

SendStaffMessage(color, const str[], {Float,_}:...)
{
    static
        args,
        start,
        end,
        string[144]
    ;
    #emit LOAD.S.pri 8
    #emit STOR.pri args

    if(args > 8)
    {
        #emit ADDR.pri str
        #emit STOR.pri start

        for (end = start + (args - 8); end > start; end -= 4)
        {
            #emit LREF.pri end
            #emit PUSH.pri
        }
        #emit PUSH.S str
        #emit PUSH.C 144
        #emit PUSH.C string

        #emit LOAD.S.pri 8
        #emit ADD.C 4
        #emit PUSH.pri

        #emit SYSREQ.C format
        #emit LCTRL 5
        #emit SCTRL 4

        foreach(new i : Player)
        {
            if((AccountData[i][pAdmin] >= 1 || AccountData[i][pSteward]) && AccountData[i][pSpawned])
            {
                SendClientMessageEx(i, color, "%s", string);
            }
        }
        return 1;
    }
    foreach (new i : Player)
    {
        if((AccountData[i][pAdmin] >= 1 || AccountData[i][pSteward]) && AccountData[i][pSpawned])
        {
            SendClientMessageEx(i, color, "%s", string);
        }
    }
    return 1;
}

SendNearbyMessage(playerid, Float:radius, color, const str[], {Float,_}:...)
{
	static
	    args,
	    start,
	    end,
	    string[144]
	;
	#emit LOAD.S.pri 8
	#emit STOR.pri args

	if (args > 16)
	{
		#emit ADDR.pri str
		#emit STOR.pri start

	    for (end = start + (args - 16); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 144
		#emit PUSH.C string

		#emit LOAD.S.pri 8
		#emit CONST.alt 4
		#emit SUB
		#emit PUSH.pri

		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4

        foreach (new i : Player)
		{
			if (IsPlayerNearPlayer(i, playerid, radius) && AccountData[i][pSpawned])
			{
  				SendClientMessage(i, color, string);
			}
		}
		return 1;
	}
	foreach (new i : Player)
	{
		if (IsPlayerNearPlayer(i, playerid, radius) && AccountData[i][pSpawned])
		{
			SendClientMessage(i, color, str);
		}
	}
	return 1;
}

SendClientMessageToAllEx(color, const text[], {Float, _}:...)
{
    static
        args,
            str[144];

    if((args = numargs()) == 2)
    {
            SendClientMessageToAll(color, text);
    }
    else
    {
        while (--args >= 2)
        {
            #emit LCTRL 5
            #emit LOAD.alt args
            #emit SHL.C.alt 2
            #emit ADD.C 12
            #emit ADD
            #emit LOAD.I
            #emit PUSH.pri
        }
        #emit PUSH.S text
        #emit PUSH.C 144
        #emit PUSH.C str
        #emit LOAD.S.pri 8
        #emit ADD.C 4
        #emit PUSH.pri
        #emit SYSREQ.C format
        #emit LCTRL 5
        #emit SCTRL 4

        SendClientMessageToAll(color, str);

        #emit RETN
    }
    return 1;
}

SendClientMessageEx(playerid, colour, const text[], va_args<>)
{
    new str[144];
    va_format(str, sizeof(str), text, va_start<3>);
    return SendClientMessage(playerid, colour, str);
}

PutPlayerInVehicleEx(playerid, vehid, seat)
{
	if(seat == 0)
	{
		if(!IsVehicleSeatOccupied(vehid,0))
		{
			ValidVehicleDriver[vehid] = playerid;
		}
	}
	SavingVehID[playerid] = vehid;
	EnteringVehID[playerid] = vehid;
	Anticheat[playerid][acImmunity] = gettime() + 5;
	AC_LastStateTime[playerid] = GetTickCount() - 9999;
	return PutPlayerInVehicle(playerid, vehid, seat);
}

DestroyJobVehicle(playerid)
{	
	DestroyVehicle(JobVehicle[playerid]);

	DestroyVehicle(TrailerVehicle[playerid]);

    DestroyVehicle(FactionHeliVeh[playerid]);

    DestroyVehicle(DMVVeh[playerid]);
}

// DestoryPlayerFactObject(playerid)
// {
// 	for(new x; x < 2; x++)
// 	{
// 		if(DestroyDynamicObject(EMSClothing[playerid][x]))
//             EMSClothing[playerid][x] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
// 	}
// }

DestroyFactVehToys(vehicleid)
{
	if(DestroyDynamicObject(UfoObjID[vehicleid][0]))
		UfoObjID[vehicleid][0] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
	
	if(DestroyDynamicObject(UfoObjID[vehicleid][1]))
		UfoObjID[vehicleid][1] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

	if(DestroyDynamic3DTextLabel(FactionVehCallsign[vehicleid]))
		FactionVehCallsign[vehicleid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

	for(new x; x < 5; x++)
	{
		if(DestroyDynamicObject(FactionVehSiren[vehicleid][x]))
			FactionVehSiren[vehicleid][x] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
	}

	for(new x; x < 23; x++)
	{
		if(DestroyDynamicObject(FactionVehObject[vehicleid][x]))
            FactionVehObject[vehicleid][x] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
	}

	for(new x; x < 10; x++)
	{
		if(DestroyDynamicObject(VehicleCore[vehicleid][pizzaBox][x]))
			VehicleCore[vehicleid][pizzaBox][x] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
	}
}

ResetVariables(playerid)
{
	Dialog_Close(playerid);
	
	//timer
	//KillTimer(p_BangunanTimer[playerid]);
    //p_BangunanTimer[playerid] = -1;

	KillTimer(AccountData[playerid][pFooterTimer]);
    AccountData[playerid][pFooterTimer] = -1;

	KillTimer(AccountData[playerid][pKillEffectTimer]);
    AccountData[playerid][pKillEffectTimer] = -1;

	KillTimer(AccountData[playerid][pWarnTDTimer]);
    AccountData[playerid][pWarnTDTimer] = -1;

	KillTimer(pUnfreezeTimer[playerid]);
	pUnfreezeTimer[playerid] = -1;

	pSriMersingCookingTimer[playerid] = false;
	pDNRCookingTimer[playerid] = false;
	pCookingTimer[playerid] = false;
	
	pCookingHouseTimer[playerid] = false;
	pHCraftBandageTimer[playerid] = false;

	pFactionCraftingTimer[playerid] = false;
	pRepairingToolkitTimer[playerid] = false;
	
	pMedisLokalTimer[playerid] = false;
	
    ForkliftLoadTimer[playerid] = false;
    ForkliftUnloadTimer[playerid] = false;

    pDeliveringPizzaTimer[playerid] = false;

	pMakeEfedrinTimer[playerid] = false;
	pMakeStimulanTimer[playerid] = false;
	pMakeMethMentahTimer[playerid] = false;
	pMakeMethTimer[playerid] = false;
	pUsingHeroinTimer[playerid] = false;
	pDrinkingWhiskyTimer[playerid] = false;
	pDrinkingSojuTimer[playerid] = false;
	
	p_BankRTakeMoneyTimer[playerid] = false;

	StopLoginTimeout(playerid);

	if(pLoginTransitionTimer[playerid] != -1)
	{
		KillTimer(pLoginTransitionTimer[playerid]);
		pLoginTransitionTimer[playerid] = -1;
	}

	pAllowSpawn[playerid] = false;
	pLoginSpawnLoaded[playerid] = false;
	
	AccountData[playerid][pCharSelected] = false;

	//pelaut
	SailRute[playerid] = -1;
    SailRouteType[playerid] = 0;
	SailDockTimer[playerid] = false;

	//tailor
	pTakingWoolTimer[playerid] = false;
	pMakingFabricTimer[playerid] = false;
	pClothingTimer[playerid] = false;

	//lumberjack
	pTakeWoodTimer[playerid] = false;
	pCutWoodTimer[playerid] = false;
	pGetBoardTimer[playerid] = false;

	//job farmer
	pTakingPlantTimer[playerid] = false;
	pProcessChiliTimer[playerid] = false;
	pProcessRiceTimer[playerid] = false;
	pPorcessSugarTimer[playerid] = false;
	PlayerFarmerVars[playerid][pDuringTakingPlant] = false;
	PlayerFarmerVars[playerid][pDuringPlantingSeed] = false;

	//job miner
	pTakingStoneTimer[playerid] = false;
	pWashingStoneTimer[playerid] = false;
	pSmeltingStoneTimer[playerid] = false;

	//job butcher
	pTakingChickTimer[playerid] = false;
	pCutingChickTimer[playerid] = false;
	pPackingChickTimer[playerid] = false;

	//job oilman
	pTakingOilTimer[playerid] = false;
	pRefiningOilTimer[playerid] = false;
	pMixingOilTimer[playerid] = false;

	//job angkot
	pAngkotTimer[playerid] = false;

	//job milker
	pTakingSusuTimer[playerid] = false;
	pProcessSusuTimer[playerid] = false;

	//job trucker
	pLoadCargoTimer[playerid] = false;
	PlayerCargoVars[playerid][IsLoadingCargo] = false;
	PlayerCargoVars[playerid][CargoStarted] = false;
	PlayerCargoVars[playerid][CargoDetached] = false;
	PlayerCargoVars[playerid][CargoType] = 0;

	//job porter
	pPorterCarrying[playerid] = false;
	pPorterDropIDX[playerid] = -1;

	pTakingFishTimer[playerid] = false;

	//job supir mixer
	MixerStep[playerid] = -1;
	MixerSlump[playerid] = 0;
	MixerPercent[playerid] = 0;
	pMixerDumpTimer[playerid] = false;
	pMixBetonTimer[playerid] = false;
	pSlumpTimer[playerid] = false;
	SemenInput[playerid] = 0;
	PasirInput[playerid] = 0;
	KrikilAInput[playerid] = 0;
	KrikilBInput[playerid] = 0;
	AirInput[playerid] = 0;

	//server stuff timer
	pIsVaping[playerid] = false;
	AccountData[playerid][pTempChip] = 0;

	TempMoneyLaundry[playerid] = 0;
	TempMoneyLaundryR[playerid] = 0;

	AccountData[playerid][pIsUsingUniform] = false;
	TempFreeCar[playerid] = false;
	
	AccountData[playerid][pBuckledOn] = false;
	
	pInSpecMode[playerid] = 0;
	
	pShortcutResultShown[playerid] = false;
	pVoiceDistanceStatus[playerid] = 1;

	pCurWeap[playerid] = 0;
	AttCheckCurWeapon[playerid] = 0;

	PlayerVoiceData[playerid][pIsCastMicOn] = true;
	
	AntiGZRetard[playerid] = 0;
	
	NudgeVal[playerid] = 0.05;
	AccountData[playerid][pEditModshopStatus] = -1;
	AccountData[playerid][pShowFooter] = false;
	AccountData[playerid][pShowWarnTD] = false;
	AccountData[playerid][pKillEffectTDShown] = false;

	AccountData[playerid][pBlindfolded] = false;

	HBETDHidden[playerid] = false;
	SpawnLocIdx[playerid] = 0;

	pTutorialStep[playerid] = -1;
	
	//cheat
	s_playerWarnings[playerid] = 0;
	
	//KillTimer(BunnyHopTimer[playerid]);
    //BunnyHopTimer[playerid] = -1;

	pTakingTrashTimer[playerid] = false;
	pEatingBarTimer[playerid] = false;
	pOpenBackpackTimer[playerid] = false;

	pOpenShotDeluxeTimer[playerid] = false;
	pOpenBuckshotSpecialTimer[playerid] = false;
	pOpenTelaGoodieTimer[playerid] = false;
	pOpenAndalasPrideTimer[playerid] = false;
	pOpenMinangComboTimer[playerid] = false;
	pOpenMalayaShineTimer[playerid] = false;
	pOpenFreshSolarTimer[playerid] = false;
	pOpenSoftexFlashTimer[playerid] = false;
	pOpenPurpleSweetTimer[playerid] = false;

	pRefuelJerrycanTimer[playerid] = false;
	pRefuelingTimer[playerid] = false;

	pMechRepairEngineTimer[playerid] = false;
	pMechRepairBodyTimer[playerid] = false;
	pMechRepairTiresTimer[playerid] = false;
	pMechUpgradeEngine[playerid] = false;
	pMechUpgradeBody[playerid] = false;

	pUsingPerbanTimer[playerid] = false;
	pUsingPilStressTimer[playerid] = false;

	pUsingKevlarTimer[playerid] = false;

	KillTimer(PlayerPhoneData[playerid][phoneInstallAppTimer]);
	PlayerPhoneData[playerid][phoneInstallAppTimer] = -1;
	
	//activity illegal & non illegal timer
	pCraftingWeaponTimer[playerid] = false;
	pCraftingDrugTimer[playerid] = false;
	pTakingKanabisTimer[playerid] = false;
	pProcessKanabisTimer[playerid] = false;
	pSellingMarijuanaTimer[playerid] = false;

	KillTimer(pCarstealLabelTimer[playerid]);
    pCarstealLabelTimer[playerid] = -1;

	pCarstealPartTimer[playerid] = false;
	pSmokingWeedTimer[playerid] = false;
	pUsingMethTimer[playerid] = false;

	pSellingTurtleTimer[playerid] = false;
	pSellingSharkTimer[playerid] = false;

	pConsfMeatTimer[playerid] = false;

	//faction timer
    pBreakingVehDoorTimer[playerid] = false;
    pImpoundingInsuTimer[playerid] = false;
    pImpoundingSamsatTimer[playerid] = false;

    RevivingPlayerTimer[playerid] = false;

	pTaggingTimer[playerid] = false;

	pKompensasiTimer[playerid] = false;

	pRebootingPhoneTimer[playerid] = false;
	//verify
	tempverify[playerid] = 1;
	temprecovery[playerid] = -1;

	//penyimpanan
	for(new x; x < MAX_GUDANG_ITEMS; x++)
	{
		GudangBrankas[playerid][x][gudangBrankasExists] = false;
		GudangBrankas[playerid][x][gudangBrankasID] = 0;
		GudangBrankas[playerid][x][gudangBrankasOwner] = 0;
		GudangBrankas[playerid][x][gudangBrankasTemp][0] = EOS;
		GudangBrankas[playerid][x][gudangBrankasModel] = 0;
		GudangBrankas[playerid][x][gudangBrankasQuant] = 0;

		RusunBrankas[playerid][x][rusunBrankasExists] = false;
		RusunBrankas[playerid][x][rusunBrankasID] = 0;
		RusunBrankas[playerid][x][rusunBrankasOwner] = 0;
		RusunBrankas[playerid][x][rusunBrankasTemp][0] = EOS;
		RusunBrankas[playerid][x][rusunBrankasModel] = 0;
		RusunBrankas[playerid][x][rusunBrankasQuant] = 0;

		HouseBrankas[playerid][x][houseBrankasExists] = false;
		HouseBrankas[playerid][x][houseBrankasID] = 0;
		HouseBrankas[playerid][x][houseBrankasOwner] = 0;
		HouseBrankas[playerid][x][houseBrankasTemp][0] = EOS;
		HouseBrankas[playerid][x][houseBrankasModel] = 0;
		HouseBrankas[playerid][x][houseBrankasQuant] = 0;
	}

	ResetPlayerWeaponsEx(playerid);
	
	AccountData[playerid][pArrestTime] = 0;
    AccountData[playerid][pArrested] = false;

	OJailData[playerid][jailed] = false;
	OJailData[playerid][jailCell] = -1;
	OJailData[playerid][jailAdmin][0] = EOS;
	OJailData[playerid][jailTime] = 0;
	OJailData[playerid][jailDur] = 0;
	OJailData[playerid][jailReason][0] = EOS;
	OJailData[playerid][jailFine] = 0;

	//blackjack
	for(new x; x < 7; x++)
    {
        PlayerTextDrawDestroy(playerid, BlackJackPTD[playerid][x]);
        BlackJackPTD[playerid][x] = PlayerText: INVALID_PLAYER_TEXT_DRAW;

        PlayerTextDrawDestroy(playerid, DealerBJTD[playerid][x]);
        DealerBJTD[playerid][x] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
    }

    TextDrawHideForPlayer(playerid, BlackJackTD[0]);
    TextDrawHideForPlayer(playerid, BlackJackTD[1]);

    TextDrawHideForPlayer(playerid, BlackJackTD[6]);
    TextDrawHideForPlayer(playerid, BlackJackTD[7]);

    PlayerTextDrawDestroy(playerid, BJTableCardTD[playerid][0]);
    BJTableCardTD[playerid][0] = PlayerText: INVALID_PLAYER_TEXT_DRAW;

    PlayerTextDrawDestroy(playerid, BJTableCardTD[playerid][1]);
    BJTableCardTD[playerid][1] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
	
	PlayerBlackJack[playerid][pInBJTable] = -1;
    PlayerBlackJack[playerid][Forbidden] = false;
    PlayerBlackJack[playerid][HasAce] = false;
    PlayerBlackJack[playerid][BlackJack] = false;
    PlayerBlackJack[playerid][DoubleTaken] = false;
    PlayerBlackJack[playerid][InsuranceTaken] = false;
    PlayerBlackJack[playerid][DealerHasAce] = false;
    PlayerBlackJack[playerid][DealerBlackJack] = false;
    PlayerBlackJack[playerid][Seated] = false;
    PlayerBlackJack[playerid][Bet] = 0;
    PlayerBlackJack[playerid][CardValue] = 0;
    PlayerBlackJack[playerid][pCardsId] = -1;
    PlayerBlackJack[playerid][DealerCardsId] = -1;
    PlayerBlackJack[playerid][DealerCardValue] = 0;
    PlayerBlackJack[playerid][pCountCards] = -1;
	//=======================================
	EditingWeapon[playerid] = 0;

	DeathCause[playerid][Bruised] = false;
	DeathCause[playerid][Shoted] = false;
	DeathCause[playerid][Burns] = false;
	DeathCause[playerid][Drown] = false;
	DeathCause[playerid][Fallen] = false;

	AccountData[playerid][pIsFallFromInterior] = false;
	AccountData[playerid][pLivestreamMode] = false;
	AccountData[playerid][pLivestreamTitle][0] = EOS;

	AccountData[playerid][pHoldingOreType] = 0;
	AccountData[playerid][pHoldingCrateType] = 0;
	AccountData[playerid][pHoldingSledge] = false;
	AccountData[playerid][pFlareUsed] = false;

	AccountData[playerid][pUsingJoint] = false;

	AccountData[playerid][pESharedType] = 0;
	AccountData[playerid][pESharedOfferer] = INVALID_PLAYER_ID;
	AccountData[playerid][pToggleNameID] = false;
	AccountData[playerid][pDuringUseLocalMedic] = false;
	AccountData[playerid][pRaceEventStep] = -1;

	AccountData[playerid][pSkating] = false;
	AccountData[playerid][pHoldingSkate] = false;
	AccountData[playerid][pHoldFlashlight] = false;
	AccountData[playerid][pFlashlightOn] = false;

	AccountData[playerid][pTypeDisphone] = 0;
    AccountData[playerid][pUsedDisphone] = false;
    AccountData[playerid][pWaitingDisphone] = 0;
	
	AccountData[playerid][pAppearance][0] = EOS;
	
	//AccountData[playerid][pRPQuizQuestion] = 0;
	//AccountData[playerid][pRPQuizWrong] = 0;

	AccountData[playerid][pEatingIndexID] = 0;
	AccountData[playerid][pEatingStep] = 0;
	AccountData[playerid][pDrinkingStep] = 0;

	AccountData[playerid][pTortured] = false;
	
	AccountData[playerid][pTempVehIterID] = -1;
	AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
	AccountData[playerid][pAdmin] = 0;

	AccountData[playerid][pAdvertDelay] = 0;

	//afk check
    AccountData[playerid][pIsAFK] = false;
    AccountData[playerid][pAFKCount] = 0;
    AccountData[playerid][pAFKTime] = 0;
    AccountData[playerid][pAFKNumb] = 0;
    AccountData[playerid][afkx] = 0.0;
    AccountData[playerid][afky] = 0.0;
    AccountData[playerid][afkz] = 0.0;

	AccountData[playerid][pEatingDrinking] = false;
	AccountData[playerid][pTempValue] = -1;
	AccountData[playerid][pTempValue2] = -1;
	AccountData[playerid][pDelayKnockdownSignalSent] = 0;
	AccountData[playerid][pTaser] = false;
	AccountData[playerid][pUseBeanbag] = false;

	AccountData[playerid][pStuckRequest] = 0;
    AccountData[playerid][pStuckWaiting] = 0;

	AccountData[playerid][pVersion][0] = EOS;
	
	AccountData[playerid][pVoted] = false;
	
	AccountData[playerid][pInEvent] = false;
	//pBangunanStep[playerid] = 0;
	//pBangunanWorked[playerid] = false;

	Anticheat[playerid][acArmorTime] = 0;
	Anticheat[playerid][acImmunity] = 0;
	
	AccountData[playerid][pACWarns] = 0;
	AccountData[playerid][pHasArmor] = false;
	AccountData[playerid][pArmorEmpty] = true;
	
	SeenPutrideliMenu[playerid] = false;

	DocumentInfo[playerid][BPJS] = false;
	DocumentInfo[playerid][BPJSClass] = 0;
	DocumentInfo[playerid][BPJSDur] = 0;
	DocumentInfo[playerid][BPJSIssuer][0] = EOS;
	DocumentInfo[playerid][BPJSIssuerRank][0] = EOS;
	DocumentInfo[playerid][BPJSIssueDate][0] = EOS;

	DocumentInfo[playerid][SKS] = false;
	DocumentInfo[playerid][SKSDur] = 0;
	DocumentInfo[playerid][SKSText][0] = EOS;
	DocumentInfo[playerid][SKSIssuer][0] = EOS;
	DocumentInfo[playerid][SKSIssuerRank][0] = EOS;
	DocumentInfo[playerid][SKSIssueDate][0] = EOS;

	DocumentInfo[playerid][SKCK] = false;
	DocumentInfo[playerid][SKCKDur] = 0;
	DocumentInfo[playerid][SKCKText][0] = EOS;
	DocumentInfo[playerid][SKCKIssuer][0] = EOS;
	DocumentInfo[playerid][SKCKIssuerRank][0] = EOS;
	DocumentInfo[playerid][SKCKIssueDate][0] = EOS;

	DocumentInfo[playerid][SKWB] = false;
	DocumentInfo[playerid][SKWBDur] = 0;
	DocumentInfo[playerid][SKWBText][0] = EOS;
	DocumentInfo[playerid][SKWBIssuer][0] = EOS;
	DocumentInfo[playerid][SKWBIssuerRank][0] = EOS;
	DocumentInfo[playerid][SKWBIssueDate][0] = EOS;

	DocumentInfo[playerid][SP] = false;
	DocumentInfo[playerid][SPDur] = 0;
	DocumentInfo[playerid][SPText][0] = EOS;
	DocumentInfo[playerid][SPIssuer][0] = EOS;
	DocumentInfo[playerid][SPIssuerRank][0] = EOS;
	DocumentInfo[playerid][SPIssueDate][0] = EOS;

	ResetAllRaceCP(playerid);

	RumusPajakTabungan[playerid] = 0;
	RumusPajakKendaraan[playerid] = 0;

	AccountData[playerid][pMenuShowed] = false;
	
	AccountData[playerid][pTurningEngine] = false;
	
	gPlayerUsingLoopingAnim[playerid] = false;
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

	AccountData[playerid][pIdlingTime] = 0;
    AccountData[playerid][idlex] = 0.0;
    AccountData[playerid][idley] = 0.0;
    AccountData[playerid][idlez] = 0.0;

	DelayShotNotif[playerid] = 0;
	RconAttempt[playerid] = 0;

	AccountData[playerid][AntiBHOP] = 0;
	//BunnyHopDetected[playerid] = false;
	gPlayerAnimLibsPreloaded[playerid] = false;

	IsPlayerHunting[playerid] = false;
	AccountData[playerid][pDuringConsficatingMeat] = -1;

	AVC_PConnected[playerid] = false;
	
	AccountData[playerid][pHiddenAdmin] = false;

	EnteringVehID[playerid] = INVALID_VEHICLE_ID;

	AccountData[playerid][pMechTempComp1] = 0;
	AccountData[playerid][pMechTempComp2] = 0;

	AccountData[playerid][pCuffed] = false;
	AccountData[playerid][pTied] = false;

	ShowroomIndex_ID[playerid] = 0;
    ShowroomBuyType[playerid] = -1;

	AccountData[playerid][pTazedTime] = 0;
	AccountData[playerid][pBeanbagTime] = 0;
	AccountData[playerid][pTackleTime] = 0;
	
	AccountData[playerid][p911Hotline] = 0;
	AccountData[playerid][pMekHotline] = 0;
	AccountData[playerid][pPdgHotline] = 0;
	AccountData[playerid][pDinarHotline] = 0;
	AccountData[playerid][pPemdaHotline] = 0;
	
	AccountData[playerid][LoginAttempts] = 0;
	
	AccountData[playerid][pTempTransferID] = INVALID_PLAYER_ID;
	
	AccountData[playerid][pTempSellerID] = INVALID_PLAYER_ID;
	AccountData[playerid][pTempSellPrice] = 0;
	AccountData[playerid][pTempSellIterID] = -1;

	AccountData[playerid][pSPY] = false;
	
	TempString[playerid][0] = EOS;
	Temptargetid[playerid] = INVALID_PLAYER_ID;

	for(new x; x < 100; x++)
	{
		ListedUser[playerid][x] = INVALID_PLAYER_ID;
		NearestUser[playerid][x] = INVALID_PLAYER_ID;
		PlayerListitem[playerid][x] = -1;
	}
	
	for(new id; id < 100; ++id)
	{
		PlayerWarning[playerid][id][warnExists] = false;
		PlayerWarning[playerid][id][warnOwner] = 0;
		PlayerWarning[playerid][id][warnType] = 0;
		PlayerWarning[playerid][id][warnIssuer][0] = EOS;
		PlayerWarning[playerid][id][warnDate][0] = EOS;
		PlayerWarning[playerid][id][warnDateTime][0] = EOS;
		PlayerWarning[playerid][id][warnReason][0] = EOS;
	}

	for(new x; x < MAX_INVOICES; x++)
	{
		ListedInvoices[playerid][x] = -1;
	}
	
	NearestSingle[playerid] = INVALID_PLAYER_ID;
	NearestVehicleID[playerid] = INVALID_VEHICLE_ID;

	for(new j; j < MAX_CONTACTS; j++)
	{
		ContactData[playerid][j][contactID] = 0;
		ContactData[playerid][j][contactExists] = false;
		ContactData[playerid][j][contactName][0] = EOS;
		ContactData[playerid][j][contactNumber][0] = EOS;
		ContactData[playerid][j][contactOwnerID] = 0;
		ContactData[playerid][j][contactUnread] = 0;
	}

	for(new j; j < MAX_INVOICES; j++)
	{
		InvoiceData[playerid][j][invoiceExists] = false;
		InvoiceData[playerid][j][invoiceOwner] = 0;
		InvoiceData[playerid][j][invoiceName][0] = EOS;
		InvoiceData[playerid][j][invoiceCost] = 0;
		InvoiceData[playerid][j][invoiceIssuerDB] = 0;
		InvoiceData[playerid][j][invoiceFactID] = FACTION_NONE;
		InvoiceData[playerid][j][invoiceID] = 0;
	}

	for(new i = 0; i < 5; i++)
	{
		PlayerTextDrawDestroy(playerid, TextDrawItemBox[playerid][i*10]);
		TextDrawItemBox[playerid][i*10] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
		
		InfoItemBox[playerid][i][ItemBoxIcon] = -1;
		InfoItemBox[playerid][i][ItemBoxMessage][0] = EOS;
		InfoItemBox[playerid][i][ItemBoxJumlahMessage][0] = EOS;
		InfoItemBox[playerid][i][ItemBoxSize] = 0;
	}

	HideModshopTD(playerid);
	
	AccountData[playerid][pUsingGPS] = false;
	AccountData[playerid][pHasSharedGPS] = false;

	AccountData[playerid][pAskTime] = 0;
	AccountData[playerid][pReportTime] = 0;
	
	AccountData[playerid][pTempSQLFactMemberID] = 0;
	AccountData[playerid][pTempSQLFactRank] = 0;

	AccountData[playerid][pActivityTime] = 0;
	AccountData[playerid][pInfoTimeTD] = 0;
	AccountData[playerid][pSuccessTimeTD] = 0;
	AccountData[playerid][pErrorTimeTD] = 0;
	AccountData[playerid][pSyntaxTimeTD] = 0;
	AccountData[playerid][pWarningTimeTD] = 0;

	AccountData[playerid][pCountingValue] = 0;

	AccountData[playerid][pDirtyMoney] = 0;
	AccountData[playerid][pMoney] = 0;
	AccountData[playerid][pBankMoney] = 0;
	AccountData[playerid][pSlipSalary] = 0;
	
	AccountData[playerid][IsLoggedIn] = false;
	AccountData[playerid][pSpawned] = false;

	AccountData[playerid][pChar] = -1;

	AccountData[playerid][pTeleported] = false;
	AccountData[playerid][pFreeze] = false;

    AccountData[playerid][pSpec] = INVALID_PLAYER_ID;

	AccountData[playerid][pInGarkot] = -1;
	AccountData[playerid][pInRent] = -1;
	AccountData[playerid][pInCannabis] = -1;
	AccountData[playerid][pInGas] = -1;
	AccountData[playerid][pInTree] = -1;
	AccountData[playerid][pInPlant] = -1;
	AccountData[playerid][pInStone] = -1;
	
	FivemNotifyIndex[playerid] = 0;

	AccountData[playerid][pDetained] = false;

	AccountData[playerid][pHungerTime] = 0;
	AccountData[playerid][pThirstTime] = 0;
	AccountData[playerid][pStressTime] = 0;
	//MythicNotifyIndex[playerid] = 0;
	
	/* Inventory Stuff*/
	for(new x; x < MAX_INVENTORY; x++)
	{
	    InventoryData[playerid][x][invExists] = false;
	    InventoryData[playerid][x][invModel] = 0;
	    InventoryData[playerid][x][invQuantity] = 0;
		InventoryData[playerid][x][invItem][0] = EOS;
	}
	AccountData[playerid][pSelectItem] = -1;
	AccountData[playerid][pInventTargetID] = INVALID_PLAYER_ID;
	AccountData[playerid][pItemQuantity] = 0;
	/* end of inventory stuff */

	/* voice stuff */
	PlayerVoiceData[playerid][pIsMegaOn] = false;
	PlayerVoiceData[playerid][pIsRadioOn] = false;
	PlayerVoiceData[playerid][pIsRadioMicOn] = false;
	//PlayerVoiceData[playerid][VoiceModeDistance] = 2;
	PlayerVoiceData[playerid][pRadioFreq] = 0;
	/* end of voice stuff */

	//GYM
	// if(GYM_PlayerUsing[playerid])
	// {
	// 	switch(GYM_PlayerType[playerid])
	// 	{
	// 		case 1:
	// 		{
	// 			g_GYMFreeWeightUsed[GYM_PlayerToolID[playerid]] = false;
	// 		}
	// 		case 2:
	// 		{
	// 			g_GYMYogaUsed[GYM_PlayerToolID[playerid]] = false;
	// 		}
	// 		case 3:
	// 		{
	// 			g_GYMBikeUsed[GYM_PlayerToolID[playerid]] = false;
	// 		}
	// 		case 4:
	// 		{
	// 			g_GYMBarbelUsed[GYM_PlayerToolID[playerid]] = false;
	// 		}
	// 	}
	// }
	
	// GYM_PlayerUsing[playerid] = false;
	// GYM_PlayerProgress[playerid] = 0;
	// GYM_PlayerType[playerid] = 0;
	// GYM_PlayerToolID[playerid] = -1;

	// if(IsValidPlayerTextDraw(playerid, PGYM_UI[playerid]))
	// {
	// 	PlayerTextDrawDestroy(playerid, PGYM_UI[playerid]);
	// 	PGYM_UI[playerid] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
	// }

	AccountData[playerid][pAccDeathTime] = 0;
	AccountData[playerid][pKnockdown] = false;
	AccountData[playerid][pKnockdownTime] = 0;
	AccountData[playerid][pComma] = false;

	//phone
	PlayerPhoneData[playerid][phoneShowedPageTD] = 0;
	PlayerPhoneData[playerid][phoneContactSelected] = -1;
	PlayerPhoneData[playerid][phoneIncomingCall] = false;

	PlayerPhoneData[playerid][phoneCallingWithPlayerID] = INVALID_PLAYER_ID;
	PlayerPhoneData[playerid][phoneTempName][0] = EOS;
	PlayerPhoneData[playerid][phoneTempNumber][0] = EOS;
	PlayerPhoneData[playerid][phoneDownloadingApp] = false;
	PlayerPhoneData[playerid][phoneDownloadingProg] = 0;
	PlayerPhoneData[playerid][CurrentlyReadTweet] = false;
	PlayerPhoneData[playerid][CurrentlyReadWA] = false;
	PlayerPhoneData[playerid][phoneShown] = false;
	PlayerPhoneData[playerid][phoneOn] = true;

	//refuel
	AccountData[playerid][pDuringRefueling] = false;
	AccountData[playerid][pHoldingFuelCan] = false;
	AccountData[playerid][pRefuelingPrice] = 0;
	
	//chatanim
    AccountData[playerid][pChatAnim] = true;

	//rokok
	AccountData[playerid][pIsSmoking] = false;
	AccountData[playerid][pIsSmokeBlowing] = false;
	AccountData[playerid][pSmokedTimes] = 0;

	//law community service
    if(AccountData[playerid][pHowMuchComServing] > 0)
    {
        AccountData[playerid][pGivenComServBy] = INVALID_PLAYER_ID;
        AccountData[playerid][pGiveComServTo] = INVALID_PLAYER_ID;
        AccountData[playerid][pCommunityService] = true;
        AccountData[playerid][pTotalComServed] = 0;
    }
    else
    {
        AccountData[playerid][pGivenComServBy] = INVALID_PLAYER_ID;
        AccountData[playerid][pGiveComServTo] = INVALID_PLAYER_ID;
        AccountData[playerid][pCommunityService] = false;
        AccountData[playerid][pTotalComServed] = -1;
        AccountData[playerid][pHowMuchComServing] = 0;
    }

	AC_CMDSpamTime[playerid] = 0;
	AC_ChatSpamTime[playerid] = 0;
	
	//ems
	AccountData[playerid][LSFDDuringReviving] = false;

	//gojek
	UberAppTemp[playerid][ServiceAcceptedBy] = INVALID_PLAYER_ID;
	ResetUberAppTemp(playerid);

	foreach(new i : Player)
	{
		if(AccountData[i][pTempSellerID] == playerid)
		{
			AccountData[i][pTempSellerID] = INVALID_PLAYER_ID;
		}

		if(AccountData[i][pSpec] == playerid)
		{
			PlayerSpectatePlayer(i, INVALID_PLAYER_ID);
			PlayerSpectateVehicle(i, INVALID_VEHICLE_ID);

			SetSpawnInfo(i, NO_TEAM, AccountData[i][pSkin], AccountData[i][pPos][0], AccountData[i][pPos][1], AccountData[i][pPos][2], AccountData[i][pPos][3], 0, 0, 0, 0, 0, 0);
			TogglePlayerSpectating(i, false);
			AccountData[i][pSpec] = INVALID_PLAYER_ID;

			PlayerTextDrawHide(i, SpecInfoTD[i]);
			ShowTDN(i, NOTIFICATION_INFO, "Anda telah keluar dari mode spectator, Pemain tersebut disconnect.");
		}
	}
	
	// //race
	// if(RaceJoinedID[playerid] != -1)
    // {
	// 	if(RaceData[RaceJoinedID[playerid]][raceCreatorID] == playerid)
    //     {
    //         ResetRaceVars(RaceJoinedID[playerid]);
    //         Iter_Remove(PRaces, RaceJoinedID[playerid]);

    //         foreach(new i : Player) if(RaceJoinedID[i] == RaceJoinedID[playerid])
    //         {
    //             SendClientMessage(i, -1, "Balap telah dibubarkan karena pembuat telah disconnect!");

    //             if(DestroyDynamicRaceCP(PlayerRaceCP[i]))
    //                 PlayerRaceCP[i] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;
                
    //             RaceCreatorMode[i] = false;
    //             RaceJoinedID[i] = -1;
    //             RaceCreatorCPIndex[i] = -1;
    //             RacePlayerStep[i] = 0;
    //         }
    //     }
	// }
	// RaceCreatorMode[playerid] = false;
	// RaceJoinedID[playerid] = -1;
	// RaceCreatorCPIndex[playerid] = -1;
	// RacePlayerStep[playerid] = 0;

	// ----------------------------------------------------------------------------//
	//DestoryPlayerFactObject(playerid);

	if(DestroyDynamicActor(pDrugSellActor[playerid]))
		pDrugSellActor[playerid] = STREAMER_TAG_ACTOR: INVALID_STREAMER_ID;

	if(DestroyDynamicMapIcon(pDrugSellIcon[playerid]))
		pDrugSellIcon[playerid] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;

	if(DestroyDynamic3DTextLabel(pDrugSellLabel[playerid]))
		pDrugSellLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

	pDrugSellChosen[playerid] = -1;
    pDrugSellStep[playerid] = 0;   

	if(DestroyDynamicObject(AccountData[playerid][pDTOObject]))
        AccountData[playerid][pDTOObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

    if(DestroyDynamic3DTextLabel(AccountData[playerid][pDTOLabel]))
        AccountData[playerid][pDTOLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

	if(DestroyDynamic3DTextLabel(AdminLabel[playerid]))
    	AdminLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

	AngkotRute[playerid] = -1;
	AngkotRouteType[playerid] = 0;
	AngkotPenumpang[playerid] = false;
	pAngkotTimer[playerid] = false;
	
	if(DestroyDynamicRaceCP(JobCP[playerid]))
		JobCP[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

	if(DestroyDynamicActor(AngkotActor[playerid]))
		AngkotActor[playerid] = STREAMER_TAG_ACTOR: INVALID_STREAMER_ID;

	for(new x; x < 3; x++)
	{
		if(DestroyDynamic3DTextLabel(pFactionLabel[playerid][x]))
    		pFactionLabel[playerid][x] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
	}

	//-------- [sidejob] ----------
	for(new x; x < sizeof(MowingPlant); x++)
    {
        if(DestroyDynamicObject(MowingObject[playerid][x]))
            MowingObject[playerid][x] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

        if(DestroyDynamicArea(MowingArea[playerid][x]))
            MowingArea[playerid][x] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
    }
    MowingCountingGrass[playerid] = 0;
    MowingTimerSecond[playerid] = 0;
	if(AccountData[playerid][pSideJob] == SIDEJOB_MOWING)
	{
    	if(IsAMowingSidejobVeh(SavingVehID[playerid]))
			ChangeVehicleColor(SavingVehID[playerid], 1, 1);

		RespawnVehicle(SavingVehID[playerid]);
	}

	
	if(DestroyDynamicCP(SweeperCP[playerid]))
		SweeperCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
	SweeperCPPath[playerid] = 0;
	SweeperRute[playerid] = -1;
	if(AccountData[playerid][pSideJob] == SIDEJOB_SWEEPER)
	{
		if(IsASweeperSidejobVeh(SavingVehID[playerid]))
			ChangeVehicleColor(SavingVehID[playerid], 1, 1);

		RespawnVehicle(SavingVehID[playerid]);
	}
	
	ForkliftUnloadedCrate[playerid] = 0;
	if(DestroyDynamicCP(ForkliftCP[playerid]))
		ForkliftCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
	if(DestroyDynamicCP(ForkliftReturnCP[playerid]))
		ForkliftReturnCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
	if(DestroyDynamicCP(UnloadForkliftCP[playerid]))
		UnloadForkliftCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
	if(DestroyDynamicObject(ForkliftCrateObj[playerid]))
		ForkliftCrateObj[playerid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

	if(AccountData[playerid][pSideJob] == SIDEJOB_FORKLIFT)
	{
		if(IsAForkliftSidejobVeh(SavingVehID[playerid]))
			ChangeVehicleColor(SavingVehID[playerid], 1, 1);

		RespawnVehicle(SavingVehID[playerid]);
	}

	TrashCollectorHoldingBag[playerid] = false;
	TrashCollectorLeavingTime[playerid] = 0;
	TrashCollected[playerid] = 0;
	for (new i; i < 25; i++) 
	{
		if(DestroyDynamicCP(TrashCollectorCP[playerid][i]))
			TrashCollectorCP[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

		if(DestroyDynamicMapIcon(TrashCollectorIcon[playerid][i]))
			TrashCollectorIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;

		selectedGarbage[playerid][i] = -1;
	}

	if(DestroyDynamicCP(TrashCollectorRVehCP[playerid]))
		TrashCollectorRVehCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

	if(DestroyDynamicCP(TrashCollectorBackCP[playerid]))
        TrashCollectorBackCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

	if(AccountData[playerid][pSideJob] == SIDEJOB_TRASHCOLLECTOR)
	{
		if(IsATrashCollectorSidejobVeh(TrashCollectorPlayerVeh[playerid]))
			ChangeVehicleColor(TrashCollectorPlayerVeh[playerid], 1, 1);

		RespawnVehicle(TrashCollectorPlayerVeh[playerid]);
		TrashCollectorPlayerVeh[playerid] = INVALID_VEHICLE_ID;
	}

	if(DestroyDynamicCP(pizzaDeliveryCP[playerid]))
		pizzaDeliveryCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

	if(DestroyDynamicActor(pizzaDeliveryActor[playerid]))
		pizzaDeliveryActor[playerid] = STREAMER_TAG_ACTOR: INVALID_STREAMER_ID;

	if(DestroyDynamicRaceCP(pizzaDeliveryRCP[playerid]))
		pizzaDeliveryRCP[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

	pizzaDelivered[playerid] = 0;
	pizzaRandom[playerid] = -1;
	pizzaHoldingBox[playerid] = false;

	SavingVehID[playerid] = INVALID_VEHICLE_ID;
	AccountData[playerid][pSideJob] = SIDEJOB_NONE;

	//notif box
	AccountData[playerid][pShowNotifBox] = false;

    //edit dynamic
	AccountData[playerid][EditingTableBJID] = -1;
	AccountData[playerid][EditingModshopSlotID] = -1;
	AccountData[playerid][EditingOreID] = -1;
	AccountData[playerid][EditingNewsStandID] = -1;
	AccountData[playerid][EditingVendingID] = -1;
	AccountData[playerid][EditingCraftTableID] = -1;
	AccountData[playerid][EditingGraffitiID] = -1;
	AccountData[playerid][EditingTreeID] = -1;
	AccountData[playerid][EditingSCamID] = -1;
	AccountData[playerid][EditingRSignID] = -1;
	AccountData[playerid][EditingXmasTreeID] = -1;
    AccountData[playerid][EditingGarbageID] = -1;
	AccountData[playerid][EditingFLabelID] = -1;
	AccountData[playerid][EditingKanabisID] = -1;
	AccountData[playerid][EditingRobberyID] = -1;
	AccountData[playerid][EditingAtmID] = -1;
	AccountData[playerid][EditingDeerID] = -1;
	
	AccountData[playerid][EditingButtonID] = -1;
	AccountData[playerid][EditingButton] = 0;

	RemoveJobIterator(playerid);

	//robbery warung
	if(AccountData[playerid][pDuringRobbery])
	{
		//warung
		GM[ShopRobberyOngoing] = false;
		GM[ShopRobberyCooldown] = gettime() + 1200;
	}

	//robbery pacific
	if(AccountData[playerid][pDuringBRobbery])
	{
		g_BankRobberyStarted = false;
		g_BankRobberyCooldown = 3600;
		g_BankRobberyCountdown = 0;
		UpdateDynamic3DTextLabelText(BankRobStatusLabel, Y_WHITE, "Pacific Standard Public Deposit Bank\n"YELLOW"/robbank\n\n"WHITE"Status: "RED"Unready");
	}
	RobberyCountdown[playerid] = 0;
	AccountData[playerid][pDuringRobbery] = false;
	AccountData[playerid][pInRobberyID] = -1;

	AccountData[playerid][pDuringBRobbery] = false;
	AccountData[playerid][pQBRobbery] = 0;
	AccountData[playerid][pABRobbery][0] = EOS;
	p_BankRobberyStep[playerid] = 0;

	//carsteal
	if(AccountData[playerid][pDuringCarsteal])
	{
		g_IsCarstealStarted = false;
		g_CarstealCountdown = 0;
		g_CarstealCooldown = gettime() + 1800;

		AccountData[playerid][pDuringCarsteal] = false;
	}
	g_CarstealCarFound[playerid] = false;
	g_CarstealCarDelivered[playerid] = false;
	AccountData[playerid][pCarstealHoldingPart] = false;
	g_CarstealStepPart[playerid] = INVALID_VEHICLE_ID;

	//clothes
	ClothesData[playerid][clothesTotal] = 0;
	AccountData[playerid][pUsingClothes] = 0;

	//boombox
	ResetBoombox(playerid);
	
	//player data
	AccountData[playerid][pName][0] = EOS;
	AccountData[playerid][pUCP][0] = EOS;
	AccountData[playerid][pIP][0] = EOS;
	
    //Toys
	AccountData[playerid][pHealth] = 100.0;
	AccountData[playerid][pArmor] = 0.0;

    AccountData[playerid][pIsToyInsertedOnMysql] = false;
	AccountData[playerid][pToySelected] = -1;
	for(new i; i < 5; i++)
	{
		pToys[playerid][i][toy_model] = 0;
		pToys[playerid][i][toy_bone] = 0;
		pToys[playerid][i][toy_x] = 0.0;
		pToys[playerid][i][toy_y] = 0.0;
		pToys[playerid][i][toy_z] = 0.0;
		pToys[playerid][i][toy_rx] = 0.0;
		pToys[playerid][i][toy_ry] = 0.0;
		pToys[playerid][i][toy_rz] = 0.0;
		pToys[playerid][i][toy_sx] = 0.0;
		pToys[playerid][i][toy_sy] = 0.0;
		pToys[playerid][i][toy_sz] = 0.0;
		pToys[playerid][i][toy_hidden] = false;
	}
	
	//admin duty
	if(AccountData[playerid][pAdminDuty])
	{
		AccountData[playerid][pAdminDuty] = false;
		SetPlayerHealth(playerid, AccountData[playerid][pHealth]);
	}
	
	for(new x; x < MAX_FACTIONS; x++)
	{
		DestroyVehicle(PlayerFactionVehicle[playerid][x]);
		PlayerFactionVehicle[playerid][x] = INVALID_VEHICLE_ID;
	}
	LSPDPlayerCallsign[playerid][0] = EOS;
	
	PlayerFactionVehStats[playerid][pFactVehModel] = -1;
	PlayerFactionVehStats[playerid][pFactVehPos][0] = 0.0;
	PlayerFactionVehStats[playerid][pFactVehPos][1] = 0.0;
	PlayerFactionVehStats[playerid][pFactVehPos][2] = 0.0;
	PlayerFactionVehStats[playerid][pFactVehPos][3] = 0.0;
	PlayerFactionVehStats[playerid][pFactVehDamage][0] = 0;
	PlayerFactionVehStats[playerid][pFactVehDamage][1] = 0;
	PlayerFactionVehStats[playerid][pFactVehDamage][2] = 0;
	PlayerFactionVehStats[playerid][pFactVehDamage][3] = 0;
	PlayerFactionVehStats[playerid][pFactVehFuel] = 0;
	PlayerFactionVehStats[playerid][pFactVehLocked] = false;
	PlayerFactionVehStats[playerid][pFactVehWorld] = 0;
	PlayerFactionVehStats[playerid][pFactVehColor1] = 0;
	PlayerFactionVehStats[playerid][pFactVehColor2] = 0;

	//pvar
	DeletePVar(playerid, "SelectedSpawnID");
	DeletePVar(playerid, "SelectedSpawnRegID");
	DeletePVar(playerid, "UpdatedToy");
	DeletePVar(playerid, "ClothesShopChoosenID");
    DeletePVar(playerid, "IsPlayerPurchasedToys");

	//reset iterators
	if(Iter_Contains(InEvent, playerid))
	{
		Iter_Remove(InEvent, playerid);
	}
	if(Iter_Contains(EvRedTeam, playerid))
	{
		Iter_Remove(EvRedTeam, playerid);
	}
	if(Iter_Contains(EvBlueTeam, playerid))
	{
		Iter_Remove(EvBlueTeam, playerid);
	}
	if(Iter_Contains(EvZombieTeam, playerid))
	{
		Iter_Remove(EvZombieTeam, playerid);
	}
	if(Iter_Contains(EvHumanTeam, playerid))
	{
		Iter_Remove(EvHumanTeam, playerid);
	}

	//hapus kendaraan job
	DestroyJobVehicle(playerid);
	
	DestroyVehicle(g_CarstealCarPhysic[playerid]);

	DestroyVehicle(ShowroomVeh[playerid]);

	DestroyVehicle(EventVehicle[playerid]);
	
	DestroyVehicle(DMVVeh[playerid]);

	/*if(DestroyDynamicCP(bangunanCP[playerid]))
        bangunanCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;*/

	if(DestroyDynamic3DTextLabel(AccountData[playerid][pAdoTag]))
		AccountData[playerid][pAdoTag] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

	if(DestroyDynamicCP(p_BankRobberyCP[playerid]))
        p_BankRobberyCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

	if(DestroyDynamicObject(AccountData[playerid][pFlareObjid]))
        AccountData[playerid][pFlareObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
	
	if(DestroyDynamicMapIcon(AccountData[playerid][pSignalIcon]))
        AccountData[playerid][pSignalIcon] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
	
	foreach(new i : Player) if(i != playerid)
	{
		if(AccountData[i][pDragOffer] == playerid)
			AccountData[i][pDragOffer] = INVALID_PLAYER_ID;

		if(AccountData[i][pESharedOfferer] == playerid)
			AccountData[i][pESharedOfferer] = INVALID_PLAYER_ID;

		if(AccountData[i][DraggingID] != INVALID_PLAYER_ID && AccountData[i][DraggingID] == playerid) //player yang quit sedang digendong oleh player lain
		{
			TogglePlayerControllable(playerid, true);
			SendClientMessage(i, -1, "Pemain yang anda gendong/seret telah keluar dari server.");
			AccountData[playerid][pGetDraggedBy] = INVALID_PLAYER_ID;
			AccountData[i][DraggingID] = INVALID_PLAYER_ID;
		}

		if(AccountData[i][pGetDraggedBy] != INVALID_PLAYER_ID && AccountData[i][pGetDraggedBy] == playerid) //player yang quit sedang menggendong player lain
		{
			SendClientMessage(i, -1, "Pemain yang menggendong/menyeret anda telah keluar dari server.");
			AccountData[playerid][DraggingID] = INVALID_PLAYER_ID;
			AccountData[i][pGetDraggedBy] = INVALID_PLAYER_ID;
		}

		if(DestroyDynamic3DTextLabel(AccountData[playerid][pNameIDLabel][i]))
			AccountData[playerid][pNameIDLabel][i] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

		if(DestroyDynamic3DTextLabel(AccountData[i][pNameIDLabel][playerid]))
			AccountData[i][pNameIDLabel][playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

		if(DestroyDynamicMapIcon(AccountData[playerid][pFlareIcon][i]))
       	 	AccountData[playerid][pFlareIcon][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;

		if(DestroyDynamicMapIcon(AccountData[i][pFlareIcon][playerid]))
        	AccountData[i][pFlareIcon][playerid] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;

		if(DestroyDynamicMapIcon(AccountData[playerid][g_CarstealIcon][i]))
			AccountData[playerid][g_CarstealIcon][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;

		if(DestroyDynamicMapIcon(AccountData[i][g_CarstealIcon][playerid]))
			AccountData[i][g_CarstealIcon][playerid] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;

		if(DestroyDynamicMapIcon(AccountData[playerid][pSignalRobberyIcon][i]))
			AccountData[playerid][pSignalRobberyIcon][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;

		if(DestroyDynamicMapIcon(AccountData[i][pSignalRobberyIcon][playerid]))
			AccountData[i][pSignalRobberyIcon][playerid] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
	}

	if(DestroyDynamic3DTextLabel(AccountData[playerid][pCarstealLabel]))
		AccountData[playerid][pCarstealLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

	if(DestroyDynamic3DTextLabel(AccountData[playerid][pCarstealLabelPart]))
		AccountData[playerid][pCarstealLabelPart] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

	if(DestroyDynamicCP(AccountData[playerid][pCarstealStoringCP]))
		AccountData[playerid][pCarstealStoringCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

	if(DestroyDynamicMapIcon(AccountData[playerid][pSharedGPSIcon]))
		AccountData[playerid][pSharedGPSIcon] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;

	if(DestroyDynamicMapIcon(PlayerCargoVars[playerid][CargoDestCP]))
		PlayerCargoVars[playerid][CargoDestCP] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;	

	if(DestroyDynamicRaceCP(PlayerCargoVars[playerid][CargoReturnCP]))
		PlayerCargoVars[playerid][CargoReturnCP] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

	if(DestroyDynamicRaceCP(pTutorialRCP[playerid]))
		pTutorialRCP[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

	//faction
	if(DestroyDynamicObject(AccountData[playerid][PoliceConeObjid]))
    	AccountData[playerid][PoliceConeObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
	if(DestroyDynamicObject(AccountData[playerid][PoliceRoadblockObjid]))
		AccountData[playerid][PoliceRoadblockObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
	if(DestroyDynamicObject(AccountData[playerid][PoliceSpikeObjid]))
		AccountData[playerid][PoliceSpikeObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
	if(DestroyDynamicArea(AccountData[playerid][PoliceSpikeArea]))
		AccountData[playerid][PoliceSpikeArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

	for(new gp; gp < sizeof(__g_GasPumpLoc); gp++)
	{
		if(DestroyDynamic3DTextLabel(g_GasPumpLabel[playerid][gp]))
			g_GasPumpLabel[playerid][gp] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
	}

	if(DestroyDynamic3DTextLabel(g_GasProgressLabel[playerid]))
		g_GasProgressLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

	AccountData[playerid][pGetDraggedBy] = INVALID_PLAYER_ID;
	AccountData[playerid][DraggingID] = INVALID_PLAYER_ID;
	AccountData[playerid][pDragOffer] = INVALID_PLAYER_ID;
}

ResetBoombox(playerid)
{
    if(BoomBoxInfo[playerid][BoomBoxPlaced])
    {
        foreach(new i : Player)
        {
            if(IsPlayerInDynamicArea(i, BoomBoxInfo[playerid][BoomBoxArea]))
            {
                StopAudioStreamForPlayer(i);
            }
        }
    }

    if(DestroyDynamicObject(BoomBoxInfo[playerid][BoomBoxObj]))
		BoomBoxInfo[playerid][BoomBoxObj] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

    if(DestroyDynamic3DTextLabel(BoomBoxInfo[playerid][BoomBoxLabel]))
		BoomBoxInfo[playerid][BoomBoxLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    if(DestroyDynamicArea(BoomBoxInfo[playerid][BoomBoxArea]))
		BoomBoxInfo[playerid][BoomBoxArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
    
    BoomBoxInfo[playerid][BoomBoxOwner][0] = EOS;
    BoomBoxInfo[playerid][BoomBoxLink][0] = EOS;

    BoomBoxInfo[playerid][BoomBoxPlaced] = false;

    BoomBoxInfo[playerid][BoomX] = 0.0;
    BoomBoxInfo[playerid][BoomY] = 0.0;
    BoomBoxInfo[playerid][BoomZ] = 0.0;
    BoomBoxInfo[playerid][BoomA] = 0.0;

    BoomBoxInfo[playerid][BoomVw] = 0;
    BoomBoxInfo[playerid][BoomInt] = 0;

	// new
}

ShowCharacterList(playerid)
{
	new count = 0, sgstr[525];

	format(sgstr, sizeof(sgstr), "Name\tLevel\tMoney\tBank\n");
	for (new i; i < MAX_CHARS; i ++) if(!isnull(PlayerChar[playerid][i]))
	{
	    format(sgstr, sizeof(sgstr), "%s%s\t%d\t$%s\t$%s\n", sgstr, PlayerChar[playerid][i], PlayerCharLevel[playerid][i], FormatMoney(PlayerCharCash[playerid][i]), FormatMoney(PlayerCharBank[playerid][i]));
		count++;
	}
	if(count < MAX_CHARS)
		format(sgstr, sizeof(sgstr), "%s"GREEN"+ New Character", sgstr);

	Dialog_Show(playerid, "CharacterList", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Character List", sgstr, "Pilih", "Quit");
	return 1;
}

SetPlayerToFacePlayer(playerid, targetid)
{
	new
	    Float:x[2],
	    Float:y[2],
	    Float:z[2],
	    Float:angle;

	GetPlayerPos(targetid, x[0], y[0], z[0]);
	GetPlayerPos(playerid, x[1], y[1], z[1]);

	angle = (180.0 - atan2(x[1] - x[0], y[1] - y[0]));
	SetPlayerFacingAngle(playerid, angle + (5.0 * -1));
}

SetPlayerPositionEx(playerid, Float:x, Float:y, Float:z, Float:a, time = 3500)
{
	if(AccountData[playerid][pTeleported])
	{
		KillTimer(pUnfreezeTimer[playerid]);
		pUnfreezeTimer[playerid] = -1;
		AccountData[playerid][pTeleported] = false;
	}
    SetCameraBehindPlayer(playerid);
    TogglePlayerControllable(playerid, false);
    AccountData[playerid][pTeleported] = true;
    AccountData[playerid][pFreeze] = true;
    SetPlayerPos(playerid, x, y, z + 0.40);
	SetPlayerFacingAngle(playerid, a);
	AC_LastStateTime[playerid] = GetTickCount() - 9999;
	Anticheat[playerid][acImmunity] = gettime() + 5;
	pUnfreezeTimer[playerid] = SetTimerEx("SetPlayerToUnfreeze", time, false, "iffff", playerid, x, y, z, a);
}

SetVehiclePositionEx(playerid, vehicleid, Float:x, Float:y, Float:z, Float:a, time = 3000)
{
    if(AccountData[playerid][pTeleported])
	{
		KillTimer(pUnfreezeTimer[playerid]);
		pUnfreezeTimer[playerid] = -1;
		AccountData[playerid][pTeleported] = false;
	}
    SetCameraBehindPlayer(playerid);
    TogglePlayerControllable(playerid, false);
    AccountData[playerid][pTeleported] = true;
    AccountData[playerid][pFreeze] = true;
    SetVehiclePos(vehicleid, x, y, z + 0.4);
	SetVehicleZAngle(vehicleid, a);
	Anticheat[playerid][acImmunity] = gettime() + 5;
	pUnfreezeTimer[playerid] = SetTimerEx("SetVehicleToUnfreeze", time, false, "iiffff", playerid, vehicleid, x, y, z, a);
}

SetPlayerVirtualWorldEx(playerid, vwid)
{
	AccountData[playerid][pWorld] = vwid;
	return SetPlayerVirtualWorld(playerid, vwid);
}

SetPlayerInteriorEx(playerid, intid)
{
	AccountData[playerid][pInterior] = intid;
	return SetPlayerInterior(playerid, intid);
}

DeleteMapJob(playerid)
{
	//job lumberjack
	for(new x; x < 7; x++)
	{
		if(DestroyDynamicArea(PlayerLumberjackVars[playerid][LumberGetWoodArea][x]))
			PlayerLumberjackVars[playerid][LumberGetWoodArea][x] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

		PlayerLumberjackVars[playerid][LumberWoodCountdown][x] = 0;
	}

	//job milker
	if(DestroyDynamicObject(PlayerMilkerVars[playerid][CowObject]))
		PlayerMilkerVars[playerid][CowObject] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
	if(DestroyDynamicArea(PlayerMilkerVars[playerid][MilkerTakeArea]))
		PlayerMilkerVars[playerid][MilkerTakeArea] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;

	PlayerMilkerVars[playerid][MilkTaken] = 0;
}

RefreshMapJob(playerid)
{
	DeleteMapJob(playerid);

	switch(AccountData[playerid][pJob])
	{
		case JOB_LUMBERJACK:
		{
			PlayerLumberjackVars[playerid][LumberGetWoodArea][0] = CreateDynamicSphere(__g_TreePos[0][0], __g_TreePos[0][1], __g_TreePos[0][2], 3.0, 0, 0, playerid);
			PlayerLumberjackVars[playerid][LumberGetWoodArea][1] = CreateDynamicSphere(__g_TreePos[1][0], __g_TreePos[1][1], __g_TreePos[1][2], 3.0, 0, 0, playerid);
			PlayerLumberjackVars[playerid][LumberGetWoodArea][2] = CreateDynamicSphere(__g_TreePos[2][0], __g_TreePos[2][1], __g_TreePos[2][2], 3.0, 0, 0, playerid);
			PlayerLumberjackVars[playerid][LumberGetWoodArea][3] = CreateDynamicSphere(__g_TreePos[3][0], __g_TreePos[3][1], __g_TreePos[3][2], 3.0, 0, 0, playerid);
			PlayerLumberjackVars[playerid][LumberGetWoodArea][4] = CreateDynamicSphere(__g_TreePos[4][0], __g_TreePos[4][1], __g_TreePos[4][2], 3.0, 0, 0, playerid);
			PlayerLumberjackVars[playerid][LumberGetWoodArea][5] = CreateDynamicSphere(__g_TreePos[5][0], __g_TreePos[5][1], __g_TreePos[5][2], 3.0, 0, 0, playerid);
			PlayerLumberjackVars[playerid][LumberGetWoodArea][6] = CreateDynamicSphere(__g_TreePos[6][0], __g_TreePos[6][1], __g_TreePos[6][2], 3.0, 0, 0, playerid);
		}
	}
}

RemoveJobIterator(playerid)
{
	if(Iter_Contains(LSPDDuty, playerid))
		Iter_Remove(LSPDDuty, playerid);

	if(Iter_Contains(LSFDDuty, playerid))
		Iter_Remove(LSFDDuty, playerid);

	if(Iter_Contains(PutrideliDuty, playerid))
		Iter_Remove(PutrideliDuty, playerid);

	if(Iter_Contains(PemerDuty, playerid))
		Iter_Remove(PemerDuty, playerid);

	if(Iter_Contains(BennysDuty, playerid))
		Iter_Remove(BennysDuty, playerid);

	if(Iter_Contains(UberDuty, playerid))
		Iter_Remove(UberDuty, playerid);

	if(Iter_Contains(DinarbucksDuty, playerid))
		Iter_Remove(DinarbucksDuty, playerid);

	if(Iter_Contains(Fox11Duty, playerid))
		Iter_Remove(Fox11Duty, playerid);

	if(Iter_Contains(AutomaxDuty, playerid))
		Iter_Remove(AutomaxDuty, playerid);

	if(Iter_Contains(HandoverDuty, playerid))
		Iter_Remove(HandoverDuty, playerid);

	if(Iter_Contains(SriMersingDuty, playerid))
		Iter_Remove(SriMersingDuty, playerid);
	
	if(Iter_Contains(TexasChickenDuty, playerid))
		Iter_Remove(TexasChickenDuty, playerid);
}

AddJobIterator(playerid)
{
	if(AccountData[playerid][pOnDuty])
	{
		switch(AccountData[playerid][pFaction])
		{
			case FACTION_LSPD:
			{
				Iter_Add(LSPDDuty, playerid);
			}
			case FACTION_LSFD:
			{
				Iter_Add(LSFDDuty, playerid);
			}
			case FACTION_PUTRIDELI:
			{
				Iter_Add(PutrideliDuty, playerid);
			}
			case FACTION_SAGOV:
			{
				Iter_Add(PemerDuty, playerid);
			}
			case FACTION_BENNYS:
			{
				Iter_Add(BennysDuty, playerid);
			}
			case FACTION_UBER:
			{
				Iter_Add(UberDuty, playerid);
			}
			case FACTION_DINARBUCKS:
			{
				Iter_Add(DinarbucksDuty, playerid);
			}
			case FACTION_FOX11:
			{
				Iter_Add(Fox11Duty, playerid);
			}
			case FACTION_AUTOMAX:
			{
				Iter_Add(AutomaxDuty, playerid);
			}
			case FACTION_HANDOVER:
			{
				Iter_Add(HandoverDuty, playerid);
			}
			case FACTION_SRIMERSING:
			{
				Iter_Add(SriMersingDuty, playerid);
			}
			case FACTION_TEXAS:
			{
				Iter_Add(TexasChickenDuty, playerid);
			}
		}
	}
}

RandomEx(min, max)
{
    return random(max - min) + min;
}

ResetPlayerMoneyEx(playerid)
{
    new rpmex[128];
	AccountData[playerid][pMoney] = 0;
    mysql_format(g_SQL, rpmex, sizeof(rpmex), "UPDATE `player_characters` SET `Char_Money` = %d WHERE `pID` = %d", AccountData[playerid][pMoney], AccountData[playerid][pID]);
    mysql_pquery(g_SQL, rpmex);
	return ResetPlayerMoney(playerid);
}

//Anti Health and Armour Hack
SetPlayerHealthEx(playerid, Float:heal)
{
	new sphex[128];
	if(heal > 0.0)
	{
		AccountData[playerid][pHealth] = heal;
		SetPlayerHealth(playerid, heal);
		
	}
	else
	{
		AccountData[playerid][pHealth] = 10.00;
		SetPlayerHealth(playerid, 0.0);

	}
	mysql_format(g_SQL, sphex, sizeof(sphex), "UPDATE `player_characters` SET `Char_Health` = '%.2f' WHERE `pID` = %d", AccountData[playerid][pHealth], AccountData[playerid][pID]);
	mysql_pquery(g_SQL, sphex);
	return 1;
}

SetPlayerArmourEx(playerid, Float:armor)
{
    new spaex[128];
	Anticheat[playerid][acArmorTime] = gettime() + 11;
	AccountData[playerid][pHasArmor] = true;
	SetPlayerArmour(playerid, armor);
	AccountData[playerid][pArmor] = armor;
	AccountData[playerid][pArmorEmpty] = false;
	
    mysql_format(g_SQL, spaex, sizeof(spaex), "UPDATE `player_characters` SET `Char_Armor` = '%.2f' WHERE `pID` = %d", AccountData[playerid][pArmor], AccountData[playerid][pID]);
	mysql_pquery(g_SQL, spaex);
	return 1;
}

/* NOTIFICATION, TEXT SCRIPT */
ShowKillEffectTD(playerid)
{
    if(AccountData[playerid][pKillEffectTDShown]) 
    {
	    TextDrawHideForPlayer(playerid, KillEffectTD);
	    KillTimer(AccountData[playerid][pKillEffectTimer]);
        AccountData[playerid][pKillEffectTimer] = -1;
	}
	TextDrawShowForPlayer(playerid, KillEffectTD);

	AccountData[playerid][pKillEffectTDShown] = true;
    SetPlayerDrunkLevel(playerid, 4500);
	AccountData[playerid][pKillEffectTimer] = SetTimerEx("HideKillEffTD", 255, false, "d", playerid);
}

ShowNotifBox(playerid, const string[]) 
{
	if(AccountData[playerid][pShowNotifBox]) 
    {
		TextDrawHideForPlayer(playerid, NotifBoxTD[0]);
		TextDrawHideForPlayer(playerid, NotifBoxTD[1]);
		TextDrawHideForPlayer(playerid, NotifBoxTD[2]);
	    PlayerTextDrawHide(playerid, pNotifBoxTD[playerid]);
	}
    PlayerPlaySound(playerid, SOUND_NOTIF_BOX, 0.0, 0.0, 0.0);
	PlayerTextDrawSetString(playerid, pNotifBoxTD[playerid], string);
	TextDrawShowForPlayer(playerid, NotifBoxTD[0]);
	TextDrawShowForPlayer(playerid, NotifBoxTD[1]);
	TextDrawShowForPlayer(playerid, NotifBoxTD[2]);
	PlayerTextDrawShow(playerid, pNotifBoxTD[playerid]);

	AccountData[playerid][pShowNotifBox] = true;
}

HideNotifBox(playerid) 
{
	if (!AccountData[playerid][pShowNotifBox])
	    return 0;
		
	AccountData[playerid][pShowNotifBox] = false;
	TextDrawHideForPlayer(playerid, NotifBoxTD[0]);
	TextDrawHideForPlayer(playerid, NotifBoxTD[1]);
	TextDrawHideForPlayer(playerid, NotifBoxTD[2]);
	PlayerTextDrawHide(playerid, pNotifBoxTD[playerid]);
	return 1;
}

SendRPMeAboveHead(playerid, const messages[])
{
	new sndrpstr[128];
	format(sndrpstr, sizeof(sndrpstr), "* %s", messages);
	SetPlayerChatBubble(playerid, sndrpstr, X11_PLUM1, 30.0, 5000);
 	SendClientMessageEx(playerid, X11_WHITE, "(Action) "PLUM1"%s", messages);
}

KickEx(playerid, time = 1000)
{
	SetTimerEx("_KickPlayerDelayed", time, false, "i", playerid);
	return 1;
}

TakePlayerDirtyMoney(playerid, dirtyval)
{
	new gdss[128];
	AccountData[playerid][pDirtyMoney] -= dirtyval;
	mysql_format(g_SQL, gdss, sizeof(gdss), "UPDATE `player_characters` SET `Char_DirtyMoney` = %d WHERE `pID` = %d", AccountData[playerid][pDirtyMoney], AccountData[playerid][pID]);
    mysql_pquery(g_SQL, gdss);
	return 1;
}

GivePlayerDirtyMoney(playerid, dirtyval)
{
	new gdss[128];
	AccountData[playerid][pDirtyMoney] += dirtyval;
	mysql_format(g_SQL, gdss, sizeof(gdss), "UPDATE `player_characters` SET `Char_DirtyMoney` = %d WHERE `pID` = %d", AccountData[playerid][pDirtyMoney], AccountData[playerid][pID]);
    mysql_pquery(g_SQL, gdss);
	return 1;
}

//Anti Money Hack
GivePlayerMoneyEx(playerid, cashgiven)
{
    new gpmexstr[128];
	AccountData[playerid][pMoney] += cashgiven;
    mysql_format(g_SQL, gpmexstr, sizeof(gpmexstr), "UPDATE `player_characters` SET `Char_Money` = %d WHERE `pID` = %d", AccountData[playerid][pMoney], AccountData[playerid][pID]);
    mysql_pquery(g_SQL, gpmexstr);

	ResetPlayerMoney(playerid);
	return GivePlayerMoney(playerid, AccountData[playerid][pMoney]);
}

TakePlayerMoneyEx(playerid, cashgiven)
{
    new gpmexstr[128];
	AccountData[playerid][pMoney] -= cashgiven;
    mysql_format(g_SQL, gpmexstr, sizeof(gpmexstr), "UPDATE `player_characters` SET `Char_Money` = %d WHERE `pID` = %d", AccountData[playerid][pMoney], AccountData[playerid][pID]);
    mysql_pquery(g_SQL, gpmexstr);
	
	ResetPlayerMoney(playerid);
	return GivePlayerMoney(playerid, AccountData[playerid][pMoney]);
}

isnan(Float:value) 
{
    return (value != value);
}

isinf(Float:value) 
{
    new Float: INF_POSITIVE = 1.0 / 0.0; // Infinity positif
    new Float: INF_NEGATIVE = -1.0 / 0.0; // Infinity negatif

    return (value == INF_POSITIVE || value == INF_NEGATIVE);
}

IsFloatEx(Float:value) 
{
    if (isnan(value) || isinf(value)) 
	{
        // NaN (Not a Number) atau Infinity dianggap tidak valid
        return false;
    } 
	else 
	{
        // Pengecekan tambahan sesuai kebutuhan Anda
        // Misalnya, batasan nilai minimum dan maksimum
        new Float: MIN_VALUE = -1000.0;
        new Float: MAX_VALUE = 1000.0;

        if (value < MIN_VALUE || value > MAX_VALUE) {
            return false;
        }

        // Jika melewati semua pengecekan, nilai dianggap valid
        return true;
    }
}

IsNumericEx(const string[]) 
{
    for (new i = 0, j = strlen(string); i < j; i++)
    {
        if (string[i] > '9' || string[i] < '0') return 0;
    }
    return 1;
}

// IsNumericDotEx(const string[])
// {
//     for (new i = 0, j = strlen(string); i < j; i++)
//     {
//         if ((string[i] > '9' || string[i] < '0') && string[i] != '.') return 0;
//     }
//     return 1;
// }

// FormatMoney(amount, const delimiter[2]=".", const comma[2]=",")
// {
//     #define MAX_MONEY_String 16
//     new txt[MAX_MONEY_String];
//     format(txt, MAX_MONEY_String, "%d", amount);
//     new l = strlen(txt);
//     if (amount < 0) // - value (minus)
//     {
//     	if (l > 2) strins(txt,delimiter,l-2);
//     	if (l > 5) strins(txt,comma,l-5);
//     	if (l > 8) strins(txt,comma,l-8);
//     }
//     else
//     {	//1000000
// 		if (l > 2) strins(txt,delimiter,l-2);
// 		if (l > 5) strins(txt,comma,l-5);
// 		if (l > 8) strins(txt,comma,l-8);
//     }
//     if (l <= 2)
//     {
//         format(txt,sizeof( txt),"0.%s",txt);
//     }
//     else
//     {
//         format(txt,sizeof( txt),"%s",txt);
//     }
//     return txt;
// }

FormatMoney(integer, const delimiter[] = ",") 
{
    new string[16];

    format(string, sizeof string, "%i", integer);

    for (new i = strlen(string) - 3, j = ((integer < 0) ? 1 : 0); i > j; i -= 3) 
	{
        strins(string, delimiter, i, sizeof string);
    }

    return string;
}

GetLocation(Float:fX, Float:fY, Float:fZ)
{
    enum e_ZoneData
    {
        e_ZoneName[32 char],
        Float:e_ZoneArea[6]
    };
    static const g_arrZoneData[][e_ZoneData] =
    {
        {!"The Big Ear",                {-410.00, 1403.30, -3.00, -137.90, 1681.20, 200.00}},
        {!"Aldea Malvada",                {-1372.10, 2498.50, 0.00, -1277.50, 2615.30, 200.00}},
        {!"Angel Pine",                   {-2324.90, -2584.20, -6.10, -1964.20, -2212.10, 200.00}},
        {!"Arco del Oeste",               {-901.10, 2221.80, 0.00, -592.00, 2571.90, 200.00}},
        {!"Avispa Country Club",          {-2646.40, -355.40, 0.00, -2270.00, -222.50, 200.00}},
        {!"Avispa Country Club",          {-2831.80, -430.20, -6.10, -2646.40, -222.50, 200.00}},
        {!"Avispa Country Club",          {-2361.50, -417.10, 0.00, -2270.00, -355.40, 200.00}},
        {!"Avispa Country Club",          {-2667.80, -302.10, -28.80, -2646.40, -262.30, 71.10}},
        {!"Avispa Country Club",          {-2470.00, -355.40, 0.00, -2270.00, -318.40, 46.10}},
        {!"Avispa Country Club",          {-2550.00, -355.40, 0.00, -2470.00, -318.40, 39.70}},
        {!"Back o Beyond",                {-1166.90, -2641.10, 0.00, -321.70, -1856.00, 200.00}},
        {!"Battery Point",                {-2741.00, 1268.40, -4.50, -2533.00, 1490.40, 200.00}},
        {!"Bayside",                      {-2741.00, 2175.10, 0.00, -2353.10, 2722.70, 200.00}},
        {!"Bayside Marina",               {-2353.10, 2275.70, 0.00, -2153.10, 2475.70, 200.00}},
        {!"Beacon Hill",                  {-399.60, -1075.50, -1.40, -319.00, -977.50, 198.50}},
        {!"Blackfield",                   {964.30, 1203.20, -89.00, 1197.30, 1403.20, 110.90}},
        {!"Blackfield",                   {964.30, 1403.20, -89.00, 1197.30, 1726.20, 110.90}},
        {!"Blackfield Chapel",            {1375.60, 596.30, -89.00, 1558.00, 823.20, 110.90}},
        {!"Blackfield Chapel",            {1325.60, 596.30, -89.00, 1375.60, 795.00, 110.90}},
        {!"Blackfield Intersection",      {1197.30, 1044.60, -89.00, 1277.00, 1163.30, 110.90}},
        {!"Blackfield Intersection",      {1166.50, 795.00, -89.00, 1375.60, 1044.60, 110.90}},
        {!"Blackfield Intersection",      {1277.00, 1044.60, -89.00, 1315.30, 1087.60, 110.90}},
        {!"Blackfield Intersection",      {1375.60, 823.20, -89.00, 1457.30, 919.40, 110.90}},
        {!"Blueberry",                    {104.50, -220.10, 2.30, 349.60, 152.20, 200.00}},
        {!"Blueberry",                    {19.60, -404.10, 3.80, 349.60, -220.10, 200.00}},
        {!"Blueberry Acres",              {-319.60, -220.10, 0.00, 104.50, 293.30, 200.00}},
        {!"Caligula's Palace",            {2087.30, 1543.20, -89.00, 2437.30, 1703.20, 110.90}},
        {!"Caligula's Palace",            {2137.40, 1703.20, -89.00, 2437.30, 1783.20, 110.90}},
        {!"Calton Heights",               {-2274.10, 744.10, -6.10, -1982.30, 1358.90, 200.00}},
        {!"Chinatown",                    {-2274.10, 578.30, -7.60, -2078.60, 744.10, 200.00}},
        {!"City Hall",                    {-2867.80, 277.40, -9.10, -2593.40, 458.40, 200.00}},
        {!"Come-A-Lot",                   {2087.30, 943.20, -89.00, 2623.10, 1203.20, 110.90}},
        {!"Commerce",                     {1323.90, -1842.20, -89.00, 1701.90, -1722.20, 110.90}},
        {!"Commerce",                     {1323.90, -1722.20, -89.00, 1440.90, -1577.50, 110.90}},
        {!"Commerce",                     {1370.80, -1577.50, -89.00, 1463.90, -1384.90, 110.90}},
        {!"Commerce",                     {1463.90, -1577.50, -89.00, 1667.90, -1430.80, 110.90}},
        {!"Commerce",                     {1583.50, -1722.20, -89.00, 1758.90, -1577.50, 110.90}},
        {!"Commerce",                     {1667.90, -1577.50, -89.00, 1812.60, -1430.80, 110.90}},
        {!"Conference Center",            {1046.10, -1804.20, -89.00, 1323.90, -1722.20, 110.90}},
        {!"Conference Center",            {1073.20, -1842.20, -89.00, 1323.90, -1804.20, 110.90}},
        {!"Cranberry Station",            {-2007.80, 56.30, 0.00, -1922.00, 224.70, 100.00}},
        {!"Creek",                        {2749.90, 1937.20, -89.00, 2921.60, 2669.70, 110.90}},
        {!"Dillimore",                    {580.70, -674.80, -9.50, 861.00, -404.70, 200.00}},
        {!"Doherty",                      {-2270.00, -324.10, -0.00, -1794.90, -222.50, 200.00}},
        {!"Doherty",                      {-2173.00, -222.50, -0.00, -1794.90, 265.20, 200.00}},
        {!"Downtown",                     {-1982.30, 744.10, -6.10, -1871.70, 1274.20, 200.00}},
        {!"Downtown",                     {-1871.70, 1176.40, -4.50, -1620.30, 1274.20, 200.00}},
        {!"Downtown",                     {-1700.00, 744.20, -6.10, -1580.00, 1176.50, 200.00}},
        {!"Downtown",                     {-1580.00, 744.20, -6.10, -1499.80, 1025.90, 200.00}},
        {!"Downtown",                     {-2078.60, 578.30, -7.60, -1499.80, 744.20, 200.00}},
        {!"Downtown",                     {-1993.20, 265.20, -9.10, -1794.90, 578.30, 200.00}},
        {!"Downtown Los Santos",          {1463.90, -1430.80, -89.00, 1724.70, -1290.80, 110.90}},
        {!"Downtown Los Santos",          {1724.70, -1430.80, -89.00, 1812.60, -1250.90, 110.90}},
        {!"Downtown Los Santos",          {1463.90, -1290.80, -89.00, 1724.70, -1150.80, 110.90}},
        {!"Downtown Los Santos",          {1370.80, -1384.90, -89.00, 1463.90, -1170.80, 110.90}},
        {!"Downtown Los Santos",          {1724.70, -1250.90, -89.00, 1812.60, -1150.80, 110.90}},
        {!"Downtown Los Santos",          {1370.80, -1170.80, -89.00, 1463.90, -1130.80, 110.90}},
        {!"Downtown Los Santos",          {1378.30, -1130.80, -89.00, 1463.90, -1026.30, 110.90}},
        {!"Downtown Los Santos",          {1391.00, -1026.30, -89.00, 1463.90, -926.90, 110.90}},
        {!"Downtown Los Santos",          {1507.50, -1385.20, 110.90, 1582.50, -1325.30, 335.90}},
        {!"East Beach",                   {2632.80, -1852.80, -89.00, 2959.30, -1668.10, 110.90}},
        {!"East Beach",                   {2632.80, -1668.10, -89.00, 2747.70, -1393.40, 110.90}},
        {!"East Beach",                   {2747.70, -1668.10, -89.00, 2959.30, -1498.60, 110.90}},
        {!"East Beach",                   {2747.70, -1498.60, -89.00, 2959.30, -1120.00, 110.90}},
        {!"East Los Santos",              {2421.00, -1628.50, -89.00, 2632.80, -1454.30, 110.90}},
        {!"East Los Santos",              {2222.50, -1628.50, -89.00, 2421.00, -1494.00, 110.90}},
        {!"East Los Santos",              {2266.20, -1494.00, -89.00, 2381.60, -1372.00, 110.90}},
        {!"East Los Santos",              {2381.60, -1494.00, -89.00, 2421.00, -1454.30, 110.90}},
        {!"East Los Santos",              {2281.40, -1372.00, -89.00, 2381.60, -1135.00, 110.90}},
        {!"East Los Santos",              {2381.60, -1454.30, -89.00, 2462.10, -1135.00, 110.90}},
        {!"East Los Santos",              {2462.10, -1454.30, -89.00, 2581.70, -1135.00, 110.90}},
        {!"Easter Basin",                 {-1794.90, 249.90, -9.10, -1242.90, 578.30, 200.00}},
        {!"Easter Basin",                 {-1794.90, -50.00, -0.00, -1499.80, 249.90, 200.00}},
        {!"Easter Bay Airport",           {-1499.80, -50.00, -0.00, -1242.90, 249.90, 200.00}},
        {!"Easter Bay Airport",           {-1794.90, -730.10, -3.00, -1213.90, -50.00, 200.00}},
        {!"Easter Bay Airport",           {-1213.90, -730.10, 0.00, -1132.80, -50.00, 200.00}},
        {!"Easter Bay Airport",           {-1242.90, -50.00, 0.00, -1213.90, 578.30, 200.00}},
        {!"Easter Bay Airport",           {-1213.90, -50.00, -4.50, -947.90, 578.30, 200.00}},
        {!"Easter Bay Airport",           {-1315.40, -405.30, 15.40, -1264.40, -209.50, 25.40}},
        {!"Easter Bay Airport",           {-1354.30, -287.30, 15.40, -1315.40, -209.50, 25.40}},
        {!"Easter Bay Airport",           {-1490.30, -209.50, 15.40, -1264.40, -148.30, 25.40}},
        {!"Easter Bay Chemicals",         {-1132.80, -768.00, 0.00, -956.40, -578.10, 200.00}},
        {!"Easter Bay Chemicals",         {-1132.80, -787.30, 0.00, -956.40, -768.00, 200.00}},
        {!"El Castillo del Diablo",       {-464.50, 2217.60, 0.00, -208.50, 2580.30, 200.00}},
        {!"El Castillo del Diablo",       {-208.50, 2123.00, -7.60, 114.00, 2337.10, 200.00}},
        {!"El Castillo del Diablo",       {-208.50, 2337.10, 0.00, 8.40, 2487.10, 200.00}},
        {!"El Corona",                    {1812.60, -2179.20, -89.00, 1970.60, -1852.80, 110.90}},
        {!"El Corona",                    {1692.60, -2179.20, -89.00, 1812.60, -1842.20, 110.90}},
        {!"El Quebrados",                 {-1645.20, 2498.50, 0.00, -1372.10, 2777.80, 200.00}},
        {!"Esplanade East",               {-1620.30, 1176.50, -4.50, -1580.00, 1274.20, 200.00}},
        {!"Esplanade East",               {-1580.00, 1025.90, -6.10, -1499.80, 1274.20, 200.00}},
        {!"Esplanade East",               {-1499.80, 578.30, -79.60, -1339.80, 1274.20, 20.30}},
        {!"Esplanade North",              {-2533.00, 1358.90, -4.50, -1996.60, 1501.20, 200.00}},
        {!"Esplanade North",              {-1996.60, 1358.90, -4.50, -1524.20, 1592.50, 200.00}},
        {!"Esplanade North",              {-1982.30, 1274.20, -4.50, -1524.20, 1358.90, 200.00}},
        {!"Fallen Tree",                  {-792.20, -698.50, -5.30, -452.40, -380.00, 200.00}},
        {!"Fallow Bridge",                {434.30, 366.50, 0.00, 603.00, 555.60, 200.00}},
        {!"Fern Ridge",                   {508.10, -139.20, 0.00, 1306.60, 119.50, 200.00}},
        {!"Financial",                    {-1871.70, 744.10, -6.10, -1701.30, 1176.40, 300.00}},
        {!"Fisher's Lagoon",              {1916.90, -233.30, -100.00, 2131.70, 13.80, 200.00}},
        {!"Flint Intersection",           {-187.70, -1596.70, -89.00, 17.00, -1276.60, 110.90}},
        {!"Flint Range",                  {-594.10, -1648.50, 0.00, -187.70, -1276.60, 200.00}},
        {!"Fort Carson",                  {-376.20, 826.30, -3.00, 123.70, 1220.40, 200.00}},
        {!"Foster Valley",                {-2270.00, -430.20, -0.00, -2178.60, -324.10, 200.00}},
        {!"Foster Valley",                {-2178.60, -599.80, -0.00, -1794.90, -324.10, 200.00}},
        {!"Foster Valley",                {-2178.60, -1115.50, 0.00, -1794.90, -599.80, 200.00}},
        {!"Foster Valley",                {-2178.60, -1250.90, 0.00, -1794.90, -1115.50, 200.00}},
        {!"Frederick Bridge",             {2759.20, 296.50, 0.00, 2774.20, 594.70, 200.00}},
        {!"Gant Bridge",                  {-2741.40, 1659.60, -6.10, -2616.40, 2175.10, 200.00}},
        {!"Gant Bridge",                  {-2741.00, 1490.40, -6.10, -2616.40, 1659.60, 200.00}},
        {!"Ganton",                       {2222.50, -1852.80, -89.00, 2632.80, -1722.30, 110.90}},
        {!"Ganton",                       {2222.50, -1722.30, -89.00, 2632.80, -1628.50, 110.90}},
        {!"Garcia",                       {-2411.20, -222.50, -0.00, -2173.00, 265.20, 200.00}},
        {!"Garcia",                       {-2395.10, -222.50, -5.30, -2354.00, -204.70, 200.00}},
        {!"Garver Bridge",                {-1339.80, 828.10, -89.00, -1213.90, 1057.00, 110.90}},
        {!"Garver Bridge",                {-1213.90, 950.00, -89.00, -1087.90, 1178.90, 110.90}},
        {!"Garver Bridge",                {-1499.80, 696.40, -179.60, -1339.80, 925.30, 20.30}},
        {!"Glen Park",                    {1812.60, -1449.60, -89.00, 1996.90, -1350.70, 110.90}},
        {!"Glen Park",                    {1812.60, -1100.80, -89.00, 1994.30, -973.30, 110.90}},
        {!"Glen Park",                    {1812.60, -1350.70, -89.00, 2056.80, -1100.80, 110.90}},
        {!"Green Palms",                  {176.50, 1305.40, -3.00, 338.60, 1520.70, 200.00}},
        {!"Greenglass College",           {964.30, 1044.60, -89.00, 1197.30, 1203.20, 110.90}},
        {!"Greenglass College",           {964.30, 930.80, -89.00, 1166.50, 1044.60, 110.90}},
        {!"Hampton Barns",                {603.00, 264.30, 0.00, 761.90, 366.50, 200.00}},
        {!"Hankypanky Point",             {2576.90, 62.10, 0.00, 2759.20, 385.50, 200.00}},
        {!"Harry Gold Parkway",           {1777.30, 863.20, -89.00, 1817.30, 2342.80, 110.90}},
        {!"Hashbury",                     {-2593.40, -222.50, -0.00, -2411.20, 54.70, 200.00}},
        {!"Hilltop Farm",                 {967.30, -450.30, -3.00, 1176.70, -217.90, 200.00}},
        {!"Hunter Quarry",                {337.20, 710.80, -115.20, 860.50, 1031.70, 203.70}},
        {!"Idlewood",                     {1812.60, -1852.80, -89.00, 1971.60, -1742.30, 110.90}},
        {!"Idlewood",                     {1812.60, -1742.30, -89.00, 1951.60, -1602.30, 110.90}},
        {!"Idlewood",                     {1951.60, -1742.30, -89.00, 2124.60, -1602.30, 110.90}},
        {!"Idlewood",                     {1812.60, -1602.30, -89.00, 2124.60, -1449.60, 110.90}},
        {!"Idlewood",                     {2124.60, -1742.30, -89.00, 2222.50, -1494.00, 110.90}},
        {!"Idlewood",                     {1971.60, -1852.80, -89.00, 2222.50, -1742.30, 110.90}},
        {!"Jefferson",                    {1996.90, -1449.60, -89.00, 2056.80, -1350.70, 110.90}},
        {!"Jefferson",                    {2124.60, -1494.00, -89.00, 2266.20, -1449.60, 110.90}},
        {!"Jefferson",                    {2056.80, -1372.00, -89.00, 2281.40, -1210.70, 110.90}},
        {!"Jefferson",                    {2056.80, -1210.70, -89.00, 2185.30, -1126.30, 110.90}},
        {!"Jefferson",                    {2185.30, -1210.70, -89.00, 2281.40, -1154.50, 110.90}},
        {!"Jefferson",                    {2056.80, -1449.60, -89.00, 2266.20, -1372.00, 110.90}},
        {!"Julius Thruway East",          {2623.10, 943.20, -89.00, 2749.90, 1055.90, 110.90}},
        {!"Julius Thruway East",          {2685.10, 1055.90, -89.00, 2749.90, 2626.50, 110.90}},
        {!"Julius Thruway East",          {2536.40, 2442.50, -89.00, 2685.10, 2542.50, 110.90}},
        {!"Julius Thruway East",          {2625.10, 2202.70, -89.00, 2685.10, 2442.50, 110.90}},
        {!"Julius Thruway North",         {2498.20, 2542.50, -89.00, 2685.10, 2626.50, 110.90}},
        {!"Julius Thruway North",         {2237.40, 2542.50, -89.00, 2498.20, 2663.10, 110.90}},
        {!"Julius Thruway North",         {2121.40, 2508.20, -89.00, 2237.40, 2663.10, 110.90}},
        {!"Julius Thruway North",         {1938.80, 2508.20, -89.00, 2121.40, 2624.20, 110.90}},
        {!"Julius Thruway North",         {1534.50, 2433.20, -89.00, 1848.40, 2583.20, 110.90}},
        {!"Julius Thruway North",         {1848.40, 2478.40, -89.00, 1938.80, 2553.40, 110.90}},
        {!"Julius Thruway North",         {1704.50, 2342.80, -89.00, 1848.40, 2433.20, 110.90}},
        {!"Julius Thruway North",         {1377.30, 2433.20, -89.00, 1534.50, 2507.20, 110.90}},
        {!"Julius Thruway South",         {1457.30, 823.20, -89.00, 2377.30, 863.20, 110.90}},
        {!"Julius Thruway South",         {2377.30, 788.80, -89.00, 2537.30, 897.90, 110.90}},
        {!"Julius Thruway West",          {1197.30, 1163.30, -89.00, 1236.60, 2243.20, 110.90}},
        {!"Julius Thruway West",          {1236.60, 2142.80, -89.00, 1297.40, 2243.20, 110.90}},
        {!"Juniper Hill",                 {-2533.00, 578.30, -7.60, -2274.10, 968.30, 200.00}},
        {!"Juniper Hollow",               {-2533.00, 968.30, -6.10, -2274.10, 1358.90, 200.00}},
        {!"K.A.C.C. Military Fuels",      {2498.20, 2626.50, -89.00, 2749.90, 2861.50, 110.90}},
        {!"Kincaid Bridge",               {-1339.80, 599.20, -89.00, -1213.90, 828.10, 110.90}},
        {!"Kincaid Bridge",               {-1213.90, 721.10, -89.00, -1087.90, 950.00, 110.90}},
        {!"Kincaid Bridge",               {-1087.90, 855.30, -89.00, -961.90, 986.20, 110.90}},
        {!"King's",                       {-2329.30, 458.40, -7.60, -1993.20, 578.30, 200.00}},
        {!"King's",                       {-2411.20, 265.20, -9.10, -1993.20, 373.50, 200.00}},
        {!"King's",                       {-2253.50, 373.50, -9.10, -1993.20, 458.40, 200.00}},
        {!"LVA Freight Depot",            {1457.30, 863.20, -89.00, 1777.40, 1143.20, 110.90}},
        {!"LVA Freight Depot",            {1375.60, 919.40, -89.00, 1457.30, 1203.20, 110.90}},
        {!"LVA Freight Depot",            {1277.00, 1087.60, -89.00, 1375.60, 1203.20, 110.90}},
        {!"LVA Freight Depot",            {1315.30, 1044.60, -89.00, 1375.60, 1087.60, 110.90}},
        {!"LVA Freight Depot",            {1236.60, 1163.40, -89.00, 1277.00, 1203.20, 110.90}},
        {!"Las Barrancas",                {-926.10, 1398.70, -3.00, -719.20, 1634.60, 200.00}},
        {!"Las Brujas",                   {-365.10, 2123.00, -3.00, -208.50, 2217.60, 200.00}},
        {!"Las Colinas",                  {1994.30, -1100.80, -89.00, 2056.80, -920.80, 110.90}},
        {!"Las Colinas",                  {2056.80, -1126.30, -89.00, 2126.80, -920.80, 110.90}},
        {!"Las Colinas",                  {2185.30, -1154.50, -89.00, 2281.40, -934.40, 110.90}},
        {!"Las Colinas",                  {2126.80, -1126.30, -89.00, 2185.30, -934.40, 110.90}},
        {!"Las Colinas",                  {2747.70, -1120.00, -89.00, 2959.30, -945.00, 110.90}},
        {!"Las Colinas",                  {2632.70, -1135.00, -89.00, 2747.70, -945.00, 110.90}},
        {!"Las Colinas",                  {2281.40, -1135.00, -89.00, 2632.70, -945.00, 110.90}},
        {!"Las Payasadas",                {-354.30, 2580.30, 2.00, -133.60, 2816.80, 200.00}},
        {!"Las Venturas Airport",         {1236.60, 1203.20, -89.00, 1457.30, 1883.10, 110.90}},
        {!"Las Venturas Airport",         {1457.30, 1203.20, -89.00, 1777.30, 1883.10, 110.90}},
        {!"Las Venturas Airport",         {1457.30, 1143.20, -89.00, 1777.40, 1203.20, 110.90}},
        {!"Las Venturas Airport",         {1515.80, 1586.40, -12.50, 1729.90, 1714.50, 87.50}},
        {!"Last Dime Motel",              {1823.00, 596.30, -89.00, 1997.20, 823.20, 110.90}},
        {!"Leafy Hollow",                 {-1166.90, -1856.00, 0.00, -815.60, -1602.00, 200.00}},
        {!"Liberty City",                 {-1000.00, 400.00, 1300.00, -700.00, 600.00, 1400.00}},
        {!"Lil' Probe Inn",               {-90.20, 1286.80, -3.00, 153.80, 1554.10, 200.00}},
        {!"Linden Side",                  {2749.90, 943.20, -89.00, 2923.30, 1198.90, 110.90}},
        {!"Linden Station",               {2749.90, 1198.90, -89.00, 2923.30, 1548.90, 110.90}},
        {!"Linden Station",               {2811.20, 1229.50, -39.50, 2861.20, 1407.50, 60.40}},
        {!"Little Mexico",                {1701.90, -1842.20, -89.00, 1812.60, -1722.20, 110.90}},
        {!"Little Mexico",                {1758.90, -1722.20, -89.00, 1812.60, -1577.50, 110.90}},
        {!"Los Flores",                   {2581.70, -1454.30, -89.00, 2632.80, -1393.40, 110.90}},
        {!"Los Flores",                   {2581.70, -1393.40, -89.00, 2747.70, -1135.00, 110.90}},
        {!"Los Santos International",     {1249.60, -2394.30, -89.00, 1852.00, -2179.20, 110.90}},
        {!"Los Santos International",     {1852.00, -2394.30, -89.00, 2089.00, -2179.20, 110.90}},
        {!"Los Santos International",     {1382.70, -2730.80, -89.00, 2201.80, -2394.30, 110.90}},
        {!"Los Santos International",     {1974.60, -2394.30, -39.00, 2089.00, -2256.50, 60.90}},
        {!"Los Santos International",     {1400.90, -2669.20, -39.00, 2189.80, -2597.20, 60.90}},
        {!"Los Santos International",     {2051.60, -2597.20, -39.00, 2152.40, -2394.30, 60.90}},
        {!"Marina",                       {647.70, -1804.20, -89.00, 851.40, -1577.50, 110.90}},
        {!"Marina",                       {647.70, -1577.50, -89.00, 807.90, -1416.20, 110.90}},
        {!"Marina",                       {807.90, -1577.50, -89.00, 926.90, -1416.20, 110.90}},
        {!"Market",                       {787.40, -1416.20, -89.00, 1072.60, -1310.20, 110.90}},
        {!"Market",                       {952.60, -1310.20, -89.00, 1072.60, -1130.80, 110.90}},
        {!"Market",                       {1072.60, -1416.20, -89.00, 1370.80, -1130.80, 110.90}},
        {!"Market",                       {926.90, -1577.50, -89.00, 1370.80, -1416.20, 110.90}},
        {!"Market Station",               {787.40, -1410.90, -34.10, 866.00, -1310.20, 65.80}},
        {!"Martin Bridge",                {-222.10, 293.30, 0.00, -122.10, 476.40, 200.00}},
        {!"Missionary Hill",              {-2994.40, -811.20, 0.00, -2178.60, -430.20, 200.00}},
        {!"Montgomery",                   {1119.50, 119.50, -3.00, 1451.40, 493.30, 200.00}},
        {!"Montgomery",                   {1451.40, 347.40, -6.10, 1582.40, 420.80, 200.00}},
        {!"Montgomery Intersection",      {1546.60, 208.10, 0.00, 1745.80, 347.40, 200.00}},
        {!"Montgomery Intersection",      {1582.40, 347.40, 0.00, 1664.60, 401.70, 200.00}},
        {!"Mulholland",                   {1414.00, -768.00, -89.00, 1667.60, -452.40, 110.90}},
        {!"Mulholland",                   {1281.10, -452.40, -89.00, 1641.10, -290.90, 110.90}},
        {!"Mulholland",                   {1269.10, -768.00, -89.00, 1414.00, -452.40, 110.90}},
        {!"Mulholland",                   {1357.00, -926.90, -89.00, 1463.90, -768.00, 110.90}},
        {!"Mulholland",                   {1318.10, -910.10, -89.00, 1357.00, -768.00, 110.90}},
        {!"Mulholland",                   {1169.10, -910.10, -89.00, 1318.10, -768.00, 110.90}},
        {!"Mulholland",                   {768.60, -954.60, -89.00, 952.60, -860.60, 110.90}},
        {!"Mulholland",                   {687.80, -860.60, -89.00, 911.80, -768.00, 110.90}},
        {!"Mulholland",                   {737.50, -768.00, -89.00, 1142.20, -674.80, 110.90}},
        {!"Mulholland",                   {1096.40, -910.10, -89.00, 1169.10, -768.00, 110.90}},
        {!"Mulholland",                   {952.60, -937.10, -89.00, 1096.40, -860.60, 110.90}},
        {!"Mulholland",                   {911.80, -860.60, -89.00, 1096.40, -768.00, 110.90}},
        {!"Mulholland",                   {861.00, -674.80, -89.00, 1156.50, -600.80, 110.90}},
        {!"Mulholland Intersection",      {1463.90, -1150.80, -89.00, 1812.60, -768.00, 110.90}},
        {!"North Rock",                   {2285.30, -768.00, 0.00, 2770.50, -269.70, 200.00}},
        {!"Ocean Docks",                  {2373.70, -2697.00, -89.00, 2809.20, -2330.40, 110.90}},
        {!"Ocean Docks",                  {2201.80, -2418.30, -89.00, 2324.00, -2095.00, 110.90}},
        {!"Ocean Docks",                  {2324.00, -2302.30, -89.00, 2703.50, -2145.10, 110.90}},
        {!"Ocean Docks",                  {2089.00, -2394.30, -89.00, 2201.80, -2235.80, 110.90}},
        {!"Ocean Docks",                  {2201.80, -2730.80, -89.00, 2324.00, -2418.30, 110.90}},
        {!"Ocean Docks",                  {2703.50, -2302.30, -89.00, 2959.30, -2126.90, 110.90}},
        {!"Ocean Docks",                  {2324.00, -2145.10, -89.00, 2703.50, -2059.20, 110.90}},
        {!"Ocean Flats",                  {-2994.40, 277.40, -9.10, -2867.80, 458.40, 200.00}},
        {!"Ocean Flats",                  {-2994.40, -222.50, -0.00, -2593.40, 277.40, 200.00}},
        {!"Ocean Flats",                  {-2994.40, -430.20, -0.00, -2831.80, -222.50, 200.00}},
        {!"Octane Springs",               {338.60, 1228.50, 0.00, 664.30, 1655.00, 200.00}},
        {!"Old Venturas Strip",           {2162.30, 2012.10, -89.00, 2685.10, 2202.70, 110.90}},
        {!"Palisades",                    {-2994.40, 458.40, -6.10, -2741.00, 1339.60, 200.00}},
        {!"Palomino Creek",               {2160.20, -149.00, 0.00, 2576.90, 228.30, 200.00}},
        {!"Paradiso",                     {-2741.00, 793.40, -6.10, -2533.00, 1268.40, 200.00}},
        {!"Pershing Square",              {1440.90, -1722.20, -89.00, 1583.50, -1577.50, 110.90}},
        {!"Pilgrim",                      {2437.30, 1383.20, -89.00, 2624.40, 1783.20, 110.90}},
        {!"Pilgrim",                      {2624.40, 1383.20, -89.00, 2685.10, 1783.20, 110.90}},
        {!"Pilson Intersection",          {1098.30, 2243.20, -89.00, 1377.30, 2507.20, 110.90}},
        {!"Pirates in Men's Pants",       {1817.30, 1469.20, -89.00, 2027.40, 1703.20, 110.90}},
        {!"Playa del Seville",            {2703.50, -2126.90, -89.00, 2959.30, -1852.80, 110.90}},
        {!"Prickle Pine",                 {1534.50, 2583.20, -89.00, 1848.40, 2863.20, 110.90}},
        {!"Prickle Pine",                 {1117.40, 2507.20, -89.00, 1534.50, 2723.20, 110.90}},
        {!"Prickle Pine",                 {1848.40, 2553.40, -89.00, 1938.80, 2863.20, 110.90}},
        {!"Prickle Pine",                 {1938.80, 2624.20, -89.00, 2121.40, 2861.50, 110.90}},
        {!"Queens",                       {-2533.00, 458.40, 0.00, -2329.30, 578.30, 200.00}},
        {!"Queens",                       {-2593.40, 54.70, 0.00, -2411.20, 458.40, 200.00}},
        {!"Queens",                       {-2411.20, 373.50, 0.00, -2253.50, 458.40, 200.00}},
        {!"Randolph Industrial Estate",   {1558.00, 596.30, -89.00, 1823.00, 823.20, 110.90}},
        {!"Redsands East",                {1817.30, 2011.80, -89.00, 2106.70, 2202.70, 110.90}},
        {!"Redsands East",                {1817.30, 2202.70, -89.00, 2011.90, 2342.80, 110.90}},
        {!"Redsands East",                {1848.40, 2342.80, -89.00, 2011.90, 2478.40, 110.90}},
        {!"Redsands West",                {1236.60, 1883.10, -89.00, 1777.30, 2142.80, 110.90}},
        {!"Redsands West",                {1297.40, 2142.80, -89.00, 1777.30, 2243.20, 110.90}},
        {!"Redsands West",                {1377.30, 2243.20, -89.00, 1704.50, 2433.20, 110.90}},
        {!"Redsands West",                {1704.50, 2243.20, -89.00, 1777.30, 2342.80, 110.90}},
        {!"Regular Tom",                  {-405.70, 1712.80, -3.00, -276.70, 1892.70, 200.00}},
        {!"Richman",                      {647.50, -1118.20, -89.00, 787.40, -954.60, 110.90}},
        {!"Richman",                      {647.50, -954.60, -89.00, 768.60, -860.60, 110.90}},
        {!"Richman",                      {225.10, -1369.60, -89.00, 334.50, -1292.00, 110.90}},
        {!"Richman",                      {225.10, -1292.00, -89.00, 466.20, -1235.00, 110.90}},
        {!"Richman",                      {72.60, -1404.90, -89.00, 225.10, -1235.00, 110.90}},
        {!"Richman",                      {72.60, -1235.00, -89.00, 321.30, -1008.10, 110.90}},
        {!"Richman",                      {321.30, -1235.00, -89.00, 647.50, -1044.00, 110.90}},
        {!"Richman",                      {321.30, -1044.00, -89.00, 647.50, -860.60, 110.90}},
        {!"Richman",                      {321.30, -860.60, -89.00, 687.80, -768.00, 110.90}},
        {!"Richman",                      {321.30, -768.00, -89.00, 700.70, -674.80, 110.90}},
        {!"Robada Intersection",          {-1119.00, 1178.90, -89.00, -862.00, 1351.40, 110.90}},
        {!"Roca Escalante",               {2237.40, 2202.70, -89.00, 2536.40, 2542.50, 110.90}},
        {!"Roca Escalante",               {2536.40, 2202.70, -89.00, 2625.10, 2442.50, 110.90}},
        {!"Rockshore East",               {2537.30, 676.50, -89.00, 2902.30, 943.20, 110.90}},
        {!"Rockshore West",               {1997.20, 596.30, -89.00, 2377.30, 823.20, 110.90}},
        {!"Rockshore West",               {2377.30, 596.30, -89.00, 2537.30, 788.80, 110.90}},
        {!"Rodeo",                        {72.60, -1684.60, -89.00, 225.10, -1544.10, 110.90}},
        {!"Rodeo",                        {72.60, -1544.10, -89.00, 225.10, -1404.90, 110.90}},
        {!"Rodeo",                        {225.10, -1684.60, -89.00, 312.80, -1501.90, 110.90}},
        {!"Rodeo",                        {225.10, -1501.90, -89.00, 334.50, -1369.60, 110.90}},
        {!"Rodeo",                        {334.50, -1501.90, -89.00, 422.60, -1406.00, 110.90}},
        {!"Rodeo",                        {312.80, -1684.60, -89.00, 422.60, -1501.90, 110.90}},
        {!"Rodeo",                        {422.60, -1684.60, -89.00, 558.00, -1570.20, 110.90}},
        {!"Rodeo",                        {558.00, -1684.60, -89.00, 647.50, -1384.90, 110.90}},
        {!"Rodeo",                        {466.20, -1570.20, -89.00, 558.00, -1385.00, 110.90}},
        {!"Rodeo",                        {422.60, -1570.20, -89.00, 466.20, -1406.00, 110.90}},
        {!"Rodeo",                        {466.20, -1385.00, -89.00, 647.50, -1235.00, 110.90}},
        {!"Rodeo",                        {334.50, -1406.00, -89.00, 466.20, -1292.00, 110.90}},
        {!"Royal Casino",                 {2087.30, 1383.20, -89.00, 2437.30, 1543.20, 110.90}},
        {!"San Andreas Sound",            {2450.30, 385.50, -100.00, 2759.20, 562.30, 200.00}},
        {!"Santa Flora",                  {-2741.00, 458.40, -7.60, -2533.00, 793.40, 200.00}},
        {!"Santa Maria Beach",            {342.60, -2173.20, -89.00, 647.70, -1684.60, 110.90}},
        {!"Santa Maria Beach",            {72.60, -2173.20, -89.00, 342.60, -1684.60, 110.90}},
        {!"Shady Cabin",                  {-1632.80, -2263.40, -3.00, -1601.30, -2231.70, 200.00}},
        {!"Shady Creeks",                 {-1820.60, -2643.60, -8.00, -1226.70, -1771.60, 200.00}},
        {!"Shady Creeks",                 {-2030.10, -2174.80, -6.10, -1820.60, -1771.60, 200.00}},
        {!"Sobell Rail Yards",            {2749.90, 1548.90, -89.00, 2923.30, 1937.20, 110.90}},
        {!"Spinybed",                     {2121.40, 2663.10, -89.00, 2498.20, 2861.50, 110.90}},
        {!"Starfish Casino",              {2437.30, 1783.20, -89.00, 2685.10, 2012.10, 110.90}},
        {!"Starfish Casino",              {2437.30, 1858.10, -39.00, 2495.00, 1970.80, 60.90}},
        {!"Starfish Casino",              {2162.30, 1883.20, -89.00, 2437.30, 2012.10, 110.90}},
        {!"Temple",                       {1252.30, -1130.80, -89.00, 1378.30, -1026.30, 110.90}},
        {!"Temple",                       {1252.30, -1026.30, -89.00, 1391.00, -926.90, 110.90}},
        {!"Temple",                       {1252.30, -926.90, -89.00, 1357.00, -910.10, 110.90}},
        {!"Temple",                       {952.60, -1130.80, -89.00, 1096.40, -937.10, 110.90}},
        {!"Temple",                       {1096.40, -1130.80, -89.00, 1252.30, -1026.30, 110.90}},
        {!"Temple",                       {1096.40, -1026.30, -89.00, 1252.30, -910.10, 110.90}},
        {!"The Camel's Toe",              {2087.30, 1203.20, -89.00, 2640.40, 1383.20, 110.90}},
        {!"The Clown's Pocket",           {2162.30, 1783.20, -89.00, 2437.30, 1883.20, 110.90}},
        {!"The Emerald Isle",             {2011.90, 2202.70, -89.00, 2237.40, 2508.20, 110.90}},
        {!"The Farm",                     {-1209.60, -1317.10, 114.90, -908.10, -787.30, 251.90}},
        {!"The Four Dragons Casino",      {1817.30, 863.20, -89.00, 2027.30, 1083.20, 110.90}},
        {!"The High Roller",              {1817.30, 1283.20, -89.00, 2027.30, 1469.20, 110.90}},
        {!"The Mako Span",                {1664.60, 401.70, 0.00, 1785.10, 567.20, 200.00}},
        {!"The Panopticon",               {-947.90, -304.30, -1.10, -319.60, 327.00, 200.00}},
        {!"The Pink Swan",                {1817.30, 1083.20, -89.00, 2027.30, 1283.20, 110.90}},
        {!"The Sherman Dam",              {-968.70, 1929.40, -3.00, -481.10, 2155.20, 200.00}},
        {!"The Strip",                    {2027.40, 863.20, -89.00, 2087.30, 1703.20, 110.90}},
        {!"The Strip",                    {2106.70, 1863.20, -89.00, 2162.30, 2202.70, 110.90}},
        {!"The Strip",                    {2027.40, 1783.20, -89.00, 2162.30, 1863.20, 110.90}},
        {!"The Strip",                    {2027.40, 1703.20, -89.00, 2137.40, 1783.20, 110.90}},
        {!"The Visage",                   {1817.30, 1863.20, -89.00, 2106.70, 2011.80, 110.90}},
        {!"The Visage",                   {1817.30, 1703.20, -89.00, 2027.40, 1863.20, 110.90}},
        {!"Unity Station",                {1692.60, -1971.80, -20.40, 1812.60, -1932.80, 79.50}},
        {!"Valle Ocultado",               {-936.60, 2611.40, 2.00, -715.90, 2847.90, 200.00}},
        {!"Verdant Bluffs",               {930.20, -2488.40, -89.00, 1249.60, -2006.70, 110.90}},
        {!"Verdant Bluffs",               {1073.20, -2006.70, -89.00, 1249.60, -1842.20, 110.90}},
        {!"Verdant Bluffs",               {1249.60, -2179.20, -89.00, 1692.60, -1842.20, 110.90}},
        {!"Verdant Meadows",              {37.00, 2337.10, -3.00, 435.90, 2677.90, 200.00}},
        {!"Verona Beach",                 {647.70, -2173.20, -89.00, 930.20, -1804.20, 110.90}},
        {!"Verona Beach",                 {930.20, -2006.70, -89.00, 1073.20, -1804.20, 110.90}},
        {!"Verona Beach",                 {851.40, -1804.20, -89.00, 1046.10, -1577.50, 110.90}},
        {!"Verona Beach",                 {1161.50, -1722.20, -89.00, 1323.90, -1577.50, 110.90}},
        {!"Verona Beach",                 {1046.10, -1722.20, -89.00, 1161.50, -1577.50, 110.90}},
        {!"Vinewood",                     {787.40, -1310.20, -89.00, 952.60, -1130.80, 110.90}},
        {!"Vinewood",                     {787.40, -1130.80, -89.00, 952.60, -954.60, 110.90}},
        {!"Vinewood",                     {647.50, -1227.20, -89.00, 787.40, -1118.20, 110.90}},
        {!"Vinewood",                     {647.70, -1416.20, -89.00, 787.40, -1227.20, 110.90}},
        {!"Whitewood Estates",            {883.30, 1726.20, -89.00, 1098.30, 2507.20, 110.90}},
        {!"Whitewood Estates",            {1098.30, 1726.20, -89.00, 1197.30, 2243.20, 110.90}},
        {!"Willowfield",                  {1970.60, -2179.20, -89.00, 2089.00, -1852.80, 110.90}},
        {!"Willowfield",                  {2089.00, -2235.80, -89.00, 2201.80, -1989.90, 110.90}},
        {!"Willowfield",                  {2089.00, -1989.90, -89.00, 2324.00, -1852.80, 110.90}},
        {!"Willowfield",                  {2201.80, -2095.00, -89.00, 2324.00, -1989.90, 110.90}},
        {!"Willowfield",                  {2541.70, -1941.40, -89.00, 2703.50, -1852.80, 110.90}},
        {!"Willowfield",                  {2324.00, -2059.20, -89.00, 2541.70, -1852.80, 110.90}},
        {!"Willowfield",                  {2541.70, -2059.20, -89.00, 2703.50, -1941.40, 110.90}},
        {!"Yellow Bell Station",          {1377.40, 2600.40, -21.90, 1492.40, 2687.30, 78.00}},
        {!"Los Santos",                   {44.60, -2892.90, -242.90, 2997.00, -768.00, 900.00}},
        {!"Las Venturas",                 {869.40, 596.30, -242.90, 2997.00, 2993.80, 900.00}},
        {!"Bone County",                  {-480.50, 596.30, -242.90, 869.40, 2993.80, 900.00}},
        {!"Tierra Robada",                {-2997.40, 1659.60, -242.90, -480.50, 2993.80, 900.00}},
        {!"Tierra Robada",                {-1213.90, 596.30, -242.90, -480.50, 1659.60, 900.00}},
        {!"San Fierro",                   {-2997.40, -1115.50, -242.90, -1213.90, 1659.60, 900.00}},
        {!"Red County",                   {-1213.90, -768.00, -242.90, 2997.00, 596.30, 900.00}},
        {!"Flint County",                 {-1213.90, -2892.90, -242.90, 44.60, -768.00, 900.00}},
        {!"Whetstone",                    {-2997.40, -2892.90, -242.90, -1213.90, -1115.50, 900.00}}
    };
    new name[32] = "San Andreas";

    for (new i = 0; i != sizeof(g_arrZoneData); i ++) if ((fX >= g_arrZoneData[i][e_ZoneArea][0] && fX <= g_arrZoneData[i][e_ZoneArea][3]) && (fY >= g_arrZoneData[i][e_ZoneArea][1] && fY <= g_arrZoneData[i][e_ZoneArea][4]) && (fZ >= g_arrZoneData[i][e_ZoneArea][2] && fZ <= g_arrZoneData[i][e_ZoneArea][5]))
        {
            strunpack(name, g_arrZoneData[i][e_ZoneName]);

            break;
        }
    return name;
}

GetStreetLocation(Float:fX, Float:fY, Float:fZ)
{
    enum e_ZoneData
    {
        e_ZoneName[32 char],
        Float:e_ZoneArea[6]
    };
    static const g_arrZoneData[][e_ZoneData] =
    {
        {!"Observatory Drive",                {-410.00, 1403.30, -3.00, -137.90, 1681.20, 200.00}},
        {!"Shadow Canyon Road",                {-1372.10, 2498.50, 0.00, -1277.50, 2615.30, 200.00}},
        {!"Angel Pine Road",                   {-2324.90, -2584.20, -6.10, -1964.20, -2212.10, 200.00}},
        {!"Western Arch Drive",               {-901.10, 2221.80, 0.00, -592.00, 2571.90, 200.00}},
        {!"Avispa Estates Drive",          {-2646.40, -355.40, 0.00, -2270.00, -222.50, 200.00}},
        {!"Avispa Estates Drive",          {-2831.80, -430.20, -6.10, -2646.40, -222.50, 200.00}},
        {!"Avispa Estates Drive",          {-2361.50, -417.10, 0.00, -2270.00, -355.40, 200.00}},
        {!"Avispa Estates Drive",          {-2667.80, -302.10, -28.80, -2646.40, -262.30, 71.10}},
        {!"Avispa Estates Drive",          {-2470.00, -355.40, 0.00, -2270.00, -318.40, 46.10}},
        {!"Avispa Estates Drive",          {-2550.00, -355.40, 0.00, -2470.00, -318.40, 39.70}},
        {!"Back o Beyond Road",                {-1166.90, -2641.10, 0.00, -321.70, -1856.00, 200.00}},
        {!"Battery Spencer Trail",                {-2741.00, 1268.40, -4.50, -2533.00, 1490.40, 200.00}},
        {!"Bayside Drive",                      {-2741.00, 2175.10, 0.00, -2353.10, 2722.70, 200.00}},
        {!"Bayside Marina Drive",               {-2353.10, 2275.70, 0.00, -2153.10, 2475.70, 200.00}},
        {!"Nob Hill",                  {-399.60, -1075.50, -1.40, -319.00, -977.50, 198.50}},
        {!"Blackfield Road",                   {964.30, 1203.20, -89.00, 1197.30, 1403.20, 110.90}},
        {!"Blackfield Road",                   {964.30, 1403.20, -89.00, 1197.30, 1726.20, 110.90}},
        {!"Blackfield Chapel Road",            {1375.60, 596.30, -89.00, 1558.00, 823.20, 110.90}},
        {!"Blackfield Chapel Road",            {1325.60, 596.30, -89.00, 1375.60, 795.00, 110.90}},
        {!"Blackfield Intersection Road",      {1197.30, 1044.60, -89.00, 1277.00, 1163.30, 110.90}},
        {!"Blackfield Intersection Road",      {1166.50, 795.00, -89.00, 1375.60, 1044.60, 110.90}},
        {!"Blackfield Intersection Road",      {1277.00, 1044.60, -89.00, 1315.30, 1087.60, 110.90}},
        {!"Blackfield Intersection Road",      {1375.60, 823.20, -89.00, 1457.30, 919.40, 110.90}},
        {!"Blueberry Boulevard",                    {104.50, -220.10, 2.30, 349.60, 152.20, 200.00}},
        {!"Blueberry Boulevard",                    {19.60, -404.10, 3.80, 349.60, -220.10, 200.00}},
        {!"Blueberry Acres Boulevard",              {-319.60, -220.10, 0.00, 104.50, 293.30, 200.00}},
        {!"Imperial Avenue",            {2087.30, 1543.20, -89.00, 2437.30, 1703.20, 110.90}},
        {!"Imperial Avenue",            {2137.40, 1703.20, -89.00, 2437.30, 1783.20, 110.90}},
        {!"Carlton Drive",               {-2274.10, 744.10, -6.10, -1982.30, 1358.90, 200.00}},
        {!"Dragon Street",                    {-2274.10, 578.30, -7.60, -2078.60, 744.10, 200.00}},
        {!"Civic Plaza",                    {-2867.80, 277.40, -9.10, -2593.40, 458.40, 200.00}},
        {!"Earn-A-Lot Street",                   {2087.30, 943.20, -89.00, 2623.10, 1203.20, 110.90}},
        {!"Commerce Drive",                     {1323.90, -1842.20, -89.00, 1701.90, -1722.20, 110.90}},
        {!"Commerce Drive",                     {1323.90, -1722.20, -89.00, 1440.90, -1577.50, 110.90}},
        {!"Commerce Drive",                     {1370.80, -1577.50, -89.00, 1463.90, -1384.90, 110.90}},
        {!"Commerce Drive",                     {1463.90, -1577.50, -89.00, 1667.90, -1430.80, 110.90}},
        {!"Commerce Drive",                     {1583.50, -1722.20, -89.00, 1758.90, -1577.50, 110.90}},
        {!"Commerce Drive",                     {1667.90, -1577.50, -89.00, 1812.60, -1430.80, 110.90}},
        {!"Convention Street",            {1046.10, -1804.20, -89.00, 1323.90, -1722.20, 110.90}},
        {!"Convention Street",            {1073.20, -1842.20, -89.00, 1323.90, -1804.20, 110.90}},
        {!"Cranberry Station",            {-2007.80, 56.30, 0.00, -1922.00, 224.70, 100.00}},
        {!"Cedar Creek Drive",                        {2749.90, 1937.20, -89.00, 2921.60, 2669.70, 110.90}},
        {!"Hillford Avenue",                    {580.70, -674.80, -9.50, 861.00, -404.70, 200.00}},
        {!"Dorchester Street",                      {-2270.00, -324.10, -0.00, -1794.90, -222.50, 200.00}},
        {!"Dorchester Street",                      {-2173.00, -222.50, -0.00, -1794.90, 265.20, 200.00}},
        {!"Urban Hub Boulevard",                     {-1982.30, 744.10, -6.10, -1871.70, 1274.20, 200.00}},
        {!"Urban Hub Boulevard",                     {-1871.70, 1176.40, -4.50, -1620.30, 1274.20, 200.00}},
        {!"Urban Hub Boulevard",                     {-1700.00, 744.20, -6.10, -1580.00, 1176.50, 200.00}},
        {!"Urban Hub Boulevard",                     {-1580.00, 744.20, -6.10, -1499.80, 1025.90, 200.00}},
        {!"Urban Hub Boulevard",                     {-2078.60, 578.30, -7.60, -1499.80, 744.20, 200.00}},
        {!"Urban Hub Boulevard",                     {-1993.20, 265.20, -9.10, -1794.90, 578.30, 200.00}},
        {!"Urban Boulevard",          {1463.90, -1430.80, -89.00, 1724.70, -1290.80, 110.90}},
        {!"Urban Boulevard",          {1724.70, -1430.80, -89.00, 1812.60, -1250.90, 110.90}},
        {!"Urban Boulevard",          {1463.90, -1290.80, -89.00, 1724.70, -1150.80, 110.90}},
        {!"Urban Boulevard",          {1370.80, -1384.90, -89.00, 1463.90, -1170.80, 110.90}},
        {!"Urban Boulevard",          {1724.70, -1250.90, -89.00, 1812.60, -1150.80, 110.90}},
        {!"Urban Boulevard",          {1370.80, -1170.80, -89.00, 1463.90, -1130.80, 110.90}},
        {!"Urban Boulevard",          {1378.30, -1130.80, -89.00, 1463.90, -1026.30, 110.90}},
        {!"Urban Boulevard",          {1391.00, -1026.30, -89.00, 1463.90, -926.90, 110.90}},
        {!"Urban Boulevard",          {1507.50, -1385.20, 110.90, 1582.50, -1325.30, 335.90}},
        {!"Palm Beach Drive",                   {2632.80, -1852.80, -89.00, 2959.30, -1668.10, 110.90}},
        {!"Palm Beach Drive",                   {2632.80, -1668.10, -89.00, 2747.70, -1393.40, 110.90}},
        {!"Palm Beach Drive",                   {2747.70, -1668.10, -89.00, 2959.30, -1498.60, 110.90}},
        {!"Palm Beach Drive",                   {2747.70, -1498.60, -89.00, 2959.30, -1120.00, 110.90}},
        {!"Los Palmas Avenue",              {2421.00, -1628.50, -89.00, 2632.80, -1454.30, 110.90}},
        {!"Los Palmas Avenue",              {2222.50, -1628.50, -89.00, 2421.00, -1494.00, 110.90}},
        {!"Los Palmas Avenue",              {2266.20, -1494.00, -89.00, 2381.60, -1372.00, 110.90}},
        {!"Los Palmas Avenue",              {2381.60, -1494.00, -89.00, 2421.00, -1454.30, 110.90}},
        {!"Los Palmas Avenue",              {2281.40, -1372.00, -89.00, 2381.60, -1135.00, 110.90}},
        {!"Los Palmas Avenue",              {2381.60, -1454.30, -89.00, 2462.10, -1135.00, 110.90}},
        {!"Los Palmas Avenue",              {2462.10, -1454.30, -89.00, 2581.70, -1135.00, 110.90}},
        {!"East Port Avenue",                 {-1794.90, 249.90, -9.10, -1242.90, 578.30, 200.00}},
        {!"East Port Avenue",                 {-1794.90, -50.00, -0.00, -1499.80, 249.90, 200.00}},
        {!"Easter Bay Airport",           {-1499.80, -50.00, -0.00, -1242.90, 249.90, 200.00}},
        {!"Easter Bay Airport",           {-1794.90, -730.10, -3.00, -1213.90, -50.00, 200.00}},
        {!"Easter Bay Airport",           {-1213.90, -730.10, 0.00, -1132.80, -50.00, 200.00}},
        {!"Easter Bay Airport",           {-1242.90, -50.00, 0.00, -1213.90, 578.30, 200.00}},
        {!"Easter Bay Airport",           {-1213.90, -50.00, -4.50, -947.90, 578.30, 200.00}},
        {!"Easter Bay Airport",           {-1315.40, -405.30, 15.40, -1264.40, -209.50, 25.40}},
        {!"Easter Bay Airport",           {-1354.30, -287.30, 15.40, -1315.40, -209.50, 25.40}},
        {!"Easter Bay Airport",           {-1490.30, -209.50, 15.40, -1264.40, -148.30, 25.40}},
        {!"Bayview Chemicals Avenue",         {-1132.80, -768.00, 0.00, -956.40, -578.10, 200.00}},
        {!"Bayview Chemicals Avenue",         {-1132.80, -787.30, 0.00, -956.40, -768.00, 200.00}},
        {!"Diablo Ridge Road",       {-464.50, 2217.60, 0.00, -208.50, 2580.30, 200.00}},
        {!"Diablo Ridge Road",       {-208.50, 2123.00, -7.60, 114.00, 2337.10, 200.00}},
        {!"Diablo Ridge Road",       {-208.50, 2337.10, 0.00, 8.40, 2487.10, 200.00}},
        {!"Mariposa Avenue",                    {1812.60, -2179.20, -89.00, 1970.60, -1852.80, 110.90}},
        {!"Mariposa Avenue",                    {1692.60, -2179.20, -89.00, 1812.60, -1842.20, 110.90}},
        {!"Quebrados Street",                 {-1645.20, 2498.50, 0.00, -1372.10, 2777.80, 200.00}},
        {!"Riverside Drive",               {-1620.30, 1176.50, -4.50, -1580.00, 1274.20, 200.00}},
        {!"Riverside Drive",               {-1580.00, 1025.90, -6.10, -1499.80, 1274.20, 200.00}},
        {!"Riverside Drive",               {-1499.80, 578.30, -79.60, -1339.80, 1274.20, 20.30}},
        {!"Riverside Avenue",              {-2533.00, 1358.90, -4.50, -1996.60, 1501.20, 200.00}},
        {!"Riverside Avenue",              {-1996.60, 1358.90, -4.50, -1524.20, 1592.50, 200.00}},
        {!"Riverside Avenue",              {-1982.30, 1274.20, -4.50, -1524.20, 1358.90, 200.00}},
        {!"Evergreen Lane",                  {-792.20, -698.50, -5.30, -452.40, -380.00, 200.00}},
        {!"Meadow Crossing",                {434.30, 366.50, 0.00, 603.00, 555.60, 200.00}},
        {!"Fernwood Lane",                   {508.10, -139.20, 0.00, 1306.60, 119.50, 200.00}},
        {!"Finance Avenue",                    {-1871.70, 744.10, -6.10, -1701.30, 1176.40, 300.00}},
        {!"Angler's Cove Lane",              {1916.90, -233.30, -100.00, 2131.70, 13.80, 200.00}},
        {!"Flint Intersection",           {-187.70, -1596.70, -89.00, 17.00, -1276.60, 110.90}},
        {!"Flint Range Avenue",                  {-594.10, -1648.50, 0.00, -187.70, -1276.60, 200.00}},
        {!"Rustic Canyon Drive",                  {-376.20, 826.30, -3.00, 123.70, 1220.40, 200.00}},
        {!"Green Valley Avenue",                {-2270.00, -430.20, -0.00, -2178.60, -324.10, 200.00}},
        {!"Green Valley Avenue",                {-2178.60, -599.80, -0.00, -1794.90, -324.10, 200.00}},
        {!"Green Valley Avenue",                {-2178.60, -1115.50, 0.00, -1794.90, -599.80, 200.00}},
        {!"Green Valley Avenue",                {-2178.60, -1250.90, 0.00, -1794.90, -1115.50, 200.00}},
        {!"Gregory Viaduct",             {2759.20, 296.50, 0.00, 2774.20, 594.70, 200.00}},
        {!"Linkspan Boulevard",                  {-2741.40, 1659.60, -6.10, -2616.40, 2175.10, 200.00}},
        {!"Linkspan Boulevard",                  {-2741.00, 1490.40, -6.10, -2616.40, 1659.60, 200.00}},
        {!"Grove Street",                       {2222.50, -1852.80, -89.00, 2632.80, -1722.30, 110.90}},
        {!"Grove Street",                       {2222.50, -1722.30, -89.00, 2632.80, -1628.50, 110.90}},
        {!"Garcia Boulevard",                       {-2411.20, -222.50, -0.00, -2173.00, 265.20, 200.00}},
        {!"Garcia Boulevard",                       {-2395.10, -222.50, -5.30, -2354.00, -204.70, 200.00}},
        {!"Bridgeford Way",                {-1339.80, 828.10, -89.00, -1213.90, 1057.00, 110.90}},
        {!"Bridgeford Way",                {-1213.90, 950.00, -89.00, -1087.90, 1178.90, 110.90}},
        {!"Bridgeford Way",                {-1499.80, 696.40, -179.60, -1339.80, 925.30, 20.30}},
        {!"Glenwood Street",                    {1812.60, -1449.60, -89.00, 1996.90, -1350.70, 110.90}},
        {!"Glenwood Street",                    {1812.60, -1100.80, -89.00, 1994.30, -973.30, 110.90}},
        {!"Glenwood Street",                    {1812.60, -1350.70, -89.00, 2056.80, -1100.80, 110.90}},
        {!"Palm Lane",                  {176.50, 1305.40, -3.00, 338.60, 1520.70, 200.00}},
        {!"Palm Tree Drive",           {964.30, 1044.60, -89.00, 1197.30, 1203.20, 110.90}},
        {!"Palm Tree Drivee",           {964.30, 930.80, -89.00, 1166.50, 1044.60, 110.90}},
        {!"Outskirts Boulevard",                {603.00, 264.30, 0.00, 761.90, 366.50, 200.00}},
        {!"Sweetheart Lane",             {2576.90, 62.10, 0.00, 2759.20, 385.50, 200.00}},
        {!"Sahara Avenue",           {1777.30, 863.20, -89.00, 1817.30, 2342.80, 110.90}},
        {!"Haight-Ashbury Street",                     {-2593.40, -222.50, -0.00, -2411.20, 54.70, 200.00}},
        {!"Dillimore Farm Road",                 {967.30, -450.30, -3.00, 1176.70, -217.90, 200.00}},
        {!"Hunter Quarry Road",                {337.20, 710.80, -115.20, 860.50, 1031.70, 203.70}},
        {!"Crenshaw Boulevard",                     {1812.60, -1852.80, -89.00, 1971.60, -1742.30, 110.90}},
        {!"Crenshaw Boulevard",                     {1812.60, -1742.30, -89.00, 1951.60, -1602.30, 110.90}},
        {!"Crenshaw Boulevard",                     {1951.60, -1742.30, -89.00, 2124.60, -1602.30, 110.90}},
        {!"Crenshaw Boulevard",                     {1812.60, -1602.30, -89.00, 2124.60, -1449.60, 110.90}},
        {!"Crenshaw Boulevard",                     {2124.60, -1742.30, -89.00, 2222.50, -1494.00, 110.90}},
        {!"Crenshaw Boulevard",                     {1971.60, -1852.80, -89.00, 2222.50, -1742.30, 110.90}},
        {!"Slauson Avenue",             {1996.90, -1449.60, -89.00, 2056.80, -1350.70, 110.90}},
        {!"Slauson Avenue",             {2124.60, -1494.00, -89.00, 2266.20, -1449.60, 110.90}},
        {!"Slauson Avenue",             {2056.80, -1372.00, -89.00, 2281.40, -1210.70, 110.90}},
        {!"Slauson Avenue",             {2056.80, -1210.70, -89.00, 2185.30, -1126.30, 110.90}},
        {!"Slauson Avenue",             {2185.30, -1210.70, -89.00, 2281.40, -1154.50, 110.90}},
        {!"Slauson Avenue",             {2056.80, -1449.60, -89.00, 2266.20, -1372.00, 110.90}},
        {!"East Side Highway",          {2623.10, 943.20, -89.00, 2749.90, 1055.90, 110.90}},
        {!"East Side Highway",          {2685.10, 1055.90, -89.00, 2749.90, 2626.50, 110.90}},
        {!"East Side Highway",          {2536.40, 2442.50, -89.00, 2685.10, 2542.50, 110.90}},
        {!"East Side Highway",          {2625.10, 2202.70, -89.00, 2685.10, 2442.50, 110.90}},
        {!"North Side Highway",         {2498.20, 2542.50, -89.00, 2685.10, 2626.50, 110.90}},
        {!"North Side Highway",         {2237.40, 2542.50, -89.00, 2498.20, 2663.10, 110.90}},
        {!"North Side Highway",         {2121.40, 2508.20, -89.00, 2237.40, 2663.10, 110.90}},
        {!"North Side Highway",         {1938.80, 2508.20, -89.00, 2121.40, 2624.20, 110.90}},
        {!"North Side Highway",         {1534.50, 2433.20, -89.00, 1848.40, 2583.20, 110.90}},
        {!"North Side Highway",         {1848.40, 2478.40, -89.00, 1938.80, 2553.40, 110.90}},
        {!"North Side Highway",         {1704.50, 2342.80, -89.00, 1848.40, 2433.20, 110.90}},
        {!"North Side Highway",         {1377.30, 2433.20, -89.00, 1534.50, 2507.20, 110.90}},
        {!"South Side Highway",         {1457.30, 823.20, -89.00, 2377.30, 863.20, 110.90}},
        {!"South Side Highway",         {2377.30, 788.80, -89.00, 2537.30, 897.90, 110.90}},
        {!"West Side Highway",          {1197.30, 1163.30, -89.00, 1236.60, 2243.20, 110.90}},
        {!"West Side Highway",          {1236.60, 2142.80, -89.00, 1297.40, 2243.20, 110.90}},
        {!"Lombard Street",                 {-2533.00, 578.30, -7.60, -2274.10, 968.30, 200.00}},
        {!"Lombard Hollow Street",               {-2533.00, 968.30, -6.10, -2274.10, 1358.90, 200.00}},
        {!"Petroleum Base Road",      {2498.20, 2626.50, -89.00, 2749.90, 2861.50, 110.90}},
        {!"Golden Gate Bridge",               {-1339.80, 599.20, -89.00, -1213.90, 828.10, 110.90}},
        {!"Golden Gate Bridge",               {-1213.90, 721.10, -89.00, -1087.90, 950.00, 110.90}},
        {!"Golden Gate Bridge",               {-1087.90, 855.30, -89.00, -961.90, 986.20, 110.90}},
        {!"Castro Street",                       {-2329.30, 458.40, -7.60, -1993.20, 578.30, 200.00}},
        {!"Castro Street",                       {-2411.20, 265.20, -9.10, -1993.20, 373.50, 200.00}},
        {!"Castro Street",                       {-2253.50, 373.50, -9.10, -1993.20, 458.40, 200.00}},
        {!"Freight Street",            {1457.30, 863.20, -89.00, 1777.40, 1143.20, 110.90}},
        {!"Freight Street",            {1375.60, 919.40, -89.00, 1457.30, 1203.20, 110.90}},
        {!"Freight Street",            {1277.00, 1087.60, -89.00, 1375.60, 1203.20, 110.90}},
        {!"Freight Street",            {1315.30, 1044.60, -89.00, 1375.60, 1087.60, 110.90}},
        {!"Freight Street",            {1236.60, 1163.40, -89.00, 1277.00, 1203.20, 110.90}},
        {!"Cliffside Drive",                {-926.10, 1398.70, -3.00, -719.20, 1634.60, 200.00}},
        {!"Haunted Hill Road",                   {-365.10, 2123.00, -3.00, -208.50, 2217.60, 200.00}},
        {!"Glendale Boulevard",                  {1994.30, -1100.80, -89.00, 2056.80, -920.80, 110.90}},
        {!"Glendale Boulevard",                  {2056.80, -1126.30, -89.00, 2126.80, -920.80, 110.90}},
        {!"Glendale Boulevard",                  {2185.30, -1154.50, -89.00, 2281.40, -934.40, 110.90}},
        {!"Glendale Boulevard",                  {2126.80, -1126.30, -89.00, 2185.30, -934.40, 110.90}},
        {!"Glendale Boulevard",                  {2747.70, -1120.00, -89.00, 2959.30, -945.00, 110.90}},
        {!"Glendale Boulevard",                  {2632.70, -1135.00, -89.00, 2747.70, -945.00, 110.90}},
        {!"Glendale Boulevard",                  {2281.40, -1135.00, -89.00, 2632.70, -945.00, 110.90}},
        {!"Palmetto Road",                {-354.30, 2580.30, 2.00, -133.60, 2816.80, 200.00}},
        {!"Las Venturas Airport",         {1236.60, 1203.20, -89.00, 1457.30, 1883.10, 110.90}},
        {!"Las Venturas Airport",         {1457.30, 1203.20, -89.00, 1777.30, 1883.10, 110.90}},
        {!"Las Venturas Airport",         {1457.30, 1143.20, -89.00, 1777.40, 1203.20, 110.90}},
        {!"Las Venturas Airport",         {1515.80, 1586.40, -12.50, 1729.90, 1714.50, 87.50}},
        {!"Cheap Street",              {1823.00, 596.30, -89.00, 1997.20, 823.20, 110.90}},
        {!"Cedar Lane",                 {-1166.90, -1856.00, 0.00, -815.60, -1602.00, 200.00}},
        {!"Liberty City",                 {-1000.00, 400.00, 1300.00, -700.00, 600.00, 1400.00}},
        {!"Spaceship Way",               {-90.20, 1286.80, -3.00, 153.80, 1554.10, 200.00}},
        {!"Linden Side",                  {2749.90, 943.20, -89.00, 2923.30, 1198.90, 110.90}},
        {!"Linden Station",               {2749.90, 1198.90, -89.00, 2923.30, 1548.90, 110.90}},
        {!"Linden Station",               {2811.20, 1229.50, -39.50, 2861.20, 1407.50, 60.40}},
        {!"Olvera Street",                {1701.90, -1842.20, -89.00, 1812.60, -1722.20, 110.90}},
        {!"Olvera Street",                {1758.90, -1722.20, -89.00, 1812.60, -1577.50, 110.90}},
        {!"Beverly Boulevard",                   {2581.70, -1454.30, -89.00, 2632.80, -1393.40, 110.90}},
        {!"Beverly Boulevard",                   {2581.70, -1393.40, -89.00, 2747.70, -1135.00, 110.90}},
        {!"Los Santos International",     {1249.60, -2394.30, -89.00, 1852.00, -2179.20, 110.90}},
        {!"Los Santos International",     {1852.00, -2394.30, -89.00, 2089.00, -2179.20, 110.90}},
        {!"Los Santos International",     {1382.70, -2730.80, -89.00, 2201.80, -2394.30, 110.90}},
        {!"Los Santos International",     {1974.60, -2394.30, -39.00, 2089.00, -2256.50, 60.90}},
        {!"Los Santos International",     {1400.90, -2669.20, -39.00, 2189.80, -2597.20, 60.90}},
        {!"Los Santos International",     {2051.60, -2597.20, -39.00, 2152.40, -2394.30, 60.90}},
        {!"Marina Drive",                       {647.70, -1804.20, -89.00, 851.40, -1577.50, 110.90}},
        {!"Marina Drive",                       {647.70, -1577.50, -89.00, 807.90, -1416.20, 110.90}},
        {!"Marina Drive",                       {807.90, -1577.50, -89.00, 926.90, -1416.20, 110.90}},
        {!"Fifth Avenue",                       {787.40, -1416.20, -89.00, 1072.60, -1310.20, 110.90}},
        {!"Fifth Avenue",                       {952.60, -1310.20, -89.00, 1072.60, -1130.80, 110.90}},
        {!"Fifth Avenue",                       {1072.60, -1416.20, -89.00, 1370.80, -1130.80, 110.90}},
        {!"Fifth Avenue",                       {926.90, -1577.50, -89.00, 1370.80, -1416.20, 110.90}},
        {!"Market Station",               {787.40, -1410.90, -34.10, 866.00, -1310.20, 65.80}},
        {!"Martin Bridge",                {-222.10, 293.30, 0.00, -122.10, 476.40, 200.00}},
        {!"Sutro Tower Road",              {-2994.40, -811.20, 0.00, -2178.60, -430.20, 200.00}},
        {!"Montgomery Boulevard",                   {1119.50, 119.50, -3.00, 1451.40, 493.30, 200.00}},
        {!"Montgomery Boulevard",                   {1451.40, 347.40, -6.10, 1582.40, 420.80, 200.00}},
        {!"Montgomery Intersection",      {1546.60, 208.10, 0.00, 1745.80, 347.40, 200.00}},
        {!"Montgomery Intersection",      {1582.40, 347.40, 0.00, 1664.60, 401.70, 200.00}},
        {!"Mulholland Drive",                   {1414.00, -768.00, -89.00, 1667.60, -452.40, 110.90}},
        {!"Mulholland Drive",                   {1281.10, -452.40, -89.00, 1641.10, -290.90, 110.90}},
        {!"Mulholland Drive",                   {1269.10, -768.00, -89.00, 1414.00, -452.40, 110.90}},
        {!"Mulholland Drive",                   {1357.00, -926.90, -89.00, 1463.90, -768.00, 110.90}},
        {!"Mulholland Drive",                   {1318.10, -910.10, -89.00, 1357.00, -768.00, 110.90}},
        {!"Mulholland Drive",                   {1169.10, -910.10, -89.00, 1318.10, -768.00, 110.90}},
        {!"Mulholland Drive",                   {768.60, -954.60, -89.00, 952.60, -860.60, 110.90}},
        {!"Mulholland Drive",                   {687.80, -860.60, -89.00, 911.80, -768.00, 110.90}},
        {!"Mulholland Drive",                   {737.50, -768.00, -89.00, 1142.20, -674.80, 110.90}},
        {!"Mulholland Drive",                   {1096.40, -910.10, -89.00, 1169.10, -768.00, 110.90}},
        {!"Mulholland Drive",                   {952.60, -937.10, -89.00, 1096.40, -860.60, 110.90}},
        {!"Mulholland Drive",                   {911.80, -860.60, -89.00, 1096.40, -768.00, 110.90}},
        {!"Mulholland Drive",                   {861.00, -674.80, -89.00, 1156.50, -600.80, 110.90}},
        {!"Mulholland Intersection",      {1463.90, -1150.80, -89.00, 1812.60, -768.00, 110.90}},
        {!"Green Mountain Boulevard",                   {2285.30, -768.00, 0.00, 2770.50, -269.70, 200.00}},
        {!"Ocean Boulevard",                  {2373.70, -2697.00, -89.00, 2809.20, -2330.40, 110.90}},
        {!"Ocean Boulevard",                  {2201.80, -2418.30, -89.00, 2324.00, -2095.00, 110.90}},
        {!"Ocean Boulevard",                  {2324.00, -2302.30, -89.00, 2703.50, -2145.10, 110.90}},
        {!"Ocean Boulevard",                  {2089.00, -2394.30, -89.00, 2201.80, -2235.80, 110.90}},
        {!"Ocean Boulevard",                  {2201.80, -2730.80, -89.00, 2324.00, -2418.30, 110.90}},
        {!"Ocean Boulevard",                  {2703.50, -2302.30, -89.00, 2959.30, -2126.90, 110.90}},
        {!"Ocean Boulevard",                  {2324.00, -2145.10, -89.00, 2703.50, -2059.20, 110.90}},
        {!"Ocean Avenue",                  {-2994.40, 277.40, -9.10, -2867.80, 458.40, 200.00}},
        {!"Ocean Avenue",                  {-2994.40, -222.50, -0.00, -2593.40, 277.40, 200.00}},
        {!"Ocean Avenue",                  {-2994.40, -430.20, -0.00, -2831.80, -222.50, 200.00}},
        {!"Oilfield Road",               {338.60, 1228.50, 0.00, 664.30, 1655.00, 200.00}},
        {!"Fremont Street",           {2162.30, 2012.10, -89.00, 2685.10, 2202.70, 110.90}},
        {!"Palisades Heights",                    {-2994.40, 458.40, -6.10, -2741.00, 1339.60, 200.00}},
        {!"Palomino Creek Road",               {2160.20, -149.00, 0.00, 2576.90, 228.30, 200.00}},
        {!"Presidio Heights",                     {-2741.00, 793.40, -6.10, -2533.00, 1268.40, 200.00}},
        {!"Central Park Avenue",              {1440.90, -1722.20, -89.00, 1583.50, -1577.50, 110.90}},
        {!"Chinatown",                      {2437.30, 1383.20, -89.00, 2624.40, 1783.20, 110.90}},
        {!"Chinatown",                      {2624.40, 1383.20, -89.00, 2685.10, 1783.20, 110.90}},
        {!"Pilson Intersection",          {1098.30, 2243.20, -89.00, 1377.30, 2507.20, 110.90}},
        {!"Treasure Island Boulevard",       {1817.30, 1469.20, -89.00, 2027.40, 1703.20, 110.90}},
        {!"Seville Boulevard",            {2703.50, -2126.90, -89.00, 2959.30, -1852.80, 110.90}},
        {!"Prickle Pine Street",                 {1534.50, 2583.20, -89.00, 1848.40, 2863.20, 110.90}},
        {!"Prickle Pine Street",                 {1117.40, 2507.20, -89.00, 1534.50, 2723.20, 110.90}},
        {!"Prickle Pine Street",                 {1848.40, 2553.40, -89.00, 1938.80, 2863.20, 110.90}},
        {!"Prickle Pine Street",                 {1938.80, 2624.20, -89.00, 2121.40, 2861.50, 110.90}},
        {!"Church Street",                       {-2533.00, 458.40, 0.00, -2329.30, 578.30, 200.00}},
        {!"Church Street",                       {-2593.40, 54.70, 0.00, -2411.20, 458.40, 200.00}},
        {!"Church Street",                       {-2411.20, 373.50, 0.00, -2253.50, 458.40, 200.00}},
        {!"Industrial Avenue",   {1558.00, 596.30, -89.00, 1823.00, 823.20, 110.90}},
        {!"Redsands East Avenue",                {1817.30, 2011.80, -89.00, 2106.70, 2202.70, 110.90}},
        {!"Redsands East Avenue",                {1817.30, 2202.70, -89.00, 2011.90, 2342.80, 110.90}},
        {!"Redsands East Avenue",                {1848.40, 2342.80, -89.00, 2011.90, 2478.40, 110.90}},
        {!"Redsands West Avenue",                {1236.60, 1883.10, -89.00, 1777.30, 2142.80, 110.90}},
        {!"Redsands West Avenue",                {1297.40, 2142.80, -89.00, 1777.30, 2243.20, 110.90}},
        {!"Redsands West Avenue",                {1377.30, 2243.20, -89.00, 1704.50, 2433.20, 110.90}},
        {!"Redsands West Avenue",                {1704.50, 2243.20, -89.00, 1777.30, 2342.80, 110.90}},
        {!"Geyser Road",                  {-405.70, 1712.80, -3.00, -276.70, 1892.70, 200.00}},
        {!"Laurel Canyon Boulevard",                      {647.50, -1118.20, -89.00, 787.40, -954.60, 110.90}},
        {!"Laurel Canyon Boulevard",                      {647.50, -954.60, -89.00, 768.60, -860.60, 110.90}},
        {!"Laurel Canyon Boulevard",                      {225.10, -1369.60, -89.00, 334.50, -1292.00, 110.90}},
        {!"Laurel Canyon Boulevard",                      {225.10, -1292.00, -89.00, 466.20, -1235.00, 110.90}},
        {!"Laurel Canyon Boulevard",                      {72.60, -1404.90, -89.00, 225.10, -1235.00, 110.90}},
        {!"Laurel Canyon Boulevard",                      {72.60, -1235.00, -89.00, 321.30, -1008.10, 110.90}},
        {!"Laurel Canyon Boulevard",                      {321.30, -1235.00, -89.00, 647.50, -1044.00, 110.90}},
        {!"Laurel Canyon Boulevard",                      {321.30, -1044.00, -89.00, 647.50, -860.60, 110.90}},
        {!"Laurel Canyon Boulevard",                      {321.30, -860.60, -89.00, 687.80, -768.00, 110.90}},
        {!"Laurel Canyon Boulevard",                      {321.30, -768.00, -89.00, 700.70, -674.80, 110.90}},
        {!"Robada Intersection",          {-1119.00, 1178.90, -89.00, -862.00, 1351.40, 110.90}},
        {!"Flamingo Road",               {2237.40, 2202.70, -89.00, 2536.40, 2542.50, 110.90}},
        {!"Flamingo Road",               {2536.40, 2202.70, -89.00, 2625.10, 2442.50, 110.90}},
        {!"Rockland Street",               {2537.30, 676.50, -89.00, 2902.30, 943.20, 110.90}},
        {!"Rockland Street",               {1997.20, 596.30, -89.00, 2377.30, 823.20, 110.90}},
        {!"Rockland Street",               {2377.30, 596.30, -89.00, 2537.30, 788.80, 110.90}},
        {!"Beverly Drive",                        {72.60, -1684.60, -89.00, 225.10, -1544.10, 110.90}},
        {!"Beverly Drive",                        {72.60, -1544.10, -89.00, 225.10, -1404.90, 110.90}},
        {!"Beverly Drive",                        {225.10, -1684.60, -89.00, 312.80, -1501.90, 110.90}},
        {!"Beverly Drive",                        {225.10, -1501.90, -89.00, 334.50, -1369.60, 110.90}},
        {!"Beverly Drive",                        {334.50, -1501.90, -89.00, 422.60, -1406.00, 110.90}},
        {!"Beverly Drive",                        {312.80, -1684.60, -89.00, 422.60, -1501.90, 110.90}},
        {!"Beverly Drive",                        {422.60, -1684.60, -89.00, 558.00, -1570.20, 110.90}},
        {!"Beverly Drive",                        {558.00, -1684.60, -89.00, 647.50, -1384.90, 110.90}},
        {!"Beverly Drive",                        {466.20, -1570.20, -89.00, 558.00, -1385.00, 110.90}},
        {!"Beverly Drive",                        {422.60, -1570.20, -89.00, 466.20, -1406.00, 110.90}},
        {!"Beverly Drive",                        {466.20, -1385.00, -89.00, 647.50, -1235.00, 110.90}},
        {!"Beverly Drive",                        {334.50, -1406.00, -89.00, 466.20, -1292.00, 110.90}},
        {!"Royal Casino Road",                 {2087.30, 1383.20, -89.00, 2437.30, 1543.20, 110.90}},
        {!"San Andreas Sound",            {2450.30, 385.50, -100.00, 2759.20, 562.30, 200.00}},
        {!"Melrose Avenue",                  {-2741.00, 458.40, -7.60, -2533.00, 793.40, 200.00}},
        {!"Santa Monica Boulevard",            {342.60, -2173.20, -89.00, 647.70, -1684.60, 110.90}},
        {!"Santa Monica Boulevard",            {72.60, -2173.20, -89.00, 342.60, -1684.60, 110.90}},
        {!"Dark Forest Road",                  {-1632.80, -2263.40, -3.00, -1601.30, -2231.70, 200.00}},
        {!"Dark Forest Road",                 {-1820.60, -2643.60, -8.00, -1226.70, -1771.60, 200.00}},
        {!"Dark Forest Road",                 {-2030.10, -2174.80, -6.10, -1820.60, -1771.60, 200.00}},
        {!"Railroad Yard",            {2749.90, 1548.90, -89.00, 2923.30, 1937.20, 110.90}},
        {!"Industrial Road",                     {2121.40, 2663.10, -89.00, 2498.20, 2861.50, 110.90}},
        {!"Starfish Casino Road",              {2437.30, 1783.20, -89.00, 2685.10, 2012.10, 110.90}},
        {!"Starfish Casino Road",              {2437.30, 1858.10, -39.00, 2495.00, 1970.80, 60.90}},
        {!"Starfish Casino Road",              {2162.30, 1883.20, -89.00, 2437.30, 2012.10, 110.90}},
        {!"Wilshire Boulevard",                       {1252.30, -1130.80, -89.00, 1378.30, -1026.30, 110.90}},
        {!"Wilshire Boulevard",                       {1252.30, -1026.30, -89.00, 1391.00, -926.90, 110.90}},
        {!"Wilshire Boulevard",                       {1252.30, -926.90, -89.00, 1357.00, -910.10, 110.90}},
        {!"Wilshire Boulevard",                       {952.60, -1130.80, -89.00, 1096.40, -937.10, 110.90}},
        {!"Wilshire Boulevard",                       {1096.40, -1130.80, -89.00, 1252.30, -1026.30, 110.90}},
        {!"Wilshire Boulevard",                       {1096.40, -1026.30, -89.00, 1252.30, -910.10, 110.90}},
        {!"The Camel's Toe Road",              {2087.30, 1203.20, -89.00, 2640.40, 1383.20, 110.90}},
        {!"The Clown's Pocket Road",           {2162.30, 1783.20, -89.00, 2437.30, 1883.20, 110.90}},
        {!"The Emerald Isle Road",             {2011.90, 2202.70, -89.00, 2237.40, 2508.20, 110.90}},
        {!"Rural Route",                     {-1209.60, -1317.10, 114.90, -908.10, -787.30, 251.90}},
        {!"Russell Road",      {1817.30, 863.20, -89.00, 2027.30, 1083.20, 110.90}},
        {!"The High Roller Road",              {1817.30, 1283.20, -89.00, 2027.30, 1469.20, 110.90}},
        {!"Mackinac Bridge",                {1664.60, 401.70, 0.00, 1785.10, 567.20, 200.00}},
        {!"Abandoned Road ",               {-947.90, -304.30, -1.10, -319.60, 327.00, 200.00}},
        {!"The Pink Swan Road",                {1817.30, 1083.20, -89.00, 2027.30, 1283.20, 110.90}},
        {!"Hoover Dam Boulevard",              {-968.70, 1929.40, -3.00, -481.10, 2155.20, 200.00}},
        {!"The Strip Boulevard",                    {2027.40, 863.20, -89.00, 2087.30, 1703.20, 110.90}},
        {!"The Strip Boulevard",                    {2106.70, 1863.20, -89.00, 2162.30, 2202.70, 110.90}},
        {!"The Strip Boulevard",                    {2027.40, 1783.20, -89.00, 2162.30, 1863.20, 110.90}},
        {!"The Strip Boulevard",                    {2027.40, 1703.20, -89.00, 2137.40, 1783.20, 110.90}},
        {!"The Visage Road",                   {1817.30, 1863.20, -89.00, 2106.70, 2011.80, 110.90}},
        {!"The Visage Road",                   {1817.30, 1703.20, -89.00, 2027.40, 1863.20, 110.90}},
        {!"Unity Station",                {1692.60, -1971.80, -20.40, 1812.60, -1932.80, 79.50}},
        {!"Secret Cove Road",               {-936.60, 2611.40, 2.00, -715.90, 2847.90, 200.00}},
        {!"Topanga Canyon Boulevard",               {930.20, -2488.40, -89.00, 1249.60, -2006.70, 110.90}},
        {!"Topanga Canyon Boulevard",               {1073.20, -2006.70, -89.00, 1249.60, -1842.20, 110.90}},
        {!"Topanga Canyon Boulevard",               {1249.60, -2179.20, -89.00, 1692.60, -1842.20, 110.90}},
        {!"Abandoned Airstrip",              {37.00, 2337.10, -3.00, 435.90, 2677.90, 200.00}},
        {!"Venice Beach Boulevard",                 {647.70, -2173.20, -89.00, 930.20, -1804.20, 110.90}},
        {!"Venice Beach Boulevard",                 {930.20, -2006.70, -89.00, 1073.20, -1804.20, 110.90}},
        {!"Venice Beach Boulevard",                 {851.40, -1804.20, -89.00, 1046.10, -1577.50, 110.90}},
        {!"Venice Beach Boulevard",                 {1161.50, -1722.20, -89.00, 1323.90, -1577.50, 110.90}},
        {!"Venice Beach Boulevard",                 {1046.10, -1722.20, -89.00, 1161.50, -1577.50, 110.90}},
        {!"Hollywood Boulevard",                     {787.40, -1310.20, -89.00, 952.60, -1130.80, 110.90}},
        {!"Hollywood Boulevard",                     {787.40, -1130.80, -89.00, 952.60, -954.60, 110.90}},
        {!"Hollywood Boulevard",                     {647.50, -1227.20, -89.00, 787.40, -1118.20, 110.90}},
        {!"Hollywood Boulevard",                     {647.70, -1416.20, -89.00, 787.40, -1227.20, 110.90}},
        {!"Benedict Canyon Road",            {883.30, 1726.20, -89.00, 1098.30, 2507.20, 110.90}},
        {!"Benedict Canyon Road",            {1098.30, 1726.20, -89.00, 1197.30, 2243.20, 110.90}},
        {!"Selma Avenue",                  {1970.60, -2179.20, -89.00, 2089.00, -1852.80, 110.90}},
        {!"Selma Avenue",                  {2089.00, -2235.80, -89.00, 2201.80, -1989.90, 110.90}},
        {!"Selma Avenue",                  {2089.00, -1989.90, -89.00, 2324.00, -1852.80, 110.90}},
        {!"Selma Avenue",                  {2201.80, -2095.00, -89.00, 2324.00, -1989.90, 110.90}},
        {!"Selma Avenue",                  {2541.70, -1941.40, -89.00, 2703.50, -1852.80, 110.90}},
        {!"Selma Avenue",                  {2324.00, -2059.20, -89.00, 2541.70, -1852.80, 110.90}},
        {!"Selma Avenue",                  {2541.70, -2059.20, -89.00, 2703.50, -1941.40, 110.90}},
        {!"Yellow Bell Station",          {1377.40, 2600.40, -21.90, 1492.40, 2687.30, 78.00}},
        {!"Los Santos",                   {44.60, -2892.90, -242.90, 2997.00, -768.00, 900.00}},
        {!"Las Venturas",                 {869.40, 596.30, -242.90, 2997.00, 2993.80, 900.00}},
        {!"Bone County",                  {-480.50, 596.30, -242.90, 869.40, 2993.80, 900.00}},
        {!"Tierra Robada",                {-2997.40, 1659.60, -242.90, -480.50, 2993.80, 900.00}},
        {!"Tierra Robada",                {-1213.90, 596.30, -242.90, -480.50, 1659.60, 900.00}},
        {!"San Fierro",                   {-2997.40, -1115.50, -242.90, -1213.90, 1659.60, 900.00}},
        {!"Red County",                   {-1213.90, -768.00, -242.90, 2997.00, 596.30, 900.00}},
        {!"Flint County",                 {-1213.90, -2892.90, -242.90, 44.60, -768.00, 900.00}},
        {!"Whetstone",                    {-2997.40, -2892.90, -242.90, -1213.90, -1115.50, 900.00}}
    };
    new name[32] = "San Andreas";

    for (new i = 0; i != sizeof(g_arrZoneData); i ++) if ((fX >= g_arrZoneData[i][e_ZoneArea][0] && fX <= g_arrZoneData[i][e_ZoneArea][3]) && (fY >= g_arrZoneData[i][e_ZoneArea][1] && fY <= g_arrZoneData[i][e_ZoneArea][4]) && (fZ >= g_arrZoneData[i][e_ZoneArea][2] && fZ <= g_arrZoneData[i][e_ZoneArea][5]))
        {
            strunpack(name, g_arrZoneData[i][e_ZoneName]);

            break;
        }
    return name;
}

SendPlayerToPlayer(playerid, targetid)
{
    new
        Float:x,
        Float:y,
        Float:z;
		
	if(!AccountData[targetid][pSpawned] || !AccountData[playerid][pSpawned])
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut belum spawn!");

	if(OJailData[playerid][jailed] || OJailData[targetid][jailed])
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sedang di jail!");
		
    GetPlayerPos(targetid, x, y, z);

    if(IsPlayerInAnyVehicle(playerid))
    {
        SetVehiclePos(GetPlayerVehicleID(playerid), x, y + 2, z);
		SetVehicleVirtualWorldEx(GetPlayerVehicleID(playerid), GetPlayerVirtualWorld(targetid));
        LinkVehicleToInteriorEx(GetPlayerVehicleID(playerid), GetPlayerInterior(targetid));
    }
    else
    {
        SetPlayerPositionEx(playerid, x + 1, y, z, 750);
    }
    SetPlayerInterior(playerid, GetPlayerInterior(targetid));
    SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(targetid));

    AccountData[playerid][pInDoor] = AccountData[targetid][pInDoor];
	AccountData[playerid][pInHouse] = AccountData[targetid][pInHouse];
	AccountData[playerid][pInBiz] = AccountData[targetid][pInBiz];
	AccountData[playerid][pInRusun] = AccountData[targetid][pInRusun];
    
	Anticheat[playerid][acImmunity] = gettime() + 5;
	return 1;
}

StopRunningAnimation(playerid)
{
	StopLoopingAnim(playerid);
	ClearAnimations(playerid, true);
	return 1;
}

ReturnWeaponName(weaponid)
{
    new weapon[22];
    switch(weaponid)
    {
        case 0: weapon = "Fist / Unknown";
		case 16: weapon = "Grenade / Explosion";
        case 18: weapon = "Molotov Cocktail";
        case 44: weapon = "Night Vision Goggles";
        case 45: weapon = "Thermal Goggles";
		case 49: weapon = "Rammed";
		case 50: weapon = "Heli Blades";
		case 51: weapon = "Explosion";
        case 54: weapon = "Fall";
		case 255: weapon = "Suicide";
        default: GetWeaponName(weaponid, weapon, sizeof(weapon));
    }
    return weapon;
}

IsAFireArm(weaponid)
{
	switch(weaponid)
	{
		case 16, 17, 18, 22..39:
		{
			return true;
		}
	}
	return false;
}

//----------[ Banneds Native ]---------
Ban_GetLongIP(const ip[])
{
  	new parts[4];
	sscanf(ip, "p<.>a<i>[4]", parts);
	return ((parts[0] << 24) | (parts[1] << 16) | (parts[2] << 8) | parts[3]);
}

GetSimpleDate()
{
	static year, month, day;
	getdate(year, month, day);

	static date[128];
	format(date, sizeof (date), "%02d/%02d/%d", day, month, year);
	return date;
}

GetSimpleTime()
{
	static year, month, day, hour, minute, second;
	gettime(hour, minute, second);
	getdate(year, month, day);

	static date[128];
	format(date, sizeof (date), "%02d/%02d/%d %02d:%02d:%02d", day, month, year, hour, minute, second);
	return date;
}

GetAdvTime() //mengambil waktu terkini secara detail
{
	static year, month, day, hour, minute, second;
	gettime(hour, minute, second);
	getdate(year, month, day);

	static monthname[15];
	switch (month)
	{
	    case 1: monthname = "Jan";
	    case 2: monthname = "Feb";
	    case 3: monthname = "Mar";
	    case 4: monthname = "Apr";
	    case 5: monthname = "Mei";
	    case 6: monthname = "Jun";
	    case 7: monthname = "Jul";
	    case 8: monthname = "Agu";
	    case 9: monthname = "Sep";
	    case 10: monthname = "Okt";
	    case 11: monthname = "Nov";
	    case 12: monthname = "Des";
	}
	
	static date[128];
	format(date, sizeof (date), "%s %02d %s %d, %02d:%02d:%02d", GetWeekDay(day, month, year), day, monthname, year, hour, minute, second);
	return date;
}

GetCalenderDate(tanggal, bulan, tahun)
{
	static monthname[15];
	switch (bulan)
	{
	    case 1: monthname = "Januari";
	    case 2: monthname = "Februari";
	    case 3: monthname = "Maret";
	    case 4: monthname = "April";
	    case 5: monthname = "Mei";
	    case 6: monthname = "Juni";
	    case 7: monthname = "Juli";
	    case 8: monthname = "Agustus";
	    case 9: monthname = "September";
	    case 10: monthname = "Oktober";
	    case 11: monthname = "November";
	    case 12: monthname = "Desember";
	}

	static date[128];
	format(date, sizeof (date), "%02d %s %d", tanggal, monthname, tahun);
	return date;
}

ReturnDate(timestamp) //mengembalikan secara detail dari timestamp yang dibuat
{
	new year, month, day, hour, minute, second;
	TimestampToDate(timestamp, year, month, day, hour, minute, second, 7);

	static monthname[15];
	switch (month)
	{
	    case 1: monthname = "Jan";
	    case 2: monthname = "Feb";
	    case 3: monthname = "Mar";
	    case 4: monthname = "Apr";
	    case 5: monthname = "Mei";
	    case 6: monthname = "Jun";
	    case 7: monthname = "Jul";
	    case 8: monthname = "Agu";
	    case 9: monthname = "Sep";
	    case 10: monthname = "Okt";
	    case 11: monthname = "Nov";
	    case 12: monthname = "Des";
	}

	new date[128];
	format(date, sizeof (date), "%s, %d %s %d - %02d:%02d:%02d", GetWeekDay(day, month, year), day, monthname, year, hour, minute, second);
	return date;
}

ReturnSimpleDate(timestamp) //mengembalikan secara ringkas/simple dari timestamp yang dibuat
{
	new year, month, day, hour, minute, second;
	TimestampToDate(timestamp, year, month, day, hour, minute, second, 7);

	new date[128];
	format(date, sizeof (date), "%d/%d/%d", day, month, year);
	return date;
}

GetFormatTime(second)
{
	new string[256];
	new hours = second / 3600;
	new minutes = second / 60 % 60;
	new seconds = second % 3600 % 60;

	format(string, sizeof(string), "%02d:%02d:%02d", hours, minutes, seconds);
	return string;
}

ReturnTimelapse(start, till, const def[] = "Baru Saja")
{
    new ret[64];
    new second = till - start;

    enum e_durationData
    {
        edS,
        edL[10],
    }

    if(second <= 0)
    {
        strcopy(ret, def);
        return ret;
    }

    static durations[][e_durationData] =
    {
        {86400, "hari"},
        {3600, "jam"},
        {60, "menit"},
        {1, "detik"}
    };

    for (new i = 0; i < sizeof(durations); i++)
    {
        if (second > durations[i][edS])
        {
            new cur = floatround(second / durations[i][edS], floatround_floor);
            format(ret, 64, "%s %d %s", ret, cur, durations[i][edL]);
            second = second % durations[i][edS];
        }
    }
    return ret;
}

//---------- Get Nama Faction & Variable //
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

GetRankName(playerid) 
{
    new rnnrt[128];

    switch(AccountData[playerid][pFaction])
    {
        case FACTION_NONE: //None
        {
            format(rnnrt, sizeof(rnnrt), "N/A");
        }
        case FACTION_LSPD: //polda 
        {
            format(rnnrt, sizeof(rnnrt), CopRank[AccountData[playerid][pFactionRank]]);
        }
		case FACTION_LSFD: //IDA 
        {
            format(rnnrt, sizeof(rnnrt), LSFDRank[AccountData[playerid][pFactionRank]]);
        }
		case FACTION_PUTRIDELI: //Putri Deli 
        {
            format(rnnrt, sizeof(rnnrt), PutrideliRank[AccountData[playerid][pFactionRank]]);
        }
		case FACTION_SAGOV: //pemerintah
		{
			format(rnnrt, sizeof(rnnrt), PemerintahRank[AccountData[playerid][pFactionRank]]);
		}
		case FACTION_BENNYS: //pemerintah
		{
			format(rnnrt, sizeof(rnnrt), BennysRank[AccountData[playerid][pFactionRank]]);
		}
		case FACTION_UBER: //uber 
        {
            format(rnnrt, sizeof(rnnrt), UberRank[AccountData[playerid][pFactionRank]]);
        }
		case FACTION_DINARBUCKS: //uber 
        {
            format(rnnrt, sizeof(rnnrt), DBRank[AccountData[playerid][pFactionRank]]);
        }
		case FACTION_FOX11: //fox 11 
        {
            format(rnnrt, sizeof(rnnrt), FoxRank[AccountData[playerid][pFactionRank]]);
        }
		case FACTION_AUTOMAX: //bengkel
        {
            format(rnnrt, sizeof(rnnrt), AutomaxRank[AccountData[playerid][pFactionRank]]);
        }
		case FACTION_HANDOVER: //bengkel
        {
            format(rnnrt, sizeof(rnnrt), HandoverRank[AccountData[playerid][pFactionRank]]);
        }
		case FACTION_SRIMERSING: //+arivena
        {
            format(rnnrt, sizeof(rnnrt), PARVRank[AccountData[playerid][pFactionRank]]);
        }
		case FACTION_TEXAS: //texas
        {
            format(rnnrt, sizeof(rnnrt), TexasRank[AccountData[playerid][pFactionRank]]);
        }
    }
    return rnnrt;
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

GetFamilyRankName(playerid) 
{
    new rnnrt[128];

    format(rnnrt, sizeof(rnnrt), FamilyRank[AccountData[playerid][pFamilyRank]]);
    return rnnrt;
}

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

GetFactionName(playerid) 
{
    new fctnr[128];

    format(fctnr, sizeof(fctnr), FacName[AccountData[playerid][pFaction]]);
    return fctnr;
}

static const VIPLevel[4][] = {
    "Bukan VIP",
    "Regular Pinky (1)",
    "Super Pinky (2)",
    "Pinkyman Pinky (3)"
};

GetVIPLevel(playerid) 
{
    static vlstr[128];

    format(vlstr, sizeof(vlstr), VIPLevel[AccountData[playerid][pVIP]]);
    return vlstr;
}

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

GetAdminLevel(playerid) 
{
    static galstr[128];

    format(galstr, sizeof(galstr), AdminLevel[AccountData[playerid][pAdmin]]);
    return galstr;
}

GetPlayerLevelName(playerid) 
{
    new name[32];
    if (AccountData[playerid][pLevel] == 1) format(name, sizeof(name), "Newbie");
    else if (AccountData[playerid][pLevel] == 2) format(name, sizeof(name), "Regular Player");
    else if (AccountData[playerid][pLevel] == 3) format(name, sizeof(name), "Junior Player");
    else if (AccountData[playerid][pLevel] == 4) format(name, sizeof(name), "Second Player");
    else if (AccountData[playerid][pLevel] == 5) format(name, sizeof(name), "Senior Player");
    else if (AccountData[playerid][pLevel] == 6) format(name, sizeof(name), "Big Slave");
    else if (AccountData[playerid][pLevel] == 7) format(name, sizeof(name), "Royal Slave");
    else if (AccountData[playerid][pLevel] == 8) format(name, sizeof(name), "Perfect Slave");
    else if (AccountData[playerid][pLevel] == 9) format(name, sizeof(name), "No Life");
    else if (AccountData[playerid][pLevel] == 10) format(name, sizeof(name), "Get a Life");
    else if (AccountData[playerid][pLevel] == 11) format(name, sizeof(name), "Take a life");
    else if (AccountData[playerid][pLevel] == 12) format(name, sizeof(name), "Big Ranked");
    else if (AccountData[playerid][pLevel] == 13) format(name, sizeof(name), "High Ranked");
    else if (AccountData[playerid][pLevel] == 14) format(name, sizeof(name), "Big Roller");
    else if (AccountData[playerid][pLevel] == 15) format(name, sizeof(name), "High Roller");
    else if (AccountData[playerid][pLevel] == 16) format(name, sizeof(name), "Get a Roller");
    else if (AccountData[playerid][pLevel] == 17) format(name, sizeof(name), "Loyal Player");
    else if (AccountData[playerid][pLevel] == 18) format(name, sizeof(name), "Perfect Player");
    else if (AccountData[playerid][pLevel] == 19) format(name, sizeof(name), "Street Runner");
    else if (AccountData[playerid][pLevel] == 20) format(name, sizeof(name), "Street Legend");
    else if (AccountData[playerid][pLevel] == 21) format(name, sizeof(name), "Street Hustler");
    else if (AccountData[playerid][pLevel] == 22) format(name, sizeof(name), "Corner Boy");
    else if (AccountData[playerid][pLevel] == 23) format(name, sizeof(name), "Getaway Driver");
    else if (AccountData[playerid][pLevel] == 24) format(name, sizeof(name), "Smooth Criminal");
    else if (AccountData[playerid][pLevel] == 25) format(name, sizeof(name), "Gang Prospect");
    else if (AccountData[playerid][pLevel] == 26) format(name, sizeof(name), "Made Man");
    else if (AccountData[playerid][pLevel] == 27) format(name, sizeof(name), "Street Captain");
    else if (AccountData[playerid][pLevel] == 28) format(name, sizeof(name), "Drug Lord");
    else if (AccountData[playerid][pLevel] == 29) format(name, sizeof(name), "Heist Master");
    else if (AccountData[playerid][pLevel] == 30) format(name, sizeof(name), "Kingpin");
    else if (AccountData[playerid][pLevel] == 31) format(name, sizeof(name), "Ghetto Superstar");
    else if (AccountData[playerid][pLevel] == 32) format(name, sizeof(name), "Hood Legend");
    else if (AccountData[playerid][pLevel] == 33) format(name, sizeof(name), "Syndicate Boss");
    else if (AccountData[playerid][pLevel] == 34) format(name, sizeof(name), "Crime Overlord");
    else if (AccountData[playerid][pLevel] == 35) format(name, sizeof(name), "Underworld King");
    else if (AccountData[playerid][pLevel] == 36) format(name, sizeof(name), "Mafia Don");
    else if (AccountData[playerid][pLevel] == 37) format(name, sizeof(name), "Cartel Leader");
    else if (AccountData[playerid][pLevel] == 38) format(name, sizeof(name), "Gang Warlord");
    else if (AccountData[playerid][pLevel] == 39) format(name, sizeof(name), "Street God");
    else if (AccountData[playerid][pLevel] == 40) format(name, sizeof(name), "Urban Legend");
    else if (AccountData[playerid][pLevel] == 41) format(name, sizeof(name), "Underworld Deity");
    else if (AccountData[playerid][pLevel] == 42) format(name, sizeof(name), "Criminal Mastermind");
    else if (AccountData[playerid][pLevel] == 43) format(name, sizeof(name), "Godfather");
    else if (AccountData[playerid][pLevel] == 44) format(name, sizeof(name), "Shadow Emperor");
    else if (AccountData[playerid][pLevel] == 45) format(name, sizeof(name), "Untouchable");
    else if (AccountData[playerid][pLevel] == 46) format(name, sizeof(name), "Crime Tycoon");
    else if (AccountData[playerid][pLevel] == 47) format(name, sizeof(name), "Underworld Puppeteer");
    else if (AccountData[playerid][pLevel] == 48) format(name, sizeof(name), "Legendary Outlaw");
    else if (AccountData[playerid][pLevel] == 49) format(name, sizeof(name), "Criminal Demigod");
    else if (AccountData[playerid][pLevel] >= 50 && AccountData[playerid][pLevel] < 100) format(name, sizeof(name), "Master of San Andreas");
    else if (AccountData[playerid][pLevel] >= 100) format(name, sizeof(name), "God of San Andreas");
    return name;
}

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

GetJobName(playerid) 
{
    static galstr[128];

    format(galstr, sizeof(galstr), JOBName[AccountData[playerid][pJob]]);
    return galstr;
}

ShowPlayerStats(playerid, targetid)
{
	static spstr[1655], Float:phealth, Float:parmour;

	GetPlayerHealth(targetid, phealth);
	GetPlayerArmour(targetid, parmour);

	format(spstr, sizeof(spstr), 
	"Category\t Detail(s)\n\
	Character ID:\t %d\n\
	"GRAY"UCP:\t "GRAY"%s\n\
	Fullname:\t %s\n\
	"GRAY"Age:\t "GRAY"%d years old\n\
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
	"GRAY"Health:\t "GRAY"%.3f\n\
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
	Char Register Date:\t %s\n\
	"GRAY"UCP Register Date:\t %s",
	AccountData[targetid][pID],
	AccountData[targetid][pUCP],
	AccountData[targetid][pName],
	AccountData[targetid][pAge],
	AccountData[targetid][pOrigin],
	(AccountData[targetid][pGender] == 1) ? ("Laki-Laki") : ("Perempuan"),
	AccountData[targetid][pBodyHeight],
	AccountData[targetid][pBodyWeight],
	GetJobName(targetid),
	GetFactionName(targetid),
	GetRankName(targetid),
	GetFamilyName(AccountData[targetid][pFamily]),
	GetFamilyRankName(targetid),
	FormatMoney(AccountData[targetid][pMoney]),
	FormatMoney(AccountData[targetid][pBankMoney]),
	FormatMoney(AccountData[targetid][pCasinoChip]),
	FormatMoney(AccountData[targetid][pDirtyMoney]),
	phealth,
	parmour,
	AccountData[targetid][pHunger],
	AccountData[targetid][pThirst],
	AccountData[targetid][pStress],
	AccountData[targetid][pWarn],
	AccountData[targetid][pLevel],
	GetPlayerLevelName(targetid),
	AccountData[targetid][pHours],
	AccountData[targetid][pMinutes],
	AccountData[targetid][pSeconds],
	GetAdminLevel(targetid),
	(AccountData[targetid][pSteward]) ? (""DARKGREEN"Yes") : ("Not Stewards"),
	ReturnTimelapse(gettime(), AccountData[targetid][pStewardTime], ""DARKRED"Expired"),
	GetVIPLevel(targetid),
	ReturnTimelapse(gettime(), AccountData[targetid][pVIPTime], ""DARKRED"Expired"),
	AccountData[targetid][pSkin],
	GetPlayerVirtualWorld(targetid),
	GetPlayerInterior(targetid),
	AccountData[targetid][pInHouse],
	AccountData[targetid][pInBiz],
	AccountData[targetid][pInDoor],
	AccountData[targetid][pInRusun],
	AccountData[targetid][pLastLogin],
	AccountData[targetid][pRegisterDate],
	UCPRegisterDate[targetid]);

	Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, sprintf("{DA9100}Pahlawan Roleplay "WHITE"- %s(%d) - (%s)", AccountData[targetid][pName], targetid, AccountData[targetid][pUCP]), spstr, "Tutup", "");
}
//---------------------------------//
GetBodyPartName(partid) 
{
    new fctnr[128];
	switch(partid)
	{
		case 3:
		{
			strcopy(fctnr, "Torso");
		}
		case 4:
		{
			strcopy(fctnr, "Groin");
		}
		case 5:
		{
			strcopy(fctnr, "Left Arm");
		}
		case 6:
		{
			strcopy(fctnr, "Right Arm");
		}
		case 7:
		{
			strcopy(fctnr, "Left Leg");
		}
		case 8:
		{
			strcopy(fctnr, "Right Leg");
		}
		case 9:
		{
			strcopy(fctnr, "Head");
		}
	}
    return fctnr;
}

ResetPlayerWeaponsEx(playerid) //hapus semua senjata yang valid yang tersimpan
{
    ResetPlayerWeapons(playerid);

    for (new i = 0; i < 13; i ++) {
		GunData[playerid][i][WeaponID] = 0;
		GunData[playerid][i][WeaponType] = 0;
		GunData[playerid][i][WeaponAmmo] = 0;
    }
    return 1;
}

ResetWeapon(playerid, weaponid) //hapus senjata dengan weaponid yang valid dan mmenyisakan senjata yang valid yang tersimpan
{
	ResetPlayerWeapons(playerid);

    for (new i = 0; i < 13; i ++) 
	{
        if(GunData[playerid][i][WeaponID] != weaponid) 
		{
            GivePlayerWeapon(playerid, GunData[playerid][i][WeaponID], GunData[playerid][i][WeaponAmmo]);
        }
        else 
		{
            GunData[playerid][i][WeaponID] = 0;
            GunData[playerid][i][WeaponAmmo] = 0;
        }
    }
    return 1;
}

UpdateWeapons(playerid) //memperbarui data senjata yang valid yang tersimpan
{
    for(new i = 0; i < 13; i ++)
	{
		if(GunData[playerid][i][WeaponID] > 0)
		{
			if((i == 2 && AccountData[playerid][pTaser]))
		    	continue;
			if((i == 3 && AccountData[playerid][pUseBeanbag]))
		    	continue;

			GetPlayerWeaponData(playerid, i, GunData[playerid][i][WeaponID], GunData[playerid][i][WeaponAmmo]);

			if(GunData[playerid][i][WeaponID] != 0 && !GunData[playerid][i][WeaponAmmo]) 
			{
				GunData[playerid][i][WeaponID] = 0;
			}
		}
	}
    return 1;
}

SetWeapons(playerid) //memberikan semua senjata yang valid yang tersimpan
{
    ResetPlayerWeapons(playerid);

    for (new i = 0; i < 13; i ++) if(GunData[playerid][i][WeaponID] > 0 && GunData[playerid][i][WeaponAmmo] > 0) 
	{
        GivePlayerWeapon(playerid, GunData[playerid][i][WeaponID], GunData[playerid][i][WeaponAmmo]);
		if(AccountData[playerid][pVIP] >= 2)
			SetPlayerWeaponTint(playerid, GunData[playerid][i][WeaponID], GetWeaponIndex(GunData[playerid][i][WeaponID]));
    }
    return 1;
}

GivePlayerWeaponEx(playerid, weaponid, ammo, wtype) //memberikan senjata valid yang baru
{
    if(weaponid < 0 || weaponid > 46)
        return 0;

	GunData[playerid][g_aWeaponSlots[weaponid]][WeaponID] = weaponid;
	GunData[playerid][g_aWeaponSlots[weaponid]][WeaponAmmo] += ammo;
	GunData[playerid][g_aWeaponSlots[weaponid]][WeaponType] = wtype;

    GivePlayerWeapon(playerid, weaponid, ammo);

	if(AccountData[playerid][pVIP] >= 2)
		SetPlayerWeaponTint(playerid, weaponid, GetWeaponIndex(weaponid));
	return 1;
}

//----------- Calendar ----------------//
GetWeekDay(day=0, month=0, year=0)
{
	if(!day)
			getdate(year, month, day);
	new
		szWeekDay[10],
		j,
		e;

	if(month <= 2)
	{
		month += 12;
		--year;
	}

	j = year % 100;
	e = year / 100;

	switch((day + (month+1)*26/10 + j + j/4 + e/4 - 2*e) % 7)
	{
		case 0: szWeekDay = "Sab";
		case 1: szWeekDay = "Min";
		case 2: szWeekDay = "Sen";
		case 3: szWeekDay = "Sel";
		case 4: szWeekDay = "Rab";
		case 5: szWeekDay = "Kam";
		case 6: szWeekDay = "Jum";
	}
	return szWeekDay;
}

PlayerPlayNearbySound(playerid, soundid)
{
	new Float:plPos[3];
	GetPlayerPos(playerid, plPos[0], plPos[1], plPos[2]);
	foreach(new p: Player)
	{
		if(IsPlayerInRangeOfPoint(p, 5.0, plPos[0], plPos[1], plPos[2]))
		{
			PlayerPlaySound(p, soundid, plPos[0], plPos[1], plPos[2]);
		}
	}
	return true;
}

PlaySoundForPlayersInRange(soundid, Float:range, Float:x, Float:y, Float:z)
{
	foreach(new i : Player)
	{
	    if(IsPlayerConnected(i) && IsPlayerInRangeOfPoint(i,range,x,y,z))
	    {
		    PlayerPlaySound(i, soundid, x, y, z);
	    }
	}
	return 1;
}

encode_tires(tire1, tire2, tire3, tire4)
{
	return tire1 | (tire2 << 1) | (tire3 << 2) | (tire4 << 3);
}

encode_tires_bike(rear, front)
{
	return rear | (front << 1);
}

SendTeamMessage(factid, color, const str[], {Float,_}:...)
{
    static
        args,
        start,
        end,
        string[512]
    ;
    #emit LOAD.S.pri 8
    #emit STOR.pri args

    if(args > 12)
    {
        #emit ADDR.pri str
        #emit STOR.pri start

        for (end = start + (args - 12); end > start; end -= 4)
        {
            #emit LREF.pri end
            #emit PUSH.pri
        }
        #emit PUSH.S str
        #emit PUSH.C 144
        #emit PUSH.C string
        #emit PUSH.C args

        #emit SYSREQ.C format
        #emit LCTRL 5
        #emit SCTRL 4

        foreach (new i : Player) if(AccountData[i][pFaction] == factid && AccountData[i][pOnDuty]) {
                SendClientMessage(i, color, string);
        }
        return 1;
    }
    foreach (new i : Player) if(AccountData[i][pFaction] == factid && AccountData[i][pOnDuty]) {
        SendClientMessage(i, color, str);
    }
    return 1;
}

IsWeaponModel(model) {
    new const g_aWeaponModels[] = {
        0, 331, 333, 334, 335, 336, 337, 338, 339, 341, 321, 322, 323, 324,
        325, 326, 342, 343, 344, 0, 0, 0, 346, 347, 348, 349, 350, 351, 352,
        353, 355, 356, 372, 357, 358, 359, 360, 361, 362, 363, 364, 365, 366,
        367, 368, 368, 371
    };
    for (new i = 0; i < sizeof(g_aWeaponModels); i ++) if(g_aWeaponModels[i] == model) {
        return 1;
    }
    return 0;
}

GetPlayerWeaponEx(playerid)
{
    new weaponid = GetPlayerWeapon(playerid);

    if(1 <= weaponid <= 46 && GunData[playerid][g_aWeaponSlots[weaponid]][WeaponID] == weaponid && GunData[playerid][g_aWeaponSlots[weaponid]][WeaponType] > WEAPON_TYPE_NONE)
        return weaponid;

    return 0;
}

GetPlayerAmmoEx(playerid)
{
	new weaponid = GetPlayerWeapon(playerid);
	new ammo = GunData[playerid][g_aWeaponSlots[weaponid]][WeaponAmmo];
	if(1 <= weaponid <= 46 && GunData[playerid][g_aWeaponSlots[weaponid]][WeaponID] == weaponid && GunData[playerid][g_aWeaponSlots[weaponid]][WeaponType] > WEAPON_TYPE_NONE)
	{
		if(GunData[playerid][g_aWeaponSlots[weaponid]][WeaponID] != 0 && GunData[playerid][g_aWeaponSlots[weaponid]][WeaponAmmo] > 0)
		{
			return ammo;
		}
	}
	return 0;
}

AddTransactionLog(const NamaPemberi[], const UCPPemberi[], const NamaPenerima[], const UCPPenerima[], jumlah, const Status[])
{
	static frmtmny[512];
	mysql_format(g_SQL, frmtmny, sizeof(frmtmny), "INSERT INTO `log_transaction` SET `Pemberi` = '%e', `UCP Pemberi`='%e', `Penerima` = '%e', `UCP Penerima`='%e', `Jumlah` = %d, `Status` = '%e', `Tanggal` = CURRENT_TIMESTAMP()", NamaPemberi, UCPPemberi, NamaPenerima, UCPPenerima, jumlah, Status);
    mysql_pquery(g_SQL, frmtmny);
	return 1;
}

AddFMoneyLog(const Nama[], const UCP[], jumlah, const Factione[])
{
	static frmtmny[512];
	mysql_format(g_SQL, frmtmny, sizeof(frmtmny), "INSERT INTO `log_fmoney` SET `Nama` = '%e', `UCP`='%e', `Jumlah` = %d, `Faction` = '%e', `Tanggal` = CURRENT_TIMESTAMP()", Nama, UCP, jumlah, Factione);
    mysql_pquery(g_SQL, frmtmny);
	return 1;
}

IsPlayerMoving(playerid)
{
    GetPlayerVelocity(playerid, Velocity[playerid][0], Velocity[playerid][1], Velocity[playerid][2]);
    if(Velocity[playerid][0] == 0.0 && Velocity[playerid][1] == 0.0 && Velocity[playerid][2] == 0.0) return 0;
    return 1;
}

IsVehicleMoving(vehicleid)
{
    GetVehicleVelocity(vehicleid, Velocity[vehicleid][0], Velocity[vehicleid][1], Velocity[vehicleid][2]);
    if(Velocity[vehicleid][0] == 0.0 && Velocity[vehicleid][1] == 0.0 && Velocity[vehicleid][2] == 0.0) return 0;
    return 1;
}

ResetAllRaceCP(playerid)
{
	if(DestroyDynamicRaceCP(AccountData[playerid][pCarstealRCP]))
		AccountData[playerid][pCarstealRCP] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

	if(DestroyDynamicRaceCP(AccountData[playerid][UberRCP]))
		AccountData[playerid][UberRCP] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

	if(DestroyDynamicRaceCP(AccountData[playerid][pGPSCP]))
		AccountData[playerid][pGPSCP] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

	if(DestroyDynamicRaceCP(EventRaceRCP[playerid]))
		EventRaceRCP[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

	if(DestroyDynamicRaceCP(PlayerCargoVars[playerid][CargoDestCP]))
		PlayerCargoVars[playerid][CargoDestCP] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

	if(DestroyDynamicRaceCP(PlayerCargoVars[playerid][CargoReturnCP]))
		PlayerCargoVars[playerid][CargoReturnCP] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;
		
	if(DestroyDynamicRaceCP(pTutorialRCP[playerid]))
		pTutorialRCP[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;
}

ShowPlayerFooter(playerid, const string[], time = 5000) 
{
	if(AccountData[playerid][pShowFooter]) 
    {
	    PlayerTextDrawHide(playerid, FooterTD[playerid]);
	    KillTimer(AccountData[playerid][pFooterTimer]);
        AccountData[playerid][pFooterTimer] = -1;
	}
	PlayerTextDrawSetString(playerid, FooterTD[playerid], string);
	PlayerTextDrawShow(playerid, FooterTD[playerid]);

	AccountData[playerid][pShowFooter] = true;
	AccountData[playerid][pFooterTimer] = SetTimerEx("HidePlayerFooter", time, false, "d", playerid);
}

RoundNegativeToPositive(Float:value)
{
    if (floatround(value) < 0)
        return floatround(value * -1);
    else
        return floatround(value);
}

//----------------------- [Mathematic] ------------//
GenerateRandomType(playerid)
{
	new alpha[12], randtext[128];

	alpha[0] = random(sizeof(g_MixAlphabet)),
	alpha[1] = random(sizeof(g_MixAlphabet)),
	alpha[2] = random(sizeof(g_MixAlphabet)),
	alpha[3] = random(sizeof(g_MixAlphabet)),
	alpha[4] = random(sizeof(g_MixAlphabet)),
	alpha[5] = random(sizeof(g_MixAlphabet)),
	alpha[6] = random(sizeof(g_MixAlphabet)),
	alpha[7] = random(sizeof(g_MixAlphabet)),
	alpha[8] = random(sizeof(g_MixAlphabet)),
	alpha[9] = random(sizeof(g_MixAlphabet)),
	alpha[10] = random(sizeof(g_MixAlphabet)),
	alpha[11] = random(sizeof(g_MixAlphabet)),

	format(randtext, sizeof(randtext), "%s%s%s%s%s%s%s%s%s%s%s%s", g_MixAlphabet[alpha[0]], g_MixAlphabet[alpha[1]], g_MixAlphabet[alpha[2]],
	g_MixAlphabet[alpha[3]], g_MixAlphabet[alpha[4]], g_MixAlphabet[alpha[5]], g_MixAlphabet[alpha[6]], g_MixAlphabet[alpha[7]], g_MixAlphabet[alpha[8]],
	g_MixAlphabet[alpha[9]], g_MixAlphabet[alpha[10]], g_MixAlphabet[alpha[11]]);

	strcopy(AccountData[playerid][pABRobbery], randtext);

	return randtext;
}

SetPlayerAFK(playerid)
{
    new randafk;
    
    randafk = Random(999);
    AccountData[playerid][pAFKNumb] = randafk;

    SetPlayerColor(playerid, X11_ORANGE);
   	SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda sekarang AFK, gunakan "CMDEA"'/afk %d' "WHITE"untuk kembali roleplay!", randafk);
	
    TogglePlayerControllable(playerid, false);
    AccountData[playerid][pAFKCount] = 0;
    AccountData[playerid][pIsAFK] = true;
}

ConvertFloatColor(Float:value, defcolor)
{
    new color;
    if(value >= 90.0 && value <= 100.0)
        color = 0x15a014FF;
    else if(value >= 80.0 && value < 90.0)
        color = 0x1b9913FF;
    else if(value >= 70.0 && value < 80.0)
        color = 0x1a7f08FF;
    else if(value >= 60.0 && value < 70.0)
        color = 0x326305FF;
    else if(value >= 50 && value < 60.0)
        color = 0x375d04FF;
    else if(value >= 40.0 && value < 50.0)
        color = 0xb35c48FF;
    else if(value >= 30.0 && value < 40.0)
        color = 0xd72800FF;
    else if(value >= 10.0 && value < 30.0)
        color = 0xfb3508FF;
    else if(value >= 0.0 && value < 10.0)
        color = 0xFF0000FF;
    else 
        color = defcolor;

    return color;
}

ShowPlayerSpawnSelection(playerid)
{
	Dialog_Show(playerid, "SpawnSelection", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Select Spawn", 
	"Titik spawn\tDetail\tLokasi\n\
	Bandara Pahlawan Roleplay\tAnda akan spawn di bandara\tLos Santos (LS)\n\
	"GRAY"Apartment\t"GRAY"Anda spawn di dalam apartment yang anda sewa\t"GRAY"-\n\
	House\tAnda spawn di dalam rumah yang anda miliki\t-\n\
	"GRAY"Faction Headquarter (HQ)\t"GRAY"Anda spawn di depan bangunan faction\t"GRAY"-\n\
	Posisi Terakhir\tAnda akan spawn di lokasi terakhir anda keluar server", "Pilih", "");
	return 1;
}

GetPlayerSpeed(playerid)
{
	new Float:ST[4];
	if(IsPlayerInAnyVehicle(playerid))
		GetVehicleVelocity(GetPlayerVehicleID(playerid), ST[0], ST[1], ST[2]);
	else 
		GetPlayerVelocity(playerid, ST[0], ST[1], ST[2]);
	ST[3] = floatsqroot(floatpower(floatabs(ST[0]), 2.0) + floatpower(floatabs(ST[1]), 2.0) + floatpower(floatabs(ST[2]), 2.0)) * 179.28625;
	return floatround(ST[3]);
}

ReplaceText(string[], const search[], const replacement[], bool:ignorecase = false, pos = 0, limit = -1, maxlength = 256)
{
	if(!limit)
		return 0;

	new sublen = strlen(search),
		replen = strlen(replacement),
		bool:packed = ispacked(string),
		maxlen = maxlength,
		len = strlen(string),
		count = 0;

	if(packed) maxlen *= 4;
	if(!sublen) return 0;

	while(-1 != (pos = strfind(string, search, ignorecase, pos)))
	{
		strdel(string, pos, pos + sublen);

		len -= sublen;

		if(replen && len + replen < maxlen)
		{
			strins(string, replacement, pos, maxlength);

			pos += replen;
			len += replen;
		}

		if(limit != -1 && ++count >= limit)break;
	}
    return 1;
}

// IsRPQuizTaken(playerid, id)
// {
// 	for(new x; x < sizeof(g_RPQuizData); x++)
// 	{
// 		if(PlayerListitem[playerid][x] == id) 
// 			return true;
// 	}
// 	return false;
// }

CheckPlayerLicense(playerid)
{
	if(AccountData[playerid][pGVL1Lic] || AccountData[playerid][pGVL2Lic] || AccountData[playerid][pMBLic] || AccountData[playerid][pBLic] || AccountData[playerid][pAir1Lic] || AccountData[playerid][pAir2Lic] || AccountData[playerid][pFirearmLic] || AccountData[playerid][pHuntingLic])
	{
		return true;
	}
	return false;
}

GetPlayerFPS(playerid) 
{
    new playerDrunkLevel = GetPlayerDrunkLevel(playerid);

    if(playerDrunkLevel < 100)
    {
        SetPlayerDrunkLevel(playerid, 2000);
    }
    else
    {
        if(lastDrunkLevel[playerid] != playerDrunkLevel)
        {
            currFPS[playerid] = (lastDrunkLevel[playerid] - playerDrunkLevel);

            lastDrunkLevel[playerid] = playerDrunkLevel;
            if((currFPS[playerid] > 0) && (currFPS[playerid] < 256))
            {
                return currFPS[playerid] - 1;
            }
        }
    }
    return 0;
}

GetPlayerPartName(playerid, nametoget)
{
	new firstname[24], lastname[24];
	sscanf(AccountData[playerid][pName], "p<_>s[24]s[24]", firstname, lastname);

	if(nametoget == 2)
	{
    	return lastname;
	}
	else
	{
		return firstname;
	}
}

IsAnyVehicleInDMVArea()
{
	foreach(new v : Vehicle)
	{
		if(GetVehicleDistanceFromPoint(v, 2086.8738,-1354.8881,24.0143) <= 1.5)
		{
			return true;
		}
	}
	return false;
}

// IsAnyVehicleInDMVArea()
// {
// 	foreach(new v : Vehicle)
// 	{
// 		if(GetVehicleDistanceFromPoint(v, 2086.8738,-1354.8881,24.0143) <= 1.5)
// 		{
// 			return true;
// 		}
// 	}
// 	return false;
// }

IsPlayerInWater(playerid)
{
	if(AccountData[playerid][pSpawned] && (GetPlayerAnimationIndex(playerid) == 1250 || GetPlayerAnimationIndex(playerid) == 1539 || GetPlayerAnimationIndex(playerid) == 1538 || GetPlayerAnimationIndex(playerid) == 1541 || GetPlayerAnimationIndex(playerid) == 1544))
	{
		return true;
	}
	return false;
}

CameraRadiusSetPos(playerid, Float:x, Float:y, Float:z, Float:degree = 0.0, Float:height = 3.0, Float:radius = 8.0)
{
	new Float:deltaToX = x + radius * floatsin(-degree, degrees);
	new Float:deltaToY = y + radius * floatcos(-degree, degrees);
	new Float:deltaToZ = z + height;

	SetPlayerCameraPos(playerid, deltaToX, deltaToY, deltaToZ);
	SetPlayerCameraLookAt(playerid, x, y, z); 
	return 1;
}

IsPlayerInInvalidNosVehicle(playerid)
{
    new vehicleid = GetPlayerVehicleID(playerid);
    #define MAX_INVALID_NOS_VEHICLES 52
    new InvalidNosVehicles[MAX_INVALID_NOS_VEHICLES] =
    {
        581,523,462,521,463,522,461,448,468,586,417,425,469,487,512,520,563,593,
        509,481,510,472,473,493,520,595,484,430,453,432,476,497,513,533,577,
        452,446,447,454,590,569,537,538,570,449,519,460,488,511,519,548,592
    };
    if(IsPlayerInAnyVehicle(playerid))
    {
        for(new i = 0; i < MAX_INVALID_NOS_VEHICLES; i++)
        {
            if(GetVehicleModel(vehicleid) == InvalidNosVehicles[i]) return true;
        }
    }
    return false;
}

IsComponentidCompatible(modelid, componentid)
{
    switch (modelid)
    {
		case 400:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1013 || componentid == 1018 || componentid == 1019 || componentid == 1020 || componentid == 1021 || componentid == 1024 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 401:	return (componentid == 1001 || componentid == 1003 || componentid == 1004 || componentid == 1005 || componentid == 1006 || componentid == 1007 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1013 || componentid == 1017 || componentid == 1019 || componentid == 1020 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098 || componentid == 1142 || componentid == 1143 || componentid == 1144 || componentid == 1145);
		case 402:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 403:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 404:	return (componentid == 1000 || componentid == 1002 || componentid == 1007 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1013 || componentid == 1016 || componentid == 1017 || componentid == 1019 || componentid == 1020 || componentid == 1021 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 405:	return (componentid == 1000 || componentid == 1001 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1014 || componentid == 1018 || componentid == 1019 || componentid == 1020 || componentid == 1021 || componentid == 1023 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 406:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 407:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 408:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 409:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 410:	return (componentid == 1001 || componentid == 1003 || componentid == 1007 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1013 || componentid == 1017 || componentid == 1019 || componentid == 1020 || componentid == 1021 || componentid == 1023 || componentid == 1024 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 411:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 412:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 413:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 414:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 415:	return (componentid == 1001 || componentid == 1003 || componentid == 1007 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1017 || componentid == 1018 || componentid == 1019 || componentid == 1023 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 416:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 417:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 418:	return (componentid == 1002 || componentid == 1006 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1016 || componentid == 1020 || componentid == 1021 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 419:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 420:	return (componentid == 1001 || componentid == 1003 || componentid == 1004 || componentid == 1005 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1019 || componentid == 1021 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 421:	return (componentid == 1000 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1014 || componentid == 1016 || componentid == 1018 || componentid == 1019 || componentid == 1020 || componentid == 1021 || componentid == 1023 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 422:	return (componentid == 1007 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1013 || componentid == 1017 || componentid == 1019 || componentid == 1020 || componentid == 1021 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 423:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 424:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 425:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 426:	return (componentid == 1001 || componentid == 1003 || componentid == 1004 || componentid == 1005 || componentid == 1006 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1019 || componentid == 1021 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 427:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 428:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 429:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 431:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 432:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 433:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 434:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 435:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 436:	return (componentid == 1001 || componentid == 1003 || componentid == 1006 || componentid == 1007 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1013 || componentid == 1017 || componentid == 1019 || componentid == 1020 || componentid == 1021 || componentid == 1022 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 437:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 438:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 439:	return (componentid == 1001 || componentid == 1003 || componentid == 1007 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1013 || componentid == 1017 || componentid == 1023 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098 || componentid == 1142 || componentid == 1143 || componentid == 1144 || componentid == 1145);
		case 440:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 441:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 442:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 443:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 444:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 445:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 447:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 450:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 451:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 455:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 456:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 457:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 458:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 459:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 460:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 464:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 465:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 466:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 467:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 469:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 470:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 471:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 474:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 475:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 476:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 477:	return (componentid == 1006 || componentid == 1007 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1017 || componentid == 1018 || componentid == 1019 || componentid == 1020 || componentid == 1021 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 478:	return (componentid == 1004 || componentid == 1005 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1012 || componentid == 1013 || componentid == 1020 || componentid == 1021 || componentid == 1022 || componentid == 1024 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 479:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 480:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 482:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 483:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 485:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 486:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 487:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 488:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 489:	return (componentid == 1000 || componentid == 1002 || componentid == 1004 || componentid == 1005 || componentid == 1006 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1013 || componentid == 1016 || componentid == 1018 || componentid == 1019 || componentid == 1020 || componentid == 1024 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 490:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 491:	return (componentid == 1003 || componentid == 1007 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1014 || componentid == 1017 || componentid == 1018 || componentid == 1019 || componentid == 1020 || componentid == 1021 || componentid == 1023 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098 || componentid == 1142 || componentid == 1143 || componentid == 1144 || componentid == 1145);
		case 492:	return (componentid == 1000 || componentid == 1004 || componentid == 1005 || componentid == 1006 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1016 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 494:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 495:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 496:	return (componentid == 1001 || componentid == 1002 || componentid == 1003 || componentid == 1006 || componentid == 1007 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1011 || componentid == 1017 || componentid == 1019 || componentid == 1020 || componentid == 1023 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098 || componentid == 1142 || componentid == 1143);
		case 497:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 498:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 499:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 500:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1013 || componentid == 1019 || componentid == 1020 || componentid == 1021 || componentid == 1024 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 501:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 502:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 503:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 504:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 505:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 506:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 507:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 508:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 511:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 512:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 513:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 514:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 515:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 516:	return (componentid == 1000 || componentid == 1002 || componentid == 1004 || componentid == 1007 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1015 || componentid == 1016 || componentid == 1017 || componentid == 1018 || componentid == 1019 || componentid == 1020 || componentid == 1021 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 517:	return (componentid == 1002 || componentid == 1003 || componentid == 1007 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1016 || componentid == 1017 || componentid == 1018 || componentid == 1019 || componentid == 1020 || componentid == 1023 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098 || componentid == 1142 || componentid == 1143 || componentid == 1144 || componentid == 1145);
		case 518:	return (componentid == 1001 || componentid == 1003 || componentid == 1005 || componentid == 1006 || componentid == 1007 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1013 || componentid == 1017 || componentid == 1018 || componentid == 1020 || componentid == 1023 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098 || componentid == 1142 || componentid == 1143 || componentid == 1144 || componentid == 1145);
		case 519:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 520:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 524:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 525:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 526:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 527:	return (componentid == 1001 || componentid == 1007 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1014 || componentid == 1015 || componentid == 1017 || componentid == 1018 || componentid == 1020 || componentid == 1021 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 528:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 529:	return (componentid == 1001 || componentid == 1003 || componentid == 1006 || componentid == 1007 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1011 || componentid == 1012 || componentid == 1017 || componentid == 1018 || componentid == 1019 || componentid == 1020 || componentid == 1023 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 530:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 531:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 532:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 533:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 534:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098 || componentid == 1100 || componentid == 1101 || componentid == 1106 || componentid == 1122 || componentid == 1123 || componentid == 1124 || componentid == 1125 || componentid == 1126 || componentid == 1127 || componentid == 1178 || componentid == 1179 || componentid == 1180 || componentid == 1185);
		case 535:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098 || componentid == 1109 || componentid == 1110 || componentid == 1113 || componentid == 1114 || componentid == 1115 || componentid == 1116 || componentid == 1117 || componentid == 1118 || componentid == 1119 || componentid == 1120 || componentid == 1121);
		case 536:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098 || componentid == 1103 || componentid == 1104 || componentid == 1105 || componentid == 1107 || componentid == 1108 || componentid == 1128 || componentid == 1181 || componentid == 1182 || componentid == 1183 || componentid == 1184);
		case 539:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 540:	return (componentid == 1001 || componentid == 1004 || componentid == 1006 || componentid == 1007 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1017 || componentid == 1018 || componentid == 1019 || componentid == 1020 || componentid == 1023 || componentid == 1024 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098 || componentid == 1142 || componentid == 1143 || componentid == 1144 || componentid == 1145);
		case 541:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 542:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1014 || componentid == 1015 || componentid == 1018 || componentid == 1019 || componentid == 1020 || componentid == 1021 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098 || componentid == 1144 || componentid == 1145);
		case 543:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 544:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 545:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 546:	return (componentid == 1001 || componentid == 1002 || componentid == 1004 || componentid == 1006 || componentid == 1007 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1017 || componentid == 1018 || componentid == 1019 || componentid == 1023 || componentid == 1024 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098 || componentid == 1142 || componentid == 1143 || componentid == 1144 || componentid == 1145);
		case 547:	return (componentid == 1000 || componentid == 1003 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1016 || componentid == 1018 || componentid == 1019 || componentid == 1020 || componentid == 1021 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098 || componentid == 1142 || componentid == 1143);
		case 548:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 549:	return (componentid == 1001 || componentid == 1003 || componentid == 1007 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1011 || componentid == 1012 || componentid == 1017 || componentid == 1018 || componentid == 1019 || componentid == 1020 || componentid == 1023 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098 || componentid == 1142 || componentid == 1143 || componentid == 1144 || componentid == 1145);
		case 550:	return (componentid == 1001 || componentid == 1003 || componentid == 1004 || componentid == 1005 || componentid == 1006 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1018 || componentid == 1019 || componentid == 1020 || componentid == 1023 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098 || componentid == 1142 || componentid == 1143 || componentid == 1144 || componentid == 1145);
		case 551:	return (componentid == 1002 || componentid == 1003 || componentid == 1005 || componentid == 1006 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1016 || componentid == 1018 || componentid == 1019 || componentid == 1020 || componentid == 1021 || componentid == 1023 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 552:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 553:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 554:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 555:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 556:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 557:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 558:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1088 || componentid == 1089 || componentid == 1090 || componentid == 1091 || componentid == 1092 || componentid == 1093 || componentid == 1094 || componentid == 1095 || componentid == 1096 || componentid == 1097 || componentid == 1098 || componentid == 1163 || componentid == 1164 || componentid == 1165 || componentid == 1166 || componentid == 1167 || componentid == 1168);
		case 559:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1065 || componentid == 1066 || componentid == 1067 || componentid == 1068 || componentid == 1069 || componentid == 1070 || componentid == 1071 || componentid == 1072 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098 || componentid == 1158 || componentid == 1159 || componentid == 1160 || componentid == 1161 || componentid == 1162 || componentid == 1173);
		case 560:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1026 || componentid == 1027 || componentid == 1028 || componentid == 1029 || componentid == 1030 || componentid == 1031 || componentid == 1032 || componentid == 1033 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098 || componentid == 1138 || componentid == 1139 || componentid == 1140 || componentid == 1141 || componentid == 1169 || componentid == 1170);
		case 561:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1055 || componentid == 1056 || componentid == 1057 || componentid == 1058 || componentid == 1059 || componentid == 1060 || componentid == 1061 || componentid == 1062 || componentid == 1063 || componentid == 1064 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098 || componentid == 1154 || componentid == 1155 || componentid == 1156 || componentid == 1157);
		case 562:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1034 || componentid == 1035 || componentid == 1036 || componentid == 1037 || componentid == 1038 || componentid == 1039 || componentid == 1040 || componentid == 1041 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098 || componentid == 1146 || componentid == 1147 || componentid == 1148 || componentid == 1149 || componentid == 1171 || componentid == 1172);
		case 563:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 564:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 565:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1045 || componentid == 1046 || componentid == 1047 || componentid == 1048 || componentid == 1049 || componentid == 1050 || componentid == 1051 || componentid == 1052 || componentid == 1053 || componentid == 1054 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098 || componentid == 1150 || componentid == 1151 || componentid == 1152 || componentid == 1153);
		case 566:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 567:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098 || componentid == 1102 || componentid == 1129 || componentid == 1130 || componentid == 1131 || componentid == 1132 || componentid == 1133 || componentid == 1186 || componentid == 1187 || componentid == 1188 || componentid == 1189);
		case 568:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 571:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 572:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 573:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 574:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 575:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1042 || componentid == 1043 || componentid == 1044 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098 || componentid == 1099 || componentid == 1174 || componentid == 1175 || componentid == 1176 || componentid == 1177);
		case 576:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098 || componentid == 1134 || componentid == 1135 || componentid == 1136 || componentid == 1137 || componentid == 1190 || componentid == 1191 || componentid == 1192 || componentid == 1193);
		case 577:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 578:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 579:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 580:	return (componentid == 1001 || componentid == 1006 || componentid == 1007 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1017 || componentid == 1018 || componentid == 1020 || componentid == 1023 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 582:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 583:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 584:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 585:	return (componentid == 1000 || componentid == 1001 || componentid == 1002 || componentid == 1003 || componentid == 1006 || componentid == 1007 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1013 || componentid == 1014 || componentid == 1015 || componentid == 1016 || componentid == 1017 || componentid == 1018 || componentid == 1019 || componentid == 1020 || componentid == 1021 || componentid == 1022 || componentid == 1023 || componentid == 1024 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098 || componentid == 1142 || componentid == 1143 || componentid == 1144 || componentid == 1145);
		case 587:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 588:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 589:	return (componentid == 1000 || componentid == 1004 || componentid == 1005 || componentid == 1006 || componentid == 1007 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1013 || componentid == 1016 || componentid == 1017 || componentid == 1018 || componentid == 1020 || componentid == 1024 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098 || componentid == 1144 || componentid == 1145);
		case 591:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 592:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 593:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 594:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 596:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 597:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 598:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 599:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 600:	return (componentid == 1004 || componentid == 1005 || componentid == 1006 || componentid == 1007 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1013 || componentid == 1017 || componentid == 1018 || componentid == 1020 || componentid == 1022 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 601:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 602:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 603:	return (componentid == 1001 || componentid == 1006 || componentid == 1007 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1017 || componentid == 1018 || componentid == 1019 || componentid == 1020 || componentid == 1023 || componentid == 1024 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098 || componentid == 1142 || componentid == 1143 || componentid == 1144 || componentid == 1145);
		case 604:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 605:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 606:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 607:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 608:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 609:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 610:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
		case 611:	return (componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 || componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 || componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1086 || componentid == 1087 || componentid == 1096 || componentid == 1097 || componentid == 1098);
    }
    return false;
}

HideRadarMapForPlayer(playerid)
{
	foreach(new garageid : PGarages)
	{
		Streamer_ToggleItem(playerid, STREAMER_TYPE_MAP_ICON, PublicGarage[garageid][pgMapIcon], false);
	}
	foreach(new gdgid : Gudangs)
	{
		Streamer_ToggleItem(playerid, STREAMER_TYPE_MAP_ICON, GudangData[gdgid][gudangMapIcon], false);
	}
	foreach(new iccid : Icons)
	{
		Streamer_ToggleItem(playerid, STREAMER_TYPE_MAP_ICON, IconData[iccid][iconMapID], false);
	}
	foreach(new shid : Shops)
	{
		Streamer_ToggleItem(playerid, STREAMER_TYPE_MAP_ICON, ShopData[shid][shopIcon], false);
	}
	GangZoneShowForPlayer(playerid, gpsZone, 0x33AA33EB);
	return 1;
}

ShowRadarMapForPlayer(playerid)
{
	foreach(new garageid : PGarages)
	{
		Streamer_ToggleItem(playerid, STREAMER_TYPE_MAP_ICON, PublicGarage[garageid][pgMapIcon], true);
	}
	foreach(new gdgid : Gudangs)
	{
		Streamer_ToggleItem(playerid, STREAMER_TYPE_MAP_ICON, GudangData[gdgid][gudangMapIcon], true);
	}
	foreach(new iccid : Icons)
	{
		Streamer_ToggleItem(playerid, STREAMER_TYPE_MAP_ICON, IconData[iccid][iconMapID], true);
	}
	foreach(new shid : Shops)
	{
		Streamer_ToggleItem(playerid, STREAMER_TYPE_MAP_ICON, ShopData[shid][shopIcon], true);
	}
	GangZoneHideForPlayer(playerid, gpsZone);
	return 1;
}

GetPlayerInventoryWeight(playerid)
{
	new weight = 50;
	if(AccountData[playerid][pVIP] == 1)
	{
		weight = 60;
	}
	else if(AccountData[playerid][pVIP] == 2)
	{
		weight = 70;
	}
	else if(AccountData[playerid][pVIP] == 3)
	{
		weight = 80;
	}
	else
	{
		weight = 50;
	}
	return weight;
}

IsAtBahamas(playerid)
{
	//ls
	if(IsPlayerInDynamicArea(playerid, AreaSantaiZone))
	{
		return 1;
	}
	return 0;
}

IsPlayerInGovTypeFaction(playerid)
{
	if(AccountData[playerid][pFaction] == FACTION_LSPD || AccountData[playerid][pFaction] == FACTION_LSFD) {
		return true;
	}
	return false;
}

IsPlayerInFNBTypeFaction(playerid)
{
	if(AccountData[playerid][pFaction] == FACTION_DINARBUCKS || AccountData[playerid][pFaction] == FACTION_PUTRIDELI || AccountData[playerid][pFaction] == FACTION_SRIMERSING || AccountData[playerid][pFaction] == FACTION_TEXAS)
		return true;
	
	return false;
}
IsPlayerStunned(playerid)
{
	if(AccountData[playerid][pTazedTime] > 0 || AccountData[playerid][pBeanbagTime] > 0 || AccountData[playerid][pTackleTime] > 0)
		return true;

	return false;
}

IsProhibitedWeapon(weaponid)
{
	switch(weaponid)
	{
		case 16.. 18, 35.. 40:
		{
			return true;
		}
		default:
		{
			return false;
		}
	}
	return false;
}

FormatTime(seconds)
{
    new str[144];

    if (seconds == 1)
    {
        format(str, sizeof(str), "one second");
    }
    else if (seconds < 60)
    {
        format(str, sizeof(str), "%d seconds", seconds);
    }
    else if (seconds < 120)  // Less than 2 minutes
    {
        format(str, sizeof(str), "a minute");
    }
    else if (seconds < 3600)  // More than 2 minutes but less than an hour
    {
        format(str, sizeof(str), "%d minutes", seconds / 60);
    }
    else if (seconds < 7200)  // Less than 2 hours
    {
        format(str, sizeof(str), "an hour");
    }
    else if (seconds < 86400)  // More than 2 hours but less than a day
    {
        format(str, sizeof(str), "%d hours", seconds / 3600);
    }
    else if (seconds < 172800)  // Less than 2 days
    {
        format(str, sizeof(str), "%d hours (a day)", seconds / 3600);
    }
    else if (seconds < 2592000) // Less than 30 days (around a month)
    {
        format(str, sizeof(str), "%d hours (%d days)", seconds / 3600, seconds / 86400);
    }
    else if (seconds < 5184000) // Less than 60 days (around 2 months)
    {
        format(str, sizeof(str), "%d days (a month)", seconds / 86400);
    }
    else if (seconds < 31536000) // Less than a year
    {
        format(str, sizeof(str), "%d days (%d months)", seconds / 86400, seconds / 2592000);
    }
    else if (seconds < 63072000) // Less than 2 years
    {
        format(str, sizeof(str), "%d months (a year)", seconds / 2592000);
    }
    else
    {
        format(str, sizeof(str), "%d months (%d years)", (seconds % 31536000) / 2592000, seconds / 31536000);
    }

    return str;
}

SetPlayerJoinCamera(playerid)
{
	//new randcamera = pData[playerid][pLoadingScreenRandom];
	new randcamera = random(5);
	switch(randcamera)
	{
		case 0:
		{
		    SetPlayerVirtualWorld(playerid, 0);
   			InterpolateCameraPos(playerid, 2060.737304, 1213.688842, 18.161676, 2172.680175, 2037.517700, 116.877761, 120000, CAMERA_MOVE);
			InterpolateCameraLookAt(playerid, 2064.142333, 1217.318603, 18.641407, 2169.474121, 2034.003662, 115.337158, 120000, CAMERA_MOVE);
  		}
  		case 1:
		{
		    SetPlayerVirtualWorld(playerid, 0);

	   		InterpolateCameraPos(playerid, 1691.288818, -1564.318115, 39.562980, 1688.464111, -1848.907592, 14.061653, 120000);
			InterpolateCameraLookAt(playerid, 1691.017456, -1569.158935, 38.341102, 1692.403686, -1851.829589, 15.032330, 120000);
  		}
  		case 2:
		{
		    SetPlayerVirtualWorld(playerid, 0);

            InterpolateCameraPos(playerid, 599.224182, -1775.964599, 16.167873, 428.634582, -1748.962036, 25.512968, 120000);
			InterpolateCameraLookAt(playerid, 594.297790, -1775.144653, 16.409967, 426.819671, -1753.597412, 25.044904, 120000);
  		}
  		case 3:
		{
		    SetPlayerVirtualWorld(playerid, 0);

   			InterpolateCameraPos(playerid, 496.975372, -1266.310302, 31.091993, 1468.297607, -889.806396, 106.448226, 120000);
			InterpolateCameraLookAt(playerid, 501.779205, -1264.923828, 31.060743, 1465.012329, -886.121704, 105.654724, 120000);
  		}
  		case 4: // city
		{
		    SetPlayerVirtualWorld(playerid, 0);

   			InterpolateCameraPos(playerid, 1390.448242, -1400.684936, 14.921609, 616.103393, -1402.872314, 18.778308, 120000);
			InterpolateCameraLookAt(playerid, 1385.449218, -1400.598632, 14.972391, 620.323669, -1400.192382, 18.692375, 120000);
  		}
	}
}

//Date and Time
GetMonth(bulan)
{
    static month[12];

    switch (bulan)
    {
        case 1: month = "January";
        case 2: month = "February";
        case 3: month = "March";
        case 4: month = "April";
        case 5: month = "May";
        case 6: month = "June";
        case 7: month = "July";
        case 8: month = "August";
        case 9: month = "September";
        case 10: month = "October";
        case 11: month = "November";
        case 12: month = "December";
    }
    return month;
}

ReturnTime()
{
    static date[6],
           string[72];

    getdate(date[2], date[1], date[0]);
    gettime(date[3], date[4], date[5]);

    format(string, sizeof(string), "%02d %s %d, %02d:%02d:%02d", date[0], GetMonth(date[1]), date[2], date[3], date[4], date[5]);
    return string;
}

stock FormatCharacterID(sql_id)
{
    new str_id[16];
    
    // Angka 8 di depan, lalu %09d artinya 9 digit sisanya diisi angka 0 otomatis
    format(str_id, sizeof(str_id), "8%09d", sql_id);
    
    return str_id;
}

GetSkinModelName(skinid)
{
    new modelname[32];
    if (skinid == 0) format(modelname, sizeof(modelname), "CJ");
    else if (skinid == 1) format(modelname, sizeof(modelname), "TRUTH");
    else if (skinid == 2) format(modelname, sizeof(modelname), "MACCER");
    else if (skinid == 3) format(modelname, sizeof(modelname), "ANDRE");
    else if (skinid == 4) format(modelname, sizeof(modelname), "BBTHIN");
    else if (skinid == 5) format(modelname, sizeof(modelname), "BB");
    else if (skinid == 6) format(modelname, sizeof(modelname), "EMMET");
    else if (skinid == 7) format(modelname, sizeof(modelname), "MALE01");
    else if (skinid == 8) format(modelname, sizeof(modelname), "JANITOR");
    else if (skinid == 9) format(modelname, sizeof(modelname), "BFORI");
    else if (skinid == 10) format(modelname, sizeof(modelname), "BFOST");
    else if (skinid == 11) format(modelname, sizeof(modelname), "VBFYCRP");
    else if (skinid == 12) format(modelname, sizeof(modelname), "BFYRI");
    else if (skinid == 13) format(modelname, sizeof(modelname), "BFYST");
    else if (skinid == 14) format(modelname, sizeof(modelname), "BMORI");
    else if (skinid == 15) format(modelname, sizeof(modelname), "BMOST");
    else if (skinid == 16) format(modelname, sizeof(modelname), "BMYAP");
    else if (skinid == 17) format(modelname, sizeof(modelname), "BMYBU");
    else if (skinid == 18) format(modelname, sizeof(modelname), "BMYBE");
    else if (skinid == 19) format(modelname, sizeof(modelname), "BMYDJ");
    else if (skinid == 20) format(modelname, sizeof(modelname), "BMYRI");
    else if (skinid == 21) format(modelname, sizeof(modelname), "BMYCR");
    else if (skinid == 22) format(modelname, sizeof(modelname), "BMYST");
    else if (skinid == 23) format(modelname, sizeof(modelname), "WMYBMX");
    else if (skinid == 24) format(modelname, sizeof(modelname), "WBDYG1");
    else if (skinid == 25) format(modelname, sizeof(modelname), "WBDYG2");
    else if (skinid == 26) format(modelname, sizeof(modelname), "WMYBP");
    else if (skinid == 27) format(modelname, sizeof(modelname), "WMYCON");
    else if (skinid == 28) format(modelname, sizeof(modelname), "BMYDRUG");
    else if (skinid == 29) format(modelname, sizeof(modelname), "WMYDRUG");
    else if (skinid == 30) format(modelname, sizeof(modelname), "HMYDRUG");
    else if (skinid == 31) format(modelname, sizeof(modelname), "DWFOLC");
    else if (skinid == 32) format(modelname, sizeof(modelname), "DWMOLC1");
    else if (skinid == 33) format(modelname, sizeof(modelname), "DWMLOC2");
    else if (skinid == 34) format(modelname, sizeof(modelname), "DWMYLC1");
    else if (skinid == 35) format(modelname, sizeof(modelname), "HMOGAR");
    else if (skinid == 36) format(modelname, sizeof(modelname), "WMYGOL1");
    else if (skinid == 37) format(modelname, sizeof(modelname), "WMYGOL2");
    else if (skinid == 38) format(modelname, sizeof(modelname), "HFORI");
    else if (skinid == 39) format(modelname, sizeof(modelname), "HFOST");
    else if (skinid == 40) format(modelname, sizeof(modelname), "HFYRI");
    else if (skinid == 41) format(modelname, sizeof(modelname), "HFYST");
    else if (skinid == 42) format(modelname, sizeof(modelname), "JETHRO");
    else if (skinid == 43) format(modelname, sizeof(modelname), "HMORI");
    else if (skinid == 44) format(modelname, sizeof(modelname), "HMOST");
    else if (skinid == 45) format(modelname, sizeof(modelname), "HMYBE");
    else if (skinid == 46) format(modelname, sizeof(modelname), "HMYRI");
    else if (skinid == 47) format(modelname, sizeof(modelname), "HMYCR");
    else if (skinid == 48) format(modelname, sizeof(modelname), "HMYST");
    else if (skinid == 49) format(modelname, sizeof(modelname), "OMOKUNG");
    else if (skinid == 50) format(modelname, sizeof(modelname), "WMYMECH");
    else if (skinid == 51) format(modelname, sizeof(modelname), "BMYMOUN");
    else if (skinid == 52) format(modelname, sizeof(modelname), "WMYMOUN");
    else if (skinid == 53) format(modelname, sizeof(modelname), "OFORI");
    else if (skinid == 54) format(modelname, sizeof(modelname), "OFOST");
    else if (skinid == 55) format(modelname, sizeof(modelname), "OFYRI");
    else if (skinid == 56) format(modelname, sizeof(modelname), "OFYST");
    else if (skinid == 57) format(modelname, sizeof(modelname), "OMORI");
    else if (skinid == 58) format(modelname, sizeof(modelname), "OMOST");
    else if (skinid == 59) format(modelname, sizeof(modelname), "OMYRI");
    else if (skinid == 60) format(modelname, sizeof(modelname), "OMYST");
    else if (skinid == 61) format(modelname, sizeof(modelname), "WMYPLT");
    else if (skinid == 62) format(modelname, sizeof(modelname), "WMOPJ");
    else if (skinid == 63) format(modelname, sizeof(modelname), "BFYPRO");
    else if (skinid == 64) format(modelname, sizeof(modelname), "HFYPRO");
    else if (skinid == 65) format(modelname, sizeof(modelname), "KENDL");
    else if (skinid == 66) format(modelname, sizeof(modelname), "BMYPOL1");
    else if (skinid == 67) format(modelname, sizeof(modelname), "BMYPOL2");
    else if (skinid == 68) format(modelname, sizeof(modelname), "WMOPREA");
    else if (skinid == 69) format(modelname, sizeof(modelname), "SBFYST");
    else if (skinid == 70) format(modelname, sizeof(modelname), "WMOSCI");
    else if (skinid == 71) format(modelname, sizeof(modelname), "WMYSGRD");
    else if (skinid == 72) format(modelname, sizeof(modelname), "SWMYHP1");
    else if (skinid == 73) format(modelname, sizeof(modelname), "SWMYHP2");
    else if (skinid == 75) format(modelname, sizeof(modelname), "SWFOPRO");
    else if (skinid == 76) format(modelname, sizeof(modelname), "WFYSTEW");
    else if (skinid == 77) format(modelname, sizeof(modelname), "SWMOTR1");
    else if (skinid == 78) format(modelname, sizeof(modelname), "WMOTR1");
    else if (skinid == 79) format(modelname, sizeof(modelname), "BMOTR1");
    else if (skinid == 80) format(modelname, sizeof(modelname), "VBMYBOX");
    else if (skinid == 81) format(modelname, sizeof(modelname), "VWMYBOX");
    else if (skinid == 82) format(modelname, sizeof(modelname), "VHMYELV");
    else if (skinid == 83) format(modelname, sizeof(modelname), "VBMYELV");
    else if (skinid == 84) format(modelname, sizeof(modelname), "VIMYELV");
    else if (skinid == 85) format(modelname, sizeof(modelname), "VWFYPRO");
    else if (skinid == 86) format(modelname, sizeof(modelname), "RYDER3");
    else if (skinid == 87) format(modelname, sizeof(modelname), "VWFYST1");
    else if (skinid == 88) format(modelname, sizeof(modelname), "WFORI");
    else if (skinid == 89) format(modelname, sizeof(modelname), "WFOST");
    else if (skinid == 90) format(modelname, sizeof(modelname), "WFYJG");
    else if (skinid == 91) format(modelname, sizeof(modelname), "WFYRI");
    else if (skinid == 92) format(modelname, sizeof(modelname), "WFYRO");
    else if (skinid == 93) format(modelname, sizeof(modelname), "WFYST");
    else if (skinid == 94) format(modelname, sizeof(modelname), "WMORI");
    else if (skinid == 95) format(modelname, sizeof(modelname), "WMOST");
    else if (skinid == 96) format(modelname, sizeof(modelname), "WMYJG");
    else if (skinid == 97) format(modelname, sizeof(modelname), "WMYLG");
    else if (skinid == 98) format(modelname, sizeof(modelname), "WMYRI");
    else if (skinid == 99) format(modelname, sizeof(modelname), "WMYRO");
    else if (skinid == 100) format(modelname, sizeof(modelname), "WMYCR");
    else if (skinid == 101) format(modelname, sizeof(modelname), "WMYST");
    else if (skinid == 102) format(modelname, sizeof(modelname), "BALLAS1");
    else if (skinid == 103) format(modelname, sizeof(modelname), "BALLAS2");
    else if (skinid == 104) format(modelname, sizeof(modelname), "BALLAS3");
    else if (skinid == 105) format(modelname, sizeof(modelname), "FAM1");
    else if (skinid == 106) format(modelname, sizeof(modelname), "FAM2");
    else if (skinid == 107) format(modelname, sizeof(modelname), "FAM3");
    else if (skinid == 108) format(modelname, sizeof(modelname), "LSV1");
    else if (skinid == 109) format(modelname, sizeof(modelname), "LSV2");
    else if (skinid == 110) format(modelname, sizeof(modelname), "LSV3");
    else if (skinid == 111) format(modelname, sizeof(modelname), "MAFFA");
    else if (skinid == 112) format(modelname, sizeof(modelname), "MAFFB");
    else if (skinid == 113) format(modelname, sizeof(modelname), "MAFBOSS");
    else if (skinid == 114) format(modelname, sizeof(modelname), "VLA1");
    else if (skinid == 115) format(modelname, sizeof(modelname), "VLA2");
    else if (skinid == 116) format(modelname, sizeof(modelname), "VLA3");
    else if (skinid == 117) format(modelname, sizeof(modelname), "TRIADA");
    else if (skinid == 118) format(modelname, sizeof(modelname), "TRIADB");
    else if (skinid == 119) format(modelname, sizeof(modelname), "SINDACO");
    else if (skinid == 120) format(modelname, sizeof(modelname), "TRIBOSS");
    else if (skinid == 121) format(modelname, sizeof(modelname), "DNB1");
    else if (skinid == 122) format(modelname, sizeof(modelname), "DNB2");
    else if (skinid == 123) format(modelname, sizeof(modelname), "DNB3");
    else if (skinid == 124) format(modelname, sizeof(modelname), "VMAFF1");
    else if (skinid == 125) format(modelname, sizeof(modelname), "VMAFF2");
    else if (skinid == 126) format(modelname, sizeof(modelname), "VMAFF3");
    else if (skinid == 127) format(modelname, sizeof(modelname), "VMAFF4");
    else if (skinid == 128) format(modelname, sizeof(modelname), "DNMYLC");
    else if (skinid == 129) format(modelname, sizeof(modelname), "DNFOLC1");
    else if (skinid == 130) format(modelname, sizeof(modelname), "DNFOLC2");
    else if (skinid == 131) format(modelname, sizeof(modelname), "DNFYLC");
    else if (skinid == 132) format(modelname, sizeof(modelname), "DNMOLC1");
    else if (skinid == 133) format(modelname, sizeof(modelname), "DNMOLC2");
    else if (skinid == 134) format(modelname, sizeof(modelname), "SBMOTR2");
    else if (skinid == 135) format(modelname, sizeof(modelname), "SWMOTR2");
    else if (skinid == 136) format(modelname, sizeof(modelname), "SBMYTR3");
    else if (skinid == 137) format(modelname, sizeof(modelname), "SWMOTR3");
    else if (skinid == 138) format(modelname, sizeof(modelname), "WFYBE");
    else if (skinid == 139) format(modelname, sizeof(modelname), "BFYBE");
    else if (skinid == 140) format(modelname, sizeof(modelname), "HFYBE");
    else if (skinid == 141) format(modelname, sizeof(modelname), "SOFYBU");
    else if (skinid == 142) format(modelname, sizeof(modelname), "SBMYST");
    else if (skinid == 143) format(modelname, sizeof(modelname), "SBMYCR");
    else if (skinid == 144) format(modelname, sizeof(modelname), "BMYCG");
    else if (skinid == 145) format(modelname, sizeof(modelname), "WFYCRK");
    else if (skinid == 146) format(modelname, sizeof(modelname), "HMYCM");
    else if (skinid == 147) format(modelname, sizeof(modelname), "WMYBU");
    else if (skinid == 148) format(modelname, sizeof(modelname), "BFYBU");
    else if (skinid == 149) format(modelname, sizeof(modelname), "SMOKEV");
    else if (skinid == 150) format(modelname, sizeof(modelname), "WFYBU");
    else if (skinid == 151) format(modelname, sizeof(modelname), "DWFYLC1");
    else if (skinid == 152) format(modelname, sizeof(modelname), "WFYPRO");
    else if (skinid == 153) format(modelname, sizeof(modelname), "WMYCONB");
    else if (skinid == 154) format(modelname, sizeof(modelname), "WMYBE");
    else if (skinid == 155) format(modelname, sizeof(modelname), "WMYPIZZ");
    else if (skinid == 156) format(modelname, sizeof(modelname), "BMOBAR");
    else if (skinid == 157) format(modelname, sizeof(modelname), "CWFYHB");
    else if (skinid == 158) format(modelname, sizeof(modelname), "CWMOFR");
    else if (skinid == 159) format(modelname, sizeof(modelname), "CWMOHB1");
    else if (skinid == 160) format(modelname, sizeof(modelname), "CWMOHB2");
    else if (skinid == 161) format(modelname, sizeof(modelname), "CWMYFR");
    else if (skinid == 162) format(modelname, sizeof(modelname), "CWMYHB1");
    else if (skinid == 163) format(modelname, sizeof(modelname), "BMYBOUN");
    else if (skinid == 164) format(modelname, sizeof(modelname), "WMYBOUN");
    else if (skinid == 165) format(modelname, sizeof(modelname), "WMOMIB");
    else if (skinid == 166) format(modelname, sizeof(modelname), "BMYMIB");
    else if (skinid == 167) format(modelname, sizeof(modelname), "WMYBELL");
    else if (skinid == 168) format(modelname, sizeof(modelname), "BMOCHIL");
    else if (skinid == 169) format(modelname, sizeof(modelname), "SOFYRI");
    else if (skinid == 170) format(modelname, sizeof(modelname), "SOMYST");
    else if (skinid == 171) format(modelname, sizeof(modelname), "VWMYBJD");
    else if (skinid == 172) format(modelname, sizeof(modelname), "VWFYCRP");
    else if (skinid == 173) format(modelname, sizeof(modelname), "SFR1");
    else if (skinid == 174) format(modelname, sizeof(modelname), "SFR2");
    else if (skinid == 175) format(modelname, sizeof(modelname), "SFR3");
    else if (skinid == 176) format(modelname, sizeof(modelname), "BMYBAR");
    else if (skinid == 177) format(modelname, sizeof(modelname), "WMYBAR");
    else if (skinid == 178) format(modelname, sizeof(modelname), "WFYSEX");
    else if (skinid == 179) format(modelname, sizeof(modelname), "WMYAMMO");
    else if (skinid == 180) format(modelname, sizeof(modelname), "BMYTATT");
    else if (skinid == 181) format(modelname, sizeof(modelname), "VWMYCR");
    else if (skinid == 182) format(modelname, sizeof(modelname), "VBMOCD");
    else if (skinid == 183) format(modelname, sizeof(modelname), "VBMYCR");
    else if (skinid == 184) format(modelname, sizeof(modelname), "VHMYCR");
    else if (skinid == 185) format(modelname, sizeof(modelname), "SBMYRI");
    else if (skinid == 186) format(modelname, sizeof(modelname), "SOMYRI");
    else if (skinid == 187) format(modelname, sizeof(modelname), "SOMYBU");
    else if (skinid == 188) format(modelname, sizeof(modelname), "SWMYST");
    else if (skinid == 189) format(modelname, sizeof(modelname), "WMYVA");
    else if (skinid == 190) format(modelname, sizeof(modelname), "COPGRL3");
    else if (skinid == 191) format(modelname, sizeof(modelname), "GUNGRL3");
    else if (skinid == 192) format(modelname, sizeof(modelname), "MECGRL3");
    else if (skinid == 193) format(modelname, sizeof(modelname), "NURGRL3");
    else if (skinid == 194) format(modelname, sizeof(modelname), "CROGRL3");
    else if (skinid == 195) format(modelname, sizeof(modelname), "GANGRL3");
    else if (skinid == 196) format(modelname, sizeof(modelname), "CWFOFR");
    else if (skinid == 197) format(modelname, sizeof(modelname), "CWFOHB");
    else if (skinid == 198) format(modelname, sizeof(modelname), "CWFYFR1");
    else if (skinid == 199) format(modelname, sizeof(modelname), "CWFYFR2");
    else if (skinid == 200) format(modelname, sizeof(modelname), "CWMYHB2");
    else if (skinid == 201) format(modelname, sizeof(modelname), "DWFYLC2");
    else if (skinid == 202) format(modelname, sizeof(modelname), "DWMYLC2");
    else if (skinid == 203) format(modelname, sizeof(modelname), "OMYKARA");
    else if (skinid == 204) format(modelname, sizeof(modelname), "WMYKARA");
    else if (skinid == 205) format(modelname, sizeof(modelname), "WFYBURG");
    else if (skinid == 206) format(modelname, sizeof(modelname), "VWMYCD");
    else if (skinid == 207) format(modelname, sizeof(modelname), "VHFYPRO");
    else if (skinid == 208) format(modelname, sizeof(modelname), "SUZIE");
    else if (skinid == 209) format(modelname, sizeof(modelname), "OMONOOD");
    else if (skinid == 210) format(modelname, sizeof(modelname), "OMOBOAT");
    else if (skinid == 211) format(modelname, sizeof(modelname), "WFYCLOT");
    else if (skinid == 212) format(modelname, sizeof(modelname), "VWMOTR1");
    else if (skinid == 213) format(modelname, sizeof(modelname), "VWMOTR2");
    else if (skinid == 214) format(modelname, sizeof(modelname), "VWFYWAI");
    else if (skinid == 215) format(modelname, sizeof(modelname), "SBFORI");
    else if (skinid == 216) format(modelname, sizeof(modelname), "SWFYRI");
    else if (skinid == 217) format(modelname, sizeof(modelname), "WMYCLOT");
    else if (skinid == 218) format(modelname, sizeof(modelname), "SBFOST");
    else if (skinid == 219) format(modelname, sizeof(modelname), "SBFYRI");
    else if (skinid == 220) format(modelname, sizeof(modelname), "SBMOCD");
    else if (skinid == 221) format(modelname, sizeof(modelname), "SBMORI");
    else if (skinid == 222) format(modelname, sizeof(modelname), "SBMOST");
    else if (skinid == 223) format(modelname, sizeof(modelname), "SHMYCR");
    else if (skinid == 224) format(modelname, sizeof(modelname), "SOFORI");
    else if (skinid == 225) format(modelname, sizeof(modelname), "SOFOST");
    else if (skinid == 226) format(modelname, sizeof(modelname), "SOFYST");
    else if (skinid == 227) format(modelname, sizeof(modelname), "SOMOBU");
    else if (skinid == 228) format(modelname, sizeof(modelname), "SOMORI");
    else if (skinid == 229) format(modelname, sizeof(modelname), "SOMOST");
    else if (skinid == 230) format(modelname, sizeof(modelname), "SWMOTR5");
    else if (skinid == 231) format(modelname, sizeof(modelname), "SWFORI");
    else if (skinid == 232) format(modelname, sizeof(modelname), "SWFOST");
    else if (skinid == 233) format(modelname, sizeof(modelname), "SWFYST");
    else if (skinid == 234) format(modelname, sizeof(modelname), "SWMOCD");
    else if (skinid == 235) format(modelname, sizeof(modelname), "SWMORI");
    else if (skinid == 236) format(modelname, sizeof(modelname), "SWMOST");
    else if (skinid == 237) format(modelname, sizeof(modelname), "SHFYPRO");
    else if (skinid == 238) format(modelname, sizeof(modelname), "SBFYPRO");
    else if (skinid == 239) format(modelname, sizeof(modelname), "SWMOTR4");
    else if (skinid == 240) format(modelname, sizeof(modelname), "SWMYRI");
    else if (skinid == 241) format(modelname, sizeof(modelname), "SMYST");
    else if (skinid == 242) format(modelname, sizeof(modelname), "SMYST2");
    else if (skinid == 243) format(modelname, sizeof(modelname), "SFYPRO");
    else if (skinid == 244) format(modelname, sizeof(modelname), "VBFYST2");
    else if (skinid == 245) format(modelname, sizeof(modelname), "VBFYPRO");
    else if (skinid == 246) format(modelname, sizeof(modelname), "VHFYST3");
    else if (skinid == 247) format(modelname, sizeof(modelname), "BIKERA");
    else if (skinid == 248) format(modelname, sizeof(modelname), "BIKERB");
    else if (skinid == 249) format(modelname, sizeof(modelname), "BMYPIMP");
    else if (skinid == 250) format(modelname, sizeof(modelname), "SWMYCR");
    else if (skinid == 251) format(modelname, sizeof(modelname), "WFYLG");
    else if (skinid == 252) format(modelname, sizeof(modelname), "WMYVA2");
    else if (skinid == 253) format(modelname, sizeof(modelname), "BMOSEC");
    else if (skinid == 254) format(modelname, sizeof(modelname), "BIKDRUG");
    else if (skinid == 255) format(modelname, sizeof(modelname), "WMYCH");
    else if (skinid == 256) format(modelname, sizeof(modelname), "SBFYSTR");
    else if (skinid == 257) format(modelname, sizeof(modelname), "SWFYSTR");
    else if (skinid == 258) format(modelname, sizeof(modelname), "HECK1");
    else if (skinid == 259) format(modelname, sizeof(modelname), "HECK2");
    else if (skinid == 260) format(modelname, sizeof(modelname), "BMYCON");
    else if (skinid == 261) format(modelname, sizeof(modelname), "WMYCD1");
    else if (skinid == 262) format(modelname, sizeof(modelname), "BMOCD");
    else if (skinid == 263) format(modelname, sizeof(modelname), "VWFYWA2");
    else if (skinid == 264) format(modelname, sizeof(modelname), "WMOICE");
    else if (skinid == 265) format(modelname, sizeof(modelname), "TENPEN");
    else if (skinid == 266) format(modelname, sizeof(modelname), "PULASKI");
    else if (skinid == 267) format(modelname, sizeof(modelname), "HERN");
    else if (skinid == 268) format(modelname, sizeof(modelname), "DWAYNE");
    else if (skinid == 269) format(modelname, sizeof(modelname), "SMOKE");
    else if (skinid == 270) format(modelname, sizeof(modelname), "SWEET");
    else if (skinid == 271) format(modelname, sizeof(modelname), "RYDER");
    else if (skinid == 272) format(modelname, sizeof(modelname), "FORELLI");
    else if (skinid == 273) format(modelname, sizeof(modelname), "TBONE");
    else if (skinid == 274) format(modelname, sizeof(modelname), "LAEMT1");
    else if (skinid == 275) format(modelname, sizeof(modelname), "LVEMT1");
    else if (skinid == 276) format(modelname, sizeof(modelname), "SFEMT1");
    else if (skinid == 277) format(modelname, sizeof(modelname), "LAFD1");
    else if (skinid == 278) format(modelname, sizeof(modelname), "LVFD1");
    else if (skinid == 279) format(modelname, sizeof(modelname), "SFFD1");
    else if (skinid == 280) format(modelname, sizeof(modelname), "LAPD1");
    else if (skinid == 281) format(modelname, sizeof(modelname), "SFPD1");
    else if (skinid == 282) format(modelname, sizeof(modelname), "LVPD1");
    else if (skinid == 283) format(modelname, sizeof(modelname), "CSHER");
    else if (skinid == 284) format(modelname, sizeof(modelname), "LAPDM1");
    else if (skinid == 285) format(modelname, sizeof(modelname), "SWAT");
    else if (skinid == 286) format(modelname, sizeof(modelname), "FBI");
    else if (skinid == 287) format(modelname, sizeof(modelname), "ARMY");
    else if (skinid == 288) format(modelname, sizeof(modelname), "DSHER");
    else if (skinid == 289) format(modelname, sizeof(modelname), "ZERO");
    else if (skinid == 290) format(modelname, sizeof(modelname), "ROSE");
    else if (skinid == 291) format(modelname, sizeof(modelname), "PAUL");
    else if (skinid == 292) format(modelname, sizeof(modelname), "CESAR");
    else if (skinid == 293) format(modelname, sizeof(modelname), "OGLOC");
    else if (skinid == 294) format(modelname, sizeof(modelname), "WUZIMU");
    else if (skinid == 295) format(modelname, sizeof(modelname), "TORINO");
    else if (skinid == 296) format(modelname, sizeof(modelname), "JIZZY");
    else if (skinid == 297) format(modelname, sizeof(modelname), "MADDOGG");
    else if (skinid == 298) format(modelname, sizeof(modelname), "CAT");
    else if (skinid == 299) format(modelname, sizeof(modelname), "CLAUDE");
    else if (skinid == 300) format(modelname, sizeof(modelname), "LAPDNA");
    else if (skinid == 301) format(modelname, sizeof(modelname), "SFPDNA");
    else if (skinid == 302) format(modelname, sizeof(modelname), "LVPDNA");
    else if (skinid == 303) format(modelname, sizeof(modelname), "LAPDPC");
    else if (skinid == 304) format(modelname, sizeof(modelname), "LAPDPD");
    else if (skinid == 305) format(modelname, sizeof(modelname), "LVPDPC");
    else if (skinid == 306) format(modelname, sizeof(modelname), "WFYCLPD");
    else if (skinid == 307) format(modelname, sizeof(modelname), "VBFYCPD");
    else if (skinid == 308) format(modelname, sizeof(modelname), "WFYCLEM");
    else if (skinid == 309) format(modelname, sizeof(modelname), "WFYCLLV");
    else if (skinid == 310) format(modelname, sizeof(modelname), "CSHERNA");
    else if (skinid == 311) format(modelname, sizeof(modelname), "DSHERNA");
    else format(modelname, sizeof(modelname), "INVALID");
    return modelname;
}
