#include <YSI_Coding\y_hooks>

#define MAX_RUSUN 200
#define MAX_RUSUN_ITEMS 100
#define DEFAULT_RUSUN_RESET 2592000

enum e_rusundetails
{
    rusunName[34],
    rusunOwnerName[24],
    rusunOwnerID,
    rusunCost,
    Float:rusunPos[4],
    rusunWorld,
    rusunInterior,

    //not saved
    STREAMER_TAG_PICKUP:rusunPickup,
    STREAMER_TAG_3D_TEXT_LABEL:rusunLabel,
    STREAMER_TAG_PICKUP:rusunChestPickup,
    STREAMER_TAG_3D_TEXT_LABEL:rusunChestLabel,
    STREAMER_TAG_3D_TEXT_LABEL:rusunOutLabel
};
new RusunData[MAX_RUSUN][e_rusundetails],
    RusunTempInvite[MAX_PLAYERS],
    Iterator:Rusuns<MAX_RUSUN>;

enum e_rusunbrankas
{
    rusunBrankasID,
    rusunBrankasOwner,
    rusunBrankasTemp[32],
    rusunBrankasModel,
    rusunBrankasQuant,

    //not saved
    bool:rusunBrankasExists
};
new RusunBrankas[MAX_PLAYERS][MAX_RUSUN_ITEMS][e_rusunbrankas];

Rusun_Nearest(playerid)
{
    foreach(new i : Rusuns) if (IsPlayerInRangeOfPoint(playerid, 2.0, RusunData[i][rusunPos][0], RusunData[i][rusunPos][1], RusunData[i][rusunPos][2]))
	{
		if (GetPlayerInterior(playerid) == RusunData[i][rusunInterior] && GetPlayerVirtualWorld(playerid) == RusunData[i][rusunWorld])
			return i;
	}
	return -1;
}

Rusun_Save(rsid)
{
    new sfstr[358];
    mysql_format(g_SQL, sfstr, sizeof(sfstr), "UPDATE `rusun` SET `Name`='%e', `OwnerName`='%e', `OwnerID`=%d, `Cost_30Day`=%d, `PosX`='%f', `PosY`='%f', `PosZ`='%f', `PosA`='%f', `World`=%d, `Interior`=%d WHERE `ID`=%d", 
    RusunData[rsid][rusunName], RusunData[rsid][rusunOwnerName], RusunData[rsid][rusunOwnerID], RusunData[rsid][rusunCost], RusunData[rsid][rusunPos][0], RusunData[rsid][rusunPos][1], RusunData[rsid][rusunPos][2], RusunData[rsid][rusunPos][3], RusunData[rsid][rusunWorld], RusunData[rsid][rusunInterior], rsid);
    mysql_pquery(g_SQL, sfstr);
    return 1;
}

Rusun_Rebuild(rsid)
{
    if(rsid != -1)
    {
        RusunData[rsid][rusunPickup] = CreateDynamicPickup(19523, 23, RusunData[rsid][rusunPos][0], RusunData[rsid][rusunPos][1], RusunData[rsid][rusunPos][2], RusunData[rsid][rusunWorld], RusunData[rsid][rusunInterior], -1, 30.00, -1, 0);
        RusunData[rsid][rusunLabel] = CreateDynamic3DTextLabel("[Tekan "GREEN"Y "WHITE"untuk membuka menu]", Y_WHITE, RusunData[rsid][rusunPos][0], RusunData[rsid][rusunPos][1], RusunData[rsid][rusunPos][2] + 0.55, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, RusunData[rsid][rusunWorld], RusunData[rsid][rusunInterior], -1, 10.00, -1, 0);
        RusunData[rsid][rusunChestPickup] = CreateDynamicPickup(1275, 23, 248.3277, 301.5946, 999.1484, rsid, 1, -1, 30.00, -1, 0);
        RusunData[rsid][rusunChestLabel] = CreateDynamic3DTextLabel("[Tekan "GREEN"Y "WHITE"untuk membuka menu]", Y_WHITE, 248.3277, 301.5946, 999.1484 + 0.55, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, rsid, 1, -1, 10.00, -1, 0);
        RusunData[rsid][rusunOutLabel] = CreateDynamic3DTextLabel("[Tekan "GREEN"Y "WHITE"untuk keluar]", Y_WHITE, 244.2521,304.9150,999.1484 + 0.55, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, rsid, 1, -1, 10.00, -1, 0);
    }
    return 1;
}

