AddPlayerSalary(playerid, const issuer[], money, const reason[])
{
	static string[514];
	static year, month, day, hour, minute, second;
	gettime(hour, minute, second);
	getdate(year, month, day);

	static date[128];
	format(date, sizeof (date), "%02d/%02d/%d %02d:%02d", day, month, year, hour, minute);

	SendClientMessage(playerid, -1, "Penghasilan anda ditambahkan ke "YELLOW"'/mysalary' "WHITE"silakan dilihat untuk lebih rinci!");
	ShowItemBox(playerid, "Salary Paper", "Received 1x", 2894, 5);

	mysql_format(g_SQL, string, sizeof(string), "INSERT INTO `salary` (`owner`, `issuer`, `money`, `reason`, `date`) VALUES ('%d', '%e', '%d', '%e', '%e')", AccountData[playerid][pID], issuer, money, reason, date);
	mysql_pquery(g_SQL, string);
	return 1;
}

forward SalaryShowForPlayer(playerid);
public SalaryShowForPlayer(playerid)
{
    new rows = cache_num_rows();
    new string[1024];
    new curr_page = index_pagination[playerid];
    new curr_idx = MAX_PAGINATION_PAGES * curr_page;

    strcat(string, "Tanggal\tIssuer\tJumlah\tReason\n");

    new date[30], issuer[46], money, totalpaycheck, reason[46];

    if(rows) 
	{
        if(curr_page == 0) {
            for(new i = 0; i < rows; i++) {
                cache_get_value_name_int(i, "money", money);
                totalpaycheck += money;

            }
            strcat(string, sprintf(""WHITE"\t"WHITE"Grand Total:\t"GREEN"$%s\n", FormatMoney(totalpaycheck)));
        }

        for (new i = curr_idx; i < curr_idx + MAX_PAGINATION_PAGES && i < rows; i++) {

            cache_get_value_name(i, "date", date);
            cache_get_value_name(i, "issuer", issuer);
            cache_get_value_name(i, "reason", reason);
            cache_get_value_name_int(i, "money", money);
            strcat(string, sprintf(""WHITE"%s\t"WHITE"%s\t"GREEN"$%s\t"WHITE"%s\n", date, issuer, FormatMoney(money), reason));
        }

        new max_pages = (rows + MAX_PAGINATION_PAGES - 1) / MAX_PAGINATION_PAGES; 
        if (curr_page > 0) {
            strcat(string, ""RED"<< Sebelumnya\n");
        }
        if (curr_page < max_pages - 1) {
            strcat(string, ""GREEN">> Selanjutnya\n");
        }
        Dialog_Show(playerid, "PlayerSalaryList", DIALOG_STYLE_TABLIST_HEADERS, sprintf("Pending Salary: Page %d of %d", curr_page + 1, max_pages), string, "Tutup", "");
    }
    else 
	{
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki pending salary!");
    }
    return 1;
}

DisplaySalary(playerid)
{
	static query[144];
	mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `salary` WHERE `owner`='%d' ORDER BY `id` ASC", AccountData[playerid][pID]);
	mysql_pquery(g_SQL, query, "SalaryShowForPlayer", "i", playerid);
	return 1;
}

