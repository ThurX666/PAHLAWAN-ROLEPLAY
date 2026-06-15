#include <YSI_Coding\y_hooks>

#define MAX_ROADSIGN 1000

new ObjRSign = mS_INVALID_LISTID;

enum    E_ROADSIGN
{
	// loaded from db
    rsignObjID,
	Float: rsignX,
	Float: rsignY,
	Float: rsignZ,
	Float: rsignRX,
	Float: rsignRY,
	Float: rsignRZ,
	rsignInt,
	rsignWorld,
    //temp
	STREAMER_TAG_OBJECT:rsignObject
}

new RoadsignData[MAX_ROADSIGN][E_ROADSIGN],
    Iterator:RSigns<MAX_ROADSIGN>;
	

RSign_Nearest(playerid)
{
	foreach(new i : RSigns)
	{
		if (IsPlayerInRangeOfPoint(playerid, 3.0, RoadsignData[i][rsignX], RoadsignData[i][rsignY], RoadsignData[i][rsignZ]))
		{
			if (GetPlayerInterior(playerid) == RoadsignData[i][rsignInt] && GetPlayerVirtualWorld(playerid) == RoadsignData[i][rsignWorld])
				return i;
		}
	}
	return -1;
}

forward LoadRSign();
public LoadRSign()
{
	new rows = cache_num_rows();
 	if(rows)
  	{
 		new id;
		for(new i; i < rows; i++)
		{
		    cache_get_value_name_int(i, "id", id);
            cache_get_value_name_int(i, "objid", RoadsignData[id][rsignObjID]);
			cache_get_value_name_float(i, "posx", RoadsignData[id][rsignX]);
			cache_get_value_name_float(i, "posy", RoadsignData[id][rsignY]);
			cache_get_value_name_float(i, "posz", RoadsignData[id][rsignZ]);
			cache_get_value_name_float(i, "posrx", RoadsignData[id][rsignRX]);
			cache_get_value_name_float(i, "posry", RoadsignData[id][rsignRY]);
			cache_get_value_name_float(i, "posrz", RoadsignData[id][rsignRZ]);
			cache_get_value_name_int(i, "interior", RoadsignData[id][rsignInt]);
			cache_get_value_name_int(i, "world", RoadsignData[id][rsignWorld]);

			if(DestroyDynamicObject(RoadsignData[id][rsignObject]))
				RoadsignData[id][rsignObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

			RoadsignData[id][rsignObject] = CreateDynamicObject(RoadsignData[id][rsignObjID], RoadsignData[id][rsignX], RoadsignData[id][rsignY], RoadsignData[id][rsignZ], RoadsignData[id][rsignRX], RoadsignData[id][rsignRY], RoadsignData[id][rsignRZ], RoadsignData[id][rsignWorld], RoadsignData[id][rsignInt], -1, 200.0, 200.0);
			Iter_Add(RSigns, id);
		}
		printf("[Dynamic Roadsigns] Total dynamic road sign loaded: %d.", rows);
	}
}

RSign_Save(id)
{
	new cQuery[512];
	format(cQuery, sizeof(cQuery), "UPDATE `roadsigns` SET `objid`=%d, `posx`='%f', `posy`='%f', `posz`='%f', `posrx`='%f', `posry`='%f', `posrz`='%f', `interior`=%d, `world`=%d WHERE `id`=%d",
	RoadsignData[id][rsignObjID],
    RoadsignData[id][rsignX],
	RoadsignData[id][rsignY],
	RoadsignData[id][rsignZ],
	RoadsignData[id][rsignRX],
	RoadsignData[id][rsignRY],
	RoadsignData[id][rsignRZ],
	RoadsignData[id][rsignInt],
	RoadsignData[id][rsignWorld],
	id
	);
	return mysql_pquery(g_SQL, cQuery);
}

RSign_BeingEdited(id)
{
	if(!Iter_Contains(RSigns, id)) return 0;
	foreach(new i : Player) if(AccountData[i][EditingRSignID] == id) return 1;
	return 0;
}

hook OnPlayerModelSelection(playerid, response, listid, modelid)
{
	if(listid == ObjRSign)
    {
		if(response)
		{
			if(AccountData[playerid][pAdmin] < 9)
				return PermissionError(playerid);

			new Float: x, Float: y, Float: z, id = Iter_Free(RSigns), query[512];

			if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah maksimum road sign telah tercapai!");
			
			GetPlayerPos(playerid, x, y, z);
			/*GetPlayerFacingAngle(playerid, a);
			x += (3.0 * floatsin(-a, degrees));
			y += (3.0 * floatcos(-a, degrees));
			z -= 1.0;*/
			
			RoadsignData[id][rsignObjID] = modelid;
			RoadsignData[id][rsignX] = x;
			RoadsignData[id][rsignY] = y;
			RoadsignData[id][rsignZ] = z;
			RoadsignData[id][rsignRX] = RoadsignData[id][rsignRY] = RoadsignData[id][rsignRZ] = 0.0;
			RoadsignData[id][rsignInt] = GetPlayerInterior(playerid);
			RoadsignData[id][rsignWorld] = GetPlayerVirtualWorld(playerid);

			RoadsignData[id][rsignObject] = CreateDynamicObject(RoadsignData[id][rsignObjID], RoadsignData[id][rsignX], RoadsignData[id][rsignY], RoadsignData[id][rsignZ], RoadsignData[id][rsignRX], RoadsignData[id][rsignRY], RoadsignData[id][rsignRZ], RoadsignData[id][rsignWorld], RoadsignData[id][rsignInt], -1, 200.0, 200.0);
			Iter_Add(RSigns, id);
			
			mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `roadsigns` (`id`, `objid`, `posx`, `posy`, `posz`, `posrx`, `posry`, `posrz`, `interior`, `world`) VALUES (%d, %d, '%f', '%f', '%f', '%f', '%f', '%f', %d, %d)", id, RoadsignData[id][rsignObjID], RoadsignData[id][rsignX], RoadsignData[id][rsignY], RoadsignData[id][rsignZ], RoadsignData[id][rsignRX], RoadsignData[id][rsignRY], RoadsignData[id][rsignRZ], GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
			mysql_pquery(g_SQL, query, "OnRSignCreated", "ii", playerid, id);
		}
		else return SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"You've cancelled the selection!");
	}
	return 1;
}

