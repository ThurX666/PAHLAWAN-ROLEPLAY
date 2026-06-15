#define	MAX_DOOR	500

enum ddoor
{
	dName[128],
	dPass[32],
	dIcon,
	dLocked,
	dAdmin,
	dVip,
	dFaction,
	dFamily,
	dExtvw,
	dExtint,
	Float:dExtposX,
	Float:dExtposY,
	Float:dExtposZ,
	Float:dExtposA,
	dIntvw,
	dIntint,
	Float:dIntposX,
	Float:dIntposY,
	Float:dIntposZ,
	Float:dIntposA,

	//NotSave
	STREAMER_TAG_3D_TEXT_LABEL:dLabelext,
	STREAMER_TAG_3D_TEXT_LABEL:dLabelint,
	dPickupext,
	dPickupint,
};

new DoorData[MAX_DOOR][ddoor],
	Iterator: Doors<MAX_DOOR>;

Doors_Nearest(playerid)
{
	foreach(new i : Doors) if (IsPlayerInRangeOfPoint(playerid, 3.0, DoorData[i][dExtposX], DoorData[i][dExtposY], DoorData[i][dExtposZ]))
	{
		if (GetPlayerInterior(playerid) == DoorData[i][dExtint] && GetPlayerVirtualWorld(playerid) == DoorData[i][dExtvw])
			return i;
	}
	return -1;
}

Doors_Save(id)
{
	new dquery[522];
	mysql_format(g_SQL, dquery, sizeof(dquery), "UPDATE `doors` SET `name`='%e', `password`='%e', `icon`='%d', `locked`='%d', `admin`='%d', `vip`='%d', `faction`='%d', `family`='%d', `extvw`='%d', `extint`='%d', `extposx`='%f', `extposy`='%f', `extposz`='%f', `extposa`='%f', `intvw`='%d', `intint`='%d', `intposx`='%f', `intposy`='%f', `intposz`='%f', `intposa`='%f' WHERE `ID`='%d'",
	DoorData[id][dName], DoorData[id][dPass], DoorData[id][dIcon], DoorData[id][dLocked], DoorData[id][dAdmin], DoorData[id][dVip], DoorData[id][dFaction], DoorData[id][dFamily], DoorData[id][dExtvw], DoorData[id][dExtint], DoorData[id][dExtposX], DoorData[id][dExtposY], DoorData[id][dExtposZ], DoorData[id][dExtposA], DoorData[id][dIntvw], DoorData[id][dIntint],
	DoorData[id][dIntposX], DoorData[id][dIntposY], DoorData[id][dIntposZ], DoorData[id][dIntposA], id);
	mysql_pquery(g_SQL, dquery);
	return 1;
}

Doors_Rebuild(id)
{
	if(id != -1)
	{
		new mstr[512];
		format(mstr,sizeof(mstr),"[ "WHITE"(F) "YELLOW"%s "GREEN"]", DoorData[id][dName]);
		DoorData[id][dPickupext] = CreateDynamicPickup(DoorData[id][dIcon], 23, DoorData[id][dExtposX], DoorData[id][dExtposY], DoorData[id][dExtposZ]+0.30, DoorData[id][dExtvw], DoorData[id][dExtint], -1, 30.0, -1, 0);
		DoorData[id][dLabelext] = CreateDynamic3DTextLabel(mstr, Y_GREEN, DoorData[id][dExtposX], DoorData[id][dExtposY], DoorData[id][dExtposZ]+0.85, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, DoorData[id][dExtvw], DoorData[id][dExtint], -1, 10.0, -1, 0);

		new dintstr[512];
		format(dintstr,sizeof(dintstr),"[ "WHITE"(F) "YELLOW"%s "GREEN"]", DoorData[id][dName]);
		DoorData[id][dPickupint] = CreateDynamicPickup(DoorData[id][dIcon], 23, DoorData[id][dIntposX], DoorData[id][dIntposY], DoorData[id][dIntposZ]+0.30, DoorData[id][dIntvw], DoorData[id][dIntint], -1, 30.0, -1, 0);
		DoorData[id][dLabelint] = CreateDynamic3DTextLabel(dintstr, Y_GREEN, DoorData[id][dIntposX], DoorData[id][dIntposY], DoorData[id][dIntposZ]+0.85, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, DoorData[id][dIntvw], DoorData[id][dIntint], -1, 10.0, -1, 0);
	}
}

