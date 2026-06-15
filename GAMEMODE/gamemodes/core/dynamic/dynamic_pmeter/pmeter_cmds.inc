YCMD:createpmeter(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9){
        PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		return PermissionError(playerid);}

    new type;
    if (sscanf(params, "d", type))
	{
        Usage(playerid, "/createpmeter [type]");
	    NUsage(playerid, "1. Merah | 2. Silver");
		return 1;
	}

    if (type < 1 || type > 2)
	    {PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0); return Error(playerid, "Pilih jenis 1 atau 2!");}

    new pmtid = Iter_Free(PMeters), query[248];
	if(pmtid == -1) {PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0); return Error(playerid, "Jumlah dynamic parking meter sudah maksimal!");}

	GetPlayerPos(playerid, ParkingMeter[pmtid][pmPos][0], ParkingMeter[pmtid][pmPos][1], ParkingMeter[pmtid][pmPos][2]);
    ParkingMeter[pmtid][pmPos][3] = 0.0;
    ParkingMeter[pmtid][pmPos][4] = 0.0;
    ParkingMeter[pmtid][pmPos][5] = 0.0;

    switch (type) 
    {
        case 1: ParkingMeter[pmtid][pmObjectid] = 1270;
		case 2: ParkingMeter[pmtid][pmObjectid] = 1269;
    }

	ParkingMeter[pmtid][pmVw] = GetPlayerVirtualWorld(playerid);
	ParkingMeter[pmtid][pmInt] = GetPlayerInterior(playerid);
	ParkingMeter[pmtid][pmVehicleid] = INVALID_VEHICLE_ID;
    ParkingMeter[pmtid][pmDuration] = 0;
    ParkingMeter[pmtid][pmFee][0] = 25;
    ParkingMeter[pmtid][pmFee][1] = 50;
	
    PMeter_Rebuild(pmtid);
	Iter_Add(PMeters, pmtid);

    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO pmeters SET ID=%d, pmobj='%d', pmfee0='%d', pmfee1='%d', pmpos0='%f', pmpos1='%f', pmpos2='%f',  pmrpos0='%f', pmrpos1='%f', pmrpos2='%f', pmvw='%d', pmint='%d'",
	pmtid, ParkingMeter[pmtid][pmObjectid], ParkingMeter[pmtid][pmFee][0], ParkingMeter[pmtid][pmFee][1], ParkingMeter[pmtid][pmPos][0], ParkingMeter[pmtid][pmPos][1], ParkingMeter[pmtid][pmPos][2], 
    ParkingMeter[pmtid][pmPos][3], ParkingMeter[pmtid][pmPos][4], ParkingMeter[pmtid][pmPos][5], ParkingMeter[pmtid][pmVw], ParkingMeter[pmtid][pmInt]);
	mysql_pquery(g_SQL, query, "OnPMeterCreated", "ii", playerid, pmtid);
    return 1;
}

YCMD:gotopmeter(playerid, params[], help)
{
	new gsid;
	if(AccountData[playerid][pAdmin] < 3)
    {
        PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
        return PermissionError(playerid);
    }
		
	if(sscanf(params, "d", gsid))
		return Usage(playerid, "/gotopmeter [id]");
		
	if(!Iter_Contains(PMeters, gsid))
    {
        PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
        return Error(playerid, "ID Parking Meter tersebut tidak valid!");
    }
	SetPlayerPositionEx(playerid, ParkingMeter[gsid][pmPos][0], ParkingMeter[gsid][pmPos][1], ParkingMeter[gsid][pmPos][2], 2.0);
    SetPlayerVirtualWorld(playerid, ParkingMeter[gsid][pmVw]);
	SetPlayerInterior(playerid, ParkingMeter[gsid][pmInt]);
	AccountData[playerid][pInBiz] = -1;
	AccountData[playerid][pInDoor] = -1;
	AccountData[playerid][pInHouse] = -1;
	Servers(playerid, "Anda berhasil teleportasi ke parking meter ID: %d.", gsid);
	return 1;
}

YCMD:editpmeter(playerid, params[], help)
{
    static
        gsid,
        type[24],
        string[128];

    if(AccountData[playerid][pAdmin] < 9)
        {PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0); return PermissionError(playerid);}

    if(sscanf(params, "ds[24]S()[128]", gsid, type, string))
    {
        Usage(playerid, "/editpmeter [id] [type]");
        NUsage(playerid, "pos, fee");
        return 1;
    }
	
    if(!Iter_Contains(PMeters, gsid)) {PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0); return Error(playerid, "ID Parking Meter tersebut tidak valid!");}

    if(!strcmp(type, "pos", true))
    {
        if(AccountData[playerid][EditingPMeter] != -1) {PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0); return Error(playerid, "Anda sedang berada dalam mode editing!");}

        if(!IsPlayerInRangeOfPoint(playerid, 30.0, ParkingMeter[gsid][pmPos][0], ParkingMeter[gsid][pmPos][1], ParkingMeter[gsid][pmPos][2])) {PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0); return Error(playerid, "Anda tidak dekat dengan dynamic Parking Meter manapun!");}
        AccountData[playerid][EditingPMeter] = gsid;
        EditDynamicObject(playerid, ParkingMeter[gsid][pmObject]);
    }
    else if(!strcmp(type, "fee", true))
    {
        new capacity, slot;

        if(sscanf(string, "dd", slot, capacity))
            return Usage(playerid, "/editpmeter [id] [fee] [slot 0-1] [ammount]");

        if(slot < 0 || slot > 1)
            {PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0); return Error(playerid, "Slot tidak boleh kurang dari 0 dan lebih dari 1!");}

        if(capacity < 1)
            {PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0); return Error(playerid, "Slot tidak boleh kurang dari 1!");}

        ParkingMeter[gsid][pmFee][slot] = capacity;
        PMeter_Save(gsid);
		PMeter_Refresh(gsid);

        SendStaffMessage(X11_TOMATO1, "AdmCmd: %s menetapkan fee slot %d untuk parking meter ID: %d.", AccountData[playerid][pAdminname], slot, gsid);
    }
    return 1;
}

