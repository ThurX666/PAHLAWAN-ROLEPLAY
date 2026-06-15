new Text:ATMTD[88],
    PlayerText:ATMPTD[MAX_PLAYERS][4];

CreateATMTD()
{
	ATMTD[0] = TextDrawCreate(165.199, 89.000, "ld_beat:chit");
	TextDrawTextSize(ATMTD[0], 10.000, 12.000);
	TextDrawAlignment(ATMTD[0], 1);
	TextDrawColor(ATMTD[0], -185075201);
	TextDrawSetShadow(ATMTD[0], 0);
	TextDrawSetOutline(ATMTD[0], 0);
	TextDrawBackgroundColor(ATMTD[0], 255);
	TextDrawFont(ATMTD[0], 4);
	TextDrawSetProportional(ATMTD[0], 1);

	ATMTD[1] = TextDrawCreate(464.199, 89.000, "ld_beat:chit");
	TextDrawTextSize(ATMTD[1], 10.000, 12.000);
	TextDrawAlignment(ATMTD[1], 1);
	TextDrawColor(ATMTD[1], -185075201);
	TextDrawSetShadow(ATMTD[1], 0);
	TextDrawSetOutline(ATMTD[1], 0);
	TextDrawBackgroundColor(ATMTD[1], 255);
	TextDrawFont(ATMTD[1], 4);
	TextDrawSetProportional(ATMTD[1], 1);

	ATMTD[2] = TextDrawCreate(464.199, 345.000, "ld_beat:chit");
	TextDrawTextSize(ATMTD[2], 10.000, 12.000);
	TextDrawAlignment(ATMTD[2], 1);
	TextDrawColor(ATMTD[2], -185075201);
	TextDrawSetShadow(ATMTD[2], 0);
	TextDrawSetOutline(ATMTD[2], 0);
	TextDrawBackgroundColor(ATMTD[2], 255);
	TextDrawFont(ATMTD[2], 4);
	TextDrawSetProportional(ATMTD[2], 1);

	ATMTD[3] = TextDrawCreate(165.199, 345.000, "ld_beat:chit");
	TextDrawTextSize(ATMTD[3], 10.000, 12.000);
	TextDrawAlignment(ATMTD[3], 1);
	TextDrawColor(ATMTD[3], -185075201);
	TextDrawSetShadow(ATMTD[3], 0);
	TextDrawSetOutline(ATMTD[3], 0);
	TextDrawBackgroundColor(ATMTD[3], 255);
	TextDrawFont(ATMTD[3], 4);
	TextDrawSetProportional(ATMTD[3], 1);

	ATMTD[4] = TextDrawCreate(170.500, 91.000, "ld_dual:white");
	TextDrawTextSize(ATMTD[4], 298.000, 5.000);
	TextDrawAlignment(ATMTD[4], 1);
	TextDrawColor(ATMTD[4], -185075201);
	TextDrawSetShadow(ATMTD[4], 0);
	TextDrawSetOutline(ATMTD[4], 0);
	TextDrawBackgroundColor(ATMTD[4], 255);
	TextDrawFont(ATMTD[4], 4);
	TextDrawSetProportional(ATMTD[4], 1);

	ATMTD[5] = TextDrawCreate(166.500, 95.000, "ld_dual:white");
	TextDrawTextSize(ATMTD[5], 5.000, 256.000);
	TextDrawAlignment(ATMTD[5], 1);
	TextDrawColor(ATMTD[5], -185075201);
	TextDrawSetShadow(ATMTD[5], 0);
	TextDrawSetOutline(ATMTD[5], 0);
	TextDrawBackgroundColor(ATMTD[5], 255);
	TextDrawFont(ATMTD[5], 4);
	TextDrawSetProportional(ATMTD[5], 1);

	ATMTD[6] = TextDrawCreate(467.500, 95.000, "ld_dual:white");
	TextDrawTextSize(ATMTD[6], 5.000, 256.000);
	TextDrawAlignment(ATMTD[6], 1);
	TextDrawColor(ATMTD[6], -185075201);
	TextDrawSetShadow(ATMTD[6], 0);
	TextDrawSetOutline(ATMTD[6], 0);
	TextDrawBackgroundColor(ATMTD[6], 255);
	TextDrawFont(ATMTD[6], 4);
	TextDrawSetProportional(ATMTD[6], 1);

	ATMTD[7] = TextDrawCreate(170.500, 350.000, "ld_dual:white");
	TextDrawTextSize(ATMTD[7], 298.000, 5.000);
	TextDrawAlignment(ATMTD[7], 1);
	TextDrawColor(ATMTD[7], -185075201);
	TextDrawSetShadow(ATMTD[7], 0);
	TextDrawSetOutline(ATMTD[7], 0);
	TextDrawBackgroundColor(ATMTD[7], 255);
	TextDrawFont(ATMTD[7], 4);
	TextDrawSetProportional(ATMTD[7], 1);

	ATMTD[8] = TextDrawCreate(170.000, 96.000, "ld_dual:white");
	TextDrawTextSize(ATMTD[8], 299.500, 256.000);
	TextDrawAlignment(ATMTD[8], 1);
	TextDrawColor(ATMTD[8], -185075201);
	TextDrawSetShadow(ATMTD[8], 0);
	TextDrawSetOutline(ATMTD[8], 0);
	TextDrawBackgroundColor(ATMTD[8], 255);
	TextDrawFont(ATMTD[8], 4);
	TextDrawSetProportional(ATMTD[8], 1);

	ATMTD[9] = TextDrawCreate(174.000, 122.000, "ld_dual:white");
	TextDrawTextSize(ATMTD[9], 292.000, 1.500);
	TextDrawAlignment(ATMTD[9], 1);
	TextDrawColor(ATMTD[9], -504828161);
	TextDrawSetShadow(ATMTD[9], 0);
	TextDrawSetOutline(ATMTD[9], 0);
	TextDrawBackgroundColor(ATMTD[9], 255);
	TextDrawFont(ATMTD[9], 4);
	TextDrawSetProportional(ATMTD[9], 1);

	ATMTD[10] = TextDrawCreate(174.000, 255.000, "ld_dual:white");
	TextDrawTextSize(ATMTD[10], 292.000, 1.500);
	TextDrawAlignment(ATMTD[10], 1);
	TextDrawColor(ATMTD[10], -504828161);
	TextDrawSetShadow(ATMTD[10], 0);
	TextDrawSetOutline(ATMTD[10], 0);
	TextDrawBackgroundColor(ATMTD[10], 255);
	TextDrawFont(ATMTD[10], 4);
	TextDrawSetProportional(ATMTD[10], 1);

	ATMTD[11] = TextDrawCreate(172.000, 95.000, "FL");
	TextDrawLetterSize(ATMTD[11], 0.349, 1.500);
	TextDrawTextSize(ATMTD[11], 1.000, 0.000);
	TextDrawAlignment(ATMTD[11], 1);
	TextDrawColor(ATMTD[11], 255);
	TextDrawSetShadow(ATMTD[11], 0);
	TextDrawSetOutline(ATMTD[11], 0);
	TextDrawBackgroundColor(ATMTD[11], 150);
	TextDrawFont(ATMTD[11], 1);
	TextDrawSetProportional(ATMTD[11], 1);

	ATMTD[12] = TextDrawCreate(184.000, 95.000, "EE");
	TextDrawLetterSize(ATMTD[12], 0.349, 1.500);
	TextDrawTextSize(ATMTD[12], 1.000, 0.000);
	TextDrawAlignment(ATMTD[12], 1);
	TextDrawColor(ATMTD[12], 684158975);
	TextDrawSetShadow(ATMTD[12], 0);
	TextDrawSetOutline(ATMTD[12], 0);
	TextDrawBackgroundColor(ATMTD[12], 150);
	TextDrawFont(ATMTD[12], 1);
	TextDrawSetProportional(ATMTD[12], 1);

	ATMTD[13] = TextDrawCreate(195.000, 95.000, "CA");
	TextDrawLetterSize(ATMTD[13], 0.349, 1.500);
	TextDrawTextSize(ATMTD[13], 1.000, 0.000);
	TextDrawAlignment(ATMTD[13], 1);
	TextDrawColor(ATMTD[13], 255);
	TextDrawSetShadow(ATMTD[13], 0);
	TextDrawSetOutline(ATMTD[13], 0);
	TextDrawBackgroundColor(ATMTD[13], 150);
	TextDrawFont(ATMTD[13], 1);
	TextDrawSetProportional(ATMTD[13], 1);

	ATMTD[14] = TextDrawCreate(213.000, 97.000, "BANK - ATM");
	TextDrawLetterSize(ATMTD[14], 0.216, 1.098);
	TextDrawTextSize(ATMTD[14], 412.000, 0.000);
	TextDrawAlignment(ATMTD[14], 1);
	TextDrawColor(ATMTD[14], 2021954047);
	TextDrawSetShadow(ATMTD[14], 0);
	TextDrawSetOutline(ATMTD[14], 0);
	TextDrawBackgroundColor(ATMTD[14], 150);
	TextDrawFont(ATMTD[14], 1);
	TextDrawSetProportional(ATMTD[14], 1);

	ATMTD[15] = TextDrawCreate(440.500, 100.000, "LD_BUM:blkdot");
	TextDrawTextSize(ATMTD[15], 26.000, 13.500);
	TextDrawAlignment(ATMTD[15], 1);
	TextDrawColor(ATMTD[15], -504828161);
	TextDrawSetShadow(ATMTD[15], 0);
	TextDrawSetOutline(ATMTD[15], 0);
	TextDrawBackgroundColor(ATMTD[15], 255);
	TextDrawFont(ATMTD[15], 4);
	TextDrawSetProportional(ATMTD[15], 1);

	ATMTD[16] = TextDrawCreate(441.500, 101.000, "LD_BUM:blkdot");
	TextDrawTextSize(ATMTD[16], 24.000, 11.500);
	TextDrawAlignment(ATMTD[16], 1);
	TextDrawColor(ATMTD[16], -1);
	TextDrawSetShadow(ATMTD[16], 0);
	TextDrawSetOutline(ATMTD[16], 0);
	TextDrawBackgroundColor(ATMTD[16], 255);
	TextDrawFont(ATMTD[16], 4);
	TextDrawSetProportional(ATMTD[16], 1);
	TextDrawSetSelectable(ATMTD[16], 1);

	ATMTD[17] = TextDrawCreate(453.500, 102.500, "EXIT");
	TextDrawLetterSize(ATMTD[17], 0.178, 0.898);
	TextDrawTextSize(ATMTD[17], 412.000, 0.000);
	TextDrawAlignment(ATMTD[17], 2);
	TextDrawColor(ATMTD[17], 255);
	TextDrawSetShadow(ATMTD[17], 0);
	TextDrawSetOutline(ATMTD[17], 0);
	TextDrawBackgroundColor(ATMTD[17], 150);
	TextDrawFont(ATMTD[17], 1);
	TextDrawSetProportional(ATMTD[17], 1);

	ATMTD[18] = TextDrawCreate(189.000, 139.000, "ld_dual:white");
	TextDrawTextSize(ATMTD[18], 86.000, 62.000);
	TextDrawAlignment(ATMTD[18], 1);
	TextDrawColor(ATMTD[18], -504828161);
	TextDrawSetShadow(ATMTD[18], 0);
	TextDrawSetOutline(ATMTD[18], 0);
	TextDrawBackgroundColor(ATMTD[18], 255);
	TextDrawFont(ATMTD[18], 4);
	TextDrawSetProportional(ATMTD[18], 1);

	ATMTD[19] = TextDrawCreate(277.000, 139.000, "ld_dual:white");
	TextDrawTextSize(ATMTD[19], 86.000, 62.000);
	TextDrawAlignment(ATMTD[19], 1);
	TextDrawColor(ATMTD[19], -504828161);
	TextDrawSetShadow(ATMTD[19], 0);
	TextDrawSetOutline(ATMTD[19], 0);
	TextDrawBackgroundColor(ATMTD[19], 255);
	TextDrawFont(ATMTD[19], 4);
	TextDrawSetProportional(ATMTD[19], 1);

	ATMTD[20] = TextDrawCreate(365.000, 139.000, "ld_dual:white");
	TextDrawTextSize(ATMTD[20], 86.000, 62.000);
	TextDrawAlignment(ATMTD[20], 1);
	TextDrawColor(ATMTD[20], -504828161);
	TextDrawSetShadow(ATMTD[20], 0);
	TextDrawSetOutline(ATMTD[20], 0);
	TextDrawBackgroundColor(ATMTD[20], 255);
	TextDrawFont(ATMTD[20], 4);
	TextDrawSetProportional(ATMTD[20], 1);

	ATMTD[21] = TextDrawCreate(190.000, 140.000, "ld_dual:white");
	TextDrawTextSize(ATMTD[21], 84.000, 60.000);
	TextDrawAlignment(ATMTD[21], 1);
	TextDrawColor(ATMTD[21], -1);
	TextDrawSetShadow(ATMTD[21], 0);
	TextDrawSetOutline(ATMTD[21], 0);
	TextDrawBackgroundColor(ATMTD[21], 255);
	TextDrawFont(ATMTD[21], 4);
	TextDrawSetProportional(ATMTD[21], 1);

	ATMTD[22] = TextDrawCreate(278.000, 140.000, "ld_dual:white");
	TextDrawTextSize(ATMTD[22], 84.000, 60.000);
	TextDrawAlignment(ATMTD[22], 1);
	TextDrawColor(ATMTD[22], -1);
	TextDrawSetShadow(ATMTD[22], 0);
	TextDrawSetOutline(ATMTD[22], 0);
	TextDrawBackgroundColor(ATMTD[22], 255);
	TextDrawFont(ATMTD[22], 4);
	TextDrawSetProportional(ATMTD[22], 1);

	ATMTD[23] = TextDrawCreate(366.000, 140.000, "ld_dual:white");
	TextDrawTextSize(ATMTD[23], 84.000, 60.000);
	TextDrawAlignment(ATMTD[23], 1);
	TextDrawColor(ATMTD[23], -1);
	TextDrawSetShadow(ATMTD[23], 0);
	TextDrawSetOutline(ATMTD[23], 0);
	TextDrawBackgroundColor(ATMTD[23], 255);
	TextDrawFont(ATMTD[23], 4);
	TextDrawSetProportional(ATMTD[23], 1);

	ATMTD[24] = TextDrawCreate(320.000, 143.000, "Bank Account Number");
	TextDrawLetterSize(ATMTD[24], 0.158, 0.898);
	TextDrawAlignment(ATMTD[24], 2);
	TextDrawColor(ATMTD[24], 2021954047);
	TextDrawSetShadow(ATMTD[24], 1);
	TextDrawSetOutline(ATMTD[24], 1);
	TextDrawBackgroundColor(ATMTD[24], 0);
	TextDrawFont(ATMTD[24], 1);
	TextDrawSetProportional(ATMTD[24], 1);

	ATMTD[25] = TextDrawCreate(231.000, 143.000, "Current Bank Balance");
	TextDrawLetterSize(ATMTD[25], 0.158, 0.898);
	TextDrawAlignment(ATMTD[25], 2);
	TextDrawColor(ATMTD[25], 2021954047);
	TextDrawSetShadow(ATMTD[25], 1);
	TextDrawSetOutline(ATMTD[25], 1);
	TextDrawBackgroundColor(ATMTD[25], 0);
	TextDrawFont(ATMTD[25], 1);
	TextDrawSetProportional(ATMTD[25], 1);

	ATMTD[26] = TextDrawCreate(409.000, 143.000, "Current Cash Balance");
	TextDrawLetterSize(ATMTD[26], 0.158, 0.898);
	TextDrawAlignment(ATMTD[26], 2);
	TextDrawColor(ATMTD[26], 2021954047);
	TextDrawSetShadow(ATMTD[26], 1);
	TextDrawSetOutline(ATMTD[26], 1);
	TextDrawBackgroundColor(ATMTD[26], 0);
	TextDrawFont(ATMTD[26], 1);
	TextDrawSetProportional(ATMTD[26], 1);

	ATMTD[27] = TextDrawCreate(320.000, 190.000, "LIMIT TRANSFER : $50.000.000");
	TextDrawLetterSize(ATMTD[27], 0.108, 0.597);
	TextDrawAlignment(ATMTD[27], 2);
	TextDrawColor(ATMTD[27], 2021954047);
	TextDrawSetShadow(ATMTD[27], 1);
	TextDrawSetOutline(ATMTD[27], 1);
	TextDrawBackgroundColor(ATMTD[27], 0);
	TextDrawFont(ATMTD[27], 1);
	TextDrawSetProportional(ATMTD[27], 1);

	ATMTD[28] = TextDrawCreate(189.000, 204.000, "ld_dual:white");
	TextDrawTextSize(ATMTD[28], 86.000, 34.000);
	TextDrawAlignment(ATMTD[28], 1);
	TextDrawColor(ATMTD[28], -504828161);
	TextDrawSetShadow(ATMTD[28], 0);
	TextDrawSetOutline(ATMTD[28], 0);
	TextDrawBackgroundColor(ATMTD[28], 255);
	TextDrawFont(ATMTD[28], 4);
	TextDrawSetProportional(ATMTD[28], 1);

	ATMTD[29] = TextDrawCreate(277.000, 204.000, "ld_dual:white");
	TextDrawTextSize(ATMTD[29], 86.000, 34.000);
	TextDrawAlignment(ATMTD[29], 1);
	TextDrawColor(ATMTD[29], -504828161);
	TextDrawSetShadow(ATMTD[29], 0);
	TextDrawSetOutline(ATMTD[29], 0);
	TextDrawBackgroundColor(ATMTD[29], 255);
	TextDrawFont(ATMTD[29], 4);
	TextDrawSetProportional(ATMTD[29], 1);

	ATMTD[30] = TextDrawCreate(365.000, 204.000, "ld_dual:white");
	TextDrawTextSize(ATMTD[30], 86.000, 34.000);
	TextDrawAlignment(ATMTD[30], 1);
	TextDrawColor(ATMTD[30], -504828161);
	TextDrawSetShadow(ATMTD[30], 0);
	TextDrawSetOutline(ATMTD[30], 0);
	TextDrawBackgroundColor(ATMTD[30], 255);
	TextDrawFont(ATMTD[30], 4);
	TextDrawSetProportional(ATMTD[30], 1);

	ATMTD[31] = TextDrawCreate(190.000, 205.000, "ld_dual:white");
	TextDrawTextSize(ATMTD[31], 84.000, 32.000);
	TextDrawAlignment(ATMTD[31], 1);
	TextDrawColor(ATMTD[31], -1);
	TextDrawSetShadow(ATMTD[31], 0);
	TextDrawSetOutline(ATMTD[31], 0);
	TextDrawBackgroundColor(ATMTD[31], 255);
	TextDrawFont(ATMTD[31], 4);
	TextDrawSetProportional(ATMTD[31], 1);

	ATMTD[32] = TextDrawCreate(278.000, 205.000, "ld_dual:white");
	TextDrawTextSize(ATMTD[32], 84.000, 32.000);
	TextDrawAlignment(ATMTD[32], 1);
	TextDrawColor(ATMTD[32], -1);
	TextDrawSetShadow(ATMTD[32], 0);
	TextDrawSetOutline(ATMTD[32], 0);
	TextDrawBackgroundColor(ATMTD[32], 255);
	TextDrawFont(ATMTD[32], 4);
	TextDrawSetProportional(ATMTD[32], 1);

	ATMTD[33] = TextDrawCreate(366.000, 205.000, "ld_dual:white");
	TextDrawTextSize(ATMTD[33], 84.000, 32.000);
	TextDrawAlignment(ATMTD[33], 1);
	TextDrawColor(ATMTD[33], -1);
	TextDrawSetShadow(ATMTD[33], 0);
	TextDrawSetOutline(ATMTD[33], 0);
	TextDrawBackgroundColor(ATMTD[33], 255);
	TextDrawFont(ATMTD[33], 4);
	TextDrawSetProportional(ATMTD[33], 1);

	ATMTD[34] = TextDrawCreate(196.000, 209.000, "Withdraw");
	TextDrawLetterSize(ATMTD[34], 0.158, 0.898);
	TextDrawAlignment(ATMTD[34], 1);
	TextDrawColor(ATMTD[34], 2021954047);
	TextDrawSetShadow(ATMTD[34], 1);
	TextDrawSetOutline(ATMTD[34], 1);
	TextDrawBackgroundColor(ATMTD[34], 0);
	TextDrawFont(ATMTD[34], 1);
	TextDrawSetProportional(ATMTD[34], 1);

	ATMTD[35] = TextDrawCreate(285.000, 209.000, "Deposit");
	TextDrawLetterSize(ATMTD[35], 0.158, 0.898);
	TextDrawAlignment(ATMTD[35], 1);
	TextDrawColor(ATMTD[35], 2021954047);
	TextDrawSetShadow(ATMTD[35], 1);
	TextDrawSetOutline(ATMTD[35], 1);
	TextDrawBackgroundColor(ATMTD[35], 0);
	TextDrawFont(ATMTD[35], 1);
	TextDrawSetProportional(ATMTD[35], 1);

	ATMTD[36] = TextDrawCreate(374.000, 209.000, "Transfer");
	TextDrawLetterSize(ATMTD[36], 0.158, 0.898);
	TextDrawAlignment(ATMTD[36], 1);
	TextDrawColor(ATMTD[36], 2021954047);
	TextDrawSetShadow(ATMTD[36], 1);
	TextDrawSetOutline(ATMTD[36], 1);
	TextDrawBackgroundColor(ATMTD[36], 0);
	TextDrawFont(ATMTD[36], 1);
	TextDrawSetProportional(ATMTD[36], 1);

	ATMTD[37] = TextDrawCreate(248.000, 207.000, "LD_BEAT:chit");
	TextDrawTextSize(ATMTD[37], 24.000, 29.000);
	TextDrawAlignment(ATMTD[37], 1);
	TextDrawColor(ATMTD[37], 684158975);
	TextDrawSetShadow(ATMTD[37], 0);
	TextDrawSetOutline(ATMTD[37], 0);
	TextDrawBackgroundColor(ATMTD[37], 255);
	TextDrawFont(ATMTD[37], 4);
	TextDrawSetProportional(ATMTD[37], 1);
	TextDrawSetSelectable(ATMTD[37], 1);

	ATMTD[38] = TextDrawCreate(256.500, 221.000, "LD_BUM:blkdot");
	TextDrawTextSize(ATMTD[38], 6.000, 1.000);
	TextDrawAlignment(ATMTD[38], 1);
	TextDrawColor(ATMTD[38], -1);
	TextDrawSetShadow(ATMTD[38], 0);
	TextDrawSetOutline(ATMTD[38], 0);
	TextDrawBackgroundColor(ATMTD[38], 255);
	TextDrawFont(ATMTD[38], 4);
	TextDrawSetProportional(ATMTD[38], 1);

	ATMTD[39] = TextDrawCreate(260.500, 214.298, ">");
	TextDrawLetterSize(ATMTD[39], 0.136, 1.500);
	TextDrawTextSize(ATMTD[39], 0.000, 1.000);
	TextDrawAlignment(ATMTD[39], 1);
	TextDrawColor(ATMTD[39], -1);
	TextDrawSetShadow(ATMTD[39], 1);
	TextDrawSetOutline(ATMTD[39], 1);
	TextDrawBackgroundColor(ATMTD[39], 0);
	TextDrawFont(ATMTD[39], 1);
	TextDrawSetProportional(ATMTD[39], 1);

	ATMTD[40] = TextDrawCreate(336.000, 206.000, "LD_BEAT:chit");
	TextDrawTextSize(ATMTD[40], 24.000, 29.000);
	TextDrawAlignment(ATMTD[40], 1);
	TextDrawColor(ATMTD[40], 684158975);
	TextDrawSetShadow(ATMTD[40], 0);
	TextDrawSetOutline(ATMTD[40], 0);
	TextDrawBackgroundColor(ATMTD[40], 255);
	TextDrawFont(ATMTD[40], 4);
	TextDrawSetProportional(ATMTD[40], 1);
	TextDrawSetSelectable(ATMTD[40], 1);

	ATMTD[41] = TextDrawCreate(344.500, 220.000, "LD_BUM:blkdot");
	TextDrawTextSize(ATMTD[41], 6.000, 1.000);
	TextDrawAlignment(ATMTD[41], 1);
	TextDrawColor(ATMTD[41], -1);
	TextDrawSetShadow(ATMTD[41], 0);
	TextDrawSetOutline(ATMTD[41], 0);
	TextDrawBackgroundColor(ATMTD[41], 255);
	TextDrawFont(ATMTD[41], 4);
	TextDrawSetProportional(ATMTD[41], 1);

	ATMTD[42] = TextDrawCreate(348.500, 213.298, ">");
	TextDrawLetterSize(ATMTD[42], 0.136, 1.500);
	TextDrawAlignment(ATMTD[42], 1);
	TextDrawColor(ATMTD[42], -1);
	TextDrawSetShadow(ATMTD[42], 1);
	TextDrawSetOutline(ATMTD[42], 1);
	TextDrawBackgroundColor(ATMTD[42], 0);
	TextDrawFont(ATMTD[42], 1);
	TextDrawSetProportional(ATMTD[42], 1);

	ATMTD[43] = TextDrawCreate(424.000, 206.000, "LD_BEAT:chit");
	TextDrawTextSize(ATMTD[43], 24.000, 29.000);
	TextDrawAlignment(ATMTD[43], 1);
	TextDrawColor(ATMTD[43], 684158975);
	TextDrawSetShadow(ATMTD[43], 0);
	TextDrawSetOutline(ATMTD[43], 0);
	TextDrawBackgroundColor(ATMTD[43], 255);
	TextDrawFont(ATMTD[43], 4);
	TextDrawSetProportional(ATMTD[43], 1);
	TextDrawSetSelectable(ATMTD[43], 1);

	ATMTD[44] = TextDrawCreate(432.500, 220.000, "LD_BUM:blkdot");
	TextDrawTextSize(ATMTD[44], 6.000, 1.000);
	TextDrawAlignment(ATMTD[44], 1);
	TextDrawColor(ATMTD[44], -1);
	TextDrawSetShadow(ATMTD[44], 0);
	TextDrawSetOutline(ATMTD[44], 0);
	TextDrawBackgroundColor(ATMTD[44], 255);
	TextDrawFont(ATMTD[44], 4);
	TextDrawSetProportional(ATMTD[44], 1);

	ATMTD[45] = TextDrawCreate(436.500, 213.298, ">");
	TextDrawLetterSize(ATMTD[45], 0.136, 1.500);
	TextDrawAlignment(ATMTD[45], 1);
	TextDrawColor(ATMTD[45], -1);
	TextDrawSetShadow(ATMTD[45], 1);
	TextDrawSetOutline(ATMTD[45], 1);
	TextDrawBackgroundColor(ATMTD[45], 0);
	TextDrawFont(ATMTD[45], 1);
	TextDrawSetProportional(ATMTD[45], 1);

	ATMTD[46] = TextDrawCreate(202.000, 219.000, "LD_BUM:blkdot");
	TextDrawTextSize(ATMTD[46], 14.000, 11.000);
	TextDrawAlignment(ATMTD[46], 1);
	TextDrawColor(ATMTD[46], 684158975);
	TextDrawSetShadow(ATMTD[46], 0);
	TextDrawSetOutline(ATMTD[46], 0);
	TextDrawBackgroundColor(ATMTD[46], 255);
	TextDrawFont(ATMTD[46], 4);
	TextDrawSetProportional(ATMTD[46], 1);

	ATMTD[47] = TextDrawCreate(208.000, 222.000, "LD_BUM:blkdot");
	TextDrawTextSize(ATMTD[47], 14.000, 1.000);
	TextDrawAlignment(ATMTD[47], 1);
	TextDrawColor(ATMTD[47], -1);
	TextDrawSetShadow(ATMTD[47], 0);
	TextDrawSetOutline(ATMTD[47], 0);
	TextDrawBackgroundColor(ATMTD[47], 255);
	TextDrawFont(ATMTD[47], 4);
	TextDrawSetProportional(ATMTD[47], 1);

	ATMTD[48] = TextDrawCreate(211.000, 225.000, "ld_beat:chit");
	TextDrawTextSize(ATMTD[48], 3.000, 3.500);
	TextDrawAlignment(ATMTD[48], 1);
	TextDrawColor(ATMTD[48], -1);
	TextDrawSetShadow(ATMTD[48], 0);
	TextDrawSetOutline(ATMTD[48], 0);
	TextDrawBackgroundColor(ATMTD[48], 255);
	TextDrawFont(ATMTD[48], 4);
	TextDrawSetProportional(ATMTD[48], 1);

	ATMTD[49] = TextDrawCreate(288.000, 219.000, "LD_BUM:blkdot");
	TextDrawTextSize(ATMTD[49], 14.000, 11.000);
	TextDrawAlignment(ATMTD[49], 1);
	TextDrawColor(ATMTD[49], 684158975);
	TextDrawSetShadow(ATMTD[49], 0);
	TextDrawSetOutline(ATMTD[49], 0);
	TextDrawBackgroundColor(ATMTD[49], 255);
	TextDrawFont(ATMTD[49], 4);
	TextDrawSetProportional(ATMTD[49], 1);

	ATMTD[50] = TextDrawCreate(289.000, 220.000, "ld_beat:chit");
	TextDrawTextSize(ATMTD[50], 2.000, 1.500);
	TextDrawAlignment(ATMTD[50], 1);
	TextDrawColor(ATMTD[50], -1);
	TextDrawSetShadow(ATMTD[50], 0);
	TextDrawSetOutline(ATMTD[50], 0);
	TextDrawBackgroundColor(ATMTD[50], 255);
	TextDrawFont(ATMTD[50], 4);
	TextDrawSetProportional(ATMTD[50], 1);

	ATMTD[51] = TextDrawCreate(289.000, 227.000, "ld_beat:chit");
	TextDrawTextSize(ATMTD[51], 2.000, 1.500);
	TextDrawAlignment(ATMTD[51], 1);
	TextDrawColor(ATMTD[51], -1);
	TextDrawSetShadow(ATMTD[51], 0);
	TextDrawSetOutline(ATMTD[51], 0);
	TextDrawBackgroundColor(ATMTD[51], 255);
	TextDrawFont(ATMTD[51], 4);
	TextDrawSetProportional(ATMTD[51], 1);

	ATMTD[52] = TextDrawCreate(299.200, 220.000, "ld_beat:chit");
	TextDrawTextSize(ATMTD[52], 2.000, 1.500);
	TextDrawAlignment(ATMTD[52], 1);
	TextDrawColor(ATMTD[52], -1);
	TextDrawSetShadow(ATMTD[52], 0);
	TextDrawSetOutline(ATMTD[52], 0);
	TextDrawBackgroundColor(ATMTD[52], 255);
	TextDrawFont(ATMTD[52], 4);
	TextDrawSetProportional(ATMTD[52], 1);

	ATMTD[53] = TextDrawCreate(299.200, 227.000, "ld_beat:chit");
	TextDrawTextSize(ATMTD[53], 2.000, 1.500);
	TextDrawAlignment(ATMTD[53], 1);
	TextDrawColor(ATMTD[53], -1);
	TextDrawSetShadow(ATMTD[53], 0);
	TextDrawSetOutline(ATMTD[53], 0);
	TextDrawBackgroundColor(ATMTD[53], 255);
	TextDrawFont(ATMTD[53], 4);
	TextDrawSetProportional(ATMTD[53], 1);

	ATMTD[54] = TextDrawCreate(290.000, 218.500, "LD_BEAT:chit");
	TextDrawTextSize(ATMTD[54], 10.000, 12.000);
	TextDrawAlignment(ATMTD[54], 1);
	TextDrawColor(ATMTD[54], -1);
	TextDrawSetShadow(ATMTD[54], 0);
	TextDrawSetOutline(ATMTD[54], 0);
	TextDrawBackgroundColor(ATMTD[54], 255);
	TextDrawFont(ATMTD[54], 4);
	TextDrawSetProportional(ATMTD[54], 1);

	ATMTD[55] = TextDrawCreate(295.000, 221.000, "$");
	TextDrawLetterSize(ATMTD[55], 0.128, 0.699);
	TextDrawAlignment(ATMTD[55], 2);
	TextDrawColor(ATMTD[55], 2021954047);
	TextDrawSetShadow(ATMTD[55], 1);
	TextDrawSetOutline(ATMTD[55], 1);
	TextDrawBackgroundColor(ATMTD[55], 0);
	TextDrawFont(ATMTD[55], 1);
	TextDrawSetProportional(ATMTD[55], 1);

	ATMTD[56] = TextDrawCreate(378.500, 221.300, "LD_BUM:blkdot");
	TextDrawTextSize(ATMTD[56], 12.000, 1.000);
	TextDrawAlignment(ATMTD[56], 1);
	TextDrawColor(ATMTD[56], 684158975);
	TextDrawSetShadow(ATMTD[56], 0);
	TextDrawSetOutline(ATMTD[56], 0);
	TextDrawBackgroundColor(ATMTD[56], 255);
	TextDrawFont(ATMTD[56], 4);
	TextDrawSetProportional(ATMTD[56], 1);

	ATMTD[57] = TextDrawCreate(387.000, 215.000, ">");
	TextDrawLetterSize(ATMTD[57], 0.188, 1.399);
	TextDrawAlignment(ATMTD[57], 1);
	TextDrawColor(ATMTD[57], 684158975);
	TextDrawSetShadow(ATMTD[57], 1);
	TextDrawSetOutline(ATMTD[57], 1);
	TextDrawBackgroundColor(ATMTD[57], 0);
	TextDrawFont(ATMTD[57], 1);
	TextDrawSetProportional(ATMTD[57], 1);

	ATMTD[58] = TextDrawCreate(378.500, 226.000, "LD_BUM:blkdot");
	TextDrawTextSize(ATMTD[58], 11.500, 1.000);
	TextDrawAlignment(ATMTD[58], 1);
	TextDrawColor(ATMTD[58], 684158975);
	TextDrawSetShadow(ATMTD[58], 0);
	TextDrawSetOutline(ATMTD[58], 0);
	TextDrawBackgroundColor(ATMTD[58], 255);
	TextDrawFont(ATMTD[58], 4);
	TextDrawSetProportional(ATMTD[58], 1);

	ATMTD[59] = TextDrawCreate(382.000, 219.500, ">");
	TextDrawLetterSize(ATMTD[59], -0.200, 1.399);
	TextDrawAlignment(ATMTD[59], 1);
	TextDrawColor(ATMTD[59], 684158975);
	TextDrawSetShadow(ATMTD[59], 1);
	TextDrawSetOutline(ATMTD[59], 1);
	TextDrawBackgroundColor(ATMTD[59], 0);
	TextDrawFont(ATMTD[59], 1);
	TextDrawSetProportional(ATMTD[59], 1);

	ATMTD[60] = TextDrawCreate(320.000, 265.000, "Quick Withdraw");
	TextDrawLetterSize(ATMTD[60], 0.158, 0.898);
	TextDrawAlignment(ATMTD[60], 2);
	TextDrawColor(ATMTD[60], 472067071);
	TextDrawSetShadow(ATMTD[60], 1);
	TextDrawSetOutline(ATMTD[60], 1);
	TextDrawBackgroundColor(ATMTD[60], 0);
	TextDrawFont(ATMTD[60], 1);
	TextDrawSetProportional(ATMTD[60], 1);

	ATMTD[61] = TextDrawCreate(320.000, 307.000, "Quick Deposit");
	TextDrawLetterSize(ATMTD[61], 0.158, 0.898);
	TextDrawAlignment(ATMTD[61], 2);
	TextDrawColor(ATMTD[61], 472067071);
	TextDrawSetShadow(ATMTD[61], 1);
	TextDrawSetOutline(ATMTD[61], 1);
	TextDrawBackgroundColor(ATMTD[61], 0);
	TextDrawFont(ATMTD[61], 1);
	TextDrawSetProportional(ATMTD[61], 1);

	ATMTD[62] = TextDrawCreate(190.000, 277.000, "LD_BUM:blkdot");
	TextDrawTextSize(ATMTD[62], 52.000, 17.000);
	TextDrawAlignment(ATMTD[62], 1);
	TextDrawColor(ATMTD[62], 684158975);
	TextDrawSetShadow(ATMTD[62], 0);
	TextDrawSetOutline(ATMTD[62], 0);
	TextDrawBackgroundColor(ATMTD[62], 255);
	TextDrawFont(ATMTD[62], 4);
	TextDrawSetProportional(ATMTD[62], 1);
	TextDrawSetSelectable(ATMTD[62], 1);

	ATMTD[63] = TextDrawCreate(201.000, 280.000, "$10,000");
	TextDrawLetterSize(ATMTD[63], 0.187, 1.098);
	TextDrawAlignment(ATMTD[63], 1);
	TextDrawColor(ATMTD[63], -1);
	TextDrawSetShadow(ATMTD[63], 1);
	TextDrawSetOutline(ATMTD[63], 1);
	TextDrawBackgroundColor(ATMTD[63], 0);
	TextDrawFont(ATMTD[63], 1);
	TextDrawSetProportional(ATMTD[63], 1);

	ATMTD[64] = TextDrawCreate(259.000, 277.000, "LD_BUM:blkdot");
	TextDrawTextSize(ATMTD[64], 52.000, 17.000);
	TextDrawAlignment(ATMTD[64], 1);
	TextDrawColor(ATMTD[64], 684158975);
	TextDrawSetShadow(ATMTD[64], 0);
	TextDrawSetOutline(ATMTD[64], 0);
	TextDrawBackgroundColor(ATMTD[64], 255);
	TextDrawFont(ATMTD[64], 4);
	TextDrawSetProportional(ATMTD[64], 1);
	TextDrawSetSelectable(ATMTD[64], 1);

	ATMTD[65] = TextDrawCreate(270.000, 280.000, "$50,000");
	TextDrawLetterSize(ATMTD[65], 0.187, 1.098);
	TextDrawAlignment(ATMTD[65], 1);
	TextDrawColor(ATMTD[65], -1);
	TextDrawSetShadow(ATMTD[65], 1);
	TextDrawSetOutline(ATMTD[65], 1);
	TextDrawBackgroundColor(ATMTD[65], 0);
	TextDrawFont(ATMTD[65], 1);
	TextDrawSetProportional(ATMTD[65], 1);

	ATMTD[66] = TextDrawCreate(329.000, 277.000, "LD_BUM:blkdot");
	TextDrawTextSize(ATMTD[66], 52.000, 17.000);
	TextDrawAlignment(ATMTD[66], 1);
	TextDrawColor(ATMTD[66], 684158975);
	TextDrawSetShadow(ATMTD[66], 0);
	TextDrawSetOutline(ATMTD[66], 0);
	TextDrawBackgroundColor(ATMTD[66], 255);
	TextDrawFont(ATMTD[66], 4);
	TextDrawSetProportional(ATMTD[66], 1);
	TextDrawSetSelectable(ATMTD[66], 1);

	ATMTD[67] = TextDrawCreate(340.000, 280.000, "$250,000");
	TextDrawLetterSize(ATMTD[67], 0.187, 1.098);
	TextDrawAlignment(ATMTD[67], 1);
	TextDrawColor(ATMTD[67], -1);
	TextDrawSetShadow(ATMTD[67], 1);
	TextDrawSetOutline(ATMTD[67], 1);
	TextDrawBackgroundColor(ATMTD[67], 0);
	TextDrawFont(ATMTD[67], 1);
	TextDrawSetProportional(ATMTD[67], 1);

	ATMTD[68] = TextDrawCreate(398.000, 277.000, "LD_BUM:blkdot");
	TextDrawTextSize(ATMTD[68], 52.000, 17.000);
	TextDrawAlignment(ATMTD[68], 1);
	TextDrawColor(ATMTD[68], 684158975);
	TextDrawSetShadow(ATMTD[68], 0);
	TextDrawSetOutline(ATMTD[68], 0);
	TextDrawBackgroundColor(ATMTD[68], 255);
	TextDrawFont(ATMTD[68], 4);
	TextDrawSetProportional(ATMTD[68], 1);
	TextDrawSetSelectable(ATMTD[68], 1);

	ATMTD[69] = TextDrawCreate(409.000, 280.000, "$500,000");
	TextDrawLetterSize(ATMTD[69], 0.187, 1.098);
	TextDrawAlignment(ATMTD[69], 1);
	TextDrawColor(ATMTD[69], -1);
	TextDrawSetShadow(ATMTD[69], 1);
	TextDrawSetOutline(ATMTD[69], 1);
	TextDrawBackgroundColor(ATMTD[69], 0);
	TextDrawFont(ATMTD[69], 1);
	TextDrawSetProportional(ATMTD[69], 1);

	ATMTD[70] = TextDrawCreate(190.000, 320.000, "LD_BUM:blkdot");
	TextDrawTextSize(ATMTD[70], 52.000, 17.000);
	TextDrawAlignment(ATMTD[70], 1);
	TextDrawColor(ATMTD[70], 684158975);
	TextDrawSetShadow(ATMTD[70], 0);
	TextDrawSetOutline(ATMTD[70], 0);
	TextDrawBackgroundColor(ATMTD[70], 255);
	TextDrawFont(ATMTD[70], 4);
	TextDrawSetProportional(ATMTD[70], 1);
	TextDrawSetSelectable(ATMTD[70], 1);

	ATMTD[71] = TextDrawCreate(201.000, 323.000, "$10,000");
	TextDrawLetterSize(ATMTD[71], 0.187, 1.098);
	TextDrawAlignment(ATMTD[71], 1);
	TextDrawColor(ATMTD[71], -1);
	TextDrawSetShadow(ATMTD[71], 1);
	TextDrawSetOutline(ATMTD[71], 1);
	TextDrawBackgroundColor(ATMTD[71], 0);
	TextDrawFont(ATMTD[71], 1);
	TextDrawSetProportional(ATMTD[71], 1);

	ATMTD[72] = TextDrawCreate(259.000, 320.000, "LD_BUM:blkdot");
	TextDrawTextSize(ATMTD[72], 52.000, 17.000);
	TextDrawAlignment(ATMTD[72], 1);
	TextDrawColor(ATMTD[72], 684158975);
	TextDrawSetShadow(ATMTD[72], 0);
	TextDrawSetOutline(ATMTD[72], 0);
	TextDrawBackgroundColor(ATMTD[72], 255);
	TextDrawFont(ATMTD[72], 4);
	TextDrawSetProportional(ATMTD[72], 1);
	TextDrawSetSelectable(ATMTD[72], 1);

	ATMTD[73] = TextDrawCreate(270.000, 323.000, "$50,000");
	TextDrawLetterSize(ATMTD[73], 0.187, 1.098);
	TextDrawAlignment(ATMTD[73], 1);
	TextDrawColor(ATMTD[73], -1);
	TextDrawSetShadow(ATMTD[73], 1);
	TextDrawSetOutline(ATMTD[73], 1);
	TextDrawBackgroundColor(ATMTD[73], 0);
	TextDrawFont(ATMTD[73], 1);
	TextDrawSetProportional(ATMTD[73], 1);

	ATMTD[74] = TextDrawCreate(328.000, 320.000, "LD_BUM:blkdot");
	TextDrawTextSize(ATMTD[74], 52.000, 17.000);
	TextDrawAlignment(ATMTD[74], 1);
	TextDrawColor(ATMTD[74], 684158975);
	TextDrawSetShadow(ATMTD[74], 0);
	TextDrawSetOutline(ATMTD[74], 0);
	TextDrawBackgroundColor(ATMTD[74], 255);
	TextDrawFont(ATMTD[74], 4);
	TextDrawSetProportional(ATMTD[74], 1);
	TextDrawSetSelectable(ATMTD[74], 1);

	ATMTD[75] = TextDrawCreate(340.000, 323.000, "$250,000");
	TextDrawLetterSize(ATMTD[75], 0.187, 1.098);
	TextDrawAlignment(ATMTD[75], 1);
	TextDrawColor(ATMTD[75], -1);
	TextDrawSetShadow(ATMTD[75], 1);
	TextDrawSetOutline(ATMTD[75], 1);
	TextDrawBackgroundColor(ATMTD[75], 0);
	TextDrawFont(ATMTD[75], 1);
	TextDrawSetProportional(ATMTD[75], 1);

	ATMTD[76] = TextDrawCreate(398.000, 320.000, "LD_BUM:blkdot");
	TextDrawTextSize(ATMTD[76], 52.000, 17.000);
	TextDrawAlignment(ATMTD[76], 1);
	TextDrawColor(ATMTD[76], 684158975);
	TextDrawSetShadow(ATMTD[76], 0);
	TextDrawSetOutline(ATMTD[76], 0);
	TextDrawBackgroundColor(ATMTD[76], 255);
	TextDrawFont(ATMTD[76], 4);
	TextDrawSetProportional(ATMTD[76], 1);
	TextDrawSetSelectable(ATMTD[76], 1);

	ATMTD[77] = TextDrawCreate(409.000, 323.000, "$500,000");
	TextDrawLetterSize(ATMTD[77], 0.187, 1.098);
	TextDrawAlignment(ATMTD[77], 1);
	TextDrawColor(ATMTD[77], -1);
	TextDrawSetShadow(ATMTD[77], 1);
	TextDrawSetOutline(ATMTD[77], 1);
	TextDrawBackgroundColor(ATMTD[77], 0);
	TextDrawFont(ATMTD[77], 1);
	TextDrawSetProportional(ATMTD[77], 1);

	ATMTD[78] = TextDrawCreate(190.000, 277.000, "LD_BUM:blkdot");
	TextDrawTextSize(ATMTD[78], 5.000, 17.000);
	TextDrawAlignment(ATMTD[78], 1);
	TextDrawColor(ATMTD[78], 480795903);
	TextDrawSetShadow(ATMTD[78], 0);
	TextDrawSetOutline(ATMTD[78], 0);
	TextDrawBackgroundColor(ATMTD[78], 255);
	TextDrawFont(ATMTD[78], 4);
	TextDrawSetProportional(ATMTD[78], 1);

	ATMTD[79] = TextDrawCreate(259.000, 277.000, "LD_BUM:blkdot");
	TextDrawTextSize(ATMTD[79], 5.000, 17.000);
	TextDrawAlignment(ATMTD[79], 1);
	TextDrawColor(ATMTD[79], 480795903);
	TextDrawSetShadow(ATMTD[79], 0);
	TextDrawSetOutline(ATMTD[79], 0);
	TextDrawBackgroundColor(ATMTD[79], 255);
	TextDrawFont(ATMTD[79], 4);
	TextDrawSetProportional(ATMTD[79], 1);

	ATMTD[80] = TextDrawCreate(329.000, 277.000, "LD_BUM:blkdot");
	TextDrawTextSize(ATMTD[80], 5.000, 17.000);
	TextDrawAlignment(ATMTD[80], 1);
	TextDrawColor(ATMTD[80], 480795903);
	TextDrawSetShadow(ATMTD[80], 0);
	TextDrawSetOutline(ATMTD[80], 0);
	TextDrawBackgroundColor(ATMTD[80], 255);
	TextDrawFont(ATMTD[80], 4);
	TextDrawSetProportional(ATMTD[80], 1);

	ATMTD[81] = TextDrawCreate(398.000, 277.000, "LD_BUM:blkdot");
	TextDrawTextSize(ATMTD[81], 5.000, 17.000);
	TextDrawAlignment(ATMTD[81], 1);
	TextDrawColor(ATMTD[81], 480795903);
	TextDrawSetShadow(ATMTD[81], 0);
	TextDrawSetOutline(ATMTD[81], 0);
	TextDrawBackgroundColor(ATMTD[81], 255);
	TextDrawFont(ATMTD[81], 4);
	TextDrawSetProportional(ATMTD[81], 1);

	ATMTD[82] = TextDrawCreate(190.000, 320.000, "LD_BUM:blkdot");
	TextDrawTextSize(ATMTD[82], 5.000, 17.000);
	TextDrawAlignment(ATMTD[82], 1);
	TextDrawColor(ATMTD[82], 480795903);
	TextDrawSetShadow(ATMTD[82], 0);
	TextDrawSetOutline(ATMTD[82], 0);
	TextDrawBackgroundColor(ATMTD[82], 255);
	TextDrawFont(ATMTD[82], 4);
	TextDrawSetProportional(ATMTD[82], 1);

	ATMTD[83] = TextDrawCreate(259.000, 320.000, "LD_BUM:blkdot");
	TextDrawTextSize(ATMTD[83], 5.000, 17.000);
	TextDrawAlignment(ATMTD[83], 1);
	TextDrawColor(ATMTD[83], 480795903);
	TextDrawSetShadow(ATMTD[83], 0);
	TextDrawSetOutline(ATMTD[83], 0);
	TextDrawBackgroundColor(ATMTD[83], 255);
	TextDrawFont(ATMTD[83], 4);
	TextDrawSetProportional(ATMTD[83], 1);

	ATMTD[84] = TextDrawCreate(328.000, 320.000, "LD_BUM:blkdot");
	TextDrawTextSize(ATMTD[84], 5.000, 17.000);
	TextDrawAlignment(ATMTD[84], 1);
	TextDrawColor(ATMTD[84], 480795903);
	TextDrawSetShadow(ATMTD[84], 0);
	TextDrawSetOutline(ATMTD[84], 0);
	TextDrawBackgroundColor(ATMTD[84], 255);
	TextDrawFont(ATMTD[84], 4);
	TextDrawSetProportional(ATMTD[84], 1);

	ATMTD[85] = TextDrawCreate(398.000, 320.000, "LD_BUM:blkdot");
	TextDrawTextSize(ATMTD[85], 5.000, 17.000);
	TextDrawAlignment(ATMTD[85], 1);
	TextDrawColor(ATMTD[85], 480795903);
	TextDrawSetShadow(ATMTD[85], 0);
	TextDrawSetOutline(ATMTD[85], 0);
	TextDrawBackgroundColor(ATMTD[85], 255);
	TextDrawFont(ATMTD[85], 4);
	TextDrawSetProportional(ATMTD[85], 1);

	ATMTD[86] = TextDrawCreate(319.000, 349.500, "THURX PROJECT");
	TextDrawLetterSize(ATMTD[86], 0.096, 0.495);
	TextDrawAlignment(ATMTD[86], 2);
	TextDrawColor(ATMTD[86], -589505281);
	TextDrawSetShadow(ATMTD[86], 1);
	TextDrawSetOutline(ATMTD[86], 1);
	TextDrawBackgroundColor(ATMTD[86], 0);
	TextDrawFont(ATMTD[86], 1);
	TextDrawSetProportional(ATMTD[86], 1);

	ATMTD[87] = TextDrawCreate(300.500, 349.000, "ld_dual:white");
	TextDrawTextSize(ATMTD[87], 36.000, 5.000);
	TextDrawAlignment(ATMTD[87], 1);
	TextDrawColor(ATMTD[87], -1);
	TextDrawSetShadow(ATMTD[87], 0);
	TextDrawSetOutline(ATMTD[87], 0);
	TextDrawBackgroundColor(ATMTD[87], 255);
	TextDrawFont(ATMTD[87], 4);
	TextDrawSetProportional(ATMTD[87], 1);
}

