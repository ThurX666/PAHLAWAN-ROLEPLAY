#include <YSI_Coding\y_hooks>
#include <td-string-width>

#define MAX_TDN 5
#define TDN_POS_X 494.0
#define TDN_POS_Y 120.5
#define TDN_FONT 1
#define TDN_LETTER_SIZE_X 0.250000
#define TDN_LETTER_SIZE_Y 1.000000
#define TDN_SIZE 112.000000
#define TDN_PROPORTIONAL 1
#define TDN_DISTANCE 20
#define TDN_MODE_DOWN
#define TDN_TIME 5000
#define TDN_TINGGI_BOX  1.7
#define MAX_TDN_TEXT 800

enum InformationTDN
{
    bool:notifyUse,
    notifyLine,
    notifyText[MAX_TDN_TEXT],
    PlayerText:notifyTextDraw,
    PlayerText:textdraw_notification[23],
    Float:notifyMinPosY,
    Float:notifyMaxPosY,
    notifyHide,
    notifymode,
    notifyTime
}
new TextDrawsNotification[MAX_PLAYERS][MAX_TDN][InformationTDN],
    notifycounter[MAX_PLAYERS];

enum
{
	NOTIFICATION_INFO,
	NOTIFICATION_ERROR,
	NOTIFICATION_SUCCESS,
	NOTIFICATION_SYNTAX,
	NOTIFICATION_WARNING,
	NOTIFICATION_MESSAGES
}

forward TimerHideTDN(playerid);
public TimerHideTDN(playerid)
{
    for(new cycle; cycle < MAX_TDN; cycle++)
    {
        if(TextDrawsNotification[playerid][cycle][notifyHide] == -1)
        {
            TextDrawsNotification[playerid][cycle][notifyUse] = false;
            if(TextDrawsNotification[playerid][cycle][notifyTextDraw] != PlayerText: INVALID_PLAYER_TEXT_DRAW)
            {
                PlayerTextDrawDestroy(playerid, TextDrawsNotification[playerid][cycle][notifyTextDraw]);
                TextDrawsNotification[playerid][cycle][notifyLine] = 0;
                TextDrawsNotification[playerid][cycle][notifyText][0] = EOS;
                TextDrawsNotification[playerid][cycle][notifyMinPosY] = 0;
                TextDrawsNotification[playerid][cycle][notifyMaxPosY] = 0;
                TextDrawsNotification[playerid][cycle][notifyTextDraw] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
                TextDrawsNotification[playerid][cycle][notifyTime] = 100;
                for(new txd; txd < 23; txd++)
                {
                    PlayerTextDrawDestroy(playerid, TextDrawsNotification[playerid][cycle][textdraw_notification][txd]);
                    TextDrawsNotification[playerid][cycle][textdraw_notification][txd] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
                }
            }
            TextDrawsNotification[playerid][cycle][notifyHide] = -1;
            UpdateTDN(playerid);

            return 1;
        }
    }
    return 0;
}

forward ShowTDN(playerid, type, const reason[]);
public ShowTDN(playerid, type, const reason[])
{
    for(new cycle; cycle < MAX_TDN; cycle++)
    {
        if(!TextDrawsNotification[playerid][cycle][notifyUse])
        {
            TextDrawsNotification[playerid][cycle][notifyText][0] = EOS;

            new text[MAX_TDN_TEXT];

            for(new len = strlen(reason), pos; pos < len; pos ++)
            {
                switch(reason[pos])
                {
                    case '`': text[pos] = 177;
                    case '&': text[pos] = 38;
                    default:  text[pos] = reason[pos];
                }
            }
            
            strcat(TextDrawsNotification[playerid][cycle][notifyText], text, MAX_TDN_TEXT);
            TextDrawsNotification[playerid][cycle][notifyTime] = 100;
            TextDrawsNotification[playerid][cycle][notifymode] = type;
 
            TextDrawsNotification[playerid][cycle][notifyUse] = true;
 
            LinesTDN(playerid, cycle);

            #if defined TDN_MODE_DOWN

            MinPosYTDN(playerid, cycle);
            MaxPosYTDN(playerid, cycle);

            #endif

            #if defined TDN_MODE_UP

            MaxPosYTDN(playerid, cycle);
            MinPosYTDN(playerid, cycle);
            
            #endif

            TextDrawsNotification[playerid][cycle][notifyHide] = -1;
            
            switch(type)
            {
                case NOTIFICATION_INFO:
                {
                    PlayerPlaySound(playerid, 1138, 0.0, 0.0, 0.0);
                }
                case NOTIFICATION_ERROR:
                {
                    PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                }
                case NOTIFICATION_SUCCESS:
                {
                    PlayerPlaySound(playerid, 5203, 0.0, 0.0, 0.0);
                }
                case NOTIFICATION_SYNTAX:
                {
                    PlayerPlaySound(playerid, 5205, 0.0, 0.0, 0.0);
                }
                case NOTIFICATION_WARNING:
                {
                    PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
                }
                case NOTIFICATION_MESSAGES:
                {
                    PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                }
            }
            CreateTDN(playerid, type, cycle);

            SetTimerEx("TimerHideTDN", TDN_TIME, false, "i", playerid);
            return 1;
        }
    }
    return 1;
}

