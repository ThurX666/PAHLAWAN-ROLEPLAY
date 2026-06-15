#include <YSI_Coding\y_hooks>

static const LSFDRank[9][] = 
{
	"N/A",
    "PKL", //1
    "Perawat", //2
    "Dokter", //3
	"Dokter Spesialis", //4
	"Profesor", //5
	"WAKADIR", //6
	"SEKBEN", //7
	"Direktur" //8
};

LSFD_ShowBrankas(playerid)
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
        if (FactionBrankas[i][factionBrankasExists] && FactionBrankas[i][factionBrankasFID] == FACTION_LSFD)
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
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "Lemari Paramedis", "Lemari penyimpanan ini kosong!", "Tutup", "");
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

        Dialog_Show(playerid, "ParamedisVaultWithdraw", DIALOG_STYLE_TABLIST_HEADERS, sprintf("Lemari Paramedis: Page %d of %d", curr_page + 1, max_pages),
        string, "Pilih", "Batal");
    }
    return 1;
}

Show_LSFDRankManage(playerid)
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
    mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 2 ORDER BY Char_FactionRank DESC");

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
            strcat(string, sprintf("%s\t%s\t%s\n", member_name[i], LSFDRank[member_rank[i]], member_lastlog[i]));
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

        Dialog_Show(playerid, "LSFDSetRank", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", string, "Pilih", "Batal");
    }
    else
    {
        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", "Faction ini tidak memiliki anggota!", "Tutup", "");
    }
    return 1;
}

stock ShowLSFDKick(playerid) 
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
    mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 2 ORDER BY Char_FactionRank DESC");

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
            strcat(string, sprintf("%s\t%s\t%s\n", member_name[i], LSFDRank[member_rank[i]], member_lastlog[i]));
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

        Dialog_Show(playerid, "LSFDKickMember", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Kick Faction", string, "Pilih", "Batal");
    }
    else
    {
        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Kick Faction", "Faction ini tidak memiliki anggota!", "Tutup", "");
    }
    return 1;
}

stock ShowInjuredList(playerid)
{
    new count = 0;
    new string[1024];
    new curr_page = index_pagination[playerid];
    new curr_idx = MAX_PAGINATION_PAGES * curr_page;
    new real_i = 0;
    new injured_exists[MAX_PAGINATION_PAGES];
    new injured_name[MAX_PAGINATION_PAGES][24];
    new injured_location[MAX_PAGINATION_PAGES][64];
    new injured_id[MAX_PAGINATION_PAGES];
    
    strcat(string, "#\tNama\tLokasi\n");
    
    for (new i = 0; i < MAX_PAGINATION_PAGES; i++) {
        injured_exists[i] = 0;
    }
    
    foreach (new i : Player) if (AccountData[i][pSpawned]) {

        if (AccountData[i][pDelayKnockdownSignalSent] <= gettime()) 
            continue;
        
        if (count >= curr_idx && count < curr_idx + MAX_PAGINATION_PAGES) {
            injured_exists[real_i] = 1;
            injured_id[real_i] = i;
            format(injured_name[real_i], 24, GetPlayerRoleplayName(i));
            
            new Float:x, Float:y, Float:z;
            GetPlayerPos(i, x, y, z);
            format(injured_location[real_i], 64, GetLocation(x, y, z));
            PlayerListitem[playerid][real_i] = i; 
            real_i++;
        }
        count++;
    }
    
    for (new i = 0; i < MAX_PAGINATION_PAGES; i++) {
        if (injured_exists[i]) {
            strcat(string, sprintf("%d\t%s\t%s\n", injured_id[i], injured_name[i], injured_location[i]));
        }
    }
    
    new maxpage = (count + MAX_PAGINATION_PAGES - 1) / MAX_PAGINATION_PAGES;
    if (curr_page > 0) {
        strcat(string, ""RED"<< Sebelumnya");
        strcat(string, "\n");
    }

    if (curr_page < maxpage - 1) {
        strcat(string, ""GREEN">> Selanjutnya");
        strcat(string, "\n");
    }

    if (!count) {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada sinyal pingsan yang masuk!");
    } 
    else {
        Dialog_Show(playerid, "InjuredList", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Sinyal Pingsan", string, "Pilih", "Batal");
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_CTRL_BACK && AccountData[playerid][pFaction] == FACTION_LSFD && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
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

Dialog:ParamedisVault(playerid, response, listitem, inputtext[])
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
                Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari LSFD", 
                "Anda tidak memiliki barang yang dapat disimpan!", "Tutup", "");
            }
            else
            {
                Dialog_Show(playerid, "ParamedisVaultDeposit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari LSFD", str, "Pilih", "Batal");
            }
        }
        case 1: //withdraw
        {
            index_pagination[playerid] = 0;
            LSFD_ShowBrankas(playerid);
        }
    }
    return 1;
}

