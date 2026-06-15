#include <YSI_Coding\y_hooks>

#define MAX_ATM 500
#define MAX_BANKPOINT 100

enum e_atm_details
{
    Float:atmPos[6],
    atmWorld,
    atmInt,

    //not save
    STREAMER_TAG_OBJECT:atmObject,
    STREAMER_TAG_AREA:atmArea
};
new AtmData[MAX_ATM][e_atm_details],
    Iterator:Atms<MAX_ATM>;


enum e_bpoint_details
{
    Float:bankPos[3],
    bankWorld,
    bankInt,

    //not save
    STREAMER_TAG_PICKUP:bankPickup,
    STREAMER_TAG_3D_TEXT_LABEL:bankLabel
};
new BankPoint[MAX_BANKPOINT][e_bpoint_details],
    Iterator:BankPoints<MAX_BANKPOINT>;

Atm_Nearest(playerid)
{
    foreach(new i : Atms) if (IsPlayerInRangeOfPoint(playerid, 2.0, AtmData[i][atmPos][0], AtmData[i][atmPos][1], AtmData[i][atmPos][2]))
	{
		if (GetPlayerInterior(playerid) == AtmData[i][atmInt] && GetPlayerVirtualWorld(playerid) == AtmData[i][atmWorld])
			return i;
	}
	return -1;
}

BankPoint_Nearest(playerid)
{
    foreach(new i : BankPoints) if (IsPlayerInRangeOfPoint(playerid, 2.0, BankPoint[i][bankPos][0], BankPoint[i][bankPos][1], BankPoint[i][bankPos][2]))
	{
		if (GetPlayerInterior(playerid) == BankPoint[i][bankInt] && GetPlayerVirtualWorld(playerid) == BankPoint[i][bankWorld])
			return i;
	}
	return -1;
}

GetAtmNearestFromPlayer(playerid)
{
    foreach(new x : Atms)
    {
        if(AtmData[x][atmInt] == 0 && AtmData[x][atmWorld] == 0)
        {
            if(IsPlayerInRangeOfPoint(playerid, 600.0, AtmData[x][atmPos][0], AtmData[x][atmPos][1], AtmData[x][atmPos][2]))
            {
                if(DestroyDynamicRaceCP(AccountData[playerid][pGPSCP]))
                    AccountData[playerid][pGPSCP] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

                AccountData[playerid][pUsingGPS] = true;
                AccountData[playerid][pGPSCP] = CreateDynamicRaceCP(1, AtmData[x][atmPos][0], AtmData[x][atmPos][1], AtmData[x][atmPos][2], AtmData[x][atmPos][0], AtmData[x][atmPos][1], AtmData[x][atmPos][2], 3.5, 0, 0, playerid, 10000.00, -1, 0);
                ShowTDN(playerid, NOTIFICATION_WARNING, "Mohon ikuti checkpoint di map!");
                return 1;
            }
        }
    }
    ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada ATM yang terdekat dari posisi anda!");
    return 1;
}

Atm_BeingEdited(atmid)
{
	if(!Iter_Contains(Atms, atmid)) return 0;
	foreach(new i : Player) if(AccountData[i][EditingAtmID] == atmid) return 1;
	return 0;
}

Atm_Save(atmid)
{
    new hjha[258];
    mysql_format(g_SQL, hjha, sizeof(hjha), "UPDATE `atms` SET `X`='%f', `Y`='%f', `Z`='%f', `RX`='%f', `RY`='%f', `RZ`='%f', `World`=%d, `Interior`=%d WHERE `ID`=%d", 
    AtmData[atmid][atmPos][0], AtmData[atmid][atmPos][1], AtmData[atmid][atmPos][2], AtmData[atmid][atmPos][3], AtmData[atmid][atmPos][4], AtmData[atmid][atmPos][5], AtmData[atmid][atmWorld], AtmData[atmid][atmInt], atmid);
    mysql_pquery(g_SQL, hjha);
    return 1;
}

