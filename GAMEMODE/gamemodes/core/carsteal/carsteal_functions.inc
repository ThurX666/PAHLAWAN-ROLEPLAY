#include <YSI_Coding\y_hooks>

//ban
//bumper depan
//bumper belakang
//pintu

new STREAMER_TAG_ACTOR:g_CarstealActor,
    bool:g_IsCarstealStarted,
    g_CarstealCountdown,
    g_CarstealCooldown,
    g_CarstealCarPhysic[MAX_PLAYERS],
    bool:g_CarstealCarFound[MAX_PLAYERS],
    bool:g_CarstealCarDelivered[MAX_PLAYERS],
    g_CarstealStepPart[MAX_PLAYERS],
    Float:g_CarstealVehX,
    Float:g_CarstealVehY,
    Float:g_CarstealVehZ;

new __g_CarstealVehicles[] = {
    602, 496, 549, 517, 474, //2 door
    507, 445, 492, 405, 550, //4 door saloon
    536, 575, 534, 567, 576, //lowrider
    560, 480, 561, 558, 562, //sport
    581, 521, 463, 461, 468 //bike
};

enum __g_CarstealDetails
{
    Float:CarstealPos[4]
};

new g_CarstealData[14][__g_CarstealDetails] =
{
    {{1924.2345,-2121.1265,13.2905,0.0252}},
    {{2048.7632,-1993.8453,13.2520,270.7440}},
    {{2429.3635,-1675.3466,13.3818,357.9107}},
    {{2385.9766,-1462.2719,23.7243,180.1478}},
    {{2861.2192,-2011.9707,10.6389,359.3865}},
    {{2759.4714,-2031.5140,13.2597,0.8652}},
    {{2655.6389,-1952.0492,13.2525,180.8088}},
    {{2462.0085,-1897.8571,13.2520,0.6159}},
    {{2027.9835,-959.1857,40.0482,193.6896}},
    {{1462.1189,-662.7288,94.4551,181.1997}},
    {{-366.7477,-1439.5139,25.4309,88.1518}},
    {{-1101.8119,-1141.0289,128.9232,0.4521}},
    {{-592.3184,-514.8571,25.2286,358.9182}},
    {{-2237.9980,-2300.0251,30.2603,230.9842}}
};

hook OnGameModeInit()
{
    g_CarstealActor = CreateDynamicActor(115, 930.9570,2065.1104,10.8203,359.3734, true, 100.0, 0, 0, -1, 300.00, -1, 0);
    g_IsCarstealStarted = false;
    g_CarstealCooldown = 0;
    g_CarstealCountdown = 0;
    return 1;
}

