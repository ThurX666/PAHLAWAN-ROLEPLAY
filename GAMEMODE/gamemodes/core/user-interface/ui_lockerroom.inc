new Text:LockerRoomTD[3];

CreateLockerRoomTD()
{
    LockerRoomTD[0] = TextDrawCreate(163.000000, 189.000000, "SERAGAM");
    TextDrawFont(LockerRoomTD[0], 1);
    TextDrawLetterSize(LockerRoomTD[0], 0.262500, 1.850000);
    TextDrawTextSize(LockerRoomTD[0], 400.000000, 81.000000);
    TextDrawSetOutline(LockerRoomTD[0], 1);
    TextDrawSetShadow(LockerRoomTD[0], 0);
    TextDrawAlignment(LockerRoomTD[0], 2);
    TextDrawColor(LockerRoomTD[0], 255);
    TextDrawBackgroundColor(LockerRoomTD[0], -1);
    TextDrawBoxColor(LockerRoomTD[0], -7232257);
    TextDrawUseBox(LockerRoomTD[0], 1);
    TextDrawSetProportional(LockerRoomTD[0], 1);
    TextDrawSetSelectable(LockerRoomTD[0], 0);

    LockerRoomTD[1] = TextDrawCreate(123.000000, 216.000000, "BAJU KERJA");
    TextDrawFont(LockerRoomTD[1], 1);
    TextDrawLetterSize(LockerRoomTD[1], 0.300000, 1.500000);
    TextDrawTextSize(LockerRoomTD[1], 204.000000, 10.000000);
    TextDrawSetOutline(LockerRoomTD[1], 1);
    TextDrawSetShadow(LockerRoomTD[1], 0);
    TextDrawAlignment(LockerRoomTD[1], 1);
    TextDrawColor(LockerRoomTD[1], -7232257);
    TextDrawBackgroundColor(LockerRoomTD[1], 255);
    TextDrawBoxColor(LockerRoomTD[1], 255);
    TextDrawUseBox(LockerRoomTD[1], 1);
    TextDrawSetProportional(LockerRoomTD[1], 1);
    TextDrawSetSelectable(LockerRoomTD[1], 1);

    LockerRoomTD[2] = TextDrawCreate(123.000000, 236.000000, "BAJU WARGA");
    TextDrawFont(LockerRoomTD[2], 1);
    TextDrawLetterSize(LockerRoomTD[2], 0.300000, 1.500000);
    TextDrawTextSize(LockerRoomTD[2], 204.000000, 10.000000);
    TextDrawSetOutline(LockerRoomTD[2], 1);
    TextDrawSetShadow(LockerRoomTD[2], 0);
    TextDrawAlignment(LockerRoomTD[2], 1);
    TextDrawColor(LockerRoomTD[2], -7232257);
    TextDrawBackgroundColor(LockerRoomTD[2], 255);
    TextDrawBoxColor(LockerRoomTD[2], 255);
    TextDrawUseBox(LockerRoomTD[2], 1);
    TextDrawSetProportional(LockerRoomTD[2], 1);
    TextDrawSetSelectable(LockerRoomTD[2], 1);
}

ShowLockerTD(playerid)
{
    for(new x=0; x < 3; x++)
    {
        TextDrawShowForPlayer(playerid, LockerRoomTD[x]);
    }
    SelectTextDraw(playerid, 0xff91a4cc);
}

HideLockerTD(playerid)
{
    for(new x=0; x < 3; x++)
    {
        TextDrawHideForPlayer(playerid, LockerRoomTD[x]);
    }
    CancelSelectTextDraw(playerid);
}