YCMD:addgudang(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new gdgid = Iter_Free(Gudangs), name[34], cost, sfstr[258];
    if (gdgid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah dynamic gudang telah mencapai batas maksimum!");
    if (sscanf(params, "ds[34]", cost, name)) return SUM(playerid, "/addgudang [rent cost] [gudang name]");
    if (cost < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Harga tidak valid!");
    if (isnull(name)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Nama gudang tidak dapat kosong!");
    if (strlen(name) > 34) return ShowTDN(playerid, NOTIFICATION_ERROR, "Panjang nama gudang max 34 karakter!");

    strcopy(GudangData[gdgid][gudangName], name);
    GudangData[gdgid][gudangCost] = cost;
    GetPlayerPos(playerid, GudangData[gdgid][gudangPos][0], GudangData[gdgid][gudangPos][1], GudangData[gdgid][gudangPos][2]);
    GudangData[gdgid][gudangWorld] = GetPlayerVirtualWorld(playerid);
    GudangData[gdgid][gudangInterior] = GetPlayerInterior(playerid);

    Iter_Add(Gudangs, gdgid);

    mysql_format(g_SQL, sfstr, sizeof(sfstr), "INSERT INTO `gudang` SET `ID`=%d, `Name`='%e', `Cost_30Day`=%d, `PosX`='%f', `PosY`='%f', `PosZ`='%f', `World`=%d, `Interior`=%d", 
    gdgid, GudangData[gdgid][gudangName], GudangData[gdgid][gudangCost], GudangData[gdgid][gudangPos][0], GudangData[gdgid][gudangPos][1], GudangData[gdgid][gudangPos][2], GudangData[gdgid][gudangWorld], GudangData[gdgid][gudangInterior]);
    mysql_pquery(g_SQL, sfstr, "OnGudangCreated", "ii", playerid, gdgid);
    return 1;
}

YCMD:editgudang(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new gdgid, type[24], string[128];
    if (sscanf(params, "ds[24]S()[128]", gdgid, type, string)) return SUM(playerid, "/editgudang [id] [type]~n~pos, cost, name");
    if (!Iter_Contains(Gudangs, gdgid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid gudang ID!");

    if (!strcmp(type, "pos", true))
    {
        GetPlayerPos(playerid, GudangData[gdgid][gudangPos][0], GudangData[gdgid][gudangPos][1], GudangData[gdgid][gudangPos][2]);
        GudangData[gdgid][gudangWorld] = GetPlayerVirtualWorld(playerid);
        GudangData[gdgid][gudangInterior] = GetPlayerInterior(playerid);
        Gudang_Save(gdgid);
        Gudang_Refresh(gdgid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s changed the location of gudang ID: %d.", AccountData[playerid][pAdminname], gdgid);
    }
    else if (!strcmp(type, "cost", true))
    {
        new cost;
        if (sscanf(string, "d", cost)) return SUM(playerid, "/editgudang [id] [cost] [7-day rent cost]");
        if (cost < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Harga tidak valid!");

        GudangData[gdgid][gudangCost] = cost;
        Gudang_Save(gdgid);
        Gudang_Refresh(gdgid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s changed the rent cost of gudang ID: %d to $%s.", AccountData[playerid][pAdminname], gdgid, FormatMoney(cost));
    }
    else if (!strcmp(type, "name", true))
    {
        new rname[34];
        if (sscanf(string, "s[34]", rname)) return SUM(playerid, "/editgudang [id] [name] [gudang name]");
        if (isnull(rname)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Nama gudang tidak dapat kosong!");
        if (strlen(rname) > 34) return ShowTDN(playerid, NOTIFICATION_ERROR, "Panjang nama gudang max 34 karakter!");

        strcopy(GudangData[gdgid][gudangName], rname);
        Gudang_Save(gdgid);
        Gudang_Refresh(gdgid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s changed the name of gudang ID: %d to %s.", AccountData[playerid][pAdminname], gdgid, GudangData[gdgid][gudangName]);
    }
    return 1;
}

YCMD:removegudang(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new gdgid, strgbg[128];
    if (sscanf(params, "d", gdgid)) return SUM(playerid, "/removegudang [id]");
    if (!Iter_Contains(Gudangs, gdgid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid gudang ID!");

    GudangData[gdgid][gudangName][0] = EOS;
    GudangData[gdgid][gudangCost] = 0;
    GudangData[gdgid][gudangPos][0] = GudangData[gdgid][gudangPos][1] = GudangData[gdgid][gudangPos][2] = 0.0;
    GudangData[gdgid][gudangWorld] = 0;
    GudangData[gdgid][gudangInterior] = 0;

    if (DestroyDynamicPickup(GudangData[gdgid][gudangPickup]))
        GudangData[gdgid][gudangPickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

    if (DestroyDynamic3DTextLabel(GudangData[gdgid][gudangLabel]))
        GudangData[gdgid][gudangLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    if (DestroyDynamicMapIcon(GudangData[gdgid][gudangMapIcon]))
        GudangData[gdgid][gudangMapIcon] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
    Iter_Remove(Gudangs, gdgid);

    mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `gudang` WHERE `ID` = %d", gdgid);
    mysql_pquery(g_SQL, strgbg);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s removed a gudang with ID: %d.", AccountData[playerid][pAdminname], gdgid);
    return 1;
}

YCMD:gotogudang(playerid, params[], help)
{
    new gdgid;
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    if (sscanf(params, "d", gdgid))
        return SUM(playerid, "/gotogudang [id]");

    if (!Iter_Contains(Gudangs, gdgid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid gudang ID!");

    SetPlayerPositionEx(playerid, GudangData[gdgid][gudangPos][0], GudangData[gdgid][gudangPos][1], GudangData[gdgid][gudangPos][2], 90);
    SetPlayerInteriorEx(playerid, GudangData[gdgid][gudangInterior]);
    SetPlayerVirtualWorldEx(playerid, GudangData[gdgid][gudangWorld]);

    AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInRusun] = -1;
    AccountData[playerid][pInGudang] = -1;
    return 1;
}