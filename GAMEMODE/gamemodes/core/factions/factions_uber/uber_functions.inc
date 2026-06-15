#include <YSI_Coding\y_hooks>

enum _Uber_Details
{
    Float:gjDutyPos[3],
    Float:gjLockerPos[3],
    Float:gjBosDeskPos[3],
    Float:gjGaragePos[3],
    Float:gjGarageSpawnPos[4],
    gjVWID,
    gjIntID
};

static const UberRank[6][] = 
{
	"N/A",

    "Driver Baru",
    "Junior",
    "Senior",
    "Ast. Boss Uber",
    "Boss Uber"
};


Uber_ShowBrankas(playerid)
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
        if (FactionBrankas[i][factionBrankasExists] && FactionBrankas[i][factionBrankasFID] == FACTION_UBER)
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
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "Lemari Uber", "Lemari penyimpanan ini kosong!", "Tutup", "");
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

        Dialog_Show(playerid, "UberVaultWithdraw", DIALOG_STYLE_TABLIST_HEADERS, sprintf("Lemari Uber: Page %d of %d", curr_page + 1, max_pages),
        string, "Pilih", "Batal");
    }
    return 1;
}

Show_UberRankManage(playerid)
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
    mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 6 ORDER BY Char_FactionRank DESC");

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
            strcat(string, sprintf("%s\t%s\t%s\n", member_name[i], UberRank[member_rank[i]], member_lastlog[i]));
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

        Dialog_Show(playerid, "UberSetRank", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", string, "Pilih", "Batal");
    }
    else
    {
        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", "Faction ini tidak memiliki anggota!", "Tutup", "");
    }
    return 1;
}

stock ShowUberKick(playerid) 
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
    mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 6 ORDER BY Char_FactionRank DESC");

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
            strcat(string, sprintf("%s\t%s\t%s\n", member_name[i], UberRank[member_rank[i]], member_lastlog[i]));
            ListedMember[playerid][count++] = member_pID[i];
        }

        new total_pages = (rows + MAX_MEMBER_ROWS - 1) / MAX_MEMBER_ROWS;
        new max_page = total_pages - 1;

        if(curr_page > 0) 
        {
            strcat(string, ""RED"<< Sebelumnya");
            strcat(string, "\n");
        }

        if(curr_page < max_page) 
        {
            strcat(string, ""GREEN">> Selanjutnya");
            strcat(string, "\n");
        }

        Dialog_Show(playerid, "UberKickMember", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Kick Faction", string, "Pilih", "Batal");
    }
    else
    {
        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Kick Faction", "Faction ini tidak memiliki anggota!", "Tutup", "");
    }
    return 1;
}

hook OnPlayerEnterDynRaceCP(playerid, STREAMER_TAG_RACE_CP:checkpointid)
{
    if(AccountData[playerid][pFaction] == FACTION_UBER)
    {
        if(checkpointid == AccountData[playerid][UberRCP] && IsPlayerInDynamicRaceCP(playerid, AccountData[playerid][UberRCP]))
        {
            ResetAllRaceCP(playerid);
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_CTRL_BACK && AccountData[playerid][pFaction] == FACTION_UBER && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
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

Dialog:UberVault(playerid, response, listitem, inputtext[])
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
                Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Uber", 
                "Anda tidak memiliki barang yang dapat disimpan!", "Tutup", "");
            }
            else
            {
                Dialog_Show(playerid, "UberVaultDeposit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Uber", str, "Pilih", "Batal");
            }
        }
        case 1: //withdraw
        {
            if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Ast. Boss Uber untuk akses Bos Desk!");

            index_pagination[playerid] = 0;
            Uber_ShowBrankas(playerid);
        }
    }
    return 1;
}

