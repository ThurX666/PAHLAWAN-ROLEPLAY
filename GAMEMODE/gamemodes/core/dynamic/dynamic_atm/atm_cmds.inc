YCMD:addatm(playerid, params[], help)
{
    new atmid = Iter_Free(Atms), hjha[258];
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    GetPlayerPos(playerid, AtmData[atmid][atmPos][0], AtmData[atmid][atmPos][1], AtmData[atmid][atmPos][2]);
    AtmData[atmid][atmPos][3] = 0.0;
    AtmData[atmid][atmPos][4] = 0.0;
    GetPlayerFacingAngle(playerid, AtmData[atmid][atmPos][5]);

    AtmData[atmid][atmWorld] = GetPlayerVirtualWorld(playerid);
    AtmData[atmid][atmInt] = GetPlayerInterior(playerid);

    AtmData[atmid][atmObject] = CreateDynamicObject(11688, AtmData[atmid][atmPos][0], AtmData[atmid][atmPos][1], AtmData[atmid][atmPos][2], AtmData[atmid][atmPos][3], AtmData[atmid][atmPos][4], AtmData[atmid][atmPos][5], AtmData[atmid][atmWorld], AtmData[atmid][atmInt], -1, 100.00, 100.00);
    SetDynamicObjectMaterial(AtmData[atmid][atmObject], 1, 19130, "matarrows", "green", 0x00000000);
    SetDynamicObjectMaterial(AtmData[atmid][atmObject], 3, 6060, "shops2_law", "atmflat", 0x00000000);
    AtmData[atmid][atmArea] = CreateDynamicSphere(AtmData[atmid][atmPos][0], AtmData[atmid][atmPos][1], AtmData[atmid][atmPos][2], 2.5, AtmData[atmid][atmWorld], AtmData[atmid][atmInt], -1);
    Iter_Add(Atms, atmid);

    mysql_format(g_SQL, hjha, sizeof(hjha), "INSERT INTO `atms` SET `ID`=%d, `X`='%f', `Y`='%f', `Z`='%f', `RX`='%f', `RY`='%f', `RZ`='%f', `World`=%d, `Interior`=%d",
        atmid, AtmData[atmid][atmPos][0], AtmData[atmid][atmPos][1], AtmData[atmid][atmPos][2], AtmData[atmid][atmPos][3], AtmData[atmid][atmPos][4], AtmData[atmid][atmPos][5], AtmData[atmid][atmWorld], AtmData[atmid][atmInt]);
    mysql_pquery(g_SQL, hjha, "OnAtmAdded", "ii", playerid, atmid);
    return 1;
}

