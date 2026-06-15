YCMD:addbutton(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);
    
    new id = Iter_Free(Buttons), query[2048];
    if(id <= -1) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah dynamic button telah mencapai batas maksimum!");
    
    GetPlayerPos(playerid, ButtonData[id][bPosX], ButtonData[id][bPosY], ButtonData[id][bPosZ]);
    ButtonData[id][bDoorModel] = 3089;
    ButtonData[id][bPosX] = ButtonData[id][bPosX] + 2;
    ButtonData[id][bPosY] = ButtonData[id][bPosY] + 2;
    ButtonData[id][bPosRX] = 0;
    ButtonData[id][bPosRY] = 0;
    ButtonData[id][bPosRZ] = 0;
    GetPlayerPos(playerid, ButtonData[id][bDoorPosX], ButtonData[id][bDoorPosY], ButtonData[id][bDoorPosZ]);
    ButtonData[id][bDoorPosX] = ButtonData[id][bDoorPosX] + 2;
    ButtonData[id][bDoorPosY] = ButtonData[id][bDoorPosY] + 2;
    ButtonData[id][bDoorPosRX] = 0;
    ButtonData[id][bDoorPosRY] = 0;
    ButtonData[id][bDoorPosRZ] = 0;

    ButtonData[id][bDoorOpenX] = 0;
    ButtonData[id][bDoorOpenY] = 0;
    ButtonData[id][bDoorOpenZ] = 0;
    ButtonData[id][bDoorOpenRX] = 0;
    ButtonData[id][bDoorOpenRY] = 0;
    ButtonData[id][bDoorOpenRZ] = 0;

    ButtonData[id][bWorld] = GetPlayerVirtualWorld(playerid);
    ButtonData[id][bInterior] = GetPlayerInterior(playerid);

    ButtonData[id][bDoorStatus] = 0;
    ButtonData[id][bFaction] = 0;
    ButtonData[id][bFamily] = -1;
    ButtonData[id][bSpeed] = 2.0;

    // Creating
    ButtonData[id][bObject] = CreateDynamicObject(2886, ButtonData[id][bPosX], ButtonData[id][bPosY], ButtonData[id][bPosZ], ButtonData[id][bPosRX], ButtonData[id][bPosRY], ButtonData[id][bPosRZ], -1, -1, -1, 30.0, 30.0);
    ButtonData[id][bDoorObject] = CreateDynamicObject(ButtonData[id][bDoorModel], ButtonData[id][bDoorPosX], ButtonData[id][bDoorPosY], ButtonData[id][bDoorPosZ], ButtonData[id][bDoorPosRX], ButtonData[id][bDoorPosRY], ButtonData[id][bDoorPosRZ], -1, -1, -1, 100.0, 100.0);
    ButtonData[id][bDoorStatus] = 0;
    Iter_Add(Buttons, id);
    
    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `buttons` SET `ID`='%d', `doormodel`='%d', `bposx`='%f', `bposy`='%f', `bposz`='%f', `bposrx`='%f', `bposry`='%f', `bposrz`='%f', `doorposx`='%f', `doorposy`='%f', `doorposz`='%f', `doorposrx`='%f', `doorposry`='%f', `doorposrz`='%f', `dopenx`='%f', `dopeny`='%f', `dopenz`='%f', `dopenrx`='%f', `dopenry`='%f', `dopenrz`='%f', `world`=%d, `interior`=%d",
    id, ButtonData[id][bDoorModel], ButtonData[id][bPosX], ButtonData[id][bPosY], ButtonData[id][bPosZ], ButtonData[id][bPosRX], ButtonData[id][bPosRY], ButtonData[id][bPosRZ], ButtonData[id][bDoorPosX], ButtonData[id][bDoorPosY], ButtonData[id][bDoorPosZ], ButtonData[id][bDoorPosRX], ButtonData[id][bDoorPosRY], ButtonData[id][bDoorPosRZ],
    ButtonData[id][bDoorOpenX], ButtonData[id][bDoorOpenY], ButtonData[id][bDoorOpenZ], ButtonData[id][bDoorOpenRX], ButtonData[id][bDoorOpenRY], ButtonData[id][bDoorOpenRZ], ButtonData[id][bWorld], ButtonData[id][bInterior]);
    mysql_pquery(g_SQL, query, "OnButtonCreated", "ii", playerid, id);
    return 1;
}

