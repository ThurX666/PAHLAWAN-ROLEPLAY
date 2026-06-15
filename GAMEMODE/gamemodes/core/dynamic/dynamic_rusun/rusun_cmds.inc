YCMD:addrusun(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new cost, rname[34], rsid = Iter_Free(Rusuns), sfstr[258];
    if(rsid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah dynamic Rusun sudah mencapai maksimum!");
    if(sscanf(params, "ds[34]", cost, rname)) return SUM(playerid, "/addrusun [harga 30 hari] [nama]");
    if(cost < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Harga tidak valid!");
    if(isnull(rname)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Nama Rusun tidak dapat kosong!");
    if(strlen(rname) > 34) return ShowTDN(playerid, NOTIFICATION_ERROR, "Maks nama rusun 34 karakter!");

    strcopy(RusunData[rsid][rusunName], rname);
    RusunData[rsid][rusunOwnerName][0] = EOS;
    RusunData[rsid][rusunOwnerID] = 0;
    RusunData[rsid][rusunCost] = cost;
    GetPlayerPos(playerid, RusunData[rsid][rusunPos][0], RusunData[rsid][rusunPos][1], RusunData[rsid][rusunPos][2]);
    GetPlayerFacingAngle(playerid, RusunData[rsid][rusunPos][3]);
    RusunData[rsid][rusunWorld] = GetPlayerVirtualWorld(playerid);
    RusunData[rsid][rusunInterior] = GetPlayerInterior(playerid);

    Iter_Add(Rusuns, rsid);

    mysql_format(g_SQL, sfstr, sizeof(sfstr), "INSERT INTO `rusun` SET `ID`=%d, `Name`='%e', `OwnerName`='%e', `OwnerID`=%d, `Cost_30Day`=%d, `PosX`='%f', `PosY`='%f', `PosZ`='%f', `PosA`='%f', `World`=%d, `Interior`=%d", 
    rsid, RusunData[rsid][rusunName], RusunData[rsid][rusunOwnerName], RusunData[rsid][rusunOwnerID], RusunData[rsid][rusunCost], RusunData[rsid][rusunPos][0], RusunData[rsid][rusunPos][1], RusunData[rsid][rusunPos][2], RusunData[rsid][rusunPos][3], RusunData[rsid][rusunWorld], RusunData[rsid][rusunInterior]);
    mysql_pquery(g_SQL, sfstr, "OnRusunCreated", "ii", playerid, rsid);
    return 1;
}

YCMD:editrusun(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new rsid, type[24], string[128];
    if(sscanf(params, "ds[24]S()[128]", rsid, type, string)) return SUM(playerid, "/editrusun [id] [type]~n~pos, cost, name, reset");
    if(!Iter_Contains(Rusuns, rsid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Rusun tersebut tidak valid!");

    if(!strcmp(type, "pos", true))
    {
        GetPlayerPos(playerid, RusunData[rsid][rusunPos][0], RusunData[rsid][rusunPos][1], RusunData[rsid][rusunPos][2]);
        GetPlayerFacingAngle(playerid, RusunData[rsid][rusunPos][3]);
        RusunData[rsid][rusunWorld] = GetPlayerVirtualWorld(playerid);
        RusunData[rsid][rusunInterior] = GetPlayerInterior(playerid);
        Rusun_Save(rsid);
        Rusun_Refresh(rsid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s mengubah lokasi rusun ID: %d.", AccountData[playerid][pAdminname], rsid);
    }
    else if(!strcmp(type, "cost", true))
    {
        new cost;
        if(sscanf(string, "d", cost)) return SUM(playerid, "/editrusun [id] [cost] [harga 7 hari]");
        if(cost < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Harga tidak valid!");

        RusunData[rsid][rusunCost] = cost;
        Rusun_Save(rsid);
        Rusun_Refresh(rsid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s mengubah harga rusun ID: %d menjadi $%s.", AccountData[playerid][pAdminname], rsid, FormatMoney(cost));
    }
    else if(!strcmp(type, "name", true))
    {
        new rname[34];
        if(sscanf(string, "s[34]", rname)) return SUM(playerid, "/editrusun [id] [name] [nama rusun]");
        if(isnull(rname)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Nama Rusun tidak dapat kosong!");
        if(strlen(rname) > 34) return ShowTDN(playerid, NOTIFICATION_ERROR, "Maks nama rusun 34 karakter!");

        strcopy(RusunData[rsid][rusunName], rname);
        Rusun_Save(rsid);
        Rusun_Refresh(rsid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s mengubah nama rusun ID: %d menjadi %s.", AccountData[playerid][pAdminname], rsid, RusunData[rsid][rusunName]);
    }
    else if(!strcmp(type, "reset", true))
    {
        RusunData[rsid][rusunOwnerName][0] = EOS;
        RusunData[rsid][rusunOwnerID] = 0;

        Rusun_Save(rsid);
        Rusun_Refresh(rsid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s telah reset rusun ID: %d.", AccountData[playerid][pAdminname], rsid);
    }
    return 1;
}

YCMD:removerusun(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new rsid, strgbg[128];
    if(sscanf(params, "d", rsid)) return SUM(playerid, "/removerusun [id]");
    if(!Iter_Contains(Rusuns, rsid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Rusun tersebut tidak valid!");

    RusunData[rsid][rusunName][0] = EOS;
    RusunData[rsid][rusunOwnerName][0] = EOS;
    RusunData[rsid][rusunOwnerID] = 0;
    RusunData[rsid][rusunCost] = 0;
    RusunData[rsid][rusunPos][0] = RusunData[rsid][rusunPos][1] = RusunData[rsid][rusunPos][2] = RusunData[rsid][rusunPos][3] = 0.0;
    RusunData[rsid][rusunWorld] = 0;
    RusunData[rsid][rusunInterior] = 0;

    if(DestroyDynamicPickup(RusunData[rsid][rusunPickup]))
        RusunData[rsid][rusunPickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

    if(DestroyDynamic3DTextLabel(RusunData[rsid][rusunLabel]))
        RusunData[rsid][rusunLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    if(DestroyDynamicPickup(RusunData[rsid][rusunChestPickup]))
        RusunData[rsid][rusunChestPickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

    if(DestroyDynamic3DTextLabel(RusunData[rsid][rusunChestLabel]))
        RusunData[rsid][rusunChestLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    if(DestroyDynamic3DTextLabel(RusunData[rsid][rusunOutLabel]))
        RusunData[rsid][rusunOutLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    Iter_Remove(Rusuns, rsid);

    mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `rusun` WHERE `ID` = %d", rsid);
    mysql_pquery(g_SQL, strgbg);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s menghapus Rusun dengan ID: %d.", AccountData[playerid][pAdminname], rsid);
    return 1;
}

YCMD:resetallrusun(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    foreach(new rsid : Rusuns)
    {
        Rusun_Reset(rsid);
    }

    RusunExpired = gettime() + DEFAULT_RUSUN_RESET;

    new fsrs[228];
    mysql_format(g_SQL, fsrs, sizeof(fsrs), "UPDATE `stuffs` SET `rusunreset`=%d WHERE `id`=0", RusunExpired);
    mysql_pquery(g_SQL, fsrs);

    SendClientMessageToAllEx(Y_LIGHTRED, "AdmCmd: %s telah mereset semua rusun.", AccountData[playerid][pAdminname]);
    return 1;
}