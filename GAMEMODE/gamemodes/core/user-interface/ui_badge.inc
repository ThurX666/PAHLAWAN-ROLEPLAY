new Text:BadgeTD[9];
new PlayerText:BadgePTD[MAX_PLAYERS][3];

CreateBadgeTD()
{
    BadgeTD[0] = TextDrawCreate(477.000000, 269.000000, "_");
	TextDrawFont(BadgeTD[0], 1);
	TextDrawLetterSize(BadgeTD[0], 0.600000, 11.000005);
	TextDrawTextSize(BadgeTD[0], 298.500000, 190.500000);
	TextDrawSetOutline(BadgeTD[0], 1);
	TextDrawSetShadow(BadgeTD[0], 0);
	TextDrawAlignment(BadgeTD[0], 2);
	TextDrawColor(BadgeTD[0], 35839);
	TextDrawBackgroundColor(BadgeTD[0], 255);
	TextDrawBoxColor(BadgeTD[0], 622615807);
	TextDrawUseBox(BadgeTD[0], 1);
	TextDrawSetProportional(BadgeTD[0], 1);
	TextDrawSetSelectable(BadgeTD[0], 0);

	BadgeTD[1] = TextDrawCreate(477.000000, 272.000000, "_");
	TextDrawFont(BadgeTD[1], 1);
	TextDrawLetterSize(BadgeTD[1], 0.600000, 10.300003);
	TextDrawTextSize(BadgeTD[1], 298.500000, 185.000000);
	TextDrawSetOutline(BadgeTD[1], 1);
	TextDrawSetShadow(BadgeTD[1], 0);
	TextDrawAlignment(BadgeTD[1], 2);
	TextDrawColor(BadgeTD[1], -1);
	TextDrawBackgroundColor(BadgeTD[1], 255);
	TextDrawBoxColor(BadgeTD[1], -1);
	TextDrawUseBox(BadgeTD[1], 1);
	TextDrawSetProportional(BadgeTD[1], 1);
	TextDrawSetSelectable(BadgeTD[1], 0);

	BadgeTD[2] = TextDrawCreate(477.000000, 308.000000, "_");
	TextDrawFont(BadgeTD[2], 1);
	TextDrawLetterSize(BadgeTD[2], 0.600000, 3.600001);
	TextDrawTextSize(BadgeTD[2], 298.500000, 185.000000);
	TextDrawSetOutline(BadgeTD[2], 1);
	TextDrawSetShadow(BadgeTD[2], 0);
	TextDrawAlignment(BadgeTD[2], 2);
	TextDrawColor(BadgeTD[2], -1);
	TextDrawBackgroundColor(BadgeTD[2], 255);
	TextDrawBoxColor(BadgeTD[2], 622615807);
	TextDrawUseBox(BadgeTD[2], 1);
	TextDrawSetProportional(BadgeTD[2], 1);
	TextDrawSetSelectable(BadgeTD[2], 0);

	BadgeTD[3] = TextDrawCreate(477.000000, 278.000000, "Kepolisian Pahlawan Roleplay");
	TextDrawFont(BadgeTD[3], 1);
	TextDrawLetterSize(BadgeTD[3], 0.291666, 1.300000);
	TextDrawTextSize(BadgeTD[3], 400.000000, 377.000000);
	TextDrawSetOutline(BadgeTD[3], 0);
	TextDrawSetShadow(BadgeTD[3], 0);
	TextDrawAlignment(BadgeTD[3], 2);
	TextDrawColor(BadgeTD[3], 622615807);
	TextDrawBackgroundColor(BadgeTD[3], 255);
	TextDrawBoxColor(BadgeTD[3], 50);
	TextDrawUseBox(BadgeTD[3], 0);
	TextDrawSetProportional(BadgeTD[3], 1);
	TextDrawSetSelectable(BadgeTD[3], 0);

	BadgeTD[4] = TextDrawCreate(396.000000, 295.000000, "ld_pool:ball");
	TextDrawFont(BadgeTD[4], 4);
	TextDrawLetterSize(BadgeTD[4], 0.600000, 2.000000);
	TextDrawTextSize(BadgeTD[4], 35.500000, 58.000000);
	TextDrawSetOutline(BadgeTD[4], 0);
	TextDrawSetShadow(BadgeTD[4], 0);
	TextDrawAlignment(BadgeTD[4], 1);
	TextDrawColor(BadgeTD[4], -589893633);
	TextDrawBackgroundColor(BadgeTD[4], -1);
	TextDrawBoxColor(BadgeTD[4], -206);
	TextDrawUseBox(BadgeTD[4], 1);
	TextDrawSetProportional(BadgeTD[4], 1);
	TextDrawSetSelectable(BadgeTD[4], 0);

	BadgeTD[5] = TextDrawCreate(397.600006, 328.000000, "ld_pool:ball");
	TextDrawFont(BadgeTD[5], 4);
	TextDrawLetterSize(BadgeTD[5], 0.600000, 2.000000);
	TextDrawTextSize(BadgeTD[5], 32.500000, 11.500000);
	TextDrawSetOutline(BadgeTD[5], 0);
	TextDrawSetShadow(BadgeTD[5], 0);
	TextDrawAlignment(BadgeTD[5], 1);
	TextDrawColor(BadgeTD[5], -1062438657);
	TextDrawBackgroundColor(BadgeTD[5], -1);
	TextDrawBoxColor(BadgeTD[5], -206);
	TextDrawUseBox(BadgeTD[5], 1);
	TextDrawSetProportional(BadgeTD[5], 1);
	TextDrawSetSelectable(BadgeTD[5], 0);

	BadgeTD[6] = TextDrawCreate(405.000000, 299.000000, "Preview_Model");
	TextDrawFont(BadgeTD[6], 5);
	TextDrawLetterSize(BadgeTD[6], 0.600000, 2.000000);
	TextDrawTextSize(BadgeTD[6], 17.500000, 30.000000);
	TextDrawSetOutline(BadgeTD[6], 0);
	TextDrawSetShadow(BadgeTD[6], 0);
	TextDrawAlignment(BadgeTD[6], 1);
	TextDrawColor(BadgeTD[6], -1062438657);
	TextDrawBackgroundColor(BadgeTD[6], 0);
	TextDrawBoxColor(BadgeTD[6], 255);
	TextDrawUseBox(BadgeTD[6], 0);
	TextDrawSetProportional(BadgeTD[6], 1);
	TextDrawSetSelectable(BadgeTD[6], 0);
	TextDrawSetPreviewModel(BadgeTD[6], 4002);
	TextDrawSetPreviewRot(BadgeTD[6], 20.000000, 0.000000, 0.000000, 0.440000);
	TextDrawSetPreviewVehCol(BadgeTD[6], 1, 1);

	BadgeTD[7] = TextDrawCreate(409.000000, 317.000000, "ld_drv:goboat");
	TextDrawFont(BadgeTD[7], 4);
	TextDrawLetterSize(BadgeTD[7], 0.600000, 2.000000);
	TextDrawTextSize(BadgeTD[7], 10.000000, 10.000000);
	TextDrawSetOutline(BadgeTD[7], 1);
	TextDrawSetShadow(BadgeTD[7], 0);
	TextDrawAlignment(BadgeTD[7], 1);
	TextDrawColor(BadgeTD[7], -1);
	TextDrawBackgroundColor(BadgeTD[7], 255);
	TextDrawBoxColor(BadgeTD[7], 50);
	TextDrawUseBox(BadgeTD[7], 1);
	TextDrawSetProportional(BadgeTD[7], 1);
	TextDrawSetSelectable(BadgeTD[7], 0);

	BadgeTD[8] = TextDrawCreate(496.000000, 347.000000, "'To Protect and To Serve'");
	TextDrawFont(BadgeTD[8], 0);
	TextDrawLetterSize(BadgeTD[8], 0.262499, 1.300000);
	TextDrawTextSize(BadgeTD[8], 400.000000, 377.000000);
	TextDrawSetOutline(BadgeTD[8], 0);
	TextDrawSetShadow(BadgeTD[8], 0);
	TextDrawAlignment(BadgeTD[8], 2);
	TextDrawColor(BadgeTD[8], 622615807);
	TextDrawBackgroundColor(BadgeTD[8], 255);
	TextDrawBoxColor(BadgeTD[8], 50);
	TextDrawUseBox(BadgeTD[8], 0);
	TextDrawSetProportional(BadgeTD[8], 1);
	TextDrawSetSelectable(BadgeTD[8], 0);
}