forward ShowTDN_Manual(playerid, type, const reason[]);
public ShowTDN_Manual(playerid, type, const reason[])
{
    for(new cycle; cycle < MAX_TDN; cycle++)
    {
        if(!TextDrawsNotification[playerid][cycle][notifyUse])
        {
            TextDrawsNotification[playerid][cycle][notifyText][0] = EOS;

            new text[MAX_TDN_TEXT];

            for(new len = strlen(reason), pos; pos < len; pos ++)
            {
                switch(reason[pos])
                {
                    default:  text[pos] = reason[pos];
                }
            }

            strcat(TextDrawsNotification[playerid][cycle][notifyText], text, MAX_TDN_TEXT);
            TextDrawsNotification[playerid][cycle][notifymode] = type;
 
            TextDrawsNotification[playerid][cycle][notifyUse] = true;
 
            LinesTDN(playerid, cycle);

            #if defined TDN_MODE_DOWN

            MinPosYTDN(playerid, cycle);
            MaxPosYTDN(playerid, cycle);

            #endif

            #if defined TDN_MODE_UP

            MaxPosYTDN(playerid, cycle);
            MinPosYTDN(playerid, cycle);
            
            #endif

            CreateTDN(playerid, type, cycle);

            for(new i; i < MAX_TDN; i++)
            {
                if(used(playerid, notifycounter[playerid]))
                {
                    if(notifycounter[playerid] == MAX_TDN - 1) 
                    {
                        notifycounter[playerid] = 0;
                    }
                    else 
                    {
                        notifycounter[playerid]++;
                    }
                }
                else break;
            }

            new TDN = notifycounter[playerid];

            TextDrawsNotification[playerid][cycle][notifyHide] = TDN;

            if(notifycounter[playerid] == MAX_TDN - 1) 
            {
                notifycounter[playerid] = 0;
            }
            else 
            {
                notifycounter[playerid]++;
            }
            return TDN;
        }
    }
    return -1;
}

stock used(playerid, id)
{
    for(new cycle; cycle < MAX_TDN; cycle++)
    {
        if(TextDrawsNotification[playerid][cycle][notifyHide] == id) return 1;
    }
    return 0;
}

forward hideTDN(playerid, TDN);
public hideTDN(playerid, TDN)
{
    for(new cycle; cycle < MAX_TDN; cycle++)
    {
        if(TextDrawsNotification[playerid][cycle][notifyHide] == TDN)
        {
            TextDrawsNotification[playerid][cycle][notifyUse] = false;
            if(TextDrawsNotification[playerid][cycle][notifyTextDraw] != PlayerText: INVALID_PLAYER_TEXT_DRAW)
            {
                PlayerTextDrawDestroy(playerid, TextDrawsNotification[playerid][cycle][notifyTextDraw]);
                TextDrawsNotification[playerid][cycle][notifyLine] = 0;
                TextDrawsNotification[playerid][cycle][notifyText][0] = EOS;
                TextDrawsNotification[playerid][cycle][notifyMinPosY] = 0;
                TextDrawsNotification[playerid][cycle][notifyMaxPosY] = 0;
                TextDrawsNotification[playerid][cycle][notifyTextDraw] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
                TextDrawsNotification[playerid][cycle][notifyTime] = 100;
                for(new txd; txd < 23; txd++)
                {
                    PlayerTextDrawDestroy(playerid, TextDrawsNotification[playerid][cycle][textdraw_notification][txd]);
                    TextDrawsNotification[playerid][cycle][textdraw_notification][txd] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
                }
            }
            TextDrawsNotification[playerid][cycle][notifyHide] = -1;
            UpdateTDN(playerid);
            return 1;
        }
    }
    return 0;
}

