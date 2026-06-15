new Text:PaycheckTD[2],
    PlayerText:InfoPaycheckTD[MAX_PLAYERS];

CreatePaycheckTD()
{
    PaycheckTD[0] = TextDrawCreate(474.000000, 4.000000, "ld_beat:chit");
    TextDrawFont(PaycheckTD[0], 4);
    TextDrawLetterSize(PaycheckTD[0], 0.600000, 2.000000);
    TextDrawTextSize(PaycheckTD[0], 17.000000, 20.000000);
    TextDrawSetOutline(PaycheckTD[0], 1);
    TextDrawSetShadow(PaycheckTD[0], 0);
    TextDrawAlignment(PaycheckTD[0], 1);
    TextDrawColor(PaycheckTD[0], -7232257);
    TextDrawBackgroundColor(PaycheckTD[0], 255);
    TextDrawBoxColor(PaycheckTD[0], 50);
    TextDrawUseBox(PaycheckTD[0], 1);
    TextDrawSetProportional(PaycheckTD[0], 1);
    TextDrawSetSelectable(PaycheckTD[0], 0);

    PaycheckTD[1] = TextDrawCreate(610.000000, 4.000000, "ld_beat:chit");
    TextDrawFont(PaycheckTD[1], 4);
    TextDrawLetterSize(PaycheckTD[1], 0.600000, 2.000000);
    TextDrawTextSize(PaycheckTD[1], 17.000000, 20.000000);
    TextDrawSetOutline(PaycheckTD[1], 1);
    TextDrawSetShadow(PaycheckTD[1], 0);
    TextDrawAlignment(PaycheckTD[1], 1);
    TextDrawColor(PaycheckTD[1], -7232257);
    TextDrawBackgroundColor(PaycheckTD[1], 255);
    TextDrawBoxColor(PaycheckTD[1], 50);
    TextDrawUseBox(PaycheckTD[1], 1);
    TextDrawSetProportional(PaycheckTD[1], 1);
    TextDrawSetSelectable(PaycheckTD[1], 0);
}

CreatePaycheckInfoTD(playerid)
{
    InfoPaycheckTD[playerid] = CreatePlayerTextDraw(playerid, 483.000000, 9.000000, "Anda mendapatkan tunjangan sebesar $50 dari Pemerintah");
    PlayerTextDrawFont(playerid, InfoPaycheckTD[playerid], 1);
    PlayerTextDrawLetterSize(playerid, InfoPaycheckTD[playerid], 0.137499, 1.099999);
    PlayerTextDrawTextSize(playerid, InfoPaycheckTD[playerid], 617.500000, 17.000000);
    PlayerTextDrawSetOutline(playerid, InfoPaycheckTD[playerid], 0);
    PlayerTextDrawSetShadow(playerid, InfoPaycheckTD[playerid], 0);
    PlayerTextDrawAlignment(playerid, InfoPaycheckTD[playerid], 1);
    PlayerTextDrawColor(playerid, InfoPaycheckTD[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, InfoPaycheckTD[playerid], 255);
    PlayerTextDrawBoxColor(playerid, InfoPaycheckTD[playerid], -7232257);
    PlayerTextDrawUseBox(playerid, InfoPaycheckTD[playerid], 1);
    DynPlayerTextDrawSetProportional(playerid, InfoPaycheckTD[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, InfoPaycheckTD[playerid], 0);
}

HidePaycheckTD(playerid)
{
    for(new x = 0; x < 2; x++)
    {
        TextDrawHideForPlayer(playerid, PaycheckTD[x]);
    }
    PlayerTextDrawHide(playerid, InfoPaycheckTD[playerid]);
}