Dialog:UberVaultDeposit(playerid, response, listitem, inputtext[])
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
    Dialog_Show(playerid, "UberVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Uber", 
    shstr, "Input", "Batal");
    return 1;
}
Dialog:UberVaultIn(playerid, response, listitem, inputtext[])
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
        format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nTidak dapat dikosongkan!\nMohon masukkan berapa jumlah yang ingin disimpan:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
        Dialog_Show(playerid, "UberVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Uber", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(!IsNumericEx(inputtext))
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nMohon diisi hanya angka!\nMohon masukkan berapa jumlah yang ingin disimpan:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
        Dialog_Show(playerid, "UberVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Uber", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(strval(inputtext) < 1 || strval(inputtext) > InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity])
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nJumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin disimpan:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
        Dialog_Show(playerid, "UberVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Uber", 
        shstr, "Input", "Batal");
        return 1;
    }

    new quantity = strval(inputtext);

    new invstr[1028];
    mysql_format(g_SQL, shstr, sizeof(shstr), "SELECT * FROM `faction_brankas` WHERE `FID` = %d AND `Item` = '%e'", FACTION_UBER, InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
    mysql_query(g_SQL, shstr);

    new rows = cache_num_rows();
    if(rows > 0)
    {
        mysql_format(g_SQL, invstr, sizeof(invstr), "UPDATE `faction_brankas` SET `Quantity` = `Quantity` + %d WHERE `FID` = %d AND `Item` = '%e'", quantity, FACTION_UBER, InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
        mysql_pquery(g_SQL, invstr);

        ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyimpan item tersebut.");

        for(new x; x < MAX_FACTIONS_ITEMS; ++x)
        {
            if(FactionBrankas[x][factionBrankasExists]  && FactionBrankas[x][factionBrankasFID] == FACTION_UBER && !strcmp(FactionBrankas[x][factionBrankasTemp], InventoryData[playerid][PlayerListitem[playerid][id]][invItem], true))
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
                FactionBrankas[x][factionBrankasFID] = FACTION_UBER;
                strcopy(FactionBrankas[x][factionBrankasTemp], InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
                FactionBrankas[x][factionBrankasModel] = InventoryData[playerid][PlayerListitem[playerid][id]][invModel];
                FactionBrankas[x][factionBrankasQuant] = quantity;

                mysql_format(g_SQL, invstr, sizeof(invstr), "INSERT INTO `faction_brankas` SET `FID` = %d, `Item`='%e', `Model`=%d, `Quantity`=%d", FACTION_UBER, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invModel], quantity);
                mysql_pquery(g_SQL, invstr, "OnFactionDeposit", "id", playerid, x);

                break;
            }
        }
    }
    ShowItemBox(playerid, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], sprintf("Removed %dx", quantity), InventoryData[playerid][PlayerListitem[playerid][id]][invModel], 5);
    Inventory_Remove(playerid, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], quantity);
    return 1;
}

Dialog:UberVaultWithdraw(playerid, response, listitem, inputtext[])
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
        Uber_ShowBrankas(playerid);
    }
    else if(!strcmp(inputtext, "<< Sebelumnya", true)) 
    {
        index_pagination[playerid]--;
        if(index_pagination[playerid] <= 0) {
            index_pagination[playerid] = 0;
        }
        Uber_ShowBrankas(playerid);
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
        Dialog_Show(playerid, "UberVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Uber", 
        shstr, "Input", "Batal");
    }
    return 1;
}
Dialog:UberVaultOut(playerid, response, listitem, inputtext[])
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
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Tidak dapat dikosongkan!\nMohon masukkan berapa jumlah yang ingin diambil:", FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant]);
        Dialog_Show(playerid, "UberVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Uber", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(!IsNumericEx(inputtext))
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Mohon diisi hanya angka!\nMohon masukkan berapa jumlah yang ingin diambil:", FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant]);
        Dialog_Show(playerid, "UberVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Uber", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(strval(inputtext) < 1 || strval(inputtext) > FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant])
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Jumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin diambil:", FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant]);
        Dialog_Show(playerid, "UberVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Uber", 
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

    InsertFactionVaultLog(playerid, FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], quantity, "Uber");

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
Dialog:UberLocker(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_UBER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Uber!");
    switch(listitem)
    {
        case 0: //toggle duty
        {
            if(AccountData[playerid][pOnDuty])
            {
                SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
                AccountData[playerid][pIsUsingUniform] = false;
                AccountData[playerid][pOnDuty] = false;
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda sekarang ~r~off duty.");
                Iter_Remove(UberDuty, playerid);
            }
            else
            {
                if(AccountData[playerid][pGender] == 1)
                {
                    AccountData[playerid][pUniform] = 255;
                    SetPlayerSkin(playerid, 255);
                }
                else
                {
                    AccountData[playerid][pUniform] = 263;
                    SetPlayerSkin(playerid, 263);
                }
                AccountData[playerid][pIsUsingUniform] = true;
                AccountData[playerid][pOnDuty] = true;
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda sekarang ~g~on duty.");
                Iter_Add(UberDuty, playerid);
            }
        }
        case 1: //baju amber
        {
            AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (255) : (263);
            SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
            AccountData[playerid][pIsUsingUniform] = true;
        }
    }
    return 1;
}

Dialog:UberBosdesk(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_UBER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Uber!");
    if(AccountData[playerid][pFactionRank] < 4) return SEM(playerid, "Minimum rank Manager untuk akses menu faction!");

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

            Dialog_Show(playerid, "UberInviteConfirm", DIALOG_STYLE_TABLIST, "{DA9100}Pahlawan Roleplay "WHITE"- Undang Faction", frmxt, "Pilih", "Batal");
        }
        case 1: //kelola jabatan
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
            mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 6 ORDER BY Char_FactionRank DESC");

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
                    strcat(string, sprintf("%s\t%s\t%s\n", member_name[i], UberRank[member_rank[i]], member_lastlog[i]));
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

                Dialog_Show(playerid, "UberSetRank", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", string, "Pilih", "Batal");
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
            ShowUberKick(playerid); 
        }
        case 3: //saldo
        {
            new rtx[158];
            format(rtx, sizeof(rtx), "Saldo Uber saat ini ialah:\n\
            "DARKGREEN"$%s", FormatMoney(UberMoneyVault));
            Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Uber Balance", rtx, "Tutup", "");
        }
        case 4: //deposit saldo
        {
            Dialog_Show(playerid, "UberDepositCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Uber Deposit", 
            "Mohon masukkan berapa jumlah deposit:", "Input", "Batal");
        }
        case 5: //tarik saldo
        {
            Dialog_Show(playerid, "UberWithdrawCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Uber Withdraw", 
            "Mohon masukkan berapa jumlah withdraw:", "Input", "Batal");
        }
    }
    return 1;
}

