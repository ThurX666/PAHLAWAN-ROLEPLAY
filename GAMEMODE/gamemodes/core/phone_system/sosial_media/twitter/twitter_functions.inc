#include <YSI_Coding\y_hooks>

enum e_twitterdetails
{
    OwnerID,
    Username[24],
    Password[32],

    //not save
    TempUsername[24],
    TempPassword[32],
    Tweet[128]
};
new TwitterData[MAX_PLAYERS][e_twitterdetails];

forward OnTwitterRegister(playerid, const userinput[]);
public OnTwitterRegister(playerid, const userinput[])
{
    if(cache_num_rows() > 0)
    {
        Dialog_Show(playerid, "TwitterRegister", DIALOG_STYLE_INPUT, 
        "{DA9100}Pahlawan Roleplay "WHITE"- Daftar Twitter", 
        "Mohon maaf, username tersebut sudah terdaftar!\n\
        Silakan masukkan username Twitter kamu, ini akan ditampilkan pada setiap tweet yang kamu buat:\n\
        Ingat: Username hanya dapat berupa huruf dan angka, tidak menggunakan simbol!", "Set", "Batal");
        return 1;
    }
    else
    {
        new strtwt[150];
        mysql_format(g_SQL, strtwt, sizeof(strtwt), "INSERT INTO `player_twitter` SET `OwnerID`=%d, `Username`='%e'", AccountData[playerid][pID], userinput);
        mysql_pquery(g_SQL, strtwt, "OnTwitterUsernameSuccess", "is", playerid, userinput);
    }
    return 1;
}

forward OnTwitterUsernameSuccess(playerid, const usersuccs[]);
public OnTwitterUsernameSuccess(playerid, const usersuccs[])
{
    new jjstr[250];
    format(jjstr, sizeof(jjstr), 
    "Hai, %s!\n\
    Silakan masukkan kata sandi untuk akun twitter kamu:\n\
    Ingat: Panjang kata sandi 7 - 32 karakter!\n\
    Tahap ini tidak dapat dibatalkan!", usersuccs);
    Dialog_Show(playerid, "TwitterRegPassword", DIALOG_STYLE_PASSWORD, "{DA9100}Pahlawan Roleplay "WHITE"- Daftar Twitter", jjstr, "Set", "");
    return 1;
}

forward OnTwitterFinishRegister(playerid);
public OnTwitterFinishRegister(playerid)
{
    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mendaftarkan akun Twitter, silakan login!");
    return 1;
}

forward OnTwitterLogin(playerid, const checkuser[]);
public OnTwitterLogin(playerid, const checkuser[])
{
    if(cache_num_rows() > 0)
    {
        new ljstr[250];
        format(ljstr, sizeof(ljstr), "Hai, %s!\n\
        Silakan masukkan kata sandi akun Twitter kamu untuk masuk:", checkuser);
        Dialog_Show(playerid, "TwitterLoginPassword", DIALOG_STYLE_PASSWORD, 
        "{DA9100}Pahlawan Roleplay "WHITE"- Login Twitter", ljstr, "Login", "Batal");
        return 1;
    }
    else
    {
        Dialog_Show(playerid, "TwitterLogin", DIALOG_STYLE_INPUT, 
        "{DA9100}Pahlawan Roleplay "WHITE"- Login Twitter", 
        "Mohon maaf kami tidak dapat menemukan akun Twitter kamu!\n\
        Silakan masukkan username Twitter kamu yang telah terdaftar:", "Input", "Batal");
    }
    return 1;
}

forward OnPlayerTweet(playerid);
public OnPlayerTweet(playerid)
{
    PlayerPhoneData[playerid][CurrentlyReadTweet] = true;
    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membuat sebuah tweet!");
    mysql_query(g_SQL, "SELECT * FROM `tweets` WHERE `ID`=1 ORDER BY `TweetDate` ASC LIMIT 30");
    new rowcount = cache_num_rows(), tempTweetFrom[24], tempTweets[128], tempTweetDate[128], lists[2500];
    if(rowcount)
    {
        if(rowcount >= 30)
        {
            mysql_pquery(g_SQL, "DELETE FROM `tweets` WHERE `ID`=1");
        }

        format(lists, sizeof(lists), "Username\tTanggal\tTweets\n");
        for(new x; x < rowcount; ++x)
        {
            cache_get_value_name(x, "TweetFrom", tempTweetFrom);
            cache_get_value_name(x, "TweetMessage", tempTweets);
            cache_get_value_name(x, "TweetDate", tempTweetDate);
            format(lists, sizeof(lists), "%s{1DA1F2}@%s\t{AAB8C2}%s\t"WHITE"%s\n", lists, tempTweetFrom, tempTweetDate, tempTweets);
        }

        foreach(new i : Player)
        {
            if(PlayerPhoneData[i][CurrentlyReadTweet])
            {
                Dialog_Show(i, "PhoneTweets", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Twitter", 
                lists, "Tweet", "Batal");
            }
        }
        return 1;
    }
    else
    {
        Dialog_Show(playerid, "PhoneTweets", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Twitter", 
        "Username\tTweets\nBelum ada Tweet yang dapat ditampilkan kepadamu!", "Tweet", "Batal");
    }
    return 1;
}

