new Float:healthvalue, Float:armorvalue, Float:hungervalue, Float:thirstvalue, Float:stressvalue, Float:healthget, Float:armorget;

ptask PlayerUpdate[1500](playerid)
{
    if(AccountData[playerid][IsLoggedIn] && AccountData[playerid][pSpawned])
    {
        if(AccountData[playerid][pHunger] < 0)
        {
            AccountData[playerid][pHunger] = 0;
        }
        else if(AccountData[playerid][pHunger] > 100)
        {
            AccountData[playerid][pHunger] = 100;
        }

        if(AccountData[playerid][pThirst] < 0)
        {
            AccountData[playerid][pThirst] = 0;
        }
        else if(AccountData[playerid][pThirst] > 100)
        {
            AccountData[playerid][pThirst] = 100;
        }

        if(AccountData[playerid][pStress] < 0)
        {
            AccountData[playerid][pStress] = 0;
        }

        else if(AccountData[playerid][pStress] > 100)
        {
            AccountData[playerid][pStress] = 100;
        }

        if(AccountData[playerid][pVIP] == 3)
        {
            if(AccountData[playerid][pStress] != 0)
            {
                AccountData[playerid][pStress] = 0;
            }
        }

        if(AccountData[playerid][pTortured])
        {
            Anticheat[playerid][acImmunity] = gettime() + 5;
            SetPlayerPos(playerid, 10.00, -10.00, 9999999999.99);
        }
    }
    return 1;
}

ptask UpdateHBEPlayer[1000](playerid)
{
    if(AccountData[playerid][IsLoggedIn] && AccountData[playerid][pSpawned])
    {
        if(!OJailData[playerid][jailed] && !AccountData[playerid][pKnockdown]) //jika tidak sedang dipenjara admin dan tidak pingsan
        {
            if(!AccountData[playerid][pIsAFK])
            {
                if(++ AccountData[playerid][pHungerTime] >= 290)
                {
                    if(AccountData[playerid][pHunger] > 0)
                    {
                        AccountData[playerid][pHunger] -= 5;

                        if(AccountData[playerid][pHunger] <= 20)
                        {
                            GameTextForPlayer(playerid, "~r~Anda merasa lapar", 7900, 1);
                        }
                    }
                    else
                    {
                        if(IsPlayerInAnyVehicle(playerid))
                            RemovePlayerFromVehicle(playerid);
                        SetPlayerHealth(playerid, 0.0);

                        GameTextForPlayer(playerid, "~r~Pingsan karena kelaparan berat", 7900, 1);
                    }
                    AccountData[playerid][pHungerTime] = 0;
                }
                if(++ AccountData[playerid][pThirstTime] >= 110)
                {
                    if(AccountData[playerid][pThirst] > 0)
                    {
                        AccountData[playerid][pThirst]--;

                        if(AccountData[playerid][pThirst] <= 20)
                        {
                            GameTextForPlayer(playerid, "~r~Anda merasa haus", 7900, 1);
                        }
                    }
                    else
                    {
                        if(IsPlayerInAnyVehicle(playerid))
                            RemovePlayerFromVehicle(playerid);
                        SetPlayerHealth(playerid, 0.0);

                        GameTextForPlayer(playerid, "~r~Pingsan karena haus berat", 7900, 1);
                    }
                    AccountData[playerid][pThirstTime] = 0;
                }
            }
            if(IsAtBahamas(playerid))
            {
                if(++ AccountData[playerid][pStressTime] >= 12)
                {
                    if(AccountData[playerid][pStress] > 0)
                    {
                        if(AccountData[playerid][pVIP] != 2)
                        {
                            AccountData[playerid][pStress] --;
                        }
                        else
                        {
                            AccountData[playerid][pStress] -= 5;
                        }
                    }
                    
                    if(AccountData[playerid][pStress] <= 85)
                    {
                        SetPlayerDrunkLevel(playerid, 0);
                        HideStressEffectTD(playerid);
                    }
                    AccountData[playerid][pStressTime] = 0;
                }
            }
            else
            {
                if(++ AccountData[playerid][pStressTime] >= 270)
                {
                    if(AccountData[playerid][pVIP] != 3)
                    {
                        if(AccountData[playerid][pStress] < 100)
                        {
                            AccountData[playerid][pStress]++;
                        }

                        if(AccountData[playerid][pStress] >= 60)
                        {
                            GameTextForPlayer(playerid, "~r~Anda merasa stres dan pusing", 7900, 1);
                        }
                    }
                    AccountData[playerid][pStressTime] = 0;
                }
            }
        }
        
        GetPlayerHealth(playerid, healthget);
        healthvalue = healthget * 28.0/100;
        if(healthget > 100.00)
        {
            PlayerTextDrawTextSize(playerid, PHBE[playerid][6], 28.0, 13.0);
        }
        else
        {
            PlayerTextDrawTextSize(playerid, PHBE[playerid][6], healthvalue, 13.0);
        }
        
        GetPlayerArmour(playerid, armorget);
        armorvalue = armorget * 28.0/100;
        if(armorget > 100.00)
        {
            PlayerTextDrawTextSize(playerid, PHBE[playerid][7], 28.0, 13.0);
        }
        else
        {
            PlayerTextDrawTextSize(playerid, PHBE[playerid][7], armorvalue, 13.0);
        }

        // PlayerTextDrawSetString(playerid, PHBE[playerid][0], sprintf("%d", AccountData[playerid][pHunger]));
        // PlayerTextDrawSetString(playerid, PHBE[playerid][1], sprintf("%d", AccountData[playerid][pThirst]));
        // PlayerTextDrawSetString(playerid, PHBE[playerid][2], sprintf("%d", AccountData[playerid][pStress]));

        hungervalue = AccountData[playerid][pHunger] * -13.0/100;
        PlayerTextDrawTextSize(playerid, PHBE[playerid][8], 13.0, hungervalue);

        thirstvalue = AccountData[playerid][pThirst] * -13.0/100;
        PlayerTextDrawTextSize(playerid, PHBE[playerid][9], 13.0, thirstvalue);

        stressvalue = AccountData[playerid][pStress] * -13.0/100;
        PlayerTextDrawTextSize(playerid, PHBE[playerid][10], 13.0, stressvalue);

        if(!HBETDHidden[playerid])
        {
            PlayerTextDrawShow(playerid, PHBE[playerid][6]);
            PlayerTextDrawShow(playerid, PHBE[playerid][7]);
            PlayerTextDrawShow(playerid, PHBE[playerid][8]);
            PlayerTextDrawShow(playerid, PHBE[playerid][9]);
            PlayerTextDrawShow(playerid, PHBE[playerid][10]);

            PlayerTextDrawShow(playerid, PHBE[playerid][11]);
            PlayerTextDrawShow(playerid, PHBE[playerid][12]);
            PlayerTextDrawShow(playerid, PHBE[playerid][13]);
            PlayerTextDrawShow(playerid, PHBE[playerid][14]);
            PlayerTextDrawShow(playerid, PHBE[playerid][15]);
        }
    }
    return 1;
}

ptask CheckPlayerInWater[3000](playerid)
{
    if(AccountData[playerid][pSpawned] && (GetPlayerAnimationIndex(playerid) == 1250 || GetPlayerAnimationIndex(playerid) == 1539 || GetPlayerAnimationIndex(playerid) == 1538 || GetPlayerAnimationIndex(playerid) == 1541 || GetPlayerAnimationIndex(playerid) == 1544))
    {
        if(!AccountData[playerid][pInEvent])
        {
            if(Inventory_Count(playerid, "Smartphone") > 0)
            {
                Inventory_Add(playerid, "Elektronik Rusak", 2041, Inventory_Count(playerid, "Smartphone"));
                ShowItemBox(playerid, "Smartphone", sprintf("Removed %dx", Inventory_Count(playerid, "Smartphone")), 18873, 5);
                ShowItemBox(playerid, "Elektronik Rusak", sprintf("Removed %dx", Inventory_Count(playerid, "Smartphone")), 2041, 6);
                Inventory_Remove(playerid, "Smartphone", -1);
            }

            if(PlayerVoiceData[playerid][pHasRadio])
            {
                PlayerVoiceData[playerid][pHasRadio] = false;
                PlayerVoiceData[playerid][pIsRadioOn] = false;
                PlayerVoiceData[playerid][pIsRadioMicOn] = false;
                PlayerVoiceData[playerid][pRadioFreq] = 0;

                ShowItemBox(playerid, "Radio", "Removed 1x", 19942, 5);
                ShowItemBox(playerid, "Elektronik Rusak", "Received 1x", 2041, 6);
            }
        }
    }
    return 1;
}

