/* Functions */
forward SaveFirstSpawn(playerid);
public SaveFirstSpawn(playerid)
{
    for (new i = 0; i < 20; i++) SendClientMessage(playerid, -1, " ");
    // OnPlayerConnect delays this callback by 1 second, so this keeps LoginScreenTD visible for 7 seconds total.
    SetTimerEx("SaveFirstSpawn2", 6000, false, "i", playerid);
	return 1;
}

forward SaveFirstSpawn2(playerid);
public SaveFirstSpawn2(playerid)
{
    HideLoginScreenTD(playerid);
    HideThurXProjectTD(playerid);
    SetTimerEx("SaveFirstSpawn3", 100, false, "i", playerid);
	return 1;
}

forward SaveFirstSpawn3(playerid);
public SaveFirstSpawn3(playerid)
{
    HideThurXProjectTD(playerid);
	if(!AccountData[playerid][IsLoggedIn])
	{
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerInterior(playerid, 0);
		TogglePlayerSpectating(playerid, true);
		static string[144];

		SetPlayerJoinCamera(playerid);

		if(IsUCPLoggedIn(playerid, AccountData[playerid][pUCP]))
		{
			format(string, sizeof(string), "[Anti-Double Login] UCP %s sudah ada di dalam server pada platform lain!", AccountData[playerid][pUCP]);
			SendClientMessage(playerid, X11_RED, string);
			return KickEx(playerid);
		}
		else
		{
			mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `player_ucp` WHERE `UCP` = '%e' LIMIT 1", AccountData[playerid][pUCP]);
			mysql_pquery(g_SQL, string, "CheckPlayerUCP", "id", playerid, g_MysqlRaceCheck[playerid]);
		}
	}
    return 1;
}

StartLoginTimeout(playerid)
{
	if(pLoginTimer[playerid] != -1)
		return 1;

	pLoginWarningTimer[playerid] = SetTimerEx("OnPlayerLoginWarning", 300000, false, "i", playerid);
	pLoginTimer[playerid] = SetTimerEx("OnPlayerNotLogin", 600000, false, "i", playerid);
	return 1;
}

StopLoginTimeout(playerid)
{
	if(pLoginWarningTimer[playerid] != -1)
	{
		KillTimer(pLoginWarningTimer[playerid]);
		pLoginWarningTimer[playerid] = -1;
	}

	if(pLoginTimer[playerid] != -1)
	{
		KillTimer(pLoginTimer[playerid]);
		pLoginTimer[playerid] = -1;
	}
	return 1;
}

forward StopMissPassed(playerid);
public StopMissPassed(playerid)
{
    PlayerPlaySound(playerid, 1188, 0.0, 0.0, 0.0);
    PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
    return 1;
}

