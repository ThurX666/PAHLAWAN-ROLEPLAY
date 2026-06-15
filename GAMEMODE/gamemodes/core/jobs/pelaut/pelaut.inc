#include <YSI_Coding\y_hooks>

new SailRute[MAX_PLAYERS],
    SailRouteType[MAX_PLAYERS];

enum e_sailroute
{
    Float:Pos[3]
};

new SailRouteLV[][e_sailroute] =
{
    {{1546.2555,563.4705,0.2809}}, //0
    {{1710.0778,471.6710,0.1403}}, //1
    {{2088.6692,486.4529,0.3091}}, //2
    {{2356.9316,517.4556,0.1353}}, //dock //3
    {{3181.1387,462.5285,-0.2179}}, //4
    {{3155.1650,-411.2981,0.4641}}, //5
    {{3157.6147,-1699.3286,0.5867}}, //6
    {{2946.7385,-2052.8506,0.4382}}, //dock //7
    {{2626.7732,-2277.0396,0.1425}},
    {{2300.1279,-2424.7351,0.1000}}, //dock //9
    {{2319.5847,-3090.6484,-0.0770}},
    {{873.3615,-2939.1641,-0.0807}},
    {{726.7996,-1885.0492,-0.3751}},
    {{729.1790,-1504.0264,0.2208}} //finish //13 
};

new SailRouteLS[][e_sailroute] =
{
    {{721.7961,-1775.7394,0.1547}}, //0
    {{861.2672,-2963.7632,0.3849}}, //1
    {{2305.4775,-3135.1885,0.4709}}, //2
    {{2347.3953,-2489.4233,0.0795}}, //3
    {{2317.3198,-2405.6653,0.2008}}, //dock //4
    {{2627.3867,-2306.7893,0.2216}}, //5
    {{2947.1262,-2051.5464,0.0348}}, //dock //6
    {{3206.4392,-1707.4839,0.5128}}, //7
    {{3198.4121,-417.0473,-0.5127}},
    {{3211.7085,486.9241,-0.1374}}, //9
    {{2296.8040,518.4781,-0.3462}}, //dock //10
    {{2096.6563,518.9552,-0.2331}},
    {{1582.9447,548.6024,-0.3090}},
    {{1627.5638,571.2642,-0.3096}} //finish //13 
};

