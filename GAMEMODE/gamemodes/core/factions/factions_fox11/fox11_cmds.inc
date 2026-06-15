YCMD:spawnsanewsheli(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] != FACTION_FOX11)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Pewarta Pahlawan Roleplay!");

    if(!AccountData[playerid][pOnDuty]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus on duty!");

    if(!IsPlayerInRangeOfPoint(playerid, 3.0, 734.7684,-1381.4521,25.6922)) return SEM(playerid, "You aren't at FOX 11 LA Studio Helipad!");

    if(Iter_Contains(Vehicle, JobVehicle[playerid]))
    {
        DestroyVehicle(JobVehicle[playerid]);

        ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mengembalikan helikopter Pewarta Pahlawan Roleplay.");
    }
    else
    {
        JobVehicle[playerid] = CreateVehicle(488, 741.0846,-1371.2528,25.8697,90.6813, 79, 1, 60000, false);
        VehicleCore[JobVehicle[playerid]][vCoreFuel] = 1000;
        SetValidVehicleHealth(JobVehicle[playerid], 2000.0); 
        VehicleCore[JobVehicle[playerid]][vMaxHealth] = 2000.0;
        VehicleCore[JobVehicle[playerid]][vIsBodyUpgraded] = true;
        VehicleCore[JobVehicle[playerid]][vIsBodyBroken] = false;
        VehicleCore[JobVehicle[playerid]][vCoreLocked] = false;
        SwitchVehicleEngine(JobVehicle[playerid], true);
        SwitchVehicleDoors(JobVehicle[playerid], false);

        ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mengeluarkan helikopter Pewarta Pahlawan Roleplay.");
    }
    return 1;
}

YCMD:broadcast(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] != FACTION_FOX11) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Pewarta Pahlawan Roleplay!");
    static string[144];
    format(string, sizeof(string), "Menu\tStatus\n\
    Start/End Broadcast\t%s\nToggle Broadcast Mic\t%s", (PlayerVoiceData[playerid][pBroadcast]) ? ("{00ff00}Started") : ("{FF0000}Not Started"), 
    (PlayerVoiceData[playerid][pIsCastMicOn]) ? ("{00ff00}Enabled") : ("{FF0000}Disabled"));
    Dialog_Show(playerid, "BroadcastMenu", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Broadcast Menu", string, "Pilih", "Batal");
    return 1;
}

YCMD:invitebc(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] != FACTION_FOX11) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Pewarta Pahlawan Roleplay!");

    new otherid;
    if(sscanf(params, "d", otherid)) return SUM(playerid, "/invitebc [playerid]");

    if(otherid == playerid) SEM(playerid, "Anda tidak dapat mengundang diri sendiri ke dalam broadcast!");
    if(!PlayerVoiceData[playerid][pBroadcast]) return SEM(playerid, "Anda belum melakukan live broadcast!");

    if(!IsPlayerNearPlayer(playerid, otherid, 3.5)) return SEM(playerid, "You are not close enough to the player!");
    PlayerVoiceData[otherid][pInBroadcast] = true;
    SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda berhasil mengundang Pemain tersebut sebagai pembicara di broadcast!");
    SendClientMessage(otherid, Y_PAHLAWAN, "<!> "WHITE"Anda diundang sebagai pembicara di broadcast, gunakan "CMDEA"'/micbc' "WHITE"untuk toggle mic live!");
    
    CallRemoteFunction("UpdatePlayerInviteBC", "id", otherid, 1);
    return 1;
}

YCMD:micbc(playerid, params[], help)
{
    if(!PlayerVoiceData[playerid][pInBroadcast]) return SEM(playerid, "Anda tidak diundang ke dalam broadcast apapun!");

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
    return 1;
}

YCMD:leavebc(playerid, params[], help)
{
    if(!PlayerVoiceData[playerid][pInBroadcast]) return SEM(playerid, "Anda tidak diundang ke dalam broadcast apapun!");
    PlayerVoiceData[playerid][pInBroadcast] = false;
    SendClientMessage(playerid, -1, "Anda berhasil keluar dari broadcast sebagai pembicara!");
    SendTeamMessage(FACTION_FOX11, Y_PAHLAWAN, "<!> "WHITE"Player "YELLOW"%s "WHITE"telah keluar dari live broadcast sebagai pembicara.", AccountData[playerid][pName]);
    
    CallRemoteFunction("UpdatePlayerInviteBC", "id", playerid, 0);
    return 1;
}

YCMD:kickbc(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] != FACTION_FOX11) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Pewarta Pahlawan Roleplay!");

    new otherid;
    if(sscanf(params, "d", otherid)) return SUM(playerid, "/invitebc [playerid]");

    if(otherid == playerid) SEM(playerid, "Anda tidak dapat menendang diri sendiri dari broadcast!");

    PlayerVoiceData[otherid][pInBroadcast] = false;
    SendClientMessage(otherid, -1, "Anda telah ditendang dari live broadcast sebagai pembicara!");
    SendTeamMessage(FACTION_FOX11, Y_PAHLAWAN, "<!> "WHITE"Player "YELLOW"%s "WHITE"telah dikeluarkan dari live broadcast oleh "YELLOW"%s.", AccountData[otherid][pName], AccountData[playerid][pName]);
    
    CallRemoteFunction("UpdatePlayerInviteBC", "id", otherid, 0);
    return 1;
}