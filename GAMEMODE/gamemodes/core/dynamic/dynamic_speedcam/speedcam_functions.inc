#include <YSI_Coding\y_hooks>

#define MAX_SPEEDCAM 1000

enum E_SPEEDCAM
{
    Float:scX,
    Float:scY,
    Float:scZ,
    Float:scRX,
    Float:scRY,
    Float:scRZ,
    scVw,
    scInt,
    Float:scSpeed,

    //not save
    STREAMER_TAG_OBJECT:scObject,
    STREAMER_TAG_3D_TEXT_LABEL:scLabel,

    scVehModel,
    Float:scVehSpeed,
    scVehPlate,
    scVehID
};
new SCamData[MAX_SPEEDCAM][E_SPEEDCAM],
    Iterator:SpeedCams<MAX_SPEEDCAM>;

SpeedCam_Save(spid)
{
	static trqqry[600];
	mysql_format(g_SQL, trqqry, sizeof(trqqry), "UPDATE `speedcam` SET `scvw`=%d, `scint`=%d, `scx`='%f', `scy`='%f', `scz`='%f', `scrx`='%f', `scry`='%f', `scrz`='%f', `scspeed`='%f' WHERE `ID`=%d",
	SCamData[spid][scVw], SCamData[spid][scInt], SCamData[spid][scX], SCamData[spid][scY], SCamData[spid][scZ], SCamData[spid][scRX], SCamData[spid][scRY], SCamData[spid][scRZ], SCamData[spid][scSpeed], spid);
	mysql_pquery(g_SQL, trqqry);
	return 1;
}

SpeedCam_Rebuild(spid)
{
    if(spid != -1)
	{
        SCamData[spid][scVehID] = INVALID_VEHICLE_ID;
        SCamData[spid][scVehSpeed] = 0.0;
        
        if(DestroyDynamicObject(SCamData[spid][scObject]))
            SCamData[spid][scObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
        if(DestroyDynamic3DTextLabel(SCamData[spid][scLabel]))
            SCamData[spid][scLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        SCamData[spid][scObject] = CreateDynamicObject(18880, SCamData[spid][scX], SCamData[spid][scY], SCamData[spid][scZ], SCamData[spid][scRX], SCamData[spid][scRY], SCamData[spid][scRZ], SCamData[spid][scVw], SCamData[spid][scInt], -1, 200.00, 200.00, -1);
        
        new mstr[512];
		format(mstr,sizeof(mstr),"[DC:%d]\n"WHITE"Loc: "GREEN"%s\n"WHITE"Speed Limit: "YELLOW"%.0f MPH\n"WHITE"Plate: "YELLOW"%s\n"WHITE"Model: "CYAN"%s\n"WHITE"Speed Captured: "RED"%.0f MPH", spid, GetLocation(SCamData[spid][scX], SCamData[spid][scY], SCamData[spid][scZ]),
        SCamData[spid][scSpeed], GetSCPlate(spid), GetSCModel(spid), SCamData[spid][scVehSpeed]);
        SCamData[spid][scLabel] = CreateDynamic3DTextLabel(mstr, 0xffffffff, SCamData[spid][scX], SCamData[spid][scY], SCamData[spid][scZ]+3.0, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, SCamData[spid][scVw], SCamData[spid][scInt], -1, 10.0, -1, 0);
	}
}

SpeedCam_Refresh(spid)
{
    Streamer_SetItemPos(STREAMER_TYPE_OBJECT, SCamData[spid][scObject], SCamData[spid][scX], SCamData[spid][scY], SCamData[spid][scZ]);
    Streamer_SetIntData(STREAMER_TYPE_OBJECT, SCamData[spid][scObject], E_STREAMER_WORLD_ID, SCamData[spid][scVw]);
    Streamer_SetIntData(STREAMER_TYPE_OBJECT, SCamData[spid][scObject], E_STREAMER_INTERIOR_ID, SCamData[spid][scInt]);
    
    Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, SCamData[spid][scLabel], SCamData[spid][scX], SCamData[spid][scY], SCamData[spid][scZ]+3.0);
    Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, SCamData[spid][scLabel], E_STREAMER_WORLD_ID, SCamData[spid][scVw]);
    Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, SCamData[spid][scLabel], E_STREAMER_INTERIOR_ID, SCamData[spid][scInt]);

    new msttra[512];
	format(msttra,sizeof(msttra),"[DC:%d]\n"WHITE"Loc: "GREEN"%s\n"WHITE"Speed Limit: "YELLOW"%.0f MPH\n"WHITE"Plate: "YELLOW"%s\n"WHITE"Model: "CYAN"%s\n"WHITE"Speed Captured: "RED"%.0f MPH", spid, GetLocation(SCamData[spid][scX], SCamData[spid][scY], SCamData[spid][scZ]),
    SCamData[spid][scSpeed], GetSCPlate(spid), GetSCModel(spid), SCamData[spid][scVehSpeed]);
    
    UpdateDynamic3DTextLabelText(SCamData[spid][scLabel], 0x00ffffff, msttra);
}

SpeedCam_Nearest(playerid)
{
    foreach(new i : SpeedCams) if (IsPlayerInRangeOfPoint(playerid, 17.85, SCamData[i][scX], SCamData[i][scY], SCamData[i][scZ]))
	{
		if (GetPlayerInterior(playerid) == SCamData[i][scInt] && GetPlayerVirtualWorld(playerid) == SCamData[i][scVw])
			return i;
	}
	return -1;
}

GetSCModel(id)
{
    new odkydwja[128], noveh[128];
    if(SCamData[id][scVehID] != INVALID_VEHICLE_ID)
    {
        format(odkydwja, sizeof(odkydwja), "%s", GetVehicleName(SCamData[id][scVehID]));
        return odkydwja;
    }
    else
    {
        strcopy(noveh, "None");
    }
    return noveh;
}

