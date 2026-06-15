YCMD:ag(playerid, params[], help)
{
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SEM(playerid, "You have to be on driver seat!");
    if(AccountData[playerid][pFaction] != FACTION_UBER) return SEM(playerid, "Anda bukan anggota Uber!");
    if(!AccountData[playerid][pOnDuty]) return SEM(playerid, "Anda tidak sedang on duty!");
    if(!IsUberVehicle(GetPlayerVehicleID(playerid))) return SEM(playerid, "Anda harus berada di dalam kendaraan Uber!");

    new orderid;
    if(sscanf(params, "i", orderid)) return SUM(playerid, "/ag [Order ID]");
    if(!IsPlayerConnected(orderid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if(gettime() > UberAppTemp[orderid][NeedUberTimer]) 
    {
        ResetUberAppTemp(orderid);
        SEM(playerid, "Order ID tersebut sudah expired atau diambil oleh driver lain!");
        return 1;
    }
    if(!UberAppTemp[orderid][NeedUber])
    {
        ResetUberAppTemp(orderid);
        SEM(playerid, "Pemain tersebut tidak membutuhkan layanan Uber atau telah diterima oleh driver lain!");
        return 1;
    }

    ResetAllRaceCP(playerid);
    AccountData[playerid][UberRCP] = CreateDynamicRaceCP(1, UberAppTemp[orderid][PosTemp][0], UberAppTemp[orderid][PosTemp][1], UberAppTemp[orderid][PosTemp][2], UberAppTemp[orderid][PosTemp][0], UberAppTemp[orderid][PosTemp][1], UberAppTemp[orderid][PosTemp][2], 3.5, 0, 0, playerid, 10000.00, -1, 0);
    
    SendClientMessageEx(orderid, 0xc0c0c8A6, "(Uber) "WHITE"Driver %s telah menerima orderan anda, mohon tunggu di lokasi.", GetPlayerRoleplayName(playerid));
    SendClientMessageEx(orderid, Y_WHITE, "-    (Details) No. HP: %s // Model: %s", PlayerPhoneData[playerid][phoneNumber], GetVehicleModelName(GetVehicleModel(GetPlayerVehicleID(playerid))));
    SendClientMessageEx(playerid, -1, "Anda telah menerima orderan "YELLOW"%s, "WHITE"lokasi telah ditandai di map.", GetPlayerRoleplayName(orderid));
    
    if(UberAppTemp[orderid][NeedUberEat])
    {
        SendTeamMessage(FACTION_PUTRIDELI, 0xc0c0c8A6, "(Uber Eats) "WHITE"Driver: %s [Ph: %s]", GetPlayerRoleplayName(playerid), PlayerPhoneData[playerid][phoneNumber]);
	    if(UberAppTemp[orderid][ShotDeluxeQuant] > 0)
        {
            SendTeamMessage(FACTION_PUTRIDELI, Y_WHITE, "-   (Menus) BBQ delicy - %dx", UberAppTemp[orderid][ShotDeluxeQuant]);
        }
    }

    UberAppTemp[orderid][NeedUberTimer] = 0;
    UberAppTemp[orderid][NeedUber] = false;
    UberAppTemp[orderid][NeedUberEat] = false;
    UberAppTemp[orderid][ServiceAcceptedBy] = playerid;
    return 1;
}

YCMD:cg(playerid, params[], help)
{
    new orderid, haha[600];
    if(AccountData[playerid][pFaction] != FACTION_UBER) return SEM(playerid, "Anda bukan anggota Uber!");
    if(!AccountData[playerid][pOnDuty]) return SEM(playerid, "Anda tidak sedang on duty!");
    if(sscanf(params, "i", orderid)) return SUM(playerid, "/cg [Order ID]");
    if(!IsPlayerConnected(orderid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if(UberAppTemp[orderid][ServiceAcceptedBy] != playerid) return SEM(playerid, "Anda belum menerima orderan dari pemain tersebut!");
    format(haha, sizeof(haha), "{c0c0c8}(Uber Eats) "WHITE"Rincian orderan dari %s\n", GetPlayerRoleplayName(orderid));
    format(haha, sizeof(haha), "%s-   (Details) No. HP: %s // Lokasi: %s // Tagihan: $%s\n", haha, PlayerPhoneData[orderid][phoneNumber], GetLocation(UberAppTemp[orderid][PosTemp][0], UberAppTemp[orderid][PosTemp][1], UberAppTemp[orderid][PosTemp][2]), FormatMoney(UberAppTemp[orderid][CostTemp]));
    if(UberAppTemp[orderid][ShotDeluxeQuant] > 0)
    {
        format(haha, sizeof(haha), "%s-   (Menus) BBQ delicy - %dx\n", haha, UberAppTemp[orderid][ShotDeluxeQuant]);
    }
    format(haha, sizeof(haha), "%s-   (Catatan) %s\n", haha, UberAppTemp[orderid][DestTemp]);
    format(haha, sizeof(haha), "%s-   (Pembayaran) Credits // Order ID: %d", haha, orderid);
    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Uber App", 
    haha, "Tutup", "");
    return 1;
}

YCMD:eg(playerid, params[], help)
{
    new orderid, egxts[158];
    if(AccountData[playerid][pFaction] != FACTION_UBER) return SEM(playerid, "Anda bukan anggota Uber!");
    if(!AccountData[playerid][pOnDuty]) return SEM(playerid, "Anda tidak sedang on duty!");
    if(sscanf(params, "i", orderid)) return SUM(playerid, "/eg [Order ID]");
    if(!IsPlayerConnected(orderid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if(UberAppTemp[orderid][ServiceAcceptedBy] != playerid) return SEM(playerid, "Anda belum menerima orderan dari pemain tersebut!");
    if(AccountData[orderid][pBankMoney] < UberAppTemp[orderid][CostTemp]) return SEM(playerid, "Saldo bank pemain tersebut tidak cukup!");

    if(!UberAppTemp[orderid][NeedUberEat])
    {
        AccountData[orderid][pBankMoney] -= UberAppTemp[orderid][CostTemp];
        AccountData[playerid][pBankMoney] += UberAppTemp[orderid][CostTemp];

        mysql_format(g_SQL, egxts, sizeof(egxts), "UPDATE `player_characters` SET `Char_BankMoney`=%d WHERE `pID`=%d", AccountData[playerid][pBankMoney], AccountData[playerid][pID]);
        mysql_pquery(g_SQL, egxts);

        mysql_format(g_SQL, egxts, sizeof(egxts), "UPDATE `player_characters` SET `Char_BankMoney`=%d WHERE `pID`=%d", AccountData[orderid][pBankMoney], AccountData[orderid][pID]);
        mysql_pquery(g_SQL, egxts);
    }

    UberAppTemp[orderid][ServiceAcceptedBy] = INVALID_PLAYER_ID;
    SendClientMessageEx(orderid, 0xc0c0c8A6, "(Uber) "WHITE"Driver "YELLOW"%s "WHITE"telah menyelesaikan orderan anda, jangan lupa berikan rating.", GetPlayerRoleplayName(playerid));
    SendClientMessageEx(playerid, 0xc0c0c8A6, "(Uber) "WHITE"Anda telah menyelesaikan order dari "YELLOW"%s, "WHITE"saldo bank bertambah "GREEN"$%s", GetPlayerRoleplayName(orderid), FormatMoney(UberAppTemp[orderid][CostTemp]));
    ResetUberAppTemp(orderid);
    return 1;
}