new PlayerText: SelectCharTD[MAX_PLAYERS][37];
new LastCharCam[MAX_PLAYERS]; // Variabel pengingat posisi kamera terakhir

// Array Data Kamera {PosX, PosY, PosZ, LookX, LookY, LookZ}
new const Float:LobbyCamData[6][6] = {
    {1853.851440, -1592.242675, 31.438648, 1853.166992, -1591.557617, 31.189294}, // Slot 0 (Char 1)
    {1851.724975, -1592.776489, 31.339223, 1850.890869, -1592.252075, 31.168262}, // Slot 1 (Char 2)
    {1850.589111, -1586.461669, 31.260410, 1851.575073, -1586.400634, 31.105276}, // Slot 2 (Char 3)
    {1856.850341, -1589.794067, 31.711511, 1857.625732, -1589.178100, 31.572244}, // Slot 3 (Char 4)
    {1858.992553, -1586.679565, 32.117515, 1859.948852, -1586.697143, 31.825696}, // Slot 4 (Char 5)
    {1852.551147, -1593.898437, 32.510368, 1852.583496, -1594.897705, 32.531063}  // Slot 5 (Select Spawn)
};

OnLoadSelectCharTD(playerid)
{
	SelectCharTD[playerid][0] = CreatePlayerTextDraw(playerid, 25.000, 137.000, "ld_dual:white");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][0], 0.600, 2.000);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][0], 140.000, 30.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][0], -602653441);
	PlayerTextDrawUseBox(playerid, SelectCharTD[playerid][0], 1);
	PlayerTextDrawBoxColor(playerid, SelectCharTD[playerid][0], 50);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][0], 1);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][0], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][0], 4);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][0], 1);
	PlayerTextDrawSetSelectable(playerid, SelectCharTD[playerid][0], 1);

	SelectCharTD[playerid][1] = CreatePlayerTextDraw(playerid, 25.000, 169.000, "ld_dual:white");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][1], 0.600, 2.000);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][1], 140.000, 30.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][1], 1);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][1], 421075225);
	PlayerTextDrawUseBox(playerid, SelectCharTD[playerid][1], 1);
	PlayerTextDrawBoxColor(playerid, SelectCharTD[playerid][1], 50);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][1], 1);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][1], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][1], 4);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][1], 1);
	PlayerTextDrawSetSelectable(playerid, SelectCharTD[playerid][1], 1);

	SelectCharTD[playerid][2] = CreatePlayerTextDraw(playerid, 25.000, 202.000, "ld_dual:white");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][2], 0.600, 2.000);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][2], 140.000, 30.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][2], 1);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][2], 421075225);
	PlayerTextDrawUseBox(playerid, SelectCharTD[playerid][2], 1);
	PlayerTextDrawBoxColor(playerid, SelectCharTD[playerid][2], 50);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][2], 1);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][2], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][2], 4);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][2], 1);
	PlayerTextDrawSetSelectable(playerid, SelectCharTD[playerid][2], 1);

	SelectCharTD[playerid][3] = CreatePlayerTextDraw(playerid, 25.000, 234.000, "ld_dual:white");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][3], 0.600, 2.000);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][3], 140.000, 30.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][3], 1);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][3], 421075225);
	PlayerTextDrawUseBox(playerid, SelectCharTD[playerid][3], 1);
	PlayerTextDrawBoxColor(playerid, SelectCharTD[playerid][3], 50);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][3], 1);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][3], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][3], 4);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][3], 1);
	PlayerTextDrawSetSelectable(playerid, SelectCharTD[playerid][3], 1);

	SelectCharTD[playerid][4] = CreatePlayerTextDraw(playerid, 25.000, 266.000, "ld_dual:white");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][4], 0.600, 2.000);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][4], 140.000, 30.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][4], 1);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][4], 421075225);
	PlayerTextDrawUseBox(playerid, SelectCharTD[playerid][4], 1);
	PlayerTextDrawBoxColor(playerid, SelectCharTD[playerid][4], 50);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][4], 1);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][4], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][4], 4);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][4], 1);
	PlayerTextDrawSetSelectable(playerid, SelectCharTD[playerid][4], 1);

	SelectCharTD[playerid][5] = CreatePlayerTextDraw(playerid, 35.000, 147.000, "ARTHUR_CLINTON");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][5], 0.173, 0.898);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][5], 400.000, 17.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][5], 1);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][5], -1);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][5], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][5], 1);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][5], 1);

	SelectCharTD[playerid][6] = CreatePlayerTextDraw(playerid, 35.000, 179.000, "ARTHUR_CLINTON");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][6], 0.173, 0.898);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][6], 400.000, 17.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][6], 1);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][6], -1);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][6], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][6], 1);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][6], 1);

	SelectCharTD[playerid][7] = CreatePlayerTextDraw(playerid, 35.000, 213.000, "ARTHUR_CLINTON");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][7], 0.173, 0.898);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][7], 400.000, 17.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][7], 1);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][7], -1);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][7], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][7], 1);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][7], 1);

	SelectCharTD[playerid][8] = CreatePlayerTextDraw(playerid, 35.000, 244.000, "ARTHUR_CLINTON");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][8], 0.173, 0.898);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][8], 400.000, 17.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][8], 1);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][8], -1);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][8], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][8], 1);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][8], 1);

	SelectCharTD[playerid][9] = CreatePlayerTextDraw(playerid, 35.000, 276.000, "ARTHUR_CLINTON");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][9], 0.173, 0.898);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][9], 400.000, 17.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][9], 1);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][9], -1);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][9], 0);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][9], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][9], 1);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][9], 1);

	SelectCharTD[playerid][10] = CreatePlayerTextDraw(playerid, 163.000, 157.000, "10-3-2023_17:34:25");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][10], 0.128, 0.800);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][10], 400.000, 17.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][10], 3);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][10], -1448498689);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][10], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][10], 0);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][10], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][10], 2);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][10], 1);

	SelectCharTD[playerid][11] = CreatePlayerTextDraw(playerid, 163.000, 189.000, "10-3-2023_17:34:25");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][11], 0.128, 0.800);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][11], 400.000, 17.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][11], 3);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][11], -1061109710);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][11], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][11], 0);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][11], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][11], 2);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][11], 1);

	SelectCharTD[playerid][12] = CreatePlayerTextDraw(playerid, 163.000, 222.000, "10-3-2023_17:34:25");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][12], 0.128, 0.800);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][12], 400.000, 17.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][12], 3);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][12], -1061109710);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][12], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][12], 0);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][12], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][12], 2);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][12], 1);

	SelectCharTD[playerid][13] = CreatePlayerTextDraw(playerid, 163.000, 254.000, "10-3-2023_17:34:25");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][13], 0.128, 0.800);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][13], 400.000, 17.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][13], 3);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][13], -1378294222);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][13], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][13], 0);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][13], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][13], 2);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][13], 1);

	SelectCharTD[playerid][14] = CreatePlayerTextDraw(playerid, 163.000, 286.000, "10-3-2023_17:34:25");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][14], 0.128, 0.800);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][14], 400.000, 17.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][14], 3);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][14], -1061109710);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][14], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][14], 0);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][14], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][14], 2);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][14], 1);

	SelectCharTD[playerid][15] = CreatePlayerTextDraw(playerid, 78.000, 179.000, "EMPTY SLOT");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][15], 0.172, 0.898);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][15], 400.000, 17.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][15], 1);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][15], -206);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][15], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][15], 0);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][15], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][15], 1);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][15], 1);

	SelectCharTD[playerid][16] = CreatePlayerTextDraw(playerid, 78.000, 213.000, "EMPTY SLOT");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][16], 0.172, 0.898);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][16], 400.000, 17.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][16], 1);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][16], -206);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][16], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][16], 0);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][16], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][16], 1);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][16], 1);

	SelectCharTD[playerid][17] = CreatePlayerTextDraw(playerid, 78.000, 244.000, "EMPTY SLOT");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][17], 0.172, 0.898);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][17], 400.000, 17.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][17], 1);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][17], -206);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][17], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][17], 0);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][17], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][17], 1);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][17], 1);

	SelectCharTD[playerid][18] = CreatePlayerTextDraw(playerid, 78.000, 276.000, "EMPTY SLOT");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][18], 0.172, 0.898);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][18], 400.000, 17.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][18], 1);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][18], -206);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][18], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][18], 0);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][18], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][18], 1);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][18], 1);

	SelectCharTD[playerid][19] = CreatePlayerTextDraw(playerid, 499.000, 137.000, "ld_dual:white");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][19], 0.600, 2.000);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][19], 115.000, 126.500);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][19], 1);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][19], 421075455);
	PlayerTextDrawUseBox(playerid, SelectCharTD[playerid][19], 1);
	PlayerTextDrawBoxColor(playerid, SelectCharTD[playerid][19], 50);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][19], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][19], 1);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][19], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][19], 4);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][19], 1);

	SelectCharTD[playerid][20] = CreatePlayerTextDraw(playerid, 499.000, 266.000, "ld_dual:white");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][20], 0.600, 2.000);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][20], 115.000, 30.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][20], 1);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][20], -602653441);
	PlayerTextDrawUseBox(playerid, SelectCharTD[playerid][20], 1);
	PlayerTextDrawBoxColor(playerid, SelectCharTD[playerid][20], 50);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][20], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][20], 1);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][20], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][20], 4);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][20], 1);
	PlayerTextDrawSetSelectable(playerid, SelectCharTD[playerid][20], 1);

	SelectCharTD[playerid][21] = CreatePlayerTextDraw(playerid, 557.000, 154.000, "ARTHUR_CLINTON");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][21], 0.173, 0.898);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][21], 400.000, 17.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][21], 2);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][21], -1);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][21], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][21], 0);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][21], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][21], 1);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][21], 1);

	SelectCharTD[playerid][22] = CreatePlayerTextDraw(playerid, 507.000, 178.000, "PID");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][22], 0.128, 0.800);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][22], 400.000, 17.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][22], 1);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][22], -1061109505);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][22], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][22], 0);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][22], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][22], 2);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][22], 1);

	SelectCharTD[playerid][23] = CreatePlayerTextDraw(playerid, 607.000, 178.000, "8000021473");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][23], 0.128, 0.800);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][23], 400.000, 17.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][23], 3);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][23], -1061109505);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][23], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][23], 0);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][23], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][23], 2);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][23], 1);

	SelectCharTD[playerid][24] = CreatePlayerTextDraw(playerid, 507.000, 187.000, "LEVEL");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][24], 0.128, 0.800);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][24], 400.000, 17.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][24], 1);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][24], -1061109505);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][24], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][24], 0);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][24], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][24], 2);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][24], 1);

	SelectCharTD[playerid][25] = CreatePlayerTextDraw(playerid, 607.000, 187.000, "1");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][25], 0.128, 0.800);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][25], 400.000, 17.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][25], 3);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][25], -1061109505);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][25], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][25], 0);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][25], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][25], 2);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][25], 1);

	SelectCharTD[playerid][26] = CreatePlayerTextDraw(playerid, 507.000, 197.000, "WALLET");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][26], 0.128, 0.800);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][26], 400.000, 17.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][26], 1);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][26], -1061109505);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][26], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][26], 0);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][26], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][26], 2);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][26], 1);

	SelectCharTD[playerid][27] = CreatePlayerTextDraw(playerid, 607.000, 197.000, "$1,000,000.00");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][27], 0.128, 0.800);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][27], 400.000, 17.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][27], 3);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][27], -1061109505);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][27], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][27], 0);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][27], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][27], 2);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][27], 1);

	SelectCharTD[playerid][28] = CreatePlayerTextDraw(playerid, 507.000, 207.000, "BANK");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][28], 0.128, 0.800);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][28], 400.000, 17.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][28], 1);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][28], -1061109505);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][28], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][28], 0);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][28], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][28], 2);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][28], 1);

	SelectCharTD[playerid][29] = CreatePlayerTextDraw(playerid, 607.000, 207.000, "$1,000,000.00");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][29], 0.128, 0.800);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][29], 400.000, 17.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][29], 3);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][29], -1061109505);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][29], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][29], 0);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][29], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][29], 2);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][29], 1);

	SelectCharTD[playerid][30] = CreatePlayerTextDraw(playerid, 507.000, 217.000, "SKIN");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][30], 0.128, 0.800);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][30], 400.000, 17.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][30], 1);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][30], -1061109505);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][30], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][30], 0);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][30], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][30], 2);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][30], 1);

	SelectCharTD[playerid][31] = CreatePlayerTextDraw(playerid, 607.000, 217.000, "BCMSHFLS_91");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][31], 0.128, 0.800);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][31], 400.000, 17.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][31], 3);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][31], -1061109505);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][31], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][31], 0);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][31], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][31], 2);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][31], 1);

	SelectCharTD[playerid][32] = CreatePlayerTextDraw(playerid, 557.000, 276.000, "SELECT");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][32], 0.172, 0.898);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][32], 400.000, 17.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][32], 2);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][32], -1);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][32], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][32], 0);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][32], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][32], 1);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][32], 1);

	SelectCharTD[playerid][33] = CreatePlayerTextDraw(playerid, 507.000, 227.000, "GOLD");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][33], 0.128, 0.800);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][33], 400.000, 17.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][33], 1);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][33], -1061109505);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][33], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][33], 0);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][33], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][33], 2);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][33], 1);

	SelectCharTD[playerid][34] = CreatePlayerTextDraw(playerid, 607.000, 227.000, "0");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][34], 0.128, 0.800);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][34], 400.000, 17.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][34], 3);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][34], -1061109505);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][34], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][34], 0);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][34], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][34], 2);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][34], 1);

	SelectCharTD[playerid][35] = CreatePlayerTextDraw(playerid, 507.000, 237.000, "VIP");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][35], 0.128, 0.800);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][35], 400.000, 17.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][35], 1);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][35], -1061109505);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][35], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][35], 0);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][35], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][35], 2);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][35], 1);

	SelectCharTD[playerid][36] = CreatePlayerTextDraw(playerid, 607.000, 237.000, "NO");
	PlayerTextDrawLetterSize(playerid, SelectCharTD[playerid][36], 0.128, 0.800);
	PlayerTextDrawTextSize(playerid, SelectCharTD[playerid][36], 400.000, 17.000);
	PlayerTextDrawAlignment(playerid, SelectCharTD[playerid][36], 3);
	PlayerTextDrawColor(playerid, SelectCharTD[playerid][36], -1061109505);
	PlayerTextDrawSetShadow(playerid, SelectCharTD[playerid][36], 0);
	PlayerTextDrawSetOutline(playerid, SelectCharTD[playerid][36], 0);
	PlayerTextDrawBackgroundColor(playerid, SelectCharTD[playerid][36], 255);
	PlayerTextDrawFont(playerid, SelectCharTD[playerid][36], 2);
	PlayerTextDrawSetProportional(playerid, SelectCharTD[playerid][36], 1);
}

