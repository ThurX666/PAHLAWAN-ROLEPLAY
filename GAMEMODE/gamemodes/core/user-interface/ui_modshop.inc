new Text:EditVObjTD[7];
new PlayerText:EditVObjPTD[MAX_PLAYERS];

CreateModshopTD()
{
    EditVObjTD[0] = TextDrawCreate(263.000000, 406.000000, "_");
	TextDrawFont(EditVObjTD[0], 1);
	TextDrawLetterSize(EditVObjTD[0], 0.154164, 2.700001);
	TextDrawTextSize(EditVObjTD[0], 1.000000, 282.500000);
	TextDrawSetOutline(EditVObjTD[0], 1);
	TextDrawSetShadow(EditVObjTD[0], 0);
	TextDrawAlignment(EditVObjTD[0], 2);
	TextDrawColor(EditVObjTD[0], -1);
	TextDrawBackgroundColor(EditVObjTD[0], 255);
	TextDrawBoxColor(EditVObjTD[0], -741092407);
	TextDrawUseBox(EditVObjTD[0], 1);
	TextDrawSetProportional(EditVObjTD[0], 1);
	TextDrawSetSelectable(EditVObjTD[0], 0);

	EditVObjTD[1] = TextDrawCreate(263.000000, 362.000000, "_");
	TextDrawFont(EditVObjTD[1], 1);
	TextDrawLetterSize(EditVObjTD[1], 0.154164, 9.150011);
	TextDrawTextSize(EditVObjTD[1], 1.000000, 94.500000);
	TextDrawSetOutline(EditVObjTD[1], 1);
	TextDrawSetShadow(EditVObjTD[1], 0);
	TextDrawAlignment(EditVObjTD[1], 2);
	TextDrawColor(EditVObjTD[1], -1);
	TextDrawBackgroundColor(EditVObjTD[1], 255);
	TextDrawBoxColor(EditVObjTD[1], -741092407);
	TextDrawUseBox(EditVObjTD[1], 1);
	TextDrawSetProportional(EditVObjTD[1], 1);
	TextDrawSetSelectable(EditVObjTD[1], 0);

	EditVObjTD[2] = TextDrawCreate(358.000000, 408.000000, "+");
	TextDrawFont(EditVObjTD[2], 1);
	TextDrawLetterSize(EditVObjTD[2], 0.258332, 2.149998);
	TextDrawTextSize(EditVObjTD[2], 16.500000, 90.500000);
	TextDrawSetOutline(EditVObjTD[2], 0);
	TextDrawSetShadow(EditVObjTD[2], 0);
	TextDrawAlignment(EditVObjTD[2], 2);
	TextDrawColor(EditVObjTD[2], -1);
	TextDrawBackgroundColor(EditVObjTD[2], 255);
	TextDrawBoxColor(EditVObjTD[2], 1296911816);
	TextDrawUseBox(EditVObjTD[2], 1);
	TextDrawSetProportional(EditVObjTD[2], 1);
	TextDrawSetSelectable(EditVObjTD[2], 1);

	EditVObjTD[3] = TextDrawCreate(169.000000, 408.000000, "-");
	TextDrawFont(EditVObjTD[3], 1);
	TextDrawLetterSize(EditVObjTD[3], 0.258332, 2.149998);
	TextDrawTextSize(EditVObjTD[3], 16.500000, 90.500000);
	TextDrawSetOutline(EditVObjTD[3], 0);
	TextDrawSetShadow(EditVObjTD[3], 0);
	TextDrawAlignment(EditVObjTD[3], 2);
	TextDrawColor(EditVObjTD[3], -1);
	TextDrawBackgroundColor(EditVObjTD[3], 255);
	TextDrawBoxColor(EditVObjTD[3], 1296911816);
	TextDrawUseBox(EditVObjTD[3], 1);
	TextDrawSetProportional(EditVObjTD[3], 1);
	TextDrawSetSelectable(EditVObjTD[3], 1);

	EditVObjTD[4] = TextDrawCreate(263.000000, 389.000000, "SAVE");
	TextDrawFont(EditVObjTD[4], 1);
	TextDrawLetterSize(EditVObjTD[4], 0.258332, 1.750000);
	TextDrawTextSize(EditVObjTD[4], 16.500000, 90.500000);
	TextDrawSetOutline(EditVObjTD[4], 0);
	TextDrawSetShadow(EditVObjTD[4], 0);
	TextDrawAlignment(EditVObjTD[4], 2);
	TextDrawColor(EditVObjTD[4], -1);
	TextDrawBackgroundColor(EditVObjTD[4], 255);
	TextDrawBoxColor(EditVObjTD[4], 16711881);
	TextDrawUseBox(EditVObjTD[4], 1);
	TextDrawSetProportional(EditVObjTD[4], 1);
	TextDrawSetSelectable(EditVObjTD[4], 1);

	EditVObjTD[5] = TextDrawCreate(263.000000, 429.000000, "Kembali");
	TextDrawFont(EditVObjTD[5], 1);
	TextDrawLetterSize(EditVObjTD[5], 0.258332, 1.450000);
	TextDrawTextSize(EditVObjTD[5], 16.500000, 90.500000);
	TextDrawSetOutline(EditVObjTD[5], 0);
	TextDrawSetShadow(EditVObjTD[5], 0);
	TextDrawAlignment(EditVObjTD[5], 2);
	TextDrawColor(EditVObjTD[5], -1);
	TextDrawBackgroundColor(EditVObjTD[5], 255);
	TextDrawBoxColor(EditVObjTD[5], -16777015);
	TextDrawUseBox(EditVObjTD[5], 1);
	TextDrawSetProportional(EditVObjTD[5], 1);
	TextDrawSetSelectable(EditVObjTD[5], 1);

	EditVObjTD[6] = TextDrawCreate(263.000000, 366.000000, "EDITING");
	TextDrawFont(EditVObjTD[6], 1);
	TextDrawLetterSize(EditVObjTD[6], 0.258332, 1.750000);
	TextDrawTextSize(EditVObjTD[6], 16.500000, 90.500000);
	TextDrawSetOutline(EditVObjTD[6], 0);
	TextDrawSetShadow(EditVObjTD[6], 0);
	TextDrawAlignment(EditVObjTD[6], 2);
	TextDrawColor(EditVObjTD[6], -1);
	TextDrawBackgroundColor(EditVObjTD[6], 255);
	TextDrawBoxColor(EditVObjTD[6], -1378294071);
	TextDrawUseBox(EditVObjTD[6], 1);
	TextDrawSetProportional(EditVObjTD[6], 1);
	TextDrawSetSelectable(EditVObjTD[6], 1);
}

