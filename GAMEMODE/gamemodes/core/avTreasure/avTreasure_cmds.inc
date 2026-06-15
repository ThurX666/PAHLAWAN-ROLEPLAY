YCMD:avtreasure(playerid, params[], help)
{
    static string[555];
    format(string, sizeof(string), 
    "Katalog\tJumlah\n\
    AV Intero Key\t%d\n\
    "GRAY"AV Flagtuf Key\t"GRAY"%d\n\
    AV Fancious Key\t%d\n\
    "GRAY"AV Rareous Key\t"GRAY"%d\n\
    AV Intero Treasure\t%d\n\
    "GRAY"AV Flagtuf Treasure\t"GRAY"%d\n\
    AV Fancious Treasure\t%d\n\
    "GRAY"AV Rareous Treasure Premiere\t"GRAY"%d", 
    avTreasureData[playerid][InteroKey],
    avTreasureData[playerid][FlagtufKey],
    avTreasureData[playerid][FanciousKey],
    avTreasureData[playerid][RareousKey],
    avTreasureData[playerid][Intero],
    avTreasureData[playerid][Flagtuf],
    avTreasureData[playerid][Fancious],
    avTreasureData[playerid][Rareous]);

    Dialog_Show(playerid, "MyAVTreasure", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- avTreasure", string, "Pilih", "Batal");
    return 1;
}