ShowSelectCharTD(playerid, charselected)
{
    new str[128];

    // --- DATA KARAKTER TERPILIH (Panel Kanan) ---
    format(str, sizeof(str), "%s", PlayerChar[playerid][charselected]);
    PlayerTextDrawSetString(playerid, SelectCharTD[playerid][21], str);
    
    format(str, sizeof(str), "%s", FormatCharacterID(PlayerCharID[playerid][charselected]));
    PlayerTextDrawSetString(playerid, SelectCharTD[playerid][23], str);
    
    format(str, sizeof(str), "%d", PlayerCharLevel[playerid][charselected]);
    PlayerTextDrawSetString(playerid, SelectCharTD[playerid][25], str);
    
    format(str, sizeof(str), "$%s", FormatMoney(PlayerCharCash[playerid][charselected]));
    PlayerTextDrawSetString(playerid, SelectCharTD[playerid][27], str);
    
    format(str, sizeof(str), "$%s", FormatMoney(PlayerCharBank[playerid][charselected]));
    PlayerTextDrawSetString(playerid, SelectCharTD[playerid][29], str);
    
    format(str, sizeof(str), "%s - %d", GetSkinModelName(PlayerCharSkin[playerid][charselected]), PlayerCharSkin[playerid][charselected]);
    PlayerTextDrawSetString(playerid, SelectCharTD[playerid][31], str);
    
    format(str, sizeof(str), "%d", PlayerUCPGold[playerid]);
    PlayerTextDrawSetString(playerid, SelectCharTD[playerid][34], str);
    
    format(str, sizeof(str), "%s", PlayerUCPVipStatus[playerid]);
    PlayerTextDrawSetString(playerid, SelectCharTD[playerid][36], str);

	for(new i = 19; i < 37; i++) {
		PlayerTextDrawShow(playerid, SelectCharTD[playerid][i]);
	}

    // --- SLOT 0 (Box: 0, Name: 5, Login: 10) ---
    if (!isnull(PlayerChar[playerid][0])) {
        format(str, sizeof(str), "%s", PlayerChar[playerid][0]);
        PlayerTextDrawSetString(playerid, SelectCharTD[playerid][5], str);
        
        format(str, sizeof(str), "%s", PlayerCharLastLogin[playerid][0]);
        PlayerTextDrawSetString(playerid, SelectCharTD[playerid][10], str);
        
        if (charselected == 0) {
            PlayerTextDrawColor(playerid, SelectCharTD[playerid][0], -602653441); // Merah
            PlayerTextDrawColor(playerid, SelectCharTD[playerid][10], -1448498689);
            PlayerTextDrawSetSelectable(playerid, SelectCharTD[playerid][0], 0);
        } else {
            PlayerTextDrawColor(playerid, SelectCharTD[playerid][0], 0x191919FF); // Abu-abu
            PlayerTextDrawColor(playerid, SelectCharTD[playerid][10], -1061109710);
            PlayerTextDrawSetSelectable(playerid, SelectCharTD[playerid][0], 1);
        }
    } else {
        PlayerTextDrawColor(playerid, SelectCharTD[playerid][0], 421075225); // Empty Slot Transparant
        PlayerTextDrawSetSelectable(playerid, SelectCharTD[playerid][0], 0);
    }

    // --- SLOT 1 (Box: 1, Name: 6, Login: 11, Empty: 15) ---
    if (!isnull(PlayerChar[playerid][1])) {
        format(str, sizeof(str), "%s", PlayerChar[playerid][1]);
        PlayerTextDrawSetString(playerid, SelectCharTD[playerid][6], str);
        
        format(str, sizeof(str), "%s", PlayerCharLastLogin[playerid][1]);
        PlayerTextDrawSetString(playerid, SelectCharTD[playerid][11], str);
        
        if (charselected == 1) {
            PlayerTextDrawColor(playerid, SelectCharTD[playerid][1], -602653441); // Merah
            PlayerTextDrawColor(playerid, SelectCharTD[playerid][11], -1448498689);
            PlayerTextDrawSetSelectable(playerid, SelectCharTD[playerid][1], 0);
        } else {
            PlayerTextDrawColor(playerid, SelectCharTD[playerid][1], 0x191919FF); // Abu-abu
            PlayerTextDrawColor(playerid, SelectCharTD[playerid][11], -1061109710);
            PlayerTextDrawSetSelectable(playerid, SelectCharTD[playerid][1], 1);
        }
    } else {
        PlayerTextDrawColor(playerid, SelectCharTD[playerid][1], 421075225); // Empty Slot Transparant
        PlayerTextDrawSetSelectable(playerid, SelectCharTD[playerid][1], 0);
    }

    // --- SLOT 2 (Box: 2, Name: 7, Login: 12, Empty: 16) ---
    if (!isnull(PlayerChar[playerid][2])) {
        format(str, sizeof(str), "%s", PlayerChar[playerid][2]);
        PlayerTextDrawSetString(playerid, SelectCharTD[playerid][7], str);
        
        format(str, sizeof(str), "%s", PlayerCharLastLogin[playerid][2]);
        PlayerTextDrawSetString(playerid, SelectCharTD[playerid][12], str);
        
        if (charselected == 2) {
            PlayerTextDrawColor(playerid, SelectCharTD[playerid][2], -602653441); // Merah
            PlayerTextDrawColor(playerid, SelectCharTD[playerid][12], -1448498689);
            PlayerTextDrawSetSelectable(playerid, SelectCharTD[playerid][2], 0);
        } else {
            PlayerTextDrawColor(playerid, SelectCharTD[playerid][2], 0x191919FF); // Abu-abu
            PlayerTextDrawColor(playerid, SelectCharTD[playerid][12], -1061109710);
            PlayerTextDrawSetSelectable(playerid, SelectCharTD[playerid][2], 1);
        }
    } else {
        PlayerTextDrawColor(playerid, SelectCharTD[playerid][2], 421075225); // Empty Slot Transparant
        PlayerTextDrawSetSelectable(playerid, SelectCharTD[playerid][2], 0);
    }

    // --- SLOT 3 (Box: 3, Name: 8, Login: 13, Empty: 17) ---
    if (!isnull(PlayerChar[playerid][3])) {
        format(str, sizeof(str), "%s", PlayerChar[playerid][3]);
        PlayerTextDrawSetString(playerid, SelectCharTD[playerid][8], str);
        
        format(str, sizeof(str), "%s", PlayerCharLastLogin[playerid][3]);
        PlayerTextDrawSetString(playerid, SelectCharTD[playerid][13], str);
        
        if (charselected == 3) {
            PlayerTextDrawColor(playerid, SelectCharTD[playerid][3], -602653441); // Merah
            PlayerTextDrawColor(playerid, SelectCharTD[playerid][13], -1448498689);
            PlayerTextDrawSetSelectable(playerid, SelectCharTD[playerid][3], 0);
        } else {
            PlayerTextDrawColor(playerid, SelectCharTD[playerid][3], 0x191919FF); // Abu-abu
            PlayerTextDrawColor(playerid, SelectCharTD[playerid][13], -1061109710);
            PlayerTextDrawSetSelectable(playerid, SelectCharTD[playerid][3], 1);
        }
    } else {
        PlayerTextDrawColor(playerid, SelectCharTD[playerid][3], 421075225); // Empty Slot Transparant
        PlayerTextDrawSetSelectable(playerid, SelectCharTD[playerid][3], 0);
    }

    // --- SLOT 4 (Box: 4, Name: 9, Login: 14, Empty: 18) ---
    if (!isnull(PlayerChar[playerid][4])) {
        format(str, sizeof(str), "%s", PlayerChar[playerid][4]);
        PlayerTextDrawSetString(playerid, SelectCharTD[playerid][9], str);
        
        format(str, sizeof(str), "%s", PlayerCharLastLogin[playerid][4]);
        PlayerTextDrawSetString(playerid, SelectCharTD[playerid][14], str);
        
        if (charselected == 4) {
            PlayerTextDrawColor(playerid, SelectCharTD[playerid][4], -602653441); // Merah
            PlayerTextDrawColor(playerid, SelectCharTD[playerid][14], -1448498689);
            PlayerTextDrawSetSelectable(playerid, SelectCharTD[playerid][4], 0);
        } else {
            PlayerTextDrawColor(playerid, SelectCharTD[playerid][4], 0x191919FF); // Abu-abu
            PlayerTextDrawColor(playerid, SelectCharTD[playerid][14], -1061109710);
            PlayerTextDrawSetSelectable(playerid, SelectCharTD[playerid][4], 1);
        }
    } else {
        PlayerTextDrawColor(playerid, SelectCharTD[playerid][4], 421075225); // Empty Slot Transparant
        PlayerTextDrawSetSelectable(playerid, SelectCharTD[playerid][4], 0);
    }


    // ========================================================
    // 2. EKSEKUSI TAMPILAN BERURUTAN (ID 0 Sampai 36)
    // ========================================================
    
    // BOX SLOT 0-4 (Selalu Show)
    PlayerTextDrawShow(playerid, SelectCharTD[playerid][0]);
    PlayerTextDrawShow(playerid, SelectCharTD[playerid][1]);
    PlayerTextDrawShow(playerid, SelectCharTD[playerid][2]);
    PlayerTextDrawShow(playerid, SelectCharTD[playerid][3]);
    PlayerTextDrawShow(playerid, SelectCharTD[playerid][4]);

    // NAMA SLOT 0-4 (ID 5-9)
    if (!isnull(PlayerChar[playerid][0])) PlayerTextDrawShow(playerid, SelectCharTD[playerid][5]); else PlayerTextDrawHide(playerid, SelectCharTD[playerid][5]);
    if (!isnull(PlayerChar[playerid][1])) PlayerTextDrawShow(playerid, SelectCharTD[playerid][6]); else PlayerTextDrawHide(playerid, SelectCharTD[playerid][6]);
    if (!isnull(PlayerChar[playerid][2])) PlayerTextDrawShow(playerid, SelectCharTD[playerid][7]); else PlayerTextDrawHide(playerid, SelectCharTD[playerid][7]);
    if (!isnull(PlayerChar[playerid][3])) PlayerTextDrawShow(playerid, SelectCharTD[playerid][8]); else PlayerTextDrawHide(playerid, SelectCharTD[playerid][8]);
    if (!isnull(PlayerChar[playerid][4])) PlayerTextDrawShow(playerid, SelectCharTD[playerid][9]); else PlayerTextDrawHide(playerid, SelectCharTD[playerid][9]);

    // LAST LOGIN SLOT 0-4 (ID 10-14)
    if (!isnull(PlayerChar[playerid][0])) PlayerTextDrawShow(playerid, SelectCharTD[playerid][10]); else PlayerTextDrawHide(playerid, SelectCharTD[playerid][10]);
    if (!isnull(PlayerChar[playerid][1])) PlayerTextDrawShow(playerid, SelectCharTD[playerid][11]); else PlayerTextDrawHide(playerid, SelectCharTD[playerid][11]);
    if (!isnull(PlayerChar[playerid][2])) PlayerTextDrawShow(playerid, SelectCharTD[playerid][12]); else PlayerTextDrawHide(playerid, SelectCharTD[playerid][12]);
    if (!isnull(PlayerChar[playerid][3])) PlayerTextDrawShow(playerid, SelectCharTD[playerid][13]); else PlayerTextDrawHide(playerid, SelectCharTD[playerid][13]);
    if (!isnull(PlayerChar[playerid][4])) PlayerTextDrawShow(playerid, SelectCharTD[playerid][14]); else PlayerTextDrawHide(playerid, SelectCharTD[playerid][14]);

    // EMPTY SLOT TEXT 1-4 (ID 15-18) 
    if (!isnull(PlayerChar[playerid][1])) PlayerTextDrawHide(playerid, SelectCharTD[playerid][15]); else PlayerTextDrawShow(playerid, SelectCharTD[playerid][15]);
    if (!isnull(PlayerChar[playerid][2])) PlayerTextDrawHide(playerid, SelectCharTD[playerid][16]); else PlayerTextDrawShow(playerid, SelectCharTD[playerid][16]);
    if (!isnull(PlayerChar[playerid][3])) PlayerTextDrawHide(playerid, SelectCharTD[playerid][17]); else PlayerTextDrawShow(playerid, SelectCharTD[playerid][17]);
    if (!isnull(PlayerChar[playerid][4])) PlayerTextDrawHide(playerid, SelectCharTD[playerid][18]); else PlayerTextDrawShow(playerid, SelectCharTD[playerid][18]);
	return 1;
}

