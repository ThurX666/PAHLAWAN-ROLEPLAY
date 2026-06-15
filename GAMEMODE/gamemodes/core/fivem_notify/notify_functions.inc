#define MAX_NOTIFY  4 // maksimal jumlah notify yang ditampilkan
//#define MAX_MYTHIC_NOTIFY 6 //maksimal jumlah notify mythic yang ditampilkan

enum e_FivemNotifyDetails 
{
    fvNotifySymbol[32], 
    fvNotifyTitle[64], 
    fvNotifyMessage[320], 
    fvNotifyLines 
};
new FivemNotify[MAX_PLAYERS][MAX_NOTIFY][e_FivemNotifyDetails], 
    PlayerText:FivemNotifyTD[MAX_PLAYERS][MAX_NOTIFY * 6], 
    FivemNotifyIndex[MAX_PLAYERS];

/*
enum e_FivemMythicDetails 
{
    MythicNotifyMessage[320],
    MythicNotifyColour,
    MythicNotifyLines 
};
new MythicNotify[MAX_PLAYERS][MAX_MYTHIC_NOTIFY][e_FivemMythicDetails], 
    PlayerText:FivemMythicNotifyTD[MAX_PLAYERS][MAX_MYTHIC_NOTIFY * 2], 
    MythicNotifyIndex[MAX_PLAYERS];
*/

static const SetTDWidthChar[] = 
{
	0,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
	12,12,12,12,12,12,12,13,13,28,28,28,28,8,17,17,30,28,28,12,9,21,28,14,28,28,
	28,28,28,28,28,28,13,13,30,30,30,30,10,25,23,21,24,22,20,24,24,17,20,22,20,
	30,27,27,26,26,24,23,24,31,23,31,24,23,21,28,33,33,14,28,10,11,12,9,11,10,
	10,12,12,7,7,13,5,18,12,10,12,11,10,12,8,13,13,18,17,13,12,30,30,37,35,37,
	25,25,25,25,33,21,24,24,24,24,17,17,17,17,27,27,27,27,31,31,31,31,11,11,11,
	11,11,20,9,10,10,10,10,7,7,7,7,10,10,10,10,13,13,13,13,27,12,30
};

// Menyesuaikan panjang box dengan panjang karakter //
getSizeMessage(const string:message[], maxWidth=500) 
{
	new size = 0, lines=1, i=-1, lastPoint = 0;

	while(message[++i]) 
	{
		size += SetTDWidthChar[message[i]];

		switch(message[i]) 
		{
			case ' ': 
				lastPoint = i;

			default: 
				if(size >= maxWidth) 
					++lines, 
					size -= maxWidth, 
					size += i - lastPoint;
		}
	}
	return lines;
}

ShowFivemNotify(playerid, const string:title[], const string:message[], const string:icon[] = "hud:radar_triads", timersa = 5) 
{
    if(FivemNotifyIndex[playerid] >= MAX_NOTIFY) return 1;
    
	for(new x=-1;++x<FivemNotifyIndex[playerid];) 
    {
		for(new i=-1;++i<6;) 
		{
			PlayerTextDrawDestroy(playerid, FivemNotifyTD[playerid][(x*6) + i]);
			FivemNotifyTD[playerid][(x*6) + i] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
		}
		FivemNotify[playerid][FivemNotifyIndex[playerid]-x] = FivemNotify[playerid][(FivemNotifyIndex[playerid]-x)-1];
	}

	strmid(FivemNotify[playerid][0][fvNotifyTitle], title, 0, 64);
	strmid(FivemNotify[playerid][0][fvNotifyMessage], message, 0, 320);
	strmid(FivemNotify[playerid][0][fvNotifySymbol], icon, 0, 20);
	FivemNotify[playerid][0][fvNotifyLines] = getSizeMessage(message);

	++FivemNotifyIndex[playerid];

	new Float:static_x=0.0;
	for(new x=-1;++x<FivemNotifyIndex[playerid];) 
	{
		FivemNotifyCreateTD(playerid, x, x * 6, static_x);
		static_x += (FivemNotify[playerid][x][fvNotifyLines] * 7.5) + 25.0;
	}

	SetTimerEx("FivemNotifyDestroy", timersa*1000, false, "i", playerid);
	return 1;
}

// hancurkan notify yang ditampilkan //
forward FivemNotifyDestroy(playerid);
public FivemNotifyDestroy(playerid) 
{
	if(!FivemNotifyIndex[playerid]) return 1;

	--FivemNotifyIndex[playerid];

	for(new i=-1;++i<6;) 
	{
		PlayerTextDrawDestroy(playerid, FivemNotifyTD[playerid][(FivemNotifyIndex[playerid]*6) + i]);
		FivemNotifyTD[playerid][(FivemNotifyIndex[playerid]*6) + i] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
	}
	return 1;
}

