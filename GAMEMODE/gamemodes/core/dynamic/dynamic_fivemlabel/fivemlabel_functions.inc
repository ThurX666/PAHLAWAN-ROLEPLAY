#include <YSI_Coding\y_hooks>

#define MAX_FIVEMLABEL  100

enum e_FivemLabel
{
    fLabelTogPickup,
    fLabelPickupID,
    fLabelText[128],
    Float:fLabelPos[4],
    fLabelWorld,
    fLabelInterior,

    //not save
    STREAMER_TAG_OBJECT:fLabelObject,
    bool:isfLabelMoving,
    STREAMER_TAG_PICKUP:fLabelPickup
};
new FivemLabelData[MAX_FIVEMLABEL][e_FivemLabel],
    Iterator: FivemLabels<MAX_FIVEMLABEL>;

ReplaceString(const text[])
{
    new replace[128];
    format(replace, sizeof(replace), text);

    strreplace(replace, "(e)", "\n");
    strreplace(replace, "(n)", "\n");
    strreplace(replace, "(b)", "{0049FF}");
    strreplace(replace, "(bl)", "{000000}");
    strreplace(replace, "(w)", "{FFFFFF}");
    strreplace(replace, "(r)", "{FF3333}");
    strreplace(replace, "(g)", "{37DB45}");
    strreplace(replace, "(y)", "{F3FF02}");
    return replace;
}

FivemLabel_IsBlockedArivenaText(const text[])
{
    if(strfind(text, "arivena", true) != -1) return 1;
    if(!strcmp(text, "ariv", true)) return 1;
    if(!strcmp(text, "ena", true)) return 1;
    if(!strcmp(text, "ari", true)) return 1;
    if(!strcmp(text, "ve", true)) return 1;
    if(!strcmp(text, "na", true)) return 1;
    return 0;
}

FiveMLabelMovingText(flid)
{
    if(flid != -1)
	{
        if(FivemLabelData[flid][fLabelTogPickup])
        {
            MoveDynamicObject(FivemLabelData[flid][fLabelObject], FivemLabelData[flid][fLabelPos][0], FivemLabelData[flid][fLabelPos][1], FivemLabelData[flid][fLabelPos][2] + (!FivemLabelData[flid][isfLabelMoving] ? (1.5) : (0.5)), 0.25);
        }
        else
        {
            MoveDynamicObject(FivemLabelData[flid][fLabelObject], FivemLabelData[flid][fLabelPos][0], FivemLabelData[flid][fLabelPos][1], FivemLabelData[flid][fLabelPos][2] + (!FivemLabelData[flid][isfLabelMoving] ? (0.3) : (-0.3)), 0.25);
        }
        FivemLabelData[flid][isfLabelMoving] = !FivemLabelData[flid][isfLabelMoving];
    }
}

FivemLabel_Save(flid)
{
	new dquery[522];
	mysql_format(g_SQL, dquery, sizeof(dquery), "UPDATE `fivem_labels` SET `TogPickup`='%d', `PickupID`='%d', `Text`='%e', `PosX`='%f', `PosY`='%f', `PosZ`='%f', `PosA`='%f', `PosWorld`='%d', `PosInterior`='%d' WHERE `ID`='%d'",
	FivemLabelData[flid][fLabelTogPickup], FivemLabelData[flid][fLabelPickupID], FivemLabelData[flid][fLabelText], FivemLabelData[flid][fLabelPos][0], FivemLabelData[flid][fLabelPos][1], FivemLabelData[flid][fLabelPos][2], FivemLabelData[flid][fLabelPos][3],
    FivemLabelData[flid][fLabelWorld], FivemLabelData[flid][fLabelInterior], flid);
	mysql_pquery(g_SQL, dquery);
	return 1;
}

FivemLabel_BeingEdited(flid)
{
	if(!Iter_Contains(FivemLabels, flid)) return 0;
	foreach(new i : Player) if(AccountData[i][EditingFLabelID] == flid) return 1;
	return 0;
}

