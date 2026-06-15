//Enums
#define MAX_REPORTS 50

enum reportData 
{
    rID,
    rPlayer,
    rText[256 char]
};
new ReportData[MAX_REPORTS][reportData],
    Iterator:Reports<MAX_REPORTS>;

Report_GetCount(playerid)
{
    new count;

    foreach (new i : Reports)
    {
        if(ReportData[i][rPlayer] == playerid)
        {
			count++;
        }
    }
    return count;
}

GetPlayerReportID(playerid)
{
    foreach(new i : Reports)
    {
        if(ReportData[i][rPlayer] == playerid)
        {
            return i;
        }
    }
    return INVALID_ITERATOR_SLOT;
}

Report_Remove(reportid)
{
    if(Iter_Contains(Reports, reportid))
    {
        ReportData[reportid][rID] = -1;
        ReportData[reportid][rPlayer] = INVALID_PLAYER_ID;
        ReportData[reportid][rText][0] = EOS;
        Iter_Remove(Reports, reportid);
    }
    return 1;
}