#include <YSI_Coding\y_hooks>

#define	MAX_BASEMENT	500

enum bbsmt
{
	bmName[128],
	bmPass[32],
	bmIcon,
	bmLocked,
	bmAdmin,
	bmVip,
	bmFaction,
	bmFamily,
	bmExtvw,
	bmExtint,
	Float:bmExtposX,
	Float:bmExtposY,
	Float:bmExtposZ,
	Float:bmExtposA,
	bmIntvw,
	bmIntint,
	Float:bmIntposX,
	Float:bmIntposY,
	Float:bmIntposZ,
	Float:bmIntposA,

	Float:bmInexitX,
	Float:bmInexitY,
	Float:bmInexitZ,

	Float:bmOutexitX,
	Float:bmOutexitY,
	Float:bmOutexitZ,
	Float:bmOutexitA,

	//NotSave
	STREAMER_TAG_3D_TEXT_LABEL:bmLabelext,
	STREAMER_TAG_PICKUP: bmPickupext,
	STREAMER_TAG_3D_TEXT_LABEL:bmLabelexit,
	STREAMER_TAG_PICKUP: bmPickupexit,
	bmEntranceCP,
	bmExitCP
};

new BasementData[MAX_BASEMENT][bbsmt],
	Iterator: Basement<MAX_BASEMENT>;

Basement_Save(bmid)
{
	new dquery[2048];
	mysql_format(g_SQL, dquery, sizeof(dquery), "UPDATE `basement` SET `name`='%e', `password`='%e', `icon`=%d, `locked`=%d, `admin`=%d, `vip`=%d, `faction`=%d, `family`=%d, `extvw`=%d, `extint`=%d, `extposx`='%f', `extposy`='%f', `extposz`='%f', `extposa`='%f', `intvw`=%d, `intint`=%d, `intposx`='%f', `intposy`='%f', `intposz`='%f', `intposa`='%f', `inexitx`='%f', `inexity`='%f', `inexitz`='%f', `outexitx`='%f', `outexity`='%f', `outexitz`='%f', `outexita`='%f' WHERE ID=%d",
	BasementData[bmid][bmName], BasementData[bmid][bmPass], BasementData[bmid][bmIcon], BasementData[bmid][bmLocked], BasementData[bmid][bmAdmin], BasementData[bmid][bmVip], BasementData[bmid][bmFaction], BasementData[bmid][bmFamily], BasementData[bmid][bmExtvw], BasementData[bmid][bmExtint], BasementData[bmid][bmExtposX], BasementData[bmid][bmExtposY], BasementData[bmid][bmExtposZ], BasementData[bmid][bmExtposA], BasementData[bmid][bmIntvw], BasementData[bmid][bmIntint],
	BasementData[bmid][bmIntposX], BasementData[bmid][bmIntposY], BasementData[bmid][bmIntposZ], BasementData[bmid][bmIntposA], BasementData[bmid][bmInexitX], BasementData[bmid][bmInexitY], BasementData[bmid][bmInexitZ], BasementData[bmid][bmOutexitX], BasementData[bmid][bmOutexitY], BasementData[bmid][bmOutexitZ], BasementData[bmid][bmOutexitA], bmid);
	mysql_pquery(g_SQL, dquery);
	return 1;
}