Doors_Refresh(id)
{
	if(id != -1)
	{
		Streamer_SetItemPos(STREAMER_TYPE_PICKUP, DoorData[id][dPickupext], DoorData[id][dExtposX], DoorData[id][dExtposY], DoorData[id][dExtposZ]+0.30);
		Streamer_SetIntData(STREAMER_TYPE_PICKUP, DoorData[id][dPickupext], E_STREAMER_WORLD_ID, DoorData[id][dExtvw]);
		Streamer_SetIntData(STREAMER_TYPE_PICKUP, DoorData[id][dPickupext], E_STREAMER_INTERIOR_ID, DoorData[id][dExtint]);

		Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, DoorData[id][dLabelext], DoorData[id][dExtposX], DoorData[id][dExtposY], DoorData[id][dExtposZ]+0.85);
		Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, DoorData[id][dLabelext], E_STREAMER_WORLD_ID, DoorData[id][dExtvw]);
		Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, DoorData[id][dLabelext], E_STREAMER_INTERIOR_ID, DoorData[id][dExtint]);
		new upddoort[512];
		format(upddoort,sizeof(upddoort),"[ "WHITE"(F) "YELLOW"%s "GREEN"]", DoorData[id][dName]);
		UpdateDynamic3DTextLabelText(DoorData[id][dLabelext], Y_GREEN, upddoort);


		Streamer_SetItemPos(STREAMER_TYPE_PICKUP, DoorData[id][dPickupint], DoorData[id][dIntposX], DoorData[id][dIntposY], DoorData[id][dIntposZ]+0.30);
		Streamer_SetIntData(STREAMER_TYPE_PICKUP, DoorData[id][dPickupint], E_STREAMER_WORLD_ID, DoorData[id][dIntvw]);
		Streamer_SetIntData(STREAMER_TYPE_PICKUP, DoorData[id][dPickupint], E_STREAMER_INTERIOR_ID, DoorData[id][dIntint]);

		Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, DoorData[id][dLabelint], DoorData[id][dIntposX], DoorData[id][dIntposY], DoorData[id][dIntposZ]+0.85);
		Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, DoorData[id][dLabelint], E_STREAMER_WORLD_ID, DoorData[id][dIntvw]);
		Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, DoorData[id][dLabelint], E_STREAMER_INTERIOR_ID, DoorData[id][dIntint]);
		new updrints[512];
		format(updrints,sizeof(updrints),"[ "WHITE"(F) "YELLOW"%s "GREEN"]", DoorData[id][dName]);
		UpdateDynamic3DTextLabelText(DoorData[id][dLabelint], Y_GREEN, updrints);

		Streamer_SetIntData(STREAMER_TYPE_PICKUP, DoorData[id][dPickupext], E_STREAMER_MODEL_ID, DoorData[id][dIcon]);
		Streamer_SetIntData(STREAMER_TYPE_PICKUP, DoorData[id][dPickupint], E_STREAMER_MODEL_ID, DoorData[id][dIcon]);
	}
}

forward OnDoorsCreated(playerid, id);
public OnDoorsCreated(playerid, id)
{
	Doors_Save(id);

    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s membuat Doors dengan ID: %d.", AccountData[playerid][pAdminname], id);
	return 1;
}

forward LoadDoors();
public LoadDoors()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
   		new did, name[128], password[128];
		for(new i; i < rows; i++)
		{
  			cache_get_value_name_int(i, "ID", did);
	    	cache_get_value_name(i, "name", name);
			strcopy(DoorData[did][dName], name);
		    cache_get_value_name(i, "password", password);
			strcopy(DoorData[did][dPass], password);
		    cache_get_value_name_int(i, "icon", DoorData[did][dIcon]);
		    cache_get_value_name_int(i, "locked", DoorData[did][dLocked]);
		    cache_get_value_name_int(i, "admin", DoorData[did][dAdmin]);
		    cache_get_value_name_int(i, "vip", DoorData[did][dVip]);
		    cache_get_value_name_int(i, "faction", DoorData[did][dFaction]);
		    cache_get_value_name_int(i, "family", DoorData[did][dFamily]);
		    cache_get_value_name_int(i, "extvw", DoorData[did][dExtvw]);
		    cache_get_value_name_int(i, "extint", DoorData[did][dExtint]);
		    cache_get_value_name_float(i, "extposx", DoorData[did][dExtposX]);
			cache_get_value_name_float(i, "extposy", DoorData[did][dExtposY]);
			cache_get_value_name_float(i, "extposz", DoorData[did][dExtposZ]);
			cache_get_value_name_float(i, "extposa", DoorData[did][dExtposA]);
			cache_get_value_name_int(i, "intvw", DoorData[did][dIntvw]);
			cache_get_value_name_int(i, "intint", DoorData[did][dIntint]);
			cache_get_value_name_float(i, "intposx", DoorData[did][dIntposX]);
			cache_get_value_name_float(i, "intposy", DoorData[did][dIntposY]);
			cache_get_value_name_float(i, "intposz", DoorData[did][dIntposZ]);
			cache_get_value_name_float(i, "intposa", DoorData[did][dIntposA]);
			
			Doors_Rebuild(did);
			Iter_Add(Doors, did);
	    }
	    printf("[Dynamic Doors] Jumlah total Doors yang dimuat: %d.", rows);
	}
}