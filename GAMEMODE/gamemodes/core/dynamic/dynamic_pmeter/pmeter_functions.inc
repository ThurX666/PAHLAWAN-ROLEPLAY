#include <YSI_Coding\y_hooks>

#define MAX_PMETERS 200

enum E_PMETERS
{
    pmObjectid,
    pmFee[2],
    Float:pmPos[6],
    pmVw,
    pmInt,
    
    //NOT SAVE
    Text3D:pmLabel,
    pmObject,
    pmVehicleid,
    pmModelid,
    pmPlate[64],
    pmDuration
};
new ParkingMeter[MAX_PMETERS][E_PMETERS],
    Iterator:PMeters<MAX_PMETERS>;

GetPMModel(id)
{
    new odkydwja[128], noveh[128];
    if(ParkingMeter[id][pmVehicleid] != INVALID_VEHICLE_ID)
    {
        format(odkydwja, sizeof(odkydwja), "%s", GetVehicleModel(ParkingMeter[id][pmModelid]));
        return odkydwja;
    }
    else
    {
        strcopy(noveh, "None");
    }
    return noveh;
}

GetPMPlate(id)
{
    new onicakwh[128], nevoh[128]; 
    if(ParkingMeter[id][pmVehicleid] != INVALID_VEHICLE_ID)
    {
        format(onicakwh, sizeof(onicakwh), "%s", ParkingMeter[id][pmPlate]);
        return onicakwh;
    }
    else
    {
        strcopy(nevoh, "None");
    }
    return nevoh;
}

GetPMDuration(id)
{
    new omawewaj[128];
    if(ParkingMeter[id][pmDuration] == 0)
    {
        strcopy(omawewaj, ""RED"Expired");
    }
    else
    {
        strcopy(omawewaj, ""GREEN"Valid");
    }
    return omawewaj;
}

PMeter_BeingEdited(id)
{
	if(!Iter_Contains(PMeters, id)) return 0;
	foreach(new i : Player) if(AccountData[i][EditingPMeter] == id) return 1;
	return 0;
}

PMeter_Save(id)
{
	new gpqqery[2048];
	mysql_format(g_SQL, gpqqery, sizeof(gpqqery), "UPDATE `pmeters` SET `pmobj`=%d, `pmfee0`=%d, `pmfee1`=%d, `pmpos0`='%f', `pmpos1`='%f', `pmpos2`='%f', `pmrpos0`='%f', `pmrpos1`='%f', `pmrpos2`='%f', `pmvw`=%d, `pmint`=%d WHERE `ID`=%d",
	ParkingMeter[id][pmObjectid], ParkingMeter[id][pmFee][0], ParkingMeter[id][pmFee][1], ParkingMeter[id][pmPos][0], ParkingMeter[id][pmPos][1], ParkingMeter[id][pmPos][2], 
    ParkingMeter[id][pmPos][3], ParkingMeter[id][pmPos][4], ParkingMeter[id][pmPos][5], ParkingMeter[id][pmVw], ParkingMeter[id][pmInt], id);
	mysql_pquery(g_SQL, gpqqery);
	return 1;
}

PMeter_Rebuild(id)
{
    if(id != -1)
	{
        ParkingMeter[id][pmVehicleid] = INVALID_VEHICLE_ID;
        ParkingMeter[id][pmModelid] = 0;
        ParkingMeter[id][pmPlate][0] = EOS;
        ParkingMeter[id][pmDuration] = 0;
        
		new mstr[512];
		format(mstr,sizeof(mstr),""GREEN"%s Parking Meter\n"WHITE"Vehicle: %s\n"WHITE"Plate: %s\n"WHITE"Duration: %s\n\n"WHITE"Use "YELLOW"'/pmeter' "WHITE"to proceed", GetLocation(ParkingMeter[id][pmPos][0], ParkingMeter[id][pmPos][1], ParkingMeter[id][pmPos][2]), 
        GetPMModel(id), GetPMPlate(id), GetPMDuration(id));

		ParkingMeter[id][pmLabel] = CreateDynamic3DTextLabel(mstr, 0x00ffffa6, ParkingMeter[id][pmPos][0], ParkingMeter[id][pmPos][1], ParkingMeter[id][pmPos][2]+0.6, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, ParkingMeter[id][pmVw], ParkingMeter[id][pmInt], -1, 5.0, -1, 0);
	
        ParkingMeter[id][pmObject] = CreateDynamicObject(ParkingMeter[id][pmObjectid], ParkingMeter[id][pmPos][0], ParkingMeter[id][pmPos][1], ParkingMeter[id][pmPos][2], ParkingMeter[id][pmPos][3], ParkingMeter[id][pmPos][4], ParkingMeter[id][pmPos][5], ParkingMeter[id][pmVw], ParkingMeter[id][pmInt], -1, 200.0, 200.0);
    }
}

