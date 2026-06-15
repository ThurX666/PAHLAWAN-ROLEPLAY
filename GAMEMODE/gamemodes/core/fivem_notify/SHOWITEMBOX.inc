forward HideItemBox(playerid);
public HideItemBox(playerid)
{
	if(!IndexItemBox[playerid]) return 1;
	--IndexItemBox[playerid];
	MaxPlayerItemBox[playerid]--;
	for(new i=-1;++i<10;) 
	{
		PlayerTextDrawDestroy(playerid, TextDrawItemBox[playerid][(IndexItemBox[playerid]*10)+i]);
		TextDrawItemBox[playerid][(IndexItemBox[playerid]*10)+i] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
	}
	return 1;
}

ShowItemBox(playerid, const string[], const total[], model, time)
{
	if(MaxPlayerItemBox[playerid] == 5) return 1;
	MaxPlayerItemBox[playerid]++;
	new validtime = time*1000;
	for(new x=-1; ++x < IndexItemBox[playerid];)
	{
		for(new i=-1;++i<10;) 
		{
			PlayerTextDrawDestroy(playerid, TextDrawItemBox[playerid][(x*10) + i]);
			TextDrawItemBox[playerid][(x*10) + i] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
		}
		InfoItemBox[playerid][IndexItemBox[playerid]-x] = InfoItemBox[playerid][(IndexItemBox[playerid]-x)-1];
	}
    PlayerPlaySound(playerid, SOUND_GET_ITEM, 0.0, 0.0, 0.0);
	strcopy(InfoItemBox[playerid][0][ItemBoxMessage], string);
	strcopy(InfoItemBox[playerid][0][ItemBoxJumlahMessage], total);
	InfoItemBox[playerid][0][ItemBoxIcon] = model;

	++IndexItemBox[playerid];
	new Float:new_x=0.0;
	for(new x=-1; ++x < IndexItemBox[playerid];)
	{
		CreateItemBox(playerid, x, x * 10, new_x);
		new_x += (InfoItemBox[playerid][x][ItemBoxSize]*7.25)+55.0;
	}
	SetTimerEx("HideItemBox", validtime, false, "i", playerid);
	return 1;
}

CreateItemBox(playerid, index, i, Float:new_x)
{
	new lines = InfoItemBox[playerid][index][ItemBoxSize];
	new Float:x = (lines * 10) + new_x;
	new Float:posisibaru = x-14.0;
	
	TextDrawItemBox[playerid][i] = CreatePlayerTextDraw(playerid, 1000.000000+posisibaru, 108.500000, "");
	PlayerTextDrawFont(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawLetterSize(playerid, TextDrawItemBox[playerid][i], 0.425000, 1.400000);
	PlayerTextDrawTextSize(playerid, TextDrawItemBox[playerid][i], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawSetShadow(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawAlignment(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawColor(playerid, TextDrawItemBox[playerid][i], 0x323232ff);
	PlayerTextDrawBackgroundColor(playerid, TextDrawItemBox[playerid][i], 0x323232ff);
	PlayerTextDrawBoxColor(playerid, TextDrawItemBox[playerid][i], 0x323232ff);
	PlayerTextDrawUseBox(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawSetProportional(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawSetSelectable(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawShow(playerid, TextDrawItemBox[playerid][i]);

	TextDrawItemBox[playerid][++i] = CreatePlayerTextDraw(playerid, 339.000+posisibaru, 322.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, TextDrawItemBox[playerid][i], 52.000, 68.000);
	PlayerTextDrawAlignment(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawColor(playerid, TextDrawItemBox[playerid][i], 0x00000066);
	PlayerTextDrawSetShadow(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawSetOutline(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawBackgroundColor(playerid, TextDrawItemBox[playerid][i], 0x00000066);
	PlayerTextDrawFont(playerid, TextDrawItemBox[playerid][i], 4);
	PlayerTextDrawSetProportional(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawShow(playerid, TextDrawItemBox[playerid][i]);

	TextDrawItemBox[playerid][++i] = CreatePlayerTextDraw(playerid, 343.000+posisibaru, 331.000, "_");
	PlayerTextDrawTextSize(playerid, TextDrawItemBox[playerid][i], 44.000, 49.000);
	PlayerTextDrawAlignment(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawColor(playerid, TextDrawItemBox[playerid][i], 0xffffffff);
	PlayerTextDrawSetShadow(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawSetOutline(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawBackgroundColor(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawFont(playerid, TextDrawItemBox[playerid][i], 5);
	PlayerTextDrawSetProportional(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawSetPreviewModel(playerid, TextDrawItemBox[playerid][i], InfoItemBox[playerid][index][ItemBoxIcon]);
	PlayerTextDrawSetPreviewRot(playerid, TextDrawItemBox[playerid][i], 0.000, 0.000, 0.000, 1.000);
	PlayerTextDrawSetPreviewVehCol(playerid, TextDrawItemBox[playerid][i], 0, 0);
	PlayerTextDrawShow(playerid, TextDrawItemBox[playerid][i]);

	TextDrawItemBox[playerid][++i] = CreatePlayerTextDraw(playerid, 340.000+posisibaru, 322.000, InfoItemBox[playerid][index][ItemBoxJumlahMessage]);
	PlayerTextDrawLetterSize(playerid, TextDrawItemBox[playerid][i], 0.129, 0.850);
	PlayerTextDrawAlignment(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawColor(playerid, TextDrawItemBox[playerid][i], 0xffffffe6);
	PlayerTextDrawSetShadow(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawSetOutline(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawBackgroundColor(playerid, TextDrawItemBox[playerid][i], 0xffffffe6);
	PlayerTextDrawFont(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawSetProportional(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawShow(playerid, TextDrawItemBox[playerid][i]);

	TextDrawItemBox[playerid][++i] = CreatePlayerTextDraw(playerid, 366.000+posisibaru, 374.000, InfoItemBox[playerid][index][ItemBoxMessage]);
	PlayerTextDrawLetterSize(playerid, TextDrawItemBox[playerid][i], 0.129, 0.850);
	PlayerTextDrawAlignment(playerid, TextDrawItemBox[playerid][i], 2);
	PlayerTextDrawColor(playerid, TextDrawItemBox[playerid][i], 0xffffffe6);
	PlayerTextDrawSetShadow(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawSetOutline(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawBackgroundColor(playerid, TextDrawItemBox[playerid][i], 0xffffffe6);
	PlayerTextDrawFont(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawSetProportional(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawShow(playerid, TextDrawItemBox[playerid][i]);

	TextDrawItemBox[playerid][++i] = CreatePlayerTextDraw(playerid, 339.000+posisibaru, 388.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, TextDrawItemBox[playerid][i], 52.000, 3.000);
	PlayerTextDrawAlignment(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawColor(playerid, TextDrawItemBox[playerid][i], 0xff91a4cc);
	PlayerTextDrawSetShadow(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawSetOutline(playerid, TextDrawItemBox[playerid][i], 0);
	PlayerTextDrawBackgroundColor(playerid, TextDrawItemBox[playerid][i], 0xffffffe6);
	PlayerTextDrawFont(playerid, TextDrawItemBox[playerid][i], 4);
	PlayerTextDrawSetProportional(playerid, TextDrawItemBox[playerid][i], 1);
	PlayerTextDrawShow(playerid, TextDrawItemBox[playerid][i]);
	return 1;
}
