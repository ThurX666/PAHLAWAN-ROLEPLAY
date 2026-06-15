YCMD:tackle(playerid, params[], help)
{
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
	    return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berjalan kaki!");

	if (AccountData[playerid][pFaction] != FACTION_LSPD)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Kepolisian Pahlawan Roleplay!");

	if(!AccountData[playerid][pTackleEnable])
	{
	    AccountData[playerid][pTackleEnable] = true;
        ShowTDN(playerid, NOTIFICATION_INFO, "Tackle mode ~g~aktif");
	}
	else
	{
	    AccountData[playerid][pTackleEnable] = false;
        ShowTDN(playerid, NOTIFICATION_INFO, "Tackle mode ~r~tidak aktif");
	}
	return 1;
}
YCMD:tk(playerid, params[], help) = tackle;