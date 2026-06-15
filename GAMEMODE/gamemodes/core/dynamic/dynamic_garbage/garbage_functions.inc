#include <YSI_Coding\y_hooks>

#define MAX_GARBAGE_BINS (1000)

enum garbageData {
 	garbageModel,
	Float:garbagePos[6],
	garbageInterior,
	garbageWorld,

    //not save
	STREAMER_TAG_3D_TEXT_LABEL:garbageText3D,
	STREAMER_TAG_OBJECT:garbageObject,

    bool:garbageTaken,
    garbageAvailTime
};
new GarbageData[MAX_GARBAGE_BINS][garbageData],
    Iterator:Garbages<MAX_GARBAGE_BINS>;

Garbage_BeingEdited(id)
{
	if(!Iter_Contains(Garbages, id)) return 0;
	foreach(new i : Player) if(AccountData[i][EditingGarbageID] == id) return 1;
	return 0;
}

Garbage_Nearest(playerid)
{
    foreach(new i : Garbages) if (IsPlayerInRangeOfPoint(playerid, 2.0, GarbageData[i][garbagePos][0], GarbageData[i][garbagePos][1], GarbageData[i][garbagePos][2]))
	{
		if (GetPlayerInterior(playerid) == GarbageData[i][garbageInterior] && GetPlayerVirtualWorld(playerid) == GarbageData[i][garbageWorld])
			return i;
	}
	return -1;
}

Garbage_Refresh(id)
{
	UpdateDynamic3DTextLabelText(GarbageData[id][garbageText3D], X11_CYAN, "[Tempat Sampah]\n"WHITE"Tekan "RED"'Y' "WHITE"untuk pungut sampah!\nTekan "RED"ALT "WHITE"untuk bersembunyi\nDrop item disini untuk membuangnya!");

	Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, GarbageData[id][garbageText3D], GarbageData[id][garbagePos][0], GarbageData[id][garbagePos][1], GarbageData[id][garbagePos][2]+1.5);
	Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, GarbageData[id][garbageText3D], E_STREAMER_WORLD_ID, GarbageData[id][garbageWorld]);
	Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, GarbageData[id][garbageText3D], E_STREAMER_INTERIOR_ID, GarbageData[id][garbageInterior]);

	SetDynamicObjectPos(GarbageData[id][garbageObject], GarbageData[id][garbagePos][0], GarbageData[id][garbagePos][1], GarbageData[id][garbagePos][2]);
	SetDynamicObjectRot(GarbageData[id][garbageObject], GarbageData[id][garbagePos][3], GarbageData[id][garbagePos][4], GarbageData[id][garbagePos][5]);
	Streamer_SetIntData(STREAMER_TYPE_OBJECT, GarbageData[id][garbageObject], E_STREAMER_WORLD_ID, GarbageData[id][garbageWorld]);
	Streamer_SetIntData(STREAMER_TYPE_OBJECT, GarbageData[id][garbageObject], E_STREAMER_INTERIOR_ID, GarbageData[id][garbageInterior]);
}

