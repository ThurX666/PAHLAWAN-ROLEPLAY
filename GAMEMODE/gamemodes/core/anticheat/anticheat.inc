#include "core/anticheat/ddos"
#include "core/anticheat/cbug"

#define MAX_ANTICHEAT_WARNINGS 3

static const Float:modShopLocations[][] =
{
    {10.0,  -1936.0861, 237.4443,   34.3125},
	{10.0,  -2714.6309, 217.3955,   4.2965},
	{10.0,  2386.7686,  1042.1649,  10.8203},
	{10.0,  2644.9480,  -2037.6088, 13.5500},
	{10.0,  1041.2783,  -1027.8124, 32.1016},
	{50.0,  616.0253,   -8.0157,    1000.9219},
	{50.0,  615.2108,   -75.3288,   997.9922},
	{50.0,  612.9303,   -124.1615,  997.9922}
};

IsPlayerNearModShop(playerid)
{
	if(IsPlayerInAnyVehicle(playerid))
	{
		for(new i; i < sizeof(modShopLocations); i ++)
		{
		    if(IsPlayerInRangeOfPoint(playerid, modShopLocations[i][0], modShopLocations[i][1], modShopLocations[i][2], modShopLocations[i][3]))
		    {
		        return 1;
			}
		}
	}
	
	return 0;
}

AC_RangeCheck(Float:x1, Float:y1, Float:z1, Float:radius, Float:x2, Float:y2, Float:z2)
{
	x1 -= x2;
	y1 -= y2;
	z1 -= z2;

	return ((x1 * x1) + (y1 * y1) + (z1 * z1)) < (radius * radius);
}

Float:AC_GetSpeed(playerid)
{
	new
		Float:vx,
		Float:vy,
		Float:vz;

	if(IsPlayerInAnyVehicle(playerid))
	{
		GetVehicleVelocity(GetPlayerVehicleID(playerid), vx, vy, vz);
	}
	else
	{
	    GetPlayerVelocity(playerid, vx, vy, vz);
	}

	return floatsqroot((vx * vx) + (vy * vy) + (vz * vz));
}

enum e_Anticheat
{
    Float:acPos[3],
    Float:acSpawn[3],
    acImmunity,
    acAirbreakTime,
    acArmorTime
};
new Anticheat[MAX_PLAYERS][e_Anticheat];

OnPlayerTeleport(playerid, Float:distance)
{
    if(AccountData[playerid][pAdmin] < 1 || !AccountData[playerid][pSteward])
    {
        if(!IsPlayerInRangeOfPoint(playerid, 4.0, AccountData[playerid][pPos][0], AccountData[playerid][pPos][1], AccountData[playerid][pPos][2]))
        {
            AccountData[playerid][pACWarns]++;

            if(AccountData[playerid][pACWarns] >= MAX_ANTICHEAT_WARNINGS)
            {
                SendStaffMessage(Y_RED, "[AntiCheat] "YELLOW"%s(%i) {DBD7D2}ditendang dari server karena Teleport Hack.", GetName(playerid), playerid);
                SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda ditendang dari server karena Teleport Hack.");
                return KickEx(playerid);
            }

            if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER)
            {
                new vsID = GetVehicleModel(GetPlayerVehicleID(playerid));
                SendStaffMessage(Y_RED, "[AntiCheat] "YELLOW"%s(%i) {DBD7D2}diduga menggunakan Teleport Hack. "YELLOW"[D: %.1f m] [%s]", GetName(playerid), playerid, distance, GetVehicleModelName(vsID));
            }
            else
            {
                SendStaffMessage(Y_RED, "[AntiCheat] "YELLOW"%s(%i) {DBD7D2}diduga menggunakan Teleport Hack. "YELLOW"[D: %.1f m] [F]", GetName(playerid), playerid, distance);
            }
        }
    }
	return 1;
}

