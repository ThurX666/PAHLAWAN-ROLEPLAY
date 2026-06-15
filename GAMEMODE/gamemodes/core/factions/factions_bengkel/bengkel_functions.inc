#include <YSI_Coding\y_hooks>

static const BennysRank[7][] = 
{
    "N/A",

    "PKL", // 1
    "Amatir", //2
    "Ahli", //3
    "Wakil Manager", //4
    "Manager",
    "Boss Bennys"
};

// Private Vehicle Components
new pv_spoiler[20][0] =
{
	{1000},
	{1001},
	{1002},
	{1003},
	{1014},
	{1015},
	{1016},
	{1023},
	{1058},
	{1060},
	{1049},
	{1050},
	{1138},
	{1139},
	{1146},
	{1147},
	{1158},
	{1162},
	{1163},
	{1164}
};
new pv_nitro[3][0] =
{
    {1008},
    {1009},
    {1010}
};
new pv_fbumper[23][0] =
{
    {1117},
    {1152},
    {1153},
    {1155},
    {1157},
    {1160},
    {1165},
    {1166},
    {1169},
    {1170},
    {1171},
    {1172},
    {1173},
    {1174},
    {1175},
    {1179},
    {1181},
    {1182},
    {1185},
    {1188},
    {1189},
    {1190},
    {1191}
};
new pv_rbumper[22][0] =
{
    {1140},
    {1141},
    {1148},
    {1149},
    {1150},
    {1151},
    {1154},
    {1156},
    {1159},
    {1161},
    {1167},
    {1168},
    {1176},
    {1177},
    {1178},
    {1180},
    {1183},
    {1184},
    {1186},
    {1187},
    {1192},
    {1193}
};
new pv_exhaust[28][0] =
{
    {1018},
    {1019},
    {1020},
    {1021},
    {1022},
    {1028},
    {1029},
    {1037},
    {1043},
    {1044},
    {1045},
    {1046},
    {1059},
    {1064},
    {1065},
    {1066},
    {1089},
    {1092},
    {1104},
    {1105},
    {1113},
    {1114},
    {1126},
    {1127},
    {1129},
    {1132},
    {1135},
    {1136}
};
new pv_bventr[2][0] =
{
    {1142},
    {1144}
};
new pv_bventl[2][0] =
{
    {1143},
    {1145}
};
new pv_bscoop[4][0] =
{
	{1004},
	{1005},
	{1011},
	{1012}
};
new pv_roof[17][0] =
{
    {1006},
    {1032},
    {1033},
    {1035},
    {1038},
    {1053},
    {1054},
    {1055},
    {1061},
    {1067},
    {1068},
    {1088},
    {1091},
    {1103},
    {1128},
    {1130},
    {1131}
};
new pv_lskirt[21][0] =
{
    {1007},
    {1026},
    {1031},
    {1036},
    {1039},
    {1042},
    {1047},
    {1048},
    {1056},
    {1057},
    {1069},
    {1070},
    {1090},
    {1093},
    {1106},
    {1108},
    {1118},
    {1119},
    {1133},
    {1122},
    {1134}
};
new pv_rskirt[21][0] =
{
    {1017},
    {1027},
    {1030},
    {1040},
    {1041},
    {1051},
    {1052},
    {1062},
    {1063},
    {1071},
    {1072},
    {1094},
    {1095},
    {1099},
    {1101},
    {1102},
    {1107},
    {1120},
    {1121},
    {1124},
    {1137}
};
new pv_hydraulics[1][0] =
{
    {1087}
};
new pv_base[1][0] =
{
    {1086}
};
new pv_rbbars[4][0] =
{
    {1109},
    {1110},
    {1123},
    {1125}
};
new pv_fbbars[2][0] =
{
    {1115},
    {1116}
};
new pv_wheels[17][0] =
{
    {1025},
    {1073},
    {1074},
    {1075},
    {1076},
    {1077},
    {1078},
    {1079},
    {1080},
    {1081},
    {1082},
    {1083},
    {1084},
    {1085},
    {1096},
    {1097},
    {1098}
};
new pv_lights[2][0] =
{
	{1013},
	{1024}
};

CountEngineCompoCost(pvid)
{
    new Float:compocost;
    if(Iter_Contains(Vehicle, PlayerVehicle[pvid][pVehPhysic]))
    {
        if(PlayerVehicle[pvid][pVehMaxHealth] == 1000.00)
        {
            compocost = (PlayerVehicle[pvid][pVehMaxHealth] - PlayerVehicle[pvid][pVehHealth])/5;
        }
        else if(PlayerVehicle[pvid][pVehMaxHealth] == 1500.00)
        {
            compocost = (PlayerVehicle[pvid][pVehMaxHealth] - PlayerVehicle[pvid][pVehHealth])/7;
        }
        else if(PlayerVehicle[pvid][pVehMaxHealth] == 2000.00)
        {
            compocost = (PlayerVehicle[pvid][pVehMaxHealth] - PlayerVehicle[pvid][pVehHealth])/10;
        }
    }
    return floatround(compocost);
}

CountBodyCompoCost(pvid)
{
    new compo = 0;
    
    static panels, doors, lights, tires;
    if(Iter_Contains(Vehicle, PlayerVehicle[pvid][pVehPhysic]))
    {
        GetVehicleDamageStatus(PlayerVehicle[pvid][pVehPhysic], panels, doors, lights, tires);

        new
            spoiler = GetVehicleComponentInSlot(PlayerVehicle[pvid][pVehPhysic], CARMODTYPE_SPOILER),
            hood = GetVehicleComponentInSlot(PlayerVehicle[pvid][pVehPhysic], CARMODTYPE_HOOD),
            roof = GetVehicleComponentInSlot(PlayerVehicle[pvid][pVehPhysic], CARMODTYPE_ROOF),
            lamps =  GetVehicleComponentInSlot(PlayerVehicle[pvid][pVehPhysic], CARMODTYPE_LAMPS),
            exhaust =  GetVehicleComponentInSlot(PlayerVehicle[pvid][pVehPhysic], CARMODTYPE_EXHAUST),
            fbumper = GetVehicleComponentInSlot(PlayerVehicle[pvid][pVehPhysic], CARMODTYPE_FRONT_BUMPER),
            rbumper = GetVehicleComponentInSlot(PlayerVehicle[pvid][pVehPhysic], CARMODTYPE_REAR_BUMPER),
            rvent = GetVehicleComponentInSlot(PlayerVehicle[pvid][pVehPhysic], CARMODTYPE_VENT_RIGHT),
            lvent = GetVehicleComponentInSlot(PlayerVehicle[pvid][pVehPhysic], CARMODTYPE_VENT_LEFT);

        if(panels > 0)
        {
            compo += 25;
            if(spoiler >= 1000) compo += 5;
            if(hood >= 1000) compo += 5;
            if(roof >= 1000) compo += 5;
            if(exhaust>= 1000) compo += 5; // total 45
        }
        if(doors > 0)
        {
            compo += 25;
            if(rvent >= 1000) compo += 5;
            if(lvent >= 1000) compo += 5; // total 35
        }
        if(lights > 0)
        {
            compo += 25;
            if(lamps>= 1000) compo += 5;
            if(fbumper >= 1000) compo += 5;
            if(rbumper >= 1000) compo += 5; // total 40
        }
    }
    return compo;
}

