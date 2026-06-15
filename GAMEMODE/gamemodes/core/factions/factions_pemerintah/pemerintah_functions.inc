#include <YSI_Coding\y_hooks>

static const PemerintahRank[8][] = 
{
	"N/A",
    "Honorer", //1
    "Staff Junior", //2
    "Staff Senior", //3
    "Kepala Dinas", //4
    "Sekretaris", //5
    "W. Gubernur", //6
    "Gubernur" //7
};

Pemerintah_ShowBrankas(playerid)
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
        if (FactionBrankas[i][factionBrankasExists] && FactionBrankas[i][factionBrankasFID] == FACTION_SAGOV)
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
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "Lemari Pemerintah", "Lemari penyimpanan ini kosong!", "Tutup", "");
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

        Dialog_Show(playerid, "PemerintahVaultWithdraw", DIALOG_STYLE_TABLIST_HEADERS, sprintf("Lemari Pemerintah: Page %d of %d", curr_page + 1, max_pages),
        string, "Pilih", "Batal");
    }
    return 1;
}

Show_PemerintahRankManage(playerid)
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
    mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 4 ORDER BY Char_FactionRank DESC");

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
            strcat(string, sprintf("%s\t%s\t%s\n", member_name[i], PemerintahRank[member_rank[i]], member_lastlog[i]));
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

        Dialog_Show(playerid, "PemerintahSetRank", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", string, "Pilih", "Batal");
    }
    else
    {
        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", "Faction ini tidak memiliki anggota!", "Tutup", "");
    }
    return 1;
}

stock ShowPemerintahKick(playerid) 
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
    mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 4 ORDER BY Char_FactionRank DESC");

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
            strcat(string, sprintf("%s\t%s\t%s\n", member_name[i], PemerintahRank[member_rank[i]], member_lastlog[i]));
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

        Dialog_Show(playerid, "PemerintahKickMember", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Kick Faction", string, "Pilih", "Batal");
    }
    else
    {
        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Kick Faction", "Faction ini tidak memiliki anggota!", "Tutup", "");
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_CTRL_BACK && AccountData[playerid][pFaction] == FACTION_SAGOV && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
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

Dialog:PemerintahVault(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

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
                Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Pemerintah", 
                "Anda tidak memiliki barang yang dapat disimpan!", "Tutup", "");
            }
            else
            {
                Dialog_Show(playerid, "PemerintahVaultDeposit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Pemerintah", str, "Pilih", "Batal");
            }
        }
        case 1: //withdraw
        {
            if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Wakil Wali Kota untuk akses faction vault withdraw!");
            index_pagination[playerid] = 0;
            Pemerintah_ShowBrankas(playerid);
        }
    }
    return 1;
}

Dialog:PemerintahVaultDeposit(playerid, response, listitem, inputtext[])
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
    Dialog_Show(playerid, "PemerintahVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari SAGOV", 
    shstr, "Input", "Batal");
    return 1;
}
Dialog:PemerintahVaultIn(playerid, response, listitem, inputtext[])
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
        Dialog_Show(playerid, "PemerintahVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Pemerintah", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(!IsNumericEx(inputtext))
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nMohon diisi hanya angka!\nMohon masukkan berapa jumlah yang ingin disimpan:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
        Dialog_Show(playerid, "PemerintahVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Pemerintah", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(strval(inputtext) < 1 || strval(inputtext) > InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity])
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nJumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin disimpan:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
        Dialog_Show(playerid, "PemerintahVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Pemerintah", 
        shstr, "Input", "Batal");
        return 1;
    }

    new quantity = strval(inputtext);

    new invstr[1028];
    mysql_format(g_SQL, shstr, sizeof(shstr), "SELECT * FROM `faction_brankas` WHERE `FID` = %d AND `Item` = '%e'", FACTION_SAGOV, InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
    mysql_query(g_SQL, shstr);

    new rows = cache_num_rows();
    if(rows > 0)
    {
        mysql_format(g_SQL, invstr, sizeof(invstr), "UPDATE `faction_brankas` SET `Quantity` = `Quantity` + %d WHERE `FID` = %d AND `Item` = '%e'", quantity, FACTION_SAGOV, InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
        mysql_pquery(g_SQL, invstr);

        ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyimpan item tersebut.");

        for(new x; x < MAX_FACTIONS_ITEMS; ++x)
        {
            if(FactionBrankas[x][factionBrankasExists]  && FactionBrankas[x][factionBrankasFID] == FACTION_SAGOV && !strcmp(FactionBrankas[x][factionBrankasTemp], InventoryData[playerid][PlayerListitem[playerid][id]][invItem], true))
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
                FactionBrankas[x][factionBrankasFID] = FACTION_SAGOV;
                strcopy(FactionBrankas[x][factionBrankasTemp], InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
                FactionBrankas[x][factionBrankasModel] = InventoryData[playerid][PlayerListitem[playerid][id]][invModel];
                FactionBrankas[x][factionBrankasQuant] = quantity;

                mysql_format(g_SQL, invstr, sizeof(invstr), "INSERT INTO `faction_brankas` SET `FID` = %d, `Item`='%e', `Model`=%d, `Quantity`=%d", FACTION_SAGOV, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invModel], quantity);
                mysql_pquery(g_SQL, invstr, "OnFactionDeposit", "id", playerid, x);

                break;
            }
        }
    }
    ShowItemBox(playerid, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], sprintf("Removed %dx", quantity), InventoryData[playerid][PlayerListitem[playerid][id]][invModel], 5);
    Inventory_Remove(playerid, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], quantity);
    return 1;
}

