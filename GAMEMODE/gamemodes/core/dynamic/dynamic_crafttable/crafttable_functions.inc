#include <YSI_Coding\y_hooks>

#define MAX_CRAFTTABLES 100

enum craftTable {
	Float:Pos[6],
	Interior,
	World,
	Type,
	Family,

    //not save
	STREAMER_TAG_3D_TEXT_LABEL:Label,
	STREAMER_TAG_OBJECT:Object
};
new CrafttableData[MAX_CRAFTTABLES][craftTable],
    Iterator:CraftTables<MAX_CRAFTTABLES>;

CraftTable_BeingEdited(id)
{
	if(!Iter_Contains(CraftTables, id)) return 0;
	foreach(new i : Player) if(AccountData[i][EditingCraftTableID] == id) return 1;
	return 0;
}

Crafttable_Nearest(playerid)
{
    foreach(new i : CraftTables) if (IsPlayerInRangeOfPoint(playerid, 3.0, CrafttableData[i][Pos][0], CrafttableData[i][Pos][1], CrafttableData[i][Pos][2]))
	{
		if (GetPlayerInterior(playerid) == CrafttableData[i][Interior] && GetPlayerVirtualWorld(playerid) == CrafttableData[i][World])
			return i;
	}
	return -1;
}

Crafttable_Refresh(id)
{
	UpdateDynamic3DTextLabelText(CrafttableData[id][Label], 0xffffffff, "Gunakan "YELLOW"'/usetable' "WHITE"untuk akses table ini!");

	Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, CrafttableData[id][Label], CrafttableData[id][Pos][0], CrafttableData[id][Pos][1], CrafttableData[id][Pos][2]+1.5);
	Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, CrafttableData[id][Label], E_STREAMER_WORLD_ID, CrafttableData[id][World]);
	Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, CrafttableData[id][Label], E_STREAMER_INTERIOR_ID, CrafttableData[id][Interior]);

	SetDynamicObjectPos(CrafttableData[id][Object], CrafttableData[id][Pos][0], CrafttableData[id][Pos][1], CrafttableData[id][Pos][2]);
	SetDynamicObjectRot(CrafttableData[id][Object], CrafttableData[id][Pos][3], CrafttableData[id][Pos][4], CrafttableData[id][Pos][5]);
	Streamer_SetIntData(STREAMER_TYPE_OBJECT, CrafttableData[id][Object], E_STREAMER_WORLD_ID, CrafttableData[id][World]);
	Streamer_SetIntData(STREAMER_TYPE_OBJECT, CrafttableData[id][Object], E_STREAMER_INTERIOR_ID, CrafttableData[id][Interior]);
}

Crafttable_Rebuild(id)
{
	if(id != -1)
	{
	    if(DestroyDynamic3DTextLabel(CrafttableData[id][Label]))
	       	CrafttableData[id][Label] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

		if(DestroyDynamicObject(CrafttableData[id][Object]))
		    CrafttableData[id][Object] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

		CrafttableData[id][Label] = CreateDynamic3DTextLabel("Gunakan "YELLOW"'/usetable' "WHITE"untuk akses table ini", 0xffffffff, CrafttableData[id][Pos][0], CrafttableData[id][Pos][1], CrafttableData[id][Pos][2]+1.5, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, CrafttableData[id][World], CrafttableData[id][Interior], -1, 10.0, -1, 0);
        CrafttableData[id][Object] = CreateDynamicObject(937, CrafttableData[id][Pos][0], CrafttableData[id][Pos][1], CrafttableData[id][Pos][2], CrafttableData[id][Pos][3], CrafttableData[id][Pos][4], CrafttableData[id][Pos][5], CrafttableData[id][World], CrafttableData[id][Interior], -1, 100.00, 100.00);
    }
	return 1;
}