CountTiresCompoCost(pvid)
{
    new compo = 0;
    static panels, doors, lights, tires;
    if(Iter_Contains(Vehicle, PlayerVehicle[pvid][pVehPhysic]))
    {
        GetVehicleDamageStatus(PlayerVehicle[pvid][pVehPhysic], panels, doors, lights, tires);

        new wheel = GetVehicleComponentInSlot(PlayerVehicle[pvid][pVehPhysic], CARMODTYPE_WHEELS);
        // total kalo rusak brutal body = 120 
        if(tires > 0)
        {
            compo = 20;
            if(wheel >= 1000) compo += 10;
        }
    }
    return compo;
}

CountUpgradeEngineCompo(pvid)
{
    new compocost = 0;
    if(Iter_Contains(Vehicle, PlayerVehicle[pvid][pVehPhysic]))
    {
        if(PlayerVehicle[pvid][pVehMaxHealth] == 1000.00) //level 1
        {
            compocost = 200;
        }
        else if(PlayerVehicle[pvid][pVehMaxHealth] == 1500.00) //level 2
        {
            compocost = 250;
        }
        else
        {
            compocost = 0;
        }
    }
    return compocost;
}

Bennys_ShowBrankas(playerid)
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
        if (FactionBrankas[i][factionBrankasExists] && FactionBrankas[i][factionBrankasFID] == FACTION_BENNYS)
        {
            if (real_i >= curr_idx && real_i < curr_idx + MAX_PAGINATION_PAGES)
            {
                fbrankas_exists[real_i - curr_idx] = true;
                fbrankas_id[real_i - curr_idx] = i;
                fbrankas_fid[real_i - curr_idx] = FactionBrankas[i][factionBrankasFID];
                fbrankas_model[real_i - curr_idx] = FactionBrankas[i][factionBrankasModel];
                strcopy(fbrankas_temp[real_i - curr_idx], FactionBrankas[i][factionBrankasTemp], 32);
                fbrankas_quant[real_i - curr_idx] = FactionBrankas[i][factionBrankasQuant];
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
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "Lemari Bennys", "Lemari penyimpanan ini kosong!", "Tutup", "");
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

        Dialog_Show(playerid, "BennysVaultWithdraw", DIALOG_STYLE_TABLIST_HEADERS, sprintf("Lemari Bennys: Page %d of %d", curr_page + 1, max_pages),
        string, "Pilih", "Batal");
    }
    return 1;
}

stock ShowBennysKick(playerid) 
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
    mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 5 ORDER BY Char_FactionRank DESC");

    new rows = cache_num_rows(),
        count = 0;

    if(rows)
    {
        for(new i = curr_index; i < rows && real_i < MAX_MEMBER_ROWS; i++)
        {
            cache_get_value_name(i, "Char_Name", member_name[real_i]);
            cache_get_value_name_int(i, "Char_FactionRank", member_rank[real_i]);
            cache_get_value_name(i, "Char_LastLogin", member_lastlog[real_i]);
            cache_get_value_name_int(i, "pID", member_pID[real_i]); 
            real_i++;
        }

        strcat(string, "Nama\tRank\tLast Online\n");

        for(new i = 0; i < real_i; ++i)
        {
            strcat(string, sprintf("%s\t%s\t%s\n", member_name[i], BennysRank[member_rank[i]], member_lastlog[i]));
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

        Dialog_Show(playerid, "BennysKickMember", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Kick Faction", string, "Pilih", "Batal");
    }
    else
    {
        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Kick Faction", "Faction ini tidak memiliki anggota!", "Tutup", "");
    }
    return 1;
}

Show_BennysRankManage(playerid)
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
    mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 5 ORDER BY Char_FactionRank DESC");

    new rows = cache_num_rows(),
        count = 0;

    if(rows)
    {
        for(new i = curr_index; i < rows; i++) if(i <= rows)
        {
            if(real_i < sizeof(member_pID)) {

                cache_get_value_name(i, "Char_Name", member_name[real_i]);
                cache_get_value_name_int(i, "Char_FactionRank", member_rank[real_i]);
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
            strcat(string, sprintf("%s\t%s\t%s\n", member_name[i], BennysRank[member_rank[i]], member_lastlog[i]));
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

        Dialog_Show(playerid, "BennysSetRankPage", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", string, "Pilih", "Batal");
    }
    else
    {
        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", "Faction ini tidak memiliki anggota!", "Tutup", "");
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_CTRL_BACK && AccountData[playerid][pFaction] == FACTION_BENNYS && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(AccountData[playerid][pInEvent]) return 1;
        
        new count = 0, frmxt[522];
        foreach(new i : Player) if(i != playerid) if(IsPlayerNearPlayer(playerid, i, 2.5)) 
		{
			if (i % 2 == 0) {
            format(frmxt, sizeof(frmxt), "%s"WHITE"Player ID - (%d)\n", frmxt, i);
            }
            else {
                format(frmxt, sizeof(frmxt), "%s"GRAY"Player ID - (%d)\n", frmxt, i);
            }
			NearestUser[playerid][count++] = i;
		}

        if(count > 0)
		{
            Dialog_Show(playerid, "FactionPanel", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Faction Panel", 
			frmxt, "Pilih", "Batal");
		}
    }
    return 1;
}

Dialog:BennysVault(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        AccountData[playerid][pMenuShowed] = false;
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
                Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Bennys", 
                "Anda tidak memiliki barang yang dapat disimpan!", "Tutup", "");
            }
            else
            {
                Dialog_Show(playerid, "BennysVaultDeposit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Bennys", str, "Pilih", "Batal");
            }
        }
        case 1: //withdraw
        {
            //if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Rank minimal adalah Wakil Manager to access withdraw vault menu!");
            index_pagination[playerid] = 0;
            Bennys_ShowBrankas(playerid);
        }
    }
    return 1;
}

