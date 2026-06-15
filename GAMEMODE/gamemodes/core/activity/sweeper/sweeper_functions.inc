#include <YSI_Coding\y_hooks>

new SweeperVeh[3],
    SweeperRute[MAX_PLAYERS],
    SweeperCPPath[MAX_PLAYERS],
    STREAMER_TAG_CP: SweeperCP[MAX_PLAYERS];

#define sweeperrute1cp1 624.8312,-1542.1720,14.8747
#define sweeperrute1cp2 736.9904,-1588.8088,13.9588
#define sweeperrute1cp3 877.9533,-1578.9265,13.1080
#define sweeperrute1cp4 1101.5474,-1574.3629,13.1001
#define sweeperrute1cp5 1147.5405,-1663.5313,13.5064
#define sweeperrute1cp6 1173.0653,-1724.9844,13.3227
#define sweeperrute1cp7 1190.4928,-1854.6001,13.1246
#define sweeperrute1cp8 1314.9072,-1840.2178,13.1080
#define sweeperrute1cp9 1315.8832,-1557.3002,13.1156
#define sweeperrute1cp10 1327.7821,-1392.8390,13.1027
#define sweeperrute1cp11 1081.7933,-1393.1356,13.3068
#define sweeperrute1cp12 625.0258,-1418.1104,13.1947
#define sweeperfinish 608.9968,-1510.5494,14.6442

#define sweeperrute2cp1 640.1120,-1471.9209,14.1285
#define sweeperrute2cp2 643.8399,-1211.9202,17.8345
#define sweeperrute2cp3 890.9633,-994.6030,36.2027
#define sweeperrute2cp4 960.4288,-1085.2065,24.2631
#define sweeperrute2cp5 1113.0936,-1150.5104,23.3814
#define sweeperrute2cp6 1180.8959,-1041.6177,31.4722
#define sweeperrute2cp7 1351.1425,-1057.5575,26.3665
#define sweeperrute2cp8 1329.9581,-1392.5977,13.1158
#define sweeperrute2cp9 934.9524,-1392.9341,12.9600
#define sweeperrute2cp10 698.3720,-1392.7950,13.1156
#define sweeperrute2cp11 625.3395,-1418.8287,13.2241

hook OnGameModeInit()
{
    SweeperVeh[0] = AddStaticVehicleEx(574,592.7849,-1512.6440,14.9750,269.9236,1,0,60000,false);
	SweeperVeh[1] = AddStaticVehicleEx(574,592.7849,-1512.6440 + 3.000,14.9750,269.9236,1,0,60000,false);
	SweeperVeh[2] = AddStaticVehicleEx(574,592.7849,-1512.6440 + 6.000,14.9750,269.9236,1,0,60000,false);

    static string[144];
    for(new x; x < sizeof(SweeperVeh);x++)
    {
        format(string, sizeof(string), "{E75480}SWP-%d", x+1);
        SetVehicleNumberPlate(SweeperVeh[x], string);
        SetTimerEx("RespawnPV", 1000, false, "d", SweeperVeh[x]);
        SetVehicleSpeedCap(SweeperVeh[x], 48.0);
    }

    CreateDynamicPickup(1239, 23, 590.5202,-1518.6681,15.2882, 0, 0, -1, 30.00, -1, 0);
    CreateDynamic3DTextLabel("[ Sweeper Sidejob Point ]", 0xFF99A4FF, 590.5202,-1518.6681,15.2882+0.5, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 10.00, -1, 0);
    return 1;
}

