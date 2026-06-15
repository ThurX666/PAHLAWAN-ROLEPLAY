new Text:NYCounter[3];

CreateNYCounterTD()
{
    NYCounter[0] = TextDrawCreate(326.000000, 423.000000, "_");
	TextDrawFont(NYCounter[0], 1);
	TextDrawLetterSize(NYCounter[0], 0.220833, 1.450000);
	TextDrawTextSize(NYCounter[0], 465.000000, 252.000000);
	TextDrawSetOutline(NYCounter[0], 1);
	TextDrawSetShadow(NYCounter[0], 0);
	TextDrawAlignment(NYCounter[0], 2);
	TextDrawColor(NYCounter[0], -1);
	TextDrawBackgroundColor(NYCounter[0], 255);
	TextDrawBoxColor(NYCounter[0], 50);
	TextDrawUseBox(NYCounter[0], 0);
	TextDrawSetProportional(NYCounter[0], 1);
	TextDrawSetSelectable(NYCounter[0], 0);

	NYCounter[1] = TextDrawCreate(394.000000, 1.500000, "usebox");
	TextDrawLetterSize(NYCounter[1], 0.000000, 5.158888);
	TextDrawTextSize(NYCounter[1], 242.000000, 0.000000);
	TextDrawAlignment(NYCounter[1], 1);
	TextDrawColor(NYCounter[1], 0);
	TextDrawUseBox(NYCounter[1], true);
	TextDrawBoxColor(NYCounter[1], 102);
	TextDrawSetShadow(NYCounter[1], 0);
	TextDrawSetOutline(NYCounter[1], 0);
	TextDrawFont(NYCounter[1], 0);
    
    NYCounter[2] = TextDrawCreate(326.000000, 423.000000, "~>~ HAPPY NEW YEAR ~<~~n~~y~2025!");
	TextDrawFont(NYCounter[2], 1);
	TextDrawLetterSize(NYCounter[2], 0.220833, 1.450000);
	TextDrawTextSize(NYCounter[2], 465.000000, 252.000000);
	TextDrawSetOutline(NYCounter[2], 1);
	TextDrawSetShadow(NYCounter[2], 0);
	TextDrawAlignment(NYCounter[2], 2);
	TextDrawColor(NYCounter[2], -1);
	TextDrawBackgroundColor(NYCounter[2], 255);
	TextDrawBoxColor(NYCounter[2], 50);
	TextDrawUseBox(NYCounter[2], 0);
	TextDrawSetProportional(NYCounter[2], 1);
	TextDrawSetSelectable(NYCounter[2], 0);
}

task UpdateNYCounterTD[1000]() 
{
    new string[150];
	new year, month, day, hour, minute, second;
	getdate(year, month, day);
	gettime(hour, minute, second);
	if(month == 1 && day == 1)
	{
		TextDrawHideForAll(NYCounter[0]);
		TextDrawShowForAll(NYCounter[2]);
	}
	else
	{
		new day2;
		switch(month)
		{
			case 1, 3, 5, 7, 8, 10, 12: day2 = 31;
			case 2: 
            { 
                if(year%4 == 0) 
                { 
                    day2 = 29; 
                }
                else 
                { 
                    day2 = 28; 
                } 
            }
			case 4, 6, 9, 11: day2 = 30;
		}
		month = 12 - month;
		day = day2 - day;
		hour = 24 - hour;
		if(hour == 24)	hour = 0;
		if(minute != 0)	hour--;
		minute = 60 - minute;
		if(minute == 60)	minute = 0;
		if(second != 0)	minute--;
		second = 60 - second;
		if(second == 60)	second = 0;

		format(string, sizeof(string), "~p~%02d ~w~Bulan, ~p~%02d ~w~Hari, ~p~%02d ~w~Jam, ~p~%02d ~w~Menit, ~p~%02d ~w~Detik ~y~Menuju 2025", month, day, hour, minute, second);

		TextDrawHideForAll(NYCounter[0]);
		TextDrawSetString(NYCounter[0], string);
		TextDrawShowForAll(NYCounter[0]);
	}
    return 1;
}