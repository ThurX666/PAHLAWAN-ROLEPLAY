#include <YSI_Coding\y_hooks>

#define MAX_GARAGE  100

enum e_GarageDetails
{
    //save
    pgName[64],

    //red cp
    Float:pgRedPos[3],
    pgRedWorld,
    pgRedInterior,

    //spawn pos
    Float:pgSpawnPos[4],
    pgSpawnWorld,
    pgSpawnInterior,

    //not save
    STREAMER_TAG_OBJECT:pgRedObjid,
    STREAMER_TAG_AREA:pgRedArea,

    STREAMER_TAG_MAP_ICON:pgMapIcon,

    STREAMER_TAG_PICKUP:pgPickup,
    STREAMER_TAG_3D_TEXT_LABEL:pgLabel
};
new PublicGarage[MAX_GARAGE][e_GarageDetails],
    Iterator:PGarages<MAX_GARAGE>;

PublicGarage_Nearest(playerid)
{
    foreach(new i : PGarages) if (IsPlayerInRangeOfPoint(playerid, 2.5, PublicGarage[i][pgRedPos][0], PublicGarage[i][pgRedPos][1], PublicGarage[i][pgRedPos][2]))
	{
		if (GetPlayerInterior(playerid) == PublicGarage[i][pgRedInterior] && GetPlayerVirtualWorld(playerid) == PublicGarage[i][pgRedWorld])
			return i;
	}
	return -1;
}

GetGarageNearestFromPlayer(playerid)
{
    foreach(new x : PGarages)
    {
        if(PublicGarage[x][pgRedInterior] == 0 && PublicGarage[x][pgRedWorld] == 0)
        {
            if(IsPlayerInRangeOfPoint(playerid, 600.0, PublicGarage[x][pgRedPos][0], PublicGarage[x][pgRedPos][1], PublicGarage[x][pgRedPos][2]))
            {
                if(DestroyDynamicRaceCP(AccountData[playerid][pGPSCP]))
                    AccountData[playerid][pGPSCP] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

                AccountData[playerid][pUsingGPS] = true;
                AccountData[playerid][pGPSCP] = CreateDynamicRaceCP(1, PublicGarage[x][pgRedPos][0], PublicGarage[x][pgRedPos][1], PublicGarage[x][pgRedPos][2], PublicGarage[x][pgRedPos][0], PublicGarage[x][pgRedPos][1], PublicGarage[x][pgRedPos][2], 3.5, 0, 0, playerid, 10000.00, -1, 0);
                ShowTDN(playerid, NOTIFICATION_WARNING, "Mohon ikuti checkpoint di map!");
                return 1;
            }
        }
    }
    ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada garkot terdekat dari posisi anda!");
    return 1;
}

