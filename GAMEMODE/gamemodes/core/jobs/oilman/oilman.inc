#include <YSI_Coding\y_hooks>

IsPlayerInTakeOilArea(playerid)
{
    for(new x; x < sizeof(__g_OilTakePos); x++)
    {
        if(IsPlayerInDynamicArea(playerid, Oilman_TakeOilArea[x]))
        {
            return 1;
        }
    }
    return 0;
}

CheckOilmanTimer(playerid)
{
    if(pTakingOilTimer[playerid]) return 1;
    else if(pRefiningOilTimer[playerid]) return 1;
    else if(pMixingOilTimer[playerid]) return 1;

    return 0;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(AccountData[playerid][pJob] == JOB_OILMAN && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        for(new x; x < sizeof(__g_OilTakePos); x++)
        {
            if(areaid == Oilman_TakeOilArea[x])
            {
                ShowNotifBox(playerid, "Tekan ~p~'Y' ~w~untuk ambil Minyak");
            }
        }
        if(areaid == Oilman_RefineArea[0] || areaid == Oilman_RefineArea[1])
        {
            ShowNotifBox(playerid, "Tekan ~p~'Y' ~w~untuk saring Minyak");
        }
        if(areaid == Oilman_MixArea)
        {
            ShowNotifBox(playerid, "Tekan ~p~'Y' ~w~untuk olah Minyak");
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    for(new x; x < sizeof(__g_OilTakePos); x++)
    {
        if(areaid == Oilman_TakeOilArea[x])
        {
            PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
            HideNotifBox(playerid);
        }
    }
    if(areaid == Oilman_RefineArea[0] || areaid == Oilman_RefineArea[1])
    {
        PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
        HideNotifBox(playerid);
    }
    if(areaid == Oilman_MixArea)
    {
        PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
        HideNotifBox(playerid);
    }
    return 1;
}

hook OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP:checkpointid)
{
    if(AccountData[playerid][pJob] == JOB_OILMAN && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(checkpointid == Oilman_BoatCP[0] || checkpointid == Oilman_BoatCP[1])
        {
            ShowNotifBox(playerid, "Tekan ~p~'Y' ~w~untuk ambil/kembalikan kapal kerja");
        }
    }
    return 1;
}

hook OnPlayerLeaveDynamicCP(playerid, STREAMER_TAG_CP:checkpointid)
{
    if(AccountData[playerid][pJob] == JOB_OILMAN && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(checkpointid == Oilman_BoatCP[0] || checkpointid == Oilman_BoatCP[1])
        {
            PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
            HideNotifBox(playerid);
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(IsPlayerInRangeOfPoint(playerid, 3.0, 2445.5918,-2619.7668,17.9107))
        {
            if(AccountData[playerid][pJob] != JOB_OILMAN) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang Tukang Minyak!");

            ShowLockerTD(playerid);
        }

        for(new x; x < sizeof(__g_OilTakePos); x++)
        {
            if(IsPlayerInDynamicArea(playerid, Oilman_TakeOilArea[x]))
            {
                if(AccountData[playerid][pJob] != JOB_OILMAN) return 1;
                if(!AccountData[playerid][pIsUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus menggunakan seragam kerja!");
                if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
                if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

                new Float:countingtotalweight;
                countingtotalweight = GetTotalWeightFloat(playerid) + float(2 * GetItemWeight("Minyak Bumi"))/1000;
                if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");

                AccountData[playerid][pActivityTime] = 1;
                pTakingOilTimer[playerid] = true;
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENGAMBIL");
                ShowProgressBar(playerid);

                ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, true, false, false, false, 0, true);

                HideNotifBox(playerid);
            }
        }

        if(IsPlayerInDynamicArea(playerid, Oilman_RefineArea[0]) || IsPlayerInDynamicArea(playerid, Oilman_RefineArea[1]))
        {
            if(AccountData[playerid][pJob] != JOB_OILMAN) return 1;
            if(!AccountData[playerid][pIsUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus menggunakan seragam kerja!");
            if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
            if(Inventory_Count(playerid, "Minyak Bumi") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Minyak Bumi! (Min: 5)");
            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

            new Float:countingtotalweight;
			countingtotalweight = GetTotalWeightFloat(playerid) + float(5 * GetItemWeight("Minyak Saringan"))/1000;
			if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

            AccountData[playerid][pActivityTime] = 1;
            pRefiningOilTimer[playerid] = true;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENYARING");
            ShowProgressBar(playerid);

            ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, true, false, false, false, 0, true);

            HideNotifBox(playerid);
        }

        if(IsPlayerInDynamicArea(playerid, Oilman_MixArea))
        {
            if(AccountData[playerid][pJob] != JOB_OILMAN) return 1;
            if(!AccountData[playerid][pIsUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus menggunakan seragam kerja!");
            if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
            if(Inventory_Count(playerid, "Minyak Saringan") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Minyak Saringan! (Min: 5)");
            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
            if(GetTotalWeightFloat(playerid) > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

            AccountData[playerid][pActivityTime] = 1;
            pMixingOilTimer[playerid] = true;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENGOLAH");
            ShowProgressBar(playerid);

            ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, true, false, false, false, 0, true);

            HideNotifBox(playerid);
        }
        
        if(IsPlayerInDynamicCP(playerid, Oilman_BoatCP[0]))
        {
            if(AccountData[playerid][pJob] != JOB_OILMAN) return 1;
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
                JobVehicle[playerid] = CreateVehicle(453, 2468.9614,-2761.5010,0.3896,269.0526, random(255), random(255), 60000, false);
                VehicleCore[JobVehicle[playerid]][vCoreFuel] = 100;
                SetValidVehicleHealth(JobVehicle[playerid], 1000.0); 
                VehicleCore[JobVehicle[playerid]][vMaxHealth] = 1000.0;
                VehicleCore[JobVehicle[playerid]][vIsBodyUpgraded] = true;
                VehicleCore[JobVehicle[playerid]][vIsBodyBroken] = false;
                VehicleCore[JobVehicle[playerid]][vCoreLocked] = false;
                PutPlayerInVehicleEx(playerid, JobVehicle[playerid], 0);
                SwitchVehicleEngine(JobVehicle[playerid], true);
                SwitchVehicleDoors(JobVehicle[playerid], false);

                ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mengeluarkan boat pekerjaan.");
            }
        }

        if(IsPlayerInDynamicCP(playerid, Oilman_BoatCP[1]))
        {
            if(AccountData[playerid][pJob] != JOB_OILMAN) return 1;
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
                JobVehicle[playerid] = CreateVehicle(453, 2701.1294,-6834.9600,-0.7143,0.9844, random(255), random(255), 60000, false);
                VehicleCore[JobVehicle[playerid]][vCoreFuel] = 100;
                SetValidVehicleHealth(JobVehicle[playerid], 1000.0); 
                VehicleCore[JobVehicle[playerid]][vMaxHealth] = 1000.0;
                VehicleCore[JobVehicle[playerid]][vIsBodyUpgraded] = true;
                VehicleCore[JobVehicle[playerid]][vIsBodyBroken] = false;
                VehicleCore[JobVehicle[playerid]][vCoreLocked] = false;
                PutPlayerInVehicleEx(playerid, JobVehicle[playerid], 0);
                SwitchVehicleEngine(JobVehicle[playerid], true);
                SwitchVehicleDoors(JobVehicle[playerid], false);

                ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mengeluarkan boat pekerjaan.");
            }
        }
    }
    return 1;
}