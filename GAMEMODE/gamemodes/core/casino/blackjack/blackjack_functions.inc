#include <YSI_Coding\y_hooks>

#define MAX_BJ_TABLES 100
#define MINIMUM_DECK_CARDS 40

enum e_bjtablesinfo
{
    Float:Pos[6],
    World,
    Interior,
    MinBet,
    MaxBet,

    //not save
    BJCurrPlayerID,
    bool:BJStarted,
    BJCountdown,
    STREAMER_TAG_OBJECT:BJTableObj,
    STREAMER_TAG_ACTOR:BJActor
};
new BlackJackTable[MAX_BJ_TABLES][e_bjtablesinfo],
    Iterator:BJTables<MAX_BJ_TABLES>;

enum e_playerblackjack
{
    bool:Seated,
    bool:Forbidden,
    bool:HasAce[2],
    bool:BlackJack,
    bool:DoubleTaken[2],
    bool:InsuranceTaken,
    bool:Splited,
    bool:SplitCardGiven,
    bool:IsSelectSplitCard,
    Bet[2],
    CardValue[2],
    pCountCards,
    pCardsId,
    pSplitCardsID,
	pInBJTable,

    //dealer
    bool:DealerHasAce,
    bool:DealerBlackJack,
    bool:DealerCardStillClosed,
    DealerCardsId,
    DealerCardValue,
    DealerClosedCard
};
new PlayerBlackJack[MAX_PLAYERS][e_playerblackjack];

new __g_CasinoNPCSkin[] = {
    171, 163, 164, 165, 166, 189
};

new PlayerText:BlackJackPTD[MAX_PLAYERS][7];
new PlayerText:SplitBJTD[MAX_PLAYERS][7];
new PlayerText:BJTableCardTD[MAX_PLAYERS][2];
new PlayerText:DealerBJTD[MAX_PLAYERS][7];

enum ___g_CardsTDRand
{
    CardModelID[64],
    CardValue1
};

new g_CasinoCards[][___g_CardsTDRand] =
{
    {"ld_card:cd10c", 10},
    {"ld_card:cd10d", 10},
    {"ld_card:cd10h", 10},
    {"ld_card:cd10s", 10},
    {"ld_card:cd11c", 10},
    {"ld_card:cd11d", 10},
    {"ld_card:cd11h", 10},
    {"ld_card:cd11s", 10},
    {"ld_card:cd12c", 10},
    {"ld_card:cd12d", 10},
    {"ld_card:cd12h", 10},
    {"ld_card:cd12s", 10},
    {"ld_card:cd13c", 10},
    {"ld_card:cd13d", 10},
    {"ld_card:cd13h", 10},
    {"ld_card:cd13s", 10},
    {"ld_card:cd1c", 11},
    {"ld_card:cd1d", 11},
    {"ld_card:cd1h", 11},
    {"ld_card:cd1s", 11},
    {"ld_card:cd2c", 2},
    {"ld_card:cd2d", 2},
    {"ld_card:cd2h", 2},
    {"ld_card:cd2s", 2},
    {"ld_card:cd3c", 3},
    {"ld_card:cd3d", 3},
    {"ld_card:cd3h", 3},
    {"ld_card:cd3s", 3},
    {"ld_card:cd4c", 4},
    {"ld_card:cd4d", 4},
    {"ld_card:cd4h", 4},
    {"ld_card:cd4s", 4},
    {"ld_card:cd5c", 5},
    {"ld_card:cd5d", 5},
    {"ld_card:cd5h", 5},
    {"ld_card:cd5s", 5},
    {"ld_card:cd6c", 6},
    {"ld_card:cd6d", 6},
    {"ld_card:cd6h", 6},
    {"ld_card:cd6s", 6},
    {"ld_card:cd7c", 7},
    {"ld_card:cd7d", 7},
    {"ld_card:cd7h", 7},
    {"ld_card:cd7s", 7},
    {"ld_card:cd8c", 8},
    {"ld_card:cd8d", 8},
    {"ld_card:cd8h", 8},
    {"ld_card:cd8s", 8},
    {"ld_card:cd9c", 9},
    {"ld_card:cd9d", 9},
    {"ld_card:cd9h", 9},
    {"ld_card:cd9s", 9},
    {"ld_card:cd10c", 10},
    {"ld_card:cd10d", 10},
    {"ld_card:cd10h", 10},
    {"ld_card:cd10s", 10},
    {"ld_card:cd11c", 10},
    {"ld_card:cd11d", 10},
    {"ld_card:cd11h", 10},
    {"ld_card:cd11s", 10},
    {"ld_card:cd12c", 10},
    {"ld_card:cd12d", 10},
    {"ld_card:cd12h", 10},
    {"ld_card:cd12s", 10},
    {"ld_card:cd13c", 10},
    {"ld_card:cd13d", 10},
    {"ld_card:cd13h", 10},
    {"ld_card:cd13s", 10},
    {"ld_card:cd1c", 11},
    {"ld_card:cd1d", 11},
    {"ld_card:cd1h", 11},
    {"ld_card:cd1s", 11},
    {"ld_card:cd2c", 2},
    {"ld_card:cd2d", 2},
    {"ld_card:cd2h", 2},
    {"ld_card:cd2s", 2},
    {"ld_card:cd3c", 3},
    {"ld_card:cd3d", 3},
    {"ld_card:cd3h", 3},
    {"ld_card:cd3s", 3},
    {"ld_card:cd4c", 4},
    {"ld_card:cd4d", 4},
    {"ld_card:cd4h", 4},
    {"ld_card:cd4s", 4},
    {"ld_card:cd5c", 5},
    {"ld_card:cd5d", 5},
    {"ld_card:cd5h", 5},
    {"ld_card:cd5s", 5},
    {"ld_card:cd6c", 6},
    {"ld_card:cd6d", 6},
    {"ld_card:cd6h", 6},
    {"ld_card:cd6s", 6},
    {"ld_card:cd7c", 7},
    {"ld_card:cd7d", 7},
    {"ld_card:cd7h", 7},
    {"ld_card:cd7s", 7},
    {"ld_card:cd8c", 8},
    {"ld_card:cd8d", 8},
    {"ld_card:cd8h", 8},
    {"ld_card:cd8s", 8},
    {"ld_card:cd9c", 9},
    {"ld_card:cd9d", 9},
    {"ld_card:cd9h", 9},
    {"ld_card:cd9s", 9},
    {"ld_card:cd10c", 10},
    {"ld_card:cd10d", 10},
    {"ld_card:cd10h", 10},
    {"ld_card:cd10s", 10},
    {"ld_card:cd11c", 10},
    {"ld_card:cd11d", 10},
    {"ld_card:cd11h", 10},
    {"ld_card:cd11s", 10},
    {"ld_card:cd12c", 10},
    {"ld_card:cd12d", 10},
    {"ld_card:cd12h", 10},
    {"ld_card:cd12s", 10},
    {"ld_card:cd13c", 10},
    {"ld_card:cd13d", 10},
    {"ld_card:cd13h", 10},
    {"ld_card:cd13s", 10},
    {"ld_card:cd1c", 11},
    {"ld_card:cd1d", 11},
    {"ld_card:cd1h", 11},
    {"ld_card:cd1s", 11},
    {"ld_card:cd2c", 2},
    {"ld_card:cd2d", 2},
    {"ld_card:cd2h", 2},
    {"ld_card:cd2s", 2},
    {"ld_card:cd3c", 3},
    {"ld_card:cd3d", 3},
    {"ld_card:cd3h", 3},
    {"ld_card:cd3s", 3},
    {"ld_card:cd4c", 4},
    {"ld_card:cd4d", 4},
    {"ld_card:cd4h", 4},
    {"ld_card:cd4s", 4},
    {"ld_card:cd5c", 5},
    {"ld_card:cd5d", 5},
    {"ld_card:cd5h", 5},
    {"ld_card:cd5s", 5},
    {"ld_card:cd6c", 6},
    {"ld_card:cd6d", 6},
    {"ld_card:cd6h", 6},
    {"ld_card:cd6s", 6},
    {"ld_card:cd7c", 7},
    {"ld_card:cd7d", 7},
    {"ld_card:cd7h", 7},
    {"ld_card:cd7s", 7},
    {"ld_card:cd8c", 8},
    {"ld_card:cd8d", 8},
    {"ld_card:cd8h", 8},
    {"ld_card:cd8s", 8},
    {"ld_card:cd9c", 9},
    {"ld_card:cd9d", 9},
    {"ld_card:cd9h", 9},
    {"ld_card:cd9s", 9},
    {"ld_card:cd10c", 10},
    {"ld_card:cd10d", 10},
    {"ld_card:cd10h", 10},
    {"ld_card:cd10s", 10},
    {"ld_card:cd11c", 10},
    {"ld_card:cd11d", 10},
    {"ld_card:cd11h", 10},
    {"ld_card:cd11s", 10},
    {"ld_card:cd12c", 10},
    {"ld_card:cd12d", 10},
    {"ld_card:cd12h", 10},
    {"ld_card:cd12s", 10},
    {"ld_card:cd13c", 10},
    {"ld_card:cd13d", 10},
    {"ld_card:cd13h", 10},
    {"ld_card:cd13s", 10},
    {"ld_card:cd1c", 11},
    {"ld_card:cd1d", 11},
    {"ld_card:cd1h", 11},
    {"ld_card:cd1s", 11},
    {"ld_card:cd2c", 2},
    {"ld_card:cd2d", 2},
    {"ld_card:cd2h", 2},
    {"ld_card:cd2s", 2},
    {"ld_card:cd3c", 3},
    {"ld_card:cd3d", 3},
    {"ld_card:cd3h", 3},
    {"ld_card:cd3s", 3},
    {"ld_card:cd4c", 4},
    {"ld_card:cd4d", 4},
    {"ld_card:cd4h", 4},
    {"ld_card:cd4s", 4},
    {"ld_card:cd5c", 5},
    {"ld_card:cd5d", 5},
    {"ld_card:cd5h", 5},
    {"ld_card:cd5s", 5},
    {"ld_card:cd6c", 6},
    {"ld_card:cd6d", 6},
    {"ld_card:cd6h", 6},
    {"ld_card:cd6s", 6},
    {"ld_card:cd7c", 7},
    {"ld_card:cd7d", 7},
    {"ld_card:cd7h", 7},
    {"ld_card:cd7s", 7},
    {"ld_card:cd8c", 8},
    {"ld_card:cd8d", 8},
    {"ld_card:cd8h", 8},
    {"ld_card:cd8s", 8},
    {"ld_card:cd9c", 9},
    {"ld_card:cd9d", 9},
    {"ld_card:cd9h", 9},
    {"ld_card:cd9s", 9},
    {"ld_card:cd10c", 10},
    {"ld_card:cd10d", 10},
    {"ld_card:cd10h", 10},
    {"ld_card:cd10s", 10},
    {"ld_card:cd11c", 10},
    {"ld_card:cd11d", 10},
    {"ld_card:cd11h", 10},
    {"ld_card:cd11s", 10},
    {"ld_card:cd12c", 10},
    {"ld_card:cd12d", 10},
    {"ld_card:cd12h", 10},
    {"ld_card:cd12s", 10},
    {"ld_card:cd13c", 10},
    {"ld_card:cd13d", 10},
    {"ld_card:cd13h", 10},
    {"ld_card:cd13s", 10},
    {"ld_card:cd1c", 11},
    {"ld_card:cd1d", 11},
    {"ld_card:cd1h", 11},
    {"ld_card:cd1s", 11},
    {"ld_card:cd2c", 2},
    {"ld_card:cd2d", 2},
    {"ld_card:cd2h", 2},
    {"ld_card:cd2s", 2},
    {"ld_card:cd3c", 3},
    {"ld_card:cd3d", 3},
    {"ld_card:cd3h", 3},
    {"ld_card:cd3s", 3},
    {"ld_card:cd4c", 4},
    {"ld_card:cd4d", 4},
    {"ld_card:cd4h", 4},
    {"ld_card:cd4s", 4},
    {"ld_card:cd5c", 5},
    {"ld_card:cd5d", 5},
    {"ld_card:cd5h", 5},
    {"ld_card:cd5s", 5},
    {"ld_card:cd6c", 6},
    {"ld_card:cd6d", 6},
    {"ld_card:cd6h", 6},
    {"ld_card:cd6s", 6},
    {"ld_card:cd7c", 7},
    {"ld_card:cd7d", 7},
    {"ld_card:cd7h", 7},
    {"ld_card:cd7s", 7},
    {"ld_card:cd8c", 8},
    {"ld_card:cd8d", 8},
    {"ld_card:cd8h", 8},
    {"ld_card:cd8s", 8},
    {"ld_card:cd9c", 9},
    {"ld_card:cd9d", 9},
    {"ld_card:cd9h", 9},
    {"ld_card:cd9s", 9},
    {"ld_card:cd10c", 10},
    {"ld_card:cd10d", 10},
    {"ld_card:cd10h", 10},
    {"ld_card:cd10s", 10},
    {"ld_card:cd11c", 10},
    {"ld_card:cd11d", 10},
    {"ld_card:cd11h", 10},
    {"ld_card:cd11s", 10},
    {"ld_card:cd12c", 10},
    {"ld_card:cd12d", 10},
    {"ld_card:cd12h", 10},
    {"ld_card:cd12s", 10},
    {"ld_card:cd13c", 10},
    {"ld_card:cd13d", 10},
    {"ld_card:cd13h", 10},
    {"ld_card:cd13s", 10},
    {"ld_card:cd1c", 11},
    {"ld_card:cd1d", 11},
    {"ld_card:cd1h", 11},
    {"ld_card:cd1s", 11},
    {"ld_card:cd2c", 2},
    {"ld_card:cd2d", 2},
    {"ld_card:cd2h", 2},
    {"ld_card:cd2s", 2},
    {"ld_card:cd3c", 3},
    {"ld_card:cd3d", 3},
    {"ld_card:cd3h", 3},
    {"ld_card:cd3s", 3},
    {"ld_card:cd4c", 4},
    {"ld_card:cd4d", 4},
    {"ld_card:cd4h", 4},
    {"ld_card:cd4s", 4},
    {"ld_card:cd5c", 5},
    {"ld_card:cd5d", 5},
    {"ld_card:cd5h", 5},
    {"ld_card:cd5s", 5},
    {"ld_card:cd6c", 6},
    {"ld_card:cd6d", 6},
    {"ld_card:cd6h", 6},
    {"ld_card:cd6s", 6},
    {"ld_card:cd7c", 7},
    {"ld_card:cd7d", 7},
    {"ld_card:cd7h", 7},
    {"ld_card:cd7s", 7},
    {"ld_card:cd8c", 8},
    {"ld_card:cd8d", 8},
    {"ld_card:cd8h", 8},
    {"ld_card:cd8s", 8},
    {"ld_card:cd9c", 9},
    {"ld_card:cd9d", 9},
    {"ld_card:cd9h", 9},
    {"ld_card:cd9s", 9},
    {"ld_card:cd10c", 10},
    {"ld_card:cd10d", 10},
    {"ld_card:cd10h", 10},
    {"ld_card:cd10s", 10},
    {"ld_card:cd11c", 10},
    {"ld_card:cd11d", 10},
    {"ld_card:cd11h", 10},
    {"ld_card:cd11s", 10},
    {"ld_card:cd12c", 10},
    {"ld_card:cd12d", 10},
    {"ld_card:cd12h", 10},
    {"ld_card:cd12s", 10},
    {"ld_card:cd13c", 10},
    {"ld_card:cd13d", 10},
    {"ld_card:cd13h", 10},
    {"ld_card:cd13s", 10},
    {"ld_card:cd1c", 11},
    {"ld_card:cd1d", 11},
    {"ld_card:cd1h", 11},
    {"ld_card:cd1s", 11},
    {"ld_card:cd2c", 2},
    {"ld_card:cd2d", 2},
    {"ld_card:cd2h", 2},
    {"ld_card:cd2s", 2},
    {"ld_card:cd3c", 3},
    {"ld_card:cd3d", 3},
    {"ld_card:cd3h", 3},
    {"ld_card:cd3s", 3},
    {"ld_card:cd4c", 4},
    {"ld_card:cd4d", 4},
    {"ld_card:cd4h", 4},
    {"ld_card:cd4s", 4},
    {"ld_card:cd5c", 5},
    {"ld_card:cd5d", 5},
    {"ld_card:cd5h", 5},
    {"ld_card:cd5s", 5},
    {"ld_card:cd6c", 6},
    {"ld_card:cd6d", 6},
    {"ld_card:cd6h", 6},
    {"ld_card:cd6s", 6},
    {"ld_card:cd7c", 7},
    {"ld_card:cd7d", 7},
    {"ld_card:cd7h", 7},
    {"ld_card:cd7s", 7},
    {"ld_card:cd8c", 8},
    {"ld_card:cd8d", 8},
    {"ld_card:cd8h", 8},
    {"ld_card:cd8s", 8},
    {"ld_card:cd9c", 9},
    {"ld_card:cd9d", 9},
    {"ld_card:cd9h", 9},
    {"ld_card:cd9s", 9},
    {"ld_card:cd10c", 10},
    {"ld_card:cd10d", 10},
    {"ld_card:cd10h", 10},
    {"ld_card:cd10s", 10},
    {"ld_card:cd11c", 10},
    {"ld_card:cd11d", 10},
    {"ld_card:cd11h", 10},
    {"ld_card:cd11s", 10},
    {"ld_card:cd12c", 10},
    {"ld_card:cd12d", 10},
    {"ld_card:cd12h", 10},
    {"ld_card:cd12s", 10},
    {"ld_card:cd13c", 10},
    {"ld_card:cd13d", 10},
    {"ld_card:cd13h", 10},
    {"ld_card:cd13s", 10},
    {"ld_card:cd1c", 11},
    {"ld_card:cd1d", 11},
    {"ld_card:cd1h", 11},
    {"ld_card:cd1s", 11},
    {"ld_card:cd2c", 2},
    {"ld_card:cd2d", 2},
    {"ld_card:cd2h", 2},
    {"ld_card:cd2s", 2},
    {"ld_card:cd3c", 3},
    {"ld_card:cd3d", 3},
    {"ld_card:cd3h", 3},
    {"ld_card:cd3s", 3},
    {"ld_card:cd4c", 4},
    {"ld_card:cd4d", 4},
    {"ld_card:cd4h", 4},
    {"ld_card:cd4s", 4},
    {"ld_card:cd5c", 5},
    {"ld_card:cd5d", 5},
    {"ld_card:cd5h", 5},
    {"ld_card:cd5s", 5},
    {"ld_card:cd6c", 6},
    {"ld_card:cd6d", 6},
    {"ld_card:cd6h", 6},
    {"ld_card:cd6s", 6},
    {"ld_card:cd7c", 7},
    {"ld_card:cd7d", 7},
    {"ld_card:cd7h", 7},
    {"ld_card:cd7s", 7},
    {"ld_card:cd8c", 8},
    {"ld_card:cd8d", 8},
    {"ld_card:cd8h", 8},
    {"ld_card:cd8s", 8},
    {"ld_card:cd9c", 9},
    {"ld_card:cd9d", 9},
    {"ld_card:cd9h", 9},
    {"ld_card:cd9s", 9}
};
new Iterator:CardsUsed[MAX_BJ_TABLES]<(sizeof(g_CasinoCards)+1)>;

BJTable_BeingEdited(tblid)
{
	if(!Iter_Contains(BJTables, tblid)) return 0;
	foreach(new i : Player) if(AccountData[i][EditingTableBJID] == tblid) return 1;
	return 0;
}

BJTable_Rebuild(tblid)
{
	if (tblid != -1)
	{
		if (DestroyDynamicObject(BlackJackTable[tblid][BJTableObj]))
		    BlackJackTable[tblid][BJTableObj] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

        if (DestroyDynamicActor(BlackJackTable[tblid][BJActor]))
		    BlackJackTable[tblid][BJActor] = STREAMER_TAG_ACTOR: INVALID_STREAMER_ID;

        new Float:actorX = BlackJackTable[tblid][Pos][0] + 0.65*(floatcos(90 + BlackJackTable[tblid][Pos][5], degrees));
        new Float:actorY = BlackJackTable[tblid][Pos][1] + 0.65*(floatsin(90 - BlackJackTable[tblid][Pos][5], degrees));

        new randskin = __g_CasinoNPCSkin[random(sizeof(__g_CasinoNPCSkin))];
		BlackJackTable[tblid][BJActor] = CreateDynamicActor(randskin, actorX, actorY, BlackJackTable[tblid][Pos][2], BlackJackTable[tblid][Pos][5] - 180.0, true, 1000.0, BlackJackTable[tblid][World], BlackJackTable[tblid][Interior], -1, 100.00, -1, 0);
        BlackJackTable[tblid][BJTableObj] = CreateDynamicObject(2188, BlackJackTable[tblid][Pos][0], BlackJackTable[tblid][Pos][1], BlackJackTable[tblid][Pos][2], BlackJackTable[tblid][Pos][3], BlackJackTable[tblid][Pos][4], BlackJackTable[tblid][Pos][5], BlackJackTable[tblid][World], BlackJackTable[tblid][Interior], -1, 100.00, 100.00, -1);
        
        BlackJackTable[tblid][BJStarted] = false;
        BlackJackTable[tblid][BJCountdown] = 0;
    }
	return 1;
}

