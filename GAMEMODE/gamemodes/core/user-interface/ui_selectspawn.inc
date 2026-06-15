new PlayerText: SelectSpawnTD[MAX_PLAYERS][50];
OnLoadSelectSpawnTD(playerid)
{
    SelectSpawnTD[playerid][0] = CreatePlayerTextDraw(playerid, 112.000, 80.000, "LD_DUAL:white");
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][0], 405.000, 295.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][0], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][0], 505290495);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][0], 255);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][0], 1);

    SelectSpawnTD[playerid][1] = CreatePlayerTextDraw(playerid, 114.000, 82.000, "LD_DUAL:white");
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][1], 401.000, 284.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][1], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][1], 255);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][1], 255);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][1], 1);

    SelectSpawnTD[playerid][2] = CreatePlayerTextDraw(playerid, 264.000, 88.000, "LD_DUAL:white");
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][2], 246.000, 271.500);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][2], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][2], 1179010815);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][2], 255);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][2], 1);

    SelectSpawnTD[playerid][3] = CreatePlayerTextDraw(playerid, 226.000, 47.000, "_");
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][3], 200.000, 220.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][3], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][3], -1);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][3], 0);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][3], 5);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][3], 0);
    PlayerTextDrawSetPreviewModel(playerid, SelectSpawnTD[playerid][3], 19168);
    PlayerTextDrawSetPreviewRot(playerid, SelectSpawnTD[playerid][3], -90.000, 0.000, 180.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, SelectSpawnTD[playerid][3], 0, 0);

    SelectSpawnTD[playerid][4] = CreatePlayerTextDraw(playerid, 226.000, 180.300, "_");
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][4], 200.000, 220.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][4], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][4], -1);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][4], 0);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][4], 5);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][4], 0);
    PlayerTextDrawSetPreviewModel(playerid, SelectSpawnTD[playerid][4], 19170);
    PlayerTextDrawSetPreviewRot(playerid, SelectSpawnTD[playerid][4], -90.000, 0.000, 180.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, SelectSpawnTD[playerid][4], 0, 0);

    SelectSpawnTD[playerid][5] = CreatePlayerTextDraw(playerid, 346.899, 180.300, "_");
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][5], 200.000, 220.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][5], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][5], -1);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][5], 0);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][5], 5);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][5], 0);
    PlayerTextDrawSetPreviewModel(playerid, SelectSpawnTD[playerid][5], 19171);
    PlayerTextDrawSetPreviewRot(playerid, SelectSpawnTD[playerid][5], -90.000, 0.000, 180.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, SelectSpawnTD[playerid][5], 0, 0);

    SelectSpawnTD[playerid][6] = CreatePlayerTextDraw(playerid, 346.799, 47.000, "_");
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][6], 200.000, 220.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][6], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][6], -1);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][6], 0);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][6], 5);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][6], 0);
    PlayerTextDrawSetPreviewModel(playerid, SelectSpawnTD[playerid][6], 19169);
    PlayerTextDrawSetPreviewRot(playerid, SelectSpawnTD[playerid][6], -90.000, 0.000, 180.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, SelectSpawnTD[playerid][6], 0, 0);

    SelectSpawnTD[playerid][7] = CreatePlayerTextDraw(playerid, 449.000, 315.000, "HUD:radar_gangb");
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][7], 12.000, 12.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][7], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][7], -1);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][7], 255);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][7], 4);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][7], 1);

    SelectSpawnTD[playerid][8] = CreatePlayerTextDraw(playerid, 420.000, 277.000, "HUD:radar_gangB");
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][8], 12.000, 12.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][8], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][8], -1);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][8], 255);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][8], 4);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][8], 1);

    SelectSpawnTD[playerid][9] = CreatePlayerTextDraw(playerid, 302.000, 209.000, "HUD:radar_gangB");
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][9], 12.000, 12.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][9], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][9], -1);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][9], 255);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][9], 4);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][9], 1);

    SelectSpawnTD[playerid][10] = CreatePlayerTextDraw(playerid, 494.000, 143.000, "HUD:radar_gangB");
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][10], 12.000, 12.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][10], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][10], -1);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][10], 255);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][10], 4);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][10], 1);

    SelectSpawnTD[playerid][11] = CreatePlayerTextDraw(playerid, 382.000, 217.000, "HUD:radar_qmark");
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][11], 9.000, 13.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][11], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][11], -1);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][11], 255);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][11], 4);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][11], 1);

    SelectSpawnTD[playerid][12] = CreatePlayerTextDraw(playerid, 387.000, 232.000, "Last Location: ~r~Randolph Industrial Estate");
    PlayerTextDrawLetterSize(playerid, SelectSpawnTD[playerid][12], 0.300, 1.500);
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][12], 0.000, 235.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][12], 2);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][12], -1);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][12], 1);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][12], 2);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][12], 255);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][12], 1);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][12], 1);

    SelectSpawnTD[playerid][13] = CreatePlayerTextDraw(playerid, 182.000, 96.000, "PILIH_LOKASI_SPAWN");
    PlayerTextDrawLetterSize(playerid, SelectSpawnTD[playerid][13], 0.319, 1.600);
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][13], 115.000, 0.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][13], 2);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][13], -1);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][13], 1);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][13], 1768516095);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][13], 1);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][13], 1);

    SelectSpawnTD[playerid][14] = CreatePlayerTextDraw(playerid, 179.000, 111.000, "Pilih_lokasi_untuk_memulai_permainan");
    PlayerTextDrawLetterSize(playerid, SelectSpawnTD[playerid][14], 0.170, 0.999);
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][14], 111.000, 0.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][14], 2);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][14], -1448498689);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][14], 1);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][14], 150);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][14], 1);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][14], 1);

    SelectSpawnTD[playerid][15] = CreatePlayerTextDraw(playerid, 122.000, 133.000, "LD_DUAL:white");
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][15], 134.000, 37.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][15], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][15], -602653441);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][15], 255);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][15], 4);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][15], 1);

    SelectSpawnTD[playerid][16] = CreatePlayerTextDraw(playerid, 123.000, 134.000, "LD_DUAL:white");
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][16], 132.000, 35.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][16], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][16], 421075455);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][16], 0);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][16], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][16], 255);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][16], 4);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][16], 1);
    PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][16], 1);

    SelectSpawnTD[playerid][17] = CreatePlayerTextDraw(playerid, 124.000, 135.500, "LD_DUAL:white");
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][17], 19.000, 32.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][17], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][17], -602653441);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][17], 0);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][17], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][17], 255);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][17], 4);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][17], 1);

    SelectSpawnTD[playerid][18] = CreatePlayerTextDraw(playerid, 133.000, 143.000, "1");
    PlayerTextDrawLetterSize(playerid, SelectSpawnTD[playerid][18], 0.289, 1.500);
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][18], 115.000, 0.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][18], 2);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][18], -1);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][18], 1);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][18], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][18], 150);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][18], 1);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][18], 1);

    SelectSpawnTD[playerid][19] = CreatePlayerTextDraw(playerid, 150.000, 141.000, "LOS_SANTOS_AIRPORT");
    PlayerTextDrawLetterSize(playerid, SelectSpawnTD[playerid][19], 0.250, 1.299);
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][19], 99.000, 0.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][19], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][19], -1);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][19], 1);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][19], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][19], 1768516095);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][19], 1);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][19], 1);

    SelectSpawnTD[playerid][20] = CreatePlayerTextDraw(playerid, 150.000, 155.000, "Bandara_utama_sebagai_akses_awal_Los_Santos.");
    PlayerTextDrawLetterSize(playerid, SelectSpawnTD[playerid][20], 0.108, 0.699);
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][20], 315.000, 24.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][20], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][20], -1061109505);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][20], 1);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][20], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][20], 255);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][20], 1);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][20], 1);

    SelectSpawnTD[playerid][21] = CreatePlayerTextDraw(playerid, 122.000, 174.000, "LD_DUAL:white");
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][21], 134.000, 37.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][21], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][21], 1179010815);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][21], 0);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][21], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][21], 255);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][21], 4);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][21], 1);

    SelectSpawnTD[playerid][22] = CreatePlayerTextDraw(playerid, 123.000, 175.000, "LD_DUAL:white");
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][22], 132.000, 35.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][22], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][22], 421075455);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][22], 0);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][22], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][22], 255);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][22], 4);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][22], 1);
    PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][22], 1);

    SelectSpawnTD[playerid][23] = CreatePlayerTextDraw(playerid, 124.000, 176.500, "LD_DUAL:white");
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][23], 19.000, 32.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][23], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][23], 1179010815);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][23], 0);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][23], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][23], 255);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][23], 4);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][23], 1);

    SelectSpawnTD[playerid][24] = CreatePlayerTextDraw(playerid, 133.000, 184.000, "2");
    PlayerTextDrawLetterSize(playerid, SelectSpawnTD[playerid][24], 0.289, 1.500);
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][24], 115.000, 0.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][24], 2);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][24], -1);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][24], 1);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][24], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][24], 150);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][24], 1);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][24], 1);

    SelectSpawnTD[playerid][25] = CreatePlayerTextDraw(playerid, 150.000, 182.000, "MARKET_STATION");
    PlayerTextDrawLetterSize(playerid, SelectSpawnTD[playerid][25], 0.250, 1.299);
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][25], 99.000, 0.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][25], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][25], -1);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][25], 1);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][25], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][25], 1768516095);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][25], 1);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][25], 1);

    SelectSpawnTD[playerid][26] = CreatePlayerTextDraw(playerid, 150.000, 196.000, "Stasiun_transit_strategis_di_pusat_aktivitas_Los_Santos.");
    PlayerTextDrawLetterSize(playerid, SelectSpawnTD[playerid][26], 0.108, 0.699);
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][26], 315.000, 24.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][26], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][26], -1061109505);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][26], 1);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][26], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][26], 255);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][26], 1);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][26], 1);

    SelectSpawnTD[playerid][27] = CreatePlayerTextDraw(playerid, 122.000, 215.000, "LD_DUAL:white");
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][27], 134.000, 37.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][27], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][27], 1179010815);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][27], 0);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][27], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][27], 255);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][27], 4);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][27], 1);

    SelectSpawnTD[playerid][28] = CreatePlayerTextDraw(playerid, 123.000, 216.000, "LD_DUAL:white");
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][28], 132.000, 35.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][28], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][28], 421075455);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][28], 0);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][28], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][28], 255);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][28], 4);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][28], 1);
    PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][28], 1);

    SelectSpawnTD[playerid][29] = CreatePlayerTextDraw(playerid, 124.000, 217.500, "LD_DUAL:white");
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][29], 19.000, 32.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][29], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][29], 1179010815);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][29], 0);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][29], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][29], 255);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][29], 4);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][29], 1);

    SelectSpawnTD[playerid][30] = CreatePlayerTextDraw(playerid, 133.000, 225.000, "3");
    PlayerTextDrawLetterSize(playerid, SelectSpawnTD[playerid][30], 0.289, 1.500);
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][30], 115.000, 0.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][30], 2);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][30], -1);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][30], 1);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][30], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][30], 150);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][30], 1);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][30], 1);

    SelectSpawnTD[playerid][31] = CreatePlayerTextDraw(playerid, 150.000, 223.000, "CRANBERRY_STATION");
    PlayerTextDrawLetterSize(playerid, SelectSpawnTD[playerid][31], 0.250, 1.299);
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][31], 99.000, 0.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][31], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][31], -1);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][31], 1);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][31], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][31], 1768516095);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][31], 1);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][31], 1);

    SelectSpawnTD[playerid][32] = CreatePlayerTextDraw(playerid, 150.000, 237.000, "Stasiun_utama_di_kawasan_bisnis_padat_San_Fierro.");
    PlayerTextDrawLetterSize(playerid, SelectSpawnTD[playerid][32], 0.108, 0.699);
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][32], 315.000, 24.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][32], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][32], -1061109505);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][32], 1);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][32], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][32], 255);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][32], 1);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][32], 1);

    SelectSpawnTD[playerid][33] = CreatePlayerTextDraw(playerid, 122.000, 256.000, "LD_DUAL:white");
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][33], 134.000, 37.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][33], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][33], 1179010815);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][33], 0);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][33], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][33], 255);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][33], 4);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][33], 1);

    SelectSpawnTD[playerid][34] = CreatePlayerTextDraw(playerid, 123.000, 257.000, "LD_DUAL:white");
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][34], 132.000, 35.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][34], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][34], 421075455);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][34], 0);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][34], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][34], 255);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][34], 4);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][34], 1);
    PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][34], 1);

    SelectSpawnTD[playerid][35] = CreatePlayerTextDraw(playerid, 124.000, 258.500, "LD_DUAL:white");
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][35], 19.000, 32.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][35], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][35], 1179010815);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][35], 0);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][35], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][35], 255);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][35], 4);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][35], 1);

    SelectSpawnTD[playerid][36] = CreatePlayerTextDraw(playerid, 133.000, 266.000, "4");
    PlayerTextDrawLetterSize(playerid, SelectSpawnTD[playerid][36], 0.289, 1.500);
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][36], 115.000, 0.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][36], 2);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][36], -1);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][36], 1);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][36], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][36], 150);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][36], 1);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][36], 1);

    SelectSpawnTD[playerid][37] = CreatePlayerTextDraw(playerid, 150.000, 264.000, "LINDEN_STATION");
    PlayerTextDrawLetterSize(playerid, SelectSpawnTD[playerid][37], 0.250, 1.299);
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][37], 99.000, 0.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][37], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][37], -1);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][37], 1);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][37], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][37], 1768516095);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][37], 1);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][37], 1);

    SelectSpawnTD[playerid][38] = CreatePlayerTextDraw(playerid, 150.000, 278.000, "Akses_transportasi_utama_di_distrik_Las_Venturas.");
    PlayerTextDrawLetterSize(playerid, SelectSpawnTD[playerid][38], 0.108, 0.699);
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][38], 315.000, 24.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][38], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][38], -1061109505);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][38], 1);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][38], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][38], 255);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][38], 1);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][38], 1);

    SelectSpawnTD[playerid][39] = CreatePlayerTextDraw(playerid, 122.000, 297.000, "LD_DUAL:white");
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][39], 134.000, 37.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][39], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][39], 1179010815);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][39], 0);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][39], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][39], 255);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][39], 4);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][39], 1);

    SelectSpawnTD[playerid][40] = CreatePlayerTextDraw(playerid, 123.000, 298.000, "LD_DUAL:white");
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][40], 132.000, 35.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][40], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][40], 421075455);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][40], 0);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][40], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][40], 255);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][40], 4);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][40], 1);
    PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][40], 1);

    SelectSpawnTD[playerid][41] = CreatePlayerTextDraw(playerid, 124.000, 299.500, "LD_DUAL:white");
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][41], 19.000, 32.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][41], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][41], 1179010815);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][41], 0);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][41], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][41], 255);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][41], 4);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][41], 1);

    SelectSpawnTD[playerid][42] = CreatePlayerTextDraw(playerid, 133.000, 307.000, "5");
    PlayerTextDrawLetterSize(playerid, SelectSpawnTD[playerid][42], 0.289, 1.500);
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][42], 115.000, 0.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][42], 2);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][42], -1);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][42], 1);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][42], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][42], 150);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][42], 1);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][42], 1);

    SelectSpawnTD[playerid][43] = CreatePlayerTextDraw(playerid, 150.000, 305.000, "LAST_LOCATION");
    PlayerTextDrawLetterSize(playerid, SelectSpawnTD[playerid][43], 0.250, 1.299);
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][43], 99.000, 0.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][43], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][43], -1);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][43], 1);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][43], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][43], 1768516095);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][43], 1);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][43], 1);

    SelectSpawnTD[playerid][44] = CreatePlayerTextDraw(playerid, 150.000, 319.000, "Kembali_ke_posisi_terakhir_karakter_sebelum_keluar.");
    PlayerTextDrawLetterSize(playerid, SelectSpawnTD[playerid][44], 0.108, 0.699);
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][44], 315.000, 24.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][44], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][44], -1061109505);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][44], 1);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][44], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][44], 255);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][44], 1);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][44], 1);

    SelectSpawnTD[playerid][45] = CreatePlayerTextDraw(playerid, 122.000, 340.000, "LD_DUAL:white");
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][45], 65.000, 20.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][45], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][45], -602653441);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][45], 0);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][45], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][45], 255);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][45], 4);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][45], 1);
    PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][45], 1);

    SelectSpawnTD[playerid][46] = CreatePlayerTextDraw(playerid, 154.000, 344.000, "SPAWN");
    PlayerTextDrawLetterSize(playerid, SelectSpawnTD[playerid][46], 0.250, 1.299);
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][46], 99.000, 0.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][46], 2);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][46], -1);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][46], 1);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][46], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][46], 1768516095);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][46], 1);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][46], 1);

    SelectSpawnTD[playerid][47] = CreatePlayerTextDraw(playerid, 191.000, 340.000, "LD_DUAL:white");
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][47], 65.000, 20.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][47], 1);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][47], 1768516095);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][47], 0);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][47], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][47], 255);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][47], 4);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][47], 1);
    PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][47], 1);

    SelectSpawnTD[playerid][48] = CreatePlayerTextDraw(playerid, 224.000, 344.000, "BACK");
    PlayerTextDrawLetterSize(playerid, SelectSpawnTD[playerid][48], 0.250, 1.299);
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][48], 99.000, 0.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][48], 2);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][48], -1);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][48], 1);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][48], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][48], 1768516095);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][48], 1);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][48], 1);

    SelectSpawnTD[playerid][49] = CreatePlayerTextDraw(playerid, 314.000, 367.000, "THURXPROJECT");
    PlayerTextDrawLetterSize(playerid, SelectSpawnTD[playerid][49], 0.129, 0.698);
    PlayerTextDrawTextSize(playerid, SelectSpawnTD[playerid][49], 99.000, 398.000);
    PlayerTextDrawAlignment(playerid, SelectSpawnTD[playerid][49], 2);
    PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][49], -246);
    PlayerTextDrawSetShadow(playerid, SelectSpawnTD[playerid][49], 0);
    PlayerTextDrawSetOutline(playerid, SelectSpawnTD[playerid][49], 0);
    PlayerTextDrawBackgroundColor(playerid, SelectSpawnTD[playerid][49], 1768516095);
    PlayerTextDrawFont(playerid, SelectSpawnTD[playerid][49], 1);
    PlayerTextDrawSetProportional(playerid, SelectSpawnTD[playerid][49], 1);
}

