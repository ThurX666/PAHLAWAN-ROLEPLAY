#include <YSI_Coding\y_hooks>

forward OnBeanbagShoot(playerid);
public OnBeanbagShoot(playerid)
{
	return SetPlayerArmedWeapon(playerid, WEAPON_SHOTGUN);
}

Beanbag_OnPlayerGiveDamage(playerid, damagedid, weaponid)
{
    #pragma unused weaponid
    if(GetPlayerState(damagedid) != PLAYER_STATE_ONFOOT)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Player harus berjalan kaki untuk terkena beanbag!");

    if(!IsPlayerNearPlayer(playerid, damagedid, 25.00))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Jarak Pemain tersebut terlalu jauh untuk terkena beanbag!");

    static string[64];

    format(string, sizeof(string), "Anda telah terkena peluru ~r~karet~w~ oleh %s", AccountData[playerid][pName]);

    AccountData[damagedid][pBeanbagTime] = 10;
    TogglePlayerControllable(damagedid, false);

    SetPlayerDrunkLevel(damagedid, GetPlayerDrunkLevel(damagedid)+1000);

    ApplyAnimation(damagedid, "SWEET", "Sweet_injuredloop", 4.1, true, true, true, true, 0, true);
    ShowPlayerFooter(damagedid, string, 10000);
    
    PlayerPlaySound(damagedid, 36400, 0.0, 0.0, 0.0);
    return 1;
}

hook OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
    if(weaponid == 25 && AccountData[playerid][pUseBeanbag] && AccountData[playerid][pFaction] == FACTION_LSPD) 
	{
		PlayerPlayNearbySound(playerid, 19401);

		SetPlayerArmedWeapon(playerid, 0);
		ApplyAnimation(playerid, "BUDDY", "buddy_reload", 4.0, false, false, false, false, 0, true);
		SetTimerEx("OnBeanbaghoot", 1655, false, "i", playerid);

        if (hittype == BULLET_HIT_TYPE_VEHICLE)
		{
			return 0; // stop processing OnPlayerWeaponShot and return 0
			// this completely stops the beanbag from damaging cars
		}
	}
    return 1;
}