BJTable_Refresh(id)
{
    if(id != -1)
    {
        SetDynamicObjectPos(BlackJackTable[id][BJTableObj], BlackJackTable[id][Pos][0], BlackJackTable[id][Pos][1], BlackJackTable[id][Pos][2]);
        SetDynamicObjectRot(BlackJackTable[id][BJTableObj], BlackJackTable[id][Pos][3], BlackJackTable[id][Pos][4], BlackJackTable[id][Pos][5]);
        Streamer_SetIntData(STREAMER_TYPE_OBJECT, BlackJackTable[id][BJTableObj], E_STREAMER_WORLD_ID, BlackJackTable[id][World]);
        Streamer_SetIntData(STREAMER_TYPE_OBJECT, BlackJackTable[id][BJTableObj], E_STREAMER_INTERIOR_ID, BlackJackTable[id][Interior]);

        SetDynamicActorFacingAngle(BlackJackTable[id][BJActor], BlackJackTable[id][Pos][5]-180.00);

        new Float:actorX = BlackJackTable[id][Pos][0] + 0.65*(floatcos(90 + BlackJackTable[id][Pos][5], degrees));
        new Float:actorY = BlackJackTable[id][Pos][1] + 0.65*(floatsin(90 - BlackJackTable[id][Pos][5], degrees));
        SetDynamicActorPos(BlackJackTable[id][BJActor], actorX, actorY, BlackJackTable[id][Pos][2]);
    }
}

BJTable_Save(id)
{
	new
	    query[512];
        
	format(query, sizeof(query), "UPDATE bj_tables SET X = '%f', Y = '%f', Z = '%f', RX = '%f', RY = '%f', RZ = '%f', Interior = %d, World = %d, MinBet = %d, MaxBet = %d WHERE id = %d",
        BlackJackTable[id][Pos][0],
        BlackJackTable[id][Pos][1],
        BlackJackTable[id][Pos][2],
        BlackJackTable[id][Pos][3],
        BlackJackTable[id][Pos][4],
        BlackJackTable[id][Pos][5],
        BlackJackTable[id][Interior],
        BlackJackTable[id][World],
        BlackJackTable[id][MinBet],
        BlackJackTable[id][MaxBet],
        id
	);
	return mysql_pquery(g_SQL, query);
}

BJTable_Nearest(playerid)
{
    foreach(new i : BJTables) if (IsPlayerInRangeOfPoint(playerid, 2.0, BlackJackTable[i][Pos][0], BlackJackTable[i][Pos][1], BlackJackTable[i][Pos][2]))
	{
		if (GetPlayerInterior(playerid) == BlackJackTable[i][Interior] && GetPlayerVirtualWorld(playerid) == BlackJackTable[i][World])
			return i;
	}
	return -1;
}

BJTable_IsBusy(id)
{
    foreach(new i : Player) if(AccountData[i][pSpawned] && PlayerBlackJack[i][pInBJTable] == id)
    {
        return true;
    }
    return false;
}

BJTable_Splitable(playerid)
{
    // Show Split
 	new firstcard[18], secondcard[18], cardnumber[2] = 0;

	PlayerTextDrawGetString(playerid, BlackJackPTD[playerid][0],firstcard,sizeof(firstcard));
	PlayerTextDrawGetString(playerid, BlackJackPTD[playerid][1],secondcard,sizeof(secondcard));

	for(new j; j < sizeof(g_CasinoCards); j++)
	{
		if(!strcmp(firstcard, g_CasinoCards[j][CardModelID], true)) cardnumber[0] = g_CasinoCards[j][CardValue1];
		if(!strcmp(secondcard, g_CasinoCards[j][CardModelID], true)) cardnumber[1] = g_CasinoCards[j][CardValue1];
	}

	if(cardnumber[0] == cardnumber[1]) return true;

	return false;
}