forward LoadPlayerDocuments(playerid);
public LoadPlayerDocuments(playerid)
{
    new count = cache_num_rows(), type;
    if(count)
    {
        for(new i; i < count; i++)
		{
            cache_get_value_name_int(i, "Type", type);

            switch(type)
            {
                case 1:
                {
                    DocumentInfo[playerid][BPJS] = true;
                    cache_get_value_name_int(i, "BPJS_Class", DocumentInfo[playerid][BPJSClass]);
                    cache_get_value_name_int(i, "BPJS_Dur", DocumentInfo[playerid][BPJSDur]);
                    cache_get_value_name(i, "BPJS_Issuer", DocumentInfo[playerid][BPJSIssuer]);
                    cache_get_value_name(i, "BPJS_IssuerRank", DocumentInfo[playerid][BPJSIssuerRank]);
                    cache_get_value_name(i, "BPJS_IssueDate", DocumentInfo[playerid][BPJSIssueDate]);
                }
                case 2:
                {
                    DocumentInfo[playerid][SKS] = true;
                    cache_get_value_name_int(i, "SKS_Dur", DocumentInfo[playerid][SKSDur]);
                    cache_get_value_name(i, "SKS_Text", DocumentInfo[playerid][SKSText]);
                    cache_get_value_name(i, "SKS_Issuer", DocumentInfo[playerid][SKSIssuer]);
                    cache_get_value_name(i, "SKS_IssuerRank", DocumentInfo[playerid][SKSIssuerRank]);
                    cache_get_value_name(i, "SKS_IssueDate", DocumentInfo[playerid][SKSIssueDate]);
                }
                case 3:
                {
                    DocumentInfo[playerid][SKCK] = true;
                    cache_get_value_name_int(i, "SKCK_Dur", DocumentInfo[playerid][SKCKDur]);
                    cache_get_value_name(i, "SKCK_Text", DocumentInfo[playerid][SKCKText]);
                    cache_get_value_name(i, "SKCK_Issuer", DocumentInfo[playerid][SKCKIssuer]);
                    cache_get_value_name(i, "SKCK_IssuerRank", DocumentInfo[playerid][SKCKIssuerRank]);
                    cache_get_value_name(i, "SKCK_IssueDate", DocumentInfo[playerid][SKCKIssueDate]);
                }
                case 4:
                {
                    DocumentInfo[playerid][SKWB] = true;
                    cache_get_value_name_int(i, "SKWB_Dur", DocumentInfo[playerid][SKWBDur]);
                    cache_get_value_name(i, "SKWB_Text", DocumentInfo[playerid][SKWBText]);
                    cache_get_value_name(i, "SKWB_Issuer", DocumentInfo[playerid][SKWBIssuer]);
                    cache_get_value_name(i, "SKWB_IssuerRank", DocumentInfo[playerid][SKWBIssuerRank]);
                    cache_get_value_name(i, "SKWB_IssueDate", DocumentInfo[playerid][SKWBIssueDate]);
                }
                case 5:
                {
                    DocumentInfo[playerid][SP] = true;
                    cache_get_value_name_int(i, "SP_Dur", DocumentInfo[playerid][SPDur]);
                    cache_get_value_name(i, "SP_Text", DocumentInfo[playerid][SPText]);
                    cache_get_value_name(i, "SP_Issuer", DocumentInfo[playerid][SPIssuer]);
                    cache_get_value_name(i, "SP_IssuerRank", DocumentInfo[playerid][SPIssuerRank]);
                    cache_get_value_name(i, "SP_IssueDate", DocumentInfo[playerid][SPIssueDate]);
                }
            }
        }
        printf("[Player Documents Loaded] %s [DBID: %d]", AccountData[playerid][pUCP], AccountData[playerid][pID]);
    }
    return 1;
}

forward SetPlayerToUnfreeze(playerid, Float:x, Float:y, Float:z, Float:a);
public SetPlayerToUnfreeze(playerid, Float:x, Float:y, Float:z, Float:a)
{	
    AccountData[playerid][pTeleported] = false;
    AccountData[playerid][pFreeze] = false;
    SetPlayerPos(playerid, x, y, z);
	SetPlayerFacingAngle(playerid, a);
    TogglePlayerControllable(playerid, true);
    return 1;
}

forward SetVehicleToUnfreeze(playerid, vehicleid, Float:x, Float:y, Float:z, Float:a);
public SetVehicleToUnfreeze(playerid, vehicleid, Float:x, Float:y, Float:z, Float:a)
{
    AccountData[playerid][pTeleported] = false;
    AccountData[playerid][pFreeze] = false;
    SetVehiclePos(vehicleid, x, y, z);
	SetVehicleZAngle(vehicleid, a);
    TogglePlayerControllable(playerid, true);
    return 1;
}

forward _KickPlayerDelayed(playerid);
public _KickPlayerDelayed(playerid)
{
	Kick(playerid);
	return 1;
}

