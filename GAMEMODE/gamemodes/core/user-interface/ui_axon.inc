new Text:AxonTD[6],
    PlayerText:AxonTDProf[MAX_PLAYERS];
    
CreateAxonTextdraw(playerid)
{
    AxonTDProf[playerid] = CreatePlayerTextDraw(playerid, 462.000000, 21.000000, "2-ADAM-30 / Police Officer III+1 Rpwasdweaablo Escobariaa [123456]");
    PlayerTextDrawFont(playerid, AxonTDProf[playerid], 1);
    PlayerTextDrawLetterSize(playerid, AxonTDProf[playerid], 0.150000, 0.750000);
    PlayerTextDrawTextSize(playerid, AxonTDProf[playerid], 483.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, AxonTDProf[playerid], 0);
    PlayerTextDrawSetShadow(playerid, AxonTDProf[playerid], 0);
    PlayerTextDrawAlignment(playerid, AxonTDProf[playerid], 3);
    PlayerTextDrawColor(playerid, AxonTDProf[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, AxonTDProf[playerid], 1296911871);
    PlayerTextDrawBoxColor(playerid, AxonTDProf[playerid], 50);
    PlayerTextDrawUseBox(playerid, AxonTDProf[playerid], 0);
    PlayerTextDrawSetProportional(playerid, AxonTDProf[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, AxonTDProf[playerid], 0);
}

CreateAxonTimeTD()
{
    AxonTD[0] = TextDrawCreate(494.000000, 10.000000, "ld_dual:white");
    TextDrawFont(AxonTD[0], 4);
    TextDrawLetterSize(AxonTD[0], 0.600000, 2.000000);
    TextDrawTextSize(AxonTD[0], -211.500000, 36.000000);
    TextDrawSetOutline(AxonTD[0], 1);
    TextDrawSetShadow(AxonTD[0], 0);
    TextDrawAlignment(AxonTD[0], 1);
    TextDrawColor(AxonTD[0], 1296911796);
    TextDrawBackgroundColor(AxonTD[0], 255);
    TextDrawBoxColor(AxonTD[0], 50);
    TextDrawUseBox(AxonTD[0], 1);
    TextDrawSetProportional(AxonTD[0], 1);
    TextDrawSetSelectable(AxonTD[0], 0);

    AxonTD[1] = TextDrawCreate(398.000000, 13.000000, "REC      Axon Body Cam");
    TextDrawFont(AxonTD[1], 1);
    TextDrawLetterSize(AxonTD[1], 0.150000, 0.750000);
    TextDrawTextSize(AxonTD[1], 483.000000, 17.000000);
    TextDrawSetOutline(AxonTD[1], 0);
    TextDrawSetShadow(AxonTD[1], 0);
    TextDrawAlignment(AxonTD[1], 1);
    TextDrawColor(AxonTD[1], -1);
    TextDrawBackgroundColor(AxonTD[1], 1296911871);
    TextDrawBoxColor(AxonTD[1], 50);
    TextDrawUseBox(AxonTD[1], 0);
    TextDrawSetProportional(AxonTD[1], 1);
    TextDrawSetSelectable(AxonTD[1], 0);

    AxonTD[2] = TextDrawCreate(459.000000, 28.000000, "Kepolisian Pahlawan Roleplay");
    TextDrawFont(AxonTD[2], 1);
    TextDrawLetterSize(AxonTD[2], 0.150000, 0.750000);
    TextDrawTextSize(AxonTD[2], 483.000000, 17.000000);
    TextDrawSetOutline(AxonTD[2], 0);
    TextDrawSetShadow(AxonTD[2], 0);
    TextDrawAlignment(AxonTD[2], 3);
    TextDrawColor(AxonTD[2], -1);
    TextDrawBackgroundColor(AxonTD[2], 1296911871);
    TextDrawBoxColor(AxonTD[2], 50);
    TextDrawUseBox(AxonTD[2], 0);
    TextDrawSetProportional(AxonTD[2], 1);
    TextDrawSetSelectable(AxonTD[2], 0);

    AxonTD[3] = TextDrawCreate(459.000000, 36.000000, "DEC 22 2023 20 : 10 : 32 GMT+7");
    TextDrawFont(AxonTD[3], 1);
    TextDrawLetterSize(AxonTD[3], 0.150000, 0.750000);
    TextDrawTextSize(AxonTD[3], 483.000000, 17.000000);
    TextDrawSetOutline(AxonTD[3], 0);
    TextDrawSetShadow(AxonTD[3], 0);
    TextDrawAlignment(AxonTD[3], 3);
    TextDrawColor(AxonTD[3], -1);
    TextDrawBackgroundColor(AxonTD[3], 1296911871);
    TextDrawBoxColor(AxonTD[3], 50);
    TextDrawUseBox(AxonTD[3], 0);
    TextDrawSetProportional(AxonTD[3], 1);
    TextDrawSetSelectable(AxonTD[3], 0);

    AxonTD[4] = TextDrawCreate(409.000000, 13.000000, "ld_pool:ball");
    TextDrawFont(AxonTD[4], 4);
    TextDrawLetterSize(AxonTD[4], 0.600000, 2.000000);
    TextDrawTextSize(AxonTD[4], 8.000000, 8.000000);
    TextDrawSetOutline(AxonTD[4], 1);
    TextDrawSetShadow(AxonTD[4], 0);
    TextDrawAlignment(AxonTD[4], 1);
    TextDrawColor(AxonTD[4], -1962934017);
    TextDrawBackgroundColor(AxonTD[4], 255);
    TextDrawBoxColor(AxonTD[4], 50);
    TextDrawUseBox(AxonTD[4], 1);
    TextDrawSetProportional(AxonTD[4], 1);
    TextDrawSetSelectable(AxonTD[4], 0);

    AxonTD[5] = TextDrawCreate(462.000000, 13.000000, "ld_dual:rockshp");
    TextDrawFont(AxonTD[5], 4);
    TextDrawLetterSize(AxonTD[5], 0.600000, 2.000000);
    TextDrawTextSize(AxonTD[5], 33.000000, 30.000000);
    TextDrawSetOutline(AxonTD[5], 1);
    TextDrawSetShadow(AxonTD[5], 0);
    TextDrawAlignment(AxonTD[5], 1);
    TextDrawColor(AxonTD[5], -65281);
    TextDrawBackgroundColor(AxonTD[5], -65281);
    TextDrawBoxColor(AxonTD[5], 50);
    TextDrawUseBox(AxonTD[5], 1);
    TextDrawSetProportional(AxonTD[5], 1);
    TextDrawSetSelectable(AxonTD[5], 0);
}

ShowAxonTD(playerid)
{
    new axonidstr[128];
    format(axonidstr, sizeof(axonidstr), "%s / %s %s [%d]", (!isnull(LSPDPlayerCallsign[playerid])) ? (sprintf("%s", LSPDPlayerCallsign[playerid])) : ("NO CALLSIGN"), GetRankName(playerid), AccountData[playerid][pName], AccountData[playerid][pID]);
    
    new Float:abc = strlen(axonidstr) * (-211.5 + strlen(AccountData[playerid][pName]))/55;
    TextDrawTextSize(AxonTD[0], abc, 36.000000);
    //TextDrawTextSize(AxonTD[0], (float(abc) * (-3.0)) - (strlen(axonidstr) + strlen(AccountData[playerid][pName])), 36.000000);

    for(new x; x < 6; x++)
	{
        TextDrawShowForPlayer(playerid, AxonTD[x]);
	}
    PlayerTextDrawSetString(playerid, AxonTDProf[playerid], axonidstr);
    PlayerTextDrawShow(playerid, AxonTDProf[playerid]);
}

HideAxonTD(playerid)
{
    for(new x; x < 6; x++)
	{
        TextDrawHideForPlayer(playerid, AxonTD[x]);
	}
    PlayerTextDrawHide(playerid, AxonTDProf[playerid]);
}