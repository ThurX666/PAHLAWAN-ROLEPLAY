new 
    Text:ProgBarTD[1],
    PlayerText:ProgressBar[MAX_PLAYERS][2];

CreateProgbarTD()
{
    ProgBarTD[0] = TextDrawCreate(217.000000, 368.000000, "ld_dual:white");
    TextDrawFont(ProgBarTD[0], 4);
    TextDrawLetterSize(ProgBarTD[0], 0.600000, 2.000000);
    TextDrawTextSize(ProgBarTD[0], 102.000000, 20.000000);
    TextDrawSetOutline(ProgBarTD[0], true);
    TextDrawSetShadow(ProgBarTD[0], false);
    TextDrawAlignment(ProgBarTD[0], true);
    TextDrawColor(ProgBarTD[0], 0x00000066);
    TextDrawBackgroundColor(ProgBarTD[0], 0x00000066);
    TextDrawBoxColor(ProgBarTD[0], 50);
    TextDrawUseBox(ProgBarTD[0], true);
    TextDrawSetProportional(ProgBarTD[0], true);
    TextDrawSetSelectable(ProgBarTD[0], false);
}

CreateProgressBarTD(playerid)
{
    ProgressBar[playerid][0] = CreatePlayerTextDraw(playerid, 217.000000, 368.000000, "ld_dual:white");
    PlayerTextDrawFont(playerid, ProgressBar[playerid][0], 4);
    PlayerTextDrawLetterSize(playerid, ProgressBar[playerid][0], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], 102.000000, 20.000000);
    PlayerTextDrawSetOutline(playerid, ProgressBar[playerid][0], true);
    PlayerTextDrawSetShadow(playerid, ProgressBar[playerid][0], false);
    PlayerTextDrawAlignment(playerid, ProgressBar[playerid][0], true);
    PlayerTextDrawColor(playerid, ProgressBar[playerid][0], 0xff91a4cc);
    PlayerTextDrawBackgroundColor(playerid, ProgressBar[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, ProgressBar[playerid][0], 50);
    PlayerTextDrawUseBox(playerid, ProgressBar[playerid][0], true);
    PlayerTextDrawSetProportional(playerid, ProgressBar[playerid][0], true);
    PlayerTextDrawSetSelectable(playerid, ProgressBar[playerid][0], false);

    ProgressBar[playerid][1] = CreatePlayerTextDraw(playerid, 268.000000, 371.500000, "MEMOTONG PAPAN");
    PlayerTextDrawFont(playerid, ProgressBar[playerid][1], true);
    PlayerTextDrawLetterSize(playerid, ProgressBar[playerid][1], 0.212499, 1.400000);
    PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], 400.000000, 104.000000);
    PlayerTextDrawSetOutline(playerid, ProgressBar[playerid][1], false);
    PlayerTextDrawSetShadow(playerid, ProgressBar[playerid][1], false);
    PlayerTextDrawAlignment(playerid, ProgressBar[playerid][1], 2);
    PlayerTextDrawColor(playerid, ProgressBar[playerid][1], 0xffffffe6);
    PlayerTextDrawBackgroundColor(playerid, ProgressBar[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, ProgressBar[playerid][1], 50);
    PlayerTextDrawUseBox(playerid, ProgressBar[playerid][1], false);
    PlayerTextDrawSetProportional(playerid, ProgressBar[playerid][1], true);
    PlayerTextDrawSetSelectable(playerid, ProgressBar[playerid][1], false);
}

ShowProgressBar(playerid)
{
    TextDrawShowForPlayer(playerid, ProgBarTD[0]);
    static Float:progressvalue;
    progressvalue = AccountData[playerid][pActivityTime] * 102.0/100;
    PlayerTextDrawTextSize(playerid, ProgressBar[playerid][0], progressvalue, 20.0);
    PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
    PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
}

HideProgressBar(playerid)
{
    TextDrawHideForPlayer(playerid, ProgBarTD[0]);
    PlayerTextDrawHide(playerid, ProgressBar[playerid][0]);
    PlayerTextDrawHide(playerid, ProgressBar[playerid][1]);
}