// new Text:td_fade;


// new IsFadeActive[MAX_PLAYERS];
// new FadingStatus[MAX_PLAYERS];

// #include <YSI_Coding\y_hooks>
// hook OnPlayerConnect(playerid) {

//     IsFadeActive[playerid] = 0;
//     FadingStatus[playerid] = 0;
//     return 1;
// }


// hook OnGameModeInit()
// {
// 	td_fade = TextDrawCreate(-20.000000, 0.000000, "_"); 
//  	TextDrawUseBox(td_fade, 1);
//  	TextDrawBoxColor(td_fade, 0x00000000);
//  	TextDrawAlignment(td_fade, 0 );
//  	TextDrawBackgroundColor(td_fade, 0x00000000);
//  	TextDrawFont(td_fade, 3);
//  	TextDrawLetterSize(td_fade, 1.000000, 52.200000);
//  	TextDrawColor(td_fade, 0x00000000);
//     return 1;
// }

// FadeIn(playerid) 
// {
// 	if(!IsFadeActive[playerid])
// 	{
// 		FadingStatus[playerid] = 10;
// 		IsFadeActive[playerid] = true;
//         PlayerPlaySound(playerid, 12201, 0, 0, 0);
// 		Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
// 	}
// }

// ptask FadeTimer[200](playerid) 
// {
//     if(!IsFadeActive[playerid]) return 0;

// 	FadingStatus[playerid] --;

// 	if(FadingStatus[playerid] > 0)
// 	{
// 		TextDrawBoxColor(td_fade, (0 << 24) | ((0 & 0xFF) << 16) | ((0 & 0xFF) << 8) | (FadingStatus[playerid] * (255 / 10)) & 0xFF);
// 		TextDrawShowForPlayer(playerid, td_fade);
// 	}
// 	else
// 	{
// 		TextDrawHideForPlayer(playerid, td_fade);

// 		FadingStatus[playerid] = 0;
// 		IsFadeActive[playerid] = false;
// 	}
//     return 1;
// }

// IsPlayerFading(playerid) 
// {
//     return IsFadeActive[playerid];
// }

// BlackScreen(playerid)
// {	
// 	IsFadeActive[playerid] = false;
// 	TextDrawHideForPlayer(playerid, td_fade);
// 	TextDrawBoxColor(td_fade, 0x00000000);
// 	TextDrawShowForPlayer(playerid, td_fade);
// 	return 1;
// }

public OnScreenColourFadeComplete(playerid) 
{
    new bool:reverse, counter;
    if (++counter == 10) 
    {
        return 1;
    }

    FadePlayerScreenColour(playerid, reverse ? 0x000000FF : 0x00000000, 1000, 50);

    reverse = !reverse;

    return 1;
} 

FadeIn(playerid)
{
    PlayerPlaySound(playerid, 12201, 0.0, 0.0, 0.0);
    SetPlayerScreenColour(playerid, 0x00000000);
    FadePlayerScreenColour(playerid, 0x000000FF, 1000, 50);
    return 1;
}