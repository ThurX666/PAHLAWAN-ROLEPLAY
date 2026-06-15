YCMD:addkanabis(playerid, params[], help)
{
    new Float:wpx, Float:wpy, Float:wpz, query[512], kanabisid = Iter_Free(Kanabises); // yang tadinya masih baru dibikin
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    if(kanabisid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah dynamic Kanabis sudah maksimal!");
    
    if(!IsPlayerInDynamicArea(playerid, KanabisField)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di ladang kanabis!");

    GetPlayerPos(playerid, wpx, wpy, wpz); //ketika diget maka akan diisi wpx, wpy, wpz nya menjadi koordinat kita saat ini.

    KanabisData[kanabisid][kanabisModel] = 19473;
    KanabisData[kanabisid][kanabisPos][0] = wpx;
    KanabisData[kanabisid][kanabisPos][1] = wpy;
    KanabisData[kanabisid][kanabisPos][2] = wpz;
    KanabisData[kanabisid][kanabisPos][3] = KanabisData[kanabisid][kanabisPos][4] = KanabisData[kanabisid][kanabisPos][5] = 0.0;
    KanabisData[kanabisid][kanabisInterior] = GetPlayerInterior(playerid);
    KanabisData[kanabisid][kanabisWorld] = GetPlayerVirtualWorld(playerid);

    KanabisData[kanabisid][kanabisObject] = CreateDynamicObject(KanabisData[kanabisid][kanabisModel], KanabisData[kanabisid][kanabisPos][0], KanabisData[kanabisid][kanabisPos][1], KanabisData[kanabisid][kanabisPos][2], KanabisData[kanabisid][kanabisPos][3], KanabisData[kanabisid][kanabisPos][4], KanabisData[kanabisid][kanabisPos][5], KanabisData[kanabisid][kanabisWorld], KanabisData[kanabisid][kanabisInterior], -1, 50.0, 50.0, KanabisField);
    KanabisData[kanabisid][kanabisArea] = CreateDynamicSphere(KanabisData[kanabisid][kanabisPos][0], KanabisData[kanabisid][kanabisPos][1], KanabisData[kanabisid][kanabisPos][2] + 1.7, 3.5, KanabisData[kanabisid][kanabisWorld], KanabisData[kanabisid][kanabisInterior], -1);
	
	Iter_Add(Kanabises, kanabisid); //ini memasukkan id baru ke dalam kelompok.

    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `kanabis` SET `id`='%d', `kanabisModel`='%d', `kanabisX`='%f', `kanabisY`='%f', `kanabisZ`='%f', `kanabisRx`='%f', `kanabisRy`='%f', `kanabisRz`='%f', `kanabisInterior`='%d', `kanabisWorld`='%d'", kanabisid, KanabisData[kanabisid][kanabisModel], KanabisData[kanabisid][kanabisPos][0], KanabisData[kanabisid][kanabisPos][1], KanabisData[kanabisid][kanabisPos][2], KanabisData[kanabisid][kanabisPos][3], KanabisData[kanabisid][kanabisPos][4], KanabisData[kanabisid][kanabisPos][5], GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
	mysql_pquery(g_SQL, query, "OnKanabisCreated", "ii", playerid, kanabisid);
    return 1;
}

YCMD:removekanabis(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9)
	    return PermissionError(playerid);

	new kanabisid, dwdstr[128];
	if(sscanf(params, "i", kanabisid)) return SUM(playerid, "/removekanabis [id]");
	if(!Iter_Contains(Kanabises, kanabisid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Kanabis tidak valid!");

    if(DestroyDynamicObject(KanabisData[kanabisid][kanabisObject]))
        KanabisData[kanabisid][kanabisObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

    if(DestroyDynamicArea(KanabisData[kanabisid][kanabisArea]))
        KanabisData[kanabisid][kanabisArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

    KanabisData[kanabisid][kanabisPos][0] = KanabisData[kanabisid][kanabisPos][1] = KanabisData[kanabisid][kanabisPos][2] = KanabisData[kanabisid][kanabisPos][3] = KanabisData[kanabisid][kanabisPos][4] = KanabisData[kanabisid][kanabisPos][5] = 0.0;
    KanabisData[kanabisid][kanabisInterior] = KanabisData[kanabisid][kanabisWorld] = 0;

    mysql_format(g_SQL, dwdstr, sizeof(dwdstr), "DELETE FROM `kanabis` WHERE `id` = '%d'", kanabisid);
    mysql_pquery(g_SQL, dwdstr);

    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s menghapus Kanabis dengan ID: %d.", AccountData[playerid][pAdminname], kanabisid);
	
	Iter_Remove(Kanabises, kanabisid);
	return 1;
}

YCMD:gotokanabis(playerid, params[], help)
{
	new kanabisid;
	if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);
		
	if(sscanf(params, "d", kanabisid))
		return SUM(playerid, "/gotokanabis [id]");

	if(!Iter_Contains(Kanabises, kanabisid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Kanabis tersebut tidak valid!");

	SetPlayerPositionEx(playerid, KanabisData[kanabisid][kanabisPos][0], KanabisData[kanabisid][kanabisPos][1], KanabisData[kanabisid][kanabisPos][2], KanabisData[kanabisid][kanabisPos][5]);
    SetPlayerInteriorEx(playerid, KanabisData[kanabisid][kanabisInterior]);
    SetPlayerVirtualWorldEx(playerid, KanabisData[kanabisid][kanabisWorld]);

	AccountData[playerid][pInDoor] = -1;
	AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
	AccountData[playerid][pInRusun] = -1;
    AccountData[playerid][pInGudang] = -1;
	return 1;
}

YCMD:editkanabis(playerid, params[], help)
{
	new kanabisid, type[24], wsredit[128]; 

    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

	if(sscanf(params, "ds[24]S()[128]", kanabisid, type, wsredit))
        return SUM(playerid, "/editkanabis [id] [name]~n~pos, interior, virtual");

	if(!Iter_Contains(Kanabises, kanabisid)) 
		return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Kanabis tidak valid!");

	if(!IsPlayerInRangeOfPoint(playerid, 30.0, KanabisData[kanabisid][kanabisPos][0], KanabisData[kanabisid][kanabisPos][1], KanabisData[kanabisid][kanabisPos][2])) 
	    return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan ID Kanabis tersebut!");

	if(!strcmp(type, "pos", true))
    {
		if(AccountData[playerid][EditingKanabisID] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang berada dalam mode editing!");

		AccountData[playerid][EditingKanabisID] = kanabisid;
		EditDynamicObject(playerid, KanabisData[kanabisid][kanabisObject]);

		SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s mengedit posisi Kanabis ID: %d.", AccountData[playerid][pAdminname], kanabisid);
	}

	else if(!strcmp(type, "interior", true))
    {
        GetPlayerPos(playerid, KanabisData[kanabisid][kanabisPos][0], KanabisData[kanabisid][kanabisPos][1], KanabisData[kanabisid][kanabisPos][2]);
		GetPlayerFacingAngle(playerid, KanabisData[kanabisid][kanabisPos][5]);

        KanabisData[kanabisid][kanabisWorld] = GetPlayerVirtualWorld(playerid);
		KanabisData[kanabisid][kanabisInterior] = GetPlayerInterior(playerid);
        Kanabis_Save(kanabisid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s menetapkan status interior untuk Kanabis ID: %d menjadi %d.", AccountData[playerid][pAdminname], kanabisid, GetPlayerVirtualWorld(playerid));
    }

	else if(!strcmp(type, "virtual", true))
    {
        new worldid;

        if(sscanf(wsredit, "d", worldid))
            return SUM(playerid, "/editkanabis [id] [virtual] [virtual world]");

        KanabisData[kanabisid][kanabisWorld] = worldid;

        Kanabis_Save(kanabisid);
        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s menetapkan virtual world untuk Kanabis ID: %d menjadi %d.", AccountData[playerid][pAdminname], kanabisid, worldid);
    }
	return 1;
}