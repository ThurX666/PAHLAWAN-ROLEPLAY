#include <YSI_Coding\y_hooks>

#define MAX_GZONE 100

enum e_gzone_details
{
    gZoneController,
    Float:gZonePos[3],

    //not saved
    STREAMER_TAG_PICKUP:gZonePickup,
    STREAMER_TAG_3D_TEXT_LABEL:gZoneLabel,
    gZoneTakingTime,
    bool:gZoneAttacked,
    gZoneAttackedByFID
};
new GangZoneData[MAX_GZONE][e_gzone_details],
    Iterator:GZones<MAX_GZONE>;

GZone_Save(GZID)
{
    new jksaw[250];
    mysql_format(g_SQL, jksaw, sizeof(jksaw), "UPDATE `gangzones` SET `Controller` = %d, X = '%f', Y = '%f', Z = '%f' WHERE `ID` = %d", GangZoneData[GZID][gZoneController], GangZoneData[GZID][gZonePos][0], GangZoneData[GZID][gZonePos][1], GangZoneData[GZID][gZonePos][2], GZID);
    mysql_pquery(g_SQL, jksaw);
    return 1;    
}

forward OnGZoneCreated(playerid, GZID);
public OnGZoneCreated(playerid, GZID)
{
    GZone_Save(GZID);

    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s membuat Gang Zone dengan ID: %d.", AccountData[playerid][pAdminname], GZID);
    return 1;
}

YCMD:addgzone(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new GZID = Iter_Free(GZones);

    if(GZID == -1) return SEM(playerid, "Jumlah dynamic gang zone sudah mencapai maksimum!");

    GetPlayerPos(playerid, GangZoneData[GZID][gZonePos][0], GangZoneData[GZID][gZonePos][1], GangZoneData[GZID][gZonePos][2]);
    GangZoneData[GZID][gZoneController] = -1;

    GangZoneData[GZID][gZonePickup] = CreateDynamicPickup(19306, 23, GangZoneData[GZID][gZonePos][0], GangZoneData[GZID][gZonePos][1], GangZoneData[GZID][gZonePos][2], 0, 0, -1, 30.0, -1, 0);
    
    new gdgsr[158], jksaw[250];
    format(gdgsr, sizeof(gdgsr), "| Wilayah %s |\n[Penguasa: %s]\nGunakan "YELLOW"'/gwar' "WHITE"untuk merebut wilayah ini!", GetLocation(GangZoneData[GZID][gZonePos][0], GangZoneData[GZID][gZonePos][1], GangZoneData[GZID][gZonePos][2]), GetFamilyName(GangZoneData[GZID][gZoneController]));
    GangZoneData[GZID][gZoneLabel] = CreateDynamic3DTextLabel(gdgsr, Y_WHITE, GangZoneData[GZID][gZonePos][0], GangZoneData[GZID][gZonePos][1], GangZoneData[GZID][gZonePos][2] + 0.55, 3.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 3.00, -1, 0);
    
    Iter_Add(GZones, GZID);

    mysql_format(g_SQL, jksaw, sizeof(jksaw), "INSERT INTO `gangzones` SET `ID` = %d, `Controller` = %d, X = '%f', Y = '%f', Z = '%f'", GZID, GangZoneData[GZID][gZoneController], GangZoneData[GZID][gZonePos][0], GangZoneData[GZID][gZonePos][1], GangZoneData[GZID][gZonePos][2]);
    mysql_pquery(g_SQL, jksaw, "OnGZoneCreated", "id", playerid, GZID);
    return 1;
}

YCMD:editgzone(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new GZID, type[24], string[128];
    if(sscanf(params, "ds[24]S()[128]", GZID, type, string)) return SUM(playerid, "/editgzone [id] [name]~n~pos, controller, reset");
    if(!Iter_Contains(GZones, GZID)) return SEM(playerid, "ID Gang Zone tersebut tidak valid!");

    if(!strcmp(type, "pos", true))
    {
        GetPlayerPos(playerid, GangZoneData[GZID][gZonePos][0], GangZoneData[GZID][gZonePos][1], GangZoneData[GZID][gZonePos][2]);
        GZone_Save(GZID);
        GZone_Refresh(GZID);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s mengubah lokasi gang zone ID: %d.", AccountData[playerid][pAdminname], GZID);
    }
    else if(!strcmp(type, "controller", true))
    {
        new FID;
        if(sscanf(string, "d", FID)) return SUM(playerid, "/editgzone [id] [controller] [FID]");
        if(FID < 0) return SEM(playerid, "FID tersebut tidak valid!");
        if(!Iter_Contains(Fams, FID)) return SEM(playerid, "FID tersebut tidak valid!");

        GangZoneData[GZID][gZoneController] = FID;
        GZone_Save(GZID);
        GZone_Refresh(GZID);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s mengubah penguasa gang zone ID: %d menjadi %s.", AccountData[playerid][pAdminname], GZID, GetFamilyName(GangZoneData[GZID][gZoneController]));
    }
    else if(!strcmp(type, "reset", true))
    {
        GangZoneData[GZID][gZoneController] = -1;
        GZone_Save(GZID);
        GZone_Refresh(GZID);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s mereset penguasa gang zone ID: %d.", AccountData[playerid][pAdminname], GZID);
    }
    return 1;
}

YCMD:removegzone(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new GZID, strgbg[128];
    if(sscanf(params, "d", GZID)) return SUM(playerid, "/removegzone [id]");
    if(!Iter_Contains(GZones, GZID)) return SEM(playerid, "ID Gang Zone tersebut tidak valid!");

    GangZoneData[GZID][gZoneController] = -1;
    GangZoneData[GZID][gZonePos][0] = GangZoneData[GZID][gZonePos][1] = GangZoneData[GZID][gZonePos][2] = 0.0;

    if(DestroyDynamicPickup(GangZoneData[GZID][gZonePickup]))
        GangZoneData[GZID][gZonePickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

    if(DestroyDynamic3DTextLabel(GangZoneData[GZID][gZoneLabel]))
        GangZoneData[GZID][gZoneLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    Iter_Remove(GZones, GZID);

    mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `gangzones` WHERE `ID` = %d", GZID);
    mysql_pquery(g_SQL, strgbg);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s menghapus Gang Zone dengan ID: %d.", AccountData[playerid][pAdminname], GZID);
    return 1;
}