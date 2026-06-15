YCMD:addbj(playerid, params[], help)
{
    new minbet, maxbet, id = Iter_Free(BJTables), query[512];

    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

	if (sscanf(params, "dd", minbet, maxbet))
	{
	    SUM(playerid, "/addbj [Min Bet] [Max Bet]");
		return 1;
	}
	if (minbet < 5000)
	    return ShowTDN(playerid, NOTIFICATION_ERROR, "Min bet $100.00!");

    if (maxbet < 5000 || maxbet > 500000)
	    return ShowTDN(playerid, NOTIFICATION_ERROR, "Max bet $100.00 - $5,000.00!");
    
    if (id == -1)
	    return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah dynamic blackjack sudah mencapai batas maksimal!");

    GetPlayerPos(playerid, BlackJackTable[id][Pos][0], BlackJackTable[id][Pos][1], BlackJackTable[id][Pos][2]);
    BlackJackTable[id][Pos][3] = BlackJackTable[id][Pos][4] = BlackJackTable[id][Pos][5] = 0.0;

    BlackJackTable[id][World] = GetPlayerVirtualWorld(playerid);
    BlackJackTable[id][Interior] = GetPlayerInterior(playerid);

    BlackJackTable[id][MinBet] = minbet;
    BlackJackTable[id][MaxBet] = maxbet;

    BlackJackTable[id][BJStarted] = false;
    BlackJackTable[id][BJCountdown] = 0;
    
    new Float:actorX = BlackJackTable[id][Pos][0] + 0.65*(floatcos(90 + BlackJackTable[id][Pos][5], degrees));
    new Float:actorY = BlackJackTable[id][Pos][1] + 0.65*(floatsin(90 - BlackJackTable[id][Pos][5], degrees));

    new randskin = __g_CasinoNPCSkin[random(sizeof(__g_CasinoNPCSkin))];
    BlackJackTable[id][BJActor] = CreateDynamicActor(randskin, actorX, actorY, BlackJackTable[id][Pos][2], BlackJackTable[id][Pos][5] - 180.0, true, 1000.0, BlackJackTable[id][World], BlackJackTable[id][Interior], -1, 100.00, -1, 0);
    BlackJackTable[id][BJTableObj] = CreateDynamicObject(2188, BlackJackTable[id][Pos][0], BlackJackTable[id][Pos][1], BlackJackTable[id][Pos][2], BlackJackTable[id][Pos][3], BlackJackTable[id][Pos][4], BlackJackTable[id][Pos][5], BlackJackTable[id][World], BlackJackTable[id][Interior], -1, 100.00, 100.00, -1);

    Iter_Add(BJTables, id);

    Iter_Init(CardsUsed);
    for(new i; i<sizeof(g_CasinoCards); i++)
    {
        Iter_Add(CardsUsed[id], i);
    }

	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `bj_tables` SET `id`=%d, `X`='%f', `Y`='%f', `Z`='%f', `RX`='%f', `RY`='%f', `RZ`='%f', `Interior`=%d, `World`=%d, `MinBet` = %d, `MaxBet` = %d", id, BlackJackTable[id][Pos][0], BlackJackTable[id][Pos][1], BlackJackTable[id][Pos][2], BlackJackTable[id][Pos][3], BlackJackTable[id][Pos][4], BlackJackTable[id][Pos][5], GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid), BlackJackTable[id][MinBet], BlackJackTable[id][MaxBet]);
	mysql_pquery(g_SQL, query, "OnBJTableCreated", "ii", playerid, id);
    return 1;
}

