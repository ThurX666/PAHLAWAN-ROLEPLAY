#include <YSI_Coding\y_hooks>

#define MAX_GUDANG 100
#define MAX_GUDANG_ITEMS 100

enum e_gudangdetails
{
    gudangName[34],
    gudangCost,
    Float:gudangPos[3],
    gudangWorld,
    gudangInterior,

    //not save
    STREAMER_TAG_PICKUP:gudangPickup,
    STREAMER_TAG_3D_TEXT_LABEL:gudangLabel,
    STREAMER_TAG_MAP_ICON:gudangMapIcon
};
new GudangData[MAX_GUDANG][e_gudangdetails],
    Iterator:Gudangs<MAX_GUDANG>;

enum e_gudangbrankas
{
    gudangBrankasID,
    gudangBrankasOwner,
    gudangBrankasTemp[32],
    gudangBrankasModel,
    gudangBrankasQuant,

    //not saved
    bool:gudangBrankasExists
};
new GudangBrankas[MAX_PLAYERS][MAX_GUDANG_ITEMS][e_gudangbrankas];

Gudang_Nearest(playerid)
{
    foreach(new i : Gudangs) if (IsPlayerInRangeOfPoint(playerid, 2.0, GudangData[i][gudangPos][0], GudangData[i][gudangPos][1], GudangData[i][gudangPos][2]))
	{
		if (GetPlayerInterior(playerid) == GudangData[i][gudangInterior] && GetPlayerVirtualWorld(playerid) == GudangData[i][gudangWorld])
			return i;
	}
	return -1;
}

Gudang_Save(gdgid)
{
    new sfstr[258];
    mysql_format(g_SQL, sfstr, sizeof(sfstr), "UPDATE `gudang` SET `Name`='%e', `Cost_30Day`=%d, `PosX`='%f', `PosY`='%f', `PosZ`='%f', `World`=%d, `Interior`=%d WHERE `ID`=%d", 
    GudangData[gdgid][gudangName], GudangData[gdgid][gudangCost], GudangData[gdgid][gudangPos][0], GudangData[gdgid][gudangPos][1], GudangData[gdgid][gudangPos][2], GudangData[gdgid][gudangWorld], GudangData[gdgid][gudangInterior], gdgid);
    mysql_pquery(g_SQL, sfstr);
    return 1;
}

Gudang_Rebuild(gdgid)
{
    if(gdgid != -1)
    {
        GudangData[gdgid][gudangPickup] = CreateDynamicPickup(19134, 23, GudangData[gdgid][gudangPos][0], GudangData[gdgid][gudangPos][1], GudangData[gdgid][gudangPos][2], GudangData[gdgid][gudangWorld], GudangData[gdgid][gudangInterior], -1, 30.00, -1, 0);
        
        new gdgsr[158];
        format(gdgsr, sizeof(gdgsr), "| %s |\n[Tekan "GREEN"Y "WHITE"untuk akses gudang]", GudangData[gdgid][gudangName]);
        GudangData[gdgid][gudangLabel] = CreateDynamic3DTextLabel(gdgsr, Y_WHITE, GudangData[gdgid][gudangPos][0], GudangData[gdgid][gudangPos][1], GudangData[gdgid][gudangPos][2] + 0.55, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, GudangData[gdgid][gudangWorld], GudangData[gdgid][gudangInterior], -1, 10.00, -1, 0);
        GudangData[gdgid][gudangMapIcon] = CreateDynamicMapIcon(GudangData[gdgid][gudangPos][0], GudangData[gdgid][gudangPos][1], GudangData[gdgid][gudangPos][2], 16, 0, GudangData[gdgid][gudangWorld], GudangData[gdgid][gudangInterior], -1, 1000.00, MAPICON_LOCAL, -1, 0);
    }
    return 1;
}

