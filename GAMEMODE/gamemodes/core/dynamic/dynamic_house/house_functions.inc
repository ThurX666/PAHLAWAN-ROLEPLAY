#include <YSI_Coding\y_hooks>

#define MAX_HOUSES 500

#define MAX_HOUSE_ITEMS 100

enum e_housestuff
{
    hID,
    hOwnerID,
    hOwnerName[24],
    Float:hPos[4],
    hType,
    hWorld,
    hInterior,
    Float:hIntPos[4],
    hIntWorld,
    hIntInterior,
    Float:hVaultPos[3],
    Float:hGaragePos[4],
    hMusicURL[128],

    //not save
    STREAMER_TAG_3D_TEXT_LABEL:hLabel,
    STREAMER_TAG_3D_TEXT_LABEL:hVaultLabel,
    STREAMER_TAG_3D_TEXT_LABEL:hExitLabel,
    STREAMER_TAG_3D_TEXT_LABEL:hGarageTextLabel,
    STREAMER_TAG_PICKUP:hGaragePickup
};
new HouseData[MAX_HOUSES][e_housestuff],
    HouseTempInvite[MAX_PLAYERS],
    Iterator:Houses<MAX_HOUSES>;

enum e_housebrankas
{
    houseBrankasID,
    houseBrankasOwner,
    houseBrankasTemp[32],
    houseBrankasModel,
    houseBrankasQuant,

    //not save
    bool:houseBrankasExists
};
new HouseBrankas[MAX_PLAYERS][MAX_HOUSE_ITEMS][e_housebrankas];

enum e_HouseHolster
{
	hHolsterID,
	bool:hHolsterTaken,
	hHolsterWeaponID,
	hHolsterWeaponAmmo
};
new HouseHolster[MAX_HOUSES][e_HouseHolster][5];

House_Save(hid)
{
    new lxa[1024];
    mysql_format(g_SQL, lxa, sizeof(lxa), "UPDATE `houses` SET `OwnerID` = %d, `OwnerName` = '%e', `X` = '%f', `Y` = '%f', `Z` = '%f', `A` = '%f', `IX` = '%f', `IY` = '%f', `IZ` = '%f', `IA` = '%f', `BX` = '%f', `BY` = '%f', `BZ` = '%f', `GX` = '%f', `GY` = '%f', `GZ` = '%f', `GA` = '%f', `Type` = %d, `World` = %d, `Interior` = %d, `IntWorld` = %d, `IntInterior` = %d, `MusicURL` = '%e' WHERE `ID` = %d",
    HouseData[hid][hOwnerID], HouseData[hid][hOwnerName], HouseData[hid][hPos][0], HouseData[hid][hPos][1], HouseData[hid][hPos][2], HouseData[hid][hPos][3], HouseData[hid][hIntPos][0], HouseData[hid][hIntPos][1], HouseData[hid][hIntPos][2], HouseData[hid][hIntPos][3], 
    HouseData[hid][hVaultPos][0], HouseData[hid][hVaultPos][1], HouseData[hid][hVaultPos][2], HouseData[hid][hGaragePos][0], HouseData[hid][hGaragePos][1], HouseData[hid][hGaragePos][2], HouseData[hid][hGaragePos][3], HouseData[hid][hType], HouseData[hid][hWorld], HouseData[hid][hInterior], HouseData[hid][hIntWorld], HouseData[hid][hIntInterior], HouseData[hid][hMusicURL], hid);
    mysql_pquery(g_SQL, lxa);
    return 1;
}

GetHouseType(hid)
{
    new teks[164];
    if(hid != -1)
    {
        switch(HouseData[hid][hType])
        {
            case 0:
            {
                format(teks, sizeof(teks), "Rumah ini tidak memiliki type, segera lapor staff!");
            }
            case 1:
            {
                format(teks, sizeof(teks), "Standard");
            }
            case 2:
            {
                format(teks, sizeof(teks), "Kontemporer");
            }
            case 3:
            {
                format(teks, sizeof(teks), "Modern");
            }
            case 4:
            {
                format(teks, sizeof(teks), "Mansion");
            }
        }
    }
    return teks;
}

House_Rebuild(hid)
{
    if(hid != -1)
    {
        if(isnull(HouseData[hid][hOwnerName]))
        {
            HouseData[hid][hLabel] = CreateDynamic3DTextLabel(""YELLOW"/hclaim "WHITE"untuk klaim rumah ini", Y_WHITE, HouseData[hid][hPos][0], HouseData[hid][hPos][1], HouseData[hid][hPos][2] + 0.35, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, HouseData[hid][hWorld], HouseData[hid][hInterior], -1, 10.00, -1, 0);
        }
        else
        {
            new hjx[128];
            format(hjx, sizeof(hjx), "[Y] "WHITE"rumah %s\n%s", HouseData[hid][hOwnerName], GetHouseType(hid));
            HouseData[hid][hLabel] = CreateDynamic3DTextLabel(hjx, Y_GREEN, HouseData[hid][hPos][0], HouseData[hid][hPos][1], HouseData[hid][hPos][2] + 0.35, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, HouseData[hid][hWorld], HouseData[hid][hInterior], -1, 10.00, -1, 0);
        }

        if(HouseData[hid][hGaragePos][0] != 0.0 && HouseData[hid][hGaragePos][1] != 0.0 && HouseData[hid][hGaragePos][2] != 0.0 && HouseData[hid][hGaragePos][3] != 0.0)
        {
            HouseData[hid][hGarageTextLabel] = CreateDynamic3DTextLabel("[Garasi Rumah]\n"WHITE"Tekan "YELLOW"tombol klakson "WHITE"untuk menyimpan kendaraan\n"RED"'Y' "WHITE"Buka garasi", Y_CYAN, HouseData[hid][hGaragePos][0], HouseData[hid][hGaragePos][1], HouseData[hid][hGaragePos][2]+0.85, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, HouseData[hid][hWorld], HouseData[hid][hInterior], -1, 10.00, -1, 0);
            HouseData[hid][hGaragePickup] = CreateDynamicPickup(19131, 23, HouseData[hid][hGaragePos][0], HouseData[hid][hGaragePos][1], HouseData[hid][hGaragePos][2], HouseData[hid][hWorld], HouseData[hid][hInterior], -1, 30.00, -1, 0);
        }

        HouseData[hid][hVaultLabel] = CreateDynamic3DTextLabel("[Y] "WHITE"Lemari", Y_GREEN, HouseData[hid][hVaultPos][0], HouseData[hid][hVaultPos][1], HouseData[hid][hVaultPos][2] + 0.35, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, HouseData[hid][hIntWorld], HouseData[hid][hIntInterior], -1, 10.00, -1, 0);

        HouseData[hid][hExitLabel] = CreateDynamic3DTextLabel("[Y] "WHITE"Keluar", Y_GREEN, HouseData[hid][hIntPos][0], HouseData[hid][hIntPos][1], HouseData[hid][hIntPos][2] + 0.35, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, HouseData[hid][hIntWorld], HouseData[hid][hIntInterior], -1, 10.00, -1, 0);
    }
    return 1;
}

