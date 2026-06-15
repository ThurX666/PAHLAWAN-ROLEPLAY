YCMD:makektp(playerid, params[], help)
{
	new otherid;
	
	if(AccountData[playerid][pFaction] != FACTION_SAGOV)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Pemerintah Pahlawan Roleplay!");

    if(!IsPlayerInRangeOfPoint(playerid, 4.0, 1373.4606,1597.7161,15.6703))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di tempat seharusnya!");

	if(sscanf(params, "i", otherid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/makektp [ID/Name]");
	if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi di server!");
	if(!IsPlayerNearPlayer(playerid, otherid, 3.5)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan pemain tersebut!");
	if(AccountData[otherid][pHasKTP]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sudah memiliki KTP!");

	AccountData[otherid][pHasKTP] = true;
    AccountData[otherid][pKTPTime] = gettime() + (7 * 86400);
	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Pembuatan KTP berhasil dilakukan.");
	ShowTDN(otherid, NOTIFICATION_INFO, "Anda telah diberikan KTP oleh petugas pemerintah.");
	return 1;
}

YCMD:givelic(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] != FACTION_SAGOV && AccountData[playerid][pFaction] != FACTION_LSPD) return SEM(playerid, "Anda bukan anggota Pemerintah / Polisi!");

    new otherid;
    if (sscanf(params, "d", otherid))
        return SUM(playerid, "/givelic [playerid]");
    if (!IsPlayerConnected(otherid) && !AccountData[otherid][pSpawned])
        return SEM(playerid, "Pemain tidak terkoneksi/belum spawn!");
    if (!IsPlayerNearPlayer(playerid, otherid, 2.0))
        return SEM(playerid, "Pemain tersebut tidak dekat dengan anda!");

    if(AccountData[playerid][pFaction] == FACTION_SAGOV)
    {
        if(AccountData[playerid][pFactionRank] < 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Staff Senior untuk akses ini!");

        if(!IsPlayerInRangeOfPoint(playerid, 3.0, 1373.4606,1597.7161,15.6703))
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di tempat yang seharusnya!");

        Dialog_Show(playerid, "GiveLic", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- "WHITE"Terbitkan Lisensi", 
        "Surat Izin Berlayar\n\
        Surat Izin Helikopter\n\
        Surat Izin Pesawat", "Pilih", "Batal");
    }
    else if(AccountData[playerid][pFaction] == FACTION_LSPD)
    {
        if(!IsPlayerInRangeOfPoint(playerid, 3.0, 944.0831,2447.8220,10.9001))
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di tempat yang seharusnya!");

        Dialog_Show(playerid, "GiveLic2", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- "WHITE"Terbitkan Lisensi", 
        "SIM A\n\
		SIM B\n\
		SIM C\n\
        Kartu Izin Berburu\n\
        Kartu Izin Senjata Api", "Pilih", "Batal");
    }

    AccountData[playerid][pTempValue2] = otherid;
    return 1;
}

YCMD:makeskwb(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] != FACTION_SAGOV) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Pemerintah Pahlawan Roleplay!");

    if(AccountData[playerid][pFactionRank] < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Staff Junior untuk akses ini!");
    
    if(!IsPlayerInRangeOfPoint(playerid, 3.0, 1373.4606,1597.7161,15.6703))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di tempat yang seharusnya!");

    static targetid, duration, text[64], esxs[512];
    if(sscanf(params, "ids[64]", targetid, duration, text))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/makeskwb [playerid] [expired] [note]");
    
    if(!IsPlayerConnected(targetid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke dalam server!");

    if(!AccountData[targetid][pSpawned])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut belum spawn!");

    if(!IsPlayerNearPlayer(playerid, targetid, 2.5)) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak dekat dengan anda!");

    if(DocumentInfo[targetid][SKWB])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sudah memiliki SKWB!");

    if(duration < 1 || duration > 7)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Expired SKWB tidak valid (1 - 7 hari)");
    
    DocumentInfo[targetid][SKWB] = true;
    DocumentInfo[targetid][SKWBDur] = gettime() + (duration * 86400);
    strcopy(DocumentInfo[targetid][SKWBText], text);
    strcopy(DocumentInfo[targetid][SKWBIssuer], GetPlayerRoleplayName(playerid));
    strcopy(DocumentInfo[targetid][SKWBIssuerRank], GetRankName(playerid));
    strcopy(DocumentInfo[targetid][SKWBIssueDate], GetAdvTime());

    mysql_format(g_SQL, esxs, sizeof(esxs), "INSERT INTO `documents` SET `Owner_ID` = %d, `Type` = 4, `SKWB_Dur` = %d, `SKWB_Text` = '%e', `SKWB_Issuer` = '%e', `SKWB_IssuerRank` = '%e', `SKWB_IssueDate` = '%e'",
    AccountData[targetid][pID], DocumentInfo[targetid][SKWBDur], DocumentInfo[targetid][SKWBText], DocumentInfo[targetid][SKWBIssuer], DocumentInfo[targetid][SKWBIssuerRank], DocumentInfo[targetid][SKWBIssueDate]);
    mysql_pquery(g_SQL, esxs);

    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Pembuatan SKWB telah berhasil dilakukan");
    ShowTDN(targetid, NOTIFICATION_INFO, "Anda telah dibuatkan SKWB oleh petugas.");
    return 1;
}