YCMD:ahelp(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 1)
        return PermissionError(playerid);

    Dialog_Show(playerid, "AdminHelp", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Admin Help", "Volunteer\n"GRAY"Junior Helper\nSenior Helper\n"GRAY"Head Helper\nAdmin Level 1\n"GRAY"Admin Level 2\nAdmin Level 3\n"GRAY"Head Admin\nManagement\n"GRAY"Executive", "Pilih", "Batal");

    return 1;
}

YCMD:a(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 1 && !AccountData[playerid][pSteward] && !AccountData[playerid][pApprentice])
		return PermissionError(playerid);

	if(isnull(params))
        return SUM(playerid, "/a [staff chat]");

	foreach(new i : Player)
	{
		if(AccountData[i][IsLoggedIn] && (AccountData[i][pAdmin] > 0 || AccountData[i][pSteward] || AccountData[i][pApprentice]))
		{
            if(AccountData[playerid][pAdmin] > 0)
                SendClientMessageEx(i, 0x59BD93FF, "* %s %s [%d]: %s", GetAdminLevel(playerid), AccountData[playerid][pAdminname], playerid, params);

			if(AccountData[playerid][pSteward])
			{
				SendClientMessageEx(i, 0x59BD93FF, "* The Stewards %s [%d]: %s", AccountData[playerid][pAdminname], playerid, params);
			}

			if(AccountData[playerid][pApprentice])
			{
                SendClientMessageEx(i, 0x59BD93FF, "* Apprentice %s [%d]: %s", AccountData[playerid][pAdminname], playerid, params);
			}
		}
	}
	return 1;
}

YCMD:aduty(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 1 && !AccountData[playerid][pSteward])
        return PermissionError(playerid);
	
	if(!strcmp(AccountData[playerid][pAdminname], "None"))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Nama admin anda belum ditetapkan, silakan hubungi admin lebih tinggi!");
	
	switch(AccountData[playerid][pAdminDuty])
    {
		case false:
		{
			GetPlayerHealth(playerid, AccountData[playerid][pHealth]);
			SetPlayerColor(playerid, X11_RED);
			SetPlayerHealth(playerid, 99999);
			AccountData[playerid][pAdminDuty] = true;
			SetPlayerName(playerid, AccountData[playerid][pAdminname]);
			
            new adlbel[144];
			if(!AccountData[playerid][pSteward])
			{
				format(adlbel, sizeof(adlbel), "((Staff On Duty))\n%s\n"RED"%s", AccountData[playerid][pAdminname], GetAdminLevel(playerid));
				SendStaffMessage(Y_SERVER, "(AdmDuty) "WHITE"%s "YELLOW"%s "WHITE"sekarang mulai bertugas sebagai "RED"%s.", GetAdminLevel(playerid), AccountData[playerid][pName], AccountData[playerid][pAdminname]);
			}
			else
			{
				format(adlbel, sizeof(adlbel), "((Staff On Duty))\n%s\n"AQUAMARINE"The Stewards", AccountData[playerid][pAdminname]);
				SendStaffMessage(Y_SERVER, "(AdmDuty) "WHITE"Steward "YELLOW"%s "WHITE"sekarang mulai bertugas sebagai "RED"%s.", AccountData[playerid][pName], AccountData[playerid][pAdminname]);
			}
			AdminLabel[playerid] = CreateDynamic3DTextLabel(adlbel, Y_YELLOW, 0.0, 0.0, 0.5, 20.0, playerid, INVALID_VEHICLE_ID, 1, -1, -1, -1, 20.0, -1, 0);
            SetPlayerAttachedObject(playerid, 0, 1254, 2, 0.082, 0.015, 0.009, 0, 90.4, 0, 1, 1.286, 1);
        }
        case true:
        {
            SetPlayerColor(playerid, X11_WHITE);
			SetPlayerHealth(playerid, AccountData[playerid][pHealth]);
            SetPlayerName(playerid, AccountData[playerid][pName]);
            AccountData[playerid][pAdminDuty] = false;

            if(DestroyDynamic3DTextLabel(AdminLabel[playerid]))
				AdminLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

            SendStaffMessage(Y_SERVER, "(AdmDuty) "RED"%s "WHITE"telah selesai bertugas dan kembali sebagai "YELLOW"%s.", AccountData[playerid][pAdminname], AccountData[playerid][pName]);

            RemovePlayerAttachedObject(playerid, 0);

            if(pToys[playerid][0][toy_model] != 0)
            {
                SetPlayerAttachedObject(playerid,
                0,
                pToys[playerid][0][toy_model],
                pToys[playerid][0][toy_bone],
                pToys[playerid][0][toy_x],
                pToys[playerid][0][toy_y],
                pToys[playerid][0][toy_z],
                pToys[playerid][0][toy_rx],
                pToys[playerid][0][toy_ry],
                pToys[playerid][0][toy_rz],
                pToys[playerid][0][toy_sx],
                pToys[playerid][0][toy_sy],
                pToys[playerid][0][toy_sz],
                pToys[playerid][0][matcolor1][4],
                pToys[playerid][0][matcolor2][4]);
            }
        }
    }
	return 1;
}

