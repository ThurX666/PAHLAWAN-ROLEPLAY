#include <YSI_Coding\y_hooks>

AssignPlayerComma(playerid)
{
    static frmtsql[215];
    DestroyJobVehicle(playerid);

    AccountData[playerid][pKnockdown] = false;
    AccountData[playerid][pKnockdownTime] = 0;
    AccountData[playerid][pComma] = false;

    SetPlayerHealthEx(playerid, 100.00);
    AccountData[playerid][pHunger] = 100;
    AccountData[playerid][pThirst] = 100;
    AccountData[playerid][pStress] = 0;

    DeathCause[playerid][Bruised] = false;
    DeathCause[playerid][Shoted] = false;
    DeathCause[playerid][Burns] = false;
    DeathCause[playerid][Drown] = false;
    DeathCause[playerid][Fallen] = false;

    AccountData[playerid][pInRusun] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInGudang] = -1;

	mysql_format(g_SQL, frmtsql, sizeof(frmtsql), "UPDATE `player_characters` SET `Char_Knockdown` = 0, `Char_KnockdownTime` = 0, `Char_Hunger` = 100, `Char_Thirst` = 100, `Char_Stress` = 0 WHERE `pID` = %d", AccountData[playerid][pID]);
    mysql_pquery(g_SQL, frmtsql);
    ResetPlayerMoneyEx(playerid);
    Inventory_Clear(playerid);
    ResetPlayerWeaponsEx(playerid);

    HideKnockTD(playerid);
    StopRunningAnimation(playerid);

    new rand = random(sizeof(CommaSpawn));
    SetPlayerPositionEx(playerid, CommaSpawn[rand][0], CommaSpawn[rand][1], CommaSpawn[rand][2], CommaSpawn[rand][3]);
    SetPlayerVirtualWorldEx(playerid, 0);
    SetPlayerInteriorEx(playerid, 0);
    SetCameraBehindPlayer(playerid);

    SendTeamMessage(FACTION_LSFD, Y_YELLOW, "[Koma] "RED"%s [%s] (%d) "WHITE"telah sadar dari koma di ruangan ICU.", GetPlayerRoleplayName(playerid), AccountData[playerid][pUCP], playerid);
}

