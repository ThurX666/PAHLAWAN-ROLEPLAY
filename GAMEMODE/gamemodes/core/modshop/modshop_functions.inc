#include <YSI_Coding\y_hooks>

new const FontNames[][] = {
    "Arial",
    "Calibri",
    "Comic Sans MS",
    "Georgia",
    "Times New Roman",
    "Consolas",
    "Constantia",
    "Corbel",
    "Courier New",
    "Impact",
    "Lucida Console",
    "Palatino Linotype",
    "Tahoma",
    "Trebuchet MS",
    "Verdana",
    "Webdings",
    "Wingdings",
    "Wingdings 2",
    "Wingdings 3"
};

enum e_pvtoy_data
{
    vtoy_ID,
    vtoy_modelid,
	vtoy_text[144],
	vtoy_font[64],
	vtoy_fontsize,
	vtoy_fontcolor[5],
	vtoy_objectcolor[5],
    STREAMER_TAG_OBJECT:vtoy_model,
    Float:vtoy_x,
    Float:vtoy_y,
    Float:vtoy_z,
    Float:vtoy_rx,
    Float:vtoy_ry,
    Float:vtoy_rz
}
new vtData[MAX_PRIVATE_VEHICLE][11][e_pvtoy_data];

// Vehicle attach update types
enum
{
	FloatX,
	FloatY,
	FloatZ,
	FloatRX,
	FloatRY,
	FloatRZ
};

new Float:NudgeVal[MAX_PLAYERS];

new Float:__g_ModshopLoc[][3] =
{
    {2067.8835,-1868.2396,13.5893},
    {2061.0615,-1868.3254,13.5893},
    {2054.3245,-1868.1346,13.5893},
    {2047.4725,-1868.2566,13.5893},
    {2040.7386,-1868.0303,13.5893},
    {2029.7916,-1868.2662,13.5893},
    {2019.9508,-1868.3489,13.5793}
};

IsPlayerInModshopArea(playerid)
{
    for(new x; x < sizeof(__g_ModshopLoc); x++)
    {
        if(IsPlayerInRangeOfPoint(playerid, 1.5, __g_ModshopLoc[x][0], __g_ModshopLoc[x][1], __g_ModshopLoc[x][2]) && GetPlayerVirtualWorld(playerid) == 0 && GetPlayerInterior(playerid) == 0)
        {
            return 1;
        }
    }
    return 0;
}

ReAllocToySlot(iteratorid, slot) 
{
    for(new i = slot + 1; i < 11; i++) 
	{
        vtData[iteratorid][i - 1] = vtData[iteratorid][i];
    }

	vtData[iteratorid][5][vtoy_modelid] = 0;
	vtData[iteratorid][5][vtoy_text][0] = EOS;
	strcopy(vtData[iteratorid][5][vtoy_font], "Arial");
	vtData[iteratorid][5][vtoy_fontsize] = 11;
	vtData[iteratorid][5][vtoy_fontcolor][0] = 255;
	vtData[iteratorid][5][vtoy_fontcolor][1] = 0;
	vtData[iteratorid][5][vtoy_fontcolor][2] = 0;
	vtData[iteratorid][5][vtoy_fontcolor][3] = 0;
	vtData[iteratorid][5][vtoy_fontcolor][4] = 0;
	vtData[iteratorid][5][vtoy_objectcolor][0] = 255;
	vtData[iteratorid][5][vtoy_objectcolor][1] = 0;
	vtData[iteratorid][5][vtoy_objectcolor][2] = 0;
	vtData[iteratorid][5][vtoy_objectcolor][3] = 0;
	vtData[iteratorid][5][vtoy_objectcolor][4] = 0;
	vtData[iteratorid][5][vtoy_x] = 0.0;
	vtData[iteratorid][5][vtoy_y] = 0.0;
	vtData[iteratorid][5][vtoy_z] = 0.0;
	vtData[iteratorid][5][vtoy_rx] = 0.0;
	vtData[iteratorid][5][vtoy_ry] = 0.0;
	vtData[iteratorid][5][vtoy_rz] = 0.0;
}

