#define MAX_LOCKERS 100
#define MAX_FCRAFTS 100
#define MAX_ARMOURIES 100
#define MAX_VAULTS 100
#define MAX_FGARAGES 100

enum e_lockerinfo
{
    Float:Pos[3],
    World,
    Interior,
    Type,
    Text[64],

    //not saved
    STREAMER_TAG_PICKUP: Pickup,
    STREAMER_TAG_3D_TEXT_LABEL: Label
};
new LockerData[MAX_LOCKERS][e_lockerinfo],
    Iterator:Lockers<MAX_LOCKERS>;

enum e_fcraftinfo
{
    Float:Pos[3],
    World,
    Interior,
    Type,

    //not saved
    STREAMER_TAG_PICKUP: Pickup,
    STREAMER_TAG_3D_TEXT_LABEL: Label
};
new FCraftData[MAX_FCRAFTS][e_fcraftinfo],
    Iterator:FCrafts<MAX_FCRAFTS>;

enum e_fgarageinfo
{
    Float:Pos[3],
    Float:GaragePos[3],
    Float:GarageSpawnPos[4],
    World,
    Interior,
    Type,
    Text[64],

    //not saved
    STREAMER_TAG_PICKUP: Pickup,
    STREAMER_TAG_3D_TEXT_LABEL: Label,
    STREAMER_TAG_OBJECT: Object
};
new FactGarageData[MAX_FGARAGES][e_fgarageinfo],
    Iterator:FGarages<MAX_FGARAGES>;

enum e_vaultinfo
{
    Float:Pos[3],
    World,
    Interior,
    Type,
    Text[64],

    //not saved
    STREAMER_TAG_PICKUP: Pickup,
    STREAMER_TAG_3D_TEXT_LABEL: Label
};
new VaultData[MAX_VAULTS][e_vaultinfo],
    Iterator:Vaults<MAX_VAULTS>;

enum e_armouryinfo
{
    Float:Pos[3],
    World,
    Interior,
    Text[64],

    //not saved
    STREAMER_TAG_PICKUP: Pickup,
    STREAMER_TAG_3D_TEXT_LABEL: Label
};
new ArmouryData[MAX_ARMOURIES][e_armouryinfo],
    Iterator:Armouries<MAX_ARMOURIES>;

forward LoadLockers();
public LoadLockers()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
 		new lid;
		for(new i; i < rows; i++)
		{
            cache_get_value_name_int(i, "id", lid);
            cache_get_value_name_float(i, "posx", LockerData[lid][Pos][0]);
            cache_get_value_name_float(i, "posy", LockerData[lid][Pos][1]);
            cache_get_value_name_float(i, "posz", LockerData[lid][Pos][2]);
            cache_get_value_name_int(i, "interior", LockerData[lid][Interior]);
            cache_get_value_name_int(i, "world", LockerData[lid][World]);
            cache_get_value_name_int(i, "type", LockerData[lid][Type]);
            cache_get_value_name(i, "name", LockerData[lid][Text]);
            
		    Locker_Rebuild(lid);

			Iter_Add(Lockers, lid);
        }
        printf("[Dynamic Locker] Jumlah total Locker yang dimuat: %d.", rows);
	}
    return 1;
}

forward LoadFCrafts();
public LoadFCrafts()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
 		new lid;
		for(new i; i < rows; i++)
		{
            cache_get_value_name_int(i, "id", lid);
            cache_get_value_name_float(i, "posx", FCraftData[lid][Pos][0]);
            cache_get_value_name_float(i, "posy", FCraftData[lid][Pos][1]);
            cache_get_value_name_float(i, "posz", FCraftData[lid][Pos][2]);
            cache_get_value_name_int(i, "interior", FCraftData[lid][Interior]);
            cache_get_value_name_int(i, "world", FCraftData[lid][World]);
            cache_get_value_name_int(i, "type", FCraftData[lid][Type]);
            
		    FCraft_Rebuild(lid);

			Iter_Add(FCrafts, lid);
        }
        printf("[Dynamic Fact Craft] Jumlah total Fact Craft yang dimuat: %d.", rows);
	}
    return 1;
}

forward LoadArmouries();
public LoadArmouries()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
 		new lid;
		for(new i; i < rows; i++)
		{
            cache_get_value_name_int(i, "id", lid);
            cache_get_value_name_float(i, "posx", ArmouryData[lid][Pos][0]);
            cache_get_value_name_float(i, "posy", ArmouryData[lid][Pos][1]);
            cache_get_value_name_float(i, "posz", ArmouryData[lid][Pos][2]);
            cache_get_value_name_int(i, "interior", ArmouryData[lid][Interior]);
            cache_get_value_name_int(i, "world", ArmouryData[lid][World]);
            cache_get_value_name(i, "name", ArmouryData[lid][Text]);
            
		    Armoury_Rebuild(lid);

			Iter_Add(Armouries, lid);
        }
        printf("[Dynamic Armoury] Jumlah total Armoury yang dimuat: %d.", rows);
	}
    return 1;
}

