forward EngineStatus(playerid, vehicleid);
public EngineStatus(playerid, vehicleid)
{
	if(!IsPlayerConnected(playerid)) 
	{
		AccountData[playerid][pTurningEngine] = false;
		return 0;
	}

	if(!AccountData[playerid][pTurningEngine]) 
	{
		AccountData[playerid][pTurningEngine] = false;
		return 0;
	}

	if(!IsValidVehicle(vehicleid)) 
	{
		AccountData[playerid][pTurningEngine] = false;
		return 0;
	}

	if(GetEngineStatus(vehicleid)) 
	{
		AccountData[playerid][pTurningEngine] = false;
		return 0;
	}

	//new streng[128];
	/*foreach(new ii : PvtVehicles)
	{
		if(vehicleid == PlayerVehicle[ii][cVeh])
		{
			if(PlayerVehicle[ii][cTicket] >= 2000)
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini sudah ditilang oleh Polisi! '/mv' - untuk memeriksanya");
		}
	}*/
	new Float: f_vHealth;
	GetVehicleHealth(vehicleid, f_vHealth);
	if(f_vHealth <= 350.0) 
	{
		AccountData[playerid][pTurningEngine] = false;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Mesin tidak dapat menyala karena mesin sudah rusak!");
	}
	if(VehicleCore[vehicleid][vCoreFuel] <= 0.0) 
	{
		AccountData[playerid][pTurningEngine] = false;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Mesin tidak dapat menyala karena bahan bakar sudah habis!");
	}
	if(GetVehicleDriver(vehicleid) == INVALID_PLAYER_ID) 
	{
		AccountData[playerid][pTurningEngine] = false;
		return 1;
	}
	SwitchVehicleEngine(vehicleid, true);

	AccountData[playerid][pTurningEngine] = false;
	return 1;
}

forward MakeNewPlateCreate(playerid, iterid, const template[]);
public MakeNewPlateCreate(playerid, iterid, const template[])
{
	if(cache_num_rows() > 0)
	{
		//nomor HP Exist
		new	tmswk[32],
			query[212],
			xd1 = random(sizeof(g_Alphabet)),
			xd2 = random(sizeof(g_Alphabet)),
			xd3 = random(sizeof(g_Alphabet));

		format(tmswk, sizeof(tmswk), "BK %d%d%d%d %s%s%s", random(10), random(10), random(10), random(10), g_Alphabet[xd1], g_Alphabet[xd2], g_Alphabet[xd3]);
		mysql_format(g_SQL, query, sizeof(query), "SELECT `PVeh_Plate` FROM `player_vehicles` WHERE `PVeh_Plate`='%e'", tmswk);
		mysql_pquery(g_SQL, query, "MakeNewPlateCreate", "ids", playerid, iterid, tmswk);
	}
	else
	{
		strcopy(PlayerVehicle[iterid][pVehPlate], template);
		SavePlayerVehicle(iterid);
		SetVehicleNumberPlate(PlayerVehicle[iterid][pVehPhysic], PlayerVehicle[iterid][pVehPlate]);

		SetTimerEx("RespawnPV", 1500, false, "d", PlayerVehicle[iterid][pVehPhysic]);
		ShowTDN(playerid, NOTIFICATION_SUCCESS, "Plat telah berhasil terpasang pada kendaraan tersebut!");
	}
    return 1;
}

static bool:IsBagasiItemValid(carid, slot)
{
    new bool:itemExists = false;
    for(new i = 0; i < sizeof(g_aInventoryItems); i++) 
    {
        // Kalau item-nya ada, ganti itemExists
        if(!strcmp(VehicleBagasi[carid][slot][vehicleBagasiTemp], g_aInventoryItems[i][e_InventoryItem], true)) {
            itemExists = true;
            break;
        }
 
        // Nah ini bakal nge-loop terus sampai ketemu si item atau gak sampai
        // size-nya abis. Kenapa? Karena kan si nama item gak selalu ada di
        // index yang lagi di-loop ini, bisa aja di index yang lain.
    }
 
    // Habis nge-loop seluruh index ternyata namanya bener-bener gak ada. Nah
    // di sini deh baru di-delete.
    if(!itemExists) 
    {
        VehicleBagasi[carid][slot][vehicleBagasiExists] = false;
        VehicleBagasi[carid][slot][vehicleBagasiModel] = 0;
        VehicleBagasi[carid][slot][vehicleBagasiQuant] = 0;
 
        VehicleBagasi[carid][slot][vehicleBagasiTemp][0] = EOS;
 
        static invstr[555];
        mysql_format(g_SQL, invstr, sizeof(invstr), "DELETE FROM `vehicle_bagasi` WHERE `ID`=%d", VehicleBagasi[carid][slot][vehicleBagasiID]);
        mysql_pquery(g_SQL, invstr);
    }
 
    return itemExists;
}

forward LoadVehicleBagasi(carid);
public LoadVehicleBagasi(carid)
{
    if(cache_num_rows() > 0)
    {
		new totalInvalidItems = 0;
        for(new x; x < cache_num_rows(); x++)
        {
            if(!VehicleBagasi[carid][x][vehicleBagasiExists])
            {
                VehicleBagasi[carid][x][vehicleBagasiExists] = true;
                cache_get_value_name_int(x, "ID", VehicleBagasi[carid][x][vehicleBagasiID]);
                cache_get_value_name_int(x, "Veh_DBID", VehicleBagasi[carid][x][vehicleBagasiVDBID]);
                cache_get_value_name(x, "Item", VehicleBagasi[carid][x][vehicleBagasiTemp]);
                cache_get_value_name_int(x, "Model", VehicleBagasi[carid][x][vehicleBagasiModel]);
                cache_get_value_name_int(x, "Quantity", VehicleBagasi[carid][x][vehicleBagasiQuant]);

				if(!IsBagasiItemValid(carid, x)) 
                {
                    totalInvalidItems++;
                }
            }
        }
    }
    return 1;
}

forward OnBagasiDeposited(playerid, carid, id);
public OnBagasiDeposited(playerid, carid, id)
{
	AccountData[playerid][pMenuShowed] = false;
    VehicleBagasi[carid][id][vehicleBagasiID] = cache_insert_id();
    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyimpan item tersebut.");
    return 1;
}

Float:GetBagasiTotalWeightFloat(vehid)
{
	new totalweights, Float:totalweights2;

    for(new x; x < MAX_BAGASI_ITEMS; x++)
    {
        if(VehicleBagasi[vehid][x][vehicleBagasiExists] && VehicleBagasi[vehid][x][vehicleBagasiVDBID] == PlayerVehicle[vehid][pVehID])
        {
            totalweights += GetItemWeight(VehicleBagasi[vehid][x][vehicleBagasiTemp]) * VehicleBagasi[vehid][x][vehicleBagasiQuant];
        }
    }
    totalweights2 = float(totalweights)/1000;
    return totalweights2;
}

Vehicle_ShowBagasi(playerid, vehid)
{
    new 
        curr_page = index_pagination[playerid], 
        count = 0, 
        string[1555], 
        real_i = 0, 
        bagasibrankas_exists[MAX_PAGINATION_PAGES],
        bagasibrankas_name[MAX_PAGINATION_PAGES][32], 
        bagasibrankas_quant[MAX_PAGINATION_PAGES],
        bagasibrankas_id[MAX_PAGINATION_PAGES],
        curr_idx; 

    curr_idx = MAX_PAGINATION_PAGES * curr_page;

    for(new i = 0; i < MAX_PAGINATION_PAGES; i++) 
    {
        bagasibrankas_exists[i] = false;
    }

    format(string, sizeof(string), "Nama Item\tJumlah\tBerat (%.3f/%d kg)\n", GetBagasiTotalWeightFloat(vehid), GetVehicleWeight(PlayerVehicle[vehid][pVehModelID]));

    for(new i = 0; i < MAX_BAGASI_ITEMS; i++)
    {
        if (VehicleBagasi[vehid][i][vehicleBagasiExists] && VehicleBagasi[vehid][i][vehicleBagasiVDBID] == PlayerVehicle[vehid][pVehID]) 
        {
            if (real_i >= curr_idx && real_i < curr_idx + MAX_PAGINATION_PAGES)
            {
                bagasibrankas_exists[real_i - curr_idx] = true;
                bagasibrankas_id[real_i - curr_idx] = i;
                strcopy(bagasibrankas_name[real_i - curr_idx], VehicleBagasi[vehid][i][vehicleBagasiTemp], 32);
                bagasibrankas_quant[real_i - curr_idx] = VehicleBagasi[vehid][i][vehicleBagasiQuant];
            }
            real_i++;
        }
    }

    for(new i = 0; i < MAX_PAGINATION_PAGES; i++) 
    {
        if(bagasibrankas_exists[i]) 
        {
            if (i % 2 == 0)
            {
                strcat(string, sprintf(""WHITE"%s\t"WHITE"%d\t"WHITE"-\n", bagasibrankas_name[i], bagasibrankas_quant[i]));
            }
            else
            {
                strcat(string, sprintf(""GRAY"%s\t"GRAY"%d\t"GRAY"-\n", bagasibrankas_name[i], bagasibrankas_quant[i]));
            }
            PlayerListitem[playerid][count++] = bagasibrankas_id[i];
        }
    }

    if(count == 0) 
	{
        SwitchVehicleBoot(PlayerVehicle[vehid][pVehPhysic], false);
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, sprintf("Bagasi Kendaraan "YELLOW"%s {DA9100}- %s", GetVehicleModelName(PlayerVehicle[vehid][pVehModelID]), PlayerVehicle[vehid][pVehPlate]), 
        "Isi bagasi kendaraan ini kosong!", "Tutup", "");
    } 
	else 
	{
        new max_pages = (real_i + MAX_PAGINATION_PAGES - 1) / MAX_PAGINATION_PAGES;

        if (curr_page > 0) {
            strcat(string, ""RED"<< Sebelumnya\n");
        }
        if (curr_page < max_pages - 1) {
            strcat(string, ""GREEN">> Selanjutnya\n");
        }

        Dialog_Show(playerid, "VehicleStorageWithdraw", DIALOG_STYLE_TABLIST_HEADERS, sprintf("Bagasi %s: Page %d of %d", PlayerVehicle[vehid][pVehPlate], curr_page + 1, max_pages),
        string, "Pilih", "Batal");
    }
    return 1;
}

IsVehicleInArea(vehicleid, Float:MinX, Float:MaxX, Float:MinY, Float:MaxY)
{
    new Float:x, Float:y, Float:z;
    GetVehiclePos(vehicleid, x, y, z);
    #pragma unused z
    if(x >= MinX && x <= MaxX && y >= MinY && y <= MaxY) { return 1; }
    return 0;
}

IsVehicleInWater(vehicleid)
{
	new Float:X, Float:Y, Float:Z;
	GetVehiclePos(vehicleid, X, Y, Z);
	if(GetVehicleDistanceFromPoint(vehicleid, -965, 2438, 42) <= 700 && Z < 45) return true;
	
	if ((Z <= 0 || (Z <= 41.0 && IsVehicleInArea(vehicleid, -1387, -473, 2025, 2824))) ||
        (Z <= 2 || (Z <= 39.0 && IsVehicleInArea(vehicleid, -1387, -473, 2025, 2824))))
    {
        return true;
    }

	new Float:water_areas[][] =
	{
		{25.0, 2313.0, -1417.0, 23.0},
		{15.0, 1280.0, -773.0, 1082.0},
		{15.0, 1279.0, -804.0, 86.0},
		{20.0, 1094.0, -674.0, 111.0},
		{26.0, 194.0, -1232.0, 76.0},
		{25.0, 2583.0, 2385.0, 15.0},
		{25.0, 225.0, -1187.0, 73.0},
		{50.0, 1973.0, -1198.0, 17.0},
		{140.0, 1923.0, 1592.0, 10.0}
	};

	for(new t=0; t < sizeof (water_areas); t++)
	{
		if(GetVehicleDistanceFromPoint(vehicleid, water_areas[t][1], water_areas[t][2], water_areas[t][3]) <= water_areas[t][0])
		{
			return true;
		}
	}
    return false;
}

IsEngineVehicle(vehicleid)
{
    static const g_aEngineStatus[] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
        1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0
    };
    new modelid = GetVehicleModel(vehicleid);

    if(modelid < 400 || modelid > 611)
        return 0;

    return (g_aEngineStatus[modelid - 400]);
}

GetEngineStatus(vehicleid)
{
	static
	engine,
	lights,
	alarm,
	doors,
	bonnet,
	boot,
	objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

	if(engine != 1)
		return 0;

	return 1;
}

GetVehicleModelByName(const name[])
{
	if(IsNumericEx(name) && (strval(name) >= 400 && strval(name) <= 611))
		return strval(name);

	for (new i = 0; i < sizeof(g_arrVehicleNames); i ++)
	{
		if(strfind(g_arrVehicleNames[i], name, true) != -1)
		{
			return i + 400;
		}
	}
	return 0;
}

GetLightStatus(vehicleid)
{
	static
	engine,
	lights,
	alarm,
	doors,
	bonnet,
	boot,
	objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

	if(lights != 1)
		return 0;

	return 1;
}

GetHoodStatus(vehicleid)
{
	static
	engine,
	lights,
	alarm,
	doors,
	bonnet,
	boot,
	objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

	if(bonnet != 1)
		return 0;

	return 1;
}

GetTrunkStatus(vehicleid)
{
	static
	engine,
	lights,
	alarm,
	doors,
	bonnet,
	boot,
	objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

	if(boot != 1)
		return 0;

	return 1;
}

SetValidVehicleHealth(vehicleid, Float:health) 
{
	VehicleHealthSecurity[vehicleid] = true;
	VehicleCore[vehicleid][vCoreHealth] = health;
	SetVehicleHealth(vehicleid, VehicleCore[vehicleid][vCoreHealth]);
	return 1;
}

ValidRepairVehicle(vehicleid) 
{
	VehicleHealthSecurity[vehicleid] = true;
	RepairVehicle(vehicleid);
	return 1;
}

Vehicle_GetStatus(carid)
{
	if(Iter_Contains(Vehicle, PlayerVehicle[carid][pVehPhysic]))
	{
		GetVehicleDamageStatus(PlayerVehicle[carid][pVehPhysic], PlayerVehicle[carid][pVehDamage][0], PlayerVehicle[carid][pVehDamage][1], PlayerVehicle[carid][pVehDamage][2], PlayerVehicle[carid][pVehDamage][3]);

		GetVehicleHealth(PlayerVehicle[carid][pVehPhysic], PlayerVehicle[carid][pVehHealth]);
		PlayerVehicle[carid][pVehMaxHealth] = VehicleCore[PlayerVehicle[carid][pVehPhysic]][vMaxHealth];
		if(PlayerVehicle[carid][pVehHealth] < 0.0 || PlayerVehicle[carid][pVehHealth] > PlayerVehicle[carid][pVehMaxHealth]) PlayerVehicle[carid][pVehHealth] = PlayerVehicle[carid][pVehMaxHealth];
		
		PlayerVehicle[carid][pVehFuel] = VehicleCore[PlayerVehicle[carid][pVehPhysic]][vCoreFuel];
		PlayerVehicle[carid][pVehBodyUpgraded] = VehicleCore[PlayerVehicle[carid][pVehPhysic]][vIsBodyUpgraded];
		PlayerVehicle[carid][pVehBodyBroken] = VehicleCore[PlayerVehicle[carid][pVehPhysic]][vIsBodyBroken];
		PlayerVehicle[carid][pVehLocked] = VehicleCore[PlayerVehicle[carid][pVehPhysic]][vCoreLocked];
		PlayerVehicle[carid][pVehWorld] = GetVehicleVirtualWorld(PlayerVehicle[carid][pVehPhysic]);

		GetVehiclePos(PlayerVehicle[carid][pVehPhysic], PlayerVehicle[carid][pVehPos][0], PlayerVehicle[carid][pVehPos][1], PlayerVehicle[carid][pVehPos][2]);
		GetVehicleZAngle(PlayerVehicle[carid][pVehPhysic], PlayerVehicle[carid][pVehPos][3]);

		if(!IsFloatEx(PlayerVehicle[carid][pVehPos][3]))
			PlayerVehicle[carid][pVehPos][3] = 0;
	}
	return 1;
}

