new Text: VerifyCodeGTD[11];
new PlayerText: VerifyCodePTD[MAX_PLAYERS][12];

CreateVerifyCodeTD()
{
    VerifyCodeGTD[0] = TextDrawCreate(230.000, 149.000, "ld_dual:white");
    TextDrawLetterSize(VerifyCodeGTD[0], 0.600, 2.000);
    TextDrawTextSize(VerifyCodeGTD[0], 180.000, 149.500);
    TextDrawAlignment(VerifyCodeGTD[0], 1);
    TextDrawColor(VerifyCodeGTD[0], 252645350);
    TextDrawUseBox(VerifyCodeGTD[0], 1);
    TextDrawBoxColor(VerifyCodeGTD[0], 50);
    TextDrawSetShadow(VerifyCodeGTD[0], 0);
    TextDrawSetOutline(VerifyCodeGTD[0], 1);
    TextDrawBackgroundColor(VerifyCodeGTD[0], 255);
    TextDrawFont(VerifyCodeGTD[0], 4);
    TextDrawSetProportional(VerifyCodeGTD[0], 1);

    VerifyCodeGTD[1] = TextDrawCreate(230.000, 298.000, "ld_dual:white");
    TextDrawLetterSize(VerifyCodeGTD[1], 0.600, 2.000);
    TextDrawTextSize(VerifyCodeGTD[1], 180.000, 5.500);
    TextDrawAlignment(VerifyCodeGTD[1], 1);
    TextDrawColor(VerifyCodeGTD[1], 168430335);
    TextDrawUseBox(VerifyCodeGTD[1], 1);
    TextDrawBoxColor(VerifyCodeGTD[1], 50);
    TextDrawSetShadow(VerifyCodeGTD[1], 0);
    TextDrawSetOutline(VerifyCodeGTD[1], 1);
    TextDrawBackgroundColor(VerifyCodeGTD[1], 255);
    TextDrawFont(VerifyCodeGTD[1], 4);
    TextDrawSetProportional(VerifyCodeGTD[1], 1);

    VerifyCodeGTD[2] = TextDrawCreate(319.000, 298.000, "THURX PROJECT");
    TextDrawLetterSize(VerifyCodeGTD[2], 0.104, 0.500);
    TextDrawTextSize(VerifyCodeGTD[2], 370.000, 192.000);
    TextDrawAlignment(VerifyCodeGTD[2], 2);
    TextDrawColor(VerifyCodeGTD[2], 926365695);
    TextDrawSetShadow(VerifyCodeGTD[2], 0);
    TextDrawSetOutline(VerifyCodeGTD[2], 0);
    TextDrawBackgroundColor(VerifyCodeGTD[2], -1);
    TextDrawFont(VerifyCodeGTD[2], 1);
    TextDrawSetProportional(VerifyCodeGTD[2], 1);

    VerifyCodeGTD[3] = TextDrawCreate(299.500, 127.500, "ld_pool:ball");
    TextDrawLetterSize(VerifyCodeGTD[3], 0.600, 2.000);
    TextDrawTextSize(VerifyCodeGTD[3], 37.500, 44.500);
    TextDrawAlignment(VerifyCodeGTD[3], 1);
    TextDrawColor(VerifyCodeGTD[3], 168430335);
    TextDrawUseBox(VerifyCodeGTD[3], 1);
    TextDrawBoxColor(VerifyCodeGTD[3], 50);
    TextDrawSetShadow(VerifyCodeGTD[3], 0);
    TextDrawSetOutline(VerifyCodeGTD[3], 1);
    TextDrawBackgroundColor(VerifyCodeGTD[3], -1);
    TextDrawFont(VerifyCodeGTD[3], 4);
    TextDrawSetProportional(VerifyCodeGTD[3], 1);

    VerifyCodeGTD[4] = TextDrawCreate(314.000, 136.000, "ld_pool:ball");
    TextDrawLetterSize(VerifyCodeGTD[4], 0.600, 2.000);
    TextDrawTextSize(VerifyCodeGTD[4], 8.500, 10.500);
    TextDrawAlignment(VerifyCodeGTD[4], 1);
    TextDrawColor(VerifyCodeGTD[4], 926365695);
    TextDrawUseBox(VerifyCodeGTD[4], 1);
    TextDrawBoxColor(VerifyCodeGTD[4], 50);
    TextDrawSetShadow(VerifyCodeGTD[4], 0);
    TextDrawSetOutline(VerifyCodeGTD[4], 1);
    TextDrawBackgroundColor(VerifyCodeGTD[4], 255);
    TextDrawFont(VerifyCodeGTD[4], 4);
    TextDrawSetProportional(VerifyCodeGTD[4], 1);

    VerifyCodeGTD[5] = TextDrawCreate(311.000, 147.000, "ld_pool:ball");
    TextDrawLetterSize(VerifyCodeGTD[5], 0.600, 2.000);
    TextDrawTextSize(VerifyCodeGTD[5], 14.500, 17.000);
    TextDrawAlignment(VerifyCodeGTD[5], 1);
    TextDrawColor(VerifyCodeGTD[5], 926365695);
    TextDrawUseBox(VerifyCodeGTD[5], 1);
    TextDrawBoxColor(VerifyCodeGTD[5], 50);
    TextDrawSetShadow(VerifyCodeGTD[5], 0);
    TextDrawSetOutline(VerifyCodeGTD[5], 1);
    TextDrawBackgroundColor(VerifyCodeGTD[5], 255);
    TextDrawFont(VerifyCodeGTD[5], 4);
    TextDrawSetProportional(VerifyCodeGTD[5], 1);

    VerifyCodeGTD[6] = TextDrawCreate(310.000, 158.000, "ld_dual:white");
    TextDrawLetterSize(VerifyCodeGTD[6], 0.600, 2.000);
    TextDrawTextSize(VerifyCodeGTD[6], 16.500, 7.500);
    TextDrawAlignment(VerifyCodeGTD[6], 1);
    TextDrawColor(VerifyCodeGTD[6], 134744319);
    TextDrawUseBox(VerifyCodeGTD[6], 1);
    TextDrawBoxColor(VerifyCodeGTD[6], 50);
    TextDrawSetShadow(VerifyCodeGTD[6], 0);
    TextDrawSetOutline(VerifyCodeGTD[6], 1);
    TextDrawBackgroundColor(VerifyCodeGTD[6], 255);
    TextDrawFont(VerifyCodeGTD[6], 4);
    TextDrawSetProportional(VerifyCodeGTD[6], 1);

    VerifyCodeGTD[7] = TextDrawCreate(319.000, 178.000, "VERIFY YOUR ACCOUNT");
    TextDrawLetterSize(VerifyCodeGTD[7], 0.216, 1.148);
    TextDrawTextSize(VerifyCodeGTD[7], 354.000, 193.000);
    TextDrawAlignment(VerifyCodeGTD[7], 2);
    TextDrawColor(VerifyCodeGTD[7], -1);
    TextDrawSetShadow(VerifyCodeGTD[7], 0);
    TextDrawSetOutline(VerifyCodeGTD[7], 1);
    TextDrawBackgroundColor(VerifyCodeGTD[7], 50);
    TextDrawFont(VerifyCodeGTD[7], 1);
    TextDrawSetProportional(VerifyCodeGTD[7], 1);

    VerifyCodeGTD[8] = TextDrawCreate(319.000, 192.000, "Enter the 6 digit code we sent to your discord.");
    TextDrawLetterSize(VerifyCodeGTD[8], 0.128, 0.750);
    TextDrawTextSize(VerifyCodeGTD[8], 370.000, 192.000);
    TextDrawAlignment(VerifyCodeGTD[8], 2);
    TextDrawColor(VerifyCodeGTD[8], 1482184959);
    TextDrawSetShadow(VerifyCodeGTD[8], 0);
    TextDrawSetOutline(VerifyCodeGTD[8], 0);
    TextDrawBackgroundColor(VerifyCodeGTD[8], -1);
    TextDrawFont(VerifyCodeGTD[8], 1);
    TextDrawSetProportional(VerifyCodeGTD[8], 1);

    VerifyCodeGTD[9] = TextDrawCreate(253.000, 250.000, "ld_dual:white");
    TextDrawLetterSize(VerifyCodeGTD[9], 0.600, 2.000);
    TextDrawTextSize(VerifyCodeGTD[9], 134.000, 20.000);
    TextDrawAlignment(VerifyCodeGTD[9], 1);
    TextDrawColor(VerifyCodeGTD[9], -16776961);
    TextDrawUseBox(VerifyCodeGTD[9], 1);
    TextDrawBoxColor(VerifyCodeGTD[9], 50);
    TextDrawSetShadow(VerifyCodeGTD[9], 0);
    TextDrawSetOutline(VerifyCodeGTD[9], 1);
    TextDrawBackgroundColor(VerifyCodeGTD[9], 255);
    TextDrawFont(VerifyCodeGTD[9], 4);
    TextDrawSetProportional(VerifyCodeGTD[9], 1);
    TextDrawSetSelectable(VerifyCodeGTD[9], 1);

    VerifyCodeGTD[10] = TextDrawCreate(319.000, 256.000, "Enter");
    TextDrawLetterSize(VerifyCodeGTD[10], 0.148, 0.750);
    TextDrawTextSize(VerifyCodeGTD[10], 373.000, 192.000);
    TextDrawAlignment(VerifyCodeGTD[10], 2);
    TextDrawColor(VerifyCodeGTD[10], -1);
    TextDrawSetShadow(VerifyCodeGTD[10], 0);
    TextDrawSetOutline(VerifyCodeGTD[10], 0);
    TextDrawBackgroundColor(VerifyCodeGTD[10], -1);
    TextDrawFont(VerifyCodeGTD[10], 1);
    TextDrawSetProportional(VerifyCodeGTD[10], 1);
}