PMeter_Refresh(id)
{
    Streamer_SetItemPos(STREAMER_TYPE_OBJECT, ParkingMeter[id][pmObject], ParkingMeter[id][pmPos][0], ParkingMeter[id][pmPos][1], ParkingMeter[id][pmPos][2]);
    Streamer_SetIntData(STREAMER_TYPE_OBJECT, ParkingMeter[id][pmObject], E_STREAMER_WORLD_ID, ParkingMeter[id][pmVw]);
    Streamer_SetIntData(STREAMER_TYPE_OBJECT, ParkingMeter[id][pmObject], E_STREAMER_INTERIOR_ID, ParkingMeter[id][pmInt]);
    
    Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, ParkingMeter[id][pmLabel], ParkingMeter[id][pmPos][0], ParkingMeter[id][pmPos][1], ParkingMeter[id][pmPos][2]+0.6);
    Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, ParkingMeter[id][pmLabel], E_STREAMER_WORLD_ID, ParkingMeter[id][pmVw]);
    Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, ParkingMeter[id][pmLabel], E_STREAMER_INTERIOR_ID, ParkingMeter[id][pmInt]);

    new msttra[512];
	format(mstr,sizeof(mstr),""GREEN"%s Parking Meter\n"WHITE"Vehicle: %s\n"WHITE"Plate: %s\n"WHITE"Duration: %s\n\n"WHITE"Use "YELLOW"'/pmeter' "WHITE"to proceed", GetLocation(ParkingMeter[id][pmPos][0], ParkingMeter[id][pmPos][1], ParkingMeter[id][pmPos][2]), 
    GetPMModel(id), GetPMPlate(id), GetPMDuration(id));
    
    UpdateDynamic3DTextLabelText(ParkingMeter[id][pmLabel], 0x00ffffa6, msttra);
}

forward OnPMeterCreated(playerid, id);
public OnPMeterCreated(playerid, id)
{
	PMeter_Save(id);

	SendClientMessageEx(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Anda berhasil membuat parking meter dengan ID: %d.", id);
    SendStaffMessage(X11_TOMATO1, "AdmCmd: %s membuat parking meter dengan ID: %d.", AccountData[playerid][pAdminname], id);
	return 1;
}

forward LoadParkingMeters();
public LoadParkingMeters()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
   		new lpmid;
		for(new i; i < rows; i++)
		{
  			cache_get_value_name_int(i, "ID", lpmid);
            cache_get_value_name_int(i, "pmobj", ParkingMeter[lpmid][pmObjectid]);
		    cache_get_value_name_int(i, "pmfee0", ParkingMeter[lpmid][pmFee][0]);
            cache_get_value_name_int(i, "pmfee1", ParkingMeter[lpmid][pmFee][1]);
		    cache_get_value_name_float(i, "pmpos0", ParkingMeter[lpmid][pmPos][0]);
		    cache_get_value_name_float(i, "pmpos1", ParkingMeter[lpmid][pmPos][1]);
		    cache_get_value_name_float(i, "pmpos2", ParkingMeter[lpmid][pmPos][2]);
		    cache_get_value_name_float(i, "pmrpos0", ParkingMeter[lpmid][pmPos][3]);
            cache_get_value_name_float(i, "pmrpos1", ParkingMeter[lpmid][pmPos][4]);
            cache_get_value_name_float(i, "pmrpos2", ParkingMeter[lpmid][pmPos][5]);
		    cache_get_value_name_int(i, "pmvw", ParkingMeter[lpmid][pmVw]);
            cache_get_value_name_int(i, "pmint", ParkingMeter[lpmid][pmInt]);
			
			PMeter_Rebuild(lpmid);
			Iter_Add(PMeters, lpmid);
	    }
	    printf("[Dynamic Parking Meter] Jumlah total parking meter yang dimuat: %d.", rows);
	}
}