VehicleFact_GetStatus(vid, playerid)
{
	if(Iter_Contains(Vehicle, vid))
	{
		GetVehicleDamageStatus(vid, PlayerFactionVehStats[playerid][pFactVehDamage][0], PlayerFactionVehStats[playerid][pFactVehDamage][1], PlayerFactionVehStats[playerid][pFactVehDamage][2], PlayerFactionVehStats[playerid][pFactVehDamage][3]);

		GetVehicleHealth(vid, PlayerFactionVehStats[playerid][pFactVehHealth]);
		PlayerFactionVehStats[playerid][pFactVehMaxHealth] = VehicleCore[vid][vMaxHealth];
		if(PlayerFactionVehStats[playerid][pFactVehHealth] < 0.0 || PlayerFactionVehStats[playerid][pFactVehHealth] > VehicleCore[vid][vMaxHealth]) PlayerFactionVehStats[playerid][pFactVehHealth] = VehicleCore[vid][vMaxHealth];
		
		PlayerFactionVehStats[playerid][pFactVehFuel] = VehicleCore[vid][vCoreFuel];
		PlayerFactionVehStats[playerid][pFactVehBodyUpgraded] = VehicleCore[vid][vIsBodyUpgraded];
		PlayerFactionVehStats[playerid][pFactVehBodyBroken] = VehicleCore[vid][vIsBodyBroken];
		PlayerFactionVehStats[playerid][pFactVehLocked] = VehicleCore[vid][vCoreLocked];
		PlayerFactionVehStats[playerid][pFactVehWorld] = GetVehicleVirtualWorld(vid);

		GetVehiclePos(vid, PlayerFactionVehStats[playerid][pFactVehPos][0], PlayerFactionVehStats[playerid][pFactVehPos][1], PlayerFactionVehStats[playerid][pFactVehPos][2]);
		GetVehicleZAngle(vid, PlayerFactionVehStats[playerid][pFactVehPos][3]);

		if(!IsFloatEx(PlayerFactionVehStats[playerid][pFactVehPos][3]))
			PlayerFactionVehStats[playerid][pFactVehPos][3] = 0;
	}
	return 1;
}

Vehicle_GetIterID(vehicleid)
{
	foreach(new i : PvtVehicles) if (PlayerVehicle[i][pVehPhysic] == vehicleid)
	{
	    return i;
	}
	return -1;
}

RespawnVehicle(vehicleid)
{
	if(Iter_Contains(Vehicle, vehicleid))
	{
		new id = Vehicle_GetIterID(vehicleid);

		if (id != -1)
		{
			Vehicle_GetStatus(id);

			SetVehicleNeonLights(PlayerVehicle[id][pVehPhysic], false, PlayerVehicle[id][pVehNeon], 0);

			DestroyVehicle(PlayerVehicle[id][pVehPhysic]);
			
			OnPlayerVehicleRespawn(id);
		}
		else
		{
			foreach(new i : Player)
			{
				if(vehicleid == PlayerFactionVehicle[i][AccountData[i][pFaction]])
				{
					DestroyVehicle(PlayerFactionVehicle[i][AccountData[i][pFaction]]);

					static string[168];
					mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `demand_vehicles` WHERE `ownerid` = %d", AccountData[i][pID]);
					mysql_pquery(g_SQL, string);
					return 1;
				}
			}

			SetVehicleToRespawn(vehicleid);
			SetValidVehicleHealth(vehicleid, 1000);
			VehicleCore[vehicleid][vCoreFuel] = 100;
			VehicleCore[vehicleid][vIsBodyUpgraded] = false;
			VehicleCore[vehicleid][vIsBodyBroken] = false;
			VehicleCore[vehicleid][vMaxHealth] = 1000.00;
		}
	}
	return 1;
}

CountPlayerVehicleParked(playerid, gpid)
{
	new tmpcount;
	foreach(new id : PvtVehicles)
	{
		if(PlayerVehicle[id][pVehOwnerID] == AccountData[playerid][pID])
		{
			if(!IsValidVehicle(PlayerVehicle[id][pVehPhysic]) && PlayerVehicle[id][pVehParked] == gpid)
			{
				tmpcount++;
			}
		}
	}
	return tmpcount;
}

CountPlayerVehicleHoused(playerid, hgid)
{
	new tmpcount;
	foreach(new id : PvtVehicles)
	{
		if(PlayerVehicle[id][pVehOwnerID] == AccountData[playerid][pID])
		{
			if(!IsValidVehicle(PlayerVehicle[id][pVehPhysic]) && PlayerVehicle[id][pVehHouseGarage] == hgid)
			{
				tmpcount++;
			}
		}
	}
	return tmpcount;
}

CountPlayerVehicleInsuranced(playerid)
{
	new tmpcount;
	foreach(new id : PvtVehicles)
	{
		if(PlayerVehicle[id][pVehOwnerID] == AccountData[playerid][pID])
		{
			if(PlayerVehicle[id][pVehInsuranced])
			{
				tmpcount++;
			}
		}
	}
	return tmpcount;
}

ReturnVehicleIDInsuranced(playerid, slot)
{
	new tmpcount = -1;
	if(slot < 0 && slot > MAX_PRIVATE_VEHICLE - 1) return -1;
	foreach(new id : PvtVehicles)
	{
		if(PlayerVehicle[id][pVehOwnerID] == AccountData[playerid][pID])
		{
			if(PlayerVehicle[id][pVehInsuranced])
			{
				tmpcount++;
				if(tmpcount == slot)
				{
					return id;
				}
			}
		}
	}
	return -1;
}

ReturnVehicleIDATakeOut(playerid, slot)
{
	new tmpcount = -1;
	if(slot < 0 && slot > MAX_PRIVATE_VEHICLE - 1) return -1;
	foreach(new id : PvtVehicles)
	{
		if(PlayerVehicle[id][pVehOwnerID] == AccountData[playerid][pID])
		{
			if(PlayerVehicle[id][pVehPhysic] == INVALID_VEHICLE_ID)
			{
				tmpcount++;
				if(tmpcount == slot)
				{
					return id;
				}
			}
		}
	}
	return -1;
}

ReturnAnyVehiclePark(playerid, slot, gpid)
{
	new tmpcount = -1;
	if(slot < 0 && slot > MAX_PRIVATE_VEHICLE - 1) return -1;
	foreach(new id : PvtVehicles)
	{
		if(PlayerVehicle[id][pVehOwnerID] == AccountData[playerid][pID])
		{
			if(PlayerVehicle[id][pVehParked] == gpid && PlayerVehicle[id][pVehParked] > -1)
			{
				tmpcount++;
				if(tmpcount == slot)
				{
					return id;
				}
			}
		}
	}
	return -1;
}

ReturnAnyVehicleHoused(playerid, slot, hgid)
{
	new tmpcount = -1;
	if(slot < 0 && slot > MAX_PRIVATE_VEHICLE - 1) return -1;
	foreach(new id : PvtVehicles)
	{
		if(PlayerVehicle[id][pVehOwnerID] == AccountData[playerid][pID])
		{
			if(PlayerVehicle[id][pVehHouseGarage] == hgid && PlayerVehicle[id][pVehHouseGarage] > -1)
			{
				tmpcount++;
				if(tmpcount == slot)
				{
					return id;
				}
			}
		}
	}
	return -1;
}

GetMyVehicleStatus(pvid, const def[] = "Terspawn")
{
	new status[144];
	strcopy(status, def);

	if(PlayerVehicle[pvid][pVehParked] >= 0)
		strcopy(status, sprintf("Garkot %s", PublicGarage[PlayerVehicle[pvid][pVehParked]][pgName]));

	if(PlayerVehicle[pvid][pVehFamGarage] >= 0)
		strcopy(status, sprintf("Garasi Fam %d", PlayerVehicle[pvid][pVehFamGarage]));

	if(PlayerVehicle[pvid][pVehHouseGarage] >= 0)
		strcopy(status, sprintf("Garasi Rumah %d", PlayerVehicle[pvid][pVehHouseGarage]));

	if(PlayerVehicle[pvid][pVehInsuranced])
		strcopy(status, "Asuransi");
	
	if(PlayerVehicle[pvid][pVehImpounded])
		strcopy(status, "Impound");

	return status;
}

GetPlayerVehicleIDInside(playerid)
{
	foreach(new i : PvtVehicles)
	{
		if(Iter_Contains(Vehicle, PlayerVehicle[i][pVehPhysic]) && IsPlayerInVehicle(playerid, PlayerVehicle[i][pVehPhysic]))
		{
			return i;
		}
	}
	return -1;
}

GetVehicleHood(vehicleid, &Float:x, &Float:y, &Float:z)
{
    if (!GetVehicleModel(vehicleid) || !IsValidVehicle(vehicleid))
	    return (x = 0.0, y = 0.0, z = 0.0), 0;

	static
	    Float:pos[7]
	;
	GetVehicleModelInfo(GetVehicleModel(vehicleid), VEHICLE_MODEL_INFO_SIZE, pos[0], pos[1], pos[2]);
	GetVehiclePos(vehicleid, pos[3], pos[4], pos[5]);
	GetVehicleZAngle(vehicleid, pos[6]);

	x = pos[3] + (floatsqroot(pos[1] + pos[1]) * floatsin(-pos[6], degrees));
	y = pos[4] + (floatsqroot(pos[1] + pos[1]) * floatcos(-pos[6], degrees));
 	z = pos[5];

	return 1;
}

GetVehicleBoot(vehicleid, &Float:x, &Float:y, &Float:z)
{
	if (!GetVehicleModel(vehicleid) || vehicleid == INVALID_VEHICLE_ID)
	    return (x = 0.0, y = 0.0, z = 0.0), 0;

	static
	    Float:pos[7]
	;
	GetVehicleModelInfo(GetVehicleModel(vehicleid), VEHICLE_MODEL_INFO_SIZE, pos[0], pos[1], pos[2]);
	GetVehiclePos(vehicleid, pos[3], pos[4], pos[5]);
	GetVehicleZAngle(vehicleid, pos[6]);

	x = pos[3] - (floatsqroot(pos[1] + pos[1]) * floatsin(-pos[6], degrees));
	y = pos[4] - (floatsqroot(pos[1] + pos[1]) * floatcos(-pos[6], degrees));
 	z = pos[5];

	return 1;
}

IsPlayerNearBoot(playerid, vehicleid)
{
	static
		Float:fX,
		Float:fY,
		Float:fZ;

	GetVehicleBoot(vehicleid, fX, fY, fZ);

	return (GetPlayerVirtualWorld(playerid) == GetVehicleVirtualWorld(vehicleid)) && IsPlayerInRangeOfPoint(playerid, 3.5, fX, fY, fZ);
}

IsPlayerNearHood(playerid, vehicleid)
{
	static
		Float:fX,
		Float:fY,
		Float:fZ;

	GetVehicleHood(vehicleid, fX, fY, fZ);

	return (GetPlayerVirtualWorld(playerid) == GetVehicleVirtualWorld(vehicleid)) && IsPlayerInRangeOfPoint(playerid, 3.5, fX, fY, fZ);
}

SetVehicleVirtualWorldEx(vehicleid, worldid)
{
	VehicleCore[vehicleid][vWorld] = worldid;
	return SetVehicleVirtualWorld(vehicleid, worldid);
}

LinkVehicleToInteriorEx(vehicleid, interiorid)
{
	VehicleCore[vehicleid][vInterior] = interiorid;
	return LinkVehicleToInterior(vehicleid, interiorid);
}

bool:IsVehicleUpsideDown(vehicleid)
{
    new Float:quat_w,Float:quat_x,Float:quat_y,Float:quat_z;
    GetVehicleRotationQuat(vehicleid,quat_w,quat_x,quat_y,quat_z);
    new Float:y = atan2(2*((quat_y*quat_z)+(quat_w*quat_x)),(quat_w*quat_w)-(quat_x*quat_x)-(quat_y*quat_y)+(quat_z*quat_z));
    return (y > 90 || y < -90);
}

Vehicle_Nearest(playerid, Float:range = 3.5) //ngeget iterator id kendaraan
{
	static
	Float:fX,
	Float:fY,
	Float:fZ;

	foreach(new i : PvtVehicles)
	{
		if(Iter_Contains(Vehicle, PlayerVehicle[i][pVehPhysic]))
		{
			GetVehiclePos(PlayerVehicle[i][pVehPhysic], fX, fY, fZ);

			if(IsPlayerInRangeOfPoint(playerid, range, fX, fY, fZ)) 
			{
				return i;
			}
		}
	}
	return INVALID_VEHICLE_ID;
}

GetVehicleOwnerName(carid)
{
	new owname[40];
	foreach(new i : Player)
	{
		if(PlayerVehicle[carid][pVehOwnerID] == AccountData[i][pID])
		{
			format(owname, sizeof(owname), "%s", GetPlayerRoleplayName(i));
		}
	}
	return owname;
}

GetVehicleOwnerID(carid)
{
	foreach(new i : Player)
	{
		if(PlayerVehicle[carid][pVehOwnerID] == AccountData[i][pID])
		{
			return i;
		}
	}
	return INVALID_PLAYER_ID;
}

GetPlayerVehicleLimit(playerid)
{
	new limit = MAX_PLAYER_VEHICLE;
	switch(AccountData[playerid][pVIP])
	{
		case 0:
		{
			limit = MAX_PLAYER_VEHICLE;
		}
		case 1:
		{
			limit = MAX_PLAYER_VEHICLE + 1;
		}
		case 2:
		{
			limit = MAX_PLAYER_VEHICLE + 2;
		}
		case 3:
		{
			limit = MAX_PLAYER_VEHICLE + 3;
		}
	}
	return limit;
}


forward ForcePlayerHopInVehicle(playerid, vid, seatsid);
public ForcePlayerHopInVehicle(playerid, vid, seatsid)
{
	if(Iter_Contains(Vehicle, vid))
	{
		SwitchVehicleDoors(vid, false);
		VehicleCore[vid][vCoreLocked] = false;
		SwitchVehicleEngine(vid, true);
		if(!IsPlayerInAnyVehicle(playerid))
		{
			PutPlayerInVehicleEx(playerid, vid, seatsid);
		}
	}
	return 1;
}

