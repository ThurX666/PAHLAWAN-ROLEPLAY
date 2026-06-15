new Text:ServerClockTD[2];

CreateServerNameTD()
{
	ServerClockTD[0] = TextDrawCreate(577.000000, 8.000000, "30 Desember 2025");
	TextDrawFont(ServerClockTD[0], 1);
	TextDrawLetterSize(ServerClockTD[0], 0.266665, 1.299998);
	TextDrawTextSize(ServerClockTD[0], 400.000000, 102.000000);
	TextDrawSetOutline(ServerClockTD[0], 1);
	TextDrawSetShadow(ServerClockTD[0], 0);
	TextDrawAlignment(ServerClockTD[0], 2);
	TextDrawColor(ServerClockTD[0], -1);
	TextDrawBackgroundColor(ServerClockTD[0], 255);
	TextDrawBoxColor(ServerClockTD[0], 50);
	TextDrawUseBox(ServerClockTD[0], 0);
	TextDrawSetProportional(ServerClockTD[0], 1);
	TextDrawSetSelectable(ServerClockTD[0], 0);

	ServerClockTD[1] = TextDrawCreate(579.000000, 20.000000, "23:59:54");
	TextDrawFont(ServerClockTD[1], 1);
	TextDrawLetterSize(ServerClockTD[1], 0.354166, 1.799998);
	TextDrawTextSize(ServerClockTD[1], 400.000000, 72.000000);
	TextDrawSetOutline(ServerClockTD[1], 1);
	TextDrawSetShadow(ServerClockTD[1], 0);
	TextDrawAlignment(ServerClockTD[1], 2);
	TextDrawColor(ServerClockTD[1], -1);
	TextDrawBackgroundColor(ServerClockTD[1], 255);
	TextDrawBoxColor(ServerClockTD[1], 50);
	TextDrawUseBox(ServerClockTD[1], 0);
	TextDrawSetProportional(ServerClockTD[1], 1);
	TextDrawSetSelectable(ServerClockTD[1], 0);
}

ShowServerNameTD(playerid)
{
	for(new x = 19; x < 29; x++)
    {
    	PlayerTextDrawShow(playerid, PHBE[playerid][x]);
	}
}

HideServerNameTD(playerid)
{
    for(new x = 19; x < 29; x++)
    {
    	PlayerTextDrawHide(playerid, PHBE[playerid][x]);
	}
}

ShowClockTD(playerid)
{
	TextDrawShowForPlayer(playerid, ServerClockTD[0]);
	TextDrawShowForPlayer(playerid, ServerClockTD[1]);
}