stock UpdateTDN(playerid)
{
    for(new cycle; cycle < MAX_TDN; cycle ++)
    {
        if(!TextDrawsNotification[playerid][cycle][notifyUse])
        {
            if(cycle != MAX_TDN - 1)
            {
                if(TextDrawsNotification[playerid][cycle + 1][notifyUse])
                {
                    TextDrawsNotification[playerid][cycle][notifyUse] = TextDrawsNotification[playerid][cycle + 1][notifyUse];
                    TextDrawsNotification[playerid][cycle][notifyLine] = TextDrawsNotification[playerid][cycle + 1][notifyLine];
                    strcat(TextDrawsNotification[playerid][cycle][notifyText], TextDrawsNotification[playerid][cycle + 1][notifyText], MAX_TDN_TEXT);
                    TextDrawsNotification[playerid][cycle][notifymode] = TextDrawsNotification[playerid][cycle + 1][notifymode];
                    TextDrawsNotification[playerid][cycle][notifyTextDraw] = TextDrawsNotification[playerid][cycle + 1][notifyTextDraw];
                    TextDrawsNotification[playerid][cycle][notifyHide] = TextDrawsNotification[playerid][cycle + 1][notifyHide];
                    TextDrawsNotification[playerid][cycle][notifyTime] = TextDrawsNotification[playerid][cycle + 1][notifyTime];

                    TextDrawsNotification[playerid][cycle + 1][notifyUse] = false;
                    TextDrawsNotification[playerid][cycle + 1][notifyLine] = 0;
                    TextDrawsNotification[playerid][cycle + 1][notifyText][0] = EOS;
                    PlayerTextDrawDestroy(playerid, TextDrawsNotification[playerid][cycle + 1][notifyTextDraw]);
                    TextDrawsNotification[playerid][cycle + 1][notifyTextDraw] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
                    TextDrawsNotification[playerid][cycle + 1][notifyMinPosY] = 0;
                    TextDrawsNotification[playerid][cycle + 1][notifyMaxPosY] = 0;
                    TextDrawsNotification[playerid][cycle + 1][notifyHide] = -1;
                    TextDrawsNotification[playerid][cycle + 1][notifymode] = -1;
                    TextDrawsNotification[playerid][cycle + 1][notifyTime] = 100;

                    for(new txd; txd < 23; txd++)
                    {
                        TextDrawsNotification[playerid][cycle][textdraw_notification][txd] = TextDrawsNotification[playerid][cycle + 1][textdraw_notification][txd];
                        PlayerTextDrawDestroy(playerid, TextDrawsNotification[playerid][cycle + 1][textdraw_notification][txd]);
                        TextDrawsNotification[playerid][cycle + 1][textdraw_notification][txd] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
                    }

                    #if defined TDN_MODE_DOWN

                    MinPosYTDN(playerid, cycle);
                    MaxPosYTDN(playerid, cycle);
                    
                    #endif

                    #if defined TDN_MODE_UP
                    
                    MaxPosYTDN(playerid, cycle);
                    MinPosYTDN(playerid, cycle);
                    
                    #endif       
                }
            }
        }
        else if(TextDrawsNotification[playerid][cycle][notifyUse])
        {
            if(cycle != 0)
            {
                if(!TextDrawsNotification[playerid][cycle - 1][notifyUse])
                {
                    TextDrawsNotification[playerid][cycle - 1][notifyUse] = TextDrawsNotification[playerid][cycle][notifyUse];
                    TextDrawsNotification[playerid][cycle - 1][notifyLine] = TextDrawsNotification[playerid][cycle][notifyLine];
                    strcat(TextDrawsNotification[playerid][cycle - 1][notifyText], TextDrawsNotification[playerid][cycle][notifyText], MAX_TDN_TEXT);
                    TextDrawsNotification[playerid][cycle - 1][notifymode] = TextDrawsNotification[playerid][cycle][notifymode];
                    TextDrawsNotification[playerid][cycle - 1][notifyTextDraw] = TextDrawsNotification[playerid][cycle][notifyTextDraw];
                    TextDrawsNotification[playerid][cycle - 1][notifyHide] = TextDrawsNotification[playerid][cycle][notifyHide];
                    TextDrawsNotification[playerid][cycle - 1][notifyTime] = TextDrawsNotification[playerid][cycle][notifyTime];

                    TextDrawsNotification[playerid][cycle][notifyUse] = false;
                    TextDrawsNotification[playerid][cycle][notifyLine] = 0;
                    TextDrawsNotification[playerid][cycle][notifyText][0] = EOS;
                    TextDrawsNotification[playerid][cycle][notifymode] = -1;
                    PlayerTextDrawDestroy(playerid, TextDrawsNotification[playerid][cycle][notifyTextDraw]);
                    TextDrawsNotification[playerid][cycle][notifyTextDraw] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
                    TextDrawsNotification[playerid][cycle][notifyMinPosY] = 0;
                    TextDrawsNotification[playerid][cycle][notifyMaxPosY] = 0;
                    TextDrawsNotification[playerid][cycle][notifyHide] = -1;
                    TextDrawsNotification[playerid][cycle][notifyTime] = 100;

                    for(new txd; txd < 23; txd++)
                    {
                        TextDrawsNotification[playerid][cycle - 1][textdraw_notification][txd] = TextDrawsNotification[playerid][cycle][textdraw_notification][txd];
                        PlayerTextDrawDestroy(playerid, TextDrawsNotification[playerid][cycle][textdraw_notification][txd]);
                        TextDrawsNotification[playerid][cycle][textdraw_notification][txd] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
                    }

                    #if defined TDN_MODE_DOWN

                    MinPosYTDN(playerid, cycle - 1);
                    MaxPosYTDN(playerid, cycle - 1);
                    
                    #endif

                    #if defined TDN_MODE_UP
                    
                    MaxPosYTDN(playerid, cycle - 1);
                    MinPosYTDN(playerid, cycle - 1);
                    
                    #endif
                }
            }
        }
        CreateTDN(playerid, TextDrawsNotification[playerid][cycle][notifymode], cycle);
    }
    return 1;
}

