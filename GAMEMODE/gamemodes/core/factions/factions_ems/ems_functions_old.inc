#include <YSI_Coding\y_hooks>

#define MAX_HOSPITAL 2

enum e_player_ems_details
{
    //duty
    STREAMER_TAG_AREA:LSFDDutyArea[MAX_HOSPITAL],
    STREAMER_TAG_OBJECT:LSFDDutyObjid[MAX_HOSPITAL],

    //locker
    STREAMER_TAG_AREA:LSFDLockerArea[MAX_HOSPITAL],
    STREAMER_TAG_OBJECT:LSFDLockerObjid[MAX_HOSPITAL],

    //bos desk
    STREAMER_TAG_AREA:LSFDBosDeskArea[MAX_HOSPITAL],
    STREAMER_TAG_OBJECT:LSFDBosDeskObjid[MAX_HOSPITAL],

    //garage
    STREAMER_TAG_AREA:LSFDGarageArea[MAX_HOSPITAL],
    STREAMER_TAG_OBJECT:LSFDGarageObjid[MAX_HOSPITAL],

    //helipad
    STREAMER_TAG_CP:LSFDHelipadCP,

    //brankas
    STREAMER_TAG_AREA:LSFDBrankasArea[MAX_HOSPITAL],
    STREAMER_TAG_OBJECT:LSFDBrankasObjid[MAX_HOSPITAL],

    //vault
    STREAMER_TAG_AREA:LSFDVaultArea[MAX_HOSPITAL],
    STREAMER_TAG_OBJECT:LSFDVaultObjid[MAX_HOSPITAL],

    //not saved
    bool:LSFDDuringReviving
};
new PlayerFactionLSFDVars[MAX_PLAYERS][e_player_ems_details];
new RevivingPlayerTimer[MAX_PLAYERS] = {0, ...};

enum _LSFD_Details
{
    Float:LSFDDutyPos[3],
    Float:LSFDLockerPos[3],
    Float:LSFDBosDeskPos[3],
    Float:LSFDGaragePos[3],
    Float:LSFDGarageSpawnPos[4],
    Float:LSFDHelipadPos[3],
    Float:LSFDHelipadSpawnPos[4],
    Float:LSFDBrankasPos[3],
    Float:LSFDVaultPos[3],
    LSFDVWID,
    LSFDIntID
};

new LSFD_Stuff[MAX_HOSPITAL][_LSFD_Details] =
{
    //on duty, locker, bos desk, garage pos, garage spawn pos, helipad, helipad spawn pos, brankas, vault item
    {{-2251.6997,529.5413,-6.5823}, {-2238.9736,540.0027,-6.5823}, {-2285.1838,509.2675,-6.5611}, {1178.2064,-1319.9713,14.1087}, {1182.9861,-1324.7009,13.7283,179.6811}, {1153.9786,-1316.1848,31.5071}, {1162.5276,-1303.2913,34.5215,269.8198}, {-2241.3938,495.3191,-6.5419}, {-2234.7866,506.0222,-6.5616}, 77, 77}, //LS
    {{-161.5104,2705.8625,62.7141}, {-156.3686,2708.1431,62.7142}, {-149.0615,2703.3801,62.7141}, {-174.8023,2730.0388,62.7241}, {-176.7314,2725.8879,63.2584,90.0016}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}, {-158.4799,2703.6138,62.7141}, {-150.8468,2707.5747,62.7141}, 0, 0} //gurun ayam
};

static const LSFDRank[11][] = 
{
    "N/A",

    "Firefighter I", //1 
    "Firefighter II", //2
    "Firefighter III", //3
    "Engineer", //4
    "Fire Captain I", //5
    "Fire Captain II", //6
    "Battalion Chief", //7
    "Assistant Fire Chief", //8
    "Deputy Fire Chief", //9
    "Fire Chief" //10
};

GetPlayerNearestLSFDGarage(playerid)
{
    for(new x; x < MAX_HOSPITAL; x++)
    {
        if(IsPlayerInRangeOfPoint(playerid, 5.0, LSFD_Stuff[x][LSFDGaragePos][0], LSFD_Stuff[x][LSFDGaragePos][1], LSFD_Stuff[x][LSFDGaragePos][2]) && GetPlayerVirtualWorld(playerid) == 0 && GetPlayerInterior(playerid) == 0)
        {
            return x;
        }
    }
    return -1;
}

IsPlayerNearLSFDGarage(playerid)
{
    for(new x; x < MAX_HOSPITAL; x++)
    {
        if(IsPlayerInRangeOfPoint(playerid, 5.0, LSFD_Stuff[x][LSFDGaragePos][0], LSFD_Stuff[x][LSFDGaragePos][1], LSFD_Stuff[x][LSFDGaragePos][2]) && GetPlayerVirtualWorld(playerid) == 0 && GetPlayerInterior(playerid) == 0)
        {
            return true;
        }
    }
    return false;
}

LSFD_ShowBrankas(playerid)
{
    new counted, jljs[1218];
    format(jljs, sizeof(jljs), "Nama Item\tJumlah\n");
    for(new i; i < MAX_FACTIONS_ITEMS; i++)
    {
        if(FactionBrankas[i][factionBrankasExists] && FactionBrankas[i][factionBrankasFID] == FACTION_LSFD)
        {
            format(jljs, sizeof(jljs), "%s%s\t%d\n", jljs, FactionBrankas[i][factionBrankasTemp], FactionBrankas[i][factionBrankasQuant]);
            PlayerListitem[playerid][counted++] = i;
        }
    }

    if(counted == 0)
    {
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari EMS", 
        "Lemari ini isinya kosong!", "Tutup", "");
    }
    else
    {
        Dialog_Show(playerid, "ParamedisVaultWithdraw", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari EMS", 
        jljs, "Pilih", "Batal");
    }
    return 1;
}

