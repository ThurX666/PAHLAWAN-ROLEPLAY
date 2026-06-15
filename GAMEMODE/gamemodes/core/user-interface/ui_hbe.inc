new Text:HBE[25],
    PlayerText:PHBE[MAX_PLAYERS][29],
	Text: PHONE_HBE[21],
    Text:StressTD;

CreateHBETextdraw()
{
	//V1
	// Speedometer
	HBE[0] = TextDrawCreate(139.000, 426.000, "KMH");
	TextDrawLetterSize(HBE[0], 0.128, 0.638);
	TextDrawAlignment(HBE[0], 2);
	TextDrawColor(HBE[0], -1);
	TextDrawSetShadow(HBE[0], 1);
	TextDrawSetOutline(HBE[0], 1);
	TextDrawBackgroundColor(HBE[0], 0);
	TextDrawFont(HBE[0], 1);
	TextDrawSetProportional(HBE[0], 1);

	HBE[1] = TextDrawCreate(168.000, 426.000, "FUEL");
	TextDrawLetterSize(HBE[1], 0.128, 0.638);
	TextDrawAlignment(HBE[1], 2);
	TextDrawColor(HBE[1], -1);
	TextDrawSetShadow(HBE[1], 1);
	TextDrawSetOutline(HBE[1], 1);
	TextDrawBackgroundColor(HBE[1], 0);
	TextDrawFont(HBE[1], 1);
	TextDrawSetProportional(HBE[1], 1);

	HBE[2] = TextDrawCreate(203.000, 426.000, "DAMAGE");
	TextDrawLetterSize(HBE[2], 0.128, 0.638);
	TextDrawAlignment(HBE[2], 2);
	TextDrawColor(HBE[2], -1);
	TextDrawSetShadow(HBE[2], 1);
	TextDrawSetOutline(HBE[2], 1);
	TextDrawBackgroundColor(HBE[2], 0);
	TextDrawFont(HBE[2], 1);
	TextDrawSetProportional(HBE[2], 1);

	HBE[3] = TextDrawCreate(120.000, 439.299, "LD_BUM:blkdot");
	TextDrawTextSize(HBE[3], 1.000, 4.000);
	TextDrawAlignment(HBE[3], 1);
	TextDrawColor(HBE[3], -1);
	TextDrawSetShadow(HBE[3], 0);
	TextDrawSetOutline(HBE[3], 0);
	TextDrawBackgroundColor(HBE[3], 255);
	TextDrawFont(HBE[3], 4);
	TextDrawSetProportional(HBE[3], 1);

	HBE[4] = TextDrawCreate(163.000, 439.299, "LD_BUM:blkdot");
	TextDrawTextSize(HBE[4], 1.000, 4.000);
	TextDrawAlignment(HBE[4], 1);
	TextDrawColor(HBE[4], -1);
	TextDrawSetShadow(HBE[4], 0);
	TextDrawSetOutline(HBE[4], 0);
	TextDrawBackgroundColor(HBE[4], 255);
	TextDrawFont(HBE[4], 4);
	TextDrawSetProportional(HBE[4], 1);

	// HBE
	HBE[5] = TextDrawCreate(3.000, 429.000, "ld_dual:white");
	TextDrawLetterSize(HBE[5], 0.600, 2.000);
	TextDrawTextSize(HBE[5], 30.000, 1.000);
	TextDrawAlignment(HBE[5], 1);
	TextDrawColor(HBE[5], -1);
	TextDrawUseBox(HBE[5], 1);
	TextDrawBoxColor(HBE[5], 50);
	TextDrawSetShadow(HBE[5], 0);
	TextDrawSetOutline(HBE[5], 1);
	TextDrawBackgroundColor(HBE[5], 255);
	TextDrawFont(HBE[5], 4);
	TextDrawSetProportional(HBE[5], 1);

	HBE[6] = TextDrawCreate(32.000, 429.000, "ld_dual:white");
	TextDrawLetterSize(HBE[6], 0.600, 2.000);
	TextDrawTextSize(HBE[6], 1.000, 15.000);
	TextDrawAlignment(HBE[6], 1);
	TextDrawColor(HBE[6], -1);
	TextDrawUseBox(HBE[6], 1);
	TextDrawBoxColor(HBE[6], 50);
	TextDrawSetShadow(HBE[6], 0);
	TextDrawSetOutline(HBE[6], 1);
	TextDrawBackgroundColor(HBE[6], 255);
	TextDrawFont(HBE[6], 4);
	TextDrawSetProportional(HBE[6], 1);

	HBE[7] = TextDrawCreate(3.000, 443.000, "ld_dual:white");
	TextDrawLetterSize(HBE[7], 0.600, 2.000);
	TextDrawTextSize(HBE[7], 30.000, 1.000);
	TextDrawAlignment(HBE[7], 1);
	TextDrawColor(HBE[7], -1);
	TextDrawUseBox(HBE[7], 1);
	TextDrawBoxColor(HBE[7], 50);
	TextDrawSetShadow(HBE[7], 0);
	TextDrawSetOutline(HBE[7], 1);
	TextDrawBackgroundColor(HBE[7], 255);
	TextDrawFont(HBE[7], 4);
	TextDrawSetProportional(HBE[7], 1);

	HBE[8] = TextDrawCreate(3.000, 429.000, "ld_dual:white");
	TextDrawLetterSize(HBE[8], 0.600, 2.000);
	TextDrawTextSize(HBE[8], 1.000, 15.000);
	TextDrawAlignment(HBE[8], 1);
	TextDrawColor(HBE[8], -1);
	TextDrawUseBox(HBE[8], 1);
	TextDrawBoxColor(HBE[8], 50);
	TextDrawSetShadow(HBE[8], 0);
	TextDrawSetOutline(HBE[8], 1);
	TextDrawBackgroundColor(HBE[8], 255);
	TextDrawFont(HBE[8], 4);
	TextDrawSetProportional(HBE[8], 1);

	HBE[9] = TextDrawCreate(34.000, 429.000, "ld_dual:white");
	TextDrawLetterSize(HBE[9], 0.600, 2.000);
	TextDrawTextSize(HBE[9], 30.000, 1.000);
	TextDrawAlignment(HBE[9], 1);
	TextDrawColor(HBE[9], -1);
	TextDrawUseBox(HBE[9], 1);
	TextDrawBoxColor(HBE[9], 50);
	TextDrawSetShadow(HBE[9], 0);
	TextDrawSetOutline(HBE[9], 1);
	TextDrawBackgroundColor(HBE[9], 255);
	TextDrawFont(HBE[9], 4);
	TextDrawSetProportional(HBE[9], 1);

	HBE[10] = TextDrawCreate(63.000, 429.000, "ld_dual:white");
	TextDrawLetterSize(HBE[10], 0.600, 2.000);
	TextDrawTextSize(HBE[10], 1.000, 15.000);
	TextDrawAlignment(HBE[10], 1);
	TextDrawColor(HBE[10], -1);
	TextDrawUseBox(HBE[10], 1);
	TextDrawBoxColor(HBE[10], 50);
	TextDrawSetShadow(HBE[10], 0);
	TextDrawSetOutline(HBE[10], 1);
	TextDrawBackgroundColor(HBE[10], 255);
	TextDrawFont(HBE[10], 4);
	TextDrawSetProportional(HBE[10], 1);

	HBE[11] = TextDrawCreate(34.000, 443.000, "ld_dual:white");
	TextDrawLetterSize(HBE[11], 0.600, 2.000);
	TextDrawTextSize(HBE[11], 30.000, 1.000);
	TextDrawAlignment(HBE[11], 1);
	TextDrawColor(HBE[11], -1);
	TextDrawUseBox(HBE[11], 1);
	TextDrawBoxColor(HBE[11], 50);
	TextDrawSetShadow(HBE[11], 0);
	TextDrawSetOutline(HBE[11], 1);
	TextDrawBackgroundColor(HBE[11], 255);
	TextDrawFont(HBE[11], 4);
	TextDrawSetProportional(HBE[11], 1);

	HBE[12] = TextDrawCreate(34.000, 429.000, "ld_dual:white");
	TextDrawLetterSize(HBE[12], 0.600, 2.000);
	TextDrawTextSize(HBE[12], 1.000, 15.000);
	TextDrawAlignment(HBE[12], 1);
	TextDrawColor(HBE[12], -1);
	TextDrawUseBox(HBE[12], 1);
	TextDrawBoxColor(HBE[12], 50);
	TextDrawSetShadow(HBE[12], 0);
	TextDrawSetOutline(HBE[12], 1);
	TextDrawBackgroundColor(HBE[12], 255);
	TextDrawFont(HBE[12], 4);
	TextDrawSetProportional(HBE[12], 1);

	HBE[13] = TextDrawCreate(65.000, 429.000, "ld_dual:white");
	TextDrawLetterSize(HBE[13], 0.600, 2.000);
	TextDrawTextSize(HBE[13], 15.000, 1.000);
	TextDrawAlignment(HBE[13], 1);
	TextDrawColor(HBE[13], -1);
	TextDrawUseBox(HBE[13], 1);
	TextDrawBoxColor(HBE[13], 50);
	TextDrawSetShadow(HBE[13], 0);
	TextDrawSetOutline(HBE[13], 1);
	TextDrawBackgroundColor(HBE[13], 255);
	TextDrawFont(HBE[13], 4);
	TextDrawSetProportional(HBE[13], 1);

	HBE[14] = TextDrawCreate(79.000, 429.000, "ld_dual:white");
	TextDrawLetterSize(HBE[14], 0.600, 2.000);
	TextDrawTextSize(HBE[14], 1.000, 14.000);
	TextDrawAlignment(HBE[14], 1);
	TextDrawColor(HBE[14], -1);
	TextDrawUseBox(HBE[14], 1);
	TextDrawBoxColor(HBE[14], 50);
	TextDrawSetShadow(HBE[14], 0);
	TextDrawSetOutline(HBE[14], 1);
	TextDrawBackgroundColor(HBE[14], 255);
	TextDrawFont(HBE[14], 4);
	TextDrawSetProportional(HBE[14], 1);

	HBE[15] = TextDrawCreate(65.000, 443.000, "ld_dual:white");
	TextDrawLetterSize(HBE[15], 0.600, 2.000);
	TextDrawTextSize(HBE[15], 15.000, 1.000);
	TextDrawAlignment(HBE[15], 1);
	TextDrawColor(HBE[15], -1);
	TextDrawUseBox(HBE[15], 1);
	TextDrawBoxColor(HBE[15], 50);
	TextDrawSetShadow(HBE[15], 0);
	TextDrawSetOutline(HBE[15], 1);
	TextDrawBackgroundColor(HBE[15], 255);
	TextDrawFont(HBE[15], 4);
	TextDrawSetProportional(HBE[15], 1);

	HBE[16] = TextDrawCreate(65.000, 429.000, "ld_dual:white");
	TextDrawLetterSize(HBE[16], 0.600, 2.000);
	TextDrawTextSize(HBE[16], 1.000, 15.000);
	TextDrawAlignment(HBE[16], 1);
	TextDrawColor(HBE[16], -1);
	TextDrawUseBox(HBE[16], 1);
	TextDrawBoxColor(HBE[16], 50);
	TextDrawSetShadow(HBE[16], 0);
	TextDrawSetOutline(HBE[16], 1);
	TextDrawBackgroundColor(HBE[16], 255);
	TextDrawFont(HBE[16], 4);
	TextDrawSetProportional(HBE[16], 1);

	HBE[17] = TextDrawCreate(81.000, 429.000, "ld_dual:white");
	TextDrawLetterSize(HBE[17], 0.600, 2.000);
	TextDrawTextSize(HBE[17], 15.000, 1.000);
	TextDrawAlignment(HBE[17], 1);
	TextDrawColor(HBE[17], -1);
	TextDrawUseBox(HBE[17], 1);
	TextDrawBoxColor(HBE[17], 50);
	TextDrawSetShadow(HBE[17], 0);
	TextDrawSetOutline(HBE[17], 1);
	TextDrawBackgroundColor(HBE[17], 255);
	TextDrawFont(HBE[17], 4);
	TextDrawSetProportional(HBE[17], 1);

	HBE[18] = TextDrawCreate(95.000, 430.000, "ld_dual:white");
	TextDrawLetterSize(HBE[18], 0.600, 2.000);
	TextDrawTextSize(HBE[18], 1.000, 14.000);
	TextDrawAlignment(HBE[18], 1);
	TextDrawColor(HBE[18], -1);
	TextDrawUseBox(HBE[18], 1);
	TextDrawBoxColor(HBE[18], 50);
	TextDrawSetShadow(HBE[18], 0);
	TextDrawSetOutline(HBE[18], 1);
	TextDrawBackgroundColor(HBE[18], 255);
	TextDrawFont(HBE[18], 4);
	TextDrawSetProportional(HBE[18], 1);

	HBE[19] = TextDrawCreate(81.000, 443.000, "ld_dual:white");
	TextDrawLetterSize(HBE[19], 0.600, 2.000);
	TextDrawTextSize(HBE[19], 15.000, 1.000);
	TextDrawAlignment(HBE[19], 1);
	TextDrawColor(HBE[19], -1);
	TextDrawUseBox(HBE[19], 1);
	TextDrawBoxColor(HBE[19], 50);
	TextDrawSetShadow(HBE[19], 0);
	TextDrawSetOutline(HBE[19], 1);
	TextDrawBackgroundColor(HBE[19], 255);
	TextDrawFont(HBE[19], 4);
	TextDrawSetProportional(HBE[19], 1);

	HBE[20] = TextDrawCreate(81.000, 430.000, "ld_dual:white");
	TextDrawLetterSize(HBE[20], 0.600, 2.000);
	TextDrawTextSize(HBE[20], 1.000, 14.000);
	TextDrawAlignment(HBE[20], 1);
	TextDrawColor(HBE[20], -1);
	TextDrawUseBox(HBE[20], 1);
	TextDrawBoxColor(HBE[20], 50);
	TextDrawSetShadow(HBE[20], 0);
	TextDrawSetOutline(HBE[20], 1);
	TextDrawBackgroundColor(HBE[20], 255);
	TextDrawFont(HBE[20], 4);
	TextDrawSetProportional(HBE[20], 1);

	HBE[21] = TextDrawCreate(97.000, 429.000, "ld_dual:white");
	TextDrawLetterSize(HBE[21], 0.600, 2.000);
	TextDrawTextSize(HBE[21], 15.000, 1.000);
	TextDrawAlignment(HBE[21], 1);
	TextDrawColor(HBE[21], -1);
	TextDrawUseBox(HBE[21], 1);
	TextDrawBoxColor(HBE[21], 50);
	TextDrawSetShadow(HBE[21], 0);
	TextDrawSetOutline(HBE[21], 1);
	TextDrawBackgroundColor(HBE[21], 255);
	TextDrawFont(HBE[21], 4);
	TextDrawSetProportional(HBE[21], 1);

	HBE[22] = TextDrawCreate(111.000, 430.000, "ld_dual:white");
	TextDrawLetterSize(HBE[22], 0.600, 2.000);
	TextDrawTextSize(HBE[22], 1.000, 14.000);
	TextDrawAlignment(HBE[22], 1);
	TextDrawColor(HBE[22], -1);
	TextDrawUseBox(HBE[22], 1);
	TextDrawBoxColor(HBE[22], 50);
	TextDrawSetShadow(HBE[22], 0);
	TextDrawSetOutline(HBE[22], 1);
	TextDrawBackgroundColor(HBE[22], 255);
	TextDrawFont(HBE[22], 4);
	TextDrawSetProportional(HBE[22], 1);

	HBE[23] = TextDrawCreate(97.000, 443.000, "ld_dual:white");
	TextDrawLetterSize(HBE[23], 0.600, 2.000);
	TextDrawTextSize(HBE[23], 15.000, 1.000);
	TextDrawAlignment(HBE[23], 1);
	TextDrawColor(HBE[23], -1);
	TextDrawUseBox(HBE[23], 1);
	TextDrawBoxColor(HBE[23], 50);
	TextDrawSetShadow(HBE[23], 0);
	TextDrawSetOutline(HBE[23], 1);
	TextDrawBackgroundColor(HBE[23], 255);
	TextDrawFont(HBE[23], 4);
	TextDrawSetProportional(HBE[23], 1);

	HBE[24] = TextDrawCreate(97.000, 429.000, "ld_dual:white");
	TextDrawLetterSize(HBE[24], 0.600, 2.000);
	TextDrawTextSize(HBE[24], 1.000, 15.000);
	TextDrawAlignment(HBE[24], 1);
	TextDrawColor(HBE[24], -1);
	TextDrawUseBox(HBE[24], 1);
	TextDrawBoxColor(HBE[24], 50);
	TextDrawSetShadow(HBE[24], 0);
	TextDrawSetOutline(HBE[24], 1);
	TextDrawBackgroundColor(HBE[24], 255);
	TextDrawFont(HBE[24], 4);
	TextDrawSetProportional(HBE[24], 1);
}

