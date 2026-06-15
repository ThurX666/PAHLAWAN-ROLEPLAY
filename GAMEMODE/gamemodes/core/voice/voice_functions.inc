#include <YSI_Coding\y_hooks>

enum e_player_voice_stuff
{
    bool:pHasRadio,
    bool:pIsRadioOn,
    bool:pIsRadioMicOn,
    bool:pIsMegaOn,
    bool:pBroadcast,
    bool:pInBroadcast,
    bool:pIsCastMicOn,
    //VoiceModeDistance,
    pRadioFreq
};
new PlayerVoiceData[MAX_PLAYERS][e_player_voice_stuff];

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    /*if(newkeys & KEY_NO && AccountData[playerid][pSpawned] && AccountData[playerid][IsLoggedIn])
    {
        switch(PlayerVoiceData[playerid][VoiceModeDistance])
        {
            case 1: //jika dalam mode berbisik
            {
                PlayerVoiceData[playerid][VoiceModeDistance] = 2;
                CallRemoteFunction("UpdatePlayerVoiceDistance", "if", playerid, 15.0);
                PlayerTextDrawSetString(playerid, RadioVoiceInfoTD[playerid], "VOICE: ~b~NORMAL");
            }
            case 2: //jika dalam mode normal
            {
                PlayerVoiceData[playerid][VoiceModeDistance] = 3;
                CallRemoteFunction("UpdatePlayerVoiceDistance", "if", playerid, 35.5);
                PlayerTextDrawSetString(playerid, RadioVoiceInfoTD[playerid], "VOICE: ~r~TERIAK");
            }
            case 3: //jika dalam mode teriak
            {
                PlayerVoiceData[playerid][VoiceModeDistance] = 1;
                CallRemoteFunction("UpdatePlayerVoiceDistance", "if", playerid, 5.5);
                PlayerTextDrawSetString(playerid, RadioVoiceInfoTD[playerid], "VOICE: ~y~BISIK");
            }
        }
    }*/

    //jika jalan kaki
    if(PRESSED(KEY_WALK) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && AccountData[playerid][pSpawned] && AccountData[playerid][IsLoggedIn] && PlayerVoiceData[playerid][pHasRadio] && PlayerVoiceData[playerid][pIsRadioOn])
    {
        switch(PlayerVoiceData[playerid][pIsRadioMicOn])
        {
            case false:
            {
                PlayerVoiceData[playerid][pIsRadioMicOn] = true;
                CallRemoteFunction("UpdatePlayerVoiceMicToggle", "id", playerid, 1);
                GameTextForPlayer(playerid, "Mic radio~n~~g~on", 5000, 6);
            }
            case true:
            {
                PlayerVoiceData[playerid][pIsRadioMicOn] = false;
                CallRemoteFunction("UpdatePlayerVoiceMicToggle", "id", playerid, 0);
                GameTextForPlayer(playerid, "Mic radio~n~~r~off", 5000, 6);
            }
        }
    }
    //jika di kendaraan
    else if(PRESSED(KEY_FIRE) && (GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER) && AccountData[playerid][pSpawned] && AccountData[playerid][IsLoggedIn] && PlayerVoiceData[playerid][pHasRadio] && PlayerVoiceData[playerid][pIsRadioOn])
    {
        switch(PlayerVoiceData[playerid][pIsRadioMicOn])
        {
            case false:
            {
                PlayerVoiceData[playerid][pIsRadioMicOn] = true;
                CallRemoteFunction("UpdatePlayerVoiceMicToggle", "id", playerid, 1);
                GameTextForPlayer(playerid, "Mic radio~n~~g~on", 5000, 6);
            }
            case true:
            {
                PlayerVoiceData[playerid][pIsRadioMicOn] = false;
                CallRemoteFunction("UpdatePlayerVoiceMicToggle", "id", playerid, 0);
                GameTextForPlayer(playerid, "Mic radio~n~~r~off", 5000, 6);
            }
        }
    }
    return 1;
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
    if(clickedid == RadioVoiceTD[8])
    {
        if(PlayerVoiceData[playerid][pHasRadio])
        {
            switch(PlayerVoiceData[playerid][pIsRadioOn])
            {
                case false:
                {
                    PlayerVoiceData[playerid][pIsRadioOn] = true;
                    CallRemoteFunction("UpdatePlayerVoiceRadioToggle", "id", playerid, 1);
                    ShowTDN(playerid, NOTIFICATION_INFO, "Radio sekarang ~g~hidup");
                }
                case true:
                {
                    PlayerVoiceData[playerid][pIsRadioOn] = false;
                    CallRemoteFunction("UpdatePlayerVoiceRadioToggle", "id", playerid, 0);
                    ShowTDN(playerid, NOTIFICATION_INFO, "Radio sekarang ~r~mati");
                }
            }
            HideRadioVoiceTD(playerid);
        }
    }
    else if(clickedid == RadioVoiceTD[7])
    {
        if(PlayerVoiceData[playerid][pHasRadio])
        {
            Dialog_Show(playerid, "SetRadioFreq", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Radio Fx", 
            "Masukkan frekuensi radio yang ingin ditetapkan pada kolom di bawah ini\n\
            (Frekuensi harus berada di antara 0 - 9999)\n\
            Catatan: Masukkan frekuensi 0 untuk memutuskan saluran frekuensi/netral", "Set", "Batal");
        }
    }
    else if(clickedid == RadioVoiceTD[9])
    {
        HideRadioVoiceTD(playerid);
    }
    return 1;
}