YCMD:count(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 1)
        return PermissionError(playerid);

    SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"This server has "YELLOW"%d total players.", Iter_Count(Player));
    SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"This server has "YELLOW"%d total vehicles.", Iter_Count(Vehicle));
    return 1;
}

YCMD:vmodels(playerid, params[], help)
{
    static string[2000];

    if(AccountData[playerid][pAdmin] < 1)
        return PermissionError(playerid);

    for (new i = 0; i < sizeof(g_arrVehicleNames); i++) {
        format(string, sizeof(string), "%s%d - %s\n", string, i + 400, g_arrVehicleNames[i]);
    }
    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_LIST, "Vehicle Models", string, "Tutup", "");

    return 1;
}

YCMD:vehname(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 1)
        return PermissionError(playerid);

    SendClientMessage(playerid, X11_ROYALBLUE, "|______________________________|");
    SendClientMessage(playerid, X11_LIGHTGOLDENRODYELLOW, "Vehicle Search:");

    new string[128];

    if (isnull(params)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Keyword kurang specific!");
    if (!params[2]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Keyword terlalu singkat!");

    for (new v; v < sizeof(g_arrVehicleNames); v++) {
        if (strfind(g_arrVehicleNames[v], params, true) != -1) {

            if (isnull(string)) format(string, sizeof(string), "%s (ID %d)", g_arrVehicleNames[v], v + 400);
            else format(string, sizeof(string), "%s | %s (ID %d)", string, g_arrVehicleNames[v], v + 400);
        }
    }

    if (!string[0]) ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ditemukan dari hasil pencarian!");
    else if (string[127]) ShowTDN(playerid, NOTIFICATION_ERROR, "Terlalu banyak hasil pencarian!");
    else SendClientMessageEx(playerid, X11_WHITE, string);

    SendClientMessage(playerid, X11_LIGHTGOLDENRODYELLOW, "--------------------------------------------------------------------------------------------------------------------------------");

    return 1;
}

YCMD:near(playerid, params[], help)
{
    static
        id = -1;

    new vehicleid = GetNearestVehicleToPlayer(playerid, 5.0, false);

    if(AccountData[playerid][pAdmin] < 1)
        return PermissionError(playerid);

    if ((id = BJTable_Nearest(playerid)) != -1)
        SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda berdiri dekat dynamic blackjack table ID: "YELLOW"%d", id);

    if ((id = Vending_Nearest(playerid)) != -1)
        SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda berdiri dekat dynamic vending ID: "YELLOW"%d", id);

    if ((id = Graffiti_Nearest(playerid)) != -1)
        SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda berdiri dekat dynamic graffiti tag ID: "YELLOW"%d", id);
        
    if ((id = RSign_Nearest(playerid)) != -1)
        SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda berdiri dekat dynamic road sign ID: "YELLOW"%d", id);

    if ((id = GetPlayerNearestFLocker(playerid)) != -1)
        SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda berdiri dekat dynamic fact locker ID: "YELLOW"%d", id);
    
    if ((id = GetPlayerNearestFCraft(playerid)) != -1)
        SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda berdiri dekat dynamic fact craft ID: "YELLOW"%d", id);
    
    if ((id = GetPlayerNearestFGaragePos(playerid)) != -1)
        SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda berdiri dekat dynamic fact garage ID: "YELLOW"%d", id);

    if ((id = GetPlayerNearestFVault(playerid)) != -1)
        SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda berdiri dekat dynamic fact vault ID: "YELLOW"%d", id);

    if ((id = GetPlayerNearestFArmoury(playerid)) != -1)
        SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda berdiri dekat dynamic fact armoury ID: "YELLOW"%d", id);

    if ((id = Actor_Nearest(playerid)) != -1)
        SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda berdiri dekat dynamic actor ID: "YELLOW"%d", id);

    if ((id = Rental_Nearest(playerid)) != -1)
        SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda berdiri dekat dynamic bike rental ID: "YELLOW"%d", id);

    if ((id = Button_Nearest(playerid)) != -1)
        SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda berdiri dekat dynamic button ID: "YELLOW"%d", id);

    if ((id = Doors_Nearest(playerid)) != -1)
        SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda berdiri dekat dynamic door ID: "YELLOW"%d", id);

    if ((id = FivemLabel_Nearest(playerid)) != -1)
        SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda berdiri dekat dynamic FiveM labels ID: "YELLOW"%d", id);

    if ((id = PublicGarage_Nearest(playerid)) != -1)
        SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda berdiri dekat dynamic public garage ID: "YELLOW"%d", id);

    if ((id = Garbage_Nearest(playerid)) != -1)
        SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda berdiri dekat dynamic garbage bin ID: "YELLOW"%d", id);

    if ((id = Kanabis_Nearest(playerid)) != -1)
        SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda berdiri dekat dynamic cannabis ID: "YELLOW"%d", id);

    if ((id = Atm_Nearest(playerid)) != -1)
        SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda berdiri dekat dynamic ATM ID: "YELLOW"%d", id);

    if ((id = Robbery_Nearest(playerid)) != -1)
        SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda berdiri dekat dynamic robbery ID: "YELLOW"%d", id);

    if ((id = Shop_Nearest(playerid)) != -1)
        SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda berdiri dekat dynamic shop ID: "YELLOW"%d", id);

    if ((id = House_Nearest(playerid)) != -1)
        SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda berdiri dekat dynamic house ID: "YELLOW"%d", id);

    if ((id = Rusun_Nearest(playerid)) != -1)
        SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda berdiri dekat dynamic rusun ID: "YELLOW"%d", id);

    if ((id = Xmas_Nearest(playerid)) != -1)
        SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda berdiri dekat dynamic xmas tree ID: "YELLOW"%d", id);

    if ((id = Biz_Nearest(playerid)) != -1)
        SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda berdiri dekat dynamic business ID: "YELLOW"%d", id);

    if ((id = Deer_Nearest(playerid)) != -1)
        SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda berdiri dekat dynamic deer ID: "YELLOW"%d", id);

    if (vehicleid != INVALID_VEHICLE_ID)
        SendClientMessageEx(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda berdiri dekat VID: "YELLOW"%d | Model: %s(%d)", vehicleid, GetVehicleName(vehicleid), GetVehicleModel(vehicleid));

    return 1;
}

YCMD:checkwarns(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 1)
		return PermissionError(playerid);

	new otherid;
	if(sscanf(params, "u", otherid))
        return SUM(playerid, "/checkwarns [playerid/name]");

	if(!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

	if(!AccountData[otherid][IsLoggedIn])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut belum login ke server!");

	static string[1024], count;
	count = 0;
	format(string, sizeof(string), "Type\tIssuer\tDate\tReason\n");
	for (new id; id < 100; ++id)
	{
		if (PlayerWarning[otherid][id][warnExists] && PlayerWarning[otherid][id][warnOwner] == AccountData[otherid][pID]) 
		{
			switch (PlayerWarning[otherid][id][warnType])
			{
				case 1:
				{
					format(string, sizeof(string), "%s"GREEN"[WARN]\t"WHITE"%s\t%s\t%s\n", string, PlayerWarning[otherid][id][warnIssuer], PlayerWarning[otherid][id][warnDate], PlayerWarning[otherid][id][warnReason]);
				}
				case 2:
				{
					format(string, sizeof(string), "%s"YELLOW"[JAIL]\t"WHITE"%s\t%s\t%s\n", string, PlayerWarning[otherid][id][warnIssuer], PlayerWarning[otherid][id][warnDate], PlayerWarning[otherid][id][warnReason]);
				}
				case 3:
				{
					format(string, sizeof(string), "%s"ORANGERED"[BAN]\t"WHITE"%s\t%s\t%s\n", string, PlayerWarning[otherid][id][warnIssuer], PlayerWarning[otherid][id][warnDate], PlayerWarning[otherid][id][warnReason]);
				}
			}
			PlayerListitem[playerid][count++] = id;
		}
	}

	if (count == 0)
	{
		Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, sprintf("Warning History of %s", AccountData[otherid][pName]), "The player has no warning history!", "Tutup", "");
	}
	else
	{
		Temptargetid[playerid] = otherid;
		Dialog_Show(playerid, "CheckWarns", DIALOG_STYLE_TABLIST_HEADERS, sprintf("Warning History of %s", AccountData[otherid][pName]), string, "Pilih", "Tutup");
	}
	return 1;
}

YCMD:aka(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 1)
        return PermissionError(playerid);

    new otherid, PlayerIP[16], query[128];
    if (sscanf(params, "d", otherid))
        return SUM(playerid, "/aka [playerid]");

    if (!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    if (AccountData[otherid][pAdmin] == 5) {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya kepada admin level 5!");
        return SendClientMessageEx(playerid, -1, "Player "YELLOW"%s(%i) "WHITE"mencoba untuk /aka terhadap anda!", AccountData[playerid][pAdminname], playerid);
    }

    GetPlayerIp(otherid, PlayerIP, sizeof(PlayerIP));
    mysql_format(g_SQL, query, sizeof(query), "SELECT `UCP` FROM `player_ucp` WHERE `IP`='%e'", PlayerIP);
    mysql_pquery(g_SQL, query, "CheckPlayerIP", "is", playerid, PlayerIP);

    return 1;
}

YCMD:zo(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 1)
	    return PermissionError(playerid);

    if(!IsPlayerInDynamicArea(playerid, RPSchoolZone)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di zona OOC!");

    new text[144], frmxt[144];
    if(sscanf(params, "s[144]", text)) return SUM(playerid, "/zo [text]");

    foreach(new i : Player) if(AccountData[i][pSpawned])
    {
        if(IsPlayerInDynamicArea(i, RPSchoolZone))
        {
            if(strlen(text) > 64)
            {
                format(frmxt, sizeof(frmxt), "[OOC] "RED"%s: "CYAN"(( %.64s...", AccountData[playerid][pAdminname], text);
                SendClientMessage(i, X11_WHITE, frmxt);
                format(frmxt, sizeof(frmxt), "...%s ))", text[64]);
                SendClientMessage(i, X11_CYAN, frmxt);
            }
            else
            {
                format(frmxt, sizeof(frmxt), "[OOC] "RED"%s: "CYAN"(( %s ))", AccountData[playerid][pAdminname], text);
                SendClientMessage(i, X11_WHITE, frmxt);
            }
        }
    }
    return 1;
}