BJTable_CreatePlayerTD(playerid)
{
    BlackJackPTD[playerid][0] = CreatePlayerTextDraw(playerid, 264.000000, 267.000000, "ld_card:cd12h");
    PlayerTextDrawFont(playerid, BlackJackPTD[playerid][0], 4);
    PlayerTextDrawLetterSize(playerid, BlackJackPTD[playerid][0], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, BlackJackPTD[playerid][0], 19.000000, 24.000000);
    PlayerTextDrawSetOutline(playerid, BlackJackPTD[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, BlackJackPTD[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, BlackJackPTD[playerid][0], 1);
    PlayerTextDrawColor(playerid, BlackJackPTD[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, BlackJackPTD[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, BlackJackPTD[playerid][0], 50);
    PlayerTextDrawUseBox(playerid, BlackJackPTD[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, BlackJackPTD[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, BlackJackPTD[playerid][0], 0);

    BlackJackPTD[playerid][1] = CreatePlayerTextDraw(playerid, 272.000000, 260.000000, "ld_card:cd1s");
    PlayerTextDrawFont(playerid, BlackJackPTD[playerid][1], 4);
    PlayerTextDrawLetterSize(playerid, BlackJackPTD[playerid][1], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, BlackJackPTD[playerid][1], 19.000000, 24.000000);
    PlayerTextDrawSetOutline(playerid, BlackJackPTD[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, BlackJackPTD[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, BlackJackPTD[playerid][1], 1);
    PlayerTextDrawColor(playerid, BlackJackPTD[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, BlackJackPTD[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, BlackJackPTD[playerid][1], 50);
    PlayerTextDrawUseBox(playerid, BlackJackPTD[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, BlackJackPTD[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, BlackJackPTD[playerid][1], 0);

    BlackJackPTD[playerid][2] = CreatePlayerTextDraw(playerid, 280.000000, 253.000000, "ld_card:cd13d");
    PlayerTextDrawFont(playerid, BlackJackPTD[playerid][2], 4);
    PlayerTextDrawLetterSize(playerid, BlackJackPTD[playerid][2], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, BlackJackPTD[playerid][2], 19.000000, 24.000000);
    PlayerTextDrawSetOutline(playerid, BlackJackPTD[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, BlackJackPTD[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, BlackJackPTD[playerid][2], 1);
    PlayerTextDrawColor(playerid, BlackJackPTD[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, BlackJackPTD[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, BlackJackPTD[playerid][2], 50);
    PlayerTextDrawUseBox(playerid, BlackJackPTD[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, BlackJackPTD[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, BlackJackPTD[playerid][2], 0);

    BlackJackPTD[playerid][3] = CreatePlayerTextDraw(playerid, 288.000000, 246.000000, "ld_card:cd3d");
    PlayerTextDrawFont(playerid, BlackJackPTD[playerid][3], 4);
    PlayerTextDrawLetterSize(playerid, BlackJackPTD[playerid][3], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, BlackJackPTD[playerid][3], 19.000000, 24.000000);
    PlayerTextDrawSetOutline(playerid, BlackJackPTD[playerid][3], 1);
    PlayerTextDrawSetShadow(playerid, BlackJackPTD[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, BlackJackPTD[playerid][3], 1);
    PlayerTextDrawColor(playerid, BlackJackPTD[playerid][3], -1);
    PlayerTextDrawBackgroundColor(playerid, BlackJackPTD[playerid][3], 255);
    PlayerTextDrawBoxColor(playerid, BlackJackPTD[playerid][3], 50);
    PlayerTextDrawUseBox(playerid, BlackJackPTD[playerid][3], 1);
    PlayerTextDrawSetProportional(playerid, BlackJackPTD[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, BlackJackPTD[playerid][3], 0);

    BlackJackPTD[playerid][4] = CreatePlayerTextDraw(playerid, 296.000000, 239.000000, "ld_card:cd2h");
    PlayerTextDrawFont(playerid, BlackJackPTD[playerid][4], 4);
    PlayerTextDrawLetterSize(playerid, BlackJackPTD[playerid][4], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, BlackJackPTD[playerid][4], 19.000000, 24.000000);
    PlayerTextDrawSetOutline(playerid, BlackJackPTD[playerid][4], 1);
    PlayerTextDrawSetShadow(playerid, BlackJackPTD[playerid][4], 0);
    PlayerTextDrawAlignment(playerid, BlackJackPTD[playerid][4], 1);
    PlayerTextDrawColor(playerid, BlackJackPTD[playerid][4], -1);
    PlayerTextDrawBackgroundColor(playerid, BlackJackPTD[playerid][4], 255);
    PlayerTextDrawBoxColor(playerid, BlackJackPTD[playerid][4], 50);
    PlayerTextDrawUseBox(playerid, BlackJackPTD[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, BlackJackPTD[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, BlackJackPTD[playerid][4], 0);

    BlackJackPTD[playerid][5] = CreatePlayerTextDraw(playerid, 273.000000, 292.000000, "24");
    PlayerTextDrawFont(playerid, BlackJackPTD[playerid][5], 2);
    PlayerTextDrawLetterSize(playerid, BlackJackPTD[playerid][5], 0.150000, 1.000000);
    PlayerTextDrawTextSize(playerid, BlackJackPTD[playerid][5], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, BlackJackPTD[playerid][5], 1);
    PlayerTextDrawSetShadow(playerid, BlackJackPTD[playerid][5], 0);
    PlayerTextDrawAlignment(playerid, BlackJackPTD[playerid][5], 2);
    PlayerTextDrawColor(playerid, BlackJackPTD[playerid][5], -1);
    PlayerTextDrawBackgroundColor(playerid, BlackJackPTD[playerid][5], 255);
    PlayerTextDrawBoxColor(playerid, BlackJackPTD[playerid][5], 50);
    PlayerTextDrawUseBox(playerid, BlackJackPTD[playerid][5], 0);
    PlayerTextDrawSetProportional(playerid, BlackJackPTD[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, BlackJackPTD[playerid][5], 0);

    BlackJackPTD[playerid][6] = CreatePlayerTextDraw(playerid, 273.000000, 300.000000, "$2,500.00");
    PlayerTextDrawFont(playerid, BlackJackPTD[playerid][6], 2);
    PlayerTextDrawLetterSize(playerid, BlackJackPTD[playerid][6], 0.150000, 1.000000);
    PlayerTextDrawTextSize(playerid, BlackJackPTD[playerid][6], 400.000000, 44.000000);
    PlayerTextDrawSetOutline(playerid, BlackJackPTD[playerid][6], 1);
    PlayerTextDrawSetShadow(playerid, BlackJackPTD[playerid][6], 0);
    PlayerTextDrawAlignment(playerid, BlackJackPTD[playerid][6], 2);
    PlayerTextDrawColor(playerid, BlackJackPTD[playerid][6], 9109759);
    PlayerTextDrawBackgroundColor(playerid, BlackJackPTD[playerid][6], 255);
    PlayerTextDrawBoxColor(playerid, BlackJackPTD[playerid][6], 50);
    PlayerTextDrawUseBox(playerid, BlackJackPTD[playerid][6], 0);
    PlayerTextDrawSetProportional(playerid, BlackJackPTD[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, BlackJackPTD[playerid][6], 0);

    //SPLIT TD
    SplitBJTD[playerid][0] = CreatePlayerTextDraw(playerid, 320.000000, 267.000000, "ld_card:cd1s");
	PlayerTextDrawFont(playerid, SplitBJTD[playerid][0], 4);
	PlayerTextDrawLetterSize(playerid, SplitBJTD[playerid][0], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, SplitBJTD[playerid][0], 19.000000, 24.000000);
	PlayerTextDrawSetOutline(playerid, SplitBJTD[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, SplitBJTD[playerid][0], 0);
	PlayerTextDrawAlignment(playerid, SplitBJTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, SplitBJTD[playerid][0], -1);
	PlayerTextDrawBackgroundColor(playerid, SplitBJTD[playerid][0], 255);
	PlayerTextDrawBoxColor(playerid, SplitBJTD[playerid][0], 50);
	PlayerTextDrawUseBox(playerid, SplitBJTD[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, SplitBJTD[playerid][0], 1);
	PlayerTextDrawSetSelectable(playerid, SplitBJTD[playerid][0], 0);

	SplitBJTD[playerid][1] = CreatePlayerTextDraw(playerid, 328.000000, 260.000000, "ld_card:cd3d");
	PlayerTextDrawFont(playerid, SplitBJTD[playerid][1], 4);
	PlayerTextDrawLetterSize(playerid, SplitBJTD[playerid][1], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, SplitBJTD[playerid][1], 19.000000, 24.000000);
	PlayerTextDrawSetOutline(playerid, SplitBJTD[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, SplitBJTD[playerid][1], 0);
	PlayerTextDrawAlignment(playerid, SplitBJTD[playerid][1], 1);
	PlayerTextDrawColor(playerid, SplitBJTD[playerid][1], -1);
	PlayerTextDrawBackgroundColor(playerid, SplitBJTD[playerid][1], 255);
	PlayerTextDrawBoxColor(playerid, SplitBJTD[playerid][1], 50);
	PlayerTextDrawUseBox(playerid, SplitBJTD[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, SplitBJTD[playerid][1], 1);
	PlayerTextDrawSetSelectable(playerid, SplitBJTD[playerid][1], 0);

	SplitBJTD[playerid][2] = CreatePlayerTextDraw(playerid, 336.000000, 253.000000, "ld_card:cd3d");
	PlayerTextDrawFont(playerid, SplitBJTD[playerid][2], 4);
	PlayerTextDrawLetterSize(playerid, SplitBJTD[playerid][2], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, SplitBJTD[playerid][2], 19.000000, 24.000000);
	PlayerTextDrawSetOutline(playerid, SplitBJTD[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, SplitBJTD[playerid][2], 0);
	PlayerTextDrawAlignment(playerid, SplitBJTD[playerid][2], 1);
	PlayerTextDrawColor(playerid, SplitBJTD[playerid][2], -1);
	PlayerTextDrawBackgroundColor(playerid, SplitBJTD[playerid][2], 255);
	PlayerTextDrawBoxColor(playerid, SplitBJTD[playerid][2], 50);
	PlayerTextDrawUseBox(playerid, SplitBJTD[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, SplitBJTD[playerid][2], 1);
	PlayerTextDrawSetSelectable(playerid, SplitBJTD[playerid][2], 0);

	SplitBJTD[playerid][3] = CreatePlayerTextDraw(playerid, 344.000000, 246.000000, "ld_card:cd3d");
	PlayerTextDrawFont(playerid, SplitBJTD[playerid][3], 4);
	PlayerTextDrawLetterSize(playerid, SplitBJTD[playerid][3], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, SplitBJTD[playerid][3], 19.000000, 24.000000);
	PlayerTextDrawSetOutline(playerid, SplitBJTD[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, SplitBJTD[playerid][3], 0);
	PlayerTextDrawAlignment(playerid, SplitBJTD[playerid][3], 1);
	PlayerTextDrawColor(playerid, SplitBJTD[playerid][3], -1);
	PlayerTextDrawBackgroundColor(playerid, SplitBJTD[playerid][3], 255);
	PlayerTextDrawBoxColor(playerid, SplitBJTD[playerid][3], 50);
	PlayerTextDrawUseBox(playerid, SplitBJTD[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, SplitBJTD[playerid][3], 1);
	PlayerTextDrawSetSelectable(playerid, SplitBJTD[playerid][3], 0);

	SplitBJTD[playerid][4] = CreatePlayerTextDraw(playerid, 352.000000, 239.000000, "ld_card:cd3d");
	PlayerTextDrawFont(playerid, SplitBJTD[playerid][4], 4);
	PlayerTextDrawLetterSize(playerid, SplitBJTD[playerid][4], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, SplitBJTD[playerid][4], 19.000000, 24.000000);
	PlayerTextDrawSetOutline(playerid, SplitBJTD[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, SplitBJTD[playerid][4], 0);
	PlayerTextDrawAlignment(playerid, SplitBJTD[playerid][4], 1);
	PlayerTextDrawColor(playerid, SplitBJTD[playerid][4], -1);
	PlayerTextDrawBackgroundColor(playerid, SplitBJTD[playerid][4], 255);
	PlayerTextDrawBoxColor(playerid, SplitBJTD[playerid][4], 50);
	PlayerTextDrawUseBox(playerid, SplitBJTD[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, SplitBJTD[playerid][4], 1);
	PlayerTextDrawSetSelectable(playerid, SplitBJTD[playerid][4], 0);

	SplitBJTD[playerid][5] = CreatePlayerTextDraw(playerid, 329.000000, 292.000000, "24");
	PlayerTextDrawFont(playerid, SplitBJTD[playerid][5], 2);
	PlayerTextDrawLetterSize(playerid, SplitBJTD[playerid][5], 0.150000, 1.000000);
	PlayerTextDrawTextSize(playerid, SplitBJTD[playerid][5], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, SplitBJTD[playerid][5], 1);
	PlayerTextDrawSetShadow(playerid, SplitBJTD[playerid][5], 0);
	PlayerTextDrawAlignment(playerid, SplitBJTD[playerid][5], 2);
	PlayerTextDrawColor(playerid, SplitBJTD[playerid][5], -1);
	PlayerTextDrawBackgroundColor(playerid, SplitBJTD[playerid][5], 255);
	PlayerTextDrawBoxColor(playerid, SplitBJTD[playerid][5], 50);
	PlayerTextDrawUseBox(playerid, SplitBJTD[playerid][5], 0);
	PlayerTextDrawSetProportional(playerid, SplitBJTD[playerid][5], 1);
	PlayerTextDrawSetSelectable(playerid, SplitBJTD[playerid][5], 0);
	
	SplitBJTD[playerid][6] = CreatePlayerTextDraw(playerid, 329.000000, 300.000000, "$2,500.00");
	PlayerTextDrawFont(playerid, SplitBJTD[playerid][6], 2);
	PlayerTextDrawLetterSize(playerid, SplitBJTD[playerid][6], 0.150000, 1.000000);
	PlayerTextDrawTextSize(playerid, SplitBJTD[playerid][6], 400.000000, 44.000000);
	PlayerTextDrawSetOutline(playerid, SplitBJTD[playerid][6], 1);
	PlayerTextDrawSetShadow(playerid, SplitBJTD[playerid][6], 0);
	PlayerTextDrawAlignment(playerid, SplitBJTD[playerid][6], 2);
	PlayerTextDrawColor(playerid, SplitBJTD[playerid][6], 9109759);
	PlayerTextDrawBackgroundColor(playerid, SplitBJTD[playerid][6], 255);
	PlayerTextDrawBoxColor(playerid, SplitBJTD[playerid][6], 50);
	PlayerTextDrawUseBox(playerid, SplitBJTD[playerid][6], 0);
	PlayerTextDrawSetProportional(playerid, SplitBJTD[playerid][6], 1);
	PlayerTextDrawSetSelectable(playerid, SplitBJTD[playerid][6], 0);

    //

    BJTableCardTD[playerid][0] = CreatePlayerTextDraw(playerid, 509.000000, 179.000000, "Deck Cards~n~416");
	PlayerTextDrawFont(playerid, BJTableCardTD[playerid][0], 1);
	PlayerTextDrawLetterSize(playerid, BJTableCardTD[playerid][0], 0.195833, 1.250000);
	PlayerTextDrawTextSize(playerid, BJTableCardTD[playerid][0], 400.000000, 47.000000);
	PlayerTextDrawSetOutline(playerid, BJTableCardTD[playerid][0], 0);
	PlayerTextDrawSetShadow(playerid, BJTableCardTD[playerid][0], 0);
	PlayerTextDrawAlignment(playerid, BJTableCardTD[playerid][0], 2);
	PlayerTextDrawColor(playerid, BJTableCardTD[playerid][0], -2686721);
	PlayerTextDrawBackgroundColor(playerid, BJTableCardTD[playerid][0], 255);
	PlayerTextDrawBoxColor(playerid, BJTableCardTD[playerid][0], 50);
	PlayerTextDrawUseBox(playerid, BJTableCardTD[playerid][0], 0);
	PlayerTextDrawSetProportional(playerid, BJTableCardTD[playerid][0], 1);
	PlayerTextDrawSetSelectable(playerid, BJTableCardTD[playerid][0], 0);

	BJTableCardTD[playerid][1] = CreatePlayerTextDraw(playerid, 509.000000, 205.000000, "Table Bet:~n~$500.00 - $1,000.00");
	PlayerTextDrawFont(playerid, BJTableCardTD[playerid][1], 1);
	PlayerTextDrawLetterSize(playerid, BJTableCardTD[playerid][1], 0.150000, 0.950000);
	PlayerTextDrawTextSize(playerid, BJTableCardTD[playerid][1], 400.000000, 79.500000);
	PlayerTextDrawSetOutline(playerid, BJTableCardTD[playerid][1], 0);
	PlayerTextDrawSetShadow(playerid, BJTableCardTD[playerid][1], 0);
	PlayerTextDrawAlignment(playerid, BJTableCardTD[playerid][1], 2);
	PlayerTextDrawColor(playerid, BJTableCardTD[playerid][1], -2686721);
	PlayerTextDrawBackgroundColor(playerid, BJTableCardTD[playerid][1], 255);
	PlayerTextDrawBoxColor(playerid, BJTableCardTD[playerid][1], 50);
	PlayerTextDrawUseBox(playerid, BJTableCardTD[playerid][1], 0);
	PlayerTextDrawSetProportional(playerid, BJTableCardTD[playerid][1], 1);
	PlayerTextDrawSetSelectable(playerid, BJTableCardTD[playerid][1], 0);

    //dealer
	DealerBJTD[playerid][0] = CreatePlayerTextDraw(playerid, 295.000000, 181.000000, "ld_card:cd12h");
	PlayerTextDrawFont(playerid, DealerBJTD[playerid][0], 4);
	PlayerTextDrawLetterSize(playerid, DealerBJTD[playerid][0], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, DealerBJTD[playerid][0], 19.000000, 24.000000);
	PlayerTextDrawSetOutline(playerid, DealerBJTD[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, DealerBJTD[playerid][0], 0);
	PlayerTextDrawAlignment(playerid, DealerBJTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, DealerBJTD[playerid][0], -1);
	PlayerTextDrawBackgroundColor(playerid, DealerBJTD[playerid][0], 255);
	PlayerTextDrawBoxColor(playerid, DealerBJTD[playerid][0], 50);
	PlayerTextDrawUseBox(playerid, DealerBJTD[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, DealerBJTD[playerid][0], 1);
	PlayerTextDrawSetSelectable(playerid, DealerBJTD[playerid][0], 0);

	DealerBJTD[playerid][1] = CreatePlayerTextDraw(playerid, 303.000000, 174.000000, "ld_card:cd12h");
	PlayerTextDrawFont(playerid, DealerBJTD[playerid][1], 4);
	PlayerTextDrawLetterSize(playerid, DealerBJTD[playerid][1], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, DealerBJTD[playerid][1], 19.000000, 24.000000);
	PlayerTextDrawSetOutline(playerid, DealerBJTD[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, DealerBJTD[playerid][1], 0);
	PlayerTextDrawAlignment(playerid, DealerBJTD[playerid][1], 1);
	PlayerTextDrawColor(playerid, DealerBJTD[playerid][1], -1);
	PlayerTextDrawBackgroundColor(playerid, DealerBJTD[playerid][1], 255);
	PlayerTextDrawBoxColor(playerid, DealerBJTD[playerid][1], 50);
	PlayerTextDrawUseBox(playerid, DealerBJTD[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, DealerBJTD[playerid][1], 1);
	PlayerTextDrawSetSelectable(playerid, DealerBJTD[playerid][1], 0);

	DealerBJTD[playerid][2] = CreatePlayerTextDraw(playerid, 311.000000, 167.000000, "ld_card:cd12h");
	PlayerTextDrawFont(playerid, DealerBJTD[playerid][2], 4);
	PlayerTextDrawLetterSize(playerid, DealerBJTD[playerid][2], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, DealerBJTD[playerid][2], 19.000000, 24.000000);
	PlayerTextDrawSetOutline(playerid, DealerBJTD[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, DealerBJTD[playerid][2], 0);
	PlayerTextDrawAlignment(playerid, DealerBJTD[playerid][2], 1);
	PlayerTextDrawColor(playerid, DealerBJTD[playerid][2], -1);
	PlayerTextDrawBackgroundColor(playerid, DealerBJTD[playerid][2], 255);
	PlayerTextDrawBoxColor(playerid, DealerBJTD[playerid][2], 50);
	PlayerTextDrawUseBox(playerid, DealerBJTD[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, DealerBJTD[playerid][2], 1);
	PlayerTextDrawSetSelectable(playerid, DealerBJTD[playerid][2], 0);

	DealerBJTD[playerid][3] = CreatePlayerTextDraw(playerid, 318.000000, 160.000000, "ld_card:cd12h");
	PlayerTextDrawFont(playerid, DealerBJTD[playerid][3], 4);
	PlayerTextDrawLetterSize(playerid, DealerBJTD[playerid][3], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, DealerBJTD[playerid][3], 19.000000, 24.000000);
	PlayerTextDrawSetOutline(playerid, DealerBJTD[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, DealerBJTD[playerid][3], 0);
	PlayerTextDrawAlignment(playerid, DealerBJTD[playerid][3], 1);
	PlayerTextDrawColor(playerid, DealerBJTD[playerid][3], -1);
	PlayerTextDrawBackgroundColor(playerid, DealerBJTD[playerid][3], 255);
	PlayerTextDrawBoxColor(playerid, DealerBJTD[playerid][3], 50);
	PlayerTextDrawUseBox(playerid, DealerBJTD[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, DealerBJTD[playerid][3], 1);
	PlayerTextDrawSetSelectable(playerid, DealerBJTD[playerid][3], 0);

	DealerBJTD[playerid][4] = CreatePlayerTextDraw(playerid, 326.000000, 153.000000, "ld_card:cd12h");
	PlayerTextDrawFont(playerid, DealerBJTD[playerid][4], 4);
	PlayerTextDrawLetterSize(playerid, DealerBJTD[playerid][4], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, DealerBJTD[playerid][4], 19.000000, 24.000000);
	PlayerTextDrawSetOutline(playerid, DealerBJTD[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, DealerBJTD[playerid][4], 0);
	PlayerTextDrawAlignment(playerid, DealerBJTD[playerid][4], 1);
	PlayerTextDrawColor(playerid, DealerBJTD[playerid][4], -1);
	PlayerTextDrawBackgroundColor(playerid, DealerBJTD[playerid][4], 255);
	PlayerTextDrawBoxColor(playerid, DealerBJTD[playerid][4], 50);
	PlayerTextDrawUseBox(playerid, DealerBJTD[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, DealerBJTD[playerid][4], 1);
	PlayerTextDrawSetSelectable(playerid, DealerBJTD[playerid][4], 0);

	DealerBJTD[playerid][5] = CreatePlayerTextDraw(playerid, 305.000000, 206.000000, "21");
	PlayerTextDrawFont(playerid, DealerBJTD[playerid][5], 2);
	PlayerTextDrawLetterSize(playerid, DealerBJTD[playerid][5], 0.150000, 1.000000);
	PlayerTextDrawTextSize(playerid, DealerBJTD[playerid][5], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, DealerBJTD[playerid][5], 1);
	PlayerTextDrawSetShadow(playerid, DealerBJTD[playerid][5], 0);
	PlayerTextDrawAlignment(playerid, DealerBJTD[playerid][5], 2);
	PlayerTextDrawColor(playerid, DealerBJTD[playerid][5], -1);
	PlayerTextDrawBackgroundColor(playerid, DealerBJTD[playerid][5], 255);
	PlayerTextDrawBoxColor(playerid, DealerBJTD[playerid][5], 50);
	PlayerTextDrawUseBox(playerid, DealerBJTD[playerid][5], 0);
	PlayerTextDrawSetProportional(playerid, DealerBJTD[playerid][5], 1);
	PlayerTextDrawSetSelectable(playerid, DealerBJTD[playerid][5], 0);

    DealerBJTD[playerid][6] = CreatePlayerTextDraw(playerid, 323.000000, 261.000000, "New hand starts in 5 second...~n~Place your bets");
    PlayerTextDrawAlignment(playerid, DealerBJTD[playerid][6], 2);
    PlayerTextDrawBackgroundColor(playerid, DealerBJTD[playerid][6], 255);
    PlayerTextDrawFont(playerid, DealerBJTD[playerid][6], 2);
    PlayerTextDrawLetterSize(playerid, DealerBJTD[playerid][6], 0.159998, 0.899999);
    PlayerTextDrawColor(playerid, DealerBJTD[playerid][6], -1);
    PlayerTextDrawSetOutline(playerid, DealerBJTD[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, DealerBJTD[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, DealerBJTD[playerid][6], 0);
}

BJTable_HideTextDraw(playerid)
{
    for(new x; x < 7; x++)
    {
        PlayerTextDrawHide(playerid, BlackJackPTD[playerid][x]);
    }

    PlayerTextDrawSetString(playerid, BlackJackPTD[playerid][5], "0");
    PlayerTextDrawSetString(playerid, BlackJackPTD[playerid][6], "$0");
    return 1;
}

BJTable_StandOut(playerid, id)
{
    for(new x; x < 7; x++)
    {
        PlayerTextDrawDestroy(playerid, BlackJackPTD[playerid][x]);
        BlackJackPTD[playerid][x] = PlayerText: INVALID_PLAYER_TEXT_DRAW;

        PlayerTextDrawDestroy(playerid, SplitBJTD[playerid][x]);
        SplitBJTD[playerid][x] = PlayerText: INVALID_PLAYER_TEXT_DRAW;

        PlayerTextDrawDestroy(playerid, DealerBJTD[playerid][x]);
        DealerBJTD[playerid][x] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
    }

    TextDrawHideForPlayer(playerid, BlackJackTD[0]);
    TextDrawHideForPlayer(playerid, BlackJackTD[1]);
    TextDrawHideForPlayer(playerid, BlackJackTD[2]);

    TextDrawHideForPlayer(playerid, BlackJackTD[8]);
    TextDrawHideForPlayer(playerid, BlackJackTD[9]);

    PlayerTextDrawDestroy(playerid, BJTableCardTD[playerid][0]);
    BJTableCardTD[playerid][0] = PlayerText: INVALID_PLAYER_TEXT_DRAW;

    PlayerTextDrawDestroy(playerid, BJTableCardTD[playerid][1]);
    BJTableCardTD[playerid][1] = PlayerText: INVALID_PLAYER_TEXT_DRAW;

    BlackJackTable[id][BJCurrPlayerID] = INVALID_PLAYER_ID;
    BlackJackTable[id][BJCountdown] = 0;
    PlayerBlackJack[playerid][Forbidden] = false;
    PlayerBlackJack[playerid][HasAce][0] = false;
    PlayerBlackJack[playerid][HasAce][1] = false;
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
    PlayerBlackJack[playerid][Seated] = false;
    PlayerBlackJack[playerid][Bet][0] = 0;
    PlayerBlackJack[playerid][Bet][1] = 0;
    PlayerBlackJack[playerid][CardValue][0] = 0;
    PlayerBlackJack[playerid][CardValue][1] = 0;
    PlayerBlackJack[playerid][pCardsId] = -1;
    PlayerBlackJack[playerid][DealerCardsId] = -1;
    PlayerBlackJack[playerid][pInBJTable] = -1;
    PlayerBlackJack[playerid][DealerCardValue] = 0;
    PlayerBlackJack[playerid][DealerClosedCard] = -1;
    PlayerBlackJack[playerid][pCountCards] = -1;

    PlayerPlayNearbySound(playerid, 5852);
    return 1;
}

BJTable_ShuffleDeck(playerid, tableid)
{
    PlayerTextDrawSetString(playerid, BJTableCardTD[playerid][0], sprintf("Deck Cards~n~%d", Iter_Count(CardsUsed[tableid])));

	if(Iter_Count(CardsUsed[tableid]) < MINIMUM_DECK_CARDS)
	{
	    Iter_Init(CardsUsed);
		for(new i; i<sizeof(g_CasinoCards); i++)
		{
			Iter_Add(CardsUsed[tableid], i);
		}
		SendClientMessage(playerid, X11_LIGHTBLUE, "DEALER: The deck of cards has now been changed!");
	}
	return 1;
}

forward NextRoundPrepare(playerid);
public NextRoundPrepare(playerid)
{
    if(!IsPlayerConnected(playerid)) return 1;
    if(!AccountData[playerid][pSpawned]) return 1;
    if(!PlayerBlackJack[playerid][Seated]) return 1;

    Dialog_Show(playerid, "BlackjackEnd", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Blackjack", "We have finished our round, would you like to continue?", "Continue", "Stand Out");
    return 1;
}

forward ContinueDrawCards(playerid, id);
public ContinueDrawCards(playerid, id)
{
    if(!IsPlayerConnected(playerid)) return 1;
    if(!AccountData[playerid][pSpawned]) return 1;
    if(!PlayerBlackJack[playerid][Seated]) return 1;
    BJTable_GivePlayerCards(playerid, id);
    return 1;
}

forward LoadBJTables();
public LoadBJTables()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
 		new id;
		for(new i; i < rows; i++)
		{
            cache_get_value_name_int(i, "id", id);
            cache_get_value_name_float(i, "X", BlackJackTable[id][Pos][0]);
            cache_get_value_name_float(i, "Y", BlackJackTable[id][Pos][1]);
            cache_get_value_name_float(i, "Z", BlackJackTable[id][Pos][2]);
            cache_get_value_name_float(i, "RX", BlackJackTable[id][Pos][3]);
            cache_get_value_name_float(i, "RY", BlackJackTable[id][Pos][4]);
            cache_get_value_name_float(i, "RZ", BlackJackTable[id][Pos][5]);
            cache_get_value_name_int(i, "World", BlackJackTable[id][World]);
            cache_get_value_name_int(i, "Interior", BlackJackTable[id][Interior]);
            cache_get_value_name_int(i, "MinBet", BlackJackTable[id][MinBet]);
            cache_get_value_name_int(i, "MaxBet", BlackJackTable[id][MaxBet]);
            
			Iter_Add(BJTables, id);

            Iter_Init(CardsUsed);
            for(new x; x < sizeof(g_CasinoCards); x++)
            {
                Iter_Add(CardsUsed[id], x);
            }
			BJTable_Rebuild(id);
        }
        printf("[Dynamic Blackjack] Jumlah total Blackjack Table yang dimuat: %d.", rows);
	}
    return 1;
}

BJTable_GivePlayerCards(playerid, id)
{
    PlayerBlackJack[playerid][pCountCards]++; //default -1, start from 0

    if(PlayerBlackJack[playerid][Splited] && !PlayerBlackJack[playerid][SplitCardGiven])
    {
        switch(PlayerBlackJack[playerid][pCountCards])
        {
            case 4: //kartu player kanan kedua
            {
                new randcard = Iter_Random(CardsUsed[id]);
                Iter_Remove(CardsUsed[id],randcard);
                
                PlayerBlackJack[playerid][pSplitCardsID] = 1;
                ApplyDynamicActorAnimation(BlackJackTable[id][BJActor], "CASINO", "dealone", 4.1, false, false, false, false, 0);

                PlayerTextDrawSetString(playerid, SplitBJTD[playerid][1], g_CasinoCards[randcard][CardModelID]);
                PlayerTextDrawShow(playerid, SplitBJTD[playerid][1]);
                PlayerBlackJack[playerid][CardValue][1] += g_CasinoCards[randcard][CardValue1];
                
                if(g_CasinoCards[randcard][CardValue1] == 11)
                    PlayerBlackJack[playerid][HasAce][1] = true;

                if(PlayerBlackJack[playerid][HasAce][1])
                {
                    PlayerTextDrawSetString(playerid, SplitBJTD[playerid][5], sprintf("%d or %d", PlayerBlackJack[playerid][CardValue][1]-10, PlayerBlackJack[playerid][CardValue][1]));
                }
                else
                {
                    PlayerTextDrawSetString(playerid, SplitBJTD[playerid][5], sprintf("%d", PlayerBlackJack[playerid][CardValue][1]));
                }

                switch(PlayerBlackJack[playerid][CardValue][1])
                {
                    case 4: {PlayerPlayNearbySound(playerid, 5841);}
                    case 5: {PlayerPlayNearbySound(playerid, 5842);}
                    case 6: {PlayerPlayNearbySound(playerid, 5843);}
                    case 7: {PlayerPlayNearbySound(playerid, 5844);}
                    case 8: {PlayerPlayNearbySound(playerid, 5845);}
                    case 9: {PlayerPlayNearbySound(playerid, 5846);}
                    case 10: {PlayerPlayNearbySound(playerid, 5829);}
                    case 11: {PlayerPlayNearbySound(playerid, 5830);}
                    case 12: 
                    {
                        if(PlayerBlackJack[playerid][HasAce][1])
                        {
                            PlayerPlayNearbySound(playerid, 5801); //2 or 12
                        }
                        else
                        {
                            PlayerPlayNearbySound(playerid, 5831); //12
                        }
                    }
                    case 13: 
                    {
                        if(PlayerBlackJack[playerid][HasAce][1])
                        {
                            PlayerPlayNearbySound(playerid, 5802); //3 or 13
                        }
                        else
                        {
                            PlayerPlayNearbySound(playerid, 5832); //13
                        }
                    }
                    case 14: 
                    {
                        if(PlayerBlackJack[playerid][HasAce][1])
                        {
                            PlayerPlayNearbySound(playerid, 5803); //4 or 14
                        }
                        else
                        {
                            PlayerPlayNearbySound(playerid, 5833); //13
                        }
                    }
                    case 15: 
                    {
                        if(PlayerBlackJack[playerid][HasAce][1])
                        {
                            PlayerPlayNearbySound(playerid, 5804); //5 or 15
                        }
                        else
                        {
                            PlayerPlayNearbySound(playerid, 5834); //13
                        }
                    }
                    case 16: 
                    {
                        if(PlayerBlackJack[playerid][HasAce][1])
                        {
                            PlayerPlayNearbySound(playerid, 5805); //6 or 16
                        }
                        else
                        {
                            PlayerPlayNearbySound(playerid, 5835); //13
                        }
                    }
                    case 17: 
                    {
                        if(PlayerBlackJack[playerid][HasAce][1])
                        {
                            PlayerPlayNearbySound(playerid, 5806); //7 or 17
                        }
                        else
                        {
                            PlayerPlayNearbySound(playerid, 5836); //13
                        }
                    }
                    case 18:
                    {
                        if(PlayerBlackJack[playerid][HasAce][1])
                        {
                            PlayerPlayNearbySound(playerid, 5807); //8 or 18
                        }
                        else
                        {
                            PlayerPlayNearbySound(playerid, 5837); //13
                        }
                    }
                    case 19: 
                    {
                        if(PlayerBlackJack[playerid][HasAce][1])
                        {
                            PlayerPlayNearbySound(playerid, 5808); //9 or 19
                        }
                        else
                        {
                            PlayerPlayNearbySound(playerid, 5838); //13
                        }
                    }
                    case 20: 
                    {
                        if(PlayerBlackJack[playerid][HasAce][1])
                        {
                            PlayerPlayNearbySound(playerid, 5800); //10 or 20
                        }
                        else
                        {
                            PlayerPlayNearbySound(playerid, 5839); //13
                        }
                    }
                    case 21: {PlayerPlayNearbySound(playerid, 5840);}
                }

                if(PlayerBlackJack[playerid][HasAce][1] && PlayerBlackJack[playerid][CardValue][1] == 21)
                {
                    PlayerBlackJack[playerid][BlackJack] = true;
                    PlayerPlayNearbySound(playerid, 5811);
                    GameTextForPlayer(playerid, "~y~BLACKJACK!", 3500, 6);
                }

                TextDrawShowForPlayer(playerid, BlackJackTD[0]);
                TextDrawHideForPlayer(playerid, BlackJackTD[1]);
                TextDrawHideForPlayer(playerid, BlackJackTD[2]);
                
                BJTable_ShuffleDeck(playerid, id);
                SetTimerEx("ContinueDrawCards", 1555, false, "id", playerid, id);
            }
            case 5: //kartu player kiri kedua
            {
                new randcard = Iter_Random(CardsUsed[id]);
                Iter_Remove(CardsUsed[id],randcard);
                
                PlayerBlackJack[playerid][pCardsId] = 1;
                ApplyDynamicActorAnimation(BlackJackTable[id][BJActor], "CASINO", "dealone", 4.1, false, false, false, false, 0);

                PlayerTextDrawSetString(playerid, BlackJackPTD[playerid][1], g_CasinoCards[randcard][CardModelID]);
                PlayerTextDrawShow(playerid, BlackJackPTD[playerid][1]);
                PlayerBlackJack[playerid][CardValue][0] += g_CasinoCards[randcard][CardValue1];
                
                if(g_CasinoCards[randcard][CardValue1] == 11)
                    PlayerBlackJack[playerid][HasAce][0] = true;

                if(PlayerBlackJack[playerid][HasAce][0])
                {
                    PlayerTextDrawSetString(playerid, BlackJackPTD[playerid][5], sprintf("%d or %d", PlayerBlackJack[playerid][CardValue][0]-10, PlayerBlackJack[playerid][CardValue][0]));
                }
                else
                {
                    PlayerTextDrawSetString(playerid, BlackJackPTD[playerid][5], sprintf("%d", PlayerBlackJack[playerid][CardValue][0]));
                }

                switch(PlayerBlackJack[playerid][CardValue][0])
                {
                    case 4: {PlayerPlayNearbySound(playerid, 5841);}
                    case 5: {PlayerPlayNearbySound(playerid, 5842);}
                    case 6: {PlayerPlayNearbySound(playerid, 5843);}
                    case 7: {PlayerPlayNearbySound(playerid, 5844);}
                    case 8: {PlayerPlayNearbySound(playerid, 5845);}
                    case 9: {PlayerPlayNearbySound(playerid, 5846);}
                    case 10: {PlayerPlayNearbySound(playerid, 5829);}
                    case 11: {PlayerPlayNearbySound(playerid, 5830);}
                    case 12: 
                    {
                        if(PlayerBlackJack[playerid][HasAce][0])
                        {
                            PlayerPlayNearbySound(playerid, 5801); //2 or 12
                        }
                        else
                        {
                            PlayerPlayNearbySound(playerid, 5831); //12
                        }
                    }
                    case 13: 
                    {
                        if(PlayerBlackJack[playerid][HasAce][0])
                        {
                            PlayerPlayNearbySound(playerid, 5802); //3 or 13
                        }
                        else
                        {
                            PlayerPlayNearbySound(playerid, 5832); //13
                        }
                    }
                    case 14: 
                    {
                        if(PlayerBlackJack[playerid][HasAce][0])
                        {
                            PlayerPlayNearbySound(playerid, 5803); //4 or 14
                        }
                        else
                        {
                            PlayerPlayNearbySound(playerid, 5833); //13
                        }
                    }
                    case 15: 
                    {
                        if(PlayerBlackJack[playerid][HasAce][0])
                        {
                            PlayerPlayNearbySound(playerid, 5804); //5 or 15
                        }
                        else
                        {
                            PlayerPlayNearbySound(playerid, 5834); //13
                        }
                    }
                    case 16: 
                    {
                        if(PlayerBlackJack[playerid][HasAce][0])
                        {
                            PlayerPlayNearbySound(playerid, 5805); //6 or 16
                        }
                        else
                        {
                            PlayerPlayNearbySound(playerid, 5835); //13
                        }
                    }
                    case 17: 
                    {
                        if(PlayerBlackJack[playerid][HasAce][0])
                        {
                            PlayerPlayNearbySound(playerid, 5806); //7 or 17
                        }
                        else
                        {
                            PlayerPlayNearbySound(playerid, 5836); //13
                        }
                    }
                    case 18:
                    {
                        if(PlayerBlackJack[playerid][HasAce][0])
                        {
                            PlayerPlayNearbySound(playerid, 5807); //8 or 18
                        }
                        else
                        {
                            PlayerPlayNearbySound(playerid, 5837); //13
                        }
                    }
                    case 19: 
                    {
                        if(PlayerBlackJack[playerid][HasAce][0])
                        {
                            PlayerPlayNearbySound(playerid, 5808); //9 or 19
                        }
                        else
                        {
                            PlayerPlayNearbySound(playerid, 5838); //13
                        }
                    }
                    case 20: 
                    {
                        if(PlayerBlackJack[playerid][HasAce][0])
                        {
                            PlayerPlayNearbySound(playerid, 5800); //10 or 20
                        }
                        else
                        {
                            PlayerPlayNearbySound(playerid, 5839); //13
                        }
                    }
                    case 21: {PlayerPlayNearbySound(playerid, 5840);}
                }

                if(PlayerBlackJack[playerid][HasAce][0] && PlayerBlackJack[playerid][CardValue][0] == 21)
                {
                    PlayerBlackJack[playerid][BlackJack] = true;
                    PlayerPlayNearbySound(playerid, 5811);
                    GameTextForPlayer(playerid, "~y~BLACKJACK!", 3500, 6);
                }

                TextDrawHideForPlayer(playerid, BlackJackTD[0]);
                TextDrawHideForPlayer(playerid, BlackJackTD[1]);
                TextDrawShowForPlayer(playerid, BlackJackTD[2]);
                
                BJTable_ShuffleDeck(playerid, id);

                PlayerBlackJack[playerid][SplitCardGiven] = true;
                PlayerBlackJack[playerid][IsSelectSplitCard] = true;
                SendClientMessage(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"It's still your turn, feel free to do something now.");

                if(PlayerBlackJack[playerid][DealerHasAce])
                {
                    SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"Last offer, do you wanna take the insurance for "YELLOW"$%s?", FormatMoney(floatround(PlayerBlackJack[playerid][Bet][0]*0.5)));
                    
                    ShowPlayerBlackJackTD(playerid);
                    TextDrawShowForPlayer(playerid, BlackJackTD[6]);
                }
                else
                {
                    ShowPlayerBlackJackTD(playerid);
                }
            }
        }
        return 1;
    }

    switch(PlayerBlackJack[playerid][pCountCards])
    {
        case 0: //kartu player pertama
        {
            new randcard = Iter_Random(CardsUsed[id]);
	        Iter_Remove(CardsUsed[id],randcard);
            
            PlayerBlackJack[playerid][pCardsId] = 0;
            ApplyDynamicActorAnimation(BlackJackTable[id][BJActor], "CASINO", "dealone", 4.1, false, false, false, false, 0);

            PlayerTextDrawSetString(playerid, BlackJackPTD[playerid][0], g_CasinoCards[randcard][CardModelID]);
            PlayerTextDrawShow(playerid, BlackJackPTD[playerid][0]);
            PlayerBlackJack[playerid][CardValue][0] += g_CasinoCards[randcard][CardValue1];
            
            if(g_CasinoCards[randcard][CardValue1] == 11)
                PlayerBlackJack[playerid][HasAce][0] = true;

            if(PlayerBlackJack[playerid][HasAce][0])
            {
                PlayerTextDrawSetString(playerid, BlackJackPTD[playerid][5], sprintf("%d or %d", PlayerBlackJack[playerid][CardValue][0]-10, PlayerBlackJack[playerid][CardValue][0]));
            }
            else
            {
                PlayerTextDrawSetString(playerid, BlackJackPTD[playerid][5], sprintf("%d", PlayerBlackJack[playerid][CardValue][0]));
            }
            PlayerTextDrawShow(playerid, BlackJackPTD[playerid][5]);

            switch(PlayerBlackJack[playerid][CardValue][0])
            {
                case 4..9:
                {
                    PlayerPlayNearbySound(playerid, 5837+g_CasinoCards[randcard][CardValue1]);
                }

                case 10..21:
                {
                    PlayerPlayNearbySound(playerid, 5819+g_CasinoCards[randcard][CardValue1]);
                }
            }

            TextDrawShowForPlayer(playerid, BlackJackTD[0]);
            TextDrawHideForPlayer(playerid, BlackJackTD[1]);
            
            BJTable_ShuffleDeck(playerid, id);
            SetTimerEx("ContinueDrawCards", 1555, false, "id", playerid, id);
        }
        case 1: //kartu dealer pertama
        {
            new randcard = Iter_Random(CardsUsed[id]);
	        Iter_Remove(CardsUsed[id],randcard);

            PlayerBlackJack[playerid][DealerCardsId] = 0;
            ApplyDynamicActorAnimation(BlackJackTable[id][BJActor], "CASINO", "dealone", 4.1, false, false, false, false, 0);

            PlayerTextDrawSetString(playerid, DealerBJTD[playerid][0], g_CasinoCards[randcard][CardModelID]);
            PlayerTextDrawShow(playerid, DealerBJTD[playerid][0]);
            PlayerBlackJack[playerid][DealerCardValue] += g_CasinoCards[randcard][CardValue1];

            if(g_CasinoCards[randcard][CardValue1] == 11)
                PlayerBlackJack[playerid][DealerHasAce] = true;

            if(PlayerBlackJack[playerid][DealerHasAce])
            {
                PlayerTextDrawSetString(playerid, DealerBJTD[playerid][5], sprintf("%d or %d", PlayerBlackJack[playerid][DealerCardValue]-10, PlayerBlackJack[playerid][DealerCardValue]));
            }
            else
            {
                PlayerTextDrawSetString(playerid, DealerBJTD[playerid][5], sprintf("%d", PlayerBlackJack[playerid][DealerCardValue]));
            }
            PlayerTextDrawShow(playerid, DealerBJTD[playerid][5]);

            switch(PlayerBlackJack[playerid][DealerCardValue])
            {
                case 4..9:
                {
                    PlayerPlayNearbySound(playerid, 5837+g_CasinoCards[randcard][CardValue1]);
                }

                case 10..21:
                {
                    PlayerPlayNearbySound(playerid, 5819+g_CasinoCards[randcard][CardValue1]);
                }
            }

            TextDrawHideForPlayer(playerid, BlackJackTD[0]);
            TextDrawShowForPlayer(playerid, BlackJackTD[1]);
            TextDrawHideForPlayer(playerid, BlackJackTD[2]);

            BJTable_ShuffleDeck(playerid, id);
            SetTimerEx("ContinueDrawCards", 1555, false, "id", playerid, id);
        }
        case 2: //kartu player kedua
        {
            new randcard = Iter_Random(CardsUsed[id]);
	        Iter_Remove(CardsUsed[id],randcard);
            
            PlayerBlackJack[playerid][pCardsId] = 1;
            ApplyDynamicActorAnimation(BlackJackTable[id][BJActor], "CASINO", "dealone", 4.1, false, false, false, false, 0);

            PlayerTextDrawSetString(playerid, BlackJackPTD[playerid][1], g_CasinoCards[randcard][CardModelID]);
            PlayerTextDrawShow(playerid, BlackJackPTD[playerid][1]);
            PlayerBlackJack[playerid][CardValue][0] += g_CasinoCards[randcard][CardValue1];

            if(g_CasinoCards[randcard][CardValue1] == 11)
                PlayerBlackJack[playerid][HasAce][0] = true;

            if(PlayerBlackJack[playerid][HasAce][0])
            {
                PlayerTextDrawSetString(playerid, BlackJackPTD[playerid][5], sprintf("%d or %d", PlayerBlackJack[playerid][CardValue][0]-10, PlayerBlackJack[playerid][CardValue][0]));
            }
            else
            {
                PlayerTextDrawSetString(playerid, BlackJackPTD[playerid][5], sprintf("%d", PlayerBlackJack[playerid][CardValue][0]));
            }

            switch(PlayerBlackJack[playerid][CardValue][0])
            {
                case 4: {PlayerPlayNearbySound(playerid, 5841);}
                case 5: {PlayerPlayNearbySound(playerid, 5842);}
                case 6: {PlayerPlayNearbySound(playerid, 5843);}
                case 7: {PlayerPlayNearbySound(playerid, 5844);}
                case 8: {PlayerPlayNearbySound(playerid, 5845);}
                case 9: {PlayerPlayNearbySound(playerid, 5846);}
                case 10: {PlayerPlayNearbySound(playerid, 5829);}
                case 11: {PlayerPlayNearbySound(playerid, 5830);}
                case 12: 
                {
                    if(PlayerBlackJack[playerid][HasAce][0])
                    {
                        PlayerPlayNearbySound(playerid, 5801); //2 or 12
                    }
                    else
                    {
                        PlayerPlayNearbySound(playerid, 5831); //12
                    }
                }
                case 13: 
                {
                    if(PlayerBlackJack[playerid][HasAce][0])
                    {
                        PlayerPlayNearbySound(playerid, 5802); //3 or 13
                    }
                    else
                    {
                        PlayerPlayNearbySound(playerid, 5832); //13
                    }
                }
                case 14: 
                {
                    if(PlayerBlackJack[playerid][HasAce][0])
                    {
                        PlayerPlayNearbySound(playerid, 5803); //4 or 14
                    }
                    else
                    {
                        PlayerPlayNearbySound(playerid, 5833); //13
                    }
                }
                case 15: 
                {
                    if(PlayerBlackJack[playerid][HasAce][0])
                    {
                        PlayerPlayNearbySound(playerid, 5804); //5 or 15
                    }
                    else
                    {
                        PlayerPlayNearbySound(playerid, 5834); //13
                    }
                }
                case 16: 
                {
                    if(PlayerBlackJack[playerid][HasAce][0])
                    {
                        PlayerPlayNearbySound(playerid, 5805); //6 or 16
                    }
                    else
                    {
                        PlayerPlayNearbySound(playerid, 5835); //13
                    }
                }
                case 17: 
                {
                    if(PlayerBlackJack[playerid][HasAce][0])
                    {
                        PlayerPlayNearbySound(playerid, 5806); //7 or 17
                    }
                    else
                    {
                        PlayerPlayNearbySound(playerid, 5836); //13
                    }
                }
                case 18:
                {
                    if(PlayerBlackJack[playerid][HasAce][0])
                    {
                        PlayerPlayNearbySound(playerid, 5807); //8 or 18
                    }
                    else
                    {
                        PlayerPlayNearbySound(playerid, 5837); //13
                    }
                }
                case 19: 
                {
                    if(PlayerBlackJack[playerid][HasAce][0])
                    {
                        PlayerPlayNearbySound(playerid, 5808); //9 or 19
                    }
                    else
                    {
                        PlayerPlayNearbySound(playerid, 5838); //13
                    }
                }
                case 20: 
                {
                    if(PlayerBlackJack[playerid][HasAce][0])
                    {
                        PlayerPlayNearbySound(playerid, 5800); //10 or 20
                    }
                    else
                    {
                        PlayerPlayNearbySound(playerid, 5839); //13
                    }
                }
                case 21: {PlayerPlayNearbySound(playerid, 5840);}
            }

            if(PlayerBlackJack[playerid][HasAce][0] && PlayerBlackJack[playerid][CardValue][0] == 21)
            {
                PlayerBlackJack[playerid][BlackJack] = true;
                PlayerPlayNearbySound(playerid, 5811);
                GameTextForPlayer(playerid, "~y~BLACKJACK!", 3500, 6);
            }

            TextDrawShowForPlayer(playerid, BlackJackTD[0]);
            TextDrawHideForPlayer(playerid, BlackJackTD[1]);

            BJTable_ShuffleDeck(playerid, id);
            SetTimerEx("ContinueDrawCards", 1555, false, "id", playerid, id);
        }
        case 3: //kartu dealer kedua tutup & start move
        {
            new randcard = Iter_Random(CardsUsed[id]);
	        Iter_Remove(CardsUsed[id],randcard);
            
            PlayerBlackJack[playerid][DealerCardsId] = 1;
            PlayerBlackJack[playerid][DealerClosedCard] = randcard;
            PlayerBlackJack[playerid][DealerCardStillClosed] = true;

            ApplyDynamicActorAnimation(BlackJackTable[id][BJActor], "CASINO", "dealone", 4.1, false, false, false, false, 0);

            PlayerTextDrawSetString(playerid, DealerBJTD[playerid][1], "ld_card:cdback");
            PlayerTextDrawShow(playerid, DealerBJTD[playerid][1]);

            if(PlayerBlackJack[playerid][DealerHasAce])
            {
                SendClientMessage(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"Choose your own way, now.");
                SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"Do you wanna take insurance for "YELLOW"$%s?", FormatMoney(floatround(PlayerBlackJack[playerid][Bet][0]*0.5)));
                
                ShowPlayerBlackJackTD(playerid);
                TextDrawShowForPlayer(playerid, BlackJackTD[6]);

                if(BJTable_Splitable(playerid))
                {
                    TextDrawShowForPlayer(playerid, BlackJackTD[7]);
                }
            }
            else
            {
                if(PlayerBlackJack[playerid][DealerCardValue] == 10)
                {
                    SendClientMessage(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"One second, dealer have to checking for blackjack.");
                    GameTextForPlayer(playerid, "~p~CHECKING FOR~n~BLACKJACK...", 5500, 6);
                    SetTimerEx("CheckingForBlackjack", 5500, false, "id", playerid, id);
                }
                else
                {
                    SendClientMessage(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"Choose your own way, now.");
                    ShowPlayerBlackJackTD(playerid);

                    if(BJTable_Splitable(playerid))
                    {
                        TextDrawShowForPlayer(playerid, BlackJackTD[7]);
                    }
                }
            }
            BJTable_ShuffleDeck(playerid, id);
        }
        default:
        {
            if(!PlayerBlackJack[playerid][Forbidden]) //jika hit masih berjalan dan player blum stand / bust
            {
                if(PlayerBlackJack[playerid][pCardsId] < 4 && PlayerBlackJack[playerid][pSplitCardsID] < 4)
                {
                    new randcard = Iter_Random(CardsUsed[id]);
	                Iter_Remove(CardsUsed[id],randcard);

                    if(PlayerBlackJack[playerid][Splited] && PlayerBlackJack[playerid][IsSelectSplitCard]) //dalam mode split dan arrow sedang pada kartu split
                    {
                        PlayerBlackJack[playerid][pSplitCardsID]++;
                        ApplyDynamicActorAnimation(BlackJackTable[id][BJActor], "CASINO", "dealone", 4.1, false, false, false, false, 0);

                        PlayerTextDrawSetString(playerid, SplitBJTD[playerid][PlayerBlackJack[playerid][pSplitCardsID]], g_CasinoCards[randcard][CardModelID]);
                        PlayerTextDrawShow(playerid, SplitBJTD[playerid][PlayerBlackJack[playerid][pSplitCardsID]]);
                        PlayerBlackJack[playerid][CardValue][1] += g_CasinoCards[randcard][CardValue1];

                        if(g_CasinoCards[randcard][CardValue1] == 11)
                            PlayerBlackJack[playerid][HasAce][1] = true;

                        if(PlayerBlackJack[playerid][CardValue][1] > 21) //jika kartu kanan bust
                        {
                            if(PlayerBlackJack[playerid][HasAce][1]) //mengandung ace lanjut
                            {
                                PlayerBlackJack[playerid][CardValue][1]-=10;
                                PlayerTextDrawSetString(playerid, SplitBJTD[playerid][5], sprintf("%d", PlayerBlackJack[playerid][CardValue][1]));
                            }
                            else //tidak ada ace dan bust dialihkan ke kiri
                            {
                                PlayerBlackJack[playerid][IsSelectSplitCard] = false;
                                PlayerTextDrawSetString(playerid, SplitBJTD[playerid][5], "~r~BUST!");

                                PlayerPlayNearbySound(playerid, 5813);

                                ApplyAnimation(playerid,"CASINO", "Roulette_lose",4.1,false,false,false,false,0,true);

                                TextDrawShowForPlayer(playerid, BlackJackTD[0]);
                                TextDrawHideForPlayer(playerid, BlackJackTD[1]);
                                TextDrawHideForPlayer(playerid, BlackJackTD[2]);
                            }
                        }
                        else //kartu kanan belum bust, lanjut
                        {
                            switch(PlayerBlackJack[playerid][CardValue][1])
                            {
                                case 4: {PlayerPlayNearbySound(playerid, 5841);}
                                case 5: {PlayerPlayNearbySound(playerid, 5842);}
                                case 6: {PlayerPlayNearbySound(playerid, 5843);}
                                case 7: {PlayerPlayNearbySound(playerid, 5844);}
                                case 8: {PlayerPlayNearbySound(playerid, 5845);}
                                case 9: {PlayerPlayNearbySound(playerid, 5846);}
                                case 10: {PlayerPlayNearbySound(playerid, 5829);}
                                case 11: {PlayerPlayNearbySound(playerid, 5830);}
                                case 12: 
                                {
                                    if(PlayerBlackJack[playerid][HasAce][1])
                                    {
                                        PlayerPlayNearbySound(playerid, 5801); //2 or 12
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5831); //12
                                    }
                                }
                                case 13: 
                                {
                                    if(PlayerBlackJack[playerid][HasAce][1])
                                    {
                                        PlayerPlayNearbySound(playerid, 5802); //3 or 13
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5832); //13
                                    }
                                }
                                case 14: 
                                {
                                    if(PlayerBlackJack[playerid][HasAce][1])
                                    {
                                        PlayerPlayNearbySound(playerid, 5803); //4 or 14
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5833); //13
                                    }
                                }
                                case 15: 
                                {
                                    if(PlayerBlackJack[playerid][HasAce][1])
                                    {
                                        PlayerPlayNearbySound(playerid, 5804); //5 or 15
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5834); //13
                                    }
                                }
                                case 16: 
                                {
                                    if(PlayerBlackJack[playerid][HasAce][1])
                                    {
                                        PlayerPlayNearbySound(playerid, 5805); //6 or 16
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5835); //13
                                    }
                                }
                                case 17: 
                                {
                                    if(PlayerBlackJack[playerid][HasAce][1])
                                    {
                                        PlayerPlayNearbySound(playerid, 5806); //7 or 17
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5836); //13
                                    }
                                }
                                case 18:
                                {
                                    if(PlayerBlackJack[playerid][HasAce][1])
                                    {
                                        PlayerPlayNearbySound(playerid, 5807); //8 or 18
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5837); //13
                                    }
                                }
                                case 19: 
                                {
                                    if(PlayerBlackJack[playerid][HasAce][1])
                                    {
                                        PlayerPlayNearbySound(playerid, 5808); //9 or 19
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5838); //13
                                    }
                                }
                                case 20: 
                                {
                                    if(PlayerBlackJack[playerid][HasAce][1])
                                    {
                                        PlayerPlayNearbySound(playerid, 5800); //10 or 20
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5839); //13
                                    }
                                }
                                case 21: {PlayerPlayNearbySound(playerid, 5840);}
                            }
                            if(PlayerBlackJack[playerid][HasAce][1])
                            {
                                PlayerTextDrawSetString(playerid, SplitBJTD[playerid][5], sprintf("%d or %d", PlayerBlackJack[playerid][CardValue][1]-10, PlayerBlackJack[playerid][CardValue][1]));
                            }
                            else
                            {
                                PlayerTextDrawSetString(playerid, SplitBJTD[playerid][5], sprintf("%d", PlayerBlackJack[playerid][CardValue][1]));
                            }
                        }
                    }
                    else //jika tidak di split atau di split namun tidak lagi memilih kartu yang di split
                    {
                        PlayerBlackJack[playerid][pCardsId]++;
                        ApplyDynamicActorAnimation(BlackJackTable[id][BJActor], "CASINO", "dealone", 4.1, false, false, false, false, 0);

                        PlayerTextDrawSetString(playerid, BlackJackPTD[playerid][PlayerBlackJack[playerid][pCardsId]], g_CasinoCards[randcard][CardModelID]);
                        PlayerTextDrawShow(playerid, BlackJackPTD[playerid][PlayerBlackJack[playerid][pCardsId]]);
                        PlayerBlackJack[playerid][CardValue][0] += g_CasinoCards[randcard][CardValue1];

                        if(g_CasinoCards[randcard][CardValue1] == 11)
                            PlayerBlackJack[playerid][HasAce][0] = true;

                        if(PlayerBlackJack[playerid][CardValue][0] > 21)
                        {
                            if(PlayerBlackJack[playerid][HasAce][0])
                            {
                                PlayerBlackJack[playerid][CardValue][0]-=10;
                                PlayerTextDrawSetString(playerid, BlackJackPTD[playerid][5], sprintf("%d", PlayerBlackJack[playerid][CardValue][0]));
                            }
                            else
                            {
                                HidePlayerBlackJackTD(playerid);

                                TextDrawHideForPlayer(playerid, BlackJackTD[0]);
                                TextDrawShowForPlayer(playerid, BlackJackTD[1]); //arrow ke NPC
                                TextDrawHideForPlayer(playerid, BlackJackTD[2]); 
                                PlayerBlackJack[playerid][Forbidden] = true;
                                PlayerTextDrawSetString(playerid, BlackJackPTD[playerid][5], "~r~BUST!");

                                PlayerPlayNearbySound(playerid, 5813);

                                ApplyAnimation(playerid,"CASINO", "Roulette_lose",4.1,false,false,false,false,0,true);

                                SetTimerEx("ContinueDrawCards", 1555, false, "id", playerid, id);
                            }
                        }
                        else
                        {
                            switch(PlayerBlackJack[playerid][CardValue][0])
                            {
                                case 4: {PlayerPlayNearbySound(playerid, 5841);}
                                case 5: {PlayerPlayNearbySound(playerid, 5842);}
                                case 6: {PlayerPlayNearbySound(playerid, 5843);}
                                case 7: {PlayerPlayNearbySound(playerid, 5844);}
                                case 8: {PlayerPlayNearbySound(playerid, 5845);}
                                case 9: {PlayerPlayNearbySound(playerid, 5846);}
                                case 10: {PlayerPlayNearbySound(playerid, 5829);}
                                case 11: {PlayerPlayNearbySound(playerid, 5830);}
                                case 12: 
                                {
                                    if(PlayerBlackJack[playerid][HasAce][0])
                                    {
                                        PlayerPlayNearbySound(playerid, 5801); //2 or 12
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5831); //12
                                    }
                                }
                                case 13: 
                                {
                                    if(PlayerBlackJack[playerid][HasAce][0])
                                    {
                                        PlayerPlayNearbySound(playerid, 5802); //3 or 13
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5832); //13
                                    }
                                }
                                case 14: 
                                {
                                    if(PlayerBlackJack[playerid][HasAce][0])
                                    {
                                        PlayerPlayNearbySound(playerid, 5803); //4 or 14
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5833); //13
                                    }
                                }
                                case 15: 
                                {
                                    if(PlayerBlackJack[playerid][HasAce][0])
                                    {
                                        PlayerPlayNearbySound(playerid, 5804); //5 or 15
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5834); //13
                                    }
                                }
                                case 16: 
                                {
                                    if(PlayerBlackJack[playerid][HasAce][0])
                                    {
                                        PlayerPlayNearbySound(playerid, 5805); //6 or 16
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5835); //13
                                    }
                                }
                                case 17: 
                                {
                                    if(PlayerBlackJack[playerid][HasAce][0])
                                    {
                                        PlayerPlayNearbySound(playerid, 5806); //7 or 17
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5836); //13
                                    }
                                }
                                case 18:
                                {
                                    if(PlayerBlackJack[playerid][HasAce][0])
                                    {
                                        PlayerPlayNearbySound(playerid, 5807); //8 or 18
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5837); //13
                                    }
                                }
                                case 19: 
                                {
                                    if(PlayerBlackJack[playerid][HasAce][0])
                                    {
                                        PlayerPlayNearbySound(playerid, 5808); //9 or 19
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5838); //13
                                    }
                                }
                                case 20: 
                                {
                                    if(PlayerBlackJack[playerid][HasAce][0])
                                    {
                                        PlayerPlayNearbySound(playerid, 5800); //10 or 20
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5839); //13
                                    }
                                }
                                case 21: {PlayerPlayNearbySound(playerid, 5840);}
                            }
                            if(PlayerBlackJack[playerid][HasAce][0])
                            {
                                PlayerTextDrawSetString(playerid, BlackJackPTD[playerid][5], sprintf("%d or %d", PlayerBlackJack[playerid][CardValue][0]-10, PlayerBlackJack[playerid][CardValue][0]));
                            }
                            else
                            {
                                PlayerTextDrawSetString(playerid, BlackJackPTD[playerid][5], sprintf("%d", PlayerBlackJack[playerid][CardValue][0]));
                            }
                        }
                    }
                    BJTable_ShuffleDeck(playerid, id);
                }
                else //jika kartu sudah mencapai 4 dalam status player masih bisa draw maka dilarang memberikan kartu melainkan diberhentikan
                {
                    if(PlayerBlackJack[playerid][pSplitCardsID] >= 4)
                    {
                        PlayerBlackJack[playerid][IsSelectSplitCard] = false;

                        TextDrawShowForPlayer(playerid, BlackJackTD[0]);
                        TextDrawHideForPlayer(playerid, BlackJackTD[1]);
                        TextDrawHideForPlayer(playerid, BlackJackTD[2]); //maka dialihkan ke kartu kiri
                    }

                    if(PlayerBlackJack[playerid][pCardsId] >= 4)
                    {
                        HidePlayerBlackJackTD(playerid);

                        TextDrawHideForPlayer(playerid, BlackJackTD[0]);
                        TextDrawShowForPlayer(playerid, BlackJackTD[1]);
                        TextDrawHideForPlayer(playerid, BlackJackTD[2]); //maka dialihkan ke kartu dealer

                        PlayerBlackJack[playerid][Forbidden] = true;

                        SetTimerEx("ContinueDrawCards", 1555, false, "id", playerid, id);
                    }

                    //kondisi barusan, kartu di split tapi tidak terjadi apa apa dan status isselected false
                }
            }
            else //jika player sudah dilarang nge-draw
            {
                if(PlayerBlackJack[playerid][DealerCardValue] < 17 && PlayerBlackJack[playerid][DealerCardsId] < 4) //jika kartu dealer kurang dari 17 atau belum berjumlah 4 maka wajib di draw
                {
                    if(PlayerBlackJack[playerid][DealerCardStillClosed]) //jika masih tertutup maka dibuka
                    {
                        new randcard = PlayerBlackJack[playerid][DealerClosedCard];
                        PlayerTextDrawSetString(playerid, DealerBJTD[playerid][PlayerBlackJack[playerid][DealerCardsId]], g_CasinoCards[randcard][CardModelID]);
                        PlayerTextDrawShow(playerid, DealerBJTD[playerid][PlayerBlackJack[playerid][DealerCardsId]]);
                        PlayerBlackJack[playerid][DealerCardValue] += g_CasinoCards[randcard][CardValue1];

                        PlayerBlackJack[playerid][DealerCardStillClosed] = false;

                        BJTable_ShuffleDeck(playerid, id);

                        if(g_CasinoCards[randcard][CardValue1] == 11)
                            PlayerBlackJack[playerid][DealerHasAce] = true;

                        if(PlayerBlackJack[playerid][DealerCardValue] > 21)
                        {
                            if(PlayerBlackJack[playerid][DealerHasAce])
                            {
                                PlayerBlackJack[playerid][DealerCardValue]-=10;
                                PlayerTextDrawSetString(playerid, DealerBJTD[playerid][5], sprintf("%d", PlayerBlackJack[playerid][DealerCardValue]));
                            }
                            else
                            {
                                PlayerTextDrawSetString(playerid, DealerBJTD[playerid][5], "~r~BUST!");
                            }
                        }
                        else
                        {
                            switch(PlayerBlackJack[playerid][DealerCardValue])
                            {
                                case 4: {PlayerPlayNearbySound(playerid, 5841);}
                                case 5: {PlayerPlayNearbySound(playerid, 5842);}
                                case 6: {PlayerPlayNearbySound(playerid, 5843);}
                                case 7: {PlayerPlayNearbySound(playerid, 5844);}
                                case 8: {PlayerPlayNearbySound(playerid, 5845);}
                                case 9: {PlayerPlayNearbySound(playerid, 5846);}
                                case 10: {PlayerPlayNearbySound(playerid, 5829);}
                                case 11: {PlayerPlayNearbySound(playerid, 5830);}
                                case 12: 
                                {
                                    if(PlayerBlackJack[playerid][DealerHasAce])
                                    {
                                        PlayerPlayNearbySound(playerid, 5801); //2 or 12
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5831); //12
                                    }
                                }
                                case 13: 
                                {
                                    if(PlayerBlackJack[playerid][DealerHasAce])
                                    {
                                        PlayerPlayNearbySound(playerid, 5802); //3 or 13
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5832); //13
                                    }
                                }
                                case 14: 
                                {
                                    if(PlayerBlackJack[playerid][DealerHasAce])
                                    {
                                        PlayerPlayNearbySound(playerid, 5803); //4 or 14
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5833); //13
                                    }
                                }
                                case 15: 
                                {
                                    if(PlayerBlackJack[playerid][DealerHasAce])
                                    {
                                        PlayerPlayNearbySound(playerid, 5804); //5 or 15
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5834); //13
                                    }
                                }
                                case 16: 
                                {
                                    if(PlayerBlackJack[playerid][DealerHasAce])
                                    {
                                        PlayerPlayNearbySound(playerid, 5805); //6 or 16
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5835); //13
                                    }
                                }
                                case 17: 
                                {
                                    if(PlayerBlackJack[playerid][DealerHasAce])
                                    {
                                        PlayerPlayNearbySound(playerid, 5806); //7 or 17
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5836); //13
                                    }
                                }
                                case 18:
                                {
                                    if(PlayerBlackJack[playerid][DealerHasAce])
                                    {
                                        PlayerPlayNearbySound(playerid, 5807); //8 or 18
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5837); //13
                                    }
                                }
                                case 19: 
                                {
                                    if(PlayerBlackJack[playerid][DealerHasAce])
                                    {
                                        PlayerPlayNearbySound(playerid, 5808); //9 or 19
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5838); //13
                                    }
                                }
                                case 20: 
                                {
                                    if(PlayerBlackJack[playerid][DealerHasAce])
                                    {
                                        PlayerPlayNearbySound(playerid, 5800); //10 or 20
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5839); //13
                                    }
                                }
                                case 21: {PlayerPlayNearbySound(playerid, 5840);}
                            }

                            if(PlayerBlackJack[playerid][DealerHasAce])
                            {
                                PlayerTextDrawSetString(playerid, DealerBJTD[playerid][5], sprintf("%d or %d", PlayerBlackJack[playerid][DealerCardValue]-10, PlayerBlackJack[playerid][DealerCardValue]));
                            }
                            else
                            {
                                PlayerTextDrawSetString(playerid, DealerBJTD[playerid][5], sprintf("%d", PlayerBlackJack[playerid][DealerCardValue]));
                            }
                            
                            //jika dealer blackjack di 2 kartu awal DAN PLAYER TIDAK MENGAMBIL INSURANCE maka permainan berakhir
                            if(PlayerBlackJack[playerid][DealerHasAce] && PlayerBlackJack[playerid][DealerCardValue] == 21 && PlayerBlackJack[playerid][DealerCardsId] == 1)
                            {
                                PlayerBlackJack[playerid][DealerBlackJack] = true;
                                PlayerPlayNearbySound(playerid, 5811);
                                GameTextForPlayer(playerid, "~y~BLACKJACK!", 3500, 6);
                                
                                AccountData[playerid][pCasinoChip] -= PlayerBlackJack[playerid][Bet][0];
                                SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"The dealer has blackjack, so you lose. You have lost your "RED"$%s", FormatMoney(PlayerBlackJack[playerid][Bet][0]));

                                SetTimerEx("NextRoundPrepare", 5555, false, "i", playerid);
                                return 1;
                            }
                        }
                    }
                    else //jika kartu kedua sudah terbuka lanjut kartu ketiga
                    {
                        new randcard = Iter_Random(CardsUsed[id]);
                        Iter_Remove(CardsUsed[id],randcard);

                        PlayerBlackJack[playerid][DealerCardsId]++;
                        ApplyDynamicActorAnimation(BlackJackTable[id][BJActor], "CASINO", "dealone", 4.1, false, false, false, false, 0);

                        PlayerTextDrawSetString(playerid, DealerBJTD[playerid][PlayerBlackJack[playerid][DealerCardsId]], g_CasinoCards[randcard][CardModelID]);
                        PlayerTextDrawShow(playerid, DealerBJTD[playerid][PlayerBlackJack[playerid][DealerCardsId]]);
                        PlayerBlackJack[playerid][DealerCardValue] += g_CasinoCards[randcard][CardValue1];

                        BJTable_ShuffleDeck(playerid, id);

                        if(g_CasinoCards[randcard][CardValue1] == 11)
                            PlayerBlackJack[playerid][DealerHasAce] = true;

                        if(PlayerBlackJack[playerid][DealerCardValue] > 21)
                        {
                            if(PlayerBlackJack[playerid][DealerHasAce])
                            {
                                PlayerBlackJack[playerid][DealerCardValue]-=10;
                                PlayerTextDrawSetString(playerid, DealerBJTD[playerid][5], sprintf("%d", PlayerBlackJack[playerid][DealerCardValue]));
                            }
                            else
                            {
                                PlayerTextDrawSetString(playerid, DealerBJTD[playerid][5], "~r~BUST!");
                            }
                        }
                        else
                        {
                            switch(PlayerBlackJack[playerid][DealerCardValue])
                            {
                                case 4: {PlayerPlayNearbySound(playerid, 5841);}
                                case 5: {PlayerPlayNearbySound(playerid, 5842);}
                                case 6: {PlayerPlayNearbySound(playerid, 5843);}
                                case 7: {PlayerPlayNearbySound(playerid, 5844);}
                                case 8: {PlayerPlayNearbySound(playerid, 5845);}
                                case 9: {PlayerPlayNearbySound(playerid, 5846);}
                                case 10: {PlayerPlayNearbySound(playerid, 5829);}
                                case 11: {PlayerPlayNearbySound(playerid, 5830);}
                                case 12: 
                                {
                                    if(PlayerBlackJack[playerid][DealerHasAce])
                                    {
                                        PlayerPlayNearbySound(playerid, 5801); //2 or 12
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5831); //12
                                    }
                                }
                                case 13: 
                                {
                                    if(PlayerBlackJack[playerid][DealerHasAce])
                                    {
                                        PlayerPlayNearbySound(playerid, 5802); //3 or 13
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5832); //13
                                    }
                                }
                                case 14: 
                                {
                                    if(PlayerBlackJack[playerid][DealerHasAce])
                                    {
                                        PlayerPlayNearbySound(playerid, 5803); //4 or 14
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5833); //13
                                    }
                                }
                                case 15: 
                                {
                                    if(PlayerBlackJack[playerid][DealerHasAce])
                                    {
                                        PlayerPlayNearbySound(playerid, 5804); //5 or 15
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5834); //13
                                    }
                                }
                                case 16: 
                                {
                                    if(PlayerBlackJack[playerid][DealerHasAce])
                                    {
                                        PlayerPlayNearbySound(playerid, 5805); //6 or 16
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5835); //13
                                    }
                                }
                                case 17: 
                                {
                                    if(PlayerBlackJack[playerid][DealerHasAce])
                                    {
                                        PlayerPlayNearbySound(playerid, 5806); //7 or 17
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5836); //13
                                    }
                                }
                                case 18:
                                {
                                    if(PlayerBlackJack[playerid][DealerHasAce])
                                    {
                                        PlayerPlayNearbySound(playerid, 5807); //8 or 18
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5837); //13
                                    }
                                }
                                case 19: 
                                {
                                    if(PlayerBlackJack[playerid][DealerHasAce])
                                    {
                                        PlayerPlayNearbySound(playerid, 5808); //9 or 19
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5838); //13
                                    }
                                }
                                case 20: 
                                {
                                    if(PlayerBlackJack[playerid][DealerHasAce])
                                    {
                                        PlayerPlayNearbySound(playerid, 5800); //10 or 20
                                    }
                                    else
                                    {
                                        PlayerPlayNearbySound(playerid, 5839); //13
                                    }
                                }
                                case 21: {PlayerPlayNearbySound(playerid, 5840);}
                            }

                            if(PlayerBlackJack[playerid][DealerHasAce])
                            {
                                PlayerTextDrawSetString(playerid, DealerBJTD[playerid][5], sprintf("%d or %d", PlayerBlackJack[playerid][DealerCardValue]-10, PlayerBlackJack[playerid][DealerCardValue]));
                            }
                            else
                            {
                                PlayerTextDrawSetString(playerid, DealerBJTD[playerid][5], sprintf("%d", PlayerBlackJack[playerid][DealerCardValue]));
                            }
                        }
                    }
                    SetTimerEx("ContinueDrawCards", 1555, false, "id", playerid, id);
                    return 1;
                }
                if(PlayerBlackJack[playerid][DealerCardValue] > 21) //jika dealer mengalami bust
                {
                    if(PlayerBlackJack[playerid][Splited]) //jika dalam split
                    {
                        if(PlayerBlackJack[playerid][CardValue][1] > 21) //jika sama-sama bust di kartu kanan
                        {
                            PlayerPlayNearbySound(playerid, 5817);
            
                            if(PlayerBlackJack[playerid][DoubleTaken][1])
                            {
                                AccountData[playerid][pCasinoChip] -= floatround(PlayerBlackJack[playerid][Bet][1]*2);
                                SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You have lost your double bet on your "YELLOW"second card "WHITE"for "RED"$%s", FormatMoney(PlayerBlackJack[playerid][Bet][1]*2));
                            }
                            else
                            {
                                AccountData[playerid][pCasinoChip] -= PlayerBlackJack[playerid][Bet][1];
                                SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You have lost your bet on your "YELLOW"second card "WHITE"for "RED"$%s", FormatMoney(PlayerBlackJack[playerid][Bet][1]));
                            }
                            GameTextForPlayer(playerid, "~r~BUST!", 3500, 6);

                            ApplyAnimation(playerid,"CASINO", "Roulette_lose",4.1,false,false,false,false,0,true);
                        }
                        else //jika player tidak bust
                        {
                            if(PlayerBlackJack[playerid][BlackJack] && PlayerBlackJack[playerid][CardValue][1] == 21) //jika player blackjack di kartu kanan
                            {
                                PlayerPlayNearbySound(playerid, 5812);
                                new Float:GrandCash = PlayerBlackJack[playerid][Bet][1] * 2.5;
                                SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You win for your blackjack on "YELLOW"second card, "WHITE"congratulations for "GREEN"$%s", FormatMoney(floatround(GrandCash)));
                                GameTextForPlayer(playerid, "~y~BLACKJACK!", 3500, 6);
                                AccountData[playerid][pCasinoChip] += floatround(GrandCash);

                                ApplyAnimation(playerid,"CASINO", "manwind",4.1,false,false,false,false,0,true);
                            }
                            else //jika non-blackjack
                            {
                                if(PlayerBlackJack[playerid][DoubleTaken][1])
                                {
                                    PlayerPlayNearbySound(playerid, 5849);
                                    
                                    new Float:GrandCash = PlayerBlackJack[playerid][Bet][1] * 3;
                                    AccountData[playerid][pCasinoChip] += floatround(GrandCash);
                                    SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"Very well double on your "YELLOW"second card, "WHITE"congratulations for "GREEN"$%s", FormatMoney(floatround(GrandCash)));
                                }
                                else
                                {
                                    PlayerPlayNearbySound(playerid, 5848);

                                    new Float:GrandCash = PlayerBlackJack[playerid][Bet][1] * 2;
                                    AccountData[playerid][pCasinoChip] += floatround(GrandCash);
                                    SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You win on your "YELLOW"second card, "WHITE"congratulations for "GREEN"$%s", FormatMoney(floatround(GrandCash)));
                                }
                                GameTextForPlayer(playerid, "~g~WIN!", 3500, 6);

                                ApplyAnimation(playerid,"CASINO", "manwind",4.1,false,false,false,false,0,true);
                            }
                        }

                        if(PlayerBlackJack[playerid][CardValue][0] > 21) //jika sama-sama bust di kartu kiri
                        {
                            PlayerPlayNearbySound(playerid, 5817);
            
                            if(PlayerBlackJack[playerid][DoubleTaken][0])
                            {
                                AccountData[playerid][pCasinoChip] -= floatround(PlayerBlackJack[playerid][Bet][0]*2);
                                SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You have lost your double bet on your "YELLOW"first card "WHITE"for "RED"$%s", FormatMoney(PlayerBlackJack[playerid][Bet][0]*2));
                            }
                            else
                            {
                                AccountData[playerid][pCasinoChip] -= PlayerBlackJack[playerid][Bet][0];
                                SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You have lost your bet on your "YELLOW"first card "WHITE"for "RED"$%s", FormatMoney(PlayerBlackJack[playerid][Bet][0]));
                            }
                            GameTextForPlayer(playerid, "~r~BUST!", 3500, 6);

                            ApplyAnimation(playerid,"CASINO", "Roulette_lose",4.1,false,false,false,false,0,true);
                        }
                        else //jika player tidak bust
                        {
                            if(PlayerBlackJack[playerid][BlackJack] && PlayerBlackJack[playerid][CardValue][0] == 21) //jika player blackjack
                            {
                                PlayerPlayNearbySound(playerid, 5812);
                                new Float:GrandCash = PlayerBlackJack[playerid][Bet][0] * 2.5;
                                SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You win for your blackjack on "YELLOW"first card, "WHITE"congratulations for "GREEN"$%s", FormatMoney(floatround(GrandCash)));
                                GameTextForPlayer(playerid, "~y~BLACKJACK!", 3500, 6);
                                AccountData[playerid][pCasinoChip] += floatround(GrandCash);

                                ApplyAnimation(playerid,"CASINO", "manwind",4.1,false,false,false,false,0,true);
                            }
                            else //jika non-blackjack
                            {
                                if(PlayerBlackJack[playerid][DoubleTaken][0])
                                {
                                    PlayerPlayNearbySound(playerid, 5849);

                                    new Float:GrandCash = PlayerBlackJack[playerid][Bet][0] * 3;
                                    AccountData[playerid][pCasinoChip] += floatround(GrandCash);
                                    SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"Very well double on your "YELLOW"first card, "WHITE"congratulations for "GREEN"$%s", FormatMoney(floatround(GrandCash)));
                                }
                                else
                                {
                                    PlayerPlayNearbySound(playerid, 5848);

                                    new Float:GrandCash = PlayerBlackJack[playerid][Bet][0] * 2;
                                    AccountData[playerid][pCasinoChip] += floatround(GrandCash);
                                    SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You win on your "YELLOW"first card, "WHITE"congratulations for "GREEN"$%s", FormatMoney(floatround(GrandCash)));
                                }
                                GameTextForPlayer(playerid, "~g~WIN!", 3500, 6);

                                ApplyAnimation(playerid,"CASINO", "manwind",4.1,false,false,false,false,0,true);
                            }
                        }
                    }
                    else //jika tidak split
                    {
                        if(PlayerBlackJack[playerid][CardValue][0] > 21) //jika sama-sama bust
                        {
                            PlayerPlayNearbySound(playerid, 5817);
            
                            if(PlayerBlackJack[playerid][DoubleTaken][0])
                            {
                                AccountData[playerid][pCasinoChip] -= floatround(PlayerBlackJack[playerid][Bet][0]*2);
                                SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"Bad double strategy, you have lost your "RED"$%s", FormatMoney(PlayerBlackJack[playerid][Bet][0]*2));
                            }
                            else
                            {
                                AccountData[playerid][pCasinoChip] -= PlayerBlackJack[playerid][Bet][0];
                                SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You lose, you have lost your "RED"$%s", FormatMoney(PlayerBlackJack[playerid][Bet][0]));
                            }
                            GameTextForPlayer(playerid, "~r~BUST!", 3500, 6);

                            ApplyAnimation(playerid,"CASINO", "Roulette_lose",4.1,false,false,false,false,0,true);
                        }
                        else //jika player tidak bust
                        {
                            if(PlayerBlackJack[playerid][BlackJack] && PlayerBlackJack[playerid][CardValue][0] == 21) //jika player blackjack
                            {
                                PlayerPlayNearbySound(playerid, 5812);
                                new Float:GrandCash = PlayerBlackJack[playerid][Bet][0] * 2.5;
                                SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You win for your blackjack, "WHITE"congratulations for "GREEN"$%s", FormatMoney(floatround(GrandCash)));
                                GameTextForPlayer(playerid, "~y~BLACKJACK!", 3500, 6);
                                AccountData[playerid][pCasinoChip] += floatround(GrandCash);

                                ApplyAnimation(playerid,"CASINO", "manwind",4.1,false,false,false,false,0,true);
                            }
                            else //jika non-blackjack
                            {
                                if(PlayerBlackJack[playerid][DoubleTaken][0])
                                {
                                    PlayerPlayNearbySound(playerid, 5849);

                                    new Float:GrandCash = PlayerBlackJack[playerid][Bet][0] * 3;
                                    AccountData[playerid][pCasinoChip] += floatround(GrandCash);
                                    SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"Very well double, congratulations for "GREEN"$%s", FormatMoney(floatround(GrandCash)));
                                }
                                else
                                {
                                    PlayerPlayNearbySound(playerid, 5848);

                                    new Float:GrandCash = PlayerBlackJack[playerid][Bet][0] * 2;
                                    AccountData[playerid][pCasinoChip] += floatround(GrandCash);
                                    SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You win, congratulations for "GREEN"$%s", FormatMoney(floatround(GrandCash)));
                                }
                                GameTextForPlayer(playerid, "~g~WIN!", 3500, 6);

                                ApplyAnimation(playerid,"CASINO", "manwind",4.1,false,false,false,false,0,true);
                            }
                        }
                    }

                    SetTimerEx("NextRoundPrepare", 5555, false, "i", playerid);
                }
                else //dealer tidak bust
                {
                    if(PlayerBlackJack[playerid][DealerCardValue] >= 17 || PlayerBlackJack[playerid][DealerCardsId] >= 4) //dicek apakah kartu nilai 17 atau jumlah 5 secara index 4
                    {
                        if(PlayerBlackJack[playerid][Splited])
                        {
                            if(PlayerBlackJack[playerid][CardValue][1] == PlayerBlackJack[playerid][DealerCardValue]) //jika nilai sama value nya pada kartu paling kanan
                            {
                                if(PlayerBlackJack[playerid][BlackJack] && PlayerBlackJack[playerid][CardValue][1] == 21) //jika player blackjack
                                {
                                    PlayerPlayNearbySound(playerid, 5812);
                                    new Float:GrandCash = PlayerBlackJack[playerid][Bet][1] * 2.5;
                                    SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You win for your blackjack on "YELLOW"second card, "WHITE"congratulations for "GREEN"$%s", FormatMoney(floatround(GrandCash)));
                                    GameTextForPlayer(playerid, "~y~BLACKJACK!", 3500, 6);
                                    AccountData[playerid][pCasinoChip] += floatround(GrandCash);
                                    ApplyAnimation(playerid,"CASINO", "manwind",4.1,false,false,false,false,0,true);
                                }
                                else //jika non-blackjack maka dianggap PUSH / SERI
                                {
                                    PlayerPlayNearbySound(playerid, 5815);
                                    SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"We have draw with your second card, so you got back your bet "GREEN"$%s", FormatMoney(PlayerBlackJack[playerid][Bet][1]));
                                    GameTextForPlayer(playerid, "~b~PUSH!", 3500, 6);
                                    AccountData[playerid][pCasinoChip] += PlayerBlackJack[playerid][Bet][1];
                                    ApplyAnimation(playerid,"CASINO", "manwind",4.1,false,false,false,false,0,true);
                                }
                            }
                            else //jika nilai tidak sama
                            {
                                if(PlayerBlackJack[playerid][BlackJack] && PlayerBlackJack[playerid][CardValue][1] == 21) //jika player blackjack
                                {
                                    PlayerPlayNearbySound(playerid, 5812);
                                    new Float:GrandCash = PlayerBlackJack[playerid][Bet][1] * 2.5;
                                    SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You win for your blackjack on "YELLOW"second card card, "WHITE"congratulations for "GREEN"$%s", FormatMoney(floatround(GrandCash)));
                                    GameTextForPlayer(playerid, "~y~BLACKJACK!", 3500, 6);
                                    AccountData[playerid][pCasinoChip] += floatround(GrandCash);
                                    ApplyAnimation(playerid,"CASINO", "manwind",4.1,false,false,false,false,0,true);
                                }
                                else //jika non-blackjack
                                {
                                    if(PlayerBlackJack[playerid][CardValue][1] > 21) //jika player bust
                                    {
                                        PlayerPlayNearbySound(playerid, 5814);

                                        if(PlayerBlackJack[playerid][DoubleTaken][1])
                                        {
                                            AccountData[playerid][pCasinoChip] -= floatround(PlayerBlackJack[playerid][Bet][1]*2);
                                            SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You have lost your double bet on your "YELLOW"second card "WHITE"for "RED"$%s", FormatMoney(PlayerBlackJack[playerid][Bet][1]*2));
                                        }
                                        else
                                        {
                                            AccountData[playerid][pCasinoChip] -= PlayerBlackJack[playerid][Bet][1];
                                            SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You have lost your bet on your "YELLOW"second card "WHITE"for "RED"$%s", FormatMoney(PlayerBlackJack[playerid][Bet][1]));
                                        }
                                        GameTextForPlayer(playerid, "~r~BUST!", 3500, 6);
                                        ApplyAnimation(playerid,"CASINO", "Roulette_lose",4.1,false,false,false,false,0,true);
                                    }
                                    else //jika tidak bust
                                    {
                                        if(PlayerBlackJack[playerid][CardValue][1] > PlayerBlackJack[playerid][DealerCardValue]) //jika nilai player lebih dari dealer
                                        {
                                            if(PlayerBlackJack[playerid][DoubleTaken][1])
                                            {
                                                PlayerPlayNearbySound(playerid, 5855);

                                                new Float:GrandCash = PlayerBlackJack[playerid][Bet][1] * 3;
                                                AccountData[playerid][pCasinoChip] += floatround(GrandCash);
                                                SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"Very well double on your "YELLOW"second card, "WHITE"congratulations for "GREEN"$%s", FormatMoney(floatround(GrandCash)));
                                            }
                                            else
                                            {
                                                PlayerPlayNearbySound(playerid, 5847);

                                                new Float:GrandCash = PlayerBlackJack[playerid][Bet][1] * 2;
                                                AccountData[playerid][pCasinoChip] += floatround(GrandCash);
                                                SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You win on your "YELLOW"second card, "WHITE"congratulations for "GREEN"$%s", FormatMoney(floatround(GrandCash)));
                                            }
                                            GameTextForPlayer(playerid, "~g~WIN!", 3500, 6);
                                            ApplyAnimation(playerid,"CASINO", "manwind",4.1,false,false,false,false,0,true);
                                        }
                                        else //jika nilai dealer lebih dari player
                                        {
                                            PlayerPlayNearbySound(playerid, 5818);
                                            if(PlayerBlackJack[playerid][DoubleTaken][1])
                                            {
                                                AccountData[playerid][pCasinoChip] -= floatround(PlayerBlackJack[playerid][Bet][1] * 2);
                                                SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You have lost your double bet on your "YELLOW"second card "WHITE"for "RED"$%s", FormatMoney(PlayerBlackJack[playerid][Bet][1]*2));
                                            }
                                            else
                                            {
                                                AccountData[playerid][pCasinoChip] -= PlayerBlackJack[playerid][Bet][1];
                                                SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You have lost your bet on your "YELLOW"second card "WHITE"for "RED"$%s", FormatMoney(PlayerBlackJack[playerid][Bet][1]));
                                            }
                                            GameTextForPlayer(playerid, "~r~LOSE!", 3500, 6);
                                            ApplyAnimation(playerid,"CASINO", "Roulette_lose",4.1,false,false,false,false,0,true);
                                        }
                                    }
                                }
                            }
                            if(PlayerBlackJack[playerid][CardValue][0] == PlayerBlackJack[playerid][DealerCardValue]) //jika nilai sama value nya pada kartu paling kiri
                            {
                                if(PlayerBlackJack[playerid][BlackJack] && PlayerBlackJack[playerid][CardValue][0] == 21) //jika player blackjack
                                {
                                    PlayerPlayNearbySound(playerid, 5812);
                                    new Float:GrandCash = PlayerBlackJack[playerid][Bet][0] * 2.5;
                                    SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You win for your blackjack on "YELLOW"first card, "WHITE"congratulations for "GREEN"$%s", FormatMoney(floatround(GrandCash)));
                                    GameTextForPlayer(playerid, "~y~BLACKJACK!", 3500, 6);
                                    AccountData[playerid][pCasinoChip] += floatround(GrandCash);
                                    ApplyAnimation(playerid,"CASINO", "manwind",4.1,false,false,false,false,0,true);
                                }
                                else //jika non-blackjack maka dianggap PUSH / SERI
                                {
                                    PlayerPlayNearbySound(playerid, 5815);
                                    SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"We have draw with your first card, so you got back your bet "GREEN"$%s", FormatMoney(PlayerBlackJack[playerid][Bet][0]));
                                    GameTextForPlayer(playerid, "~b~PUSH!", 3500, 6);
                                    ApplyAnimation(playerid,"CASINO", "manwind",4.1,false,false,false,false,0,true);
                                }
                            }
                            else //jika nilai tidak sama
                            {
                                if(PlayerBlackJack[playerid][BlackJack] && PlayerBlackJack[playerid][CardValue][0] == 21) //jika player blackjack
                                {
                                    PlayerPlayNearbySound(playerid, 5812);
                                    new Float:GrandCash = PlayerBlackJack[playerid][Bet][0] * 2.5;
                                    SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You win for your blackjack on "YELLOW"first card card, "WHITE"congratulations for "GREEN"$%s", FormatMoney(floatround(GrandCash)));
                                    GameTextForPlayer(playerid, "~y~BLACKJACK!", 3500, 6);
                                    AccountData[playerid][pCasinoChip] += floatround(GrandCash);
                                    ApplyAnimation(playerid,"CASINO", "manwind",4.1,false,false,false,false,0,true);
                                }
                                else //jika non-blackjack
                                {
                                    if(PlayerBlackJack[playerid][CardValue][0] > 21) //jika player bust
                                    {
                                        PlayerPlayNearbySound(playerid, 5814);

                                        if(PlayerBlackJack[playerid][DoubleTaken][0])
                                        {
                                            AccountData[playerid][pCasinoChip] -= floatround(PlayerBlackJack[playerid][Bet][0]*2);
                                            SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You have lost your double bet on your "YELLOW"first card "WHITE"for "RED"$%s", FormatMoney(PlayerBlackJack[playerid][Bet][0]*2));
                                        }
                                        else
                                        {
                                            AccountData[playerid][pCasinoChip] -= PlayerBlackJack[playerid][Bet][0];
                                            SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You have lost your bet on your "YELLOW"first card "WHITE"for "RED"$%s", FormatMoney(PlayerBlackJack[playerid][Bet][0]));
                                        }
                                        GameTextForPlayer(playerid, "~r~BUST!", 3500, 6);
                                        ApplyAnimation(playerid,"CASINO", "Roulette_lose",4.1,false,false,false,false,0,true);
                                    }
                                    else //jika tidak bust
                                    {
                                        if(PlayerBlackJack[playerid][CardValue][0] > PlayerBlackJack[playerid][DealerCardValue]) //jika nilai player lebih dari dealer
                                        {
                                            if(PlayerBlackJack[playerid][DoubleTaken][0])
                                            {
                                                PlayerPlayNearbySound(playerid, 5855);

                                                new Float:GrandCash = PlayerBlackJack[playerid][Bet][0] * 3;
                                                AccountData[playerid][pCasinoChip] += floatround(GrandCash);
                                                SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"Very well double on your "YELLOW"first card, "WHITE"congratulations for "GREEN"$%s", FormatMoney(floatround(GrandCash)));
                                            }
                                            else
                                            {
                                                PlayerPlayNearbySound(playerid, 5847);

                                                new Float:GrandCash = PlayerBlackJack[playerid][Bet][0] * 2;
                                                AccountData[playerid][pCasinoChip] += floatround(GrandCash);
                                                SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You win on your "YELLOW"first card, "WHITE"congratulations for "GREEN"$%s", FormatMoney(floatround(GrandCash)));
                                            }
                                            GameTextForPlayer(playerid, "~g~WIN!", 3500, 6);
                                            ApplyAnimation(playerid,"CASINO", "manwind",4.1,false,false,false,false,0,true);
                                        }
                                        else //jika nilai dealer lebih dari player
                                        {
                                            PlayerPlayNearbySound(playerid, 5818);
                                            if(PlayerBlackJack[playerid][DoubleTaken][0])
                                            {
                                                AccountData[playerid][pCasinoChip] -= floatround(PlayerBlackJack[playerid][Bet][0] * 2);
                                                SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You have lost your double bet on your "YELLOW"first card "WHITE"for "RED"$%s", FormatMoney(PlayerBlackJack[playerid][Bet][0]*2));
                                            }
                                            else
                                            {
                                                AccountData[playerid][pCasinoChip] -= PlayerBlackJack[playerid][Bet][0];
                                                SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You have lost your bet on your "YELLOW"first card "WHITE"for "RED"$%s", FormatMoney(PlayerBlackJack[playerid][Bet][0]));
                                            }
                                            GameTextForPlayer(playerid, "~r~LOSE!", 3500, 6);
                                            ApplyAnimation(playerid,"CASINO", "Roulette_lose",4.1,false,false,false,false,0,true);
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            if(PlayerBlackJack[playerid][CardValue][0] == PlayerBlackJack[playerid][DealerCardValue]) //jika nilai sama value nya TANPA SPLIT
                            {
                                if(PlayerBlackJack[playerid][BlackJack] && PlayerBlackJack[playerid][CardValue][0] == 21) //jika player blackjack
                                {
                                    PlayerPlayNearbySound(playerid, 5812);
                                    new Float:GrandCash = PlayerBlackJack[playerid][Bet][0] * 2.5;
                                    SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You win, congratulations for "GREEN"$%s", FormatMoney(floatround(GrandCash)));
                                    GameTextForPlayer(playerid, "~y~BLACKJACK!", 3500, 6);
                                    AccountData[playerid][pCasinoChip] += floatround(GrandCash);
                                    ApplyAnimation(playerid,"CASINO", "manwind",4.1,false,false,false,false,0,true);
                                }
                                else //jika non-blackjack maka dianggap PUSH / SERI
                                {
                                    PlayerPlayNearbySound(playerid, 5815);
                                    SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"We have draw here, so you got back your bet "GREEN"$%s", FormatMoney(PlayerBlackJack[playerid][Bet][0]));
                                    GameTextForPlayer(playerid, "~b~PUSH!", 3500, 6);
                                    ApplyAnimation(playerid,"CASINO", "manwind",4.1,false,false,false,false,0,true);
                                }
                            }
                            else //jika nilai tidak sama
                            {
                                if(PlayerBlackJack[playerid][BlackJack] && PlayerBlackJack[playerid][CardValue][0] == 21) //jika player blackjack
                                {
                                    PlayerPlayNearbySound(playerid, 5812);
                                    new Float:GrandCash = PlayerBlackJack[playerid][Bet][0] * 2.5;
                                    SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You win, congratulations for "GREEN"$%s", FormatMoney(floatround(GrandCash)));
                                    GameTextForPlayer(playerid, "~y~BLACKJACK!", 3500, 6);
                                    AccountData[playerid][pCasinoChip] += floatround(GrandCash);
                                    ApplyAnimation(playerid,"CASINO", "manwind",4.1,false,false,false,false,0,true);
                                }
                                else //jika non-blackjack
                                {
                                    if(PlayerBlackJack[playerid][CardValue][0] > 21) //jika player bust
                                    {
                                        PlayerPlayNearbySound(playerid, 5814);

                                        if(PlayerBlackJack[playerid][DoubleTaken][0])
                                        {
                                            AccountData[playerid][pCasinoChip] -= floatround(PlayerBlackJack[playerid][Bet][0]*2);
                                            SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"Bad double strategy, you have lost your "RED"$%s", FormatMoney(PlayerBlackJack[playerid][Bet][0]*2));
                                        }
                                        else
                                        {
                                            AccountData[playerid][pCasinoChip] -= PlayerBlackJack[playerid][Bet][0];
                                            SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You lose, you have lost your "RED"$%s", FormatMoney(PlayerBlackJack[playerid][Bet][0]));
                                        }
                                        GameTextForPlayer(playerid, "~r~BUST!", 3500, 6);
                                        ApplyAnimation(playerid,"CASINO", "Roulette_lose",4.1,false,false,false,false,0,true);
                                    }
                                    else //jika tidak bust
                                    {
                                        if(PlayerBlackJack[playerid][CardValue][0] > PlayerBlackJack[playerid][DealerCardValue]) //jika nilai player lebih dari dealer
                                        {
                                            if(PlayerBlackJack[playerid][DoubleTaken][0])
                                            {
                                                PlayerPlayNearbySound(playerid, 5855);

                                                new Float:GrandCash = PlayerBlackJack[playerid][Bet][0] * 3;
                                                AccountData[playerid][pCasinoChip] += floatround(GrandCash);
                                                SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"Very well double, congratulations for "GREEN"$%s", FormatMoney(floatround(GrandCash)));
                                            }
                                            else
                                            {
                                                PlayerPlayNearbySound(playerid, 5847);

                                                new Float:GrandCash = PlayerBlackJack[playerid][Bet][0] * 2;
                                                AccountData[playerid][pCasinoChip] += floatround(GrandCash);
                                                SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You win, congratulations for "GREEN"$%s", FormatMoney(floatround(GrandCash)));
                                            }
                                            GameTextForPlayer(playerid, "~g~WIN!", 3500, 6);
                                            ApplyAnimation(playerid,"CASINO", "manwind",4.1,false,false,false,false,0,true);
                                        }
                                        else //jika nilai dealer lebih dari player
                                        {
                                            PlayerPlayNearbySound(playerid, 5818);
                                            if(PlayerBlackJack[playerid][DoubleTaken][0])
                                            {
                                                AccountData[playerid][pCasinoChip] -= floatround(PlayerBlackJack[playerid][Bet][0] * 2);
                                                SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"Bad double strategy, you have lost your "RED"$%s", FormatMoney(PlayerBlackJack[playerid][Bet][0]*2));
                                            }
                                            else
                                            {
                                                AccountData[playerid][pCasinoChip] -= PlayerBlackJack[playerid][Bet][0];
                                                SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You lose, you have lost your "RED"$%s", FormatMoney(PlayerBlackJack[playerid][Bet][0]));
                                            }
                                            GameTextForPlayer(playerid, "~r~LOSE!", 3500, 6);
                                            ApplyAnimation(playerid,"CASINO", "Roulette_lose",4.1,false,false,false,false,0,true);
                                        }
                                    }
                                }
                            }
                        }
                        SetTimerEx("NextRoundPrepare", 5555, false, "i", playerid);
                    }
                }
            }
        }
    }
    return 1;
}