forward ForcePlayerHopInBuyVeh(playerid, vid, seatsid);
public ForcePlayerHopInBuyVeh(playerid, vid, seatsid)
{
	DestroyVehicle(ShowroomVeh[playerid]);

	if(Iter_Contains(Vehicle, vid))
	{
		SwitchVehicleDoors(vid, false);
		VehicleCore[vid][vCoreLocked] = false;
		SwitchVehicleEngine(vid, true);
		if(!IsPlayerInAnyVehicle(playerid))
		{
			PutPlayerInVehicleEx(playerid, vid, seatsid);
		}
	}
	return 1;
}

OnPlayerVehicleRespawn(i)
{
	if(i <= -1) return 0;

	DestroyVehicle(PlayerVehicle[i][pVehPhysic]);
	PlayerVehicle[i][pVehPhysic] = INVALID_VEHICLE_ID;
	
	PlayerVehicle[i][pVehPhysic] = CreateVehicle(PlayerVehicle[i][pVehModelID], PlayerVehicle[i][pVehPos][0], PlayerVehicle[i][pVehPos][1], PlayerVehicle[i][pVehPos][2], PlayerVehicle[i][pVehPos][3], PlayerVehicle[i][pVehColor1], PlayerVehicle[i][pVehColor2], 60000, false);
	VehicleCore[PlayerVehicle[i][pVehPhysic]][vCoreFuel] = PlayerVehicle[i][pVehFuel];
	VehicleCore[PlayerVehicle[i][pVehPhysic]][vMaxHealth] = PlayerVehicle[i][pVehMaxHealth];
	VehicleCore[PlayerVehicle[i][pVehPhysic]][vIsBodyUpgraded] = PlayerVehicle[i][pVehBodyUpgraded];
	VehicleCore[PlayerVehicle[i][pVehPhysic]][vIsBodyBroken] = PlayerVehicle[i][pVehBodyBroken];
	SetVehicleNumberPlate(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehPlate]);
	SetVehicleVirtualWorldEx(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehWorld]);
	LinkVehicleToInteriorEx(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehInterior]);

	PlayerVehicle[i][pVehHandbraked] = false;

	if(PlayerVehicle[i][pVehHealth] < 350.0)
	{
		SetValidVehicleHealth(PlayerVehicle[i][pVehPhysic], 350.0);
	}
	else
	{
		SetValidVehicleHealth(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehHealth]);
	}
	UpdateVehicleDamageStatus(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehDamage][0], PlayerVehicle[i][pVehDamage][1], PlayerVehicle[i][pVehDamage][2], PlayerVehicle[i][pVehDamage][3]);
	if(PlayerVehicle[i][pVehPaintjob] != -1)
	{
		ChangeVehiclePaintjob(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehPaintjob]);
	}
	
	for(new z = 0; z < 17; z++)
	{
		if(PlayerVehicle[i][pVehMod][z]) AddVehicleComponent(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehMod][z]);
	}

	if(PlayerVehicle[i][pVehLocked])
	{
		SwitchVehicleDoors(PlayerVehicle[i][pVehPhysic], true);
		VehicleCore[PlayerVehicle[i][pVehPhysic]][vCoreLocked] = true;
	}
	else
	{
		SwitchVehicleDoors(PlayerVehicle[i][pVehPhysic], false);
		VehicleCore[PlayerVehicle[i][pVehPhysic]][vCoreLocked] = false;
	}

	if(IsEngineVehicle(PlayerVehicle[i][pVehPhysic]))
	{
		SwitchVehicleEngine(PlayerVehicle[i][pVehPhysic], false);
	}
	else
	{
		SwitchVehicleEngine(PlayerVehicle[i][pVehPhysic], true);
	}

	if(DestroyDynamic3DTextLabel(PlayerVehicle[i][pVehTireLockLabel]))
		PlayerVehicle[i][pVehTireLockLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

	if(PlayerVehicle[i][pVehTireLocked])
	{
		PlayerVehicle[i][pVehTireLockLabel] = CreateDynamic3DTextLabel("* Kendaraan ini sedang di-tirelock *", Y_GRAY, 0.0, 0.0, 0.0, 10.00, INVALID_PLAYER_ID, PlayerVehicle[i][pVehPhysic], 0, GetVehicleVirtualWorld(PlayerVehicle[i][pVehPhysic]), GetVehicleInterior(PlayerVehicle[i][pVehPhysic]), -1, 10.00, -1, 0);
	}

	AttachVehicleToys(i);
	return 1;
}

forward OnVehCreated(carid);
public OnVehCreated(carid)
{
	if (carid == -1)
	    return 0;

	PlayerVehicle[carid][pVehID] = cache_insert_id();
	SavePlayerVehicle(carid);
	return 1;
}

forward OnVehRentalCreated(playerid, carid);
public OnVehRentalCreated(playerid, carid)
{
	if(carid == -1)
	    return 0;

	PlayerVehicle[carid][pVehID] = cache_insert_id();
	SavePlayerVehicle(carid);

	SetTimerEx("ForcePlayerHopInVehicle", 1500, false, "idd", playerid, PlayerVehicle[carid][pVehPhysic], 0);
	return 1;
}

forward OnVehBuyCreated(playerid, carid);
public OnVehBuyCreated(playerid, carid)
{
	if(carid == -1)
	    return 0;

	PlayerVehicle[carid][pVehID] = cache_insert_id();
	SavePlayerVehicle(carid);

	SetTimerEx("ForcePlayerHopInBuyVeh", 2500, false, "idd", playerid, PlayerVehicle[carid][pVehPhysic], 0);
	return 1;
}

forward OnWeaponVStored(carid, id);
public OnWeaponVStored(carid, id)
{
	VehicleHolster[carid][vHolsterID][id] = cache_insert_id();
	return 1;
}

forward LoadVehicleHolster(carid);
public LoadVehicleHolster(carid)
{
	new count = cache_num_rows();
    if(count)
    {
		for(new i; i < count; i++)
		{
			for(new z; z < 3; z++)
			{
				if(!VehicleHolster[carid][vHolsterTaken][z])
				{
					cache_get_value_name_int(i, "ID", VehicleHolster[carid][vHolsterID][z]);
					cache_get_value_name_int(i, "WeaponID", VehicleHolster[carid][vHolsterWeaponID][z]);
					cache_get_value_name_int(i, "WeaponAmmo", VehicleHolster[carid][vHolsterWeaponAmmo][z]);
					VehicleHolster[carid][vHolsterTaken][z] = true;
					break;
				}
			}
		}
	}
	return 1;
}