// tampilkan notify //
FivemNotifyCreateTD(playerid, index, i, Float:static_x) 
{
	new lines = FivemNotify[playerid][index][fvNotifyLines],
		Float:x = (lines * 7.5) + static_x;

	FivemNotifyTD[playerid][i] = CreatePlayerTextDraw(playerid, 29.42, 292.73 - x, "box");
	PlayerTextDrawLetterSize(playerid, FivemNotifyTD[playerid][i], 0.0, 2.0 + (lines *0.9));
	PlayerTextDrawTextSize(playerid, FivemNotifyTD[playerid][i], 132.0, 0.0);
	PlayerTextDrawAlignment(playerid, FivemNotifyTD[playerid][i], 1);
	PlayerTextDrawColor(playerid, FivemNotifyTD[playerid][i], -1);
	PlayerTextDrawUseBox(playerid, FivemNotifyTD[playerid][i], 1);
	PlayerTextDrawBoxColor(playerid, FivemNotifyTD[playerid][i], 0xff91a459);
	PlayerTextDrawSetShadow(playerid, FivemNotifyTD[playerid][i], 0);
	PlayerTextDrawSetOutline(playerid, FivemNotifyTD[playerid][i], 0);
	PlayerTextDrawBackgroundColor(playerid, FivemNotifyTD[playerid][i], 255);
	PlayerTextDrawFont(playerid, FivemNotifyTD[playerid][i], 1);
	PlayerTextDrawSetProportional(playerid, FivemNotifyTD[playerid][i], 1); 
	PlayerTextDrawSetShadow(playerid, FivemNotifyTD[playerid][i], 0);
	PlayerTextDrawShow(playerid, FivemNotifyTD[playerid][i]);

	FivemNotifyTD[playerid][++i] = CreatePlayerTextDraw(playerid, 27.84, 298.5 - x, "particle:lamp_shad_64");
	PlayerTextDrawLetterSize(playerid, FivemNotifyTD[playerid][i], 0.0, 0.0);
	PlayerTextDrawTextSize(playerid, FivemNotifyTD[playerid][i], 109.0, 15.0 + (lines * 7.2));
	PlayerTextDrawAlignment(playerid, FivemNotifyTD[playerid][i], 1);
	PlayerTextDrawColor(playerid, FivemNotifyTD[playerid][i], -16777184);
	PlayerTextDrawSetShadow(playerid, FivemNotifyTD[playerid][i], 0);
	PlayerTextDrawSetOutline(playerid, FivemNotifyTD[playerid][i], 0);
	PlayerTextDrawBackgroundColor(playerid, FivemNotifyTD[playerid][i], 255);
	PlayerTextDrawFont(playerid, FivemNotifyTD[playerid][i], 4);
	PlayerTextDrawSetProportional(playerid, FivemNotifyTD[playerid][i], 0);
	PlayerTextDrawSetShadow(playerid, FivemNotifyTD[playerid][i], 0);
	PlayerTextDrawShow(playerid, FivemNotifyTD[playerid][i]);

	FivemNotifyTD[playerid][++i] = CreatePlayerTextDraw(playerid, 29.34, 292.7 - x, "box");
	PlayerTextDrawLetterSize(playerid, FivemNotifyTD[playerid][i], 0.0, 1.428);
	PlayerTextDrawTextSize(playerid, FivemNotifyTD[playerid][i], 44.0, 0.0);
	PlayerTextDrawAlignment(playerid, FivemNotifyTD[playerid][i], 1);
	PlayerTextDrawColor(playerid, FivemNotifyTD[playerid][i], -1);
	PlayerTextDrawUseBox(playerid, FivemNotifyTD[playerid][i], 1);
	PlayerTextDrawBoxColor(playerid, FivemNotifyTD[playerid][i], 0xff91a48c);
	PlayerTextDrawSetShadow(playerid, FivemNotifyTD[playerid][i], 0);
	PlayerTextDrawSetOutline(playerid, FivemNotifyTD[playerid][i], 0);
	PlayerTextDrawBackgroundColor(playerid, FivemNotifyTD[playerid][i], 255);
	PlayerTextDrawFont(playerid, FivemNotifyTD[playerid][i], 1);
	PlayerTextDrawSetProportional(playerid, FivemNotifyTD[playerid][i], 1);
	PlayerTextDrawSetShadow(playerid, FivemNotifyTD[playerid][i], 0);
	PlayerTextDrawShow(playerid, FivemNotifyTD[playerid][i]);

	FivemNotifyTD[playerid][++i] = CreatePlayerTextDraw(playerid, 29.69, 292.83 - x, FivemNotify[playerid][index][fvNotifySymbol]);
	PlayerTextDrawLetterSize(playerid, FivemNotifyTD[playerid][i], 0.0, 0.0);
	PlayerTextDrawTextSize(playerid, FivemNotifyTD[playerid][i], 13.0, 13.0);
	PlayerTextDrawAlignment(playerid, FivemNotifyTD[playerid][i], 1);
	PlayerTextDrawColor(playerid, FivemNotifyTD[playerid][i], -1);
	PlayerTextDrawSetShadow(playerid, FivemNotifyTD[playerid][i], 0);
	PlayerTextDrawSetOutline(playerid, FivemNotifyTD[playerid][i], 0);
	PlayerTextDrawBackgroundColor(playerid, FivemNotifyTD[playerid][i], 255);
	PlayerTextDrawFont(playerid, FivemNotifyTD[playerid][i], 4);
	PlayerTextDrawSetProportional(playerid, FivemNotifyTD[playerid][i], 0);
	PlayerTextDrawSetShadow(playerid, FivemNotifyTD[playerid][i], 0);
	PlayerTextDrawShow(playerid, FivemNotifyTD[playerid][i]);

	FivemNotifyTD[playerid][++i] = CreatePlayerTextDraw(playerid, 47.47, 291.44 - x, FivemNotify[playerid][index][fvNotifyTitle]);
	PlayerTextDrawLetterSize(playerid, FivemNotifyTD[playerid][i], 0.134, 0.861);
	PlayerTextDrawAlignment(playerid, FivemNotifyTD[playerid][i], 1);
	PlayerTextDrawColor(playerid, FivemNotifyTD[playerid][i], -1);
	PlayerTextDrawSetShadow(playerid, FivemNotifyTD[playerid][i], 0);
	PlayerTextDrawSetOutline(playerid, FivemNotifyTD[playerid][i], 0);
	PlayerTextDrawBackgroundColor(playerid, FivemNotifyTD[playerid][i], 255);
	PlayerTextDrawFont(playerid, FivemNotifyTD[playerid][i], 2);
	PlayerTextDrawSetProportional(playerid, FivemNotifyTD[playerid][i], 1);
	PlayerTextDrawSetShadow(playerid, FivemNotifyTD[playerid][i], 0);
	PlayerTextDrawShow(playerid, FivemNotifyTD[playerid][i]);

	FivemNotifyTD[playerid][++i] = CreatePlayerTextDraw(playerid, 30.61, 308.96 - x, FivemNotify[playerid][index][fvNotifyMessage]);
	PlayerTextDrawLetterSize(playerid, FivemNotifyTD[playerid][i], 0.145, 0.887);
	PlayerTextDrawTextSize(playerid, FivemNotifyTD[playerid][i], 132.0, 0.0);
	PlayerTextDrawAlignment(playerid, FivemNotifyTD[playerid][i], 1);
	PlayerTextDrawColor(playerid, FivemNotifyTD[playerid][i], -1);
	PlayerTextDrawSetShadow(playerid, FivemNotifyTD[playerid][i], 0);
	PlayerTextDrawSetOutline(playerid, FivemNotifyTD[playerid][i], 0);
	PlayerTextDrawBackgroundColor(playerid, FivemNotifyTD[playerid][i], 255);
	PlayerTextDrawFont(playerid, FivemNotifyTD[playerid][i], 1);
	PlayerTextDrawSetProportional(playerid, FivemNotifyTD[playerid][i], 1);
	PlayerTextDrawSetShadow(playerid, FivemNotifyTD[playerid][i], 0);
	PlayerTextDrawShow(playerid, FivemNotifyTD[playerid][i]);
	return 1;
}

