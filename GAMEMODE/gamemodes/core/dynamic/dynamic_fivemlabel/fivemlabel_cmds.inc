YCMD:addflabel(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    Dialog_Show(playerid, "FLabelAdd", DIALOG_STYLE_INPUT, "FiveM Label - Add", "Enter the text to display on the label:", "Pilih", "Batal");
    return 1;
}

YCMD:editflabel(playerid, params[], help)
{
    static
        flid,
        type[24],
        string[128];

    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    if(sscanf(params, "ds[24]S()[128]", flid, type, string)) return SUM(playerid, "/editflabel [id] [type]~n~location, pos, togpickup, pickup, text");
    
    if(!Iter_Contains(FivemLabels, flid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Fivem Label ID tersebut tidak valid!");

    if(!strcmp(type, "location", true))
    {
        GetPlayerPos(playerid, FivemLabelData[flid][fLabelPos][0], FivemLabelData[flid][fLabelPos][1], FivemLabelData[flid][fLabelPos][2]);
        GetPlayerFacingAngle(playerid, FivemLabelData[flid][fLabelPos][3]);
        FivemLabelData[flid][fLabelWorld] = GetPlayerVirtualWorld(playerid);
        FivemLabelData[flid][fLabelInterior] = GetPlayerInterior(playerid);
        FivemLabel_Save(flid);
        FivemLabel_Refresh(flid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set the location for Fivem Labels ID: %d.", AccountData[playerid][pAdminname], flid);
    }
    else if(!strcmp(type, "pos", true))
    {
        if(AccountData[playerid][EditingFLabelID] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang berada di dalam mode editing!");

        if(!IsPlayerInRangeOfPoint(playerid, 30.0, FivemLabelData[flid][fLabelPos][0], FivemLabelData[flid][fLabelPos][1], FivemLabelData[flid][fLabelPos][2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan fivem label tersebut!");
        if(FivemLabel_BeingEdited(flid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Fivem Labels ID tersebut sedang diedit oleh admin lain!");

        AccountData[playerid][EditingFLabelID] = flid;
        EditDynamicObject(playerid, FivemLabelData[flid][fLabelObject]);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s edited the position of Fivem Labels ID: %d.", AccountData[playerid][pAdminname], flid);
    }
    else if(!strcmp(type, "togpickup", true))
    {
        switch(FivemLabelData[flid][fLabelTogPickup])
        {
            case false:
            {
                if(DestroyDynamicPickup(FivemLabelData[flid][fLabelPickup]))
                {
                    FivemLabelData[flid][fLabelPickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;
                }

                FivemLabelData[flid][fLabelTogPickup] = true;
                FivemLabelData[flid][fLabelPickupID] = 1239;

                FivemLabelData[flid][fLabelPickup] = CreateDynamicPickup(FivemLabelData[flid][fLabelPickupID], 23, FivemLabelData[flid][fLabelPos][0], FivemLabelData[flid][fLabelPos][1], FivemLabelData[flid][fLabelPos][2], FivemLabelData[flid][fLabelWorld], FivemLabelData[flid][fLabelInterior], -1, 100.00, -1, 0);
            }
            case true:
            {
                if(DestroyDynamicPickup(FivemLabelData[flid][fLabelPickup]))
                {
                    FivemLabelData[flid][fLabelPickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;
                }
                FivemLabelData[flid][fLabelTogPickup] = false;
            }
        }
        FivemLabel_Save(flid);
        FivemLabel_Refresh(flid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set the pickup toggle for Fivem Labels ID: %d to %d.", AccountData[playerid][pAdminname], flid, FivemLabelData[flid][fLabelTogPickup]);
    }
    else if(!strcmp(type, "pickup", true))
    {
        new pickupid;

        if(!FivemLabelData[flid][fLabelTogPickup]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Fivem Label ID tersebut tidak memiliki pickup!");

        if(sscanf(string, "d", pickupid))
            return SUM(playerid, "/editflabel [id] [pickup] [pickup id]");

        FivemLabelData[flid][fLabelPickupID] = pickupid;

        FivemLabel_Save(flid);
        FivemLabel_Refresh(flid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set the Pickup ID for Fivem Labels ID: %d to %d.", AccountData[playerid][pAdminname], flid, pickupid);
    }
    else if(!strcmp(type, "text", true))
    {
        AccountData[playerid][EditingFLabelID] = flid;

        Dialog_Show(playerid, "FLabelEdit", DIALOG_STYLE_INPUT, "FiveM Label - Edit Text", "Enter the text to be changed on the label:", "Pilih", "Batal");
    }
    return 1;
}

YCMD:removeflabel(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    static
        flid;

    if(sscanf(params, "d", flid)) return SUM(playerid, "/removeflabel [id]");

    if(!Iter_Contains(FivemLabels, flid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Fivem Label ID tersebut tidak valid!");

    if(DestroyDynamicObject(FivemLabelData[flid][fLabelObject]))
    {
        FivemLabelData[flid][fLabelObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
    }

    if(DestroyDynamicPickup(FivemLabelData[flid][fLabelPickup]))
    {
        FivemLabelData[flid][fLabelPickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;
    }
    
    FivemLabelData[flid][fLabelPickupID] = 1239;
    FivemLabelData[flid][fLabelTogPickup] = false;
    FivemLabelData[flid][fLabelText][0] = EOS;
    FivemLabelData[flid][fLabelPos][0] = 0.0;
    FivemLabelData[flid][fLabelPos][1] = 0.0;
    FivemLabelData[flid][fLabelPos][2] = 0.0;
    FivemLabelData[flid][fLabelWorld] = 0;
    FivemLabelData[flid][fLabelInterior] = 0;
    
    Iter_Remove(FivemLabels, flid);

    new query[128];
    mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `fivem_labels` WHERE `ID`=%d", flid);
    mysql_pquery(g_SQL, query);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has deleted Fivem Labels ID: %d.", AccountData[playerid][pAdminname], flid);
    return 1;
}

YCMD:gotoflabel(playerid, params[], help)
{
    new id;
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);
        
    if(sscanf(params, "d", id))
        return SUM(playerid, "/gotoflabel [id]");

    if(!Iter_Contains(FivemLabels, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Fivem Label ID tersebut tidak valid!");
    SetPlayerPositionEx(playerid, FivemLabelData[id][fLabelPos][0], FivemLabelData[id][fLabelPos][1], FivemLabelData[id][fLabelPos][2], -90);
    SetPlayerInteriorEx(playerid, FivemLabelData[id][fLabelInterior]);
    SetPlayerVirtualWorldEx(playerid, FivemLabelData[id][fLabelWorld]);

    AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInRusun] = -1;
    AccountData[playerid][pInGudang] = -1;
    return 1;
}