Atm_Refresh(atmid)
{
    if(atmid != -1)
    {
        SetDynamicObjectPos(AtmData[atmid][atmObject], AtmData[atmid][atmPos][0], AtmData[atmid][atmPos][1], AtmData[atmid][atmPos][2]);
        SetDynamicObjectRot(AtmData[atmid][atmObject], AtmData[atmid][atmPos][3], AtmData[atmid][atmPos][4], AtmData[atmid][atmPos][5]);
        Streamer_SetIntData(STREAMER_TYPE_OBJECT, AtmData[atmid][atmObject], E_STREAMER_WORLD_ID, AtmData[atmid][atmWorld]);
	    Streamer_SetIntData(STREAMER_TYPE_OBJECT, AtmData[atmid][atmObject], E_STREAMER_INTERIOR_ID, AtmData[atmid][atmInt]);

        Streamer_SetItemPos(STREAMER_TYPE_AREA, AtmData[atmid][atmArea], AtmData[atmid][atmPos][0], AtmData[atmid][atmPos][1], AtmData[atmid][atmPos][2]);
        Streamer_SetIntData(STREAMER_TYPE_AREA, AtmData[atmid][atmArea], E_STREAMER_WORLD_ID, AtmData[atmid][atmWorld]);
	    Streamer_SetIntData(STREAMER_TYPE_AREA, AtmData[atmid][atmArea], E_STREAMER_INTERIOR_ID, AtmData[atmid][atmInt]);
    }
    return 1;
}

Atm_Rebuild(atmid)
{
	if (atmid != -1)
	{
		if (DestroyDynamicObject(AtmData[atmid][atmObject]))
		    AtmData[atmid][atmObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

        if (DestroyDynamicArea(AtmData[atmid][atmArea]))
		    AtmData[atmid][atmArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

		AtmData[atmid][atmObject] = CreateDynamicObject(11688, AtmData[atmid][atmPos][0], AtmData[atmid][atmPos][1], AtmData[atmid][atmPos][2], AtmData[atmid][atmPos][3], AtmData[atmid][atmPos][4], AtmData[atmid][atmPos][5], AtmData[atmid][atmWorld], AtmData[atmid][atmInt], -1, 100.00, 100.00); 
        SetDynamicObjectMaterial(AtmData[atmid][atmObject], 1, 19130, "matarrows", "green", 0x00000000);
        SetDynamicObjectMaterial(AtmData[atmid][atmObject], 3, 6060, "shops2_law", "atmflat", 0x00000000);
        AtmData[atmid][atmArea] = CreateDynamicSphere(AtmData[atmid][atmPos][0], AtmData[atmid][atmPos][1], AtmData[atmid][atmPos][2], 2.5, AtmData[atmid][atmWorld], AtmData[atmid][atmInt], -1);
    }
	return 1;
}

BankPoint_Rebuild(bptid)
{
	if (bptid != -1)
	{
		if (DestroyDynamicPickup(BankPoint[bptid][bankPickup]))
		    BankPoint[bptid][bankPickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

        if (DestroyDynamic3DTextLabel(BankPoint[bptid][bankLabel]))
		    BankPoint[bptid][bankLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

		BankPoint[bptid][bankPickup] = CreateDynamicPickup(1274, 23, BankPoint[bptid][bankPos][0], BankPoint[bptid][bankPos][1], BankPoint[bptid][bankPos][2], BankPoint[bptid][bankWorld], BankPoint[bptid][bankInt], -1, 30.00, -1, 0);
        BankPoint[bptid][bankLabel] = CreateDynamic3DTextLabel("[Fleeca Bank Point]\n"WHITE"Selamat datang di Fleeca Bank!\nGunakan "GREEN"[Y] "WHITE"untuk akses bank menu", 0xc0c0c8A6, BankPoint[bptid][bankPos][0], BankPoint[bptid][bankPos][1], BankPoint[bptid][bankPos][2]+0.85, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, BankPoint[bptid][bankWorld], BankPoint[bptid][bankInt], -1, 10.00, -1, 0);
    }
	return 1;
}

forward OnAtmAdded(playerid, atmid);
public OnAtmAdded(playerid, atmid)
{
    Atm_Save(atmid);
    Atm_Refresh(atmid);

    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s membuat ATM dengan ID: %d.", AccountData[playerid][pAdminname], atmid);
    return 1;
}

forward OnBankPointAdded(playerid, bptid);
public OnBankPointAdded(playerid, bptid)
{
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s membuat Bank Point dengan ID: %d.", AccountData[playerid][pAdminname], bptid);
    return 1;
}

forward LoadAtms();
public LoadAtms()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
 		new id;
		for(new i; i < rows; i++)
		{
            cache_get_value_name_int(i, "ID", id);
            cache_get_value_name_float(i, "X", AtmData[id][atmPos][0]);
            cache_get_value_name_float(i, "Y", AtmData[id][atmPos][1]);
            cache_get_value_name_float(i, "Z", AtmData[id][atmPos][2]);
            cache_get_value_name_float(i, "RX", AtmData[id][atmPos][3]);
            cache_get_value_name_float(i, "RY", AtmData[id][atmPos][4]);
            cache_get_value_name_float(i, "RZ", AtmData[id][atmPos][5]);
            cache_get_value_name_int(i, "World", AtmData[id][atmWorld]);
            cache_get_value_name_int(i, "Interior", AtmData[id][atmInt]);
            
			Atm_Rebuild(id);
			Iter_Add(Atms, id);
        }
        printf("[Dynamic ATM] Jumlah total ATM yang dimuat: %d.", rows);
	}
}

forward LoadBankPoints();
public LoadBankPoints()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
 		new id;
		for(new i; i < rows; i++)
		{
            cache_get_value_name_int(i, "ID", id);
            cache_get_value_name_float(i, "X", BankPoint[id][bankPos][0]);
            cache_get_value_name_float(i, "Y", BankPoint[id][bankPos][1]);
            cache_get_value_name_float(i, "Z", BankPoint[id][bankPos][2]);
            cache_get_value_name_int(i, "World", BankPoint[id][bankWorld]);
            cache_get_value_name_int(i, "Interior", BankPoint[id][bankInt]);
            
			BankPoint_Rebuild(id);
			Iter_Add(BankPoints, id);
        }
        printf("[Dynamic Bank Point] Jumlah total bank point yang dimuat: %d.", rows);
	}
}