Dialog:BroadcastMenu(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    switch(listitem)
    {
        case 0: //toggle boradcast
        {
            switch(PlayerVoiceData[playerid][pBroadcast])
            {
                case true:
                {
                    PlayerVoiceData[playerid][pBroadcast] = false;
                    PlayerVoiceData[playerid][pIsCastMicOn] = false;
                    CallRemoteFunction("UpdatePlayerBroadcast", "id", playerid, 0);
                    CallRemoteFunction("UpdatePlayerCastToggle", "id", playerid, 0);

                    foreach(new i : Player) if(AccountData[i][pSpawned])
                    {
                        if(PlayerVoiceData[i][pInBroadcast])
                        {
                            PlayerVoiceData[i][pInBroadcast] = false;
                            CallRemoteFunction("UpdatePlayerInviteBC", "id", i, 0);
                        }
                    }
                    
                    SendClientMessageToAllEx(X11_SLATEBLUE2, "Pewarta Pahlawan: %s has completed the live broadcast, thank you.", AccountData[playerid][pName]);
                }
                case false:
                {
                    ToggleInfo[playerid][TogBroadcast] = true;
                    PlayerVoiceData[playerid][pBroadcast] = true;
                    CallRemoteFunction("UpdatePlayerBroadcast", "id", playerid, 1);
                    SendClientMessageToAllEx(X11_SLATEBLUE2, "Pewarta Pahlawan: %s has started the live broadcast, enjoy listening.", AccountData[playerid][pName]);
                }
            }
        }
        case 1: //toggle mic broadcast
        {
            switch(PlayerVoiceData[playerid][pIsCastMicOn])
            {
                case false:
                {
                    PlayerVoiceData[playerid][pIsCastMicOn] = true;
                    CallRemoteFunction("UpdatePlayerCastToggle", "id", playerid, 1);
                    GameTextForPlayer(playerid, "Mic cast~n~~g~on", 5000, 6);
                }
                case true:
                {
                    PlayerVoiceData[playerid][pIsCastMicOn] = false;
                    CallRemoteFunction("UpdatePlayerCastToggle", "id", playerid, 0);
                    GameTextForPlayer(playerid, "Mic cast~n~~r~off", 5000, 6);
                }
            }
        }
    }
    return 1;
}
Dialog:SetRadioFreq(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    new dfreq = strval(inputtext);

    if(dfreq < 0 || dfreq > 9999)
    {
        Dialog_Show(playerid, "SetRadioFreq", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Radio Fx", 
        "Masukkan frekuensi radio yang ingin ditetapkan pada kolom di bawah ini\n\
        (Frekuensi harus berada di antara 0 - 9999)\n\
        Catatan: Masukkan frekuensi 0 untuk memutuskan saluran frekuensi/netral", "Set", "Batal");
        return 1;
    }

    switch(dfreq)
    {
        case 1: //main freq pd
        {
            if(AccountData[playerid][pFaction] != FACTION_LSPD && AccountData[playerid][pFaction] != FACTION_LSFD)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Freq 1 khusus Polisi tetapi bisa diakses EMS!");
        }
        case 2.. 21:
        {
            if(AccountData[playerid][pFaction] != FACTION_LSPD)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Freq 2 - 21 khusus polisi!");
        }
        case 22:
        {
            if(AccountData[playerid][pFaction] != FACTION_LSPD && AccountData[playerid][pFaction] != FACTION_LSFD)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Freq 22 khusus EMS tetapi bisa diakses Polisi!");
        }
        case 23:
        {
            if(AccountData[playerid][pFaction] != FACTION_SAGOV)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Freq 23 khusus Pemerintah!");
        }
        case 24:
        {
            if(AccountData[playerid][pFaction] != FACTION_BENNYS)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Freq 24 khusus Bengkel Bennys!");
        }
        case 25:
        {
            if(AccountData[playerid][pFaction] != FACTION_UBER)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Freq 25 khusus Uber!");
        }
        case 26:
        {
            if(AccountData[playerid][pFaction] != FACTION_FOX11)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Freq 26 khusus Pewarta Berita!");
        }
    }

    CallRemoteFunction("AssignFreqToFSVoice", "idd", playerid, PlayerVoiceData[playerid][pHasRadio], dfreq);

    PlayerVoiceData[playerid][pRadioFreq] = dfreq;

    new strls[128];
    format(strls, sizeof(strls), "%d", PlayerVoiceData[playerid][pRadioFreq]);
    PlayerTextDrawSetString(playerid, RadioVoiceFreqTD[playerid], strls);
    ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Anda berhasil masuk ke freq %d", dfreq));
    HideRadioVoiceTD(playerid);
    return 1;
}