#include <YSI_Coding\y_hooks>

#define MAX_FAMILIES 100

#define MAX_FAMS_ITEMS 1000

enum e_familia
{
    famID,
    famLeaderID,
    famLeaderName[32],
    famName[32],
    famMoney,
    famDirtyMoney,

    famVaultWorld,
    famVaultInt,
    Float:famVaultPos[3],
    famDeskWorld,
    famDeskInt,
    Float:famDeskPos[3],

    famGarageWorld,
    famGarageInt,
    Float:famGaragePos[3],
    famGarageSpWorld,
    famGarageSpInt,
    Float:famGarageSpPos[4],

    //not save
    STREAMER_TAG_3D_TEXT_LABEL:famVaultLabel,
    STREAMER_TAG_3D_TEXT_LABEL:famDeskLabel,

    STREAMER_TAG_OBJECT:famGarageObjid,
    STREAMER_TAG_PICKUP:famGaragePickup,
    STREAMER_TAG_3D_TEXT_LABEL:famGarageLabel
};
new FamilyData[MAX_FAMILIES][e_familia],
    Iterator:Fams<MAX_FAMILIES>;

enum e_badsidebrankas
{
    badsideBrankasID,
    badsideBrankasFMID,
    badsideBrankasTemp[32],
    badsideBrankasModel,
    badsideBrankasQuant,

    //not saved
    bool:badsideBrankasExists
};
new BadsideBrankas[MAX_FAMS_ITEMS][e_badsidebrankas];

CountPlayerVehiclePBG(playerid, fmid)
{
	new tmpcount;
	foreach(new id : PvtVehicles)
	{
		if(PlayerVehicle[id][pVehOwnerID] == AccountData[playerid][pID])
		{
			if(!Iter_Contains(Vehicle, PlayerVehicle[id][pVehPhysic]) && PlayerVehicle[id][pVehFamGarage] == fmid)
			{
				tmpcount++;
			}
		}
	}
	return tmpcount;
}

ReturnAnyVehiclePBG(playerid, slot, fmid)
{
	new tmpcount = -1;
	if(slot < 0 && slot > MAX_PRIVATE_VEHICLE - 1) return -1;
	foreach(new id : PvtVehicles)
	{
		if(PlayerVehicle[id][pVehOwnerID] == AccountData[playerid][pID])
		{
			if(PlayerVehicle[id][pVehFamGarage] == fmid && PlayerVehicle[id][pVehFamGarage] > -1)
			{
				tmpcount++;
				if(tmpcount == slot)
				{
					return id;
				}
			}
		}
	}
	return -1;
}

GetFamilyOwnerName(fmid)
{
    new fname[32];
    if(fmid != -1)
    {
        if(!isnull(FamilyData[fmid][famLeaderName]))
        {
            format(fname, sizeof(fname), "%s", FamilyData[fmid][famLeaderName]);
        }
        else
        {
            format(fname, sizeof(fname), "Tidak Ada");
        }
    }
    return fname;
}

GetFamilyName(fmid) //mencari dengan iterator
{
    new fname[32];
    if(fmid != -1)
    {
        if(!isnull(FamilyData[fmid][famName]))
        {
            format(fname, sizeof(fname), "%s", FamilyData[fmid][famName]);
        }
        else
        {
            format(fname, sizeof(fname), "Kosong");
        }
    }
    else
    {
        format(fname, sizeof(fname), "N/A");
    }
    return fname;
}

CountFamilyOnline(fmid)
{
    new jumlah, fnumber[128];
    if(fmid != -1)
    {
        foreach(new i : Player)
        {
            if(AccountData[i][pFamily] == fmid)
            {
                jumlah++;
            }
        }
        if(jumlah > 4)
        {
            format(fnumber, sizeof(fnumber), "4+");
        }
        else
        {
            format(fnumber, sizeof(fnumber), "%d", jumlah);
        }
    }
    return fnumber;
}

static const FamsRank[7][] = 
{
	"N/A", //0

    "Prospek", //1
    "Junior", //2
    "Senior", //3
    "Penasihat", //4
    "Wakil", //5
    "Ketua" //6
};

