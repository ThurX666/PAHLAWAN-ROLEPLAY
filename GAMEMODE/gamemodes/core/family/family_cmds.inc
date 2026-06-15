YCMD:addfamily(playerid, params[], help)
{
    new bname[32], leadid, fmid = Iter_Free(Fams), gjhs[158];
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    if(fmid == -1) return SEM(playerid, "Jumlah badside sudah mencapai maksimum!");
    if(sscanf(params, "is[32]", leadid, bname)) return SUM(playerid, "/addfamily [playerid] [nama]");
    if(!IsPlayerConnected(leadid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if(strlen(bname) > 32) return SEM(playerid, "Panjang nama badside maksimal 32 karakter!");
    
    FamilyData[fmid][famLeaderID] = AccountData[leadid][pID];
    strcopy(FamilyData[fmid][famLeaderName], AccountData[leadid][pName]);
    strcopy(FamilyData[fmid][famName], bname);
    FamilyData[fmid][famMoney] = 0;
    FamilyData[fmid][famDirtyMoney] = 0;
    AccountData[leadid][pFamily] = fmid;
    AccountData[leadid][pFamilyRank] = 3;

    Iter_Add(Fams, fmid);

    mysql_format(g_SQL, gjhs, sizeof(gjhs), "INSERT INTO `families` SET `ID`=%d, `LeaderID`=%d, `LeaderName`='%e', `Name`='%e', `Money`=%d", fmid, FamilyData[fmid][famLeaderID], FamilyData[fmid][famLeaderName], FamilyData[fmid][famName], FamilyData[fmid][famMoney]);
    mysql_pquery(g_SQL, gjhs, "OnBadsideAdded", "ii", playerid, fmid);
    return 1;
}

YCMD:editfamily(playerid, params[], help)
{
    new fmid, type[24], string[128];
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    if(sscanf(params, "ds[24]S()[128]", fmid, type, string)) return SUM(playerid, "/editfamily [id] [name]~n~name, leader, money, dirtymoney, vault, desk, remove");
    if(!Iter_Contains(Fams, fmid)) return SEM(playerid, "ID Family tersebut tidak valid!");

    if(!strcmp(type, "name", true))
    {
        new newname[32];

        if(sscanf(string, "s[32]", newname)) return SUM(playerid, "/editfamily [id] [name] [nama baru]");
        strcopy(FamilyData[fmid][famName], newname);

        static strrs[144];
        format(strrs, sizeof(strrs), "[ "WHITE"(Garasi Badside): "YELLOW"%s "GREEN"]", FamilyData[fmid][famName]);
        UpdateDynamic3DTextLabelText(FamilyData[fmid][famGarageLabel], Y_GREEN, strrs);

        Badside_Save(fmid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s mengubah nama Family ID: %d menjadi %s.", AccountData[playerid][pAdminname], fmid, newname);
    }
    else if(!strcmp(type, "leader", true))
    {
        new newid, jeje[158];

        if(sscanf(string, "d", newid)) return SUM(playerid, "/editfamily [id] [leader] [playerid]");
        if(!IsPlayerConnected(newid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
        
        foreach(new i : Player)
        {
            if(FamilyData[fmid][famLeaderID] == AccountData[i][pID])
            {
                AccountData[i][pFamily] = -1;
                AccountData[i][pFamilyRank] = 0;
            }
        }
        mysql_format(g_SQL, jeje, sizeof(jeje), "UPDATE `player_characters` SET `Char_Family` = -1, `Char_FamilyRank` = 0 WHERE `Char_Family` = %d AND `Char_FamilyRank` = 6", FamilyData[fmid][famLeaderID], fmid);
        mysql_pquery(g_SQL, jeje);
        
        FamilyData[fmid][famLeaderID] = AccountData[newid][pID];
        strcopy(FamilyData[fmid][famLeaderName], AccountData[newid][pName]);

        AccountData[newid][pFamily] = fmid;
        AccountData[newid][pFamilyRank] = 6;

        Badside_Save(fmid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s mengubah ketua Family ID: %d menjadi %s(%d).", AccountData[playerid][pAdminname], fmid, AccountData[newid][pName], newid);
    }
    else if(!strcmp(type, "money", true))
    {
        new ammount;
        if(sscanf(string, "d", ammount)) return SUM(playerid, "/editfamily [id] [money] [jumlah]");
        if(ammount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid!");

        FamilyData[fmid][famMoney] = ammount;
        Badside_Save(fmid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s mengubah uang Family ID: %d menjadi $%s.", AccountData[playerid][pAdminname], fmid, FormatMoney(FamilyData[fmid][famMoney]));
    }
    else if(!strcmp(type, "dirtymoney", true))
    {
        new ammount;
        if(sscanf(string, "d", ammount)) return SUM(playerid, "/editfamily [id] [dirtymoney] [jumlah]");
        if(ammount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid!");

        FamilyData[fmid][famDirtyMoney] = ammount;
        Badside_Save(fmid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s mengubah dirty money Family ID: %d menjadi $%s.", AccountData[playerid][pAdminname], fmid, FormatMoney(FamilyData[fmid][famDirtyMoney]));
    }
    else if(!strcmp(type, "vault", true))
    {
        if(DestroyDynamic3DTextLabel(FamilyData[fmid][famVaultLabel]))
            FamilyData[fmid][famVaultLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        FamilyData[fmid][famVaultWorld] = GetPlayerVirtualWorld(playerid);
        FamilyData[fmid][famVaultInt] = GetPlayerInterior(playerid);

        GetPlayerPos(playerid, FamilyData[fmid][famVaultPos][0], FamilyData[fmid][famVaultPos][1], FamilyData[fmid][famVaultPos][2]);
        FamilyData[fmid][famVaultLabel] = CreateDynamic3DTextLabel("[Y] "WHITE"untuk akses penyimpanan", Y_YELLOW, FamilyData[fmid][famVaultPos][0], FamilyData[fmid][famVaultPos][1], FamilyData[fmid][famVaultPos][2] + 0.35, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, FamilyData[fmid][famVaultWorld], FamilyData[fmid][famVaultInt], -1, 10.00, -1, 0);

        Badside_Save(fmid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s mengubah posisi brankas Family ID: %d.", AccountData[playerid][pAdminname], fmid);
    }
    else if(!strcmp(type, "desk", true))
    {
        if(DestroyDynamic3DTextLabel(FamilyData[fmid][famDeskLabel]))
            FamilyData[fmid][famDeskLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        FamilyData[fmid][famDeskWorld] = GetPlayerVirtualWorld(playerid);
        FamilyData[fmid][famDeskInt] = GetPlayerInterior(playerid);

        GetPlayerPos(playerid, FamilyData[fmid][famDeskPos][0], FamilyData[fmid][famDeskPos][1], FamilyData[fmid][famDeskPos][2]);
        FamilyData[fmid][famDeskLabel] = CreateDynamic3DTextLabel("[Y] "WHITE"untuk akses bos desk", Y_YELLOW, FamilyData[fmid][famDeskPos][0], FamilyData[fmid][famDeskPos][1], FamilyData[fmid][famDeskPos][2] + 0.35, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, FamilyData[fmid][famDeskWorld], FamilyData[fmid][famDeskInt], -1, 10.00, -1, 0);

        Badside_Save(fmid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s mengubah posisi bos desk Family ID: %d.", AccountData[playerid][pAdminname], fmid);
    }
    else if(!strcmp(type, "garage", true))
    {
        if(DestroyDynamicObject(FamilyData[fmid][famGarageObjid]))
            FamilyData[fmid][famGarageObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
        
        if(DestroyDynamicPickup(FamilyData[fmid][famGaragePickup]))
            FamilyData[fmid][famGaragePickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;
        
        if(DestroyDynamic3DTextLabel(FamilyData[fmid][famGarageLabel]))
            FamilyData[fmid][famGarageLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        FamilyData[fmid][famGarageWorld] = GetPlayerVirtualWorld(playerid);
        FamilyData[fmid][famGarageInt] = GetPlayerInterior(playerid);

        GetPlayerPos(playerid, FamilyData[fmid][famGaragePos][0], FamilyData[fmid][famGaragePos][1], FamilyData[fmid][famGaragePos][2]);
        FamilyData[fmid][famGarageObjid] = CreateDynamicObject(1316, FamilyData[fmid][famGaragePos][0], FamilyData[fmid][famGaragePos][1], FamilyData[fmid][famGaragePos][2] - 0.9, 0.0, 0.0, 0.0, FamilyData[fmid][famGarageWorld], FamilyData[fmid][famGarageInt], -1, 100.00, 100.00, -1);
        SetDynamicObjectMaterial(FamilyData[fmid][famGarageObjid], 0, 18646, "matcolours", "white", 0x99ff0091);

        FamilyData[fmid][famGaragePickup] = CreateDynamicPickup(1313, 23, FamilyData[fmid][famGaragePos][0], FamilyData[fmid][famGaragePos][1], FamilyData[fmid][famGaragePos][2]-0.05, FamilyData[fmid][famGarageWorld], FamilyData[fmid][famGarageInt], -1, 30.00, -1, 0);
        
        static strrs[144];
        format(strrs, sizeof(strrs), "[ "WHITE"(Garasi Badside): "YELLOW"%s "GREEN"]", FamilyData[fmid][famName]);
        FamilyData[fmid][famGarageLabel] = CreateDynamic3DTextLabel(strrs, Y_GREEN, FamilyData[fmid][famGaragePos][0], FamilyData[fmid][famGaragePos][1], FamilyData[fmid][famGaragePos][2]+0.45, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, FamilyData[fmid][famGarageWorld], FamilyData[fmid][famGarageInt], -1, 10.00, -1, 0);

        Badside_Save(fmid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s mengubah posisi garage Family ID: %d.", AccountData[playerid][pAdminname], fmid);
    }
    else if(!strcmp(type, "garagespawn", true))
    {
        FamilyData[fmid][famGarageSpWorld] = GetPlayerVirtualWorld(playerid);
        FamilyData[fmid][famGarageSpInt] = GetPlayerInterior(playerid);

        GetPlayerPos(playerid, FamilyData[fmid][famGarageSpPos][0], FamilyData[fmid][famGarageSpPos][1], FamilyData[fmid][famGarageSpPos][2]);
        GetPlayerFacingAngle(playerid, FamilyData[fmid][famGarageSpPos][3]);

        Badside_Save(fmid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s mengubah posisi garage spawn Family ID: %d.", AccountData[playerid][pAdminname], fmid);
    }
    else if(!strcmp(type, "remove", true))
    {
        if(DestroyDynamic3DTextLabel(FamilyData[fmid][famVaultLabel]))
            FamilyData[fmid][famVaultLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        if(DestroyDynamic3DTextLabel(FamilyData[fmid][famDeskLabel]))
            FamilyData[fmid][famDeskLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        if(DestroyDynamicObject(FamilyData[fmid][famGarageObjid]))
            FamilyData[fmid][famGarageObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

        if(DestroyDynamicPickup(FamilyData[fmid][famGaragePickup]))
            FamilyData[fmid][famGaragePickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;
        
        if(DestroyDynamic3DTextLabel(FamilyData[fmid][famGarageLabel]))
            FamilyData[fmid][famGarageLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        FamilyData[fmid][famLeaderID] = 0;
        FamilyData[fmid][famLeaderName][0] = EOS;
        FamilyData[fmid][famName][0] = EOS;
        FamilyData[fmid][famMoney] = 0;
        FamilyData[fmid][famDirtyMoney] = 0;
        FamilyData[fmid][famVaultWorld] = 0;
        FamilyData[fmid][famVaultInt] = 0;
        FamilyData[fmid][famVaultPos][0] = 0;
        FamilyData[fmid][famVaultPos][1] = 0;
        FamilyData[fmid][famVaultPos][2] = 0;
        FamilyData[fmid][famDeskWorld] = 0;
        FamilyData[fmid][famDeskInt] = 0;
        FamilyData[fmid][famDeskPos][0] = 0;
        FamilyData[fmid][famDeskPos][1] = 0;
        FamilyData[fmid][famDeskPos][2] = 0;

        foreach(new i : Player)
        {
            if(AccountData[i][pFamily] == fmid)
            {
                AccountData[i][pFamily] = -1;
                AccountData[i][pFamilyRank] = 0;
            }
        }

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s menghapus Family ID: %d.", AccountData[playerid][pAdminname], fmid);

        new jeje[187];
        mysql_format(g_SQL, jeje, sizeof(jeje), "UPDATE `player_characters` SET `Char_Family` = -1, `Char_FamilyRank` = 0 WHERE `Char_Family` = %d", fmid);
        mysql_pquery(g_SQL, jeje);

        mysql_format(g_SQL, jeje, sizeof(jeje), "DELETE FROM `families` WHERE `ID` = %d", fmid);
        mysql_pquery(g_SQL, jeje);

        mysql_format(g_SQL, jeje, sizeof(jeje), "DELETE FROM `badside_brankas` WHERE `FMID` = %d", fmid);
        mysql_pquery(g_SQL, jeje);

        Iter_Remove(Fams, fmid);
    }
    return 1;
}