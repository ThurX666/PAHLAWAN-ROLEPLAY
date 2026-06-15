YCMD:addgarkot(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);

    new gpid = Iter_Free(PGarages), query[522], name[64];

    if (gpid == -1)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah dynamic public garages telah mencapai batas maksimm!");

    if(sscanf(params, "s[64]", name))
        return SUM(playerid, "/addgarkot [name]");

    strcopy(PublicGarage[gpid][pgName], name);
    GetPlayerPos(playerid, PublicGarage[gpid][pgRedPos][0], PublicGarage[gpid][pgRedPos][1], PublicGarage[gpid][pgRedPos][2]);
    PublicGarage[gpid][pgRedWorld] = GetPlayerVirtualWorld(playerid);
    PublicGarage[gpid][pgRedInterior] = GetPlayerInterior(playerid);

    PublicGarage[gpid][pgSpawnPos][0] = 0.0;
    PublicGarage[gpid][pgSpawnPos][1] = 0.0;
    PublicGarage[gpid][pgSpawnPos][2] = 0.0;
    PublicGarage[gpid][pgSpawnPos][3] = 0.0;
    PublicGarage[gpid][pgSpawnWorld] = 99;
    PublicGarage[gpid][pgSpawnInterior] = 99;

    PublicGarage_Rebuild(gpid);
    
    Iter_Add(PGarages, gpid);
    
    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `public_garages` SET `ID`=%d, `PG_RedX`='%f', `PG_RedY`='%f', `PG_RedZ`='%f', `PG_RedWorld`=%d, `PG_RedInterior`=%d", gpid, PublicGarage[gpid][pgRedPos][0], PublicGarage[gpid][pgRedPos][1], PublicGarage[gpid][pgRedPos][2], PublicGarage[gpid][pgRedWorld], PublicGarage[gpid][pgRedInterior]);
    mysql_pquery(g_SQL, query, "OnGarageCreated", "ii", playerid, gpid);
    return 1;
}

YCMD:editgarkot(playerid, params[], help)
{
    static
        gpid,
        type[24],
        string[128];

    if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);

    if(sscanf(params, "ds[24]S()[128]", gpid, type, string)) return SUM(playerid, "/editgarkot [id] [name] ~n~redpos, spawnpos");
    
    if(!Iter_Contains(PGarages, gpid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Garkot tersebut tidak valid!");

    if(!strcmp(type, "redpos", true))
    {
        GetPlayerPos(playerid, PublicGarage[gpid][pgRedPos][0], PublicGarage[gpid][pgRedPos][1], PublicGarage[gpid][pgRedPos][2]);

        PublicGarage[gpid][pgRedWorld] = GetPlayerVirtualWorld(playerid);
        PublicGarage[gpid][pgRedInterior] = GetPlayerInterior(playerid);
        PublicGarage_Save(gpid);
        PublicGarage_Refresh(gpid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set the position for Public Garage ID: %d.", AccountData[playerid][pAdminname], gpid);
    }
    else if(!strcmp(type, "spawnpos", true))
    {
        GetPlayerPos(playerid, PublicGarage[gpid][pgSpawnPos][0], PublicGarage[gpid][pgSpawnPos][1], PublicGarage[gpid][pgSpawnPos][2]);
        GetPlayerFacingAngle(playerid, PublicGarage[gpid][pgSpawnPos][3]);

        PublicGarage[gpid][pgSpawnWorld] = GetPlayerVirtualWorld(playerid);
        PublicGarage[gpid][pgSpawnInterior] = GetPlayerInterior(playerid);
        PublicGarage_Save(gpid);
        PublicGarage_Refresh(gpid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set the spawn position for Public Garage ID: %d.", AccountData[playerid][pAdminname], gpid);
    }
    else if(!strcmp(type, "name", true))
    {
        new name[64];

        if(sscanf(string, "s[64]", name))
            return SUM(playerid, "/editgarkot [id] [name] [new name]");

        strcopy(PublicGarage[gpid][pgName], name);
        PublicGarage_Save(gpid);
        PublicGarage_Refresh(gpid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set the name of Public Garage ID: %d to %s.", AccountData[playerid][pAdminname], gpid, name);
    }
    return 1;
}

YCMD:removegarkot(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new pgid, strgbg[512];

    if(sscanf(params, "d", pgid)) return SUM(playerid, "/removegarkot [id]");

    if(!Iter_Contains(PGarages, pgid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Garkot tersebut tidak valid!");

    if(DestroyDynamicObject(PublicGarage[pgid][pgRedObjid]))
    {
        PublicGarage[pgid][pgRedObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
    }

    if(DestroyDynamicArea(PublicGarage[pgid][pgRedArea]))
    {
        PublicGarage[pgid][pgRedArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
    }

    if(DestroyDynamicMapIcon(PublicGarage[pgid][pgMapIcon]))
    {
        PublicGarage[pgid][pgMapIcon] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
    }

    PublicGarage[pgid][pgName][0] = EOS;
    PublicGarage[pgid][pgRedPos][0] = 0.0;
    PublicGarage[pgid][pgRedPos][1] = 0.0;
    PublicGarage[pgid][pgRedPos][2] = 0.0;
    PublicGarage[pgid][pgRedWorld] = 0;
    PublicGarage[pgid][pgRedInterior] = 0;

    PublicGarage[pgid][pgSpawnPos][0] = 0.0;
    PublicGarage[pgid][pgSpawnPos][1] = 0.0;
    PublicGarage[pgid][pgSpawnPos][2] = 0.0;
    PublicGarage[pgid][pgSpawnPos][3] = 0.0;
    PublicGarage[pgid][pgSpawnWorld] = 0;
    PublicGarage[pgid][pgSpawnInterior] = 0;

    Iter_Remove(PGarages, pgid);

    mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `public_garages` WHERE `ID` = %d", pgid);
    mysql_pquery(g_SQL, strgbg);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s removed the Public Garage with ID: %d.", AccountData[playerid][pAdminname], pgid);
    return 1;
}

YCMD:gotogarkot(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new pgid;

    if(sscanf(params, "d", pgid)) return SUM(playerid, "/gotogarkot [id]");

    if(!Iter_Contains(PGarages, pgid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Garkot tersebut tidak valid!");

    SetPlayerPositionEx(playerid, PublicGarage[pgid][pgRedPos][0], PublicGarage[pgid][pgRedPos][1], PublicGarage[pgid][pgRedPos][2], 90);
    SetPlayerVirtualWorldEx(playerid, PublicGarage[pgid][pgRedWorld]);
    SetPlayerInteriorEx(playerid, PublicGarage[pgid][pgRedInterior]);

    AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInRusun] = -1;
    AccountData[playerid][pInGudang] = -1;
    return 1;
}