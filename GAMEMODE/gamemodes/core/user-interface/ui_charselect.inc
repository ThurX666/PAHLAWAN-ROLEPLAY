new Text:CharSelTD[50],
	Text:LoginUITD[34],
    PlayerText:CharSelPTD[MAX_PLAYERS][3];

CreateLoginUITD()
{
	LoginUITD[0] = TextDrawCreate(-121.000, -160.000, "LD_DUAL:white");
	TextDrawTextSize(LoginUITD[0], 962.000, 961.000);
	TextDrawAlignment(LoginUITD[0], 1);
	TextDrawColor(LoginUITD[0], 150);
	TextDrawSetShadow(LoginUITD[0], 0);
	TextDrawBackgroundColor(LoginUITD[0], 255);
	TextDrawSetProportional(LoginUITD[0], 1);
	TextDrawFont(LoginUITD[0], 4);
	TextDrawSetOutline(LoginUITD[0], true);
	TextDrawUseBox(LoginUITD[0], true);

	LoginUITD[1] = TextDrawCreate(261.000, 115.900, "/");
	TextDrawLetterSize(LoginUITD[1], 0.709, 2.598);
	TextDrawAlignment(LoginUITD[1], 1);
	TextDrawColor(LoginUITD[1], -54500609);
	TextDrawSetShadow(LoginUITD[1], 1);
	TextDrawSetOutline(LoginUITD[1], 1);
	TextDrawBackgroundColor(LoginUITD[1], 0);
	TextDrawFont(LoginUITD[1], 1);
	TextDrawSetProportional(LoginUITD[1], 1);

	LoginUITD[2] = TextDrawCreate(261.000, 115.900, "/");
	TextDrawLetterSize(LoginUITD[2], 0.709, 2.598);
	TextDrawAlignment(LoginUITD[2], 1);
	TextDrawColor(LoginUITD[2], -54500609);
	TextDrawSetShadow(LoginUITD[2], 1);
	TextDrawSetOutline(LoginUITD[2], 1);
	TextDrawBackgroundColor(LoginUITD[2], 0);
	TextDrawFont(LoginUITD[2], 1);
	TextDrawSetProportional(LoginUITD[2], 1);

	LoginUITD[3] = TextDrawCreate(269.000, 120.400, "LD_DUAL:white");
	TextDrawTextSize(LoginUITD[3], 19.000, 5.000);
	TextDrawAlignment(LoginUITD[3], 1);
	TextDrawColor(LoginUITD[3], -54500609);
	TextDrawSetShadow(LoginUITD[3], 0);
	TextDrawSetOutline(LoginUITD[3], 0);
	TextDrawBackgroundColor(LoginUITD[3], 255);
	TextDrawFont(LoginUITD[3], 4);
	TextDrawSetProportional(LoginUITD[3], 1);

	LoginUITD[4] = TextDrawCreate(289.000, 115.900, "/");
	TextDrawLetterSize(LoginUITD[4], -0.708, 2.598);
	TextDrawAlignment(LoginUITD[4], 1);
	TextDrawColor(LoginUITD[4], -54500609);
	TextDrawSetShadow(LoginUITD[4], 1);
	TextDrawSetOutline(LoginUITD[4], 1);
	TextDrawBackgroundColor(LoginUITD[4], 0);
	TextDrawFont(LoginUITD[4], 1);
	TextDrawSetProportional(LoginUITD[4], 1);

	LoginUITD[5] = TextDrawCreate(289.000, 115.900, "/");
	TextDrawLetterSize(LoginUITD[5], -0.708, 2.598);
	TextDrawAlignment(LoginUITD[5], 1);
	TextDrawColor(LoginUITD[5], -54500609);
	TextDrawSetShadow(LoginUITD[5], 1);
	TextDrawSetOutline(LoginUITD[5], 1);
	TextDrawBackgroundColor(LoginUITD[5], 0);
	TextDrawFont(LoginUITD[5], 1);
	TextDrawSetProportional(LoginUITD[5], 1);

	LoginUITD[6] = TextDrawCreate(273.000, 134.899, "LD_DUAL:white");
	TextDrawTextSize(LoginUITD[6], 13.000, 5.000);
	TextDrawAlignment(LoginUITD[6], 1);
	TextDrawColor(LoginUITD[6], -54500609);
	TextDrawSetShadow(LoginUITD[6], 0);
	TextDrawSetOutline(LoginUITD[6], 0);
	TextDrawBackgroundColor(LoginUITD[6], 255);
	TextDrawFont(LoginUITD[6], 4);
	TextDrawSetProportional(LoginUITD[6], 1);

	LoginUITD[7] = TextDrawCreate(291.200, 122.900, "/");
	TextDrawLetterSize(LoginUITD[7], -0.708, 2.598);
	TextDrawAlignment(LoginUITD[7], 1);
	TextDrawColor(LoginUITD[7], -54500609);
	TextDrawSetShadow(LoginUITD[7], 1);
	TextDrawSetOutline(LoginUITD[7], 1);
	TextDrawBackgroundColor(LoginUITD[7], 0);
	TextDrawFont(LoginUITD[7], 1);
	TextDrawSetProportional(LoginUITD[7], 1);

	LoginUITD[8] = TextDrawCreate(291.200, 122.900, "/");
	TextDrawLetterSize(LoginUITD[8], -0.708, 2.598);
	TextDrawAlignment(LoginUITD[8], 1);
	TextDrawColor(LoginUITD[8], -54500609);
	TextDrawSetShadow(LoginUITD[8], 1);
	TextDrawSetOutline(LoginUITD[8], 1);
	TextDrawBackgroundColor(LoginUITD[8], 0);
	TextDrawFont(LoginUITD[8], 1);
	TextDrawSetProportional(LoginUITD[8], 1);

	LoginUITD[9] = TextDrawCreate(262.000, 107.400, "LD_DUAL:white");
	TextDrawTextSize(LoginUITD[9], 24.000, 5.000);
	TextDrawAlignment(LoginUITD[9], 1);
	TextDrawColor(LoginUITD[9], -54500609);
	TextDrawSetShadow(LoginUITD[9], 0);
	TextDrawSetOutline(LoginUITD[9], 0);
	TextDrawBackgroundColor(LoginUITD[9], 255);
	TextDrawFont(LoginUITD[9], 4);
	TextDrawSetProportional(LoginUITD[9], 1);

	LoginUITD[10] = TextDrawCreate(283.000, 107.400, "LD_DUAL:white");
	TextDrawTextSize(LoginUITD[10], 5.000, 8.500);
	TextDrawAlignment(LoginUITD[10], 1);
	TextDrawColor(LoginUITD[10], -54500609);
	TextDrawSetShadow(LoginUITD[10], 0);
	TextDrawSetOutline(LoginUITD[10], 0);
	TextDrawBackgroundColor(LoginUITD[10], 255);
	TextDrawFont(LoginUITD[10], 4);
	TextDrawSetProportional(LoginUITD[10], 1);

	LoginUITD[11] = TextDrawCreate(283.000, 117.400, "LD_DUAL:white");
	TextDrawTextSize(LoginUITD[11], 5.000, 4.000);
	TextDrawAlignment(LoginUITD[11], 1);
	TextDrawColor(LoginUITD[11], -54500609);
	TextDrawSetShadow(LoginUITD[11], 0);
	TextDrawSetOutline(LoginUITD[11], 0);
	TextDrawBackgroundColor(LoginUITD[11], 255);
	TextDrawFont(LoginUITD[11], 4);
	TextDrawSetProportional(LoginUITD[11], 1);

	LoginUITD[12] = TextDrawCreate(298.000, 116.000, "Pahlawan");
	TextDrawLetterSize(LoginUITD[12], 0.469, 2.299);
	TextDrawAlignment(LoginUITD[12], 1);
	TextDrawColor(LoginUITD[12], -1);
	TextDrawSetShadow(LoginUITD[12], 1);
	TextDrawSetOutline(LoginUITD[12], 5);
	TextDrawBackgroundColor(LoginUITD[12], 0);
	TextDrawFont(LoginUITD[12], 1);
	TextDrawSetProportional(LoginUITD[12], 1);

	LoginUITD[13] = TextDrawCreate(371.000, 134.000, "Roleplay");
	TextDrawLetterSize(LoginUITD[13], 0.219, 1.299);
	TextDrawAlignment(LoginUITD[13], 3);
	TextDrawColor(LoginUITD[13], -1);
	TextDrawSetShadow(LoginUITD[13], 1);
	TextDrawSetOutline(LoginUITD[13], 5);
	TextDrawBackgroundColor(LoginUITD[13], 0);
	TextDrawFont(LoginUITD[13], 1);
	TextDrawSetProportional(LoginUITD[13], 1);

	LoginUITD[14] = TextDrawCreate(421.000, -21.000, "LD_DUAL:white");
	TextDrawTextSize(LoginUITD[14], 2.000, 51.000);
	TextDrawAlignment(LoginUITD[14], 1);
	TextDrawColor(LoginUITD[14], -92237754);
	TextDrawSetShadow(LoginUITD[14], 0);
	TextDrawSetOutline(LoginUITD[14], 0);
	TextDrawBackgroundColor(LoginUITD[14], 255);
	TextDrawFont(LoginUITD[14], 4);
	TextDrawSetProportional(LoginUITD[14], 1);

	LoginUITD[15] = TextDrawCreate(421.000, 30.000, "LD_DUAL:white");
	TextDrawTextSize(LoginUITD[15], 308.000, 2.000);
	TextDrawAlignment(LoginUITD[15], 1);
	TextDrawColor(LoginUITD[15], -92237754);
	TextDrawSetShadow(LoginUITD[15], 0);
	TextDrawSetOutline(LoginUITD[15], 0);
	TextDrawBackgroundColor(LoginUITD[15], 255);
	TextDrawFont(LoginUITD[15], 4);
	TextDrawSetProportional(LoginUITD[15], 1);

	LoginUITD[16] = TextDrawCreate(517.000, -21.000, "LD_DUAL:white");
	TextDrawTextSize(LoginUITD[16], 2.000, 211.000);
	TextDrawAlignment(LoginUITD[16], 1);
	TextDrawColor(LoginUITD[16], -92237754);
	TextDrawSetShadow(LoginUITD[16], 0);
	TextDrawSetOutline(LoginUITD[16], 0);
	TextDrawBackgroundColor(LoginUITD[16], 255);
	TextDrawFont(LoginUITD[16], 4);
	TextDrawSetProportional(LoginUITD[16], 1);

	LoginUITD[17] = TextDrawCreate(519.000, 188.000, "LD_DUAL:white");
	TextDrawTextSize(LoginUITD[17], 308.000, 2.000);
	TextDrawAlignment(LoginUITD[17], 1);
	TextDrawColor(LoginUITD[17], -92237754);
	TextDrawSetShadow(LoginUITD[17], 0);
	TextDrawSetOutline(LoginUITD[17], 0);
	TextDrawBackgroundColor(LoginUITD[17], 255);
	TextDrawFont(LoginUITD[17], 4);
	TextDrawSetProportional(LoginUITD[17], 1);

	LoginUITD[18] = TextDrawCreate(603.000, 258.000, "LD_DUAL:white");
	TextDrawTextSize(LoginUITD[18], 308.000, 2.000);
	TextDrawAlignment(LoginUITD[18], 1);
	TextDrawColor(LoginUITD[18], -92237754);
	TextDrawSetShadow(LoginUITD[18], 0);
	TextDrawSetOutline(LoginUITD[18], 0);
	TextDrawBackgroundColor(LoginUITD[18], 255);
	TextDrawFont(LoginUITD[18], 4);
	TextDrawSetProportional(LoginUITD[18], 1);

	LoginUITD[19] = TextDrawCreate(603.000, 398.000, "LD_DUAL:white");
	TextDrawTextSize(LoginUITD[19], 308.000, 2.000);
	TextDrawAlignment(LoginUITD[19], 1);
	TextDrawColor(LoginUITD[19], -92237754);
	TextDrawSetShadow(LoginUITD[19], 0);
	TextDrawSetOutline(LoginUITD[19], 0);
	TextDrawBackgroundColor(LoginUITD[19], 255);
	TextDrawFont(LoginUITD[19], 4);
	TextDrawSetProportional(LoginUITD[19], 1);

	LoginUITD[20] = TextDrawCreate(603.000, 260.000, "LD_DUAL:white");
	TextDrawTextSize(LoginUITD[20], 2.000, 138.000);
	TextDrawAlignment(LoginUITD[20], 1);
	TextDrawColor(LoginUITD[20], -92237754);
	TextDrawSetShadow(LoginUITD[20], 0);
	TextDrawSetOutline(LoginUITD[20], 0);
	TextDrawBackgroundColor(LoginUITD[20], 255);
	TextDrawFont(LoginUITD[20], 4);
	TextDrawSetProportional(LoginUITD[20], 1);

	LoginUITD[21] = TextDrawCreate(5.000, -19.000, "LD_DUAL:white");
	TextDrawTextSize(LoginUITD[21], 2.000, 393.000);
	TextDrawAlignment(LoginUITD[21], 1);
	TextDrawColor(LoginUITD[21], -92237754);
	TextDrawSetShadow(LoginUITD[21], 0);
	TextDrawSetOutline(LoginUITD[21], 0);
	TextDrawBackgroundColor(LoginUITD[21], 255);
	TextDrawFont(LoginUITD[21], 4);
	TextDrawSetProportional(LoginUITD[21], 1);

	LoginUITD[22] = TextDrawCreate(55.000, 210.000, "LD_DUAL:white");
	TextDrawTextSize(LoginUITD[22], 2.000, 393.000);
	TextDrawAlignment(LoginUITD[22], 1);
	TextDrawColor(LoginUITD[22], -92237754);
	TextDrawSetShadow(LoginUITD[22], 0);
	TextDrawSetOutline(LoginUITD[22], 0);
	TextDrawBackgroundColor(LoginUITD[22], 255);
	TextDrawFont(LoginUITD[22], 4);
	TextDrawSetProportional(LoginUITD[22], 1);

	LoginUITD[23] = TextDrawCreate(57.000, 210.000, "LD_DUAL:white");
	TextDrawTextSize(LoginUITD[23], 97.000, 2.000);
	TextDrawAlignment(LoginUITD[23], 1);
	TextDrawColor(LoginUITD[23], -92237754);
	TextDrawSetShadow(LoginUITD[23], 0);
	TextDrawSetOutline(LoginUITD[23], 0);
	TextDrawBackgroundColor(LoginUITD[23], 255);
	TextDrawFont(LoginUITD[23], 4);
	TextDrawSetProportional(LoginUITD[23], 1);

	LoginUITD[24] = TextDrawCreate(55.000, 178.000, "LD_DUAL:white");
	TextDrawTextSize(LoginUITD[24], 99.000, 2.000);
	TextDrawAlignment(LoginUITD[24], 1);
	TextDrawColor(LoginUITD[24], -92237754);
	TextDrawSetShadow(LoginUITD[24], 0);
	TextDrawSetOutline(LoginUITD[24], 0);
	TextDrawBackgroundColor(LoginUITD[24], 255);
	TextDrawFont(LoginUITD[24], 4);
	TextDrawSetProportional(LoginUITD[24], 1);

	LoginUITD[25] = TextDrawCreate(382.000, 210.000, "LD_DUAL:white");
	TextDrawTextSize(LoginUITD[25], 2.000, 393.000);
	TextDrawAlignment(LoginUITD[25], 1);
	TextDrawColor(LoginUITD[25], -92237754);
	TextDrawSetShadow(LoginUITD[25], 0);
	TextDrawSetOutline(LoginUITD[25], 0);
	TextDrawBackgroundColor(LoginUITD[25], 255);
	TextDrawFont(LoginUITD[25], 4);
	TextDrawSetProportional(LoginUITD[25], 1);

	LoginUITD[26] = TextDrawCreate(55.000, 9.000, "LD_DUAL:white");
	TextDrawTextSize(LoginUITD[26], 99.000, 2.000);
	TextDrawAlignment(LoginUITD[26], 1);
	TextDrawColor(LoginUITD[26], -92237754);
	TextDrawSetShadow(LoginUITD[26], 0);
	TextDrawSetOutline(LoginUITD[26], 0);
	TextDrawBackgroundColor(LoginUITD[26], 255);
	TextDrawFont(LoginUITD[26], 4);
	TextDrawSetProportional(LoginUITD[26], 1);

	LoginUITD[27] = TextDrawCreate(201.000, -17.000, "LD_DUAL:white");
	TextDrawTextSize(LoginUITD[27], 2.000, 406.000);
	TextDrawAlignment(LoginUITD[27], 1);
	TextDrawColor(LoginUITD[27], -92237754);
	TextDrawSetShadow(LoginUITD[27], 0);
	TextDrawSetOutline(LoginUITD[27], 0);
	TextDrawBackgroundColor(LoginUITD[27], 255);
	TextDrawFont(LoginUITD[27], 4);
	TextDrawSetProportional(LoginUITD[27], 1);

	LoginUITD[28] = TextDrawCreate(55.000, 11.000, "LD_DUAL:white");
	TextDrawTextSize(LoginUITD[28], 2.000, 167.000);
	TextDrawAlignment(LoginUITD[28], 1);
	TextDrawColor(LoginUITD[28], -92237754);
	TextDrawSetShadow(LoginUITD[28], 0);
	TextDrawSetOutline(LoginUITD[28], 0);
	TextDrawBackgroundColor(LoginUITD[28], 255);
	TextDrawFont(LoginUITD[28], 4);
	TextDrawSetProportional(LoginUITD[28], 1);

	LoginUITD[29] = TextDrawCreate(152.000, 11.000, "LD_DUAL:white");
	TextDrawTextSize(LoginUITD[29], 2.000, 167.000);
	TextDrawAlignment(LoginUITD[29], 1);
	TextDrawColor(LoginUITD[29], -92237754);
	TextDrawSetShadow(LoginUITD[29], 0);
	TextDrawSetOutline(LoginUITD[29], 0);
	TextDrawBackgroundColor(LoginUITD[29], 255);
	TextDrawFont(LoginUITD[29], 4);
	TextDrawSetProportional(LoginUITD[29], 1);

	LoginUITD[30] = TextDrawCreate(412.000, 311.000, "LD_DUAL:white");
	TextDrawTextSize(LoginUITD[30], 2.000, 393.000);
	TextDrawAlignment(LoginUITD[30], 1);
	TextDrawColor(LoginUITD[30], -92237754);
	TextDrawSetShadow(LoginUITD[30], 0);
	TextDrawSetOutline(LoginUITD[30], 0);
	TextDrawBackgroundColor(LoginUITD[30], 255);
	TextDrawFont(LoginUITD[30], 4);
	TextDrawSetProportional(LoginUITD[30], 1);

	LoginUITD[31] = TextDrawCreate(152.000, 212.000, "LD_DUAL:white");
	TextDrawTextSize(LoginUITD[31], 2.000, 114.000);
	TextDrawAlignment(LoginUITD[31], 1);
	TextDrawColor(LoginUITD[31], -92237754);
	TextDrawSetShadow(LoginUITD[31], 0);
	TextDrawSetOutline(LoginUITD[31], 0);
	TextDrawBackgroundColor(LoginUITD[31], 255);
	TextDrawFont(LoginUITD[31], 4);
	TextDrawSetProportional(LoginUITD[31], 1);

	LoginUITD[32] = TextDrawCreate(-18.000, -42.000, "LD_CHAT:dpad_64");
	TextDrawTextSize(LoginUITD[32], 682.000, 1015.000);
	TextDrawAlignment(LoginUITD[32], 1);
	TextDrawColor(LoginUITD[32], 70);
	TextDrawSetShadow(LoginUITD[32], 0);
	TextDrawSetOutline(LoginUITD[32], 0);
	TextDrawBackgroundColor(LoginUITD[32], 255);
	TextDrawFont(LoginUITD[32], 4);
	TextDrawSetProportional(LoginUITD[32], 1);

	LoginUITD[33] = TextDrawCreate(-18.000, 482.000, "LD_CHAT:dpad_64");
	TextDrawTextSize(LoginUITD[33], 682.000, -1015.000);
	TextDrawAlignment(LoginUITD[33], 1);
	TextDrawColor(LoginUITD[33], 70);
	TextDrawSetShadow(LoginUITD[33], 0);
	TextDrawSetOutline(LoginUITD[33], 0);
	TextDrawBackgroundColor(LoginUITD[33], 255);
	TextDrawFont(LoginUITD[33], 4);
	TextDrawSetProportional(LoginUITD[33], 1);
}

