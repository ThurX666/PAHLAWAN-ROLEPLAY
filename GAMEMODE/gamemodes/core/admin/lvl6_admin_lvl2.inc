YCMD:setjob(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 6)
	    return PermissionError(playerid);

    new otherid, jobid;
    if(sscanf(params, "id", otherid, jobid)) return SUM(playerid, "/setjob [playerid] [jobid]");

    if(!IsPlayerConnected(otherid) && !AccountData[otherid][IsLoggedIn])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    if(jobid < JOB_NONE || jobid > JOB_TAILOR) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Job ID!");

    AccountData[otherid][pJob] = jobid;
    SendAdm(playerid, "Anda telah mengubah job %s jadi %s.", AccountData[otherid][pName], GetJobName(otherid));
    SendAdm(otherid, "%s telah mengubah job anda jadi %s.", AccountData[playerid][pAdminname], GetJobName(otherid));
    return 1;
}

YCMD:oban(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 6)
        return PermissionError(playerid);

    new player[24], datez, reason[64];
    if (sscanf(params, "s[24]D(0)s[64]", player, datez, reason))
        return SUM(playerid, "/oban [name] [days (0 for permanent ban)] [reason]");

    if (strlen(reason) > 32) return ShowTDN(playerid, NOTIFICATION_ERROR, "Maksimum reason adalah 32 karakter!");

    foreach (new ii : Player)
    {
        new PlayerName[24];
        GetPlayerName(ii, PlayerName, MAX_PLAYER_NAME);

        if (strfind(PlayerName, player, true) != -1)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sedang online, gunakan '/ban'.");
    }

    new query[128];

    mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `player_characters` WHERE `Char_Name`='%e'", player);
    mysql_pquery(g_SQL, query, "OnOBanQueryData", "issi", playerid, player, reason, datez);
    return true;
}

YCMD:oresetweap(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 6)
        return PermissionError(playerid);

    new player[24], PlayerName[MAX_PLAYER_NAME];
    if (sscanf(params, "s[24]", player))
        return SUM(playerid, "/oresetweap [name]");

    foreach (new ii : Player)
    {
        GetPlayerName(ii, PlayerName, MAX_PLAYER_NAME);

        if (strfind(PlayerName, player, true) != -1)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sedang online, gunakan '/resetweap' terhadapnya!");
    }

    new query[512];
    mysql_format(g_SQL, query, sizeof(query), "SELECT `pID` FROM `player_characters` WHERE `Char_Name`='%e'", player);
    mysql_pquery(g_SQL, query, "OResetWeapon", "is", playerid, player);
    return 1;
}