CreateATMPTD(playerid)
{
	ATMPTD[playerid][0] = CreatePlayerTextDraw(playerid, 173.000, 109.500, "Welcome back, Arthur Clinton!");
	PlayerTextDrawLetterSize(playerid, ATMPTD[playerid][0], 0.158, 0.898);
	PlayerTextDrawAlignment(playerid, ATMPTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, ATMPTD[playerid][0], 472067071);
	PlayerTextDrawSetShadow(playerid, ATMPTD[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, ATMPTD[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, ATMPTD[playerid][0], 0);
	PlayerTextDrawFont(playerid, ATMPTD[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, ATMPTD[playerid][0], 1);

	ATMPTD[playerid][1] = CreatePlayerTextDraw(playerid, 232.000, 163.000, "$BANKBALANCE");
	PlayerTextDrawLetterSize(playerid, ATMPTD[playerid][1], 0.238, 1.498);
	PlayerTextDrawAlignment(playerid, ATMPTD[playerid][1], 2);
	PlayerTextDrawColor(playerid, ATMPTD[playerid][1], 472067071);
	PlayerTextDrawSetShadow(playerid, ATMPTD[playerid][1], 1);
	PlayerTextDrawSetOutline(playerid, ATMPTD[playerid][1], 1);
	PlayerTextDrawBackgroundColor(playerid, ATMPTD[playerid][1], 0);
	PlayerTextDrawFont(playerid, ATMPTD[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, ATMPTD[playerid][1], 1);

	ATMPTD[playerid][2] = CreatePlayerTextDraw(playerid, 320.000, 163.000, "BANKNUMBER");
	PlayerTextDrawLetterSize(playerid, ATMPTD[playerid][2], 0.238, 1.498);
	PlayerTextDrawAlignment(playerid, ATMPTD[playerid][2], 2);
	PlayerTextDrawColor(playerid, ATMPTD[playerid][2], 472067071);
	PlayerTextDrawSetShadow(playerid, ATMPTD[playerid][2], 1);
	PlayerTextDrawSetOutline(playerid, ATMPTD[playerid][2], 1);
	PlayerTextDrawBackgroundColor(playerid, ATMPTD[playerid][2], 0);
	PlayerTextDrawFont(playerid, ATMPTD[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, ATMPTD[playerid][2], 1);

	ATMPTD[playerid][3] = CreatePlayerTextDraw(playerid, 409.000, 163.000, "$CASHBALANCE");
	PlayerTextDrawLetterSize(playerid, ATMPTD[playerid][3], 0.238, 1.498);
	PlayerTextDrawAlignment(playerid, ATMPTD[playerid][3], 2);
	PlayerTextDrawColor(playerid, ATMPTD[playerid][3], 472067071);
	PlayerTextDrawSetShadow(playerid, ATMPTD[playerid][3], 1);
	PlayerTextDrawSetOutline(playerid, ATMPTD[playerid][3], 1);
	PlayerTextDrawBackgroundColor(playerid, ATMPTD[playerid][3], 0);
	PlayerTextDrawFont(playerid, ATMPTD[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, ATMPTD[playerid][3], 1);
}

ShowATMTD(playerid)
{
	HideHBETD(playerid);
	HideServerNameTD(playerid);

    for(new x; x < 88; x++)
    {
        TextDrawShowForPlayer(playerid, ATMTD[x]);
    }

	PlayerTextDrawSetString(playerid, ATMPTD[playerid][0], sprintf("Welcome Back, %s!", AccountData[playerid][pName]));
    PlayerTextDrawSetString(playerid, ATMPTD[playerid][1], sprintf("$%s", FormatMoney(AccountData[playerid][pBankMoney])));
    PlayerTextDrawSetString(playerid, ATMPTD[playerid][2], sprintf("%d", AccountData[playerid][pBankNumber]));
	PlayerTextDrawSetString(playerid, ATMPTD[playerid][3], sprintf("$%s", FormatMoney(AccountData[playerid][pMoney])));

    PlayerTextDrawShow(playerid, ATMPTD[playerid][0]);
    PlayerTextDrawShow(playerid, ATMPTD[playerid][1]);
    PlayerTextDrawShow(playerid, ATMPTD[playerid][2]);
    PlayerTextDrawShow(playerid, ATMPTD[playerid][3]);

    SelectTextDraw(playerid, 0xadadadcc);
    return 1;
}

HideATMTD(playerid)
{
    for(new x; x < 88; x++)
    {
        TextDrawHideForPlayer(playerid, ATMTD[x]);
    }

    PlayerTextDrawHide(playerid, ATMPTD[playerid][0]);
    PlayerTextDrawHide(playerid, ATMPTD[playerid][1]);
    PlayerTextDrawHide(playerid, ATMPTD[playerid][2]);
    PlayerTextDrawHide(playerid, ATMPTD[playerid][3]);

	ShowHBETD(playerid);
	ShowServerNameTD(playerid);

    CancelSelectTextDraw(playerid);
    return 1;
}