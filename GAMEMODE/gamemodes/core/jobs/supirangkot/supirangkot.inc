#include <YSI_Coding\y_hooks>

new AngkotRute[MAX_PLAYERS],
    AngkotRouteType[MAX_PLAYERS],
    bool:AngkotPenumpang[MAX_PLAYERS],
    STREAMER_TAG_ACTOR:AngkotActor[MAX_PLAYERS];

enum e_angkotrote
{
    Float:Pos[3],
    Float:ActorPos[4]
};

new Angkot25Route[][e_angkotrote] =
{
    {{1684.9834,-1545.1239,13.4926}, {1683.6769,-1540.8846,13.5469,268.1926}}, 
    {{1671.6582,-1595.2448,13.4990}, {1676.2362,-1598.8765,13.5469,90.8440}}, 
    {{1860.7517,-1614.7878,13.5052}, {1865.7803,-1619.1777,13.5391,88.9640}}, 
    {{1938.7078,-1686.4507,13.4955}, {1935.0348,-1689.4596,13.5469,358.1200}},  
    {{2026.4272,-1754.9050,13.4983}, {2030.2961,-1759.1062,13.5469,88.6508}},  
    {{2167.9629,-1755.1226,13.5003}, {2171.8872,-1759.0854,13.5487,92.7241}},  
    {{2244.6941,-1735.0415,13.4983}, {2249.2651,-1739.1581,13.5469,89.2774}},  
    {{2410.9211,-1767.2651,13.4996}, {2407.0532,-1772.3701,13.5391,359.0600}}, 
    {{2398.0637,-1969.5056,13.4964}, {2392.2764,-1965.3730,13.5469,268.8191}}, 
    {{2213.8169,-2008.7249,13.4418}, {2211.7073,-2015.0837,13.5469,26.3202}},  
    {{2243.5752,-2116.5190,13.4267}, {2237.2161,-2117.0786,13.5391,315.8195}}, 
    {{2184.4370,-2147.2615,13.4813}, {2184.0776,-2141.4219,13.5469,227.7721}}, 
    {{2011.7590,-2107.2361,13.5219}, {2008.0852,-2103.0264,13.5469,271.9524}}, 
    {{1947.0134,-2164.1113,13.5181}, {1941.9449,-2160.9822,13.5542,270.6992}},  
    {{1825.6011,-2135.4805,13.4981}, {1829.0406,-2131.1326,13.5469,180.4582}}, 
    {{1858.5955,-2055.2302,13.4960}, {1862.4753,-2058.1338,13.5469,88.3375}}, 
    {{1964.3888,-2004.8970,13.4957}, {1967.7136,-2001.9407,13.5469,179.5183}}, 
    {{1964.1763,-1788.8846,13.4981}, {1967.6628,-1783.7426,13.5469,180.1449}}, 
    {{1944.4612,-1727.8751,13.4964}, {1947.3903,-1723.6904,13.5469,180.7716}}, 
    {{1925.8668,-1609.5269,13.5001}, {1920.5002,-1606.4227,13.5469,270.3857}}, 
    {{1731.9078,-1594.0587,13.4869}, {1728.1548,-1589.9409,13.5429,255.6590}}, 
    {{1660.5300,-1513.0024,13.4980}, {1663.8033,-1509.1953,13.5469,182.0250}}, 
    {{1700.6780,-1480.2180,13.4898}, {0.0,0.0,0.0,0.0}}
};