YCMD:torture(playerid, params[], help)
{
    new otherid, Float:otheridpos[3];
    if(AccountData[playerid][pAdmin] < 6)
        return PermissionError(playerid);

    if(sscanf(params, "d", otherid)) return SUM(playerid, "/torture [playerid]");

    if (!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    if (otherid == playerid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya terhadap diri sendiri!");

    if (!AccountData[playerid][pSpawned] || !AccountData[otherid][pSpawned])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda/Pemain tersebut belum spawn!");

    AccountData[otherid][pTortured] = true;
    Anticheat[otherid][acImmunity] = gettime() + 5;
    SetPlayerPos(otherid, 10.00, -10.00, 9999999999.99);
    GetPlayerPos(otherid, otheridpos[0], otheridpos[1], otheridpos[2]);

    SendAdm(playerid, "You have inflicted torture on %s(%d).", AccountData[otherid][pName], otherid);

    static string[144];
    format(string, sizeof(string), "AdmCmd: You have been tortured by %s.", AccountData[playerid][pAdminname]);
	SendClientMessage(otherid, Y_LIGHTRED, string);
    return 1;
}

YCMD:ann(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 6)
        return PermissionError(playerid);

    new judul[64], desk[144];
    if (sscanf(params, "s[64]s[144]", judul, desk))
        return SUM(playerid, "/ann [judul] [deskripsi]");

    if(strlen(judul) < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Judul minimal 4 huruf!");
    if(strlen(desk) < 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Deskripsi minimal 10 huruf!");

    // Check for special trouble-making input
    if (strfind(params, "~x~", true) != -1)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Simbol '~x~' tidak dapat digunakan!");

    if (strfind(params, "#k~", true) != -1)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Constant Keys tidak dapat digunakan!");

    if (strfind(params, "/q", true) != -1)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menggunakan /q di announcement!");

    // Count tildes (uneven number = faulty input)
    new iTemp = 0;
    for (new i = (strlen(params) - 1); i != -1; i--)
    {
        if (params[i] == '~')
            iTemp++;
    }
    if (iTemp % 2 == 1)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda membuat/menghilangkan extra ~ di announce!");
    
    foreach(new i : Player) if(AccountData[i][pSpawned])
    {
        ShowAnnounceTD(i, judul, desk);
    }

    SetTimer("CloseAnnounceTD", 7500, false);
    return true;
}

YCMD:sethbe(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 6)
        return PermissionError(playerid);

    new amount, otherid;
    if (sscanf(params, "ud", otherid, amount))
        return SUM(playerid, "/sethbe [playerid id/name] [amount]");

    if (!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    if (amount < 0 || amount > 100)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid!");

    AccountData[otherid][pHunger] = amount;
    AccountData[otherid][pThirst] = amount;

    static string[215];
    mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_Hunger` = %d, `Char_Thirst` = %d WHERE `pID` = %d", amount, amount, AccountData[otherid][pID]);
    mysql_pquery(g_SQL, string);

    SetPlayerDrunkLevel(otherid, 0);
    SendAdm(playerid, "You have set HBE for %s to %d.", AccountData[otherid][pName], amount);

    format(string, sizeof(string), "AdmCmd: %s has set your character's HBE to %d.", AccountData[playerid][pAdminname], amount);
    SendClientMessage(otherid, Y_LIGHTRED, string);

    return 1;
}

YCMD:setstress(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 6)
        return PermissionError(playerid);

    new amount, otherid;
    if (sscanf(params, "ud", otherid, amount))
        return SUM(playerid, "/setstress [playerid id/name] [amount]");

    if (!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    AccountData[otherid][pStress] = amount;

    static string[215];
    mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_Stress` = %d WHERE `pID` = %d", amount, AccountData[otherid][pID]);
    mysql_pquery(g_SQL, string);

    SetPlayerDrunkLevel(otherid, 0);
    SendAdm(playerid, "You have set stress for %s to %d.", AccountData[otherid][pName], amount);
    
    format(string, sizeof(string), "AdmCmd: %s has set your character's stress to %d.", AccountData[playerid][pAdminname], amount);
    SendClientMessage(otherid, Y_LIGHTRED, string);

    return 1;
}

YCMD:makequiz(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 6)
        return PermissionError(playerid);

    static tmp[128], string[256], str[256], pr;

    if (sscanf(params, "s[128]S()[256]", tmp, string))
    {
        SUM(playerid, "/makequiz [type] (question, answer, price, end)");
        SendClientMessage(playerid, X11_GRAY, "NOTE: Please prepare your response first!");
        return 1;
    }

    if (!strcmp(tmp, "question", true))
    {
        if (sscanf(string, "s[256]", str))
            return SUM(playerid, "/makequiz question [question]");
        if (quiz)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Quiz telah dimulai, gunakan '/makequiz end' untuk mengakhiri!");
        if (!answermade)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Mohon siapkan jawaban terlebih dahulu!");
        if (qprs == 0)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Mohon siapkan hadiah terlebih dahulu!");

        SendClientMessageToAllEx(Y_SERVER, "(Quiz) "WHITE"Admin "RED"%s "WHITE"has started the quiz.", AccountData[playerid][pAdminname]);
        SendClientMessageToAllEx(-1, "~> Soal: %s", str);
        SendClientMessageToAllEx(-1, "~> Hadiah: "DARKGREEN"$%s.", FormatMoney(qprs));
        SendClientMessageToAll(-1, "Gunakan "CMDEA"'/qa' "WHITE"to answer!");
        quiz = true;
    }
    else if (!strcmp(tmp, "answer", true))
    {
        if (sscanf(string, "s[256]", str))
            return SUM(playerid, "/makequiz answer [answer]");
        if (quiz)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Quiz telah dimulai, gunakan '/makequiz end' untuk mengakhiri!");
        strcopy(answers, str);
        answermade = true;
        format(string, sizeof(string), "[Quiz] You have answered, "YELLOW"%s", str);
        SendClientMessage(playerid, -1, string);
    }
    else if (!strcmp(tmp, "price", true))
    {
        if (sscanf(string, "d", pr))
            return SUM(playerid, "/makequiz price [amount]");
        if (quiz)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Quiz telah dimulai, gunakan '/makequiz end' untuk mengakhiri!");
        if (!answermade)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Mohon siapkan jawaban terlebih dahulu!");
        if (pr <= 0)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Mohon siapkan hadiah terlebih dahulu!");
        qprs = pr;
        format(string, sizeof(string), "[Quiz] You have set the quiz prize to "DARKGREEN"$%s.", FormatMoney(pr));
        SendClientMessage(playerid, -1, string);
    }
    else if (!strcmp(tmp, "end", true))
    {
        if (!quiz)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada quiz yang sedang berjalan!");
        SendClientMessageToAllEx(-1, "[Quiz] Admin "RED"%s has closed the quiz!", AccountData[playerid][pAdminname]);
        answermade = false;
        quiz = false;
        qprs = 0;
        answers[0] = EOS;
    }
    return 1;
}

YCMD:vote(playerid, params[], help)
{
    new type[24], string[128];
    if (sscanf(params, "s[24]S()[128]", type, string))
        return SUM(playerid, "/vote [type]~n~create, yes, no");

    if (!strcmp(type, "create", true))
    {
        if(AccountData[playerid][pAdmin] < 6)
            return PermissionError(playerid);

        if (VoteInfo[voteStarted])
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Voting sudah dimulai!");

        new name[128];

        if (sscanf(string, "s[128]", name))
            return SUM(playerid, "/vote [create] [voting title]");

        VoteInfo[voteText][0] = EOS;
        VoteInfo[voteYes] = 0;
        VoteInfo[voteNo] = 0;

        VoteInfo[voteStarted] = true;
        VoteInfo[voteTime] = gettime() + 60;

        strcopy(VoteInfo[voteText], name);
        SendClientMessageToAllEx(Y_WHITE, "[Vote] "YELLOW"%s.", VoteInfo[voteText]);
        SendClientMessageToAllEx(Y_WHITE, "~> "RED"%s "WHITE"memulai voting, gunakan "YELLOW"'/vote yes' "WHITE"atau "YELLOW"'/vote no' "WHITE"untuk berpartisipasi.", AccountData[playerid][pAdminname]);
    }
    else if (!strcmp(type, "yes", true))
    {
        if (!VoteInfo[voteStarted])
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada voting yang sedang berlangsung!");

        if (AccountData[playerid][pVoted])
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah berpartisipasi dalam voting!");

        AccountData[playerid][pVoted] = true;
        VoteInfo[voteYes]++;

        ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah melakukan vote.");
    }
    else if (!strcmp(type, "no", true))
    {
        if (!VoteInfo[voteStarted])
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada voting yang sedang berlangsung!");

        if (AccountData[playerid][pVoted])
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah berpartisipasi dalam voting!");

        AccountData[playerid][pVoted] = true;
        VoteInfo[voteNo]++;

        ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah melakukan vote.");
    }
    return 1;
}