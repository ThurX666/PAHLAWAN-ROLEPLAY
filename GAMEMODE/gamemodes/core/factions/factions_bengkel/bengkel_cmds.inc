YCMD:modif(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] != FACTION_BENNYS && AccountData[playerid][pFaction] != FACTION_AUTOMAX && AccountData[playerid][pFaction] != FACTION_HANDOVER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Perintah ini hanya dapat diakses oleh faction sejenis bengkel!");

    if(!AccountData[playerid][pOnDuty]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus on duty terlebih dahulu!");

    if(AccountData[playerid][pFaction] == FACTION_BENNYS && !IsPlayerInDynamicArea(playerid, BennysLVArea)) 
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di bennys modif point!");

    if(AccountData[playerid][pFaction] == FACTION_AUTOMAX && !IsPlayerInDynamicArea(playerid, AutomaxServiceArea)) 
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di automax modif point!");

    if(AccountData[playerid][pFaction] == FACTION_HANDOVER && !IsPlayerInDynamicArea(playerid, HandoverServiceArea)) 
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di handover modif point!");

    if(!PlayerHasItem(playerid, "Obeng")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Obeng!");

    new carid = INVALID_VEHICLE_ID, foundnearby = 0;

    static string[528];
    if((carid = Vehicle_Nearest(playerid, 4.0)) != INVALID_VEHICLE_ID)
    {
        Vehicle_GetStatus(carid);

        AccountData[playerid][pTempVehIterID] = carid;
        format(string, sizeof(string), "Layanan\tKebutuhan\n\
        Perbaikan Mesin\t%d Komponen\n\
        "GRAY"Perbaikan Body\t"GRAY"%d Komponen\n\
        Perbaikan Ban\t%d Komponen\n\
        "GRAY"Ganti Warna\t"GRAY"75 Komponen\n\
        Paintjob\t100 Komponen\n\
        "GRAY"Upgrade Mesin\t"GRAY"%d Komponen\n\
        Upgrade Body\t250 Komponen\n\
        "GRAY"Modifikasi/Addons\t50 Komponen", 
        CountEngineCompoCost(carid),
        CountBodyCompoCost(carid),
        CountTiresCompoCost(carid),
        CountUpgradeEngineCompo(carid));

        Dialog_Show(playerid, "MechanicMenu", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Menu Mekanik", string, "Pilih", "Batal");
        foundnearby++;
    }
    if(!foundnearby)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan pribadi di sekitarmu!");
    return 1;
}

YCMD:buycomponent(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] != FACTION_BENNYS && AccountData[playerid][pFaction] != FACTION_AUTOMAX && AccountData[playerid][pFaction] != FACTION_HANDOVER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Perintah ini hanya dapat diakses oleh faction sejenis bengkel!");

    if(!IsPlayerInRangeOfPoint(playerid, 3.0, -168.2616,1032.5665,19.7344)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di component depot!");

    new value, pricing;
    if(sscanf(params, "d", value)) return SUM(playerid, "/buycomponent [ammount]");
    if(value < 1 || value > GM[g_ComponentStock]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid ammount!.");

    new Float:countingtotalweight;
    countingtotalweight = GetTotalWeightFloat(playerid) + float(value * GetItemWeight("Component"))/1000;
    if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

    pricing = value * GM[g_ComponentPrice];
    if(AccountData[playerid][pMoney] < RoundNegativeToPositive(pricing)) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

    TakePlayerMoneyEx(playerid, pricing);
    Inventory_Add(playerid, "Komponen", 2040, value);
    ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(pricing)), 1212, 4);
	ShowItemBox(playerid, "Komponen", sprintf("Received %dx", value), 2040, 5);

    GM[g_ComponentStock] -= value;

    static string[512];
    format(string, sizeof(string), "[Gudang Komponen]\n"WHITE"Harga: "GREEN"$%s/komponen\n"WHITE"Stock: "YELLOW"%d/100000\n"WHITE"Gunakan "YELLOW"'/buycomponent' "WHITE"untuk membeli komponen", FormatMoney(GM[g_ComponentPrice]), GM[g_ComponentStock]);
    UpdateDynamic3DTextLabelText(g_ComponentLabel, 0xc0c0c8A6, string);
    return 1;
}

YCMD:tow(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] != FACTION_BENNYS && AccountData[playerid][pFaction] != FACTION_AUTOMAX && AccountData[playerid][pFaction] != FACTION_HANDOVER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Perintah ini hanya dapat diakses oleh faction sejenis bengkel!");

    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus di kursi pengemudi!");

    if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 525) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di dalam Tow Truck!");

    new towtruckvehID, hookedvehID, Float:bootX, Float:bootY, Float:bootZ;

    towtruckvehID = GetPlayerVehicleID(playerid);
    GetVehicleBoot(towtruckvehID, bootX, bootY, bootZ);

    hookedvehID = GetNearestVehicleToPos(bootX, bootY, bootZ,GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),3.0,false);
    if(!IsValidVehicle(hookedvehID)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan yang dekat dengan tow truck anda!");
	if(GetVehicleDriver(hookedvehID) != INVALID_PLAYER_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut sedang disetir seseorang!");
    if(IsABike(hookedvehID) || IsABoat(hookedvehID) || IsAPlane(hookedvehID) || IsAHelicopter(hookedvehID) || IsATruck(hookedvehID) || IsAUnique(hookedvehID))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut tidak dapat diderek!");
        
    AttachTrailerToVehicle(hookedvehID, towtruckvehID);

    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menderek kendaraan tersebut.");
    return 1;
}

YCMD:untow(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] != FACTION_BENNYS && AccountData[playerid][pFaction] != FACTION_AUTOMAX && AccountData[playerid][pFaction] != FACTION_HANDOVER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Perintah ini hanya dapat diakses oleh faction sejenis bengkel!");

    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus di kursi pengemudi!");

    if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 525) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di dalam Tow Truck!");

    new hookedvehID = GetVehicleTrailer(GetPlayerVehicleID(playerid));
    if(!hookedvehID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan yang sedang diderek!");

    // new Float:vX, Float:vY, Float:vZ, Float:vA;
    // GetVehiclePos(GetPlayerVehicleID(playerid), vX, vY, vZ);
    // GetVehicleZAngle(GetPlayerVehicleID(playerid), vA);

    // SetVehiclePos(hookedvehID, vX - 0.800, vY - 1.200, vZ - 0.118);
    // SetVehicleZAngle(hookedvehID, vA);

    DetachTrailerFromVehicle(GetPlayerVehicleID(playerid));

    ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah melepaskan derek terhadap kendaraan tersebut.");
    return 1;
}