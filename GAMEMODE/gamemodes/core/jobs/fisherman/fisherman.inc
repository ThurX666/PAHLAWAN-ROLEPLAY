#include <YSI_Coding\y_hooks>

CheckFishermanTimer(playerid)
{
    if(pTakingFishTimer[playerid]) return 1;
    return 0;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && AccountData[playerid][pJob] == JOB_FISHERMAN)
	{
        if(areaid == Fisherman_TakeFish)
        {
            ShowNotifBox(playerid, "Tekan ~p~'Y' ~w~untuk jala Ikan");
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(areaid == Fisherman_TakeFish)
    {
        HideNotifBox(playerid);
        PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
    }
    return 1;
}

hook OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP:checkpointid)
{
    if(AccountData[playerid][pJob] == JOB_FISHERMAN && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(checkpointid == Fisherman_BoatCP)
        {
            ShowNotifBox(playerid, "Tekan ~p~'Y' ~w~untuk ambil/kembalikan kapal kerja");
        }
    }
    return 1;
}

hook OnPlayerLeaveDynamicCP(playerid, STREAMER_TAG_CP:checkpointid)
{
    if(AccountData[playerid][pJob] == JOB_FISHERMAN && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(checkpointid == Fisherman_BoatCP)
        {
            PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
            HideNotifBox(playerid);
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES)
    {
        if(IsPlayerInRangeOfPoint(playerid, 3.0, 2530.4011,-2434.6401,17.8828) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
        {
            if(AccountData[playerid][pJob] != JOB_FISHERMAN) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang Nelayan!");

            ShowLockerTD(playerid);
        }

        if(IsPlayerInDynamicArea(playerid, Fisherman_TakeFish) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER && GetVehicleModel(SavingVehID[playerid]) == 453)
        {
            if(AccountData[playerid][pJob] != JOB_FISHERMAN) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang Nelayan!");

            if(!AccountData[playerid][pIsUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus menggunakan seragam kerja!");
            if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

            AccountData[playerid][pActivityTime] = 1;
            pTakingFishTimer[playerid] = true;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENJALA");
            ShowProgressBar(playerid);

            HideNotifBox(playerid);
        }

        if(IsPlayerInDynamicCP(playerid, Fisherman_BoatCP) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
        {
            if(AccountData[playerid][pJob] != JOB_FISHERMAN) return 1;
            if(!AccountData[playerid][pIsUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus menggunakan seragam kerja!");
            if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

            if(Iter_Contains(Vehicle, JobVehicle[playerid]))
            {
                DestroyVehicle(JobVehicle[playerid]);

                ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mengembalikan boat pekerjaan.");
            }
            else
            {
                JobVehicle[playerid] = CreateVehicle(453, 2929.9102,-2128.8325,-0.9523,263.6270, random(255), random(255), 60000, false);
                VehicleCore[JobVehicle[playerid]][vCoreFuel] = 100;
                SetValidVehicleHealth(JobVehicle[playerid], 1000.0); 
                VehicleCore[JobVehicle[playerid]][vMaxHealth] = 1000.0;
                VehicleCore[JobVehicle[playerid]][vIsBodyUpgraded] = true;
                VehicleCore[JobVehicle[playerid]][vIsBodyBroken] = false;
                VehicleCore[JobVehicle[playerid]][vCoreLocked] = false;
                SwitchVehicleEngine(JobVehicle[playerid], true);
                SwitchVehicleDoors(JobVehicle[playerid], false);

                ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mengeluarkan boat pekerjaan.");
            }
        }
    }
    return 1;
}