stock MinPosYTDN(playerid, TDN)
{
    #if defined TDN_MODE_DOWN

    if(TDN == 0)
    {
        TextDrawsNotification[playerid][TDN][notifyMinPosY] = TDN_POS_Y;
    }
    else
    {
        TextDrawsNotification[playerid][TDN][notifyMinPosY] = TextDrawsNotification[playerid][TDN - 1][notifyMaxPosY] + TDN_DISTANCE;
    }
    return 1;

    #endif

    #if defined TDN_MODE_UP

    TextDrawsNotification[playerid][TDN][notifyMinPosY] = TextDrawsNotification[playerid][TDN][notifyMaxPosY] - ((TDN_LETTER_SIZE_Y * 2) + 2) - ((TDN_LETTER_SIZE_Y * 5.75) * TDN_TINGGI_BOX) - ((TDN_TINGGI_BOX - 1) * ((TDN_LETTER_SIZE_Y * 2) + 2 + TDN_LETTER_SIZE_Y)) - (TDN_LETTER_SIZE_Y + 3);
    return 1;

    #endif
}

stock MaxPosYTDN(playerid, TDN)
{
    #if defined TDN_MODE_DOWN

    TextDrawsNotification[playerid][TDN][notifyMaxPosY] = TextDrawsNotification[playerid][TDN][notifyMinPosY] + (TDN_LETTER_SIZE_Y * 2) + 2 + (TDN_LETTER_SIZE_Y * 5.75 * TDN_TINGGI_BOX) + ((TDN_TINGGI_BOX - 1) * ((TDN_LETTER_SIZE_Y * 2) + 2 + TDN_LETTER_SIZE_Y)) + TDN_LETTER_SIZE_Y + 3;
    return 1;

    #endif

    #if defined TDN_MODE_UP

    if(TDN == 0)
    {
        TextDrawsNotification[playerid][TDN][notifyMaxPosY] = TDN_POS_Y;
    }
    else
    {
        TextDrawsNotification[playerid][TDN][notifyMaxPosY] = TextDrawsNotification[playerid][TDN - 1][notifyMinPosY] - TDN_DISTANCE;
    }
    return 1;

    #endif
}

stock LinesTDN(playerid, TDN)
{
    new lines = 1, Float:width, lastspace = -1, supr, len = strlen(TextDrawsNotification[playerid][TDN][notifyText]);
 
    for(new i = 0; i < len; i ++)
    {
        if(TextDrawsNotification[playerid][TDN][notifyText][i] == '~')
        {
            if(supr == 0)
            {
                supr = 1;
                if(TextDrawsNotification[playerid][TDN][notifyText][i+2] != '~') SendClientMessage(playerid, -1, "Error: '~' used incorrectly'");
            }
            else if(supr == 1) supr = 0;
        }
        else
        {
            if(supr == 1)
            {
                if(TextDrawsNotification[playerid][TDN][notifyText][i] == 'n')
                {
                    lines ++;
                    lastspace = -1;
                    width = 0;
                }
            }
            else
            {
                if(TextDrawsNotification[playerid][TDN][notifyText][i] == ' ') lastspace = i;
 
                width += TDN_LETTER_SIZE_X * GetTextDrawCharacterWidth(TextDrawsNotification[playerid][TDN][notifyText][i], TDN_FONT, bool:TDN_PROPORTIONAL);

                if(width > TDN_SIZE - 3)
                {
                    if(lastspace != i && lastspace != -1)
                    {
                        lines ++;
                        i = lastspace;
                        lastspace = -1;
                        width = 0;
                    }
                    else
                    {
                        lines ++;
                        lastspace = -1;
                        width = 0;
                    }
                }
            }
        }
    }
    
    TextDrawsNotification[playerid][TDN][notifyLine] = lines;
 
    return 1;
}

