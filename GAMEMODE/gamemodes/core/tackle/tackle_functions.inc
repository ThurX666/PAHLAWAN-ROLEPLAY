Tackle_OnPlayerGiveDamage(playerid, damagedid, weaponid)
{
	#pragma unused weaponid

	new animindex = GetPlayerAnimationIndex(damagedid);
	if (!animindex || GetPlayerState(playerid) != PLAYER_STATE_ONFOOT || GetPlayerState(damagedid) != PLAYER_STATE_ONFOOT)
	{
		// Invalid tackle
		return 0;
	}

    static string[64];

    format(string, sizeof(string), "Anda telah terkena ~r~tackle~w~ oleh %s", AccountData[playerid][pName]);

    AccountData[damagedid][pTackleTime] = 15;
    AccountData[playerid][pTackleEnable] = false;
    TogglePlayerControllable(damagedid, false);

    SetPlayerDrunkLevel(damagedid, GetPlayerDrunkLevel(damagedid)+2000);

    ApplyAnimation(playerid, "DODGE", "Crush_Jump", 4.1, false, true, true, false, 0, true);
	ApplyAnimation(damagedid, "PED", "KO_shot_front", 4.1, false, true, true, true, 0, true);
    ShowPlayerFooter(damagedid, string, 10000);
    
    PlayerPlaySound(damagedid, 6003, 0.0, 0.0, 0.0);
	return 1;
}