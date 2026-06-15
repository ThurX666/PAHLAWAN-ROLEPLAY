enum e_avTreasuredetails
{
    Intero, //25 ribu (Makanan/Minuman 70%, Uang $100 - $500 15%, VIP Silver 5%)
    Flagtuf, // 50 ribu 
    Fancious, //100 ribu
    Rareous, // 200 ribu
    InteroKey,
    FlagtufKey,
    FanciousKey,
    RareousKey
};
new avTreasureData[MAX_PLAYERS][e_avTreasuredetails];

forward LoadPlayerAVTreasure(playerid);
public LoadPlayerAVTreasure(playerid)
{
    if(cache_num_rows() > 0)
    {
        cache_get_value_name_int(0, "InteroKey", avTreasureData[playerid][InteroKey]);
        cache_get_value_name_int(0, "FlagtufKey", avTreasureData[playerid][FlagtufKey]);
        cache_get_value_name_int(0, "FanciousKey", avTreasureData[playerid][FanciousKey]);
        cache_get_value_name_int(0, "RareousKey", avTreasureData[playerid][RareousKey]);
        cache_get_value_name_int(0, "Intero", avTreasureData[playerid][Intero]);
        cache_get_value_name_int(0, "Flagtuf", avTreasureData[playerid][Flagtuf]);
        cache_get_value_name_int(0, "Fancious", avTreasureData[playerid][Fancious]);
        cache_get_value_name_int(0, "Rareous", avTreasureData[playerid][Rareous]);
    }
    else
    {
        new string[567];
        mysql_format(g_SQL, string, sizeof(string), "INSERT INTO `avtreasure` (`Owner_ID`, `InteroKey`, `FlagtufKey`, `FanciousKey`, `RareousKey`, `Intero`, `Flagtuf`, `Fancious`, `Rareous`) VALUES ('%d', '0', '0', '0', '0', '0', '0', '0', '0')", AccountData[playerid][pID]);
        mysql_pquery(g_SQL, string);
    }
    return 1;
}