ptask PlayerVehicleUpdate[1000](playerid)
{
	if(SavingVehID[playerid] != INVALID_VEHICLE_ID && IsPlayerInVehicle(playerid, SavingVehID[playerid]) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		if(!GetEngineStatus(SavingVehID[playerid]) && IsEngineVehicle(SavingVehID[playerid]))
		{	
			SwitchVehicleEngine(SavingVehID[playerid], false);
		}

        new Float:fHealth;
        GetVehicleHealth(SavingVehID[playerid], fHealth);
        if(fHealth <= 350.0) //maximal 1000 health
        {
            if(SavingVehID[playerid] == JobVehicle[playerid])
            {
                DestroyVehicle(JobVehicle[playerid]);

                DestroyVehicle(TrailerVehicle[playerid]);
            }

            if(AccountData[playerid][pDuringCarsteal])
            {
                if(SavingVehID[playerid] == g_CarstealCarPhysic[playerid])
                {
                    DestroyVehicle(g_CarstealCarPhysic[playerid]);

                    foreach(new x : LSPDDuty)
                    {
                        if(DestroyDynamicMapIcon(AccountData[playerid][g_CarstealIcon][x]))
                            AccountData[playerid][g_CarstealIcon][x] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
                    }

                    g_CarstealCountdown = 0;
                    AccountData[playerid][pDuringCarsteal] = false;
                    g_IsCarstealStarted = false;
                    g_CarstealCarFound[playerid] = false;
                    g_CarstealCooldown = gettime() + 1800;

                    ResetAllRaceCP(playerid);

                    ShowFivemNotify(playerid, "Pahlawan Roleplay~n~CAR STEAL", "Kendaraan carsteal telah hancur, misi dinyatakan gagal!", "hud:radar_qmark", 25);
                }
            }

            if(AccountData[playerid][pInEvent])
            {
                if(SavingVehID[playerid] == EventVehicle[playerid])
                {
                    DestroyVehicle(EventVehicle[playerid]);

                    ResetPlayerWeapons(playerid);

                    if(Iter_Contains(EvBlueTeam, playerid))
                        Iter_Remove(EvBlueTeam, playerid);
                    
                    if(Iter_Contains(EvRedTeam, playerid))
                        Iter_Remove(EvRedTeam, playerid);

                    if(Iter_Contains(EvHumanTeam, playerid))
                        Iter_Remove(EvHumanTeam, playerid);
                    
                    if(Iter_Contains(EvZombieTeam, playerid))
                        Iter_Remove(EvZombieTeam, playerid);
                    
                    if(Iter_Contains(InEvent, playerid))
                        Iter_Remove(InEvent, playerid);

                    LeaveEvent(playerid);

                    SendClientMessage(playerid, -1, "[OOC Event] Anda dieleminasi dari event karena merusakkan kendaraan.");

                    foreach(new i : InEvent)
                    {
                        SendClientMessageEx(i, X11_YELLOW, "[OOC Event] "RED"%s "YELLOW"got wrecked.", AccountData[playerid][pName]);
                    }
                }
            }
            if(AccountData[playerid][pSideJob] == SIDEJOB_FORKLIFT)
            {
                if(IsAForkliftSidejobVeh(SavingVehID[playerid]))
                {
                    ForkliftUnloadedCrate[playerid] = 0;
                    AccountData[playerid][pSideJob] = SIDEJOB_NONE;

                    AccountData[playerid][pForkliftSidejobDelay] = 1800;

                    SetTimerEx("RespawnPV", 1000, false, "d", SavingVehID[playerid]);

                    if(DestroyDynamicCP(ForkliftCP[playerid]))
                        ForkliftCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    if(DestroyDynamicCP(ForkliftReturnCP[playerid]))
                        ForkliftReturnCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    if(DestroyDynamicCP(UnloadForkliftCP[playerid]))
                        UnloadForkliftCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    if(DestroyDynamicObject(ForkliftCrateObj[playerid]))
                        ForkliftCrateObj[playerid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

                    TogglePlayerControllable(playerid, true);
                    ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan anda rusak tugas forkflift dinyatakan gagal.");
                }
            }

            if(AccountData[playerid][pSideJob] == SIDEJOB_TRASHCOLLECTOR)
            {
                if(SavingVehID[playerid] == TrashCollectorPlayerVeh[playerid])
                {
                    TrashCollectorHoldingBag[playerid] = false;
                    TrashCollectorLeavingTime[playerid] = 0;
                    AccountData[playerid][pSideJob] = SIDEJOB_NONE;
                    TrashCollected[playerid] = 0;

                    if(DestroyDynamicCP(TrashCollectorRVehCP[playerid]))
                        TrashCollectorRVehCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    if(DestroyDynamicCP(TrashCollectorBackCP[playerid]))
                        TrashCollectorBackCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    for (new i; i < 25; i++) 
                    {
                        if(DestroyDynamicCP(TrashCollectorCP[playerid][i]))
                            TrashCollectorCP[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                        if(DestroyDynamicMapIcon(TrashCollectorIcon[playerid][i]))
                            TrashCollectorIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;

                        selectedGarbage[playerid][i] = -1;
                    }
                    
                    AccountData[playerid][pTrashCollectorDelay] = 1800;

                    SetTimerEx("RespawnPV", 1000, false, "d", TrashCollectorPlayerVeh[playerid]);

                    TrashCollectorPlayerVeh[playerid] = INVALID_VEHICLE_ID;

                    gPlayerUsingLoopingAnim[playerid] = false;
                    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
                    RemovePlayerAttachedObject(playerid, 9);
                    StopRunningAnimation(playerid);

                    ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan anda rusak tugas trash collector dinyatakan gagal.");
                }
            }

            if(AccountData[playerid][pSideJob] == SIDEJOB_PIZZA)
            {
                if(JobVehicle[playerid] == SavingVehID[playerid])
                {
                    DestroyVehicle(JobVehicle[playerid]);

                    if(DestroyDynamicCP(pizzaDeliveryCP[playerid]))
                        pizzaDeliveryCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    if(DestroyDynamicActor(pizzaDeliveryActor[playerid]))
                        pizzaDeliveryActor[playerid] = STREAMER_TAG_ACTOR: INVALID_STREAMER_ID;

                    if(DestroyDynamicRaceCP(pizzaDeliveryRCP[playerid]))
                        pizzaDeliveryRCP[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

                    AccountData[playerid][pSideJob] = SIDEJOB_NONE;
                    pizzaDelivered[playerid] = 0;
                    pizzaRandom[playerid] = -1;
                    pizzaHoldingBox[playerid] = false;

                    AccountData[playerid][pPizzaSidejobDelay] = 1800;

                    gPlayerUsingLoopingAnim[playerid] = false;
                    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
                    RemovePlayerAttachedObject(playerid, 9);
                    StopRunningAnimation(playerid);

                    TogglePlayerControllable(playerid, true);
                    ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan anda rusak tugas pengantaran pizza dinyatakan gagal.");
                }
            }
        }
        if(VehicleCore[SavingVehID[playerid]][vCoreFuel] < 0) VehicleCore[SavingVehID[playerid]][vCoreFuel] = 0;
        else if(VehicleCore[SavingVehID[playerid]][vCoreFuel] > 1000) VehicleCore[SavingVehID[playerid]][vCoreFuel] = MAX_FUEL_FULL;
    }
    return 1;
}

// SpeedoTD
ptask VehicleSpeedoUpdate[250](playerid) 
{
    if(AccountData[playerid][IsLoggedIn] && AccountData[playerid][pSpawned] && SavingVehID[playerid] != INVALID_VEHICLE_ID)
    {
        if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
        {
            static Float:vAngle, Float:vX, Float:vY, Float:vZ, string[200], Float:vHealth;   

            format(string, sizeof(string), "%.0f", EVF::GetVehicleSpeed(SavingVehID[playerid]));
            PlayerTextDrawSetString(playerid, PHBE[playerid][2], string);

            format(string, sizeof(string), "%d", VehicleCore[SavingVehID[playerid]][vCoreFuel] / 10);
            PlayerTextDrawSetString(playerid, PHBE[playerid][1], string);

            GetVehicleHealth(SavingVehID[playerid], vHealth);

            new Float:vHealthPercent = 0.0;
            if(VehicleCore[SavingVehID[playerid]][vMaxHealth] > 0.0)
            {
                vHealthPercent = (vHealth / VehicleCore[SavingVehID[playerid]][vMaxHealth]) * 100.0;
                if(vHealthPercent > 100.0) vHealthPercent = 100.0;
            }

            format(string, sizeof(string), "%.0f", vHealthPercent);
            PlayerTextDrawSetString(playerid, PHBE[playerid][3], string);

            GetVehiclePos(SavingVehID[playerid], vX, vY, vZ);
            GetVehicleZAngle(SavingVehID[playerid], vAngle);

            format(string, sizeof(string), "%s I %s", GetStreetLocation(vX, vY, vZ), GetLocation(vX, vY, vZ));
            PlayerTextDrawSetString(playerid, PHBE[playerid][5], string);

            if(vAngle >= 348.75 || vAngle < 11.25) PlayerTextDrawSetString(playerid, PHBE[playerid][4], "North");
            else if(vAngle >= 303.75 && vAngle < 326.25) PlayerTextDrawSetString(playerid, PHBE[playerid][4], "Northeast");
            else if(vAngle >= 258.75 && vAngle < 281.25) PlayerTextDrawSetString(playerid, PHBE[playerid][4], "East");
            else if(vAngle >= 213.75 && vAngle < 236.25) PlayerTextDrawSetString(playerid, PHBE[playerid][4], "Southeast");
            else if(vAngle >= 168.75 && vAngle < 191.25) PlayerTextDrawSetString(playerid, PHBE[playerid][4], "South");
            else if(vAngle >= 123.25 && vAngle < 146.25) PlayerTextDrawSetString(playerid, PHBE[playerid][4], "Southwest");
            else if(vAngle >= 78.75 && vAngle < 101.25) PlayerTextDrawSetString(playerid, PHBE[playerid][4], "West");
            else if(vAngle >= 33.75 && vAngle < 56.25) PlayerTextDrawSetString(playerid, PHBE[playerid][4], "Northwest");

            gettime(av_hours, av_minutes, av_seconds);
            format(string, sizeof(string), "%02d:%02d", av_hours, av_minutes);
            PlayerTextDrawSetString(playerid, PHBE[playerid][0], string);
        }
    }
    return 1;
}

task UpdateLockLights[256]() 
{
    foreach(new vid : Vehicle)
    {
        if(VehicleCore[vid][vIsRemoted] && !IsVehicleSeatOccupied(vid, 0))
        {
            if(VehicleCore[vid][vRemotedCount] < VehicleCore[vid][vRemotedType] * 2)
            {
                if(VehicleCore[vid][vRemotedCount] % 2)
                {
                    if(!GetEngineStatus(vid))
                        SwitchVehicleEngine(vid, true);

                    VehicleCore[vid][vRemotedCount]++;
                    SwitchVehicleLight(vid, true);

                    new Float:vppos[3];
                    GetVehiclePos(vid, vppos[0], vppos[1], vppos[2]);
                    PlaySoundForPlayersInRange(1147, 5.5, vppos[0], vppos[1], vppos[2]);
                }
                else //ganjil
                {
                    VehicleCore[vid][vRemotedCount]++;
                    SwitchVehicleLight(vid, false);
                }
            }
            else
            {
                if(!IsVehicleSeatOccupied(vid,0))
                    SwitchVehicleEngine(vid, false);

                VehicleCore[vid][vIsRemoted] = false;
                VehicleCore[vid][vRemotedCount] = 0;
                SwitchVehicleLight(vid, false);
            }
        }
        else if(VehicleCore[vid][vIsRemoted] && IsVehicleSeatOccupied(vid, 0))
        {
            VehicleCore[vid][vIsRemoted] = false;
            VehicleCore[vid][vRemotedCount] = 0;
            SwitchVehicleLight(vid, false);
        }
    }
    return 1;
}

task UpdateSirenELM[160]()
{
    new panels, doors, lights, tires, Float:vHealth;
    new sirenstate;
    foreach(new vid : Vehicle)
    {
        if(!VehicleCore[vid][vIsBodyBroken])
        {
            GetVehicleDamageStatus(vid, panels, doors, lights, tires);
            if(panels != 0 || doors != 0 || lights != 0 || tires != 0)
            {
                if(VehicleCore[vid][vIsBodyUpgraded])
                {
                    GetVehicleHealth(vid, vHealth);

                    if(VehicleCore[vid][vMaxHealth] == 1000.00 && vHealth >= 800)
                    {
                        UpdateVehicleDamageStatus(vid, 0, 0, 0, 0);
                    }
                    else if(VehicleCore[vid][vMaxHealth] == 1500.00 && vHealth >= 1200)
                    {
                        UpdateVehicleDamageStatus(vid, 0, 0, 0, 0);
                    }
                    else if(VehicleCore[vid][vMaxHealth] == 2000.00 && vHealth >= 1600)
                    {
                        UpdateVehicleDamageStatus(vid, 0, 0, 0, 0);
                    }
                    else
                    {
                        VehicleCore[vid][vIsBodyBroken] = true;
                    }
                }
                else
                {
                    VehicleCore[vid][vIsBodyBroken] = true;
                }
            }
        }
        if(IsLSPDVehicle(vid) || IsLSFDVehicle(vid))
        {
            sirenstate = GetVehicleParamsSirenState(vid);
            if(sirenstate == 1)
            {
                SwitchVehicleLight(vid, true);
                GetVehicleDamageStatus(vid, VehicleCore[vid][vCoreDamage][0], VehicleCore[vid][vCoreDamage][1], VehicleCore[vid][vCoreDamage][2], VehicleCore[vid][vCoreDamage][3]);
                if(!VehicleCore[vid][vIsBlink])
                {
                    VehicleCore[vid][vIsBlink] = true;
                }

                if(VehicleCore[vid][vBlink] == 1)
                {
                    UpdateVehicleDamageStatus(vid, VehicleCore[vid][vCoreDamage][0], VehicleCore[vid][vCoreDamage][1], 69, VehicleCore[vid][vCoreDamage][3]); //mati
                    VehicleCore[vid][vBlink] = 2;
                }
                else if(VehicleCore[vid][vBlink] == 2)
                {
                    UpdateVehicleDamageStatus(vid, VehicleCore[vid][vCoreDamage][0], VehicleCore[vid][vCoreDamage][1], 1, VehicleCore[vid][vCoreDamage][3]); //kanan
                    VehicleCore[vid][vBlink] = 3;
                }
                else if(VehicleCore[vid][vBlink] == 3)
                {
                    UpdateVehicleDamageStatus(vid, VehicleCore[vid][vCoreDamage][0], VehicleCore[vid][vCoreDamage][1], 4, VehicleCore[vid][vCoreDamage][3]); //kiri
                    VehicleCore[vid][vBlink] = 4;
                }
                else if(VehicleCore[vid][vBlink] == 4)
                {
                    UpdateVehicleDamageStatus(vid, VehicleCore[vid][vCoreDamage][0], VehicleCore[vid][vCoreDamage][1], 69, VehicleCore[vid][vCoreDamage][3]); //mati
                    VehicleCore[vid][vBlink] = 5;
                }
                else if(VehicleCore[vid][vBlink] == 5)
                {
                    UpdateVehicleDamageStatus(vid, VehicleCore[vid][vCoreDamage][0], VehicleCore[vid][vCoreDamage][1], 4, VehicleCore[vid][vCoreDamage][3]); //kiri
                    VehicleCore[vid][vBlink] = 0;
                }
                else if(VehicleCore[vid][vBlink] == 0)
                {
                    UpdateVehicleDamageStatus(vid, VehicleCore[vid][vCoreDamage][0], VehicleCore[vid][vCoreDamage][1], 1, VehicleCore[vid][vCoreDamage][3]); //kanan
                    VehicleCore[vid][vBlink] = 1;
                }
            }
            else if(sirenstate == 0) //off
            {
                if(VehicleCore[vid][vIsBlink])
                {
                    for(new x; x < 5; x++)
                    {
                        if(DestroyDynamicObject(FactionVehSiren[vid][x]))
                            FactionVehSiren[vid][x] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
                    }
                    VehicleCore[vid][vIsBlink] = false;
                    VehicleCore[vid][vBlink] = 0;
                    GetVehicleDamageStatus(vid, VehicleCore[vid][vCoreDamage][0], VehicleCore[vid][vCoreDamage][1], VehicleCore[vid][vCoreDamage][2], VehicleCore[vid][vCoreDamage][3]);
                    UpdateVehicleDamageStatus(vid, VehicleCore[vid][vCoreDamage][0], VehicleCore[vid][vCoreDamage][1], VehicleCore[vid][vCoreDamage][2], VehicleCore[vid][vCoreDamage][3]);
                }
            }
        }
    }
    return 1;
}

ptask UpdatePlayerPaycheck[900000](playerid)
{
    if(AccountData[playerid][IsLoggedIn] && AccountData[playerid][pSpawned])
    {
        if(!AccountData[playerid][pIsAFK])
        {
            // switch(AccountData[playerid][pVIP])
            // {
            //     case 0, 1:
            //     {
            //         AccountData[playerid][pSlipSalary] += 2015;
            //         ShowFivemNotify(playerid, "Pahlawan Roleplay~n~TUNJANGAN", "Anda telah menerima tunjangan dari Pemerintah Pahlawan Roleplay senilai ~g~$20.15", "hud:radar_cash", 11);
            //     }
            //     case 2:
            //     {
            //         AccountData[playerid][pSlipSalary] += (2015*2);
            //         ShowFivemNotify(playerid, "Pahlawan Roleplay~n~TUNJANGAN", "Anda telah menerima tunjangan dari Pemerintah Pahlawan Roleplay senilai ~g~$40.30", "hud:radar_cash", 11);
            //     }
            //     case 3:
            //     {
            //         AccountData[playerid][pSlipSalary] += (2015*3);
            //         ShowFivemNotify(playerid, "Pahlawan Roleplay~n~TUNJANGAN", "Anda telah menerima tunjangan dari Pemerintah Pahlawan Roleplay senilai ~g~$60.45", "hud:radar_cash", 11);
            //     }
            // }

            if(AccountData[playerid][pFaction] != FACTION_NONE)
            {
                if(AccountData[playerid][pOnDuty])
                {
                    AccountData[playerid][pSlipSalary] += 250;
                    ShowTDN(playerid, NOTIFICATION_INFO, "Anda menerima $250 sebagai tunjangan duty faction.");
                }
            }
        }
    }
    return 1;
}

ptask UpdateDragTimer[1200](playerid)
{
    if(AccountData[playerid][IsLoggedIn] && AccountData[playerid][pSpawned])
    {
        if(AccountData[playerid][DraggingID] != INVALID_PLAYER_ID)
        {
            if(IsPlayerConnected(AccountData[playerid][DraggingID]))
            {
                static Float:X, Float:Y, Float:Z, Float:Ang, peInterior, VW;
                peInterior = GetPlayerInterior(playerid);
                VW = GetPlayerVirtualWorld(playerid);
                GetPlayerPos(playerid, X, Y, Z);
                GetPlayerFacingAngle(playerid, Ang);

                X += (0.75 * -floatsin(-Ang, degrees));
                Y += (0.75 * -floatcos(-Ang, degrees));

                SetPlayerPos(AccountData[playerid][DraggingID], X, Y, Z);
                if(GetPlayerInterior(AccountData[playerid][DraggingID]) != peInterior) SetPlayerInteriorEx(AccountData[playerid][DraggingID], peInterior);
                if(GetPlayerVirtualWorld(AccountData[playerid][DraggingID]) != VW) SetPlayerVirtualWorldEx(AccountData[playerid][DraggingID], VW);
                AccountData[AccountData[playerid][DraggingID]][pInDoor] = AccountData[playerid][pInDoor];
                AccountData[AccountData[playerid][DraggingID]][pInHouse] = AccountData[playerid][pInHouse];
                AccountData[AccountData[playerid][DraggingID]][pInBiz] = AccountData[playerid][pInBiz];
                AccountData[AccountData[playerid][DraggingID]][pInRusun] = AccountData[playerid][pInRusun];
                Anticheat[AccountData[playerid][DraggingID]][acImmunity] = gettime() + 5;
            }
        }
    }
    return 1;
}

task vehrentchecking[1000]()
{
    foreach(new pv : PvtVehicles)			
	{
        if(PlayerVehicle[pv][pVehRental] > -1 && PlayerVehicle[pv][pVehRentTime] - gettime() <= 0)
        {
            PlayerVehicle[pv][pVehRental] = -1;
            PlayerVehicle[pv][pVehRentTime] = 0;

            if(Iter_Contains(Vehicle, PlayerVehicle[pv][pVehPhysic]))
            {
                SetVehicleNeonLights(PlayerVehicle[pv][pVehPhysic], false, PlayerVehicle[pv][pVehNeon], 0);
            }
            DestroyVehicle(PlayerVehicle[pv][pVehPhysic]);
            PlayerVehicle[pv][pVehHandbraked] = false;

            new rentqry[1024];
            mysql_format(g_SQL, rentqry, sizeof(rentqry), "DELETE FROM `vehicle_bagasi` WHERE `Veh_DBID`=%d", PlayerVehicle[pv][pVehID]);
            mysql_pquery(g_SQL, rentqry);
            mysql_format(g_SQL, rentqry, sizeof(rentqry), "DELETE FROM `vehicle_holster` WHERE `Veh_DBID`=%d", PlayerVehicle[pv][pVehID]);
            mysql_pquery(g_SQL, rentqry);
            mysql_format(g_SQL, rentqry, sizeof(rentqry), "DELETE FROM `player_vehicles` WHERE `id` = %d", PlayerVehicle[pv][pVehID]);
            mysql_pquery(g_SQL, rentqry);
            mysql_format(g_SQL, rentqry, sizeof(rentqry), "DELETE FROM `vtoys` WHERE `Veh_DBID`=%d", PlayerVehicle[pv][pVehID]);
            mysql_pquery(g_SQL, rentqry);

            for(new x; x < 6; x++)
            {
                vtData[pv][x][vtoy_modelid] = 0;
                vtData[pv][x][vtoy_text][0] = EOS;
                strcopy(vtData[pv][x][vtoy_font], "Arial");
                vtData[pv][x][vtoy_fontsize] = 11;
                vtData[pv][x][vtoy_fontcolor][0] = 255;
                vtData[pv][x][vtoy_fontcolor][1] = 0;
                vtData[pv][x][vtoy_fontcolor][2] = 0;
                vtData[pv][x][vtoy_fontcolor][3] = 0;
                vtData[pv][x][vtoy_fontcolor][4] = 0;
                vtData[pv][x][vtoy_objectcolor][0] = 255;
                vtData[pv][x][vtoy_objectcolor][1] = 0;
                vtData[pv][x][vtoy_objectcolor][2] = 0;
                vtData[pv][x][vtoy_objectcolor][3] = 0;
                vtData[pv][x][vtoy_objectcolor][4] = 0;
                vtData[pv][x][vtoy_x] = 0.0;
                vtData[pv][x][vtoy_y] = 0.0;
                vtData[pv][x][vtoy_z] = 0.0;
                vtData[pv][x][vtoy_rx] = 0.0;
                vtData[pv][x][vtoy_ry] = 0.0;
                vtData[pv][x][vtoy_rz] = 0.0;
            }

            for(new x; x < MAX_BAGASI_ITEMS; x++)
            {
                VehicleBagasi[pv][x][vehicleBagasiExists] = false;
                VehicleBagasi[pv][x][vehicleBagasiID] = 0;
                VehicleBagasi[pv][x][vehicleBagasiVDBID] = 0;
                VehicleBagasi[pv][x][vehicleBagasiTemp][0] = EOS;
                VehicleBagasi[pv][x][vehicleBagasiModel] = 0;
                VehicleBagasi[pv][x][vehicleBagasiQuant] = 0;
            }

            for(new z; z < 3; z++)
            {
                VehicleHolster[pv][vHolsterTaken][z] = false;
                VehicleHolster[pv][vHolsterID][z] = -1;
                VehicleHolster[pv][vHolsterWeaponID][z] = 0;
                VehicleHolster[pv][vHolsterWeaponAmmo][z] = 0;
            }

            Iter_Remove(PvtVehicles, pv);
        }
    }
    return 1;
}

ptask playerstablingdmax[1000](playerid)
{
    if(AccountData[playerid][IsLoggedIn] && AccountData[playerid][pSpawned])
    {
        if(Inventory_Count(playerid, "Obeng") > 1)
            Inventory_Set(playerid, "Obeng", 19627, 1);
        if(Inventory_Count(playerid, "Cangkul") > 1)
            Inventory_Set(playerid, "Cangkul", 2228, 1);
        if(Inventory_Count(playerid, "Ember") > 1)
            Inventory_Set(playerid, "Ember", 19468, 1);
        if(Inventory_Count(playerid, "Ember Penuh") > 1)
            Inventory_Set(playerid, "Ember Penuh", 1554, 1);
    }
    return 1;
}

ptask UpdateSpecStats[1000](playerid)
{
    if(AccountData[playerid][pSpawned] && AccountData[playerid][pSpec] != INVALID_PLAYER_ID)
    {
        if(IsPlayerConnected(AccountData[playerid][pSpec]) && AccountData[AccountData[playerid][pSpec]][pSpawned])
        {
            new otherid = AccountData[playerid][pSpec];
            static string[144];

            new Float:health, Float:armour, keys, ups, lefts, Float:vhealth;
            GetPlayerHealth(otherid, health);
            GetPlayerArmour(otherid, armour);
            GetPlayerKeys(otherid, keys, ups, lefts);

            if(IsPlayerInAnyVehicle(otherid) && IsValidVehicle(GetPlayerVehicleID(otherid)))
            {
                if (GetPlayerState(otherid) == PLAYER_STATE_DRIVER)
                {
                    GetVehicleHealth(GetPlayerVehicleID(otherid), vhealth);
                    format(string, sizeof(string), "%s (%d)~n~HP: %.2f~n~AP: %.2f~n~vHP: %.2f~n~Cash: $%s~n~World: %d // Int: %d~n~Keys: %d %d %d~n~FPS: %d // Ping: %d", AccountData[otherid][pName], otherid, health, armour, vhealth, FormatMoney(AccountData[otherid][pMoney]), GetPlayerVirtualWorld(otherid), GetPlayerInterior(otherid), keys, ups, lefts, GetPlayerFPS(otherid), GetPlayerPing(otherid));
                    PlayerTextDrawSetString(playerid, SpecInfoTD[playerid], string);
                }
                else
                {
                    format(string, sizeof(string), "%s (%d)~n~HP: %.2f~n~AP: %.2f~n~Cash: $%s~n~World: %d // Int: %d~n~Keys: %d %d %d~n~FPS: %d // Ping: %d", AccountData[otherid][pName], otherid, health, armour, FormatMoney(AccountData[otherid][pMoney]), GetPlayerVirtualWorld(otherid), GetPlayerInterior(otherid), keys, ups, lefts, GetPlayerFPS(otherid), GetPlayerPing(otherid));
                    PlayerTextDrawSetString(playerid, SpecInfoTD[playerid], string);
                }
            }
            else
            {
                format(string, sizeof(string), "%s (%d)~n~HP: %.2f~n~AP: %.2f~n~Cash: $%s~n~World: %d // Int: %d~n~Keys: %d %d %d~n~FPS: %d // Ping: %d", AccountData[otherid][pName], otherid, health, armour, FormatMoney(AccountData[otherid][pMoney]), GetPlayerVirtualWorld(otherid), GetPlayerInterior(otherid), keys, ups, lefts, GetPlayerFPS(otherid), GetPlayerPing(otherid));
                PlayerTextDrawSetString(playerid, SpecInfoTD[playerid], string);
            }
        }
    }
    return 1;
}

ptask playerdelay[1000](playerid)
{
    if(AccountData[playerid][IsLoggedIn] && AccountData[playerid][pSpawned])
    {
        //holding trash bag check
        if(TrashCollectorHoldingBag[playerid])
        {
            if(GetPlayerAnimationIndex(playerid) != 463)
            	ApplyAnimation(playerid, "FAT", "FatWalk", 4.1, true, true, true, true, 1, true);
        }

        //using skate
        if(AccountData[playerid][pSkating])
        {
            if(GetPlayerAnimationIndex(playerid) != 1458)
                ApplyAnimation(playerid,"SKATE","skate_sprint",0.67,true,true,true,true,true,true);
        }

        //taser check
        if(AccountData[playerid][pTazedTime] > 0)
		{
            AccountData[playerid][pTazedTime]--;

			if(GetPlayerAnimationIndex(playerid) != 388)
            	ApplyAnimation(playerid, "CRACK", "crckdeth4", 4.0, false, false, false, true, 0, true);

            if(AccountData[playerid][pTazedTime] <= 0)
            {
                AccountData[playerid][pTazedTime] = 0;
                TogglePlayerControllable(playerid, true);
                ShowPlayerFooter(playerid, "Efek taser ~r~berakhir.", 2500);
			}
		}

        //beanbag check
        if(AccountData[playerid][pBeanbagTime] > 0)
		{
            AccountData[playerid][pBeanbagTime]--;

			if(GetPlayerAnimationIndex(playerid) != 1537)
            	ApplyAnimation(playerid, "SWEET", "Sweet_injuredloop", 4.1, true, true, true, true, 0, true);

            if(AccountData[playerid][pBeanbagTime] <= 0)
            {
                AccountData[playerid][pBeanbagTime] = 0;
                TogglePlayerControllable(playerid, true);
                ShowPlayerFooter(playerid, "Efek peluru karet ~r~berakhir.", 2500);
			}
		}

        //tackle check
        if(AccountData[playerid][pTackleTime] > 0)
		{
            AccountData[playerid][pTackleTime]--;

			if(GetPlayerAnimationIndex(playerid) != 1151)
            	ApplyAnimation(playerid, "PED", "FLOOR_hit_f", 4.1, false, false, false, true, 0, true);

            if(AccountData[playerid][pTackleTime] <= 0)
            {
                AccountData[playerid][pTackleTime] = 0;
                TogglePlayerControllable(playerid, true);
                ShowPlayerFooter(playerid, "Efek tackle ~r~berakhir.", 2500);
			}
		}

        //stress anim check
        if(AccountData[playerid][pStressedTime] > 0)
		{
            AccountData[playerid][pStressedTime]--;

            if(!IsPlayerInAnyVehicle(playerid))
            {
                if(GetPlayerAnimationIndex(playerid) != 388)
                    ApplyAnimation(playerid, "CRACK", "crckdeth4", 4.0, false, false, false, true, 0, true);
            }

            if(AccountData[playerid][pStressedTime] <= 0)
            {
                TogglePlayerControllable(playerid, true);
                AccountData[playerid][pStressedTime] = 0;
                HideStressEffectTD(playerid);
			}
		}
        
        //advert delay
        if(AccountData[playerid][pAdvertDelay] != 0 && AccountData[playerid][pAdvertDelay] <= gettime())
        {
            AccountData[playerid][pAdvertDelay] = 0;
            ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sekarang sudah bisa membuat iklan kembali!");
        }

        //accept death check
        if(AccountData[playerid][pKnockdown] && AccountData[playerid][pAccDeathTime] > 0)
        {
            if(AccountData[playerid][pAccDeathTime] != 0 && AccountData[playerid][pAccDeathTime] <= gettime())
            {
                AccountData[playerid][pAccDeathTime] = 0;
                SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda sudah dapat menggunakan "CMDEA"'/medic' "WHITE"untuk menghidupkan karakter!");
            }
        }

        //fixme checking
        if(AccountData[playerid][pStuckRequest] > 0)
        {
            if(AccountData[playerid][pStuckWaiting] != 0 && AccountData[playerid][pStuckWaiting] <= gettime())
            {
                AccountData[playerid][pStuckRequest] = 0;
                AccountData[playerid][pStuckWaiting] = 0;
                ShowTDN(playerid, NOTIFICATION_WARNING, "Fix request anda tidak ada yang menerima, silakan ulangi jika masih mengalami masalah!");
            }
        }

        //License expired checking
        if(AccountData[playerid][pGVL1Lic])
        {
            if(AccountData[playerid][pGVL1LicTime] != 0 && AccountData[playerid][pGVL1LicTime] <= gettime())
            {
                SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Dokumen "CMDEA"SIM A "WHITE"anda telah expired, silakan lakukan perpanjangan!");
                AccountData[playerid][pGVL1LicTime] = 0;
            }
        }
        if(AccountData[playerid][pGVL2Lic])
        {
            if(AccountData[playerid][pGVL2LicTime] != 0 && AccountData[playerid][pGVL2LicTime] <= gettime())
            {
                SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Dokumen "CMDEA"SIM B "WHITE"anda telah expired, silakan lakukan perpanjangan!");
                AccountData[playerid][pGVL2LicTime] = 0;
            }
        }
        if(AccountData[playerid][pMBLic])
        {
            if(AccountData[playerid][pMBLicTime] != 0 && AccountData[playerid][pMBLicTime] <= gettime())
            {
                SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Dokumen "CMDEA"SIM C "WHITE"anda telah expired, silakan lakukan perpanjangan!");
                AccountData[playerid][pMBLicTime] = 0;
            }
        }
        if(AccountData[playerid][pBLic])
        {
            if(AccountData[playerid][pBLicTime] != 0 && AccountData[playerid][pBLicTime] <= gettime())
            {
                SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Dokumen "CMDEA"Surat Izin Berlayar "WHITE"anda telah expired, silakan lakukan perpanjangan!");
                AccountData[playerid][pBLicTime] = 0;
            }
        }
        if(AccountData[playerid][pAir1Lic])
        {
            if(AccountData[playerid][pAir1LicTime] != 0 && AccountData[playerid][pAir1LicTime] <= gettime())
            {
                SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Dokumen "CMDEA"Surat Izin Helikopter "WHITE"anda telah expired, silakan lakukan perpanjangan!");
                AccountData[playerid][pAir1LicTime] = 0;
            }
        }
        if(AccountData[playerid][pAir2Lic])
        {
            if(AccountData[playerid][pAir2LicTime] != 0 && AccountData[playerid][pAir2LicTime] <= gettime())
            {
                SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Dokumen "CMDEA"Surat Izin Pesawat "WHITE"anda telah expired, silakan lakukan perpanjangan!");
                AccountData[playerid][pAir2LicTime] = 0;
            }
        }
        if(AccountData[playerid][pFirearmLic])
        {
            if(AccountData[playerid][pFirearmLicTime] != 0 && AccountData[playerid][pFirearmLicTime] <= gettime())
            {
                SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Dokumen "CMDEA"Kartu Izin Senjata Api "WHITE"anda telah expired, silakan lakukan perpanjangan!");
                AccountData[playerid][pFirearmLicTime] = 0;
            }
        }
        if(AccountData[playerid][pHuntingLic])
        {
            if(AccountData[playerid][pHuntingLicTime] != 0 && AccountData[playerid][pHuntingLicTime] <= gettime())
            {
                SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Dokumen "CMDEA"Kartu Izin Berburu "WHITE"anda telah expired, silakan lakukan perpanjangan!");
                AccountData[playerid][pHuntingLicTime] = 0;
            }
        }

        //steward Expired Checking
        if(AccountData[playerid][pSteward])
        {
            if(AccountData[playerid][pStewardTime] != 0 && AccountData[playerid][pStewardTime] <= gettime())
            {
                SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Status "CMDEA"Stewards "WHITE"anda telah expired, anda sekarang player biasa!");
                AccountData[playerid][pSteward] = false;
                AccountData[playerid][pStewardTime] = 0;
            }
        }
        
        //KTP Expired Checking
        if(AccountData[playerid][pKTPTime])
        {
            if(AccountData[playerid][pKTPTime] != 0 && AccountData[playerid][pKTPTime] <= gettime())
            {
                SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Masa aktif "CMDEA"KTP "WHITE"anda sudah expired, silakan urus kembali untuk memperpanjang!");
                AccountData[playerid][pHasKTP] = false;
                AccountData[playerid][pKTPTime] = 0;
            }
        }

        //VIP Expired Checking
        if(AccountData[playerid][pVIP] > 0)
        {
            if(AccountData[playerid][pVIPTime] != 0 && AccountData[playerid][pVIPTime] <= gettime())
            {
                SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Status "CMDEA"VIP "WHITE"anda telah expired, anda sekarang player biasa!");
                AccountData[playerid][pVIP] = 0;
                AccountData[playerid][pVIPTime] = 0;
            }
        }

        //dokumen checking
        if(DocumentInfo[playerid][BPJS])
        {
            if(DocumentInfo[playerid][BPJSDur] != 0 && DocumentInfo[playerid][BPJSDur] <= gettime())
            {
                SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Kartu "CMDEA"BPJS "WHITE"anda sudah kedaluwarsa dan anda dapat kembali mengurusnya!");
                DocumentInfo[playerid][BPJS] = false;
                DocumentInfo[playerid][BPJSClass] = 0;
                DocumentInfo[playerid][BPJSDur] = 0;
                DocumentInfo[playerid][BPJSIssuer][0] = EOS;
                DocumentInfo[playerid][BPJSIssuerRank][0] = EOS;
                DocumentInfo[playerid][BPJSIssueDate][0] = EOS;
                
                static shsh[128];
                mysql_format(g_SQL, shsh, sizeof(shsh), "DELETE FROM `documents` WHERE `Owner_ID` = %d AND `Type` = 1", AccountData[playerid][pID]);
                mysql_pquery(g_SQL, shsh);
            }
        }

        if(DocumentInfo[playerid][SKS])
        {
            if(DocumentInfo[playerid][SKSDur] != 0 && DocumentInfo[playerid][SKSDur] <= gettime())
            {
                SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Dokumen "CMDEA"SKS "WHITE"anda sudah kedaluwarsa dan anda dapat kembali mengurusnya!");
                DocumentInfo[playerid][SKS] = false;
                DocumentInfo[playerid][SKSDur] = 0;
                DocumentInfo[playerid][SKSText][0] = EOS;
                DocumentInfo[playerid][SKSIssuer][0] = EOS;
                DocumentInfo[playerid][SKSIssuerRank][0] = EOS;
                DocumentInfo[playerid][SKSIssueDate][0] = EOS;
                
                static shsh[128];
                mysql_format(g_SQL, shsh, sizeof(shsh), "DELETE FROM `documents` WHERE `Owner_ID` = %d AND `Type` = 2", AccountData[playerid][pID]);
                mysql_pquery(g_SQL, shsh);
            }
        }

        if(DocumentInfo[playerid][SP])
        {
            if(DocumentInfo[playerid][SPDur] != 0 && DocumentInfo[playerid][SPDur] <= gettime())
            {
                SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Dokumen "CMDEA"Surat Psikologi "WHITE"anda sudah kedaluwarsa dan anda dapat kembali mengurusnya!");
                DocumentInfo[playerid][SP] = false;
                DocumentInfo[playerid][SPDur] = 0;
                DocumentInfo[playerid][SPText][0] = EOS;
                DocumentInfo[playerid][SPIssuer][0] = EOS;
                DocumentInfo[playerid][SPIssuerRank][0] = EOS;
                DocumentInfo[playerid][SPIssueDate][0] = EOS;
                
                static shsh[128];
                mysql_format(g_SQL, shsh, sizeof(shsh), "DELETE FROM `documents` WHERE `Owner_ID` = %d AND `Type` = 5", AccountData[playerid][pID]);
                mysql_pquery(g_SQL, shsh);
            }
        }

        if(DocumentInfo[playerid][SKCK])
        {
            if(DocumentInfo[playerid][SKCKDur] != 0 && DocumentInfo[playerid][SKCKDur] <= gettime())
            {
                SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Dokumen "CMDEA"SKCK "WHITE"anda sudah kedaluwarsa dan anda dapat kembali mengurusnya!");
                DocumentInfo[playerid][SKCK] = false;
                DocumentInfo[playerid][SKCKDur] = 0;
                DocumentInfo[playerid][SKCKText][0] = EOS;
                DocumentInfo[playerid][SKCKIssuer][0] = EOS;
                DocumentInfo[playerid][SKCKIssuerRank][0] = EOS;
                DocumentInfo[playerid][SKCKIssueDate][0] = EOS;
                
                static shsh[128];
                mysql_format(g_SQL, shsh, sizeof(shsh), "DELETE FROM `documents` WHERE `Owner_ID` = %d AND `Type` = 3", AccountData[playerid][pID]);
                mysql_pquery(g_SQL, shsh);
            }
        }

        if(DocumentInfo[playerid][SKWB])
        {
            if(DocumentInfo[playerid][SKWBDur] != 0 && DocumentInfo[playerid][SKWBDur] <= gettime())
            {
                SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Dokumen "CMDEA"SKWB "WHITE"anda sudah kedaluwarsa, artinya anda tidak dapat jaminan warga baru lagi!");
                DocumentInfo[playerid][SKWB] = false;
                DocumentInfo[playerid][SKWBDur] = 0;
                DocumentInfo[playerid][SKWBText][0] = EOS;
                DocumentInfo[playerid][SKWBIssuer][0] = EOS;
                DocumentInfo[playerid][SKWBIssuerRank][0] = EOS;
                DocumentInfo[playerid][SKWBIssueDate][0] = EOS;
                
                static shsh[128];
                mysql_format(g_SQL, shsh, sizeof(shsh), "DELETE FROM `documents` WHERE `Owner_ID` = %d AND `Type` = 4", AccountData[playerid][pID]);
                mysql_pquery(g_SQL, shsh);
            }
        }
        
        //sidejob sweeper
        if(AccountData[playerid][pMowingSidejobDelay] > 0)
        {
            AccountData[playerid][pMowingSidejobDelay]--;

            if(AccountData[playerid][pMowingSidejobDelay] <= 1)
            {
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda sekarang bisa melakukan sidejob mowing lagi!");
                AccountData[playerid][pMowingSidejobDelay] = 0;
            }
        }
        //sidejob sweeper
        if(AccountData[playerid][pSweeperSidejobDelay] > 0)
        {
            AccountData[playerid][pSweeperSidejobDelay]--;

            if(AccountData[playerid][pSweeperSidejobDelay] <= 1)
            {
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda sekarang bisa melakukan sidejob sweeper lagi!");
                AccountData[playerid][pSweeperSidejobDelay] = 0;
            }
        }
        //sidejob forklift
        if(AccountData[playerid][pForkliftSidejobDelay] > 0)
        {
            AccountData[playerid][pForkliftSidejobDelay]--;

            if(AccountData[playerid][pForkliftSidejobDelay] <= 1)
            {
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda sekarang bisa melakukan sidejob forklift lagi!");
                AccountData[playerid][pForkliftSidejobDelay] = 0;
            }
        }
        //sidejob trash collector
        if(AccountData[playerid][pTrashCollectorDelay] > 0)
        {
            AccountData[playerid][pTrashCollectorDelay]--;

            if(AccountData[playerid][pTrashCollectorDelay] <= 1)
            {
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda sekarang bisa melakukan sidejob trash collector lagi");
                AccountData[playerid][pTrashCollectorDelay] = 0;
            }
        }
        //sidejob forklift
        if(AccountData[playerid][pPizzaSidejobDelay] > 0)
        {
            AccountData[playerid][pPizzaSidejobDelay]--;

            if(AccountData[playerid][pPizzaSidejobDelay] <= 1)
            {
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda sekarang bisa melakukan sidejob pizza lagi");
                AccountData[playerid][pPizzaSidejobDelay] = 0;
            }
        }
    }
    return 1;
}

ptask IdlingCheck[1000](playerid)
{
    if(IsPlayerConnected(playerid) && AccountData[playerid][IsLoggedIn])
    {
        if(!AccountData[playerid][pKnockdown] && !AccountData[playerid][pIsAFK] && !AccountData[playerid][pInEvent])
        {
            if(AccountData[playerid][pIdlingTime] >= 35)
            {
                if(!gPlayerUsingLoopingAnim[playerid] && !IsPlayerMoving(playerid) && !IsPlayerInAnyVehicle(playerid))
                {
                    if(GetPlayerAnimationIndex(playerid) == 1189)
                    {
                        if(IsPlayerInRangeOfPoint(playerid, 1.0, AccountData[playerid][idlex], AccountData[playerid][idley], AccountData[playerid][idlez]))
                        {
                            static randanim;
                            randanim = random(6);
                            switch(randanim)
                            {
                                case 0:
                                {
                                    ApplyAnimation(playerid, "PLAYIDLES", "shldr", 2.17, false, true, true, false, 0, true);
                                }
                                case 1:
                                {
                                    ApplyAnimation(playerid, "PLAYIDLES", "stretch", 4.60, false, true, true, false, 0, true);
                                }
                                case 2:
                                {
                                    ApplyAnimation(playerid, "PLAYIDLES", "strleg", 3.67, false, true, true, false, 0, true);
                                }
                                case 3:
                                {
                                    ApplyAnimation(playerid, "PLAYIDLES", "time", 5.20, false, true, true, false, 0, true);
                                }
                                case 4:
                                {
                                    ApplyAnimation(playerid, "ped", "XPRESSscratch", 3.97, false, true, true, false, 0, true);
                                }
                                case 5:
                                {
                                    ApplyAnimation(playerid, "DEALER", "DEALER_IDLE_01", 5.00, false, true, true, false, 0, true);
                                }
                            }
                        }
                    }
                }
                AccountData[playerid][pIdlingTime] = 0;
            }
            else
            {
                AccountData[playerid][pIdlingTime]++;

                if(AccountData[playerid][pIdlingTime] == 15)
                {
                    GetPlayerPos(playerid, AccountData[playerid][idlex], AccountData[playerid][idley], AccountData[playerid][idlez]);
                }
            }
        }
    }
    return 1;
}

ptask AFKChecking[1000](playerid)
{
    if(IsPlayerConnected(playerid) && AccountData[playerid][pSpawned])
    {
        if(!PlayerBlackJack[playerid][Seated])
        {
            if(!AccountData[playerid][pIsAFK])
            {
                if(AccountData[playerid][pAFKTime] >= 0)
                {
                    AccountData[playerid][pAFKCount]++;

                    switch(AccountData[playerid][pAFKCount])
                    {
                        case 300:
                        {
                            GetPlayerPos(playerid, AccountData[playerid][afkx], AccountData[playerid][afky], AccountData[playerid][afkz]);
                        }
                        case 600:
                        {
                            if(IsPlayerInRangeOfPoint(playerid, 1.5, AccountData[playerid][afkx], AccountData[playerid][afky], AccountData[playerid][afkz]))
                            {
                                SetPlayerAFK(playerid);
                            }
                            else
                            {
                                AccountData[playerid][pAFKCount] = 0;
                            }
                        }
                    }
                }
            }
            else
            {
                AccountData[playerid][pAFKTime]++;

                static string[75];
                format(string, sizeof(string), "~y~Anda AFK~n~selama ~r~%d detik~n~~y~gunakan /afk kembali ke rp", AccountData[playerid][pAFKTime]);
                GameTextForPlayer(playerid, string, 1000, 4);
            }
        }
    }
}

ptask UpdateTimeActivity[1000](playerid)
{
    if(pTakingTrashTimer[playerid])
    {
        if(!IsPlayerConnected(playerid))
        {
            pTakingTrashTimer[playerid] = false;
            return 0;
        }

        if(AccountData[playerid][pTempValue] == -1)
        {
            pTakingTrashTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;

            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);
            return 0;
        }
        
        if(AccountData[playerid][pActivityTime] >= 6)
        {
            pTakingTrashTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;

            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            GarbageData[AccountData[playerid][pTempValue]][garbageAvailTime] = gettime() + 300;
            GarbageData[AccountData[playerid][pTempValue]][garbageTaken] = true;

            new randbott;
            randbott = Random(31);
            new randbotvalue = RandomEx(2, 11);
            new randplasvalue = RandomEx(2, 11);

            switch(randbott)
            {
                case 0..9:
                {
                    ShowTDN(playerid, NOTIFICATION_INFO, "Anda tidak mendapatkan apa-apa!");
                }

                case 10..30:
                {
                    Inventory_Add(playerid, "Botol", 19570, randbotvalue);
                    ShowItemBox(playerid, "Botol", sprintf("Received %dx", randbotvalue), 19570, 5);

                    Inventory_Add(playerid, "Plastik", 1265, randplasvalue);
                    ShowItemBox(playerid, "Plastik", sprintf("Received %dx", randplasvalue), 1265, 5);
                }
            }
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/6;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pTakingKanabisTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pTakingKanabisTimer[playerid] = false;

            KanabisData[AccountData[playerid][pInCannabis]][kanabisTaken] = false;
            return 0;
        }

        if(AccountData[playerid][pInCannabis] == -1)
        {
            pTakingKanabisTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;
            KanabisData[AccountData[playerid][pInCannabis]][kanabisTaken] = false;
            AccountData[playerid][pInCannabis] = -1;
            return 0;
        }

        if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        {
            pTakingKanabisTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;
            KanabisData[AccountData[playerid][pInCannabis]][kanabisTaken] = false;
            AccountData[playerid][pInCannabis] = -1;
            return 0;
        }

        if(!IsValidDynamicArea(KanabisData[AccountData[playerid][pInCannabis]][kanabisArea]))
        {
            pTakingKanabisTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;
            KanabisData[AccountData[playerid][pInCannabis]][kanabisTaken] = false;
            AccountData[playerid][pInCannabis] = -1;
            return 0;
        }

        if(!IsPlayerInDynamicArea(playerid, KanabisData[AccountData[playerid][pInCannabis]][kanabisArea]))
        {
            pTakingKanabisTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;
            KanabisData[AccountData[playerid][pInCannabis]][kanabisTaken] = false;
            AccountData[playerid][pInCannabis] = -1;
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pTakingKanabisTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;
            KanabisData[AccountData[playerid][pInCannabis]][kanabisTaken] = false;
            AccountData[playerid][pInCannabis] = -1;

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 6)
        {
            pTakingKanabisTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;
            KanabisData[AccountData[playerid][pInCannabis]][kanabisTaken] = false;

            if(DestroyDynamicObject(KanabisData[AccountData[playerid][pInCannabis]][kanabisObject]))
                KanabisData[AccountData[playerid][pInCannabis]][kanabisObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

            if(DestroyDynamicArea(KanabisData[AccountData[playerid][pInCannabis]][kanabisArea]))
                KanabisData[AccountData[playerid][pInCannabis]][kanabisArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

            KanabisData[AccountData[playerid][pInCannabis]][kanabisGrow] = gettime() + 60;

            AccountData[playerid][pThirst]--;
            AccountData[playerid][pHunger]--;
            AccountData[playerid][pStress]++;

            Inventory_Add(playerid, "Daun Ganja", 19473);
            
            ShowItemBox(playerid, "Daun Ganja", "Received 1x", 19473, 5);

            AccountData[playerid][pInCannabis] = -1;
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/6;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pProcessKanabisTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pProcessKanabisTimer[playerid] = false;
            return 0;
        }

        if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        {
            pProcessKanabisTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;
            return 0;
        }

        if(!IsPlayerInDynamicArea(playerid, ProcessMarijuanaArea))
        {
            pProcessKanabisTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;
            return 0;
        }

        if(Inventory_Count(playerid, "Daun Ganja") < 3)
        {
            pProcessKanabisTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Daun Ganja! (Min: 3)");
            return 0;
        }

        if(Inventory_Count(playerid, "Plastik") < 2)
        {
            pProcessKanabisTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Plastik! (Min: 2)");
            return 0;
        }
        
        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pProcessKanabisTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 6)
        {
            pProcessKanabisTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;

            AccountData[playerid][pThirst]--;
            AccountData[playerid][pHunger]--;
            AccountData[playerid][pStress]++;

            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membuat Marijuana!");
            Inventory_Remove(playerid, "Daun Ganja", 3);
            Inventory_Remove(playerid, "Plastik", 2);
            Inventory_Add(playerid, "Marijuana", 1578);
            ShowItemBox(playerid, "Daun Ganja", "Removed 3x", 19473, 4);
            ShowItemBox(playerid, "Plastik", "Removed 2x", 1265, 5);
            ShowItemBox(playerid, "Marijuana", "Received 1x", 1578, 6);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;
            
            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/6;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }
    if(pCraftingWeaponTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pCraftingWeaponTimer[playerid] = false;
            return 0;
        }

        if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        {
            pCraftingWeaponTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;
            return 0;
        }

        if(!IsPlayerInRangeOfPoint(playerid, 3.5, -1864.4888,-1606.3203,21.7578))
        {
            pCraftingWeaponTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;
            return 0;
        }
        
        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pCraftingWeaponTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 36)
        {
            pCraftingWeaponTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;

            AccountData[playerid][pThirst] -= 5;
            AccountData[playerid][pHunger] -= 5;
            AccountData[playerid][pStress] += 5;

            switch(AccountData[playerid][pTempValue2])
            {
                case 0:
                {
                    GivePlayerWeaponEx(playerid, 22, 250, WEAPON_TYPE_PLAYER);
                    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membuat Colt-45");
                    ShowItemBox(playerid, "Colt-45", "Received 1x", 346, 5);
                }
                case 1:
                {
                    GivePlayerWeaponEx(playerid, 24, 250, WEAPON_TYPE_PLAYER);
                    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membuat Desert Eagle");
                    ShowItemBox(playerid, "Desert Eagle", "Received 1x", 348, 5);
                }
                case 2:
                {
                    GivePlayerWeaponEx(playerid, 28, 500, WEAPON_TYPE_PLAYER);
                    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membuat Uzi");
                    ShowItemBox(playerid, "MP5", "Received 1x", 353, 5);
                }
                case 3:
                {
                    GivePlayerWeaponEx(playerid, 32, 500, WEAPON_TYPE_PLAYER);
                    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membuat Tec-9");
                    ShowItemBox(playerid, "Tec-9", "Received 1x", 372, 5);
                }
                case 4:
                {
                    GivePlayerWeaponEx(playerid, 25, 300, WEAPON_TYPE_PLAYER);
                    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membuat Shotgun");
                    ShowItemBox(playerid, "Shotgun", "Received 1x", 349, 5);
                }
                case 5:
                {
                    GivePlayerWeaponEx(playerid, 30, 500, WEAPON_TYPE_PLAYER);
                    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membuat AK-47");
                    ShowItemBox(playerid, "AK-47", "Received 1x", 355, 5);
                }
            }
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;
            
            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/36;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pCraftingDrugTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pCraftingDrugTimer[playerid] = false;
            return 0;
        }

        if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        {
            pCraftingDrugTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;
            return 0;
        }

        if(!IsPlayerInRangeOfPoint(playerid, 3.5, -2671.4055,2311.7197,23.7979))
        {
            pCraftingDrugTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;
            return 0;
        }
        
        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pCraftingDrugTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 16)
        {
            pCraftingDrugTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;

            AccountData[playerid][pThirst] -= 2;
            AccountData[playerid][pHunger] -= 2;
            AccountData[playerid][pStress] += 2;

            switch(AccountData[playerid][pTempValue2])
            {
                case 0:
                {
                    Inventory_Add(playerid, "Sinte", 3027);
                    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membuat Sinte");
                    ShowItemBox(playerid, "Sinte", "Received 1x", 3027, 5);
                }
                case 1:
                {
                    Inventory_Add(playerid, "Heroin", 1579);
                    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membuat Heroin");
                    ShowItemBox(playerid, "Heroin", "Received 1x", 1579, 5);
                }
                case 2:
                {
                    Inventory_Add(playerid, "Anggur Merah", 1579);
                    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membuat Anggur Merah");
                    ShowItemBox(playerid, "Anggur Merah", "Received 1x", 1579, 5);
                }
                case 3:
                {
                    Inventory_Add(playerid, "Tuak", 1579);
                    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membuat Tuak");
                    ShowItemBox(playerid, "Tuak", "Received 1x", 1579, 5);
                }
            }
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;
            
            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/16;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pConsfMeatTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pConsfMeatTimer[playerid] = false;

            DeerData[AccountData[playerid][pDuringConsficatingMeat]][deerGoingConsf] = false;
            return 0;
        }

        if(AccountData[playerid][pDuringConsficatingMeat] == -1)
        {
            pConsfMeatTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;
            DeerData[AccountData[playerid][pDuringConsficatingMeat]][deerGoingConsf] = false;
            AccountData[playerid][pDuringConsficatingMeat] = -1;
            return 0;
        }

        if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        {
            pConsfMeatTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;
            DeerData[AccountData[playerid][pDuringConsficatingMeat]][deerGoingConsf] = false;
            AccountData[playerid][pDuringConsficatingMeat] = -1;
            return 0;
        }

        if(!IsPlayerInRangeOfPoint(playerid, 3.0, DeerData[AccountData[playerid][pDuringConsficatingMeat]][deerPos][0], DeerData[AccountData[playerid][pDuringConsficatingMeat]][deerPos][1], DeerData[AccountData[playerid][pDuringConsficatingMeat]][deerPos][2]))
        {
            pConsfMeatTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;
            DeerData[AccountData[playerid][pDuringConsficatingMeat]][deerGoingConsf] = false;
            AccountData[playerid][pDuringConsficatingMeat] = -1;
            return 0;
        }

        if(!DeerData[AccountData[playerid][pDuringConsficatingMeat]][deerShoted])
        {
            pConsfMeatTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;
            DeerData[AccountData[playerid][pDuringConsficatingMeat]][deerGoingConsf] = false;
            AccountData[playerid][pDuringConsficatingMeat] = -1;
            return 0;
        }

        if(DeerData[AccountData[playerid][pDuringConsficatingMeat]][deerConsficated])
        {
            pConsfMeatTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;
            DeerData[AccountData[playerid][pDuringConsficatingMeat]][deerGoingConsf] = false;
            AccountData[playerid][pDuringConsficatingMeat] = -1;
            return 0;
        }

        if(!IsPlayerInDynamicArea(playerid, HuntingZone))
        {
            pConsfMeatTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;
            DeerData[AccountData[playerid][pDuringConsficatingMeat]][deerGoingConsf] = false;
            AccountData[playerid][pDuringConsficatingMeat] = -1;
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pConsfMeatTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;
            DeerData[AccountData[playerid][pDuringConsficatingMeat]][deerGoingConsf] = false;
            AccountData[playerid][pDuringConsficatingMeat] = -1;

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 6)
        {
            pConsfMeatTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;

            DeerData[AccountData[playerid][pDuringConsficatingMeat]][deerGoingConsf] = false;
            DeerData[AccountData[playerid][pDuringConsficatingMeat]][deerRespawnTime] = 100;
            DeerData[AccountData[playerid][pDuringConsficatingMeat]][deerConsficated] = true;

            if(DestroyDynamicObject(DeerData[AccountData[playerid][pDuringConsficatingMeat]][deerObject]))
                DeerData[AccountData[playerid][pDuringConsficatingMeat]][deerObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
            
            new prms[525];
            format(prms, sizeof(prms), "Rusa\n"RED"Tidak Tersedia\n"WHITE"%02d:%02d", DeerData[AccountData[playerid][pDuringConsficatingMeat]][deerRespawnTime]/60%60, DeerData[AccountData[playerid][pDuringConsficatingMeat]][deerRespawnTime]%3600%60);
            UpdateDynamic3DTextLabelText(DeerData[AccountData[playerid][pDuringConsficatingMeat]][deerLabel], 0xFFFFFFBF, prms);

            AccountData[playerid][pThirst]--;
            AccountData[playerid][pHunger]--;
            AccountData[playerid][pStress] -= 2;

            new randevent = Random(100);
            switch(randevent)
            {
                case 0.. 69: //daging
                {
                    Inventory_Add(playerid, "Daging", 2806);
                    ShowItemBox(playerid, "Daging", "Received 1x", 2806, 5);
                }
                case 70..90: //kulit
                {
                    Inventory_Add(playerid, "Kulit", 1828);
                    ShowItemBox(playerid, "Kulit", "Received 1x", 1828, 5);
                }
                case 91.. 99: //tanduk
                {
                    Inventory_Add(playerid, "Tanduk", 19314);
                    ShowItemBox(playerid, "Tanduk", "Received 1x", 19314, 5);
                }
            }

            AccountData[playerid][pDuringConsficatingMeat] = -1;
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/6;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }
    return 1;
}

ptask UpdateTimeActivity2[1000](playerid)
{
    if(pCarstealPartTimer[playerid])
    {
        if(!IsPlayerConnected(playerid))
        {
            pCarstealPartTimer[playerid] = false;
            return 0;
        }

        if(!AccountData[playerid][pDuringCarsteal])
        {
            pCarstealPartTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            return 0;
        }
        
        if(g_CarstealStepPart[playerid] == 0)
        {
            pCarstealPartTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            return 0;
        }

        if(!IsPlayerInRangeOfPoint(playerid, 5.0, g_CarstealVehX, g_CarstealVehY, g_CarstealVehZ))
        {
            pCarstealPartTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            return 0;
        }

        if(!IsValidVehicle(g_CarstealCarPhysic[playerid]))
        {
            pCarstealPartTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            return 0;
        }

        if(Inventory_Count(playerid, "Linggis") < 1)
        {
            pCarstealPartTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            return 0;
        }

        if(Inventory_Count(playerid, "Kunci T") < 1)
        {
            pCarstealPartTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 11)
        {
            pCarstealPartTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            
            AccountData[playerid][pCarstealHoldingPart] = true;

            switch(g_CarstealStepPart[playerid])
            {
                case 1: //ban
                {
                    SetPlayerAttachedObject(playerid, 9, 1096, 6, 0.046000, 0.183000, -0.197999, 0.000000, -4.899998, 10.800001, 0.703000, 0.579000, 0.548999);
                    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);

                    AccountData[playerid][pCarstealStoringCP] =  CreateDynamicCP(965.3608,2083.1655,10.8203, 2.0, 0, 0, playerid, 250.0, -1, 0);
                }
                case 2: //bumper belakang
                {
                    SetPlayerAttachedObject(playerid, 9, 1159, 6, 0.423999, 0.407999, -1.410999, -31.499994, 80.799987, 12.599996, 1.000000, 1.000000, 1.000000);
                    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);

                    AccountData[playerid][pCarstealStoringCP] =  CreateDynamicCP(968.9711,2063.0598,10.8203, 2.0, 0, 0, playerid, 250.0, -1, 0);
                }
                case 3: //bumper depan
                {
                    SetPlayerAttachedObject(playerid, 9, 1185, 6, 0.268999, -0.135999, -1.133999, 0.000000, 84.800003, -15.300001, 1.000000, 1.000000, 1.000000);
                    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);

                    AccountData[playerid][pCarstealStoringCP] =  CreateDynamicCP(944.8134,2059.6748,10.8203, 2.0, 0, 0, playerid, 250.0, -1, 0);
                }
                case 4: //pintu
                {
                    SetPlayerAttachedObject(playerid, 9, 1271, 5, 0.094000, 0.164999, 0.164000, 6.700001, 15.199984, 8.599995, 0.592999, 0.513999, 0.592000);
                    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);

                    AccountData[playerid][pCarstealStoringCP] =  CreateDynamicCP(956.9954,2082.8633,10.8203, 2.0, 0, 0, playerid, 250.0, -1, 0);
                }
            }
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/11;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pSellingMarijuanaTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pSellingMarijuanaTimer[playerid] = false;
            return 0;
        }

        if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        {
            pSellingMarijuanaTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;
            return 0;
        }

        if(!IsPlayerInRangeOfPoint(playerid, 3.0, g_DrugsSellActorPos[pDrugSellChosen[playerid]][0], g_DrugsSellActorPos[pDrugSellChosen[playerid]][1], g_DrugsSellActorPos[pDrugSellChosen[playerid]][2]))
        {
            pSellingMarijuanaTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;
            return 0;
        }

        if(!PlayerHasItem(playerid, "Marijuana"))
        {
            pSellingMarijuanaTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;

            if(DestroyDynamicActor(pDrugSellActor[playerid]))
				pDrugSellActor[playerid] = STREAMER_TAG_ACTOR: INVALID_STREAMER_ID;

			if(DestroyDynamicMapIcon(pDrugSellIcon[playerid]))
				pDrugSellIcon[playerid] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;

			if(DestroyDynamic3DTextLabel(pDrugSellLabel[playerid]))
				pDrugSellLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

            pDrugSellChosen[playerid] = -1;
            pDrugSellStep[playerid] = 0;   
            
            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Marijuana untuk dijual!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 4)
        {
            pSellingMarijuanaTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            Inventory_Remove(playerid, "Marijuana");
            ShowItemBox(playerid, "Marijuana", "Removed 1x", 1578, 4);
            ShowItemBox(playerid, "Dirty Money", "Received $150x", 1550, 5);

            GivePlayerDirtyMoney(playerid, 150);

            if(DestroyDynamicActor(pDrugSellActor[playerid]))
				pDrugSellActor[playerid] = STREAMER_TAG_ACTOR: INVALID_STREAMER_ID;

			if(DestroyDynamicMapIcon(pDrugSellIcon[playerid]))
				pDrugSellIcon[playerid] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;

			if(DestroyDynamic3DTextLabel(pDrugSellLabel[playerid]))
				pDrugSellLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

			pDrugSellStep[playerid]++;

            if(pDrugSellStep[playerid] >= 11)
            {
                pDrugSellChosen[playerid] = -1;
                pDrugSellStep[playerid] = 0;   

                ShowTDN(playerid, NOTIFICATION_WARNING, "Anda telah menyelesaikan penjualan, kembalilah untuk melanjutkan!");
            }
            else
            {
                new randskin = RandomEx(1, 311);
                pDrugSellChosen[playerid] = random(sizeof(g_DrugsSellActorPos));
			    pDrugSellActor[playerid] = CreateDynamicActor(randskin, g_DrugsSellActorPos[pDrugSellChosen[playerid]][0], g_DrugsSellActorPos[pDrugSellChosen[playerid]][1], g_DrugsSellActorPos[pDrugSellChosen[playerid]][2], g_DrugsSellActorPos[pDrugSellChosen[playerid]][3], 1, 100.0, 0, 0, -1, 300.00, -1, 0);
			    pDrugSellIcon[playerid] = CreateDynamicMapIcon(g_DrugsSellActorPos[pDrugSellChosen[playerid]][0], g_DrugsSellActorPos[pDrugSellChosen[playerid]][1], g_DrugsSellActorPos[pDrugSellChosen[playerid]][2], 23, -1, 0, 0, playerid, 155.55, MAPICON_LOCAL, -1, 0);
			    pDrugSellLabel[playerid] = CreateDynamic3DTextLabel("[Y] "WHITE"Jual", Y_PAHLAWAN, g_DrugsSellActorPos[pDrugSellChosen[playerid]][0], g_DrugsSellActorPos[pDrugSellChosen[playerid]][1], g_DrugsSellActorPos[pDrugSellChosen[playerid]][2]+0.85, 30.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, playerid, 30.00, -1, 0);
            }
        }
        else
        {
            AccountData[playerid][pActivityTime]++;
            
            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/4;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pMoneyLaundryTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pMoneyLaundryTimer[playerid] = false;
            return 0;
        }

        if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        {
            pMoneyLaundryTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;
            return 0;
        }

        if(!IsPlayerInRangeOfPoint(playerid, 5.5, 1477.2319,-31.4594,9.0832))
        {
            pMoneyLaundryTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 21)
        {
            pMoneyLaundryTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowItemBox(playerid, "Dirty Money", sprintf("Removed $%sx", FormatMoney(TempMoneyLaundry[playerid])), 1550, 4);
            ShowItemBox(playerid, "Cash", sprintf("Received $%sx", FormatMoney(floatround(TempMoneyLaundryR[playerid]))), 1212, 5);

            TakePlayerDirtyMoney(playerid, TempMoneyLaundry[playerid]);
            GivePlayerMoneyEx(playerid, floatround(TempMoneyLaundryR[playerid]));
        }
        else
        {
            AccountData[playerid][pActivityTime]++;
            
            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/21;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pRefuelingTimer[playerid])
    {
        new pumpid = AccountData[playerid][pInGas];
        new vid = AccountData[playerid][pTempVehID];

        if(!IsPlayerConnected(playerid)) 
        {
            pRefuelingTimer[playerid] = false;

            AccountData[playerid][pDuringRefueling] = false;
            StopRunningAnimation(playerid);

            TakePlayerMoneyEx(playerid, AccountData[playerid][pRefuelingPrice]);
            AccountData[playerid][pRefuelingPrice] = 0;

            UpdateDynamic3DTextLabelText(g_GasPumpLabel[playerid][pumpid], Y_WHITE, "Tekan "GREEN"Y "WHITE"untuk mengisi bbm");

            if(DestroyDynamic3DTextLabel(g_GasProgressLabel[playerid]))
                g_GasProgressLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

            AccountData[playerid][pInGas] = -1;
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }
        if(!AccountData[playerid][pDuringRefueling])
        {
            pRefuelingTimer[playerid] = false;

            AccountData[playerid][pDuringRefueling] = false;
            StopRunningAnimation(playerid);

            TakePlayerMoneyEx(playerid, AccountData[playerid][pRefuelingPrice]);
            ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(AccountData[playerid][pRefuelingPrice])), 1212, 5);

            AccountData[playerid][pRefuelingPrice] = 0;

            UpdateDynamic3DTextLabelText(g_GasPumpLabel[playerid][pumpid], Y_WHITE, "Tekan "GREEN"Y "WHITE"untuk mengisi bbm");

            if(DestroyDynamic3DTextLabel(g_GasProgressLabel[playerid]))
                g_GasProgressLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
            
            AccountData[playerid][pInGas] = -1;
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }
        if(!IsPlayerInRangeOfPoint(playerid, 1.0, __g_GasPumpLoc[pumpid][0], __g_GasPumpLoc[pumpid][1], __g_GasPumpLoc[pumpid][2]))
        {
            pRefuelingTimer[playerid] = false;

            AccountData[playerid][pDuringRefueling] = false;
            StopRunningAnimation(playerid);

            TakePlayerMoneyEx(playerid, AccountData[playerid][pRefuelingPrice]);
            ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(AccountData[playerid][pRefuelingPrice])), 1212, 5);
            AccountData[playerid][pRefuelingPrice] = 0;

            UpdateDynamic3DTextLabelText(g_GasPumpLabel[playerid][pumpid], Y_WHITE, "Tekan "GREEN"Y "WHITE"untuk mengisi bbm");

            if(DestroyDynamic3DTextLabel(g_GasProgressLabel[playerid]))
                g_GasProgressLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
            
            AccountData[playerid][pInGas] = -1;
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }
        if(!IsValidVehicle(vid))
        {
            pRefuelingTimer[playerid] = false;

            AccountData[playerid][pDuringRefueling] = false;
            StopRunningAnimation(playerid);

            TakePlayerMoneyEx(playerid, AccountData[playerid][pRefuelingPrice]);
            ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(AccountData[playerid][pRefuelingPrice])), 1212, 5);
            AccountData[playerid][pRefuelingPrice] = 0;

            UpdateDynamic3DTextLabelText(g_GasPumpLabel[playerid][pumpid], Y_WHITE, "Tekan "GREEN"Y "WHITE"untuk mengisi bbm");

            if(DestroyDynamic3DTextLabel(g_GasProgressLabel[playerid]))
                g_GasProgressLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
            
            AccountData[playerid][pInGas] = -1;
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }
        if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        {
            pRefuelingTimer[playerid] = false;

            AccountData[playerid][pDuringRefueling] = false;
            StopRunningAnimation(playerid);

            TakePlayerMoneyEx(playerid, AccountData[playerid][pRefuelingPrice]);
            ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(AccountData[playerid][pRefuelingPrice])), 1212, 5);
            AccountData[playerid][pRefuelingPrice] = 0;

            UpdateDynamic3DTextLabelText(g_GasPumpLabel[playerid][pumpid], Y_WHITE, "Tekan "GREEN"Y "WHITE"untuk mengisi bbm");

            if(DestroyDynamic3DTextLabel(g_GasProgressLabel[playerid]))
                g_GasProgressLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
            
            AccountData[playerid][pInGas] = -1;
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }
        static Float:vX, Float:vY, Float:vZ, gplstr[128];
        GetVehiclePos(vid, vX, vY, vZ);
        if(!IsPlayerInRangeOfPoint(playerid, 3.5, vX, vY, vZ))
        {
            pRefuelingTimer[playerid] = false;

            AccountData[playerid][pDuringRefueling] = false;
            StopRunningAnimation(playerid);

            TakePlayerMoneyEx(playerid, AccountData[playerid][pRefuelingPrice]);
            ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(AccountData[playerid][pRefuelingPrice])), 1212, 5);
            AccountData[playerid][pRefuelingPrice] = 0;

            UpdateDynamic3DTextLabelText(g_GasPumpLabel[playerid][pumpid], Y_WHITE, "Tekan "GREEN"Y "WHITE"untuk mengisi bbm");

            if(DestroyDynamic3DTextLabel(g_GasProgressLabel[playerid]))
                g_GasProgressLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
            
            AccountData[playerid][pInGas] = -1;
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }

        if(VehicleCore[vid][vCoreFuel] >= 100)
        {
            pRefuelingTimer[playerid] = false;

            AccountData[playerid][pDuringRefueling] = false;
            StopRunningAnimation(playerid);

            VehicleCore[vid][vCoreFuel] = 100;
            TakePlayerMoneyEx(playerid, AccountData[playerid][pRefuelingPrice]+20);
            ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(AccountData[playerid][pRefuelingPrice]+20)), 1212, 5);
            ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Anda membayar ~r~$%s + pajak $20.00 ~l~untuk isi bahan bakar", FormatMoney(AccountData[playerid][pRefuelingPrice])));
            AccountData[playerid][pRefuelingPrice] = 0;

            UpdateDynamic3DTextLabelText(g_GasPumpLabel[playerid][pumpid], Y_WHITE, "Tekan "GREEN"Y "WHITE"untuk mengisi bbm");

            if(DestroyDynamic3DTextLabel(g_GasProgressLabel[playerid]))
                g_GasProgressLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
            PlayerPlaySound(playerid, 4201, 0.0, 0.0, 0.0);
        
            AccountData[playerid][pInGas] = -1;
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
        }
        else
        {
            if(AccountData[playerid][pMoney] < AccountData[playerid][pRefuelingPrice]) 
            {
                pRefuelingTimer[playerid] = false;

                AccountData[playerid][pDuringRefueling] = false;
                StopRunningAnimation(playerid);

                TakePlayerMoneyEx(playerid, AccountData[playerid][pRefuelingPrice]);
                ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(AccountData[playerid][pRefuelingPrice])), 1212, 5);
                AccountData[playerid][pRefuelingPrice] = 0;

                UpdateDynamic3DTextLabelText(g_GasPumpLabel[playerid][pumpid], Y_WHITE, "Tekan "GREEN"Y "WHITE"untuk mengisi bbm");

                if(DestroyDynamic3DTextLabel(g_GasProgressLabel[playerid]))
                    g_GasProgressLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

                ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

                AccountData[playerid][pInGas] = -1;
                AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
                return 0;
            }

            VehicleCore[vid][vCoreFuel] += 2;
            AccountData[playerid][pRefuelingPrice] += 14;

            format(gplstr, sizeof(gplstr), "Tekan "GREEN"Y "WHITE"untuk membatalkan mengisi bbm\nHarga: "DARKGREEN"$%s", FormatMoney(AccountData[playerid][pRefuelingPrice]));
            UpdateDynamic3DTextLabelText(g_GasPumpLabel[playerid][pumpid], Y_WHITE, gplstr);

            format(gplstr, sizeof(gplstr), "%d persen", VehicleCore[vid][vCoreFuel]);
            UpdateDynamic3DTextLabelText(g_GasProgressLabel[playerid], Y_WHITE, gplstr);
            PlayerPlaySound(playerid, 4202, 0.0, 0.0, 0.0);
        }
    }

    if(pRefuelJerrycanTimer[playerid])
    {
        new vid = AccountData[playerid][pTempVehID];

        if(!IsPlayerConnected(playerid)) 
        {
            pRefuelJerrycanTimer[playerid] = false;

            AccountData[playerid][pDuringRefueling] = false;
            AccountData[playerid][pHoldingFuelCan] = false;
            StopRunningAnimation(playerid);

            RemovePlayerAttachedObject(playerid, 9);

            if(DestroyDynamic3DTextLabel(g_GasProgressLabel[playerid]))
                g_GasProgressLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }
        if(!AccountData[playerid][pDuringRefueling])
        {
            pRefuelJerrycanTimer[playerid] = false;

            AccountData[playerid][pDuringRefueling] = false;
            AccountData[playerid][pHoldingFuelCan] = false;
            StopRunningAnimation(playerid);

            RemovePlayerAttachedObject(playerid, 9);

            if(DestroyDynamic3DTextLabel(g_GasProgressLabel[playerid]))
                g_GasProgressLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }
        if(!PlayerHasItem(playerid, "Jerigen") && !AccountData[playerid][pHoldingFuelCan])
        {
            pRefuelJerrycanTimer[playerid] = false;

            AccountData[playerid][pDuringRefueling] = false;
            AccountData[playerid][pHoldingFuelCan] = false;
            StopRunningAnimation(playerid);

            RemovePlayerAttachedObject(playerid, 9);

            if(DestroyDynamic3DTextLabel(g_GasProgressLabel[playerid]))
                g_GasProgressLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
            
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }
        if(!IsValidVehicle(vid))
        {
            pRefuelJerrycanTimer[playerid] = false;

            AccountData[playerid][pDuringRefueling] = false;
            AccountData[playerid][pHoldingFuelCan] = false;
            StopRunningAnimation(playerid);

            RemovePlayerAttachedObject(playerid, 9);

            if(DestroyDynamic3DTextLabel(g_GasProgressLabel[playerid]))
                g_GasProgressLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }
        if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        {
            pRefuelJerrycanTimer[playerid] = false;

            AccountData[playerid][pDuringRefueling] = false;
            AccountData[playerid][pHoldingFuelCan] = false;
            StopRunningAnimation(playerid);

            RemovePlayerAttachedObject(playerid, 9);
            
            if(DestroyDynamic3DTextLabel(g_GasProgressLabel[playerid]))
                g_GasProgressLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }

        static Float:vX, Float:vY, Float:vZ, gplstr[128];
        GetVehiclePos(vid, vX, vY, vZ);
        if(!IsPlayerInRangeOfPoint(playerid, 3.5, vX, vY, vZ))
        {
            pRefuelJerrycanTimer[playerid] = false;

            AccountData[playerid][pDuringRefueling] = false;
            AccountData[playerid][pHoldingFuelCan] = false;
            StopRunningAnimation(playerid);

            RemovePlayerAttachedObject(playerid, 9);

            if(DestroyDynamic3DTextLabel(g_GasProgressLabel[playerid]))
                g_GasProgressLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }

        if(VehicleCore[vid][vCoreFuel] >= 100)
        {
            pRefuelJerrycanTimer[playerid] = false;

            AccountData[playerid][pDuringRefueling] = false;
            AccountData[playerid][pHoldingFuelCan] = false;
            StopRunningAnimation(playerid);

            VehicleCore[vid][vCoreFuel] = 100;

            RemovePlayerAttachedObject(playerid, 9);

            if(DestroyDynamic3DTextLabel(g_GasProgressLabel[playerid]))
                g_GasProgressLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
        }
        else
        {
            VehicleCore[vid][vCoreFuel]++;
            format(gplstr, sizeof(gplstr), "%d persen", VehicleCore[vid][vCoreFuel]);

            if(!IsValidDynamic3DTextLabel(g_GasProgressLabel[playerid]))
                g_GasProgressLabel[playerid] = CreateDynamic3DTextLabel("Tekan "GREEN"Y "WHITE"untuk mengisi bbm", Y_WHITE, 0.0, 0.0, 1.10, 5.0, INVALID_PLAYER_ID, vid, 0, 0, 0, playerid, 5.0, -1, 0);
            
            UpdateDynamic3DTextLabelText(g_GasProgressLabel[playerid], Y_WHITE, gplstr);
        }
    }
    return 1;
}

