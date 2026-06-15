YCMD:mysalary(playerid, params[], help)
{
    DisplaySalary(playerid);
    return 1;
}

YCMD:paycheck(playerid, params[], help)
{
    if(!IsPlayerInRangeOfPoint(playerid, 3.0, 1459.4313,-1002.3887,9.0519))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di dalam Bank Pacific!");

    if(AccountData[playerid][pPaycheckTime] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Belum saatnya untuk mengambil paycheck!");

    DisplayPaycheck(playerid);
    return 1;
}