hook OnPlayerEditDynObject(playerid, STREAMER_TAG_OBJECT: objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if(AccountData[playerid][EditingPMeter] != -1 && Iter_Contains(PMeters, AccountData[playerid][EditingPMeter]))
	{
		if(response == EDIT_RESPONSE_FINAL)
	    {
	        new etid = AccountData[playerid][EditingPMeter];
	        ParkingMeter[etid][pmPos][0] = x;
	        ParkingMeter[etid][pmPos][1] = y;
	        ParkingMeter[etid][pmPos][2] = z;
	        ParkingMeter[etid][pmPos][3] = rx;
	        ParkingMeter[etid][pmPos][4] = ry;
	        ParkingMeter[etid][pmPos][5] = rz;

	        SetDynamicObjectPos(objectid, ParkingMeter[etid][pmPos][0], ParkingMeter[etid][pmPos][1], ParkingMeter[etid][pmPos][2]);
	        SetDynamicObjectRot(objectid, ParkingMeter[etid][pmPos][3], ParkingMeter[etid][pmPos][4], ParkingMeter[etid][pmPos][5]);

            Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, ParkingMeter[etid][pmLabel], ParkingMeter[etid][pmPos][0], ParkingMeter[etid][pmPos][1], ParkingMeter[etid][pmPos][2] + 0.6);

		    PMeter_Save(etid);
	        AccountData[playerid][EditingPMeter] = -1;
	    }

	    if(response == EDIT_RESPONSE_CANCEL)
	    {
	        new etid = AccountData[playerid][EditingPMeter];
	        SetDynamicObjectPos(objectid, ParkingMeter[etid][pmPos][0], ParkingMeter[etid][pmPos][1], ParkingMeter[etid][pmPos][2]);
	        SetDynamicObjectRot(objectid, ParkingMeter[etid][pmPos][3], ParkingMeter[etid][pmPos][4], ParkingMeter[etid][pmPos][5]);
	        AccountData[playerid][EditingPMeter] = -1;
	    }
	}
	return 0;
}

