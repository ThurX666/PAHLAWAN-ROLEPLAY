new Text:PINGSANTD[8],
    PlayerText:HABISDARAHTD[MAX_PLAYERS];

CreateKnockTextdraw()    
{
    PINGSANTD[0] = TextDrawCreate(37.000000, 1.000000, "_");
    TextDrawFont(PINGSANTD[0], 0);
    TextDrawLetterSize(PINGSANTD[0], 0.600000, 50.250007);
    TextDrawTextSize(PINGSANTD[0], 298.500000, 1209.500000);
    TextDrawSetOutline(PINGSANTD[0], 1);
    TextDrawSetShadow(PINGSANTD[0], 0);
    TextDrawAlignment(PINGSANTD[0], 2);
    TextDrawColor(PINGSANTD[0], -1);
    TextDrawBackgroundColor(PINGSANTD[0], 255);
    TextDrawBoxColor(PINGSANTD[0], 1296911751);
    TextDrawUseBox(PINGSANTD[0], 1);
    TextDrawSetProportional(PINGSANTD[0], 1);
    TextDrawSetSelectable(PINGSANTD[0], 0);

    PINGSANTD[1] = TextDrawCreate(242.000000, 341.000000, "Tekan ~b~[N]~w~");
    TextDrawFont(PINGSANTD[1], 1);
    TextDrawLetterSize(PINGSANTD[1], 0.258333, 1.200000);
    TextDrawTextSize(PINGSANTD[1], 400.000000, 17.000000);
    TextDrawSetOutline(PINGSANTD[1], 1);
    TextDrawSetShadow(PINGSANTD[1], 0);
    TextDrawAlignment(PINGSANTD[1], 1);
    TextDrawColor(PINGSANTD[1], -1);
    TextDrawBackgroundColor(PINGSANTD[1], 255);
    TextDrawBoxColor(PINGSANTD[1], 50);
    TextDrawUseBox(PINGSANTD[1], 0);
    TextDrawSetProportional(PINGSANTD[1], 1);
    TextDrawSetSelectable(PINGSANTD[1], 0);

    PINGSANTD[2] = TextDrawCreate(291.000000, 341.000000, "untuk mengirim sinyal");
    TextDrawFont(PINGSANTD[2], 1);
    TextDrawLetterSize(PINGSANTD[2], 0.258333, 1.200000);
    TextDrawTextSize(PINGSANTD[2], 400.000000, 17.000000);
    TextDrawSetOutline(PINGSANTD[2], 1);
    TextDrawSetShadow(PINGSANTD[2], 0);
    TextDrawAlignment(PINGSANTD[2], 1);
    TextDrawColor(PINGSANTD[2], -1);
    TextDrawBackgroundColor(PINGSANTD[2], 255);
    TextDrawBoxColor(PINGSANTD[2], 50);
    TextDrawUseBox(PINGSANTD[2], 0);
    TextDrawSetProportional(PINGSANTD[2], 1);
    TextDrawSetSelectable(PINGSANTD[2], 0);

    PINGSANTD[3] = TextDrawCreate(184.000000, 354.000000, "Tekan ~b~[H]~w~");
    TextDrawFont(PINGSANTD[3], 1);
    TextDrawLetterSize(PINGSANTD[3], 0.258333, 1.200000);
    TextDrawTextSize(PINGSANTD[3], 400.000000, 17.000000);
    TextDrawSetOutline(PINGSANTD[3], 1);
    TextDrawSetShadow(PINGSANTD[3], 0);
    TextDrawAlignment(PINGSANTD[3], 1);
    TextDrawColor(PINGSANTD[3], -1);
    TextDrawBackgroundColor(PINGSANTD[3], 255);
    TextDrawBoxColor(PINGSANTD[3], 50);
    TextDrawUseBox(PINGSANTD[3], 0);
    TextDrawSetProportional(PINGSANTD[3], 1);
    TextDrawSetSelectable(PINGSANTD[3], 0);

    PINGSANTD[4] = TextDrawCreate(232.000000, 354.000000, "jika tidak terlihat ~b~|");
    TextDrawFont(PINGSANTD[4], 1);
    TextDrawLetterSize(PINGSANTD[4], 0.258333, 1.200000);
    TextDrawTextSize(PINGSANTD[4], 400.000000, 17.000000);
    TextDrawSetOutline(PINGSANTD[4], 1);
    TextDrawSetShadow(PINGSANTD[4], 0);
    TextDrawAlignment(PINGSANTD[4], 1);
    TextDrawColor(PINGSANTD[4], -1);
    TextDrawBackgroundColor(PINGSANTD[4], 255);
    TextDrawBoxColor(PINGSANTD[4], 50);
    TextDrawUseBox(PINGSANTD[4], 0);
    TextDrawSetProportional(PINGSANTD[4], 1);
    TextDrawSetSelectable(PINGSANTD[4], 0);

    PINGSANTD[5] = TextDrawCreate(321.000000, 354.000000, "Tekan ~b~[Y]~w~");
    TextDrawFont(PINGSANTD[5], 1);
    TextDrawLetterSize(PINGSANTD[5], 0.258333, 1.200000);
    TextDrawTextSize(PINGSANTD[5], 400.000000, 17.000000);
    TextDrawSetOutline(PINGSANTD[5], 1);
    TextDrawSetShadow(PINGSANTD[5], 0);
    TextDrawAlignment(PINGSANTD[5], 1);
    TextDrawColor(PINGSANTD[5], -1);
    TextDrawBackgroundColor(PINGSANTD[5], 255);
    TextDrawBoxColor(PINGSANTD[5], 50);
    TextDrawUseBox(PINGSANTD[5], 0);
    TextDrawSetProportional(PINGSANTD[5], 1);
    TextDrawSetSelectable(PINGSANTD[5], 0);

    PINGSANTD[6] = TextDrawCreate(432.000000, 354.000000, "untuk respawn");
    TextDrawFont(PINGSANTD[6], 1);
    TextDrawLetterSize(PINGSANTD[6], 0.258333, 1.200000);
    TextDrawTextSize(PINGSANTD[6], 400.000000, 17.000000);
    TextDrawSetOutline(PINGSANTD[6], 1);
    TextDrawSetShadow(PINGSANTD[6], 0);
    TextDrawAlignment(PINGSANTD[6], 3);
    TextDrawColor(PINGSANTD[6], -1);
    TextDrawBackgroundColor(PINGSANTD[6], 255);
    TextDrawBoxColor(PINGSANTD[6], 50);
    TextDrawUseBox(PINGSANTD[6], 0);
    TextDrawSetProportional(PINGSANTD[6], 1);
    TextDrawSetSelectable(PINGSANTD[6], 0);

    PINGSANTD[7] = TextDrawCreate(172.000000, 367.000000, "Kamu akan kehabisan darah dalam waktu");
    TextDrawFont(PINGSANTD[7], 1);
    TextDrawLetterSize(PINGSANTD[7], 0.258333, 1.200000);
    TextDrawTextSize(PINGSANTD[7], 400.000000, 17.000000);
    TextDrawSetOutline(PINGSANTD[7], 1);
    TextDrawSetShadow(PINGSANTD[7], 0);
    TextDrawAlignment(PINGSANTD[7], 1);
    TextDrawColor(PINGSANTD[7], -1);
    TextDrawBackgroundColor(PINGSANTD[7], 255);
    TextDrawBoxColor(PINGSANTD[7], 50);
    TextDrawUseBox(PINGSANTD[7], 0);
    TextDrawSetProportional(PINGSANTD[7], 1);
    TextDrawSetSelectable(PINGSANTD[7], 0);
}

