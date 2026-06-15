YCMD:r(playerid, params[], help)
{
    if(!PlayerVoiceData[playerid][pHasRadio]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki radio!");
    if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
    if(AccountData[playerid][pCuffed]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");

    new strls[128];
    format(strls, sizeof(strls), "%d", PlayerVoiceData[playerid][pRadioFreq]);
    PlayerTextDrawSetString(playerid, RadioVoiceFreqTD[playerid], strls);
    ShowRadioVoiceTD(playerid);

    if(!IsPlayerInAnyVehicle(playerid))
	{
        ApplyAnimation(playerid, "ped","Jetpack_Idle", 4.1, false, false, false, true, 0, true);
	    SetPlayerAttachedObject(playerid, 9, 19942, 5, 0.043000, 0.022999, -0.006000, -112.000022, -34.900020, -8.500002, 1.000000, 1.000000, 1.000000);
    }
    return 1;
}

YCMD:m(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");
    
    if(!PlayerVoiceData[playerid][pIsMegaOn])
    {
        CallRemoteFunction("UpdateVoiceMegaStatus", "id", playerid, 1);
        GameTextForPlayer(playerid, "Megaphone ~g~On", 3500, 4);
        PlayerVoiceData[playerid][pIsMegaOn] = true;
    }
    else
    {
        CallRemoteFunction("UpdateVoiceMegaStatus", "id", playerid, 0);
        GameTextForPlayer(playerid, "Megaphone ~r~Off", 3500, 4);
        PlayerVoiceData[playerid][pIsMegaOn] = false;
    }
    return 1;
}

YCMD:tac(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");
    
    new choosefreq;

    if(sscanf(params, "d", choosefreq)) return SyntaxMsg(playerid, "/tac [0 - 20]");

    if(choosefreq < 0 || choosefreq > 20) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Tac Freq!");

    switch(choosefreq)
    {
        case 0:
        {
            PlayerVoiceData[playerid][pIsRadioOn] = true;
            PlayerVoiceData[playerid][pRadioFreq] = 1;
            CallRemoteFunction("UpdatePlayerVoiceRadioToggle", "id", playerid, 1);
            CallRemoteFunction("AssignFreqToFSVoice", "idd", playerid, PlayerVoiceData[playerid][pHasRadio], 1);


            GameTextForPlayer(playerid, "Switched to ~y~Main Freq", 3500, 4);
        }
        default:
        {
            PlayerVoiceData[playerid][pIsRadioOn] = true;
            PlayerVoiceData[playerid][pRadioFreq] = choosefreq+1;
            CallRemoteFunction("UpdatePlayerVoiceRadioToggle", "id", playerid, 1);
            CallRemoteFunction("AssignFreqToFSVoice", "idd", playerid, PlayerVoiceData[playerid][pHasRadio], choosefreq+1);


            GameTextForPlayer(playerid, sprintf("Switched to ~y~Tac-%d", choosefreq), 3500, 4);
        }
    }
    return 1;
}