CreateModshopPlayerTD(playerid)
{
    EditVObjPTD[playerid] = CreatePlayerTextDraw(playerid, 264.000000, 409.000000, "Cordinate");
	PlayerTextDrawFont(playerid, EditVObjPTD[playerid], 1);
	PlayerTextDrawLetterSize(playerid, EditVObjPTD[playerid], 0.258332, 1.750000);
	PlayerTextDrawTextSize(playerid, EditVObjPTD[playerid], 16.500000, 92.000000);
	PlayerTextDrawSetOutline(playerid, EditVObjPTD[playerid], 0);
	PlayerTextDrawSetShadow(playerid, EditVObjPTD[playerid], 0);
	PlayerTextDrawAlignment(playerid, EditVObjPTD[playerid], 2);
	PlayerTextDrawColor(playerid, EditVObjPTD[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, EditVObjPTD[playerid], 255);
	PlayerTextDrawBoxColor(playerid, EditVObjPTD[playerid], 1296911817);
	PlayerTextDrawUseBox(playerid, EditVObjPTD[playerid], 1);
	PlayerTextDrawSetProportional(playerid, EditVObjPTD[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, EditVObjPTD[playerid], 0);
}

ShowModshopTD(playerid)
{
    for(new x; x < 7; x++)
    {
        TextDrawShowForPlayer(playerid, EditVObjTD[x]);
    }
    CreateModshopPlayerTD(playerid);
    PlayerTextDrawShow(playerid, EditVObjPTD[playerid]);
}

HideModshopTD(playerid)
{
    for(new x; x < 7; x++)
    {
        TextDrawHideForPlayer(playerid, EditVObjTD[x]);
    }
    DestroyPTextdraw(playerid, EditVObjPTD[playerid]);
	CancelSelectTextDraw(playerid);
}