Dialog:UberInviteConfirm(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_UBER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Uber!");
    if(AccountData[playerid][pFactionRank] < 4) return SEM(playerid, "Minimum rank Manager untuk akses menu faction!");

    new targetid = NearestUser[playerid][listitem], icsr[128];
    if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    AccountData[targetid][pFaction] = FACTION_UBER;
    AccountData[targetid][pFactionRank] = 1;
    mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction` = 6, `Char_FactionRank` = 1 WHERE `pID` = %d", AccountData[targetid][pID]);
    mysql_pquery(g_SQL, icsr);
    ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Anda telah mengundang %s ke faction!", AccountData[targetid][pName]));

    InsertFactionLog("Invite", sprintf("%s %s - %s %s", AccountData[playerid][pName], AccountData[playerid][pUCP], AccountData[targetid][pName], AccountData[targetid][pUCP]), "Uber");
    return 1;
}

Dialog:UberSetRankConfirm(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_UBER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Uber!");
    if(AccountData[playerid][pFactionRank] < 4) return SEM(playerid, "Minimum rank Manager untuk akses menu faction!");

    if(isnull(inputtext)) return Dialog_Show(playerid, "UberSetRankConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
    "Error: Tidak dapat dikosongkan!\n\
    Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
    1. Driver Baru\n\
    2. Junior\n\
    3. Senior\n\
    4. Ast. Boss Uber\n\
    5. Boss Uber", "Set", "Batal");
    
    if(!IsNumericEx(inputtext)) return Dialog_Show(playerid, "UberSetRankConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
    "Error: Masukkan hanya angka!\n\
    Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
    1. Driver Baru\n\
    2. Junior\n\
    3. Senior\n\
    4. Ast. Boss Uber\n\
    5. Boss Uber", "Set", "Batal");

    if(strval(inputtext) < 1 || strval(inputtext) > 5) return Dialog_Show(playerid, "UberSetRankConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
    "Error: Tidak dapat diisi dibawah 1 atau lebih tinggi dari jabatan anda!\n\
    Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
    1. Driver Baru\n\
    2. Junior\n\
    3. Senior\n\
    4. Ast. Boss Uber\n\
    5. Boss Uber", "Set", "Batal");

    new hjh[128];
    mysql_format(g_SQL, hjh, sizeof(hjh), "UPDATE `player_characters` SET `Char_FactionRank`=%d WHERE `pID`=%d", strval(inputtext), AccountData[playerid][pTempSQLFactMemberID]);
    mysql_pquery(g_SQL, hjh);

    foreach(new i : Player)
    {
        if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && AccountData[playerid][pTempSQLFactMemberID] == AccountData[i][pID])
        {
            AccountData[i][pFactionRank] = strval(inputtext);
            ShowTDN(i, NOTIFICATION_INFO, "Jabatan faction anda telah diperbarui!");
            InsertFactionLog("Set Rank", sprintf("%s %s - %s %s LV %d", AccountData[playerid][pName], AccountData[playerid][pUCP], AccountData[i][pName], AccountData[i][pUCP], strval(inputtext)), "Uber");
        }
    }

    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah jabatan faction Pemain tersebut!");
    return 1;
}

Dialog:UberDepositCash(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_UBER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Uber!");
    if(AccountData[playerid][pFactionRank] < 4) return SEM(playerid, "Minimum rank Manager untuk akses menu faction!");
    
    if(isnull(inputtext))
    {
        return Dialog_Show(playerid, "UberDepositCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Uber Deposit",
        "Error: Tidak dapat dikosongkan!\n\
        Mohon masukkan berapa jumlah deposit:", "Deposit", "Batal");
    }          

    if (!IsNumericEx(inputtext)) return Dialog_Show(playerid, "UberDepositCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Uber Deposit",
        "Error: Masukkan hanya angka!\n\
        Mohon masukkan berapa jumlah deposit:", "Deposit", "Batal");

    if(strval(inputtext) < 1) return Dialog_Show(playerid, "UberDepositCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Uber Deposit",
    "Error: Invalid amount, you can't deposit less than $1!\n\
    Mohon masukkan berapa jumlah deposit:", "Deposit", "Batal");

    if(strval(inputtext) > AccountData[playerid][pMoney]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

    TakePlayerMoneyEx(playerid, strval(inputtext));
    UberMoneyVault += strval(inputtext);

    static frmtmny[128];
    mysql_format(g_SQL, frmtmny, sizeof(frmtmny), "UPDATE `stuffs` SET `ubermoneyvault` = %d WHERE `id` = 0", UberMoneyVault);
    mysql_pquery(g_SQL, frmtmny);
    ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil deposit $%s untuk Uber.", FormatMoney(strval(inputtext))));
    return 1;
}

Dialog:UberWithdrawCash(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_UBER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Uber!");
    if(AccountData[playerid][pFactionRank] < 4) return SEM(playerid, "Minimum rank Manager untuk akses menu faction!");

    if(isnull(inputtext))
    {
        return Dialog_Show(playerid, "UberWithdrawCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Uber Withdraw",
        "Error: Tidak dapat dikosongkan!\n\
       Mohon masukkan jumlah yang ingin ditarik:", "Withdraw", "Batal");
    }          

    if (!IsNumericEx(inputtext)) return Dialog_Show(playerid, "UberWithdrawCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Uber Withdraw",
        "Error: Masukkan hanya angka!\n\
       Mohon masukkan jumlah yang ingin ditarik:", "Withdraw", "Batal");

    if(strval(inputtext) < 1) return Dialog_Show(playerid, "UberWithdrawCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Uber Withdraw",
    "Error: Jumlah tidak valid, anda tidak dapat withdraw kurang dari $1!\n\
   Mohon masukkan jumlah yang ingin ditarik:", "Withdraw", "Batal");

    if(UberMoneyVault < RoundNegativeToPositive(strval(inputtext))) return SEM(playerid, "Jumlah tidak valid, saldo tidak cukup!");

    UberMoneyVault -= strval(inputtext);
    GivePlayerMoneyEx(playerid, strval(inputtext));

    static frmtmny[128];
    mysql_format(g_SQL, frmtmny, sizeof(frmtmny), "UPDATE `stuffs` SET `ubermoneyvault` = %d WHERE `id` = 0", UberMoneyVault);
    mysql_pquery(g_SQL, frmtmny);

    AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], strval(inputtext), "Uber");

    ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil withdraw $%s dari Uber.", FormatMoney(strval(inputtext))));
    return 1;
}

Dialog:UberGarage(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_UBER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Uber!");
    switch(listitem)
    {
        case 0: //keluarkan kendaraan
        {
            if(PlayerFactionVehicle[playerid][FACTION_UBER] != INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah mengeluarkan kendaraan, simpan terlebih dahulu!");

            Dialog_Show(playerid, "UberGarageTakeout", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Keluarkan Kendaraan", 
            "Manana\n\
            "GRAY"Solair\n\
            Merit", "Pilih", "Batal");
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
Dialog:UberGarageTakeout(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        AccountData[playerid][pTempValue] = -1;
        return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    }
    if(AccountData[playerid][pFaction] != FACTION_UBER) 
    {
        AccountData[playerid][pTempValue] = -1;
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Uber!");
    }

    new garageid = GetPlayerNearestFGarage(playerid);
    if(garageid  == -1)
        return SEM(playerid, "Anda tidak dekat dengan garasi faction anda!");
    
    for(new x; x < MAX_FACTIONS; x++)
    {
        DestroyVehicle(PlayerFactionVehicle[playerid][x]);
        PlayerFactionVehicle[playerid][x] = INVALID_VEHICLE_ID;
    }
    
    switch(listitem)
    {
        case 0: //manana
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 410;

            PlayerFactionVehicle[playerid][FACTION_UBER] = CreateVehicle(410, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 0, 0, 60000, false);

            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_UBER], 1097);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_UBER], 1023);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_UBER], 1013);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_UBER], 1019);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_UBER], 1007);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_UBER], 1017);
            DestroyFactVehToys(PlayerFactionVehicle[playerid][FACTION_UBER]);

            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][0] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][0], 0, "UBER", 100, "Arial", 25, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][0], PlayerFactionVehicle[playerid][FACTION_UBER], -0.980, 0.390, 0.170, 0.000, 0.000, 0.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][1] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][1], 0, "UBER", 100, "Arial", 25, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][1], PlayerFactionVehicle[playerid][FACTION_UBER], 0.980, 0.390, 0.170, 0.000, 0.000, 540.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][2] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][2], 0, "ADVANCED", 140, "Arial", 25, 1, -12068873, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][2], PlayerFactionVehicle[playerid][FACTION_UBER], -0.991, -0.149, 0.030, 0.000, 0.000, 360.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][3] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][3], 0, "TECHNOLOGIES", 140, "Arial", 25, 1, -12068873, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][3], PlayerFactionVehicle[playerid][FACTION_UBER], -0.992, -0.049, -0.060, 0.000, 0.000, 360.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][4] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][4], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][4], PlayerFactionVehicle[playerid][FACTION_UBER], 0.987, 0.580, -0.079, 90.000, 360.000, 180.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][5] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][5], 0, "ADVANCED", 140, "Arial", 25, 1, -12068873, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][5], PlayerFactionVehicle[playerid][FACTION_UBER], 0.991, -0.149, 0.030, 0.000, 0.000, 180.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][6] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][6], 0, "TECHNOLOGIES", 140, "Arial", 25, 1, -12068873, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][6], PlayerFactionVehicle[playerid][FACTION_UBER], 0.992, -0.049, -0.060, 0.000, 0.000, 180.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][7] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][7], 0, "CENTER", 140, "Arial", 25, 1, -12068873, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][7], PlayerFactionVehicle[playerid][FACTION_UBER], 0.980, -0.199, -0.150, 0.000, 0.000, 540.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][8] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][8], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][8], PlayerFactionVehicle[playerid][FACTION_UBER], 0.987, 0.630, -0.079, 90.000, 0.000, 180.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][9] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][9], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][9], PlayerFactionVehicle[playerid][FACTION_UBER], 0.987, 0.682, -0.079, 90.000, 0.000, 180.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][10] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][10], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][10], PlayerFactionVehicle[playerid][FACTION_UBER], -0.993, 0.682, -0.079, 90.000, 360.000, 0.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][11] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][11], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][11], PlayerFactionVehicle[playerid][FACTION_UBER], -0.987, 0.630, -0.079, 90.000, 0.000, 720.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][12] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][12], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][12], PlayerFactionVehicle[playerid][FACTION_UBER], -0.987, 0.580, -0.079, 90.000, 0.000, 0.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][13] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][13], 0, "UBERATC.COM/CAR", 140, "Arial", 20, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][13], PlayerFactionVehicle[playerid][FACTION_UBER], -0.962, -1.160, 0.230, 360.000, 745.000, 0.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][14] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][14], 0, "UBERATC.COM/CAR", 140, "Arial", 20, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][14], PlayerFactionVehicle[playerid][FACTION_UBER], 0.962, -1.160, 0.230, 0.000, 20.000, 540.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][15] = CreateDynamicObject(19309,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterial(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][15], 0, 10765, "airportgnd_sfse", "black64", 0);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][15], PlayerFactionVehicle[playerid][FACTION_UBER], 0.000, -0.470, 0.990, 0.000, 0.000, 0.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][16] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][16], 0, "Uber", 140, "Arial Narrow", 50, 0, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][16], PlayerFactionVehicle[playerid][FACTION_UBER], -0.080, -0.479, 0.990, 0.000, 0.000, 0.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][17] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][17], 0, "Uber", 140, "Arial Narrow", 50, 0, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][17], PlayerFactionVehicle[playerid][FACTION_UBER], 0.080, -0.479, 0.990, 0.000, 0.000, 180.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][18] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][18], 0, "CENTER", 140, "Arial", 25, 1, -12068873, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][18], PlayerFactionVehicle[playerid][FACTION_UBER], -0.980, -0.199, -0.150, 0.000, 0.000, 720.000);
        }
        case 1: //solair
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 458;

            PlayerFactionVehicle[playerid][FACTION_UBER] = CreateVehicle(458, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 0, 0, 60000, false);

            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_UBER], 1097);
            DestroyFactVehToys(PlayerFactionVehicle[playerid][FACTION_UBER]);

            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][0] = CreateDynamicObject(19309,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterial(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][0], 0, 10765, "airportgnd_sfse", "black64", 0);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][0], PlayerFactionVehicle[playerid][FACTION_UBER], -0.009, -0.530, 0.830, 0.000, 0.000, 0.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][1] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][1], 0, "UBER", 100, "Arial", 25, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][1], PlayerFactionVehicle[playerid][FACTION_UBER], -1.131, 0.720, 0.000, 0.000, 0.000, 0.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][2] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][2], 0, "TECHNOLOGIES", 140, "Arial", 25, 1, -12068873, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][2], PlayerFactionVehicle[playerid][FACTION_UBER], -1.125, 0.280, -0.290, 0.000, 0.000, 0.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][3] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][3], 0, "ADVANCED", 140, "Arial", 25, 1, -12068873, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][3], PlayerFactionVehicle[playerid][FACTION_UBER], -1.120, 0.180, -0.180, 0.000, 0.000, 0.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][4] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][4], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][4], PlayerFactionVehicle[playerid][FACTION_UBER], -1.130, 0.910, -0.300, 90.000, 0.000, 360.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][5] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][5], 0, "CENTER", 140, "Arial", 25, 1, -12068873, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][5], PlayerFactionVehicle[playerid][FACTION_UBER], -1.090, 0.120, -0.410, 0.000, 0.000, 0.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][6] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][6], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][6], PlayerFactionVehicle[playerid][FACTION_UBER], -1.130, 0.970, -0.300, 90.000, 0.000, 360.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][7] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][7], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][7], PlayerFactionVehicle[playerid][FACTION_UBER], -1.130, 1.030, -0.300, 90.000, 0.000, 0.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][8] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][8], 0, "UBERATC.COM/CAR", 140, "Arial", 20, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][8], PlayerFactionVehicle[playerid][FACTION_UBER], -1.111, -1.040, 0.000, 0.000, 20.000, 0.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][9] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][9], 0, "UBER", 100, "Arial", 25, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][9], PlayerFactionVehicle[playerid][FACTION_UBER], 1.119, 0.720, 0.000, 0.000, 0.000, 180.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][10] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][10], 0, "ADVANCED", 140, "Arial", 25, 1, -12068873, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][10], PlayerFactionVehicle[playerid][FACTION_UBER], 1.120, 0.180, -0.180, 0.000, 0.000, 180.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][11] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][11], 0, "TECHNOLOGIES", 140, "Arial", 25, 1, -12068873, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][11], PlayerFactionVehicle[playerid][FACTION_UBER], 1.134, 0.280, -0.290, 0.000, 0.000, 180.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][12] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][12], 0, "CENTER", 140, "Arial", 25, 1, -12068873, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][12], PlayerFactionVehicle[playerid][FACTION_UBER], 1.099, 0.123, -0.410, 0.000, 0.000, 180.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][13] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][13], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][13], PlayerFactionVehicle[playerid][FACTION_UBER], 1.129, 0.910, -0.300, 90.000, 0.000, 540.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][14] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][14], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][14], PlayerFactionVehicle[playerid][FACTION_UBER], 1.130, 0.970, -0.300, 90.000, 0.000, 180.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][15] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][15], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][15], PlayerFactionVehicle[playerid][FACTION_UBER], 1.129, 1.030, -0.300, 90.000, 0.000, 180.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][16] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][16], 0, "UBERATC.COM/CAR", 140, "Arial", 20, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][16], PlayerFactionVehicle[playerid][FACTION_UBER], 1.110, -1.040, 0.000, 0.000, 20.000, 180.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][17] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][17], 0, "Uber", 140, "Arial Narrow", 50, 0, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][17], PlayerFactionVehicle[playerid][FACTION_UBER], -0.090, -0.540, 0.830, 0.000, 0.000, 0.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][18] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][18], 0, "Uber", 140, "Arial Narrow", 50, 0, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][18], PlayerFactionVehicle[playerid][FACTION_UBER], 0.070, -0.540, 0.830, 0.000, 0.000, 180.000);
        }
        case 2: //merit
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 551;

            PlayerFactionVehicle[playerid][FACTION_UBER] = CreateVehicle(551, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 0, 0, 60000, false);
            
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_UBER], 1097);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_UBER], 1002);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_UBER], 1005);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_UBER], 1018);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_UBER], 1006);
            DestroyFactVehToys(PlayerFactionVehicle[playerid][FACTION_UBER]);

            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][0] = CreateDynamicObject(19309,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterial(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][0], 0, 10765, "airportgnd_sfse", "black64", 0);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][0], PlayerFactionVehicle[playerid][FACTION_UBER], 0.000, -0.540, 0.980, 0.000, 0.000, 0.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][1] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][1], 0, "Uber", 140, "Arial Narrow", 50, 0, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][1], PlayerFactionVehicle[playerid][FACTION_UBER], -0.080, -0.550, 0.980, 0.000, 0.000, 0.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][2] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][2], 0, "Uber", 140, "Arial Narrow", 50, 0, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][2], PlayerFactionVehicle[playerid][FACTION_UBER], 0.079, -0.550, 0.980, 0.000, 0.000, 180.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][3] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][3], 0, "UBER", 100, "Arial", 25, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][3], PlayerFactionVehicle[playerid][FACTION_UBER], -1.130, 0.630, 0.089, 0.000, 0.000, 0.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][4] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][4], 0, "TECHNOLOGIES", 140, "Arial", 25, 1, -12068873, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][4], PlayerFactionVehicle[playerid][FACTION_UBER], -1.140, 0.200, -0.220, 0.000, 0.000, 0.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][5] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][5], 0, "ADVANCED", 140, "Arial", 25, 1, -12068873, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][5], PlayerFactionVehicle[playerid][FACTION_UBER], -1.139, 0.100, -0.130, 0.000, 0.000, 0.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][6] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][6], 0, "CENTER", 140, "Arial", 25, 1, -12068873, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][6], PlayerFactionVehicle[playerid][FACTION_UBER], -1.129, 0.040, -0.320, 0.000, 0.000, 0.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][7] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][7], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][7], PlayerFactionVehicle[playerid][FACTION_UBER], -1.140, 0.800, -0.210, 90.000, 360.000, 360.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][8] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][8], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][8], PlayerFactionVehicle[playerid][FACTION_UBER], -1.140, 0.860, -0.210, 90.000, 0.000, 0.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][9] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][9], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][9], PlayerFactionVehicle[playerid][FACTION_UBER], -1.140, 0.920, -0.210, 90.000, 0.000, 0.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][10] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][10], 0, "UBERATC.COM/CAR", 140, "Arial", 20, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][10], PlayerFactionVehicle[playerid][FACTION_UBER], -1.110, -0.919, 0.190, 720.000, 20.000, 0.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][11] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][11], 0, "UBER", 100, "Arial", 25, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][11], PlayerFactionVehicle[playerid][FACTION_UBER], 1.130, 0.630, 0.090, 0.000, 0.000, 180.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][12] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][12], 0, "TECHNOLOGIES", 140, "Arial", 25, 1, -12068873, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][12], PlayerFactionVehicle[playerid][FACTION_UBER], 1.140, 0.200, -0.220, 0.000, 0.000, 180.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][13] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][13], 0, "ADVANCED", 140, "Arial", 25, 1, -12068873, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][13], PlayerFactionVehicle[playerid][FACTION_UBER], 1.141, 0.100, -0.130, 0.000, 0.000, 180.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][14] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][14], 0, "CENTER", 140, "Arial", 25, 1, -12068873, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][14], PlayerFactionVehicle[playerid][FACTION_UBER], 1.131, 0.050, -0.320, 0.000, 0.000, 180.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][15] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][15], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][15], PlayerFactionVehicle[playerid][FACTION_UBER], 1.139, 0.800, -0.210, 90.000, 0.000, 180.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][16] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][16], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][16], PlayerFactionVehicle[playerid][FACTION_UBER], 1.140, 0.860, -0.210, 90.000, 0.000, 180.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][17] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][17], 0, ". . . . . . . . . .", 140, "Arial", 25, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][17], PlayerFactionVehicle[playerid][FACTION_UBER], 1.140, 0.920, -0.210, 90.000, 0.000, 180.000);
            
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][18] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,200.0,200.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][18], 0, "UBERATC.COM/CAR", 140, "Arial", 20, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_UBER]][18], PlayerFactionVehicle[playerid][FACTION_UBER], 1.110, -0.919, 0.190, 360.000, 20.000, 180.000);
        }
    }

    FactionVehHasCallsign[PlayerFactionVehicle[playerid][FACTION_UBER]] = false;
    LSPDPlayerCallsign[playerid][0] = EOS;

    PlayerFactionVehStats[playerid][pFactVehColor1] = 0;
    PlayerFactionVehStats[playerid][pFactVehColor2] = 0;
    PlayerFactionVehStats[playerid][pFactVehFuel] = 100;
    PlayerFactionVehStats[playerid][pFactVehMaxHealth] = 1000.0;
    PlayerFactionVehStats[playerid][pFactVehBodyUpgraded] = false;
    PlayerFactionVehStats[playerid][pFactVehBodyBroken] = false;
    PlayerFactionVehStats[playerid][pFactVehLocked] = false;

    VehicleCore[PlayerFactionVehicle[playerid][FACTION_UBER]][vCoreFuel] = 100;
    SetValidVehicleHealth(PlayerFactionVehicle[playerid][FACTION_UBER], 1000.0); 
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_UBER]][vMaxHealth] = 1000.0;
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_UBER]][vIsBodyUpgraded] = false;
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_UBER]][vIsBodyBroken] = false;
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_UBER]][vCoreLocked] = false;
    PutPlayerInVehicleEx(playerid, PlayerFactionVehicle[playerid][FACTION_UBER], 0);
    SwitchVehicleEngine(PlayerFactionVehicle[playerid][FACTION_UBER], true);
    SwitchVehicleDoors(PlayerFactionVehicle[playerid][FACTION_UBER], false);

    static string[555];
    mysql_format(g_SQL, string, sizeof(string), "INSERT INTO `demand_vehicles` (`ownerid`, `model`, `vehX`, `vehY`, `vehZ`, `vehA`, `damage0`, `damage1`, `damage2`, `damage3`, `health`, `fuel`, `locked`, `world`, `color1`, `color2`) VALUES (%d, %d, '%f', '%f', '%f', '0.0', 0, 0, 0, 0, '2000.0', %d, %d, 0, %d, %d)", 
    AccountData[playerid][pID],
    PlayerFactionVehStats[playerid][pFactVehModel],
    FactGarageData[garageid][GarageSpawnPos][0],
    FactGarageData[garageid][GarageSpawnPos][1],
    FactGarageData[garageid][GarageSpawnPos][2],
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_UBER]][vCoreFuel],
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_UBER]][vCoreLocked],
    PlayerFactionVehStats[playerid][pFactVehColor1],
    PlayerFactionVehStats[playerid][pFactVehColor2]);
    mysql_pquery(g_SQL, string);
    return 1;
}
Dialog:UberPanel(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_UBER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Uber!");
    new targetid = NearestSingle[playerid];
    if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if(!IsPlayerNearPlayer(playerid, targetid, 3.0)) return SEM(playerid, "Pemain tersebut tidak dekat dengan anda!");
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
                if(AccountData[i][DraggingID] == playerid) return SEM(playerid, "Anda tidak dapat menyeret seseorang yang sedang menyeret orang lain!");
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
Dialog:UberSetRank(playerid, response, listitem, inputtext[])
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
        Show_UberRankManage(playerid);
    }
    else if(!strcmp(inputtext, "<< Sebelumnya", true)) 
    {
        index_pagination[playerid]--;
        if(index_pagination[playerid] <= 0) {
            index_pagination[playerid] = 0;
        }
        Show_UberRankManage(playerid);
    }
    else 
    {
        if(AccountData[playerid][pFaction] != FACTION_UBER) 
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Uber!");
        if(AccountData[playerid][pFactionRank] < 4) return SEM(playerid, "Minimum rank Manager untuk akses menu faction!");

        mysql_query(g_SQL, sprintf("SELECT * FROM `player_characters` WHERE `pID` = '%d'", ListedMember[playerid][listitem]));
        new rows = cache_num_rows();
        if(rows)
        {
            cache_get_value_name_int(0, "pID", AccountData[playerid][pTempSQLFactMemberID]);
            cache_get_value_name_int(0, "Char_FactionRank", AccountData[playerid][pTempSQLFactRank]);
            if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFactMemberID]) return SEM(playerid, "Anda tidak dapat menetapkan rank anda sendiri!");
            if(AccountData[playerid][pTempSQLFactRank] >= AccountData[playerid][pFactionRank]) return SEM(playerid, "Anda tidak dapat menetapkan rank rekan yang sejajar/lebih tinggi dari anda!");
            Dialog_Show(playerid, "UberSetRankConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
            "Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. Driver Baru\n\
            2. Junior\n\
            3. Senior\n\
            4. Ast. Boss Uber\n\
            5. Boss Uber", "Set", "Batal");
        }
    }
    return 1;
}

Dialog:UberKickMember(playerid, response, listitem, inputtext[])
{
    if (!response)
        return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    if (!strcmp(inputtext, ">> Selanjutnya", true)) {
        index_pagination[playerid]++;
        ShowUberKick(playerid);
    }
    else if (!strcmp(inputtext, "<< Sebelumnya", true)) {
        index_pagination[playerid]--;
        if (index_pagination[playerid] < 0) {
            index_pagination[playerid] = 0;
        }
        ShowUberKick(playerid);
    }
    else 
    {
        new l_row_pid = ListedMember[playerid][listitem];

        if (AccountData[playerid][pFaction] != FACTION_UBER)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Uber!");

        if(AccountData[playerid][pFactionRank] < 4) return SEM(playerid, "Minimum rank Manager untuk akses menu faction!");

        mysql_query(g_SQL, sprintf("SELECT * FROM `player_characters` WHERE `pID` = %d", l_row_pid));
        new rows = cache_num_rows();
        if (rows) 
        {
            new fckname[64], fckrank, fcklastlogin[30], kckstr[225], iscr[128];
            cache_get_value_name(0, "Char_Name", fckname);
            cache_get_value_name_int(0, "Char_FactionRank", fckrank);
            cache_get_value_name(0, "Char_LastLogin", fcklastlogin);

            if (AccountData[playerid][pID] == l_row_pid)
                return SEM(playerid, "Anda tidak dapat menendang diri sendiri!");

            if (fckrank >= AccountData[playerid][pFactionRank])
                return SEM(playerid, "Anda tidak dapat menendang rekan sejajar/lebih tinggi dari anda!");

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

                    if(Iter_Contains(UberDuty, i))
                        Iter_Remove(UberDuty, i);

                    ShowTDN(i, NOTIFICATION_WARNING, "Anda telah ditendang dari Uber!");
                    break;
                }
            }

            InsertFactionLog("Kick", sprintf("%s %s - %s", AccountData[playerid][pName], AccountData[playerid][pUCP], fckname), "Uber");

            mysql_format(g_SQL, iscr, sizeof(iscr), "UPDATE `player_characters` SET `Char_Faction` = 0, `Char_FactionRank` = 0 WHERE `pID` = %d", l_row_pid);
            mysql_pquery(g_SQL, iscr);

            format(kckstr, sizeof(kckstr), "Anda berhasil mengeluarkan:\n\
            Name: %s\n\
            Rank: %s\n\
            Last Online: %s", fckname, UberRank[fckrank], fcklastlogin);
            Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Kick Faction", kckstr, "Tutup", "");
        }
    }
    return 1;
}