forward CheckingForBlackjack(playerid, id);
public CheckingForBlackjack(playerid, id)
{
    if(!IsPlayerConnected(playerid)) return 1;
    if(!AccountData[playerid][pSpawned]) return 1;
    if(!PlayerBlackJack[playerid][Seated]) return 1;

    new randcard = PlayerBlackJack[playerid][DealerClosedCard];
    ApplyDynamicActorAnimation(BlackJackTable[id][BJActor], "CASINO", "dealone", 4.1, false, false, false, false, 0);

    if(g_CasinoCards[randcard][CardValue1] == 11) //jika dapat AS maka blackjack
    {
        PlayerBlackJack[playerid][DealerCardStillClosed] = false;
        PlayerBlackJack[playerid][DealerBlackJack] = true;
        PlayerPlayNearbySound(playerid, 5811);

        PlayerTextDrawSetString(playerid, DealerBJTD[playerid][PlayerBlackJack[playerid][DealerCardsId]], g_CasinoCards[randcard][CardModelID]);
        PlayerTextDrawShow(playerid, DealerBJTD[playerid][PlayerBlackJack[playerid][DealerCardsId]]);
        GameTextForPlayer(playerid, "~y~BLACKJACK!", 3500, 6);
        
        AccountData[playerid][pCasinoChip] -= PlayerBlackJack[playerid][Bet][0];
        SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"The dealer has blackjack, so you lose. You have lost your "RED"$%s", FormatMoney(PlayerBlackJack[playerid][Bet][0]));

        SetTimerEx("NextRoundPrepare", 5555, false, "i", playerid);
    }
    else //jika tidak
    {
        SendClientMessage(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"Feel free to continue your turn.");
        ShowPlayerBlackJackTD(playerid);
        if(BJTable_Splitable(playerid))
        {
            TextDrawShowForPlayer(playerid, BlackJackTD[7]);
        }
    }
    return 1;
}