YCMD:pmeter(playerid, params[], help)
{
    if(IsPlayerInAnyVehicle(playerid) || GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
    {
        PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
        return Error(playerid, "Anda harus turun dari kendaraan!");
    }

    static pmid, vhid;

    if(sscanf(params, "dd", pmid, vhid))
    {
        Usage(playerid, "/pmeter [nomor DP/parking meter ID] [vehid]");
        NotesMsg(playerid, "Gunakan /mv untuk mencari vehid!");
        return 1;
    }

    if(!Iter_Contains(PMeters, pmid))
    {
        PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
        return Error(playerid, "ID Parking Meter tersebut tidak valid!");
    }

    if(!IsPlayerInRangeOfPoint(playerid, 3.0, ParkingMeter[pmid][pmPos][0], ParkingMeter[pmid][pmPos][1], ParkingMeter[pmid][pmPos][2]))
    {
        PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
        return Error(playerid, "Anda tidak dekat dengan Parking Meter tersebut!");
    }

    if(ParkingMeter[pmid][pmDuration] > 0 || ParkingMeter[pmid][pmVehicleid] != INVALID_VEHICLE_ID)
    {
        PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
        return Error(playerid, "Parking Meter sedang digunakan oleh player lain!");
    }

    if(!IsValidVehicle(vhid))
    {
        PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
        return Error(playerid, "Invalid vehicle id, gunakan '/mv' untuk melihat vehid!");
    }

    if(!NearVehicle(playerid, vhid, 3.0))
    {
        PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
        return Error(playerid, "Anda tidak dekat dengan kendaraan (vehicle id) tersebut!");
    }

    foreach(new i : PVehicles)			
	{
		if(vhid == pvData[i][cVeh])
		{
            if(pvData[i][cOwner] == AccountData[playerid][pID])
            {
                AccountData[playerid][inPMeter] = pmid;
                AccountData[playerid][PMeterVeh] = vhid;

                static awjdawu[128], juhaiwj[128];
                format(awjdawu, sizeof(awjdawu), ""GREEN"%s Parking Meter: "YELLOW"%d", GetLocation(ParkingMeter[pmid][pmPos][0], ParkingMeter[pmid][pmPos][1], ParkingMeter[pmid][pmPos][2]), pmid);
                
                format(juhaiwj, sizeof(juhaiwj), "Duration\tCost\n\
                "WHITE"12 Min\t"GREEN"%s\n\
                "WHITE"24 Min\t"GREEN"%s\n\
                ", FormatMoney(ParkingMeter[pmid][pmFee][0]), FormatMoney(ParkingMeter[pmid][pmFee][1]));
                
                Dialog_Show(playerid, "ParkingMeter", DIALOG_STYLE_TABLIST_HEADERS, awjdawu, juhaiwj, "Pilih", "Batal");
            }
            else
            {
                PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0); 
                return Error(playerid, "ID kendaraan tersebut bukan milik anda! gunakan '/mv' untuk mencari ID!");
            }
        }
    }
    return 1;
}

YCMD:deletepmeter(playerid, params[], help)
{
    static
        gpid;

    if(AccountData[playerid][pAdmin] < 9){
        PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		return PermissionError(playerid);}

    if(sscanf(params, "d", gpid))
    {
        return Usage(playerid, "/deletepmeter [id]");
    }

    if(PMeter_BeingEdited(gpid)) {PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0); return Error(playerid, "ID Parking Meter tersebut sedang diedit oleh admin lainnya!");}

    DestroyDynamic3DTextLabel(ParkingMeter[gpid][pmLabel]);
    DestroyDynamicObject(ParkingMeter[gpid][pmObject]);

    ParkingMeter[gpid][pmObjectid] = INVALID_OBJECT_ID;

    ParkingMeter[gpid][pmFee][0] = 0;
    ParkingMeter[gpid][pmFee][1] = 0;

    ParkingMeter[gpid][pmPos][0] = 0;
    ParkingMeter[gpid][pmPos][1] = 0;
    ParkingMeter[gpid][pmPos][2] = 0;
    ParkingMeter[gpid][pmPos][3] = 0;
    ParkingMeter[gpid][pmPos][4] = 0;
    ParkingMeter[gpid][pmPos][5] = 0;

    ParkingMeter[gpid][pmVw] = 0;
    ParkingMeter[gpid][pmInt] = 0;

    ParkingMeter[gpid][pmVehicleid] = INVALID_VEHICLE_ID;
    ParkingMeter[gpid][pmDuration] = 0;
    
    ParkingMeter[gpid][pmLabel] = Text3D: INVALID_3DTEXT_ID;
    
    Iter_Remove(PMeters, gpid);
    new query[128];
    mysql_format(g_SQL, query, sizeof(query), "DELETE FROM pmeters WHERE ID=%d", gpid);
    mysql_pquery(g_SQL, query);
    SendStaffMessage(X11_TOMATO1, "AdmCmd: %s telah menghapus parking meter ID: %d.", AccountData[playerid][pAdminname], gpid);
    return 1;
}

YCMD:cekpark(playerid, params[], help)
{
    static gpid;
    if(sscanf(params, "d", gpid))
    {
        return Usage(playerid, "/cekpark [id]");
    }

    Info(playerid, "Sisa durasi untuk id %d adalah %d lagi", gpid, ParkingMeter[gpid][pmDuration]);
    return 1;
}