stock CreateTDN(playerid, type, TDN)
{
    if(TextDrawsNotification[playerid][TDN][notifyUse])
    {
        TextDrawsNotification[playerid][TDN][notifymode] = type;
        if(TextDrawsNotification[playerid][TDN][notifyTextDraw] != PlayerText: INVALID_PLAYER_TEXT_DRAW)
        {
            PlayerTextDrawDestroy(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw]);
            TextDrawsNotification[playerid][TDN][notifyTextDraw] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
            for(new txd; txd < 23; txd++)
            {
                PlayerTextDrawDestroy(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][txd]);
                TextDrawsNotification[playerid][TDN][textdraw_notification][txd] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
            }
        }
        switch(type)
        {
            case NOTIFICATION_ERROR:
            {
                TextDrawsNotification[playerid][TDN][textdraw_notification][0] = CreatePlayerTextDraw(playerid, 507.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 105.000)), "LD_BUM:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 102.000, 37.500);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], -1448498689);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][1] = CreatePlayerTextDraw(playerid, 499.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 101.000)), "ld_beat:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 18.000, 22.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], -909522433);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][2] = CreatePlayerTextDraw(playerid, 599.200, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 101.000)), "ld_beat:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 18.000, 22.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], -909522433);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][3] = CreatePlayerTextDraw(playerid, 499.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 124.500)), "ld_beat:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 18.000, 22.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], -1448498689);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][4] = CreatePlayerTextDraw(playerid, 599.200, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 124.500)), "ld_beat:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 18.000, 22.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], -1448498689);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][5] = CreatePlayerTextDraw(playerid, 502.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 112.000)), "LD_BUM:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 112.000, 23.500);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], -1448498689);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][6] = CreatePlayerTextDraw(playerid, 507.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 105.000)), "LD_BUM:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 102.000, 13.500);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], -909522433);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][7] = CreatePlayerTextDraw(playerid, 502.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 112.000)), "LD_BUM:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 112.000, 6.500);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], -909522433);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][8] = CreatePlayerTextDraw(playerid, 506.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 105.000)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 7.000, 8.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], -16776961);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][9] = CreatePlayerTextDraw(playerid, 510.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 105.000)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 7.000, 8.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], -16776961);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][10] = CreatePlayerTextDraw(playerid, 506.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 110.299)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 7.000, 8.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], -16776961);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][11] = CreatePlayerTextDraw(playerid, 510.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 110.299)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 7.000, 8.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], -16776961);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][12] = CreatePlayerTextDraw(playerid, 507.299, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 108.000)), "ld_bum:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 8.500, 6.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], -16776961);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][13] = CreatePlayerTextDraw(playerid, 509.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 106.500)), "ld_bum:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 5.000, 10.500);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], -16776961);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][14] = CreatePlayerTextDraw(playerid, 508.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 107.000)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 7.000, 9.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], -1);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][15] = CreatePlayerTextDraw(playerid, 511.500, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 108.500)), "X");
                PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 0.180, 0.597);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 2);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], -16776961);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 1);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 1);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 0);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 1);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][16] = CreatePlayerTextDraw(playerid, 518.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 106.500)), "ERROR");
                PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 0.180, 0.999);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 100);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 1);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 1);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 0);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 1);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 1);
            }
            case NOTIFICATION_SUCCESS:
            {
                TextDrawsNotification[playerid][TDN][textdraw_notification][0] = CreatePlayerTextDraw(playerid, 507.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 105.000)), "LD_BUM:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 102.000, 37.500);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], -1448498689);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][1] = CreatePlayerTextDraw(playerid, 499.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 101.000)), "ld_beat:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 18.000, 22.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], -909522433);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][2] = CreatePlayerTextDraw(playerid, 599.200, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 101.000)), "ld_beat:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 18.000, 22.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], -909522433);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][3] = CreatePlayerTextDraw(playerid, 499.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 124.500)), "ld_beat:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 18.000, 22.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], -1448498689);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][4] = CreatePlayerTextDraw(playerid, 599.200, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 124.500)), "ld_beat:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 18.000, 22.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], -1448498689);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][5] = CreatePlayerTextDraw(playerid, 502.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 112.000)), "LD_BUM:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 112.000, 23.500);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], -1448498689);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][6] = CreatePlayerTextDraw(playerid, 507.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 105.000)), "LD_BUM:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 102.000, 13.500);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], -909522433);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][7] = CreatePlayerTextDraw(playerid, 502.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 112.000)), "LD_BUM:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 112.000, 6.500);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], -909522433);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][8] = CreatePlayerTextDraw(playerid, 506.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 105.000)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 7.000, 8.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 512819199);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][9] = CreatePlayerTextDraw(playerid, 510.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 105.000)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 7.000, 8.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 512819199);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][10] = CreatePlayerTextDraw(playerid, 506.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 110.299)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 7.000, 8.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 512819199);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][11] = CreatePlayerTextDraw(playerid, 510.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 110.299)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 7.000, 8.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 512819199);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][12] = CreatePlayerTextDraw(playerid, 507.299, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 108.000)), "ld_bum:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 8.500, 6.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 512819199);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][13] = CreatePlayerTextDraw(playerid, 509.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 106.500)), "ld_bum:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 5.000, 10.500);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 512819199);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][14] = CreatePlayerTextDraw(playerid, 508.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 107.000)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 7.000, 9.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], -1);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][15] = CreatePlayerTextDraw(playerid, 512.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 109.000)), "/");
                PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 0.180, 0.497);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 2);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 512819199);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 1);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 1);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 0);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 1);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][16] = CreatePlayerTextDraw(playerid, 518.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 106.500)), "SUCCESS");
                PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 0.180, 0.999);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 100);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 1);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 1);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 0);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 1);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][17] = CreatePlayerTextDraw(playerid, 511.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 111.500)), "/");
                PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][17], -0.180, 0.190);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][17], 2);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][17], 512819199);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][17], 1);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][17], 1);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][17], 0);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][17], 1);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][17], 1);
            }
            case NOTIFICATION_SYNTAX:
            {
                TextDrawsNotification[playerid][TDN][textdraw_notification][0] = CreatePlayerTextDraw(playerid, 507.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 105.000)), "LD_BUM:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 102.000, 37.500);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], -1448498689);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][1] = CreatePlayerTextDraw(playerid, 499.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 101.000)), "ld_beat:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 18.000, 22.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], -909522433);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][2] = CreatePlayerTextDraw(playerid, 599.200, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 101.000)), "ld_beat:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 18.000, 22.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], -909522433);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][3] = CreatePlayerTextDraw(playerid, 499.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 124.500)), "ld_beat:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 18.000, 22.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], -1448498689);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][4] = CreatePlayerTextDraw(playerid, 599.200, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 124.500)), "ld_beat:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 18.000, 22.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], -1448498689);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][5] = CreatePlayerTextDraw(playerid, 502.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 112.000)), "LD_BUM:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 112.000, 23.500);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], -1448498689);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][6] = CreatePlayerTextDraw(playerid, 507.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 105.000)), "LD_BUM:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 102.000, 13.500);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], -909522433);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][7] = CreatePlayerTextDraw(playerid, 502.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 112.000)), "LD_BUM:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 112.000, 6.500);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], -909522433);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][8] = CreatePlayerTextDraw(playerid, 506.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 105.000)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 7.000, 8.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], -2139062017);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][9] = CreatePlayerTextDraw(playerid, 510.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 105.000)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 7.000, 8.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], -2139062017);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][10] = CreatePlayerTextDraw(playerid, 506.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 110.299)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 7.000, 8.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], -2139062017);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][11] = CreatePlayerTextDraw(playerid, 510.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 110.299)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 7.000, 8.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], -2139062017);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][12] = CreatePlayerTextDraw(playerid, 507.299, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 108.000)), "ld_bum:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 8.500, 6.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], -2139062017);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][13] = CreatePlayerTextDraw(playerid, 509.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 106.500)), "ld_bum:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 5.000, 10.500);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], -2139062017);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][14] = CreatePlayerTextDraw(playerid, 518.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 106.500)), "SYNTAX");
                PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 0.180, 0.999);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 100);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 1);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 1);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 0);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 1);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][15] = CreatePlayerTextDraw(playerid, 507.700, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 106.500)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 8.000, 10.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 1768516095);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][16] = CreatePlayerTextDraw(playerid, 508.499, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 107.500)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 6.500, 8.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], -1448498689);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][17] = CreatePlayerTextDraw(playerid, 509.499, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 108.500)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][17], 4.500, 6.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][17], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][17], -2139062017);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][17], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][17], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][17], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][17], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][17], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][18] = CreatePlayerTextDraw(playerid, 510.499, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 109.500)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][18], 2.500, 4.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][18], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][18], -1448498689);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][18], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][18], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][18], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][18], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][18], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][19] = CreatePlayerTextDraw(playerid, 511.499, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 110.500)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][19], 0.500, 2.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][19], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][19], -2139062017);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][19], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][19], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][19], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][19], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][19], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][20] = CreatePlayerTextDraw(playerid, 510.200, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 110.000)), "/");
                PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][20], 0.170, 0.398);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][20], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][20], -1448498689);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][20], 1);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][20], 1);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][20], 0);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][20], 1);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][20], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][21] = CreatePlayerTextDraw(playerid, 510.200, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 113.000)), "/");
                PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][21], 0.170, -0.388);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][21], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][21], -1448498689);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][21], 1);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][21], 1);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][21], 0);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][21], 1);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][21], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][22] = CreatePlayerTextDraw(playerid, 512.200, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 111.000)), "LD_BUM:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][22], 1.500, 0.500);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][22], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][22], -1448498689);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][22], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][22], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][22], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][22], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][22], 1);
            }
            case NOTIFICATION_WARNING:
            {
                TextDrawsNotification[playerid][TDN][textdraw_notification][0] = CreatePlayerTextDraw(playerid, 507.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 105.000)), "LD_BUM:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 102.000, 37.500);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], -1448498689);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][1] = CreatePlayerTextDraw(playerid, 499.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 101.000)), "ld_beat:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 18.000, 22.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], -909522433);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][2] = CreatePlayerTextDraw(playerid, 599.200, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 101.000)), "ld_beat:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 18.000, 22.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], -909522433);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][3] = CreatePlayerTextDraw(playerid, 499.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 124.500)), "ld_beat:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 18.000, 22.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], -1448498689);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][4] = CreatePlayerTextDraw(playerid, 599.200, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 124.500)), "ld_beat:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 18.000, 22.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], -1448498689);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][5] = CreatePlayerTextDraw(playerid, 502.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 112.000)), "LD_BUM:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 112.000, 23.500);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], -1448498689);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][6] = CreatePlayerTextDraw(playerid, 507.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 105.000)), "LD_BUM:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 102.000, 13.500);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], -909522433);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][7] = CreatePlayerTextDraw(playerid, 502.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 112.000)), "LD_BUM:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 112.000, 6.500);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], -909522433);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][8] = CreatePlayerTextDraw(playerid, 506.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 105.000)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 7.000, 8.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], -2147483393);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][9] = CreatePlayerTextDraw(playerid, 510.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 105.000)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 7.000, 8.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], -2147483393);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][10] = CreatePlayerTextDraw(playerid, 506.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 110.299)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 7.000, 8.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], -2147483393);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][11] = CreatePlayerTextDraw(playerid, 510.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 110.299)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 7.000, 8.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], -2147483393);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][12] = CreatePlayerTextDraw(playerid, 507.299, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 108.000)), "ld_bum:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 8.500, 6.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], -2147483393);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][13] = CreatePlayerTextDraw(playerid, 509.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 106.500)), "ld_bum:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 5.000, 10.500);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], -2147483393);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][14] = CreatePlayerTextDraw(playerid, 508.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 107.000)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 7.000, 9.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], -1);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][15] = CreatePlayerTextDraw(playerid, 511.500, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 108.500)), "!");
                PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 0.180, 0.598);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 2);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], -2147483393);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 1);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 1);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 0);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 1);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][16] = CreatePlayerTextDraw(playerid, 518.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 106.500)), "WARNING");
                PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 0.180, 0.999);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 100);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 1);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 1);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 0);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 1);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 1);
            }
            case NOTIFICATION_MESSAGES:
            {
                TextDrawsNotification[playerid][TDN][textdraw_notification][0] = CreatePlayerTextDraw(playerid, 507.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 105.000)), "LD_BUM:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 102.000, 37.500);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], -1448498689);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][1] = CreatePlayerTextDraw(playerid, 499.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 101.000)), "ld_beat:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 18.000, 22.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], -909522433);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][2] = CreatePlayerTextDraw(playerid, 599.200, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 101.000)), "ld_beat:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 18.000, 22.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], -909522433);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][3] = CreatePlayerTextDraw(playerid, 499.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 124.500)), "ld_beat:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 18.000, 22.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], -1448498689);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][4] = CreatePlayerTextDraw(playerid, 599.200, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 124.500)), "ld_beat:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 18.000, 22.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], -1448498689);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][5] = CreatePlayerTextDraw(playerid, 502.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 112.000)), "LD_BUM:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 112.000, 23.500);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], -1448498689);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][6] = CreatePlayerTextDraw(playerid, 507.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 105.000)), "LD_BUM:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 102.000, 13.500);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], -909522433);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][7] = CreatePlayerTextDraw(playerid, 502.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 112.000)), "LD_BUM:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 112.000, 6.500);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], -909522433);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][8] = CreatePlayerTextDraw(playerid, 506.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 105.000)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 7.000, 8.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 16711935);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][9] = CreatePlayerTextDraw(playerid, 510.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 105.000)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 7.000, 8.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 16711935);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][10] = CreatePlayerTextDraw(playerid, 506.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 110.299)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 7.000, 8.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 16711935);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][11] = CreatePlayerTextDraw(playerid, 510.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 110.299)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 7.000, 8.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 16711935);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][12] = CreatePlayerTextDraw(playerid, 507.299, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 108.000)), "ld_bum:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 8.500, 6.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 16711935);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][13] = CreatePlayerTextDraw(playerid, 509.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 106.500)), "ld_bum:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 5.000, 10.500);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 16711935);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][14] = CreatePlayerTextDraw(playerid, 508.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 108.000)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 7.000, 6.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], -1);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][15] = CreatePlayerTextDraw(playerid, 509.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 112.000)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 2.000, 2.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], -1);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][16] = CreatePlayerTextDraw(playerid, 518.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 106.500)), "MESSAGES");
                PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 0.180, 0.999);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 100);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 1);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 1);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 0);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 1);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 1);
            }
            default: // Notification Info
            {
                TextDrawsNotification[playerid][TDN][textdraw_notification][0] = CreatePlayerTextDraw(playerid, 507.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 105.000)), "LD_BUM:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 102.000, 37.500);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], -1448498689);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][1] = CreatePlayerTextDraw(playerid, 499.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 101.000)), "ld_beat:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 18.000, 22.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], -909522433);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][2] = CreatePlayerTextDraw(playerid, 599.200, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 101.000)), "ld_beat:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 18.000, 22.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], -909522433);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][3] = CreatePlayerTextDraw(playerid, 499.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 124.500)), "ld_beat:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 18.000, 22.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], -1448498689);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][4] = CreatePlayerTextDraw(playerid, 599.200, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 124.500)), "ld_beat:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 18.000, 22.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], -1448498689);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][5] = CreatePlayerTextDraw(playerid, 502.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 112.000)), "LD_BUM:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 112.000, 23.500);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], -1448498689);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][6] = CreatePlayerTextDraw(playerid, 507.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 105.000)), "LD_BUM:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 102.000, 13.500);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], -909522433);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][7] = CreatePlayerTextDraw(playerid, 502.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 112.000)), "LD_BUM:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 112.000, 6.500);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], -909522433);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][8] = CreatePlayerTextDraw(playerid, 506.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 105.000)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 7.000, 8.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], -2686721);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][9] = CreatePlayerTextDraw(playerid, 510.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 105.000)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 7.000, 8.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], -2686721);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][10] = CreatePlayerTextDraw(playerid, 506.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 110.299)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 7.000, 8.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], -2686721);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][11] = CreatePlayerTextDraw(playerid, 510.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 110.299)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 7.000, 8.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], -2686721);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][12] = CreatePlayerTextDraw(playerid, 507.299, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 108.000)), "ld_bum:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 8.500, 6.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], -2686721);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][12], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][13] = CreatePlayerTextDraw(playerid, 509.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 106.500)), "ld_bum:blkdot");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 5.000, 10.500);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], -2686721);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][13], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][14] = CreatePlayerTextDraw(playerid, 508.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 107.000)), "LD_BEAT:chit");
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 7.000, 9.000);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], -1);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 0);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 0);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 255);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 4);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][14], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][15] = CreatePlayerTextDraw(playerid, 511.500, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 108.500)), "i");
                PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 0.180, 0.597);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 2);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], -2686721);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 1);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 1);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 0);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 1);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][15], 1);

                TextDrawsNotification[playerid][TDN][textdraw_notification][16] = CreatePlayerTextDraw(playerid, 518.000, (TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 106.500)), "INFO");
                PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 0.180, 0.999);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 100);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 1);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 1);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 0);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 1);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][16], 1);
            }
        }

        TextDrawsNotification[playerid][TDN][notifyTextDraw] = CreatePlayerTextDraw(playerid, 507.000, TextDrawsNotification[playerid][TDN][notifyMinPosY], TextDrawsNotification[playerid][TDN][notifyText]);
        PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 0.130, 0.785);
        PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 609.000, 22.000);
        PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 1);
        PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 255);
        PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 1);
        PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 1);
        PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 0);
        PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 1);
        PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 1);

        for(new txd; txd < 23; txd++)
        {
            PlayerTextDrawShow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][txd]);
        }
        PlayerTextDrawShow(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw]);
    }
    return 1;
}

