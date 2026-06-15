//Weapon Attach

enum gunEdit
{
    eWeaponID,
    Float:Position[6],
    Bone,
    Hidden,
    WeaponTint
};
new GunEdit[MAX_PLAYERS][5][gunEdit], EditingWeapon[MAX_PLAYERS];

enum
{
    WEAPON_TYPE_NONE,
    WEAPON_TYPE_ADMIN,
    WEAPON_TYPE_FACTION,
    WEAPON_TYPE_PLAYER
};

enum e_gundetails
{
    WeaponID,
    WeaponType,
    WeaponAmmo
};
new GunData[MAX_PLAYERS][13][e_gundetails];

new iWeaponTints[12] = {
    0, //default
	0xFFFF0000, // Merah
	0xFF0000FF, // Biru
	0xFF00FFFF, // Cyan
	0xFF00FF00, // Hijau
	0xFFFFFF00, // Kuning
	0xFFFFD700, // Emas 
	0xFFFFA500, // Orange 
	0xFFffc0cb, // Pink 
	0xFFFf80FF, // Magenta 
	0xFF2C2D2D, // hitam 
	0xFF808080 // abu-abu 
};

GetWeaponIndex(weaponid) //untuk index gunedit
{
    new guneditindex;
 
    switch (weaponid)
    {
        case 2..9: guneditindex = 0; //meele
        case 22..24: guneditindex = 1;	// Handguns
        case 25..29, 32: guneditindex = 2;	// Shotguns & sub-machinegunes
        case 30, 31, 33, 34: guneditindex = 3; //Machineguns & rifles
        case 41, 42: guneditindex = 4; //extras (spraycan dan fire extinguish)
    }
    return guneditindex;
}

GetWeaponObjectSlot(weaponid) //untuk slot setplayerattachobject
{
    new objectslot;
 
    switch (weaponid)
    {
        case 2..9: objectslot = 4; //meele
        case 22..24: objectslot = 5;	// Handguns
        case 25..29, 32: objectslot = 6;	// Shotguns & sub-machinegunes
        case 30, 31, 33, 34: objectslot = 7; //Machineguns & rifles
        case 41, 42: objectslot = 8; //extras (spraycan dan fire extinguish)
    }
    return objectslot;
}
 
GetWeaponModel(weaponid) //Will only return the model of wearable weapons (22-38)
{
    new model;
   
    switch(weaponid)
    {
        case 1: model = 331;
        case 2..8: model = 331 + weaponid;
        case 9: model = 341;
        case 10..15: model = 311 + weaponid;
        case 16: model = 342;
        case 17: model = 343;
        case 18: model = 344;
        case 22..29: model = 324 + weaponid;
        case 30: model = 355;
        case 31: model = 356;
        case 32: model = 372;
        case 33..38: model = 324 + weaponid;
        case 41..42: model = 324 + weaponid;
    }
    return model;
}
 
PlayerHasWeapon(playerid, weaponid)
{
    new weapon, ammo;
 
    for (new i; i < 13; i++)
    {
        GetPlayerWeaponData(playerid, i, weapon, ammo);
        if (weapon == weaponid && ammo) return 1;
    }
    return 0;
}

IsWeaponWearable(weaponid)
{
    if(weaponid >= 2 && weaponid <= 9) return true;
    else if(weaponid >= 22 && weaponid <= 34) return true;
    else if(weaponid == 41 || weaponid == 42) return true;
    else return false;
}

IsWeaponTintable(weaponid)
{
    new bool:tintable = false;
    switch(weaponid)
    {
        case 22: tintable = true;
        case 23: tintable = true;
        case 24: tintable = true;
        case 25: tintable = true;
        case 27: tintable = true;
        case 28: tintable = true;
        case 29: tintable = true;
        case 30: tintable = true;
        case 31: tintable = true;
        case 32: tintable = true;
        case 33: tintable = true;
        case 35: tintable = true;
        case 36: tintable = true;
        case 38: tintable = true;
        default: tintable = false;
    }
    return tintable;
}

IsFirearmWeapon(weaponid)
{
    switch(weaponid)
    {
        case 22..34: 
        {
            return true;
        }
    }
    return false;
}

IsWeaponHideable(weaponid)
    return (weaponid >= 22 && weaponid <= 24 || weaponid == 28 || weaponid == 32);

//Drop Weapon
#define MAX_DROP_WEAPON 5000
enum droppedweapons {
    WeapID,
    WeapPlayer[24],
	WeapModel,
	WeaponID,
	WeapAmmo,
    Float:WeapPos[3],
	WeapInt,
	WeapWorld,
    STREAMER_TAG_OBJECT:WeapObject
};
new DropWeap[MAX_DROP_WEAPON][droppedweapons];