Garbage_Rebuild(id)
{
	if (id != -1)
	{
	    if (DestroyDynamic3DTextLabel(GarbageData[id][garbageText3D]))
	       	GarbageData[id][garbageText3D] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

		if (DestroyDynamicObject(GarbageData[id][garbageObject]))
		    GarbageData[id][garbageObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

		GarbageData[id][garbageText3D] = CreateDynamic3DTextLabel("[Tempat Sampah]\n"WHITE"Tekan "RED"'Y' "WHITE"untuk pungut sampah!\nTekan "RED"ALT "WHITE"untuk bersembunyi\nDrop item disini untuk membuangnya!", X11_CYAN, GarbageData[id][garbagePos][0], GarbageData[id][garbagePos][1], GarbageData[id][garbagePos][2]+1.5, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, GarbageData[id][garbageWorld], GarbageData[id][garbageInterior], -1, 10.0, -1, 0);
		GarbageData[id][garbageObject] = CreateDynamicObject(GarbageData[id][garbageModel], GarbageData[id][garbagePos][0], GarbageData[id][garbagePos][1], GarbageData[id][garbagePos][2], GarbageData[id][garbagePos][3], GarbageData[id][garbagePos][4], GarbageData[id][garbagePos][5], GarbageData[id][garbageWorld], GarbageData[id][garbageInterior], -1, 100.0, 100.0);

        GarbageData[id][garbageTaken] = false;
        GarbageData[id][garbageAvailTime] = 0;
    }
	return 1;
}

Garbage_Save(id)
{
	new
	    query[512];
        
	format(query, sizeof(query), "UPDATE garbages SET garbageModel = %d, garbageX = '%f', garbageY = '%f', garbageZ = '%f', garbageRx = '%f', garbageRy = '%f', garbageRz = '%f', garbageInterior = %d, garbageWorld = %d WHERE id = %d",
        GarbageData[id][garbageModel],
        GarbageData[id][garbagePos][0],
        GarbageData[id][garbagePos][1],
        GarbageData[id][garbagePos][2],
        GarbageData[id][garbagePos][3],
        GarbageData[id][garbagePos][4],
        GarbageData[id][garbagePos][5],
        GarbageData[id][garbageInterior],
        GarbageData[id][garbageWorld],
        id
	);
	return mysql_pquery(g_SQL, query);
}

/*GetClosestGarbage(playerid)
{
	new
	    Float:fDistance[2] = {99999.0, 0.0},
	    iIndex = -1
	;
	foreach (new i : Garbages) if (GarbageData[i][garbageCapacity] > 0 && GetPlayerInterior(playerid) == GarbageData[i][garbageInterior] && GetPlayerVirtualWorld(playerid) == GarbageData[i][garbageWorld])
	{
		fDistance[1] = GetPlayerDistanceFromPoint(playerid, GarbageData[i][garbagePos][0], GarbageData[i][garbagePos][1], GarbageData[i][garbagePos][2]);

		if (fDistance[1] < fDistance[0])
		{
		    fDistance[0] = fDistance[1];
		    iIndex = i;
		}
	}
	return iIndex;
}
*/

forward LoadGarbages();
public LoadGarbages()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
 		new id;
		for(new i; i < rows; i++)
		{
            cache_get_value_name_int(i, "id", id);
            cache_get_value_name_int(i, "garbageModel", GarbageData[id][garbageModel]);
            cache_get_value_name_float(i, "garbageX", GarbageData[id][garbagePos][0]);
            cache_get_value_name_float(i, "garbageY", GarbageData[id][garbagePos][1]);
            cache_get_value_name_float(i, "garbageZ", GarbageData[id][garbagePos][2]);
            cache_get_value_name_float(i, "garbageRx", GarbageData[id][garbagePos][3]);
            cache_get_value_name_float(i, "garbageRy", GarbageData[id][garbagePos][4]);
            cache_get_value_name_float(i, "garbageRz", GarbageData[id][garbagePos][5]);
            cache_get_value_name_int(i, "garbageInterior", GarbageData[id][garbageInterior]);
            cache_get_value_name_int(i, "garbageWorld", GarbageData[id][garbageWorld]);
            
			Garbage_Rebuild(id);
			Iter_Add(Garbages, id);
        }
        printf("[Dynamic Garbages] Jumlah total Garbages Bin yang dimuat: %d.", rows);
	}
	return 1;
}

hook OnPlayerEditDynObject(playerid, STREAMER_TAG_OBJECT: objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if(AccountData[playerid][EditingGarbageID] != -1 && Iter_Contains(Garbages, AccountData[playerid][EditingGarbageID]))
	{
		if(response == EDIT_RESPONSE_FINAL)
	    {
	        new edgid = AccountData[playerid][EditingGarbageID];
	        GarbageData[edgid][garbagePos][0] = x;
	        GarbageData[edgid][garbagePos][1] = y;
	        GarbageData[edgid][garbagePos][2] = z;
	        GarbageData[edgid][garbagePos][3] = rx;
	        GarbageData[edgid][garbagePos][4] = ry;
	        GarbageData[edgid][garbagePos][5] = rz;

			SetDynamicObjectPos(objectid, GarbageData[edgid][garbagePos][0], GarbageData[edgid][garbagePos][1], GarbageData[edgid][garbagePos][2]);
	        SetDynamicObjectRot(objectid, GarbageData[edgid][garbagePos][3], GarbageData[edgid][garbagePos][4], GarbageData[edgid][garbagePos][5]);

			Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, GarbageData[edgid][garbageText3D], GarbageData[edgid][garbagePos][0], GarbageData[edgid][garbagePos][1], GarbageData[edgid][garbagePos][2]+1.5);
			
		    Garbage_Save(edgid);
	        AccountData[playerid][EditingGarbageID] = -1;
	    }

	    else if(response == EDIT_RESPONSE_CANCEL)
	    {
	        new edgid = AccountData[playerid][EditingGarbageID];
	        SetDynamicObjectPos(objectid, GarbageData[edgid][garbagePos][0], GarbageData[edgid][garbagePos][1], GarbageData[edgid][garbagePos][2]);
	        SetDynamicObjectRot(objectid, GarbageData[edgid][garbagePos][3], GarbageData[edgid][garbagePos][4], GarbageData[edgid][garbagePos][5]);
	        AccountData[playerid][EditingGarbageID] = -1;
	    }
	}
	return 0;
}