Gudang_Refresh(gdgid)
{
    if(gdgid != -1)
    {
        Streamer_SetItemPos(STREAMER_TYPE_PICKUP, GudangData[gdgid][gudangPickup], GudangData[gdgid][gudangPos][0], GudangData[gdgid][gudangPos][1], GudangData[gdgid][gudangPos][2]);
        Streamer_SetIntData(STREAMER_TYPE_PICKUP, GudangData[gdgid][gudangPickup], E_STREAMER_WORLD_ID, GudangData[gdgid][gudangWorld]);
        Streamer_SetIntData(STREAMER_TYPE_PICKUP, GudangData[gdgid][gudangPickup], E_STREAMER_INTERIOR_ID, GudangData[gdgid][gudangInterior]);

        Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, GudangData[gdgid][gudangLabel], GudangData[gdgid][gudangPos][0], GudangData[gdgid][gudangPos][1], GudangData[gdgid][gudangPos][2] + 0.55);
        Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, GudangData[gdgid][gudangLabel], E_STREAMER_WORLD_ID, GudangData[gdgid][gudangWorld]);
        Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, GudangData[gdgid][gudangLabel], E_STREAMER_INTERIOR_ID, GudangData[gdgid][gudangInterior]);
        new gdgsr[158];
        format(gdgsr, sizeof(gdgsr), "| %s |\n[Tekan "GREEN"Y "WHITE"untuk akses gudang]", GudangData[gdgid][gudangName]);
        UpdateDynamic3DTextLabelText(GudangData[gdgid][gudangLabel], Y_WHITE, gdgsr);

        Streamer_SetItemPos(STREAMER_TYPE_MAP_ICON, GudangData[gdgid][gudangMapIcon], GudangData[gdgid][gudangPos][0], GudangData[gdgid][gudangPos][1], GudangData[gdgid][gudangPos][2]);
        Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, GudangData[gdgid][gudangMapIcon], E_STREAMER_WORLD_ID, GudangData[gdgid][gudangWorld]);
        Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, GudangData[gdgid][gudangMapIcon], E_STREAMER_INTERIOR_ID, GudangData[gdgid][gudangInterior]);
    }
    return 1;
}

Float:GetGudangTotalWeightFloat(playerid)
{
	new totalweights, Float:totalweights2;

    for(new x; x < MAX_GUDANG_ITEMS; x++)
    {
        if(GudangBrankas[playerid][x][gudangBrankasExists] && GudangBrankas[playerid][x][gudangBrankasOwner] == AccountData[playerid][pID])
        {
            totalweights += GetItemWeight(GudangBrankas[playerid][x][gudangBrankasTemp]) * GudangBrankas[playerid][x][gudangBrankasQuant];
        }
    }
    totalweights2 = float(totalweights)/1000;
    return totalweights2;
}

