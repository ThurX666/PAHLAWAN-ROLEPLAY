YCMD:banip(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 8)
        return PermissionError(playerid);

    new iptoban[17];

    if (sscanf(params, "s[17]", iptoban))
        return SUM(playerid, "/banip [IP Address]");

    if(strfind(iptoban, "*", true) != -1 && AccountData[playerid][pAdmin] != 5)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat ban range IP!");

    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s banned IP Address %s.", AccountData[playerid][pAdminname], iptoban);

    new tstr[128];
    format(tstr, sizeof(tstr), "banip %s", iptoban);
    SendRconCommand(tstr);
    return 1;
}

YCMD:blockucp(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 8)
        return PermissionError(playerid);

    new nameucp[22], haridur, reasonblock[60], totalblockdur;
    if (sscanf(params, "s[22]ds[60]", nameucp, haridur, reasonblock))
        return SUM(playerid, "/blockucp [UCP Name] [duration (days) 0 for permanent] [reason]");

    if (haridur < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Mohon masukkan durasi yang valid!");

    if (strlen(reasonblock) > 60) return ShowTDN(playerid, NOTIFICATION_ERROR, "Maksimum reason adalah 60 karakter!");

    if (haridur != 0)
    {
        totalblockdur = gettime() + (haridur * 86400);
    }
    else
    {
        totalblockdur = haridur;
    }

    new query[128];
    mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `player_ucp` WHERE `UCP` = '%e'", nameucp);
    mysql_pquery(g_SQL, query, "OnBlockingUCP", "isdds", playerid, nameucp, totalblockdur, haridur, reasonblock);
    return 1;
}

YCMD:areviveall(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 8)
        return PermissionError(playerid);

    static frmtsql[215];

    foreach (new i : Player)
    {
        if (AccountData[playerid][pSpawned])
        {
            if (AccountData[i][pKnockdown])
            {
                HideKnockTD(i);
                SetPlayerHealthEx(i, 100.0);
                AccountData[i][pKnockdown] = false;
                AccountData[i][pKnockdownTime] = 0;
                AccountData[i][pHunger] = 50;
                AccountData[i][pThirst] = 50;
                AccountData[i][pStress] = 0;

                DeathCause[i][Bruised] = false;
                DeathCause[i][Shoted] = false;
                DeathCause[i][Burns] = false;
                DeathCause[i][Drown] = false;
                DeathCause[i][Fallen] = false;

                mysql_format(g_SQL, frmtsql, sizeof(frmtsql), "UPDATE `player_characters` SET `Char_Knockdown` = 0, `Char_KnockdownTime` = 0, `Char_Hunger` = 50, `Char_Thirst` = 50 WHERE `pID` = %d", AccountData[i][pID]);
                mysql_pquery(g_SQL, frmtsql);

                StopRunningAnimation(i);
            }
            format(frmtsql, sizeof(frmtsql), "AdmCmd: %s has revived all players.", AccountData[playerid][pAdminname]);
            SendClientMessage(i, Y_LIGHTRED, frmtsql);
        }
    }

    return 1;
}

YCMD:sethpall(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 8)
        return PermissionError(playerid);

    new Float:amount;
    if (sscanf(params, "f", amount))
        return SUM(playerid, "/sethpall [amount]");

    static frmtsql[215];
    foreach (new i : Player)
    {
        if (IsPlayerConnected(i))
        {
            if (AccountData[i][pSpawned])
            {
                AccountData[i][pHealth] = amount;

                mysql_format(g_SQL, frmtsql, sizeof(frmtsql), "UPDATE `player_characters` SET `Char_Health` = '%.3f' WHERE `pID` = %d", amount, AccountData[i][pID]);
                mysql_pquery(g_SQL, frmtsql);

                SetPlayerHealthEx(i, amount);

                format(frmtsql, sizeof(frmtsql), "AdmCmd: %s has set the health of all characters to %.2f.", AccountData[playerid][pAdminname], amount);
                SendClientMessage(i, Y_LIGHTRED, frmtsql);
            }
        }
    }

    return 1;
}