CreateCharSelTD()
{
	CharSelTD[0] = TextDrawCreate(648.000, -610.000, "LD_CHAT:dpad_lr");
	TextDrawTextSize(CharSelTD[0], -6000.000, 2000.000);
	TextDrawAlignment(CharSelTD[0], 1);
	TextDrawColor(CharSelTD[0], 165);
	TextDrawSetShadow(CharSelTD[0], 0);
	TextDrawSetOutline(CharSelTD[0], 0);
	TextDrawBackgroundColor(CharSelTD[0], 255);
	TextDrawFont(CharSelTD[0], 4);
	TextDrawSetProportional(CharSelTD[0], 1);

	CharSelTD[1] = TextDrawCreate(362.000, -39.000, "LD_DUAL:white");
	TextDrawTextSize(CharSelTD[1], 2.000, 371.000);
	TextDrawAlignment(CharSelTD[1], 1);
	TextDrawColor(CharSelTD[1], -92237754);
	TextDrawSetShadow(CharSelTD[1], 0);
	TextDrawSetOutline(CharSelTD[1], 0);
	TextDrawBackgroundColor(CharSelTD[1], 255);
	TextDrawFont(CharSelTD[1], 4);
	TextDrawSetProportional(CharSelTD[1], 1);

	CharSelTD[2] = TextDrawCreate(418.000, 94.000, "LD_DUAL:white");
	TextDrawTextSize(CharSelTD[2], 2.000, 371.000);
	TextDrawAlignment(CharSelTD[2], 1);
	TextDrawColor(CharSelTD[2], -92237754);
	TextDrawSetShadow(CharSelTD[2], 0);
	TextDrawSetOutline(CharSelTD[2], 0);
	TextDrawBackgroundColor(CharSelTD[2], 255);
	TextDrawFont(CharSelTD[2], 4);
	TextDrawSetProportional(CharSelTD[2], 1);

	CharSelTD[3] = TextDrawCreate(514.000, -329.000, "LD_DUAL:white");
	TextDrawTextSize(CharSelTD[3], 2.000, 371.000);
	TextDrawAlignment(CharSelTD[3], 1);
	TextDrawColor(CharSelTD[3], -92237754);
	TextDrawSetShadow(CharSelTD[3], 0);
	TextDrawSetOutline(CharSelTD[3], 0);
	TextDrawBackgroundColor(CharSelTD[3], 255);
	TextDrawFont(CharSelTD[3], 4);
	TextDrawSetProportional(CharSelTD[3], 1);

	CharSelTD[4] = TextDrawCreate(516.000, 40.000, "LD_DUAL:white");
	TextDrawTextSize(CharSelTD[4], 200.000, 2.000);
	TextDrawAlignment(CharSelTD[4], 1);
	TextDrawColor(CharSelTD[4], -92237754);
	TextDrawSetShadow(CharSelTD[4], 0);
	TextDrawSetOutline(CharSelTD[4], 0);
	TextDrawBackgroundColor(CharSelTD[4], 255);
	TextDrawFont(CharSelTD[4], 4);
	TextDrawSetProportional(CharSelTD[4], 1);

	CharSelTD[5] = TextDrawCreate(442.000, 18.000, "LD_DUAL:white");
	TextDrawTextSize(CharSelTD[5], 200.000, 2.000);
	TextDrawAlignment(CharSelTD[5], 1);
	TextDrawColor(CharSelTD[5], -92237754);
	TextDrawSetShadow(CharSelTD[5], 0);
	TextDrawSetOutline(CharSelTD[5], 0);
	TextDrawBackgroundColor(CharSelTD[5], 255);
	TextDrawFont(CharSelTD[5], 4);
	TextDrawSetProportional(CharSelTD[5], 1);

	CharSelTD[6] = TextDrawCreate(586.000, 390.000, "LD_DUAL:white");
	TextDrawTextSize(CharSelTD[6], 200.000, 2.000);
	TextDrawAlignment(CharSelTD[6], 1);
	TextDrawColor(CharSelTD[6], -92237754);
	TextDrawSetShadow(CharSelTD[6], 0);
	TextDrawSetOutline(CharSelTD[6], 0);
	TextDrawBackgroundColor(CharSelTD[6], 255);
	TextDrawFont(CharSelTD[6], 4);
	TextDrawSetProportional(CharSelTD[6], 1);

	CharSelTD[7] = TextDrawCreate(496.000, 353.000, "LD_DUAL:white");
	TextDrawTextSize(CharSelTD[7], 200.000, 2.000);
	TextDrawAlignment(CharSelTD[7], 1);
	TextDrawColor(CharSelTD[7], -92237754);
	TextDrawSetShadow(CharSelTD[7], 0);
	TextDrawSetOutline(CharSelTD[7], 0);
	TextDrawBackgroundColor(CharSelTD[7], 255);
	TextDrawFont(CharSelTD[7], 4);
	TextDrawSetProportional(CharSelTD[7], 1);

	CharSelTD[8] = TextDrawCreate(420.000, 94.000, "LD_DUAL:white");
	TextDrawTextSize(CharSelTD[8], 139.000, 2.000);
	TextDrawAlignment(CharSelTD[8], 1);
	TextDrawColor(CharSelTD[8], -92237754);
	TextDrawSetShadow(CharSelTD[8], 0);
	TextDrawSetOutline(CharSelTD[8], 0);
	TextDrawBackgroundColor(CharSelTD[8], 255);
	TextDrawFont(CharSelTD[8], 4);
	TextDrawSetProportional(CharSelTD[8], 1);

	CharSelTD[9] = TextDrawCreate(583.000, 94.000, "LD_DUAL:white");
	TextDrawTextSize(CharSelTD[9], 2.000, 403.000);
	TextDrawAlignment(CharSelTD[9], 1);
	TextDrawColor(CharSelTD[9], -92237754);
	TextDrawSetShadow(CharSelTD[9], 0);
	TextDrawSetOutline(CharSelTD[9], 0);
	TextDrawBackgroundColor(CharSelTD[9], 255);
	TextDrawFont(CharSelTD[9], 4);
	TextDrawSetProportional(CharSelTD[9], 1);

	CharSelTD[10] = TextDrawCreate(480.000, 278.000, "LD_DUAL:white");
	TextDrawTextSize(CharSelTD[10], 72.000, 2.000);
	TextDrawAlignment(CharSelTD[10], 1);
	TextDrawColor(CharSelTD[10], -92237754);
	TextDrawSetShadow(CharSelTD[10], 0);
	TextDrawSetOutline(CharSelTD[10], 0);
	TextDrawBackgroundColor(CharSelTD[10], 255);
	TextDrawFont(CharSelTD[10], 4);
	TextDrawSetProportional(CharSelTD[10], 1);

	CharSelTD[11] = TextDrawCreate(450.000, 314.000, "LD_DUAL:white");
	TextDrawTextSize(CharSelTD[11], 173.000, 2.000);
	TextDrawAlignment(CharSelTD[11], 1);
	TextDrawColor(CharSelTD[11], -92237754);
	TextDrawSetShadow(CharSelTD[11], 0);
	TextDrawSetOutline(CharSelTD[11], 0);
	TextDrawBackgroundColor(CharSelTD[11], 255);
	TextDrawFont(CharSelTD[11], 4);
	TextDrawSetProportional(CharSelTD[11], 1);

	CharSelTD[12] = TextDrawCreate(490.000, 77.000, "LD_DUAL:white");
	TextDrawTextSize(CharSelTD[12], 102.000, 24.500);
	TextDrawAlignment(CharSelTD[12], 1);
	TextDrawColor(CharSelTD[12], 0);
	TextDrawSetShadow(CharSelTD[12], 0);
	TextDrawSetOutline(CharSelTD[12], 0);
	TextDrawBackgroundColor(CharSelTD[12], 255);
	TextDrawFont(CharSelTD[12], 4);
	TextDrawSetProportional(CharSelTD[12], 1);
	TextDrawSetSelectable(CharSelTD[12], 1);

	CharSelTD[13] = TextDrawCreate(450.000, 316.000, "LD_DUAL:white");
	TextDrawTextSize(CharSelTD[13], 2.000, 403.000);
	TextDrawAlignment(CharSelTD[13], 1);
	TextDrawColor(CharSelTD[13], -92237754);
	TextDrawSetShadow(CharSelTD[13], 0);
	TextDrawSetOutline(CharSelTD[13], 0);
	TextDrawBackgroundColor(CharSelTD[13], 255);
	TextDrawFont(CharSelTD[13], 4);
	TextDrawSetProportional(CharSelTD[13], 1);

	CharSelTD[14] = TextDrawCreate(449.000, 128.000, "LD_DUAL:white");
	TextDrawTextSize(CharSelTD[14], 72.000, 2.000);
	TextDrawAlignment(CharSelTD[14], 1);
	TextDrawColor(CharSelTD[14], -92237754);
	TextDrawSetShadow(CharSelTD[14], 0);
	TextDrawSetOutline(CharSelTD[14], 0);
	TextDrawBackgroundColor(CharSelTD[14], 255);
	TextDrawFont(CharSelTD[14], 4);
	TextDrawSetProportional(CharSelTD[14], 1);

	CharSelTD[15] = TextDrawCreate(449.000, 130.000, "LD_DUAL:white");
	TextDrawTextSize(CharSelTD[15], 2.000, 148.000);
	TextDrawAlignment(CharSelTD[15], 1);
	TextDrawColor(CharSelTD[15], -92237754);
	TextDrawSetShadow(CharSelTD[15], 0);
	TextDrawSetOutline(CharSelTD[15], 0);
	TextDrawBackgroundColor(CharSelTD[15], 255);
	TextDrawFont(CharSelTD[15], 4);
	TextDrawSetProportional(CharSelTD[15], 1);

	CharSelTD[16] = TextDrawCreate(550.000, 130.000, "LD_DUAL:white");
	TextDrawTextSize(CharSelTD[16], 2.000, 148.000);
	TextDrawAlignment(CharSelTD[16], 1);
	TextDrawColor(CharSelTD[16], -92237754);
	TextDrawSetShadow(CharSelTD[16], 0);
	TextDrawSetOutline(CharSelTD[16], 0);
	TextDrawBackgroundColor(CharSelTD[16], 255);
	TextDrawFont(CharSelTD[16], 4);
	TextDrawSetProportional(CharSelTD[16], 1);

	CharSelTD[17] = TextDrawCreate(133.000, 351.000, "LD_DUAL:white");
	TextDrawTextSize(CharSelTD[17], 89.000, 20.500);
	TextDrawAlignment(CharSelTD[17], 1);
	TextDrawColor(CharSelTD[17], 0);
	TextDrawSetShadow(CharSelTD[17], 0);
	TextDrawSetOutline(CharSelTD[17], 0);
	TextDrawBackgroundColor(CharSelTD[17], 255);
	TextDrawFont(CharSelTD[17], 4);
	TextDrawSetProportional(CharSelTD[17], 1);
	TextDrawSetSelectable(CharSelTD[17], 1);

	CharSelTD[18] = TextDrawCreate(490.000, 106.000, "LD_DUAL:white");
	TextDrawTextSize(CharSelTD[18], 102.000, 24.500);
	TextDrawAlignment(CharSelTD[18], 1);
	TextDrawColor(CharSelTD[18], 0);
	TextDrawSetShadow(CharSelTD[18], 0);
	TextDrawSetOutline(CharSelTD[18], 0);
	TextDrawBackgroundColor(CharSelTD[18], 255);
	TextDrawFont(CharSelTD[18], 4);
	TextDrawSetProportional(CharSelTD[18], 1);
	TextDrawSetSelectable(CharSelTD[18], 1);

	CharSelTD[19] = TextDrawCreate(491.000, 77.000, "LD_DUAL:white");
	TextDrawTextSize(CharSelTD[19], 102.000, 24.500);
	TextDrawAlignment(CharSelTD[19], 1);
	TextDrawColor(CharSelTD[19], 421075455);
	TextDrawSetShadow(CharSelTD[19], 0);
	TextDrawSetOutline(CharSelTD[19], 0);
	TextDrawBackgroundColor(CharSelTD[19], 255);
	TextDrawFont(CharSelTD[19], 4);
	TextDrawSetProportional(CharSelTD[19], 1);

	CharSelTD[20] = TextDrawCreate(490.000, 135.000, "LD_DUAL:white");
	TextDrawTextSize(CharSelTD[20], 102.000, 24.500);
	TextDrawAlignment(CharSelTD[20], 1);
	TextDrawColor(CharSelTD[20], 0);
	TextDrawSetShadow(CharSelTD[20], 0);
	TextDrawSetOutline(CharSelTD[20], 0);
	TextDrawBackgroundColor(CharSelTD[20], 255);
	TextDrawFont(CharSelTD[20], 4);
	TextDrawSetProportional(CharSelTD[20], 1);
	TextDrawSetSelectable(CharSelTD[20], 1);

	CharSelTD[21] = TextDrawCreate(493.500, 90.000, "#1");
	TextDrawLetterSize(CharSelTD[21], 0.158, 0.799);
	TextDrawAlignment(CharSelTD[21], 1);
	TextDrawColor(CharSelTD[21], -926365441);
	TextDrawSetShadow(CharSelTD[21], 1);
	TextDrawSetOutline(CharSelTD[21], 1);
	TextDrawBackgroundColor(CharSelTD[21], 0);
	TextDrawFont(CharSelTD[21], 1);
	TextDrawSetProportional(CharSelTD[21], 1);

	CharSelTD[22] = TextDrawCreate(574.000, 78.000, "LD_BEAT:chit");
	TextDrawTextSize(CharSelTD[22], 18.000, 22.000);
	TextDrawAlignment(CharSelTD[22], 1);
	TextDrawColor(CharSelTD[22], -1263225601);
	TextDrawSetShadow(CharSelTD[22], 0);
	TextDrawSetOutline(CharSelTD[22], 0);
	TextDrawBackgroundColor(CharSelTD[22], 255);
	TextDrawFont(CharSelTD[22], 4);
	TextDrawSetProportional(CharSelTD[22], 1);

	CharSelTD[23] = TextDrawCreate(575.500, 79.500, "LD_BEAT:chit");
	TextDrawTextSize(CharSelTD[23], 15.000, 19.100);
	TextDrawAlignment(CharSelTD[23], 1);
	TextDrawColor(CharSelTD[23], 421075455);
	TextDrawSetShadow(CharSelTD[23], 0);
	TextDrawSetOutline(CharSelTD[23], 0);
	TextDrawBackgroundColor(CharSelTD[23], 255);
	TextDrawFont(CharSelTD[23], 4);
	TextDrawSetProportional(CharSelTD[23], 1);

	CharSelTD[24] = TextDrawCreate(582.500, 89.000, "LD_DUAL:white");
	TextDrawTextSize(CharSelTD[24], 8.000, 10.000);
	TextDrawAlignment(CharSelTD[24], 1);
	TextDrawColor(CharSelTD[24], 421075455);
	TextDrawSetShadow(CharSelTD[24], 0);
	TextDrawSetOutline(CharSelTD[24], 0);
	TextDrawBackgroundColor(CharSelTD[24], 255);
	TextDrawFont(CharSelTD[24], 4);
	TextDrawSetProportional(CharSelTD[24], 1);

	CharSelTD[25] = TextDrawCreate(580.098, 84.000, "LD_BEAT:chit");
	TextDrawTextSize(CharSelTD[25], 6.000, 7.500);
	TextDrawAlignment(CharSelTD[25], 1);
	TextDrawColor(CharSelTD[25], -1263225601);
	TextDrawSetShadow(CharSelTD[25], 0);
	TextDrawSetOutline(CharSelTD[25], 0);
	TextDrawBackgroundColor(CharSelTD[25], 255);
	TextDrawFont(CharSelTD[25], 4);
	TextDrawSetProportional(CharSelTD[25], 1);

	CharSelTD[26] = TextDrawCreate(581.098, 85.000, "LD_BEAT:chit");
	TextDrawTextSize(CharSelTD[26], 4.000, 5.500);
	TextDrawAlignment(CharSelTD[26], 1);
	TextDrawColor(CharSelTD[26], 421075455);
	TextDrawSetShadow(CharSelTD[26], 0);
	TextDrawSetOutline(CharSelTD[26], 0);
	TextDrawBackgroundColor(CharSelTD[26], 255);
	TextDrawFont(CharSelTD[26], 4);
	TextDrawSetProportional(CharSelTD[26], 1);

	CharSelTD[27] = TextDrawCreate(578.799, 89.000, "LD_BEAT:chit");
	TextDrawTextSize(CharSelTD[27], 9.300, 7.000);
	TextDrawAlignment(CharSelTD[27], 1);
	TextDrawColor(CharSelTD[27], -1263225601);
	TextDrawSetShadow(CharSelTD[27], 0);
	TextDrawSetOutline(CharSelTD[27], 0);
	TextDrawBackgroundColor(CharSelTD[27], 255);
	TextDrawFont(CharSelTD[27], 4);
	TextDrawSetProportional(CharSelTD[27], 1);

	CharSelTD[28] = TextDrawCreate(578.799, 90.000, "LD_BEAT:chit");
	TextDrawTextSize(CharSelTD[28], 9.300, 7.000);
	TextDrawAlignment(CharSelTD[28], 1);
	TextDrawColor(CharSelTD[28], 421075455);
	TextDrawSetShadow(CharSelTD[28], 0);
	TextDrawSetOutline(CharSelTD[28], 0);
	TextDrawBackgroundColor(CharSelTD[28], 255);
	TextDrawFont(CharSelTD[28], 4);
	TextDrawSetProportional(CharSelTD[28], 1);

	CharSelTD[29] = TextDrawCreate(491.000, 106.000, "LD_DUAL:white");
	TextDrawTextSize(CharSelTD[29], 102.000, 24.500);
	TextDrawAlignment(CharSelTD[29], 1);
	TextDrawColor(CharSelTD[29], 421075455);
	TextDrawSetShadow(CharSelTD[29], 0);
	TextDrawSetOutline(CharSelTD[29], 0);
	TextDrawBackgroundColor(CharSelTD[29], 255);
	TextDrawFont(CharSelTD[29], 4);
	TextDrawSetProportional(CharSelTD[29], 1);

	CharSelTD[30] = TextDrawCreate(493.500, 119.000, "#2");
	TextDrawLetterSize(CharSelTD[30], 0.158, 0.799);
	TextDrawAlignment(CharSelTD[30], 1);
	TextDrawColor(CharSelTD[30], -926365441);
	TextDrawSetShadow(CharSelTD[30], 1);
	TextDrawSetOutline(CharSelTD[30], 1);
	TextDrawBackgroundColor(CharSelTD[30], 0);
	TextDrawFont(CharSelTD[30], 1);
	TextDrawSetProportional(CharSelTD[30], 1);

	CharSelTD[31] = TextDrawCreate(574.000, 107.000, "LD_BEAT:chit");
	TextDrawTextSize(CharSelTD[31], 18.000, 22.000);
	TextDrawAlignment(CharSelTD[31], 1);
	TextDrawColor(CharSelTD[31], -1263225601);
	TextDrawSetShadow(CharSelTD[31], 0);
	TextDrawSetOutline(CharSelTD[31], 0);
	TextDrawBackgroundColor(CharSelTD[31], 255);
	TextDrawFont(CharSelTD[31], 4);
	TextDrawSetProportional(CharSelTD[31], 1);

	CharSelTD[32] = TextDrawCreate(575.500, 108.500, "LD_BEAT:chit");
	TextDrawTextSize(CharSelTD[32], 15.000, 19.100);
	TextDrawAlignment(CharSelTD[32], 1);
	TextDrawColor(CharSelTD[32], 421075455);
	TextDrawSetShadow(CharSelTD[32], 0);
	TextDrawSetOutline(CharSelTD[32], 0);
	TextDrawBackgroundColor(CharSelTD[32], 255);
	TextDrawFont(CharSelTD[32], 4);
	TextDrawSetProportional(CharSelTD[32], 1);

	CharSelTD[33] = TextDrawCreate(582.500, 118.000, "LD_DUAL:white");
	TextDrawTextSize(CharSelTD[33], 8.000, 10.000);
	TextDrawAlignment(CharSelTD[33], 1);
	TextDrawColor(CharSelTD[33], 421075455);
	TextDrawSetShadow(CharSelTD[33], 0);
	TextDrawSetOutline(CharSelTD[33], 0);
	TextDrawBackgroundColor(CharSelTD[33], 255);
	TextDrawFont(CharSelTD[33], 4);
	TextDrawSetProportional(CharSelTD[33], 1);

	CharSelTD[34] = TextDrawCreate(580.098, 113.000, "LD_BEAT:chit");
	TextDrawTextSize(CharSelTD[34], 6.000, 7.500);
	TextDrawAlignment(CharSelTD[34], 1);
	TextDrawColor(CharSelTD[34], -1263225601);
	TextDrawSetShadow(CharSelTD[34], 0);
	TextDrawSetOutline(CharSelTD[34], 0);
	TextDrawBackgroundColor(CharSelTD[34], 255);
	TextDrawFont(CharSelTD[34], 4);
	TextDrawSetProportional(CharSelTD[34], 1);

	CharSelTD[35] = TextDrawCreate(581.098, 114.000, "LD_BEAT:chit");
	TextDrawTextSize(CharSelTD[35], 4.000, 5.500);
	TextDrawAlignment(CharSelTD[35], 1);
	TextDrawColor(CharSelTD[35], 421075455);
	TextDrawSetShadow(CharSelTD[35], 0);
	TextDrawSetOutline(CharSelTD[35], 0);
	TextDrawBackgroundColor(CharSelTD[35], 255);
	TextDrawFont(CharSelTD[35], 4);
	TextDrawSetProportional(CharSelTD[35], 1);

	CharSelTD[36] = TextDrawCreate(578.799, 118.000, "LD_BEAT:chit");
	TextDrawTextSize(CharSelTD[36], 9.300, 7.000);
	TextDrawAlignment(CharSelTD[36], 1);
	TextDrawColor(CharSelTD[36], -1263225601);
	TextDrawSetShadow(CharSelTD[36], 0);
	TextDrawSetOutline(CharSelTD[36], 0);
	TextDrawBackgroundColor(CharSelTD[36], 255);
	TextDrawFont(CharSelTD[36], 4);
	TextDrawSetProportional(CharSelTD[36], 1);

	CharSelTD[37] = TextDrawCreate(578.799, 119.000, "LD_BEAT:chit");
	TextDrawTextSize(CharSelTD[37], 9.300, 7.000);
	TextDrawAlignment(CharSelTD[37], 1);
	TextDrawColor(CharSelTD[37], 421075455);
	TextDrawSetShadow(CharSelTD[37], 0);
	TextDrawSetOutline(CharSelTD[37], 0);
	TextDrawBackgroundColor(CharSelTD[37], 255);
	TextDrawFont(CharSelTD[37], 4);
	TextDrawSetProportional(CharSelTD[37], 1);

	CharSelTD[38] = TextDrawCreate(491.000, 135.000, "LD_DUAL:white");
	TextDrawTextSize(CharSelTD[38], 102.000, 24.500);
	TextDrawAlignment(CharSelTD[38], 1);
	TextDrawColor(CharSelTD[38], 421075455);
	TextDrawSetShadow(CharSelTD[38], 0);
	TextDrawSetOutline(CharSelTD[38], 0);
	TextDrawBackgroundColor(CharSelTD[38], 255);
	TextDrawFont(CharSelTD[38], 4);
	TextDrawSetProportional(CharSelTD[38], 1);

	CharSelTD[39] = TextDrawCreate(493.500, 148.000, "#3");
	TextDrawLetterSize(CharSelTD[39], 0.158, 0.799);
	TextDrawAlignment(CharSelTD[39], 1);
	TextDrawColor(CharSelTD[39], -926365441);
	TextDrawSetShadow(CharSelTD[39], 1);
	TextDrawSetOutline(CharSelTD[39], 1);
	TextDrawBackgroundColor(CharSelTD[39], 0);
	TextDrawFont(CharSelTD[39], 1);
	TextDrawSetProportional(CharSelTD[39], 1);

	CharSelTD[40] = TextDrawCreate(574.000, 136.000, "LD_BEAT:chit");
	TextDrawTextSize(CharSelTD[40], 18.000, 22.000);
	TextDrawAlignment(CharSelTD[40], 1);
	TextDrawColor(CharSelTD[40], -1263225601);
	TextDrawSetShadow(CharSelTD[40], 0);
	TextDrawSetOutline(CharSelTD[40], 0);
	TextDrawBackgroundColor(CharSelTD[40], 255);
	TextDrawFont(CharSelTD[40], 4);
	TextDrawSetProportional(CharSelTD[40], 1);

	CharSelTD[41] = TextDrawCreate(575.500, 137.500, "LD_BEAT:chit");
	TextDrawTextSize(CharSelTD[41], 15.000, 19.100);
	TextDrawAlignment(CharSelTD[41], 1);
	TextDrawColor(CharSelTD[41], 421075455);
	TextDrawSetShadow(CharSelTD[41], 0);
	TextDrawSetOutline(CharSelTD[41], 0);
	TextDrawBackgroundColor(CharSelTD[41], 255);
	TextDrawFont(CharSelTD[41], 4);
	TextDrawSetProportional(CharSelTD[41], 1);

	CharSelTD[42] = TextDrawCreate(582.500, 147.000, "LD_DUAL:white");
	TextDrawTextSize(CharSelTD[42], 8.000, 10.000);
	TextDrawAlignment(CharSelTD[42], 1);
	TextDrawColor(CharSelTD[42], 421075455);
	TextDrawSetShadow(CharSelTD[42], 0);
	TextDrawSetOutline(CharSelTD[42], 0);
	TextDrawBackgroundColor(CharSelTD[42], 255);
	TextDrawFont(CharSelTD[42], 4);
	TextDrawSetProportional(CharSelTD[42], 1);

	CharSelTD[43] = TextDrawCreate(580.098, 142.000, "LD_BEAT:chit");
	TextDrawTextSize(CharSelTD[43], 6.000, 7.500);
	TextDrawAlignment(CharSelTD[43], 1);
	TextDrawColor(CharSelTD[43], -1263225601);
	TextDrawSetShadow(CharSelTD[43], 0);
	TextDrawSetOutline(CharSelTD[43], 0);
	TextDrawBackgroundColor(CharSelTD[43], 255);
	TextDrawFont(CharSelTD[43], 4);
	TextDrawSetProportional(CharSelTD[43], 1);

	CharSelTD[44] = TextDrawCreate(581.098, 143.000, "LD_BEAT:chit");
	TextDrawTextSize(CharSelTD[44], 4.000, 5.500);
	TextDrawAlignment(CharSelTD[44], 1);
	TextDrawColor(CharSelTD[44], 421075455);
	TextDrawSetShadow(CharSelTD[44], 0);
	TextDrawSetOutline(CharSelTD[44], 0);
	TextDrawBackgroundColor(CharSelTD[44], 255);
	TextDrawFont(CharSelTD[44], 4);
	TextDrawSetProportional(CharSelTD[44], 1);

	CharSelTD[45] = TextDrawCreate(490.500, 59.500, "KARAKTER");
	TextDrawLetterSize(CharSelTD[45], 0.337, 1.498);
	TextDrawAlignment(CharSelTD[45], 1);
	TextDrawColor(CharSelTD[45], -1);
	TextDrawSetShadow(CharSelTD[45], 1);
	TextDrawSetOutline(CharSelTD[45], 1);
	TextDrawBackgroundColor(CharSelTD[45], 0);
	TextDrawFont(CharSelTD[45], 1);
	TextDrawSetProportional(CharSelTD[45], 1);

	CharSelTD[46] = TextDrawCreate(578.799, 147.000, "LD_BEAT:chit");
	TextDrawTextSize(CharSelTD[46], 9.300, 7.000);
	TextDrawAlignment(CharSelTD[46], 1);
	TextDrawColor(CharSelTD[46], -1263225601);
	TextDrawSetShadow(CharSelTD[46], 0);
	TextDrawSetOutline(CharSelTD[46], 0);
	TextDrawBackgroundColor(CharSelTD[46], 255);
	TextDrawFont(CharSelTD[46], 4);
	TextDrawSetProportional(CharSelTD[46], 1);

	CharSelTD[47] = TextDrawCreate(578.799, 148.000, "LD_BEAT:chit");
	TextDrawTextSize(CharSelTD[47], 9.300, 7.000);
	TextDrawAlignment(CharSelTD[47], 1);
	TextDrawColor(CharSelTD[47], 421075455);
	TextDrawSetShadow(CharSelTD[47], 0);
	TextDrawSetOutline(CharSelTD[47], 0);
	TextDrawBackgroundColor(CharSelTD[47], 255);
	TextDrawFont(CharSelTD[47], 4);
	TextDrawSetProportional(CharSelTD[47], 1);

	CharSelTD[48] = TextDrawCreate(134.000, 351.000, "LD_DUAL:white");
	TextDrawTextSize(CharSelTD[48], 89.000, 20.500);
	TextDrawAlignment(CharSelTD[48], 1);
	TextDrawColor(CharSelTD[48], 421075455);
	TextDrawSetShadow(CharSelTD[48], 0);
	TextDrawSetOutline(CharSelTD[48], 0);
	TextDrawBackgroundColor(CharSelTD[48], 255);
	TextDrawFont(CharSelTD[48], 4);
	TextDrawSetProportional(CharSelTD[48], 1);

	CharSelTD[49] = TextDrawCreate(179.000, 352.000, "Pilih");
	TextDrawLetterSize(CharSelTD[49], 0.418, 1.799);
	TextDrawAlignment(CharSelTD[49], 2);
	TextDrawColor(CharSelTD[49], -1);
	TextDrawSetShadow(CharSelTD[49], 1);
	TextDrawSetOutline(CharSelTD[49], 1);
	TextDrawBackgroundColor(CharSelTD[49], 0);
	TextDrawFont(CharSelTD[49], 3);
	TextDrawSetProportional(CharSelTD[49], 1);
}