forward InsuranceResultan(playerid, id);
public InsuranceResultan(playerid, id)
{
    if(!IsPlayerConnected(playerid)) return 1;
    if(!AccountData[playerid][pSpawned]) return 1;
    if(!PlayerBlackJack[playerid][Seated]) return 1;

    new randcard = PlayerBlackJack[playerid][DealerClosedCard];
    ApplyDynamicActorAnimation(BlackJackTable[id][BJActor], "CASINO", "dealone", 4.1, false, false, false, false, 0);

    PlayerTextDrawSetString(playerid, DealerBJTD[playerid][PlayerBlackJack[playerid][DealerCardsId]], g_CasinoCards[randcard][CardModelID]);
    PlayerTextDrawShow(playerid, DealerBJTD[playerid][PlayerBlackJack[playerid][DealerCardsId]]);
    PlayerBlackJack[playerid][DealerCardValue] += g_CasinoCards[randcard][CardValue1];

    new Float:insuranceprice = (PlayerBlackJack[playerid][Bet][0]*0.5) * 2;
    new Float:GrandCash = insuranceprice+PlayerBlackJack[playerid][Bet][0];
    if(g_CasinoCards[randcard][CardValue1] == 10) //maka blackjack
    {
        PlayerPlayNearbySound(playerid, 5811);
        GameTextForPlayer(playerid, "~g~INSURANCE~n~WIN!", 3500, 6);

        AccountData[playerid][pCasinoChip] += floatround(GrandCash);
        SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"Wow, a great blackjack. You have won the insurance for "GREEN"$%s", FormatMoney(floatround(GrandCash)));

        SetTimerEx("NextRoundPrepare", 5555, false, "i", playerid);
    }
    else //lost insurance
    {
        switch(PlayerBlackJack[playerid][DealerCardValue])
        {
            case 4: {PlayerPlayNearbySound(playerid, 5841);}
            case 5: {PlayerPlayNearbySound(playerid, 5842);}
            case 6: {PlayerPlayNearbySound(playerid, 5843);}
            case 7: {PlayerPlayNearbySound(playerid, 5844);}
            case 8: {PlayerPlayNearbySound(playerid, 5845);}
            case 9: {PlayerPlayNearbySound(playerid, 5846);}
            case 10: {PlayerPlayNearbySound(playerid, 5829);}
            case 11: {PlayerPlayNearbySound(playerid, 5830);}
            case 12: 
            {
                if(PlayerBlackJack[playerid][DealerHasAce])
                {
                    PlayerPlayNearbySound(playerid, 5801); //2 or 12
                }
                else
                {
                    PlayerPlayNearbySound(playerid, 5831); //12
                }
            }
            case 13: 
            {
                if(PlayerBlackJack[playerid][DealerHasAce])
                {
                    PlayerPlayNearbySound(playerid, 5802); //3 or 13
                }
                else
                {
                    PlayerPlayNearbySound(playerid, 5832); //13
                }
            }
            case 14: 
            {
                if(PlayerBlackJack[playerid][DealerHasAce])
                {
                    PlayerPlayNearbySound(playerid, 5803); //4 or 14
                }
                else
                {
                    PlayerPlayNearbySound(playerid, 5833); //13
                }
            }
            case 15: 
            {
                if(PlayerBlackJack[playerid][DealerHasAce])
                {
                    PlayerPlayNearbySound(playerid, 5804); //5 or 15
                }
                else
                {
                    PlayerPlayNearbySound(playerid, 5834); //13
                }
            }
            case 16: 
            {
                if(PlayerBlackJack[playerid][DealerHasAce])
                {
                    PlayerPlayNearbySound(playerid, 5805); //6 or 16
                }
                else
                {
                    PlayerPlayNearbySound(playerid, 5835); //13
                }
            }
            case 17: 
            {
                if(PlayerBlackJack[playerid][DealerHasAce])
                {
                    PlayerPlayNearbySound(playerid, 5806); //7 or 17
                }
                else
                {
                    PlayerPlayNearbySound(playerid, 5836); //13
                }
            }
            case 18:
            {
                if(PlayerBlackJack[playerid][DealerHasAce])
                {
                    PlayerPlayNearbySound(playerid, 5807); //8 or 18
                }
                else
                {
                    PlayerPlayNearbySound(playerid, 5837); //13
                }
            }
            case 19: 
            {
                if(PlayerBlackJack[playerid][DealerHasAce])
                {
                    PlayerPlayNearbySound(playerid, 5808); //9 or 19
                }
                else
                {
                    PlayerPlayNearbySound(playerid, 5838); //13
                }
            }
            case 20: 
            {
                if(PlayerBlackJack[playerid][DealerHasAce])
                {
                    PlayerPlayNearbySound(playerid, 5800); //10 or 20
                }
                else
                {
                    PlayerPlayNearbySound(playerid, 5839); //13
                }
            }
            case 21: {PlayerPlayNearbySound(playerid, 5840);}
        }
        GameTextForPlayer(playerid, "~r~INSURANCE~n~LOST!", 3500, 6);
        AccountData[playerid][pCasinoChip] -= floatround(PlayerBlackJack[playerid][Bet][0]*0.5);
        SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"Bad decision, you have lost the insurance for "RED"$%s", FormatMoney(floatround(PlayerBlackJack[playerid][Bet][0]*0.5)));

        if(PlayerBlackJack[playerid][Splited])
        {
            if(PlayerBlackJack[playerid][IsSelectSplitCard])
            {
                TextDrawHideForPlayer(playerid, BlackJackTD[0]);
                TextDrawHideForPlayer(playerid, BlackJackTD[1]);
                TextDrawShowForPlayer(playerid, BlackJackTD[2]); //pindah ke pemain bagian split
            }
        }
        else
        {
            TextDrawShowForPlayer(playerid, BlackJackTD[0]); //td arrow kepada pemain
            TextDrawHideForPlayer(playerid, BlackJackTD[1]);
            TextDrawHideForPlayer(playerid, BlackJackTD[2]);
        }

        ShowPlayerBlackJackTD(playerid);
    }
    
    if(PlayerBlackJack[playerid][DealerHasAce])
    {
        PlayerTextDrawSetString(playerid, DealerBJTD[playerid][5], sprintf("%d or %d", PlayerBlackJack[playerid][DealerCardValue]-10, PlayerBlackJack[playerid][DealerCardValue]));
    }
    else
    {
        PlayerTextDrawSetString(playerid, DealerBJTD[playerid][5], sprintf("%d", PlayerBlackJack[playerid][DealerCardValue]));
    }

    PlayerBlackJack[playerid][InsuranceTaken] = false;
    return 1;
}