ResetEditing(playerid)
{
    if(AccountData[playerid][EditingModshopSlotID] != -1)
	{
		new iteratorid = Vehicle_GetIterID(GetPlayerVehicleID(playerid));
		if(iteratorid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini bukan jenis kendaraan pribadi!");
		
        AttachVehicleToys(iteratorid);
        Vehicle_ObjectUpdate(iteratorid, AccountData[playerid][EditingModshopSlotID]);
            
        AccountData[playerid][EditingModshopSlotID] = -1;
    }
    return 1;
}

MySQL_LoadVehicleToys(iteratorid)
{
	new tstr[512];
	mysql_format(g_SQL, tstr, sizeof(tstr), "SELECT * FROM `vtoys` WHERE `Veh_DBID`='%d'", PlayerVehicle[iteratorid][pVehID]);
	mysql_pquery(g_SQL, tstr, "LoadVehicleToys", "i", iteratorid);
}

forward LoadVehicleToys(iteratorid);
public LoadVehicleToys(iteratorid)
{
	new rows = cache_num_rows(), formatwarna[144];
 	if(rows)
  	{
        for(new slot; slot < rows; slot++)
        {
            cache_get_value_name_int(slot, "ID", vtData[iteratorid][slot][vtoy_ID]);
            cache_get_value_name_int(slot, "Modelid", vtData[iteratorid][slot][vtoy_modelid]);
			cache_get_value_name(slot, "Text", vtData[iteratorid][slot][vtoy_text]);
			cache_get_value_name(slot, "Font", vtData[iteratorid][slot][vtoy_font]);
			cache_get_value_name_int(slot, "FontSize", vtData[iteratorid][slot][vtoy_fontsize]);
			
			cache_get_value_name(slot, "FontColor", formatwarna);
			sscanf(formatwarna, "p<|>a<i>[4]", vtData[iteratorid][slot][vtoy_fontcolor]);
        	vtData[iteratorid][slot][vtoy_fontcolor][4] = RGBA(vtData[iteratorid][slot][vtoy_fontcolor][0], vtData[iteratorid][slot][vtoy_fontcolor][1], vtData[iteratorid][slot][vtoy_fontcolor][2], vtData[iteratorid][slot][vtoy_fontcolor][3]);
			
			cache_get_value_name(slot, "ObjectColor", formatwarna);
			sscanf(formatwarna, "p<|>a<i>[4]", vtData[iteratorid][slot][vtoy_objectcolor]);
        	vtData[iteratorid][slot][vtoy_objectcolor][4] = RGBA(vtData[iteratorid][slot][vtoy_objectcolor][0], vtData[iteratorid][slot][vtoy_objectcolor][1], vtData[iteratorid][slot][vtoy_objectcolor][2], vtData[iteratorid][slot][vtoy_objectcolor][3]);

            cache_get_value_name_float(slot, "XPos", vtData[iteratorid][slot][vtoy_x]);
            cache_get_value_name_float(slot, "YPos", vtData[iteratorid][slot][vtoy_y]);
            cache_get_value_name_float(slot, "ZPos", vtData[iteratorid][slot][vtoy_z]);
            cache_get_value_name_float(slot, "XRot", vtData[iteratorid][slot][vtoy_rx]);
            cache_get_value_name_float(slot, "YRot", vtData[iteratorid][slot][vtoy_ry]);
            cache_get_value_name_float(slot, "ZRot", vtData[iteratorid][slot][vtoy_rz]);
        }
        AttachVehicleToys(iteratorid);
	}
}

MySQL_SaveVehicleToys(iteratorid, slot)
{
	if(slot == -1) return 1;

	new lstr[520];
	mysql_format(g_SQL, lstr, sizeof(lstr), "UPDATE `vtoys` SET \
	`Modelid` = %d, `Text` = '%e', `Font` = '%e', `FontSize` = %d, `FontColor` = '%d|%d|%d|%d', `ObjectColor` = '%d|%d|%d|%d', `XPos` = %.3f, `YPos` = %.3f, `ZPos` = %.3f, `XRot` = %.3f, `YRot` = %.3f, `ZRot` = %.3f WHERE `Veh_DBID` = %d AND `ID` = %d",
		vtData[iteratorid][slot][vtoy_modelid],
		vtData[iteratorid][slot][vtoy_text],
		vtData[iteratorid][slot][vtoy_font],
		vtData[iteratorid][slot][vtoy_fontsize],
		vtData[iteratorid][slot][vtoy_fontcolor][0],
		vtData[iteratorid][slot][vtoy_fontcolor][1],
		vtData[iteratorid][slot][vtoy_fontcolor][2],
		vtData[iteratorid][slot][vtoy_fontcolor][3],
		vtData[iteratorid][slot][vtoy_objectcolor][0],
		vtData[iteratorid][slot][vtoy_objectcolor][1],
		vtData[iteratorid][slot][vtoy_objectcolor][2],
		vtData[iteratorid][slot][vtoy_objectcolor][3],
        vtData[iteratorid][slot][vtoy_x],
        vtData[iteratorid][slot][vtoy_y],
        vtData[iteratorid][slot][vtoy_z],
        vtData[iteratorid][slot][vtoy_rx],
        vtData[iteratorid][slot][vtoy_ry],
        vtData[iteratorid][slot][vtoy_rz],
        PlayerVehicle[iteratorid][pVehID],
        vtData[iteratorid][slot][vtoy_ID]);
    mysql_pquery(g_SQL, lstr);
    return 1;
}

Vehicle_ObjectUpdate(iteratorid, slot)
{   
	if(Iter_Contains(PvtVehicles, iteratorid))
	{
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, vtData[iteratorid][slot][vtoy_model], E_STREAMER_ATTACHED_VEHICLE, PlayerVehicle[iteratorid][pVehPhysic]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vtData[iteratorid][slot][vtoy_model], E_STREAMER_ATTACH_OFFSET_X, vtData[iteratorid][slot][vtoy_x]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vtData[iteratorid][slot][vtoy_model], E_STREAMER_ATTACH_OFFSET_Y, vtData[iteratorid][slot][vtoy_y]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vtData[iteratorid][slot][vtoy_model], E_STREAMER_ATTACH_OFFSET_Z, vtData[iteratorid][slot][vtoy_z]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vtData[iteratorid][slot][vtoy_model], E_STREAMER_ATTACH_X, vtData[iteratorid][slot][vtoy_x]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vtData[iteratorid][slot][vtoy_model], E_STREAMER_ATTACH_Y, vtData[iteratorid][slot][vtoy_y]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vtData[iteratorid][slot][vtoy_model], E_STREAMER_ATTACH_Z, vtData[iteratorid][slot][vtoy_z]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vtData[iteratorid][slot][vtoy_model], E_STREAMER_ATTACH_R_X, vtData[iteratorid][slot][vtoy_rx]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vtData[iteratorid][slot][vtoy_model], E_STREAMER_ATTACH_R_Y, vtData[iteratorid][slot][vtoy_ry]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vtData[iteratorid][slot][vtoy_model], E_STREAMER_ATTACH_R_Z, vtData[iteratorid][slot][vtoy_rz]);
        return 1;
    }
    return 0;
}

