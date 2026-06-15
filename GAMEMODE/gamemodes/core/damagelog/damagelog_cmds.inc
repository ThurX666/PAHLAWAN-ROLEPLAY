YCMD:dlog(playerid, params[], help)
{
    new haduh[258], tempLogDate[128], tempLogWeapon[128], Float:tempLogDamage, tempLogPart[35], lists[2500];
    mysql_format(g_SQL, haduh, sizeof(haduh), "SELECT * FROM `damagelogs` WHERE `OwnerID` = %d ORDER BY `ID` DESC LIMIT 30", AccountData[playerid][pID]);
    mysql_query(g_SQL, haduh);

    if(cache_num_rows() > 0)
    {
        format(lists, sizeof(lists), "Tanggal\tSenjata\tDamage\n");
        for(new x; x < cache_num_rows(); ++x)
        {
            cache_get_value_name(x, "Date", tempLogDate);
            cache_get_value_name(x, "Weapon", tempLogWeapon);
            cache_get_value_name_float(x, "Damage", tempLogDamage);
            cache_get_value_name(x, "BodyPart", tempLogPart);
            format(lists, sizeof(lists), "%s%s\t%s\t%.2f - %s\n", lists, tempLogDate, tempLogWeapon, tempLogDamage, tempLogPart);
        }
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Damage Log", 
        lists, "Tutup", "");
        return 1;
    }
    else
    {
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Damage Log", 
        "Tanggal\tSenjata\tDamage\nThere are no damage logs to be shown!", "Tutup", "");
    }
    return 1;
}

YCMD:adlog(playerid, params[], help)
{
    if(AccountData[playerid][pAdmin] < 2)
        return PermissionError(playerid);

    new otherid;
    if(sscanf(params, "u", otherid)) return SUM(playerid, "/adlog [playerid/Part Of Name]");

    if(!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server.");

    new haduh[258], tempLogDate[128], tempLogWeapon[128], Float:tempLogDamage, tempLogPart[35], tempLogIssuer[25], lists[2500];
    mysql_format(g_SQL, haduh, sizeof(haduh), "SELECT * FROM `damagelogs` WHERE `OwnerID` = %d ORDER BY `ID` DESC LIMIT 30", AccountData[otherid][pID]);
    mysql_query(g_SQL, haduh);
    if(cache_num_rows() > 0)
    {
        format(lists, sizeof(lists), "Tanggal\tSenjata\tDamage\tPelaku\n");
        for(new x; x < cache_num_rows(); ++x)
        {
            cache_get_value_name(x, "Date", tempLogDate);
            cache_get_value_name(x, "Weapon", tempLogWeapon);
            cache_get_value_name_float(x, "Damage", tempLogDamage);
            cache_get_value_name(x, "BodyPart", tempLogPart);
            cache_get_value_name(x, "IssuerName", tempLogIssuer);
            format(lists, sizeof(lists), "%s%s\t%s\t%.2f - %s\t%s\n", lists, tempLogDate, tempLogWeapon, tempLogDamage, tempLogPart, tempLogIssuer);
        }
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Damage Log", 
        lists, "Tutup", "");
        return 1;
    }
    else
    {
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Damage Log", 
        "Tanggal\tSenjata\tDamage\nThere are no damage logs to be shown!", "Tutup", "");
    }
    return 1;
}