Rusun_Refresh(rsid)
{
    if(rsid != -1)
    {
        Streamer_SetItemPos(STREAMER_TYPE_PICKUP, RusunData[rsid][rusunPickup], RusunData[rsid][rusunPos][0], RusunData[rsid][rusunPos][1], RusunData[rsid][rusunPos][2]);
        Streamer_SetIntData(STREAMER_TYPE_PICKUP, RusunData[rsid][rusunPickup], E_STREAMER_WORLD_ID, RusunData[rsid][rusunWorld]);
        Streamer_SetIntData(STREAMER_TYPE_PICKUP, RusunData[rsid][rusunPickup], E_STREAMER_INTERIOR_ID, RusunData[rsid][rusunInterior]);

        Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, RusunData[rsid][rusunLabel], RusunData[rsid][rusunPos][0], RusunData[rsid][rusunPos][1], RusunData[rsid][rusunPos][2] + 0.55);
        Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, RusunData[rsid][rusunLabel], E_STREAMER_WORLD_ID, RusunData[rsid][rusunWorld]);
        Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, RusunData[rsid][rusunLabel], E_STREAMER_INTERIOR_ID, RusunData[rsid][rusunInterior]);
    }
    return 1;
}

Player_RusunCount(playerid)
{
    new counting;
    foreach(new rsid : Rusuns)
    {
        if(RusunData[rsid][rusunOwnerID] == AccountData[playerid][pID])
        {
            counting++;
        }
    }
    return counting;
}

Player_NearRusun(playerid, rsid)
{
    new counting, frmxt[522];
    foreach(new i : Player) if(i != playerid) if(IsPlayerInRangeOfPoint(i, 1.5, RusunData[rsid][rusunPos][0], RusunData[rsid][rusunPos][1], RusunData[rsid][rusunPos][2])) 
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
		return Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Undang Teman", "Tidak ada player yang dekat dengan pintu rusun anda!", "Tutup", "");
    }

    Dialog_Show(playerid, "RusunInvite", DIALOG_STYLE_TABLIST, "{DA9100}Pahlawan Roleplay "WHITE"- Undang Teman", frmxt, "Pilih", "Batal");
    return 1;
}

Player_ReturnRusunID(playerid)
{
    new rid = -1;
    foreach(new rsid : Rusuns)
    {
        if(RusunData[rsid][rusunOwnerID] == AccountData[playerid][pID])
        {
            rid = rsid;
        }
    }
    return rid;
}

forward LoadRusunBrankas(playerid);
public LoadRusunBrankas(playerid)
{
    if(cache_num_rows() > 0)
    {
        for(new x; x < cache_num_rows(); x++)
        {
            if(!RusunBrankas[playerid][x][rusunBrankasExists])
            {
                RusunBrankas[playerid][x][rusunBrankasExists] = true;
                cache_get_value_name_int(x, "ID", RusunBrankas[playerid][x][rusunBrankasID]);
                cache_get_value_name_int(x, "Owner", RusunBrankas[playerid][x][rusunBrankasOwner]);
                cache_get_value_name(x, "Item", RusunBrankas[playerid][x][rusunBrankasTemp]);
                cache_get_value_name_int(x, "Model", RusunBrankas[playerid][x][rusunBrankasModel]);
                cache_get_value_name_int(x, "Quantity", RusunBrankas[playerid][x][rusunBrankasQuant]);
            }
        }
        printf("[Player Rusun] Jumlah total Items Rusun yang dimuat untuk %s [DBID: %d]: %d.", AccountData[playerid][pUCP], AccountData[playerid][pID], cache_num_rows());
    }
    return 1;
}

forward Player_OpenSavedClothes(playerid);
public Player_OpenSavedClothes(playerid)
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
        Dialog_Show(playerid, "RusunClothes", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Pakaian", 
        sjjr, "Pilih", "Kembali");
    }
    else
    {
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Pakaian", 
        "Anda tidak memiliki pakaian tersimpan!", "Tutup", "");
    }
    return 1;
}

Rusun_Reset(rsid)
{
    RusunData[rsid][rusunOwnerName][0] = EOS;
    RusunData[rsid][rusunOwnerID] = 0;
    Rusun_Save(rsid);
}

Float:GetRusunTotalWeightFloat(playerid)
{
	new totalweights, Float:totalweights2;

    for(new x; x < MAX_RUSUN_ITEMS; x++)
    {
        if(RusunBrankas[playerid][x][rusunBrankasExists] && RusunBrankas[playerid][x][rusunBrankasOwner] == AccountData[playerid][pID])
        {
            totalweights += GetItemWeight(RusunBrankas[playerid][x][rusunBrankasTemp]) * RusunBrankas[playerid][x][rusunBrankasQuant];
        }
    }
    totalweights2 = float(totalweights)/1000;
    return totalweights2;
}

