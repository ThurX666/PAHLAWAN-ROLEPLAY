new Text:EmotesTD[24];
new PlayerText:EmotesPTD[MAX_PLAYERS][11];

CreateEmotesTD()
{
    EmotesTD[0] = TextDrawCreate(480.500, 100.000, "LD_BUM:blkdot");
    TextDrawTextSize(EmotesTD[0], 156.000, 17.000);
    TextDrawAlignment(EmotesTD[0], 1);
    TextDrawColor(EmotesTD[0], -577620788);
    TextDrawSetShadow(EmotesTD[0], 0);
    TextDrawSetOutline(EmotesTD[0], 0);
    TextDrawBackgroundColor(EmotesTD[0], 255);
    TextDrawFont(EmotesTD[0], 4);
    TextDrawSetProportional(EmotesTD[0], 1);

    EmotesTD[1] = TextDrawCreate(480.500, 52.500, "LD_BUM:blkdot");
    TextDrawTextSize(EmotesTD[1], 156.000, 47.500);
    TextDrawAlignment(EmotesTD[1], 1);
    TextDrawColor(EmotesTD[1], -72336436);
    TextDrawSetShadow(EmotesTD[1], 0);
    TextDrawSetOutline(EmotesTD[1], 0);
    TextDrawBackgroundColor(EmotesTD[1], 255);
    TextDrawFont(EmotesTD[1], 4);
    TextDrawSetProportional(EmotesTD[1], 1);

    EmotesTD[2] = TextDrawCreate(557.000, 64.000, "EMOTE LIST");
    TextDrawLetterSize(EmotesTD[2], 0.469, 2.299);
    TextDrawAlignment(EmotesTD[2], 2);
    TextDrawColor(EmotesTD[2], -1);
    TextDrawSetShadow(EmotesTD[2], 1);
    TextDrawSetOutline(EmotesTD[2], 1);
    TextDrawBackgroundColor(EmotesTD[2], 0);
    TextDrawFont(EmotesTD[2], 3);
    TextDrawSetProportional(EmotesTD[2], 1);

    EmotesTD[3] = TextDrawCreate(494.000, 105.000, "Emote Animations");
    TextDrawLetterSize(EmotesTD[3], 0.190, 0.999);
    TextDrawAlignment(EmotesTD[3], 1);
    TextDrawColor(EmotesTD[3], -1);
    TextDrawSetShadow(EmotesTD[3], 1);
    TextDrawSetOutline(EmotesTD[3], 1);
    TextDrawBackgroundColor(EmotesTD[3], 0);
    TextDrawFont(EmotesTD[3], 1);
    TextDrawSetProportional(EmotesTD[3], 1);

    EmotesTD[4] = TextDrawCreate(485.000, 103.000, "LD_BEAT:chit");
    TextDrawTextSize(EmotesTD[4], 6.000, 7.000);
    TextDrawAlignment(EmotesTD[4], 1);
    TextDrawColor(EmotesTD[4], -1);
    TextDrawSetShadow(EmotesTD[4], 0);
    TextDrawSetOutline(EmotesTD[4], 0);
    TextDrawBackgroundColor(EmotesTD[4], 255);
    TextDrawFont(EmotesTD[4], 4);
    TextDrawSetProportional(EmotesTD[4], 1);

    EmotesTD[5] = TextDrawCreate(483.000, 108.000, "LD_BEAT:chit");
    TextDrawTextSize(EmotesTD[5], 10.000, 7.000);
    TextDrawAlignment(EmotesTD[5], 1);
    TextDrawColor(EmotesTD[5], -1);
    TextDrawSetShadow(EmotesTD[5], 0);
    TextDrawSetOutline(EmotesTD[5], 0);
    TextDrawBackgroundColor(EmotesTD[5], 255);
    TextDrawFont(EmotesTD[5], 4);
    TextDrawSetProportional(EmotesTD[5], 1);

    EmotesTD[6] = TextDrawCreate(480.500, 117.000, "LD_BUM:blkdot");
    TextDrawTextSize(EmotesTD[6], 156.000, 178.000);
    TextDrawAlignment(EmotesTD[6], 1);
    TextDrawColor(EmotesTD[6], 148);
    TextDrawSetShadow(EmotesTD[6], 0);
    TextDrawSetOutline(EmotesTD[6], 0);
    TextDrawBackgroundColor(EmotesTD[6], 255);
    TextDrawFont(EmotesTD[6], 4);
    TextDrawSetProportional(EmotesTD[6], 1);

    EmotesTD[7] = TextDrawCreate(480.500, 117.200, "LD_BUM:blkdot"); //1
    TextDrawTextSize(EmotesTD[7], 156.000, 16.500);
    TextDrawAlignment(EmotesTD[7], 1);
    TextDrawColor(EmotesTD[7], 0);
    TextDrawSetShadow(EmotesTD[7], 0);
    TextDrawSetOutline(EmotesTD[7], 0);
    TextDrawBackgroundColor(EmotesTD[7], 255);
    TextDrawFont(EmotesTD[7], 4);
    TextDrawSetProportional(EmotesTD[7], 1);
    TextDrawSetSelectable(EmotesTD[7], 1);

    EmotesTD[8] = TextDrawCreate(480.500, 133.500, "LD_BUM:blkdot"); //2
    TextDrawTextSize(EmotesTD[8], 156.000, 16.500);
    TextDrawAlignment(EmotesTD[8], 1);
    TextDrawColor(EmotesTD[8], 0);
    TextDrawSetShadow(EmotesTD[8], 0);
    TextDrawSetOutline(EmotesTD[8], 0);
    TextDrawBackgroundColor(EmotesTD[8], 255);
    TextDrawFont(EmotesTD[8], 4);
    TextDrawSetProportional(EmotesTD[8], 1);
    TextDrawSetSelectable(EmotesTD[8], 1);

    EmotesTD[9] = TextDrawCreate(480.500, 150.199, "LD_BUM:blkdot"); //3
    TextDrawTextSize(EmotesTD[9], 156.000, 16.500);
    TextDrawAlignment(EmotesTD[9], 1);
    TextDrawColor(EmotesTD[9], 0);
    TextDrawSetShadow(EmotesTD[9], 0);
    TextDrawSetOutline(EmotesTD[9], 0);
    TextDrawBackgroundColor(EmotesTD[9], 255);
    TextDrawFont(EmotesTD[9], 4);
    TextDrawSetProportional(EmotesTD[9], 1);
    TextDrawSetSelectable(EmotesTD[9], 1);

    EmotesTD[10] = TextDrawCreate(480.500, 166.199, "LD_BUM:blkdot"); //4
    TextDrawTextSize(EmotesTD[10], 156.000, 16.500);
    TextDrawAlignment(EmotesTD[10], 1);
    TextDrawColor(EmotesTD[10], 0);
    TextDrawSetShadow(EmotesTD[10], 0);
    TextDrawSetOutline(EmotesTD[10], 0);
    TextDrawBackgroundColor(EmotesTD[10], 255);
    TextDrawFont(EmotesTD[10], 4);
    TextDrawSetProportional(EmotesTD[10], 1);
    TextDrawSetSelectable(EmotesTD[10], 1);

    EmotesTD[11] = TextDrawCreate(480.500, 182.199, "LD_BUM:blkdot"); //5
    TextDrawTextSize(EmotesTD[11], 156.000, 16.500);
    TextDrawAlignment(EmotesTD[11], 1);
    TextDrawColor(EmotesTD[11], 0);
    TextDrawSetShadow(EmotesTD[11], 0);
    TextDrawSetOutline(EmotesTD[11], 0);
    TextDrawBackgroundColor(EmotesTD[11], 255);
    TextDrawFont(EmotesTD[11], 4);
    TextDrawSetProportional(EmotesTD[11], 1);
    TextDrawSetSelectable(EmotesTD[11], 1);

    EmotesTD[12] = TextDrawCreate(480.500, 198.199, "LD_BUM:blkdot"); //6
    TextDrawTextSize(EmotesTD[12], 156.000, 16.500);
    TextDrawAlignment(EmotesTD[12], 1);
    TextDrawColor(EmotesTD[12], 0);
    TextDrawSetShadow(EmotesTD[12], 0);
    TextDrawSetOutline(EmotesTD[12], 0);
    TextDrawBackgroundColor(EmotesTD[12], 255);
    TextDrawFont(EmotesTD[12], 4);
    TextDrawSetProportional(EmotesTD[12], 1);
    TextDrawSetSelectable(EmotesTD[12], 1);

    EmotesTD[13] = TextDrawCreate(480.500, 214.199, "LD_BUM:blkdot"); //7
    TextDrawTextSize(EmotesTD[13], 156.000, 16.500);
    TextDrawAlignment(EmotesTD[13], 1);
    TextDrawColor(EmotesTD[13], 0);
    TextDrawSetShadow(EmotesTD[13], 0);
    TextDrawSetOutline(EmotesTD[13], 0);
    TextDrawBackgroundColor(EmotesTD[13], 255);
    TextDrawFont(EmotesTD[13], 4);
    TextDrawSetProportional(EmotesTD[13], 1);
    TextDrawSetSelectable(EmotesTD[13], 1);

    EmotesTD[14] = TextDrawCreate(480.500, 230.199, "LD_BUM:blkdot"); //8
    TextDrawTextSize(EmotesTD[14], 156.000, 16.500);
    TextDrawAlignment(EmotesTD[14], 1);
    TextDrawColor(EmotesTD[14], 0);
    TextDrawSetShadow(EmotesTD[14], 0);
    TextDrawSetOutline(EmotesTD[14], 0);
    TextDrawBackgroundColor(EmotesTD[14], 255);
    TextDrawFont(EmotesTD[14], 4);
    TextDrawSetProportional(EmotesTD[14], 1);
    TextDrawSetSelectable(EmotesTD[14], 1);

    EmotesTD[15] = TextDrawCreate(480.500, 246.199, "LD_BUM:blkdot"); //9
    TextDrawTextSize(EmotesTD[15], 156.000, 16.500);
    TextDrawAlignment(EmotesTD[15], 1);
    TextDrawColor(EmotesTD[15], 0);
    TextDrawSetShadow(EmotesTD[15], 0);
    TextDrawSetOutline(EmotesTD[15], 0);
    TextDrawBackgroundColor(EmotesTD[15], 255);
    TextDrawFont(EmotesTD[15], 4);
    TextDrawSetProportional(EmotesTD[15], 1);
    TextDrawSetSelectable(EmotesTD[15], 1);

    EmotesTD[16] = TextDrawCreate(480.500, 262.199, "LD_BUM:blkdot"); //10
    TextDrawTextSize(EmotesTD[16], 156.000, 16.500);
    TextDrawAlignment(EmotesTD[16], 1);
    TextDrawColor(EmotesTD[16], 0);
    TextDrawSetShadow(EmotesTD[16], 0);
    TextDrawSetOutline(EmotesTD[16], 0);
    TextDrawBackgroundColor(EmotesTD[16], 255);
    TextDrawFont(EmotesTD[16], 4);
    TextDrawSetProportional(EmotesTD[16], 1);
    TextDrawSetSelectable(EmotesTD[16], 1);

    EmotesTD[17] = TextDrawCreate(480.500, 278.500, "LD_BUM:blkdot");
    TextDrawTextSize(EmotesTD[17], 156.000, 16.500);
    TextDrawAlignment(EmotesTD[17], 1);
    TextDrawColor(EmotesTD[17], 148);
    TextDrawSetShadow(EmotesTD[17], 0);
    TextDrawSetOutline(EmotesTD[17], 0);
    TextDrawBackgroundColor(EmotesTD[17], 255);
    TextDrawFont(EmotesTD[17], 4);
    TextDrawSetProportional(EmotesTD[17], 1);

    EmotesTD[18] = TextDrawCreate(480.500, 297.500, "LD_BUM:blkdot");
    TextDrawTextSize(EmotesTD[18], 156.000, 30.500);
    TextDrawAlignment(EmotesTD[18], 1);
    TextDrawColor(EmotesTD[18], 148);
    TextDrawSetShadow(EmotesTD[18], 0);
    TextDrawSetOutline(EmotesTD[18], 0);
    TextDrawBackgroundColor(EmotesTD[18], 255);
    TextDrawFont(EmotesTD[18], 4);
    TextDrawSetProportional(EmotesTD[18], 1);

    EmotesTD[19] = TextDrawCreate(484.000, 302.000, "/e (~g~nama~w~) untuk memainkannya atau klik langsung di atas");
    TextDrawLetterSize(EmotesTD[19], 0.179, 0.999);
    TextDrawTextSize(EmotesTD[19], 620.000, 0.000);
    TextDrawAlignment(EmotesTD[19], 1);
    TextDrawColor(EmotesTD[19], -1);
    TextDrawSetShadow(EmotesTD[19], 1);
    TextDrawSetOutline(EmotesTD[19], 1);
    TextDrawBackgroundColor(EmotesTD[19], 0);
    TextDrawFont(EmotesTD[19], 1);
    TextDrawSetProportional(EmotesTD[19], 1);

    EmotesTD[20] = TextDrawCreate(557.000, 80.000, "Pahlawan Roleplay");
    TextDrawLetterSize(EmotesTD[20], 0.349, 1.499);
    TextDrawAlignment(EmotesTD[20], 2);
    TextDrawColor(EmotesTD[20], -1);
    TextDrawSetShadow(EmotesTD[20], 1);
    TextDrawSetOutline(EmotesTD[20], 1);
    TextDrawBackgroundColor(EmotesTD[20], 0);
    TextDrawFont(EmotesTD[20], 0);
    TextDrawSetProportional(EmotesTD[20], 1);

    EmotesTD[21] = TextDrawCreate(599.000, 280.600, "NEXT >"); //next
    TextDrawLetterSize(EmotesTD[21], 0.220, 1.199);
    TextDrawTextSize(EmotesTD[21], 628.000, 12.000);
    TextDrawAlignment(EmotesTD[21], 1);
    TextDrawColor(EmotesTD[21], -1);
    TextDrawSetShadow(EmotesTD[21], 1);
    TextDrawSetOutline(EmotesTD[21], 1);
    TextDrawBackgroundColor(EmotesTD[21], 0);
    TextDrawFont(EmotesTD[21], 1);
    TextDrawSetProportional(EmotesTD[21], 1);
    TextDrawSetSelectable(EmotesTD[21], 1);

    EmotesTD[22] = TextDrawCreate(490.000, 280.600, "< PREV"); //prev
    TextDrawLetterSize(EmotesTD[22], 0.220, 1.199);
    TextDrawTextSize(EmotesTD[22], 519.000, 12.000);
    TextDrawAlignment(EmotesTD[22], 1);
    TextDrawColor(EmotesTD[22], -1);
    TextDrawSetShadow(EmotesTD[22], 1);
    TextDrawSetOutline(EmotesTD[22], 1);
    TextDrawBackgroundColor(EmotesTD[22], 0);
    TextDrawFont(EmotesTD[22], 1);
    TextDrawSetProportional(EmotesTD[22], 1);
    TextDrawSetSelectable(EmotesTD[22], 1);

    EmotesTD[23] = TextDrawCreate(552.000, 279.500, "LD_BEAT:cross"); //close
    TextDrawTextSize(EmotesTD[23], 12.000, 15.000);
    TextDrawAlignment(EmotesTD[23], 1);
    TextDrawColor(EmotesTD[23], -1);
    TextDrawSetShadow(EmotesTD[23], 0);
    TextDrawSetOutline(EmotesTD[23], 0);
    TextDrawBackgroundColor(EmotesTD[23], 255);
    TextDrawFont(EmotesTD[23], 4);
    TextDrawSetProportional(EmotesTD[23], 1);
    TextDrawSetSelectable(EmotesTD[23], 1);
}