PublicGarage_Refresh(gpid)
{
    if(gpid != -1)
    {
        Streamer_SetItemPos(STREAMER_TYPE_OBJECT, PublicGarage[gpid][pgRedObjid], PublicGarage[gpid][pgRedPos][0], PublicGarage[gpid][pgRedPos][1], PublicGarage[gpid][pgRedPos][2] - 0.9);
        Streamer_SetIntData(STREAMER_TYPE_OBJECT, PublicGarage[gpid][pgRedObjid], E_STREAMER_WORLD_ID, PublicGarage[gpid][pgRedWorld]);
        Streamer_SetIntData(STREAMER_TYPE_OBJECT, PublicGarage[gpid][pgRedObjid], E_STREAMER_INTERIOR_ID, PublicGarage[gpid][pgRedInterior]);

        Streamer_SetItemPos(STREAMER_TYPE_AREA, PublicGarage[gpid][pgRedArea], PublicGarage[gpid][pgRedPos][0], PublicGarage[gpid][pgRedPos][1], PublicGarage[gpid][pgRedPos][2]);
        Streamer_SetIntData(STREAMER_TYPE_AREA, PublicGarage[gpid][pgRedArea], E_STREAMER_WORLD_ID, PublicGarage[gpid][pgRedWorld]);
        Streamer_SetIntData(STREAMER_TYPE_AREA, PublicGarage[gpid][pgRedArea], E_STREAMER_INTERIOR_ID, PublicGarage[gpid][pgRedInterior]);

        Streamer_SetItemPos(STREAMER_TYPE_MAP_ICON, PublicGarage[gpid][pgMapIcon], PublicGarage[gpid][pgRedPos][0], PublicGarage[gpid][pgRedPos][1], PublicGarage[gpid][pgRedPos][2]);
        Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, PublicGarage[gpid][pgMapIcon], E_STREAMER_WORLD_ID, PublicGarage[gpid][pgRedWorld]);
        Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, PublicGarage[gpid][pgMapIcon], E_STREAMER_INTERIOR_ID, PublicGarage[gpid][pgRedInterior]);
        
        Streamer_SetItemPos(STREAMER_TYPE_PICKUP, PublicGarage[gpid][pgPickup], PublicGarage[gpid][pgRedPos][0], PublicGarage[gpid][pgRedPos][1], PublicGarage[gpid][pgRedPos][2]-0.05);
        Streamer_SetIntData(STREAMER_TYPE_PICKUP, PublicGarage[gpid][pgPickup], E_STREAMER_WORLD_ID, PublicGarage[gpid][pgRedWorld]);
        Streamer_SetIntData(STREAMER_TYPE_PICKUP, PublicGarage[gpid][pgPickup], E_STREAMER_INTERIOR_ID, PublicGarage[gpid][pgRedInterior]);
        
        Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, PublicGarage[gpid][pgLabel], PublicGarage[gpid][pgRedPos][0], PublicGarage[gpid][pgRedPos][1], PublicGarage[gpid][pgRedPos][2]+0.30);
        Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, PublicGarage[gpid][pgLabel], E_STREAMER_WORLD_ID, PublicGarage[gpid][pgRedWorld]);
        Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, PublicGarage[gpid][pgLabel], E_STREAMER_INTERIOR_ID, PublicGarage[gpid][pgRedInterior]);

        static strrs[144];
        format(strrs, sizeof(strrs), "[ "WHITE"(Garkot): "YELLOW"%s "GREEN"]", PublicGarage[gpid][pgName]);
        UpdateDynamic3DTextLabelText(PublicGarage[gpid][pgLabel], Y_GREEN, strrs);
    }
}

