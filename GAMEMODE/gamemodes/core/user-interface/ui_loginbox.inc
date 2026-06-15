new Text:LoginBoxGTD[25];
new PlayerText:LoginBoxPTD[MAX_PLAYERS][7];

CreateLoginBoxTD()
{
	LoginBoxGTD[0] = TextDrawCreate(230.000, 64.000, "ld_dual:white");
	TextDrawLetterSize(LoginBoxGTD[0], 0.600, 2.000);
	TextDrawTextSize(LoginBoxGTD[0], 180.000, 319.500);
	TextDrawAlignment(LoginBoxGTD[0], 1);
	TextDrawColor(LoginBoxGTD[0], 252645350);
	TextDrawUseBox(LoginBoxGTD[0], 1);
	TextDrawBoxColor(LoginBoxGTD[0], 50);
	TextDrawSetShadow(LoginBoxGTD[0], 0);
	TextDrawSetOutline(LoginBoxGTD[0], 1);
	TextDrawBackgroundColor(LoginBoxGTD[0], 255);
	TextDrawFont(LoginBoxGTD[0], 4);
	TextDrawSetProportional(LoginBoxGTD[0], 1);

	LoginBoxGTD[1] = TextDrawCreate(230.000, 378.000, "ld_dual:white");
	TextDrawLetterSize(LoginBoxGTD[1], 0.600, 2.000);
	TextDrawTextSize(LoginBoxGTD[1], 180.000, 5.500);
	TextDrawAlignment(LoginBoxGTD[1], 1);
	TextDrawColor(LoginBoxGTD[1], 168430335);
	TextDrawUseBox(LoginBoxGTD[1], 1);
	TextDrawBoxColor(LoginBoxGTD[1], 50);
	TextDrawSetShadow(LoginBoxGTD[1], 0);
	TextDrawSetOutline(LoginBoxGTD[1], 1);
	TextDrawBackgroundColor(LoginBoxGTD[1], 255);
	TextDrawFont(LoginBoxGTD[1], 4);
	TextDrawSetProportional(LoginBoxGTD[1], 1);

	LoginBoxGTD[2] = TextDrawCreate(319.000, 378.000, "THURX PROJECT");
	TextDrawLetterSize(LoginBoxGTD[2], 0.104, 0.500);
	TextDrawTextSize(LoginBoxGTD[2], 370.000, 192.000);
	TextDrawAlignment(LoginBoxGTD[2], 2);
	TextDrawColor(LoginBoxGTD[2], 926365695);
	TextDrawSetShadow(LoginBoxGTD[2], 0);
	TextDrawSetOutline(LoginBoxGTD[2], 0);
	TextDrawBackgroundColor(LoginBoxGTD[2], -1);
	TextDrawFont(LoginBoxGTD[2], 1);
	TextDrawSetProportional(LoginBoxGTD[2], 1);

	LoginBoxGTD[3] = TextDrawCreate(253.000, 194.000, "ld_dual:white");
	TextDrawLetterSize(LoginBoxGTD[3], 0.600, 2.000);
	TextDrawTextSize(LoginBoxGTD[3], 134.000, 20.000);
	TextDrawAlignment(LoginBoxGTD[3], 1);
	TextDrawColor(LoginBoxGTD[3], 84215295);
	TextDrawUseBox(LoginBoxGTD[3], 1);
	TextDrawBoxColor(LoginBoxGTD[3], 50);
	TextDrawSetShadow(LoginBoxGTD[3], 0);
	TextDrawSetOutline(LoginBoxGTD[3], 1);
	TextDrawBackgroundColor(LoginBoxGTD[3], 255);
	TextDrawFont(LoginBoxGTD[3], 4);
	TextDrawSetProportional(LoginBoxGTD[3], 1);

	LoginBoxGTD[4] = TextDrawCreate(253.000, 225.000, "ld_dual:white");
	TextDrawLetterSize(LoginBoxGTD[4], 0.600, 2.000);
	TextDrawTextSize(LoginBoxGTD[4], 134.000, 20.000);
	TextDrawAlignment(LoginBoxGTD[4], 1);
	TextDrawColor(LoginBoxGTD[4], 0);
	TextDrawUseBox(LoginBoxGTD[4], 1);
	TextDrawBoxColor(LoginBoxGTD[4], 50);
	TextDrawSetShadow(LoginBoxGTD[4], 0);
	TextDrawSetOutline(LoginBoxGTD[4], 1);
	TextDrawBackgroundColor(LoginBoxGTD[4], 255);
	TextDrawFont(LoginBoxGTD[4], 4);
	TextDrawSetProportional(LoginBoxGTD[4], 1);
	TextDrawSetSelectable(LoginBoxGTD[4], 1);

	LoginBoxGTD[5] = TextDrawCreate(253.000, 225.000, "ld_dual:white");
	TextDrawLetterSize(LoginBoxGTD[5], 0.600, 2.000);
	TextDrawTextSize(LoginBoxGTD[5], 134.000, 20.000);
	TextDrawAlignment(LoginBoxGTD[5], 1);
	TextDrawColor(LoginBoxGTD[5], 200);
	TextDrawUseBox(LoginBoxGTD[5], 1);
	TextDrawBoxColor(LoginBoxGTD[5], 50);
	TextDrawSetShadow(LoginBoxGTD[5], 0);
	TextDrawSetOutline(LoginBoxGTD[5], 1);
	TextDrawBackgroundColor(LoginBoxGTD[5], 255);
	TextDrawFont(LoginBoxGTD[5], 4);
	TextDrawSetProportional(LoginBoxGTD[5], 1);

	LoginBoxGTD[6] = TextDrawCreate(253.000, 256.000, "ld_dual:white");
	TextDrawLetterSize(LoginBoxGTD[6], 0.600, 2.000);
	TextDrawTextSize(LoginBoxGTD[6], 134.000, 21.000);
	TextDrawAlignment(LoginBoxGTD[6], 1);
	TextDrawColor(LoginBoxGTD[6], -16777216);
	TextDrawUseBox(LoginBoxGTD[6], 1);
	TextDrawBoxColor(LoginBoxGTD[6], 50);
	TextDrawSetShadow(LoginBoxGTD[6], 0);
	TextDrawSetOutline(LoginBoxGTD[6], 1);
	TextDrawBackgroundColor(LoginBoxGTD[6], 255);
	TextDrawFont(LoginBoxGTD[6], 4);
	TextDrawSetProportional(LoginBoxGTD[6], 1);
	TextDrawSetSelectable(LoginBoxGTD[6], 1);

	LoginBoxGTD[7] = TextDrawCreate(253.000, 256.000, "ld_dual:white");
	TextDrawLetterSize(LoginBoxGTD[7], 0.600, 2.000);
	TextDrawTextSize(LoginBoxGTD[7], 134.000, 21.000);
	TextDrawAlignment(LoginBoxGTD[7], 1);
	TextDrawColor(LoginBoxGTD[7], -16777016);
	TextDrawUseBox(LoginBoxGTD[7], 1);
	TextDrawBoxColor(LoginBoxGTD[7], 50);
	TextDrawSetShadow(LoginBoxGTD[7], 0);
	TextDrawSetOutline(LoginBoxGTD[7], 1);
	TextDrawBackgroundColor(LoginBoxGTD[7], 255);
	TextDrawFont(LoginBoxGTD[7], 4);
	TextDrawSetProportional(LoginBoxGTD[7], 1);

	LoginBoxGTD[8] = TextDrawCreate(319.000, 262.000, "Login");
	TextDrawLetterSize(LoginBoxGTD[8], 0.150, 0.800);
	TextDrawTextSize(LoginBoxGTD[8], 370.000, 192.000);
	TextDrawAlignment(LoginBoxGTD[8], 2);
	TextDrawColor(LoginBoxGTD[8], -1);
	TextDrawSetShadow(LoginBoxGTD[8], 0);
	TextDrawSetOutline(LoginBoxGTD[8], 0);
	TextDrawBackgroundColor(LoginBoxGTD[8], -1);
	TextDrawFont(LoginBoxGTD[8], 1);
	TextDrawSetProportional(LoginBoxGTD[8], 1);

	LoginBoxGTD[9] = TextDrawCreate(353.000, 279.000, "ld_dual:white");
	TextDrawLetterSize(LoginBoxGTD[9], 0.600, 2.000);
	TextDrawTextSize(LoginBoxGTD[9], 35.000, 8.500);
	TextDrawAlignment(LoginBoxGTD[9], 1);
	TextDrawColor(LoginBoxGTD[9], 252645120);
	TextDrawUseBox(LoginBoxGTD[9], 1);
	TextDrawBoxColor(LoginBoxGTD[9], 50);
	TextDrawSetShadow(LoginBoxGTD[9], 0);
	TextDrawSetOutline(LoginBoxGTD[9], 1);
	TextDrawBackgroundColor(LoginBoxGTD[9], 255);
	TextDrawFont(LoginBoxGTD[9], 4);
	TextDrawSetProportional(LoginBoxGTD[9], 1);
	TextDrawSetSelectable(LoginBoxGTD[9], 1);

	LoginBoxGTD[10] = TextDrawCreate(353.000, 279.000, "ld_dual:white");
	TextDrawLetterSize(LoginBoxGTD[10], 0.600, 2.000);
	TextDrawTextSize(LoginBoxGTD[10], 35.000, 8.500);
	TextDrawAlignment(LoginBoxGTD[10], 1);
	TextDrawColor(LoginBoxGTD[10], 252645120);
	TextDrawUseBox(LoginBoxGTD[10], 1);
	TextDrawBoxColor(LoginBoxGTD[10], 50);
	TextDrawSetShadow(LoginBoxGTD[10], 0);
	TextDrawSetOutline(LoginBoxGTD[10], 1);
	TextDrawBackgroundColor(LoginBoxGTD[10], 255);
	TextDrawFont(LoginBoxGTD[10], 4);
	TextDrawSetProportional(LoginBoxGTD[10], 1);

	LoginBoxGTD[11] = TextDrawCreate(371.000, 279.000, "Lupa Password?");
	TextDrawLetterSize(LoginBoxGTD[11], 0.128, 0.750);
	TextDrawTextSize(LoginBoxGTD[11], 370.000, 34.000);
	TextDrawAlignment(LoginBoxGTD[11], 2);
	TextDrawColor(LoginBoxGTD[11], 1482184959);
	TextDrawSetShadow(LoginBoxGTD[11], 0);
	TextDrawSetOutline(LoginBoxGTD[11], 0);
	TextDrawBackgroundColor(LoginBoxGTD[11], 255);
	TextDrawFont(LoginBoxGTD[11], 1);
	TextDrawSetProportional(LoginBoxGTD[11], 1);

	LoginBoxGTD[12] = TextDrawCreate(319.000, 149.000, "PAHLAWAN");
	TextDrawLetterSize(LoginBoxGTD[12], 0.398, 1.949);
	TextDrawTextSize(LoginBoxGTD[12], 370.000, 192.000);
	TextDrawAlignment(LoginBoxGTD[12], 2);
	TextDrawColor(LoginBoxGTD[12], -16776961);
	TextDrawSetShadow(LoginBoxGTD[12], 0);
	TextDrawSetOutline(LoginBoxGTD[12], 1);
	TextDrawBackgroundColor(LoginBoxGTD[12], 50);
	TextDrawFont(LoginBoxGTD[12], 1);
	TextDrawSetProportional(LoginBoxGTD[12], 1);

	LoginBoxGTD[13] = TextDrawCreate(319.000, 164.000, "ROLEPLAY");
	TextDrawLetterSize(LoginBoxGTD[13], 0.237, 1.199);
	TextDrawTextSize(LoginBoxGTD[13], 370.000, 192.000);
	TextDrawAlignment(LoginBoxGTD[13], 2);
	TextDrawColor(LoginBoxGTD[13], -628031233);
	TextDrawSetShadow(LoginBoxGTD[13], 0);
	TextDrawSetOutline(LoginBoxGTD[13], 1);
	TextDrawBackgroundColor(LoginBoxGTD[13], 50);
	TextDrawFont(LoginBoxGTD[13], 1);
	TextDrawSetProportional(LoginBoxGTD[13], 1);

	LoginBoxGTD[14] = TextDrawCreate(299.500, 90.500, "ld_pool:ball");
	TextDrawLetterSize(LoginBoxGTD[14], 0.600, 2.000);
	TextDrawTextSize(LoginBoxGTD[14], 37.500, 44.500);
	TextDrawAlignment(LoginBoxGTD[14], 1);
	TextDrawColor(LoginBoxGTD[14], 168430335);
	TextDrawUseBox(LoginBoxGTD[14], 1);
	TextDrawBoxColor(LoginBoxGTD[14], 50);
	TextDrawSetShadow(LoginBoxGTD[14], 0);
	TextDrawSetOutline(LoginBoxGTD[14], 1);
	TextDrawBackgroundColor(LoginBoxGTD[14], -1);
	TextDrawFont(LoginBoxGTD[14], 4);
	TextDrawSetProportional(LoginBoxGTD[14], 1);

	LoginBoxGTD[15] = TextDrawCreate(314.000, 101.000, "ld_pool:ball");
	TextDrawLetterSize(LoginBoxGTD[15], 0.600, 2.000);
	TextDrawTextSize(LoginBoxGTD[15], 8.500, 10.500);
	TextDrawAlignment(LoginBoxGTD[15], 1);
	TextDrawColor(LoginBoxGTD[15], 926365695);
	TextDrawUseBox(LoginBoxGTD[15], 1);
	TextDrawBoxColor(LoginBoxGTD[15], 50);
	TextDrawSetShadow(LoginBoxGTD[15], 0);
	TextDrawSetOutline(LoginBoxGTD[15], 1);
	TextDrawBackgroundColor(LoginBoxGTD[15], 255);
	TextDrawFont(LoginBoxGTD[15], 4);
	TextDrawSetProportional(LoginBoxGTD[15], 1);

	LoginBoxGTD[16] = TextDrawCreate(311.000, 112.000, "ld_pool:ball");
	TextDrawLetterSize(LoginBoxGTD[16], 0.600, 2.000);
	TextDrawTextSize(LoginBoxGTD[16], 14.500, 17.000);
	TextDrawAlignment(LoginBoxGTD[16], 1);
	TextDrawColor(LoginBoxGTD[16], 926365695);
	TextDrawUseBox(LoginBoxGTD[16], 1);
	TextDrawBoxColor(LoginBoxGTD[16], 50);
	TextDrawSetShadow(LoginBoxGTD[16], 0);
	TextDrawSetOutline(LoginBoxGTD[16], 1);
	TextDrawBackgroundColor(LoginBoxGTD[16], 255);
	TextDrawFont(LoginBoxGTD[16], 4);
	TextDrawSetProportional(LoginBoxGTD[16], 1);

	LoginBoxGTD[17] = TextDrawCreate(310.000, 122.000, "ld_dual:white");
	TextDrawLetterSize(LoginBoxGTD[17], 0.600, 2.000);
	TextDrawTextSize(LoginBoxGTD[17], 16.500, 7.500);
	TextDrawAlignment(LoginBoxGTD[17], 1);
	TextDrawColor(LoginBoxGTD[17], 134744319);
	TextDrawUseBox(LoginBoxGTD[17], 1);
	TextDrawBoxColor(LoginBoxGTD[17], 50);
	TextDrawSetShadow(LoginBoxGTD[17], 0);
	TextDrawSetOutline(LoginBoxGTD[17], 1);
	TextDrawBackgroundColor(LoginBoxGTD[17], 255);
	TextDrawFont(LoginBoxGTD[17], 4);
	TextDrawSetProportional(LoginBoxGTD[17], 1);

	LoginBoxGTD[18] = TextDrawCreate(319.000, 302.000, "Perangkat Anda");
	TextDrawLetterSize(LoginBoxGTD[18], 0.128, 0.750);
	TextDrawTextSize(LoginBoxGTD[18], 370.000, 192.000);
	TextDrawAlignment(LoginBoxGTD[18], 2);
	TextDrawColor(LoginBoxGTD[18], 1482184959);
	TextDrawSetShadow(LoginBoxGTD[18], 0);
	TextDrawSetOutline(LoginBoxGTD[18], 0);
	TextDrawBackgroundColor(LoginBoxGTD[18], -1);
	TextDrawFont(LoginBoxGTD[18], 1);
	TextDrawSetProportional(LoginBoxGTD[18], 1);

	LoginBoxGTD[19] = TextDrawCreate(260.000, 199.500, "ld_pool:ball");
	TextDrawLetterSize(LoginBoxGTD[19], 0.600, 2.000);
	TextDrawTextSize(LoginBoxGTD[19], 3.500, 4.500);
	TextDrawAlignment(LoginBoxGTD[19], 1);
	TextDrawColor(LoginBoxGTD[19], 926365695);
	TextDrawUseBox(LoginBoxGTD[19], 1);
	TextDrawBoxColor(LoginBoxGTD[19], 50);
	TextDrawSetShadow(LoginBoxGTD[19], 0);
	TextDrawSetOutline(LoginBoxGTD[19], 1);
	TextDrawBackgroundColor(LoginBoxGTD[19], 255);
	TextDrawFont(LoginBoxGTD[19], 4);
	TextDrawSetProportional(LoginBoxGTD[19], 1);

	LoginBoxGTD[20] = TextDrawCreate(258.799, 205.000, "ld_pool:ball");
	TextDrawLetterSize(LoginBoxGTD[20], 0.600, 2.000);
	TextDrawTextSize(LoginBoxGTD[20], 6.000, 6.500);
	TextDrawAlignment(LoginBoxGTD[20], 1);
	TextDrawColor(LoginBoxGTD[20], 926365695);
	TextDrawUseBox(LoginBoxGTD[20], 1);
	TextDrawBoxColor(LoginBoxGTD[20], 50);
	TextDrawSetShadow(LoginBoxGTD[20], 0);
	TextDrawSetOutline(LoginBoxGTD[20], 1);
	TextDrawBackgroundColor(LoginBoxGTD[20], 255);
	TextDrawFont(LoginBoxGTD[20], 4);
	TextDrawSetProportional(LoginBoxGTD[20], 1);

	LoginBoxGTD[21] = TextDrawCreate(258.000, 208.500, "ld_dual:white");
	TextDrawLetterSize(LoginBoxGTD[21], 0.600, 2.000);
	TextDrawTextSize(LoginBoxGTD[21], 7.500, 4.500);
	TextDrawAlignment(LoginBoxGTD[21], 1);
	TextDrawColor(LoginBoxGTD[21], 84215295);
	TextDrawUseBox(LoginBoxGTD[21], 1);
	TextDrawBoxColor(LoginBoxGTD[21], 50);
	TextDrawSetShadow(LoginBoxGTD[21], 0);
	TextDrawSetOutline(LoginBoxGTD[21], 1);
	TextDrawBackgroundColor(LoginBoxGTD[21], 255);
	TextDrawFont(LoginBoxGTD[21], 4);
	TextDrawSetProportional(LoginBoxGTD[21], 1);

	LoginBoxGTD[22] = TextDrawCreate(257.898, 229.500, "ld_pool:ball");
	TextDrawLetterSize(LoginBoxGTD[22], 0.600, 2.000);
	TextDrawTextSize(LoginBoxGTD[22], 5.197, 8.500);
	TextDrawAlignment(LoginBoxGTD[22], 1);
	TextDrawColor(LoginBoxGTD[22], 926365695);
	TextDrawUseBox(LoginBoxGTD[22], 1);
	TextDrawBoxColor(LoginBoxGTD[22], 50);
	TextDrawSetShadow(LoginBoxGTD[22], 0);
	TextDrawSetOutline(LoginBoxGTD[22], 1);
	TextDrawBackgroundColor(LoginBoxGTD[22], 255);
	TextDrawFont(LoginBoxGTD[22], 4);
	TextDrawSetProportional(LoginBoxGTD[22], 1);

	LoginBoxGTD[23] = TextDrawCreate(258.898, 230.500, "ld_pool:ball");
	TextDrawLetterSize(LoginBoxGTD[23], 0.600, 2.000);
	TextDrawTextSize(LoginBoxGTD[23], 3.197, 8.500);
	TextDrawAlignment(LoginBoxGTD[23], 1);
	TextDrawColor(LoginBoxGTD[23], 84215295);
	TextDrawUseBox(LoginBoxGTD[23], 1);
	TextDrawBoxColor(LoginBoxGTD[23], 50);
	TextDrawSetShadow(LoginBoxGTD[23], 0);
	TextDrawSetOutline(LoginBoxGTD[23], 1);
	TextDrawBackgroundColor(LoginBoxGTD[23], 255);
	TextDrawFont(LoginBoxGTD[23], 4);
	TextDrawSetProportional(LoginBoxGTD[23], 1);

	LoginBoxGTD[24] = TextDrawCreate(258.000, 234.500, "ld_dual:white");
	TextDrawLetterSize(LoginBoxGTD[24], 0.600, 2.000);
	TextDrawTextSize(LoginBoxGTD[24], 5.000, 5.500);
	TextDrawAlignment(LoginBoxGTD[24], 1);
	TextDrawColor(LoginBoxGTD[24], 1010580735);
	TextDrawUseBox(LoginBoxGTD[24], 1);
	TextDrawBoxColor(LoginBoxGTD[24], 50);
	TextDrawSetShadow(LoginBoxGTD[24], 0);
	TextDrawSetOutline(LoginBoxGTD[24], 1);
	TextDrawBackgroundColor(LoginBoxGTD[24], 255);
	TextDrawFont(LoginBoxGTD[24], 4);
	TextDrawSetProportional(LoginBoxGTD[24], 1);
}