forward LoadPlayerFactVeh(playerid);
public LoadPlayerFactVeh(playerid)
{
	new rows = cache_num_rows();
	if(rows > 0)
	{
		cache_get_value_name_int(0, "model", PlayerFactionVehStats[playerid][pFactVehModel]);
    	cache_get_value_name_float(0, "vehX", PlayerFactionVehStats[playerid][pFactVehPos][0]);
    	cache_get_value_name_float(0, "vehY", PlayerFactionVehStats[playerid][pFactVehPos][1]);
    	cache_get_value_name_float(0, "vehZ", PlayerFactionVehStats[playerid][pFactVehPos][2]);
    	cache_get_value_name_float(0, "vehA", PlayerFactionVehStats[playerid][pFactVehPos][3]);
    	cache_get_value_name_int(0, "damage0", PlayerFactionVehStats[playerid][pFactVehDamage][0]);
    	cache_get_value_name_int(0, "damage1", PlayerFactionVehStats[playerid][pFactVehDamage][1]);
    	cache_get_value_name_int(0, "damage2", PlayerFactionVehStats[playerid][pFactVehDamage][2]);
    	cache_get_value_name_int(0, "damage3", PlayerFactionVehStats[playerid][pFactVehDamage][3]);
    	cache_get_value_name_float(0, "health", PlayerFactionVehStats[playerid][pFactVehHealth]);
    	cache_get_value_name_int(0, "fuel", PlayerFactionVehStats[playerid][pFactVehFuel]);
    	cache_get_value_name_int(0, "locked", PlayerFactionVehStats[playerid][pFactVehLocked]);
    	cache_get_value_name_int(0, "world", PlayerFactionVehStats[playerid][pFactVehWorld]);
    	cache_get_value_name_int(0, "color1", PlayerFactionVehStats[playerid][pFactVehColor1]);
    	cache_get_value_name_int(0, "color2", PlayerFactionVehStats[playerid][pFactVehColor2]);
    	cache_get_value_name_float(0, "maxhealth", PlayerFactionVehStats[playerid][pFactVehMaxHealth]);
    	cache_get_value_name_int(0, "bodyupgraded", PlayerFactionVehStats[playerid][pFactVehBodyUpgraded]);
    	cache_get_value_name_int(0, "bodybroken", PlayerFactionVehStats[playerid][pFactVehBodyBroken]);

		if(!IsFloatEx(PlayerFactionVehStats[playerid][pFactVehDamage][0]))
			PlayerFactionVehStats[playerid][pFactVehDamage][0] = 0;
		if(!IsFloatEx(PlayerFactionVehStats[playerid][pFactVehDamage][1]))
			PlayerFactionVehStats[playerid][pFactVehDamage][1] = 0;
		if(!IsFloatEx(PlayerFactionVehStats[playerid][pFactVehDamage][2]))
			PlayerFactionVehStats[playerid][pFactVehDamage][2] = 0;
		if(!IsFloatEx(PlayerFactionVehStats[playerid][pFactVehDamage][3]))
			PlayerFactionVehStats[playerid][pFactVehDamage][3] = 0;
		
		DestroyVehicle(PlayerFactionVehicle[playerid][AccountData[playerid][pFaction]]);
		PlayerFactionVehicle[playerid][AccountData[playerid][pFaction]] = INVALID_VEHICLE_ID;

		PlayerFactionVehicle[playerid][AccountData[playerid][pFaction]] = CreateVehicle(PlayerFactionVehStats[playerid][pFactVehModel], PlayerFactionVehStats[playerid][pFactVehPos][0], PlayerFactionVehStats[playerid][pFactVehPos][1], PlayerFactionVehStats[playerid][pFactVehPos][2], PlayerFactionVehStats[playerid][pFactVehPos][3], PlayerFactionVehStats[playerid][pFactVehColor1], PlayerFactionVehStats[playerid][pFactVehColor2], 60000, true);
		VehicleCore[PlayerFactionVehicle[playerid][AccountData[playerid][pFaction]]][vCoreFuel] = PlayerFactionVehStats[playerid][pFactVehFuel];
		VehicleCore[PlayerFactionVehicle[playerid][AccountData[playerid][pFaction]]][vMaxHealth] = PlayerFactionVehStats[playerid][pFactVehMaxHealth];
		VehicleCore[PlayerFactionVehicle[playerid][AccountData[playerid][pFaction]]][vIsBodyUpgraded] = PlayerFactionVehStats[playerid][pFactVehBodyUpgraded];
		VehicleCore[PlayerFactionVehicle[playerid][AccountData[playerid][pFaction]]][vIsBodyBroken] = PlayerFactionVehStats[playerid][pFactVehBodyBroken];
		SetVehicleVirtualWorldEx(PlayerFactionVehicle[playerid][AccountData[playerid][pFaction]], PlayerFactionVehStats[playerid][pFactVehWorld]);
		if(PlayerFactionVehStats[playerid][pFactVehHealth] < 350.0)
		{
			SetValidVehicleHealth(PlayerFactionVehicle[playerid][AccountData[playerid][pFaction]], 350.0);
		}
		else
		{
			SetValidVehicleHealth(PlayerFactionVehicle[playerid][AccountData[playerid][pFaction]], PlayerFactionVehStats[playerid][pFactVehHealth]);
		}
		UpdateVehicleDamageStatus(PlayerFactionVehicle[playerid][AccountData[playerid][pFaction]], PlayerFactionVehStats[playerid][pFactVehDamage][0], PlayerFactionVehStats[playerid][pFactVehDamage][1], PlayerFactionVehStats[playerid][pFactVehDamage][2], PlayerFactionVehStats[playerid][pFactVehDamage][3]);
		SwitchVehicleEngine(PlayerFactionVehicle[playerid][AccountData[playerid][pFaction]], false);
		SwitchVehicleDoors(PlayerFactionVehicle[playerid][AccountData[playerid][pFaction]], PlayerFactionVehStats[playerid][pFactVehLocked]);
		VehicleCore[PlayerFactionVehicle[playerid][AccountData[playerid][pFaction]]][vCoreLocked] = PlayerFactionVehStats[playerid][pFactVehLocked];

		switch(AccountData[playerid][pFaction])
		{
			case FACTION_LSPD:
			{
				switch(PlayerFactionVehStats[playerid][pFactVehModel])
				{
					case 596..598,426,599,427,490,415,541,411,451,601:
					{
						AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1010);
						AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1025);
					}
					case 468:
					{
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][0] = CreateDynamicObject(19476,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][0], 0, "POLISI", 80, "Arial", 25, 1, -15616, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][0], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.095, 0.150, 0.321, -48.500, -29.299, 177.200);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][1] = CreateDynamicObject(19476,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][1], 0, "POLISI", 80, "Arial", 25, 1, -15616, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][1], PlayerFactionVehicle[playerid][FACTION_LSPD], 0.099, 0.145, 0.318, 42.199, -17.400, 3.399);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][2] = CreateDynamicObject(19476,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][2], 0, "8", 80, "Webdings", 50, 1, -15616, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][2], PlayerFactionVehicle[playerid][FACTION_LSPD], 0.162, -0.484, 0.124, -12.300, -0.399, 6.799);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][3] = CreateDynamicObject(19476,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][3], 0, "8", 80, "Webdings", 50, 1, -15616, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][3], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.157, -0.485, 0.124, 0.000, 2.200, -3.799);
					}
					case 560:
					{
						AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1010);
						AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1025);

						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][0] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][0], 0, "POLISI", 130, "Arial", 100, 1, -15616, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][0], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.009, 1.980, 0.290, 360.040, 279.000, 90.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][1] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][1], 0, "|||||", 130, "Arial", 50, 1, -15616, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][1], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.026, -2.368, 0.220, 0.000, 5.000, 90.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][2] = CreateDynamicObject(19620,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][2], PlayerFactionVehicle[playerid][FACTION_LSPD], 0.000, 0.000, 0.850, 0.000, 0.000, 0.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][3] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][3], 0, "______", 130, "Arial", 100, 1, -15616, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][3], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.009, -0.620, 0.812, 360.040, -274.000, -90.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][4] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][4], 0, "______", 130, "Arial", 100, 1, -15616, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][4], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.009, -0.620, 0.800, -360.040, 274.000, -90.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][5] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][5], 0, "SABHARA", 130, "Arial", 50, 0, -15616, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][5], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.009, -0.620, 0.792, 180.000, 90.000, 90.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][6] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][6], 0, "g", 140, "Webdings", 50, 1, -15616, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][6], PlayerFactionVehicle[playerid][FACTION_LSPD], -1.026, -1.789, 0.220, 0.000, 10.000, 0.000);
					}
					case 428:
					{
						AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1010);
						AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1025);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][0] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][0], 0, "LOS SANTOS", 140, "Arial", 40, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][0], PlayerFactionVehicle[playerid][FACTION_LSPD], -1.160, -0.520, 0.220, 0.000, 0.000, 0.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][1] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][1], 0, "POLICE DEPARTMENT", 140, "Arial", 40, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][1], PlayerFactionVehicle[playerid][FACTION_LSPD], -1.160, -1.710, 0.220, 0.000, 0.000, 0.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][2] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][2], 0, "S.W.A.T", 140, "Arial", 70, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][2], PlayerFactionVehicle[playerid][FACTION_LSPD], -1.160, -2.361, 0.830, 0.000, 0.000, 0.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][3] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][3], 0, "SPECIAL WEAPONS", 140, "Arial", 40, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][3], PlayerFactionVehicle[playerid][FACTION_LSPD], -1.160, -0.790, 0.040, 0.000, 0.000, 0.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][4] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][4], 0, "AND TACTICS", 140, "Arial", 40, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][4], PlayerFactionVehicle[playerid][FACTION_LSPD], -1.160, -1.920, 0.040, 0.000, 0.000, 0.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][5] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][5], 0, "METRO POLICE", 140, "Arial", 40, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][5], PlayerFactionVehicle[playerid][FACTION_LSPD], -1.160, -2.341, 1.040, 0.000, 0.000, 0.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][6] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][6], 0, "S.W.A.T", 140, "Arial", 70, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][6], PlayerFactionVehicle[playerid][FACTION_LSPD], 1.158, -2.361, 0.830, 0.000, 0.000, 180.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][7] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][7], 0, "METRO POLICE", 140, "Arial", 40, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][7], PlayerFactionVehicle[playerid][FACTION_LSPD], 1.159, -2.341, 1.040, 0.000, 0.000, 180.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][8] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][8], 0, "POLICE DEPARTMENT", 140, "Arial", 40, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][8], PlayerFactionVehicle[playerid][FACTION_LSPD], 1.160, -0.520, 0.220, 0.000, 0.000, 180.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][9] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][9], 0, "LOS SANTOS", 140, "Arial", 40, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][9], PlayerFactionVehicle[playerid][FACTION_LSPD], 1.159, -1.710, 0.220, 0.000, 0.000, 180.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][10] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][10], 0, "AND TACTICS", 140, "Arial", 40, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][10], PlayerFactionVehicle[playerid][FACTION_LSPD], 1.160, -0.299, 0.040, 0.000, 0.000, 180.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][11] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][11], 0, "SPECIAL WEAPONS", 140, "Arial", 40, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][11], PlayerFactionVehicle[playerid][FACTION_LSPD], 1.159, -1.432, 0.040, 0.000, 0.000, 180.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][12] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][12], 0, "S.W.A.T", 140, "Arial", 40, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][12], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.010, 1.250, 1.090, 0.000, 0.000, 270.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][13] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][13], 0, "S.W.A.T", 140, "Arial", 40, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][13], PlayerFactionVehicle[playerid][FACTION_LSPD], 0.009, -3.010, -0.679, 0.000, 0.000, 450.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][14] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][14], PlayerFactionVehicle[playerid][FACTION_LSPD], 0.760, 2.820, -0.540, 0.000, 0.000, 180.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][15] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][15], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.760, 2.820, -0.540, 360.000, 180.000, 180.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][16] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][16], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.289, 2.699, 0.040, 360.000, 0.000, 180.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][17] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][17], PlayerFactionVehicle[playerid][FACTION_LSPD], 0.280, 2.699, 0.040, 0.000, 180.000, 180.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][18] = CreateDynamicObject(19419,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][18], PlayerFactionVehicle[playerid][FACTION_LSPD], 0.000, 0.790, 1.300, 0.000, 0.000, 0.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][19] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][19], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.460, -3.020, -0.540, 0.000, 360.000, 0.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][20] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][20], PlayerFactionVehicle[playerid][FACTION_LSPD], 0.460, -3.020, -0.540, 360.000, 180.000, 0.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][21] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][21], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.460, -2.980, 1.449, 0.000, 180.000, 0.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][22] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][22], PlayerFactionVehicle[playerid][FACTION_LSPD], 0.460, -2.980, 1.450, 0.000, 360.000, 0.000);
					}
					case 554:
					{
						AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1010);
						AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1025);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][0] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][0], 0, "<<", 130, "Impact", 130, 1, -16777216, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][0], PlayerFactionVehicle[playerid][FACTION_LSPD], -1.229, 0.640, 0.050, 0.000, 0.000, 0.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][1] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][1], 0, "POLISI", 100, "Arial Black", 65, 1, -16777216, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][1], PlayerFactionVehicle[playerid][FACTION_LSPD], -1.229, -0.489, 0.080, 0.000, 0.000, 0.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][2] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][2], 0, "EMERGENCY", 140, "Arial Black", 35, 1, -4877296, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][2], PlayerFactionVehicle[playerid][FACTION_LSPD], -1.199, -2.299, 0.230, 0.000, 0.000, 0.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][3] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][3], 0, "POLISI", 100, "Arial Black", 65, 1, -16777216, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][3], PlayerFactionVehicle[playerid][FACTION_LSPD], 1.220, -0.469, 0.080, 0.000, 0.000, 180.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][4] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][4], 0, "CALL 110", 140, "Arial Black", 35, 1, -4877296, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][4], PlayerFactionVehicle[playerid][FACTION_LSPD], -1.219, -2.389, 0.120, 360.000, 360.000, 360.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][5] = CreateDynamicObject(19419,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][5], PlayerFactionVehicle[playerid][FACTION_LSPD], 0.000, -0.009, 1.030, 0.000, 0.000, 0.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][6] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][6], 0, ">>", 130, "Impact", 130, 1, -16777216, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][6], PlayerFactionVehicle[playerid][FACTION_LSPD], 1.220, 0.640, 0.050, 0.000, 0.000, 180.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][7] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][7], 0, "EMERGENCY", 140, "Arial Black", 35, 1, -4877296, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][7], PlayerFactionVehicle[playerid][FACTION_LSPD], 1.210, -2.294, 0.230, 0.000, 0.000, 540.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][8] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][8], 0, "CALL 110", 140, "Arial Black", 35, 1, -4877296, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][8], PlayerFactionVehicle[playerid][FACTION_LSPD], 1.220, -2.379, 0.120, 0.000, 0.000, 180.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][9] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][9], 0, "POLISI", 140, "Arial Black", 75, 1, -4877296, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][9], PlayerFactionVehicle[playerid][FACTION_LSPD], 0.010, 0.657, 0.851, 0.000, 48.099, 270.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][10] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][10], 0, ">", 120, "Calibri", 195, 1, -4877296, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][10], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.159, 1.990, 0.406, 4.799, 90.000, 900.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][11] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][11], 0, ">", 120, "Calibri", 195, 1, -4877296, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][11], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.159, 1.720, 0.427, 364.000, 450.000, 540.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][12] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][12], PlayerFactionVehicle[playerid][FACTION_LSPD], 0.230, 2.591, 0.170, 0.000, 0.000, 180.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][13] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][13], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.230, 2.591, 0.170, 360.000, 180.000, 180.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][14] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][14], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.750, 2.631, -0.120, 0.000, 0.000, 180.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][15] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][15], PlayerFactionVehicle[playerid][FACTION_LSPD], 0.739, 2.631, -0.120, 360.000, 180.000, 180.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][16] = CreateDynamicObject(19285,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][16], PlayerFactionVehicle[playerid][FACTION_LSPD], 0.000, 0.080, 1.030, 0.000, 0.000, 0.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][17] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][17], 0, "POLISI", 140, "Arial Black", 80, 1, -4877296, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][17], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.018, -2.899, 0.000, 0.000, 0.000, 90.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][18] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][18], 0, "<", 110, "Calibri", 130, 1, -4877296, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][18], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.179, -2.900, 0.220, 270.000, 0.000, 450.000);
					}
				}
			}
			case FACTION_LSFD:
			{
				switch(PlayerFactionVehStats[playerid][pFactVehModel])
				{
					case 416:
					{
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][0] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][0], 0, "EMT", 140, "Arial", 55, 1, -282565, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][0], PlayerFactionVehicle[playerid][FACTION_LSFD], -1.289, -2.910, 0.930, 0.000, 0.000, 0.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][1] = CreateDynamicObject(2658,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterial(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][1], 0, 19267, "mapmarkers", "red-2", 0);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][1], PlayerFactionVehicle[playerid][FACTION_LSFD], -1.300, -2.739, 0.870, 360.000, 90.000, 270.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][2] = CreateDynamicObject(2658,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterial(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][2], 0, 19267, "mapmarkers", "red-2", 0);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][2], PlayerFactionVehicle[playerid][FACTION_LSFD], 1.300, -2.789, 0.870, 720.000, 630.000, 90.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][3] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][3], 0, "EMT", 100, "Arial", 75, 1, -282565, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][3], PlayerFactionVehicle[playerid][FACTION_LSFD], 0.009, -1.450, 1.720, 360.000, 90.000, 90.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][4] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][4], 0, "EMERGENCY MEDICAL", 140, "Arial", 25, 1, -282565, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][4], PlayerFactionVehicle[playerid][FACTION_LSFD], 0.019, -1.800, 1.710, 0.000, 90.000, 90.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][5] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][5], 0, "EMT", 140, "Arial", 55, 1, -282565, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][5], PlayerFactionVehicle[playerid][FACTION_LSFD], 1.290, -2.910, 0.950, 900.000, 1260.000, 360.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][6] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][6], 0, "KOTA PAHLAWAN", 140, "Arial", 31, 1, -282565, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][6], PlayerFactionVehicle[playerid][FACTION_LSFD], -1.289, -2.900, 0.750, 0.000, 0.000, 0.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][7] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterial(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][7], 0, 19267, "mapmarkers", "red-2", 0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][7], 0, "KOTA PAHLAWAN", 140, "Arial", 31, 1, -282565, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][7], PlayerFactionVehicle[playerid][FACTION_LSFD], 1.291, -2.900, 0.770, 0.000, 0.000, 540.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][8] = CreateDynamicObject(2643,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterial(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][8], 0, 19655, "mattubes", "greendirt1", 0);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][8], PlayerFactionVehicle[playerid][FACTION_LSFD], 0.000, -1.510, 1.620, 270.000, 0.000, 0.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][9] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][9], 0, "TECHNICIAN", 140, "Arial", 25, 1, -282565, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][9], PlayerFactionVehicle[playerid][FACTION_LSFD], 0.019, -1.940, 1.710, 360.000, 90.000, 90.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][10] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][10], 0, "PAHLAWAN", 140, "Arial", 75, 1, -16751616, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][10], PlayerFactionVehicle[playerid][FACTION_LSFD], 0.009, -2.451, 1.720, 0.000, 90.000, 90.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][11] = CreateDynamicObject(11701,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][11], PlayerFactionVehicle[playerid][FACTION_LSFD], 0.001, 0.890, 1.231, 0.000, 0.000, 0.000);
					}
					case 490:
					{
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][0] = CreateDynamicObject(11701,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][0], PlayerFactionVehicle[playerid][FACTION_LSFD], 0.000, 0.410, 1.130, 0.000, 0.000, 0.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][1] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][1], 0, "EMT", 140, "Arial", 155, 1, -282565, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][1], PlayerFactionVehicle[playerid][FACTION_LSFD], -1.200, -0.306, 0.050, 360.000, 360.000, 1080.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][2] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][2], 0, "EMT", 140, "Arial", 55, 1, -282565, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][2], PlayerFactionVehicle[playerid][FACTION_LSFD], -0.280, -3.168, 0.140, 0.000, 0.000, 450.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][3] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterial(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][3], 0, 19267, "mapmarkers", "red-2", 0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][3], 0, "KOTA PAHLAWAN", 140, "Arial", 31, 1, -282565, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][3], PlayerFactionVehicle[playerid][FACTION_LSFD], -0.300, -3.169, 0.000, 0.000, 0.000, 90.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][4] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterial(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][4], 0, 19267, "mapmarkers", "red-2", 0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][4], 0, "KOTA PAHLAWAN", 140, "Arial", 31, 1, -282565, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][4], PlayerFactionVehicle[playerid][FACTION_LSFD], -1.201, -0.318, -0.210, 0.000, 0.000, 0.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][5] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][5], 0, "EMT", 140, "Arial", 155, 1, -282565, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][5], PlayerFactionVehicle[playerid][FACTION_LSFD], 1.200, -0.216, 0.050, 0.000, 0.000, 180.000);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][6] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						SetDynamicObjectMaterial(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][6], 0, 19267, "mapmarkers", "red-2", 0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][6], 0, "KOTA PAHLAWAN", 140, "Arial", 31, 1, -282565, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][6], PlayerFactionVehicle[playerid][FACTION_LSFD], 1.199, -0.228, -0.210, 0.000, 0.000, 180.000);
					}
				}
			}
			case FACTION_UBER:
			{
				switch(PlayerFactionVehStats[playerid][pFactVehModel])
				{
					case 410:
					{
						AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_UBER], 1097);
						AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_UBER], 1023);
						AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_UBER], 1013);
						AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_UBER], 1019);
						AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_UBER], 1007);
						AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_UBER], 1017);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][0] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][0], 0, "UBER", 100, "Arial", 25, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][0], PlayerFactionVehicle[playerid][FACTION_UBER], -0.980, 0.390, 0.170, 0.000, 0.000, 0.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][1] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][1], 0, "UBER", 100, "Arial", 25, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][1], PlayerFactionVehicle[playerid][FACTION_UBER], 0.980, 0.390, 0.170, 0.000, 0.000, 540.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][2] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][2], 0, "ADVANCED", 140, "Arial", 25, 1, -12068873, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][2], PlayerFactionVehicle[playerid][FACTION_UBER], -0.991, -0.149, 0.030, 0.000, 0.000, 360.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][3] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][3], 0, "TECHNOLOGIES", 140, "Arial", 25, 1, -12068873, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][3], PlayerFactionVehicle[playerid][FACTION_UBER], -0.992, -0.049, -0.060, 0.000, 0.000, 360.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][4] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][4], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][4], PlayerFactionVehicle[playerid][FACTION_UBER], 0.987, 0.580, -0.079, 90.000, 360.000, 180.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][5] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][5], 0, "ADVANCED", 140, "Arial", 25, 1, -12068873, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][5], PlayerFactionVehicle[playerid][FACTION_UBER], 0.991, -0.149, 0.030, 0.000, 0.000, 180.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][6] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][6], 0, "TECHNOLOGIES", 140, "Arial", 25, 1, -12068873, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][6], PlayerFactionVehicle[playerid][FACTION_UBER], 0.992, -0.049, -0.060, 0.000, 0.000, 180.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][7] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][7], 0, "CENTER", 140, "Arial", 25, 1, -12068873, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][7], PlayerFactionVehicle[playerid][FACTION_UBER], 0.980, -0.199, -0.150, 0.000, 0.000, 540.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][8] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][8], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][8], PlayerFactionVehicle[playerid][FACTION_UBER], 0.987, 0.630, -0.079, 90.000, 0.000, 180.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][9] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][9], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][9], PlayerFactionVehicle[playerid][FACTION_UBER], 0.987, 0.682, -0.079, 90.000, 0.000, 180.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][10] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][10], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][10], PlayerFactionVehicle[playerid][FACTION_UBER], -0.993, 0.682, -0.079, 90.000, 360.000, 0.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][11] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][11], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][11], PlayerFactionVehicle[playerid][FACTION_UBER], -0.987, 0.630, -0.079, 90.000, 0.000, 720.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][12] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][12], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][12], PlayerFactionVehicle[playerid][FACTION_UBER], -0.987, 0.580, -0.079, 90.000, 0.000, 0.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][13] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][13], 0, "UBERATC.COM/CAR", 140, "Arial", 20, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][13], PlayerFactionVehicle[playerid][FACTION_UBER], -0.962, -1.160, 0.230, 360.000, 745.000, 0.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][14] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][14], 0, "UBERATC.COM/CAR", 140, "Arial", 20, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][14], PlayerFactionVehicle[playerid][FACTION_UBER], 0.962, -1.160, 0.230, 0.000, 20.000, 540.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][15] = CreateDynamicObject(19309,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterial(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][15], 0, 10765, "airportgnd_sfse", "black64", 0);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][15], PlayerFactionVehicle[playerid][FACTION_UBER], 0.000, -0.470, 0.990, 0.000, 0.000, 0.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][16] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][16], 0, "Uber", 140, "Arial Narrow", 50, 0, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][16], PlayerFactionVehicle[playerid][FACTION_UBER], -0.080, -0.479, 0.990, 0.000, 0.000, 0.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][17] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][17], 0, "Uber", 140, "Arial Narrow", 50, 0, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][17], PlayerFactionVehicle[playerid][FACTION_UBER], 0.080, -0.479, 0.990, 0.000, 0.000, 180.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][18] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][18], 0, "CENTER", 140, "Arial", 25, 1, -12068873, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][18], PlayerFactionVehicle[playerid][FACTION_UBER], -0.980, -0.199, -0.150, 0.000, 0.000, 720.000);
					}
					case 458:
					{
						AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_UBER], 1097);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][0] = CreateDynamicObject(19309,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterial(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][0], 0, 10765, "airportgnd_sfse", "black64", 0);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][0], PlayerFactionVehicle[playerid][FACTION_UBER], -0.009, -0.530, 0.830, 0.000, 0.000, 0.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][1] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][1], 0, "UBER", 100, "Arial", 25, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][1], PlayerFactionVehicle[playerid][FACTION_UBER], -1.131, 0.720, 0.000, 0.000, 0.000, 0.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][2] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][2], 0, "TECHNOLOGIES", 140, "Arial", 25, 1, -12068873, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][2], PlayerFactionVehicle[playerid][FACTION_UBER], -1.125, 0.280, -0.290, 0.000, 0.000, 0.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][3] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][3], 0, "ADVANCED", 140, "Arial", 25, 1, -12068873, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][3], PlayerFactionVehicle[playerid][FACTION_UBER], -1.120, 0.180, -0.180, 0.000, 0.000, 0.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][4] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][4], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][4], PlayerFactionVehicle[playerid][FACTION_UBER], -1.130, 0.910, -0.300, 90.000, 0.000, 360.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][5] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][5], 0, "CENTER", 140, "Arial", 25, 1, -12068873, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][5], PlayerFactionVehicle[playerid][FACTION_UBER], -1.090, 0.120, -0.410, 0.000, 0.000, 0.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][6] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][6], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][6], PlayerFactionVehicle[playerid][FACTION_UBER], -1.130, 0.970, -0.300, 90.000, 0.000, 360.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][7] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][7], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][7], PlayerFactionVehicle[playerid][FACTION_UBER], -1.130, 1.030, -0.300, 90.000, 0.000, 0.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][8] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][8], 0, "UBERATC.COM/CAR", 140, "Arial", 20, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][8], PlayerFactionVehicle[playerid][FACTION_UBER], -1.111, -1.040, 0.000, 0.000, 20.000, 0.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][9] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][9], 0, "UBER", 100, "Arial", 25, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][9], PlayerFactionVehicle[playerid][FACTION_UBER], 1.119, 0.720, 0.000, 0.000, 0.000, 180.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][10] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][10], 0, "ADVANCED", 140, "Arial", 25, 1, -12068873, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][10], PlayerFactionVehicle[playerid][FACTION_UBER], 1.120, 0.180, -0.180, 0.000, 0.000, 180.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][11] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][11], 0, "TECHNOLOGIES", 140, "Arial", 25, 1, -12068873, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][11], PlayerFactionVehicle[playerid][FACTION_UBER], 1.134, 0.280, -0.290, 0.000, 0.000, 180.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][12] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][12], 0, "CENTER", 140, "Arial", 25, 1, -12068873, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][12], PlayerFactionVehicle[playerid][FACTION_UBER], 1.099, 0.123, -0.410, 0.000, 0.000, 180.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][13] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][13], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][13], PlayerFactionVehicle[playerid][FACTION_UBER], 1.129, 0.910, -0.300, 90.000, 0.000, 540.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][14] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][14], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][14], PlayerFactionVehicle[playerid][FACTION_UBER], 1.130, 0.970, -0.300, 90.000, 0.000, 180.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][15] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][15], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][15], PlayerFactionVehicle[playerid][FACTION_UBER], 1.129, 1.030, -0.300, 90.000, 0.000, 180.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][16] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][16], 0, "UBERATC.COM/CAR", 140, "Arial", 20, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][16], PlayerFactionVehicle[playerid][FACTION_UBER], 1.110, -1.040, 0.000, 0.000, 20.000, 180.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][17] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][17], 0, "Uber", 140, "Arial Narrow", 50, 0, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][17], PlayerFactionVehicle[playerid][FACTION_UBER], -0.090, -0.540, 0.830, 0.000, 0.000, 0.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][18] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][18], 0, "Uber", 140, "Arial Narrow", 50, 0, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][18], PlayerFactionVehicle[playerid][FACTION_UBER], 0.070, -0.540, 0.830, 0.000, 0.000, 180.000);
					}
					case 551:
					{
						AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_UBER], 1097);
						AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_UBER], 1002);
						AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_UBER], 1005);
						AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_UBER], 1018);
						AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_UBER], 1006);
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][0] = CreateDynamicObject(19309,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterial(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][0], 0, 10765, "airportgnd_sfse", "black64", 0);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][0], PlayerFactionVehicle[playerid][FACTION_UBER], 0.000, -0.540, 0.980, 0.000, 0.000, 0.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][1] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][1], 0, "Uber", 140, "Arial Narrow", 50, 0, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][1], PlayerFactionVehicle[playerid][FACTION_UBER], -0.080, -0.550, 0.980, 0.000, 0.000, 0.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][2] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][2], 0, "Uber", 140, "Arial Narrow", 50, 0, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][2], PlayerFactionVehicle[playerid][FACTION_UBER], 0.079, -0.550, 0.980, 0.000, 0.000, 180.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][3] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][3], 0, "UBER", 100, "Arial", 25, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][3], PlayerFactionVehicle[playerid][FACTION_UBER], -1.130, 0.630, 0.089, 0.000, 0.000, 0.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][4] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][4], 0, "TECHNOLOGIES", 140, "Arial", 25, 1, -12068873, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][4], PlayerFactionVehicle[playerid][FACTION_UBER], -1.140, 0.200, -0.220, 0.000, 0.000, 0.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][5] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][5], 0, "ADVANCED", 140, "Arial", 25, 1, -12068873, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][5], PlayerFactionVehicle[playerid][FACTION_UBER], -1.139, 0.100, -0.130, 0.000, 0.000, 0.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][6] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][6], 0, "CENTER", 140, "Arial", 25, 1, -12068873, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][6], PlayerFactionVehicle[playerid][FACTION_UBER], -1.129, 0.040, -0.320, 0.000, 0.000, 0.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][7] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][7], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][7], PlayerFactionVehicle[playerid][FACTION_UBER], -1.140, 0.800, -0.210, 90.000, 360.000, 360.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][8] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][8], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][8], PlayerFactionVehicle[playerid][FACTION_UBER], -1.140, 0.860, -0.210, 90.000, 0.000, 0.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][9] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][9], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][9], PlayerFactionVehicle[playerid][FACTION_UBER], -1.140, 0.920, -0.210, 90.000, 0.000, 0.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][10] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][10], 0, "UBERATC.COM/CAR", 140, "Arial", 20, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][10], PlayerFactionVehicle[playerid][FACTION_UBER], -1.110, -0.919, 0.190, 720.000, 20.000, 0.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][11] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][11], 0, "UBER", 100, "Arial", 25, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][11], PlayerFactionVehicle[playerid][FACTION_UBER], 1.130, 0.630, 0.090, 0.000, 0.000, 180.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][12] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][12], 0, "TECHNOLOGIES", 140, "Arial", 25, 1, -12068873, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][12], PlayerFactionVehicle[playerid][FACTION_UBER], 1.140, 0.200, -0.220, 0.000, 0.000, 180.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][13] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][13], 0, "ADVANCED", 140, "Arial", 25, 1, -12068873, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][13], PlayerFactionVehicle[playerid][FACTION_UBER], 1.141, 0.100, -0.130, 0.000, 0.000, 180.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][14] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][14], 0, "CENTER", 140, "Arial", 25, 1, -12068873, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][14], PlayerFactionVehicle[playerid][FACTION_UBER], 1.131, 0.050, -0.320, 0.000, 0.000, 180.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][15] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][15], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][15], PlayerFactionVehicle[playerid][FACTION_UBER], 1.139, 0.800, -0.210, 90.000, 0.000, 180.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][16] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][16], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][16], PlayerFactionVehicle[playerid][FACTION_UBER], 1.140, 0.860, -0.210, 90.000, 0.000, 180.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][17] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][17], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][17], PlayerFactionVehicle[playerid][FACTION_UBER], 1.140, 0.920, -0.210, 90.000, 0.000, 180.000);
						
						FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][18] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
						SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][18], 0, "UBERATC.COM/CAR", 140, "Arial", 20, 1, -1, 0, 1);
						AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][18], PlayerFactionVehicle[playerid][FACTION_UBER], 1.110, -0.919, 0.190, 360.000, 20.000, 180.000);
					}
				}
			}
		}
		ChangeVehicleColor(PlayerFactionVehicle[playerid][AccountData[playerid][pFaction]], PlayerFactionVehStats[playerid][pFactVehColor1], PlayerFactionVehStats[playerid][pFactVehColor2]);
	}
	return 1;
}

