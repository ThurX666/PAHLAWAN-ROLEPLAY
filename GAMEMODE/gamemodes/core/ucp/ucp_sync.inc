#if defined _ucp_sync_included
    #endinput
#endif
#define _ucp_sync_included

static bool:g_UCPOnlineTimerStarted;

stock UCP_MarkClaimCompleted(claimid)
{
    new query[128];
    mysql_format(g_SQL, query, sizeof(query),
        "UPDATE `ucp_item_claims` SET `status`='Claimed', `claimed_at`=NOW() WHERE `id`=%d AND `status`='Pending'",
        claimid
    );
    mysql_tquery(g_SQL, query, "", "");
}

forward UCP_LoadPendingClaims(playerid);
public UCP_LoadPendingClaims(playerid)
{
    if (!IsPlayerConnected(playerid) || !AccountData[playerid][IsLoggedIn] || !AccountData[playerid][pSpawned])
        return 0;

    new rows = cache_num_rows();
    for (new i = 0; i < rows; i++)
    {
        new claimid, model, claimType[16], itemName[64];
        cache_get_value_name_int(i, "id", claimid);
        cache_get_value_name_int(i, "item_model", model);
        cache_get_value_name(i, "claim_type", claimType);
        cache_get_value_name(i, "item_name", itemName);

        if (!strcmp(claimType, "Vehicle", true))
        {
            if (model < 400 || model > 611)
                continue;

            new Float:pos[4];
            GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
            GetPlayerFacingAngle(playerid, pos[3]);
            Vehicle_Create(
                playerid,
                model,
                pos[0],
                pos[1],
                pos[2],
                pos[3],
                random(255),
                random(255),
                GetPlayerVirtualWorld(playerid),
                GetPlayerInterior(playerid)
            );
            UCP_MarkClaimCompleted(claimid);
            ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Klaim UCP %s berhasil diberikan.", itemName));
        }
        else if (!strcmp(claimType, "Skin", true))
        {
            if (model < 0 || model > 311)
                continue;

            AccountData[playerid][pSkin] = model;
            SetPlayerSkin(playerid, model);

            new query[128];
            mysql_format(g_SQL, query, sizeof(query),
                "UPDATE `player_characters` SET `Char_Skin`=%d WHERE `pID`=%d",
                model,
                AccountData[playerid][pID]
            );
            mysql_tquery(g_SQL, query, "", "");
            UCP_MarkClaimCompleted(claimid);
            ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Skin UCP %s berhasil digunakan.", itemName));
        }
        else if (!strcmp(claimType, "Service", true) && !strcmp(itemName, "Hapus Warning", true))
        {
            if (AccountData[playerid][pWarn] > 0)
                AccountData[playerid][pWarn]--;

            new query[128];
            mysql_format(g_SQL, query, sizeof(query),
                "UPDATE `player_characters` SET `Char_Warn`=%d WHERE `pID`=%d",
                AccountData[playerid][pWarn],
                AccountData[playerid][pID]
            );
            mysql_tquery(g_SQL, query, "", "");
            UCP_MarkClaimCompleted(claimid);
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Satu poin warning berhasil dihapus melalui klaim UCP.");
        }
    }
    return 1;
}

stock UCP_CheckPendingClaims(playerid)
{
    new query[256];
    mysql_format(g_SQL, query, sizeof(query),
        "SELECT `id`, `claim_type`, `item_name`, `item_model` FROM `ucp_item_claims` WHERE `username`='%e' AND `character_id`=%d AND `status`='Pending' ORDER BY `id` ASC LIMIT 10",
        AccountData[playerid][pUCP],
        AccountData[playerid][pID]
    );
    mysql_pquery(g_SQL, query, "UCP_LoadPendingClaims", "i", playerid);
}

forward UCP_SnapshotMetrics();
public UCP_SnapshotMetrics()
{
    new query[768];
    mysql_format(g_SQL, query, sizeof(query),
        "INSERT INTO `ucp_server_activity` (`players_online`, `logged_at`) VALUES (%d, NOW())",
        Iter_Count(Player)
    );
    mysql_tquery(g_SQL, query, "", "");

    mysql_format(g_SQL, query, sizeof(query),
        "INSERT INTO `ucp_economy_stats` (`stat_date`, `total_circulation`, `total_assets_value`) SELECT CURDATE(), COALESCE(SUM(`Char_Money` + `Char_BankMoney`), 0), ((SELECT COALESCE(SUM(`Price`), 0) FROM `houses`) + (SELECT COALESCE(SUM(`Price`), 0) FROM `biz`)) FROM `player_characters` ON DUPLICATE KEY UPDATE `total_circulation`=VALUES(`total_circulation`), `total_assets_value`=VALUES(`total_assets_value`)"
    );
    mysql_tquery(g_SQL, query, "", "");
    return 1;
}

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
        "INSERT INTO `ucp_online_players` (`player_id`, `character_name`, `color`, `score`, `ping`, `login_time`) VALUES (%d, '%e', '%e', %d, %d, NOW()) ON DUPLICATE KEY UPDATE `character_name`=VALUES(`character_name`), `color`=VALUES(`color`), `score`=VALUES(`score`), `ping`=VALUES(`ping`)",
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
        SetTimer("UCP_SnapshotMetrics", 600000, true);
        g_UCPOnlineTimerStarted = true;
    }
    UCP_SnapshotMetrics();
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
