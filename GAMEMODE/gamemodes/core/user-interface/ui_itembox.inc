new PlayerText:ItemBoxTD[MAX_PLAYERS][4];

CreateItemBoxTextdraw(playerid)
{
    ItemBoxTD[playerid][0] = CreatePlayerTextDraw(playerid, 357.000000, 331.000000, "_");
    PlayerTextDrawFont(playerid, ItemBoxTD[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, ItemBoxTD[playerid][0], 0.612500, 1.049997);
    PlayerTextDrawTextSize(playerid, ItemBoxTD[playerid][0], 298.500000, 32.500000);
    PlayerTextDrawSetOutline(playerid, ItemBoxTD[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, ItemBoxTD[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, ItemBoxTD[playerid][0], 2);
    PlayerTextDrawColor(playerid, ItemBoxTD[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, ItemBoxTD[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, ItemBoxTD[playerid][0], -1);
    PlayerTextDrawUseBox(playerid, ItemBoxTD[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, ItemBoxTD[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, ItemBoxTD[playerid][0], 0);

    ItemBoxTD[playerid][1] = CreatePlayerTextDraw(playerid, 340.000000, 343.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, ItemBoxTD[playerid][1], 5);
    PlayerTextDrawLetterSize(playerid, ItemBoxTD[playerid][1], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, ItemBoxTD[playerid][1], 60.500000, 74.500000);
    PlayerTextDrawSetOutline(playerid, ItemBoxTD[playerid][1], 0);
    PlayerTextDrawSetShadow(playerid, ItemBoxTD[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, ItemBoxTD[playerid][1], 1);
    PlayerTextDrawColor(playerid, ItemBoxTD[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, ItemBoxTD[playerid][1], -7232412);
    PlayerTextDrawBoxColor(playerid, ItemBoxTD[playerid][1], 255);
    PlayerTextDrawUseBox(playerid, ItemBoxTD[playerid][1], 0);
    PlayerTextDrawSetProportional(playerid, ItemBoxTD[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, ItemBoxTD[playerid][1], 0);
    PlayerTextDrawSetPreviewModel(playerid, ItemBoxTD[playerid][1], 2804);
    PlayerTextDrawSetPreviewRot(playerid, ItemBoxTD[playerid][1], -35.000000, 0.000000, -20.000000, 1.159999);
    PlayerTextDrawSetPreviewVehCol(playerid, ItemBoxTD[playerid][1], 1, 1);

    ItemBoxTD[playerid][2] = CreatePlayerTextDraw(playerid, 370.000000, 419.000000, "WEED LEAFS");
    PlayerTextDrawFont(playerid, ItemBoxTD[playerid][2], 2);
    PlayerTextDrawLetterSize(playerid, ItemBoxTD[playerid][2], 0.112500, 1.000000);
    PlayerTextDrawTextSize(playerid, ItemBoxTD[playerid][2], 399.500000, 58.500000);
    PlayerTextDrawSetOutline(playerid, ItemBoxTD[playerid][2], 0);
    PlayerTextDrawSetShadow(playerid, ItemBoxTD[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, ItemBoxTD[playerid][2], 2);
    PlayerTextDrawColor(playerid, ItemBoxTD[playerid][2], 255);
    PlayerTextDrawBackgroundColor(playerid, ItemBoxTD[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, ItemBoxTD[playerid][2], -7232282);
    PlayerTextDrawUseBox(playerid, ItemBoxTD[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, ItemBoxTD[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, ItemBoxTD[playerid][2], 0);

    ItemBoxTD[playerid][3] = CreatePlayerTextDraw(playerid, 341.000000, 331.000000, "RECEIVED 100X");
    PlayerTextDrawFont(playerid, ItemBoxTD[playerid][3], 1);
    PlayerTextDrawLetterSize(playerid, ItemBoxTD[playerid][3], 0.133333, 0.900000);
    PlayerTextDrawTextSize(playerid, ItemBoxTD[playerid][3], 399.500000, 19.000000);
    PlayerTextDrawSetOutline(playerid, ItemBoxTD[playerid][3], 0);
    PlayerTextDrawSetShadow(playerid, ItemBoxTD[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, ItemBoxTD[playerid][3], 1);
    PlayerTextDrawColor(playerid, ItemBoxTD[playerid][3], 255);
    PlayerTextDrawBackgroundColor(playerid, ItemBoxTD[playerid][3], 255);
    PlayerTextDrawBoxColor(playerid, ItemBoxTD[playerid][3], 88);
    PlayerTextDrawUseBox(playerid, ItemBoxTD[playerid][3], 0);
    PlayerTextDrawSetProportional(playerid, ItemBoxTD[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, ItemBoxTD[playerid][3], 0);
}