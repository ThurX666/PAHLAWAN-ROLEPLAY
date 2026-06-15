#include <YSI_Coding\y_hooks>

new Float:GarbagePointPos[][3] = {
    {2118.7366,1425.3243,10.8203},
    {2131.5320,1425.3242,10.8203},
    {2129.4282,1764.9672,10.8203},
    {2308.6060,1764.9413,10.8203},
    {2480.1077,1781.4598,10.8203},
    {2558.3433,1771.2291,11.0234},
    {2495.5574,1912.4700,10.8203},
    {2310.6943,2053.4197,10.8281},
    {1979.6300,2069.0845,10.8203},
    {1979.6282,2083.1213,10.8203},
    {1881.4550,2123.5146,10.8203},
    {1983.9133,2495.3406,10.8570},
    {2174.3430,2514.5466,10.8203},
    {2223.4089,2564.7190,10.8130},
    {2354.9377,2568.7637,10.8203},
    {2420.3792,2786.2102,10.8203},
    {2210.8943,2724.6865,10.8203},
    {2160.2109,2836.7676,10.8203},
    {1780.7230,2765.6233,11.3509},
    {1422.6002,2880.2622,10.8203},
    {1260.6505,2673.2549,10.8203},
    {1098.7792,2302.0127,10.8203},
    {1054.7175,2207.4194,10.8203},
    {1140.2617,1978.1647,10.8203},
    {1355.8729,1911.6136,10.8203},
    {1895.9374,1284.2408,10.8203},
    {1735.2896,1166.7733,10.8203},
    {1529.1226,1016.8629,10.8203},
    {1419.1816,1126.2207,10.8203},
    {1015.6996,1231.9285,10.8125},
    {1023.3309,1480.4663,5.8203},
    {1056.0392,1841.1210,10.8203},
    {1512.5790,2070.0237,10.8203},
    {1610.8342,2240.9136,10.8203},
    {1642.1013,2366.2227,10.8203},
    {1892.2719,2636.0535,10.8203},
    {1679.1840,2759.3521,10.8203},
    {1619.8757,2780.9749,10.8203},
    {1461.5017,2611.0210,10.8203},
    {1085.0845,2377.1772,10.8203},
    {915.6999,2140.8391,10.8203},
    {965.6270,1868.9125,10.8203},
    {1416.1083,970.4255,10.8130},
    {1648.1653,885.3669,10.8203},
    {1891.7678,1181.4043,10.8281},
    {2018.5371,1211.1583,10.8130},
    {2175.6296,1265.1184,10.8203},
    {2475.6304,1349.8522,10.8203},
    {2489.6152,1450.5732,10.9063},
    {2599.1072,1600.1101,10.8203}
};

new TrashCollectorVeh[4],
    TrashCollectorPlayerVeh[MAX_PLAYERS],
    TrashCollectorHoldingBag[MAX_PLAYERS],
    TrashCollected[MAX_PLAYERS],
    TrashCollectorLeavingTime[MAX_PLAYERS],
    selectedGarbage[MAX_PLAYERS][sizeof(GarbagePointPos)],
    STREAMER_TAG_CP: TrashCollectorCP[MAX_PLAYERS][25],
    STREAMER_TAG_CP: TrashCollectorRVehCP[MAX_PLAYERS],
    STREAMER_TAG_CP: TrashCollectorBackCP[MAX_PLAYERS],
    STREAMER_TAG_MAP_ICON: TrashCollectorIcon[MAX_PLAYERS][25];

hook OnGameModeInit()
{
    TrashCollectorVeh[0] = AddStaticVehicleEx(408,1090.7152,1229.4314,11.3686,90.1503,16,16,60000,false);
	TrashCollectorVeh[1] = AddStaticVehicleEx(408,1090.7152,1240.4314,11.3686,90.1503,16,16,60000,false);
	TrashCollectorVeh[2] = AddStaticVehicleEx(408,1090.7152,1251.4314,11.3686,90.1503,16,16,60000,false);
	TrashCollectorVeh[3] = AddStaticVehicleEx(408,1090.7152,1262.4314,11.3686,90.1503,16,16,60000,false);

    static string[144];
    for(new x; x < sizeof(TrashCollectorVeh);x++)
    {
        format(string, sizeof(string), "{E75480}TSH-%d", x+1);
        SetVehicleNumberPlate(TrashCollectorVeh[x], string);
        SetTimerEx("RespawnPV", 1000, false, "d", TrashCollectorVeh[x]);
    }

    CreateDynamicPickup(1239, 23, 1057.8223,1240.6493,10.8275, 0, 0, -1, 30.00, -1, 0);
    CreateDynamic3DTextLabel("[ Trash Collector Sidejob Point ]", 0xFF99A4FF, 1057.8223,1240.6493,10.8275+0.5, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 10.00, -1, 0);
    return 1;
}

