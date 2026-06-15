YCMD:addicon(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9)
		return PermissionError(playerid);

    new iconids = Iter_Free(Icons);
    if(iconids == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah dynamic map icons sudah maksimal!");

    new type;
	if(sscanf(params, "d", type)) 
    {
        SUM(playerid, "/addicon [icon type]");
        return 1;
    }

    if(type < 0 || type > 63)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak boleh kurang dari 0 atau lebih dari 63!");

    GetPlayerPos(playerid, IconData[iconids][iconPos][0], IconData[iconids][iconPos][1], IconData[iconids][iconPos][2]);
	IconData[iconids][iconVw] = GetPlayerVirtualWorld(playerid);
	IconData[iconids][iconInt] = GetPlayerInterior(playerid);
	IconData[iconids][iconType] = type;
    IconData[iconids][iconColor] = -1;
	
    MapIcon_Rebuild(iconids);
	Iter_Add(Icons, iconids);

    new query[1024];
    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `mapicons` SET `ID`=%d, `iconvw`=%d, `iconint`=%d, `iconpos0`=%f, `iconpos1`=%f, `iconpos2`=%f, `icontype`=%d",
	iconids, IconData[iconids][iconVw], IconData[iconids][iconInt], IconData[iconids][iconPos][0], IconData[iconids][iconPos][1], IconData[iconids][iconPos][2], IconData[iconids][iconType]);
	mysql_pquery(g_SQL, query, "OnIconCreated", "ii", playerid, iconids);
    return 1;
}

YCMD:editicon(playerid, params[], help)
{
    static
        iconids,
        type[24],
        string[128];

    if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);

    if(sscanf(params, "ds[24]S()[128]", iconids, type, string))
        return SUM(playerid, "/editicon [id] [type]~n~location, type");
	
    if(!Iter_Contains(Icons, iconids)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Map Icon tersebut tidak vaiconids!");

    if(!strcmp(type, "location", true))
    {
		GetPlayerPos(playerid, IconData[iconids][iconPos][0], IconData[iconids][iconPos][1], IconData[iconids][iconPos][2]);

        IconData[iconids][iconVw] = GetPlayerVirtualWorld(playerid);
		IconData[iconids][iconInt] = GetPlayerInterior(playerid);
        MapIcon_Save(iconids);
		MapIcon_Refresh(iconids);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s menetapkan lokasi map icon ID: %d.", AccountData[playerid][pAdminname], iconids);
    }
    else if(!strcmp(type, "type", true))
    {
        new newicon;

        if(sscanf(string, "d", newicon))
            return SUM(playerid, "/editicon [id] [type] [icon type]");

        if(newicon < 0 || newicon > 63)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak boleh kurang dari 0 atau lebih dari 63!");

        IconData[iconids][iconType] = newicon;
        MapIcon_Save(iconids);
		MapIcon_Refresh(iconids);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s menetapkan icon type untuk map icon ID: %d.", AccountData[playerid][pAdminname], iconids);
    }
    return 1;
}

YCMD:gotoicon(playerid, params[], help)
{
	new iconids;
	if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);
		
	if(sscanf(params, "d", iconids))
		return SUM(playerid, "/gotoicon [id]");

	if(!Iter_Contains(Icons, iconids)) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "ID map icon tersebut tidak valid!");

	SetPlayerPositionEx(playerid, IconData[iconids][iconPos][0], IconData[iconids][iconPos][1], IconData[iconids][iconPos][2], 0.0);
    SetPlayerInteriorEx(playerid, IconData[iconids][iconInt]);
    SetPlayerVirtualWorldEx(playerid, IconData[iconids][iconVw]);

    AccountData[playerid][pInDoor] = -1;
	AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
	AccountData[playerid][pInRusun] = -1;
    AccountData[playerid][pInGudang] = -1;
	return 1;
}

YCMD:removeicon(playerid, params[], help)
{
    static
        iconids;

    if(AccountData[playerid][pAdmin] < 9)
		return PermissionError(playerid);

    if(sscanf(params, "d", iconids))
        return SUM(playerid, "/removeicon [id]");

    if(!Iter_Contains(Icons, iconids))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "ID map icon tersebut tidak valid!");

    DestroyDynamicMapIcon(IconData[iconids][iconMapID]);

    IconData[iconids][iconVw] = 0;
    IconData[iconids][iconInt] = 0;

    IconData[iconids][iconPos][0] = 0;
    IconData[iconids][iconPos][1] = 0;
    IconData[iconids][iconPos][2] = 0;

    IconData[iconids][iconType] = 0;
    
    IconData[iconids][iconMapID] = -1;
    
    Iter_Remove(Icons, iconids);
    new query[128];
    mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `mapicons` WHERE `ID`=%d", iconids);
    mysql_pquery(g_SQL, query);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s telah menghapus map icon ID: %d.", AccountData[playerid][pAdminname], iconids);
    return 1;
}