static bool:IsGudangItemValid(playerid, slot)
{
    new bool:itemExists = false;
    for(new i = 0; i < sizeof(g_aInventoryItems); i++) 
    {
        // Kalau item-nya ada, ganti itemExists
        if(!strcmp(GudangBrankas[playerid][slot][gudangBrankasTemp], g_aInventoryItems[i][e_InventoryItem], true)) {
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
        GudangBrankas[playerid][slot][gudangBrankasExists] = false;
        GudangBrankas[playerid][slot][gudangBrankasModel] = 0;
        GudangBrankas[playerid][slot][gudangBrankasQuant] = 0;
 
        GudangBrankas[playerid][slot][gudangBrankasTemp][0] = EOS;
 
        static invstr[555];
        mysql_format(g_SQL, invstr, sizeof(invstr), "DELETE FROM `gudang_brankas` WHERE `ID`=%d", GudangBrankas[playerid][slot][gudangBrankasID]);
        mysql_pquery(g_SQL, invstr);
    }
 
    return itemExists;
}

forward LoadGudangBrankas(playerid);
public LoadGudangBrankas(playerid)
{
    if(cache_num_rows() > 0)
    {
        new totalInvalidItems = 0;
        for(new x; x < cache_num_rows(); x++)
        {
            if(!GudangBrankas[playerid][x][gudangBrankasExists])
            {
                GudangBrankas[playerid][x][gudangBrankasExists] = true;
                cache_get_value_name_int(x, "ID", GudangBrankas[playerid][x][gudangBrankasID]);
                cache_get_value_name_int(x, "Owner", GudangBrankas[playerid][x][gudangBrankasOwner]);
                cache_get_value_name(x, "Item", GudangBrankas[playerid][x][gudangBrankasTemp]);
                cache_get_value_name_int(x, "Model", GudangBrankas[playerid][x][gudangBrankasModel]);
                cache_get_value_name_int(x, "Quantity", GudangBrankas[playerid][x][gudangBrankasQuant]);

                if(!IsGudangItemValid(playerid, x)) 
                {
                    totalInvalidItems++;
                }
            }
        }
        printf("[Player Gudang] Total number of Gudang Items loaded for %s [DBID: %d]: %d.", AccountData[playerid][pUCP], AccountData[playerid][pID], cache_num_rows());

        if(totalInvalidItems) 
		{
            printf("[Player Gudang] Total number of invalid items deleted for %s [DBID: %d]: %d.", AccountData[playerid][pUCP], AccountData[playerid][pID], totalInvalidItems);
        }
    }
    return 1;
}

Gudang_ShowBrankas(playerid)
{
    new 
        curr_page = index_pagination[playerid], 
        count = 0, 
        string[1555], 
        real_i = 0, 
        gdgbrankas_exists[MAX_PAGINATION_PAGES],
        gdgbrankas_name[MAX_PAGINATION_PAGES][32], 
        gdgbrankas_quant[MAX_PAGINATION_PAGES],
        gdgbrankas_id[MAX_PAGINATION_PAGES],
        curr_idx; 

    curr_idx = MAX_PAGINATION_PAGES * curr_page;

    for(new i = 0; i < MAX_PAGINATION_PAGES; i++) 
    {
        gdgbrankas_exists[i] = false;
    }

    format(string, sizeof(string), "Nama Item\tJumlah\tBerat (%.3f/300 kg)\n", GetGudangTotalWeightFloat(playerid));

    for(new i = 0; i < MAX_GUDANG_ITEMS; i++)
    {
        if (GudangBrankas[playerid][i][gudangBrankasExists] && GudangBrankas[playerid][i][gudangBrankasOwner] == AccountData[playerid][pID])
        {
            if (real_i >= curr_idx && real_i < curr_idx + MAX_PAGINATION_PAGES)
            {
                gdgbrankas_exists[real_i - curr_idx] = true;
                gdgbrankas_id[real_i - curr_idx] = i;
                strcopy(gdgbrankas_name[real_i - curr_idx], GudangBrankas[playerid][i][gudangBrankasTemp], 32);
                gdgbrankas_quant[real_i - curr_idx] = GudangBrankas[playerid][i][gudangBrankasQuant];
            }
            real_i++;
        }
    }

    for(new i = 0; i < MAX_PAGINATION_PAGES; i++) 
    {
        if(gdgbrankas_exists[i]) 
        {
            if (i % 2 == 0)
            {
                strcat(string, sprintf(""WHITE"%s\t"WHITE"%d\t"WHITE"-\n", gdgbrankas_name[i], gdgbrankas_quant[i]));
            }
            else
            {
                strcat(string, sprintf(""GRAY"%s\t"GRAY"%d\t"GRAY"-\n", gdgbrankas_name[i], gdgbrankas_quant[i]));
            }
            PlayerListitem[playerid][count++] = gdgbrankas_id[i];
        }
    }

    if(count == 0) 
	{
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "Warehouse", "This warehouse is empty!", "Tutup", "");
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

        Dialog_Show(playerid, "GudangItemVaultWithdraw", DIALOG_STYLE_TABLIST_HEADERS, sprintf("Warehouse: Page %d of %d", curr_page + 1, max_pages),
        string, "Pilih", "Batal");
    }
    return 1;
}

forward OnGudangCreated(playerid, gdgid);
public OnGudangCreated(playerid, gdgid)
{
    Gudang_Save(gdgid);
    Gudang_Rebuild(gdgid);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s create a gudang with ID: %d.", AccountData[playerid][pAdminname], gdgid);
    return 1;
}

