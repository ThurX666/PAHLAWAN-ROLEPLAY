#include <YSI_Coding\y_hooks>

CheckMinerTimer(playerid)
{
    if(pTakingStoneTimer[playerid]) return 1;
    if(pWashingStoneTimer[playerid]) return 1;
    if(pSmeltingStoneTimer[playerid]) return 1;
    return 0;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(AccountData[playerid][pJob] == JOB_MINER && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(areaid == Miner_TakeStoneArea)
        {
            ShowNotifBox(playerid, "Tekan ~p~'Y' ~w~untuk ambil Batu");
        }
        if(areaid == Miner_WashStoneArea)
        {
            ShowNotifBox(playerid, "Tekan ~p~'Y' ~w~untuk cuci Batu");
        }
        if(areaid == Miner_SmeltStoneArea)
        {
            ShowNotifBox(playerid, "Tekan ~p~'Y' ~w~untuk lebur Batu");
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(areaid == Miner_TakeStoneArea)
    {
        PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
        HideNotifBox(playerid);
    }
    if(areaid == Miner_WashStoneArea)
    {
        PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
        HideNotifBox(playerid);
    }
    if(areaid == Miner_SmeltStoneArea)
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
        if(IsPlayerInRangeOfPoint(playerid, 3.0, 2380.0393,-2265.4482,13.5469))
        {
            if(AccountData[playerid][pJob] != JOB_MINER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang Penambang!");

            ShowLockerTD(playerid);
        }

        if(IsPlayerInDynamicArea(playerid, Miner_TakeStoneArea))
        {
            if(AccountData[playerid][pJob] != JOB_MINER) return 1;
            if(!AccountData[playerid][pIsUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus menggunakan seragam kerja!");
            if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(2 * GetItemWeight("Batu"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");

            AccountData[playerid][pActivityTime] = 1;
            pTakingStoneTimer[playerid] = true;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENAMBANG");
            ShowProgressBar(playerid);

            SetPlayerAttachedObject(playerid, 9, 19631, 6, 0.071000, 0.082999, 0.017000, -9.800041, 107.400207, 2.799999, 1.000000, 1.000000, 1.000000);
            ApplyAnimation(playerid, "BASEBALL", "Bat_4", 4.1, true, false, false, false, 0, true);

            HideNotifBox(playerid);
        }

        if(IsPlayerInDynamicArea(playerid, Miner_WashStoneArea))
        {
            if(AccountData[playerid][pJob] != JOB_MINER) return 1;
            if(!AccountData[playerid][pIsUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus menggunakan seragam kerja!");
            if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
            if(Inventory_Count(playerid, "Batu") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Batu! (Min: 5)");
            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

            new Float:countingtotalweight;
			countingtotalweight = GetTotalWeightFloat(playerid) + float(5 * GetItemWeight("Batu Cucian"))/1000;
			if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

            AccountData[playerid][pActivityTime] = 1;
            pWashingStoneTimer[playerid] = true;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENCUCI BATU");
            ShowProgressBar(playerid);

            ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, true, false, false, false, 0, true);

            HideNotifBox(playerid);
        }

        if(IsPlayerInDynamicArea(playerid, Miner_SmeltStoneArea))
        {
            if(AccountData[playerid][pJob] != JOB_MINER) return 1;
            if(!AccountData[playerid][pIsUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus menggunakan seragam kerja!");
            if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
            if(Inventory_Count(playerid, "Batu Cucian") < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Batu Cucian! (Min: 2)");
            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
            if(GetTotalWeightFloat(playerid) > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

            AccountData[playerid][pActivityTime] = 1;
            pSmeltingStoneTimer[playerid] = true;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MELEBUR BATU");
            ShowProgressBar(playerid);

            ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, true, false, false, false, 0, true);

            HideNotifBox(playerid);
        }
    }
    return 1;
}