forward LoadVaults();
public LoadVaults()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
 		new lid;
		for(new i; i < rows; i++)
		{
            cache_get_value_name_int(i, "id", lid);
            cache_get_value_name_float(i, "posx", VaultData[lid][Pos][0]);
            cache_get_value_name_float(i, "posy", VaultData[lid][Pos][1]);
            cache_get_value_name_float(i, "posz", VaultData[lid][Pos][2]);
            cache_get_value_name_int(i, "interior", VaultData[lid][Interior]);
            cache_get_value_name_int(i, "world", VaultData[lid][World]);
            cache_get_value_name_int(i, "type", VaultData[lid][Type]);
            cache_get_value_name(i, "name", VaultData[lid][Text]);
            
		    Vault_Rebuild(lid);

			Iter_Add(Vaults, lid);
        }
        printf("[Dynamic Faction Vault] Jumlah total Faction Vault yang dimuat: %d.", rows);
	}
    return 1;
}

forward LoadFGarages();
public LoadFGarages()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
 		new lid;
		for(new i; i < rows; i++)
		{
            cache_get_value_name_int(i, "id", lid);
            cache_get_value_name_float(i, "posx", FactGarageData[lid][Pos][0]);
            cache_get_value_name_float(i, "posy", FactGarageData[lid][Pos][1]);
            cache_get_value_name_float(i, "posz", FactGarageData[lid][Pos][2]);
            cache_get_value_name_float(i, "gposx", FactGarageData[lid][GaragePos][0]);
            cache_get_value_name_float(i, "gposy", FactGarageData[lid][GaragePos][1]);
            cache_get_value_name_float(i, "gposz", FactGarageData[lid][GaragePos][2]);
            cache_get_value_name_float(i, "gposspawnx", FactGarageData[lid][GarageSpawnPos][0]);
            cache_get_value_name_float(i, "gposspawny", FactGarageData[lid][GarageSpawnPos][1]);
            cache_get_value_name_float(i, "gposspawnz", FactGarageData[lid][GarageSpawnPos][2]);
            cache_get_value_name_float(i, "gposspawna", FactGarageData[lid][GarageSpawnPos][3]);
            cache_get_value_name_int(i, "interior", FactGarageData[lid][Interior]);
            cache_get_value_name_int(i, "world", FactGarageData[lid][World]);
            cache_get_value_name_int(i, "type", FactGarageData[lid][Type]);
            cache_get_value_name(i, "name", FactGarageData[lid][Text]);
            
		    FGarage_Rebuild(lid);

			Iter_Add(FGarages, lid);
        }
        printf("[Dynamic Faction Garage] Jumlah total Faction Garage yang dimuat: %d.", rows);
	}

    return 1;
}