forward LoadGudang();
public LoadGudang()
{
    new rows = cache_num_rows();
    if(rows)
    {
        new gdgid;
		for(new i; i < rows; i++)
		{
            cache_get_value_name_int(i, "ID", gdgid);
            cache_get_value_name(i, "Name", GudangData[gdgid][gudangName]);
            cache_get_value_name_int(i, "Cost_30Day", GudangData[gdgid][gudangCost]);
            cache_get_value_name_float(i, "PosX", GudangData[gdgid][gudangPos][0]);
            cache_get_value_name_float(i, "PosY", GudangData[gdgid][gudangPos][1]);
            cache_get_value_name_float(i, "PosZ", GudangData[gdgid][gudangPos][2]);
            cache_get_value_name_int(i, "World", GudangData[gdgid][gudangWorld]);
            cache_get_value_name_int(i, "Interior", GudangData[gdgid][gudangInterior]);

            Gudang_Rebuild(gdgid);
            Iter_Add(Gudangs, gdgid);
        }
        printf("[Dynamic Gudang] Total number of gudang loaded: %d.", rows);
    }
    return 1;
}

forward OnGudangDeposited(playerid, id);
public OnGudangDeposited(playerid, id)
{
    AccountData[playerid][pMenuShowed] = false;
    GudangBrankas[playerid][id][gudangBrankasID] = cache_insert_id();
    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyimpan item tersebut.");
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && AccountData[playerid][IsLoggedIn] && AccountData[playerid][pSpawned] && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        new gdgid = Gudang_Nearest(playerid);
        if(gdgid != -1)
        {
            if(AccountData[playerid][pHasGudangID] != -1)
            {
                if(gettime() > AccountData[playerid][pGudangRentTime])
                {
                    AccountData[playerid][pGudangRentTime] = 0;
                    AccountData[playerid][pHasGudangID] = -1;
                    ShowTDN(playerid, NOTIFICATION_ERROR, "Masa sewa gudang anda telah berakhir, silakan sewa kembali!");
                    return 1;
                }
                AccountData[playerid][pInGudang] = gdgid;
                AccountData[playerid][pMenuShowed] = true;
                Dialog_Show(playerid, "GudangItemVault", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Gudang", 
                "Simpan Barang\n"GRAY"Ambil Barang", "Pilih", "Batal");
            }
            else
            {
                ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum menyewa gudang di balai kota!");
            }
        }
    }
    return 1;
}

Dialog:GudangRental(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    switch(listitem)
    {
        case 0: //sewa
        {
            if(AccountData[playerid][pHasGudangID] != -1)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sudah menyewa sebuah gudang!");

            if(AccountData[playerid][pMoney] < 140000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

            TakePlayerMoneyEx(playerid, 140000);

            AccountData[playerid][pGudangRentTime] = gettime() + 2592000;
            AccountData[playerid][pHasGudangID] = 1;

            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyewa gudang tersebut selama 30 hari.");
            AccountData[playerid][pInGudang] = -1;
        }
        case 1: //berhenti
        {
            if(AccountData[playerid][pHasGudangID] == -1)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum menyewa sebuah gudang!");

            Dialog_Show(playerid, "GudangUnrental", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Gudang",
            "Apakah anda yakin untuk berhenti menyewa gudang?", "Ya", "Tidak");
        }
    }
    return 1;
}

Dialog:GudangUnrental(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;

    AccountData[playerid][pGudangRentTime] = 0;
    AccountData[playerid][pHasGudangID] = -1;
    ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah berhenti menyewa gudang.");
    return 1;
}

Dialog:GudangItemVault(playerid, response, listitem, inputtext[])
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
            format(str, sizeof(str), "Item\tQuantity\tWeight (%.3f/300 kg)\n", GetGudangTotalWeightFloat(playerid));
            for(new index; index < MAX_INVENTORY; index++)
            {
                if(InventoryData[playerid][index][invExists])
                {
                    for(new i; i < sizeof(g_aInventoryItems); i ++) if (!strcmp(g_aInventoryItems[i][e_InventoryItem], InventoryData[playerid][index][invItem], true))
                    {
                        if (i % 2 == 0) {
                            format(str, sizeof(str), "%s"WHITE"%s\t"WHITE"%d\t"WHITE"-\n", str, InventoryData[playerid][index][invItem], InventoryData[playerid][index][invQuantity]);
                        } else {
                            format(str, sizeof(str), "%s"GRAY"%s\t"GRAY"%d\t"GRAY"-\n", str, InventoryData[playerid][index][invItem], InventoryData[playerid][index][invQuantity]);
                        }
                        PlayerListitem[playerid][count++] = index;
                    }
                }
            }

            if(count == 0)
            {
                Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Gudang", 
                "You have nothing to store!", "Tutup", "");
            }
            else
            {
                Dialog_Show(playerid, "GudangItemVaultDeposit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Gudang", str, "Pilih", "Batal");
            }

            /*
            new str[1218], amounts, itemname[32], tss[128];
            format(str, sizeof(str), "Nama Item\tJumlah\tBerat (%.3f/300 kg)\n", GetGudangTotalWeightFloat(playerid));
            mysql_format(g_SQL, tss, sizeof(tss), "SELECT * FROM `inventory` WHERE `Owner_ID`=%d", AccountData[playerid][pID]);
            mysql_pquery(g_SQL, tss, "");

            mysql_query(g_SQL, tss);
            new rows = cache_num_rows();
            if(rows)
            {
                for(new x; x < rows; ++x)
                {
                    cache_get_value_name(x, "invent_Item", itemname);
                    cache_get_value_name_int(x, "invent_Quantity", amounts);
                    format(str, sizeof(str), "%s%s\t%d\t-\n", str, itemname, amounts);
                }
                Dialog_Show(playerid, "GudangItemVaultDeposit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Gudang", str, "Pilih", "Batal");
            }
            else
            {
                Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Gudang", 
                "Anda tidak memiliki barang yang dapat disimpan!", "Tutup", "");
            }
            */
        }
        case 1: //withdraw
        {
            index_pagination[playerid] = 0;
            Gudang_ShowBrankas(playerid);
        }
    }
    return 1;
}

