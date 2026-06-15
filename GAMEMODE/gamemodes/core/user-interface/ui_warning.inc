new Text:WarningTD[8];
new PlayerText:PlayerWarnTD[MAX_PLAYERS][2];

CreateWarningTD()
{
    WarningTD[0] = TextDrawCreate(-2.000000, -5.000000, "ld_dual:white");
	TextDrawFont(WarningTD[0], 4);
	TextDrawLetterSize(WarningTD[0], 0.600000, 2.000000);
	TextDrawTextSize(WarningTD[0], 646.500000, 462.500000);
	TextDrawSetOutline(WarningTD[0], 1);
	TextDrawSetShadow(WarningTD[0], 0);
	TextDrawAlignment(WarningTD[0], 1);
	TextDrawColor(WarningTD[0], -16777016);
	TextDrawBackgroundColor(WarningTD[0], 255);
	TextDrawBoxColor(WarningTD[0], 50);
	TextDrawUseBox(WarningTD[0], 1);
	TextDrawSetProportional(WarningTD[0], 1);
	TextDrawSetSelectable(WarningTD[0], 0);

	WarningTD[1] = TextDrawCreate(255.000000, 167.000000, "ld_dual:white");
	TextDrawFont(WarningTD[1], 4);
	TextDrawLetterSize(WarningTD[1], 0.600000, 2.000000);
	TextDrawTextSize(WarningTD[1], 1.500000, 92.000000);
	TextDrawSetOutline(WarningTD[1], 1);
	TextDrawSetShadow(WarningTD[1], 0);
	TextDrawAlignment(WarningTD[1], 1);
	TextDrawColor(WarningTD[1], -1);
	TextDrawBackgroundColor(WarningTD[1], 255);
	TextDrawBoxColor(WarningTD[1], 50);
	TextDrawUseBox(WarningTD[1], 1);
	TextDrawSetProportional(WarningTD[1], 1);
	TextDrawSetSelectable(WarningTD[1], 0);

	WarningTD[2] = TextDrawCreate(314.000000, 169.000000, "WARNING!");
	TextDrawFont(WarningTD[2], 1);
	TextDrawLetterSize(WarningTD[2], 0.458333, 2.000000);
	TextDrawTextSize(WarningTD[2], 400.000000, 112.000000);
	TextDrawSetOutline(WarningTD[2], 0);
	TextDrawSetShadow(WarningTD[2], 0);
	TextDrawAlignment(WarningTD[2], 2);
	TextDrawColor(WarningTD[2], -1);
	TextDrawBackgroundColor(WarningTD[2], 255);
	TextDrawBoxColor(WarningTD[2], 50);
	TextDrawUseBox(WarningTD[2], 0);
	TextDrawSetProportional(WarningTD[2], 1);
	TextDrawSetSelectable(WarningTD[2], 0);

	WarningTD[3] = TextDrawCreate(398.000000, 167.000000, "ld_dual:white");
	TextDrawFont(WarningTD[3], 4);
	TextDrawLetterSize(WarningTD[3], 0.600000, 2.000000);
	TextDrawTextSize(WarningTD[3], 1.500000, 92.000000);
	TextDrawSetOutline(WarningTD[3], 1);
	TextDrawSetShadow(WarningTD[3], 0);
	TextDrawAlignment(WarningTD[3], 1);
	TextDrawColor(WarningTD[3], -1);
	TextDrawBackgroundColor(WarningTD[3], 255);
	TextDrawBoxColor(WarningTD[3], 50);
	TextDrawUseBox(WarningTD[3], 1);
	TextDrawSetProportional(WarningTD[3], 1);
	TextDrawSetSelectable(WarningTD[3], 0);

	WarningTD[4] = TextDrawCreate(390.000000, 190.000000, "ld_dual:white");
	TextDrawFont(WarningTD[4], 4);
	TextDrawLetterSize(WarningTD[4], 0.600000, 2.000000);
	TextDrawTextSize(WarningTD[4], -124.000000, 1.500000);
	TextDrawSetOutline(WarningTD[4], 1);
	TextDrawSetShadow(WarningTD[4], 0);
	TextDrawAlignment(WarningTD[4], 1);
	TextDrawColor(WarningTD[4], -1);
	TextDrawBackgroundColor(WarningTD[4], 255);
	TextDrawBoxColor(WarningTD[4], 50);
	TextDrawUseBox(WarningTD[4], 1);
	TextDrawSetProportional(WarningTD[4], 1);
	TextDrawSetSelectable(WarningTD[4], 0);

	WarningTD[5] = TextDrawCreate(360.000000, 168.000000, "ld_chat:badchat");
	TextDrawFont(WarningTD[5], 4);
	TextDrawLetterSize(WarningTD[5], 0.600000, 2.000000);
	TextDrawTextSize(WarningTD[5], 17.000000, 17.000000);
	TextDrawSetOutline(WarningTD[5], 1);
	TextDrawSetShadow(WarningTD[5], 0);
	TextDrawAlignment(WarningTD[5], 1);
	TextDrawColor(WarningTD[5], -1);
	TextDrawBackgroundColor(WarningTD[5], 255);
	TextDrawBoxColor(WarningTD[5], 50);
	TextDrawUseBox(WarningTD[5], 1);
	TextDrawSetProportional(WarningTD[5], 1);
	TextDrawSetSelectable(WarningTD[5], 0);

	WarningTD[6] = TextDrawCreate(399.500000, 166.000000, "ld_dual:white");
	TextDrawFont(WarningTD[6], 4);
	TextDrawLetterSize(WarningTD[6], 0.600000, 2.000000);
	TextDrawTextSize(WarningTD[6], -144.500000, 1.500000);
	TextDrawSetOutline(WarningTD[6], 1);
	TextDrawSetShadow(WarningTD[6], 0);
	TextDrawAlignment(WarningTD[6], 1);
	TextDrawColor(WarningTD[6], -1);
	TextDrawBackgroundColor(WarningTD[6], 255);
	TextDrawBoxColor(WarningTD[6], 50);
	TextDrawUseBox(WarningTD[6], 1);
	TextDrawSetProportional(WarningTD[6], 1);
	TextDrawSetSelectable(WarningTD[6], 0);

	WarningTD[7] = TextDrawCreate(399.500000, 258.000000, "ld_dual:white");
	TextDrawFont(WarningTD[7], 4);
	TextDrawLetterSize(WarningTD[7], 0.600000, 2.000000);
	TextDrawTextSize(WarningTD[7], -144.500000, 1.500000);
	TextDrawSetOutline(WarningTD[7], 1);
	TextDrawSetShadow(WarningTD[7], 0);
	TextDrawAlignment(WarningTD[7], 1);
	TextDrawColor(WarningTD[7], -1);
	TextDrawBackgroundColor(WarningTD[7], 255);
	TextDrawBoxColor(WarningTD[7], 50);
	TextDrawUseBox(WarningTD[7], 1);
	TextDrawSetProportional(WarningTD[7], 1);
	TextDrawSetSelectable(WarningTD[7], 0);
}

