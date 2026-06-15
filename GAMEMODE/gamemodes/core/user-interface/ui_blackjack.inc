CreateBlackjackTD()
{
	BlackJackTD[0] = TextDrawCreate(269.000000, 317.000000, "ld_beat:up");
	TextDrawFont(BlackJackTD[0], 4);
	TextDrawLetterSize(BlackJackTD[0], 0.600000, 2.000000);
	TextDrawTextSize(BlackJackTD[0], 10.000000, 15.000000);
	TextDrawSetOutline(BlackJackTD[0], 1);
	TextDrawSetShadow(BlackJackTD[0], 0);
	TextDrawAlignment(BlackJackTD[0], 1);
	TextDrawColor(BlackJackTD[0], 16777215);
	TextDrawBackgroundColor(BlackJackTD[0], 255);
	TextDrawBoxColor(BlackJackTD[0], 50);
	TextDrawUseBox(BlackJackTD[0], 1);
	TextDrawSetProportional(BlackJackTD[0], 1);
	TextDrawSetSelectable(BlackJackTD[0], 0);

	BlackJackTD[1] = TextDrawCreate(300.000000, 218.000000, "ld_beat:up");
	TextDrawFont(BlackJackTD[1], 4);
	TextDrawLetterSize(BlackJackTD[1], 0.600000, 2.000000);
	TextDrawTextSize(BlackJackTD[1], 10.000000, 15.000000);
	TextDrawSetOutline(BlackJackTD[1], 1);
	TextDrawSetShadow(BlackJackTD[1], 0);
	TextDrawAlignment(BlackJackTD[1], 1);
	TextDrawColor(BlackJackTD[1], 16777215);
	TextDrawBackgroundColor(BlackJackTD[1], 255);
	TextDrawBoxColor(BlackJackTD[1], 50);
	TextDrawUseBox(BlackJackTD[1], 1);
	TextDrawSetProportional(BlackJackTD[1], 1);
	TextDrawSetSelectable(BlackJackTD[1], 0);

	BlackJackTD[2] = TextDrawCreate(324.000000, 317.000000, "ld_beat:up");
	TextDrawFont(BlackJackTD[2], 4);
	TextDrawLetterSize(BlackJackTD[2], 0.600000, 2.000000);
	TextDrawTextSize(BlackJackTD[2], 10.000000, 15.000000);
	TextDrawSetOutline(BlackJackTD[2], 1);
	TextDrawSetShadow(BlackJackTD[2], 0);
	TextDrawAlignment(BlackJackTD[2], 1);
	TextDrawColor(BlackJackTD[2], 16777215);
	TextDrawBackgroundColor(BlackJackTD[2], 255);
	TextDrawBoxColor(BlackJackTD[2], 50);
	TextDrawUseBox(BlackJackTD[2], 1);
	TextDrawSetProportional(BlackJackTD[2], 1);
	TextDrawSetSelectable(BlackJackTD[2], 0);

	BlackJackTD[3] = TextDrawCreate(111.000000, 219.000000, "HIT");
	TextDrawFont(BlackJackTD[3], 1);
	TextDrawLetterSize(BlackJackTD[3], 0.258332, 1.750000);
	TextDrawTextSize(BlackJackTD[3], 151.500000, 15.000000);
	TextDrawSetOutline(BlackJackTD[3], 1);
	TextDrawSetShadow(BlackJackTD[3], 0);
	TextDrawAlignment(BlackJackTD[3], 1);
	TextDrawColor(BlackJackTD[3], -1);
	TextDrawBackgroundColor(BlackJackTD[3], 255);
	TextDrawBoxColor(BlackJackTD[3], 200);
	TextDrawUseBox(BlackJackTD[3], 1);
	TextDrawSetProportional(BlackJackTD[3], 1);
	TextDrawSetSelectable(BlackJackTD[3], 1);

	BlackJackTD[4] = TextDrawCreate(111.000000, 242.500000, "STAND");
	TextDrawFont(BlackJackTD[4], 1);
	TextDrawLetterSize(BlackJackTD[4], 0.258332, 1.750000);
	TextDrawTextSize(BlackJackTD[4], 151.500000, 15.000000);
	TextDrawSetOutline(BlackJackTD[4], 1);
	TextDrawSetShadow(BlackJackTD[4], 0);
	TextDrawAlignment(BlackJackTD[4], 1);
	TextDrawColor(BlackJackTD[4], -1);
	TextDrawBackgroundColor(BlackJackTD[4], 255);
	TextDrawBoxColor(BlackJackTD[4], 200);
	TextDrawUseBox(BlackJackTD[4], 1);
	TextDrawSetProportional(BlackJackTD[4], 1);
	TextDrawSetSelectable(BlackJackTD[4], 1);

	BlackJackTD[5] = TextDrawCreate(111.000000, 266.000000, "DOUBLE");
	TextDrawFont(BlackJackTD[5], 1);
	TextDrawLetterSize(BlackJackTD[5], 0.258332, 1.750000);
	TextDrawTextSize(BlackJackTD[5], 151.500000, 15.000000);
	TextDrawSetOutline(BlackJackTD[5], 1);
	TextDrawSetShadow(BlackJackTD[5], 0);
	TextDrawAlignment(BlackJackTD[5], 1);
	TextDrawColor(BlackJackTD[5], -1);
	TextDrawBackgroundColor(BlackJackTD[5], 255);
	TextDrawBoxColor(BlackJackTD[5], 200);
	TextDrawUseBox(BlackJackTD[5], 1);
	TextDrawSetProportional(BlackJackTD[5], 1);
	TextDrawSetSelectable(BlackJackTD[5], 1);

	BlackJackTD[6] = TextDrawCreate(111.000000, 290.000000, "INSURANCE");
	TextDrawFont(BlackJackTD[6], 1);
	TextDrawLetterSize(BlackJackTD[6], 0.258332, 1.750000);
	TextDrawTextSize(BlackJackTD[6], 151.500000, 15.000000);
	TextDrawSetOutline(BlackJackTD[6], 1);
	TextDrawSetShadow(BlackJackTD[6], 0);
	TextDrawAlignment(BlackJackTD[6], 1);
	TextDrawColor(BlackJackTD[6], -1);
	TextDrawBackgroundColor(BlackJackTD[6], 255);
	TextDrawBoxColor(BlackJackTD[6], 200);
	TextDrawUseBox(BlackJackTD[6], 1);
	TextDrawSetProportional(BlackJackTD[6], 1);
	TextDrawSetSelectable(BlackJackTD[6], 1);

	BlackJackTD[7] = TextDrawCreate(111.000000, 314.000000, "SPLIT");
	TextDrawFont(BlackJackTD[7], 1);
	TextDrawLetterSize(BlackJackTD[7], 0.258332, 1.750000);
	TextDrawTextSize(BlackJackTD[7], 151.500000, 15.000000);
	TextDrawSetOutline(BlackJackTD[7], 1);
	TextDrawSetShadow(BlackJackTD[7], 0);
	TextDrawAlignment(BlackJackTD[7], 1);
	TextDrawColor(BlackJackTD[7], -1);
	TextDrawBackgroundColor(BlackJackTD[7], 255);
	TextDrawBoxColor(BlackJackTD[7], 200);
	TextDrawUseBox(BlackJackTD[7], 1);
	TextDrawSetProportional(BlackJackTD[7], 1);
	TextDrawSetSelectable(BlackJackTD[7], 1);

	BlackJackTD[8] = TextDrawCreate(509.000000, 157.000000, "_");
	TextDrawFont(BlackJackTD[8], 1);
	TextDrawLetterSize(BlackJackTD[8], 0.600000, 7.400001);
	TextDrawTextSize(BlackJackTD[8], 298.500000, 70.500000);
	TextDrawSetOutline(BlackJackTD[8], 1);
	TextDrawSetShadow(BlackJackTD[8], 0);
	TextDrawAlignment(BlackJackTD[8], 2);
	TextDrawColor(BlackJackTD[8], -1);
	TextDrawBackgroundColor(BlackJackTD[8], 255);
	TextDrawBoxColor(BlackJackTD[8], 9109759);
	TextDrawUseBox(BlackJackTD[8], 1);
	TextDrawSetProportional(BlackJackTD[8], 1);
	TextDrawSetSelectable(BlackJackTD[8], 0);

	BlackJackTD[9] = TextDrawCreate(508.000000, 158.000000, "Blackjack");
	TextDrawFont(BlackJackTD[9], 0);
	TextDrawLetterSize(BlackJackTD[9], 0.591666, 1.750000);
	TextDrawTextSize(BlackJackTD[9], 400.000000, 47.000000);
	TextDrawSetOutline(BlackJackTD[9], 0);
	TextDrawSetShadow(BlackJackTD[9], 0);
	TextDrawAlignment(BlackJackTD[9], 2);
	TextDrawColor(BlackJackTD[9], 255);
	TextDrawBackgroundColor(BlackJackTD[9], 255);
	TextDrawBoxColor(BlackJackTD[9], 50);
	TextDrawUseBox(BlackJackTD[9], 0);
	TextDrawSetProportional(BlackJackTD[9], 1);
	TextDrawSetSelectable(BlackJackTD[9], 0);
}

ShowPlayerBlackJackTD(playerid)
{
	for(new x = 3; x < 6; x++)
	{
		TextDrawShowForPlayer(playerid, BlackJackTD[x]);
		SelectTextDraw(playerid, 0xff91a4cc);
	}
	return 1;
}

HidePlayerBlackJackTD(playerid)
{
	for(new x = 3; x < 8; x++)
	{
		TextDrawHideForPlayer(playerid, BlackJackTD[x]);
		CancelSelectTextDraw(playerid);
	}
	return 1;
}