Dialog:PemerintahVaultWithdraw(playerid, response, listitem, inputtext[])
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
        Pemerintah_ShowBrankas(playerid);
    }
    else if(!strcmp(inputtext, "<< Sebelumnya", true)) 
    {
        index_pagination[playerid]--;
        if(index_pagination[playerid] <= 0) {
            index_pagination[playerid] = 0;
        }
        Pemerintah_ShowBrankas(playerid);
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
        Dialog_Show(playerid, "PemerintahVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Pemerintah", 
        shstr, "Input", "Batal");
    }
    return 1;
}
Dialog:PemerintahVaultOut(playerid, response, listitem, inputtext[])
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
        Dialog_Show(playerid, "PemerintahVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Pemerintah", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(!IsNumericEx(inputtext))
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Mohon diisi hanya angka!\nMohon masukkan berapa jumlah yang ingin diambil:", FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant]);
        Dialog_Show(playerid, "PemerintahVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Pemerintah", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(strval(inputtext) < 1 || strval(inputtext) > FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant])
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Jumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin diambil:", FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant]);
        Dialog_Show(playerid, "PemerintahVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Pemerintah", 
        shstr, "Input", "Batal");
        return 1;
    }

    new quantity = strval(inputtext), jts[150];
    new Float:countingtotalweight;
    countingtotalweight = GetTotalWeightFloat(playerid) + float(quantity * GetItemWeight(FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp]))/1000;
    if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

    if(!strcmp(FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], "Obeng")) 
    {
        if(PlayerHasItem(playerid, "Obeng"))
        {
            return SEM(playerid, "Anda sudah memiliki Obeng!");
        }
        else
        {
            if(quantity > 1) return SEM(playerid, "Anda tidak dapat membawa lebih dari satu Obeng!"); 
        }
    }
    if(!strcmp(FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], "Cangkul")) 
    {
        if(PlayerHasItem(playerid, "Cangkul"))
        {
            return SEM(playerid, "Anda sudah memiliki Cangkul!");
        }
        else
        {
            if(quantity > 1) return SEM(playerid, "Anda tidak dapat membawa lebih dari satu Cangkul!"); 
        }
    }
    
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

    InsertFactionVaultLog(playerid, FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], quantity, "Pemerintah");

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
Dialog:PemerintahPanel(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    new targetid = NearestSingle[playerid];
    if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if(!IsPlayerNearPlayer(playerid, targetid, 3.0)) return SEM(playerid, "Pemain tersebut tidak dekat dengan anda!");
    if(AccountData[playerid][pKnockdown]) return SEM(playerid, "Karakter anda terluka parah saat ini!");
    switch(listitem)
    {
        case 0: //Periksa Lisensi
        {
            if(!CheckPlayerLicense(targetid))
            {
                Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Licenses Checking", 
                "Orang tersebut tidak memiliki lisensi.", "Tutup", "");
                return 1;
            }

            ShowLCTD(targetid, playerid);

            NearestSingle[playerid] = INVALID_PLAYER_ID;
        }
        case 1: //borgol
        {
            AccountData[targetid][pCuffed] = true;
            GameTextForPlayer(targetid, "~r~Terborgol", 3500, 3);
            SetPlayerSpecialAction(targetid, SPECIAL_ACTION_CUFFED);
            ShowTDN(targetid, NOTIFICATION_INFO, "Anda telah diborgol!");
            NearestSingle[playerid] = INVALID_PLAYER_ID;
        }
        case 2: //buka borgol
        {
            AccountData[targetid][pCuffed] = false;
            GameTextForPlayer(targetid, "~g~Borgol Dilepas", 3500, 3);
            SetPlayerSpecialAction(targetid, SPECIAL_ACTION_NONE);
            ShowTDN(targetid, NOTIFICATION_INFO, "Borgol anda telah dilepas!");
            NearestSingle[playerid] = INVALID_PLAYER_ID;
        }
        case 3: //Invoice Belum Terbayar
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
        case 4: //Kartu Identitas
        {
            if(!AccountData[targetid][pHasKTP]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak memiliki Kartu Tanda Penduduk/sudah expired!");
            
            ShowIDCTD(targetid, playerid);
        }
        case 5: //Geledah
        {
            ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, false, false, false, false, 0, true);

            new str[1218], count;
            format(str, sizeof(str), "Nama Item\tJumlah\n");
            for(new index; index < MAX_INVENTORY; index++)
            {
                if(InventoryData[targetid][index][invExists])
                {
                    for(new i; i < sizeof(g_aInventoryItems); i ++) if (!strcmp(g_aInventoryItems[i][e_InventoryItem], InventoryData[targetid][index][invItem], true))
                    {
                        if (i % 2 == 0)
                        {
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
                Dialog_Show(playerid, "FactionConsficating", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Geledah", str, "Pilih", "Batal");
            }
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
        case 7: //Seret
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
        case 8: //Masukkan Mobil
        {
            new vehid = GetNearestVehicleToPlayer(playerid, 4.0, false);
            if(vehid != INVALID_VEHICLE_ID)
            {
                if(GetEmptyBackSeat(vehid) == INVALID_SEAT_ID) return SEM(playerid, "Tidak ada kursi kosong di belakang!");
                PutPlayerInVehicleEx(targetid, vehid, GetEmptyBackSeat(vehid));
                TogglePlayerControllable(targetid, false);
                AccountData[targetid][pDetained] = true;
                ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasukkan Pemain tersebut secara paksa.");
            }
            NearestSingle[playerid] = INVALID_PLAYER_ID;
        }
        case 9: //Keluarkan Paksa
        {
            if(!AccountData[targetid][pDetained]) return SEM(playerid, "Pemain tersebut tidak sedang di-detain!");
            TogglePlayerControllable(targetid, true);
            RemovePlayerFromVehicle(targetid);
            AccountData[targetid][pDetained] = false;
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menendang Pemain tersebut dari kendaraan.");
            NearestSingle[playerid] = INVALID_PLAYER_ID;
        }
        case 10: //Invoice Manual
        {
            if(!IsPlayerInAnyVehicle(playerid))
            {
                SetPlayerAttachedObject(playerid, 9, 19786, 5, 0.182999, 0.048999, -0.112999, -66.699935, -23.799949, -116.699996, 0.130999, 0.136000, 0.142000, 0, 0);
    		    ApplyAnimation(playerid, "INT_SHOP","shop_loop", 4.1, true, false, false, true, 0, true);
            }

            Dialog_Show(playerid, "InvoiceSetName", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Invoice", 
            "Mohon masukkan nama dari invoice ini:", "Input", "Batal");
        }
        case 11:
        {
            new vehid = GetNearestVehicleToPlayer(playerid, 4.0, false);
            if(vehid == INVALID_VEHICLE_ID) return SEM(playerid, "There are no vehicles around!");

            foreach(new pv : PvtVehicles)
            {
                if(Iter_Contains(Vehicle, PlayerVehicle[pv][pVehPhysic]))
                {
                    ApplyAnimation(playerid, "COP_AMBIENT", "Copbrowse_loop", 2.33, true, false, false, false, false, true);

                    AccountData[playerid][pActivityTime] = 1;
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENYITA");
                    ShowProgressBar(playerid);

                    AccountData[playerid][pTempVehIterID] = pv;
                    pImpoundingInsuTimer[playerid] = true;
                    return 1;
                }
            }
            SEM(playerid, "Kendaraan tersebut bukanlah kendaraan pribadi!");
        }
        case 12: //sita senjata
        {
            ResetPlayerWeaponsEx(targetid);
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyita seluruh senjata Pemain tersebut.");
            SIM(targetid, "Seluruh senjata yang anda miliki telah disita oleh "RED"%s [%s] (ID: %d)", AccountData[playerid][pName], AccountData[playerid][pUCP], playerid);

            NearestSingle[playerid] = INVALID_PLAYER_ID;
        }
    }
    return 1;
}

Dialog:PemerintahLocker(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_SAGOV) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Pemerintah Kota Pahlawan Roleplay!");
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
                Iter_Remove(PemerDuty, playerid);
            }
            else
            {
                if(AccountData[playerid][pGender] == 1)
                {
                    AccountData[playerid][pUniform] = 295;
                    SetPlayerSkin(playerid, 295);
                }
                else
                {
                    AccountData[playerid][pUniform] = 141;
                    SetPlayerSkin(playerid, 141);
                }
                ResetWeapon(playerid, 3);
                AccountData[playerid][pIsUsingUniform] = true;
                AccountData[playerid][pOnDuty] = true;
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda sekarang ~g~on duty.");
                Iter_Add(PemerDuty, playerid);
            }
        }
        case 1: //baju pemerintah
        {
            switch(AccountData[playerid][pGender])
            {
                case 1: //male
                {
                    Dialog_Show(playerid, "PemerintahUniform", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Baju Pemerintah", 
                    "Gubernur\n\
                    "GRAY"W. Gubernur\n\
                    Sekretaris\n\
                    "GRAY"Kepala Dinas\n\
                    Pegawai Senior\n\
                    "GRAY"Pegawai Junior\n\
                    Tim Magang\n\
                    "GRAY"Satpam", "Pilih", "Batal");
                }
                case 2: //female
                {
                    Dialog_Show(playerid, "PemerintahUniform", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Baju Pemerintah", 
                    "Sekretaris\n\
                    "GRAY"Kepala Dinas\n\
                    Pegawai Senior\n\
                    "GRAY"Pegawai Junior\n\
                    Tim Magang\n\
                    "GRAY"Pemerintah 3\n\
                    Pemerintah 4\n\
                    "GRAY"Pemerintah 5\n\
                    Pemerintah 6\n\
                    "GRAY"Pemerintah 7", "Pilih", "Batal");
                }
            }
        }
        case 2: //baton stick
        {
            ResetWeapon(playerid, 3);
            GivePlayerWeaponEx(playerid, 3, 1, WEAPON_TYPE_FACTION);

            ShowItemBox(playerid, "Baton Stick", "Received 1x", 334, 5);
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mengambil ~b~Baton Stick");
        }
    }
    return 1;
}

