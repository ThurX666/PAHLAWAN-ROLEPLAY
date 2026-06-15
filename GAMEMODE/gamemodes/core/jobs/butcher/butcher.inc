#include <YSI_Coding\y_hooks>

CheckButcherTimer(playerid)
{
    if(pTakingChickTimer[playerid]) return 1;
    if(pCutingChickTimer[playerid]) return 1;
    if(pPackingChickTimer[playerid]) return 1;
    return 0;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(AccountData[playerid][pJob] == JOB_BUTCHER && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(areaid == Butcher_TakeChickArea)
        {
            ShowNotifBox(playerid, "Tekan ~p~'Y' ~w~untuk ambil Ayam");
        }
        if(areaid == Butcher_CutChickArea)
        {
            ShowNotifBox(playerid, "Tekan ~p~'Y' ~w~untuk potong Ayam");
        }
        if(areaid == Butcher_PackChickArea)
        {
            ShowNotifBox(playerid, "Tekan ~p~'Y' ~w~untuk kemas Ayam");
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(areaid == Butcher_TakeChickArea)
    {
        PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
        HideNotifBox(playerid);
    }
    if(areaid == Butcher_CutChickArea)
    {
        PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
        HideNotifBox(playerid);
    }
    if(areaid == Butcher_PackChickArea)
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
        if(IsPlayerInRangeOfPoint(playerid, 3.0, 2183.2461,-2668.4189,17.8828))
        {
            if(AccountData[playerid][pJob] != JOB_BUTCHER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang Tukang Ayam!");

            ShowLockerTD(playerid);
        }

        if(IsPlayerInDynamicArea(playerid, Butcher_TakeChickArea))
        {
            if(AccountData[playerid][pJob] != JOB_BUTCHER) return 1;
            if(!AccountData[playerid][pIsUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus menggunakan seragam kerja!");
            if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
            
            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(1 * GetItemWeight("Ayam"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");

            AccountData[playerid][pActivityTime] = 1;
            pTakingChickTimer[playerid] = true;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENGAMBIL");
            ShowProgressBar(playerid);

            ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, true, false, false, false, 0, true);

            HideNotifBox(playerid);
        }

        if(IsPlayerInDynamicArea(playerid, Butcher_CutChickArea))
        {
            if(AccountData[playerid][pJob] != JOB_BUTCHER) return 1;
            if(!AccountData[playerid][pIsUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus menggunakan seragam kerja!");
            if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
            if(Inventory_Count(playerid, "Ayam") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Ayam! (Min: 5)");
            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

            new Float:countingtotalweight;
			countingtotalweight = GetTotalWeightFloat(playerid) + float(8 * GetItemWeight("Ayam Potong"))/1000;
			if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

            AccountData[playerid][pActivityTime] = 1;
            pCutingChickTimer[playerid] = true;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMOTONG");
            ShowProgressBar(playerid);

            ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, true, false, false, false, 0, true);

            HideNotifBox(playerid);
        }

        if(IsPlayerInDynamicArea(playerid, Butcher_PackChickArea))
        {
            if(AccountData[playerid][pJob] != JOB_BUTCHER) return 1;
            if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
            if(Inventory_Count(playerid, "Ayam Potong") < 8) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Ayam Potong! (Min: 8)");
            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
            
            new Float:countingtotalweight;
			countingtotalweight = GetTotalWeightFloat(playerid) + float(8 * GetItemWeight("Ayam Kemas"))/1000;
			if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

            AccountData[playerid][pActivityTime] = 1;
            pPackingChickTimer[playerid] = true;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENGEMAS");
            ShowProgressBar(playerid);

            ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, true, false, false, false, 0, true);

            HideNotifBox(playerid);
        }
    }
    return 1;
}