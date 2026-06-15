YCMD:sthelp(playerid, params[], help)
{
    if(!AccountData[playerid][pSteward]) return PermissionError(playerid);

    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- The Stewards", 
    "Stewards\tDescription\n\
    /count\tGet server statistics\n\
    "GRAY"/a\t"GRAY"Access staff chat\n\
    /ans\tRespond to player asks\n\
    "GRAY"/ra\t"GRAY"Respond to player reports\n\
    /aduty\tGo on Duty as a steward\n\
    "GRAY"/asks\t"GRAY"View active questions\n\
    /reports\tView active reports\n\
    "GRAY"/spec\t"GRAY"Monitor players\n\
    /astats\tView player stats\n\
    "GRAY"/ostats\t"GRAY"View player stats (offline)\n\
    /checkucp\tCheck player's UCP\n\
    "GRAY"/acharlist\t"GRAY"Check character list in UCP\n\
    /avehlist\tCheck player's vehicle list\n\
    "GRAY"/ntag\t"GRAY"View nicknames and UCPs of all players\n\
    /gotoveh\tTeleport to a vehicle\n\
    "GRAY"/gotols\t"GRAY"Teleport to Los Santos\n\
    /goto\tTeleport to a player\n\
    "GRAY"/gethere\t"GRAY"Pull a player towards you\n\
    /getip\tGet a player's IP address\n\
    "GRAY"/getin\t"GRAY"Forcefully enter a vehicle\n\
    /getveh\tPull a vehicle towards you\n\
    "GRAY"/sendto\t"GRAY"Send a player to a specific location\n\
    /dveh\tDestroy a vehicle (insurance)\n\
    "GRAY"/kick\t"GRAY"Kick a player from the server\n\
    /slap\tSlap a player\n\
    "GRAY"/ainv\t"GRAY"Check a player's inventory\n\
    /jetpack\tSpawn a jetpack", "Tutup", "");
    return 1;
}