//OnDynamicPlayerTextdrawClicked
SelectCharTDClick(playerid, PlayerText:playertextid)
{
    // ========================================================
    // SELECT CHARACTER SLOT (0 - 4) TANPA LOOP
    // ========================================================
    
    // --- SLOT 0 ---
    if (playertextid == SelectCharTD[playerid][0])
    {
        PlayerSelectCharTD[playerid] = 0;
        SetLobbySelectCharCamera(playerid, 0);
        ShowSelectCharTD(playerid, 0);
    }
    // --- SLOT 1 ---
    else if (playertextid == SelectCharTD[playerid][1])
    {
        PlayerSelectCharTD[playerid] = 1;
        SetLobbySelectCharCamera(playerid, 1);
        ShowSelectCharTD(playerid, 1);
    }
    // --- SLOT 2 ---
    else if (playertextid == SelectCharTD[playerid][2])
    {
        PlayerSelectCharTD[playerid] = 2;
        SetLobbySelectCharCamera(playerid, 2);
        ShowSelectCharTD(playerid, 2);
    }
    // --- SLOT 3 ---
    else if (playertextid == SelectCharTD[playerid][3])
    {
        PlayerSelectCharTD[playerid] = 3;
        SetLobbySelectCharCamera(playerid, 3);
        ShowSelectCharTD(playerid, 3);
    }
    // --- SLOT 4 ---
    else if (playertextid == SelectCharTD[playerid][4])
    {
        PlayerSelectCharTD[playerid] = 4;
        SetLobbySelectCharCamera(playerid, 4);
        ShowSelectCharTD(playerid, 4);
    }
    else if (playertextid == SelectCharTD[playerid][20]) 
    {
        // Pastikan slot yang dipilih benar-benar ada isinya
        if (!isnull(PlayerChar[playerid][PlayerSelectCharTD[playerid]])) 
        {
            // Sembunyikan UI Karakter
            for (new i = 0; i < 37; i++) {
                PlayerTextDrawHide(playerid, SelectCharTD[playerid][i]);
            }

            // Gerakkan kamera dengan mulus ke posisi Select Spawn (Index 5 di Array)
            SetLobbySelectCharCamera(playerid, 5);
            PlayerSelectSpawnTD[playerid] = 0; // Default paksa ke posisi atas (0)

            SetTimerEx("ChangeCameraLobby", 1500, false, "id", playerid, 1);
        }
    }
    
    return 1; 
}