Rusun_ShowBrankas(playerid)
{
    new 
        curr_page = index_pagination[playerid], 
        count = 0, 
        string[1555], 
        real_i = 0, 
        rsnbrankas_exists[MAX_PAGINATION_PAGES],
        rsnbrankas_name[MAX_PAGINATION_PAGES][32], 
        rsnbrankas_quant[MAX_PAGINATION_PAGES],
        rsnbrankas_id[MAX_PAGINATION_PAGES],
        curr_idx; 

    curr_idx = MAX_PAGINATION_PAGES * curr_page;

    for(new i = 0; i < MAX_PAGINATION_PAGES; i++) 
    {
        rsnbrankas_exists[i] = false;
    }

    format(string, sizeof(string), "Nama Item\tJumlah\tBerat (%.3f/300 kg)\n", GetRusunTotalWeightFloat(playerid));

    for(new i = 0; i < MAX_RUSUN_ITEMS; i++)
    {
        if (RusunBrankas[playerid][i][rusunBrankasExists] && RusunBrankas[playerid][i][rusunBrankasOwner] == AccountData[playerid][pID])
        {
            if (real_i >= curr_idx && real_i < curr_idx + MAX_PAGINATION_PAGES)
            {
                rsnbrankas_exists[real_i - curr_idx] = true;
                rsnbrankas_id[real_i - curr_idx] = i;
                strcopy(rsnbrankas_name[real_i - curr_idx], RusunBrankas[playerid][i][rusunBrankasTemp], 32);
                rsnbrankas_quant[real_i - curr_idx] = RusunBrankas[playerid][i][rusunBrankasQuant];
            }
            real_i++;
        }
    }

    for(new i = 0; i < MAX_PAGINATION_PAGES; i++) 
    {
        if(rsnbrankas_exists[i]) 
        {
            if (i % 2 == 0)
            {
                strcat(string, sprintf(""WHITE"%s\t"WHITE"%d\t"WHITE"-\n", rsnbrankas_name[i], rsnbrankas_quant[i]));
            }
            else
            {
                strcat(string, sprintf(""GRAY"%s\t"GRAY"%d\t"GRAY"-\n", rsnbrankas_name[i], rsnbrankas_quant[i]));
            }
            PlayerListitem[playerid][count++] = rsnbrankas_id[i];
        }
    }

    if(count == 0) 
	{
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "Brankas Rusun", "Isi brankas rusun ini kosong!", "Tutup", "");
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

        Dialog_Show(playerid, "RusunItemVaultWithdraw", DIALOG_STYLE_TABLIST_HEADERS, sprintf("Brankas Rusun: Page %d of %d", curr_page + 1, max_pages),
        string, "Pilih", "Batal");
    }
    return 1;
}

forward OnRusunDeposited(playerid, id);
public OnRusunDeposited(playerid, id)
{
    AccountData[playerid][pMenuShowed] = false;
    RusunBrankas[playerid][id][rusunBrankasID] = cache_insert_id();
    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyimpan item tersebut.");
    return 1;
}

forward OnRusunCreated(playerid, rsid);
public OnRusunCreated(playerid, rsid)
{
    Rusun_Save(rsid);
    Rusun_Rebuild(rsid);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s membuat Rusun dengan ID: %d.", AccountData[playerid][pAdminname], rsid);
    return 1;
}