forward OnBJTableCreated(playerid, id);
public OnBJTableCreated(playerid, id)
{
	BJTable_Save(id);
	BJTable_Refresh(id);
	SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s membuat Blackjack Table dengan ID: %d.", AccountData[playerid][pAdminname], id);
	return 1;
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
    if(clickedid == BlackJackTD[3]) //hit
    {
        Dialog_Show(playerid, "HittBJ", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Hit", "Apakah anda yakin ingin hit?", "Hit", "Batal");
    }
    else if(clickedid == BlackJackTD[4]) //stand
    {
        if(PlayerBlackJack[playerid][Forbidden]) return 1;
        HidePlayerBlackJackTD(playerid);

        Dialog_Show(playerid, "StandBJ", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Stand", "Apakah anda yakin ingin stand?", "Stand", "Batal");
    }
    else if(clickedid == BlackJackTD[5]) //double
    {   
        Dialog_Show(playerid, "DoubleBJ", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Double", "Apakah anda yakin ingin double?", "Double", "Batal");
    }
    else if(clickedid == BlackJackTD[6]) //insurance
    {
        if(PlayerBlackJack[playerid][InsuranceTaken]) return 1;

        Dialog_Show(playerid, "InsuranceBJ", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Insurance", "Apakah anda yakin ingin membeli insurance?", "Insurance", "Batal");
    }
    else if(clickedid == BlackJackTD[7]) //split
    {
        if(PlayerBlackJack[playerid][Splited]) return 1;
        
        Dialog_Show(playerid, "SplitBJ", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Split", "Apakah anda yakin ingin split?", "Split", "Batal");
    }
    return 1;
}

hook OnPlayerEditDynObject(playerid, STREAMER_TAG_OBJECT: objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if(AccountData[playerid][EditingTableBJID] != -1 && Iter_Contains(BJTables, AccountData[playerid][EditingTableBJID]))
	{
		if(response == EDIT_RESPONSE_FINAL)
	    {
	        new tblid = AccountData[playerid][EditingTableBJID];
	        BlackJackTable[tblid][Pos][0] = x;
	        BlackJackTable[tblid][Pos][1] = y;
	        BlackJackTable[tblid][Pos][2] = z;
	        BlackJackTable[tblid][Pos][3] = rx;
	        BlackJackTable[tblid][Pos][4] = ry;
	        BlackJackTable[tblid][Pos][5] = rz;

			SetDynamicObjectPos(objectid, BlackJackTable[tblid][Pos][0], BlackJackTable[tblid][Pos][1], BlackJackTable[tblid][Pos][2]);
	        SetDynamicObjectRot(objectid, BlackJackTable[tblid][Pos][3], BlackJackTable[tblid][Pos][4], BlackJackTable[tblid][Pos][5]);

            SetDynamicActorFacingAngle(BlackJackTable[tblid][BJActor], BlackJackTable[tblid][Pos][5]-180.00);
            
            new Float:actorX = BlackJackTable[tblid][Pos][0] + 0.65*(floatcos(90 + BlackJackTable[tblid][Pos][5], degrees));
            new Float:actorY = BlackJackTable[tblid][Pos][1] + 0.65*(floatsin(90 - BlackJackTable[tblid][Pos][5], degrees));
            SetDynamicActorPos(BlackJackTable[tblid][BJActor], actorX, actorY, BlackJackTable[tblid][Pos][2]);
		    BJTable_Save(tblid);
	        AccountData[playerid][EditingTableBJID] = -1;
	    }

	    else if(response == EDIT_RESPONSE_CANCEL)
	    {
	        new tblid = AccountData[playerid][EditingTableBJID];
	        SetDynamicObjectPos(objectid, BlackJackTable[tblid][Pos][0], BlackJackTable[tblid][Pos][1], BlackJackTable[tblid][Pos][2]);
	        SetDynamicObjectRot(objectid, BlackJackTable[tblid][Pos][3], BlackJackTable[tblid][Pos][4], BlackJackTable[tblid][Pos][5]);
	        AccountData[playerid][EditingTableBJID] = -1;
	    }
	}
	return 0;
}

Dialog:SplitBJ(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    if(AccountData[playerid][pTempChip] < PlayerBlackJack[playerid][Bet][0])
    {
        PlayerPlayNearbySound(playerid, 5823);
        return SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"Sorry sir, Anda tidak memiliki cukup chip for the split "GRAY"($%s)", FormatMoney(PlayerBlackJack[playerid][Bet][0]));
    }

    HidePlayerBlackJackTD(playerid);

    SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"Your card has been splited, it was at "RED"$%s "WHITE"for the second bet.", FormatMoney(PlayerBlackJack[playerid][Bet][0]));

    new id = PlayerBlackJack[playerid][pInBJTable];
    if(id == -1) return 1;
    
    PlayerBlackJack[playerid][Splited] = true;

    new tdstring[64];
    PlayerTextDrawGetString(playerid, BlackJackPTD[playerid][1], tdstring); //get string icon kartu kedua
    PlayerTextDrawHide(playerid, BlackJackPTD[playerid][1]); //kemudian di hide kartu keduanya

    PlayerBlackJack[playerid][CardValue][0] = PlayerBlackJack[playerid][CardValue][0]/2; //kartu awal dipecah, dibagi 2 value nya
    PlayerBlackJack[playerid][CardValue][1] = PlayerBlackJack[playerid][CardValue][0]; //kartu split pertama di tetapkan value nya
    PlayerBlackJack[playerid][Bet][1] = PlayerBlackJack[playerid][Bet][0]; //bet split ditetapkan
    AccountData[playerid][pTempChip] -= PlayerBlackJack[playerid][Bet][0];

    PlayerTextDrawSetString(playerid, BlackJackPTD[playerid][5], sprintf("%d", PlayerBlackJack[playerid][CardValue][0]));
    PlayerTextDrawSetString(playerid, SplitBJTD[playerid][0], tdstring); //
    PlayerTextDrawSetString(playerid, SplitBJTD[playerid][5], sprintf("%d", PlayerBlackJack[playerid][CardValue][1])); //
    PlayerTextDrawSetString(playerid, SplitBJTD[playerid][6], sprintf("$%s", FormatMoney(PlayerBlackJack[playerid][Bet][1]))); //split di set bet nya

    PlayerTextDrawShow(playerid, SplitBJTD[playerid][0]); //di show yang split
    PlayerTextDrawShow(playerid, SplitBJTD[playerid][5]); //di show yang split
    PlayerTextDrawShow(playerid, SplitBJTD[playerid][6]); //di show yang split

    //set arrow next
    TextDrawHideForPlayer(playerid, BlackJackTD[0]);
    TextDrawHideForPlayer(playerid, BlackJackTD[1]);
    TextDrawShowForPlayer(playerid, BlackJackTD[2]);

    SetTimerEx("ContinueDrawCards", 1555, false, "id", playerid, id);
    return 1;
}

Dialog:InsuranceBJ(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        return 1;
    }

    if(AccountData[playerid][pTempChip] < floatround(PlayerBlackJack[playerid][Bet][0]*0.5))
    {
        PlayerPlayNearbySound(playerid, 5823);
        return SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"Sorry sir, Anda tidak memiliki cukup chip for the insurance "GRAY"($%s)", FormatMoney(floatround(PlayerBlackJack[playerid][Bet][0]*0.5)));
    }
    HidePlayerBlackJackTD(playerid);

    new id = PlayerBlackJack[playerid][pInBJTable];
    if(id == -1) return 1;
    
    new Float:TotalBet = PlayerBlackJack[playerid][Bet][0]+(PlayerBlackJack[playerid][Bet][0]*0.5);
    PlayerTextDrawSetString(playerid, BlackJackPTD[playerid][6], sprintf("$%s", FormatMoney(floatround(TotalBet))));
    AccountData[playerid][pTempChip] -= (PlayerBlackJack[playerid][Bet][0]*0.5);
    PlayerBlackJack[playerid][InsuranceTaken] = true;
    ApplyAnimation(playerid, "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0, true);

    TextDrawHideForPlayer(playerid, BlackJackTD[0]);
    TextDrawShowForPlayer(playerid, BlackJackTD[1]);

    GameTextForPlayer(playerid, "~g~INSURANCE...", 5500, 6);
    SetTimerEx("InsuranceResultan", 5500, false, "id", playerid, id);
    return 1;
}

Dialog:DoubleBJ(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        return 1;
    }

    if(AccountData[playerid][pTempChip] < PlayerBlackJack[playerid][Bet][0]) 
    {
        PlayerPlayNearbySound(playerid, 5823);
        return SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"Sorry sir, Anda tidak memiliki cukup chip for double "GRAY"($%s)", FormatMoney(PlayerBlackJack[playerid][Bet][0]));
    }

    AccountData[playerid][pTempChip] -= PlayerBlackJack[playerid][Bet][0];

    new id = PlayerBlackJack[playerid][pInBJTable];
    if(id == -1) return 1;

    new randcard = Iter_Random(CardsUsed[id]);
    Iter_Remove(CardsUsed[id],randcard);
    
    BJTable_ShuffleDeck(playerid, id);

    ApplyDynamicActorAnimation(BlackJackTable[id][BJActor], "CASINO", "dealone", 4.1, false, false, false, false, 0);
    
    if(PlayerBlackJack[playerid][Splited]) //jika split
    {
        if(PlayerBlackJack[playerid][IsSelectSplitCard]) //jika masih megang kartu kanan
        {
            PlayerBlackJack[playerid][IsSelectSplitCard] = false;
            PlayerBlackJack[playerid][DoubleTaken][1] = true;
            PlayerBlackJack[playerid][pSplitCardsID]++;
            PlayerBlackJack[playerid][CardValue][1] += g_CasinoCards[randcard][CardValue1];

            if(g_CasinoCards[randcard][CardValue1] == 11)
                PlayerBlackJack[playerid][HasAce][1] = true;

            if(PlayerBlackJack[playerid][HasAce][1])
            {
                PlayerTextDrawSetString(playerid, SplitBJTD[playerid][5], sprintf("%d or %d", PlayerBlackJack[playerid][CardValue][1]-10, PlayerBlackJack[playerid][CardValue][1]));
            }
            else
            {
                PlayerTextDrawSetString(playerid, SplitBJTD[playerid][5], sprintf("%d", PlayerBlackJack[playerid][CardValue][1]));
            }

            switch(PlayerBlackJack[playerid][CardValue][1])
            {
                case 4: {PlayerPlayNearbySound(playerid, 5841);}
                case 5: {PlayerPlayNearbySound(playerid, 5842);}
                case 6: {PlayerPlayNearbySound(playerid, 5843);}
                case 7: {PlayerPlayNearbySound(playerid, 5844);}
                case 8: {PlayerPlayNearbySound(playerid, 5845);}
                case 9: {PlayerPlayNearbySound(playerid, 5846);}
                case 10: {PlayerPlayNearbySound(playerid, 5829);}
                case 11: {PlayerPlayNearbySound(playerid, 5830);}
                case 12: 
                {
                    if(PlayerBlackJack[playerid][HasAce][1])
                    {
                        PlayerPlayNearbySound(playerid, 5801); //2 or 12
                    }
                    else
                    {
                        PlayerPlayNearbySound(playerid, 5831); //12
                    }
                }
                case 13: 
                {
                    if(PlayerBlackJack[playerid][HasAce][1])
                    {
                        PlayerPlayNearbySound(playerid, 5802); //3 or 13
                    }
                    else
                    {
                        PlayerPlayNearbySound(playerid, 5832); //13
                    }
                }
                case 14: 
                {
                    if(PlayerBlackJack[playerid][HasAce][1])
                    {
                        PlayerPlayNearbySound(playerid, 5803); //4 or 14
                    }
                    else
                    {
                        PlayerPlayNearbySound(playerid, 5833); //13
                    }
                }
                case 15: 
                {
                    if(PlayerBlackJack[playerid][HasAce][1])
                    {
                        PlayerPlayNearbySound(playerid, 5804); //5 or 15
                    }
                    else
                    {
                        PlayerPlayNearbySound(playerid, 5834); //13
                    }
                }
                case 16: 
                {
                    if(PlayerBlackJack[playerid][HasAce][1])
                    {
                        PlayerPlayNearbySound(playerid, 5805); //6 or 16
                    }
                    else
                    {
                        PlayerPlayNearbySound(playerid, 5835); //13
                    }
                }
                case 17: 
                {
                    if(PlayerBlackJack[playerid][HasAce][1])
                    {
                        PlayerPlayNearbySound(playerid, 5806); //7 or 17
                    }
                    else
                    {
                        PlayerPlayNearbySound(playerid, 5836); //13
                    }
                }
                case 18:
                {
                    if(PlayerBlackJack[playerid][HasAce][1])
                    {
                        PlayerPlayNearbySound(playerid, 5807); //8 or 18
                    }
                    else
                    {
                        PlayerPlayNearbySound(playerid, 5837); //13
                    }
                }
                case 19: 
                {
                    if(PlayerBlackJack[playerid][HasAce][1])
                    {
                        PlayerPlayNearbySound(playerid, 5808); //9 or 19
                    }
                    else
                    {
                        PlayerPlayNearbySound(playerid, 5838); //13
                    }
                }
                case 20: 
                {
                    if(PlayerBlackJack[playerid][HasAce][1])
                    {
                        PlayerPlayNearbySound(playerid, 5800); //10 or 20
                    }
                    else
                    {
                        PlayerPlayNearbySound(playerid, 5839); //13
                    }
                }
                case 21: {PlayerPlayNearbySound(playerid, 5840);}
            }

            PlayerTextDrawSetString(playerid, SplitBJTD[playerid][PlayerBlackJack[playerid][pSplitCardsID]], g_CasinoCards[randcard][CardModelID]);
            PlayerTextDrawShow(playerid, SplitBJTD[playerid][PlayerBlackJack[playerid][pSplitCardsID]]);

            PlayerTextDrawSetString(playerid, SplitBJTD[playerid][6], sprintf("$%s", FormatMoney(floatround(PlayerBlackJack[playerid][Bet][1]*2))));
            SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You have choose double for your second card, the bet increase "RED"$%s "WHITE"on this card", FormatMoney(PlayerBlackJack[playerid][Bet][1]));

            TextDrawShowForPlayer(playerid, BlackJackTD[0]);
            TextDrawHideForPlayer(playerid, BlackJackTD[1]);
            TextDrawHideForPlayer(playerid, BlackJackTD[2]); //pindah ke sebelah kiri
            return 1;
        }
        else
        {
            PlayerBlackJack[playerid][Forbidden] = true;
            PlayerBlackJack[playerid][DoubleTaken][0] = true;
            PlayerBlackJack[playerid][pCardsId]++;
            PlayerBlackJack[playerid][CardValue][0] += g_CasinoCards[randcard][CardValue1];

            if(g_CasinoCards[randcard][CardValue1] == 11)
                PlayerBlackJack[playerid][HasAce][0] = true;

            if(PlayerBlackJack[playerid][HasAce][0])
            {
                PlayerTextDrawSetString(playerid, BlackJackPTD[playerid][5], sprintf("%d or %d", PlayerBlackJack[playerid][CardValue][0]-10, PlayerBlackJack[playerid][CardValue][0]));
            }
            else
            {
                PlayerTextDrawSetString(playerid, BlackJackPTD[playerid][5], sprintf("%d", PlayerBlackJack[playerid][CardValue][0]));
            }

            switch(PlayerBlackJack[playerid][CardValue][0])
            {
                case 4: {PlayerPlayNearbySound(playerid, 5841);}
                case 5: {PlayerPlayNearbySound(playerid, 5842);}
                case 6: {PlayerPlayNearbySound(playerid, 5843);}
                case 7: {PlayerPlayNearbySound(playerid, 5844);}
                case 8: {PlayerPlayNearbySound(playerid, 5845);}
                case 9: {PlayerPlayNearbySound(playerid, 5846);}
                case 10: {PlayerPlayNearbySound(playerid, 5829);}
                case 11: {PlayerPlayNearbySound(playerid, 5830);}
                case 12: 
                {
                    if(PlayerBlackJack[playerid][HasAce][0])
                    {
                        PlayerPlayNearbySound(playerid, 5801); //2 or 12
                    }
                    else
                    {
                        PlayerPlayNearbySound(playerid, 5831); //12
                    }
                }
                case 13: 
                {
                    if(PlayerBlackJack[playerid][HasAce][0])
                    {
                        PlayerPlayNearbySound(playerid, 5802); //3 or 13
                    }
                    else
                    {
                        PlayerPlayNearbySound(playerid, 5832); //13
                    }
                }
                case 14: 
                {
                    if(PlayerBlackJack[playerid][HasAce][0])
                    {
                        PlayerPlayNearbySound(playerid, 5803); //4 or 14
                    }
                    else
                    {
                        PlayerPlayNearbySound(playerid, 5833); //13
                    }
                }
                case 15: 
                {
                    if(PlayerBlackJack[playerid][HasAce][0])
                    {
                        PlayerPlayNearbySound(playerid, 5804); //5 or 15
                    }
                    else
                    {
                        PlayerPlayNearbySound(playerid, 5834); //13
                    }
                }
                case 16: 
                {
                    if(PlayerBlackJack[playerid][HasAce][0])
                    {
                        PlayerPlayNearbySound(playerid, 5805); //6 or 16
                    }
                    else
                    {
                        PlayerPlayNearbySound(playerid, 5835); //13
                    }
                }
                case 17: 
                {
                    if(PlayerBlackJack[playerid][HasAce][0])
                    {
                        PlayerPlayNearbySound(playerid, 5806); //7 or 17
                    }
                    else
                    {
                        PlayerPlayNearbySound(playerid, 5836); //13
                    }
                }
                case 18:
                {
                    if(PlayerBlackJack[playerid][HasAce][0])
                    {
                        PlayerPlayNearbySound(playerid, 5807); //8 or 18
                    }
                    else
                    {
                        PlayerPlayNearbySound(playerid, 5837); //13
                    }
                }
                case 19: 
                {
                    if(PlayerBlackJack[playerid][HasAce][0])
                    {
                        PlayerPlayNearbySound(playerid, 5808); //9 or 19
                    }
                    else
                    {
                        PlayerPlayNearbySound(playerid, 5838); //13
                    }
                }
                case 20: 
                {
                    if(PlayerBlackJack[playerid][HasAce][0])
                    {
                        PlayerPlayNearbySound(playerid, 5800); //10 or 20
                    }
                    else
                    {
                        PlayerPlayNearbySound(playerid, 5839); //13
                    }
                }
                case 21: {PlayerPlayNearbySound(playerid, 5840);}
            }
            PlayerTextDrawSetString(playerid, BlackJackPTD[playerid][PlayerBlackJack[playerid][pCardsId]], g_CasinoCards[randcard][CardModelID]);
            PlayerTextDrawShow(playerid, BlackJackPTD[playerid][PlayerBlackJack[playerid][pCardsId]]);
            PlayerTextDrawSetString(playerid, BlackJackPTD[playerid][6], sprintf("$%s", FormatMoney(floatround(PlayerBlackJack[playerid][Bet][0]*2))));
            SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You have choose double for your first card, the bet increase "RED"$%s "WHITE"on this card", FormatMoney(PlayerBlackJack[playerid][Bet][0]));
        
            HidePlayerBlackJackTD(playerid);
        }
    }
    else //tidak split
    {
        HidePlayerBlackJackTD(playerid);
        PlayerBlackJack[playerid][Forbidden] = true;
        PlayerBlackJack[playerid][DoubleTaken][0] = true;
        if(PlayerBlackJack[playerid][pCardsId] >= 6) return 1;
        
        PlayerBlackJack[playerid][pCardsId]++;
        PlayerBlackJack[playerid][CardValue][0] += g_CasinoCards[randcard][CardValue1];

        TextDrawHideForPlayer(playerid, BlackJackTD[0]);
        TextDrawShowForPlayer(playerid, BlackJackTD[1]); //pindah ke sebelah NPC
        TextDrawHideForPlayer(playerid, BlackJackTD[2]); 

        PlayerTextDrawSetString(playerid, BlackJackPTD[playerid][PlayerBlackJack[playerid][pCardsId]], g_CasinoCards[randcard][CardModelID]);
        PlayerTextDrawShow(playerid, BlackJackPTD[playerid][PlayerBlackJack[playerid][pCardsId]]);
        PlayerTextDrawSetString(playerid, BlackJackPTD[playerid][6], sprintf("$%s", FormatMoney(floatround(PlayerBlackJack[playerid][Bet][0]*2))));

        if(g_CasinoCards[randcard][CardValue1] == 11)
            PlayerBlackJack[playerid][HasAce][0] = true;

        if(PlayerBlackJack[playerid][HasAce][0])
        {
            PlayerTextDrawSetString(playerid, BlackJackPTD[playerid][5], sprintf("%d or %d", PlayerBlackJack[playerid][CardValue][0]-10, PlayerBlackJack[playerid][CardValue][0]));
        }
        else
        {
            PlayerTextDrawSetString(playerid, BlackJackPTD[playerid][5], sprintf("%d", PlayerBlackJack[playerid][CardValue][0]));
        }

        switch(PlayerBlackJack[playerid][CardValue][0])
        {
            case 4: {PlayerPlayNearbySound(playerid, 5841);}
            case 5: {PlayerPlayNearbySound(playerid, 5842);}
            case 6: {PlayerPlayNearbySound(playerid, 5843);}
            case 7: {PlayerPlayNearbySound(playerid, 5844);}
            case 8: {PlayerPlayNearbySound(playerid, 5845);}
            case 9: {PlayerPlayNearbySound(playerid, 5846);}
            case 10: {PlayerPlayNearbySound(playerid, 5829);}
            case 11: {PlayerPlayNearbySound(playerid, 5830);}
            case 12: 
            {
                if(PlayerBlackJack[playerid][HasAce][0])
                {
                    PlayerPlayNearbySound(playerid, 5801); //2 or 12
                }
                else
                {
                    PlayerPlayNearbySound(playerid, 5831); //12
                }
            }
            case 13: 
            {
                if(PlayerBlackJack[playerid][HasAce][0])
                {
                    PlayerPlayNearbySound(playerid, 5802); //3 or 13
                }
                else
                {
                    PlayerPlayNearbySound(playerid, 5832); //13
                }
            }
            case 14: 
            {
                if(PlayerBlackJack[playerid][HasAce][0])
                {
                    PlayerPlayNearbySound(playerid, 5803); //4 or 14
                }
                else
                {
                    PlayerPlayNearbySound(playerid, 5833); //13
                }
            }
            case 15: 
            {
                if(PlayerBlackJack[playerid][HasAce][0])
                {
                    PlayerPlayNearbySound(playerid, 5804); //5 or 15
                }
                else
                {
                    PlayerPlayNearbySound(playerid, 5834); //13
                }
            }
            case 16: 
            {
                if(PlayerBlackJack[playerid][HasAce][0])
                {
                    PlayerPlayNearbySound(playerid, 5805); //6 or 16
                }
                else
                {
                    PlayerPlayNearbySound(playerid, 5835); //13
                }
            }
            case 17: 
            {
                if(PlayerBlackJack[playerid][HasAce][0])
                {
                    PlayerPlayNearbySound(playerid, 5806); //7 or 17
                }
                else
                {
                    PlayerPlayNearbySound(playerid, 5836); //13
                }
            }
            case 18:
            {
                if(PlayerBlackJack[playerid][HasAce][0])
                {
                    PlayerPlayNearbySound(playerid, 5807); //8 or 18
                }
                else
                {
                    PlayerPlayNearbySound(playerid, 5837); //13
                }
            }
            case 19: 
            {
                if(PlayerBlackJack[playerid][HasAce][0])
                {
                    PlayerPlayNearbySound(playerid, 5808); //9 or 19
                }
                else
                {
                    PlayerPlayNearbySound(playerid, 5838); //13
                }
            }
            case 20: 
            {
                if(PlayerBlackJack[playerid][HasAce][0])
                {
                    PlayerPlayNearbySound(playerid, 5800); //10 or 20
                }
                else
                {
                    PlayerPlayNearbySound(playerid, 5839); //13
                }
            }
            case 21: {PlayerPlayNearbySound(playerid, 5840);}
        }
    }
    SetTimerEx("ContinueDrawCards", 1555, false, "id", playerid, id);
    return 1;
}