/*
forward serverTimer();
public serverTimer()
{
	//Date and Time Textdraw
	new hours;

	// Increase server uptime
	up_seconds ++;
	if(up_seconds == 60)
	{
	    up_seconds = 0, up_minutes ++;
	    if(up_minutes == 60)
	    {
	        up_minutes = 0, up_hours ++;
	        if(up_hours == 24) up_hours = 0, up_days ++;
			new rand = RandomEx(0, 20);
			if(hours > 18)
			{
				SetWorldTime(23);
				WorldTime = 23;
			}
			else
			{
				SetWorldTime(hours);
				WorldTime = hours;
			}
			SetWeather(rand);
			WorldWeather = rand;

			// Sync Server
			//mysql_pquery(g_SQL, "OPTIMIZE TABLE `businesses`,`toys`,`vehicles`");
		}
	}
}
*/

forward Float:GetXYInFrontOfPlayer(playerid, &Float:X, &Float:Y, Float:distance);
public Float:GetXYInFrontOfPlayer(playerid, &Float:X, &Float:Y, Float:distance)
{
	new Float:A;
	GetPlayerPos(playerid, X, Y, A);

	if(IsPlayerInAnyVehicle(playerid)) GetVehicleZAngle(GetPlayerVehicleID(playerid), A);
	else GetPlayerFacingAngle(playerid, A);

	X += (distance * floatsin(-A, degrees));
	Y += (distance * floatcos(-A, degrees));

	return A;
}

forward EndSmoking(playerid);
public EndSmoking(playerid)
{
	if(!IsPlayerConnected(playerid)) return 0;
	if(!AccountData[playerid][pIsSmoking]) return 0;
	if(!AccountData[playerid][pIsSmokeBlowing]) return 0;

    AccountData[playerid][pStress] --;
    if(AccountData[playerid][pUsingJoint])
    {
        new Float:parmour;
        GetPlayerArmour(playerid, parmour);
        SetPlayerArmourEx(playerid, parmour+5);
        if(parmour > 100)
            SetPlayerArmourEx(playerid, 100.0);
    }

	if(AccountData[playerid][pSmokedTimes] >= 6)
	{
        if(pIsVaping[playerid])
            RemovePlayerAttachedObject(playerid, 8);

		AccountData[playerid][pSmokedTimes] = 0;
		AccountData[playerid][pIsSmoking] = false;
        AccountData[playerid][pUsingJoint] = false;
		ShowTDN(playerid, NOTIFICATION_WARNING, "Joint atau rokok anda telah habis sebatang.");
	}
	AccountData[playerid][pIsSmokeBlowing] = false;

    if(pIsVaping[playerid])
    {
        RemovePlayerAttachedObject(playerid, 9);
    }
    else
    {
        RemovePlayerAttachedObject(playerid, 8);
    }
    ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.1, false, false, false, false, 0, true);
	ClearAnimations(playerid, true);
	return 1;
}

forward StartSmoking(playerid);
public StartSmoking(playerid)
{
	if(!IsPlayerConnected(playerid)) return 0;
	if(!AccountData[playerid][pIsSmoking]) return 0;
	if(!AccountData[playerid][pIsSmokeBlowing]) return 0;

    if(pIsVaping[playerid])
    {
        SetPlayerAttachedObject(playerid, 9, 18716, 2, 0.074000, -1.191000, 0.026997, -97.299995, 7.100001, 73.799980, 1.000000, 1.000000, 1.000000);
        SetTimerEx("EndSmoking", 4255, false, "i", playerid);
    }
    else
    {
	    SetPlayerAttachedObject(playerid, 8, 18677, 2, 0.000000, 0.165999, -1.623000, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000);
	    SetTimerEx("EndSmoking", 3600, false, "i", playerid);
    }
	return 1;
}

forward OnPlayerNotLogin(playerid);
public OnPlayerNotLogin(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        StopLoginTimeout(playerid);
        return 0;
    }

    if(AccountData[playerid][IsLoggedIn] || InCharSelection[playerid] || AVC_PConnected[playerid])
    {
        StopLoginTimeout(playerid);
        return 1;
    }

    StopLoginTimeout(playerid);
    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Login", "Kamu dikeluarkan dari server karena terlalu lama berada di alur login.", "Quit", "");
	KickEx(playerid);
    return 1;
}

