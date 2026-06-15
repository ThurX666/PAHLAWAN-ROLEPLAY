YCMD:hclaim(playerid, params[], help)
{
    new hid = House_Nearest(playerid);

    if(hid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan rumah manapun!");
    if(!isnull(HouseData[hid][hOwnerName])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Rumah ini sudah dimiliki orang lain!");
    if(Player_HouseCount(playerid) > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah memiliki rumah!");
    
    AccountData[playerid][pHouseSharedID] = -1;
    HouseData[hid][hOwnerID] = AccountData[playerid][pID];
    strcopy(HouseData[hid][hOwnerName], AccountData[playerid][pName]);

    House_Save(hid);
    House_Refresh(hid);
    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil klaim rumah ini menjadi milikmu!");
    return 1;
}

YCMD:addhouse(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new hid = Iter_Free(Houses), lxa[512], type;

    if(hid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah dynamic Rumah sudah mencapai batas maksimum!");
    if(sscanf(params, "d", type)) return SUM(playerid, "/addhouse [type 1 - 4]");

    if(type < 1 || type > 4)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Type tidak valid!");

    HouseData[hid][hOwnerID] = 0;
    HouseData[hid][hOwnerName][0] = EOS;
    GetPlayerPos(playerid, HouseData[hid][hPos][0], HouseData[hid][hPos][1], HouseData[hid][hPos][2]);
    GetPlayerFacingAngle(playerid, HouseData[hid][hPos][3]);

    switch(type)
    {
        case 1: //standard
        {
            HouseData[hid][hIntPos][0] = 130.8151;
            HouseData[hid][hIntPos][1] = -745.0514;
            HouseData[hid][hIntPos][2] = -34.6250;
            HouseData[hid][hIntPos][3] = 270.2174;

            HouseData[hid][hVaultPos][0] = 132.6884;
            HouseData[hid][hVaultPos][1] = -738.2083;
            HouseData[hid][hVaultPos][2] = -34.6328;
        }
        case 2: //kontemporer
        {
            HouseData[hid][hIntPos][0] = 1960.8262;
            HouseData[hid][hIntPos][1] = -2387.8486;
            HouseData[hid][hIntPos][2] = -8.9141;
            HouseData[hid][hIntPos][3] = 271.1472;

            HouseData[hid][hVaultPos][0] = 1961.4633;
            HouseData[hid][hVaultPos][1] = -2393.5640;
            HouseData[hid][hVaultPos][2] = -5.3809;
        }
        case 3: //modern
        {
            HouseData[hid][hIntPos][0] = 1467.0586;
            HouseData[hid][hIntPos][1] = -1080.2438;
            HouseData[hid][hIntPos][2] = 213.8583;
            HouseData[hid][hIntPos][3] = 269.5805;

            HouseData[hid][hVaultPos][0] = 1496.2782;
            HouseData[hid][hVaultPos][1] = -1068.1410;
            HouseData[hid][hVaultPos][2] = 217.1184;
        }
        case 4: //mansion
        {
            HouseData[hid][hIntPos][0] = 1467.0586;
            HouseData[hid][hIntPos][1] = -1080.2438;
            HouseData[hid][hIntPos][2] = 213.8583;
            HouseData[hid][hIntPos][3] = 269.5805;

            HouseData[hid][hVaultPos][0] = 1496.2782;
            HouseData[hid][hVaultPos][1] = -1068.1410;
            HouseData[hid][hVaultPos][2] = 217.1184;
        }
    }
    HouseData[hid][hGaragePos][0] = HouseData[hid][hGaragePos][1] = HouseData[hid][hGaragePos][2] = HouseData[hid][hGaragePos][3] = 0.0;

    HouseData[hid][hType] = type;
    HouseData[hid][hWorld] = GetPlayerVirtualWorld(playerid);
    HouseData[hid][hInterior] = GetPlayerInterior(playerid);

    HouseData[hid][hIntWorld] = hid;
    HouseData[hid][hIntInterior] = 0;
    HouseData[hid][hMusicURL][0] = EOS;

    Iter_Add(Houses, hid);

    mysql_format(g_SQL, lxa, sizeof(lxa), "INSERT INTO `houses` SET `ID` = %d, `OwnerID` = %d, `OwnerName` = '%e', `X` = '%f', `Y` = '%f', `Z` = '%f', `A` = '%f', `IX` = '%f', `IY` = '%f', `IZ` = '%f', `IA` = '%f', `BX` = '%f', `BY` = '%f', `BZ` = '%f', `GX` = '%f', `GY` = '%f', `GZ` = '%f', `GA` = '%f', `Type` = %d, `World` = %d, `Interior` = %d, `IntWorld` = %d, `IntInterior` = %d",
    hid, HouseData[hid][hOwnerID], HouseData[hid][hOwnerName], HouseData[hid][hPos][0], HouseData[hid][hPos][1], HouseData[hid][hPos][2], HouseData[hid][hPos][3], HouseData[hid][hIntPos][0], HouseData[hid][hIntPos][1], HouseData[hid][hIntPos][2], HouseData[hid][hIntPos][3], 
    HouseData[hid][hVaultPos][0], HouseData[hid][hVaultPos][1], HouseData[hid][hVaultPos][2], HouseData[hid][hGaragePos][0], HouseData[hid][hGaragePos][1], HouseData[hid][hGaragePos][2], HouseData[hid][hGaragePos][3], HouseData[hid][hType], HouseData[hid][hWorld], HouseData[hid][hInterior], HouseData[hid][hIntWorld], HouseData[hid][hIntInterior]);
    mysql_pquery(g_SQL, lxa, "OnHouseCreated", "ii", playerid, hid);
    return 1;
}

YCMD:edithouse(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new hid, type[24], string[128];
    if(sscanf(params, "ds[24]S()[128]", hid, type, string)) return SUM(playerid, "/edithouse [id] [type]~n~pos, interior, vault, garage, reset");
    if(!Iter_Contains(Houses, hid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Rumah tersebut tidak valid!");

    if(!strcmp(type, "pos", true))
    {
        GetPlayerPos(playerid, HouseData[hid][hPos][0], HouseData[hid][hPos][1], HouseData[hid][hPos][2]);
        GetPlayerFacingAngle(playerid, HouseData[hid][hPos][3]);
        HouseData[hid][hWorld] = GetPlayerVirtualWorld(playerid);
        HouseData[hid][hInterior] = GetPlayerInterior(playerid);
        House_Save(hid);
        House_Refresh(hid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s mengubah lokasi rumah ID: %d.", AccountData[playerid][pAdminname], hid);
    }
    else if(!strcmp(type, "interior", true))
    {
        GetPlayerPos(playerid, HouseData[hid][hIntPos][0], HouseData[hid][hIntPos][1], HouseData[hid][hIntPos][2]);
        GetPlayerFacingAngle(playerid, HouseData[hid][hIntPos][3]);
        HouseData[hid][hIntWorld] = GetPlayerVirtualWorld(playerid);
        HouseData[hid][hIntInterior] = GetPlayerInterior(playerid);
        House_Save(hid);
        House_Refresh(hid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s mengubah lokasi interior rumah ID: %d.", AccountData[playerid][pAdminname], hid);
    }
    else if(!strcmp(type, "vault", true))
    {
        GetPlayerPos(playerid, HouseData[hid][hVaultPos][0], HouseData[hid][hVaultPos][1], HouseData[hid][hVaultPos][2]);
        House_Save(hid);
        House_Refresh(hid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s mengubah posisi brankas rumah ID: %d.", AccountData[playerid][pAdminname], hid);
    }
    else if(!strcmp(type, "garage", true))
    {
        GetPlayerPos(playerid, HouseData[hid][hGaragePos][0], HouseData[hid][hGaragePos][1], HouseData[hid][hGaragePos][2]);
        GetPlayerFacingAngle(playerid, HouseData[hid][hGaragePos][3]);
        House_Save(hid);
        House_Refresh(hid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s mengubah posisi garasi rumah ID: %d.", AccountData[playerid][pAdminname], hid);
    }
    else if(!strcmp(type, "reset", true))
    {
        HouseData[hid][hOwnerName][0] = EOS;
        HouseData[hid][hOwnerID] = 0;

        House_Save(hid);
        House_Refresh(hid);

        new query[218];
        mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `house_holster` WHERE `House_DBID`=%d", hid);
		mysql_pquery(g_SQL, query);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s telah reset rumah ID: %d.", AccountData[playerid][pAdminname], hid);
    }
    return 1;
}

YCMD:removehouse(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new hid, strgbg[128];
    if(sscanf(params, "d", hid)) return SUM(playerid, "/removehouse [id]");
    if(!Iter_Contains(Houses, hid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Rumah tersebut tidak valid!");

    HouseData[hid][hOwnerName][0] = EOS;
    HouseData[hid][hOwnerID] = 0;
    HouseData[hid][hPos][0] = HouseData[hid][hPos][1] = HouseData[hid][hPos][2] = HouseData[hid][hPos][3] = 0.0;
    HouseData[hid][hGaragePos][0] = HouseData[hid][hGaragePos][1] = HouseData[hid][hGaragePos][2] = HouseData[hid][hGaragePos][3] = 0.0;
    HouseData[hid][hIntPos][0] = HouseData[hid][hIntPos][1] = HouseData[hid][hIntPos][2] = HouseData[hid][hIntPos][3] = 0.0;
    HouseData[hid][hVaultPos][0] = HouseData[hid][hVaultPos][1] = HouseData[hid][hVaultPos][2] = 0.0;
    HouseData[hid][hType] = 0;
    HouseData[hid][hWorld] = 0;
    HouseData[hid][hInterior] = 0;
    HouseData[hid][hIntWorld] = 0;
    HouseData[hid][hIntInterior] = 0;
    HouseData[hid][hMusicURL][0] = EOS;

    if(DestroyDynamic3DTextLabel(HouseData[hid][hLabel]))
        HouseData[hid][hLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    if(DestroyDynamic3DTextLabel(HouseData[hid][hVaultLabel]))
        HouseData[hid][hVaultLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    if(DestroyDynamic3DTextLabel(HouseData[hid][hExitLabel]))
        HouseData[hid][hExitLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    if(DestroyDynamicPickup(HouseData[hid][hGaragePickup]))
        HouseData[hid][hGaragePickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

    if(DestroyDynamic3DTextLabel(HouseData[hid][hGarageTextLabel]))
        HouseData[hid][hGarageTextLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    Iter_Remove(Houses, hid);

    mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `houses` WHERE `ID` = %d", hid);
    mysql_pquery(g_SQL, strgbg);

    mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `house_holster` WHERE `House_DBID`=%d", hid);
	mysql_pquery(g_SQL, strgbg);

    mysql_format(g_SQL, strgbg, sizeof(strgbg), "UPDATE `player_characters` SET `Char_HouseSharedID` = -1 WHERE `Char_HouseSharedID` = %d", hid);
    mysql_pquery(g_SQL, strgbg);

    foreach(new i : Player)
    {
        if(AccountData[i][pHouseSharedID] == hid)
        {
            AccountData[i][pHouseSharedID] = -1;
        }
    }

    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s menghapus Rumah dengan ID: %d.", AccountData[playerid][pAdminname], hid);
    return 1;
}

YCMD:gotohouse(playerid, params[], help)
{
    new hid;
	if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);
		
	if(sscanf(params, "d", hid))
		return SUM(playerid, "/gotohouse [id]");

	if(!Iter_Contains(Houses, hid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Rumah tersebut tidak valid!");

	SetPlayerPositionEx(playerid, HouseData[hid][hPos][0], HouseData[hid][hPos][1], HouseData[hid][hPos][2], 90);
    SetPlayerInteriorEx(playerid, HouseData[hid][hInterior]);
    SetPlayerVirtualWorldEx(playerid, HouseData[hid][hWorld]);

	AccountData[playerid][pInDoor] = -1;
	AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
	AccountData[playerid][pInRusun] = -1;
    AccountData[playerid][pInGudang] = -1;
    return 1;
}

forward BulldozerHouse(adminid);
public BulldozerHouse(adminid)
{
    new rows = cache_num_rows(), strsdbg[255];

    if(rows > 0)
    {
        for(new x; x < rows; x++)
        {
            new pstID, hsID;
            cache_get_value_name_int(x, "ID", hsID);
            cache_get_value_name_int(x, "OwnerID", pstID);
            
            mysql_format(g_SQL, strsdbg, sizeof(strsdbg), "DELETE FROM `houses` WHERE `ID` = %d", hsID);
            mysql_pquery(g_SQL, strsdbg);

            mysql_format(g_SQL, strsdbg, sizeof(strsdbg), "DELETE FROM `house_holster` WHERE `House_DBID`=%d", hsID);
	        mysql_pquery(g_SQL, strsdbg);

            mysql_format(g_SQL, strsdbg, sizeof(strsdbg), "UPDATE `player_characters` SET `Char_HouseSharedID` = -1 WHERE `Char_HouseSharedID` = %d", hsID);
            mysql_pquery(g_SQL, strsdbg);

            if(DestroyDynamic3DTextLabel(HouseData[hsID][hLabel]))
                HouseData[hsID][hLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

            if(DestroyDynamic3DTextLabel(HouseData[hsID][hVaultLabel]))
                HouseData[hsID][hVaultLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

            if(DestroyDynamic3DTextLabel(HouseData[hsID][hExitLabel]))
                HouseData[hsID][hExitLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

            if(DestroyDynamicPickup(HouseData[hsID][hGaragePickup]))
                HouseData[hsID][hGaragePickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

            if(DestroyDynamic3DTextLabel(HouseData[hsID][hGarageTextLabel]))
                HouseData[hsID][hGarageTextLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

            HouseData[hsID][hOwnerName][0] = EOS;
            HouseData[hsID][hOwnerID] = 0;
            HouseData[hsID][hPos][0] = HouseData[hsID][hPos][1] = HouseData[hsID][hPos][2] = HouseData[hsID][hPos][3] = 0.0;
            HouseData[hsID][hGaragePos][0] = HouseData[hsID][hGaragePos][1] = HouseData[hsID][hGaragePos][2] = HouseData[hsID][hGaragePos][3] = 0.0;
            HouseData[hsID][hIntPos][0] = HouseData[hsID][hIntPos][1] = HouseData[hsID][hIntPos][2] = HouseData[hsID][hIntPos][3] = 0.0;
            HouseData[hsID][hVaultPos][0] = HouseData[hsID][hVaultPos][1] = HouseData[hsID][hVaultPos][2] = 0.0;
            HouseData[hsID][hType] = 0;
            HouseData[hsID][hWorld] = 0;
            HouseData[hsID][hInterior] = 0;
            HouseData[hsID][hIntWorld] = 0;
            HouseData[hsID][hIntInterior] = 0;
            HouseData[hsID][hMusicURL][0] = EOS;

            foreach(new i : Player)
            {
                if(AccountData[i][pHouseSharedID] == hsID || AccountData[i][pID] == pstID)
                {
                    AccountData[i][pHouseSharedID] = -1;

                    for(new l; l < MAX_HOUSE_ITEMS; l++)
                    {
                        HouseBrankas[i][l][houseBrankasExists] = false;
                        HouseBrankas[i][l][houseBrankasID] = 0;
                        HouseBrankas[i][l][houseBrankasOwner] = 0;
                        HouseBrankas[i][l][houseBrankasTemp][0] = EOS;
                        HouseBrankas[i][l][houseBrankasModel] = 0;
                        HouseBrankas[i][l][houseBrankasQuant] = 0;
                    }

                    mysql_format(g_SQL, strsdbg, sizeof(strsdbg), "DELETE FROM `house_brankas` WHERE `Owner`=%d", AccountData[i][pID]);
	                mysql_pquery(g_SQL, strsdbg);
                }
            }

            mysql_format(g_SQL, strsdbg, sizeof(strsdbg), "DELETE FROM `house_brankas` WHERE `Owner`=%d", pstID);
	        mysql_pquery(g_SQL, strsdbg);

            Iter_Remove(Houses, hsID);
        }
        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s telah menggusur %d rumah yang tidak melapor bulanan.", AccountData[adminid][pAdminname], rows);
    }
    return 1;
}

YCMD:bulldozerhouse(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    mysql_pquery(g_SQL, "SELECT * FROM `houses` WHERE `Lapor` = 0", "BulldozerHouse", "i", playerid);
    return 1;
}