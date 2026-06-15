YCMD:taser(playerid, params[], help)
{
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
	    return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berjalan kaki!");

	if (AccountData[playerid][pFaction] != FACTION_LSPD && AccountData[playerid][pFaction] != FACTION_SAGOV)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Kepolisian / Pemerintahan Pahlawan Roleplay!");

	if(AccountData[playerid][pUseBeanbag]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Simpan dahulu beanbag anda!");

	if(!AccountData[playerid][pTaser])
	{
	    AccountData[playerid][pTaser] = true;
	    GetPlayerWeaponData(playerid, 2, GunData[playerid][2][WeaponID], GunData[playerid][2][WeaponAmmo]);
		GunData[playerid][2][WeaponType] = WEAPON_TYPE_FACTION;
		GivePlayerWeapon(playerid, 23, 10);

        SendRPMeAboveHead(playerid, "Mengeluarkan taser dan siap untuk menembak.");
	}
	else
	{
	    AccountData[playerid][pTaser] = false;
		SetWeapons(playerid);

        SendRPMeAboveHead(playerid, "Menyarungkan kembali taser miliknya.");
		SetPlayerArmedWeapon(playerid, GunData[playerid][2][WeaponID]);
	}
	return 1;
}