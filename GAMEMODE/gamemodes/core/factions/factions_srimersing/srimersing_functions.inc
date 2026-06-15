#include <YSI_Coding\y_hooks>

SriMersing_ShowBrankas(playerid)
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
        if (FactionBrankas[i][factionBrankasExists] && FactionBrankas[i][factionBrankasFID] == FACTION_SRIMERSING)
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
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "Lemari Sri Mersing", "Lemari penyimpanan ini kosong!", "Tutup", "");
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

        Dialog_Show(playerid, "SriMersingWithdraw", DIALOG_STYLE_TABLIST_HEADERS, sprintf("Lemari Sri Mersing: Page %d of %d", curr_page + 1, max_pages),
        string, "Pilih", "Batal");
    }
    return 1;
}

static const PARVRank[11][] = 
{
	"N/A",
	"Magang",
	"Junior",
	"Pelayan",
    "Barista",
	"Senior",
	"Marketing",
	"Supervisor",
	"Manager",
	"Chief Officer",
	"Chief Executive"
};

Show_SriMersingRankManage(playerid)
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
    mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 11 ORDER BY Char_FactionRank DESC");

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
            strcat(string, sprintf("%s\t%s\t%s\n", member_name[i], PARVRank[member_rank[i]], member_lastlog[i]));
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

        Dialog_Show(playerid, "SriMersingSetRank", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", string, "Pilih", "Batal");
    }
    else
    {
        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", "Faction ini tidak memiliki anggota!", "Tutup", "");
    }
    return 1;
}

stock ShowSriMersingKick(playerid) 
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
    mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 11 ORDER BY Char_FactionRank DESC");

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
            strcat(string, sprintf("%s\t%s\t%s\n", member_name[i], PARVRank[member_rank[i]], member_lastlog[i]));
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

        Dialog_Show(playerid, "SriMersingKickMember", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Kick Faction", string, "Pilih", "Batal");
    }
    else
    {
        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Kick Faction", "Faction ini tidak memiliki anggota!", "Tutup", "");
    }
    return 1;
}

forward CookingSriMersing(playerid, cookid);
public CookingSriMersing(playerid, cookid)
{
    switch(cookid)
    {
        case 0: //Buckshot Special
        {
            Inventory_Add(playerid, "Buckshot Special", 2663);
            ShowItemBox(playerid, "Buckshot Special", "Received 1x", 2663, 5);
        }
        case 1: // frenchy velty
        {
            Inventory_Add(playerid, "Frenchy Velty", 2663);
            ShowItemBox(playerid, "Frenchy Velty", "Received 1x", 2663, 5);
        }
    }
    AccountData[playerid][pActivityTime] = 0;
    StopRunningAnimation(playerid);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_CTRL_BACK && AccountData[playerid][pFaction] == FACTION_SRIMERSING && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
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

Dialog:SriMersingVault(playerid, response, listitem, inputtext[])
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
                Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Sri Mersing", 
                "Anda tidak memiliki barang yang dapat disimpan!", "Tutup", "");
            }
            else
            {
                Dialog_Show(playerid, "SriMersingDeposit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Sri Mersing", str, "Pilih", "Batal");
            }
        }
        case 1: //withdraw
        {
            if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Marketing untuk akses vault menu!");
            index_pagination[playerid] = 0;
            SriMersing_ShowBrankas(playerid);
        }
    }
    return 1;
}