DropWeapon(const player[], model, weaponid = 0, ammo = 0, Float:x, Float:y, Float:z, interior, world)
{
    for (new i = 0; i != MAX_DROP_WEAPON; i ++) if(!DropWeap[i][WeapModel])
    {
        format(DropWeap[i][WeapPlayer], 24, player);

        DropWeap[i][WeapModel] = model;
        DropWeap[i][WeaponID] = weaponid;
        DropWeap[i][WeapAmmo] = ammo;
        DropWeap[i][WeapPos][0] = x;
        DropWeap[i][WeapPos][1] = y;
        DropWeap[i][WeapPos][2] = z;

        DropWeap[i][WeapInt] = interior;
        DropWeap[i][WeapWorld] = world;

        if(DestroyDynamicObject(DropWeap[i][WeapObject]))
            DropWeap[i][WeapObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

        if(IsWeaponModel(model)) 
		{
            DropWeap[i][WeapObject] = CreateDynamicObject(model, x, y, z, 93.7, 120.0, 120.0, world, interior);
        } 
		else 
		{
            DropWeap[i][WeapObject] = CreateDynamicObject(model, x, y, z, 0.0, 0.0, 0.0, world, interior);
        }
        return i;
    }
    return -1;
}

NearWeapon(playerid)
{
    for (new i; i != MAX_DROP_WEAPON; i ++) if(IsValidDynamicObject(DropWeap[i][WeapObject]) && IsPlayerInRangeOfPoint(playerid, 1.5, DropWeap[i][WeapPos][0], DropWeap[i][WeapPos][1], DropWeap[i][WeapPos][2]))
    {
        if(GetPlayerInterior(playerid) == DropWeap[i][WeapInt] && GetPlayerVirtualWorld(playerid) == DropWeap[i][WeapWorld])
        return i;
    }
    return -1;
}

DeleteWeapon(itemid)
{
    if(itemid != -1 && DropWeap[itemid][WeapModel])
    {
        DropWeap[itemid][WeapModel] = 0;
        DropWeap[itemid][WeapPos][0] = 0.0;
        DropWeap[itemid][WeapPos][1] = 0.0;
        DropWeap[itemid][WeapPos][2] = 0.0;
        DropWeap[itemid][WeapInt] = 0;
        DropWeap[itemid][WeapWorld] = 0;

        if(DestroyDynamicObject(DropWeap[itemid][WeapObject]))
            DropWeap[itemid][WeapObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
    }
    return 1;
}

PickupWeapon(playerid, itemid)
{
    if(itemid != -1 && DropWeap[itemid][WeapModel])
    {
        GivePlayerWeaponEx(playerid, DropWeap[itemid][WeaponID], DropWeap[itemid][WeapAmmo], WEAPON_TYPE_PLAYER);
		ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Anda telah mengambil %s.", ReturnWeaponName(DropWeap[itemid][WeaponID])));
        DeleteWeapon(itemid);
    }
    return 1;
}

RemovePlayerWeapons(playerid)
{
    if(GunData[playerid][0][WeaponAmmo] > 500)
        GunData[playerid][0][WeaponAmmo] = 500;
    if(GunData[playerid][1][WeaponAmmo] > 500)
        GunData[playerid][1][WeaponAmmo] = 500;
    if(GunData[playerid][2][WeaponAmmo] > 500)
        GunData[playerid][2][WeaponAmmo] = 500;
    if(GunData[playerid][3][WeaponAmmo] > 500)
        GunData[playerid][3][WeaponAmmo] = 500;
    if(GunData[playerid][4][WeaponAmmo] > 500)
        GunData[playerid][4][WeaponAmmo] = 500;
    if(GunData[playerid][5][WeaponAmmo] > 500)
        GunData[playerid][5][WeaponAmmo] = 500;
    if(GunData[playerid][6][WeaponAmmo] > 500)
        GunData[playerid][6][WeaponAmmo] = 500;
    if(GunData[playerid][7][WeaponAmmo] > 500)
        GunData[playerid][7][WeaponAmmo] = 500;
    if(GunData[playerid][8][WeaponAmmo] > 500)
        GunData[playerid][8][WeaponAmmo] = 500;
    if(GunData[playerid][9][WeaponAmmo] > 500)
        GunData[playerid][9][WeaponAmmo] = 500;
    if(GunData[playerid][10][WeaponAmmo] > 500)
        GunData[playerid][10][WeaponAmmo] = 500;
    if(GunData[playerid][11][WeaponAmmo] > 500)
        GunData[playerid][11][WeaponAmmo] = 500;
    if(GunData[playerid][12][WeaponAmmo] > 500)
        GunData[playerid][12][WeaponAmmo] = 500;

    static string[580];
    mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_weapons` SET `Type1`= %d, `Type2`= %d, `Type3`= %d, `Type4`= %d, `Type5`= %d, `Type6`= %d, `Type7`= %d, `Type8`= %d, `Type9`= %d, `Type10`= %d, `Type11`= %d, `Type12`= %d, `Type13`= %d, \
    `Gun1`= %d, `Gun2`= %d, `Gun3`= %d, `Gun4`= %d, `Gun5`= %d, `Gun6`= %d, `Gun7`= %d, `Gun8`= %d, `Gun9`= %d, `Gun10`= %d, `Gun11`= %d, `Gun12`= %d, `Gun13`= %d, `Ammo1`= %d, `Ammo2`= %d, `Ammo3`= %d, `Ammo4`= %d, `Ammo5`= %d, `Ammo6`= %d, \
    `Ammo7`= %d, `Ammo8`= %d, `Ammo9`= %d, `Ammo10`= %d, `Ammo11`= %d, `Ammo12`= %d, `Ammo13`= %d WHERE `Owner_ID` = %d", GunData[playerid][0][WeaponType],
    GunData[playerid][1][WeaponType],
    GunData[playerid][2][WeaponType],
    GunData[playerid][3][WeaponType],
    GunData[playerid][4][WeaponType],
    GunData[playerid][5][WeaponType],
    GunData[playerid][6][WeaponType],
    GunData[playerid][7][WeaponType],
    GunData[playerid][8][WeaponType],
    GunData[playerid][9][WeaponType],
    GunData[playerid][10][WeaponType],
    GunData[playerid][11][WeaponType],
    GunData[playerid][12][WeaponType],
    GunData[playerid][0][WeaponID],
    GunData[playerid][1][WeaponID],
    GunData[playerid][2][WeaponID],
    GunData[playerid][3][WeaponID],
    GunData[playerid][4][WeaponID],
    GunData[playerid][5][WeaponID],
    GunData[playerid][6][WeaponID],
    GunData[playerid][7][WeaponID],
    GunData[playerid][8][WeaponID],
    GunData[playerid][9][WeaponID],
    GunData[playerid][10][WeaponID],
    GunData[playerid][11][WeaponID],
    GunData[playerid][12][WeaponID],
    GunData[playerid][0][WeaponAmmo],
    GunData[playerid][1][WeaponAmmo],
    GunData[playerid][2][WeaponAmmo],
    GunData[playerid][3][WeaponAmmo],
    GunData[playerid][4][WeaponAmmo],
    GunData[playerid][5][WeaponAmmo],
    GunData[playerid][6][WeaponAmmo],
    GunData[playerid][7][WeaponAmmo],
    GunData[playerid][8][WeaponAmmo],
    GunData[playerid][9][WeaponAmmo],
    GunData[playerid][10][WeaponAmmo],
    GunData[playerid][11][WeaponAmmo],
    GunData[playerid][12][WeaponAmmo],
    AccountData[playerid][pID]);
    mysql_pquery(g_SQL, string);
}

SetPlayerWeaponTint(playerid, iWepID, index) 
{
    RemovePlayerAttachedObject(playerid, GetWeaponObjectSlot(iWepID));

	switch(iWepID)
    {
		case 22: SetPlayerAttachedObject(playerid, GetWeaponObjectSlot(iWepID), 346, 6, -0.004999, -0.003999, -0.006000, 0.000000, 0.000000, -1.800000, 1.007000, 1.337999, 1.069000, iWeaponTints[GunEdit[playerid][index][WeaponTint]], iWeaponTints[GunEdit[playerid][index][WeaponTint]]);
		case 23: SetPlayerAttachedObject(playerid, GetWeaponObjectSlot(iWepID), 347, 6, -0.003999, -0.001999, -0.003999, 0.000000, 0.299999, -0.999999, 1.000000, 1.188000, 1.063000, iWeaponTints[GunEdit[playerid][index][WeaponTint]], iWeaponTints[GunEdit[playerid][index][WeaponTint]]);
		case 24: SetPlayerAttachedObject(playerid, GetWeaponObjectSlot(iWepID), 348, 6, -0.006999, -0.004000, 0.002000, -1.600000, -0.200000, 0.400000, 1.019999, 1.146999, 1.027000, iWeaponTints[GunEdit[playerid][index][WeaponTint]], iWeaponTints[GunEdit[playerid][index][WeaponTint]]);
		case 25: SetPlayerAttachedObject(playerid, GetWeaponObjectSlot(iWepID), 349, 6, 0.000000, -0.008999, -0.004000, 0.000000, 1.099999, 1.499999, 1.000000, 1.222000, 1.088000, iWeaponTints[GunEdit[playerid][index][WeaponTint]], iWeaponTints[GunEdit[playerid][index][WeaponTint]]);
		case 27: SetPlayerAttachedObject(playerid, GetWeaponObjectSlot(iWepID), 351, 6, 0.003000, -0.014000, -0.003000, 0.000000, 0.000000, 2.199999, 1.000000, 1.371000, 1.023000, iWeaponTints[GunEdit[playerid][index][WeaponTint]], iWeaponTints[GunEdit[playerid][index][WeaponTint]]);
		case 28: SetPlayerAttachedObject(playerid, GetWeaponObjectSlot(iWepID), 352, 6, -0.002000, -0.008000, -0.001999, -0.300000, 0.000000, 1.199999, 1.019999, 1.245000, 1.043000, iWeaponTints[GunEdit[playerid][index][WeaponTint]], iWeaponTints[GunEdit[playerid][index][WeaponTint]]);
		case 29: SetPlayerAttachedObject(playerid, GetWeaponObjectSlot(iWepID), 353, 6, 0.000000, -0.009000, -0.009000, 0.000000, 0.099999, 2.100000, 1.000000, 1.290001, 1.053000, iWeaponTints[GunEdit[playerid][index][WeaponTint]], iWeaponTints[GunEdit[playerid][index][WeaponTint]]);
		case 30: SetPlayerAttachedObject(playerid, GetWeaponObjectSlot(iWepID), 355, 6, 0.000000, -0.011000, 0.000000, 0.000000, 0.000000, 2.100000, 1.009000, 1.424000, 1.013000, iWeaponTints[GunEdit[playerid][index][WeaponTint]], iWeaponTints[GunEdit[playerid][index][WeaponTint]]);
		case 31: SetPlayerAttachedObject(playerid, GetWeaponObjectSlot(iWepID), 356, 6, -0.002000, -0.005999, 0.001000, 0.000000, 0.899999, 1.699999, 0.997999, 1.318999, 1.088001, iWeaponTints[GunEdit[playerid][index][WeaponTint]], iWeaponTints[GunEdit[playerid][index][WeaponTint]]);
		case 32: SetPlayerAttachedObject(playerid, GetWeaponObjectSlot(iWepID), 372, 6, -0.003000, -0.009000, -0.001999, 0.000000, 0.400000, 0.800000, 1.015000, 1.232000, 1.055000, iWeaponTints[GunEdit[playerid][index][WeaponTint]], iWeaponTints[GunEdit[playerid][index][WeaponTint]]);
		case 33: SetPlayerAttachedObject(playerid, GetWeaponObjectSlot(iWepID), 357, 6, 0.000000, -0.015000, -0.001999, 0.000000, 1.200000, 2.199999, 1.000000, 1.286001, 1.096001, iWeaponTints[GunEdit[playerid][index][WeaponTint]], iWeaponTints[GunEdit[playerid][index][WeaponTint]]);
		case 35: SetPlayerAttachedObject(playerid, GetWeaponObjectSlot(iWepID), 359, 6, 0.001999, -0.007000, -0.009000, 0.000000, -0.100000, 0.000000, 0.989999, 1.213001, 1.084001, iWeaponTints[GunEdit[playerid][index][WeaponTint]], iWeaponTints[GunEdit[playerid][index][WeaponTint]]);
		case 36: SetPlayerAttachedObject(playerid, GetWeaponObjectSlot(iWepID), 360, 6, 0.001000, -0.004999, -0.008000, 0.000000, 0.000000, 0.000000, 1.000000, 1.140000, 1.055000, iWeaponTints[GunEdit[playerid][index][WeaponTint]], iWeaponTints[GunEdit[playerid][index][WeaponTint]]);
		case 38: SetPlayerAttachedObject(playerid, GetWeaponObjectSlot(iWepID), 362, 6, -0.041000, 0.001999, 0.012000, 0.000000, 0.999999, -0.599999, 1.085000, 1.189999, 1.134000, iWeaponTints[GunEdit[playerid][index][WeaponTint]], iWeaponTints[GunEdit[playerid][index][WeaponTint]]);
		default: return 1;
	}
	return 1;
}

forward LoadPlayerWeapons(playerid);
public LoadPlayerWeapons(playerid)
{
    if (cache_num_rows() > 0)
	{
        cache_get_value_name_int(0, "Type1", GunData[playerid][0][WeaponType]);
        cache_get_value_name_int(0, "Type2", GunData[playerid][1][WeaponType]);
        cache_get_value_name_int(0, "Type3", GunData[playerid][2][WeaponType]);
        cache_get_value_name_int(0, "Type4", GunData[playerid][3][WeaponType]);
        cache_get_value_name_int(0, "Type5", GunData[playerid][4][WeaponType]);
        cache_get_value_name_int(0, "Type6", GunData[playerid][5][WeaponType]);
        cache_get_value_name_int(0, "Type7", GunData[playerid][6][WeaponType]);
        cache_get_value_name_int(0, "Type8", GunData[playerid][7][WeaponType]);
        cache_get_value_name_int(0, "Type9", GunData[playerid][8][WeaponType]);
        cache_get_value_name_int(0, "Type10", GunData[playerid][9][WeaponType]);
        cache_get_value_name_int(0, "Type11", GunData[playerid][10][WeaponType]);
        cache_get_value_name_int(0, "Type12", GunData[playerid][11][WeaponType]);
        cache_get_value_name_int(0, "Type13", GunData[playerid][12][WeaponType]);

        cache_get_value_name_int(0, "Gun1", GunData[playerid][0][WeaponID]);
        cache_get_value_name_int(0, "Gun2", GunData[playerid][1][WeaponID]);
        cache_get_value_name_int(0, "Gun3", GunData[playerid][2][WeaponID]);
        cache_get_value_name_int(0, "Gun4", GunData[playerid][3][WeaponID]);
        cache_get_value_name_int(0, "Gun5", GunData[playerid][4][WeaponID]);
        cache_get_value_name_int(0, "Gun6", GunData[playerid][5][WeaponID]);
        cache_get_value_name_int(0, "Gun7", GunData[playerid][6][WeaponID]);
        cache_get_value_name_int(0, "Gun8", GunData[playerid][7][WeaponID]);
        cache_get_value_name_int(0, "Gun9", GunData[playerid][8][WeaponID]);
        cache_get_value_name_int(0, "Gun10", GunData[playerid][9][WeaponID]);
        cache_get_value_name_int(0, "Gun11", GunData[playerid][10][WeaponID]);
        cache_get_value_name_int(0, "Gun12", GunData[playerid][11][WeaponID]);
        cache_get_value_name_int(0, "Gun13", GunData[playerid][12][WeaponID]);
        
        cache_get_value_name_int(0, "Ammo1", GunData[playerid][0][WeaponAmmo]);
        cache_get_value_name_int(0, "Ammo2", GunData[playerid][1][WeaponAmmo]);
        cache_get_value_name_int(0, "Ammo3", GunData[playerid][2][WeaponAmmo]);
        cache_get_value_name_int(0, "Ammo4", GunData[playerid][3][WeaponAmmo]);
        cache_get_value_name_int(0, "Ammo5", GunData[playerid][4][WeaponAmmo]);
        cache_get_value_name_int(0, "Ammo6", GunData[playerid][5][WeaponAmmo]);
        cache_get_value_name_int(0, "Ammo7", GunData[playerid][6][WeaponAmmo]);
        cache_get_value_name_int(0, "Ammo8", GunData[playerid][7][WeaponAmmo]);
        cache_get_value_name_int(0, "Ammo9", GunData[playerid][8][WeaponAmmo]);
        cache_get_value_name_int(0, "Ammo10", GunData[playerid][9][WeaponAmmo]);
        cache_get_value_name_int(0, "Ammo11", GunData[playerid][10][WeaponAmmo]);
        cache_get_value_name_int(0, "Ammo12", GunData[playerid][11][WeaponAmmo]);
        cache_get_value_name_int(0, "Ammo13", GunData[playerid][12][WeaponAmmo]);
		printf("[Player Weapons] Total number of weapons loaded for %s [DBID: %d]: %d.", AccountData[playerid][pUCP], AccountData[playerid][pID], cache_num_rows());
	}
    else
    {
        GunData[playerid][0][WeaponType] = WEAPON_TYPE_NONE;
        GunData[playerid][1][WeaponType] = WEAPON_TYPE_NONE;
        GunData[playerid][2][WeaponType] = WEAPON_TYPE_NONE;
        GunData[playerid][3][WeaponType] = WEAPON_TYPE_NONE;
        GunData[playerid][4][WeaponType] = WEAPON_TYPE_NONE;
        GunData[playerid][5][WeaponType] = WEAPON_TYPE_NONE;
        GunData[playerid][6][WeaponType] = WEAPON_TYPE_NONE;
        GunData[playerid][7][WeaponType] = WEAPON_TYPE_NONE;
        GunData[playerid][8][WeaponType] = WEAPON_TYPE_NONE;
        GunData[playerid][9][WeaponType] = WEAPON_TYPE_NONE;
        GunData[playerid][10][WeaponType] = WEAPON_TYPE_NONE;
        GunData[playerid][11][WeaponType] = WEAPON_TYPE_NONE;
        GunData[playerid][12][WeaponType] = WEAPON_TYPE_NONE;

        GunData[playerid][0][WeaponID] = 0;
        GunData[playerid][1][WeaponID] = 0;
        GunData[playerid][2][WeaponID] = 0;
        GunData[playerid][3][WeaponID] = 0;
        GunData[playerid][4][WeaponID] = 0;
        GunData[playerid][5][WeaponID] = 0;
        GunData[playerid][6][WeaponID] = 0;
        GunData[playerid][7][WeaponID] = 0;
        GunData[playerid][8][WeaponID] = 0;
        GunData[playerid][9][WeaponID] = 0;
        GunData[playerid][10][WeaponID] = 0;
        GunData[playerid][11][WeaponID] = 0;
        GunData[playerid][12][WeaponID] = 0;

        GunData[playerid][0][WeaponAmmo] = 0;
        GunData[playerid][1][WeaponAmmo] = 0;
        GunData[playerid][2][WeaponAmmo] = 0;
        GunData[playerid][3][WeaponAmmo] = 0;
        GunData[playerid][4][WeaponAmmo] = 0;
        GunData[playerid][5][WeaponAmmo] = 0;
        GunData[playerid][6][WeaponAmmo] = 0;
        GunData[playerid][7][WeaponAmmo] = 0;
        GunData[playerid][8][WeaponAmmo] = 0;
        GunData[playerid][9][WeaponAmmo] = 0;
        GunData[playerid][10][WeaponAmmo] = 0;
        GunData[playerid][11][WeaponAmmo] = 0;
        GunData[playerid][12][WeaponAmmo] = 0;

        static string[580];
		mysql_format(g_SQL, string, sizeof(string), "INSERT IGNORE INTO `player_weapons` SET `Owner_ID` = %d, `Type1`=0, `Type2`=0, `Type3`=0, `Type4`=0, `Type5`=0, `Type6`=0, `Type7`=0, `Type8`=0, `Type9`=0, `Type10`=0, `Type11`=0, `Type12`=0, `Type13`=0, \
        `Gun1`=0, `Gun2`=0, `Gun3`=0, `Gun4`=0, `Gun5`=0, `Gun6`=0, `Gun7`=0, `Gun8`=0, `Gun9`=0, `Gun10`=0, `Gun11`=0, `Gun12`=0, `Gun13`=0, `Ammo1`=0, `Ammo2`=0, `Ammo3`=0, `Ammo4`=0, `Ammo5`=0, `Ammo6`=0, \
        `Ammo7`=0, `Ammo8`=0, `Ammo9`=0, `Ammo10`=0, `Ammo11`=0, `Ammo12`=0, `Ammo13`=0", AccountData[playerid][pID]);
        mysql_pquery(g_SQL, string);
    }
    return 1;
}


//Weapon Attach System
forward OnWeaponsLoaded(playerid);
public OnWeaponsLoaded(playerid)
{
    if(cache_num_rows() > 0)
    {
        cache_get_value_name_float(0, "PosX_0", GunEdit[playerid][0][Position][0]);
        cache_get_value_name_float(0, "PosY_0", GunEdit[playerid][0][Position][1]);
        cache_get_value_name_float(0, "PosZ_0", GunEdit[playerid][0][Position][2]);
        cache_get_value_name_float(0, "RotX_0", GunEdit[playerid][0][Position][3]);
        cache_get_value_name_float(0, "RotY_0", GunEdit[playerid][0][Position][4]);
        cache_get_value_name_float(0, "RotZ_0", GunEdit[playerid][0][Position][5]);
        cache_get_value_name_int(0, "Bone_0", GunEdit[playerid][0][Bone]);
        cache_get_value_name_int(0, "Hidden_0", GunEdit[playerid][0][Hidden]);
        cache_get_value_name_int(0, "Tint_0", GunEdit[playerid][0][WeaponTint]);
        
        cache_get_value_name_float(0, "PosX_1", GunEdit[playerid][1][Position][0]);
        cache_get_value_name_float(0, "PosY_1", GunEdit[playerid][1][Position][1]);
        cache_get_value_name_float(0, "PosZ_1", GunEdit[playerid][1][Position][2]);
        cache_get_value_name_float(0, "RotX_1", GunEdit[playerid][1][Position][3]);
        cache_get_value_name_float(0, "RotY_1", GunEdit[playerid][1][Position][4]);
        cache_get_value_name_float(0, "RotZ_1", GunEdit[playerid][1][Position][5]);
        cache_get_value_name_int(0, "Bone_1", GunEdit[playerid][1][Bone]);
        cache_get_value_name_int(0, "Hidden_1", GunEdit[playerid][1][Hidden]);
        cache_get_value_name_int(0, "Tint_1", GunEdit[playerid][1][WeaponTint]);

        cache_get_value_name_float(0, "PosX_2", GunEdit[playerid][2][Position][0]);
        cache_get_value_name_float(0, "PosY_2", GunEdit[playerid][2][Position][1]);
        cache_get_value_name_float(0, "PosZ_2", GunEdit[playerid][2][Position][2]);
        cache_get_value_name_float(0, "RotX_2", GunEdit[playerid][2][Position][3]);
        cache_get_value_name_float(0, "RotY_2", GunEdit[playerid][2][Position][4]);
        cache_get_value_name_float(0, "RotZ_2", GunEdit[playerid][2][Position][5]);
        cache_get_value_name_int(0, "Bone_2", GunEdit[playerid][2][Bone]);
        cache_get_value_name_int(0, "Hidden_2", GunEdit[playerid][2][Hidden]);
        cache_get_value_name_int(0, "Tint_2", GunEdit[playerid][2][WeaponTint]);
        
        cache_get_value_name_float(0, "PosX_3", GunEdit[playerid][3][Position][0]);
        cache_get_value_name_float(0, "PosY_3", GunEdit[playerid][3][Position][1]);
        cache_get_value_name_float(0, "PosZ_3", GunEdit[playerid][3][Position][2]);
        cache_get_value_name_float(0, "RotX_3", GunEdit[playerid][3][Position][3]);
        cache_get_value_name_float(0, "RotY_3", GunEdit[playerid][3][Position][4]);
        cache_get_value_name_float(0, "RotZ_3", GunEdit[playerid][3][Position][5]);
        cache_get_value_name_int(0, "Bone_3", GunEdit[playerid][3][Bone]);
        cache_get_value_name_int(0, "Hidden_3", GunEdit[playerid][3][Hidden]);
        cache_get_value_name_int(0, "Tint_3", GunEdit[playerid][3][WeaponTint]);

        cache_get_value_name_float(0, "PosX_4", GunEdit[playerid][4][Position][0]);
        cache_get_value_name_float(0, "PosY_4", GunEdit[playerid][4][Position][1]);
        cache_get_value_name_float(0, "PosZ_4", GunEdit[playerid][4][Position][2]);
        cache_get_value_name_float(0, "RotX_4", GunEdit[playerid][4][Position][3]);
        cache_get_value_name_float(0, "RotY_4", GunEdit[playerid][4][Position][4]);
        cache_get_value_name_float(0, "RotZ_4", GunEdit[playerid][4][Position][5]);
        cache_get_value_name_int(0, "Bone_4", GunEdit[playerid][4][Bone]);
        cache_get_value_name_int(0, "Hidden_4", GunEdit[playerid][4][Hidden]);
        cache_get_value_name_int(0, "Tint_4", GunEdit[playerid][4][WeaponTint]);
        return 1;
    }
    else
    {
        //meelee
		GunEdit[playerid][0][Position][0] = -0.006999;
		GunEdit[playerid][0][Position][1] = 0.081999;
		GunEdit[playerid][0][Position][2] = -0.057999;
		GunEdit[playerid][0][Position][3] = -69.699958;
		GunEdit[playerid][0][Position][4] = 89.900093;
		GunEdit[playerid][0][Position][5] = 1.999999;
		GunEdit[playerid][0][Bone] = 7;
		GunEdit[playerid][0][Hidden] = false;
		GunEdit[playerid][0][WeaponTint] = 0;

		//handgun
		GunEdit[playerid][1][Position][0] = 0.000000;
		GunEdit[playerid][1][Position][1] = -0.036000;
		GunEdit[playerid][1][Position][2] = 0.124999;
		GunEdit[playerid][1][Position][3] = -90.799949;
		GunEdit[playerid][1][Position][4] = 1.399999;
		GunEdit[playerid][1][Position][5] = 3.700002;
		GunEdit[playerid][1][Bone] = 8;
		GunEdit[playerid][1][Hidden] = false;
		GunEdit[playerid][1][WeaponTint] = 0;

		//shotgun & submachine gun
		GunEdit[playerid][2][Position][0] = 0.186;
		GunEdit[playerid][2][Position][1] = -0.163;
		GunEdit[playerid][2][Position][2] = 0.163;
		GunEdit[playerid][2][Position][3] = -4.1;
		GunEdit[playerid][2][Position][4] = 158.3;
		GunEdit[playerid][2][Position][5] = 10.9;
		GunEdit[playerid][2][Bone] = 1;
		GunEdit[playerid][2][Hidden] = false;
		GunEdit[playerid][2][WeaponTint] = 0;

		//machineguns & rifles
		GunEdit[playerid][3][Position][0] = -0.187;
		GunEdit[playerid][3][Position][1] = 0.178;
		GunEdit[playerid][3][Position][2] = 0.092;
		GunEdit[playerid][3][Position][3] = -4.1;
		GunEdit[playerid][3][Position][4] = 42.7;
		GunEdit[playerid][3][Position][5] = -1;
		GunEdit[playerid][3][Bone] = 1;
		GunEdit[playerid][3][Hidden] = false;
		GunEdit[playerid][3][WeaponTint] = 0;

		//extras
		GunEdit[playerid][4][Position][0] = -0.062999;
		GunEdit[playerid][4][Position][1] = -0.052000;
		GunEdit[playerid][4][Position][2] = 0.047000;
		GunEdit[playerid][4][Position][3] = 119.499946;
		GunEdit[playerid][4][Position][4] = -113.499954;
		GunEdit[playerid][4][Position][5] = -28.999856;
		GunEdit[playerid][4][Bone] = 8;
		GunEdit[playerid][4][Hidden] = false;
		GunEdit[playerid][4][WeaponTint] = 0;

        static string[1254];
        mysql_format(g_SQL, string, sizeof(string), "INSERT IGNORE INTO `gunpos` (`Owner`, `PosX_0`, `PosY_0`, `PosZ_0`, `RotX_0`, `RotY_0`, `RotZ_0`, `Bone_0`, `Hidden_0`, `Tint_0`, `PosX_1`, `PosY_1`, `PosZ_1`, `RotX_1`, `RotY_1`, `RotZ_1`, `Bone_1`, `Hidden_1`, `Tint_1`, \
        `PosX_2`, `PosY_2`, `PosZ_2`, `RotX_2`, `RotY_2`, `RotZ_2`, `Bone_2`, `Hidden_2`, `Tint_2`, `PosX_3`, `PosY_3`, `PosZ_3`, `RotX_3`, `RotY_3`, `RotZ_3`, `Bone_3`, `Hidden_3`, `Tint_3`, \
        `PosX_4`, `PosY_4`, `PosZ_4`, `RotX_4`, `RotY_4`, `RotZ_4`, `Bone_4`, `Hidden_4`, `Tint_4`) VALUES (%d, '%.3f', '%.3f', '%.3f', '%.3f', '%.3f', '%.3f', %d, %d, %d, '%.3f', '%.3f', '%.3f', '%.3f', '%.3f', '%.3f', %d, %d, %d, '%.3f', '%.3f', '%.3f', '%.3f', '%.3f', '%.3f', %d, %d, %d, '%.3f', '%.3f', '%.3f', '%.3f', '%.3f', '%.3f', %d, %d, %d, '%.3f', '%.3f', '%.3f', '%.3f', '%.3f', '%.3f', %d, %d, %d)", AccountData[playerid][pID], GunEdit[playerid][0][Position][0], GunEdit[playerid][0][Position][1], GunEdit[playerid][0][Position][2], GunEdit[playerid][0][Position][3], GunEdit[playerid][0][Position][4], GunEdit[playerid][0][Position][5], GunEdit[playerid][0][Bone], GunEdit[playerid][0][Hidden], GunEdit[playerid][0][WeaponTint],
        GunEdit[playerid][1][Position][0], GunEdit[playerid][1][Position][1], GunEdit[playerid][1][Position][2], GunEdit[playerid][1][Position][3], GunEdit[playerid][1][Position][4], GunEdit[playerid][1][Position][5], GunEdit[playerid][1][Bone], GunEdit[playerid][1][Hidden], GunEdit[playerid][1][WeaponTint],
        GunEdit[playerid][2][Position][0], GunEdit[playerid][2][Position][1], GunEdit[playerid][2][Position][2], GunEdit[playerid][2][Position][3], GunEdit[playerid][2][Position][4], GunEdit[playerid][2][Position][5], GunEdit[playerid][2][Bone], GunEdit[playerid][2][Hidden], GunEdit[playerid][2][WeaponTint],
        GunEdit[playerid][3][Position][0], GunEdit[playerid][3][Position][1], GunEdit[playerid][3][Position][2], GunEdit[playerid][3][Position][3], GunEdit[playerid][3][Position][4], GunEdit[playerid][3][Position][5], GunEdit[playerid][3][Bone], GunEdit[playerid][3][Hidden], GunEdit[playerid][3][WeaponTint],
        GunEdit[playerid][4][Position][0], GunEdit[playerid][4][Position][1], GunEdit[playerid][4][Position][2], GunEdit[playerid][4][Position][3], GunEdit[playerid][4][Position][4], GunEdit[playerid][4][Position][5], GunEdit[playerid][4][Bone], GunEdit[playerid][4][Hidden], GunEdit[playerid][4][WeaponTint]);
        mysql_pquery(g_SQL, string);
    }
    return 1;
}

//Weapon Attach System
YCMD:weapon(playerid, params[], help)
{
    if(AccountData[playerid][pInEvent]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukan ini di dalam event!");
    
    new name[20], give[128];
    if(sscanf(params, "s[20]S()[128]", name, give))
    {
        SUM(playerid, "/gun [nama opsi]~n~give, drop, pickup, pos, resetpos, bone, hide~n~tint");
        return 1;
    }

    new wpid[MAX_PLAYERS];
    wpid[playerid] = GetPlayerWeaponEx(playerid);

    if(!strcmp(name, "pos", true))
    {
        if(wpid[playerid] < 1 || wpid[playerid] > 45) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang memegang senjata/invalid weapon ID!");
    
        if(wpid[playerid] != 40)
        {
            if(GunData[playerid][g_aWeaponSlots[wpid[playerid]]][WeaponType] == WEAPON_TYPE_NONE)
            {
                SendClientMessageEx(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda ditendang dari server karena diduga Weapon Hack. "YELLOW"[%s]", ReturnWeaponName(wpid[playerid]));
                SetWeapons(playerid); //Reload old weapons
                return KickEx(playerid);
            }
        }

        if (!IsWeaponWearable(wpid[playerid]))
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Senjata ini tidak dapat diedit!");
        
        if (EditingWeapon[playerid])
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang mengedit senjata!");

        new index = GetWeaponIndex(wpid[playerid]);

        if (GunEdit[playerid][index][Hidden])
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak bisa edit senjata yang disembunyikan!");

        SetPlayerArmedWeapon(playerid, 0);
    
        SetPlayerAttachedObject(playerid, GetWeaponObjectSlot(wpid[playerid]), GetWeaponModel(wpid[playerid]), GunEdit[playerid][index][Bone], GunEdit[playerid][index][Position][0], GunEdit[playerid][index][Position][1], GunEdit[playerid][index][Position][2], GunEdit[playerid][index][Position][3], GunEdit[playerid][index][Position][4], GunEdit[playerid][index][Position][5], 1.0, 1.0, 1.0);
        EditAttachedObject(playerid, GetWeaponObjectSlot(wpid[playerid]));
    
        EditingWeapon[playerid] = wpid[playerid];
    }
    else if(!strcmp(name, "resetpos", true))
    {
        if(EditingWeapon[playerid])
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang mengedit senjata!");

        //meelee
		GunEdit[playerid][0][Position][0] = -0.006999;
		GunEdit[playerid][0][Position][1] = 0.081999;
		GunEdit[playerid][0][Position][2] = -0.057999;
		GunEdit[playerid][0][Position][3] = -69.699958;
		GunEdit[playerid][0][Position][4] = 89.900093;
		GunEdit[playerid][0][Position][5] = 1.999999;
		GunEdit[playerid][0][Bone] = 7;
		GunEdit[playerid][0][Hidden] = false;
		GunEdit[playerid][0][WeaponTint] = 0;

		//handgun
		GunEdit[playerid][1][Position][0] = 0.000000;
		GunEdit[playerid][1][Position][1] = -0.036000;
		GunEdit[playerid][1][Position][2] = 0.124999;
		GunEdit[playerid][1][Position][3] = -90.799949;
		GunEdit[playerid][1][Position][4] = 1.399999;
		GunEdit[playerid][1][Position][5] = 3.700002;
		GunEdit[playerid][1][Bone] = 8;
		GunEdit[playerid][1][Hidden] = false;
		GunEdit[playerid][1][WeaponTint] = 0;

		//shotgun & submachine gun
		GunEdit[playerid][2][Position][0] = 0.186;
		GunEdit[playerid][2][Position][1] = -0.163;
		GunEdit[playerid][2][Position][2] = 0.163;
		GunEdit[playerid][2][Position][3] = -4.1;
		GunEdit[playerid][2][Position][4] = 158.3;
		GunEdit[playerid][2][Position][5] = 10.9;
		GunEdit[playerid][2][Bone] = 1;
		GunEdit[playerid][2][Hidden] = false;
		GunEdit[playerid][2][WeaponTint] = 0;

		//machineguns & rifles
		GunEdit[playerid][3][Position][0] = -0.187;
		GunEdit[playerid][3][Position][1] = 0.178;
		GunEdit[playerid][3][Position][2] = 0.092;
		GunEdit[playerid][3][Position][3] = -4.1;
		GunEdit[playerid][3][Position][4] = 42.7;
		GunEdit[playerid][3][Position][5] = -1;
		GunEdit[playerid][3][Bone] = 1;
		GunEdit[playerid][3][Hidden] = false;
		GunEdit[playerid][3][WeaponTint] = 0;

		//extras
		GunEdit[playerid][4][Position][0] = -0.062999;
		GunEdit[playerid][4][Position][1] = -0.052000;
		GunEdit[playerid][4][Position][2] = 0.047000;
		GunEdit[playerid][4][Position][3] = 119.499946;
		GunEdit[playerid][4][Position][4] = -113.499954;
		GunEdit[playerid][4][Position][5] = -28.999856;
		GunEdit[playerid][4][Bone] = 8;
		GunEdit[playerid][4][Hidden] = false;
		GunEdit[playerid][4][WeaponTint] = 0;

        static string[1254];
        mysql_format(g_SQL, string, sizeof(string), "UPDATE `gunpos` SET `PosX_0` = '%.3f', `PosY_0` = '%.3f', `PosZ_0` = '%.3f', `RotX_0` = '%.3f', `RotY_0` = '%.3f', `RotZ_0` = '%.3f', `Bone_0` = %d, `Hidden_0` = %d, `Tint_0` = %d, `PosX_1` = '%.3f', `PosY_1` = '%.3f', `PosZ_1` = '%.3f', `RotX_1` = '%.3f', `RotY_1` = '%.3f', `RotZ_1` = '%.3f', `Bone_1` = %d, `Hidden_1` = %d, `Tint_1` = %d, \
        `PosX_2` = '%.3f', `PosY_2` = '%.3f', `PosZ_2` = '%.3f', `RotX_2` = '%.3f', `RotY_2` = '%.3f', `RotZ_2` = '%.3f', `Bone_2` = %d, `Hidden_2` = %d, `Tint_2` = %d, `PosX_3` = '%.3f', `PosY_3` = '%.3f', `PosZ_3` = '%.3f', `RotX_3` = '%.3f', `RotY_3` = '%.3f', `RotZ_3` = '%.3f', `Bone_3` = %d, `Hidden_3` = %d, `Tint_3` = %d, \
        `PosX_4` = '%.3f', `PosY_4` = '%.3f', `PosZ_4` = '%.3f', `RotX_4` = '%.3f', `RotY_4` = '%.3f', `RotZ_4` = '%.3f', `Bone_4` = %d, `Hidden_4` = %d, `Tint_4` = %d WHERE `Owner` = %d", GunEdit[playerid][0][Position][0], GunEdit[playerid][0][Position][1], GunEdit[playerid][0][Position][2], GunEdit[playerid][0][Position][3], GunEdit[playerid][0][Position][4], GunEdit[playerid][0][Position][5], GunEdit[playerid][0][Bone], GunEdit[playerid][0][Hidden], GunEdit[playerid][0][WeaponTint],
        GunEdit[playerid][1][Position][0], GunEdit[playerid][1][Position][1], GunEdit[playerid][1][Position][2], GunEdit[playerid][1][Position][3], GunEdit[playerid][1][Position][4], GunEdit[playerid][1][Position][5], GunEdit[playerid][1][Bone], GunEdit[playerid][1][Hidden], GunEdit[playerid][1][WeaponTint],
        GunEdit[playerid][2][Position][0], GunEdit[playerid][2][Position][1], GunEdit[playerid][2][Position][2], GunEdit[playerid][2][Position][3], GunEdit[playerid][2][Position][4], GunEdit[playerid][2][Position][5], GunEdit[playerid][2][Bone], GunEdit[playerid][2][Hidden], GunEdit[playerid][2][WeaponTint],
        GunEdit[playerid][3][Position][0], GunEdit[playerid][3][Position][1], GunEdit[playerid][3][Position][2], GunEdit[playerid][3][Position][3], GunEdit[playerid][3][Position][4], GunEdit[playerid][3][Position][5], GunEdit[playerid][3][Bone], GunEdit[playerid][3][Hidden], GunEdit[playerid][3][WeaponTint],
        GunEdit[playerid][4][Position][0], GunEdit[playerid][4][Position][1], GunEdit[playerid][4][Position][2], GunEdit[playerid][4][Position][3], GunEdit[playerid][4][Position][4], GunEdit[playerid][4][Position][5], GunEdit[playerid][4][Bone], GunEdit[playerid][4][Hidden], GunEdit[playerid][4][WeaponTint], AccountData[playerid][pID]);
        mysql_pquery(g_SQL, string);

        ShowTDN(playerid, NOTIFICATION_INFO, "Seluruh perubahan untuk senjata termasuk posisi dan warna berhasil direset!");
    }
    else if (!strcmp(name, "bone", true))
    {
        if(wpid[playerid] < 1 || wpid[playerid] > 45) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang memegang senjata/invalid weapon ID!");
    
        if(wpid[playerid] != 40)
        {
            if(GunData[playerid][g_aWeaponSlots[wpid[playerid]]][WeaponType] == WEAPON_TYPE_NONE)
            {
                SendClientMessageEx(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda ditendang dari server karena diduga Weapon Hack. "YELLOW"[%s]", ReturnWeaponName(wpid[playerid]));
                SetWeapons(playerid); //Reload old weapons
                return KickEx(playerid);
            }
        }

        if (!IsWeaponWearable(wpid[playerid]))
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Senjata ini tidak dapat diedit!");
            
        if (EditingWeapon[playerid])
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang mengedit senjata!");

        Dialog_Show(playerid, "GunEditBone", DIALOG_STYLE_LIST, "Bone", "Spine\n"GRAY"Head\nLeft upper arm\n"GRAY"Right upper arm\nLeft hand\n"GRAY"Right hand\nLeft thigh\n"GRAY"Right thigh\nLeft foot\n"GRAY"Right foot\nRight calf\n"GRAY"Left calf\nLeft forearm\n"GRAY"Right forearm\nLeft shoulder\n"GRAY"Right shoulder\nNeck\n"GRAY"Jaw", "Pilih", "Batal");
        EditingWeapon[playerid] = wpid[playerid];
    }
    else if (!strcmp(name, "hide", true))
    {
        if(wpid[playerid] < 1 || wpid[playerid] > 45) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang memegang senjata/invalid weapon ID!");
    
        if(wpid[playerid] != 40)
        {
            if(GunData[playerid][g_aWeaponSlots[wpid[playerid]]][WeaponType] == WEAPON_TYPE_NONE)
            {
                SendClientMessageEx(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda ditendang dari server karena diduga Weapon Hack. "YELLOW"[%s]", ReturnWeaponName(wpid[playerid]));
                SetWeapons(playerid); //Reload old weapons
                return KickEx(playerid);
            }
        }

        if (!IsWeaponWearable(wpid[playerid]))
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Senjata ini tidak bisa diedit!");
            
        if (EditingWeapon[playerid])
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menyembunyikan senjata jika sedang mengedit!");

        if (!IsWeaponHideable(wpid[playerid]))
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Senjata ini tidak dapat disembunyikan!");

        new index = GetWeaponIndex(wpid[playerid]), weaponname[18], string[1254];
        GetWeaponName(wpid[playerid], weaponname, sizeof(weaponname));
    
        if(GunEdit[playerid][index][Hidden])
        {
            format(string, sizeof(string), "[i] Anda berhasil menampilkan "YELLOW"%s.", weaponname);
            GunEdit[playerid][index][Hidden] = false;
        }
        else
        {
            if(IsPlayerAttachedObjectSlotUsed(playerid, GetWeaponObjectSlot(wpid[playerid])))
                RemovePlayerAttachedObject(playerid, GetWeaponObjectSlot(wpid[playerid]));

            format(string, sizeof(string), "[i] Anda berhasil menyembunyikan "YELLOW"%s.", weaponname);
            GunEdit[playerid][index][Hidden] = true;
        }
        SendClientMessage(playerid, -1, string);
    
        mysql_format(g_SQL, string, sizeof(string), "UPDATE `gunpos` SET `PosX_0` = '%.3f', `PosY_0` = '%.3f', `PosZ_0` = '%.3f', `RotX_0` = '%.3f', `RotY_0` = '%.3f', `RotZ_0` = '%.3f', `Bone_0` = %d, `Hidden_0` = %d, `Tint_0` = %d, `PosX_1` = '%.3f', `PosY_1` = '%.3f', `PosZ_1` = '%.3f', `RotX_1` = '%.3f', `RotY_1` = '%.3f', `RotZ_1` = '%.3f', `Bone_1` = %d, `Hidden_1` = %d, `Tint_1` = %d, \
        `PosX_2` = '%.3f', `PosY_2` = '%.3f', `PosZ_2` = '%.3f', `RotX_2` = '%.3f', `RotY_2` = '%.3f', `RotZ_2` = '%.3f', `Bone_2` = %d, `Hidden_2` = %d, `Tint_2` = %d, `PosX_3` = '%.3f', `PosY_3` = '%.3f', `PosZ_3` = '%.3f', `RotX_3` = '%.3f', `RotY_3` = '%.3f', `RotZ_3` = '%.3f', `Bone_3` = %d, `Hidden_3` = %d, `Tint_3` = %d, \
        `PosX_4` = '%.3f', `PosY_4` = '%.3f', `PosZ_4` = '%.3f', `RotX_4` = '%.3f', `RotY_4` = '%.3f', `RotZ_4` = '%.3f', `Bone_4` = %d, `Hidden_4` = %d, `Tint_4` = %d WHERE `Owner` = %d", GunEdit[playerid][0][Position][0], GunEdit[playerid][0][Position][1], GunEdit[playerid][0][Position][2], GunEdit[playerid][0][Position][3], GunEdit[playerid][0][Position][4], GunEdit[playerid][0][Position][5], GunEdit[playerid][0][Bone], GunEdit[playerid][0][Hidden], GunEdit[playerid][0][WeaponTint],
        GunEdit[playerid][1][Position][0], GunEdit[playerid][1][Position][1], GunEdit[playerid][1][Position][2], GunEdit[playerid][1][Position][3], GunEdit[playerid][1][Position][4], GunEdit[playerid][1][Position][5], GunEdit[playerid][1][Bone], GunEdit[playerid][1][Hidden], GunEdit[playerid][1][WeaponTint],
        GunEdit[playerid][2][Position][0], GunEdit[playerid][2][Position][1], GunEdit[playerid][2][Position][2], GunEdit[playerid][2][Position][3], GunEdit[playerid][2][Position][4], GunEdit[playerid][2][Position][5], GunEdit[playerid][2][Bone], GunEdit[playerid][2][Hidden], GunEdit[playerid][2][WeaponTint],
        GunEdit[playerid][3][Position][0], GunEdit[playerid][3][Position][1], GunEdit[playerid][3][Position][2], GunEdit[playerid][3][Position][3], GunEdit[playerid][3][Position][4], GunEdit[playerid][3][Position][5], GunEdit[playerid][3][Bone], GunEdit[playerid][3][Hidden], GunEdit[playerid][3][WeaponTint],
        GunEdit[playerid][4][Position][0], GunEdit[playerid][4][Position][1], GunEdit[playerid][4][Position][2], GunEdit[playerid][4][Position][3], GunEdit[playerid][4][Position][4], GunEdit[playerid][4][Position][5], GunEdit[playerid][4][Bone], GunEdit[playerid][4][Hidden], GunEdit[playerid][4][WeaponTint], AccountData[playerid][pID]);
        mysql_pquery(g_SQL, string);
    }
    else if(!strcmp(name, "give", true))
    {
        if(wpid[playerid] < 1 || wpid[playerid] > 45) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang memegang senjata/invalid weapon ID!");

        if(GunData[playerid][g_aWeaponSlots[wpid[playerid]]][WeaponType] != WEAPON_TYPE_PLAYER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memberikan senjata faction/admin!");

        if(wpid[playerid] != 40)
        {
            if(GunData[playerid][g_aWeaponSlots[wpid[playerid]]][WeaponType] == WEAPON_TYPE_NONE)
            {
                SendClientMessageEx(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda ditendang dari server karena diduga Weapon Hack. "YELLOW"[Give] [%s]", ReturnWeaponName(wpid[playerid]));
                SetWeapons(playerid); //Reload old weapons
                return KickEx(playerid);
            }
        }

        if(IsPlayerHunting[playerid] && wpid[playerid] == 34)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memberi hunting weapon!");

        if(AccountData[playerid][pTaser] && wpid[playerid] == 23)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memberi taser!");
        
        if(AccountData[playerid][pUseBeanbag] && wpid[playerid] == 25)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memberi beanbag!");

        new otherid;	
        if(sscanf(give, "u", otherid))
            return SUM(playerid, "/gun [give] [playerid]");
            
        if(otherid == INVALID_PLAYER_ID || otherid == playerid || !IsPlayerNearPlayer(playerid, otherid, 5.0))
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan pemain tersebut!");

        if(IsAFireArm(wpid[playerid]) && AccountData[otherid][pLevel] < 5)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut harus memiliki level setidaknya 5!");

        new ammo = GetPlayerAmmoEx(playerid);
        
        ResetWeapon(playerid, wpid[playerid]);
        ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Anda memberi %s kepada %s.", ReturnWeaponName(wpid[playerid]) , GetPlayerRoleplayName(otherid)));
        ShowTDN(otherid, NOTIFICATION_INFO, sprintf("Player %s telah memberimu %s.", GetPlayerRoleplayName(playerid), ReturnWeaponName(wpid[playerid])));
        GivePlayerWeaponEx(otherid, wpid[playerid], ammo, WEAPON_TYPE_PLAYER);
    }
    else if(!strcmp(name, "drop", true))
    {
        if(wpid[playerid] < 1 || wpid[playerid] > 45) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang memegang senjata/invalid weapon ID!");

        if(GunData[playerid][g_aWeaponSlots[wpid[playerid]]][WeaponType] != WEAPON_TYPE_PLAYER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat drop senjata admin/faction!");
        if(wpid[playerid] != 40)
        {
            if(GunData[playerid][g_aWeaponSlots[wpid[playerid]]][WeaponType] == WEAPON_TYPE_NONE)
            {
                SendClientMessageEx(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda ditendang dari server karena diduga Weapon Hack. "YELLOW"[Drop] [%s]", ReturnWeaponName(wpid[playerid]));
                SetWeapons(playerid); //Reload old weapons
                return KickEx(playerid);
            }
        }
        
        if(IsPlayerHunting[playerid] && wpid[playerid] == 34)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Hunting weapon tidak dapat di-drop!");

        if(AccountData[playerid][pTaser] && wpid[playerid] == 23)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Taser tidak dapat di-drop!");
        
        if(AccountData[playerid][pUseBeanbag] && wpid[playerid] == 25)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Beanbag tidak dapat di-drop!");

        static
            Float:x,
            Float:y,
            Float:z,
            Float:angle;

        GetPlayerPos(playerid, x, y, z);
        GetPlayerFacingAngle(playerid, angle);

        x += 1 * floatsin(-angle, degrees);
        y += 1 * floatcos(-angle, degrees);

        DropWeapon(AccountData[playerid][pName], GetWeaponModel(wpid[playerid]), wpid[playerid], GetPlayerAmmoEx(playerid), x, y, z - 1, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
        ResetWeapon(playerid, wpid[playerid]);

        ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, false, false, false, false, 0, true);
        SendRPMeAboveHead(playerid, sprintf("Meletakkan %s ke bawah.", ReturnWeaponName(wpid[playerid])));
    }
    else if(!strcmp(name, "pickup", true))
    {
        new wp = NearWeapon(playerid);
        if(wp != -1)
        {
            if(IsAFireArm(wp) && AccountData[playerid][pLevel] < 5)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda dapat memegang senjata jika sudah mencapai level 5 karakter!");

            PickupWeapon(playerid, wp);
            SendRPMeAboveHead(playerid, sprintf("Mengambil %s di hadapannya.", ReturnWeaponName(DropWeap[wp][WeaponID])));
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, false, false, false, false, 0, true);
        }
    }
    else if(!strcmp(name, "tint", true))
    {
        if(AccountData[playerid][pVIP] < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda perlu minimal VIP Super Pinky untuk akses fitur ini!");
        
        if(wpid[playerid] < 1 || wpid[playerid] > 45) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang memegang senjata/invalid weapon ID!");
    
        if(wpid[playerid] != 40)
        {
            if(GunData[playerid][g_aWeaponSlots[wpid[playerid]]][WeaponType] == WEAPON_TYPE_NONE)
            {
                SendClientMessageEx(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda ditendang dari server karena diduga Weapon Hack. "YELLOW"[%s]", ReturnWeaponName(wpid[playerid]));
                SetWeapons(playerid); //Reload old weapons
                return KickEx(playerid);
            }
        }

        if(!IsWeaponTintable(wpid[playerid]))
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Senjata ini tidak dapat dirubah warnanya!");
        
        if (EditingWeapon[playerid])
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang mengedit senjata!");

        new index = GetWeaponIndex(wpid[playerid]);

        if(GunEdit[playerid][index][Hidden])
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak bisa edit senjata yang disembunyikan!");

        Dialog_Show(playerid, "GunEditTint", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Weapon Tint", 
        "Default (Standard)\n"RED"Merah\n"BLUE"Biru\n"CYAN"Cyan\n"GREEN"Hijau\n"YELLOW"Kuning\n"GOLD"Emas\n"ORANGE"Orange\n{DA9100}Pink\n"MAGENTA"Magenta\n{2C2D2D}Hitam\n{808080}Abu-Abu", "Pilih", "Batal");
    
        EditingWeapon[playerid] = wpid[playerid];
    }
    else
    {
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda memasukkan nama opsi yang tidak valid!");
    }
	return 1;
}
YCMD:gun(playerid, params[], help) = weapon;