hook OnPlayerEditDynObject(playerid, STREAMER_TAG_OBJECT: objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if(AccountData[playerid][EditingRSignID] != -1 && Iter_Contains(RSigns, AccountData[playerid][EditingRSignID]))
	{
		if(response == EDIT_RESPONSE_FINAL)
	    {
	        new etid = AccountData[playerid][EditingRSignID];
	        RoadsignData[etid][rsignX] = x;
	        RoadsignData[etid][rsignY] = y;
	        RoadsignData[etid][rsignZ] = z;
	        RoadsignData[etid][rsignRX] = rx;
	        RoadsignData[etid][rsignRY] = ry;
	        RoadsignData[etid][rsignRZ] = rz;

	        SetDynamicObjectPos(objectid, RoadsignData[etid][rsignX], RoadsignData[etid][rsignY], RoadsignData[etid][rsignZ]);
	        SetDynamicObjectRot(objectid, RoadsignData[etid][rsignRX], RoadsignData[etid][rsignRY], RoadsignData[etid][rsignRZ]);

		    RSign_Save(etid);
	        AccountData[playerid][EditingRSignID] = -1;
	    }

	    if(response == EDIT_RESPONSE_CANCEL)
	    {
	        new etid = AccountData[playerid][EditingRSignID];
	        SetDynamicObjectPos(objectid, RoadsignData[etid][rsignX], RoadsignData[etid][rsignY], RoadsignData[etid][rsignZ]);
	        SetDynamicObjectRot(objectid, RoadsignData[etid][rsignRX], RoadsignData[etid][rsignRY], RoadsignData[etid][rsignRZ]);
	        AccountData[playerid][EditingRSignID] = -1;
	    }
	}
	return 0;
}

forward OnRSignCreated(playerid, id);
public OnRSignCreated(playerid, id)
{
	RSign_Save(id);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has created sign ID: %d.", AccountData[playerid][pAdminname], id);
	return 1;
}