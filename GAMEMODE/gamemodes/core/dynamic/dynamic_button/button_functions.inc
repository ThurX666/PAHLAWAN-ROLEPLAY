#include <YSI_Coding\y_hooks>

#define MAX_BUTTONS 500

enum E_BUTTON
{
	bDoorModel,
	bFaction,
	bFamily,
	Float:bSpeed,

    //posisi button / tombol
	Float:bPosX,
	Float:bPosY,
	Float:bPosZ,

	Float:bPosRX,
	Float:bPosRY,
	Float:bPosRZ,

    //posisi pintu / move door
	Float:bDoorPosX,
	Float:bDoorPosY,
	Float:bDoorPosZ,
	Float:bDoorPosRX,
	Float:bDoorPosRY,
	Float:bDoorPosRZ,

    Float:bDoorOpenX,
    Float:bDoorOpenY,
    Float:bDoorOpenZ,
    Float:bDoorOpenRX,
    Float:bDoorOpenRY,
    Float:bDoorOpenRZ,

    bWorld,
    bInterior,
	bDoorStatus,
    STREAMER_TAG_OBJECT:bObject,
    STREAMER_TAG_OBJECT:bDoorObject
}
new ButtonData[MAX_BUTTONS][E_BUTTON],
	Iterator: Buttons<MAX_BUTTONS>;

new Float:bDoorEditX[MAX_PLAYERS],
	Float:bDoorEditY[MAX_PLAYERS],
	Float:bDoorEditZ[MAX_PLAYERS],
	Float:bDoorEditRX[MAX_PLAYERS],
	Float:bDoorEditRY[MAX_PLAYERS],
	Float:bDoorEditRZ[MAX_PLAYERS];

Button_Nearest(playerid)
{
    foreach(new i : Buttons) if (IsPlayerInRangeOfPoint(playerid, 3.0, ButtonData[i][bPosX], ButtonData[i][bPosY], ButtonData[i][bPosZ]))
	{
		if (GetPlayerInterior(playerid) == ButtonData[i][bInterior] && GetPlayerVirtualWorld(playerid) == ButtonData[i][bWorld])
			return i;
	}
	return -1;
}

Button_Save(id)
{
	new dquery[2048];
	mysql_format(g_SQL, dquery, sizeof(dquery), "UPDATE `buttons` SET `doormodel`=%d, `faction`=%d, `family`=%d, `speed`='%f', `bposx`='%f', `bposy`='%f', `bposz`='%f', `bposrx`='%f', `bposry`='%f', `bposrz`='%f', `doorposx`='%f', `doorposy`='%f', `doorposz`='%f', `doorposrx`='%f', `doorposry`='%f', `doorposrz`='%f', `dopenx`='%f', `dopeny`='%f', `dopenz`='%f', `dopenrx`='%f', `dopenry`='%f', `dopenrz`='%f', `world`=%d, `interior`=%d WHERE `ID`=%d",
	ButtonData[id][bDoorModel], ButtonData[id][bFaction], ButtonData[id][bFamily], ButtonData[id][bSpeed], ButtonData[id][bPosX], ButtonData[id][bPosY], ButtonData[id][bPosZ], ButtonData[id][bPosRX], ButtonData[id][bPosRY], ButtonData[id][bPosRZ], ButtonData[id][bDoorPosX], ButtonData[id][bDoorPosY], ButtonData[id][bDoorPosZ], ButtonData[id][bDoorPosRX], ButtonData[id][bDoorPosRY], ButtonData[id][bDoorPosRZ], 
    ButtonData[id][bDoorOpenX], ButtonData[id][bDoorOpenY], ButtonData[id][bDoorOpenZ], ButtonData[id][bDoorOpenRX], ButtonData[id][bDoorOpenRY], ButtonData[id][bDoorOpenRZ], ButtonData[id][bWorld], ButtonData[id][bInterior], id);
	mysql_pquery(g_SQL, dquery);
	return 1;
}