forward LoadRusun();
public LoadRusun()
{
    new rows = cache_num_rows();
    if(rows)
    {
        new rsid;
		for(new i; i < rows; i++)
		{
            cache_get_value_name_int(i, "ID", rsid);
            cache_get_value_name(i, "Name", RusunData[rsid][rusunName]);
            cache_get_value_name(i, "OwnerName", RusunData[rsid][rusunOwnerName]);
            cache_get_value_name_int(i, "OwnerID", RusunData[rsid][rusunOwnerID]);
            cache_get_value_name_int(i, "Cost_30Day", RusunData[rsid][rusunCost]);
            cache_get_value_name_float(i, "PosX", RusunData[rsid][rusunPos][0]);
            cache_get_value_name_float(i, "PosY", RusunData[rsid][rusunPos][1]);
            cache_get_value_name_float(i, "PosZ", RusunData[rsid][rusunPos][2]);
            cache_get_value_name_float(i, "PosA", RusunData[rsid][rusunPos][3]);
            cache_get_value_name_int(i, "World", RusunData[rsid][rusunWorld]);
            cache_get_value_name_int(i, "Interior", RusunData[rsid][rusunInterior]);

            Rusun_Rebuild(rsid);
            Iter_Add(Rusuns, rsid);
        }
        printf("[Dynamic Rusun] Total number of rusun loaded: %d.", rows);
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && AccountData[playerid][IsLoggedIn] && AccountData[playerid][pSpawned] && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(IsPlayerInRangeOfPoint(playerid, 1.5, 244.2521,304.9150,999.1484) && GetPlayerVirtualWorld(playerid) == AccountData[playerid][pInRusun] && GetPlayerInterior(playerid) == 1) //keluar rusun
        {
            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
            if(AccountData[playerid][pInRusun] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di dalam rusun manapun!");

            new rsid = AccountData[playerid][pInRusun];
            SetPlayerPositionEx(playerid, RusunData[rsid][rusunPos][0], RusunData[rsid][rusunPos][1], RusunData[rsid][rusunPos][2], RusunData[rsid][rusunPos][3]);
            SetPlayerInteriorEx(playerid, RusunData[rsid][rusunInterior]);
            SetPlayerVirtualWorldEx(playerid, RusunData[rsid][rusunWorld]);
            AccountData[playerid][pInRusun] = -1;
            FadeIn(playerid);
        }

        if(IsPlayerInRangeOfPoint(playerid, 1.5, 248.3277,301.5946,999.1484) && GetPlayerVirtualWorld(playerid) == AccountData[playerid][pInRusun] && GetPlayerInterior(playerid) == 1) //brankas rusun
        {
            if(AccountData[playerid][pInRusun] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di dalam rusun manapun!");

            ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, false, false, false, false, 0, true);
            Dialog_Show(playerid, "RusunChest", DIALOG_STYLE_LIST, sprintf("{DA9100}Pahlawan Roleplay "WHITE"- %s", RusunData[AccountData[playerid][pInRusun]][rusunName]), 
            "Undang\n\
            "GRAY"Pakaian\n\
            Membuang Pakaian\n\
            "GRAY"Brankas", "Pilih", "Batal");
        }

        new rsid = Rusun_Nearest(playerid), srss[258];
        if(rsid != -1)
        {
            if(RusunData[rsid][rusunOwnerID] != 0)
            {
                if(RusunData[rsid][rusunOwnerID] != AccountData[playerid][pID])
                {
                    PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
                    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, sprintf("{DA9100}Pahlawan Roleplay "WHITE"- %s", RusunData[rsid][rusunName]), 
                    "Sudah dimiliki warga lain!", "Tutup", "");
                }
                else
                {
                    AccountData[playerid][pInRusun] = rsid;
                    Dialog_Show(playerid, "RusunMenuOwned", DIALOG_STYLE_LIST, sprintf("{DA9100}Pahlawan Roleplay "WHITE"- %s", RusunData[rsid][rusunName]), 
                    "Masuk\n\
                    "GRAY"Cek status sewa", "Pilih", "Batal");
                }
            }
            else
            {
                AccountData[playerid][pInRusun] = rsid;
                format(srss, sizeof(srss), "Sewa\t"DARKGREEN"$%s / bulan\n"YELLOW"Cek sisa waktu sewa ((reset rusun))", FormatMoney(RusunData[rsid][rusunCost]));
                Dialog_Show(playerid, "RusunMenu", DIALOG_STYLE_TABLIST, sprintf("{DA9100}Pahlawan Roleplay "WHITE"- %s", RusunData[rsid][rusunName]), 
                srss, "Pilih", "Batal");
            }
        }
    }
    return 1;
}

