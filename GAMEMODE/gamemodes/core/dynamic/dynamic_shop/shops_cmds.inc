YCMD:addshop(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

    new sid = Iter_Free(Shops), query[280];
	if(sid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah dynamic Shops sudah maksimal!");

	new stype, bizid;
	if(sscanf(params, "dd", stype, bizid)) return SUM(playerid, "/addshop [type] [biz id]~n~1. Minimarket, 2. Clothes, 3. Electronic, 4. Ammunation");

    if(stype < 1 || stype > 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Mohon masukkan type untuk toko tersebut yang sesuai!");
    if(!Iter_Contains(Bizes, bizid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Bisnis tidak valid!");
    if(Shop_GetByBizID(bizid) != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Bisnis tersebut sudah memiliki shop!");
    if(stype != BizData[bizid][bizType]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Type shop harus sama dengan type bisnis tersebut!");

    GetPlayerPos(playerid, ShopData[sid][shopPos][0], ShopData[sid][shopPos][1], ShopData[sid][shopPos][2]);
    ShopData[sid][shopVw] = GetPlayerVirtualWorld(playerid);
    ShopData[sid][shopInt] = GetPlayerInterior(playerid);

    ShopData[sid][shopType] = stype;
    ShopData[sid][shopBizID] = bizid;

    Shop_Rebuild(sid);
	Iter_Add(Shops, sid);

    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `shops` SET `ID`=%d, `type`=%d, `bizID`=%d, `shopX`='%f', `shopY`='%f', `shopZ`='%f', `shopVw`=%d, `shopInt`=%d", sid, ShopData[sid][shopType], ShopData[sid][shopBizID], ShopData[sid][shopPos][0], ShopData[sid][shopPos][1], ShopData[sid][shopPos][2], ShopData[sid][shopVw], ShopData[sid][shopInt]);
	mysql_pquery(g_SQL, query, "OnShopsCreated", "ii", playerid, sid);

    return 1;
}

YCMD:editshop(playerid, params[], help)
{
    static
        sid,
        type[24],
        string[128];

    if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

    if(sscanf(params, "ds[24]S()[128]", sid, type, string)) return SUM(playerid, "/editshop [id] [type]~n~location, type, biz, remove");
	
    if(!Iter_Contains(Shops, sid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Shops tersebut tidak valid!");

    if(!strcmp(type, "location", true))
    {
		GetPlayerPos(playerid, ShopData[sid][shopPos][0], ShopData[sid][shopPos][1], ShopData[sid][shopPos][2]);

        ShopData[sid][shopVw] = GetPlayerVirtualWorld(playerid);
		ShopData[sid][shopInt] = GetPlayerInterior(playerid);
        Shop_Save(sid);
		Shop_Refresh(sid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s menetapkan lokasi Shops ID: %d.", AccountData[playerid][pAdminname], sid);
    }

    else if(!strcmp(type, "type", true))
    {
        new stype;

        if(sscanf(string, "d", stype))
            return SUM(playerid, "/editshop [id] [type]~n~1. Minimarket, 2. Clothes, 3. Electronic, 4. Ammunation");

        if(stype < 1 || stype > 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Type Shops tidak valid!");
        if(ShopData[sid][shopBizID] != -1)
        {
            if(!Iter_Contains(Bizes, ShopData[sid][shopBizID])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Bisnis yang terhubung tidak valid! Gunakan /editshop [id] biz - untuk melepas.");
            if(stype != BizData[ShopData[sid][shopBizID]][bizType]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Type shop harus sama dengan type bisnis. Gunakan /editshop [id] biz - terlebih dahulu.");
        }

        ShopData[sid][shopType] = stype;
        Shop_Save(sid);
		Shop_Refresh(sid);

    
        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s mengubah type Shops ID: %d menjadi %d.", AccountData[playerid][pAdminname], sid, stype);
    }

    else if(!strcmp(type, "biz", true))
    {
        new bizid;

        if(isnull(string))
            return SUM(playerid, "/editshop [id] biz [biz id/-]");

        if(!strcmp(string, "-", true))
        {
            ShopData[sid][shopBizID] = -1;
            Shop_Save(sid);
            Shop_Refresh(sid);

            SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s melepas Shops ID: %d dari bisnis manapun.", AccountData[playerid][pAdminname], sid);
            return 1;
        }

        if(sscanf(string, "d", bizid))
            return SUM(playerid, "/editshop [id] biz [biz id/-]");

        if(!Iter_Contains(Bizes, bizid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Bisnis tidak valid!");
        if(Shop_GetByBizID(bizid, sid) != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Bisnis tersebut sudah memiliki shop!");
        if(ShopData[sid][shopType] != BizData[bizid][bizType]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Type shop harus sama dengan type bisnis tersebut!");

        ShopData[sid][shopBizID] = bizid;
        Shop_Save(sid);
		Shop_Refresh(sid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s menghubungkan Shops ID: %d ke Business ID: %d.", AccountData[playerid][pAdminname], sid, bizid);
    }

    else if(!strcmp(type, "remove", true))
    {
        if(DestroyDynamic3DTextLabel(ShopData[sid][shopLabel]))
            ShopData[sid][shopLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        if(DestroyDynamicMapIcon(ShopData[sid][shopIcon]))
            ShopData[sid][shopIcon] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;

        if(DestroyDynamicPickup(ShopData[sid][shopPickup]))
            ShopData[sid][shopPickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;
		
        ShopData[sid][shopType] = 0;
        ShopData[sid][shopBizID] = -1;
		ShopData[sid][shopPos][0] = 0;
		ShopData[sid][shopPos][1] = 0;
		ShopData[sid][shopPos][2] = 0;
		ShopData[sid][shopVw] = 0;
		ShopData[sid][shopInt] = 0;
		
		Iter_Remove(Shops, sid);
		new query[128];
		mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `shops` WHERE `ID`=%d", sid);
		mysql_pquery(g_SQL, query);
        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s telah menghapus Shops ID: %d.", AccountData[playerid][pAdminname], sid);
	}
    return 1;
}

YCMD:gotoshop(playerid, params[], help)
{
	new id;
	if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);
		
	if(sscanf(params, "d", id))
		return SUM(playerid, "/gotoshop [id]");

	if(!Iter_Contains(Shops, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Shops tersebut tidak valid!");
	SetPlayerPositionEx(playerid, ShopData[id][shopPos][0], ShopData[id][shopPos][1], ShopData[id][shopPos][2], -90);
    SetPlayerInteriorEx(playerid, ShopData[id][shopInt]);
    SetPlayerVirtualWorldEx(playerid, ShopData[id][shopVw]);

    AccountData[playerid][pInDoor] = -1;
	AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
	AccountData[playerid][pInRusun] = -1;
    AccountData[playerid][pInGudang] = -1;
	return 1;
}

YCMD:shopicons(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

    if(!isnull(params))
    {
        if(!strcmp(params, "off", true) || !strcmp(params, "hide", true))
        {
            Shop_HideGlobalMapIcons(playerid);
            return ShowTDN(playerid, NOTIFICATION_SUCCESS, "Map icon semua shop berhasil disembunyikan.");
        }
        if(strcmp(params, "on", true) && strcmp(params, "show", true))
            return SUM(playerid, "/shopicons [on/off]");
    }
    else if(PlayerShopGlobalIcons[playerid])
    {
        Shop_HideGlobalMapIcons(playerid);
        return ShowTDN(playerid, NOTIFICATION_SUCCESS, "Map icon semua shop berhasil disembunyikan.");
    }

    new count = Shop_ShowGlobalMapIcons(playerid);
    if(!count) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada shop yang bisa ditampilkan.");

    ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("%d map icon shop berhasil ditampilkan.", count));
    return 1;
}

YCMD:showshopicons(playerid, params[], help) = shopicons;
