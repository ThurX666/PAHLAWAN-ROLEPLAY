new Text:MoneyCent[2];
    
CreateMoneyCentTextdraw()
{
    MoneyCent[0] = TextDrawCreate(583.000000, 72.000000, ".");
    TextDrawFont(MoneyCent[0], 3);
    TextDrawLetterSize(MoneyCent[0], 0.566667, 3.299993);
    TextDrawTextSize(MoneyCent[0], 400.000000, 17.000000);
    TextDrawSetOutline(MoneyCent[0], true);
    TextDrawSetShadow(MoneyCent[0], false);
    TextDrawAlignment(MoneyCent[0], 2);
    TextDrawColor(MoneyCent[0], 794437375);
    TextDrawBackgroundColor(MoneyCent[0], 255);
    TextDrawBoxColor(MoneyCent[0], 50);
    TextDrawUseBox(MoneyCent[0], false);
    TextDrawSetProportional(MoneyCent[0], true);
    TextDrawSetSelectable(MoneyCent[0], false);

    MoneyCent[1] = TextDrawCreate(546.000000, 72.000000, ",");
    TextDrawFont(MoneyCent[1], 3);
    TextDrawLetterSize(MoneyCent[1], 0.541665, 3.149996);
    TextDrawTextSize(MoneyCent[1], 400.000000, 17.000000);
    TextDrawSetOutline(MoneyCent[1], true);
    TextDrawSetShadow(MoneyCent[1], false);
    TextDrawAlignment(MoneyCent[1], 2);
    TextDrawColor(MoneyCent[1], 794437375);
    TextDrawBackgroundColor(MoneyCent[1], 255);
    TextDrawBoxColor(MoneyCent[1], 50);
    TextDrawUseBox(MoneyCent[1], false);
    TextDrawSetProportional(MoneyCent[1], true);
    TextDrawSetSelectable(MoneyCent[1], false);
}

ShowMoneyCentTD(playerid)
{
    for(new x=0; x < 2; x++)
	{
	    TextDrawShowForPlayer(playerid, MoneyCent[x]);
    }
}

HideMoneyCentTD(playerid)
{
    for(new x=0; x < 2; x++)
	{
	    TextDrawHideForPlayer(playerid, MoneyCent[x]);
    }
}