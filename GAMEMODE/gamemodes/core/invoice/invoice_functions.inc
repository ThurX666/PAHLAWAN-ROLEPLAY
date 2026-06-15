#include <YSI_Coding\y_hooks>

#define MAX_INVOICES 5

enum e_invoicedata
{
    invoiceID,
    invoiceOwner,
    invoiceName[34],
    invoiceCost,
    invoiceIssuerDB,
    invoiceIssuerName[MAX_PLAYER_NAME + 1],
    invoiceFactID,

    //not save
    bool:invoiceExists
};
new InvoiceData[MAX_PLAYERS][MAX_INVOICES][e_invoicedata],
    ListedInvoices[MAX_PLAYERS][MAX_INVOICES],
    pTempIvcReason[MAX_PLAYERS][34];

forward OnInvoiceAssigned(playerid, ivcid);
public OnInvoiceAssigned(playerid, ivcid)
{
    InvoiceData[playerid][ivcid][invoiceID] = cache_insert_id();
    ShowTDN(playerid, NOTIFICATION_WARNING, "Anda baru saja menerima ~b~tagihan/invoice ~l~baru, segera dibayar!");
    return 1;
}

forward LoadPlayerInvoices(playerid);
public LoadPlayerInvoices(playerid)
{
    if(cache_num_rows() > 0)
	{
        for(new i; i < cache_num_rows(); i++)
		{
            if(!InvoiceData[playerid][i][invoiceExists])
            {
                InvoiceData[playerid][i][invoiceExists] = true;
                cache_get_value_name_int(i, "ID", InvoiceData[playerid][i][invoiceID]);
                cache_get_value_name_int(i, "Owner", InvoiceData[playerid][i][invoiceOwner]);
                cache_get_value_name(i, "Name", InvoiceData[playerid][i][invoiceName]);
                cache_get_value_name_int(i, "Cost", InvoiceData[playerid][i][invoiceCost]);
                cache_get_value_name_int(i, "IssuerDB", InvoiceData[playerid][i][invoiceIssuerDB]);
                cache_get_value_name(i, "IssuerName", InvoiceData[playerid][i][invoiceIssuerName]);
                cache_get_value_name_int(i, "Faction", InvoiceData[playerid][i][invoiceFactID]);
            }
        }
        printf("[Player Invoices] Jumlah total Invoices yang dimuat untuk %s [DBID: %d]: %d.", AccountData[playerid][pUCP], AccountData[playerid][pID], cache_num_rows());
    }
    return 1;
}

Dialog:InvoiceSetName(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        StopLoopingAnim(playerid);
        RemovePlayerAttachedObject(playerid, 9);
        return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    }
    new targetid = NearestSingle[playerid];
    if(!IsPlayerConnected(targetid)) 
    {
        StopLoopingAnim(playerid);
        RemovePlayerAttachedObject(playerid, 9);
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    }
    if(!IsPlayerNearPlayer(playerid, targetid, 3.0)) 
    {
        StopLoopingAnim(playerid);
        RemovePlayerAttachedObject(playerid, 9);
        return ShowTDN(playerid, NOTIFICATION_WARNING, "Pemain tersebut tidak dekat dengan anda!");
    }
    if(isnull(inputtext)) return Dialog_Show(playerid, "InvoiceSetName", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Invoice", 
    "Error: Tidak dapat dikosongkan!\n\
    Mohon masukkan nama dari invoice ini:", "Input", "Batal");
    if(strlen(inputtext) < 3 || strlen(inputtext) > 34) return Dialog_Show(playerid, "InvoiceSetName", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Invoice", 
    "Error: Nama tagihan harus mengandung 3 - 34 karakter!\n\
    Mohon masukkan nama dari invoice ini:", "Input", "Batal");

    if(strfind(inputtext, "%", true) != -1 || strfind(inputtext, "#", true) != -1)  return Dialog_Show(playerid, "InvoiceSetName", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Invoice", 
    "Error: Tidak dapat memasukkan simbol persen!\n\
    Mohon masukkan nama dari invoice ini:", "Input", "Batal");
    
    strcopy(pTempIvcReason[targetid], inputtext);
    Dialog_Show(playerid, "InvoiceSetCost", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Invoice", 
    "Mohon masukkan nominal untuk tagihan ini:", "Input", "Batal");
    return 1;
}