Dialog:SriMersingDeposit(playerid, response, listitem, inputtext[])
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
    Dialog_Show(playerid, "SriMersingIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Sri Mersing", 
    shstr, "Input", "Batal");
    return 1;
}
Dialog:SriMersingIn(playerid, response, listitem, inputtext[])
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
        Dialog_Show(playerid, "SriMersingIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Sri Mersing", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(!IsNumericEx(inputtext))
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nMohon diisi hanya angka!\nMohon masukkan berapa jumlah yang ingin disimpan:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
        Dialog_Show(playerid, "SriMersingIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Sri Mersing", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(strval(inputtext) < 1 || strval(inputtext) > InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity])
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nJumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin disimpan:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
        Dialog_Show(playerid, "SriMersingIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Sri Mersing", 
        shstr, "Input", "Batal");
        return 1;
    }

    new quantity = strval(inputtext);

    new invstr[1028];
    mysql_format(g_SQL, shstr, sizeof(shstr), "SELECT * FROM `faction_brankas` WHERE `FID` = %d AND `Item` = '%e'", FACTION_SRIMERSING, InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
    mysql_query(g_SQL, shstr);

    new rows = cache_num_rows();
    if(rows > 0)
    {
        mysql_format(g_SQL, invstr, sizeof(invstr), "UPDATE `faction_brankas` SET `Quantity` = `Quantity` + %d WHERE `FID` = %d AND `Item` = '%e'", quantity, FACTION_SRIMERSING, InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
        mysql_pquery(g_SQL, invstr);

        ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyimpan item tersebut.");

        for(new x; x < MAX_FACTIONS_ITEMS; ++x)
        {
            if(FactionBrankas[x][factionBrankasExists]  && FactionBrankas[x][factionBrankasFID] == FACTION_SRIMERSING && !strcmp(FactionBrankas[x][factionBrankasTemp], InventoryData[playerid][PlayerListitem[playerid][id]][invItem], true))
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
                FactionBrankas[x][factionBrankasFID] = FACTION_SRIMERSING;
                strcopy(FactionBrankas[x][factionBrankasTemp], InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
                FactionBrankas[x][factionBrankasModel] = InventoryData[playerid][PlayerListitem[playerid][id]][invModel];
                FactionBrankas[x][factionBrankasQuant] = quantity;

                mysql_format(g_SQL, invstr, sizeof(invstr), "INSERT INTO `faction_brankas` SET `FID` = %d, `Item`='%e', `Model`=%d, `Quantity`=%d", FACTION_SRIMERSING, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invModel], quantity);
                mysql_pquery(g_SQL, invstr, "OnFactionDeposit", "id", playerid, x);

                break;
            }
        }
    }
    ShowItemBox(playerid, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], sprintf("Removed %dx", quantity), InventoryData[playerid][PlayerListitem[playerid][id]][invModel], 5);
    Inventory_Remove(playerid, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], quantity);
    return 1;
}

Dialog:SriMersingWithdraw(playerid, response, listitem, inputtext[])
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
        SriMersing_ShowBrankas(playerid);
    }
    else if(!strcmp(inputtext, "<< Sebelumnya", true)) 
    {
        index_pagination[playerid]--;
        if(index_pagination[playerid] <= 0) {
            index_pagination[playerid] = 0;
        }
        SriMersing_ShowBrankas(playerid);
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
        Dialog_Show(playerid, "SriMersingOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Sri Mersing", 
        shstr, "Input", "Batal");
    }
    return 1;
}

Dialog:SriMersingOut(playerid, response, listitem, inputtext[])
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
        Dialog_Show(playerid, "SriMersingOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Sri Mersing", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(!IsNumericEx(inputtext))
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Mohon diisi hanya angka!\nMohon masukkan berapa jumlah yang ingin diambil:", FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant]);
        Dialog_Show(playerid, "SriMersingOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Sri Mersing", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(strval(inputtext) < 1 || strval(inputtext) > FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant])
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Jumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin diambil:", FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant]);
        Dialog_Show(playerid, "SriMersingOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Sri Mersing", 
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
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah memiliki Obeng!");
        }
        else
        {
            if(quantity > 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat membawa lebih dari satu Obeng!"); 
        }
    }
    if(!strcmp(FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], "Cangkul")) 
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

    InsertFactionVaultLog(playerid, FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], quantity, "SriMersing");

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