Dialog:TwitterRegister(playerid, response, listitem, inputtext[])
{
    new sqlfstr[128];
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    if(isnull(inputtext))
    {
        Dialog_Show(playerid, "TwitterRegister", DIALOG_STYLE_INPUT, 
        "{DA9100}Pahlawan Roleplay "WHITE"- Daftar Twitter", 
        "Username Tidak dapat dikosongkan!\n\
        Silakan masukkan username Twitter kamu, ini akan ditampilkan pada setiap tweet yang kamu buat:\n\
        Ingat: Username hanya dapat berupa huruf dan angka, tidak menggunakan simbol!\n\
        Panjang username 7 - 24 karakter!", "Set", "Batal");
        return 1;
    }

    if(strlen(inputtext) < 7 || strlen(inputtext) > 24)
    {
        Dialog_Show(playerid, "TwitterRegister", DIALOG_STYLE_INPUT, 
        "{DA9100}Pahlawan Roleplay "WHITE"- Daftar Twitter", 
        "Username Tidak dapat dikosongkan!\n\
        Silakan masukkan username Twitter kamu, ini akan ditampilkan pada setiap tweet yang kamu buat:\n\
        Ingat: Username hanya dapat berupa huruf dan angka, tidak menggunakan simbol!\n\
        Panjang username 7 - 24 karakter!", "Set", "Batal");
        return 1;
    }

    strcopy(TwitterData[playerid][TempUsername], inputtext);
    mysql_format(g_SQL, sqlfstr, sizeof(sqlfstr), "SELECT * FROM `player_twitter` WHERE `Username`='%e'", TwitterData[playerid][TempUsername]);
    mysql_pquery(g_SQL, sqlfstr, "OnTwitterRegister", "is", playerid, TwitterData[playerid][TempUsername]);
    return 1;
}
Dialog:TwitterRegPassword(playerid, response, listitem, inputtext[])
{
    new sqlfstr[250];
    if(!response)
    {
        format(sqlfstr, sizeof(sqlfstr), "Hai, %s!\n\
        Silakan masukkan kata sandi untuk akun twitter kamu:\n\
        Ingat: Panjang kata sandi 7 - 32 karakter!\n\
        Tahap ini tidak dapat dibatalkan!", TwitterData[playerid][TempUsername]);
        Dialog_Show(playerid, "TwitterRegPassword", DIALOG_STYLE_PASSWORD, 
        "{DA9100}Pahlawan Roleplay "WHITE"- Daftar Twitter", sqlfstr, "Set", "");
        return 1;
    }

    if(isnull(inputtext))
    {
        Dialog_Show(playerid, "TwitterRegPassword", DIALOG_STYLE_PASSWORD, 
        "{DA9100}Pahlawan Roleplay "WHITE"- Daftar Twitter", 
        "Kata sandi Tidak dapat dikosongkan!\n\
        Silakan masukkan kata sandi untuk akun twitter kamu:\n\
        Ingat: Panjang kata sandi 7 - 32 karakter!\n\
        Tahap ini tidak dapat dibatalkan!", "Set", "");
        return 1;
    }

    if(strlen(inputtext) < 7 || strlen(inputtext) > 32)
    {
        Dialog_Show(playerid, "TwitterRegPassword", DIALOG_STYLE_PASSWORD, 
        "{DA9100}Pahlawan Roleplay "WHITE"- Daftar Twitter", 
        "Panjang kata sandi kurang atau kelebihan!\n\
        Silakan masukkan kata sandi untuk akun twitter kamu:\n\
        Ingat: Panjang kata sandi 7 - 32 karakter!\n\
        Tahap ini tidak dapat dibatalkan!", "Set", "");
        return 1;
    }

    strcopy(TwitterData[playerid][TempPassword], inputtext);
    mysql_format(g_SQL, sqlfstr, sizeof(sqlfstr), "UPDATE `player_twitter` SET `Password`='%e' WHERE `Username`='%e'", TwitterData[playerid][TempPassword], TwitterData[playerid][TempUsername]);
    mysql_pquery(g_SQL, sqlfstr, "OnTwitterFinishRegister", "i", playerid);
    return 1;
}
Dialog:TwitterLogin(playerid, response, listitem, inputtext[])
{
    new sqlfstr[128];
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    strcopy(TwitterData[playerid][TempUsername], inputtext);
    mysql_format(g_SQL, sqlfstr, sizeof(sqlfstr), "SELECT * FROM `player_twitter` WHERE `Username`='%e'", TwitterData[playerid][TempUsername]);
    mysql_pquery(g_SQL, sqlfstr, "OnTwitterLogin", "is", playerid, TwitterData[playerid][TempUsername]);
    return 1;
}
Dialog:TwitterLoginPassword(playerid, response, listitem, inputtext[])
{
    new sqlfstr[128], twdbid;
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    strcopy(TwitterData[playerid][TempPassword], inputtext);
    mysql_format(g_SQL, sqlfstr, sizeof(sqlfstr), "SELECT * FROM `player_twitter` WHERE `Username`='%e' AND `Password`='%e'", TwitterData[playerid][TempUsername], TwitterData[playerid][TempPassword]);
    mysql_query(g_SQL, sqlfstr);
    new rows = cache_num_rows();
    if(rows)
    {
        cache_get_value_name_int(0, "ID", twdbid);
        cache_get_value_name(0, "Username", TwitterData[playerid][Username]);
        PlayerPhoneData[playerid][IsTwitterLoggedIn] = twdbid;
        mysql_format(g_SQL, sqlfstr, sizeof(sqlfstr), "UPDATE `player_phones` SET `TwitterLoggedIn`=%d WHERE `phoneOwner`=%d", twdbid, AccountData[playerid][pID]);
        mysql_pquery(g_SQL, sqlfstr);
        PlayerTextDrawSetString(playerid, TwitterInfoTD[playerid], sprintf("Hai, %s bagaimana harimu?", TwitterData[playerid][Username]));
        HideTwitterTD(playerid);
        ShowTwitterMainTD(playerid);
    }
    else
    {
        new ljstr[250];
        format(ljstr, sizeof(ljstr), "Hai, %s!\n\
        Kata sandi yang kamu masukkan salah!\n\
        Silakan masukkan kata sandi akun Twitter kamu untuk masuk:", TwitterData[playerid][TempUsername]);
        Dialog_Show(playerid, "TwitterLoginPassword", DIALOG_STYLE_PASSWORD, 
        "{DA9100}Pahlawan Roleplay "WHITE"- Login Twitter", ljstr, "Login", "Batal");
    }
    return 1;
}
Dialog:PhoneTweets(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        PlayerPhoneData[playerid][CurrentlyReadTweet] = false;
        return 1;
    }

    PlayerPhoneData[playerid][CurrentlyReadTweet] = false;
    Dialog_Show(playerid, "TwitterTweeting", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Twitter", 
    "Silahkan masukkan tweet yang ingin kamu buat:", "Tweet", "Batal");
    return 1;
}
Dialog:TwitterTweeting(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    if(isnull(inputtext))
    {
        return Dialog_Show(playerid, "TwitterTweeting", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Twitter", 
        "Tweet tidak boleh diisi kosong!\n\
        Silahkan masukkan tweet yang ingin kamu buat:", "Tweet", "Batal");
    }

    if(strlen(inputtext) > 128)
    {
        return Dialog_Show(playerid, "TwitterTweeting", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Twitter", 
        "Tweet maksimal 128 karakter!\n\
        Silahkan masukkan tweet yang ingin kamu buat:", "Tweet", "Batal");
    }

    if(strfind(inputtext, "%", true) != -1 || strfind(inputtext, "#", true) != -1)  return Dialog_Show(playerid, "TwitterTweeting", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Twitter", 
    "You cannot insert percent symbol!\n\
    Silahkan masukkan tweet yang ingin kamu buat:", "Tweet", "Batal");

    strcopy(TwitterData[playerid][Tweet], inputtext);

    new biaya = strlen(TwitterData[playerid][Tweet]) * 2;
    AccountData[playerid][pBankMoney] -= biaya;

    new fhstr[250];
    mysql_format(g_SQL, fhstr, sizeof(fhstr), "INSERT INTO `tweets` SET `TweetFrom`='%e', `TweetMessage`='%e', `TweetDate`='%e'", TwitterData[playerid][Username], TwitterData[playerid][Tweet], GetSimpleTime());
    mysql_pquery(g_SQL, fhstr, "OnPlayerTweet", "i", playerid);
    return 1;
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
    if(clickedid == TwitterButtonPhone[1])
    {
        HidePhoneMainMenuTD(playerid);

        if(PlayerPhoneData[playerid][IsTwitterLoggedIn] < 1)
        {
            ShowTwitterLoginTD(playerid);
        }
        else
        {
            new sqlfstr[128];
            mysql_format(g_SQL, sqlfstr, sizeof(sqlfstr), "SELECT * FROM `player_twitter` WHERE `ID`=%d", PlayerPhoneData[playerid][IsTwitterLoggedIn]);
            mysql_query(g_SQL, sqlfstr);
            new rows = cache_num_rows();
            if(rows)
            {
                cache_get_value_name(0, "Username", TwitterData[playerid][Username]);
                PlayerTextDrawSetString(playerid, TwitterInfoTD[playerid], sprintf("Hai, %s bagaimana harimu?", TwitterData[playerid][Username]));
                ShowTwitterMainTD(playerid);
            }
        }
    }
    else if(clickedid == TwitterLoginTD[5]) //register twitter
    {
        Dialog_Show(playerid, "TwitterRegister", DIALOG_STYLE_INPUT, 
        "{DA9100}Pahlawan Roleplay "WHITE"- Daftar Twitter", 
        "Hai, selamat datang di Twitter!\n\
        Silakan masukkan username Twitter kamu, ini akan ditampilkan pada setiap tweet yang kamu buat:\n\
        Ingat: Username hanya dapat berupa huruf dan angka, tidak menggunakan simbol!\n\
        Panjang username 7 - 24 karakter!", "Set", "Batal");
    }
    else if(clickedid == TwitterLoginTD[2]) //login twitter
    {
        Dialog_Show(playerid, "TwitterLogin", DIALOG_STYLE_INPUT, 
        "{DA9100}Pahlawan Roleplay "WHITE"- Login Twitter", 
        "Hai, selamat datang di Twitter!\n\
        Silakan masukkan username Twitter kamu yang telah terdaftar:", "Input", "Batal");
    }
    else if(clickedid == TwitterMainTD[1]) //tweet
    {
        PlayerPhoneData[playerid][CurrentlyReadTweet] = true;
        mysql_query(g_SQL, "SELECT * FROM `tweets` WHERE `ID`=1 ORDER BY `TweetDate` ASC LIMIT 30");
        new rowcount = cache_num_rows(), tempTweetFrom[24], tempTweets[128], tempTweetDate[128], lists[2500];
        if(rowcount)
        {
            format(lists, sizeof(lists), "Username\tTanggal\tTweets\n");
            for(new x; x < rowcount; ++x)
            {
                cache_get_value_name(x, "TweetFrom", tempTweetFrom);
                cache_get_value_name(x, "TweetMessage", tempTweets);
                cache_get_value_name(x, "TweetDate", tempTweetDate);
                format(lists, sizeof(lists), "%s{1DA1F2}@%s\t{AAB8C2}%s\t"WHITE"%s\n", lists, tempTweetFrom, tempTweetDate, tempTweets);
            }

            foreach(new i : Player)
            {
                if(PlayerPhoneData[i][CurrentlyReadTweet])
                {
                    Dialog_Show(i, "PhoneTweets", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Twitter", 
                    lists, "Tweet", "Batal");
                }
            }
            return 1;
        }
        else
        {
            Dialog_Show(playerid, "PhoneTweets", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Twitter", 
            "Username\tTweets\nBelum ada Tweet yang dapat ditampilkan kepadamu!", "Tweet", "Batal");
        }
        return 1;
    }
    else if(clickedid == TwitterMainTD[4]) //logout
    {
        new sqlfstr[128];
        PlayerPhoneData[playerid][IsTwitterLoggedIn] = 0;
        mysql_format(g_SQL, sqlfstr, sizeof(sqlfstr), "UPDATE `player_phones` SET `TwitterLoggedIn`=0 WHERE `phoneOwner`=%d", AccountData[playerid][pID]);
        mysql_pquery(g_SQL, sqlfstr);
        HideTwitterTD(playerid);
        ShowTwitterLoginTD(playerid);
    }
    return 1;
}