forward ChangeCameraLobby(playerid, type);
public ChangeCameraLobby(playerid, type)
{
	if (type == 1) {
		ShowSelectSpawnTD(playerid, PlayerSelectSpawnTD[playerid]);
	} else {
		ShowSelectCharTD(playerid, PlayerSelectCharTD[playerid]);
	}
}

SetLobbySelectCharCamera(playerid, new_slot)
{
    // Ambil data posisi kamera player saat ini (sebelum dia pindah)
    new old_slot = LastCharCam[playerid]; 

    // Bergerak mulus menggunakan CAMERA_MOVE selama 1500ms (1.5 detik)
    InterpolateCameraPos(playerid, 
        LobbyCamData[old_slot][0], LobbyCamData[old_slot][1], LobbyCamData[old_slot][2], // DARI (Titik Lama)
        LobbyCamData[new_slot][0], LobbyCamData[new_slot][1], LobbyCamData[new_slot][2], // KE (Titik Baru)
        1500, CAMERA_MOVE); 

    InterpolateCameraLookAt(playerid, 
        LobbyCamData[old_slot][3], LobbyCamData[old_slot][4], LobbyCamData[old_slot][5], // DARI (Hadap Lama)
        LobbyCamData[new_slot][3], LobbyCamData[new_slot][4], LobbyCamData[new_slot][5], // KE (Hadap Baru)
        1500, CAMERA_MOVE);

    // Simpan posisi yang baru ke dalam ingatan, buat persiapan kalau dia ngeklik slot lain lagi
    LastCharCam[playerid] = new_slot;
}