Dialog:InvoiceSetCost(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        StopLoopingAnim(playerid);
        RemovePlayerAttachedObject(playerid, 9);
        return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    }
    new targetid = NearestSingle[playerid];
    if(!IsPlayerConnected(targetid)) 
    {
        StopLoopingAnim(playerid);
        RemovePlayerAttachedObject(playerid, 9);
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    }
    if(!IsPlayerNearPlayer(playerid, targetid, 3.0)) 
    {
        StopLoopingAnim(playerid);
        RemovePlayerAttachedObject(playerid, 9);
        return ShowTDN(playerid, NOTIFICATION_WARNING, "Pemain tersebut tidak dekat dengan anda!");
    }
    if(isnull(inputtext))
    {
        return Dialog_Show(playerid, "InvoiceSetCost", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Invoice", 
        "Error: Tidak dapat dikosongkan!\n\
        Mohon masukkan nominal biaya untuk tagihan ini:", "Input", "Batal");
    }

    if(!IsNumericEx(inputtext)) return Dialog_Show(playerid, "InvoiceSetCost", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Invoice", 
    "Error: Masukkan hanya angka!\n\
    Mohon masukkan nominal biaya untuk tagihan ini:", "Input", "Batal");

    if(strval(inputtext) < 1) return Dialog_Show(playerid, "InvoiceSetCost", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Invoice", 
    "Error: Invalid ammount, Tidak dapat kurang dari $1!\n\
    Mohon masukkan nominal biaya untuk tagihan ini:", "Input", "Batal");

    for(new ivcid; ivcid < MAX_INVOICES; ++ivcid)
    {
        if(!InvoiceData[targetid][ivcid][invoiceExists]) 
        {
            InvoiceData[targetid][ivcid][invoiceCost] = strval(inputtext);
            InvoiceData[targetid][ivcid][invoiceExists] = true;
            InvoiceData[targetid][ivcid][invoiceOwner] = AccountData[targetid][pID];
            strcopy(InvoiceData[targetid][ivcid][invoiceName], pTempIvcReason[targetid]);
            
            InvoiceData[targetid][ivcid][invoiceIssuerDB] = AccountData[playerid][pID];
            strcopy(InvoiceData[targetid][ivcid][invoiceIssuerName], AccountData[playerid][pName]);
            InvoiceData[targetid][ivcid][invoiceFactID] = AccountData[playerid][pFaction];

            new invstr[250];
            mysql_format(g_SQL, invstr, sizeof(invstr), "INSERT INTO `invoices` SET `Owner`=%d, `Name`='%e', `Cost`=%d, `IssuerDB`=%d, `IssuerName`='%e', `Faction`=%d", InvoiceData[targetid][ivcid][invoiceOwner], InvoiceData[targetid][ivcid][invoiceName], InvoiceData[targetid][ivcid][invoiceCost], InvoiceData[targetid][ivcid][invoiceIssuerDB], InvoiceData[targetid][ivcid][invoiceIssuerName], InvoiceData[targetid][ivcid][invoiceFactID]);
            mysql_pquery(g_SQL, invstr, "OnInvoiceAssigned", "id", targetid, ivcid);

            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memberikan invoice kepada Pemain tersebut.");

            NearestSingle[playerid] = INVALID_PLAYER_ID;
            break;
        }

        if(ivcid == (MAX_INVOICES - 1))
        {
            NearestSingle[playerid] = INVALID_PLAYER_ID;
            ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut memiliki 5 invoice belum terbayar!");
        }
    }
    StopLoopingAnim(playerid);
    RemovePlayerAttachedObject(playerid, 9);
    return 1;
}

