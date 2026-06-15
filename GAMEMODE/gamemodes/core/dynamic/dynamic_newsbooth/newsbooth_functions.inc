#include <YSI_Coding\y_hooks>

#define MAX_NEWSSTANDS (100)

enum newsstandData {
	Float:Pos[6],
	Interior,
	World,

    //not save
	STREAMER_TAG_3D_TEXT_LABEL:Label,
	STREAMER_TAG_OBJECT:Object
};
new NewsStandData[MAX_NEWSSTANDS][newsstandData],
    Iterator:NewsBooths<MAX_NEWSSTANDS>;

forward LoadNewsStands();
public LoadNewsStands()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
 		new id;
		for(new i; i < rows; i++)
		{
            cache_get_value_name_int(i, "id", id);
            cache_get_value_name_float(i, "X", NewsStandData[id][Pos][0]);
            cache_get_value_name_float(i, "Y", NewsStandData[id][Pos][1]);
            cache_get_value_name_float(i, "Z", NewsStandData[id][Pos][2]);
            cache_get_value_name_float(i, "Rx", NewsStandData[id][Pos][3]);
            cache_get_value_name_float(i, "Ry", NewsStandData[id][Pos][4]);
            cache_get_value_name_float(i, "Rz", NewsStandData[id][Pos][5]);
            cache_get_value_name_int(i, "Interior", NewsStandData[id][Interior]);
            cache_get_value_name_int(i, "World", NewsStandData[id][World]);
            
			NewsStand_Rebuild(id);
			Iter_Add(NewsBooths, id);
        }
        printf("[Dynamic Newspaper Stand] Jumlah total Newspaper Stand yang dimuat: %d.", rows);
	}
	return 1;
}

hook OnPlayerEditDynObject(playerid, STREAMER_TAG_OBJECT: objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if(AccountData[playerid][EditingNewsStandID] != -1 && Iter_Contains(NewsBooths, AccountData[playerid][EditingNewsStandID]))
	{
		if(response == EDIT_RESPONSE_FINAL)
	    {
	        new edgid = AccountData[playerid][EditingNewsStandID];
	        NewsStandData[edgid][Pos][0] = x;
	        NewsStandData[edgid][Pos][1] = y;
	        NewsStandData[edgid][Pos][2] = z;
	        NewsStandData[edgid][Pos][3] = rx;
	        NewsStandData[edgid][Pos][4] = ry;
	        NewsStandData[edgid][Pos][5] = rz;

			SetDynamicObjectPos(objectid, NewsStandData[edgid][Pos][0], NewsStandData[edgid][Pos][1], NewsStandData[edgid][Pos][2]);
	        SetDynamicObjectRot(objectid, NewsStandData[edgid][Pos][3], NewsStandData[edgid][Pos][4], NewsStandData[edgid][Pos][5]);

			Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, NewsStandData[edgid][Label], NewsStandData[edgid][Pos][0], NewsStandData[edgid][Pos][1], NewsStandData[edgid][Pos][2]+0.85);
			
		    NewsStand_Save(edgid);
	        AccountData[playerid][EditingNewsStandID] = -1;
	    }

	    else if(response == EDIT_RESPONSE_CANCEL)
	    {
	        new edgid = AccountData[playerid][EditingNewsStandID];
	        SetDynamicObjectPos(objectid, NewsStandData[edgid][Pos][0], NewsStandData[edgid][Pos][1], NewsStandData[edgid][Pos][2]);
	        SetDynamicObjectRot(objectid, NewsStandData[edgid][Pos][3], NewsStandData[edgid][Pos][4], NewsStandData[edgid][Pos][5]);
	        AccountData[playerid][EditingNewsStandID] = -1;
	    }
	}
	return 0;
}

forward OnNewsStandCreated(playerid, nwsbtid);
public OnNewsStandCreated(playerid, nwsbtid)
{
	NewsStand_Save(nwsbtid);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s membuat News Stand dengan ID: %d.", AccountData[playerid][pAdminname], nwsbtid);
	return 1;
}

NewsStand_BeingEdited(id)
{
	if(!Iter_Contains(NewsBooths, id)) return 0;
	foreach(new i : Player) if(AccountData[i][EditingNewsStandID] == id) return 1;
	return 0;
}

NewsStand_Nearest(playerid)
{
    foreach(new i : NewsBooths) if (IsPlayerInRangeOfPoint(playerid, 2.0, NewsStandData[i][Pos][0], NewsStandData[i][Pos][1], NewsStandData[i][Pos][2]))
	{
		if (GetPlayerInterior(playerid) == NewsStandData[i][Interior] && GetPlayerVirtualWorld(playerid) == NewsStandData[i][World])
			return i;
	}
	return -1;
}

NewsStand_Rebuild(id)
{
	if (id != -1)
	{
	    if (DestroyDynamic3DTextLabel(NewsStandData[id][Label]))
	       	NewsStandData[id][Label] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

		if (DestroyDynamicObject(NewsStandData[id][Object]))
		    NewsStandData[id][Object] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

		NewsStandData[id][Label] = CreateDynamic3DTextLabel("[Kotak Koran]\n"WHITE"Gunakan "YELLOW"'/read' "WHITE"untuk membaca koran!\nHarga: "GREEN"$25.75", 0xc0c0c8A6, NewsStandData[id][Pos][0], NewsStandData[id][Pos][1], NewsStandData[id][Pos][2]+0.85, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, NewsStandData[id][World], NewsStandData[id][Interior], -1, 10.0, -1, 0);
		NewsStandData[id][Object] = CreateDynamicObject(1285, NewsStandData[id][Pos][0], NewsStandData[id][Pos][1], NewsStandData[id][Pos][2], NewsStandData[id][Pos][3], NewsStandData[id][Pos][4], NewsStandData[id][Pos][5], NewsStandData[id][World], NewsStandData[id][Interior], -1, 100.0, 100.0);
    }
	return 1;
}

NewsStand_Save(id)
{
	new
	    query[512];
        
	format(query, sizeof(query), "UPDATE `newsstands` SET X = '%f', Y = '%f', Z = '%f', Rx = '%f', Ry = '%f', Rz = '%f', Interior = %d, World = %d WHERE id = %d",
        NewsStandData[id][Pos][0],
        NewsStandData[id][Pos][1],
        NewsStandData[id][Pos][2],
        NewsStandData[id][Pos][3],
        NewsStandData[id][Pos][4],
        NewsStandData[id][Pos][5],
        NewsStandData[id][Interior],
        NewsStandData[id][World],
        id
	);
	return mysql_pquery(g_SQL, query);
}