Dialog:PemerintahUniform(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_SAGOV) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Pemerintah Kota Pahlawan Roleplay!");

    switch(listitem)
    {
        case 0: AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (228) : (141);
        case 1: AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (187) : (91);
        case 2: AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (68) : (76);
        case 3: AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (153) : (11);
        case 4: AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (186) : (148);
        case 5: AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (147) : (141);
        case 6: AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (59) : (91);
        case 7: AccountData[playerid][pUniform] = 71;
        case 8: AccountData[playerid][pUniform] = 11;
        case 9: AccountData[playerid][pUniform] = 148;
    }
    SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
    AccountData[playerid][pIsUsingUniform] = true;
    return 1;
}

Dialog:PemerintahBosdesk(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_SAGOV) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Pemerintah Kota Pahlawan Roleplay!");
    if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Wakil Wali Kota untuk akses faction menu!");

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

            Dialog_Show(playerid, "PemerintahInviteConfirm", DIALOG_STYLE_TABLIST, "{DA9100}Pahlawan Roleplay "WHITE"- Undang Faction", frmxt, "Pilih", "Batal");
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
            mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 4 ORDER BY Char_FactionRank DESC");

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
                    strcat(string, sprintf("%s\t%s\t%s\n", member_name[i], PemerintahRank[member_rank[i]], member_lastlog[i]));
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

                Dialog_Show(playerid, "PemerintahSetRank", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", string, "Pilih", "Batal");
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
            ShowPemerintahKick(playerid); 
        }
        case 3: //saldo
        {
            new rtx[158];
            format(rtx, sizeof(rtx), "Saldo Pemerintah Kota Pahlawan Roleplay saat ini ialah:\n\
            "DARKGREEN"$%s", FormatMoney(PemerMoneyVault));
            Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Pemerintah Balance", rtx, "Tutup", "");
        }
        case 4: //deposit saldo
        {
            Dialog_Show(playerid, "PemerintahDepositCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Pemerintah Deposit", 
            "Mohon masukkan berapa jumlah deposit:", "Input", "Batal");
        }
        case 5: //tarik saldo
        {
            Dialog_Show(playerid, "PemerintahWithdrawCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Pemerintah Withdraw", 
            "Mohon masukkan berapa jumlah withdraw:", "Input", "Batal");
        }
    }
    return 1;
}