forward BankNewRek(playerid, brek);
public BankNewRek(playerid, brek)
{
	if(cache_num_rows() > 0)
	{
		//Rekening Exist
		new query[512], rand = RandomEx(111111, 999999);
		new rek = rand+AccountData[playerid][pID];
		mysql_format(g_SQL, query, sizeof(query), "SELECT `Char_BankNumber` FROM `player_characters` WHERE `Char_BankNumber`=%d", rek);
		mysql_pquery(g_SQL, query, "BankNewRek", "id", playerid, rek);
	}
	else
	{
		new query[512];
	    mysql_format(g_SQL, query, sizeof(query), "UPDATE `player_characters` SET `Char_BankNumber`=%d WHERE `pID`=%d", brek, AccountData[playerid][pID]);
		mysql_pquery(g_SQL, query);
		AccountData[playerid][pBankNumber] = brek;
	}
    return true;
}

forward CharNewSSN(playerid, brek);
public CharNewSSN(playerid, brek)
{
	if(cache_num_rows() > 0)
	{
		//SSN Exist
		new query[512], rand = RandomEx(111111111, 999999999);
		new ssn = rand+AccountData[playerid][pID];
		mysql_format(g_SQL, query, sizeof(query), "SELECT `Char_SSN` FROM `player_characters` WHERE `Char_SSN`=%d", ssn);
		mysql_pquery(g_SQL, query, "CharNewSSN", "id", playerid, ssn);
	}
	else
	{
		new query[512];
	    mysql_format(g_SQL, query, sizeof(query), "UPDATE `player_characters` SET `Char_SSN`=%d WHERE `pID`=%d", brek, AccountData[playerid][pID]);
		mysql_pquery(g_SQL, query);
		AccountData[playerid][pSSN] = brek;
	}
    return true;
}

