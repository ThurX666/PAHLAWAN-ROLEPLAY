#include <YSI_Coding\y_hooks>

new ForkliftVeh[3],
    ForkliftUnloadedCrate[MAX_PLAYERS],
    STREAMER_TAG_OBJECT:ForkliftCrateObj[MAX_PLAYERS],
    STREAMER_TAG_CP:ForkliftCP[MAX_PLAYERS],
    STREAMER_TAG_CP:ForkliftReturnCP[MAX_PLAYERS],
    STREAMER_TAG_CP:UnloadForkliftCP[MAX_PLAYERS];

new Float:LoadingCratePos[][3] = {
    {-1736.8992,-165.2845,3.3116},
    {-1761.4497,-171.6745,3.3167},
    {-1712.6986,123.8810,3.3116},
    {-1730.9977,214.7282,3.3198},
    {-1749.5790,207.4260,3.3174},
    {-1729.6689,-2.7463,3.3162},
    {-1714.1796,-9.3511,3.3308}
};

new Float:UnloadingCratePos[][3] = {
    {-1607.3757,166.5321,3.3187},
    {-1548.1283,123.7208,3.3170}
};

hook OnGameModeInit()
{
    ForkliftVeh[0] = AddStaticVehicleEx(530,-1719.1427,-58.7288,3.3181,133.0009,126,0,60000,false);
	ForkliftVeh[1] = AddStaticVehicleEx(530,-1717.5240,-60.5736,3.3191,131.3610,126,0,60000,false);
	ForkliftVeh[2] = AddStaticVehicleEx(530,-1715.8085,-62.2223,3.3182,132.1132,126,0,60000,false);

    static string[144];
    for(new x; x < sizeof(ForkliftVeh);x++)
    {
        format(string, sizeof(string), "{E75480}FRK-%d", x+1);
        SetVehicleNumberPlate(ForkliftVeh[x], string);
        SetTimerEx("RespawnPV", 1000, false, "d", ForkliftVeh[x]);
    }

    CreateDynamicPickup(1239, 23, -1714.4917,-63.0923,3.5547, 0, 0, -1, 30.00, -1, 0);
    CreateDynamic3DTextLabel("[ Forklift Sidejob Point ]", 0xFF99A4FF, -1714.4917,-63.0923,3.5547+0.5, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 10.00, -1, 0);
    return 1;
}

hook OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP:checkpointid)
{
    if(AccountData[playerid][pSideJob] == SIDEJOB_FORKLIFT && GetPlayerState(playerid) == PLAYER_STATE_DRIVER && GetVehicleModel(SavingVehID[playerid]) == 530)
    {
        if(checkpointid == ForkliftCP[playerid])
        {
            TogglePlayerControllable(playerid, false);

            AccountData[playerid][pActivityTime] = 1;
            ForkliftLoadTimer[playerid] = true;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENGANGKUT");
            ShowProgressBar(playerid);
        }
        else if(checkpointid == UnloadForkliftCP[playerid])
        {
            TogglePlayerControllable(playerid, false);

            AccountData[playerid][pActivityTime] = 1;
            ForkliftUnloadTimer[playerid] = true;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "BONGKAR MUAT");
            ShowProgressBar(playerid);
        }
        else if(checkpointid == ForkliftReturnCP[playerid])
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

            GivePlayerMoneyEx(playerid, 743);

            ShowItemBox(playerid, "Cash", "Received $743x", 1212, 5);

            PlayerPlaySound(playerid, 183, 0.0, 0.0, 0.0);
            GameTextForPlayer(playerid, "mission passed!~n~~w~$743", 8900, 0);
            SetTimerEx("StopMissPassed", 8000, false, "i", playerid);
        }
    }
    return 1;
}

IsAForkliftSidejobVeh(carid)
{
	for(new v; v < sizeof(ForkliftVeh); v++) 
	{
	    if(carid == ForkliftVeh[v]) return 1;
	}
	return 0;
}

StartForkliftSidejob(playerid)
{
    if(DestroyDynamicCP(ForkliftCP[playerid]))
        ForkliftCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

    if(DestroyDynamicCP(ForkliftReturnCP[playerid]))
        ForkliftReturnCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

    if(DestroyDynamicCP(UnloadForkliftCP[playerid]))
        UnloadForkliftCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

    if(DestroyDynamicObject(ForkliftCrateObj[playerid]))
        ForkliftCrateObj[playerid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

    new rand = random(sizeof(LoadingCratePos));
    ForkliftCP[playerid] = CreateDynamicCP(LoadingCratePos[rand][0], LoadingCratePos[rand][1], LoadingCratePos[rand][2], 3.5, 0, 0, playerid, 10000.00, -1, 0);

    ForkliftUnloadedCrate[playerid] = 0;
    AccountData[playerid][pSideJob] = SIDEJOB_FORKLIFT;

    ShowPlayerFooter(playerid, "~g~Sidejob Forklift: ~w~Pergi dan angkut ~y~10 crate~w~~n~ke tempat yang telah ditandai dengan ~r~icon ~w~pada map!", 15000);
    return 1;
}