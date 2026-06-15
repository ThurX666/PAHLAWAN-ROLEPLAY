#include <YSI_Coding\y_hooks>

forward OnTaserShoot(playerid);
public OnTaserShoot(playerid)
{
	return SetPlayerArmedWeapon(playerid, WEAPON_SILENCED);
}

Tazer_OnPlayerGiveDamage(playerid, damagedid, weaponid)
{
    #pragma unused weaponid
    if(GetPlayerState(damagedid) != PLAYER_STATE_ONFOOT)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Player harus berjalan kaki untuk terkena tased!");

    if(!IsPlayerNearPlayer(playerid, damagedid, 25.00))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Jarak Pemain tersebut terlalu jauh untuk terkena tased!");

    static string[64];

    format(string, sizeof(string), "Anda telah ~r~disetrum~w~ oleh %s", AccountData[playerid][pName]);

    AccountData[damagedid][pTazedTime] = 10;
    TogglePlayerControllable(damagedid, false);

    SetPlayerDrunkLevel(damagedid, GetPlayerDrunkLevel(damagedid)+1000);

    ApplyAnimation(damagedid, "CRACK", "crckdeth4", 4.0, false, false, false, true, 0, true);
    ShowPlayerFooter(damagedid, string, 10000);
    
    PlayerPlaySound(damagedid, 6003, 0.0, 0.0, 0.0);
    return 1;
}

hook OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
    if(weaponid == 23 && AccountData[playerid][pTaser] && (AccountData[playerid][pFaction] == FACTION_LSPD || AccountData[playerid][pFaction] == FACTION_SAGOV)) 
	{
		PlayerPlayNearbySound(playerid, 6402);

		SetPlayerArmedWeapon(playerid, 0);
		ApplyAnimation(playerid, "SILENCED", "Silence_reload", 4.0, false, false, false, false, 0, true);
		SetTimerEx("OnTaserShoot", 1655, false, "i", playerid);

        if (hittype == BULLET_HIT_TYPE_VEHICLE)
		{
			return 0; // stop processing OnPlayerWeaponShot and return 0
			// this completely stops the taser from damaging cars
		}
	}
    return 1;
}