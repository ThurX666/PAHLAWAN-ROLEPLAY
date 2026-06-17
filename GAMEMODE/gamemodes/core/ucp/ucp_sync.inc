#if defined _ucp_sync_included
    #endinput
#endif
#define _ucp_sync_included

static bool:g_UCPOnlineTimerStarted;

stock UCP_FormatPlayerColor(playerid, dest[], size = sizeof dest)
{
    new color = GetPlayerColor(playerid);
    format(dest, size, "#%06x", color >>> 8);
}

stock UCP_SyncPlayerOnline(playerid)
{
    if (!IsPlayerConnected(playerid)) return;
    if (!AccountData[playerid][IsLoggedIn]) return;
    if (!AccountData[playerid][pSpawned]) return;

    new query[384], hexColor[11];
    UCP_FormatPlayerColor(playerid, hexColor);

    mysql_format(g_SQL, query, sizeof(query),
        "INSERT INTO `ucp_online_players` (`player_id`, `character_name`, `color`, `score`, `ping`, `login_time`) "
        "VALUES (%d, '%e', '%e', %d, %d, NOW()) "
        "ON DUPLICATE KEY UPDATE `character_name`=VALUES(`character_name`), `color`=VALUES(`color`), `score`=VALUES(`score`), `ping`=VALUES(`ping`)",
        playerid,
        AccountData[playerid][pName],
        hexColor,
        AccountData[playerid][pLevel],
        GetPlayerPing(playerid)
    );
    mysql_tquery(g_SQL, query, "", "");
}

stock UCP_RemovePlayerOnline(playerid)
{
    new query[96];
    mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `ucp_online_players` WHERE `player_id` = %d", playerid);
    mysql_tquery(g_SQL, query, "", "");
}

forward UCP_UpdateAllOnlinePlayers();
public UCP_UpdateAllOnlinePlayers()
{
    new query[160];

    foreach (new i : Player)
    {
        if (!IsPlayerConnected(i)) continue;
        if (!AccountData[i][IsLoggedIn]) continue;
        if (!AccountData[i][pSpawned]) continue;

        mysql_format(g_SQL, query, sizeof(query),
            "UPDATE `ucp_online_players` SET `score` = %d, `ping` = %d WHERE `player_id` = %d",
            AccountData[i][pLevel],
            GetPlayerPing(i),
            i
        );
        mysql_tquery(g_SQL, query, "", "");
    }
    return 1;
}

stock UCP_InitOnlineSync()
{
    mysql_tquery(g_SQL, "TRUNCATE TABLE `ucp_online_players`", "", "");

    if (!g_UCPOnlineTimerStarted)
    {
        SetTimer("UCP_UpdateAllOnlinePlayers", 60000, true);
        g_UCPOnlineTimerStarted = true;
    }
}

hook OnPlayerDisconnect(playerid, reason)
{
    #pragma unused reason
    if (AccountData[playerid][IsLoggedIn] && AccountData[playerid][pSpawned])
    {
        UCP_RemovePlayerOnline(playerid);
    }
    return 1;
}