CreateHBEProgressBarTD(playerid)
{
	//v1
	// Speedometer
	PHBE[playerid][0] = CreatePlayerTextDraw(playerid, 121.000, 414.000, "23:45:35");
	PlayerTextDrawLetterSize(playerid, PHBE[playerid][0], 0.178, 1.098);
	PlayerTextDrawAlignment(playerid, PHBE[playerid][0], 1);
	PlayerTextDrawColor(playerid, PHBE[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, PHBE[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, PHBE[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, PHBE[playerid][0], 255);
	PlayerTextDrawFont(playerid, PHBE[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, PHBE[playerid][0], 1);

	PHBE[playerid][1] = CreatePlayerTextDraw(playerid, 127.000, 425.000, "000");
	PlayerTextDrawLetterSize(playerid, PHBE[playerid][1], 0.178, 1.098);
	PlayerTextDrawAlignment(playerid, PHBE[playerid][1], 2);
	PlayerTextDrawColor(playerid, PHBE[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, PHBE[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, PHBE[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, PHBE[playerid][1], 255);
	PlayerTextDrawFont(playerid, PHBE[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, PHBE[playerid][1], 1);

	PHBE[playerid][2] = CreatePlayerTextDraw(playerid, 156.000, 425.000, "000");
	PlayerTextDrawLetterSize(playerid, PHBE[playerid][2], 0.178, 1.098);
	PlayerTextDrawAlignment(playerid, PHBE[playerid][2], 2);
	PlayerTextDrawColor(playerid, PHBE[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, PHBE[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, PHBE[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, PHBE[playerid][2], 255);
	PlayerTextDrawFont(playerid, PHBE[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, PHBE[playerid][2], 1);

	PHBE[playerid][3] = CreatePlayerTextDraw(playerid, 186.000, 425.000, "000");
	PlayerTextDrawLetterSize(playerid, PHBE[playerid][3], 0.178, 1.098);
	PlayerTextDrawAlignment(playerid, PHBE[playerid][3], 2);
	PlayerTextDrawColor(playerid, PHBE[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, PHBE[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, PHBE[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, PHBE[playerid][3], 255);
	PlayerTextDrawFont(playerid, PHBE[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, PHBE[playerid][3], 1);

	PHBE[playerid][4] = CreatePlayerTextDraw(playerid, 142.000, 436.000, "Southwest");
	PlayerTextDrawLetterSize(playerid, PHBE[playerid][4], 0.187, 1.098);
	PlayerTextDrawAlignment(playerid, PHBE[playerid][4], 2);
	PlayerTextDrawColor(playerid, PHBE[playerid][4], -628031233);
	PlayerTextDrawSetShadow(playerid, PHBE[playerid][4], 1);
	PlayerTextDrawSetOutline(playerid, PHBE[playerid][4], 1);
	PlayerTextDrawBackgroundColor(playerid, PHBE[playerid][4], 25);
	PlayerTextDrawFont(playerid, PHBE[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, PHBE[playerid][4], 1);

	PHBE[playerid][5] = CreatePlayerTextDraw(playerid, 168.000, 437.000, "Bayview Chemicals Avenue I Easter Bay Chemicals");
	PlayerTextDrawLetterSize(playerid, PHBE[playerid][5], 0.158, 0.898);
	PlayerTextDrawAlignment(playerid, PHBE[playerid][5], 1);
	PlayerTextDrawColor(playerid, PHBE[playerid][5], -1);
	PlayerTextDrawSetShadow(playerid, PHBE[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, PHBE[playerid][5], 1);
	PlayerTextDrawBackgroundColor(playerid, PHBE[playerid][5], 25);
	PlayerTextDrawFont(playerid, PHBE[playerid][5], 1);
	PlayerTextDrawSetProportional(playerid, PHBE[playerid][5], 1);

	// HBE
	PHBE[playerid][6] = CreatePlayerTextDraw(playerid, 4.000, 430.000, "ld_dual:white");
	PlayerTextDrawLetterSize(playerid, PHBE[playerid][6], 0.600, 2.000);
	PlayerTextDrawTextSize(playerid, PHBE[playerid][6], 28.000, 13.000);
	PlayerTextDrawAlignment(playerid, PHBE[playerid][6], 1);
	PlayerTextDrawColor(playerid, PHBE[playerid][6], 780883967);
	PlayerTextDrawUseBox(playerid, PHBE[playerid][6], 1);
	PlayerTextDrawBoxColor(playerid, PHBE[playerid][6], 50);
	PlayerTextDrawSetShadow(playerid, PHBE[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, PHBE[playerid][6], 1);
	PlayerTextDrawBackgroundColor(playerid, PHBE[playerid][6], 255);
	PlayerTextDrawFont(playerid, PHBE[playerid][6], 4);
	PlayerTextDrawSetProportional(playerid, PHBE[playerid][6], 1);

	PHBE[playerid][7] = CreatePlayerTextDraw(playerid, 35.000, 430.000, "ld_dual:white");
	PlayerTextDrawLetterSize(playerid, PHBE[playerid][7], 0.600, 2.000);
	PlayerTextDrawTextSize(playerid, PHBE[playerid][7], 28.000, 13.000);
	PlayerTextDrawAlignment(playerid, PHBE[playerid][7], 1);
	PlayerTextDrawColor(playerid, PHBE[playerid][7], -1448498689);
	PlayerTextDrawUseBox(playerid, PHBE[playerid][7], 1);
	PlayerTextDrawBoxColor(playerid, PHBE[playerid][7], 50);
	PlayerTextDrawSetShadow(playerid, PHBE[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, PHBE[playerid][7], 1);
	PlayerTextDrawBackgroundColor(playerid, PHBE[playerid][7], 255);
	PlayerTextDrawFont(playerid, PHBE[playerid][7], 4);
	PlayerTextDrawSetProportional(playerid, PHBE[playerid][7], 1);

	PHBE[playerid][8] = CreatePlayerTextDraw(playerid, 66.000, 443.000, "ld_dual:white");
	PlayerTextDrawLetterSize(playerid, PHBE[playerid][8], 0.600, 2.000);
	PlayerTextDrawTextSize(playerid, PHBE[playerid][8], 13.000, -13.000);
	PlayerTextDrawAlignment(playerid, PHBE[playerid][8], 1);
	PlayerTextDrawColor(playerid, PHBE[playerid][8], -7601921);
	PlayerTextDrawUseBox(playerid, PHBE[playerid][8], 1);
	PlayerTextDrawBoxColor(playerid, PHBE[playerid][8], 50);
	PlayerTextDrawSetShadow(playerid, PHBE[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, PHBE[playerid][8], 1);
	PlayerTextDrawBackgroundColor(playerid, PHBE[playerid][8], 255);
	PlayerTextDrawFont(playerid, PHBE[playerid][8], 4);
	PlayerTextDrawSetProportional(playerid, PHBE[playerid][8], 1);

	PHBE[playerid][9] = CreatePlayerTextDraw(playerid, 82.000, 443.000, "ld_dual:white");
	PlayerTextDrawLetterSize(playerid, PHBE[playerid][9], 0.600, 2.000);
	PlayerTextDrawTextSize(playerid, PHBE[playerid][9], 13.000, -13.000);
	PlayerTextDrawAlignment(playerid, PHBE[playerid][9], 1);
	PlayerTextDrawColor(playerid, PHBE[playerid][9], 52735);
	PlayerTextDrawUseBox(playerid, PHBE[playerid][9], 1);
	PlayerTextDrawBoxColor(playerid, PHBE[playerid][9], 50);
	PlayerTextDrawSetShadow(playerid, PHBE[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, PHBE[playerid][9], 1);
	PlayerTextDrawBackgroundColor(playerid, PHBE[playerid][9], 255);
	PlayerTextDrawFont(playerid, PHBE[playerid][9], 4);
	PlayerTextDrawSetProportional(playerid, PHBE[playerid][9], 1);

	PHBE[playerid][10] = CreatePlayerTextDraw(playerid, 98.000, 443.000, "ld_dual:white");
	PlayerTextDrawLetterSize(playerid, PHBE[playerid][10], 0.600, 2.000);
	PlayerTextDrawTextSize(playerid, PHBE[playerid][10], 13.000, -13.000);
	PlayerTextDrawAlignment(playerid, PHBE[playerid][10], 1);
	PlayerTextDrawColor(playerid, PHBE[playerid][10], -1962934017);
	PlayerTextDrawUseBox(playerid, PHBE[playerid][10], 1);
	PlayerTextDrawBoxColor(playerid, PHBE[playerid][10], 50);
	PlayerTextDrawSetShadow(playerid, PHBE[playerid][10], 0);
	PlayerTextDrawSetOutline(playerid, PHBE[playerid][10], 1);
	PlayerTextDrawBackgroundColor(playerid, PHBE[playerid][10], 255);
	PlayerTextDrawFont(playerid, PHBE[playerid][10], 4);
	PlayerTextDrawSetProportional(playerid, PHBE[playerid][10], 1);

	PHBE[playerid][11] = CreatePlayerTextDraw(playerid, 7.000, 433.000, "HUD:radar_girlfriend");
	PlayerTextDrawLetterSize(playerid, PHBE[playerid][11], 0.600, 2.000);
	PlayerTextDrawTextSize(playerid, PHBE[playerid][11], 6.500, 7.000);
	PlayerTextDrawAlignment(playerid, PHBE[playerid][11], 1);
	PlayerTextDrawColor(playerid, PHBE[playerid][11], -1);
	PlayerTextDrawUseBox(playerid, PHBE[playerid][11], 1);
	PlayerTextDrawBoxColor(playerid, PHBE[playerid][11], 50);
	PlayerTextDrawSetShadow(playerid, PHBE[playerid][11], 0);
	PlayerTextDrawSetOutline(playerid, PHBE[playerid][11], 1);
	PlayerTextDrawBackgroundColor(playerid, PHBE[playerid][11], 255);
	PlayerTextDrawFont(playerid, PHBE[playerid][11], 4);
	PlayerTextDrawSetProportional(playerid, PHBE[playerid][11], 1);

	PHBE[playerid][12] = CreatePlayerTextDraw(playerid, 38.000, 433.000, "HUD:radar_tshirt");
	PlayerTextDrawTextSize(playerid, PHBE[playerid][12], 6.500, 7.000);
	PlayerTextDrawAlignment(playerid, PHBE[playerid][12], 1);
	PlayerTextDrawColor(playerid, PHBE[playerid][12], -1);
	PlayerTextDrawSetShadow(playerid, PHBE[playerid][12], 0);
	PlayerTextDrawSetOutline(playerid, PHBE[playerid][12], 0);
	PlayerTextDrawBackgroundColor(playerid, PHBE[playerid][12], 255);
	PlayerTextDrawFont(playerid, PHBE[playerid][12], 4);
	PlayerTextDrawSetProportional(playerid, PHBE[playerid][12], 1);

	PHBE[playerid][13] = CreatePlayerTextDraw(playerid, 69.195, 433.000, "HUD:radar_burgerShot");
	PlayerTextDrawTextSize(playerid, PHBE[playerid][13], 6.500, 7.000);
	PlayerTextDrawAlignment(playerid, PHBE[playerid][13], 1);
	PlayerTextDrawColor(playerid, PHBE[playerid][13], -1);
	PlayerTextDrawSetShadow(playerid, PHBE[playerid][13], 0);
	PlayerTextDrawSetOutline(playerid, PHBE[playerid][13], 0);
	PlayerTextDrawBackgroundColor(playerid, PHBE[playerid][13], 255);
	PlayerTextDrawFont(playerid, PHBE[playerid][13], 4);
	PlayerTextDrawSetProportional(playerid, PHBE[playerid][13], 1);

	PHBE[playerid][14] = CreatePlayerTextDraw(playerid, 85.195, 433.000, "HUD:radar_centre");
	PlayerTextDrawTextSize(playerid, PHBE[playerid][14], 6.500, 7.000);
	PlayerTextDrawAlignment(playerid, PHBE[playerid][14], 1);
	PlayerTextDrawColor(playerid, PHBE[playerid][14], -1);
	PlayerTextDrawSetShadow(playerid, PHBE[playerid][14], 0);
	PlayerTextDrawSetOutline(playerid, PHBE[playerid][14], 0);
	PlayerTextDrawBackgroundColor(playerid, PHBE[playerid][14], 255);
	PlayerTextDrawFont(playerid, PHBE[playerid][14], 4);
	PlayerTextDrawSetProportional(playerid, PHBE[playerid][14], 1);

	PHBE[playerid][15] = CreatePlayerTextDraw(playerid, 101.300, 433.000, "HUD:radar_waypoint");
	PlayerTextDrawTextSize(playerid, PHBE[playerid][15], 6.500, 7.000);
	PlayerTextDrawAlignment(playerid, PHBE[playerid][15], 1);
	PlayerTextDrawColor(playerid, PHBE[playerid][15], -1);
	PlayerTextDrawSetShadow(playerid, PHBE[playerid][15], 0);
	PlayerTextDrawSetOutline(playerid, PHBE[playerid][15], 0);
	PlayerTextDrawBackgroundColor(playerid, PHBE[playerid][15], 255);
	PlayerTextDrawFont(playerid, PHBE[playerid][15], 4);
	PlayerTextDrawSetProportional(playerid, PHBE[playerid][15], 1);

	// VOICE
	PHBE[playerid][16] = CreatePlayerTextDraw(playerid, 113.000, 429.000, "ld_dual:white");
	PlayerTextDrawLetterSize(playerid, PHBE[playerid][16], 0.600, 2.000);
	PlayerTextDrawTextSize(playerid, PHBE[playerid][16], 3.000, 4.000);
	PlayerTextDrawAlignment(playerid, PHBE[playerid][16], 1);
	PlayerTextDrawColor(playerid, PHBE[playerid][16], -1);
	PlayerTextDrawUseBox(playerid, PHBE[playerid][16], 1);
	PlayerTextDrawBoxColor(playerid, PHBE[playerid][16], 50);
	PlayerTextDrawSetShadow(playerid, PHBE[playerid][16], 0);
	PlayerTextDrawSetOutline(playerid, PHBE[playerid][16], 1);
	PlayerTextDrawBackgroundColor(playerid, PHBE[playerid][16], 255);
	PlayerTextDrawFont(playerid, PHBE[playerid][16], 4);
	PlayerTextDrawSetProportional(playerid, PHBE[playerid][16], 1);

	PHBE[playerid][17] = CreatePlayerTextDraw(playerid, 113.000, 434.500, "ld_dual:white");
	PlayerTextDrawLetterSize(playerid, PHBE[playerid][17], 0.600, 2.000);
	PlayerTextDrawTextSize(playerid, PHBE[playerid][17], 3.000, 4.000);
	PlayerTextDrawAlignment(playerid, PHBE[playerid][17], 1);
	PlayerTextDrawColor(playerid, PHBE[playerid][17], -1);
	PlayerTextDrawUseBox(playerid, PHBE[playerid][17], 1);
	PlayerTextDrawBoxColor(playerid, PHBE[playerid][17], 50);
	PlayerTextDrawSetShadow(playerid, PHBE[playerid][17], 0);
	PlayerTextDrawSetOutline(playerid, PHBE[playerid][17], 1);
	PlayerTextDrawBackgroundColor(playerid, PHBE[playerid][17], 255);
	PlayerTextDrawFont(playerid, PHBE[playerid][17], 4);
	PlayerTextDrawSetProportional(playerid, PHBE[playerid][17], 1);

	PHBE[playerid][18] = CreatePlayerTextDraw(playerid, 113.000, 440.000, "ld_dual:white");
	PlayerTextDrawLetterSize(playerid, PHBE[playerid][18], 0.600, 2.000);
	PlayerTextDrawTextSize(playerid, PHBE[playerid][18], 3.000, 4.000);
	PlayerTextDrawAlignment(playerid, PHBE[playerid][18], 1);
	PlayerTextDrawColor(playerid, PHBE[playerid][18], -1);
	PlayerTextDrawUseBox(playerid, PHBE[playerid][18], 1);
	PlayerTextDrawBoxColor(playerid, PHBE[playerid][18], 50);
	PlayerTextDrawSetShadow(playerid, PHBE[playerid][18], 0);
	PlayerTextDrawSetOutline(playerid, PHBE[playerid][18], 1);
	PlayerTextDrawBackgroundColor(playerid, PHBE[playerid][18], 255);
	PlayerTextDrawFont(playerid, PHBE[playerid][18], 4);
	PlayerTextDrawSetProportional(playerid, PHBE[playerid][18], 1);

	// LOGO
	PHBE[playerid][19] = CreatePlayerTextDraw(playerid, 295.000, 9.298, "ld_dual:white");
	PlayerTextDrawLetterSize(playerid, PHBE[playerid][19], 0.600, 2.000);
	PlayerTextDrawTextSize(playerid, PHBE[playerid][19], 6.000, 24.200);
	PlayerTextDrawAlignment(playerid, PHBE[playerid][19], 1);
	PlayerTextDrawColor(playerid, PHBE[playerid][19], 25);
	PlayerTextDrawUseBox(playerid, PHBE[playerid][19], 1);
	PlayerTextDrawBoxColor(playerid, PHBE[playerid][19], 50);
	PlayerTextDrawSetShadow(playerid, PHBE[playerid][19], 0);
	PlayerTextDrawSetOutline(playerid, PHBE[playerid][19], 1);
	PlayerTextDrawBackgroundColor(playerid, PHBE[playerid][19], 255);
	PlayerTextDrawFont(playerid, PHBE[playerid][19], 4);
	PlayerTextDrawSetProportional(playerid, PHBE[playerid][19], 1);

	PHBE[playerid][20] = CreatePlayerTextDraw(playerid, 286.500, 23.000, "ld_dual:white");
	PlayerTextDrawLetterSize(playerid, PHBE[playerid][20], 0.600, 2.000);
	PlayerTextDrawTextSize(playerid, PHBE[playerid][20], 6.000, 10.500);
	PlayerTextDrawAlignment(playerid, PHBE[playerid][20], 1);
	PlayerTextDrawColor(playerid, PHBE[playerid][20], 25);
	PlayerTextDrawUseBox(playerid, PHBE[playerid][20], 1);
	PlayerTextDrawBoxColor(playerid, PHBE[playerid][20], 50);
	PlayerTextDrawSetShadow(playerid, PHBE[playerid][20], 0);
	PlayerTextDrawSetOutline(playerid, PHBE[playerid][20], 1);
	PlayerTextDrawBackgroundColor(playerid, PHBE[playerid][20], 255);
	PlayerTextDrawFont(playerid, PHBE[playerid][20], 4);
	PlayerTextDrawSetProportional(playerid, PHBE[playerid][20], 1);

	PHBE[playerid][21] = CreatePlayerTextDraw(playerid, 291.000, 18.000, "ld_dual:white");
	PlayerTextDrawLetterSize(playerid, PHBE[playerid][21], 0.600, 2.000);
	PlayerTextDrawTextSize(playerid, PHBE[playerid][21], 5.000, 7.000);
	PlayerTextDrawAlignment(playerid, PHBE[playerid][21], 1);
	PlayerTextDrawColor(playerid, PHBE[playerid][21], 25);
	PlayerTextDrawUseBox(playerid, PHBE[playerid][21], 1);
	PlayerTextDrawBoxColor(playerid, PHBE[playerid][21], 50);
	PlayerTextDrawSetShadow(playerid, PHBE[playerid][21], 0);
	PlayerTextDrawSetOutline(playerid, PHBE[playerid][21], 1);
	PlayerTextDrawBackgroundColor(playerid, PHBE[playerid][21], 255);
	PlayerTextDrawFont(playerid, PHBE[playerid][21], 4);
	PlayerTextDrawSetProportional(playerid, PHBE[playerid][21], 1);

	PHBE[playerid][22] = CreatePlayerTextDraw(playerid, 296.000, 10.298, "ld_dual:white");
	PlayerTextDrawLetterSize(playerid, PHBE[playerid][22], 0.600, 2.000);
	PlayerTextDrawTextSize(playerid, PHBE[playerid][22], 4.000, 21.500);
	PlayerTextDrawAlignment(playerid, PHBE[playerid][22], 1);
	PlayerTextDrawColor(playerid, PHBE[playerid][22], -628031233);
	PlayerTextDrawUseBox(playerid, PHBE[playerid][22], 1);
	PlayerTextDrawBoxColor(playerid, PHBE[playerid][22], 50);
	PlayerTextDrawSetShadow(playerid, PHBE[playerid][22], 0);
	PlayerTextDrawSetOutline(playerid, PHBE[playerid][22], 1);
	PlayerTextDrawBackgroundColor(playerid, PHBE[playerid][22], 255);
	PlayerTextDrawFont(playerid, PHBE[playerid][22], 4);
	PlayerTextDrawSetProportional(playerid, PHBE[playerid][22], 1);

	PHBE[playerid][23] = CreatePlayerTextDraw(playerid, 287.500, 23.000, "ld_dual:white");
	PlayerTextDrawLetterSize(playerid, PHBE[playerid][23], 0.600, 2.000);
	PlayerTextDrawTextSize(playerid, PHBE[playerid][23], 4.000, 9.000);
	PlayerTextDrawAlignment(playerid, PHBE[playerid][23], 1);
	PlayerTextDrawColor(playerid, PHBE[playerid][23], -628031233);
	PlayerTextDrawUseBox(playerid, PHBE[playerid][23], 1);
	PlayerTextDrawBoxColor(playerid, PHBE[playerid][23], 50);
	PlayerTextDrawSetShadow(playerid, PHBE[playerid][23], 0);
	PlayerTextDrawSetOutline(playerid, PHBE[playerid][23], 1);
	PlayerTextDrawBackgroundColor(playerid, PHBE[playerid][23], 255);
	PlayerTextDrawFont(playerid, PHBE[playerid][23], 4);
	PlayerTextDrawSetProportional(playerid, PHBE[playerid][23], 1);

	PHBE[playerid][24] = CreatePlayerTextDraw(playerid, 291.000, 19.000, "ld_dual:white");
	PlayerTextDrawLetterSize(playerid, PHBE[playerid][24], 0.600, 2.000);
	PlayerTextDrawTextSize(playerid, PHBE[playerid][24], 5.000, 5.000);
	PlayerTextDrawAlignment(playerid, PHBE[playerid][24], 1);
	PlayerTextDrawColor(playerid, PHBE[playerid][24], -628031233);
	PlayerTextDrawUseBox(playerid, PHBE[playerid][24], 1);
	PlayerTextDrawBoxColor(playerid, PHBE[playerid][24], 50);
	PlayerTextDrawSetShadow(playerid, PHBE[playerid][24], 0);
	PlayerTextDrawSetOutline(playerid, PHBE[playerid][24], 1);
	PlayerTextDrawBackgroundColor(playerid, PHBE[playerid][24], 255);
	PlayerTextDrawFont(playerid, PHBE[playerid][24], 4);
	PlayerTextDrawSetProportional(playerid, PHBE[playerid][24], 1);

	PHBE[playerid][25] = CreatePlayerTextDraw(playerid, 279.000, 0.000, "P");
	PlayerTextDrawLetterSize(playerid, PHBE[playerid][25], 0.809, 4.197);
	PlayerTextDrawAlignment(playerid, PHBE[playerid][25], 1);
	PlayerTextDrawColor(playerid, PHBE[playerid][25], -16776961);
	PlayerTextDrawSetShadow(playerid, PHBE[playerid][25], 0);
	PlayerTextDrawSetOutline(playerid, PHBE[playerid][25], 1);
	PlayerTextDrawBackgroundColor(playerid, PHBE[playerid][25], 25);
	PlayerTextDrawFont(playerid, PHBE[playerid][25], 1);
	PlayerTextDrawSetProportional(playerid, PHBE[playerid][25], 1);

	PHBE[playerid][26] = CreatePlayerTextDraw(playerid, 303.000, 8.000, "PAHLAWAN");
	PlayerTextDrawLetterSize(playerid, PHBE[playerid][26], 0.307, 1.498);
	PlayerTextDrawAlignment(playerid, PHBE[playerid][26], 1);
	PlayerTextDrawColor(playerid, PHBE[playerid][26], -16776961);
	PlayerTextDrawSetShadow(playerid, PHBE[playerid][26], 0);
	PlayerTextDrawSetOutline(playerid, PHBE[playerid][26], 1);
	PlayerTextDrawBackgroundColor(playerid, PHBE[playerid][26], 25);
	PlayerTextDrawFont(playerid, PHBE[playerid][26], 1);
	PlayerTextDrawSetProportional(playerid, PHBE[playerid][26], 1);

	PHBE[playerid][27] = CreatePlayerTextDraw(playerid, 303.000, 20.000, "ROLEPLAY");
	PlayerTextDrawLetterSize(playerid, PHBE[playerid][27], 0.300, 1.500);
	PlayerTextDrawAlignment(playerid, PHBE[playerid][27], 1);
	PlayerTextDrawColor(playerid, PHBE[playerid][27], -628031233);
	PlayerTextDrawSetShadow(playerid, PHBE[playerid][27], 0);
	PlayerTextDrawSetOutline(playerid, PHBE[playerid][27], 1);
	PlayerTextDrawBackgroundColor(playerid, PHBE[playerid][27], 25);
	PlayerTextDrawFont(playerid, PHBE[playerid][27], 1);
	PlayerTextDrawSetProportional(playerid, PHBE[playerid][27], 1);

	PHBE[playerid][28] = CreatePlayerTextDraw(playerid, 633.000, 437.000, "#THURXPROJECT");
	PlayerTextDrawLetterSize(playerid, PHBE[playerid][28], 0.150, 0.888);
	PlayerTextDrawAlignment(playerid, PHBE[playerid][28], 3);
	PlayerTextDrawColor(playerid, PHBE[playerid][28], -236);
	PlayerTextDrawSetShadow(playerid, PHBE[playerid][28], 0);
	PlayerTextDrawSetOutline(playerid, PHBE[playerid][28], 1);
	PlayerTextDrawBackgroundColor(playerid, PHBE[playerid][28], 10);
	PlayerTextDrawFont(playerid, PHBE[playerid][28], 1);
	PlayerTextDrawSetProportional(playerid, PHBE[playerid][28], 1);
}

CreatePhoneHBE()
{
	PHONE_HBE[0] = TextDrawCreate(542.000, 415.000, "LD_BEAT:chit");
	TextDrawTextSize(PHONE_HBE[0], 50.000, 60.000);
	TextDrawAlignment(PHONE_HBE[0], 1);
	TextDrawColor(PHONE_HBE[0], -1778384641);
	TextDrawSetShadow(PHONE_HBE[0], 0);
	TextDrawSetOutline(PHONE_HBE[0], 0);
	TextDrawBackgroundColor(PHONE_HBE[0], 255);
	TextDrawFont(PHONE_HBE[0], 4);
	TextDrawSetProportional(PHONE_HBE[0], 1);

	PHONE_HBE[1] = TextDrawCreate(463.000, 415.000, "LD_BEAT:chit");
	TextDrawTextSize(PHONE_HBE[1], 50.000, 60.000);
	TextDrawAlignment(PHONE_HBE[1], 1);
	TextDrawColor(PHONE_HBE[1], -1778384641);
	TextDrawSetShadow(PHONE_HBE[1], 0);
	TextDrawSetOutline(PHONE_HBE[1], 0);
	TextDrawBackgroundColor(PHONE_HBE[1], 255);
	TextDrawFont(PHONE_HBE[1], 4);
	TextDrawSetProportional(PHONE_HBE[1], 1);

	PHONE_HBE[2] = TextDrawCreate(487.000, 425.000, "ld_dual:white");
	TextDrawLetterSize(PHONE_HBE[2], 0.600, 2.000);
	TextDrawTextSize(PHONE_HBE[2], 81.000, 30.000);
	TextDrawAlignment(PHONE_HBE[2], 1);
	TextDrawColor(PHONE_HBE[2], -1778384641);
	TextDrawUseBox(PHONE_HBE[2], 1);
	TextDrawBoxColor(PHONE_HBE[2], 50);
	TextDrawSetShadow(PHONE_HBE[2], 0);
	TextDrawSetOutline(PHONE_HBE[2], 1);
	TextDrawBackgroundColor(PHONE_HBE[2], 255);
	TextDrawFont(PHONE_HBE[2], 4);
	TextDrawSetProportional(PHONE_HBE[2], 1);

	PHONE_HBE[3] = TextDrawCreate(545.000, 417.500, "LD_BEAT:chit");
	TextDrawTextSize(PHONE_HBE[3], 45.000, 55.000);
	TextDrawAlignment(PHONE_HBE[3], 1);
	TextDrawColor(PHONE_HBE[3], 255);
	TextDrawSetShadow(PHONE_HBE[3], 0);
	TextDrawSetOutline(PHONE_HBE[3], 0);
	TextDrawBackgroundColor(PHONE_HBE[3], 255);
	TextDrawFont(PHONE_HBE[3], 4);
	TextDrawSetProportional(PHONE_HBE[3], 1);

	PHONE_HBE[4] = TextDrawCreate(465.000, 417.500, "LD_BEAT:chit");
	TextDrawTextSize(PHONE_HBE[4], 45.000, 55.000);
	TextDrawAlignment(PHONE_HBE[4], 1);
	TextDrawColor(PHONE_HBE[4], 255);
	TextDrawSetShadow(PHONE_HBE[4], 0);
	TextDrawSetOutline(PHONE_HBE[4], 0);
	TextDrawBackgroundColor(PHONE_HBE[4], 255);
	TextDrawFont(PHONE_HBE[4], 4);
	TextDrawSetProportional(PHONE_HBE[4], 1);

	PHONE_HBE[5] = TextDrawCreate(485.000, 426.500, "ld_dual:white");
	TextDrawLetterSize(PHONE_HBE[5], 0.600, 2.000);
	TextDrawTextSize(PHONE_HBE[5], 85.000, 28.000);
	TextDrawAlignment(PHONE_HBE[5], 1);
	TextDrawColor(PHONE_HBE[5], 255);
	TextDrawUseBox(PHONE_HBE[5], 1);
	TextDrawBoxColor(PHONE_HBE[5], 50);
	TextDrawSetShadow(PHONE_HBE[5], 0);
	TextDrawSetOutline(PHONE_HBE[5], 1);
	TextDrawBackgroundColor(PHONE_HBE[5], 255);
	TextDrawFont(PHONE_HBE[5], 4);
	TextDrawSetProportional(PHONE_HBE[5], 1);

	PHONE_HBE[6] = TextDrawCreate(549.000, 423.000, "LD_BEAT:chit");
	TextDrawTextSize(PHONE_HBE[6], 35.000, 45.000);
	TextDrawAlignment(PHONE_HBE[6], 1);
	TextDrawColor(PHONE_HBE[6], 673720575);
	TextDrawSetShadow(PHONE_HBE[6], 0);
	TextDrawSetOutline(PHONE_HBE[6], 0);
	TextDrawBackgroundColor(PHONE_HBE[6], 255);
	TextDrawFont(PHONE_HBE[6], 4);
	TextDrawSetProportional(PHONE_HBE[6], 1);

	PHONE_HBE[7] = TextDrawCreate(471.000, 423.000, "LD_BEAT:chit");
	TextDrawTextSize(PHONE_HBE[7], 35.000, 45.000);
	TextDrawAlignment(PHONE_HBE[7], 1);
	TextDrawColor(PHONE_HBE[7], 673720575);
	TextDrawSetShadow(PHONE_HBE[7], 0);
	TextDrawSetOutline(PHONE_HBE[7], 0);
	TextDrawBackgroundColor(PHONE_HBE[7], 255);
	TextDrawFont(PHONE_HBE[7], 4);
	TextDrawSetProportional(PHONE_HBE[7], 1);

	PHONE_HBE[8] = TextDrawCreate(487.000, 430.799, "ld_dual:white");
	TextDrawLetterSize(PHONE_HBE[8], 0.600, 2.000);
	TextDrawTextSize(PHONE_HBE[8], 81.000, 23.000);
	TextDrawAlignment(PHONE_HBE[8], 1);
	TextDrawColor(PHONE_HBE[8], 673720575);
	TextDrawUseBox(PHONE_HBE[8], 1);
	TextDrawBoxColor(PHONE_HBE[8], 50);
	TextDrawSetShadow(PHONE_HBE[8], 0);
	TextDrawSetOutline(PHONE_HBE[8], 1);
	TextDrawBackgroundColor(PHONE_HBE[8], 255);
	TextDrawFont(PHONE_HBE[8], 4);
	TextDrawSetProportional(PHONE_HBE[8], 1);

	PHONE_HBE[9] = TextDrawCreate(531.000, 431.000, "LD_BEAT:chit");
	TextDrawTextSize(PHONE_HBE[9], 15.000, 17.000);
	TextDrawAlignment(PHONE_HBE[9], 1);
	TextDrawColor(PHONE_HBE[9], 255);
	TextDrawSetShadow(PHONE_HBE[9], 0);
	TextDrawSetOutline(PHONE_HBE[9], 0);
	TextDrawBackgroundColor(PHONE_HBE[9], 255);
	TextDrawFont(PHONE_HBE[9], 4);
	TextDrawSetProportional(PHONE_HBE[9], 1);

	PHONE_HBE[10] = TextDrawCreate(510.000, 431.000, "LD_BEAT:chit");
	TextDrawTextSize(PHONE_HBE[10], 15.000, 17.000);
	TextDrawAlignment(PHONE_HBE[10], 1);
	TextDrawColor(PHONE_HBE[10], 255);
	TextDrawSetShadow(PHONE_HBE[10], 0);
	TextDrawSetOutline(PHONE_HBE[10], 0);
	TextDrawBackgroundColor(PHONE_HBE[10], 255);
	TextDrawFont(PHONE_HBE[10], 4);
	TextDrawSetProportional(PHONE_HBE[10], 1);

	PHONE_HBE[11] = TextDrawCreate(518.000, 433.799, "ld_dual:white");
	TextDrawLetterSize(PHONE_HBE[11], 0.600, 2.000);
	TextDrawTextSize(PHONE_HBE[11], 20.000, 11.399);
	TextDrawAlignment(PHONE_HBE[11], 1);
	TextDrawColor(PHONE_HBE[11], 255);
	TextDrawUseBox(PHONE_HBE[11], 1);
	TextDrawBoxColor(PHONE_HBE[11], 50);
	TextDrawSetShadow(PHONE_HBE[11], 0);
	TextDrawSetOutline(PHONE_HBE[11], 1);
	TextDrawBackgroundColor(PHONE_HBE[11], 255);
	TextDrawFont(PHONE_HBE[11], 4);
	TextDrawSetProportional(PHONE_HBE[11], 1);

	PHONE_HBE[12] = TextDrawCreate(535.000, 435.500, "LD_BEAT:chit");
	TextDrawTextSize(PHONE_HBE[12], 6.000, 8.000);
	TextDrawAlignment(PHONE_HBE[12], 1);
	TextDrawColor(PHONE_HBE[12], 421097572);
	TextDrawSetShadow(PHONE_HBE[12], 0);
	TextDrawSetOutline(PHONE_HBE[12], 0);
	TextDrawBackgroundColor(PHONE_HBE[12], 255);
	TextDrawFont(PHONE_HBE[12], 4);
	TextDrawSetProportional(PHONE_HBE[12], 1);

	PHONE_HBE[13] = TextDrawCreate(556.000, 436.799, "ld_dual:white");
	TextDrawLetterSize(PHONE_HBE[13], 0.600, 2.000);
	TextDrawTextSize(PHONE_HBE[13], 2.000, 5.000);
	TextDrawAlignment(PHONE_HBE[13], 1);
	TextDrawColor(PHONE_HBE[13], -1);
	TextDrawUseBox(PHONE_HBE[13], 1);
	TextDrawBoxColor(PHONE_HBE[13], 50);
	TextDrawSetShadow(PHONE_HBE[13], 0);
	TextDrawSetOutline(PHONE_HBE[13], 1);
	TextDrawBackgroundColor(PHONE_HBE[13], 255);
	TextDrawFont(PHONE_HBE[13], 4);
	TextDrawSetProportional(PHONE_HBE[13], 1);

	PHONE_HBE[14] = TextDrawCreate(553.000, 437.799, "ld_dual:white");
	TextDrawLetterSize(PHONE_HBE[14], 0.600, 2.000);
	TextDrawTextSize(PHONE_HBE[14], 2.000, 4.000);
	TextDrawAlignment(PHONE_HBE[14], 1);
	TextDrawColor(PHONE_HBE[14], -1);
	TextDrawUseBox(PHONE_HBE[14], 1);
	TextDrawBoxColor(PHONE_HBE[14], 50);
	TextDrawSetShadow(PHONE_HBE[14], 0);
	TextDrawSetOutline(PHONE_HBE[14], 1);
	TextDrawBackgroundColor(PHONE_HBE[14], 255);
	TextDrawFont(PHONE_HBE[14], 4);
	TextDrawSetProportional(PHONE_HBE[14], 1);

	PHONE_HBE[15] = TextDrawCreate(550.000, 438.799, "ld_dual:white");
	TextDrawLetterSize(PHONE_HBE[15], 0.600, 2.000);
	TextDrawTextSize(PHONE_HBE[15], 2.000, 3.000);
	TextDrawAlignment(PHONE_HBE[15], 1);
	TextDrawColor(PHONE_HBE[15], -1);
	TextDrawUseBox(PHONE_HBE[15], 1);
	TextDrawBoxColor(PHONE_HBE[15], 50);
	TextDrawSetShadow(PHONE_HBE[15], 0);
	TextDrawSetOutline(PHONE_HBE[15], 1);
	TextDrawBackgroundColor(PHONE_HBE[15], 255);
	TextDrawFont(PHONE_HBE[15], 4);
	TextDrawSetProportional(PHONE_HBE[15], 1);

	PHONE_HBE[16] = TextDrawCreate(547.000, 439.799, "ld_dual:white");
	TextDrawLetterSize(PHONE_HBE[16], 0.600, 2.000);
	TextDrawTextSize(PHONE_HBE[16], 2.000, 2.000);
	TextDrawAlignment(PHONE_HBE[16], 1);
	TextDrawColor(PHONE_HBE[16], -1);
	TextDrawUseBox(PHONE_HBE[16], 1);
	TextDrawBoxColor(PHONE_HBE[16], 50);
	TextDrawSetShadow(PHONE_HBE[16], 0);
	TextDrawSetOutline(PHONE_HBE[16], 1);
	TextDrawBackgroundColor(PHONE_HBE[16], 255);
	TextDrawFont(PHONE_HBE[16], 4);
	TextDrawSetProportional(PHONE_HBE[16], 1);

	PHONE_HBE[17] = TextDrawCreate(561.000, 436.799, "ld_dual:white");
	TextDrawLetterSize(PHONE_HBE[17], 0.600, 2.000);
	TextDrawTextSize(PHONE_HBE[17], 10.000, 5.000);
	TextDrawAlignment(PHONE_HBE[17], 1);
	TextDrawColor(PHONE_HBE[17], -1);
	TextDrawUseBox(PHONE_HBE[17], 1);
	TextDrawBoxColor(PHONE_HBE[17], 50);
	TextDrawSetShadow(PHONE_HBE[17], 0);
	TextDrawSetOutline(PHONE_HBE[17], 1);
	TextDrawBackgroundColor(PHONE_HBE[17], 255);
	TextDrawFont(PHONE_HBE[17], 4);
	TextDrawSetProportional(PHONE_HBE[17], 1);

	PHONE_HBE[18] = TextDrawCreate(495.000, 435.000, "7:00");
	TextDrawLetterSize(PHONE_HBE[18], 0.150, 0.799);
	TextDrawAlignment(PHONE_HBE[18], 2);
	TextDrawColor(PHONE_HBE[18], -1);
	TextDrawSetShadow(PHONE_HBE[18], 0);
	TextDrawSetOutline(PHONE_HBE[18], 1);
	TextDrawBackgroundColor(PHONE_HBE[18], -236);
	TextDrawFont(PHONE_HBE[18], 1);
	TextDrawSetProportional(PHONE_HBE[18], 1);

	PHONE_HBE[19] = TextDrawCreate(566.000, 436.000, "100");
	TextDrawLetterSize(PHONE_HBE[19], 0.108, 0.699);
	TextDrawAlignment(PHONE_HBE[19], 2);
	TextDrawColor(PHONE_HBE[19], 255);
	TextDrawSetShadow(PHONE_HBE[19], 0);
	TextDrawSetOutline(PHONE_HBE[19], 1);
	TextDrawBackgroundColor(PHONE_HBE[19], -236);
	TextDrawFont(PHONE_HBE[19], 1);
	TextDrawSetProportional(PHONE_HBE[19], 1);

	PHONE_HBE[20] = TextDrawCreate(572.000, 437.799, "ld_dual:white");
	TextDrawLetterSize(PHONE_HBE[20], 0.600, 2.000);
	TextDrawTextSize(PHONE_HBE[20], 1.000, 3.000);
	TextDrawAlignment(PHONE_HBE[20], 1);
	TextDrawColor(PHONE_HBE[20], -1);
	TextDrawUseBox(PHONE_HBE[20], 1);
	TextDrawBoxColor(PHONE_HBE[20], 50);
	TextDrawSetShadow(PHONE_HBE[20], 0);
	TextDrawSetOutline(PHONE_HBE[20], 1);
	TextDrawBackgroundColor(PHONE_HBE[20], 255);
	TextDrawFont(PHONE_HBE[20], 4);
	TextDrawSetProportional(PHONE_HBE[20], 1);
}

CreateStressTD()
{
    StressTD = TextDrawCreate(322.000000, -1.000000, "_");
    TextDrawFont(StressTD, true);
    TextDrawLetterSize(StressTD, 0.600000, 56.800003);
    TextDrawTextSize(StressTD, 298.500000, 675.000000);
    TextDrawSetOutline(StressTD, true);
    TextDrawSetShadow(StressTD, false);
    TextDrawAlignment(StressTD, 2);
    TextDrawColor(StressTD, -1);
    TextDrawBackgroundColor(StressTD,  155);
    TextDrawBoxColor(StressTD, 35634);
    TextDrawUseBox(StressTD, true);
    TextDrawSetProportional(StressTD, true);
    TextDrawSetSelectable(StressTD, false);
}

//V1
ShowHBETD(playerid)
{
    for(new x = 5; x < 25; x++)
	{
        TextDrawShowForPlayer(playerid, HBE[x]);
    }
    for(new x = 6; x < 16; x++)
    {
        PlayerTextDrawShow(playerid, PHBE[playerid][x]);
    }

	switch(pVoiceDistanceStatus[playerid])
	{
		case 0: // Teriak
		{
			PlayerTextDrawShow(playerid, PHBE[playerid][18]); // Voice 1
			PlayerTextDrawShow(playerid, PHBE[playerid][17]); // Voice 2
			PlayerTextDrawShow(playerid, PHBE[playerid][16]); // Voice 3
		}
		case 1: // Normal
		{
			PlayerTextDrawShow(playerid, PHBE[playerid][18]); // Voice 1
			PlayerTextDrawShow(playerid, PHBE[playerid][17]); // Voice 2
			PlayerTextDrawHide(playerid, PHBE[playerid][16]); // Voice 3
		}
		case 2: // Bisik
		{
			PlayerTextDrawShow(playerid, PHBE[playerid][18]); // Voice 1
			PlayerTextDrawHide(playerid, PHBE[playerid][17]); // Voice 2
			PlayerTextDrawHide(playerid, PHBE[playerid][16]); // Voice 3
		}
	}

	// Phone
	for (new y = 0; y < 21; y++)
	{
		TextDrawShowForPlayer(playerid, PHONE_HBE[y]);
	}

	HBETDHidden[playerid] = false;
}

HideHBETD(playerid)
{
    for(new x = 5; x < 25; x++)
	{
        TextDrawHideForPlayer(playerid, HBE[x]);
    }
    for(new x = 6; x < 16; x++)
    {
        PlayerTextDrawHide(playerid, PHBE[playerid][x]);
    }

	PlayerTextDrawHide(playerid, PHBE[playerid][18]); // Voice 1
	PlayerTextDrawHide(playerid, PHBE[playerid][17]); // Voice 2
	PlayerTextDrawHide(playerid, PHBE[playerid][16]); // Voice 3

	// Phone
	for (new y = 0; y < 21; y++)
	{
		TextDrawHideForPlayer(playerid, PHONE_HBE[y]);
	}

	HBETDHidden[playerid] = true;
}

ShowSpeedoTD(playerid)
{
    for(new x; x < 5; x++)
    {
        TextDrawShowForPlayer(playerid, HBE[x]);
	}

	for(new x; x < 6; x++)
	{
        PlayerTextDrawShow(playerid, PHBE[playerid][x]);
    }
}

HideSpeedoTD(playerid)
{
    for(new x; x < 5; x++)
    {
        TextDrawHideForPlayer(playerid, HBE[x]);
	}

	for(new x; x < 6; x++)
	{
        PlayerTextDrawHide(playerid, PHBE[playerid][x]);
    }
}

ShowStressEffectTD(playerid)
{
    TextDrawShowForPlayer(playerid, StressTD);
}

HideStressEffectTD(playerid)
{
    TextDrawHideForPlayer(playerid, StressTD);
}