forward LoadPlayerVehicle(playerid);
public LoadPlayerVehicle(playerid)
{
	new string[512], rows = cache_num_rows();
	if(rows > 0)
	{
		for(new z = 0; z < rows; z++)
		{
			new i = Iter_Free(PvtVehicles);

			if(i > -1)
			{
				Iter_Add(PvtVehicles, i);

				cache_get_value_name_int(z, "id", PlayerVehicle[i][pVehID]);
				//PlayerVehicle[i][VehicleOwned] = true;
				cache_get_value_name_int(z, "PVeh_Owner", PlayerVehicle[i][pVehOwnerID]);				
				cache_get_value_name_int(z, "PVeh_ModelID", PlayerVehicle[i][pVehModelID]);
				cache_get_value_name_int(z, "PVeh_Price", PlayerVehicle[i][pVehPrice]);
				cache_get_value_name_int(z, "PVeh_Parked", PlayerVehicle[i][pVehParked]);
				cache_get_value_name_int(z, "PVeh_Familied", PlayerVehicle[i][pVehFamGarage]);
				cache_get_value_name_int(z, "PVeh_Housed", PlayerVehicle[i][pVehHouseGarage]);
				cache_get_value_name_int(z, "PVeh_RentTime", PlayerVehicle[i][pVehRentTime]);
				cache_get_value_name_int(z, "PVeh_Rental", PlayerVehicle[i][pVehRental]);
				cache_get_value_name(z, "PVeh_Plate", PlayerVehicle[i][pVehPlate]);
				cache_get_value_name_int(z, "PVeh_PlateTime", PlayerVehicle[i][pVehPlateTime]);

				cache_get_value_name_float(z, "PVeh_Health", PlayerVehicle[i][pVehHealth]);
				cache_get_value_name_int(z, "PVeh_BodyUpgraded", PlayerVehicle[i][pVehBodyUpgraded]);
				cache_get_value_name_int(z, "PVeh_BodyBroken", PlayerVehicle[i][pVehBodyBroken]);
				cache_get_value_name_float(z, "PVeh_MaxHealth", PlayerVehicle[i][pVehMaxHealth]);
				if(PlayerVehicle[i][pVehHealth] < 0.0 || PlayerVehicle[i][pVehHealth] > PlayerVehicle[i][pVehMaxHealth]) 
					PlayerVehicle[i][pVehHealth] = PlayerVehicle[i][pVehMaxHealth];

				cache_get_value_name_int(z, "PVeh_Fuel", PlayerVehicle[i][pVehFuel]);
				cache_get_value_name_int(z, "PVeh_Locked", PlayerVehicle[i][pVehLocked]);
				cache_get_value_name_int(z, "PVeh_Mod0", PlayerVehicle[i][pVehMod][0]);
				cache_get_value_name_int(z, "PVeh_Mod1", PlayerVehicle[i][pVehMod][1]);
				cache_get_value_name_int(z, "PVeh_Mod2", PlayerVehicle[i][pVehMod][2]);
				cache_get_value_name_int(z, "PVeh_Mod3", PlayerVehicle[i][pVehMod][3]);
				cache_get_value_name_int(z, "PVeh_Mod4", PlayerVehicle[i][pVehMod][4]);
				cache_get_value_name_int(z, "PVeh_Mod5", PlayerVehicle[i][pVehMod][5]);
				cache_get_value_name_int(z, "PVeh_Mod6", PlayerVehicle[i][pVehMod][6]);
				cache_get_value_name_int(z, "PVeh_Mod7", PlayerVehicle[i][pVehMod][7]);
				cache_get_value_name_int(z, "PVeh_Mod8", PlayerVehicle[i][pVehMod][8]);
				cache_get_value_name_int(z, "PVeh_Mod9", PlayerVehicle[i][pVehMod][9]);
				cache_get_value_name_int(z, "PVeh_Mod10", PlayerVehicle[i][pVehMod][10]);
				cache_get_value_name_int(z, "PVeh_Mod11", PlayerVehicle[i][pVehMod][11]);
				cache_get_value_name_int(z, "PVeh_Mod12", PlayerVehicle[i][pVehMod][12]);
				cache_get_value_name_int(z, "PVeh_Mod13", PlayerVehicle[i][pVehMod][13]);
				cache_get_value_name_int(z, "PVeh_Mod14", PlayerVehicle[i][pVehMod][14]);
				cache_get_value_name_int(z, "PVeh_Mod15", PlayerVehicle[i][pVehMod][15]);
				cache_get_value_name_int(z, "PVeh_Mod16", PlayerVehicle[i][pVehMod][16]);
				cache_get_value_name_int(z, "PVeh_Damage0", PlayerVehicle[i][pVehDamage][0]);
				cache_get_value_name_int(z, "PVeh_Damage1", PlayerVehicle[i][pVehDamage][1]);
				cache_get_value_name_int(z, "PVeh_Damage2", PlayerVehicle[i][pVehDamage][2]);
				cache_get_value_name_int(z, "PVeh_Damage3", PlayerVehicle[i][pVehDamage][3]);
				cache_get_value_name_float(z, "PVeh_PosX", PlayerVehicle[i][pVehPos][0]);
				cache_get_value_name_float(z, "PVeh_PosY", PlayerVehicle[i][pVehPos][1]);
				cache_get_value_name_float(z, "PVeh_PosZ", PlayerVehicle[i][pVehPos][2]);
				cache_get_value_name_float(z, "PVeh_PosA", PlayerVehicle[i][pVehPos][3]);
				cache_get_value_name_int(z, "PVeh_Neon", PlayerVehicle[i][pVehNeon]); //batas
				cache_get_value_name_int(z, "PVeh_Paintjob", PlayerVehicle[i][pVehPaintjob]);
				cache_get_value_name_int(z, "PVeh_Color1", PlayerVehicle[i][pVehColor1]);
				cache_get_value_name_int(z, "PVeh_Color2", PlayerVehicle[i][pVehColor2]);
				cache_get_value_name_int(z, "PVeh_World", PlayerVehicle[i][pVehWorld]);
				cache_get_value_name_int(z, "PVeh_Interior", PlayerVehicle[i][pVehInterior]);
				cache_get_value_name_int(z, "PVeh_Impounded", PlayerVehicle[i][pVehImpounded]);
				cache_get_value_name_int(z, "PVeh_ImpoundDuration", PlayerVehicle[i][pVehImpoundReason]);
				cache_get_value_name_int(z, "PVeh_ImpoundFee", PlayerVehicle[i][pVehImpoundFee]);
				cache_get_value_name(z, "PVeh_ImpoundReason", PlayerVehicle[i][pVehImpoundReason]);
				cache_get_value_name_int(z, "PVeh_Insuranced", PlayerVehicle[i][pVehInsuranced]);
				cache_get_value_name_int(z, "PVeh_TireLocked", PlayerVehicle[i][pVehTireLocked]);
				
				PlayerVehicle[i][pVehHandbraked] = false;
				
				if(PlayerVehicle[i][pVehImpounded] || PlayerVehicle[i][pVehInsuranced] || PlayerVehicle[i][pVehParked] > -1 || PlayerVehicle[i][pVehFamGarage] > -1 || PlayerVehicle[i][pVehHouseGarage] > -1) //jika kendaraan diimpound maka tidak akan di spawn / tetap terimpound
				{
					PlayerVehicle[i][pVehPhysic] = INVALID_VEHICLE_ID;
				}
				else //jika kendaraan tidak di impound maka dicek disconnect time
				{
					OnPlayerVehicleRespawn(i);
				}

				mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `vehicle_holster` WHERE `Veh_DBID` = %d", PlayerVehicle[i][pVehID]);
				mysql_pquery(g_SQL, string, "LoadVehicleHolster", "i", i);

				mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `vehicle_bagasi` WHERE `Veh_DBID` = %d", PlayerVehicle[i][pVehID]);
				mysql_pquery(g_SQL, string, "LoadVehicleBagasi", "i", i);

				MySQL_LoadVehicleToys(i);
			}
		}
		printf("[Player Vehicle] Jumlah total Vehicle yang dimuat untuk %s [DBID: %d]: %d.", AccountData[playerid][pUCP], AccountData[playerid][pID], rows);
	}
	return 1;
}