Dialog:GudangItemVaultDeposit(playerid, response, listitem, inputtext[])
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
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih apapun!");
        return 1;
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
    Dialog_Show(playerid, "GudangItemVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Gudang", 
    shstr, "Input", "Batal");
    return 1;
}

Dialog:GudangItemVaultIn(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        AccountData[playerid][pTempValue] = -1;
        AccountData[playerid][pMenuShowed] = false;
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
        return 1;
    }

    if(AccountData[playerid][pTempValue] == -1)
    {
        AccountData[playerid][pMenuShowed] = false;
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih apapun!");
        return 1;
    }

    new shstr[512], id = AccountData[playerid][pTempValue];
    if(isnull(inputtext)) 
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan menyimpan item:\nNama: "CYAN"%s\n"WHITE"Jumlah di tas: "YELLOW"%d\n"WHITE"Error: Tidak dapat dikosongkan!\nPlease enter the quantity you want to store:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
        Dialog_Show(playerid, "GudangItemVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Gudang", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(!IsNumericEx(inputtext))
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan menyimpan item:\nNama: "CYAN"%s\n"WHITE"Jumlah di tas: "YELLOW"%d\n"WHITE"Error: Please enter only numbers!\nPlease enter the quantity you want to store:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
        Dialog_Show(playerid, "GudangItemVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Gudang", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(strval(inputtext) < 1 || strval(inputtext) > InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity])
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan menyimpan item:\nNama: "CYAN"%s\n"WHITE"Jumlah di tas: "YELLOW"%d\n"WHITE"Error: Jumlah tidak valid!\nPlease enter the quantity you want to store:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
        Dialog_Show(playerid, "GudangItemVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Gudang", 
        shstr, "Input", "Batal");
        return 1;
    }

    new quantity = strval(inputtext);

    new Float:countingtotalweight;
    countingtotalweight = GetGudangTotalWeightFloat(playerid) + float(quantity * GetItemWeight(InventoryData[playerid][PlayerListitem[playerid][id]][invItem]))/1000;
    if(countingtotalweight > 300) return ShowTDN(playerid, NOTIFICATION_ERROR, "Gudang anda telah penuh!");

    new invstr[1028];
    mysql_format(g_SQL, shstr, sizeof(shstr), "SELECT * FROM `gudang_brankas` WHERE `Owner`=%d AND `Item` = '%e'", AccountData[playerid][pID], InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
    mysql_query(g_SQL, shstr);

    new rows = cache_num_rows();
    if(rows > 0)
    {
        mysql_format(g_SQL, invstr, sizeof(invstr), "UPDATE `gudang_brankas` SET `Quantity` = `Quantity` + %d WHERE `Owner` = %d AND `Item` = '%e'", quantity, AccountData[playerid][pID], InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
        mysql_pquery(g_SQL, invstr);

        ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyimpan item tersebut.");

        for(new x; x < MAX_GUDANG_ITEMS; ++x)
        {
            if(GudangBrankas[playerid][x][gudangBrankasExists]  && GudangBrankas[playerid][x][gudangBrankasOwner] == AccountData[playerid][pID] && !strcmp(GudangBrankas[playerid][x][gudangBrankasTemp], InventoryData[playerid][PlayerListitem[playerid][id]][invItem], true))
            {
                GudangBrankas[playerid][x][gudangBrankasQuant] += quantity;
            }
        }
    }
    else
    {
        for(new x; x < MAX_GUDANG_ITEMS; ++x)
        {
            if(!GudangBrankas[playerid][x][gudangBrankasExists]) 
            {
                GudangBrankas[playerid][x][gudangBrankasExists] = true;
                GudangBrankas[playerid][x][gudangBrankasOwner] = AccountData[playerid][pID];
                strcopy(GudangBrankas[playerid][x][gudangBrankasTemp], InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
                GudangBrankas[playerid][x][gudangBrankasModel] = InventoryData[playerid][PlayerListitem[playerid][id]][invModel];
                GudangBrankas[playerid][x][gudangBrankasQuant] = quantity;

                mysql_format(g_SQL, invstr, sizeof(invstr), "INSERT INTO `gudang_brankas` SET `Owner`=%d, `Item`='%e', `Model`=%d, `Quantity`=%d", AccountData[playerid][pID], InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invModel], quantity);
                mysql_pquery(g_SQL, invstr, "OnGudangDeposited", "id", playerid, x);

                break;
            }
        }
    }
    ShowItemBox(playerid, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], sprintf("Removed %dx", quantity), InventoryData[playerid][PlayerListitem[playerid][id]][invModel], 5);
    Inventory_Remove(playerid, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], quantity);
    return 1;
}

