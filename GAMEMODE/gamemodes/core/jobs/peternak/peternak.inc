#include <YSI_Coding\y_hooks>

enum E_SUSUSTUFF
{
    STREAMER_TAG_AREA:MilkerTakeArea,
    STREAMER_TAG_OBJECT:CowObject,
    MilkTaken
};
new PlayerMilkerVars[MAX_PLAYERS][E_SUSUSTUFF];

new Float: CowSpawn[][6] = {
    {-1496.929321, 1969.653076, 47.324443, 0.000000, 0.000000, 310.000000},
    {-1501.920166, 1971.417846, 47.374488, 0.000000, -0.000007, 234.999954},
    {-1505.783569, 1972.056518, 47.374450, 0.000000, -0.000007, 179.999954},
    {-1461.833496, 1977.191894, 47.284446, 0.000009, 0.000000, 129.999969},
    {-1456.557739, 1976.324096, 47.284446, 0.000003, 0.000003, -94.400032},
    {-1450.956787, 1976.484375, 47.284446, 0.000003, 0.000003, 94.999954},
    {-1464.698486, 1984.149414, 47.284446, -0.000007, 0.000014, 315.000000},
    {-1461.833496, 1986.552856, 47.284446, 0.000015, -0.000003, 199.999969},
    {-1455.523803, 1986.552856, 47.284446, 0.000009, 0.000000, 174.999984},
    {-1513.568847, 1984.149414, 47.154434, -0.000012, 0.000019, -44.999988},
    {-1450.114257, 1986.552856, 47.284446, 0.000009, 0.000000, 199.999984},
    {-1510.703857, 1986.552856, 47.154434, 0.000012, -0.000011, -159.999984},
    {-1505.012695, 1982.771606, 47.154434, 0.000014, 0.000011, 54.999927},
    {-1504.394165, 1986.552856, 47.154434, 0.000011, -0.000006, 174.999938},
    {-1498.984619, 1986.552856, 46.994445, 0.000007, -0.000006, -159.999969}
};

IsPlayerInMilkerProcess(playerid)
{
    for(new x; x < sizeof(__g_MilkProcessPos); x++)
    {
        if(IsPlayerInDynamicArea(playerid, MilkerProcessArea[x]))
        {
            return 1;
        }
    }
    return 0;
}

CheckMilkerTimer(playerid)
{
    if(pTakingSusuTimer[playerid]) return 1;
    else if(pProcessSusuTimer[playerid]) return 1;
    return 0;
}

Dialog:StartPeternak(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    switch(listitem)
    {
        case 0:
        {
            new rand = random(sizeof(CowSpawn));
            if(DestroyDynamicObject(PlayerMilkerVars[playerid][CowObject]))
                PlayerMilkerVars[playerid][CowObject] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
            if(DestroyDynamicArea(PlayerMilkerVars[playerid][MilkerTakeArea]))
                PlayerMilkerVars[playerid][MilkerTakeArea] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
            PlayerMilkerVars[playerid][MilkTaken] = 0;
            PlayerMilkerVars[playerid][CowObject] = CreateDynamicObject(19833, CowSpawn[rand][0], CowSpawn[rand][1], CowSpawn[rand][2], CowSpawn[rand][3], CowSpawn[rand][4], CowSpawn[rand][5], 0, 0, playerid, 300.00, 300.00); 
            PlayerMilkerVars[playerid][MilkerTakeArea] = CreateDynamicSphere(CowSpawn[rand][0], CowSpawn[rand][1], CowSpawn[rand][2], 2.2, 0, 0, playerid);
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memulai pekerjaan");

            if(AccountData[playerid][pGender] == 1)
            {
                AccountData[playerid][pUniform] = 161;
            }
            else
            {
                AccountData[playerid][pUniform] = 198;
            }
            SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
        }
        case 1:
        {
            if(DestroyDynamicObject(PlayerMilkerVars[playerid][CowObject]))
                PlayerMilkerVars[playerid][CowObject] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
            if(DestroyDynamicArea(PlayerMilkerVars[playerid][MilkerTakeArea]))
                PlayerMilkerVars[playerid][MilkerTakeArea] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
            PlayerMilkerVars[playerid][MilkTaken] = 0;
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyelesaikan pekerjaan");

            AccountData[playerid][pIsUsingUniform] = false;
		    SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
        }
    }
    return 1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(AccountData[playerid][pJob] == JOB_MILKER && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
        if(areaid == PlayerMilkerVars[playerid][MilkerTakeArea])
        {
            ShowNotifBox(playerid, "Tekan ~p~'Y' ~w~untuk perah Susu");
        }

        for(new x; x < sizeof(__g_MilkProcessPos); x++)
        {
            if(areaid == MilkerProcessArea[x])
            {
                ShowNotifBox(playerid, "Tekan ~p~'Y' ~w~untuk olah Susu");
            }
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(areaid == PlayerMilkerVars[playerid][MilkerTakeArea])
    {
        HideNotifBox(playerid);
        PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
    }

    for(new x; x < sizeof(__g_MilkProcessPos); x++)
    {
        if(areaid == MilkerProcessArea[x])
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
        if(IsPlayerInRangeOfPoint(playerid, 3.5, -1460.4857,2000.1849,48.2871))
        {
            if(AccountData[playerid][pJob] != JOB_MILKER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang Peternak!");

            HideNotifBox(playerid);
            Dialog_Show(playerid, "StartPeternak", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Peternak", 
            "Mulai perah susu\n\
            "GRAY"Selesaikan pekerjaan", "Pilih", "Batal");
        }

        if(IsPlayerInDynamicArea(playerid, PlayerMilkerVars[playerid][MilkerTakeArea]))
        {
            if(AccountData[playerid][pJob] != JOB_MILKER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang Peternak!");
            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
            
            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(5 * GetItemWeight("Susu"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");

            AccountData[playerid][pActivityTime] = 1;
            pTakingSusuTimer[playerid] = true;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMERAH SUSU");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.0, 1, 0, 0, 0, 0, 1);

            HideNotifBox(playerid);
        }

        if(IsPlayerInMilkerProcess(playerid))
        {
            if(AccountData[playerid][pJob] != JOB_MILKER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang Peternak!");
            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
            
            if(Inventory_Count(playerid, "Susu") < 10 || Inventory_Count(playerid, "Botol") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda perlu 10x Susu dan 5x Botol!");
            
            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(10 * GetItemWeight("Susu Fermentasi"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");

            AccountData[playerid][pActivityTime] = 1;
            pProcessSusuTimer[playerid] = true;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENGOLAH");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, true, false, false, false, 0, true);

            HideNotifBox(playerid);
        }
    }
    return 1;
}