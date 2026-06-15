new PlayerText:perampokanTD[MAX_PLAYERS];

CreateRobberyTD(playerid)
{
    perampokanTD[playerid] = CreatePlayerTextDraw(playerid, 144.000000, 205.000000, "Mohon tetap di warung selama 15 menit");
    PlayerTextDrawFont(playerid, perampokanTD[playerid], 1);
    PlayerTextDrawLetterSize(playerid, perampokanTD[playerid], 0.291666, 1.299999);
    PlayerTextDrawTextSize(playerid, perampokanTD[playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, perampokanTD[playerid], 0);
    PlayerTextDrawSetShadow(playerid, perampokanTD[playerid], 0);
    PlayerTextDrawAlignment(playerid, perampokanTD[playerid], 3);
    PlayerTextDrawColor(playerid, perampokanTD[playerid], Y_PAHLAWAN);
    PlayerTextDrawBackgroundColor(playerid, perampokanTD[playerid], 255);
    PlayerTextDrawBoxColor(playerid, perampokanTD[playerid], 50);
    PlayerTextDrawUseBox(playerid, perampokanTD[playerid], 0);
    PlayerTextDrawSetProportional(playerid, perampokanTD[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, perampokanTD[playerid], 0);
}

ShowRobberyTD(playerid)
{
    PlayerTextDrawShow(playerid, perampokanTD[playerid]);
}

HideRobberyTD(playerid)
{
    PlayerTextDrawHide(playerid, perampokanTD[playerid]);
}