hook OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP:checkpointid)
{
    if(AccountData[playerid][pSideJob] == SIDEJOB_SWEEPER)
    {
        if(SweeperRute[playerid] == 0)
        {
            switch(SweeperCPPath[playerid])
            {
                case 1:
                {
                    if(DestroyDynamicCP(SweeperCP[playerid]))
                        SweeperCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    SweeperCPPath[playerid] = 2;
                    PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                    SweeperCP[playerid] = CreateDynamicCP(sweeperrute1cp1, 3.5, 0, 0, playerid, 10000.00, -1, 0);
                }
                case 2:
                {
                    if(DestroyDynamicCP(SweeperCP[playerid]))
                        SweeperCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    SweeperCPPath[playerid] = 3;
                    PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                    SweeperCP[playerid] = CreateDynamicCP(sweeperrute1cp2, 3.5, 0, 0, playerid, 10000.00, -1, 0);
                }
                case 3:
                {
                    if(DestroyDynamicCP(SweeperCP[playerid]))
                        SweeperCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    SweeperCPPath[playerid] = 4;
                    PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                    SweeperCP[playerid] = CreateDynamicCP(sweeperrute1cp3, 3.5, 0, 0, playerid, 10000.00, -1, 0);
                }
                case 4:
                {
                    if(DestroyDynamicCP(SweeperCP[playerid]))
                        SweeperCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    SweeperCPPath[playerid] = 5;
                    PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                    SweeperCP[playerid] = CreateDynamicCP(sweeperrute1cp4, 3.5, 0, 0, playerid, 10000.00, -1, 0);
                }
                case 5:
                {
                    if(DestroyDynamicCP(SweeperCP[playerid]))
                        SweeperCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    SweeperCPPath[playerid] = 6;
                    PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                    SweeperCP[playerid] = CreateDynamicCP(sweeperrute1cp5, 3.5, 0, 0, playerid, 10000.00, -1, 0);
                }
                case 6:
                {
                    if(DestroyDynamicCP(SweeperCP[playerid]))
                        SweeperCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    SweeperCPPath[playerid] = 7;
                    PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                    SweeperCP[playerid] = CreateDynamicCP(sweeperrute1cp6, 3.5, 0, 0, playerid, 10000.00, -1, 0);
                }
                case 7:
                {
                    if(DestroyDynamicCP(SweeperCP[playerid]))
                        SweeperCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    SweeperCPPath[playerid] = 8;
                    PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                    SweeperCP[playerid] = CreateDynamicCP(sweeperrute1cp7, 3.5, 0, 0, playerid, 10000.00, -1, 0);
                }
                case 8:
                {
                    if(DestroyDynamicCP(SweeperCP[playerid]))
                        SweeperCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    SweeperCPPath[playerid] = 9;
                    PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                    SweeperCP[playerid] = CreateDynamicCP(sweeperrute1cp8, 3.5, 0, 0, playerid, 10000.00, -1, 0);
                }
                case 9:
                {
                    if(DestroyDynamicCP(SweeperCP[playerid]))
                        SweeperCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    SweeperCPPath[playerid] = 10;
                    PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                    SweeperCP[playerid] = CreateDynamicCP(sweeperrute1cp9, 3.5, 0, 0, playerid, 10000.00, -1, 0);
                }
                case 10:
                {
                    if(DestroyDynamicCP(SweeperCP[playerid]))
                        SweeperCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    SweeperCPPath[playerid] = 11;
                    PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                    SweeperCP[playerid] = CreateDynamicCP(sweeperrute1cp10, 3.5, 0, 0, playerid, 10000.00, -1, 0);
                }
                case 11:
                {
                    if(DestroyDynamicCP(SweeperCP[playerid]))
                        SweeperCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    SweeperCPPath[playerid] = 12;
                    PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                    SweeperCP[playerid] = CreateDynamicCP(sweeperrute1cp11, 3.5, 0, 0, playerid, 10000.00, -1, 0);
                }
                case 12:
                {
                    if(DestroyDynamicCP(SweeperCP[playerid]))
                        SweeperCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    SweeperCPPath[playerid] = 13;
                    PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                    SweeperCP[playerid] = CreateDynamicCP(sweeperrute1cp12, 3.5, 0, 0, playerid, 10000.00, -1, 0);
                }
                case 13:
                {
                    if(DestroyDynamicCP(SweeperCP[playerid]))
                        SweeperCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    SweeperCPPath[playerid] = 14;
                    PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                    SweeperCP[playerid] = CreateDynamicCP(sweeperfinish, 3.5, 0, 0, playerid, 10000.00, -1, 0);
                }
                case 14:
                {
                    if(DestroyDynamicCP(SweeperCP[playerid]))
                        SweeperCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    AccountData[playerid][pSideJob] = SIDEJOB_NONE;
                    SweeperCPPath[playerid] = 0;
                    SweeperRute[playerid] = -1;
                    AccountData[playerid][pSweeperSidejobDelay] = 1800;

                    SetTimerEx("RespawnPV", 1000, false, "d", SavingVehID[playerid]);

                    GivePlayerMoneyEx(playerid, 525);

                    ShowItemBox(playerid, "Cash", "Received $525x", 1212, 1);

                    PlayerPlaySound(playerid, 183, 0.0, 0.0, 0.0);
                    GameTextForPlayer(playerid, "mission passed!~n~~w~$525", 8900, 0);
                    SetTimerEx("StopMissPassed", 8000, false, "i", playerid);
                }
            }
        }
        else if(SweeperRute[playerid] == 1)
        {
            switch(SweeperCPPath[playerid])
            {
                case 1:
                {
                    if(DestroyDynamicCP(SweeperCP[playerid]))
                        SweeperCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    SweeperCPPath[playerid] = 2;
                    PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                    SweeperCP[playerid] = CreateDynamicCP(sweeperrute2cp1, 3.5, 0, 0, playerid, 10000.00, -1, 0);
                }
                case 2:
                {
                    if(DestroyDynamicCP(SweeperCP[playerid]))
                        SweeperCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    SweeperCPPath[playerid] = 3;
                    PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                    SweeperCP[playerid] = CreateDynamicCP(sweeperrute2cp2, 3.5, 0, 0, playerid, 10000.00, -1, 0);
                }
                case 3:
                {
                    if(DestroyDynamicCP(SweeperCP[playerid]))
                        SweeperCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    SweeperCPPath[playerid] = 4;
                    PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                    SweeperCP[playerid] = CreateDynamicCP(sweeperrute2cp3, 3.5, 0, 0, playerid, 10000.00, -1, 0);
                }
                case 4:
                {
                    if(DestroyDynamicCP(SweeperCP[playerid]))
                        SweeperCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    SweeperCPPath[playerid] = 5;
                    PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                    SweeperCP[playerid] = CreateDynamicCP(sweeperrute2cp4, 3.5, 0, 0, playerid, 10000.00, -1, 0);
                }
                case 5:
                {
                    if(DestroyDynamicCP(SweeperCP[playerid]))
                        SweeperCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    SweeperCPPath[playerid] = 6;
                    PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                    SweeperCP[playerid] = CreateDynamicCP(sweeperrute2cp5, 3.5, 0, 0, playerid, 10000.00, -1, 0);
                }
                case 6:
                {
                    if(DestroyDynamicCP(SweeperCP[playerid]))
                        SweeperCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    SweeperCPPath[playerid] = 7;
                    PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                    SweeperCP[playerid] = CreateDynamicCP(sweeperrute2cp6, 3.5, 0, 0, playerid, 10000.00, -1, 0);
                }
                case 7:
                {
                    if(DestroyDynamicCP(SweeperCP[playerid]))
                        SweeperCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    SweeperCPPath[playerid] = 8;
                    PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                    SweeperCP[playerid] = CreateDynamicCP(sweeperrute2cp7, 3.5, 0, 0, playerid, 10000.00, -1, 0);
                }
                case 8:
                {
                    if(DestroyDynamicCP(SweeperCP[playerid]))
                        SweeperCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    SweeperCPPath[playerid] = 9;
                    PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                    SweeperCP[playerid] = CreateDynamicCP(sweeperrute2cp8, 3.5, 0, 0, playerid, 10000.00, -1, 0);
                }
                case 9:
                {
                    if(DestroyDynamicCP(SweeperCP[playerid]))
                        SweeperCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    SweeperCPPath[playerid] = 10;
                    PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                    SweeperCP[playerid] = CreateDynamicCP(sweeperrute2cp9, 3.5, 0, 0, playerid, 10000.00, -1, 0);
                }
                case 10:
                {
                    if(DestroyDynamicCP(SweeperCP[playerid]))
                        SweeperCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    SweeperCPPath[playerid] = 11;
                    PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                    SweeperCP[playerid] = CreateDynamicCP(sweeperrute2cp10, 3.5, 0, 0, playerid, 10000.00, -1, 0);
                }
                case 11:
                {
                    if(DestroyDynamicCP(SweeperCP[playerid]))
                        SweeperCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    SweeperCPPath[playerid] = 12;
                    PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                    SweeperCP[playerid] = CreateDynamicCP(sweeperrute2cp11, 3.5, 0, 0, playerid, 10000.00, -1, 0);
                }
                case 12:
                {
                    if(DestroyDynamicCP(SweeperCP[playerid]))
                        SweeperCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    SweeperCPPath[playerid] = 13;
                    PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
                    SweeperCP[playerid] = CreateDynamicCP(sweeperfinish, 3.5, 0, 0, playerid, 10000.00, -1, 0);
                }
                case 13:
                {
                    if(DestroyDynamicCP(SweeperCP[playerid]))
                        SweeperCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    AccountData[playerid][pSideJob] = SIDEJOB_NONE;
                    SweeperCPPath[playerid] = 0;
                    SweeperRute[playerid] = -1;
                    AccountData[playerid][pSweeperSidejobDelay] = 1800;

                    SetTimerEx("RespawnPV", 1000, false, "d", SavingVehID[playerid]);

                    GivePlayerMoneyEx(playerid, 525);

                    ShowItemBox(playerid, "Cash", "Received $525x", 1212, 1);

                    PlayerPlaySound(playerid, 183, 0.0, 0.0, 0.0);
                    GameTextForPlayer(playerid, "mission passed!~n~~w~$525", 8900, 0);
                    SetTimerEx("StopMissPassed", 8000, false, "i", playerid);
                }
            }
        }
    }
    return 1;
}

IsASweeperSidejobVeh(carid)
{
	for(new v; v < sizeof(SweeperVeh); v++) 
	{
	    if(carid == SweeperVeh[v]) return 1;
	}
	return 0;
}

StartSweeperSidejob(playerid)
{
    if(DestroyDynamicCP(SweeperCP[playerid]))
        SweeperCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
    
    AccountData[playerid][pSideJob] = SIDEJOB_SWEEPER;
    SweeperCPPath[playerid] = 1;
    SweeperRute[playerid] = random(2);

    switch(SweeperRute[playerid])
    {
        case 0:
        {
            SweeperCP[playerid] = CreateDynamicCP(sweeperrute1cp1, 3.5, 0, 0, playerid, 10000.00, -1, 0);
        }
        case 1:
        {
            SweeperCP[playerid] = CreateDynamicCP(sweeperrute2cp1, 3.5, 0, 0, playerid, 10000.00, -1, 0);
        }
    }
    return 1;
}