Dialog:GudangItemVaultWithdraw(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        AccountData[playerid][pMenuShowed] = false;
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
        return 1;
    }

    if(listitem == -1){
        AccountData[playerid][pMenuShowed] = false;
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih apapun!");
        return 1;
    }


    if (!strcmp(inputtext, ">> Selanjutnya", true)) 
    {
        index_pagination[playerid]++;

        Gudang_ShowBrankas(playerid);
    } 
    else if (!strcmp(inputtext, "<< Sebelumnya", true)) 
    {
        index_pagination[playerid]--;
        if (index_pagination[playerid] < 0) {
            index_pagination[playerid] = 0;
        }
        Gudang_ShowBrankas(playerid);
    }
    else 
    {
        if (PlayerListitem[playerid][listitem] == -1) 
        {
            AccountData[playerid][pMenuShowed] = false;
            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih apapun!");
            return 1;
        }

        AccountData[playerid][pTempValue] = listitem;

        new shstr[528];
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Mohon masukkan berapa jumlah yang ingin diambil:", GudangBrankas[playerid][PlayerListitem[playerid][listitem]][gudangBrankasTemp], GudangBrankas[playerid][PlayerListitem[playerid][listitem]][gudangBrankasQuant]);
        Dialog_Show(playerid, "GudangItemVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Gudang", 
        shstr, "Input", "Batal");
    }

    return 1;
}

