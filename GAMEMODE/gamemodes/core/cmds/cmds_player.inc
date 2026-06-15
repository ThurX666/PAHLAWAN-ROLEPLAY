YCMD:cc(playerid, params[], help)
{
	SendClientMessage(playerid, X11_WHITE, "");
	SendClientMessage(playerid, X11_WHITE, "");
	SendClientMessage(playerid, X11_WHITE, "");
	SendClientMessage(playerid, X11_WHITE, "");
	SendClientMessage(playerid, X11_WHITE, "");
	SendClientMessage(playerid, X11_WHITE, "");
	SendClientMessage(playerid, X11_WHITE, "");
	SendClientMessage(playerid, X11_WHITE, "");
	SendClientMessage(playerid, X11_WHITE, "");
	SendClientMessage(playerid, X11_WHITE, "");
	SendClientMessage(playerid, X11_WHITE, "");
	SendClientMessage(playerid, X11_WHITE, "");
	SendClientMessage(playerid, X11_WHITE, "");
	SendClientMessage(playerid, X11_WHITE, "");
	SendClientMessage(playerid, X11_WHITE, "");
	SendClientMessage(playerid, X11_WHITE, "");
	SendClientMessage(playerid, X11_WHITE, "");
	SendClientMessage(playerid, X11_WHITE, "");
	SendClientMessage(playerid, X11_WHITE, "");
	SendClientMessage(playerid, X11_WHITE, "");
	return 1;
}
YCMD:clearchat(playerid, params[], help) = cc;

YCMD:sm(playerid, params[], help)
{
	new ereksi[512];
	format(ereksi, sizeof(ereksi),
	"Kegiatan Roleplay\tKeperluan\tStatus\n\
	Begal/Copet/Scam\t4 Polisi & 2 EMS\t%s\n\
	"GRAY"Ladang/Lab/Craft\t"GRAY"4 Polisi & 2 EMS\t%s\n\
	Carsteal\t4 Polisi & 2 EMS\t%s\n\
	"GRAY"Rampok Warung\t"GRAY"4 Polisi & 2 EMS\t%s\n\
	Rampok Bank Kecil\t6 Polisi & 2 EMS\t%s\n\
	"GRAY"Rampok Bank Besar\t"GRAY"10 Polisi & 2 EMS\t%s",
	(Iter_Count(LSPDDuty) >= 4 && Iter_Count(LSFDDuty) >= 2) ? (""GREEN"Boleh") : (""ORANGE"Mendung"),
	(Iter_Count(LSPDDuty) >= 4 && Iter_Count(LSFDDuty) >= 2) ? (""GREEN"Boleh") : (""ORANGE"Mendung"),
	(Iter_Count(LSPDDuty) >= 4 && Iter_Count(LSFDDuty) >= 2) ? (""GREEN"Boleh") : (""ORANGE"Mendung"),
	(Iter_Count(LSPDDuty) >= 4 && Iter_Count(LSFDDuty) >= 2) ? (""GREEN"Boleh") : (""ORANGE"Mendung"),
	(Iter_Count(LSPDDuty) >= 6 && Iter_Count(LSFDDuty) >= 2) ? (""GREEN"Boleh") : (""ORANGE"Mendung"),
	(Iter_Count(LSPDDuty) >= 10 && Iter_Count(LSFDDuty) >= 2) ? (""GREEN"Boleh") : (""ORANGE"Mendung"));
	Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Status Mendung", ereksi, "Tutup", "");
	return 1;
}

YCMD:cl(playerid, params[], help)
{
	if(!PlayerHasItem(playerid, "Smartphone"))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki smartphone!");

	new Float:n1, Float:n2, oper, Float:answer;
	if(sscanf(params, "fcf", n1, oper, n2)) 
		return SUM(playerid, "/cl [first number] [operator] [second number] ~n~+, -, *, / | Example: 25 * 3 (to multiply)");

	switch(oper)
	{
		case '+': answer = n1 + n2;
		case '-': answer = n1 - n2;
		case '/':
		{
			if(n2 == 0) 
			{
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dibagi oleh 0!");
			}
			answer = n1 / n2;
		}
		case '*': answer = n1 * n2;
		default: 
		{
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input/operator!");
		}
	}
	SendClientMessageEx(playerid, X11_GREEN, "[CALCULATOR] "WHITE"%.2f %c %.2f = "YELLOW"%.2f", n1, oper, n2, answer);
	return 1;
}

YCMD:delay(playerid, params[], help)
{
	static string[512];
	format(string, sizeof(string), "Activity\tDelay (Minutes)\n\
	"GRAY"Mowing Sidejob\t"GRAY"%d\n\
	Sweeper Sidejob\t%d\n\
	"GRAY"Forklift Sidejob\t"GRAY"%d\n\
	Trash Collector Sidejob\t%d\n\
	"GRAY"Pizza Delivery Sidejob\t"GRAY"%d",
	AccountData[playerid][pMowingSidejobDelay]/60,
	AccountData[playerid][pSweeperSidejobDelay]/60,
	AccountData[playerid][pForkliftSidejobDelay]/60,
	AccountData[playerid][pTrashCollectorDelay]/60,
	AccountData[playerid][pPizzaSidejobDelay]/60);
	Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Delay Times", string, "Tutup", "");
	return 1;
}

YCMD:delays(playerid, params[], help) = delay;

YCMD:sv(playerid, params[], help)
{
	Dialog_Show(playerid, "VoiceModeSet", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Jarak Voice", 
	""RED"Teriak\n"WHITE"Normal\n"YELLOW"Bisik", "Pilih", "Batal");
	return 1;
}

YCMD:svkey(playerid, params[], help)
{
	Dialog_Show(playerid, "VoiceKeySet", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Keybind Voice", 
	"Push to talk: Z Button\n\
	"GRAY"Push to talk: M Button\n\
	Push to talk: L Button\n\
	"GRAY"Push to talk: B Button (default)\n\
	Push to talk: X Button\n\
	"GRAY"Push to talk: R Button\n\
	Push to talk: P Button", "Pilih", "Batal");
	return 1;
}

YCMD:fixme(playerid, params[], help)
{
	if (AccountData[playerid][pArrested] || OJailData[playerid][jailed]) {
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menggunakan ini ketika sedang dihukum!");
	}
	if (AccountData[playerid][pInEvent]) {
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menggunakan ini ketika di dalam event!");
	}
	if (AccountData[playerid][pStuckRequest] != 0) {
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah mengirim fix request, mohon tunggu!");
	}
	
	Dialog_Show(playerid, "ApplyFixme", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Fix Me", 
	"Keluhan\tKeterangan Masalah\n\
	Bug Visu (WWID)\tApabila anda tidak melihat objek/player apapun (berada di alam baka).\n\
	"GRAY"Karakter Stuck\t"GRAY"Apabila anda stuck (tertimpa) objek/kendaraan sehingga tidak bisa gerak.\n\
	Tidak Bisa Bergerak\tApabila anda tidak dapat menggerakkan karakter (freeze).\n\
	"GRAY"Bug Balai Kota\t"GRAY"Jika terjatuh dari interior balai kota dan berada di bawahnya", "Pilih", "Batal");
	return 1;
}

YCMD:id(playerid, params[], help)
{
	new othername[24];
	if(sscanf(params, "s[24]", othername))
        return SUM(playerid, "/id [Part Of Name]");

	new lenght = strlen(othername);
	if(lenght < 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Setidaknya masukkan 3 karakter dari nickname Pemain tersebut!");

	new count = 0;
	foreach(new i : Player)
	{
		if(!AccountData[i][pSpawned]) continue;
		
		if(strcmp(othername, AccountData[i][pName], true, lenght) == 0)
		{
			SendClientMessageEx(playerid, -1, "UCP: %s | Name: %s | Level: %d | Ping: %d ms | Packet Loss: %.2f | Playtime: %s | ID: %d", AccountData[i][pUCP], AccountData[i][pName], AccountData[i][pLevel], GetPlayerPing(i), GetPlayerPacketLoss(i),  GetFormatTime(NetStats_GetConnectedTime(i)/1000), i);
			count++;
		}
	}

	if(count == 0)
		return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Tidak ada '%s' di dalam server!", othername));
	return 1;
}

YCMD:netstats(playerid, params[], help)
{
	SendClientMessageEx(playerid, -1, "Ping: %d ms | Packet Loss: %.2f | Playtime: %s", GetPlayerPing(playerid), GetPlayerPacketLoss(playerid),  GetFormatTime(NetStats_GetConnectedTime(playerid)/1000));
	return 1;
}

YCMD:admins(playerid, params[], help)
{
	static count = 0, string[1048];
	format(string, sizeof(string), "Rank\tAdmin Name\tStatus\n");
	foreach(new i:Player)
	{
		if(AccountData[i][pSpawned])
		{
			if(AccountData[i][pAdmin] > 0 || AccountData[i][pApprentice] || AccountData[i][pSteward])
			{
				if(!AccountData[i][pHiddenAdmin])
				{
					if(AccountData[i][pAdmin] > 0)
					{
						format(string, sizeof(string), "%s"ORANGERED"%s\t"YELLOW"%s\t%s\n", string, GetAdminLevel(i), AccountData[i][pAdminname], (AccountData[i][pAdminDuty]) ? (""GREEN"Bertugas") : (""ORANGE"Roleplay"));
					}

					if(AccountData[i][pApprentice])
					{
						format(string, sizeof(string), "%s"GREEN"Apprentice\t"YELLOW"%s\t-\n", string, AccountData[i][pAdminname]);
					}

					if(AccountData[i][pSteward])
					{
						format(string, sizeof(string), "%s"AQUAMARINE"The Stewards\t"YELLOW"%s\t%s\n", string, AccountData[i][pAdminname], (AccountData[i][pAdminDuty]) ? (""GREEN"Bertugas") : (""ORANGE"Roleplay"));
					}
					count++;
				}
			}
		}
	}
	if(count == 0) return Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Online Administrators", "No administrators are currently online!", "Tutup", "");

	Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Online Administrators", string, "Tutup", "");
	return 1;
}

YCMD:stats(playerid, params[], help)
{
	ShowPlayerStats(playerid, playerid);
	return 1;
}

YCMD:stopsong(playerid, params[], help)
{
	if(AccountData[playerid][pSideJob] != SIDEJOB_NONE) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukan ini ketika sedang sidejob!");
	PlayerPlaySound(playerid, 1188, 0.0, 0.0, 0.0);
	PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
	StopAudioStreamForPlayer(playerid);
	ShowTDN(playerid, NOTIFICATION_INFO, "Music telah diberhentikan!");
	return 1;
}

YCMD:qa(playerid, params[], help)
{
	static string[256];
	if (!quiz) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada quiz yang sedang berlangsung!");
	if (sscanf(params, "s[256]", string)) return SUM(playerid, "/qa [answer]");
	if(strcmp(string, answers, true)==0)
	{
		GivePlayerMoneyEx(playerid, qprs);
		SendClientMessageToAllEx(-1, "[Quiz] "RED"%s "WHITE"has won the quiz!", AccountData[playerid][pName]);
		SendClientMessageToAllEx(-1, "~> Answer: "YELLOW"'%s'", string);
		SendClientMessageEx(playerid, -1, "[Quiz] Correct answer! You have earned "DARKGREEN"$%s", FormatMoney(qprs));
		answermade = false;
		quiz = false;
		qprs = 0;
		answers[0] = EOS;
	}
	else
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Jawaban tidak benar!");
	}
	return 1;
}

YCMD:cursor(playerid, params[], help)
{
	SelectTextDraw(playerid, 0xff91a4cc);
	return 1;
}

YCMD:help(playerid, params[], help)
{
	Dialog_Show(playerid, "PlayerHelp", DIALOG_STYLE_TABLIST_HEADERS, 
	"{DA9100}Pahlawan Roleplay "WHITE"- Bantuan", 
	"Jenis Bantuan\tKeterangan\n\
	Perintah Dasar\tBerisi beberapa CMD dasar untuk player\n\
	"GRAY"Perintah Kendaraan\t"GRAY"Berisi beberapa CMD seputar kendaraan\n\
	Perintah Roleplay\tBerisi beberapa CMD untuk roleplay\n\
	"GRAY"Petunjuk Dasar\t"GRAY"Berisi beberapa petunjuk dasar Pahlawan Roleplay\n\
	Petunjuk Lapar Haus\tBerisi beberapa petunjuk tentang kebutuhan karakter\n\
	"GRAY"Perintah Racing\t"GRAY"Berisi beberapa CMD untuk sistem balapan\n\
	Hotkeys (Shortcut Key)\tBeberapa tombol hanya tersedia untuk player PC", "Pilih", "Batal");
	return 1;
}

