new Text:RadioVoiceTD[10],
    PlayerText:RadioVoiceFreqTD[MAX_PLAYERS];
    //PlayerText:RadioVoiceInfoTD[MAX_PLAYERS];

CreateRadioVoiceTD()
{
    RadioVoiceTD[0] = TextDrawCreate(463.000000, 381.000000, "_");
    TextDrawFont(RadioVoiceTD[0], true);
    TextDrawLetterSize(RadioVoiceTD[0], 0.600000, 12.600010);
    TextDrawTextSize(RadioVoiceTD[0], 298.500000, 82.500000);
    TextDrawSetOutline(RadioVoiceTD[0], true);
    TextDrawSetShadow(RadioVoiceTD[0], false);
    TextDrawAlignment(RadioVoiceTD[0], 2);
    TextDrawColor(RadioVoiceTD[0], -1);
    TextDrawBackgroundColor(RadioVoiceTD[0], 255);
    TextDrawBoxColor(RadioVoiceTD[0], 255);
    TextDrawUseBox(RadioVoiceTD[0], true);
    TextDrawSetProportional(RadioVoiceTD[0], true);
    TextDrawSetSelectable(RadioVoiceTD[0], false);

    RadioVoiceTD[1] = TextDrawCreate(463.000000, 394.000000, "_");
    TextDrawFont(RadioVoiceTD[1], true);
    TextDrawLetterSize(RadioVoiceTD[1], 0.600000, 10.300003);
    TextDrawTextSize(RadioVoiceTD[1], 298.500000, 75.000000);
    TextDrawSetOutline(RadioVoiceTD[1], true);
    TextDrawSetShadow(RadioVoiceTD[1], false);
    TextDrawAlignment(RadioVoiceTD[1], 2);
    TextDrawColor(RadioVoiceTD[1], -1);
    TextDrawBackgroundColor(RadioVoiceTD[1], 255);
    TextDrawBoxColor(RadioVoiceTD[1], -741092353);
    TextDrawUseBox(RadioVoiceTD[1], true);
    TextDrawSetProportional(RadioVoiceTD[1], true);
    TextDrawSetSelectable(RadioVoiceTD[1], false);

    RadioVoiceTD[2] = TextDrawCreate(499.000000, 330.000000, "_");
    TextDrawFont(RadioVoiceTD[2], true);
    TextDrawLetterSize(RadioVoiceTD[2], 0.600000, 5.500011);
    TextDrawTextSize(RadioVoiceTD[2], 298.500000, 6.000000);
    TextDrawSetOutline(RadioVoiceTD[2], true);
    TextDrawSetShadow(RadioVoiceTD[2], false);
    TextDrawAlignment(RadioVoiceTD[2], 2);
    TextDrawColor(RadioVoiceTD[2], -1);
    TextDrawBackgroundColor(RadioVoiceTD[2], 255);
    TextDrawBoxColor(RadioVoiceTD[2], 255);
    TextDrawUseBox(RadioVoiceTD[2], true);
    TextDrawSetProportional(RadioVoiceTD[2], true);
    TextDrawSetSelectable(RadioVoiceTD[2], false);

    RadioVoiceTD[3] = TextDrawCreate(477.000000, 368.000000, "_");
    TextDrawFont(RadioVoiceTD[3], true);
    TextDrawLetterSize(RadioVoiceTD[3], 0.600000, 2.300009);
    TextDrawTextSize(RadioVoiceTD[3], 298.500000, 15.500000);
    TextDrawSetOutline(RadioVoiceTD[3], true);
    TextDrawSetShadow(RadioVoiceTD[3], false);
    TextDrawAlignment(RadioVoiceTD[3], 2);
    TextDrawColor(RadioVoiceTD[3], -1);
    TextDrawBackgroundColor(RadioVoiceTD[3], 255);
    TextDrawBoxColor(RadioVoiceTD[3], 255);
    TextDrawUseBox(RadioVoiceTD[3], true);
    TextDrawSetProportional(RadioVoiceTD[3], true);
    TextDrawSetSelectable(RadioVoiceTD[3], false);

    RadioVoiceTD[4] = TextDrawCreate(447.000000, 381.000000, "Pahlkie");
    TextDrawFont(RadioVoiceTD[4], true);
    TextDrawLetterSize(RadioVoiceTD[4], 0.162499, 0.949999);
    TextDrawTextSize(RadioVoiceTD[4], 499.500000, 17.000000);
    TextDrawSetOutline(RadioVoiceTD[4], true);
    TextDrawSetShadow(RadioVoiceTD[4], false);
    TextDrawAlignment(RadioVoiceTD[4], true);
    TextDrawColor(RadioVoiceTD[4], -1);
    TextDrawBackgroundColor(RadioVoiceTD[4], 255);
    TextDrawBoxColor(RadioVoiceTD[4], 50);
    TextDrawUseBox(RadioVoiceTD[4], false);
    TextDrawSetProportional(RadioVoiceTD[4], true);
    TextDrawSetSelectable(RadioVoiceTD[4], false);

    RadioVoiceTD[5] = TextDrawCreate(430.000000, 398.000000, "FREQ");
    TextDrawFont(RadioVoiceTD[5], true);
    TextDrawLetterSize(RadioVoiceTD[5], 0.162499, 0.949999);
    TextDrawTextSize(RadioVoiceTD[5], 499.500000, 17.000000);
    TextDrawSetOutline(RadioVoiceTD[5], false);
    TextDrawSetShadow(RadioVoiceTD[5], false);
    TextDrawAlignment(RadioVoiceTD[5], true);
    TextDrawColor(RadioVoiceTD[5], 255);
    TextDrawBackgroundColor(RadioVoiceTD[5], 255);
    TextDrawBoxColor(RadioVoiceTD[5], 50);
    TextDrawUseBox(RadioVoiceTD[5], false);
    TextDrawSetProportional(RadioVoiceTD[5], true);
    TextDrawSetSelectable(RadioVoiceTD[5], false);

    RadioVoiceTD[6] = TextDrawCreate(463.000000, 421.000000, "_");
    TextDrawFont(RadioVoiceTD[6], true);
    TextDrawLetterSize(RadioVoiceTD[6], 0.600000, 3.500009);
    TextDrawTextSize(RadioVoiceTD[6], 298.500000, 82.500000);
    TextDrawSetOutline(RadioVoiceTD[6], true);
    TextDrawSetShadow(RadioVoiceTD[6], false);
    TextDrawAlignment(RadioVoiceTD[6], 2);
    TextDrawColor(RadioVoiceTD[6], -1);
    TextDrawBackgroundColor(RadioVoiceTD[6], 255);
    TextDrawBoxColor(RadioVoiceTD[6], 255);
    TextDrawUseBox(RadioVoiceTD[6], true);
    TextDrawSetProportional(RadioVoiceTD[6], true);
    TextDrawSetSelectable(RadioVoiceTD[6], false);

    RadioVoiceTD[7] = TextDrawCreate(477.000000, 421.000000, "SETFQ");
    TextDrawFont(RadioVoiceTD[7], 2);
    TextDrawLetterSize(RadioVoiceTD[7], 0.173997, 1.649999);
    TextDrawTextSize(RadioVoiceTD[7], 499.500000, 20.000000);
    TextDrawSetOutline(RadioVoiceTD[7], false);
    TextDrawSetShadow(RadioVoiceTD[7], false);
    TextDrawAlignment(RadioVoiceTD[7], true);
    TextDrawColor(RadioVoiceTD[7], -1);
    TextDrawBackgroundColor(RadioVoiceTD[7], 255);
    TextDrawBoxColor(RadioVoiceTD[7], 1296911871);
    TextDrawUseBox(RadioVoiceTD[7], true);
    TextDrawSetProportional(RadioVoiceTD[7], true);
    TextDrawSetSelectable(RadioVoiceTD[7], true);

    RadioVoiceTD[8] = TextDrawCreate(427.000000, 421.000000, "POWER");
    TextDrawFont(RadioVoiceTD[8], 2);
    TextDrawLetterSize(RadioVoiceTD[8], 0.174998, 1.649999);
    TextDrawTextSize(RadioVoiceTD[8], 450.500000, 20.000000);
    TextDrawSetOutline(RadioVoiceTD[8], false);
    TextDrawSetShadow(RadioVoiceTD[8], false);
    TextDrawAlignment(RadioVoiceTD[8], true);
    TextDrawColor(RadioVoiceTD[8], -1);
    TextDrawBackgroundColor(RadioVoiceTD[8], 255);
    TextDrawBoxColor(RadioVoiceTD[8], 1296911871);
    TextDrawUseBox(RadioVoiceTD[8], true);
    TextDrawSetProportional(RadioVoiceTD[8], true);
    TextDrawSetSelectable(RadioVoiceTD[8], true);

    RadioVoiceTD[9] = TextDrawCreate(457.000000, 421.000000, "TTP");
    TextDrawFont(RadioVoiceTD[9], 2);
    TextDrawLetterSize(RadioVoiceTD[9], 0.173997, 1.649999);
    TextDrawTextSize(RadioVoiceTD[9], 470.500000, 20.000000);
    TextDrawSetOutline(RadioVoiceTD[9], false);
    TextDrawSetShadow(RadioVoiceTD[9], false);
    TextDrawAlignment(RadioVoiceTD[9], true);
    TextDrawColor(RadioVoiceTD[9], -1);
    TextDrawBackgroundColor(RadioVoiceTD[9], 255);
    TextDrawBoxColor(RadioVoiceTD[9], 1296911871);
    TextDrawUseBox(RadioVoiceTD[9], true);
    TextDrawSetProportional(RadioVoiceTD[9], true);
    TextDrawSetSelectable(RadioVoiceTD[9], true);
}