Dialog:RusunMenu(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        AccountData[playerid][pInRusun] = -1;
        return 1;
    }

    new rsid = AccountData[playerid][pInRusun];
    switch(listitem)
    {
        case 0:
        {
            if(rsid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan rusun manapun!");
            if(Player_RusunCount(playerid) > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah menyewa rusun!");
            if(RusunData[rsid][rusunOwnerID] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Sudah dimiliki warga lain!");
            if(AccountData[playerid][pMoney] < RusunData[rsid][rusunCost]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

            TakePlayerMoneyEx(playerid, RusunData[rsid][rusunCost]);

            strcopy(RusunData[rsid][rusunOwnerName], GetPlayerRoleplayName(playerid));
            RusunData[rsid][rusunOwnerID] = AccountData[playerid][pID];

            Rusun_Save(rsid);

            SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"You have successfully rented an rusun for 30 days.");
            AccountData[playerid][pInRusun] = -1;
        }
        case 1:
        {
            AccountData[playerid][pInRusun] = -1;
            Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, sprintf("{DA9100}Pahlawan Roleplay "WHITE"- %s", RusunData[rsid][rusunName]), 
            sprintf("Anda memiliki durasi sewa rusun ini selama\n"WHITE"%s", ReturnTimelapse(gettime(), RusunExpired, ""DARKRED"Sewa Expired")), "Tutup", "");
        }
    }
    return 1;
}

Dialog:RusunMenuOwned(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        AccountData[playerid][pInRusun] = -1;
        return 1;
    }

    new rsid = AccountData[playerid][pInRusun];
    switch(listitem)
    {
        case 0:
        {
            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

            SetPlayerPositionEx(playerid, 244.2521,304.9150,999.1484,268.6741);
            SetPlayerInteriorEx(playerid, 1);
            SetPlayerVirtualWorldEx(playerid, AccountData[playerid][pInRusun]);
            RusunTempInvite[playerid] = INVALID_PLAYER_ID;
            FadeIn(playerid);
        }
        case 1:
        {
            AccountData[playerid][pInRusun] = -1;
            Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, sprintf("{DA9100}Pahlawan Roleplay "WHITE"- %s", RusunData[rsid][rusunName]), 
            sprintf("Anda memiliki durasi sewa rusun ini selama\n"WHITE"%s", ReturnTimelapse(gettime(), RusunExpired, ""DARKRED"Sewa Expired")), "Tutup", "");
        }
    }
    return 1;
}

Dialog:RusunInvite(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    new otherid = NearestUser[playerid][listitem], jhtrs[258];
    RusunTempInvite[otherid] = playerid;
    AccountData[otherid][pInRusun] = AccountData[playerid][pInRusun];
    format(jhtrs, sizeof(jhtrs), "Pemilik rusun %s mengundang anda untuk masuk ke dalam.\n\
    Apakah anda ingin menerima undangannya?", RusunData[AccountData[playerid][pInRusun]][rusunName]);
    Dialog_Show(otherid, "RusunInviteConfirm", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Undangan Rusun", 
    jhtrs, "Ya", "No");
    return 1;
}

Dialog:RusunInviteConfirm(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        if(IsPlayerConnected(RusunTempInvite[playerid]))
            ShowTDN(RusunTempInvite[playerid], NOTIFICATION_INFO, "Undangan anda telah ditolak.");
        RusunTempInvite[playerid] = INVALID_PLAYER_ID;
        AccountData[playerid][pInRusun] = -1;
        return 1;
    }
    if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
    
    SetPlayerPositionEx(playerid, 244.2521,304.9150,999.1484,268.6741);
    SetPlayerInteriorEx(playerid, 1);
    SetPlayerVirtualWorldEx(playerid, AccountData[playerid][pInRusun]);
    RusunTempInvite[playerid] = INVALID_PLAYER_ID;
    FadeIn(playerid);
    return 1;
}

