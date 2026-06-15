#include <YSI_Coding\y_hooks>

#define MAX_RENTAL    20

enum e_BikeRents
{
    Name[64],
    Model[2],
    Cost[2],
    Float:Pos[3],
    Float:SpawnPos[4],
    World,
    Interior,

    //not saved
    STREAMER_TAG_PICKUP:Pickup,
    STREAMER_TAG_3D_TEXT_LABEL:Label
};
new RentalData[MAX_RENTAL][e_BikeRents],
    Iterator:Rentals<MAX_RENTAL>;

Rental_Nearest(playerid)
{
    foreach(new i : Rentals) if (IsPlayerInRangeOfPoint(playerid, 3.0, RentalData[i][Pos][0], RentalData[i][Pos][1], RentalData[i][Pos][2]))
	{
		if (GetPlayerInterior(playerid) == RentalData[i][Interior] && GetPlayerVirtualWorld(playerid) == RentalData[i][World])
			return i;
	}
	return -1;
}

Rental_Save(brid)
{
    new dquery[552];
    mysql_format(g_SQL, dquery, sizeof(dquery), "UPDATE `rentals` SET `Model1`='%d', `Model2`='%d', `Cost1`='%d', `Cost2`='%d', `PosX`='%f', \
    `PosY`='%f', `PosZ`='%f', `SpawnX`='%f', `SpawnY`='%f', `SpawnZ`='%f', `SpawnA`='%f', `World`='%d', `Interior`='%d' WHERE `ID`='%d'",
    RentalData[brid][Model][0], RentalData[brid][Model][1], RentalData[brid][Cost][0], RentalData[brid][Cost][1], RentalData[brid][Pos][0], RentalData[brid][Pos][1], 
    RentalData[brid][Pos][2], RentalData[brid][SpawnPos][0], RentalData[brid][SpawnPos][1], RentalData[brid][SpawnPos][2], RentalData[brid][SpawnPos][3], RentalData[brid][World], RentalData[brid][Interior], brid);
    mysql_pquery(g_SQL, dquery);
    return 1;
}

Rental_Refresh(brid)
{
    if(brid != -1)
    {
        Streamer_SetItemPos(STREAMER_TYPE_PICKUP, RentalData[brid][Pickup], RentalData[brid][Pos][0], RentalData[brid][Pos][1], RentalData[brid][Pos][2]);
        Streamer_SetIntData(STREAMER_TYPE_PICKUP, RentalData[brid][Pickup], E_STREAMER_WORLD_ID, RentalData[brid][World]);
        Streamer_SetIntData(STREAMER_TYPE_PICKUP, RentalData[brid][Pickup], E_STREAMER_INTERIOR_ID, RentalData[brid][Interior]);

        Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, RentalData[brid][Label], RentalData[brid][Pos][0], RentalData[brid][Pos][1], RentalData[brid][Pos][2]+0.85);
        Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, RentalData[brid][Label], E_STREAMER_WORLD_ID, RentalData[brid][World]);
        Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, RentalData[brid][Label], E_STREAMER_INTERIOR_ID, RentalData[brid][Interior]);
    }
    return 1;
}

Rental_Rebuild(brid)
{
    if(brid != -1)
    {
        RentalData[brid][Pickup] = CreateDynamicPickup(1239, 23, RentalData[brid][Pos][0], RentalData[brid][Pos][1], RentalData[brid][Pos][2], RentalData[brid][World], RentalData[brid][Interior], -1, 30.00, -1, 0);
        
        static string[258];
        format(string, sizeof(string), "[Sewa Kendaraan]\n"CYAN"%s\n"GREEN"[Y] "WHITE"untuk membuka menu rental", RentalData[brid][Name]);
        RentalData[brid][Label] = CreateDynamic3DTextLabel(string, 0xc0c0c8A6, RentalData[brid][Pos][0], RentalData[brid][Pos][1], RentalData[brid][Pos][2]+0.85, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, RentalData[brid][World], RentalData[brid][Interior], -1, 10.00, -1, 0);
    }
    return 1;
}