// CreateVoiceInfoTD()
// {
//     VoiceInfoTD[0] = TextDrawCreate(381.000000, 438.000000, "ld_dual:white");
//     TextDrawFont(VoiceInfoTD[0], 4);
//     TextDrawLetterSize(VoiceInfoTD[0], 0.600000, 2.000000);
//     TextDrawTextSize(VoiceInfoTD[0], 4.000000, 4.000000);
//     TextDrawSetOutline(VoiceInfoTD[0], 1);
//     TextDrawSetShadow(VoiceInfoTD[0], 0);
//     TextDrawAlignment(VoiceInfoTD[0], 1);
//     TextDrawColor(VoiceInfoTD[0], -741092353);
//     TextDrawBackgroundColor(VoiceInfoTD[0], 255);
//     TextDrawBoxColor(VoiceInfoTD[0], 50);
//     TextDrawUseBox(VoiceInfoTD[0], 1);
//     TextDrawSetProportional(VoiceInfoTD[0], 1);
//     TextDrawSetSelectable(VoiceInfoTD[0], 0);

//     VoiceInfoTD[1] = TextDrawCreate(381.000000, 432.000000, "ld_dual:white");
//     TextDrawFont(VoiceInfoTD[1], 4);
//     TextDrawLetterSize(VoiceInfoTD[1], 0.600000, 2.000000);
//     TextDrawTextSize(VoiceInfoTD[1], 4.000000, 4.000000);
//     TextDrawSetOutline(VoiceInfoTD[1], 1);
//     TextDrawSetShadow(VoiceInfoTD[1], 0);
//     TextDrawAlignment(VoiceInfoTD[1], 1);
//     TextDrawColor(VoiceInfoTD[1], -741092353);
//     TextDrawBackgroundColor(VoiceInfoTD[1], 255);
//     TextDrawBoxColor(VoiceInfoTD[1], 50);
//     TextDrawUseBox(VoiceInfoTD[1], 1);
//     TextDrawSetProportional(VoiceInfoTD[1], 1);
//     TextDrawSetSelectable(VoiceInfoTD[1], 0);