Dialog:ParkingMeter(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        AccountData[playerid][inPMeter] = -1;
        return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    }

    switch(listitem)
    {
        case 0: //12 menit
        {
            if(AccountData[playerid][inPMeter] == -1)
            {
                PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0); 
                return ErrorMsg(playerid, "Anda tidak berada di Parking Meter manapun, gunakan '/pmeter' untuk akses meter!");
            }

            if(ParkingMeter[AccountData[playerid][inPMeter]][pmDuration] > 0 || ParkingMeter[AccountData[playerid][inPMeter]][pmVehicleid] != INVALID_VEHICLE_ID)
            {
                PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
                return ErrorMsg(playerid, "Parking Meter sedang digunakan oleh player lain!");
            }

            if(!IsValidVehicle(AccountData[playerid][PMeterVeh]))
            {
                PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
                return ErrorMsg(playerid, "Invalid vehicle id, gunakan '/mv' untuk melihat vehid!");
            }

            if(!NearVehicle(playerid, AccountData[playerid][PMeterVeh], 3.0))
            {
                PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
                return ErrorMsg(playerid, "Anda tidak dekat dengan kendaraan (vehicle id) tersebut!");
            }

            if(GetPlayerMoney(playerid) < ParkingMeter[AccountData[playerid][inPMeter]][pmFee][0])
            {
                PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0); 
                return ErrorMsg(playerid, "Not enough cash!");
            }

            foreach(new i : PVehicles)			
            {
                if(AccountData[playerid][PMeterVeh] == pvData[i][cVeh])
                {
                    if(pvData[i][cOwner] == AccountData[playerid][pID])
                    {
                        ParkingMeter[AccountData[playerid][inPMeter]][pmVehicleid] = AccountData[playerid][PMeterVeh];
                        ParkingMeter[AccountData[playerid][inPMeter]][pmDuration] = 720;

                        GivePlayerMoneyEx(playerid, -ParkingMeter[AccountData[playerid][inPMeter]][pmFee][0]);

                        PMeter_Refresh(AccountData[playerid][inPMeter]);

                        SendClientMessageEx(playerid, X11_LIGHTBLUE, "PARKING: "WHITE"You've managed to park your "ROYALBLUE"%s (VID: %d) "WHITE"for "YELLOW"12 minutes.", GetVehicleName(AccountData[playerid][PMeterVeh]), AccountData[playerid][PMeterVeh]);
                    
                        AccountData[playerid][inPMeter] = -1;
                        AccountData[playerid][PMeterVeh] = INVALID_VEHICLE_ID;
                    }
                    else
                    {
                        PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0); 
                        return ErrorMsg(playerid, "ID kendaraan tersebut bukan milik anda! gunakan '/mv' untuk mencari ID!");
                    }
                }
            }
        }
        case 1: //24 menit
        {
            if(AccountData[playerid][inPMeter] == -1)
            {
                PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0); 
                return ErrorMsg(playerid, "Anda tidak berada di Parking Meter manapun, gunakan '/pmeter' untuk akses meter!");
            }

            if(ParkingMeter[AccountData[playerid][inPMeter]][pmDuration] > 0 || ParkingMeter[AccountData[playerid][inPMeter]][pmVehicleid] != INVALID_VEHICLE_ID)
            {
                PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
                return ErrorMsg(playerid, "Parking Meter sedang digunakan oleh player lain!");
            }

            if(!IsValidVehicle(AccountData[playerid][PMeterVeh]))
            {
                PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
                return ErrorMsg(playerid, "Invalid vehicle id, gunakan '/mv' untuk melihat vehid!");
            }

            if(!NearVehicle(playerid, AccountData[playerid][PMeterVeh], 3.0))
            {
                PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
                return ErrorMsg(playerid, "Anda tidak dekat dengan kendaraan (vehicle id) tersebut!");
            }

            if(GetPlayerMoney(playerid) < ParkingMeter[AccountData[playerid][inPMeter]][pmFee][1])
            {
                PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0); 
                return ErrorMsg(playerid, "Not enough cash!");
            }

            foreach(new i : PVehicles)			
            {
                if(AccountData[playerid][PMeterVeh] == pvData[i][cVeh])
                {
                    if(pvData[i][cOwner] == AccountData[playerid][pID])
                    {
                        ParkingMeter[AccountData[playerid][inPMeter]][pmVehicleid] = AccountData[playerid][PMeterVeh];
                        ParkingMeter[AccountData[playerid][inPMeter]][pmDuration] = 1440;

                        GivePlayerMoneyEx(playerid, -ParkingMeter[AccountData[playerid][inPMeter]][pmFee][1]);

                        PMeter_Refresh(AccountData[playerid][inPMeter]);

                        SendClientMessageEx(playerid, X11_LIGHTBLUE, "PARKING: "WHITE"You've managed to park your "ROYALBLUE"%s (VID: %d) "WHITE"for "YELLOW"24 minutes.", GetVehicleName(AccountData[playerid][PMeterVeh]), AccountData[playerid][PMeterVeh]);

                        AccountData[playerid][inPMeter] = -1;
                        AccountData[playerid][PMeterVeh] = INVALID_VEHICLE_ID;
                    }
                    else
                    {
                        PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0); 
                        return ErrorMsg(playerid, "ID kendaraan tersebut bukan milik anda! gunakan '/mv' untuk mencari ID!");
                    }
                }
            }
        }
    }
    return 1;
}

task PMeterDuration[1000]()
{
    foreach(new pmid : PMeters)
    {
        if(ParkingMeter[pmid][pmVehicleid] != INVALID_VEHICLE_ID)
        {
            if(ParkingMeter[pmid][pmDuration] != 0)
            {
                if(ParkingMeter[pmid][pmDuration] > 0)
                {
                    ParkingMeter[pmid][pmDuration]--;
                }
                else
                {
                    ParkingMeter[pmid][pmDuration] = 0;

                    PMeter_Refresh(pmid);
                }
            }

            new Float:vehdistancia = GetVehicleDistanceFromPoint(ParkingMeter[pmid][pmVehicleid], ParkingMeter[pmid][pmPos][0], ParkingMeter[pmid][pmPos][1], ParkingMeter[pmid][pmPos][2]);

            if(vehdistancia >= 5.5)
            {
                ParkingMeter[pmid][pmVehicleid] = INVALID_VEHICLE_ID;
                ParkingMeter[pmid][pmDuration] = 0;

                PMeter_Refresh(pmid);
            }
        }
    }
}