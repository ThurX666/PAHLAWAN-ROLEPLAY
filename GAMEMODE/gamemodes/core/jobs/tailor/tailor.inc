#include <YSI_Coding\y_hooks>

CheckTailorTimer(playerid)
{
    if(pTakingWoolTimer[playerid]) return 1;
    else if(pMakingFabricTimer[playerid]) return 1;
    else if(pClothingTimer[playerid]) return 1;
    return 0;
}

IsPlayerInFabricArea(playerid)
{
    for(new x; x < sizeof(__g_MakeFabric); x++)
    {
        if(IsPlayerInDynamicArea(playerid, PenjahitFabricArea[x]))
        {
            return true;
        }
    }
    return false;
}

IsPlayerInClothingArea(playerid)
{
    for(new x; x < sizeof(__g_MakeClothes); x++)
    {
        if(IsPlayerInDynamicArea(playerid, PenjahitJahitArea[x]))
        {
            return true;
        }
    }
    return false;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
        if(areaid == Penjahit_TakeWoolArea)
        {
            ShowNotifBox(playerid, "Tekan ~p~'Y' ~w~untuk ambil Wool");
        }

        for(new x; x < sizeof(__g_MakeFabric); x++)
        {
            if(areaid == PenjahitFabricArea[x])
            {
                ShowNotifBox(playerid, "Tekan ~p~'Y' ~w~untuk buat Kain");
            }
        }

        for(new x; x < sizeof(__g_MakeClothes); x++)
        {
            if(areaid == PenjahitJahitArea[x])
            {
                ShowNotifBox(playerid, "Tekan ~p~'Y' ~w~untuk jahit Pakaian");
            }
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(areaid == Penjahit_TakeWoolArea)
    {
        HideNotifBox(playerid);
        PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
    }
    for(new x; x < sizeof(__g_MakeFabric); x++)
    {
        if(areaid == PenjahitFabricArea[x])
        {
            HideNotifBox(playerid);
            PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
        }
    }
    for(new x; x < sizeof(__g_MakeClothes); x++)
    {
        if(areaid == PenjahitJahitArea[x])
        {
            HideNotifBox(playerid);
            PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(IsPlayerInRangeOfPoint(playerid, 3.0, 2556.8508,2023.0450,10.8256))
        {
            if(AccountData[playerid][pJob] != JOB_TAILOR) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang Penjahit!");

            ShowLockerTD(playerid);
        }

        if(IsPlayerInDynamicArea(playerid, Penjahit_TakeWoolArea))
        {
            if(AccountData[playerid][pJob] != JOB_TAILOR) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang Penjahit!");
            if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
            if(!AccountData[playerid][pIsUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus menggunakan seragam kerja!");

            new Float:countingtotalweight;
			countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Wool"))/1000;
			if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");

            AccountData[playerid][pActivityTime] = 1;
            pTakingWoolTimer[playerid] = true;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENGAMBIL WOOL");
            ShowProgressBar(playerid);

            ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, true, false, false, false, 0, true);

            HideNotifBox(playerid);
        }

        for(new x; x < sizeof(__g_MakeFabric); x++)
        {
            if(IsPlayerInDynamicArea(playerid, PenjahitFabricArea[x]))
            {
                if(AccountData[playerid][pJob] != JOB_TAILOR) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang Penjahit!");
                if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
                if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
                if(!AccountData[playerid][pIsUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus menggunakan seragam kerja!");
                if(Inventory_Count(playerid, "Wool") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Wool anda tidak cukup! (Min: 5)");
                
                new Float:countingtotalweight;
                countingtotalweight = GetTotalWeightFloat(playerid) + float(5 * GetItemWeight("Kain"))/1000;
                if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

                AccountData[playerid][pActivityTime] = 1;
                pMakingFabricTimer[playerid] = true;
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMBUAT KAIN");
                ShowProgressBar(playerid);
                
                ApplyAnimation(playerid, "OTB", "betslp_loop", 4.1, true, false, false, false, false, true);

                HideNotifBox(playerid);
            }
        }
    
        for(new x; x < sizeof(__g_MakeClothes); x++)
        {
            if(IsPlayerInDynamicArea(playerid, PenjahitJahitArea[x]))
            {
                if(AccountData[playerid][pJob] != JOB_TAILOR) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang Penjahit!");
                if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
                if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
                if(!AccountData[playerid][pIsUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus menggunakan seragam kerja!");
                if(Inventory_Count(playerid, "Kain") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kain anda tidak cukup! (Min: 5)");

                new Float:countingtotalweight;
                countingtotalweight = GetTotalWeightFloat(playerid) + float(5 * GetItemWeight("Pakaian"))/1000;
                if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

                AccountData[playerid][pActivityTime] = 1;
                pClothingTimer[playerid] = true;
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENJAHIT");
                ShowProgressBar(playerid);

                ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, true, false, false, false, 0, true);

                HideNotifBox(playerid);
            }
        }
    }
    return 1;
}