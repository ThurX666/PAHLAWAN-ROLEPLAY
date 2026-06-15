#define MAX_ROULETTE_TABLES 100

enum e_roulettetble
{
    Float:Pos[6],
    World,
    Interior,

    //not save
    bool:Occupied,
    bool:Started,
    STREAMER_TAG_OBJECT:RTOBjID
};
new RouletteTable[MAX_ROULETTE_TABLES][e_roulettetble],
    Iterator:Roulettes<MAX_ROULETTE_TABLES>;

enum e_roulettepls
{
    bool:Seated,
    Bet,
    pInRouletteTable
};
new PlayerRoulette[MAX_PLAYERS][e_roulettepls];

RouletteTable_Nearest(playerid)
{
    foreach(new i : Roulettes) if (IsPlayerInRangeOfPoint(playerid, 2.0, RouletteTable[i][Pos][0], RouletteTable[i][Pos][1], RouletteTable[i][Pos][2]))
	{
		if (GetPlayerInterior(playerid) == RouletteTable[i][Interior] && GetPlayerVirtualWorld(playerid) == RouletteTable[i][World])
			return i;
	}
	return -1;
}

forward OnRuletteTableCreated(playerid, id);
public OnRuletteTableCreated(playerid, id)
{
	RouletteTable_Save(id);
	RouletteTable_Refresh(id);
	SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s membuat Roulette Table dengan ID: %d.", AccountData[playerid][pAdminname], id);
	return 1;
}

YCMD:addroulette(playerid, params[], help)
{
    new minbet, maxbet, id = Iter_Free(Roulettes), query[512];

    if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

	if (sscanf(params, "dd", minbet, maxbet))
	{
	    SUM(playerid, "/addroulette [Min Bet] [Max Bet]");
		return 1;
	}
	if (minbet < 5000)
	    return ShowTDN(playerid, NOTIFICATION_ERROR, "Min bet $100.00!");

    if (maxbet < 5000 || maxbet > 500000)
	    return ShowTDN(playerid, NOTIFICATION_ERROR, "Max bet $100.00 - $5,000.00!");

    GetPlayerPos(playerid, RouletteTable[id][Pos][0], RouletteTable[id][Pos][1], RouletteTable[id][Pos][2]);
    RouletteTable[id][Pos][3] = RouletteTable[id][Pos][4] = RouletteTable[id][Pos][5] = 0.0;

    RouletteTable[id][World] = GetPlayerVirtualWorld(playerid);
    RouletteTable[id][Interior] = GetPlayerInterior(playerid);

    RouletteTable[id][MinBet] = minbet;
    RouletteTable[id][MaxBet] = maxbet;

    RouletteTable[id][Occupied] = false;
    RouletteTable[id][Started] = false;
    
    new Float:actorX = RouletteTable[id][Pos][0] + 0.65*(floatcos(90 + RouletteTable[id][Pos][5], degrees));
    new Float:actorY = RouletteTable[id][Pos][1] + 0.65*(floatsin(90 - RouletteTable[id][Pos][5], degrees));

    new randskin = __g_CasinoNPCSkin[random(sizeof(__g_CasinoNPCSkin))];
    RouletteTable[id][Actor] = CreateDynamicActor(randskin, actorX, actorY, RouletteTable[id][Pos][2], RouletteTable[id][Pos][5] - 180.0, true, 1000.0, RouletteTable[id][World], RouletteTable[id][Interior], -1, 100.00, -1, 0);
    RouletteTable[id][Object] = CreateDynamicObject(1978, RouletteTable[id][Pos][0], RouletteTable[id][Pos][1], RouletteTable[id][Pos][2], RouletteTable[id][Pos][3], RouletteTable[id][Pos][4], RouletteTable[id][Pos][5], RouletteTable[id][World], RouletteTable[id][Interior], -1, 100.00, 100.00, -1);

    Iter_Add(Roulettes, id);

	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `bj_tables` SET `id`=%d, `X`='%f', `Y`='%f', `Z`='%f', `RX`='%f', `RY`='%f', `RZ`='%f', `Interior`=%d, `World`=%d, `MinBet` = %d, `MaxBet` = %d", id, RouletteTable[id][Pos][0], RouletteTable[id][Pos][1], RouletteTable[id][Pos][2], RouletteTable[id][Pos][3], RouletteTable[id][Pos][4], RouletteTable[id][Pos][5], GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid), RouletteTable[id][MinBet], RouletteTable[id][MaxBet]);
	mysql_pquery(g_SQL, query, "OnRuletteTableCreated", "ii", playerid, id);
    return 1;
}

YCMD:roulette(playerid, params[], help)
{
    new id = RouletteTable_Nearest(playerid);
    if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan meja roulette manapun!");

    if(PlayerRoulette[playerid][Seated]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang bermain roulette!");
    if(RouletteTable[id][Occupied]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Meja roulette ini sedang sibuk!");
    
    PlayerRoulette[playerid][Bet] = 0;
    
    PlayerRoulette[playerid][Seated] = true;
    RouletteTable[id][Occupied] = true;
    RouletteTable[id][Started] = false;

    new Float:actorX = RouletteTable[id][Pos][0] - 0.55*(floatcos(90 + RouletteTable[id][Pos][5], degrees));
    new Float:actorY = RouletteTable[id][Pos][1] - 0.55*(floatsin(90 - RouletteTable[id][Pos][5], degrees));
    CameraRadiusSetPos(playerid, actorX, actorY, RouletteTable[id][Pos][2], RouletteTable[id][Pos][5]+180.0, 2.8, 1.5);

    SendClientMessageEx(playerid, X11_LIGHTBLUE, "DEALER: "WHITE"Welcome to your seat. This table minimum bet is "YELLOW"$%s "WHITE"and maximum is "YELLOW"$%s", FormatMoney(RouletteTable[id][MinBet]), FormatMoney(RouletteTable[id][MaxBet]));
    
    PlayerRoulette[playerid][pInRouletteTable] = id;

    TogglePlayerControllable(playerid, false);

    PlayerPlayNearbySound(playerid, 5810);
    Dialog_Show(playerid, "BlackjackBet", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Your Bets", "Welcome to your table, please place your bets:", "Place", "Batal");
    return 1;
}