forward LoadRentals();
public LoadRentals()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
 		new brid;
		for(new i; i < rows; i++)
		{
            cache_get_value_name_int(i, "ID", brid);
            cache_get_value_name(i, "Name", RentalData[brid][Name]);
            cache_get_value_name_int(i, "Model1", RentalData[brid][Model][0]);
            cache_get_value_name_int(i, "Model2", RentalData[brid][Model][1]);
            cache_get_value_name_int(i, "Cost1", RentalData[brid][Cost][0]);
            cache_get_value_name_int(i, "Cost2", RentalData[brid][Cost][1]);
            cache_get_value_name_float(i, "PosX", RentalData[brid][Pos][0]);
            cache_get_value_name_float(i, "PosY", RentalData[brid][Pos][1]);
            cache_get_value_name_float(i, "PosZ", RentalData[brid][Pos][2]);
            cache_get_value_name_float(i, "SpawnX", RentalData[brid][SpawnPos][0]);
            cache_get_value_name_float(i, "SpawnY", RentalData[brid][SpawnPos][1]);
            cache_get_value_name_float(i, "SpawnZ", RentalData[brid][SpawnPos][2]);
            cache_get_value_name_float(i, "SpawnA", RentalData[brid][SpawnPos][3]);
            cache_get_value_name_int(i, "World", RentalData[brid][World]);
            cache_get_value_name_int(i, "Interior", RentalData[brid][Interior]);
            
			Rental_Rebuild(brid);
			Iter_Add(Rentals, brid);
        }
        printf("[Dynamic Rentals] Total number of loaded Rentals: %d.", rows);
	}
}

forward OnRentalCreated(playerid, brid);
public OnRentalCreated(playerid, brid)
{
    Rental_Save(brid);

    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s created Rental with ID: %d.", AccountData[playerid][pAdminname], brid);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        new brid = Rental_Nearest(playerid), brstr[512];

        if(brid == -1) return 1;

        if(Iter_Count(UberDuty) >= 8) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat akses rental, silakan pesan Uber!");

        AccountData[playerid][pInRent] = brid;
        format(brstr, sizeof(brstr), 
        "Vehicle Type\tRental Cost\n\
        %s\t$%s/hr\n\
        %s\t$%s/hr\n\
        "YELLOW"> Pilih ini untuk mengembalikan kendaraan rental.", GetVehicleModelName(RentalData[brid][Model][0]), FormatMoney(RentalData[brid][Cost][0]), GetVehicleModelName(RentalData[brid][Model][1]), FormatMoney(RentalData[brid][Cost][1]));
        Dialog_Show(playerid, "RentalCatalog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Rental", 
        brstr, "Pilih", "Batal");
    }
    return 1;
}