Crafttable_Save(id)
{
	new
	    query[512];
        
	format(query, sizeof(query), "UPDATE `crafttables` SET `X` = '%f', `Y` = '%f', `Z` = '%f', `Rx` = '%f', `Ry` = '%f', `Rz` = '%f', `Interior` = %d, `World` = %d, `Family` = %d, `Type` = %d WHERE `id` = %d",
        CrafttableData[id][Pos][0],
        CrafttableData[id][Pos][1],
        CrafttableData[id][Pos][2],
        CrafttableData[id][Pos][3],
        CrafttableData[id][Pos][4],
        CrafttableData[id][Pos][5],
        CrafttableData[id][Interior],
        CrafttableData[id][World],
        CrafttableData[id][Family],
        CrafttableData[id][Type],
        id
	);
	return mysql_pquery(g_SQL, query);
}

forward LoadCraftTables();
public LoadCraftTables()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
 		new id;
		for(new i; i < rows; i++)
		{
            cache_get_value_name_int(i, "id", id);
            cache_get_value_name_float(i, "X", CrafttableData[id][Pos][0]);
            cache_get_value_name_float(i, "Y", CrafttableData[id][Pos][1]);
            cache_get_value_name_float(i, "Z", CrafttableData[id][Pos][2]);
            cache_get_value_name_float(i, "Rx", CrafttableData[id][Pos][3]);
            cache_get_value_name_float(i, "Ry", CrafttableData[id][Pos][4]);
            cache_get_value_name_float(i, "Rz", CrafttableData[id][Pos][5]);
            cache_get_value_name_int(i, "Interior", CrafttableData[id][Interior]);
            cache_get_value_name_int(i, "World", CrafttableData[id][World]);
            cache_get_value_name_int(i, "Family", CrafttableData[id][Family]);
            cache_get_value_name_int(i, "Type", CrafttableData[id][Type]);
            
			Crafttable_Rebuild(id);
			Iter_Add(CraftTables, id);
        }
        printf("[Dynamic Craft Tables] Jumlah total Craft Table yang dimuat: %d.", rows);
	}
	return 1;
}

forward OnCraftTableAdded(playerid, id);
public OnCraftTableAdded(playerid, id)
{
	Crafttable_Save(id);
	Crafttable_Refresh(id);
	SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s membuat Craft Table dengan ID: %d.", AccountData[playerid][pAdminname], id);
	return 1;
}

hook OnPlayerEditDynObject(playerid, STREAMER_TAG_OBJECT: objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if(AccountData[playerid][EditingCraftTableID] != -1 && Iter_Contains(CraftTables, AccountData[playerid][EditingCraftTableID]))
	{
		if(response == EDIT_RESPONSE_FINAL)
	    {
	        new edgid = AccountData[playerid][EditingCraftTableID];
	        CrafttableData[edgid][Pos][0] = x;
	        CrafttableData[edgid][Pos][1] = y;
	        CrafttableData[edgid][Pos][2] = z;
	        CrafttableData[edgid][Pos][3] = rx;
	        CrafttableData[edgid][Pos][4] = ry;
	        CrafttableData[edgid][Pos][5] = rz;

			SetDynamicObjectPos(objectid, CrafttableData[edgid][Pos][0], CrafttableData[edgid][Pos][1], CrafttableData[edgid][Pos][2]);
	        SetDynamicObjectRot(objectid, CrafttableData[edgid][Pos][3], CrafttableData[edgid][Pos][4], CrafttableData[edgid][Pos][5]);

			Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, CrafttableData[edgid][Label], CrafttableData[edgid][Pos][0], CrafttableData[edgid][Pos][1], CrafttableData[edgid][Pos][2]+1.5);
			
		    Crafttable_Save(edgid);
	        AccountData[playerid][EditingCraftTableID] = -1;
	    }

	    else if(response == EDIT_RESPONSE_CANCEL)
	    {
	        new edgid = AccountData[playerid][EditingCraftTableID];
	        SetDynamicObjectPos(objectid, CrafttableData[edgid][Pos][0], CrafttableData[edgid][Pos][1], CrafttableData[edgid][Pos][2]);
	        SetDynamicObjectRot(objectid, CrafttableData[edgid][Pos][3], CrafttableData[edgid][Pos][4], CrafttableData[edgid][Pos][5]);
	        AccountData[playerid][EditingCraftTableID] = -1;
	    }
	}
	return 0;
}