CreatePCharSelTextdraw(playerid)
{
    CharSelPTD[playerid][0] = CreatePlayerTextDraw(playerid, 493.500, 78.500, "Kosong");
	PlayerTextDrawLetterSize(playerid, CharSelPTD[playerid][0], 0.180, 1.098);
	PlayerTextDrawAlignment(playerid, CharSelPTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, CharSelPTD[playerid][0], -252645121);
	PlayerTextDrawSetShadow(playerid, CharSelPTD[playerid][0], 1);
	PlayerTextDrawSetOutline(playerid, CharSelPTD[playerid][0], 1);
	PlayerTextDrawBackgroundColor(playerid, CharSelPTD[playerid][0], 0);
	PlayerTextDrawFont(playerid, CharSelPTD[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, CharSelPTD[playerid][0], 1);

	CharSelPTD[playerid][1] = CreatePlayerTextDraw(playerid, 493.500, 107.500, "Kosong");
	PlayerTextDrawLetterSize(playerid, CharSelPTD[playerid][1], 0.180, 1.098);
	PlayerTextDrawAlignment(playerid, CharSelPTD[playerid][1], 1);
	PlayerTextDrawColor(playerid, CharSelPTD[playerid][1], -252645121);
	PlayerTextDrawSetShadow(playerid, CharSelPTD[playerid][1], 1);
	PlayerTextDrawSetOutline(playerid, CharSelPTD[playerid][1], 1);
	PlayerTextDrawBackgroundColor(playerid, CharSelPTD[playerid][1], 0);
	PlayerTextDrawFont(playerid, CharSelPTD[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, CharSelPTD[playerid][1], 1);

	CharSelPTD[playerid][2] = CreatePlayerTextDraw(playerid, 493.500, 136.500, "Kosong");
	PlayerTextDrawLetterSize(playerid, CharSelPTD[playerid][2], 0.180, 1.098);
	PlayerTextDrawAlignment(playerid, CharSelPTD[playerid][2], 1);
	PlayerTextDrawColor(playerid, CharSelPTD[playerid][2], -252645121);
	PlayerTextDrawSetShadow(playerid, CharSelPTD[playerid][2], 1);
	PlayerTextDrawSetOutline(playerid, CharSelPTD[playerid][2], 1);
	PlayerTextDrawBackgroundColor(playerid, CharSelPTD[playerid][2], 0);
	PlayerTextDrawFont(playerid, CharSelPTD[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, CharSelPTD[playerid][2], 1);
}

ShowLoginTD(playerid)
{
	for(new x; x < 34; x++)
	{
		TextDrawShowForPlayer(playerid, LoginUITD[x]);
	}
}

HideLoginUITD(playerid)
{
	for(new x; x < 34; x++)
	{
		TextDrawHideForPlayer(playerid, LoginUITD[x]);
	}
}

HideCharSelectTD(playerid)
{
	for(new x; x < 50; x++)
	{
		TextDrawHideForPlayer(playerid, CharSelTD[x]);
	}

	for(new x; x < 3; x++)
	{
		PlayerTextDrawHide(playerid, CharSelPTD[playerid][x]);
	}
	CancelSelectTextDraw(playerid);
}