forward PaycheckShowForPlayer(playerid);
public PaycheckShowForPlayer(playerid)
{
    new rows = cache_num_rows();
	if(rows) 
	{
		static string[666], money, totalpaycheck, Float:zakat, newbalance;
		
		money = 0;
		totalpaycheck = 0;
		zakat = 0.0;

		for(new i; i < rows; i++)
		{
			cache_get_value_name_int(i, "money", money);
			totalpaycheck += money;
		}
		format(string, sizeof(string), ""WHITE"Previous Balance: "GREEN"$%s\n", FormatMoney(AccountData[playerid][pBankMoney]));
		format(string, sizeof(string), "%s"WHITE"Paycheck: "GREEN"$%s\n", string, FormatMoney(totalpaycheck));

		if(totalpaycheck >= 36507)
		{
			zakat = floatround(totalpaycheck * 0.025);
			format(string, sizeof(string), "%s"WHITE"Tax (2,5): "RED"$%s\n", string, FormatMoney(floatround(zakat)));
		}
		else
		{
			format(string, sizeof(string), "%s"WHITE"No Tax Payment\n", string);
		}

		newbalance = AccountData[playerid][pBankMoney] + totalpaycheck - floatround(zakat);
		format(string, sizeof(string), "%s"WHITE"New Balance: "GREEN"$%s\n", string, FormatMoney(newbalance));

		SendClientMessageEx(playerid, Y_CYAN, "<=================< {FFFFFF}Paycheck #%04d {00FFFF}>=================>", AccountData[playerid][pPaycheckIndex]);
		SendClientMessageEx(playerid, Y_CYAN, "=> {FFFFFF}Previous Balance: {00FF00}$%s", FormatMoney(AccountData[playerid][pBankMoney]));
		SendClientMessageEx(playerid, Y_CYAN, "=> {FFFFFF}Tax (2,5): "RED"$%s", FormatMoney(floatround(zakat)));
		SendClientMessageEx(playerid, Y_CYAN, "=> {FFFFFF}Paycheck: {00FF00}$%s", FormatMoney(totalpaycheck));
		SendClientMessageEx(playerid, Y_CYAN, "=> {FFFFFF}New Balance: {00FF00}$%s", FormatMoney(newbalance));
		SendClientMessage(playerid, Y_CYAN, "<===================================================>");

		AccountData[playerid][pPaycheckTime] = 3600;

		AccountData[playerid][pBankMoney] = newbalance;

		Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_LIST, sprintf("Paycheck #%04d", AccountData[playerid][pPaycheckIndex]), string, "Tutup", "");

		mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `salary` WHERE `owner`='%d'", AccountData[playerid][pID]);
		mysql_pquery(g_SQL, string);
	}
	else
	{
		new givenpaycheck = 5000, mybalance;

		mybalance = givenpaycheck + AccountData[playerid][pBankMoney];
		SendClientMessageEx(playerid, Y_CYAN, "<=================< {FFFFFF}Paycheck #%04d {00FFFF}>=================>", AccountData[playerid][pPaycheckIndex]);
		SendClientMessageEx(playerid, Y_CYAN, "=> {FFFFFF}Previous Balance: {00FF00}$%s", FormatMoney(AccountData[playerid][pBankMoney]));
		SendClientMessageEx(playerid, Y_CYAN, "=> {FFFFFF}Paycheck: {00FF00}$%s", FormatMoney(givenpaycheck));
		SendClientMessageEx(playerid, Y_CYAN, "=> {FFFFFF}New Balance: {00FF00}$%s", FormatMoney(mybalance));
		SendClientMessage(playerid, Y_CYAN, "<===================================================>");

		AccountData[playerid][pPaycheckTime] = 3600;

		AccountData[playerid][pBankMoney] = mybalance;
	}
    return 1;
}

DisplayPaycheck(playerid)
{
	static string[144];
	mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `salary` WHERE `owner`='%d' ORDER BY `id` ASC", AccountData[playerid][pID]);
	mysql_pquery(g_SQL, string, "PaycheckShowForPlayer", "i", playerid);
	return 1;
}

Dialog:PlayerSalaryList(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        if (!strcmp(inputtext, ">> Selanjutnya", true))
        {
            index_pagination[playerid]++;
            DisplaySalary(playerid);
        }
        else if (!strcmp(inputtext, "<< Sebelumnya", true))
        {
            index_pagination[playerid]--;
            if (index_pagination[playerid] < 0)
            {
                index_pagination[playerid] = 0;
            }
            DisplaySalary(playerid);
        }
    }
    return 1;
}