hook OnPlayerEnterDynRaceCP(playerid, STREAMER_TAG_RACE_CP:checkpointid)
{
    if(IsPlayerConnected(playerid) && AccountData[playerid][IsLoggedIn] && AccountData[playerid][pSpawned] && AccountData[playerid][pDuringCarsteal])
    {
        if(GetPlayerVehicleID(playerid) == g_CarstealCarPhysic[playerid] && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
        {
            if(checkpointid == AccountData[playerid][pCarstealRCP] && IsPlayerInDynamicRaceCP(playerid, AccountData[playerid][pCarstealRCP]))
            {
                ResetAllRaceCP(playerid);

                g_CarstealCarDelivered[playerid] = true;
                g_CarstealCarFound[playerid] = false;
                g_CarstealStepPart[playerid] = 1;

                foreach(new x : LSPDDuty)
                {
                    if(DestroyDynamicMapIcon(AccountData[playerid][g_CarstealIcon][x]))
                        AccountData[playerid][g_CarstealIcon][x] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
                }

                AccountData[playerid][pCarstealLabelPart] = CreateDynamic3DTextLabel("Tekan "GREEN"[N] "WHITE"untuk membongkar ban", Y_WHITE, 0.25, 0.0, 0.0, 5.0, INVALID_PLAYER_ID, g_CarstealCarPhysic[playerid], 0, 0, 0, playerid, 5.0, -1, 0);
                RemovePlayerFromVehicle(playerid);
            }
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_NO && AccountData[playerid][IsLoggedIn] && AccountData[playerid][pSpawned] && AccountData[playerid][pDuringCarsteal] && g_CarstealCarDelivered[playerid])
    {
        if(!AccountData[playerid][pKnockdown])
        {
            if(IsValidVehicle(g_CarstealCarPhysic[playerid]))
            {
                GetVehiclePos(g_CarstealCarPhysic[playerid], g_CarstealVehX, g_CarstealVehY, g_CarstealVehZ);

                if(IsPlayerInRangeOfPoint(playerid, 5.0, g_CarstealVehX, g_CarstealVehY, g_CarstealVehZ))
                {
                    if(!AccountData[playerid][pCarstealHoldingPart])
                    {
                        if(!PlayerHasItem(playerid, "Linggis")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Linggis!");
                        if(!PlayerHasItem(playerid, "Kunci T")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Kunci T!");

                        switch(g_CarstealStepPart[playerid])
                        {
                            case 1: //disuru bongkar ban
                            {
                                if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

                                AccountData[playerid][pActivityTime] = 1;
                                pCarstealPartTimer[playerid] = true;
                                PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMBONGKAR BAN");
                                ShowProgressBar(playerid);

                                ApplyAnimation(playerid, "COP_AMBIENT", "Copbrowse_loop", 2.33, true, false, false, false, 0, true);
                            }
                            case 2: //disuru bongkar bumper belakang
                            {
                                if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

                                AccountData[playerid][pActivityTime] = 1;
                                pCarstealPartTimer[playerid] = true;
                                PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMBONGKAR BUMPER");
                                ShowProgressBar(playerid);

                                ApplyAnimation(playerid, "COP_AMBIENT", "Copbrowse_loop", 2.33, true, false, false, false, 0, true);
                            }
                            case 3: //disuru bongkar bumper depan
                            {
                                if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

                                AccountData[playerid][pActivityTime] = 1;
                                pCarstealPartTimer[playerid] = true;
                                PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMBONGKAR BUMPER");
                                ShowProgressBar(playerid);

                                ApplyAnimation(playerid, "COP_AMBIENT", "Copbrowse_loop", 2.33, true, false, false, false, 0, true);
                            }
                            case 4: //disuru bongkar pintu
                            {
                                if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

                                AccountData[playerid][pActivityTime] = 1;
                                pCarstealPartTimer[playerid] = true;
                                PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMBONGKAR PINTU");
                                ShowProgressBar(playerid);

                                ApplyAnimation(playerid, "COP_AMBIENT", "Copbrowse_loop", 2.33, true, false, false, false, 0, true);
                            }
                        }
                    }
                }
            }
        }
    }
    return 1;
}

hook OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP: checkpointid)
{
    if(checkpointid == AccountData[playerid][pCarstealStoringCP])
    {
        if(AccountData[playerid][IsLoggedIn] && AccountData[playerid][pSpawned] && AccountData[playerid][pDuringCarsteal] && g_CarstealCarDelivered[playerid])
        {
            if(!AccountData[playerid][pKnockdown])
            {
                if(IsValidVehicle(g_CarstealCarPhysic[playerid]))
                {
                    if(DestroyDynamicCP(AccountData[playerid][pCarstealStoringCP]))
                        AccountData[playerid][pCarstealStoringCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    StopRunningAnimation(playerid);

                    switch(g_CarstealStepPart[playerid])
                    {
                        case 1: //letak ban
                        {
                            g_CarstealStepPart[playerid] = 2;
                            AccountData[playerid][pCarstealHoldingPart] = false;

                            ApplyAnimation(playerid, "CARRY", "putdwn", 1.13, false, false, false, false, 0, true);
                            RemovePlayerAttachedObject(playerid, 9);

                            new Float:vhoodX, Float:vhoodY, Float:vhoodZ;
                            GetVehicleBoot(g_CarstealCarPhysic[playerid], vhoodX, vhoodY, vhoodZ);
                            Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, AccountData[playerid][pCarstealLabelPart], vhoodX, vhoodY, vhoodZ);
                            UpdateDynamic3DTextLabelText(AccountData[playerid][pCarstealLabelPart], Y_WHITE, "Tekan "GREEN"[N] "WHITE"untuk membongkar bumper belakang");
                            Streamer_Update(playerid, STREAMER_TYPE_3D_TEXT_LABEL);
                        }
                        case 2: //letak bumper belakang
                        {
                            g_CarstealStepPart[playerid] = 3;
                            AccountData[playerid][pCarstealHoldingPart] = false;

                            ApplyAnimation(playerid, "CARRY", "putdwn", 1.13, false, false, false, false, 0, true);
                            RemovePlayerAttachedObject(playerid, 9);

                            new Float:vhoodX, Float:vhoodY, Float:vhoodZ;
                            GetVehicleHood(g_CarstealCarPhysic[playerid], vhoodX, vhoodY, vhoodZ);
                            Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, AccountData[playerid][pCarstealLabelPart], vhoodX, vhoodY, vhoodZ);
                            UpdateDynamic3DTextLabelText(AccountData[playerid][pCarstealLabelPart], Y_WHITE, "Tekan "GREEN"[N] "WHITE"untuk membongkar bumper depan");
                            Streamer_Update(playerid, STREAMER_TYPE_3D_TEXT_LABEL);
                        }
                        case 3: //letak bumper depan
                        {
                            g_CarstealStepPart[playerid] = 4;
                            AccountData[playerid][pCarstealHoldingPart] = false;

                            ApplyAnimation(playerid, "CARRY", "putdwn", 1.13, false, false, false, false, 0, true);
                            RemovePlayerAttachedObject(playerid, 9);

                            Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, AccountData[playerid][pCarstealLabelPart], 0.25, 0.0, 0.0);
                            UpdateDynamic3DTextLabelText(AccountData[playerid][pCarstealLabelPart], Y_WHITE, "Tekan "GREEN"[N] "WHITE"untuk membongkar pintu");
                            Streamer_Update(playerid, STREAMER_TYPE_3D_TEXT_LABEL);
                        }
                        case 4: //letak pintu
                        {
                            g_CarstealStepPart[playerid] = 5;
                            AccountData[playerid][pCarstealHoldingPart] = false;

                            ApplyAnimation(playerid, "CARRY", "putdwn", 1.13, false, false, false, false, 0, true);
                            RemovePlayerAttachedObject(playerid, 9);

                            UpdateDynamic3DTextLabelText(AccountData[playerid][pCarstealLabelPart], Y_WHITE, "Bicaralah kepada Gangster untuk meminta upah");
                            Streamer_Update(playerid, STREAMER_TYPE_3D_TEXT_LABEL);

                            AccountData[playerid][pCarstealStoringCP] =  CreateDynamicCP(930.8962,2067.2246,10.8203, 2.0, 0, 0, playerid, 250.0, -1, 0);
                        }
                        case 5: //bicara pada gangster
                        {
                            new randomcash = RandomEx(6000, 9800), updxls[522];
                            GivePlayerDirtyMoney(playerid, randomcash);

                            Inventory_Remove(playerid, "Linggis", 1);
                            Inventory_Remove(playerid, "Kunci T", 1);

                            ShowItemBox(playerid, "Linggis", "Removed 1x", 18634, 4);
                            ShowItemBox(playerid, "Kunci T", "Removed 1x", 18633, 5);

                            ApplyDynamicActorAnimation(g_CarstealActor, "PED", "IDLE_chat", 6.67, 1, 0, 0, 0, 0);

                            format(updxls, sizeof(updxls), ""LIGHTGREEN"Gangster: "WHITE"Kerja bagus kawan! Aku hargai penderitaanmu dengan "DARKGREEN"$%s\n"WHITE"Datanglah kemari jika kau inginkan tugas lagi.", FormatMoney(randomcash));
                            UpdateDynamic3DTextLabelText(AccountData[playerid][pCarstealLabel], Y_WHITE, updxls);
                            pCarstealLabelTimer[playerid] = SetTimerEx("CarstealLabelReset", 8500, false, "i", playerid);

                            g_IsCarstealStarted = false;
                            g_CarstealCountdown = 0;
                            g_CarstealCooldown = gettime() + 1800;
                            
                            DestroyVehicle(g_CarstealCarPhysic[playerid]);

                            g_CarstealCarFound[playerid] = false;
                            g_CarstealCarDelivered[playerid] = false;
                            g_CarstealStepPart[playerid] = 0;

                            AccountData[playerid][pDuringCarsteal] = false;
                            AccountData[playerid][pCarstealHoldingPart] = false;

                            if(DestroyDynamic3DTextLabel(AccountData[playerid][pCarstealLabelPart]))
                            {
                                AccountData[playerid][pCarstealLabelPart] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
                            }
                        }
                    }
                }
            }
        }
    }
    return 1;
}

forward CarstealLabelReset(playerid);
public CarstealLabelReset(playerid)
{
    KillTimer(pCarstealLabelTimer[playerid]);
    pCarstealLabelTimer[playerid] = -1;
    ApplyDynamicActorAnimation(g_CarstealActor, "PED", "IDLE_stance", 1.50, 1, 0, 0, 0, 0);
    UpdateDynamic3DTextLabelText(AccountData[playerid][pCarstealLabel], Y_WHITE, ""LIGHTGREEN"Gangster: "WHITE"Apa kau ingin melakukan tugas dariku?\n\
    Jika kau berani melakukannya maka akan kuberi bayaran yang setimpal.\n"YELLOW"CMD: "WHITE"/carsteal");
    return 1;
}

ptask UpdatingCarstealCountdown[1000](playerid) 
{
    if(IsPlayerConnected(playerid) && AccountData[playerid][IsLoggedIn] && AccountData[playerid][pSpawned] && AccountData[playerid][pDuringCarsteal])
    {
        if(!g_CarstealCarDelivered[playerid])
        {
            if(g_CarstealCountdown > 0)
            {
                g_CarstealCountdown--;
            }
            else
            {
                g_CarstealCountdown = 0;
                AccountData[playerid][pDuringCarsteal] = false;
                g_CarstealCarFound[playerid] = false;
                g_IsCarstealStarted = false;
                g_CarstealCooldown = gettime() + 1800;

                DestroyVehicle(g_CarstealCarPhysic[playerid]);

                foreach(new x : LSPDDuty)
				{
					if(DestroyDynamicMapIcon(AccountData[playerid][g_CarstealIcon][x]))
						AccountData[playerid][g_CarstealIcon][x] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
				}
                ShowFivemNotify(playerid, "Pahlawan Roleplay~n~CAR STEAL", "Dasar payah, anda belum menemukan kendaraan carsteal atau waktu habis. Misi dinyatakan gagal!", "hud:radar_qmark", 25);
            }
        }
    }
    return 1;
}

ptask UpdateCarstealIcon[4500](playerid)
{
    if(AccountData[playerid][pDuringCarsteal])
    {
        if(g_CarstealCarFound[playerid])
        {
            if(!g_CarstealCarDelivered[playerid])
            {
                static Float:pCX, Float: pCY, Float: pCZ;
                GetVehiclePos(g_CarstealCarPhysic[playerid], pCX, pCY, pCZ);

                foreach(new x : LSPDDuty)
				{
					if(DestroyDynamicMapIcon(AccountData[playerid][g_CarstealIcon][x]))
						AccountData[playerid][g_CarstealIcon][x] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;

                    AccountData[playerid][g_CarstealIcon][x] = CreateDynamicMapIcon(pCX, pCY, pCZ, 0, Y_TOMATO, -1, -1, x, 10000.00, MAPICON_GLOBAL, -1, 0);
				}
            }
        }
    }
    return 1;
}