StartPelautJob(playerid, routetype)
{
    if(DestroyDynamicRaceCP(JobCP[playerid]))
        JobCP[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;
        
    SailRute[playerid] = 0;
    SailRouteType[playerid] = routetype;
    SailDockTimer[playerid] = false;

    //175k - rusun
    //140k - gudang

    switch(routetype)
    {
        case 1:
        {
            JobVehicle[playerid] = CreateVehicle(484, 1613.3888,577.7652,0.2738,88.3286, random(255), random(255), 60000, false);
            VehicleCore[JobVehicle[playerid]][vCoreFuel] = 100;
            SetValidVehicleHealth(JobVehicle[playerid], 1000.0); 
            VehicleCore[JobVehicle[playerid]][vMaxHealth] = 1000.0;
            VehicleCore[JobVehicle[playerid]][vIsBodyUpgraded] = false;
            VehicleCore[JobVehicle[playerid]][vIsBodyBroken] = false;
            VehicleCore[JobVehicle[playerid]][vCoreLocked] = false;
            PutPlayerInVehicleEx(playerid, JobVehicle[playerid], 0);
            SwitchVehicleEngine(JobVehicle[playerid], true);
            SwitchVehicleDoors(JobVehicle[playerid], false);

            JobCP[playerid] = CreateDynamicRaceCP(3, SailRouteLV[SailRute[playerid]][Pos][0], SailRouteLV[SailRute[playerid]][Pos][1], SailRouteLV[SailRute[playerid]][Pos][2], SailRouteLV[SailRute[playerid]+1][Pos][0], SailRouteLV[SailRute[playerid]+1][Pos][1], SailRouteLV[SailRute[playerid]+1][Pos][2], 3.5, 0, 0, playerid, 10000.00, -1, 0);
        }
        case 2:
        {
            JobVehicle[playerid] = CreateVehicle(484, 718.0920,-1498.5295,0.2506,189.6813, random(255), random(255), 60000, false);
            VehicleCore[JobVehicle[playerid]][vCoreFuel] = 100;
            SetValidVehicleHealth(JobVehicle[playerid], 1000.0); 
            VehicleCore[JobVehicle[playerid]][vMaxHealth] = 1000.0;
            VehicleCore[JobVehicle[playerid]][vIsBodyUpgraded] = false;
            VehicleCore[JobVehicle[playerid]][vIsBodyBroken] = false;
            VehicleCore[JobVehicle[playerid]][vCoreLocked] = false;
            PutPlayerInVehicleEx(playerid, JobVehicle[playerid], 0);
            SwitchVehicleEngine(JobVehicle[playerid], true);
            SwitchVehicleDoors(JobVehicle[playerid], false);

            JobCP[playerid] = CreateDynamicRaceCP(3, SailRouteLS[SailRute[playerid]][Pos][0], SailRouteLS[SailRute[playerid]][Pos][1], SailRouteLS[SailRute[playerid]][Pos][2], SailRouteLS[SailRute[playerid]+1][Pos][0], SailRouteLS[SailRute[playerid]+1][Pos][1], SailRouteLS[SailRute[playerid]+1][Pos][2], 3.5, 0, 0, playerid, 10000.00, -1, 0);
        }
    }
    Streamer_Update(playerid, -1);
    return 1;
}

hook OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP:checkpointid)
{
    if(AccountData[playerid][pJob] == JOB_PELAUT && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(checkpointid == PelautStartLV)
        {
            ShowNotifBox(playerid, "Tekan ~p~'Y' ~w~untuk kerja pelaut");
        }
        if(checkpointid == PelautStartLS)
        {
            ShowNotifBox(playerid, "Tekan ~p~'Y' ~w~untuk kerja pelaut");
        }
    }
    return 1;
}