Dialog:InvoicePay(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        StopLoopingAnim(playerid);
        RemovePlayerAttachedObject(playerid, 9);
        return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    }

    if(listitem < 0 || listitem > 4)
    {
        StopLoopingAnim(playerid);
        RemovePlayerAttachedObject(playerid, 9);
        return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda belum memilih invoice apapun!");
    }
    if(ListedInvoices[playerid][listitem] == -1) 
    {
        StopLoopingAnim(playerid);
        RemovePlayerAttachedObject(playerid, 9);
        return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda belum memilih invoice apapun!");
    }
    if(!InvoiceData[playerid][ListedInvoices[playerid][listitem]][invoiceExists] && InvoiceData[playerid][ListedInvoices[playerid][listitem]][invoiceOwner] != AccountData[playerid][pID])
    {
        StopLoopingAnim(playerid);
        RemovePlayerAttachedObject(playerid, 9);
        return ShowTDN(playerid, NOTIFICATION_WARNING, "Invoice tersebut tidak ada atau bukan milik anda!");
    }

    if(AccountData[playerid][pBankMoney] < InvoiceData[playerid][ListedInvoices[playerid][listitem]][invoiceCost]) 
    {
        StopLoopingAnim(playerid);
        RemovePlayerAttachedObject(playerid, 9);
        return ShowTDN(playerid, NOTIFICATION_WARNING, "Saldo bank anda tidak cukup untuk membayar invoice!");
    }

    new strgbg[158];

    new Float:forfaction = InvoiceData[playerid][ListedInvoices[playerid][listitem]][invoiceCost] * 0.90;
    new Float:fortaxpemer = InvoiceData[playerid][ListedInvoices[playerid][listitem]][invoiceCost] - forfaction;

    //mysql_format(g_SQL, strgbg, sizeof(strgbg), "UPDATE `player_characters` SET `Char_BankMoney` = `Char_BankMoney` + %d WHERE `pID`=%d", floatround(foroknum), InvoiceData[playerid][ListedInvoices[playerid][listitem]][invoiceIssuerDB]);
    //mysql_pquery(g_SQL, strgbg);

    foreach(new i : Player) if(i != playerid)
    {
        if(AccountData[i][pID] == InvoiceData[playerid][ListedInvoices[playerid][listitem]][invoiceIssuerDB])
        {
            if(AccountData[i][pFaction] == FACTION_UBER)
            {
                AccountData[i][pBankMoney] += floatround(forfaction);
            }
            ShowTDN(i, NOTIFICATION_WARNING, "Seseorang telah membayar invoice yang anda berikan.");
        }
    }

    switch(InvoiceData[playerid][ListedInvoices[playerid][listitem]][invoiceFactID])
    {
        case FACTION_LSPD:
        {
            PolisiMoneyVault += floatround(forfaction);
            PemerMoneyVault += floatround(fortaxpemer);
            mysql_format(g_SQL, strgbg, sizeof(strgbg), "UPDATE `stuffs` SET `polisimoneyvault`=%d, `pemermoneyvault`=%d WHERE `id`=0", PolisiMoneyVault, PemerMoneyVault);
            mysql_pquery(g_SQL, strgbg);
        }
        case FACTION_LSFD:
        {
            EMSMoneyVault += floatround(forfaction);
            PemerMoneyVault += floatround(fortaxpemer);
            mysql_format(g_SQL, strgbg, sizeof(strgbg), "UPDATE `stuffs` SET `emsmoneyvault`=%d, `pemermoneyvault`=%d WHERE `id`=0", EMSMoneyVault, PemerMoneyVault);
            mysql_pquery(g_SQL, strgbg);
        }
        case FACTION_PUTRIDELI:
        {
            PutrideliMoneyVault += floatround(forfaction);
            PemerMoneyVault += floatround(fortaxpemer);
            mysql_format(g_SQL, strgbg, sizeof(strgbg), "UPDATE `stuffs` SET `putridelimoneyvault`=%d, `pemermoneyvault`=%d WHERE `id`=0", PutrideliMoneyVault, PemerMoneyVault);
            mysql_pquery(g_SQL, strgbg);
        }
        case FACTION_SAGOV:
        {
            PemerMoneyVault += InvoiceData[playerid][ListedInvoices[playerid][listitem]][invoiceCost];
            mysql_format(g_SQL, strgbg, sizeof(strgbg), "UPDATE `stuffs` SET `pemermoneyvault`=%d WHERE `id`=0", PemerMoneyVault);
            mysql_pquery(g_SQL, strgbg);
        }
        case FACTION_DINARBUCKS:
        {
            DinarbucksMoneyVault += floatround(forfaction);
            PemerMoneyVault += floatround(fortaxpemer);
            mysql_format(g_SQL, strgbg, sizeof(strgbg), "UPDATE `stuffs` SET `dinarbucksmoneyvault`=%d, `pemermoneyvault`=%d WHERE `id`=0", DinarbucksMoneyVault, PemerMoneyVault);
            mysql_pquery(g_SQL, strgbg);
        }
        case FACTION_BENNYS:
        {
            BennysMoneyVault += floatround(forfaction);
            PemerMoneyVault += floatround(fortaxpemer);
            mysql_format(g_SQL, strgbg, sizeof(strgbg), "UPDATE `stuffs` SET `bennysmoneyvault`=%d, `pemermoneyvault`=%d WHERE `id`=0", BennysMoneyVault, PemerMoneyVault);
            mysql_pquery(g_SQL, strgbg);
        }
        case FACTION_UBER:
        {
            PemerMoneyVault += floatround(fortaxpemer);
            mysql_format(g_SQL, strgbg, sizeof(strgbg), "UPDATE `stuffs` SET `ubermoneyvault`=%d, `pemermoneyvault`=%d WHERE `id`=0", UberMoneyVault, PemerMoneyVault);
            mysql_pquery(g_SQL, strgbg);
        }
        case FACTION_FOX11:
        {
            Fox11MoneyVault += floatround(forfaction);
            PemerMoneyVault += floatround(fortaxpemer);
            mysql_format(g_SQL, strgbg, sizeof(strgbg), "UPDATE `stuffs` SET `fox11moneyvault`=%d, `pemermoneyvault`=%d WHERE `id`=0", Fox11MoneyVault, PemerMoneyVault);
            mysql_pquery(g_SQL, strgbg);
        }
        case FACTION_AUTOMAX:
        {
            AutomaxMoneyVault += floatround(forfaction);
            PemerMoneyVault += floatround(fortaxpemer);
            mysql_format(g_SQL, strgbg, sizeof(strgbg), "UPDATE `stuffs` SET `automaxmoneyvault`=%d, `pemermoneyvault`=%d WHERE `id`=0", AutomaxMoneyVault, PemerMoneyVault);
            mysql_pquery(g_SQL, strgbg);
        }
        case FACTION_HANDOVER:
        {
            HandoverMoneyVault += floatround(forfaction);
            PemerMoneyVault += floatround(fortaxpemer);
            mysql_format(g_SQL, strgbg, sizeof(strgbg), "UPDATE `stuffs` SET `handovermoneyvault`=%d, `pemermoneyvault`=%d WHERE `id`=0", HandoverMoneyVault, PemerMoneyVault);
            mysql_pquery(g_SQL, strgbg);
        }
        case FACTION_SRIMERSING:
        {
            SriMersingMoneyVault += floatround(forfaction);
            PemerMoneyVault += floatround(fortaxpemer);
            mysql_format(g_SQL, strgbg, sizeof(strgbg), "UPDATE `stuffs` SET `srimersingmoneyvault`=%d, `pemermoneyvault`=%d WHERE `id`=0", SriMersingMoneyVault, PemerMoneyVault);
            mysql_pquery(g_SQL, strgbg);
        }
        case FACTION_TEXAS:
        {
            TexasChickenMoneyVault += floatround(forfaction);
            PemerMoneyVault += floatround(fortaxpemer);
            mysql_format(g_SQL, strgbg, sizeof(strgbg), "UPDATE `stuffs` SET `texaschickenmoneyvault`=%d, `pemermoneyvault`=%d WHERE `id`=0", TexasChickenMoneyVault, PemerMoneyVault);
            mysql_pquery(g_SQL, strgbg);
        }
    }

    AccountData[playerid][pBankMoney] -= InvoiceData[playerid][ListedInvoices[playerid][listitem]][invoiceCost];

    mysql_format(g_SQL, strgbg, sizeof(strgbg), "UPDATE `player_characters` SET `Char_BankMoney`=%d WHERE `pID`=%d", AccountData[playerid][pBankMoney], AccountData[playerid][pID]);
    mysql_pquery(g_SQL, strgbg);

    mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `invoices` WHERE `ID` = %d", InvoiceData[playerid][ListedInvoices[playerid][listitem]][invoiceID]);
    mysql_pquery(g_SQL, strgbg);

    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membayar tagihan invoice.");

    InvoiceData[playerid][ListedInvoices[playerid][listitem]][invoiceExists] = false;
    InvoiceData[playerid][ListedInvoices[playerid][listitem]][invoiceOwner] = 0;
    InvoiceData[playerid][ListedInvoices[playerid][listitem]][invoiceName][0] = EOS;
    InvoiceData[playerid][ListedInvoices[playerid][listitem]][invoiceCost] = 0;
    InvoiceData[playerid][ListedInvoices[playerid][listitem]][invoiceIssuerDB] = 0;
    InvoiceData[playerid][ListedInvoices[playerid][listitem]][invoiceIssuerName][0] = EOS;
    InvoiceData[playerid][ListedInvoices[playerid][listitem]][invoiceFactID] = FACTION_NONE;
    InvoiceData[playerid][ListedInvoices[playerid][listitem]][invoiceID] = 0;

    StopLoopingAnim(playerid);
    RemovePlayerAttachedObject(playerid, 9);
    return 1;
}