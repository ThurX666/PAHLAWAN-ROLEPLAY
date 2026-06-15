#include <YSI_Coding\y_hooks>

enum E_LUMBERJACKSTUFF
{
    STREAMER_TAG_AREA:LumberGetWoodArea[7],
    LumberWoodCountdown[7]
};
new PlayerLumberjackVars[MAX_PLAYERS][E_LUMBERJACKSTUFF];

IsPlayerInTreePos(playerid)
{
    for(new x; x < sizeof(__g_TreePos); x++)
    {
        if(IsPlayerInDynamicArea(playerid, PlayerLumberjackVars[playerid][LumberGetWoodArea][x]))
        {
            return true;
        }
    }
    return false;
}

IsPlayerInCutLog(playerid)
{
    for(new x; x < sizeof(__g_CutLog); x++)
    {
        if(IsPlayerInDynamicArea(playerid, LumberCutLogArea[x]))
        {
            return true;
        }
    }
    return false;
}

IsPlayerInPackLog(playerid)
{
    for(new x; x < sizeof(__g_PackLog); x++)
    {
        if(IsPlayerInDynamicArea(playerid, LumberPackArea[x]))
        {
            return true;
        }
    }
    return false;
}

CheckLumberjackTimer(playerid)
{
    if(pTakeWoodTimer[playerid]) return 1;
    else if(pCutWoodTimer[playerid]) return 1;
    else if(pGetBoardTimer[playerid]) return 1;

    return 0;
}