YCMD:setrender(playerid, params[], help)
{
    Dialog_Show(playerid, "SetMapRender", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Render Settings", "Type\tRadius\nSoft\t100.00\n"GRAY"Medium\t"GRAY"200.00\nHard\t300.00 (default)", "Set", "Batal");
    return 1;
}

YCMD:takebx(playerid, params[], help)
{
	if(AccountData[playerid][pKnockdown])
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");

	if(!AccountData[playerid][pBoombox])
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki boombox!");

	if(!BoomBoxInfo[playerid][BoomBoxPlaced])
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum meletakkan boombox!");

	if(!IsPlayerInRangeOfPoint(playerid, 3.0, BoomBoxInfo[playerid][BoomX], BoomBoxInfo[playerid][BoomY], BoomBoxInfo[playerid][BoomZ]))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan boombox milik anda sendiri!");

	if(strcmp(BoomBoxInfo[playerid][BoomBoxOwner], AccountData[playerid][pName]))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Boombox ini bukan milik anda!");

	else
	{
		foreach(new i : Player)
		{
			if(IsPlayerInDynamicArea(i, BoomBoxInfo[playerid][BoomBoxArea]))
			{
				StopAudioStreamForPlayer(i);
			}
		}
		
		if(DestroyDynamicObject(BoomBoxInfo[playerid][BoomBoxObj]))
			BoomBoxInfo[playerid][BoomBoxObj] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

		if(DestroyDynamic3DTextLabel(BoomBoxInfo[playerid][BoomBoxLabel]))
			BoomBoxInfo[playerid][BoomBoxLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

		if(DestroyDynamicArea(BoomBoxInfo[playerid][BoomBoxArea]))
			BoomBoxInfo[playerid][BoomBoxArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
		
		BoomBoxInfo[playerid][BoomBoxOwner][0] = EOS;
		BoomBoxInfo[playerid][BoomBoxLink][0] = EOS;

		BoomBoxInfo[playerid][BoomBoxPlaced] = false;

		BoomBoxInfo[playerid][BoomX] = 0.0;
		BoomBoxInfo[playerid][BoomY] = 0.0;
		BoomBoxInfo[playerid][BoomZ] = 0.0;
		BoomBoxInfo[playerid][BoomA] = 0.0;

		BoomBoxInfo[playerid][BoomVw] = 0;
		BoomBoxInfo[playerid][BoomInt] = 0;
	}
	return 1;
}

YCMD:flist(playerid, params[], help)
{
	new string[512], FMemCount[12];
	new pol[128], ems[128], pdg[128], com[128], mek[128], uber[128], dinar[128], fox11[128], automx[128], hndover[128], plrv[128], txcr[128];

	for(new x; x < 12; x++)
	{
		FMemCount[x] = 0;
	}

	foreach(new i : Player) if(AccountData[i][pSpawned] && AccountData[i][pFaction] != 0)
	{
		if(AccountData[i][pFaction] == FACTION_LSPD)
		{
			FMemCount[0]++;
		}

		if(AccountData[i][pFaction] == FACTION_LSFD)
		{
			FMemCount[1]++;
		}

		if(AccountData[i][pFaction] == FACTION_PUTRIDELI)
		{
			FMemCount[2]++;
		}

		if(AccountData[i][pFaction] == FACTION_SAGOV)
		{
			FMemCount[3]++;
		}

		if(AccountData[i][pFaction] == FACTION_BENNYS)
		{
			FMemCount[4]++;
		}

		if(AccountData[i][pFaction] == FACTION_UBER)
		{
			FMemCount[5]++;
		}

		if(AccountData[i][pFaction] == FACTION_DINARBUCKS)
		{
			FMemCount[6]++;
		}

		if(AccountData[i][pFaction] == FACTION_FOX11)
		{
			FMemCount[7]++;
		}

		if(AccountData[i][pFaction] == FACTION_AUTOMAX)
		{
			FMemCount[8]++;
		}

		if(AccountData[i][pFaction] == FACTION_HANDOVER)
		{
			FMemCount[9]++;
		}
		if(AccountData[i][pFaction] == FACTION_SRIMERSING)
		{
			FMemCount[10]++;
		}
		if(AccountData[i][pFaction] == FACTION_TEXAS)
		{
			FMemCount[11]++;
		}
	}
	if(Iter_Count(LSPDDuty) > 8)
	{
		format(pol, sizeof(pol), "8+");
	}
	else
	{
		format(pol, sizeof(pol), "%d", Iter_Count(LSPDDuty));
	}

	if(Iter_Count(LSFDDuty) > 8)
	{
		format(ems, sizeof(ems), "8+");
	}
	else
	{
		format(ems, sizeof(ems), "%d", Iter_Count(LSFDDuty));
	}

	if(Iter_Count(PutrideliDuty) > 8)
	{
		format(pdg, sizeof(pdg), "8+");
	}
	else
	{
		format(pdg, sizeof(pdg), "%d", Iter_Count(PutrideliDuty));
	}

	if(Iter_Count(PemerDuty) > 8)
	{
		format(com, sizeof(com), "8+");
	}
	else
	{
		format(com, sizeof(com), "%d", Iter_Count(PemerDuty));
	}

	if(Iter_Count(BennysDuty) > 8)
	{
		format(mek, sizeof(mek), "8+");
	}
	else
	{
		format(mek, sizeof(mek), "%d", Iter_Count(BennysDuty));
	}
	
	if(Iter_Count(UberDuty) > 8)
	{
		format(uber, sizeof(uber), "8+");
	}
	else
	{
		format(uber, sizeof(uber), "%d", Iter_Count(UberDuty));
	}

	if(Iter_Count(DinarbucksDuty) > 8)
	{
		format(dinar, sizeof(dinar), "8+");
	}
	else
	{
		format(dinar, sizeof(dinar), "%d", Iter_Count(DinarbucksDuty));
	}

	if(Iter_Count(Fox11Duty) > 8)
	{
		format(fox11, sizeof(fox11), "8+");
	}
	else
	{
		format(fox11, sizeof(fox11), "%d", Iter_Count(Fox11Duty));
	}

	if(Iter_Count(AutomaxDuty) > 8)
	{
		format(automx, sizeof(automx), "8+");
	}
	else
	{
		format(automx, sizeof(automx), "%d", Iter_Count(AutomaxDuty));
	}

	if(Iter_Count(HandoverDuty) > 8)
	{
		format(hndover, sizeof(hndover), "8+");
	}
	else
	{
		format(hndover, sizeof(hndover), "%d", Iter_Count(HandoverDuty));
	}

	if(Iter_Count(SriMersingDuty) > 8)
	{
		format(plrv, sizeof(plrv), "8+");
	}
	else
	{
		format(plrv, sizeof(plrv), "%d", Iter_Count(SriMersingDuty));
	}

	if(Iter_Count(TexasChickenDuty) > 8)
	{
		format(txcr, sizeof(txcr), "8+");
	}
	else
	{
		format(txcr, sizeof(txcr), "%d", Iter_Count(TexasChickenDuty));
	}

	format(string, sizeof(string), "#\tFaction\tDuty/Online\n\
	1.\tKepolisian Daerah Pahlawan Roleplay\t%s/%d\n\
	"GRAY"2.\t"GRAY"Paramedis Kota Pahlawan Roleplay\t"GRAY"%s/%d\n\
	3.\tPutri Deli Beach Club\t%s/%d\n\
	"GRAY"4.\t"GRAY"Pemerintah Daerah Pahlawan Roleplay\t"GRAY"%s/%d\n\
	5.\tBennys Automotive\t%s/%d\n\
	"GRAY"6.\t"GRAY"Uber\t"GRAY"%s/%d\n\
	7.\tPinky Tiger Club\t%s/%d\n\
	"GRAY"8.\t"GRAY"Pewarta Berita Kota Pahlawan Roleplay\t"GRAY"%s/%d\n\
	9.\tAutomax Workshop\t%s/%d\n\
	"GRAY"10.\t"GRAY"Handover Motorworks\t%s/%d\n\
	11.\tSri Mersing Resto\t%s/%d\n\
	"GRAY"12.\t"GRAY"Texas Chicken\t%s/%d", pol, FMemCount[0], ems, FMemCount[1], pdg, FMemCount[2], com, FMemCount[3], mek, FMemCount[4], uber, FMemCount[5], dinar, FMemCount[6], fox11, FMemCount[7], automx, FMemCount[8], hndover, FMemCount[9], plrv, FMemCount[10], txcr, FMemCount[11]);
	Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- On Duty List", 
	string, "Tutup", "");
	return 1;
}

Dialog:FamonDialogList(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        return 1;
    }

    if(!strcmp(inputtext, ">> Selanjutnya", true)) 
    {
        index_pagination[playerid]++;

        new
            max_contact_page = MAX_FACTIONS_ITEMS / MAX_PAGINATION_PAGES;

        if(index_pagination[playerid] >= max_contact_page) 
        {
            index_pagination[playerid] = max_contact_page;
        }
        Show_BadsideOnMember(playerid);
    }
    else if(!strcmp(inputtext, "<< Sebelumnya", true)) 
    {
        index_pagination[playerid]--;
        if(index_pagination[playerid] <= 0) {
            index_pagination[playerid] = 0;
        }
        Show_BadsideOnMember(playerid);
    }
    return 1;
}

YCMD:famon(playerid, params[], help)
{
	if(AccountData[playerid][pFamily] < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari badside manapun!");
    
	index_pagination[playerid] = 0;
	Show_BadsideOnMember(playerid);
	return 1;
}

YCMD:fon(playerid, params[], help)
{
	if(AccountData[playerid][pFaction] < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari faction manapun!");

	index_pagination[playerid] = 0;
	Show_FactionOnMember(playerid);
	return 1;
}

YCMD:hidektd(playerid, params[], help)
{
	HideIDCTD(playerid);
	HideLCTD(playerid);
	HideKTATD(playerid);
	HideBPJSTD(playerid);
	return 1;
}

YCMD:pay(playerid, params[], help)
{
	new targetid, money;
	if(sscanf(params, "ud", targetid, money)) return SUM(playerid, "/pay [playerid] [amount]");
	if(!AVC_PConnected[playerid]) return Kick(playerid);
	if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(targetid == playerid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya terhadap diri sendiri!");

	if(money > 5000 && AccountData[playerid][pAdmin] == 0)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Maksimal $5,000 sekali transaksi!");
	
	if(money < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat memberi kurang dari $1!");

	if(!IsPlayerNearPlayer(playerid, targetid, 3.5)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan Pemain tersebut!");

	if(AccountData[playerid][pMoney] < RoundNegativeToPositive(money)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

	TakePlayerMoneyEx(playerid, money);
	GivePlayerMoneyEx(targetid, money);

	ShowTDN(targetid, NOTIFICATION_INFO, sprintf("Player %s memberimu ~g~$%s.", GetPlayerRoleplayName(playerid), FormatMoney(money)));
	ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil memberi ~r~$%s ~l~kepada ~r~%s.", FormatMoney(money), GetPlayerRoleplayName(targetid)));
	
	SetPlayerToFacePlayer(playerid, targetid);
	SetPlayerToFacePlayer(targetid, playerid);
	ApplyAnimation(targetid, "GANGS", "prtial_hndshk_biz_01", 4.0, 0, 0, 0, 0, 0, true);
	ApplyAnimation(playerid, "GANGS", "prtial_hndshk_biz_01", 4.0, 0, 0, 0, 0, 0, true);

	foreach(new i : Player)
	{
		if(AccountData[i][pAdmin] > 0)
		{
			if(money < 10000)
			{
				SendClientMessageEx(i, X11_YELLOW, "[Pay] %s (%d) has given $%s to %s (%d)", AccountData[playerid][pName], playerid, FormatMoney(money), AccountData[targetid][pName], targetid);
				AddTransactionLog(AccountData[playerid][pName], AccountData[playerid][pUCP], AccountData[targetid][pName], AccountData[targetid][pUCP], money, "NORMAL");
			}
			else
			{
				SendClientMessageEx(i, X11_ORANGE, "[RMT Alert] %s (%d) has given $%s to %s (%d)", AccountData[playerid][pName], playerid, FormatMoney(money), AccountData[targetid][pName], targetid);
				AddTransactionLog(AccountData[playerid][pName], AccountData[playerid][pUCP], AccountData[targetid][pName], AccountData[targetid][pUCP], money, "RMT");
			}
		}
	}
	printf("[Pay] %s (%s) memberi %s kepada %s (%s)", AccountData[playerid][pName], AccountData[playerid][pUCP], money, AccountData[targetid][pName], AccountData[targetid][pUCP]);
	return 1;
}

YCMD:gdm(playerid, params[], help)
{
	new targetid, money;
	if(sscanf(params, "ud", targetid, money)) return SUM(playerid, "/gdm [playerid] [amount]");
	if(!AVC_PConnected[playerid]) return Kick(playerid);
	if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(targetid == playerid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya terhadap diri sendiri!");

	if(money > 5000 && AccountData[playerid][pAdmin] == 0)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Maksimal $5,000 sekali transaksi!");
	
	if(money < 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memberi kurang dari $100!");

	if(!IsPlayerNearPlayer(playerid, targetid, 3.5)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan Pemain tersebut!");

	if(AccountData[playerid][pDirtyMoney] < RoundNegativeToPositive(money)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup dirty money!");

	TakePlayerDirtyMoney(playerid, money);
	GivePlayerDirtyMoney(targetid, money);

	ShowItemBox(playerid, "Dirty Money", sprintf("Removed $%sx", FormatMoney(money)), 1550, 5);
	ShowItemBox(targetid, "Dirty Money", sprintf("Received $%sx", FormatMoney(money)), 1550, 5);

	ShowTDN(targetid, NOTIFICATION_INFO, sprintf("Player %s memberimu ~r~$%s ~l~dirty money.", GetPlayerRoleplayName(playerid), FormatMoney(money)));
	ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil memberi ~r~$%s ~l~dirty money kepada ~r~%s.", FormatMoney(money), GetPlayerRoleplayName(targetid)));
	ApplyAnimation(playerid, "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0, true);
	return 1;
}

YCMD:myv(playerid, params[], help)
{
    new bool:found = false;
    new string[1618];
    format(string, sizeof(string), "Vehicle ID\tModel [Database ID]\tPlate\t/ Rental / Status\n");
    foreach(new i : PvtVehicles)
    {
        if(PlayerVehicle[i][pVehOwnerID] == AccountData[playerid][pID])
        {
            if(strcmp(PlayerVehicle[i][pVehPlate], "-")) // If it has a plate
            {
                if(PlayerVehicle[i][pVehRentTime] != 0) // If it's a rental vehicle with a plate
                {
                    format(string, sizeof(string), "%s%s\t%s [%d]\t%s\t/ %s / %s\n", string, (PlayerVehicle[i][pVehPhysic] == INVALID_VEHICLE_ID) ? ("[Not Spawned]") : (sprintf("[%d]", PlayerVehicle[i][pVehPhysic])), GetVehicleModelName(PlayerVehicle[i][pVehModelID]), PlayerVehicle[i][pVehID], PlayerVehicle[i][pVehPlate], ReturnTimelapse(gettime(), PlayerVehicle[i][pVehRentTime], "Rental Expired"), GetMyVehicleStatus(i));
                    found = true;
                }
                else // If it's not a rental vehicle but has a plate
                {
                    format(string, sizeof(string), "%s%s\t%s [%d]\t%s\t/ Dimiliki / %s\n", string, (PlayerVehicle[i][pVehPhysic] == INVALID_VEHICLE_ID) ? ("[Not Spawned]") : (sprintf("[%d]", PlayerVehicle[i][pVehPhysic])), GetVehicleModelName(PlayerVehicle[i][pVehModelID]), PlayerVehicle[i][pVehID], PlayerVehicle[i][pVehPlate], GetMyVehicleStatus(i));
                    found = true;
                }
            }
            else // If it doesn't have a plate
            {
                if(PlayerVehicle[i][pVehRentTime] != 0) // If it's a rental vehicle without a plate
                {
                    format(string, sizeof(string), "%s%s\t%s [%d]\tNo Plate\t/ %s / %s\n", string, (PlayerVehicle[i][pVehPhysic] == INVALID_VEHICLE_ID) ? ("[Not Spawned]") : (sprintf("[%d]", PlayerVehicle[i][pVehPhysic])), GetVehicleModelName(PlayerVehicle[i][pVehModelID]), PlayerVehicle[i][pVehID], ReturnTimelapse(gettime(), PlayerVehicle[i][pVehRentTime], "Rental Expired"), GetMyVehicleStatus(i));
                    found = true;
                }
                else // If it's not a rental vehicle and doesn't have a plate
                {
                    format(string, sizeof(string), "%s%s\t%s [%d]\tNo Plate\t/ Dimiliki / %s\n", string, (PlayerVehicle[i][pVehPhysic] == INVALID_VEHICLE_ID) ? ("[Not Spawned]") : (sprintf("[%d]", PlayerVehicle[i][pVehPhysic])), GetVehicleModelName(PlayerVehicle[i][pVehModelID]), PlayerVehicle[i][pVehID], GetMyVehicleStatus(i));
                    found = true;
                }
            }
        }
    }
    if(found)
        Dialog_Show(playerid, "VehicleFind", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE" - Kepemilikan Kendaraan", string, "Cari", "Tutup");
    else
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE" - Kepemilikan Kendaraan", "Anda tidak memiliki kendaraan apapun!", "Tutup", "");
    return 1;
}

YCMD:fa(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] == FACTION_NONE) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari faction manapun!");

    if(isnull(params)) return SUM(playerid, "/fa [message]");

    static string[144];
    switch(AccountData[playerid][pFaction])
    {
        case FACTION_LSPD:
        {
			if(strlen(params) > 64)
			{
            	format(string, sizeof(string), "(Polisi - %s %s): "WHITE"> %.64s...", GetRankName(playerid), GetPlayerRoleplayName(playerid), params);
				SendClientMessageToAll(0x0096FFFF, string);
            	format(string, sizeof(string), "...%s <", params[64]);
				SendClientMessageToAll(X11_WHITE, string);
			}
			else
			{
				format(string, sizeof(string), "(Polisi - %s %s): "WHITE"> %s <", GetRankName(playerid), GetPlayerRoleplayName(playerid), params);
            	SendClientMessageToAll(0x0096FFFF, string);
			}
        }
        case FACTION_LSFD:
        {
			if(strlen(params) > 64)
			{
            	format(string, sizeof(string), "(Paramedis - %s %s): "WHITE"> %.64s...", GetRankName(playerid), GetPlayerRoleplayName(playerid), params);
				SendClientMessageToAll(0xFF1A1AFF, string);
            	format(string, sizeof(string), "...%s <", params[64]);
				SendClientMessageToAll(X11_WHITE, string);
			}
			else
			{
				format(string, sizeof(string), "(Paramedis - %s %s): "WHITE"> %s <", GetRankName(playerid), GetPlayerRoleplayName(playerid), params);
            	SendClientMessageToAll(0xFF1A1AFF, string);
			}
        }
        case FACTION_PUTRIDELI:
        {
			if(strlen(params) > 64)
			{
            	format(string, sizeof(string), "(Putri Deli - %s %s): "WHITE"> %.64s...", GetRankName(playerid), GetPlayerRoleplayName(playerid), params);
				SendClientMessageToAll(0xF28C28FF, string);
            	format(string, sizeof(string), "...%s <", params[64]);
				SendClientMessageToAll(X11_WHITE, string);
			}
			else
			{
				format(string, sizeof(string), "(Putri Deli - %s %s): "WHITE"> %s <", GetRankName(playerid), GetPlayerRoleplayName(playerid), params);
            	SendClientMessageToAll(0xF28C28FF, string);
			}
        }
        case FACTION_SAGOV:
        {
			if(strlen(params) > 64)
			{
            	format(string, sizeof(string), "(Pemerintah - %s %s): "WHITE"> %.64s...", GetRankName(playerid), GetPlayerRoleplayName(playerid), params);
				SendClientMessageToAll(0x40E0D0FF, string);
            	format(string, sizeof(string), "...%s <", params[64]);
				SendClientMessageToAll(X11_WHITE, string);
			}
			else
			{
				format(string, sizeof(string), "(Pemerintah - %s %s): "WHITE"> %s <", GetRankName(playerid), GetPlayerRoleplayName(playerid), params);
            	SendClientMessageToAll(0x40E0D0FF, string);
			}
        }
        case FACTION_BENNYS:
        {
			if(strlen(params) > 64)
			{
            	format(string, sizeof(string), "(Bennys - %s %s): "WHITE"> %.64s...", GetRankName(playerid), GetPlayerRoleplayName(playerid), params);
				SendClientMessageToAll(0x20B2AAFF, string);
            	format(string, sizeof(string), "...%s <", params[64]);
				SendClientMessageToAll(X11_WHITE, string);
			}
			else
			{
				format(string, sizeof(string), "(Bennys - %s %s): "WHITE"> %s <", GetRankName(playerid), GetPlayerRoleplayName(playerid), params);
            	SendClientMessageToAll(0x20B2AAFF, string);
			}
        }
        case FACTION_UBER:
        {
			if(strlen(params) > 64)
			{
            	format(string, sizeof(string), "(Uber - %s %s): "WHITE"> %.64s...", GetRankName(playerid), GetPlayerRoleplayName(playerid), params);
				SendClientMessageToAll(0xc0c0c8FF, string);
            	format(string, sizeof(string), "...%s <", params[64]);
				SendClientMessageToAll(X11_WHITE, string);
			}
			else
			{
				format(string, sizeof(string), "(Uber - %s %s): "WHITE"> %s <", GetRankName(playerid), GetPlayerRoleplayName(playerid), params);
            	SendClientMessageToAll(0xc0c0c8FF, string);
			}
        }
        case FACTION_DINARBUCKS:
        {
			if(strlen(params) > 64)
			{
            	format(string, sizeof(string), "(Pinky Tiger - %s %s): "WHITE"> %.64s...", GetRankName(playerid), GetPlayerRoleplayName(playerid), params);
				SendClientMessageToAll(0x188D38FF, string);
            	format(string, sizeof(string), "...%s <", params[64]);
				SendClientMessageToAll(X11_WHITE, string);
			}
			else
			{
				format(string, sizeof(string), "(Pinky Tiger - %s %s): "WHITE"> %s <", GetRankName(playerid), GetPlayerRoleplayName(playerid), params);
            	SendClientMessageToAll(0x188D38FF, string);
			}
        }
        case FACTION_FOX11:
        {
			if(strlen(params) > 64)
			{
            	format(string, sizeof(string), "(Pewarta - %s %s): "WHITE"> %.64s...", GetRankName(playerid), GetPlayerRoleplayName(playerid), params);
				SendClientMessageToAll(0x075ebfA6, string);
            	format(string, sizeof(string), "...%s <", params[64]);
				SendClientMessageToAll(X11_WHITE, string);
			}
			else
			{
				format(string, sizeof(string), "(Pewarta - %s %s): "WHITE"> %s <", GetRankName(playerid), GetPlayerRoleplayName(playerid), params);
            	SendClientMessageToAll(0x075ebfA6, string);
			}
        }
		case FACTION_AUTOMAX:
        {
			if(strlen(params) > 64)
			{
            	format(string, sizeof(string), "(Automax - %s %s): "WHITE"> %.64s...", GetRankName(playerid), GetPlayerRoleplayName(playerid), params);
				SendClientMessageToAll(0x6fd356FF, string);
            	format(string, sizeof(string), "...%s <", params[64]);
				SendClientMessageToAll(X11_WHITE, string);
			}
			else
			{
				format(string, sizeof(string), "(Automax - %s %s): "WHITE"> %s <", GetRankName(playerid), GetPlayerRoleplayName(playerid), params);
            	SendClientMessageToAll(0x6fd356FF, string);
			}
        }
		case FACTION_HANDOVER:
        {
			if(strlen(params) > 64)
			{
            	format(string, sizeof(string), "(Handover - %s %s): "WHITE"> %.64s...", GetRankName(playerid), GetPlayerRoleplayName(playerid), params);
				SendClientMessageToAll(0xff7dcbFF, string);
            	format(string, sizeof(string), "...%s <", params[64]);
				SendClientMessageToAll(X11_WHITE, string);
			}
			else
			{
				format(string, sizeof(string), "(Handover - %s %s): "WHITE"> %s <", GetRankName(playerid), GetPlayerRoleplayName(playerid), params);
            	SendClientMessageToAll(0xff7dcbFF, string);
			}
        }
		case FACTION_SRIMERSING:
        {
			if(strlen(params) > 64)
			{
            	format(string, sizeof(string), "(Sri Mersing - %s %s): "WHITE"> %.64s...", GetRankName(playerid), GetPlayerRoleplayName(playerid), params);
				SendClientMessageToAll(0xcbe9f6FF, string);
            	format(string, sizeof(string), "...%s <", params[64]);
				SendClientMessageToAll(X11_WHITE, string);
			}
			else
			{
				format(string, sizeof(string), "(Sri Mersing - %s %s): "WHITE"> %s <", GetRankName(playerid), GetPlayerRoleplayName(playerid), params);
            	SendClientMessageToAll(0xcbe9f6FF, string);
			}
        }
		case FACTION_TEXAS:
        {
			if(strlen(params) > 64)
			{
            	format(string, sizeof(string), "(Texas Chicken - %s %s): "WHITE"> %.64s...", GetRankName(playerid), GetPlayerRoleplayName(playerid), params);
				SendClientMessageToAll(X11_YELLOW, string);
            	format(string, sizeof(string), "...%s <", params[64]);
				SendClientMessageToAll(X11_WHITE, string);
			}
			else
			{
				format(string, sizeof(string), "(Texas Chicken - %s %s): "WHITE"> %s <", GetRankName(playerid), GetPlayerRoleplayName(playerid), params);
            	SendClientMessageToAll(X11_YELLOW, string);
			}
        }
    }
    return 1;
}

YCMD:ro(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] == FACTION_NONE) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari faction manapun!");

    static chat[144], string[144];
    if(sscanf(params, "s[144]", chat)) return SUM(playerid, "/ro [pesan]");

    if(strlen(chat) > 64)
    {
        foreach(new i : Player) if(AccountData[i][pSpawned] && AccountData[i][pFaction] == AccountData[playerid][pFaction])
        {
            format(string, sizeof(string), "(( %s %s [%d]: %.64s... ))", GetRankName(playerid), GetPlayerRoleplayName(playerid), playerid, chat);
            SendClientMessage(i, 0xFFEC8BFF, string);
            format(string, sizeof(string), "(( ...%s ))", chat[64]);
            SendClientMessage(i, 0xFFEC8BFF, string);
        }
    }
    else
    {
        foreach(new i : Player) if(AccountData[i][pSpawned] && AccountData[i][pFaction] == AccountData[playerid][pFaction])
        {
            format(string, sizeof(string), "(( %s %s [%d]: %s ))", GetRankName(playerid), GetPlayerRoleplayName(playerid), playerid, chat);
            SendClientMessage(i, 0xFFEC8BFF, string);
        }
    }
    return 1;
}

YCMD:rdo(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] == FACTION_NONE) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari faction manapun!");

    static chat[144], string[144];
    if(sscanf(params, "s[144]", chat)) return SUM(playerid, "/ro [pesan]");

    if(strlen(chat) > 64)
    {
        foreach(new i : Player) if(AccountData[i][pSpawned] && IsPlayerInGovTypeFaction(i))
        {
            format(string, sizeof(string), "(( [DEP] %s %s [%d]: %.64s... ))", GetRankName(playerid), GetPlayerRoleplayName(playerid), playerid, chat);
            SendClientMessage(i, 0x88D0C5FF, string);
            format(string, sizeof(string), "(( ...%s ))", chat[64]);
            SendClientMessage(i, 0x88D0C5FF, string);
        }
    }
    else
    {
        foreach(new i : Player) if(AccountData[i][pSpawned] && IsPlayerInGovTypeFaction(i))
        {
            format(string, sizeof(string), "(( [DEP] %s %s [%d]: %s ))", GetRankName(playerid), GetPlayerRoleplayName(playerid), playerid, chat);
            SendClientMessage(i, 0x88D0C5FF, string);
        }
    }
    return 1;
}

YCMD:carry(playerid, params[], help)
{
	if(AccountData[playerid][pGetDraggedBy] != INVALID_PLAYER_ID)
	{
		ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil melepaskan diri dari gendongan Pemain tersebut.");
		TogglePlayerControllable(playerid, true);

		if(IsPlayerConnected(AccountData[playerid][pGetDraggedBy]))
		{
			AccountData[AccountData[playerid][pGetDraggedBy]][DraggingID] = INVALID_PLAYER_ID;
			ShowTDN(AccountData[playerid][pGetDraggedBy], NOTIFICATION_INFO, "Pemain tersebut telah melepaskan dirinya.");
		}
		AccountData[playerid][pGetDraggedBy] = INVALID_PLAYER_ID;
		return 1;
	}

	if(AccountData[playerid][DraggingID] != INVALID_PLAYER_ID)
	{
		TogglePlayerControllable(AccountData[playerid][DraggingID], true);
		ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil berhenti menggendong seseorang.");
		ShowTDN(AccountData[playerid][DraggingID], NOTIFICATION_INFO, "Anda telah dilepaskan oleh seseorang yang menggendong anda.");
		AccountData[AccountData[playerid][DraggingID]][pGetDraggedBy] = INVALID_PLAYER_ID;
		AccountData[playerid][DraggingID] = INVALID_PLAYER_ID;
		return 1;
	}

	new targetid;
	if(sscanf(params, "u", targetid)) return SUM(playerid, "/carry [nama/playerid]");
	if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

	if(targetid == playerid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya terhadap diri sendiri!");

	if (!AccountData[targetid][pSpawned]) {
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut belum spawn!");
	}
	if (!IsPlayerNearPlayer(playerid, targetid, 2.5)) {
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan Pemain tersebut!");
	}
	if (AccountData[targetid][DraggingID] != INVALID_PLAYER_ID) {
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menggendong/menyeret player yang sedang menggendong/menyeret player lain!");
	}
	if (AccountData[targetid][pGetDraggedBy] != INVALID_PLAYER_ID) {
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menggendong/menyeret player yang sedang digendong/diseret player lain!");
	}
	if (IsPlayerInAnyVehicle(targetid)) {
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sedang berada di dalam kendaraan!");
	}
	
	AccountData[targetid][pDragOffer] = playerid;
	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil meminta permohonan untuk menggendong.");
	SendClientMessageEx(targetid, -1, "Player "YELLOW"%s [%s] (%d) "WHITE"has requested to be carried. Use "YELLOW"'/accept carry' "WHITE"to accept it.", GetPlayerRoleplayName(playerid), AccountData[playerid][pUCP], playerid);
	return 1;
}

YCMD:sellveh(playerid, params[], help)
{
	static targetid, vid, pricing;
	if(sscanf(params, "udd", targetid, vid, pricing)) return SUM(playerid, "/sellveh [playerid] [VID] [price]");
	if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(!IsPlayerNearPlayer(playerid, targetid, 3.5)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan Pemain tersebut!");
	if(!IsValidVehicle(vid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid vehicle ID!");
	if(pricing < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Harga tidak valid!");
	if(!AccountData[playerid][pHasKTP]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Kartu Tanda Penduduk/sudah expired!");
	if(!AccountData[targetid][pHasKTP]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak memiliki Kartu Tanda Penduduk/sudah expired!");

	foreach(new pv : PvtVehicles)
	{
		if(PlayerVehicle[pv][pVehPhysic] == vid)
		{
			if(PlayerVehicle[pv][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut bukan milik anda!");
			if(!strcmp(PlayerVehicle[pv][pVehPlate], "-", false)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut tidak memiliki plat!");
			if(PlayerVehicle[pv][pVehRental] > -1 || PlayerVehicle[pv][pVehRentTime] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan rental tidak dapat dijual!");
			if(PlayerVehicle[pv][pVehTireLocked]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut dalam kondisi tirelocked!");

			AccountData[targetid][pTempSellerID] = playerid;
			AccountData[targetid][pTempSellPrice] = pricing;
			AccountData[targetid][pTempSellIterID] = pv;

			ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Anda menawarkan ~b~%s ~l~kepada ~r~%s(%d) ~l~seharga ~g~$%s", GetVehicleModelName(PlayerVehicle[pv][pVehModelID]), AccountData[targetid][pName], targetid, FormatMoney(AccountData[targetid][pTempSellPrice])));
			ShowTDN(targetid, NOTIFICATION_INFO, sprintf("Player %s(%d) ingin menjual ~b~%s ~l~seharga ~r~$%s", AccountData[playerid][pName], playerid, GetVehicleModelName(PlayerVehicle[pv][pVehModelID]), FormatMoney(AccountData[targetid][pTempSellPrice])));
			ShowTDN(targetid, NOTIFICATION_WARNING, "Gunakan '/accept buyveh' untuk menerimanya!");
			return 1;
		}
	}
	ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut bukan kendaraan pribadi!");
	return 1;
}

YCMD:accept(playerid, params[], help)
{
	new string[158], type[24];

	if(sscanf(params, "s[24]S()[128]", type, string)) return SUM(playerid, "/accept [name] (buyveh, carry, taxi)");
	if(strcmp(type,"buyveh",true) == 0) 
	{
		static pv, counting;
		counting = 0;
		pv = AccountData[playerid][pTempSellIterID];
		if(!IsPlayerConnected(AccountData[playerid][pTempSellerID])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki transaksi dengan siapapun");
		if(!IsPlayerNearPlayer(playerid, AccountData[playerid][pTempSellerID], 3.5)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan pemain tersebut!");
		if(AccountData[playerid][pMoney] < AccountData[playerid][pTempSellPrice]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
		if(!IsValidVehicle(PlayerVehicle[pv][pVehPhysic])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan yang dijual tidak ada/tidak spawn!");
		if(PlayerVehicle[pv][pVehTireLocked]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut dalam kondisi tirelocked!");
		if(!AccountData[playerid][pHasKTP]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Kartu Tanda Penduduk/sudah expired!");
		if(!AccountData[AccountData[playerid][pTempSellerID]][pHasKTP]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak memiliki Kartu Tanda Penduduk/sudah expired!");
		
		foreach(new v : PvtVehicles)
        {
            if(PlayerVehicle[v][pVehOwnerID] == AccountData[playerid][pID])
                counting++;
        }
		if(counting >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot kendaraan anda telah penuh!");
		TakePlayerMoneyEx(playerid, AccountData[playerid][pTempSellPrice]);
		GivePlayerMoneyEx(AccountData[playerid][pTempSellerID], AccountData[playerid][pTempSellPrice]);

		SendClientMessageToAllEx(0x1DA1F2FF, "> %s (%s) milik %s terjual ke %s.", GetVehicleModelName(PlayerVehicle[pv][pVehModelID]), PlayerVehicle[pv][pVehPlate], GetPlayerRoleplayName(AccountData[playerid][pTempSellerID]), GetPlayerRoleplayName(playerid));
		ShowTDN(AccountData[playerid][pTempSellerID], NOTIFICATION_INFO, "Pemain tersebut telah menerima tawaran anda!");
		ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membeli kendaraan tersebut.");
		PlayerVehicle[pv][pVehOwnerID] = AccountData[playerid][pID];
		
		mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `vehicle_bagasi` WHERE `Veh_DBID`=%d", PlayerVehicle[pv][pVehID]);
		mysql_pquery(g_SQL, string);

		mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `vehicle_holster` WHERE `Veh_DBID`=%d", PlayerVehicle[pv][pVehID]);
		mysql_pquery(g_SQL, string);

		mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_vehicles` SET `PVeh_Owner`=%d WHERE `id` = %d", PlayerVehicle[pv][pVehOwnerID], PlayerVehicle[pv][pVehID]);
		mysql_pquery(g_SQL, string);

		for(new x; x < MAX_BAGASI_ITEMS; x++)
		{
			VehicleBagasi[pv][x][vehicleBagasiExists] = false;
			VehicleBagasi[pv][x][vehicleBagasiID] = 0;
			VehicleBagasi[pv][x][vehicleBagasiVDBID] = 0;
			VehicleBagasi[pv][x][vehicleBagasiTemp][0] = EOS;
			VehicleBagasi[pv][x][vehicleBagasiModel] = 0;
			VehicleBagasi[pv][x][vehicleBagasiQuant] = 0;
		}

		for(new z; z < 3; z++)
		{
			VehicleHolster[pv][vHolsterTaken][z] = false;
			VehicleHolster[pv][vHolsterID][z] = -1;
			VehicleHolster[pv][vHolsterWeaponID][z] = 0;
			VehicleHolster[pv][vHolsterWeaponAmmo][z] = 0;
		}

		AccountData[playerid][pTempSellerID] = INVALID_PLAYER_ID;
		AccountData[playerid][pTempSellPrice] = 0;
		AccountData[playerid][pTempSellIterID] = -1;
	}
	else if(strcmp(type,"carry",true) == 0) 
	{
		if(AccountData[playerid][pDragOffer] == INVALID_PLAYER_ID || !IsPlayerConnected(AccountData[playerid][pDragOffer]))
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi/tidak ada tawaran dari siapapun");
		
		if(!IsPlayerNearPlayer(playerid, AccountData[playerid][pDragOffer], 3.5)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan Pemain tersebut!");
		
		AccountData[AccountData[playerid][pDragOffer]][DraggingID] = playerid;
		AccountData[playerid][pGetDraggedBy] = AccountData[playerid][pDragOffer];
		TogglePlayerControllable(playerid, false);
		ShowTDN(AccountData[playerid][pDragOffer], NOTIFICATION_SUCCESS, "Anda berhasil menggendong seseorang.");
		SendClientMessageEx(playerid, -1, "Player "YELLOW"%s [%s] (%d) "WHITE"is carrying your character. Use "YELLOW"/carry "WHITE"to release yourself.", GetPlayerRoleplayName(AccountData[playerid][pDragOffer]), AccountData[AccountData[playerid][pDragOffer]][pUCP], AccountData[playerid][pDragOffer]);
		AccountData[playerid][pDragOffer] = INVALID_PLAYER_ID;
	}
	else if(strcmp(type,"eshared",true) == 0) 
	{
		if(AccountData[playerid][pESharedOfferer] == INVALID_PLAYER_ID)
		{
			AccountData[playerid][pESharedType] = 0;
			AccountData[playerid][pESharedOfferer] = INVALID_PLAYER_ID;
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki tawaran eshared!");
		}
		if(!IsPlayerConnected(AccountData[playerid][pESharedOfferer]))
		{
			AccountData[playerid][pESharedType] = 0;
			AccountData[playerid][pESharedOfferer] = INVALID_PLAYER_ID;
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
		}	

		if(!IsPlayerNearPlayer(playerid, AccountData[playerid][pESharedOfferer], 2.0)) 
		{
			AccountData[playerid][pESharedType] = 0;
			AccountData[playerid][pESharedOfferer] = INVALID_PLAYER_ID;
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan Pemain tersebut!");
		}

		new offererid = AccountData[playerid][pESharedOfferer];
		
		switch(AccountData[playerid][pESharedType])
		{
			case 1: //cipok
			{
				SetPlayerToFacePlayer(playerid, offererid);
				SetPlayerToFacePlayer(offererid, playerid);
				ApplyAnimation(playerid, "KISSING", "Grlfrd_Kiss_01", 4.1, false, false, false, false, 0, true);
				ApplyAnimation(offererid, "KISSING", "Playa_Kiss_01", 4.1, false, false, false, false, 0, true);
			}
			case 2: //cipok2
			{
				SetPlayerToFacePlayer(playerid, offererid);
				SetPlayerToFacePlayer(offererid, playerid);
				ApplyAnimation(playerid, "KISSING", "Grlfrd_Kiss_02", 4.1, false, false, false, false, 0, true);
				ApplyAnimation(offererid, "KISSING", "Playa_Kiss_02", 4.1, false, false, false, false, 0, true);
			}
			case 3: //cipok3
			{
				SetPlayerToFacePlayer(playerid, offererid);
				SetPlayerToFacePlayer(offererid, playerid);
				ApplyAnimation(playerid, "KISSING", "Grlfrd_Kiss_03", 4.1, false, false, false, false, 0, true);
				ApplyAnimation(offererid, "KISSING", "Playa_Kiss_03", 4.1, false, false, false, false, 0, true);
			}
			case 4: //gift
			{
				SetPlayerToFacePlayer(playerid, offererid);
				SetPlayerToFacePlayer(offererid, playerid);
				ApplyAnimation(playerid, "KISSING", "gift_get", 4.1, false, false, false, false, 0, true);
				ApplyAnimation(offererid, "KISSING", "gift_give", 4.1, false, false, false, false, 0, true);
			}
			case 5: //nikmat
			{
				SetPlayerToFacePlayer(playerid, offererid);
				SetPlayerToFacePlayer(offererid, playerid);
				ApplyAnimation(playerid, "BLOWJOBZ", "BJ_COUCH_LOOP_W", 4.1, true, false, false, false, 0, true);
				ApplyAnimation(offererid, "BLOWJOBZ", "BJ_COUCH_LOOP_P", 4.1, true, false, false, false, 0, true);
			}
			case 6: //nikmat2
			{
				SetPlayerToFacePlayer(playerid, offererid);
				SetPlayerToFacePlayer(offererid, playerid);
				ApplyAnimation(playerid, "BLOWJOBZ", "BJ_STAND_LOOP_W", 4.1, true, false, false, false, 0, true);
				ApplyAnimation(offererid, "BLOWJOBZ", "BJ_STAND_LOOP_P", 4.1, true, false, false, false, 0, true);
			}
			case 7: //salam
			{
				SetPlayerToFacePlayer(playerid, offererid);
				SetPlayerToFacePlayer(offererid, playerid);
				ApplyAnimation(playerid, "GANGS", "hndshkaa", 4.1, false, false, false, false, 0, true);
				ApplyAnimation(offererid, "GANGS", "hndshkaa", 4.1, false, false, false, false, 0, true);
			}
			case 8: //salam2
			{
				SetPlayerToFacePlayer(playerid, offererid);
				SetPlayerToFacePlayer(offererid, playerid);
				ApplyAnimation(playerid, "GANGS", "hndshkba", 4.1, false, false, false, false, 0, true);
				ApplyAnimation(offererid, "GANGS", "hndshkba", 4.1, false, false, false, false, 0, true);
			}
			case 9: //salam3
			{
				SetPlayerToFacePlayer(playerid, offererid);
				SetPlayerToFacePlayer(offererid, playerid);
				ApplyAnimation(playerid, "GANGS", "hndshkca", 4.1, false, false, false, false, 0, true);
				ApplyAnimation(offererid, "GANGS", "hndshkca", 4.1, false, false, false, false, 0, true);
			}
			case 10: //salam4
			{
				SetPlayerToFacePlayer(playerid, offererid);
				SetPlayerToFacePlayer(offererid, playerid);
				ApplyAnimation(playerid, "GANGS", "hndshkcb", 4.1, false, false, false, false, 0, true);
				ApplyAnimation(offererid, "GANGS", "hndshkcb", 4.1, false, false, false, false, 0, true);
			}
			case 11: //salam5
			{
				SetPlayerToFacePlayer(playerid, offererid);
				SetPlayerToFacePlayer(offererid, playerid);
				ApplyAnimation(playerid, "GANGS", "hndshkda", 4.1, false, false, false, false, 0, true);
				ApplyAnimation(offererid, "GANGS", "hndshkda", 4.1, false, false, false, false, 0, true);
			}
			case 12: //salam6
			{
				SetPlayerToFacePlayer(playerid, offererid);
				SetPlayerToFacePlayer(offererid, playerid);
				ApplyAnimation(playerid, "GANGS", "hndshkea", 4.1, false, false, false, false, 0, true);
				ApplyAnimation(offererid, "GANGS", "hndshkea", 4.1, false, false, false, false, 0, true);
			}
			case 13: //salam7
			{
				SetPlayerToFacePlayer(playerid, offererid);
				SetPlayerToFacePlayer(offererid, playerid);
				ApplyAnimation(playerid, "GANGS", "hndshkfa", 4.1, false, false, false, false, 0, true);
				ApplyAnimation(offererid, "GANGS", "hndshkfa_swt", 4.1, false, false, false, false, 0, true);
			}
		}
		ShowTDN(playerid, NOTIFICATION_INFO, "Pemain tersebut telah menerima tawaran eshared anda.");
		AccountData[playerid][pESharedType] = 0;
		AccountData[playerid][pESharedOfferer] = INVALID_PLAYER_ID;
	}
	return 1;
}

YCMD:medic(playerid, params[], help)
{
	if(Iter_Count(LSFDDuty) > 2)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Sedang ada EMS yang sedang on duty, mohon kirim sinyal!");

	if(!AccountData[playerid][pKnockdown])
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang pingsan!");
	
	if(AccountData[playerid][pDuringUseLocalMedic])
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang diobati oleh dokter lokal, mohon tunggu!");

	if(gettime() < AccountData[playerid][pAccDeathTime])
		return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Anda harus menunggu %d menit.", (AccountData[playerid][pAccDeathTime] - gettime())/60));

	AccountData[playerid][pDuringUseLocalMedic] = true;
	AccountData[playerid][pActivityTime] = 1;
	PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENYEMBUHKAN");
	ShowProgressBar(playerid);
	pMedisLokalTimer[playerid] = true;
	return 1;
}

YCMD:stopsmoke(playerid, params[], help)
{
	if(!AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang merokok!");

	if(pIsVaping[playerid])
		RemovePlayerAttachedObject(playerid, 8);

	AccountData[playerid][pIsSmoking] = false;
	AccountData[playerid][pIsSmokeBlowing] = false;
	AccountData[playerid][pSmokedTimes] = 0;
	ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah berhenti menghisapnya.");
	return 1;
}

YCMD:stopeating(playerid, params[], help)
{
	if(AccountData[playerid][pEatingStep] == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang makan!");

	AccountData[playerid][pEatingStep] = 0;

	ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah berhenti makan.");
	return 1;
}

YCMD:stopdrinking(playerid, params[], help)
{
	if(AccountData[playerid][pDrinkingStep] == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang minum!");

	AccountData[playerid][pDrinkingStep] = 0;

	ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah berhenti minum.");
	return 1;
}

YCMD:sellbottle(playerid, params[], help)
{
	static playerbottles;
	playerbottles = Inventory_Count(playerid, "Botol");

	if(!IsPlayerInRangeOfPoint(playerid, 3.0, 2180.6221,-1985.8651,13.5506))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di tempat penjualan!");

	if(playerbottles < 1)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki botol untuk dijual!");

	static pricing;
	pricing = playerbottles * 20;
	GivePlayerMoneyEx(playerid, pricing);
	ShowItemBox(playerid, "Botol", sprintf("Removed %dx", playerbottles), 19570, 4);
	ShowItemBox(playerid, "Cash", sprintf("Received $%sx", FormatMoney(pricing)), 1212, 5);
	
	Inventory_Remove(playerid, "Botol", playerbottles);
	return 1;
}

YCMD:sellplastic(playerid, params[], help)
{
	static playerbottles;
	playerbottles = Inventory_Count(playerid, "Plastik");

	if(!IsPlayerInRangeOfPoint(playerid, 3.0, 2180.6221,-1985.8651,13.5506))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di tempat penjualan!");

	if(playerbottles < 1)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Plastik untuk dijual!");

	static pricing;
	pricing = playerbottles * 20;
	GivePlayerMoneyEx(playerid, pricing);
	ShowItemBox(playerid, "Plastik", sprintf("Removed %dx", playerbottles), 1265, 4);
	ShowItemBox(playerid, "Cash", sprintf("Received $%sx", FormatMoney(pricing)), 1212, 5);
	
	Inventory_Remove(playerid, "Plastik", playerbottles);
	return 1;
}

YCMD:toggle(playerid, params[], help)
{
	static string[522];
	format(string, sizeof(string), "Name\tToggle\n\
	Private Messages\t%s\n\
	"GRAY"Global OOC Messages\t%s\n\
	Login Messages\t%s\n\
	"GRAY"Level Up Messages\t%s\n\
	Advertisement Messages\t%s\n\
	"GRAY"Admin Command Messages\t%s\n\
	Pewarta Broadcast\t%s", (ToggleInfo[playerid][TogPM]) ? (""DARKGREEN"Active") : (""DARKRED"Inactive"),
	(ToggleInfo[playerid][TogGOOC]) ? (""DARKGREEN"Active") : (""DARKRED"Inactive"),
	(ToggleInfo[playerid][TogLogin]) ? (""DARKGREEN"Active") : (""DARKRED"Inactive"),
	(ToggleInfo[playerid][TogLevel]) ? (""DARKGREEN"Active") : (""DARKRED"Inactive"),
	(ToggleInfo[playerid][TogAdv]) ? (""DARKGREEN"Active") : (""DARKRED"Inactive"),
	(ToggleInfo[playerid][TogAdmCmd]) ? (""DARKGREEN"Active") : (""DARKRED"Inactive"),
	(ToggleInfo[playerid][TogBroadcast]) ? (""DARKGREEN"Listening") : (""DARKRED"Deafen"));
    Dialog_Show(playerid, "ToggleSettings", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Toggle Settings", string, "Toggle", "Batal");
	return 1;
}

YCMD:skydive(playerid, params[], help)
{
    if(!IsPlayerInRangeOfPoint(playerid, 3.0, -2237.6172,-1744.6632,480.8505) || GetPlayerVirtualWorld(playerid) != 0 || GetPlayerInterior(playerid) != 0)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di area skydive!");

    if(AccountData[playerid][pMoney] < 650)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

    TakePlayerMoneyEx(playerid, 650);
    GivePlayerWeaponEx(playerid, 46, 1, WEAPON_TYPE_PLAYER);
    SetPlayerPos(playerid, -2226.1772,-1690.2449,810.7187);
    ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah dijatuhkan dari helikopter, kenakanlah parasut untuk mendarat!");
    Anticheat[playerid][acImmunity] = gettime() + 5;
	return 1;
}

/*
YCMD:rps(playerid, params[], help)
{
	new otherid, string[32];
	if(sscanf(params, "ds[32]", otherid, string)) return SUM(playerid, "/rps [playerid] [name] (rock, paper, scissor)");

	if(!AccountData[otherid][pSpawned]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(!IsPlayerNearPlayer(playerid, otherid, 3.5)) return SEM(playerid, "You are not close to that player!");

	
	return 1;
}
*/

YCMD:fams(playerid, params[], help)
{
	static count, string[1028];
	count = 0;
	format(string, sizeof(string), "FID\tName\tOnline\tLeader\n");
	foreach(new fmid : Fams)
	{
		format(string, sizeof(string), "%s%d\t%s\t%s\t%s\n", string, fmid, FamilyData[fmid][famName], CountFamilyOnline(fmid), GetFamilyOwnerName(fmid));
		count ++;
	}
	if(count == 0)
	{
		Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Daftar Nama Badside/Family Resmi", 
		"Tidak ada data yang dapat ditampilkan!", "Tutup", "");
		return 1;
	}

	Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Daftar Nama Badside/Family Resmi", 
	string, "Tutup", "");
	return 1;
}

YCMD:mywarns(playerid, params[], help)
{
    static string[1024], count;
    count = 0;
    format(string, sizeof(string), "Type\tIssuer\tDate\tReason\n");
    for(new id; id < 100; ++id)
    {
        if(PlayerWarning[playerid][id][warnExists] && PlayerWarning[playerid][id][warnOwner] == AccountData[playerid][pID]) 
        {
            switch(PlayerWarning[playerid][id][warnType])
            {
                case 1:
                {
                    format(string, sizeof(string), "%s"GREEN"[WARN]\t"WHITE"%s\t%s\t%s\n", string, PlayerWarning[playerid][id][warnIssuer], PlayerWarning[playerid][id][warnDate], PlayerWarning[playerid][id][warnReason]);
                }
                case 2:
                {
                    format(string, sizeof(string), "%s"YELLOW"[JAIL]\t"WHITE"%s\t%s\t%s\n", string, PlayerWarning[playerid][id][warnIssuer], PlayerWarning[playerid][id][warnDate], PlayerWarning[playerid][id][warnReason]);
                }
                case 3:
                {
                    format(string, sizeof(string), "%s"ORANGERED"[BAN]\t"WHITE"%s\t%s\t%s\n", string, PlayerWarning[playerid][id][warnIssuer], PlayerWarning[playerid][id][warnDate], PlayerWarning[playerid][id][warnReason]);
                }
            }
            PlayerListitem[playerid][count++] = id;
        }
    }

    if(count == 0)
    {
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Warning History", "Anda tidak memiliki riwayat peringatan apapun!", "Tutup", "");
    }
    else
    {
        Dialog_Show(playerid, "CheckMyWarns", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Warning History", string, "Pilih", "Tutup");
    }
    return 1;
}

YCMD:eject(playerid, params[], help)
{
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus duduk di kursi driver!");

    static targetid;
    foreach(new i : PvtVehicles)
    {
        if(PlayerVehicle[i][pVehOwnerID] == AccountData[playerid][pID] && GetPlayerVehicleID(playerid) == PlayerVehicle[i][pVehPhysic])
        {
            if(sscanf(params, "u", targetid)) return SUM(playerid, "/eject [name/playerid]");
            if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
            if(!AccountData[targetid][pSpawned]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut belum spawn!");
            if(GetPlayerVehicleID(targetid) != GetPlayerVehicleID(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak berada di dalam kendaraan anda!");        

            RemovePlayerFromVehicle(targetid);
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menendang Pemain tersebut dari kendaraan!");
            ShowTDN(targetid, NOTIFICATION_INFO, "Anda telah ditendang paksa dari kendaraan!");
            return 1;
        }
    }
    ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
    return 1;
}

YCMD:afk(playerid, params[], help)
{
	if(!AccountData[playerid][pIsAFK])
	{
		SetPlayerAFK(playerid);
		return 1;
	}

	new afknumber;
	if(sscanf(params, "d", afknumber))
    {
		SUM(playerid, "/afk [code]");
		SendClientMessageEx(playerid, -1, "Use %d as a code!", AccountData[playerid][pAFKNumb]);
		return 1;
	}

	if(afknumber != AccountData[playerid][pAFKNumb])
	{
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);

		new reandafk = Random(999);
		AccountData[playerid][pAFKNumb] = reandafk;
		
		ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Mohon gunakan '/afk %d' untuk keluar dari AFK mode!", reandafk));
		return 1;
	}
	
	AccountData[playerid][pIsAFK] = false;
    AccountData[playerid][pAFKCount] = 0;
    AccountData[playerid][pAFKTime] = 0;
    AccountData[playerid][pAFKNumb] = 0;
    AccountData[playerid][afkx] = 0.0;
    AccountData[playerid][afky] = 0.0;
    AccountData[playerid][afkz] = 0.0;

	SetPlayerColor(playerid, X11_WHITE);
	ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah keluar dari mode AFK!");

	TogglePlayerControllable(playerid, true);
	return 1;
}

// YCMD:rpquiz(playerid, params[], help)
// {
// 	if(!IsPlayerInRangeOfPoint(playerid, 3.5, 1368.1154,1568.2551,17.0003)) return SEM(playerid, "You are not at City Hall!"); 
// 	if(AccountData[playerid][pLevel] < 5) return SEM(playerid, "You can only perform the RP Quiz when your character's level has reached 5!"); 
	
// 	for(new x; x < sizeof(g_RPQuizData); x++)
// 	{
// 		PlayerListitem[playerid][x] = -1;
// 	}

// 	new rnadquiz;
// 	do {
// 		rnadquiz = random(sizeof(g_RPQuizData));
//     } while (IsRPQuizTaken(playerid, rnadquiz));

// 	AccountData[playerid][pRPQuizQuestion] ++;
// 	PlayerListitem[playerid][AccountData[playerid][pRPQuizQuestion]] = rnadquiz;
// 	Dialog_Show(playerid, "RPQuizTest", DIALOG_STYLE_INPUT, sprintf("{DA9100}Pahlawan Roleplay "WHITE"- RP Quiz: %d of 20 Questions", AccountData[playerid][pRPQuizQuestion]), 
// 	g_RPQuizData[rnadquiz][RPQuiz_Question], "Input", "Batal");

// 	Anticheat[playerid][acImmunity] = gettime() + 5;
// 	SetPlayerPos(playerid, 1884.1031,-2542.9663,17.2344);
// 	SetPlayerFacingAngle(playerid, 269.7495);
// 	SetPlayerVirtualWorld(playerid, playerid+1);
// 	SetPlayerInterior(playerid, 0);
// 	return 1;
// }

YCMD:mylevel(playerid, params[], help)
{
	static string[800], pltm;
	pltm = AccountData[playerid][pLevel]*5;
	format(string, sizeof(string), ""WHITE"Level karakter anda saat ini adalah "YELLOW"level %d\n\
	"WHITE"Playtime karakter anda saat ini adalah: "YELLOW"%02d hours %02d minutes %02d seconds\n\
	"WHITE"Untuk naik level berikutnya, dibutuhkan playtime: "CYAN"%02d hours", AccountData[playerid][pLevel], AccountData[playerid][pHours],AccountData[playerid][pMinutes],AccountData[playerid][pSeconds], pltm);
	Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Level Check", string, "Tutup", "");
	return 1;
}

YCMD:pawn(playerid, params[], help)
{
	if(!IsPlayerInRangeOfPoint(playerid, 3.0, 795.0921,1687.0704,5.2813))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di pawn shop!");

	Dialog_Show(playerid, "PawnShopCatalog", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Pawn Shop", 
	"Alumunium\n\
	"GRAY"Kaca\n\
	Baja\n\
	"GRAY"Karet\n\
	Plastik\n\
	"GRAY"Jual Elektronik Rusak", "Pilih", "Batal"); 
	return 1;
}

YCMD:handbrake(playerid, params[], help)
{
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di kursi driver!");

	new vehid = GetPlayerVehicleID(playerid);
	foreach(new carid : PvtVehicles)
	{
		if(vehid == PlayerVehicle[carid][pVehPhysic])
		{
			if(!PlayerVehicle[carid][pVehHandbraked])
			{
				PlayerVehicle[carid][pVehHandbraked] = true;
				Vehicle_GetStatus(carid);
				ShowTDN(playerid, NOTIFICATION_INFO, "Vehicle Handbrake ~g~aktif.");
			}
			else
			{
				PlayerVehicle[carid][pVehHandbraked] = false;
				ShowTDN(playerid, NOTIFICATION_INFO, "Vehicle Handbrake ~r~tidak aktif.");
			}
		}
	}
	return 1;
}

YCMD:sid(playerid, params[], help)
{
	new hjhs[144];
	switch(AccountData[playerid][pToggleNameID])
	{
		case false:
		{
			AccountData[playerid][pToggleNameID] = true;

			foreach(new i : Player) if(i != playerid)
			{
				if(AccountData[i][pSpawned] && AccountData[i][IsLoggedIn])
				{
					format(hjhs, sizeof(hjhs), "%s (%s) [%d]", AccountData[i][pName], AccountData[i][pUCP], i);
					AccountData[playerid][pNameIDLabel][i] = CreateDynamic3DTextLabel(hjhs, Y_WHITE, 0.0, 0.0, 0.1, 20.0, i, INVALID_VEHICLE_ID, 1, -1, -1, playerid, 20.0, -1, 0);
				}
			}
			ShowTDN(playerid, NOTIFICATION_INFO, "UCP ID dan nama ~g~aktif.");
		}
		case true:
		{
			AccountData[playerid][pToggleNameID] = false;

			foreach(new i : Player) if(i != playerid)
			{
				if(AccountData[i][pSpawned] && AccountData[i][IsLoggedIn])
				{
					if(DestroyDynamic3DTextLabel(AccountData[playerid][pNameIDLabel][i]))
						AccountData[playerid][pNameIDLabel][i] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
				}
			}

			ShowTDN(playerid, NOTIFICATION_INFO, "UCP ID dan nama ~r~tidak aktif.");
		}
	}
	return 1;
}

YCMD:cook(playerid, params[], help)
{
    if(!IsPlayerInFNBTypeFaction(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya dapat diakses oleh anggota faction berjenis restoran!");
    
    if(!AccountData[playerid][pOnDuty]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus on duty terlebih dahulu!");

    switch(AccountData[playerid][pFaction])
    {
        case FACTION_PUTRIDELI:
        {
            if(!IsPlayerInRangeOfPoint(playerid, 3.0, 654.8177,-1870.0217,6.5251))
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di spot masak!");

            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

            HideNotifBox(playerid);
            Dialog_Show(playerid, "PutrideliCooking", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Putri Deli Masak", 
            "Nama Makanan & Minuman\tBahan\t-\n\
            BBQ Delicy\tKentang Potong: 5x | Kubis Potong: 5x | Bawang Potong: 5x | Tomat Potong: 5x\tAir: 5x | Gula: 5x | Micin: 5x | Ayam Kemas: 5x\n\
			"GRAY"Rice Combo\t"GRAY"Kentang Potong: 5x | Kubis Potong: 5x | Bawang Potong: 5x | Tomat Potong: 5x\t"GRAY"Air: 5x | Gula: 5x | Micin: 5x | Ayam Kemas: 5x", "Pilih", "Batal");
        }
        case FACTION_DINARBUCKS:
        {
            if(!IsPlayerInRangeOfPoint(playerid, 3.0, 381.2641,-184.5646,1000.6328))
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di spot masak!");

            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

            HideNotifBox(playerid);
            Dialog_Show(playerid, "DinarbucksCooking", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Pinky Tiger Masak", 
            "Nama Makanan & Minuman\tBahan\t-\n\
            Buckshot Special\tKentang Potong: 5x | Kubis Potong: 5x | Bawang Potong: 5x | Tomat Potong: 5x\tAir: 5x | Gula: 5x | Micin: 5x | Ayam Kemas: 5x\n\
			"GRAY"Frenchy Velty\t"GRAY"Kentang Potong: 5x | Kubis Potong: 5x | Bawang Potong: 5x | Tomat Potong: 5x\t"GRAY"Air: 5x | Gula: 5x | Micin: 5x | Ayam Kemas: 5x", "Pilih", "Batal");
        }
		case FACTION_SRIMERSING:
		{
			if(!IsPlayerInRangeOfPoint(playerid, 3.0, -320.5377,1298.4698,54.3645))
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di spot masak!");

            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

            HideNotifBox(playerid);
            Dialog_Show(playerid, "SriMersingCooking", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Sri Mersing Masak", 
            "Nama Makanan & Minuman\tBahan\t-\n\
            Minang Combo\tKentang Potong: 5x | Kubis Potong: 5x | Bawang Potong: 5x | Tomat Potong: 5x\tAir: 5x | Gula: 5x | Micin: 5x | Ayam Kemas: 5x\n\
			"GRAY"Malaya Shine\t"GRAY"Kentang Potong: 5x | Kubis Potong: 5x | Bawang Potong: 5x | Tomat Potong: 5x\t"GRAY"Air: 5x | Gula: 5x | Micin: 5x | Ayam Kemas: 5x", "Pilih", "Batal");
		}
		case FACTION_TEXAS:
		{
			if(!IsPlayerInRangeOfPoint(playerid, 3.0, 2721.6523,739.3129,11.3191))
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di spot masak!");

			if(AccountData[playerid][pFactionRank] < 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Junior untuk akses perintah ini!");
            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

            HideNotifBox(playerid);
            Dialog_Show(playerid, "TexasChickenCooking", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Texas Chicken Masak", 
            "Nama Makanan & Minuman\tBahan\t-\n\
            Fresh Solar\tKentang Potong: 5x | Kubis Potong: 5x | Bawang Potong: 5x | Tomat Potong: 5x\tAir: 5x | Gula: 5x | Micin: 5x | Ayam Kemas: 5x\n\
			"GRAY"Softex Flash\t"GRAY"Kentang Potong: 5x | Kubis Potong: 5x | Bawang Potong: 5x | Tomat Potong: 5x\t"GRAY"Air: 5x | Gula: 5x | Micin: 5x | Ayam Kemas: 5x\n\
            Purple Sweet\tKentang Potong: 5x | Kubis Potong: 5x | Bawang Potong: 5x | Tomat Potong: 5x\tAir: 5x | Gula: 5x | Micin: 5x | Ayam Kemas: 5x", "Pilih", "Batal");
		}
    }
    return 1;
}

YCMD:slice(playerid, params[], help)
{
	if(!IsPlayerInFNBTypeFaction(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya dapat diakses oleh anggota faction berjenis restoran!");

    if(!AccountData[playerid][pOnDuty]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus on duty terlebih dahulu!");
    
    switch(AccountData[playerid][pFaction])
    {
        case FACTION_PUTRIDELI:
        {
            if(!IsPlayerInRangeOfPoint(playerid, 3.0, 659.5117,-1870.5515,6.5251))
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di spot pemotongan!");

            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

            HideNotifBox(playerid);
			Dialog_Show(playerid, "FactionRestoSlicing", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Putri Deli Potong", 
			"Apa yang ingin anda potong?\n\
            Kentang\n\
            Kubis\n\
            Bawang\n\
            Tomat", "Pilih", "Batal");
        }
        case FACTION_DINARBUCKS:
        {
            if(!IsPlayerInRangeOfPoint(playerid, 3.0, 381.2641,-182.3879,1000.6328))
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di spot pemotongan!");

            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

            HideNotifBox(playerid);
            Dialog_Show(playerid, "FactionRestoSlicing", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Pinky Tiger Potong", 
			"Apa yang ingin anda potong?\n\
            Kentang\n\
            Kubis\n\
            Bawang\n\
            Tomat", "Pilih", "Batal");
        }
        case FACTION_SRIMERSING:
        {
            if(!IsPlayerInRangeOfPoint(playerid, 3.0, -328.0962,1301.1195,54.3635))
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di spot pemotongan!");

            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

            HideNotifBox(playerid);
            Dialog_Show(playerid, "FactionRestoSlicing", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Sri Mersing Potong", 
			"Apa yang ingin anda potong?\n\
            Kentang\n\
            Kubis\n\
            Bawang\n\
            Tomat", "Pilih", "Batal");
        }
        case FACTION_TEXAS:
        {
            if(!IsPlayerInRangeOfPoint(playerid, 3.0, 2725.5566,741.7584,11.3191))
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di spot pemotongan!");
			
			if(AccountData[playerid][pFactionRank] < 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Junior untuk akses perintah ini!");
            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

            HideNotifBox(playerid);
            Dialog_Show(playerid, "FactionRestoSlicing", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Texas Chicken Potong", 
			"Apa yang ingin anda potong?\n\
            Kentang\n\
            Kubis\n\
            Bawang\n\
            Tomat", "Pilih", "Batal");
        }
    }
    return 1;
}

YCMD:flare(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] != FACTION_LSPD && AccountData[playerid][pFaction] != FACTION_LSFD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian ataupun Paramedis!");

    if(AccountData[playerid][pFlareUsed]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah meletakkan flare!");


    if(DestroyDynamicObject(AccountData[playerid][pFlareObjid]))
        AccountData[playerid][pFlareObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

    new Float:pos[3];
    AccountData[playerid][pFlareUsed] = true;
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
    AccountData[playerid][pFlareObjid] = CreateDynamicObject(18728, pos[0], pos[1], pos[2]-0.50, 0.0, 0.0, 0.0, 0, 0, -1, 200.00, 200.00, -1);

    foreach(new i : Player)
    {
        if(AccountData[i][pSpawned] && AccountData[i][pOnDuty])
        {
            if(AccountData[i][pFaction] == FACTION_LSFD || AccountData[i][pFaction] == FACTION_LSPD)
            {
				if(DestroyDynamicMapIcon(AccountData[playerid][pFlareIcon][i]))
        			AccountData[playerid][pFlareIcon][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;

                AccountData[playerid][pFlareIcon][i] = CreateDynamicMapIcon(pos[0], pos[1], pos[2], 0, Y_ORANGE, 0, 0, i, 60000, MAPICON_GLOBAL, -1, 0);
                SendClientMessageEx(i, 0x7296AAFF, "%s %s (%d) meletakkan flare di daerah %s", GetRankName(playerid), AccountData[playerid][pName], playerid, GetLocation(pos[0], pos[1], pos[2]));
            }
        }
    }
    return 1;
}

YCMD:unflare(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] != FACTION_LSPD && AccountData[playerid][pFaction] != FACTION_LSFD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian ataupun Paramedis!");

    if(!AccountData[playerid][pFlareUsed]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum meletakkan flare!");

    AccountData[playerid][pFlareUsed] = false;

    if(DestroyDynamicObject(AccountData[playerid][pFlareObjid]))
        AccountData[playerid][pFlareObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

	foreach(new i : Player)
    {
        if(AccountData[i][pSpawned] && AccountData[i][pOnDuty])
        {
            if(AccountData[i][pFaction] == FACTION_LSFD || AccountData[i][pFaction] == FACTION_LSPD)
            {
    			if(DestroyDynamicMapIcon(AccountData[playerid][pFlareIcon][i]))
        			AccountData[playerid][pFlareIcon][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
			}
		}
	}
    return 1;
}

YCMD:setbadge(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] != FACTION_LSPD && AccountData[playerid][pFaction] != FACTION_LSFD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian ataupun Paramedis!");

    if(AccountData[playerid][pFaction] == FACTION_LSPD  && AccountData[playerid][pFactionRank] < 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank KOMPOL untuk akses ini!");
    if(AccountData[playerid][pFaction] == FACTION_LSFD && AccountData[playerid][pFactionRank] < 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank WAKADIR untuk akses ini!");

	new otherid, badgenumber;
    if(sscanf(params, "dd", otherid, badgenumber)) return SUM(playerid, "/setbadge [otherid] [number badge]");

    if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if(AccountData[otherid][pFaction] != AccountData[playerid][pFaction]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak berada di dalam faction yang sama dengan anda!");

    AccountData[otherid][pBadge] = badgenumber;

    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengganti nomor lencana Pemain tersebut!");
    ShowTDN(otherid, NOTIFICATION_INFO, "Nomor lencana anda telah diganti!");
    return 1;
}

YCMD:showbadge(playerid, params[], help)
{
	
	return 1;
}

YCMD:livestream(playerid, params[], help)
{
	new title[144];
	if(sscanf(params, "s[144]", title))
	{
		foreach(new i : Player) if(AccountData[i][pSpawned])
		{
			if(AccountData[i][pLivestreamMode])
			{
				SendClientMessageEx(playerid, X11_ORANGE, "| ID: %d | "GRAY"%s : "LIGHTGREEN"%s", i, AccountData[i][pName], AccountData[i][pLivestreamTitle]);
			}
		}
		SendClientMessage(playerid, -1, "CMD "CMDEA"'/livestream [judul]' "WHITE"jika sedang live dan "CMDEA"'/livestream off' "WHITE"untuk menonaktifkan.");
		return 1;
	}

	if(!strcmp(title, "off", true))
    {
		if(!AccountData[playerid][pLivestreamMode]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang membagikan livestream!");

		AccountData[playerid][pLivestreamMode] = false;
		AccountData[playerid][pLivestreamTitle][0] = EOS;
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah berhenti membagikan status livestream.");
	}
	else
	{
		AccountData[playerid][pLivestreamMode] = true;
		strcopy(AccountData[playerid][pLivestreamTitle], title);
		ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membagikan status livestream!");

		static string[144];
		format(string, sizeof(string), "(Livestream) "WHITE"Player "YELLOW"%s [ID: %d] "WHITE"sekarang sedang siaran langsung, cek di "CMDEA"'/livestream'", AccountData[playerid][pName], playerid);
		SendClientMessageToAll(Y_SERVER, string);
	}
	return 1;
}

YCMD:unbfold(playerid, params[], help)
{
	if(AccountData[playerid][pBlindfolded]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
	
	new otherid;
	if(sscanf(params, "d", otherid)) return SUM(playerid, "/unbfold [playerid]");

	if(otherid == playerid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya terhadap diri sendiri!");
	if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(!IsPlayerNearPlayer(playerid, otherid, 3.2)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan Pemain tersebut!");
	if(!AccountData[otherid][pBlindfolded]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak sedang di-bindfold!");

	AccountData[otherid][pBlindfolded] = false;
	RemovePlayerAttachedObject(otherid, 9);
	SetPlayerSpecialAction(otherid, SPECIAL_ACTION_NONE);
	TextDrawHideForPlayer(otherid, BlindfoldTD);
	ShowRadarMapForPlayer(playerid);

	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil melepaskan blindfold Pemain tersebut!");
	return 1;
}

YCMD:tutorial(playerid, params[], help)
{
	if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
	if(AccountData[playerid][pTutorialPassed]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah menyelesaikan tutorial!");
	if(pTutorialStep[playerid] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang tutorial, silakan selesaikan!");

	pTutorialStep[playerid] = 0;

	ResetAllRaceCP(playerid);
	
	pTutorialRCP[playerid] = CreateDynamicRaceCP(1, __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], __g_TutorialPos[pTutorialStep[playerid]][0], __g_TutorialPos[pTutorialStep[playerid]][1], __g_TutorialPos[pTutorialStep[playerid]][2], 3.5, 0, 0, playerid, 6000.00, -1, 0);
	SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Tutorial dimulai! Ikuti "RED"checkpoint "YELLOW"yang muncul di layar.");
	SendClientMessage(playerid, X11_YELLOW, "[Tutorial] Baca setiap petunjuk dengan teliti agar kamu paham cara bermainnya.");
	return 1;
}

YCMD:starterpack(playerid, params[], help)
{
	//if(gettime() > 1720030356) return SEM(playerid, "There is no active compensation or it has already ended!");
	if(pKompensasiTimer[playerid]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Mohon tunggu, anda sedang dalam proses klaim starterpack!");

	new query[128];
	mysql_format(g_SQL, query, sizeof(query), "SELECT `claimedSP` FROM `player_ucp` WHERE `UCP` = '%e' LIMIT 1", AccountData[playerid][pUCP]);
	mysql_pquery(g_SQL, query, "CheckClaimedSP", "i", playerid);
	return 1;
}

YCMD:saveme(playerid, params[], help)
{
	if(AccountData[playerid][pInEvent]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya di dalam event!");
	
	Anticheat[playerid][acImmunity] = gettime() + 11;
	UpdateAccountData(playerid);
	RemovePlayerWeapons(playerid);
	SetWeapons(playerid);
	foreach(new vp : PvtVehicles)
	{
		if(PlayerVehicle[vp][pVehOwnerID] == AccountData[playerid][pID])
		{
			SavePlayerVehicle(vp);
		}
	}

	SendClientMessage(playerid, X11_YELLOW, "[Pahlawan Roleplay Database] All your character data has been successfully saved!");
	return 1;
}

YCMD:out(playerid, params[], help)
{
	new valuetype;
	if(sscanf(params, "d", valuetype)) return SUM(playerid, "/out [1. Garbage, 2. Trunk]");
	if(valuetype < 1 || valuetype > 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid type! (1 - 2)");

	if(valuetype == 1)
	{
		if(pInSpecMode[playerid] != 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang bersembunyi di tong sampah!");

        SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pSkin], AccountData[playerid][pPos][0], AccountData[playerid][pPos][1], AccountData[playerid][pPos][2], AccountData[playerid][pPos][3], 0, 0, 0, 0, 0, 0);
        TogglePlayerSpectating(playerid, false);

		PlayerSpectatePlayer(playerid, INVALID_PLAYER_ID);
        PlayerSpectateVehicle(playerid, INVALID_VEHICLE_ID);

		pInSpecMode[playerid] = 0;
		
		TextDrawHideForPlayer(playerid, GarbageHideTD[0]);
		TextDrawHideForPlayer(playerid, GarbageHideTD[1]);
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah keluar dari persembunyian.");

		PlayerPlaySound(playerid, 6802, 0, 0, 0);
	}
	else if(valuetype == 2)
	{
		if(pInSpecMode[playerid] != 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang bersembunyi di trunk kendaraan!");

		new vid = SavingVehID[playerid];

		if(vid == INVALID_VEHICLE_ID || !IsValidVehicle(vid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tidak ada di server!");
		if(VehicleCore[vid][vCoreLocked]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini sedang terkunci!");

		GetVehicleBoot(vid, AccountData[playerid][pPos][0], AccountData[playerid][pPos][1], AccountData[playerid][pPos][2]);

		AccountData[playerid][pInterior] = GetVehicleInterior(vid);
		AccountData[playerid][pWorld] = GetVehicleVirtualWorld(vid);

		SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pSkin], AccountData[playerid][pPos][0], AccountData[playerid][pPos][1], AccountData[playerid][pPos][2], 180.0, 0, 0, 0, 0, 0, 0);
		TogglePlayerSpectating(playerid, false);

		PlayerSpectatePlayer(playerid, INVALID_PLAYER_ID);
        PlayerSpectateVehicle(playerid, INVALID_VEHICLE_ID);
		
		SavingVehID[playerid] = INVALID_VEHICLE_ID;
		pInSpecMode[playerid] = 0;

		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah keluar dari trunk kendaraan.");

		PlayerPlaySound(playerid, 12200, 0, 0, 0);
	}
	return 1;
}

YCMD:time(playerid, params[], help)
{
	static string[555];

	format(string, sizeof(string), " \nWaktu saat ini menunjukkan %s\n", GetAdvTime());
	Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Server Time", string, "Tutup", "");
	return 1;
}

YCMD:cekiter(playerid, params[], help)
{
	new vehid;
	if(sscanf(params, "d", vehid)) return SUM(playerid, "/cekiter [vehid]");

	if(!Iter_Contains(Vehicle, vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut tidak ada di server!");
	
	new iterid = Vehicle_GetIterID(vehid);
	SendClientMessageEx(playerid, Y_LIGHTRED, "AdmCmd: The iterator ID for VID: %d is %d.", vehid, iterid);
	return 1;
}

YCMD:sb(playerid, params[], help)
{
	if(!IsPlayerInAnyVehicle(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di dalam kendaraan apapun!");

	new vid = GetPlayerVehicleID(playerid);
	if(vid != INVALID_VEHICLE_ID)
	if(IsABike(vid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak memiliki seatbelt!");

	switch(AccountData[playerid][pBuckledOn])
	{
		case false: 
		{
        	AccountData[playerid][pBuckledOn] = true;
        	ShowTDN(playerid, NOTIFICATION_INFO, "Seatbelt ~g~aktif!");
        	SendRPMeAboveHead(playerid, "Mengencangkan sabuk pengaman.");
		}
		case true: 
		{
			AccountData[playerid][pBuckledOn] = false;
			ShowTDN(playerid, NOTIFICATION_INFO, "Seatbelt ~r~tidak aktif!");
			SendRPMeAboveHead(playerid, "Melepaskan sabuk pengaman.");
		}
	}
	return 1;
}

YCMD:addlabel(playerid, params[], help)
{
	if(AccountData[playerid][pFaction] == FACTION_NONE) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari faction manapun!");

	Dialog_Show(playerid, "MyFactionLabel", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay - "WHITE"Faction Label", 
	"Slot\tLabel\n\
	#1\t%s\n\
	#2\t%s\n\
	#3\t%s", "Pilih", "Batal", (IsValidDynamic3DTextLabel(pFactionLabel[playerid][0])) ? (""RED"Used") : (""GREEN"Avail"),
	(IsValidDynamic3DTextLabel(pFactionLabel[playerid][1])) ? (""RED"Used") : (""GREEN"Avail"),
	(IsValidDynamic3DTextLabel(pFactionLabel[playerid][2])) ? (""RED"Used") : (""GREEN"Avail"));
	return 1;
}

Dialog:MyFactionLabel(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	switch(listitem)
	{
		case 0:
		{
			AccountData[playerid][pTempValue] = 0;
			Dialog_Show(playerid, "MyFactLabelEdit", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Faction Label #1", 
			"Edit Text Label\nEdit Label Position\nRemove Label", "Pilih", "Batal");
		}
		case 1:
		{
			AccountData[playerid][pTempValue] = 1;
			Dialog_Show(playerid, "MyFactLabelEdit", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Faction Label #2", 
			"Edit Text Label\nEdit Label Position\nRemove Label", "Pilih", "Batal");
		}
		case 2:
		{
			AccountData[playerid][pTempValue] = 2;
			Dialog_Show(playerid, "MyFactLabelEdit", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Faction Label #3", 
			"Edit Text Label\nEdit Label Position\nRemove Label", "Pilih", "Batal");
		}
	}
	return 1;
}

Dialog:MyFactLabelEdit(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	new id = AccountData[playerid][pTempValue];
	if(id == -1) return 1;

	switch(listitem)
	{
		case 0:
		{
			Dialog_Show(playerid, "FactLabelEditText", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Text Label", 
			"Mohon masukkan tulisan label yang ingin dibuat:\n\
			(n) = text akan berada di bawah/baris baru.\n\
			(r) = warna text merah.\n\
			(b) = warna text hitam.\n\
			(y) = warna text kuning.\n\
			(bl) = warna text biru.\n\
			(g) = warna text hijau.\n\
			(o) = warna text orange.\n\
			(w) = warna text putih.", "Input", "Batal");
		}
		case 1:
		{
			if(!IsValidDynamic3DTextLabel(pFactionLabel[playerid][id])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Label tersebut tidak ada atau belum digunakan!");

			new Float:xxpos[3];
			GetPlayerPos(playerid, xxpos[0], xxpos[1], xxpos[2]);
			Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, pFactionLabel[playerid][id], xxpos[0], xxpos[1], xxpos[2]+0.65);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah posisi label tersebut!");

			AccountData[playerid][pTempValue] = -1;
		}
		case 2:
		{
			if(DestroyDynamic3DTextLabel(pFactionLabel[playerid][id]))
				pFactionLabel[playerid][id] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

			ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah menghapus label tersebut!");

			AccountData[playerid][pTempValue] = -1;
		}
	}
	return 1;
}

Dialog:FactLabelEditText(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	new id = AccountData[playerid][pTempValue];
	if(id == -1) return 1;

	if(isnull(inputtext))
    {
        Dialog_Show(playerid, "FactLabelEditText", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Text Label", 
        "Error: Tag tidak bisa diisi kosong!\n\
        Mohon masukkan tulisan label yang ingin dibuat:\n\
        (n) = text akan berada di bawah/baris baru.\n\
        (r) = warna text merah.\n\
        (b) = warna text hitam.\n\
        (y) = warna text kuning.\n\
        (bl) = warna text biru.\n\
        (g) = warna text hijau.\n\
        (o) = warna text orange.\n\
        (w) = warna text putih.", "Input", "Batal");
        return 1;
    }

    if(strlen(inputtext) < 4)
    {
        Dialog_Show(playerid, "FactLabelEditText", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Text Label", 
        "Error: Tag terlalu singkat minimal 4 karakter!\n\
        Mohon masukkan tulisan label yang ingin dibuat:\n\
        (n) = text akan berada di bawah/baris baru.\n\
        (r) = warna text merah.\n\
        (b) = warna text hitam.\n\
        (y) = warna text kuning.\n\
        (bl) = warna text biru.\n\
        (g) = warna text hijau.\n\
        (o) = warna text orange.\n\
        (w) = warna text putih.", "Input", "Batal");
        return 1;
    }

    if(strfind(inputtext, "%", true) != -1 || strfind(inputtext, "#", true) != -1) 
    {
        Dialog_Show(playerid, "FactLabelEditText", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Edit Text Label", 
        "Error: Tidak dapat memasukkan simbol/tanda persen!\n\
        Mohon masukkan tulisan label yang ingin dibuat:\n\
        (n) = text akan berada di bawah/baris baru.\n\
        (r) = warna text merah.\n\
        (b) = warna text hitam.\n\
        (y) = warna text kuning.\n\
        (bl) = warna text biru.\n\
        (g) = warna text hijau.\n\
        (o) = warna text orange.\n\
        (w) = warna text putih.", "Input", "Batal");
        return 1;
    }

	strcopy(TempString[playerid], inputtext);

    ReplaceText(TempString[playerid], "(n)", "\n");
    ReplaceText(TempString[playerid], "(r)", "{FF0000}"); // red
    ReplaceText(TempString[playerid], "(b)", "{0E0101}"); // black
    ReplaceText(TempString[playerid], "(y)", "{FFFF00}"); // yellow
    ReplaceText(TempString[playerid], "(bl)", "{0000FF}"); // blue
    ReplaceText(TempString[playerid], "(g)", "{00FF00}"); // green
    ReplaceText(TempString[playerid], "(o)", "{FFA500}"); // orange
    ReplaceText(TempString[playerid], "(w)", "{FFFFFF}"); // white

	strcat(TempString[playerid], sprintf("\n%s (%d)", AccountData[playerid][pName], playerid));

	if(!IsValidDynamic3DTextLabel(pFactionLabel[playerid][id]))
	{
		new Float:xxpos[3];
		GetPlayerPos(playerid, xxpos[0], xxpos[1], xxpos[2]);
		pFactionLabel[playerid][id] = CreateDynamic3DTextLabel(TempString[playerid], Y_WHITE, xxpos[0], xxpos[1], xxpos[2]+0.65, 10.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), -1, 10.00, -1, 0);

		ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membuat label tersebut!");
	}
	else
	{
		UpdateDynamic3DTextLabelText(pFactionLabel[playerid][id], Y_WHITE, TempString[playerid]);

		ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengganti teks label tersebut!");
	}

	TempString[playerid][0] = EOS;
	return 1;
}

YCMD:vcolorlist(playerid, params[], help) 
{
    static color_list[3072];
    color_list[0] = EOS;

    for (new colorid; colorid != sizeof(g_VehicleColors); colorid++)
    {
        format(color_list, sizeof color_list, "%s{%06x}%03d%s", color_list, g_VehicleColors[colorid] >>> 8, colorid, !((colorid + 1) % 16) ? ("\n") : (" "));
    }

	Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "List Warna Kendaraan", color_list, "Tutup", "");
    return 1;
}

YCMD:fs(playerid, params[], help)
{
	if(!IsPlayerInRangeOfPoint(playerid, 3.0, 767.2671,-22.9374,1000.5859) && GetPlayerVirtualWorld(playerid) != 2001 && GetPlayerInterior(playerid) != 6)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di Cobra GYM");

	Dialog_Show(playerid, "FightStyle", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Fighting Styles", "Normal (default)\nBoxing\nKungfu\nKneehead\nGrabkick\nElbow", "Pilih", "Batal");
	return 1;
}