YCMD:unban(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 8)
        return PermissionError(playerid);

    new tmp[24];
    if (sscanf(params, "s[24]", tmp))
        return SUM(playerid, "/unban [name]");

    new query[128];
    mysql_format(g_SQL, query, sizeof(query), "SELECT `name`,`ip` FROM `player_bans` WHERE `name` = '%e'", tmp);
    mysql_pquery(g_SQL, query, "OnUnbanQueryData", "is", playerid, tmp);
    return 1;
}

YCMD:unblockucp(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 8)
        return PermissionError(playerid);

    new ucpname[22];
    if (sscanf(params, "s[22]", ucpname))
        return SUM(playerid, "/unblockucp [UCP name]");

    new query[128];
    mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `player_ucp` WHERE `UCP` = '%e'", ucpname);
    mysql_pquery(g_SQL, query, "OnUnblockUCP", "is", playerid, ucpname);
    return 1;
}

YCMD:unbanip(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 8)
        return PermissionError(playerid);

    if (isnull(params))
        return SUM(playerid, "/unbanip [IP Address]");

    new mstr[128];
    format(mstr, sizeof(mstr), "unbanip %s", params);
    SendRconCommand(mstr);
    format(mstr, sizeof(mstr), "reloadbans");
    SendRconCommand(mstr);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has unbanned the IP %s.", AccountData[playerid][pAdminname], params);

    return 1;
}

YCMD:explode(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 8)
        return PermissionError(playerid);

    new Float:POS[3], otherid, giveplayer[24];
    if (sscanf(params, "d", otherid))
        return SUM(playerid, "/explode [playerid]");

    if (!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    GetPlayerName(otherid, giveplayer, sizeof(giveplayer));

    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has exploded %s(%d).",  AccountData[playerid][pAdminname], AccountData[otherid][pName], otherid);

    GetPlayerPos(otherid, POS[0], POS[1], POS[2]);
    CreateExplosion(POS[0], POS[1], POS[2], 7, 5.0);
    return 1;
}

/*
YCMD:setadminname(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 8)
		return PermissionError(playerid);
	
	new aname[128], otherid, query[128];
	if(sscanf(params, "us[128]", otherid, aname))
	   	return SUM(playerid, "/setadminname [ID/Name] [admin name]");
	
	mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `player_characters` WHERE `Char_AdminName`='%e' AND `Char_UCP` != '%e'", aname, AccountData[otherid][pUCP]);
	mysql_pquery(g_SQL, query, "CNAdmName", "iis", otherid, playerid, aname);
	return 1;
}
YCMD:setaname(playerid, params[], help) = setadminname;
*/

YCMD:togspy(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 8)
		return PermissionError(playerid);

	switch(AccountData[playerid][pSPY])
	{
		case false:
		{
			AccountData[playerid][pSPY] = true;
			ShowTDN(playerid, NOTIFICATION_INFO, "SPY mode ~g~aktif.");
		}
		case true:
		{
			AccountData[playerid][pSPY] = false;
			ShowTDN(playerid, NOTIFICATION_INFO, "SPY mode ~r~tidak aktif.");
		}
	}
	return 1;
}