Dialog:BennysVaultDeposit(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        AccountData[playerid][pMenuShowed] = false;
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
    Dialog_Show(playerid, "BennysVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Bennys", 
    shstr, "Input", "Batal");
    return 1;
}

Dialog:BennysVaultIn(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        AccountData[playerid][pMenuShowed] = false;
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
        format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nTidak dapat dikosongkan!\nMohon masukkan berapa jumlah yang ingin disimpan:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
        Dialog_Show(playerid, "BennysVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Bennys", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(!IsNumericEx(inputtext))
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nMohon diisi hanya angka!\nMohon masukkan berapa jumlah yang ingin disimpan:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
        Dialog_Show(playerid, "BennysVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Bennys", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(strval(inputtext) < 1 || strval(inputtext) > InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity])
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nJumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin disimpan:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
        Dialog_Show(playerid, "BennysVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Bennys", 
        shstr, "Input", "Batal");
        return 1;
    }

    new quantity = strval(inputtext);

    new invstr[1028];
    mysql_format(g_SQL, shstr, sizeof(shstr), "SELECT * FROM `faction_brankas` WHERE `FID` = %d AND `Item` = '%e'", FACTION_BENNYS, InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
    mysql_query(g_SQL, shstr);

    new rows = cache_num_rows();
    if(rows > 0)
    {
        mysql_format(g_SQL, invstr, sizeof(invstr), "UPDATE `faction_brankas` SET `Quantity` = `Quantity` + %d WHERE `FID` = %d AND `Item` = '%e'", quantity, FACTION_BENNYS, InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
        mysql_pquery(g_SQL, invstr);

        ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyimpan item tersebut.");

        for(new x; x < MAX_FACTIONS_ITEMS; ++x)
        {
            if(FactionBrankas[x][factionBrankasExists]  && FactionBrankas[x][factionBrankasFID] == FACTION_BENNYS && !strcmp(FactionBrankas[x][factionBrankasTemp], InventoryData[playerid][PlayerListitem[playerid][id]][invItem], true))
            {
                FactionBrankas[x][factionBrankasQuant] += quantity;
            }
        }
    }
    else
    {
        for(new x; x < MAX_FACTIONS_ITEMS; ++x)
        {
            if(!FactionBrankas[x][factionBrankasExists]) 
            {
                FactionBrankas[x][factionBrankasExists] = true;
                FactionBrankas[x][factionBrankasFID] = FACTION_BENNYS;
                strcopy(FactionBrankas[x][factionBrankasTemp], InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
                FactionBrankas[x][factionBrankasModel] = InventoryData[playerid][PlayerListitem[playerid][id]][invModel];
                FactionBrankas[x][factionBrankasQuant] = quantity;

                mysql_format(g_SQL, invstr, sizeof(invstr), "INSERT INTO `faction_brankas` SET `FID` = %d, `Item`='%e', `Model`=%d, `Quantity`=%d", FACTION_BENNYS, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invModel], quantity);
                mysql_pquery(g_SQL, invstr, "OnFactionDeposit", "id", playerid, x);

                break;
            }
        }
    }
    ShowItemBox(playerid, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], sprintf("Removed %dx", quantity), InventoryData[playerid][PlayerListitem[playerid][id]][invModel], 5);
    Inventory_Remove(playerid, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], quantity);
    return 1;
}

