new Text:CarDealerTD[27],
    PlayerText:CarDealerPTD[MAX_PLAYERS][3];

CreateCardealerTD()
{    
    CarDealerTD[0] = TextDrawCreate(487.000, 327.000, "LD_BUM:blkdot");
    TextDrawTextSize(CarDealerTD[0], 34.000, 18.000);
    TextDrawAlignment(CarDealerTD[0], 1);
    TextDrawColor(CarDealerTD[0], 421075455);
    TextDrawSetShadow(CarDealerTD[0], 0);
    TextDrawSetOutline(CarDealerTD[0], 0);
    TextDrawBackgroundColor(CarDealerTD[0], 255);
    TextDrawFont(CarDealerTD[0], 4);
    TextDrawSetProportional(CarDealerTD[0], 1);
    TextDrawSetSelectable(CarDealerTD[0], 1);

    CarDealerTD[1] = TextDrawCreate(499.000, 334.000, "LD_BUM:blkdot");
    TextDrawTextSize(CarDealerTD[1], 12.000, 3.000);
    TextDrawAlignment(CarDealerTD[1], 1);
    TextDrawColor(CarDealerTD[1], -1);
    TextDrawSetShadow(CarDealerTD[1], 0);
    TextDrawSetOutline(CarDealerTD[1], 0);
    TextDrawBackgroundColor(CarDealerTD[1], 255);
    TextDrawFont(CarDealerTD[1], 4);
    TextDrawSetProportional(CarDealerTD[1], 1);

    CarDealerTD[2] = TextDrawCreate(497.000, 327.000, "<");
    TextDrawLetterSize(CarDealerTD[2], 0.250, 1.799);
    TextDrawAlignment(CarDealerTD[2], 1);
    TextDrawColor(CarDealerTD[2], -1);
    TextDrawSetShadow(CarDealerTD[2], 1);
    TextDrawSetOutline(CarDealerTD[2], 1);
    TextDrawBackgroundColor(CarDealerTD[2], 0);
    TextDrawFont(CarDealerTD[2], 1);
    TextDrawSetProportional(CarDealerTD[2], 1);

    CarDealerTD[3] = TextDrawCreate(497.000, 327.000, "<");
    TextDrawLetterSize(CarDealerTD[3], 0.250, 1.799);
    TextDrawAlignment(CarDealerTD[3], 1);
    TextDrawColor(CarDealerTD[3], -1);
    TextDrawSetShadow(CarDealerTD[3], 1);
    TextDrawSetOutline(CarDealerTD[3], 1);
    TextDrawBackgroundColor(CarDealerTD[3], 0);
    TextDrawFont(CarDealerTD[3], 1);
    TextDrawSetProportional(CarDealerTD[3], 1);

    CarDealerTD[4] = TextDrawCreate(500.000, 333.000, "LD_BUM:blkdot");
    TextDrawTextSize(CarDealerTD[4], 2.000, 5.000);
    TextDrawAlignment(CarDealerTD[4], 1);
    TextDrawColor(CarDealerTD[4], -1);
    TextDrawSetShadow(CarDealerTD[4], 0);
    TextDrawSetOutline(CarDealerTD[4], 0);
    TextDrawBackgroundColor(CarDealerTD[4], 255);
    TextDrawFont(CarDealerTD[4], 4);
    TextDrawSetProportional(CarDealerTD[4], 1);

    CarDealerTD[5] = TextDrawCreate(531.000, 327.000, "LD_BUM:blkdot");
    TextDrawTextSize(CarDealerTD[5], 34.000, 18.000);
    TextDrawAlignment(CarDealerTD[5], 1);
    TextDrawColor(CarDealerTD[5], 421075455);
    TextDrawSetShadow(CarDealerTD[5], 0);
    TextDrawSetOutline(CarDealerTD[5], 0);
    TextDrawBackgroundColor(CarDealerTD[5], 255);
    TextDrawFont(CarDealerTD[5], 4);
    TextDrawSetProportional(CarDealerTD[5], 1);
    TextDrawSetSelectable(CarDealerTD[5], 1);

    CarDealerTD[6] = TextDrawCreate(542.000, 334.000, "LD_BUM:blkdot");
    TextDrawTextSize(CarDealerTD[6], 13.000, 3.000);
    TextDrawAlignment(CarDealerTD[6], 1);
    TextDrawColor(CarDealerTD[6], -1);
    TextDrawSetShadow(CarDealerTD[6], 0);
    TextDrawSetOutline(CarDealerTD[6], 0);
    TextDrawBackgroundColor(CarDealerTD[6], 255);
    TextDrawFont(CarDealerTD[6], 4);
    TextDrawSetProportional(CarDealerTD[6], 1);

    CarDealerTD[7] = TextDrawCreate(557.000, 327.000, "<");
    TextDrawLetterSize(CarDealerTD[7], -0.250, 1.789);
    TextDrawAlignment(CarDealerTD[7], 1);
    TextDrawColor(CarDealerTD[7], -1);
    TextDrawSetShadow(CarDealerTD[7], 1);
    TextDrawSetOutline(CarDealerTD[7], 1);
    TextDrawBackgroundColor(CarDealerTD[7], 0);
    TextDrawFont(CarDealerTD[7], 1);
    TextDrawSetProportional(CarDealerTD[7], 1);

    CarDealerTD[8] = TextDrawCreate(557.000, 327.000, "<");
    TextDrawLetterSize(CarDealerTD[8], -0.250, 1.789);
    TextDrawAlignment(CarDealerTD[8], 1);
    TextDrawColor(CarDealerTD[8], -1);
    TextDrawSetShadow(CarDealerTD[8], 1);
    TextDrawSetOutline(CarDealerTD[8], 1);
    TextDrawBackgroundColor(CarDealerTD[8], 0);
    TextDrawFont(CarDealerTD[8], 1);
    TextDrawSetProportional(CarDealerTD[8], 1);

    CarDealerTD[9] = TextDrawCreate(552.000, 333.000, "LD_BUM:blkdot");
    TextDrawTextSize(CarDealerTD[9], 1.000, 5.000);
    TextDrawAlignment(CarDealerTD[9], 1);
    TextDrawColor(CarDealerTD[9], -1);
    TextDrawSetShadow(CarDealerTD[9], 0);
    TextDrawSetOutline(CarDealerTD[9], 0);
    TextDrawBackgroundColor(CarDealerTD[9], 255);
    TextDrawFont(CarDealerTD[9], 4);
    TextDrawSetProportional(CarDealerTD[9], 1);

    CarDealerTD[10] = TextDrawCreate(487.000, 344.000, "LD_BUM:blkdot");
    TextDrawTextSize(CarDealerTD[10], 34.000, 1.000);
    TextDrawAlignment(CarDealerTD[10], 1);
    TextDrawColor(CarDealerTD[10], 0xff91a4ff);
    TextDrawSetShadow(CarDealerTD[10], 0);
    TextDrawSetOutline(CarDealerTD[10], 0);
    TextDrawBackgroundColor(CarDealerTD[10], 255);
    TextDrawFont(CarDealerTD[10], 4);
    TextDrawSetProportional(CarDealerTD[10], 1);

    CarDealerTD[11] = TextDrawCreate(531.000, 344.000, "LD_BUM:blkdot");
    TextDrawTextSize(CarDealerTD[11], 34.000, 1.000);
    TextDrawAlignment(CarDealerTD[11], 1);
    TextDrawColor(CarDealerTD[11], 0xff91a4ff);
    TextDrawSetShadow(CarDealerTD[11], 0);
    TextDrawSetOutline(CarDealerTD[11], 0);
    TextDrawBackgroundColor(CarDealerTD[11], 255);
    TextDrawFont(CarDealerTD[11], 4);
    TextDrawSetProportional(CarDealerTD[11], 1);

    CarDealerTD[12] = TextDrawCreate(545.000, 358.000, "LD_BEAT:chit");
    TextDrawTextSize(CarDealerTD[12], 26.000, 33.000);
    TextDrawAlignment(CarDealerTD[12], 1);
    TextDrawColor(CarDealerTD[12], -16776961);
    TextDrawSetShadow(CarDealerTD[12], 0);
    TextDrawSetOutline(CarDealerTD[12], 0);
    TextDrawBackgroundColor(CarDealerTD[12], 255);
    TextDrawFont(CarDealerTD[12], 4);
    TextDrawSetProportional(CarDealerTD[12], 1);
    TextDrawSetSelectable(CarDealerTD[12], 1);

    CarDealerTD[13] = TextDrawCreate(523.000, 358.000, "LD_BEAT:chit");
    TextDrawTextSize(CarDealerTD[13], 26.000, 33.000);
    TextDrawAlignment(CarDealerTD[13], 1);
    TextDrawColor(CarDealerTD[13], -65281);
    TextDrawSetShadow(CarDealerTD[13], 0);
    TextDrawSetOutline(CarDealerTD[13], 0);
    TextDrawBackgroundColor(CarDealerTD[13], 255);
    TextDrawFont(CarDealerTD[13], 4);
    TextDrawSetProportional(CarDealerTD[13], 1);
    TextDrawSetSelectable(CarDealerTD[13], 1);

    CarDealerTD[14] = TextDrawCreate(501.000, 358.000, "LD_BEAT:chit");
    TextDrawTextSize(CarDealerTD[14], 26.000, 33.000);
    TextDrawAlignment(CarDealerTD[14], 1);
    TextDrawColor(CarDealerTD[14], 16711935);
    TextDrawSetShadow(CarDealerTD[14], 0);
    TextDrawSetOutline(CarDealerTD[14], 0);
    TextDrawBackgroundColor(CarDealerTD[14], 255);
    TextDrawFont(CarDealerTD[14], 4);
    TextDrawSetProportional(CarDealerTD[14], 1);
    TextDrawSetSelectable(CarDealerTD[14], 1);

    CarDealerTD[15] = TextDrawCreate(479.000, 358.000, "LD_BEAT:chit");
    TextDrawTextSize(CarDealerTD[15], 26.000, 33.000);
    TextDrawAlignment(CarDealerTD[15], 1);
    TextDrawColor(CarDealerTD[15], 65535);
    TextDrawSetShadow(CarDealerTD[15], 0);
    TextDrawSetOutline(CarDealerTD[15], 0);
    TextDrawBackgroundColor(CarDealerTD[15], 255);
    TextDrawFont(CarDealerTD[15], 4);
    TextDrawSetProportional(CarDealerTD[15], 1);
    TextDrawSetSelectable(CarDealerTD[15], 1);

    CarDealerTD[16] = TextDrawCreate(457.000, 358.000, "LD_BEAT:chit");
    TextDrawTextSize(CarDealerTD[16], 26.000, 33.000);
    TextDrawAlignment(CarDealerTD[16], 1);
    TextDrawColor(CarDealerTD[16], 16295423);
    TextDrawSetShadow(CarDealerTD[16], 0);
    TextDrawSetOutline(CarDealerTD[16], 0);
    TextDrawBackgroundColor(CarDealerTD[16], 255);
    TextDrawFont(CarDealerTD[16], 4);
    TextDrawSetProportional(CarDealerTD[16], 1);
    TextDrawSetSelectable(CarDealerTD[16], 1);

    CarDealerTD[17] = TextDrawCreate(435.000, 358.000, "LD_BEAT:chit");
    TextDrawTextSize(CarDealerTD[17], 26.000, 33.000);
    TextDrawAlignment(CarDealerTD[17], 1);
    TextDrawColor(CarDealerTD[17], -1);
    TextDrawSetShadow(CarDealerTD[17], 0);
    TextDrawSetOutline(CarDealerTD[17], 0);
    TextDrawBackgroundColor(CarDealerTD[17], 255);
    TextDrawFont(CarDealerTD[17], 4);
    TextDrawSetProportional(CarDealerTD[17], 1);
    TextDrawSetSelectable(CarDealerTD[17], 1);

    CarDealerTD[18] = TextDrawCreate(413.000, 358.000, "LD_BEAT:chit");
    TextDrawTextSize(CarDealerTD[18], 26.000, 33.000);
    TextDrawAlignment(CarDealerTD[18], 1);
    TextDrawColor(CarDealerTD[18], 255);
    TextDrawSetShadow(CarDealerTD[18], 0);
    TextDrawSetOutline(CarDealerTD[18], 0);
    TextDrawBackgroundColor(CarDealerTD[18], 255);
    TextDrawFont(CarDealerTD[18], 4);
    TextDrawSetProportional(CarDealerTD[18], 1);
    TextDrawSetSelectable(CarDealerTD[18], 1);

    CarDealerTD[19] = TextDrawCreate(391.000, 358.000, "LD_BEAT:chit");
    TextDrawTextSize(CarDealerTD[19], 26.000, 33.000);
    TextDrawAlignment(CarDealerTD[19], 1);
    TextDrawColor(CarDealerTD[19], 1768516095);
    TextDrawSetShadow(CarDealerTD[19], 0);
    TextDrawSetOutline(CarDealerTD[19], 0);
    TextDrawBackgroundColor(CarDealerTD[19], 255);
    TextDrawFont(CarDealerTD[19], 4);
    TextDrawSetProportional(CarDealerTD[19], 1);
    TextDrawSetSelectable(CarDealerTD[19], 1);

    CarDealerTD[20] = TextDrawCreate(369.000, 358.000, "LD_BEAT:chit");
    TextDrawTextSize(CarDealerTD[20], 26.000, 33.000);
    TextDrawAlignment(CarDealerTD[20], 1);
    TextDrawColor(CarDealerTD[20], -1811885057);
    TextDrawSetShadow(CarDealerTD[20], 0);
    TextDrawSetOutline(CarDealerTD[20], 0);
    TextDrawBackgroundColor(CarDealerTD[20], 255);
    TextDrawFont(CarDealerTD[20], 4);
    TextDrawSetProportional(CarDealerTD[20], 1);
    TextDrawSetSelectable(CarDealerTD[20], 1);

    CarDealerTD[21] = TextDrawCreate(434.000, 327.000, "LD_BUM:blkdot");
    TextDrawTextSize(CarDealerTD[21], 43.000, 18.000);
    TextDrawAlignment(CarDealerTD[21], 1);
    TextDrawColor(CarDealerTD[21], 421075455);
    TextDrawSetShadow(CarDealerTD[21], 0);
    TextDrawSetOutline(CarDealerTD[21], 0);
    TextDrawBackgroundColor(CarDealerTD[21], 255);
    TextDrawFont(CarDealerTD[21], 4);
    TextDrawSetProportional(CarDealerTD[21], 1);
    TextDrawSetSelectable(CarDealerTD[21], 1);

    CarDealerTD[22] = TextDrawCreate(434.000, 344.000, "LD_BUM:blkdot");
    TextDrawTextSize(CarDealerTD[22], 43.000, 1.000);
    TextDrawAlignment(CarDealerTD[22], 1);
    TextDrawColor(CarDealerTD[22], 0xff91a4ff);
    TextDrawSetShadow(CarDealerTD[22], 0);
    TextDrawSetOutline(CarDealerTD[22], 0);
    TextDrawBackgroundColor(CarDealerTD[22], 255);
    TextDrawFont(CarDealerTD[22], 4);
    TextDrawSetProportional(CarDealerTD[22], 1);

    CarDealerTD[23] = TextDrawCreate(456.000, 330.000, "PURCHASE");
    TextDrawLetterSize(CarDealerTD[23], 0.200, 1.098);
    TextDrawAlignment(CarDealerTD[23], 2);
    TextDrawColor(CarDealerTD[23], -1);
    TextDrawSetShadow(CarDealerTD[23], 1);
    TextDrawSetOutline(CarDealerTD[23], 1);
    TextDrawBackgroundColor(CarDealerTD[23], 0);
    TextDrawFont(CarDealerTD[23], 1);
    TextDrawSetProportional(CarDealerTD[23], 1);

    CarDealerTD[24] = TextDrawCreate(381.000, 327.000, "LD_BUM:blkdot");
    TextDrawTextSize(CarDealerTD[24], 43.000, 18.000);
    TextDrawAlignment(CarDealerTD[24], 1);
    TextDrawColor(CarDealerTD[24], 421075455);
    TextDrawSetShadow(CarDealerTD[24], 0);
    TextDrawSetOutline(CarDealerTD[24], 0);
    TextDrawBackgroundColor(CarDealerTD[24], 255);
    TextDrawFont(CarDealerTD[24], 4);
    TextDrawSetProportional(CarDealerTD[24], 1);
    TextDrawSetSelectable(CarDealerTD[24], 1);

    CarDealerTD[25] = TextDrawCreate(381.000, 344.000, "LD_BUM:blkdot");
    TextDrawTextSize(CarDealerTD[25], 43.000, 1.000);
    TextDrawAlignment(CarDealerTD[25], 1);
    TextDrawColor(CarDealerTD[25], 0xff91a4ff);
    TextDrawSetShadow(CarDealerTD[25], 0);
    TextDrawSetOutline(CarDealerTD[25], 0);
    TextDrawBackgroundColor(CarDealerTD[25], 255);
    TextDrawFont(CarDealerTD[25], 4);
    TextDrawSetProportional(CarDealerTD[25], 1);

    CarDealerTD[26] = TextDrawCreate(403.000, 330.000, "Batal");
    TextDrawLetterSize(CarDealerTD[26], 0.200, 1.098);
    TextDrawAlignment(CarDealerTD[26], 2);
    TextDrawColor(CarDealerTD[26], -1);
    TextDrawSetShadow(CarDealerTD[26], 1);
    TextDrawSetOutline(CarDealerTD[26], 1);
    TextDrawBackgroundColor(CarDealerTD[26], 0);
    TextDrawFont(CarDealerTD[26], 1);
    TextDrawSetProportional(CarDealerTD[26], 1);
}