hook OnPlayerLeaveDynamicCP(playerid, STREAMER_TAG_CP:checkpointid)
{
    if(checkpointid == PelautStartLV)
    {
        PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
        HideNotifBox(playerid);
    }
    if(checkpointid == PelautStartLS)
    {
        PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
        HideNotifBox(playerid);
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(IsPlayerInDynamicCP(playerid, PelautStartLV))
        {
            if(AccountData[playerid][pJob] != JOB_PELAUT) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukanlah Pelaut!");

            if(!IsValidVehicle(JobVehicle[playerid]))
            {
                StartPelautJob(playerid, 1);
            }
            else
            {
                DestroyVehicle(JobVehicle[playerid]);

                if(DestroyDynamicRaceCP(JobCP[playerid]))
                    JobCP[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

                SailRute[playerid] = -1;
                SailRouteType[playerid] = 0;
                SailDockTimer[playerid] = false;
                ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membatalkan pekerjaan dan mengembalikan kendaraannya.");
            }
        }
        
        if(IsPlayerInDynamicCP(playerid, PelautStartLS))
        {
            if(AccountData[playerid][pJob] != JOB_PELAUT) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukanlah Pelaut!");

            if(!IsValidVehicle(JobVehicle[playerid]))
            {
                StartPelautJob(playerid, 2);
            }
            else
            {
                DestroyVehicle(JobVehicle[playerid]);

                if(DestroyDynamicRaceCP(JobCP[playerid]))
                    JobCP[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

                SailRute[playerid] = -1;
                SailRouteType[playerid] = 0;
                SailDockTimer[playerid] = false;
                ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membatalkan pekerjaan dan mengembalikan kendaraannya.");
            }
        }
    }
    return 1;
}

hook OnPlayerEnterDynRaceCP(playerid, STREAMER_TAG_RACE_CP:checkpointid)
{
    if(AccountData[playerid][pJob] == JOB_PELAUT && Iter_Contains(Vehicle, JobVehicle[playerid]) && IsPlayerInVehicle(playerid, JobVehicle[playerid]))
    {
        if(SailRouteType[playerid] == 1)
        {
            if(checkpointid == JobCP[playerid])
            {
                switch(SailRute[playerid])
                {
                    case 3, 7, 9:
                    {
                        PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                        SailDockTimer[playerid] = true;
                        AccountData[playerid][pActivityTime] = 1;
                        PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "BERSANDAR");
                        ShowProgressBar(playerid);
                    }
                    case 13:
                    {
                        PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                        SailDockTimer[playerid] = true;
                        AccountData[playerid][pActivityTime] = 1;
                        PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "SAMPAI");
                        ShowProgressBar(playerid);
                    }
                    default:
                    {
                        if(DestroyDynamicRaceCP(JobCP[playerid]))
                            JobCP[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;
                        
                        SailRute[playerid]++;

                        if(SailRute[playerid] >= 13)
                        {
                            JobCP[playerid] = CreateDynamicRaceCP(4, SailRouteLV[SailRute[playerid]][Pos][0], SailRouteLV[SailRute[playerid]][Pos][1], SailRouteLV[SailRute[playerid]][Pos][2], SailRouteLV[SailRute[playerid]][Pos][0], SailRouteLV[SailRute[playerid]][Pos][1], SailRouteLV[SailRute[playerid]][Pos][2], 3.5, 0, 0, playerid, 10000.00, -1, 0);
                        }
                        else
                        {
                            JobCP[playerid] = CreateDynamicRaceCP(3, SailRouteLV[SailRute[playerid]][Pos][0], SailRouteLV[SailRute[playerid]][Pos][1], SailRouteLV[SailRute[playerid]][Pos][2], SailRouteLV[SailRute[playerid]+1][Pos][0], SailRouteLV[SailRute[playerid]+1][Pos][1], SailRouteLV[SailRute[playerid]+1][Pos][2], 3.5, 0, 0, playerid, 10000.00, -1, 0);
                        }
                    }
                }
            }
        }

        else if(SailRouteType[playerid] == 2)
        {
            if(checkpointid == JobCP[playerid])
            {
                switch(SailRute[playerid])
                {
                    case 4, 6, 10:
                    {
                        PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                        SailDockTimer[playerid] = true;
                        AccountData[playerid][pActivityTime] = 1;
                        PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "BERSANDAR");
                        ShowProgressBar(playerid);
                    }
                    case 13:
                    {
                        PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                        SailDockTimer[playerid] = true;
                        AccountData[playerid][pActivityTime] = 1;
                        PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "SAMPAI");
                        ShowProgressBar(playerid);
                    }
                    default:
                    {
                        if(DestroyDynamicRaceCP(JobCP[playerid]))
                            JobCP[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;
                        
                        SailRute[playerid]++;

                        if(SailRute[playerid] >= 13)
                        {
                            JobCP[playerid] = CreateDynamicRaceCP(4, SailRouteLS[SailRute[playerid]][Pos][0], SailRouteLS[SailRute[playerid]][Pos][1], SailRouteLS[SailRute[playerid]][Pos][2], SailRouteLS[SailRute[playerid]][Pos][0], SailRouteLS[SailRute[playerid]][Pos][1], SailRouteLS[SailRute[playerid]][Pos][2], 3.5, 0, 0, playerid, 10000.00, -1, 0);
                        }
                        else
                        {
                            JobCP[playerid] = CreateDynamicRaceCP(3, SailRouteLS[SailRute[playerid]][Pos][0], SailRouteLS[SailRute[playerid]][Pos][1], SailRouteLS[SailRute[playerid]][Pos][2], SailRouteLS[SailRute[playerid]+1][Pos][0], SailRouteLS[SailRute[playerid]+1][Pos][1], SailRouteLS[SailRute[playerid]+1][Pos][2], 3.5, 0, 0, playerid, 10000.00, -1, 0);
                        }
                    }
                }
            }
        }
    }
    return 1;
}