Dialog:RusunChest(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;

    switch(listitem)
    {
        case 0: //Undang
        {
            Player_NearRusun(playerid, AccountData[playerid][pInRusun]);
        }
        case 1: //Pakaian
        {
            Player_OpenSavedClothes(playerid);
        }
        case 2: //Membuang
        {
            if(AccountData[playerid][pUsingClothes] == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang memakai pakaian tersimpan apapun!");

            new tstr[128];
            mysql_format(g_SQL, tstr, sizeof(tstr), "DELETE FROM `player_clothes` WHERE `ID`=%d", AccountData[playerid][pUsingClothes]);
            mysql_pquery(g_SQL, tstr);

            AccountData[playerid][pUsingClothes] = 0;
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membuang pakaian tersebut!");

            SetDefaultAppearance(playerid);
        }
        case 3: //Brankas
        {
            AccountData[playerid][pMenuShowed] = true;
            Dialog_Show(playerid, "RusunItemVault", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Rusun", 
            "Simpan Barang\n"GRAY"Ambil Barang", "Pilih", "Kembali");
        }
    }
    return 1;
}

Dialog:RusunClothes(playerid, response, listitem, inputtext[])
{
    if(!response) return Dialog_Show(playerid, "RusunChest", DIALOG_STYLE_LIST, sprintf("{DA9100}Pahlawan Roleplay "WHITE"- %s", RusunData[AccountData[playerid][pInRusun]][rusunName]), 
    "Undang\n\
    "GRAY"Pakaian\n\
    Membuang Pakaian\n\
    "GRAY"Brankas", "Pilih", "Batal");

    if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih!");

    static shstr[128];
    mysql_format(g_SQL, shstr, sizeof(shstr), "SELECT * FROM `player_clothes` WHERE `Owner`=%d", AccountData[playerid][pID]);
    mysql_query(g_SQL, shstr);
    if(cache_num_rows() > 0)
    {
        cache_get_value_name_int(listitem, "ID", AccountData[playerid][pUsingClothes]);
        SetPlayerClothes(playerid, AccountData[playerid][pUsingClothes]);
    }
    return 1;
}

Dialog:RusunItemVault(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        AccountData[playerid][pMenuShowed] = false;
        Dialog_Show(playerid, "RusunChest", DIALOG_STYLE_LIST, sprintf("{DA9100}Pahlawan Roleplay "WHITE"- %s", RusunData[AccountData[playerid][pInRusun]][rusunName]), 
        "Undang\n\
        "GRAY"Pakaian\n\
        Membuang Pakaian\n\
        "GRAY"Brankas", "Pilih", "Batal");
        return 1;
    }

    switch(listitem)
    {
        case 0: //deposit
        {
            new str[1218], count;
            format(str, sizeof(str), "Nama Item\tJumlah\tBerat (%.3f/300 kg)\n", GetRusunTotalWeightFloat(playerid));
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
                Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Rusun", 
                "Anda tidak memiliki barang yang dapat disimpan!", "Tutup", "");
            }
            else
            {
                Dialog_Show(playerid, "RusunItemVaultDeposit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Rusun", str, "Pilih", "Batal");
            }
        }
        case 1: //withdraw
        {
            index_pagination[playerid] = 0;
            Rusun_ShowBrankas(playerid);
        }
    }
    return 1;
}

Dialog:RusunItemVaultDeposit(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        AccountData[playerid][pMenuShowed] = false;
        Dialog_Show(playerid, "RusunChest", DIALOG_STYLE_LIST, sprintf("{DA9100}Pahlawan Roleplay "WHITE"- %s", RusunData[AccountData[playerid][pInRusun]][rusunName]), 
        "Undang\n\
        "GRAY"Pakaian\n\
        Membuang Pakaian\n\
        "GRAY"Brankas", "Pilih", "Batal");
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
    Dialog_Show(playerid, "RusunItemVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Rusun Brankas", 
    shstr, "Input", "Batal");
    return 1;
}