Dialog:RentalCatalog(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    
    new brid = AccountData[playerid][pInRent],
        strgbg[522],
        color1 = RandomEx(0, 255),
        color2 = RandomEx(0, 255),
        count = 0;

    switch(listitem)
    {
        case 0: //TDR-3000
        {
            foreach(new carid : PvtVehicles)
            {
                if(PlayerVehicle[carid][pVehOwnerID] == AccountData[playerid][pID])
                    count++;
            }

            if(AccountData[playerid][pMoney] < RentalData[brid][Cost][0]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
            if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah mencapai batas slot maksimum kendaraan!");
            
            TakePlayerMoneyEx(playerid, RentalData[brid][Cost][0]);
            VehicleRental_Create(playerid, RentalData[brid][Model][0], 3600, brid, RentalData[brid][SpawnPos][0], RentalData[brid][SpawnPos][1], RentalData[brid][SpawnPos][2], RentalData[brid][SpawnPos][3], color1, color2, RentalData[brid][World], RentalData[brid][Interior]);
        }
        case 1: //Mountain Bike
        {
            foreach(new carid : PvtVehicles)
            {
                if(PlayerVehicle[carid][pVehOwnerID] == AccountData[playerid][pID])
                    count++;
            }
            
            if(AccountData[playerid][pMoney] < RentalData[brid][Cost][1]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
            if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah mencapai batas slot maksimum kendaraan!");
            
            TakePlayerMoneyEx(playerid, RentalData[brid][Cost][1]);
            VehicleRental_Create(playerid, RentalData[brid][Model][1], 3600, brid, RentalData[brid][SpawnPos][0], RentalData[brid][SpawnPos][1], RentalData[brid][SpawnPos][2], RentalData[brid][SpawnPos][3], color1, color2, RentalData[brid][World], RentalData[brid][Interior]);
        }
        case 2: //Return rented vehicle
        {
            foreach(new i : PvtVehicles)
            {
                if(PlayerVehicle[i][pVehOwnerID] == AccountData[playerid][pID])
                {
                    if(PlayerVehicle[i][pVehRental] > -1 || PlayerVehicle[i][pVehRentTime] > 0)
                    {
                        PlayerVehicle[i][pVehRental] = -1;
                        PlayerVehicle[i][pVehRentTime] = 0;
                        
                        if(Iter_Contains(Vehicle, PlayerVehicle[i][pVehPhysic]))
                        {
                            SetVehicleNeonLights(PlayerVehicle[i][pVehPhysic], false, PlayerVehicle[i][pVehNeon], 0);
                        }
                        DestroyVehicle(PlayerVehicle[i][pVehPhysic]);
                        PlayerVehicle[i][pVehHandbraked] = false;

                        mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `vehicle_bagasi` WHERE `Veh_DBID`=%d", PlayerVehicle[i][pVehID]);
                        mysql_pquery(g_SQL, strgbg);
                        mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `vehicle_holster` WHERE `Veh_DBID`=%d", PlayerVehicle[i][pVehID]);
                        mysql_pquery(g_SQL, strgbg);
                        mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `player_vehicles` WHERE `id` = %d", PlayerVehicle[i][pVehID]);
                        mysql_pquery(g_SQL, strgbg);
                        mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `vtoys` WHERE `Veh_DBID`=%d", PlayerVehicle[i][pVehID]);
                        mysql_pquery(g_SQL, strgbg);

                        for(new x; x < 6; x++)
                        {
                            vtData[i][x][vtoy_modelid] = 0;
                            vtData[i][x][vtoy_text][0] = EOS;
                            strcopy(vtData[i][x][vtoy_font], "Arial");
                            vtData[i][x][vtoy_fontsize] = 11;
                            vtData[i][x][vtoy_fontcolor][0] = 255;
                            vtData[i][x][vtoy_fontcolor][1] = 0;
                            vtData[i][x][vtoy_fontcolor][2] = 0;
                            vtData[i][x][vtoy_fontcolor][3] = 0;
                            vtData[i][x][vtoy_fontcolor][4] = 0;
                            vtData[i][x][vtoy_objectcolor][0] = 255;
                            vtData[i][x][vtoy_objectcolor][1] = 0;
                            vtData[i][x][vtoy_objectcolor][2] = 0;
                            vtData[i][x][vtoy_objectcolor][3] = 0;
                            vtData[i][x][vtoy_objectcolor][4] = 0;
                            vtData[i][x][vtoy_x] = 0.0;
                            vtData[i][x][vtoy_y] = 0.0;
                            vtData[i][x][vtoy_z] = 0.0;
                            vtData[i][x][vtoy_rx] = 0.0;
                            vtData[i][x][vtoy_ry] = 0.0;
                            vtData[i][x][vtoy_rz] = 0.0;
                        }

                        for(new x; x < MAX_BAGASI_ITEMS; x++)
                        {
                            VehicleBagasi[i][x][vehicleBagasiExists] = false;
                            VehicleBagasi[i][x][vehicleBagasiID] = 0;
                            VehicleBagasi[i][x][vehicleBagasiVDBID] = 0;
                            VehicleBagasi[i][x][vehicleBagasiTemp][0] = EOS;
                            VehicleBagasi[i][x][vehicleBagasiModel] = 0;
                            VehicleBagasi[i][x][vehicleBagasiQuant] = 0;
                        }

                        for(new z; z < 3; z++)
                        {
                            VehicleHolster[i][vHolsterTaken][z] = false;
                            VehicleHolster[i][vHolsterID][z] = -1;
                            VehicleHolster[i][vHolsterWeaponID][z] = 0;
                            VehicleHolster[i][vHolsterWeaponAmmo][z] = 0;
                        }
                        
                        Iter_Remove(PvtVehicles, i);

                        ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengembalikan semua kendaraan rental.");
                        return 1;
                    }
                }
            }
            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum menyewa kendaraan apapun!");
        }
    }
    return 1;
}