YCMD:blackjack(playerid, params[], help)
{
    new id = BJTable_Nearest(playerid);
    if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan meja blackjack manapun!");
    
    if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");

    if(PlayerBlackJack[playerid][Seated]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang bermain blackjack!");
    if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
    
    if(BJTable_IsBusy(id))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Meja blackjack ini sedang digunakan player lain!");

    for(new x; x < 7; x++)
    {
        PlayerTextDrawDestroy(playerid, BlackJackPTD[playerid][x]);
        BlackJackPTD[playerid][x] = PlayerText: INVALID_PLAYER_TEXT_DRAW;

        PlayerTextDrawDestroy(playerid, DealerBJTD[playerid][x]);
        DealerBJTD[playerid][x] = PlayerText: INVALID_PLAYER_TEXT_DRAW;

        PlayerTextDrawDestroy(playerid, DealerBJTD[playerid][x]);
        DealerBJTD[playerid][x] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
    }

    PlayerTextDrawDestroy(playerid, BJTableCardTD[playerid][0]);
    BJTableCardTD[playerid][0] = PlayerText: INVALID_PLAYER_TEXT_DRAW;

    PlayerTextDrawDestroy(playerid, BJTableCardTD[playerid][1]);
    BJTableCardTD[playerid][1] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
    
    PlayerBlackJack[playerid][Bet][0] = 0;
    PlayerBlackJack[playerid][Bet][1] = 0;
    PlayerBlackJack[playerid][CardValue][0] = 0;
    PlayerBlackJack[playerid][CardValue][1] = 0;
    PlayerBlackJack[playerid][pCardsId] = -1;
    PlayerBlackJack[playerid][DealerCardsId] = -1;
    PlayerBlackJack[playerid][DealerCardValue] = 0;
    PlayerBlackJack[playerid][DealerClosedCard] = -1;
    
    PlayerBlackJack[playerid][Forbidden] = false;
    PlayerBlackJack[playerid][HasAce] = false;
    PlayerBlackJack[playerid][BlackJack] = false;
    PlayerBlackJack[playerid][DoubleTaken][0] = false;
    PlayerBlackJack[playerid][DoubleTaken][1] = false;
    PlayerBlackJack[playerid][InsuranceTaken] = false;
    PlayerBlackJack[playerid][Splited] = false;
    PlayerBlackJack[playerid][SplitCardGiven] = false;
    PlayerBlackJack[playerid][IsSelectSplitCard] = false;
    PlayerBlackJack[playerid][DealerHasAce] = false;
    PlayerBlackJack[playerid][DealerBlackJack] = false;
    PlayerBlackJack[playerid][DealerCardStillClosed] = false;
    PlayerBlackJack[playerid][pCountCards] = -1;
    PlayerBlackJack[playerid][Seated] = true;
    BlackJackTable[id][BJStarted] = false;
    BlackJackTable[id][BJCountdown] = 0;
    BlackJackTable[id][BJCurrPlayerID] = playerid;
    BJTable_CreatePlayerTD(playerid);
    BJTable_HideTextDraw(playerid);

    TextDrawShowForPlayer(playerid, BlackJackTD[8]);
    TextDrawShowForPlayer(playerid, BlackJackTD[9]);

    PlayerTextDrawSetString(playerid, BJTableCardTD[playerid][0], sprintf("Deck Cards~n~%d", Iter_Count(CardsUsed[id])));
    PlayerTextDrawShow(playerid, BJTableCardTD[playerid][0]);
    PlayerTextDrawSetString(playerid, BJTableCardTD[playerid][1], sprintf("Table Bet:~n~$%s - $%s", FormatMoney(BlackJackTable[id][MinBet]), FormatMoney(BlackJackTable[id][MaxBet])));
    PlayerTextDrawShow(playerid, BJTableCardTD[playerid][1]);

    new Float:actorX = BlackJackTable[id][Pos][0] - 0.55*(floatcos(90 + BlackJackTable[id][Pos][5], degrees));
    new Float:actorY = BlackJackTable[id][Pos][1] - 0.55*(floatsin(90 - BlackJackTable[id][Pos][5], degrees));
    CameraRadiusSetPos(playerid, actorX, actorY, BlackJackTable[id][Pos][2], BlackJackTable[id][Pos][5]+180.0, 2.8, 1.5);

    SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"Welcome to your seat. This table minimum bet is "YELLOW"$%s "WHITE"and maximum is "YELLOW"$%s", FormatMoney(BlackJackTable[id][MinBet]), FormatMoney(BlackJackTable[id][MaxBet]));
    
    PlayerBlackJack[playerid][pInBJTable] = id;

    TogglePlayerControllable(playerid, false);

    PlayerPlayNearbySound(playerid, 5810);
    Dialog_Show(playerid, "BlackjackBet", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Your Bets", "Welcome to your table, please place your bets:", "Place", "Batal");
    return 1;
}

YCMD:editbj(playerid, params[], help)
{
    new tblid;
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);
    if (AccountData[playerid][EditingTableBJID] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang berada di dalam mode editing!");

    if (sscanf(params, "d", tblid))
    {
        SUM(playerid, "/editbj [id]");
        return 1;
    }

    if (!Iter_Contains(BJTables, tblid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Blackjack Table ID!");

    if (!IsPlayerInRangeOfPoint(playerid, 30.0, BlackJackTable[tblid][Pos][0], BlackJackTable[tblid][Pos][1], BlackJackTable[tblid][Pos][2]))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan meja blackjack tersebut!");

    if (BJTable_BeingEdited(tblid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Blackjack Table sedang diedit oleh admin lain!");

    AccountData[playerid][EditingTableBJID] = tblid;
    EditDynamicObject(playerid, BlackJackTable[tblid][BJTableObj]);

    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s edited Blackjack Table position ID: %d.", AccountData[playerid][pAdminname], tblid);
    return 1;
}

YCMD:removebj(playerid, params[], help)
{
    new tblid, strgbg[128];
    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

    if (sscanf(params, "d", tblid))
        return SUM(playerid, "/removebj [id]");

    if (!Iter_Contains(BJTables, tblid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Blackjack Table ID!");
    if (BJTable_BeingEdited(tblid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Blackjack Table sedang diedit oleh admin lain!");

    if (DestroyDynamicObject(BlackJackTable[tblid][BJTableObj]))
        BlackJackTable[tblid][BJTableObj] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

    if (DestroyDynamicActor(BlackJackTable[tblid][BJActor]))
        BlackJackTable[tblid][BJActor] = STREAMER_TAG_ACTOR: INVALID_STREAMER_ID;

    BlackJackTable[tblid][Pos][0] = BlackJackTable[tblid][Pos][1] = BlackJackTable[tblid][Pos][2] = BlackJackTable[tblid][Pos][3] = BlackJackTable[tblid][Pos][4] = BlackJackTable[tblid][Pos][5] = 0.0;
    BlackJackTable[tblid][World] = 0;
    BlackJackTable[tblid][Interior] = 0;
    BlackJackTable[tblid][MinBet] = 0;
    BlackJackTable[tblid][MaxBet] = 0;
    BlackJackTable[tblid][BJCountdown] = 0;
    BlackJackTable[tblid][BJCurrPlayerID] = INVALID_PLAYER_ID;

    Iter_Remove(BJTables, tblid);

    mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `bj_tables` WHERE `id` = %d", tblid);
    mysql_pquery(g_SQL, strgbg);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s removed Blackjack Table with ID: %d.", AccountData[playerid][pAdminname], tblid);
    return 1;
}

YCMD:mychip(playerid, params[], help)
{
    ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Anda saat ini memiliki chip ~g~$%s", FormatMoney(AccountData[playerid][pCasinoChip])));
    return 1;
}

YCMD:buychip(playerid, params[], help)
{
    if(!IsPlayerInRangeOfPoint(playerid, 3.0, 2238.5657,1595.6613,1019.3632)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di counter casino!");
    if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");

    new money, Float:pricing;
    if(sscanf(params, "d", money)) return SUM(playerid, "/buychip [ammount]");

    if(money < 100 || money > 30000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Beli di antara $100 - $30,000!");

    if(AccountData[playerid][pMoney] < RoundNegativeToPositive(money)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup uang!");

    TakePlayerMoneyEx(playerid, money);

    pricing = money - (money * 0.03);
    AccountData[playerid][pCasinoChip] += floatround(pricing);

    ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(money)), 1212, 4);
    
    ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda telah membeli ~g~$%s ~l~chip seharga ~r~$%s ~l~(pajak 3 persen).", FormatMoney(floatround(pricing)), FormatMoney(money)));
    return 1;
}

YCMD:redeemchip(playerid, params[], help)
{
    if(!IsPlayerInRangeOfPoint(playerid, 3.0, 2231.1189,1595.9353,1019.3696)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di counter casino!");
    if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");

    new money;
    if(sscanf(params, "d", money)) return SUM(playerid, "/redeemchip [ammount]");
    
	if(money < 100 || money > 30000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Redeem di antara $100 - $30,000!");

    if(AccountData[playerid][pCasinoChip] < RoundNegativeToPositive(money)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Chip anda tidak cukup!");

    AccountData[playerid][pCasinoChip] -= money;

    GivePlayerMoneyEx(playerid, money);

    ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(money)), 1212, 4);
    ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil menukar ~g~$%s ~l~chip.", FormatMoney(money)));
    return 1;
}