forward LoadButtons();
public LoadButtons()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
   		new id;
		for(new i; i < rows; i++)
		{
  			cache_get_value_name_int(i, "ID", id);
	    	cache_get_value_name_int(i, "doormodel", ButtonData[id][bDoorModel]);
		    cache_get_value_name_int(i, "faction", ButtonData[id][bFaction]);
		    cache_get_value_name_int(i, "family", ButtonData[id][bFamily]);
		    cache_get_value_name_float(i, "speed", ButtonData[id][bSpeed]);
		    cache_get_value_name_float(i, "bposx", ButtonData[id][bPosX]);
			cache_get_value_name_float(i, "bposy", ButtonData[id][bPosY]);
			cache_get_value_name_float(i, "bposz", ButtonData[id][bPosZ]);
			cache_get_value_name_float(i, "bposrx", ButtonData[id][bPosRX]);
			cache_get_value_name_float(i, "bposry", ButtonData[id][bPosRY]);
			cache_get_value_name_float(i, "bposrz", ButtonData[id][bPosRZ]);
            cache_get_value_name_float(i, "doorposx", ButtonData[id][bDoorPosX]);
            cache_get_value_name_float(i, "doorposy", ButtonData[id][bDoorPosY]);
            cache_get_value_name_float(i, "doorposz", ButtonData[id][bDoorPosZ]);
            cache_get_value_name_float(i, "doorposrx", ButtonData[id][bDoorPosRX]);
            cache_get_value_name_float(i, "doorposry", ButtonData[id][bDoorPosRY]);
            cache_get_value_name_float(i, "doorposrz", ButtonData[id][bDoorPosRZ]);
			cache_get_value_name_float(i, "dopenx", ButtonData[id][bDoorOpenX]);
			cache_get_value_name_float(i, "dopeny", ButtonData[id][bDoorOpenY]);
			cache_get_value_name_float(i, "dopenz", ButtonData[id][bDoorOpenZ]);
			cache_get_value_name_float(i, "dopenrx", ButtonData[id][bDoorOpenRX]);
			cache_get_value_name_float(i, "dopenry", ButtonData[id][bDoorOpenRY]);
			cache_get_value_name_float(i, "dopenrz", ButtonData[id][bDoorOpenRZ]);
            cache_get_value_name_int(i, "world", ButtonData[id][bWorld]);
            cache_get_value_name_int(i, "interior", ButtonData[id][bInterior]);

			if(DestroyDynamicObject(ButtonData[id][bDoorObject]))
            	ButtonData[id][bDoorObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

        	if(DestroyDynamicObject(ButtonData[id][bObject]))
           	 	ButtonData[id][bObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

            ButtonData[id][bObject] = CreateDynamicObject(2886, ButtonData[id][bPosX], ButtonData[id][bPosY], ButtonData[id][bPosZ], ButtonData[id][bPosRX], ButtonData[id][bPosRY], ButtonData[id][bPosRZ], ButtonData[id][bWorld], ButtonData[id][bInterior], -1, 30.0, 30.0);
			ButtonData[id][bDoorObject] = CreateDynamicObject(ButtonData[id][bDoorModel], ButtonData[id][bDoorPosX], ButtonData[id][bDoorPosY], ButtonData[id][bDoorPosZ], ButtonData[id][bDoorPosRX], ButtonData[id][bDoorPosRY], ButtonData[id][bDoorPosRZ], ButtonData[id][bWorld], ButtonData[id][bInterior], -1, 100.0, 100.0);
			ButtonData[id][bDoorStatus] = 0;

			Iter_Add(Buttons, id);
	    }
	    printf("[Dynamic Buttons] Jumlah total buttons yang dimuat: %d.", rows);
	}
	return 1;
}

forward OnButtonCreated(playerid, id);
public OnButtonCreated(playerid, id)
{
	Button_Save(id);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s membuat button ID: %d.", AccountData[playerid][pAdminname], id);
	return 1;
}