CreateWarningPlayerTD(playerid)
{
    PlayerWarnTD[playerid][0] = CreatePlayerTextDraw(playerid, 268.000000, 199.000000, "JANGAN RUSUH + SUSAH DIBILANGIN");
	PlayerTextDrawFont(playerid, PlayerWarnTD[playerid][0], 1);
	PlayerTextDrawLetterSize(playerid, PlayerWarnTD[playerid][0], 0.233333, 1.000000);
	PlayerTextDrawTextSize(playerid, PlayerWarnTD[playerid][0], 387.500000, 112.000000);
	PlayerTextDrawSetOutline(playerid, PlayerWarnTD[playerid][0], 0);
	PlayerTextDrawSetShadow(playerid, PlayerWarnTD[playerid][0], 0);
	PlayerTextDrawAlignment(playerid, PlayerWarnTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, PlayerWarnTD[playerid][0], -1);
	PlayerTextDrawBackgroundColor(playerid, PlayerWarnTD[playerid][0], 255);
	PlayerTextDrawBoxColor(playerid, PlayerWarnTD[playerid][0], 50);
	PlayerTextDrawUseBox(playerid, PlayerWarnTD[playerid][0], 0);
	PlayerTextDrawSetProportional(playerid, PlayerWarnTD[playerid][0], 1);
	PlayerTextDrawSetSelectable(playerid, PlayerWarnTD[playerid][0], 0);

	PlayerWarnTD[playerid][1] = CreatePlayerTextDraw(playerid, 352.000000, 236.000000, "Warned by: {DA9100}Pahlawan Roleplay "WHITE"- BangJamex");
	PlayerTextDrawFont(playerid, PlayerWarnTD[playerid][1], 1);
	PlayerTextDrawLetterSize(playerid, PlayerWarnTD[playerid][1], 0.133333, 0.900000);
	PlayerTextDrawTextSize(playerid, PlayerWarnTD[playerid][1], 387.500000, 86.500000);
	PlayerTextDrawSetOutline(playerid, PlayerWarnTD[playerid][1], 0);
	PlayerTextDrawSetShadow(playerid, PlayerWarnTD[playerid][1], 0);
	PlayerTextDrawAlignment(playerid, PlayerWarnTD[playerid][1], 2);
	PlayerTextDrawColor(playerid, PlayerWarnTD[playerid][1], -1);
	PlayerTextDrawBackgroundColor(playerid, PlayerWarnTD[playerid][1], 255);
	PlayerTextDrawBoxColor(playerid, PlayerWarnTD[playerid][1], 50);
	PlayerTextDrawUseBox(playerid, PlayerWarnTD[playerid][1], 0);
	PlayerTextDrawSetProportional(playerid, PlayerWarnTD[playerid][1], 1);
	PlayerTextDrawSetSelectable(playerid, PlayerWarnTD[playerid][1], 0);
}

