YCMD:carsteal(playerid, params[], help)
{
    if(!IsPlayerInRangeOfPoint(playerid, 5.0, 930.9570, 2065.1104, 10.8203))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di tempat carsteal!");

    if(pCarstealLabelTimer[playerid] > -1)
    {
        KillTimer(pCarstealLabelTimer[playerid]);
        pCarstealLabelTimer[playerid] = -1;
    }

    new crstlfrmt[522];
    if(AccountData[playerid][pDuringCarsteal])
    {
        ApplyDynamicActorAnimation(g_CarstealActor, "PED", "IDLE_chat", 6.67, 1, 0, 0, 0, 0);
        UpdateDynamic3DTextLabelText(AccountData[playerid][pCarstealLabel], Y_WHITE, ""LIGHTGREEN"Gangster: "WHITE"Lakukan saja tugasmu, bukankah telah kuberikan padamu?\nJangan tanyakan dulu tugas yang lainnya.");
        pCarstealLabelTimer[playerid] = SetTimerEx("CarstealLabelReset", 8500, false, "i", playerid);
        return 1;
    }

    if(g_IsCarstealStarted)
    {
        ApplyDynamicActorAnimation(g_CarstealActor, "PED", "IDLE_chat", 6.67, 1, 0, 0, 0, 0);
        UpdateDynamic3DTextLabelText(AccountData[playerid][pCarstealLabel], Y_WHITE, ""LIGHTGREEN"Gangster: "WHITE"Aduh, kau datang terlambat! Aku sudah menyuruh orang lain.");
        pCarstealLabelTimer[playerid] = SetTimerEx("CarstealLabelReset", 8500, false, "i", playerid);
        return 1;
    }

    if(gettime() < g_CarstealCooldown)
    {
        ApplyDynamicActorAnimation(g_CarstealActor, "PED", "IDLE_chat", 6.67, 1, 0, 0, 0, 0);
        format(crstlfrmt, sizeof(crstlfrmt), ""LIGHTGREEN"Gangster: "WHITE"Aku masih memikirkan strategi untuk tugas berikutnya.\n\
        "YELLOW"Cooldown: "WHITE"%02d menit.", (g_CarstealCooldown - gettime())/60);
        UpdateDynamic3DTextLabelText(AccountData[playerid][pCarstealLabel], Y_WHITE, crstlfrmt);
        pCarstealLabelTimer[playerid] = SetTimerEx("CarstealLabelReset", 8500, false, "i", playerid);
        return 1;
    }

    if(Iter_Count(LSPDDuty) < 4 || Iter_Count(LSFDDuty) < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal 4 polisi dan 2 Paramedis on duty!");

    if(Inventory_Count(playerid, "Linggis") < 1)
    {
        ApplyDynamicActorAnimation(g_CarstealActor, "PED", "IDLE_chat", 6.67, 1, 0, 0, 0, 0);
        UpdateDynamic3DTextLabelText(AccountData[playerid][pCarstealLabel], Y_WHITE, ""LIGHTGREEN"Gangster: "WHITE"Kau tidak memiliki Linggis!");
        return 1;
    }

    if(Inventory_Count(playerid, "Kunci T") < 1)
    {
        ApplyDynamicActorAnimation(g_CarstealActor, "PED", "IDLE_chat", 6.67, 1, 0, 0, 0, 0);
        UpdateDynamic3DTextLabelText(AccountData[playerid][pCarstealLabel], Y_WHITE, ""LIGHTGREEN"Gangster: "WHITE"Kau tidak memiliki Kunci T!");
        return 1;
    }

    AccountData[playerid][pDuringCarsteal] = true;
    g_IsCarstealStarted = true;
    g_CarstealCountdown = 900;
    g_CarstealCarFound[playerid] = false;
    g_CarstealCarDelivered[playerid] = false;
    new rand = random(sizeof(g_CarstealData)), randcolor1 = RandomEx(0, 255), randcolor2 = RandomEx(0, 255), randmodel = __g_CarstealVehicles[random(sizeof(__g_CarstealVehicles))];
    g_CarstealCarPhysic[playerid] = CreateVehicle(randmodel, g_CarstealData[rand][CarstealPos][0], g_CarstealData[rand][CarstealPos][1], g_CarstealData[rand][CarstealPos][2], g_CarstealData[rand][CarstealPos][3], randcolor1, randcolor2, 60000, false);
    VehicleCore[g_CarstealCarPhysic[playerid]][vCoreFuel] = 55;
    SetValidVehicleHealth(g_CarstealCarPhysic[playerid], 1000.0); 
    VehicleCore[g_CarstealCarPhysic[playerid]][vMaxHealth] = 1000.0;
    VehicleCore[g_CarstealCarPhysic[playerid]][vIsBodyUpgraded] = false;
    VehicleCore[g_CarstealCarPhysic[playerid]][vIsBodyBroken] = false;
    VehicleCore[g_CarstealCarPhysic[playerid]][vCoreLocked] = false;
    SwitchVehicleEngine(g_CarstealCarPhysic[playerid], false);
    SwitchVehicleDoors(g_CarstealCarPhysic[playerid], false);
    SetVehicleNumberPlate(g_CarstealCarPhysic[playerid], sprintf("BK %d", g_CarstealCarPhysic[playerid]));
    ApplyDynamicActorAnimation(g_CarstealActor, "PED", "IDLE_chat", 6.67, 1, 0, 0, 0, 0);
    format(crstlfrmt, sizeof(crstlfrmt), ""LIGHTGREEN"Gangster: "WHITE"Baik, tolong dengarkan! Sebuah "CYAN"%s "WHITE"sedang diparkirkan di sekitar "YELLOW"%s.\n\
    "WHITE"Ambil dan bawalah kemari, kau punya waktu selama %02d menit. Waspadalah terhadap polisi!\n"YELLOW"CMD: "WHITE"/csinfo", GetVehicleModelName(randmodel), GetLocation(g_CarstealData[rand][CarstealPos][0], g_CarstealData[rand][CarstealPos][1], g_CarstealData[rand][CarstealPos][2]), g_CarstealCountdown/60);
    UpdateDynamic3DTextLabelText(AccountData[playerid][pCarstealLabel], Y_WHITE, crstlfrmt);

    pCarstealLabelTimer[playerid] = SetTimerEx("CarstealLabelReset", 20000, false, "i", playerid);
    return 1;
}


YCMD:csinfo(playerid, params[], help)
{
    new csinfotxt[258];
    if(!AccountData[playerid][pDuringCarsteal]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang menjalankan misi carsteal!");

    if(IsValidVehicle(g_CarstealCarPhysic[playerid]))
    {
        if(!g_CarstealCarFound[playerid])
        {
            new Float: csvehX, Float: csvehY, Float: csvehZ;
            GetVehiclePos(g_CarstealCarPhysic[playerid], csvehX, csvehY, csvehZ);

            format(csinfotxt, sizeof(csinfotxt), ""WHITE"Carilah kendaraan ini:\n\n\
            Model: "YELLOW"%s\n\
            "WHITE"Lokasi: "YELLOW"%s\n\n\
            "WHITE"Segera temukan dan bawa kepada Gangster sebelum waktu selesai "RED"(%d menit)", GetVehicleModelName(GetVehicleModel(g_CarstealCarPhysic[playerid])), GetLocation(csvehX, csvehY, csvehZ), g_CarstealCountdown/60);
            Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Carsteal Info", csinfotxt, "Tutup", "");
        }
        else
        {
            SendClientMessage(playerid, X11_DARKORCHID4, "[Carsteal] "WHITE"You have found the Carsteal vehicle; take it to the gangster immediately!");
        }
    }
    return 1;
}