ptask UpdateTimeOtherFunc[1000](playerid)
{
    if(pRebootingPhoneTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pRebootingPhoneTimer[playerid] = false;
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 16)
        {
            PlayerPhoneData[playerid][phoneOn] = true;
            pRebootingPhoneTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HidePhoneRebootTD(playerid);
            ShowPhoneLockScreenTD(playerid);
            ShowTDN(playerid, NOTIFICATION_INFO, "Smartphone anda telah dihidupkan.");

            if(IsPlayerAttachedObjectSlotUsed(playerid, 9))
                RemovePlayerAttachedObject(playerid, 9);

            if(!IsPlayerInAnyVehicle(playerid))
			{
                ApplyAnimation(playerid, "ped","Jetpack_Idle", 4.1, false, false, false, true, 0, true);
                SetPlayerAttachedObject(playerid, 9, 18869, 5, 0.043000, 0.022999, -0.006000, -112.000022, -34.900020, -8.500002, 1.000000, 1.000000, 1.000000);
            }
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 50.0/16;
            PlayerTextDrawTextSize(playerid, PhoneRebootBar[playerid], progressvalue, 3.0);
            PlayerTextDrawShow(playerid, PhoneRebootBar[playerid]);
        }
    }
    
    if(pCookingTimer[playerid])
    {
        if(!IsPlayerConnected(playerid))
        {
            pCookingTimer[playerid] = false;
            return 0;
        }

        if(Inventory_Count(playerid, "Kentang Potong") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Kentang Potong! (Min: 5).");
            return 0;
        }

        if(Inventory_Count(playerid, "Kubis Potong") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Kubis Potong! (Min: 5).");
            return 0;
        }

        if(Inventory_Count(playerid, "Bawang Potong") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Bawang Potong! (Min: 5).");
            return 0;
        }

        if(Inventory_Count(playerid, "Tomat Potong") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Tomat Potong! (Min: 5).");
            return 0;
        }

        if(Inventory_Count(playerid, "Air") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Air! (Min: 5).");
            return 0;
        }

        if(Inventory_Count(playerid, "Gula") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Gula! (Min: 5).");
            return 0;
        }

        if(Inventory_Count(playerid, "Micin") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Micin! (Min: 5).");
            return 0;
        }

        if(Inventory_Count(playerid, "Ayam Kemas") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Ayam Kemas! (Min: 5).");
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            pCookingTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 11)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            
            AccountData[playerid][pActivityTime] = 0;
            pCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            Inventory_Remove(playerid, "Kentang Potong", 5);
            Inventory_Remove(playerid, "Kubis Potong", 5);
            Inventory_Remove(playerid, "Bawang Potong", 5);
            Inventory_Remove(playerid, "Tomat Potong", 5);
            Inventory_Remove(playerid, "Air", 5);
            Inventory_Remove(playerid, "Gula", 5);
            Inventory_Remove(playerid, "Micin", 5);
            Inventory_Remove(playerid, "Ayam Kemas", 5);

            ShowItemBox(playerid, "Kentang Potong", "Removed 5x", 19574, 4);
            ShowItemBox(playerid, "Kubis Potong", "Removed 5x", 19576, 5);
            ShowItemBox(playerid, "Bawang Potong", "Removed 5x", 19575, 6);
            ShowItemBox(playerid, "Tomat Potong", "Removed 5x", 19577, 7);
            ShowItemBox(playerid, "Air", "Removed 5x", 19570, 8);
            ShowItemBox(playerid, "Gula", "Removed 5x", 1279, 9);
            ShowItemBox(playerid, "Micin", "Removed 5x", 19573, 10);
            ShowItemBox(playerid, "Ayam Kemas", "Removed 5x", 2768, 11);
            
            switch(AccountData[playerid][pTempValue2])
            {
                case 0:
                {
                    Inventory_Add(playerid, "BBQ Delicy", 2663);
                    ShowItemBox(playerid, "BBQ Delicy", "Received 1x", 2663, 12);
                }
                case 1:
                {
                    Inventory_Add(playerid, "Rice Combo", 2663);
                    ShowItemBox(playerid, "Rice Combo", "Received 1x", 2663, 12);
                }
            }
            AccountData[playerid][pTempValue2] = -1;
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/11;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pCookingHouseTimer[playerid])
    {
        if(!IsPlayerConnected(playerid))
        {
            pCookingHouseTimer[playerid] = false;
            return 0;
        }

        if(Inventory_Count(playerid, "Kentang") < 3)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pCookingHouseTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Kentang! (Min: 3).");
            return 0;
        }

        if(Inventory_Count(playerid, "Cabai") < 3)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pCookingHouseTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Cabai! (Min: 3).");
            return 0;
        }

        if(Inventory_Count(playerid, "Bawang") < 3)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pCookingHouseTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Bawang! (Min: 3).");
            return 0;
        }

        if(Inventory_Count(playerid, "Tomat") < 3)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pCookingHouseTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Tomat! (Min: 3).");
            return 0;
        }

        if(Inventory_Count(playerid, "Air") < 3)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pCookingHouseTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Air! (Min: 3).");
            return 0;
        }

        if(Inventory_Count(playerid, "Gula") < 3)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pCookingHouseTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Gula! (Min: 3).");
            return 0;
        }

        if(Inventory_Count(playerid, "Micin") < 3)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pCookingHouseTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Micin! (Min: 3).");
            return 0;
        }

        if(Inventory_Count(playerid, "Ayam Kemas") < 3)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pCookingHouseTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Ayam Kemas! (Min: 3).");
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            pCookingHouseTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 11)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            
            AccountData[playerid][pActivityTime] = 0;
            pCookingHouseTimer[playerid] = false;
            HideProgressBar(playerid);

            Inventory_Remove(playerid, "Kentang", 3);
            Inventory_Remove(playerid, "Cabai", 3);
            Inventory_Remove(playerid, "Bawang", 3);
            Inventory_Remove(playerid, "Tomat", 3);
            Inventory_Remove(playerid, "Air", 3);
            Inventory_Remove(playerid, "Gula", 3);
            Inventory_Remove(playerid, "Micin", 3);
            Inventory_Remove(playerid, "Ayam Kemas", 3);

            ShowItemBox(playerid, "Kentang", "Removed 3x", 19638, 4);
            ShowItemBox(playerid, "Cabai", "Removed 3x", 2253, 5);
            ShowItemBox(playerid, "Bawang", "Removed 3x", 19636, 6);
            ShowItemBox(playerid, "Tomat", "Removed 3x", 19636, 7);
            ShowItemBox(playerid, "Air", "Removed 3x", 19570, 8);
            ShowItemBox(playerid, "Gula", "Removed 3x", 1279, 9);
            ShowItemBox(playerid, "Micin", "Removed 3x", 19573, 10);
            ShowItemBox(playerid, "Ayam Kemas", "Removed 3x", 2768, 11);
            
            switch(AccountData[playerid][pTempValue2])
            {
                case 0:
                {
                    Inventory_Add(playerid, "Gulai Ayam", 2355, 5);
                    ShowItemBox(playerid, "Gulai Ayam", "Received 5x", 2355, 12);
                }
                case 1:
                {
                    Inventory_Add(playerid, "Es Lilin", 19565, 5);
                    ShowItemBox(playerid, "Es Lilin", "Received 5x", 19565, 12);
                }
            }
            AccountData[playerid][pTempValue2] = -1;
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/11;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pHCraftBandageTimer[playerid])
    {
        if(!IsPlayerConnected(playerid))
        {
            pHCraftBandageTimer[playerid] = false;
            return 0;
        }

        if(Inventory_Count(playerid, "Karet") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pHCraftBandageTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Karet! (Min: 5).");
            return 0;
        }

        if(Inventory_Count(playerid, "Plastik") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pHCraftBandageTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Plastik! (Min: 5).");
            return 0;
        }

        if(Inventory_Count(playerid, "Kertas") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pHCraftBandageTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Kertas! (Min: 5).");
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            pHCraftBandageTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 11)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            
            AccountData[playerid][pActivityTime] = 0;
            pHCraftBandageTimer[playerid] = false;
            HideProgressBar(playerid);

            Inventory_Remove(playerid, "Karet", 5);
            Inventory_Remove(playerid, "Plastik", 5);
            Inventory_Remove(playerid, "Kertas", 5);

            ShowItemBox(playerid, "Karet", "Removed 5x", 1316, 4);
            ShowItemBox(playerid, "Plastik", "Removed 5x", 1265, 5);
            ShowItemBox(playerid, "Kertas", "Removed 5x", 19873, 6);
            
            Inventory_Add(playerid, "Perban", 11736);
            ShowItemBox(playerid, "Perban", "Received 5x", 11736, 12);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/11;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pFactionCraftingTimer[playerid])
    {
        if(!IsPlayerConnected(playerid))
        {
            pFactionCraftingTimer[playerid] = false;
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            pFactionCraftingTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 11)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            
            AccountData[playerid][pActivityTime] = 0;
            pFactionCraftingTimer[playerid] = false;
            HideProgressBar(playerid);

            switch(AccountData[playerid][pTempValue2])
            {
                case 0:
                {
                    Inventory_Add(playerid, "Part Mesin", 19917);
                    ShowItemBox(playerid, "Part Mesin", "Received 1x", 19917, 11);
                }
                case 1:
                {
                    Inventory_Add(playerid, "Part Body", 1141);
                    ShowItemBox(playerid, "Part Body", "Received 1x", 1141, 11);
                }
                case 2:
                {
                    Inventory_Add(playerid, "Ban Baru", 1083);
                    ShowItemBox(playerid, "Ban Baru", "Received 1x", 1083, 11);
                }
                case 3:
                {
                    Inventory_Add(playerid, "Air Brush", 2752);
                    ShowItemBox(playerid, "Air Brush", "Received 1x", 2752, 11);
                }
                case 4:
                {
                    Inventory_Add(playerid, "Toolkit", 19921);
                    ShowItemBox(playerid, "Toolkit", "Received 1x", 19921, 11);
                }
            }
            AccountData[playerid][pTempValue2] = -1;
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/11;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pDNRCookingTimer[playerid])
    {
        if(!IsPlayerConnected(playerid))
        {
            pDNRCookingTimer[playerid] = false;
            return 0;
        }

        if(Inventory_Count(playerid, "Kentang Potong") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pDNRCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Kentang Potong! (Min: 5).");
            return 0;
        }

        if(Inventory_Count(playerid, "Kubis Potong") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pDNRCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Kubis Potong! (Min: 5).");
            return 0;
        }

        if(Inventory_Count(playerid, "Bawang Potong") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pDNRCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Bawang Potong! (Min: 5).");
            return 0;
        }

        if(Inventory_Count(playerid, "Tomat Potong") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pDNRCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Tomat Potong! (Min: 5).");
            return 0;
        }

        if(Inventory_Count(playerid, "Air") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pDNRCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Air! (Min: 5).");
            return 0;
        }

        if(Inventory_Count(playerid, "Gula") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pDNRCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Gula! (Min: 5).");
            return 0;
        }

        if(Inventory_Count(playerid, "Micin") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pDNRCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Micin! (Min: 5).");
            return 0;
        }

        if(Inventory_Count(playerid, "Ayam Kemas") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pDNRCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Ayam Kemas! (Min: 5).");
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            pDNRCookingTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 11)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            
            AccountData[playerid][pActivityTime] = 0;
            pDNRCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            Inventory_Remove(playerid, "Kentang Potong", 5);
            Inventory_Remove(playerid, "Kubis Potong", 5);
            Inventory_Remove(playerid, "Bawang Potong", 5);
            Inventory_Remove(playerid, "Tomat Potong", 5);
            Inventory_Remove(playerid, "Air", 5);
            Inventory_Remove(playerid, "Gula", 5);
            Inventory_Remove(playerid, "Micin", 5);
            Inventory_Remove(playerid, "Ayam Kemas", 5);

            ShowItemBox(playerid, "Kentang Potong", "Removed 5x", 19574, 4);
            ShowItemBox(playerid, "Kubis Potong", "Removed 5x", 19576, 5);
            ShowItemBox(playerid, "Bawang Potong", "Removed 5x", 19575, 6);
            ShowItemBox(playerid, "Tomat Potong", "Removed 5x", 19577, 7);
            ShowItemBox(playerid, "Air", "Removed 5x", 19570, 8);
            ShowItemBox(playerid, "Gula", "Removed 5x", 1279, 9);
            ShowItemBox(playerid, "Micin", "Removed 5x", 19573, 10);
            ShowItemBox(playerid, "Ayam Kemas", "Removed 5x", 2768, 11);
            
            switch(AccountData[playerid][pTempValue2])
            {
                case 0:
                {
                    Inventory_Add(playerid, "Buckshot Special", 2663);
                    ShowItemBox(playerid, "Buckshot Special", "Received 1x", 2663, 11);
                }
                case 1:
                {
                    Inventory_Add(playerid, "Frenchy Velty", 2663);
                    ShowItemBox(playerid, "Frenchy Velty", "Received 1x", 2663, 11);
                }
            }
            AccountData[playerid][pTempValue2] = -1;
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/11;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pSriMersingCookingTimer[playerid])
    {
        if(!IsPlayerConnected(playerid))
        {
            pSriMersingCookingTimer[playerid] = false;
            return 0;
        }

        if(Inventory_Count(playerid, "Kentang Potong") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pSriMersingCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Kentang Potong! (Min: 5).");
            return 0;
        }

        if(Inventory_Count(playerid, "Kubis Potong") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pSriMersingCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Kubis Potong! (Min: 5).");
            return 0;
        }

        if(Inventory_Count(playerid, "Bawang Potong") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pSriMersingCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Bawang Potong! (Min: 5).");
            return 0;
        }

        if(Inventory_Count(playerid, "Tomat Potong") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pSriMersingCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Tomat Potong! (Min: 5).");
            return 0;
        }

        if(Inventory_Count(playerid, "Air") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pSriMersingCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Air! (Min: 5).");
            return 0;
        }

        if(Inventory_Count(playerid, "Gula") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pSriMersingCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Gula! (Min: 5).");
            return 0;
        }

        if(Inventory_Count(playerid, "Micin") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pSriMersingCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Micin! (Min: 5).");
            return 0;
        }

        if(Inventory_Count(playerid, "Ayam Kemas") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pSriMersingCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Ayam Kemas! (Min: 5).");
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            pSriMersingCookingTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 11)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            
            AccountData[playerid][pActivityTime] = 0;
            pSriMersingCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            Inventory_Remove(playerid, "Kentang Potong", 5);
            Inventory_Remove(playerid, "Kubis Potong", 5);
            Inventory_Remove(playerid, "Bawang Potong", 5);
            Inventory_Remove(playerid, "Tomat Potong", 5);
            Inventory_Remove(playerid, "Air", 5);
            Inventory_Remove(playerid, "Gula", 5);
            Inventory_Remove(playerid, "Micin", 5);
            Inventory_Remove(playerid, "Ayam Kemas", 5);

            ShowItemBox(playerid, "Kentang Potong", "Removed 5x", 19574, 4);
            ShowItemBox(playerid, "Kubis Potong", "Removed 5x", 19576, 5);
            ShowItemBox(playerid, "Bawang Potong", "Removed 5x", 19575, 6);
            ShowItemBox(playerid, "Tomat Potong", "Removed 5x", 19577, 7);
            ShowItemBox(playerid, "Air", "Removed 5x", 19570, 8);
            ShowItemBox(playerid, "Gula", "Removed 5x", 1279, 9);
            ShowItemBox(playerid, "Micin", "Removed 5x", 19573, 10);
            ShowItemBox(playerid, "Ayam Kemas", "Removed 5x", 2768, 11);
            
            switch(AccountData[playerid][pTempValue2])
            {
                case 0:
                {
                    Inventory_Add(playerid, "Minang Combo", 2663);
                    ShowItemBox(playerid, "Minang Combo", "Received 1x", 2663, 11);
                }
                case 1:
                {
                    Inventory_Add(playerid, "Malaya Shine", 2663);
                    ShowItemBox(playerid, "Malaya Shine", "Received 1x", 2663, 11);
                }
            }
            AccountData[playerid][pTempValue2] = -1;
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/11;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pTexasCookingTimer[playerid])
    {
        if(!IsPlayerConnected(playerid))
        {
            pTexasCookingTimer[playerid] = false;
            return 0;
        }

        if(Inventory_Count(playerid, "Kentang Potong") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pTexasCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Kentang Potong! (Min: 5).");
            return 0;
        }

        if(Inventory_Count(playerid, "Kubis Potong") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pTexasCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Kubis Potong! (Min: 5).");
            return 0;
        }

        if(Inventory_Count(playerid, "Bawang Potong") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pTexasCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Bawang Potong! (Min: 5).");
            return 0;
        }

        if(Inventory_Count(playerid, "Tomat Potong") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pTexasCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Tomat Potong! (Min: 5).");
            return 0;
        }

        if(Inventory_Count(playerid, "Air") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pTexasCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Air! (Min: 5).");
            return 0;
        }

        if(Inventory_Count(playerid, "Gula") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pTexasCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Gula! (Min: 5).");
            return 0;
        }

        if(Inventory_Count(playerid, "Micin") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pTexasCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Micin! (Min: 5).");
            return 0;
        }

        if(Inventory_Count(playerid, "Ayam Kemas") < 5)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            AccountData[playerid][pActivityTime] = 0;
            pTexasCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Ayam Kemas! (Min: 5).");
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            pTexasCookingTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 11)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            
            AccountData[playerid][pActivityTime] = 0;
            pTexasCookingTimer[playerid] = false;
            HideProgressBar(playerid);

            Inventory_Remove(playerid, "Kentang Potong", 5);
            Inventory_Remove(playerid, "Kubis Potong", 5);
            Inventory_Remove(playerid, "Bawang Potong", 5);
            Inventory_Remove(playerid, "Tomat Potong", 5);
            Inventory_Remove(playerid, "Air", 5);
            Inventory_Remove(playerid, "Gula", 5);
            Inventory_Remove(playerid, "Micin", 5);
            Inventory_Remove(playerid, "Ayam Kemas", 5);

            ShowItemBox(playerid, "Kentang Potong", "Removed 5x", 19574, 4);
            ShowItemBox(playerid, "Kubis Potong", "Removed 5x", 19576, 5);
            ShowItemBox(playerid, "Bawang Potong", "Removed 5x", 19575, 6);
            ShowItemBox(playerid, "Tomat Potong", "Removed 5x", 19577, 7);
            ShowItemBox(playerid, "Air", "Removed 5x", 19570, 8);
            ShowItemBox(playerid, "Gula", "Removed 5x", 1279, 9);
            ShowItemBox(playerid, "Micin", "Removed 5x", 19573, 10);
            ShowItemBox(playerid, "Ayam Kemas", "Removed 5x", 2768, 11);
            
            switch(AccountData[playerid][pTempValue2])
            {
                case 0:
                {
                    Inventory_Add(playerid, "Fresh Solar", 2663);
                    ShowItemBox(playerid, "Fresh Solar", "Received 1x", 2663, 11);
                }
                case 1:
                {
                    Inventory_Add(playerid, "Softex Flash", 2663);
                    ShowItemBox(playerid, "Softex Flash", "Received 1x", 2663, 11);
                }
                case 2:
                {
                    Inventory_Add(playerid, "Purple Sweet", 2663);
                    ShowItemBox(playerid, "Purple Sweet", "Received 1x", 2663, 11);
                }
            }
            AccountData[playerid][pTempValue2] = -1;
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/11;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pOpenBackpackTimer[playerid])
    {
        if(!IsPlayerConnected(playerid))
        {
            pOpenBackpackTimer[playerid] = false;
            return 0;
        }

        if(!PlayerHasItem(playerid, "Ransel"))
        {
            AccountData[playerid][pActivityTime] = 0;
            pOpenBackpackTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Ransel!");
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pOpenBackpackTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 11)
        {
            AccountData[playerid][pActivityTime] = 0;
            pOpenBackpackTimer[playerid] = false;
            HideProgressBar(playerid);

            Inventory_Remove(playerid, "Ransel");
            Inventory_Add(playerid, "Chicken BBQ", 2355, 10);
            Inventory_Add(playerid, "Coconut Water", 19564, 10);
            
            ShowItemBox(playerid, "Ransel", "Removed 1x", 3026, 4);
            ShowItemBox(playerid, "Chicken BBQ", "Received 10x", 2355, 5);
            ShowItemBox(playerid, "Coconut Water", "Received 10x", 19564, 6);
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mendapatkan 10 makan dan minum.");
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/11;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pKompensasiTimer[playerid])
    {
        if(!IsPlayerConnected(playerid))
        {
            pKompensasiTimer[playerid] = false;
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pKompensasiTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 26)
        {
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;
            pKompensasiTimer[playerid] = false;
            HideProgressBar(playerid);

            Inventory_Add(playerid, "Chicken BBQ", 2355, 20);
            Inventory_Add(playerid, "Coconut Water", 19564, 20);

            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil klaim starterpack, 20x Chicken BBQ & Coconut Water.");

            new jjja[128];
            mysql_format(g_SQL, jjja, sizeof(jjja), "UPDATE `player_ucp` SET `claimedSP` = '1' WHERE `UCP` = '%e'", AccountData[playerid][pUCP]);
		    mysql_pquery(g_SQL, jjja);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/26;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pOpenShotDeluxeTimer[playerid])
    {
        if(!IsPlayerConnected(playerid))
        {
            pOpenShotDeluxeTimer[playerid] = false;
            return 0;
        }

        if(!PlayerHasItem(playerid, "BBQ Delicy"))
        {
            AccountData[playerid][pActivityTime] = 0;
            pOpenShotDeluxeTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki BBQ delicy!");
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pOpenShotDeluxeTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 11)
        {
            AccountData[playerid][pActivityTime] = 0;
            pOpenShotDeluxeTimer[playerid] = false;
            HideProgressBar(playerid);

            Inventory_Remove(playerid, "BBQ Delicy");
            Inventory_Add(playerid, "Chicken BBQ", 2355, 5);
            Inventory_Add(playerid, "Coconut Water", 19564, 5);
            ShowItemBox(playerid, "BBQ Delicy", "Removed 1x", 2663, 4);
            ShowItemBox(playerid, "Chicken BBQ", "Received 5x", 2355, 5);
            ShowItemBox(playerid, "Coconut Water", "Received 5x", 19564, 6);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/11;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pOpenBuckshotSpecialTimer[playerid])
    {
        if(!IsPlayerConnected(playerid))
        {
            pOpenBuckshotSpecialTimer[playerid] = false;
            return 0;
        }

        if(!PlayerHasItem(playerid, "Buckshot Special"))
        {
            AccountData[playerid][pActivityTime] = 0;
            pOpenBuckshotSpecialTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki buckshot special!");
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pOpenBuckshotSpecialTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 11)
        {
            AccountData[playerid][pActivityTime] = 0;
            pOpenBuckshotSpecialTimer[playerid] = false;
            HideProgressBar(playerid);

            Inventory_Remove(playerid, "Buckshot Special");
            Inventory_Add(playerid, "Donut", 2221, 5);
            Inventory_Add(playerid, "Brewed Coffee", 19835, 5);
            ShowItemBox(playerid, "Buckshot Special", "Removed 1x", 2663, 4);
            ShowItemBox(playerid, "Donut", "Received 5x", 2221, 5);
            ShowItemBox(playerid, "Brewed Coffee", "Received 5x", 19835, 6);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/11;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }
    if(pOpenMinangComboTimer[playerid])
    {
        if(!IsPlayerConnected(playerid))
        {
            pOpenMinangComboTimer[playerid] = false;
            return 0;
        }

        if(!PlayerHasItem(playerid, "Minang Combo"))
        {
            AccountData[playerid][pActivityTime] = 0;
            pOpenMinangComboTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki fresh truffle!");
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pOpenMinangComboTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 11)
        {
            AccountData[playerid][pActivityTime] = 0;
            pOpenMinangComboTimer[playerid] = false;
            HideProgressBar(playerid);

            Inventory_Remove(playerid, "Minang Combo");
            Inventory_Add(playerid, "Nasi Padang", 2219, 5);
            Inventory_Add(playerid, "Jus Timun", 1546, 5);
            ShowItemBox(playerid, "Minang Combo", "Removed 1x", 2663, 4);
            ShowItemBox(playerid, "Nasi Padang", "Received 5x", 2219, 5);
            ShowItemBox(playerid, "Jus Timun", "Received 5x", 1546, 6);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/11;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }
    if(pOpenMalayaShineTimer[playerid])
    {
        if(!IsPlayerConnected(playerid))
        {
            pOpenMalayaShineTimer[playerid] = false;
            return 0;
        }

        if(!PlayerHasItem(playerid, "Malaya Shine"))
        {
            AccountData[playerid][pActivityTime] = 0;
            pOpenMalayaShineTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki garlaxy combo!");
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pOpenMalayaShineTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 11)
        {
            AccountData[playerid][pActivityTime] = 0;
            pOpenMalayaShineTimer[playerid] = false;
            HideProgressBar(playerid);

            Inventory_Remove(playerid, "Malaya Shine");
            Inventory_Add(playerid, "Roti Jala", 2355, 5);
            Inventory_Add(playerid, "Sirup Selasih", 1544, 5);
            ShowItemBox(playerid, "Malaya Shine", "Removed 1x", 2663, 4);
            ShowItemBox(playerid, "Roti Jala", "Received 5x", 2355, 5);
            ShowItemBox(playerid, "Sirup Selasih", "Received 5x", 1544, 6);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/11;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pOpenFreshSolarTimer[playerid])
    {
        if(!IsPlayerConnected(playerid))
        {
            pOpenFreshSolarTimer[playerid] = false;
            return 0;
        }

        if(!PlayerHasItem(playerid, "Fresh Solar"))
        {
            AccountData[playerid][pActivityTime] = 0;
            pOpenFreshSolarTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki fresh solar!");
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pOpenFreshSolarTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 11)
        {
            AccountData[playerid][pActivityTime] = 0;
            pOpenFreshSolarTimer[playerid] = false;
            HideProgressBar(playerid);

            Inventory_Remove(playerid, "Fresh Solar");
            Inventory_Add(playerid, "Burger", 2880, 5);
            Inventory_Add(playerid, "Coca-Cola", 2647, 5);
            ShowItemBox(playerid, "Fresh Solar", "Removed 1x", 2663, 4);
            ShowItemBox(playerid, "Burger", "Received 5x", 2880, 5);
            ShowItemBox(playerid, "Coca-Cola", "Received 5x", 2647, 6);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/11;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pOpenSoftexFlashTimer[playerid])
    {
        if(!IsPlayerConnected(playerid))
        {
            pOpenSoftexFlashTimer[playerid] = false;
            return 0;
        }

        if(!PlayerHasItem(playerid, "Softex Flash"))
        {
            pOpenSoftexFlashTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki softex flash!");
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pOpenSoftexFlashTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 11)
        {
            pOpenSoftexFlashTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            Inventory_Remove(playerid, "Softex Flash");
            Inventory_Add(playerid, "Teriyaki", 2355, 5);
            Inventory_Add(playerid, "Rootbeer", 1546, 5);
            ShowItemBox(playerid, "Softex Flash", "Removed 1x", 2663, 4);
            ShowItemBox(playerid, "Teriyaki", "Received 5x", 2355, 5);
            ShowItemBox(playerid, "Rootbeer", "Received 5x", 1546, 6);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/11;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pOpenPurpleSweetTimer[playerid])
    {
        if(!IsPlayerConnected(playerid))
        {
            pOpenPurpleSweetTimer[playerid] = false;
            return 0;
        }

        if(!PlayerHasItem(playerid, "Purple Sweet"))
        {
            pOpenPurpleSweetTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki purple sweet!");
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pOpenPurpleSweetTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 11)
        {
            pOpenPurpleSweetTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            Inventory_Remove(playerid, "Purple Sweet");
            Inventory_Add(playerid, "Fried Chicken", 2355, 5);
            Inventory_Add(playerid, "Guinness", 1669, 5);
            ShowItemBox(playerid, "Purple Sweet", "Removed 1x", 2663, 4);
            ShowItemBox(playerid, "Fried Chicken", "Received 5x", 2355, 5);
            ShowItemBox(playerid, "Guinness", "Received 5x", 1669, 6);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/11;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pOpenTelaGoodieTimer[playerid])
    {
        if(!IsPlayerConnected(playerid))
        {
            pOpenTelaGoodieTimer[playerid] = false;
            return 0;
        }

        if(!PlayerHasItem(playerid, "Frenchy Velty"))
        {
            AccountData[playerid][pActivityTime] = 0;
            pOpenTelaGoodieTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki frenchy velty!");
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pOpenTelaGoodieTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 11)
        {
            AccountData[playerid][pActivityTime] = 0;
            pOpenTelaGoodieTimer[playerid] = false;
            HideProgressBar(playerid);

            Inventory_Remove(playerid, "Frenchy Velty");
            Inventory_Add(playerid, "French Fries", 2769, 5);
            Inventory_Add(playerid, "Red Velvet", 1546, 5);
            ShowItemBox(playerid, "Frenchy Velty", "Removed 1x", 2663, 4);
            ShowItemBox(playerid, "French Fries", "Received 5x", 2769, 5);
            ShowItemBox(playerid, "Red Velvet", "Received 5x", 1546, 6);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/11;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pOpenAndalasPrideTimer[playerid])
    {
        if(!IsPlayerConnected(playerid))
        {
            pOpenAndalasPrideTimer[playerid] = false;
            return 0;
        }

        if(!PlayerHasItem(playerid, "Rice Combo"))
        {
            AccountData[playerid][pActivityTime] = 0;
            pOpenAndalasPrideTimer[playerid] = false;
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki rice combo!");
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pOpenAndalasPrideTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 11)
        {
            AccountData[playerid][pActivityTime] = 0;
            pOpenAndalasPrideTimer[playerid] = false;
            HideProgressBar(playerid);

            Inventory_Remove(playerid, "Rice Combo");
            Inventory_Add(playerid, "Fried Rice", 2219, 5);
            Inventory_Add(playerid, "Vanilla Milkshake", 19569, 5);
            ShowItemBox(playerid, "Rice Combo", "Removed 1x", 2663, 4);
            ShowItemBox(playerid, "Fried Rice", "Received 5x", 2219, 5);
            ShowItemBox(playerid, "Vanilla Milkshake", "Received 5x", 19569, 6);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/11;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pEatingBarTimer[playerid])
    {
        if(!IsPlayerConnected(playerid))
        {
            pEatingBarTimer[playerid] = false;
            return 0;
        }

        if(!AccountData[playerid][pEatingDrinking])
        {
            pEatingBarTimer[playerid] = false;
            AccountData[playerid][pEatingDrinking] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 6)
        {
            pEatingBarTimer[playerid] = false;
            AccountData[playerid][pEatingDrinking] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);
        }
        else
        {
            AccountData[playerid][pActivityTime]++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/6;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pBreakingVehDoorTimer[playerid])
    {
        new vid = AccountData[playerid][pTempVehID];
        if(!IsPlayerConnected(playerid)) 
        {
            pBreakingVehDoorTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }
        if(!IsValidVehicle(vid))
        {
            pBreakingVehDoorTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            return 0;
        }
        if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        {
            pBreakingVehDoorTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }
        static Float:vX, Float:vY, Float:vZ;
        GetVehiclePos(vid, vX, vY, vZ);
        if(!IsPlayerInRangeOfPoint(playerid, 3.5, vX, vY, vZ))
        {
            pBreakingVehDoorTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 11)
        {
            pBreakingVehDoorTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);

            VehicleCore[vid][vCoreLocked] = false;
            SwitchVehicleDoors(vid, false);
            PlayerPlayNearbySound(playerid, SOUND_LOCK_CAR_DOOR);
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membuka kendaraan tersebut.");

            NearestVehicleID[playerid] = INVALID_VEHICLE_ID;
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/11;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pImpoundingInsuTimer[playerid])
    {
        new vid = AccountData[playerid][pTempVehIterID];
        if(vid == -1)
        {
            pImpoundingInsuTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehIterID] = -1;
            return 0;
        }
        
        if(!IsPlayerConnected(playerid)) 
        {
            pImpoundingInsuTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehIterID] = -1;
            return 0;
        }
        if(!IsValidVehicle(PlayerVehicle[vid][pVehPhysic]))
        {
            pImpoundingInsuTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehIterID] = -1;
            return 0;
        }
        if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        {
            pImpoundingInsuTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehIterID] = -1;
            return 0;
        }
        static Float:vX, Float:vY, Float:vZ;
        GetVehiclePos(PlayerVehicle[vid][pVehPhysic], vX, vY, vZ);
        if(!IsPlayerInRangeOfPoint(playerid, 3.5, vX, vY, vZ))
        {
            pImpoundingInsuTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehIterID] = -1;
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 16)
        {
            pImpoundingInsuTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);

            PlayerVehicle[vid][pVehInsuranced] = true;

            foreach(new i : Player)
            {
                if(AccountData[i][pSpawned] && AccountData[i][IsLoggedIn] && PlayerVehicle[vid][pVehOwnerID] == AccountData[i][pID])
                {
                    SendClientMessageEx(i, -1, "Kendaraan "AQUAMARINE"%s "WHITE"anda telah diasuransikan oleh petugas kepolisian!", GetVehicleModelName(PlayerVehicle[vid][pVehModelID]));
                }
            }

            DestroyVehicle(PlayerVehicle[vid][pVehPhysic]);

            new impstr[144];
            mysql_format(g_SQL, impstr, sizeof(impstr), "UPDATE `player_vehicles` SET `PVeh_Insuranced` = 1 WHERE `id`=%d",PlayerVehicle[vid][pVehID]);
            mysql_pquery(g_SQL, impstr);
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyita kendaraan tersebut ke asuransi.");

            NearestVehicleID[playerid] = INVALID_VEHICLE_ID;
            AccountData[playerid][pTempVehIterID] = -1;
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/16;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pImpoundingSamsatTimer[playerid])
    {
        new vid = AccountData[playerid][pTempVehIterID];
        if(!IsPlayerConnected(playerid)) 
        {
            pImpoundingSamsatTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);

            DestroyVehicle(PlayerVehicle[vid][pVehPhysic]);
            AccountData[playerid][pTempVehIterID] = -1;
            return 0;
        }
        if(!IsValidVehicle(PlayerVehicle[vid][pVehPhysic]))
        {
            pImpoundingSamsatTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            return 0;
        }
        if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        {
            pImpoundingSamsatTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);

            DestroyVehicle(PlayerVehicle[vid][pVehPhysic]);
            AccountData[playerid][pTempVehIterID] = -1;
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 16)
        {
            pImpoundingSamsatTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);

            foreach(new i : Player)
            {
                if(AccountData[i][pSpawned] && AccountData[i][IsLoggedIn] && PlayerVehicle[vid][pVehOwnerID] == AccountData[i][pID])
                {
                    SendClientMessageEx(i, -1, "Kendaraan "AQUAMARINE"%s "WHITE"anda telah di-impound oleh petugas kepolisian!", GetVehicleModelName(PlayerVehicle[vid][pVehModelID]));
                }
            }

            DestroyVehicle(PlayerVehicle[vid][pVehPhysic]);

            new impstr[250];
            mysql_format(g_SQL, impstr, sizeof(impstr), "UPDATE `player_vehicles` SET `PVeh_Impounded` = 1, `PVeh_ImpoundDuration`=%d, `PVeh_ImpoundFee`=%d, `PVeh_ImpoundReason`='%e' WHERE `id`=%d", PlayerVehicle[vid][pVehImpoundDuration], PlayerVehicle[vid][pVehImpoundFee], PlayerVehicle[vid][pVehImpoundReason], PlayerVehicle[vid][pVehID]);
            mysql_pquery(g_SQL, impstr);
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyita kendaraan tersebut ke dalam impound.");

            NearestVehicleID[playerid] = INVALID_VEHICLE_ID;
            AccountData[playerid][pTempVehIterID] = -1;
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/16;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pUsingPerbanTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pUsingPerbanTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopLoopingAnim(playerid);
            HideProgressBar(playerid);
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 6)
        {
            pUsingPerbanTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopLoopingAnim(playerid);
            HideProgressBar(playerid);

            new Float:hhealth;
            GetPlayerHealth(playerid, hhealth);
            SetPlayerHealthEx(playerid, hhealth+20);
        }
        else
        {

            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/6;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pUsingKevlarTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pUsingKevlarTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopLoopingAnim(playerid);
            HideProgressBar(playerid);
            return 0;
        }

        new Float:pkevlar;
		GetPlayerArmour(playerid, pkevlar);
		if(pkevlar >= 100.00)
        {
            pUsingKevlarTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopLoopingAnim(playerid);
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Armor anda telah mencapai maksimum!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 6)
        {
            pUsingKevlarTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopLoopingAnim(playerid);
            HideProgressBar(playerid);

            SetPlayerArmourEx(playerid, 100.0);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/6;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pSmokingWeedTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pSmokingWeedTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopLoopingAnim(playerid);
            HideProgressBar(playerid);
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 6)
        {
            pSmokingWeedTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopLoopingAnim(playerid);
            HideProgressBar(playerid);

            AccountData[playerid][pStress] -= 8;

            SetPlayerDrunkLevel(playerid, 50000);
            ShowStressEffectTD(playerid);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/6;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pUsingMethTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pUsingMethTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopLoopingAnim(playerid);
            HideProgressBar(playerid);
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 6)
        {
            pUsingMethTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopLoopingAnim(playerid);
            HideProgressBar(playerid);

            AccountData[playerid][pHunger] += 50;
            AccountData[playerid][pThirst] += 50;
                
            SetPlayerDrunkLevel(playerid, 50000);
            ShowStressEffectTD(playerid);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/6;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    
    }
    
    if(pUsingHeroinTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pUsingHeroinTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopLoopingAnim(playerid);
            HideProgressBar(playerid);
            return 0;
        }

        new Float:pkevlar;
		GetPlayerArmour(playerid, pkevlar);
		if(pkevlar >= 100.00)
        {
            pUsingHeroinTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopLoopingAnim(playerid);
            HideProgressBar(playerid);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Armor anda telah mencapai maksimum!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 6)
        {
            pUsingHeroinTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopLoopingAnim(playerid);
            HideProgressBar(playerid);

            new Float:phealth, Float:parmso;
            GetPlayerHealth(playerid, phealth);
            SetPlayerHealthEx(playerid, phealth+50);
            GetPlayerArmour(playerid, parmso);
            SetPlayerArmourEx(playerid, parmso+50);

            AccountData[playerid][pHunger] += 50;
            AccountData[playerid][pThirst] += 50;
                
            SetPlayerDrunkLevel(playerid, 50000);
            ShowStressEffectTD(playerid);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/6;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pDrinkingWhiskyTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pDrinkingWhiskyTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopLoopingAnim(playerid);
            StopFoodAnim(playerid);
            HideProgressBar(playerid);
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 6)
        {
            pDrinkingWhiskyTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopLoopingAnim(playerid);
            StopFoodAnim(playerid);
            HideProgressBar(playerid);

            AccountData[playerid][pStress] -= 8;
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/6;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pDrinkingSojuTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pDrinkingSojuTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopLoopingAnim(playerid);
            StopFoodAnim(playerid);
            HideProgressBar(playerid);
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 6)
        {
            pDrinkingSojuTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopLoopingAnim(playerid);
            StopFoodAnim(playerid);
            HideProgressBar(playerid);

            AccountData[playerid][pStress] -= 8;
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/6;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pUsingPilStressTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pUsingPilStressTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopLoopingAnim(playerid);
            HideProgressBar(playerid);
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 6)
        {
            pUsingPilStressTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopLoopingAnim(playerid);
            HideProgressBar(playerid);

            AccountData[playerid][pStress] -= 5;

            if(AccountData[playerid][pStress] <= 85)
            {
                SetPlayerDrunkLevel(playerid, 0);
                HideStressEffectTD(playerid);
            }
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/6;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }
    return 1;
}

ptask UpdateTimeJob[1000](playerid)
{
    if(pMechRepairEngineTimer[playerid]) //langsung vehicleid
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pMechRepairEngineTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }

        if(AccountData[playerid][pTempVehID] == INVALID_VEHICLE_ID)
        {
            pMechRepairEngineTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }

        if(!IsValidVehicle(AccountData[playerid][pTempVehID]))
        {
            pMechRepairEngineTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }
        if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        {
            pMechRepairEngineTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }

        static Float:vX, Float:vY, Float:vZ;
        GetVehiclePos(AccountData[playerid][pTempVehID], vX, vY, vZ);
        if(!IsPlayerInRangeOfPoint(playerid, 4.0, vX, vY, vZ))
        {
            pMechRepairEngineTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 11)
        {
            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
            pMechRepairEngineTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);

            SetValidVehicleHealth(AccountData[playerid][pTempVehID], VehicleCore[AccountData[playerid][pTempVehID]][vMaxHealth]);

            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memperbaiki ~p~mesin kendaraan!");
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/11;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }
    
    if(pMechRepairBodyTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pMechRepairBodyTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }

        if(AccountData[playerid][pTempVehID] == INVALID_VEHICLE_ID)
        {
            pMechRepairBodyTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }

        if(!IsValidVehicle(AccountData[playerid][pTempVehID]))
        {
            pMechRepairBodyTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }
        if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        {
            pMechRepairBodyTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }

        static Float:vX, Float:vY, Float:vZ;
        GetVehiclePos(AccountData[playerid][pTempVehID], vX, vY, vZ);
        if(!IsPlayerInRangeOfPoint(playerid, 4.0, vX, vY, vZ))
        {
            pMechRepairBodyTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 11)
        {
            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);

            pMechRepairBodyTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);

            GetVehicleDamageStatus(AccountData[playerid][pTempVehID], VehicleCore[AccountData[playerid][pTempVehID]][vCoreDamage][0], VehicleCore[AccountData[playerid][pTempVehID]][vCoreDamage][1], VehicleCore[AccountData[playerid][pTempVehID]][vCoreDamage][2], VehicleCore[AccountData[playerid][pTempVehID]][vCoreDamage][3]);
            UpdateVehicleDamageStatus(AccountData[playerid][pTempVehID], 0, 0, 0, VehicleCore[AccountData[playerid][pTempVehID]][vCoreDamage][3]);

            VehicleCore[AccountData[playerid][pTempVehID]][vIsBodyBroken] = false;

            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memperbaiki ~p~body kendaraan!");

            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/11;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pMechRepairTiresTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pMechRepairTiresTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }

        if(AccountData[playerid][pTempVehID] == INVALID_VEHICLE_ID)
        {
            pMechRepairTiresTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }

        if(!IsValidVehicle(AccountData[playerid][pTempVehID]))
        {
            pMechRepairTiresTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }
        if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        {
            pMechRepairTiresTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }

        static Float:vX, Float:vY, Float:vZ;
        GetVehiclePos(AccountData[playerid][pTempVehID], vX, vY, vZ);
        if(!IsPlayerInRangeOfPoint(playerid, 4.0, vX, vY, vZ))
        {
            pMechRepairTiresTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 11)
        {
            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);

            pMechRepairTiresTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);

            GetVehicleDamageStatus(AccountData[playerid][pTempVehID], VehicleCore[AccountData[playerid][pTempVehID]][vCoreDamage][0], VehicleCore[AccountData[playerid][pTempVehID]][vCoreDamage][1], VehicleCore[AccountData[playerid][pTempVehID]][vCoreDamage][2], VehicleCore[AccountData[playerid][pTempVehID]][vCoreDamage][3]);
            UpdateVehicleDamageStatus(AccountData[playerid][pTempVehID], VehicleCore[AccountData[playerid][pTempVehID]][vCoreDamage][0], VehicleCore[AccountData[playerid][pTempVehID]][vCoreDamage][1], VehicleCore[AccountData[playerid][pTempVehID]][vCoreDamage][2], 0);

            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memperbaiki ~p~ban kendaraan!");
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/11;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pMechUpgradeEngine[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pMechUpgradeEngine[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }

        if(AccountData[playerid][pTempVehID] == INVALID_VEHICLE_ID)
        {
            pMechUpgradeEngine[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }

        if(!IsValidVehicle(AccountData[playerid][pTempVehID]))
        {
            pMechUpgradeEngine[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }
        if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        {
            pMechUpgradeEngine[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }

        static Float:vX, Float:vY, Float:vZ;
        GetVehiclePos(AccountData[playerid][pTempVehID], vX, vY, vZ);
        if(!IsPlayerInRangeOfPoint(playerid, 4.0, vX, vY, vZ))
        {
            pMechUpgradeEngine[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 11)
        {
            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);

            pMechUpgradeEngine[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);

            if(VehicleCore[AccountData[playerid][pTempVehID]][vMaxHealth] == 1000.00)
            {
                VehicleCore[AccountData[playerid][pTempVehID]][vMaxHealth] = 1500.00;
                ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil upgrade mesin kendaraan menjadi ~b~level 2!");
            }
            else if(VehicleCore[AccountData[playerid][pTempVehID]][vMaxHealth] == 1500.00)
            {
                VehicleCore[AccountData[playerid][pTempVehID]][vMaxHealth] = 2000.00;
                ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil upgrade mesin kendaraan menjadi ~b~level 3!");
            }
            VehicleCore[AccountData[playerid][pTempVehID]][vCoreDamage][0] = 0;
            VehicleCore[AccountData[playerid][pTempVehID]][vCoreDamage][1] = 0;
            VehicleCore[AccountData[playerid][pTempVehID]][vCoreDamage][2] = 0;
            VehicleCore[AccountData[playerid][pTempVehID]][vCoreDamage][3] = 0;
            VehicleCore[AccountData[playerid][pTempVehID]][vIsBodyBroken] = false;
            UpdateVehicleDamageStatus(AccountData[playerid][pTempVehID], VehicleCore[AccountData[playerid][pTempVehID]][vCoreDamage][0], VehicleCore[AccountData[playerid][pTempVehID]][vCoreDamage][1], VehicleCore[AccountData[playerid][pTempVehID]][vCoreDamage][2], VehicleCore[AccountData[playerid][pTempVehID]][vCoreDamage][3]);
            SetValidVehicleHealth(AccountData[playerid][pTempVehID], VehicleCore[AccountData[playerid][pTempVehID]][vMaxHealth]);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/11;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pMechUpgradeBody[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pMechUpgradeBody[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }

        if(AccountData[playerid][pTempVehID] == INVALID_VEHICLE_ID)
        {
            pMechUpgradeBody[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }

        if(!IsValidVehicle(AccountData[playerid][pTempVehID]))
        {
            pMechUpgradeBody[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }
        if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        {
            pMechUpgradeBody[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }

        static Float:vX, Float:vY, Float:vZ;
        GetVehiclePos(AccountData[playerid][pTempVehID], vX, vY, vZ);
        if(!IsPlayerInRangeOfPoint(playerid, 4.0, vX, vY, vZ))
        {
            pMechUpgradeBody[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 11)
        {
            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
            
            pMechUpgradeBody[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);

            VehicleCore[AccountData[playerid][pTempVehID]][vIsBodyUpgraded] = true;
            VehicleCore[AccountData[playerid][pTempVehID]][vCoreDamage][0] = 0;
            VehicleCore[AccountData[playerid][pTempVehID]][vCoreDamage][1] = 0;
            VehicleCore[AccountData[playerid][pTempVehID]][vCoreDamage][2] = 0;
            VehicleCore[AccountData[playerid][pTempVehID]][vCoreDamage][3] = 0;
            VehicleCore[AccountData[playerid][pTempVehID]][vIsBodyBroken] = false;
            UpdateVehicleDamageStatus(AccountData[playerid][pTempVehID], VehicleCore[AccountData[playerid][pTempVehID]][vCoreDamage][0], VehicleCore[AccountData[playerid][pTempVehID]][vCoreDamage][1], VehicleCore[AccountData[playerid][pTempVehID]][vCoreDamage][2], VehicleCore[AccountData[playerid][pTempVehID]][vCoreDamage][3]);
            SetValidVehicleHealth(AccountData[playerid][pTempVehID], VehicleCore[AccountData[playerid][pTempVehID]][vMaxHealth]);
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;

            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil upgrade body kendaraan!");
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/11;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(ForkliftLoadTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            ForkliftLoadTimer[playerid] = false;
            return 0;
        }

        if(!IsPlayerInDynamicCP(playerid, ForkliftCP[playerid]))
        {
            ForkliftLoadTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            TogglePlayerControllable(playerid, true);
            return 0;
        }

        if(AccountData[playerid][pSideJob] != SIDEJOB_FORKLIFT)
        {
            ForkliftLoadTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            TogglePlayerControllable(playerid, true);
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 7)
        {
            ForkliftLoadTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            TogglePlayerControllable(playerid, true);
            
            if(DestroyDynamicCP(ForkliftCP[playerid]))
                ForkliftCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

            if(DestroyDynamicCP(UnloadForkliftCP[playerid]))
                UnloadForkliftCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

            if(DestroyDynamicObject(ForkliftCrateObj[playerid]))
                ForkliftCrateObj[playerid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

            new rand = random(sizeof(UnloadingCratePos));
            UnloadForkliftCP[playerid] = CreateDynamicCP(UnloadingCratePos[rand][0], UnloadingCratePos[rand][1], UnloadingCratePos[rand][2], 3.5, 0, 0, playerid, 10000.00, -1, 0);
            ForkliftCrateObj[playerid] = CreateDynamicObject(1271,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            AttachDynamicObjectToVehicle(ForkliftCrateObj[playerid], SavingVehID[playerid], -0.019, 0.500, 0.270, 0.000, 0.000, 0.000);

            ShowPlayerFooter(playerid, "~g~Sidejob Forklift: ~w~Bawa ~y~crate ~w~ke tempat bongkar muatan~n~yang telah ditandai dengan ~r~icon ~w~pada map!", 15000);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/7;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }
    if(ForkliftUnloadTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            ForkliftUnloadTimer[playerid] = false;
            return 0;
        }

        if(!IsPlayerInDynamicCP(playerid, UnloadForkliftCP[playerid]))
        {
            ForkliftUnloadTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            TogglePlayerControllable(playerid, true);
            return 0;
        }

        if(AccountData[playerid][pSideJob] != SIDEJOB_FORKLIFT)
        {
            ForkliftUnloadTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            TogglePlayerControllable(playerid, true);
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 7)
        {
            ForkliftUnloadTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            TogglePlayerControllable(playerid, true);
            
            ForkliftUnloadedCrate[playerid]++;

            if(DestroyDynamicCP(ForkliftCP[playerid]))
                ForkliftCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

            if(DestroyDynamicCP(UnloadForkliftCP[playerid]))
                UnloadForkliftCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

            if(DestroyDynamicObject(ForkliftCrateObj[playerid]))
                ForkliftCrateObj[playerid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

            ShowPlayerFooter(playerid, sprintf("~y~%d/10 crate ~w~telah dibongkar muat", ForkliftUnloadedCrate[playerid]), 5000);

            if(ForkliftUnloadedCrate[playerid] >= 10)
            {
                if(DestroyDynamicCP(ForkliftReturnCP[playerid]))
                    ForkliftReturnCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                ForkliftReturnCP[playerid] = CreateDynamicCP(-1732.6582,-65.4632,3.5547, 3.5, 0, 0, playerid, 10000.00, -1, 0);

                ShowTDN(playerid, NOTIFICATION_INFO, "Tugas forklift selesai, kembalikan kendaraan ke tempat awal untuk mendapat bayaran.");
            }
            else
            {
                new rand = random(sizeof(LoadingCratePos));
                ForkliftCP[playerid] = CreateDynamicCP(LoadingCratePos[rand][0], LoadingCratePos[rand][1], LoadingCratePos[rand][2], 3.5, 0, 0, playerid, 10000.00, -1, 0);
            }
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/7;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }
    return 1;
}

ptask UpdateTimeJob2[1000](playerid)
{
    if(pMedisLokalTimer[playerid])
    {
        if(!IsPlayerConnected(playerid))
        {
            pMedisLokalTimer[playerid] = false;
            AccountData[playerid][pDuringUseLocalMedic] = false;
            return 0;
        }

        if(!AccountData[playerid][pDuringUseLocalMedic])
        {
            pMedisLokalTimer[playerid] = false;
            AccountData[playerid][pDuringUseLocalMedic] = false;
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 20)
        {
            AccountData[playerid][pActivityTime] = 0;

            pMedisLokalTimer[playerid] = false;
            AccountData[playerid][pDuringUseLocalMedic] = false;
            HideProgressBar(playerid);

            SetPlayerHealthEx(playerid, 100.0);
            AccountData[playerid][pAccDeathTime] = 0;
            AccountData[playerid][pKnockdown] = false;
            AccountData[playerid][pKnockdownTime] = 0;
            AccountData[playerid][pHunger] = 50;
            AccountData[playerid][pThirst] = 50;
            AccountData[playerid][pStress] = 0;
            DeathCause[playerid][Bruised] = false;
            DeathCause[playerid][Shoted] = false;
            DeathCause[playerid][Burns] = false;
            DeathCause[playerid][Drown] = false;
            DeathCause[playerid][Fallen] = false;
            new frmtsql[215];
            mysql_format(g_SQL, frmtsql, sizeof(frmtsql), "UPDATE `player_characters` SET `Char_Knockdown` = 0, `Char_KnockdownTime` = 0, `Char_Hunger` = 50, `Char_Thirst` = 50, `Char_Stress` = 0 WHERE `pID` = %d", AccountData[playerid][pID]);
            mysql_pquery(g_SQL, frmtsql);

            TakePlayerMoneyEx(playerid, 15000);

            ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah disembuhkan oleh dokter lokal seharga $15,000.");

            HideKnockTD(playerid);
            StopRunningAnimation(playerid);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/20;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(RevivingPlayerTimer[playerid])
    {
        new targetid = NearestSingle[playerid];
        if(!AccountData[playerid][LSFDDuringReviving])
        {
            RevivingPlayerTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            AccountData[playerid][LSFDDuringReviving] = false;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            NearestSingle[playerid] = INVALID_PLAYER_ID;
            return 0;
        }

        if(!IsPlayerConnected(playerid))
        {
            RevivingPlayerTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            AccountData[playerid][LSFDDuringReviving] = false;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            NearestSingle[playerid] = INVALID_PLAYER_ID;
            return 0;
        }

        if(!IsPlayerConnected(targetid))
        {
            RevivingPlayerTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            AccountData[playerid][LSFDDuringReviving] = false;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak ada di server!");
            NearestSingle[playerid] = INVALID_PLAYER_ID;
            return 0;
        }

        if(!IsPlayerNearPlayer(playerid, targetid, 2.5)) 
        {
            RevivingPlayerTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            AccountData[playerid][LSFDDuringReviving] = false;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            ShowTDN(playerid, NOTIFICATION_ERROR, "You are not close enough to the player!");
            NearestSingle[playerid] = INVALID_PLAYER_ID;
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 21)
        {
            RevivingPlayerTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            AccountData[playerid][LSFDDuringReviving] = false;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);

            HideKnockTD(targetid);
            SetPlayerHealthEx(targetid, 100.0);
            AccountData[targetid][pKnockdown] = false;
            AccountData[targetid][pKnockdownTime] = 0;
            AccountData[targetid][pHunger] = 50;
            AccountData[targetid][pThirst] = 50;
            AccountData[targetid][pStress] = 0;

            DeathCause[targetid][Bruised] = false;
            DeathCause[targetid][Shoted] = false;
            DeathCause[targetid][Burns] = false;
            DeathCause[targetid][Drown] = false;
            DeathCause[targetid][Fallen] = false;

            new frmtsql[215];
            mysql_format(g_SQL, frmtsql, sizeof(frmtsql), "UPDATE `player_characters` SET `Char_Knockdown` = 0, `Char_KnockdownTime` = 0, `Char_Hunger` = 50, `Char_Thirst` = 50, `Char_Stress` = 0 WHERE `pID` = %d", AccountData[targetid][pID]);
            mysql_pquery(g_SQL, frmtsql);

            StopRunningAnimation(targetid);

            NearestSingle[playerid] = INVALID_PLAYER_ID;
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/21;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pTakeWoodTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pTakeWoodTimer[playerid] = false;
            return 0;
        }

        if(!IsPlayerInTreePos(playerid))
        {
            pTakeWoodTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            if(IsPlayerAttachedObjectSlotUsed(playerid, 9)) 
                RemovePlayerAttachedObject(playerid, 9);
            return 0;
        }
        
        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pTakeWoodTimer[playerid] = false;

            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

            if(IsPlayerAttachedObjectSlotUsed(playerid, 9)) 
                RemovePlayerAttachedObject(playerid, 9);
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 6)
        {
            pTakeWoodTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            if(IsPlayerAttachedObjectSlotUsed(playerid, 9)) 
                RemovePlayerAttachedObject(playerid, 9);

            new t = AccountData[playerid][pInTree];
            if(DestroyDynamicArea(PlayerLumberjackVars[playerid][LumberGetWoodArea][t]))
                PlayerLumberjackVars[playerid][LumberGetWoodArea][t] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

            PlayerLumberjackVars[playerid][LumberWoodCountdown][t] = 15;

            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(2 * GetItemWeight("Kayu"))/1000;
            if(countingtotalweight > 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

            Inventory_Add(playerid, "Kayu", 19793, 2);
            ShowItemBox(playerid, "Kayu", "Received 2x", 19793, 5);
        }
        else
        {
            AccountData[playerid][pActivityTime]++;

            PlayerPlaySound(playerid, 34604, 0.0, 0.0, 0.0);
            
            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/6;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pCutWoodTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pCutWoodTimer[playerid] = false;
            return 0;
        }

        if(!IsPlayerInCutLog(playerid))
        {
            pCutWoodTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pCutWoodTimer[playerid] = false;

            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(Inventory_Count(playerid, "Kayu") < 5)
        {
            pCutWoodTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Kayu anda tidak mencukupi! (Min: 5)");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 4)
        {
            pCutWoodTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            Inventory_Remove(playerid, "Kayu", 5);
            Inventory_Add(playerid, "Kayu Potong", 831, 5);
            ShowItemBox(playerid, "Kayu", "Removed 5x", 19793, 4);
            ShowItemBox(playerid, "Kayu Potong", "Received 5x", 831, 5);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            PlayerPlaySound(playerid, 17200, 0.0, 0.0, 0.0);

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/4;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pGetBoardTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pGetBoardTimer[playerid] = false;
            return 0;
        }

        if(!IsPlayerInPackLog(playerid))
        {
            pGetBoardTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pGetBoardTimer[playerid] = false;

            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(Inventory_Count(playerid, "Kayu Potong") < 5)
        {
            pGetBoardTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Kayu Potong anda tidak cukup! (Min: 5)");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 6)
        {
            pGetBoardTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            Inventory_Remove(playerid, "Kayu Potong", 5);
            Inventory_Add(playerid, "Papan", 19433, 5);
            ShowItemBox(playerid, "Kayu Potong", "Removed 5x", 831, 4);
            ShowItemBox(playerid, "Papan", "Received 5x", 19433, 5);

            AccountData[playerid][pStress]++;
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            PlayerPlaySound(playerid, 33401, 0.0, 0.0, 0.0);

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/6;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pTakingStoneTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pTakingStoneTimer[playerid] = false;
            return 0;
        }

        if(!IsValidDynamicArea(Miner_TakeStoneArea))
        {
            pTakingStoneTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            if(IsPlayerAttachedObjectSlotUsed(playerid, 9)) 
                RemovePlayerAttachedObject(playerid, 9);
            return 0;
        }

        if(!IsPlayerInDynamicArea(playerid, Miner_TakeStoneArea))
        {
            pTakingStoneTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            if(IsPlayerAttachedObjectSlotUsed(playerid, 9)) 
                RemovePlayerAttachedObject(playerid, 9);
            return 0;
        }
        
        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pTakingStoneTimer[playerid] = false;

            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            if(IsPlayerAttachedObjectSlotUsed(playerid, 9)) 
                RemovePlayerAttachedObject(playerid, 9);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 6)
        {
            pTakingStoneTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            if(IsPlayerAttachedObjectSlotUsed(playerid, 9)) 
                RemovePlayerAttachedObject(playerid, 9);

            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(2 * GetItemWeight("Batu"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

            Inventory_Add(playerid, "Batu", 3930, 2);
            ShowItemBox(playerid, "Batu", "Received 2x", 3930, 4);

            new rands = RandomEx(1, 101);
            switch(rands)
            {
                case 95..100:
                {
                    new randv = RandomEx(1, 6);
                    Inventory_Add(playerid, "Material", 2972, randv);
                    ShowItemBox(playerid, "Material", sprintf("Received %dx", randv), 2972, 5);
                }
            }
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            PlayerPlaySound(playerid, 1135, 0.0, 0.0, 0.0);

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/6;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }
    if(pWashingStoneTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pWashingStoneTimer[playerid] = false;
            return 0;
        }

        if(!IsValidDynamicArea(Miner_WashStoneArea))
        {
            pWashingStoneTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);
            return 0;
        }

        if(!IsPlayerInDynamicArea(playerid, Miner_WashStoneArea))
        {
            pWashingStoneTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pWashingStoneTimer[playerid] = false;

            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(Inventory_Count(playerid, "Batu") < 5)
        {
            pWashingStoneTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Batu! (Min: 5)");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 16)
        {
            pWashingStoneTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            Inventory_Remove(playerid, "Batu", 5);
            Inventory_Add(playerid, "Batu Cucian", 2936, 5);

            ShowItemBox(playerid, "Batu", "Removed 5x", 3930, 4);
            ShowItemBox(playerid, "Batu Cucian", "Received 5x", 2936, 5);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            PlayerPlaySound(playerid, 174, 0.0, 0.0, 0.0);

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/16;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }
    if(pSmeltingStoneTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pSmeltingStoneTimer[playerid] = false;
            return 0;
        }

        if(!IsPlayerInDynamicArea(playerid, Miner_SmeltStoneArea))
        {
            pSmeltingStoneTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pSmeltingStoneTimer[playerid] = false;

            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(Inventory_Count(playerid, "Batu Cucian") < 2)
        {
            pSmeltingStoneTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Batu Cucian! (Min: 2)");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 6)
        {
            pSmeltingStoneTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            Inventory_Remove(playerid, "Batu Cucian", 2);
            ShowItemBox(playerid, "Batu Cucian", "Removed 2x", 2936, 4);

            new randcase = random(151);
            Inventory_Add(playerid, "Tembaga", 11748);
            ShowItemBox(playerid, "Tembaga", "Received 1x", 11748, 5);
            switch(randcase)
            {
                case 0..128:
                {
                    Inventory_Add(playerid, "Besi", 19809);
                    ShowItemBox(playerid, "Besi", "Received 1x", 19809, 6);
                }
                case 129..149:
                {
                    Inventory_Add(playerid, "Emas", 19941);
                    ShowItemBox(playerid, "Emas", "Received 1x", 19941, 6);
                }
                case 150:
                {
                    Inventory_Add(playerid, "Berlian", 19874);
                    ShowItemBox(playerid, "Berlian", "Received 1x", 19874, 6);
                }
            }
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            PlayerPlaySound(playerid, 17801, 0.0, 0.0, 0.0);

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/6;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }
    if(pTakingChickTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pTakingChickTimer[playerid] = false;
            return 0;
        }

        if(!IsValidDynamicArea(Butcher_TakeChickArea))
        {
            pTakingChickTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);
            return 0;
        }

        if(!IsPlayerInDynamicArea(playerid, Butcher_TakeChickArea))
        {
            pTakingChickTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);
            return 0;
        }
        
        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pTakingChickTimer[playerid] = false;

            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 6)
        {
            pTakingChickTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(1 * GetItemWeight("Ayam"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

            Inventory_Add(playerid, "Ayam", 16776);
            ShowItemBox(playerid, "Ayam", "Received 1x", 16776, 4);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            PlayerPlaySound(playerid, 20803, 0.0, 0.0, 0.0);

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/6;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }
    if(pCutingChickTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pCutingChickTimer[playerid] = false;
            return 0;
        }

        if(!IsPlayerInDynamicArea(playerid, Butcher_CutChickArea))
        {
            pCutingChickTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);
            return 0;
        }

        if(Inventory_Count(playerid, "Ayam") < 5)
        {
            pCutingChickTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Ayam! (Min: 5)");
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pCutingChickTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 4)
        {
            pCutingChickTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            Inventory_Remove(playerid, "Ayam", 5);
            Inventory_Add(playerid, "Ayam Potong", 2804, 8);
            ShowItemBox(playerid, "Ayam", "Removed 5x", 16776, 4);
            ShowItemBox(playerid, "Ayam Potong", "Received 8x", 2804, 5);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            PlayerPlaySound(playerid, 32402, 0.0, 0.0, 0.0);

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/4;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pPackingChickTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pPackingChickTimer[playerid] = false;
            return 0;
        }

        if(!IsPlayerInDynamicArea(playerid, Butcher_PackChickArea))
        {
            pPackingChickTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);
            return 0;
        }
        
        if(Inventory_Count(playerid, "Ayam Potong") < 8)
        {
            pPackingChickTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Ayam Potong! (Min: 8)");
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pPackingChickTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 7)
        {
            pPackingChickTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            Inventory_Remove(playerid, "Ayam Potong", 8);
            Inventory_Add(playerid, "Ayam Kemas", 2768, 8);
            ShowItemBox(playerid, "Ayam Potong", "Removed 8x", 2804, 4);
            ShowItemBox(playerid, "Ayam Kemas", "Received 8x", 2768, 5);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            PlayerPlaySound(playerid, 20802, 0.0, 0.0, 0.0);

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/7;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pTakingOilTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pTakingOilTimer[playerid] = false;
            return 0;
        }

        if(!IsPlayerInTakeOilArea(playerid))
        {
            pTakingOilTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);
            return 0;
        }
        
        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pTakingOilTimer[playerid] = false;

            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 6)
        {
            pTakingOilTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(2 * GetItemWeight("Minyak Bumi"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

            Inventory_Add(playerid, "Minyak Bumi", 935, 2);
            ShowItemBox(playerid, "Minyak Bumi", "Received 2x", 935, 5);

            new rands = RandomEx(1, 101);
            switch(rands)
            {
                case 95..100:
                {
                    new randv = RandomEx(1, 6);
                    Inventory_Add(playerid, "Material", 2972, randv);
                    ShowItemBox(playerid, "Material", sprintf("Received %dx", randv), 2972, 5);
                }
            }
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            PlayerPlaySound(playerid, 11200, 0.0, 0.0, 0.0);

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/6;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pRefiningOilTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pRefiningOilTimer[playerid] = false;
            return 0;
        }

        if(!IsPlayerInDynamicArea(playerid, Oilman_RefineArea[0]) && !IsPlayerInDynamicArea(playerid, Oilman_RefineArea[1]))
        {
            pRefiningOilTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pRefiningOilTimer[playerid] = false;

            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(Inventory_Count(playerid, "Minyak Bumi") < 5)
        {
            pRefiningOilTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Minyak Bumi! (Min: 5)");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 16)
        {
            pRefiningOilTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            Inventory_Remove(playerid, "Minyak Bumi", 5);
            Inventory_Add(playerid, "Minyak Saringan", 3632, 5);

            ShowItemBox(playerid, "Minyak Bumi", "Removed 5x", 935, 4);
            ShowItemBox(playerid, "Minyak Saringan", "Received 5x", 3632, 5);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;
            
            PlayerPlaySound(playerid, 32600, 0.0, 0.0, 0.0);

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/16;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pMixingOilTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pMixingOilTimer[playerid] = false;
            return 0;
        }

        if(!IsPlayerInDynamicArea(playerid, Oilman_MixArea))
        {
            pMixingOilTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pMixingOilTimer[playerid] = false;

            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(Inventory_Count(playerid, "Minyak Saringan") < 5)
        {
            pMixingOilTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Minyak Saringan! (Min: 5)");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 6)
        {
            pMixingOilTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            Inventory_Remove(playerid, "Minyak Saringan", 5);
            Inventory_Add(playerid, "Minyak", 19621, 5);
            
            ShowItemBox(playerid, "Minyak Saringan", "Removed 5x", 3632, 4);
            ShowItemBox(playerid, "Minyak", "Received 5x", 19621, 5);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            PlayerPlaySound(playerid, 25800, 0.0, 0.0, 0.0);

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/6;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pLoadCargoTimer[playerid])
    {
        if(!IsPlayerConnected(playerid))
        {
            pLoadCargoTimer[playerid] = false;
            return 0;
        }

        if(!PlayerCargoVars[playerid][CargoStarted])
        {
            PlayerCargoVars[playerid][IsLoadingCargo] = false;
            pLoadCargoTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            TogglePlayerControllable(playerid, true);
            return 0;
        }

        if(!PlayerCargoVars[playerid][IsLoadingCargo])
        {
            pLoadCargoTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            TogglePlayerControllable(playerid, true);
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 66)
        {
            pLoadCargoTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            PlayerCargoVars[playerid][IsLoadingCargo] = false;
            PlayerCargoVars[playerid][CargoStarted] = false;
            TogglePlayerControllable(playerid, true);

            PlayerPlaySound(playerid, 12200, 0.0, 0.0, 0.0);

            ResetAllRaceCP(playerid);
            PlayerCargoVars[playerid][CargoReturnCP] = CreateDynamicRaceCP(1, -1544.2682,127.2019,4.1608, -1544.2682,127.2019,4.1608, 5.0, 0, 0, playerid, 6000.00, -1, 0);
            SendClientMessage(playerid, -1, "[i] Bawa muatan kargo kembali ke pelabuhan "YELLOW"Tanjung Katung. "WHITE"Ikutilah tanda!");
        }
        else
        {
            AccountData[playerid][pActivityTime]++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/66;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);

            PlayerPlaySound(playerid, 6002, 0.0, 0.0, 0.0);
        }
    }
    return 1;
}

ptask UpdateTimeJob3[1000](playerid)
{
    if(pDeliveringPizzaTimer[playerid])
    {
        if(!IsPlayerConnected(playerid))
        {
            if(DestroyDynamicActor(pizzaDeliveryActor[playerid]))
                pizzaDeliveryActor[playerid] = STREAMER_TAG_ACTOR: INVALID_STREAMER_ID;

            pDeliveringPizzaTimer[playerid] = false;
            return 0;
        }

        if(AccountData[playerid][pSideJob] != SIDEJOB_PIZZA)
        {
            if(DestroyDynamicActor(pizzaDeliveryActor[playerid]))
                pizzaDeliveryActor[playerid] = STREAMER_TAG_ACTOR: INVALID_STREAMER_ID;

            pDeliveringPizzaTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);
            return 0;
        }

        if(!pizzaHoldingBox[playerid])
        {
            if(DestroyDynamicActor(pizzaDeliveryActor[playerid]))
                pizzaDeliveryActor[playerid] = STREAMER_TAG_ACTOR: INVALID_STREAMER_ID;

            pDeliveringPizzaTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);
            return 0;
        }

        if(!IsPlayerInDynamicCP(playerid, pizzaDeliveryCP[playerid]))
        {
            if(DestroyDynamicActor(pizzaDeliveryActor[playerid]))
                pizzaDeliveryActor[playerid] = STREAMER_TAG_ACTOR: INVALID_STREAMER_ID;

            pDeliveringPizzaTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 11)
        {
            pDeliveringPizzaTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            RemovePlayerAttachedObject(playerid, 9);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            StopRunningAnimation(playerid);
            pizzaHoldingBox[playerid] = false;

            if(DestroyDynamicCP(pizzaDeliveryCP[playerid]))
                    pizzaDeliveryCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

            if(DestroyDynamicActor(pizzaDeliveryActor[playerid]))
                pizzaDeliveryActor[playerid] = STREAMER_TAG_ACTOR: INVALID_STREAMER_ID;

            if(DestroyDynamicRaceCP(pizzaDeliveryRCP[playerid]))
                pizzaDeliveryRCP[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;
            
            pizzaDelivered[playerid]++;

            new Float:distancia, Float:pricing;
            distancia = GetPlayerDistanceFromPoint(playerid, LastDeliveryPos[playerid][0], LastDeliveryPos[playerid][1], LastDeliveryPos[playerid][2]);
            
            pricing = distancia * 0.421;

            if(floatround(pricing) < 100)
            {
                GivePlayerMoneyEx(playerid, 75);
                ShowItemBox(playerid, "Cash", "Received $75x", 1212, 5);
            }
            else
            {
                GivePlayerMoneyEx(playerid, floatround(pricing));
                ShowItemBox(playerid, "Cash", sprintf("Received $%sx", FormatMoney(floatround(pricing))), 1212, 5);
            }

            if(pizzaDelivered[playerid] == 10)
            {
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah menyelesaikan tugas pengantaran pizza, kembalikan kendaraan segera!");

                pizzaDeliveryRCP[playerid] = CreateDynamicRaceCP(1, 2109.9192,-1774.5371,13.3921, 2109.9192,-1774.5371,13.3921, 3.5, 0, 0, playerid, 10000.00, -1, 0);
            }
            else
            {
                GetPlayerPos(playerid, LastDeliveryPos[playerid][0], LastDeliveryPos[playerid][1], LastDeliveryPos[playerid][2]);

                pizzaRandom[playerid] = random(sizeof(deliveryPizzaPos));
                pizzaDeliveryCP[playerid] = CreateDynamicCP(deliveryPizzaPos[pizzaRandom[playerid]][0], deliveryPizzaPos[pizzaRandom[playerid]][1], deliveryPizzaPos[pizzaRandom[playerid]][2], 2.0, 0, 0, playerid, 10000, -1, 0);

                ShowPlayerFooter(playerid, sprintf("~y~%d/10 pizza ~w~telah diantarkan kepada pelanggan", pizzaDelivered[playerid]), 500);
            }

            ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, false, false, false, false, 0, true);
        }
        else
        {
            AccountData[playerid][pActivityTime]++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/11;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pTakingPlantTimer[playerid])
    {
        new d = AccountData[playerid][pInPlant];

        if(PlayerFarmerVars[playerid][pDuringTakingPlant])
        {
            if(!IsPlayerConnected(playerid)) 
            {
                FarmerPlant[d][DuringHarvest] = false;
                pTakingPlantTimer[playerid] = false;
                return 0;
            }

            if(!IsValidDynamicCP(FarmerPlant[d][FarmerPlantCP]))
            {
                FarmerPlant[d][DuringHarvest] = false;
                pTakingPlantTimer[playerid] = false;

                PlayerFarmerVars[playerid][pDuringTakingPlant] = false;

                AccountData[playerid][pActivityTime] = 0;
                HideProgressBar(playerid);

                ClearAnimations(playerid, true);
                StopLoopingAnim(playerid);
                SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
                TogglePlayerControllable(playerid, true);
                return 0;
            }

            if(!IsPlayerInDynamicCP(playerid, FarmerPlant[d][FarmerPlantCP]))
            {
                FarmerPlant[d][DuringHarvest] = false;
                pTakingPlantTimer[playerid] = false;

                PlayerFarmerVars[playerid][pDuringTakingPlant] = false;

                AccountData[playerid][pActivityTime] = 0;
                HideProgressBar(playerid);

                ClearAnimations(playerid, true);
                StopLoopingAnim(playerid);
                SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
                TogglePlayerControllable(playerid, true);
                return 0;
            }

            if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
            {
                FarmerPlant[d][DuringHarvest] = false;
                pTakingPlantTimer[playerid] = false;

                PlayerFarmerVars[playerid][pDuringTakingPlant] = false;

                AccountData[playerid][pActivityTime] = 0;
                HideProgressBar(playerid);

                ClearAnimations(playerid, true);
                StopLoopingAnim(playerid);
                SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
                TogglePlayerControllable(playerid, true);

                ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
                return 0;
            }

            if(AccountData[playerid][pActivityTime] >= 4)
            {
                TogglePlayerControllable(playerid, true);
                
                PlayerFarmerVars[playerid][pDuringTakingPlant] = false;
                AccountData[playerid][pActivityTime] = 0;

                pTakingPlantTimer[playerid] = false;

                HideProgressBar(playerid);

                if(DestroyDynamicObject(FarmerPlant[d][FarmerPlantObject]))
                    FarmerPlant[d][FarmerPlantObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

                if(DestroyDynamicCP(FarmerPlant[d][FarmerPlantCP]))
                    FarmerPlant[d][FarmerPlantCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                FarmerPlant[d][DeadTimer] = 0;
                FarmerPlant[d][DuringHarvest] = false;
                FarmerPlant[d][Watered] = false;
                FarmerPlant[d][Pos][0] = 0;
                FarmerPlant[d][Pos][1] = 0;
                FarmerPlant[d][Pos][2] = 0;
                FarmerPlant[d][ReadyHarvest] = false;
                FarmerPlant[d][SpawnTimer] = 0;

                new randvalue = RandomEx(1, 7);
                new randevent = random(10);
                switch(randevent)
                {
                    case 0..7:
                    {
                        switch(FarmerPlant[d][Type])
                        {
                            case FARMER_PLANT_CABAI:
                            {
                                Inventory_Add(playerid, "Cabai", 2253, randvalue);
                                ShowItemBox(playerid, "Cabai", sprintf("Received %dx", randvalue), 2253, 5);
                            }
                            case FARMER_PLANT_TEBU:
                            {
                                Inventory_Add(playerid, "Tebu", 855, randvalue);
                                ShowItemBox(playerid, "Tebu", sprintf("Received %dx", randvalue), 855, 5);
                            }
                            case FARMER_PLANT_PADI:
                            {
                                Inventory_Add(playerid, "Padi", 2247, randvalue);
                                ShowItemBox(playerid, "Padi", sprintf("Received %dx", randvalue), 2247, 5);
                            }
                            case FARMER_PLANT_STRAWBERRY:
                            {
                                Inventory_Add(playerid, "Strawberry", 19577, randvalue);
                                ShowItemBox(playerid, "Strawberry", sprintf("Received %dx", randvalue), 19577, 5);
                            }
                            case FARMER_PLANT_JERUK:
                            {
                                Inventory_Add(playerid, "Jeruk", 19574, randvalue);
                                ShowItemBox(playerid, "Jeruk", sprintf("Received %dx", randvalue), 19574, 5);
                            }
                            case FARMER_PLANT_ANGGUR:
                            {
                                Inventory_Add(playerid, "Anggur", 19576, randvalue);
                                ShowItemBox(playerid, "Anggur", sprintf("Received %dx", randvalue), 19576, 5);
                            }
                        }
                    }
                    case 8, 9:
                    {
                        ShowTDN(playerid, NOTIFICATION_WARNING, "Tanaman telah dirusak oleh jawa, anda tidak mendapatkan hasil panen apapun.");
                    }
                }
                FarmerPlant[d][Type] = FARMER_PLANT_NONE;

                static strgbg[258];
                mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `farmplants` WHERE `id` = %d", d);
                mysql_pquery(g_SQL, strgbg);
 
                Iter_Remove(FarmPlants, d);
            }
            else
            {
                AccountData[playerid][pActivityTime] ++;

                static Float:progressvalue;
                progressvalue = AccountData[playerid][pActivityTime] * 102.0/4;
                PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
                PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
            }
        }
    }

    if(pAngkotTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pAngkotTimer[playerid] = false;
            return 0;
        }

        if(!IsValidDynamicRaceCP(JobCP[playerid]))
        {
            pAngkotTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            TogglePlayerControllable(playerid, true);
            return 0;
        }

        if(!IsPlayerInDynamicRaceCP(playerid, JobCP[playerid]))
        {
            pAngkotTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            TogglePlayerControllable(playerid, true);
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 6)
        {
            pAngkotTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            TogglePlayerControllable(playerid, true);

            GivePlayerMoneyEx(playerid, 35);
            ShowItemBox(playerid, "Cash", "Received $35x", 1212, 5);

            AngkotRute[playerid]++;
            AngkotPenumpang[playerid] = false;
            PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);

            if(DestroyDynamicRaceCP(JobCP[playerid]))
                JobCP[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

            if(DestroyDynamicActor(AngkotActor[playerid]))
                AngkotActor[playerid] = STREAMER_TAG_ACTOR: INVALID_STREAMER_ID;

            if(AngkotRouteType[playerid] == 1)
            {
                if(AngkotRute[playerid] >= 22)
                {
                    JobCP[playerid] = CreateDynamicRaceCP(1, Angkot25Route[AngkotRute[playerid]][Pos][0], Angkot25Route[AngkotRute[playerid]][Pos][1], Angkot25Route[AngkotRute[playerid]][Pos][2], Angkot25Route[AngkotRute[playerid]][Pos][0], Angkot25Route[AngkotRute[playerid]][Pos][1], Angkot25Route[AngkotRute[playerid]][Pos][2], 3.5, 0, 0, playerid, 10000.00, -1, 0);
                }
                else
                {
                    new randactor = random(11), randskin = RandomEx(1, 311);
                    switch(randactor)
                    {
                        case 2, 4:
                        {
                            AngkotActor[playerid] = CreateDynamicActor(randskin, Angkot25Route[AngkotRute[playerid]][ActorPos][0], Angkot25Route[AngkotRute[playerid]][ActorPos][1], Angkot25Route[AngkotRute[playerid]][ActorPos][2], Angkot25Route[AngkotRute[playerid]][ActorPos][3], true, 100.0, 0, 0, -1, 200.00, -1, 0);
                            ApplyDynamicActorAnimation(AngkotActor[playerid], "MISC", "Hiker_Pose", 4.1, true, false, false, false, 0);
                            AngkotPenumpang[playerid] = true;
                        }
                    }
                    JobCP[playerid] = CreateDynamicRaceCP(0, Angkot25Route[AngkotRute[playerid]][Pos][0], Angkot25Route[AngkotRute[playerid]][Pos][1], Angkot25Route[AngkotRute[playerid]][Pos][2], Angkot25Route[AngkotRute[playerid]+1][Pos][0], Angkot25Route[AngkotRute[playerid]+1][Pos][1], Angkot25Route[AngkotRute[playerid]+1][Pos][2], 3.5, 0, 0, playerid, 10000.00, -1, 0);
                }
            }
            else if(AngkotRouteType[playerid] == 2)
            {
                if(AngkotRute[playerid] >= 22)
                {
                    JobCP[playerid] = CreateDynamicRaceCP(1, Angkot36Route[AngkotRute[playerid]][Pos][0], Angkot36Route[AngkotRute[playerid]][Pos][1], Angkot36Route[AngkotRute[playerid]][Pos][2], Angkot36Route[AngkotRute[playerid]][Pos][0], Angkot36Route[AngkotRute[playerid]][Pos][1], Angkot36Route[AngkotRute[playerid]][Pos][2], 3.5, 0, 0, playerid, 10000.00, -1, 0);
                }
                else
                {
                    new randactor = random(11), randskin = RandomEx(1, 311);
                    switch(randactor)
                    {
                        case 2, 4:
                        {
                            AngkotActor[playerid] = CreateDynamicActor(randskin, Angkot36Route[AngkotRute[playerid]][ActorPos][0], Angkot36Route[AngkotRute[playerid]][ActorPos][1], Angkot36Route[AngkotRute[playerid]][ActorPos][2], Angkot36Route[AngkotRute[playerid]][ActorPos][3], true, 100.0, 0, 0, -1, 200.00, -1, 0);
                            ApplyDynamicActorAnimation(AngkotActor[playerid], "MISC", "Hiker_Pose", 4.1, true, false, false, false, 0);
                            AngkotPenumpang[playerid] = true;
                        }
                    }
                    JobCP[playerid] = CreateDynamicRaceCP(0, Angkot36Route[AngkotRute[playerid]][Pos][0], Angkot36Route[AngkotRute[playerid]][Pos][1], Angkot36Route[AngkotRute[playerid]][Pos][2], Angkot36Route[AngkotRute[playerid]+1][Pos][0], Angkot36Route[AngkotRute[playerid]+1][Pos][1], Angkot36Route[AngkotRute[playerid]+1][Pos][2], 3.5, 0, 0, playerid, 10000.00, -1, 0);
                }
            }
            Streamer_Update(playerid, -1);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/6;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(SailDockTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            SailDockTimer[playerid] = false;
            return 0;
        }

        if(!IsValidDynamicRaceCP(JobCP[playerid]))
        {
            SailDockTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            TogglePlayerControllable(playerid, true);
            return 0;
        }

        if(!IsPlayerInDynamicRaceCP(playerid, JobCP[playerid]))
        {
            SailDockTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            TogglePlayerControllable(playerid, true);
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 11)
        {
            SailDockTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            TogglePlayerControllable(playerid, true);

            GivePlayerMoneyEx(playerid, 800);
            ShowItemBox(playerid, "Cash", "Received $800x", 1212, 5);

            PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);

            if(DestroyDynamicRaceCP(JobCP[playerid]))
                JobCP[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

            if(SailRouteType[playerid] == 1)
            {
                if(SailRute[playerid] == 13) //finish
                {
                    DestroyVehicle(JobVehicle[playerid]);

                    SetPlayerPos(playerid, 723.1931,-1495.6730,1.9343);
                    SetPlayerFacingAngle(playerid, 0.0);

                    GivePlayerMoneyEx(playerid, 800);
                    ShowItemBox(playerid, "Cash", "Received $800x", 1212, 6);

                    SailRute[playerid] = -1;
                    SailRouteType[playerid] = 0;
                    SailDockTimer[playerid] = false;
                }
                else
                {
                    SailRute[playerid] ++;
                    JobCP[playerid] = CreateDynamicRaceCP(3, SailRouteLV[SailRute[playerid]][Pos][0], SailRouteLV[SailRute[playerid]][Pos][1], SailRouteLV[SailRute[playerid]][Pos][2], SailRouteLV[SailRute[playerid]+1][Pos][0], SailRouteLV[SailRute[playerid]+1][Pos][1], SailRouteLV[SailRute[playerid]+1][Pos][2], 3.5, 0, 0, playerid, 10000.00, -1, 0);
                }
            }
            else if(SailRouteType[playerid] == 2)
            {
                if(SailRute[playerid] == 13) //finish
                {
                    DestroyVehicle(JobVehicle[playerid]);

                    SetPlayerPos(playerid, 1628.0438,580.3433,1.7578);
                    SetPlayerFacingAngle(playerid, 360.0);

                    GivePlayerMoneyEx(playerid, 800);
                    ShowItemBox(playerid, "Cash", "Received $800x", 1212, 6);

                    SailRute[playerid] = -1;
                    SailRouteType[playerid] = 0;
                    SailDockTimer[playerid] = false;
                }
                else
                {
                    SailRute[playerid] ++;
                    JobCP[playerid] = CreateDynamicRaceCP(3, SailRouteLS[SailRute[playerid]][Pos][0], SailRouteLS[SailRute[playerid]][Pos][1], SailRouteLS[SailRute[playerid]][Pos][2], SailRouteLS[SailRute[playerid]+1][Pos][0], SailRouteLS[SailRute[playerid]+1][Pos][1], SailRouteLS[SailRute[playerid]+1][Pos][2], 3.5, 0, 0, playerid, 10000.00, -1, 0);
                }
            }
            
            Streamer_Update(playerid, -1);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/11;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pTakingFishTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pTakingFishTimer[playerid] = false;
            return 0;
        }

        if(!IsValidDynamicArea(Fisherman_TakeFish))
        {
            pTakingFishTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);
            TogglePlayerControllable(playerid, true);
            return 0;
        }

        if(!IsPlayerInDynamicArea(playerid, Fisherman_TakeFish))
        {
            pTakingFishTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);
            TogglePlayerControllable(playerid, true);
            return 0;
        }
        
        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pTakingFishTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 8)
        {
            pTakingFishTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            Inventory_Add(playerid, "Ikan", 1604, 2);
            ShowItemBox(playerid, "Ikan", "Received 2x", 1604, 5);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/8;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pRepairingToolkitTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pRepairingToolkitTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            return 0;
        }

        if(AccountData[playerid][pTempVehID] == INVALID_VEHICLE_ID)
        {
            pRepairingToolkitTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            return 0;
        }
        
        if(!IsValidVehicle(AccountData[playerid][pTempVehID]))
        {
            pRepairingToolkitTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            return 0;
        }
        
        if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        {
            pRepairingToolkitTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            return 0;
        }

        static Float:vX, Float:vY, Float:vZ;
        GetVehiclePos(AccountData[playerid][pTempVehID], vX, vY, vZ);
        if(!IsPlayerInRangeOfPoint(playerid, 3.5, vX, vY, vZ))
        {
            pRepairingToolkitTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 6)
        {
            pRepairingToolkitTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            StopRunningAnimation(playerid);
            HideProgressBar(playerid);

            SetValidVehicleHealth(AccountData[playerid][pTempVehID], VehicleCore[AccountData[playerid][pTempVehID]][vMaxHealth]);
            DisableVehicleSpeedCap(AccountData[playerid][pTempVehID]);

            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/6;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }
    return 1;
}

ptask UpdateTimeJob4[1000](playerid)
{
    if(pMixBetonTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pMixBetonTimer[playerid] = false;
            return 0;
        }

        if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
        {
            pMixBetonTimer[playerid] = false;
            HideProgressBar(playerid);

            AccountData[playerid][pActivityTime] = 0;
            return 0;
        }

        if(AccountData[playerid][pJob] != JOB_MIXER)
        {
            pMixBetonTimer[playerid] = false;
            HideProgressBar(playerid);

            AccountData[playerid][pActivityTime] = 0;
            return 0;
        }

        if(!IsPlayerInRangeOfPoint(playerid, 5.0, 589.4763,1245.1146,12.6529) && !IsPlayerInRangeOfPoint(playerid, 5.0, 565.0966,1252.4762,12.6899))
        {
            pMixBetonTimer[playerid] = false;
            HideProgressBar(playerid);

            AccountData[playerid][pActivityTime] = 0;
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 6)
        {
            pMixBetonTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            new statepos = random(5);
            MixerStep[playerid] = 1;

            if(DestroyDynamicRaceCP(JobCP[playerid]))
                JobCP[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

            switch(statepos)
            {
                case 0:
                {
                    MixerSlump[playerid] = 1;
                    pSlumpTimer[playerid] = true;
                    MixerPercent[playerid] = 160;
                    JobCP[playerid] = CreateDynamicRaceCP(1, 1253.7083,-1262.4938,12.8505, 1253.7083,-1262.4938,12.8505, 3.5, 0, 0, playerid, 10000.00, -1, 0); //LSGH
                }
                case 1:
                {
                    MixerSlump[playerid] = 2;
                    pSlumpTimer[playerid] = true;
                    MixerPercent[playerid] = 155;
                    JobCP[playerid] = CreateDynamicRaceCP(1, 2609.2375,837.2880,4.7698, 2609.2375,837.2880,4.7698, 3.5, 0, 0, playerid, 10000.00, -1, 0); //LVRE
                }
                case 2:
                {
                    MixerSlump[playerid] = 3;
                    pSlumpTimer[playerid] = true;
                    MixerPercent[playerid] = 160;
                    JobCP[playerid] = CreateDynamicRaceCP(1, 2420.0486,1897.8876,5.5897, 2420.0486,1897.8876,5.5897, 3.5, 0, 0, playerid, 10000.00, -1, 0); //LVSC
                }
                case 3:
                {
                    MixerSlump[playerid] = 4;
                    pSlumpTimer[playerid] = true;
                    MixerPercent[playerid] = 220;
                    JobCP[playerid] = CreateDynamicRaceCP(1, -2371.8359,2373.5081,4.0192, -2371.8359,2373.5081,4.0192, 3.5, 0, 0, playerid, 10000.00, -1, 0); //BAYSIDE
                }
                case 4:
                {
                    MixerSlump[playerid] = 5;
                    pSlumpTimer[playerid] = true;
                    MixerPercent[playerid] = 170;
                    JobCP[playerid] = CreateDynamicRaceCP(1, -2088.4290,232.4257,34.7872, -2088.4290,232.4257,34.7872, 3.5, 0, 0, playerid, 10000.00, -1, 0); //SF
                }
                default:
                {
                    MixerSlump[playerid] = 4;
                    pSlumpTimer[playerid] = true;
                    MixerPercent[playerid] = 220;
                    JobCP[playerid] = CreateDynamicRaceCP(1, -2371.8359,2373.5081,4.0192, -2371.8359,2373.5081,4.0192, 3.5, 0, 0, playerid, 10000.00, -1, 0); //BAYSIDE
                }
            }

            TextDrawShowForPlayer(playerid, JobMixTD[10]);
            SetPlayerProgressBarValue(playerid, pSlumpMeter[playerid], MixerPercent[playerid]);
            ShowPlayerProgressBar(playerid, pSlumpMeter[playerid]);

            ShowPlayerFooter(playerid, "Antarkan ~g~beton ~w~ke lokasi proyek yang ditandai dengan~n~~r~icon ~w~pada minimap anda dan jaga kualitas ~y~slump ~w~agar tidak kering", 15000);
            Streamer_Update(playerid, -1);
        }
        else
        {
            AccountData[playerid][pActivityTime]++;
            
            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/6;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);

            PlayerPlaySound(playerid, 25801, 0, 0, 0);
        }
    }

    if(pSlumpTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pSlumpTimer[playerid] = false;
            MixerPercent[playerid] = 0;
            TextDrawHideForPlayer(playerid, JobMixTD[10]);
            HidePlayerProgressBar(playerid, pSlumpMeter[playerid]);
            return 0;
        }

        if(AccountData[playerid][pJob] != JOB_MIXER)
        {
            pSlumpTimer[playerid] = false;
            MixerPercent[playerid] = 0;
            TextDrawHideForPlayer(playerid, JobMixTD[10]);
            HidePlayerProgressBar(playerid, pSlumpMeter[playerid]);
            return 0;
        }

        if(MixerPercent[playerid] > 0)
        {
            MixerPercent[playerid]--;

            if(MixerPercent[playerid] <= 0)
            {
                MixerPercent[playerid] = 0;
                pSlumpTimer[playerid] = false;
            }
            
            HidePlayerProgressBar(playerid, pSlumpMeter[playerid]);
            SetPlayerProgressBarValue(playerid, pSlumpMeter[playerid], MixerPercent[playerid]);
            ShowPlayerProgressBar(playerid, pSlumpMeter[playerid]);
        }
    }

    if(pMixerDumpTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pMixerDumpTimer[playerid] = false;
            return 0;
        }

        if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
        {
            pMixerDumpTimer[playerid] = false;
            HideProgressBar(playerid);

            AccountData[playerid][pActivityTime] = 0;
            return 0;
        }

        if(AccountData[playerid][pJob] != JOB_MIXER)
        {
            pMixerDumpTimer[playerid] = false;
            HideProgressBar(playerid);

            AccountData[playerid][pActivityTime] = 0;
            return 0;
        }

        if(!IsPlayerInDynamicRaceCP(playerid, JobCP[playerid]))
        {
            pMixerDumpTimer[playerid] = false;
            HideProgressBar(playerid);

            AccountData[playerid][pActivityTime] = 0;
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 16)
        {
            pMixerDumpTimer[playerid] = false;
            pSlumpTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            if(DestroyDynamicRaceCP(JobCP[playerid]))
                JobCP[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

            TextDrawHideForPlayer(playerid, JobMixTD[10]);
            HidePlayerProgressBar(playerid, pSlumpMeter[playerid]);

            MixerStep[playerid] = 2;

            switch(MixerSlump[playerid])
            {
                case 1:
                {
                    if(MixerPercent[playerid] > 0)
                    {
                        GivePlayerMoneyEx(playerid, 250);
                        ShowItemBox(playerid, "Cash", "Received $250x", 1212, 5);
                        ShowTDN(playerid, NOTIFICATION_WARNING, "Anda mengantarkan beton tepat waktu dengan slump yang terjaga!");
                    }
                    else
                    {
                        GivePlayerMoneyEx(playerid, 50);
                        ShowItemBox(playerid, "Cash", "Received $50x", 1212, 5);
                        ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak menjaga slump beton dengan baik!");
                    }
                }
                case 2:
                {
                    if(MixerPercent[playerid] > 0)
                    {
                        GivePlayerMoneyEx(playerid, 150);
                        ShowItemBox(playerid, "Cash", "Received $150x", 1212, 5);
                        ShowTDN(playerid, NOTIFICATION_WARNING, "Anda mengantarkan beton tepat waktu dengan slump yang terjaga!");
                    }
                    else
                    {
                        GivePlayerMoneyEx(playerid, 35);
                        ShowItemBox(playerid, "Cash", "Received $35x", 1212, 5);
                        ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak menjaga slump beton dengan baik!");
                    }
                }
                case 3:
                {
                    if(MixerPercent[playerid] > 0)
                    {
                        GivePlayerMoneyEx(playerid, 175);
                        ShowItemBox(playerid, "Cash", "Received $175x", 1212, 5);
                        ShowTDN(playerid, NOTIFICATION_WARNING, "Anda mengantarkan beton tepat waktu dengan slump yang terjaga!");
                    }
                    else
                    {
                        GivePlayerMoneyEx(playerid, 40);
                        ShowItemBox(playerid, "Cash", "Received $40x", 1212, 5);
                        ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak menjaga slump beton dengan baik!");
                    }
                }
                case 4:
                {
                    if(MixerPercent[playerid] > 0)
                    {
                        GivePlayerMoneyEx(playerid, 250);
                        ShowItemBox(playerid, "Cash", "Received $250x", 1212, 5);
                        ShowTDN(playerid, NOTIFICATION_WARNING, "Anda mengantarkan beton tepat waktu dengan slump yang terjaga!");
                    }
                    else
                    {
                        GivePlayerMoneyEx(playerid, 50);
                        ShowItemBox(playerid, "Cash", "Received $50x", 1212, 5);
                        ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak menjaga slump beton dengan baik!");
                    }
                }
                case 5:
                {
                    if(MixerPercent[playerid] > 0)
                    {
                        GivePlayerMoneyEx(playerid, 175);
                        ShowItemBox(playerid, "Cash", "Received $175x", 1212, 5);
                        ShowTDN(playerid, NOTIFICATION_WARNING, "Anda mengantarkan beton tepat waktu dengan slump yang terjaga!");
                    }
                    else
                    {
                        GivePlayerMoneyEx(playerid, 40);
                        ShowItemBox(playerid, "Cash", "Received $40x", 1212, 5);
                        ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak menjaga slump beton dengan baik!");
                    }
                }
            }

            JobCP[playerid] = CreateDynamicRaceCP(1, 572.4443,1215.7301,11.5167, 572.4443,1215.7301,11.5167, 3.5, 0, 0, playerid, 10000.00, -1, 0); //LSGH

            MixerSlump[playerid] = 0;
            ShowPlayerFooter(playerid, "Kembali ke ~b~Batching Plant ~w~untuk menyeselaikan pekerjaan", 5000);
            Streamer_Update(playerid, -1);
        }
        else
        {
            AccountData[playerid][pActivityTime]++;
            
            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/16;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);

            PlayerPlaySound(playerid, 12600, 0, 0, 0);
        }
    }

    if(pSellingTurtleTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pSellingTurtleTimer[playerid] = false;
            return 0;
        }

        if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        {
            pSellingTurtleTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;
            return 0;
        }

        if(!IsPlayerInRangeOfPoint(playerid, 3.5, 2161.5310,-103.1758,2.7500))
        {
            pSellingTurtleTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= AccountData[playerid][pCountingValue])
        {
            pSellingTurtleTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);
        }
        else
        {
            AccountData[playerid][pActivityTime]++;
            
            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/AccountData[playerid][pCountingValue];
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);

            Inventory_Remove(playerid, "Penyu");
            ShowItemBox(playerid, "Penyu", "Removed 1x", 1609, 4);
            ShowItemBox(playerid, "Dirty Money", "Received $150.00x", 1550, 5);

            GivePlayerDirtyMoney(playerid, 150);
            SendClientMessageEx(playerid, -1, "[i] Uang kotor bertambah "RED"+$150 "WHITE"(Total: "RED"$%s"WHITE").", FormatMoney(AccountData[playerid][pDirtyMoney]));
        }
    }

    if(pSellingSharkTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pSellingSharkTimer[playerid] = false;
            return 0;
        }

        if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        {
            pSellingSharkTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;
            return 0;
        }

        if(!IsPlayerInRangeOfPoint(playerid, 3.5, -489.2872,613.1413,1.7813))
        {
            pSellingSharkTimer[playerid] = false;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= AccountData[playerid][pCountingValue])
        {
            pSellingSharkTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);
        }
        else
        {
            AccountData[playerid][pActivityTime]++;
            
            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/AccountData[playerid][pCountingValue];
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);

            Inventory_Remove(playerid, "Hiu");
            ShowItemBox(playerid, "Hiu", "Removed 1x", 1608, 1);
            ShowItemBox(playerid, "Dirty Money", "Received $550x", 1550, 2);

            GivePlayerDirtyMoney(playerid, 550);
            SendClientMessageEx(playerid, -1, "[i] Uang kotor bertambah "RED"+$550 "WHITE"(Total: "RED"$%s"WHITE").", FormatMoney(AccountData[playerid][pDirtyMoney]));
        }
    }

    if(p_BankRTakeMoneyTimer[playerid])
    {
        if(!IsPlayerConnected(playerid))
        {
            p_BankRTakeMoneyTimer[playerid] = false;
            return 0;
        }

        if(!IsValidDynamicCP(p_BankRobberyCP[playerid]))
        {
            p_BankRTakeMoneyTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);
            return 0;
        }

        if(!IsPlayerInDynamicCP(playerid, p_BankRobberyCP[playerid]))
        {
            p_BankRTakeMoneyTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 31)
        {
            p_BankRTakeMoneyTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pThirst]--;
            AccountData[playerid][pHunger]--;
            AccountData[playerid][pStress]++;

            if(DestroyDynamicCP(p_BankRobberyCP[playerid]))
                p_BankRobberyCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

            if(p_BankRobberyStep[playerid] == 4)
            {
                new randcash = RandomEx(42000, 56000);
                GivePlayerDirtyMoney(playerid, randcash);

                ShowItemBox(playerid, "Dirty Money", sprintf("Received $%sx", FormatMoney(randcash)), 1550, 5);
                ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Anda mendapatkan hasil rampokan bank pacfic sebesar ~g~+$%s.", FormatMoney(randcash)));

                AccountData[playerid][pDuringBRobbery] = false;
                p_BankRobberyStep[playerid] = 0;
            }
            else
            {
                p_BankRobberyStep[playerid]++;

                switch(p_BankRobberyStep[playerid])
                {
                    case 2:
                    {
                        p_BankRobberyCP[playerid] = CreateDynamicCP(1444.0125,-1119.6868,23.9590, 1.5, 0, 0, playerid, 5.5, -1, 0);
                    }
                    case 3:
                    {
                        p_BankRobberyCP[playerid] = CreateDynamicCP(1441.4429,-1121.0752,23.9590, 1.5, 0, 0, playerid, 5.5, -1, 0);
                    }
                    case 4:
                    {
                        p_BankRobberyCP[playerid] = CreateDynamicCP(1443.0812,-1120.4921,23.9590, 1.5, 0, 0, playerid, 5.5, -1, 0);
                    }
                }
            }
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/31;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pMakeEfedrinTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pMakeEfedrinTimer[playerid] = false;
            return 0;
        }

        if(!IsPlayerNearEfedrinMake(playerid))
        {
            pMakeEfedrinTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pMakeEfedrinTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 11)
        {
            pMakeEfedrinTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            Inventory_Add(playerid, "Efedrin", 11748);
            ShowItemBox(playerid, "Efedrin", "Received 1x", 11748, 5);

            AccountData[playerid][pThirst]--;
            AccountData[playerid][pHunger]--;
            AccountData[playerid][pStress]++;

            SendTeamMessage(FACTION_LSPD, 0xff4b4bff, "> Pembuatan sabu sedang berlangsung <");
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/11;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pMakeStimulanTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pMakeStimulanTimer[playerid] = false;
            return 0;
        }

        if(!IsPlayerNearEfedrinMix(playerid))
        {
            pMakeStimulanTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);
            return 0;
        }

        if(!PlayerHasItem(playerid, "Efedrin"))
        {
            pMakeStimulanTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Efedrin!");
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pMakeStimulanTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 16)
        {
            pMakeStimulanTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);
            
            Inventory_Remove(playerid, "Efedrin");
            Inventory_Add(playerid, "Stimulan", 19874, 2);
            ShowItemBox(playerid, "Efedrin", "Removed 1x", 11748, 4);
            ShowItemBox(playerid, "Stimulan", "Received 2x", 19874, 5);

            AccountData[playerid][pThirst]--;
            AccountData[playerid][pHunger]--;
            AccountData[playerid][pStress]++;

            SendTeamMessage(FACTION_LSPD, 0xff4b4bff, "> Pembuatan sabu sedang berlangsung <");
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/16;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pMakeMethMentahTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pMakeMethMentahTimer[playerid] = false;
            return 0;
        }

        if(!IsPlayerInRangeOfPoint(playerid, 3.0, -1429.6238,-941.1603,202.4961))
        {
            pMakeMethMentahTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);
            return 0;
        }

        if(Inventory_Count(playerid, "Stimulan") < 2)
        {
            pMakeMethMentahTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup stimulan! (Min: 2)");
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pMakeMethMentahTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 16)
        {
            pMakeMethMentahTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);
            
            Inventory_Remove(playerid, "Stimulan", 2);
            Inventory_Add(playerid, "Sabu Kristal", 2866);
            ShowItemBox(playerid, "Stimulan", "Removed 2x", 19874, 4);
            ShowItemBox(playerid, "Sabu Kristal", "Received 1x", 2866, 5);

            AccountData[playerid][pThirst]--;
            AccountData[playerid][pHunger]--;
            AccountData[playerid][pStress]++;

            SendTeamMessage(FACTION_LSPD, 0xff4b4bff, "> Pembuatan sabu sedang berlangsung <");
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/16;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }
    if(pMakeMethTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pMakeMethTimer[playerid] = false;
            return 0;
        }

        if(!IsPlayerInRangeOfPoint(playerid, 3.0, -1635.0948,-2233.9541,31.4765))
        {
            pMakeMethTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);
            return 0;
        }

        if(!PlayerHasItem(playerid, "Jerigen"))
        {
            pMakeMethTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki jerigen!");
            return 0;
        }

        if(Inventory_Count(playerid, "Sabu Kristal") < 2)
        {
            pMakeMethTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup sabu kristal! (Min: 2)");
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pMakeMethTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 16)
        {
            pMakeMethTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);
            
            Inventory_Remove(playerid, "Jerigen");
            Inventory_Remove(playerid, "Sabu Kristal", 2);
            Inventory_Add(playerid, "Sabu", 1575);

            ShowItemBox(playerid, "Jerigen", "Removed 1x", 1650, 5);
            ShowItemBox(playerid, "Sabu Kristal", "Removed 2x", 2866, 6);
            ShowItemBox(playerid, "Sabu", "Received 1x", 1575, 7);

            AccountData[playerid][pThirst]--;
            AccountData[playerid][pHunger]--;
            AccountData[playerid][pStress]++;

            SendTeamMessage(FACTION_LSPD, 0xff4b4bff, "> Pembuatan sabu sedang berlangsung <");
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/16;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }
    return 1;
}

ptask UpdateTimeJob5[1000](playerid) 
{
    if(pTakingWoolTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pTakingWoolTimer[playerid] = false;
            return 0;
        }

        if(!IsPlayerInDynamicArea(playerid, Penjahit_TakeWoolArea))
        {
            pTakingWoolTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);
            return 0;
        }
        
        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pTakingWoolTimer[playerid] = false;

            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 6)
        {
            pTakingWoolTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            Inventory_Add(playerid, "Wool", 1974, 3);
            ShowItemBox(playerid, "Wool", "Received 3x", 1974, 4);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            PlayerPlaySound(playerid, 20802, 0.0, 0.0, 0.0);

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/6;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pMakingFabricTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pMakingFabricTimer[playerid] = false;
            return 0;
        }

        if(!IsPlayerInFabricArea(playerid))
        {
            pMakingFabricTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pMakingFabricTimer[playerid] = false;

            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(Inventory_Count(playerid, "Wool") < 5)
        {
            pMakingFabricTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Wool anda tidak cukup! (Min: 5)");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 11)
        {
            pMakingFabricTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            Inventory_Remove(playerid, "Wool", 5);
            Inventory_Add(playerid, "Kain", 11747, 5);

            ShowItemBox(playerid, "Wool", "Removed 5x", 1974, 4);
            ShowItemBox(playerid, "Kain", "Received 5x", 11747, 5);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            PlayerPlaySound(playerid, 32401, 0.0, 0.0, 0.0);

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/11;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pClothingTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pClothingTimer[playerid] = false;
            return 0;
        }

        if(!IsPlayerInClothingArea(playerid))
        {
            pClothingTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pClothingTimer[playerid] = false;

            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(Inventory_Count(playerid, "Kain") < 5)
        {
            pClothingTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Kain anda tidak cukup! (Min: 5)");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 6)
        {
            pClothingTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            Inventory_Remove(playerid, "Kain", 5);
            Inventory_Add(playerid, "Pakaian", 2399, 5);

            ShowItemBox(playerid, "Kain", "Removed 5x", 11747, 4);
            ShowItemBox(playerid, "Pakaian", "Received 5x", 2399, 5);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            PlayerPlaySound(playerid, 4400, 0.0, 0.0, 0.0);

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/6;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
        }
    }

    if(pTakingSusuTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pTakingSusuTimer[playerid] = false;
            return 0;
        }

        if(!IsValidDynamicArea(PlayerMilkerVars[playerid][MilkerTakeArea]))
        {
            pTakingSusuTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            return 0;
        }

        if(!IsPlayerInDynamicArea(playerid, PlayerMilkerVars[playerid][MilkerTakeArea]))
        {
            pTakingSusuTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pTakingSusuTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 6)
        {
            pTakingSusuTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(5 * GetItemWeight("Susu"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");

            Inventory_Add(playerid, "Susu", 19570, 5);
            ShowItemBox(playerid, "Susu", "Received 5x", 19570, 5);

            if(DestroyDynamicObject(PlayerMilkerVars[playerid][CowObject]))
                PlayerMilkerVars[playerid][CowObject] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
            if(DestroyDynamicArea(PlayerMilkerVars[playerid][MilkerTakeArea]))
                PlayerMilkerVars[playerid][MilkerTakeArea] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;

            PlayerMilkerVars[playerid][MilkTaken]++;
            if(PlayerMilkerVars[playerid][MilkTaken] == 10)
            {
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah selesai melakukan pekerjaan.");
                AccountData[playerid][pIsUsingUniform] = false;
		        SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
            }
            else
            {
                new rand = random(sizeof(CowSpawn));
                PlayerMilkerVars[playerid][CowObject] = CreateDynamicObject(19833, CowSpawn[rand][0], CowSpawn[rand][1], CowSpawn[rand][2], CowSpawn[rand][3], CowSpawn[rand][4], CowSpawn[rand][5], 0, 0, playerid, 300.00, 300.00); 
                PlayerMilkerVars[playerid][MilkerTakeArea] = CreateDynamicSphere(CowSpawn[rand][0], CowSpawn[rand][1], CowSpawn[rand][2], 2.2, 0, 0, playerid);
            }
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/6;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);

            PlayerPlaySound(playerid, 25801, 0, 0, 0);
        }
    }

    if(pProcessSusuTimer[playerid])
    {
        if(!IsPlayerConnected(playerid)) 
        {
            pProcessSusuTimer[playerid] = false;
            return 0;
        }

        if(!IsPlayerInMilkerProcess(playerid))
        {
            pProcessSusuTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            return 0;
        }

        if(Inventory_Count(playerid, "Susu") < 10)
        {
            pProcessSusuTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            ShowTDN(playerid, NOTIFICATION_ERROR, "Susu tidak cukup! (Min: 10)");
            return 0;
        }

        if(Inventory_Count(playerid, "Botol") < 5)
        {
            pProcessSusuTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            ShowTDN(playerid, NOTIFICATION_ERROR, "Botol tidak cukup! (Min: 5)");
            return 0;
        }

        if(GetTotalWeightFloat(playerid) >= GetPlayerInventoryWeight(playerid))
        {
            pProcessSusuTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
            return 0;
        }

        if(AccountData[playerid][pActivityTime] >= 16)
        {
            pProcessSusuTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            Inventory_Remove(playerid, "Susu", 10);
            Inventory_Remove(playerid, "Botol", 5);
            Inventory_Add(playerid, "Susu Fermentasi", 19569, 10);

            ShowItemBox(playerid, "Botol", "Removed 5x", 19570, 5);
            ShowItemBox(playerid, "Susu","Removed 10x", 19570, 6);
            ShowItemBox(playerid, "Susu Fermentasi", "Received 10x", 19569, 7);
        }
        else
        {
            AccountData[playerid][pActivityTime] ++;

            static Float:progressvalue;
            progressvalue = AccountData[playerid][pActivityTime] * 102.0/16;
            PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
            PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);

            PlayerPlaySound(playerid, 20803, 0, 0, 0);
        }
    }
    return 1;
}

ptask UpdateLevelTimer[1000](playerid) 
{
    if(AccountData[playerid][pSpawned])
    {
        if(!AccountData[playerid][pIsAFK])
        {
            AccountData[playerid][pLoginTime]++;
            AccountData[playerid][pSeconds]++;
            if(AccountData[playerid][pSeconds] == 60)
            {
                new scoremath = ((AccountData[playerid][pLevel])*5);

                AccountData[playerid][pMinutes]++;
                AccountData[playerid][pSeconds] = 0;
                
                if(AccountData[playerid][pMinutes] == 60)
                {
                    AccountData[playerid][pHours] ++;
                    AccountData[playerid][pMinutes] = 0;
                }

                if(AccountData[playerid][pHours] >= scoremath && AccountData[playerid][pLevel] < 1000)
                {
                    static string[144];
                    AccountData[playerid][pLevel] ++;
                    SetPlayerScore(playerid, AccountData[playerid][pLevel]);
                    format(string,sizeof(string),"~g~Level Up!~n~~w~Anda sekarang level ~y~%d", AccountData[playerid][pLevel]);
                    GameTextForPlayer(playerid, string, 8000, 1);

                    format(string, sizeof(string), "[Level Up] "RED"%s(%d) "WHITE"telah mencapai "YELLOW"level %d, "WHITE"selamat ya!", AccountData[playerid][pName], playerid, AccountData[playerid][pLevel]);
                    foreach(new i : Player) if(AccountData[i][pSpawned] && ToggleInfo[i][TogLevel])
                    {
                        SendClientMessage(i, X11_LIGHTBLUE, string);
                    }
                }
            }
        }
    }
    return 1;
}

ptask OnPlayerFallFromInterior[1000](playerid) 
{
    if(AccountData[playerid][pSpawned] && AccountData[playerid][pInDoor] != -1 && !AccountData[playerid][pIsFallFromInterior])
    {
        new Float:vpos[3];
        GetPlayerVelocity(playerid, vpos[0], vpos[1], vpos[2]);
		if(vpos[2] <= -0.6)
		{
            AccountData[playerid][pIsFallFromInterior] = true;
            TogglePlayerControllable(playerid, false);
            Dialog_Show(playerid, "InteriorFall", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Fall from Interior", 
            ""ORANGE"Sistem kami mendeteksi bahwa karakter anda dalam masalah, yaitu terjatuh dari map.\n\
            Kami akan mencoba untuk mengembalikan ke posisi yang benar. Mohon pilih salah satu dari pilihan berikut\n\
            untuk menyelesaikan masalah yang anda alami, interior artinya karakter akan dikembalikan ke dalam map/bangunan\n\
            Sedangkan exterior untuk mengembalikan karakter anda ke luar pintu masuk map/bangunan.", "Interior", "Exterior");
		}
    }
    return 1;
}

new stressseconds;
ptask PlayerStressRadom[5555](playerid) 
{
    if(AccountData[playerid][pSpawned])
    {
        stressseconds++;
        if(AccountData[playerid][pStress] >= 60 && AccountData[playerid][pStress] < 70 && stressseconds == 8)
        {
            stressseconds = 0;
            new rand = random(2);
            if(rand == 0) //kiri
            {
                if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && IsVehicleMoving(GetPlayerVehicleID(playerid)))
                {
                    ShowStressEffectTD(playerid);
                    AccountData[playerid][pStressedTime] = 10;
                    new Float:angle;
                    GetVehicleZAngle(SavingVehID[playerid], angle);
                    SetVehicleZAngle(SavingVehID[playerid], angle - 5.0);
                    SetVehicleAngularVelocity(SavingVehID[playerid], 0, 0, -0.07);
                }
            }
            else //kanan
            {
                if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && IsVehicleMoving(GetPlayerVehicleID(playerid)))
                {
                    ShowStressEffectTD(playerid);
                    AccountData[playerid][pStressedTime] = 10;
                    new Float:angle;
                    GetVehicleZAngle(SavingVehID[playerid], angle);
                    SetVehicleZAngle(SavingVehID[playerid], angle + 5.0);
                    SetVehicleAngularVelocity(SavingVehID[playerid], 0, 0, 0.07);
                }
            }

            if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
            {
                ShowStressEffectTD(playerid);
                AccountData[playerid][pStressedTime] = 10;
		        TogglePlayerControllable(playerid, false);
                ApplyAnimation(playerid, "CRACK", "crckdeth4", 4.0, false, false, false, true, 0, true);
            }
        }
        else if(AccountData[playerid][pStress] >= 70 && AccountData[playerid][pStress] < 75 && stressseconds == 4)
        {
            stressseconds = 0;
            new rand = random(2);
            if(rand == 0) //kiri
            {
                if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && IsVehicleMoving(GetPlayerVehicleID(playerid)))
                {
                    ShowStressEffectTD(playerid);
                    AccountData[playerid][pStressedTime] = 10;
                    new Float:angle;
                    GetVehicleZAngle(SavingVehID[playerid], angle);
                    SetVehicleZAngle(SavingVehID[playerid], angle - 5.0);
                    SetVehicleAngularVelocity(SavingVehID[playerid], 0, 0, -0.07);
                }
            }
            else //kanan
            {
                if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && IsVehicleMoving(GetPlayerVehicleID(playerid)))
                {
                    ShowStressEffectTD(playerid);
                    AccountData[playerid][pStressedTime] = 10;
                    new Float:angle;
                    GetVehicleZAngle(SavingVehID[playerid], angle);
                    SetVehicleZAngle(SavingVehID[playerid], angle + 5.0);
                    SetVehicleAngularVelocity(SavingVehID[playerid], 0, 0, 0.07);
                }
            }

            if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
            {
                ShowStressEffectTD(playerid);
                AccountData[playerid][pStressedTime] = 10;
		        TogglePlayerControllable(playerid, false);
                ApplyAnimation(playerid, "CRACK", "crckdeth4", 4.0, false, false, false, true, 0, true);
            }
        }
        else if(AccountData[playerid][pStress] >= 75 && stressseconds == 2)
        {
            stressseconds = 0;
            new rand = random(2);
            if(rand == 0) //kiri
            {
                if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && IsVehicleMoving(GetPlayerVehicleID(playerid)))
                {
                    ShowStressEffectTD(playerid);
                    AccountData[playerid][pStressedTime] = 3;
                    new Float:angle;
                    GetVehicleZAngle(SavingVehID[playerid], angle);
                    SetVehicleZAngle(SavingVehID[playerid], angle - 5.0);
                    SetVehicleAngularVelocity(SavingVehID[playerid], 0, 0, -0.07);
                }
            }
            else //kanan
            {
                if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && IsVehicleMoving(GetPlayerVehicleID(playerid)))
                {
                    ShowStressEffectTD(playerid);
                    AccountData[playerid][pStressedTime] = 3;
                    new Float:angle;
                    GetVehicleZAngle(SavingVehID[playerid], angle);
                    SetVehicleZAngle(SavingVehID[playerid], angle + 5.0);
                    SetVehicleAngularVelocity(SavingVehID[playerid], 0, 0, 0.07);
                }
            }

            if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
            {
                ShowStressEffectTD(playerid);
                AccountData[playerid][pStressedTime] = 3;
		        TogglePlayerControllable(playerid, false);
                ApplyAnimation(playerid, "CRACK", "crckdeth4", 4.0, false, false, false, true, 0, true);
            }
        }
    }
    return 1;
}