Dialog:GudangItemVaultOut(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        AccountData[playerid][pTempValue] = -1;
        AccountData[playerid][pMenuShowed] = false;
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
        return 1;
    }

    if(AccountData[playerid][pTempValue] == -1)
    {
        AccountData[playerid][pMenuShowed] = false;
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih apapun!");
        return 1;
    }

    new shstr[512], id = AccountData[playerid][pTempValue];
    if(isnull(inputtext)) 
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Error: Tidak dapat dikosongkan!\nPlease enter the quantity you want to retrieve:", GudangBrankas[playerid][PlayerListitem[playerid][id]][gudangBrankasTemp], GudangBrankas[playerid][PlayerListitem[playerid][id]][gudangBrankasQuant]);
        Dialog_Show(playerid, "GudangItemVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Gudang", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(!IsNumericEx(inputtext))
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Error: Please enter only numbers!\nPlease enter the quantity you want to retrieve:", GudangBrankas[playerid][PlayerListitem[playerid][id]][gudangBrankasTemp], GudangBrankas[playerid][PlayerListitem[playerid][id]][gudangBrankasQuant]);
        Dialog_Show(playerid, "GudangItemVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Gudang", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(strval(inputtext) < 1 || strval(inputtext) > GudangBrankas[playerid][PlayerListitem[playerid][id]][gudangBrankasQuant])
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Error: Jumlah tidak valid!\nPlease enter the quantity you want to retrieve:", GudangBrankas[playerid][PlayerListitem[playerid][id]][gudangBrankasTemp], GudangBrankas[playerid][PlayerListitem[playerid][id]][gudangBrankasQuant]);
        Dialog_Show(playerid, "GudangItemVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Gudang", 
        shstr, "Input", "Batal");
        return 1;
    }

    new quantity = strval(inputtext), jts[150];
    new Float:countingtotalweight;
    countingtotalweight = GetTotalWeightFloat(playerid) + float(quantity * GetItemWeight(GudangBrankas[playerid][PlayerListitem[playerid][id]][gudangBrankasTemp]))/1000;
    if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

    if(!strcmp(GudangBrankas[playerid][PlayerListitem[playerid][id]][gudangBrankasTemp], "Obeng")) 
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

    if(!strcmp(GudangBrankas[playerid][PlayerListitem[playerid][id]][gudangBrankasTemp], "Cangkul")) 
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

    if(!strcmp(GudangBrankas[playerid][PlayerListitem[playerid][id]][gudangBrankasTemp], "Smartphone"))
    {
        mysql_format(g_SQL, jts, sizeof(jts), "SELECT * FROM `player_phones` WHERE `phoneOwner`=%d", AccountData[playerid][pID]);
        mysql_pquery(g_SQL, jts, "OnPlayerBuySmartphone", "i", playerid);
    }
    else
    {
        Inventory_Add(playerid, GudangBrankas[playerid][PlayerListitem[playerid][id]][gudangBrankasTemp], GudangBrankas[playerid][PlayerListitem[playerid][id]][gudangBrankasModel], quantity);
    }
    
    ShowItemBox(playerid, GudangBrankas[playerid][PlayerListitem[playerid][id]][gudangBrankasTemp], sprintf("Received %dx", quantity), GudangBrankas[playerid][PlayerListitem[playerid][id]][gudangBrankasModel], 5);

    GudangBrankas[playerid][PlayerListitem[playerid][id]][gudangBrankasQuant] -= quantity;
    
    if(GudangBrankas[playerid][PlayerListitem[playerid][id]][gudangBrankasQuant] > 0)
    {
        mysql_format(g_SQL, jts, sizeof(jts), "UPDATE `gudang_brankas` SET `Quantity`=%d WHERE `ID`=%d", GudangBrankas[playerid][PlayerListitem[playerid][id]][gudangBrankasQuant], GudangBrankas[playerid][PlayerListitem[playerid][id]][gudangBrankasID]);
        mysql_pquery(g_SQL, jts);
    }
    else
    {
        mysql_format(g_SQL, jts, sizeof(jts), "DELETE FROM `gudang_brankas` WHERE `ID`=%d", GudangBrankas[playerid][PlayerListitem[playerid][id]][gudangBrankasID]);
        mysql_pquery(g_SQL, jts);

        GudangBrankas[playerid][PlayerListitem[playerid][id]][gudangBrankasExists] = false;
        GudangBrankas[playerid][PlayerListitem[playerid][id]][gudangBrankasID] = 0;
        GudangBrankas[playerid][PlayerListitem[playerid][id]][gudangBrankasOwner] = 0;
        GudangBrankas[playerid][PlayerListitem[playerid][id]][gudangBrankasTemp][0] = EOS;
        GudangBrankas[playerid][PlayerListitem[playerid][id]][gudangBrankasModel] = 0;
        GudangBrankas[playerid][PlayerListitem[playerid][id]][gudangBrankasQuant] = 0;
    }
    AccountData[playerid][pMenuShowed] = false;
    return 1;
}