new Angkot36Route[][e_angkotrote] =
{
    {{1654.5988,-1564.4122,13.5036}, {1652.5109,-1568.1786,13.5469,359.7531}}, 
    {{1686.3066,-1671.7349,13.5076}, {1683.8049,-1675.3798,13.5469,1.1317}}, 
    {{1724.6000,-1817.3027,13.4813}, {1727.4653,-1820.6829,13.5469,72.8711}}, 
    {{1818.5909,-1909.6052,13.5051}, {1816.1130,-1913.5529,13.5513,359.5518}},  
    {{1914.9946,-1935.5400,13.5088}, {1918.6938,-1937.8425,13.5408,90.8726}},  
    {{1995.3687,-2113.0833,13.4429}, {1999.2375,-2115.6392,13.5469,91.2428}},  
    {{2219.7961,-2148.9326,13.4983}, {2224.1204,-2147.6013,13.5469,134.7243}},  
    {{2220.8352,-2011.2456,13.4747}, {2221.8623,-2006.8643,13.5469,200.4113}}, 
    {{2364.2444,-1975.5222,13.4449}, {2367.8267,-1978.0690,13.5469,91.9824}}, 
    {{2416.6458,-1819.5332,13.4989}, {2419.3086,-1815.9498,13.5469,181.4650}}, 

    {{2364.4751,-1729.2854,13.4987}, {2359.9133,-1726.8074,13.5391,268.4899}}, 
    {{2145.8621,-1749.5103,13.5066}, {2141.5635,-1746.8247,13.5512,267.4557}}, 
    {{1985.1179,-1749.2634,13.5020}, {1981.2858,-1746.7916,13.5469,270.7435}}, 
    {{1944.6680,-1697.6075,13.4955}, {1947.2924,-1693.5709,13.5469,181.5981}},  
    {{1885.4987,-1609.4561,13.4986}, {1881.3798,-1606.7312,13.5469,270.1994}}, 
    {{1837.0266,-1540.2488,13.4937}, {1841.2430,-1537.0386,13.5469,157.3207}}, 
    {{1854.7841,-1408.4556,13.5060}, {1857.5505,-1405.1831,13.5625,180.2090}}, 
    {{1772.1483,-1283.2501,13.5840}, {1767.4524,-1283.2625,13.6405,299.3017}}, 
    {{1711.6227,-1328.6715,13.5056}, {1709.2468,-1332.7903,13.5469,359.1143}}, 
    {{1711.8416,-1411.6080,13.5057}, {1709.1499,-1414.9091,13.5469,357.1830}}, 
    {{1655.0692,-1502.4899,13.4982}, {1652.3710,-1505.7488,13.5469,358.9108}}, 
    {{1676.1404,-1551.0532,13.4973}, {1679.7861,-1553.2773,13.5469,89.0260}}, 
    {{1700.6780,-1480.2180,13.4898}, {0.0,0.0,0.0,0.0}}
};