OnPlayerAirbreak(playerid)
{
	if(AccountData[playerid][pAdmin] < 1 || !AccountData[playerid][pSteward])
    {
	    AccountData[playerid][pACWarns]++;

	    if(AccountData[playerid][pACWarns] >= MAX_ANTICHEAT_WARNINGS)
	    {
	        SendStaffMessage(Y_RED, "[AntiCheat] "YELLOW"%s(%i) {DBD7D2}ditendang dari server karena Airbreak.", GetName(playerid), playerid);
            SendClientMessage(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda telah ditendang dari server karena Airbreak.");
            return KickEx(playerid);
		}

        SendStaffMessage(Y_RED, "[AntiCheat] "YELLOW"%s(%i) {DBD7D2}diduga menggunakan Airbreak.", GetName(playerid), playerid);
	}
	return 1;
}

ptask CheckingACTeleport[1000](playerid) 
{
    if(GetPlayerState(playerid) != PLAYER_STATE_SPECTATING && GetPlayerState(playerid) != PLAYER_STATE_NONE)
	{
        if(AccountData[playerid][IsLoggedIn])
        {
            if(gettime() > Anticheat[playerid][acImmunity])
            {
                if(!IsPlayerInRangeOfPoint(playerid, 200.0, Anticheat[playerid][acPos][0], Anticheat[playerid][acPos][1], Anticheat[playerid][acPos][2]) && !IsPlayerInRangeOfPoint(playerid, 5.0, Anticheat[playerid][acSpawn][0], Anticheat[playerid][acSpawn][1], Anticheat[playerid][acSpawn][2]))
                {
                    new
                        Float:x,
                        Float:y,
                        Float:z;

                    GetPlayerPos(playerid, x, y, z);

                    if(!AC_RangeCheck(Anticheat[playerid][acPos][0], Anticheat[playerid][acPos][1], Anticheat[playerid][acPos][2], 3.0, Anticheat[playerid][acSpawn][0], Anticheat[playerid][acSpawn][1], Anticheat[playerid][acSpawn][2]) && x != 0.0 && y != 0.0 && z != 0.0 && GetPlayerState(playerid) != PLAYER_STATE_PASSENGER && !IsPlayerNearModShop(playerid))
                    {
                        OnPlayerTeleport(playerid, GetPlayerDistanceFromPoint(playerid, Anticheat[playerid][acPos][0], Anticheat[playerid][acPos][1], Anticheat[playerid][acPos][2]));
                    }
                }
            }
            else if(gettime() > Anticheat[playerid][acAirbreakTime] && !IsPlayerInRangeOfPoint(playerid, 10.0, Anticheat[playerid][acPos][0], Anticheat[playerid][acPos][1], Anticheat[playerid][acPos][2]))
            {
                if((GetPlayerState(playerid) == PLAYER_STATE_ONFOOT || GetPlayerState(playerid) == PLAYER_STATE_DRIVER) && GetPlayerSurfingVehicleID(playerid) == INVALID_VEHICLE_ID && GetPlayerSurfingObjectID(playerid) == INVALID_OBJECT_ID)
                {
                    // Player is 10.0 meters away from their position. Let's check their velocity!

                    new
                        Float:px,
                        Float:py,
                        Float:pz;

                    GetPlayerPos(playerid, px, py, pz);

                    px = floatabs(Anticheat[playerid][acPos][0] - px);
                    py = floatabs(Anticheat[playerid][acPos][1] - py);
                    pz = floatabs(Anticheat[playerid][acPos][2] - pz);

                    // Player seems to have moved a great distance. Let's do more checking.
                    if(((0.5 <= px < 13.9) && (0.5 <= py <= 13.9)) || (4.2 <= pz <= 19.2))
                    {
                        new
                            Float:speed = AC_GetSpeed(playerid);

                        if((0.082 <= speed <= 0.215 && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) || (0.0009 <= speed <= 0.0013 && GetPlayerState(playerid) == PLAYER_STATE_DRIVER))
                        {
                            // When airbreaking in the air, a player's velocity levels tend to stay at a regular speed, as they were moving onfoot.
                            OnPlayerAirbreak(playerid);
                            Anticheat[playerid][acAirbreakTime] = gettime() + 1;
                        }
                    }
                }
            }
            GetPlayerPos(playerid, Anticheat[playerid][acPos][0], Anticheat[playerid][acPos][1], Anticheat[playerid][acPos][2]);
        }
    }
    return 1;
}