House_Refresh(hid)
{
    if(hid != -1)
    {
        if(isnull(HouseData[hid][hOwnerName]))
        {
            UpdateDynamic3DTextLabelText(HouseData[hid][hLabel], Y_WHITE, ""YELLOW"/hclaim "WHITE"untuk klaim rumah ini");
        }
        else
        {
            new hjx[128];
            format(hjx, sizeof(hjx), "[Y] "WHITE"rumah %s\n%s", HouseData[hid][hOwnerName], GetHouseType(hid));
            UpdateDynamic3DTextLabelText(HouseData[hid][hLabel], Y_GREEN, hjx);
        }

        Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, HouseData[hid][hVaultLabel], HouseData[hid][hVaultPos][0], HouseData[hid][hVaultPos][1], HouseData[hid][hVaultPos][2] + 0.35);
        Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, HouseData[hid][hVaultLabel], E_STREAMER_WORLD_ID, HouseData[hid][hIntWorld]);
        Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, HouseData[hid][hVaultLabel], E_STREAMER_INTERIOR_ID, HouseData[hid][hIntInterior]);

        Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, HouseData[hid][hExitLabel], HouseData[hid][hIntPos][0], HouseData[hid][hIntPos][1], HouseData[hid][hIntPos][2] + 0.35);
        Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, HouseData[hid][hExitLabel], E_STREAMER_WORLD_ID, HouseData[hid][hIntWorld]);
        Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, HouseData[hid][hExitLabel], E_STREAMER_INTERIOR_ID, HouseData[hid][hIntInterior]);

        Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, HouseData[hid][hLabel], HouseData[hid][hPos][0], HouseData[hid][hPos][1], HouseData[hid][hPos][2] + 0.35);
        Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, HouseData[hid][hLabel], E_STREAMER_WORLD_ID, HouseData[hid][hWorld]);
        Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, HouseData[hid][hLabel], E_STREAMER_INTERIOR_ID, HouseData[hid][hInterior]);

        if(HouseData[hid][hGaragePos][0] != 0.0 && HouseData[hid][hGaragePos][1] != 0.0 && HouseData[hid][hGaragePos][2] != 0.0 && HouseData[hid][hGaragePos][3] != 0.0)
        {
            if(!IsValidDynamicPickup(HouseData[hid][hGaragePickup]))
            {
                HouseData[hid][hGarageTextLabel] = CreateDynamic3DTextLabel("[Garasi Rumah]\n"WHITE"Tekan "YELLOW"tombol klakson "WHITE"untuk menyimpan kendaraan\n"RED"'Y' "WHITE"Buka garasi", Y_CYAN, HouseData[hid][hGaragePos][0], HouseData[hid][hGaragePos][1], HouseData[hid][hGaragePos][2] + 0.85, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, HouseData[hid][hWorld], HouseData[hid][hInterior], -1, 10.00, -1, 0);
                HouseData[hid][hGaragePickup] = CreateDynamicPickup(19131, 23, HouseData[hid][hGaragePos][0], HouseData[hid][hGaragePos][1], HouseData[hid][hGaragePos][2], HouseData[hid][hWorld], HouseData[hid][hInterior], -1, 30.00, -1, 0);
            }
        }

        if(IsValidDynamicPickup(HouseData[hid][hGaragePickup]))
        {
            Streamer_SetItemPos(STREAMER_TYPE_PICKUP, HouseData[hid][hGaragePickup], HouseData[hid][hGaragePos][0], HouseData[hid][hGaragePos][1], HouseData[hid][hGaragePos][2]);
            Streamer_SetIntData(STREAMER_TYPE_PICKUP, HouseData[hid][hGaragePickup], E_STREAMER_WORLD_ID, HouseData[hid][hWorld]);
            Streamer_SetIntData(STREAMER_TYPE_PICKUP, HouseData[hid][hGaragePickup], E_STREAMER_INTERIOR_ID, HouseData[hid][hInterior]);
        }

        if(IsValidDynamic3DTextLabel(HouseData[hid][hGarageTextLabel]))
        {
            Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, HouseData[hid][hGarageTextLabel], HouseData[hid][hGaragePos][0], HouseData[hid][hGaragePos][1], HouseData[hid][hGaragePos][2] + 0.85);
            Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, HouseData[hid][hGarageTextLabel], E_STREAMER_WORLD_ID, HouseData[hid][hWorld]);
            Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, HouseData[hid][hGarageTextLabel], E_STREAMER_INTERIOR_ID, HouseData[hid][hInterior]);
        }
    }
    return 1;
}

House_Nearest(playerid)
{
    foreach(new i : Houses) if (IsPlayerInRangeOfPoint(playerid, 2.5, HouseData[i][hPos][0], HouseData[i][hPos][1], HouseData[i][hPos][2]))
	{
		if (GetPlayerInterior(playerid) == HouseData[i][hInterior] && GetPlayerVirtualWorld(playerid) == HouseData[i][hWorld])
			return i;
	}
	return -1;
}

HouseGarage_Nearest(playerid)
{
    foreach(new i : Houses) if (IsPlayerInRangeOfPoint(playerid, 4.5, HouseData[i][hGaragePos][0], HouseData[i][hGaragePos][1], HouseData[i][hGaragePos][2]))
	{
		if (GetPlayerInterior(playerid) == 0 && GetPlayerVirtualWorld(playerid) == 0)
			return i;
	}
	return -1;
}

Player_ReturnHouseID(playerid)
{
    new rid = -1;
    foreach(new hid : Houses)
    {
        if(HouseData[hid][hOwnerID] == AccountData[playerid][pID] || AccountData[playerid][pHouseSharedID] == hid)
        {
            rid = hid;
        }
    }
    return rid;
}

Player_NearHouse(playerid, hid)
{
    new counting, frmxt[522];
    foreach(new i : Player) if(i != playerid) if(IsPlayerInRangeOfPoint(i, 1.5, HouseData[hid][hPos][0], HouseData[hid][hPos][1], HouseData[hid][hPos][2])) 
    {
        if (i % 2 == 0) {
            format(frmxt, sizeof(frmxt), "%s"WHITE"Player ID - (%d)\n", frmxt, i);
        }
        else {
            format(frmxt, sizeof(frmxt), "%s"GRAY"Player ID - (%d)\n", frmxt, i);
        }
        NearestUser[playerid][counting++] = i;
    }

    if(counting == 0)
    {
        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
		return Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Undang Teman", "Tidak ada player yang dekat dengan pintu rumah anda!", "Tutup", "");
    }

    Dialog_Show(playerid, "HouseInvite", DIALOG_STYLE_TABLIST, "{DA9100}Pahlawan Roleplay "WHITE"- Undang Teman", frmxt, "Pilih", "Batal");
    return 1;
}

static bool:IsHouseItemValid(playerid, slot)
{
    new bool:itemExists = false;
    for(new i = 0; i < sizeof(g_aInventoryItems); i++) 
    {
        // Kalau item-nya ada, ganti itemExists
        if(!strcmp(HouseBrankas[playerid][slot][houseBrankasTemp], g_aInventoryItems[i][e_InventoryItem], true)) {
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
        HouseBrankas[playerid][slot][houseBrankasExists] = false;
        HouseBrankas[playerid][slot][houseBrankasModel] = 0;
        HouseBrankas[playerid][slot][houseBrankasQuant] = 0;
 
        HouseBrankas[playerid][slot][houseBrankasTemp][0] = EOS;
 
        static invstr[555];
        mysql_format(g_SQL, invstr, sizeof(invstr), "DELETE FROM `house_brankas` WHERE `ID`=%d", HouseBrankas[playerid][slot][houseBrankasID]);
        mysql_pquery(g_SQL, invstr);
    }
 
    return itemExists;
}

forward LoadHouseBrankas(playerid);
public LoadHouseBrankas(playerid)
{
    if(cache_num_rows() > 0)
    {
        new totalInvalidItems = 0;
        for(new x; x < cache_num_rows(); x++)
        {
            if(!HouseBrankas[playerid][x][houseBrankasExists])
            {
                HouseBrankas[playerid][x][houseBrankasExists] = true;
                cache_get_value_name_int(x, "ID", HouseBrankas[playerid][x][houseBrankasID]);
                cache_get_value_name_int(x, "Owner", HouseBrankas[playerid][x][houseBrankasOwner]);
                cache_get_value_name(x, "Item", HouseBrankas[playerid][x][houseBrankasTemp]);
                cache_get_value_name_int(x, "Model", HouseBrankas[playerid][x][houseBrankasModel]);
                cache_get_value_name_int(x, "Quantity", HouseBrankas[playerid][x][houseBrankasQuant]);

                if(!IsHouseItemValid(playerid, x)) 
                {
                    totalInvalidItems++;
                }
            }
        }
        printf("[Player House] Jumlah total Items House yang dimuat untuk %s [DBID: %d]: %d.", AccountData[playerid][pUCP], AccountData[playerid][pID], cache_num_rows());

        if(totalInvalidItems) 
		{
            printf("[Player House] Total number of invalid items deleted for %s [DBID: %d]: %d.", AccountData[playerid][pUCP], AccountData[playerid][pID], totalInvalidItems);
        }
    }
    return 1;
}

forward Player_HouseSavedClothes(playerid);
public Player_HouseSavedClothes(playerid)
{
    new shstr[128], sjjr[258];
    mysql_format(g_SQL, shstr, sizeof(shstr), "SELECT * FROM `player_clothes` WHERE `Owner`=%d", AccountData[playerid][pID]);
    mysql_query(g_SQL, shstr);
    new rows = cache_num_rows(), ClothesName[34];
    if(rows)
    {
        for(new i; i < rows; i++)
        {
            cache_get_value_name(i, "Name", ClothesName);
            format(sjjr, sizeof(sjjr), "%s%s\n", sjjr, ClothesName);
        }
        Dialog_Show(playerid, "HouseClothes", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Pakaian", 
        sjjr, "Pilih", "Kembali");
    }
    else
    {
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Pakaian", 
        "Anda tidak memiliki pakaian tersimpan!", "Tutup", "");
    }
    return 1;
}

Float:GetHouseTotalWeightFloat(playerid)
{
	new totalweights, Float:totalweights2;

    for(new x; x < MAX_HOUSE_ITEMS; x++)
    {
        if(HouseBrankas[playerid][x][houseBrankasExists] && HouseBrankas[playerid][x][houseBrankasOwner] == AccountData[playerid][pID])
        {
            totalweights += GetItemWeight(HouseBrankas[playerid][x][houseBrankasTemp]) * HouseBrankas[playerid][x][houseBrankasQuant];
        }
    }
    totalweights2 = float(totalweights)/1000;
    return totalweights2;
}