enum e_LobbyActorData {
    Float:aX,
    Float:aY,
    Float:aZ,
    Float:aA,
    aAnimLib[16],
    aAnimName[32]
}

new const LobbyData[5][e_LobbyActorData] = {
    // X         Y          Z        Rotasi    AnimLib         AnimName
    {1852.73, -1591.31, 31.3469, 181.100, "PED",         "SEAT_idle"},       // Char 1 (Slot 0)
    {1850.71, -1592.06, 31.3469, 238.840, "CRIB",        "PED_Console_Loop"},// Char 2 (Slot 1)
    {1851.96, -1586.59, 31.3469,   0.311, "COP_AMBIENT", "Copbrowse_nod"},   // Char 3 (Slot 2)
    {1857.79, -1588.76, 31.3469,  83.968, "SMOKING",     "M_smklean_loop"},  // Char 4 (Slot 3)
    {1861.11, -1586.99, 31.3469, 358.932, "WEAPONS",     "SHP_Tray_Pose"}    // Char 5 (Slot 4)
};

ApplyLobbyActorAnimation(playerid, slot)
{
    if(slot < 0 || slot >= 5)
        return 0;

    if(isnull(PlayerChar[playerid][slot]))
        return 0;

    if(!IsValidDynamicActor(LobbyActorID[playerid][slot]))
        return 0;

    ApplyDynamicActorAnimation(LobbyActorID[playerid][slot],
        LobbyData[slot][aAnimLib], LobbyData[slot][aAnimName],
        4.1, true, false, false, false, 0);
    return 1;
}