hook OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP:checkpointid)
{
    if(AccountData[playerid][pSideJob] == SIDEJOB_TRASHCOLLECTOR)
    {
        if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
        {
            if(checkpointid == TrashCollectorBackCP[playerid])
            {
                if(TrashCollectorHoldingBag[playerid])
                {
                    if(DestroyDynamicCP(TrashCollectorBackCP[playerid]))
                        TrashCollectorBackCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    gPlayerUsingLoopingAnim[playerid] = false;
                    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
                    RemovePlayerAttachedObject(playerid, 9);
                    StopRunningAnimation(playerid);
                    TrashCollectorHoldingBag[playerid] = false;
                    TrashCollected[playerid]++;
                    ShowPlayerFooter(playerid, sprintf("~y~%d/15 ~w~Trash collected", TrashCollected[playerid]), 5000);

                    if(TrashCollected[playerid] >= 15)
                    {
                        if(DestroyDynamicCP(TrashCollectorRVehCP[playerid]))
                            TrashCollectorRVehCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                        TrashCollectorRVehCP[playerid] = CreateDynamicCP(1086.9010,1306.3644,11.3549, 5.0, 0, 0, playerid, 10000.00, -1, 0);

                        ShowTDN(playerid, NOTIFICATION_INFO, "Sidejob tukang sampah telah selesai, kembalikan kendaraan untuk bonus.");
                    }

                    ApplyAnimation(playerid, "GRENADE", "WEAPON_THROWU", 4.0, 0, 0, 0, 0, 0, true); //dekat

                    PlayerPlaySound(playerid, 5205, 0.0, 0.0, 0.0);
                }
            }

            for(new x; x < 15; x++)
            {
                if(checkpointid == TrashCollectorCP[playerid][x])
                {
                    if(!TrashCollectorHoldingBag[playerid])
                    {
                        if(DestroyDynamicCP(TrashCollectorCP[playerid][x]))
                            TrashCollectorCP[playerid][x] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                        if(DestroyDynamicMapIcon(TrashCollectorIcon[playerid][x]))
                            TrashCollectorIcon[playerid][x] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;

                        selectedGarbage[playerid][x] = -1;

                        if(DestroyDynamicCP(TrashCollectorBackCP[playerid]))
                            TrashCollectorBackCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                        
                        TrashCollectorHoldingBag[playerid] = true;

                        static Float:vbx, Float:vby, Float:vbz;
                        GetVehicleBoot(TrashCollectorPlayerVeh[playerid], vbx, vby, vbz);
                        TrashCollectorBackCP[playerid] = CreateDynamicCP(vbx, vby, vbz, 1.5, 0, 0, playerid, 10000.00, -1, 0);

                        PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);

                        SetPlayerAttachedObject(playerid, 9, 1264, 6, 0.260999, -0.156999, 0.042999, 98.499954, -103.600120, 21.199995, 0.605000, 0.482000, 0.942000);

                        ApplyAnimation(playerid, "BAR", "Barserve_give", 4.1, false, false, false, false, 0, true);
                    }
                }
            }
        }

        if(IsPlayerInVehicle(playerid, TrashCollectorPlayerVeh[playerid]))
        {
            if(checkpointid == TrashCollectorRVehCP[playerid])
            {
                TrashCollectorHoldingBag[playerid] = false;
                TrashCollectorLeavingTime[playerid] = 0;
                AccountData[playerid][pSideJob] = SIDEJOB_NONE;
                TrashCollected[playerid] = 0;

                for (new i; i < 15; i++) 
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

                if(DestroyDynamicCP(TrashCollectorRVehCP[playerid]))
                    TrashCollectorRVehCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                if(DestroyDynamicCP(TrashCollectorBackCP[playerid]))
                    TrashCollectorBackCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                GivePlayerMoneyEx(playerid, 1000);

                ShowItemBox(playerid, "Cash", "Received $1,000x", 1212, 1);

                PlayerPlaySound(playerid, 183, 0.0, 0.0, 0.0);
                GameTextForPlayer(playerid, "mission passed!~n~~w~$1,000", 8900, 0);
                SetTimerEx("StopMissPassed", 8000, false, "i", playerid);
            }
        }
    }
    return 1;
}