CreateBadgePTD(playerid)
{
    BadgePTD[playerid][0] = CreatePlayerTextDraw(playerid, 451.000000, 311.000000, "Uvuvwevwevwe Onyetevwevwe Osas");
	PlayerTextDrawFont(playerid, BadgePTD[playerid][0], 1);
	PlayerTextDrawLetterSize(playerid, BadgePTD[playerid][0], 0.170833, 1.000000);
	PlayerTextDrawTextSize(playerid, BadgePTD[playerid][0], 567.000000, 377.000000);
	PlayerTextDrawSetOutline(playerid, BadgePTD[playerid][0], 0);
	PlayerTextDrawSetShadow(playerid, BadgePTD[playerid][0], 0);
	PlayerTextDrawAlignment(playerid, BadgePTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, BadgePTD[playerid][0], -1);
	PlayerTextDrawBackgroundColor(playerid, BadgePTD[playerid][0], 255);
	PlayerTextDrawBoxColor(playerid, BadgePTD[playerid][0], 50);
	PlayerTextDrawUseBox(playerid, BadgePTD[playerid][0], 0);
	PlayerTextDrawSetProportional(playerid, BadgePTD[playerid][0], 1);
	PlayerTextDrawSetSelectable(playerid, BadgePTD[playerid][0], 0);

	BadgePTD[playerid][1] = CreatePlayerTextDraw(playerid, 451.000000, 325.000000, "Police Officer III+1 - 66655");
	PlayerTextDrawFont(playerid, BadgePTD[playerid][1], 1);
	PlayerTextDrawLetterSize(playerid, BadgePTD[playerid][1], 0.170833, 1.000000);
	PlayerTextDrawTextSize(playerid, BadgePTD[playerid][1], 567.000000, 377.000000);
	PlayerTextDrawSetOutline(playerid, BadgePTD[playerid][1], 0);
	PlayerTextDrawSetShadow(playerid, BadgePTD[playerid][1], 0);
	PlayerTextDrawAlignment(playerid, BadgePTD[playerid][1], 1);
	PlayerTextDrawColor(playerid, BadgePTD[playerid][1], -1);
	PlayerTextDrawBackgroundColor(playerid, BadgePTD[playerid][1], 255);
	PlayerTextDrawBoxColor(playerid, BadgePTD[playerid][1], 50);
	PlayerTextDrawUseBox(playerid, BadgePTD[playerid][1], 0);
	PlayerTextDrawSetProportional(playerid, BadgePTD[playerid][1], 1);
	PlayerTextDrawSetSelectable(playerid, BadgePTD[playerid][1], 0);

	BadgePTD[playerid][2] = CreatePlayerTextDraw(playerid, 407.000000, 329.000000, "66655");
	PlayerTextDrawFont(playerid, BadgePTD[playerid][2], 1);
	PlayerTextDrawLetterSize(playerid, BadgePTD[playerid][2], 0.141666, 0.850000);
	PlayerTextDrawTextSize(playerid, BadgePTD[playerid][2], 567.000000, 377.000000);
	PlayerTextDrawSetOutline(playerid, BadgePTD[playerid][2], 0);
	PlayerTextDrawSetShadow(playerid, BadgePTD[playerid][2], 0);
	PlayerTextDrawAlignment(playerid, BadgePTD[playerid][2], 1);
	PlayerTextDrawColor(playerid, BadgePTD[playerid][2], 255);
	PlayerTextDrawBackgroundColor(playerid, BadgePTD[playerid][2], 255);
	PlayerTextDrawBoxColor(playerid, BadgePTD[playerid][2], 50);
	PlayerTextDrawUseBox(playerid, BadgePTD[playerid][2], 0);
	PlayerTextDrawSetProportional(playerid, BadgePTD[playerid][2], 1);
	PlayerTextDrawSetSelectable(playerid, BadgePTD[playerid][2], 0);
}