Vehicle_ObjectColorSync(iteratorid, slot)
{
    if(Iter_Contains(PvtVehicles, iteratorid))
	{
        SetDynamicObjectMaterial( vtData[iteratorid][slot][vtoy_model], 0,  vtData[iteratorid][slot][vtoy_modelid], "none", "none", vtData[iteratorid][slot][vtoy_objectcolor][4]);
        MySQL_SaveVehicleToys(iteratorid, slot);
	    return 1;
    }
    return 0;
}

Vehicle_ObjectTextSync(iteratorid, slot)
{
    if(Iter_Contains(PvtVehicles, iteratorid))
	{
        SetDynamicObjectMaterialText( vtData[iteratorid][slot][vtoy_model], 0,  vtData[iteratorid][slot][vtoy_text], 130,  vtData[iteratorid][slot][vtoy_font],  vtData[iteratorid][slot][vtoy_fontsize], 1, vtData[iteratorid][slot][vtoy_fontcolor][4], 0, 1);
        MySQL_SaveVehicleToys(iteratorid, slot);
        return 1;
    }
    return 0;
}

Vehicle_ObjectEdit(playerid, iteratorid, slot, bool:text = false)
{
	if(Iter_Contains(PvtVehicles, iteratorid))
	{
        if(DestroyDynamicObject(vtData[iteratorid][slot][vtoy_model]))
			vtData[iteratorid][slot][vtoy_model] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

        new 
            Float:x,
            Float:y,
            Float:z,
            Float:rx = vtData[iteratorid][slot][vtoy_rx],
            Float:ry = vtData[iteratorid][slot][vtoy_ry],
            Float:rz = vtData[iteratorid][slot][vtoy_rz]
        ;
		
        GetVehiclePos(GetPlayerVehicleID(playerid), x, y, z);
		SetVehicleZAngle(GetPlayerVehicleID(playerid), 0.0);
        vtData[iteratorid][slot][vtoy_model] = CreateDynamicObject(vtData[iteratorid][slot][vtoy_modelid], x, y, z, rx, ry, rz, -1, -1, -1, 200.00, 200.00, -1);   
       	AccountData[playerid][EditingModshopSlotID] = slot;
        if(text) 
        {
            Vehicle_ObjectTextSync(GetPlayerVehicleID(playerid), slot);
        }
		EditDynamicObject(playerid, vtData[iteratorid][slot][vtoy_model]);
        return 1;
    }
    return 0;
}

forward OnToysPurchased(iteratorid, slot);
public OnToysPurchased(iteratorid, slot)
{
    vtData[iteratorid][slot][vtoy_ID] = cache_insert_id();
    AttachVehicleToys(iteratorid);
    MySQL_SaveVehicleToys(iteratorid, slot);
}

MySQL_CreateVehicleToy(iteratorid, slot)
{
	new query[512];

	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `vtoys` (`Veh_DBID`) VALUES ('%d')", PlayerVehicle[iteratorid][pVehID]);
	mysql_pquery(g_SQL, query, "OnToysPurchased", "ii", iteratorid, slot);
}

AttachVehicleToys(iteratorid)
{
    if(!Iter_Contains(Vehicle, PlayerVehicle[iteratorid][pVehPhysic])) return 1;

    new Float:CurPosVehX, Float:CurPosVehY, Float:CurPosVehZ;
    GetVehiclePos(PlayerVehicle[iteratorid][pVehPhysic], CurPosVehX, CurPosVehY, CurPosVehZ);

    for(new x; x < 11; x++)
    {
        if(vtData[iteratorid][x][vtoy_modelid] != 0)
        {
            if(!IsValidDynamicObject(vtData[iteratorid][x][vtoy_model]))
            {
                vtData[iteratorid][x][vtoy_model] = CreateDynamicObject(vtData[iteratorid][x][vtoy_modelid],
                CurPosVehX,
                CurPosVehY,
                CurPosVehZ,
                vtData[iteratorid][x][vtoy_rx],
                vtData[iteratorid][x][vtoy_ry],
                vtData[iteratorid][x][vtoy_rz],
				-1, -1, -1, 200.00, 200.00, -1);
            }
			AttachDynamicObjectToVehicle(vtData[iteratorid][x][vtoy_model],
			PlayerVehicle[iteratorid][pVehPhysic],
			vtData[iteratorid][x][vtoy_x],
			vtData[iteratorid][x][vtoy_y],
			vtData[iteratorid][x][vtoy_z],
			vtData[iteratorid][x][vtoy_rx],
			vtData[iteratorid][x][vtoy_ry],
			vtData[iteratorid][x][vtoy_rz]);
			
			if(vtData[iteratorid][x][vtoy_modelid] == 18667)
			{
				Vehicle_ObjectTextSync(iteratorid, x);
			}
			else
			{
				Vehicle_ObjectColorSync(iteratorid, x);
			}
        }
    }
	return 1;
}