CreatePlayerLoginBoxTD(playerid)
{
	LoginBoxPTD[playerid][0] = CreatePlayerTextDraw(playerid, 271.000, 200.500, "Arthur_Clinton");
	PlayerTextDrawLetterSize(playerid, LoginBoxPTD[playerid][0], 0.128, 0.750);
	PlayerTextDrawTextSize(playerid, LoginBoxPTD[playerid][0], 370.000, 192.000);
	PlayerTextDrawAlignment(playerid, LoginBoxPTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, LoginBoxPTD[playerid][0], 1482184959);
	PlayerTextDrawSetShadow(playerid, LoginBoxPTD[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, LoginBoxPTD[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, LoginBoxPTD[playerid][0], -1);
	PlayerTextDrawFont(playerid, LoginBoxPTD[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, LoginBoxPTD[playerid][0], 1);

	LoginBoxPTD[playerid][1] = CreatePlayerTextDraw(playerid, 271.000, 231.500, "Password");
	PlayerTextDrawLetterSize(playerid, LoginBoxPTD[playerid][1], 0.128, 0.750);
	PlayerTextDrawTextSize(playerid, LoginBoxPTD[playerid][1], 370.000, 192.000);
	PlayerTextDrawAlignment(playerid, LoginBoxPTD[playerid][1], 1);
	PlayerTextDrawColor(playerid, LoginBoxPTD[playerid][1], 1482184959);
	PlayerTextDrawSetShadow(playerid, LoginBoxPTD[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, LoginBoxPTD[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, LoginBoxPTD[playerid][1], -1);
	PlayerTextDrawFont(playerid, LoginBoxPTD[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, LoginBoxPTD[playerid][1], 1);

	LoginBoxPTD[playerid][2] = CreatePlayerTextDraw(playerid, 253.000, 313.000, "ld_dual:white");
	PlayerTextDrawLetterSize(playerid, LoginBoxPTD[playerid][2], 0.600, 2.000);
	PlayerTextDrawTextSize(playerid, LoginBoxPTD[playerid][2], 64.000, 18.000);
	PlayerTextDrawAlignment(playerid, LoginBoxPTD[playerid][2], 1);
	PlayerTextDrawColor(playerid, LoginBoxPTD[playerid][2], 2105376200);
	PlayerTextDrawUseBox(playerid, LoginBoxPTD[playerid][2], 1);
	PlayerTextDrawBoxColor(playerid, LoginBoxPTD[playerid][2], 50);
	PlayerTextDrawSetShadow(playerid, LoginBoxPTD[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, LoginBoxPTD[playerid][2], 1);
	PlayerTextDrawBackgroundColor(playerid, LoginBoxPTD[playerid][2], 255);
	PlayerTextDrawFont(playerid, LoginBoxPTD[playerid][2], 4);
	PlayerTextDrawSetProportional(playerid, LoginBoxPTD[playerid][2], 1);
	PlayerTextDrawSetSelectable(playerid, LoginBoxPTD[playerid][2], 1);

	LoginBoxPTD[playerid][3] = CreatePlayerTextDraw(playerid, 285.000, 318.000, "Android");
	PlayerTextDrawLetterSize(playerid, LoginBoxPTD[playerid][3], 0.150, 0.800);
	PlayerTextDrawTextSize(playerid, LoginBoxPTD[playerid][3], 370.000, 192.000);
	PlayerTextDrawAlignment(playerid, LoginBoxPTD[playerid][3], 2);
	PlayerTextDrawColor(playerid, LoginBoxPTD[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, LoginBoxPTD[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, LoginBoxPTD[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, LoginBoxPTD[playerid][3], -1);
	PlayerTextDrawFont(playerid, LoginBoxPTD[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, LoginBoxPTD[playerid][3], 1);

	LoginBoxPTD[playerid][4] = CreatePlayerTextDraw(playerid, 323.000, 313.000, "ld_dual:white");
	PlayerTextDrawLetterSize(playerid, LoginBoxPTD[playerid][4], 0.600, 2.000);
	PlayerTextDrawTextSize(playerid, LoginBoxPTD[playerid][4], 64.000, 18.000);
	PlayerTextDrawAlignment(playerid, LoginBoxPTD[playerid][4], 1);
	PlayerTextDrawColor(playerid, LoginBoxPTD[playerid][4], 421075400);
	PlayerTextDrawUseBox(playerid, LoginBoxPTD[playerid][4], 1);
	PlayerTextDrawBoxColor(playerid, LoginBoxPTD[playerid][4], 50);
	PlayerTextDrawSetShadow(playerid, LoginBoxPTD[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, LoginBoxPTD[playerid][4], 1);
	PlayerTextDrawBackgroundColor(playerid, LoginBoxPTD[playerid][4], 255);
	PlayerTextDrawFont(playerid, LoginBoxPTD[playerid][4], 4);
	PlayerTextDrawSetProportional(playerid, LoginBoxPTD[playerid][4], 1);
	PlayerTextDrawSetSelectable(playerid, LoginBoxPTD[playerid][4], 1);

	LoginBoxPTD[playerid][5] = CreatePlayerTextDraw(playerid, 355.000, 318.000, "Komputer");
	PlayerTextDrawLetterSize(playerid, LoginBoxPTD[playerid][5], 0.150, 0.800);
	PlayerTextDrawTextSize(playerid, LoginBoxPTD[playerid][5], 370.000, 192.000);
	PlayerTextDrawAlignment(playerid, LoginBoxPTD[playerid][5], 2);
	PlayerTextDrawColor(playerid, LoginBoxPTD[playerid][5], 1010580680);
	PlayerTextDrawSetShadow(playerid, LoginBoxPTD[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, LoginBoxPTD[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, LoginBoxPTD[playerid][5], -1);
	PlayerTextDrawFont(playerid, LoginBoxPTD[playerid][5], 1);
	PlayerTextDrawSetProportional(playerid, LoginBoxPTD[playerid][5], 1);

	LoginBoxPTD[playerid][6] = CreatePlayerTextDraw(playerid, 259.898, 235.500, "ld_pool:ball");
	PlayerTextDrawLetterSize(playerid, LoginBoxPTD[playerid][6], 0.600, 2.000);
	PlayerTextDrawTextSize(playerid, LoginBoxPTD[playerid][6], 1.199, 3.000);
	PlayerTextDrawAlignment(playerid, LoginBoxPTD[playerid][6], 1);
	PlayerTextDrawColor(playerid, LoginBoxPTD[playerid][6], 84215295);
	PlayerTextDrawUseBox(playerid, LoginBoxPTD[playerid][6], 1);
	PlayerTextDrawBoxColor(playerid, LoginBoxPTD[playerid][6], 50);
	PlayerTextDrawSetShadow(playerid, LoginBoxPTD[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, LoginBoxPTD[playerid][6], 1);
	PlayerTextDrawBackgroundColor(playerid, LoginBoxPTD[playerid][6], 255);
	PlayerTextDrawFont(playerid, LoginBoxPTD[playerid][6], 4);
	PlayerTextDrawSetProportional(playerid, LoginBoxPTD[playerid][6], 1);
}

ShowLoginBoxTD(playerid)
{
    for (new i = 0; i < 25; i++)
    {
        if (i < 7)
        {
            if (LoginBoxPTD[playerid][i] != INVALID_PLAYER_TEXT_DRAW)
            {
                PlayerTextDrawShow(playerid, LoginBoxPTD[playerid][i]);
            }
        }

        TextDrawShowForPlayer(playerid, LoginBoxGTD[i]);
    }
}

HideLoginBoxTD(playerid)
{
    for (new i = 0; i < 25; i++)
    {
        if (i < 7)
        {
            if (LoginBoxPTD[playerid][i] != INVALID_PLAYER_TEXT_DRAW)
            {
                PlayerTextDrawDestroy(playerid, LoginBoxPTD[playerid][i]);
            }
        }

        TextDrawHideForPlayer(playerid, LoginBoxGTD[i]);
    }
}