forward RefreshLobbyActorAnimations(playerid);
public RefreshLobbyActorAnimations(playerid)
{
    if(!IsPlayerConnected(playerid) || !InCharSelection[playerid])
        return 0;

    for(new i = 0; i < MAX_CHARS; i++)
    {
        ApplyLobbyActorAnimation(playerid, i);
    }
    return 1;
}

CreateLobbyActor(playerid)
{
    for (new i = 0; i < MAX_CHARS; i++)
    {
        if (!isnull(PlayerChar[playerid][i]))
        {
            // [OPSIONAL] Hancurkan actor lama jika sebelumnya sudah ada, agar tidak numpuk/bug
            if (IsValidDynamicActor(LobbyActorID[playerid][i])) {
                DestroyDynamicActor(LobbyActorID[playerid][i]);
            }

            // FIX: Penempatan Virtual World dan Interior sudah di posisi yang benar!
            LobbyActorID[playerid][i] = CreateDynamicActor(
                PlayerCharSkin[playerid][i], 
                LobbyData[i][aX], LobbyData[i][aY], LobbyData[i][aZ], LobbyData[i][aA], 
                true,   // invulnerable
                100.0,  // health
                LobbyVirtualWorld[playerid], // Parameter ke-8: worldid
                2,                           // Parameter ke-9: interiorid
                playerid,                    // Parameter ke-10: Khusus untuk player ini saja
                300.0                        // Parameter ke-11: streamdistance
            );

            ApplyLobbyActorAnimation(playerid, i);
        }
    }

    SetTimerEx("RefreshLobbyActorAnimations", 600, false, "i", playerid);
}
