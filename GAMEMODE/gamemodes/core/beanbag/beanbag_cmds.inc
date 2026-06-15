YCMD:beanbag(playerid, params[], help)
{
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
	    return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berjalan kaki!");

	if (AccountData[playerid][pFaction] != FACTION_LSPD)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Kepolisian Pahlawan Roleplay!");

	if(AccountData[playerid][pTaser]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Simpan dahulu taser anda!");

	if(!AccountData[playerid][pUseBeanbag])
	{
	    AccountData[playerid][pUseBeanbag] = true;
	    GetPlayerWeaponData(playerid, 3, GunData[playerid][3][WeaponID], GunData[playerid][3][WeaponAmmo]);
		GunData[playerid][3][WeaponType] = WEAPON_TYPE_FACTION;
		GivePlayerWeapon(playerid, 25, 10);

        SendRPMeAboveHead(playerid, "Mengeluarkan beanbag dan siap untuk menembak.");
	}
	else
	{
	    AccountData[playerid][pUseBeanbag] = false;
		SetWeapons(playerid);

        SendRPMeAboveHead(playerid, "Menyimpan kembali beanbag miliknya.");
		SetPlayerArmedWeapon(playerid, GunData[playerid][3][WeaponID]);
	}
	return 1;
}
YCMD:bb(playerid, params[], help) = beanbag;