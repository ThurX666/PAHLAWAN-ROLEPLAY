YCMD:ado(playerid, params[], help)
{
    static string[164], Float:x, Float:y, Float:z;

    if(isnull(params)) return SyntaxMsg(playerid, "/ado [text]~n~Use '/ado off' to remove text.");

    if(strlen(params) > 128) return ShowTDN(playerid, NOTIFICATION_ERROR, "Panjang text maksimal adalah 128 karakter!");

    if (!strcmp(params, "off", true))
    {
        if (!AccountData[playerid][pAdoActive]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada text yang dapat dihapus!");

        if (DestroyDynamic3DTextLabel(AccountData[playerid][pAdoTag]))
            AccountData[playerid][pAdoTag] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        ShowTDN(playerid, NOTIFICATION_SUCCESS, "Text berhasil dihapus.");
        AccountData[playerid][pAdoActive] = false;
        return 1;
    }

    FixText(params);
    format(string, sizeof(string), "* %s [%d]*\n(( %s ))", AccountData[playerid][pUCP], playerid, params);

	if(GetPVarType(playerid, "Caps")) UpperToLower(params);

    GetPlayerPos(playerid, x, y, z);
    if(AccountData[playerid][pAdoActive])
    {
        if (IsValidDynamic3DTextLabel(AccountData[playerid][pAdoTag]))
            UpdateDynamic3DTextLabelText(AccountData[playerid][pAdoTag], X11_PLUM1, string);
        else
            AccountData[playerid][pAdoTag] = CreateDynamic3DTextLabel(string, X11_PLUM1, x, y, z, 15, _, _, 1, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
    }
    else
    {
        AccountData[playerid][pAdoActive] = true;
        AccountData[playerid][pAdoTag] = CreateDynamic3DTextLabel(string, X11_PLUM1, x, y, z, 15, _, _, 1, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
    }
    return 1;
}

YCMD:me(playerid, params[], help)
{
	static
	    string[144], action[144];

	if(sscanf(params, "s[144]", action))
		return SUM(playerid, "/me [action]");

	format(string, sizeof(string), "* %s", action);
 	SetPlayerChatBubble(playerid, string, X11_PLUM1, 30.0, 10000);

 	SendClientMessageEx(playerid, X11_WHITE, "(Action) "PLUM1"%s", action);
	return 1;
}

YCMD:do(playerid, params[], help)
{
	static
	    string[144], action[144];

	if(sscanf(params, "s[144]", action))
		return SUM(playerid, "/do [action]");

	format(string, sizeof(string), "* %s", action);
 	SetPlayerChatBubble(playerid, string, X11_LIGHTGREEN, 30.0, 10000);

 	SendClientMessageEx(playerid, X11_WHITE, "(Action) "PLUM1"%s", action);
	return 1;
}

// YCMD:me(playerid, params[], help)
// {
// 	static action[144];
// 	if(sscanf(params, "s[144]", action))
// 		return SyntaxMsg(playerid, "/me [action]");

// 	if(strlen(action) > 64)
// 	{
// 		SendNearbyMessage(playerid, 20.0, X11_PLUM1, "* %s %.64s", GetPlayerRoleplayName(playerid), action);
// 		SendNearbyMessage(playerid, 20.0, X11_PLUM1, "...%s", action[64]);
// 	}
// 	else SendNearbyMessage(playerid, 20.0, X11_PLUM1, "* %s %s", GetPlayerRoleplayName(playerid), action);
// 	return 1;
// }

// YCMD:lme(playerid, params[], help)
// {
// 	static action[144];

// 	if(sscanf(params, "s[144]", action))
// 		return SyntaxMsg(playerid, "/lme [action]");

// 	if(strlen(action) > 64)
// 	{
// 		SendNearbyMessage(playerid, 10.0, 0xA98789FF, "* %s %.64s", GetPlayerRoleplayName(playerid), action);
// 		SendNearbyMessage(playerid, 10.0, 0xA98789FF, "...%s", action[64]);
// 	}
// 	else SendNearbyMessage(playerid, 10.0, 0xA98789FF, "* %s %s", GetPlayerRoleplayName(playerid), action);
// 	return 1;
// }

// YCMD:do(playerid, params[], help)
// {
// 	static action[144];
// 	if(sscanf(params, "s[144]", action))
// 		return SyntaxMsg(playerid, "/do [action]");

// 	if(strlen(action) > 64)
// 	{
// 		SendNearbyMessage(playerid, 20.0, X11_PLUM1, "* %.64s", action);
// 		SendNearbyMessage(playerid, 20.0, X11_PLUM1, "...%s (( %s ))", action[64], GetPlayerRoleplayName(playerid));
// 	}
// 	else SendNearbyMessage(playerid, 20.0, X11_PLUM1, "* %s (( %s ))", action, GetPlayerRoleplayName(playerid));
// 	return 1;
// }

// YCMD:ldo(playerid, params[], help)
// {
// 	static action[144];
// 	if(sscanf(params, "s[144]", action))
// 		return SyntaxMsg(playerid, "/ldo [action]");

// 	if(strlen(action) > 64)
// 	{
// 		SendNearbyMessage(playerid, 10.0, 0xA98789FF, "* %.64s", action);
// 		SendNearbyMessage(playerid, 10.0, 0xA98789FF, "...%s (( %s ))", action[64], GetPlayerRoleplayName(playerid));
// 	}
// 	else SendNearbyMessage(playerid, 10.0, 0xA98789FF, "* %s (( %s ))", action, GetPlayerRoleplayName(playerid));
// 	return 1;
// }

YCMD:pm(playerid, params[], help)
{
	new
		playerb,
		text[144]
	;

	if(sscanf(params, "ds[144]", playerb, text))
		return SUM(playerid, "/pm [playerid] [teks]");

	if(!IsPlayerConnected(playerb)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    if(playerb == playerid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya terhadap diri sendiri!");
	
	if(AccountData[playerb][pAdminDuty]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak boleh PM admin on duty!");

	if(AccountData[playerid][pAdminDuty])
	{
		SendClientMessageEx(playerb, X11_LIGHTGOLDENRODYELLOW, "(( PM from "RED"%s (ID: %d): "LIGHTGOLDENRODYELLOW"%s ))", AccountData[playerid][pAdminname], playerid, text);
	}
	else
	{
		if(!ToggleInfo[playerb][TogPM]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut mematikan PM!");
		
		SendClientMessageEx(playerb, X11_LIGHTGOLDENRODYELLOW, "(( PM from %s (ID: %d): %s ))", AccountData[playerid][pName], playerid, text);
	}
	PlayerPlaySound(playerb, 5202, 0.0, 0.0, 0.0);

	SendClientMessageEx(playerid, X11_BISQUE3, "(( PM sent to %s (ID: %d): %s ))", AccountData[playerb][pName], playerb, text);
	PlayerPlaySound(playerid, 5205, 0.0, 0.0, 0.0);

	foreach(new i : Player) if(AccountData[i][pAdmin] > 1 && AccountData[i][pSPY])
    {
        SendClientMessageEx(i, X11_LIGHTGOLDENRODYELLOW, "[SPY PM] %s (%d) to %s (%d): %s", AccountData[playerid][pName], playerid, AccountData[playerb][pName], playerb, text);
    }
	return 1;
}

/*
YCMD:whisper(playerid, params[], help)
{
	new text[128], otherid;
    if(sscanf(params, "us[128]", otherid, text))
        return SUM(playerid, "/(w)hisper [playerid/Part Of Name] [text]");

    if(otherid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, otherid, 5.0)) return SEM(playerid, "Pemain tersebut tidak ada / tidak dekat dengan anda!");

    if(otherid == playerid) return SEM(playerid, "You cannot do that to yourself!");

	if(GetPVarType(playerid, "Caps")) UpperToLower(params);
    if(strlen(text) > 64) 
	{
        SendClientMessageEx(otherid, X11_LIGHTGOLDENRODYELLOW, "> Whisper from %s (%d): %.64s", GetPlayerRoleplayName(playerid), playerid, text);
        SendClientMessageEx(otherid, X11_LIGHTGOLDENRODYELLOW, "...%s **", text[64]);

        SendClientMessageEx(playerid, X11_LIGHTGOLDENRODYELLOW, "> Whisper to %s (%d): %.64s", GetPlayerRoleplayName(otherid), otherid, text);
        SendClientMessageEx(playerid, X11_LIGHTGOLDENRODYELLOW, "...%s **", text[64]);
    }
    else 
	{
        SendClientMessageEx(otherid, X11_LIGHTGOLDENRODYELLOW, "> Whisper from %s (%d): %s **", GetPlayerRoleplayName(playerid), playerid, text);
        SendClientMessageEx(playerid, X11_LIGHTGOLDENRODYELLOW, "> Whisper to %s (%d): %s **", GetPlayerRoleplayName(otherid), otherid, text);
    }
    SendRPMeAboveHead(playerid, "Membisikkan sesuatu pada telinga orang di sekitarnya", X11_PLUM1);

	foreach(new i : Player) if(AccountData[i][pAdmin] > 1 && AccountData[i][pSPY])
    {
        SendClientMessageEx(i, X11_LIGHTGOLDENRODYELLOW, "[SPY Whisper] %s (%d) to %s (%d): %s", GetPlayerRoleplayName(playerid), playerid, GetPlayerRoleplayName(otherid), otherid, text);
    }
    return 1;
}
*/
//YCMD:w(playerid, params[], help) = whisper;

/*
YCMD:low(playerid, params[], help)
{
    if(isnull(params))
        return SUM(playerid, "/l(ow) [teks]");

	if(GetPVarType(playerid, "Caps")) UpperToLower(params);
	if(IsPlayerInAnyVehicle(playerid))
	{
		foreach(new i : Player)
		{
			if(IsPlayerInAnyVehicle(i) && GetPlayerVehicleID(i) == GetPlayerVehicleID(playerid))
			{
				if(strlen(params) > 64) 
				{
					SendClientMessageEx(i, X11_WHITE, "[car] %s[%d]: %.64s ..", GetPlayerRoleplayName(playerid), playerid, params);
					SendClientMessageEx(i, X11_WHITE, "...%s", params[64]);
				}
				else 
				{
					SendClientMessageEx(i, X11_WHITE, "[car] %s[%d]: %s", GetPlayerRoleplayName(playerid), playerid, params);
				}
				printf("[CAR] %s(%d) : %s", GetPlayerRoleplayName(playerid), playerid, params);
			}
		}
	}
	else
	{
		if(strlen(params) > 64) 
		{
			SendNearbyMessage(playerid, 2.0, X11_WHITE, "[low] %s[%d]: %.64s ..", GetPlayerRoleplayName(playerid), playerid, params);
			SendNearbyMessage(playerid, 2.0, X11_WHITE, "...%s", params[64]);
		}
		else 
		{
			SendNearbyMessage(playerid, 2.0, X11_WHITE, "[low] %s[%d]: %s", GetPlayerRoleplayName(playerid), playerid, params);
		}
		printf("[LOW] %s(%d) : %s", GetPlayerRoleplayName(playerid), playerid, params);
	}
    return 1;
}
YCMD:l(playerid, params[], help) = low;

YCMD:shout(playerid, params[], help)
{
	if(isnull(params))
		return SUM(playerid, "/s(hout) [teks]");

	if(!AccountData[playerid][pSpawned] && !AccountData[playerid][IsLoggedIn]) return SEM(playerid, "You cannot do that at the moment!");

	new bool:isCaps = false;

	for( new i, j = strlen( params )-1; i < j; i ++ )
    {
        if( ( 'A' <= params[ i ] <= 'Z' ) && ( 'A' <= params[ i+1 ] <= 'Z' ) )
            isCaps = true;
    }

	if(isCaps)
	{
		if(strlen(params) > 64)
		{
			SendNearbyMessage(playerid, 40.0, X11_ORANGE1, "%s screams: %.64s", GetPlayerRoleplayName(playerid), params);
			SendNearbyMessage(playerid, 40.0, X11_ORANGE1, "...%s!", params[64]);
		}
		else SendNearbyMessage(playerid, 40.0, X11_ORANGE1, "%s screams: %s!", GetPlayerRoleplayName(playerid), params);
	}
	else
	{
		if(strlen(params) > 64)
		{
			SendNearbyMessage(playerid, 30.0, X11_ORANGE1, "%s shouts: %.64s", GetPlayerRoleplayName(playerid), params);
			SendNearbyMessage(playerid, 30.0, X11_ORANGE1, "...%s!", params[64]);
		}
		else SendNearbyMessage(playerid, 30.0, X11_ORANGE1, "%s shouts: %s!", GetPlayerRoleplayName(playerid), params);
	}
	SetPlayerChatBubble(playerid, params, X11_ORANGE1, 30.0, 6000);
	return 1;
}
YCMD:s(playerid, params[], help) = shout;
*/

// YCMD:b(playerid, params[], help)
// {
// 	static string[144];
//     if(sscanf(params, "s[144]", string))
//         return SUM(playerid, "/b [teks]");

// 	if(AccountData[playerid][pAdminDuty])
// 	{
// 		if(strlen(string) > 64)
// 		{
// 			SendNearbyMessage(playerid, 10.0, X11_RED, "%s: "WHITE"(( %.64s... ", AccountData[playerid][pAdminname], string);
// 			SendNearbyMessage(playerid, 10.0, X11_WHITE, "...%s ))", string[64]);
// 		}
// 		else 
// 		{
// 			SendNearbyMessage(playerid, 10.0, X11_RED, "%s: "WHITE"(( %s ))", AccountData[playerid][pAdminname], string);
// 		}
// 	}
// 	else
// 	{
// 		if(strlen(string) > 64)
// 		{
// 			SendNearbyMessage(playerid, 10.0, X11_WHITE, "%s: (( %.64s... ", GetPlayerRoleplayName(playerid), string);
// 			SendNearbyMessage(playerid, 10.0, X11_WHITE, "...%s ))", string[64]);
// 		}
// 		else 
// 		{
// 			SendNearbyMessage(playerid, 10.0, X11_WHITE, "%s: (( %s ))", GetPlayerRoleplayName(playerid), string);
// 		}
// 	}
//     return 1;
// }

YCMD:b(playerid, params[], help)
{
	static string[144];
    if(sscanf(params, "s[144]", string))
        return SyntaxMsg(playerid, "/b [teks]");

	if(AccountData[playerid][pAdminDuty])
	{
		if(!AccountData[playerid][pSteward])
		{
			if(strlen(string) > 64)
			{
				SendNearbyMessage(playerid, 10.0, X11_WHITE, "[L] %s "RED"%s: "GOLD"(( "WHITE"%.64s...", GetAdminLevel(playerid), AccountData[playerid][pAdminname], string);
				SendNearbyMessage(playerid, 10.0, X11_WHITE, "...%s "GOLD"))", string[64]);
			}
			else 
			{
				SendNearbyMessage(playerid, 10.0, X11_WHITE, "[L] %s "RED"%s: "GOLD"(( "WHITE"%s "GOLD"))", GetAdminLevel(playerid), AccountData[playerid][pAdminname], string);
			}
		}
		else
		{
			if(strlen(string) > 64)
			{
				SendNearbyMessage(playerid, 10.0, X11_WHITE, "[L] The Stewards "AQUAMARINE"%s: "GOLD"(( "WHITE"%.64s...", AccountData[playerid][pAdminname], string);
				SendNearbyMessage(playerid, 10.0, X11_WHITE, "...%s "GOLD"))", string[64]);
			}
			else 
			{
				SendNearbyMessage(playerid, 10.0, X11_WHITE, "[L] The Stewards "AQUAMARINE"%s: "GOLD"(( "WHITE"%s "GOLD"))", AccountData[playerid][pAdminname], string);
			}
		}
	}
	else
	{
		if(strlen(string) > 64)
		{
			SendNearbyMessage(playerid, 10.0, X11_WHITE, "[L] %s "WHITE"%s [%d]: "GOLD"(( "WHITE"%.64s...", GetPlayerLevelName(playerid), AccountData[playerid][pUCP], playerid, string);
			SendNearbyMessage(playerid, 10.0, X11_WHITE, "...%s "GOLD"))", string[64]);
		}
		else 
		{
			SendNearbyMessage(playerid, 10.0, X11_WHITE, "[L] %s "WHITE"%s [%d]: "GOLD"(( "WHITE"%s "GOLD"))", GetPlayerLevelName(playerid), AccountData[playerid][pUCP], playerid, string);
		}
	}
    return 1;
}

// YCMD:ooc(playerid, params[], help)
// {
// 	if(!TogOOC && AccountData[playerid][pAdmin] < 1 && !AccountData[playerid][pSteward] && AccountData[playerid][pVIP] < 1)  return SEM(playerid, "Global OOC Chat sedang dinonaktifkan.");

//     if(isnull(params))
//         return SUM(playerid, "/o [global OOC]");

//     if(strlen(params) < 144)
//     {
// 		if(AccountData[playerid][pAdminDuty])
// 		{
// 			foreach (new i : Player)
// 			{
// 				if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && ToggleInfo[i][TogGOOC])
// 				{
// 					if(!AccountData[playerid][pSteward])
// 					{
// 						if(strlen(params) > 64)
// 						{
// 							SendClientMessageEx(i, X11_WHITE, "(( "RED"%s: "WHITE"%.64s...", AccountData[playerid][pAdminname], params);
// 							SendClientMessageEx(i, X11_WHITE, "...%s ))", params[64]);
// 						}
// 						else
// 						{
// 							SendClientMessageEx(i, X11_WHITE, "(( "RED"%s: "WHITE"%s ))", AccountData[playerid][pAdminname], params);
// 						}
// 					}
// 					else
// 					{
// 						if(strlen(params) > 64)
// 						{
// 							SendClientMessageEx(i, X11_WHITE, "(( The Stewards "AQUAMARINE"%s: "WHITE"%.64s...", AccountData[playerid][pAdminname], params);
// 							SendClientMessageEx(i, X11_WHITE, "...%s ))", params[64]);
// 						}
// 						else
// 						{
// 							SendClientMessageEx(i, X11_WHITE, "(( The Stewards "AQUAMARINE"%s: "WHITE"%s ))", AccountData[playerid][pAdminname], params);
// 						}
// 					}
// 				}
// 			}
// 		}
// 		else
// 		{
// 			if(AccountData[playerid][pVIP] > 0)
// 			{
// 				if(!isnull(DonatorData[playerid][pDTag]))
// 				{
// 					foreach (new i : Player)
// 					{
// 						if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && ToggleInfo[i][TogGOOC])
// 						{
// 							if(strlen(params) > 64)
// 							{
// 								SendClientMessageEx(i, X11_WHITE, "(( %s %s: "WHITE"%.64s...", ColouredText(DonatorData[playerid][pDTag]), AccountData[playerid][pName], params);
// 								SendClientMessageEx(i, X11_WHITE, "...%s ))", params[64]);
// 							}
// 							else
// 							{
// 								SendClientMessageEx(i, X11_WHITE, "(( %s %s: "WHITE"%s ))", ColouredText(DonatorData[playerid][pDTag]), AccountData[playerid][pName], params);
// 							}
// 						}
// 					}
// 				}
// 				else
// 				{
// 					foreach (new i : Player)
// 					{
// 						if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && ToggleInfo[i][TogGOOC])
// 						{
// 							if(strlen(params) > 64)
// 							{
// 								SendClientMessageEx(i, X11_WHITE, "(( Donatur %s: %.64s...", AccountData[playerid][pName], params);
// 								SendClientMessageEx(i, X11_WHITE, "...%s ))", params[64]);
// 							}
// 							else
// 							{
// 								SendClientMessageEx(i, X11_WHITE, "(( Donatur %s: %s ))", AccountData[playerid][pName], params);
// 							}
// 						}
// 					}
// 				}
// 			}
// 			else
// 			{
// 				foreach (new i : Player)
// 				{
// 					if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && ToggleInfo[i][TogGOOC])
// 					{
// 						if(strlen(params) > 64)
// 						{
// 							SendClientMessageEx(i, X11_WHITE, "(( %s: %.64s...", AccountData[playerid][pName], params);
// 							SendClientMessageEx(i, X11_WHITE, "...%s ))", params[64]);
// 						}
// 						else
// 						{
// 							SendClientMessageEx(i, X11_WHITE, "(( %s: %s ))", AccountData[playerid][pName], params);
// 						}
// 					}
// 				}
// 			}
// 		}
//     }
//     else 
// 		return SEM(playerid, "Panjang pesan maksimum adalah 144 karakter!");
		
//     return 1;
// }

YCMD:ooc(playerid, params[], help)
{
	if(!TogOOC && AccountData[playerid][pAdmin] < 1 && !AccountData[playerid][pSteward] && AccountData[playerid][pVIP] < 1)  return ShowTDN(playerid, NOTIFICATION_ERROR, "Global OOC Chat sedang dinonaktifkan.");

    if(isnull(params))
        return SUM(playerid, "/o [global OOC]");

    if(strlen(params) < 144)
    {
		if(AccountData[playerid][pAdminDuty])
		{
			foreach (new i : Player)
			{
				if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && ToggleInfo[i][TogGOOC])
				{
					if(!AccountData[playerid][pSteward])
					{
						if(strlen(params) > 64)
						{
							SendClientMessageEx(i, X11_WHITE, "[G] %s "RED"%s: "GOLD"(( "WHITE"%.64s...", GetAdminLevel(playerid), AccountData[playerid][pAdminname], params);
							SendClientMessageEx(i, X11_WHITE, "...%s "GOLD"))", params[64]);
						}
						else
						{
							SendClientMessageEx(i, X11_WHITE, "[G] %s "RED"%s: "GOLD"(( "WHITE"%s "GOLD"))", GetAdminLevel(playerid), AccountData[playerid][pAdminname], params);
						}
					}
					else
					{
						if(strlen(params) > 64)
						{
							SendClientMessageEx(i, X11_WHITE, "[G] The Stewards "AQUAMARINE"%s: "GOLD"(( "WHITE"%.64s...", AccountData[playerid][pAdminname], params);
							SendClientMessageEx(i, X11_WHITE, "...%s "GOLD"))", params[64]);
						}
						else
						{
							SendClientMessageEx(i, X11_WHITE, "[G] The Stewards "AQUAMARINE"%s: "GOLD"(( "WHITE"%s "GOLD"))", AccountData[playerid][pAdminname], params);
						}
					}
				}
			}
		}
		else
		{
			if(AccountData[playerid][pVIP] > 0)
			{
				if(!isnull(DonatorData[playerid][pDTag]))
				{
					foreach (new i : Player)
					{
						if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && ToggleInfo[i][TogGOOC])
						{
							if(strlen(params) > 64)
							{
								SendClientMessageEx(i, X11_WHITE, "[G] %s "WHITE"%s [%d]: "GOLD"(( "WHITE"%.64s...", ColouredText(DonatorData[playerid][pDTag]), AccountData[playerid][pUCP], playerid, params);
								SendClientMessageEx(i, X11_WHITE, "...%s "GOLD"))", params[64]);
							}
							else
							{
								SendClientMessageEx(i, X11_WHITE, "[G] %s "WHITE"%s [%d]: "GOLD"(( "WHITE"%s "GOLD"))", ColouredText(DonatorData[playerid][pDTag]), AccountData[playerid][pUCP], playerid, params);
							}
						}
					}
				}
				else
				{
					foreach (new i : Player)
					{
						if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && ToggleInfo[i][TogGOOC])
						{
							if(strlen(params) > 64)
							{
								SendClientMessageEx(i, X11_WHITE, "[G] Donatur %s [%d]: "GOLD"(( "WHITE"%.64s...", AccountData[playerid][pUCP], playerid, params);
								SendClientMessageEx(i, X11_WHITE, "...%s "GOLD"))", params[64]);
							}
							else
							{
								SendClientMessageEx(i, X11_WHITE, "[G] Donatur %s [%d]: "GOLD"(( "WHITE"%s "GOLD"))", AccountData[playerid][pUCP], playerid, params);
							}
						}
					}
				}
			}
			else
			{
				foreach (new i : Player)
				{
					if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && ToggleInfo[i][TogGOOC])
					{
						if(strlen(params) > 64)
						{
							SendClientMessageEx(i, X11_WHITE, "[G] %s "WHITE"%s [%d]: "GOLD"(( "WHITE"%.64s...", GetPlayerLevelName(playerid), AccountData[playerid][pUCP], playerid, params);
							SendClientMessageEx(i, X11_WHITE, "...%s "GOLD"))", params[64]);
						}
						else
						{
							SendClientMessageEx(i, X11_WHITE, "[G] %s "WHITE"%s [%d]: "GOLD"(( "WHITE"%s "GOLD"))", GetPlayerLevelName(playerid), AccountData[playerid][pUCP], playerid, params);
						}
					}
				}
			}
		}
    }
    else 
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Maksimal panjang text 144 karakter!");
		
    return 1;
}
YCMD:o(playerid, params[], help) = ooc;

YCMD:dice(playerid, params[], help)
{
	static action;
	if(sscanf(params, "d", action))
		return SUM(playerid, "/dice [type dice] (1. One Dice | 2. Two Dices)");

	if(action < 1 || action > 2)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda hanya dapat memasukkan 1 atau 2!");
	
	static rand;
	if(action == 1)
	{
		rand = random(7);
		SendNearbyMessage(playerid, 20.0, X11_PLUM1, "** %s tosses a dice into the air, and the dice displayed the value of "RED"%d.", GetPlayerRoleplayName(playerid), rand);
	}
	else
	{
		rand = random(13);
		SendNearbyMessage(playerid, 20.0, X11_PLUM1, "** %s tosses two dices into the air, and the dices displayed the value of "RED"%d.", GetPlayerRoleplayName(playerid), rand);
	}
	return 1;
}

YCMD:attempt(playerid, params[], help)
{
	static action[144];
	if(sscanf(params, "s[144]", action))
		return SUM(playerid, "/attempt [action]");

	static rand;
	if(strlen(action) > 64)
	{
		rand = random(6);
		switch(rand)
		{
			case 0..2:
			{
				SendNearbyMessage(playerid, 20.0, X11_PLUM1, "** %s attempts to %.64s", GetPlayerRoleplayName(playerid), action);
				SendNearbyMessage(playerid, 20.0, X11_PLUM1, "...%s, but fail.", action[64]);
			}
			case 3..5:
			{
				SendNearbyMessage(playerid, 20.0, X11_PLUM1, "** %s attempts to %.64s", GetPlayerRoleplayName(playerid), action);
				SendNearbyMessage(playerid, 20.0, X11_PLUM1, "...%s, and success.", action[64]);
			}
		}
	}
	else 
	{
		rand = random(6);
		switch(rand)
		{
			case 0..2:
			{
				SendNearbyMessage(playerid, 20.0, X11_PLUM1, "** %s attempts to %s, but fail.", GetPlayerRoleplayName(playerid), action);
			}
			case 3..5:
			{
				SendNearbyMessage(playerid, 20.0, X11_PLUM1, "** %s attempts to %s, and success.", GetPlayerRoleplayName(playerid), action);
			}
		}
	}
	return 1;
}

YCMD:appearance(playerid, params[], help)
{
	static type[24], string[128], appstr[144];
	if(sscanf(params, "s[24]S()[128]", type, string)) return SUM(playerid, "/appearance [option] (add | show)");

	if(!strcmp(type, "add", true))
    {
		new appearances[144];
        if(sscanf(string, "s[144]", appearances)) return SUM(playerid, "/appearance [add] [your character appearance]");

		strcopy(AccountData[playerid][pAppearance], appearances);

		format(appstr, sizeof(appstr), "* %s", AccountData[playerid][pAppearance]);
		SetPlayerChatBubble(playerid, appstr, X11_PLUM1, 30.0, 15000);

		SendClientMessageEx(playerid, X11_LIGHTBLUE, "[APPEARANCE] "PLUM1"* %s", AccountData[playerid][pAppearance]);
    }
    else if(!strcmp(type, "show", true))
    {
        if(isnull(AccountData[playerid][pAppearance])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus membuat appearance terlebih dahulu!");
	
		format(appstr, sizeof(appstr), "* %s", AccountData[playerid][pAppearance]);
		SetPlayerChatBubble(playerid, appstr, X11_PLUM1, 30.0, 15000);

		SendClientMessageEx(playerid, X11_LIGHTBLUE, "[APPEARANCE] "PLUM1"* %s", AccountData[playerid][pAppearance]);
	}
	return 1;
}