RemovePlayerFactionVehicle(playerid)
{
	if(AccountData[playerid][pFaction] < 1) return 1;
	
	if(Iter_Contains(Vehicle, PlayerFactionVehicle[playerid][AccountData[playerid][pFaction]]))
	{
		PlayerFactionVehStats[playerid][pFactVehModel] = GetVehicleModel(PlayerFactionVehicle[playerid][AccountData[playerid][pFaction]]);

		GetVehicleDamageStatus(PlayerFactionVehicle[playerid][AccountData[playerid][pFaction]], PlayerFactionVehStats[playerid][pFactVehDamage][0], PlayerFactionVehStats[playerid][pFactVehDamage][1], PlayerFactionVehStats[playerid][pFactVehDamage][2], PlayerFactionVehStats[playerid][pFactVehDamage][3]);
		
		GetVehicleHealth(PlayerFactionVehicle[playerid][AccountData[playerid][pFaction]], PlayerFactionVehStats[playerid][pFactVehHealth]);
		if(PlayerFactionVehStats[playerid][pFactVehHealth] < 0.0 || PlayerFactionVehStats[playerid][pFactVehHealth] > VehicleCore[PlayerFactionVehicle[playerid][AccountData[playerid][pFaction]]][vMaxHealth]) PlayerFactionVehStats[playerid][pFactVehHealth] = VehicleCore[PlayerFactionVehicle[playerid][AccountData[playerid][pFaction]]][vMaxHealth];
		PlayerFactionVehStats[playerid][pFactVehMaxHealth] = VehicleCore[PlayerFactionVehicle[playerid][AccountData[playerid][pFaction]]][vMaxHealth];
		PlayerFactionVehStats[playerid][pFactVehBodyUpgraded] = VehicleCore[PlayerFactionVehicle[playerid][AccountData[playerid][pFaction]]][vIsBodyUpgraded];
		PlayerFactionVehStats[playerid][pFactVehBodyBroken] = VehicleCore[PlayerFactionVehicle[playerid][AccountData[playerid][pFaction]]][vIsBodyBroken];

		PlayerFactionVehStats[playerid][pFactVehFuel] = VehicleCore[PlayerFactionVehicle[playerid][AccountData[playerid][pFaction]]][vCoreFuel];
		PlayerFactionVehStats[playerid][pFactVehLocked] = VehicleCore[PlayerFactionVehicle[playerid][AccountData[playerid][pFaction]]][vCoreLocked];
		PlayerFactionVehStats[playerid][pFactVehWorld] = GetVehicleVirtualWorld(PlayerFactionVehicle[playerid][AccountData[playerid][pFaction]]);

		GetVehiclePos(PlayerFactionVehicle[playerid][AccountData[playerid][pFaction]], PlayerFactionVehStats[playerid][pFactVehPos][0], PlayerFactionVehStats[playerid][pFactVehPos][1], PlayerFactionVehStats[playerid][pFactVehPos][2]);
		GetVehicleZAngle(PlayerFactionVehicle[playerid][AccountData[playerid][pFaction]], PlayerFactionVehStats[playerid][pFactVehPos][3]);
		
		if(!IsFloatEx(PlayerFactionVehStats[playerid][pFactVehPos][3]))
			PlayerFactionVehStats[playerid][pFactVehPos][3] = 0;

		static string[512];
		mysql_format(g_SQL, string, sizeof(string), "UPDATE `demand_vehicles` SET `model` = %d, `vehX` = '%.3f', `vehY` = '%.3f', `vehZ` = '%.3f', `vehA` = '%.3f', `damage0` = %d, `damage1` = %d, `damage2` = %d, `damage3` = %d, \
		`health` = '%.2f', `maxhealth` = '%.2f', `bodyupgraded` = %d, `bodybroken` = %d, `fuel` = %d, `locked` = %d, `world` = %d WHERE `ownerid` = %d", PlayerFactionVehStats[playerid][pFactVehModel], PlayerFactionVehStats[playerid][pFactVehPos][0], PlayerFactionVehStats[playerid][pFactVehPos][1], PlayerFactionVehStats[playerid][pFactVehPos][2], PlayerFactionVehStats[playerid][pFactVehPos][3],
		PlayerFactionVehStats[playerid][pFactVehDamage][0], PlayerFactionVehStats[playerid][pFactVehDamage][1], PlayerFactionVehStats[playerid][pFactVehDamage][2], PlayerFactionVehStats[playerid][pFactVehDamage][3], PlayerFactionVehStats[playerid][pFactVehHealth], PlayerFactionVehStats[playerid][pFactVehMaxHealth], PlayerFactionVehStats[playerid][pFactVehBodyUpgraded], PlayerFactionVehStats[playerid][pFactVehBodyBroken], PlayerFactionVehStats[playerid][pFactVehFuel], PlayerFactionVehStats[playerid][pFactVehLocked], PlayerFactionVehStats[playerid][pFactVehWorld], AccountData[playerid][pID]);
		mysql_pquery(g_SQL, string);
	}

	return 1;
}