GetSCPlate(id)
{
    new onicakwh[128], nevoh[128]; 
    if(SCamData[id][scVehID] != INVALID_VEHICLE_ID)
    {
        foreach(new i : PvtVehicles)			
        {
            if(SCamData[id][scVehID] == PlayerVehicle[i][pVehPhysic])
            {
                format(onicakwh, sizeof(onicakwh), "%s", PlayerVehicle[i][pVehPlate]);
                return onicakwh;
            }
        }
    }
    else
    {
        strcopy(nevoh, "None");
    }
    return nevoh;
}

SpeedCam_BeingEdited(spid)
{
	if(!Iter_Contains(SpeedCams, spid)) return 0;
	foreach(new i : Player) if(AccountData[i][EditingSCamID] == spid) return 1;
	return 0;
}

task CheckingSCam[1555]() 
{
    foreach(new i : Player) if(AccountData[i][pSpawned])
    {
        if(IsPlayerInAnyVehicle(i))
        {
            new id = SpeedCam_Nearest(i), 
            carid = INVALID_VEHICLE_ID,
            Float:vspeed;

            if(id != -1) //jika di dekat speed cam
            {
                if((carid = Vehicle_Nearest(i)) != INVALID_VEHICLE_ID)
                {
                    vspeed = EVF::GetVehicleSpeed(PlayerVehicle[carid][pVehPhysic]);
                    if(vspeed > SCamData[id][scSpeed])
                    {
                        SCamData[id][scVehSpeed] = vspeed;
                        SCamData[id][scVehID] = PlayerVehicle[carid][pVehPhysic];

                        SpeedCam_Refresh(id);

                        // foreach(new p : LSPDDuty) if(IsPlayerInVehicle(p, PlayerFactionVehicle[p][FACTION_LSPD]))
                        // {
                        //     SendClientMessageEx(p, X11_BLUE, "[SPEEDCAM] "YELLOW"Vehicle: [%s] Plate: [%s] Speed: [%.0f/%.0f] Loc: |%s| Heading: [%s]", GetSCModel(id), GetSCPlate(id), SCamData[id][scVehSpeed], SCamData[id][scSpeed], GetLocation(SCamData[id][scX], SCamData[id][scY], SCamData[id][scZ]), GetVehicleFacingCompass(PlayerVehicle[carid][pVehPhysic]));
                        // }
                    }
                }
            }
        }
    }
    return 1;
}

hook OnPlayerEditDynObject(playerid, STREAMER_TAG_OBJECT: objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if(AccountData[playerid][EditingSCamID] != -1 && Iter_Contains(SpeedCams, (AccountData[playerid][EditingSCamID])))
	{
		if(response == EDIT_RESPONSE_FINAL)
	    {
	        new spid = AccountData[playerid][EditingSCamID];
	        SCamData[spid][scX] = x;
	        SCamData[spid][scY] = y;
	        SCamData[spid][scZ] = z;
	        SCamData[spid][scRX] = rx;
	        SCamData[spid][scRY] = ry;
	        SCamData[spid][scRZ] = rz;

	        SetDynamicObjectPos(objectid, SCamData[spid][scX], SCamData[spid][scY], SCamData[spid][scZ]);
	        SetDynamicObjectRot(objectid, SCamData[spid][scRX], SCamData[spid][scRY], SCamData[spid][scRZ]);

		    Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, SCamData[spid][scLabel], SCamData[spid][scX], SCamData[spid][scY], SCamData[spid][scZ]+3.0);

		    SpeedCam_Save(spid);
	        AccountData[playerid][EditingSCamID] = -1;
	    }

	    if(response == EDIT_RESPONSE_CANCEL)
	    {
	        new spid = AccountData[playerid][EditingSCamID];
	        SetDynamicObjectPos(objectid, SCamData[spid][scX], SCamData[spid][scY], SCamData[spid][scZ]);
	        SetDynamicObjectRot(objectid, SCamData[spid][scRX], SCamData[spid][scRY], SCamData[spid][scRZ]);
	        AccountData[playerid][EditingSCamID] = -1;
	    }
	}
	return 0;
}

forward OnSpeedCamCreated(playerid, spid);
public OnSpeedCamCreated(playerid, spid)
{
	SpeedCam_Save(spid);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has created Speed Cam ID: %d.", AccountData[playerid][pAdminname], spid);
	return 1;
}

forward LoadSpeedCam();
public LoadSpeedCam()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
   		new spid;

		for(new i; i < rows; i++)
		{
  			cache_get_value_name_int(i, "ID", spid);
		    cache_get_value_name_int(i, "scvw", SCamData[spid][scVw]);
		    cache_get_value_name_int(i, "scint", SCamData[spid][scInt]);
		    cache_get_value_name_float(i, "scx", SCamData[spid][scX]);
			cache_get_value_name_float(i, "scy", SCamData[spid][scY]);
			cache_get_value_name_float(i, "scz", SCamData[spid][scZ]);
			
			cache_get_value_name_float(i, "scrx", SCamData[spid][scRX]);
			cache_get_value_name_float(i, "scry", SCamData[spid][scRY]);
			cache_get_value_name_float(i, "scrz", SCamData[spid][scRZ]);

            cache_get_value_name_float(i, "scspeed", SCamData[spid][scSpeed]);
			
			Iter_Add(SpeedCams, spid);
			SpeedCam_Rebuild(spid);
	    }
	    printf("[Dynamic Speed Cam] Total dynamic speed cam loaded: %d.", rows);
	}
}