ShowSelectSpawnTD(playerid, selectspawnid)
{
    new str[128];
    new char_slot = PlayerSelectCharTD[playerid]; // Ambil slot karakter yang sedang dipakai

    // ========================================================
    // CEK ANTI-COMBAT LOG / ANTI-/Q
    // ========================================================
    /*if (gettime() - PlayerCharLastLoginUnix[playerid][char_slot] < 3600)
    {
        selectspawnid = 4; // Paksa pilihan otomatis ke indeks 4 (Last Location)
    }*/

    for (new i = 0; i < 7; i++) PlayerTextDrawShow(playerid, SelectSpawnTD[playerid][i]);

    // Map Icon
    if (selectspawnid == 0)
    {
        PlayerTextDrawShow(playerid, SelectSpawnTD[playerid][7]);
        for (new i = 8; i < 13; i++) PlayerTextDrawHide(playerid, SelectSpawnTD[playerid][i]);

        // Merah & Kunci Tombol untuk Map Icon (Indeks 0)
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][15], -602653441);
        PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][16], 0);
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][17], -602653441);

        // Abu-abu & Buka Tombol untuk Pilihan Lainnya (Indeks 1, 2, 3, 4)
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][21], 1179010815);
        PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][22], 1);
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][23], 1179010815);

        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][27], 1179010815);
        PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][28], 1);
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][29], 1179010815);

        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][33], 1179010815);
        PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][34], 1);
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][35], 1179010815);

        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][39], 1179010815);
        PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][40], 1);
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][41], 1179010815);
    }

    if (selectspawnid == 1)
    {
        PlayerTextDrawShow(playerid, SelectSpawnTD[playerid][8]);
        for (new i = 7; i < 13; i++) if (i != 8) PlayerTextDrawHide(playerid, SelectSpawnTD[playerid][i]);

        // Merah & Kunci Tombol untuk Map Icon (Indeks 1)
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][21], -602653441);
        PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][22], 0);
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][23], -602653441);

        // Abu-abu & Buka Tombol untuk Pilihan Lainnya (Indeks 0, 2, 3, 4)
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][15], 1179010815);
        PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][16], 1);
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][17], 1179010815);

        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][27], 1179010815);
        PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][28], 1);
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][29], 1179010815);

        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][33], 1179010815);
        PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][34], 1);
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][35], 1179010815);

        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][39], 1179010815);
        PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][40], 1);
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][41], 1179010815);
    }

    if (selectspawnid == 2)
    {
        PlayerTextDrawShow(playerid, SelectSpawnTD[playerid][9]);
        for (new i = 7; i < 13; i++) if (i != 9) PlayerTextDrawHide(playerid, SelectSpawnTD[playerid][i]);

        // Merah & Kunci Tombol untuk Map Icon (Indeks 2)
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][27], -602653441);
        PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][28], 0);
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][29], -602653441);

        // Abu-abu & Buka Tombol untuk Pilihan Lainnya (Indeks 0, 1, 3, 4)
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][15], 1179010815);
        PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][16], 1);
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][17], 1179010815);

        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][21], 1179010815);
        PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][22], 1);
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][23], 1179010815);

        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][33], 1179010815);
        PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][34], 1);
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][35], 1179010815);

        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][39], 1179010815);
        PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][40], 1);
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][41], 1179010815);
    }

    if (selectspawnid == 3)
    {
        PlayerTextDrawShow(playerid, SelectSpawnTD[playerid][10]);
        for (new i = 7; i < 13; i++) if (i != 10) PlayerTextDrawHide(playerid, SelectSpawnTD[playerid][i]);

        // Merah & Kunci Tombol untuk Map Icon (Indeks 3)
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][33], -602653441);
        PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][34], 0);
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][35], -602653441);

        // Abu-abu & Buka Tombol untuk Pilihan Lainnya (Indeks 0, 1, 2, 4)
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][15], 1179010815);
        PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][16], 1);
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][17], 1179010815);

        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][21], 1179010815);
        PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][22], 1);
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][23], 1179010815);

        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][27], 1179010815);
        PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][28], 1);
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][29], 1179010815);

        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][39], 1179010815);
        PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][40], 1);
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][41], 1179010815);
    }

    if (selectspawnid == 4)
    {
        PlayerTextDrawShow(playerid, SelectSpawnTD[playerid][11]);
        format(str, sizeof(str), "Last Location: ~r~%s", GetLocation(PlayerCharLastSpawnX[playerid][char_slot], PlayerCharLastSpawnY[playerid][char_slot], PlayerCharLastSpawnZ[playerid][char_slot]));
        PlayerTextDrawSetString(playerid, SelectSpawnTD[playerid][12], str);
        PlayerTextDrawShow(playerid, SelectSpawnTD[playerid][12]);
        for (new i = 7; i < 13; i++) if (i != 11 && i != 12) PlayerTextDrawHide(playerid, SelectSpawnTD[playerid][i]);

        // Merah & Kunci Tombol untuk Map Icon (Indeks 4)
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][39], -602653441);
        PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][40], 0);
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][41], -602653441);

        // Abu-abu & Buka Tombol untuk Pilihan Lainnya (Indeks 0, 1, 2, 3)
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][15], 1179010815);
        PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][16], 1);
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][17], 1179010815);

        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][21], 1179010815);
        PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][22], 1);
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][23], 1179010815);

        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][27], 1179010815);
        PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][28], 1);
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][29], 1179010815);

        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][33], 1179010815);
        PlayerTextDrawSetSelectable(playerid, SelectSpawnTD[playerid][34], 1);
        PlayerTextDrawColor(playerid, SelectSpawnTD[playerid][35], 1179010815);
    }

    for (new i = 13; i < 50; i++) PlayerTextDrawShow(playerid, SelectSpawnTD[playerid][i]);
}

