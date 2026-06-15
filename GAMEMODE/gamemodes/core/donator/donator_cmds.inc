YCMD:dtag(playerid, params[], help)
{
    if(AccountData[playerid][pVIP] == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Fitur ini hanya untuk donatur VIP!");

    new dtagn[128], query[128];
	if(sscanf(params, "s[128]", dtagn)) return SUM(playerid, "/dtag [your tag]");
	
	mysql_format(g_SQL, query, sizeof(query), "SELECT `Char_DonatorTag` FROM `player_characters` WHERE `Char_DonatorTag`='%e'", dtagn);
	mysql_pquery(g_SQL, query, "SetDTag", "is", playerid, dtagn);
    return 1;
}

YCMD:dvradio(playerid, params[], help)
{
    if(AccountData[playerid][pVIP] == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Fitur ini hanya untuk donatur VIP!");

    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di kursi pengemudi!");

    if(IsABike(SavingVehID[playerid]) || !IsEngineVehicle(SavingVehID[playerid])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak valid!");

    Dialog_Show(playerid, "VIPVehicleRadio", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Donator Vehicle Radio", 
    "Pahlawan Roleplay Donator Radio System\n\n\
    Kami sarankan anda untuk upload file mp3 ke discord terlebih dahulu.\n\
    "RED"Note: Fitur ini tidak support link YouTube secara langsung!\n\n\
    "YELLOW"(Apabila file mp3 telah di upload ke discord, silahkan copy linknya dan paste di bawah ini):", "Input", "Batal");
    return 1;
}