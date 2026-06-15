YCMD:ask(playerid, params[], help)
{
    new askid = Iter_Free(Asks);

    if(isnull(params))
        return SUM(playerid, "/ask [pertanyaan]");

    if(Ask_GetCount(playerid) > 0)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah mengajukan 'ask' yang belum terjawab, mohon tunggu!");

    if(askid <= -1)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Layanan 'ask' sedang penuh, mohon tunggu!");

    if(AccountData[playerid][pAskTime] >= gettime())
        return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Mohon tunggu %d detik sebelum mengirim lagi!", AccountData[playerid][pAskTime] - gettime()));

    SendClientMessageEx(playerid, X11_YELLOW, "(Bertanya) %s [%d] > %s", GetPlayerRoleplayName(playerid), playerid, params);
    foreach (new i : Player)
    {
        if((AccountData[i][pAdmin] > 0 && AccountData[i][pAdminDuty]) || AccountData[i][pSteward] || AccountData[i][pApprentice])
        {
            SendClientMessageEx(i, X11_YELLOW, "(Pertanyaan #%d) %s (%d) > %s", askid, AccountData[playerid][pName], playerid, params);
            PlayerPlaySound(i, 1137, 0.0, 0.0, 0.0);
        }
    }
    AccountData[playerid][pAskTime] = gettime() + 300;
    AskData[askid][askID] = askid;
    AskData[askid][askPlayer] = playerid;
    strcopy(AskData[askid][askText], params);
    Iter_Add(Asks, askid);
    return 1;
}

YCMD:ans(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 1)
     	return PermissionError(playerid);

    new askid, msg[144];
    if(sscanf(params,"ds[144]", askid, msg))
        return SUM(playerid, "/ans [ask id] [jawaban]");

    if(!Iter_Contains(Asks, askid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid ASK ID!");

    AccountData[AskData[askid][askPlayer]][pAskTime] = 0;
    SendStaffMessage(X11_YELLOW, "(Jawab #%d) %s menjawab %s (%d)", askid, AccountData[playerid][pAdminname], AccountData[AskData[askid][askPlayer]][pName], AskData[askid][askPlayer]);
    SendStaffMessage(X11_YELLOW, "> %s", msg);
    SendClientMessageEx(AskData[askid][askPlayer], X11_YELLOW, "(Jawaban) %s telah menjawab pertanyaan yang anda ajukan.", AccountData[playerid][pAdminname]);
    SendClientMessageEx(AskData[askid][askPlayer], X11_YELLOW, "(Pesan) %s", msg);
    Ask_Remove(askid);
    return 1;
}

YCMD:asks(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 1) 
        return PermissionError(playerid);
			
	new lstr[1524], counting;

    format(lstr, sizeof(lstr), "#ID\tDetail Pemain\tPertanyaan\n");
    foreach(new i : Asks)
    {
        if(strlen(AskData[i][askText]) > 64)
            format(lstr,sizeof(lstr), "%s#%d\t%s [%s] (%d)\t%.64s...\n", lstr, i, AccountData[AskData[i][askPlayer]][pName], AccountData[AskData[i][askPlayer]][pUCP], AskData[i][askPlayer], AskData[i][askText]);
        else
            format(lstr,sizeof(lstr), "%s#%d\t%s [%s] (%d)\t%s\n", lstr, i, AccountData[AskData[i][askPlayer]][pName], AccountData[AskData[i][askPlayer]][pUCP], AskData[i][askPlayer], AskData[i][askText]);

        PlayerListitem[playerid][counting++] = i;
    }

    if(counting == 0)
        ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada pertanyaan yang sedang aktif!");
    else
        Dialog_Show(playerid, "QueueAsks", DIALOG_STYLE_TABLIST_HEADERS,"{DA9100}Pahlawan Roleplay "WHITE"- Daftar Asks",lstr,"Cek","Tutup");
    return 1;
}

YCMD:aclear(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 4)
    {
        PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
        return PermissionError(playerid);
    }

    foreach(new i : Asks)
    {
        AskData[i][askID] = -1;
        AskData[i][askPlayer] = INVALID_PLAYER_ID;
        AskData[i][askText][0] = EOS;
    }
    Iter_Clear(Asks);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has cleared all questions.", AccountData[playerid][pAdminname]);
    return 1;
}