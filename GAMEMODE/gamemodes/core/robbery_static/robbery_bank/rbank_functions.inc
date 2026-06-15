#include <YSI_Coding\y_hooks>

new bool:g_BankRobberyStarted,
    g_BankRobberyCooldown,
    g_BankRobberyCountdown,
    p_BankRobberyStep[MAX_PLAYERS],
    STREAMER_TAG_CP:p_BankRobberyCP[MAX_PLAYERS];

Dialog:BankHacking(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        AccountData[playerid][pQBRobbery] = 0;
        AccountData[playerid][pABRobbery][0] = EOS;
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan peretasan bank.");
        return 1;
    }

    new stta[512];
    if(isnull(inputtext))
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");

        format(stta, sizeof(stta), ""WHITE"Pacific Standard Public Deposit Bank\n\n\
        "RED"Hacking Bank on progress [%d/5]...\n\
        "WHITE"Please re-type this code:\n\n\
        "LIGHTYELLOW"%s", AccountData[playerid][pQBRobbery], GenerateRandomType(playerid));
        Dialog_Show(playerid, "BankHacking", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Hacking Bank", 
        stta, "Input", "Batal");
        return 1;
    }

    if(strcmp(inputtext, AccountData[playerid][pABRobbery] , false))
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Jawaban salah, alarm dibunyikan!");

        foreach(new i : LSPDDuty)
        {
            ShowFivemNotify(i, "SANEWS~n~BREAKING NEWS", "There has been an attempt to break into Bank Pacific", "hud:radar_cash", 25);
        }

        SendClientMessageToAll(Y_YELLOW, "[Perampokan] "WHITE"Telah terjadi upaya pembobolan Bank Pacific!");

        AccountData[playerid][pQBRobbery] = 1;

        format(stta, sizeof(stta), ""WHITE"Pacific Standard Public Deposit Bank\n\n\
        "RED"Hacking Bank on progress [%d/5]...\n\
        "WHITE"Please re-type this code:\n\n\
        "LIGHTYELLOW"%s", AccountData[playerid][pQBRobbery], GenerateRandomType(playerid));
        Dialog_Show(playerid, "BankHacking", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Hacking Bank", 
        stta, "Input", "Batal");
        return 1;
    }

    if(AccountData[playerid][pQBRobbery] >= 5)
    {
        AccountData[playerid][pQBRobbery] = 0;
        AccountData[playerid][pABRobbery][0] = EOS;

        g_BankRobberyStarted = true;
        g_BankRobberyCountdown = 600;

        AccountData[playerid][pDuringBRobbery] = true;

        foreach(new i : LSPDDuty)
        {
            ShowFivemNotify(i, "SANEWS~n~BREAKING NEWS", "Pacific Bank robbery in progress", "hud:radar_cash", 25);
        }

        ShowRobberyTD(playerid);

        UpdateDynamic3DTextLabelText(BankRobStatusLabel, Y_WHITE, "Pacific Standard Public Deposit Bank\n"YELLOW"/robbank\n\n"WHITE"Status: "YELLOW"Hacking");
        SendClientMessageToAll(X11_RED, "SANEWS: Pacific Bank robbery just occured, the LSPD advise citizen to avoid the location!");
        return 1;
    }
    
    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Jawaban benar, soal berikutnya juga harus benar!");
    AccountData[playerid][pQBRobbery]++;
    format(stta, sizeof(stta), ""WHITE"Pacific Standard Public Deposit Bank\n\n\
    "RED"Hacking Bank on progress [%d/5]...\n\
    "WHITE"Please re-type this code:\n\n\
    "LIGHTYELLOW"%s", AccountData[playerid][pQBRobbery], GenerateRandomType(playerid));
    Dialog_Show(playerid, "BankHacking", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Hacking Bank", 
    stta, "Input", "Batal");
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && AccountData[playerid][pDuringBRobbery] && p_BankRobberyStep[playerid] > 0)
    {
        if(IsValidDynamicCP(p_BankRobberyCP[playerid]) && IsPlayerInDynamicCP(playerid, p_BankRobberyCP[playerid]))
        {
            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
            
            AccountData[playerid][pActivityTime] = 1;
            p_BankRTakeMoneyTimer[playerid] = true;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENGAMBIL UANG");
            ShowProgressBar(playerid);

            ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, true, false, false, false, 0, true);

            HideNotifBox(playerid);
        }
    }
    return 1;
}

hook OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP:checkpointid)
{
    if(checkpointid == p_BankRobberyCP[playerid])
    {
        ShowNotifBox(playerid, "Tekan ~y~'Y' ~w~Kumpulkan Uang");
    }
    return 1;
}

hook OnPlayerLeaveDynamicCP(playerid, STREAMER_TAG_CP:checkpointid)
{
    if(checkpointid == p_BankRobberyCP[playerid])
    {
        HideNotifBox(playerid);
        PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
    }
    return 1;
}

task BankRobCooldownCheck[1500]()
{
    if(!IsValidDynamicObject(BankVault))
    {
        if(!g_BankRobberyStarted)
        {
            if(g_BankRobberyCooldown != 0 && g_BankRobberyCooldown < gettime())
            {
                if(DestroyDynamicObject(BankVault))
                    BankVault = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
                    
                BankVault = CreateDynamicObject(19799, 1444.822631, -1124.319946, 24.488027, 0.000000, 0.000000, 579.799987, 0, 0, -1, 200.00, 200.00);

                UpdateDynamic3DTextLabelText(BankRobStatusLabel, Y_WHITE, "Pacific Standard Public Deposit Bank\n"YELLOW"/robbank\n\n"WHITE"Status: "GREEN"Ready");

                g_BankRobberyCooldown = 0;
            }
        }
    }
    return 1;
}

ptask BankRobCountUpdate[1000](playerid) 
{
    if(IsPlayerConnected(playerid) && AccountData[playerid][IsLoggedIn] && AccountData[playerid][pSpawned] && AccountData[playerid][pDuringBRobbery] && g_BankRobberyStarted)
    {
        if(g_BankRobberyCountdown > 0)
        {
            g_BankRobberyCountdown--;
            
            PlayerTextDrawSetString(playerid, perampokanTD[playerid], sprintf("Mohon tetap di Bank Pacific selama %d menit %02d detik", g_BankRobberyCountdown/60, g_BankRobberyCountdown % 3600 % 60));
        }
        else
        {
            g_BankRobberyStarted = false;
            g_BankRobberyCountdown = 0;
            g_BankRobberyCooldown = gettime() + 3600;

            p_BankRobberyStep[playerid] = 1;

            UpdateDynamic3DTextLabelText(BankRobStatusLabel, Y_WHITE, "Pacific Standard Public Deposit Bank\n"YELLOW"/robbank\n\n"WHITE"Status: "RED"Unready");

            ShowFivemNotify(playerid, "Pahlawan Roleplay~n~PERAMPOKAN BANK", "Bank Pacific berhasil dihack, ambil semua barang di brankas!", "hud:radar_cash", 25);

            if(DestroyDynamicObject(BankVault))
                BankVault = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

            if(DestroyDynamicCP(p_BankRobberyCP[playerid]))
                p_BankRobberyCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
            
            p_BankRobberyCP[playerid] = CreateDynamicCP(1443.5103,-1123.1447,23.9590, 1.5, 0, 0, playerid, 5.5, -1, 0);

            HideRobberyTD(playerid);
        }
    }
    return 1;
}