Show_FamsRankManage(playerid)
{
    new 
        string[1012],
        member_name[MAX_MEMBER_ROWS][64],
        member_pID[MAX_MEMBER_ROWS],
        member_rank[MAX_MEMBER_ROWS],
        member_lastlog[MAX_MEMBER_ROWS][30],
        curr_page = index_pagination[playerid],
        curr_index;

    curr_index = curr_page * MAX_MEMBER_ROWS;

    for(new i = 0; i < MAX_MEMBER_ROWS; i++) {
        member_pID[i] = 0;
    }

    new real_i = 0;
    
    new jajang[512];
    mysql_format(g_SQL, jajang, sizeof(jajang), "SELECT * FROM `player_characters` WHERE `Char_Family` = %d ORDER BY `Char_FamilyRank` DESC", AccountData[playerid][pFamily]);
    mysql_query(g_SQL, jajang);

    new rows = cache_num_rows(),
        count = 0;

    if(rows)
    {
        for(new i = curr_index; i < rows; i++) if(i <= rows)
        {
            if(real_i < sizeof(member_pID)) {

                cache_get_value_name(i, "Char_Name", member_name[real_i]);
                cache_get_value_name_int(i, "Char_FamilyRank", member_rank[real_i]);
                cache_get_value_name(i, "Char_LastLogin", member_lastlog[real_i]);
                cache_get_value_name_int(i, "pID", member_pID[real_i]); 
                real_i++;
            }
            else {
                break;
            }
        }

        strcat(string, "Nama\tRank\tLast Online\n");

        for(new i = 0; i < real_i; ++i) if(member_pID[i] != 0)
        {
            strcat(string, sprintf("%s\t%s\t%s\n", member_name[i], FamsRank[member_rank[i]], member_lastlog[i]));
            ListedMember[playerid][count++] = member_pID[i];
        }

        new 
            total_pages = (rows + MAX_MEMBER_ROWS - 1) / MAX_MEMBER_ROWS;

        new 
            max_page = total_pages - 1; 

        TempRows[playerid] = rows;

        if(curr_page > 0) {
            strcat(string, ""RED"<< Sebelumnya");
            strcat(string, "\n");
        }
        if(curr_page < max_page) {
            strcat(string, ""GREEN">> Selanjutnya"); 
            strcat(string, "\n");
        }

        Dialog_Show(playerid, "FamSetRank", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", string, "Pilih", "Batal");
    }
    else
    {
        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", "Anda tidak memiliki member di badside ini!", "Tutup", "");
    }
    return 1;
}

stock ShowBadsideKick(playerid) 
{
    new 
        string[1012],
        member_name[MAX_MEMBER_ROWS][64],
        member_pID[MAX_MEMBER_ROWS],
        member_rank[MAX_MEMBER_ROWS],
        member_lastlog[MAX_MEMBER_ROWS][30],
        curr_page = index_pagination[playerid],
        curr_index;

    curr_index = curr_page * MAX_MEMBER_ROWS;

    for(new i = 0; i < MAX_MEMBER_ROWS; i++) {
        member_pID[i] = 0;
    }

    new real_i = 0;
    new jajang[512];
    mysql_format(g_SQL, jajang, sizeof(jajang), "SELECT * FROM `player_characters` WHERE `Char_Family` = %d ORDER BY `Char_FamilyRank` DESC", AccountData[playerid][pFamily]);
    mysql_query(g_SQL, jajang);

    new rows = cache_num_rows(),
        count = 0;

    if(rows)
    {
        for(new i = curr_index; i < rows && real_i < MAX_MEMBER_ROWS; i++)
        {
            cache_get_value_name(i, "Char_Name", member_name[real_i]);
            cache_get_value_name_int(i, "Char_FamilyRank", member_rank[real_i]);
            cache_get_value_name(i, "Char_LastLogin", member_lastlog[real_i]);
            cache_get_value_name_int(i, "pID", member_pID[real_i]); 
            real_i++;
        }

        strcat(string, "Nama\tRank\tLast Online\n");

        for(new i = 0; i < real_i; ++i)
        {
            strcat(string, sprintf("%s\t%s\t%s\n", member_name[i], FamsRank[member_rank[i]], member_lastlog[i]));
            ListedMember[playerid][count++] = member_pID[i];
        }

        new total_pages = (rows + MAX_MEMBER_ROWS - 1) / MAX_MEMBER_ROWS;
        new max_page = total_pages - 1;

        if(curr_page > 0) {
            strcat(string, ""RED"<< Sebelumnya");
            strcat(string, "\n");
        }
        if(curr_page < max_page) {
            strcat(string, ""GREEN">> Selanjutnya");
            strcat(string, "\n");
        }

        Dialog_Show(playerid, "FamKickMember", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Kick Badside", string, "Pilih", "Batal");
    }
    else
    {
        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Kick Badside", "Anda tidak memiliki member di badside ini!", "Tutup", "");
    }
    return 1;
}

Badside_Save(fmid)
{
    new gjhs[558];
    mysql_format(g_SQL, gjhs, sizeof(gjhs), "UPDATE `families` SET `LeaderID`=%d, `LeaderName`='%e', `Name`='%e', `Money`=%d, `DirtyMoney`=%d, `VX` = '%f', `VY` = '%f', `VZ` = '%f', `VW` = %d, `VI` = %d, `DX` = '%f', `DY` = '%f', `DZ` = '%f', `DW` = %d, `DI` = %d, `GX` = %f, `GY` = %f, `GZ` = %f, `GW` = %d, `GI` = %d, `GSX` = %f, `GSY` = %f, `GSZ` = %f, `GSA` = %f, `GSW` = %d, `GSI` = %d WHERE `ID` = %d", FamilyData[fmid][famLeaderID], FamilyData[fmid][famLeaderName], FamilyData[fmid][famName], FamilyData[fmid][famMoney], 
    FamilyData[fmid][famDirtyMoney], FamilyData[fmid][famVaultPos][0], FamilyData[fmid][famVaultPos][1], FamilyData[fmid][famVaultPos][2], FamilyData[fmid][famVaultWorld], FamilyData[fmid][famVaultInt], FamilyData[fmid][famDeskPos][0], FamilyData[fmid][famDeskPos][1], FamilyData[fmid][famDeskPos][2], FamilyData[fmid][famDeskWorld], FamilyData[fmid][famDeskInt], FamilyData[fmid][famGaragePos][0], FamilyData[fmid][famGaragePos][1], FamilyData[fmid][famGaragePos][2], FamilyData[fmid][famGarageWorld], FamilyData[fmid][famGarageInt], 
    FamilyData[fmid][famGarageSpPos][0], FamilyData[fmid][famGarageSpPos][1], FamilyData[fmid][famGarageSpPos][2], FamilyData[fmid][famGarageSpPos][3], FamilyData[fmid][famGarageSpWorld], FamilyData[fmid][famGarageSpInt], fmid);
    mysql_pquery(g_SQL, gjhs);
    return 1;
}

Badside_Rebuild(fmid)
{
    if(fmid != -1)
    {
        if(DestroyDynamic3DTextLabel(FamilyData[fmid][famVaultLabel]))
            FamilyData[fmid][famVaultLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        FamilyData[fmid][famVaultLabel] = CreateDynamic3DTextLabel("[Y] "WHITE"untuk akses penyimpanan", Y_YELLOW, FamilyData[fmid][famVaultPos][0], FamilyData[fmid][famVaultPos][1], FamilyData[fmid][famVaultPos][2] + 0.35, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, FamilyData[fmid][famVaultWorld], FamilyData[fmid][famVaultInt], -1, 10.00, -1, 0);
    
        if(DestroyDynamic3DTextLabel(FamilyData[fmid][famDeskLabel]))
            FamilyData[fmid][famDeskLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        FamilyData[fmid][famDeskLabel] = CreateDynamic3DTextLabel("[Y] "WHITE"untuk akses bos desk", Y_YELLOW, FamilyData[fmid][famDeskPos][0], FamilyData[fmid][famDeskPos][1], FamilyData[fmid][famDeskPos][2] + 0.35, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, FamilyData[fmid][famDeskWorld], FamilyData[fmid][famDeskInt], -1, 10.00, -1, 0);
    
        if(DestroyDynamicObject(FamilyData[fmid][famGarageObjid]))
            FamilyData[fmid][famGarageObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
        FamilyData[fmid][famGarageObjid] = CreateDynamicObject(1316, FamilyData[fmid][famGaragePos][0], FamilyData[fmid][famGaragePos][1], FamilyData[fmid][famGaragePos][2] - 0.9, 0.0, 0.0, 0.0, FamilyData[fmid][famGarageWorld], FamilyData[fmid][famGarageInt], -1, 100.00, 100.00, -1);
        SetDynamicObjectMaterial(FamilyData[fmid][famGarageObjid], 0, 18646, "matcolours", "white", 0x99ff0091);

        if(DestroyDynamicPickup(FamilyData[fmid][famGaragePickup]))
            FamilyData[fmid][famGaragePickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;
        
        if(DestroyDynamic3DTextLabel(FamilyData[fmid][famGarageLabel]))
            FamilyData[fmid][famGarageLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        FamilyData[fmid][famGaragePickup] = CreateDynamicPickup(1313, 23, FamilyData[fmid][famGaragePos][0], FamilyData[fmid][famGaragePos][1], FamilyData[fmid][famGaragePos][2]-0.05, FamilyData[fmid][famGarageWorld], FamilyData[fmid][famGarageInt], -1, 30.00, -1, 0);
        
        static strrs[144];
        format(strrs, sizeof(strrs), "[ "WHITE"(Garasi Badside): "YELLOW"%s "GREEN"]", FamilyData[fmid][famName]);
        FamilyData[fmid][famGarageLabel] = CreateDynamic3DTextLabel(strrs, Y_GREEN, FamilyData[fmid][famGaragePos][0], FamilyData[fmid][famGaragePos][1], FamilyData[fmid][famGaragePos][2]+0.45, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, FamilyData[fmid][famGarageWorld], FamilyData[fmid][famGarageInt], -1, 10.00, -1, 0);
    }
    return 1;
}

Badside_ShowBrankas(playerid)
{
    new 
        curr_page = index_pagination[playerid],
        count = 0,
        string[1012],
        real_i = 0,
        fbrankas_exists[MAX_PAGINATION_PAGES],
        fbrankas_temp[MAX_PAGINATION_PAGES][32],
        fbrankas_model[MAX_PAGINATION_PAGES],
        fbrankas_quant[MAX_PAGINATION_PAGES],
        fbrankas_id[MAX_PAGINATION_PAGES],
        fbrankas_fid[MAX_PAGINATION_PAGES],
        curr_idx;

    curr_idx = MAX_PAGINATION_PAGES * curr_page;

    for(new i = 0; i < MAX_PAGINATION_PAGES; i++) 
    {
        fbrankas_exists[i] = false;
    }

    strcat(string, "Nama Item\tJumlah\n");
    for(new i = 0; i < MAX_FACTIONS_ITEMS; i++) 
    {
        if (BadsideBrankas[i][badsideBrankasExists] && BadsideBrankas[i][badsideBrankasFMID] == AccountData[playerid][pFamily])
        {
            if (real_i >= curr_idx && real_i < curr_idx + MAX_PAGINATION_PAGES)
            {
                fbrankas_exists[real_i - curr_idx] = true;
                fbrankas_id[real_i - curr_idx] = i;
                fbrankas_fid[real_i - curr_idx] = BadsideBrankas[i][badsideBrankasFMID];
                fbrankas_model[real_i - curr_idx] = BadsideBrankas[i][badsideBrankasModel];
                strcopy(fbrankas_temp[real_i - curr_idx], BadsideBrankas[i][badsideBrankasTemp], 32);
                fbrankas_quant[real_i - curr_idx] = BadsideBrankas[i][badsideBrankasQuant];
            }
            real_i++;
        }
    }

    for(new i = 0; i < MAX_PAGINATION_PAGES; i++) 
    {
        if(fbrankas_exists[i]) 
        {
            if (i % 2 == 0)
            {
                strcat(string, sprintf(""WHITE"%s\t"WHITE"%d\n", fbrankas_temp[i], fbrankas_quant[i]));
            }
            else
            {
                strcat(string, sprintf(""GRAY"%s\t"GRAY"%d\n", fbrankas_temp[i], fbrankas_quant[i]));
            }
            PlayerListitem[playerid][count++] = fbrankas_id[i];
        }
    }

    if(count == 0) 
	{
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "Lemari Badside", "Lemari penyimpanan ini kosong!", "Tutup", "");
    } 
	else 
	{
        new max_pages = (real_i + MAX_PAGINATION_PAGES - 1) / MAX_PAGINATION_PAGES;

        if (curr_page > 0) {
            strcat(string, ""RED"<< Sebelumnya\n");
        }
        if (curr_page < max_pages - 1) {
            strcat(string, ""GREEN">> Selanjutnya\n");
        }

        Dialog_Show(playerid, "BadsideVaultWithdraw", DIALOG_STYLE_TABLIST_HEADERS, sprintf("Lemari Badside: Page %d of %d", curr_page + 1, max_pages),
        string, "Pilih", "Batal");
    }
    return 1;
}

static bool:IsBadsideItemValid(slot)
{
    new bool:itemExists = false;
    for(new i = 0; i < sizeof(g_aInventoryItems); i++) 
    {
        // Kalau item-nya ada, ganti itemExists
        if(!strcmp(BadsideBrankas[slot][badsideBrankasTemp], g_aInventoryItems[i][e_InventoryItem], true)) {
            itemExists = true;
            break;
        }
 
        // Nah ini bakal nge-loop terus sampai ketemu si item atau gak sampai
        // size-nya abis. Kenapa? Karena kan si nama item gak selalu ada di
        // index yang lagi di-loop ini, bisa aja di index yang lain.
    }
 
    // Habis nge-loop seluruh index ternyata namanya bener-bener gak ada. Nah
    // di sini deh baru di-delete.
    if(!itemExists) 
    {
        BadsideBrankas[slot][badsideBrankasExists] = false;
        BadsideBrankas[slot][badsideBrankasModel] = 0;
        BadsideBrankas[slot][badsideBrankasQuant] = 0;
        BadsideBrankas[slot][badsideBrankasFMID] = -1;
 
        BadsideBrankas[slot][badsideBrankasTemp][0] = EOS;
 
        static invstr[555];
        mysql_format(g_SQL, invstr, sizeof(invstr), "DELETE FROM `badside_brankas` WHERE `ID`=%d", BadsideBrankas[slot][badsideBrankasID]);
        mysql_pquery(g_SQL, invstr);
    }
 
    return itemExists;
}

forward LoadBadsideBrankas();
public LoadBadsideBrankas()
{
    if(cache_num_rows() > 0)
    {
        new totalInvalidItems = 0;
        for(new x; x < cache_num_rows(); x++)
        {
            if(!BadsideBrankas[x][badsideBrankasExists])
            {
                BadsideBrankas[x][badsideBrankasExists] = true;
                cache_get_value_name_int(x, "ID", BadsideBrankas[x][badsideBrankasID]);
                cache_get_value_name_int(x, "FMID", BadsideBrankas[x][badsideBrankasFMID]);
                cache_get_value_name(x, "Item", BadsideBrankas[x][badsideBrankasTemp]);
                cache_get_value_name_int(x, "Model", BadsideBrankas[x][badsideBrankasModel]);
                cache_get_value_name_int(x, "Quantity", BadsideBrankas[x][badsideBrankasQuant]);

                if(!IsBadsideItemValid(x)) 
                {
                    totalInvalidItems++;
                }
            }
        }
    }
    return 1;
}

forward OnBadsideDeposit(playerid, id);
public OnBadsideDeposit(playerid, id)
{
    AccountData[playerid][pMenuShowed] = false;
    BadsideBrankas[id][badsideBrankasID] = cache_insert_id();
    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyimpan item tersebut.");
    return 1;
}

forward OnBadsideAdded(playerid, fmid);
public OnBadsideAdded(playerid, fmid)
{
    Badside_Save(fmid);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s membuat Family dengan ID: %d.", AccountData[playerid][pAdminname], fmid);
    return 1;
}

forward LoadFamilies();
public LoadFamilies()
{
    new rows = cache_num_rows();
    if(rows)
    {
        new fmid;
		for(new i; i < rows; i++)
		{
            cache_get_value_name_int(i, "ID", fmid);
            cache_get_value_name_int(i, "LeaderID", FamilyData[fmid][famLeaderID]);
            cache_get_value_name(i, "LeaderName", FamilyData[fmid][famLeaderName]);
            cache_get_value_name(i, "Name", FamilyData[fmid][famName]);
            cache_get_value_name_int(i, "Money", FamilyData[fmid][famMoney]);
            cache_get_value_name_int(i, "DirtyMoney", FamilyData[fmid][famDirtyMoney]);

            cache_get_value_name_int(i, "VW", FamilyData[fmid][famVaultWorld]);
            cache_get_value_name_int(i, "VI", FamilyData[fmid][famVaultInt]);
            cache_get_value_name_float(i, "VX", FamilyData[fmid][famVaultPos][0]);
            cache_get_value_name_float(i, "VY", FamilyData[fmid][famVaultPos][1]);
            cache_get_value_name_float(i, "VZ", FamilyData[fmid][famVaultPos][2]);

            cache_get_value_name_int(i, "DW", FamilyData[fmid][famDeskWorld]);
            cache_get_value_name_int(i, "DI", FamilyData[fmid][famDeskInt]);
            cache_get_value_name_float(i, "DX", FamilyData[fmid][famDeskPos][0]);
            cache_get_value_name_float(i, "DY", FamilyData[fmid][famDeskPos][1]);
            cache_get_value_name_float(i, "DZ", FamilyData[fmid][famDeskPos][2]);

            cache_get_value_name_int(i, "GW", FamilyData[fmid][famGarageWorld]);
            cache_get_value_name_int(i, "GI", FamilyData[fmid][famGarageInt]);
            cache_get_value_name_float(i, "GX", FamilyData[fmid][famGaragePos][0]);
            cache_get_value_name_float(i, "GY", FamilyData[fmid][famGaragePos][1]);
            cache_get_value_name_float(i, "GZ", FamilyData[fmid][famGaragePos][2]);

            cache_get_value_name_int(i, "GSW", FamilyData[fmid][famGarageSpWorld]);
            cache_get_value_name_int(i, "GSI", FamilyData[fmid][famGarageSpInt]);
            cache_get_value_name_float(i, "GSX", FamilyData[fmid][famGarageSpPos][0]);
            cache_get_value_name_float(i, "GSY", FamilyData[fmid][famGarageSpPos][1]);
            cache_get_value_name_float(i, "GSZ", FamilyData[fmid][famGarageSpPos][2]);
            cache_get_value_name_float(i, "GSA", FamilyData[fmid][famGarageSpPos][3]);

            Iter_Add(Fams, fmid);
            Badside_Rebuild(fmid);
        }
        printf("[Dynamic Families] Jumlah total Family yang dimuat: %d.", rows);
    }
    return 1;
}

forward SaveVehicleToFamily(playerid, carid, fmid);
public SaveVehicleToFamily(playerid, carid, fmid)
{
    if(!IsPlayerConnected(playerid)) return 1;
    if(!AccountData[playerid][pSpawned]) return 1;
    if(PlayerVehicle[carid][pVehPhysic] == INVALID_VEHICLE_ID || !Iter_Contains(Vehicle, PlayerVehicle[carid][pVehPhysic])) return 1;
    if(!Iter_Contains(Fams, fmid)) return 1;
    if(!IsValidDynamicObject(FamilyData[fmid][famGarageObjid])) return 1;

    PlayerVehicle[carid][pVehFamGarage] = fmid;
    SetVehicleNeonLights(PlayerVehicle[carid][pVehPhysic], false, PlayerVehicle[carid][pVehNeon], 0);
    DestroyVehicle(PlayerVehicle[carid][pVehPhysic]);
    PlayerVehicle[carid][pVehPhysic] = INVALID_VEHICLE_ID;

    new sqlsdwadkw[128];
    mysql_format(g_SQL, sqlsdwadkw, sizeof(sqlsdwadkw), "UPDATE `player_vehicles` SET `PVeh_Familied` = %d WHERE `id` = %d", PlayerVehicle[carid][pVehFamGarage], PlayerVehicle[carid][pVehID]);
    mysql_pquery(g_SQL, sqlsdwadkw);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_CTRL_BACK && AccountData[playerid][pFamily] > -1 && AccountData[playerid][pFamilyRank] > 1 && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(AccountData[playerid][pInEvent]) return 1;
        
        new count = 0, frmxt[522];
        foreach(new i : Player) if(i != playerid) if(IsPlayerNearPlayer(playerid, i, 2.5)) 
		{
			if (i % 2 == 0) 
            {
                format(frmxt, sizeof(frmxt), "%s"WHITE"Player ID - (%d)\n", frmxt, i);
            }
            else 
            {
                format(frmxt, sizeof(frmxt), "%s"GRAY"Player ID - (%d)\n", frmxt, i);
            }
			NearestUser[playerid][count++] = i;
		}

        if(count > 0) 
		{
            Dialog_Show(playerid, "FactionPanel", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Badside Panel", 
            frmxt, "Pilih", "Batal");
		}
    }
    else if(newkeys & KEY_YES && AccountData[playerid][pFamily] > -1 && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        new fmid = AccountData[playerid][pFamily];
        if(IsPlayerInRangeOfPoint(playerid, 1.0, FamilyData[fmid][famVaultPos][0], FamilyData[fmid][famVaultPos][1], FamilyData[fmid][famVaultPos][2]))
        {
            AccountData[playerid][pMenuShowed] = true;
            Dialog_Show(playerid, "BadsideVault", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Badside", 
            "Simpan Barang\n"GRAY"Ambil Barang", "Pilih", "Kembali");
        }

        if(IsPlayerInRangeOfPoint(playerid, 3.5, FamilyData[fmid][famGaragePos][0], FamilyData[fmid][famGaragePos][1], FamilyData[fmid][famGaragePos][2]))
        {
            if(FamilyData[fmid][famGaragePos][0] == 0.0 && FamilyData[fmid][famGaragePos][1] == 0.0 && FamilyData[fmid][famGaragePos][2] == 0.0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Garasi Family ini belum memiliki titik despawn!");
            if(FamilyData[fmid][famGarageSpPos][0] == 0.0 && FamilyData[fmid][famGarageSpPos][1] == 0.0 && FamilyData[fmid][famGarageSpPos][2] == 0.0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Garasi Family ini belum memiliki titik spawn kendaraan!");

            if(CountPlayerVehiclePBG(playerid, fmid) < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan yang tersimpan di garasi!");

            AccountData[playerid][pInGarkot] = fmid;
            new id, count = CountPlayerVehiclePBG(playerid, fmid), location[512], lstr[596];

            strcat(location,"No\tModel Kendaraan\tNomor Plat\n",sizeof(location));
            for(new itt; itt < count; itt++)
            {
                id = ReturnAnyVehiclePBG(playerid, itt, fmid);
                if(itt == count)
                {
                    format(lstr,sizeof(lstr), "%d\t%s\t%s\n", itt + 1, GetVehicleModelName(PlayerVehicle[id][pVehModelID]), PlayerVehicle[id][pVehPlate]);
                }
                else format(lstr,sizeof(lstr), "%d\t%s\t%s\n", itt + 1, GetVehicleModelName(PlayerVehicle[id][pVehModelID]), PlayerVehicle[id][pVehPlate]);
                strcat(location,lstr,sizeof(location));
            }
            Dialog_Show(playerid, "BadsideGarage", DIALOG_STYLE_TABLIST_HEADERS,"Garasi Badside - Ambil Kendaraan", location, "Pilih","Batal");
            HideNotifBox(playerid);
        }

        if(AccountData[playerid][pFamilyRank] > 2)
        {
            if(IsPlayerInRangeOfPoint(playerid, 1.0, FamilyData[fmid][famDeskPos][0], FamilyData[fmid][famDeskPos][1], FamilyData[fmid][famDeskPos][2]))
            {
                Dialog_Show(playerid, "BadsideBosdesk", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Bos Desk", 
                "Invite\n\
                "GRAY"Kelola Jabatan\n\
                Kick\n\
                "GRAY"Saldo Finansial\n\
                Deposit Saldo\n\
                "GRAY"Withdraw Saldo\n\
                Deposit Dirty Money\n\
                "GRAY"Withdraw Dirty Money", "Pilih", "Batal");
            }
        }
    }
    else if(newkeys & KEY_CROUCH && AccountData[playerid][pFamily] > -1 && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
    {
        new fmid = AccountData[playerid][pFamily];
        if(IsPlayerInRangeOfPoint(playerid, 3.5, FamilyData[fmid][famGaragePos][0], FamilyData[fmid][famGaragePos][1], FamilyData[fmid][famGaragePos][2]))
        {
            if(FamilyData[fmid][famGaragePos][0] == 0.0 && FamilyData[fmid][famGaragePos][1] == 0.0 && FamilyData[fmid][famGaragePos][2] == 0.0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Garasi Family ini belum memiliki titik despawn!");
            if(FamilyData[fmid][famGarageSpPos][0] == 0.0 && FamilyData[fmid][famGarageSpPos][1] == 0.0 && FamilyData[fmid][famGarageSpPos][2] == 0.0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Garasi Family ini belum memiliki titik spawn kendaraan!");

            new carid = -1,
                foundnearby = 0;

            if((carid = GetPlayerVehicleIDInside(playerid)) != -1)
            {
                if(PlayerVehicle[carid][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
                if(PlayerVehicle[carid][pVehRental] > -1 || PlayerVehicle[carid][pVehRentTime] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menyimpan kendaraan rental!");
                Vehicle_GetStatus(carid);
                HideNotifBox(playerid);
                
                foundnearby++;
                RemovePlayerFromVehicle(playerid);
                SetTimerEx("SaveVehicleToFamily", 2500, false, "idd", playerid, carid, fmid);
            }

            if(!foundnearby)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini bukan jenis kendaraan pribadi!");
        }
    }
    return 1;
}

Dialog:BadsidePanel(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    new targetid = NearestSingle[playerid];
    if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if(!IsPlayerNearPlayer(playerid, targetid, 3.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak dekat dengan anda!");
    if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Karakter anda terluka parah saat ini!");
    
    switch(listitem)
    {
        case 0: //Geledah
        {
            ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, false, false, false, false, 0, true);

            new str[1218], count;
            format(str, sizeof(str), "Nama Item\tJumlah\n\
            Uang\t"DARKGREEN"$%s\n", FormatMoney(AccountData[targetid][pMoney]));
            for(new index; index < MAX_INVENTORY; index++)
            {
                if(InventoryData[targetid][index][invExists])
                {
                    for(new i; i < sizeof(g_aInventoryItems); i ++) if (!strcmp(g_aInventoryItems[i][e_InventoryItem], InventoryData[targetid][index][invItem], true))
                    {
                        if (i % 2 == 0) {
                            format(str, sizeof(str), "%s"WHITE"%s\t"WHITE"%d\n", str, InventoryData[targetid][index][invItem], InventoryData[targetid][index][invQuantity]);
                        }
                        else {
                            format(str, sizeof(str), "%s"GRAY"%s\t"GRAY"%d\n", str, InventoryData[targetid][index][invItem], InventoryData[targetid][index][invQuantity]);
                        }
                        PlayerListitem[playerid][count++] = index;
                    }
                }
            }

            if(count == 0)
            {
                Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Geledah", 
                "Pemain tersebut tidak memiliki item apapun!", "Tutup", "");
            }
            else
            {
                Dialog_Show(playerid, "BadsideConsficating", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Geledah", str, "Pilih", "Batal");
            }
        }
        case 1: //Borgol
        {
            AccountData[targetid][pTied] = true;
            GameTextForPlayer(targetid, "~r~Terikat", 3500, 3);
            SetPlayerSpecialAction(targetid, SPECIAL_ACTION_CUFFED);
            ShowTDN(targetid, NOTIFICATION_INFO, "Anda telah terikat!");
            NearestSingle[playerid] = INVALID_PLAYER_ID;
        }
        case 2: //Buka Borgol
        {
            AccountData[targetid][pTied] = false;
            GameTextForPlayer(targetid, "~g~Ikatan Dilepas", 3500, 3);
            SetPlayerSpecialAction(targetid, SPECIAL_ACTION_NONE);
            ShowTDN(targetid, NOTIFICATION_INFO, "Ikatan anda telah dilepas!");
            NearestSingle[playerid] = INVALID_PLAYER_ID;
        }
        case 3: //Seret
        {
            if(AccountData[playerid][DraggingID] != INVALID_PLAYER_ID)
            {
                AccountData[playerid][DraggingID] = INVALID_PLAYER_ID;
                if(IsPlayerConnected(AccountData[playerid][DraggingID]))
                {
                    AccountData[AccountData[playerid][DraggingID]][pGetDraggedBy] = INVALID_PLAYER_ID;
                }
                TogglePlayerControllable(targetid, true);
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah berhenti menggendong seseorang.");
                return 1;
            }

            foreach(new i: Player)
            {
                if(AccountData[i][DraggingID] == playerid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menyeret seseorang yang sedang menyeret orang lain!");
            }

            AccountData[playerid][DraggingID] = targetid;
            AccountData[targetid][pGetDraggedBy] = playerid;
            TogglePlayerControllable(targetid, false);
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menggendong seseorang.");
            NearestSingle[playerid] = INVALID_PLAYER_ID;
        }
        case 4: //Masukkan Mobil
        {
            new vehid = GetNearestVehicleToPlayer(playerid, 4.0, false);
            if(vehid != INVALID_VEHICLE_ID)
            {
                if(GetEmptySeat(vehid) == INVALID_SEAT_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kursi kosong di belakang!");
                PutPlayerInVehicleEx(targetid, vehid, GetEmptySeat(vehid));
                TogglePlayerControllable(targetid, false);
                AccountData[targetid][pDetained] = true;
                ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasukkan Pemain tersebut secara paksa.");
            }
            NearestSingle[playerid] = INVALID_PLAYER_ID;
        }
        case 5: //Keluarkan Paksa
        {
            if(!AccountData[targetid][pDetained]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak sedang di-detain!");
            TogglePlayerControllable(targetid, true);
            RemovePlayerFromVehicle(targetid);
            AccountData[targetid][pDetained] = false;
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menendang Pemain tersebut dari kendaraan.");
            NearestSingle[playerid] = INVALID_PLAYER_ID;
        }
        case 6: //cek senjata
        {
            new lstr[555], weaponid, ammo, count;
            format(lstr, sizeof(lstr), "Slot #ID\tNama\tPeluru\n");
            for(new i; i < 13; i ++)
            {
                GetPlayerWeaponData(targetid, i, weaponid, ammo);

                if(weaponid > 0)
                {
                    count++;
                    format(lstr, sizeof(lstr), "%s"RED"%d\t"RED"%s\t"RED"%d\n", lstr, i, ReturnWeaponName(weaponid), ammo);
                }
            }
            if(count > 0)
            {
                Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Senjata", lstr,"Tutup","");
            }
            else
            {
                Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Senjata", "Pemain tersebut tidak memiliki senjata!","Tutup","");
            }
        }
    }
    return 1;
}
Dialog:BadsideConsficatingMoney(playerid, response, listitem, inputtext[])
{
    if (!response) return 1;
    if (isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");
    if (!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya dapat dimasukkan angka!");

    new targetid = NearestSingle[playerid];
    if (!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if (!IsPlayerNearPlayer(playerid, targetid, 3.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak dekat dengan anda!");
    if (AccountData[targetid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sedang melakukan sesuatu!");
    
    if(strval(inputtext) < 1) return Dialog_Show(playerid, "BadsideConsficatingMoney", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Ambil Uang",
    "Error: Jumlah tidak valid, anda tidak dapat mengambil kurang dari $1!\n\
    Mohon masukkan berapa jumlah yang ingin anda ambil:", "Ambil", "Batal");

    if(AccountData[targetid][pMoney] < RoundNegativeToPositive(strval(inputtext))) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak memiliki cukup uang!");

    TakePlayerMoneyEx(targetid, strval(inputtext));
    GivePlayerMoneyEx(playerid, strval(inputtext));

    SIM(targetid, "Uang $%s milik anda telah diambil oleh "RED"%s [%s] (ID: %d).", FormatMoney(strval(inputtext)), AccountData[playerid][pName], AccountData[playerid][pUCP], playerid);
    ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil mengambil $%s dari Pemain tersebut.", FormatMoney(strval(inputtext))));
    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, false, false, false, false, 0, true);
    SendRPMeAboveHead(playerid, sprintf("Mengambil $%s dari orang di depannya.", FormatMoney(strval(inputtext))));

    NearestSingle[playerid] = INVALID_PLAYER_ID;
    return 1;
}

Dialog:BadsideConsficating(playerid, response, listitem, inputtext[])
{
    if (!response) return 1;
    new targetid = NearestSingle[playerid];
    if (!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if (!IsPlayerNearPlayer(playerid, targetid, 3.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak dekat dengan anda!");
    if (AccountData[targetid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sedang melakukan sesuatu!");
    if (AccountData[targetid][pMenuShowed]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sedang ingin menyimpan/mengambil sesuatu!");
    
    if (listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item apapun!");

    if (listitem == 0)
    {
        new jhj[258];
        format(jhj, sizeof(jhj), ""WHITE"Pemain ini memiliki "GREEN"$%s "WHITE"yang sedang dibawanya.\n\
        "YELLOW"Berapa banyak jumlah yang ingin anda ambil?", FormatMoney(AccountData[targetid][pMoney]));
        Dialog_Show(playerid, "BadsideConsficatingMoney", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Money", jhj, "Ambil", "Batal");
    }
    else
    {
        if(!strcmp(InventoryData[targetid][PlayerListitem[playerid][listitem - 1]][invQuantity], "Changename Card")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat mengambil changename card!");

        new Float:countingtotalweight;
        countingtotalweight = GetTotalWeightFloat(playerid) + float(InventoryData[targetid][PlayerListitem[playerid][listitem - 1]][invQuantity] * GetItemWeight(InventoryData[targetid][PlayerListitem[playerid][listitem - 1]][invItem]))/1000;
        if (countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

        if(!strcmp(InventoryData[targetid][PlayerListitem[playerid][listitem - 1]][invQuantity], "Hunt Ammo"))
        {
            if(IsPlayerHunting[targetid])
            {
                ResetWeapon(targetid, 34);
                if(PlayerHasItem(targetid, "Hunt Ammo"))
                {
                    GivePlayerWeaponEx(targetid, 34, Inventory_Count(targetid, "Hunt Ammo"), WEAPON_TYPE_PLAYER);
                }
            }
        }

        SIM(targetid, "Seluruh %s milik anda telah diambil oleh "RED" %s [%s] (ID: %d).", InventoryData[targetid][PlayerListitem[playerid][listitem - 1]][invItem], AccountData[playerid][pName], AccountData[playerid][pUCP], playerid);
        ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil mengambil semua %s.", InventoryData[targetid][PlayerListitem[playerid][listitem - 1]][invItem]));
        ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, false, false, false, false, 0, true);
        SendRPMeAboveHead(playerid, sprintf("Menyita seluruh %s dari orang di depannya.", InventoryData[targetid][PlayerListitem[playerid][listitem - 1]][invItem]));
        
        Inventory_Add(playerid, InventoryData[targetid][PlayerListitem[playerid][listitem - 1]][invItem], InventoryData[targetid][PlayerListitem[playerid][listitem - 1]][invModel], InventoryData[targetid][PlayerListitem[playerid][listitem - 1]][invQuantity]);
        Inventory_Remove(targetid, InventoryData[targetid][PlayerListitem[playerid][listitem - 1]][invItem], InventoryData[targetid][PlayerListitem[playerid][listitem - 1]][invQuantity]);
        
        Inventory_Close(targetid);
        
        NearestSingle[playerid] = INVALID_PLAYER_ID;
    }
    return 1;
}

Dialog:BadsideVault(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        AccountData[playerid][pMenuShowed] = false;
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
        return 1;
    }

    switch(listitem)
    {
        case 0: //deposit
        {
            new str[1218], count;
            format(str, sizeof(str), "Nama Item\tJumlah\n");
            for(new index; index < MAX_INVENTORY; index++)
            {
                if(InventoryData[playerid][index][invExists])
                {
                    for(new i; i < sizeof(g_aInventoryItems); i ++) if (!strcmp(g_aInventoryItems[i][e_InventoryItem], InventoryData[playerid][index][invItem], true))
                    {
                        format(str, sizeof(str), "%s%s\t%d\n", str, InventoryData[playerid][index][invItem], InventoryData[playerid][index][invQuantity]);
                        PlayerListitem[playerid][count++] = index;
                    }
                }
            }

            if(count == 0)
            {
                Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Badside", 
                "Anda tidak memiliki barang yang dapat disimpan!", "Tutup", "");
            }
            else
            {
                Dialog_Show(playerid, "BadsideVaultDeposit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Badside", str, "Pilih", "Batal");
            }
        }
        case 1: //withdraw
        {
            if(AccountData[playerid][pFamilyRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan petinggi badside/family!");
            index_pagination[playerid] = 0;
            Badside_ShowBrankas(playerid);
        }
    }
    return 1;
}

Dialog:BadsideVaultDeposit(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        AccountData[playerid][pMenuShowed] = false;
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
        return 1;
    }

    if(listitem == -1) 
    {
        AccountData[playerid][pMenuShowed] = false;
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item apapun!");
    }

    AccountData[playerid][pTempValue] = listitem;

    if(!strcmp(InventoryData[playerid][PlayerListitem[playerid][listitem]][invItem], "Changename Card")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menyimpan Changename Card ke penyimpanan manapun!");
	if(!strcmp(InventoryData[playerid][PlayerListitem[playerid][listitem]][invItem], "Hunt Ammo"))
	{
		if(IsPlayerHunting[playerid])
		{
			ResetWeapon(playerid, 34);
			if(PlayerHasItem(playerid, "Hunt Ammo"))
			{
				GivePlayerWeaponEx(playerid, 34, Inventory_Count(playerid, "Hunt Ammo"), WEAPON_TYPE_PLAYER);
			}
		}
	}
    
    new shstr[528];
    format(shstr, sizeof(shstr), ""WHITE"Anda akan menyimpan item:\nNama: "CYAN"%s\n"WHITE"Jumlah di tas: "YELLOW"%d\n"WHITE"Mohon masukkan jumlah yang ingin disimpan:", InventoryData[playerid][PlayerListitem[playerid][listitem]][invItem], InventoryData[playerid][PlayerListitem[playerid][listitem]][invQuantity]);
    Dialog_Show(playerid, "BadsideVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Badside", 
    shstr, "Input", "Batal");
    return 1;
}

Dialog:BadsideVaultIn(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        AccountData[playerid][pMenuShowed] = false;
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
        return 1;
    }

    if(AccountData[playerid][pTempValue] == -1)
    {
        AccountData[playerid][pMenuShowed] = false;
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item apapun!");
        return 1;
    }

    new shstr[512], id = AccountData[playerid][pTempValue];
    if(isnull(inputtext)) 
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan menyimpan item:\nNama: "CYAN"%s\n"WHITE"Jumlah di tas: "YELLOW"%d\n"WHITE"Error: Tidak dapat dikosongkan!\nPlease enter the quantity you want to store:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
        Dialog_Show(playerid, "BadsideVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Badside", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(!IsNumericEx(inputtext))
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan menyimpan item:\nNama: "CYAN"%s\n"WHITE"Jumlah di tas: "YELLOW"%d\n"WHITE"Error: Please enter only numbers!\nPlease enter the quantity you want to store:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
        Dialog_Show(playerid, "BadsideVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Badside", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(strval(inputtext) < 1 || strval(inputtext) > InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity])
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan menyimpan item:\nNama: "CYAN"%s\n"WHITE"Jumlah di tas: "YELLOW"%d\n"WHITE"Error: Jumlah tidak valid!\nPlease enter the quantity you want to store:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
        Dialog_Show(playerid, "BadsideVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Badside", 
        shstr, "Input", "Batal");
        return 1;
    }

    new quantity = strval(inputtext);

    new invstr[1028];
    mysql_format(g_SQL, shstr, sizeof(shstr), "SELECT * FROM `badside_brankas` WHERE `FMID` = %d AND `Item` = '%e'", AccountData[playerid][pFamily], InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
    mysql_query(g_SQL, shstr);

    new rows = cache_num_rows();
    if(rows > 0)
    {
        mysql_format(g_SQL, invstr, sizeof(invstr), "UPDATE `badside_brankas` SET `Quantity` = `Quantity` + %d WHERE `FMID` = %d AND `Item` = '%e'", quantity, AccountData[playerid][pFamily], InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
        mysql_pquery(g_SQL, invstr);

        ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyimpan item tersebut.");

        for(new x; x < MAX_FAMS_ITEMS; ++x)
        {
            if(BadsideBrankas[x][badsideBrankasExists] && BadsideBrankas[x][badsideBrankasFMID] == AccountData[playerid][pFamily] && !strcmp(BadsideBrankas[x][badsideBrankasTemp], InventoryData[playerid][PlayerListitem[playerid][id]][invItem], true))
            {
                BadsideBrankas[x][badsideBrankasQuant] += quantity;
            }
        }
    }
    else
    {
        for(new x; x < MAX_FAMS_ITEMS; ++x)
        {
            if(!BadsideBrankas[x][badsideBrankasExists]) 
            {
                BadsideBrankas[x][badsideBrankasExists] = true;
                BadsideBrankas[x][badsideBrankasFMID] = AccountData[playerid][pFamily];
                strcopy(BadsideBrankas[x][badsideBrankasTemp], InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
                BadsideBrankas[x][badsideBrankasModel] = InventoryData[playerid][PlayerListitem[playerid][id]][invModel];
                BadsideBrankas[x][badsideBrankasQuant] = quantity;

                mysql_format(g_SQL, invstr, sizeof(invstr), "INSERT INTO `badside_brankas` SET `FMID` = %d, `Item`='%e', `Model`=%d, `Quantity`=%d", AccountData[playerid][pFamily], InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invModel], quantity);
                mysql_pquery(g_SQL, invstr, "OnBadsideDeposit", "id", playerid, x);

                break;
            }
        }
    }
    ShowItemBox(playerid, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], sprintf("Removed %dx", quantity), InventoryData[playerid][PlayerListitem[playerid][id]][invModel], 5);
    Inventory_Remove(playerid, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], quantity);
    return 1;
}

Dialog:BadsideVaultWithdraw(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        AccountData[playerid][pMenuShowed] = false;
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
        return 1;
    }

    if(listitem == -1) 
    {
        AccountData[playerid][pMenuShowed] = false;
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item apapun!");
    }

    if(!strcmp(inputtext, ">> Selanjutnya", true)) 
    {
        index_pagination[playerid]++;

        new
            max_contact_page = MAX_FACTIONS_ITEMS / MAX_PAGINATION_PAGES;

        if(index_pagination[playerid] >= max_contact_page) 
        {
            index_pagination[playerid] = max_contact_page;
        }
        Badside_ShowBrankas(playerid);
    }
    else if(!strcmp(inputtext, "<< Sebelumnya", true)) 
    {
        index_pagination[playerid]--;
        if(index_pagination[playerid] <= 0) {
            index_pagination[playerid] = 0;
        }
        Badside_ShowBrankas(playerid);
    }
    else 
    {
        if(PlayerListitem[playerid][listitem] == -1)
        {
            AccountData[playerid][pMenuShowed] = false;
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item apapun!");
        }
        
        AccountData[playerid][pTempValue] = listitem;
        new shstr[528];
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Mohon masukkan berapa jumlah yang ingin diambil:", BadsideBrankas[PlayerListitem[playerid][listitem]][badsideBrankasTemp], BadsideBrankas[PlayerListitem[playerid][listitem]][badsideBrankasQuant]);
        Dialog_Show(playerid, "BadsideVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Badside", 
        shstr, "Input", "Batal");
    }
    return 1;
}

Dialog:BadsideVaultOut(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        AccountData[playerid][pMenuShowed] = false;
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
        return 1;
    }

    if(AccountData[playerid][pTempValue] == -1)
    {
        AccountData[playerid][pMenuShowed] = false;
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item apapun!");
        return 1;
    }

    new shstr[512], id = AccountData[playerid][pTempValue];
    if(isnull(inputtext)) 
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Error: Tidak dapat dikosongkan!\nPlease enter the quantity you want to retrieve:", BadsideBrankas[PlayerListitem[playerid][id]][badsideBrankasTemp], BadsideBrankas[PlayerListitem[playerid][id]][badsideBrankasQuant]);
        Dialog_Show(playerid, "BadsideVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Badside", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(!IsNumericEx(inputtext))
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Error: Please enter only numbers!\nPlease enter the quantity you want to retrieve:", BadsideBrankas[PlayerListitem[playerid][id]][badsideBrankasTemp], BadsideBrankas[PlayerListitem[playerid][id]][badsideBrankasQuant]);
        Dialog_Show(playerid, "BadsideVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Badside", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(strval(inputtext) < 1 || strval(inputtext) > BadsideBrankas[PlayerListitem[playerid][id]][badsideBrankasQuant])
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Error: Jumlah tidak valid!\nPlease enter the quantity you want to retrieve:", BadsideBrankas[PlayerListitem[playerid][id]][badsideBrankasTemp], BadsideBrankas[PlayerListitem[playerid][id]][badsideBrankasQuant]);
        Dialog_Show(playerid, "BadsideVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Badside", 
        shstr, "Input", "Batal");
        return 1;
    }

    new quantity = strval(inputtext), jts[150];
    new Float:countingtotalweight;
    countingtotalweight = GetTotalWeightFloat(playerid) + float(quantity * GetItemWeight(BadsideBrankas[PlayerListitem[playerid][id]][badsideBrankasTemp]))/1000;
    if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
    
    if(!strcmp(BadsideBrankas[PlayerListitem[playerid][id]][badsideBrankasTemp], "Obeng")) 
    {
        if(PlayerHasItem(playerid, "Obeng"))
        {
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah memiliki Obeng!");
        }
        else
        {
            if(quantity > 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat membawa lebih dari satu Obeng!"); 
        }
    }
    if(!strcmp(BadsideBrankas[PlayerListitem[playerid][id]][badsideBrankasTemp], "Cangkul")) 
    {
        if(PlayerHasItem(playerid, "Cangkul"))
        {
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah memiliki Cangkul!");
        }
        else
        {
            if(quantity > 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat membawa lebih dari satu Cangkul!"); 
        }
    }

    if(!strcmp(BadsideBrankas[PlayerListitem[playerid][id]][badsideBrankasTemp], "Smartphone"))
    {
        mysql_format(g_SQL, jts, sizeof(jts), "SELECT * FROM `player_phones` WHERE `phoneOwner`=%d", AccountData[playerid][pID]);
        mysql_pquery(g_SQL, jts, "OnPlayerBuySmartphone", "i", playerid);
    }
    else
    {
        Inventory_Add(playerid, BadsideBrankas[PlayerListitem[playerid][id]][badsideBrankasTemp], BadsideBrankas[PlayerListitem[playerid][id]][badsideBrankasModel], quantity);
    }

    ShowItemBox(playerid, BadsideBrankas[PlayerListitem[playerid][id]][badsideBrankasTemp], sprintf("Received %dx", quantity), BadsideBrankas[PlayerListitem[playerid][id]][badsideBrankasModel], 5);

    BadsideBrankas[PlayerListitem[playerid][id]][badsideBrankasQuant] -= quantity;
    
    if(BadsideBrankas[PlayerListitem[playerid][id]][badsideBrankasQuant] > 0)
    {
        mysql_format(g_SQL, jts, sizeof(jts), "UPDATE `badside_brankas` SET `Quantity`=%d WHERE `ID`=%d", BadsideBrankas[PlayerListitem[playerid][id]][badsideBrankasQuant], BadsideBrankas[PlayerListitem[playerid][id]][badsideBrankasID]);
        mysql_pquery(g_SQL, jts);
    }
    else
    {
        mysql_format(g_SQL, jts, sizeof(jts), "DELETE FROM `badside_brankas` WHERE `ID`=%d", BadsideBrankas[PlayerListitem[playerid][id]][badsideBrankasID]);
        mysql_pquery(g_SQL, jts);

        BadsideBrankas[PlayerListitem[playerid][id]][badsideBrankasExists] = false;
        BadsideBrankas[PlayerListitem[playerid][id]][badsideBrankasID] = 0;
        BadsideBrankas[PlayerListitem[playerid][id]][badsideBrankasFMID] = -1;
        BadsideBrankas[PlayerListitem[playerid][id]][badsideBrankasTemp][0] = EOS;
        BadsideBrankas[PlayerListitem[playerid][id]][badsideBrankasModel] = 0;
        BadsideBrankas[PlayerListitem[playerid][id]][badsideBrankasQuant] = 0;
    }
    AccountData[playerid][pMenuShowed] = false;
    return 1;
}
Dialog:BadsideGarage(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        AccountData[playerid][pInGarkot] = -1;
        return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    }

    new id = ReturnAnyVehiclePBG(playerid, listitem, AccountData[playerid][pInGarkot]);
    if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan yang tersimpan di garasi ini!");
    
    if(PlayerVehicle[id][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
    PlayerVehicle[id][pVehParked] = -1;
    PlayerVehicle[id][pVehFamGarage] = -1;
    PlayerVehicle[id][pVehHouseGarage] = -1;
    PlayerVehicle[id][pVehInsuranced] = false;

    PlayerVehicle[id][pVehImpounded] = false;
    PlayerVehicle[id][pVehImpoundDuration] = 0;
    PlayerVehicle[id][pVehImpoundFee] = 0;
    PlayerVehicle[id][pVehImpoundReason][0] = EOS;

    PlayerVehicle[id][pVehPos][0] = FamilyData[AccountData[playerid][pInGarkot]][famGarageSpPos][0];
    PlayerVehicle[id][pVehPos][1] = FamilyData[AccountData[playerid][pInGarkot]][famGarageSpPos][1];
    PlayerVehicle[id][pVehPos][2] = FamilyData[AccountData[playerid][pInGarkot]][famGarageSpPos][2];
    PlayerVehicle[id][pVehPos][3] = FamilyData[AccountData[playerid][pInGarkot]][famGarageSpPos][3];
    
    OnPlayerVehicleRespawn(id);
    AccountData[playerid][pInGarkot] = -1;

    SetTimerEx("ForcePlayerHopInVehicle", 1500, false, "idd", playerid, PlayerVehicle[id][pVehPhysic], 0);

    new sqlsdwadkw[128];
    mysql_format(g_SQL, sqlsdwadkw, sizeof(sqlsdwadkw), "UPDATE `player_vehicles` SET `PVeh_Familied` = %d WHERE `id` = %d", PlayerVehicle[id][pVehFamGarage], PlayerVehicle[id][pVehID]);
    mysql_pquery(g_SQL, sqlsdwadkw);
    return 1;
}
Dialog:BadsideBosdesk(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFamily] < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota dari family manapun!");
    if(AccountData[playerid][pFamilyRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan petinggi badside/family!");

    switch(listitem)
    {
        case 0: //invite
        {
            new frmxt[522], count = 0;

            foreach(new i : Player) if(i != playerid) if(IsPlayerNearPlayer(playerid, i, 1.5)) 
            {
                if (i % 2 == 0) {
                    format(frmxt, sizeof(frmxt), "%s"WHITE"Player ID - (%d)\n", frmxt, i);
                }
                else {
                    format(frmxt, sizeof(frmxt), "%s"GRAY"Player ID - (%d)\n", frmxt, i);
                }
                NearestUser[playerid][count++] = i;
            }

            if(count == 0)
            {
                PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                return Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Invite Badside", "Tidak ada pemain terdekat!", "Tutup", "");
            }

            Dialog_Show(playerid, "BadsideInviteConfirm", DIALOG_STYLE_TABLIST, "{DA9100}Pahlawan Roleplay "WHITE"- Invite Badside", frmxt, "Pilih", "Batal");
        }
        case 1: //kelola jabatan
        {
            index_pagination[playerid] = 0;

            new 
                string[1012],
                member_name[MAX_MEMBER_ROWS][64],
                member_pID[MAX_MEMBER_ROWS],
                member_rank[MAX_MEMBER_ROWS],
                member_lastlog[MAX_MEMBER_ROWS][30],
                curr_page = index_pagination[playerid],
                curr_index;

            curr_index = curr_page * MAX_MEMBER_ROWS;

            for(new i = 0; i < MAX_MEMBER_ROWS; i++) {
                member_pID[i] = 0;
            }

            new real_i = 0;
            
            new jajang[512];
            mysql_format(g_SQL, jajang, sizeof(jajang), "SELECT * FROM `player_characters` WHERE `Char_Family` = %d ORDER BY `Char_FamilyRank` DESC", AccountData[playerid][pFamily]);
            mysql_query(g_SQL, jajang);

            new rows = cache_num_rows(),
                count = 0;

            if(rows)
            {
                for(new i = curr_index; i < rows; i++) if(i <= rows)
                {
                    if(real_i < sizeof(member_pID)) {

                        cache_get_value_name(i, "Char_Name", member_name[real_i]);
                        cache_get_value_name_int(i, "Char_FamilyRank", member_rank[real_i]);
                        cache_get_value_name(i, "Char_LastLogin", member_lastlog[real_i]);
                        cache_get_value_name_int(i, "pID", member_pID[real_i]); 
                        real_i++;
                    }
                    else 
                    {
                        break;
                    }
                }

                strcat(string, "Nama\tRank\tLast Online\n");

                for(new i = 0; i < real_i; i++) if(member_pID[i] != 0)
                {
                    strcat(string, sprintf("%s\t%s\t%s\n", member_name[i], FamsRank[member_rank[i]], member_lastlog[i]));
                    ListedMember[playerid][count++] = member_pID[i];
                }

                new 
                    total_pages = (rows + MAX_MEMBER_ROWS - 1) / MAX_MEMBER_ROWS;

                new 
                    max_page = total_pages - 1; 

                TempRows[playerid] = rows;

                if(curr_page > 0) {
                    strcat(string, ""RED"<< Sebelumnya");
                    strcat(string, "\n");
                }
                if(curr_page < max_page) {
                    strcat(string, ""GREEN">> Selanjutnya"); 
                    strcat(string, "\n");
                }

                Dialog_Show(playerid, "FamSetRank", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", string, "Pilih", "Batal");
            }
            else
            {
                PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", "Anda tidak memiliki member di badside ini!", "Tutup", "");
            }
        }
        case 2: //kick
        {
            index_pagination[playerid] = 0;
            ShowBadsideKick(playerid); 
        }
        case 3: //saldo
        {
            new rtx[158];
            format(rtx, sizeof(rtx), "Badside/family ini memiliki saldo sebesar:\n\
            "DARKGREEN"$%s\n\
            "RED"$%s", FormatMoney(FamilyData[AccountData[playerid][pFamily]][famMoney]), FormatMoney(FamilyData[AccountData[playerid][pFamily]][famDirtyMoney]));
            Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Badside Money Vault", rtx, "Tutup", "");
        }
        case 4: //deposit saldo
        {
            Dialog_Show(playerid, "BadsideDepositCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Badside Deposit", 
            "Mohon masukkan nominal deposit untuk saldo badside:", "Input", "Batal");
        }
        case 5: //tarik saldo
        {
            Dialog_Show(playerid, "BadsideWithdrawCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Badside Withdraw", 
            "Mohon masukkan nominal penarikan tunai dari saldo badside:", "Input", "Batal");
        }
        case 6: //deposit saldo
        {
            Dialog_Show(playerid, "BadsideDepositDMoney", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Dirty Money Deposit", 
            "Mohon masukkan nominal deposit untuk saldo dirty money badside:", "Input", "Batal");
        }
        case 7: //tarik saldo
        {
            Dialog_Show(playerid, "BadsideWithdrawDMoney", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Dirty Money Withdraw", 
            "Mohon masukkan nominal penarikan saldo dirty money badside:", "Input", "Batal");
        }
    }
    return 1;
}

Dialog:BadsideInviteConfirm(playerid, response, listitem, inputtext[])
{
    if (!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if (listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih!");
    if (AccountData[playerid][pFamily] < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota dari family manapun!");
    if (AccountData[playerid][pFamilyRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan petinggi dari family ini!");

    new targetid = NearestUser[playerid][listitem], icsr[128];
    if (!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if(AccountData[targetid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut harus memiliki level setidaknya 5!");
    AccountData[targetid][pFamily] = AccountData[playerid][pFamily];
    AccountData[targetid][pFamilyRank] = 1;
    mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Family` = %d, `Char_FamilyRank` = 1 WHERE `pID` = %d", AccountData[targetid][pFamily], AccountData[targetid][pID]);
    mysql_pquery(g_SQL, icsr);
    ShowTDN(targetid, NOTIFICATION_INFO, sprintf("Anda telah diundang menjadi anggota %s oleh %s.", GetFamilyName(AccountData[targetid][pFamily]), AccountData[playerid][pName]));
    ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil mengundang %s ke dalam family.", AccountData[targetid][pName]));
    return 1;
}

Dialog:BadsideSetRankConfirm(playerid, response, listitem, inputtext[])
{
    if (!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if (AccountData[playerid][pFamily] < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota dari family manapun!");
    if (AccountData[playerid][pFamilyRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan petinggi dari family ini!");

    if (isnull(inputtext)) return Dialog_Show(playerid, "BadsideSetRankConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Positions",
    "Error: Tidak dapat dikosongkan!\n\
    Please select a position to set (enter a number only):\n\
    1. Member\n\
    2. Vice\n\
    3. Boss", "Set", "Batal");

    if (!IsNumericEx(inputtext)) return Dialog_Show(playerid, "BadsideSetRankConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Positions",
    "Error: Masukkan hanya angka!\n\
    Please select a position to set (enter a number only):\n\
    1. Member\n\
    2. Vice\n\
    3. Boss", "Set", "Batal");

    if (strval(inputtext) < 1 || strval(inputtext) > AccountData[playerid][pFamilyRank]) return Dialog_Show(playerid, "BadsideSetRankConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Positions",
    "Error: Cannot be lower than 1 or higher than your current position!\n\
    Please select a position to set (enter a number only):\n\
    1. Member\n\
    2. Vice\n\
    3. Boss", "Set", "Batal");

    new hjh[128];
    mysql_format(g_SQL, hjh, sizeof(hjh), "UPDATE `player_characters` SET `Char_FamilyRank`=%d WHERE `pID`=%d", strval(inputtext), AccountData[playerid][pTempSQLFactMemberID]);
    mysql_pquery(g_SQL, hjh);

    foreach (new i : Player)
    {
        if (AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && AccountData[playerid][pTempSQLFactMemberID] == AccountData[i][pID])
        {
            AccountData[i][pFamilyRank] = strval(inputtext);
            ShowTDN(i, NOTIFICATION_INFO, "Jabatan baru anda di badside/family telah diubah");
        }
    }

    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah jabatan badside/family Pemain tersebut");
    return 1;
}

Dialog:BadsideDepositCash(playerid, response, listitem, inputtext[])
{
    if (!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if (AccountData[playerid][pFamily] < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota dari family manapun!");
    if (AccountData[playerid][pFamilyRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan petinggi dari family ini!");
    
    if(isnull(inputtext))
    {
        return Dialog_Show(playerid, "BadsideDepositCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Badside Deposit",
        "Error: Tidak dapat dikosongkan!\n\
        Mohon masukkan berapa jumlah deposit:", "Input", "Batal");
    }          

    if (!IsNumericEx(inputtext)) return Dialog_Show(playerid, "BadsideDepositCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Badside Deposit",
        "Error: Masukkan hanya angka!\n\
        Mohon masukkan berapa jumlah deposit:", "Input", "Batal");

    if(strval(inputtext) < 1) return Dialog_Show(playerid, "BadsideDepositCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Badside Deposit",
    "Error: Invalid amount, you can't deposit less than $1!\n\
    Mohon masukkan berapa jumlah deposit:", "Input", "Batal");

    new frmtmny[164];

    if(strval(inputtext) > AccountData[playerid][pMoney]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

    TakePlayerMoneyEx(playerid, strval(inputtext));
    FamilyData[AccountData[playerid][pFamily]][famMoney] += strval(inputtext);
    mysql_format(g_SQL, frmtmny, sizeof(frmtmny), "UPDATE `families` SET `Money` = %d WHERE `ID` = %d", FamilyData[AccountData[playerid][pFamily]][famMoney], AccountData[playerid][pFamily]);
    mysql_pquery(g_SQL, frmtmny);
    ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil deposit $%s", FormatMoney(strval(inputtext))));
    return 1;
}

Dialog:BadsideWithdrawCash(playerid, response, listitem, inputtext[])
{
    if (!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if (AccountData[playerid][pFamily] < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota dari family manapun!");
    if (AccountData[playerid][pFamilyRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan petinggi dari family ini!");
    
    if(isnull(inputtext))
    {
        return Dialog_Show(playerid, "BadsideWithdrawCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Badside Withdraw",
        "Error: Tidak dapat dikosongkan!\n\
       Mohon masukkan jumlah yang ingin ditarik:", "Input", "Batal");
    }          

    if (!IsNumericEx(inputtext)) return Dialog_Show(playerid, "BadsideWithdrawCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Badside Withdraw",
        "Error: Masukkan hanya angka!\n\
       Mohon masukkan jumlah yang ingin ditarik:", "Input", "Batal");

    if(strval(inputtext) < 1) return Dialog_Show(playerid, "BadsideWithdrawCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Badside Withdraw",
    "Error: Jumlah tidak valid, anda tidak dapat withdraw kurang dari $1!\n\
   Mohon masukkan jumlah yang ingin ditarik:", "Input", "Batal");

    new frmtmny[164];
    
    if(FamilyData[AccountData[playerid][pFamily]][famMoney] < RoundNegativeToPositive(strval(inputtext))) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid, saldo tidak cukup!");

    FamilyData[AccountData[playerid][pFamily]][famMoney] -= strval(inputtext);
    GivePlayerMoneyEx(playerid, strval(inputtext));
    mysql_format(g_SQL, frmtmny, sizeof(frmtmny), "UPDATE `families` SET `Money` = %d WHERE `ID` = %d", FamilyData[AccountData[playerid][pFamily]][famMoney], AccountData[playerid][pFamily]);
    mysql_pquery(g_SQL, frmtmny);
    ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil withdraw $%s", FormatMoney(strval(inputtext))));
    return 1;
}

Dialog:BadsideDepositDMoney(playerid, response, listitem, inputtext[])
{
    if (!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if (AccountData[playerid][pFamily] < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota dari family manapun!");
    if (AccountData[playerid][pFamilyRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan petinggi dari family ini!");
    
    if(isnull(inputtext))
    {
        return Dialog_Show(playerid, "BadsideDepositDMoney", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Dirty Money Deposit",
        "Error: Tidak dapat dikosongkan!\n\
        Mohon masukkan berapa jumlah deposit:", "Input", "Batal");
    }          

    if (!IsNumericEx(inputtext)) return Dialog_Show(playerid, "BadsideDepositDMoney", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Dirty Money Deposit",
        "Error: Masukkan hanya angka!\n\
        Mohon masukkan berapa jumlah deposit:", "Input", "Batal");

    if(strval(inputtext) < 1) return Dialog_Show(playerid, "BadsideDepositDMoney", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Dirty Money Deposit",
    "Error: Invalid amount, you can't deposit less than $1!\n\
    Mohon masukkan berapa jumlah deposit:", "Input", "Batal");

    new frmtmny[164];
    
    if(strval(inputtext) > AccountData[playerid][pDirtyMoney]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Dirty money anda tidak mencukupi!");

    TakePlayerDirtyMoney(playerid, strval(inputtext));
    FamilyData[AccountData[playerid][pFamily]][famDirtyMoney] += strval(inputtext);
    mysql_format(g_SQL, frmtmny, sizeof(frmtmny), "UPDATE `families` SET `DirtyMoney` = %d WHERE `ID` = %d", FamilyData[AccountData[playerid][pFamily]][famDirtyMoney], AccountData[playerid][pFamily]);
    mysql_pquery(g_SQL, frmtmny);
    ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil deposit $%s dirty money", FormatMoney(strval(inputtext))));
    return 1;
}

Dialog:BadsideWithdrawDMoney(playerid, response, listitem, inputtext[])
{
    if (!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if (AccountData[playerid][pFamily] < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota dari family manapun!");
    if (AccountData[playerid][pFamilyRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan petinggi dari family ini!");
    
    if(isnull(inputtext))
    {
        return Dialog_Show(playerid, "BadsideWithdrawCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Dirty Money Withdraw",
        "Error: Tidak dapat dikosongkan!\n\
        Mohon masukkan jumlah yang ingin ditarik:", "Input", "Batal");
    }          

    if (!IsNumericEx(inputtext)) return Dialog_Show(playerid, "BadsideWithdrawCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Dirty Money Withdraw",
        "Error: Masukkan hanya angka!\n\
        Mohon masukkan jumlah yang ingin ditarik:", "Input", "Batal");

    if(strval(inputtext) < 1) return Dialog_Show(playerid, "BadsideWithdrawCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Dirty Money Withdraw",
    "Error: Jumlah tidak valid, anda tidak dapat withdraw kurang dari $1!\n\
   Mohon masukkan jumlah yang ingin ditarik:", "Input", "Batal");

    new frmtmny[164];
    
    if(FamilyData[AccountData[playerid][pFamily]][famDirtyMoney] < RoundNegativeToPositive(strval(inputtext))) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid, saldo tidak cukup!");

    FamilyData[AccountData[playerid][pFamily]][famDirtyMoney] -= strval(inputtext);
    GivePlayerDirtyMoney(playerid, strval(inputtext));
    mysql_format(g_SQL, frmtmny, sizeof(frmtmny), "UPDATE `families` SET `DirtyMoney` = %d WHERE `ID` = %d", FamilyData[AccountData[playerid][pFamily]][famDirtyMoney], AccountData[playerid][pFamily]);
    mysql_pquery(g_SQL, frmtmny);
    ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil withdraw $%s dirty money", FormatMoney(strval(inputtext))));
    return 1;
}

Dialog:FamSetRank(playerid, response, listitem, inputtext[])
{
    if(!response) 
        return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    if(listitem == -1) return 1;
    
    if(!strcmp(inputtext, ">> Selanjutnya", true)) 
    {
        index_pagination[playerid]++;

        new
            rows = TempRows[playerid];

        new 
            total_pages = (rows + MAX_MEMBER_ROWS - 1) / MAX_MEMBER_ROWS;

        new 
            max_page = total_pages - 1; 

        if(index_pagination[playerid] >= max_page) {
            index_pagination[playerid] = max_page;
        }
        Show_FamsRankManage(playerid);
    }
    else if(!strcmp(inputtext, "<< Sebelumnya", true)) 
    {
        index_pagination[playerid]--;
        if(index_pagination[playerid] <= 0) {
            index_pagination[playerid] = 0;
        }
        Show_FamsRankManage(playerid);
    }
    else
    {
        if(AccountData[playerid][pFamily] < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota dari family manapun!");
        if(AccountData[playerid][pFamilyRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan petinggi badside/family!");

        mysql_query(g_SQL, sprintf("SELECT * FROM `player_characters` WHERE `pID` = '%d'", ListedMember[playerid][listitem]));
        new rows = cache_num_rows();
        if(rows)
        {
            cache_get_value_name_int(0, "pID", AccountData[playerid][pTempSQLFactMemberID]);
            cache_get_value_name_int(0, "Char_FamilyRank", AccountData[playerid][pTempSQLFactRank]);
            if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFactMemberID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menetapkan rank anda sendiri!");
            if(AccountData[playerid][pTempSQLFactRank] >= AccountData[playerid][pFamilyRank]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menetapkan rank rekan yang sejajar/lebih tinggi dari anda!");
            Dialog_Show(playerid, "BadsideSetRankConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
            "Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. Prospek\n\
            2. Junior\n\
            3. Senior\n\
            4. Penasihat\n\
            5. Wakil\n\
            6. Ketua", "Set", "Batal");
        }
    }
    return 1;
}

Dialog:FamKickMember(playerid, response, listitem, inputtext[])
{
    if (!response)
        return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    if (!strcmp(inputtext, ">> Selanjutnya", true)) {
        index_pagination[playerid]++;
        ShowBadsideKick(playerid);
    }
    else if (!strcmp(inputtext, "<< Sebelumnya", true)) {
        index_pagination[playerid]--;
        if (index_pagination[playerid] < 0) {
            index_pagination[playerid] = 0;
        }
        ShowBadsideKick(playerid);
    }
    else 
    {
        new l_row_pid = ListedMember[playerid][listitem];

        if(AccountData[playerid][pFamily] < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota dari family manapun!");
        if(AccountData[playerid][pFamilyRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan petinggi badside/family!");

        mysql_query(g_SQL, sprintf("SELECT * FROM `player_characters` WHERE `pID` = %d", l_row_pid));
        new rows = cache_num_rows();
        if (rows) 
        {
            new fckname[64], fckrank, fcklastlogin[30], kckstr[225], icsr[128];
            cache_get_value_name(0, "Char_Name", fckname);
            cache_get_value_name_int(0, "Char_FamilyRank", fckrank);
            cache_get_value_name(0, "Char_LastLogin", fcklastlogin);

            if(AccountData[playerid][pID] == l_row_pid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya terhadap diri sendiri!");
            if(fckrank >= AccountData[playerid][pFamilyRank]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat kick player yang ranknya lebih tinggi atau sama dengan anda!");

            foreach(new i : Player)
            {
                if(l_row_pid == AccountData[i][pID])
                {
                    AccountData[i][pFamily] = -1;
                    AccountData[i][pFamilyRank] = 0;
                    SendClientMessage(i, Y_PAHLAWAN, "<!> "WHITE"Anda telah ditendang dari family!");
                }
            }

            mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Family` = -1, `Char_FamilyRank` = 0 WHERE `pID` = %d", l_row_pid);
            mysql_pquery(g_SQL, icsr);

            format(kckstr, sizeof(kckstr), "Anda berhasil mengeluarkan:\n\
            Name: %s\n\
            Rank: %s\n\
            Last Online: %s", fckname, FamsRank[fckrank], fcklastlogin);
            Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Kick Badside", 
            kckstr, "Tutup", "");
        }
    }
    return 1;
}