Basement_Rebuild(bmid)
{
	if(bmid != -1)
	{
		new mstr[512];
		format(mstr,sizeof(mstr),"[DB:%d]\n{FFFFFF}%s", bmid, BasementData[bmid][bmName]);
		BasementData[bmid][bmPickupext] = CreateDynamicPickup(BasementData[bmid][bmIcon], 23, BasementData[bmid][bmExtposX], BasementData[bmid][bmExtposY], BasementData[bmid][bmExtposZ], BasementData[bmid][bmExtvw], BasementData[bmid][bmExtint], -1, 30.0, -1, 0);		
		BasementData[bmid][bmLabelext] = CreateDynamic3DTextLabel(mstr, Y_CYAN, BasementData[bmid][bmExtposX], BasementData[bmid][bmExtposY], BasementData[bmid][bmExtposZ]+0.80, 30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, BasementData[bmid][bmExtvw], BasementData[bmid][bmExtint], -1, 10.0, -1, 0);

    	format(mstr,sizeof(mstr),"[DB:%d]\n{FFFFFF}%s", bmid, BasementData[bmid][bmName]);
		BasementData[bmid][bmPickupexit] = CreateDynamicPickup(BasementData[bmid][bmIcon], 23, BasementData[bmid][bmInexitX], BasementData[bmid][bmInexitY], BasementData[bmid][bmInexitZ], BasementData[bmid][bmIntvw], BasementData[bmid][bmIntint], -1, 30.0, -1, 0);
		BasementData[bmid][bmLabelexit] = CreateDynamic3DTextLabel(mstr, Y_CYAN, BasementData[bmid][bmInexitX], BasementData[bmid][bmInexitY], BasementData[bmid][bmInexitZ]+0.80, 30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, BasementData[bmid][bmIntvw], BasementData[bmid][bmIntint], -1, 10.0, -1, 0);

		BasementData[bmid][bmEntranceCP] = CreateDynamicCP(BasementData[bmid][bmExtposX], BasementData[bmid][bmExtposY], BasementData[bmid][bmExtposZ], 3.0, BasementData[bmid][bmExtvw], BasementData[bmid][bmExtint], -1, 15.0, -1, 0);
		BasementData[bmid][bmExitCP] = CreateDynamicCP(BasementData[bmid][bmInexitX], BasementData[bmid][bmInexitY], BasementData[bmid][bmInexitZ], 3.0, BasementData[bmid][bmIntvw], BasementData[bmid][bmIntint], -1, 15.0, -1, 0);
	}
}

Basement_Refresh(bmid)
{
	if(bmid != -1)
	{
		Streamer_SetItemPos(STREAMER_TYPE_PICKUP, BasementData[bmid][bmPickupext], BasementData[bmid][bmExtposX], BasementData[bmid][bmExtposY], BasementData[bmid][bmExtposZ]);
		Streamer_SetIntData(STREAMER_TYPE_PICKUP, BasementData[bmid][bmPickupext], E_STREAMER_WORLD_ID, BasementData[bmid][bmExtvw]);
		Streamer_SetIntData(STREAMER_TYPE_PICKUP, BasementData[bmid][bmPickupext], E_STREAMER_INTERIOR_ID, BasementData[bmid][bmExtint]);

		Streamer_SetItemPos(STREAMER_TYPE_PICKUP, BasementData[bmid][bmPickupexit], BasementData[bmid][bmInexitX], BasementData[bmid][bmInexitY], BasementData[bmid][bmInexitZ]);
		Streamer_SetIntData(STREAMER_TYPE_PICKUP, BasementData[bmid][bmPickupexit], E_STREAMER_WORLD_ID, BasementData[bmid][bmIntvw]);
		Streamer_SetIntData(STREAMER_TYPE_PICKUP, BasementData[bmid][bmPickupexit], E_STREAMER_INTERIOR_ID, BasementData[bmid][bmIntint]);

		Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, BasementData[bmid][bmLabelext], BasementData[bmid][bmExtposX], BasementData[bmid][bmExtposY], BasementData[bmid][bmExtposZ]+0.80);
		Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, BasementData[bmid][bmLabelext], E_STREAMER_WORLD_ID, BasementData[bmid][bmExtvw]);
		Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, BasementData[bmid][bmLabelext], E_STREAMER_INTERIOR_ID, BasementData[bmid][bmExtint]);

		new updtbmtext[512];
		format(updtbmtext,sizeof(updtbmtext),"[DB:%d]\n{FFFFFF}%s", bmid, BasementData[bmid][bmName]);
		UpdateDynamic3DTextLabelText(BasementData[bmid][bmLabelext], Y_CYAN, updtbmtext);

		Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, BasementData[bmid][bmLabelexit], BasementData[bmid][bmInexitX], BasementData[bmid][bmInexitY], BasementData[bmid][bmInexitZ]+0.80);
		Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, BasementData[bmid][bmLabelexit], E_STREAMER_WORLD_ID, BasementData[bmid][bmIntvw]);
		Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, BasementData[bmid][bmLabelexit], E_STREAMER_INTERIOR_ID, BasementData[bmid][bmIntint]);
		
		new updexitbmt[512];
		format(updexitbmt,sizeof(updexitbmt),"[DB:%d]\n{FFFFFF}%s", bmid, BasementData[bmid][bmName]);
		UpdateDynamic3DTextLabelText(BasementData[bmid][bmLabelexit], Y_CYAN, updexitbmt);

		Streamer_SetIntData(STREAMER_TYPE_PICKUP, BasementData[bmid][bmPickupext], E_STREAMER_MODEL_ID, BasementData[bmid][bmIcon]);
		Streamer_SetIntData(STREAMER_TYPE_PICKUP, BasementData[bmid][bmPickupexit], E_STREAMER_MODEL_ID, BasementData[bmid][bmIcon]);
	}
}