SelectSpawnTDClick(playerid, PlayerText:playertextid)
{
    new char_slot = PlayerSelectCharTD[playerid];

    for (new i = 0; i < 5; i++)
    {
        if (playertextid == SelectSpawnTD[playerid][16 + (i * 6)])
        {
            /*if (gettime() - PlayerCharLastLoginUnix[playerid][char_slot] < 3600)
            {
                PlayerSelectSpawnTD[playerid] = 4; // Paksa pilihan otomatis ke indeks 4 (Last Location)
                ShowSelectSpawnTD(playerid, 4); // Paksa ke Last Location
            }
            else
            {
                PlayerSelectSpawnTD[playerid] = i; // Simpan pilihan normal sesuai indeks yang diklik
                ShowSelectSpawnTD(playerid, i); // Tampilkan pilihan normal sesuai indeks yang diklik
            }*/

            PlayerSelectSpawnTD[playerid] = i; // Simpan pilihan normal sesuai indeks yang diklik
            ShowSelectSpawnTD(playerid, i); // Tampilkan pilihan normal sesuai indeks yang diklik
            return 1; // Langsung hentikan loop setelah tombol berhasil terdeteksi
        }
    }

    if (playertextid == SelectSpawnTD[playerid][45]) // Tombol SPAWN
    {
        if (PlayerSelectSpawnTD[playerid] != -1) // Pastikan ada pilihan yang dipilih
        {
            for (new i = 0; i < MAX_CHARS; i++)
                if (IsValidDynamicActor(LobbyActorID[playerid][i]))
                    DestroyDynamicActor(LobbyActorID[playerid][i]);

            for (new i = 0; i < 37; i++) PlayerTextDrawDestroy(playerid, SelectCharTD[playerid][i]);
            for (new i = 0; i < 50; i++) PlayerTextDrawDestroy(playerid, SelectSpawnTD[playerid][i]);

            strcopy(AccountData[playerid][pName], PlayerChar[playerid][char_slot]);

            static string[315];
            mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `player_bans` WHERE (name = '%e') OR (longip & %i = %i) LIMIT 1", AccountData[playerid][pName], BAN_MASK, (Ban_GetLongIP(AccountData[playerid][pIP]) & BAN_MASK));
	        mysql_pquery(g_SQL, string, "CheckBan", "i", playerid);
        }
        return 1;
    }

    if (playertextid == SelectSpawnTD[playerid][47]) // Tombol BACK
    {
        for (new i = 0; i < 50; i++) PlayerTextDrawHide(playerid, SelectSpawnTD[playerid][i]);

        SetLobbySelectCharCamera(playerid, PlayerSelectCharTD[playerid]);
        SetTimerEx("ChangeCameraLobby", 1500, false, "id", playerid, 0);
    }
    return 1;
}