//     VoiceInfoTD[2] = TextDrawCreate(381.000000, 426.000000, "ld_dual:white");
//     TextDrawFont(VoiceInfoTD[2], 4);
//     TextDrawLetterSize(VoiceInfoTD[2], 0.600000, 2.000000);
//     TextDrawTextSize(VoiceInfoTD[2], 4.000000, 4.000000);
//     TextDrawSetOutline(VoiceInfoTD[2], 1);
//     TextDrawSetShadow(VoiceInfoTD[2], 0);
//     TextDrawAlignment(VoiceInfoTD[2], 1);
//     TextDrawColor(VoiceInfoTD[2], -741092353);
//     TextDrawBackgroundColor(VoiceInfoTD[2], 255);
//     TextDrawBoxColor(VoiceInfoTD[2], 50);
//     TextDrawUseBox(VoiceInfoTD[2], 1);
//     TextDrawSetProportional(VoiceInfoTD[2], 1);
//     TextDrawSetSelectable(VoiceInfoTD[2], 0);
// }

CreateRadioVoiceFreqTD(playerid)
{
    RadioVoiceFreqTD[playerid] = CreatePlayerTextDraw(playerid, 463.000000, 401.000000, "1234");
    PlayerTextDrawFont(playerid, RadioVoiceFreqTD[playerid], 3);
    PlayerTextDrawLetterSize(playerid, RadioVoiceFreqTD[playerid], 0.362500, 1.500000);
    PlayerTextDrawTextSize(playerid, RadioVoiceFreqTD[playerid], 499.500000, 41.500000);
    PlayerTextDrawSetOutline(playerid, RadioVoiceFreqTD[playerid], false);
    PlayerTextDrawSetShadow(playerid, RadioVoiceFreqTD[playerid], false);
    PlayerTextDrawAlignment(playerid, RadioVoiceFreqTD[playerid], 2);
    PlayerTextDrawColor(playerid, RadioVoiceFreqTD[playerid], 255);
    PlayerTextDrawBackgroundColor(playerid, RadioVoiceFreqTD[playerid], 255);
    PlayerTextDrawBoxColor(playerid, RadioVoiceFreqTD[playerid], 50);
    PlayerTextDrawUseBox(playerid, RadioVoiceFreqTD[playerid], false);
    PlayerTextDrawSetProportional(playerid, RadioVoiceFreqTD[playerid], true);
    PlayerTextDrawSetSelectable(playerid, RadioVoiceFreqTD[playerid], false);
}