ptask UpdateWoodCountdown[1000](playerid) 
{
    for(new t; t < 7; t++)
    {
        if(PlayerLumberjackVars[playerid][LumberWoodCountdown][t] > 0)
        {
            PlayerLumberjackVars[playerid][LumberWoodCountdown][t]--;

            if(PlayerLumberjackVars[playerid][LumberWoodCountdown][t] <= 0)
            {
                PlayerLumberjackVars[playerid][LumberWoodCountdown][t] = 0;

                if(DestroyDynamicArea(PlayerLumberjackVars[playerid][LumberGetWoodArea][t]))
                    PlayerLumberjackVars[playerid][LumberGetWoodArea][t] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
                
                switch(t)
                {
                    case 0:
                    {
                        PlayerLumberjackVars[playerid][LumberGetWoodArea][0] = CreateDynamicSphere(__g_TreePos[0][0], __g_TreePos[0][1], __g_TreePos[0][2], 3.0, 0, 0, playerid);
                    }
                    case 1:
                    {
                        PlayerLumberjackVars[playerid][LumberGetWoodArea][1] = CreateDynamicSphere(__g_TreePos[1][0], __g_TreePos[1][1], __g_TreePos[1][2], 3.0, 0, 0, playerid);
                    }
                    case 2:
                    {
                        PlayerLumberjackVars[playerid][LumberGetWoodArea][2] = CreateDynamicSphere(__g_TreePos[2][0], __g_TreePos[2][1], __g_TreePos[2][2], 3.0, 0, 0, playerid);
                    }
                    case 3:
                    {
                        PlayerLumberjackVars[playerid][LumberGetWoodArea][3] = CreateDynamicSphere(__g_TreePos[3][0], __g_TreePos[3][1], __g_TreePos[3][2], 3.0, 0, 0, playerid);
                    }
                    case 4:
                    {
                        PlayerLumberjackVars[playerid][LumberGetWoodArea][4] = CreateDynamicSphere(__g_TreePos[4][0], __g_TreePos[4][1], __g_TreePos[4][2], 3.0, 0, 0, playerid);
                    }
                    case 5:
                    {
                        PlayerLumberjackVars[playerid][LumberGetWoodArea][5] = CreateDynamicSphere(__g_TreePos[5][0], __g_TreePos[5][1], __g_TreePos[5][2], 3.0, 0, 0, playerid);
                    }
                    case 6:
                    {
                        PlayerLumberjackVars[playerid][LumberGetWoodArea][6] = CreateDynamicSphere(__g_TreePos[6][0], __g_TreePos[6][1], __g_TreePos[6][2], 3.0, 0, 0, playerid);
                    }
                }
            }
        }
    }
    return 1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(AccountData[playerid][pJob] == JOB_LUMBERJACK && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
        for(new x; x < sizeof(__g_TreePos); x++)
        {
            if(areaid == PlayerLumberjackVars[playerid][LumberGetWoodArea][x])
            {
                ShowNotifBox(playerid, "Tekan ~p~'Y' ~w~untuk ambil Kayu");
            }
        }

        for(new x; x < sizeof(__g_CutLog); x++)
        {
            if(areaid == LumberCutLogArea[x])
            {
                ShowNotifBox(playerid, "Tekan ~p~'Y' ~w~untuk memotong Kayu");
            }
        }
        for(new x; x < sizeof(__g_PackLog); x++)
        {
            if(areaid == LumberPackArea[x])
            {
                ShowNotifBox(playerid, "Tekan ~p~'Y' ~w~untuk nembuat Papan");
            }
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    for(new x; x < sizeof(__g_TreePos); x++)
    {
        if(areaid == PlayerLumberjackVars[playerid][LumberGetWoodArea][x])
        {
            HideNotifBox(playerid);
            PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
        }
    }
    for(new x; x < sizeof(__g_CutLog); x++)
    {
        if(areaid == LumberCutLogArea[x])
        {
            HideNotifBox(playerid);
            PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
        }
    }
    for(new x; x < sizeof(__g_PackLog); x++)
    {
        if(areaid == LumberPackArea[x])
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
        if(IsPlayerInRangeOfPoint(playerid, 3.0, -491.5486,-193.8380,78.3525))
        {
            if(AccountData[playerid][pJob] != JOB_LUMBERJACK) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang Tukang Kayu!");

            ShowLockerTD(playerid);
        }

        for(new x; x < sizeof(__g_TreePos); x++)
        {
            if(IsPlayerInDynamicArea(playerid, PlayerLumberjackVars[playerid][LumberGetWoodArea][x]))
            {
                if(AccountData[playerid][pJob] != JOB_LUMBERJACK) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang Tukang Kayu!");
                if(!AccountData[playerid][pIsUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus menggunakan seragam kerja!");
                if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

                new Float:countingtotalweight;
                countingtotalweight = GetTotalWeightFloat(playerid) + float(2 * GetItemWeight("Kayu"))/1000;
                if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

                AccountData[playerid][pActivityTime] = 1;
                AccountData[playerid][pInTree] = x;
                pTakeWoodTimer[playerid] = true;
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENGAMBIL KAYU");
                ShowProgressBar(playerid);

                SetPlayerAttachedObject(playerid, 9, 341, 6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.000000, 1.000000, 1.000000);
                ApplyAnimation(playerid, "CHAINSAW", "WEAPON_csaw", 1.33, 1, 0, 0, 0, 0, 1);

                HideNotifBox(playerid);
            }
        }

        if(IsPlayerInCutLog(playerid))
        {
            if(AccountData[playerid][pJob] != JOB_LUMBERJACK) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang Tukang Kayu!");
            if(!AccountData[playerid][pIsUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus menggunakan seragam kerja!");
            if(Inventory_Count(playerid, "Kayu") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kayu anda tidak cukup! (Min: 5)");
            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(5 * GetItemWeight("Kayu Potong"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

            AccountData[playerid][pActivityTime] = 1;
            pCutWoodTimer[playerid] = true;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMOTONG KAYU");
            ShowProgressBar(playerid);

            ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, 1, 0, 0, 0, 0, 1);

            HideNotifBox(playerid);
        }
    
        if(IsPlayerInPackLog(playerid))
        {
            if(AccountData[playerid][pJob] != JOB_LUMBERJACK) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang Tukang Kayu!");
            if(!AccountData[playerid][pIsUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus menggunakan seragam kerja!");
            if(Inventory_Count(playerid, "Kayu Potong") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kayu Potong anda tidak cukup! (Min: 5)");
            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
            
            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(5 * GetItemWeight("Papan"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

            AccountData[playerid][pActivityTime] = 1;
            pGetBoardTimer[playerid] = true;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMBUAT PAPAN");
            ShowProgressBar(playerid);

            ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, 1, 0, 0, 0, 0, 1);

            HideNotifBox(playerid);
        }
    }
    return 1;
}