forward OnGarbageCreated(playerid, id);
public OnGarbageCreated(playerid, id)
{
	Garbage_Save(id);
	Garbage_Refresh(id);
	SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s membuat Garbage Bin dengan ID: %d.", AccountData[playerid][pAdminname], id);
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(!AccountData[playerid][pKnockdown])
		{
            new id = Garbage_Nearest(playerid);

            if(id != -1)
            {
				if(gettime() < GarbageData[id][garbageAvailTime]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tempat sampah ini baru saja dipulung!");
                if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
				
				GarbageData[id][garbageAvailTime] = 0;
				GarbageData[id][garbageTaken] = false;
				
				AccountData[playerid][pTempValue] = id;
                AccountData[playerid][pActivityTime] = 1;
				pTakingTrashTimer[playerid] = true;
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMULUNG");
                ShowProgressBar(playerid);

                ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, true, false, false, false, 0, true);
            }
        }
    }
	else if(newkeys & KEY_WALK && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		if(!AccountData[playerid][pKnockdown])
		{
            new id = Garbage_Nearest(playerid);

            if(id != -1)
            {
				if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING || pInSpecMode[playerid] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
				if(GarbageData[id][garbageModel] == 1300) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat bersembunyi di tong sampah jenis ini!");

				pInSpecMode[playerid] = 1;
				GetPlayerPos(playerid, AccountData[playerid][pPos][0], AccountData[playerid][pPos][1], AccountData[playerid][pPos][2]);
        		GetPlayerFacingAngle(playerid, AccountData[playerid][pPos][3]);

				AccountData[playerid][pInterior] = GetPlayerInterior(playerid);
        		AccountData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);

				GetPlayerHealth(playerid, AccountData[playerid][pHealth]);
				if(AccountData[playerid][pHasArmor])
				{
					GetPlayerArmour(playerid, AccountData[playerid][pArmor]);
				}
				else
				{
					AccountData[playerid][pArmor] = 0.0;
				}

				TogglePlayerSpectating(playerid, true);

				PlayerPlaySound(playerid, 6802, 0, 0, 0);

				new Float:gcamX = GarbageData[id][garbagePos][0] - 0.50*(floatcos(90 + GarbageData[id][garbagePos][5], degrees));
    			new Float:gcamY = GarbageData[id][garbagePos][1] - 0.50*(floatsin(90 - GarbageData[id][garbagePos][5], degrees));
				SetTimerEx("CameraHideGarbage", 2000, false, "ifffff", playerid, GarbageData[id][garbagePos][0], GarbageData[id][garbagePos][1], GarbageData[id][garbagePos][2], gcamX, gcamY);
            }
        }
	}
    return 1;
}

forward CameraHideGarbage(playerid, Float:x, Float:y, Float:z, Float:camX, Float:camY);
public CameraHideGarbage(playerid, Float:x, Float:y, Float:z, Float:camX, Float:camY)
{
	if(!IsPlayerConnected(playerid)) return 0;
	if(pInSpecMode[playerid] != 1) return 0;

	TextDrawShowForPlayer(playerid, GarbageHideTD[0]);
	TextDrawShowForPlayer(playerid, GarbageHideTD[1]);
	SetPlayerCameraPos(playerid, x, y, z+0.55);
	SetPlayerCameraLookAt(playerid, camX, camY, z+0.67, CAMERA_CUT);

	SendClientMessage(playerid, -1, "Anda sekarang bersembunyi di tong sampah, gunakan "YELLOW"/out "WHITE"untuk keluar.");
	return 1;
}