/*CreateRadioVoiceInfoTD(playerid)
{
    RadioVoiceInfoTD[playerid] = CreatePlayerTextDraw(playerid, 583.000000, 433.000000, "VOICE: ~b~NORMAL");
    PlayerTextDrawFont(playerid, RadioVoiceInfoTD[playerid], 1);
    PlayerTextDrawLetterSize(playerid, RadioVoiceInfoTD[playerid], 0.212500, 1.049000);
    PlayerTextDrawTextSize(playerid, RadioVoiceInfoTD[playerid], 638.500000, -64.000000);
    PlayerTextDrawSetOutline(playerid, RadioVoiceInfoTD[playerid], 0);
    PlayerTextDrawSetShadow(playerid, RadioVoiceInfoTD[playerid], 0);
    PlayerTextDrawAlignment(playerid, RadioVoiceInfoTD[playerid], 1);
    PlayerTextDrawColor(playerid, RadioVoiceInfoTD[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, RadioVoiceInfoTD[playerid], 255);
    PlayerTextDrawBoxColor(playerid, RadioVoiceInfoTD[playerid], 50);
    PlayerTextDrawUseBox(playerid, RadioVoiceInfoTD[playerid], 0);
    PlayerTextDrawSetProportional(playerid, RadioVoiceInfoTD[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, RadioVoiceInfoTD[playerid], 0);
}*/

ShowRadioVoiceTD(playerid)
{
    for(new x = 0; x < 10; x++)
    {
        TextDrawShowForPlayer(playerid, RadioVoiceTD[x]);
    }
    PlayerTextDrawShow(playerid, RadioVoiceFreqTD[playerid]);
    SelectTextDraw(playerid, 0xff91a4cc);
}

HideRadioVoiceTD(playerid)
{
    for(new x = 0; x < 10; x++)
    {
        TextDrawHideForPlayer(playerid, RadioVoiceTD[x]);
    }
    PlayerTextDrawHide(playerid, RadioVoiceFreqTD[playerid]);
    CancelSelectTextDraw(playerid);

    RemovePlayerAttachedObject(playerid, 9);
    StopLoopingAnim(playerid);

    pShortcutResultShown[playerid] = false;
}