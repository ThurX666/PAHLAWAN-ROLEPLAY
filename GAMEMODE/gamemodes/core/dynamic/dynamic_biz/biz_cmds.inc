YCMD:buy(playerid, params[], help)
{
    if(AccountData[playerid][pInBiz] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di dalam bisnis!");

    new bizid = AccountData[playerid][pInBiz];
    PlayerShopBizID[playerid] = -1;
    return Biz_ShowProductMenu(playerid, bizid);
}

YCMD:restockbiz(playerid, params[], help)
{
    if(AccountData[playerid][pInBiz] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di dalam bisnis!");

    new bizid = AccountData[playerid][pInBiz], erex[512];
    if(BizData[bizid][bizOwnerID] != AccountData[playerid][pID] && !Biz_IsEmployee(bizid, playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan owner/employee bisnis ini!");

    if(BizData[bizid][bizType] == 1)
    {
        format(erex, sizeof(erex), "Name\tCurrent stocks\n\
        Udud (12 batang)\t%d\n\
        "GRAY"Pancingan\t"GRAY"%d\n\
        Baseball Bat\t%d\n\
        "GRAY"Knife\t"GRAY"%d\n\
        Golf Stick\t%d\n\
        "GRAY"Pool Cue\t"GRAY"%d\n\
        Hunting Rifle\t%d\n\
        "GRAY"Hunting Ammo (24x)\t"GRAY"%d\n\
        Obeng\t%d\n\
        "GRAY"Hoe\t"GRAY"%d",
        BizData[bizid][bizProdStock][0],
        BizData[bizid][bizProdStock][1],
        BizData[bizid][bizProdStock][2],
        BizData[bizid][bizProdStock][3],
        BizData[bizid][bizProdStock][4],
        BizData[bizid][bizProdStock][5],
        BizData[bizid][bizProdStock][6],
        BizData[bizid][bizProdStock][7],
        BizData[bizid][bizProdStock][8],
        BizData[bizid][bizProdStock][9]);
        Dialog_Show(playerid, "BizRestock", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Biz Restock", erex, "Pilih", "Batal");
    }
    
    if(BizData[bizid][bizType] == 3)
    {
        format(erex, sizeof(erex), "Name\tCurrent stocks\n\
        Arivhone (Smartphone)\t%d\n\
        "GRAY"Radio\t"GRAY"%d\n\
        Earphone\t%d\n\
        "GRAY"Boombox\t"GRAY"%d\n\
        Chainsaw Electric\t%d\n\
        "GRAY"Battery\t"GRAY"%d\n\
        Spraycan\t%d",
        BizData[bizid][bizProdStock][0],
        BizData[bizid][bizProdStock][1],
        BizData[bizid][bizProdStock][2],
        BizData[bizid][bizProdStock][3],
        BizData[bizid][bizProdStock][4],
        BizData[bizid][bizProdStock][5],
        BizData[bizid][bizProdStock][6]);
        Dialog_Show(playerid, "BizRestock", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Biz Restock", erex, "Pilih", "Batal");
    }
    return 1;
}

YCMD:bizmenu(playerid, params[], help)
{
    new bizid = Biz_GetNearestSign(playerid, BIZ_MENU_RADIUS), erex[512];
    if(bizid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di area sign bisnis!");

    if(Biz_GetAuctionStatus(bizid) == BIZ_AUCTION_ENDED)
    {
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Bisnis ini masih dalam masa auction ended!");
    }
    if(BizData[bizid][bizOwnerID] != AccountData[playerid][pID] && !Biz_IsEmployee(bizid, playerid))
    {
        return SendClientMessage(playerid, Y_GREY, "ERROR: Kamu bukan owner atau employee dari bisnis ini.");
    }

    AccountData[playerid][pInBiz] = bizid;

    if(BizData[bizid][bizType] == 1)
    {
        format(erex, sizeof(erex), "Name\tSettings\n\
        Nama Biz\t%s\n\
        "GRAY"Profit\t"GRAY"$%s\n\
        "GRAY"Harga Udud (12 batang)\t"GRAY"$%s\n\
        Harga Pancingan\t$%s\n\
        "GRAY"Harga Baseball Bat\t"GRAY"$%s\n\
        Harga Knife\t$%s\n\
        "GRAY"Harga Golf Stick\t"GRAY"$%s\n\
        Harga Pool Cue\t$%s\n\
        "GRAY"Harga Hunting Rifle\t"GRAY"$%s\n\
        Harga Hunting Ammo (24x)\t$%s\n\
        "GRAY"Harga Obeng\t"GRAY"$%s\n\
        Harga Hoe\t$%s",
        BizData[bizid][bizName],
        FormatMoney(BizData[bizid][bizMoney]),
        FormatMoney(BizData[bizid][bizProdPrice][0]),
        FormatMoney(BizData[bizid][bizProdPrice][1]),
        FormatMoney(BizData[bizid][bizProdPrice][2]),
        FormatMoney(BizData[bizid][bizProdPrice][3]),
        FormatMoney(BizData[bizid][bizProdPrice][4]),
        FormatMoney(BizData[bizid][bizProdPrice][5]),
        FormatMoney(BizData[bizid][bizProdPrice][6]),
        FormatMoney(BizData[bizid][bizProdPrice][7]),
        FormatMoney(BizData[bizid][bizProdPrice][8]),
        FormatMoney(BizData[bizid][bizProdPrice][9]));
        Dialog_Show(playerid, "BizMenu", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Biz Menu", erex, "Pilih", "Batal");
    }
    
    if(BizData[bizid][bizType] == 3)
    {
        format(erex, sizeof(erex), "Name\tSettings\n\
        Nama Biz\t%s\n\
        "GRAY"Profit\t"GRAY"$%s\n\
        "GRAY"Harga Arivhone (Smartphone)\t"GRAY"$%s\n\
        Harga Radio\t$%s\n\
        "GRAY"Harga Earphone\t"GRAY"$%s\n\
        Harga Boombox\t$%s\n\
        "GRAY"Harga Chainsaw Electric\t"GRAY"$%s\n\
        Harga Battery\t$%s\n\
        "GRAY"Harga Spraycan\t"GRAY"$%s",
        BizData[bizid][bizName],
        FormatMoney(BizData[bizid][bizMoney]),
        FormatMoney(BizData[bizid][bizProdPrice][0]),
        FormatMoney(BizData[bizid][bizProdPrice][1]),
        FormatMoney(BizData[bizid][bizProdPrice][2]),
        FormatMoney(BizData[bizid][bizProdPrice][3]),
        FormatMoney(BizData[bizid][bizProdPrice][4]),
        FormatMoney(BizData[bizid][bizProdPrice][5]),
        FormatMoney(BizData[bizid][bizProdPrice][6]));
        Dialog_Show(playerid, "BizMenu", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Biz Menu", erex, "Pilih", "Batal");
    }
    return 1;
}

YCMD:buybiz(playerid, params[], help)
{
    new bizid = Biz_Nearest(playerid);
    if(bizid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan bisnis manapun!");
    if(!isnull(BizData[bizid][bizOwnerName])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Bisnis ini sudah dimiliki seseorang!");
    if(BizData[bizid][bizBid]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Bisnis ini sedang dilelang melalui UCP!");
    if(BizData[bizid][bizPrice] < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Bisnis ini belum memiliki harga jual!");
    if(Player_BizCount(playerid) > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah memiliki bisnis!");
    if(AccountData[playerid][pMoney] < BizData[bizid][bizPrice]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

    TakePlayerMoneyEx(playerid, BizData[bizid][bizPrice]);
    BizData[bizid][bizOwnerID] = AccountData[playerid][pID];
    strcopy(BizData[bizid][bizOwnerName], AccountData[playerid][pName]);
    BizData[bizid][bizMoney] = 0;
    Biz_ClearAuction(bizid);
    Biz_ClearEmployees(bizid);

    Biz_Save(bizid);
    Biz_Refresh(bizid);
    ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(BizData[bizid][bizPrice])), 1212, 4);
    Biz_SendCashPurchaseInfo(playerid);
    return 1;
}

YCMD:bizinfo(playerid, params[], help)
{
    new bizid = Biz_InfoNearest(playerid);
    if(bizid == -1)
    {
        bizid = Biz_Nearest(playerid);
    }
    if(bizid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan titik informasi bisnis!");

    if(!isnull(BizData[bizid][bizOwnerName]))
        return 1;

    return Biz_ShowInfo(playerid, bizid);
}

YCMD:showbid(playerid, params[], help)
{
    new bizid = Biz_GetAuctionNearest(playerid, BIZ_AUCTION_CMD_RADIUS);
    if(bizid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada auction bisnis yang sedang berjalan di dekat anda!");

    return Biz_ShowBidMain(playerid, bizid);
}

YCMD:bizbid(playerid, params[], help)
{
    new bizid = Biz_GetAuctionNearest(playerid, BIZ_AUCTION_CMD_RADIUS);
    if(bizid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada auction bisnis yang sedang berjalan di dekat anda!");

    return Biz_ShowBidMain(playerid, bizid);
}

YCMD:bizemployee(playerid, params[], help)
{
    if(AccountData[playerid][pInBiz] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di dalam bisnis!");

    new bizid = AccountData[playerid][pInBiz], action[16], string[64];
    if(BizData[bizid][bizOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Bisnis ini bukan milik anda!");
    if(sscanf(params, "s[16]S()[64]", action, string)) return SUM(playerid, "/bizemployee [invite/fire/list] [playerid/slot]");

    if(!strcmp(action, "list", true))
    {
        new employeeList[180], info[256];
        Biz_FormatEmployeeList(bizid, employeeList, sizeof(employeeList));
        format(info, sizeof(info), "{FFFF00}Employee %s\n\n{FFFFFF}%s", BizData[bizid][bizName], employeeList);
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Employee Bisnis", info, "Tutup", "");
    }
    else if(!strcmp(action, "invite", true) || !strcmp(action, "hire", true))
    {
        new targetid;
        if(sscanf(string, "u", targetid)) return SUM(playerid, "/bizemployee invite [playerid/name]");
        if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Player tersebut tidak online!");
        if(targetid == playerid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat mengundang diri sendiri!");
        if(BizData[bizid][bizOwnerID] == AccountData[targetid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Owner tidak perlu menjadi employee!");
        if(Biz_GetEmployeeSlotByPlayerID(bizid, AccountData[targetid][pID]) != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Player tersebut sudah menjadi employee bisnis ini!");

        new slot = Biz_GetFreeEmployeeSlot(bizid);
        if(slot == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot employee bisnis ini sudah penuh!");

        BizEmployeeID[bizid][slot] = AccountData[targetid][pID];
        strcopy(BizEmployeeName[bizid][slot], AccountData[targetid][pName]);
        Biz_Save(bizid);

        SendClientMessageEx(targetid, Y_LIGHTRED, "Anda telah dijadikan employee bisnis %s oleh %s.", BizData[bizid][bizName], AccountData[playerid][pName]);
        ShowTDN(playerid, NOTIFICATION_SUCCESS, "Employee bisnis berhasil ditambahkan.");
    }
    else if(!strcmp(action, "fire", true) || !strcmp(action, "kick", true))
    {
        new slot;
        if(sscanf(string, "d", slot)) return SUM(playerid, "/bizemployee fire [slot 1-4]");
        if(slot < 1 || slot > MAX_BIZ_EMPLOYEES) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot employee tidak valid!");
        slot--;
        if(BizEmployeeID[bizid][slot] == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot employee tersebut kosong!");

        new employeeName[MAX_PLAYER_NAME + 1];
        strcopy(employeeName, BizEmployeeName[bizid][slot]);
        BizEmployeeID[bizid][slot] = 0;
        BizEmployeeName[bizid][slot][0] = EOS;
        Biz_Save(bizid);

        ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Employee %s berhasil dikeluarkan.", employeeName));
    }
    else return SUM(playerid, "/bizemployee [invite/fire/list] [playerid/slot]");
    return 1;
}

YCMD:addbiz(playerid, params[], help)
{
    new bizid = Iter_Free(Bizes), type, price;
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);
    if(bizid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah dynamic businesses telah mencapai batas maksimum!");
    if(sscanf(params, "dd", type, price)) return SUM(playerid, "/addbiz [type] [price]~n~1. Minimarket, 2. Clothes, 3. Electronic, 4. Ammunation");

    if(type < 1 || type > 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Type tidak valid! (1 - 4)");
    if(price < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Harga tidak valid!");

    strcopy(BizData[bizid][bizName], "-");
    BizData[bizid][bizOwnerID] = 0;
    BizData[bizid][bizOwnerName][0] = EOS;
    BizData[bizid][bizMoney] = 0;
    BizData[bizid][bizType] = type;
    BizData[bizid][bizPrice] = price;
    BizData[bizid][bizBid] = false;
    BizData[bizid][bizAuctionID] = 0;
    BizData[bizid][bizOpenBid] = 0;
    BizData[bizid][bizAuctionStart] = 0;
    BizData[bizid][bizAuctionEnd] = 0;
    BizData[bizid][bizAuctionStartedByID] = 0;
    BizData[bizid][bizAuctionStartedBy][0] = EOS;
    BizHighestBid[bizid] = 0;
    BizHighestBidder[bizid][0] = EOS;
    BizAuctionFinalizing[bizid] = false;
    Biz_ClearEmployees(bizid);

    for(new x; x < 11; x++)
    {
        BizData[bizid][bizProdStock][x] = 200;
    }

    for(new x; x < 11; x++)
    {
        BizData[bizid][bizProdPrice][x] = 2000;
    }

    GetPlayerPos(playerid, BizData[bizid][bizSignPos][0], BizData[bizid][bizSignPos][1], BizData[bizid][bizSignPos][2]);
    BizData[bizid][bizSignPos][3] = 0.0;
    BizData[bizid][bizSignPos][4] = 0.0;
    GetPlayerFacingAngle(playerid, BizData[bizid][bizSignPos][5]);
    BizData[bizid][bizSignVw] = GetPlayerVirtualWorld(playerid);
    BizData[bizid][bizSignInt] = GetPlayerInterior(playerid);

    Biz_Rebuild(bizid);
    
    Iter_Add(Bizes, bizid);

    static dddstr[3600];
    mysql_format(g_SQL, dddstr, sizeof(dddstr), "INSERT INTO `biz` SET `ID`=%d, `Name`='%e', `OwnerID`=%d, `OwnerName`='%e', `Money`=%d, `Type`=%d, `Price`=%d, `IsBid`=%d, `AuctionID`=%d, `OpenBid`=%d, `AuctionStart`=%d, `AuctionEnd`=%d, `AuctionStartedByID`=%d, `AuctionStartedBy`='%e', \
    `ProdStock0`=%d, `ProdStock1`=%d, `ProdStock2`=%d, `ProdStock3`=%d, `ProdStock4`=%d, `ProdStock5`=%d, `ProdStock6`=%d, `ProdStock7`=%d, `ProdStock8`=%d, `ProdStock9`=%d, `ProdStock10`=%d, \
    `ProdPrice0`=%d, `ProdPrice1`=%d, `ProdPrice2`=%d, `ProdPrice3`=%d, `ProdPrice4`=%d, `ProdPrice5`=%d, `ProdPrice6`=%d, `ProdPrice7`=%d, `ProdPrice8`=%d, `ProdPrice9`=%d, `ProdPrice10`=%d, \
    `SignX`='%f', `SignY`='%f', `SignZ`='%f', `SignRX`='%f', `SignRY`='%f', `SignRZ`='%f', `SignVw`=%d, `SignInt`=%d, \
    `EmployeeID0`=%d, `EmployeeName0`='%e', `EmployeeID1`=%d, `EmployeeName1`='%e', `EmployeeID2`=%d, `EmployeeName2`='%e', `EmployeeID3`=%d, `EmployeeName3`='%e'",
    bizid,
    BizData[bizid][bizName], 
    BizData[bizid][bizOwnerID], 
    BizData[bizid][bizOwnerName], 
    BizData[bizid][bizMoney], 
    BizData[bizid][bizType],
    BizData[bizid][bizPrice],
    BizData[bizid][bizBid] ? 1 : 0,
    BizData[bizid][bizAuctionID],
    BizData[bizid][bizOpenBid],
    BizData[bizid][bizAuctionStart],
    BizData[bizid][bizAuctionEnd],
    BizData[bizid][bizAuctionStartedByID],
    BizData[bizid][bizAuctionStartedBy],
    BizData[bizid][bizProdStock][0],
    BizData[bizid][bizProdStock][1],
    BizData[bizid][bizProdStock][2],
    BizData[bizid][bizProdStock][3],
    BizData[bizid][bizProdStock][4],
    BizData[bizid][bizProdStock][5],
    BizData[bizid][bizProdStock][6],
    BizData[bizid][bizProdStock][7],
    BizData[bizid][bizProdStock][8],
    BizData[bizid][bizProdStock][9],
    BizData[bizid][bizProdStock][10],
    BizData[bizid][bizProdPrice][0],
    BizData[bizid][bizProdPrice][1],
    BizData[bizid][bizProdPrice][2],
    BizData[bizid][bizProdPrice][3],
    BizData[bizid][bizProdPrice][4],
    BizData[bizid][bizProdPrice][5],
    BizData[bizid][bizProdPrice][6],
    BizData[bizid][bizProdPrice][7],
    BizData[bizid][bizProdPrice][8],
    BizData[bizid][bizProdPrice][9],
    BizData[bizid][bizProdPrice][10],
    BizData[bizid][bizSignPos][0],
    BizData[bizid][bizSignPos][1],
    BizData[bizid][bizSignPos][2],
    BizData[bizid][bizSignPos][3],
    BizData[bizid][bizSignPos][4],
    BizData[bizid][bizSignPos][5],
    BizData[bizid][bizSignVw],
    BizData[bizid][bizSignInt],
    BizEmployeeID[bizid][0],
    BizEmployeeName[bizid][0],
    BizEmployeeID[bizid][1],
    BizEmployeeName[bizid][1],
    BizEmployeeID[bizid][2],
    BizEmployeeName[bizid][2],
    BizEmployeeID[bizid][3],
    BizEmployeeName[bizid][3]);
    mysql_pquery(g_SQL, dddstr, "OnBizCreated", "ii", playerid, bizid);
    return 1;
}

YCMD:editbiz(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    new bizid, type[24], string[128];
    if(sscanf(params, "ds[24]S()[128]", bizid, type, string)) return SUM(playerid, "/editbiz [id] [type]~n~pos, type, price, bid~n~owner, resetowner, sign, reset");
    if(!Iter_Contains(Bizes, bizid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Bisnis tidak valid!");

    if(!strcmp(type, "pos", true))
    {
        GetPlayerPos(playerid, BizData[bizid][bizSignPos][0], BizData[bizid][bizSignPos][1], BizData[bizid][bizSignPos][2]);
        BizData[bizid][bizSignPos][3] = 0.0;
        BizData[bizid][bizSignPos][4] = 0.0;
        GetPlayerFacingAngle(playerid, BizData[bizid][bizSignPos][5]);
        BizData[bizid][bizSignVw] = GetPlayerVirtualWorld(playerid);
        BizData[bizid][bizSignInt] = GetPlayerInterior(playerid);
        Biz_Save(bizid);
        Biz_Refresh(bizid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s change sign location for Business ID: %d.", AccountData[playerid][pAdminname], bizid);
    }

    else if(!strcmp(type, "type", true))
    {
        new btype;

        if(sscanf(string, "d", btype))
            return SUM(playerid, "/editbiz [id] [type]~n~1. Minimarket, 2. Clothes, 3. Electronic, 4. Ammunation");

        if(btype < 1 || btype > 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Type bisnis tidak valid! (1 - 4)");

        BizData[bizid][bizType] = btype;

        Biz_Save(bizid);
        Biz_Refresh(bizid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has change the type of Business ID: %d to %d.", AccountData[playerid][pAdminname], bizid, btype);
    }

    else if(!strcmp(type, "price", true))
    {
        new price;
        if(sscanf(string, "d", price)) return SUM(playerid, "/editbiz [id] price [cash price]");
        if(price < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Harga bisnis tidak valid!");

        BizData[bizid][bizPrice] = price;
        Biz_Save(bizid);
        Biz_Refresh(bizid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s mengubah harga cash Business ID: %d menjadi $%s.", AccountData[playerid][pAdminname], bizid, FormatMoney(price));
    }

    else if(!strcmp(type, "bid", true))
    {
        return Biz_ShowAdminBidPanel(playerid, bizid);
    }

    else if(!strcmp(type, "openbid", true))
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Gunakan /editbiz [id] bid untuk mengatur auction.");
        return Biz_ShowAdminBidPanel(playerid, bizid);
    }

    else if(!strcmp(type, "auctionend", true) || !strcmp(type, "bidend", true))
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Gunakan /editbiz [id] bid untuk mengatur tanggal auction.");
        return Biz_ShowAdminBidPanel(playerid, bizid);
    }

    else if(!strcmp(type, "owner", true))
    {
        new targetid;
        if(sscanf(string, "u", targetid)) return SUM(playerid, "/editbiz [id] owner [playerid/name]");
        if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Player tersebut tidak online!");

        BizData[bizid][bizOwnerID] = AccountData[targetid][pID];
        strcopy(BizData[bizid][bizOwnerName], AccountData[targetid][pName]);
        Biz_ClearAuction(bizid);
        Biz_ClearEmployees(bizid);
        Biz_Save(bizid);
        Biz_Refresh(bizid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s menetapkan owner Business ID: %d kepada %s.", AccountData[playerid][pAdminname], bizid, AccountData[targetid][pName]);
    }

    else if(!strcmp(type, "resetowner", true))
    {
        BizData[bizid][bizOwnerID] = 0;
        BizData[bizid][bizOwnerName][0] = EOS;
        Biz_ClearEmployees(bizid);
        Biz_Save(bizid);
        Biz_Refresh(bizid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s mereset owner Business ID: %d.", AccountData[playerid][pAdminname], bizid);
    }

    else if(!strcmp(type, "sign", true))
    {
        if(EditingBizID[playerid] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang berada dalam mode editing bisnis!");
        if(!IsPlayerInRangeOfPoint(playerid, 30.0, BizData[bizid][bizSignPos][0], BizData[bizid][bizSignPos][1], BizData[bizid][bizSignPos][2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan sign bisnis tersebut!");
        if(Biz_BeingEdited(bizid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Bisnis tersebut sedang diedit oleh admin lain!");

        EditingBizID[playerid] = bizid;
        EditDynamicObject(playerid, BizData[bizid][bizSign]);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s mengedit sign Business ID: %d.", AccountData[playerid][pAdminname], bizid);
    }

    else if(!strcmp(type, "reset", true))
    {
        strcopy(BizData[bizid][bizName], "-");
        BizData[bizid][bizOwnerName][0] = EOS;
        BizData[bizid][bizOwnerID] = 0;
        BizData[bizid][bizMoney] = 0;
        Biz_ClearAuction(bizid);
        Biz_ClearEmployees(bizid);

        for(new x; x < 11; x++)
        {
            BizData[bizid][bizProdStock][x] = 200;
        }

        for(new x; x < 11; x++)
        {
            BizData[bizid][bizProdPrice][x] = 2000;
        }

        Biz_Save(bizid);
        Biz_Refresh(bizid);

        SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has reset Business ID: %d.", AccountData[playerid][pAdminname], bizid);
    }
    return 1;
}

YCMD:gotobiz(playerid, params[], help)
{
    new bizid;
	if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

	if(sscanf(params, "d", bizid))
		return SUM(playerid, "/gotobiz [bizid]");

	if(!Iter_Contains(Bizes, bizid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Bisnis tidak valid!");

	new Float:bx, Float:by, Float:bz, Float:ba;
    Biz_GetInfoPosition(bizid, bx, by, bz, ba);

	SetPlayerPositionEx(playerid, bx, by, bz, ba);
    SetPlayerInteriorEx(playerid, BizData[bizid][bizSignInt]);
    SetPlayerVirtualWorldEx(playerid, BizData[bizid][bizSignVw]);

    AccountData[playerid][pInDoor] = -1;
	AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
	AccountData[playerid][pInRusun] = -1;
    AccountData[playerid][pInGudang] = -1;
	return 1;
}

YCMD:removebiz(playerid, params[], help)
{
    new bizid, strgbg[128];
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);
    if(sscanf(params, "d", bizid)) return SUM(playerid, "/removebiz [bizid]");
    if(!Iter_Contains(Bizes, bizid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Bisnis tidak valid!");

    strcopy(BizData[bizid][bizName], "-");
    BizData[bizid][bizOwnerID] = 0;
    BizData[bizid][bizOwnerName][0] = EOS;
    BizData[bizid][bizMoney] = 0;
    BizData[bizid][bizType] = 0;
    BizData[bizid][bizPrice] = 0;
    Biz_ClearAuction(bizid);
    Biz_ClearEmployees(bizid);

    for(new x; x < 11; x++)
    {
        BizData[bizid][bizProdStock][x] = 0;
    }

    for(new x; x < 11; x++)
    {
        BizData[bizid][bizProdPrice][x] = 0;
    }

    for(new x; x < 6; x++)
    {
        BizData[bizid][bizSignPos][x] = 0.0;
    }
    BizData[bizid][bizSignVw] = 0;
    BizData[bizid][bizSignInt] = 0;

    if(DestroyDynamicObject(BizData[bizid][bizSign]))
        BizData[bizid][bizSign] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

    if(DestroyDynamicObject(BizData[bizid][bizSignText]))
        BizData[bizid][bizSignText] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

    if(DestroyDynamicPickup(BizData[bizid][bizInfoPickup]))
        BizData[bizid][bizInfoPickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

    if(DestroyDynamic3DTextLabel(BizData[bizid][bizInfoLabel]))
        BizData[bizid][bizInfoLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    Iter_Remove(Bizes, bizid);
    mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `biz` WHERE `ID` = %d", bizid);
    mysql_pquery(g_SQL, strgbg);
    mysql_pquery(g_SQL, sprintf("DELETE FROM `biz_bids` WHERE `BizID`=%d", bizid));
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has removed Business ID: %d.", AccountData[playerid][pAdminname], bizid);
    return 1;
}