Dialog:RusunItemVaultIn(playerid, response, listitem, inputtext[])
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
        Dialog_Show(playerid, "RusunItemVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Rusun", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(!IsNumericEx(inputtext))
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan menyimpan item:\nNama: "CYAN"%s\n"WHITE"Jumlah di tas: "YELLOW"%d\n"WHITE"Error: Please enter only numbers!\nPlease enter the quantity you want to store:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
        Dialog_Show(playerid, "RusunItemVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Rusun", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(strval(inputtext) < 1 || strval(inputtext) > InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity])
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan menyimpan item:\nNama: "CYAN"%s\n"WHITE"Jumlah di tas: "YELLOW"%d\n"WHITE"Error: Jumlah tidak valid!\nPlease enter the quantity you want to store:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
        Dialog_Show(playerid, "RusunItemVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Rusun", 
        shstr, "Input", "Batal");
        return 1;
    }

    new quantity = strval(inputtext);

    new Float:countingtotalweight;
    countingtotalweight = GetRusunTotalWeightFloat(playerid) + float(quantity * GetItemWeight(InventoryData[playerid][PlayerListitem[playerid][id]][invItem]))/1000;
    if(countingtotalweight > 300) return ShowTDN(playerid, NOTIFICATION_ERROR, "Brankas rusun anda telah penuh!");

    new invstr[1028];
    mysql_format(g_SQL, shstr, sizeof(shstr), "SELECT * FROM `rusun_brankas` WHERE `Owner`=%d AND `Item` = '%e'", AccountData[playerid][pID], InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
    mysql_query(g_SQL, shstr);

    new rows = cache_num_rows();
    if(rows > 0)
    {
        mysql_format(g_SQL, invstr, sizeof(invstr), "UPDATE `rusun_brankas` SET `Quantity` = `Quantity` + %d WHERE `Owner` = %d AND `Item` = '%e'", quantity, AccountData[playerid][pID], InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
        mysql_pquery(g_SQL, invstr);

        ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyimpan item tersebut.");

        for(new x; x < MAX_RUSUN_ITEMS; ++x)
        {
            if(RusunBrankas[playerid][x][rusunBrankasExists] && RusunBrankas[playerid][x][rusunBrankasOwner] == AccountData[playerid][pID] && !strcmp(RusunBrankas[playerid][x][rusunBrankasTemp], InventoryData[playerid][PlayerListitem[playerid][id]][invItem], true))
            {
                RusunBrankas[playerid][x][rusunBrankasQuant] += quantity;
            }
        }
    }
    else
    {
        for(new x; x < MAX_RUSUN_ITEMS; ++x)
        {
            if(!RusunBrankas[playerid][x][rusunBrankasExists]) 
            {
                RusunBrankas[playerid][x][rusunBrankasExists] = true;
                RusunBrankas[playerid][x][rusunBrankasOwner] = AccountData[playerid][pID];
                strcopy(RusunBrankas[playerid][x][rusunBrankasTemp], InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
                RusunBrankas[playerid][x][rusunBrankasModel] = InventoryData[playerid][PlayerListitem[playerid][id]][invModel];
                RusunBrankas[playerid][x][rusunBrankasQuant] = quantity;

                mysql_format(g_SQL, invstr, sizeof(invstr), "INSERT INTO `rusun_brankas` SET `Owner`=%d, `Item`='%e', `Model`=%d, `Quantity`=%d", AccountData[playerid][pID], InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invModel], quantity);
                mysql_pquery(g_SQL, invstr, "OnRusunDeposited", "id", playerid, x);

                break;
            }
        }
    }
    ShowItemBox(playerid, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], sprintf("Removed %dx", quantity), InventoryData[playerid][PlayerListitem[playerid][id]][invModel], 5);
    Inventory_Remove(playerid, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], quantity);
    return 1;
}

Dialog:RusunItemVaultWithdraw(playerid, response, listitem, inputtext[])
{
    if (!response) 
    {
        AccountData[playerid][pMenuShowed] = false;
        Dialog_Show(playerid, "RusunChest", DIALOG_STYLE_LIST, sprintf("{DA9100}Pahlawan Roleplay "WHITE"- %s", RusunData[AccountData[playerid][pInRusun]][rusunName]), 
        "Undang\n\
        "GRAY"Pakaian\n\
        Membuang Pakaian\n\
        "GRAY"Brankas", "Pilih", "Batal");
        return 1;
    }

    if (listitem == -1) 
    {
        AccountData[playerid][pMenuShowed] = false;
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih apapun!");
        return 1;
    }

    if (!strcmp(inputtext, ">> Selanjutnya", true)) 
    {
        index_pagination[playerid]++;

        Rusun_ShowBrankas(playerid);
    } 
    else if (!strcmp(inputtext, "<< Sebelumnya", true)) 
    {
        index_pagination[playerid]--;
        if (index_pagination[playerid] < 0) {
            index_pagination[playerid] = 0;
        }
        Rusun_ShowBrankas(playerid);
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
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Mohon masukkan berapa jumlah yang ingin diambil:", RusunBrankas[playerid][PlayerListitem[playerid][listitem]][rusunBrankasTemp], RusunBrankas[playerid][PlayerListitem[playerid][listitem]][rusunBrankasQuant]);
        Dialog_Show(playerid, "RusunItemVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Rusun", 
        shstr, "Input", "Batal");
    }

    return 1;
}

