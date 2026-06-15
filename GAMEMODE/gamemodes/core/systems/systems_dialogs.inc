Dialog:PlayerComma(playerid, response, listitem, inputtext[]) 
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
	AssignPlayerComma(playerid);
	SendClientMessage(playerid, -1, "[i] Anda telah menyetujui untuk spawn, artinya karakter anda dinyatakan koma.");
    SendClientMessage(playerid, -1, "[i] Dengan demikian senjata, seluruh barang di tas dan uang di saku akan hilang.");
	return 1;
}

Dialog:UnusedDialog(playerid, response, listitem, inputtext[])
{
	if(response == 0 || response == 1)
		return 1;
	return 1;
}

Dialog:FactionRestoSlicing(playerid, response, listitem, inputtext[]) 
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	switch(listitem)
	{
		case 0: //Kentang
		{
			if(Inventory_Count(playerid, "Kentang") < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki 2 Kentang!");

			Inventory_Remove(playerid, "Kentang", 2);
			Inventory_Add(playerid, "Kentang Potong", 19574, 10);

			ShowItemBox(playerid, "Kentang", "Removed 2x", 19638, 4);
			ShowItemBox(playerid, "Kentang Potong", "Received 10x", 19574, 5);
		}
		case 1: //Kubis
		{
			if(Inventory_Count(playerid, "Kubis") < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki 2 Kubis!");

			Inventory_Remove(playerid, "Kubis", 2);
			Inventory_Add(playerid, "Kubis Potong", 19576, 10);

			ShowItemBox(playerid, "Kubis", "Removed 2x", 19637, 4);
			ShowItemBox(playerid, "Kubis Potong", "Received 10x", 19576, 5);
		}
		case 2: //Bawang
		{
			if(Inventory_Count(playerid, "Bawang") < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki 2 Bawang!");
		
			Inventory_Remove(playerid, "Bawang", 2);
			Inventory_Add(playerid, "Bawang Potong", 19575, 10);

			ShowItemBox(playerid, "Bawang", "Removed 2x", 19636, 4);
			ShowItemBox(playerid, "Bawang Potong", "Received 10x", 19575, 5);
		}
		case 3: //Tomat
		{
			if(Inventory_Count(playerid, "Tomat") < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki 2 Tomat!");
		
			Inventory_Remove(playerid, "Tomat", 2);
			Inventory_Add(playerid, "Tomat Potong", 19577, 10);

			ShowItemBox(playerid, "Tomat", "Removed 2x", 19636, 4);
			ShowItemBox(playerid, "Tomat Potong", "Received 10x", 19577, 5);
		}
	}
	return 1;
}

Dialog:Blindfold(playerid, response, listitem, inputtext[]) 
{
	if(!response) return 1;
	if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada pemain terdekat!");

	new id = NearestUser[playerid][listitem];
	if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada pemain terdekat!");
	
	if(!IsPlayerConnected(id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(!IsPlayerNearPlayer(playerid, id, 3.2)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak dekat dengan anda!");
	
	if(AccountData[id][pBlindfolded]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sedang dikarungi. Gunakan '/unbfold' untuk melepas!");

	AccountData[id][pBlindfolded] = true;
	SetPlayerAttachedObject(id, 9, 2663, 2, 0.049999, -0.009999, -0.005999, -10.099994, -98.199989, -5.000000, 0.873000, 1.524000, 0.623999);
	HideRadarMapForPlayer(playerid);

	Inventory_Remove(playerid, "Karung Goni");
	ShowItemBox(playerid, "Karung Goni", "Removed 1x", 2663, 4);

	TextDrawShowForPlayer(id, BlindfoldTD);
	
	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menggunakan blindfold terhadap Pemain tersebut!");

	SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Gunakan "CMDEA"'/unbfold' "WHITE"untuk melepaskan karung goni.");

	SendClientMessageEx(id, 0xFF00FFAA, "[Server] Anda telah dikarungi oleh %s [%s] (ID: %d).", AccountData[playerid][pName], AccountData[playerid][pUCP], playerid);

	for(new x; x < 100; x++)
	{
		NearestUser[playerid][x] = INVALID_PLAYER_ID;
	}
	return 1;
}

Dialog:VerifPW(playerid, response, listitem, inputtext[]) 
{
	if(!response) return KickEx(playerid);

	static newpin;
	newpin = strval(inputtext);

	if(isnull(inputtext))
	{
		Kick(playerid);
		return 1;
	}

	if(!IsNumericEx(inputtext))
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Kode recovery hanya berupa angka!");
		
		static string[512];
		format(string, sizeof(string), "Selamat datang di Pahlawan Roleplay\nNama UCP: %s\n\
		Anda telah meminta layanan lupa password.\nKami telah mengirimkan anda kode recovery melalui DM discord anda.\n"YELLOW"(Mohon masukkan kode tersebut di bawah ini):", AccountData[playerid][pUCP]);
		Dialog_Show(playerid, "VerifPW", DIALOG_STYLE_PASSWORD, "{DA9100}Pahlawan Roleplay "WHITE"- Lupa Sandi", string, "Input", "Batal");
		return 1;
	}

	if(newpin != tempverify[playerid] && newpin != temprecovery[playerid])
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Kode recovery salah!");
		KickEx(playerid);
		return 1;
	}
	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasukkan kode recovery!");

	Dialog_Show(playerid, "RecPassword", DIALOG_STYLE_PASSWORD, "{DA9100}Pahlawan Roleplay "WHITE"- Ganti Sandi", "Masukkan password baru untuk menggantinya:", "Set", "Batal");
	return 1;
}

Dialog:RecPassword(playerid, response, listitem, inputtext[])
{
	if(!response) return KickEx(playerid);

	if(isnull(inputtext))
	{
		Kick(playerid);
		return 1;
	}

	static string[256];
	format(string, sizeof(string), ""WHITE"Selamat Datang di {DA9100}Pahlawan Roleplay!\n"WHITE"Nama UCP: "RED"%s\nERROR: "WHITE"Panjang password harus 7 hingga 32 karakter!\n"YELLOW"(Masukkan password baru untuk menggantinya):", GetName(playerid));

	if(strlen(inputtext) < 7)
		return Dialog_Show(playerid, "RecPassword", DIALOG_STYLE_PASSWORD, "{DA9100}Pahlawan Roleplay "WHITE"- Ganti Sandi", string, "Input", "Quit");

	if(strlen(inputtext) > 32)
		return Dialog_Show(playerid, "RecPassword", DIALOG_STYLE_PASSWORD, "{DA9100}Pahlawan Roleplay "WHITE"- Ganti Sandi", string, "Input", "Quit");

	if(!IsValidPassword(inputtext))
		return Dialog_Show(playerid, "RecPassword", DIALOG_STYLE_PASSWORD, "{DA9100}Pahlawan Roleplay "WHITE"- Ganti Sandi", sprintf(""WHITE"Selamat Datang di {DA9100}Pahlawan Roleplay!\n"WHITE"Nama UCP: "RED"%s\nERROR: "WHITE"Sandi hanya dapat mengandung A-Z, a-z, 0-9, _, [ ], ( )\n"YELLOW"(Mohon masukkan password untuk register):", GetName(playerid)), "Input", "Quit");

	bcrypt_hash(playerid, "OnPasswordRecChanged", inputtext, BCRYPT_COST);
	return 1;
}

Dialog:Register(playerid, response, listitem, inputtext[])
{
	if(!response)
		return Kick(playerid);

	if(isnull(inputtext))
	{
		Kick(playerid);
		return 1;
	}

	static string[256];
	format(string, sizeof(string), ""WHITE"Selamat Datang di {DA9100}Pahlawan Roleplay!\n"WHITE"Nama UCP: "RED"%s\nERROR: "WHITE"Panjang password harus 7 hingga 32 karakter!\n"YELLOW"(Mohon masukkan password untuk register):", GetName(playerid));

	if(strlen(inputtext) < 7)
		return Dialog_Show(playerid, "Register", DIALOG_STYLE_PASSWORD, "UCP - Register", string, "Input", "Quit");

	if(strlen(inputtext) > 32)
		return Dialog_Show(playerid, "Register", DIALOG_STYLE_PASSWORD, "UCP - Register", string, "Input", "Quit");

	if(!IsValidPassword(inputtext))
		return Dialog_Show(playerid, "Register", DIALOG_STYLE_PASSWORD, "UCP - Register", sprintf(""WHITE"Selamat Datang di {DA9100}Pahlawan Roleplay!\n"WHITE"Nama UCP: "RED"%s\nERROR: "WHITE"Sandi hanya dapat mengandung A-Z, a-z, 0-9, _, [ ], ( )\n"YELLOW"(Mohon masukkan password untuk register):", GetName(playerid)), "Input", "Quit");

	bcrypt_hash(playerid, "OnPasswordHashed", inputtext, BCRYPT_COST);
	return 1;
}

Dialog:Login(playerid, response, listitem, inputtext[])
{
	if (!response)
		return 1;
		
	if(isnull(inputtext))
	{
		SendClientMessage(playerid, Y_GREY, "ERROR: Anda harus memasukkan password untuk login!");
		return 1;
	}

	format(AccountData[playerid][pTempPassword], 64, "%s", inputtext);

	new len = strlen(inputtext);
    new mask[128];
    for (new i = 0; i < len; i++) {
        mask[i] = '-';
    }
    mask[len] = '\0';

	PlayerTextDrawSetString(playerid, LoginBoxPTD[playerid][1], mask);
	PlayerTextDrawShow(playerid, LoginBoxPTD[playerid][1]);
	/*new string[555];
	mysql_format(g_SQL, string, sizeof(string), "SELECT `Password` FROM `player_ucp` WHERE `UCP` = '%e' LIMIT 1", AccountData[playerid][pUCP]);
	mysql_pquery(g_SQL, string, "OnLoginPassCheck", "is", playerid, inputtext);*/
	return 1;
}

Dialog:Verification(playerid, response, listitem, inputtext[])
{
	if(!response) return KickEx(playerid);

	if(isnull(inputtext))
	{
		Kick(playerid);
		return 1;
	}

	if(!IsNumericEx(inputtext))
	{
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		SendClientMessage(playerid, Y_GREY, "ERROR: Masukkan kode verifikasi hanya berupa angka!");

		Dialog_Show(playerid, "Verification", DIALOG_STYLE_PASSWORD, ""RED"UCP - Verification Required", ""WHITE"Masukkan 6 digit kode dari Discord Anda: "PAHLAWAN"(input below)", "Continue", "Cancel");
		return 1;
	}

	tempverify[playerid] = floatround(strval(inputtext));

	new charBuffer[2]; // Buffer untuk 1 karakter + null terminator
	for (new i = 0; i < 6; i++) {
		charBuffer[0] = inputtext[i]; // Ambil karakter
		charBuffer[1] = '\0'; // Tambahkan null terminator
		PlayerTextDrawSetString(playerid, VerifyCodePTD[playerid][6 + i], charBuffer);
		PlayerTextDrawShow(playerid, VerifyCodePTD[playerid][6 + i]);
	}

	/*if(newpin == tempverify[playerid])
	{
		static string[512];
		mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `whitelists` WHERE `ucp`='%e' LIMIT 1", AccountData[playerid][pUCP]);
		mysql_query(g_SQL, string);
		static rows;
		rows = cache_num_rows();
		
		if(rows) 
		{
			mysql_format(g_SQL, string, sizeof(string), "UPDATE `whitelists` SET `verify`=-1 WHERE `ucp`='%e'", AccountData[playerid][pUCP]);
			mysql_pquery(g_SQL, string);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyelesaikan verifikasi!");

			format(string, sizeof(string), ""WHITE"Selamat datang di {DA9100}Pahlawan Roleplay\n"WHITE"UCP ini belum terdaftar!\nNama UCP: "RED"%s\n"YELLOW"(Silakan masukkan kata sandi untuk mendaftar):", AccountData[playerid][pUCP]);
			Dialog_Show(playerid, "Register", DIALOG_STYLE_PASSWORD, "UCP - Register", string, "Input", "Quit");
		}
		else
		{
			KickEx(playerid);
		}
	}
	else
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Kode verifikasi salah!");
		KickEx(playerid);
	}*/
	return 1;
}

Dialog:VerificationLogin(playerid, response, listitem, inputtext[])
{
	if(!response) return KickEx(playerid);

	static newpin;
	newpin = floatround(strval(inputtext));

	if(isnull(inputtext))
	{
		Kick(playerid);
		return 1;
	}

	if(!IsNumericEx(inputtext))
	{
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		
		static string[512];
		format(string, sizeof(string), ""RED"<!> Masukkan kode verifikasi hanya berupa angka!\n\n"WHITE"Selamat datang di {DA9100}Pahlawan Roleplay\n"WHITE"UCP ini telah terdaftar namun belum melakukan verifikasi!\nNama UCP: "DARK_SEA_GREEN_2"%s\n"YELLOW"(Silakan masukkan kode verifikasi):", AccountData[playerid][pUCP]);
		Dialog_Show(playerid, "VerificationLogin", DIALOG_STYLE_PASSWORD, "{DA9100}Pahlawan Roleplay "WHITE"- Unregistered Account", string, "Verify", "Batal");
		return 1;
	}

	if(newpin == tempverify[playerid])
	{
		static string[512];
		mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `whitelists` WHERE `ucp`='%e' LIMIT 1", AccountData[playerid][pUCP]);
		mysql_query(g_SQL, string);
		static rows;
		rows = cache_num_rows();
		
		if(rows)
		{
			mysql_format(g_SQL, string, sizeof(string), "UPDATE `whitelists` SET `verify`=-1 WHERE `ucp`='%e'", AccountData[playerid][pUCP]);
			mysql_pquery(g_SQL, string);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyelesaikan verifikasi!");

			format(string, sizeof(string), ""WHITE"Selamat datang di {DA9100}Pahlawan Roleplay\n"WHITE"UCP ini telah terdaftar!\nNama UCP: "DARK_SEA_GREEN_2"%s\n"YELLOW"(Silakan masukkan kata sandi untuk login):", AccountData[playerid][pUCP]);
			Dialog_Show(playerid, "Login", DIALOG_STYLE_PASSWORD, "UCP - Login", string, "Input", "Quit");
		}
		else
		{
			KickEx(playerid);
		}
	}
	else
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Kode verifikasi salah!");
		KickEx(playerid);
	}
	return 1;
}

Dialog:CharacterList(playerid, response, listitem, inputtext[])
{
	static string[315];
	if(!response) return Kick(playerid);
	if(listitem < 0 || listitem > 2) 
	{
		ShowCharacterList(playerid);
		ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih karakter apapun!");
		return 1;
	}

	if(isnull(PlayerChar[playerid][listitem]))
	{
		Dialog_Show(playerid, "MakeNewChar", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Pembuatan Karakter", ""WHITE"Selamat datang di {DA9100}Pahlawan Roleplay.\n\
		"WHITE"Sebelum bermain, Anda harus membuat karakter terlebih dahulu.\n\
		"WHITE"Gunakan format "RED"NamaDepan_NamaBelakang"WHITE" untuk nama karakter Anda.\n\n\
		"WHITE"Contoh: "YELLOW"John_Doe, Kenji_Tanaka, Budi_Santoso", "Input", "Kembali");
		return 1;
	}
	strcopy(AccountData[playerid][pName], PlayerChar[playerid][listitem]);

	mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `player_bans` WHERE (name = '%e') OR (longip & %i = %i) LIMIT 1", AccountData[playerid][pName], BAN_MASK, (Ban_GetLongIP(AccountData[playerid][pIP]) & BAN_MASK));
	mysql_pquery(g_SQL, string, "CheckBan", "i", playerid);
	return 1;
}

Dialog:MakeNewChar(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowCharacterList(playerid);

	if(strlen(inputtext) < 1 || strlen(inputtext) > 24)
		return Dialog_Show(playerid, "MakeNewChar", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Pembuatan Karakter", ""RED"Error: "WHITE"Nama karakter harus berisi 1 - 24 huruf!\nContoh: "YELLOW"John_Doe, Kenji_Tanaka, Budi_Santoso\n"YELLOW"(Mohon masukkan nama yang benar):", "Input", "Kembali");

	if(!IsRoleplayName(inputtext))
		return Dialog_Show(playerid, "MakeNewChar", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Pembuatan Karakter", ""RED"Error: "WHITE"Format nama karakter salah!\nContoh: "YELLOW"John_Doe, Kenji_Tanaka, Budi_Santoso\n"YELLOW"(Mohon masukkan nama yang benar):", "Input", "Kembali");

	static string[178];
	mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `player_characters` WHERE `Char_Name` = '%e'", inputtext);
	mysql_pquery(g_SQL, string, "InsertPlayerName", "is", playerid, inputtext);

	strcopy(AccountData[playerid][pUCP], GetName(playerid));
	return 1;
}

Dialog:NewCharAge(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		static
			iDay,
			iMonth,
			iYear,
			day,
			month,
			year;
			
		getdate(year, month, day);

		static const
				arrMonthDays[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

		if(sscanf(inputtext, "p</>ddd", iDay, iMonth, iYear)) 
		{
			PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0); Dialog_Show(playerid, "NewCharAge", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Birthday", "Error: Format salah!\nPlease insert the birthday with following format hh/bb/tttt cth: (25/08/2001)", "Input", "");
		}
		else if(iYear < 1900 || iYear > year) 
		{
			PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0); Dialog_Show(playerid, "NewCharAge", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Birthday", "Error: Invalid input tahun kelahiran!\nPlease insert the birthday with following format hh/bb/tttt cth: (25/08/2001)", "Input", "");
		}
		else if(iMonth < 1 || iMonth > 12) 
		{
			PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0); Dialog_Show(playerid, "NewCharAge", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Birthday", "Error: Invalid input bulan kelahiran!\nPlease insert the birthday with following format hh/bb/tttt cth: (25/08/2001)", "Input", "");
		}
		else if(iDay < 1 || iDay > arrMonthDays[iMonth - 1]) 
		{
			PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0); Dialog_Show(playerid, "NewCharAge", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Birthday", "Error: Invalid input tanggal kelahiran!\nPlease insert the birthday with following format hh/bb/tttt cth: (25/08/2001)", "Input", "");
		}
		else 
		{
			AccountData[playerid][pAge] = iYear;

			static originstring[3528+1];
			for(new x = 0; x < sizeof(_g_originName);x++)
			{
				format(originstring, sizeof(originstring), "%s%s\n", originstring, _g_originName[x]);
			}
			Dialog_Show(playerid, "NewCharOrigin", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Origin", originstring, "Pilih", "");
		}
	}
	else
	{
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		Dialog_Show(playerid, "NewCharAge", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Birthday", 
		"Error: Tidak dapat dibatalkan!\n\
		Mohon masukkan tanggal lahir karakter!\n\
		Perhatian: Format berupa hh/bb/tttt (cth: 25/08/2001).", "Input", "Batal");
	}
	return 1;
}

Dialog:NewCharOrigin(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		static originstring[3528+1];
		for(new x; x < sizeof(_g_originName); x++)
		{
			format(originstring, sizeof(originstring), "%s%s\n", originstring, _g_originName[x]);
		}
		return Dialog_Show(playerid, "NewCharOrigin", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Origin", originstring, "Pilih", "");
	}

	if(listitem == -1 || listitem > sizeof(_g_originName) - 1)
	{
		strcopy(AccountData[playerid][pOrigin], _g_originName[0]);
	}
	else
	{
		strcopy(AccountData[playerid][pOrigin], _g_originName[listitem]);
	}

	Dialog_Show(playerid, "NewCharHeight", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Body Height (cm)", "Please insert your body height (cm)!", "Input", "");
	return 1;
}

Dialog:NewCharHeight(playerid, response, listitem, inputtext[])
{
	if(!response) 
	{
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		Dialog_Show(playerid, "NewCharHeight", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Body Height (cm)", 
		"Error: Tidak dapat dibatalkan!\n\
		Mohon masukkan Body Height (cm) karakter!\n\
		Perhatian: Format hanya berupa angka satuan cm (cth: 169).", "Input", "");
		return 1;
	}

	if(isnull(inputtext))
	{
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		Dialog_Show(playerid, "NewCharHeight", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Body Height (cm)", "Error: Tidak dapat dikosongkan!", "Input", "");
		return 1;
	}
	if(!IsNumericEx(inputtext))
	{
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		Dialog_Show(playerid, "NewCharHeight", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Body Height (cm)", "Error: Masukkan hanya angka!", "Input", "");
		return 1;
	}
	if(strval(inputtext) > 200)
	{
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		Dialog_Show(playerid, "NewCharHeight", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Body Height (cm)", "Error: Tidak bisa lebih dari 200 cm!", "Input", "");
		return 1;
	}
	if(strval(inputtext) < 140)
	{
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		Dialog_Show(playerid, "NewCharHeight", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Body Height (cm)", "Error: Tidak bisa di bawah 140 cm!", "Input", "");
		return 1;
	}
	AccountData[playerid][pBodyHeight] = strval(inputtext);
	Dialog_Show(playerid, "NewCharWeight", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Body Weight (kg)", "Masukkan berat badan karakter (kg)!", "Input", "");
	return 1;
}

Dialog:NewCharWeight(playerid, response, listitem, inputtext[])
{
	if(!response) 
	{
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		Dialog_Show(playerid, "NewCharWeight", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Body Weight (kg)", 
		"Error: Tidak dapat dibatalkan!\n\
		Mohon masukkan Body Weight (kg) karakter!\n\
		Perhatian: Format hanya berupa angka satuan kg (cth: 75).", "Input", "Batal");
		return 1;
	}

	if(isnull(inputtext))
	{
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		Dialog_Show(playerid, "NewCharWeight", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Body Weight (kg)", "Error: Tidak dapat dikosongkan!", "Input", "");
		return 1;
	}
	if(!IsNumericEx(inputtext))
	{
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		Dialog_Show(playerid, "NewCharWeight", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Body Weight (kg)", "Error: Masukkan hanya angka!", "Input", "");
		return 1;
	}
	if(strval(inputtext) > 100)
	{
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		Dialog_Show(playerid, "NewCharWeight", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Body Weight (kg)", "Error: Tidak bisa lebih dari 100 kg!", "Input", "");
		return 1;
	}
	if(strval(inputtext) < 40)
	{
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		Dialog_Show(playerid, "NewCharWeight", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Body Weight (kg)", "Error: Tidak bisa di bawah 40 kg!", "Input", "");
		return 1;
	}
	AccountData[playerid][pBodyWeight] = strval(inputtext);
	Dialog_Show(playerid, "NewCharGender", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Jenis Kelamin", "Laki-Laki\n"GRAY"Perempuan", "Pilih", "");
	return 1;
}

Dialog:SpawnSelectPD(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		ShowPlayerSpawnSelection(playerid);
		return 1;
	}

	switch(listitem)
	{
		case 0: //SAMSAT
		{
			AccountData[playerid][pInDoor] = -1;
			AccountData[playerid][pInHouse] = -1;
			AccountData[playerid][pInBiz] = -1;
			AccountData[playerid][pInRusun] = -1;
			AVC_PConnected[playerid] = true;

			SetPlayerVirtualWorldEx(playerid, 0);
			SetPlayerInteriorEx(playerid, 0);
			AccountData[playerid][pPos][0] = 1015.6490;
			AccountData[playerid][pPos][1] = 2369.1287;
			AccountData[playerid][pPos][2] = 10.8203;
			AccountData[playerid][pPos][3] = 36.9737;
			SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pSkin], 1015.6490,2369.1287,10.8203,36.9737, 0, 0, 0, 0, 0, 0);
			TogglePlayerSpectating(playerid, false);
			SetCameraBehindPlayer(playerid);
			Anticheat[playerid][acImmunity] = gettime() + 5;
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			GameTextForPlayer(playerid, "Memuat Object...", 6500, 3);
		}
		case 1: //coming soon
		{
			AccountData[playerid][pInDoor] = -1;
			AccountData[playerid][pInHouse] = -1;
			AccountData[playerid][pInBiz] = -1;
			AccountData[playerid][pInRusun] = -1;
			AVC_PConnected[playerid] = true;

			SetPlayerVirtualWorldEx(playerid, 0);
			SetPlayerInteriorEx(playerid, 0);
			AccountData[playerid][pPos][0] = 1015.6490;
			AccountData[playerid][pPos][1] = 2369.1287;
			AccountData[playerid][pPos][2] = 10.8203;
			AccountData[playerid][pPos][3] = 36.9737;
			SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pSkin], 1015.6490,2369.1287,10.8203,36.9737, 0, 0, 0, 0, 0, 0);
			TogglePlayerSpectating(playerid, false);
			SetCameraBehindPlayer(playerid);
			Anticheat[playerid][acImmunity] = gettime() + 5;
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			GameTextForPlayer(playerid, "Memuat Object...", 6500, 3);
		}
	}
	return 1;
}

Dialog:SpawnSelection(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		AccountData[playerid][pInDoor] = 44;
		AccountData[playerid][pInHouse] = -1;
		AccountData[playerid][pInBiz] = -1;
		AccountData[playerid][pInRusun] = -1;
		AVC_PConnected[playerid] = true;

		SetPlayerVirtualWorldEx(playerid, 60);
		SetPlayerInteriorEx(playerid, 0);
		
		new rand = random(sizeof(AirportLSSpawn));
		AccountData[playerid][pPos][0] = AirportLSSpawn[rand][0];
		AccountData[playerid][pPos][1] = AirportLSSpawn[rand][1];
		AccountData[playerid][pPos][2] = AirportLSSpawn[rand][2];
		AccountData[playerid][pPos][3] = AirportLSSpawn[rand][3];
		SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pSkin], AirportLSSpawn[rand][0], AirportLSSpawn[rand][1], AirportLSSpawn[rand][2], AirportLSSpawn[rand][3], 0, 0, 0, 0, 0, 0);
		TogglePlayerSpectating(playerid, false);
		Anticheat[playerid][acImmunity] = gettime() + 5;
		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		GameTextForPlayer(playerid, "Memuat Objek...", 6500, 3);
		return 1;
	}

	switch(listitem)
	{
		case 0: //bandara
		{
			AccountData[playerid][pInDoor] = 44;
			AccountData[playerid][pInHouse] = -1;
			AccountData[playerid][pInBiz] = -1;
			AccountData[playerid][pInRusun] = -1;
			AVC_PConnected[playerid] = true;

			SetPlayerVirtualWorldEx(playerid, 60);
			SetPlayerInteriorEx(playerid, 0);
			
			new rand = random(sizeof(AirportLSSpawn));
			AccountData[playerid][pPos][0] = AirportLSSpawn[rand][0];
			AccountData[playerid][pPos][1] = AirportLSSpawn[rand][1];
			AccountData[playerid][pPos][2] = AirportLSSpawn[rand][2];
			AccountData[playerid][pPos][3] = AirportLSSpawn[rand][3];
			SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pSkin], AirportLSSpawn[rand][0], AirportLSSpawn[rand][1], AirportLSSpawn[rand][2], AirportLSSpawn[rand][3], 0, 0, 0, 0, 0, 0);
			TogglePlayerSpectating(playerid, false);
			SetCameraBehindPlayer(playerid);
			Anticheat[playerid][acImmunity] = gettime() + 5;
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			GameTextForPlayer(playerid, "Memuat Objek...", 6500, 3);
		}
		case 1: //rusun
		{
			new rsid = Player_ReturnRusunID(playerid);
			if(rsid == -1) 
			{
				ShowPlayerSpawnSelection(playerid);
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum menyewa rusun manapun!");
			}

			AccountData[playerid][pInDoor] = -1;
			AccountData[playerid][pInHouse] = -1;
			AccountData[playerid][pInBiz] = -1;
			AccountData[playerid][pInRusun] = rsid;
			AVC_PConnected[playerid] = true;

			SetPlayerVirtualWorldEx(playerid, rsid);
			SetPlayerInteriorEx(playerid, 1);
			AccountData[playerid][pPos][0] = 244.2521;
			AccountData[playerid][pPos][1] = 304.9150;
			AccountData[playerid][pPos][2] = 999.1484;
			AccountData[playerid][pPos][3] = 268.6741;
			SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pSkin], 244.2521, 304.9150, 999.1484, 268.6741, 0, 0, 0, 0, 0, 0);
			TogglePlayerSpectating(playerid, false);
			SetCameraBehindPlayer(playerid);
			Anticheat[playerid][acImmunity] = gettime() + 5;
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			GameTextForPlayer(playerid, "Memuat Objek...", 6500, 3);
		}
		case 2: //rumah
		{
			new hid = Player_ReturnHouseID(playerid);
			if(hid == -1)
			{
				ShowPlayerSpawnSelection(playerid);
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki rumah!");
			}

			AccountData[playerid][pInDoor] = -1;
			AccountData[playerid][pInHouse] = hid;
			AccountData[playerid][pInBiz] = -1;
			AccountData[playerid][pInRusun] = -1;
			AVC_PConnected[playerid] = true;

			SetPlayerVirtualWorldEx(playerid, HouseData[hid][hIntWorld]);
			SetPlayerInteriorEx(playerid, HouseData[hid][hIntInterior]);
			AccountData[playerid][pPos][0] = HouseData[hid][hIntPos][0];
			AccountData[playerid][pPos][1] = HouseData[hid][hIntPos][1];
			AccountData[playerid][pPos][2] = HouseData[hid][hIntPos][2];
			AccountData[playerid][pPos][3] = HouseData[hid][hIntPos][3];
			SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pSkin], HouseData[hid][hIntPos][0], HouseData[hid][hIntPos][1], HouseData[hid][hIntPos][2], HouseData[hid][hIntPos][3], 0, 0, 0, 0, 0, 0);
			TogglePlayerSpectating(playerid, false);
			SetCameraBehindPlayer(playerid);
			Anticheat[playerid][acImmunity] = gettime() + 5;
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			GameTextForPlayer(playerid, "Memuat Objek...", 6500, 3);
		}
		case 3: //faction hq
		{
			if(AccountData[playerid][pFaction] == FACTION_NONE)
			{
				ShowPlayerSpawnSelection(playerid);
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari any faction!");
			}

			switch(AccountData[playerid][pFaction])
			{
				case 1: //LSPD
				{
					Dialog_Show(playerid, "SpawnSelectPD", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Select Spawn", 
					"SAMSAT Pahlawan Roleplay\n\
					Coming Soon", "Pilih", "Kembali");
				}
				case 2: //EMS
				{
					AccountData[playerid][pInDoor] = -1;
					AccountData[playerid][pInHouse] = -1;
					AccountData[playerid][pInBiz] = -1;
					AccountData[playerid][pInRusun] = -1;
					AVC_PConnected[playerid] = true;

					SetPlayerVirtualWorldEx(playerid, 0);
					SetPlayerInteriorEx(playerid, 0);
					AccountData[playerid][pPos][0] = 1778.3971;
					AccountData[playerid][pPos][1] = -1185.6299;
					AccountData[playerid][pPos][2] = 23.8576;
					AccountData[playerid][pPos][3] = 31.6753;
					SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pSkin], 1778.3971,-1185.6299,23.8576,31.6753, 0, 0, 0, 0, 0, 0);
					TogglePlayerSpectating(playerid, false);
					SetCameraBehindPlayer(playerid);
					Anticheat[playerid][acImmunity] = gettime() + 5;
					PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					GameTextForPlayer(playerid, "Memuat Objek...", 6500, 3);
				}
				case 3: //Putri Deli
				{
					AccountData[playerid][pInDoor] = -1;
					AccountData[playerid][pInHouse] = -1;
					AccountData[playerid][pInBiz] = -1;
					AccountData[playerid][pInRusun] = -1;
					AVC_PConnected[playerid] = true;

					SetPlayerVirtualWorldEx(playerid, 0);
					SetPlayerInteriorEx(playerid, 0);
					AccountData[playerid][pPos][0] = 651.5056;
					AccountData[playerid][pPos][1] = -1828.7012;
					AccountData[playerid][pPos][2] = 5.6535;
					AccountData[playerid][pPos][3] = 144.0539;
					SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pSkin], 651.5056,-1828.7012,5.6535,144.0539, 0, 0, 0, 0, 0, 0);
					TogglePlayerSpectating(playerid, false);
					SetCameraBehindPlayer(playerid);
					Anticheat[playerid][acImmunity] = gettime() + 5;
					PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					GameTextForPlayer(playerid, "Memuat Objek...", 6500, 3);
				}
				case 4: //SAGOV
				{
					AccountData[playerid][pInDoor] = -1;
					AccountData[playerid][pInHouse] = -1;
					AccountData[playerid][pInBiz] = -1;
					AccountData[playerid][pInRusun] = -1;
					AVC_PConnected[playerid] = true;

					SetPlayerVirtualWorldEx(playerid, 0);
					SetPlayerInteriorEx(playerid, 0);
					AccountData[playerid][pPos][0] = 1254.9034;
					AccountData[playerid][pPos][1] = -2048.0667;
					AccountData[playerid][pPos][2] = 59.7613;
					AccountData[playerid][pPos][3] = 85.3792;
					SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pSkin], 1254.9034,-2048.0667,59.7613,85.3792, 0, 0, 0, 0, 0, 0);
					TogglePlayerSpectating(playerid, false);
					SetCameraBehindPlayer(playerid);
					Anticheat[playerid][acImmunity] = gettime() + 5;
					PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					GameTextForPlayer(playerid, "Memuat Objek...", 6500, 3);
				}
				case 5: //bennys
				{
					AccountData[playerid][pInDoor] = -1;
					AccountData[playerid][pInHouse] = -1;
					AccountData[playerid][pInBiz] = -1;
					AccountData[playerid][pInRusun] = -1;
					AVC_PConnected[playerid] = true;

					SetPlayerVirtualWorldEx(playerid, 0);
					SetPlayerInteriorEx(playerid, 0);
					AccountData[playerid][pPos][0] = 1366.8295;
					AccountData[playerid][pPos][1] = 749.0135;
					AccountData[playerid][pPos][2] = 10.8203;
					AccountData[playerid][pPos][3] = 89.5632;
					SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pSkin], 1366.8295,749.0135,10.8203,89.5632, 0, 0, 0, 0, 0, 0);
					TogglePlayerSpectating(playerid, false);
					SetCameraBehindPlayer(playerid);
					Anticheat[playerid][acImmunity] = gettime() + 5;
					PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					GameTextForPlayer(playerid, "Memuat Objek...", 6500, 3);
				}
				case 6: //Uber
				{
					AccountData[playerid][pInDoor] = -1;
					AccountData[playerid][pInHouse] = -1;
					AccountData[playerid][pInBiz] = -1;
					AccountData[playerid][pInRusun] = -1;
					AVC_PConnected[playerid] = true;

					SetPlayerVirtualWorldEx(playerid, 0);
					SetPlayerInteriorEx(playerid, 0);
					AccountData[playerid][pPos][0] = -1972.3809;
					AccountData[playerid][pPos][1] = -928.3663;
					AccountData[playerid][pPos][2] = 32.2266;
					AccountData[playerid][pPos][3] = 109.9067;
					SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pSkin], -1972.3809,-928.3663,32.2266,109.9067, 0, 0, 0, 0, 0, 0);
					TogglePlayerSpectating(playerid, false);
					SetCameraBehindPlayer(playerid);
					Anticheat[playerid][acImmunity] = gettime() + 5;
					PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					GameTextForPlayer(playerid, "Memuat Objek...", 6500, 3);
				}
				case 7: //Dinarbucks
				{
					AccountData[playerid][pInDoor] = -1;
					AccountData[playerid][pInHouse] = -1;
					AccountData[playerid][pInBiz] = -1;
					AccountData[playerid][pInRusun] = -1;
					AVC_PConnected[playerid] = true;

					SetPlayerVirtualWorldEx(playerid, 0);
					SetPlayerInteriorEx(playerid, 0);
					AccountData[playerid][pPos][0] = 1024.3879;
					AccountData[playerid][pPos][1] = -1314.6719;
					AccountData[playerid][pPos][2] = 13.5469;
					AccountData[playerid][pPos][3] = 210.0105;
					SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pSkin], 1024.3879,-1314.6719,13.5469,210.0105, 0, 0, 0, 0, 0, 0);
					TogglePlayerSpectating(playerid, false);
					SetCameraBehindPlayer(playerid);
					Anticheat[playerid][acImmunity] = gettime() + 5;
					PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					GameTextForPlayer(playerid, "Memuat Objek...", 6500, 3);
				}
				case 8: //fox 11
				{
					AccountData[playerid][pInDoor] = -1;
					AccountData[playerid][pInHouse] = -1;
					AccountData[playerid][pInBiz] = -1;
					AccountData[playerid][pInRusun] = -1;
					AVC_PConnected[playerid] = true;

					SetPlayerVirtualWorldEx(playerid, 0);
					SetPlayerInteriorEx(playerid, 0);
					AccountData[playerid][pPos][0] = 621.2632;
					AccountData[playerid][pPos][1] = -1360.1761;
					AccountData[playerid][pPos][2] = 13.5888;
					AccountData[playerid][pPos][3] = 287.0075;
					SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pSkin], 621.2632,-1360.1761,13.5888,287.0075, 0, 0, 0, 0, 0, 0);
					TogglePlayerSpectating(playerid, false);
					SetCameraBehindPlayer(playerid);
					Anticheat[playerid][acImmunity] = gettime() + 5;
					PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					GameTextForPlayer(playerid, "Memuat Objek...", 6500, 3);
				}
				case 9: //automax
				{
					AccountData[playerid][pInDoor] = -1;
					AccountData[playerid][pInHouse] = -1;
					AccountData[playerid][pInBiz] = -1;
					AccountData[playerid][pInRusun] = -1;
					AVC_PConnected[playerid] = true;

					SetPlayerVirtualWorldEx(playerid, 0);
					SetPlayerInteriorEx(playerid, 0);
					AccountData[playerid][pPos][0] = -1802.9841;
					AccountData[playerid][pPos][1] = 169.7179;
					AccountData[playerid][pPos][2] = 15.1094;
					AccountData[playerid][pPos][3] = 119.9230;
					SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pSkin], -1802.9841,169.7179,15.1094,119.9230, 0, 0, 0, 0, 0, 0);
					TogglePlayerSpectating(playerid, false);
					SetCameraBehindPlayer(playerid);
					Anticheat[playerid][acImmunity] = gettime() + 5;
					PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					GameTextForPlayer(playerid, "Memuat Objek...", 6500, 3);
				}
				case 10: //handover
				{
					AccountData[playerid][pInDoor] = -1;
					AccountData[playerid][pInHouse] = -1;
					AccountData[playerid][pInBiz] = -1;
					AccountData[playerid][pInRusun] = -1;
					AVC_PConnected[playerid] = true;

					SetPlayerVirtualWorldEx(playerid, 0);
					SetPlayerInteriorEx(playerid, 0);
					AccountData[playerid][pPos][0] = 216.1168;
					AccountData[playerid][pPos][1] = -303.3412;
					AccountData[playerid][pPos][2] = 1.5781;
					AccountData[playerid][pPos][3] = 8.1365;
					SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pSkin], 216.1168,-303.3412,1.5781,8.1365, 0, 0, 0, 0, 0, 0);
					TogglePlayerSpectating(playerid, false);
					SetCameraBehindPlayer(playerid);
					Anticheat[playerid][acImmunity] = gettime() + 5;
					PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					GameTextForPlayer(playerid, "Memuat Objek...", 6500, 3);
				}
				case 11: //+arivena
				{
					AccountData[playerid][pInDoor] = -1;
					AccountData[playerid][pInHouse] = -1;
					AccountData[playerid][pInBiz] = -1;
					AccountData[playerid][pInRusun] = -1;
					AVC_PConnected[playerid] = true;

					SetPlayerVirtualWorldEx(playerid, 0);
					SetPlayerInteriorEx(playerid, 0);
					AccountData[playerid][pPos][0] = -356.6686;
					AccountData[playerid][pPos][1] = 1381.3325;
					AccountData[playerid][pPos][2] = 57.1206;
					AccountData[playerid][pPos][3] = 220.5421;
					SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pSkin], -356.6686,1381.3325,57.1206,220.5421, 0, 0, 0, 0, 0, 0);
					TogglePlayerSpectating(playerid, false);
					SetCameraBehindPlayer(playerid);
					Anticheat[playerid][acImmunity] = gettime() + 5;
					PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					GameTextForPlayer(playerid, "Memuat Objek...", 6500, 3);
				}
				case 12: //texas chicken
				{
					AccountData[playerid][pInDoor] = -1;
					AccountData[playerid][pInHouse] = -1;
					AccountData[playerid][pInBiz] = -1;
					AccountData[playerid][pInRusun] = -1;
					AVC_PConnected[playerid] = true;

					SetPlayerVirtualWorldEx(playerid, 0);
					SetPlayerInteriorEx(playerid, 0);
					AccountData[playerid][pPos][0] = 2687.5742;
					AccountData[playerid][pPos][1] = 718.6926;
					AccountData[playerid][pPos][2] = 10.6719;
					AccountData[playerid][pPos][3] = 220.5421;
					SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pSkin], 2687.5742,718.6926,10.6719,220.5421, 0, 0, 0, 0, 0, 0);
					TogglePlayerSpectating(playerid, false);
					SetCameraBehindPlayer(playerid);
					Anticheat[playerid][acImmunity] = gettime() + 5;
					PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					GameTextForPlayer(playerid, "Memuat Objek...", 6500, 3);
				}
			}
		}
		case 4:
		{
			AVC_PConnected[playerid] = true;

			SetPlayerVirtualWorldEx(playerid, AccountData[playerid][pWorld]);
			SetPlayerInteriorEx(playerid, AccountData[playerid][pInterior]);
			SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pSkin], AccountData[playerid][pPos][0], AccountData[playerid][pPos][1], AccountData[playerid][pPos][2], 0.0, 0, 0, 0, 0, 0, 0);
			TogglePlayerSpectating(playerid, false);
			SetCameraBehindPlayer(playerid);
			Anticheat[playerid][acImmunity] = gettime() + 5;
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			GameTextForPlayer(playerid, "Memuat Objek...", 6500, 3);
		}
	}
	return 1;
}