Dialog:SriMersingLocker(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_SRIMERSING) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Sri Mersing Resto!");
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
                Iter_Remove(SriMersingDuty, playerid);
            }
            else
            {
                if(AccountData[playerid][pGender] == 1)
                {
                    AccountData[playerid][pUniform] = 240;
                    SetPlayerSkin(playerid, 240);
                }
                else
                {
                    AccountData[playerid][pUniform] = 172;
                    SetPlayerSkin(playerid, 172);
                }
                AccountData[playerid][pIsUsingUniform] = true;
                AccountData[playerid][pOnDuty] = true;
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda sekarang ~g~on duty.");
                Iter_Add(SriMersingDuty, playerid);
            }
        }
        case 1: //baju SriMersing
        {
            Dialog_Show(playerid, "SriMersingUniform", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Sri Mersing Uniform", 
            "Sri Mersing 1\n\
            "GRAY"Sri Mersing 2", "Pilih", "Batal");
        }
    }
    return 1;
}
Dialog:SriMersingUniform(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_SRIMERSING) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Sri Mersing Resto!");

    switch(listitem)
    {
        case 0: AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (240) : (172);
        case 1: AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (217) : (211);
    }
    SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
    AccountData[playerid][pIsUsingUniform] = true;
    return 1;
}
Dialog:SriMersingBosDesk(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_SRIMERSING) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Sri Mersing Resto!");
    if(AccountData[playerid][pFactionRank] < 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank faction adalah Supervisor untuk akses ini!");

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

            Dialog_Show(playerid, "SriMersingInviteConfirm", DIALOG_STYLE_TABLIST, "{DA9100}Pahlawan Roleplay "WHITE"- Undang Faction", frmxt, "Pilih", "Batal");
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
            mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 11 ORDER BY Char_FactionRank DESC");

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
                    strcat(string, sprintf("%s\t%s\t%s\n", member_name[i], PARVRank[member_rank[i]], member_lastlog[i]));
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

                Dialog_Show(playerid, "SriMersingSetRank", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", string, "Pilih", "Batal");
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
            ShowSriMersingKick(playerid); 
        }
        case 3: //saldo
        {
            new rtx[158];
            format(rtx, sizeof(rtx), "Saldo Sri Mersing saat ini ialah:\n\
            "DARKGREEN"$%s", FormatMoney(SriMersingMoneyVault));
            Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Sri Mersing Balance", rtx, "Tutup", "");
        }
        case 4: //deposit saldo
        {
            Dialog_Show(playerid, "SriMersingDepositCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Sri Mersing Deposit", 
            "Mohon masukkan berapa jumlah deposit:", "Input", "Batal");
        }
        case 5: //tarik saldo
        {
            Dialog_Show(playerid, "SriMersingWithdrawCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Sri Mersing Withdraw", 
            "Mohon masukkan berapa jumlah withdraw:", "Input", "Batal");
        }
    }
    return 1;
}
Dialog:SriMersingInviteConfirm(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_SRIMERSING) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Sri Mersing Resto!");
    if(AccountData[playerid][pFactionRank] < 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank faction adalah Supervisor untuk akses ini!");

    new targetid = NearestUser[playerid][listitem], icsr[128];
    if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    AccountData[targetid][pFaction] = FACTION_SRIMERSING;
    AccountData[targetid][pFactionRank] = 1;
    mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction` = 11, `Char_FactionRank` = 1 WHERE `pID` = %d", AccountData[targetid][pID]);
    mysql_pquery(g_SQL, icsr);
    ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Anda telah mengundang %s ke faction!", AccountData[targetid][pName]));

    InsertFactionLog("Invite", sprintf("%s %s - %s %s", AccountData[playerid][pName], AccountData[playerid][pUCP], AccountData[targetid][pName], AccountData[targetid][pUCP]), "SriMersing");
    return 1;
}
Dialog:SMSetRankConfirm(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_SRIMERSING) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Sri Mersing Resto!");
    if(AccountData[playerid][pFactionRank] < 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank faction adalah Supervisor untuk akses ini!");

    if(isnull(inputtext)) return Dialog_Show(playerid, "SMSetRankConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
    "Error: Tidak dapat dikosongkan!\n\
    Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
    1. Magang\n\
    2. Junior\n\
    3. Pelayan\n\
    4. Barista\n\
    5. Senior\n\
    6. Marketing\n\
    7. Supervisor\n\
    8. Manager\n\
    9. Chief Officer\n\
    10. Chief Executive", "Set", "Batal");
    
    if(!IsNumericEx(inputtext)) return Dialog_Show(playerid, "SMSetRankConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
    "Error: Masukkan hanya angka!\n\
    Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
    1. Magang\n\
    2. Junior\n\
    3. Pelayan\n\
    4. Barista\n\
    5. Senior\n\
    6. Marketing\n\
    7. Supervisor\n\
    8. Manager\n\
    9. Chief Officer\n\
    10. Chief Executive", "Set", "Batal");

    if(strval(inputtext) < 1 || strval(inputtext) > 10) return Dialog_Show(playerid, "SMSetRankConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
    "Error: Tidak dapat diisi dibawah 1 atau lebih tinggi dari jabatan anda!\n\
    Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
    1. Magang\n\
    2. Junior\n\
    3. Pelayan\n\
    4. Barista\n\
    5. Senior\n\
    6. Marketing\n\
    7. Supervisor\n\
    8. Manager\n\
    9. Chief Officer\n\
    10. Chief Executive", "Set", "Batal");

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
Dialog:SriMersingDepositCash(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_SRIMERSING) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Sri Mersing Resto!");
    if(AccountData[playerid][pFactionRank] < 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank faction adalah Supervisor untuk akses ini!");
    
    if(isnull(inputtext))
    {
        return Dialog_Show(playerid, "SriMersingDepositCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Sri Mersing Deposit",
        "Error: Tidak dapat dikosongkan!\n\
        Mohon masukkan berapa jumlah deposit:", "Deposit", "Batal");
    }          

    if (!IsNumericEx(inputtext)) return Dialog_Show(playerid, "SriMersingDepositCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Sri Mersing Deposit",
        "Error: Masukkan hanya angka!\n\
        Mohon masukkan berapa jumlah deposit:", "Deposit", "Batal");

    if(strval(inputtext) < 1) return Dialog_Show(playerid, "SriMersingDepositCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Sri Mersing Deposit",
    "Error: Invalid amount, you can't deposit less than $1!\n\
    Mohon masukkan berapa jumlah deposit:", "Deposit", "Batal");

    if(strval(inputtext) > AccountData[playerid][pMoney]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

    TakePlayerMoneyEx(playerid, strval(inputtext));
    SriMersingMoneyVault += strval(inputtext);

    static frmtmny[128];
    mysql_format(g_SQL, frmtmny, sizeof(frmtmny), "UPDATE `stuffs` SET `srimersingmoneyvault` = %d WHERE `id` = 0", SriMersingMoneyVault);
    mysql_pquery(g_SQL, frmtmny);
    ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil deposit $%s untuk Sri Mersing", FormatMoney(strval(inputtext))));
    return 1;
}

Dialog:SriMersingWithdrawCash(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_SRIMERSING) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Sri Mersing Resto!");
    if(AccountData[playerid][pFactionRank] < 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank faction adalah Supervisor untuk akses ini!");

    if(isnull(inputtext))
    {
        return Dialog_Show(playerid, "SriMersingWithdrawCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Sri Mersing Withdraw",
        "Error: Tidak dapat dikosongkan!\n\
       Mohon masukkan jumlah yang ingin ditarik:", "Withdraw", "Batal");
    }          

    if (!IsNumericEx(inputtext)) return Dialog_Show(playerid, "SriMersingWithdrawCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Sri Mersing Withdraw",
        "Error: Masukkan hanya angka!\n\
       Mohon masukkan jumlah yang ingin ditarik:", "Withdraw", "Batal");

    if(strval(inputtext) < 1) return Dialog_Show(playerid, "SriMersingWithdrawCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Sri Mersing Withdraw",
    "Error: Jumlah tidak valid, anda tidak dapat withdraw kurang dari $1!\n\
   Mohon masukkan jumlah yang ingin ditarik:", "Withdraw", "Batal");

    if(SriMersingMoneyVault < RoundNegativeToPositive(strval(inputtext))) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid, saldo tidak cukup!");

    SriMersingMoneyVault -= strval(inputtext);
    GivePlayerMoneyEx(playerid, strval(inputtext));

    static frmtmny[128];
    mysql_format(g_SQL, frmtmny, sizeof(frmtmny), "UPDATE `stuffs` SET `srimersingmoneyvault` = %d WHERE `id` = 0", SriMersingMoneyVault);
    mysql_pquery(g_SQL, frmtmny);

    AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], strval(inputtext), "SriMersing");

    ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil withdraw $%s dari Sri Mersing",FormatMoney(strval(inputtext))));
    return 1;
}
Dialog:SriMersingGarage(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_SRIMERSING) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Sri Mersing Resto!");
    switch(listitem)
    {
        case 0: //keluarkan kendaraan
        {
            if(PlayerFactionVehicle[playerid][FACTION_SRIMERSING] != INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah mengeluarkan kendaraan, simpan terlebih dahulu!");

            Dialog_Show(playerid, "SriMersingGarageTakeout", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Keluarkan Kendaraan", 
            "Hotdog\n\
            "GRAY"Pizzaboy", "Pilih", "Batal");
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
Dialog:SriMersingGarageTakeout(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        AccountData[playerid][pTempValue] = -1;
        return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    }
    if(AccountData[playerid][pFaction] != FACTION_SRIMERSING) 
    {
        AccountData[playerid][pTempValue] = -1;
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Sri Mersing Resto!");
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
        case 0: //hotdog
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 588;
            PlayerFactionVehicle[playerid][FACTION_SRIMERSING] = CreateVehicle(588, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 6, 6, 60000, true);
        }
        case 1: //pizzaboy
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 448;
            PlayerFactionVehicle[playerid][FACTION_SRIMERSING] = CreateVehicle(448, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 6, 6, 60000, true);
        }
    }

    DestroyFactVehToys(PlayerFactionVehicle[playerid][FACTION_SRIMERSING]);
    FactionVehHasCallsign[PlayerFactionVehicle[playerid][FACTION_SRIMERSING]] = false;
    LSPDPlayerCallsign[playerid][0] = EOS;

    PlayerFactionVehStats[playerid][pFactVehColor1] = 6;
    PlayerFactionVehStats[playerid][pFactVehColor2] = 6;
    PlayerFactionVehStats[playerid][pFactVehFuel] = 100;
    PlayerFactionVehStats[playerid][pFactVehMaxHealth] = 1000.0;
    PlayerFactionVehStats[playerid][pFactVehBodyUpgraded] = false;
    PlayerFactionVehStats[playerid][pFactVehBodyBroken] = false;
    PlayerFactionVehStats[playerid][pFactVehLocked] = false;

    VehicleCore[PlayerFactionVehicle[playerid][FACTION_SRIMERSING]][vCoreFuel] = 100;
    SetValidVehicleHealth(PlayerFactionVehicle[playerid][FACTION_SRIMERSING], 1000.0); 
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_SRIMERSING]][vMaxHealth] = 1000.0;
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_SRIMERSING]][vIsBodyUpgraded] = false;
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_SRIMERSING]][vIsBodyBroken] = false;
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_SRIMERSING]][vCoreLocked] = false;
    PutPlayerInVehicleEx(playerid, PlayerFactionVehicle[playerid][FACTION_SRIMERSING], 0);
    SwitchVehicleEngine(PlayerFactionVehicle[playerid][FACTION_SRIMERSING], true);
    SwitchVehicleDoors(PlayerFactionVehicle[playerid][FACTION_SRIMERSING], false);

    static string[555];
    mysql_format(g_SQL, string, sizeof(string), "INSERT INTO `demand_vehicles` (`ownerid`, `model`, `vehX`, `vehY`, `vehZ`, `vehA`, `damage0`, `damage1`, `damage2`, `damage3`, `health`, `fuel`, `locked`, `world`, `color1`, `color2`) VALUES (%d, %d, '%f', '%f', '%f', '0.0', 0, 0, 0, 0, '2000.0', %d, %d, 0, %d, %d)", 
    AccountData[playerid][pID],
    PlayerFactionVehStats[playerid][pFactVehModel],
    FactGarageData[garageid][GarageSpawnPos][0],
    FactGarageData[garageid][GarageSpawnPos][1],
    FactGarageData[garageid][GarageSpawnPos][2],
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_SRIMERSING]][vCoreFuel],
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_SRIMERSING]][vCoreLocked],
    PlayerFactionVehStats[playerid][pFactVehColor1],
    PlayerFactionVehStats[playerid][pFactVehColor2]);
    mysql_pquery(g_SQL, string);
    return 1;
}
Dialog:SriMersingPanel(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_SRIMERSING) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Sri Mersing Resto!");
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
Dialog:SriMersingCooking(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_SRIMERSING) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Sri Mersing Resto!");
    switch(listitem)
    {
        case 0: //Buckshot Special
        {
            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

            AccountData[playerid][pActivityTime] = 1;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMASAK");
            ShowProgressBar(playerid);

            pSriMersingCookingTimer[playerid] = true;
            AccountData[playerid][pTempValue2] = 0;

            ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, 1, 0, 0, 0, 0, 1);
        }
        case 1: //frenchy velty
        {
            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

            AccountData[playerid][pActivityTime] = 1;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMASAK");
            ShowProgressBar(playerid);

            pSriMersingCookingTimer[playerid] = true;
            AccountData[playerid][pTempValue2] = 1;

            ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, 1, 0, 0, 0, 0, 1);
        }
    }
    return 1;
}

Dialog:SriMersingSetRank(playerid, response, listitem, inputtext[])
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
        Show_SriMersingRankManage(playerid);
    }
    else if(!strcmp(inputtext, "<< Sebelumnya", true)) 
    {
        index_pagination[playerid]--;
        if(index_pagination[playerid] <= 0) {
            index_pagination[playerid] = 0;
        }
        Show_SriMersingRankManage(playerid);
    }
    else 
    {
        if(AccountData[playerid][pFaction] != FACTION_SRIMERSING) 
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Sri Mersing Resto!");
        if(AccountData[playerid][pFactionRank] < 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank faction adalah Supervisor untuk akses ini!");

        mysql_query(g_SQL, sprintf("SELECT * FROM `player_characters` WHERE `pID` = '%d'", ListedMember[playerid][listitem]));
        new rows = cache_num_rows();
        if(rows)
        {
            cache_get_value_name_int(0, "pID", AccountData[playerid][pTempSQLFactMemberID]);
            cache_get_value_name_int(0, "Char_FactionRank", AccountData[playerid][pTempSQLFactRank]);
            if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFactMemberID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menetapkan rank anda sendiri!");
            if(AccountData[playerid][pTempSQLFactRank] >= AccountData[playerid][pFactionRank]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menetapkan rank rekan yang sejajar/lebih tinggi dari anda!");
            Dialog_Show(playerid, "SMSetRankConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
            "Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. Magang\n\
            2. Junior\n\
            3. Pelayan\n\
            4. Barista\n\
            5. Senior\n\
            6. Marketing\n\
            7. Supervisor\n\
            8. Manager\n\
            9. Chief Officer\n\
            10. Chief Executive", "Set", "Batal");
        }
    }
    return 1;
}

Dialog:SriMersingKickMember(playerid, response, listitem, inputtext[])
{
    if (!response)
        return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    if (!strcmp(inputtext, ">> Selanjutnya", true)) 
    {
        index_pagination[playerid]++;
        ShowSriMersingKick(playerid);
    }
    else if (!strcmp(inputtext, "<< Sebelumnya", true)) 
    {
        index_pagination[playerid]--;
        if (index_pagination[playerid] < 0) 
        {
            index_pagination[playerid] = 0;
        }
        ShowSriMersingKick(playerid);
    }
    else 
    {
        new l_row_pid = ListedMember[playerid][listitem];

        if (AccountData[playerid][pFaction] != FACTION_SRIMERSING)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Sri Mersing Resto!");

        if(AccountData[playerid][pFactionRank] < 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank faction adalah Supervisor untuk akses ini!");

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

                    if(Iter_Contains(SriMersingDuty, i))
                        Iter_Remove(SriMersingDuty, i);

                    ShowTDN(i, NOTIFICATION_WARNING, "Anda telah ditendang dari Sri Mersing!");
                    break;
                }
            }

            InsertFactionLog("Kick", sprintf("%s %s - %s", AccountData[playerid][pName], AccountData[playerid][pUCP], fckname), "SriMersing");

            mysql_format(g_SQL, iscr, sizeof(iscr), "UPDATE `player_characters` SET `Char_Faction` = 0, `Char_FactionRank` = 0 WHERE `pID` = %d", l_row_pid);
            mysql_pquery(g_SQL, iscr);

            format(kckstr, sizeof(kckstr), "Anda berhasil mengeluarkan:\n\
            Name: %s\n\
            Rank: %s\n\
            Last Online: %s", fckname, PARVRank[fckrank], fcklastlogin);
            Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Kick Faction", kckstr, "Tutup", "");
        }
    }
    return 1;
}