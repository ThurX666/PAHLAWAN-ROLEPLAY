new Text:LoginScreenTD[6];

CreateLoginScreenTD()
{
    LoginScreenTD[0] = TextDrawCreate(-1.000000, -1.000000, "ld_dual:white");
	TextDrawFont(LoginScreenTD[0], 4);
	TextDrawLetterSize(LoginScreenTD[0], 0.600000, 2.000000);
	TextDrawTextSize(LoginScreenTD[0], 642.500000, 450.000000);
	TextDrawSetOutline(LoginScreenTD[0], 1);
	TextDrawSetShadow(LoginScreenTD[0], 0);
	TextDrawAlignment(LoginScreenTD[0], 1);
	TextDrawColor(LoginScreenTD[0], 33686271);
	TextDrawBackgroundColor(LoginScreenTD[0], 255);
	TextDrawBoxColor(LoginScreenTD[0], 50);
	TextDrawUseBox(LoginScreenTD[0], 1);
	TextDrawSetProportional(LoginScreenTD[0], 1);
	TextDrawSetSelectable(LoginScreenTD[0], 0);

	LoginScreenTD[1] = TextDrawCreate(317.000000, 175.000000, "PAHLAWAN");
	TextDrawFont(LoginScreenTD[1], 1);
	TextDrawLetterSize(LoginScreenTD[1], 1.200000, 5.000000);
	TextDrawTextSize(LoginScreenTD[1], 400.000000, 17.000000);
	TextDrawSetOutline(LoginScreenTD[1], 1);
	TextDrawSetShadow(LoginScreenTD[1], 0);
	TextDrawAlignment(LoginScreenTD[1], 2);
	TextDrawColor(LoginScreenTD[1], -16776961);
	TextDrawBackgroundColor(LoginScreenTD[1], -16776961);
	TextDrawBoxColor(LoginScreenTD[1], 50);
	TextDrawUseBox(LoginScreenTD[1], 0);
	TextDrawSetProportional(LoginScreenTD[1], 1);
	TextDrawSetSelectable(LoginScreenTD[1], 0);

	LoginScreenTD[2] = TextDrawCreate(317.000000, 209.000000, "ROLEPLAY");
	TextDrawFont(LoginScreenTD[2], 1);
	TextDrawLetterSize(LoginScreenTD[2], 1.200000, 5.000000);
	TextDrawTextSize(LoginScreenTD[2], 400.000000, 17.000000);
	TextDrawSetOutline(LoginScreenTD[2], 1);
	TextDrawSetShadow(LoginScreenTD[2], 0);
	TextDrawAlignment(LoginScreenTD[2], 2);
	TextDrawColor(LoginScreenTD[2], -628031233);
	TextDrawBackgroundColor(LoginScreenTD[2], -628031233);
	TextDrawBoxColor(LoginScreenTD[2], 50);
	TextDrawUseBox(LoginScreenTD[2], 0);
	TextDrawSetProportional(LoginScreenTD[2], 1);
	TextDrawSetSelectable(LoginScreenTD[2], 0);

	LoginScreenTD[3] = TextDrawCreate(243.000000, 260.000000, "ld_dual:white");
	TextDrawFont(LoginScreenTD[3], 4);
	TextDrawLetterSize(LoginScreenTD[3], 0.600000, 2.000000);
	TextDrawTextSize(LoginScreenTD[3], 37.000000, 0.500000);
	TextDrawSetOutline(LoginScreenTD[3], 1);
	TextDrawSetShadow(LoginScreenTD[3], 0);
	TextDrawAlignment(LoginScreenTD[3], 1);
	TextDrawColor(LoginScreenTD[3], 1296911871);
	TextDrawBackgroundColor(LoginScreenTD[3], 255);
	TextDrawBoxColor(LoginScreenTD[3], 50);
	TextDrawUseBox(LoginScreenTD[3], 1);
	TextDrawSetProportional(LoginScreenTD[3], 1);
	TextDrawSetSelectable(LoginScreenTD[3], 0);

	LoginScreenTD[4] = TextDrawCreate(355.000000, 260.000000, "ld_dual:white");
	TextDrawFont(LoginScreenTD[4], 4);
	TextDrawLetterSize(LoginScreenTD[4], 0.600000, 2.000000);
	TextDrawTextSize(LoginScreenTD[4], 37.000000, 0.500000);
	TextDrawSetOutline(LoginScreenTD[4], 1);
	TextDrawSetShadow(LoginScreenTD[4], 0);
	TextDrawAlignment(LoginScreenTD[4], 1);
	TextDrawColor(LoginScreenTD[4], 1296911871);
	TextDrawBackgroundColor(LoginScreenTD[4], 255);
	TextDrawBoxColor(LoginScreenTD[4], 50);
	TextDrawUseBox(LoginScreenTD[4], 1);
	TextDrawSetProportional(LoginScreenTD[4], 1);
	TextDrawSetSelectable(LoginScreenTD[4], 0);

	LoginScreenTD[5] = TextDrawCreate(317.000000, 256.000000, "VERSION 1.8.3 - REBORN");
	TextDrawFont(LoginScreenTD[5], 1);
	TextDrawLetterSize(LoginScreenTD[5], 0.137494, 0.750000);
	TextDrawTextSize(LoginScreenTD[5], 400.000000, 147.000000);
	TextDrawSetOutline(LoginScreenTD[5], 0);
	TextDrawSetShadow(LoginScreenTD[5], 0);
	TextDrawAlignment(LoginScreenTD[5], 2);
	TextDrawColor(LoginScreenTD[5], 1296911871);
	TextDrawBackgroundColor(LoginScreenTD[5], 255);
	TextDrawBoxColor(LoginScreenTD[5], 50);
	TextDrawUseBox(LoginScreenTD[5], 0);
	TextDrawSetProportional(LoginScreenTD[5], 1);
	TextDrawSetSelectable(LoginScreenTD[5], 0);
}

ShowLoginScreenTD(playerid)
{
    for (new i = 0; i < 6; i++)
    {
        TextDrawShowForPlayer(playerid, LoginScreenTD[i]);
    }
}

HideLoginScreenTD(playerid)
{
    for (new i = 0; i < 6; i++)
    {
        TextDrawHideForPlayer(playerid, LoginScreenTD[i]);
    }
}