CreateKnockPlayerTD(playerid)
{
    HABISDARAHTD[playerid] = CreatePlayerTextDraw(playerid, 443.000000, 367.000000, "~b~19 menit 58 detik");
    PlayerTextDrawFont(playerid, HABISDARAHTD[playerid], 1);
    PlayerTextDrawLetterSize(playerid, HABISDARAHTD[playerid], 0.258333, 1.200000);
    PlayerTextDrawTextSize(playerid, HABISDARAHTD[playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, HABISDARAHTD[playerid], 1);
    PlayerTextDrawSetShadow(playerid, HABISDARAHTD[playerid], 0);
    PlayerTextDrawAlignment(playerid, HABISDARAHTD[playerid], 3);
    PlayerTextDrawColor(playerid, HABISDARAHTD[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, HABISDARAHTD[playerid], 255);
    PlayerTextDrawBoxColor(playerid, HABISDARAHTD[playerid], 50);
    PlayerTextDrawUseBox(playerid, HABISDARAHTD[playerid], 0);
    PlayerTextDrawSetProportional(playerid, HABISDARAHTD[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, HABISDARAHTD[playerid], 0);
}

ShowKnockTD(playerid)
{
    for(new x; x < 8; x++)
    {
        TextDrawShowForPlayer(playerid, PINGSANTD[x]);
    }
    PlayerTextDrawShow(playerid, HABISDARAHTD[playerid]);
}

HideKnockTD(playerid)
{
    for(new x; x < 8; x++)
    {
        TextDrawHideForPlayer(playerid, PINGSANTD[x]);
    }
    PlayerTextDrawHide(playerid, HABISDARAHTD[playerid]);
}