Dialog:PemerintahInviteConfirm(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_SAGOV) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Pemerintah Kota Pahlawan Roleplay!");
    if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Wakil Wali Kota untuk akses faction menu!");

    new targetid = NearestUser[playerid][listitem], icsr[128];
    if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    AccountData[targetid][pFaction] = FACTION_SAGOV;
    AccountData[targetid][pFactionRank] = 1;
    mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction` = 4, `Char_FactionRank` = 1 WHERE `pID` = %d", AccountData[targetid][pID]);
    mysql_pquery(g_SQL, icsr);
    ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Anda telah mengundang %s ke faction!", AccountData[targetid][pName]));

    InsertFactionLog("Invite", sprintf("%s %s - %s %s", AccountData[playerid][pName], AccountData[playerid][pUCP], AccountData[targetid][pName], AccountData[targetid][pUCP]), "Pemerintah");
    return 1;
}
Dialog:PemerintahSetRankConfirm(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_SAGOV) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Pemerintah Kota Pahlawan Roleplay!");
    if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Wakil Wali Kota untuk akses faction menu!");

    if(isnull(inputtext)) return Dialog_Show(playerid, "PemerintahSetRankConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
    "Error: Tidak dapat dikosongkan!\n\
    Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
    1. Honorer\n\
    2. Staff Junior\n\
    3. Staff Senior\n\
    4. Kepala Dinas\n\
    5. Sekretaris\n\
    6. W. Gubernur\n\
    7. Gubernur", "Set", "Batal");
    
    if(!IsNumericEx(inputtext)) return Dialog_Show(playerid, "PemerintahSetRankConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
    "Error: Masukkan hanya angka!\n\
    Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
    1. Honorer\n\
    2. Staff Junior\n\
    3. Staff Senior\n\
    4. Kepala Dinas\n\
    5. Sekretaris\n\
    6. W. Gubernur\n\
    7. Gubernur", "Set", "Batal");

    if(strval(inputtext) < 1 || strval(inputtext) > 7) return Dialog_Show(playerid, "PemerintahSetRankConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
    "Error: Tidak dapat diisi dibawah 1 atau lebih tinggi dari jabatan anda!\n\
    Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
    1. Honorer\n\
    2. Staff Junior\n\
    3. Staff Senior\n\
    4. Kepala Dinas\n\
    5. Sekretaris\n\
    6. W. Gubernur\n\
    7. Gubernur", "Set", "Batal");

    new hjh[128];
    mysql_format(g_SQL, hjh, sizeof(hjh), "UPDATE `player_characters` SET `Char_FactionRank`=%d WHERE `pID`=%d", strval(inputtext), AccountData[playerid][pTempSQLFactMemberID]);
    mysql_pquery(g_SQL, hjh);

    foreach(new i : Player)
    {
        if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && AccountData[playerid][pTempSQLFactMemberID] == AccountData[i][pID])
        {
            AccountData[i][pFactionRank] = strval(inputtext);
            ShowTDN(i, NOTIFICATION_INFO, "Jabatan faction anda telah diperbarui!");
            InsertFactionLog("Set Rank", sprintf("%s %s - %s %s LV %d", AccountData[playerid][pName], AccountData[playerid][pUCP], AccountData[i][pName], AccountData[i][pUCP], strval(inputtext)), "Pemerintah");
        }
    }

    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah jabatan faction Pemain tersebut!");
    return 1;
}
Dialog:PemerintahDepositCash(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_SAGOV) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Pemerintah Kota Pahlawan Roleplay!");
    if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Wakil Wali Kota untuk akses faction menu!");
    
    if(isnull(inputtext))
    {
        return Dialog_Show(playerid, "PemerintahDepositCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Pemerintah Deposit",
        "Error: Tidak dapat dikosongkan!\n\
        Mohon masukkan berapa jumlah deposit:", "Deposit", "Batal");
    }          

    if (!IsNumericEx(inputtext)) return Dialog_Show(playerid, "PemerintahDepositCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Pemerintah Deposit",
        "Error: Masukkan hanya angka!\n\
        Mohon masukkan berapa jumlah deposit:", "Deposit", "Batal");

    if(strval(inputtext) < 1) return Dialog_Show(playerid, "PemerintahDepositCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Pemerintah Deposit",
    "Error: Invalid amount, you can't deposit less than $1!\n\
    Mohon masukkan berapa jumlah deposit:", "Deposit", "Batal");

    if(strval(inputtext) > AccountData[playerid][pMoney]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

    TakePlayerMoneyEx(playerid, strval(inputtext));
    PemerMoneyVault += strval(inputtext);

    static frmtmny[128];
    mysql_format(g_SQL, frmtmny, sizeof(frmtmny), "UPDATE `stuffs` SET `pemermoneyvault` = %d WHERE `id` = 0", PemerMoneyVault);
    mysql_pquery(g_SQL, frmtmny);
    ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil deposit $%s untuk Pemerintah Pahlawan Roleplay.", FormatMoney(strval(inputtext))));
    return 1;
}

Dialog:PemerintahWithdrawCash(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_SAGOV) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Pemerintah Kota Pahlawan Roleplay!");
    if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Wakil Wali Kota untuk akses faction menu!");

    if(isnull(inputtext))
    {
        return Dialog_Show(playerid, "PemerintahWithdrawCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Pemerintah Withdraw",
        "Error: Tidak dapat dikosongkan!\n\
       Mohon masukkan jumlah yang ingin ditarik:", "Withdraw", "Batal");
    }          

    if (!IsNumericEx(inputtext)) return Dialog_Show(playerid, "PemerintahWithdrawCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Pemerintah Withdraw",
        "Error: Masukkan hanya angka!\n\
       Mohon masukkan jumlah yang ingin ditarik:", "Withdraw", "Batal");

    if(strval(inputtext) < 1) return Dialog_Show(playerid, "PemerintahWithdrawCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Pemerintah Withdraw",
    "Error: Jumlah tidak valid, anda tidak dapat withdraw kurang dari $1!\n\
   Mohon masukkan jumlah yang ingin ditarik:", "Withdraw", "Batal");

    if(PemerMoneyVault < RoundNegativeToPositive(strval(inputtext))) return SEM(playerid, "Jumlah tidak valid, saldo tidak cukup!");

    PemerMoneyVault -= strval(inputtext);
    GivePlayerMoneyEx(playerid, strval(inputtext));

    static frmtmny[128];
    mysql_format(g_SQL, frmtmny, sizeof(frmtmny), "UPDATE `stuffs` SET `pemermoneyvault` = %d WHERE `id` = 0", PemerMoneyVault);
    mysql_pquery(g_SQL, frmtmny);

    AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], strval(inputtext), "Pemerintah");

    ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil withdraw $%s dari Pemerintah Pahlawan Roleplay.", FormatMoney(strval(inputtext))));
    return 1;
}
Dialog:PemerintahGarage(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_SAGOV) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Pemerintah Kota Pahlawan Roleplay!");
    switch(listitem)
    {
        case 0: //keluarkan kendaraan
        {
            if(PlayerFactionVehicle[playerid][FACTION_SAGOV] != INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah mengeluarkan kendaraan, simpan terlebih dahulu!");

            Dialog_Show(playerid, "PemerintahGarageTakeout", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Keluarkan Kendaraan", 
            "Premier\n\
            "GRAY"Stafford\n\
            Stretch\n\
            "GRAY"FBI Rancher\n\
            Hermes", "Pilih", "Batal");
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

Dialog:PemerintahGarageTakeout(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        AccountData[playerid][pTempValue] = -1;
        return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    }
    if(AccountData[playerid][pFaction] != FACTION_SAGOV) 
    {
        AccountData[playerid][pTempValue] = -1;
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Pemerintah Kota Pahlawan Roleplay!");
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
        case 0: //premier
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 426;
            PlayerFactionVehicle[playerid][FACTION_SAGOV] = CreateVehicle(426, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 0, 0, 60000, false);
        }
        case 1: //stafford
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 580;
            PlayerFactionVehicle[playerid][FACTION_SAGOV] = CreateVehicle(580, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 1, 1, 60000, false);
        }
        case 2: //stretch
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 409;
            PlayerFactionVehicle[playerid][FACTION_SAGOV] = CreateVehicle(409, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 1, 1, 60000, false);
        }
        case 3: //fbi rancher
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 490;
            PlayerFactionVehicle[playerid][FACTION_SAGOV] = CreateVehicle(490, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 0, 0, 60000, false);
        }
        case 4: //hermes
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 474;
            PlayerFactionVehicle[playerid][FACTION_SAGOV] = CreateVehicle(474, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 1, 1, 60000, false);
        }
    }

    DestroyFactVehToys(PlayerFactionVehicle[playerid][FACTION_SAGOV]);
    FactionVehHasCallsign[PlayerFactionVehicle[playerid][FACTION_SAGOV]] = false;
    LSPDPlayerCallsign[playerid][0] = EOS;

    PlayerFactionVehStats[playerid][pFactVehColor1] = 0;
    PlayerFactionVehStats[playerid][pFactVehColor2] = 0;
    PlayerFactionVehStats[playerid][pFactVehFuel] = 100;
    PlayerFactionVehStats[playerid][pFactVehMaxHealth] = 1000.0;
    PlayerFactionVehStats[playerid][pFactVehBodyUpgraded] = false;
    PlayerFactionVehStats[playerid][pFactVehBodyBroken] = false;
    PlayerFactionVehStats[playerid][pFactVehLocked] = false;

    VehicleCore[PlayerFactionVehicle[playerid][FACTION_SAGOV]][vCoreFuel] = 100;
    SetValidVehicleHealth(PlayerFactionVehicle[playerid][FACTION_SAGOV], 1000.0); 
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_SAGOV]][vMaxHealth] = 1000.0;
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_SAGOV]][vIsBodyUpgraded] = false;
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_SAGOV]][vIsBodyBroken] = false;
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_SAGOV]][vCoreLocked] = false;
    PutPlayerInVehicleEx(playerid, PlayerFactionVehicle[playerid][FACTION_SAGOV], 0);
    SwitchVehicleEngine(PlayerFactionVehicle[playerid][FACTION_SAGOV], true);
    SwitchVehicleDoors(PlayerFactionVehicle[playerid][FACTION_SAGOV], false);

    static string[555];
    mysql_format(g_SQL, string, sizeof(string), "INSERT INTO `demand_vehicles` (`ownerid`, `model`, `vehX`, `vehY`, `vehZ`, `vehA`, `damage0`, `damage1`, `damage2`, `damage3`, `health`, `fuel`, `locked`, `world`, `color1`, `color2`) VALUES (%d, %d, '%f', '%f', '%f', '0.0', 0, 0, 0, 0, '2000.0', %d, %d, 0, %d, %d)", 
    AccountData[playerid][pID],
    PlayerFactionVehStats[playerid][pFactVehModel],
    FactGarageData[garageid][GarageSpawnPos][0],
    FactGarageData[garageid][GarageSpawnPos][1],
    FactGarageData[garageid][GarageSpawnPos][2],
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_SAGOV]][vCoreFuel],
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_SAGOV]][vCoreLocked],
    PlayerFactionVehStats[playerid][pFactVehColor1],
    PlayerFactionVehStats[playerid][pFactVehColor2]);
    mysql_pquery(g_SQL, string);
    return 1;
}

Dialog:ChangeName(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    new tempName[MAX_PLAYER_NAME + 1];

    if(isnull(inputtext)) return SEM(playerid, "Tidak dapat dikosongkan!");
    if(strlen(inputtext) < 4) return SEM(playerid, "The new name cannot be lower than 4 characters!");
    if(strlen(inputtext) > 23) return SEM(playerid, "The new name cannot be more than 23 huruf!");
    
    if(!IsRoleplayName(inputtext)) return SEM(playerid, "Invalid roleplay name format!");
    if(!IsValidName(inputtext)) return SEM(playerid, "The new name include wrong format!");
    
    strcopy(tempName, inputtext);

    new query[248];
    mysql_format(g_SQL, query, sizeof(query), "SELECT `Char_Name` FROM `player_characters` WHERE `Char_Name`='%e'", tempName);
    mysql_pquery(g_SQL, query, "ChangeName", "is", playerid, tempName);
    return 1;
}

Dialog:ChangeNameOrigin(playerid, response, listitem, inputtext[])
{
    if(!response)
	{
        PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		static originstring[3528+1];
		for(new x; x < sizeof(_g_originName); x++)
		{
			format(originstring, sizeof(originstring), "%s%s\n", originstring, _g_originName[x]);
		}
		return Dialog_Show(playerid, "ChangeNameOrigin", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Origin", originstring, "Pilih", "");
	}

	if(listitem == -1 || listitem > sizeof(_g_originName) - 1)
	{
		strcopy(AccountData[playerid][pOrigin], _g_originName[0]);
	}
	else
	{
		strcopy(AccountData[playerid][pOrigin], _g_originName[listitem]);
	}
    
    new query[128];
    mysql_format(g_SQL, query, sizeof(query), "UPDATE `player_characters` SET `Char_Origin`='%e' WHERE `pID`=%d", AccountData[playerid][pOrigin], AccountData[playerid][pID]);
    mysql_pquery(g_SQL, query);

    ShowTDN(playerid, NOTIFICATION_INFO, "Proses pergantian nama telah selesai.");
    return 1;
}

Dialog:PemerintahSetRank(playerid, response, listitem, inputtext[])
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
        Show_PemerintahRankManage(playerid);
    }
    else if(!strcmp(inputtext, "<< Sebelumnya", true)) 
    {
        index_pagination[playerid]--;
        if(index_pagination[playerid] <= 0) {
            index_pagination[playerid] = 0;
        }
        Show_PemerintahRankManage(playerid);
    }
    else 
    {
        if(AccountData[playerid][pFaction] != FACTION_SAGOV) 
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Pemerintah Kota Pahlawan Roleplay!");
        if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Wakil Wali Kota untuk akses faction menu!");

        mysql_query(g_SQL, sprintf("SELECT * FROM `player_characters` WHERE `pID` = '%d'", ListedMember[playerid][listitem]));
        new rows = cache_num_rows();
        if(rows)
        {
            cache_get_value_name_int(0, "pID", AccountData[playerid][pTempSQLFactMemberID]);
            cache_get_value_name_int(0, "Char_FactionRank", AccountData[playerid][pTempSQLFactRank]);
            if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFactMemberID]) return SEM(playerid, "Anda tidak dapat menetapkan rank anda sendiri!");
            if(AccountData[playerid][pTempSQLFactRank] >= AccountData[playerid][pFactionRank]) return SEM(playerid, "Anda tidak dapat menetapkan rank rekan yang sejajar/lebih tinggi dari anda!");
            Dialog_Show(playerid, "PemerintahSetRankConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
            "Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. Honorer\n\
            2. Staff Junior\n\
            3. Staff Senior\n\
            4. Kepala Dinas\n\
            5. Sekretaris\n\
            6. W. Gubernur\n\
            7. Gubernur", "Set", "Batal");
        }
    }
    return 1;
}

Dialog:PemerintahKickMember(playerid, response, listitem, inputtext[])
{
    if (!response)
        return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    if (!strcmp(inputtext, ">> Selanjutnya", true)) {
        index_pagination[playerid]++;
        ShowPemerintahKick(playerid);
    }
    else if (!strcmp(inputtext, "<< Sebelumnya", true)) {
        index_pagination[playerid]--;
        if (index_pagination[playerid] < 0) {
            index_pagination[playerid] = 0;
        }
        ShowPemerintahKick(playerid);
    }
    else 
    {
        new l_row_pid = ListedMember[playerid][listitem];

        if (AccountData[playerid][pFaction] != FACTION_SAGOV)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Pemerintah Kota Pahlawan Roleplay!");

        if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Wakil Wali Kota untuk akses faction menu!");

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

                    if(Iter_Contains(PemerDuty, i))
                        Iter_Remove(PemerDuty, i);

                    ShowTDN(i, NOTIFICATION_WARNING, "Anda telah ditendang dari Pemerintah Kota Pahlawan Roleplay!");
                    break;
                }
            }

            InsertFactionLog("Kick", sprintf("%s %s - %s", AccountData[playerid][pName], AccountData[playerid][pUCP], fckname), "Pemerintah");

            mysql_format(g_SQL, iscr, sizeof(iscr), "UPDATE `player_characters` SET `Char_Faction` = 0, `Char_FactionRank` = 0 WHERE `pID` = %d", l_row_pid);
            mysql_pquery(g_SQL, iscr);

            format(kckstr, sizeof(kckstr), "Anda berhasil mengeluarkan:\n\
            Name: %s\n\
            Rank: %s\n\
            Last Online: %s", fckname, PemerintahRank[fckrank], fcklastlogin);
            Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Kick Faction", kckstr, "Tutup", "");
        }
    }
    return 1;
}