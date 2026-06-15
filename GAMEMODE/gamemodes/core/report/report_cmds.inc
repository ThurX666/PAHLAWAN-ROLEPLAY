YCMD:report(playerid, params[], help)
{
    new reportid = Iter_Free(Reports);

    if(isnull(params))
        return SUM(playerid, "/report [laporan]");

    if(Report_GetCount(playerid) > 0)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah mengajukan report, mohon tunggu respon!");

    if(reportid <= -1)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Report saat ini sedang penuh, mohon tunggu beberapa saat!");
    
    if(AccountData[playerid][pReportTime] >= gettime())
        return ShowTDN(playerid, NOTIFICATION_WARNING, sprintf("Mohon tunggu %d detik sebelum mengajukan report lagi!", AccountData[playerid][pReportTime] - gettime()));

    SendClientMessageEx(playerid, X11_RED, "(Report) %s (%d) > %s", AccountData[playerid][pName], playerid, params);
    foreach (new i : Player)
    {
        if(AccountData[i][pAdmin] > 0 && AccountData[i][pAdminDuty])
        {
            SendClientMessageEx(i, X11_RED, "(Report #%d) %s (%d) > %s", reportid, AccountData[playerid][pName], playerid, params);
            PlayerPlaySound(i, 1137, 0.0, 0.0, 0.0);
        }
    }
    AccountData[playerid][pReportTime] = gettime() + 300;
    ReportData[reportid][rID] = reportid;
    ReportData[reportid][rPlayer] = playerid;
    strcopy(ReportData[reportid][rText], params);
    Iter_Add(Reports, reportid);
    return 1;
}

YCMD:ra(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 2)
     	return PermissionError(playerid);

    static reportid, msg[144];

    if(sscanf(params,"dS()[144]", reportid, msg))
        return SUM(playerid, "/ra [report id] [(opt) pesan]");
        
    if(!Iter_Contains(Reports, reportid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Report ID!");

    AccountData[ReportData[reportid][rPlayer]][pReportTime] = 0;
    SendStaffMessage(X11_RED, "(Respon #%d) %s telah menanggapi laporan %s (%d)", reportid, AccountData[playerid][pAdminname], AccountData[ReportData[reportid][rPlayer]][pName], ReportData[reportid][rPlayer]);
    SendClientMessageEx(ReportData[reportid][rPlayer], X11_RED, "(Report) %s telah menanggapi laporan anda.", AccountData[playerid][pAdminname]);
    if(!isnull(msg))
    {
        SendClientMessageEx(ReportData[reportid][rPlayer], X11_RED, "(Pesan) %s", msg);
    }
    Report_Remove(reportid);
    return 1;
}

YCMD:reports(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 1)
        return PermissionError(playerid);
			
	new lstr[1524], counting;

    format(lstr,sizeof(lstr),"#ID\tDetail Pemain\tLaporan\n");

    foreach (new i : Reports)
    {
        if(strlen(ReportData[i][rText]) > 64)
            format(lstr,sizeof(lstr), "%s#%d\t%s [%s] (%d)\t%.64s...\n", lstr, i, AccountData[ReportData[i][rPlayer]][pName], AccountData[ReportData[i][rPlayer]][pUCP], ReportData[i][rPlayer], ReportData[i][rText]);
        else
            format(lstr,sizeof(lstr), "%s#%d\t%s [%s] (%d)\t%s\n", lstr, i, AccountData[ReportData[i][rPlayer]][pName], AccountData[ReportData[i][rPlayer]][pUCP], ReportData[i][rPlayer], ReportData[i][rText]);

        PlayerListitem[playerid][counting++] = i;
    }

    if(counting == 0)
        ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada laporan yang sedang aktif!");
    else
        Dialog_Show(playerid, "QueueReports", DIALOG_STYLE_TABLIST_HEADERS,"{DA9100}Pahlawan Roleplay "WHITE"- Daftar Reports",lstr,"Cek","Tutup");
    return 1;
}

YCMD:rclear(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 4)
        return PermissionError(playerid);

    foreach(new i : Reports)
    {
        ReportData[i][rID] = -1;
        ReportData[i][rPlayer] = INVALID_PLAYER_ID;
        ReportData[i][rText][0] = EOS;
    }
    Iter_Clear(Reports);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has cleared all reports.", AccountData[playerid][pAdminname]);
    return 1;
} 