forward RevivingPlayer(playerid, targetid);
public RevivingPlayer(playerid, targetid)
{
    if(!AccountData[playerid][LSFDDuringReviving])
    {
        KillTimer(RevivingPlayerTimer[playerid]);
        RevivingPlayerTimer[playerid] = -1;
        AccountData[playerid][pActivityTime] = 0;
        AccountData[playerid][LSFDDuringReviving] = false;
        StopRunningAnimation(playerid);
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsPlayerConnected(playerid))
    {
        KillTimer(RevivingPlayerTimer[playerid]);
        RevivingPlayerTimer[playerid] = -1;
        AccountData[playerid][pActivityTime] = 0;
        AccountData[playerid][LSFDDuringReviving] = false;
        StopRunningAnimation(playerid);
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsPlayerConnected(targetid))
    {
        KillTimer(RevivingPlayerTimer[playerid]);
        RevivingPlayerTimer[playerid] = -1;
        AccountData[playerid][pActivityTime] = 0;
        AccountData[playerid][LSFDDuringReviving] = false;
        StopRunningAnimation(playerid);
        HideProgressBar(playerid);
        SEM(playerid, "Pemain tersebut tidak ada di server!");
        return 0;
    }

    if(!IsPlayerNearPlayer(playerid, targetid, 2.5)) 
    {
        KillTimer(RevivingPlayerTimer[playerid]);
        RevivingPlayerTimer[playerid] = -1;
        AccountData[playerid][pActivityTime] = 0;
        AccountData[playerid][LSFDDuringReviving] = false;
        StopRunningAnimation(playerid);
        HideProgressBar(playerid);
        SEM(playerid, "You are not close enough to the player!");
        return 0;
    }

    if(AccountData[playerid][pActivityTime] >= 21)
    {
        KillTimer(RevivingPlayerTimer[playerid]);
        RevivingPlayerTimer[playerid] = -1;
        AccountData[playerid][pActivityTime] = 0;
        AccountData[playerid][LSFDDuringReviving] = false;
        StopRunningAnimation(playerid);
        HideProgressBar(playerid);

        SetPlayerHealthEx(targetid, 100.0);
        AccountData[targetid][pKnockdown] = false;
        AccountData[targetid][pKnockdownTime] = 0;
        AccountData[targetid][pHunger] = 50;
        AccountData[targetid][pThirst] = 50;
        AccountData[targetid][pStress] = 0;
        new frmtsql[215];
        mysql_format(g_SQL, frmtsql, sizeof(frmtsql), "UPDATE `player_characters` SET `Char_Knockdown` = 0, `Char_KnockdownTime` = 0, `Char_Hunger` = 50, `Char_Thirst` = 50, `Char_Stress` = 0 WHERE `pID` = %d", AccountData[targetid][pID]);
        mysql_pquery(g_SQL, frmtsql);

        StopRunningAnimation(targetid);

        NearestSingle[playerid] = INVALID_PLAYER_ID;
    }
    else
    {
        AccountData[playerid][pActivityTime] ++;

        static Float:progressvalue;
        progressvalue = AccountData[playerid][pActivityTime] * 102.0/21;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
    }
    return 1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && AccountData[playerid][pFaction] == FACTION_LSFD)
    {
        for(new x; x < MAX_HOSPITAL; x++)
        {
            if(areaid == PlayerFactionLSFDVars[playerid][LSFDDutyArea][x])
            {
                if(!AccountData[playerid][pOnDuty])
                {
                    ShowNotifBox(playerid, "[Y] ~g~On Duty");
                }
                else
                {
                    ShowNotifBox(playerid, "[Y] ~r~Off Duty");
                }
            }

            if(areaid == PlayerFactionLSFDVars[playerid][LSFDLockerArea][x])
            {
                ShowNotifBox(playerid, "[Y] Locker LSFD");
            }

            if(areaid == PlayerFactionLSFDVars[playerid][LSFDBosDeskArea][x])
            {
                ShowNotifBox(playerid, "[Y] Akses Bos Desk");
            }

            if(areaid == PlayerFactionLSFDVars[playerid][LSFDGarageArea][x])
            {
                ShowNotifBox(playerid, "[Y] Garasi LSFD");
            }

            if(areaid == PlayerFactionLSFDVars[playerid][LSFDBrankasArea][x])
            {
                ShowNotifBox(playerid, "[Y] Akses Brankas");
            }
            if(areaid == PlayerFactionLSFDVars[playerid][LSFDVaultArea][x])
            {
                ShowNotifBox(playerid, "[Y] Akses Lemari");
            }
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA: areaid)
{
    for(new x; x < MAX_HOSPITAL; x++)
    {
        if(areaid == PlayerFactionLSFDVars[playerid][LSFDDutyArea][x])
        {
            HideNotifBox(playerid);
        }

        if(areaid == PlayerFactionLSFDVars[playerid][LSFDLockerArea][x])
        {
            HideNotifBox(playerid);
        }

        if(areaid == PlayerFactionLSFDVars[playerid][LSFDBosDeskArea][x])
        {
            HideNotifBox(playerid);
        }

        if(areaid == PlayerFactionLSFDVars[playerid][LSFDGarageArea][x])
        {
            HideNotifBox(playerid);
        }

        if(areaid == PlayerFactionLSFDVars[playerid][LSFDBrankasArea][x])
        {
            HideNotifBox(playerid);
        }
        if(areaid == PlayerFactionLSFDVars[playerid][LSFDVaultArea][x])
        {
            HideNotifBox(playerid);
        }
    }
    return 1;
}

hook OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP:checkpointid)
{
    if(checkpointid == PlayerFactionLSFDVars[playerid][LSFDHelipadCP])
    {
        if(Iter_Contains(Vehicle, FactionHeliVeh[playerid]))
            ShowNotifBox(playerid, "[Y] Kembalikan Heli");
        else
            ShowNotifBox(playerid, "[Y] Keluarkan Heli");
    }
    return 1;
}