CreatePlayerVerifyCodeTD(playerid)
{
    VerifyCodePTD[playerid][0] = CreatePlayerTextDraw(playerid, 253.000, 210.000, "ld_dual:white");
    PlayerTextDrawLetterSize(playerid, VerifyCodePTD[playerid][0], 0.600, 2.000);
    PlayerTextDrawTextSize(playerid, VerifyCodePTD[playerid][0], 20.000, 35.000);
    PlayerTextDrawAlignment(playerid, VerifyCodePTD[playerid][0], 1);
    PlayerTextDrawColor(playerid, VerifyCodePTD[playerid][0], 505290495);
    PlayerTextDrawUseBox(playerid, VerifyCodePTD[playerid][0], 1);
    PlayerTextDrawBoxColor(playerid, VerifyCodePTD[playerid][0], 50);
    PlayerTextDrawSetShadow(playerid, VerifyCodePTD[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, VerifyCodePTD[playerid][0], 1);
    PlayerTextDrawBackgroundColor(playerid, VerifyCodePTD[playerid][0], 255);
    PlayerTextDrawFont(playerid, VerifyCodePTD[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, VerifyCodePTD[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, VerifyCodePTD[playerid][0], 1);

    VerifyCodePTD[playerid][1] = CreatePlayerTextDraw(playerid, 276.000, 210.000, "ld_dual:white");
    PlayerTextDrawLetterSize(playerid, VerifyCodePTD[playerid][1], 0.600, 2.000);
    PlayerTextDrawTextSize(playerid, VerifyCodePTD[playerid][1], 20.000, 35.000);
    PlayerTextDrawAlignment(playerid, VerifyCodePTD[playerid][1], 1);
    PlayerTextDrawColor(playerid, VerifyCodePTD[playerid][1], 505290495);
    PlayerTextDrawUseBox(playerid, VerifyCodePTD[playerid][1], 1);
    PlayerTextDrawBoxColor(playerid, VerifyCodePTD[playerid][1], 50);
    PlayerTextDrawSetShadow(playerid, VerifyCodePTD[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, VerifyCodePTD[playerid][1], 1);
    PlayerTextDrawBackgroundColor(playerid, VerifyCodePTD[playerid][1], 255);
    PlayerTextDrawFont(playerid, VerifyCodePTD[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, VerifyCodePTD[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, VerifyCodePTD[playerid][1], 1);

    VerifyCodePTD[playerid][2] = CreatePlayerTextDraw(playerid, 298.500, 210.000, "ld_dual:white");
    PlayerTextDrawLetterSize(playerid, VerifyCodePTD[playerid][2], 0.600, 2.000);
    PlayerTextDrawTextSize(playerid, VerifyCodePTD[playerid][2], 20.000, 35.000);
    PlayerTextDrawAlignment(playerid, VerifyCodePTD[playerid][2], 1);
    PlayerTextDrawColor(playerid, VerifyCodePTD[playerid][2], 505290495);
    PlayerTextDrawUseBox(playerid, VerifyCodePTD[playerid][2], 1);
    PlayerTextDrawBoxColor(playerid, VerifyCodePTD[playerid][2], 50);
    PlayerTextDrawSetShadow(playerid, VerifyCodePTD[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, VerifyCodePTD[playerid][2], 1);
    PlayerTextDrawBackgroundColor(playerid, VerifyCodePTD[playerid][2], 255);
    PlayerTextDrawFont(playerid, VerifyCodePTD[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, VerifyCodePTD[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, VerifyCodePTD[playerid][2], 1);

    VerifyCodePTD[playerid][3] = CreatePlayerTextDraw(playerid, 321.000, 210.000, "ld_dual:white");
    PlayerTextDrawLetterSize(playerid, VerifyCodePTD[playerid][3], 0.600, 2.000);
    PlayerTextDrawTextSize(playerid, VerifyCodePTD[playerid][3], 20.000, 35.000);
    PlayerTextDrawAlignment(playerid, VerifyCodePTD[playerid][3], 1);
    PlayerTextDrawColor(playerid, VerifyCodePTD[playerid][3], 505290495);
    PlayerTextDrawUseBox(playerid, VerifyCodePTD[playerid][3], 1);
    PlayerTextDrawBoxColor(playerid, VerifyCodePTD[playerid][3], 50);
    PlayerTextDrawSetShadow(playerid, VerifyCodePTD[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, VerifyCodePTD[playerid][3], 1);
    PlayerTextDrawBackgroundColor(playerid, VerifyCodePTD[playerid][3], 255);
    PlayerTextDrawFont(playerid, VerifyCodePTD[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, VerifyCodePTD[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, VerifyCodePTD[playerid][3], 1);

    VerifyCodePTD[playerid][4] = CreatePlayerTextDraw(playerid, 344.000, 210.000, "ld_dual:white");
    PlayerTextDrawLetterSize(playerid, VerifyCodePTD[playerid][4], 0.600, 2.000);
    PlayerTextDrawTextSize(playerid, VerifyCodePTD[playerid][4], 20.000, 35.000);
    PlayerTextDrawAlignment(playerid, VerifyCodePTD[playerid][4], 1);
    PlayerTextDrawColor(playerid, VerifyCodePTD[playerid][4], 505290495);
    PlayerTextDrawUseBox(playerid, VerifyCodePTD[playerid][4], 1);
    PlayerTextDrawBoxColor(playerid, VerifyCodePTD[playerid][4], 50);
    PlayerTextDrawSetShadow(playerid, VerifyCodePTD[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, VerifyCodePTD[playerid][4], 1);
    PlayerTextDrawBackgroundColor(playerid, VerifyCodePTD[playerid][4], 255);
    PlayerTextDrawFont(playerid, VerifyCodePTD[playerid][4], 4);
    PlayerTextDrawSetProportional(playerid, VerifyCodePTD[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, VerifyCodePTD[playerid][4], 1);

    VerifyCodePTD[playerid][5] = CreatePlayerTextDraw(playerid, 367.000, 210.000, "ld_dual:white");
    PlayerTextDrawLetterSize(playerid, VerifyCodePTD[playerid][5], 0.600, 2.000);
    PlayerTextDrawTextSize(playerid, VerifyCodePTD[playerid][5], 20.000, 35.000);
    PlayerTextDrawAlignment(playerid, VerifyCodePTD[playerid][5], 1);
    PlayerTextDrawColor(playerid, VerifyCodePTD[playerid][5], 505290495);
    PlayerTextDrawUseBox(playerid, VerifyCodePTD[playerid][5], 1);
    PlayerTextDrawBoxColor(playerid, VerifyCodePTD[playerid][5], 50);
    PlayerTextDrawSetShadow(playerid, VerifyCodePTD[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, VerifyCodePTD[playerid][5], 1);
    PlayerTextDrawBackgroundColor(playerid, VerifyCodePTD[playerid][5], 255);
    PlayerTextDrawFont(playerid, VerifyCodePTD[playerid][5], 4);
    PlayerTextDrawSetProportional(playerid, VerifyCodePTD[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, VerifyCodePTD[playerid][5], 1);

    VerifyCodePTD[playerid][6] = CreatePlayerTextDraw(playerid, 259.000, 218.500, "0");
    PlayerTextDrawLetterSize(playerid, VerifyCodePTD[playerid][6], 0.377, 1.850);
    PlayerTextDrawTextSize(playerid, VerifyCodePTD[playerid][6], 370.000, 192.000);
    PlayerTextDrawAlignment(playerid, VerifyCodePTD[playerid][6], 1);
    PlayerTextDrawColor(playerid, VerifyCodePTD[playerid][6], -1);
    PlayerTextDrawSetShadow(playerid, VerifyCodePTD[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, VerifyCodePTD[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, VerifyCodePTD[playerid][6], -1);
    PlayerTextDrawFont(playerid, VerifyCodePTD[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, VerifyCodePTD[playerid][6], 1);

    VerifyCodePTD[playerid][7] = CreatePlayerTextDraw(playerid, 282.000, 218.500, "0");
    PlayerTextDrawLetterSize(playerid, VerifyCodePTD[playerid][7], 0.377, 1.850);
    PlayerTextDrawTextSize(playerid, VerifyCodePTD[playerid][7], 370.000, 192.000);
    PlayerTextDrawAlignment(playerid, VerifyCodePTD[playerid][7], 1);
    PlayerTextDrawColor(playerid, VerifyCodePTD[playerid][7], -1);
    PlayerTextDrawSetShadow(playerid, VerifyCodePTD[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, VerifyCodePTD[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, VerifyCodePTD[playerid][7], -1);
    PlayerTextDrawFont(playerid, VerifyCodePTD[playerid][7], 1);
    PlayerTextDrawSetProportional(playerid, VerifyCodePTD[playerid][7], 1);

    VerifyCodePTD[playerid][8] = CreatePlayerTextDraw(playerid, 304.500, 218.500, "0");
    PlayerTextDrawLetterSize(playerid, VerifyCodePTD[playerid][8], 0.377, 1.850);
    PlayerTextDrawTextSize(playerid, VerifyCodePTD[playerid][8], 370.000, 192.000);
    PlayerTextDrawAlignment(playerid, VerifyCodePTD[playerid][8], 1);
    PlayerTextDrawColor(playerid, VerifyCodePTD[playerid][8], -1);
    PlayerTextDrawSetShadow(playerid, VerifyCodePTD[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, VerifyCodePTD[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, VerifyCodePTD[playerid][8], -1);
    PlayerTextDrawFont(playerid, VerifyCodePTD[playerid][8], 1);
    PlayerTextDrawSetProportional(playerid, VerifyCodePTD[playerid][8], 1);

    VerifyCodePTD[playerid][9] = CreatePlayerTextDraw(playerid, 327.000, 218.500, "0");
    PlayerTextDrawLetterSize(playerid, VerifyCodePTD[playerid][9], 0.377, 1.850);
    PlayerTextDrawTextSize(playerid, VerifyCodePTD[playerid][9], 370.000, 192.000);
    PlayerTextDrawAlignment(playerid, VerifyCodePTD[playerid][9], 1);
    PlayerTextDrawColor(playerid, VerifyCodePTD[playerid][9], -1);
    PlayerTextDrawSetShadow(playerid, VerifyCodePTD[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, VerifyCodePTD[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, VerifyCodePTD[playerid][9], -1);
    PlayerTextDrawFont(playerid, VerifyCodePTD[playerid][9], 1);
    PlayerTextDrawSetProportional(playerid, VerifyCodePTD[playerid][9], 1);

    VerifyCodePTD[playerid][10] = CreatePlayerTextDraw(playerid, 350.000, 218.500, "0");
    PlayerTextDrawLetterSize(playerid, VerifyCodePTD[playerid][10], 0.377, 1.850);
    PlayerTextDrawTextSize(playerid, VerifyCodePTD[playerid][10], 370.000, 192.000);
    PlayerTextDrawAlignment(playerid, VerifyCodePTD[playerid][10], 1);
    PlayerTextDrawColor(playerid, VerifyCodePTD[playerid][10], -1);
    PlayerTextDrawSetShadow(playerid, VerifyCodePTD[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, VerifyCodePTD[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, VerifyCodePTD[playerid][10], -1);
    PlayerTextDrawFont(playerid, VerifyCodePTD[playerid][10], 1);
    PlayerTextDrawSetProportional(playerid, VerifyCodePTD[playerid][10], 1);

    VerifyCodePTD[playerid][11] = CreatePlayerTextDraw(playerid, 373.000, 218.500, "0");
    PlayerTextDrawLetterSize(playerid, VerifyCodePTD[playerid][11], 0.377, 1.850);
    PlayerTextDrawTextSize(playerid, VerifyCodePTD[playerid][11], 370.000, 192.000);
    PlayerTextDrawAlignment(playerid, VerifyCodePTD[playerid][11], 1);
    PlayerTextDrawColor(playerid, VerifyCodePTD[playerid][11], -1);
    PlayerTextDrawSetShadow(playerid, VerifyCodePTD[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, VerifyCodePTD[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, VerifyCodePTD[playerid][11], -1);
    PlayerTextDrawFont(playerid, VerifyCodePTD[playerid][11], 1);
    PlayerTextDrawSetProportional(playerid, VerifyCodePTD[playerid][11], 1);
}

ShowVerifyCodeTD(playerid)
{
    for (new i = 0; i < 12; i++)
    {
        if (VerifyCodePTD[playerid][i] != INVALID_PLAYER_TEXT_DRAW)
        {
            PlayerTextDrawShow(playerid, VerifyCodePTD[playerid][i]);
        }

        if (i < 11)
        {
            TextDrawShowForPlayer(playerid, VerifyCodeGTD[i]);
        }
    }
}

HideVerifyCodeTD(playerid)
{
    for (new i = 0; i < 12; i++)
    {
        if (VerifyCodePTD[playerid][i] != INVALID_PLAYER_TEXT_DRAW)
        {
            PlayerTextDrawDestroy(playerid, VerifyCodePTD[playerid][i]);
        }

        if (i < 11)
        {
            TextDrawHideForPlayer(playerid, VerifyCodeGTD[i]);
        }
    }
}