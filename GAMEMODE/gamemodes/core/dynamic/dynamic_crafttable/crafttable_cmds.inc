YCMD:addcrafttable(playerid, params[], help)
{
    new ctid = Iter_Free(CraftTables), hjha[258], type, fmid;
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    if(sscanf(params, "dd", fmid, type)) return SUM(playerid, "/addcrafttable [family] [type] (1. Regular | 2. Admin | 3. Drugs | 4. Beers)");
    
    if(!Iter_Contains(Fams, fmid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Family ID tidak valid!");

    if(type < 0 || type > 4)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid type ID (1 - 4)");

    if(ctid <= -1)
	    return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah dynamic Craft Table telah mencapai batas maksimum!");

    GetPlayerPos(playerid, CrafttableData[ctid][Pos][0], CrafttableData[ctid][Pos][1], CrafttableData[ctid][Pos][2]);
    CrafttableData[ctid][Pos][3] = 0.0;
    CrafttableData[ctid][Pos][4] = 0.0;
    GetPlayerFacingAngle(playerid, CrafttableData[ctid][Pos][5]);

    CrafttableData[ctid][World] = GetPlayerVirtualWorld(playerid);
    CrafttableData[ctid][Interior] = GetPlayerInterior(playerid);

    CrafttableData[ctid][Label] = CreateDynamic3DTextLabel("Gunakan "YELLOW"'/usetable' "WHITE"untuk akses table ini", 0xffffffff, CrafttableData[ctid][Pos][0], CrafttableData[ctid][Pos][1], CrafttableData[ctid][Pos][2]+1.5, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, CrafttableData[ctid][World], CrafttableData[ctid][Interior], -1, 10.0, -1, 0);
    CrafttableData[ctid][Object] = CreateDynamicObject(937, CrafttableData[ctid][Pos][0], CrafttableData[ctid][Pos][1], CrafttableData[ctid][Pos][2], CrafttableData[ctid][Pos][3], CrafttableData[ctid][Pos][4], CrafttableData[ctid][Pos][5], CrafttableData[ctid][World], CrafttableData[ctid][Interior], -1, 100.00, 100.00);
    
    CrafttableData[ctid][Family] = fmid;
    CrafttableData[ctid][Type] = type;

    Iter_Add(CraftTables, ctid);

    mysql_format(g_SQL, hjha, sizeof(hjha), "INSERT INTO `crafttables` SET `ID`=%d, `X`='%f', `Y`='%f', `Z`='%f', `Rx`='%f', `Ry`='%f', `Rz`='%f', `World`=%d, `Interior`=%d, `Family` = %d, `Type` = %d",
        ctid, CrafttableData[ctid][Pos][0], CrafttableData[ctid][Pos][1], CrafttableData[ctid][Pos][2], CrafttableData[ctid][Pos][3], CrafttableData[ctid][Pos][4], CrafttableData[ctid][Pos][5], CrafttableData[ctid][World], CrafttableData[ctid][Interior], CrafttableData[ctid][Family], CrafttableData[ctid][Type]);
    mysql_pquery(g_SQL, hjha, "OnCraftTableAdded", "ii", playerid, ctid);
    return 1;
}

YCMD:removecrafttable(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

	new id, strgbg[128];
	if(sscanf(params, "i", id)) return SUM(playerid, "/removecrafttable [id]");
	if(!Iter_Contains(CraftTables, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Craft Table ID!");

    if(CraftTable_BeingEdited(id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "That Craft Table ID sedang diedit oleh admin lain!");

    if(DestroyDynamic3DTextLabel(CrafttableData[id][Label]))
        CrafttableData[id][Label] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    if(DestroyDynamicObject(CrafttableData[id][Object]))
        CrafttableData[id][Object] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;

    CrafttableData[id][Pos][0] = CrafttableData[id][Pos][1] = CrafttableData[id][Pos][2] = CrafttableData[id][Pos][3] = CrafttableData[id][Pos][4] = CrafttableData[id][Pos][5] = 0.0;
    CrafttableData[id][Interior] = CrafttableData[id][World] = 0;
    CrafttableData[id][Family] = -1;
    CrafttableData[id][Type] = 0;

    Iter_Remove(CraftTables, id);

    mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `crafttables` WHERE `id` = %d", id);
    mysql_pquery(g_SQL, strgbg);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s removed Craft Table with ID: %d.", AccountData[playerid][pAdminname], id);
	return 1;
}

YCMD:editcrafttable(playerid, params[], help)
{
	new id, type[24], stredit[128]; 

    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

	if(sscanf(params, "ds[24]S()[128]", id, type, stredit))
    {
        SUM(playerid, "/editcrafttable [id] [type] (pos, interior, virtual, type)");
        return 1;
    }

	if(!Iter_Contains(CraftTables, id)) 
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Craft Table ID!");

	if(!IsPlayerInRangeOfPoint(playerid, 30.0, CrafttableData[id][Pos][0], CrafttableData[id][Pos][1], CrafttableData[id][Pos][2])) 
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan Craft Table ID tersebut!");

	if(!strcmp(type, "pos", true))
    {
		if(AccountData[playerid][EditingCraftTableID] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang berada di dalam mode editing!");

        if(!IsPlayerInRangeOfPoint(playerid, 30.0, CrafttableData[id][Pos][0], CrafttableData[id][Pos][1], CrafttableData[id][Pos][2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan crafting table tersebut!");
        if(CraftTable_BeingEdited(id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Craft Table ID tersebut sedang diedit oleh admin lain!");

		AccountData[playerid][EditingCraftTableID] = id;
		EditDynamicObject(playerid, CrafttableData[id][Object]);

		SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s edited the position of Craft Table ID: %d.", AccountData[playerid][pAdminname], id);
	}
	else if(!strcmp(type, "interior", true))
    {
        GetPlayerPos(playerid, CrafttableData[id][Pos][0], CrafttableData[id][Pos][1], CrafttableData[id][Pos][2]);
		GetPlayerFacingAngle(playerid, CrafttableData[id][Pos][5]);

        CrafttableData[id][World] = GetPlayerVirtualWorld(playerid);
		CrafttableData[id][Interior] = GetPlayerInterior(playerid);
        Crafttable_Save(id);
		Crafttable_Refresh(id);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set the interior status of Craft Table ID: %d.", AccountData[playerid][pAdminname], id);
    }
	else if(!strcmp(type, "virtual", true))
    {
        new worldid;

        if(sscanf(stredit, "d", worldid))
            return SUM(playerid, "/editcrafttable [id] [virtual] [interior world]");

        CrafttableData[id][World] = worldid;

        Crafttable_Save(id);
		Crafttable_Refresh(id);
        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set the virtual world for Craft Table ID: %d to %d.", AccountData[playerid][pAdminname], id, worldid);
    }
	else if(!strcmp(type, "family", true))
    {
        new fams;

        if(sscanf(stredit, "d", fams))
            return SUM(playerid, "/editcrafttable [id] [family] [FID]");

        CrafttableData[id][Family] = fams;

        Crafttable_Save(id);
		Crafttable_Refresh(id);
        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set the family access for Craft Table ID: %d to FID %d.", AccountData[playerid][pAdminname], id, fams);
    }
	else if(!strcmp(type, "type", true))
    {
        new typse;

        if(sscanf(stredit, "d", typse))
            return SUM(playerid, "/editcrafttable [id] [type] (1. Regular | 2. Admin | 3. Drugs | 4. Beers)");

        CrafttableData[id][Type] = typse;

        Crafttable_Save(id);
		Crafttable_Refresh(id);
        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set the virtual world for Craft Table ID: %d to %d.", AccountData[playerid][pAdminname], id, typse);
    }
	return 1;
}

YCMD:usetable(playerid, params[], help)
{
    if(AccountData[playerid][pFamily] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota badside/family manapun!");
    if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");
       
    new id = Crafttable_Nearest(playerid);
    if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan craft table manapun!");

    if(AccountData[playerid][pFamily] != CrafttableData[id][Family]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Table ini bukan milik family anda!");
    if(AccountData[playerid][pFamilyRank] < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Aksis ditolak, minimal rank Wakil!");

    static string[1512];
    if(CrafttableData[id][Type] == 1)
    {
        AccountData[playerid][pTempValue] = 1;
        format(string, sizeof(string), "Name\tRequirements #1\tRequirements #2\n\
        Colt-45\tAlu:%d/30 | Kaca: %d/35 | Baja: %d/45 | Karet: %d/31\tPlastik: %d/34 | Material: %d/5 | Skin: %d/5\n\
        "GRAY"Desert Eagle\t"GRAY"Alu:%d/55 | Kaca: %d/45 | Baja: %d/60 | Karet: %d/42\t"GRAY"Plastik: %d/51 | Material: %d/5 | Skin: %d/5\n\
        Uzi\tAlu:%d/100 | Kaca: %d/50 | Baja: %d/105 | Karet: %d/75\tPlastik: %d/55 | Material: %d/5 | Skin: %d/5\n\
        "GRAY"Tec-9\t"GRAY"Alu:%d/105 | Kaca: %d/55 | Baja: %d/105 | Karet: %d/45\t"GRAY"Plastik: %d/40 | Material: %d/5 | Skin: %d/5\n\
        Shotgun\tAlu:%d/75 | Kaca: %d/45 | Baja: %d/90 | Karet: %d/30\tPlastik: %d/30 | Material: %d/5 | Skin: %d/5",
        Inventory_Count(playerid, "Alumunium"), Inventory_Count(playerid, "Kaca"), Inventory_Count(playerid, "Baja"), Inventory_Count(playerid, "Karet"), Inventory_Count(playerid, "Plastik"), Inventory_Count(playerid, "Material"), Inventory_Count(playerid, "Kulit"),
        Inventory_Count(playerid, "Alumunium"), Inventory_Count(playerid, "Kaca"), Inventory_Count(playerid, "Baja"), Inventory_Count(playerid, "Karet"), Inventory_Count(playerid, "Plastik"), Inventory_Count(playerid, "Material"), Inventory_Count(playerid, "Kulit"),
        Inventory_Count(playerid, "Alumunium"), Inventory_Count(playerid, "Kaca"), Inventory_Count(playerid, "Baja"), Inventory_Count(playerid, "Karet"), Inventory_Count(playerid, "Plastik"), Inventory_Count(playerid, "Material"), Inventory_Count(playerid, "Kulit"),
        Inventory_Count(playerid, "Alumunium"), Inventory_Count(playerid, "Kaca"), Inventory_Count(playerid, "Baja"), Inventory_Count(playerid, "Karet"), Inventory_Count(playerid, "Plastik"), Inventory_Count(playerid, "Material"), Inventory_Count(playerid, "Kulit"),
        Inventory_Count(playerid, "Alumunium"), Inventory_Count(playerid, "Kaca"), Inventory_Count(playerid, "Baja"), Inventory_Count(playerid, "Karet"), Inventory_Count(playerid, "Plastik"), Inventory_Count(playerid, "Material"), Inventory_Count(playerid, "Kulit"));
    }
    else if(CrafttableData[id][Type] == 2) //admin
    {
        AccountData[playerid][pTempValue] = 1;
        format(string, sizeof(string), "Name\tRequirements #1\tRequirements #2\n\
        Colt-45\tAlu:%d/30 | Kaca: %d/35 | Baja: %d/45 | Karet: %d/31\tPlastik: %d/34 | Material: %d/5 | Skin: %d/5\n\
        "GRAY"Desert Eagle\t"GRAY"Alu:%d/55 | Kaca: %d/45 | Baja: %d/60 | Karet: %d/42\t"GRAY"Plastik: %d/51 | Material: %d/5 | Skin: %d/5\n\
        Uzi\tAlu:%d/100 | Kaca: %d/50 | Baja: %d/105 | Karet: %d/75\tPlastik: %d/55 | Material: %d/5 | Skin: %d/5\n\
        "GRAY"Tec-9\t"GRAY"Alu:%d/105 | Kaca: %d/55 | Baja: %d/105 | Karet: %d/45\t"GRAY"Plastik: %d/40 | Material: %d/5 | Skin: %d/5\n\
        Shotgun\tAlu:%d/75 | Kaca: %d/45 | Baja: %d/90 | Karet: %d/30\tPlastik: %d/30 | Material: %d/5 | Skin: %d/5\n\
        "GRAY"AK-47\t"GRAY"Alu:%d/135 | Kaca: %d/75 | Baja: %d/145 | Karet: %d/75\t"GRAY"Plastik: %d/50 | Material: %d/5 | Skin: %d/5",
        Inventory_Count(playerid, "Alumunium"), Inventory_Count(playerid, "Kaca"), Inventory_Count(playerid, "Baja"), Inventory_Count(playerid, "Karet"), Inventory_Count(playerid, "Plastik"), Inventory_Count(playerid, "Material"), Inventory_Count(playerid, "Kulit"),
        Inventory_Count(playerid, "Alumunium"), Inventory_Count(playerid, "Kaca"), Inventory_Count(playerid, "Baja"), Inventory_Count(playerid, "Karet"), Inventory_Count(playerid, "Plastik"), Inventory_Count(playerid, "Material"), Inventory_Count(playerid, "Kulit"),
        Inventory_Count(playerid, "Alumunium"), Inventory_Count(playerid, "Kaca"), Inventory_Count(playerid, "Baja"), Inventory_Count(playerid, "Karet"), Inventory_Count(playerid, "Plastik"), Inventory_Count(playerid, "Material"), Inventory_Count(playerid, "Kulit"),
        Inventory_Count(playerid, "Alumunium"), Inventory_Count(playerid, "Kaca"), Inventory_Count(playerid, "Baja"), Inventory_Count(playerid, "Karet"), Inventory_Count(playerid, "Plastik"), Inventory_Count(playerid, "Material"), Inventory_Count(playerid, "Kulit"),
        Inventory_Count(playerid, "Alumunium"), Inventory_Count(playerid, "Kaca"), Inventory_Count(playerid, "Baja"), Inventory_Count(playerid, "Karet"), Inventory_Count(playerid, "Plastik"), Inventory_Count(playerid, "Material"), Inventory_Count(playerid, "Kulit"),
        Inventory_Count(playerid, "Alumunium"), Inventory_Count(playerid, "Kaca"), Inventory_Count(playerid, "Baja"), Inventory_Count(playerid, "Karet"), Inventory_Count(playerid, "Plastik"), Inventory_Count(playerid, "Material"), Inventory_Count(playerid, "Kulit"));
    }
    else if(CrafttableData[id][Type] == 3) //drugs
    {
        AccountData[playerid][pTempValue] = 2;
        format(string, sizeof(string), "Name\tRequirements #1\tRequirements #2\n\
        Sabu\tJerigen:%d/1 | Sabu Kristal: %d/2\n\
        "GRAY"Marijuana\t"GRAY"Daun Ganja:%d/3 | Plastik: %d/2\n\
        Sinte\tMarijuana:%d/2 | Kertas: %d/1\n\
        "GRAY"Heroin\t"GRAY"Sabu:%d/2 | Kertas: %d/1\t"GRAY"Jerigen: %d/1",
        Inventory_Count(playerid, "Jerigen"), Inventory_Count(playerid, "Sabu Kristal"),
        Inventory_Count(playerid, "Daun Ganja"), Inventory_Count(playerid, "Plastik"),
        Inventory_Count(playerid, "Marijuana"), Inventory_Count(playerid, "Kertas"),
        Inventory_Count(playerid, "Sabu"), Inventory_Count(playerid, "Kertas"), Inventory_Count(playerid, "Jerigen"));
    }
    else if(CrafttableData[id][Type] == 4) //beers
    {
        AccountData[playerid][pTempValue] = 3;
        format(string, sizeof(string), "Name\tRequirements #1\tRequirements #2\n\
        Anggur Merah\tBotol:%d/2 | Water: %d/2\tGula: %d/2 | Micin: %d/2\n\
        "GRAY"Tuak\t"GRAY"Botol:%d/2 | Water: %d/2\t"GRAY"Gula: %d/2 | Micin: %d/2",
        Inventory_Count(playerid, "Botol"), Inventory_Count(playerid, "Water"), Inventory_Count(playerid, "Gula"), Inventory_Count(playerid, "Micin"),
        Inventory_Count(playerid, "Botol"), Inventory_Count(playerid, "Water"), Inventory_Count(playerid, "Gula"), Inventory_Count(playerid, "Micin"));
    }
    Dialog_Show(playerid, "CraftingTable", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Craft Table", 
    string, "Craft", "Batal");
    return 1;
}