House_ShowBrankas(playerid)
{
    new 
        curr_page = index_pagination[playerid], 
        count = 0, 
        string[1555], 
        real_i = 0, 
        hbrankas_exists[MAX_PAGINATION_PAGES],
        hbrankas_name[MAX_PAGINATION_PAGES][32], 
        hbrankas_quant[MAX_PAGINATION_PAGES],
        hbrankas_id[MAX_PAGINATION_PAGES],
        curr_idx; 

    curr_idx = MAX_PAGINATION_PAGES * curr_page;

    for(new i = 0; i < MAX_PAGINATION_PAGES; i++) 
    {
        hbrankas_exists[i] = false;
    }

    switch(HouseData[AccountData[playerid][pInHouse]][hType])
    {
        case 1:
        {
            format(string, sizeof(string), "Nama Item\tJumlah\tBerat (%.3f/450 kg)\n", GetHouseTotalWeightFloat(playerid));
        }
        case 2:
        {
            format(string, sizeof(string), "Nama Item\tJumlah\tBerat (%.3f/500 kg)\n", GetHouseTotalWeightFloat(playerid));
        }
        case 3:
        {
            format(string, sizeof(string), "Nama Item\tJumlah\tBerat (%.3f/700 kg)\n", GetHouseTotalWeightFloat(playerid));
        }
        case 4:
        {
            format(string, sizeof(string), "Nama Item\tJumlah\tBerat (%.3f/~ kg)\n", GetHouseTotalWeightFloat(playerid));
        }
    }

    for(new i = 0; i < MAX_HOUSE_ITEMS; i++)
    {
        if (HouseBrankas[playerid][i][houseBrankasExists] && HouseBrankas[playerid][i][houseBrankasOwner] == AccountData[playerid][pID])
        {
            if (real_i >= curr_idx && real_i < curr_idx + MAX_PAGINATION_PAGES)
            {
                hbrankas_exists[real_i - curr_idx] = true;
                hbrankas_id[real_i - curr_idx] = i;
                strcopy(hbrankas_name[real_i - curr_idx], HouseBrankas[playerid][i][houseBrankasTemp], 32);
                hbrankas_quant[real_i - curr_idx] = HouseBrankas[playerid][i][houseBrankasQuant];
            }
            real_i++;
        }
    }

    for(new i = 0; i < MAX_PAGINATION_PAGES; i++) 
    {
        if(hbrankas_exists[i]) 
        {
            if (i % 2 == 0)
            {
                strcat(string, sprintf(""WHITE"%s\t"WHITE"%d\t"WHITE"-\n", hbrankas_name[i], hbrankas_quant[i]));
            }
            else
            {
                strcat(string, sprintf(""GRAY"%s\t"GRAY"%d\t"GRAY"-\n", hbrankas_name[i], hbrankas_quant[i]));
            }
            PlayerListitem[playerid][count++] = hbrankas_id[i];
        }
    }

    if(count == 0) 
	{
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "Brankas Rumah", "Isi brankas rumah ini kosong!", "Tutup", "");
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

        Dialog_Show(playerid, "HouseItemVaultWithdraw", DIALOG_STYLE_TABLIST_HEADERS, sprintf("Brankas Rumah: Page %d of %d", curr_page + 1, max_pages),
        string, "Pilih", "Batal");
    }
    return 1;
}

Player_HouseCount(playerid)
{
    new counting;
    foreach(new hid : Houses)
    {
        if(HouseData[hid][hOwnerID] == AccountData[playerid][pID])
        {
            counting++;
        }
    }
    return counting;
}

