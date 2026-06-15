#include <YSI_Coding\y_hooks>

new Float:efedrinTakePos[][3] =
{
    {-1432.5780,-953.9797,202.4961},
    {-1432.7750,-947.7214,202.4961},
    {-1433.1696,-941.3769,202.4961}
};

new Float:mixingPos[][3] =
{
    {-1630.4089,-2233.4709,31.4765},
    {-1630.1741,-2239.7441,31.4765},
    {-1629.9360,-2246.2415,31.4765}
};

new Float:DTOPos[][3] =
{
    {290.8326,2543.4919,16.8205},
    {258.1614,2933.7319,1.7734},
    {-937.6212,2644.7139,42.2696},
    {-2021.9683,2338.3391,1.5832}
};

IsPlayerNearEfedrinMake(playerid)
{
    for(new x; x < sizeof(efedrinTakePos); x++)
    {
        if(IsPlayerInRangeOfPoint(playerid, 3.0, efedrinTakePos[x][0],efedrinTakePos[x][1],efedrinTakePos[x][2]) && GetPlayerVirtualWorld(playerid) == 0 && GetPlayerInterior(playerid) == 0)
        {
            return true;
        }
    }
    return false;
}

IsPlayerNearEfedrinMix(playerid)
{
    for(new x; x < sizeof(efedrinTakePos); x++)
    {
        if(IsPlayerInRangeOfPoint(playerid, 3.0, mixingPos[x][0],mixingPos[x][1],mixingPos[x][2]) && GetPlayerVirtualWorld(playerid) == 0 && GetPlayerInterior(playerid) == 0)
        {
            return true;
        }
    }
    return false;
}