YCMD:editbutton(playerid, params[], help)
{
    static
        id,
        type[24],
        string[128];

    if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);

    if(sscanf(params, "ds[24]S()[128]", id, type, string))
        return SUM(playerid, "/editbutton [id] [type]~n~doormodel | faction | family | buttonpos | close | open | speed | remove");

    if(!Iter_Contains(Buttons, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid button ID!");
    
    if(!strcmp(type, "doormodel", true))
    {
        new object;

        if(sscanf(string, "d", object))
            return SUM(playerid, "/editbutton [id] [doormodel] [object id]");

        ButtonData[id][bDoorModel] = object;
        if(DestroyDynamicObject(ButtonData[id][bDoorObject]))
            ButtonData[id][bDoorObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
        ButtonData[id][bDoorObject] = CreateDynamicObject(ButtonData[id][bDoorModel], ButtonData[id][bPosX], ButtonData[id][bPosY], ButtonData[id][bPosZ], ButtonData[id][bPosRX], ButtonData[id][bPosRY], ButtonData[id][bPosRZ], -1, -1, -1, 100.0, 100.0);
        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s changed the door model for button ID %d to %d.", AccountData[playerid][pAdminname], id, object);
        Button_Save(id);
    }
    else if(!strcmp(type, "faction", true))
    {
        new fid;

        if(sscanf(string, "d", fid))
            return SUM(playerid, "/editbutton [id] [faction] [faction id]");

        if(fid < 0 || fid > MAX_FACTIONS - 1)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid faction ID!");
        
        ButtonData[id][bFaction] = fid;
        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s changed the faction access for button ID %d to faction ID: %d.", AccountData[playerid][pAdminname], id, fid);
        Button_Save(id);
    }
    else if(!strcmp(type, "family", true))
    {
        new fmid;

        if(sscanf(string, "d", fmid))
            return SUM(playerid, "/editbutton [id] [faction] [faction id]");

        if(!Iter_Contains(Fams, fmid))
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Family ID tidak valid!");
        
        ButtonData[id][bFamily] = fmid;
        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s changed the family access for button ID %d to family ID: %d.", AccountData[playerid][pAdminname], id, fmid);
        Button_Save(id);
    }
    else if(!strcmp(type, "speed", true))
    {
        new Float:speed;

        if(sscanf(string, "f", speed))
            return SUM(playerid, "/editbutton [id] [Speed] [level]");
        
        ButtonData[id][bSpeed] = speed;
        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s changed the speed for button ID %d to %f.", AccountData[playerid][pAdminname], id, speed);
        Button_Save(id);
    }
    else if(!strcmp(type, "close", true))
    {    
        AccountData[playerid][EditingButton] = 1;
        AccountData[playerid][EditingButtonID] = id;
        GetDynamicObjectPos(ButtonData[id][bDoorObject], bDoorEditX[playerid], bDoorEditY[playerid], bDoorEditZ[playerid]);
        GetDynamicObjectRot(ButtonData[id][bDoorObject], bDoorEditRX[playerid], bDoorEditRY[playerid], bDoorEditRZ[playerid]);
        EditDynamicObject(playerid, ButtonData[id][bDoorObject]);
        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s edited the closed position of button ID: %d.", AccountData[playerid][pAdminname], id);
        Button_Save(id);
    }
    else if(!strcmp(type, "open", true))
    {
        AccountData[playerid][EditingButton] = 2;
        AccountData[playerid][EditingButtonID] = id;
        GetDynamicObjectPos(ButtonData[id][bDoorObject], bDoorEditX[playerid], bDoorEditY[playerid], bDoorEditZ[playerid]);
        GetDynamicObjectRot(ButtonData[id][bDoorObject], bDoorEditRX[playerid], bDoorEditRY[playerid], bDoorEditRZ[playerid]);
        EditDynamicObject(playerid, ButtonData[id][bDoorObject]);
        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s edited the open position of button ID: %d.", AccountData[playerid][pAdminname], id);
    }
    else if(!strcmp(type, "buttonpos", true))
    {    
        AccountData[playerid][EditingButton] = 3;
        AccountData[playerid][EditingButtonID] = id;
        GetDynamicObjectPos(ButtonData[id][bObject], bDoorEditX[playerid], bDoorEditY[playerid], bDoorEditZ[playerid]);
        GetDynamicObjectRot(ButtonData[id][bObject], bDoorEditRX[playerid], bDoorEditRY[playerid], bDoorEditRZ[playerid]);
        EditDynamicObject(playerid, ButtonData[id][bObject]);
        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s edited the button position of button ID: %d.", AccountData[playerid][pAdminname], id);
        Button_Save(id);
    }
    else if(!strcmp(type, "remove", true))
    {
        ButtonData[id][bDoorModel] = 0;
        ButtonData[id][bPosX] = 0;
        ButtonData[id][bPosY] = 0;
        ButtonData[id][bPosZ] = 0;
        ButtonData[id][bPosRX] = 0;
        ButtonData[id][bPosRY] = 0;
        ButtonData[id][bPosRZ] = 0;
        ButtonData[id][bDoorPosX] = 0;
        ButtonData[id][bDoorPosY] = 0;
        ButtonData[id][bDoorPosZ] = 0;
        ButtonData[id][bDoorPosRX] = 0;
        ButtonData[id][bDoorPosRY] = 0;
        ButtonData[id][bDoorPosRZ] = 0;

        ButtonData[id][bDoorOpenX] = 0;
        ButtonData[id][bDoorOpenY] = 0;
        ButtonData[id][bDoorOpenZ] = 0;
        ButtonData[id][bDoorOpenRX] = 0;
        ButtonData[id][bDoorOpenRY] = 0;
        ButtonData[id][bDoorOpenRZ] = 0;
        ButtonData[id][bWorld] = 0;
        ButtonData[id][bInterior] = 0;
        ButtonData[id][bDoorStatus] = 0;
        ButtonData[id][bFaction] = 0;
        ButtonData[id][bFamily] = -1;
        ButtonData[id][bSpeed] = 0;
        
        if(DestroyDynamicObject(ButtonData[id][bDoorObject]))
            ButtonData[id][bDoorObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
        if(DestroyDynamicObject(ButtonData[id][bObject]))
            ButtonData[id][bObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
        
        Iter_Remove(Buttons, id);
        new query[2048];
        mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `buttons` WHERE `ID`=%d", id);
        mysql_pquery(g_SQL, query);
        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s deleted button ID: %d.", AccountData[playerid][pAdminname], id);
    }
    return 1;
}

YCMD:gotobutton(playerid, params[], help)
{
    new id;
    if(AccountData[playerid][pAdmin] < 9)
        return PermissionError(playerid);
        
    if(sscanf(params, "i", id)) return SUM(playerid, "/gotobutton [button id]");
    if(!Iter_Contains(Buttons, id)) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Button ID!");

    SetPlayerPositionEx(playerid, ButtonData[id][bPosX], ButtonData[id][bPosY], ButtonData[id][bPosZ], 0.0);
    SetPlayerInteriorEx(playerid, ButtonData[id][bInterior]);
    SetPlayerVirtualWorldEx(playerid, ButtonData[id][bWorld]);
    AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInRusun] = -1;
    AccountData[playerid][pInGudang] = -1;
    return 1;
}