/*ptask PlayerUpdate[1000](playerid)
{
    for(new cycle; cycle < MAX_TDN; cycle++)
    {
        if(TextDrawsNotification[i][cycle][notifyHide] == -1)
        {
            TextDrawsNotification[i][cycle][notifyTime] = TextDrawsNotification[i][cycle][notifyTime] - (2 * 10);
            if(TextDrawsNotification[i][cycle][notifyTime] < 1) TextDrawsNotification[i][cycle][notifyTime] = TextDrawsNotification[i][cycle][notifyTime] = 0;

            PlayerTextDrawTextSize(i, TextDrawsNotification[i][cycle][textdraw_notification][3], TextDrawsNotification[i][cycle][notifyTime] * (118.000000 / 100), 1.000000);
            PlayerTextDrawShow(i, TextDrawsNotification[i][cycle][textdraw_notification][3]);
        }
    }
    return 1;
}*/

hook OnPlayerConnect(playerid)
{
	for(new TDN; TDN < MAX_TDN; TDN++)
	{
		PlayerTextDrawDestroy(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw]);
		TextDrawsNotification[playerid][TDN][notifyTextDraw] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
		TextDrawsNotification[playerid][TDN][notifyHide] = -1;

        for(new x; x < 23; x++)
        {
		    PlayerTextDrawDestroy(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][x]);
		    TextDrawsNotification[playerid][TDN][textdraw_notification][x] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
		
	    }
    }
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    for(new cycle; cycle < MAX_TDN; cycle++)
    {
        TextDrawsNotification[playerid][cycle][notifyUse] = false;
        TextDrawsNotification[playerid][cycle][notifyLine] = 0;
        TextDrawsNotification[playerid][cycle][notifyText][0] = EOS;
        TextDrawsNotification[playerid][cycle][notifyMinPosY] = 0;
        TextDrawsNotification[playerid][cycle][notifyMaxPosY] = 0;
        TextDrawsNotification[playerid][cycle][notifyHide] = -1;
		PlayerTextDrawDestroy(playerid, TextDrawsNotification[playerid][cycle][notifyTextDraw]);
        TextDrawsNotification[playerid][cycle][notifyTextDraw] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
        TextDrawsNotification[playerid][cycle][notifyTime] = 100;

        for(new x; x < 23; x++)
        {
		    PlayerTextDrawDestroy(playerid, TextDrawsNotification[playerid][cycle][textdraw_notification][x]);
		    TextDrawsNotification[playerid][cycle][textdraw_notification][x] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
		
	    }
    }
	return 1;
}