forward OnPlayerKnockdown(playerid);
public OnPlayerKnockdown(playerid)
{
    if(IsPlayerConnected(playerid))
    {
        if(AccountData[playerid][pJob] == JOB_FARMER)
        {
            if(CheckFarmerTimer(playerid))
            {
                pTakingPlantTimer[playerid] = false;
                pProcessChiliTimer[playerid] = false;
                pProcessRiceTimer[playerid] = false;
                pPorcessSugarTimer[playerid] = false;

                AccountData[playerid][pActivityTime] = 0;
                HideProgressBar(playerid);

                ClearAnimations(playerid, true);
                StopLoopingAnim(playerid);
                SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
                TogglePlayerControllable(playerid, true);
            }

            PlayerFarmerVars[playerid][pDuringTakingPlant] = false;
        }
        else if(AccountData[playerid][pJob] == JOB_LUMBERJACK)
        {
            if(CheckLumberjackTimer(playerid))
            {
                pTakeWoodTimer[playerid] = false;
                pCutWoodTimer[playerid] = false;
                pGetBoardTimer[playerid] = false;

                AccountData[playerid][pActivityTime] = 0;

                AccountData[playerid][pCountingValue] = 0;
                HideProgressBar(playerid);

                ClearAnimations(playerid, true);
                StopLoopingAnim(playerid);
                SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
                TogglePlayerControllable(playerid, true);
            }
        }
        else if(AccountData[playerid][pJob] == JOB_MINER)
        {
            if(CheckMinerTimer(playerid))
            {
                pTakingStoneTimer[playerid] = false;
                pWashingStoneTimer[playerid] = false;
                pSmeltingStoneTimer[playerid] = false;

                AccountData[playerid][pActivityTime] = 0;
                HideProgressBar(playerid);

                ClearAnimations(playerid, true);
                StopLoopingAnim(playerid);
                SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
                TogglePlayerControllable(playerid, true);

                if(IsPlayerAttachedObjectSlotUsed(playerid, 9)) 
                    RemovePlayerAttachedObject(playerid, 9);
            }
        }
        else if(AccountData[playerid][pJob] == JOB_BUTCHER)
        {
            if(CheckButcherTimer(playerid))
            {
                pTakingChickTimer[playerid] = false;
                pCutingChickTimer[playerid] = false;
                pPackingChickTimer[playerid] = false;

                AccountData[playerid][pActivityTime] = 0;
                HideProgressBar(playerid);

                ClearAnimations(playerid, true);
                StopLoopingAnim(playerid);
                SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
                TogglePlayerControllable(playerid, true);
            }
        }
        else if(AccountData[playerid][pJob] == JOB_OILMAN)
        {
            if(CheckOilmanTimer(playerid))
            {
                pTakingOilTimer[playerid] = false;
                pRefiningOilTimer[playerid] = false;
                pMixingOilTimer[playerid] = false;

                AccountData[playerid][pActivityTime] = 0;
                HideProgressBar(playerid);

                ClearAnimations(playerid, true);
                StopLoopingAnim(playerid);
                SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
                TogglePlayerControllable(playerid, true);
            }
        }
        else if(AccountData[playerid][pJob] == JOB_FISHERMAN)
        {
            if(CheckFishermanTimer(playerid))
            {
                pTakingFishTimer[playerid] = false;

                AccountData[playerid][pActivityTime] = 0;
                HideProgressBar(playerid);
                TogglePlayerControllable(playerid, true);
            }
        }
        else if(AccountData[playerid][pJob] == JOB_MILKER)
        {
            if(CheckMilkerTimer(playerid))
            {
                pTakingSusuTimer[playerid] = false;
                pProcessSusuTimer[playerid] = false;

                AccountData[playerid][pActivityTime] = 0;
                HideProgressBar(playerid);

                ClearAnimations(playerid, true);
                StopLoopingAnim(playerid);
                SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
                TogglePlayerControllable(playerid, true);
            }
        }
        else if(AccountData[playerid][pJob] == JOB_TAILOR)
        {
            if(CheckTailorTimer(playerid))
            {
                pTakingWoolTimer[playerid] = false;
                pMakingFabricTimer[playerid] = false;
                pClothingTimer[playerid] = false;

                AccountData[playerid][pActivityTime] = 0;
                HideProgressBar(playerid);

                ClearAnimations(playerid, true);
                StopLoopingAnim(playerid);
                SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
                TogglePlayerControllable(playerid, true);
            }
        }

        //illegal & activity
        if(pTakingKanabisTimer[playerid] && AccountData[playerid][pInCannabis] > -1)
        {
            pTakingKanabisTimer[playerid] = false;
            KanabisData[AccountData[playerid][pInCannabis]][kanabisTaken] = false;

            AccountData[playerid][pInCannabis] = -1;

            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;
        }

        if(pProcessKanabisTimer[playerid])
        {
            pProcessKanabisTimer[playerid] = false;

            HideProgressBar(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            AccountData[playerid][pActivityTime] = 0;
        }

        if(AccountData[playerid][pDuringRobbery])
        {
            AccountData[playerid][pDuringRobbery] = false;
            GM[ShopRobberyOngoing] = false;
		    RobberyCountdown[playerid] = 0;
		    GM[ShopRobberyCooldown] = gettime() + 1200;
            AccountData[playerid][pInRobberyID] = -1;
            HideRobberyTD(playerid);

            foreach(new x : LSPDDuty)
            {
                if(DestroyDynamicMapIcon(AccountData[playerid][pSignalRobberyIcon][x]))
                    AccountData[playerid][pSignalRobberyIcon][x] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
        }

        if(AccountData[playerid][pDuringBRobbery])
        {
            p_BankRTakeMoneyTimer[playerid] = false;
            
            AccountData[playerid][pDuringBRobbery] = false;
            g_BankRobberyStarted = false;
		    g_BankRobberyCooldown = 3600;
		    g_BankRobberyCountdown = 0;

            HideRobberyTD(playerid);

            p_BankRobberyStep[playerid] = 0;

            if(DestroyDynamicCP(p_BankRobberyCP[playerid]))
                p_BankRobberyCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        }

        if(AccountData[playerid][pDuringCarsteal])
        {
	        pCarstealPartTimer[playerid] = false;

            AccountData[playerid][pDuringCarsteal] = false;
            g_CarstealCarFound[playerid] = false;
            g_CarstealCarDelivered[playerid] = false;
            AccountData[playerid][pCarstealHoldingPart] = false;
            g_CarstealStepPart[playerid] = 0;

            g_IsCarstealStarted = false;
            g_CarstealCountdown = 0;
            g_CarstealCooldown = gettime() + 1800;
            
            ResetAllRaceCP(playerid);

            DestroyVehicle(g_CarstealCarPhysic[playerid]);

            if(DestroyDynamic3DTextLabel(AccountData[playerid][pCarstealLabelPart]))
                AccountData[playerid][pCarstealLabelPart] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

            if(DestroyDynamicCP(AccountData[playerid][pCarstealStoringCP]))
                AccountData[playerid][pCarstealStoringCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

            foreach(new x : LSPDDuty)
            {
                if(DestroyDynamicMapIcon(AccountData[playerid][g_CarstealIcon][x]))
                    AccountData[playerid][g_CarstealIcon][x] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
        }

        if(AccountData[playerid][pSideJob] == SIDEJOB_FORKLIFT)
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

            gPlayerUsingLoopingAnim[playerid] = false;
            TogglePlayerControllable(playerid, true);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            RemovePlayerAttachedObject(playerid, 9);
            StopRunningAnimation(playerid);
        }

        if(AccountData[playerid][pSideJob] == SIDEJOB_TRASHCOLLECTOR)
        {
            TrashCollectorHoldingBag[playerid] = false;
            AccountData[playerid][pSideJob] = SIDEJOB_NONE;
            TrashCollected[playerid] = 0;

            for (new i; i < 25; i++) 
            {
                if(DestroyDynamicCP(TrashCollectorCP[playerid][i]))
                    TrashCollectorCP[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                if(DestroyDynamicMapIcon(TrashCollectorIcon[playerid][i]))
                    TrashCollectorIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;

                selectedGarbage[playerid][i] = -1;
            }

            if(DestroyDynamicCP(TrashCollectorRVehCP[playerid]))
                TrashCollectorRVehCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

            if(DestroyDynamicCP(TrashCollectorBackCP[playerid]))
                TrashCollectorBackCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

            AccountData[playerid][pTrashCollectorDelay] = 1800;

            SetTimerEx("RespawnPV", 1000, false, "d", TrashCollectorPlayerVeh[playerid]);

            TrashCollectorPlayerVeh[playerid] = INVALID_VEHICLE_ID;

            gPlayerUsingLoopingAnim[playerid] = false;
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            RemovePlayerAttachedObject(playerid, 9);
            StopRunningAnimation(playerid);
        }

        if(AccountData[playerid][pSideJob] == SIDEJOB_PIZZA)
        {
            DestroyVehicle(JobVehicle[playerid]);

            if(DestroyDynamicCP(pizzaDeliveryCP[playerid]))
                pizzaDeliveryCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

            if(DestroyDynamicActor(pizzaDeliveryActor[playerid]))
                pizzaDeliveryActor[playerid] = STREAMER_TAG_ACTOR: INVALID_STREAMER_ID;

            if(DestroyDynamicRaceCP(pizzaDeliveryRCP[playerid]))
                pizzaDeliveryRCP[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

            AccountData[playerid][pSideJob] = SIDEJOB_NONE;
            pizzaDelivered[playerid] = 0;
            pizzaRandom[playerid] = -1;
            pizzaHoldingBox[playerid] = false;

            AccountData[playerid][pPizzaSidejobDelay] = 1800;

            gPlayerUsingLoopingAnim[playerid] = false;
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            RemovePlayerAttachedObject(playerid, 9);
            StopRunningAnimation(playerid);

            TogglePlayerControllable(playerid, true);
        }

        HideNotifBox(playerid);
        HideClothesShopTD(playerid);
        Inventory_Close(playerid);
        HideLCTD(playerid);
        HideProgressBar(playerid);
        HideAllPhoneTD(playerid);
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && AccountData[playerid][pKnockdown] && AccountData[playerid][pKnockdownTime] > 0 && !OJailData[playerid][jailed] && AccountData[playerid][IsLoggedIn])
    {
        Dialog_Show(playerid, "PlayerComma", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Konfirmasi Koma", 
        ""WHITE"Anda akan koma, perlu diketahui bahwa yang terjadi setelah anda koma:\n\
        "YELLOW"- Semua senjata akan hilang.\n\
        - Semua barang di inventory akan hilang.\n\
        - Uang di saku anda akan direset jadi $0.\n\
        - Anda akan spawn di dalam rumah sakit.\n\n\
        "RED"( Apakah anda setuju untuk koma? )", "Yes", "No");
    }
    else if(newkeys & KEY_NO && AccountData[playerid][pKnockdown] && AccountData[playerid][pKnockdownTime] > 0 && !OJailData[playerid][jailed] && AccountData[playerid][IsLoggedIn])
    {
        if(AccountData[playerid][pDelayKnockdownSignalSent] > gettime())
        {
            return ShowTDN(playerid, NOTIFICATION_WARNING, "Mohon menunggu beberapa saat sebelum mengirimkan signal kembali!");
        }
        ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengirimkan signal kepada paramedis");
        AccountData[playerid][pDelayKnockdownSignalSent] = gettime() + 60;

        static Float:px, Float:py, Float:pz;
        GetPlayerPos(playerid, px, py, pz);
        foreach(new i : LSFDDuty)
        {
            SendClientMessageEx(i, Y_YELLOW, "[Pasien Pingsan] "WHITE"Sinyal baru telah masuk dari daerah %s.", GetLocation(px, py, pz));
        }
    }
    return 1;
}

ptask UpdateKnockTime[1000](playerid) 
{
    if(AccountData[playerid][pKnockdown] && !OJailData[playerid][jailed] && AccountData[playerid][IsLoggedIn])
    {
        if(AccountData[playerid][pKnockdownTime] > 0)
        {
            AccountData[playerid][pKnockdownTime]--;
            PlayerTextDrawSetString(playerid, HABISDARAHTD[playerid], sprintf("%02d menit %02d detik", AccountData[playerid][pKnockdownTime] / 60 % 60, AccountData[playerid][pKnockdownTime] % 3600 % 60));
            SetPlayerHealth(playerid, 1000);

            if(!AccountData[playerid][pDetained])
            {
                ApplyAnimation(playerid, "WUZI", "CS_DEAD_GUY", 4.1, false, false, false, true, 0, true);
            }
        }
        else
        {
            AssignPlayerComma(playerid);
            SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda koma karena tidak diselamatkan tepat waktu dan kehilangan banyak darah.");
            SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Seluruh senjata, barang di tas dan uang di saku telah dimusnahkan karena koma.");
        }
    }
    return 1;
}

ptask UpdateCuffTime[1000](playerid) 
{
    if((AccountData[playerid][pCuffed] || AccountData[playerid][pBlindfolded]) && !IsPlayerInAnyVehicle(playerid))
    {
        if(AccountData[playerid][pBlindfolded])
        {
            if(!IsPlayerAttachedObjectSlotUsed(playerid, 9))
                SetPlayerAttachedObject(playerid, 9, 2663, 2, 0.049999, -0.009999, -0.005999, -10.099994, -98.199989, -5.000000, 0.873000, 1.524000, 0.623999);
        }

        if(GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_CUFFED)
        {
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CUFFED);
        }
    }
    return 1;
}