Dialog:HittBJ(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;

    TextDrawHideForPlayer(playerid, BlackJackTD[5]);
    TextDrawHideForPlayer(playerid, BlackJackTD[6]);
    TextDrawHideForPlayer(playerid, BlackJackTD[7]);

    new id = PlayerBlackJack[playerid][pInBJTable];
    if(id == -1) return 1;
    BJTable_GivePlayerCards(playerid, id);
    return 1;
}

Dialog:StandBJ(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        ShowPlayerBlackJackTD(playerid);
        return 1;
    }
    
    if(PlayerBlackJack[playerid][Splited])
    {
        if(PlayerBlackJack[playerid][IsSelectSplitCard])
        {
            PlayerBlackJack[playerid][IsSelectSplitCard] = false;

            TextDrawShowForPlayer(playerid, BlackJackTD[0]);
            TextDrawHideForPlayer(playerid, BlackJackTD[1]);
            TextDrawHideForPlayer(playerid, BlackJackTD[2]); //pindah ke sebelah kiri

            ShowPlayerBlackJackTD(playerid);
            return 1;
        }
    }

    PlayerBlackJack[playerid][Forbidden] = true;

    TextDrawHideForPlayer(playerid, BlackJackTD[0]);
    TextDrawShowForPlayer(playerid, BlackJackTD[1]); //arrow ke NPC
    TextDrawHideForPlayer(playerid, BlackJackTD[2]); 

    new id = PlayerBlackJack[playerid][pInBJTable];
    if(id == -1) return 1;
    BJTable_GivePlayerCards(playerid, id);

    ApplyAnimation(playerid,"CASINO", "Roulette_loop",4.1,false,false,false,false,0,true);
    return 1;
}