Dialog:ParamedisVaultDeposit(playerid, response, listitem, inputtext[])
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
    Dialog_Show(playerid, "ParamedisVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari LSFD", 
    shstr, "Input", "Batal");
    return 1;
}
Dialog:ParamedisVaultIn(playerid, response, listitem, inputtext[])
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
        Dialog_Show(playerid, "ParamedisVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari LSFD", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(!IsNumericEx(inputtext))
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nMohon diisi hanya angka!\nMohon masukkan berapa jumlah yang ingin disimpan:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
        Dialog_Show(playerid, "ParamedisVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari LSFD", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(strval(inputtext) < 1 || strval(inputtext) > InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity])
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nJumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin disimpan:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
        Dialog_Show(playerid, "ParamedisVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari LSFD", 
        shstr, "Input", "Batal");
        return 1;
    }

    new quantity = strval(inputtext);

    new invstr[1028];
    mysql_format(g_SQL, shstr, sizeof(shstr), "SELECT * FROM `faction_brankas` WHERE `FID` = %d AND `Item` = '%e'", FACTION_LSFD, InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
    mysql_query(g_SQL, shstr);

    new rows = cache_num_rows();
    if(rows > 0)
    {
        mysql_format(g_SQL, invstr, sizeof(invstr), "UPDATE `faction_brankas` SET `Quantity` = `Quantity` + %d WHERE `FID` = %d AND `Item` = '%e'", quantity, FACTION_LSFD, InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
        mysql_pquery(g_SQL, invstr);

        ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyimpan item tersebut.");

        for(new x; x < MAX_FACTIONS_ITEMS; ++x)
        {
            if(FactionBrankas[x][factionBrankasExists]  && FactionBrankas[x][factionBrankasFID] == FACTION_LSFD && !strcmp(FactionBrankas[x][factionBrankasTemp], InventoryData[playerid][PlayerListitem[playerid][id]][invItem], true))
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
                FactionBrankas[x][factionBrankasFID] = FACTION_LSFD;
                strcopy(FactionBrankas[x][factionBrankasTemp], InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
                FactionBrankas[x][factionBrankasModel] = InventoryData[playerid][PlayerListitem[playerid][id]][invModel];
                FactionBrankas[x][factionBrankasQuant] = quantity;

                mysql_format(g_SQL, invstr, sizeof(invstr), "INSERT INTO `faction_brankas` SET `FID` = %d, `Item`='%e', `Model`=%d, `Quantity`=%d", FACTION_LSFD, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invModel], quantity);
                mysql_pquery(g_SQL, invstr, "OnFactionDeposit", "id", playerid, x);

                break;
            }
        }
    }
    ShowItemBox(playerid, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], sprintf("Removed %dx", quantity), InventoryData[playerid][PlayerListitem[playerid][id]][invModel], 5);
    Inventory_Remove(playerid, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], quantity);
    return 1;
}
Dialog:ParamedisVaultWithdraw(playerid, response, listitem, inputtext[])
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
        LSFD_ShowBrankas(playerid);
    }
    else if(!strcmp(inputtext, "<< Sebelumnya", true)) 
    {
        index_pagination[playerid]--;
        if(index_pagination[playerid] <= 0) {
            index_pagination[playerid] = 0;
        }
        LSFD_ShowBrankas(playerid);
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
        Dialog_Show(playerid, "ParamedisVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari LSFD", 
        shstr, "Input", "Batal");
    }
    return 1;
}
Dialog:ParamedisVaultOut(playerid, response, listitem, inputtext[])
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
        Dialog_Show(playerid, "ParamedisVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari LSFD", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(!IsNumericEx(inputtext))
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Mohon diisi hanya angka!\nMohon masukkan berapa jumlah yang ingin diambil:", FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant]);
        Dialog_Show(playerid, "ParamedisVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari LSFD", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(strval(inputtext) < 1 || strval(inputtext) > FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant])
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Jumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin diambil:", FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant]);
        Dialog_Show(playerid, "ParamedisVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari LSFD", 
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

    InsertFactionVaultLog(playerid, FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], quantity, "LSFD");

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
Dialog:ParamedisLocker(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_LSFD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Paramedis Pahlawan Roleplay!");
    switch(listitem)
    {
        case 0: //toggle duty
        {
            if(AccountData[playerid][pOnDuty])
            {
                //DestoryPlayerFactObject(playerid);

                SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
                AccountData[playerid][pIsUsingUniform] = false;
                AccountData[playerid][pOnDuty] = false;
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda sekarang ~r~off duty.");
                SendTeamMessage(FACTION_LSFD, 0xFF1A1AFF, "(RS) %s %s telah menyelesaikan masa tugas.", GetRankName(playerid), GetPlayerRoleplayName(playerid));
                Iter_Remove(LSFDDuty, playerid);
            }
            else
            {
                if(AccountData[playerid][pGender] == 1)
                {
                    AccountData[playerid][pUniform] = 276;
                    SetPlayerSkin(playerid, 276);
                }
                else
                {
                    AccountData[playerid][pUniform] = 308;
                    SetPlayerSkin(playerid, 308);
                }

                // DestoryPlayerFactObject(playerid);

                // EMSClothing[playerid][0] = CreateDynamicObject(19777, 1353.147460, 1502.041259, 11.309309, 90.099983, 450.000000, 180.000000, -1, -1, -1, 200.00, 200.00); // buat dibaju
                // SetDynamicObjectMaterialText(EMSClothing[playerid][0], 0, "EMT", 60, "Arial", 55, 1, 0xFFFFFF00, 0x00000000, 1);

                // EMSClothing[playerid][1] = CreateDynamicObject(19777, 1354.158447, 1502.051269, 11.269291, 90.099983, 450.000000, 180.000000, -1, -1, -1, 200.00, 200.00); // buat dibaju
                // SetDynamicObjectMaterialText(EMSClothing[playerid][1], 0, "KOTA PAHLAWAN", 140, "Arial", 55, 1, 0xFFFFFF00, 0x00000000, 1);

                // AttachDynamicObjectToPlayer(EMSClothing[playerid][0], playerid, 0.206999, -0.113000, 0.004000, -89.599929, 174.099990, 92.299995);
                // AttachDynamicObjectToPlayer(EMSClothing[playerid][1], playerid, 0.206999, -0.113000, -0.004000, -89.599929, 174.099990, 92.299995);

                AccountData[playerid][pIsUsingUniform] = true;
                AccountData[playerid][pOnDuty] = true;
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda sekarang ~g~on duty.");
                SendTeamMessage(FACTION_LSFD, 0xFF1A1AFF, "(RS) %s %s melapor untuk bertugas.", GetRankName(playerid), GetPlayerRoleplayName(playerid));
                Iter_Add(LSFDDuty, playerid);
            }
        }
        case 1: //change uniform
        {
            if(AccountData[playerid][pGender] == 1)
            {
                Dialog_Show(playerid, "ParamedisUniform", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- LSFD Uniform", 
                "LSFD #1\n\
                "GRAY"LSFD #2\n\
                LSFD #3\n\
                "GRAY"LSFD #4\n\
                LSFD #5\n\
                "GRAY"LSFD #6\n\
                LSFD #7\n\
                "GRAY"LSFD #8\n\
                LSFD #9", "Pilih", "Batal");
            }
            else
            {
                Dialog_Show(playerid, "ParamedisUniform", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- LSFD Uniform", 
                "LSFD #1\n\
                "GRAY"LSFD #2\n\
                LSFD #3\n\
                "GRAY"LSFD #4\n\
                LSFD #5", "Pilih", "Batal");
            }
        }
    }
    return 1;
}
Dialog:ParamedisUniform(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_LSFD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Paramedis Pahlawan Roleplay!");

    //DestoryPlayerFactObject(playerid);

    switch(listitem)
    {
        case 0: AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (70) : (308);
        case 1: 
        {
            AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (276) : (141);
            // if(AccountData[playerid][pGender] == 1)
            // {
            //     EMSClothing[playerid][0] = CreateDynamicObject(19777, 1353.147460, 1502.041259, 11.309309, 90.099983, 450.000000, 180.000000, -1, -1, -1, 200.00, 200.00); // buat dibaju
            //     SetDynamicObjectMaterialText(EMSClothing[playerid][0], 0, "EMT", 60, "Arial", 55, 1, 0xFFFFFF00, 0x00000000, 1);

            //     EMSClothing[playerid][1] = CreateDynamicObject(19777, 1354.158447, 1502.051269, 11.269291, 90.099983, 450.000000, 180.000000, -1, -1, -1, 200.00, 200.00); // buat dibaju
            //     SetDynamicObjectMaterialText(EMSClothing[playerid][1], 0, "KOTA PAHLAWAN", 140, "Arial", 55, 1, 0xFFFFFF00, 0x00000000, 1);

            //     AttachDynamicObjectToPlayer(EMSClothing[playerid][0], playerid, 0.206999, -0.113000, 0.004000, -89.599929, 174.099990, 92.299995);
            //     AttachDynamicObjectToPlayer(EMSClothing[playerid][1], playerid, 0.206999, -0.113000, -0.004000, -89.599929, 174.099990, 92.299995);
            // }
        }
        case 2: AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (275) : (150);
        case 3: AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (274) : (211);
        case 4: AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (228) : (148);
        case 5: AccountData[playerid][pUniform] = 275;
        case 6: AccountData[playerid][pUniform] = 277;
        case 7: AccountData[playerid][pUniform] = 278;
        case 8: AccountData[playerid][pUniform] = 279;
    }
    SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
    AccountData[playerid][pIsUsingUniform] = true;
    return 1;
}
Dialog:ParamedisBosdesk(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_LSFD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Paramedis Pahlawan Roleplay!");
    if(AccountData[playerid][pFactionRank] < 6) return SEM(playerid, "Minimum rank Fire Captain II untuk akses menu faction!");

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

            Dialog_Show(playerid, "ParamedisInviteConfirm", DIALOG_STYLE_TABLIST, "{DA9100}Pahlawan Roleplay "WHITE"- Undang Faction", frmxt, "Pilih", "Batal");
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
            mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 2 ORDER BY Char_FactionRank DESC");

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
                    strcat(string, sprintf("%s\t%s\t%s\n", member_name[i], LSFDRank[member_rank[i]], member_lastlog[i]));
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

                Dialog_Show(playerid, "LSFDSetRank", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", string, "Pilih", "Batal");
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
            ShowLSFDKick(playerid); 
        }
        case 3: //saldo
        {
            new rtx[158];
            format(rtx, sizeof(rtx), "Saldo EMS Kota Pahlawan Roleplay saat ini ialah:\n\
            "DARKGREEN"$%s", FormatMoney(EMSMoneyVault));
            Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- EMS Balance", rtx, "Tutup", "");
        }
        case 4: //deposit saldo
        {
            Dialog_Show(playerid, "ParamedisDepositCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- EMS Deposit", 
            "Mohon masukkan berapa jumlah deposit:", "Input", "Batal");
        }
        case 5: //tarik saldo
        {
            Dialog_Show(playerid, "ParamedisWithdrawCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- EMS Withdraw", 
            "Mohon masukkan berapa jumlah withdraw:", "Input", "Batal");
        }
    }
    return 1;
}
Dialog:ParamedisInviteConfirm(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_LSFD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Paramedis Pahlawan Roleplay!");
    if(AccountData[playerid][pFactionRank] < 6) return SEM(playerid, "Minimum rank Fire Captain II untuk akses menu faction!");

    new targetid = NearestUser[playerid][listitem], icsr[128];
    if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    AccountData[targetid][pFaction] = FACTION_LSFD;
    AccountData[targetid][pFactionRank] = 1;
    mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction` = 2, `Char_FactionRank` = 1 WHERE `pID` = %d", AccountData[targetid][pID]);
    mysql_pquery(g_SQL, icsr);
    ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Anda telah mengundang %s ke faction!", AccountData[targetid][pName]));

    InsertFactionLog("Invite", sprintf("%s %s - %s %s", AccountData[playerid][pName], AccountData[playerid][pUCP], AccountData[targetid][pName], AccountData[targetid][pUCP]), "LSFD");
    return 1;
}
Dialog:ParamedisSetRankConfirm(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_LSFD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Paramedis Pahlawan Roleplay!");
    if(AccountData[playerid][pFactionRank] < 6) return SEM(playerid, "Minimum rank Fire Captain II untuk akses menu faction!");

    if(isnull(inputtext)) return Dialog_Show(playerid, "ParamedisSetRankConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
    "Error: Tidak dapat dikosongkan!\n\
    Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
    1. Training\n\
    2. Perawat\n\
    3. Dokter\n\
    4. Dokter Spesialis\n\
    5. Profesor\n\
    6. WAKADIR\n\
    7. SEKBEN\n\
    8. Direktur", "Set", "Batal");
    
    if(!IsNumericEx(inputtext)) return Dialog_Show(playerid, "ParamedisSetRankConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
    "Error: Masukkan hanya angka!\n\
    Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
    1. Training\n\
    2. Perawat\n\
    3. Dokter\n\
    4. Dokter Spesialis\n\
    5. Profesor\n\
    6. WAKADIR\n\
    7. SEKBEN\n\
    8. Direktur", "Set", "Batal");

    if(strval(inputtext) < 1 || strval(inputtext) > 8) return Dialog_Show(playerid, "ParamedisSetRankConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
    "Error: Tidak dapat diisi dibawah 1 atau lebih tinggi dari jabatan anda!\n\
    Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
    1. Training\n\
    2. Perawat\n\
    3. Dokter\n\
    4. Dokter Spesialis\n\
    5. Profesor\n\
    6. WAKADIR\n\
    7. SEKBEN\n\
    8. Direktur", "Set", "Batal");

    new hjh[128];
    mysql_format(g_SQL, hjh, sizeof(hjh), "UPDATE `player_characters` SET `Char_FactionRank`=%d WHERE `pID`=%d", strval(inputtext), AccountData[playerid][pTempSQLFactMemberID]);
    mysql_pquery(g_SQL, hjh);

    foreach(new i : Player)
    {
        if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && AccountData[playerid][pTempSQLFactMemberID] == AccountData[i][pID])
        {
            AccountData[i][pFactionRank] = strval(inputtext);
            ShowTDN(i, NOTIFICATION_INFO, "Jabatan faction anda telah diperbarui!");
            InsertFactionLog("Set Rank", sprintf("%s %s - %s %s LV %d", AccountData[playerid][pName], AccountData[playerid][pUCP], AccountData[i][pName], AccountData[i][pUCP], strval(inputtext)), "LSFD");
        }
    }

    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah jabatan faction Pemain tersebut!");
    return 1;
}
Dialog:ParamedisDepositCash(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_LSFD) return SEM(playerid, "Anda bukan anggota Paramedis Pahlawan Roleplay!");
    if(AccountData[playerid][pFactionRank] < 6) return SEM(playerid, "Minimum rank Fire Captain II untuk akses menu faction!");
 
    if(isnull(inputtext))
    {
        return Dialog_Show(playerid, "ParamedisDepositCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- EMS Deposit",
        "Error: Tidak dapat dikosongkan!\n\
        Mohon masukkan berapa jumlah deposit:", "Deposit", "Batal");
    }          

    if (!IsNumericEx(inputtext)) return Dialog_Show(playerid, "ParamedisDepositCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- EMS Deposit",
        "Error: Masukkan hanya angka!\n\
        Mohon masukkan berapa jumlah deposit:", "Deposit", "Batal");

    if(strval(inputtext) < 1) return Dialog_Show(playerid, "ParamedisDepositCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- EMS Deposit",
    "Error: Invalid amount, you can't deposit less than $1!\n\
    Mohon masukkan berapa jumlah deposit:", "Deposit", "Batal");

    if(strval(inputtext) > AccountData[playerid][pMoney]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

    TakePlayerMoneyEx(playerid, strval(inputtext));
    EMSMoneyVault += strval(inputtext);

    static frmtmny[128];
    mysql_format(g_SQL, frmtmny, sizeof(frmtmny), "UPDATE `stuffs` SET `emsmoneyvault` = %d WHERE `id` = 0", EMSMoneyVault);
    mysql_pquery(g_SQL, frmtmny);
    ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil deposit $%s untuk Paramedis Pahlawan Roleplay.", FormatMoney(strval(inputtext))));
    return 1;
}

Dialog:ParamedisWithdrawCash(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_LSFD) return SEM(playerid, "Anda bukan anggota Paramedis Pahlawan Roleplay!");
    if(AccountData[playerid][pFactionRank] < 6) return SEM(playerid, "Minimum rank Fire Captain II untuk akses menu faction!");

    if(isnull(inputtext))
    {
        return Dialog_Show(playerid, "ParamedisWithdrawCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- EMS Withdraw",
        "Error: Tidak dapat dikosongkan!\n\
       Mohon masukkan jumlah yang ingin ditarik:", "Withdraw", "Batal");
    }          

    if (!IsNumericEx(inputtext)) return Dialog_Show(playerid, "ParamedisWithdrawCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- EMS Withdraw",
        "Error: Masukkan hanya angka!\n\
       Mohon masukkan jumlah yang ingin ditarik:", "Withdraw", "Batal");

    if(strval(inputtext) < 1) return Dialog_Show(playerid, "ParamedisWithdrawCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- EMS Withdraw",
    "Error: Jumlah tidak valid, anda tidak dapat withdraw kurang dari $1!\n\
   Mohon masukkan jumlah yang ingin ditarik:", "Withdraw", "Batal");

    if(EMSMoneyVault < RoundNegativeToPositive(strval(inputtext))) return SEM(playerid, "Jumlah tidak valid, saldo tidak cukup!");

    EMSMoneyVault -= strval(inputtext);
    GivePlayerMoneyEx(playerid, strval(inputtext));

    static frmtmny[128];
    mysql_format(g_SQL, frmtmny, sizeof(frmtmny), "UPDATE `stuffs` SET `emsmoneyvault` = %d WHERE `id` = 0", EMSMoneyVault);
    mysql_pquery(g_SQL, frmtmny);

    AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], strval(inputtext), "Paramedis");

    ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil withdraw $%s dari Paramedis Pahlawan Roleplay.", FormatMoney(strval(inputtext))));
    return 1;
}
Dialog:ParamedisGarage(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_LSFD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Paramedis Pahlawan Roleplay!");
    switch(listitem)
    {
        case 0: //keluarkan kendaraan
        {
            if(PlayerFactionVehicle[playerid][FACTION_LSFD] != INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah mengeluarkan kendaraan, simpan terlebih dahulu!");

            Dialog_Show(playerid, "ParamedisGarageTakeout", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Keluarkan Kendaraan", 
            "Ambulance\n\
            "GRAY"Firetruck\n\
            Firetruck Ladder\n\
            "GRAY"Premier\n\
            FBI Rancher\n\
            "GRAY"Utility Van\n\
            Sanchez", "Pilih", "Batal");
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
Dialog:ParamedisGarageTakeout(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        AccountData[playerid][pTempValue] = -1;
        return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    }
    if(AccountData[playerid][pFaction] != FACTION_LSFD) 
    {
        AccountData[playerid][pTempValue] = -1;
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Paramedis Pahlawan Roleplay!");
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
        case 0: //ambulance
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 416;
            PlayerFactionVehStats[playerid][pFactVehColor1] = 6;
            PlayerFactionVehStats[playerid][pFactVehColor2] = 128;
            PlayerFactionVehicle[playerid][FACTION_LSFD] = CreateVehicle(416, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 6, 128, 60000, true);

            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][0] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][0], 0, "EMT", 140, "Arial", 55, 1, -282565, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][0], PlayerFactionVehicle[playerid][FACTION_LSFD], -1.289, -2.910, 0.930, 0.000, 0.000, 0.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][1] = CreateDynamicObject(2658,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterial(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][1], 0, 19267, "mapmarkers", "red-2", 0);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][1], PlayerFactionVehicle[playerid][FACTION_LSFD], -1.300, -2.739, 0.870, 360.000, 90.000, 270.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][2] = CreateDynamicObject(2658,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterial(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][2], 0, 19267, "mapmarkers", "red-2", 0);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][2], PlayerFactionVehicle[playerid][FACTION_LSFD], 1.300, -2.789, 0.870, 720.000, 630.000, 90.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][3] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][3], 0, "EMT", 100, "Arial", 75, 1, -282565, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][3], PlayerFactionVehicle[playerid][FACTION_LSFD], 0.009, -1.450, 1.720, 360.000, 90.000, 90.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][4] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][4], 0, "EMERGENCY MEDICAL", 140, "Arial", 25, 1, -282565, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][4], PlayerFactionVehicle[playerid][FACTION_LSFD], 0.019, -1.800, 1.710, 0.000, 90.000, 90.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][5] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][5], 0, "EMT", 140, "Arial", 55, 1, -282565, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][5], PlayerFactionVehicle[playerid][FACTION_LSFD], 1.290, -2.910, 0.950, 900.000, 1260.000, 360.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][6] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][6], 0, "KOTA PAHLAWAN", 140, "Arial", 31, 1, -282565, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][6], PlayerFactionVehicle[playerid][FACTION_LSFD], -1.289, -2.900, 0.750, 0.000, 0.000, 0.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][7] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterial(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][7], 0, 19267, "mapmarkers", "red-2", 0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][7], 0, "KOTA PAHLAWAN", 140, "Arial", 31, 1, -282565, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][7], PlayerFactionVehicle[playerid][FACTION_LSFD], 1.291, -2.900, 0.770, 0.000, 0.000, 540.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][8] = CreateDynamicObject(2643,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterial(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][8], 0, 19655, "mattubes", "greendirt1", 0);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][8], PlayerFactionVehicle[playerid][FACTION_LSFD], 0.000, -1.510, 1.620, 270.000, 0.000, 0.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][9] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][9], 0, "TECHNICIAN", 140, "Arial", 25, 1, -282565, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][9], PlayerFactionVehicle[playerid][FACTION_LSFD], 0.019, -1.940, 1.710, 360.000, 90.000, 90.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][10] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][10], 0, "PAHLAWAN", 140, "Arial", 75, 1, -16751616, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][10], PlayerFactionVehicle[playerid][FACTION_LSFD], 0.009, -2.451, 1.720, 0.000, 90.000, 90.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][11] = CreateDynamicObject(11701,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][11], PlayerFactionVehicle[playerid][FACTION_LSFD], 0.001, 0.890, 1.231, 0.000, 0.000, 0.000);
        }
        case 1: //firetruck semprot
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 407;
            PlayerFactionVehStats[playerid][pFactVehColor1] = 3;
            PlayerFactionVehStats[playerid][pFactVehColor2] = 3;
            PlayerFactionVehicle[playerid][FACTION_LSFD] = CreateVehicle(407, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 3, 3, 60000, true);

            DestroyFactVehToys(PlayerFactionVehicle[playerid][FACTION_LSFD]);
        }
        case 2: //firetruck ladder
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 544;
            PlayerFactionVehStats[playerid][pFactVehColor1] = 3;
            PlayerFactionVehStats[playerid][pFactVehColor2] = 3;
            PlayerFactionVehicle[playerid][FACTION_LSFD] = CreateVehicle(544, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 3, 3, 60000, true);

            DestroyFactVehToys(PlayerFactionVehicle[playerid][FACTION_LSFD]);
        }
        case 3: //Premier
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 426;
            PlayerFactionVehStats[playerid][pFactVehColor1] = 252;
            PlayerFactionVehStats[playerid][pFactVehColor2] = 252;
            PlayerFactionVehicle[playerid][FACTION_LSFD] = CreateVehicle(426, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 3, 3, 60000, true);

            DestroyFactVehToys(PlayerFactionVehicle[playerid][FACTION_LSFD]);
        }
        case 4: //fbi rancher
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 490;
            PlayerFactionVehStats[playerid][pFactVehColor1] = 6;
            PlayerFactionVehStats[playerid][pFactVehColor2] = 128;
            PlayerFactionVehicle[playerid][FACTION_LSFD] = CreateVehicle(490, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 6, 128, 60000, true);

            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][0] = CreateDynamicObject(11701,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][0], PlayerFactionVehicle[playerid][FACTION_LSFD], 0.000, 0.410, 1.130, 0.000, 0.000, 0.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][1] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][1], 0, "EMT", 140, "Arial", 155, 1, -282565, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][1], PlayerFactionVehicle[playerid][FACTION_LSFD], -1.200, -0.306, 0.050, 360.000, 360.000, 1080.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][2] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][2], 0, "EMT", 140, "Arial", 55, 1, -282565, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][2], PlayerFactionVehicle[playerid][FACTION_LSFD], -0.280, -3.168, 0.140, 0.000, 0.000, 450.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][3] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterial(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][3], 0, 19267, "mapmarkers", "red-2", 0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][3], 0, "KOTA PAHLAWAN", 140, "Arial", 31, 1, -282565, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][3], PlayerFactionVehicle[playerid][FACTION_LSFD], -0.300, -3.169, 0.000, 0.000, 0.000, 90.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][4] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterial(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][4], 0, 19267, "mapmarkers", "red-2", 0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][4], 0, "KOTA PAHLAWAN", 140, "Arial", 31, 1, -282565, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][4], PlayerFactionVehicle[playerid][FACTION_LSFD], -1.201, -0.318, -0.210, 0.000, 0.000, 0.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][5] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][5], 0, "EMT", 140, "Arial", 155, 1, -282565, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][5], PlayerFactionVehicle[playerid][FACTION_LSFD], 1.200, -0.216, 0.050, 0.000, 0.000, 180.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][6] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterial(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][6], 0, 19267, "mapmarkers", "red-2", 0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][6], 0, "KOTA PAHLAWAN", 140, "Arial", 31, 1, -282565, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSFD]][6], PlayerFactionVehicle[playerid][FACTION_LSFD], 1.199, -0.228, -0.210, 0.000, 0.000, 180.000);
        }
        case 5: //utility van
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 552;
            PlayerFactionVehStats[playerid][pFactVehColor1] = 3;
            PlayerFactionVehStats[playerid][pFactVehColor2] = 3;
            PlayerFactionVehicle[playerid][FACTION_LSFD] = CreateVehicle(552, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 3, 3, 60000, true);

            DestroyFactVehToys(PlayerFactionVehicle[playerid][FACTION_LSFD]);
        }
        case 6: //sanchez
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 468;
            PlayerFactionVehStats[playerid][pFactVehColor1] = 3;
            PlayerFactionVehStats[playerid][pFactVehColor2] = 3;
            PlayerFactionVehicle[playerid][FACTION_LSFD] = CreateVehicle(468, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 3, 3, 60000, true);
            
            DestroyFactVehToys(PlayerFactionVehicle[playerid][FACTION_LSFD]);
        }
    }

    FactionVehHasCallsign[PlayerFactionVehicle[playerid][FACTION_LSFD]] = false;
    LSPDPlayerCallsign[playerid][0] = EOS;

    PlayerFactionVehStats[playerid][pFactVehFuel] = 100;
    PlayerFactionVehStats[playerid][pFactVehMaxHealth] = 2000.0;
    PlayerFactionVehStats[playerid][pFactVehBodyUpgraded] = true;
    PlayerFactionVehStats[playerid][pFactVehBodyBroken] = false;
    PlayerFactionVehStats[playerid][pFactVehLocked] = false;

    VehicleCore[PlayerFactionVehicle[playerid][FACTION_LSFD]][vCoreFuel] = 100;
    SetValidVehicleHealth(PlayerFactionVehicle[playerid][FACTION_LSFD], 2000.0); 
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_LSFD]][vMaxHealth] = 2000.0;
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_LSFD]][vIsBodyUpgraded] = true;
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_LSFD]][vIsBodyBroken] = false;
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_LSFD]][vCoreLocked] = false;
    PutPlayerInVehicleEx(playerid, PlayerFactionVehicle[playerid][FACTION_LSFD], 0);
    SwitchVehicleEngine(PlayerFactionVehicle[playerid][FACTION_LSFD], true);
    SwitchVehicleDoors(PlayerFactionVehicle[playerid][FACTION_LSFD], false);

    static string[555];
    mysql_format(g_SQL, string, sizeof(string), "INSERT INTO `demand_vehicles` (`ownerid`, `model`, `vehX`, `vehY`, `vehZ`, `vehA`, `damage0`, `damage1`, `damage2`, `damage3`, `health`, `fuel`, `locked`, `world`, `color1`, `color2`) VALUES (%d, %d, '%f', '%f', '%f', '0.0', 0, 0, 0, 0, '2000.0', %d, %d, 0, %d, %d)", 
    AccountData[playerid][pID],
    PlayerFactionVehStats[playerid][pFactVehModel],
    FactGarageData[garageid][GarageSpawnPos][0],
    FactGarageData[garageid][GarageSpawnPos][1],
    FactGarageData[garageid][GarageSpawnPos][2],
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_LSFD]][vCoreFuel],
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_LSFD]][vCoreLocked],
    PlayerFactionVehStats[playerid][pFactVehColor1],
    PlayerFactionVehStats[playerid][pFactVehColor2]);
    mysql_pquery(g_SQL, string);
    return 1;
}
Dialog:ParamedisPanel(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_LSFD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Paramedis Pahlawan Roleplay!");
    new targetid = NearestSingle[playerid];
    if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if(!IsPlayerNearPlayer(playerid, targetid, 3.0)) return SEM(playerid, "Pemain tersebut tidak dekat dengan anda!");
    if(AccountData[playerid][pKnockdown]) return SEM(playerid, "Karakter anda terluka parah saat ini!");
    switch(listitem)
    {
        case 0: //revive
        {
            if(!AccountData[targetid][pKnockdown]) return SEM(playerid, "The player is not injured!");
            if(!PlayerHasItem(playerid, "Medkit")) return SEM(playerid, "You don't have a medkit!");
            if(AccountData[playerid][LSFDDuringReviving]) return SEM(playerid, "You are currently performing a revive on another player!");

            Inventory_Remove(playerid, "Medkit");

            ApplyAnimation(playerid, "MEDIC","CPR", 8.33, true, false, false, true, 0, true);

            AccountData[playerid][pActivityTime] = 1;
            AccountData[playerid][LSFDDuringReviving] = true;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENYEMBUHKAN");
            ShowProgressBar(playerid);

            RevivingPlayerTimer[playerid] = true;
        }
        case 1: //treatment
        {
            SetPlayerHealthEx(targetid, 100);
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Treatment berhasil dilakukan");

            NearestSingle[playerid] = INVALID_PLAYER_ID;
        }
        case 2: //seret
        {
            if(AccountData[playerid][DraggingID] != INVALID_PLAYER_ID)
            {
                AccountData[playerid][DraggingID] = INVALID_PLAYER_ID;
                if(IsPlayerConnected(AccountData[playerid][DraggingID]))
                {
                    AccountData[AccountData[playerid][DraggingID]][pGetDraggedBy] = INVALID_PLAYER_ID;
                }
                TogglePlayerControllable(targetid, true);
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah berhenti menyeret seseorang");
                return 1;
            }

            foreach(new i: Player)
            {
                if(AccountData[i][DraggingID] == playerid) return SEM(playerid, "Anda tidak dapat menyeret seseorang yang sedang menyeret orang lain!");
            }

            AccountData[playerid][DraggingID] = targetid;
            AccountData[targetid][pGetDraggedBy] = playerid;
            TogglePlayerControllable(targetid, false);
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyeret seseorang.");
            NearestSingle[playerid] = INVALID_PLAYER_ID;
        }
        case 3: //borgol
        {
            AccountData[targetid][pCuffed] = true;
            GameTextForPlayer(targetid, "~r~Terborgol", 3500, 3);
            SetPlayerSpecialAction(targetid, SPECIAL_ACTION_CUFFED);
            ShowTDN(targetid, NOTIFICATION_INFO, "Anda telah diborgol!");
            NearestSingle[playerid] = INVALID_PLAYER_ID;
        }
        case 4: //buka borgol
        {
            AccountData[targetid][pCuffed] = false;
            GameTextForPlayer(targetid, "~g~Borgol Dilepas", 3500, 3);
            SetPlayerSpecialAction(targetid, SPECIAL_ACTION_NONE);
            ShowTDN(targetid, NOTIFICATION_INFO, "Borgol anda telah dilepas!");
            NearestSingle[playerid] = INVALID_PLAYER_ID;
        }
        case 5: //Invoice Belum Terbayar
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
        case 6: //invoice manual
        {
            if(!IsPlayerInAnyVehicle(playerid))
            {
                SetPlayerAttachedObject(playerid, 9, 19786, 5, 0.182999, 0.048999, -0.112999, -66.699935, -23.799949, -116.699996, 0.130999, 0.136000, 0.142000, 0, 0);
    		    ApplyAnimation(playerid, "INT_SHOP","shop_loop", 4.1, true, false, false, true, 0, true);
            }

            Dialog_Show(playerid, "InvoiceSetName", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Invoice", 
            "Mohon masukkan nama dari invoice ini:", "Input", "Batal");
        }
        case 7: //periksa
        {
            if(DeathCause[NearestSingle[playerid]][Bruised])
                SendClientMessage(playerid, X11_LIGHTBLUE, "DIAGNOSIS: "WHITE"Orang tersebut diduga pingsan karena memar dipukul dengan "YELLOW"tangan kosong/benda tumpul.");
            if(DeathCause[NearestSingle[playerid]][Shoted])
                SendClientMessage(playerid, X11_LIGHTBLUE, "DIAGNOSIS: "WHITE"Orang tersebut diduga pingsan karena "YELLOW"tertembak senjata api.");
            if(DeathCause[NearestSingle[playerid]][Burns])
                SendClientMessage(playerid, X11_LIGHTBLUE, "DIAGNOSIS: "WHITE"Orang tersebut diduga pingsan karena "YELLOW"luka bakar.");
            if(DeathCause[NearestSingle[playerid]][Drown])
                SendClientMessage(playerid, X11_LIGHTBLUE, "DIAGNOSIS: "WHITE"Orang tersebut diduga pingsan karena "YELLOW"kehabisan nafas/tenggelam.");
            if(DeathCause[NearestSingle[playerid]][Fallen])
                SendClientMessage(playerid, X11_LIGHTBLUE, "DIAGNOSIS: "WHITE"Orang tersebut diduga pingsan karena "YELLOW"terjatuh dari ketinggian.");

            new pentil[512];
            format(pentil, sizeof(pentil), ""WHITE"Name: %s\n\
            "WHITE"Kesehatan: "RED"%.2f\n\
            "WHITE"Lapar: "YELLOW"%d\n\
            "WHITE"Haus: "YELLOW"%d", AccountData[targetid][pName], AccountData[targetid][pHealth], AccountData[targetid][pHunger], AccountData[targetid][pThirst]);
            Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Periksa", pentil, "Tutup", "");
            NearestSingle[playerid] = INVALID_PLAYER_ID;
        }
        case 8: //Detain
        {
            new vehid = GetNearestVehicleToPlayer(playerid, 4.0, false);
            if(vehid != INVALID_VEHICLE_ID)
            {
                if(GetEmptyBackSeat(vehid) == INVALID_SEAT_ID) return SEM(playerid, "Tidak ada kursi kosong di belakang!");
                AccountData[targetid][pDetained] = true;
                PutPlayerInVehicleEx(targetid, vehid, GetEmptyBackSeat(vehid));
                TogglePlayerControllable(targetid, false);
                ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasukkan Pemain tersebut secara paksa.");
            }
            NearestSingle[playerid] = INVALID_PLAYER_ID;
        }
        case 9: //ejected
        {
            if(!AccountData[targetid][pDetained]) return SEM(playerid, "Pemain tersebut tidak sedang di-detain!");
            AccountData[targetid][pDetained] = false;
            TogglePlayerControllable(targetid, true);
            RemovePlayerFromVehicle(targetid);
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menendang Pemain tersebut dari kendaraan.");
            NearestSingle[playerid] = INVALID_PLAYER_ID;
        }
        case 10: //sita senjata
        {
            ResetPlayerWeaponsEx(targetid);
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyita seluruh senjata Pemain tersebut.");
            SIM(targetid, "Seluruh senjata yang anda miliki telah disita oleh "RED"%s [%s] (ID: %d)", AccountData[playerid][pName], AccountData[playerid][pUCP], playerid);

            NearestSingle[playerid] = INVALID_PLAYER_ID;
        }
    }
    return 1;
}

Dialog:LSFDSetRank(playerid, response, listitem, inputtext[])
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
        Show_LSFDRankManage(playerid);
    }
    else if(!strcmp(inputtext, "<< Sebelumnya", true)) 
    {
        index_pagination[playerid]--;
        if(index_pagination[playerid] <= 0) {
            index_pagination[playerid] = 0;
        }
        Show_LSFDRankManage(playerid);
    }
    else 
    {
        if(AccountData[playerid][pFaction] != FACTION_LSFD) 
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Paramedis Pahlawan Roleplay!");
        if(AccountData[playerid][pFactionRank] < 6) return SEM(playerid, "Minimum rank Fire Captain II untuk akses menu faction!");

        mysql_query(g_SQL, sprintf("SELECT * FROM `player_characters` WHERE `pID` = '%d'", ListedMember[playerid][listitem]));
        new rows = cache_num_rows();
        if(rows)
        {
            cache_get_value_name_int(0, "pID", AccountData[playerid][pTempSQLFactMemberID]);
            cache_get_value_name_int(0, "Char_FactionRank", AccountData[playerid][pTempSQLFactRank]);
            if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFactMemberID]) return SEM(playerid, "Anda tidak dapat menetapkan rank anda sendiri!");
            if(AccountData[playerid][pTempSQLFactRank] >= AccountData[playerid][pFactionRank]) return SEM(playerid, "Anda tidak dapat menetapkan rank rekan yang sejajar/lebih tinggi dari anda!");
            Dialog_Show(playerid, "ParamedisSetRankConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
            "Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. Training\n\
            2. Perawat\n\
            3. Dokter\n\
            4. Dokter Spesialis\n\
            5. Profesor\n\
            6. WAKADIR\n\
            7. SEKBEN\n\
            8. Direktur", "Set", "Batal");
        }
    }
    return 1;
}

Dialog:LSFDKickMember(playerid, response, listitem, inputtext[])
{
    if (!response)
        return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    if (!strcmp(inputtext, ">> Selanjutnya", true)) {
        index_pagination[playerid]++;
        ShowLSFDKick(playerid);
    }
    else if (!strcmp(inputtext, "<< Sebelumnya", true)) {
        index_pagination[playerid]--;
        if (index_pagination[playerid] < 0) {
            index_pagination[playerid] = 0;
        }
        ShowLSFDKick(playerid);
    }
    else 
    {
        new l_row_pid = ListedMember[playerid][listitem];

        if (AccountData[playerid][pFaction] != FACTION_LSFD)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Paramedis Pahlawan Roleplay!");

        if(AccountData[playerid][pFactionRank] < 6) return SEM(playerid, "Minimum rank Fire Captain II untuk akses menu faction!");

        mysql_query(g_SQL, sprintf("SELECT * FROM `player_characters` WHERE `pID` = %d", l_row_pid));
        new rows = cache_num_rows();
        if (rows) {

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

                    if(Iter_Contains(LSFDDuty, i))
                        Iter_Remove(LSFDDuty, i);

                    ShowTDN(i, NOTIFICATION_WARNING, "Anda telah ditendang dari Paramedis!");
                    break;
                }
            }

            InsertFactionLog("Kick", sprintf("%s %s - %s", AccountData[playerid][pName], AccountData[playerid][pUCP], fckname), "Paramedis");

            mysql_format(g_SQL, iscr, sizeof(iscr), "UPDATE `player_characters` SET `Char_Faction` = 0, `Char_FactionRank` = 0 WHERE `pID` = %d", l_row_pid);
            mysql_pquery(g_SQL, iscr);

            format(kckstr, sizeof(kckstr), "Anda berhasil mengeluarkan:\n\
            Name: %s\n\
            Rank: %s\n\
            Last Online: %s", fckname, LSFDRank[fckrank], fcklastlogin);
            Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Kick Faction", kckstr, "Tutup", "");
        }
    }
    return 1;
}