Dialog:BennysVaultWithdraw(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        AccountData[playerid][pMenuShowed] = false;
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
        Bennys_ShowBrankas(playerid);
    }
    else if(!strcmp(inputtext, "<< Sebelumnya", true)) 
    {
        index_pagination[playerid]--;
        if(index_pagination[playerid] <= 0) {
            index_pagination[playerid] = 0;
        }
        Bennys_ShowBrankas(playerid);
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
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Mohon masukkan berapa jumlah yang ingin diambil:", FactionBrankas[PlayerListitem[playerid][listitem]][factionBrankasTemp], FactionBrankas[PlayerListitem[playerid][listitem]][factionBrankasQuant]);
        Dialog_Show(playerid, "BennysVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Bennys", 
        shstr, "Input", "Batal");
    }
    return 1;
}
Dialog:BennysVaultOut(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        AccountData[playerid][pMenuShowed] = false;
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
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Tidak dapat dikosongkan!\nMohon masukkan berapa jumlah yang ingin diambil:", FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant]);
        Dialog_Show(playerid, "BennysVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Bennys", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(!IsNumericEx(inputtext))
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Mohon diisi hanya angka!\nMohon masukkan berapa jumlah yang ingin diambil:", FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant]);
        Dialog_Show(playerid, "BennysVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Bennys", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(strval(inputtext) < 1 || strval(inputtext) > FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant])
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Jumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin diambil:", FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant]);
        Dialog_Show(playerid, "BennysVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Bennys", 
        shstr, "Input", "Batal");
        return 1;
    }

    new quantity = strval(inputtext), jts[150];
    new Float:countingtotalweight;
    countingtotalweight = GetTotalWeightFloat(playerid) + float(quantity * GetItemWeight(FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp]))/1000;
    if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

    if(!strcmp(FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], "Smartphone"))
    {
        mysql_format(g_SQL, jts, sizeof(jts), "SELECT * FROM `player_phones` WHERE `phoneOwner`=%d", AccountData[playerid][pID]);
        mysql_pquery(g_SQL, jts, "OnPlayerBuySmartphone", "i", playerid);
    }
    else
    {
        Inventory_Add(playerid, FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], FactionBrankas[PlayerListitem[playerid][id]][factionBrankasModel], quantity);
    }
    
    ShowItemBox(playerid, FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], sprintf("Received %dx", quantity), FactionBrankas[PlayerListitem[playerid][id]][factionBrankasModel], 5);

    InsertFactionVaultLog(playerid, FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], quantity, "Bennys");

    FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant] -= quantity;
    
    if(FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant] > 0)
    {
        mysql_format(g_SQL, jts, sizeof(jts), "UPDATE `faction_brankas` SET `Quantity`=%d WHERE `ID`=%d", FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant], FactionBrankas[PlayerListitem[playerid][id]][factionBrankasID]);
        mysql_pquery(g_SQL, jts);
    }
    else
    {
        mysql_format(g_SQL, jts, sizeof(jts), "DELETE FROM `faction_brankas` WHERE `ID`=%d", FactionBrankas[PlayerListitem[playerid][id]][factionBrankasID]);
        mysql_pquery(g_SQL, jts);

        FactionBrankas[PlayerListitem[playerid][id]][factionBrankasExists] = false;
        FactionBrankas[PlayerListitem[playerid][id]][factionBrankasID] = 0;
        FactionBrankas[PlayerListitem[playerid][id]][factionBrankasFID] = FACTION_NONE;
        FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp][0] = EOS;
        FactionBrankas[PlayerListitem[playerid][id]][factionBrankasModel] = 0;
        FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant] = 0;
    }
    AccountData[playerid][pMenuShowed] = false;
    return 1;
}
Dialog:BennysLocker(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_BENNYS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Bennys Automotive!");
    switch(listitem)
    {
        case 0: //baju warga
        {
            if(AccountData[playerid][pOnDuty])
            {
                SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
                AccountData[playerid][pIsUsingUniform] = false;
                AccountData[playerid][pOnDuty] = false;
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda sekarang ~r~off duty.");
                Iter_Remove(BennysDuty, playerid);
            }
            else
            {
                if(AccountData[playerid][pGender] == 1)
                {
                    AccountData[playerid][pUniform] = 268;
                    SetPlayerSkin(playerid, 268);
                }
                else
                {
                    AccountData[playerid][pUniform] = 193;
                    SetPlayerSkin(playerid, 193);
                }
                AccountData[playerid][pIsUsingUniform] = true;
                AccountData[playerid][pOnDuty] = true;
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda sekarang ~g~on duty.");
                Iter_Add(BennysDuty, playerid);
            }
        }
        case 1: //baju Bennys
        {
            switch(AccountData[playerid][pGender])
            {
                case 1: //male
                {
                    Dialog_Show(playerid, "BennysUniform", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Baju Bennys", 
                    "Bennys 1\n\
                    "GRAY"Bennys 2\n\
                    Bennys 3", "Pilih", "Batal");
                }
                case 2: //female
                {
                    Dialog_Show(playerid, "BennysUniform", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Baju Bennys", 
                    "Bennys 1\n\
                    "GRAY"Bennys 2", "Pilih", "Batal");
                }
            }
        }
    }
    return 1;
}
Dialog:BennysUniform(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_BENNYS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Bennys Automotive!");

    switch(listitem)
    {
        case 0: AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (268) : (190);
        case 1: AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (42) : (193);
        case 2: AccountData[playerid][pUniform] = 119;
    }
    SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
    AccountData[playerid][pIsUsingUniform] = true;
    return 1;
}
Dialog:BennysBosdesk(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_BENNYS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Bennys Automotive!");
    if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank faction adalah Wakil Manager untuk akses ini!");

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
                return Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Undang Faction", "Tidak ada pemain terdekat!", "Tutup", "");
            }

            Dialog_Show(playerid, "BennysIhnviteConfirm", DIALOG_STYLE_TABLIST, "{DA9100}Pahlawan Roleplay "WHITE"- Undang Faction", frmxt, "Pilih", "Batal");
        }
        case 1:
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
            mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 5 ORDER BY Char_FactionRank DESC");

            new rows = cache_num_rows(),
                count = 0;

            if(rows)
            {
                for(new i = curr_index; i < rows; i++) if(i <= rows)
                {
                    if(real_i < sizeof(member_pID)) {

                        cache_get_value_name(i, "Char_Name", member_name[real_i]);
                        cache_get_value_name_int(i, "Char_FactionRank", member_rank[real_i]);
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
                    strcat(string, sprintf("%s\t%s\t%s\n", member_name[i], BennysRank[member_rank[i]], member_lastlog[i]));
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

                Dialog_Show(playerid, "BennysSetRankPage", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", string, "Pilih", "Batal");
            }
            else
            {
                PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", "Faction ini tidak memiliki anggota!", "Tutup", "");
            }
        }
        case 2: //kick
        {
            index_pagination[playerid] = 0;
            ShowBennysKick(playerid); 
        }
        case 3: //saldo
        {
            new rtx[158];
            format(rtx, sizeof(rtx), "Saldo Bennys Automotive saat ini ialah:\n\
            "DARKGREEN"$%s", FormatMoney(BennysMoneyVault));
            Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Bennys Balance", rtx, "Tutup", "");
        }
        case 4: //deposit saldo
        {
            Dialog_Show(playerid, "BennysDepositCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Bennys Deposit", 
            "Mohon masukkan berapa jumlah deposit:", "Input", "Batal");
        }
        case 5: //tarik saldo
        {
            Dialog_Show(playerid, "BennysWithdrawCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Bennys Withdraw", 
            "Mohon masukkan berapa jumlah withdraw:", "Input", "Batal");
        }
    }
    return 1;
}
Dialog:BennysIhnviteConfirm(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_BENNYS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Bennys Automotive!");
    if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank faction adalah Wakil Manager untuk akses ini!");

    new targetid = NearestUser[playerid][listitem], icsr[128];
    if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    AccountData[targetid][pFaction] = FACTION_BENNYS;
    AccountData[targetid][pFactionRank] = 1;
    mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction` = 5, `Char_FactionRank` = 1 WHERE `pID` = %d", AccountData[targetid][pID]);
    mysql_pquery(g_SQL, icsr);
    ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Anda telah mengundang %s ke faction!", AccountData[targetid][pName]));

    InsertFactionLog("Invite", sprintf("%s %s - %s %s", AccountData[playerid][pName], AccountData[playerid][pUCP], AccountData[targetid][pName], AccountData[targetid][pUCP]), "Bennys");
    return 1;
}
Dialog:BennysSetRankConfirm(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_BENNYS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Bennys Automotive!");
    if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Wakil Manager untuk akses faction menu!");

    if(isnull(inputtext)) return Dialog_Show(playerid, "BennysSetRankConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
    "Error: Tidak dapat dikosongkan!\n\
    Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
    1. PKL\n\
    2. Amatir\n\
    3. Ahli\n\
    4. Wakil Manager\n\
    5. Manager\n\
    6. Boss Bennys", "Set", "Batal");
    
    if(!IsNumericEx(inputtext)) return Dialog_Show(playerid, "BennysSetRankConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
    "Error: Masukkan hanya angka!\n\
    Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
    1. PKL\n\
    2. Amatir\n\
    3. Ahli\n\
    4. Wakil Manager\n\
    5. Manager\n\
    6. Boss Bennys", "Set", "Batal");

    if(strval(inputtext) < 1 || strval(inputtext) > 6) return Dialog_Show(playerid, "BennysSetRankConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
    "Error: Tidak dapat diisi dibawah 1 atau lebih tinggi dari jabatan anda!\n\
    Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
    1. PKL\n\
    2. Amatir\n\
    3. Ahli\n\
    4. Wakil Manager\n\
    5. Manager\n\
    6. Boss Bennys", "Set", "Batal");

    new hjh[128];
    mysql_format(g_SQL, hjh, sizeof(hjh), "UPDATE `player_characters` SET `Char_FactionRank`=%d WHERE `pID`=%d", strval(inputtext), AccountData[playerid][pTempSQLFactMemberID]);
    mysql_pquery(g_SQL, hjh);

    foreach(new i : Player)
    {
        if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && AccountData[playerid][pTempSQLFactMemberID] == AccountData[i][pID])
        {
            AccountData[i][pFactionRank] = strval(inputtext);
            ShowTDN(i, NOTIFICATION_INFO, "Jabatan faction anda telah diperbarui!");
            InsertFactionLog("Set Rank", sprintf("%s %s - %s %s LV %d", AccountData[playerid][pName], AccountData[playerid][pUCP], AccountData[i][pName], AccountData[i][pUCP], strval(inputtext)), "Bennys");
        }
    }

    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah jabatan faction Pemain tersebut!");
    return 1;
}
Dialog:BennysDepositCash(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_BENNYS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Bennys Automotive!");
    if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Rank minimal adalah Wakil Manager untuk akses menu ini!");
    
    if(isnull(inputtext))
    {
        return Dialog_Show(playerid, "BennysDepositCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Bennys Deposit",
        "Error: Tidak dapat dikosongkan!\n\
        Mohon masukkan berapa jumlah deposit:", "Deposit", "Batal");
    }          

    if (!IsNumericEx(inputtext)) return Dialog_Show(playerid, "BennysDepositCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Bennys Deposit",
        "Error: Masukkan hanya angka!\n\
        Mohon masukkan berapa jumlah deposit:", "Deposit", "Batal");

    if(strval(inputtext) < 1) return Dialog_Show(playerid, "BennysDepositCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Bennys Deposit",
    "Error: Invalid amount, you can't deposit less than $1!\n\
    Mohon masukkan berapa jumlah deposit:", "Deposit", "Batal");

    if(strval(inputtext) > AccountData[playerid][pMoney]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

    TakePlayerMoneyEx(playerid, strval(inputtext));
    BennysMoneyVault += strval(inputtext);

    static frmtmny[128];
    mysql_format(g_SQL, frmtmny, sizeof(frmtmny), "UPDATE `stuffs` SET `bennysmoneyvault` = %d WHERE `id` = 0", BennysMoneyVault);
    mysql_pquery(g_SQL, frmtmny);
    ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil deposit $%s untuk Bennys Automotive.", FormatMoney(strval(inputtext))));
    return 1;
}

Dialog:BennysWithdrawCash(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_BENNYS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Bennys Automotive!");
    if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Rank minimal adalah Wakil Manager untuk akses menu ini!");

    if(isnull(inputtext))
    {
        return Dialog_Show(playerid, "BennysWithdrawCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Bennys Withdraw",
        "Error: Tidak dapat dikosongkan!\n\
       Mohon masukkan jumlah yang ingin ditarik:", "Withdraw", "Batal");
    }          

    if (!IsNumericEx(inputtext)) return Dialog_Show(playerid, "BennysWithdrawCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Bennys Withdraw",
        "Error: Masukkan hanya angka!\n\
       Mohon masukkan jumlah yang ingin ditarik:", "Withdraw", "Batal");

    if(strval(inputtext) < 1) return Dialog_Show(playerid, "BennysWithdrawCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Bennys Withdraw",
    "Error: Jumlah tidak valid, anda tidak dapat withdraw kurang dari $1!\n\
   Mohon masukkan jumlah yang ingin ditarik:", "Withdraw", "Batal");

    if(BennysMoneyVault < RoundNegativeToPositive(strval(inputtext))) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid, saldo tidak cukup!");

    BennysMoneyVault -= strval(inputtext);
    GivePlayerMoneyEx(playerid, strval(inputtext));

    static frmtmny[128];
    mysql_format(g_SQL, frmtmny, sizeof(frmtmny), "UPDATE `stuffs` SET `bennysmoneyvault` = %d WHERE `id` = 0", BennysMoneyVault);
    mysql_pquery(g_SQL, frmtmny);

    AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], strval(inputtext), "Bennys");

    ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil withdraw $%s dari Bennys Automotive",FormatMoney(strval(inputtext))));
    return 1;
}
Dialog:BennysGarage(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_BENNYS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Bennys Automotive!");
    switch(listitem)
    {
        case 0: //keluarkan kendaraan
        {
            if(PlayerFactionVehicle[playerid][FACTION_BENNYS] != INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah mengeluarkan kendaraan, simpan terlebih dahulu!");

            Dialog_Show(playerid, "BennysGarageTakeout", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Keluarkan Kendaraan", 
            "Tow Truck\n\
            "GRAY"Yosemite", "Pilih", "Batal");
        }
        case 1: //simpan kendaraan
        {
            for(new x; x < MAX_FACTIONS; x++)
            {
                DestroyVehicle(PlayerFactionVehicle[playerid][x]);
                PlayerFactionVehicle[playerid][x] = INVALID_VEHICLE_ID;
            }
            LSPDPlayerCallsign[playerid][0] = EOS;
            
            static string[168];
            mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `demand_vehicles` WHERE `ownerid` = %d", AccountData[playerid][pID]);
            mysql_pquery(g_SQL, string);
            ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan tersebut telah tersimpan ke garasi faction.");
        }
    }
    return 1;
}

Dialog:BennysGarageTakeout(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        AccountData[playerid][pTempValue] = -1;
        return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    }

    if(AccountData[playerid][pFaction] != FACTION_BENNYS) 
    {
        AccountData[playerid][pTempValue] = -1;
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Bennys Automotive!");
    }
    
    new garageid = GetPlayerNearestFGarage(playerid);
    if(garageid  == -1)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan garasi faction anda!");

    for(new x; x < MAX_FACTIONS; x++)
    {
        DestroyVehicle(PlayerFactionVehicle[playerid][x]);
        PlayerFactionVehicle[playerid][x] = INVALID_VEHICLE_ID;
    }
    
    switch(listitem)
    {
        case 0: //tow truck
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 525;
            PlayerFactionVehicle[playerid][FACTION_BENNYS] = CreateVehicle(525, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 102, 1, 60000, false);
        }
        case 1: //yosemite
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 554;
            PlayerFactionVehicle[playerid][FACTION_BENNYS] = CreateVehicle(554, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 102, 1, 60000, false);
        }
    }

    DestroyFactVehToys(PlayerFactionVehicle[playerid][FACTION_BENNYS]);
    FactionVehHasCallsign[PlayerFactionVehicle[playerid][FACTION_BENNYS]] = false;
    LSPDPlayerCallsign[playerid][0] = EOS;

    PlayerFactionVehStats[playerid][pFactVehColor1] = 102;
    PlayerFactionVehStats[playerid][pFactVehColor2] = 1;
    PlayerFactionVehStats[playerid][pFactVehFuel] = 100;
    PlayerFactionVehStats[playerid][pFactVehMaxHealth] = 1000.0;
    PlayerFactionVehStats[playerid][pFactVehBodyUpgraded] = false;
    PlayerFactionVehStats[playerid][pFactVehBodyBroken] = false;
    PlayerFactionVehStats[playerid][pFactVehLocked] = false;

    VehicleCore[PlayerFactionVehicle[playerid][FACTION_BENNYS]][vCoreFuel] = 100;
    SetValidVehicleHealth(PlayerFactionVehicle[playerid][FACTION_BENNYS], 1000.0); 
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_BENNYS]][vMaxHealth] = 1000.0;
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_BENNYS]][vIsBodyUpgraded] = false;
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_BENNYS]][vIsBodyBroken] = false;
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_BENNYS]][vCoreLocked] = false;
    PutPlayerInVehicleEx(playerid, PlayerFactionVehicle[playerid][FACTION_BENNYS], 0);
    SwitchVehicleEngine(PlayerFactionVehicle[playerid][FACTION_BENNYS], true);
    SwitchVehicleDoors(PlayerFactionVehicle[playerid][FACTION_BENNYS], false);

    static string[555];
    mysql_format(g_SQL, string, sizeof(string), "INSERT INTO `demand_vehicles` (`ownerid`, `model`, `vehX`, `vehY`, `vehZ`, `vehA`, `damage0`, `damage1`, `damage2`, `damage3`, `health`, `fuel`, `locked`, `world`, `color1`, `color2`) VALUES (%d, %d, '%f', '%f', '%f', '0.0', 0, 0, 0, 0, '2000.0', %d, %d, 0, %d, %d)", 
    AccountData[playerid][pID],
    PlayerFactionVehStats[playerid][pFactVehModel],
    FactGarageData[garageid][GarageSpawnPos][0],
    FactGarageData[garageid][GarageSpawnPos][1],
    FactGarageData[garageid][GarageSpawnPos][2],
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_BENNYS]][vCoreFuel],
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_BENNYS]][vCoreLocked],
    PlayerFactionVehStats[playerid][pFactVehColor1],
    PlayerFactionVehStats[playerid][pFactVehColor2]);
    mysql_pquery(g_SQL, string);
    return 1;
}

Dialog:BennysPanel(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    if(AccountData[playerid][pFaction] != FACTION_BENNYS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Bennys Automotive!");
    new targetid = NearestSingle[playerid];
    if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if(!IsPlayerNearPlayer(playerid, targetid, 3.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak dekat dengan anda!");
    if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Karakter anda terluka parah saat ini!");
    switch(listitem)
    {
        case 0: //Invoice Belum Terbayar
        {
            new xjjs[600], count;
            format(xjjs, sizeof(xjjs), "#\tNama Tagihan\tPemberi\tNominal Tagihan\n");
            for(new id; id < MAX_INVOICES; ++id)
            {
                if(InvoiceData[targetid][id][invoiceExists] && InvoiceData[targetid][id][invoiceOwner] == AccountData[targetid][pID]) 
                {
                    format(xjjs, sizeof(xjjs), "%s"WHITE"%d\t"WHITE"%s\t"YELLOW"%s\t"RED"%s\n", xjjs, id + 1, InvoiceData[targetid][id][invoiceName], InvoiceData[targetid][id][invoiceIssuerName], FormatMoney(InvoiceData[targetid][id][invoiceCost]));
                    count++;
                }
            }

            if(count == 0)
            {
                Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Unpaid Invoice", 
                "This person has no invoices.", "Tutup", "");
            }
            else
            {
                Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Unpaid Invoice", 
                xjjs, "Tutup", "");
            }
            NearestSingle[playerid] = INVALID_PLAYER_ID;
        }
        case 1: //invoice manual
        {
            if(!IsPlayerInAnyVehicle(playerid))
            {
                SetPlayerAttachedObject(playerid, 9, 19786, 5, 0.182999, 0.048999, -0.112999, -66.699935, -23.799949, -116.699996, 0.130999, 0.136000, 0.142000, 0, 0);
    		    ApplyAnimation(playerid, "INT_SHOP","shop_loop", 4.1, true, false, false, true, 0, true);
            }

            Dialog_Show(playerid, "InvoiceSetName", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Invoice", 
            "Mohon masukkan nama dari invoice ini:", "Input", "Batal");
        }
        case 2: //Seret
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
    }
    return 1;
}

SavePVComponents(vehicleid, componentid)
{
	foreach(new ii : PvtVehicles)
	{
		if(vehicleid == PlayerVehicle[ii][pVehPhysic])
		{
			for(new s = 0; s < 20; s++)
			{
				if(componentid == pv_spoiler[s][0])
				{
					PlayerVehicle[ii][pVehMod][0] = componentid;
				}
			}

			for(new s = 0; s < 3; s++)
			{
				if(componentid == pv_nitro[s][0])
				{
					PlayerVehicle[ii][pVehMod][1] = componentid;
				}
			}

			for(new s = 0; s < 23; s++)
			{
				if(componentid == pv_fbumper[s][0])
				{
					PlayerVehicle[ii][pVehMod][2] = componentid;
				}
			}

			for(new s = 0; s < 22; s++)
			{
				if(componentid == pv_rbumper[s][0])
				{
					PlayerVehicle[ii][pVehMod][3] = componentid;
				}
			}

			for(new s = 0; s < 28; s++)
			{
				if(componentid == pv_exhaust[s][0])
				{
					PlayerVehicle[ii][pVehMod][4] = componentid;
				}
			}

			for(new s = 0; s < 2; s++)
			{
				if(componentid == pv_bventr[s][0])
				{
					PlayerVehicle[ii][pVehMod][5] = componentid;
				}
			}

			for(new s = 0; s < 2; s++)
			{
				if(componentid == pv_bventl[s][0])
				{
					PlayerVehicle[ii][pVehMod][6] = componentid;
				}
			}

			for(new s = 0; s < 4; s++)
			{
				if(componentid == pv_bscoop[s][0])
				{
					PlayerVehicle[ii][pVehMod][7] = componentid;
				}
			}

			for(new s = 0; s < 17; s++)
			{
				if(componentid == pv_roof[s][0])
				{
					PlayerVehicle[ii][pVehMod][8] = componentid;
				}
			}

			for(new s = 0; s < 21; s++)
			{
				if(componentid == pv_lskirt[s][0])
				{
					PlayerVehicle[ii][pVehMod][9] = componentid;
				}
			}

			for(new s = 0; s < 21; s++)
			{
				if(componentid == pv_rskirt[s][0])
				{
					PlayerVehicle[ii][pVehMod][10] = componentid;
				}
			}

			for(new s = 0; s < 1; s++)
			{
				if(componentid == pv_hydraulics[s][0])
				{
					PlayerVehicle[ii][pVehMod][11] = componentid;
				}
			}

			for(new s = 0; s < 1; s++)
			{
				if(componentid == pv_base[s][0])
				{
					PlayerVehicle[ii][pVehMod][12] = componentid;
				}
			}

			for(new s = 0; s < 4; s++)
			{
				if(componentid == pv_rbbars[s][0])
				{
					PlayerVehicle[ii][pVehMod][13] = componentid;
				}
			}

			for(new s = 0; s < 2; s++)
			{
				if(componentid == pv_fbbars[s][0])
				{
					PlayerVehicle[ii][pVehMod][14] = componentid;
				}
			}

			for(new s = 0; s < 17; s++)
			{
				if(componentid == pv_wheels[s][0])
				{
					PlayerVehicle[ii][pVehMod][15] = componentid;
				}
			}

			for(new s = 0; s < 2; s++)
			{
				if(componentid == pv_lights[s][0])
				{
					PlayerVehicle[ii][pVehMod][16] = componentid;
				}
			}
		}
	}
	return 1;
}

Dialog:BennysSetRankPage(playerid, response, listitem, inputtext[])
{
    if(!response) 
        return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

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
        Show_BennysRankManage(playerid);
    }
    else if(!strcmp(inputtext, "<< Sebelumnya", true)) 
    {
        index_pagination[playerid]--;
        if(index_pagination[playerid] <= 0) {
            index_pagination[playerid] = 0;
        }
        Show_BennysRankManage(playerid);
    }
    else 
    {
        if(AccountData[playerid][pFaction] != FACTION_BENNYS) 
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Bennys Automotive!");
        if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank faction adalah Wakil Manager untuk akses ini!");

        mysql_query(g_SQL, sprintf("SELECT * FROM `player_characters` WHERE `pID` = '%d'", ListedMember[playerid][listitem]));
        new rows = cache_num_rows();
        if(rows)
        {
            cache_get_value_name_int(0, "pID", AccountData[playerid][pTempSQLFactMemberID]);
            cache_get_value_name_int(0, "Char_FactionRank", AccountData[playerid][pTempSQLFactRank]);
            if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFactMemberID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menetapkan rank anda sendiri!");
            if(AccountData[playerid][pTempSQLFactRank] >= AccountData[playerid][pFactionRank]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menetapkan rank rekan yang sejajar/lebih tinggi dari anda!");
            Dialog_Show(playerid, "BennysSetRankConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
            "Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. PKL\n\
            2. Amatir\n\
            3. Ahli\n\
            4. Wakil Manager\n\
            5. Manager\n\
            6. Boss Bennys", "Set", "Batal");
        }
    }
    return 1;
}

Dialog:BennysKickMember(playerid, response, listitem, inputtext[])
{
    if (!response)
        return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    if (!strcmp(inputtext, ">> Selanjutnya", true)) 
    {
        index_pagination[playerid]++;
        ShowBennysKick(playerid);
    }
    else if (!strcmp(inputtext, "<< Sebelumnya", true)) 
    {
        index_pagination[playerid]--;
        if (index_pagination[playerid] < 0) 
        {
            index_pagination[playerid] = 0;
        }
        ShowBennysKick(playerid);
    }
    else 
    {
        new l_row_pid = ListedMember[playerid][listitem];

        if (AccountData[playerid][pFaction] != FACTION_BENNYS)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Bennys Automotive!");

        if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank faction adalah Wakil Manager untuk akses ini!");

        mysql_query(g_SQL, sprintf("SELECT * FROM `player_characters` WHERE `pID` = %d", l_row_pid));
        new rows = cache_num_rows();
        if (rows) {

            new fckname[64], fckrank, fcklastlogin[30], kckstr[225], iscr[128];
            cache_get_value_name(0, "Char_Name", fckname);
            cache_get_value_name_int(0, "Char_FactionRank", fckrank);
            cache_get_value_name(0, "Char_LastLogin", fcklastlogin);

            if (AccountData[playerid][pID] == l_row_pid)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menendang diri sendiri!");

            if (fckrank >= AccountData[playerid][pFactionRank])
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menendang rekan sejajar/lebih tinggi dari anda!");


            static 
                string[168];

            mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `demand_vehicles` WHERE `ownerid` = %d", l_row_pid);
            mysql_pquery(g_SQL, string);

            foreach(new i : Player)
            {
                if(l_row_pid == AccountData[i][pID])
                {
                    for(new x = 0; x < MAX_FACTIONS; x++)
                    {
                        DestroyVehicle(PlayerFactionVehicle[i][x]);
                        PlayerFactionVehicle[i][x] = INVALID_VEHICLE_ID;
                    }
                    LSPDPlayerCallsign[i][0] = EOS;
                    
                    AccountData[i][pFaction] = 0;
                    AccountData[i][pFactionRank] = 0;

                    if(Iter_Contains(BennysDuty, i))
                        Iter_Remove(BennysDuty, i);

                    ShowTDN(i, NOTIFICATION_WARNING, "Anda telah ditendang dari Bennys!");
                    break;
                }
            }

            InsertFactionLog("Kick", sprintf("%s %s - %s", AccountData[playerid][pName], AccountData[playerid][pUCP], fckname), "Bennys");

            mysql_format(g_SQL, iscr, sizeof(iscr), "UPDATE `player_characters` SET `Char_Faction` = 0, `Char_FactionRank` = 0 WHERE `pID` = %d", l_row_pid);
            mysql_pquery(g_SQL, iscr);

            format(kckstr, sizeof(kckstr), "Anda berhasil mengeluarkan:\n\
            Name: %s\n\
            Rank: %s\n\
            Last Online: %s", fckname, BennysRank[fckrank], fcklastlogin);
            Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Kick Faction", kckstr, "Tutup", "");
        }
    }
    return 1;
}

Dialog:FactionCrafting(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    if(AccountData[playerid][pFaction] != FACTION_BENNYS && AccountData[playerid][pFaction] != FACTION_AUTOMAX && AccountData[playerid][pFaction] != FACTION_HANDOVER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Perintah ini hanya dapat diakses oleh faction sejenis bengkel!");

    switch(listitem)
    {
        case 0:
        {
            if(Inventory_Count(playerid, "Komponen") < 180) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Komponen!");
            if(Inventory_Count(playerid, "Tembaga") < 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Tembaga!");
            if(Inventory_Count(playerid, "Besi") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Besi!");
            if(Inventory_Count(playerid, "Plastik") < 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Plastik!");
            if(Inventory_Count(playerid, "Minyak") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Minyak!");

            Inventory_Remove(playerid, "Komponen", 180);
            Inventory_Remove(playerid, "Tembaga", 3);
            Inventory_Remove(playerid, "Besi", 5);
            Inventory_Remove(playerid, "Plastik", 3);
            Inventory_Remove(playerid, "Minyak", 5);

            ShowItemBox(playerid, "Komponen", "Received 180x", 2040, 5);
            ShowItemBox(playerid, "Tembaga", "Received 3x", 19772, 6);
            ShowItemBox(playerid, "Besi", "Received 5x", 19809, 7);
            ShowItemBox(playerid, "Plastik", "Received 3x", 2937, 8);
            ShowItemBox(playerid, "Minyak", "Received 5x", 19621, 9);

            AccountData[playerid][pActivityTime] = 1;
            AccountData[playerid][pTempValue2] = 0;
            pFactionCraftingTimer[playerid] = true;
        }
        case 1:
        {
            if(Inventory_Count(playerid, "Komponen") < 180) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Komponen!");
            if(Inventory_Count(playerid, "Tembaga") < 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Tembaga!");
            if(Inventory_Count(playerid, "Besi") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Besi!");
            if(Inventory_Count(playerid, "Plastik") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Plastik!");
            if(Inventory_Count(playerid, "Minyak") < 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Minyak!");

            Inventory_Remove(playerid, "Komponen", 180);
            Inventory_Remove(playerid, "Tembaga", 3);
            Inventory_Remove(playerid, "Besi", 5);
            Inventory_Remove(playerid, "Plastik", 5);
            Inventory_Remove(playerid, "Minyak", 3);

            ShowItemBox(playerid, "Komponen", "Received 180x", 2040, 5);
            ShowItemBox(playerid, "Tembaga", "Received 3x", 19772, 6);
            ShowItemBox(playerid, "Besi", "Received 5x", 19809, 7);
            ShowItemBox(playerid, "Plastik", "Received 5x", 19433, 8);
            ShowItemBox(playerid, "Minyak", "Received 3x", 1649, 9);

            AccountData[playerid][pActivityTime] = 1;
            AccountData[playerid][pTempValue2] = 1;
            pFactionCraftingTimer[playerid] = true;
        }
        case 2:
        {
            if(Inventory_Count(playerid, "Komponen") < 180) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Komponen!");
            if(Inventory_Count(playerid, "Tembaga") < 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Tembaga!");
            if(Inventory_Count(playerid, "Besi") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Besi!");
            if(Inventory_Count(playerid, "Linggis") < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Linggis!");
            if(Inventory_Count(playerid, "Plastik") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Plastik!");

            Inventory_Remove(playerid, "Komponen", 180);
            Inventory_Remove(playerid, "Tembaga", 3);
            Inventory_Remove(playerid, "Besi", 5);
            Inventory_Remove(playerid, "Linggis", 2);
            Inventory_Remove(playerid, "Plastik", 5);

            ShowItemBox(playerid, "Komponen", "Received 180x", 2040, 5);
            ShowItemBox(playerid, "Tembaga", "Received 3x", 19772, 6);
            ShowItemBox(playerid, "Besi", "Received 5x", 19809, 7);
            ShowItemBox(playerid, "Linggis", "Received 2x", 1316, 8);
            ShowItemBox(playerid, "Plastik", "Received 5x", 2937, 9);

            AccountData[playerid][pActivityTime] = 1;
            AccountData[playerid][pTempValue2] = 2;
            pFactionCraftingTimer[playerid] = true;
        }
        case 3:
        {
            if(Inventory_Count(playerid, "Komponen") < 180) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Komponen!");
            if(Inventory_Count(playerid, "Pilox") < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Pilox!");
            if(Inventory_Count(playerid, "Botol") < 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Botol!");
            if(Inventory_Count(playerid, "Emas") < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Gold!");

            Inventory_Remove(playerid, "Komponen", 180);
            Inventory_Remove(playerid, "Pilox", 1);
            Inventory_Remove(playerid, "Botol", 10);
            Inventory_Remove(playerid, "Emas", 2);

            ShowItemBox(playerid, "Komponen", "Received 180x", 2040, 5);
            ShowItemBox(playerid, "Pilox", "Received 1x", 365, 6);
            ShowItemBox(playerid, "Botol", "Received 10x", 19570, 7);
            ShowItemBox(playerid, "Emas", "Received 2x", 19941, 8);

            AccountData[playerid][pActivityTime] = 1;
            AccountData[playerid][pTempValue2] = 3;
            pFactionCraftingTimer[playerid] = true;
        }
        case 4:
        {
            if(Inventory_Count(playerid, "Komponen") < 180) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Komponen!");
            if(Inventory_Count(playerid, "Tembaga") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Tembaga!");
            if(Inventory_Count(playerid, "Besi") < 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Besi!");
            if(Inventory_Count(playerid, "Plastik") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Plastik!");
            if(Inventory_Count(playerid, "Minyak") < 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Minyak!");

            Inventory_Remove(playerid, "Komponen", 180);
            Inventory_Remove(playerid, "Tembaga", 5);
            Inventory_Remove(playerid, "Besi", 10);
            Inventory_Remove(playerid, "Plastik", 5);
            Inventory_Remove(playerid, "Minyak", 10);

            ShowItemBox(playerid, "Komponen", "Received 180x", 2040, 5);
            ShowItemBox(playerid, "Tembaga", "Received 5x", 19772, 6);
            ShowItemBox(playerid, "Besi", "Received 10x", 19809, 7);
            ShowItemBox(playerid, "Plastik", "Received 5x", 2937, 8);
            ShowItemBox(playerid, "Minyak", "Received 10x", 19621, 9);

            AccountData[playerid][pActivityTime] = 1;
            AccountData[playerid][pTempValue2] = 4;
            pFactionCraftingTimer[playerid] = true;
        }
    }
    return 1;
}