hook OnPlayerLeaveDynamicCP(playerid, STREAMER_TAG_CP:checkpointid)
{
    if(checkpointid == PlayerFactionLSFDVars[playerid][LSFDHelipadCP])
    {
        HideNotifBox(playerid);
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && AccountData[playerid][pFaction] == FACTION_LSFD && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        for(new x; x < MAX_HOSPITAL; x++)
        {
            if(IsPlayerInDynamicArea(playerid, PlayerFactionLSFDVars[playerid][LSFDDutyArea][x]))
            {
                if(!AccountData[playerid][pOnDuty])
                {
                    AccountData[playerid][pOnDuty] = true;
                    SendClienMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Anda sekarang "GREEN"On Duty.");
                    Iter_Add(LSFDDuty, playerid);
                }
                else
                {
                    AccountData[playerid][pOnDuty] = false;
                    SendClienMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Anda sekarang "RED"Off Duty.");
                    Iter_Remove(LSFDDuty, playerid);
                }
                HideNotifBox(playerid);
            }

            if(IsPlayerInDynamicArea(playerid, PlayerFactionLSFDVars[playerid][LSFDLockerArea][x]))
            {
                HideNotifBox(playerid);
                Dialog_Show(playerid, "ParamedisLocker", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Seragam", 
                "Baju Warga\n\
                "GRAY"Baju LSFD", "Pilih", "Batal");
            }

            if(IsPlayerInDynamicArea(playerid, PlayerFactionLSFDVars[playerid][LSFDBosDeskArea][x]))
            {
                HideNotifBox(playerid);
                if(AccountData[playerid][pFactionRank] < 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank KOMDIS untuk akses Bos Desk!");

                Dialog_Show(playerid, "ParamedisBosdesk", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Bos Desk", 
                "Invite\n\
                "GRAY"Kelola Jabatan\n\
                Kick\n\
                "GRAY"Saldo Finansial\n\
                Deposit Saldo\n\
                "GRAY"Tarik Saldo", "Pilih", "Batal");
            }

            if(IsPlayerInDynamicArea(playerid, PlayerFactionLSFDVars[playerid][LSFDGarageArea][x]))
            {
                HideNotifBox(playerid);
                Dialog_Show(playerid, ParamedisGarage, DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Garasi EMS", 
                "Keluarkan Kendaraan\n\
                "GRAY"Simpan Kendaraan\n\
                Beli Kendaraan\n\
                "GRAY"Hapus Kendaraan", "Pilih", "Batal");
            }

            if(IsPlayerInDynamicArea(playerid, PlayerFactionLSFDVars[playerid][LSFDBrankasArea][x]))
            {
                HideNotifBox(playerid);
                Dialog_Show(playerid, DIALOG_BRANKAS_LSFD, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas LSFD", 
                "Item\n\
                Perban\n\
                "GRAY"Medkit\n\
                Pil Stress", "Pilih", "Batal");
            }

            if(IsPlayerInDynamicArea(playerid, PlayerFactionLSFDVars[playerid][LSFDVaultArea][x]))
            {
                HideNotifBox(playerid);

                AccountData[playerid][pMenuShowed] = true;
                Dialog_Show(playerid, ParamedisVault, DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari LSFD", 
                "Simpan Barang\n"GRAY"Ambil Barang", "Pilih", "Kembali");
            }
        }
        if(IsValidDynamicCP(PlayerFactionLSFDVars[playerid][LSFDHelipadCP]) && IsPlayerInDynamicCP(playerid, PlayerFactionLSFDVars[playerid][LSFDHelipadCP]))
        {
            if(Iter_Contains(Vehicle, FactionHeliVeh[playerid]))
            {
                DestroyVehicle(FactionHeliVeh[playerid]);
                FactionHeliVeh[playerid] = INVALID_VEHICLE_ID;
            }
            else
            {
                FactionHeliVeh[playerid] = CreateVehicle(487,LSFD_Stuff[0][LSFDHelipadSpawnPos][0],LSFD_Stuff[0][LSFDHelipadSpawnPos][1], LSFD_Stuff[0][LSFDHelipadSpawnPos][2],LSFD_Stuff[0][LSFDHelipadSpawnPos][3], 3,1, 60000, false);
                VehicleCore[FactionHeliVeh[playerid]][vCoreFuel] = 100;
                SetValidVehicleHealth(FactionHeliVeh[playerid], 1000.0); 
                VehicleCore[FactionHeliVeh[playerid]][vCoreLocked] = false;
                PutPlayerInVehicleEx(playerid, FactionHeliVeh[playerid], 0);
                SwitchVehicleEngine(FactionHeliVeh[playerid], true);
                SwitchVehicleDoors(FactionHeliVeh[playerid], false);
            }
            HideNotifBox(playerid);
        }
    }
    else if(newkeys & KEY_CTRL_BACK && AccountData[playerid][pFaction] == FACTION_LSFD && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(AccountData[playerid][pInEvent]) return 1;
        
        new count = 0, frmxt[522];
        foreach(new i : Player) if(i != playerid) if(IsPlayerNearPlayer(playerid, i, 2.5)) 
		{
			format(frmxt, sizeof(frmxt), "%sKantong - (%d)\n", frmxt, i);
			NearestUser[playerid][count++] = i;
		}

        if(count > 0) 
		{
            Dialog_Show(playerid, FactionPanel, DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Faction Panel", 
            frmxt, "Pilih", "Batal");
		}
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case ParamedisVault:
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
                        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari LSFD", 
                        "Anda tidak memiliki barang yang dapat disimpan!", "Tutup", "");
                    }
                    else
                    {
                        Dialog_Show(playerid, ParamedisVaultDeposit, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari LSFD", str, "Pilih", "Batal");
                    }
                }
                case 1: //withdraw
                {
                    index_pagination[playerid] = 0;
                    LSFD_ShowBrankas(playerid);
                }
            }
        }

        case ParamedisVaultDeposit:
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

            new shstr[528];
            format(shstr, sizeof(shstr), ""WHITE"Anda akan menyimpan item:\nNama: "CYAN"%s\n"WHITE"Jumlah di tas: "YELLOW"%d\n"WHITE"Mohon masukkan jumlah yang ingin disimpan:", InventoryData[playerid][PlayerListitem[playerid][listitem]][invItem], InventoryData[playerid][PlayerListitem[playerid][listitem]][invQuantity]);
            Dialog_Show(playerid, ParamedisVaultIn, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari LSFD", 
            shstr, "Input", "Batal");
        }
        case ParamedisVaultIn:
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
                Dialog_Show(playerid, ParamedisVaultIn, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari LSFD", 
                shstr, "Input", "Batal");
                return 1;
            }

            if(!IsNumericEx(inputtext))
            {
                AccountData[playerid][pMenuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nMohon diisi hanya angka!\nMohon masukkan berapa jumlah yang ingin disimpan:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
                Dialog_Show(playerid, ParamedisVaultIn, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari LSFD", 
                shstr, "Input", "Batal");
                return 1;
            }

            if(strval(inputtext) < 1 || strval(inputtext) > InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity])
            {
                AccountData[playerid][pMenuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nJumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin disimpan:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
                Dialog_Show(playerid, ParamedisVaultIn, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari LSFD", 
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
        }
        case ParamedisVaultWithdraw:
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

            new shstr[528];
            format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Mohon masukkan berapa jumlah yang ingin diambil:", FactionBrankas[PlayerListitem[playerid][listitem]][factionBrankasTemp], FactionBrankas[PlayerListitem[playerid][listitem]][factionBrankasQuant]);
            Dialog_Show(playerid, ParamedisVaultOut, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari LSFD", 
            shstr, "Input", "Batal");
        }
        case ParamedisVaultOut:
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
                Dialog_Show(playerid, ParamedisVaultOut, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari LSFD", 
                shstr, "Input", "Batal");
                return 1;
            }

            if(!IsNumericEx(inputtext))
            {
                AccountData[playerid][pMenuShowed] = true;
                format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Mohon diisi hanya angka!\nMohon masukkan berapa jumlah yang ingin diambil:", FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant]);
                Dialog_Show(playerid, ParamedisVaultOut, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari LSFD", 
                shstr, "Input", "Batal");
                return 1;
            }

            if(strval(inputtext) < 1 || strval(inputtext) > FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant])
            {
                AccountData[playerid][pMenuShowed] = true;
                format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Jumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin diambil:", FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant]);
                Dialog_Show(playerid, ParamedisVaultOut, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari LSFD", 
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
        }
        case ParamedisLocker:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
            if(AccountData[playerid][pFaction] != FACTION_LSFD) return SEM(playerid, "Anda bukan anggota Paramedis Pahlawan Roleplay!");
            switch(listitem)
            {
                case 0: //baju warga
                {
                    SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
                    AccountData[playerid][pIsUsingUniform] = false;
                }
                case 1: //baju ems
                {
                    Dialog_Show(playerid, ParamedisUniform, DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Baju LSFD", 
                    "LSFD 1\n\
                    "GRAY"LSFD 2\n\
                    LSFD 3", "Pilih", "Batal");
                }
            }
        }
        case ParamedisUniform:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
            if(AccountData[playerid][pFaction] != FACTION_LSFD) return SEM(playerid, "Anda bukan anggota Paramedis Pahlawan Roleplay!");

            switch(listitem)
            {
                case 0: AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (70) : (308);
                case 1: AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (276) : (141);
                case 2: AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (275) : (150);
            }
            SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
            AccountData[playerid][pIsUsingUniform] = true;
        }
        case ParamedisBosdesk:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
            if(AccountData[playerid][pFaction] != FACTION_LSFD) return SEM(playerid, "Anda bukan anggota Paramedis Pahlawan Roleplay!");
            if(AccountData[playerid][pFactionRank] < 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank KOMDIS untuk akses Bos Desk!");

            switch(listitem)
            {
                case 0: //invite
                {
                    new frmxt[522], count = 0;

                    foreach(new i : Player) if(i != playerid) if(IsPlayerNearPlayer(playerid, i, 1.5)) 
                    {
                        format(frmxt, sizeof(frmxt), "%sKantong - (%d)\n", frmxt, i);
                        NearestUser[playerid][count++] = i;
                    }

                    if(count == 0)
                    {
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Undang Faction", "Tidak ada pemain terdekat!", "Tutup", "");
                    }

                    Dialog_Show(playerid, ParamedisInviteConfirm, DIALOG_STYLE_TABLIST, "{DA9100}Pahlawan Roleplay "WHITE"- Undang Faction", frmxt, "Pilih", "Batal");
                }
                case 1: //kelola jabatan
                {
                    mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 2 ORDER BY Char_FactionRank DESC");

                    new rows = cache_num_rows();
                    if(rows)
                    {
                        new fckname[64], fckrank, fcklastlogin[30];
                        
                        AddDialogListitem(playerid, "Nama\tRank\tLast Online");
                        for(new i; i < rows; ++i)
                        {
                            cache_get_value_name(i, "Char_Name", fckname);
                            cache_get_value_name_int(i, "Char_FactionRank", fckrank);
                            cache_get_value_name(i, "Char_LastLogin", fcklastlogin);
                            
                            AddDialogListitem(playerid, "%s\t%s\t%s", fckname, LSFDRank[fckrank], fcklastlogin);
                        }
                        ShowPlayerDialogPages(playerid, "LSFDSetRank", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", "Pilih", "Batal", 15, ""GREEN">> Lanjut", ""ORANGE"<< Kembali");
                    }
                    else
                    {
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", "Faction ini tidak memiliki anggota!", "Tutup", "");
                    }
                }
                case 2: //kick
                {
	                mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 2 ORDER BY Char_FactionRank DESC");

                    new rows = cache_num_rows();
                    if(rows)
                    {
                        new fckname[64], fckrank, fcklastlogin[30];
                        
                        AddDialogListitem(playerid, "Nama\tRank\tLast Online");
                        for(new i; i < rows; ++i)
                        {
                            cache_get_value_name(i, "Char_Name", fckname);
                            cache_get_value_name_int(i, "Char_FactionRank", fckrank);
                            cache_get_value_name(i, "Char_LastLogin", fcklastlogin);
                            
                            AddDialogListitem(playerid, "%s\t%s\t%s", fckname, LSFDRank[fckrank], fcklastlogin);
                        }
                        ShowPlayerDialogPages(playerid, "LSFDKickMember", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Kick Faction", "Pilih", "Batal", 15, ""GREEN">> Lanjut", ""ORANGE"<< Kembali");
                    }
                    else
                    {
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Kick Faction", "Faction ini tidak memiliki anggota!", "Tutup", "");
                    }
                }
            }
        }
        case ParamedisInviteConfirm:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
            if(AccountData[playerid][pFaction] != FACTION_LSFD) return SEM(playerid, "Anda bukan anggota Paramedis Pahlawan Roleplay!");
            if(AccountData[playerid][pFactionRank] < 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank KOMDIS untuk akses Bos Desk!");

            new targetid = NearestUser[playerid][listitem], icsr[128];
            if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
            AccountData[targetid][pFaction] = FACTION_LSFD;
            AccountData[targetid][pFactionRank] = 1;
            mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction` = 2, `Char_FactionRank` = 1 WHERE `pID` = %d", AccountData[targetid][pID]);
            mysql_pquery(g_SQL, icsr);
            SendClientMessageEx(playerid, X11_PALEGREEN4, "[Info] "WHITE"You have successfully invited "YELLOW"%s "WHITE"to the faction.", AccountData[targetid][pName]);

            InsertFactionLog("Invite", sprintf("%s %s - %s %s", AccountData[playerid][pName], AccountData[playerid][pUCP], AccountData[targetid][pName], AccountData[targetid][pUCP]), "LSFD");
        }
        case ParamedisSetRankConfirm:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
            if(AccountData[playerid][pFaction] != FACTION_LSFD) return SEM(playerid, "Anda bukan anggota Paramedis Pahlawan Roleplay!");
            if(AccountData[playerid][pFactionRank] < 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank KOMDIS untuk akses Bos Desk!");

            if(isnull(inputtext)) return Dialog_Show(playerid, ParamedisSetRankConfirm, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
            "Error: Tidak dapat dikosongkan!\n\
            Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. Training\n\
            2. Perawat\n\
            3. Dokter\n\
            4. Dokter\n\
            5. Dokter Spesialis\n\
            6. KOMDIS\n\
            7. WAKADIR\n\
            8. SEKBEN\n\
            9. Direktur", "Set", "Batal");
            
            if(!IsNumericEx(inputtext)) return Dialog_Show(playerid, ParamedisSetRankConfirm, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
            "Error: Masukkan hanya angka!\n\
            Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. Training\n\
            2. Perawat\n\
            3. Dokter\n\
            4. Dokter\n\
            5. Dokter Spesialis\n\
            6. KOMDIS\n\
            7. WAKADIR\n\
            8. SEKBEN\n\
            9. Direktur", "Set", "Batal");

            if(strval(inputtext) < 1 || strval(inputtext) > AccountData[playerid][pFactionRank]) return Dialog_Show(playerid, ParamedisSetRankConfirm, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
            "Error: Tidak dapat diisi dibawah 1 atau lebih tinggi dari jabatan anda!\n\
            Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. Training\n\
            2. Perawat\n\
            3. Dokter\n\
            4. Dokter\n\
            5. Dokter Spesialis\n\
            6. KOMDIS\n\
            7. WAKADIR\n\
            8. SEKBEN\n\
            9. Direktur", "Set", "Batal");

            new hjh[128];
            mysql_format(g_SQL, hjh, sizeof(hjh), "UPDATE `player_characters` SET `Char_FactionRank`=%d WHERE `pID`=%d", strval(inputtext), AccountData[playerid][pTempSQLFactMemberID]);
            mysql_pquery(g_SQL, hjh);

            foreach(new i : Player)
            {
                if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && AccountData[playerid][pTempSQLFactMemberID] == AccountData[i][pID])
                {
                    AccountData[i][pFactionRank] = strval(inputtext);
                    SendClientMessage(i, X11_PALEGREEN4, "[Info] "WHITE"Jabatan anda di faction telah diperbarui.");
                    InsertFactionLog("Set Rank", sprintf("%s %s - %s %s LV %d", AccountData[playerid][pName], AccountData[playerid][pUCP], AccountData[i][pName], AccountData[i][pUCP], strval(inputtext)), "LSFD");
                }
            }

            SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"Anda telah merubah jabatan faction pemain tersebut.");

        }
        case ParamedisGarage:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
            if(AccountData[playerid][pFaction] != FACTION_LSFD) return SEM(playerid, "Anda bukan anggota Paramedis Pahlawan Roleplay!");
            switch(listitem)
            {
                case 0: //keluarkan kendaraan
                {
                    if(CountPlayerFactVehInGarage(playerid, FACTION_LSFD) < 1) return SEM(playerid, "Anda tidak memiliki kendaraan faction yang tersimpan!");

                    new id, count = CountPlayerFactVehInGarage(playerid, FACTION_LSFD), lstr[596];
                    format(lstr,sizeof(lstr),"No\tModel Kendaraan\tNomor Plat\n");
                    for(new itt; itt < count; itt++)
                    {
                        id = GetVehicleIDStoredFactGarage(playerid, itt, FACTION_LSFD);
                        if(itt == count)
                        {
                            format(lstr,sizeof(lstr), "%s%d\t%s\t%s", lstr, itt+1, GetVehicleModelName(PlayerVehicle[id][pVehModelID]), PlayerVehicle[id][pVehPlate]);
                        }
                        else format(lstr,sizeof(lstr), "%s%d\t%s\t%s\n", lstr, itt+1, GetVehicleModelName(PlayerVehicle[id][pVehModelID]), PlayerVehicle[id][pVehPlate]);
                    }
                    Dialog_Show(playerid, ParamedisGarageTakeout, DIALOG_STYLE_TABLIST_HEADERS,"{DA9100}Pahlawan Roleplay "WHITE"- Keluarkan Kendaraan", lstr, "Pilih","Batal");
                }
                case 1: //simpan kendaraan
                {
                    new carid = INVALID_VEHICLE_ID, foundnearby = 0;

                    if((carid = Vehicle_Nearest(playerid, 10.0)) != INVALID_VEHICLE_ID)
                    {
                        if(PlayerVehicle[carid][pVehOwnerID] != AccountData[playerid][pID]) return SEM(playerid, "Kendaraan ini bukan milik anda!");
                        if(PlayerVehicle[carid][pVehRental] > -1 || PlayerVehicle[carid][pVehRentTime] > 0) return SEM(playerid, "Anda tidak dapat menyimpan kendaraan rental!");
                        if(PlayerVehicle[carid][pVehFaction] != FACTION_LSFD) return SEM(playerid, "Kendaraan tersebut bukan dari LSFD Pahlawan Roleplay!");
                        Vehicle_GetStatus(carid);
                        PlayerVehicle[carid][pVehFactStored] = FACTION_LSFD;

                        foundnearby++;
                        DisableVehicleSpeedCap(PlayerVehicle[carid][pVehPhysic]);
                        SetVehicleNeonLights(PlayerVehicle[carid][pVehPhysic], false, PlayerVehicle[carid][pVehNeon], 0);

                        DestroyVehicle(PlayerVehicle[carid][pVehPhysic]);
                        PlayerVehicle[carid][pVehPhysic] = INVALID_VEHICLE_ID;
                    }
                    if(!foundnearby)
                        return SEM(playerid, "Tidak ada kendaraan dari LSFD Pahlawan Roleplay milik anda di sekitar!");
                }
                case 2: //beli kendaraan
                {
                    //ambulance
                    //firetruck semprot
                    //firetruck ladder
                    //premier
                    
                    Dialog_Show(playerid, ParamedisGarage_BUY, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Beli Kendaraan", 
                    "Model\tHarga\n\
                    Sanchez\t$1,500\n\
                    "GRAY"FBI Rancher\t"GRAY"$5,000\n\
                    Ambulance\t$5,000\n\
                    "GRAY"Merit\t"GRAY"$5,000", "Pilih", "Batal");
                }
                case 3: //hapus kendaraan
                {
                    new frmtdel[151];
                    mysql_format(g_SQL, frmtdel, sizeof(frmtdel), "SELECT * FROM `player_vehicles` WHERE `PVeh_Faction` = 2 AND `PVeh_Owner` = %d ORDER BY `id` ASC LIMIT 30", AccountData[playerid][pID]);
                    mysql_query(g_SQL, frmtdel);

                    new rows = cache_num_rows();
                    if(rows)
                    {
                        new list[522], hkvid, hkvmod;
                        
                        format(list, sizeof(list), "Database ID\tModel\n");
                        for(new i; i < rows; ++i)
                        {
                            cache_get_value_name_int(i, "id", hkvid);
                            cache_get_value_name_int(i, "PVeh_ModelID", hkvmod);

                            format(list, sizeof(list), "%s%d\t%s\n", list, hkvid, GetVehicleModelName(hkvmod));
                        }
                        Dialog_Show(playerid, ParamedisGarage_DELETE, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Hapus Kendaraan", list, "Pilih", "Batal");
                    }
                    else
                    {
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return Dialog_Show(playerid, ParamedisGarage_DELETE, DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Hapus Kendaraan", "Anda tidak memiliki kendaraan dari LSFD Pahlawan Roleplay", "Tutup", "");
                    }
                }
            }
        }
        case ParamedisGarageTakeout:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
            if(AccountData[playerid][pFaction] != FACTION_LSFD) return SEM(playerid, "Anda bukan anggota Paramedis Pahlawan Roleplay!");

            if(listitem == -1) return SEM(playerid, "You have not selected a vehicle to deploy!");
            new id = GetVehicleIDStoredFactGarage(playerid, listitem, FACTION_LSFD);
            if(id == -1) return SEM(playerid, "You have not selected a vehicle to deploy!");

            if(!IsPlayerNearLSFDGarage(playerid)) return SEM(playerid, "Anda tidak dekat dengan garasi faction anda!");
            if(PlayerVehicle[id][pVehOwnerID] != AccountData[playerid][pID]) return SEM(playerid, "Kendaraan ini bukan milik anda!");
			PlayerVehicle[id][pVehParked] = -1;
            PlayerVehicle[id][pVehHouseGarage] = -1;
            PlayerVehicle[id][pVehFactStored] = FACTION_NONE;

            new garageid = GetPlayerNearestLSFDGarage(playerid);
            PlayerVehicle[id][pVehPos][0] = LSFD_Stuff[garageid][LSFDGarageSpawnPos][0];
            PlayerVehicle[id][pVehPos][1] = LSFD_Stuff[garageid][LSFDGarageSpawnPos][1];
            PlayerVehicle[id][pVehPos][2] = LSFD_Stuff[garageid][LSFDGarageSpawnPos][2];
            PlayerVehicle[id][pVehPos][3] = LSFD_Stuff[garageid][LSFDGarageSpawnPos][3];
            
            OnPlayerVehicleRespawn(id);

            SetTimerEx("ForcePlayerHopInVehicle", 1500, false, "idd", playerid, PlayerVehicle[id][pVehPhysic], 0);
        }
        case ParamedisGarage_BUY:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
            if(AccountData[playerid][pFaction] != FACTION_LSFD) return SEM(playerid, "Anda bukan anggota Paramedis Pahlawan Roleplay!");

            if(!IsPlayerNearLSFDGarage(playerid)) return SEM(playerid, "Anda tidak dekat dengan garasi faction anda!");

            new count = 0, garageid = GetPlayerNearestLSFDGarage(playerid);
            foreach(new carid : PvtVehicles)
            {
                if(PlayerVehicle[carid][pVehOwnerID] == AccountData[playerid][pID])
                    count++;
            }
            if(count >= GetPlayerVehicleLimit(playerid)) return SEM(playerid, "Slot kendaraan anda sudah mencapai batas maksimum!");

            switch(listitem)
            {
                case 0: //Sanchez
                {
                    if(AccountData[playerid][pMoney] < 1500) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    TakePlayerMoneyEx(playerid, 1500);
                    Vehicle_Create(playerid, 468, FACTION_LSFD, LSFD_Stuff[garageid][LSFDGarageSpawnPos][0], LSFD_Stuff[garageid][LSFDGarageSpawnPos][1], LSFD_Stuff[garageid][LSFDGarageSpawnPos][2], LSFD_Stuff[garageid][LSFDGarageSpawnPos][3], 3, 3, 0, 0);
                    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Pembelian berhasil!");
                }
                case 1: //FBI Rancher
                {
                    if(AccountData[playerid][pMoney] < 5000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    TakePlayerMoneyEx(playerid, 5000);
                    Vehicle_Create(playerid, 490, FACTION_LSFD, LSFD_Stuff[garageid][LSFDGarageSpawnPos][0], LSFD_Stuff[garageid][LSFDGarageSpawnPos][1], LSFD_Stuff[garageid][LSFDGarageSpawnPos][2], LSFD_Stuff[garageid][LSFDGarageSpawnPos][3], 3, 3, 0, 0);
                    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Pembelian berhasil!");
                }
                case 2: //Ambulance
                {
                    if(AccountData[playerid][pMoney] < 5000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    TakePlayerMoneyEx(playerid, 5000);
                    Vehicle_Create(playerid, 416, FACTION_LSFD, LSFD_Stuff[garageid][LSFDGarageSpawnPos][0], LSFD_Stuff[garageid][LSFDGarageSpawnPos][1], LSFD_Stuff[garageid][LSFDGarageSpawnPos][2], LSFD_Stuff[garageid][LSFDGarageSpawnPos][3], 3, 3, 0, 0);
                    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Pembelian berhasil!");
                }
                case 3: //Merit
                {
                    if(AccountData[playerid][pMoney] < 5000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    TakePlayerMoneyEx(playerid, 5000);
                    Vehicle_Create(playerid, 551, FACTION_LSFD, LSFD_Stuff[garageid][LSFDGarageSpawnPos][0], LSFD_Stuff[garageid][LSFDGarageSpawnPos][1], LSFD_Stuff[garageid][LSFDGarageSpawnPos][2], LSFD_Stuff[garageid][LSFDGarageSpawnPos][3], 3, 3, 0, 0);
                    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Pembelian berhasil!");
                }
            }
        }
        case ParamedisGarage_DELETE:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
            if(AccountData[playerid][pFaction] != FACTION_LSFD) return SEM(playerid, "Anda bukan anggota Paramedis Pahlawan Roleplay!");

            new frmtdel[158];
            mysql_format(g_SQL, frmtdel, sizeof(frmtdel), "SELECT * FROM `player_vehicles` WHERE `PVeh_Faction` = 2 AND `PVeh_Owner` = %d ORDER BY `id` ASC LIMIT 30", AccountData[playerid][pID]);
            mysql_query(g_SQL, frmtdel);
            if(cache_num_rows())
            {
                new hapvid, hapmods, kckstr[225], strgbg[128];

                cache_get_value_name_int(listitem, "id", hapvid);
                cache_get_value_name_int(listitem, "PVeh_ModelID", hapmods);
                
                format(kckstr, sizeof(kckstr), "Anda berhasil menghapus kendaraan:\n\
                Database ID: %d\n\
                Model: %s", hapvid, GetVehicleModelName(hapmods));
                Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Hapus Kendaraan", kckstr, "Tutup", "");

                new pvid = GetFactionVehicleIDFromListitem(playerid, listitem, FACTION_LSFD);

                if(IsValidVehicle(PlayerVehicle[pvid][pVehPhysic]))
                {
                    DisableVehicleSpeedCap(PlayerVehicle[pvid][pVehPhysic]);
                    SetVehicleNeonLights(PlayerVehicle[pvid][pVehPhysic], false, PlayerVehicle[pvid][pVehNeon], 0);

                    DestroyVehicle(PlayerVehicle[pvid][pVehPhysic]);
                    PlayerVehicle[pvid][pVehPhysic] = INVALID_VEHICLE_ID;
                }
                mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `player_vehicles` WHERE `id` = %d", hapvid);
                mysql_pquery(g_SQL, strgbg);
                
                Iter_SafeRemove(PvtVehicles, pvid, pvid);
            }
        }
        case DIALOG_BRANKAS_LSFD:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
            if(AccountData[playerid][pFaction] != FACTION_LSFD) return SEM(playerid, "Anda bukan anggota Paramedis Pahlawan Roleplay!");

            AccountData[playerid][pTempSQLFactMemberID] = listitem;
            switch(listitem)
            {
                case 0: //perban
                {
                    Dialog_Show(playerid, DIALOG_LSFDBRANKAS_CONFIRM, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas LSFD", 
                    ""WHITE"Anda akan membeli Perban dengan:\n\n\
                    Uang: $150\n\
                    Kain: 5x\n\
                    Base Oil: 2x\n\
                    Plastik: 10x\n\
                    Karet: 3x\n\
                    Material: 5x\n\
                    "YELLOW"( Masukkan berapa jumlah yang ingin anda beli! )", "Input", "Batal");
                }
                case 1: //medkit
                {
                    Dialog_Show(playerid, DIALOG_LSFDBRANKAS_CONFIRM, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas LSFD", 
                    ""WHITE"Anda akan membeli Medkit dengan:\n\n\
                    Uang: $150\n\
                    Kain: 10x\n\
                    Base Oil: 5x\n\
                    Plastik: 15x\n\
                    Material: 5x\n\n\
                    Susu Olahan: 5x\n\n\
                    "YELLOW"( Masukkan berapa jumlah yang ingin anda beli! )", "Input", "Batal");
                }
                case 2: //pil stress
                {
                    Dialog_Show(playerid, DIALOG_LSFDBRANKAS_CONFIRM, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas LSFD", 
                    ""WHITE"Anda akan membeli Pil Stress dengan:\n\n\
                    Uang: $150\n\
                    Kain: 5x\n\
                    Base Oil: 2x\n\
                    Plastik: 10x\n\
                    Karet: 3x\n\n\
                    Material: 5x\n\n\
                    "YELLOW"( Masukkan berapa jumlah yang ingin anda beli! )", "Input", "Batal");
                }
            }
            /*
            AccountData[playerid][pTempSQLFactMemberID] = listitem;
            Dialog_Show(playerid, DIALOG_LSFDBRANKAS_CONFIRM, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas LSFD", 
            "Mohon ikuti sesuai format berikut\n\
            [ambil] [jumlah] atau [depo] [jumlah]\n\
            Masukkan tanpa tanda ] [ pada kolom di bawah ini:", "Input", "Batal");
            */
        }
        case DIALOG_LSFDBRANKAS_CONFIRM:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
            if(AccountData[playerid][pFaction] != FACTION_LSFD) return SEM(playerid, "Anda bukan anggota Paramedis Pahlawan Roleplay!");
            if(isnull(inputtext)) return Dialog_Show(playerid, DIALOG_LSFDBRANKAS_CONFIRM, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas LSFD", 
            "Error: Tidak dapat dikosongkan!\n\
            ( Masukkan berapa jumlah yang ingin anda beli! )", "Input", "Batal");
            if(!IsNumericEx(inputtext)) return Dialog_Show(playerid, DIALOG_LSFDBRANKAS_CONFIRM, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Brankas LSFD", 
            "Error: Masukkan hanya angka!\n\
            ( Masukkan berapa jumlah yang ingin anda beli! )", "Input", "Batal");
            
            static value, sha[168];
            value = strval(inputtext);

            if(value < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid!");
            
            switch(AccountData[playerid][pTempSQLFactMemberID])
            {
                case 0: //perban
                {
                    new pricing = value * 150;
                    new bahan1 = value * 5; //kain
                    new bahan2 = value * 2; //base oil
                    new bahan3 = value * 10; //plastik
                    new bahan4 = value * 3; //karet
                    new bahan5 = value * 5; //material;
                    if(AccountData[playerid][pMoney] < pricing) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    if(Inventory_Count(playerid, "Cloth") < bahan1) return SEM(playerid, "Kain anda tidak cukup!");
                    if(Inventory_Count(playerid, "Base Oil") < bahan2) return SEM(playerid, "Base Oil anda tidak cukup!");
                    if(Inventory_Count(playerid, "Plastic") < bahan3) return SEM(playerid, "Plastik anda tidak cukup!");
                    if(Inventory_Count(playerid, "Karet") < bahan4) return SEM(playerid, "Karet anda tidak cukup!");

                    new Float:countingtotalweight;
                    countingtotalweight = GetTotalWeightFloat(playerid) + float(value * GetItemWeight("Perban"))/1000;
                    if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
                    TakePlayerMoneyEx(playerid, pricing);
                    Inventory_Remove(playerid, "Cloth", bahan1);
                    Inventory_Remove(playerid, "Base Oil", bahan2);
                    Inventory_Remove(playerid, "Plastic", bahan3);
                    Inventory_Remove(playerid, "Karet", bahan4);
                    LSFDMoneyVault += pricing;
                    mysql_format(g_SQL, sha, sizeof(sha), "UPDATE `stuffs` SET `emsmoneyvault`=%d WHERE `id`=0", LSFDMoneyVault);
                    mysql_pquery(g_SQL, sha);
                    Inventory_Add(playerid, "Perban", 11736, value);
                    ShowItemBox(playerid, "Perban", sprintf("Received %dx", value), 11736, 5);
                    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Anda berhasil mengambil perban");

                    InsertFactionLog("Craft Perban", sprintf("%s %s - QT %d", AccountData[playerid][pName], AccountData[playerid][pUCP], value), "LSFD");
                }
                case 1: //medkit
                {
                    new pricing = value * 150;
                    new bahan1 = value * 10; //kain (11 kg)
                    new bahan2 = value * 5; //base oil (6 kg)
                    new bahan3 = value * 15; //plastik (11 kg)
                    new bahan4 = value * 5; //material (15 kg)
                    new bahan5 = value * 5; //Susu olahan (15 kg)
                    if(AccountData[playerid][pMoney] < pricing) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    if(Inventory_Count(playerid, "Cloth") < bahan1) return SEM(playerid, "Kain anda tidak cukup!");
                    if(Inventory_Count(playerid, "Base Oil") < bahan2) return SEM(playerid, "Base Oil anda tidak cukup!");
                    if(Inventory_Count(playerid, "Plastic") < bahan3) return SEM(playerid, "Plastik anda tidak cukup!");
                    if(Inventory_Count(playerid, "Sterile Milk") < bahan5) return SEM(playerid, "Susu Olahan anda tidak cukup!");

                    new Float:countingtotalweight;
                    countingtotalweight = GetTotalWeightFloat(playerid) + float(value * GetItemWeight("Medkit"))/1000;
                    if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
                    TakePlayerMoneyEx(playerid, pricing);
                    Inventory_Remove(playerid, "Cloth", bahan1);
                    Inventory_Remove(playerid, "Base Oil", bahan2);
                    Inventory_Remove(playerid, "Plastic", bahan3);
                    Inventory_Remove(playerid, "Sterile Milk", bahan5);
                    LSFDMoneyVault += pricing;
                    mysql_format(g_SQL, sha, sizeof(sha), "UPDATE `stuffs` SET `emsmoneyvault`=%d WHERE `id`=0", LSFDMoneyVault);
                    mysql_pquery(g_SQL, sha);
                    Inventory_Add(playerid, "Medkit", 11738, value);
                    ShowItemBox(playerid, "Medkit", sprintf("Received %dx", value), 11738, 5);
                    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Anda berhasil mengambil medkit");

                    InsertFactionLog("Craft Medkit", sprintf("%s %s - QT %d", AccountData[playerid][pName], AccountData[playerid][pUCP], value), "LSFD");
                }
                case 2: //pil stress
                {
                    new pricing = value * 150;
                    new bahan1 = value * 5; //kain
                    new bahan2 = value * 2; //base oil
                    new bahan3 = value * 10; //plastik
                    new bahan4 = value * 3; //karet
                    new bahan5 = value * 5; //material
                    if(AccountData[playerid][pMoney] < pricing) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    if(Inventory_Count(playerid, "Cloth") < bahan1) return SEM(playerid, "Kain anda tidak cukup!");
                    if(Inventory_Count(playerid, "Base Oil") < bahan2) return SEM(playerid, "Base Oil anda tidak cukup!");
                    if(Inventory_Count(playerid, "Plastic") < bahan3) return SEM(playerid, "Plastik anda tidak cukup!");
                    if(Inventory_Count(playerid, "Karet") < bahan4) return SEM(playerid, "Karet anda tidak cukup!");

                    new Float:countingtotalweight;
                    countingtotalweight = GetTotalWeightFloat(playerid) + float(value * GetItemWeight("Pil Stres"))/1000;
                    if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
                    TakePlayerMoneyEx(playerid, pricing);
                    Inventory_Remove(playerid, "Cloth", bahan1);
                    Inventory_Remove(playerid, "Base Oil", bahan2);
                    Inventory_Remove(playerid, "Plastic", bahan3);
                    Inventory_Remove(playerid, "Karet", bahan4);
                    LSFDMoneyVault += pricing;
                    mysql_format(g_SQL, sha, sizeof(sha), "UPDATE `stuffs` SET `emsmoneyvault`=%d WHERE `id`=0", LSFDMoneyVault);
                    mysql_pquery(g_SQL, sha);
                    Inventory_Add(playerid, "Pil Stres", 1241, value);
                    ShowItemBox(playerid, "Pil Stres", sprintf("Received %dx", value), 1241, 5);
                    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Anda berhasil mengambil pil stress");

                    InsertFactionLog("Craft Pil Stress", sprintf("%s %s - QT %d", AccountData[playerid][pName], AccountData[playerid][pUCP], value), "LSFD");
                }
            }
        }
        case ParamedisPanel:
        {
            if(!response) return 1;
            if(AccountData[playerid][pFaction] != FACTION_LSFD) return SEM(playerid, "Anda bukan anggota Paramedis Pahlawan Roleplay!");
            new targetid = NearestSingle[playerid];
            if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
            if(!IsPlayerNearPlayer(playerid, targetid, 3.0)) return SEM(playerid, "Pemain tersebut tidak dekat dengan anda!");
            if(AccountData[playerid][pKnockdown]) return SEM(playerid, "Karakter anda terluka parah saat ini!");
            switch(listitem)
            {
                case 0: //revive
                {
                    if(!AccountData[targetid][pKnockdown]) return SEM(playerid, "Pemain tersebut tidak sedang pingsan/knockdown!");
                    if(!PlayerHasItem(playerid, "Medkit")) return SEM(playerid, "Anda tidak memiliki Medkit!");
                    if(AccountData[playerid][LSFDDuringReviving]) return SEM(playerid, "Anda sedang melakukan revive terhadap player lain!");

                    Inventory_Remove(playerid, "Medkit");

                    ApplyAnimation(playerid, "MEDIC","CPR", 8.33, 1, 0, 0, 1, 0, 1);

                    AccountData[playerid][pActivityTime] = 1;
                    AccountData[playerid][LSFDDuringReviving] = true;
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENGOBATI");
                    ShowProgressBar(playerid);

                    RevivingPlayerTimer[playerid] = SetTimerEx("RevivingPlayer", 1000, true, "ii", playerid, targetid);
                }
                case 1: //treatment
                {
                    SetPlayerHealthEx(targetid, 100);
                    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Treatment berhasil dilakukan");

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
                        SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"Anda telah berhenti menggendong seseorang.");
                        return 1;
                    }

                    foreach(new i: Player)
                    {
                        if(AccountData[i][DraggingID] == playerid) return SEM(playerid, "Anda tidak dapat menyeret seseorang yang sedang menyeret orang lain!");
                    }

                    AccountData[playerid][DraggingID] = targetid;
                    AccountData[targetid][pGetDraggedBy] = playerid;
                    TogglePlayerControllable(targetid, false);
                    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"You have successfully carried someone.");
                    NearestSingle[playerid] = INVALID_PLAYER_ID;
                }
                case 3: //borgol
                {
                    AccountData[targetid][pCuffed] = true;
	                SetPlayerSpecialAction(targetid, SPECIAL_ACTION_CUFFED);
                    SendClientMessage(targetid, X11_LIGHTBLUE, "INFO: "WHITE"You've been cuffed!");
                    NearestSingle[playerid] = INVALID_PLAYER_ID;
                }
                case 4: //buka borgol
                {
                    AccountData[targetid][pCuffed] = false;
	                SetPlayerSpecialAction(targetid, SPECIAL_ACTION_NONE);
                    SendClientMessage(targetid, X11_LIGHTBLUE, "INFO: "WHITE"You've been uncuffed!");
                    NearestSingle[playerid] = INVALID_PLAYER_ID;
                }
                case 5: //Invoice Belum Terbayar
                {
                    new xjjs[600], count;
                    format(xjjs, sizeof(xjjs), "#\tNama Tagihan\tNominal Tagihan\n");
                    for(new id; id < MAX_INVOICES; ++id)
                    {
                        if(InvoiceData[targetid][id][invoiceExists] && InvoiceData[targetid][id][invoiceOwner] == AccountData[targetid][pID]) 
                        {
                            format(xjjs, sizeof(xjjs), "%s%d\t%s\t%s\n", xjjs, id + 1, InvoiceData[targetid][id][invoiceName], FormatMoney(InvoiceData[targetid][id][invoiceCost]));
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
                    Dialog_Show(playerid, "InvoiceSetName", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Invoice", 
                    "Mohon masukkan nama dari invoice ini:", "Input", "Batal");
                }
                case 7: //periksa
                {
                    new pentil[512];
                    format(pentil, sizeof(pentil), ""WHITE"Name: %s\n\
                    "WHITE"Kesehatan: "RED"%.2f\n\
                    "WHITE"Lapar: "YELLOW"%d\n\
                    "WHITE"Haus: "YELLOW"%d", AccountData[targetid][pName], AccountData[targetid][pHealth], AccountData[targetid][pHunger], AccountData[targetid][pThirst]);
                    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Periksa", pentil, "Tutup", "");
                    NearestSingle[playerid] = INVALID_PLAYER_ID;
                }
            }
        }
    }
    return 0;
}

DialogPages:LSFDSetRank(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_LSFD) return SEM(playerid, "Anda bukan anggota Paramedis Pahlawan Roleplay!");
    if(AccountData[playerid][pFactionRank] < 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank KOMDIS untuk akses Bos Desk!");

    mysql_query(g_SQL, "SELECT * FROM `player_characters` WHERE `Char_Faction` = 2 ORDER BY `Char_FactionRank` DESC");
    new rows = cache_num_rows();
    if(rows)
    {
        cache_get_value_name_int(listitem, "pID", AccountData[playerid][pTempSQLFactMemberID]);
        cache_get_value_name_int(listitem, "Char_FactionRank", AccountData[playerid][pTempSQLFactRank]);
        if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFactMemberID]) return SEM(playerid, "Anda tidak dapat menetapkan rank anda sendiri!");
        if(AccountData[playerid][pTempSQLFactRank] >= AccountData[playerid][pFactionRank]) return SEM(playerid, "Anda tidak dapat menetapkan rank rekan yang sejajar/lebih tinggi dari anda!");
        Dialog_Show(playerid, ParamedisSetRankConfirm, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
        "Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
        1. Training\n\
        2. Perawat\n\
        3. Dokter\n\
        4. Dokter\n\
        5. Dokter Spesialis\n\
        6. KOMDIS\n\
        7. WAKADIR\n\
        8. SEKBEN\n\
        9. Direktur", "Set", "Batal");
    }
    return 1;
}

DialogPages:LSFDKickMember(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_LSFD) return SEM(playerid, "Anda bukan anggota Paramedis Pahlawan Roleplay!");
    if(AccountData[playerid][pFactionRank] < 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank KOMDIS untuk akses Bos Desk!");

    mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 2 ORDER BY Char_FactionRank DESC");
    if(cache_num_rows())
    {
        new pidrow, fckname[64], fckrank, fcklastlogin[30], kckstr[225], icsr[128];

        cache_get_value_name_int(listitem, "pID", pidrow);
        cache_get_value_name(listitem, "Char_Name", fckname);
        cache_get_value_name_int(listitem, "Char_FactionRank", fckrank);
        cache_get_value_name(listitem, "Char_LastLogin", fcklastlogin);

        if(AccountData[playerid][pID] == pidrow) return SEM(playerid, "Anda tidak dapat kick diri sendiri!");
        if(fckrank >= AccountData[playerid][pFactionRank]) return SEM(playerid, "Anda tidak dapat kick pangkat yang lebih tinggi atau setara!");
        
        /* kendaraan pribadi yang milik faction dicek */
        new strgbg[158];
        mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `player_vehicles` WHERE `PVeh_Owner` = %d AND `PVeh_Faction` = 2", pidrow);
        mysql_pquery(g_SQL, strgbg);

        foreach(new i : Player)
        {
            if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && pidrow == AccountData[i][pID])
            {
                AccountData[i][pFaction] = 0;
                AccountData[i][pFactionRank] = 0;

                //jika kendaraan pribadi ada di server dan player sedang online, maka kendaraan fisik dihapus
                foreach(new pvid : PvtVehicles)
                {
                    if(PlayerVehicle[pvid][pVehOwnerID] == AccountData[i][pID])
                    {
                        if(PlayerVehicle[pvid][pVehFaction] == FACTION_LSFD)
                        {
                            if(IsValidVehicle(PlayerVehicle[pvid][pVehPhysic]))
                            {
                                DisableVehicleSpeedCap(PlayerVehicle[pvid][pVehPhysic]);
                                SetVehicleNeonLights(PlayerVehicle[pvid][pVehPhysic], false, PlayerVehicle[pvid][pVehNeon], 0);

                                DestroyVehicle(PlayerVehicle[pvid][pVehPhysic]);
                                PlayerVehicle[pvid][pVehPhysic] = INVALID_VEHICLE_ID;
                            }
                            Iter_SafeRemove(PvtVehicles, pvid, pvid);
                        }
                    }
                }
                if(Iter_Contains(LSFDDuty, i))
		            Iter_Remove(LSFDDuty, i);
                SendClientMessage(i, X11_ORANGERED, "[Warning] "WHITE"You have been removed from the LSFD Pahlawan Roleplay!");
            }
        }
        InsertFactionLog("Kick", sprintf("%s %s - %s", AccountData[playerid][pName], AccountData[playerid][pUCP], fckname), "LSFD");

        mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction` = 0, `Char_FactionRank` = 0 WHERE `pID` = %d", pidrow);
        mysql_pquery(g_SQL, icsr);
        format(kckstr, sizeof(kckstr), "Anda berhasil mengeluarkan:\n\
        Name: %s\n\
        Rank: %s\n\
        Last Online: %s", fckname, LSFDRank[fckrank], fcklastlogin);
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Kick Faction", 
        kckstr, "Tutup", "");
    }
    return 1;
}