Dialog:SelectionRegSpawn(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		AccountData[playerid][pInDoor] = 44;
		AccountData[playerid][pInHouse] = -1;
		AccountData[playerid][pInBiz] = -1;
		AccountData[playerid][pInRusun] = -1;
		AVC_PConnected[playerid] = true;
		AccountData[playerid][IsLoggedIn] = true;

		SetPlayerVirtualWorldEx(playerid, 60);
		SetPlayerInteriorEx(playerid, 0);

		new rand = random(sizeof(AirportLSSpawn));
		AccountData[playerid][pPos][0] = AirportLSSpawn[rand][0];
		AccountData[playerid][pPos][1] = AirportLSSpawn[rand][1];
		AccountData[playerid][pPos][2] = AirportLSSpawn[rand][2];
		AccountData[playerid][pPos][3] = AirportLSSpawn[rand][3];
		SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pSkin], AirportLSSpawn[rand][0], AirportLSSpawn[rand][1], AirportLSSpawn[rand][2], AirportLSSpawn[rand][3], 0, 0, 0, 0, 0, 0);
		TogglePlayerSpectating(playerid, false);
		Anticheat[playerid][acImmunity] = gettime() + 5;
		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		GameTextForPlayer(playerid, "Memuat Objek...", 6500, 3);
		return 1;
	}

	switch(listitem)
	{
		case 0: //airport
		{
			AccountData[playerid][pInDoor] = 44;
			AccountData[playerid][pInHouse] = -1;
			AccountData[playerid][pInBiz] = -1;
			AccountData[playerid][pInRusun] = -1;
			AVC_PConnected[playerid] = true;
			AccountData[playerid][IsLoggedIn] = true;

			SetPlayerVirtualWorldEx(playerid, 60);
			SetPlayerInteriorEx(playerid, 0);
			
			new rand = random(sizeof(AirportLSSpawn));
			AccountData[playerid][pPos][0] = AirportLSSpawn[rand][0];
			AccountData[playerid][pPos][1] = AirportLSSpawn[rand][1];
			AccountData[playerid][pPos][2] = AirportLSSpawn[rand][2];
			AccountData[playerid][pPos][3] = AirportLSSpawn[rand][3];
			SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pSkin], AirportLSSpawn[rand][0], AirportLSSpawn[rand][1], AirportLSSpawn[rand][2], AirportLSSpawn[rand][3], 0, 0, 0, 0, 0, 0);
			TogglePlayerSpectating(playerid, false);
			SetCameraBehindPlayer(playerid);
			Anticheat[playerid][acImmunity] = gettime() + 5;
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			GameTextForPlayer(playerid, "Memuat Objek...", 6500, 3);
		}
	}
	return 1;
}

Dialog:NewCharGender(playerid, response, listitem, inputtext[])
{
	if(!response)
		return Dialog_Show(playerid, "NewCharGender", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Jenis Kelamin", "Laki-Laki\n"GRAY"Perempuan", "Pilih", "");

	switch(listitem)
	{
		case 0:
		{
			static randmodel;
			randmodel = __g_RandomSkinMale[random(sizeof(__g_RandomSkinMale))];
			AccountData[playerid][pGender] = 1;
			AccountData[playerid][pSkin] = randmodel;
			SetPlayerHealthEx(playerid, 100.0);
			SetPlayerArmourEx(playerid, 0.0);
			SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Pembuatan karakter berhasil dilakukan!");

			SetPlayerCameraPos(playerid, 642.535644, -2237.217285, 143.806137);
			SetPlayerCameraLookAt(playerid, 523.445556, -1929.099853, 0.045935);
			InterpolateCameraPos(playerid,642.535644, -2237.217285, 143.806137, 523.445556, -1929.099853, 143.806137,50000,CAMERA_MOVE);

			Dialog_Show(playerid, "SelectionRegSpawn", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Pilih Lokasi Spawn", 
			"Titik spawn\tDetail\tLokasi\n\
			Los Santos International Airport\tAnda spawn di bandara\tLos Santos (LS)", "Pilih", "");
		}
		case 1:
		{
			static randmodel;
			randmodel = __g_RandomSkinFemale[random(sizeof(__g_RandomSkinFemale))];
			AccountData[playerid][pGender] = 2;
			AccountData[playerid][pSkin] = randmodel;
			SetPlayerHealthEx(playerid, 100.0);
			SetPlayerArmourEx(playerid, 0.0);
			SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Pembuatan karakter berhasil dilakukan!");

			SetPlayerCameraPos(playerid, 642.535644, -2237.217285, 143.806137);
			SetPlayerCameraLookAt(playerid, 523.445556, -1929.099853, 0.045935);
			InterpolateCameraPos(playerid,642.535644, -2237.217285, 143.806137, 523.445556, -1929.099853, 143.806137,50000,CAMERA_MOVE);
			
			Dialog_Show(playerid, "SelectionRegSpawn", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Pilih Lokasi Spawn", 
			"Titik spawn\tDetail\tLokasi\n\
			Los Santos International Airport\tAnda spawn di bandara\tLos Santos (LS)", "Pilih", "");
		}
	}
	return 1;
}

Dialog:ShopCatalog(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	switch(listitem)
	{
		case 0: //Nasi Uduk
		{
			if(AccountData[playerid][pMoney] < 650) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

			TakePlayerMoneyEx(playerid, 650);
			Inventory_Add(playerid, "Nasi Uduk", 2769);
			ShowItemBox(playerid, "Cash", "Removed $650x", 1212, 5);
			ShowItemBox(playerid, "Nasi Uduk", "Received 1x", 2769, 6);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membeli nasi uduk.");
		}
		case 1: //Air Mineral
		{
			if(AccountData[playerid][pMoney] < 650) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

			TakePlayerMoneyEx(playerid, 650);
			Inventory_Add(playerid, "Air Mineral", 19570);
			ShowItemBox(playerid, "Cash", "Removed $650x", 1212, 5);
			ShowItemBox(playerid, "Air Mineral", "Received 1x", 19570, 6);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membeli air mineral.");
		}
		case 2: //skateboard
		{
			if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");
			if(AccountData[playerid][pMoney] < 870) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

			static Float:countingtotalweight;
			countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Skateboard"))/1000;
			if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

			TakePlayerMoneyEx(playerid, 870);

			Inventory_Add(playerid, "Skateboard", 19878, 1);
			ShowItemBox(playerid, "Cash", "Removed $870x", 1212, 5);
			ShowItemBox(playerid, "Skateboard", "Received 1x", 19878, 6);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membeli skateboard.");
		}
		case 3: //Perban
		{
			if(AccountData[playerid][pMoney] < 360) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

			static Float:countingtotalweight;
			countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Perban"))/1000;
			if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

			TakePlayerMoneyEx(playerid, 360);

			Inventory_Add(playerid, "Perban", 11736);
			ShowItemBox(playerid, "Cash", "Removed $360x", 1212, 5);
			ShowItemBox(playerid, "Perban", "Received 1x", 11736, 6);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membeli Perban.");
		}
		case 4: //Udud
		{
			if(AccountData[playerid][pMoney] < 310) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

			static Float:countingtotalweight;
			countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Udud"))/1000;
			if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

			TakePlayerMoneyEx(playerid, 310);

			Inventory_Add(playerid, "Udud", 19896, 12);
			ShowItemBox(playerid, "Cash", "Removed $310x", 1212, 5);
			ShowItemBox(playerid, "Udud", "Received 1x", 19896, 6);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membeli Udud.");
		}
		case 5: //Baseball Bat
		{
			if(AccountData[playerid][pMoney] < 950) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

			TakePlayerMoneyEx(playerid, 950);
			GivePlayerWeaponEx(playerid, 5, 1, WEAPON_TYPE_PLAYER);

			ShowItemBox(playerid, "Cash", "Removed $950x", 1212, 5);
			ShowItemBox(playerid, "Baseball Bat", "Received 1x", 336, 6);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membeli baseball bat.");
		}
		case 6: //Pisau
		{
			if(AccountData[playerid][pMoney] < 950) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

			TakePlayerMoneyEx(playerid, 950);
			GivePlayerWeaponEx(playerid, 4, 1, WEAPON_TYPE_PLAYER);

			ShowItemBox(playerid, "Cash", "Removed $950x", 1212, 5);
			ShowItemBox(playerid, "Knife", "Received 1x", 335, 6);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membeli knife.");
		}
		case 7: //Golf Stick
		{
			if(AccountData[playerid][pMoney] < 950) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

			TakePlayerMoneyEx(playerid, 950);
			GivePlayerWeaponEx(playerid, 2, 1, WEAPON_TYPE_PLAYER);

			ShowItemBox(playerid, "Cash", "Removed $950x", 1212, 5);
			ShowItemBox(playerid, "Golf Stick", "Received 1x", 333, 6);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membeli golf stick.");
		}
		case 8: //Pool Cue
		{
			if(AccountData[playerid][pMoney] < 950) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

			TakePlayerMoneyEx(playerid, 950);
			GivePlayerWeaponEx(playerid, 7, 1, WEAPON_TYPE_PLAYER);

			ShowItemBox(playerid, "Cash", "Removed $950x", 1212, 5);
			ShowItemBox(playerid, "Pool Cue", "Received 1x", 338, 6);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membeli pool cue.");
		}
		case 9: //Hunting Rifle
		{
			if(AccountData[playerid][pMoney] < 1200) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

			TakePlayerMoneyEx(playerid, 1200);
			AccountData[playerid][pHasHuntingRifle] = true;

			ShowItemBox(playerid, "Cash", "Removed $1,200x", 1212, 5);
			ShowItemBox(playerid, "Hunting Rifle", "Received 1x", 357, 6);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membeli hunting rifle.");
		}
		case 10: //Hunting Ammo
		{
			if(AccountData[playerid][pMoney] < 700) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

			TakePlayerMoneyEx(playerid, 700);
			Inventory_Add(playerid, "Hunt Ammo", 2358, 24);

			ShowItemBox(playerid, "Cash", "Removed $700x", 1212, 5);
			ShowItemBox(playerid, "Hunting Ammo", "Received 24x", 2358, 6);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membeli hunting ammo.");
		}
		case 11: //Obeng
		{
			if(AccountData[playerid][pMoney] < 620) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
			static Float:countingtotalweight;
			countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Obeng"))/1000;
			if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

			if(PlayerHasItem(playerid,"Obeng")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah memiliki Obeng!");
			
			TakePlayerMoneyEx(playerid, 620);

			Inventory_Add(playerid, "Obeng", 19627);
			ShowItemBox(playerid, "Cash", "Removed $620x", 1212, 5);
			ShowItemBox(playerid, "Obeng", "Received 1x", 19627, 6);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membeli Obeng.");
		}
		case 12: //Pilox
		{
			if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");
			if(AccountData[playerid][pMoney] < 780) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

			static Float:countingtotalweight;
			countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Pilox"))/1000;
			if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
			
			TakePlayerMoneyEx(playerid, 780);

			Inventory_Add(playerid, "Pilox", 365);
			ShowItemBox(playerid, "Cash", "Removed $780x", 1212, 5);
			ShowItemBox(playerid, "Pilox", "Received 1x", 365, 6);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membeli Pilox.");
		}
		case 13: //Senter
		{
			if(AccountData[playerid][pMoney] < 520) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

			static Float:countingtotalweight;
			countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Senter"))/1000;
			if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

			TakePlayerMoneyEx(playerid, 520);

			Inventory_Add(playerid, "Senter", 18641, 1);
			ShowItemBox(playerid, "Cash", "Removed $520x", 1212, 5);
			ShowItemBox(playerid, "Senter", "Received 1x", 18641, 6);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membeli Senter.");
		}
		case 14: //Cangkul
		{
			if(AccountData[playerid][pMoney] < 500) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
			static Float:countingtotalweight;
			countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Cangkul"))/1000;
			if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

			if(PlayerHasItem(playerid,"Cangkul")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah memiliki Cangkul!");
			
			TakePlayerMoneyEx(playerid, 500);

			Inventory_Add(playerid, "Cangkul", 2228);
			ShowItemBox(playerid, "Cash", "Removed $500x", 1212, 5);
			ShowItemBox(playerid, "Cangkul", "Received 1x", 2228, 6);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membeli Cangkul.");
		}
		case 15: //pancingan
		{
			if(AccountData[playerid][pMoney] < 980) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
			new Float:countingtotalweight;
			countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Pancingan"))/1000;
			if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

			TakePlayerMoneyEx(playerid, 980);

			Inventory_Add(playerid, "Pancingan", 18632);
			ShowItemBox(playerid, "Cash", "Removed $980x", 1212, 5);
			ShowItemBox(playerid, "Pancingan", "Received 1x", 18632, 6);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membeli Pancingan.");
		}
		case 16: //umpan
		{
			if(AccountData[playerid][pMoney] < 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

			Dialog_Show(playerid, "ShopBuyBait", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Warung", 
			"Anda akan membeli umpan seharga "DARKGREEN"$100/pcs\n\
			"YELLOW"(Masukkan berapa banyak yang ingin anda beli):", "Beli", "Batal");
		}
		case 17: //Ember
		{
			if(AccountData[playerid][pMoney] < 500) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
			static Float:countingtotalweight;
			countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Ember"))/1000;
			if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

			if(PlayerHasItem(playerid,"Ember")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah memiliki Ember!");
			
			TakePlayerMoneyEx(playerid, 500);

			Inventory_Add(playerid, "Ember", 19468);
			ShowItemBox(playerid, "Cash", "Removed $500x", 1212, 5);
			ShowItemBox(playerid, "Ember", "Received 1x", 19468, 6);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membeli Ember.");
		}
	}
	return 1;
}

Dialog:ShopBuyBait(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(isnull(inputtext))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");

	if(!IsNumericEx(inputtext))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Masukkan hanya angka!");

	if(strval(inputtext) < 1)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid!");

	static pricing;
	pricing = strval(inputtext) * 100;

	if(AccountData[playerid][pMoney] < RoundNegativeToPositive(pricing)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

	static Float:countingtotalweight;
	countingtotalweight = GetTotalWeightFloat(playerid) + float(strval(inputtext) * GetItemWeight("Umpan"))/1000;
	if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

	TakePlayerMoneyEx(playerid, pricing);

	Inventory_Add(playerid, "Umpan", 1603, strval(inputtext));

	ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(pricing)), 1212, 4);
	ShowItemBox(playerid, "Umpan", sprintf("Received %dx", strval(inputtext)), 1603, 5);

	ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil membeli ~b~%d bait ~l~seharga ~r~$%s.", strval(inputtext), FormatMoney(pricing)));
	return 1;
}

Dialog:VendingDrink(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(listitem < 0 || listitem > 1) return 1;

	if(AccountData[playerid][pMoney] < 200) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
	
	AccountData[playerid][pTempValue] = listitem;
	Dialog_Show(playerid, "VendingDrinkConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Vending Menu", 
	"Anda akan membeli minuman dari vending machine seharga "DARKGREEN"$200.50/pcs\n\
	"YELLOW"(Mohon masukkan berapa banyak yang ingin dibeli):", "Beli", "Batal");
	return 1;
}

Dialog:VendingDrinkConfirm(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(isnull(inputtext))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");

	if(!IsNumericEx(inputtext))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Masukkan hanya angka!");

	if(strval(inputtext) < 1)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid!");

	if(AccountData[playerid][pTempValue] < 0 || AccountData[playerid][pTempValue] > 1)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item apapun!");

	static pricing;
	pricing = strval(inputtext) * 200;

	if(AccountData[playerid][pMoney] < RoundNegativeToPositive(pricing)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
	
	if(AccountData[playerid][pTempValue] == 0)
	{
		static Float:countingtotalweight;
		countingtotalweight = GetTotalWeightFloat(playerid) + float(strval(inputtext) * GetItemWeight("Cola"))/1000;
		if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

		TakePlayerMoneyEx(playerid, pricing);

		Inventory_Add(playerid, "Cola", 2647, strval(inputtext));

		ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(pricing)), 1212, 4);
		ShowItemBox(playerid, "Cola", sprintf("Received %dx", strval(inputtext)), 2647, 5);
		ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil membeli ~b~%d cola ~l~seharga ~r~$%s.", strval(inputtext), FormatMoney(pricing)));
	}
	else
	{
		static Float:countingtotalweight;
		countingtotalweight = GetTotalWeightFloat(playerid) + float(strval(inputtext) * GetItemWeight("Sprunk"))/1000;
		if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

		TakePlayerMoneyEx(playerid, pricing);

		Inventory_Add(playerid, "Sprunk", 2601, strval(inputtext));

		ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(pricing)), 1212, 4);
		ShowItemBox(playerid, "Sprunk", sprintf("Received %dx", strval(inputtext)), 2601, 5);
		ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil membeli ~b~%d sprunk ~l~seharga ~r~$%s.", strval(inputtext), FormatMoney(pricing)));
	}
	PlayerPlaySound(playerid, 42600, 0.0, 0.0, 0.0);
	return 1;
}

Dialog:VendingSnack(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(listitem < 0 || listitem > 1) return 1;

	if(AccountData[playerid][pMoney] < 200) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
	
	AccountData[playerid][pTempValue] = listitem;
	Dialog_Show(playerid, "VendingSnackConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Vending Menu", 
	"Anda akan membeli snack dari vending machine seharga "DARKGREEN"$200.50/pcs\n\
	"YELLOW"(Mohon masukkan berapa banyak yang ingin dibeli):", "Beli", "Batal");
	return 1;
}

Dialog:VendingSnackConfirm(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(isnull(inputtext))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");

	if(!IsNumericEx(inputtext))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Masukkan hanya angka!");

	if(strval(inputtext) < 1)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid!");

	if(AccountData[playerid][pTempValue] < 0 || AccountData[playerid][pTempValue] > 1)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item apapun!");

	static pricing;
	pricing = strval(inputtext) * 200;

	if(AccountData[playerid][pMoney] < RoundNegativeToPositive(pricing)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
	
	if(AccountData[playerid][pTempValue] == 0)
	{
		static Float:countingtotalweight;
		countingtotalweight = GetTotalWeightFloat(playerid) + float(strval(inputtext) * GetItemWeight("Snack"))/1000;
		if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

		TakePlayerMoneyEx(playerid, pricing);

		Inventory_Add(playerid, "Snack", 19565, strval(inputtext));

		ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(pricing)), 1212, 4);
		ShowItemBox(playerid, "Snack", sprintf("Received %dx", strval(inputtext)), 19565, 5);
		ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil membeli ~b~%d snack ~l~seharga ~r~$%s.", strval(inputtext), FormatMoney(pricing)));
	}
	else
	{
		static Float:countingtotalweight;
		countingtotalweight = GetTotalWeightFloat(playerid) + float(strval(inputtext) * GetItemWeight("Cereal"))/1000;
		if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

		TakePlayerMoneyEx(playerid, pricing);

		Inventory_Add(playerid, "Cereal", 19562, strval(inputtext));

		ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(pricing)), 1212, 4);
		ShowItemBox(playerid, "Cereal", sprintf("Received %dx", strval(inputtext)), 19562, 5);
		ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil membeli ~b~%d cereal ~l~seharga ~r~$%s.", strval(inputtext), FormatMoney(pricing)));
	}
	PlayerPlaySound(playerid, 42601, 0.0, 0.0, 0.0);
	return 1;
}