YCMD:setname(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 8)
        return PermissionError(playerid);

    new targetid;
    if (sscanf(params, "d", targetid))
        return SUM(playerid, "/setname [ID/Name]");

    if (!IsPlayerConnected(targetid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    
    if (!AccountData[targetid][IsLoggedIn])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    AccountData[playerid][pTempSQLFactMemberID] = targetid;
    Dialog_Show(playerid, "AdmSetName", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Change Name", ""WHITE"Mohon masukkan nama baru karakter di bawah ini (Kultur Server ini adalah Indonesia)\n\
    Nama bisa apa saja asalkan tidak mengandung kata kotor, singkatan, atau nama publik figur/terkenal\n\n\
    Contoh nama yang baik: Asep_Sutanto, Christina_Agnes, Iskak_Syueb, Fadil_Siregar:", "Input", "Kembali");

    return 1;
}

YCMD:reco(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 8)
		return PermissionError(playerid);
		
	new otherid;
	if(sscanf(params, "i", otherid))
	    return SUM(playerid, "/reco [playerid]");

    if(!IsPlayerConnected(otherid) && !AccountData[otherid][IsLoggedIn])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	
	ResetPlayerMoneyEx(otherid);
	AccountData[otherid][pBankMoney] = 0;
	AccountData[otherid][pCasinoChip] = 0;

	new sqlsdwadkw[128];
	mysql_format(g_SQL, sqlsdwadkw, sizeof(sqlsdwadkw), "UPDATE `player_characters` SET `Char_Money` = 0, `Char_BankMoney` = 0, `Char_CasinoChip` = 0 WHERE `pID` = %d", AccountData[otherid][pID]);
	mysql_pquery(g_SQL, sqlsdwadkw);
	
	SendAdm(otherid, "%s has reset your character economy!", AccountData[playerid][pAdminname]);
	SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has reset character economy %s(%d).",  AccountData[playerid][pAdminname], AccountData[otherid][pName], otherid);
	
	//format(sclstr, sizeof(sclstr), "%s(%d) [%s] menggunakan CMD '/givebankmoney'\n
	//> menambah saldo bank milik %s(%d) [%s] dengan jumlah $%s", AccountData[playerid][pAdminname], playerid, AccountData[playerid][pUCP], AccountData[otherid][pName], otherid, AccountData[otherid][pUCP], FormatMoney(money));
	//CallLocalFunction("StaffCommandLog", "is", playerid, sclstr);
	return 1;
}

YCMD:setlevel(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 8)
        return PermissionError(playerid);
	
	new amount, otherid;
	if(sscanf(params, "dd", otherid, amount))
        return SUM(playerid, "/setlevel [playerid] [level]");
	
	if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Level tidak dapat kurang dari 1!");

	if(!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
		
	AccountData[otherid][pLevel] = amount;
	AccountData[otherid][pHours] = (AccountData[otherid][pLevel] - 1)*5;
	AccountData[otherid][pMinutes] = 0;
	AccountData[otherid][pSeconds] = 0;
	
    static string[215];
	mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_Level` = %d WHERE `pID` = %d", amount, AccountData[otherid][pID]);
    mysql_pquery(g_SQL, string);

	SetPlayerScore(otherid, amount);
	SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has set the level of %s to %d.", AccountData[playerid][pAdminname], AccountData[otherid][pName], amount);
	format(string, sizeof(string), "AdmCmd: %s has set your character's level to %d.", AccountData[playerid][pAdminname], amount);
	SendClientMessage(otherid, Y_LIGHTRED, string);

	return 1;
}

YCMD:konser(playerid, params[], help)
{
	if(AccountData[playerid][pAdmin] < 8)
		return PermissionError(playerid);

	Dialog_Show(playerid, "KonserList", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Konser",
	"Mulai Konser\nStop Konser\nSiti Nurbaya\nSeparuh Nafas\nSelir Hati\nSelimut Hati\nSedang Ingin Bercinta\nRoman Picisan\n\
	Risalah Hati\nPupus\nPerempuan Paling Cantik\nPangeran Cinta\nMunajat Cinta\nMadu Tiga\nLaskar Cinta\nKirana\nKangen\nKamulah Surgaku\nKamulah Satu\n\
	Elang\nDewi\nAngin\nAku Milikmu", "Pilih", "Batal");
	return 1;
}

YCMD:goodmood(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 8)
        return PermissionError(playerid);

    SetPlayerHealthEx(playerid, 100.0);
    AccountData[playerid][pHunger] = 100;
    AccountData[playerid][pThirst] = 100;
    AccountData[playerid][pStress] = 0;

    SendClientMessage(playerid, Y_LIGHTRED, "AdmCmd: You used the '/goodmood' command.");
    return 1;
}