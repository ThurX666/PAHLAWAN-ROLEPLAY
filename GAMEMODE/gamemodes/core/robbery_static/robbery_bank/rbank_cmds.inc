YCMD:robbank(playerid, params[], help)
{
    if(!IsPlayerInRangeOfPoint(playerid, 3.5, 1447.3456,-1123.2587,23.9590)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di Bank Pacific!");

    if (!PlayerHasItem(playerid, "Alat Hack")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Alat Hack!");
    if (!PlayerHasItem(playerid, "Linggis")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Linggis!");
    if (AccountData[playerid][pDuringRobbery]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang merampok, harap tunggu!");
    if (g_BankRobberyStarted) return ShowTDN(playerid, NOTIFICATION_ERROR, "Bank Pacific baru saja dirampok!");
    if(Iter_Count(LSPDDuty) < 10 || Iter_Count(LSFDDuty) < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Harus memiliki setidaknya 10 polisi & 2 EMS bertugas!");
    if (gettime() < g_BankRobberyCooldown) return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Perampokan Bank Pacific cooldown %d menit.", (g_BankRobberyCooldown - gettime()) / 60));
    
    AccountData[playerid][pQBRobbery] = 1;

    Inventory_Remove(playerid, "Alat Hack", 1);
    Inventory_Remove(playerid, "Linggis", 1);

    ShowItemBox(playerid, "Alat Hack", "Removed 1x", 19893, 4);
    ShowItemBox(playerid, "Linggis", "Removed 1x", 18634, 5);

    new stta[512];
    format(stta, sizeof(stta), ""WHITE"Pacific Standard Public Deposit Bank\n\n\
    "RED"Hacking Bank on progress [%d/5]...\n\
    "WHITE"Please re-type this code:\n\n\
    "LIGHTYELLOW"%s", AccountData[playerid][pQBRobbery], GenerateRandomType(playerid));
    Dialog_Show(playerid, "BankHacking", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Hacking Bank", 
    stta, "Input", "Batal");
    return 1;
}