StartAngkotJob(playerid, routetype)
{
    if(DestroyDynamicRaceCP(JobCP[playerid]))
        JobCP[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;
    
    if(DestroyDynamicActor(AngkotActor[playerid]))
        AngkotActor[playerid] = STREAMER_TAG_ACTOR: INVALID_STREAMER_ID;
        
    AngkotRute[playerid] = 0;
    AngkotRouteType[playerid] = routetype;
    AngkotPenumpang[playerid] = false;

    switch(routetype)
    {
        case 1:
        {
            JobVehicle[playerid] = CreateVehicle(440, 1702.8298,-1474.0992,13.5873,179.7953, 6, 6, 60000, false);
            VehicleCore[JobVehicle[playerid]][vCoreFuel] = 35;
            SetValidVehicleHealth(JobVehicle[playerid], 1000.0); 
            VehicleCore[JobVehicle[playerid]][vMaxHealth] = 1000.0;
            VehicleCore[JobVehicle[playerid]][vIsBodyUpgraded] = false;
            VehicleCore[JobVehicle[playerid]][vIsBodyBroken] = false;
            VehicleCore[JobVehicle[playerid]][vCoreLocked] = false;
            PutPlayerInVehicleEx(playerid, JobVehicle[playerid], 0);
            SwitchVehicleEngine(JobVehicle[playerid], true);
            SwitchVehicleDoors(JobVehicle[playerid], false);

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
        case 2:
        {
            JobVehicle[playerid] = CreateVehicle(482, 1702.8298,-1474.0992,13.5873,179.7953, 79, 79, 60000, false);
            VehicleCore[JobVehicle[playerid]][vCoreFuel] = 35;
            SetValidVehicleHealth(JobVehicle[playerid], 1000.0); 
            VehicleCore[JobVehicle[playerid]][vMaxHealth] = 1000.0;
            VehicleCore[JobVehicle[playerid]][vIsBodyUpgraded] = false;
            VehicleCore[JobVehicle[playerid]][vIsBodyBroken] = false;
            VehicleCore[JobVehicle[playerid]][vCoreLocked] = false;
            PutPlayerInVehicleEx(playerid, JobVehicle[playerid], 0);
            SwitchVehicleEngine(JobVehicle[playerid], true);
            SwitchVehicleDoors(JobVehicle[playerid], false);

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
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(IsPlayerInRangeOfPoint(playerid, 3.0, 1691.8894,-1458.7782,13.5469))
        {
            if(AccountData[playerid][pJob] != JOB_ANGKOT) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukanlah Supir Angkot!");

            if(!IsValidVehicle(JobVehicle[playerid]))
            {
                new randrute = Random(1, 3);
                StartAngkotJob(playerid, randrute);
            }
            else
            {
                DestroyVehicle(JobVehicle[playerid]);

                if(DestroyDynamicRaceCP(JobCP[playerid]))
                    JobCP[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

                if(DestroyDynamicActor(AngkotActor[playerid]))
                    AngkotActor[playerid] = STREAMER_TAG_ACTOR: INVALID_STREAMER_ID;

                AngkotRute[playerid] = -1;
                AngkotRouteType[playerid] = 0;
                AngkotPenumpang[playerid] = false;
                pAngkotTimer[playerid] = false;
                ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membatalkan pekerjaan dan mengembalikan kendaraannya.");
            }
        }
    }
    return 1;
}

hook OnPlayerEnterDynRaceCP(playerid, STREAMER_TAG_RACE_CP:checkpointid)
{
    if(AccountData[playerid][pJob] == JOB_ANGKOT && Iter_Contains(Vehicle, JobVehicle[playerid]) && IsPlayerInVehicle(playerid, JobVehicle[playerid]))
    {
        if(AngkotRouteType[playerid] == 1)
        {
            if(checkpointid == JobCP[playerid])
            {
                if(!AngkotPenumpang[playerid])
                {
                    if(DestroyDynamicRaceCP(JobCP[playerid]))
                        JobCP[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

                    if(DestroyDynamicActor(AngkotActor[playerid]))
                        AngkotActor[playerid] = STREAMER_TAG_ACTOR: INVALID_STREAMER_ID;

                    AngkotRute[playerid]++;
                    PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);

                    if(AngkotRute[playerid] >= 23)
                    {
                        DestroyVehicle(JobVehicle[playerid]);

                        AngkotRute[playerid] = -1;
                        AngkotRouteType[playerid] = 0;
                        AngkotPenumpang[playerid] = false;
                        pAngkotTimer[playerid] = false;

                        GivePlayerMoneyEx(playerid, 50);
                        ShowTDN(playerid, NOTIFICATION_INFO, "Anda mendapatkan bonus $50 karena menyelesaikan pekerjaan angkot!");
                        ShowItemBox(playerid, "Cash", "Received $50x", 1212, 5);
                    }
                    else
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
                    Streamer_Update(playerid, -1);
                }
                else
                {
                    PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                    pAngkotTimer[playerid] = true;
                    AccountData[playerid][pActivityTime] = 1;
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "PENUMPANG NAIK");
                    ShowProgressBar(playerid);
                }
            }
        }
        else if(AngkotRouteType[playerid] == 2)
        {
            if(checkpointid == JobCP[playerid])
            {
                if(!AngkotPenumpang[playerid])
                {
                    if(DestroyDynamicRaceCP(JobCP[playerid]))
                        JobCP[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

                    if(DestroyDynamicActor(AngkotActor[playerid]))
                        AngkotActor[playerid] = STREAMER_TAG_ACTOR: INVALID_STREAMER_ID;

                    AngkotRute[playerid]++;
                    PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);

                    if(AngkotRute[playerid] >= 23)
                    {
                        DestroyVehicle(JobVehicle[playerid]);
                        
                        AngkotRute[playerid] = -1;
                        AngkotRouteType[playerid] = 0;
                        AngkotPenumpang[playerid] = false;
                        pAngkotTimer[playerid] = false;

                        GivePlayerMoneyEx(playerid, 50);
                        ShowTDN(playerid, NOTIFICATION_INFO, "Anda mendapatkan bonus $50 karena menyelesaikan pekerjaan angkot!");
                        ShowItemBox(playerid, "Cash", "Received $50x", 1212, 5);
                    }
                    else
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
                    PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                    pAngkotTimer[playerid] = true;
                    AccountData[playerid][pActivityTime] = 1;
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "PENUMPANG NAIK");
                    ShowProgressBar(playerid);
                }
            }
        }
    }
    return 1;
}