hook OnGameModeInit()
{
    for(new x; x < sizeof(efedrinTakePos); x++)
    {
        CreateDynamic3DTextLabel("[Y] "WHITE"untuk membuat efedrin", Y_RED, efedrinTakePos[x][0],efedrinTakePos[x][1],efedrinTakePos[x][2], 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 3.0, -1, 0);
    }

    for(new x; x < sizeof(mixingPos); x++)
    {
        CreateDynamic3DTextLabel("[Y] "WHITE"untuk membuat stimulan", Y_RED, mixingPos[x][0],mixingPos[x][1],mixingPos[x][2], 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 3.0, -1, 0);
    }

    CreateDynamic3DTextLabel("[Y] "WHITE"untuk membuat sabu kristal", Y_RED, -1429.6238,-941.1603,202.4961, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 3.0, -1, 0);
    CreateDynamic3DTextLabel("[Y] "WHITE"untuk menyempurnakan sabu", Y_RED, -1635.0948,-2233.9541,31.4765, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 3.0, -1, 0);
    
    CreateDynamic3DTextLabel("[Y] "WHITE"untuk crafting senjata", Y_RED, -1864.4888,-1606.3203,21.7578, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 3.0, -1, 0);
    CreateDynamic3DTextLabel("[Y] "WHITE"untuk crafting drugs & minuman", Y_RED, -2671.4055,2311.7197,23.7979, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 3.0, -1, 0);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && AccountData[playerid][pSpawned] && AccountData[playerid][IsLoggedIn] && IsPlayerNearEfedrinMake(playerid))
    {
        if(Iter_Count(LSPDDuty) < 4 || Iter_Count(LSFDDuty) < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal 4 polisi dan 2 Paramedis on duty!");
        if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");
        if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

        new Float:countingtotalweight;
        countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Efedrin"))/1000;
        if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda penuh!");

        AccountData[playerid][pActivityTime] = 1;
        pMakeEfedrinTimer[playerid] = true;
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "BUAT EFEDRIN");
        ShowProgressBar(playerid);

        ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, true, false, false, false, 0, true);
    }
    else if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && AccountData[playerid][pSpawned] && AccountData[playerid][IsLoggedIn] && IsPlayerNearEfedrinMix(playerid))
    {
        if(Iter_Count(LSPDDuty) < 4 || Iter_Count(LSFDDuty) < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal 4 polisi dan 2 Paramedis on duty!");
        if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");
        if(!PlayerHasItem(playerid, "Efedrin")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki efedrin!");
        if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

        new Float:countingtotalweight;
        countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Stimulan"))/1000;
        if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda penuh!");

        AccountData[playerid][pActivityTime] = 1;
        pMakeStimulanTimer[playerid] = true;
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "BUAT STIMULAN");
        ShowProgressBar(playerid);

        ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, true, false, false, false, 0, true);
    }
    else if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && AccountData[playerid][pSpawned] && AccountData[playerid][IsLoggedIn] && IsPlayerInRangeOfPoint(playerid, 3.0, -1429.6238,-941.1603,202.4961))
    {
        if(Iter_Count(LSPDDuty) < 4 || Iter_Count(LSFDDuty) < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal 4 polisi dan 2 Paramedis on duty!");
        if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");
        if(Inventory_Count(playerid, "Stimulan") < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup stimulan! (Min: 2)");
        if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

        new Float:countingtotalweight;
        countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Sabu Kristal"))/1000;
        if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda penuh!");

        AccountData[playerid][pActivityTime] = 1;
        pMakeMethMentahTimer[playerid] = true;
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "BUAT SABU");
        ShowProgressBar(playerid);

        ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, true, false, false, false, 0, true);
    }
    else if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && AccountData[playerid][pSpawned] && AccountData[playerid][IsLoggedIn] && IsPlayerInRangeOfPoint(playerid, 3.0, -1635.0948,-2233.9541,31.4765))
    {
        if(Iter_Count(LSPDDuty) < 4 || Iter_Count(LSFDDuty) < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal 4 polisi dan 2 Paramedis on duty!");
        if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");
        if(Inventory_Count(playerid, "Jerigen") < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Jerigen! (Min: 1)");
        if(Inventory_Count(playerid, "Sabu Kristal") < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Sabu Kristal! (Min: 2)");
        if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

        new Float:countingtotalweight;
        countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Sabu"))/1000;
        if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda penuh!");

        AccountData[playerid][pActivityTime] = 1;
        pMakeMethTimer[playerid] = true;
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "BUAT SABU");
        ShowProgressBar(playerid);

        ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, true, false, false, false, 0, true);
    }
    else if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && AccountData[playerid][pSpawned] && AccountData[playerid][IsLoggedIn] && IsPlayerInRangeOfPoint(playerid, 3.0, 1477.2319,-31.4594,9.0832))
    {
        if(AccountData[playerid][pFamily] < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari any families/badside!");
        if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
        if(Iter_Count(LSPDDuty) < 4 || Iter_Count(LSFDDuty) < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal 4 polisi dan 2 Paramedis on duty!");
        if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");
        
        new hjes[215];
        format(hjes, sizeof(hjes), "Ini area pencucian uang!\n\
        Uang kotor anda: "RED"$%s\n\
        "YELLOW"(Mohon masukkan berapa jumlah):", FormatMoney(AccountData[playerid][pDirtyMoney]));
        Dialog_Show(playerid, "MoneyWash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Pencucian Uang", hjes, "Input", "Batal");
    }
    else if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && AccountData[playerid][pSpawned] && AccountData[playerid][IsLoggedIn] && IsPlayerInRangeOfPoint(playerid, 3.5, -1864.4888,-1606.3203,21.7578))
    {
        if(AccountData[playerid][pFamily] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota dari badside manapun!");
        if(Iter_Count(LSPDDuty) < 4 || Iter_Count(LSFDDuty) < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal 4 polisi dan 2 Paramedis on duty!");
        if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");
        if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

        static string[1512];
        format(string, sizeof(string), "Nama\tBahan #1\tBahan #2\n\
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
        Dialog_Show(playerid, "CraftingWeapon", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Crafting Senjata", string, "Rakit", "Batal");
    }
    else if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && AccountData[playerid][pSpawned] && AccountData[playerid][IsLoggedIn] && IsPlayerInRangeOfPoint(playerid, 3.5, -2671.4055,2311.7197,23.7979))
    {
        if(Iter_Count(LSPDDuty) < 4 || Iter_Count(LSFDDuty) < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal 4 polisi dan 2 Paramedis on duty!");
        if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");
        if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

        static string[1512];
        format(string, sizeof(string), "Nama\tBahan #1\tBahan #2\n\
        Sinte\tMarijuana:%d/2 | Kertas: %d/1\n\
        "GRAY"Heroin\t"GRAY"Sabu:%d/2 | Kertas: %d/1\t"GRAY"Jerigen: %d/1\n\
        Anggur Merah\tBotol:%d/2 | Water: %d/2\tGula: %d/2 | Micin: %d/2\n\
        "GRAY"Tuak\t"GRAY"Botol:%d/2 | Water: %d/2\t"GRAY"Gula: %d/2 | Micin: %d/2",
        Inventory_Count(playerid, "Marijuana"), Inventory_Count(playerid, "Kertas"),
        Inventory_Count(playerid, "Sabu"), Inventory_Count(playerid, "Kertas"), Inventory_Count(playerid, "Jerigen"),
        Inventory_Count(playerid, "Botol"), Inventory_Count(playerid, "Water"), Inventory_Count(playerid, "Gula"), Inventory_Count(playerid, "Micin"),
        Inventory_Count(playerid, "Botol"), Inventory_Count(playerid, "Water"), Inventory_Count(playerid, "Gula"), Inventory_Count(playerid, "Micin"));
        Dialog_Show(playerid, "CraftingDrugs", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Crafting Senjata", string, "Rakit", "Batal");
    }
    return 1;
}

Dialog:CraftingDrugs(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda belum memilih pilihan!");

    if(Iter_Count(LSPDDuty) < 4 || Iter_Count(LSFDDuty) < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal 4 polisi dan 2 Paramedis on duty!");
    if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");
    switch(listitem)
    {
        case 0: //Sinte
        {
            if(AccountData[playerid][pFamily] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota dari badside manapun!");

            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Sinte"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda penuh!");

            if(Inventory_Count(playerid, "Marijuana") < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup marijuana! (Min: 2)");
            if(Inventory_Count(playerid, "Kertas") < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Kertas! (Min: 1)");

            Inventory_Remove(playerid, "Marijuana", 2);
            Inventory_Remove(playerid, "Kertas");

            ShowItemBox(playerid, "Marijuana", "Removed 2x", 1578, 4);
            ShowItemBox(playerid, "Kertas", "Removed 1x", 19873, 5);
        }
        case 1: //Heroin
        {
            if(AccountData[playerid][pFamily] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota dari badside manapun!");

            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Heroin"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda penuh!");

            if(Inventory_Count(playerid, "Sabu") < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Sabu! (Min: 2)");
            if(Inventory_Count(playerid, "Kertas") < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Kertas! (Min: 1)");
            if(Inventory_Count(playerid, "Jerigen") < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Jerigen! (Min: 1)");

            Inventory_Remove(playerid, "Sabu", 2);
            Inventory_Remove(playerid, "Kertas");
            Inventory_Remove(playerid, "Jerigen");

            ShowItemBox(playerid, "Sabu", "Removed 2x", 1575, 4);
            ShowItemBox(playerid, "Kertas", "Removed 1x", 19873, 5);
            ShowItemBox(playerid, "Jerigen", "Removed 1x", 1650, 6);
        }
        case 2: //Anggur Merah
        {
            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Anggur Merah"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda penuh!");

            if(Inventory_Count(playerid, "Botol") < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Botol! (Min: 2)");
            if(Inventory_Count(playerid, "Air") < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Air! (Min: 2)");
            if(Inventory_Count(playerid, "Gula") < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Gula! (Min: 2)");
            if(Inventory_Count(playerid, "Micin") < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Micin! (Min: 2)");
            
            Inventory_Remove(playerid, "Botol", 2);
            Inventory_Remove(playerid, "Air", 2);
            Inventory_Remove(playerid, "Gula", 2);
            Inventory_Remove(playerid, "Micin", 2);

            ShowItemBox(playerid, "Botol", "Removed 2x", 19570, 4);
            ShowItemBox(playerid, "Air", "Removed 2x", 19570, 5);
            ShowItemBox(playerid, "Gula", "Removed 2x", 1279, 6);
            ShowItemBox(playerid, "Micin", "Removed 2x", 19573, 7);
        }
        case 3: //Tuak
        {
            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Tuak"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda penuh!");

            if(Inventory_Count(playerid, "Botol") < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Botol! (Min: 2)");
            if(Inventory_Count(playerid, "Air") < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Air! (Min: 2)");
            if(Inventory_Count(playerid, "Gula") < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Gula! (Min: 2)");
            if(Inventory_Count(playerid, "Micin") < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Micin! (Min: 2)");
            
            Inventory_Remove(playerid, "Botol", 2);
            Inventory_Remove(playerid, "Air", 2);
            Inventory_Remove(playerid, "Gula", 2);
            Inventory_Remove(playerid, "Micin", 2);

            ShowItemBox(playerid, "Botol", "Removed 2x", 19570, 4);
            ShowItemBox(playerid, "Air", "Removed 2x", 19570, 5);
            ShowItemBox(playerid, "Gula", "Removed 2x", 1279, 6);
            ShowItemBox(playerid, "Micin", "Removed 2x", 19573, 7);
        }
    }
    AccountData[playerid][pTempValue2] = listitem;
    AccountData[playerid][pActivityTime] = 1;
    pCraftingDrugTimer[playerid] = true;
    PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MERAKIT");
    ShowProgressBar(playerid);

    ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, true, false, false, false, 0, true);
    return 1;
}
Dialog:CraftingWeapon(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda belum memilih pilihan!");

    if(Iter_Count(LSPDDuty) < 4 || Iter_Count(LSFDDuty) < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal 4 polisi dan 2 Paramedis on duty!");
    if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");
    
    switch(listitem)
    {
        case 0: //Colt-45
        {
            if(AccountData[playerid][pDirtyMoney] < 5750) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda perlu dirty money $5,750 untuk membeli schematic senjata ini!");

            if(Inventory_Count(playerid, "Alumunium") < 30) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Alumunium! (Min: 30)");
            if(Inventory_Count(playerid, "Kaca") < 35) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Kaca! (Min: 35)");
            if(Inventory_Count(playerid, "Baja") < 45) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Baja! (Min: 45)");
            if(Inventory_Count(playerid, "Karet") < 31) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Karet! (Min: 31)");
            if(Inventory_Count(playerid, "Plastik") < 34) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Plastik! (Min: 34)");
            if(Inventory_Count(playerid, "Material") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup material! (Min: 5)");
            if(Inventory_Count(playerid, "Kulit") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup skin! (Min: 5)");

            TakePlayerDirtyMoney(playerid, 5750);
            Inventory_Remove(playerid, "Alumunium", 30);
            Inventory_Remove(playerid, "Kaca", 35);
            Inventory_Remove(playerid, "Baja", 45);
            Inventory_Remove(playerid, "Karet", 31);
            Inventory_Remove(playerid, "Plastik", 34);
            Inventory_Remove(playerid, "Material", 5);
            Inventory_Remove(playerid, "Kulit", 5);

            ShowItemBox(playerid, "Alumunium", "Removed 30x", 2937, 4);
            ShowItemBox(playerid, "Kaca", "Removed 35x", 1649, 5);
            ShowItemBox(playerid, "Baja", "Removed 45x", 19772, 6);
            ShowItemBox(playerid, "Karet", "Removed 31x", 1316, 7);
            ShowItemBox(playerid, "Plastik", "Removed 34x", 1265, 8);
            ShowItemBox(playerid, "Material", "Removed 5x", 2972, 9);
            ShowItemBox(playerid, "Kulit", "Removed 5x", 1828, 10);
        }
        case 1: //Desert Eagle
        {
            if(AccountData[playerid][pDirtyMoney] < 25125) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda perlu dirty money $25,125 untuk membeli schematic senjata ini!");
            if(Inventory_Count(playerid, "Alumunium") < 55) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Alumunium! (Min: 55)");
            if(Inventory_Count(playerid, "Kaca") < 45) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Kaca! (Min: 45)");
            if(Inventory_Count(playerid, "Baja") < 60) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Baja! (Min: 60)");
            if(Inventory_Count(playerid, "Karet") < 42) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Karet! (Min: 42)");
            if(Inventory_Count(playerid, "Plastik") < 51) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Plastik! (Min: 51)");
            if(Inventory_Count(playerid, "Material") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup material! (Min: 5)");
            if(Inventory_Count(playerid, "Kulit") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup skin! (Min: 5)");

            TakePlayerDirtyMoney(playerid, 25125);
            Inventory_Remove(playerid, "Alumunium", 55);
            Inventory_Remove(playerid, "Kaca", 45);
            Inventory_Remove(playerid, "Baja", 60);
            Inventory_Remove(playerid, "Karet", 42);
            Inventory_Remove(playerid, "Plastik", 51);
            Inventory_Remove(playerid, "Material", 5);
            Inventory_Remove(playerid, "Kulit", 5);

            ShowItemBox(playerid, "Alumunium", "Removed 55x", 2937, 4);
            ShowItemBox(playerid, "Kaca", "Removed 45x", 1649, 5);
            ShowItemBox(playerid, "Baja", "Removed 60x", 19772, 6);
            ShowItemBox(playerid, "Karet", "Removed 42x", 1316, 7);
            ShowItemBox(playerid, "Plastik", "Removed 51x", 1265, 8);
            ShowItemBox(playerid, "Material", "Removed 5x", 2972, 9);
            ShowItemBox(playerid, "Kulit", "Removed 5x", 1828, 10);
        }
        case 2: //uzi
        {
            if(AccountData[playerid][pDirtyMoney] < 11500) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda perlu dirty money $11,500 untuk membeli schematic senjata ini!");
            if(Inventory_Count(playerid, "Alumunium") < 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Alumunium! (Min: 100)");
            if(Inventory_Count(playerid, "Kaca") < 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Kaca! (Min: 50)");
            if(Inventory_Count(playerid, "Baja") < 105) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Baja! (Min: 105)");
            if(Inventory_Count(playerid, "Karet") < 75) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Karet! (Min: 75)");
            if(Inventory_Count(playerid, "Plastik") < 55) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Plastik! (Min: 55)");
            if(Inventory_Count(playerid, "Material") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup material! (Min: 5)");
            if(Inventory_Count(playerid, "Kulit") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup skin! (Min: 5)");
            
            TakePlayerDirtyMoney(playerid, 11500);
            Inventory_Remove(playerid, "Alumunium", 100);
            Inventory_Remove(playerid, "Kaca", 50);
            Inventory_Remove(playerid, "Baja", 105);
            Inventory_Remove(playerid, "Karet", 75);
            Inventory_Remove(playerid, "Plastik", 55);
            Inventory_Remove(playerid, "Material", 5);
            Inventory_Remove(playerid, "Kulit", 5);

            ShowItemBox(playerid, "Alumunium", "Removed 100x", 2937, 4);
            ShowItemBox(playerid, "Kaca", "Removed 50x", 1649, 5);
            ShowItemBox(playerid, "Baja", "Removed 105x", 19772, 6);
            ShowItemBox(playerid, "Karet", "Removed 75x", 1316, 7);
            ShowItemBox(playerid, "Plastik", "Removed 55x", 1265, 8);
            ShowItemBox(playerid, "Material", "Removed 5x", 2972, 9);
            ShowItemBox(playerid, "Kulit", "Removed 5x", 1828, 10);
        }
        case 3: //tec9
        {
            if(AccountData[playerid][pDirtyMoney] < 11500) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda perlu dirty money $11,500 untuk membeli schematic senjata ini!");
            if(Inventory_Count(playerid, "Alumunium") < 105) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Alumunium! (Min: 105)");
            if(Inventory_Count(playerid, "Kaca") < 55) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Kaca! (Min: 55)");
            if(Inventory_Count(playerid, "Baja") < 105) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Baja! (Min: 105)");
            if(Inventory_Count(playerid, "Karet") < 45) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Karet! (Min: 45)");
            if(Inventory_Count(playerid, "Plastik") < 40) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Plastik! (Min: 40)");
            if(Inventory_Count(playerid, "Material") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup material! (Min: 5)");
            if(Inventory_Count(playerid, "Kulit") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup skin! (Min: 5)");

            TakePlayerDirtyMoney(playerid, 11500);
            Inventory_Remove(playerid, "Alumunium", 105);
            Inventory_Remove(playerid, "Kaca", 55);
            Inventory_Remove(playerid, "Baja", 105);
            Inventory_Remove(playerid, "Karet", 45);
            Inventory_Remove(playerid, "Plastik", 40);
            Inventory_Remove(playerid, "Material", 5);
            Inventory_Remove(playerid, "Kulit", 5);

            ShowItemBox(playerid, "Alumunium", "Removed 105x", 2937, 4);
            ShowItemBox(playerid, "Kaca", "Removed 55x", 1649, 5);
            ShowItemBox(playerid, "Baja", "Removed 105x", 19772, 6);
            ShowItemBox(playerid, "Karet", "Removed 45x", 1316, 7);
            ShowItemBox(playerid, "Plastik", "Removed 40x", 1265, 8);
            ShowItemBox(playerid, "Material", "Removed 5x", 2972, 9);
            ShowItemBox(playerid, "Kulit", "Removed 5x", 1828, 10);
        }
        case 4: //SHOTGUN
        {
            if(AccountData[playerid][pDirtyMoney] < 9500) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda perlu dirty money $9,500 untuk membeli schematic senjata ini!");
            if(Inventory_Count(playerid, "Alumunium") < 75) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Alumunium! (Min: 75)");
            if(Inventory_Count(playerid, "Kaca") < 45) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Kaca! (Min: 45)");
            if(Inventory_Count(playerid, "Baja") < 90) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Baja! (Min: 90)");
            if(Inventory_Count(playerid, "Karet") < 30) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Karet! (Min: 30)");
            if(Inventory_Count(playerid, "Plastik") < 30) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Plastik! (Min: 30)");
            if(Inventory_Count(playerid, "Material") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup material! (Min: 5)");
            if(Inventory_Count(playerid, "Kulit") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup skin! (Min: 5)");

            TakePlayerDirtyMoney(playerid, 9500);
            Inventory_Remove(playerid, "Alumunium", 75);
            Inventory_Remove(playerid, "Kaca", 45);
            Inventory_Remove(playerid, "Baja", 90);
            Inventory_Remove(playerid, "Karet", 30);
            Inventory_Remove(playerid, "Plastik", 30);
            Inventory_Remove(playerid, "Material", 5);
            Inventory_Remove(playerid, "Kulit", 5);

            ShowItemBox(playerid, "Alumunium", "Removed 75x", 2937, 4);
            ShowItemBox(playerid, "Kaca", "Removed 45x", 1649, 5);
            ShowItemBox(playerid, "Baja", "Removed 90x", 19772, 6);
            ShowItemBox(playerid, "Karet", "Removed 30x", 1316, 7);
            ShowItemBox(playerid, "Plastik", "Removed 30x", 1265, 8);
            ShowItemBox(playerid, "Material", "Removed 5x", 2972, 9);
            ShowItemBox(playerid, "Kulit", "Removed 5x", 1828, 10);
        }
        case 5: //AK47
        {
            if(AccountData[playerid][pDirtyMoney] < 52500) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda perlu dirty money $52,500 untuk membeli schematic senjata ini!");
            if(Inventory_Count(playerid, "Alumunium") < 135) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Alumunium! (Min: 135)");
            if(Inventory_Count(playerid, "Kaca") < 75) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Kaca! (Min: 75)");
            if(Inventory_Count(playerid, "Baja") < 145) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Baja! (Min: 145)");
            if(Inventory_Count(playerid, "Karet") < 75) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Karet! (Min: 75)");
            if(Inventory_Count(playerid, "Plastik") < 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Plastik! (Min: 50)");
            if(Inventory_Count(playerid, "Material") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup material! (Min: 5)");
            if(Inventory_Count(playerid, "Kulit") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup skin! (Min: 5)");

            TakePlayerDirtyMoney(playerid, 52500);
            Inventory_Remove(playerid, "Alumunium", 135);
            Inventory_Remove(playerid, "Kaca", 75);
            Inventory_Remove(playerid, "Baja", 145);
            Inventory_Remove(playerid, "Karet", 75);
            Inventory_Remove(playerid, "Plastik", 50);
            Inventory_Remove(playerid, "Material", 5);
            Inventory_Remove(playerid, "Kulit", 5);

            ShowItemBox(playerid, "Alumunium", "Removed 135x", 2937, 4);
            ShowItemBox(playerid, "Kaca", "Removed 75x", 1649, 5);
            ShowItemBox(playerid, "Baja", "Removed 145x", 19772, 6);
            ShowItemBox(playerid, "Karet", "Removed 75x", 1316, 7);
            ShowItemBox(playerid, "Plastik", "Removed 50x", 1265, 8);
            ShowItemBox(playerid, "Material", "Removed 5x", 2972, 9);
            ShowItemBox(playerid, "Kulit", "Removed 5x", 1828, 10);
        }
    }
    AccountData[playerid][pTempValue2] = listitem;
    AccountData[playerid][pActivityTime] = 1;
    pCraftingWeaponTimer[playerid] = true;
    PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MERAKIT");
    ShowProgressBar(playerid);

    ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, true, false, false, false, 0, true);
    return 1;
}

Dialog:DisposPhoneCatalog(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    
    if(AccountData[playerid][pUsedDisphone]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah menghubungi DTO, mohon tunggu pesanan atau segera ambil pesenan anda!");

    switch(listitem)
    {
        case 0: //colt-45
        {
            if(AccountData[playerid][pBankMoney] < 300000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Saldo bank anda tidak mencukupi!");

            AccountData[playerid][pTypeDisphone] = 1;
            AccountData[playerid][pUsedDisphone] = true;
            AccountData[playerid][pWaitingDisphone] = gettime() + 900;
            SendClientMessage(playerid, X11_WHITE, "Stranger (phone) says: Kami akan segera mengirimkan barang yang kau pesan dalam waktu 15 menit...");
            SendClientMessage(playerid, X11_WHITE, "...informasi berikutnya akan kami sampaikan jika barang telah tiba.");
        }
        case 1: //desert eagle
        {
            if(AccountData[playerid][pBankMoney] < 700000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Saldo bank anda tidak mencukupi!");

            AccountData[playerid][pTypeDisphone] = 2;
            AccountData[playerid][pUsedDisphone] = true;
            AccountData[playerid][pWaitingDisphone] = gettime() + 900;
            SendClientMessage(playerid, X11_WHITE, "Stranger (phone) says: Kami akan segera mengirimkan barang yang kau pesan dalam waktu 15 menit...");
            SendClientMessage(playerid, X11_WHITE, "...informasi berikutnya akan kami sampaikan jika barang telah tiba.");
        }
        case 2: //shotgun
        {
            if(AccountData[playerid][pBankMoney] < 600000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Saldo bank anda tidak mencukupi!");

            AccountData[playerid][pTypeDisphone] = 3;
            AccountData[playerid][pUsedDisphone] = true;
            AccountData[playerid][pWaitingDisphone] = gettime() + 900;
            SendClientMessage(playerid, X11_WHITE, "Stranger (phone) says: Kami akan segera mengirimkan barang yang kau pesan dalam waktu 15 menit...");
            SendClientMessage(playerid, X11_WHITE, "...informasi berikutnya akan kami sampaikan jika barang telah tiba.");
        }
        case 3: //tec - 9
        {
            if(AccountData[playerid][pBankMoney] < 700000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Saldo bank anda tidak mencukupi!");

            AccountData[playerid][pTypeDisphone] = 4;
            AccountData[playerid][pUsedDisphone] = true;
            AccountData[playerid][pWaitingDisphone] = gettime() + 900;
            SendClientMessage(playerid, X11_WHITE, "Stranger (phone) says: Kami akan segera mengirimkan barang yang kau pesan dalam waktu 15 menit...");
            SendClientMessage(playerid, X11_WHITE, "...informasi berikutnya akan kami sampaikan jika barang telah tiba.");
        }
        case 4: //uzi
        {
            if(AccountData[playerid][pBankMoney] < 700000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Saldo bank anda tidak mencukupi!");

            AccountData[playerid][pTypeDisphone] = 5;
            AccountData[playerid][pUsedDisphone] = true;
            AccountData[playerid][pWaitingDisphone] = gettime() + 900;
            SendClientMessage(playerid, X11_WHITE, "Stranger (phone) says: Kami akan segera mengirimkan barang yang kau pesan dalam waktu 15 menit...");
            SendClientMessage(playerid, X11_WHITE, "...informasi berikutnya akan kami sampaikan jika barang telah tiba.");
        }
    }
    return 1;
}

Dialog:MegaMallCatalog(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    switch(listitem)
    {
        case 0: //kevlar
        {
            if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");
            if(AccountData[playerid][pMoney] < 85000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Kevlar"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid, inventory anda penuh!");

            TakePlayerMoneyEx(playerid, 85000);
            Inventory_Add(playerid, "Kevlar", 19515);
            ShowItemBox(playerid, "Cash", "Removed $85,000x", 1212, 4);
            ShowItemBox(playerid, "Kevlar", "Received 1x", 19515, 5);
        }
        case 1: //Linggis
        {
            if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");
            if(AccountData[playerid][pMoney] < 800) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Linggis"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid, inventory anda penuh!");

            TakePlayerMoneyEx(playerid, 800);
            Inventory_Add(playerid, "Linggis", 18634);
            ShowItemBox(playerid, "Cash", "Removed $800x", 1212, 4);
            ShowItemBox(playerid, "Linggis", "Received 1x", 18634, 5);
        }
        case 2: //Kunci T
        {
            if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");
            if(AccountData[playerid][pMoney] < 600) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Kunci T"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid, inventory anda penuh!");

            TakePlayerMoneyEx(playerid, 600);
            Inventory_Add(playerid, "Kunci T", 18633);
            ShowItemBox(playerid, "Cash", "Removed $600x", 1212, 4);
            ShowItemBox(playerid, "Kunci T", "Received 1x", 18633, 5);
        }
        // case 3: //toolkit
        // {
        // if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");
        //     if(AccountData[playerid][pMoney] < 100000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

        //     new Float:countingtotalweight;
        //     countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Toolkit"))/1000;
        //     if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid, inventory anda penuh!");

        //     TakePlayerMoneyEx(playerid, 100000);
        //     Inventory_Add(playerid, "Toolkit", 19921);
        //     ShowItemBox(playerid, "Cash", "Removed $1,000.00x", 1212, 4);
        //     ShowItemBox(playerid, "Toolkit", "Received 1x", 19921, 5);
        // }
        case 3: //Kentang
        {
            if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");
            if(AccountData[playerid][pMoney] < 60) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Kentang"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid, inventory anda penuh!");

            AccountData[playerid][pTempValue] = 1;
            Dialog_Show(playerid, "KitchStuffBuy", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Mega Mall", 
            "Anda akan membeli Kentang seharga "GREEN"$60/pcs\n\
            "YELLOW"(Mohon masukkan berapa jumlah yang ingin dibeli):", "Beli", "Batal");
        }
        case 4: //Kubis
        {
            if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");
            if(AccountData[playerid][pMoney] < 60) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Kubis"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid, inventory anda penuh!");

            AccountData[playerid][pTempValue] = 2;
            Dialog_Show(playerid, "KitchStuffBuy", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Mega Mall", 
            "Anda akan membeli Kubis seharga "GREEN"$60/pcs\n\
            "YELLOW"(Mohon masukkan berapa jumlah yang ingin dibeli):", "Beli", "Batal");
        }
        case 5: //Bawang
        {
            if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");
            if(AccountData[playerid][pMoney] < 60) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Bawang"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid, inventory anda penuh!");

            AccountData[playerid][pTempValue] = 3;
            Dialog_Show(playerid, "KitchStuffBuy", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Mega Mall", 
            "Anda akan membeli Bawang seharga "GREEN"$60/pcs\n\
            "YELLOW"(Mohon masukkan berapa jumlah yang ingin dibeli):", "Beli", "Batal");
        }
        case 6: //Tomat
        {
            if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");
            if(AccountData[playerid][pMoney] < 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Tomat"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid, inventory anda penuh!");

            AccountData[playerid][pTempValue] = 4;
            Dialog_Show(playerid, "KitchStuffBuy", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Mega Mall", 
            "Anda akan membeli Tomat seharga "GREEN"$50/pcs\n\
            "YELLOW"(Mohon masukkan berapa jumlah yang ingin dibeli):", "Beli", "Batal");
        }
        case 7: //Air
        {
            if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");
            if(AccountData[playerid][pMoney] < 40) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Air"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid, inventory anda penuh!");
            
            AccountData[playerid][pTempValue] = 5;
            Dialog_Show(playerid, "KitchStuffBuy", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Mega Mall", 
            "Anda akan membeli Air seharga "GREEN"$40/pcs\n\
            "YELLOW"(Mohon masukkan berapa jumlah yang ingin dibeli):", "Beli", "Batal");
        }
        case 8: //Gula
        {
            if(AccountData[playerid][pMoney] < 70) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Gula"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid, inventory anda penuh!");

            AccountData[playerid][pTempValue] = 6;
            Dialog_Show(playerid, "KitchStuffBuy", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Mega Mall", 
            "Anda akan membeli Gula seharga "GREEN"$70/pcs\n\
            "YELLOW"(Mohon masukkan berapa jumlah yang ingin dibeli):", "Beli", "Batal");
        }
        case 9: //Micin
        {
            if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");
            if(AccountData[playerid][pMoney] < 70) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Micin"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid, inventory anda penuh!");

            AccountData[playerid][pTempValue] = 7;
            Dialog_Show(playerid, "KitchStuffBuy", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Mega Mall", 
            "Anda akan membeli Micin seharga "GREEN"$70/pcs\n\
            "YELLOW"(Mohon masukkan berapa jumlah yang ingin dibeli):", "Beli", "Batal");
        }
        case 10: //Kertas
        {
            if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");
            if(AccountData[playerid][pMoney] < 120) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Kertas"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid, inventory anda penuh!");

            AccountData[playerid][pTempValue] = 8;
            Dialog_Show(playerid, "KitchStuffBuy", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Mega Mall", 
            "Anda akan membeli Kertas seharga "GREEN"$120/pcs\n\
            "YELLOW"(Mohon masukkan berapa jumlah yang ingin dibeli):", "Beli", "Batal");
        }
        case 11: //Karung Goni
        {
            if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");
            if(AccountData[playerid][pMoney] < 1300) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Karung Goni"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid, inventory anda penuh!");

            TakePlayerMoneyEx(playerid, 1300);
            Inventory_Add(playerid, "Karung Goni", 2663);
            ShowItemBox(playerid, "Cash", "Removed $1,300", 1212, 4);
            ShowItemBox(playerid, "Karung Goni", "Received 1x", 2663, 5);
        }
    }
    return 1;
}

Dialog:MoneyWash(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;

    if(isnull(inputtext))
    {
        return Dialog_Show(playerid, "MoneyWash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Money Laundry",
        "Error: Tidak dapat dikosongkan!\n\
        This is money laundry area!\n\
        Your dirty money: "RED"$%s\n\
        "YELLOW"(Please insert how much to be washed):", "Input", "Batal");
    }          

    if (!IsNumericEx(inputtext)) return Dialog_Show(playerid, "MoneyWash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Money Laundry",
    "Error: Masukkan hanya angka!\n\
    This is money laundry area!\n\
    Your dirty money: "RED"$%s\n\
    "YELLOW"(Please insert how much to be washed):", "Input", "Batal");

    if(strval(inputtext) < 100) return Dialog_Show(playerid, "MoneyWash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Money Laundry",
    "Error: Invalid amount, you can't wash less than $100!\n\
    This is money laundry area!\n\
    Your dirty money: "RED"$%s\n\
    "YELLOW"(Please insert how much to be washed):", "Input", "Batal");

    if(AccountData[playerid][pDirtyMoney] < RoundNegativeToPositive(strval(inputtext))) return ShowTDN(playerid, NOTIFICATION_ERROR, "Dirty money anda tidak cukup!");

    new Float:hasilpemotongan = RoundNegativeToPositive(strval(inputtext)) * 0.2;
    TempMoneyLaundry[playerid] = strval(inputtext);
    TempMoneyLaundryR[playerid] = RoundNegativeToPositive(strval(inputtext)) - hasilpemotongan;

    AccountData[playerid][pActivityTime] = 1;
    pMoneyLaundryTimer[playerid] = true;
	PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENCUCI UANG");
	ShowProgressBar(playerid);

    ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, true, false, false, false, 0, true);

    SendTeamMessage(FACTION_LSPD, 0xff4b4bff, "> Pencucian uang sedang berlangsung <");
    return 1;
}

Dialog:KitchStuffBuy(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
        AccountData[playerid][pTempValue] = -1;
        return 1;
    }

    if(isnull(inputtext))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");

    if(!IsNumericEx(inputtext))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya dapat diisi angka!");

    if(strval(inputtext) < 1)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid!");

    switch(AccountData[playerid][pTempValue])
    {
        case 1:
        {
            static pricing;
            pricing = strval(inputtext) * 60;

            if(AccountData[playerid][pMoney] < RoundNegativeToPositive(pricing)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

            static Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(strval(inputtext) * GetItemWeight("Kentang"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid, inventory anda penuh!");

            TakePlayerMoneyEx(playerid, pricing);

            Inventory_Add(playerid, "Kentang", 19638, strval(inputtext));

            ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(pricing)), 1212, 4);
            ShowItemBox(playerid, "Kentang", sprintf("Received %dx", strval(inputtext)), 19638, 5);

            ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Anda telah membeli ~b~%d Kentang ~l~seharga ~r~$%s.", strval(inputtext), FormatMoney(pricing)));
        }
        case 2:
        {
            static pricing;
            pricing = strval(inputtext) * 60;

            if(AccountData[playerid][pMoney] < RoundNegativeToPositive(pricing)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

            static Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(strval(inputtext) * GetItemWeight("Kubis"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid, inventory anda penuh!");

            TakePlayerMoneyEx(playerid, pricing);

            Inventory_Add(playerid, "Kubis", 19637, strval(inputtext));

            ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(pricing)), 1212, 4);
            ShowItemBox(playerid, "Kubis", sprintf("Received %dx", strval(inputtext)), 19637, 5);

            ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Anda telah membeli ~b~%d Kubis ~l~seharga ~r~$%s.", strval(inputtext), FormatMoney(pricing)));
        }
        case 3:
        {
            static pricing;
            pricing = strval(inputtext) * 60;

            if(AccountData[playerid][pMoney] < RoundNegativeToPositive(pricing)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

            static Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(strval(inputtext) * GetItemWeight("Bawang"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid, inventory anda penuh!");

            TakePlayerMoneyEx(playerid, pricing);

            Inventory_Add(playerid, "Bawang", 19636, strval(inputtext));

            ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(pricing)), 1212, 4);
            ShowItemBox(playerid, "Bawang", sprintf("Received %dx", strval(inputtext)), 19636, 5);

            ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Anda telah membeli ~b~%d Bawang ~l~seharga ~r~$%s.", strval(inputtext), FormatMoney(pricing)));
        }
        case 4:
        {
            static pricing;
            pricing = strval(inputtext) * 50;

            if(AccountData[playerid][pMoney] < RoundNegativeToPositive(pricing)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

            static Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(strval(inputtext) * GetItemWeight("Tomat"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid, inventory anda penuh!");

            TakePlayerMoneyEx(playerid, pricing);

            Inventory_Add(playerid, "Tomat", 19636, strval(inputtext));

            ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(pricing)), 1212, 4);
            ShowItemBox(playerid, "Tomat", sprintf("Received %dx", strval(inputtext)), 19636, 5);

            ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Anda telah membeli ~b~%d Tomat ~l~seharga ~r~$%s.", strval(inputtext), FormatMoney(pricing)));
        }
        case 5:
        {
            static pricing;
            pricing = strval(inputtext) * 40;

            if(AccountData[playerid][pMoney] < RoundNegativeToPositive(pricing)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

            static Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(strval(inputtext) * GetItemWeight("Air"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid, inventory anda penuh!");

            TakePlayerMoneyEx(playerid, pricing);

            Inventory_Add(playerid, "Air", 19570, strval(inputtext));

            ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(pricing)), 1212, 4);
            ShowItemBox(playerid, "Air", sprintf("Received %dx", strval(inputtext)), 19570, 5);

            ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Anda telah membeli ~b~%d Air ~l~seharga ~r~$%s.", strval(inputtext), FormatMoney(pricing)));
        }
        case 6:
        {
            static pricing;
            pricing = strval(inputtext) * 70;

            if(AccountData[playerid][pMoney] < RoundNegativeToPositive(pricing)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

            static Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(strval(inputtext) * GetItemWeight("Gula"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid, inventory anda penuh!");

            TakePlayerMoneyEx(playerid, pricing);

            Inventory_Add(playerid, "Gula", 1279, strval(inputtext));

            ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(pricing)), 1212, 4);
            ShowItemBox(playerid, "Gula", sprintf("Received %dx", strval(inputtext)), 1279, 5);

            ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Anda telah membeli ~b~%d Gula ~l~seharga ~r~$%s.", strval(inputtext), FormatMoney(pricing)));
        }
        case 7:
        {
            static pricing;
            pricing = strval(inputtext) * 70;

            if(AccountData[playerid][pMoney] < RoundNegativeToPositive(pricing)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

            static Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(strval(inputtext) * GetItemWeight("Micin"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid, inventory anda penuh!");

            TakePlayerMoneyEx(playerid, pricing);

            Inventory_Add(playerid, "Micin", 19573, strval(inputtext));

            ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(pricing)), 1212, 4);
            ShowItemBox(playerid, "Micin", sprintf("Received %dx", strval(inputtext)), 19573, 5);

            ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Anda telah membeli ~b~%d Micin ~l~seharga ~r~$%s.", strval(inputtext), FormatMoney(pricing)));
        }
        case 8:
        {
            static pricing;
            pricing = strval(inputtext) * 120;

            if(AccountData[playerid][pMoney] < RoundNegativeToPositive(pricing)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

            static Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(strval(inputtext) * GetItemWeight("Kertas"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid, inventory anda penuh!");

            TakePlayerMoneyEx(playerid, pricing);

            Inventory_Add(playerid, "Kertas", 19873, strval(inputtext));

            ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(pricing)), 1212, 4);
            ShowItemBox(playerid, "Kertas", sprintf("Received %dx", strval(inputtext)), 19873, 5);

            ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Anda telah membeli ~b~%d Kertas ~l~seharga ~r~$%s.", strval(inputtext), FormatMoney(pricing)));
        }
    }
    return 1;
}

Dialog:PawnShopCatalog(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    if(listitem == -1 || listitem > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih opsi apapun!");
    
    if(listitem == 5) //sell
    {
        if(!PlayerHasItem(playerid, "Elektronik Rusak")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Elektronik Rusak!");
        new pricing = Inventory_Count(playerid, "Elektronik Rusak") * 125;
        
        GivePlayerMoneyEx(playerid, pricing);

        ShowItemBox(playerid, "Elektronik Rusak", sprintf("Removed %dx", Inventory_Count(playerid, "Elektronik Rusak")), 2041, 5);
        ShowItemBox(playerid, "Cash", sprintf("Received $%sx", FormatMoney(pricing)), 1212, 6);
        Inventory_Remove(playerid, "Elektronik Rusak", -1);
        return 1;
    }
    AccountData[playerid][pTempValue] = listitem;
    Dialog_Show(playerid, "PawnShopRedeem", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Pawn Shop", "Mohon masukkan jumlah yang ingin ditukarkan:", 
    "Redeem", "Batal");
    return 1;
}

Dialog:PawnShopRedeem(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat mengosongkan kolom ini!");
    if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya angka yang dapat dimasukkan!");

    if(strval(inputtext) < 1 || strval(inputtext) > Inventory_Count(playerid, "Material")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid!");

    switch(AccountData[playerid][pTempValue])
    {
        case 0: //Alumunium
        {
            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(strval(inputtext) * GetItemWeight("Alumunium"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid, inventory anda penuh!");

            Inventory_Remove(playerid, "Material", strval(inputtext));
            ShowItemBox(playerid, "Material", sprintf("Removed %dx", strval(inputtext)), 2972, 4);

            Inventory_Add(playerid, "Alumunium", 2937, strval(inputtext));
            ShowItemBox(playerid, "Alumunium", sprintf("Added %dx", strval(inputtext)), 2937, 5);
        }
        case 1: //Kaca
        {
            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(strval(inputtext) * GetItemWeight("Kaca"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid, inventory anda penuh!");

            Inventory_Remove(playerid, "Material", strval(inputtext));
            ShowItemBox(playerid, "Material", sprintf("Removed %dx", strval(inputtext)), 2972, 4);

            Inventory_Add(playerid, "Kaca", 1649, strval(inputtext));
            ShowItemBox(playerid, "Kaca", sprintf("Added %dx", strval(inputtext)), 1649, 5);
        }
        case 2: //Baja
        {
            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(strval(inputtext) * GetItemWeight("Baja"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid, inventory anda penuh!");

            Inventory_Remove(playerid, "Material", strval(inputtext));
            ShowItemBox(playerid, "Material", sprintf("Removed %dx", strval(inputtext)), 2972, 4);

            Inventory_Add(playerid, "Baja", 19772, strval(inputtext));
            ShowItemBox(playerid, "Baja", sprintf("Added %dx", strval(inputtext)), 19772, 5);
        }
        case 3: //Karet
        {
            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(strval(inputtext) * GetItemWeight("Karet"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid, inventory anda penuh!");

            Inventory_Remove(playerid, "Material", strval(inputtext));
            ShowItemBox(playerid, "Material", sprintf("Removed %dx", strval(inputtext)), 2972, 4);

            Inventory_Add(playerid, "Karet", 1316, strval(inputtext));
            ShowItemBox(playerid, "Karet", sprintf("Added %dx", strval(inputtext)), 1316, 5);
        }
        case 4: //Plastik
        {
            new Float:countingtotalweight;
            countingtotalweight = GetTotalWeightFloat(playerid) + float(strval(inputtext) * GetItemWeight("Plastik"))/1000;
            if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid, inventory anda penuh!");

            Inventory_Remove(playerid, "Material", strval(inputtext));
            ShowItemBox(playerid, "Material", sprintf("Removed %dx", strval(inputtext)), 2972, 4);

            Inventory_Add(playerid, "Plastik", 1265, strval(inputtext));
            ShowItemBox(playerid, "Plastik", sprintf("Added %dx", strval(inputtext)), 1265, 5);
        }
    }
    return 1;
}

ptask UpdateDTOTime[5000](playerid) 
{
    if(AccountData[playerid][pSpawned] && AccountData[playerid][pUsedDisphone])
    {
        if(AccountData[playerid][pWaitingDisphone] != 0 && AccountData[playerid][pWaitingDisphone] <= gettime())
        {
            AccountData[playerid][pWaitingDisphone] = 0;

            if(DestroyDynamicRaceCP(AccountData[playerid][pGPSCP]))
		        AccountData[playerid][pGPSCP] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

            if(DestroyDynamicObject(AccountData[playerid][pDTOObject]))
                AccountData[playerid][pDTOObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

            if(DestroyDynamic3DTextLabel(AccountData[playerid][pDTOLabel]))
                AccountData[playerid][pDTOLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
            
            new randpos = random(sizeof(DTOPos));
            AccountData[playerid][pGPSCP] = CreateDynamicRaceCP(1, DTOPos[randpos][0],DTOPos[randpos][1],DTOPos[randpos][2], DTOPos[randpos][0],DTOPos[randpos][1],DTOPos[randpos][2], 3.5, 0, 0, playerid, 10000.00, -1, 0);
            AccountData[playerid][pDTOObject] = CreateDynamicObject(964, DTOPos[randpos][0],DTOPos[randpos][1],DTOPos[randpos][2]-0.75, 0.0, 0.0, 0.0, 0, 0, playerid, 100.00, 100.00, -1);
            AccountData[playerid][pDTOLabel] = CreateDynamic3DTextLabel("Use "YELLOW"/pickupdto "WHITE"to claim your DTO order item", X11_WHITE, DTOPos[randpos][0],DTOPos[randpos][1],DTOPos[randpos][2], 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, playerid, 10.0, -1, 0);

            SendClientMessage(playerid, X11_WHITE, "Stranger (phone) says: Hey, kawan. Barang pesananmu telah tiba di lokasi, pergilah ke sana dan ambil pesananmu segera...");
            SendClientMessageEx(playerid, X11_WHITE, "...lokasinya berada di %s, aku sudah mengirimkan letak lokasinya padamu.", GetLocation(DTOPos[randpos][0],DTOPos[randpos][1],DTOPos[randpos][2]));
            ShowTDN(playerid, NOTIFICATION_WARNING, "Mohon ikuti checkpoint di map!");
        }
    }
    return 1;
}

YCMD:megamall(playerid, params[], help)
{
    if(!IsPlayerInRangeOfPoint(playerid, 3.0, 2479.1294,-1963.1271,16.7578) && !IsPlayerInRangeOfPoint(playerid, 3.0, -1881.4132,823.1917,35.1767)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di mega mall!");
    
    Dialog_Show(playerid, "MegaMallCatalog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Mega Mall", 
    "Item\tPrice\n\
    Kevlar\t$85,000\n\
    "GRAY"Crowbar\t"GRAY"$800\n\
    Kunci T\t$600\n\
    "GRAY"Kentang\t"GRAY"$60\n\
    Kubis\t$60\n\
    "GRAY"Bawang\t"GRAY"$60\n\
    Tomat\t$50\n\
    "GRAY"Air\t"GRAY"$40\n\
    Gula\t$70\n\
    "GRAY"Micin\t"GRAY"$70\n\
    Kertas\t$120\n\
    "GRAY"Blindfold\t"GRAY"$1,300", "Beli", "Batal");
    return 1;
}

YCMD:pickupdto(playerid, params[], help)
{
    if(!AccountData[playerid][pUsedDisphone]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum menghubungi DTO!");
    if(AccountData[playerid][pWaitingDisphone] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pesanan anda belum tiba, harap bersabar!");
    
    new Float:pox, Float:poy, Float:poz;
    GetDynamicObjectPos(AccountData[playerid][pDTOObject], pox, poy, poz);

    if(!IsPlayerInRangeOfPoint(playerid, 3.5, pox, poy, poz)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan lokasi drop off pesanan!");

    if(!PlayerHasItem(playerid, "Disposable Phone")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki disposable phone!");

    switch(AccountData[playerid][pTypeDisphone])
    {
        case 1:
        {
            if(AccountData[playerid][pBankMoney] < 3000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Saldo bank anda tidak mencukupi!");
            AccountData[playerid][pBankMoney] -= 3000;
            GivePlayerWeaponEx(playerid, 22, 250, WEAPON_TYPE_PLAYER);
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mengambil ~b~Colt-45");
            ShowItemBox(playerid, "Colt-45", "Received 1x", 346, 5);
        }
        case 2:
        {
            if(AccountData[playerid][pBankMoney] < 7000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Saldo bank anda tidak mencukupi!");
            AccountData[playerid][pBankMoney] -= 7000;
            GivePlayerWeaponEx(playerid, 24, 250, WEAPON_TYPE_PLAYER);
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mengambil ~b~Desert Eagle");
            ShowItemBox(playerid, "Desert Eagle", "Received 1x", 348, 5);
        }
        case 3:
        {
            if(AccountData[playerid][pBankMoney] < 6000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Saldo bank anda tidak mencukupi!");
            AccountData[playerid][pBankMoney] -= 6000;
            GivePlayerWeaponEx(playerid, 25, 300, WEAPON_TYPE_PLAYER);
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mengambil ~b~Shotgun");
            ShowItemBox(playerid, "Shotgun", "Received 1x", 349, 5);
        }
        case 4:
        {
            if(AccountData[playerid][pBankMoney] < 7000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Saldo bank anda tidak mencukupi!");
            AccountData[playerid][pBankMoney] -= 7000;
            GivePlayerWeaponEx(playerid, 32, 500, WEAPON_TYPE_PLAYER);
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mengambil ~b~Tec-9");
            ShowItemBox(playerid, "Tec-9", "Received 1x", 372, 5);
        }
        case 5:
        {
            if(AccountData[playerid][pBankMoney] < 7000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Saldo bank anda tidak mencukupi!");
            AccountData[playerid][pBankMoney] -= 7000;
            GivePlayerWeaponEx(playerid, 28, 500, WEAPON_TYPE_PLAYER);
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mengambil ~b~Uzi");
            ShowItemBox(playerid, "MP5", "Received 1x", 353, 5);
        }
    }

    if(DestroyDynamicRaceCP(AccountData[playerid][pGPSCP]))
        AccountData[playerid][pGPSCP] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

    if(DestroyDynamicObject(AccountData[playerid][pDTOObject]))
        AccountData[playerid][pDTOObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

    if(DestroyDynamic3DTextLabel(AccountData[playerid][pDTOLabel]))
        AccountData[playerid][pDTOLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    Inventory_Remove(playerid, "Disposable Phone");
    ShowItemBox(playerid, "Disposable Phone", "Removed 1x", 330, 4);
    
    AccountData[playerid][pTypeDisphone] = 0;
    AccountData[playerid][pUsedDisphone] = false;
    AccountData[playerid][pWaitingDisphone] = 0;
    return 1;
}