SpawnPlayerAtLocation(playerid, spawnid)
{
    new char_slot = PlayerSelectCharTD[playerid];
    new Float:x, Float:y, Float:z, Float:a;
    new vw = 0, int_id = 0; // Bikin variabel dengan default VW 0 dan Interior 0

    switch (spawnid)
    {
        case 0: // Spawn Bandara (Los Santos)
        {
            x = 1749.9818; y = -2516.1926; z = 13.5969; a = 91.5945;
            vw = 60;    // Khusus Bandara set VW ke 60
            int_id = 0; // Interior tetap 0
        }
        case 1: // Market Station
        {
            x = 823.9694; y = -1361.6813; z = -0.5078; a = 319.9306;
            // vw dan int_id otomatis pakai default (0)
        }
        case 2: // Cranberry Station
        {
            x = -1968.6857; y = 111.4491; z = 27.6875; a = 358.8939;
        }
        case 3: // Linden Station
        {
            x = 2853.6133; y = 1291.0961; z = 11.3906; a = 91.2656;
        }
        case 4: // Last Location
        {
            x = PlayerCharLastSpawnX[playerid][char_slot];
            y = PlayerCharLastSpawnY[playerid][char_slot];
            z = PlayerCharLastSpawnZ[playerid][char_slot];
            a = PlayerCharLastSpawnA[playerid][char_slot];
            
            vw = AccountData[playerid][pWorld];
            int_id = AccountData[playerid][pInterior];
        }
        default: // Default ke Bandara jika terjadi error
        {
            x = 1749.9818; y = -2516.1926; z = 13.5969; a = 91.5945; 
            vw = 60;
            int_id = 0;
        }
    }

    // Vip dan Gold perlu disesuaikan nantinya
    /*AccountData[playerid][pVip] = 0;
    AccountData[playerid][pVipTime] = 0;
    AccountData[playerid][pGold] = 0; */

    InCharSelection[playerid] = false; // Pastikan flag karakter sudah false
    SetPlayerColor(playerid, 0xFFFFFFFF); // Set warna pemain ke default (putih)

    AccountData[playerid][pWorld] = vw; // Simpan VW ke database
    AccountData[playerid][pInterior] = int_id; // Simpan Interior ke database
    AccountData[playerid][pPos][0] = x; // Simpan X ke database
    AccountData[playerid][pPos][1] = y; // Simpan Y ke database
    AccountData[playerid][pPos][2] = z; // Simpan Z ke database
    AccountData[playerid][pPos][3] = a; // Simpan Angle ke database
    SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pSkin], x, y, z, a, 0, 0, 0, 0, 0, 0);
    pAllowSpawn[playerid] = true;
    pLoginSpawnLoaded[playerid] = false;
    TogglePlayerSpectating(playerid, false);

    CancelSelectTextDraw(playerid);
    SetCameraBehindPlayer(playerid);
    Anticheat[playerid][acImmunity] = gettime() + 5;
    GameTextForPlayer(playerid, "Memuat Objek...", 6500, 3);
}