ShowHouseSharedList(playerid)
{
	new count = 0, sgstr[525];

	for (new i; i < 3; i ++) if(!isnull(HouseMemberName[playerid][i]))
	{
	    format(sgstr, sizeof(sgstr), "%s%s\n", sgstr, HouseMemberName[playerid][i]);
		count++;
	}
	if(count < 3)
		format(sgstr, sizeof(sgstr), "%s"GREEN"+ Berikan Kunci", sgstr);

	Dialog_Show(playerid, "HouseGiveKey", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Pemegang Kunci", sgstr, "Pilih", "Kembali");
	return 1;
}

forward LoadHouseHolster(hid);
public LoadHouseHolster(hid)
{
	new count = cache_num_rows();
    if(count)
    {
		for(new i; i < count; i++)
		{
			for(new z; z < 5; z++)
			{
				if(!HouseHolster[hid][hHolsterTaken][z])
				{
					cache_get_value_name_int(i, "ID", HouseHolster[hid][hHolsterID][z]);
					cache_get_value_name_int(i, "WeaponID", HouseHolster[hid][hHolsterWeaponID][z]);
					cache_get_value_name_int(i, "WeaponAmmo", HouseHolster[hid][hHolsterWeaponAmmo][z]);
					HouseHolster[hid][hHolsterTaken][z] = true;
					break;
				}
			}
		}
	}
	return 1;
}

forward LoadHouseSharedKey(playerid);
public LoadHouseSharedKey(playerid)
{
    for (new i; i < 3; i ++)
	{
		HouseMemberName[playerid][i][0] = EOS;
	}

	for (new i; i < cache_num_rows(); i ++)
	{
		cache_get_value_name(i, "Char_Name", HouseMemberName[playerid][i]);
	}
  	ShowHouseSharedList(playerid);
    return 1;
}

forward OnWeaponHStored(hid, id);
public OnWeaponHStored(hid, id)
{
	HouseHolster[hid][hHolsterID][id] = cache_insert_id();
	return 1;
}

forward OnHouseDeposited(playerid, id);
public OnHouseDeposited(playerid, id)
{
    AccountData[playerid][pMenuShowed] = false;
    HouseBrankas[playerid][id][houseBrankasID] = cache_insert_id();
    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyimpan item tersebut.");
    return 1;
}

forward LoadHouses();
public LoadHouses()
{
    new rows = cache_num_rows(), afafa[512];
    if(rows)
    {
        new hid;
		for(new i; i < rows; i++)
		{
            cache_get_value_name_int(i, "ID", hid);
            cache_get_value_name_int(i, "OwnerID", HouseData[hid][hOwnerID]);
            cache_get_value_name(i, "OwnerName", HouseData[hid][hOwnerName]);
            cache_get_value_name_float(i, "X", HouseData[hid][hPos][0]);
            cache_get_value_name_float(i, "Y", HouseData[hid][hPos][1]);
            cache_get_value_name_float(i, "Z", HouseData[hid][hPos][2]);
            cache_get_value_name_float(i, "A", HouseData[hid][hPos][3]);
            cache_get_value_name_float(i, "IX", HouseData[hid][hIntPos][0]);
            cache_get_value_name_float(i, "IY", HouseData[hid][hIntPos][1]);
            cache_get_value_name_float(i, "IZ", HouseData[hid][hIntPos][2]);
            cache_get_value_name_float(i, "IA", HouseData[hid][hIntPos][3]);
            cache_get_value_name_float(i, "BX", HouseData[hid][hVaultPos][0]);
            cache_get_value_name_float(i, "BY", HouseData[hid][hVaultPos][1]);
            cache_get_value_name_float(i, "BZ", HouseData[hid][hVaultPos][2]);
            cache_get_value_name_float(i, "GX", HouseData[hid][hGaragePos][0]);
            cache_get_value_name_float(i, "GY", HouseData[hid][hGaragePos][1]);
            cache_get_value_name_float(i, "GZ", HouseData[hid][hGaragePos][2]);
            cache_get_value_name_float(i, "GA", HouseData[hid][hGaragePos][3]);
            cache_get_value_name_int(i, "Type", HouseData[hid][hType]);
            cache_get_value_name_int(i, "World", HouseData[hid][hWorld]);
            cache_get_value_name_int(i, "Interior", HouseData[hid][hInterior]);
            cache_get_value_name_int(i, "IntWorld", HouseData[hid][hIntWorld]);
            cache_get_value_name_int(i, "IntInterior", HouseData[hid][hIntInterior]);
            cache_get_value_name(i, "MusicURL", HouseData[hid][hMusicURL]);

            House_Rebuild(hid);
            Iter_Add(Houses, hid);

            mysql_format(g_SQL, afafa, sizeof(afafa), "SELECT * FROM `house_holster` WHERE `House_DBID` = %d", hid);
			mysql_pquery(g_SQL, afafa, "LoadHouseHolster", "i", hid);
        }
        printf("[Dynamic Rumah] Jumlah total Rumah yang dimuat: %d.", rows);
    }
    return 1;
}

forward OnHouseCreated(playerid, hid);
public OnHouseCreated(playerid, hid)
{
    House_Save(hid);
    House_Rebuild(hid);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s membuat Rumah dengan ID: %d.", AccountData[playerid][pAdminname], hid);
    return 1;
}

forward SaveVehicleToHouse(playerid, carid, hid);
public SaveVehicleToHouse(playerid, carid, hid)
{
    if(!IsPlayerConnected(playerid)) return 1;
    if(!AccountData[playerid][pSpawned]) return 1;
    if(PlayerVehicle[carid][pVehPhysic] == INVALID_VEHICLE_ID || !IsValidVehicle(PlayerVehicle[carid][pVehPhysic])) return 1;
    if(!Iter_Contains(Houses, hid)) return 1;
    if(!IsValidDynamicPickup(HouseData[hid][hGaragePickup])) return 1;

    PlayerVehicle[carid][pVehHouseGarage] = hid;

    SetVehicleNeonLights(PlayerVehicle[carid][pVehPhysic], false, PlayerVehicle[carid][pVehNeon], 0);
    DestroyVehicle(PlayerVehicle[carid][pVehPhysic]);
    PlayerVehicle[carid][pVehPhysic] = INVALID_VEHICLE_ID;

    new sqlsdwadkw[128];
    mysql_format(g_SQL, sqlsdwadkw, sizeof(sqlsdwadkw), "UPDATE `player_vehicles` SET `PVeh_Housed` = %d WHERE `id` = %d", PlayerVehicle[carid][pVehHouseGarage], PlayerVehicle[carid][pVehID]);
    mysql_pquery(g_SQL, sqlsdwadkw);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && AccountData[playerid][IsLoggedIn] && AccountData[playerid][pSpawned] && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(AccountData[playerid][pInHouse] != -1)
        {
            if(Iter_Contains(Houses, AccountData[playerid][pInHouse]))
            {
                if(IsPlayerInRangeOfPoint(playerid, 1.5, HouseData[AccountData[playerid][pInHouse]][hIntPos][0],HouseData[AccountData[playerid][pInHouse]][hIntPos][1],HouseData[AccountData[playerid][pInHouse]][hIntPos][2]) && GetPlayerVirtualWorld(playerid) == HouseData[AccountData[playerid][pInHouse]][hIntWorld] && GetPlayerInterior(playerid) == HouseData[AccountData[playerid][pInHouse]][hIntInterior]) //keluar rumah
                {
                    if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
                    if(AccountData[playerid][pInHouse] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di dalam rumah manapun!");

                    StopAudioStreamForPlayer(playerid);
                    SetPlayerPositionEx(playerid, HouseData[AccountData[playerid][pInHouse]][hPos][0], HouseData[AccountData[playerid][pInHouse]][hPos][1], HouseData[AccountData[playerid][pInHouse]][hPos][2], HouseData[AccountData[playerid][pInHouse]][hPos][3], 6500);
                    SetPlayerInteriorEx(playerid, 0);
                    SetPlayerVirtualWorldEx(playerid, 0);
                    GameTextForPlayer(playerid, "Loading World...", 6500, 3);
                    AccountData[playerid][pInHouse] = -1;
                    FadeIn(playerid);
                }

                else if(IsPlayerInRangeOfPoint(playerid, 0.5, HouseData[AccountData[playerid][pInHouse]][hVaultPos][0], HouseData[AccountData[playerid][pInHouse]][hVaultPos][1], HouseData[AccountData[playerid][pInHouse]][hVaultPos][2]) && GetPlayerVirtualWorld(playerid) == HouseData[AccountData[playerid][pInHouse]][hIntWorld] && GetPlayerInterior(playerid) == HouseData[AccountData[playerid][pInHouse]][hIntInterior]) //brankas rumah
                {
                    if(AccountData[playerid][pInHouse] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di dalam rumah manapun!");
                    if(HouseData[AccountData[playerid][pInHouse]][hOwnerID] != AccountData[playerid][pID] && AccountData[playerid][pHouseSharedID] != AccountData[playerid][pInHouse]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki kunci rumah ini!");

                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, false, false, false, false, 0, true);
                    Dialog_Show(playerid, "HouseChest", DIALOG_STYLE_LIST, sprintf("{DA9100}Pahlawan Roleplay "WHITE"- %s", HouseData[AccountData[playerid][pInHouse]][hOwnerName]), 
                    "Undang\n\
                    "GRAY"Pakaian\n\
                    Membuang Pakaian\n\
                    "GRAY"Brankas\n\
                    Weapon Chest\n\
                    "GRAY"Musik\n\
                    Pemegang Kunci\n\
                    "GRAY"Kerajinan Tangan", "Pilih", "Batal");
                }
            }
        }

        new hid = House_Nearest(playerid);
        if(hid != -1)
        {
            if(HouseData[hid][hOwnerID] != 0)
            {
                if(HouseData[hid][hOwnerID] != AccountData[playerid][pID] && AccountData[playerid][pHouseSharedID] != hid)
                {
                    PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
                    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, sprintf("{DA9100}Pahlawan Roleplay "WHITE"- %s", HouseData[hid][hOwnerName]), 
                    "Rumah ini sudah dimiliki warga lain!", "Tutup", "");
                }
                else
                {
                    if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
                    
                    AccountData[playerid][pInHouse] = hid;

                    if(!isnull(HouseData[hid][hMusicURL]))
                        PlayAudioStreamForPlayer(playerid, HouseData[hid][hMusicURL]);

                    SetPlayerPositionEx(playerid, HouseData[hid][hIntPos][0],HouseData[hid][hIntPos][1],HouseData[hid][hIntPos][2],HouseData[hid][hIntPos][3], 6500);
                    SetPlayerInteriorEx(playerid, HouseData[hid][hIntInterior]);
                    SetPlayerVirtualWorldEx(playerid, HouseData[hid][hIntWorld]);
                    GameTextForPlayer(playerid, "Loading World...", 6500, 3);
                    HouseTempInvite[playerid] = INVALID_PLAYER_ID;
                    FadeIn(playerid);
                }
            }
        }

        new hgid = HouseGarage_Nearest(playerid);
        if(hgid != -1)
        {
            if(HouseData[hgid][hOwnerID] != 0) //jika rumah memiliki owner atau sudah dimiliki oleh siapapun juga
            {
                if(HouseData[hgid][hOwnerID] == AccountData[playerid][pID] || AccountData[playerid][pHouseSharedID] == hgid)
                {
                    if(HouseData[hgid][hGaragePos][0] == 0.0 && HouseData[hgid][hGaragePos][1] == 0.0 && HouseData[hgid][hGaragePos][2] == 0.0 && HouseData[hgid][hGaragePos][3] == 0.0)
                        return ShowTDN(playerid, NOTIFICATION_ERROR, "Rumah ini tidak memiliki garasi!");

                    if(CountPlayerVehicleHoused(playerid, hgid) < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki kendaraan yang tersimpan di garasi ini!");
                    AccountData[playerid][pInGarkot] = hgid;
                    new id, count = CountPlayerVehicleHoused(playerid, hgid), location[512], lstr[596];
                    strcat(location,"No\tModel\tPlate\n",sizeof(location));
                    for(new itt; itt < count; itt++)
                    {
                        id = ReturnAnyVehicleHoused(playerid, itt, hgid);
                        if(itt == count)
                        {
                            format(lstr,sizeof(lstr), "%d\t%s\t%s\n", itt + 1, GetVehicleModelName(PlayerVehicle[id][pVehModelID]), PlayerVehicle[id][pVehPlate]);
                        }
                        else format(lstr,sizeof(lstr), "%d\t%s\t%s\n", itt + 1, GetVehicleModelName(PlayerVehicle[id][pVehModelID]), PlayerVehicle[id][pVehPlate]);
                        strcat(location,lstr,sizeof(location));
                    }
                    Dialog_Show(playerid, "HouseGarage", DIALOG_STYLE_TABLIST_HEADERS,"House Garage - Takeout Vehicle", location, "Pilih","Batal");
                }
            }
        }
    }
    else if(newkeys & KEY_CROUCH && AccountData[playerid][IsLoggedIn] && AccountData[playerid][pSpawned] && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
    {
        new hid = HouseGarage_Nearest(playerid);
        if(hid != -1)
        {
            if(HouseData[hid][hOwnerID] != 0)
            {
                if(HouseData[hid][hOwnerID] == AccountData[playerid][pID] || AccountData[playerid][pHouseSharedID] == hid)
                {
                    new carid = -1,
                        foundnearby = 0;

                    if((carid = GetPlayerVehicleIDInside(playerid)) != -1)
                    {
                        if(PlayerVehicle[carid][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
                        if(PlayerVehicle[carid][pVehRental] > -1 || PlayerVehicle[carid][pVehRentTime] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menyimpan kendaraan rental!");
                        Vehicle_GetStatus(carid);

                        foundnearby++;
                        RemovePlayerFromVehicle(playerid);
                        SetTimerEx("SaveVehicleToHouse", 2500, false, "idd", playerid, carid, hid);
                    }

                    if(!foundnearby)
                        return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini bukan jenis kendaraan pribadi!");
                }
            }
        }
    }
    return 1;
}

Dialog:HouseInvite(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih apapun!");
    
    new otherid = NearestUser[playerid][listitem], jhtrs[258];
    HouseTempInvite[otherid] = playerid;
    AccountData[otherid][pInHouse] = AccountData[playerid][pInHouse];
    format(jhtrs, sizeof(jhtrs), "Pemilik rumah, %s mengundang anda untuk masuk ke dalam.\n\
    Apakah anda ingin menerima undangannya?", HouseData[AccountData[playerid][pInHouse]][hOwnerName]);
    Dialog_Show(otherid, "HouseInviteConfirm", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- House Invitation", 
    jhtrs, "Ya", "Tidak");
    return 1;
}

Dialog:HouseInviteConfirm(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        if(IsPlayerConnected(HouseTempInvite[playerid]))
            ShowTDN(HouseTempInvite[playerid], NOTIFICATION_INFO, "Undangan anda telah ditolak.");
        HouseTempInvite[playerid] = INVALID_PLAYER_ID;
        AccountData[playerid][pInHouse] = -1;
        return 1;
    }
    if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
    
    new hid = AccountData[playerid][pInHouse];

    if(hid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di dalam rumah!");
    
    if(!isnull(HouseData[hid][hMusicURL]))
        PlayAudioStreamForPlayer(playerid, HouseData[hid][hMusicURL]);

    SetPlayerPositionEx(playerid, HouseData[hid][hIntPos][0],HouseData[hid][hIntPos][1],HouseData[hid][hIntPos][2],HouseData[hid][hIntPos][3], 6500);
    SetPlayerInteriorEx(playerid, HouseData[hid][hIntInterior]);
    SetPlayerVirtualWorldEx(playerid, HouseData[hid][hIntWorld]);
    GameTextForPlayer(playerid, "Loading World...", 6500, 3);
    HouseTempInvite[playerid] = INVALID_PLAYER_ID;
    FadeIn(playerid);
    return 1;
}

Dialog:HouseChest(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;

    switch(listitem)
    {
        case 0: //Undang
        {
            Player_NearHouse(playerid, AccountData[playerid][pInHouse]);
        }
        case 1: //Pakaian
        {
            Player_HouseSavedClothes(playerid);
        }
        case 2: //Membuang
        {
            if(AccountData[playerid][pUsingClothes] == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang memakai clothes yang tersimpan!");

            new tstr[128];
            mysql_format(g_SQL, tstr, sizeof(tstr), "DELETE FROM `player_clothes` WHERE `ID`=%d", AccountData[playerid][pUsingClothes]);
            mysql_pquery(g_SQL, tstr);

            AccountData[playerid][pUsingClothes] = 0;
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda berhasil membuang pakaian tersebut!");

            SetDefaultAppearance(playerid);
        }
        case 3: //Brankas
        {
            AccountData[playerid][pMenuShowed] = true;
            Dialog_Show(playerid, "HouseItemVault", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Rumah", 
            "Simpan Barang\n"GRAY"Ambil Barang", "Pilih", "Kembali");
        }
        case 4: //weapon chest
        {
            if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berjalan kaki!");
            if(IsPlayerHunting[playerid]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus keluar dari mode berburu sebelum membuka weapon chest!");
            if(AccountData[playerid][pTaser]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat akses weapon chest ketika menggunakan Taser!");
            if (AccountData[playerid][pUseBeanbag]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat akses weapon chest ketika menggunakan beanbag!");

            AccountData[playerid][pMenuShowed] = true;
            Dialog_Show(playerid, "HouseHolster", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Weapon Chest", "Simpan Senjata\n"GRAY"Ambil Senjata", "Pilih", "Batal");
        }
        case 5: //musik
        {
            if(HouseData[AccountData[playerid][pInHouse]][hOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini bukan rumah milik anda!");

            Dialog_Show(playerid, "HouseMusic", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Musik Rumah", 
            "Pahlawan Roleplay House Music System\n\n\
            Kami sarankan anda untuk upload file mp3 ke discord terlebih dahulu.\n\
            "RED"Note: Fitur ini tidak support link YouTube secara langsung!\n\n\
            "YELLOW"(Apabila file mp3 telah di upload ke discord, silahkan copy linknya dan paste di bawah ini):", "Input", "Batal");
        }
        case 6: //pemegang kunci
        {
            if(HouseData[AccountData[playerid][pInHouse]][hOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini bukan rumah milik anda!");
            if(HouseData[AccountData[playerid][pInHouse]][hType] != 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya rumah level Mansion yang dapat akses!");

            new xsst[138];
            mysql_format(g_SQL, xsst, sizeof(xsst), "SELECT * FROM `player_characters` WHERE `Char_HouseSharedID` = %d LIMIT 3", AccountData[playerid][pInHouse]);
            mysql_pquery(g_SQL, xsst, "LoadHouseSharedKey", "i", playerid);
        }
        case 7: //kerajinan tangan
        {
            if(HouseData[AccountData[playerid][pInHouse]][hOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini bukan rumah milik anda!");
            if(HouseData[AccountData[playerid][pInHouse]][hType] < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya rumah level Kontemporer yang dapat akses!");

            Dialog_Show(playerid, "HouseCrafting", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Kerajinan", 
            "Nama Item\tBahan\t-\n\
            Gulai Ayam\tKentang: 3x | Cabai: 3x | Bawang: 3x | Tomat: 3x\tAir: 3x | Gula: 3x | Micin: 3x | Ayam Kemas: 3x\n\
			"GRAY"Es Lilin\t"GRAY"Kentang: 3x | Cabai: 3x | Bawang: 3x | Tomat: 3x\t"GRAY"Air: 3x | Gula: 3x | Micin: 3x | Ayam Kemas: 3x\n\
            Perban\tKaret: 5x | Plastik: 5x | Kertas: 5x\t-", "Pilih", "Batal");
        }
    }
    return 1;
}

Dialog:HouseCrafting(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        return 1;
    }

    switch(listitem)
    {
        case 0: //gulai ayam
        {
            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

            AccountData[playerid][pActivityTime] = 1;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMASAK");
            ShowProgressBar(playerid);

            pCookingHouseTimer[playerid] = true;
            AccountData[playerid][pTempValue2] = 0;

            ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, 1, 0, 0, 0, 0, 1);
        }
        case 1: //es lilin
        {
            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

            AccountData[playerid][pActivityTime] = 1;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMASAK");
            ShowProgressBar(playerid);

            pCookingHouseTimer[playerid] = true;
            AccountData[playerid][pTempValue2] = 1;

            ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, 1, 0, 0, 0, 0, 1);
        }
        case 2: //perban
        {
            if(HouseData[AccountData[playerid][pInHouse]][hType] < 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya rumah level Modern yang dapat akses!");

            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

            AccountData[playerid][pActivityTime] = 1;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MERAKIT");
            ShowProgressBar(playerid);

            pHCraftBandageTimer[playerid] = true;

            ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, 1, 0, 0, 0, 0, 1);
        }
    }
    return 1;
}

Dialog:HouseHolster(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        AccountData[playerid][pMenuShowed] = false;
        return 1;
    }

    switch(listitem)
    {
        case 0: //simpan
        {
            static wpid[MAX_PLAYERS];
            wpid[playerid] = GetPlayerWeaponEx(playerid);
            if(wpid[playerid] < 1 || wpid[playerid] > 45) 
            {
                AccountData[playerid][pMenuShowed] = false;
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang memegang senjata apapun/weapon ID tidak valid!");
            }

            if(GunData[playerid][g_aWeaponSlots[wpid[playerid]]][WeaponType] != WEAPON_TYPE_PLAYER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menyimpan senjata jenis admin atau faction!");

            if(wpid[playerid] != 40)
            {
                if(GunData[playerid][g_aWeaponSlots[wpid[playerid]]][WeaponType] == WEAPON_TYPE_NONE)
                {
                    SendClientMessageEx(playerid, Y_RED, "[AntiCheat] {DBD7D2}Anda ditendang dari server karena diduga Weapon Hack. "YELLOW"[Holster] [%s]", ReturnWeaponName(wpid[playerid]));
                    SetWeapons(playerid); //Reload old weapons
                    return KickEx(playerid);
                }
                
                if(AccountData[playerid][pInHouse] != -1)
                {
                    for(new id; id < 5; ++id)
                    {
                        if(!HouseHolster[AccountData[playerid][pInHouse]][hHolsterTaken][id]) 
                        {
                            HouseHolster[AccountData[playerid][pInHouse]][hHolsterTaken][id] = true;
                            GetPlayerWeaponData(playerid, g_aWeaponSlots[wpid[playerid]], HouseHolster[AccountData[playerid][pInHouse]][hHolsterWeaponID][id], HouseHolster[AccountData[playerid][pInHouse]][hHolsterWeaponAmmo][id]);
                            ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Anda telah menyimpan %s ke dalam weapon chest!", ReturnWeaponName(wpid[playerid])));
                            ResetWeapon(playerid, wpid[playerid]);
                            
                            new afafa[512];
                            mysql_format(g_SQL, afafa, sizeof(afafa), "INSERT INTO `house_holster` (`House_DBID`, `WeaponID`, `WeaponAmmo`) VALUES (%d, %d, %d)", AccountData[playerid][pInHouse], HouseHolster[AccountData[playerid][pInHouse]][hHolsterWeaponID][id], HouseHolster[AccountData[playerid][pInHouse]][hHolsterWeaponAmmo][id]);
                            mysql_pquery(g_SQL, afafa, "OnWeaponHStored", "id", AccountData[playerid][pInHouse], id);

                            AccountData[playerid][pMenuShowed] = false;
                            break;
                        }

                        if(id == (5 - 1))
                            ShowTDN(playerid, NOTIFICATION_ERROR, "Holster rumah rumah ini sudah penuh!");
                    }
                }
                AccountData[playerid][pMenuShowed] = false;
                return 1;
            }
        }
        case 1: //ambil
        {
            new xjjs[512], count;
            format(xjjs, sizeof(xjjs), "#\tWeapon\tAmmo\n");
            for(new id; id < 5; ++id)
            {
                if(HouseHolster[AccountData[playerid][pInHouse]][hHolsterTaken][id]) 
                {
                    format(xjjs, sizeof(xjjs), "%s%d\t%s\t%d\n", xjjs, id + 1, ReturnWeaponName(HouseHolster[AccountData[playerid][pInHouse]][hHolsterWeaponID][id]), HouseHolster[AccountData[playerid][pInHouse]][hHolsterWeaponAmmo][id]);
                    count++;
                }
                else
                {
                    format(xjjs, sizeof(xjjs), "%s"GREEN"%d\t"GREEN"Kosong\t"GREEN"0\n", xjjs, id + 1);
                }
            }

            if(count == 0)
            {
                ShowTDN(playerid, NOTIFICATION_ERROR, "Holster rumah ini kosong!");
            }
            else
            {
                Dialog_Show(playerid, "HouseHolsterWithdraw", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Holster Rumah", xjjs, "Pilih", "Batal");
            }
        }
    }
    return 1;
}

Dialog:HouseHolsterWithdraw(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        AccountData[playerid][pMenuShowed] = false;
        return 1;
    }

    if(listitem > 5)
    {
        AccountData[playerid][pMenuShowed] = false;
        return 1;
    }

    if(!HouseHolster[AccountData[playerid][pInHouse]][hHolsterTaken][listitem])
    {
        AccountData[playerid][pMenuShowed] = false;

        ShowTDN(playerid, NOTIFICATION_ERROR, "Slot penyimpanan tersebut kosong!");
        return 1;
    }

    if(IsAFireArm(HouseHolster[AccountData[playerid][pInHouse]][hHolsterWeaponID][listitem]) && AccountData[playerid][pLevel] < 5)
    {
        AccountData[playerid][pMenuShowed] = false;
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda dapat memegang senjata jika sudah mencapai level 5 karakter!");
    }

    new afafa[512];
    mysql_format(g_SQL, afafa, sizeof(afafa), "DELETE FROM `house_holster` WHERE `House_DBID` = %d AND `ID` = %d", AccountData[playerid][pInHouse], HouseHolster[AccountData[playerid][pInHouse]][hHolsterID][listitem]);
    mysql_pquery(g_SQL, afafa);

    ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Anda telah mengambil %s dari weapon chest.", ReturnWeaponName(HouseHolster[AccountData[playerid][pInHouse]][hHolsterWeaponID][listitem])));
    GivePlayerWeaponEx(playerid, HouseHolster[AccountData[playerid][pInHouse]][hHolsterWeaponID][listitem], HouseHolster[AccountData[playerid][pInHouse]][hHolsterWeaponAmmo][listitem], WEAPON_TYPE_PLAYER);
    HouseHolster[AccountData[playerid][pInHouse]][hHolsterTaken][listitem] = false;
    HouseHolster[AccountData[playerid][pInHouse]][hHolsterWeaponID][listitem] = 0;
    HouseHolster[AccountData[playerid][pInHouse]][hHolsterWeaponAmmo][listitem] = 0;
    AccountData[playerid][pMenuShowed] = false;
    return 1;
}

Dialog:HouseMusic(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;

    if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat diisi kosong!");

    foreach(new i : Player)
    {
        if(i != playerid && AccountData[i][pSpawned])
        {
            if(AccountData[i][pInHouse] == AccountData[playerid][pInHouse])
            {
                PlayAudioStreamForPlayer(i, inputtext);
                ShowTDN(i, NOTIFICATION_INFO, "Musik telah diputar, jika tidak terdengar cek volume radio di setting GTA!");
            }
        }
    }
    strcopy(HouseData[AccountData[playerid][pInHouse]][hMusicURL], inputtext);
    PlayAudioStreamForPlayer(playerid, inputtext);
    ShowTDN(playerid, NOTIFICATION_INFO, "Musik telah diputar, jika tidak terdengar cek volume radio di setting GTA!");
    House_Save(AccountData[playerid][pInHouse]);
    return 1;
}

Dialog:HouseClothes(playerid, response, listitem, inputtext[])
{
    if(!response) return Dialog_Show(playerid, "HouseChest", DIALOG_STYLE_LIST, sprintf("{DA9100}Pahlawan Roleplay "WHITE"- %s", HouseData[AccountData[playerid][pInHouse]][hOwnerName]), 
    "Undang\n\
    "GRAY"Pakaian\n\
    Membuang Pakaian\n\
    "GRAY"Brankas\n\
    Weapon Chest\n\
    "GRAY"Musik\n\
    Pemegang Kunci\n\
    "GRAY"Kerajinan Tangan", "Pilih", "Batal");

    new shstr[128];
    mysql_format(g_SQL, shstr, sizeof(shstr), "SELECT * FROM `player_clothes` WHERE `Owner`=%d", AccountData[playerid][pID]);
    mysql_query(g_SQL, shstr);
    if(cache_num_rows() > 0)
    {
        cache_get_value_name_int(listitem, "ID", AccountData[playerid][pUsingClothes]);
        SetPlayerClothes(playerid, AccountData[playerid][pUsingClothes]);
    }
    return 1;
}

Dialog:HouseItemVault(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        AccountData[playerid][pMenuShowed] = false;
        Dialog_Show(playerid, "HouseChest", DIALOG_STYLE_LIST, sprintf("{DA9100}Pahlawan Roleplay "WHITE"- %s", HouseData[AccountData[playerid][pInHouse]][hOwnerName]), 
        "Undang\n\
        "GRAY"Pakaian\n\
        Membuang Pakaian\n\
        "GRAY"Brankas\n\
        Weapon Chest\n\
        "GRAY"Musik\n\
        Pemegang Kunci\n\
        "GRAY"Kerajinan Tangan", "Pilih", "Batal");
        return 1;
    }

    switch(listitem)
    {
        case 0: //deposit
        {
            new str[1218], count;
            switch(HouseData[AccountData[playerid][pInHouse]][hType])
            {
                case 1:
                {
                    format(str, sizeof(str), "Nama Item\tJumlah\tBerat (%.3f/450 kg)\n", GetHouseTotalWeightFloat(playerid));
                }
                case 2:
                {
                    format(str, sizeof(str), "Nama Item\tJumlah\tBerat (%.3f/500 kg)\n", GetHouseTotalWeightFloat(playerid));
                }
                case 3:
                {
                    format(str, sizeof(str), "Nama Item\tJumlah\tBerat (%.3f/700 kg)\n", GetHouseTotalWeightFloat(playerid));
                }
                case 4:
                {
                    format(str, sizeof(str), "Nama Item\tJumlah\tBerat (%.3f/~ kg)\n", GetHouseTotalWeightFloat(playerid));
                }
            }
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
                Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Rumah", 
                "Anda tidak memiliki barang yang dapat disimpan!", "Tutup", "");
            }
            else
            {
                Dialog_Show(playerid, "HouseItemVaultDeposit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Rumah", str, "Pilih", "Batal");
            }
        }
        case 1: //withdraw
        {
            index_pagination[playerid] = 0;
            House_ShowBrankas(playerid);
        }
    }
    return 1;
}

Dialog:HouseGiveKey(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        Dialog_Show(playerid, "HouseChest", DIALOG_STYLE_LIST, sprintf("{DA9100}Pahlawan Roleplay "WHITE"- %s", HouseData[AccountData[playerid][pInHouse]][hOwnerName]), 
        "Undang\n\
        "GRAY"Pakaian\n\
        Membuang Pakaian\n\
        "GRAY"Brankas\n\
        Weapon Chest\n\
        "GRAY"Musik\n\
        Pemegang Kunci\n\
        "GRAY"Kerajinan Tangan", "Pilih", "Batal");
        return 1;
    }
    if(listitem < 0 || listitem > 2) 
    {
        ShowHouseSharedList(playerid);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih!");
        return 1;
    }

    if(isnull(HouseMemberName[playerid][listitem]))
    {
        Dialog_Show(playerid, "HouseGiveKeyConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Bagikan Kunci", "Mohon masukkan playerid yang ingin diberikan kunci rumah:", "Input", "Kembali");
        return 1;
    }

    strcopy(TempString[playerid], HouseMemberName[playerid][listitem]);
    Dialog_Show(playerid, "HouseTakeKey", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Tarik Kunci", sprintf("Apakah anda yakin ingin menarik kunci dari %s?", HouseMemberName[playerid][listitem]),
    "Ya", "No");
    return 1;
}

Dialog:HouseTakeKey(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;

    static destid, slss[146];
    mysql_format(g_SQL, slss, sizeof(slss), "SELECT * FROM `player_characters` WHERE `Char_Name` = '%e' LIMIT 1", TempString[playerid]);
    mysql_query(g_SQL, slss);
    if(cache_num_rows())
    {
        cache_get_value_name_int(0, "pID", destid);

        foreach(new i : Player)
        {
            if(AccountData[i][pID] == destid && AccountData[i][IsLoggedIn]) //jika ada di server
            {
                AccountData[i][pHouseSharedID] = -1;
                ShowTDN(i, NOTIFICATION_INFO, "Kunci rumah anda telah ditarik kembali oleh pemilik!");
            }
        }
        mysql_format(g_SQL, slss, sizeof(slss), "UPDATE `player_characters` SET `Char_HouseSharedID` = '-1' WHERE `pID` = %d", destid);
        mysql_pquery(g_SQL, slss);
    }
    return 1;
}

Dialog:HouseGiveKeyConfirm(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        ShowHouseSharedList(playerid);
        return 1;
    }

    if(isnull(inputtext)) return Dialog_Show(playerid, "HouseGiveKeyConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Bagikan Kunci", 
    "Error: Tidak dapat dikosongkan!\n\
    Mohon masukkan playerid yang ingin diberikan kunci rumah:", "Pilih", "Batal");
    if(!IsNumericEx(inputtext)) return Dialog_Show(playerid, "HouseGiveKeyConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Bagikan Kunci", 
    "Error: Masukkan hanya angka!\n\
    Mohon masukkan playerid yang ingin diberikan kunci rumah:", "Pilih", "Batal");

    if(!IsPlayerConnected(strval(inputtext))) return Dialog_Show(playerid, "HouseGiveKeyConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Bagikan Kunci", 
    "Error: The player is not connected to the server!\n\
    Mohon masukkan playerid yang ingin diberikan kunci rumah:", "Pilih", "Batal");
    if(strval(inputtext) == playerid) return Dialog_Show(playerid, "HouseGiveKeyConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Bagikan Kunci", 
    "Error: Anda tidak dapat memberikan kunci rumah pada diri sendiri!\n\
    Mohon masukkan playerid yang ingin diberikan kunci rumah:", "Pilih", "Batal");
    if(!IsPlayerNearPlayer(playerid, strval(inputtext), 3.5)) return Dialog_Show(playerid, "HouseGiveKeyConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Bagikan Kunci", 
    "Error: Pemain tersebut tidak dekat dengan anda!\n\
    Mohon masukkan playerid yang ingin diberikan kunci rumah:", "Pilih", "Batal");
    if(Player_HouseCount(strval(inputtext)) > 0) return Dialog_Show(playerid, "HouseGiveKeyConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Bagikan Kunci", 
    "Error: Pemain tersebut sudah memiliki rumah sendiri!\n\
    Mohon masukkan playerid yang ingin diberikan kunci rumah:", "Pilih", "Batal");

    AccountData[strval(inputtext)][pHouseSharedID] = AccountData[playerid][pInHouse];

    new slxs[164];
    mysql_format(g_SQL, slxs, sizeof(slxs), "UPDATE `player_characters` SET `Char_HouseSharedID` = %d WHERE `pID` = %d", AccountData[strval(inputtext)][pHouseSharedID], AccountData[strval(inputtext)][pID]);
    mysql_pquery(g_SQL, slxs);

    ShowTDN(strval(inputtext), NOTIFICATION_INFO, "Anda telah diberikan kunci untuk tinggal di rumah ini!");
    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memberikan kunci rumah kepada Pemain tersebut");
    return 1;
}

Dialog:HouseItemVaultDeposit(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        AccountData[playerid][pMenuShowed] = false;
        Dialog_Show(playerid, "HouseChest", DIALOG_STYLE_LIST, sprintf("{DA9100}Pahlawan Roleplay "WHITE"- %s", HouseData[AccountData[playerid][pInHouse]][hOwnerName]), 
        "Undang\n\
        "GRAY"Pakaian\n\
        Membuang Pakaian\n\
        "GRAY"Brankas\n\
        Weapon Chest\n\
        "GRAY"Musik\n\
        Pemegang Kunci\n\
        "GRAY"Kerajinan Tangan", "Pilih", "Batal");
        return 1;
    }

    if(listitem == -1) 
    {
        AccountData[playerid][pMenuShowed] = false;
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih apapun!");
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
    Dialog_Show(playerid, "HouseItemVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Rumah", 
    shstr, "Input", "Batal");
    return 1;
}

Dialog:HouseItemVaultIn(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        AccountData[playerid][pTempValue] = -1;
        AccountData[playerid][pMenuShowed] = false;
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
        Dialog_Show(playerid, "HouseItemVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Rumah", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(!IsNumericEx(inputtext))
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan menyimpan item:\nNama: "CYAN"%s\n"WHITE"Jumlah di tas: "YELLOW"%d\n"WHITE"Error: Please enter only numbers!\nPlease enter the quantity you want to store:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
        Dialog_Show(playerid, "HouseItemVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Rumah", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(strval(inputtext) < 1 || strval(inputtext) > InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity])
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan menyimpan item:\nNama: "CYAN"%s\n"WHITE"Jumlah di tas: "YELLOW"%d\n"WHITE"Error: Jumlah tidak valid!\nPlease enter the quantity you want to store:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
        Dialog_Show(playerid, "HouseItemVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Rumah", 
        shstr, "Input", "Batal");
        return 1;
    }

    new quantity = strval(inputtext);

    new Float:countingtotalweight;
    countingtotalweight = GetHouseTotalWeightFloat(playerid) + float(quantity * GetItemWeight(InventoryData[playerid][PlayerListitem[playerid][id]][invItem]))/1000;
    switch(HouseData[AccountData[playerid][pInHouse]][hType])
    {
        case 1:
        {
            if(countingtotalweight > 450) return ShowTDN(playerid, NOTIFICATION_ERROR, "Brankas rumah anda telah penuh!");
        }
        case 2:
        {
            if(countingtotalweight > 500) return ShowTDN(playerid, NOTIFICATION_ERROR, "Brankas rumah anda telah penuh!");
        }
        case 3:
        {
            if(countingtotalweight > 700) return ShowTDN(playerid, NOTIFICATION_ERROR, "Brankas rumah anda telah penuh!");
        }
    }

    new invstr[1028];
    mysql_format(g_SQL, shstr, sizeof(shstr), "SELECT * FROM `house_brankas` WHERE `Owner`=%d AND `Item` = '%e'", AccountData[playerid][pID], InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
    mysql_query(g_SQL, shstr);

    new rows = cache_num_rows();
    if(rows > 0)
    {
        mysql_format(g_SQL, invstr, sizeof(invstr), "UPDATE `house_brankas` SET `Quantity` = `Quantity` + %d WHERE `Owner` = %d AND `Item` = '%e'", quantity, AccountData[playerid][pID], InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
        mysql_pquery(g_SQL, invstr);

        ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyimpan item tersebut.");

        for(new x; x < MAX_HOUSE_ITEMS; ++x)
        {
            if(HouseBrankas[playerid][x][houseBrankasExists]  && HouseBrankas[playerid][x][houseBrankasOwner] == AccountData[playerid][pID] && !strcmp(HouseBrankas[playerid][x][houseBrankasTemp], InventoryData[playerid][PlayerListitem[playerid][id]][invItem], true))
            {
                HouseBrankas[playerid][x][houseBrankasQuant] += quantity;
            }
        }
    }
    else
    {
        for(new x; x < MAX_HOUSE_ITEMS; ++x)
        {
            if(!HouseBrankas[playerid][x][houseBrankasExists]) 
            {
                HouseBrankas[playerid][x][houseBrankasExists] = true;
                HouseBrankas[playerid][x][houseBrankasOwner] = AccountData[playerid][pID];
                strcopy(HouseBrankas[playerid][x][houseBrankasTemp], InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
                HouseBrankas[playerid][x][houseBrankasModel] = InventoryData[playerid][PlayerListitem[playerid][id]][invModel];
                HouseBrankas[playerid][x][houseBrankasQuant] = quantity;

                mysql_format(g_SQL, invstr, sizeof(invstr), "INSERT INTO `house_brankas` SET `Owner`=%d, `Item`='%e', `Model`=%d, `Quantity`=%d", AccountData[playerid][pID], InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invModel], quantity);
                mysql_pquery(g_SQL, invstr, "OnHouseDeposited", "id", playerid, x);

                break;
            }
        }
    }
    ShowItemBox(playerid, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], sprintf("Removed %dx", quantity), InventoryData[playerid][PlayerListitem[playerid][id]][invModel], 5);
    Inventory_Remove(playerid, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], quantity);
    return 1;
}

Dialog:HouseItemVaultWithdraw(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        AccountData[playerid][pMenuShowed] = false;
        Dialog_Show(playerid, "HouseChest", DIALOG_STYLE_LIST, sprintf("{DA9100}Pahlawan Roleplay "WHITE"- %s", HouseData[AccountData[playerid][pInHouse]][hOwnerName]), 
        "Undang\n\
        "GRAY"Pakaian\n\
        Membuang Pakaian\n\
        "GRAY"Brankas\n\
        Weapon Chest\n\
        "GRAY"Musik\n\
        Pemegang Kunci\n\
        "GRAY"Kerajinan Tangan", "Pilih", "Batal");
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
        House_ShowBrankas(playerid);
    } 
    else if (!strcmp(inputtext, "<< Sebelumnya", true)) 
    {
        index_pagination[playerid]--;
        if (index_pagination[playerid] < 0) {
            index_pagination[playerid] = 0; 
        }
        House_ShowBrankas(playerid); 
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
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Mohon masukkan berapa jumlah yang ingin diambil:", HouseBrankas[playerid][PlayerListitem[playerid][listitem]][houseBrankasTemp], HouseBrankas[playerid][PlayerListitem[playerid][listitem]][houseBrankasQuant]);
        Dialog_Show(playerid, "HouseItemVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Rumah", 
        shstr, "Input", "Batal");
    }

    return 1;
}

Dialog:HouseItemVaultOut(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        AccountData[playerid][pMenuShowed] = false;
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
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Error: Tidak dapat dikosongkan!\nPlease enter the quantity you want to retrieve:", HouseBrankas[playerid][PlayerListitem[playerid][id]][houseBrankasTemp], HouseBrankas[playerid][PlayerListitem[playerid][id]][houseBrankasQuant]);
        Dialog_Show(playerid, "HouseItemVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Rumah", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(!IsNumericEx(inputtext))
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Error: Please enter only numbers!\nPlease enter the quantity you want to retrieve:", HouseBrankas[playerid][PlayerListitem[playerid][id]][houseBrankasTemp], HouseBrankas[playerid][PlayerListitem[playerid][id]][houseBrankasQuant]);
        Dialog_Show(playerid, "HouseItemVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Rumah", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(strval(inputtext) < 1 || strval(inputtext) > HouseBrankas[playerid][PlayerListitem[playerid][id]][houseBrankasQuant])
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Error: Jumlah tidak valid!\nPlease enter the quantity you want to retrieve:", HouseBrankas[playerid][PlayerListitem[playerid][id]][houseBrankasTemp], HouseBrankas[playerid][PlayerListitem[playerid][id]][houseBrankasQuant]);
        Dialog_Show(playerid, "HouseItemVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Rumah", 
        shstr, "Input", "Batal");
        return 1;
    }

    new quantity = strval(inputtext), jts[150];
    new Float:countingtotalweight;
    countingtotalweight = GetTotalWeightFloat(playerid) + float(quantity * GetItemWeight(HouseBrankas[playerid][PlayerListitem[playerid][id]][houseBrankasTemp]))/1000;
    if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

    if(!strcmp(HouseBrankas[playerid][PlayerListitem[playerid][id]][houseBrankasTemp], "Obeng")) 
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

    if(!strcmp(HouseBrankas[playerid][PlayerListitem[playerid][id]][houseBrankasTemp], "Cangkul")) 
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

    if(!strcmp(HouseBrankas[playerid][PlayerListitem[playerid][id]][houseBrankasTemp], "Smartphone"))
    {
        mysql_format(g_SQL, jts, sizeof(jts), "SELECT * FROM `player_phones` WHERE `phoneOwner`=%d", AccountData[playerid][pID]);
        mysql_pquery(g_SQL, jts, "OnPlayerBuySmartphone", "i", playerid);
    }
    else
    {
        Inventory_Add(playerid, HouseBrankas[playerid][PlayerListitem[playerid][id]][houseBrankasTemp], HouseBrankas[playerid][PlayerListitem[playerid][id]][houseBrankasModel], quantity);
    }
    
    ShowItemBox(playerid, HouseBrankas[playerid][PlayerListitem[playerid][id]][houseBrankasTemp], sprintf("Received %dx", quantity), HouseBrankas[playerid][PlayerListitem[playerid][id]][houseBrankasModel], 5);

    HouseBrankas[playerid][PlayerListitem[playerid][id]][houseBrankasQuant] -= quantity;
    
    if(HouseBrankas[playerid][PlayerListitem[playerid][id]][houseBrankasQuant] > 0)
    {
        mysql_format(g_SQL, jts, sizeof(jts), "UPDATE `house_brankas` SET `Quantity`=%d WHERE `ID`=%d", HouseBrankas[playerid][PlayerListitem[playerid][id]][houseBrankasQuant], HouseBrankas[playerid][PlayerListitem[playerid][id]][houseBrankasID]);
        mysql_pquery(g_SQL, jts);
    }
    else
    {
        mysql_format(g_SQL, jts, sizeof(jts), "DELETE FROM `house_brankas` WHERE `ID`=%d", HouseBrankas[playerid][PlayerListitem[playerid][id]][houseBrankasID]);
        mysql_pquery(g_SQL, jts);

        HouseBrankas[playerid][PlayerListitem[playerid][id]][houseBrankasExists] = false;
        HouseBrankas[playerid][PlayerListitem[playerid][id]][houseBrankasID] = 0;
        HouseBrankas[playerid][PlayerListitem[playerid][id]][houseBrankasOwner] = 0;
        HouseBrankas[playerid][PlayerListitem[playerid][id]][houseBrankasTemp][0] = EOS;
        HouseBrankas[playerid][PlayerListitem[playerid][id]][houseBrankasModel] = 0;
        HouseBrankas[playerid][PlayerListitem[playerid][id]][houseBrankasQuant] = 0;
    }
    AccountData[playerid][pMenuShowed] = false;
    return 1;
}

Dialog:HouseGarage(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        AccountData[playerid][pInGarkot] = -1;
        return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    }

    new id = ReturnAnyVehicleHoused(playerid, listitem, AccountData[playerid][pInGarkot]);
    if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan yang tersimpan pada garasi rumah ini!");
    
    if(PlayerVehicle[id][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
    PlayerVehicle[id][pVehParked] = -1;
    PlayerVehicle[id][pVehFamGarage] = -1;
    PlayerVehicle[id][pVehHouseGarage] = -1;
    PlayerVehicle[id][pVehInsuranced] = false;

    PlayerVehicle[id][pVehImpounded] = false;
    PlayerVehicle[id][pVehImpoundDuration] = 0;
    PlayerVehicle[id][pVehImpoundFee] = 0;
    PlayerVehicle[id][pVehImpoundReason][0] = EOS;

    PlayerVehicle[id][pVehPos][0] = HouseData[AccountData[playerid][pInGarkot]][hGaragePos][0];
    PlayerVehicle[id][pVehPos][1] = HouseData[AccountData[playerid][pInGarkot]][hGaragePos][1];
    PlayerVehicle[id][pVehPos][2] = HouseData[AccountData[playerid][pInGarkot]][hGaragePos][2];
    PlayerVehicle[id][pVehPos][3] = HouseData[AccountData[playerid][pInGarkot]][hGaragePos][3];
    
    OnPlayerVehicleRespawn(id);
    AccountData[playerid][pInGarkot] = -1;

    SetTimerEx("ForcePlayerHopInVehicle", 1500, false, "idd", playerid, PlayerVehicle[id][pVehPhysic], 0);

    new sqlsdwadkw[158];
    mysql_format(g_SQL, sqlsdwadkw, sizeof(sqlsdwadkw), "UPDATE `player_vehicles` SET `PVeh_Parked` = %d, `PVeh_Housed` = %d WHERE `id` = %d", PlayerVehicle[id][pVehParked], PlayerVehicle[id][pVehHouseGarage], PlayerVehicle[id][pVehID]);
    mysql_pquery(g_SQL, sqlsdwadkw);
    return 1;
}