Dialog:BlackjackBet(playerid, response, listitem, inputtext[])
{
    new id = PlayerBlackJack[playerid][pInBJTable];

    if(!response)
    {
        SetCameraBehindPlayer(playerid);
        TogglePlayerControllable(playerid, true);
        BJTable_StandOut(playerid, id);
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
        return 1;
    }

    if(isnull(inputtext))
    {
        return Dialog_Show(playerid, "BlackjackBet", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Your Bets", "ERROR: You can't let this section empty!\nPlease place your bets:", "Place", "Batal");
    }

    if(!IsNumericEx(inputtext))
    {
        PlayerPlayNearbySound(playerid, 5809);
        Dialog_Show(playerid, "BlackjackBet", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Your Bets", "ERROR: You can only input numbers!\nPlease place your bets:", "Place", "Batal");
        return 1;
    }

    if(strval(inputtext) < 1)
    {
        PlayerPlayNearbySound(playerid, 5809);
        return Dialog_Show(playerid, "BlackjackBet", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Your Bets", "ERROR: Invalid ammount of bets!\nPlease place your bets:", "Place", "Batal");
    }

    if(RoundNegativeToPositive(strval(inputtext)) > AccountData[playerid][pCasinoChip]) 
    {
        PlayerPlayNearbySound(playerid, 5823);
        return Dialog_Show(playerid, "BlackjackBet", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Your Bets", "ERROR: Anda tidak memiliki cukup funds!\nPlease place your bets:", "Place", "Batal");
    }

    if(RoundNegativeToPositive(strval(inputtext)) > BlackJackTable[id][MaxBet] || RoundNegativeToPositive(strval(inputtext)) < BlackJackTable[id][MinBet]) 
    {
        PlayerPlayNearbySound(playerid, 5809);
        return Dialog_Show(playerid, "BlackjackBet", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Your Bets", "ERROR: Your bet has more/less than the limit!\nPlease place your bets:", "Place", "Batal");
    }

    PlayerBlackJack[playerid][Bet][0] = strval(inputtext);
    AccountData[playerid][pTempChip] = (AccountData[playerid][pCasinoChip] - strval(inputtext));
    PlayerTextDrawSetString(playerid, BlackJackPTD[playerid][6], sprintf("$%s", FormatMoney(PlayerBlackJack[playerid][Bet][0])));
    PlayerTextDrawShow(playerid, BlackJackPTD[playerid][6]);
    BlackJackTable[id][BJStarted] = false;
    BlackJackTable[id][BJCountdown] = 15;
    SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"You've successfully assigned your bet: "RED"$%s", FormatMoney(PlayerBlackJack[playerid][Bet][0]));
    ApplyAnimation(playerid, "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0, true);
    return 1;
}

Dialog:BlackjackEnd(playerid, response, listitem, inputtext[])
{
    new id = PlayerBlackJack[playerid][pInBJTable];
    if(id == -1) return 1;
    
    if(!response)
    {
        SetCameraBehindPlayer(playerid);
        TogglePlayerControllable(playerid, true);
        BJTable_StandOut(playerid, id);
        SendClientMessage(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"Thank you, have a nice day.");
        return 1;
    }

    for(new x; x < 7; x++)
    {
        PlayerTextDrawDestroy(playerid, BlackJackPTD[playerid][x]);
        BlackJackPTD[playerid][x] = PlayerText: INVALID_PLAYER_TEXT_DRAW;

        PlayerTextDrawDestroy(playerid, SplitBJTD[playerid][x]);
        SplitBJTD[playerid][x] = PlayerText: INVALID_PLAYER_TEXT_DRAW;

        PlayerTextDrawDestroy(playerid, DealerBJTD[playerid][x]);
        DealerBJTD[playerid][x] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
    }

    PlayerTextDrawDestroy(playerid, BJTableCardTD[playerid][0]);
    BJTableCardTD[playerid][0] = PlayerText: INVALID_PLAYER_TEXT_DRAW;

    PlayerTextDrawDestroy(playerid, BJTableCardTD[playerid][1]);
    BJTableCardTD[playerid][1] = PlayerText: INVALID_PLAYER_TEXT_DRAW;

    TextDrawHideForPlayer(playerid, BlackJackTD[0]);
    TextDrawHideForPlayer(playerid, BlackJackTD[1]);
    TextDrawHideForPlayer(playerid, BlackJackTD[2]);
    
    PlayerBlackJack[playerid][Forbidden] = false;
    PlayerBlackJack[playerid][HasAce][0] = false;
    PlayerBlackJack[playerid][HasAce][1] = false;
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
    PlayerBlackJack[playerid][Bet][0] = 0;
    PlayerBlackJack[playerid][Bet][1] = 0;
    PlayerBlackJack[playerid][CardValue][0] = 0;
    PlayerBlackJack[playerid][pCardsId] = -1;
    PlayerBlackJack[playerid][DealerCardsId] = -1;
    PlayerBlackJack[playerid][DealerCardValue] = 0;
    PlayerBlackJack[playerid][DealerClosedCard] = -1;

    BJTable_CreatePlayerTD(playerid);
    BJTable_HideTextDraw(playerid);

    TextDrawShowForPlayer(playerid, BlackJackTD[8]);
    TextDrawShowForPlayer(playerid, BlackJackTD[9]);

    PlayerTextDrawSetString(playerid, BJTableCardTD[playerid][0], sprintf("Deck Cards~n~%d", Iter_Count(CardsUsed[id])));
    PlayerTextDrawShow(playerid, BJTableCardTD[playerid][0]);
    PlayerTextDrawSetString(playerid, BJTableCardTD[playerid][1], sprintf("Table Bet:~n~$%s - $%s", FormatMoney(BlackJackTable[id][MinBet]), FormatMoney(BlackJackTable[id][MaxBet])));
    PlayerTextDrawShow(playerid, BJTableCardTD[playerid][1]);

    BlackJackTable[id][BJCountdown] = 0;
    SendClientMessage(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"Let's play again, hope you get better in this round.");

    TogglePlayerControllable(playerid, false);

    PlayerPlayNearbySound(playerid, 5810);
    Dialog_Show(playerid, "BlackjackBet", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Your Bets", "Welcome to your table, please place your bets:", "Place", "Batal");
    return 1;
}

task BlackJackCountDown[1000]() 
{
    foreach(new i : BJTables) //mencari seluruh valid id bj table
    {
        if(!BlackJackTable[i][BJStarted])
        {
            if(BlackJackTable[i][BJCountdown] > 0) //apakah id id bj table tersebut lebih dari 0
            {
                BlackJackTable[i][BJCountdown]--; //jika ia dikurangi

                static string[144];
                format(string, sizeof(string), "New hand starts in %d second...", BlackJackTable[i][BJCountdown]); //countodwn berdasarkan masing-masing id

                if(BlackJackTable[i][BJCurrPlayerID] != INVALID_PLAYER_ID) //jika ada yang main
                {
                    PlayerTextDrawSetString(BlackJackTable[i][BJCurrPlayerID], DealerBJTD[BlackJackTable[i][BJCurrPlayerID]][6], string);
                    PlayerTextDrawShow(BlackJackTable[i][BJCurrPlayerID], DealerBJTD[BlackJackTable[i][BJCurrPlayerID]][6]);
                }

                if(BlackJackTable[i][BJCountdown] <= 0) //countodwn sudah selesai
                {
                    BlackJackTable[i][BJStarted] = true;
                    BlackJackTable[i][BJCountdown] = 0; //countdown di set 0

                    if(BlackJackTable[i][BJCurrPlayerID] != INVALID_PLAYER_ID) //jika ada yang main
                    {
                        PlayerTextDrawHide(BlackJackTable[i][BJCurrPlayerID], DealerBJTD[BlackJackTable[i][BJCurrPlayerID]][6]);
                        BJTable_GivePlayerCards(BlackJackTable[i][BJCurrPlayerID], i); //para player dberikan kartu sesuai id nya
                    }
                }
            }
        }
    }
    return 1;
}