Vault_Rebuild(lid)
{
    if(lid != -1)
    {
        if(DestroyDynamicPickup(VaultData[lid][Pickup]))
            VaultData[lid][Pickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

        if(DestroyDynamic3DTextLabel(VaultData[lid][Label]))
            VaultData[lid][Label] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        VaultData[lid][Pickup] = CreateDynamicPickup(1210, 23, VaultData[lid][Pos][0], VaultData[lid][Pos][1], VaultData[lid][Pos][2], VaultData[lid][World], VaultData[lid][Interior], -1, 30.0, -1, 0);
        
        static string[268];
        switch(VaultData[lid][Type])
        {
            case 1: //LSPD
            {
                format(string, sizeof(string), "[Kepolisian Pahlawan Roleplay]\n"GREEN"%s\n"WHITE"Gudang Penyimpanan Harta Kekayaan Fraksi\nGunakan "YELLOW"'/vault' "WHITE"untuk akses menu ini", VaultData[lid][Text]);
                VaultData[lid][Label] = CreateDynamic3DTextLabel(string, 0x0096FFFF, VaultData[lid][Pos][0], VaultData[lid][Pos][1], VaultData[lid][Pos][2]+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, VaultData[lid][World], VaultData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 2: //LSFD
            {
                format(string, sizeof(string), "[Paramedis Pahlawan Roleplay]\n"GREEN"%s\n"WHITE"Gudang Penyimpanan Harta Kekayaan Fraksi\nGunakan "YELLOW"'/vault' "WHITE"untuk akses menu ini", VaultData[lid][Text]);
                VaultData[lid][Label] = CreateDynamic3DTextLabel(string, 0xFF1A1AFF, VaultData[lid][Pos][0], VaultData[lid][Pos][1], VaultData[lid][Pos][2]+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, VaultData[lid][World], VaultData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 3: //Putri Deli
            {
                format(string, sizeof(string), "[Putri Deli Beach Club]\n"GREEN"%s\n"WHITE"Gudang Penyimpanan Harta Kekayaan Fraksi\nGunakan "YELLOW"'/vault' "WHITE"untuk akses menu ini", VaultData[lid][Text]);
                VaultData[lid][Label] = CreateDynamic3DTextLabel(string, 0xD2691EFF, VaultData[lid][Pos][0], VaultData[lid][Pos][1], VaultData[lid][Pos][2]+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, VaultData[lid][World], VaultData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 4: //SAGOV
            {
                format(string, sizeof(string), "[Pemerintah Kota Pahlawan Roleplay]\n"GREEN"%s\n"WHITE"Gudang Penyimpanan Harta Kekayaan Fraksi\nGunakan "YELLOW"'/vault' "WHITE"untuk akses menu ini", VaultData[lid][Text]);
                VaultData[lid][Label] = CreateDynamic3DTextLabel(string, 0x0096FFFF, VaultData[lid][Pos][0], VaultData[lid][Pos][1], VaultData[lid][Pos][2]+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, VaultData[lid][World], VaultData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 5: //bennys
            {
                format(string, sizeof(string), "[Bennys Automotive]\n"GREEN"%s\n"WHITE"Gudang Penyimpanan Harta Kekayaan Fraksi\nGunakan "YELLOW"'/vault' "WHITE"untuk akses menu ini", VaultData[lid][Text]);
                VaultData[lid][Label] = CreateDynamic3DTextLabel(string, 0x20B2AAFF, VaultData[lid][Pos][0], VaultData[lid][Pos][1], VaultData[lid][Pos][2]+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, VaultData[lid][World], VaultData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 6: //Uber
            {
                format(string, sizeof(string), "[Uber]\n"GREEN"%s\n"WHITE"Gudang Penyimpanan Harta Kekayaan Fraksi\nGunakan "YELLOW"'/vault' "WHITE"untuk akses menu ini", VaultData[lid][Text]);
                VaultData[lid][Label] = CreateDynamic3DTextLabel(string, 0xc0c0c8FF, VaultData[lid][Pos][0], VaultData[lid][Pos][1], VaultData[lid][Pos][2]+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, VaultData[lid][World], VaultData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 7: //Dinarbucks
            {
                format(string, sizeof(string), "[Pinky Tiger Club]\n"GREEN"%s\n"WHITE"Gudang Penyimpanan Harta Kekayaan Fraksi\nGunakan "YELLOW"'/vault' "WHITE"untuk akses menu ini", VaultData[lid][Text]);
                VaultData[lid][Label] = CreateDynamic3DTextLabel(string, 0x188d38FF, VaultData[lid][Pos][0], VaultData[lid][Pos][1], VaultData[lid][Pos][2]+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, VaultData[lid][World], VaultData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 8: //Fox 11 LA
            {
                format(string, sizeof(string), "[Pewarta Pahlawan Roleplay]\n"GREEN"%s\n"WHITE"Gudang Penyimpanan Harta Kekayaan Fraksi\nGunakan "YELLOW"'/vault' "WHITE"untuk akses menu ini", VaultData[lid][Text]);
                VaultData[lid][Label] = CreateDynamic3DTextLabel(string, 0x075ebfFF, VaultData[lid][Pos][0], VaultData[lid][Pos][1], VaultData[lid][Pos][2]+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, VaultData[lid][World], VaultData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 9: //bengkel
            {
                format(string, sizeof(string), "[Automax Workshop]\n"GREEN"%s\n"WHITE"Gudang Penyimpanan Harta Kekayaan Fraksi\nGunakan "YELLOW"'/vault' "WHITE"untuk akses menu ini", VaultData[lid][Text]);
                VaultData[lid][Label] = CreateDynamic3DTextLabel(string, 0x6fd356FF, VaultData[lid][Pos][0], VaultData[lid][Pos][1], VaultData[lid][Pos][2]+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, VaultData[lid][World], VaultData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 10: //bengkel
            {
                format(string, sizeof(string), "[Handover Motorworks]\n"GREEN"%s\n"WHITE"Gudang Penyimpanan Harta Kekayaan Fraksi\nGunakan "YELLOW"'/vault' "WHITE"untuk akses menu ini", VaultData[lid][Text]);
                VaultData[lid][Label] = CreateDynamic3DTextLabel(string, 0xff7dcbFF, VaultData[lid][Pos][0], VaultData[lid][Pos][1], VaultData[lid][Pos][2]+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, VaultData[lid][World], VaultData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 11: //+arivena
            {
                format(string, sizeof(string), "[Sri Mersing Resto]\n"GREEN"%s\n"WHITE"Gudang Penyimpanan Harta Kekayaan Fraksi\nGunakan "YELLOW"'/vault' "WHITE"untuk akses menu ini", VaultData[lid][Text]);
                VaultData[lid][Label] = CreateDynamic3DTextLabel(string, 0xcbe9f6FF, VaultData[lid][Pos][0], VaultData[lid][Pos][1], VaultData[lid][Pos][2]+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, VaultData[lid][World], VaultData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 12: //texas
            {
                format(string, sizeof(string), "[Texas Chicken]\n"GREEN"%s\n"WHITE"Gudang Penyimpanan Harta Kekayaan Fraksi\nGunakan "YELLOW"'/vault' "WHITE"untuk akses menu ini", VaultData[lid][Text]);
                VaultData[lid][Label] = CreateDynamic3DTextLabel(string, 0xFfff00FF, VaultData[lid][Pos][0], VaultData[lid][Pos][1], VaultData[lid][Pos][2]+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, VaultData[lid][World], VaultData[lid][Interior], -1, 10.00, -1, 0);
            }
        }
    }
    return 1;
}

FGarage_Rebuild(lid)
{
    if(lid != -1)
    {
        if(DestroyDynamicPickup(FactGarageData[lid][Pickup]))
            FactGarageData[lid][Pickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

        if(DestroyDynamic3DTextLabel(FactGarageData[lid][Label]))
            FactGarageData[lid][Label] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        if(DestroyDynamicObject(FactGarageData[lid][Object]))
            FactGarageData[lid][Object] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
        FactGarageData[lid][Object] = CreateDynamicObject(1316, FactGarageData[lid][Pos][0], FactGarageData[lid][Pos][1], FactGarageData[lid][Pos][2] - 0.9, 0.0, 0.0, 0.0, FactGarageData[lid][World], FactGarageData[lid][Interior], -1, 100.00, 100.00, -1);
        SetDynamicObjectMaterial(FactGarageData[lid][Object], 0, 18646, "matcolours", "white", 0x99ffff00);

        FactGarageData[lid][Pickup] = CreateDynamicPickup(2485, 23, FactGarageData[lid][Pos][0], FactGarageData[lid][Pos][1], FactGarageData[lid][Pos][2]-0.05, FactGarageData[lid][World], FactGarageData[lid][Interior], -1, 30.0, -1, 0);
        
        static string[268];
        switch(FactGarageData[lid][Type])
        {
            case 1: //LSPD
            {
                format(string, sizeof(string), "[ "WHITE"(Garasi Fraksi): "YELLOW"Kepolisian Pahlawan Roleplay "GREEN"]\n"WHITE"| %s |\n"YELLOW"'/fgarage'", FactGarageData[lid][Text]);
                FactGarageData[lid][Label] = CreateDynamic3DTextLabel(string, Y_GREEN, FactGarageData[lid][Pos][0], FactGarageData[lid][Pos][1], FactGarageData[lid][Pos][2]+0.45, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, FactGarageData[lid][World], FactGarageData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 2: //LSFD
            {
                format(string, sizeof(string), "[ "WHITE"(Garasi Fraksi): "YELLOW"Paramedis Pahlawan Roleplay "GREEN"]\n"WHITE"| %s |\n"YELLOW"'/fgarage'", FactGarageData[lid][Text]);
                FactGarageData[lid][Label] = CreateDynamic3DTextLabel(string, Y_GREEN, FactGarageData[lid][Pos][0], FactGarageData[lid][Pos][1], FactGarageData[lid][Pos][2]+0.45, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, FactGarageData[lid][World], FactGarageData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 3: //Putri Deli
            {
                format(string, sizeof(string), "[ "WHITE"(Garasi Fraksi): "YELLOW"Putri Deli Beach Club "GREEN"]\n"WHITE"| %s |\n"YELLOW"'/fgarage'", FactGarageData[lid][Text]);
                FactGarageData[lid][Label] = CreateDynamic3DTextLabel(string, Y_GREEN, FactGarageData[lid][Pos][0], FactGarageData[lid][Pos][1], FactGarageData[lid][Pos][2]+0.45, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, FactGarageData[lid][World], FactGarageData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 4: //SAGOV
            {
                format(string, sizeof(string), "[ "WHITE"(Garasi Fraksi): "YELLOW"Pemerintah Daerah Pahlawan Roleplay "GREEN"]\n"WHITE"| %s |\n"YELLOW"'/fgarage'", FactGarageData[lid][Text]);
                FactGarageData[lid][Label] = CreateDynamic3DTextLabel(string, Y_GREEN, FactGarageData[lid][Pos][0], FactGarageData[lid][Pos][1], FactGarageData[lid][Pos][2]+0.45, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, FactGarageData[lid][World], FactGarageData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 5: //Bennys
            {
                format(string, sizeof(string), "[ "WHITE"(Garasi Fraksi): "YELLOW"Bennys Automotive "GREEN"]\n"WHITE"| %s |\n"YELLOW"'/fgarage'", FactGarageData[lid][Text]);
                FactGarageData[lid][Label] = CreateDynamic3DTextLabel(string, Y_GREEN, FactGarageData[lid][Pos][0], FactGarageData[lid][Pos][1], FactGarageData[lid][Pos][2]+0.45, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, FactGarageData[lid][World], FactGarageData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 6: //Uber
            {
                format(string, sizeof(string), "[ "WHITE"(Garasi Fraksi): "YELLOW"Uber Pahlawan Roleplay "GREEN"]\n"WHITE"| %s |\n"YELLOW"'/fgarage'", FactGarageData[lid][Text]);
                FactGarageData[lid][Label] = CreateDynamic3DTextLabel(string, Y_GREEN, FactGarageData[lid][Pos][0], FactGarageData[lid][Pos][1], FactGarageData[lid][Pos][2]+0.45, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, FactGarageData[lid][World], FactGarageData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 7: //Dinarbucks
            {
                format(string, sizeof(string), "[ "WHITE"(Garasi Fraksi): "YELLOW"Pinky Tiger Club "GREEN"]\n"WHITE"| %s |\n"YELLOW"'/fgarage'", FactGarageData[lid][Text]);
                FactGarageData[lid][Label] = CreateDynamic3DTextLabel(string, Y_GREEN, FactGarageData[lid][Pos][0], FactGarageData[lid][Pos][1], FactGarageData[lid][Pos][2]+0.45, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, FactGarageData[lid][World], FactGarageData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 8: //Fox 11 LA
            {
                format(string, sizeof(string), "[ "WHITE"(Garasi Fraksi): "YELLOW"Pewarta Pahlawan Roleplay "GREEN"]\n"WHITE"| %s |\n"YELLOW"'/fgarage'", FactGarageData[lid][Text]);
                FactGarageData[lid][Label] = CreateDynamic3DTextLabel(string, Y_GREEN, FactGarageData[lid][Pos][0], FactGarageData[lid][Pos][1], FactGarageData[lid][Pos][2]+0.45, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, FactGarageData[lid][World], FactGarageData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 9: //bengkel
            {
                format(string, sizeof(string), "[ "WHITE"(Garasi Fraksi): "YELLOW"Automax Workshop "GREEN"]\n"WHITE"| %s |\n"YELLOW"'/fgarage'", FactGarageData[lid][Text]);
                FactGarageData[lid][Label] = CreateDynamic3DTextLabel(string, Y_GREEN, FactGarageData[lid][Pos][0], FactGarageData[lid][Pos][1], FactGarageData[lid][Pos][2]+0.45, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, FactGarageData[lid][World], FactGarageData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 10: //bengkel
            {
                format(string, sizeof(string), "[ "WHITE"(Garasi Fraksi): "YELLOW"Handover Motorworks "GREEN"]\n"WHITE"| %s |\n"YELLOW"'/fgarage'", FactGarageData[lid][Text]);
                FactGarageData[lid][Label] = CreateDynamic3DTextLabel(string, Y_GREEN, FactGarageData[lid][Pos][0], FactGarageData[lid][Pos][1], FactGarageData[lid][Pos][2]+0.45, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, FactGarageData[lid][World], FactGarageData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 11: //+arivena
            {
                format(string, sizeof(string), "[ "WHITE"(Garasi Fraksi): "YELLOW"Sri Mersing Resto "GREEN"]\n"WHITE"| %s |\n"YELLOW"'/fgarage'", FactGarageData[lid][Text]);
                FactGarageData[lid][Label] = CreateDynamic3DTextLabel(string, Y_GREEN, FactGarageData[lid][Pos][0], FactGarageData[lid][Pos][1], FactGarageData[lid][Pos][2]+0.45, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, FactGarageData[lid][World], FactGarageData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 12: //texas chicken
            {
                format(string, sizeof(string), "[ "WHITE"(Garasi Fraksi): "YELLOW"Texas Chicken "GREEN"]\n"WHITE"| %s |\n"YELLOW"'/fgarage'", FactGarageData[lid][Text]);
                FactGarageData[lid][Label] = CreateDynamic3DTextLabel(string, Y_GREEN, FactGarageData[lid][Pos][0], FactGarageData[lid][Pos][1], FactGarageData[lid][Pos][2]+0.45, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, FactGarageData[lid][World], FactGarageData[lid][Interior], -1, 10.00, -1, 0);
            }
        }
    }
    return 1;
}

Locker_Rebuild(lid)
{
    if(lid != -1)
    {
        if(DestroyDynamicPickup(LockerData[lid][Pickup]))
            LockerData[lid][Pickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

        if(DestroyDynamic3DTextLabel(LockerData[lid][Label]))
            LockerData[lid][Label] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        LockerData[lid][Pickup] = CreateDynamicPickup(1275, 23, LockerData[lid][Pos][0], LockerData[lid][Pos][1], LockerData[lid][Pos][2], LockerData[lid][World], LockerData[lid][Interior], -1, 30.0, -1, 0);
        
        static string[268];
        switch(LockerData[lid][Type])
        {
            case 1: //LSPD
            {
                format(string, sizeof(string), "[Kepolisian Pahlawan Roleplay]\n"GREEN"%s\n"WHITE"Locker Fraksi\nGunakan "YELLOW"'/locker' "WHITE"untuk akses menu ini", LockerData[lid][Text]);
                LockerData[lid][Label] = CreateDynamic3DTextLabel(string, 0x0096FFFF, LockerData[lid][Pos][0], LockerData[lid][Pos][1], LockerData[lid][Pos][2]+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, LockerData[lid][World], LockerData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 2: //LSFD
            {
                format(string, sizeof(string), "[Paramedis Pahlawan Roleplay]\n"GREEN"%s\n"WHITE"Locker Fraksi\nGunakan "YELLOW"'/locker' "WHITE"untuk akses menu ini", LockerData[lid][Text]);
                LockerData[lid][Label] = CreateDynamic3DTextLabel(string, 0xFF1A1AFF, LockerData[lid][Pos][0], LockerData[lid][Pos][1], LockerData[lid][Pos][2]+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, LockerData[lid][World], LockerData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 3: //Putri Deli
            {
                format(string, sizeof(string), "[Putri Deli Beach Club]\n"GREEN"%s\n"WHITE"Locker Fraksi\nGunakan "YELLOW"'/locker' "WHITE"untuk akses menu ini", LockerData[lid][Text]);
                VaultData[lid][Label] = CreateDynamic3DTextLabel(string, 0xD2691EFF, LockerData[lid][Pos][0], LockerData[lid][Pos][1], LockerData[lid][Pos][2]+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, LockerData[lid][World], LockerData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 4: //SAGOV
            {
                format(string, sizeof(string), "[Pemerintah Kota Pahlawan Roleplay]\n"GREEN"%s\n"WHITE"Locker Fraksi\nGunakan "YELLOW"'/locker' "WHITE"untuk akses menu ini", LockerData[lid][Text]);
                LockerData[lid][Label] = CreateDynamic3DTextLabel(string, 0x0096FFFF, LockerData[lid][Pos][0], LockerData[lid][Pos][1], LockerData[lid][Pos][2]+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, LockerData[lid][World], LockerData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 5: //bennys
            {
                format(string, sizeof(string), "[Bennys Automotive]\n"GREEN"%s\n"WHITE"Locker Fraksi\nGunakan "YELLOW"'/locker' "WHITE"untuk akses menu ini", LockerData[lid][Text]);
                LockerData[lid][Label] = CreateDynamic3DTextLabel(string, 0x20B2AAFF, LockerData[lid][Pos][0], LockerData[lid][Pos][1], LockerData[lid][Pos][2]+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, LockerData[lid][World], LockerData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 6: //Uber
            {
                format(string, sizeof(string), "[Uber]\n"GREEN"%s\n"WHITE"Locker Fraksi\nGunakan "YELLOW"'/locker' "WHITE"untuk akses menu ini", LockerData[lid][Text]);
                LockerData[lid][Label] = CreateDynamic3DTextLabel(string, 0xc0c0c8FF, LockerData[lid][Pos][0], LockerData[lid][Pos][1], LockerData[lid][Pos][2]+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, LockerData[lid][World], LockerData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 7: //Dinarbucks
            {
                format(string, sizeof(string), "[Pinky Tiger Club]\n"GREEN"%s\n"WHITE"Locker Fraksi\nGunakan "YELLOW"'/locker' "WHITE"untuk akses menu ini", LockerData[lid][Text]);
                LockerData[lid][Label] = CreateDynamic3DTextLabel(string, 0x188d38FF, LockerData[lid][Pos][0], LockerData[lid][Pos][1], LockerData[lid][Pos][2]+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, LockerData[lid][World], LockerData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 8: //FOX 11 LA
            {
                format(string, sizeof(string), "[Pewarta Pahlawan Roleplay]\n"GREEN"%s\n"WHITE"Locker Fraksi\nGunakan "YELLOW"'/locker' "WHITE"untuk akses menu ini", LockerData[lid][Text]);
                LockerData[lid][Label] = CreateDynamic3DTextLabel(string, 0x075ebfFF, LockerData[lid][Pos][0], LockerData[lid][Pos][1], LockerData[lid][Pos][2]+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, LockerData[lid][World], LockerData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 9: //automax
            {
                format(string, sizeof(string), "[Automax Workshop]\n"GREEN"%s\n"WHITE"Locker Fraksi\nGunakan "YELLOW"'/locker' "WHITE"untuk akses menu ini", LockerData[lid][Text]);
                LockerData[lid][Label] = CreateDynamic3DTextLabel(string, 0x6fd356FF, LockerData[lid][Pos][0], LockerData[lid][Pos][1], LockerData[lid][Pos][2]+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, LockerData[lid][World], LockerData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 10: //handover
            {
                format(string, sizeof(string), "[Handover Motorworks]\n"GREEN"%s\n"WHITE"Locker Fraksi\nGunakan "YELLOW"'/locker' "WHITE"untuk akses menu ini", LockerData[lid][Text]);
                LockerData[lid][Label] = CreateDynamic3DTextLabel(string, 0xff7dcbFF, LockerData[lid][Pos][0], LockerData[lid][Pos][1], LockerData[lid][Pos][2]+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, LockerData[lid][World], LockerData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 11: //+arivena
            {
                format(string, sizeof(string), "[Sri Mersing Resto]\n"GREEN"%s\n"WHITE"Locker Fraksi\nGunakan "YELLOW"'/locker' "WHITE"untuk akses menu ini", LockerData[lid][Text]);
                LockerData[lid][Label] = CreateDynamic3DTextLabel(string, 0xcbe9f6FF, LockerData[lid][Pos][0], LockerData[lid][Pos][1], LockerData[lid][Pos][2]+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, LockerData[lid][World], LockerData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 12: //texas
            {
                format(string, sizeof(string), "[Texas Chicken]\n"GREEN"%s\n"WHITE"Locker Fraksi\nGunakan "YELLOW"'/locker' "WHITE"untuk akses menu ini", LockerData[lid][Text]);
                LockerData[lid][Label] = CreateDynamic3DTextLabel(string, 0xFfff00FF, LockerData[lid][Pos][0], LockerData[lid][Pos][1], LockerData[lid][Pos][2]+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, LockerData[lid][World], LockerData[lid][Interior], -1, 10.00, -1, 0);
            }
        }
    }
    return 1;
}

FCraft_Rebuild(lid)
{
    if(lid != -1)
    {
        if(DestroyDynamicPickup(FCraftData[lid][Pickup]))
            FCraftData[lid][Pickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

        if(DestroyDynamic3DTextLabel(FCraftData[lid][Label]))
            FCraftData[lid][Label] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        FCraftData[lid][Pickup] = CreateDynamicPickup(19832, 23, FCraftData[lid][Pos][0], FCraftData[lid][Pos][1], FCraftData[lid][Pos][2], FCraftData[lid][World], FCraftData[lid][Interior], -1, 30.0, -1, 0);
        
        switch(FCraftData[lid][Type])
        {
            case 5: //bennys
            {
                FCraftData[lid][Label] = CreateDynamic3DTextLabel("[Titik Crafting Fraksi]\nBengkel Bennys\nGunakan "YELLOW"'/fcraft' "WHITE"untuk akses menu ini", 0xffffffff, FCraftData[lid][Pos][0], FCraftData[lid][Pos][1], FCraftData[lid][Pos][2]+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, FCraftData[lid][World], FCraftData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 9: //automax
            {
                FCraftData[lid][Label] = CreateDynamic3DTextLabel("[Titik Crafting Fraksi]\nAutomax Workshop\nGunakan "YELLOW"'/fcraft' "WHITE"untuk akses menu ini", 0xffffffff, FCraftData[lid][Pos][0], FCraftData[lid][Pos][1], FCraftData[lid][Pos][2]+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, FCraftData[lid][World], FCraftData[lid][Interior], -1, 10.00, -1, 0);
            }
            case 10: //handover
            {
                FCraftData[lid][Label] = CreateDynamic3DTextLabel("[Titik Crafting Fraksi]\nHandover Motorworks\nGunakan "YELLOW"'/fcraft' "WHITE"untuk akses menu ini", 0xffffffff, FCraftData[lid][Pos][0], FCraftData[lid][Pos][1], FCraftData[lid][Pos][2]+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, FCraftData[lid][World], FCraftData[lid][Interior], -1, 10.00, -1, 0);
            }
        }
    }
    return 1;
}

Armoury_Rebuild(lid)
{
    if(lid != -1)
    {
        if(DestroyDynamicPickup(ArmouryData[lid][Pickup]))
            ArmouryData[lid][Pickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

        if(DestroyDynamic3DTextLabel(ArmouryData[lid][Label]))
            ArmouryData[lid][Label] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        ArmouryData[lid][Pickup] = CreateDynamicPickup(1242, 23, ArmouryData[lid][Pos][0], ArmouryData[lid][Pos][1], ArmouryData[lid][Pos][2], ArmouryData[lid][World], ArmouryData[lid][Interior], -1, 30.0, -1, 0);
        
        static string[268];
        format(string, sizeof(string), "[Kepolisian Pahlawan Roleplay]\n"GREEN"%s\n"WHITE"Gudang Perlengkapan & Persenjataan\nGunakan "YELLOW"'/armoury' "WHITE"untuk akses menu ini", ArmouryData[lid][Text]);
        ArmouryData[lid][Label] = CreateDynamic3DTextLabel(string, 0x0096FFFF, ArmouryData[lid][Pos][0], ArmouryData[lid][Pos][1], ArmouryData[lid][Pos][2]+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, ArmouryData[lid][World], ArmouryData[lid][Interior], -1, 10.00, -1, 0);
    }
    return 1;
}

IsPlayerNearLocker(playerid)
{
    foreach(new lid : Lockers)
    {
        if(IsPlayerInRangeOfPoint(playerid, 1.0, LockerData[lid][Pos][0], LockerData[lid][Pos][1], LockerData[lid][Pos][2]) && GetPlayerVirtualWorld(playerid) == LockerData[lid][World] && GetPlayerInterior(playerid) == LockerData[lid][Interior] && AccountData[playerid][pFaction] == LockerData[lid][Type])
        {
            return true;
        }
    }
    return false;
}

IsPlayerNearFCraft(playerid)
{
    foreach(new lid : FCrafts)
    {
        if(IsPlayerInRangeOfPoint(playerid, 1.0, FCraftData[lid][Pos][0], FCraftData[lid][Pos][1], FCraftData[lid][Pos][2]) && GetPlayerVirtualWorld(playerid) == FCraftData[lid][World] && GetPlayerInterior(playerid) == FCraftData[lid][Interior] && AccountData[playerid][pFaction] == FCraftData[lid][Type])
        {
            return true;
        }
    }
    return false;
}

IsPlayerNearArmoury(playerid)
{
    foreach(new lid : Armouries)
    {
        if(IsPlayerInRangeOfPoint(playerid, 3.0, ArmouryData[lid][Pos][0], ArmouryData[lid][Pos][1], ArmouryData[lid][Pos][2]) && GetPlayerVirtualWorld(playerid) == ArmouryData[lid][World] && GetPlayerInterior(playerid) == ArmouryData[lid][Interior])
        {
            return true;
        }
    }
    return false;
}

IsPlayerNearVault(playerid)
{
    foreach(new lid : Vaults)
    {
        if(IsPlayerInRangeOfPoint(playerid, 1.0, VaultData[lid][Pos][0], VaultData[lid][Pos][1], VaultData[lid][Pos][2]) && GetPlayerVirtualWorld(playerid) == VaultData[lid][World] && GetPlayerInterior(playerid) == VaultData[lid][Interior] && AccountData[playerid][pFaction] == VaultData[lid][Type])
        {
            return true;
        }
    }
    return false;
}

IsPlayerNearFGarage(playerid)
{
    foreach(new lid : FGarages)
    {
        if(IsPlayerInRangeOfPoint(playerid, 3.0, FactGarageData[lid][Pos][0], FactGarageData[lid][Pos][1], FactGarageData[lid][Pos][2]) && GetPlayerVirtualWorld(playerid) == FactGarageData[lid][World] && GetPlayerInterior(playerid) == FactGarageData[lid][Interior] && AccountData[playerid][pFaction] == FactGarageData[lid][Type])
        {
            return true;
        }
    }
    return false;
}

GetPlayerNearestFLocker(playerid)
{
    foreach(new lid : Lockers)
    {
        if(IsPlayerInRangeOfPoint(playerid, 3.0, LockerData[lid][Pos][0], LockerData[lid][Pos][1], LockerData[lid][Pos][2]) && GetPlayerVirtualWorld(playerid) == LockerData[lid][World] && GetPlayerInterior(playerid) == LockerData[lid][Interior])
        {
            return lid;
        }
    }
    return -1;
}

GetPlayerNearestFCraft(playerid)
{
    foreach(new lid : FCrafts)
    {
        if(IsPlayerInRangeOfPoint(playerid, 3.0, FCraftData[lid][Pos][0], FCraftData[lid][Pos][1], FCraftData[lid][Pos][2]) && GetPlayerVirtualWorld(playerid) == FCraftData[lid][World] && GetPlayerInterior(playerid) == FCraftData[lid][Interior])
        {
            return lid;
        }
    }
    return -1;
}

GetPlayerNearestFVault(playerid)
{
    foreach(new lid : Vaults)
    {
        if(IsPlayerInRangeOfPoint(playerid, 3.0, VaultData[lid][Pos][0], VaultData[lid][Pos][1], VaultData[lid][Pos][2]) && GetPlayerVirtualWorld(playerid) == VaultData[lid][World] && GetPlayerInterior(playerid) == VaultData[lid][Interior])
        {
            return lid;
        }
    }
    return -1;
}

GetPlayerNearestFArmoury(playerid)
{
    foreach(new lid : Armouries)
    {
        if(IsPlayerInRangeOfPoint(playerid, 3.0, ArmouryData[lid][Pos][0], ArmouryData[lid][Pos][1], ArmouryData[lid][Pos][2]) && GetPlayerVirtualWorld(playerid) == ArmouryData[lid][World] && GetPlayerInterior(playerid) == ArmouryData[lid][Interior])
        {
            return lid;
        }
    }
    return -1;
}

GetPlayerNearestFGarage(playerid)
{
    foreach(new lid : FGarages)
    {
        if(IsPlayerInRangeOfPoint(playerid, 3.0, FactGarageData[lid][Pos][0], FactGarageData[lid][Pos][1], FactGarageData[lid][Pos][2]) && GetPlayerVirtualWorld(playerid) == FactGarageData[lid][World] && GetPlayerInterior(playerid) == FactGarageData[lid][Interior] && AccountData[playerid][pFaction] == FactGarageData[lid][Type])
        {
            return lid;
        }
    }
    return -1;
}

GetPlayerNearestFGaragePos(playerid)
{
    foreach(new lid : FGarages)
    {
        if(IsPlayerInRangeOfPoint(playerid, 3.0, FactGarageData[lid][Pos][0], FactGarageData[lid][Pos][1], FactGarageData[lid][Pos][2]) && GetPlayerVirtualWorld(playerid) == FactGarageData[lid][World] && GetPlayerInterior(playerid) == FactGarageData[lid][Interior])
        {
            return lid;
        }
    }
    return -1;
}