YCMD:editatm(playerid, params[], help)
{
    new atmid;
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);
    if (AccountData[playerid][EditingAtmID] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang dalam mode editing!");

    if (sscanf(params, "d", atmid))
    {
        SUM(playerid, "/editgarbage [id]");
        return 1;
    }

    if (!Iter_Contains(Atms, atmid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid ATM ID!");

    if (!IsPlayerInRangeOfPoint(playerid, 30.0, AtmData[atmid][atmPos][0], AtmData[atmid][atmPos][1], AtmData[atmid][atmPos][2]))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan dynamic ATM tersebut!");
    if (Atm_BeingEdited(atmid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID ATM sedang diedit oleh admin lain!");

    AccountData[playerid][EditingAtmID] = atmid;
    EditDynamicObject(playerid, AtmData[atmid][atmObject]);

    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s edited ATM position ID: %d.", AccountData[playerid][pAdminname], atmid);
    return 1;
}

YCMD:gotoatm(playerid, params[], help)
{
    new atmid;
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    if (sscanf(params, "d", atmid))
        return SUM(playerid, "/gotoatm [id]");

    if (!Iter_Contains(Atms, atmid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid ATM ID!");
    SetPlayerPositionEx(playerid, AtmData[atmid][atmPos][0], AtmData[atmid][atmPos][1], AtmData[atmid][atmPos][2], AtmData[atmid][atmPos][5]);
    SetPlayerInteriorEx(playerid, AtmData[atmid][atmInt]);
    SetPlayerVirtualWorldEx(playerid, AtmData[atmid][atmWorld]);

    AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInRusun] = -1;
    AccountData[playerid][pInGudang] = -1;
    return 1;
}

YCMD:removeatm(playerid, params[], help)
{
    new atmid, strgbg[128];
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    if (sscanf(params, "d", atmid))
        return SUM(playerid, "/removeatm [id]");

    if (!Iter_Contains(Atms, atmid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid ATM ID!");
    if (Atm_BeingEdited(atmid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID ATM sedang diedit oleh admin lain!");

    if (DestroyDynamicObject(AtmData[atmid][atmObject]))
        AtmData[atmid][atmObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

    if (DestroyDynamicArea(AtmData[atmid][atmArea]))
        AtmData[atmid][atmArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

    AtmData[atmid][atmPos][0] = AtmData[atmid][atmPos][1] = AtmData[atmid][atmPos][2] = AtmData[atmid][atmPos][3] = AtmData[atmid][atmPos][4] = AtmData[atmid][atmPos][5] = 0.0;
    AtmData[atmid][atmWorld] = 0;
    AtmData[atmid][atmInt] = 0;

    Iter_Remove(Atms, atmid);

    mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `atms` WHERE `ID` = %d", atmid);
    mysql_pquery(g_SQL, strgbg);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s removed ATM with ID: %d.", AccountData[playerid][pAdminname], atmid);
    return 1;
}


YCMD:addbankpoint(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new bptid = Iter_Free(BankPoints), hjha[258];
    GetPlayerPos(playerid, BankPoint[bptid][bankPos][0], BankPoint[bptid][bankPos][1], BankPoint[bptid][bankPos][2]);

    BankPoint[bptid][bankWorld] = GetPlayerVirtualWorld(playerid);
    BankPoint[bptid][bankInt] = GetPlayerInterior(playerid);

    BankPoint[bptid][bankPickup] = CreateDynamicPickup(1274, 23, BankPoint[bptid][bankPos][0], BankPoint[bptid][bankPos][1], BankPoint[bptid][bankPos][2], BankPoint[bptid][bankWorld], BankPoint[bptid][bankInt], -1, 30.00, -1, 0);
    BankPoint[bptid][bankLabel] = CreateDynamic3DTextLabel("[Fleeca Bank Point]\n"WHITE"Selamat datang di Fleeca Bank!\nGunakan "GREEN"[Y] "WHITE"untuk akses bank menu", 0xc0c0c8A6, BankPoint[bptid][bankPos][0], BankPoint[bptid][bankPos][1], BankPoint[bptid][bankPos][2]+0.85, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, BankPoint[bptid][bankWorld], BankPoint[bptid][bankInt], -1, 10.00, -1, 0);
    
    Iter_Add(BankPoints, bptid);

    mysql_format(g_SQL, hjha, sizeof(hjha), "INSERT INTO `bankpoints` SET `ID`=%d, `X`='%f', `Y`='%f', `Z`='%f', `World`=%d, `Interior`=%d",
        bptid, BankPoint[bptid][bankPos][0], BankPoint[bptid][bankPos][1], BankPoint[bptid][bankPos][2], BankPoint[bptid][bankWorld], BankPoint[bptid][bankInt]);
    mysql_pquery(g_SQL, hjha, "OnBankPointAdded", "ii", playerid, bptid);
    return 1;
}

YCMD:removebankpoint(playerid, params[], help)
{
    new bptid, strgbg[128];
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    if (sscanf(params, "d", bptid))
        return SUM(playerid, "/removebankpoint [id]");

    if (!Iter_Contains(BankPoints, bptid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Bank Point ID!");

    if (DestroyDynamicPickup(BankPoint[bptid][bankPickup]))
        BankPoint[bptid][bankPickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

    if (DestroyDynamic3DTextLabel(BankPoint[bptid][bankLabel]))
        BankPoint[bptid][bankLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    BankPoint[bptid][bankPos][0] = BankPoint[bptid][bankPos][1] = BankPoint[bptid][bankPos][2] = 0.0;
    BankPoint[bptid][bankWorld] = 0;
    BankPoint[bptid][bankInt] = 0;

    Iter_Remove(BankPoints, bptid);

    mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `bankpoints` WHERE `ID` = %d", bptid);
    mysql_pquery(g_SQL, strgbg);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s removed Bank Point with ID: %d.", AccountData[playerid][pAdminname], bptid);
    return 1;
}

YCMD:gotobankpoint(playerid, params[], help)
{
    new bptid;
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    if (sscanf(params, "d", bptid))
        return SUM(playerid, "/gotobankpoint [id]");

    if (!Iter_Contains(BankPoints, bptid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid bank point ID!");
    SetPlayerPositionEx(playerid, BankPoint[bptid][bankPos][0], BankPoint[bptid][bankPos][1], BankPoint[bptid][bankPos][2], 90.00);
    SetPlayerInteriorEx(playerid, BankPoint[bptid][bankInt]);
    SetPlayerVirtualWorldEx(playerid, BankPoint[bptid][bankWorld]);

    AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInRusun] = -1;
    AccountData[playerid][pInGudang] = -1;
    return 1;
}