FivemLabel_Refresh(flid)
{
	if(flid != -1)
	{
        if(FivemLabelData[flid][fLabelTogPickup])
        {
            Streamer_SetIntData(STREAMER_TYPE_PICKUP, FivemLabelData[flid][fLabelPickup], E_STREAMER_MODEL_ID, FivemLabelData[flid][fLabelPickupID]);
            Streamer_SetItemPos(STREAMER_TYPE_PICKUP, FivemLabelData[flid][fLabelPickup], FivemLabelData[flid][fLabelPos][0], FivemLabelData[flid][fLabelPos][1], FivemLabelData[flid][fLabelPos][2]);
		    Streamer_SetIntData(STREAMER_TYPE_PICKUP, FivemLabelData[flid][fLabelPickup], E_STREAMER_WORLD_ID, FivemLabelData[flid][fLabelWorld]);
		    Streamer_SetIntData(STREAMER_TYPE_PICKUP, FivemLabelData[flid][fLabelPickup], E_STREAMER_INTERIOR_ID, FivemLabelData[flid][fLabelInterior]);

            Streamer_SetItemPos(STREAMER_TYPE_OBJECT, FivemLabelData[flid][fLabelObject], FivemLabelData[flid][fLabelPos][0], FivemLabelData[flid][fLabelPos][1], FivemLabelData[flid][fLabelPos][2]);
        }
        else
        {
            Streamer_SetItemPos(STREAMER_TYPE_OBJECT, FivemLabelData[flid][fLabelObject], FivemLabelData[flid][fLabelPos][0], FivemLabelData[flid][fLabelPos][1], FivemLabelData[flid][fLabelPos][2]);
        }
        Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FivemLabelData[flid][fLabelObject], E_STREAMER_R_Z, FivemLabelData[flid][fLabelPos][3]);
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, FivemLabelData[flid][fLabelObject], E_STREAMER_WORLD_ID, FivemLabelData[flid][fLabelWorld]);
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, FivemLabelData[flid][fLabelObject], E_STREAMER_INTERIOR_ID, FivemLabelData[flid][fLabelInterior]);

        SetDynamicObjectMaterialText(FivemLabelData[flid][fLabelObject], 0, FivemLabelData[flid][fLabelText], 130, "Tahoma", 24, 1, -23304, 0, 1);
        FiveMLabelMovingText(flid);
    }
}

FivemLabel_Rebuild(flid)
{
	if(flid != -1)
	{
        if(FivemLabelData[flid][fLabelTogPickup])
        {
            FivemLabelData[flid][fLabelPickup] = CreateDynamicPickup(FivemLabelData[flid][fLabelPickupID], 23, FivemLabelData[flid][fLabelPos][0], FivemLabelData[flid][fLabelPos][1], FivemLabelData[flid][fLabelPos][2], FivemLabelData[flid][fLabelWorld], FivemLabelData[flid][fLabelInterior], -1, 100.00, -1, 0);
        }
        FivemLabelData[flid][fLabelObject] = CreateDynamicObject(19482, FivemLabelData[flid][fLabelPos][0], FivemLabelData[flid][fLabelPos][1], FivemLabelData[flid][fLabelPos][2], 0.0, 0.0, FivemLabelData[flid][fLabelPos][3], FivemLabelData[flid][fLabelWorld], FivemLabelData[flid][fLabelInterior], -1, 100.00, 100.00, -1);
        SetDynamicObjectMaterialText(FivemLabelData[flid][fLabelObject], 0, FivemLabelData[flid][fLabelText], 130, "Tahoma", 24, 1, -23304, 0, 1);
        FiveMLabelMovingText(flid);
    }
}

FivemLabel_Nearest(playerid)
{
    foreach(new i : FivemLabels) if (IsPlayerInRangeOfPoint(playerid, 1.5, FivemLabelData[i][fLabelPos][0], FivemLabelData[i][fLabelPos][1], FivemLabelData[i][fLabelPos][2]))
	{
		if (GetPlayerInterior(playerid) == FivemLabelData[i][fLabelInterior] && GetPlayerVirtualWorld(playerid) == FivemLabelData[i][fLabelWorld])
			return i;
	}
	return -1;
}

hook OnDynamicObjectMoved(STREAMER_TAG_OBJECT:objectid)
{
    foreach(new flid : FivemLabels)
    {
        if(FivemLabelData[flid][fLabelObject])
        {
            FiveMLabelMovingText(flid);
        }
    }
    return 1;
}

hook OnPlayerEditDynObject(playerid, STREAMER_TAG_OBJECT: objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if(AccountData[playerid][EditingFLabelID] != -1 && Iter_Contains(FivemLabels, AccountData[playerid][EditingFLabelID]))
	{
		if(response == EDIT_RESPONSE_FINAL)
	    {
	        new edgid = AccountData[playerid][EditingFLabelID];
	        FivemLabelData[edgid][fLabelPos][3] = rz;

	        SetDynamicObjectRot(objectid, 0.0, 0.0, FivemLabelData[edgid][fLabelPos][3]);

		    FivemLabel_Save(edgid);
	        AccountData[playerid][EditingFLabelID] = -1;
	    }

	    else if(response == EDIT_RESPONSE_CANCEL)
	    {
	        new edgid = AccountData[playerid][EditingFLabelID];
	        SetDynamicObjectRot(objectid, 0.0, 0.0, FivemLabelData[edgid][fLabelPos][3]);
	        AccountData[playerid][EditingFLabelID] = -1;
	    }
	}
	return 0;
}