DestroyVehicleToys(iteratorid)
{
    for(new x; x < 11; x++)
    {
        if(DestroyDynamicObject(vtData[iteratorid][x][vtoy_model]))
            vtData[iteratorid][x][vtoy_model] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
    }

	if(DestroyDynamic3DTextLabel(PlayerVehicle[iteratorid][pVehTireLockLabel]))
		PlayerVehicle[iteratorid][pVehTireLockLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
}

AddVObjPos(playerid)
{
	new vehid = Vehicle_GetIterID(GetPlayerVehicleID(playerid)), gametext[36];
	new idxs = AccountData[playerid][EditingModshopSlotID];
	
	if(idxs == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih slot modification apapun!");
	if(vehid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini bukan jenis kendaraan pribadi!");
	if(AccountData[playerid][pEditModshopStatus] == FloatX)
	{
		vtData[vehid][idxs][vtoy_x] += NudgeVal[playerid];
		format(gametext, 36, "Float X: ~w~%f", vtData[vehid][idxs][vtoy_x]);
	} 
	else if(AccountData[playerid][pEditModshopStatus] == FloatY)
	{
		vtData[vehid][idxs][vtoy_y] += NudgeVal[playerid];
		format(gametext, 36, "Float Y: ~w~%f", vtData[vehid][idxs][vtoy_y]);
	}
	else if(AccountData[playerid][pEditModshopStatus] == FloatZ)
	{
		vtData[vehid][idxs][vtoy_z] += NudgeVal[playerid];
		format(gametext, 36, "Float Z: ~w~%f", vtData[vehid][idxs][vtoy_z]);
	}
	else if(AccountData[playerid][pEditModshopStatus] == FloatRX)
	{
		vtData[vehid][idxs][vtoy_rx] += NudgeVal[playerid];
		format(gametext, 36, "Float RX: ~w~%f", vtData[vehid][idxs][vtoy_rx]);
	}
	else if(AccountData[playerid][pEditModshopStatus] == FloatRY)
	{
		vtData[vehid][idxs][vtoy_ry] += NudgeVal[playerid];
		format(gametext, 36, "Float RY: ~w~%f", vtData[vehid][idxs][vtoy_ry]);
	}
	else if(AccountData[playerid][pEditModshopStatus] == FloatRZ)
	{
		vtData[vehid][idxs][vtoy_rz] += NudgeVal[playerid];
		format(gametext, 36, "Float RZ: ~w~%f", vtData[vehid][idxs][vtoy_rz]);
	}
	PlayerTextDrawSetString(playerid, EditVObjPTD[playerid], gametext);
	Streamer_SetIntData(STREAMER_TYPE_OBJECT, vtData[vehid][idxs][vtoy_model], E_STREAMER_ATTACHED_VEHICLE, PlayerVehicle[vehid][pVehPhysic]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vtData[vehid][idxs][vtoy_model], E_STREAMER_ATTACH_OFFSET_X, vtData[vehid][idxs][vtoy_x]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vtData[vehid][idxs][vtoy_model], E_STREAMER_ATTACH_OFFSET_Y, vtData[vehid][idxs][vtoy_y]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vtData[vehid][idxs][vtoy_model], E_STREAMER_ATTACH_OFFSET_Z, vtData[vehid][idxs][vtoy_z]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vtData[vehid][idxs][vtoy_model], E_STREAMER_ATTACH_X, vtData[vehid][idxs][vtoy_x]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vtData[vehid][idxs][vtoy_model], E_STREAMER_ATTACH_Y, vtData[vehid][idxs][vtoy_y]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vtData[vehid][idxs][vtoy_model], E_STREAMER_ATTACH_Z, vtData[vehid][idxs][vtoy_z]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vtData[vehid][idxs][vtoy_model], E_STREAMER_ATTACH_R_X, vtData[vehid][idxs][vtoy_rx]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vtData[vehid][idxs][vtoy_model], E_STREAMER_ATTACH_R_Y, vtData[vehid][idxs][vtoy_ry]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vtData[vehid][idxs][vtoy_model], E_STREAMER_ATTACH_R_Z, vtData[vehid][idxs][vtoy_rz]);
	return 1;
}

SubVObjPos(playerid)
{
	new vehid = Vehicle_GetIterID(GetPlayerVehicleID(playerid)), gametext[36];
	new idxs = AccountData[playerid][EditingModshopSlotID];

	if(idxs == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih slot modification apapun!");
	if(vehid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini bukan jenis kendaraan pribadi!");

	if(AccountData[playerid][pEditModshopStatus] == FloatX)
	{
		vtData[vehid][idxs][vtoy_x] -= NudgeVal[playerid];
		format(gametext, 36, "Float X: ~w~%f", vtData[vehid][idxs][vtoy_x]);
	} 
	else if(AccountData[playerid][pEditModshopStatus] == FloatY)
	{
		vtData[vehid][idxs][vtoy_y] -= NudgeVal[playerid];
		format(gametext, 36, "Float Y: ~w~%f", vtData[vehid][idxs][vtoy_y]);
	}
	else if(AccountData[playerid][pEditModshopStatus] == FloatZ)
	{
		vtData[vehid][idxs][vtoy_z] -= NudgeVal[playerid];
		format(gametext, 36, "Float Z: ~w~%f", vtData[vehid][idxs][vtoy_z]);
	}
	else if(AccountData[playerid][pEditModshopStatus] == FloatRX)
	{
		vtData[vehid][idxs][vtoy_rx] -= NudgeVal[playerid];
		format(gametext, 36, "Float RX: ~w~%f", vtData[vehid][idxs][vtoy_rx]);
	}
	else if(AccountData[playerid][pEditModshopStatus] == FloatRY)
	{
		vtData[vehid][idxs][vtoy_ry] -= NudgeVal[playerid];
		format(gametext, 36, "Float RY: ~w~%f", vtData[vehid][idxs][vtoy_ry]);
	}
	else if(AccountData[playerid][pEditModshopStatus] == FloatRZ)
	{
		vtData[vehid][idxs][vtoy_rz] -= NudgeVal[playerid];
		format(gametext, 36, "Float RZ: ~w~%f", vtData[vehid][idxs][vtoy_rz]);
	}
	PlayerTextDrawSetString(playerid, EditVObjPTD[playerid], gametext);
	Streamer_SetIntData(STREAMER_TYPE_OBJECT, vtData[vehid][idxs][vtoy_model], E_STREAMER_ATTACHED_VEHICLE, PlayerVehicle[vehid][pVehPhysic]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vtData[vehid][idxs][vtoy_model], E_STREAMER_ATTACH_OFFSET_X, vtData[vehid][idxs][vtoy_x]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vtData[vehid][idxs][vtoy_model], E_STREAMER_ATTACH_OFFSET_Y, vtData[vehid][idxs][vtoy_y]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vtData[vehid][idxs][vtoy_model], E_STREAMER_ATTACH_OFFSET_Z, vtData[vehid][idxs][vtoy_z]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vtData[vehid][idxs][vtoy_model], E_STREAMER_ATTACH_X, vtData[vehid][idxs][vtoy_x]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vtData[vehid][idxs][vtoy_model], E_STREAMER_ATTACH_Y, vtData[vehid][idxs][vtoy_y]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vtData[vehid][idxs][vtoy_model], E_STREAMER_ATTACH_Z, vtData[vehid][idxs][vtoy_z]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vtData[vehid][idxs][vtoy_model], E_STREAMER_ATTACH_R_X, vtData[vehid][idxs][vtoy_rx]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vtData[vehid][idxs][vtoy_model], E_STREAMER_ATTACH_R_Y, vtData[vehid][idxs][vtoy_ry]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vtData[vehid][idxs][vtoy_model], E_STREAMER_ATTACH_R_Z, vtData[vehid][idxs][vtoy_rz]);
	return 1;
}

hook OnPlayerEditDynObject(playerid, STREAMER_TAG_OBJECT:objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if(AccountData[playerid][EditingModshopSlotID] != -1)
	{
		new iteratorid = Vehicle_GetIterID(GetPlayerVehicleID(playerid));
		new slotid = AccountData[playerid][EditingModshopSlotID];

		if(iteratorid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini bukan jenis kendaraan pribadi!");
		if(!IsValidDynamicObject(vtData[iteratorid][slotid][vtoy_model])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Object vehicle toys tidak valid!");
		if(response == EDIT_RESPONSE_FINAL)
		{
			new 
				vehicleid = GetPlayerVehicleID(playerid),
				Float:vx,
				Float:vy,
				Float:vz,
				Float:va,
				Float:real_x,
				Float:real_y,
				Float:real_z,
				Float:real_a
			;

			GetVehiclePos(vehicleid, vx, vy, vz);
			GetVehicleZAngle(vehicleid, va);

			real_x = x - vx;
			real_y = y - vy;
			real_z = z - vz;
			real_a = rz - va;

			new Float:v_size[3];
			GetVehicleModelInfo(GetVehicleModel(vehicleid), VEHICLE_MODEL_INFO_SIZE, v_size[0], v_size[1], v_size[2]);
			if(	(real_x >= v_size[0] || -v_size[0] >= real_x) || 
				(real_y >= v_size[1] || -v_size[1] >= real_y) ||
				(real_z >= v_size[2] || -v_size[2] >= real_z))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Posisi object terlalu jauh dari body kendaraan!");
				ResetEditing(playerid);
				return 1;
			}

			vtData[iteratorid][slotid][vtoy_x] = real_x;
			vtData[iteratorid][slotid][vtoy_y] = real_y;
			vtData[iteratorid][slotid][vtoy_z] = real_z;
			vtData[iteratorid][slotid][vtoy_rx] = rx;
			vtData[iteratorid][slotid][vtoy_ry] = ry;
			vtData[iteratorid][slotid][vtoy_rz] = real_a;
		
			Vehicle_ObjectUpdate(iteratorid, slotid);
			AttachVehicleToys(iteratorid);
			MySQL_SaveVehicleToys(iteratorid, slotid);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Posisi object telah berhasil diperbarui!");

			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		}
	    else if(response == EDIT_RESPONSE_CANCEL)
	    {
			Streamer_SetIntData(STREAMER_TYPE_OBJECT, vtData[iteratorid][slotid][vtoy_model], E_STREAMER_ATTACHED_VEHICLE, GetPlayerVehicleID(playerid));
			TogglePlayerControllable(playerid, true);
	        AttachDynamicObjectToVehicle(objectid,GetPlayerVehicleID(playerid),vtData[iteratorid][slotid][vtoy_x],vtData[iteratorid][slotid][vtoy_y],vtData[iteratorid][slotid][vtoy_z],vtData[iteratorid][slotid][vtoy_rx],vtData[iteratorid][slotid][vtoy_ry],vtData[iteratorid][slotid][vtoy_rz]);
	        ResetEditing(playerid);
	    }
	}
	return 1;
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if(clickedid == EditVObjTD[4])
    {
        if(IsPlayerInAnyVehicle(playerid))
        {
            HideModshopTD(playerid);
            new iteratorid = Vehicle_GetIterID(GetPlayerVehicleID(playerid));
			if(iteratorid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini bukan jenis kendaraan pribadi!");
			MySQL_SaveVehicleToys(iteratorid, AccountData[playerid][EditingModshopSlotID]);

			Dialog_Show(playerid, "ModshopAndroChoose", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Modshop Menu", "Ubah X\nUbah Y\nUbah Z\nUbah RX\nUbah RY\nUbah RZ", "Pilih", "Batal");
        }
    }
    else if(clickedid == EditVObjTD[5])
    {
		AccountData[playerid][EditingModshopSlotID] = -1;
        HideModshopTD(playerid);
    	ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    }
    else if(clickedid == EditVObjTD[2])
    {
		if(AccountData[playerid][EditingModshopSlotID] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih slot modification apapun!");
		
        AddVObjPos(playerid);
    }
    else if(clickedid == EditVObjTD[3])
    {
		if(AccountData[playerid][EditingModshopSlotID] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih slot modification apapun!");
		
        SubVObjPos(playerid);
    }
    else if(clickedid == EditVObjTD[6])
    {
        Dialog_Show(playerid, "ModshopCatalogAndro", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Modshop Menu", "Set current float value\nNormal Value = 0.05\n\nEnter Float NudgeValue in here:", "Edit", "Batal");
    }
	return 1;
}

Dialog:ModshopCatalog(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih opsi!");
	
	new iteratorid = Vehicle_GetIterID(GetPlayerVehicleID(playerid));
	if(iteratorid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini bukan jenis kendaraan pribadi!");

	if(!strcmp(inputtext, "+ Beli baru", false) || vtData[iteratorid][listitem][vtoy_modelid] == 0)
	{
		new 
			count;
		for(new x; x < 11; x++)
		{
			if(vtData[iteratorid][x][vtoy_model] != 0)
			{
				count++;
			}
		}

		switch(AccountData[playerid][pVIP])
		{
			case 0: //tidak vip
			{
				if(count >= 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak donasi VIP maks slot 5!");
			}
			case 1, 2: //regular pinky
			{
				if(count >= 7) return ShowTDN(playerid, NOTIFICATION_ERROR, "Donasi VIP Regular Pinky hanya dapat maks slot 7!");
			}
			case 3: //pinkyman pimky
			{
				if(count >= 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot vehicle toys anda sudah mencapai batas maks 10 slot!");
			}
		}
		ShowModelSelectionMenu(playerid, ModshopModel, "Pilih Modifikasi!");
	}
	else
	{
		AccountData[playerid][EditingModshopSlotID] = listitem;
		Dialog_Show(playerid, "ModshopCatalogMenu", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Modshop Menu", "Edit Position\n"GRAY"Set Text\nSize Text\n"GRAY"Change Font\nChange Color\n"GRAY"Remove", "Pilih", "Batal");
	}
	return 1;
}

Dialog:ModshopAndroChoose(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	switch(listitem)
	{
		case 0:
		{
			AccountData[playerid][pEditModshopStatus] = FloatX;
		}
		case 1:
		{
			AccountData[playerid][pEditModshopStatus] = FloatY;
		}
		case 2:
		{
			AccountData[playerid][pEditModshopStatus] = FloatZ;
		}
		case 3:
		{
			AccountData[playerid][pEditModshopStatus] = FloatRX;
		}
		case 4:
		{
			AccountData[playerid][pEditModshopStatus] = FloatRY;
		}
		case 5:
		{
			AccountData[playerid][pEditModshopStatus] = FloatRZ;
		}
	}

	ShowModshopTD(playerid);
	SelectTextDraw(playerid, 0xff91a4cc);
	SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Gunakan "CMDEA"'/cursor' "WHITE"jika mouse hilang dari layar/textdraw tidak bisa ditekan!");
	return 1;
}

Dialog:ModshopCatalogDevice(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	new iteratorid = Vehicle_GetIterID(GetPlayerVehicleID(playerid)),
		slotid = AccountData[playerid][EditingModshopSlotID];
	
	if(iteratorid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini bukan jenis kendaraan pribadi!");

	switch(listitem)
	{
		case 0:
		{
			SwitchVehicleEngine(GetPlayerVehicleID(playerid),false);
			Vehicle_ObjectEdit(playerid, iteratorid, slotid, (vtData[iteratorid][slotid][vtoy_modelid] == 18667) ? (true) : (false));
		}
		case 1:
		{
			Dialog_Show(playerid, "ModshopAndroChoose", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Modshop Menu", "Ubah X\nUbah Y\nUbah Z\nUbah RX\nUbah RY\nUbah RZ", "Pilih", "Batal");
		}
	}
	return 1;
}

Dialog:ModshopCatalogAndro(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat mengosongkan kolom ini!");
	new Float:distance = floatstr(inputtext);
	if(distance > 10.0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jarak offset terlalu jauh max 10.0!");
	NudgeVal[playerid] = floatstr(inputtext);
	return 1;
}

Dialog:ModshopCatalogMenu(playerid, response, listitem, inputtext[])
{
	if(!response) 
	{
		AccountData[playerid][EditingModshopSlotID] = -1;
		return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
	}

	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di kursi pengemudi!");
	new iteratorid = Vehicle_GetIterID(GetPlayerVehicleID(playerid)),
		slotid = AccountData[playerid][EditingModshopSlotID];

	if(iteratorid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini bukan jenis kendaraan pribadi!");

	switch(listitem)
	{
		case 0:
		{
			Dialog_Show(playerid, "ModshopCatalogDevice", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Modshop Text Size", "Pada perangkat apa anda bermain?\nPC / Laptop\nAndroganja","Pilih", "Batal");
		}
		case 1:
		{
			if(vtData[iteratorid][slotid][vtoy_modelid] != 18667) return ShowTDN(playerid, NOTIFICATION_ERROR, "Objek ini bukan merupakan text");

			Dialog_Show(playerid, "ModshopCatalogTxt", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Modshop Text", "Mohon masukkan text dengan panjang 1 s/d 32 karakter:", 
			"Input", "Batal");
		}
		case 2:
		{
			if(vtData[iteratorid][slotid][vtoy_modelid] != 18667) return ShowTDN(playerid, NOTIFICATION_ERROR, "Objek ini bukan merupakan text");

			Dialog_Show(playerid, "ModshopCatalogSizeTxt", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Modshop Text Size", "Mohon masukkan ukuran font text (hanya angka):", 
			"Input", "Batal");
		}
		case 3:
		{
			if(vtData[iteratorid][slotid][vtoy_modelid] != 18667) return ShowTDN(playerid, NOTIFICATION_ERROR, "Objek ini bukan merupakan text");
			
			static string[512];
			for(new x; x < sizeof(FontNames); x++)
			{
				format(string, sizeof(string), "%s%s\n", string, FontNames[x]);
			}
			Dialog_Show(playerid, "ModshopCatalogFont", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Modshop Font", string, "Pilih", "Batal");
		}
		case 4:
		{
			Dialog_Show(playerid, "ModshopCatalogColor", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Modshop Color", "Masukkan Color (Dalam format ARGB)\n"ORANGE"Contoh: 255 255 0 0 (Untuk warna merah)", "Input", "Batal");
		}
		case 5:
		{
			if(DestroyDynamicObject(vtData[iteratorid][slotid][vtoy_model]))
				vtData[iteratorid][slotid][vtoy_model] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
			
			vtData[iteratorid][slotid][vtoy_modelid] = 0;
			vtData[iteratorid][slotid][vtoy_text][0] = EOS;
			strcopy(vtData[iteratorid][slotid][vtoy_font], "Arial");
			vtData[iteratorid][slotid][vtoy_fontsize] = 11;
			vtData[iteratorid][slotid][vtoy_fontcolor][0] = 255;
			vtData[iteratorid][slotid][vtoy_fontcolor][1] = 0;
			vtData[iteratorid][slotid][vtoy_fontcolor][2] = 0;
			vtData[iteratorid][slotid][vtoy_fontcolor][3] = 0;
			vtData[iteratorid][slotid][vtoy_fontcolor][4] = 0;
			vtData[iteratorid][slotid][vtoy_objectcolor][0] = 255;
			vtData[iteratorid][slotid][vtoy_objectcolor][1] = 0;
			vtData[iteratorid][slotid][vtoy_objectcolor][2] = 0;
			vtData[iteratorid][slotid][vtoy_objectcolor][3] = 0;
			vtData[iteratorid][slotid][vtoy_objectcolor][4] = 0;
			vtData[iteratorid][slotid][vtoy_x] = 0.0;
			vtData[iteratorid][slotid][vtoy_y] = 0.0;
			vtData[iteratorid][slotid][vtoy_z] = 0.0;
			vtData[iteratorid][slotid][vtoy_rx] = 0.0;
			vtData[iteratorid][slotid][vtoy_ry] = 0.0;
			vtData[iteratorid][slotid][vtoy_rz] = 0.0;

			static string[144];
			mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `vtoys` WHERE `ID` = %d", vtData[iteratorid][slotid][vtoy_ID]);
			mysql_pquery(g_SQL, string);

			ReAllocToySlot(iteratorid, slotid);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menghapus vehicle toy tersebut.");

			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		}
	} 
	return 1;
}

Dialog:ModshopCatalogColor(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
	
	new color[4];
	if(sscanf(inputtext, "p< >a<i>[4]", color))
	{
		Dialog_Show(playerid, "ModshopCatalogColor", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Color 1", ""WHITE"Format warna salah!\n"YELLOW"Masukkan Color (Dalam format ARGB)\n"ORANGE"Contoh: 255 255 0 0 (Untuk warna merah)", "Set", "Batal");
		return 1;
	}

	new iteratorid = Vehicle_GetIterID(GetPlayerVehicleID(playerid)),
		slotid = AccountData[playerid][EditingModshopSlotID];

	if(iteratorid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini bukan jenis kendaraan pribadi!");

	if(vtData[iteratorid][slotid][vtoy_modelid] != 18667)
	{
		vtData[iteratorid][slotid][vtoy_objectcolor][0] = color[0];
		vtData[iteratorid][slotid][vtoy_objectcolor][1] = color[1];
		vtData[iteratorid][slotid][vtoy_objectcolor][2] = color[2];
		vtData[iteratorid][slotid][vtoy_objectcolor][3] = color[3];
		vtData[iteratorid][slotid][vtoy_objectcolor][4] = RGBA(color[0], color[1], color[2], color[3]);
		Vehicle_ObjectColorSync(iteratorid, slotid);
	}
	else
	{
		vtData[iteratorid][slotid][vtoy_fontcolor][0] = color[0];
		vtData[iteratorid][slotid][vtoy_fontcolor][1] = color[1];
		vtData[iteratorid][slotid][vtoy_fontcolor][2] = color[2];
		vtData[iteratorid][slotid][vtoy_fontcolor][3] = color[3];
		vtData[iteratorid][slotid][vtoy_fontcolor][4] = RGBA(color[0], color[1], color[2], color[3]);
		Vehicle_ObjectTextSync(iteratorid, slotid);
	}

	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengganti color vehicle toy tersebut.");

	PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
	return 1;
}

Dialog:ModshopCatalogSizeTxt(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	new iteratorid = Vehicle_GetIterID(GetPlayerVehicleID(playerid)),
		slotid = AccountData[playerid][EditingModshopSlotID];

	if(iteratorid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini bukan jenis kendaraan pribadi!");

	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");

	if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya dapat diisi oleh angka!");

	vtData[iteratorid][slotid][vtoy_fontsize] = strval(inputtext);
	Vehicle_ObjectTextSync(iteratorid, slotid);

	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengganti size text vehicle toy tersebut.");

	PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
	return 1;
}

Dialog:ModshopCatalogTxt(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
	new iteratorid = Vehicle_GetIterID(GetPlayerVehicleID(playerid)),
		slotid = AccountData[playerid][EditingModshopSlotID];

	if(iteratorid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini bukan jenis kendaraan pribadi!");

	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");

	if(strfind(inputtext, "{", true) != -1) return Dialog_Show(playerid, "ModshopCatalogTxt", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Uber App", 
		"Error: Anda tidak dapat memasukkan simbol {\n\
		Masukkan text yang ingin dibuat:", "Input", "Batal");

	if(strfind(inputtext, "}", true) != -1) return Dialog_Show(playerid, "ModshopCatalogTxt", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Uber App", 
		"Error: Anda tidak dapat memasukkan simbol }\n\
		Masukkan text yang ingin dibuat:", "Input", "Batal");

	if(strfind(inputtext, "%", true) != -1 || strfind(inputtext, "#", true) != -1)  return Dialog_Show(playerid, "ModshopCatalogTxt", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Uber App", 
		"Error: Anda tidak dapat memasukkan simbol persen!\n\
		Masukkan text yang ingin dibuat:", "Input", "Batal");

	if(strlen(inputtext) > 32) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya dapat diisi maksimal 32 karkater!");
	
	strcopy(vtData[iteratorid][slotid][vtoy_text], inputtext, 144);
	Vehicle_ObjectTextSync(iteratorid, slotid);

	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengganti text vehicle toy tersebut.");

	PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
	return 1;
}

Dialog:ModshopCatalogFont(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(listitem >= sizeof(FontNames)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pilihan tidak valid!");

	new iteratorid = Vehicle_GetIterID(GetPlayerVehicleID(playerid)),
		slotid = AccountData[playerid][EditingModshopSlotID];

	if(iteratorid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini bukan jenis kendaraan pribadi!");

	strcopy(vtData[iteratorid][slotid][vtoy_font], FontNames[listitem], 64);
	Vehicle_ObjectTextSync(iteratorid, slotid);
	
	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengganti font text vehicle toy tersebut.");

	PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
	return 1;
}