RemovePlayerVehicle(playerid)
{
	foreach(new i : PvtVehicles)
	{
		if(PlayerVehicle[i][pVehOwnerID] == AccountData[playerid][pID])
		{
			Vehicle_GetStatus(i);
			static cQuery[4885];
			
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `player_vehicles` SET ");
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_ModelID`=%d, ", cQuery, PlayerVehicle[i][pVehModelID]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Price`=%d, ", cQuery, PlayerVehicle[i][pVehPrice]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Parked`=%d, ", cQuery, PlayerVehicle[i][pVehParked]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Familied`=%d, ", cQuery, PlayerVehicle[i][pVehFamGarage]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Housed`=%d, ", cQuery, PlayerVehicle[i][pVehHouseGarage]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_RentTime`=%d, ", cQuery, PlayerVehicle[i][pVehRentTime]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Rental`=%d, ", cQuery, PlayerVehicle[i][pVehRental]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Plate`='%e', ", cQuery, PlayerVehicle[i][pVehPlate]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_PlateTime`=%d, ", cQuery, PlayerVehicle[i][pVehPlateTime]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Health`='%.2f', ", cQuery, PlayerVehicle[i][pVehHealth]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_BodyUpgraded`=%d, ", cQuery, PlayerVehicle[i][pVehBodyUpgraded]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_BodyBroken`=%d, ", cQuery, PlayerVehicle[i][pVehBodyBroken]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_MaxHealth`='%.2f', ", cQuery, PlayerVehicle[i][pVehMaxHealth]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Fuel`=%d, ", cQuery, PlayerVehicle[i][pVehFuel]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Locked`=%d, ", cQuery, PlayerVehicle[i][pVehLocked]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod0`=%d, ", cQuery, PlayerVehicle[i][pVehMod][0]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod1`=%d, ", cQuery, PlayerVehicle[i][pVehMod][1]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod2`=%d, ", cQuery, PlayerVehicle[i][pVehMod][2]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod3`=%d, ", cQuery, PlayerVehicle[i][pVehMod][3]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod4`=%d, ", cQuery, PlayerVehicle[i][pVehMod][4]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod5`=%d, ", cQuery, PlayerVehicle[i][pVehMod][5]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod6`=%d, ", cQuery, PlayerVehicle[i][pVehMod][6]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod7`=%d, ", cQuery, PlayerVehicle[i][pVehMod][7]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod8`=%d, ", cQuery, PlayerVehicle[i][pVehMod][8]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod9`=%d, ", cQuery, PlayerVehicle[i][pVehMod][9]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod10`=%d, ", cQuery, PlayerVehicle[i][pVehMod][10]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod11`=%d, ", cQuery, PlayerVehicle[i][pVehMod][11]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod12`=%d, ", cQuery, PlayerVehicle[i][pVehMod][12]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod13`=%d, ", cQuery, PlayerVehicle[i][pVehMod][13]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod14`=%d, ", cQuery, PlayerVehicle[i][pVehMod][14]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod15`=%d, ", cQuery, PlayerVehicle[i][pVehMod][15]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod16`=%d, ", cQuery, PlayerVehicle[i][pVehMod][16]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Damage0`=%d, ", cQuery, PlayerVehicle[i][pVehDamage][0]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Damage1`=%d, ", cQuery, PlayerVehicle[i][pVehDamage][1]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Damage2`=%d, ", cQuery, PlayerVehicle[i][pVehDamage][2]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Damage3`=%d, ", cQuery, PlayerVehicle[i][pVehDamage][3]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_PosX`='%.2f', ", cQuery, PlayerVehicle[i][pVehPos][0]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_PosY`='%.2f', ", cQuery, PlayerVehicle[i][pVehPos][1]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_PosZ`='%.2f', ", cQuery, PlayerVehicle[i][pVehPos][2]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_PosA`='%.2f', ", cQuery, PlayerVehicle[i][pVehPos][3]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Neon`=%d, ", cQuery, PlayerVehicle[i][pVehNeon]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Paintjob`=%d, ", cQuery, PlayerVehicle[i][pVehPaintjob]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Color1`=%d, ", cQuery, PlayerVehicle[i][pVehColor1]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Color2`=%d, ", cQuery, PlayerVehicle[i][pVehColor2]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_World`=%d, ", cQuery, PlayerVehicle[i][pVehWorld]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Interior`=%d, ", cQuery, PlayerVehicle[i][pVehInterior]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Impounded`=%d, ", cQuery, PlayerVehicle[i][pVehImpounded]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_ImpoundDuration`=%d, ", cQuery, PlayerVehicle[i][pVehImpoundDuration]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_ImpoundFee`=%d, ", cQuery, PlayerVehicle[i][pVehImpoundFee]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_ImpoundReason`='%e', ", cQuery, PlayerVehicle[i][pVehImpoundReason]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Insuranced`=%d, ", cQuery, PlayerVehicle[i][pVehInsuranced]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_TireLocked`=%d ", cQuery, PlayerVehicle[i][pVehTireLocked]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%sWHERE `id` = %d", cQuery, PlayerVehicle[i][pVehID]);
			mysql_pquery(g_SQL, cQuery);

			if(Iter_Contains(Vehicle, PlayerVehicle[i][pVehPhysic]))
			{
				if(IsVehicleUpsideDown(PlayerVehicle[i][pVehPhysic]) && !IsABike(PlayerVehicle[i][pVehPhysic]))
				{
					if(IsPlayerNearVehicle(playerid, PlayerVehicle[i][pVehPhysic], 55.55))
					{
						SendStaffMessage(X11_YELLOW, "AdmWarn: "RED"%s "YELLOW"logged out while vehicle "CYAN"%s "YELLOW"is upside down.", AccountData[playerid][pName], GetVehicleModelName(PlayerVehicle[i][pVehModelID]));
					}
				}
				SetVehicleNeonLights(PlayerVehicle[i][pVehPhysic], false, PlayerVehicle[i][pVehNeon], 0);
			}
			DestroyVehicle(PlayerVehicle[i][pVehPhysic]);

			for(new z; z < 3; z++)
			{
				VehicleHolster[i][vHolsterTaken][z] = false;
				VehicleHolster[i][vHolsterID][z] = -1;
				VehicleHolster[i][vHolsterWeaponID][z] = 0;
				VehicleHolster[i][vHolsterWeaponAmmo][z] = 0;
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

			PlayerVehicle[i][pVehHandbraked] = false;
			PlayerVehicle[i][pVehOwnerID] = -1;
			Iter_Remove(PvtVehicles, i);
		}
	}
	return 1;
}

SavePlayerVehicle(i)
{
	Vehicle_GetStatus(i);
	static cQuery[4885];
	
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `player_vehicles` SET ");
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_ModelID`=%d, ", cQuery, PlayerVehicle[i][pVehModelID]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Price`=%d, ", cQuery, PlayerVehicle[i][pVehPrice]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Parked`=%d, ", cQuery, PlayerVehicle[i][pVehParked]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Familied`=%d, ", cQuery, PlayerVehicle[i][pVehFamGarage]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Housed`=%d, ", cQuery, PlayerVehicle[i][pVehHouseGarage]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_RentTime`=%d, ", cQuery, PlayerVehicle[i][pVehRentTime]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Rental`=%d, ", cQuery, PlayerVehicle[i][pVehRental]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Plate`='%e', ", cQuery, PlayerVehicle[i][pVehPlate]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_PlateTime`=%d, ", cQuery, PlayerVehicle[i][pVehPlateTime]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Health`='%.2f', ", cQuery, PlayerVehicle[i][pVehHealth]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_BodyUpgraded`=%d, ", cQuery, PlayerVehicle[i][pVehBodyUpgraded]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_BodyBroken`=%d, ", cQuery, PlayerVehicle[i][pVehBodyBroken]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_MaxHealth`='%.2f', ", cQuery, PlayerVehicle[i][pVehMaxHealth]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Fuel`=%d, ", cQuery, PlayerVehicle[i][pVehFuel]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Locked`=%d, ", cQuery, PlayerVehicle[i][pVehLocked]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod0`=%d, ", cQuery, PlayerVehicle[i][pVehMod][0]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod1`=%d, ", cQuery, PlayerVehicle[i][pVehMod][1]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod2`=%d, ", cQuery, PlayerVehicle[i][pVehMod][2]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod3`=%d, ", cQuery, PlayerVehicle[i][pVehMod][3]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod4`=%d, ", cQuery, PlayerVehicle[i][pVehMod][4]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod5`=%d, ", cQuery, PlayerVehicle[i][pVehMod][5]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod6`=%d, ", cQuery, PlayerVehicle[i][pVehMod][6]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod7`=%d, ", cQuery, PlayerVehicle[i][pVehMod][7]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod8`=%d, ", cQuery, PlayerVehicle[i][pVehMod][8]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod9`=%d, ", cQuery, PlayerVehicle[i][pVehMod][9]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod10`=%d, ", cQuery, PlayerVehicle[i][pVehMod][10]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod11`=%d, ", cQuery, PlayerVehicle[i][pVehMod][11]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod12`=%d, ", cQuery, PlayerVehicle[i][pVehMod][12]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod13`=%d, ", cQuery, PlayerVehicle[i][pVehMod][13]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod14`=%d, ", cQuery, PlayerVehicle[i][pVehMod][14]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod15`=%d, ", cQuery, PlayerVehicle[i][pVehMod][15]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod16`=%d, ", cQuery, PlayerVehicle[i][pVehMod][16]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Damage0`=%d, ", cQuery, PlayerVehicle[i][pVehDamage][0]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Damage1`=%d, ", cQuery, PlayerVehicle[i][pVehDamage][1]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Damage2`=%d, ", cQuery, PlayerVehicle[i][pVehDamage][2]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Damage3`=%d, ", cQuery, PlayerVehicle[i][pVehDamage][3]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_PosX`='%.2f', ", cQuery, PlayerVehicle[i][pVehPos][0]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_PosY`='%.2f', ", cQuery, PlayerVehicle[i][pVehPos][1]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_PosZ`='%.2f', ", cQuery, PlayerVehicle[i][pVehPos][2]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_PosA`='%.2f', ", cQuery, PlayerVehicle[i][pVehPos][3]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Neon`=%d, ", cQuery, PlayerVehicle[i][pVehNeon]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Paintjob`=%d, ", cQuery, PlayerVehicle[i][pVehPaintjob]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Color1`=%d, ", cQuery, PlayerVehicle[i][pVehColor1]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Color2`=%d, ", cQuery, PlayerVehicle[i][pVehColor2]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_World`=%d, ", cQuery, PlayerVehicle[i][pVehWorld]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Interior`=%d, ", cQuery, PlayerVehicle[i][pVehInterior]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Impounded`=%d, ", cQuery, PlayerVehicle[i][pVehImpounded]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_ImpoundDuration`=%d, ", cQuery, PlayerVehicle[i][pVehImpoundDuration]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_ImpoundFee`=%d, ", cQuery, PlayerVehicle[i][pVehImpoundFee]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_ImpoundReason`='%e', ", cQuery, PlayerVehicle[i][pVehImpoundReason]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Insuranced`=%d, ", cQuery, PlayerVehicle[i][pVehInsuranced]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_TireLocked`=%d ", cQuery, PlayerVehicle[i][pVehTireLocked]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%sWHERE `id` = %d", cQuery, PlayerVehicle[i][pVehID]);
	mysql_pquery(g_SQL, cQuery);
	return 1;
}

Vehicle_Create(playerid, modelid, Float:x, Float:y, Float:z, Float:angle, color1, color2, worldid, interiorid)
{
    new i = Iter_Free(PvtVehicles);
	
	if(i <= -1)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuat kendaraan player!");

	PlayerVehicle[i][pVehOwnerID] = AccountData[playerid][pID];
	PlayerVehicle[i][pVehModelID] = modelid;
	PlayerVehicle[i][pVehPrice] = 1000;
	PlayerVehicle[i][pVehParked] = -1;
	PlayerVehicle[i][pVehFamGarage] = -1;
	PlayerVehicle[i][pVehHouseGarage] = -1;
	PlayerVehicle[i][pVehRentTime] = 0;
	PlayerVehicle[i][pVehRental] = -1;

	strcopy(PlayerVehicle[i][pVehPlate], "-");

	PlayerVehicle[i][pVehPlateTime] = 0;
	PlayerVehicle[i][pVehBodyUpgraded] = false;
	PlayerVehicle[i][pVehBodyBroken] = false;
	PlayerVehicle[i][pVehMaxHealth] = 1000.0;
	PlayerVehicle[i][pVehHealth] = 1000.0;
	PlayerVehicle[i][pVehFuel] = 100;

	for(new j = 0; j < 17; j++)
		PlayerVehicle[i][pVehMod][j] = 0;

	PlayerVehicle[i][pVehDamage][0] = 0;
	PlayerVehicle[i][pVehDamage][1] = 0;
	PlayerVehicle[i][pVehDamage][2] = 0;
	PlayerVehicle[i][pVehDamage][3] = 0;
	PlayerVehicle[i][pVehPos][0] = x;
	PlayerVehicle[i][pVehPos][1] = y;
	PlayerVehicle[i][pVehPos][2] = z;
	PlayerVehicle[i][pVehPos][3] = angle;
	PlayerVehicle[i][pVehNeon] = 0;
	PlayerVehicle[i][pVehPaintjob] = -1;
	PlayerVehicle[i][pVehColor1] = color1;
	PlayerVehicle[i][pVehColor2] = color2;
	PlayerVehicle[i][pVehWorld] = worldid;
	PlayerVehicle[i][pVehInterior] = interiorid;
	PlayerVehicle[i][pVehImpounded] = false;
	PlayerVehicle[i][pVehImpoundDuration] = 0;
	PlayerVehicle[i][pVehImpoundFee] = 0;
	PlayerVehicle[i][pVehImpoundReason][0] = EOS;
	PlayerVehicle[i][pVehInsuranced] = false;
	PlayerVehicle[i][pVehTireLocked] = false;
	PlayerVehicle[i][pVehLocked] = false;

	PlayerVehicle[i][pVehPhysic] = CreateVehicle(PlayerVehicle[i][pVehModelID], PlayerVehicle[i][pVehPos][0], PlayerVehicle[i][pVehPos][1], PlayerVehicle[i][pVehPos][2], PlayerVehicle[i][pVehPos][3], PlayerVehicle[i][pVehColor1], PlayerVehicle[i][pVehColor2], 60000, false);
	VehicleCore[PlayerVehicle[i][pVehPhysic]][vCoreFuel] = PlayerVehicle[i][pVehFuel];
	SetValidVehicleHealth(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehHealth]); 
	VehicleCore[PlayerVehicle[i][pVehPhysic]][vIsBodyUpgraded] = PlayerVehicle[i][pVehBodyUpgraded];
	VehicleCore[PlayerVehicle[i][pVehPhysic]][vIsBodyBroken] = PlayerVehicle[i][pVehBodyBroken];
	VehicleCore[PlayerVehicle[i][pVehPhysic]][vMaxHealth] = PlayerVehicle[i][pVehMaxHealth];
	VehicleCore[PlayerVehicle[i][pVehPhysic]][vCoreLocked] = PlayerVehicle[i][pVehLocked];
	SetVehicleNumberPlate(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehPlate]);
	SetVehicleVirtualWorldEx(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehWorld]);
	LinkVehicleToInteriorEx(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehInterior]);
	SwitchVehicleEngine(PlayerVehicle[i][pVehPhysic], true);
	SwitchVehicleDoors(PlayerVehicle[i][pVehPhysic], false);

	Iter_Add(PvtVehicles, i);

	static cQuery[1668];
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO `player_vehicles` (`PVeh_Owner`, `PVeh_ModelID`, `PVeh_Price`, `PVeh_Parked`, `PVeh_Familied`, `PVeh_Housed`, `PVeh_RentTime`, `PVeh_Rental`, `PVeh_Plate`, `PVeh_PlateTime`, `PVeh_Health`, `PVeh_BodyUpgraded`, \
	`PVeh_BodyBroken`, `PVeh_MaxHealth`, `PVeh_Fuel`, `PVeh_Locked`, `PVeh_Mod0`, `PVeh_Mod1`, `PVeh_Mod2`, `PVeh_Mod3`, `PVeh_Mod4`, `PVeh_Mod5`, `PVeh_Mod6`, `PVeh_Mod7`, `PVeh_Mod8`, `PVeh_Mod9`, `PVeh_Mod10`, `PVeh_Mod11`, `PVeh_Mod12`, `PVeh_Mod13`, `PVeh_Mod14`, `PVeh_Mod15`, `PVeh_Mod16`, \
	`PVeh_Damage0`, `PVeh_Damage1`, `PVeh_Damage2`, `PVeh_Damage3`, `PVeh_PosX`, `PVeh_PosY`, `PVeh_PosZ`, `PVeh_PosA`, `PVeh_Neon`, `PVeh_Paintjob`, `PVeh_Color1`, `PVeh_Color2`, `PVeh_World`, `PVeh_Interior`, `PVeh_Impounded`, `PVeh_ImpoundDuration`, `PVeh_ImpoundFee`, \
	`PVeh_ImpoundReason`, `PVeh_Insuranced`) VALUES (%d, %d, %d, %d, %d, %d, %d, %d, '%e', %d, '%f', %d, %d, '%f', %d, %d, %d, \
	%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, '%f', '%f', '%f', \
	'%f', %d, %d, %d, %d, %d, %d, %d, %d, %d, '%s', %d)", PlayerVehicle[i][pVehOwnerID], PlayerVehicle[i][pVehModelID], PlayerVehicle[i][pVehPrice], PlayerVehicle[i][pVehParked], PlayerVehicle[i][pVehFamGarage], PlayerVehicle[i][pVehHouseGarage], PlayerVehicle[i][pVehRentTime], PlayerVehicle[i][pVehRental], PlayerVehicle[i][pVehPlate],
	PlayerVehicle[i][pVehPlateTime], PlayerVehicle[i][pVehHealth], PlayerVehicle[i][pVehBodyUpgraded], PlayerVehicle[i][pVehBodyBroken], PlayerVehicle[i][pVehMaxHealth], PlayerVehicle[i][pVehFuel], 
	PlayerVehicle[i][pVehLocked], PlayerVehicle[i][pVehMod][0], PlayerVehicle[i][pVehMod][1], PlayerVehicle[i][pVehMod][2], PlayerVehicle[i][pVehMod][3], PlayerVehicle[i][pVehMod][4], PlayerVehicle[i][pVehMod][5], 
	PlayerVehicle[i][pVehMod][6], PlayerVehicle[i][pVehMod][7], PlayerVehicle[i][pVehMod][8], PlayerVehicle[i][pVehMod][9], PlayerVehicle[i][pVehMod][10], PlayerVehicle[i][pVehMod][11], PlayerVehicle[i][pVehMod][12], 
	PlayerVehicle[i][pVehMod][13], PlayerVehicle[i][pVehMod][14], PlayerVehicle[i][pVehMod][15], PlayerVehicle[i][pVehMod][16], PlayerVehicle[i][pVehDamage][0], PlayerVehicle[i][pVehDamage][1], 
	PlayerVehicle[i][pVehDamage][2], PlayerVehicle[i][pVehDamage][3], PlayerVehicle[i][pVehPos][0], PlayerVehicle[i][pVehPos][1], PlayerVehicle[i][pVehPos][2], PlayerVehicle[i][pVehPos][3], 
	PlayerVehicle[i][pVehNeon], PlayerVehicle[i][pVehPaintjob], PlayerVehicle[i][pVehColor1], PlayerVehicle[i][pVehColor2], PlayerVehicle[i][pVehWorld], PlayerVehicle[i][pVehInterior], PlayerVehicle[i][pVehImpounded], PlayerVehicle[i][pVehImpoundDuration], PlayerVehicle[i][pVehImpoundFee], PlayerVehicle[i][pVehImpoundReason], PlayerVehicle[i][pVehInsuranced]);
	mysql_pquery(g_SQL, cQuery, "OnVehCreated", "i", i);
	return 1;
}