IsATrashCollectorSidejobVeh(carid)
{
	for(new v; v < sizeof(TrashCollectorVeh); v++) 
	{
	    if(carid == TrashCollectorVeh[v]) return 1;
	}
	return 0;
}

IsGarbageSelected(playerid, trashIdx)
{
    for (new i = 0; i < 15; i++)
    {
        if (selectedGarbage[playerid][i] == trashIdx)
        {
            return true;
        }
    }
    return false;
}

StartTrashCollectorSidejob(playerid)
{
    if(DestroyDynamicCP(TrashCollectorRVehCP[playerid]))
	    TrashCollectorRVehCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

    if(DestroyDynamicCP(TrashCollectorBackCP[playerid]))
        TrashCollectorBackCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

    for(new i = 0; i < 15; i++)
    {
        new randomTrashIdx;
        do {
            randomTrashIdx = random(sizeof(GarbagePointPos));
        } while (IsGarbageSelected(playerid, randomTrashIdx));
        
        selectedGarbage[playerid][i] = randomTrashIdx;

        if(DestroyDynamicCP(TrashCollectorCP[playerid][i]))
            TrashCollectorCP[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

        if(DestroyDynamicMapIcon(TrashCollectorIcon[playerid][i]))
            TrashCollectorIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        TrashCollectorCP[playerid][i] = CreateDynamicCP(GarbagePointPos[selectedGarbage[playerid][i]][0], GarbagePointPos[selectedGarbage[playerid][i]][1], GarbagePointPos[selectedGarbage[playerid][i]][2], 1.5, 0, 0, playerid, 15.00, -1, 0);
        TrashCollectorIcon[playerid][i] = CreateDynamicMapIcon(GarbagePointPos[selectedGarbage[playerid][i]][0], GarbagePointPos[selectedGarbage[playerid][i]][1], GarbagePointPos[selectedGarbage[playerid][i]][2], 0, Y_RED, 0, 0, playerid, 10000.00, MAPICON_GLOBAL, -1, 0);
    }

    TrashCollectorHoldingBag[playerid] = false;
    TrashCollected[playerid] = 0;
    AccountData[playerid][pSideJob] = SIDEJOB_TRASHCOLLECTOR;

    TrashCollectorPlayerVeh[playerid] = GetPlayerVehicleID(playerid);

    ShowPlayerFooter(playerid, "~g~Sidejob Tukang Sampah: ~w~Pungutlah ~y~15 sampah~n~~w~ke tempat yang telah ditandai dengan ~r~icon ~w~pada map anda!", 15000);
    return 1;
}

ptask UpdateTrashCollectorSidejob[1000](playerid) 
{
    if(TrashCollectorLeavingTime[playerid] > 0)
    {
        TrashCollectorLeavingTime[playerid]--;

        static string[128];
        format(string, sizeof(string), "~y~Kembali ke kendaraan~n~~r~%d detik", TrashCollectorLeavingTime[playerid]);
        GameTextForPlayer(playerid, string, 1200, 6);
        PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);

        if(TrashCollectorLeavingTime[playerid] <= 0)
        {
            TrashCollectorHoldingBag[playerid] = false;
            TrashCollectorLeavingTime[playerid] = 0;
            AccountData[playerid][pSideJob] = SIDEJOB_NONE;
            TrashCollected[playerid] = 0;

            if(DestroyDynamicCP(TrashCollectorRVehCP[playerid]))
			    TrashCollectorRVehCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

            if(DestroyDynamicCP(TrashCollectorBackCP[playerid]))
                TrashCollectorBackCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

            for (new i; i < 15; i++) 
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

            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak kembali ke kendaraan, sidejob trash collector digagalkan.");
        }
    }
    return 1;   
}