/*
// ----------- FiveM Mythic Notification ------------------//
ShowMythicNotify(playerid, const string:message[], Colour = 0xFF0000FF) 
{
    if(MythicNotifyIndex[playerid] >= MAX_MYTHIC_NOTIFY) return 1;
    
	for(new x=-1;++x<MythicNotifyIndex[playerid];) 
    {
		for(new i=-1;++i<2;) PlayerTextDrawDestroy(playerid, FivemMythicNotifyTD[playerid][(x*2) + i]);
		MythicNotify[playerid][MythicNotifyIndex[playerid]-x] = MythicNotify[playerid][(MythicNotifyIndex[playerid]-x)-1];
	}

	strmid(MythicNotify[playerid][0][MythicNotifyMessage], message, 0, 320);
    MythicNotify[playerid][0][MythicNotifyColour] = Colour;
	MythicNotify[playerid][0][MythicNotifyLines] = getSizeMessage(message);

    SendClientMessageEx(playerid, -1, "MythicNotifyLines = %d", MythicNotify[playerid][0][MythicNotifyLines]);

	++MythicNotifyIndex[playerid];

	new Float:static_x=0.0;
	for(new x=-1;++x<MythicNotifyIndex[playerid];) 
	{
		FivemMythicNotifyCreateTD(playerid, x, x * 2, static_x);
		static_x += (MythicNotify[playerid][x][MythicNotifyLines] * 7.5) + 100.0;
        SendClientMessageEx(playerid, -1, "static_x = %f", static_x);
	}

	SetTimerEx("FivemMythicNotifyDestroy", 10000, false, "i", playerid);
	return 1;
}

forward FivemMythicNotifyDestroy(playerid);
public FivemMythicNotifyDestroy(playerid) 
{
	if(!MythicNotifyIndex[playerid]) return 1;

	--MythicNotifyIndex[playerid];

	for(new i=-1;++i<2;) 
	{
		PlayerTextDrawDestroy(playerid, FivemMythicNotifyTD[playerid][(MythicNotifyIndex[playerid]*2) + i]);
	}
	return 1;
}

FivemMythicNotifyCreateTD(playerid, index, i, Float:static_x)
{
    new lines = MythicNotify[playerid][index][MythicNotifyLines],
		Float:x = (lines * 7.5) + static_x;

    SendClientMessageEx(playerid, -1, "lines = %d", lines);
    SendClientMessageEx(playerid, -1, "float x = %f", x);

    FivemMythicNotifyTD[playerid][i] = CreatePlayerTextDraw(playerid, 563.000000 - x, 4.500000, "_");
    PlayerTextDrawLetterSize(playerid, FivemMythicNotifyTD[playerid][i], 0.600000, 1.550003);
    PlayerTextDrawTextSize(playerid, FivemMythicNotifyTD[playerid][i], 630.500000 - (lines * 0.9), 140.000000);
    PlayerTextDrawAlignment(playerid, FivemMythicNotifyTD[playerid][i], 1);
	PlayerTextDrawColor(playerid, FivemMythicNotifyTD[playerid][i], -1);
	PlayerTextDrawUseBox(playerid, FivemMythicNotifyTD[playerid][i], 1);
	PlayerTextDrawBoxColor(playerid, FivemMythicNotifyTD[playerid][i], MythicNotify[playerid][index][MythicNotifyColour]);
	PlayerTextDrawSetShadow(playerid, FivemMythicNotifyTD[playerid][i], 0);
	PlayerTextDrawSetOutline(playerid, FivemMythicNotifyTD[playerid][i], 0);
	PlayerTextDrawBackgroundColor(playerid, FivemMythicNotifyTD[playerid][i], 255);
	PlayerTextDrawFont(playerid, FivemMythicNotifyTD[playerid][i], 1);
	PlayerTextDrawSetProportional(playerid, FivemMythicNotifyTD[playerid][i], 1); 
	PlayerTextDrawSetShadow(playerid, FivemMythicNotifyTD[playerid][i], 0);
	PlayerTextDrawShow(playerid, FivemMythicNotifyTD[playerid][i]);

    FivemMythicNotifyTD[playerid][++i] = CreatePlayerTextDraw(playerid, 567.000000 - x, 6.000000, MythicNotify[playerid][index][MythicNotifyMessage]);
    PlayerTextDrawFont(playerid, FivemMythicNotifyTD[playerid][i], 1);
    PlayerTextDrawLetterSize(playerid, FivemMythicNotifyTD[playerid][i], 0.183333, 1.150000);
    PlayerTextDrawTextSize(playerid, FivemMythicNotifyTD[playerid][i], 634.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, FivemMythicNotifyTD[playerid][i], 0);
    PlayerTextDrawSetShadow(playerid, FivemMythicNotifyTD[playerid][i], 0);
    PlayerTextDrawAlignment(playerid, FivemMythicNotifyTD[playerid][i], 1);
    PlayerTextDrawColor(playerid, FivemMythicNotifyTD[playerid][i], -1);
    PlayerTextDrawBackgroundColor(playerid, FivemMythicNotifyTD[playerid][i], 255);
    PlayerTextDrawBoxColor(playerid, FivemMythicNotifyTD[playerid][i], 50);
    PlayerTextDrawUseBox(playerid, FivemMythicNotifyTD[playerid][i], 0);
    PlayerTextDrawSetProportional(playerid, FivemMythicNotifyTD[playerid][i], 1);
    PlayerTextDrawSetSelectable(playerid, FivemMythicNotifyTD[playerid][i], 0);
    PlayerTextDrawShow(playerid, FivemMythicNotifyTD[playerid][i]);
    return 1;
}

YCMD:test(playerid, params[], help)
{
    ShowMythicNotify(playerid, "Sudah dirampok bang", 0xFF0000FF); 
    return 1;
}

YCMD:test2(playerid, params[], help)
{
    ShowMythicNotify(playerid, "bang", 0x0096FFFF); 
}

YCMD:test3(playerid, params[], help)
{
    ShowMythicNotify(playerid, "Andrew Mississippi telah menjual kendaraan Yosemite nya kepada Sultan Arifanto", 0x00A36CFF); 
}*/