VehicleBuy_Create(playerid, modelid, price, Float:x, Float:y, Float:z, Float:angle, color1, color2, worldid, interiorid)
{
    new i = Iter_Free(PvtVehicles);

	if(i <= -1)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuat kendaraan player!");

	PlayerVehicle[i][pVehOwnerID] = AccountData[playerid][pID];
	PlayerVehicle[i][pVehModelID] = modelid;
	PlayerVehicle[i][pVehPrice] = price;
	PlayerVehicle[i][pVehParked] = -1;
	PlayerVehicle[i][pVehFamGarage] = -1;
	PlayerVehicle[i][pVehHouseGarage] = -1;
	PlayerVehicle[i][pVehRentTime] = 0;
	PlayerVehicle[i][pVehRental] = -1;

	strcopy(PlayerVehicle[i][pVehPlate], "-");

	PlayerVehicle[i][pVehPlateTime] = 0;
	PlayerVehicle[i][pVehBodyUpgraded] = false;
	PlayerVehicle[i][pVehBodyBroken] = false;
	PlayerVehicle[i][pVehMaxHealth] = 1000.0;
	PlayerVehicle[i][pVehHealth] = 1000.0;

	for(new j = 0; j < 17; j++)
		PlayerVehicle[i][pVehMod][j] = 0;

	PlayerVehicle[i][pVehDamage][0] = 0;
	PlayerVehicle[i][pVehDamage][1] = 0;
	PlayerVehicle[i][pVehDamage][2] = 0;
	PlayerVehicle[i][pVehDamage][3] = 0;
	PlayerVehicle[i][pVehFuel] = 100;
	PlayerVehicle[i][pVehPos][0] = x;
	PlayerVehicle[i][pVehPos][1] = y;
	PlayerVehicle[i][pVehPos][2] = z;
	PlayerVehicle[i][pVehPos][3] = angle;
	PlayerVehicle[i][pVehNeon] = 0;
	PlayerVehicle[i][pVehPaintjob] = -1;
	PlayerVehicle[i][pVehColor1] = color1;
	PlayerVehicle[i][pVehColor2] = color2;
	PlayerVehicle[i][pVehWorld] = worldid;
	PlayerVehicle[i][pVehInterior] = interiorid;
	PlayerVehicle[i][pVehImpounded] = false;
	PlayerVehicle[i][pVehImpoundDuration] = 0;
	PlayerVehicle[i][pVehImpoundFee] = 0;
	PlayerVehicle[i][pVehImpoundReason][0] = EOS;
	PlayerVehicle[i][pVehInsuranced] = false;
	PlayerVehicle[i][pVehTireLocked] = false;
	PlayerVehicle[i][pVehLocked] = false;

	PlayerVehicle[i][pVehPhysic] = CreateVehicle(PlayerVehicle[i][pVehModelID], PlayerVehicle[i][pVehPos][0], PlayerVehicle[i][pVehPos][1], PlayerVehicle[i][pVehPos][2], PlayerVehicle[i][pVehPos][3], PlayerVehicle[i][pVehColor1], PlayerVehicle[i][pVehColor2], 60000, false);
	VehicleCore[PlayerVehicle[i][pVehPhysic]][vCoreFuel] = PlayerVehicle[i][pVehFuel];
	SetValidVehicleHealth(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehHealth]); 
	VehicleCore[PlayerVehicle[i][pVehPhysic]][vIsBodyUpgraded] = PlayerVehicle[i][pVehBodyUpgraded];
	VehicleCore[PlayerVehicle[i][pVehPhysic]][vIsBodyBroken] = PlayerVehicle[i][pVehBodyBroken];
	VehicleCore[PlayerVehicle[i][pVehPhysic]][vMaxHealth] = PlayerVehicle[i][pVehMaxHealth];
	VehicleCore[PlayerVehicle[i][pVehPhysic]][vCoreLocked] = PlayerVehicle[i][pVehLocked];
	SetVehicleNumberPlate(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehPlate]);
	SetVehicleVirtualWorldEx(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehWorld]);
	LinkVehicleToInteriorEx(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehInterior]);
	SwitchVehicleEngine(PlayerVehicle[i][pVehPhysic], true);
	SwitchVehicleDoors(PlayerVehicle[i][pVehPhysic], false);


	Iter_Add(PvtVehicles, i);

	static cQuery[1668];
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO `player_vehicles` (`PVeh_Owner`, `PVeh_ModelID`, `PVeh_Price`, `PVeh_Parked`, `PVeh_Familied`, `PVeh_Housed`, `PVeh_RentTime`, `PVeh_Rental`, `PVeh_Plate`, `PVeh_PlateTime`, `PVeh_Health`, `PVeh_BodyUpgraded`, \
	`PVeh_BodyBroken`, `PVeh_MaxHealth`, `PVeh_Fuel`, `PVeh_Locked`, `PVeh_Mod0`, `PVeh_Mod1`, `PVeh_Mod2`, `PVeh_Mod3`, `PVeh_Mod4`, `PVeh_Mod5`, `PVeh_Mod6`, `PVeh_Mod7`, `PVeh_Mod8`, `PVeh_Mod9`, `PVeh_Mod10`, `PVeh_Mod11`, `PVeh_Mod12`, `PVeh_Mod13`, `PVeh_Mod14`, `PVeh_Mod15`, `PVeh_Mod16`, \
	`PVeh_Damage0`, `PVeh_Damage1`, `PVeh_Damage2`, `PVeh_Damage3`, `PVeh_PosX`, `PVeh_PosY`, `PVeh_PosZ`, `PVeh_PosA`, `PVeh_Neon`, `PVeh_Paintjob`, `PVeh_Color1`, `PVeh_Color2`, `PVeh_World`, `PVeh_Interior`, `PVeh_Impounded`, `PVeh_ImpoundDuration`, `PVeh_ImpoundFee`, \
	`PVeh_ImpoundReason`, `PVeh_Insuranced`) VALUES (%d, %d, %d, %d, %d, %d, %d, %d, '%e', %d, '%f', %d, %d, '%f', %d, %d, %d, \
	%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, '%f', '%f', '%f', \
	'%f', %d, %d, %d, %d, %d, %d, %d, %d, %d, '%s', %d)", PlayerVehicle[i][pVehOwnerID], PlayerVehicle[i][pVehModelID], PlayerVehicle[i][pVehPrice], PlayerVehicle[i][pVehParked], PlayerVehicle[i][pVehFamGarage], PlayerVehicle[i][pVehHouseGarage], PlayerVehicle[i][pVehRentTime], PlayerVehicle[i][pVehRental], PlayerVehicle[i][pVehPlate],
	PlayerVehicle[i][pVehPlateTime], PlayerVehicle[i][pVehHealth], PlayerVehicle[i][pVehBodyUpgraded], PlayerVehicle[i][pVehBodyBroken], PlayerVehicle[i][pVehMaxHealth], PlayerVehicle[i][pVehFuel], 
	PlayerVehicle[i][pVehLocked], PlayerVehicle[i][pVehMod][0], PlayerVehicle[i][pVehMod][1], PlayerVehicle[i][pVehMod][2], PlayerVehicle[i][pVehMod][3], PlayerVehicle[i][pVehMod][4], PlayerVehicle[i][pVehMod][5], 
	PlayerVehicle[i][pVehMod][6], PlayerVehicle[i][pVehMod][7], PlayerVehicle[i][pVehMod][8], PlayerVehicle[i][pVehMod][9], PlayerVehicle[i][pVehMod][10], PlayerVehicle[i][pVehMod][11], PlayerVehicle[i][pVehMod][12], 
	PlayerVehicle[i][pVehMod][13], PlayerVehicle[i][pVehMod][14], PlayerVehicle[i][pVehMod][15], PlayerVehicle[i][pVehMod][16], PlayerVehicle[i][pVehDamage][0], PlayerVehicle[i][pVehDamage][1], 
	PlayerVehicle[i][pVehDamage][2], PlayerVehicle[i][pVehDamage][3], PlayerVehicle[i][pVehPos][0], PlayerVehicle[i][pVehPos][1], PlayerVehicle[i][pVehPos][2], PlayerVehicle[i][pVehPos][3], 
	PlayerVehicle[i][pVehNeon], PlayerVehicle[i][pVehPaintjob], PlayerVehicle[i][pVehColor1], PlayerVehicle[i][pVehColor2], PlayerVehicle[i][pVehWorld], PlayerVehicle[i][pVehInterior], PlayerVehicle[i][pVehImpounded], PlayerVehicle[i][pVehImpoundDuration], PlayerVehicle[i][pVehImpoundFee], PlayerVehicle[i][pVehImpoundReason], PlayerVehicle[i][pVehInsuranced]);
	mysql_pquery(g_SQL, cQuery, "OnVehBuyCreated", "ii", playerid, i);
	return 1;
}

VehicleRental_Create(playerid, modelid, rentaltime, rentalid, Float:x, Float:y, Float:z, Float:angle, color1, color2, worldid, interiorid)
{
    new i = Iter_Free(PvtVehicles);

	if(i <= -1)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuat kendaraan player!");

	PlayerVehicle[i][pVehOwnerID] = AccountData[playerid][pID];
	PlayerVehicle[i][pVehModelID] = modelid;
	PlayerVehicle[i][pVehParked] = -1;
	PlayerVehicle[i][pVehFamGarage] = -1;
	PlayerVehicle[i][pVehHouseGarage] = -1;
	PlayerVehicle[i][pVehRentTime] = gettime()+rentaltime;
	PlayerVehicle[i][pVehRental] = rentalid;
	strcopy(PlayerVehicle[i][pVehPlate], "RENTAL");
	PlayerVehicle[i][pVehPlateTime] = gettime()+rentaltime;
	PlayerVehicle[i][pVehBodyUpgraded] = false;
	PlayerVehicle[i][pVehBodyBroken] = false;
	PlayerVehicle[i][pVehMaxHealth] = 1000.0;
	PlayerVehicle[i][pVehHealth] = 1000.0;
	PlayerVehicle[i][pVehFuel] = 100;

	for(new j = 0; j < 17; j++)
		PlayerVehicle[i][pVehMod][j] = 0;

	PlayerVehicle[i][pVehDamage][0] = 0;
	PlayerVehicle[i][pVehDamage][1] = 0;
	PlayerVehicle[i][pVehDamage][2] = 0;
	PlayerVehicle[i][pVehDamage][3] = 0;
	PlayerVehicle[i][pVehPos][0] = x;
	PlayerVehicle[i][pVehPos][1] = y;
	PlayerVehicle[i][pVehPos][2] = z;
	PlayerVehicle[i][pVehPos][3] = angle;
	PlayerVehicle[i][pVehNeon] = 0;
	PlayerVehicle[i][pVehPaintjob] = -1;
	PlayerVehicle[i][pVehColor1] = color1;
	PlayerVehicle[i][pVehColor2] = color2;
	PlayerVehicle[i][pVehWorld] = worldid;
	PlayerVehicle[i][pVehInterior] = interiorid;
	PlayerVehicle[i][pVehImpounded] = false;
	PlayerVehicle[i][pVehImpoundDuration] = 0;
	PlayerVehicle[i][pVehImpoundFee] = 0;
	PlayerVehicle[i][pVehImpoundReason][0] = EOS;
	PlayerVehicle[i][pVehInsuranced] = false;
	PlayerVehicle[i][pVehTireLocked] = false;
	PlayerVehicle[i][pVehLocked] = false;

	PlayerVehicle[i][pVehPhysic] = CreateVehicle(PlayerVehicle[i][pVehModelID], PlayerVehicle[i][pVehPos][0], PlayerVehicle[i][pVehPos][1], PlayerVehicle[i][pVehPos][2], PlayerVehicle[i][pVehPos][3], PlayerVehicle[i][pVehColor1], PlayerVehicle[i][pVehColor2], 60000, false);
	VehicleCore[PlayerVehicle[i][pVehPhysic]][vCoreFuel] = PlayerVehicle[i][pVehFuel];
	SetValidVehicleHealth(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehHealth]); 
	VehicleCore[PlayerVehicle[i][pVehPhysic]][vIsBodyUpgraded] = PlayerVehicle[i][pVehBodyUpgraded];
	VehicleCore[PlayerVehicle[i][pVehPhysic]][vIsBodyBroken] = PlayerVehicle[i][pVehBodyBroken];
	VehicleCore[PlayerVehicle[i][pVehPhysic]][vMaxHealth] = PlayerVehicle[i][pVehMaxHealth];
	VehicleCore[PlayerVehicle[i][pVehPhysic]][vCoreLocked] = PlayerVehicle[i][pVehLocked];
	SetVehicleNumberPlate(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehPlate]);
	SetVehicleVirtualWorldEx(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehWorld]);
	LinkVehicleToInteriorEx(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehInterior]);
	SwitchVehicleEngine(PlayerVehicle[i][pVehPhysic], true);
	SwitchVehicleDoors(PlayerVehicle[i][pVehPhysic], false);
	
	Iter_Add(PvtVehicles, i);

	static cQuery[1668];
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO `player_vehicles` (`PVeh_Owner`, `PVeh_ModelID`, `PVeh_Price`, `PVeh_Parked`, `PVeh_Familied`, `PVeh_Housed`, `PVeh_RentTime`, `PVeh_Rental`, `PVeh_Plate`, `PVeh_PlateTime`, `PVeh_Health`, `PVeh_BodyUpgraded`, \
	`PVeh_BodyBroken`, `PVeh_MaxHealth`, `PVeh_Fuel`, `PVeh_Locked`, `PVeh_Mod0`, `PVeh_Mod1`, `PVeh_Mod2`, `PVeh_Mod3`, `PVeh_Mod4`, `PVeh_Mod5`, `PVeh_Mod6`, `PVeh_Mod7`, `PVeh_Mod8`, `PVeh_Mod9`, `PVeh_Mod10`, `PVeh_Mod11`, `PVeh_Mod12`, `PVeh_Mod13`, `PVeh_Mod14`, `PVeh_Mod15`, `PVeh_Mod16`, \
	`PVeh_Damage0`, `PVeh_Damage1`, `PVeh_Damage2`, `PVeh_Damage3`, `PVeh_PosX`, `PVeh_PosY`, `PVeh_PosZ`, `PVeh_PosA`, `PVeh_Neon`, `PVeh_Paintjob`, `PVeh_Color1`, `PVeh_Color2`, `PVeh_World`, `PVeh_Interior`, `PVeh_Impounded`, `PVeh_ImpoundDuration`, `PVeh_ImpoundFee`, \
	`PVeh_ImpoundReason`, `PVeh_Insuranced`) VALUES (%d, %d, %d, %d, %d, %d, %d, %d, '%e', %d, '%f', %d, %d, '%f', %d, %d, %d, \
	%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, '%f', '%f', '%f', \
	'%f', %d, %d, %d, %d, %d, %d, %d, %d, %d, '%s', %d)", PlayerVehicle[i][pVehOwnerID], PlayerVehicle[i][pVehModelID], PlayerVehicle[i][pVehPrice], PlayerVehicle[i][pVehParked], PlayerVehicle[i][pVehFamGarage], PlayerVehicle[i][pVehHouseGarage], PlayerVehicle[i][pVehRentTime], PlayerVehicle[i][pVehRental], PlayerVehicle[i][pVehPlate],
	PlayerVehicle[i][pVehPlateTime], PlayerVehicle[i][pVehHealth], PlayerVehicle[i][pVehBodyUpgraded], PlayerVehicle[i][pVehBodyBroken], PlayerVehicle[i][pVehMaxHealth], PlayerVehicle[i][pVehFuel], 
	PlayerVehicle[i][pVehLocked], PlayerVehicle[i][pVehMod][0], PlayerVehicle[i][pVehMod][1], PlayerVehicle[i][pVehMod][2], PlayerVehicle[i][pVehMod][3], PlayerVehicle[i][pVehMod][4], PlayerVehicle[i][pVehMod][5], 
	PlayerVehicle[i][pVehMod][6], PlayerVehicle[i][pVehMod][7], PlayerVehicle[i][pVehMod][8], PlayerVehicle[i][pVehMod][9], PlayerVehicle[i][pVehMod][10], PlayerVehicle[i][pVehMod][11], PlayerVehicle[i][pVehMod][12], 
	PlayerVehicle[i][pVehMod][13], PlayerVehicle[i][pVehMod][14], PlayerVehicle[i][pVehMod][15], PlayerVehicle[i][pVehMod][16], PlayerVehicle[i][pVehDamage][0], PlayerVehicle[i][pVehDamage][1], 
	PlayerVehicle[i][pVehDamage][2], PlayerVehicle[i][pVehDamage][3], PlayerVehicle[i][pVehPos][0], PlayerVehicle[i][pVehPos][1], PlayerVehicle[i][pVehPos][2], PlayerVehicle[i][pVehPos][3], 
	PlayerVehicle[i][pVehNeon], PlayerVehicle[i][pVehPaintjob], PlayerVehicle[i][pVehColor1], PlayerVehicle[i][pVehColor2], PlayerVehicle[i][pVehWorld], PlayerVehicle[i][pVehInterior], PlayerVehicle[i][pVehImpounded], PlayerVehicle[i][pVehImpoundDuration], PlayerVehicle[i][pVehImpoundFee], PlayerVehicle[i][pVehImpoundReason], PlayerVehicle[i][pVehInsuranced]);
	mysql_pquery(g_SQL, cQuery, "OnVehRentalCreated", "ii", playerid, i);
	return 1;
}

GetVehicleWeight(vmodel)
{
    new weight;
    for(new x; x < sizeof(VehicleSpec); x++)
    {
        if(VehicleSpec[x][Model] == vmodel)
        {
            weight = VehicleSpec[x][BaggageWeight];
            return weight;
        }
    }
    return weight;
}

IsAJobVehicle(vehicleid)
{
	foreach(new i : Player) if(AccountData[i][pSpawned])
	{
		if(Iter_Contains(Vehicle, JobVehicle[i]) && JobVehicle[i] == vehicleid)
		{
			return true;
		}
	}
	return false;
}

CountPlayerTrunked(vehicleid)
{
	new count;
	foreach(new i : Player) if(AccountData[i][pSpawned] && (pInSpecMode[i] == 2 || pInSpecMode[i] == 3) && SavingVehID[i] == vehicleid)
	{
		count++;
	}
	return count;
}