hook OnPlayerEditDynObject(playerid, STREAMER_TAG_OBJECT: objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if(AccountData[playerid][EditingButtonID] != -1 && Iter_Contains(Buttons, AccountData[playerid][EditingButtonID]))
	{
		new id = AccountData[playerid][EditingButtonID];
        if(response == EDIT_RESPONSE_FINAL)
		{
			SetDynamicObjectPos(objectid, x, y, z);
			SetDynamicObjectRot(objectid, rx, ry, rz);
			if(AccountData[playerid][EditingButton] == 1)
			{
				ButtonData[id][bDoorPosX] = x;
				ButtonData[id][bDoorPosY] = y;
				ButtonData[id][bDoorPosZ] = z;
				ButtonData[id][bDoorPosRX] = rx;
				ButtonData[id][bDoorPosRY] = ry;
				ButtonData[id][bDoorPosRZ] = rz;
				
				AccountData[playerid][EditingButtonID] = -1;
				AccountData[playerid][EditingButton] = 0;
				ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah posisi tutup button.");
				ButtonData[id][bDoorStatus] = 0;
				Button_Save(id);
			}
			else if(AccountData[playerid][EditingButton] == 2)
			{
				ButtonData[id][bDoorOpenX] = x;
				ButtonData[id][bDoorOpenY] = y;
				ButtonData[id][bDoorOpenZ] = z;
				ButtonData[id][bDoorOpenRX] = rx;
				ButtonData[id][bDoorOpenRY] = ry;
				ButtonData[id][bDoorOpenRZ] = rz;
				
				AccountData[playerid][EditingButtonID] = -1;
				AccountData[playerid][EditingButton] = 0;
				ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah posisi buka button.");

				ButtonData[id][bDoorStatus] = 1;
				Button_Save(id);
			}
			else if(AccountData[playerid][EditingButton] == 3)
			{
				ButtonData[id][bPosX] = x;
				ButtonData[id][bPosY] = y;
				ButtonData[id][bPosZ] = z;
				ButtonData[id][bPosRX] = rx;
				ButtonData[id][bPosRY] = ry;
				ButtonData[id][bPosRZ] = rz;
				
				AccountData[playerid][EditingButtonID] = -1;
				AccountData[playerid][EditingButton] = 0;
				ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah posisi button.");

				ButtonData[id][bDoorStatus] = 1;
				Button_Save(id);
			}
		}

		else if(response == EDIT_RESPONSE_CANCEL)
		{
			SetDynamicObjectPos(objectid, bDoorEditX[playerid], bDoorEditY[playerid], bDoorEditZ[playerid]);
			SetDynamicObjectRot(objectid, bDoorEditRX[playerid], bDoorEditRY[playerid], bDoorEditRZ[playerid]);
			bDoorEditX[playerid] = 0; bDoorEditY[playerid] = 0; bDoorEditZ[playerid] = 0;
			bDoorEditRX[playerid] = 0; bDoorEditRY[playerid] = 0; bDoorEditRZ[playerid] = 0;
			Button_Save(id);
		}
	}
	return 0;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if((newkeys & KEY_SECONDARY_ATTACK))
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		{
			foreach(new idx : Buttons)
			{
				if(ButtonData[idx][bDoorModel] && IsPlayerInRangeOfPoint(playerid, 1.5, ButtonData[idx][bPosX], ButtonData[idx][bPosY], ButtonData[idx][bPosZ]) && GetPlayerVirtualWorld(playerid) == ButtonData[idx][bWorld] && GetPlayerInterior(playerid) == ButtonData[idx][bInterior])
				{
					if(ButtonData[idx][bFaction] != 0)
					{
                        if(ButtonData[idx][bFaction] == FACTION_FEDERAL)
                        {
                            if(AccountData[playerid][pFaction] != FACTION_LSPD && AccountData[playerid][pFaction] != FACTION_LSFD)
                                return ShowTDN(playerid, NOTIFICATION_ERROR, "Akses ditolak!");
                        }
                        else
                        {
                            if(ButtonData[idx][bFaction] != AccountData[playerid][pFaction])
							    return ShowTDN(playerid, NOTIFICATION_ERROR, "Akses ditolak!");
                        }
					}

					if(ButtonData[idx][bFamily] != -1)
					{
                        if(ButtonData[idx][bFamily] != AccountData[playerid][pFamily])
							return ShowTDN(playerid, NOTIFICATION_ERROR, "Akses ditolak!");
					}

                    if(!ButtonData[idx][bDoorStatus])
                    {
                        ApplyAnimation(playerid, "HEIST9", "Use_SwipeCard", 10.0, false, false, false, false, 0, false);
                        ButtonData[idx][bDoorStatus] = 1;
                        MoveDynamicObject(ButtonData[idx][bDoorObject], ButtonData[idx][bDoorOpenX], ButtonData[idx][bDoorOpenY], ButtonData[idx][bDoorOpenZ], ButtonData[idx][bSpeed]);
                        SetDynamicObjectRot(ButtonData[idx][bDoorObject], ButtonData[idx][bDoorOpenRX], ButtonData[idx][bDoorOpenRY], ButtonData[idx][bDoorOpenRZ]);
                    }
                    else
                    {
                        ApplyAnimation(playerid, "HEIST9", "Use_SwipeCard", 10.0, false, false, false, false, 0, false);
                        ButtonData[idx][bDoorStatus] = 0;
                        MoveDynamicObject(ButtonData[idx][bDoorObject], ButtonData[idx][bDoorPosX], ButtonData[idx][bDoorPosY], ButtonData[idx][bDoorPosZ], ButtonData[idx][bSpeed]);
                        SetDynamicObjectRot(ButtonData[idx][bDoorObject], ButtonData[idx][bDoorPosRX], ButtonData[idx][bDoorPosRY], ButtonData[idx][bDoorPosRZ]);
                    }
				}
			}
		}
	}
	return 1;
}