Dialog:RusunItemVaultOut(playerid, response, listitem, inputtext[])
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
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Error: Tidak dapat dikosongkan!\nPlease enter the quantity you want to retrieve:", RusunBrankas[playerid][PlayerListitem[playerid][id]][rusunBrankasTemp], RusunBrankas[playerid][PlayerListitem[playerid][id]][rusunBrankasQuant]);
        Dialog_Show(playerid, "RusunItemVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Rusun", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(!IsNumericEx(inputtext))
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Error: Please enter only numbers!\nPlease enter the quantity you want to retrieve:", RusunBrankas[playerid][PlayerListitem[playerid][id]][rusunBrankasTemp], RusunBrankas[playerid][PlayerListitem[playerid][id]][rusunBrankasQuant]);
        Dialog_Show(playerid, "RusunItemVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Rusun", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(strval(inputtext) < 1 || strval(inputtext) > RusunBrankas[playerid][PlayerListitem[playerid][id]][rusunBrankasQuant])
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Error: Jumlah tidak valid!\nPlease enter the quantity you want to retrieve:", RusunBrankas[playerid][PlayerListitem[playerid][id]][rusunBrankasTemp], RusunBrankas[playerid][PlayerListitem[playerid][id]][rusunBrankasQuant]);
        Dialog_Show(playerid, "RusunItemVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas Rusun", 
        shstr, "Input", "Batal");
        return 1;
    }

    new quantity = strval(inputtext), jts[150];
    new Float:countingtotalweight;
    countingtotalweight = GetTotalWeightFloat(playerid) + float(quantity * GetItemWeight(RusunBrankas[playerid][PlayerListitem[playerid][id]][rusunBrankasTemp]))/1000;
    if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

    if(!strcmp(RusunBrankas[playerid][PlayerListitem[playerid][id]][rusunBrankasTemp], "Obeng")) 
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

    if(!strcmp(RusunBrankas[playerid][PlayerListitem[playerid][id]][rusunBrankasTemp], "Cangkul")) 
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

    if(!strcmp(RusunBrankas[playerid][PlayerListitem[playerid][id]][rusunBrankasTemp], "Smartphone"))
    {
        mysql_format(g_SQL, jts, sizeof(jts), "SELECT * FROM `player_phones` WHERE `phoneOwner`=%d", AccountData[playerid][pID]);
        mysql_pquery(g_SQL, jts, "OnPlayerBuySmartphone", "i", playerid);
    }
    else
    {
        Inventory_Add(playerid, RusunBrankas[playerid][PlayerListitem[playerid][id]][rusunBrankasTemp], RusunBrankas[playerid][PlayerListitem[playerid][id]][rusunBrankasModel], quantity);
    }
    
    ShowItemBox(playerid, RusunBrankas[playerid][PlayerListitem[playerid][id]][rusunBrankasTemp], sprintf("Received %dx", quantity), RusunBrankas[playerid][PlayerListitem[playerid][id]][rusunBrankasModel], 5);

    RusunBrankas[playerid][PlayerListitem[playerid][id]][rusunBrankasQuant] -= quantity;
    
    if(RusunBrankas[playerid][PlayerListitem[playerid][id]][rusunBrankasQuant] > 0)
    {
        mysql_format(g_SQL, jts, sizeof(jts), "UPDATE `rusun_brankas` SET `Quantity`=%d WHERE `ID`=%d", RusunBrankas[playerid][PlayerListitem[playerid][id]][rusunBrankasQuant], RusunBrankas[playerid][PlayerListitem[playerid][id]][rusunBrankasID]);
        mysql_pquery(g_SQL, jts);
    }
    else
    {
        mysql_format(g_SQL, jts, sizeof(jts), "DELETE FROM `rusun_brankas` WHERE `ID`=%d", RusunBrankas[playerid][PlayerListitem[playerid][id]][rusunBrankasID]);
        mysql_pquery(g_SQL, jts);

        RusunBrankas[playerid][PlayerListitem[playerid][id]][rusunBrankasExists] = false;
        RusunBrankas[playerid][PlayerListitem[playerid][id]][rusunBrankasID] = 0;
        RusunBrankas[playerid][PlayerListitem[playerid][id]][rusunBrankasOwner] = 0;
        RusunBrankas[playerid][PlayerListitem[playerid][id]][rusunBrankasTemp][0] = EOS;
        RusunBrankas[playerid][PlayerListitem[playerid][id]][rusunBrankasModel] = 0;
        RusunBrankas[playerid][PlayerListitem[playerid][id]][rusunBrankasQuant] = 0;
    }
    AccountData[playerid][pMenuShowed] = false;
    return 1;
}

task RusunRentedCheck[60000]() 
{
    if(gettime() > RusunExpired)
    {
        RusunExpired = gettime() + DEFAULT_RUSUN_RESET;

        new fsrs[228];
        mysql_format(g_SQL, fsrs, sizeof(fsrs), "UPDATE `stuffs` SET `rusunreset`=%d WHERE `id`=0", RusunExpired);
        mysql_pquery(g_SQL, fsrs);

        foreach(new rsid : Rusuns)
        {
            Rusun_Reset(rsid);
        }

        SendClientMessageToAllEx(X11_YELLOW, "[i] Semua rusun telah digusur karena sudah 30 hari.");
        print("[i] Semua rusun telah digusur karena sudah 30 hari.");
    }
    return 1;
}