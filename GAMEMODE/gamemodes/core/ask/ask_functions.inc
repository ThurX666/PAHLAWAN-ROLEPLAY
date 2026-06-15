//Enums
#define MAX_ASKS 50

enum askData 
{
    askID,
    askPlayer,
    askText[256 char]
};
new AskData[MAX_ASKS][askData],
    Iterator:Asks<MAX_ASKS>;

Ask_GetCount(playerid)
{
    new count;

    foreach (new i : Asks)
    {
        if(AskData[i][askPlayer] == playerid)
        {
			count++;
        }
    }
    return count;
}

GetPlayerAskID(playerid)
{
    foreach(new i : Asks)
    {
        if(AskData[i][askPlayer] == playerid)
        {
            return i;
        }
    }
    return INVALID_ITERATOR_SLOT;
}

Ask_Remove(askid)
{
    if(Iter_Contains(Asks, askid))
    {
        AskData[askid][askID] = -1;
        AskData[askid][askPlayer] = INVALID_PLAYER_ID;
        AskData[askid][askText][0] = EOS;
        Iter_Remove(Asks, askid);
    }
    return 1;
}