CreateCarDealerPTD(playerid)
{
    CarDealerPTD[playerid][0] = CreatePlayerTextDraw(playerid, 565.000, 285.000, "30/30");
    PlayerTextDrawLetterSize(playerid, CarDealerPTD[playerid][0], 0.217, 1.199);
    PlayerTextDrawAlignment(playerid, CarDealerPTD[playerid][0], 3);
    PlayerTextDrawColor(playerid, CarDealerPTD[playerid][0], 0xff91a4ff);
    PlayerTextDrawSetShadow(playerid, CarDealerPTD[playerid][0], 1);
    PlayerTextDrawSetOutline(playerid, CarDealerPTD[playerid][0], 1);
    PlayerTextDrawBackgroundColor(playerid, CarDealerPTD[playerid][0], 0);
    PlayerTextDrawFont(playerid, CarDealerPTD[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, CarDealerPTD[playerid][0], 1);

    CarDealerPTD[playerid][1] = CreatePlayerTextDraw(playerid, 565.000, 297.000, "Landstalker - $50.000");
    PlayerTextDrawLetterSize(playerid, CarDealerPTD[playerid][1], 0.217, 1.199);
    PlayerTextDrawAlignment(playerid, CarDealerPTD[playerid][1], 3);
    PlayerTextDrawColor(playerid, CarDealerPTD[playerid][1], 0xff91a4ff);
    PlayerTextDrawSetShadow(playerid, CarDealerPTD[playerid][1], 1);
    PlayerTextDrawSetOutline(playerid, CarDealerPTD[playerid][1], 1);
    PlayerTextDrawBackgroundColor(playerid, CarDealerPTD[playerid][1], 0);
    PlayerTextDrawFont(playerid, CarDealerPTD[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, CarDealerPTD[playerid][1], 1);

    CarDealerPTD[playerid][2] = CreatePlayerTextDraw(playerid, 565.000, 309.000, "75kg Trunk Capacity");
    PlayerTextDrawLetterSize(playerid, CarDealerPTD[playerid][2], 0.167, 0.898);
    PlayerTextDrawAlignment(playerid, CarDealerPTD[playerid][2], 3);
    PlayerTextDrawColor(playerid, CarDealerPTD[playerid][2], 0xff91a4ff);
    PlayerTextDrawSetShadow(playerid, CarDealerPTD[playerid][2], 1);
    PlayerTextDrawSetOutline(playerid, CarDealerPTD[playerid][2], 1);
    PlayerTextDrawBackgroundColor(playerid, CarDealerPTD[playerid][2], 0);
    PlayerTextDrawFont(playerid, CarDealerPTD[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, CarDealerPTD[playerid][2], 1);
}

ShowCarDealerTD(playerid)
{
    for(new x; x < 27; x++)
    {
        TextDrawShowForPlayer(playerid, CarDealerTD[x]);
    }
    PlayerTextDrawShow(playerid, CarDealerPTD[playerid][0]);
    PlayerTextDrawShow(playerid, CarDealerPTD[playerid][1]);
    PlayerTextDrawShow(playerid, CarDealerPTD[playerid][2]);
}

HideCarDealerTD(playerid)
{
    for(new x; x < 27; x++)
    {
        TextDrawHideForPlayer(playerid, CarDealerTD[x]);
    }
    PlayerTextDrawHide(playerid, CarDealerPTD[playerid][0]);
    PlayerTextDrawHide(playerid, CarDealerPTD[playerid][1]);
    PlayerTextDrawHide(playerid, CarDealerPTD[playerid][2]);
}