hook OnPlayerEditDynObject(playerid, STREAMER_TAG_OBJECT: objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if(AccountData[playerid][EditingAtmID] != -1 && Iter_Contains(Atms, AccountData[playerid][EditingAtmID]))
	{
		if(response == EDIT_RESPONSE_FINAL)
	    {
	        new atmid = AccountData[playerid][EditingAtmID];
	        AtmData[atmid][atmPos][0] = x;
	        AtmData[atmid][atmPos][1] = y;
	        AtmData[atmid][atmPos][2] = z;
	        AtmData[atmid][atmPos][3] = rx;
	        AtmData[atmid][atmPos][4] = ry;
	        AtmData[atmid][atmPos][5] = rz;

			SetDynamicObjectPos(objectid, AtmData[atmid][atmPos][0], AtmData[atmid][atmPos][1], AtmData[atmid][atmPos][2]);
	        SetDynamicObjectRot(objectid, AtmData[atmid][atmPos][3], AtmData[atmid][atmPos][4], AtmData[atmid][atmPos][5]);

			Streamer_SetItemPos(STREAMER_TYPE_AREA, AtmData[atmid][atmArea], AtmData[atmid][atmPos][0], AtmData[atmid][atmPos][1], AtmData[atmid][atmPos][2]);
			
		    Atm_Save(atmid);
	        AccountData[playerid][EditingAtmID] = -1;
	    }

	    else if(response == EDIT_RESPONSE_CANCEL)
	    {
	        new atmid = AccountData[playerid][EditingAtmID];
	        SetDynamicObjectPos(objectid, AtmData[atmid][atmPos][0], AtmData[atmid][atmPos][1], AtmData[atmid][atmPos][2]);
	        SetDynamicObjectRot(objectid, AtmData[atmid][atmPos][3], AtmData[atmid][atmPos][4], AtmData[atmid][atmPos][5]);
	        AccountData[playerid][EditingAtmID] = -1;
	    }
	}
	return 0;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    foreach(new atmid : Atms)
    {
        if(areaid == AtmData[atmid][atmArea])
        {
            ShowNotifBox(playerid, "Tekan ~p~'Y' ~w~Akses Menu ATM");
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    foreach(new atmid : Atms)
    {
        if(areaid == AtmData[atmid][atmArea])
        {
            HideNotifBox(playerid);
            PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
        }
    }
    return 1;
}

Dialog:ATMDeposit(playerid, response, listitem, inputtext[])
{
    if (!response) return 1;

    if(isnull(inputtext))
    {
        return Dialog_Show(playerid, "ATMDeposit", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Deposit",
        "Error: Tidak dapat dikosongkan!\n\
        Mohon masukkan berapa jumlah deposit:", "Deposit", "Batal");
    }

    if(!IsNumericEx(inputtext)) return Dialog_Show(playerid, "ATMDeposit", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Deposit",
        "Error: Masukkan hanya angka!\n\
        Mohon masukkan berapa jumlah deposit:", "Deposit", "Batal");

    if(strval(inputtext) < 1) return Dialog_Show(playerid, "ATMDeposit", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Deposit",
    "Error: Invalid amount, you can't deposit less than $1!\n\
    Mohon masukkan berapa jumlah deposit:", "Deposit", "Batal");

    if(AccountData[playerid][pMoney] < RoundNegativeToPositive(strval(inputtext))) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

    TakePlayerMoneyEx(playerid, strval(inputtext));
    AccountData[playerid][pBankMoney] += strval(inputtext);

    PlayerTextDrawSetString(playerid, ATMPTD[playerid][0], sprintf("$%s", FormatMoney(AccountData[playerid][pBankMoney])));
    PlayerTextDrawSetString(playerid, ATMPTD[playerid][2], sprintf("$%s", FormatMoney(AccountData[playerid][pMoney])));
    ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Anda telah berhasil deposit ~g~$%s", FormatMoney(strval(inputtext))));
    ShowItemBox(playerid, "Cash", sprintf("Removed $%s", FormatMoney(strval(inputtext))), 1212, 4);
    return 1;
}

Dialog:ATMWithdraw(playerid, response, listitem, inputtext[])
{
    if (!response) return 1;

    if(isnull(inputtext))
    {
        return Dialog_Show(playerid, "ATMWithdraw", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Withdraw",
        "Error: Tidak dapat dikosongkan!\n\
       Mohon masukkan jumlah yang ingin ditarik:", "Withdraw", "Batal");
    }          

    if (!IsNumericEx(inputtext)) return Dialog_Show(playerid, "ATMWithdraw", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Withdraw",
        "Error: Masukkan hanya angka!\n\
       Mohon masukkan jumlah yang ingin ditarik:", "Withdraw", "Batal");

    if(strval(inputtext) < 1) return Dialog_Show(playerid, "ATMWithdraw", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Withdraw",
    "Error: Jumlah tidak valid, anda tidak dapat withdraw kurang dari $1!\n\
   Mohon masukkan jumlah yang ingin ditarik:", "Withdraw", "Batal");

    new Float:RumusPotonganWithdraw;
    if(AccountData[playerid][pBankMoney] < RoundNegativeToPositive(strval(inputtext))) return ShowTDN(playerid, NOTIFICATION_ERROR, "Saldo anda tidak mencukupi!");

    RumusPotonganWithdraw = strval(inputtext) - (strval(inputtext) * 0.04);
    if(floatround(RumusPotonganWithdraw) < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat kurang dari $1!");
    if(AccountData[playerid][pBankMoney] < RoundNegativeToPositive(floatround(RumusPotonganWithdraw))) return ShowTDN(playerid, NOTIFICATION_ERROR, "Saldo anda tidak mencukupi!");
    GivePlayerMoneyEx(playerid, floatround(RumusPotonganWithdraw));
    AccountData[playerid][pBankMoney] -= strval(inputtext);

    PlayerTextDrawSetString(playerid, ATMPTD[playerid][0], sprintf("$%s", FormatMoney(AccountData[playerid][pBankMoney])));
    PlayerTextDrawSetString(playerid, ATMPTD[playerid][2], sprintf("$%s", FormatMoney(AccountData[playerid][pMoney])));
    ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Anda telah berhasil withdraw ~r~$%s", FormatMoney(strval(inputtext))));

    ShowItemBox(playerid, "Cash", sprintf("Received $%s", FormatMoney(strval(inputtext))), 1212, 4);
    return 1;
}

Dialog:ATMTransfer(playerid, response, listitem, inputtext[])
{
    if (!response) return 1;

    if (!AVC_PConnected[playerid]) return Kick(playerid);

    if (isnull(inputtext)) return Dialog_Show(playerid, "ATMTransfer", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Transfer",
        "Error: Tidak dapat dikosongkan!\n\
        Mohon masukkan nomor rekening bank tujuan:", "Set", "Batal");

    if (!IsNumericEx(inputtext)) return Dialog_Show(playerid, "ATMTransfer", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Transfer",
        "Error: Masukkan hanya angka!\n\
        Mohon masukkan nomor rekening bank tujuan:", "Set", "Batal");

    if (strval(inputtext) < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Nomor rekening tidak valid!");
    if (strval(inputtext) == AccountData[playerid][pBankNumber]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat transfer ke rekening sendiri!");

    foreach (new i : Player)
    {
        if (AccountData[i][pSpawned] && AccountData[i][IsLoggedIn])
        {
            if (AccountData[i][pBankNumber] == strval(inputtext))
            {
                AccountData[playerid][pTempTransferID] = i;

                Dialog_Show(playerid, "ATMTransferConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Transfer",
                    "Mohon masukkan berapa jumlah yang ingin ditransfer:", "Transfer", "Batal");
                return 1;
            }
        }
    }

    Dialog_Show(playerid, "ATMTransfer", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Transfer",
        "Error: Pemilik rekening tersebut tidak terkoneksi ke server!\n\
        Mohon masukkan nomor rekening bank tujuan:", "Set", "Batal");
    return 1;
}

Dialog:ATMTransferConfirm(playerid, response, listitem, inputtext[])
{
    if (!response) return 1;

    if (!AVC_PConnected[playerid]) return Kick(playerid);

    new money[32];
    if(isnull(inputtext))
    {
        return Dialog_Show(playerid, "ATMTransferConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Transfer",
        "Error: Tidak dapat dikosongkan!\n\
        Mohon masukkan berapa jumlah yang ingin ditransfer:", "Transfer", "Batal");
    }          

    if (!IsNumericEx(inputtext)) return Dialog_Show(playerid, "ATMTransferConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Transfer",
        "Error: Masukkan hanya angka!\n\
        Mohon masukkan berapa jumlah yang ingin ditransfer:", "Transfer", "Batal");

    if(strval(inputtext) < 1) return Dialog_Show(playerid, "ATMTransferConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Transfer",
    "Error: The amount is invalid, you cannot transfer less than $1!\n\
    Mohon masukkan berapa jumlah yang ingin ditransfer:", "Transfer", "Batal");

    if (!IsPlayerConnected(AccountData[playerid][pTempTransferID])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemilik rekening tersebut telah keluar server!");

    new Float:RumusPotonganTransfer;
    if(AccountData[playerid][pBankMoney] < RoundNegativeToPositive(strval(inputtext))) return ShowTDN(playerid, NOTIFICATION_ERROR, "Saldo anda tidak mencukupi!");

    RumusPotonganTransfer = strval(inputtext) - (strval(inputtext) * 0.04);
    if(floatround(RumusPotonganTransfer) < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat kurang dari $1!");
    if(AccountData[playerid][pBankMoney] < RoundNegativeToPositive(floatround(RumusPotonganTransfer))) return ShowTDN(playerid, NOTIFICATION_ERROR, "Saldo anda tidak mencukupi!");
    AccountData[playerid][pBankMoney] -= strval(inputtext);
    AccountData[AccountData[playerid][pTempTransferID]][pBankMoney] += floatround(RumusPotonganTransfer);

    PlayerTextDrawSetString(playerid, ATMPTD[playerid][0], sprintf("$%s", FormatMoney(AccountData[playerid][pBankMoney])));
    PlayerTextDrawSetString(playerid, ATMPTD[playerid][2], sprintf("$%s", FormatMoney(AccountData[playerid][pMoney])));

    ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Anda telah berhasil transfer ~r~$%s", FormatMoney(strval(inputtext))));
    SendClientMessageEx(AccountData[playerid][pTempTransferID], -1, "[Transfer] Anda telah menerima transfer "GREEN"$%s "WHITE"dengan potongan 4 persen.", FormatMoney(strval(inputtext)));

    if (strval(inputtext) < 1000)
    {
        foreach (new i : Player) if(IsPlayerConnected(i) && AccountData[i][pSpawned])
        {
            if (AccountData[i][pAdmin] > 0)
            {
                SendClientMessageEx(i, X11_YELLOW, "[Transfer] %s (%d) transferred $%s to %s (%d)", AccountData[playerid][pName], playerid, FormatMoney(strval(inputtext)), AccountData[AccountData[playerid][pTempTransferID]][pName], AccountData[playerid][pTempTransferID]);
            }
        }
        AddTransactionLog(GetName(playerid), AccountData[playerid][pUCP], GetName(AccountData[playerid][pTempTransferID]), AccountData[AccountData[playerid][pTempTransferID]][pUCP], strval(inputtext), "NORMAL TRANSFER");
    }
    else
    {
        foreach (new i : Player) if(IsPlayerConnected(i) && AccountData[i][pSpawned])
        {
            if (AccountData[i][pAdmin] > 0)
            {
                SendClientMessageEx(i, X11_ORANGE, "[RMT Alert] %s (%d) transferred $%s to %s (%d)", AccountData[playerid][pName], playerid, FormatMoney(strval(inputtext)), AccountData[AccountData[playerid][pTempTransferID]][pName], AccountData[playerid][pTempTransferID]);
            }
        }
        AddTransactionLog(GetName(playerid), AccountData[playerid][pUCP], GetName(AccountData[playerid][pTempTransferID]), AccountData[AccountData[playerid][pTempTransferID]][pUCP], strval(inputtext), "RMT TRANSFER");
    }

    printf("[Transfer] %s(%s) - $%s", AccountData[playerid][pName], AccountData[playerid][pUCP], FormatMoney(strval(inputtext)));
    printf("[Transfer Rumus Potongan] %s(%s) - %d", AccountData[playerid][pName], AccountData[playerid][pUCP], floatround(RumusPotonganTransfer));
    printf("[Transfer] %s (%s) mentransfer %s - %s kepada %s (%s)", AccountData[playerid][pName], AccountData[playerid][pUCP], money, inputtext, AccountData[AccountData[playerid][pTempTransferID]][pName], AccountData[AccountData[playerid][pTempTransferID]][pUCP]);

    AccountData[playerid][pTempTransferID] = INVALID_PLAYER_ID;
    return 1;
}

Dialog:ATMQuickMenu(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    if(AccountData[playerid][pTempValue2] < 1 || AccountData[playerid][pTempValue2] > 8) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih opsi!");

    switch(AccountData[playerid][pTempValue2])
    {
        case 1:
        {
            if(AccountData[playerid][pBankMoney] < 10000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Saldo anda tidak mencukupi!");

            new Float:RumusPotonganWithdraw;
            RumusPotonganWithdraw = 10000 - (10000 * 0.04);
            AccountData[playerid][pBankMoney] -= 10000;
            GivePlayerMoneyEx(playerid, floatround(RumusPotonganWithdraw));
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda berhasil quick withdraw ~r~$10,000.00");

            PlayerTextDrawSetString(playerid, ATMPTD[playerid][0], sprintf("$%s", FormatMoney(AccountData[playerid][pBankMoney])));
            PlayerTextDrawSetString(playerid, ATMPTD[playerid][2], sprintf("$%s", FormatMoney(AccountData[playerid][pMoney])));

            ShowItemBox(playerid, "Cash", "Received $10,000", 1212, 4);
        }
        case 2:
        {
            if(AccountData[playerid][pBankMoney] < 50000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Saldo anda tidak mencukupi!");

            new Float:RumusPotonganWithdraw;
            RumusPotonganWithdraw = 50000 - (50000 * 0.04);
            AccountData[playerid][pBankMoney] -= 50000;
            GivePlayerMoneyEx(playerid, floatround(RumusPotonganWithdraw));
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda berhasil quick withdraw ~r~$50,000.00");

            PlayerTextDrawSetString(playerid, ATMPTD[playerid][0], sprintf("$%s", FormatMoney(AccountData[playerid][pBankMoney])));
            PlayerTextDrawSetString(playerid, ATMPTD[playerid][2], sprintf("$%s", FormatMoney(AccountData[playerid][pMoney])));
            
            ShowItemBox(playerid, "Cash", "Received $50,000", 1212, 4);
        }
        case 3:
        {
            if(AccountData[playerid][pBankMoney] < 250000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Saldo anda tidak mencukupi!");

            new Float:RumusPotonganWithdraw;
            RumusPotonganWithdraw = 250000 - (250000 * 0.04);
            AccountData[playerid][pBankMoney] -= 250000;
            GivePlayerMoneyEx(playerid, floatround(RumusPotonganWithdraw));
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda berhasil quick withdraw ~r~$250,000");

            PlayerTextDrawSetString(playerid, ATMPTD[playerid][0], sprintf("$%s", FormatMoney(AccountData[playerid][pBankMoney])));
            PlayerTextDrawSetString(playerid, ATMPTD[playerid][2], sprintf("$%s", FormatMoney(AccountData[playerid][pMoney])));

            ShowItemBox(playerid, "Cash", "Received $250,000", 1212, 4);
        }
        case 4:
        {
            if(AccountData[playerid][pBankMoney] < 500000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Saldo anda tidak mencukupi!");

            new Float:RumusPotonganWithdraw;
            RumusPotonganWithdraw = 500000 - (500000 * 0.04);
            AccountData[playerid][pBankMoney] -= 500000;
            GivePlayerMoneyEx(playerid, floatround(RumusPotonganWithdraw));
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda berhasil quick withdraw ~r~$500,000");

            PlayerTextDrawSetString(playerid, ATMPTD[playerid][0], sprintf("$%s", FormatMoney(AccountData[playerid][pBankMoney])));
            PlayerTextDrawSetString(playerid, ATMPTD[playerid][2], sprintf("$%s", FormatMoney(AccountData[playerid][pMoney])));

            ShowItemBox(playerid, "Cash", "Received $500,000", 1212, 4);
        }
        case 5:
        {
            if(AccountData[playerid][pMoney] < 10000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang saku anda tidak mencukupi!");

            TakePlayerMoneyEx(playerid, 10000);
            AccountData[playerid][pBankMoney] += 10000;
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda berhasil quick deposit ~g~$10,000");

            PlayerTextDrawSetString(playerid, ATMPTD[playerid][0], sprintf("$%s", FormatMoney(AccountData[playerid][pBankMoney])));
            PlayerTextDrawSetString(playerid, ATMPTD[playerid][2], sprintf("$%s", FormatMoney(AccountData[playerid][pMoney])));

            ShowItemBox(playerid, "Cash", "Removed $10,000", 1212, 4);
        }
        case 6:
        {
            if(AccountData[playerid][pMoney] < 50000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang saku anda tidak mencukupi!");

            TakePlayerMoneyEx(playerid, 50000);
            AccountData[playerid][pBankMoney] += 50000;
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda berhasil quick deposit ~g~$50,000");

            PlayerTextDrawSetString(playerid, ATMPTD[playerid][0], sprintf("$%s", FormatMoney(AccountData[playerid][pBankMoney])));
            PlayerTextDrawSetString(playerid, ATMPTD[playerid][2], sprintf("$%s", FormatMoney(AccountData[playerid][pMoney])));

            ShowItemBox(playerid, "Cash", "Removed $50,000", 1212, 4);
        }
        case 7:
        {
            if(AccountData[playerid][pMoney] < 250000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang saku anda tidak mencukupi!");

            TakePlayerMoneyEx(playerid, 250000);
            AccountData[playerid][pBankMoney] += 250000;
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda berhasil quick deposit ~g~$250,000");

            PlayerTextDrawSetString(playerid, ATMPTD[playerid][0], sprintf("$%s", FormatMoney(AccountData[playerid][pBankMoney])));
            PlayerTextDrawSetString(playerid, ATMPTD[playerid][2], sprintf("$%s", FormatMoney(AccountData[playerid][pMoney])));

            ShowItemBox(playerid, "Cash", "Removed $250,000", 1212, 4);
        }
        case 8:
        {
            if(AccountData[playerid][pMoney] < 500000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang saku anda tidak mencukupi!");

            TakePlayerMoneyEx(playerid, 500000);
            AccountData[playerid][pBankMoney] += 500000;
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda berhasil quick deposit ~g~$500,000");

            PlayerTextDrawSetString(playerid, ATMPTD[playerid][0], sprintf("$%s", FormatMoney(AccountData[playerid][pBankMoney])));
            PlayerTextDrawSetString(playerid, ATMPTD[playerid][2], sprintf("$%s", FormatMoney(AccountData[playerid][pMoney])));

            ShowItemBox(playerid, "Cash", "Removed $500,000", 1212, 4);
        }
    }
    AccountData[playerid][pTempValue2] = -1;
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(!AccountData[playerid][pKnockdown])
		{
            new id = Atm_Nearest(playerid),
                bptid = BankPoint_Nearest(playerid);

            if(id != -1 || bptid != -1)
            {
                HideNotifBox(playerid);
                
                if(!AVC_PConnected[playerid]) return Kick(playerid);
                
                ApplyAnimation(playerid, "PED", "ATM", 4.1, true, false, false, false, 0, true); // ATM

                ShowATMTD(playerid);
            }
        }
    }
    return 1;
}