forward OnPlayerLoginWarning(playerid);
public OnPlayerLoginWarning(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        pLoginWarningTimer[playerid] = -1;
        return 0;
    }

    pLoginWarningTimer[playerid] = -1;

    if(!AccountData[playerid][IsLoggedIn] && !InCharSelection[playerid] && !AVC_PConnected[playerid])
    {
        SendClientMessage(playerid, Y_RED, "PERINGATAN: Kamu sudah terlalu lama berada di alur login. Segera login atau kamu akan dikeluarkan dari server.");
    }
    return 1;
}

forward OnFactionDeposit(playerid, id);
public OnFactionDeposit(playerid, id)
{
    AccountData[playerid][pMenuShowed] = false;
    FactionBrankas[id][factionBrankasID] = cache_insert_id();
    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyimpan item tersebut.");
    return 1;
}

InsertFactionVaultLog(playerid, const itemName[], quant, const factName[])
{
    static jhjss[512];
    mysql_format(g_SQL, jhjss, sizeof(jhjss), "INSERT INTO `faction_vaultlogs` (`Name`, `UCP`, `Item`, `Quantity`, `Faction`, `Time`) VALUES ('%e', '%e', '%e', %d, '%e', CURRENT_TIMESTAMP())", AccountData[playerid][pName], AccountData[playerid][pUCP], itemName, quant, factName);
    mysql_pquery(g_SQL, jhjss);
    return 1;
}

InsertFactionLog(const actvity[], const susName[], const factionName[])
{
    static jhjss[512];
    mysql_format(g_SQL, jhjss, sizeof(jhjss), "INSERT INTO `faction_logs` (`SusName`, `Activity`, `Faction`, `Time`) VALUES ('%e', '%e', '%e', CURRENT_TIMESTAMP())", susName, actvity, factionName);
    mysql_pquery(g_SQL, jhjss);
    return 1;
}

forward ResetAntiBH(playerid);
public ResetAntiBH(playerid)
{
    AccountData[playerid][AntiBHOP] = 0;
    return 1;
}

forward HideKillEffTD(playerid);
public HideKillEffTD(playerid) 
{
	if (!AccountData[playerid][pKillEffectTDShown])
    {
        KillTimer(AccountData[playerid][pKillEffectTimer]);
        AccountData[playerid][pKillEffectTimer] = -1;
	    return 0;
    }

    KillTimer(AccountData[playerid][pKillEffectTimer]);
    AccountData[playerid][pKillEffectTimer] = -1;

    SetPlayerDrunkLevel(playerid, 0);
	AccountData[playerid][pKillEffectTDShown] = false;
	return TextDrawHideForPlayer(playerid, KillEffectTD);
}

forward HidePlayerFooter(playerid);
public HidePlayerFooter(playerid) 
{
	if (!AccountData[playerid][pShowFooter])
    {
        KillTimer(AccountData[playerid][pFooterTimer]);
        AccountData[playerid][pFooterTimer] = -1;
	    return 0;
    }

    KillTimer(AccountData[playerid][pFooterTimer]);
    AccountData[playerid][pFooterTimer] = -1;

	AccountData[playerid][pShowFooter] = false;
	return PlayerTextDrawHide(playerid, FooterTD[playerid]);
}

forward CheckClaimedSP(playerid);
public CheckClaimedSP(playerid)
{
	if(cache_num_rows())
	{
		new isclaimed;

		cache_get_value_name_int(0, "claimedSP", isclaimed);

		if(isclaimed)
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah pernah klaim dan tidak dapat melakukannya lagi!");
		
        ApplyAnimation(playerid, "SWEET", "Sweet_injuredloop", 4.0, true, false, false, true, 0, true);

        pKompensasiTimer[playerid] = true;
        AccountData[playerid][pActivityTime] = 1;
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "SEMBAHYANG");
        ShowProgressBar(playerid);
	}
	return 1;
}
