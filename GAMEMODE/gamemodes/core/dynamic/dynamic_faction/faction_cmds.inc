YCMD:addlocker(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new lockertype, name[64];
    if(sscanf(params, "ds[64]", lockertype, name)) return SUM(playerid, "/addlocker [faction id] [name]");

    if(lockertype < 1 || lockertype > MAX_FACTIONS - 1) return SUM(playerid, "Type should be between 1 and 9");
    new lid = Iter_Free(Lockers);
    if(lid <= -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah dynamic lockers telah mencapai batas maksimum!");

    GetPlayerPos(playerid, LockerData[lid][Pos][0], LockerData[lid][Pos][1], LockerData[lid][Pos][2]);
    LockerData[lid][World] = GetPlayerVirtualWorld(playerid);
    LockerData[lid][Interior] = GetPlayerInterior(playerid);
    LockerData[lid][Type] = lockertype;
    strcopy(LockerData[lid][Text], name);

    Iter_Add(Lockers, lid);

    static string[258];
    mysql_format(g_SQL, string, sizeof(string), "INSERT INTO `lockers` (`id`, `posx`, `posy`, `posz`, `world`, `interior`, `type`, `name`) VALUES (%d, '%f', '%f', '%f', %d, %d, %d, '%e')", lid, LockerData[lid][Pos][0], LockerData[lid][Pos][1], LockerData[lid][Pos][2], LockerData[lid][World], LockerData[lid][Interior], LockerData[lid][Type], LockerData[lid][Text]);
    mysql_pquery(g_SQL, string);

    Locker_Rebuild(lid);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s created a locker with ID: %d.", AccountData[playerid][pAdminname], lid);
    return 1;
}

YCMD:removelocker(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new lid;
    if(sscanf(params, "d", lid)) return SUM(playerid, "/removelocker [locker id]");

    if(!Iter_Contains(Lockers, lid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Locker ID tersebut tidak valid!");

    LockerData[lid][Pos][0] = 0.0;
    LockerData[lid][Pos][1] = 0.0;
    LockerData[lid][Pos][2] = 0.0;
    LockerData[lid][World] = 0;
    LockerData[lid][Interior] = 0;
    LockerData[lid][Type] = 0;
    LockerData[lid][Text][0] = EOS;

    if(DestroyDynamicPickup(LockerData[lid][Pickup]))
        LockerData[lid][Pickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

    if(DestroyDynamic3DTextLabel(LockerData[lid][Label]))
        LockerData[lid][Label] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    static string[128];
    mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `lockers` WHERE `id` = %d", lid);
    mysql_pquery(g_SQL, string);
    
    Iter_Remove(Lockers, lid);
    return 1;
}

YCMD:addfcrafting(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new lockertype;
    if(sscanf(params, "d", lockertype)) return SUM(playerid, "/addfcrafting [faction id]");

    if(lockertype != FACTION_BENNYS && lockertype != FACTION_AUTOMAX && lockertype != FACTION_HANDOVER) return ShowTDN(playerid, NOTIFICATION_ERROR, "CMD ini hanya untuk faction jenis bengkel!");

    new lid = Iter_Free(FCrafts);
    if(lid <= -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah dynamic faction craft telah mencapai batas maksimum!");

    GetPlayerPos(playerid, FCraftData[lid][Pos][0], FCraftData[lid][Pos][1], FCraftData[lid][Pos][2]);
    FCraftData[lid][World] = GetPlayerVirtualWorld(playerid);
    FCraftData[lid][Interior] = GetPlayerInterior(playerid);
    FCraftData[lid][Type] = lockertype;

    Iter_Add(FCrafts, lid);

    static string[258];
    mysql_format(g_SQL, string, sizeof(string), "INSERT INTO `fcrafts` (`id`, `posx`, `posy`, `posz`, `world`, `interior`, `type`) VALUES (%d, '%f', '%f', '%f', %d, %d, %d)", lid, FCraftData[lid][Pos][0], FCraftData[lid][Pos][1], FCraftData[lid][Pos][2], FCraftData[lid][World], FCraftData[lid][Interior], FCraftData[lid][Type]);
    mysql_pquery(g_SQL, string);

    FCraft_Rebuild(lid);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s created a facton crafting with ID: %d.", AccountData[playerid][pAdminname], lid);
    return 1;
}

YCMD:removefcraft(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new lid;
    if(sscanf(params, "d", lid)) return SUM(playerid, "/removefcraft [faction craft id]");

    if(!Iter_Contains(FCrafts, lid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Faction Craft ID tersebut tidak valid!");

    FCraftData[lid][Pos][0] = 0.0;
    FCraftData[lid][Pos][1] = 0.0;
    FCraftData[lid][Pos][2] = 0.0;
    FCraftData[lid][World] = 0;
    FCraftData[lid][Interior] = 0;
    FCraftData[lid][Type] = 0;

    if(DestroyDynamicPickup(FCraftData[lid][Pickup]))
        FCraftData[lid][Pickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

    if(DestroyDynamic3DTextLabel(FCraftData[lid][Label]))
        FCraftData[lid][Label] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    static string[128];
    mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `fcrafts` WHERE `id` = %d", lid);
    mysql_pquery(g_SQL, string);
    
    Iter_Remove(FCrafts, lid);
    return 1;
}

YCMD:addarmoury(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new lid = Iter_Free(Armouries), name[64];
    if(sscanf(params, "s[64]", name)) return SUM(playerid, "/addarmoury [name]");

    if(lid <= -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah dynamic armoury telah mencapai batas maksimum!");

    GetPlayerPos(playerid, ArmouryData[lid][Pos][0], ArmouryData[lid][Pos][1], ArmouryData[lid][Pos][2]);
    ArmouryData[lid][World] = GetPlayerVirtualWorld(playerid);
    ArmouryData[lid][Interior] = GetPlayerInterior(playerid);
    strcopy(ArmouryData[lid][Text], name);
    Iter_Add(Armouries, lid);

    static string[268];
    mysql_format(g_SQL, string, sizeof(string), "INSERT INTO `armouries` (`id`, `posx`, `posy`, `posz`, `world`, `interior`, `name`) VALUES (%d, '%f', '%f', '%f', %d, %d, '%e')", lid, ArmouryData[lid][Pos][0], ArmouryData[lid][Pos][1], ArmouryData[lid][Pos][2], ArmouryData[lid][World], ArmouryData[lid][Interior], ArmouryData[lid][Text]);
    mysql_pquery(g_SQL, string);

    Armoury_Rebuild(lid);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s created an armoury with ID: %d.", AccountData[playerid][pAdminname], lid);
    return 1;
}

YCMD:removearmoury(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new lid;
    if(sscanf(params, "d", lid)) return SUM(playerid, "/removearmoury [id]");

    if(!Iter_Contains(Armouries, lid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Armoury ID tersebut tidak valid!");

    ArmouryData[lid][Pos][0] = 0.0;
    ArmouryData[lid][Pos][1] = 0.0;
    ArmouryData[lid][Pos][2] = 0.0;
    ArmouryData[lid][World] = 0;
    ArmouryData[lid][Interior] = 0;

    if(DestroyDynamicPickup(ArmouryData[lid][Pickup]))
        ArmouryData[lid][Pickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

    if(DestroyDynamic3DTextLabel(ArmouryData[lid][Label]))
        ArmouryData[lid][Label] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    static string[128];
    mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `armouries` WHERE `id` = %d", lid);
    mysql_pquery(g_SQL, string);
    
    Iter_Remove(Armouries, lid);
    return 1;
}

YCMD:addvault(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new lockertype, name[64];
    if(sscanf(params, "ds[64]", lockertype, name)) return SUM(playerid, "/addvault [faction id] [name]");

    if(lockertype < 1 || lockertype > MAX_FACTIONS - 1) return SUM(playerid, "Invalid faction ID");
    new lid = Iter_Free(Vaults);
    if(lid <= -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah dynamic faction vaults telah mencapai batas maksimum!");

    GetPlayerPos(playerid, VaultData[lid][Pos][0], VaultData[lid][Pos][1], VaultData[lid][Pos][2]);
    VaultData[lid][World] = GetPlayerVirtualWorld(playerid);
    VaultData[lid][Interior] = GetPlayerInterior(playerid);
    VaultData[lid][Type] = lockertype;
    strcopy(VaultData[lid][Text], name);

    Iter_Add(Vaults, lid);

    static string[258];
    mysql_format(g_SQL, string, sizeof(string), "INSERT INTO `vaults` (`id`, `posx`, `posy`, `posz`, `world`, `interior`, `type`, `name`) VALUES (%d, '%f', '%f', '%f', %d, %d, %d, '%e')", lid, VaultData[lid][Pos][0], VaultData[lid][Pos][1], VaultData[lid][Pos][2], VaultData[lid][World], VaultData[lid][Interior], VaultData[lid][Type], VaultData[lid][Text]);
    mysql_pquery(g_SQL, string);

    Vault_Rebuild(lid);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s created a faction vault with ID: %d.", AccountData[playerid][pAdminname], lid);
    return 1;
}

YCMD:removevault(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new lid;
    if(sscanf(params, "d", lid)) return SUM(playerid, "/removevault [id]");

    if(!Iter_Contains(Vaults, lid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Vault ID tersebut tidak valid!");

    VaultData[lid][Pos][0] = 0.0;
    VaultData[lid][Pos][1] = 0.0;
    VaultData[lid][Pos][2] = 0.0;
    VaultData[lid][World] = 0;
    VaultData[lid][Interior] = 0;

    if(DestroyDynamicPickup(VaultData[lid][Pickup]))
        VaultData[lid][Pickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

    if(DestroyDynamic3DTextLabel(VaultData[lid][Label]))
        VaultData[lid][Label] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    static string[128];
    mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `vaults` WHERE `id` = %d", lid);
    mysql_pquery(g_SQL, string);
    
    Iter_Remove(Vaults, lid);
    return 1;
}

YCMD:addfgarage(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new lockertype, name[64];
    if(sscanf(params, "ds[64]", lockertype, name)) return SUM(playerid, "/addfgarage [faction id] [name]");

    if(lockertype < 1 || lockertype > MAX_FACTIONS - 1) return SUM(playerid, "Invalid faction ID");
    new lid = Iter_Free(FGarages);
    if(lid <= -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah dynamic lockers telah mencapai batas maksimum!");

    GetPlayerPos(playerid, FactGarageData[lid][Pos][0], FactGarageData[lid][Pos][1], FactGarageData[lid][Pos][2]);
    
    FactGarageData[lid][GaragePos][0] = FactGarageData[lid][Pos][0];
    FactGarageData[lid][GaragePos][1] = FactGarageData[lid][Pos][1];
    FactGarageData[lid][GaragePos][2] = FactGarageData[lid][Pos][2];

    FactGarageData[lid][GarageSpawnPos][0] = FactGarageData[lid][Pos][0];
    FactGarageData[lid][GarageSpawnPos][1] = FactGarageData[lid][Pos][1];
    FactGarageData[lid][GarageSpawnPos][2] = FactGarageData[lid][Pos][2];
    GetPlayerFacingAngle(playerid, FactGarageData[lid][GarageSpawnPos][3]);

    FactGarageData[lid][World] = GetPlayerVirtualWorld(playerid);
    FactGarageData[lid][Interior] = GetPlayerInterior(playerid);
    FactGarageData[lid][Type] = lockertype;
    strcopy(FactGarageData[lid][Text], name);

    Iter_Add(FGarages, lid);

    static string[512];
    mysql_format(g_SQL, string, sizeof(string), "INSERT INTO `faction_garages` (`id`, `posx`, `posy`, `posz`, `gposx`, `gposy`, `gposz`, `gposspawnx`, `gposspawny`, `gposspawnz`, `gposspawna`, `world`, `interior`, `type`, `name`) VALUES (%d, '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', %d, %d, %d, '%e')", lid, FactGarageData[lid][Pos][0], FactGarageData[lid][Pos][1], FactGarageData[lid][Pos][2], FactGarageData[lid][GaragePos][0], FactGarageData[lid][GaragePos][1], FactGarageData[lid][GaragePos][2], FactGarageData[lid][GarageSpawnPos][0], FactGarageData[lid][GarageSpawnPos][1], FactGarageData[lid][GarageSpawnPos][2], FactGarageData[lid][GarageSpawnPos][3], FactGarageData[lid][World], FactGarageData[lid][Interior], FactGarageData[lid][Type], FactGarageData[lid][Text]);
    mysql_pquery(g_SQL, string);

    FGarage_Rebuild(lid);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s created a faction garage with ID: %d.", AccountData[playerid][pAdminname], lid);
    return 1;
}

YCMD:editfgarage(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new lid;
    if(sscanf(params, "d", lid)) return SUM(playerid, "/editfgarage [id]");
    if(!Iter_Contains(FGarages, lid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Faction garage ID tersebut tidak valid!");
    
    if(IsPlayerInAnyVehicle(playerid))
    {
        new vid = GetPlayerVehicleID(playerid);
        GetVehiclePos(vid, FactGarageData[lid][GarageSpawnPos][0], FactGarageData[lid][GarageSpawnPos][1], FactGarageData[lid][GarageSpawnPos][2]);
        GetVehicleZAngle(vid, FactGarageData[lid][GarageSpawnPos][3]);
    }
    else
    {
        GetPlayerPos(playerid, FactGarageData[lid][GarageSpawnPos][0], FactGarageData[lid][GarageSpawnPos][1], FactGarageData[lid][GarageSpawnPos][2]);
        GetPlayerFacingAngle(playerid, FactGarageData[lid][GarageSpawnPos][3]);
    }

    static string[268];
    mysql_format(g_SQL, string, sizeof(string), "UPDATE `faction_garages` SET `gposspawnx` = '%f', `gposspawny` = '%f', `gposspawnz` = '%f', `gposspawna` = '%f' WHERE `id` = %d", FactGarageData[lid][GarageSpawnPos][0], FactGarageData[lid][GarageSpawnPos][1], FactGarageData[lid][GarageSpawnPos][2], FactGarageData[lid][GarageSpawnPos][3], lid);
    mysql_pquery(g_SQL, string);

    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s modified the spawn of faction garage ID: %d.", AccountData[playerid][pAdminname], lid);
    return 1;
}

YCMD:removefgarage(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new lid;
    if(sscanf(params, "d", lid)) return SUM(playerid, "Usage: /removefgarage [id]");

    if(!Iter_Contains(FGarages, lid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Faction Garage ID!");

    FactGarageData[lid][Pos][0] = 0.0;
    FactGarageData[lid][Pos][1] = 0.0;
    FactGarageData[lid][Pos][2] = 0.0;
    FactGarageData[lid][GaragePos][0] = 0.0;
    FactGarageData[lid][GaragePos][1] = 0.0;
    FactGarageData[lid][GaragePos][2] = 0.0;
    FactGarageData[lid][GarageSpawnPos][0] = 0.0;
    FactGarageData[lid][GarageSpawnPos][1] = 0.0;
    FactGarageData[lid][GarageSpawnPos][2] = 0.0;
    FactGarageData[lid][GarageSpawnPos][3] = 0.0;
    FactGarageData[lid][World] = 0;
    FactGarageData[lid][Interior] = 0;

    if(DestroyDynamicPickup(FactGarageData[lid][Pickup]))
        FactGarageData[lid][Pickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

    if(DestroyDynamic3DTextLabel(FactGarageData[lid][Label]))
        FactGarageData[lid][Label] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    if(DestroyDynamicObject(FactGarageData[lid][Object]))
        FactGarageData[lid][Object] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

    static string[128];
    mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `faction_garages` WHERE `id` = %d", lid);
    mysql_pquery(g_SQL, string);
    
    Iter_Remove(FGarages, lid);
    return 1;
}

YCMD:locker(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] == FACTION_NONE) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari faction manapun!");

    if(!IsPlayerNearLocker(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan locker faction anda!");

    switch(AccountData[playerid][pFaction])
    {
        case FACTION_LSPD:
        {
            Dialog_Show(playerid, "PolisiLocker", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Locker Kepolisian", 
            "On Duty/Off Duty\n\
            Ganti Seragam\n\
            Plain Clothes Detective\n\
            Ambil Perlengkapan\n\
            Simpan Perlengkapan", "Pilih", "Batal");
        }
        case FACTION_LSFD:
        {
            Dialog_Show(playerid, "ParamedisLocker", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Locker Paramedis", 
            "On Duty/Off Duty\n\
            Ganti Seragam", "Pilih", "Batal");
        }
        case FACTION_PUTRIDELI:
        {
            Dialog_Show(playerid, "PutrideliLocker", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Locker Koki Sunda", 
            "On Duty/Off Duty\n\
            Ganti Seragam", "Pilih", "Batal");
        }
        case FACTION_SAGOV:
        {
            Dialog_Show(playerid, "PemerintahLocker", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Locker Pemerintah", 
            "On Duty/Off Duty\n\
            Ganti Seragam\n\
            Baton Stick", "Pilih", "Batal");
        }
        case FACTION_BENNYS:
        {
            Dialog_Show(playerid, "BennysLocker", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Locker Bennys", 
            "On Duty/Off Duty\n\
            Ganti Seragam", "Pilih", "Batal");
        }
        case FACTION_UBER:
        {
            Dialog_Show(playerid, "UberLocker", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Locker Uber", 
            "On Duty/Off Duty\n\
            Ganti Seragam", "Pilih", "Batal");
        }
        case FACTION_DINARBUCKS:
        {
            Dialog_Show(playerid, "DinarbucksLocker", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Locker Dinarbucks", 
            "On Duty/Off Duty\n\
            Ganti Seragam", "Pilih", "Batal");
        }
        case FACTION_FOX11:
        {
            Dialog_Show(playerid, "PewartaLocker", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Locker Wartawan", 
            "On Duty/Off Duty\n\
            Ganti Seragam", "Pilih", "Batal");
        }
        case FACTION_AUTOMAX:
        {
            Dialog_Show(playerid, "AutomaxLocker", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Locker Automax", 
            "On Duty/Off Duty\n\
            Ganti Seragam", "Pilih", "Batal");
        }
        case FACTION_HANDOVER:
        {
            Dialog_Show(playerid, "HandoverLocker", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Locker Handover", 
            "On Duty/Off Duty\n\
            Ganti Seragam", "Pilih", "Batal");
        }
        case FACTION_SRIMERSING:
        {
            Dialog_Show(playerid, "SriMersingLocker", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Locker Karens Dinner", 
            "On Duty/Off Duty\n\
            Ganti Seragam", "Pilih", "Batal");
        }
        case FACTION_TEXAS:
        {
            Dialog_Show(playerid, "TexasChickenLocker", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Locker Karens Dinner", 
            "On Duty/Off Duty\n\
            Ganti Seragam\n\
            Baton Satpam", "Pilih", "Batal");
        }
    }
    return 1;
}

YCMD:fcraft(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] != FACTION_BENNYS && AccountData[playerid][pFaction] != FACTION_AUTOMAX && AccountData[playerid][pFaction] != FACTION_HANDOVER) return ShowTDN(playerid, NOTIFICATION_ERROR, "CMD ini hanya untuk faction berjenis bengkel!");

    if(!IsPlayerNearFCraft(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan titik crafting faction anda!");

    static string[555];
    format(string, sizeof(string), "Katalog\tAlat & Bahan\n\
    Part Mesin\tKomponen: %d/180 | Tembaga: %d/3 | Besi: %d/5 | Plastik: %d/3 | Minyak: %d/5\n\
    "GRAY"Part Body\t"GRAY"Komponen: %d/180 | Tembaga: %d/3 | Besi: %d/5 | Plastik: %d/5 | Minyak: %d/3\n\
    Ban Baru\tKomponen: %d/180 | Tembaga: %d/3 | Besi: %d/5 | Linggis: %d/2 | Plastik: %d/5\n\
    "GRAY"Air Brush\t"GRAY"Komponen: %d/180 | Pilox: %d/1 | Botol: %d/10 | Emas: %d/2\n\
    Toolkit\tKomponen: %d/180 | Tembaga: %d/5 | Besi: %d/10 | Plastik: %d/5 | Minyak: %d/10", 
    Inventory_Count(playerid, "Komponen"), Inventory_Count(playerid, "Tembaga"), Inventory_Count(playerid, "Besi"), Inventory_Count(playerid, "Plastik"), Inventory_Count(playerid, "Minyak"),
    Inventory_Count(playerid, "Komponen"), Inventory_Count(playerid, "Tembaga"), Inventory_Count(playerid, "Besi"), Inventory_Count(playerid, "Plastik"), Inventory_Count(playerid, "Minyak"),
    Inventory_Count(playerid, "Komponen"), Inventory_Count(playerid, "Tembaga"), Inventory_Count(playerid, "Besi"), Inventory_Count(playerid, "Linggis"), Inventory_Count(playerid, "Plastik"),
    Inventory_Count(playerid, "Komponen"), Inventory_Count(playerid, "Pilox"), Inventory_Count(playerid, "Botol"), Inventory_Count(playerid, "Emas"),
    Inventory_Count(playerid, "Komponen"), Inventory_Count(playerid, "Tembaga"), Inventory_Count(playerid, "Besi"), Inventory_Count(playerid, "Plastik"), Inventory_Count(playerid, "Minyak"));
    Dialog_Show(playerid, "FactionCrafting", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Crafting Fraksi", string, "Pilih", "Batal");
    return 1;
}

YCMD:fgarage(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] == FACTION_NONE) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari faction manapun!");
    if(!AccountData[playerid][pOnDuty]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus on duty terlebih dahulu!");
    if(!IsPlayerNearFGarage(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan garasi faction anda!");
    
    switch(AccountData[playerid][pFaction])
    {
        case FACTION_LSPD:
        {
            Dialog_Show(playerid, "PolisiGarage", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Garasi Kepolisian", 
            "Keluarkan Kendaraan\n\
            Simpan Kendaraan", "Pilih", "Batal");
        }
        case FACTION_LSFD:
        {
            Dialog_Show(playerid, "ParamedisGarage", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Garasi Paramedis", 
            "Keluarkan Kendaraan\n\
            Simpan Kendaraan", "Pilih", "Batal");
        }
        case FACTION_PUTRIDELI:
        {
            Dialog_Show(playerid, "PutrideliGarage", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Garasi Koki Sunda", 
            "Keluarkan Kendaraan\n\
            Simpan Kendaraan", "Pilih", "Batal");
        }
        case FACTION_SAGOV:
        {
            Dialog_Show(playerid, "PemerintahGarage", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Garasi Pemerintah", 
            "Keluarkan Kendaraan\n\
            Simpan Kendaraan", "Pilih", "Batal");
        }
        case FACTION_BENNYS:
        {
            Dialog_Show(playerid, "BennysGarage", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Garasi Bennys", 
            "Keluarkan Kendaraan\n\
            Simpan Kendaraan", "Pilih", "Batal");
        }
        case FACTION_UBER:
        {
            Dialog_Show(playerid, "UberGarage", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Garasi Uber", 
            "Keluarkan Kendaraan\n\
            Simpan Kendaraan", "Pilih", "Batal");
        }
        case FACTION_DINARBUCKS:
        {
            Dialog_Show(playerid, "DinarbucksGarage", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Garasi Dinarbucks", 
            "Keluarkan Kendaraan\n\
            Simpan Kendaraan", "Pilih", "Batal");
        }
        case FACTION_FOX11:
        {
            Dialog_Show(playerid, "PewartaGarage", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Garasi Wartawan", 
            "Keluarkan Kendaraan\n\
            Simpan Kendaraan", "Pilih", "Batal");
        }
        case FACTION_AUTOMAX:
        {
            Dialog_Show(playerid, "AutomaxGarage", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Garasi Automax", 
            "Keluarkan Kendaraan\n\
            Simpan Kendaraan", "Pilih", "Batal");
        }
        case FACTION_HANDOVER:
        {
            Dialog_Show(playerid, "HandoverGarage", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Garasi Handover", 
            "Keluarkan Kendaraan\n\
            Simpan Kendaraan", "Pilih", "Batal");
        }
        case FACTION_SRIMERSING:
        {
            Dialog_Show(playerid, "SriMersingGarage", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Garasi Karens Dinner", 
            "Keluarkan Kendaraan\n\
            Simpan Kendaraan", "Pilih", "Batal");
        }
        case FACTION_TEXAS:
        {
            Dialog_Show(playerid, "TexasChickenGarage", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Garasi Karens Dinner", 
            "Keluarkan Kendaraan\n\
            Simpan Kendaraan", "Pilih", "Batal");
        }
    }
    return 1;
}

YCMD:armoury(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");
    if(!AccountData[playerid][pOnDuty]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus on duty terlebih dahulu!");
    if(!IsPlayerNearArmoury(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan armoury manapun!");

    Dialog_Show(playerid, "PolisiArmoury", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Senjata", 
    "Restock Ammo\n\
    Refill Health & Regular Armour\n\
    Refill Health & Tactical Armour (SWAT)\n\
    Clear Weapons & Armour\n\
    Desert Eagle\n\
    Shotgun\n\
    MP5\n\
    M4\n\
    Combat Shotgun\n\
    Sniper Rifle", "Pilih", "Batal");
    return 1;
}

YCMD:vault(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] == FACTION_NONE) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari faction manapun!");
    if(!AccountData[playerid][pOnDuty]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus on duty terlebih dahulu!");
    if(!IsPlayerNearVault(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan brankas faction manapun!");

    switch(AccountData[playerid][pFaction])
    {
        case FACTION_LSPD:
        {
            Dialog_Show(playerid, "PolisiVault", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Kepolisian", 
            "Simpan Barang\n\
            Ambil Barang", "Pilih", "Kembali");
        }
        case FACTION_LSFD:
        {
            Dialog_Show(playerid, "ParamedisVault", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Paramedis", 
            "Simpan Barang\n\
            Ambil Barang", "Pilih", "Kembali");
        }
        case FACTION_PUTRIDELI:
        {
            Dialog_Show(playerid, "PutrideliVault", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Putri Deli", 
            "Simpan Barang\n\
            Ambil Barang", "Pilih", "Kembali");
        }
        case FACTION_SAGOV:
        {
            Dialog_Show(playerid, "PemerintahVault", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Pemerintah", 
            "Simpan Barang\n\
            Ambil Barang", "Pilih", "Kembali");
        }
        case FACTION_BENNYS:
        {
            Dialog_Show(playerid, "BennysVault", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Bennys", 
            "Simpan Barang\n\
            Ambil Barang", "Pilih", "Kembali");
        }
        case FACTION_UBER:
        {
            Dialog_Show(playerid, "UberVault", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Uber", 
            "Simpan Barang\n\
            Ambil Barang", "Pilih", "Kembali");
        }
        case FACTION_DINARBUCKS:
        {
            Dialog_Show(playerid, "DinarbucksVault", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Dinarbucks", 
            "Simpan Barang\n\
            Ambil Barang", "Pilih", "Kembali");
        }
        case FACTION_FOX11:
        {
            Dialog_Show(playerid, "PewartaVault", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Wartawan", 
            "Simpan Barang\n\
            Ambil Barang", "Pilih", "Kembali");
        }
        case FACTION_AUTOMAX:
        {
            Dialog_Show(playerid, "AutomaxVault", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Automax", 
            "Simpan Barang\n\
            Ambil Barang", "Pilih", "Kembali");
        }
        case FACTION_HANDOVER:
        {
            Dialog_Show(playerid, "HandoverVault", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Handover", 
            "Simpan Barang\n\
            Ambil Barang", "Pilih", "Kembali");
        }
        case FACTION_SRIMERSING:
        {
            Dialog_Show(playerid, "SriMersingVault", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Karens Dinner", 
            "Simpan Barang\n\
            Ambil Barang", "Pilih", "Kembali");
        }
        case FACTION_TEXAS:
        {
            Dialog_Show(playerid, "TexasChickenVault", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Karens Dinner", 
            "Simpan Barang\n\
            Ambil Barang", "Pilih", "Kembali");
        }
    }
    return 1;
}

YCMD:fmenu(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] == FACTION_NONE) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari faction manapun!");

    if(!AccountData[playerid][pOnDuty]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus on duty terlebih dahulu!");
    switch(AccountData[playerid][pFaction])
    {
        case FACTION_LSPD:
        {
            if(AccountData[playerid][pFactionRank] < 14) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank PANGKASAT untuk akses Bos Desk!");

            Dialog_Show(playerid, "PolisiBosdesk", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Menu Kepolisian", 
            "Invite\n\
            Manage Ranks\n\
            Kick\n\
            Cek Saldo\n\
            Deposit Balance\n\
            Withdraw Balance", "Pilih", "Batal");
        }
        case FACTION_LSFD:
        {
            if(AccountData[playerid][pFactionRank] < 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jabatan minimum Vice Director untuk akses faction menu!");

            Dialog_Show(playerid, "ParamedisBosdesk", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Menu Paramedis", 
            "Invite\n\
            Manage Ranks\n\
            Kick\n\
            Cek Saldo\n\
            Deposit Balance\n\
            Withdraw Balance", "Pilih", "Batal");
        }
        case FACTION_PUTRIDELI:
        {
            if(AccountData[playerid][pFactionRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jabatan minimum Store Supervisor untuk akses boss desk!");

            Dialog_Show(playerid, "PutrideliBosdesk", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Menu Putri Deli", 
            "Invite\n\
            Manage Ranks\n\
            Kick\n\
            Cek Saldo\n\
            Deposit Balance\n\
            Withdraw Balance", "Pilih", "Batal");
        }
        case FACTION_SAGOV:
        {
            if(AccountData[playerid][pFactionRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jabatan minimum Sekretaris untuk akses boss desk!");

            Dialog_Show(playerid, "PemerintahBosdesk", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Menu Pemerintah", 
            "Invite\n\
            Manage Ranks\n\
            Kick\n\
            Cek Saldo\n\
            Deposit Balance\n\
            Withdraw Balance", "Pilih", "Batal");
        }
        case FACTION_BENNYS:
        {
            if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jabatan minimum Vice Manager untuk akses boss desk!");

            Dialog_Show(playerid, "BennysBosdesk", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Menu Bennys", 
            "Invite\n\
            Manage Ranks\n\
            Kick\n\
            Cek Saldo\n\
            Deposit Balance\n\
            Withdraw Balance", "Pilih", "Batal");
        }
        case FACTION_UBER:
        {
            if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jabatan minimum Ast. Boss Uber untuk akses boss desk!");

            Dialog_Show(playerid, "UberBosdesk", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Menu Uber", 
            "Invite\n\
            Manage Ranks\n\
            Kick\n\
            Cek Saldo\n\
            Deposit Balance\n\
            Withdraw Balance", "Pilih", "Batal");
        }
        case FACTION_DINARBUCKS:
        {
            if(AccountData[playerid][pFactionRank] < 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jabatan minimum Supervisor untuk akses boss desk!");

            Dialog_Show(playerid, "DinarbucksBosDesk", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Menu Dinarbucks", 
            "Invite\n\
            Manage Ranks\n\
            Kick\n\
            Cek Saldo\n\
            Deposit Balance\n\
            Withdraw Balance", "Pilih", "Batal");
        }
        case FACTION_FOX11:
        {
            if(AccountData[playerid][pFactionRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jabatan minimum Chief Officer untuk akses boss desk!");

            Dialog_Show(playerid, "PewartaBosdesk", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Menu Wartawan", 
            "Invite\n\
            Manage Ranks\n\
            Kick\n\
            Cek Saldo\n\
            Deposit Balance\n\
            Withdraw Balance", "Pilih", "Batal");
        }
        case FACTION_AUTOMAX:
        {
            if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jabatan minimum Vice Manager untuk akses boss desk!");

            Dialog_Show(playerid, "AutomaxBosdesk", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Menu Automax", 
            "Invite\n\
            Manage Ranks\n\
            Kick\n\
            Cek Saldo\n\
            Deposit Balance\n\
            Withdraw Balance", "Pilih", "Batal");
        }
        case FACTION_HANDOVER:
        {
            if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jabatan minimum Vice Manager untuk akses boss desk!");

            Dialog_Show(playerid, "HandoverBosdesk", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Menu Handover", 
            "Invite\n\
            Manage Ranks\n\
            Kick\n\
            Cek Saldo\n\
            Deposit Balance\n\
            Withdraw Balance", "Pilih", "Batal");
        }
        case FACTION_SRIMERSING:
        {
            if(AccountData[playerid][pFactionRank] < 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jabatan minimum Supervisor untuk akses boss desk!");

            Dialog_Show(playerid, "SriMersingBosDesk", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Menu Karens Dinner", 
            "Invite\n\
            Manage Ranks\n\
            Kick\n\
            Cek Saldo\n\
            Deposit Balance\n\
            Withdraw Balance", "Pilih", "Batal");
        }
        case FACTION_TEXAS:
        {
            if(AccountData[playerid][pFactionRank] < 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jabatan minimum Supervisor untuk akses boss desk!");

            Dialog_Show(playerid, "TexasChickenBosDesk", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Texas Chicken Dinner", 
            "Invite\n\
            Manage Ranks\n\
            Kick\n\
            Cek Saldo\n\
            Deposit Balance\n\
            Withdraw Balance", "Pilih", "Batal");
        }
    }
    return 1;
}