PublicGarage_Rebuild(gpid)
{
	if(gpid != -1)
	{
        if(DestroyDynamicObject(PublicGarage[gpid][pgRedObjid]))
		    PublicGarage[gpid][pgRedObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

        if(DestroyDynamicArea(PublicGarage[gpid][pgRedArea]))
            PublicGarage[gpid][pgRedArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

        if(DestroyDynamicMapIcon(PublicGarage[gpid][pgMapIcon]))
            PublicGarage[gpid][pgMapIcon] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        if(DestroyDynamicPickup(PublicGarage[gpid][pgPickup]))
            PublicGarage[gpid][pgPickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;
        
        if(DestroyDynamic3DTextLabel(PublicGarage[gpid][pgLabel]))
            PublicGarage[gpid][pgLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        PublicGarage[gpid][pgRedObjid] = CreateDynamicObject(1316, PublicGarage[gpid][pgRedPos][0], PublicGarage[gpid][pgRedPos][1], PublicGarage[gpid][pgRedPos][2] - 0.9, 0.0, 0.0, 0.0, PublicGarage[gpid][pgRedWorld], PublicGarage[gpid][pgRedInterior], -1, 100.00, 100.00, -1);
        SetDynamicObjectMaterial(PublicGarage[gpid][pgRedObjid], 0, 18646, "matcolours", "white", 0x9900ff91);
        PublicGarage[gpid][pgRedArea] = CreateDynamicSphere(PublicGarage[gpid][pgRedPos][0], PublicGarage[gpid][pgRedPos][1], PublicGarage[gpid][pgRedPos][2], 3.5, PublicGarage[gpid][pgRedWorld], PublicGarage[gpid][pgRedInterior], -1);

        PublicGarage[gpid][pgMapIcon] = CreateDynamicMapIcon(PublicGarage[gpid][pgRedPos][0], PublicGarage[gpid][pgRedPos][1], PublicGarage[gpid][pgRedPos][2], 55, 0, PublicGarage[gpid][pgRedWorld], PublicGarage[gpid][pgRedInterior], -1, 1000.00, MAPICON_LOCAL, -1, 0);

        PublicGarage[gpid][pgPickup] = CreateDynamicPickup(2485, 23, PublicGarage[gpid][pgRedPos][0], PublicGarage[gpid][pgRedPos][1], PublicGarage[gpid][pgRedPos][2]-0.05, PublicGarage[gpid][pgRedWorld], PublicGarage[gpid][pgRedInterior], -1, 30.00, -1, 0);
        
        static strrs[144];
        format(strrs, sizeof(strrs), "[ "WHITE"(Garkot): "YELLOW"%s "GREEN"]", PublicGarage[gpid][pgName]);
        PublicGarage[gpid][pgLabel] = CreateDynamic3DTextLabel(strrs, Y_GREEN, PublicGarage[gpid][pgRedPos][0], PublicGarage[gpid][pgRedPos][1], PublicGarage[gpid][pgRedPos][2]+0.30, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, PublicGarage[gpid][pgRedWorld], PublicGarage[gpid][pgRedInterior], -1, 10.00, -1, 0);
    }
	return 1;
}

PublicGarage_Save(gpid)
{
	new
	    query[512];
        
	format(query, sizeof(query), "UPDATE public_garages SET PG_Name='%s', PG_RedX='%f', PG_RedY='%f', PG_RedZ='%f', PG_RedWorld=%d, PG_RedInterior=%d, \
    PG_SpawnX='%f', PG_SpawnY='%f', PG_SpawnZ='%f', PG_SpawnA='%f', PG_SpawnWorld=%d, PG_SpawnInterior=%d WHERE id = %d",
        PublicGarage[gpid][pgName],
        PublicGarage[gpid][pgRedPos][0], 
        PublicGarage[gpid][pgRedPos][1], 
        PublicGarage[gpid][pgRedPos][2], 
        PublicGarage[gpid][pgRedWorld], 
        PublicGarage[gpid][pgRedInterior],

        PublicGarage[gpid][pgSpawnPos][0], 
        PublicGarage[gpid][pgSpawnPos][1], 
        PublicGarage[gpid][pgSpawnPos][2], 
        PublicGarage[gpid][pgSpawnPos][3], 
        PublicGarage[gpid][pgSpawnWorld], 
        PublicGarage[gpid][pgSpawnInterior],

        gpid
	);
	return mysql_pquery(g_SQL, query);
}

forward OnGarageCreated(playerid, gpid);
public OnGarageCreated(playerid, gpid)
{
	PublicGarage_Save(gpid);
	PublicGarage_Refresh(gpid);

    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s membuat Public Garage dengan ID: %d.", AccountData[playerid][pAdminname], gpid);
	return 1;
}

forward LoadPublicGarages();
public LoadPublicGarages()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
 		new gpid;
		for(new i; i < rows; i++)
		{
            cache_get_value_name_int(i, "ID", gpid);
            cache_get_value_name(i, "PG_Name", PublicGarage[gpid][pgName]);
            cache_get_value_name_float(i, "PG_RedX", PublicGarage[gpid][pgRedPos][0]);
            cache_get_value_name_float(i, "PG_RedY", PublicGarage[gpid][pgRedPos][1]);
            cache_get_value_name_float(i, "PG_RedZ", PublicGarage[gpid][pgRedPos][2]);
            cache_get_value_name_int(i, "PG_RedWorld", PublicGarage[gpid][pgRedWorld]);
            cache_get_value_name_int(i, "PG_RedInterior", PublicGarage[gpid][pgRedInterior]);
            cache_get_value_name_float(i, "PG_SpawnX", PublicGarage[gpid][pgSpawnPos][0]);
            cache_get_value_name_float(i, "PG_SpawnY", PublicGarage[gpid][pgSpawnPos][1]);
            cache_get_value_name_float(i, "PG_SpawnZ", PublicGarage[gpid][pgSpawnPos][2]);
            cache_get_value_name_float(i, "PG_SpawnA", PublicGarage[gpid][pgSpawnPos][3]);
            cache_get_value_name_int(i, "PG_SpawnWorld", PublicGarage[gpid][pgSpawnWorld]);
            cache_get_value_name_int(i, "PG_SpawnInterior", PublicGarage[gpid][pgSpawnInterior]);
            
			PublicGarage_Rebuild(gpid);
			Iter_Add(PGarages, gpid);
        }
        printf("[Dynamic Public Garages] Jumlah total Public Garages yang dimuat: %d.", rows);
	}
}

forward SaveVehicleToGarkot(playerid, carid, gpid);
public SaveVehicleToGarkot(playerid, carid, gpid)
{
    if(!IsPlayerConnected(playerid)) return 1;
    if(!AccountData[playerid][pSpawned]) return 1;
    if(PlayerVehicle[carid][pVehPhysic] == INVALID_VEHICLE_ID || !IsValidVehicle(PlayerVehicle[carid][pVehPhysic])) return 1;
    if(!Iter_Contains(PGarages, gpid)) return 1;
    if(!IsValidDynamicObject(PublicGarage[gpid][pgRedObjid])) return 1;

    PlayerVehicle[carid][pVehParked] = gpid;
    SetVehicleNeonLights(PlayerVehicle[carid][pVehPhysic], false, PlayerVehicle[carid][pVehNeon], 0);

    DestroyVehicle(PlayerVehicle[carid][pVehPhysic]);
    PlayerVehicle[carid][pVehPhysic] = INVALID_VEHICLE_ID;

    new sqlsdwadkw[128];
    mysql_format(g_SQL, sqlsdwadkw, sizeof(sqlsdwadkw), "UPDATE `player_vehicles` SET `PVeh_Parked` = %d WHERE `id` = %d", PlayerVehicle[carid][pVehParked], PlayerVehicle[carid][pVehID]);
    mysql_pquery(g_SQL, sqlsdwadkw);
    return 1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA: areaid)
{
    foreach(new gpid : PGarages)
    {
        if(areaid == PublicGarage[gpid][pgRedArea])
        {
            if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
            {
                ShowNotifBox(playerid, "Tekan ~p~'H' ~w~Simpan Kendaraan");
            }
            else
            {
                ShowNotifBox(playerid, "Tekan ~p~'Y' ~w~Akses Garasi Kota");
            }
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA: areaid)
{
    foreach(new gpid : PGarages)
    {
        if(areaid == PublicGarage[gpid][pgRedArea])
        {
            HideNotifBox(playerid);
            PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
        }
    }
    return 1;
}

Dialog:GarkotMenu(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        AccountData[playerid][pInGarkot] = -1;
        return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    }

    new id = ReturnAnyVehiclePark(playerid, listitem, AccountData[playerid][pInGarkot]);
    if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan yang tersimpan di garkot ini!");
    
    if(PlayerVehicle[id][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
    PlayerVehicle[id][pVehParked] = -1;
    PlayerVehicle[id][pVehFamGarage] = -1;
    PlayerVehicle[id][pVehHouseGarage] = -1;
    PlayerVehicle[id][pVehInsuranced] = false;

    PlayerVehicle[id][pVehImpounded] = false;
    PlayerVehicle[id][pVehImpoundDuration] = 0;
    PlayerVehicle[id][pVehImpoundFee] = 0;
    PlayerVehicle[id][pVehImpoundReason][0] = EOS;

    PlayerVehicle[id][pVehPos][0] = PublicGarage[AccountData[playerid][pInGarkot]][pgSpawnPos][0];
    PlayerVehicle[id][pVehPos][1] = PublicGarage[AccountData[playerid][pInGarkot]][pgSpawnPos][1];
    PlayerVehicle[id][pVehPos][2] = PublicGarage[AccountData[playerid][pInGarkot]][pgSpawnPos][2];
    PlayerVehicle[id][pVehPos][3] = PublicGarage[AccountData[playerid][pInGarkot]][pgSpawnPos][3];
    
    OnPlayerVehicleRespawn(id);
    AccountData[playerid][pInGarkot] = -1;

    SetTimerEx("ForcePlayerHopInVehicle", 1500, false, "idd", playerid, PlayerVehicle[id][pVehPhysic], 0);

    new sqlsdwadkw[128];
    mysql_format(g_SQL, sqlsdwadkw, sizeof(sqlsdwadkw), "UPDATE `player_vehicles` SET `PVeh_Parked` = %d WHERE `id` = %d", PlayerVehicle[id][pVehParked], PlayerVehicle[id][pVehID]);
    mysql_pquery(g_SQL, sqlsdwadkw);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        new gpid = -1;
	    gpid = PublicGarage_Nearest(playerid);

        if(gpid != -1)
        {
            if(PublicGarage[gpid][pgRedPos][0] == 0.0 && PublicGarage[gpid][pgRedPos][1] == 0.0 && PublicGarage[gpid][pgRedPos][2] == 0.0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Garkot ini belum memiliki posisi despawn!");
            if(PublicGarage[gpid][pgSpawnPos][0] == 0.0 && PublicGarage[gpid][pgSpawnPos][1] == 0.0 && PublicGarage[gpid][pgSpawnPos][2] == 0.0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Garkot ini belum memiliki posisi spawn!");

            if(CountPlayerVehicleParked(playerid, gpid) < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki kendaraan yang tersimpan di garasi ini!");

            AccountData[playerid][pInGarkot] = gpid;
            new id, count = CountPlayerVehicleParked(playerid, gpid), location[512], lstr[596];

            strcat(location,"No\tModel Kendaraan\tNomor Plat\n",sizeof(location));
            for(new itt; itt < count; itt++)
            {
                id = ReturnAnyVehiclePark(playerid, itt, gpid);
                if(itt == count)
                {
                    format(lstr,sizeof(lstr), "%d\t%s\t%s\n", itt + 1, GetVehicleModelName(PlayerVehicle[id][pVehModelID]), PlayerVehicle[id][pVehPlate]);
                }
                else format(lstr,sizeof(lstr), "%d\t%s\t%s\n", itt + 1, GetVehicleModelName(PlayerVehicle[id][pVehModelID]), PlayerVehicle[id][pVehPlate]);
                strcat(location,lstr,sizeof(location));
            }
            Dialog_Show(playerid, "GarkotMenu", DIALOG_STYLE_TABLIST_HEADERS,"Garasi Kota Umum - Ambil Kendaraan", location, "Pilih","Batal");
            HideNotifBox(playerid);
        }
    }
    
    else if(newkeys & KEY_CROUCH && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
    {
        new gpid = -1;
	    gpid = PublicGarage_Nearest(playerid);

        if(gpid != -1)
        {
            if(PublicGarage[gpid][pgRedPos][0] == 0.0 && PublicGarage[gpid][pgRedPos][1] == 0.0 && PublicGarage[gpid][pgRedPos][2] == 0.0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Garkot ini belum memiliki posisi despawn!");
            if(PublicGarage[gpid][pgSpawnPos][0] == 0.0 && PublicGarage[gpid][pgSpawnPos][1] == 0.0 && PublicGarage[gpid][pgSpawnPos][2] == 0.0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Garkot ini belum memiliki posisi spawn!");

            new carid = -1,
                foundnearby = 0;

            if((carid = GetPlayerVehicleIDInside(playerid)) != -1)
            {
                if(PlayerVehicle[carid][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
                if(PlayerVehicle[carid][pVehRental] > -1 || PlayerVehicle[carid][pVehRentTime] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menyimpan kendaraan rental!");
                Vehicle_GetStatus(carid);
                HideNotifBox(playerid);
                
                foundnearby++;

                RemovePlayerFromVehicle(playerid);
                
                SetTimerEx("SaveVehicleToGarkot", 2500, false, "idd", playerid, carid, gpid);
            }

            if(!foundnearby)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini bukanlah kendaraan pribadi!");
        }
    }
    return 1;
}