Dialog:FLabelAdd(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    new flid = Iter_Free(FivemLabels), query[248];
    if(flid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah dynamic Fivem Labels telah mencapai batas maksimum!");
    if(FivemLabel_IsBlockedArivenaText(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Text Fivem Label tersebut tidak diperbolehkan!");

    format(FivemLabelData[flid][fLabelText], 128, ReplaceString(inputtext));
    GetPlayerPos(playerid, FivemLabelData[flid][fLabelPos][0], FivemLabelData[flid][fLabelPos][1], FivemLabelData[flid][fLabelPos][2]);
    GetPlayerFacingAngle(playerid, FivemLabelData[flid][fLabelPos][3]);
    FivemLabelData[flid][fLabelWorld] = GetPlayerVirtualWorld(playerid);
    FivemLabelData[flid][fLabelInterior] = GetPlayerInterior(playerid);

    FivemLabelData[flid][fLabelTogPickup] = false;
    FivemLabelData[flid][fLabelPickupID] = 1239;

    FivemLabel_Rebuild(flid);
    Iter_Add(FivemLabels, flid);

    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `fivem_labels` SET `ID`='%d', `TogPickup`='%d', `PickupID`='%d', `Text`='%e', `PosX`='%f', `PosY`='%f', `PosZ`='%f', `PosWorld`='%d', `PosInterior`='%d'", flid, FivemLabelData[flid][fLabelTogPickup], FivemLabelData[flid][fLabelPickupID], FivemLabelData[flid][fLabelText], FivemLabelData[flid][fLabelPos][0], FivemLabelData[flid][fLabelPos][1], FivemLabelData[flid][fLabelPos][2], FivemLabelData[flid][fLabelWorld], FivemLabelData[flid][fLabelInterior]);
    mysql_pquery(g_SQL, query, "OnFivemLabelCreated", "ii", playerid, flid);
    return 1;
}

Dialog:FLabelEdit(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    new flid = AccountData[playerid][EditingFLabelID];
    if(!Iter_Contains(FivemLabels, flid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Fivem Labels tersebut tidak valid!");
    if(FivemLabel_IsBlockedArivenaText(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Text Fivem Label tersebut tidak diperbolehkan!");

    format(FivemLabelData[flid][fLabelText], 128, ReplaceString(inputtext));
    FivemLabel_Save(flid);
    FivemLabel_Refresh(flid);

    AccountData[playerid][EditingFLabelID] = -1;
    return 1;
}

forward OnFivemLabelCreated(playerid, flid);
public OnFivemLabelCreated(playerid, flid)
{
	FivemLabel_Save(flid);

    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s membuat Fivem Labels dengan ID: %d.", AccountData[playerid][pAdminname], flid);
	return 1;
}

forward LoadFivemLabelText();
public LoadFivemLabelText()
{
	new rows = cache_num_rows();
	if(rows)
	{
		new flid, name[128], query[96], loaded, removed;
		for(new i; i < rows; i++)
		{
			cache_get_value_name_int(i, "ID", flid);
			cache_get_value_name(i, "Text", name);
            if(FivemLabel_IsBlockedArivenaText(name))
            {
                mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `fivem_labels` WHERE `ID`=%d", flid);
                mysql_pquery(g_SQL, query);
                removed++;
                continue;
            }

            cache_get_value_name_int(i, "TogPickup", FivemLabelData[flid][fLabelTogPickup]);
            cache_get_value_name_int(i, "PickupID", FivemLabelData[flid][fLabelPickupID]);
			strcopy(FivemLabelData[flid][fLabelText], name);
		    cache_get_value_name_float(i, "PosX", FivemLabelData[flid][fLabelPos][0]);
			cache_get_value_name_float(i, "PosY", FivemLabelData[flid][fLabelPos][1]);
			cache_get_value_name_float(i, "PosZ", FivemLabelData[flid][fLabelPos][2]);
            cache_get_value_name_float(i, "PosA", FivemLabelData[flid][fLabelPos][3]);
			cache_get_value_name_int(i, "PosWorld", FivemLabelData[flid][fLabelWorld]);
			cache_get_value_name_int(i, "PosInterior", FivemLabelData[flid][fLabelInterior]);
			
			FivemLabel_Rebuild(flid);
			Iter_Add(FivemLabels, flid);
            loaded++;
	    }
	    printf("[Dynamic Fivem Labels] The total number of Fivem Labels loaded: %d. Removed blocked labels: %d.", loaded, removed);
	}
}