Dialog:ElectronicCatalog(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
	switch(listitem)
	{
		case 0: //smartphone
		{
			if(AccountData[playerid][pMoney] < 2105) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

			static Float:countingtotalweight;
			countingtotalweight = GetTotalWeightFloat(playerid) + float(GetItemWeight("Smartphone"))/1000;
			if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

			TakePlayerMoneyEx(playerid, 2105);
			
			static string[128];
			mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `player_phones` WHERE `phoneOwner`=%d", AccountData[playerid][pID]);
			mysql_pquery(g_SQL, string, "OnPlayerBuySmartphone", "i", playerid);

			ShowItemBox(playerid, "Cash", "Removed $2,105x", 1212, 4);
			ShowItemBox(playerid, "Smartphone", "Received 1x", 19942, 5);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Transaksi berhasil dilakukan.");
		}
		case 1: //radio
		{
			if(AccountData[playerid][pMoney] < 2000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

			TakePlayerMoneyEx(playerid, 2000);
			PlayerVoiceData[playerid][pHasRadio] = true;

			ShowItemBox(playerid, "Cash", "Removed $2,000", 1212, 4);
			ShowItemBox(playerid, "Radio", "Received 1x", 19942, 5);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Transaksi berhasil dilakukan.");
		}
		case 2: //earphone
		{
			if(AccountData[playerid][pMoney] < 1800) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

			TakePlayerMoneyEx(playerid, 1800);
			AccountData[playerid][pEarphone] = true;

			ShowItemBox(playerid, "Cash", "Removed $1,800", 1212, 4);
			ShowItemBox(playerid, "Earphone", "Received 1x", 19421, 5);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Transaksi berhasil dilakukan.");
		}
		case 3: //boombox
		{
			if(AccountData[playerid][pVIP] < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Donatur VIP!");
			
			if(AccountData[playerid][pMoney] < 3690) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

			TakePlayerMoneyEx(playerid, 3690);
			AccountData[playerid][pBoombox] = true;

			ShowItemBox(playerid, "Cash", "Removed $3,690x", 1212, 4);
			ShowItemBox(playerid, "Boombox", "Received 1x", 2103, 5);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Transaksi berhasil dilakukan.");
		}
		case 4: //vape
		{
			if(AccountData[playerid][pVIP] < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Donatur VIP Super Pinky!");
			
			if(AccountData[playerid][pMoney] < 6300) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

			TakePlayerMoneyEx(playerid, 6300);

			Inventory_Add(playerid, "Vape", 19823);

			ShowItemBox(playerid, "Cash", "Removed $6,300x", 1212, 4);
			ShowItemBox(playerid, "Vape", "Received 1x", 19823, 5);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Transaksi berhasil dilakukan.");
		}
	}
	return 1;
}

Dialog:AmmunationCatalog(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
	if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");
	if(!AccountData[playerid][pFirearmLic]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Kartu Izin Senjata Api!");

	switch(listitem)
	{
		case 0: //katana
		{
			if(AccountData[playerid][pMoney] < 46500) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

			TakePlayerMoneyEx(playerid, 46500);

			GivePlayerWeaponEx(playerid, 8, 1, WEAPON_TYPE_PLAYER);
			ShowItemBox(playerid, "Cash", "Removed $46,500x", 1212, 4);
			ShowItemBox(playerid, "Katana", "Received 1x", 339, 5);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Transaksi berhasil dilakukan.");
		}
		case 1: //Colt 45
		{
			if(AccountData[playerid][pMoney] < 155000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

			TakePlayerMoneyEx(playerid, 155000);

			GivePlayerWeaponEx(playerid, 22, 250, WEAPON_TYPE_PLAYER);
			ShowItemBox(playerid, "Cash", "Removed $155,000x", 1212, 4);
			ShowItemBox(playerid, "Colt-45", "Received 1x", 346, 5);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Transaksi berhasil dilakukan.");
		}
		case 2: //Silenced Pistol
		{
			if(AccountData[playerid][pMoney] < 155000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

			TakePlayerMoneyEx(playerid, 155000);

			GivePlayerWeaponEx(playerid, 23, 250, WEAPON_TYPE_PLAYER);
			ShowItemBox(playerid, "Cash", "Removed $155,000x", 1212, 4);
			ShowItemBox(playerid, "SLC Pistol", "Received 1x", 347, 5);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Transaksi berhasil dilakukan.");
		}
		case 3: //Desert Eagle
		{
			if(AccountData[playerid][pMoney] < 180000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

			TakePlayerMoneyEx(playerid, 180000);

			GivePlayerWeaponEx(playerid, 24, 250, WEAPON_TYPE_PLAYER);
			ShowItemBox(playerid, "Cash", "Removed $180.000x", 1212, 4);
			ShowItemBox(playerid, "Desert Eagle", "Received 1x", 348, 5);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Transaksi berhasil dilakukan.");
		}
		case 4: //Shotgun
		{
			if(AccountData[playerid][pMoney] < 285000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

			TakePlayerMoneyEx(playerid, 285000);

			GivePlayerWeaponEx(playerid, 25, 350, WEAPON_TYPE_PLAYER);
			ShowItemBox(playerid, "Cash", "Removed $285.000x", 1212, 4);
			ShowItemBox(playerid, "Shotgun", "Received 1x", 349, 5);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Transaksi berhasil dilakukan.");
		}
		case 5: //Uzi
		{
			if(AccountData[playerid][pMoney] < 267000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

			TakePlayerMoneyEx(playerid, 267000);

			GivePlayerWeaponEx(playerid, 28, 500, WEAPON_TYPE_PLAYER);
			ShowItemBox(playerid, "Cash", "Removed $267.000x", 1212, 4);
			ShowItemBox(playerid, "Uzi", "Received 1x", 352, 5);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Transaksi berhasil dilakukan.");
		}
		case 6: //MP5
		{
			if(AccountData[playerid][pMoney] < 426000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

			TakePlayerMoneyEx(playerid, 426000);

			GivePlayerWeaponEx(playerid, 29, 500, WEAPON_TYPE_PLAYER);
			ShowItemBox(playerid, "Cash", "Removed $426.000x", 1212, 4);
			ShowItemBox(playerid, "MP-5", "Received 1x", 353, 5);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Transaksi berhasil dilakukan.");
		}
		case 7: //Tec 9
		{
			if(AccountData[playerid][pMoney] < 267000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

			TakePlayerMoneyEx(playerid, 267000);

			GivePlayerWeaponEx(playerid, 32, 500, WEAPON_TYPE_PLAYER);
			ShowItemBox(playerid, "Cash", "Removed $267.000x", 1212, 4);
			ShowItemBox(playerid, "Tec-9", "Received 1x", 372, 5);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Transaksi berhasil dilakukan.");
		}
	}
	return 1;
}

Dialog:JobFarmerProcess(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
	
	switch(listitem)
	{
		case 0: //chili sauce
		{
			if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
			if(Inventory_Count(playerid, "Cabai") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki 5 Cabai!");
			if(Inventory_Count(playerid, "Botol") < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki 2 Botol!");
			if(Inventory_Count(playerid, "Plastik") < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki 2 Plastik!");

			new Float:countingtotalweight;
			countingtotalweight = GetTotalWeightFloat(playerid) + float(1 * GetItemWeight("Chili Sauce"))/1000;
			if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
			
			AccountData[playerid][pActivityTime] = 1;
			pProcessChiliTimer[playerid] = true;
			PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENGOLAH CABAI");
			ShowProgressBar(playerid);
			ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, 1, 0, 0, 0, 0, 1);

			HideNotifBox(playerid);
		}
		case 1: //rice
		{
			if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
			if(Inventory_Count(playerid, "Padi") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki 5 Padi!");
			if(Inventory_Count(playerid, "Fabric") < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki 2 fabric!");
			if(Inventory_Count(playerid, "Plastik") < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki 2 Plastik!");

			new Float:countingtotalweight;
			countingtotalweight = GetTotalWeightFloat(playerid) + float(1 * GetItemWeight("Rice"))/1000;
			if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
			
			AccountData[playerid][pActivityTime] = 1;
			pProcessRiceTimer[playerid] = true;
			PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENGOLAH PADI");
			ShowProgressBar(playerid);
			ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, 1, 0, 0, 0, 0, 1);

			HideNotifBox(playerid);
		}
		case 2: //Gula
		{
			if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
			if(Inventory_Count(playerid, "Tebu") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki 5 Tebu!");
			if(Inventory_Count(playerid, "Fabric") < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki 2 fabric!");
			if(Inventory_Count(playerid, "Plastik") < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki 2 Plastik!");

			new Float:countingtotalweight;
			countingtotalweight = GetTotalWeightFloat(playerid) + float(1 * GetItemWeight("Gula"))/1000;
			if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
			
			AccountData[playerid][pActivityTime] = 1;
			pPorcessSugarTimer[playerid] = true;
			PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENGOLAH GULA");
			ShowProgressBar(playerid);
			ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, 1, 0, 0, 0, 0, 1);

			HideNotifBox(playerid);
		}
	} 
	return 1;
}

Dialog:JobFarmerBuySeeds(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	AccountData[playerid][pTempValue] = listitem;
	switch(listitem)
	{
		case 0: //cabe
		{
			Dialog_Show(playerid, "JobFarmerBuySeedsConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Bibit Cabai", 
			""WHITE"Anda akan membeli "YELLOW"Bibit Cabai "WHITE"seharga "GREEN"$40/bibit\n\
			"YELLOW"(Masukkan berapa banyak bibit yang ingin anda beli):", "Input", "Batal");
		}
		case 1: //tebu
		{
			Dialog_Show(playerid, "JobFarmerBuySeedsConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Bibit Tebu", 
			""WHITE"Anda akan membeli "YELLOW"Bibit Tebu "WHITE"seharga "GREEN"$40/bibit\n\
			"YELLOW"(Masukkan berapa banyak bibit yang ingin anda beli):", "Input", "Batal");
		}
		case 2: //padi
		{
			Dialog_Show(playerid, "JobFarmerBuySeedsConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Bibit Padi", 
			""WHITE"Anda akan membeli "YELLOW"Bibit Padi "WHITE"seharga "GREEN"$40/bibit\n\
			"YELLOW"(Masukkan berapa banyak bibit yang ingin anda beli):", "Input", "Batal");
		}
	}
	return 1;
}

Dialog:JobFarmerBuyFSeeds(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	AccountData[playerid][pTempValue] = listitem;
	switch(listitem)
	{
		case 0: //Strawberry
		{
			Dialog_Show(playerid, "JobFarmerBuySeedsFC", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Bibit Strawberry", 
			""WHITE"Anda akan membeli "YELLOW"Bibit Strawberry "WHITE"seharga "GREEN"$40/bibit\n\
			"YELLOW"(Masukkan berapa banyak bibit yang ingin anda beli):", "Input", "Batal");
		}
		case 1: //Jeruk
		{
			Dialog_Show(playerid, "JobFarmerBuySeedsFC", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Bibit Jeruk", 
			""WHITE"Anda akan membeli "YELLOW"Bibit Jeruk "WHITE"seharga "GREEN"$40/bibit\n\
			"YELLOW"(Masukkan berapa banyak bibit yang ingin anda beli):", "Input", "Batal");
		}
		case 2: //Anggur
		{
			Dialog_Show(playerid, "JobFarmerBuySeedsFC", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Bibit Anggur", 
			""WHITE"Anda akan membeli "YELLOW"Bibit Anggur "WHITE"seharga "GREEN"$40/bibit\n\
			"YELLOW"(Masukkan berapa banyak bibit yang ingin anda beli):", "Input", "Batal");
		}
	}
	return 1;
}

Dialog:JobFarmerBuySeedsConfirm(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		AccountData[playerid][pTempValue] = -1;
		return 1;
	}

	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");
	if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Masukkan hanya angka!");
	if(strval(inputtext) < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid!");

	static rumusharga;
	switch(AccountData[playerid][pTempValue])
	{
		case 0: //cabe
		{
			rumusharga = strval(inputtext) * 40;

			if(AccountData[playerid][pMoney] < RoundNegativeToPositive(rumusharga)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
	
			new Float:countingtotalweight;
			countingtotalweight = GetTotalWeightFloat(playerid) + float(strval(inputtext) * GetItemWeight("Bibit Cabai"))/1000;
			if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

			TakePlayerMoneyEx(playerid, rumusharga);
			Inventory_Add(playerid, "Bibit Cabai", 2663, strval(inputtext));
			ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(rumusharga)), 1212, 5);
			ShowItemBox(playerid, "Bibit Cabai", sprintf("Received %dx", strval(inputtext)), 2663, 6);
		}
		case 1: //tebu
		{
			rumusharga = strval(inputtext) * 40;

			if(AccountData[playerid][pMoney] < RoundNegativeToPositive(rumusharga)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
	
			new Float:countingtotalweight;
			countingtotalweight = GetTotalWeightFloat(playerid) + float(strval(inputtext) * GetItemWeight("Bibit Tebu"))/1000;
			if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

			TakePlayerMoneyEx(playerid, rumusharga);
			Inventory_Add(playerid, "Bibit Tebu", 2663, strval(inputtext));
			ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(rumusharga)), 1212, 5);
			ShowItemBox(playerid, "Bibit Tebu", sprintf("Received %dx", strval(inputtext)), 2663, 6);
		}
		case 2: //padi
		{
			rumusharga = strval(inputtext) * 40;

			if(AccountData[playerid][pMoney] < RoundNegativeToPositive(rumusharga)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
	
			new Float:countingtotalweight;
			countingtotalweight = GetTotalWeightFloat(playerid) + float(strval(inputtext) * GetItemWeight("Bibit Padi"))/1000;
			if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

			TakePlayerMoneyEx(playerid, rumusharga);
			Inventory_Add(playerid, "Bibit Padi", 2663, strval(inputtext));
			ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(rumusharga)), 1212, 5);
			ShowItemBox(playerid, "Bibit Padi", sprintf("Received %dx", strval(inputtext)), 2663, 6);
		}
	}
	AccountData[playerid][pTempValue] = -1;
	return 1;
}

Dialog:JobFarmerBuySeedsFC(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		AccountData[playerid][pTempValue] = -1;
		return 1;
	}

	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");
	if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Masukkan hanya angka!");
	if(strval(inputtext) < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid!");

	static rumusharga;
	switch(AccountData[playerid][pTempValue])
	{
		case 0: //cabe
		{
			rumusharga = strval(inputtext) * 40;

			if(AccountData[playerid][pMoney] < RoundNegativeToPositive(rumusharga)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
	
			new Float:countingtotalweight;
			countingtotalweight = GetTotalWeightFloat(playerid) + float(strval(inputtext) * GetItemWeight("Bibit Strawberry"))/1000;
			if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

			TakePlayerMoneyEx(playerid, rumusharga);
			Inventory_Add(playerid, "Bibit Strawberry", 2663, strval(inputtext));
			ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(rumusharga)), 1212, 5);
			ShowItemBox(playerid, "Bibit Strawberry", sprintf("Received %dx", strval(inputtext)), 2663, 6);
		}
		case 1: //tebu
		{
			rumusharga = strval(inputtext) * 40;

			if(AccountData[playerid][pMoney] < RoundNegativeToPositive(rumusharga)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
	
			new Float:countingtotalweight;
			countingtotalweight = GetTotalWeightFloat(playerid) + float(strval(inputtext) * GetItemWeight("Bibit Jeruk"))/1000;
			if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

			TakePlayerMoneyEx(playerid, rumusharga);
			Inventory_Add(playerid, "Bibit Jeruk", 2663, strval(inputtext));
			ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(rumusharga)), 1212, 5);
			ShowItemBox(playerid, "Bibit Jeruk", sprintf("Received %dx", strval(inputtext)), 2663, 6);
		}
		case 2: //padi
		{
			rumusharga = strval(inputtext) * 40;

			if(AccountData[playerid][pMoney] < RoundNegativeToPositive(rumusharga)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
	
			new Float:countingtotalweight;
			countingtotalweight = GetTotalWeightFloat(playerid) + float(strval(inputtext) * GetItemWeight("Bibit Anggur"))/1000;
			if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

			TakePlayerMoneyEx(playerid, rumusharga);
			Inventory_Add(playerid, "Bibit Anggur", 2663, strval(inputtext));
			ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(rumusharga)), 1212, 5);
			ShowItemBox(playerid, "Bibit Anggur", sprintf("Received %dx", strval(inputtext)), 2663, 6);
		}
	}
	AccountData[playerid][pTempValue] = -1;
	return 1;
}

Dialog:VehicleInsurance(playerid, response, listitem, inputtext[])
{
	if(!response)
		return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
	
	if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan untuk ditebus!");
	static id;
	id = ReturnVehicleIDInsuranced(playerid, listitem);
	if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan untuk ditebus!");

	if(AccountData[playerid][pMoney] < 3500) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki uang yang cukup!");
	if(PlayerVehicle[id][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaaan ini bukan milik anda!");

	//if(IsModelABike(PlayerVehicle[id][pVehModelID]) && AccountData[playerid][pMBLicTime] == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki SIM C atau sudah expired!");
	//if(IsModelATruck(PlayerVehicle[id][pVehModelID]) && AccountData[playerid][pGVL2LicTime] == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki SIM B atau sudah expired!");
	//if(IsModelALorry(PlayerVehicle[id][pVehModelID]) && AccountData[playerid][pGVL2LicTime] == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki SIM B atau sudah expired!");
	//if(IsModelAHelicopter(PlayerVehicle[id][pVehModelID]) && AccountData[playerid][pAir1LicTime] == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki SIH atau sudah expired!");

	// if(!IsModelABike(PlayerVehicle[id][pVehModelID]) && !IsModelATruck(PlayerVehicle[id][pVehModelID]) && !IsModelALorry(PlayerVehicle[id][pVehModelID]) && !IsModelAHelicopter(PlayerVehicle[id][pVehModelID]))
	// {
	// 	if(AccountData[playerid][pGVL1LicTime] == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki SIM A atau sudah expired!"); 
	// }

	PlayerVehicle[id][pVehParked] = -1;
	PlayerVehicle[id][pVehFamGarage] = -1;
	PlayerVehicle[id][pVehHouseGarage] = -1;
	PlayerVehicle[id][pVehInsuranced] = false;
	PlayerVehicle[id][pVehTireLocked] = false;

	PlayerVehicle[id][pVehPos][0] = -2437.8345;
	PlayerVehicle[id][pVehPos][1] = 1035.3152;
	PlayerVehicle[id][pVehPos][2] = 50.8273;
	PlayerVehicle[id][pVehPos][3] = 0.1480;
	
	PlayerVehicle[id][pVehFuel] = 30;
	PlayerVehicle[id][pVehHealth] = 650.0;
	PlayerVehicle[id][pVehDamage][0] = 0;
	PlayerVehicle[id][pVehDamage][1] = 0;
	PlayerVehicle[id][pVehDamage][2] = 0;
	PlayerVehicle[id][pVehDamage][3] = 0;
	PlayerVehicle[id][pVehWorld] = 0;
	PlayerVehicle[id][pVehInterior] = 0;

	TakePlayerMoneyEx(playerid, 3500);
	ShowItemBox(playerid, "Cash", "Removed $3,500x", 1212, 5);
	
	OnPlayerVehicleRespawn(id);

	SetTimerEx("ForcePlayerHopInVehicle", 1500, false, "idd", playerid, PlayerVehicle[id][pVehPhysic], 0);

	static string[144];
	mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_vehicles` SET `PVeh_Parked` = -1, `PVeh_Insuranced` = 0 WHERE `id` = %d", PlayerVehicle[id][pVehID]);
	mysql_pquery(g_SQL, string);
	return 1;
}

Dialog:VehicleTrunk(playerid, response, listitem, inputtext[])
{
	if(!response)
		return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	switch(listitem)
	{
		case 0:
		{
			if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berjalan kaki!");
	
			new vehid = GetNearestVehicleToPlayer(playerid, 4.0, false);
			if(vehid == INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan di dekat anda!");

			if(!IsPlayerNearBoot(playerid, vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di dekat trunk kendaraan!");

			if(IsABike(vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak memiliki trunk!");

			if(VehicleCore[vehid][vCoreLocked]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini sedang terkunci!");

			switch (GetTrunkStatus(vehid))
			{
				case false:
				{
					SwitchVehicleBoot(vehid, true);
				}
				case true:
				{
					SwitchVehicleBoot(vehid, false);
				}
			}
		}
		case 1:
		{
			if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berjalan kaki!");

			if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING || pInSpecMode[playerid] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");

			new vehid = GetNearestVehicleToPlayer(playerid, 4.0, false);
			if(vehid == INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan di dekat anda!");

			if(!IsPlayerNearBoot(playerid, vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di dekat trunk kendaraan!");

			if(IsABike(vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak memiliki trunk!");

			if(VehicleCore[vehid][vCoreLocked]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini sedang terkunci!");

			if(CountPlayerTrunked(vehid) >= 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Trunk ini telah diisi orang lain!");
			
			GetPlayerHealth(playerid, AccountData[playerid][pHealth]);
			if(AccountData[playerid][pHasArmor])
			{
				GetPlayerArmour(playerid, AccountData[playerid][pArmor]);
			}
			else
			{
				AccountData[playerid][pArmor] = 0.0;
			}

			SavingVehID[playerid] = vehid;
			pInSpecMode[playerid] = 2;
			TogglePlayerSpectating(playerid, true);
			PlayerSpectateVehicle(playerid, vehid);

			SendClientMessage(playerid, -1, "Anda sekarang masuk di dalam trunk, gunakan "YELLOW"/out "WHITE"untuk keluar.");

			PlayerPlaySound(playerid, 12200, 0, 0, 0);
		}
		case 2:
		{
			if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berjalan kaki!");

			if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING || pInSpecMode[playerid] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");

			new vehid = GetNearestVehicleToPlayer(playerid, 4.0, false);
			if(vehid == INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan di dekat anda!");

			if(!IsPlayerNearBoot(playerid, vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di dekat trunk kendaraan!");

			if(IsABike(vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak memiliki trunk!");

			if(VehicleCore[vehid][vCoreLocked]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini sedang terkunci!");

			if(CountPlayerTrunked(vehid) >= 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Trunk ini telah diisi orang lain!");

			new frmxt[522], count = 0;

			foreach(new i : Player) if(i != playerid) if(IsPlayerNearPlayer(playerid, i, 3.2)) 
			{
				if (i % 2 == 0) {
					format(frmxt, sizeof(frmxt), "%s"WHITE"Player ID - (%d)\n", frmxt, i);
				}
				else {
					format(frmxt, sizeof(frmxt), "%s"GRAY"Player ID - (%d)\n", frmxt, i);
				}
				NearestUser[playerid][count++] = i;
			}

			if(count == 0) 
			{
				PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
				return Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Masukkan ke Trunk", "Tidak ada pemain terdekat!", "Tutup", "");
			}

			Dialog_Show(playerid, "VehicleForceTrunk", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Masukkan ke Trunk", frmxt, "Pilih", "Batal");
		}
		case 3:
		{
			if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berjalan kaki!");

			if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING || pInSpecMode[playerid] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");

			new vehid = GetNearestVehicleToPlayer(playerid, 4.0, false);
			if(vehid == INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan di dekat anda!");

			if(!IsPlayerNearBoot(playerid, vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di dekat trunk kendaraan!");

			if(IsABike(vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak memiliki trunk!");

			if(VehicleCore[vehid][vCoreLocked]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini sedang terkunci!");

			new frmxt[522], count = 0;

			foreach(new i : Player) if(i != playerid) if((pInSpecMode[i] == 2 || pInSpecMode[i] == 3) && SavingVehID[i] == vehid) 
			{
				if (i % 2 == 0) {
					format(frmxt, sizeof(frmxt), "%s"WHITE"Player ID - (%d)\n", frmxt, i);
				}
				else {
					format(frmxt, sizeof(frmxt), "%s"GRAY"Player ID - (%d)\n", frmxt, i);
				}
				NearestUser[playerid][count++] = i;
			}

			if(count == 0) 
			{
				PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
				return Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Keluarkan dari Trunk", "Tidak ada player di dalam trunk!", "Tutup", "");
			}

			Dialog_Show(playerid, "VehicleForceUntrunk", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Keluarkan dari Trunk", frmxt, "Pilih", "Batal");
		}
	}
	return 1;
}

Dialog:VehicleForceTrunk(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
	if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada pemain terdekat!");

	new id = NearestUser[playerid][listitem];
	if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada pemain terdekat!");
	
	if(!IsPlayerConnected(id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(!IsPlayerNearPlayer(playerid, id, 3.2)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak dekat dengan anda!");
	
	if(GetPlayerState(id) == PLAYER_STATE_SPECTATING) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
	if(pInSpecMode[id] == 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sudah di dalam trunk!");

	new vehid = GetNearestVehicleToPlayer(playerid, 4.0, false);
	if(vehid == INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan di dekat anda!");
	if(!IsPlayerNearBoot(playerid, vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di dekat trunk kendaraan!");
	if(IsABike(vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak memiliki trunk!");
	if(VehicleCore[vehid][vCoreLocked]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini sedang terkunci!");
	
	if(CountPlayerTrunked(vehid) >= 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Trunk ini telah diisi orang lain!");

	GetPlayerHealth(id, AccountData[id][pHealth]);
	if(AccountData[id][pHasArmor])
	{
		GetPlayerArmour(id, AccountData[id][pArmor]);
	}
	else
	{
		AccountData[id][pArmor] = 0.0;
	}

	SavingVehID[id] = vehid;
	pInSpecMode[id] = 3;
	TogglePlayerSpectating(id, true);
	PlayerSpectateVehicle(id, vehid);

	PlayerPlaySound(id, 12200, 0, 0, 0);

	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasukkan pemain tersebut!");

	SendClientMessageEx(id, -1, "Anda telah di-masukkan ke trunk oleh "YELLOW"%s [%s] (ID: %d)", AccountData[playerid][pName], AccountData[playerid][pUCP], playerid);

	for(new x; x < 100; x++)
	{
		NearestUser[playerid][x] = INVALID_PLAYER_ID;
	}
	return 1;
}

Dialog:VehicleForceUntrunk(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
	if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada pemain di dalam trunk!");

	new otherid = NearestUser[playerid][listitem];
	if(otherid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada pemain di dalam trunk!");
	
	if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(!AccountData[otherid][pSpawned]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut belum spawn!");
	if(pInSpecMode[otherid] != 2 && pInSpecMode[otherid] != 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak sedang dimasukkan ke trunk!");

	new vid = SavingVehID[otherid];
	if(!IsValidVehicle(vid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut tidak ada/tidak valid!");

	PlayerSpectatePlayer(otherid, INVALID_PLAYER_ID);
	PlayerSpectateVehicle(otherid, INVALID_VEHICLE_ID);

	GetVehicleBoot(vid, AccountData[otherid][pPos][0], AccountData[otherid][pPos][1], AccountData[otherid][pPos][2]);

	AccountData[otherid][pInterior] = GetVehicleInterior(vid);
	AccountData[otherid][pWorld] = GetVehicleVirtualWorld(vid);

	SetSpawnInfo(otherid, NO_TEAM, AccountData[otherid][pSkin], AccountData[otherid][pPos][0], AccountData[otherid][pPos][1], AccountData[otherid][pPos][2], 180.0, 0, 0, 0, 0, 0, 0);
	TogglePlayerSpectating(otherid, false);

	SavingVehID[otherid] = INVALID_VEHICLE_ID;
	pInSpecMode[otherid] = 0;

	ShowTDN(otherid, NOTIFICATION_WARNING, "Anda telah ditendang dari trunk kendaraan.");
	ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mengeluarkan Pemain tersebut dari trunk kendaraan.");

	PlayerPlaySound(otherid, 12200, 0, 0, 0);

	for(new x; x < 100; x++)
	{
		NearestUser[playerid][x] = INVALID_PLAYER_ID;
	}
	return 1;
}

Dialog:VehicleFind(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
	Dialog_Show(playerid, "VehicleTrack", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Track Veh", ""WHITE"Pencarian kendaraan\n"YELLOW"(Masukkan VID kendaraan yang ingin dicari):", "Input", "Batal");
	return 1;
}

Dialog:VehicleTrack(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	static Float:posisiX, Float:posisiY, Float:posisiZ,
		carid;
	
	if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Masukkan hanya angka!");

	carid = strval(inputtext);
	
	if(!IsValidVehicle(carid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut tidak terspawn!");

	foreach(new veh : PvtVehicles)
	{
		if(PlayerVehicle[veh][pVehPhysic] == carid)
		{
			if(PlayerVehicle[veh][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID kendaraan tersebut bukan milik anda!");

			AccountData[playerid][pUsingGPS] = true;

			if(DestroyDynamicRaceCP(AccountData[playerid][pGPSCP]))
				AccountData[playerid][pGPSCP] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

			GetVehiclePos(carid, posisiX, posisiY, posisiZ);
			AccountData[playerid][pGPSCP] = CreateDynamicRaceCP(1, posisiX, posisiY, posisiZ, posisiX, posisiY, posisiZ, 3.5, 0, 0, playerid, 10000.00, -1, 0);
			SendClientMessageEx(playerid, -1, "%s milikmu berada di %s, ikutilah tanda yang telah diberikan.", GetVehicleModelName(PlayerVehicle[veh][pVehModelID]), GetLocation(posisiX, posisiY, posisiZ));
		}
	}
	return 1;
}

Dialog:VehicleSelling(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");
	if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Masukkan hanya angka!");

	static vid, string[358];
	vid = strval(inputtext);
	if(!IsValidVehicle(vid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut tidak terspawn!");

	foreach(new pv : PvtVehicles)
	{
		if(PlayerVehicle[pv][pVehPhysic] == vid)
		{
			if(PlayerVehicle[pv][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID kendaraan tersebut bukan milik anda!");
			if(!strcmp(PlayerVehicle[pv][pVehPlate], "-", false)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut tidak memiliki plat!");
			if(PlayerVehicle[pv][pVehRental] > -1 || PlayerVehicle[pv][pVehRentTime] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan rental tidak dapat dijual!");
			if(PlayerVehicle[pv][pVehTireLocked]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ban kendaraan tersebut sedang dikunci!");
			
			static Float:pricing;
			pricing = GetVehiclePrice(PlayerVehicle[pv][pVehModelID]) * 0.15;
			GivePlayerMoneyEx(playerid, floatround(pricing));
			
			SIM(playerid, "Kendaraan tersebut laku seharga $%s", FormatMoney(floatround(pricing)));

			if(Iter_Contains(Vehicle, PlayerVehicle[pv][pVehPhysic]))
			{
				SetVehicleNeonLights(PlayerVehicle[pv][pVehPhysic], false, PlayerVehicle[pv][pVehNeon], 0);
			}
			DestroyVehicle(PlayerVehicle[pv][pVehPhysic]);
			PlayerVehicle[pv][pVehHandbraked] = false;

			mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `vehicle_bagasi` WHERE `Veh_DBID`=%d", PlayerVehicle[pv][pVehID]);
			mysql_pquery(g_SQL, string);
			mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `vehicle_holster` WHERE `Veh_DBID`=%d", PlayerVehicle[pv][pVehID]);
			mysql_pquery(g_SQL, string);
			mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `player_vehicles` WHERE `id` = %d", PlayerVehicle[pv][pVehID]);
			mysql_pquery(g_SQL, string);
			mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `vtoys` WHERE `Veh_DBID`=%d", PlayerVehicle[pv][pVehID]);
			mysql_pquery(g_SQL, string);

			for(new x; x < 6; x++)
			{
				vtData[pv][x][vtoy_modelid] = 0;
				vtData[pv][x][vtoy_text][0] = EOS;
				strcopy(vtData[pv][x][vtoy_font], "Arial");
				vtData[pv][x][vtoy_fontsize] = 11;
				vtData[pv][x][vtoy_fontcolor][0] = 255;
				vtData[pv][x][vtoy_fontcolor][1] = 0;
				vtData[pv][x][vtoy_fontcolor][2] = 0;
				vtData[pv][x][vtoy_fontcolor][3] = 0;
				vtData[pv][x][vtoy_fontcolor][4] = 0;
				vtData[pv][x][vtoy_objectcolor][0] = 255;
				vtData[pv][x][vtoy_objectcolor][1] = 0;
				vtData[pv][x][vtoy_objectcolor][2] = 0;
				vtData[pv][x][vtoy_objectcolor][3] = 0;
				vtData[pv][x][vtoy_objectcolor][4] = 0;
				vtData[pv][x][vtoy_x] = 0.0;
				vtData[pv][x][vtoy_y] = 0.0;
				vtData[pv][x][vtoy_z] = 0.0;
				vtData[pv][x][vtoy_rx] = 0.0;
				vtData[pv][x][vtoy_ry] = 0.0;
				vtData[pv][x][vtoy_rz] = 0.0;
			}

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

			Iter_Remove(PvtVehicles, pv);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menjual kendaraan tersebut");
		}
	}
	return 1;
}

Dialog:ToggleSettings(playerid, response, listitem, inputtext[])
{
	static string[512];
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	switch(listitem)
	{
		case 0: //pm
		{
			switch(ToggleInfo[playerid][TogPM])
			{
				case false:
				{
					ToggleInfo[playerid][TogPM] = true;
					mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_TogPM` = 1 WHERE `pID` = %d", string, AccountData[playerid][pID]);
					mysql_pquery(g_SQL, string);

					ShowTDN(playerid, NOTIFICATION_INFO, "Private Message ~g~aktif.");
				}
				case true:
				{
					ToggleInfo[playerid][TogPM] = false;
					mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_TogPM` = 0 WHERE `pID` = %d", string, AccountData[playerid][pID]);
					mysql_pquery(g_SQL, string);

					ShowTDN(playerid, NOTIFICATION_INFO, "Private Message ~r~tidak aktif.");
				}
			}
		}
		case 1: //global ooc
		{
			switch(ToggleInfo[playerid][TogGOOC])
			{
				case false:
				{
					ToggleInfo[playerid][TogGOOC] = true;
					mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_TogGOOC` = 1 WHERE `pID` = %d", string, AccountData[playerid][pID]);
					mysql_pquery(g_SQL, string);

					ShowTDN(playerid, NOTIFICATION_INFO, "Global OOC Messages ~g~aktif.");
				}
				case true:
				{
					ToggleInfo[playerid][TogGOOC] = false;
					mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_TogGOOC` = 0 WHERE `pID` = %d", string, AccountData[playerid][pID]);
					mysql_pquery(g_SQL, string);

					ShowTDN(playerid, NOTIFICATION_INFO, "Global OOC Messages ~r~tidak aktif.");
				}
			}
		}
		case 2: //TogLogin
		{
			switch(ToggleInfo[playerid][TogLogin])
			{
				case false:
				{
					ToggleInfo[playerid][TogLogin] = true;
					mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_TogLogin` = 1 WHERE `pID` = %d", string, AccountData[playerid][pID]);
					mysql_pquery(g_SQL, string);

					ShowTDN(playerid, NOTIFICATION_INFO, "Login Messages ~g~aktif.");
				}
				case true:
				{
					ToggleInfo[playerid][TogLogin] = false;
					mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_TogLogin` = 0 WHERE `pID` = %d", string, AccountData[playerid][pID]);
					mysql_pquery(g_SQL, string);

					ShowTDN(playerid, NOTIFICATION_INFO, "Login Messages ~r~tidak aktif.");
				}
			}
		}
		case 3: //TogLevel
		{
			switch(ToggleInfo[playerid][TogLevel])
			{
				case false:
				{
					ToggleInfo[playerid][TogLevel] = true;
					mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_TogLevel` = 1 WHERE `pID` = %d", string, AccountData[playerid][pID]);
					mysql_pquery(g_SQL, string);

					ShowTDN(playerid, NOTIFICATION_INFO, "Level Up Messages ~g~aktif.");
				}
				case true:
				{
					ToggleInfo[playerid][TogLevel] = false;
					mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_TogLevel` = 0 WHERE `pID` = %d", string, AccountData[playerid][pID]);
					mysql_pquery(g_SQL, string);

					ShowTDN(playerid, NOTIFICATION_INFO, "Level Up Messages ~g~tidak aktif.");
				}
			}
		}
		case 4: //TogAdv
		{
			switch(ToggleInfo[playerid][TogAdv])
			{
				case false:
				{
					ToggleInfo[playerid][TogAdv] = true;
					mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_TogAdv` = 1 WHERE `pID` = %d", string, AccountData[playerid][pID]);
					mysql_pquery(g_SQL, string);

					ShowTDN(playerid, NOTIFICATION_INFO, "Advertisement Messages ~g~aktif.");
				}
				case true:
				{
					ToggleInfo[playerid][TogAdv] = false;
					mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_TogAdv` = 0 WHERE `pID` = %d", string, AccountData[playerid][pID]);
					mysql_pquery(g_SQL, string);

					ShowTDN(playerid, NOTIFICATION_INFO, "Advertisement Messages ~g~tidak aktif.");
				}
			}
		}
		case 5: //TogAdmCmd
		{
			switch(ToggleInfo[playerid][TogAdmCmd])
			{
				case false:
				{
					ToggleInfo[playerid][TogAdmCmd] = true;
					mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_TogAdmCmd` = 1 WHERE `pID` = %d", string, AccountData[playerid][pID]);
					mysql_pquery(g_SQL, string);

					ShowTDN(playerid, NOTIFICATION_INFO, "Admin Command Messages ~g~aktif.");
				}
				case true:
				{
					ToggleInfo[playerid][TogAdmCmd] = false;
					mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_TogAdmCmd` = 0 WHERE `pID` = %d", string, AccountData[playerid][pID]);
					mysql_pquery(g_SQL, string);

					ShowTDN(playerid, NOTIFICATION_INFO, "Admin Command Messages ~g~tidak aktif.");
				}
			}
		}
		// case 6: //toggle money cent dot
		// {
		// 	switch(ToggleInfo[playerid][TogMoneyTD])
		// 	{
		// 		case false:
		// 		{
		// 			ToggleInfo[playerid][TogMoneyTD] = true;
		// 			mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_TogMoneyTD` = 1 WHERE `pID` = %d", string, AccountData[playerid][pID]);
		// 			mysql_pquery(g_SQL, string);

		// 			ShowMoneyCentTD(playerid);
		// 			ShowTDN(playerid, NOTIFICATION_INFO, "Money Cent Dots Textdraw ~g~aktif.");
		// 		}
		// 		case true:
		// 		{
		// 			ToggleInfo[playerid][TogMoneyTD] = false;
		// 			mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Char_TogMoneyTD` = 0 WHERE `pID` = %d", string, AccountData[playerid][pID]);
		// 			mysql_pquery(g_SQL, string);

		// 			HideMoneyCentTD(playerid);
		// 			ShowTDN(playerid, NOTIFICATION_INFO, "Money Cent Dots Textdraw ~r~tidak aktif.");
		// 		}
		// 	}
		// }
		case 6: //TogBroadcast
		{
			switch(ToggleInfo[playerid][TogBroadcast])
			{
				case false:
				{
					ToggleInfo[playerid][TogBroadcast] = true;
					ShowTDN(playerid, NOTIFICATION_INFO, "Broadcast status ~g~aktif.");

					CallRemoteFunction("UpdatePlayerListeningCast", "id", playerid, 1);
				}
				case true:
				{
					ToggleInfo[playerid][TogBroadcast] = false;
					ShowTDN(playerid, NOTIFICATION_INFO, "Broadcast status ~r~tidak aktif.");

					CallRemoteFunction("UpdatePlayerListeningCast", "id", playerid, 0);
				}
			}
		}
	}
	return 1;
}

Dialog:QueueAsks(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(listitem == -1)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih pertanyaan!");
	
	static
		id,
		otherid;

	id = PlayerListitem[playerid][listitem];

	if(Iter_Contains(Asks, id))
    {
		otherid = AskData[id][askPlayer];

		static tstr[64], lstr[512 + 512];

		if(!IsPlayerConnected(otherid))
		{
			Ask_Remove(id);
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut telah keluar dari server!");
		}

		AccountData[playerid][pTempSQLFactMemberID] = id;

		format(tstr, sizeof(tstr), "Ask ID: #%d", id);
		format(lstr,sizeof(lstr),""WHITE"Nama Pemain: "YELLOW"%s\n"WHITE"Nama UCP: "YELLOW"%s\n"WHITE"Pertanyaan: "CYAN"%s\n"WHITE"Jawaban: "GREEN"(input below)", AccountData[otherid][pName], AccountData[otherid][pUCP], AskData[id][askText]);
		Dialog_Show(playerid, "AnswerAsks", DIALOG_STYLE_INPUT,tstr,lstr,"Jawab","Tutup");
	}
	return 1;
}

Dialog:AnswerAsks(playerid, response, listitem, inputtext[])
{
	static string[1524], counting, id;
	counting = 0;
	id = AccountData[playerid][pTempSQLFactMemberID];
	if(!response)
	{
		format(string, sizeof(string), "#ID\tDetail Pemain\tPertanyaan\n");

		foreach(new i : Asks)
		{
			if(strlen(AskData[i][askText]) > 64)
				format(string,sizeof(string), "%s#%d\t%s [%s] (%d)\t%.64s...\n", string, i, AccountData[AskData[i][askPlayer]][pName], AccountData[AskData[i][askPlayer]][pUCP], AskData[i][askPlayer], AskData[i][askText]);
			else
				format(string,sizeof(string), "%s#%d\t%s [%s] (%d)\t%s\n", string, i, AccountData[AskData[i][askPlayer]][pName], AccountData[AskData[i][askPlayer]][pUCP], AskData[i][askPlayer], AskData[i][askText]);

			PlayerListitem[playerid][counting++] = i;
		}

		if(counting == 0)
			ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada daftar pertanyaan!");
		else
			Dialog_Show(playerid, "QueueAsks", DIALOG_STYLE_TABLIST_HEADERS,"{DA9100}Pahlawan Roleplay "WHITE"- Daftar Asks",string,"Cek","Tutup");
		return 1;
	}

	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");

	if(!IsPlayerConnected(AskData[id][askPlayer]))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut telah keluar dari server!");

	if(strfind(inputtext, "%", true) != -1 || strfind(inputtext, "#", true) != -1)  return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memasukkan tanda persen!");

	AccountData[AskData[id][askPlayer]][pAskTime] = 0;
	SendStaffMessage(X11_YELLOW, "(Jawab #%d) %s menjawab %s (%d)", id, AccountData[playerid][pAdminname], AccountData[AskData[id][askPlayer]][pName], AskData[id][askPlayer]);
    SendStaffMessage(X11_YELLOW, "> %s", inputtext);
	SendClientMessageEx(AskData[id][askPlayer], X11_YELLOW, "(Jawaban) %s telah menjawab pertanyaan yang anda ajukan.", AccountData[playerid][pAdminname]);
    SendClientMessageEx(AskData[id][askPlayer], X11_YELLOW, "(Pesan) %s", inputtext);
	Ask_Remove(id);

	format(string, sizeof(string), "#ID\tDetail Pemain\tPertanyaan\n");

	foreach(new i : Asks)
	{
		if(strlen(AskData[i][askText]) > 64)
			format(string,sizeof(string), "%s#%d\t%s [%s] (%d)\t%.64s...\n", string, i, AccountData[AskData[i][askPlayer]][pName], AccountData[AskData[i][askPlayer]][pUCP], AskData[i][askPlayer], AskData[i][askText]);
		else
			format(string,sizeof(string), "%s#%d\t%s [%s] (%d)\t%s\n", string, i, AccountData[AskData[i][askPlayer]][pName], AccountData[AskData[i][askPlayer]][pUCP], AskData[i][askPlayer], AskData[i][askText]);

		PlayerListitem[playerid][counting++] = i;
	}

	if(counting == 0)
		ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada daftar pertanyaan!");
	else
		Dialog_Show(playerid, "QueueAsks", DIALOG_STYLE_TABLIST_HEADERS,"{DA9100}Pahlawan Roleplay "WHITE"- Daftar Asks",string,"Cek","Tutup");
	return 1;
}

Dialog:QueueReports(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(listitem == -1)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih laporan!");

	static id, otherid;
	id = PlayerListitem[playerid][listitem];
	otherid = ReportData[id][rPlayer];

	static tstr[64], lstr[512 + 512];

	if(!IsPlayerConnected(otherid))
	{
		Report_Remove(id);
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut telah keluar dari server!");
	}

	AccountData[playerid][pTempSQLFactMemberID] = id;
	
	format(tstr, sizeof(tstr), "Report ID: #%d", id);
	format(lstr,sizeof(lstr),""WHITE"Nama Pemain: "YELLOW"%s\n"WHITE"Nama UCP: "YELLOW"%s\n"WHITE"Laporan: "ORANGERED"%s", AccountData[otherid][pName], AccountData[otherid][pUCP], ReportData[id][rText]);

	if(AccountData[playerid][pAdmin] > 1) Dialog_Show(playerid, "RespondReports", DIALOG_STYLE_INPUT,tstr,lstr, "Jawab", "Tutup");
	else Dialog_Show(playerid, "DialogUnused", DIALOG_STYLE_INPUT,tstr,lstr, "Tutup", "");
	return 1;
}

Dialog:RespondReports(playerid, response, listitem, inputtext[])
{
	static string[1524], counting, id;
	counting = 0;
	id = AccountData[playerid][pTempSQLFactMemberID];
	if(!response) 
	{
		format(string,sizeof(string),"#ID\tDetail Pemain\tLaporan\n");
		foreach(new i : Reports)
		{
			if(strlen(ReportData[i][rText]) > 64)
				format(string,sizeof(string), "%s#%d\t%s [%s] (%d)\t%.64s...\n", string, i, AccountData[ReportData[i][rPlayer]][pName], AccountData[ReportData[i][rPlayer]][pUCP], ReportData[i][rPlayer], ReportData[i][rText]);
			else
				format(string,sizeof(string), "%s#%d\t%s [%s] (%d)\t%s\n", string, i, AccountData[ReportData[i][rPlayer]][pName], AccountData[ReportData[i][rPlayer]][pUCP], ReportData[i][rPlayer], ReportData[i][rText]);

			PlayerListitem[playerid][counting++] = i;
		}

		if(counting == 0)
			ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada daftar laporan!");
		else
			Dialog_Show(playerid, "QueueReports", DIALOG_STYLE_TABLIST_HEADERS,"{DA9100}Pahlawan Roleplay "WHITE"- Daftar Reports",string,"Cek","Tutup");
		return 1;
	}

	if(!IsPlayerConnected(ReportData[id][rPlayer])) 
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut telah keluar dari server!");
	
	if(strfind(inputtext, "%", true) != -1 || strfind(inputtext, "#", true) != -1)  return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memasukkan tanda persen!");
	
	AccountData[ReportData[id][rPlayer]][pReportTime] = 0;
	SendStaffMessage(X11_RED, "(Respon #%d) %s telah menanggapi laporan %s (%d)", id, AccountData[playerid][pAdminname], AccountData[ReportData[id][rPlayer]][pName], ReportData[id][rPlayer]);
	SendClientMessageEx(ReportData[id][rPlayer], X11_RED, "(Report) %s telah menanggapi laporan anda.", AccountData[playerid][pAdminname]);
	if(!isnull(inputtext))
	{
		SendClientMessageEx(ReportData[id][rPlayer], X11_RED, "(Pesan) %s", inputtext);
	}
	Report_Remove(id);

	format(string,sizeof(string),"#ID\tDetail Pemain\tLaporan\n");

	foreach(new i : Reports)
	{
		if(strlen(ReportData[i][rText]) > 64)
			format(string,sizeof(string), "%s#%d\t%s [%s] (%d)\t%.64s...\n", string, i, AccountData[ReportData[i][rPlayer]][pName], AccountData[ReportData[i][rPlayer]][pUCP], ReportData[i][rPlayer], ReportData[i][rText]);
		else
			format(string,sizeof(string), "%s#%d\t%s [%s] (%d)\t%s\n", string, i, AccountData[ReportData[i][rPlayer]][pName], AccountData[ReportData[i][rPlayer]][pUCP], ReportData[i][rPlayer], ReportData[i][rText]);

		PlayerListitem[playerid][counting++] = i;
	}

	if(counting == 0)
		ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada daftar laporan!");
	else
		Dialog_Show(playerid, "QueueReports", DIALOG_STYLE_TABLIST_HEADERS,"{DA9100}Pahlawan Roleplay "WHITE"- Daftar Reports",string,"Cek","Tutup");
	return 1;
}

//-------------[ Player Gun Position ]-----------
Dialog:GunEditBone(playerid, response, listitem, inputtext[])
{
	if(!response) 
	{
		EditingWeapon[playerid] = 0;
		return 1;
	}
	if(listitem == -1 || listitem > 17)
	{
		EditingWeapon[playerid] = 0;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid bone ID, mohon pilih ulang!");
	}
	static weaponid, weaponname[18], string[1254];
	weaponid = EditingWeapon[playerid];

	if(GetPlayerWeaponEx(playerid) != weaponid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak meemgang senjata tersebut!");

	GetWeaponName(weaponid, weaponname, sizeof(weaponname));
	new enum_index = GetWeaponIndex(weaponid);
	GunEdit[playerid][enum_index][Bone] = listitem + 1;

	ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil mengganti bone untuk senjata %s.", weaponname));
	
	mysql_format(g_SQL, string, sizeof(string), "UPDATE `gunpos` SET `PosX_0` = '%.3f', `PosY_0` = '%.3f', `PosZ_0` = '%.3f', `RotX_0` = '%.3f', `RotY_0` = '%.3f', `RotZ_0` = '%.3f', `Bone_0` = %d, `Hidden_0` = %d, `Tint_0` = %d, `PosX_1` = '%.3f', `PosY_1` = '%.3f', `PosZ_1` = '%.3f', `RotX_1` = '%.3f', `RotY_1` = '%.3f', `RotZ_1` = '%.3f', `Bone_1` = %d, `Hidden_1` = %d, `Tint_1` = %d, \
	`PosX_2` = '%.3f', `PosY_2` = '%.3f', `PosZ_2` = '%.3f', `RotX_2` = '%.3f', `RotY_2` = '%.3f', `RotZ_2` = '%.3f', `Bone_2` = %d, `Hidden_2` = %d, `Tint_2` = %d, `PosX_3` = '%.3f', `PosY_3` = '%.3f', `PosZ_3` = '%.3f', `RotX_3` = '%.3f', `RotY_3` = '%.3f', `RotZ_3` = '%.3f', `Bone_3` = %d, `Hidden_3` = %d, `Tint_3` = %d, \
	`PosX_4` = '%.3f', `PosY_4` = '%.3f', `PosZ_4` = '%.3f', `RotX_4` = '%.3f', `RotY_4` = '%.3f', `RotZ_4` = '%.3f', `Bone_4` = %d, `Hidden_4` = %d, `Tint_4` = %d WHERE `Owner` = %d", GunEdit[playerid][0][Position][0], GunEdit[playerid][0][Position][1], GunEdit[playerid][0][Position][2], GunEdit[playerid][0][Position][3], GunEdit[playerid][0][Position][4], GunEdit[playerid][0][Position][5], GunEdit[playerid][0][Bone], GunEdit[playerid][0][Hidden], GunEdit[playerid][0][WeaponTint],
	GunEdit[playerid][1][Position][0], GunEdit[playerid][1][Position][1], GunEdit[playerid][1][Position][2], GunEdit[playerid][1][Position][3], GunEdit[playerid][1][Position][4], GunEdit[playerid][1][Position][5], GunEdit[playerid][1][Bone], GunEdit[playerid][1][Hidden], GunEdit[playerid][1][WeaponTint],
	GunEdit[playerid][2][Position][0], GunEdit[playerid][2][Position][1], GunEdit[playerid][2][Position][2], GunEdit[playerid][2][Position][3], GunEdit[playerid][2][Position][4], GunEdit[playerid][2][Position][5], GunEdit[playerid][2][Bone], GunEdit[playerid][2][Hidden], GunEdit[playerid][2][WeaponTint],
	GunEdit[playerid][3][Position][0], GunEdit[playerid][3][Position][1], GunEdit[playerid][3][Position][2], GunEdit[playerid][3][Position][3], GunEdit[playerid][3][Position][4], GunEdit[playerid][3][Position][5], GunEdit[playerid][3][Bone], GunEdit[playerid][3][Hidden], GunEdit[playerid][3][WeaponTint],
	GunEdit[playerid][4][Position][0], GunEdit[playerid][4][Position][1], GunEdit[playerid][4][Position][2], GunEdit[playerid][4][Position][3], GunEdit[playerid][4][Position][4], GunEdit[playerid][4][Position][5], GunEdit[playerid][4][Bone], GunEdit[playerid][4][Hidden], GunEdit[playerid][4][WeaponTint], AccountData[playerid][pID]);
	mysql_pquery(g_SQL, string);

	EditingWeapon[playerid] = 0;
	return 1;
}

Dialog:GunEditTint(playerid, response, listitem, inputtext[])
{
	if(!response) 
	{
		EditingWeapon[playerid] = 0;
		return 1;
	}
	
	if(listitem == -1 || listitem > 11)
	{
		EditingWeapon[playerid] = 0;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih warna apapun!");
	}

	static weaponid, weaponname[18];
	weaponid = EditingWeapon[playerid];

	if(GetPlayerWeaponEx(playerid) != weaponid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak meemgang senjata tersebut!");

	GetWeaponName(weaponid, weaponname, sizeof(weaponname));
	new enum_index = GetWeaponIndex(weaponid);

	EditingWeapon[playerid] = 0;
	GunEdit[playerid][enum_index][WeaponTint] = listitem;
	SetWeapons(playerid);

	static string[1254];
	mysql_format(g_SQL, string, sizeof(string), "UPDATE `gunpos` SET `PosX_0` = '%.3f', `PosY_0` = '%.3f', `PosZ_0` = '%.3f', `RotX_0` = '%.3f', `RotY_0` = '%.3f', `RotZ_0` = '%.3f', `Bone_0` = %d, `Hidden_0` = %d, `Tint_0` = %d, `PosX_1` = '%.3f', `PosY_1` = '%.3f', `PosZ_1` = '%.3f', `RotX_1` = '%.3f', `RotY_1` = '%.3f', `RotZ_1` = '%.3f', `Bone_1` = %d, `Hidden_1` = %d, `Tint_1` = %d, \
	`PosX_2` = '%.3f', `PosY_2` = '%.3f', `PosZ_2` = '%.3f', `RotX_2` = '%.3f', `RotY_2` = '%.3f', `RotZ_2` = '%.3f', `Bone_2` = %d, `Hidden_2` = %d, `Tint_2` = %d, `PosX_3` = '%.3f', `PosY_3` = '%.3f', `PosZ_3` = '%.3f', `RotX_3` = '%.3f', `RotY_3` = '%.3f', `RotZ_3` = '%.3f', `Bone_3` = %d, `Hidden_3` = %d, `Tint_3` = %d, \
	`PosX_4` = '%.3f', `PosY_4` = '%.3f', `PosZ_4` = '%.3f', `RotX_4` = '%.3f', `RotY_4` = '%.3f', `RotZ_4` = '%.3f', `Bone_4` = %d, `Hidden_4` = %d, `Tint_4` = %d WHERE `Owner` = %d", GunEdit[playerid][0][Position][0], GunEdit[playerid][0][Position][1], GunEdit[playerid][0][Position][2], GunEdit[playerid][0][Position][3], GunEdit[playerid][0][Position][4], GunEdit[playerid][0][Position][5], GunEdit[playerid][0][Bone], GunEdit[playerid][0][Hidden], GunEdit[playerid][0][WeaponTint],
	GunEdit[playerid][1][Position][0], GunEdit[playerid][1][Position][1], GunEdit[playerid][1][Position][2], GunEdit[playerid][1][Position][3], GunEdit[playerid][1][Position][4], GunEdit[playerid][1][Position][5], GunEdit[playerid][1][Bone], GunEdit[playerid][1][Hidden], GunEdit[playerid][1][WeaponTint],
	GunEdit[playerid][2][Position][0], GunEdit[playerid][2][Position][1], GunEdit[playerid][2][Position][2], GunEdit[playerid][2][Position][3], GunEdit[playerid][2][Position][4], GunEdit[playerid][2][Position][5], GunEdit[playerid][2][Bone], GunEdit[playerid][2][Hidden], GunEdit[playerid][2][WeaponTint],
	GunEdit[playerid][3][Position][0], GunEdit[playerid][3][Position][1], GunEdit[playerid][3][Position][2], GunEdit[playerid][3][Position][3], GunEdit[playerid][3][Position][4], GunEdit[playerid][3][Position][5], GunEdit[playerid][3][Bone], GunEdit[playerid][3][Hidden], GunEdit[playerid][3][WeaponTint],
	GunEdit[playerid][4][Position][0], GunEdit[playerid][4][Position][1], GunEdit[playerid][4][Position][2], GunEdit[playerid][4][Position][3], GunEdit[playerid][4][Position][4], GunEdit[playerid][4][Position][5], GunEdit[playerid][4][Bone], GunEdit[playerid][4][Hidden], GunEdit[playerid][4][WeaponTint], AccountData[playerid][pID]);
	mysql_pquery(g_SQL, string);

	ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil mengganti warna senjata %s.", weaponname));
	return 1;
}

//------------------ [Sidejob] --------------------------//
Dialog:SidejobMowing(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		RemovePlayerFromVehicle(playerid);
		SetTimerEx("RespawnPV", 1500, false, "d", SavingVehID[playerid]);
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		return 1;
	}
	
	if(!GetEngineStatus(SavingVehID[playerid]) && !AccountData[playerid][pTurningEngine])
	{
		AccountData[playerid][pTurningEngine] = true;
		SetTimerEx("EngineStatus", 2000, false, "id", playerid, SavingVehID[playerid]);
	}
	StartMowingSidejob(playerid);
	return 1;
}

Dialog:SidejobSweeper(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		RemovePlayerFromVehicle(playerid);
		SetTimerEx("RespawnPV", 1500, false, "d", SavingVehID[playerid]);
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		return 1;
	}
	
	if(!GetEngineStatus(SavingVehID[playerid]) && !AccountData[playerid][pTurningEngine])
	{
		AccountData[playerid][pTurningEngine] = true;
		SetTimerEx("EngineStatus", 2000, false, "id", playerid, SavingVehID[playerid]);
	}
	StartSweeperSidejob(playerid);
	return 1;
}

Dialog:SidejobForklift(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		RemovePlayerFromVehicle(playerid);
		SetTimerEx("RespawnPV", 1500, false, "d", SavingVehID[playerid]);
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		return 1;
	}
	
	if(!GetEngineStatus(SavingVehID[playerid]) && !AccountData[playerid][pTurningEngine])
	{
		AccountData[playerid][pTurningEngine] = true;
		SetTimerEx("EngineStatus", 2000, false, "id", playerid, SavingVehID[playerid]);
	}
	StartForkliftSidejob(playerid);
	return 1;
}

Dialog:SidejobTrashCollector(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		RemovePlayerFromVehicle(playerid);
		SetTimerEx("RespawnPV", 1500, false, "d", SavingVehID[playerid]);
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		return 1;
	}
	
	if(!GetEngineStatus(SavingVehID[playerid]) && !AccountData[playerid][pTurningEngine])
	{
		AccountData[playerid][pTurningEngine] = true;
		SetTimerEx("EngineStatus", 2000, false, "id", playerid, SavingVehID[playerid]);
	}
	StartTrashCollectorSidejob(playerid);
	return 1;
}

Dialog:MakeVehPlate(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");
	if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Masukkan hanya angka!");

	new carid = strval(inputtext);
	
	if(!IsValidVehicle(carid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut tidak terspawn!");

	foreach(new veh : PvtVehicles)
	{
		if(PlayerVehicle[veh][pVehPhysic] == carid)
		{
			if(strcmp(PlayerVehicle[veh][pVehPlate], "-", false))
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut sudah memiliki plat!");

			new	tmswk[64],
				query[212],
				xd1 = random(sizeof(g_Alphabet)),
				xd2 = random(sizeof(g_Alphabet)),
				xd3 = random(sizeof(g_Alphabet));

			format(tmswk, sizeof(tmswk), "BK %d%d%d%d %s%s%s", random(10), random(10), random(10), random(10), g_Alphabet[xd1], g_Alphabet[xd2], g_Alphabet[xd3]);
			mysql_format(g_SQL, query, sizeof(query), "SELECT `PVeh_Plate` FROM `player_vehicles` WHERE `PVeh_Plate`='%e'", tmswk);
			mysql_pquery(g_SQL, query, "MakeNewPlateCreate", "ids", playerid, veh, tmswk);
		}
	}
	return 1;
}

// Bagasi
Dialog:VehicleStorage(playerid, response, listitem, inputtext[])
{
	if(AccountData[playerid][pTempVehIterID] == -1) 
	{
		AccountData[playerid][pMenuShowed] = false;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang mengecek bagasi!");
	}

	static vehid;
	vehid = AccountData[playerid][pTempVehIterID];

	if(!response) 
	{
		AccountData[playerid][pMenuShowed] = false;
		SwitchVehicleBoot(PlayerVehicle[vehid][pVehPhysic], false);
		AccountData[playerid][pTempVehIterID] = -1;
		return 1;
	}

	if(!IsValidVehicle(PlayerVehicle[vehid][pVehPhysic]))
	{
		AccountData[playerid][pMenuShowed] = false;
		SwitchVehicleBoot(PlayerVehicle[vehid][pVehPhysic], false);
		AccountData[playerid][pTempVehIterID] = -1;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut tidak ada di dalam server!");
	}

	if(!IsPlayerNearVehicle(playerid, PlayerVehicle[vehid][pVehPhysic], 3.5)) 
	{
		AccountData[playerid][pMenuShowed] = false;
		SwitchVehicleBoot(PlayerVehicle[vehid][pVehPhysic], false);
		AccountData[playerid][pTempVehIterID] = -1;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut tidak dekat dengan anda!");
	}

	switch(listitem)
	{
		case 0: //deposit
		{
			new string[1218], count;
			count = 0;
			format(string, sizeof(string), "Nama Item\tJumlah\tBerat (%.3f/%d kg)\n", GetBagasiTotalWeightFloat(vehid), GetVehicleWeight(PlayerVehicle[vehid][pVehModelID]));
			for(new index; index < MAX_INVENTORY; index++)
			{
				if(InventoryData[playerid][index][invExists])
				{
					for(new i; i < sizeof(g_aInventoryItems); i ++) if (!strcmp(g_aInventoryItems[i][e_InventoryItem], InventoryData[playerid][index][invItem], true))
					{
						if (i % 2 == 0) {
							format(string, sizeof(string), "%s"WHITE"%s\t"WHITE"%d\t"WHITE"-\n", string, InventoryData[playerid][index][invItem], InventoryData[playerid][index][invQuantity]);
						} else {
							format(string, sizeof(string), "%s"GRAY"%s\t"GRAY"%d\t"GRAY"-\n", string, InventoryData[playerid][index][invItem], InventoryData[playerid][index][invQuantity]);
						}
						PlayerListitem[playerid][count++] = index;
					}
				}
			}

			if(count == 0)
			{
				Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, sprintf("Bagasi Kendaraan "YELLOW"%s {DA9100}- %s", GetVehicleModelName(PlayerVehicle[vehid][pVehModelID]), PlayerVehicle[vehid][pVehPlate]), 
				"Anda tidak memiliki barang yang dapat disimpan!", "Tutup", "");
			}
			else
			{
				Dialog_Show(playerid, "VehicleStorageDeposit", DIALOG_STYLE_TABLIST_HEADERS, sprintf("Bagasi Kendaraan "YELLOW"%s {DA9100}- %s", GetVehicleModelName(PlayerVehicle[vehid][pVehModelID]), PlayerVehicle[vehid][pVehPlate]), string, "Pilih", "Batal");
			}
		}
		case 1: //withdraw
		{
			index_pagination[playerid] = 0;
			Vehicle_ShowBagasi(playerid, vehid);
		}
	}
	return 1;
}

Dialog:VehicleStorageDeposit(playerid, response, listitem, inputtext[])
{
	if(AccountData[playerid][pTempVehIterID] == -1) 
	{
		AccountData[playerid][pMenuShowed] = false;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang mengecek bagasi!");
	}
	static vehid;
	vehid = AccountData[playerid][pTempVehIterID];

	if(!response) 
	{
		AccountData[playerid][pMenuShowed] = false;
		SwitchVehicleBoot(PlayerVehicle[vehid][pVehPhysic], false);
		AccountData[playerid][pTempVehIterID] = -1;
		return 1;
	}

	if(listitem == -1)
	{
		AccountData[playerid][pMenuShowed] = false;
		SwitchVehicleBoot(PlayerVehicle[vehid][pVehPhysic], false);
		AccountData[playerid][pTempVehIterID] = -1;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih apapun!");
	}

	if(!IsValidVehicle(PlayerVehicle[vehid][pVehPhysic]))
	{
		AccountData[playerid][pMenuShowed] = false;
		SwitchVehicleBoot(PlayerVehicle[vehid][pVehPhysic], false);
		AccountData[playerid][pTempVehIterID] = -1;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut tidak ada di dalam server!");
	}

	if(!IsPlayerNearVehicle(playerid, PlayerVehicle[vehid][pVehPhysic], 3.5)) 
	{
		AccountData[playerid][pMenuShowed] = false;
		SwitchVehicleBoot(PlayerVehicle[vehid][pVehPhysic], false);
		AccountData[playerid][pTempVehIterID] = -1;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut tidak dekat dengan anda!");
	}

	AccountData[playerid][pTempValue] = listitem;

	if(!strcmp(InventoryData[playerid][PlayerListitem[playerid][listitem]][invItem], "Changename Card")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menyimpan Changename Card ke penyimpanan manapun!");
	if(!strcmp(InventoryData[playerid][PlayerListitem[playerid][listitem]][invItem], "Hunt Ammo"))
	{
		if(IsPlayerHunting[playerid])
		{
			ResetWeapon(playerid, 34);
			if(PlayerHasItem(playerid, "Hunt Ammo"))
			{
				GivePlayerWeaponEx(playerid, 34, Inventory_Count(playerid, "Hunt Ammo"), WEAPON_TYPE_PLAYER);
			}
		}
	}

	static string[528];
	format(string, sizeof(string), ""WHITE"Anda akan menyimpan item:\nNama: "CYAN"%s\n"WHITE"Jumlah di tas: "YELLOW"%d\n"WHITE"Mohon masukkan jumlah yang ingin disimpan:", InventoryData[playerid][PlayerListitem[playerid][listitem]][invItem], InventoryData[playerid][PlayerListitem[playerid][listitem]][invQuantity]);
	Dialog_Show(playerid, "VehicleStorageIn", DIALOG_STYLE_INPUT, sprintf("Bagasi Kendaraan "YELLOW"%s {DA9100}- %s", GetVehicleModelName(PlayerVehicle[vehid][pVehModelID]), PlayerVehicle[vehid][pVehPlate]), 
	string, "Input", "Batal");
	return 1;
}

Dialog:VehicleStorageIn(playerid, response, listitem, inputtext[])
{
	if(AccountData[playerid][pTempVehIterID] == -1) 
	{
		AccountData[playerid][pMenuShowed] = false;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang mengecek bagasi!");
	}
	
	static vehid;
	vehid = AccountData[playerid][pTempVehIterID];

	if(!response) 
	{
		AccountData[playerid][pMenuShowed] = false;
		SwitchVehicleBoot(PlayerVehicle[vehid][pVehPhysic], false);
		AccountData[playerid][pTempVehIterID] = -1;
		AccountData[playerid][pTempValue] = -1;
		return 1;
	}

	if(AccountData[playerid][pTempValue] == -1)
	{
		AccountData[playerid][pMenuShowed] = false;
		SwitchVehicleBoot(PlayerVehicle[vehid][pVehPhysic], false);
		AccountData[playerid][pTempVehIterID] = -1;
		AccountData[playerid][pTempValue] = -1;
		ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item apapun!");
		return 1;
	}

	if(!IsValidVehicle(PlayerVehicle[vehid][pVehPhysic]))
	{
		AccountData[playerid][pMenuShowed] = false;
		SwitchVehicleBoot(PlayerVehicle[vehid][pVehPhysic], false);
		AccountData[playerid][pTempVehIterID] = -1;
		AccountData[playerid][pTempValue] = -1;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut tidak ada di dalam server!");
	}

	if(!IsPlayerNearVehicle(playerid, PlayerVehicle[vehid][pVehPhysic], 3.5)) 
	{
		AccountData[playerid][pMenuShowed] = false;
		SwitchVehicleBoot(PlayerVehicle[vehid][pVehPhysic], false);
		AccountData[playerid][pTempVehIterID] = -1;
		AccountData[playerid][pTempValue] = -1;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut tidak dekat dengan anda!");
	}
	
	static string[1028], id;
	id = AccountData[playerid][pTempValue];

	if(isnull(inputtext)) 
	{
		AccountData[playerid][pMenuShowed] = true;
		format(string, sizeof(string), ""WHITE"Anda akan menyimpan item:\nNama: "CYAN"%s\n"WHITE"Jumlah di tas: "YELLOW"%d\n"WHITE"Error: Tidak dapat dikosongkan!\nPlease enter the quantity you want to store:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
		Dialog_Show(playerid, "VehicleStorageIn", DIALOG_STYLE_INPUT, sprintf("Bagasi Kendaraan "YELLOW"%s {DA9100}- %s", GetVehicleModelName(PlayerVehicle[vehid][pVehModelID]), PlayerVehicle[vehid][pVehPlate]), 
		string, "Input", "Batal");
		return 1;
	}

	if(!IsNumericEx(inputtext))
	{
		AccountData[playerid][pMenuShowed] = true;
		format(string, sizeof(string), ""WHITE"Anda akan menyimpan item:\nNama: "CYAN"%s\n"WHITE"Jumlah di tas: "YELLOW"%d\n"WHITE"Error: Please enter only numbers!\nPlease enter the quantity you want to store:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
		Dialog_Show(playerid, "VehicleStorageIn", DIALOG_STYLE_INPUT, sprintf("Bagasi Kendaraan "YELLOW"%s {DA9100}- %s", GetVehicleModelName(PlayerVehicle[vehid][pVehModelID]), PlayerVehicle[vehid][pVehPlate]), 
		string, "Input", "Batal");
		return 1;
	}

	if(strval(inputtext) < 1 || strval(inputtext) > InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity])
	{
		AccountData[playerid][pMenuShowed] = true;
		format(string, sizeof(string), ""WHITE"Anda akan menyimpan item:\nNama: "CYAN"%s\n"WHITE"Jumlah di tas: "YELLOW"%d\n"WHITE"Error: Jumlah tidak valid!\nPlease enter the quantity you want to store:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
		Dialog_Show(playerid, "VehicleStorageIn", DIALOG_STYLE_INPUT, sprintf("Bagasi Kendaraan "YELLOW"%s {DA9100}- %s", GetVehicleModelName(PlayerVehicle[vehid][pVehModelID]), PlayerVehicle[vehid][pVehPlate]), 
		string, "Input", "Batal");
		return 1;
	}

	static quantity;
	quantity = strval(inputtext);
	
	SwitchVehicleBoot(PlayerVehicle[vehid][pVehPhysic], false);

	static Float:countingtotalweight;
	countingtotalweight = GetBagasiTotalWeightFloat(vehid) + float(quantity * GetItemWeight(InventoryData[playerid][PlayerListitem[playerid][id]][invItem]))/1000;
	if(countingtotalweight > GetVehicleWeight(PlayerVehicle[vehid][pVehModelID])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Bagasi anda telah penuh!");

	SendRPMeAboveHead(playerid, sprintf("Menyimpan %dx %s ke dalam bagasi %s.", quantity, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], GetVehicleModelName(PlayerVehicle[vehid][pVehModelID])));

	mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `vehicle_bagasi` WHERE `Veh_DBID`=%d AND `Item` = '%e'", PlayerVehicle[vehid][pVehID], InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
	mysql_query(g_SQL, string);

	static rows;
	rows = cache_num_rows();
	if(rows > 0)
	{
		for(new x; x < MAX_BAGASI_ITEMS; ++x)
		{
			if(VehicleBagasi[vehid][x][vehicleBagasiExists] && VehicleBagasi[vehid][x][vehicleBagasiVDBID] == PlayerVehicle[vehid][pVehID] && !strcmp(VehicleBagasi[vehid][x][vehicleBagasiTemp], InventoryData[playerid][PlayerListitem[playerid][id]][invItem], true))
			{
				VehicleBagasi[vehid][x][vehicleBagasiQuant] += quantity;
			}
		}
		mysql_format(g_SQL, string, sizeof(string), "UPDATE `vehicle_bagasi` SET `Quantity` = `Quantity` + %d WHERE `Veh_DBID` = %d AND `Item` = '%e'", quantity, PlayerVehicle[vehid][pVehID], InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
		mysql_pquery(g_SQL, string);

		ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyimpan item tersebut.");
	}
	else
	{
		for(new x; x < MAX_BAGASI_ITEMS; ++x)
		{
			if(!VehicleBagasi[vehid][x][vehicleBagasiExists]) 
			{
				VehicleBagasi[vehid][x][vehicleBagasiExists] = true;
				VehicleBagasi[vehid][x][vehicleBagasiVDBID] =  PlayerVehicle[vehid][pVehID];
				strcopy(VehicleBagasi[vehid][x][vehicleBagasiTemp], InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
				VehicleBagasi[vehid][x][vehicleBagasiModel] = InventoryData[playerid][PlayerListitem[playerid][id]][invModel];
				VehicleBagasi[vehid][x][vehicleBagasiQuant] = quantity;

				mysql_format(g_SQL, string, sizeof(string), "INSERT INTO `vehicle_bagasi` SET `Veh_DBID`=%d, `Item`='%e', `Model`=%d, `Quantity`=%d", PlayerVehicle[vehid][pVehID], InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invModel], quantity);
				mysql_pquery(g_SQL, string, "OnBagasiDeposited", "iid", playerid, vehid, x);

				break;
			}
		}
	}
	AccountData[playerid][pTempVehIterID] = -1;
	ShowItemBox(playerid, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], sprintf("Removed %dx", quantity), InventoryData[playerid][PlayerListitem[playerid][id]][invModel], 5);
	Inventory_Remove(playerid, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], quantity);
	return 1;
}

Dialog:VehicleStorageWithdraw(playerid, response, listitem, inputtext[])
{
    if (AccountData[playerid][pTempVehIterID] == -1) 
    {
        AccountData[playerid][pMenuShowed] = false;
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang mengecek bagasi!");
    }

    static vehid;
    vehid = AccountData[playerid][pTempVehIterID];

    if (!response) 
    {
        AccountData[playerid][pMenuShowed] = false;
        SwitchVehicleBoot(PlayerVehicle[vehid][pVehPhysic], false);
        AccountData[playerid][pTempVehIterID] = -1;
        return 1;
    }

    if (listitem == -1) 
    {
        AccountData[playerid][pMenuShowed] = false;
        SwitchVehicleBoot(PlayerVehicle[vehid][pVehPhysic], false);
        AccountData[playerid][pTempVehIterID] = -1;
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item apapun!");
    }

    if (!strcmp(inputtext, ">> Selanjutnya", true)) 
    {
        index_pagination[playerid]++;
        Vehicle_ShowBagasi(playerid, vehid);
    } 
    else if (!strcmp(inputtext, "<< Sebelumnya", true)) 
    {
        index_pagination[playerid]--;
        if (index_pagination[playerid] < 0) {
            index_pagination[playerid] = 0;
        }
        Vehicle_ShowBagasi(playerid, vehid);
    }
    else 
    {
        if (PlayerListitem[playerid][listitem] == -1) 
        {
            AccountData[playerid][pMenuShowed] = false;
            SwitchVehicleBoot(PlayerVehicle[vehid][pVehPhysic], false);
            AccountData[playerid][pTempVehIterID] = -1;
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item apapun!");
        }

		AccountData[playerid][pTempValue] = listitem;
		
        static string[528];
        format(string, sizeof(string), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Mohon masukkan berapa jumlah yang ingin diambil:", VehicleBagasi[vehid][PlayerListitem[playerid][listitem]][vehicleBagasiTemp], VehicleBagasi[vehid][PlayerListitem[playerid][listitem]][vehicleBagasiQuant]);
        Dialog_Show(playerid, "VehicleStorageOut", DIALOG_STYLE_INPUT, sprintf("Bagasi Kendaraan "YELLOW"%s {DA9100}- %s", GetVehicleModelName(PlayerVehicle[vehid][pVehModelID]), PlayerVehicle[vehid][pVehPlate]), 
        string, "Input", "Batal");
    }

    return 1;
}

Dialog:VehicleStorageOut(playerid, response, listitem, inputtext[])
{
	if(AccountData[playerid][pTempVehIterID] == -1) 
	{
		AccountData[playerid][pMenuShowed] = false;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang mengecek bagasi!");
	}

	static vehid;
	vehid = AccountData[playerid][pTempVehIterID];

	if(!response) 
	{
		AccountData[playerid][pMenuShowed] = false;
		SwitchVehicleBoot(PlayerVehicle[vehid][pVehPhysic], false);
		AccountData[playerid][pTempVehIterID] = -1;
		return 1;
	}

	if(!IsValidVehicle(PlayerVehicle[vehid][pVehPhysic]))
	{
		AccountData[playerid][pMenuShowed] = false;
		SwitchVehicleBoot(PlayerVehicle[vehid][pVehPhysic], false);
		AccountData[playerid][pTempVehIterID] = -1;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut tidak ada di dalam server!");
	}

	if(!IsPlayerNearVehicle(playerid, PlayerVehicle[vehid][pVehPhysic], 3.5)) 
	{
		AccountData[playerid][pMenuShowed] = false;
		SwitchVehicleBoot(PlayerVehicle[vehid][pVehPhysic], false);
		AccountData[playerid][pTempVehIterID] = -1;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut tidak dekat dengan anda!");
	}

	static string[512], id;
	id = AccountData[playerid][pTempValue];
	if(isnull(inputtext)) 
	{
		AccountData[playerid][pMenuShowed] = true;
		format(string, sizeof(string), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Error: Tidak dapat dikosongkan!\nPlease enter the quantity you want to retrieve:", VehicleBagasi[vehid][PlayerListitem[playerid][id]][vehicleBagasiTemp], VehicleBagasi[vehid][PlayerListitem[playerid][id]][vehicleBagasiQuant]);
		Dialog_Show(playerid, "VehicleStorageOut", DIALOG_STYLE_INPUT, sprintf("Bagasi Kendaraan "YELLOW"%s {DA9100}- %s", GetVehicleModelName(PlayerVehicle[vehid][pVehModelID]), PlayerVehicle[vehid][pVehPlate]), 
		string, "Input", "Batal");
		return 1;
	}

	if(!IsNumericEx(inputtext))
	{
		AccountData[playerid][pMenuShowed] = true;
		format(string, sizeof(string), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Error: Please enter only numbers!\nPlease enter the quantity you want to retrieve:", VehicleBagasi[vehid][PlayerListitem[playerid][id]][vehicleBagasiTemp], VehicleBagasi[vehid][PlayerListitem[playerid][id]][vehicleBagasiQuant]);
		Dialog_Show(playerid, "VehicleStorageOut", DIALOG_STYLE_INPUT, sprintf("Bagasi Kendaraan "YELLOW"%s {DA9100}- %s", GetVehicleModelName(PlayerVehicle[vehid][pVehModelID]), PlayerVehicle[vehid][pVehPlate]), 
		string, "Input", "Batal");
		return 1;
	}

	if(strval(inputtext) < 1 || strval(inputtext) > VehicleBagasi[vehid][PlayerListitem[playerid][id]][vehicleBagasiQuant])
	{
		AccountData[playerid][pMenuShowed] = true;
		format(string, sizeof(string), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Error: Jumlah tidak valid!\nPlease enter the quantity you want to retrieve:", VehicleBagasi[vehid][PlayerListitem[playerid][id]][vehicleBagasiTemp], VehicleBagasi[vehid][PlayerListitem[playerid][id]][vehicleBagasiQuant]);
		Dialog_Show(playerid, "VehicleStorageOut", DIALOG_STYLE_INPUT, sprintf("Bagasi Kendaraan "YELLOW"%s {DA9100}- %s", GetVehicleModelName(PlayerVehicle[vehid][pVehModelID]), PlayerVehicle[vehid][pVehPlate]), 
		string, "Input", "Batal");
		return 1;
	}

	static quantity;
	quantity = strval(inputtext);

	SwitchVehicleBoot(PlayerVehicle[vehid][pVehPhysic], false);

	static Float:countingtotalweight;
	countingtotalweight = GetTotalWeightFloat(playerid) + float(quantity * GetItemWeight(VehicleBagasi[vehid][PlayerListitem[playerid][id]][vehicleBagasiTemp]))/1000;
	if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

	SendRPMeAboveHead(playerid, sprintf("Mengambil %dx %s dari bagasi %s.", quantity, VehicleBagasi[vehid][PlayerListitem[playerid][id]][vehicleBagasiTemp], GetVehicleModelName(PlayerVehicle[vehid][pVehModelID])));

	if(!strcmp(VehicleBagasi[vehid][PlayerListitem[playerid][id]][vehicleBagasiTemp], "Smartphone"))
	{
		mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `player_phones` WHERE `phoneOwner`=%d", AccountData[playerid][pID]);
		mysql_pquery(g_SQL, string, "OnPlayerBuySmartphone", "i", playerid);
	}
	else
	{
		Inventory_Add(playerid, VehicleBagasi[vehid][PlayerListitem[playerid][id]][vehicleBagasiTemp], VehicleBagasi[vehid][PlayerListitem[playerid][id]][vehicleBagasiModel], quantity);
	}

	ShowItemBox(playerid, VehicleBagasi[vehid][PlayerListitem[playerid][id]][vehicleBagasiTemp], sprintf("Received %dx", quantity), VehicleBagasi[vehid][PlayerListitem[playerid][id]][vehicleBagasiModel], 5);

	VehicleBagasi[vehid][PlayerListitem[playerid][id]][vehicleBagasiQuant] -= quantity;
	
	if(VehicleBagasi[vehid][PlayerListitem[playerid][id]][vehicleBagasiQuant] > 0)
	{
		mysql_format(g_SQL, string, sizeof(string), "UPDATE `vehicle_bagasi` SET `Quantity` = %d WHERE `ID`=%d", VehicleBagasi[vehid][PlayerListitem[playerid][id]][vehicleBagasiQuant], VehicleBagasi[vehid][PlayerListitem[playerid][id]][vehicleBagasiID]);
		mysql_pquery(g_SQL, string);
	}
	else
	{
		mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `vehicle_bagasi` WHERE `ID`=%d", VehicleBagasi[vehid][PlayerListitem[playerid][id]][vehicleBagasiID]);
		mysql_pquery(g_SQL, string);

		VehicleBagasi[vehid][PlayerListitem[playerid][id]][vehicleBagasiExists] = false;
		VehicleBagasi[vehid][PlayerListitem[playerid][id]][vehicleBagasiID] = 0;
		VehicleBagasi[vehid][PlayerListitem[playerid][id]][vehicleBagasiTemp][0] = EOS;
		VehicleBagasi[vehid][PlayerListitem[playerid][id]][vehicleBagasiModel] = 0;
		VehicleBagasi[vehid][PlayerListitem[playerid][id]][vehicleBagasiQuant] = 0;
	}
	AccountData[playerid][pMenuShowed] = false;
	AccountData[playerid][pTempVehIterID] = -1;
	return 1;
}

//-------- emote -------//
Dialog:EmoteList(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
	
	switch(listitem)
	{
		case 0:
		{
			static string[1524];
			if (!strlen(string)) {
				for(new i; i < sizeof(g_AnimDetails); i ++) {
					format(string, sizeof(string), "%s%s\n", string, g_AnimDetails[i][e_AnimationName]);
				}
			}
			return Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Emotes", string, "Tutup", "");
		}
		case 1:
		{
			static string[1524];
			if (!strlen(string)) {
				for(new i; i < sizeof(g_AnimPropDetails); i ++) {
					format(string, sizeof(string), "%s%s\n", string, g_AnimPropDetails[i][e_AnimationPropName]);
				}
			}
			return Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Emotes Property", string, "Tutup", "");
		}
		case 2:
		{
			static string[1524];
			if (!strlen(string)) 
			{
				for(new i; i < sizeof(g_AnimSharedName); i ++) 
				{
					format(string, sizeof(string), "%s%s\n", string, g_AnimSharedName[i]);
				}
			}
			return Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Emotes Shared", string, "Tutup", "");
		}
	}
	return 1;
}
//------------------------------------------------------//

Dialog:CheckWarns(playerid, response, listitem, inputtext[])
{
	if(!response) 
	{
		Temptargetid[playerid] = INVALID_PLAYER_ID;
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		return 1;
	}
	
	if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih riwayat peringatan apapun!");
	if(Temptargetid[playerid] == INVALID_PLAYER_ID && !IsPlayerConnected(Temptargetid[playerid]) && !AccountData[Temptargetid[playerid]][pSpawned])
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

	static frmxss[512], otherid;
	otherid = Temptargetid[playerid];
	switch(PlayerWarning[otherid][PlayerListitem[playerid][listitem]][warnType])
	{
		case 1:
		{
			format(frmxss, sizeof(frmxss), ""WHITE"Penerbit: "RED"%s\n\
			"WHITE"Type: "GREEN"[WARN]\n\
			"WHITE"Tanggal: "CYAN"%s\n\
			"WHITE"Alasan:\n\
			"AQUAMARINE"%s",
			PlayerWarning[otherid][PlayerListitem[playerid][listitem]][warnIssuer],
			PlayerWarning[otherid][PlayerListitem[playerid][listitem]][warnDateTime],
			PlayerWarning[otherid][PlayerListitem[playerid][listitem]][warnReason]);
		}
		case 2:
		{
			format(frmxss, sizeof(frmxss), ""WHITE"Penerbit: "RED"%s\n\
			"WHITE"Type: "YELLOW"[JAIL]\n\
			"WHITE"Tanggal: "CYAN"%s\n\
			"WHITE"Alasan:\n\
			"AQUAMARINE"%s",
			PlayerWarning[otherid][PlayerListitem[playerid][listitem]][warnIssuer],
			PlayerWarning[otherid][PlayerListitem[playerid][listitem]][warnDateTime],
			PlayerWarning[otherid][PlayerListitem[playerid][listitem]][warnReason]);
		}
		case 3:
		{
			format(frmxss, sizeof(frmxss), ""WHITE"Penerbit: "RED"%s\n\
			"WHITE"Type: "ORANGERED"[BAN]\n\
			"WHITE"Tanggal: "CYAN"%s\n\
			"WHITE"Alasan:\n\
			"AQUAMARINE"%s",
			PlayerWarning[otherid][PlayerListitem[playerid][listitem]][warnIssuer],
			PlayerWarning[otherid][PlayerListitem[playerid][listitem]][warnDateTime],
			PlayerWarning[otherid][PlayerListitem[playerid][listitem]][warnReason]);
		}
	}
	Dialog_Show(playerid, "CheckWarnsDetail", DIALOG_STYLE_MSGBOX, "Detail Peringatan", frmxss, "Kembali", "");
	return 1;
}

Dialog:CheckMyWarns(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
	if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih riwayat peringatan apapun!");
	if(PlayerListitem[playerid][listitem] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih riwayat peringatan apapun!");

	static frmxss[512];
	switch(PlayerWarning[playerid][PlayerListitem[playerid][listitem]][warnType])
	{
		case 1:
		{
			format(frmxss, sizeof(frmxss), ""WHITE"Penerbit: "RED"%s\n\
			"WHITE"Type: "GREEN"[WARN]\n\
			"WHITE"Tanggal: "CYAN"%s\n\
			"WHITE"Alasan:\n\
			"AQUAMARINE"%s",
			PlayerWarning[playerid][PlayerListitem[playerid][listitem]][warnIssuer],
			PlayerWarning[playerid][PlayerListitem[playerid][listitem]][warnDateTime],
			PlayerWarning[playerid][PlayerListitem[playerid][listitem]][warnReason]);
		}
		case 2:
		{
			format(frmxss, sizeof(frmxss), ""WHITE"Penerbit: "RED"%s\n\
			"WHITE"Type: "YELLOW"[JAIL]\n\
			"WHITE"Tanggal: "CYAN"%s\n\
			"WHITE"Alasan:\n\
			"AQUAMARINE"%s",
			PlayerWarning[playerid][PlayerListitem[playerid][listitem]][warnIssuer],
			PlayerWarning[playerid][PlayerListitem[playerid][listitem]][warnDateTime],
			PlayerWarning[playerid][PlayerListitem[playerid][listitem]][warnReason]);
		}
		case 3:
		{
			format(frmxss, sizeof(frmxss), ""WHITE"Penerbit: "RED"%s\n\
			"WHITE"Type: "ORANGERED"[BAN]\n\
			"WHITE"Tanggal: "CYAN"%s\n\
			"WHITE"Alasan:\n\
			"AQUAMARINE"%s",
			PlayerWarning[playerid][PlayerListitem[playerid][listitem]][warnIssuer],
			PlayerWarning[playerid][PlayerListitem[playerid][listitem]][warnDateTime],
			PlayerWarning[playerid][PlayerListitem[playerid][listitem]][warnReason]);
		}
	}
	Dialog_Show(playerid, "CheckMyWarnsDetail", DIALOG_STYLE_MSGBOX, "Detail Peringatan", frmxss, "Kembali", "");
	return 1;
}

Dialog:CheckWarnsDetail(playerid, response, listitem, inputtext[])
{
	if(response == 0 || response == 1)
	{
		static dahla[1024], count, otherid;
		count = 0;

		if(Temptargetid[playerid] != INVALID_PLAYER_ID && IsPlayerConnected(Temptargetid[playerid]) && AccountData[Temptargetid[playerid]][pSpawned])
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

		otherid = Temptargetid[playerid];
		format(dahla, sizeof(dahla), "Type\tPenerbit\tTanggal\tAlasan\n");
		for(new id; id < 100; ++id)
		{
			if(PlayerWarning[otherid][id][warnExists] && PlayerWarning[otherid][id][warnOwner] == AccountData[playerid][pID]) 
			{
				switch(PlayerWarning[otherid][id][warnType])
				{
					case 1:
					{
						format(dahla, sizeof(dahla), "%s"GREEN"[WARN]\t"WHITE"%s\t%s\t%s\n", dahla, PlayerWarning[otherid][id][warnIssuer], PlayerWarning[otherid][id][warnDate], PlayerWarning[otherid][id][warnReason]);
					}
					case 2:
					{
						format(dahla, sizeof(dahla), "%s"YELLOW"[JAIL]\t"WHITE"%s\t%s\t%s\n", dahla, PlayerWarning[otherid][id][warnIssuer], PlayerWarning[otherid][id][warnDate], PlayerWarning[otherid][id][warnReason]);
					}
					case 3:
					{
						format(dahla, sizeof(dahla), "%s"ORANGERED"[BAN]\t"WHITE"%s\t%s\t%s\n", dahla, PlayerWarning[otherid][id][warnIssuer], PlayerWarning[otherid][id][warnDate], PlayerWarning[otherid][id][warnReason]);
					}
				}
				PlayerListitem[playerid][count++] = id;
			}
		}

		if(count == 0)
		{
			Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, sprintf("Riwayat Peringatan %s", AccountData[otherid][pName]), "Pemain tersebut tidak memiliki riwayat peringatan apapun!", "Tutup", "");
		}
		else
		{
			Dialog_Show(playerid, "CheckWarns", DIALOG_STYLE_TABLIST_HEADERS, sprintf("Riwayat Peringatan %s", AccountData[otherid][pName]), dahla, "Pilih", "Tutup");
		}
	}
	return 1;
}

Dialog:CheckMyWarnsDetail(playerid, response, listitem, inputtext[])
{
	if(response == 0 || response == 1)
	{
		static dahla[1024], count;
		count = 0;
		format(dahla, sizeof(dahla), "Type\tPenerbit\tTanggal\tAlasan\n");
		for(new id; id < 100; ++id)
		{
			if(PlayerWarning[playerid][id][warnExists] && PlayerWarning[playerid][id][warnOwner] == AccountData[playerid][pID]) 
			{
				switch(PlayerWarning[playerid][id][warnType])
				{
					case 1:
					{
						format(dahla, sizeof(dahla), "%s"GREEN"[WARN]\t"WHITE"%s\t%s\t%s\n", dahla, PlayerWarning[playerid][id][warnIssuer], PlayerWarning[playerid][id][warnDate], PlayerWarning[playerid][id][warnReason]);
					}
					case 2:
					{
						format(dahla, sizeof(dahla), "%s"YELLOW"[JAIL]\t"WHITE"%s\t%s\t%s\n", dahla, PlayerWarning[playerid][id][warnIssuer], PlayerWarning[playerid][id][warnDate], PlayerWarning[playerid][id][warnReason]);
					}
					case 3:
					{
						format(dahla, sizeof(dahla), "%s"ORANGERED"[BAN]\t"WHITE"%s\t%s\t%s\n", dahla, PlayerWarning[playerid][id][warnIssuer], PlayerWarning[playerid][id][warnDate], PlayerWarning[playerid][id][warnReason]);
					}
				}
				PlayerListitem[playerid][count++] = id;
			}
		}

		if(count == 0)
		{
			Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX,"{DA9100}Pahlawan Roleplay "WHITE"- Riwayat Peringatan", "Anda tidak memiliki riwayat peringatan apapun!", "Tutup", "");
		}
		else
		{
			Dialog_Show(playerid, "CheckMyWarns", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Riwayat Peringatan", dahla, "Pilih", "Tutup");
		}
	}
	return 1;
}

Dialog:FactionConsficating(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	if (listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item apapun!");
	if(NearestSingle[playerid] == -1 || NearestSingle[playerid] == INVALID_PLAYER_ID) return 1;

	new targetid = NearestSingle[playerid];
	if (!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if (!IsPlayerNearPlayer(playerid, targetid, 3.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak dekat dengan anda!");
	if (AccountData[targetid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sedang melakukan sesuatu, mohon tunggu!");
	if (AccountData[targetid][pMenuShowed]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sedang akses penyimpanan, mohon tunggu!");

	if(!strcmp(InventoryData[targetid][PlayerListitem[playerid][listitem]][invQuantity], "Changename Card")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat mengambil changename card!");

	new Float:countingtotalweight;
	countingtotalweight = GetTotalWeightFloat(playerid) + float(InventoryData[targetid][PlayerListitem[playerid][listitem]][invQuantity] * GetItemWeight(InventoryData[targetid][PlayerListitem[playerid][listitem]][invItem])) / 1000;
	if (countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");
	
	if(!strcmp(InventoryData[targetid][PlayerListitem[playerid][listitem]][invQuantity], "Hunt Ammo"))
	{
		if(IsPlayerHunting[targetid])
		{
			ResetWeapon(targetid, 34);
			if(PlayerHasItem(targetid, "Hunt Ammo"))
			{
				GivePlayerWeaponEx(targetid, 34, Inventory_Count(targetid, "Hunt Ammo"), WEAPON_TYPE_PLAYER);
			}
		}
	}

	SIM(targetid,"Seluruh %s milik anda telah disita oleh "RED"%s [%s] (ID: %d)", InventoryData[targetid][PlayerListitem[playerid][listitem]][invItem], AccountData[playerid][pName], AccountData[playerid][pUCP], playerid);
	ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil menyita seluruh %s milik Pemain tersebut", InventoryData[targetid][PlayerListitem[playerid][listitem]][invItem]));
	ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, false, false, false, false, 0, true);
	SendRPMeAboveHead(playerid, sprintf("Menyita semua %s dari orang di depannya.", InventoryData[targetid][PlayerListitem[playerid][listitem]][invItem]));

	Inventory_Add(playerid, InventoryData[targetid][PlayerListitem[playerid][listitem]][invItem], InventoryData[targetid][PlayerListitem[playerid][listitem]][invModel], InventoryData[targetid][PlayerListitem[playerid][listitem]][invQuantity]);
	Inventory_Remove(targetid, InventoryData[targetid][PlayerListitem[playerid][listitem]][invItem], InventoryData[targetid][PlayerListitem[playerid][listitem]][invQuantity]);
	
	Inventory_Close(targetid);
	NearestSingle[playerid] = INVALID_PLAYER_ID;
	return 1;
}

Dialog:ShowToIDCard(playerid, response, listitem, inputtext[])
{
	if(!response) 
	{
		for(new x; x < 100; x++)
		{
			NearestUser[playerid][x] = INVALID_PLAYER_ID;
		}
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		return 1;
	}
	if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih apapun!");

	static targetid;
	targetid = NearestUser[playerid][listitem];

	if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(!IsPlayerNearPlayer(playerid, targetid, 3.5)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak dekat dengan anda!");

	PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);

	if(!AccountData[playerid][pHasKTP])
	{
		Dialog_Show(targetid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Kartu Tanda Penduduk", 
		"Orang ini tidak memiliki Kartu Tanda Penduduk/sudah expired.", "Tutup", "");
		return 1;
	}

	ShowIDCTD(playerid, targetid);

	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menunjukkan KTP kepada Pemain tersebut.");
	return 1;
}

Dialog:ShowToLicense(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		for(new x; x < 100; x++)
		{
			NearestUser[playerid][x] = INVALID_PLAYER_ID;
		}
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		return 1;
	}
	if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih apapun!");

	static targetid;
	targetid = NearestUser[playerid][listitem];

	if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(!IsPlayerNearPlayer(playerid, targetid, 3.5)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak dekat dengan anda!");

	PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);

	ShowLCTD(playerid, targetid);
	return 1;
}

Dialog:FactionPanel(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		for(new x; x < 100; x++)
		{
			NearestUser[playerid][x] = INVALID_PLAYER_ID;
		}
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		return 1;
	}

	if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih apapun!");

	static targetid;
	targetid = NearestUser[playerid][listitem];
	NearestSingle[playerid] = targetid;

	if(!IsPlayerNearPlayer(playerid, targetid, 3.5)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak dekat dengan anda!");

	PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);

	Dialog_Show(playerid, "FactionSelectPanel", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Select Panel", "Faction Panel\n"GRAY"Badside Panel", "Pilih", "Batal");
	return 1;
}

Dialog:FactionSelectPanel(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		for(new x; x < 100; x++)
		{
			NearestUser[playerid][x] = INVALID_PLAYER_ID;
		}
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		return 1;
	}
	
	switch(listitem)
	{
		case 0: //faction
		{
			if(AccountData[playerid][pFaction] < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota dari faction manapuns!");

			switch(AccountData[playerid][pFaction])
			{
				case FACTION_LSPD:
				{
					Dialog_Show(playerid, "PolisiPanel", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Faction Panel", 
					"Periksa Lisensi\n\
					"GRAY"Invoice Belum Terbayar\n\
					Kartu Identitas\n\
					"GRAY"Geledah\n\
					Borgol\n\
					"GRAY"Buka Borgol\n\
					Seret\n\
					"GRAY"Masukkan Mobil\n\
					Keluarkan Paksa\n\
					"GRAY"Invoice Manual\n\
					Penjarakan\n\
					"GRAY"Ambil Dirty Money\n\
					Cek Senjata\n\
					"GRAY"Sita Senjata", "Pilih", "Batal");
				}
				case FACTION_LSFD:
				{
					Dialog_Show(playerid, "ParamedisPanel", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Faction Panel", 
					"Revive\n\
					"GRAY"Treatment\n\
					Seret\n\
					"GRAY"Borgol\n\
					Buka Borgol\n\
					"GRAY"Invoice Belum Terbayar\n\
					Invoice Manual\n\
					"GRAY"Periksa\n\
					Detain\n\
					"GRAY"Eject\n\
					Sita Senjata", "Pilih", "Batal");
				}
				case FACTION_PUTRIDELI:
				{
					Dialog_Show(playerid, "PutrideliPanel", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Faction Panel", 
					"Invoice Belum Terbayar\n\
					"GRAY"Invoice Manual\n\
					Seret", "Pilih", "Batal");
				}
				case FACTION_SAGOV:
				{
					Dialog_Show(playerid, "PemerintahPanel", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Faction Panel", 
					"Periksa Lisensi\n\
					"GRAY"Borgol\n\
					Buka Borgol\n\
					"GRAY"Invoice Belum Terbayar\n\
					Kartu Identitas\n\
					"GRAY"Geledah\n\
					Cek Senjata\n\
					"GRAY"Seret\n\
					Masukkan Mobil\n\
					"GRAY"Keluarkan Paksa\n\
					Invoice Manual\n\
					"GRAY"Menyita kendaraan ke asuransi\n\
					Sita Senjata", "Pilih", "Batal");
				}
				case FACTION_BENNYS:
				{
					Dialog_Show(playerid, "BennysPanel", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Faction Panel", 
					"Invoice Belum Terbayar\n\
					"GRAY"Invoice Manual\n\
					Seret", "Pilih", "Batal");
				}
				case FACTION_UBER:
				{
					Dialog_Show(playerid, "UberPanel", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Faction Panel", 
					"Invoice Belum Terbayar\n\
					"GRAY"Invoice Manual\n\
					Seret", "Pilih", "Batal");
				}
				case FACTION_DINARBUCKS:
				{
					Dialog_Show(playerid, "DinarbucksPanel", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Faction Panel", 
					"Invoice Belum Terbayar\n\
					"GRAY"Invoice Manual\n\
					Seret", "Pilih", "Batal");
				}
				case FACTION_FOX11:
				{
					Dialog_Show(playerid, "PewartaPanel", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Faction Panel", 
					"Invoice Belum Terbayar\n\
					"GRAY"Invoice Manual\n\
					Seret", "Pilih", "Batal");
				}
				case FACTION_AUTOMAX:
				{
					Dialog_Show(playerid, "AutomaxPanel", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Faction Panel", 
					"Invoice Belum Terbayar\n\
					"GRAY"Invoice Manual\n\
					Seret", "Pilih", "Batal");
				}
				case FACTION_HANDOVER:
				{
					Dialog_Show(playerid, "HandoverPanel", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Faction Panel", 
					"Invoice Belum Terbayar\n\
					"GRAY"Invoice Manual\n\
					Seret", "Pilih", "Batal");
				}
				case FACTION_SRIMERSING:
				{
					Dialog_Show(playerid, "SriMersingPanel", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Faction Panel", 
					"Invoice Belum Terbayar\n\
					"GRAY"Invoice Manual\n\
					Seret", "Pilih", "Batal");
				}
				case FACTION_TEXAS:
				{
					Dialog_Show(playerid, "TexasChickenPanel", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Faction Panel", 
					"Invoice Belum Terbayar\n\
					"GRAY"Invoice Manual\n\
					Seret\n\
					"GRAY"Borgol\n\
					Buka Borgol\n\
					"GRAY"Geledah", "Pilih", "Batal");
				}
			}
			for(new x; x < 100; x++)
			{
				NearestUser[playerid][x] = INVALID_PLAYER_ID;
			}
		}
		case 1: //badside
		{
			if(AccountData[playerid][pFamily] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota dari badside/family manapun!");

			Dialog_Show(playerid, "BadsidePanel", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Badside Panel", 
			"Geledah\n\
			"GRAY"Ikat\n\
			Buka Ikatan\n\
			"GRAY"Seret\n\
			Masukkan Mobil\n\
			"GRAY"Keluarkan Paksa\n\
			Cek Senjata", "Pilih", "Batal");
		}
	}
	return 1;
}

Dialog:VoiceModeSet(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	switch(listitem)
	{
		case 0: // Bisik ke Normal
		{
			pVoiceDistanceStatus[playerid] = 1;
			CallRemoteFunction("UpdatePlayerVoiceDistance", "if", playerid, 14.7);
			PlayerTextDrawShow(playerid, PHBE[playerid][18]); // Voice 1
			PlayerTextDrawShow(playerid, PHBE[playerid][17]); // Voice 2
			PlayerTextDrawHide(playerid, PHBE[playerid][16]); // Voice 3
		}
		case 1: // Normal ke Bisik
		{
			pVoiceDistanceStatus[playerid] = 2;
			CallRemoteFunction("UpdatePlayerVoiceDistance", "if", playerid, 6.7);
			PlayerTextDrawShow(playerid, PHBE[playerid][18]); // Voice 1
			PlayerTextDrawHide(playerid, PHBE[playerid][17]); // Voice 2
			PlayerTextDrawHide(playerid, PHBE[playerid][16]); // Voice 3
		}
		case 2: // Bisik ke Teriak
		{
			pVoiceDistanceStatus[playerid] = 0;
			CallRemoteFunction("UpdatePlayerVoiceDistance", "if", playerid, 40.7);
			PlayerTextDrawShow(playerid, PHBE[playerid][18]); // Voice 1
			PlayerTextDrawShow(playerid, PHBE[playerid][17]); // Voice 2
			PlayerTextDrawShow(playerid, PHBE[playerid][16]); // Voice 3
		}
	}
	return 1;
}

Dialog:VoiceKeySet(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	switch(listitem)
	{
		case 0: //Z
		{
			CallRemoteFunction("UpdatePlayerVoiceKey", "id", playerid, 0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Keybind push to talk voice berhasil diganti menjadi ~b~Tombol Z");
		}
		case 1: //M
		{
			CallRemoteFunction("UpdatePlayerVoiceKey", "id", playerid, 1);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Keybind push to talk voice berhasil diganti menjadi ~b~Tombol M");
		}
		case 2: //L
		{
			CallRemoteFunction("UpdatePlayerVoiceKey", "id", playerid, 2);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Keybind push to talk voice berhasil diganti menjadi ~b~Tombol L");
		}
		case 3: //B
		{
			CallRemoteFunction("UpdatePlayerVoiceKey", "id", playerid, 3);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Keybind push to talk voice berhasil diganti menjadi ~b~Tombol B");
		}
		case 4: //X
		{
			CallRemoteFunction("UpdatePlayerVoiceKey", "id", playerid, 4);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Keybind push to talk voice berhasil diganti menjadi ~b~Tombol X");
		}
		case 5: //R
		{
			CallRemoteFunction("UpdatePlayerVoiceKey", "id", playerid, 5);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Keybind push to talk voice berhasil diganti menjadi ~b~Tombol R");
		}
		case 6: //P
		{
			CallRemoteFunction("UpdatePlayerVoiceKey", "id", playerid, 6);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Keybind push to talk voice berhasil diganti menjadi ~b~Tombol P");
		}
	}
	return 1;
}

//911 dispatch
Dialog:EmergencyChoose(playerid, response, listitem, inputtext[])
{
	if(!response) 
	{
		CutCallingLine(playerid);
		return 1;
	}

	switch(listitem)
	{
		case 0: //lspd
		{
			Dialog_Show(playerid, "EmergencyChoosePolice", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- 110 Emergency Hotline", 
			"Dispatcher: Halo, apa yang sedang kamu alami?\n(Tuliskan masalah yang anda hadapi):", "Set", "Batal");
		}
		case 1: //lsfd
		{
			Dialog_Show(playerid, "EmergencyChooseFire", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- 110 Emergency Hotline", 
			"Dispatcher: Halo, apa yang sedang kamu alami?\n(Tuliskan masalah yang anda hadapi):", "Set", "Batal");
		}
	}
	return 1;
}

Dialog:EmergencyChoosePolice(playerid, response, listitem, inputtext[])
{
	if(!response) 
	{
		CutCallingLine(playerid);
		return 1;
	}

	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");
	if(strfind(inputtext, "%", true) != -1 || strfind(inputtext, "#", true) != -1)  return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memasukkan tanda persen!");

	AccountData[playerid][p911Hotline] = gettime()+60;

	static Float:px, Float:py, Float:pz, string[144], frmt[144];
	strcopy(string, inputtext);
	GetPlayerPos(playerid, px, py, pz);

	foreach(new i : LSPDDuty)
	{
		SendClientMessage(i, X11_RED, "__________ [911 Emergency Dispatch] __________");
		format(frmt, sizeof(frmt), "Caller: %s | Ph: "YELLOW"%s "WHITE"| %s", GetPlayerRoleplayName(playerid), PlayerPhoneData[playerid][phoneNumber], (AccountData[playerid][pGender] == 1) ? ("Laki-Laki") : ("Perempuan"));
		SendClientMessage(i, X11_WHITE, frmt);
		format(frmt, sizeof(frmt), "Loc: %s", GetLocation(px, py, pz));
		SendClientMessage(i, X11_WHITE, frmt);
		format(frmt, sizeof(frmt), "~> %s", string);
		SendClientMessage(i, 0x0096FFFF, frmt);
		SendClientMessage(i, X11_RED, "___________________________________________");
	}

	ShowTDN(playerid, NOTIFICATION_INFO, "Pesan anda telah kami sampaikan kepada petugas.");

	CutCallingLine(playerid);
	return 1;
}

Dialog:EmergencyChooseFire(playerid, response, listitem, inputtext[])
{
	if(!response) 
	{
		CutCallingLine(playerid);
		return 1;
	}

	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");
	if(strfind(inputtext, "%", true) != -1 || strfind(inputtext, "#", true) != -1)  return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memasukkan tanda persen!");

	AccountData[playerid][p911Hotline] = gettime()+60;

	static Float:px, Float:py, Float:pz, string[144], frmt[144];
	strcopy(string, inputtext);
	GetPlayerPos(playerid, px, py, pz);
	
	foreach(new i : LSFDDuty)
	{
		SendClientMessage(i, X11_RED, "__________ [911 Emergency Dispatch] __________");
		format(frmt, sizeof(frmt), "Caller: %s | Ph: "YELLOW"%s "WHITE"| %s", GetPlayerRoleplayName(playerid), PlayerPhoneData[playerid][phoneNumber], (AccountData[playerid][pGender] == 1) ? ("Laki-Laki") : ("Perempuan"));
		SendClientMessage(i, X11_WHITE, frmt);
		format(frmt, sizeof(frmt), "Loc: %s", GetLocation(px, py, pz));
		SendClientMessage(i, X11_WHITE, frmt);
		format(frmt, sizeof(frmt), "~> %s", string);
		SendClientMessage(i, 0xFF1A1AFF, frmt);
		SendClientMessage(i, X11_RED, "___________________________________________");
	}

	ShowTDN(playerid, NOTIFICATION_INFO, "Pesan anda telah kami sampaikan kepada petugas.");

	CutCallingLine(playerid);
	return 1;
}

//event
Dialog:EventTDMCreator(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	switch(listitem)
	{
		case 0: //red skin
		{
			Dialog_Show(playerid, "EventTDMRedSkin", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- TDM Red Team Skin", "Mohon masukkan skin id yang valid (1 - 311):",
			"Input", "Batal");
		}
		case 1: //red health
		{
			Dialog_Show(playerid, "EventTDMRedHealth", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- TDM Red Team Health", "Mohon masukkan jumlah health yang valid (10 - 100):",
			"Input", "Batal");
		}
		case 2: //red armour
		{
			Dialog_Show(playerid, "EventTDMRedArmor", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- TDM Red Team Armour", "Mohon masukkan jumlah armour yang valid (0 - 100):",
			"Input", "Batal");
		}
		case 3: //red spawn point
		{
			GetPlayerPos(playerid, EventInfo[redSpawn][0], EventInfo[redSpawn][1], EventInfo[redSpawn][2]);
			GetPlayerFacingAngle(playerid, EventInfo[redSpawn][3]);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Red Team spawn point berhasil ditetapkan!");
		}
		case 4: //red w1
		{
			Dialog_Show(playerid, "EventTDMRedW1", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- TDM Red Team W1", "Mohon masukkan weapon id yang valid (0 - 34):",
			"Input", "Batal");
		}
		case 5: //red w2
		{
			Dialog_Show(playerid, "EventTDMRedW2", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- TDM Red Team W2", "Mohon masukkan weapon id yang valid (0 - 34):",
			"Input", "Batal");
		}
		case 6: //red w3
		{
			Dialog_Show(playerid, "EventTDMRedW3", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- TDM Red Team W3", "Mohon masukkan weapon id yang valid (0 - 34):",
			"Input", "Batal");
		}
		case 7: //blue skin
		{
			Dialog_Show(playerid, "EventTDMBlueSkin", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- TDM Blue Team Skin", "Mohon masukkan skin id yang valid (1 - 311):",
			"Input", "Batal");
		}
		case 8: //blue health
		{
			Dialog_Show(playerid, "EventTDMBlueHealth", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- TDM Blue Team Health", "Mohon masukkan jumlah health yang valid (10 - 100):",
			"Input", "Batal");
		}
		case 9: //blue armour
		{
			Dialog_Show(playerid, "EventTDMBlueArmor", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- TDM Blue Team Armour", "Mohon masukkan jumlah armour yang valid (0 - 100):",
			"Input", "Batal");
		}
		case 10: //blue spawn point
		{
			GetPlayerPos(playerid, EventInfo[blueSpawn][0], EventInfo[blueSpawn][1], EventInfo[blueSpawn][2]);
			GetPlayerFacingAngle(playerid, EventInfo[blueSpawn][3]);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Blue Team spawn point berhasil ditetapkan!");
		}
		case 11: //blue w1
		{
			Dialog_Show(playerid, "EventTDMBlueW1", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- TDM Blue Team W1", "Mohon masukkan weapon id yang valid (0 - 34):",
			"Input", "Batal");
		}
		case 12: //blue w2
		{
			Dialog_Show(playerid, "EventTDMBlueW2", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- TDM Blue Team W2", "Mohon masukkan weapon id yang valid (0 - 34):",
			"Input", "Batal");
		}
		case 13: //blue w3
		{
			Dialog_Show(playerid, "EventTDMBlueW3", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- TDM Blue Team W3", "Mohon masukkan weapon id yang valid (0 - 34):",
			"Input", "Batal");
		}
		case 14: //arena vwid
		{
			Dialog_Show(playerid, "EventTDMAVWID", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- TDM Arena VWID", "Mohon masukkan virtual world ID yang valid untuk event team deathmatch tersebut:",
			"Input", "Batal");
		}
		case 15: //arena interior id
		{
			Dialog_Show(playerid, "EventTDMAINTID", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- TDM Arena Interior ID", "Mohon masukkan interior ID yang valid untuk event team deathmatch tersebut:",
			"Input", "Batal");
		}
		case 16: //time limit
		{
			Dialog_Show(playerid, "EventTDMTime", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- TDM Time Limit", "Mohon masukkan rentang waktu event team deathmatch tersebut dalam satuan menit:",
			"Input", "Batal");
		}
		case 17: //target score
		{
			Dialog_Show(playerid, "EventTDMScore", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- TDM Target Score", "Mohon masukkan skor yang ingin dicapai dalam event team deathmatch tersebut:",
			"Input", "Batal");
		}
		case 18: //max player
		{
			Dialog_Show(playerid, "EventTDMMPLYR", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- TDM Max Players", "Mohon masukkan maksimum partisipan dalam event tersebut:",
			"Input", "Batal");
		}
		case 19: //participation price
		{
			Dialog_Show(playerid, "EventTDMPartPrize", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- TDM Participation Prize", "Mohon masukkan nominal uang yang akan diberikan sebagai hadiah partisipasi:",
			"Input", "Batal");
		}
		case 20: //Winner prize
		{
			Dialog_Show(playerid, "EventTDMWinPrize", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- TDM Winner Prize", "Mohon masukkan nominal uang yang akan diberikan sebagai hadiah pemenang event:",
			"Input", "Batal");
		}
	}
	return 1;
}

Dialog:EventTDMRedSkin(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

	if(EventInfo[eventOpened] || EventInfo[eventStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Sedang ada event yang berlangsung!");

	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");
	if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya angka yang dapat dimasukkan!");
	if(strval(inputtext) < 1 || strval(inputtext) > 311) return ShowTDN(playerid, NOTIFICATION_ERROR, "Skin ID tidak valid (1 - 311)");

	EventInfo[redSkin] = strval(inputtext);

	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Red Team skin berhasil ditetapkan!");
	return 1;
}
Dialog:EventTDMRedHealth(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

	if(EventInfo[eventOpened] || EventInfo[eventStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Sedang ada event yang berlangsung!");

	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");
	if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya angka yang dapat dimasukkan!");
	if(strval(inputtext) < 10 || strval(inputtext) > 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Health tidak valid (10 - 100)");

	EventInfo[redHealth] = strval(inputtext);

	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Red Team health berhasil ditetapkan!");
	return 1;
}
Dialog:EventTDMRedArmor(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

	if(EventInfo[eventOpened] || EventInfo[eventStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Sedang ada event yang berlangsung!");

	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");
	if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya angka yang dapat dimasukkan!");
	if(strval(inputtext) < 0 || strval(inputtext) > 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Armour tidak valid (0 - 100)");

	EventInfo[redArmour] = strval(inputtext);

	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Red Team armour berhasil ditetapkan!");
	return 1;
}
Dialog:EventTDMRedW1(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

	if(EventInfo[eventOpened] || EventInfo[eventStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Sedang ada event yang berlangsung!");

	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");
	if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya angka yang dapat dimasukkan!");
	if(strval(inputtext) < 0 || strval(inputtext) > 34) return ShowTDN(playerid, NOTIFICATION_ERROR, "Weapon ID tidak valid (0 - 34)");

	EventInfo[redWeapon][0] = strval(inputtext);

	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Red Team Weapon 1 berhasil ditetapkan!");
	return 1;
}
Dialog:EventTDMRedW2(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

	if(EventInfo[eventOpened] || EventInfo[eventStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Sedang ada event yang berlangsung!");

	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");
	if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya angka yang dapat dimasukkan!");
	if(strval(inputtext) < 0 || strval(inputtext) > 34) return ShowTDN(playerid, NOTIFICATION_ERROR, "Weapon ID tidak valid (0 - 34)");

	EventInfo[redWeapon][1] = strval(inputtext);

	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Red Team Weapon 2 berhasil ditetapkan!");
	return 1;
}
Dialog:EventTDMRedW3(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

	if(EventInfo[eventOpened] || EventInfo[eventStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Sedang ada event yang berlangsung!");

	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");
	if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya angka yang dapat dimasukkan!");
	if(strval(inputtext) < 0 || strval(inputtext) > 34) return ShowTDN(playerid, NOTIFICATION_ERROR, "Weapon ID tidak valid (0 - 34)");

	EventInfo[redWeapon][2] = strval(inputtext);

	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Red Team Weapon 3 berhasil ditetapkan!");
	return 1;
}
Dialog:EventTDMBlueSkin(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

	if(EventInfo[eventOpened] || EventInfo[eventStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Sedang ada event yang berlangsung!");

	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");
	if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya angka yang dapat dimasukkan!");
	if(strval(inputtext) < 1 || strval(inputtext) > 311) return ShowTDN(playerid, NOTIFICATION_ERROR, "Skin ID tidak valid (1 - 311)");

	EventInfo[blueSkin] = strval(inputtext);

	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Blue Team skin berhasil ditetapkan!");
	return 1;
}
Dialog:EventTDMBlueHealth(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

	if(EventInfo[eventOpened] || EventInfo[eventStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Sedang ada event yang berlangsung!");

	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");
	if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya angka yang dapat dimasukkan!");
	if(strval(inputtext) < 10 || strval(inputtext) > 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Health tidak valid (10 - 100)");

	EventInfo[blueHealth] = strval(inputtext);

	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Blue Team health berhasil ditetapkan!");
	return 1;
}
Dialog:EventTDMBlueArmor(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

	if(EventInfo[eventOpened] || EventInfo[eventStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Sedang ada event yang berlangsung!");

	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");
	if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya angka yang dapat dimasukkan!");
	if(strval(inputtext) < 0 || strval(inputtext) > 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Armour tidak valid (0 - 100)");

	EventInfo[blueArmour] = strval(inputtext);

	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Blue Team armour berhasil ditetapkan!");
	return 1;
}
Dialog:EventTDMBlueW1(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

	if(EventInfo[eventOpened] || EventInfo[eventStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Sedang ada event yang berlangsung!");

	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");
	if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya angka yang dapat dimasukkan!");
	if(strval(inputtext) < 0 || strval(inputtext) > 34) return ShowTDN(playerid, NOTIFICATION_ERROR, "Weapon ID tidak valid (0 - 34)");

	EventInfo[blueWeapon][0] = strval(inputtext);

	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Blue Team Weapon 1 berhasil ditetapkan!");
	return 1;
}
Dialog:EventTDMBlueW2(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

	if(EventInfo[eventOpened] || EventInfo[eventStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Sedang ada event yang berlangsung!");

	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");
	if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya angka yang dapat dimasukkan!");
	if(strval(inputtext) < 0 || strval(inputtext) > 34) return ShowTDN(playerid, NOTIFICATION_ERROR, "Weapon ID tidak valid (0 - 34)");

	EventInfo[blueWeapon][1] = strval(inputtext);

	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Blue Team Weapon 2 berhasil ditetapkan!");
	return 1;
}
Dialog:EventTDMBlueW3(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

	if(EventInfo[eventOpened] || EventInfo[eventStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Sedang ada event yang berlangsung!");

	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");
	if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya angka yang dapat dimasukkan!");
	if(strval(inputtext) < 0 || strval(inputtext) > 34) return ShowTDN(playerid, NOTIFICATION_ERROR, "Weapon ID tidak valid (0 - 34)");

	EventInfo[blueWeapon][2] = strval(inputtext);

	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Blue Team Weapon 3 berhasil ditetapkan!");
	return 1;
}
Dialog:EventTDMAVWID(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

	if(EventInfo[eventOpened] || EventInfo[eventStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Sedang ada event yang berlangsung!");

	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");
	if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya angka yang dapat dimasukkan!");
	if(strval(inputtext) < 0 || strval(inputtext) > 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Virtual World ID tidak valid (0 - 100)");

	EventInfo[arenaVWID] = strval(inputtext);

	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Arena VWID berhasil ditetapkan!");
	return 1;
}
Dialog:EventTDMAINTID(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

	if(EventInfo[eventOpened] || EventInfo[eventStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Sedang ada event yang berlangsung!");

	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");
	if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya angka yang dapat dimasukkan!");
	if(strval(inputtext) < 0 || strval(inputtext) > 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Interior ID tidak valid (0 - 100)");

	EventInfo[arenaIntid] = strval(inputtext);

	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Arena Interior ID berhasil ditetapkan!");
	return 1;
}
Dialog:EventTDMTime(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

	if(EventInfo[eventOpened] || EventInfo[eventStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Sedang ada event yang berlangsung!");
	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");
	if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya angka yang dapat dimasukkan!");
	if(strval(inputtext) < 1 || strval(inputtext) > 30) return ShowTDN(playerid, NOTIFICATION_ERROR, "Time limit tidak valid (1 - 30)");

	EventInfo[timeLimit] = strval(inputtext)*60;

	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Time limitation berhasil ditetapkan!");
	return 1;

}
Dialog:EventTDMScore(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

	if(EventInfo[eventOpened] || EventInfo[eventStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Sedang ada event yang berlangsung!");
	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");
	if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya angka yang dapat dimasukkan!");
	if(strval(inputtext) < 1 || strval(inputtext) > 500) return ShowTDN(playerid, NOTIFICATION_ERROR, "Target score tidak valid (1 - 500)");

	EventInfo[targetScore] = strval(inputtext);

	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Target score berhasil ditetapkan!");
	return 1;
}
Dialog:EventTDMMPLYR(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

	if(EventInfo[eventOpened] || EventInfo[eventStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Sedang ada event yang berlangsung!");
	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");
	if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya angka yang dapat dimasukkan!");
	if(strval(inputtext) < 50 || strval(inputtext) > 300) return ShowTDN(playerid, NOTIFICATION_ERROR, "Max Players tidak valid (50 - 250)");

	EventInfo[maxPlayer] = strval(inputtext);

	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Max player berhasil ditetapkan!");
	return 1;
}
Dialog:EventTDMPartPrize(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

	if(EventInfo[eventOpened] || EventInfo[eventStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Sedang ada event yang berlangsung!");
	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");
	if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya angka yang dapat dimasukkan!");
	if(strval(inputtext) < 1 || strval(inputtext) > 500) return ShowTDN(playerid, NOTIFICATION_ERROR, "Participation prize tidak valid (1 - 500)");

	EventInfo[partPrize] = strval(inputtext);

	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Participation prize berhasil ditetapkan!");
	return 1;
}
Dialog:EventTDMWinPrize(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

	if(EventInfo[eventOpened] || EventInfo[eventStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Sedang ada event yang berlangsung!");
	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");
	if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya angka yang dapat dimasukkan!");
	if(strval(inputtext) < 1 || strval(inputtext) > 1000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Winner prize tidak valid (1 - 1000)");

	EventInfo[winnerPrize] = strval(inputtext);

	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Winner prize berhasil ditetapkan!");
	return 1;
}

Dialog:EventRace(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	switch(listitem)
	{
		case 0: //race spawn
		{
			GetPlayerPos(playerid, EventInfo[raceSpawn][0], EventInfo[raceSpawn][1], EventInfo[raceSpawn][2]);
			GetPlayerFacingAngle(playerid, EventInfo[raceSpawn][3]);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Racing spawn point berhasil ditetapkan!");
		}
		case 1: //race vehicle
		{
			Dialog_Show(playerid, "EventRaceVID", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Race Vehicel Model ID", "Mohon masukkan vehicle id yang valid:",
			"Input", "Batal");
		}
		case 2: //race vehicle
		{
			Dialog_Show(playerid, "EventRaceMusic", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Race Event Music", "Please insert the music URL (mp3):",
			"Input", "Batal");
		}
		case 3: //add race checkpoint
		{
			new rcpid = Iter_Free(EvRaceCP);
			if(rcpid <= -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "CP Balap telah mencapai batas maksimal!");

			GetPlayerPos(playerid, EventRaceCP[rcpid][raceCPCoord][0], EventRaceCP[rcpid][raceCPCoord][1], EventRaceCP[rcpid][raceCPCoord][2]);
			Iter_Add(EvRaceCP, rcpid);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Racing checkpoint berhasil ditetapkan (%d/30).", Iter_Count(EvRaceCP)));
		}
		case 4: //clear all race checkpoint
		{
			foreach(new rcpid : EvRaceCP)
			{
				EventRaceCP[rcpid][raceCPCoord][0] = 0.0;
				EventRaceCP[rcpid][raceCPCoord][1] = 0.0;
				EventRaceCP[rcpid][raceCPCoord][2] = 0.0;
			}

			Iter_Clear(EvRaceCP);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Seluruh checkpoint race berhasil direset!");
		}
		case 5: //arena vwid
		{
			Dialog_Show(playerid, "EventTDMAVWID", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Race Arena VWID", "Mohon masukkan virtual world ID yang valid untuk event racing tersebut:",
			"Input", "Batal");
		}
		case 6: //arena interior id
		{
			Dialog_Show(playerid, "EventTDMAINTID", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Race Arena Interior ID", "Mohon masukkan interior ID yang valid untuk event racing tersebut:",
			"Input", "Batal");
		}
		case 7: //max player
		{
			Dialog_Show(playerid, "EventTDMMPLYR", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Race Max Players", "Mohon masukkan maksimum partisipan dalam event tersebut:",
			"Input", "Batal");
		}
		case 8: //participation price
		{
			Dialog_Show(playerid, "EventTDMPartPrize", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Race Participation Prize", "Mohon masukkan nominal uang yang akan diberikan sebagai hadiah partisipasi:",
			"Input", "Batal");
		}
		case 9: //Winner prize
		{
			Dialog_Show(playerid, "EventTDMWinPrize", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Race Winner Prize", "Mohon masukkan nominal uang yang akan diberikan sebagai hadiah pemenang event:",
			"Input", "Batal");
		}
	}
	return 1;
}

Dialog:EventRaceVID(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

	if(EventInfo[eventOpened] || EventInfo[eventStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Sedang ada event yang berlangsung!");

	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");
	if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya angka yang dapat dimasukkan!");
	
	if (strval(inputtext) < 400 || strval(inputtext) > 611)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Masukkan model kendaraan antara 400 - 611!");

	EventInfo[raceVehicle] = strval(inputtext);

	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Race vehicle model id berhasil ditetapkan!");
	return 1;
}

Dialog:EventRaceMusic(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

	if(EventInfo[eventOpened] || EventInfo[eventStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Sedang ada event yang berlangsung!");

	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");

	strcopy(EventInfo[eventMusic], inputtext);

	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Race music berhasil ditetapkan!");
	return 1;
}

//event ZOMBIE
Dialog:EventZombie(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	switch(listitem)
	{
		case 0: //zombie spawn point
		{
			GetPlayerPos(playerid, EventInfo[zombieSpawn][0], EventInfo[zombieSpawn][1], EventInfo[zombieSpawn][2]);
			GetPlayerFacingAngle(playerid, EventInfo[zombieSpawn][3]);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Zombie spawn point berhasil ditetapkan!");
		}
		case 1: //survivor spawn point
		{
			GetPlayerPos(playerid, EventInfo[humanSpawn][0], EventInfo[humanSpawn][1], EventInfo[humanSpawn][2]);
			GetPlayerFacingAngle(playerid, EventInfo[humanSpawn][3]);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Survivor spawn point berhasil ditetapkan!");
		}
		case 2: //RB 1 (min x & max y)
		{
			GetPlayerPos(playerid, EventInfo[boundPoint1][0], EventInfo[boundPoint1][1], EventInfo[boundPoint1][2]);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Bound point 1 berhasil ditetapkan!");
		}
		case 3: //RB 2 (min y & max x)
		{
			GetPlayerPos(playerid, EventInfo[boundPoint2][0], EventInfo[boundPoint2][1], EventInfo[boundPoint2][2]);

			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Bound point 2 berhasil ditetapkan!");
		}
		case 4: //arena vwid
		{
			Dialog_Show(playerid, "EventTDMAVWID", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Arena VWID", "Mohon masukkan virtual world ID yang valid untuk event tersebut:",
			"Input", "Batal");
		}
		case 5: //max player
		{
			Dialog_Show(playerid, "EventTDMMPLYR", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Max Players", "Mohon masukkan maksimum partisipan dalam event tersebut:",
			"Input", "Batal");
		}
		case 6: //participation price
		{
			Dialog_Show(playerid, "EventTDMPartPrize", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Participation Prize", "Mohon masukkan nominal uang yang akan diberikan sebagai hadiah partisipasi:",
			"Input", "Batal");
		}
		case 7: //Winner prize
		{
			Dialog_Show(playerid, "EventTDMWinPrize", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Winner Prize", "Mohon masukkan nominal uang yang akan diberikan sebagai hadiah pemenang event:",
			"Input", "Batal");
		}
	}
	return 1;
}

//fallout
Dialog:EventFallout(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	switch(listitem)
	{
		case 0: //max player
		{
			Dialog_Show(playerid, "EventTDMMPLYR", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Max Players", "Mohon masukkan maksimum partisipan dalam event tersebut:",
			"Input", "Batal");
		}
		case 1: //participation price
		{
			Dialog_Show(playerid, "EventTDMPartPrize", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Participation Prize", "Mohon masukkan nominal uang yang akan diberikan sebagai hadiah partisipasi:",
			"Input", "Batal");
		}
		case 2: //Winner prize
		{
			Dialog_Show(playerid, "EventTDMWinPrize", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Winner Prize", "Mohon masukkan nominal uang yang akan diberikan sebagai hadiah pemenang event:",
			"Input", "Batal");
		}
	}
	return 1;
}

//squid game
Dialog:EventSquidGame(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	switch(listitem)
	{
		case 0: //max player
		{
			Dialog_Show(playerid, "EventTDMMPLYR", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Max Players", "Mohon masukkan maksimum partisipan dalam event tersebut:",
			"Input", "Batal");
		}
		case 1: //participation price
		{
			Dialog_Show(playerid, "EventTDMPartPrize", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Participation Prize", "Mohon masukkan nominal uang yang akan diberikan sebagai hadiah partisipasi:",
			"Input", "Batal");
		}
		case 2: //Winner prize
		{
			Dialog_Show(playerid, "EventTDMWinPrize", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Winner Prize", "Mohon masukkan nominal uang yang akan diberikan sebagai hadiah pemenang event:",
			"Input", "Batal");
		}
	}
	return 1;
}

//=====================  end of event  ============================
Dialog:CheckAdverts(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
	if(listitem == -1) return 1;
	
	new idadvert = PlayerListitem[playerid][listitem];
	if(idadvert == -1) return 1;
	if(!AdvertisementEnum[idadvert][adSubmitted]) return 1;
	
	AccountData[playerid][pTempValue] = idadvert;
	static string[258];
	format(string, sizeof(string), ""WHITE"Issuer: "YELLOW"%s\n\
	"CYAN"%s", AdvertisementEnum[idadvert][adIssuer], AdvertisementEnum[idadvert][adDetail]);

	Dialog_Show(playerid, "CheckAdvertsDetails", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Adverts", string, "Call", "Batal");
	return 1;
}
Dialog:CheckAdvertsDetails(playerid, response, listitem, inputtext[])
{
	if(!response) 
	{
		AccountData[playerid][pTempValue] = -1;
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		return 1;
	}
	if(AccountData[playerid][pTempValue] == -1) return 1;

	new targetid = GetNumberOwner(AdvertisementEnum[AccountData[playerid][pTempValue]][adNumb]);
	if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Mohon maaf nomor tersebut tidak aktif di kota!");
	if(OJailData[targetid][jailed]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sedang di-jail admin!");
	if(AccountData[targetid][pArrested]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sedang dipenjara!");
	OnOutcomingCall(playerid, AdvertisementEnum[AccountData[playerid][pTempValue]][adNumb]);
	return 1;
}

Dialog:InteriorFall(playerid, response, listitem, inputtext[])
{
	new did = AccountData[playerid][pInDoor];
	if(did == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah tidak berada di interior manapun!");
	
	if(!response)
	{
		SetPlayerPositionEx(playerid, DoorData[did][dExtposX], DoorData[did][dExtposY], DoorData[did][dExtposZ], DoorData[did][dExtposA], 6500);
		AccountData[playerid][pInDoor] = -1;
		AccountData[playerid][pIsFallFromInterior] = false;
		SetPlayerInteriorEx(playerid, DoorData[did][dExtint]);
		SetPlayerVirtualWorldEx(playerid, DoorData[did][dExtvw]);
		SetCameraBehindPlayer(playerid);
		SetPlayerWeather(playerid, WorldWeather);
		GameTextForPlayer(playerid, "Loading Object...", 6500, 3);
		return 1;
	}
	SetPlayerPositionEx(playerid, DoorData[did][dIntposX], DoorData[did][dIntposY], DoorData[did][dIntposZ], DoorData[did][dIntposA], 6500);
	AccountData[playerid][pInDoor] = did;
	AccountData[playerid][pIsFallFromInterior] = false;
	SetPlayerInteriorEx(playerid, DoorData[did][dIntint]);
	SetPlayerVirtualWorldEx(playerid, DoorData[did][dIntvw]);
	SetCameraBehindPlayer(playerid);
	SetPlayerWeather(playerid, 0);
	GameTextForPlayer(playerid, "Loading Object...", 6500, 3);
	return 1;
}

Dialog:MyDocuments(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	CancelSelectTextDraw(playerid);
	switch(listitem)
	{
		case 0: //lihat KTA
		{
			if(AccountData[playerid][pFaction] == FACTION_NONE) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari any faction!");

			ShowKTATD(playerid, playerid);
			SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Untuk menyembunyikan textdraw saat ini, gunakan "CMDEA"'/hidektd' "WHITE"sebagai CMD.");
		}
		case 1: //tunjukkan KTA
		{
			if(AccountData[playerid][pFaction] == FACTION_NONE) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari any faction!");

			foreach(new i : Player) if(AccountData[i][pSpawned])
			{
				if(IsPlayerNearPlayer(playerid, i, 6.5)) 
				{
					ShowKTATD(playerid, i);
					SendClientMessage(i, Y_PAHLAWAN, "<!> "WHITE"Untuk menyembunyikan textdraw saat ini, gunakan "CMDEA"'/hidektd' "WHITE"sebagai CMD.");
				}
			}
		}
		case 2: //Lihat BPJS
		{
			if(!DocumentInfo[playerid][BPJS]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki BPJS!");
			ShowBPJSTD(playerid, playerid);
			SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Untuk menyembunyikan textdraw saat ini, gunakan "CMDEA"'/hidektd' "WHITE"sebagai CMD.");
		}
		case 3: //Tunjukkan BPJS
		{
			if(!DocumentInfo[playerid][BPJS]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki BPJS!");

			new count = 0, frmxt[522];
			foreach(new i : Player) if(i != playerid) if(IsPlayerNearPlayer(playerid, i, 2.5)) 
			{
				if (i % 2 == 0) {
				format(frmxt, sizeof(frmxt), "%s"WHITE"Kantong - (%d)\n", frmxt, i);
				}
				else {
					format(frmxt, sizeof(frmxt), "%s"GRAY"Kantong - (%d)\n", frmxt, i);
				}
				NearestUser[playerid][count++] = i;
			}

			if(count > 0)
			{
				Dialog_Show(playerid, "ShowToBPJS", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Tunjukkan BPJS", 
				frmxt, "Pilih", "Batal");
			}
		}
		case 4: //lihat SKS
		{
			if(!DocumentInfo[playerid][SKS]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki SKS!");
			new frmtxs[1080];
			format(frmtxs, sizeof(frmtxs), ""WHITE"========== SURAT KETERANGAN SEHAT ==========\n\
			Pernyataan resmi dari RSU. Mitra Pahlawan Roleplay\n\n\
			PETUGAS\n\
			Nama:\n\
			"YELLOW"%s\n\
			"WHITE"Jabatan:\n\
			"YELLOW"%s\n\n\
			"WHITE"BIODATA DI BAWAH INI\n\
			Nama:\t\tJenis Kelamin:\n\
			%s\t%s\n\
			Usia:\n\
			%d Tahun\n\
			Tanggal Pernyataan:\n\
			"AQUAMARINE"%s\n\n\
			"WHITE"Menerangkan bahwa:\n\
			"ORANGE"%s\n\n\
			"WHITE"KETERANGAN & TANDA TANGAN\n\
			Bahwa surat ini dinyatakan sah di mata negara dan hukum.\n\
			Masa Berlaku: "AQUAMARINE"%s\n\n\
			"WHITE"- %s -",
			DocumentInfo[playerid][SKSIssuer],
			DocumentInfo[playerid][SKSIssuerRank],
			GetPlayerRoleplayName(playerid),
			(AccountData[playerid][pGender] == 1) ? ("Laki-Laki") : ("Perempuan"),
			AccountData[playerid][pAge],
			DocumentInfo[playerid][SKSIssueDate],
			DocumentInfo[playerid][SKSText],
			ReturnTimelapse(gettime(), DocumentInfo[playerid][SKSDur], ""DARKRED"Habis"),
			DocumentInfo[playerid][SKSIssuer]);
			Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- SKS", 
			frmtxs, "Tutup", "");

		}
		case 5: //Tunjukkan SKS
		{
			if(!DocumentInfo[playerid][SKS]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki SKS!");

			new count = 0, frmxt[522];
			foreach(new i : Player) if(i != playerid) if(IsPlayerNearPlayer(playerid, i, 2.5)) 
			{
				if (i % 2 == 0) {
				format(frmxt, sizeof(frmxt), "%s"WHITE"Player ID - (%d)\n", frmxt, i);
				}
				else {
					format(frmxt, sizeof(frmxt), "%s"GRAY"Player ID - (%d)\n", frmxt, i);
				}
				NearestUser[playerid][count++] = i;
			}

			if(count > 0)
			{
				Dialog_Show(playerid, "ShowToSKS", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Tunjukkan SKS", 
				frmxt, "Pilih", "Batal");
			}
		}
		case 6: //lihat SKCK
		{
			if(!DocumentInfo[playerid][SKCK]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki SKCK!");
			new frmtxs[1080];
			format(frmtxs, sizeof(frmtxs), ""WHITE"========== SURAT KETERANGAN CATATAN KEPOLISIAN ==========\n\
			Dengan ini Kepolisian Daerah Pahlawan Roleplay telah merilis\n\
			keterangan catatan kepolisian bagi yang berdata diri di bawah ini:\n\n\
			Nama Lengkap: "YELLOW"%s\n\
			"WHITE"Usia: "YELLOW"%d Tahun\n\n\
			"WHITE"Tanggal Pernyataan:\n\
			"CYAN"%s\n\
			"WHITE"Dinyatakan bahwa yang bersangkutan:\n\
			"ORANGE"%s\n\n\
			"WHITE"Surat ini dinyatakan sah di mata negara dan hukum.\n\
			Masa Berlaku: "CYAN"%s\n\n\
			"WHITE"Hormat,\n\
			%s %s\n\
			Sentra Pelayanan Kepolisian Terpadu.",
			GetPlayerRoleplayName(playerid),
			AccountData[playerid][pAge],
			DocumentInfo[playerid][SKCKIssueDate],
			DocumentInfo[playerid][SKCKText],
			ReturnTimelapse(gettime(), DocumentInfo[playerid][SKCKDur], ""DARKRED"Habis"),
			DocumentInfo[playerid][SKCKIssuerRank],
			DocumentInfo[playerid][SKCKIssuer]);
			Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- SKCK", 
			frmtxs, "Tutup", "");

		}
		case 7: //Tunjukkan SKCK
		{
			if(!DocumentInfo[playerid][SKCK]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki SKCK!");

			new count = 0, frmxt[522];
			foreach(new i : Player) if(i != playerid) if(IsPlayerNearPlayer(playerid, i, 2.5)) 
			{
				if (i % 2 == 0) {
				format(frmxt, sizeof(frmxt), "%s"WHITE"Player ID - (%d)\n", frmxt, i);
				}
				else {
					format(frmxt, sizeof(frmxt), "%s"GRAY"Player ID - (%d)\n", frmxt, i);
				}
				NearestUser[playerid][count++] = i;
			}

			if(count > 0)
			{
				Dialog_Show(playerid, "ShowToSKCK", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- SKCK", 
				frmxt, "Pilih", "Batal");
			}
		}
		case 8: //lihat SKWB
		{
			if(!DocumentInfo[playerid][SKWB]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki SKWB/Expired!");
			new frmtxs[1080];
			format(frmtxs, sizeof(frmtxs), ""WHITE"========== SURAT KETERANGAN WARGA BARU ==========\n\
			Pernyataan resmi dari Pemerintah Daerah Pahlawan Roleplay\n\n\
			PETUGAS\n\
			Nama:\n\
			"YELLOW"%s\n\
			"WHITE"Jabatan:\n\
			"YELLOW"%s\n\n\
			"WHITE"BIODATA DI BAWAH INI\n\
			Nama:\t\tJenis Kelamin:\n\
			%s\t%s\n\
			Usia:\n\
			%d Tahun\n\
			Tanggal Pernyataan:\n\
			"AQUAMARINE"%s\n\n\
			"WHITE"Menerangkan bahwa:\n\
			"ORANGE"%s\n\n\
			"WHITE"KETERANGAN & TANDA TANGAN\n\
			Bahwa surat ini dinyatakan sah di mata negara dan hukum.\n\
			Warga yang disebutkan di atas memiliki hak penuh untuk\n\
			mendapatkan pendidikan dan keuntungan tertentu sebagaimana mestinya.\n\
			Apabila warga yang telah disebutkan melanggar hukum negara atau\n\
			membuat perilaku yang melanggar aturan kota maka surat ini dapat ditarik kembali.\n\
			Masa Berlaku: "AQUAMARINE"%s\n\n\
			"WHITE"- %s -",
			DocumentInfo[playerid][SKWBIssuer],
			DocumentInfo[playerid][SKWBIssuerRank],
			GetPlayerRoleplayName(playerid),
			(AccountData[playerid][pGender] == 1) ? ("Laki-Laki") : ("Perempuan"),
			AccountData[playerid][pAge],
			DocumentInfo[playerid][SKWBIssueDate],
			DocumentInfo[playerid][SKWBText],
			ReturnTimelapse(gettime(), DocumentInfo[playerid][SKWBDur], ""DARKRED"Habis"),
			DocumentInfo[playerid][SKWBIssuer]);
			Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Surat SKWB", 
			frmtxs, "Tutup", "");
		}
		case 9: //Tunjukkan SKWB
		{
			if(!DocumentInfo[playerid][SKWB]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki SKWB/Expired!");

			new count = 0, frmxt[522];
			foreach(new i : Player) if(i != playerid) if(IsPlayerNearPlayer(playerid, i, 2.5)) 
			{
				if (i % 2 == 0) {
				format(frmxt, sizeof(frmxt), "%s"WHITE"Kantong - (%d)\n", frmxt, i);
				}
				else {
					format(frmxt, sizeof(frmxt), "%s"GRAY"Kantong - (%d)\n", frmxt, i);
				}
				NearestUser[playerid][count++] = i;
			}

			if(count > 0)
			{
				Dialog_Show(playerid, "ShowToSKWB", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Tunjukkan SKWB", 
				frmxt, "Pilih", "Batal");
			}
		}
		case 10: //lihat Surat Psikologi
		{
			if(!DocumentInfo[playerid][SP]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Surat Psikologi!");
			new frmtxs[1080];
			format(frmtxs, sizeof(frmtxs), ""WHITE"========== SURAT PSIKOLOGI ==========\n\
			Pernyataan resmi dari Paramedis Pahlawan Roleplay\n\n\
			PETUGAS\n\
			Nama:\n\
			"YELLOW"%s\n\
			"WHITE"Jabatan:\n\
			"YELLOW"%s\n\n\
			"WHITE"BIODATA DI BAWAH INI\n\
			Nama:\t\tJenis Kelamin:\n\
			%s\t%s\n\
			Usia:\n\
			%d Tahun\n\
			Tanggal Pernyataan:\n\
			"AQUAMARINE"%s\n\n\
			"WHITE"Menerangkan bahwa:\n\
			"ORANGE"%s\n\n\
			"WHITE"KETERANGAN & TANDA TANGAN\n\
			Bahwa surat ini dinyatakan sah di mata hukum dan negara.\n\
			Masa Berlaku: "AQUAMARINE"%s\n\n\
			"WHITE"- %s -",
			DocumentInfo[playerid][SPIssuer],
			DocumentInfo[playerid][SPIssuerRank],
			GetPlayerRoleplayName(playerid),
			(AccountData[playerid][pGender] == 1) ? ("Laki-Laki") : ("Perempuan"),
			AccountData[playerid][pAge],
			DocumentInfo[playerid][SPIssueDate],
			DocumentInfo[playerid][SPText],
			ReturnTimelapse(gettime(), DocumentInfo[playerid][SPDur], ""DARKRED"Habis"),
			DocumentInfo[playerid][SPIssuer]);
			Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Surat Psikologi", 
			frmtxs, "Tutup", "");

		}
		case 11: //Tunjukkan SP
		{
			if(!DocumentInfo[playerid][SP]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Surat Psikologi!");

			new count = 0, frmxt[522];
			foreach(new i : Player) if(i != playerid) if(IsPlayerNearPlayer(playerid, i, 2.5)) 
			{
				if (i % 2 == 0) {
				format(frmxt, sizeof(frmxt), "%s"WHITE"Player ID - (%d)\n", frmxt, i);
				}
				else {
					format(frmxt, sizeof(frmxt), "%s"GRAY"Player ID - (%d)\n", frmxt, i);
				}
				NearestUser[playerid][count++] = i;
			}

			if(count > 0)
			{
				Dialog_Show(playerid, "ShowToSP", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Tunjukkan Surat Psikologi", 
				frmxt, "Pilih", "Batal");
			}
		}
	}
	return 1;
}

Dialog:ShowToBPJS(playerid, response, listitem, inputtext[])
{
	if(!response) 
	{
		for(new x; x < 100; x++)
		{
			NearestUser[playerid][x] = INVALID_PLAYER_ID;
		}
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		return 1;
	}
	if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih apapun!");

	static targetid;
	targetid = NearestUser[playerid][listitem];

	if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(!IsPlayerNearPlayer(playerid, targetid, 3.5)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak dekat dengan anda!");

	PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);

	ShowBPJSTD(playerid, targetid);
	SendClientMessage(targetid, Y_PAHLAWAN, "<!> "WHITE"Untuk menyembunyikan textdraw saat ini, gunakan "CMDEA"'/hidektd' "WHITE"sebagai CMD.");
	return 1;
}

Dialog:ShowToSKS(playerid, response, listitem, inputtext[])
{
	if(!response) 
	{
		for(new x; x < 100; x++)
		{
			NearestUser[playerid][x] = INVALID_PLAYER_ID;
		}
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		return 1;
	}
	if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih apapun!");

	static targetid;
	targetid = NearestUser[playerid][listitem];

	if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(!IsPlayerNearPlayer(playerid, targetid, 3.5)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak dekat dengan anda!");

	PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);

	new frmtxs[1080];
	format(frmtxs, sizeof(frmtxs), ""WHITE"========== SURAT KETERANGAN SEHAT ==========\n\
	Pernyataan resmi dari RSU. Mitra Pahlawan Roleplay\n\n\
	PETUGAS\n\
	Nama:\n\
	"YELLOW"%s\n\
	"WHITE"Jabatan:\n\
	"YELLOW"%s\n\n\
	"WHITE"BIODATA DI BAWAH INI\n\
	Nama:\t\tJenis Kelamin:\n\
	%s\t%s\n\
	Usia:\n\
	%d Tahun\n\
	Tanggal Pernyataan:\n\
	"AQUAMARINE"%s\n\n\
	"WHITE"Menerangkan bahwa:\n\
	"ORANGE"%s\n\n\
	"WHITE"KETERANGAN & TANDA TANGAN\n\
	Bahwa surat ini dinyatakan sah di mata negara dan hukum.\n\
	Masa Berlaku: "AQUAMARINE"%s\n\n\
	"WHITE"- %s -",
	DocumentInfo[playerid][SKSIssuer],
	DocumentInfo[playerid][SKSIssuerRank],
	GetPlayerRoleplayName(playerid),
	(AccountData[playerid][pGender] == 1) ? ("Laki-Laki") : ("Perempuan"),
	AccountData[playerid][pAge],
	DocumentInfo[playerid][SKSIssueDate],
	DocumentInfo[playerid][SKSText],
	ReturnTimelapse(gettime(), DocumentInfo[playerid][SKSDur], ""DARKRED"Habis"),
	DocumentInfo[playerid][SKSIssuer]);
	Dialog_Show(targetid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- SKS", 
	frmtxs, "Tutup", "");
	return 1;
}

Dialog:ShowToSP(playerid, response, listitem, inputtext[])
{
	if(!response) 
	{
		for(new x; x < 100; x++)
		{
			NearestUser[playerid][x] = INVALID_PLAYER_ID;
		}
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		return 1;
	}
	if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih apapun!");

	static targetid;
	targetid = NearestUser[playerid][listitem];

	if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(!IsPlayerNearPlayer(playerid, targetid, 3.5)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak dekat dengan anda!");

	PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);

	new frmtxs[1080];
	format(frmtxs, sizeof(frmtxs), ""WHITE"========== SURAT PSIKOLOGI ==========\n\
	Pernyataan resmi dari Paramedis Pahlawan Roleplay\n\n\
	PETUGAS\n\
	Nama:\n\
	"YELLOW"%s\n\
	"WHITE"Jabatan:\n\
	"YELLOW"%s\n\n\
	"WHITE"BIODATA DI BAWAH INI\n\
	Nama:\t\tJenis Kelamin:\n\
	%s\t%s\n\
	Usia:\n\
	%d Tahun\n\
	Tanggal Pernyataan:\n\
	"AQUAMARINE"%s\n\n\
	"WHITE"Menerangkan bahwa:\n\
	"ORANGE"%s\n\n\
	"WHITE"KETERANGAN & TANDA TANGAN\n\
	Bahwa surat ini dinyatakan sah di mata hukum dan negara.\n\
	Masa Berlaku: "AQUAMARINE"%s\n\n\
	"WHITE"- %s -",
	DocumentInfo[playerid][SPIssuer],
	DocumentInfo[playerid][SPIssuerRank],
	GetPlayerRoleplayName(playerid),
	(AccountData[playerid][pGender] == 1) ? ("Laki-Laki") : ("Perempuan"),
	AccountData[playerid][pAge],
	DocumentInfo[playerid][SPIssueDate],
	DocumentInfo[playerid][SPText],
	ReturnTimelapse(gettime(), DocumentInfo[playerid][SPDur], ""DARKRED"Habis"),
	DocumentInfo[playerid][SPIssuer]);
	Dialog_Show(targetid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Surat Psikologi", 
	frmtxs, "Tutup", "");
	return 1;
}

Dialog:ShowToSKCK(playerid, response, listitem, inputtext[])
{
	if(!response) 
	{
		for(new x; x < 100; x++)
		{
			NearestUser[playerid][x] = INVALID_PLAYER_ID;
		}
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		return 1;
	}
	if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih apapun!");

	static targetid;
	targetid = NearestUser[playerid][listitem];

	if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(!IsPlayerNearPlayer(playerid, targetid, 3.5)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak dekat dengan anda!");

	PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);

	new frmtxs[1080];
	format(frmtxs, sizeof(frmtxs), ""WHITE"========== SURAT KETERANGAN CATATAN KEPOLISIAN ==========\n\
	Dengan ini Kepolisian Daerah Pahlawan Roleplay telah merilis\n\
	keterangan catatan kepolisian bagi yang berdata diri di bawah ini:\n\n\
	Nama Lengkap: "YELLOW"%s\n\
	"WHITE"Usia: "YELLOW"%d Tahun\n\n\
	"WHITE"Tanggal Pernyataan:\n\
	"CYAN"%s\n\
	"WHITE"Dinyatakan bahwa yang bersangkutan:\n\
	"ORANGE"%s\n\n\
	"WHITE"Surat ini dinyatakan sah di mata negara dan hukum.\n\
	Masa Berlaku: "CYAN"%s\n\n\
	"WHITE"Hormat,\n\
	%s %s\n\
	Sentra Pelayanan Kepolisian Terpadu.",
	GetPlayerRoleplayName(playerid),
	AccountData[playerid][pAge],
	DocumentInfo[playerid][SKCKIssueDate],
	DocumentInfo[playerid][SKCKText],
	ReturnTimelapse(gettime(), DocumentInfo[playerid][SKCKDur], ""DARKRED"Habis"),
	DocumentInfo[playerid][SKCKIssuerRank],
	DocumentInfo[playerid][SKCKIssuer]);
	Dialog_Show(targetid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- SKCK", 
	frmtxs, "Tutup", "");
	return 1;
}

Dialog:ShowToSKWB(playerid, response, listitem, inputtext[])
{
	if(!response) 
	{
		for(new x; x < 100; x++)
		{
			NearestUser[playerid][x] = INVALID_PLAYER_ID;
		}
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		return 1;
	}
	if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih apapun!");

	static targetid;
	targetid = NearestUser[playerid][listitem];

	if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(!IsPlayerNearPlayer(playerid, targetid, 3.5)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak dekat dengan anda!");

	PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);

	new frmtxs[1080];
	format(frmtxs, sizeof(frmtxs), ""WHITE"========== SURAT KETERANGAN WARGA BARU ==========\n\
	Pernyataan resmi dari Pemerintah Kota Pahlawan Roleplay\n\n\
	PETUGAS\n\
	Nama:\n\
	"YELLOW"%s\n\
	"WHITE"Jabatan:\n\
	"YELLOW"%s\n\n\
	"WHITE"BIODATA DI BAWAH INI\n\
	Nama:\t\tJenis Kelamin:\n\
	%s\t%s\n\
	Usia:\n\
	%d Tahun\n\
	Tanggal Pernyataan:\n\
	"AQUAMARINE"%s\n\n\
	"WHITE"Menerangkan bahwa:\n\
	"ORANGE"%s\n\n\
	"WHITE"KETERANGAN & TANDA TANGAN\n\
	Bahwa surat ini dinyatakan sah di mata negara dan hukum.\n\
	Warga yang disebutkan di atas memiliki hak penuh untuk\n\
	mendapatkan pendidikan dan keuntungan tertentu sebagaimana mestinya.\n\
	Apabila warga yang telah disebutkan melanggar hukum negara atau\n\
	membuat perilaku yang melanggar aturan kota maka surat ini dapat ditarik kembali.\n\
	Masa Berlaku: "AQUAMARINE"%s\n\n\
	"WHITE"- %s -",
	DocumentInfo[playerid][SKWBIssuer],
	DocumentInfo[playerid][SKWBIssuerRank],
	GetPlayerRoleplayName(playerid),
	(AccountData[playerid][pGender] == 1) ? ("Laki-Laki") : ("Perempuan"),
	AccountData[playerid][pAge],
	DocumentInfo[playerid][SKWBIssueDate],
	DocumentInfo[playerid][SKWBText],
	ReturnTimelapse(gettime(), DocumentInfo[playerid][SKWBDur], ""DARKRED"Habis"),
	DocumentInfo[playerid][SKWBIssuer]);
	Dialog_Show(targetid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Surat SKWB", 
	frmtxs, "Tutup", "");
	return 1;
}

Dialog:MySlipSalary(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(AccountData[playerid][pSlipSalary] < 1000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal nilai total slip gaji yang dapat dicairkan adalah $10.00!");

	GivePlayerMoneyEx(playerid, AccountData[playerid][pSlipSalary]);
	ShowItemBox(playerid, "Cash", sprintf("Received $%sx", FormatMoney(AccountData[playerid][pSlipSalary])), 1212, 4);
	AccountData[playerid][pSlipSalary] = 0;
	PlayerPlaySound(playerid, 4201, 0.0, 0.0, 0.0);
	return 1;
}

Dialog:MyAVTreasure(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(listitem < 4 || listitem > 7) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memilih pilihan tersebut!");

	// switch(listitem)
	// {
	// 	case 4: //intero chest
	// 	{
	// 		Dialog_Show(playerid, DIALOG_OPENAVTREASURE, DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- avTreasure", 
	// 		""WHITE"Anda akan membuka "YELLOW"AV Intero Treasure.\n\
	// 		"WHITE"Untuk membukanya anda perlu "CYAN"1x AV Intero Key.\n\
	// 		"WHITE"Apabila anda tidak memilikinya, anda dapat membelinya seharga "GREEN"Rp. 25.000,- (donasi)\n\n\
	// 		"GOLD"Probabilitas konten yang ada di dalamnya:\n\
	// 		* Makanan/Minuman *\n\
	// 		* Uang $100 - $500 *\n\
	// 		"YELLOW"(Apakah anda ingin membukanya?)", "Buka", "Batal");
	// 	}
	// 	case 5: //flagtuf chest
	// 	{
	// 		Dialog_Show(playerid, DIALOG_OPENAVTREASURE, DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- avTreasure", 
	// 		""WHITE"Anda akan membuka "YELLOW"AV Flagtuf Treasure.\n\
	// 		"WHITE"Untuk membukanya anda perlu "CYAN"1x AV Flagtuf Key.\n\
	// 		"WHITE"Apabila anda tidak memilikinya, anda dapat membelinya seharga "GREEN"Rp. 50.000,- (donasi)\n\n\
	// 		"YELLOW"(Apakah anda ingin membukanya?)", "Buka", "Batal");
	// 	}
	// 	case 6: //Fancious chest
	// 	{
	// 		Dialog_Show(playerid, DIALOG_OPENAVTREASURE, DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- avTreasure", 
	// 		""WHITE"Anda akan membuka "YELLOW"AV Fancious Treasure.\n\
	// 		"WHITE"Untuk membukanya anda perlu "CYAN"1x AV Fancious Key.\n\
	// 		"WHITE"Apabila anda tidak memilikinya, anda dapat membelinya seharga "GREEN"Rp. 100.000,- (donasi)\n\n\
	// 		"YELLOW"(Apakah anda ingin membukanya?)", "Buka", "Batal");
	// 	}
	// 	case 7: //Rareous chest
	// 	{
	// 		Dialog_Show(playerid, DIALOG_OPENAVTREASURE, DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- avTreasure", 
	// 		""WHITE"Anda akan membuka "YELLOW"AV Rareous Treasure.\n\
	// 		"WHITE"Untuk membukanya anda perlu "CYAN"1x AV Rareous Key.\n\
	// 		"WHITE"Apabila anda tidak memilikinya, anda dapat membelinya seharga "GREEN"Rp. 200.000,- (donasi)\n\n\
	// 		"YELLOW"(Apakah anda ingin membukanya?)", "Buka", "Batal");
	// 	}
	// }
	return 1;
}

Dialog:PecelLeleCatalog(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	switch(listitem)
	{
		case 0:
		{
			if(AccountData[playerid][pMoney] < 4575) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

			TakePlayerMoneyEx(playerid, 4575);
			ShowItemBox(playerid, "Cash", "Removed $45.75x", 1212, 6);

			AccountData[playerid][pHunger] += 20;
			ShowTDN(playerid, NOTIFICATION_INFO, "Anda membeli dan langsung memakan Pecel Lele di tempat.");
		}
		case 1:
		{
			if(AccountData[playerid][pMoney] < 3768) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

			TakePlayerMoneyEx(playerid, 3768);
			ShowItemBox(playerid, "Cash", "Removed $37.68x", 1212, 6);

			AccountData[playerid][pThirst] += 20;
			ShowTDN(playerid, NOTIFICATION_INFO, "Anda membeli dan langsung meminum Teh Manis Dingin di tempat.");
		}
	}
	return 1;
}

//FACTION & COMPANY
Dialog:MechanicMenu(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	new carid = AccountData[playerid][pTempVehIterID];
	if(carid == -1) return 1;

	switch(listitem)
	{
		case 0: //repair engine
		{
			if(!PlayerHasItem(playerid, "Obeng")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Obeng!");
			if(Inventory_Count(playerid, "Komponen") < CountEngineCompoCost(carid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Komponen anda tidak cukup!");
			if(!PlayerHasItem(playerid, "Part Mesin")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Part Mesin!");

			new brokenObeng = RandomEx(0, 100);
			switch(brokenObeng)
			{
				case 99:
				{
					Inventory_Remove(playerid, "Obeng");
					return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah merusak Obeng secara tidak sengaja.");
				}
			}

			Inventory_Remove(playerid, "Komponen", CountEngineCompoCost(carid));
			Inventory_Remove(playerid, "Part Mesin");

			AccountData[playerid][pTempValue] = CountEngineCompoCost(carid);
			AccountData[playerid][pTempVehID] = PlayerVehicle[carid][pVehPhysic];

			ApplyAnimation(playerid, "CAR", "Fixn_Car_Loop", 5.00, true, false, false, false, 0, true);
			ShowItemBox(playerid, "Komponen", sprintf("Removed %dx", CountEngineCompoCost(carid)), 2040, 5);
			ShowItemBox(playerid, "Part Mesin", "Removed 1x", 19917, 6);

			AccountData[playerid][pActivityTime] = 1;
			PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMPERBAIKI");
			ShowProgressBar(playerid);

			Inventory_Close(playerid);

			pMechRepairEngineTimer[playerid] = true;
		}
		case 1: //repair body
		{
			if(!PlayerHasItem(playerid, "Obeng")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Obeng!");
			if(Inventory_Count(playerid, "Komponen") < CountBodyCompoCost(carid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Komponen anda tidak cukup!");
			if(!PlayerHasItem(playerid, "Part Body")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Part Body!");

			new brokenObeng = RandomEx(0, 100);
			switch(brokenObeng)
			{
				case 99:
				{
					Inventory_Remove(playerid, "Obeng");
					return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah merusak Obeng secara tidak sengaja.");
				}
			}

			Inventory_Remove(playerid, "Komponen", CountBodyCompoCost(carid));
			Inventory_Remove(playerid, "Part Body");
			AccountData[playerid][pTempValue] = CountBodyCompoCost(carid);
			AccountData[playerid][pTempVehID] = PlayerVehicle[carid][pVehPhysic];

			ApplyAnimation(playerid, "CAR", "Fixn_Car_Loop", 5.00, true, false, false, false, 0, true);
			ShowItemBox(playerid, "Komponen", sprintf("Removed %dx", CountBodyCompoCost(carid)), 2040, 5);
			ShowItemBox(playerid, "Part Body", "Removed 1x", 1141, 6);

			AccountData[playerid][pActivityTime] = 1;
			PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMPERBAIKI");
			ShowProgressBar(playerid);

			Inventory_Close(playerid);

			pMechRepairBodyTimer[playerid] = true;
		}
		case 2: //repair tire
		{
			if(!PlayerHasItem(playerid, "Obeng")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Obeng!");
			if(Inventory_Count(playerid, "Komponen") < CountTiresCompoCost(carid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Komponen anda tidak cukup!");
			if(!PlayerHasItem(playerid, "Ban Baru")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Ban Baru!");

			new brokenObeng = RandomEx(0, 100);
			switch(brokenObeng)
			{
				case 99:
				{
					Inventory_Remove(playerid, "Obeng");
					return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah merusak Obeng secara tidak sengaja.");
				}
			}

			Inventory_Remove(playerid, "Komponen", CountTiresCompoCost(carid));
			Inventory_Remove(playerid, "Ban Baru");

			AccountData[playerid][pTempValue] = CountTiresCompoCost(carid);
			AccountData[playerid][pTempVehID] = PlayerVehicle[carid][pVehPhysic];
			ApplyAnimation(playerid, "CAR", "Fixn_Car_Loop", 5.00, true, false, false, false, 0, true);
			ShowItemBox(playerid, "Komponen", sprintf("Removed %dx", CountTiresCompoCost(carid)), 2040, 5);
			ShowItemBox(playerid, "Ban Baru", "Removed 1x", 1083, 6);

			AccountData[playerid][pActivityTime] = 1;
			PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMPERBAIKI");
			ShowProgressBar(playerid);

			Inventory_Close(playerid);

			pMechRepairTiresTimer[playerid] = true;
		}
		case 3: //repaint
		{
			if(Inventory_Count(playerid, "Komponen") < 75) return ShowTDN(playerid, NOTIFICATION_ERROR, "Komponen anda tidak cukup!");
			if(!PlayerHasItem(playerid, "Air Brush")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Air Brush!");
			
			if(AccountData[playerid][pFactionRank] < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Rank faction minimal adalah Amatir untuk akses ini!");
			AccountData[playerid][pTempVehID] = PlayerVehicle[carid][pVehPhysic];
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;

			Dialog_Show(playerid, "MechanicRespray", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Repaint", 
			""WHITE"Mohon masukkan warna primary dan warna secondary untuk kendaraan ini\n\
			Format: "YELLOW"[color 1] [color 2]\n\
			"WHITE"Contoh: "YELLOW"255 42", "Input", "Batal");
		}
		case 4: //paintjob
		{
			if(Inventory_Count(playerid, "Komponen") < 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Komponen anda tidak cukup!");
			if(!PlayerHasItem(playerid, "Air Brush")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Air Brush!");

			if(AccountData[playerid][pFactionRank] < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Rank faction minimal adalah Amatir untuk akses ini!");
			AccountData[playerid][pTempVehID] = PlayerVehicle[carid][pVehPhysic];

			Dialog_Show(playerid, "MechanicPaintjob", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Paintjob", "Mohon masukkan ID Paintjob:\n\
			Contoh: 0 - 2\n\
			Peringatan: Masukkan 3 apabila ingin menghapus paintjob!", "Set", "Batal");
		}
		case 5: //upgrade engine
		{
			if(!PlayerHasItem(playerid, "Obeng")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Obeng!");

			if(AccountData[playerid][pFactionRank] < 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Rank faction minimal adalah Ahli untuk akses ini!");

			new brokenObeng = RandomEx(0, 100);

			if(PlayerVehicle[carid][pVehMaxHealth] == 1000.00) //level 1
			{
				if(Inventory_Count(playerid, "Komponen") < 200) return ShowTDN(playerid, NOTIFICATION_ERROR, "Komponen anda tidak cukup!");
				
				switch(brokenObeng)
				{
					case 99:
					{
						Inventory_Remove(playerid, "Obeng");
						return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah merusak Obeng secara tidak sengaja.");
					}
				}

				Inventory_Remove(playerid, "Komponen", 200);

				AccountData[playerid][pTempValue] = 200;
				AccountData[playerid][pTempVehID] = PlayerVehicle[carid][pVehPhysic];

				ApplyAnimation(playerid, "CAR", "Fixn_Car_Loop", 5.00, true, false, false, false, 0, true);
				ShowItemBox(playerid, "Komponen", "Removed 150x", 2040, 5);

				AccountData[playerid][pActivityTime] = 1;
				PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENINGKATKAN");
				ShowProgressBar(playerid);

				Inventory_Close(playerid);

				pMechUpgradeEngine[playerid] = true;
			}
			else if(PlayerVehicle[carid][pVehMaxHealth] == 1500.00) //level 2
			{
				if(Inventory_Count(playerid, "Komponen") < 250) return ShowTDN(playerid, NOTIFICATION_ERROR, "Komponen anda tidak cukup!");

				switch(brokenObeng)
				{
					case 99:
					{
						Inventory_Remove(playerid, "Obeng");
						return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah merusak Obeng secara tidak sengaja.");
					}
				}

				Inventory_Remove(playerid, "Komponen", 250);

				AccountData[playerid][pTempValue] = 250;
				AccountData[playerid][pTempVehID] = PlayerVehicle[carid][pVehPhysic];

				ApplyAnimation(playerid, "CAR", "Fixn_Car_Loop", 5.00, true, false, false, false, 0, true);
				ShowItemBox(playerid, "Komponen", "Removed 250x", 2040, 5);

				AccountData[playerid][pActivityTime] = 1;
				PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENINGKATKAN");
				ShowProgressBar(playerid);

				Inventory_Close(playerid);

				pMechUpgradeEngine[playerid] = true;
			}
			else if(PlayerVehicle[carid][pVehMaxHealth] == 2000.00) //level 3
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini sudah mencapai maksimal level mesin!");
		}
		case 6: //upgrade body/armor
		{
			if(PlayerVehicle[carid][pVehBodyUpgraded])  return ShowTDN(playerid, NOTIFICATION_ERROR, "Body kendaraan ini sudah ditingkatkan!");
			if(!PlayerHasItem(playerid, "Obeng")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Obeng!");
			if(Inventory_Count(playerid, "Komponen") < 250) return ShowTDN(playerid, NOTIFICATION_ERROR, "Komponen anda tidak cukup!");

			if(AccountData[playerid][pFactionRank] < 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Rank faction minimal adalah Ahli untuk akses ini!");

			new brokenObeng = RandomEx(0, 100);
			switch(brokenObeng)
			{
				case 99:
				{
					Inventory_Remove(playerid, "Obeng");
					return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah merusak Obeng secara tidak sengaja.");
				}
			}

			Inventory_Remove(playerid, "Komponen", 250);

			AccountData[playerid][pTempValue] = 250;
			AccountData[playerid][pTempVehID] = PlayerVehicle[carid][pVehPhysic];

			ApplyAnimation(playerid, "CAR", "Fixn_Car_Loop", 5.00, true, false, false, false, 0, true);
			ShowItemBox(playerid, "Komponen", "Removed 250x", 2040, 5);

			AccountData[playerid][pActivityTime] = 1;
			PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENINGKATKAN");
			ShowProgressBar(playerid);

			Inventory_Close(playerid);

			pMechUpgradeBody[playerid] = true;
		}
		case 7: //modif
		{
			if(!PlayerHasItem(playerid, "Obeng")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Obeng!");
			if(Inventory_Count(playerid, "Komponen") < 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Komponen anda tidak cukup!");
			if(AccountData[playerid][pFactionRank] < 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Rank faction minimal adalah Amatir untuk akses ini!");
			AccountData[playerid][pTempVehID] = PlayerVehicle[carid][pVehPhysic];
			Dialog_Show(playerid, "MechanicModifCatalog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Modif", 
			"Name\tRequirements\n\
			Ganti Ban\t50 Komponen\n\
			"GRAY"Spoiler\t50 Komponen\n\
			Hood\t50 Komponen\n\
			"GRAY"Vents\t50 Komponen\n\
			Lights\t50 Komponen\n\
			"GRAY"Exhausts\t50 Komponen\n\
			Front Bumpers\t50 Komponen\n\
			"GRAY"Rear Bumpers\t50 Komponen\n\
			Roofs\t50 Komponen\n\
			"GRAY"Sideskirts\t50 Komponen\n\
			Bullbars\t50 Komponen\n\
			"GRAY"Stereo\t50 Komponen\n\
			Hydraulic\t50 Komponen\n\
			"GRAY"Nitro Level 1\t50 Komponen\n\
			Nitro Level 2\t50 Komponen\n\
			"GRAY"Nitro Level 3\t50 Komponen\n\
			Neon\t50 Komponen", "Pilih", "Batal");
		}
	}
	return 1;
}
Dialog:MechanicRespray(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
		AccountData[playerid][pMechTempComp1] = 0;
		AccountData[playerid][pMechTempComp2] = 0;
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		return 1;
	}

	if(AccountData[playerid][pTempVehID] == INVALID_VEHICLE_ID)
	{
		AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
		AccountData[playerid][pMechTempComp1] = 0;
		AccountData[playerid][pMechTempComp2] = 0;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid vehicle!");
	}

	if(!IsValidVehicle(AccountData[playerid][pTempVehID]))
	{
		AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
		AccountData[playerid][pMechTempComp1] = 0;
		AccountData[playerid][pMechTempComp2] = 0;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid vehicle!");
	}

	if(!IsPlayerNearVehicle(playerid, AccountData[playerid][pTempVehID], 4.0))
	{
		AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
		AccountData[playerid][pMechTempComp1] = 0;
		AccountData[playerid][pMechTempComp2] = 0;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan kendaraan tersebut!");
	}

	static color1, color2;
	if(sscanf(inputtext, "dd", color1, color2))
	{
		Dialog_Show(playerid, "MechanicRespray", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Repaint", 
		""WHITE"Mohon masukkan warna primary dan warna secondary untuk kendaraan ini\n\
		Format: "YELLOW"[color 1] [color 2]\n\
		"WHITE"Contoh: "YELLOW"255 42", "Input", "Batal");
		return 1;
	}

	if(color1 > 255 || color1 < 0)
	{
		AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
		AccountData[playerid][pMechTempComp1] = 0;
		AccountData[playerid][pMechTempComp2] = 0;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid color id! (0 - 255)");
	}

	if(color2 > 255 || color2 < 0)
	{
		AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
		AccountData[playerid][pMechTempComp1] = 0;
		AccountData[playerid][pMechTempComp2] = 0;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid color id! (0 - 255)");
	}

	new vehicleid = AccountData[playerid][pTempVehID];
	AccountData[playerid][pMechTempComp1] = color1;
	AccountData[playerid][pMechTempComp2] = color2;

	ChangeVehicleColor(vehicleid, AccountData[playerid][pMechTempComp1], AccountData[playerid][pMechTempComp2]);
	foreach(new ii : PvtVehicles)
	{
		if(vehicleid == PlayerVehicle[ii][pVehPhysic])
		{
			PlayerVehicle[ii][pVehColor1] = AccountData[playerid][pMechTempComp1];
			PlayerVehicle[ii][pVehColor2] = AccountData[playerid][pMechTempComp2];
		}
	}
	PlayerPlaySound(playerid, 5201, 0.0, 0.0, 0.0);

	Inventory_Remove(playerid, "Komponen", 75);
	Inventory_Remove(playerid, "Air Brush");

	ShowItemBox(playerid, "Komponen", "Removed 75x", 2040, 5);
	ShowItemBox(playerid, "Air Brush", "Removed 1x", 2752, 6);

	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengganti warna kendaraan ini.");
	AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
	AccountData[playerid][pMechTempComp1] = 0;
	AccountData[playerid][pMechTempComp2] = 0;
	return 1;
}
Dialog:MechanicPaintjob(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
		AccountData[playerid][pMechTempComp1] = 0;
		AccountData[playerid][pMechTempComp2] = 0;
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		return 1;
	}

	if(AccountData[playerid][pTempVehID] == INVALID_VEHICLE_ID)
	{
		AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
		AccountData[playerid][pMechTempComp1] = 0;
		AccountData[playerid][pMechTempComp2] = 0;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid vehicle!");
	}

	if(!IsValidVehicle(AccountData[playerid][pTempVehID]))
	{
		AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
		AccountData[playerid][pMechTempComp1] = 0;
		AccountData[playerid][pMechTempComp2] = 0;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid vehicle!");
	}

	if(!IsPlayerNearVehicle(playerid, AccountData[playerid][pTempVehID], 4.0))
	{
		AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
		AccountData[playerid][pMechTempComp1] = 0;
		AccountData[playerid][pMechTempComp2] = 0;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan kendaraan tersebut!");
	}

	if(isnull(inputtext))
	{
		AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
		AccountData[playerid][pMechTempComp1] = 0;
		AccountData[playerid][pMechTempComp2] = 0;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dikosongkan!");
	}

	if(!IsNumericEx(inputtext))
	{
		AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
		AccountData[playerid][pMechTempComp1] = 0;
		AccountData[playerid][pMechTempComp2] = 0;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Masukkan hanya angka!");
	}
	
	AccountData[playerid][pMechTempComp1] = strval(inputtext);

	if(AccountData[playerid][pMechTempComp1] < 0 || AccountData[playerid][pMechTempComp1] > 3)
	{
		AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
		AccountData[playerid][pMechTempComp1] = 0;
		AccountData[playerid][pMechTempComp2] = 0;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Masukkan hanya 0 - 3!");
	}

	new vehicleid = AccountData[playerid][pTempVehID];
	ChangeVehiclePaintjob(vehicleid, AccountData[playerid][pMechTempComp1]);
	foreach(new ii : PvtVehicles)
	{
		if(vehicleid == PlayerVehicle[ii][pVehPhysic])
		{
			PlayerVehicle[ii][pVehPaintjob] = AccountData[playerid][pMechTempComp1];
		}
	}
	
	Inventory_Remove(playerid, "Komponen", 100);
	Inventory_Remove(playerid, "Air Brush");

	ShowItemBox(playerid, "Komponen", "Removed 100x", 2040, 5);
	ShowItemBox(playerid, "Air Brush", "Removed 1x", 2752, 6);

	ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah paintjob kendaraan ini.");
	AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
	AccountData[playerid][pMechTempComp1] = 0;
	AccountData[playerid][pMechTempComp2] = 0;
	return 1;
}
Dialog:MechanicModifCatalog(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(!IsValidVehicle(AccountData[playerid][pTempVehID]))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid vehicle!");

	static Float:vX, Float:vY, Float:vZ;
	GetVehiclePos(AccountData[playerid][pTempVehID], vX, vY, vZ);
	if(!IsPlayerInRangeOfPoint(playerid, 4.0, vX, vY, vZ))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan kendaraan tersebut!");

	switch(listitem)
	{
		case 0: //ganti ban
		{
			Dialog_Show(playerid, "MechanicModWheel", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Ban", 
			"Offroad\n"GRAY"Mega\nWires\n"GRAY"Twist\nGrove\n"GRAY"Import\nAtomic\n"GRAY"Ahab\nVirtual\n"GRAY"Access\nTrance\n"GRAY"Shadow\nRimshine\n"GRAY"Classic\nCutter\n"GRAY"Switch\nDollar", "Pilih", "Batal");
		}
		case 1: //spoiler
		{
			Dialog_Show(playerid, "MechanicModSpoiler", DIALOG_STYLE_TABLIST_HEADERS,"{DA9100}Pahlawan Roleplay "WHITE"- Spoiler",
			"Spoiler\tJenis Modshop\n\
			Alien\tWheel Arch\n\
			"GRAY"X-Flow\t"GRAY"Wheel Arch\n\
			Win\tTransfender\n\
			"GRAY"Fury\t"GRAY"Transfender\n\
			Alpha\tTransfender\n\
			"GRAY"Pro\t"GRAY"Transfender\n\
			Champ\tTransfender\n\
			"GRAY"Race\t"GRAY"Transfender\n\
			Drag\tTransfender","Pilih","Batal");
		}
		case 2: //hood
		{
			Dialog_Show(playerid, "MechanicModHood", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Hood", "Fury\n"GRAY"Champ\nRace\n"GRAY"Worx", "Pilih", "Batal");
		}
		case 3: //vent
		{
			Dialog_Show(playerid, "MechanicModVent", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Vent", "Oval\n"GRAY"Square", "Pilih", "Batal");
		}
		case 4: //lights
		{
			Dialog_Show(playerid, "MechanicModLight", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Light", "Round\n"GRAY"Square", "Pilih", "Batal");
		}
		case 5: //exhaust
		{
			Dialog_Show(playerid, "MechanicModExhaust", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Exhaust", 
			"Exhaust\tJenis Modshop\n\
			Alien\tWheel Arch\n\
			"GRAY"X-Flow\t"GRAY"Wheel Arch\n\
			Chromer\tLoco Low\n\
			"GRAY"Slamin\t"GRAY"Loco Low\n\
			Large\tTransfender\n\
			"GRAY"Medium\t"GRAY"Transfender\n\
			Small\tTransfender\n\
			"GRAY"Twin\t"GRAY"Transfender\n\
			Upswept\tTransfender", "Pilih", "Batal");
		}
		case 6: //front bumper
		{
			Dialog_Show(playerid, "MechanicModFrontBump", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Front Bumpers", 
			"Front Bumper\tJenis Modshop\n\
			Alien\tWheel Arch\n\
			"GRAY"X-Flow\t"GRAY"Wheel Arch\n\
			Chromer\tLoco Low\n\
			"GRAY"Slamin\t"GRAY"Loco Low", "Pilih", "Batal");
		}
		case 7: //rear bumper
		{
			Dialog_Show(playerid, "MechanicModRearBump", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Rear Bumpers", 
			"Rear Bumper\tJenis Modshop\n\
			Alien\tWheel Arch\n\
			"GRAY"X-Flow\t"GRAY"Wheel Arch\n\
			Chromer\tLoco Low\n\
			"GRAY"Slamin\t"GRAY"Loco Low", "Pilih", "Batal");
		}
		case 8: //roofs
		{
			Dialog_Show(playerid, "MechanicModRoofs", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Roofs", 
			"Roof\tJenis Modshop\n\
			Alien\tWheel Arch\n\
			"GRAY"X-Flow\t"GRAY"Wheel Arch\n\
			Hardtop\tLoco Low\n\
			"GRAY"Softtop\t"GRAY"Loco Low\n\
			Scoop\tTransfender", "Pilih", "Batal");
		}
		case 9: //sideskirts
		{
			Dialog_Show(playerid, "MechanicModSideskirt", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Sideskirts", 
			"Sideskirts\tJenis Modshop\n\
			Alien\tWheel Arch\n\
			"GRAY"X-Flow\t"GRAY"Wheel Arch\n\
			Chrome Strip\tLoco Low\n\
			"GRAY"Chrome Flames\t"GRAY"Loco Low\n\
			Chrome Arches\tLoco Low\n\
			"GRAY"Chrome Trim\t"GRAY"Loco Low\n\
			Wheelcovers\tLoco Low\n\
			"GRAY"General\t"GRAY"Transfender", "Pilih", "Batal");
		}
		case 10: //bullbars
		{
			Dialog_Show(playerid, "MechanicModBullbar", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Bullbars", "Chrome Grill\n"GRAY"Chrome Bars\nChrome Lights\n"GRAY"Chrome Bullbar", "Pilih", "Batal");
		}
		case 11:  //stereo
		{
			AccountData[playerid][pMechTempComp1] = 1086;
			AccountData[playerid][pMechTempComp2] = 0;
			
			new vehicleid = AccountData[playerid][pTempVehID];

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}

			Inventory_Remove(playerid, "Komponen", 50);

			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang stereo pada kendaraan ini senilai ~b~50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 12: //hydraulic
		{
			AccountData[playerid][pMechTempComp1] = 1087;
			AccountData[playerid][pMechTempComp2] = 0;

			new vehicleid = AccountData[playerid][pTempVehID];

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
			
			Inventory_Remove(playerid, "Komponen", 50);

			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang hydraulic pada kendaraan ini senilai ~b~50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 13: //nitro lv1
		{
			AccountData[playerid][pMechTempComp1] = 1009;
			AccountData[playerid][pMechTempComp2] = 0;

			new vehicleid = AccountData[playerid][pTempVehID];
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}

			Inventory_Remove(playerid, "Komponen", 50);

			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang nitro level 1 pada kendaraan ini senilai ~b~50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 14: //nitro lv2
		{
			AccountData[playerid][pMechTempComp1] = 1008;
			AccountData[playerid][pMechTempComp2] = 0;

			new vehicleid = AccountData[playerid][pTempVehID];
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}

			Inventory_Remove(playerid, "Komponen", 50);

			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang nitro level 2 pada kendaraan ini senilai ~b~50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 15: //nitro lv3
		{
			AccountData[playerid][pMechTempComp1] = 1010;
			AccountData[playerid][pMechTempComp2] = 0;

			new vehicleid = AccountData[playerid][pTempVehID];
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			Inventory_Remove(playerid, "Komponen", 50);

			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang nitro level 3 pada kendaraan ini senilai ~b~50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 16: //neon
		{
			Dialog_Show(playerid, MechanicModNeon, DIALOG_STYLE_LIST,"{DA9100}Pahlawan Roleplay "WHITE"- Neon","Merah\n"GRAY"Biru\nHijau\n"GRAY"Kuning\nPink\n"GRAY"Putih\n"RED"(Hapus Neon)","Pilih","Batal");
		}
	}
	return 1;
}
Dialog:MechanicModWheel(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
		AccountData[playerid][pMechTempComp1] = 0;
		AccountData[playerid][pMechTempComp2] = 0;
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		return 1;
	}

	if(!IsValidVehicle(AccountData[playerid][pTempVehID]))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid vehicle!");

	static Float:vX, Float:vY, Float:vZ;
	GetVehiclePos(AccountData[playerid][pTempVehID], vX, vY, vZ);
	if(!IsPlayerInRangeOfPoint(playerid, 4.0, vX, vY, vZ))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan kendaraan tersebut!");

	new vehicleid = AccountData[playerid][pTempVehID];

	Inventory_Remove(playerid, "Komponen", 50);

	switch(listitem)
	{
		case 0:
		{
			AccountData[playerid][pMechTempComp1] = 1025;
			AccountData[playerid][pMechTempComp2] = 0;

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
			
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah ban kendaraan ini 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 1:
		{
			AccountData[playerid][pMechTempComp1] = 1074;
			AccountData[playerid][pMechTempComp2] = 0;

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
	
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah ban kendaraan ini 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 2:
		{
			AccountData[playerid][pMechTempComp1] = 1076;
			AccountData[playerid][pMechTempComp2] = 0;

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
	
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah ban kendaraan ini 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 3:
		{
			AccountData[playerid][pMechTempComp1] = 1078;
			AccountData[playerid][pMechTempComp2] = 0;

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
	
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah ban kendaraan ini 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 4:
		{
			AccountData[playerid][pMechTempComp1] = 1081;
			AccountData[playerid][pMechTempComp2] = 0;

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
	
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah ban kendaraan ini 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 5:
		{
			AccountData[playerid][pMechTempComp1] = 1082;
			AccountData[playerid][pMechTempComp2] = 0;

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
	
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah ban kendaraan ini 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 6:
		{
			AccountData[playerid][pMechTempComp1] = 1085;
			AccountData[playerid][pMechTempComp2] = 0;

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
	
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah ban kendaraan ini 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 7:
		{
			AccountData[playerid][pMechTempComp1] = 1096;
			AccountData[playerid][pMechTempComp2] = 0;

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
	
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah ban kendaraan ini 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 8:
		{
			AccountData[playerid][pMechTempComp1] = 1097;
			AccountData[playerid][pMechTempComp2] = 0;

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
	
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah ban kendaraan ini 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 9:
		{
			AccountData[playerid][pMechTempComp1] = 1098;
			AccountData[playerid][pMechTempComp2] = 0;

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
	
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah ban kendaraan ini 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 10:
		{
			AccountData[playerid][pMechTempComp1] = 1084;
			AccountData[playerid][pMechTempComp2] = 0;

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
	
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah ban kendaraan ini 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 11:
		{
			AccountData[playerid][pMechTempComp1] = 1073;
			AccountData[playerid][pMechTempComp2] = 0;

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
	
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah ban kendaraan ini 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 12:
		{
			AccountData[playerid][pMechTempComp1] = 1075;
			AccountData[playerid][pMechTempComp2] = 0;

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
	
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah ban kendaraan ini 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 13:
		{
			AccountData[playerid][pMechTempComp1] = 1077;
			AccountData[playerid][pMechTempComp2] = 0;

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
	
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah ban kendaraan ini 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 14:
		{
			AccountData[playerid][pMechTempComp1] = 1079;
			AccountData[playerid][pMechTempComp2] = 0;

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
	
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah ban kendaraan ini 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 15:
		{
			AccountData[playerid][pMechTempComp1] = 1080;
			AccountData[playerid][pMechTempComp2] = 0;

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
	
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah ban kendaraan ini 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 16:
		{
			AccountData[playerid][pMechTempComp1] = 1083;
			AccountData[playerid][pMechTempComp2] = 0;

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
	
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah ban kendaraan ini 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
	}
	return 1;
}
Dialog:MechanicModSpoiler(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
		AccountData[playerid][pMechTempComp1] = 0;
		AccountData[playerid][pMechTempComp2] = 0;
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		return 1;
	}

	if(!IsValidVehicle(AccountData[playerid][pTempVehID]))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid vehicle!");

	static Float:vX, Float:vY, Float:vZ;
	GetVehiclePos(AccountData[playerid][pTempVehID], vX, vY, vZ);
	if(!IsPlayerInRangeOfPoint(playerid, 4.0, vX, vY, vZ))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan kendaraan tersebut!");

	new vehicleid = AccountData[playerid][pTempVehID];

	Inventory_Remove(playerid, "Komponen", 50);

	switch(listitem)
	{
		case 0:
		{
			if(GetVehicleModel(vehicleid) == 562)
			{
				AccountData[playerid][pMechTempComp1] = 1147;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 565)
			{
				AccountData[playerid][pMechTempComp1] = 1049;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 559)
			{
				AccountData[playerid][pMechTempComp1] = 1162;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 561)
			{
				AccountData[playerid][pMechTempComp1] = 1058;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 558)
			{
				AccountData[playerid][pMechTempComp1] = 1164;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 560)
			{
				AccountData[playerid][pMechTempComp1] = 1138;
				AccountData[playerid][pMechTempComp2] = 0;
			}

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang spoiler seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 1:
		{
			if(GetVehicleModel(vehicleid) == 562)
			{
				AccountData[playerid][pMechTempComp1] = 1146;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 565)
			{
				AccountData[playerid][pMechTempComp1] = 1050;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 559)
			{
				AccountData[playerid][pMechTempComp1] = 1158;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 561)
			{
				AccountData[playerid][pMechTempComp1] = 1060;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 558)
			{
				AccountData[playerid][pMechTempComp1] = 1163;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 560)
			{
				AccountData[playerid][pMechTempComp1] = 1139;
				AccountData[playerid][pMechTempComp2] = 0;
			}

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang spoiler seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 2:
		{
			AccountData[playerid][pMechTempComp1] = 1001;
			AccountData[playerid][pMechTempComp2] = 0;
			
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang spoiler seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 3:
		{
			AccountData[playerid][pMechTempComp1] = 1023;
			AccountData[playerid][pMechTempComp2] = 0;
			
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}

			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang spoiler seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 4:
		{
			AccountData[playerid][pMechTempComp1] = 1003;
			AccountData[playerid][pMechTempComp2] = 0;

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang spoiler seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 5:
		{
			AccountData[playerid][pMechTempComp1] = 1000;
			AccountData[playerid][pMechTempComp2] = 0;
			
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang spoiler seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 6:
		{
			AccountData[playerid][pMechTempComp1] = 1014;
			AccountData[playerid][pMechTempComp2] = 0;
			
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang spoiler seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 7:
		{
			AccountData[playerid][pMechTempComp1] = 1015;
			AccountData[playerid][pMechTempComp2] = 0;
			
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang spoiler seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 8:
		{
			AccountData[playerid][pMechTempComp1] = 1002;
			AccountData[playerid][pMechTempComp2] = 0;
			
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang spoiler seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
	}
	return 1;
}
Dialog:MechanicModHood(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
		AccountData[playerid][pMechTempComp1] = 0;
		AccountData[playerid][pMechTempComp2] = 0;
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		return 1;
	}

	if(!IsValidVehicle(AccountData[playerid][pTempVehID]))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid vehicle!");

	static Float:vX, Float:vY, Float:vZ;
	GetVehiclePos(AccountData[playerid][pTempVehID], vX, vY, vZ);
	if(!IsPlayerInRangeOfPoint(playerid, 4.0, vX, vY, vZ))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan kendaraan tersebut!");

	new vehicleid = AccountData[playerid][pTempVehID];

	Inventory_Remove(playerid, "Komponen", 50);

	switch(listitem)
	{
		case 0:
		{
			AccountData[playerid][pMechTempComp1] = 1005;
			AccountData[playerid][pMechTempComp2] = 0;
			
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang hood kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 1:
		{
			AccountData[playerid][pMechTempComp1] = 1004;
			AccountData[playerid][pMechTempComp2] = 0;
			
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang hood kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 2:
		{
			AccountData[playerid][pMechTempComp1] = 1011;
			AccountData[playerid][pMechTempComp2] = 0;
			
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang hood kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 3:
		{
			AccountData[playerid][pMechTempComp1] = 1012;
			AccountData[playerid][pMechTempComp2] = 0;
			
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang hood kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
	}
	return 1;
}
Dialog:MechanicModVent(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
		AccountData[playerid][pMechTempComp1] = 0;
		AccountData[playerid][pMechTempComp2] = 0;
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		return 1;
	}

	if(!IsValidVehicle(AccountData[playerid][pTempVehID]))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid vehicle!");

	static Float:vX, Float:vY, Float:vZ;
	GetVehiclePos(AccountData[playerid][pTempVehID], vX, vY, vZ);
	if(!IsPlayerInRangeOfPoint(playerid, 4.0, vX, vY, vZ))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan kendaraan tersebut!");

	new vehicleid = AccountData[playerid][pTempVehID];

	Inventory_Remove(playerid, "Komponen", 50);

	switch(listitem)
	{
		case 0:
		{
			AccountData[playerid][pMechTempComp1] = 1142;
			AccountData[playerid][pMechTempComp2] = 1143;
			
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang vent kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 1:
		{
			AccountData[playerid][pMechTempComp1] = 1144;
			AccountData[playerid][pMechTempComp2] = 1145;
			
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang vent kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
	}
	return 1;
}
Dialog:MechanicModLight(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
		AccountData[playerid][pMechTempComp1] = 0;
		AccountData[playerid][pMechTempComp2] = 0;
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		return 1;
	}

	if(!IsValidVehicle(AccountData[playerid][pTempVehID]))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid vehicle!");

	static Float:vX, Float:vY, Float:vZ;
	GetVehiclePos(AccountData[playerid][pTempVehID], vX, vY, vZ);
	if(!IsPlayerInRangeOfPoint(playerid, 4.0, vX, vY, vZ))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan kendaraan tersebut!");

	new vehicleid = AccountData[playerid][pTempVehID];

	Inventory_Remove(playerid, "Komponen", 50);

	switch(listitem)
	{
		case 0:
		{
			AccountData[playerid][pMechTempComp1] = 1013;
			AccountData[playerid][pMechTempComp2] = 0;
			
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang lights kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 1:
		{
			AccountData[playerid][pMechTempComp1] = 1024;
			AccountData[playerid][pMechTempComp2] = 0;
			
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang lights kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
	}
	return 1;
}
Dialog:MechanicModExhaust(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
		AccountData[playerid][pMechTempComp1] = 0;
		AccountData[playerid][pMechTempComp2] = 0;
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		return 1;
	}

	if(!IsValidVehicle(AccountData[playerid][pTempVehID]))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid vehicle!");

	static Float:vX, Float:vY, Float:vZ;
	GetVehiclePos(AccountData[playerid][pTempVehID], vX, vY, vZ);
	if(!IsPlayerInRangeOfPoint(playerid, 4.0, vX, vY, vZ))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan kendaraan tersebut!");

	new vehicleid = AccountData[playerid][pTempVehID];

	Inventory_Remove(playerid, "Komponen", 50);

	switch(listitem)
	{
		case 0:
		{
			if(GetVehicleModel(vehicleid) == 562)
			{
				AccountData[playerid][pMechTempComp1] = 1034;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 565)
			{
				AccountData[playerid][pMechTempComp1] = 1046;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 559)
			{
				AccountData[playerid][pMechTempComp1] = 1065;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 561)
			{
				AccountData[playerid][pMechTempComp1] = 1064;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 560)
			{
				AccountData[playerid][pMechTempComp1] = 1028;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 558)
			{
				AccountData[playerid][pMechTempComp1] = 1089;
				AccountData[playerid][pMechTempComp2] = 0;
			}

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang exhaust kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 1:
		{
			if(GetVehicleModel(vehicleid) == 562)
			{
				AccountData[playerid][pMechTempComp1] = 1037;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 565)
			{
				AccountData[playerid][pMechTempComp1] = 1045;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 559)
			{
				AccountData[playerid][pMechTempComp1] = 1066;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 561)
			{
				AccountData[playerid][pMechTempComp1] = 1059;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 560)
			{
				AccountData[playerid][pMechTempComp1] = 1029;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 558)
			{
				AccountData[playerid][pMechTempComp1] = 1092;
				AccountData[playerid][pMechTempComp2] = 0;
			}

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang exhaust kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 2:
		{
			if(GetVehicleModel(vehicleid) == 575)
			{
				AccountData[playerid][pMechTempComp1] = 1044;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 534)
			{
				AccountData[playerid][pMechTempComp1] = 1126;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 567)
			{
				AccountData[playerid][pMechTempComp1] = 1129;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 536)
			{
				AccountData[playerid][pMechTempComp1] = 1104;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 576)
			{
				AccountData[playerid][pMechTempComp1] = 1113;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 535)
			{
				AccountData[playerid][pMechTempComp1] = 1136;
				AccountData[playerid][pMechTempComp2] = 0;
			}

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang exhaust kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 3:
		{
			if(GetVehicleModel(vehicleid) == 575)
			{
				AccountData[playerid][pMechTempComp1] = 1043;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 534)
			{
				AccountData[playerid][pMechTempComp1] = 1127;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 567)
			{
				AccountData[playerid][pMechTempComp1] = 1132;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 536)
			{
				AccountData[playerid][pMechTempComp1] = 1105;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 576)
			{
				AccountData[playerid][pMechTempComp1] = 1135;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 535)
			{
				AccountData[playerid][pMechTempComp1] = 1114;
				AccountData[playerid][pMechTempComp2] = 0;
			}

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang exhaust kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 4:
		{
			AccountData[playerid][pMechTempComp1] = 1020;
			AccountData[playerid][pMechTempComp2] = 0;
			
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang exhaust kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 5:
		{
			AccountData[playerid][pMechTempComp1] = 1021;
			AccountData[playerid][pMechTempComp2] = 0;
			
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang exhaust kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 6:
		{
			AccountData[playerid][pMechTempComp1] = 1022;
			AccountData[playerid][pMechTempComp2] = 0;
			
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang exhaust kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 7:
		{
			AccountData[playerid][pMechTempComp1] = 1019;
			AccountData[playerid][pMechTempComp2] = 0;
			
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang exhaust kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 8:
		{
			AccountData[playerid][pMechTempComp1] = 1018;
			AccountData[playerid][pMechTempComp2] = 0;
			
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang exhaust kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
	}
	return 1;
}
Dialog:MechanicModFrontBump(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
		AccountData[playerid][pMechTempComp1] = 0;
		AccountData[playerid][pMechTempComp2] = 0;
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		return 1;
	}

	if(!IsValidVehicle(AccountData[playerid][pTempVehID]))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid vehicle!");

	static Float:vX, Float:vY, Float:vZ;
	GetVehiclePos(AccountData[playerid][pTempVehID], vX, vY, vZ);
	if(!IsPlayerInRangeOfPoint(playerid, 4.0, vX, vY, vZ))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan kendaraan tersebut!");

	new vehicleid = AccountData[playerid][pTempVehID];

	Inventory_Remove(playerid, "Komponen", 50);
	
	switch(listitem)
	{
		case 0:
		{
			if(GetVehicleModel(vehicleid) == 562)
			{
				AccountData[playerid][pMechTempComp1] = 1171;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 565)
			{
				AccountData[playerid][pMechTempComp1] = 1153;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 559)
			{
				AccountData[playerid][pMechTempComp1] = 1160;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 561)
			{
				AccountData[playerid][pMechTempComp1] = 1155;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 558)
			{
				AccountData[playerid][pMechTempComp1] = 1166;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 560)
			{
				AccountData[playerid][pMechTempComp1] = 1169;
				AccountData[playerid][pMechTempComp2] = 0;
			}

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
			
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang bumper depan kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 1:
		{
			if(GetVehicleModel(vehicleid) == 562)
			{
				AccountData[playerid][pMechTempComp1] = 1172;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 565)
			{
				AccountData[playerid][pMechTempComp1] = 1152;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 559)
			{
				AccountData[playerid][pMechTempComp1] = 1173;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 561)
			{
				AccountData[playerid][pMechTempComp1] = 1157;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 558)
			{
				AccountData[playerid][pMechTempComp1] = 1165;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 560)
			{
				AccountData[playerid][pMechTempComp1] = 1170;
				AccountData[playerid][pMechTempComp2] = 0;
			}

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
			
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang bumper depan kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 2:
		{
			if(GetVehicleModel(vehicleid) == 575)
			{
				AccountData[playerid][pMechTempComp1] = 1174;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 534)
			{
				AccountData[playerid][pMechTempComp1] = 1179;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 567)
			{
				AccountData[playerid][pMechTempComp1] = 1189;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 536)
			{
				AccountData[playerid][pMechTempComp1] = 1182;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 576)
			{
				AccountData[playerid][pMechTempComp1] = 1191;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 535)
			{
				AccountData[playerid][pMechTempComp1] = 1115;
				AccountData[playerid][pMechTempComp2] = 0;
			}

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
			
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang bumper depan kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 3:
		{
			if(GetVehicleModel(vehicleid) == 575)
			{
				AccountData[playerid][pMechTempComp1] = 1175;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 534)
			{
				AccountData[playerid][pMechTempComp1] = 1185;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 567)
			{
				AccountData[playerid][pMechTempComp1] = 1188;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 536)
			{
				AccountData[playerid][pMechTempComp1] = 1181;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 576)
			{
				AccountData[playerid][pMechTempComp1] = 1190;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 535)
			{
				AccountData[playerid][pMechTempComp1] = 1116;
				AccountData[playerid][pMechTempComp2] = 0;
			}

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
			
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang bumper depan kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
	}
	return 1;
}
Dialog:MechanicModRearBump(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
		AccountData[playerid][pMechTempComp1] = 0;
		AccountData[playerid][pMechTempComp2] = 0;
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		return 1;
	}

	if(!IsValidVehicle(AccountData[playerid][pTempVehID]))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid vehicle!");

	static Float:vX, Float:vY, Float:vZ;
	GetVehiclePos(AccountData[playerid][pTempVehID], vX, vY, vZ);
	if(!IsPlayerInRangeOfPoint(playerid, 4.0, vX, vY, vZ))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan kendaraan tersebut!");

	new vehicleid = AccountData[playerid][pTempVehID];

	Inventory_Remove(playerid, "Komponen", 50);

	switch(listitem)
	{
		case 0:
		{
			if(GetVehicleModel(vehicleid) == 562)
			{
				AccountData[playerid][pMechTempComp1] = 1149;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 565)
			{
				AccountData[playerid][pMechTempComp1] = 1150;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 559)
			{
				AccountData[playerid][pMechTempComp1] = 1159;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 561)
			{
				AccountData[playerid][pMechTempComp1] = 1154;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 558)
			{
				AccountData[playerid][pMechTempComp1] = 1168;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 560)
			{
				AccountData[playerid][pMechTempComp1] = 1141;
				AccountData[playerid][pMechTempComp2] = 0;
			}

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
			
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang bumper belakang kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 1:
		{
			if(GetVehicleModel(vehicleid) == 562)
			{
				AccountData[playerid][pMechTempComp1] = 1148;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 565)
			{
				AccountData[playerid][pMechTempComp1] = 1151;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 559)
			{
				AccountData[playerid][pMechTempComp1] = 1161;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 561)
			{
				AccountData[playerid][pMechTempComp1] = 1156;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 558)
			{
				AccountData[playerid][pMechTempComp1] = 1167;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 560)
			{
				AccountData[playerid][pMechTempComp1] = 1140;
				AccountData[playerid][pMechTempComp2] = 0;
			}

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
			
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang bumper belakang kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 2:
		{
			if(GetVehicleModel(vehicleid) == 575)
			{
				AccountData[playerid][pMechTempComp1] = 1176;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 534)
			{
				AccountData[playerid][pMechTempComp1] = 1180;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 567)
			{
				AccountData[playerid][pMechTempComp1] = 1187;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 536)
			{
				AccountData[playerid][pMechTempComp1] = 1184;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 576)
			{
				AccountData[playerid][pMechTempComp1] = 1192;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 535)
			{
				AccountData[playerid][pMechTempComp1] = 1109;
				AccountData[playerid][pMechTempComp2] = 0;
			}

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
			
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang bumper belakang kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 3:
		{
			if(GetVehicleModel(vehicleid) == 575)
			{
				AccountData[playerid][pMechTempComp1] = 1177;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 534)
			{
				AccountData[playerid][pMechTempComp1] = 1178;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 567)
			{
				AccountData[playerid][pMechTempComp1] = 1186;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 536)
			{
				AccountData[playerid][pMechTempComp1] = 1183;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 576)
			{
				AccountData[playerid][pMechTempComp1] = 1193;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 535)
			{
				AccountData[playerid][pMechTempComp1] = 1110;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang bumper belakang kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
	}
	return 1;
}
Dialog:MechanicModRoofs(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
		AccountData[playerid][pMechTempComp1] = 0;
		AccountData[playerid][pMechTempComp2] = 0;
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		return 1;
	}

	if(!IsValidVehicle(AccountData[playerid][pTempVehID]))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid vehicle!");

	static Float:vX, Float:vY, Float:vZ;
	GetVehiclePos(AccountData[playerid][pTempVehID], vX, vY, vZ);
	if(!IsPlayerInRangeOfPoint(playerid, 4.0, vX, vY, vZ))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan kendaraan tersebut!");

	new vehicleid = AccountData[playerid][pTempVehID];

	Inventory_Remove(playerid, "Komponen", 50);
	switch(listitem)
	{
		case 0:
		{
			if(GetVehicleModel(vehicleid) == 562)
			{
				AccountData[playerid][pMechTempComp1] = 1038;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 565)
			{
				AccountData[playerid][pMechTempComp1] = 1054;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 559)
			{
				AccountData[playerid][pMechTempComp1] = 1067;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 561)
			{
				AccountData[playerid][pMechTempComp1] = 1055;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 558)
			{
				AccountData[playerid][pMechTempComp1] = 1088;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 560)
			{
				AccountData[playerid][pMechTempComp1] = 1032;
				AccountData[playerid][pMechTempComp2] = 0;
			}

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
			
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang roof kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 1:
		{
			if(GetVehicleModel(vehicleid) == 562)
			{
				AccountData[playerid][pMechTempComp1] = 1038;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 565)
			{
				AccountData[playerid][pMechTempComp1] = 1053;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 559)
			{
				AccountData[playerid][pMechTempComp1] = 1068;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 561)
			{
				AccountData[playerid][pMechTempComp1] = 1061;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 558)
			{
				AccountData[playerid][pMechTempComp1] = 1091;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 560)
			{
				AccountData[playerid][pMechTempComp1] = 1033;
				AccountData[playerid][pMechTempComp2] = 0;
			}

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
			
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang roof kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 2:
		{
			if(GetVehicleModel(vehicleid) == 567)
			{
				AccountData[playerid][pMechTempComp1] = 1130;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 536)
			{
				AccountData[playerid][pMechTempComp1] = 1128;
				AccountData[playerid][pMechTempComp2] = 0;
			}

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
			
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang roof kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 3:
		{
			if(GetVehicleModel(vehicleid) == 567)
			{
				AccountData[playerid][pMechTempComp1] = 1131;
				AccountData[playerid][pMechTempComp2] = 0;
			}
			if(GetVehicleModel(vehicleid) == 536)
			{
				AccountData[playerid][pMechTempComp1] = 1103;
				AccountData[playerid][pMechTempComp2] = 0;
			}

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
			
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang roof kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 4:
		{
			AccountData[playerid][pMechTempComp1] = 1006;
			AccountData[playerid][pMechTempComp2] = 0;

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang roof kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
	}
	return 1;
}
Dialog:MechanicModSideskirt(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
		AccountData[playerid][pMechTempComp1] = 0;
		AccountData[playerid][pMechTempComp2] = 0;
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		return 1;
	}

	if(!IsValidVehicle(AccountData[playerid][pTempVehID]))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid vehicle!");

	static Float:vX, Float:vY, Float:vZ;
	GetVehiclePos(AccountData[playerid][pTempVehID], vX, vY, vZ);
	if(!IsPlayerInRangeOfPoint(playerid, 4.0, vX, vY, vZ))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan kendaraan tersebut!");

	new vehicleid = AccountData[playerid][pTempVehID];

	Inventory_Remove(playerid, "Komponen", 50);
	switch(listitem)
	{
		case 0:
		{
			if(GetVehicleModel(vehicleid) == 562)
			{
				AccountData[playerid][pMechTempComp1] = 1036;
				AccountData[playerid][pMechTempComp2] = 1040;
			}
			if(GetVehicleModel(vehicleid) == 565)
			{
				AccountData[playerid][pMechTempComp1] = 1047;
				AccountData[playerid][pMechTempComp2] = 1051;
			}
			if(GetVehicleModel(vehicleid) == 559)
			{
				AccountData[playerid][pMechTempComp1] = 1069;
				AccountData[playerid][pMechTempComp2] = 1071;
			}
			if(GetVehicleModel(vehicleid) == 561)
			{
				AccountData[playerid][pMechTempComp1] = 1056;
				AccountData[playerid][pMechTempComp2] = 1062;
			}
			if(GetVehicleModel(vehicleid) == 558)
			{
				AccountData[playerid][pMechTempComp1] = 1090;
				AccountData[playerid][pMechTempComp2] = 1094;
			}
			if(GetVehicleModel(vehicleid) == 560)
			{
				AccountData[playerid][pMechTempComp1] = 1026;
				AccountData[playerid][pMechTempComp2] = 1027;
			}

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang sideskirts kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 1:
		{
			if(GetVehicleModel(vehicleid) == 562)
			{
				AccountData[playerid][pMechTempComp1] = 1039;
				AccountData[playerid][pMechTempComp2] = 1041;
			}
			if(GetVehicleModel(vehicleid) == 565)
			{
				AccountData[playerid][pMechTempComp1] = 1048;
				AccountData[playerid][pMechTempComp2] = 1052;
			}
			if(GetVehicleModel(vehicleid) == 559)
			{
				AccountData[playerid][pMechTempComp1] = 1070;
				AccountData[playerid][pMechTempComp2] = 1072;
			}
			if(GetVehicleModel(vehicleid) == 561)
			{
				AccountData[playerid][pMechTempComp1] = 1057;
				AccountData[playerid][pMechTempComp2] = 1063;
			}
			if(GetVehicleModel(vehicleid) == 558)
			{
				AccountData[playerid][pMechTempComp1] = 1093;
				AccountData[playerid][pMechTempComp2] = 1095;
			}
			if(GetVehicleModel(vehicleid) == 560)
			{
				AccountData[playerid][pMechTempComp1] = 1031;
				AccountData[playerid][pMechTempComp2] = 1030;
			}

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang sideskirts kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 2:
		{
			if(GetVehicleModel(vehicleid) == 575)
			{
				AccountData[playerid][pMechTempComp1] = 1042;
				AccountData[playerid][pMechTempComp2] = 1099;
			}
			if(GetVehicleModel(vehicleid) == 536)
			{
				AccountData[playerid][pMechTempComp1] = 1108;
				AccountData[playerid][pMechTempComp2] = 1107;
			}
			if(GetVehicleModel(vehicleid) == 576)
			{
				AccountData[playerid][pMechTempComp1] = 1134;
				AccountData[playerid][pMechTempComp2] = 1137;
			}
			if(GetVehicleModel(vehicleid) == 567)
			{
				AccountData[playerid][pMechTempComp1] = 1102;
				AccountData[playerid][pMechTempComp2] = 1133;
			}

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang sideskirts kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 3:
		{
			AccountData[playerid][pMechTempComp1] = 1102;
			AccountData[playerid][pMechTempComp2] = 1101;
			
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang sideskirts kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 4:
		{
			AccountData[playerid][pMechTempComp1] = 1106;
			AccountData[playerid][pMechTempComp2] = 1124;
			
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang sideskirts kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 5:
		{
			AccountData[playerid][pMechTempComp1] = 1118;
			AccountData[playerid][pMechTempComp2] = 1120;

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang sideskirts kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 6:
		{
			AccountData[playerid][pMechTempComp1] = 1119;
			AccountData[playerid][pMechTempComp2] = 1121;
			
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang sideskirts kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 7:
		{
			AccountData[playerid][pMechTempComp1] = 1007;
			AccountData[playerid][pMechTempComp2] = 1017;
			
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");

			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang sideskirts kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
	}
	return 1;
}
Dialog:MechanicModBullbar(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
		AccountData[playerid][pMechTempComp1] = 0;
		AccountData[playerid][pMechTempComp2] = 0;
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		return 1;
	}

	if(!IsValidVehicle(AccountData[playerid][pTempVehID]))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid vehicle!");

	static Float:vX, Float:vY, Float:vZ;
	GetVehiclePos(AccountData[playerid][pTempVehID], vX, vY, vZ);
	if(!IsPlayerInRangeOfPoint(playerid, 4.0, vX, vY, vZ))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan kendaraan tersebut!");

	new vehicleid = AccountData[playerid][pTempVehID];

	Inventory_Remove(playerid, "Komponen", 50);

	switch(listitem)
	{
		case 0:
		{
			AccountData[playerid][pMechTempComp1] = 1100;
			AccountData[playerid][pMechTempComp2] = 0;

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
			
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang bullbars kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 1:
		{
			AccountData[playerid][pMechTempComp1] = 1123;
			AccountData[playerid][pMechTempComp2] = 0;

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang bullbars kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 2:
		{
			AccountData[playerid][pMechTempComp1] = 1125;
			AccountData[playerid][pMechTempComp2] = 0;

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
			
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang bullbars kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 3:
		{
			AccountData[playerid][pMechTempComp1] = 1117;
			AccountData[playerid][pMechTempComp2] = 0;

			if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp1])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
			
			
			AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp1]);
			SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp1]);
			if(AccountData[playerid][pMechTempComp2] != 0)
			{
				if(!IsComponentidCompatible(GetVehicleModel(vehicleid), AccountData[playerid][pMechTempComp2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan ini tidak cocok dengan modifikasi tersebut!");
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechTempComp2]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechTempComp2]);
			}
	
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasang bullbars kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
	}
	return 1;
}
Dialog:MechanicModNeon(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
		AccountData[playerid][pMechTempComp1] = 0;
		AccountData[playerid][pMechTempComp2] = 0;
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		return 1;
	}

	if(!IsValidVehicle(AccountData[playerid][pTempVehID]))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid vehicle!");

	static Float:vX, Float:vY, Float:vZ;
	GetVehiclePos(AccountData[playerid][pTempVehID], vX, vY, vZ);
	if(!IsPlayerInRangeOfPoint(playerid, 4.0, vX, vY, vZ))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan kendaraan tersebut!");

	new vehicleid = AccountData[playerid][pTempVehID];

	Inventory_Remove(playerid, "Komponen", 50);

	switch(listitem)
	{
		case 0:
		{
			AccountData[playerid][pMechTempComp1] = RED_NEON;

			if(AccountData[playerid][pMechTempComp1] == 0)
			{
				SetVehicleNeonLights(vehicleid, false, AccountData[playerid][pMechTempComp1], 0);
			}
			else
			{
				SetVehicleNeonLights(vehicleid, true, AccountData[playerid][pMechTempComp1], 0);
			}

			foreach(new ii : PvtVehicles)
			{
				if(vehicleid == PlayerVehicle[ii][pVehPhysic])
				{
					PlayerVehicle[ii][pVehNeon] = AccountData[playerid][pMechTempComp1];
				}
			}
			
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah neon kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 1:
		{
			AccountData[playerid][pMechTempComp1] = BLUE_NEON;

			if(AccountData[playerid][pMechTempComp1] == 0)
			{
				SetVehicleNeonLights(vehicleid, false, AccountData[playerid][pMechTempComp1], 0);
			}
			else
			{
				SetVehicleNeonLights(vehicleid, true, AccountData[playerid][pMechTempComp1], 0);
			}

			foreach(new ii : PvtVehicles)
			{
				if(vehicleid == PlayerVehicle[ii][pVehPhysic])
				{
					PlayerVehicle[ii][pVehNeon] = AccountData[playerid][pMechTempComp1];
				}
			}
			
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah neon kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 2:
		{
			AccountData[playerid][pMechTempComp1] = GREEN_NEON;

			if(AccountData[playerid][pMechTempComp1] == 0)
			{
				SetVehicleNeonLights(vehicleid, false, AccountData[playerid][pMechTempComp1], 0);
			}
			else
			{
				SetVehicleNeonLights(vehicleid, true, AccountData[playerid][pMechTempComp1], 0);
			}

			foreach(new ii : PvtVehicles)
			{
				if(vehicleid == PlayerVehicle[ii][pVehPhysic])
				{
					PlayerVehicle[ii][pVehNeon] = AccountData[playerid][pMechTempComp1];
				}
			}
			
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah neon kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 3:
		{
			AccountData[playerid][pMechTempComp1] = YELLOW_NEON;

			if(AccountData[playerid][pMechTempComp1] == 0)
			{
				SetVehicleNeonLights(vehicleid, false, AccountData[playerid][pMechTempComp1], 0);
			}
			else
			{
				SetVehicleNeonLights(vehicleid, true, AccountData[playerid][pMechTempComp1], 0);
			}

			foreach(new ii : PvtVehicles)
			{
				if(vehicleid == PlayerVehicle[ii][pVehPhysic])
				{
					PlayerVehicle[ii][pVehNeon] = AccountData[playerid][pMechTempComp1];
				}
			}
			
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah neon kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 4:
		{
			AccountData[playerid][pMechTempComp1] = PINK_NEON;

			if(AccountData[playerid][pMechTempComp1] == 0)
			{
				SetVehicleNeonLights(vehicleid, false, AccountData[playerid][pMechTempComp1], 0);
			}
			else
			{
				SetVehicleNeonLights(vehicleid, true, AccountData[playerid][pMechTempComp1], 0);
			}

			foreach(new ii : PvtVehicles)
			{
				if(vehicleid == PlayerVehicle[ii][pVehPhysic])
				{
					PlayerVehicle[ii][pVehNeon] = AccountData[playerid][pMechTempComp1];
				}
			}
			
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah neon kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 5:
		{
			AccountData[playerid][pMechTempComp1] = WHITE_NEON;

			if(AccountData[playerid][pMechTempComp1] == 0)
			{
				SetVehicleNeonLights(vehicleid, false, AccountData[playerid][pMechTempComp1], 0);
			}
			else
			{
				SetVehicleNeonLights(vehicleid, true, AccountData[playerid][pMechTempComp1], 0);
			}

			foreach(new ii : PvtVehicles)
			{
				if(vehicleid == PlayerVehicle[ii][pVehPhysic])
				{
					PlayerVehicle[ii][pVehNeon] = AccountData[playerid][pMechTempComp1];
				}
			}
			
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah neon kendaraan seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
		case 6:
		{
			AccountData[playerid][pMechTempComp1] = 0;
			SetVehicleNeonLights(vehicleid, false, AccountData[playerid][pMechTempComp1], 0);

			foreach(new ii : PvtVehicles)
			{
				if(vehicleid == PlayerVehicle[ii][pVehPhysic])
				{
					PlayerVehicle[ii][pVehNeon] = AccountData[playerid][pMechTempComp1];
				}
			}
			
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membongkar neon kendaraan ini seharga 50 Komponen.");
			AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
			AccountData[playerid][pMechTempComp1] = 0;
			AccountData[playerid][pMechTempComp2] = 0;
		}
	}
	return 1;
}

Dialog:GiveLic(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    new otherid = AccountData[playerid][pTempValue2];

    if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    
    switch(listitem)
    {
        case 0:
        {
            if (AccountData[otherid][pBLic])
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sudah memiliki Surat Izin Berlayar!");

            AccountData[otherid][pBLic] = true;
            AccountData[otherid][pBLicTime] = gettime() + (30 * 86400);
            ShowTDN(otherid, NOTIFICATION_INFO, "Seorang petugas telah memberikan anda Surat Izin Berlayar.");
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membuat Surat Izin Berlayar kepada orang tersebut.");
        }
        case 1:
        {
            if (AccountData[otherid][pAir1Lic])
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sudah memiliki Surat Izin Helikopter!");

            AccountData[otherid][pAir1Lic] = true;
            AccountData[otherid][pAir1LicTime] = gettime() + (30 * 86400);
            ShowTDN(otherid, NOTIFICATION_INFO, "Seorang petugas telah memberikan anda Surat Izin Helikopter.");
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membuat Surat Izin Helikopter kepada orang tersebut.");
        }
        case 2:
        {
            if (AccountData[otherid][pAir2Lic])
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sudah memiliki Surat Izin Pesawat!");

            AccountData[otherid][pAir2Lic] = true;
            AccountData[otherid][pAir2LicTime] = gettime() + (30 * 86400);
            ShowTDN(otherid, NOTIFICATION_INFO, "Seorang petugas telah memberikan anda Surat Izin Pesawat.");
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membuat Surat Izin Pesawat kepada orang tersebut.");
        }
    }
    return 1;
}

Dialog:GiveLic2(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    new otherid = AccountData[playerid][pTempValue2];

    if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    
    switch(listitem)
    {
        case 0:
        {
            if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Lisensi ini hanya dapat dirilis oleh kepolisian!");
            if(AccountData[otherid][pGVL1LicTime] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "SIM A belum expired!");

            AccountData[otherid][pGVL1Lic] = true;
            AccountData[otherid][pGVL1LicTime] = gettime() + (20 * 86400);
            ShowTDN(otherid, NOTIFICATION_INFO, "Seorang petugas telah memberikan anda SIM A.");
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membuat SIM A kepada orang tersebut.");
        }
        case 1:
        {
            if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Lisensi ini hanya dapat dirilis oleh kepolisian!");
            if(AccountData[otherid][pGVL2LicTime] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "SIM B belum expired!");

            AccountData[otherid][pGVL2Lic] = true;
            AccountData[otherid][pGVL2LicTime] = gettime() + (20 * 86400);
            ShowTDN(otherid, NOTIFICATION_INFO, "Seorang petugas telah memberikan anda SIM B.");
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membuat SIM B kepada orang tersebut.");
        }
        case 2:
        {
            if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Lisensi ini hanya dapat dirilis oleh kepolisian!");
            if(AccountData[otherid][pMBLicTime] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "SIM C belum expired!");

            AccountData[otherid][pMBLic] = true;
            AccountData[otherid][pMBLicTime] = gettime() + (20 * 86400);
            ShowTDN(otherid, NOTIFICATION_INFO, "Seorang petugas telah memberikan anda SIM C.");
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membuat SIM C kepada orang tersebut.");
        }
        case 3:
        {
            if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Lisensi ini hanya dapat dirilis oleh kepolisian!");
            if(AccountData[playerid][pFactionRank] < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank KOPDA untuk akses ini!");

            if (AccountData[otherid][pHuntingLicTime] != 0)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Kartu Izin Berburu belum expired!");

            AccountData[otherid][pHuntingLic] = true;
            AccountData[otherid][pHuntingLicTime] = gettime() + (20 * 86400);
            ShowTDN(otherid, NOTIFICATION_INFO, "Seorang petugas telah memberikan anda Kartu Izin Berburu.");
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membuat Kartu Izin Berburu kepada orang tersebut.");
        }
        case 4:
        {
            if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Lisensi ini hanya dapat dirilis oleh kepolisian!");
            if(AccountData[playerid][pFactionRank] < 14) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank BRIGJEN untuk akses ini!");

            if (AccountData[otherid][pFirearmLicTime] != 0)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Kartu Izin Senjata Api belum expired!");
            
            AccountData[otherid][pFirearmLic] = true;
            AccountData[otherid][pFirearmLicTime] = gettime() + (30 * 86400);
            ShowTDN(otherid, NOTIFICATION_INFO, "Seorang petugas telah memberikan anda Kartu Izin Senjata Api.");
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membuat Kartu Izin Senjata Api kepada orang tersebut.");
        }
    }
    return 1;
}

Dialog:FightStyle(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah membatalkan pilihan!"); 

	if(!IsPlayerInRangeOfPoint(playerid, 3.0, 767.2671,-22.9374,1000.5859) && GetPlayerVirtualWorld(playerid) != 2001 && GetPlayerInterior(playerid) != 6)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di Cobra GYM");

	if(AccountData[playerid][pMoney] < 5000)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda membutuhkan uang $5,000!");

	switch(listitem)
	{
		case 0:
		{
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menggantinya ke Fighting Style Normal.");
			SetPlayerFightingStyle(playerid, FIGHT_STYLE_NORMAL);
			GameTextForPlayer(playerid, "~p~Fighting Style~n~~w~Normal!", 3500, 3);
		}
		case 1:
		{
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menggantinya ke Fighting Style Boxing.");
			SetPlayerFightingStyle(playerid, FIGHT_STYLE_BOXING);
			GameTextForPlayer(playerid, "~p~Fighting Style~n~~w~Boxing!", 3500, 3);
		}
		case 2:
		{
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menggantinya ke Fighting Style Kungfu.");
			SetPlayerFightingStyle(playerid, FIGHT_STYLE_KUNGFU);
			GameTextForPlayer(playerid, "~p~Fighting Style~n~~w~Kungfu!", 3500, 3);
		}
		case 3:
		{
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menggantinya ke Fighting Style Kneehead.");
			SetPlayerFightingStyle(playerid, FIGHT_STYLE_KNEEHEAD);
			GameTextForPlayer(playerid, "~p~Fighting Style~n~~w~Kneehead!", 3500, 3);
		}
		case 4:
		{
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menggantinya ke Fighting Style Grab Kick.");
			SetPlayerFightingStyle(playerid, FIGHT_STYLE_GRABKICK);
			GameTextForPlayer(playerid, "~p~Fighting Style~n~~w~Grab Kick!", 3500, 3);
		}
		case 5:
		{
			ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menggantinya ke Fighting Style Elbow.");
			SetPlayerFightingStyle(playerid, FIGHT_STYLE_ELBOW);
			GameTextForPlayer(playerid, "~p~Fighting Style~n~~w~Elbow!", 3500, 3);
		}
	}
	TakePlayerMoneyEx(playerid, 5000);
	AccountData[playerid][pFightingStyle] = GetPlayerFightingStyle(playerid);
	ShowItemBox(playerid, "Cash", "Removed $5,000x", 1212, 5);
	return 1;
}

Dialog:ForgotPassword(playerid, response, listitem, inputtext[])
{
	if(!response) return SendClientMessage(playerid, Y_GREY, "ERROR: Anda telah membatalkan pilihan!");

	AccountData[playerid][pInResetPassword] = true;
	SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Mengecek data email anda, mohon tunggu...");

	new query[244];
	mysql_format(g_SQL, query, sizeof(query), "SELECT `Email` FROM `player_ucp` WHERE `UCP` = '%e' AND `Email` = '%e'", AccountData[playerid][pUCP], inputtext);
	mysql_pquery(g_SQL, query, "VerifyEmail", "i", playerid);
	return 1;
}

Dialog:ResetPassword(playerid, response, listitem, inputtext[])
{
	if(!response) 
	{
		SendClientMessage(playerid, Y_GREY, "ERROR: Anda telah membatalkan proses reset password!");
		KickEx(playerid);
		return 1;
	}

	if(strlen(inputtext) < 6 || strlen(inputtext) > 32)
	{
		Dialog_Show(playerid, "ResetPassword", DIALOG_STYLE_PASSWORD, ""RED"UCP - Reset Password", ""WHITE"Silakan masukkan kata sandi baru anda: "PAHLAWAN"(input below)", "Reset", "Cancel");

		SendClientMessage(playerid, Y_GREY, "ERROR: Password harus antara 6-32 karakter!");
		return 1;
	}

	for(new i = 0, len = strlen(inputtext); i < len; i++)
	{
		switch(inputtext[i])
		{
			case 'a'..'z', 'A'..'Z', '0'..'9': continue;
			default:
			{
				Dialog_Show(playerid, "ResetPassword", DIALOG_STYLE_PASSWORD, ""RED"UCP - Reset Password", ""WHITE"Silakan masukkan kata sandi baru anda: "PAHLAWAN"(input below)", "Reset", "Cancel");

				SendClientMessage(playerid, Y_GREY, "ERROR: Password hanya boleh terdiri dari huruf dan angka!");
				return 1;
			}
		}
	}

	format(AccountData[playerid][pTempPassword], 64, "%s", inputtext);
	bcrypt_hash(playerid, "OnPasswordResetHashed", inputtext, BCRYPT_COST);
	return 1;
}