forward HideWarningTD(playerid);
public HideWarningTD(playerid)
{
    if (!AccountData[playerid][pShowWarnTD])
	    return 0;

	AccountData[playerid][pShowWarnTD] = false;

    for(new x; x < 8; x++)
    {
        TextDrawHideForPlayer(playerid, WarningTD[x]);
    }

    PlayerTextDrawHide(playerid, PlayerWarnTD[playerid][0]);
    PlayerTextDrawHide(playerid, PlayerWarnTD[playerid][1]);

    ShowHBETD(playerid);
    ShowServerNameTD(playerid);

    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
        ShowSpeedoTD(playerid);
    return 1;
}

ShowWarningTD(playerid, const aname[], const text[])
{
    if(AccountData[playerid][pShowWarnTD]) 
    {
	    for(new x; x < 8; x++)
        {
            TextDrawHideForPlayer(playerid, WarningTD[x]);
        }

        PlayerTextDrawHide(playerid, PlayerWarnTD[playerid][0]);
        PlayerTextDrawHide(playerid, PlayerWarnTD[playerid][1]);

	    KillTimer(AccountData[playerid][pWarnTDTimer]);
        AccountData[playerid][pWarnTDTimer] = -1;

        ShowHBETD(playerid);
        ShowServerNameTD(playerid);

        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
            ShowSpeedoTD(playerid);
	}

    HideHBETD(playerid);
    HideServerNameTD(playerid);
    HideSpeedoTD(playerid);

    PlayerTextDrawSetString(playerid, PlayerWarnTD[playerid][0], text);
    PlayerTextDrawSetString(playerid, PlayerWarnTD[playerid][1], sprintf("Warned by: %s", aname));

    for(new x; x < 8; x++)
    {
        TextDrawShowForPlayer(playerid, WarningTD[x]);
    }

    PlayerTextDrawShow(playerid, PlayerWarnTD[playerid][0]);
    PlayerTextDrawShow(playerid, PlayerWarnTD[playerid][1]);

    AccountData[playerid][pShowWarnTD] = true;
	AccountData[playerid][pWarnTDTimer] = SetTimerEx("HideWarningTD", 7500, false, "d", playerid);
}

ShowKickTD(playerid, const aname[], const text[])
{
    if(AccountData[playerid][pShowWarnTD]) 
    {
	    for(new x; x < 8; x++)
        {
            TextDrawHideForPlayer(playerid, WarningTD[x]);
        }

        PlayerTextDrawHide(playerid, PlayerWarnTD[playerid][0]);
        PlayerTextDrawHide(playerid, PlayerWarnTD[playerid][1]);

	    KillTimer(AccountData[playerid][pWarnTDTimer]);
        AccountData[playerid][pWarnTDTimer] = -1;

        ShowHBETD(playerid);
        ShowServerNameTD(playerid);

        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
            ShowSpeedoTD(playerid);
	}

    HideHBETD(playerid);
    HideServerNameTD(playerid);
    HideSpeedoTD(playerid);

    PlayerTextDrawSetString(playerid, PlayerWarnTD[playerid][0], text);
    PlayerTextDrawSetString(playerid, PlayerWarnTD[playerid][1], sprintf("Kicked by: %s", aname));

    for(new x; x < 8; x++)
    {
        TextDrawShowForPlayer(playerid, WarningTD[x]);
    }

    PlayerTextDrawShow(playerid, PlayerWarnTD[playerid][0]);
    PlayerTextDrawShow(playerid, PlayerWarnTD[playerid][1]);
}