hook OnPlayerEnterDynamicCP(playerid, checkpointid)
{
	foreach(new bmid : Basement)
    {
        if(checkpointid == BasementData[bmid][bmEntranceCP])
        {
            if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
            {
                GameTextForPlayer(playerid, "~p~Basement~n~~w~Gunakan ~y~~k~~VEHICLE_HORN~~n~~w~Untuk Masuk", 3000, 4);
            }
            else
            {
                GameTextForPlayer(playerid, "~p~Basement~n~~w~Gunakan ~y~~k~~VEHICLE_ENTER_EXIT~~n~~w~Untuk Masuk", 3000, 4);
            }
        }
        else if(checkpointid == BasementData[bmid][bmExitCP])
        {
            if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
            {
                GameTextForPlayer(playerid, "~p~Basement~n~~w~Gunakan ~y~~k~~VEHICLE_HORN~~n~~w~Untuk Masuk", 3000, 4);
            }
            else
            {
                GameTextForPlayer(playerid, "~p~Basement~n~~w~Gunakan ~y~~k~~VEHICLE_ENTER_EXIT~~n~~w~Untuk Masuk", 3000, 4);
            }
        }
    }
	return 1;
}

forward OnBasementCreated(bmid);
public OnBasementCreated(bmid)
{
	Basement_Save(bmid);
	return 1;
}

forward LoadBasement();
public LoadBasement()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
   		new bmid;

		for(new i; i < rows; i++)
		{
  			cache_get_value_name_int(i, "ID", bmid);
	    	cache_get_value_name(i, "name", BasementData[bmid][bmName]);
		    cache_get_value_name(i, "password", BasementData[bmid][bmPass]);

		    cache_get_value_name_int(i, "icon", BasementData[bmid][bmIcon]);
		    cache_get_value_name_int(i, "locked", BasementData[bmid][bmLocked]);
		    cache_get_value_name_int(i, "admin", BasementData[bmid][bmAdmin]);
		    cache_get_value_name_int(i, "vip", BasementData[bmid][bmVip]);
		    cache_get_value_name_int(i, "faction", BasementData[bmid][bmFaction]);
		    cache_get_value_name_int(i, "family", BasementData[bmid][bmFamily]);
		    cache_get_value_name_int(i, "extvw", BasementData[bmid][bmExtvw]);
		    cache_get_value_name_int(i, "extint", BasementData[bmid][bmExtint]);
		    cache_get_value_name_float(i, "extposx", BasementData[bmid][bmExtposX]);
			cache_get_value_name_float(i, "extposy", BasementData[bmid][bmExtposY]);
			cache_get_value_name_float(i, "extposz", BasementData[bmid][bmExtposZ]);
			cache_get_value_name_float(i, "extposa", BasementData[bmid][bmExtposA]);
			cache_get_value_name_int(i, "intvw", BasementData[bmid][bmIntvw]);
			cache_get_value_name_int(i, "intint", BasementData[bmid][bmIntint]);
			cache_get_value_name_float(i, "intposx", BasementData[bmid][bmIntposX]);
			cache_get_value_name_float(i, "intposy", BasementData[bmid][bmIntposY]);
			cache_get_value_name_float(i, "intposz", BasementData[bmid][bmIntposZ]);
			cache_get_value_name_float(i, "intposa", BasementData[bmid][bmIntposA]);

			cache_get_value_name_float(i, "inexitx", BasementData[bmid][bmInexitX]);
			cache_get_value_name_float(i, "inexity", BasementData[bmid][bmInexitY]);
			cache_get_value_name_float(i, "inexitz", BasementData[bmid][bmInexitZ]);

			cache_get_value_name_float(i, "outexitx", BasementData[bmid][bmOutexitX]);
			cache_get_value_name_float(i, "outexity", BasementData[bmid][bmOutexitY]);
			cache_get_value_name_float(i, "outexitz", BasementData[bmid][bmOutexitZ]);
			cache_get_value_name_float(i, "outexita", BasementData[bmid][bmOutexitA]);
			
			Iter_Add(Basement, bmid);
			Basement_Rebuild(bmid);
			Basement_Refresh(bmid);
	    }
	    printf("[Dynamic Basement] Jumlah total basement yang dimuat: %d.", rows);
	}
}