ShowBadge(playerid)
{
    static string[200];
    foreach(new i : Player)
    {
        if(AccountData[i][pSpawned])
        {
            if(IsPlayerNearPlayer(playerid, i, 6.5))
            {
                for(new x; x < 9; x++)
                {
                    TextDrawShowForPlayer(i, BadgeTD[x]);
                }

				PlayerTextDrawSetString(i, BadgePTD[playerid][0], AccountData[playerid][pName]);
				format(string, sizeof(string), "%s - %d", GetRankName(playerid), AccountData[playerid][pBadge]);
    			PlayerTextDrawSetString(i, BadgePTD[playerid][1], string);
				format(string, sizeof(string), "%d", AccountData[playerid][pBadge]);
    			PlayerTextDrawSetString(i, BadgePTD[playerid][2], string);

                PlayerTextDrawShow(i, BadgePTD[playerid][0]);
                PlayerTextDrawShow(i, BadgePTD[playerid][1]);
                PlayerTextDrawShow(i, BadgePTD[playerid][2]);

                SendClientMessage(i, Y_PAHLAWAN, "<!> "WHITE"Badge telah ditampilkan, gunakan "CMDEA"'/hidebadge' "WHITE"untuk menyembunyikannya!");
            }
        }
    }
    return 1;
}

HideBadgeTD(playerid)
{
    for(new x; x < 9; x++)
    {
        TextDrawHideForPlayer(playerid, BadgeTD[x]);
    }
    PlayerTextDrawHide(playerid, BadgePTD[playerid][0]);
    PlayerTextDrawHide(playerid, BadgePTD[playerid][1]);
    PlayerTextDrawHide(playerid, BadgePTD[playerid][2]);
    return 1;
}