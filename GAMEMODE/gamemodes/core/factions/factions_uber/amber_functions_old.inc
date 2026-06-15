#include <YSI_Coding\y_hooks>

enum _Amber_Details
{
    Float:gjDutyPos[3],
    Float:gjLockerPos[3],
    Float:gjBosDeskPos[3],
    Float:gjGaragePos[3],
    Float:gjGarageSpawnPos[4],
    gjVWID,
    gjIntID
};

hook OnPlayerEnterDynRaceCP(playerid, STREAMER_TAG_RACE_CP:checkpointid)
{
    if(AccountData[playerid][pFaction] == FACTION_AMBER)
    {
        if(checkpointid == PlayerFactionAmberVars[playerid][AmberRCP] && IsPlayerInDynamicRaceCP(playerid, PlayerFactionAmberVars[playerid][AmberRCP]))
        {
            ResetAllRaceCP(playerid);
        }
    }
    return 1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA: areaid)
{
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && AccountData[playerid][pFaction] == FACTION_AMBER)
    {
        if(areaid == PlayerFactionAmberVars[playerid][AmberDutyArea])
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
    
        if(areaid == PlayerFactionAmberVars[playerid][AmberLockerArea])
        {
            ShowNotifBox(playerid, "[Y] Locker Amber");
        }
    
        if(areaid == PlayerFactionAmberVars[playerid][AmberBosDeskArea])
        {
            ShowNotifBox(playerid, "[Y] Akses Bos Desk");
        }
    
        if(areaid == PlayerFactionAmberVars[playerid][AmberGarageArea])
        {
            ShowNotifBox(playerid, "[Y] Garasi Amber");
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA: areaid)
{
    if(areaid == PlayerFactionAmberVars[playerid][AmberDutyArea])
    {
        HideNotifBox(playerid);
        PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
    }

    if(areaid == PlayerFactionAmberVars[playerid][AmberLockerArea])
    {
        HideNotifBox(playerid);
        PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
    }

    if(areaid == PlayerFactionAmberVars[playerid][AmberBosDeskArea])
    {
        HideNotifBox(playerid);
        PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
    }

    if(areaid == PlayerFactionAmberVars[playerid][AmberGarageArea])
    {
        HideNotifBox(playerid);
        PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && AccountData[playerid][pFaction] == FACTION_AMBER && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(IsPlayerInDynamicArea(playerid, PlayerFactionAmberVars[playerid][AmberDutyArea]))
        {
            if(!AccountData[playerid][pOnDuty])
            {
                AccountData[playerid][pOnDuty] = true;
                SendClienMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"Anda sekarang "GREEN"On Duty.");
                Iter_Add(AmberDuty, playerid);
            }
            else
            {
                AccountData[playerid][pOnDuty] = false;
                SendClienMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"Anda sekarang "RED"Off Duty.");
                Iter_Remove(AmberDuty, playerid);
            }
            HideNotifBox(playerid);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFactionAmberVars[playerid][AmberLockerArea]))
        {
            HideNotifBox(playerid);
            Dialog_Show(playerid, DIALOG_LOCKER_AMBER, DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Seragam", 
            "Baju Warga\n\
            "GRAY"Baju Amber", "Pilih", "Batal");
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFactionAmberVars[playerid][AmberBosDeskArea]))
        {
            HideNotifBox(playerid);
            if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Ast. Bos Amber untuk akses Bos Desk!");

            Dialog_Show(playerid, DIALOG_BOSDESK_AMBER, DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Bos Desk", 
            "Invite\n\
            "GRAY"Kelola Jabatan\n\
            Kick\n\
            "GRAY"Saldo Finansial\n\
            Deposit Saldo\n\
            "GRAY"Tarik Saldo", "Pilih", "Batal");
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFactionAmberVars[playerid][AmberGarageArea]))
        {
            HideNotifBox(playerid);
            Dialog_Show(playerid, DIALOG_GARAGE_AMBER, DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Garasi Amber", 
            "Keluarkan Kendaraan\n\
            "GRAY"Simpan Kendaraan\n\
            Beli Kendaraan\n\
            "GRAY"Hapus Kendaraan", "Pilih", "Batal");
        }
    }
    else if(newkeys & KEY_CTRL_BACK && AccountData[playerid][pFaction] == FACTION_PUTRIDELI && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(AccountData[playerid][pInEvent]) return 1;
        
        new count = 0;
		foreach(new i : Player) if(i != playerid) if(IsPlayerNearPlayer(playerid, i, 2.5)) 
		{
            count++;
			NearestSingle[playerid] = i;
		}
		if(count > 0) 
		{
            Dialog_Show(playerid, DIALOG_AMBER_PANEL, DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Faction Panel", 
            "Invoice Belum Terbayar\n\
            "GRAY"Invoice Manual", "Pilih", "Batal");
		}
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_LOCKER_AMBER:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
            if(AccountData[playerid][pFaction] != FACTION_AMBER) return SEM(playerid, "Anda bukan anggota Amber!");
            switch(listitem)
            {
                case 0: //baju warga
                {
                    SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
                    AccountData[playerid][pIsUsingUniform] = false;
                }
                case 1: //baju amber
                {
                    AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (188) : (263);
                    SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
                    AccountData[playerid][pIsUsingUniform] = true;
                }
            }
        }
        case DIALOG_BOSDESK_AMBER:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
            if(AccountData[playerid][pFaction] != FACTION_AMBER) return SEM(playerid, "Anda bukan anggota Amber!");
            if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Ast. Bos Amber untuk akses Bos Desk!");

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

                    Dialog_Show(playerid, DIALOG_INVITE_CONFIRM_AMBER, DIALOG_STYLE_TABLIST, "{DA9100}Pahlawan Roleplay "WHITE"- Undang Faction", frmxt, "Pilih", "Batal");
                }
                case 1: //kelola jabatan
                {
                    mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 4 ORDER BY Char_FactionRank DESC");

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
                            
                            AddDialogListitem(playerid, "%s\t%s\t%s", fckname, AmberRank[fckrank], fcklastlogin);
                        }
                        ShowPlayerDialogPages(playerid, "AmberSetRank", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", "Pilih", "Batal", 15, ""GREEN">> Lanjut", ""ORANGE"<< Kembali");
                    }
                    else
                    {
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", "Faction ini tidak memiliki anggota!", "Tutup", "");
                    }
                }
                case 2: //kick
                {
	                mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 4 ORDER BY Char_FactionRank DESC");

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
                            
                            AddDialogListitem(playerid, "%s\t%s\t%s", fckname, AmberRank[fckrank], fcklastlogin);
                        }
                        ShowPlayerDialogPages(playerid, "AmberKickMember", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Kick Faction", "Pilih", "Batal", 15, ""GREEN">> Lanjut", ""ORANGE"<< Kembali");
                    }
                    else
                    {
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Kick Faction", "Faction ini tidak memiliki anggota!", "Tutup", "");
                    }
                }
            }
        }
        case DIALOG_INVITE_CONFIRM_AMBER:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
            if(AccountData[playerid][pFaction] != FACTION_AMBER) return SEM(playerid, "Anda bukan anggota Amber!");
            if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Ast. Bos Amber untuk akses Bos Desk!");

            new targetid = NearestUser[playerid][listitem], icsr[128];
            if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
            AccountData[targetid][pFaction] = FACTION_AMBER;
            AccountData[targetid][pFactionRank] = 1;
            mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction` = 4, `Char_FactionRank` = 1 WHERE `pID` = %d", AccountData[targetid][pID]);
            mysql_pquery(g_SQL, icsr);
            SendClientMessageEx(playerid, X11_LIGHTBLUE, "INFO: "WHITE"You have successfully invited "YELLOW"%s "GRAY45"to the faction.", AccountData[targetid][pName]);

            InsertFactionLog("Invite", sprintf("%s %s - %s %s", AccountData[playerid][pName], AccountData[playerid][pUCP], AccountData[targetid][pName], AccountData[targetid][pUCP]), "Amber");
        }
        case DIALOG_RANK_SET_AMBER:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
            if(AccountData[playerid][pFaction] != FACTION_AMBER) return SEM(playerid, "Anda bukan anggota Amber!");
            if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Ast. Bos Amber untuk akses Bos Desk!");

            if(isnull(inputtext)) return Dialog_Show(playerid, DIALOG_RANK_SET_AMBER, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
            "Error: Tidak dapat dikosongkan!\n\
            Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. Magang\n\
            2. Junior\n\
            3. Senior\n\
            4. Wakil Bos\n\
            5. Bos Amber", "Set", "Batal");
            
            if(!IsNumericEx(inputtext)) return Dialog_Show(playerid, DIALOG_RANK_SET_AMBER, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
            "Error: Masukkan hanya angka!\n\
            Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. Magang\n\
            2. Junior\n\
            3. Senior\n\
            4. Wakil Bos\n\
            5. Bos Amber", "Set", "Batal");

            if(strval(inputtext) < 1 || strval(inputtext) > AccountData[playerid][pFactionRank]) return Dialog_Show(playerid, DIALOG_RANK_SET_AMBER, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
            "Error: Tidak dapat diisi dibawah 1 atau lebih tinggi dari jabatan anda!\n\
            Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. Magang\n\
            2. Junior\n\
            3. Senior\n\
            4. Wakil Bos\n\
            5. Bos Amber", "Set", "Batal");

            new hjh[128];
            mysql_format(g_SQL, hjh, sizeof(hjh), "UPDATE `player_characters` SET `Char_FactionRank`=%d WHERE `pID`=%d", strval(inputtext), AccountData[playerid][pTempSQLFactMemberID]);
            mysql_pquery(g_SQL, hjh);

            foreach(new i : Player)
            {
                if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && AccountData[playerid][pTempSQLFactMemberID] == AccountData[i][pID])
                {
                    AccountData[i][pFactionRank] = strval(inputtext);
                    SendClientMessage(i, X11_LIGHTBLUE, "[Info] "WHITE"Jabatan anda di faction telah diperbarui.");

                    InsertFactionLog("Set Rank", sprintf("%s %s - %s %s LV %d", AccountData[playerid][pName], AccountData[playerid][pUCP], AccountData[i][pName], AccountData[i][pUCP], strval(inputtext)), "Amber");
                }
            }

            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah jabatan faction Pemain tersebut!");
        }
        case DIALOG_GARAGE_AMBER:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
            if(AccountData[playerid][pFaction] != FACTION_AMBER) return SEM(playerid, "Anda bukan anggota Amber!");
            switch(listitem)
            {
                case 0: //keluarkan kendaraan
                {
                    if(CountPlayerFactVehInGarage(playerid, FACTION_AMBER) < 1) return SEM(playerid, "You do not have any faction vehicles stored!");

                    new id, count = CountPlayerFactVehInGarage(playerid, FACTION_AMBER), lstr[596];
                    format(lstr,sizeof(lstr),"No\tModel Kendaraan\tNomor Plat\n");
                    for(new itt; itt < count; itt++)
                    {
                        id = GetVehicleIDStoredFactGarage(playerid, itt, FACTION_AMBER);
                        if(itt == count)
                        {
                            format(lstr,sizeof(lstr), "%s%d\t%s\t%s", lstr, itt+1, GetVehicleModelName(PlayerVehicle[id][pVehModelID]), PlayerVehicle[id][pVehPlate]);
                        }
                        else format(lstr,sizeof(lstr), "%s%d\t%s\t%s\n", lstr, itt+1, GetVehicleModelName(PlayerVehicle[id][pVehModelID]), PlayerVehicle[id][pVehPlate]);
                    }
                    Dialog_Show(playerid, DIALOG_GARAGE_AMBER_TAKEOUT, DIALOG_STYLE_TABLIST_HEADERS,"{DA9100}Pahlawan Roleplay "WHITE"- Keluarkan Kendaraan", lstr, "Pilih","Batal");
                }
                case 1: //simpan kendaraan
                {
                    new carid = INVALID_VEHICLE_ID, foundnearby = 0;

                    if((carid = Vehicle_Nearest(playerid, 10.0)) != INVALID_VEHICLE_ID)
                    {
                        if(PlayerVehicle[carid][pVehOwnerID] != AccountData[playerid][pID]) return SEM(playerid, "Kendaraan ini bukan milik anda!");
                        if(PlayerVehicle[carid][pVehRental] > -1 || PlayerVehicle[carid][pVehRentTime] > 0) return SEM(playerid, "Anda tidak dapat menyimpan kendaraan rental!");
                        Vehicle_GetStatus(carid);
                        PlayerVehicle[carid][pVehFactStored] = FACTION_AMBER;

                        foundnearby++;
                        
                        DisableVehicleSpeedCap(PlayerVehicle[carid][pVehPhysic]);
                        SetVehicleNeonLights(PlayerVehicle[carid][pVehPhysic], false, PlayerVehicle[carid][pVehNeon], 0);

                        DestroyVehicle(PlayerVehicle[carid][pVehPhysic]);
                        PlayerVehicle[carid][pVehPhysic] = INVALID_VEHICLE_ID;
                    }
                    if(!foundnearby)
                        return SEM(playerid, "Tidak ada kendaraan dari Amber milik anda di sekitar!");
                }
                case 2: //beli kendaraan
                {
                    Dialog_Show(playerid, DIALOG_GARAGE_AMBER_BUY, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Beli Kendaraan", 
                    "Model\tHarga\n\
                    Moonbeam\t$5,000\n\
                    "GRAY"Wayfarer\t"GRAY"$1,500\n\
                    BF-400\t$1,500", "Pilih", "Batal");
                }
                case 3: //hapus kendaraan
                {
                    new frmtdel[151];
                    mysql_format(g_SQL, frmtdel, sizeof(frmtdel), "SELECT * FROM `player_vehicles` WHERE `PVeh_Faction` = 4 AND `PVeh_Owner` = %d ORDER BY `id` ASC LIMIT 30", AccountData[playerid][pID]);
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
                        Dialog_Show(playerid, DIALOG_GARAGE_AMBER_DELETE, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Hapus Kendaraan", list, "Pilih", "Batal");
                    }
                    else
                    {
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return Dialog_Show(playerid, DIALOG_GARAGE_AMBER_DELETE, DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Hapus Kendaraan", "Anda tidak memiliki kendaraan dari Amber", "Tutup", "");
                    }
                }
            }
        }
        case DIALOG_GARAGE_AMBER_TAKEOUT:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
            if(AccountData[playerid][pFaction] != FACTION_AMBER) return SEM(playerid, "Anda bukan anggota Amber!");

            if(listitem == -1) return SEM(playerid, "You have not selected a vehicle to deploy!");
            new id = GetVehicleIDStoredFactGarage(playerid, listitem, FACTION_AMBER);
            if(id == -1) return SEM(playerid, "You have not selected a vehicle to deploy!");

            if(!IsPlayerInRangeOfPoint(playerid, 5.0, Amber_Stuff[gjGaragePos][0], Amber_Stuff[gjGaragePos][1], Amber_Stuff[gjGaragePos][2]))
                return SEM(playerid, "Anda tidak dekat dengan garasi Amber manapun!");

            if(PlayerVehicle[id][pVehOwnerID] != AccountData[playerid][pID]) return SEM(playerid, "Kendaraan ini bukan milik anda!");
			PlayerVehicle[id][pVehParked] = -1;
            PlayerVehicle[id][pVehHouseGarage] = -1;
            PlayerVehicle[id][pVehFactStored] = FACTION_NONE;

            PlayerVehicle[id][pVehPos][0] = Amber_Stuff[gjGarageSpawnPos][0];
            PlayerVehicle[id][pVehPos][1] = Amber_Stuff[gjGarageSpawnPos][1];
            PlayerVehicle[id][pVehPos][2] = Amber_Stuff[gjGarageSpawnPos][2];
            PlayerVehicle[id][pVehPos][3] = Amber_Stuff[gjGarageSpawnPos][3];
            
            OnPlayerVehicleRespawn(id);

            SetTimerEx("ForcePlayerHopInVehicle", 1500, false, "idd", playerid, PlayerVehicle[id][pVehPhysic], 0);
        }
        case DIALOG_GARAGE_AMBER_BUY:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
            if(AccountData[playerid][pFaction] != FACTION_AMBER) return SEM(playerid, "Anda bukan anggota Amber!");

            if(!IsPlayerInRangeOfPoint(playerid, 5.0, Amber_Stuff[gjGaragePos][0], Amber_Stuff[gjGaragePos][1], Amber_Stuff[gjGaragePos][2]))
                return SEM(playerid, "Anda tidak dekat dengan garasi Amber manapun!");

            new count = 0;
            foreach(new carid : PvtVehicles)
            {
                if(PlayerVehicle[carid][pVehOwnerID] == AccountData[playerid][pID])
                    count++;
            }
            if(count >= GetPlayerVehicleLimit(playerid)) return SEM(playerid, "Slot kendaraan anda sudah mencapai batas maksimum!");

            switch(listitem)
            {
                case 0: //moonbeam
                {
                    if(AccountData[playerid][pMoney] < 5000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    TakePlayerMoneyEx(playerid, 5000);
                    Vehicle_Create(playerid, 418, FACTION_AMBER, Amber_Stuff[gjGarageSpawnPos][0], Amber_Stuff[gjGarageSpawnPos][1], Amber_Stuff[gjGarageSpawnPos][2], Amber_Stuff[gjGarageSpawnPos][3], 86, 86, 0, 0);
                    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Pembelian berhasil!");
                }
                case 1: //wayfarer
                {
                    if(AccountData[playerid][pMoney] < 1500) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    TakePlayerMoneyEx(playerid, 1500);
                    Vehicle_Create(playerid, 586, FACTION_AMBER, Amber_Stuff[gjGarageSpawnPos][0], Amber_Stuff[gjGarageSpawnPos][1], Amber_Stuff[gjGarageSpawnPos][2], Amber_Stuff[gjGarageSpawnPos][3], 86, 86, 0, 0);
                    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Pembelian berhasil!");
                }
                case 2: //BF-400
                {
                    if(AccountData[playerid][pMoney] < 1500) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                    TakePlayerMoneyEx(playerid, 1500);
                    Vehicle_Create(playerid, 581, FACTION_AMBER, Amber_Stuff[gjGarageSpawnPos][0], Amber_Stuff[gjGarageSpawnPos][1], Amber_Stuff[gjGarageSpawnPos][2], Amber_Stuff[gjGarageSpawnPos][3], 86, 86, 0, 0);
                    SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Pembelian berhasil!");
                }
            }
        }
        case DIALOG_GARAGE_AMBER_DELETE:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
            if(AccountData[playerid][pFaction] != FACTION_AMBER) return SEM(playerid, "Anda bukan anggota Amber!");

            new frmtdel[158];
            mysql_format(g_SQL, frmtdel, sizeof(frmtdel), "SELECT * FROM `player_vehicles` WHERE `PVeh_Faction` = 4 AND `PVeh_Owner` = %d ORDER BY `id` ASC LIMIT 30", AccountData[playerid][pID]);
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

                new pvid = GetFactionVehicleIDFromListitem(playerid, listitem, FACTION_AMBER);

                if(Iter_Contains(Vehicle, PlayerVehicle[pvid][pVehPhysic]))
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
        case DIALOG_AMBER_PANEL:
        {
            if(!response) return 1;
            if(AccountData[playerid][pFaction] != FACTION_AMBER) return SEM(playerid, "Anda bukan anggota Amber!");
            new targetid = NearestSingle[playerid];
            if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
            if(!IsPlayerNearPlayer(playerid, targetid, 3.0)) return SEM(playerid, "Pemain tersebut tidak dekat dengan anda!");
            switch(listitem)
            {
                case 0: //Invoice Belum Terbayar
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
                case 1: //invoice manual
                {
                    Dialog_Show(playerid, "InvoiceSetName", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Invoice", 
                    "Mohon masukkan nama dari invoice ini:", "Input", "Batal");
                }
            }
        }
    }
    return 0;
}

DialogPages:AmberSetRank(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_AMBER) return SEM(playerid, "Anda bukan anggota Amber!");
    if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Ast. Bos Amber untuk akses Bos Desk!");

    mysql_query(g_SQL, "SELECT * FROM `player_characters` WHERE `Char_Faction` = 4 ORDER BY `Char_FactionRank` DESC");
    new rows = cache_num_rows();
    if(rows)
    {
        cache_get_value_name_int(listitem, "pID", AccountData[playerid][pTempSQLFactMemberID]);
        cache_get_value_name_int(listitem, "Char_FactionRank", AccountData[playerid][pTempSQLFactRank]);
        if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFactMemberID]) return SEM(playerid, "Anda tidak dapat menetapkan rank anda sendiri!");
        if(AccountData[playerid][pTempSQLFactRank] >= AccountData[playerid][pFactionRank]) return SEM(playerid, "Anda tidak dapat menetapkan rank rekan yang sejajar/lebih tinggi dari anda!");
        Dialog_Show(playerid, DIALOG_RANK_SET_AMBER, DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
        "Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
        1. Magang\n\
        2. Junior\n\
        3. Senior\n\
        4. Wakil Bos\n\
        5. Bos Amber", "Set", "Batal");
    }
    return 1;
}

DialogPages:AmberKickMember(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_AMBER) return SEM(playerid, "Anda bukan anggota Amber!");
    if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Ast. Bos Amber untuk akses Bos Desk!");

    mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 4 ORDER BY Char_FactionRank DESC");
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
        mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `player_vehicles` WHERE `PVeh_Owner` = %d AND `PVeh_Faction` = 4", pidrow);
        mysql_pquery(g_SQL, strgbg);

        foreach(new i : Player)
        {
            if(pidrow == AccountData[i][pID])
            {
                AccountData[i][pFaction] = 0;
                AccountData[i][pFactionRank] = 0;

                //jika kendaraan pribadi ada di server dan player sedang online, maka kendaraan fisik dihapus
                foreach(new pvid : PvtVehicles)
                {
                    if(PlayerVehicle[pvid][pVehOwnerID] == AccountData[i][pID])
                    {
                        if(PlayerVehicle[pvid][pVehFaction] == FACTION_AMBER)
                        {
                            if(Iter_Contains(Vehicle, PlayerVehicle[pvid][pVehPhysic]))
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
                if(Iter_Contains(AmberDuty, i))
		            Iter_Remove(AmberDuty, i);
                SendClientMessage(i, X11_ORANGERED, "[Warning] "WHITE"You have been removed from the Amber!");
            }
        }
        InsertFactionLog("Set Rank", sprintf("%s %s - %s", AccountData[playerid][pName], AccountData[playerid][pUCP], fckname, strval(inputtext)), "Amber");

        mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction` = 0, `Char_FactionRank` = 0 WHERE `pID` = %d", pidrow);
        mysql_pquery(g_SQL, icsr);
        format(kckstr, sizeof(kckstr), "Anda berhasil mengeluarkan:\n\
        Name: %s\n\
        Rank: %s\n\
        Last Online: %s", fckname, AmberRank[fckrank], fcklastlogin);
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Kick Faction", 
        kckstr, "Tutup", "");
    }
    return 1;
}