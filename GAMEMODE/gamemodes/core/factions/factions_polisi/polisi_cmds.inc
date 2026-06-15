YCMD:pagate(playerid, params[], help)
{
    if (AccountData[playerid][pFaction] != FACTION_LSPD)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");

    if(!IsPlayerInRangeOfPoint(playerid, 15.50, 1142.3409,1363.5345,10.6827))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di gerbang Akademi Polisi!");

    if(g_LSPDAcademyGateOpened)
    {
        MoveDynamicObject(LSPDAcademyGate, 1142.335937, 1363.166870, 11.331659, 2.0, 0.000000, 0.000000, 0.000000);
        g_LSPDAcademyGateOpened = false;
    }
    else
    {
        MoveDynamicObject(LSPDAcademyGate, 1142.335937, 1363.166870, 4.311656, 2.0, 0.000000, 0.000000, 0.000000);
        g_LSPDAcademyGateOpened = true;
    }
    return 1;
}

YCMD:tirelock(playerid, params[], help)
{
    if (AccountData[playerid][pFaction] != FACTION_LSPD)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");

    new vehid;
    if(sscanf(params, "d", vehid)) return SUM(playerid, "/tirelock [vehid]");

    if(!IsValidVehicle(vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid vehicle ID!");
    if(!IsPlayerNearVehicle(playerid, vehid, 5.55)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak cukup dekat dengan kendaraan tersebut!");

    new id = Vehicle_GetIterID(vehid);
	if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut bukan jenis kendaraan pribadi!");

    if(PlayerVehicle[id][pVehRental] > -1 || PlayerVehicle[id][pVehRentTime] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memberikan tirelock pada kendaraan rental!");
    if(PlayerVehicle[id][pVehTireLocked]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini sudah di-tirelock, gunakan '/untirelock' untuk menghapusnya!");
    if(DestroyDynamic3DTextLabel(PlayerVehicle[id][pVehTireLockLabel]))
        PlayerVehicle[id][pVehTireLockLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    VehicleCore[id][vCoreLocked] = true;
    SwitchVehicleEngine(vehid, false);
	SwitchVehicleDoors(vehid, true);
    PlayerVehicle[id][pVehTireLocked] = true;
    PlayerVehicle[id][pVehTireLockLabel] = CreateDynamic3DTextLabel("* Kendaraan ini sedang di-tirelock *", Y_GRAY, 0.0, 0.0, 0.0, 10.00, INVALID_PLAYER_ID, vehid, 0, GetVehicleVirtualWorld(vehid), GetVehicleInterior(vehid), -1, 10.00, -1, 0);
    ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil tirelock kendaraan %s.", GetVehicleModelName(PlayerVehicle[id][pVehModelID])));
    SIM(GetVehicleOwnerID(id), "Kendaraan %s telah di-tirelock oleh "RED"%s(%d).", GetVehicleModelName(PlayerVehicle[id][pVehModelID]), AccountData[playerid][pName], playerid);
    return 1;
}

YCMD:untirelock(playerid, params[], help)
{
    if (AccountData[playerid][pFaction] != FACTION_LSPD)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");

    new vehid;
    if(sscanf(params, "d", vehid)) return SUM(playerid, "/tirelock [vehid]");

    if(!IsValidVehicle(vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid vehicle ID!");
    if(!IsPlayerNearVehicle(playerid, vehid, 5.55)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak cukup dekat dengan kendaraan tersebut!");

    new id = Vehicle_GetIterID(vehid);
	if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut bukan jenis kendaraan pribadi!");

    if(!PlayerVehicle[id][pVehTireLocked]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak sedang di-tirelock!");

    VehicleCore[id][vCoreLocked] = false;
	SwitchVehicleDoors(vehid, false);
    PlayerVehicle[id][pVehTireLocked] = false;

    if(DestroyDynamic3DTextLabel(PlayerVehicle[id][pVehTireLockLabel]))
        PlayerVehicle[id][pVehTireLockLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
    
    SendClientMessageEx(playerid, X11_LIGHTBLUE, "IMPOUND: "WHITE"You have successfully remove the tirelock for this "CYAN"%s "WHITE"vehicle.", GetVehicleModelName(PlayerVehicle[id][pVehModelID]));
    SendClientMessageEx(GetVehicleOwnerID(id), X11_LIGHTBLUE, "IMPOUND: "WHITE"Your "CYAN"%s "WHITE"tirelock has been removed by officer "BLUE"%s(%d).", GetVehicleModelName(PlayerVehicle[id][pVehModelID]), AccountData[playerid][pName], playerid);
    return 1;
}

YCMD:pdm(playerid, params[], help)
{
    if (AccountData[playerid][pFaction] != FACTION_LSPD)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");

    Dialog_Show(playerid, "PolisiPDMMenu", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Police Menu",
        "Vehicle Interactions\n\
        Spawn Objects\n\
        Suspect List", "Pilih", "Batal");
    return 1;
}

YCMD:trace(playerid, params[], help)
{
    if (AccountData[playerid][pFaction] != FACTION_LSPD)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");

    new type, number[16], targetid, Float:targetX, Float:targetY, Float:targetZ;
    if (sscanf(params, "ds[16]", type, number))
        return SUM(playerid, "/trace [Type 1. HP, 2. Plate] [Plate/HP]");

    if (type < 1 || type > 2)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid trace type!");

    switch (type)
    {
        case 1: // HP
        {
            targetid = GetNumberOwner(number);
            if (targetid == INVALID_PLAYER_ID)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Nomor HP tersebut tidak ada di dalam server!");
            if (!IsPlayerConnected(targetid) && !AccountData[targetid][pSpawned])
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Nomor HP tersebut tidak ada di dalam server atau belum spawn!");
            if(!PlayerPhoneData[targetid][phoneOn]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Nomor HP tersebut tidak aktif / HP dalam keadaan mati!");
            GetPlayerPos(targetid, targetX, targetY, targetZ);
            ResetAllRaceCP(playerid);
            AccountData[playerid][pUsingGPS] = true;
            AccountData[playerid][pGPSCP] = CreateDynamicRaceCP(1, targetX, targetY, targetZ, targetX, targetY, targetZ, 3.5, 0, 0, playerid, 10000.00, -1, 0);
            SendClientMessageEx(playerid, -1, "Pemilik nomor %s, bernama %s, berada di %s, checkpoint telah diberikan!", number, GetPlayerRoleplayName(targetid), GetLocation(targetX, targetY, targetZ));
        }
        case 2: // Plate
        {
            new count = 0;
            foreach (new v : PvtVehicles)
            {
                if(!IsValidVehicle(PlayerVehicle[v][pVehPhysic])) continue;
                if(isnull(PlayerVehicle[v][pVehPlate])) continue;
                if(strcmp(PlayerVehicle[v][pVehPlate], "-", true, 16) == 0) continue;

                if(strcmp(PlayerVehicle[v][pVehPlate], number, true, 16) == 0)
                {
                    GetVehiclePos(PlayerVehicle[v][pVehPhysic], targetX, targetY, targetZ);
                    ResetAllRaceCP(playerid);
                    AccountData[playerid][pUsingGPS] = true;
                    AccountData[playerid][pGPSCP] = CreateDynamicRaceCP(1, targetX, targetY, targetZ, targetX, targetY, targetZ, 3.5, 0, 0, playerid, 10000.00, -1, 0);
                    SendClientMessageEx(playerid, -1, "Pemilik kendaraan %s [%s], bernama %s, berada di %s, checkpoint telah diberikan!", number, GetVehicleModelName(PlayerVehicle[v][pVehModelID]), GetVehicleOwnerName(v), GetLocation(targetX, targetY, targetZ));
                    count++;
                }
            }
            if(count == 0)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan atau plat tersebut tidak ada di dalam server!");
        }
    }
    return 1;
}

YCMD:takelic(playerid, params[], help)
{
    if (AccountData[playerid][pFaction] != FACTION_LSPD)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");

    new otherid;
    if (sscanf(params, "d", otherid))
        return SUM(playerid, "/takelic [playerid]");
    if (!IsPlayerConnected(otherid) && !AccountData[otherid][pSpawned])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi/belum spawn!");
    if (!IsPlayerNearPlayer(playerid, otherid, 2.0))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak dekat dengan anda!");

    AccountData[playerid][pTempValue2] = otherid;

    Dialog_Show(playerid, "TakeLicense", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- "WHITE"Tarik Lisensi", 
    "SIM A\n\
    SIM B\n\
    SIM C\n\
    Surat Izin Berlayar\n\
    Surat Izin Helikopter\n\
    Surat Izin Pesawat\n\
    Kartu Izin Berburu\n\
    Kartu Izin Senjata Api", "Pilih", "Batal");
    return 1;
}

YCMD:callsign(playerid, params[], help)
{
	new clsgnstr[32];

	if(AccountData[playerid][pFaction] != FACTION_LSPD && AccountData[playerid][pFaction] != FACTION_LSFD)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian/Paramedis Pahlawan Roleplay!");

    if(!AccountData[playerid][pOnDuty]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus on duty!");

    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mengendarai kendaraan kepolisian!");

	if(!IsLSPDVehicle(GetPlayerVehicleID(playerid)) && !IsLSFDVehicle(GetPlayerVehicleID(playerid)))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di kendaraan faction kepolisian!");

	switch(FactionVehHasCallsign[GetPlayerVehicleID(playerid)])
	{
		case 0:
		{
			if(sscanf(params, "s[32]",clsgnstr)) 
				return SUM(playerid, "/callsign [cth: 1-ADAM-1]");

            if(DestroyDynamic3DTextLabel(FactionVehCallsign[GetPlayerVehicleID(playerid)]))
                FactionVehCallsign[GetPlayerVehicleID(playerid)] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

			FactionVehCallsign[GetPlayerVehicleID(playerid)] = CreateDynamic3DTextLabel(clsgnstr, Y_WHITE, -1.0, -2.8, -0.4, 30.0, INVALID_PLAYER_ID, GetPlayerVehicleID(playerid), 0, 0, 0, -1, 30.0, -1, 0);
			FactionVehHasCallsign[GetPlayerVehicleID(playerid)] = true;

            strcopy(LSPDPlayerCallsign[playerid], clsgnstr);

            static string[144];
            format(string, sizeof(string), "(Server) "WHITE"Anda berhasil menetapkan callsign kendaraan ini menjadi "CMDEA"'%s'.", clsgnstr);
            SendClientMessage(playerid, Y_SERVER, string);
			Streamer_Update(playerid, -1);
		}
		case 1:
		{
			if(DestroyDynamic3DTextLabel(FactionVehCallsign[GetPlayerVehicleID(playerid)]))
                FactionVehCallsign[GetPlayerVehicleID(playerid)] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

	    	FactionVehHasCallsign[GetPlayerVehicleID(playerid)] = false;
            LSPDPlayerCallsign[playerid][0] = EOS;
            
	    	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Callsign kendaraan ini berhasil dihapus!");
			Streamer_Update(playerid, -1);
		}
	}
	return 1;
}

YCMD:mdt(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] != FACTION_LSPD)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");

    if(IsPlayerInAnyVehicle(playerid))
    {
        if(!IsLSPDVehicle(GetPlayerVehicleID(playerid)))
		    return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di dalam kendaraan kepolisian!");
    }
    else
    {
        if(!IsPlayerNearMDC(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di dekat Mobile Data Terminal!");
    }

    PlayerPlayNearbySound(playerid, MDC_OPEN);
	SendRPMeAboveHead(playerid, "Login ke Mobile Data Terminal.");

    Dialog_Show(playerid, "MDC_Main", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- MDT Dashboard", "Name Search\nPlate Search\nAll Points Bulletin\nCrime Broadcast\nRoster", "Pilih", "Batal");
    return 1;
}

YCMD:spawnheli(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] != FACTION_LSPD)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");

    if(!AccountData[playerid][pOnDuty]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus on duty!");

    if(IsPlayerInRangeOfPoint(playerid, 3.0, 2042.7186,-2128.7253,19.9640))
    {
        if(Iter_Contains(Vehicle, JobVehicle[playerid]))
        {
            DestroyVehicle(JobVehicle[playerid]);

            ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mengembalikan helikopter Maverick Kepolisian.");
        }
        else
        {
            JobVehicle[playerid] = CreateVehicle(497, 2059.2483,-2128.4412,20.1406,180.4092, 0, 1, 60000, false);
            VehicleCore[JobVehicle[playerid]][vCoreFuel] = 1000;
            SetValidVehicleHealth(JobVehicle[playerid], 2000.0); 
            VehicleCore[JobVehicle[playerid]][vMaxHealth] = 2000.0;
            VehicleCore[JobVehicle[playerid]][vIsBodyUpgraded] = true;
            VehicleCore[JobVehicle[playerid]][vIsBodyBroken] = false;
            VehicleCore[JobVehicle[playerid]][vCoreLocked] = false;
            SwitchVehicleEngine(JobVehicle[playerid], true);
            SwitchVehicleDoors(JobVehicle[playerid], false);

            ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mengeluarkan helikopter Maverick Kepolisian.");
        }
    }
    else if(IsPlayerInRangeOfPoint(playerid, 3.0, 977.2639,2478.5715,23.2101))
    {
        if(Iter_Contains(Vehicle, JobVehicle[playerid]))
        {
            DestroyVehicle(JobVehicle[playerid]);

            ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mengembalikan helikopter Maverick Kepolisian.");
        }
        else
        {
            JobVehicle[playerid] = CreateVehicle(497, 968.4270,2468.5740,23.3871,0.0012, 0, 1, 60000, false);
            VehicleCore[JobVehicle[playerid]][vCoreFuel] = 1000;
            SetValidVehicleHealth(JobVehicle[playerid], 2000.0); 
            VehicleCore[JobVehicle[playerid]][vMaxHealth] = 2000.0;
            VehicleCore[JobVehicle[playerid]][vIsBodyUpgraded] = true;
            VehicleCore[JobVehicle[playerid]][vIsBodyBroken] = false;
            VehicleCore[JobVehicle[playerid]][vCoreLocked] = false;
            SwitchVehicleEngine(JobVehicle[playerid], true);
            SwitchVehicleDoors(JobVehicle[playerid], false);

            ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mengeluarkan helikopter Maverick Kepolisian.");
        }
    }
    else
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di tempat pengambilan helikopter kepolisian!");
    return 1;
}

YCMD:spawnboat(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] != FACTION_LSPD)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");

    if(!AccountData[playerid][pOnDuty]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus on duty!");

    if(!IsPlayerInRangeOfPoint(playerid, 3.0, 2938.5337,-2051.8362,3.5480)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di tempat pengambilan kapal kepolisian!");

    if(Iter_Contains(Vehicle, JobVehicle[playerid]))
    {
        DestroyVehicle(JobVehicle[playerid]);

        ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mengembalikan boat Kepolisian Pahlawan Roleplay.");
    }
    else
    {
        JobVehicle[playerid] = CreateVehicle(430, 2930.7275,-2060.2361,0.1659,276.9433, 0, 1, 60000, true);
        VehicleCore[JobVehicle[playerid]][vCoreFuel] = 1000;
        SetValidVehicleHealth(JobVehicle[playerid], 2000.0); 
        VehicleCore[JobVehicle[playerid]][vMaxHealth] = 2000.0;
        VehicleCore[JobVehicle[playerid]][vIsBodyUpgraded] = true;
        VehicleCore[JobVehicle[playerid]][vIsBodyBroken] = false;
        VehicleCore[JobVehicle[playerid]][vCoreLocked] = false;
        SwitchVehicleEngine(JobVehicle[playerid], true);
        SwitchVehicleDoors(JobVehicle[playerid], false);

        ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mengeluarkan boat Kepolisian Pahlawan Roleplay.");
    }
    return 1;
}

YCMD:mpo(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] != FACTION_LSPD)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");

    if(!IsPlayerInAnyVehicle(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di dalam kendaraan kepolisian!");
    if(!IsLSPDVehicle(GetPlayerVehicleID(playerid)))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di dalam kendaraan kepolisian!");

    SendNearbyMessage(playerid, 60.0, X11_YELLOW, "[MEGAPHONE %s:o<] Harap tepikan kendaraan anda, kami dari Kepolisian Pahlawan Roleplay!", GetPlayerRoleplayName(playerid));
    return 1;
}

YCMD:em(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] != FACTION_LSPD)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");

    if(!IsPlayerInAnyVehicle(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di dalam kendaraan kepolisian!");
    if(!IsLSPDVehicle(GetPlayerVehicleID(playerid)))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di dalam kendaraan kepolisian!");

    new randex = RandomEx(0, 7);

    switch(randex)
    {
        case 0:
        {
            SendNearbyMessage(playerid, 60.0, X11_YELLOW, "[MEGAPHONE %s:o<] Disini Kepolisian Pahlawan Roleplay dalam situasi darurat, menyingkirlah dari jalan!", GetPlayerRoleplayName(playerid));
        }
        case 1:
        {
            SendNearbyMessage(playerid, 60.0, X11_YELLOW, "[MEGAPHONE %s:o<] Menyingkir dari jalan! Situasi darurat, ini Kepolisian Pahlawan Roleplay!", GetPlayerRoleplayName(playerid));
        }
        case 2:
        {
            SendNearbyMessage(playerid, 60.0, X11_YELLOW, "[MEGAPHONE %s:o<] Situasi darurat Kepolisian Pahlawan Roleplay, mohon menyingkir dari jalan!", GetPlayerRoleplayName(playerid));
        }
        case 3:
        {
            SendNearbyMessage(playerid, 60.0, X11_YELLOW, "[MEGAPHONE %s:o<] Berikan jalan segera, ini Kepolisian Pahlawan Roleplay sedang dalam situasi darurat!", GetPlayerRoleplayName(playerid));
        }
        case 4:
        {
            SendNearbyMessage(playerid, 60.0, X11_YELLOW, "[MEGAPHONE %s:o<] Harap berikan jalan, disini Kepolisian Pahlawan Roleplay dalam situasai darurat!", GetPlayerRoleplayName(playerid));
        }
        case 5:
        {
            SendNearbyMessage(playerid, 60.0, X11_YELLOW, "[MEGAPHONE %s:o<] Disini Kepolisian Pahlawan Roleplay dalam situasi darurat, menyingkir dan berikan jalan!", GetPlayerRoleplayName(playerid));
        }
        case 6:
        {
            SendNearbyMessage(playerid, 60.0, X11_YELLOW, "[MEGAPHONE %s:o<] Ini Kepolisian Pahlawan Roleplay, menyingkir dan berikan jalan untuk kami!", GetPlayerRoleplayName(playerid));
        }
    }
    return 1;
}

YCMD:makeskck(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");

    if(!IsPlayerInRangeOfPoint(playerid, 4.0, 944.0831,2447.8220,10.9001))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di tempat yang seharusnya!");

    static targetid, duration, text[64], esxs[512];
    if(sscanf(params, "ids[64]", targetid, duration, text))
        return SUM(playerid, "/makeskck [playerid] [expired] [note]");
    
    if(!IsPlayerConnected(targetid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    if(!AccountData[targetid][pSpawned])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut belum spawn!");

    if(!IsPlayerNearPlayer(playerid, targetid, 2.5)) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada dekat dengan pemain tersebut!");

    if(DocumentInfo[targetid][SKCK])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sudah memiliki SKCK!");

    if(duration < 1 || duration > 24)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Expired SKCK is invalid (1 - 24 hari)");
    
    DocumentInfo[targetid][SKCK] = true;
    DocumentInfo[targetid][SKCKDur] = gettime() + (duration * 86400);
    strcopy(DocumentInfo[targetid][SKCKText], text);
    strcopy(DocumentInfo[targetid][SKCKIssuer], GetPlayerRoleplayName(playerid));
    strcopy(DocumentInfo[targetid][SKCKIssuerRank], GetRankName(playerid));
    strcopy(DocumentInfo[targetid][SKCKIssueDate], GetAdvTime());

    mysql_format(g_SQL, esxs, sizeof(esxs), "INSERT INTO `documents` SET `Owner_ID` = %d, `Type` = 3, `SKCK_Dur` = %d, `SKCK_Text` = '%e', `SKCK_Issuer` = '%e', `SKCK_IssuerRank` = '%e', `SKCK_IssueDate` = '%e'",
    AccountData[targetid][pID], DocumentInfo[targetid][SKCKDur], DocumentInfo[targetid][SKCKText], DocumentInfo[targetid][SKCKIssuer], DocumentInfo[targetid][SKCKIssuerRank], DocumentInfo[targetid][SKCKIssueDate]);
    mysql_pquery(g_SQL, esxs);

    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Pembuatan SKCK berhasil dilakukan.");
    ShowTDN(targetid, NOTIFICATION_INFO, "Anda telah diberikan SKCK dari petugas.");
    return 1;
}

YCMD:makeplate(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");

    if(!IsPlayerInRangeOfPoint(playerid, 4.0, 944.0831,2447.8220,10.9001))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di tempat yang seharusnya!");

    Dialog_Show(playerid, "MakeVehPlate", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Pemasangan Plat", "Anda akan memasang plat kendaraan\n"YELLOW"(Mohon masukkan VID kendaraan, dapat dilihat di '/myv'):", "Input", "Batal");
    return 1;
}

// YCMD:makestnk(playerid, params[], help)
// {
//     if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");

//     if(!IsPlayerInRangeOfPoint(playerid, 4.0, 944.0831,2447.8220,10.9001))
//         return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di tempat yang seharusnya!");

//     static targetid, nomorktp[25], namaktp[25], plat[64], warna[64], modelnya[64];
//     if(sscanf(params, "is[25]s[25]s[64]s[64]s[64]", targetid, nomorktp, namaktp, plat, warna, modelnya))
//         return SUM(playerid, "/makestnk [playerid] [NIK KTP] [nama sesuai KTP] [nomor plat] [warna] [model]");
    
//     if(!IsPlayerConnected(targetid))
//         return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

//     if(!AccountData[targetid][pSpawned])
//         return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut belum spawn!");

//     if(!IsPlayerNearPlayer(playerid, targetid, 2.5)) 
//         return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada dekat dengan pemain tersebut!");
    

//     return 1;
// }