CreateEmotesPTD(playerid)
{
    EmotesPTD[playerid][0] = CreatePlayerTextDraw(playerid, 483.500, 120.000, "Emote 1");
    PlayerTextDrawLetterSize(playerid, EmotesPTD[playerid][0], 0.210, 1.099);
    PlayerTextDrawAlignment(playerid, EmotesPTD[playerid][0], 1);
    PlayerTextDrawColor(playerid, EmotesPTD[playerid][0], -1);
    PlayerTextDrawSetShadow(playerid, EmotesPTD[playerid][0], 1);
    PlayerTextDrawSetOutline(playerid, EmotesPTD[playerid][0], 1);
    PlayerTextDrawBackgroundColor(playerid, EmotesPTD[playerid][0], 0);
    PlayerTextDrawFont(playerid, EmotesPTD[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, EmotesPTD[playerid][0], 1);

    EmotesPTD[playerid][1] = CreatePlayerTextDraw(playerid, 483.500, 136.000, "Emote 2");
    PlayerTextDrawLetterSize(playerid, EmotesPTD[playerid][1], 0.210, 1.099);
    PlayerTextDrawAlignment(playerid, EmotesPTD[playerid][1], 1);
    PlayerTextDrawColor(playerid, EmotesPTD[playerid][1], -1);
    PlayerTextDrawSetShadow(playerid, EmotesPTD[playerid][1], 1);
    PlayerTextDrawSetOutline(playerid, EmotesPTD[playerid][1], 1);
    PlayerTextDrawBackgroundColor(playerid, EmotesPTD[playerid][1], 0);
    PlayerTextDrawFont(playerid, EmotesPTD[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, EmotesPTD[playerid][1], 1);

    EmotesPTD[playerid][2] = CreatePlayerTextDraw(playerid, 483.500, 152.000, "Emote 3");
    PlayerTextDrawLetterSize(playerid, EmotesPTD[playerid][2], 0.210, 1.099);
    PlayerTextDrawAlignment(playerid, EmotesPTD[playerid][2], 1);
    PlayerTextDrawColor(playerid, EmotesPTD[playerid][2], -1);
    PlayerTextDrawSetShadow(playerid, EmotesPTD[playerid][2], 1);
    PlayerTextDrawSetOutline(playerid, EmotesPTD[playerid][2], 1);
    PlayerTextDrawBackgroundColor(playerid, EmotesPTD[playerid][2], 0);
    PlayerTextDrawFont(playerid, EmotesPTD[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, EmotesPTD[playerid][2], 1);

    EmotesPTD[playerid][3] = CreatePlayerTextDraw(playerid, 483.500, 168.000, "Emote 4");
    PlayerTextDrawLetterSize(playerid, EmotesPTD[playerid][3], 0.210, 1.099);
    PlayerTextDrawAlignment(playerid, EmotesPTD[playerid][3], 1);
    PlayerTextDrawColor(playerid, EmotesPTD[playerid][3], -1);
    PlayerTextDrawSetShadow(playerid, EmotesPTD[playerid][3], 1);
    PlayerTextDrawSetOutline(playerid, EmotesPTD[playerid][3], 1);
    PlayerTextDrawBackgroundColor(playerid, EmotesPTD[playerid][3], 0);
    PlayerTextDrawFont(playerid, EmotesPTD[playerid][3], 1);
    PlayerTextDrawSetProportional(playerid, EmotesPTD[playerid][3], 1);

    EmotesPTD[playerid][4] = CreatePlayerTextDraw(playerid, 483.500, 184.000, "Emote 5");
    PlayerTextDrawLetterSize(playerid, EmotesPTD[playerid][4], 0.210, 1.099);
    PlayerTextDrawAlignment(playerid, EmotesPTD[playerid][4], 1);
    PlayerTextDrawColor(playerid, EmotesPTD[playerid][4], -1);
    PlayerTextDrawSetShadow(playerid, EmotesPTD[playerid][4], 1);
    PlayerTextDrawSetOutline(playerid, EmotesPTD[playerid][4], 1);
    PlayerTextDrawBackgroundColor(playerid, EmotesPTD[playerid][4], 0);
    PlayerTextDrawFont(playerid, EmotesPTD[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, EmotesPTD[playerid][4], 1);

    EmotesPTD[playerid][5] = CreatePlayerTextDraw(playerid, 483.500, 200.000, "Emote 6");
    PlayerTextDrawLetterSize(playerid, EmotesPTD[playerid][5], 0.210, 1.099);
    PlayerTextDrawAlignment(playerid, EmotesPTD[playerid][5], 1);
    PlayerTextDrawColor(playerid, EmotesPTD[playerid][5], -1);
    PlayerTextDrawSetShadow(playerid, EmotesPTD[playerid][5], 1);
    PlayerTextDrawSetOutline(playerid, EmotesPTD[playerid][5], 1);
    PlayerTextDrawBackgroundColor(playerid, EmotesPTD[playerid][5], 0);
    PlayerTextDrawFont(playerid, EmotesPTD[playerid][5], 1);
    PlayerTextDrawSetProportional(playerid, EmotesPTD[playerid][5], 1);

    EmotesPTD[playerid][6] = CreatePlayerTextDraw(playerid, 483.500, 216.000, "Emote 7");
    PlayerTextDrawLetterSize(playerid, EmotesPTD[playerid][6], 0.210, 1.099);
    PlayerTextDrawAlignment(playerid, EmotesPTD[playerid][6], 1);
    PlayerTextDrawColor(playerid, EmotesPTD[playerid][6], -1);
    PlayerTextDrawSetShadow(playerid, EmotesPTD[playerid][6], 1);
    PlayerTextDrawSetOutline(playerid, EmotesPTD[playerid][6], 1);
    PlayerTextDrawBackgroundColor(playerid, EmotesPTD[playerid][6], 0);
    PlayerTextDrawFont(playerid, EmotesPTD[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, EmotesPTD[playerid][6], 1);

    EmotesPTD[playerid][7] = CreatePlayerTextDraw(playerid, 483.500, 232.000, "Emote 8");
    PlayerTextDrawLetterSize(playerid, EmotesPTD[playerid][7], 0.210, 1.099);
    PlayerTextDrawAlignment(playerid, EmotesPTD[playerid][7], 1);
    PlayerTextDrawColor(playerid, EmotesPTD[playerid][7], -1);
    PlayerTextDrawSetShadow(playerid, EmotesPTD[playerid][7], 1);
    PlayerTextDrawSetOutline(playerid, EmotesPTD[playerid][7], 1);
    PlayerTextDrawBackgroundColor(playerid, EmotesPTD[playerid][7], 0);
    PlayerTextDrawFont(playerid, EmotesPTD[playerid][7], 1);
    PlayerTextDrawSetProportional(playerid, EmotesPTD[playerid][7], 1);

    EmotesPTD[playerid][8] = CreatePlayerTextDraw(playerid, 483.500, 248.000, "Emote 9");
    PlayerTextDrawLetterSize(playerid, EmotesPTD[playerid][8], 0.210, 1.099);
    PlayerTextDrawAlignment(playerid, EmotesPTD[playerid][8], 1);
    PlayerTextDrawColor(playerid, EmotesPTD[playerid][8], -1);
    PlayerTextDrawSetShadow(playerid, EmotesPTD[playerid][8], 1);
    PlayerTextDrawSetOutline(playerid, EmotesPTD[playerid][8], 1);
    PlayerTextDrawBackgroundColor(playerid, EmotesPTD[playerid][8], 0);
    PlayerTextDrawFont(playerid, EmotesPTD[playerid][8], 1);
    PlayerTextDrawSetProportional(playerid, EmotesPTD[playerid][8], 1);

    EmotesPTD[playerid][9] = CreatePlayerTextDraw(playerid, 483.500, 264.000, "Emote 10");
    PlayerTextDrawLetterSize(playerid, EmotesPTD[playerid][9], 0.210, 1.099);
    PlayerTextDrawAlignment(playerid, EmotesPTD[playerid][9], 1);
    PlayerTextDrawColor(playerid, EmotesPTD[playerid][9], -1);
    PlayerTextDrawSetShadow(playerid, EmotesPTD[playerid][9], 1);
    PlayerTextDrawSetOutline(playerid, EmotesPTD[playerid][9], 1);
    PlayerTextDrawBackgroundColor(playerid, EmotesPTD[playerid][9], 0);
    PlayerTextDrawFont(playerid, EmotesPTD[playerid][9], 1);
    PlayerTextDrawSetProportional(playerid, EmotesPTD[playerid][9], 1);

    EmotesPTD[playerid][10] = CreatePlayerTextDraw(playerid, 633.000, 105.000, "200 / 200");
    PlayerTextDrawLetterSize(playerid, EmotesPTD[playerid][10], 0.190, 0.999);
    PlayerTextDrawAlignment(playerid, EmotesPTD[playerid][10], 3);
    PlayerTextDrawColor(playerid, EmotesPTD[playerid][10], -1);
    PlayerTextDrawSetShadow(playerid, EmotesPTD[playerid][10], 1);
    PlayerTextDrawSetOutline(playerid, EmotesPTD[playerid][10], 1);
    PlayerTextDrawBackgroundColor(playerid, EmotesPTD[playerid][10], 0);
    PlayerTextDrawFont(playerid, EmotesPTD[playerid][10], 1);
    PlayerTextDrawSetProportional(playerid, EmotesPTD[playerid][10], 1);
}