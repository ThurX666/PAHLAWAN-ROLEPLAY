#include <YSI_Coding\y_hooks>

new Float: RandomJailSpawn[][5] = {
    {227.4145,110.6261,999.0162,358.7130},
    {223.4700,110.9333,999.0162,358.4230},
    {219.4507,111.3199,999.0162,358.7364},
    {215.4960,111.4410,999.0162,358.7362}
};

new Float: MDCPosition[][3] = {
    {941.8063,2451.0320,10.9001},
    {934.5219,2443.4302,10.9001},
    {242.6550,1845.5930,8.7578}
};

static const CopRank[17][] = 
{
	"N/A",

    "BHARADA", //1
    "BHARATU", //2
    "BRIPDA", //3
    "BRIPTU", //4
    "BRIGPOL", //5
    "BRIPKA", //6
    "AIPDA", //7
    "AIPTU", //8
    "IPDA", //9
    "IPTU", //10
    "AKP", //11
    "KOMPOL", //12
    "AKBP", //13
    "KOMBESPOL", //14
	"BRIGJENPOL", //15
	"IRJENPOL" //16
};

IsPlayerNearMDC(playerid)
{
    for(new x; x < sizeof(MDCPosition); x++)
    {
        if(IsPlayerInRangeOfPoint(playerid, 3.0, MDCPosition[x][0], MDCPosition[x][1], MDCPosition[x][2]))
        {
            return true;
        }
    }
    return false;
}

SendPlayerToFederal(playerid)
{
    new rand = random(sizeof(RandomJailSpawn));
    SetPlayerPositionEx(playerid, RandomJailSpawn[rand][0], RandomJailSpawn[rand][1], RandomJailSpawn[rand][2], RandomJailSpawn[rand][3]);
    SetPlayerVirtualWorldEx(playerid, 0);
    SetPlayerInteriorEx(playerid, 10);
    AccountData[playerid][pCuffed] = false;
}

LSPD_ShowBrankas(playerid)
{
    new 
        curr_page = index_pagination[playerid],
        count = 0,
        string[1012],
        real_i = 0,
        fbrankas_exists[MAX_PAGINATION_PAGES],
        fbrankas_temp[MAX_PAGINATION_PAGES][32],
        fbrankas_model[MAX_PAGINATION_PAGES],
        fbrankas_quant[MAX_PAGINATION_PAGES],
        fbrankas_id[MAX_PAGINATION_PAGES],
        fbrankas_fid[MAX_PAGINATION_PAGES],
        curr_idx;

    curr_idx = MAX_PAGINATION_PAGES * curr_page;

    for(new i = 0; i < MAX_PAGINATION_PAGES; i++) 
    {
        fbrankas_exists[i] = false;
    }

    strcat(string, "Nama Item\tJumlah\n");
    for(new i = 0; i < MAX_FACTIONS_ITEMS; i++) 
    {
        if (FactionBrankas[i][factionBrankasExists] && FactionBrankas[i][factionBrankasFID] == FACTION_LSPD)
        {
            if (real_i >= curr_idx && real_i < curr_idx + MAX_PAGINATION_PAGES)
            {
                fbrankas_exists[real_i - curr_idx] = true;
                fbrankas_id[real_i - curr_idx] = i;
                fbrankas_fid[real_i - curr_idx] = FactionBrankas[i][factionBrankasFID];
                fbrankas_model[real_i - curr_idx] = FactionBrankas[i][factionBrankasModel];
                strcopy(fbrankas_temp[real_i - curr_idx], FactionBrankas[i][factionBrankasTemp], 32);
                fbrankas_quant[real_i - curr_idx] = FactionBrankas[i][factionBrankasQuant];
            }
            real_i++;
        }
    }

    for(new i = 0; i < MAX_PAGINATION_PAGES; i++) 
    {
        if(fbrankas_exists[i]) 
        {
            if (i % 2 == 0)
            {
                strcat(string, sprintf(""WHITE"%s\t"WHITE"%d\n", fbrankas_temp[i], fbrankas_quant[i]));
            }
            else
            {
                strcat(string, sprintf(""GRAY"%s\t"GRAY"%d\n", fbrankas_temp[i], fbrankas_quant[i]));
            }
            PlayerListitem[playerid][count++] = fbrankas_id[i];
        }
    }

    if(count == 0) 
	{
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "LSPD Vault", "Lemari penyimpanan ini kosong!", "Tutup", "");
    } 
	else 
	{
        new max_pages = (real_i + MAX_PAGINATION_PAGES - 1) / MAX_PAGINATION_PAGES;

        if (curr_page > 0) {
            strcat(string, ""RED"<< Sebelumnya\n");
        }
        if (curr_page < max_pages - 1) {
            strcat(string, ""GREEN">> Selanjutnya\n");
        }

        Dialog_Show(playerid, "PolisiVaultWithdraw", DIALOG_STYLE_TABLIST_HEADERS, sprintf("LSPD Vault: Page %d of %d", curr_page + 1, max_pages),
        string, "Pilih", "Batal");
    }
    return 1;
}

Show_LSPDRankManage(playerid)
{
    new 
        string[1012],
        member_name[MAX_MEMBER_ROWS][64],
        member_pID[MAX_MEMBER_ROWS],
        member_rank[MAX_MEMBER_ROWS],
        member_lastlog[MAX_MEMBER_ROWS][30],
        curr_page = index_pagination[playerid],
        curr_index;

    curr_index = curr_page * MAX_MEMBER_ROWS;

    for(new i = 0; i < MAX_MEMBER_ROWS; i++) {
        member_pID[i] = 0;
    }

    new real_i = 0;
    mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 1 ORDER BY Char_FactionRank DESC");

    new rows = cache_num_rows(),
        count = 0;

    if(rows)
    {
        for(new i = curr_index; i < rows; i++) if(i <= rows)
        {
            if(real_i < sizeof(member_pID)) {

                cache_get_value_name(i, "Char_Name", member_name[real_i]);
                cache_get_value_name_int(i, "Char_FactionRank", member_rank[real_i]);
                cache_get_value_name(i, "Char_LastLogin", member_lastlog[real_i]);
                cache_get_value_name_int(i, "pID", member_pID[real_i]); 
                real_i++;
            }
            else {
                break;
            }
        }

        strcat(string, "Nama\tRank\tLast Online\n");

        for(new i = 0; i < real_i; ++i) if(member_pID[i] != 0)
        {
            strcat(string, sprintf("%s\t%s\t%s\n", member_name[i], CopRank[member_rank[i]], member_lastlog[i]));
            ListedMember[playerid][count++] = member_pID[i];
        }

        new 
            total_pages = (rows + MAX_MEMBER_ROWS - 1) / MAX_MEMBER_ROWS;

        new 
            max_page = total_pages - 1; 

        TempRows[playerid] = rows;

        if(curr_page > 0) {
            strcat(string, ""RED"<< Sebelumnya");
            strcat(string, "\n");
        }
        if(curr_page < max_page) {
            strcat(string, ""GREEN">> Selanjutnya"); 
            strcat(string, "\n");
        }

        Dialog_Show(playerid, "LSPDSetRank", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", string, "Pilih", "Batal");
    }
    else
    {
        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", "Faction ini tidak memiliki anggota!", "Tutup", "");
    }
    return 1;
}

stock ShowLSPDKick(playerid) 
{
    new 
        string[1012],
        member_name[MAX_MEMBER_ROWS][64],
        member_pID[MAX_MEMBER_ROWS],
        member_rank[MAX_MEMBER_ROWS],
        member_lastlog[MAX_MEMBER_ROWS][30],
        curr_page = index_pagination[playerid],
        curr_index;

    curr_index = curr_page * MAX_MEMBER_ROWS;

    for(new i = 0; i < MAX_MEMBER_ROWS; i++) {
        member_pID[i] = 0;
    }

    new real_i = 0;
    mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 1 ORDER BY Char_FactionRank DESC");

    new rows = cache_num_rows(),
        count = 0;

    if(rows)
    {
        for(new i = curr_index; i < rows && real_i < MAX_MEMBER_ROWS; i++)
        {
            cache_get_value_name(i, "Char_Name", member_name[real_i]);
            cache_get_value_name_int(i, "Char_FactionRank", member_rank[real_i]);
            cache_get_value_name(i, "Char_LastLogin", member_lastlog[real_i]);
            cache_get_value_name_int(i, "pID", member_pID[real_i]); 
            real_i++;
        }

        strcat(string, "Nama\tRank\tLast Online\n");

        for(new i = 0; i < real_i; ++i)
        {
            strcat(string, sprintf("%s\t%s\t%s\n", member_name[i], CopRank[member_rank[i]], member_lastlog[i]));
            ListedMember[playerid][count++] = member_pID[i];
        }

        new total_pages = (rows + MAX_MEMBER_ROWS - 1) / MAX_MEMBER_ROWS;
        new max_page = total_pages - 1;

        if(curr_page > 0) 
        {
            strcat(string, ""RED"<< Sebelumnya");
            strcat(string, "\n");
        }

        if(curr_page < max_page) 
        {
            strcat(string, ""GREEN">> Selanjutnya");
            strcat(string, "\n");
        }

        Dialog_Show(playerid, "LSPDKickMember", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Kick Faction", string, "Pilih", "Batal");
    }
    else
    {
        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Kick Faction", "Faction ini tidak memiliki anggota!", "Tutup", "");
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && AccountData[playerid][pFaction] == FACTION_LSPD && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && IsPlayerInRangeOfPoint(playerid, 3.0, 983.5379,2474.1208,10.8549))
    {
        Dialog_Show(playerid, "PolisiImpoundSearch", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Impound", 
        "Please insert the player ID:", "Pilih", "Batal");
    }
    else if(newkeys & KEY_CTRL_BACK && AccountData[playerid][pFaction] == FACTION_LSPD && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(AccountData[playerid][pInEvent]) return 1;
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
            Dialog_Show(playerid, "FactionPanel", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Faction Panel", 
            frmxt, "Pilih", "Batal");
		}
    }
    return 1;
}

Dialog:TakeLicense(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    new otherid = AccountData[playerid][pTempValue2];

    if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    
    switch(listitem)
    {
        case 0:
        {
            if (!AccountData[otherid][pGVL1Lic])
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak memiliki SIM A!");

            AccountData[otherid][pGVL1Lic] = false;
            AccountData[otherid][pGVL1LicTime] = 0;
            ShowTDN(otherid, NOTIFICATION_WARNING, "Seorang petugas telah menyita SIM A milik anda.");
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyita SIM A Pemain tersebut.");
        }
        case 1:
        {
            if (!AccountData[otherid][pGVL2Lic])
                return ShowTDN(playerid, NOTIFICATION_ERROR, "TPemain tersebut tidak memiliki SIM B!");

            AccountData[otherid][pGVL2Lic] = false;
            AccountData[otherid][pGVL2LicTime] = 0;
            ShowTDN(otherid, NOTIFICATION_WARNING, "Seorang petugas telah menyita SIM B milik anda.");
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyita SIM B Pemain tersebut.");
        }
        case 2:
        {
            if (!AccountData[otherid][pMBLic])
                return ShowTDN(playerid, NOTIFICATION_ERROR, "TPemain tersebut tidak memiliki SIM C!");

            AccountData[otherid][pMBLic] = false;
            AccountData[otherid][pMBLicTime] = 0;
            ShowTDN(otherid, NOTIFICATION_WARNING, "Seorang petugas telah menyita SIM C milik anda.");
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyita SIM C Pemain tersebut.");
        }
        case 3:
        {
            if (!AccountData[otherid][pBLic])
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak memiliki Surat Izin Berlayar!");

            AccountData[otherid][pBLic] = false;
            AccountData[otherid][pBLicTime] = 0;
            ShowTDN(otherid, NOTIFICATION_WARNING, "Seorang petugas telah menyita Surat Izin Berlayar milik anda.");
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyita Surat Izin Berlayar Pemain tersebut.");
        }
        case 4:
        {
            if (!AccountData[otherid][pAir1Lic])
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak memiliki Surat Izin Helikopter!");

            AccountData[otherid][pAir1Lic] = false;
            AccountData[otherid][pAir1LicTime] = 0;
            ShowTDN(otherid, NOTIFICATION_WARNING, "Seorang petugas telah menyita Surat Izin Helikopter milik anda.");
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyita Surat Izin Helikopter Pemain tersebut.");
        }
        case 5:
        {
            if (!AccountData[otherid][pAir2Lic])
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak memiliki Surat Izin Pesawat!");

            AccountData[otherid][pAir2Lic] = false;
            AccountData[otherid][pAir2LicTime] = 0;
            ShowTDN(otherid, NOTIFICATION_WARNING, "Seorang petugas telah menyita Surat Izin Pesawat milik anda.");
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyita Surat Izin Pesawat Pemain tersebut.");
        }
        case 6:
        {
            if (!AccountData[otherid][pHuntingLic])
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak memiliki Kartu Izin Berburu!");

            AccountData[otherid][pHuntingLic] = false;
            AccountData[otherid][pHuntingLicTime] = 0;
            ShowTDN(otherid, NOTIFICATION_WARNING, "Seorang petugas telah menyita Kartu Izin Berburu milik anda.");
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyita Kartu Izin Berburu Pemain tersebut.");
        }
        case 7:
        {
            if (!AccountData[otherid][pFirearmLic])
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak memiliki Kartu Izin Senjata Api!");

            AccountData[otherid][pFirearmLic] = false;
            AccountData[otherid][pFirearmLicTime] = 0;
            ShowTDN(otherid, NOTIFICATION_WARNING, "Seorang petugas telah menyita Kartu Izin Senjata Api milik anda.");
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyita Kartu Izin Senjata Api Pemain tersebut.");
        }
    }
    return 1;
}
Dialog:PolisiLocker(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");

    switch(listitem)
    {
        case 0: //toggle duty
        {
            if(AccountData[playerid][pOnDuty])
            {
                //lepas armor
                SetPlayerArmour(playerid, 0.0);
                AccountData[playerid][pArmor] = 0.0;
                AccountData[playerid][pHasArmor] = false;
                AccountData[playerid][pArmorEmpty] = true;

                ResetPlayerWeaponsEx(playerid);

                SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
                AccountData[playerid][pIsUsingUniform] = false;
                AccountData[playerid][pOnDuty] = false;
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda sekarang ~r~off duty.");
                SendTeamMessage(FACTION_LSPD, 0x8D8DFFFF, "(MABES) %s %s telah menyelesaikan masa tugas.", GetRankName(playerid), GetPlayerRoleplayName(playerid));
                Iter_Remove(LSPDDuty, playerid);
            }
            else
            {
                if(AccountData[playerid][pGender] == 1)
                {
                    AccountData[playerid][pUniform] = 311;
                    SetPlayerSkin(playerid, 311);
                }
                else
                {
                    AccountData[playerid][pUniform] = 309;
                    SetPlayerSkin(playerid, 309);
                }
                AccountData[playerid][pIsUsingUniform] = true;
                AccountData[playerid][pOnDuty] = true;
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda sekarang ~g~on duty.");
                SendTeamMessage(FACTION_LSPD, 0x8D8DFFFF, "(MABES) %s %s melapor untuk bertugas.", GetRankName(playerid), GetPlayerRoleplayName(playerid));
                Iter_Add(LSPDDuty, playerid);
            }
        }
        case 1: //change uniform
        {
            if(AccountData[playerid][pGender] == 1)
            {
                Dialog_Show(playerid, "PolisiUniform", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- LSPD Uniform", 
                "LSPD #1\nLSPD #2\nLSPD #3\nLSPD #4\nLSPD #5\nLSPD #6\nLSPD #7\nLSPD #8\nLSPD #9", "Pilih", "Batal");
            }
            else
            {
                Dialog_Show(playerid, "PolisiUniform", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- LSPD Uniform", 
                "LSPD #1\nLSPD #2\nLSPD #3\nLSPD #4", "Pilih", "Batal");
            }
        }
        case 2: //
        {
            Dialog_Show(playerid, "PolisiPlainClothes", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Seragam Polisi", 
            "Please insert the skin ID that you want to use:", "Pilih", "Batal");
        }
        case 3: //get equipments
        {
            if(!AccountData[playerid][pOnDuty]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang on duty!");
            SetPlayerArmourEx(playerid, 100.0);
            GivePlayerWeaponEx(playerid, 3, 1, WEAPON_TYPE_FACTION);
            GivePlayerWeaponEx(playerid, 41, 5000, WEAPON_TYPE_FACTION);

            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengambil perlengkapan.");
        }
        case 4: //return equipments
        {
            //lepas armor
            SetPlayerArmour(playerid, 0.0);
            AccountData[playerid][pArmor] = 0.0;
            AccountData[playerid][pHasArmor] = false;
            AccountData[playerid][pArmorEmpty] = true;
            ResetWeapon(playerid, 3);
            ResetWeapon(playerid, 41);
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mengembalikan perlengkapan.");
        }
    }
    return 1;
}
Dialog:PolisiUniform(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");

    switch(listitem)
    {
        case 0:
        {
            AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (280) : (306);
            SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
            AccountData[playerid][pIsUsingUniform] = true;
        }
        case 1:
        {
            AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (281) : (307);
            SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
            AccountData[playerid][pIsUsingUniform] = true;
        }
        case 2:
        {
            AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (284) : (306);
            SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
            AccountData[playerid][pIsUsingUniform] = true;
        }
        case 3:
        {
            AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (285) : (307);
            SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
            AccountData[playerid][pIsUsingUniform] = true;
        }
        case 4:
        {
            AccountData[playerid][pUniform] = 265;
            SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
            AccountData[playerid][pIsUsingUniform] = true;
        }
        case 5:
        {
            AccountData[playerid][pUniform] = 266;
            SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
            AccountData[playerid][pIsUsingUniform] = true;
        }
        case 6:
        {
            AccountData[playerid][pUniform] = 267;
            SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
            AccountData[playerid][pIsUsingUniform] = true;
        }
        case 7:
        {
            AccountData[playerid][pUniform] = 300;
            SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
            AccountData[playerid][pIsUsingUniform] = true;
        }
        case 8:
        {
            AccountData[playerid][pUniform] = 301;
            SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
            AccountData[playerid][pIsUsingUniform] = true;
        }
    }
    return 1;
}
Dialog:PolisiPlainClothes(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");
    if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat mengosongkannya!");
    if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya ID Skin!");
    
    if(strval(inputtext) < 1 || strval(inputtext) > 311)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid skin ID (1 - 311)");

    AccountData[playerid][pUniform] = strval(inputtext);
    SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
    AccountData[playerid][pIsUsingUniform] = true;
    return 1;
}
Dialog:PolisiBosdesk(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");
    if(AccountData[playerid][pFactionRank] < 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimum rank KOMPOL untuk akses menu faction!");

    switch(listitem)
    {
        case 0: //invite
        {
            new frmxt[522], count = 0;

            foreach(new i : Player) if(i != playerid) if(IsPlayerNearPlayer(playerid, i, 1.5)) 
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
                return Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Undang Faction", "Tidak ada pemain terdekat!", "Tutup", "");
            }

            Dialog_Show(playerid, "PolisiInviteConfirm", DIALOG_STYLE_TABLIST, "{DA9100}Pahlawan Roleplay "WHITE"- Undang Faction", frmxt, "Pilih", "Batal");
        }
        case 1: //kelola jabatan
        {
            new 
                string[1012],
                member_name[MAX_MEMBER_ROWS][64],
                member_pID[MAX_MEMBER_ROWS],
                member_rank[MAX_MEMBER_ROWS],
                member_lastlog[MAX_MEMBER_ROWS][30],
                curr_page = index_pagination[playerid],
                curr_index;

            curr_index = curr_page * MAX_MEMBER_ROWS;

            for(new i = 0; i < MAX_MEMBER_ROWS; i++) {
                member_pID[i] = 0;
            }

            new real_i = 0;
            mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 1 ORDER BY Char_FactionRank DESC");

            new rows = cache_num_rows(),
                count = 0;

            if(rows)
            {
                for(new i = curr_index; i < rows; i++) if(i <= rows)
                {
                    if(real_i < sizeof(member_pID)) {

                        cache_get_value_name(i, "Char_Name", member_name[real_i]);
                        cache_get_value_name_int(i, "Char_FactionRank", member_rank[real_i]);
                        cache_get_value_name(i, "Char_LastLogin", member_lastlog[real_i]);
                        cache_get_value_name_int(i, "pID", member_pID[real_i]); 
                        real_i++;
                    }
                    else {
                        break;
                    }
                }

                strcat(string, "Nama\tRank\tLast Online\n");

                for(new i = 0; i < real_i; ++i) if(member_pID[i] != 0)
                {
                    strcat(string, sprintf("%s\t%s\t%s\n", member_name[i], CopRank[member_rank[i]], member_lastlog[i]));
                    ListedMember[playerid][count++] = member_pID[i];
                }

                new 
                    total_pages = (rows + MAX_MEMBER_ROWS - 1) / MAX_MEMBER_ROWS;

                new 
                    max_page = total_pages - 1; 

                TempRows[playerid] = rows;

                if(curr_page > 0) {
                    strcat(string, ""RED"<< Sebelumnya");
                    strcat(string, "\n");
                }
                if(curr_page < max_page) {
                    strcat(string, ""GREEN">> Selanjutnya"); 
                    strcat(string, "\n");
                }

                Dialog_Show(playerid, "LSPDSetRank", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", string, "Pilih", "Batal");
            }
            else
            {
                PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", "Faction ini tidak memiliki anggota!", "Tutup", "");
            }
        }
        case 2: //kick
        {
            index_pagination[playerid] = 0;
            ShowLSPDKick(playerid); 
        }
        case 3: //saldo
        {
            new rtx[158];
            format(rtx, sizeof(rtx), "Saldo Kepolisian Kota Pahlawan Roleplay saat ini ialah:\n\
            "DARKGREEN"$%s", FormatMoney(PolisiMoneyVault));
            Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Kepolisian Balance", rtx, "Tutup", "");
        }
        case 4: //deposit saldo
        {
            Dialog_Show(playerid, "PolisiDepositCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Kepolisian Deposit", 
            "Mohon masukkan berapa jumlah deposit:", "Input", "Batal");
        }
        case 5: //tarik saldo
        {
            Dialog_Show(playerid, "PolisiWithdrawCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Kepolisian Withdraw", 
            "Mohon masukkan berapa jumlah withdraw:", "Input", "Batal");
        }
    }
    return 1;
}
Dialog:PolisiInviteConfirm(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");
    if(AccountData[playerid][pFactionRank] < 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimum rank KOMPOL untuk akses menu faction!");

    new targetid = NearestUser[playerid][listitem], icsr[128];
    if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    
    AccountData[targetid][pFaction] = FACTION_LSPD;
    AccountData[targetid][pFactionRank] = 1;
    mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction` = 1, `Char_FactionRank` = 1 WHERE `pID` = %d", AccountData[targetid][pID]);
    mysql_pquery(g_SQL, icsr);
    ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Anda telah mengundang %s ke faction!", AccountData[targetid][pName]));

    InsertFactionLog("Invite", sprintf("%s %s - %s %s", AccountData[playerid][pName], AccountData[playerid][pUCP], AccountData[targetid][pName], AccountData[targetid][pUCP]), "LSPD");
    return 1;
}
Dialog:PolisiSetRankConfirm(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");
    if(AccountData[playerid][pFactionRank] < 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimum rank KOMPOL untuk akses menu faction!");

    if(isnull(inputtext)) return Dialog_Show(playerid, "PolisiSetRankConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
    "Error: Tidak dapat dikosongkan!\n\
    Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
    1. BHARADA\n\
    2. BHARATU\n\
    3. BRIPDA\n\
    4. BRIPTU\n\
    5. BRIGPOL\n\
    6. BRIPKA\n\
    7. AIPDA\n\
    8. AIPTU\n\
    9. IPDA\n\
    10. IPTU\n\
    11. AKP\n\
    12. KOMPOL\n\
    13. AKBP\n\
    14. KOMBESPOL\n\
    15. BRIGJENPOL\n\
    16. IRJENPOL", "Set", "Batal");
    
    if(!IsNumericEx(inputtext)) return Dialog_Show(playerid, "PolisiSetRankConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
    "Error: Masukkan hanya angka!\n\
    Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
    1. BHARADA\n\
    2. BHARATU\n\
    3. BRIPDA\n\
    4. BRIPTU\n\
    5. BRIGPOL\n\
    6. BRIPKA\n\
    7. AIPDA\n\
    8. AIPTU\n\
    9. IPDA\n\
    10. IPTU\n\
    11. AKP\n\
    12. KOMPOL\n\
    13. AKBP\n\
    14. KOMBESPOL\n\
    15. BRIGJENPOL\n\
    16. IRJENPOL", "Set", "Batal");

    if(strval(inputtext) < 1 || strval(inputtext) > 16) return Dialog_Show(playerid, "PolisiSetRankConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
    "Error: Tidak dapat diisi dibawah 1 atau lebih tinggi dari jabatan anda!\n\
    Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
    1. BHARADA\n\
    2. BHARATU\n\
    3. BRIPDA\n\
    4. BRIPTU\n\
    5. BRIGPOL\n\
    6. BRIPKA\n\
    7. AIPDA\n\
    8. AIPTU\n\
    9. IPDA\n\
    10. IPTU\n\
    11. AKP\n\
    12. KOMPOL\n\
    13. AKBP\n\
    14. KOMBESPOL\n\
    15. BRIGJENPOL\n\
    16. IRJENPOL", "Set", "Batal");

    new hjh[128];
    mysql_format(g_SQL, hjh, sizeof(hjh), "UPDATE `player_characters` SET `Char_FactionRank`=%d WHERE `pID`=%d", strval(inputtext), AccountData[playerid][pTempSQLFactMemberID]);
    mysql_pquery(g_SQL, hjh);

    foreach(new i : Player)
    {
        if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && AccountData[playerid][pTempSQLFactMemberID] == AccountData[i][pID])
        {
            AccountData[i][pFactionRank] = strval(inputtext);
            ShowTDN(i, NOTIFICATION_INFO, "Jabatan faction anda telah diperbarui!");
            InsertFactionLog("Set Rank", sprintf("%s %s - %s %s LV %d", AccountData[playerid][pName], AccountData[playerid][pUCP], AccountData[i][pName], AccountData[i][pUCP], strval(inputtext)), "LSPD");
        }
    }

    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil mengubah jabatan faction Pemain tersebut!");
    return 1;
}
Dialog:PolisiVault(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    switch(listitem)
    {
        case 0: //deposit
        {
            new str[1218], count;
            format(str, sizeof(str), "Nama Item\tJumlah\n");
            for(new index; index < MAX_INVENTORY; index++)
            {
                if(InventoryData[playerid][index][invExists])
                {
                    for(new i; i < sizeof(g_aInventoryItems); i ++) if (!strcmp(g_aInventoryItems[i][e_InventoryItem], InventoryData[playerid][index][invItem], true))
                    {
                        format(str, sizeof(str), "%s%s\t%d\n", str, InventoryData[playerid][index][invItem], InventoryData[playerid][index][invQuantity]);
                        PlayerListitem[playerid][count++] = index;
                    }
                }
            }

            if(count == 0)
            {
                Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Kepolisian", 
                "Anda tidak memiliki barang yang dapat disimpan!", "Tutup", "");
            }
            else
            {
                Dialog_Show(playerid, "PolisiVaultDeposit", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Kepolisian", str, "Pilih", "Batal");
            }
        }
        case 1: //withdraw
        {
            if(AccountData[playerid][pFactionRank] < 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimum rank KOMPOL untuk akses menu faction!");

            index_pagination[playerid] = 0;
            LSPD_ShowBrankas(playerid);
        }
    }
    return 1;
}

Dialog:PolisiVaultDeposit(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        AccountData[playerid][pMenuShowed] = false;
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
        return 1;
    }

    if(listitem == -1) 
    {
        AccountData[playerid][pMenuShowed] = false;
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item apapun!");
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
    
    new shstr[528];
    format(shstr, sizeof(shstr), ""WHITE"Anda akan menyimpan item:\nNama: "CYAN"%s\n"WHITE"Jumlah di tas: "YELLOW"%d\n"WHITE"Mohon masukkan jumlah yang ingin disimpan:", InventoryData[playerid][PlayerListitem[playerid][listitem]][invItem], InventoryData[playerid][PlayerListitem[playerid][listitem]][invQuantity]);
    Dialog_Show(playerid, "PolisiVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Kepolisian", 
    shstr, "Input", "Batal");
    return 1;
}
Dialog:PolisiVaultIn(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        AccountData[playerid][pMenuShowed] = false;
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
        return 1;
    }

    if(AccountData[playerid][pTempValue] == -1)
    {
        AccountData[playerid][pMenuShowed] = false;
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item apapun!");
        return 1;
    }

    new shstr[512], id = AccountData[playerid][pTempValue];
    if(isnull(inputtext)) 
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nTidak dapat dikosongkan!\nMohon masukkan berapa jumlah yang ingin disimpan:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
        Dialog_Show(playerid, "PolisiVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Kepolisian", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(!IsNumericEx(inputtext))
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nMohon diisi hanya angka!\nMohon masukkan berapa jumlah yang ingin disimpan:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
        Dialog_Show(playerid, "PolisiVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Kepolisian", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(strval(inputtext) < 1 || strval(inputtext) > InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity])
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nJumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin disimpan:", InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invQuantity]);
        Dialog_Show(playerid, "PolisiVaultIn", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Kepolisian", 
        shstr, "Input", "Batal");
        return 1;
    }

    new quantity = strval(inputtext);

    new invstr[1028];
    mysql_format(g_SQL, shstr, sizeof(shstr), "SELECT * FROM `faction_brankas` WHERE `FID` = %d AND `Item` = '%e'", FACTION_LSPD, InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
    mysql_query(g_SQL, shstr);

    new rows = cache_num_rows();
    if(rows > 0)
    {
        mysql_format(g_SQL, invstr, sizeof(invstr), "UPDATE `faction_brankas` SET `Quantity` = `Quantity` + %d WHERE `FID` = %d AND `Item` = '%e'", quantity, FACTION_LSPD, InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
        mysql_pquery(g_SQL, invstr);

        ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyimpan item tersebut.");

        for(new x; x < MAX_FACTIONS_ITEMS; ++x)
        {
            if(FactionBrankas[x][factionBrankasExists]  && FactionBrankas[x][factionBrankasFID] == FACTION_LSPD && !strcmp(FactionBrankas[x][factionBrankasTemp], InventoryData[playerid][PlayerListitem[playerid][id]][invItem], true))
            {
                FactionBrankas[x][factionBrankasQuant] += quantity;
            }
        }
    }
    else
    {
        for(new x; x < MAX_FACTIONS_ITEMS; ++x)
        {
            if(!FactionBrankas[x][factionBrankasExists]) 
            {
                FactionBrankas[x][factionBrankasExists] = true;
                FactionBrankas[x][factionBrankasFID] = FACTION_LSPD;
                strcopy(FactionBrankas[x][factionBrankasTemp], InventoryData[playerid][PlayerListitem[playerid][id]][invItem]);
                FactionBrankas[x][factionBrankasModel] = InventoryData[playerid][PlayerListitem[playerid][id]][invModel];
                FactionBrankas[x][factionBrankasQuant] = quantity;

                mysql_format(g_SQL, invstr, sizeof(invstr), "INSERT INTO `faction_brankas` SET `FID` = %d, `Item`='%e', `Model`=%d, `Quantity`=%d", FACTION_LSPD, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], InventoryData[playerid][PlayerListitem[playerid][id]][invModel], quantity);
                mysql_pquery(g_SQL, invstr, "OnFactionDeposit", "id", playerid, x);

                break;
            }
        }
    }
    ShowItemBox(playerid, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], sprintf("Removed %dx", quantity), InventoryData[playerid][PlayerListitem[playerid][id]][invModel], 5);
    Inventory_Remove(playerid, InventoryData[playerid][PlayerListitem[playerid][id]][invItem], quantity);
    return 1;
}
Dialog:PolisiVaultWithdraw(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        AccountData[playerid][pMenuShowed] = false;
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
        return 1;
    }

    if(listitem == -1) 
    {
        AccountData[playerid][pMenuShowed] = false;
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item apapun!");
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
        LSPD_ShowBrankas(playerid);
    }
    else if(!strcmp(inputtext, "<< Sebelumnya", true)) 
    {
        index_pagination[playerid]--;
        if(index_pagination[playerid] <= 0) {
            index_pagination[playerid] = 0;
        }
        LSPD_ShowBrankas(playerid);
    }
    else 
    {

        if(PlayerListitem[playerid][listitem] == -1)
        {
            AccountData[playerid][pMenuShowed] = false;
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item apapun!");
        }
        
        AccountData[playerid][pTempValue] = listitem;
        new shstr[528];
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Mohon masukkan berapa jumlah yang ingin diambil:", FactionBrankas[PlayerListitem[playerid][listitem]][factionBrankasTemp], FactionBrankas[PlayerListitem[playerid][listitem]][factionBrankasQuant]);
        Dialog_Show(playerid, "PolisiVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Kepolisian", 
        shstr, "Input", "Batal");
    }
    return 1;
}
Dialog:PolisiVaultOut(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        AccountData[playerid][pMenuShowed] = false;
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
        return 1;
    }

    if(AccountData[playerid][pTempValue] == -1)
    {
        AccountData[playerid][pMenuShowed] = false;
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item apapun!");
        return 1;
    }

    new shstr[512], id = AccountData[playerid][pTempValue];
    if(isnull(inputtext)) 
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Tidak dapat dikosongkan!\nMohon masukkan berapa jumlah yang ingin diambil:", FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant]);
        Dialog_Show(playerid, "PolisiVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Kepolisian", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(!IsNumericEx(inputtext))
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Mohon diisi hanya angka!\nMohon masukkan berapa jumlah yang ingin diambil:", FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant]);
        Dialog_Show(playerid, "PolisiVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Kepolisian", 
        shstr, "Input", "Batal");
        return 1;
    }

    if(strval(inputtext) < 1 || strval(inputtext) > FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant])
    {
        AccountData[playerid][pMenuShowed] = true;
        format(shstr, sizeof(shstr), ""WHITE"Anda akan mengambil item:\nNama: "CYAN"%s\n"WHITE"Jumlah tersimpan: "YELLOW"%d\n"WHITE"Jumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin diambil:", FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant]);
        Dialog_Show(playerid, "PolisiVaultOut", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Lemari Kepolisian", 
        shstr, "Input", "Batal");
        return 1;
    }

    new quantity = strval(inputtext), jts[150];
    new Float:countingtotalweight;
    countingtotalweight = GetTotalWeightFloat(playerid) + float(quantity * GetItemWeight(FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp]))/1000;
    if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda sudah penuh!");

    if(!strcmp(FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], "Obeng")) 
    {
        if(PlayerHasItem(playerid, "Obeng"))
        {
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah memiliki Obeng!");
        }
        else
        {
            if(quantity > 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat membawa lebih dari satu Obeng!"); 
        }
    }
    if(!strcmp(FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], "Cangkul")) 
    {
        if(PlayerHasItem(playerid, "Cangkul"))
        {
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah memiliki Cangkul!");
        }
        else
        {
            if(quantity > 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat membawa lebih dari satu Cangkul!"); 
        }
    }
    
    if(!strcmp(FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], "Smartphone"))
    {
        mysql_format(g_SQL, jts, sizeof(jts), "SELECT * FROM `player_phones` WHERE `phoneOwner`=%d", AccountData[playerid][pID]);
        mysql_pquery(g_SQL, jts, "OnPlayerBuySmartphone", "i", playerid);
    }
    else
    {
        Inventory_Add(playerid, FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], FactionBrankas[PlayerListitem[playerid][id]][factionBrankasModel], quantity);
    }
    ShowItemBox(playerid, FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], sprintf("Received %dx", quantity), FactionBrankas[PlayerListitem[playerid][id]][factionBrankasModel], 5);

    InsertFactionVaultLog(playerid, FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp], quantity, "POLISI");

    FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant] -= quantity;
    
    if(FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant] > 0)
    {
        mysql_format(g_SQL, jts, sizeof(jts), "UPDATE `faction_brankas` SET `Quantity`=%d WHERE `ID`=%d", FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant], FactionBrankas[PlayerListitem[playerid][id]][factionBrankasID]);
        mysql_pquery(g_SQL, jts);
    }
    else
    {
        mysql_format(g_SQL, jts, sizeof(jts), "DELETE FROM `faction_brankas` WHERE `ID`=%d", FactionBrankas[PlayerListitem[playerid][id]][factionBrankasID]);
        mysql_pquery(g_SQL, jts);

        FactionBrankas[PlayerListitem[playerid][id]][factionBrankasExists] = false;
        FactionBrankas[PlayerListitem[playerid][id]][factionBrankasID] = 0;
        FactionBrankas[PlayerListitem[playerid][id]][factionBrankasFID] = FACTION_NONE;
        FactionBrankas[PlayerListitem[playerid][id]][factionBrankasTemp][0] = EOS;
        FactionBrankas[PlayerListitem[playerid][id]][factionBrankasModel] = 0;
        FactionBrankas[PlayerListitem[playerid][id]][factionBrankasQuant] = 0;
    }
    AccountData[playerid][pMenuShowed] = false;
    return 1;
}
Dialog:PolisiArmoury(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");

    switch(listitem)
    {
        case 0: //restock ammo
        {
            if(AccountData[playerid][pLevel] < 5)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda dapat memegang senjata jika sudah mencapai level 5 karakter!");

            if(GetPlayerWeaponEx(playerid) == 24)
            {
                ResetWeapon(playerid, 24);
                GivePlayerWeaponEx(playerid, 24, 300, WEAPON_TYPE_FACTION);
                ShowTDN(playerid, NOTIFICATION_INFO, "Peluru senjata sudah diperbarui.");
            }
            else if(GetPlayerWeaponEx(playerid) == 25)
            {
                ResetWeapon(playerid, 25);
                GivePlayerWeaponEx(playerid, 25, 350, WEAPON_TYPE_FACTION);
                ShowTDN(playerid, NOTIFICATION_INFO, "Peluru senjata sudah diperbarui.");
            }
            else if(GetPlayerWeaponEx(playerid) == 29)
            {
                ResetWeapon(playerid, 29);
                GivePlayerWeaponEx(playerid, 29, 650, WEAPON_TYPE_FACTION);
                ShowTDN(playerid, NOTIFICATION_INFO, "Peluru senjata sudah diperbarui.");
            }
            else if(GetPlayerWeaponEx(playerid) == 31)
            {
                ResetWeapon(playerid, 31);
                GivePlayerWeaponEx(playerid, 31, 650, WEAPON_TYPE_FACTION);
                ShowTDN(playerid, NOTIFICATION_INFO, "Peluru senjata sudah diperbarui.");
            }
            else if(GetPlayerWeaponEx(playerid) == 27)
            {
                ResetWeapon(playerid, 27);
                GivePlayerWeaponEx(playerid, 27, 400, WEAPON_TYPE_FACTION);
                ShowTDN(playerid, NOTIFICATION_INFO, "Peluru senjata sudah diperbarui.");
            }
            else if(GetPlayerWeaponEx(playerid) == 34)
            {
                ResetWeapon(playerid, 34);
                GivePlayerWeaponEx(playerid, 34, 400, WEAPON_TYPE_FACTION);
                ShowTDN(playerid, NOTIFICATION_INFO, "Peluru senjata sudah diperbarui.");
            }
            else
            {
                ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang memegang senjata/senjata ini tidak bisa direstock!");
            }
        }
        case 1: //refill health & armour
        {
            SetPlayerHealthEx(playerid, 100.0);
            SetPlayerArmourEx(playerid, 255.0);
            ShowTDN(playerid, NOTIFICATION_INFO, "Darah dan armor anda sudah diperbarui.");
        }
        case 2: //tactical body armour
        {
            SetPlayerHealthEx(playerid, 100.0);
            SetPlayerArmourEx(playerid, 500.0);
            ShowTDN(playerid, NOTIFICATION_INFO, "Darah dan armor taktis anda sudah diperbarui.");
        }
        case 3: //clear weapon & armour
        {
            //lepas armor
            SetPlayerArmour(playerid, 0.0);
            AccountData[playerid][pArmor] = 0.0;
            AccountData[playerid][pHasArmor] = false;
            AccountData[playerid][pArmorEmpty] = true;

            ResetPlayerWeaponsEx(playerid);
            ShowTDN(playerid, NOTIFICATION_INFO, "Seluruh senjata dan armor anda telah dikembalikan.");
        }
        case 4: //DE
        {
            if(AccountData[playerid][pLevel] < 5)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda dapat memegang senjata jika sudah mencapai level 5 karakter!");

            GivePlayerWeaponEx(playerid, 24, 300, WEAPON_TYPE_FACTION);
            ShowItemBox(playerid, "Desert Eagle", "Received 1x", 348, 5);
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mengambil Desert Eagle");
        }
        case 5: //SG
        {
            if(AccountData[playerid][pLevel] < 5)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda dapat memegang senjata jika sudah mencapai level 5 karakter!");

            GivePlayerWeaponEx(playerid, 25, 350, WEAPON_TYPE_FACTION);
            ShowItemBox(playerid, "Shotgun", "Received 1x", 349, 5);
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mengambil Shotgun");
        }
        case 6: //MP5
        {
            if(AccountData[playerid][pLevel] < 5)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda dapat memegang senjata jika sudah mencapai level 5 karakter!");

            GivePlayerWeaponEx(playerid, 29, 650, WEAPON_TYPE_FACTION);
            ShowItemBox(playerid, "MP5", "Received 1x", 353, 5);
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mengambil MP5");
        }
        case 7: //M4
        {
            if(AccountData[playerid][pLevel] < 5)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda dapat memegang senjata jika sudah mencapai level 5 karakter!");

            GivePlayerWeaponEx(playerid, 31, 650, WEAPON_TYPE_FACTION);
            ShowItemBox(playerid, "M4", "Received 1x", 356, 5);
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mengambil M4");
        }
        case 8: //Combat shotgun
        {
            if(AccountData[playerid][pLevel] < 5)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda dapat memegang senjata jika sudah mencapai level 5 karakter!");

            GivePlayerWeaponEx(playerid, 27, 400, WEAPON_TYPE_FACTION);
            ShowItemBox(playerid, "Combat Shotgun", "Received 1x", 351, 5);
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mengambil Combat Shotgun");
        }
        case 9: //sniper rifle
        {
            if(AccountData[playerid][pLevel] < 5)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda dapat memegang senjata jika sudah mencapai level 5 karakter!");
                
            GivePlayerWeaponEx(playerid, 34, 400, WEAPON_TYPE_FACTION);
            ShowItemBox(playerid, "Sniper Rifle", "Received 1x", 358, 5);
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mengambil Sniper Rifle");
        }
    }
    return 1;
}
Dialog:PolisiDepositCash(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");
    if(AccountData[playerid][pFactionRank] < 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimum rank KOMPOL untuk akses menu faction!");
    
    if(isnull(inputtext))
    {
        return Dialog_Show(playerid, "PolisiDepositCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Kepolisian Deposit",
        "Error: Tidak dapat dikosongkan!\n\
        Mohon masukkan berapa jumlah deposit:", "Deposit", "Batal");
    }          

    if (!IsNumericEx(inputtext)) return Dialog_Show(playerid, "PolisiDepositCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Kepolisian Deposit",
        "Error: Masukkan hanya angka!\n\
        Mohon masukkan berapa jumlah deposit:", "Deposit", "Batal");

    if(strval(inputtext) < 1) return Dialog_Show(playerid, "PolisiDepositCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Kepolisian Deposit",
    "Error: Invalid amount, you can't deposit less than $1!\n\
    Mohon masukkan berapa jumlah deposit:", "Deposit", "Batal");

    if(strval(inputtext) > AccountData[playerid][pMoney]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");

    TakePlayerMoneyEx(playerid, strval(inputtext));
    PolisiMoneyVault += strval(inputtext);

    static frmtmny[128];
    mysql_format(g_SQL, frmtmny, sizeof(frmtmny), "UPDATE `stuffs` SET `polisimoneyvault` = %d WHERE `id` = 0", PolisiMoneyVault);
    mysql_pquery(g_SQL, frmtmny);
    ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil deposit $%s untuk Kepolisian Pahlawan Roleplay.", FormatMoney(strval(inputtext))));
    return 1;
}

Dialog:PolisiWithdrawCash(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");
    if(AccountData[playerid][pFactionRank] < 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimum rank KOMPOL untuk akses menu faction!");

    if(isnull(inputtext))
    {
        return Dialog_Show(playerid, "PolisiWithdrawCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Kepolisian Withdraw",
        "Error: Tidak dapat dikosongkan!\n\
       Mohon masukkan jumlah yang ingin ditarik:", "Withdraw", "Batal");
    }          

    if (!IsNumericEx(inputtext)) return Dialog_Show(playerid, "PolisiWithdrawCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Kepolisian Withdraw",
        "Error: Masukkan hanya angka!\n\
       Mohon masukkan jumlah yang ingin ditarik:", "Withdraw", "Batal");

    if(strval(inputtext) < 1) return Dialog_Show(playerid, "PolisiWithdrawCash", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Kepolisian Withdraw",
    "Error: Jumlah tidak valid, anda tidak dapat withdraw kurang dari $1!\n\
   Mohon masukkan jumlah yang ingin ditarik:", "Withdraw", "Batal");

    if(PolisiMoneyVault < RoundNegativeToPositive(strval(inputtext))) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid, saldo tidak cukup!");

    PolisiMoneyVault -= strval(inputtext);
    GivePlayerMoneyEx(playerid, strval(inputtext));

    static frmtmny[128];
    mysql_format(g_SQL, frmtmny, sizeof(frmtmny), "UPDATE `stuffs` SET `polisimoneyvault` = %d WHERE `id` = 0", PolisiMoneyVault);
    mysql_pquery(g_SQL, frmtmny);

    AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], strval(inputtext), "Kepolisian");

    ShowTDN(playerid, NOTIFICATION_SUCCESS, sprintf("Anda berhasil withdraw $%s dari Kepolisian Pahlawan Roleplay.", FormatMoney(strval(inputtext))));
    return 1;
}
Dialog:PolisiGarage(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pFaction] != FACTION_LSPD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");
    switch(listitem)
    {
        case 0: //keluarkan kendaraan
        {
            if(PlayerFactionVehicle[playerid][FACTION_LSPD] != INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah mengeluarkan kendaraan, simpan terlebih dahulu!");

            Dialog_Show(playerid, "PolisiGarageTakeoutveh", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Keluarkan Kendaraan", 
            "Cruiser LSPD\n\
            "GRAY"Cruiser SFPD\n\
            Cruiser LVPD\n\
            "GRAY"HPV1000\n\
            NRG-500\n\
            "GRAY"Premier\n\
            Police Ranger\n\
            "GRAY"Enforcer\n\
            Sultan\n\
            "GRAY"FBI Rancher\n\
            Cheetah\n\
            "GRAY"Bullet\n\
            Infernus\n\
            "GRAY"Turismo\n\
            Securicar\n\
            "GRAY"Barracuda\n\
            Mountain Bike\n\
            "GRAY"Sanchez\n\
            Yosemite", "Pilih", "Batal");
        }
        case 1: //simpan kendaraan
        {
            for(new x; x < MAX_FACTIONS; x++)
            {
                DestroyVehicle(PlayerFactionVehicle[playerid][x]);
                PlayerFactionVehicle[playerid][x] = INVALID_VEHICLE_ID;
            }
            LSPDPlayerCallsign[playerid][0] = EOS;
            
            static string[168];
            mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `demand_vehicles` WHERE `ownerid` = %d", AccountData[playerid][pID]);
            mysql_pquery(g_SQL, string);
            ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan tersebut telah tersimpan ke garasi faction.");
        }
    }
    return 1;
}
Dialog:PolisiGarageTakeoutveh(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        AccountData[playerid][pTempValue] = -1;
        return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    }
    if(AccountData[playerid][pFaction] != FACTION_LSPD) 
    {
        AccountData[playerid][pTempValue] = -1;
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");
    }

    new garageid = GetPlayerNearestFGarage(playerid);

    if(garageid  == -1)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan garasi faction anda!");

    for(new x; x < MAX_FACTIONS; x++)
    {
        DestroyVehicle(PlayerFactionVehicle[playerid][x]);
        PlayerFactionVehicle[playerid][x] = INVALID_VEHICLE_ID;
    }

    switch(listitem)
    {
        case 0: //cruiser LSPD
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 596;
            PlayerFactionVehStats[playerid][pFactVehColor1] = 25;
            PlayerFactionVehStats[playerid][pFactVehColor2] = 25;

            PlayerFactionVehicle[playerid][FACTION_LSPD] = CreateVehicle(596, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 25, 25, 60000, true);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1010);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1025);
            DestroyFactVehToys(PlayerFactionVehicle[playerid][FACTION_LSPD]);

            SetValidVehicleHealth(PlayerFactionVehicle[playerid][FACTION_LSPD], 2000.0); 
            VehicleCore[PlayerFactionVehicle[playerid][FACTION_LSPD]][vMaxHealth] = 2000.0;
            PlayerFactionVehStats[playerid][pFactVehMaxHealth] = 2000.0;
        }
        case 1: //cruiser SFPD
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 597;
            PlayerFactionVehStats[playerid][pFactVehColor1] = 25;
            PlayerFactionVehStats[playerid][pFactVehColor2] = 25;

            PlayerFactionVehicle[playerid][FACTION_LSPD] = CreateVehicle(597, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 25, 25, 60000, true);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1010);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1025);
            DestroyFactVehToys(PlayerFactionVehicle[playerid][FACTION_LSPD]);

            SetValidVehicleHealth(PlayerFactionVehicle[playerid][FACTION_LSPD], 2000.0); 
            VehicleCore[PlayerFactionVehicle[playerid][FACTION_LSPD]][vMaxHealth] = 2000.0;
            PlayerFactionVehStats[playerid][pFactVehMaxHealth] = 2000.0;
        }
        case 2: //cruiser LVPD
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 598;
            PlayerFactionVehStats[playerid][pFactVehColor1] = 25;
            PlayerFactionVehStats[playerid][pFactVehColor2] = 25;

            PlayerFactionVehicle[playerid][FACTION_LSPD] = CreateVehicle(598, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 25, 25, 60000, true);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1010);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1025);
            DestroyFactVehToys(PlayerFactionVehicle[playerid][FACTION_LSPD]);
            
            SetValidVehicleHealth(PlayerFactionVehicle[playerid][FACTION_LSPD], 2000.0); 
            VehicleCore[PlayerFactionVehicle[playerid][FACTION_LSPD]][vMaxHealth] = 2000.0;
            PlayerFactionVehStats[playerid][pFactVehMaxHealth] = 2000.0;
        }
        case 3: //HPV1000
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 523;
            PlayerFactionVehStats[playerid][pFactVehColor1] = 0;
            PlayerFactionVehStats[playerid][pFactVehColor2] = 1;
            PlayerFactionVehicle[playerid][FACTION_LSPD] = CreateVehicle(523, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 0, 1, 60000, true);
            DestroyFactVehToys(PlayerFactionVehicle[playerid][FACTION_LSPD]);

            SetValidVehicleHealth(PlayerFactionVehicle[playerid][FACTION_LSPD], 2000.0); 
            VehicleCore[PlayerFactionVehicle[playerid][FACTION_LSPD]][vMaxHealth] = 2000.0;
            PlayerFactionVehStats[playerid][pFactVehMaxHealth] = 2000.0;
        }
        case 4: //NRG-500
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 522;
            PlayerFactionVehStats[playerid][pFactVehColor1] = 127;
            PlayerFactionVehStats[playerid][pFactVehColor2] = 6;
            PlayerFactionVehicle[playerid][FACTION_LSPD] = CreateVehicle(522, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 127, 6, 60000, true);
            DestroyFactVehToys(PlayerFactionVehicle[playerid][FACTION_LSPD]);

            SetValidVehicleHealth(PlayerFactionVehicle[playerid][FACTION_LSPD], 2000.0); 
            VehicleCore[PlayerFactionVehicle[playerid][FACTION_LSPD]][vMaxHealth] = 2000.0;
            PlayerFactionVehStats[playerid][pFactVehMaxHealth] = 2000.0;
        }
        case 5: //Premier
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 426;
            PlayerFactionVehStats[playerid][pFactVehColor1] = 25;
            PlayerFactionVehStats[playerid][pFactVehColor2] = 25;

            PlayerFactionVehicle[playerid][FACTION_LSPD] = CreateVehicle(426, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 25, 25, 60000, true);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1010);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1025);
            DestroyFactVehToys(PlayerFactionVehicle[playerid][FACTION_LSPD]);

            SetValidVehicleHealth(PlayerFactionVehicle[playerid][FACTION_LSPD], 2000.0); 
            VehicleCore[PlayerFactionVehicle[playerid][FACTION_LSPD]][vMaxHealth] = 2000.0;
            PlayerFactionVehStats[playerid][pFactVehMaxHealth] = 2000.0;
        }
        case 6: //Ranger
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 599;
            PlayerFactionVehStats[playerid][pFactVehColor1] = 25;
            PlayerFactionVehStats[playerid][pFactVehColor2] = 25;

            PlayerFactionVehicle[playerid][FACTION_LSPD] = CreateVehicle(599, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 25, 25, 60000, false);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1010);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1025);
            DestroyFactVehToys(PlayerFactionVehicle[playerid][FACTION_LSPD]);

            SetValidVehicleHealth(PlayerFactionVehicle[playerid][FACTION_LSPD], 2000.0); 
            VehicleCore[PlayerFactionVehicle[playerid][FACTION_LSPD]][vMaxHealth] = 2000.0;
            PlayerFactionVehStats[playerid][pFactVehMaxHealth] = 2000.0;
        }
        case 7: //Enforcer
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 427;
            PlayerFactionVehStats[playerid][pFactVehColor1] = 25;
            PlayerFactionVehStats[playerid][pFactVehColor2] = 25;

            PlayerFactionVehicle[playerid][FACTION_LSPD] = CreateVehicle(427, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 25, 25, 60000, false);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1010);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1025);
            DestroyFactVehToys(PlayerFactionVehicle[playerid][FACTION_LSPD]);

            SetValidVehicleHealth(PlayerFactionVehicle[playerid][FACTION_LSPD], 4000.0); 
            VehicleCore[PlayerFactionVehicle[playerid][FACTION_LSPD]][vMaxHealth] = 4000.0;
            PlayerFactionVehStats[playerid][pFactVehMaxHealth] = 4000.0;
        }
        case 8: //Sultan
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 560;
            PlayerFactionVehStats[playerid][pFactVehColor1] = 25;
            PlayerFactionVehStats[playerid][pFactVehColor2] = 25;

            PlayerFactionVehicle[playerid][FACTION_LSPD] = CreateVehicle(560, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 25, 25, 60000, true);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1010);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1025);

            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][0] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][0], 0, "POLISI", 130, "Arial", 100, 1, -15616, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][0], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.009, 1.980, 0.290, 360.040, 279.000, 90.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][1] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][1], 0, "|||||", 130, "Arial", 50, 1, -15616, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][1], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.026, -2.368, 0.220, 0.000, 5.000, 90.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][2] = CreateDynamicObject(19620,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][2], PlayerFactionVehicle[playerid][FACTION_LSPD], 0.000, 0.000, 0.850, 0.000, 0.000, 0.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][3] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][3], 0, "______", 130, "Arial", 100, 1, -15616, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][3], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.009, -0.620, 0.812, 360.040, -274.000, -90.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][4] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][4], 0, "______", 130, "Arial", 100, 1, -15616, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][4], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.009, -0.620, 0.800, -360.040, 274.000, -90.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][5] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][5], 0, "SABHARA", 130, "Arial", 50, 0, -15616, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][5], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.009, -0.620, 0.792, 180.000, 90.000, 90.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][6] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][6], 0, "g", 140, "Webdings", 50, 1, -15616, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][6], PlayerFactionVehicle[playerid][FACTION_LSPD], -1.026, -1.789, 0.220, 0.000, 10.000, 0.000);

            SetValidVehicleHealth(PlayerFactionVehicle[playerid][FACTION_LSPD], 2000.0); 
            VehicleCore[PlayerFactionVehicle[playerid][FACTION_LSPD]][vMaxHealth] = 2000.0;
            PlayerFactionVehStats[playerid][pFactVehMaxHealth] = 2000.0;
        }
        case 9: //FBI Rancher
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 490;
            PlayerFactionVehStats[playerid][pFactVehColor1] = 25;
            PlayerFactionVehStats[playerid][pFactVehColor2] = 25;

            PlayerFactionVehicle[playerid][FACTION_LSPD] = CreateVehicle(490, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 25, 25, 60000, true);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1010);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1025);
            DestroyFactVehToys(PlayerFactionVehicle[playerid][FACTION_LSPD]);

            SetValidVehicleHealth(PlayerFactionVehicle[playerid][FACTION_LSPD], 2000.0); 
            VehicleCore[PlayerFactionVehicle[playerid][FACTION_LSPD]][vMaxHealth] = 2000.0;
            PlayerFactionVehStats[playerid][pFactVehMaxHealth] = 2000.0;
        }
        case 10: //Cheetah
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 415;
            PlayerFactionVehStats[playerid][pFactVehColor1] = 25;
            PlayerFactionVehStats[playerid][pFactVehColor2] = 25;

            PlayerFactionVehicle[playerid][FACTION_LSPD] = CreateVehicle(415, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 25, 25, 60000, true);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1010);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1025);
            DestroyFactVehToys(PlayerFactionVehicle[playerid][FACTION_LSPD]);

            SetValidVehicleHealth(PlayerFactionVehicle[playerid][FACTION_LSPD], 2000.0); 
            VehicleCore[PlayerFactionVehicle[playerid][FACTION_LSPD]][vMaxHealth] = 2000.0;
            PlayerFactionVehStats[playerid][pFactVehMaxHealth] = 2000.0;
        }
        case 11: //Bullet
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 541;
            PlayerFactionVehStats[playerid][pFactVehColor1] = 25;
            PlayerFactionVehStats[playerid][pFactVehColor2] = 25;

            PlayerFactionVehicle[playerid][FACTION_LSPD] = CreateVehicle(541, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 25, 25, 60000, true);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1010);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1025);
            DestroyFactVehToys(PlayerFactionVehicle[playerid][FACTION_LSPD]);

            SetValidVehicleHealth(PlayerFactionVehicle[playerid][FACTION_LSPD], 2000.0); 
            VehicleCore[PlayerFactionVehicle[playerid][FACTION_LSPD]][vMaxHealth] = 2000.0;
            PlayerFactionVehStats[playerid][pFactVehMaxHealth] = 2000.0;
        }
        case 12: //Infernus
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 411;
            PlayerFactionVehStats[playerid][pFactVehColor1] = 25;
            PlayerFactionVehStats[playerid][pFactVehColor2] = 25;

            PlayerFactionVehicle[playerid][FACTION_LSPD] = CreateVehicle(411, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 25, 25, 60000, true);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1010);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1025);
            DestroyFactVehToys(PlayerFactionVehicle[playerid][FACTION_LSPD]);

            SetValidVehicleHealth(PlayerFactionVehicle[playerid][FACTION_LSPD], 2000.0); 
            VehicleCore[PlayerFactionVehicle[playerid][FACTION_LSPD]][vMaxHealth] = 2000.0;
            PlayerFactionVehStats[playerid][pFactVehMaxHealth] = 2000.0;
        }
        case 13: //Turismo
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 451;
            PlayerFactionVehStats[playerid][pFactVehColor1] = 25;
            PlayerFactionVehStats[playerid][pFactVehColor2] = 25;

            PlayerFactionVehicle[playerid][FACTION_LSPD] = CreateVehicle(451, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 25, 25, 60000, true);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1010);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1025);
            DestroyFactVehToys(PlayerFactionVehicle[playerid][FACTION_LSPD]);

            SetValidVehicleHealth(PlayerFactionVehicle[playerid][FACTION_LSPD], 2000.0); 
            VehicleCore[PlayerFactionVehicle[playerid][FACTION_LSPD]][vMaxHealth] = 2000.0;
            PlayerFactionVehStats[playerid][pFactVehMaxHealth] = 2000.0;
        }
        case 14: //Securicar
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 428;
            PlayerFactionVehStats[playerid][pFactVehColor1] = 0;
            PlayerFactionVehStats[playerid][pFactVehColor2] = 0;

            PlayerFactionVehicle[playerid][FACTION_LSPD] = CreateVehicle(428, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 0, 0, 60000, true);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1010);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1025);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][0] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][0], 0, "LOS SANTOS", 140, "Arial", 40, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][0], PlayerFactionVehicle[playerid][FACTION_LSPD], -1.160, -0.520, 0.220, 0.000, 0.000, 0.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][1] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][1], 0, "POLICE DEPARTMENT", 140, "Arial", 40, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][1], PlayerFactionVehicle[playerid][FACTION_LSPD], -1.160, -1.710, 0.220, 0.000, 0.000, 0.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][2] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][2], 0, "S.W.A.T", 140, "Arial", 70, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][2], PlayerFactionVehicle[playerid][FACTION_LSPD], -1.160, -2.361, 0.830, 0.000, 0.000, 0.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][3] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][3], 0, "SPECIAL WEAPONS", 140, "Arial", 40, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][3], PlayerFactionVehicle[playerid][FACTION_LSPD], -1.160, -0.790, 0.040, 0.000, 0.000, 0.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][4] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][4], 0, "AND TACTICS", 140, "Arial", 40, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][4], PlayerFactionVehicle[playerid][FACTION_LSPD], -1.160, -1.920, 0.040, 0.000, 0.000, 0.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][5] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][5], 0, "METRO POLICE", 140, "Arial", 40, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][5], PlayerFactionVehicle[playerid][FACTION_LSPD], -1.160, -2.341, 1.040, 0.000, 0.000, 0.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][6] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][6], 0, "S.W.A.T", 140, "Arial", 70, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][6], PlayerFactionVehicle[playerid][FACTION_LSPD], 1.158, -2.361, 0.830, 0.000, 0.000, 180.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][7] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][7], 0, "METRO POLICE", 140, "Arial", 40, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][7], PlayerFactionVehicle[playerid][FACTION_LSPD], 1.159, -2.341, 1.040, 0.000, 0.000, 180.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][8] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][8], 0, "POLICE DEPARTMENT", 140, "Arial", 40, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][8], PlayerFactionVehicle[playerid][FACTION_LSPD], 1.160, -0.520, 0.220, 0.000, 0.000, 180.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][9] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][9], 0, "LOS SANTOS", 140, "Arial", 40, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][9], PlayerFactionVehicle[playerid][FACTION_LSPD], 1.159, -1.710, 0.220, 0.000, 0.000, 180.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][10] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][10], 0, "AND TACTICS", 140, "Arial", 40, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][10], PlayerFactionVehicle[playerid][FACTION_LSPD], 1.160, -0.299, 0.040, 0.000, 0.000, 180.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][11] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][11], 0, "SPECIAL WEAPONS", 140, "Arial", 40, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][11], PlayerFactionVehicle[playerid][FACTION_LSPD], 1.159, -1.432, 0.040, 0.000, 0.000, 180.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][12] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][12], 0, "S.W.A.T", 140, "Arial", 40, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][12], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.010, 1.250, 1.090, 0.000, 0.000, 270.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][13] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][13], 0, "S.W.A.T", 140, "Arial", 40, 1, -1, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][13], PlayerFactionVehicle[playerid][FACTION_LSPD], 0.009, -3.010, -0.679, 0.000, 0.000, 450.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][14] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][14], PlayerFactionVehicle[playerid][FACTION_LSPD], 0.760, 2.820, -0.540, 0.000, 0.000, 180.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][15] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][15], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.760, 2.820, -0.540, 360.000, 180.000, 180.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][16] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][16], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.289, 2.699, 0.040, 360.000, 0.000, 180.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][17] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][17], PlayerFactionVehicle[playerid][FACTION_LSPD], 0.280, 2.699, 0.040, 0.000, 180.000, 180.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][18] = CreateDynamicObject(19419,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][18], PlayerFactionVehicle[playerid][FACTION_LSPD], 0.000, 0.790, 1.300, 0.000, 0.000, 0.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][19] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][19], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.460, -3.020, -0.540, 0.000, 360.000, 0.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][20] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][20], PlayerFactionVehicle[playerid][FACTION_LSPD], 0.460, -3.020, -0.540, 360.000, 180.000, 0.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][21] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][21], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.460, -2.980, 1.449, 0.000, 180.000, 0.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][22] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][22], PlayerFactionVehicle[playerid][FACTION_LSPD], 0.460, -2.980, 1.450, 0.000, 360.000, 0.000);

            SetValidVehicleHealth(PlayerFactionVehicle[playerid][FACTION_LSPD], 4000.0); 
            VehicleCore[PlayerFactionVehicle[playerid][FACTION_LSPD]][vMaxHealth] = 4000.0;
            PlayerFactionVehStats[playerid][pFactVehMaxHealth] = 4000.0;
        }
        case 15: //barracuda
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 601;
            PlayerFactionVehStats[playerid][pFactVehColor1] = 0;
            PlayerFactionVehStats[playerid][pFactVehColor2] = 0;

            PlayerFactionVehicle[playerid][FACTION_LSPD] = CreateVehicle(601, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 0, 0, 60000, true);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1010);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1025);
            DestroyFactVehToys(PlayerFactionVehicle[playerid][FACTION_LSPD]);

            SetValidVehicleHealth(PlayerFactionVehicle[playerid][FACTION_LSPD], 6000.0); 
            VehicleCore[PlayerFactionVehicle[playerid][FACTION_LSPD]][vMaxHealth] = 6000.0;
            PlayerFactionVehStats[playerid][pFactVehMaxHealth] = 6000.0;
        }
        case 16: //MTB
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 510;
            PlayerFactionVehicle[playerid][FACTION_LSPD] = CreateVehicle(510, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 0, 1, 60000, false);
            DestroyFactVehToys(PlayerFactionVehicle[playerid][FACTION_LSPD]);
        }
        case 17: //sanchez
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 468;
            PlayerFactionVehicle[playerid][FACTION_LSPD] = CreateVehicle(468, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 25, 25, 60000, false);

            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][0] = CreateDynamicObject(19476,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][0], 0, "POLISI", 80, "Arial", 25, 1, -15616, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][0], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.095, 0.150, 0.321, -48.500, -29.299, 177.200);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][1] = CreateDynamicObject(19476,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][1], 0, "POLISI", 80, "Arial", 25, 1, -15616, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][1], PlayerFactionVehicle[playerid][FACTION_LSPD], 0.099, 0.145, 0.318, 42.199, -17.400, 3.399);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][2] = CreateDynamicObject(19476,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][2], 0, "8", 80, "Webdings", 50, 1, -15616, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][2], PlayerFactionVehicle[playerid][FACTION_LSPD], 0.162, -0.484, 0.124, -12.300, -0.399, 6.799);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][3] = CreateDynamicObject(19476,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][3], 0, "8", 80, "Webdings", 50, 1, -15616, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][3], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.157, -0.485, 0.124, 0.000, 2.200, -3.799);
        }
        case 18: //yosemite
        {
            PlayerFactionVehStats[playerid][pFactVehModel] = 554;
            PlayerFactionVehStats[playerid][pFactVehColor1] = 6;
            PlayerFactionVehStats[playerid][pFactVehColor2] = 127;

            PlayerFactionVehicle[playerid][FACTION_LSPD] = CreateVehicle(554, FactGarageData[garageid][GarageSpawnPos][0], FactGarageData[garageid][GarageSpawnPos][1], FactGarageData[garageid][GarageSpawnPos][2], FactGarageData[garageid][GarageSpawnPos][3], 6, 127, 60000, true);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1010);
            AddVehicleComponent(PlayerFactionVehicle[playerid][FACTION_LSPD], 1025);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][0] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][0], 0, "<<", 130, "Impact", 130, 1, -16777216, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][0], PlayerFactionVehicle[playerid][FACTION_LSPD], -1.229, 0.640, 0.050, 0.000, 0.000, 0.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][1] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][1], 0, "POLISI", 100, "Arial Black", 65, 1, -16777216, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][1], PlayerFactionVehicle[playerid][FACTION_LSPD], -1.229, -0.489, 0.080, 0.000, 0.000, 0.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][2] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][2], 0, "EMERGENCY", 140, "Arial Black", 35, 1, -4877296, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][2], PlayerFactionVehicle[playerid][FACTION_LSPD], -1.199, -2.299, 0.230, 0.000, 0.000, 0.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][3] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][3], 0, "POLISI", 100, "Arial Black", 65, 1, -16777216, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][3], PlayerFactionVehicle[playerid][FACTION_LSPD], 1.220, -0.469, 0.080, 0.000, 0.000, 180.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][4] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][4], 0, "CALL 110", 140, "Arial Black", 35, 1, -4877296, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][4], PlayerFactionVehicle[playerid][FACTION_LSPD], -1.219, -2.389, 0.120, 360.000, 360.000, 360.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][5] = CreateDynamicObject(19419,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][5], PlayerFactionVehicle[playerid][FACTION_LSPD], 0.000, -0.009, 1.030, 0.000, 0.000, 0.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][6] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][6], 0, ">>", 130, "Impact", 130, 1, -16777216, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][6], PlayerFactionVehicle[playerid][FACTION_LSPD], 1.220, 0.640, 0.050, 0.000, 0.000, 180.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][7] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][7], 0, "EMERGENCY", 140, "Arial Black", 35, 1, -4877296, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][7], PlayerFactionVehicle[playerid][FACTION_LSPD], 1.210, -2.294, 0.230, 0.000, 0.000, 540.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][8] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][8], 0, "CALL 110", 140, "Arial Black", 35, 1, -4877296, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][8], PlayerFactionVehicle[playerid][FACTION_LSPD], 1.220, -2.379, 0.120, 0.000, 0.000, 180.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][9] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][9], 0, "POLISI", 140, "Arial Black", 75, 1, -4877296, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][9], PlayerFactionVehicle[playerid][FACTION_LSPD], 0.010, 0.657, 0.851, 0.000, 48.099, 270.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][10] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][10], 0, ">", 120, "Calibri", 195, 1, -4877296, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][10], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.159, 1.990, 0.406, 4.799, 90.000, 900.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][11] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][11], 0, ">", 120, "Calibri", 195, 1, -4877296, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][11], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.159, 1.720, 0.427, 364.000, 450.000, 540.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][12] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][12], PlayerFactionVehicle[playerid][FACTION_LSPD], 0.230, 2.591, 0.170, 0.000, 0.000, 180.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][13] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][13], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.230, 2.591, 0.170, 360.000, 180.000, 180.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][14] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][14], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.750, 2.631, -0.120, 0.000, 0.000, 180.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][15] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][15], PlayerFactionVehicle[playerid][FACTION_LSPD], 0.739, 2.631, -0.120, 360.000, 180.000, 180.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][16] = CreateDynamicObject(19285,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][16], PlayerFactionVehicle[playerid][FACTION_LSPD], 0.000, 0.080, 1.030, 0.000, 0.000, 0.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][17] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][17], 0, "POLISI", 140, "Arial Black", 80, 1, -4877296, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][17], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.018, -2.899, 0.000, 0.000, 0.000, 90.000);
            FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][18] = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][18], 0, "<", 110, "Calibri", 130, 1, -4877296, 0, 1);
            AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVehicle[playerid][FACTION_LSPD]][18], PlayerFactionVehicle[playerid][FACTION_LSPD], -0.179, -2.900, 0.220, 270.000, 0.000, 450.000);
        }
    }

    FactionVehHasCallsign[PlayerFactionVehicle[playerid][FACTION_LSPD]] = false;
    LSPDPlayerCallsign[playerid][0] = EOS;

    PlayerFactionVehStats[playerid][pFactVehFuel] = 100;
    PlayerFactionVehStats[playerid][pFactVehBodyUpgraded] = true;
    PlayerFactionVehStats[playerid][pFactVehBodyBroken] = false;
    PlayerFactionVehStats[playerid][pFactVehLocked] = false;

    VehicleCore[PlayerFactionVehicle[playerid][FACTION_LSPD]][vCoreFuel] = 100;
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_LSPD]][vIsBodyUpgraded] = true;
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_LSPD]][vIsBodyBroken] = false;
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_LSPD]][vCoreLocked] = false;
    PutPlayerInVehicleEx(playerid, PlayerFactionVehicle[playerid][FACTION_LSPD], 0);
    SwitchVehicleEngine(PlayerFactionVehicle[playerid][FACTION_LSPD], true);
    SwitchVehicleDoors(PlayerFactionVehicle[playerid][FACTION_LSPD], false);

    
    static string[555];
    mysql_format(g_SQL, string, sizeof(string), "INSERT INTO `demand_vehicles` (`ownerid`, `model`, `vehX`, `vehY`, `vehZ`, `vehA`, `damage0`, `damage1`, `damage2`, `damage3`, `health`, `fuel`, `locked`, `world`, `color1`, `color2`) VALUES (%d, %d, '%f', '%f', '%f', '0.0', 0, 0, 0, 0, '2000.0', %d, %d, 0, %d, %d)", 
    AccountData[playerid][pID],
    PlayerFactionVehStats[playerid][pFactVehModel],
    FactGarageData[garageid][GarageSpawnPos][0],
    FactGarageData[garageid][GarageSpawnPos][1],
    FactGarageData[garageid][GarageSpawnPos][2],
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_LSPD]][vCoreFuel],
    VehicleCore[PlayerFactionVehicle[playerid][FACTION_LSPD]][vCoreLocked],
    PlayerFactionVehStats[playerid][pFactVehColor1],
    PlayerFactionVehStats[playerid][pFactVehColor2]);
    mysql_pquery(g_SQL, string);
    return 1;
}
Dialog:PolisiPanel(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    new targetid = NearestSingle[playerid];
    if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if(!IsPlayerNearPlayer(playerid, targetid, 3.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak dekat dengan anda!");
    if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Karakter anda terluka parah saat ini!");
    switch(listitem)
    {
        case 0: //Periksa Lisensi
        {
            if(!CheckPlayerLicense(targetid))
            {
                Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Licenses Checking", 
                "The player doesn't have a lisensi.", "Tutup", "");
                return 1;
            }

            ShowLCTD(targetid, playerid);
            
            NearestSingle[playerid] = INVALID_PLAYER_ID;
        }
        case 1: //Invoice Belum Terbayar
        {
            new xjjs[600], count;
            format(xjjs, sizeof(xjjs), "#\tNama Tagihan\tPemberi\tNominal Tagihan\n");
            for(new id; id < MAX_INVOICES; ++id)
            {
                if(InvoiceData[targetid][id][invoiceExists] && InvoiceData[targetid][id][invoiceOwner] == AccountData[targetid][pID]) 
                {
                    format(xjjs, sizeof(xjjs), "%s"WHITE"%d\t"WHITE"%s\t"YELLOW"%s\t"RED"%s\n", xjjs, id + 1, InvoiceData[targetid][id][invoiceName], InvoiceData[targetid][id][invoiceIssuerName], FormatMoney(InvoiceData[targetid][id][invoiceCost]));
                    count++;
                }
            }

            if(count == 0)
            {
                Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Unpaid Invoice", 
                "This person has no invoices.", "Tutup", "");
            }
            else
            {
                Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Unpaid Invoice", 
                xjjs, "Tutup", "");
            }
            NearestSingle[playerid] = INVALID_PLAYER_ID;
        }
        case 2: //Kartu Identitas
        {
            if(!AccountData[targetid][pHasKTP]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak memiliki Kartu Tanda Penduduk/sudah expired!");
            
            ShowIDCTD(targetid, playerid);
        }
        case 3: //Geledah
        {
            ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, false, false, false, false, 0, true);

            new str[1218], count;
            format(str, sizeof(str), "Nama Item\tJumlah\n");
            for(new index; index < MAX_INVENTORY; index++)
            {
                if(InventoryData[targetid][index][invExists])
                {
                    for(new i; i < sizeof(g_aInventoryItems); i ++) if (!strcmp(g_aInventoryItems[i][e_InventoryItem], InventoryData[targetid][index][invItem], true))
                    {
                        if (i % 2 == 0)
                        {
                            format(str, sizeof(str), "%s"WHITE"%s\t"WHITE"%d\n", str, InventoryData[targetid][index][invItem], InventoryData[targetid][index][invQuantity]);
                        }
                        else {
                            format(str, sizeof(str), "%s"GRAY"%s\t"GRAY"%d\n", str, InventoryData[targetid][index][invItem], InventoryData[targetid][index][invQuantity]);
                        }
                        PlayerListitem[playerid][count++] = index;
                    }
                }
            }

            if(count == 0)
            {
                Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Geledah", 
                "Pemain tersebut tidak memiliki item apapun!", "Tutup", "");
            }
            else
            {
                Dialog_Show(playerid, "FactionConsficating", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Geledah", str, "Pilih", "Batal");
            }
        }
        case 4: //Borgol
        {
            AccountData[targetid][pCuffed] = true;
            GameTextForPlayer(targetid, "~r~Cuffed", 3500, 3);
            SetPlayerSpecialAction(targetid, SPECIAL_ACTION_CUFFED);
            ShowTDN(targetid, NOTIFICATION_INFO, "Anda telah diborgol!");
            NearestSingle[playerid] = INVALID_PLAYER_ID;
        }
        case 5: //Buka Borgol
        {
            AccountData[targetid][pCuffed] = false;
            GameTextForPlayer(targetid, "~g~Uncuffed", 3500, 3);
            SetPlayerSpecialAction(targetid, SPECIAL_ACTION_NONE);
            ShowTDN(targetid, NOTIFICATION_INFO, "Borgol anda telah dilepas!");
            NearestSingle[playerid] = INVALID_PLAYER_ID;
        }
        case 6: //Seret
        {
            if(AccountData[playerid][DraggingID] != INVALID_PLAYER_ID)
            {
                AccountData[playerid][DraggingID] = INVALID_PLAYER_ID;
                if(IsPlayerConnected(AccountData[playerid][DraggingID]))
                {
                    AccountData[AccountData[playerid][DraggingID]][pGetDraggedBy] = INVALID_PLAYER_ID;
                }
                TogglePlayerControllable(targetid, true);
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah berhenti menggendong seseorang.");
                return 1;
            }

            foreach(new i: Player)
            {
                if(AccountData[i][DraggingID] == playerid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menyeret seseorang yang sedang menyeret orang lain!");
            }

            AccountData[playerid][DraggingID] = targetid;
            AccountData[targetid][pGetDraggedBy] = playerid;
            TogglePlayerControllable(targetid, false);
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menggendong seseorang.");
            NearestSingle[playerid] = INVALID_PLAYER_ID;
        }
        case 7: //Masukkan Mobil
        {
            new vehid = GetNearestVehicleToPlayer(playerid, 4.0, false);
            if(vehid != INVALID_VEHICLE_ID)
            {
                if(GetEmptyBackSeat(vehid) == INVALID_SEAT_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kursi kosong di belakang!");
                PutPlayerInVehicleEx(targetid, vehid, GetEmptyBackSeat(vehid));
                TogglePlayerControllable(targetid, false);
                AccountData[targetid][pDetained] = true;
                ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil memasukkan Pemain tersebut secara paksa.");
            }
            NearestSingle[playerid] = INVALID_PLAYER_ID;
        }
        case 8: //Keluarkan Paksa
        {
            if(!AccountData[targetid][pDetained]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak sedang di-detain!");
            TogglePlayerControllable(targetid, true);
            RemovePlayerFromVehicle(targetid);
            AccountData[targetid][pDetained] = false;
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menendang Pemain tersebut dari kendaraan.");
            NearestSingle[playerid] = INVALID_PLAYER_ID;
        }
        case 9: //Invoice Manual
        {
            if(!IsPlayerInAnyVehicle(playerid))
            {
                SetPlayerAttachedObject(playerid, 9, 19786, 5, 0.182999, 0.048999, -0.112999, -66.699935, -23.799949, -116.699996, 0.130999, 0.136000, 0.142000, 0, 0);
    		    ApplyAnimation(playerid, "INT_SHOP","shop_loop", 4.1, true, false, false, true, 0, true);
            }

            Dialog_Show(playerid, "InvoiceSetName", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Invoice", 
            "Mohon masukkan nama dari invoice ini:", "Input", "Batal");
        }
        case 10: //penjarakan
        {
            Dialog_Show(playerid, "PolisiArrest", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Penjarakan",
            "Masukkan jumlah menit yang ingin diberikan:", "Input", "Batal");
        }
        case 11: //ambil uang kotor
        {
            if(AccountData[targetid][pDirtyMoney] < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak memiliki dirty money!");

            new jhj[258];
            format(jhj, sizeof(jhj), "This player's dirty money "RED"$%s\n\
            "YELLOW"Do you want to take all of them?", FormatMoney(AccountData[targetid][pDirtyMoney]));
            Dialog_Show(playerid, "ConsfDirt", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Dirty Money", jhj, "Yes", "Batal");
        }
        case 12: //cek senjata
        {
            new lstr[555], weaponid, ammo, count;
            format(lstr, sizeof(lstr), "Slot #ID\tNama\tPeluru\n");
            for(new i; i < 13; i ++)
            {
                GetPlayerWeaponData(targetid, i, weaponid, ammo);

                if(weaponid > 0)
                {
                    count++;
                    format(lstr, sizeof(lstr), "%s"RED"%d\t"RED"%s\t"RED"%d\n", lstr, i, ReturnWeaponName(weaponid), ammo);
                }
            }
            if(count > 0)
            {
                Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Senjata", lstr,"Tutup","");
            }
            else
            {
                Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Senjata", "The player doesn't have any weapon!","Tutup","");
            }
        }
        case 13: //sita senjata
        {
            ResetPlayerWeaponsEx(targetid);
            ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyita seluruh senjata Pemain tersebut.");
            SIM(targetid, "Seluruh senjata yang anda miliki telah disita oleh "RED"%s [%s] (ID: %d)", AccountData[playerid][pName], AccountData[playerid][pUCP], playerid);

            NearestSingle[playerid] = INVALID_PLAYER_ID;
        }
    }
    return 1;
}

Dialog:ConsfDirt(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    new targetid = NearestSingle[playerid];
    if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if(!IsPlayerNearPlayer(playerid, targetid, 3.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak dekat dengan anda!");
    if(AccountData[targetid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sedang melakukan sesuatu, harap tunggu!");
    
    AccountData[targetid][pDirtyMoney] = 0;

    SIM(targetid, "Seluruh dirty money anda telah disita oleh "RED"%s [%s] (ID: %d)", AccountData[playerid][pName], AccountData[playerid][pUCP], playerid);
    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil menyita seluruh dirty money Pemain tersebut.");
    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
    SendRPMeAboveHead(playerid, "Menyita seluruh dirty money dari orang di depannya.");

    NearestSingle[playerid] = INVALID_PLAYER_ID;
    return 1;
}
Dialog:PolisiArrest(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    
    new targetid = NearestSingle[playerid];
    if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if(!IsPlayerNearPlayer(playerid, targetid, 3.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak dekat dengan anda!");

    if(isnull(inputtext)) return  Dialog_Show(playerid, "PolisiArrest", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Penjarakan",
    "Error: Tidak dapat dikosongkan!\n\
    Masukkan jumlah menit yang ingin diberikan:", "Input", "Batal");

    if(!IsNumericEx(inputtext)) return  Dialog_Show(playerid, "PolisiArrest", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Penjarakan",
    "Error: Masukkan hanya angka!\n\
    Masukkan jumlah menit yang ingin diberikan:", "Input", "Batal");

    static string[268];
    mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `mdc_charges` WHERE `ownerid` = %d AND `status` = 1", AccountData[targetid][pID]);
    mysql_pquery(g_SQL, string, "OnArrestCheckCharges", "ids", playerid, targetid, inputtext);
    return 1;
}
Dialog:PolisiPDMMenu(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    
    switch(listitem)
    {
        case 0: //interaksi kendaraan
        {
            new vehid = GetNearestVehicleToPlayer(playerid, 4.0, false);
            if(vehid == INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan di dekat anda!");

            NearestVehicleID[playerid] = vehid;
            Dialog_Show(playerid, "PolisiPDMVeh", DIALOG_STYLE_LIST, 
            "{DA9100}Pahlawan Roleplay "WHITE"- Interaksi Kendaraan", 
            "Informasi Kendaraan\n\
            "GRAY"Membobol Kendaraan\n\
            Menyita Kendaraan ke Asuransi\n\
            "GRAY"Menyita Kendaraan ke Samsat", "Pilih", "Batal");
        }
        case 1: //mengeluarkan objek
        {
            Dialog_Show(playerid, "PolisiPDMObject", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Keluarkan Object", 
            "Kerucut\n\
            "GRAY"Pembatas Jalan\n\
            Ranjau Kendaraan", "Pilih", "Batal");
        }
        case 2: //list tahanan
        {
            new hhh[1524], count;
            format(hhh, sizeof(hhh), "Nama\tDurasi Hukuman\n");
            foreach(new i : Player) if(i != playerid)
            {
                if(AccountData[i][pArrested] && AccountData[i][pArrestTime] > 0)
                {
                    format(hhh, sizeof(hhh), "%s%s\t%s\n", hhh, GetPlayerRoleplayName(i), GetFormatTime(AccountData[i][pArrestTime]));
                    ListedUser[playerid][count++] = i;
                }
            }
            if(!count) 
            {
                PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                return Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- List Tahanan", "Tidak ada tahanan yang sedang dipenjara!", "Tutup", "");
            }
            Dialog_Show(playerid, "PolisiListPrison", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- List Tahanan", hhh, "Lepas", "Batal");
        }
    }
    return 1;
}
Dialog:PolisiPDMVeh(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    new vehid = NearestVehicleID[playerid];
    if(!IsValidVehicle(vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut tidak ada di dalam server!");
    if(!IsPlayerNearVehicle(playerid, vehid, 3.5)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut tidak dekat dengan anda!");

    switch(listitem)
    {
        case 0: //informasi kendaraan
        {
            new hjh[512];
            new pv = Vehicle_GetIterID(vehid);
            if(pv == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan tersebut bukanlah kendaraan pribadi!");

            format(hjh, sizeof(hjh), "Nama Kendaraan: %s\n\
            Plat Kendaraan: %s\n\
            Status Kendaraan: %s\n\
            Nama Pemilik: %s", GetVehicleModelName(PlayerVehicle[pv][pVehModelID]), PlayerVehicle[pv][pVehPlate], (PlayerVehicle[pv][pVehRentTime] != 0) ? ("Rental") : ("Dimiliki"), GetVehicleOwnerName(pv));
            Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Info Kendaraan", 
            hjh, "Tutup", "");

            NearestVehicleID[playerid] = INVALID_VEHICLE_ID;
        }
        case 1: //membobol kendaraaan
        {
            if(!VehicleCore[vehid][vCoreLocked]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut tidak sedang dikunci!");

            ApplyAnimation(playerid, "AIRPORT", "thrw_barl_thrw", 2.00, true, false, false, false, false, true);

            AccountData[playerid][pActivityTime] = 1;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMBOBOL");
            ShowProgressBar(playerid);

            AccountData[playerid][pTempVehID] = vehid;
            pBreakingVehDoorTimer[playerid] = true;
        }
        case 2: //menyita ke asuransi
        {
            new pv = Vehicle_GetIterID(vehid);
            if(pv == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan tersebut bukanlah kendaraan pribadi!");

            ApplyAnimation(playerid, "COP_AMBIENT", "Copbrowse_loop", 2.33, true, false, false, false, false, true);

            AccountData[playerid][pActivityTime] = 1;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENYITA ASURANSI");
            ShowProgressBar(playerid);

            AccountData[playerid][pTempVehIterID] = pv;
            pImpoundingInsuTimer[playerid] = true;
        }
        case 3: //menyita ke samsat
        {
            new pv = Vehicle_GetIterID(vehid);
            if(pv == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan tersebut bukanlah kendaraan pribadi!");

            Dialog_Show(playerid, "PolisiPDMImpound", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Penyitaan Kendaraan", 
            "Harap masukkan sesuai format yang ada di bawah ini!\n\
            [Durasi sita (hari)] [Denda] [Alasan]", "Input", "Batal");
        }
    }
    return 1;
}
Dialog:PolisiPDMImpound(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    new vehid = NearestVehicleID[playerid];
    if(!IsValidVehicle(vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut tidak ada di dalam server!");
    if(!IsPlayerNearVehicle(playerid, vehid, 3.5)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut tidak dekat dengan anda!");
    
    if(isnull(inputtext)) return Dialog_Show(playerid, "PolisiPDMImpound", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Penyitaan Kendaraan", 
    "Error: Tidak dapat dikosongkan!\n\
    Harap masukkan sesuai format yang ada di bawah ini!\n\
    [Durasi sita (hari)] [Denda] [Alasan]", "Input", "Batal");
    
    new durasi, duration, denda, reason[128];
    if(sscanf(inputtext, "dds[128]", duration, denda, reason))
    {
        return Dialog_Show(playerid, "PolisiPDMImpound", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Penyitaan Kendaraan", 
        "Error: Format salah!\n\
        Harap masukkan sesuai format yang ada di bawah ini!\n\
        [Durasi sita (hari)] [Denda] [Alasan]", "Input", "Batal");
    }

    if(duration < 1 || duration > 3) return Dialog_Show(playerid, "PolisiPDMImpound", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Penyitaan Kendaraan", 
    "Error: Durasi sita harus 1 - 3 hari saja!\n\
    Harap masukkan sesuai format yang ada di bawah ini!\n\
    [Durasi sita (hari)] [Denda] [Alasan]", "Input", "Batal");

    if(denda < 1) return Dialog_Show(playerid, "PolisiPDMImpound", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Penyitaan Kendaraan", 
    "Error: Denda tidak dapat kurang dari $1!\n\
    Harap masukkan sesuai format yang ada di bawah ini!\n\
    [Durasi sita (hari)] [Denda] [Alasan]", "Input", "Batal");

    new pv = Vehicle_GetIterID(vehid);
    if(pv == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jenis kendaraan tersebut bukanlah kendaraan pribadi!");

    ApplyAnimation(playerid, "COP_AMBIENT", "Copbrowse_loop", 2.33, true, false, false, false, false, true);

    AccountData[playerid][pActivityTime] = 1;
    PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENYITA SAMSAT");
    ShowProgressBar(playerid);

    durasi = gettime() + (duration * 86400);
    strcopy(PlayerVehicle[pv][pVehImpoundReason], reason);

    PlayerVehicle[pv][pVehImpounded] = true;
    PlayerVehicle[pv][pVehImpoundDuration] = durasi;
    PlayerVehicle[pv][pVehImpoundFee] = denda;

    AccountData[playerid][pTempVehIterID] = pv;
    pImpoundingSamsatTimer[playerid] = true;
    return 1;
}
Dialog:PolisiPDMObject(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    switch(listitem)
    {
        case 0: //kerucut
        {
            if(IsValidDynamicObject(AccountData[playerid][PoliceConeObjid]))
            {
                DestroyDynamicObject(AccountData[playerid][PoliceConeObjid]);
                AccountData[playerid][PoliceConeObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

                SendRPMeAboveHead(playerid, "Mengambil kembali kerucut.");
                return 1;
            }

            if(DestroyDynamicObject(AccountData[playerid][PoliceConeObjid]))
                AccountData[playerid][PoliceConeObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

            new Float:X, Float:Y, Float:Z, Float:Ang;
            GetPlayerPos(playerid, X, Y, Z);
            Ang = GetXYInFrontOfPlayer(playerid, X, Y, 5.0);
            AccountData[playerid][PoliceConeObjid] = CreateDynamicObject(1238, X, Y, Z-0.9, 0.0, 0.0, Ang, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), -1, 300.0);

            SendRPMeAboveHead(playerid, "Meletakkan kerucut.");
        }
        case 1: //pembatas jalan
        {
            if(IsValidDynamicObject(AccountData[playerid][PoliceRoadblockObjid]))
            {
                DestroyDynamicObject(AccountData[playerid][PoliceRoadblockObjid]);
                AccountData[playerid][PoliceRoadblockObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

                SendRPMeAboveHead(playerid, "Mengambil kembali pembatas jalan.");
                return 1;
            }

            if(DestroyDynamicObject(AccountData[playerid][PoliceRoadblockObjid]))
                AccountData[playerid][PoliceRoadblockObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

            new Float:X, Float:Y, Float:Z, Float:Ang;
            GetPlayerPos(playerid, X, Y, Z);
            Ang = GetXYInFrontOfPlayer(playerid, X, Y, 5.0);
            AccountData[playerid][PoliceRoadblockObjid] = CreateDynamicObject(1422, X, Y, Z-0.9, 0.0, 0.0, Ang, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), -1, 300.0);

            SendRPMeAboveHead(playerid, "Meletakkan pembatas jalan.");
        }
        case 2: //ranjau kendaraan
        {
            if(IsValidDynamicObject(AccountData[playerid][PoliceSpikeObjid]) || IsValidDynamicArea(AccountData[playerid][PoliceSpikeArea]))
            {
                DestroyDynamicObject(AccountData[playerid][PoliceSpikeObjid]);
                AccountData[playerid][PoliceSpikeObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

                DestroyDynamicArea(AccountData[playerid][PoliceSpikeArea]);
                AccountData[playerid][PoliceSpikeArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

                SendRPMeAboveHead(playerid, "Mengambil kembali ranjau kendaraan.");
                return 1;
            }

            if(DestroyDynamicObject(AccountData[playerid][PoliceSpikeObjid]))
                AccountData[playerid][PoliceSpikeObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
            
            if(DestroyDynamicArea(AccountData[playerid][PoliceSpikeArea]))
                AccountData[playerid][PoliceSpikeArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

            new Float:X, Float:Y, Float:Z, Float:Ang;
            GetPlayerPos(playerid, X, Y, Z);
            Ang = GetXYInFrontOfPlayer(playerid, X, Y, 5.0);
            AccountData[playerid][PoliceSpikeObjid] = CreateDynamicObject(2892, X, Y, Z-1, 0.0, 0.0, Ang, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), -1, 300.0);
            AccountData[playerid][PoliceSpikeArea] = CreateDynamicRectangle(X-2, Y-6, X+2, Y+6);

            SendRPMeAboveHead(playerid, "Meletakkan ranjau kendaraan.");
        }
    }
    return 1;
}
Dialog:PolisiListPrison(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    
    if(listitem == -1) return 1;
    Temptargetid[playerid] = ListedUser[playerid][listitem];
    if(Temptargetid[playerid] == -1) return 1;

    Dialog_Show(playerid, PolisiPrisonFree, DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- List Tahanan", 
    sprintf("Are you sure you want to free %s?", GetPlayerRoleplayName(Temptargetid[playerid])), "Yes", "No");
    return 1;
}
Dialog:PolisiPrisonFree(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(!IsPlayerConnected(Temptargetid[playerid])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    AccountData[Temptargetid[playerid]][pArrested] = false;
    AccountData[Temptargetid[playerid]][pArrestTime] = 0;

    SetPlayerInteriorEx(Temptargetid[playerid], 0);
    SetPlayerVirtualWorldEx(Temptargetid[playerid], 0);

    SetPlayerPositionEx(Temptargetid[playerid], 143.7855,1945.5334,19.3505,356.1586);
    StopRunningAnimation(Temptargetid[playerid]);

    SendClientMessageToAllEx(X11_CHOCOLATE, "SACF Press Release: %s has been released from the prison by %s %s.", GetPlayerRoleplayName(Temptargetid[playerid]), GetRankName(playerid), GetPlayerRoleplayName(playerid));
    return 1;
}
Dialog:PolisiImpoundSearch(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(isnull(inputtext)) return Dialog_Show(playerid, "PolisiImpoundSearch", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Impound", 
    "Error: Tidak dapat dikosongkan!\n\
    Please insert the player ID:", "Pilih", "Batal");
    if(!IsNumericEx(inputtext)) return Dialog_Show(playerid, "PolisiImpoundSearch", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Impound", 
    "Error: Masukkan hanya angka!\n\
    Please insert the player ID:", "Pilih", "Batal");
    
    new mstr[128], hjstr[512], modelid, impduration, impfee;
    AccountData[playerid][pTempSQLImpoundID] = strval(inputtext);
    if(!IsPlayerConnected(AccountData[playerid][pTempSQLImpoundID])) return Dialog_Show(playerid, "PolisiImpoundSearch", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Impound", 
    "Error: The player is not connected to the server!\n\
    Please insert the player ID:", "Pilih", "Batal");
    if(!IsPlayerNearPlayer(playerid, AccountData[playerid][pTempSQLImpoundID], 3.5)) return Dialog_Show(playerid, "PolisiImpoundSearch", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Impound", 
    "Error: Pemain tersebut tidak dekat dengan anda!\n\
    Please insert the player ID:", "Pilih", "Batal");

    mysql_format(g_SQL, mstr, sizeof(mstr), "SELECT * FROM `player_vehicles` WHERE `PVeh_Impounded`=1 AND `PVeh_Owner`=%d", AccountData[AccountData[playerid][pTempSQLImpoundID]][pID]);
    mysql_query(g_SQL, mstr);
    if(cache_num_rows())
    {
        format(hjstr, sizeof(hjstr), "Model\tDurasi\tTagihan\n");
        for(new x; x < cache_num_rows(); x++)
        {
            cache_get_value_name_int(x, "PVeh_ModelID", modelid);
            cache_get_value_name_int(x, "PVeh_ImpoundDuration", impduration);
            cache_get_value_name_int(x, "PVeh_ImpoundFee", impfee);

            format(hjstr, sizeof(hjstr), "%s%s\t%s\t$%s\n", hjstr, GetVehicleModelName(modelid), ReturnTimelapse(gettime(), impduration, "Sudah Waktunya"), FormatMoney(impfee));
        }
        Dialog_Show(playerid, "PolisiImpoundSelect", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Impounded List", 
        hjstr, "Pilih", "Batal");
    }
    else
    {
        Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Impounded List", "Tidak ada kendaraan impound dari pemain tersebut!", 
        "Tutup", "");
    }
    return 1;
}
Dialog:PolisiImpoundSelect(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan!");

    new mstr[128];
    mysql_format(g_SQL, mstr, sizeof(mstr), "SELECT * FROM `player_vehicles` WHERE `PVeh_Impounded`=1 AND `PVeh_Owner`=%d", AccountData[AccountData[playerid][pTempSQLImpoundID]][pID]);
    mysql_query(g_SQL, mstr);
    new modelid, impduration, impfee, impreason[128], jjj[512];
    if(cache_num_rows())
    {
        cache_get_value_name_int(listitem, "id", AccountData[playerid][pTempSQLImpoundVID]);
        cache_get_value_name_int(listitem, "PVeh_ModelID", modelid);
        cache_get_value_name_int(listitem, "PVeh_ImpoundDuration", impduration);
        cache_get_value_name_int(listitem, "PVeh_ImpoundFee", impfee);
        cache_get_value_name(listitem, "PVeh_ImpoundReason", impreason);

        format(jjj, sizeof(jjj), "Detail Impound SAMSAT:\n\
        Model: %s\n\
        Durasi: %s\n\
        Tagihan: $%s\n\
        Alasan: %s", GetVehicleModelName(modelid), ReturnTimelapse(gettime(), impduration, "Sudah Waktunya"), FormatMoney(impfee), impreason);
        Dialog_Show(playerid, "PolisiImpoundConfirm", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Impounded List", 
        jjj, "Lepas", "Batal");
    }
    return 1;
}
Dialog:PolisiImpoundConfirm(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    foreach(new vid : PvtVehicles)
    {
        if(PlayerVehicle[vid][pVehID] == AccountData[playerid][pTempSQLImpoundVID] && PlayerVehicle[vid][pVehImpounded] && PlayerVehicle[vid][pVehOwnerID] == AccountData[AccountData[playerid][pTempSQLImpoundID]][pID])
        {
            if(gettime() < PlayerVehicle[vid][pVehImpoundDuration]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Belum waktunya untuk mengeluarkan kendaraan tersebut!");
            
            PlayerVehicle[vid][pVehParked] = -1;
            PlayerVehicle[vid][pVehFamGarage] = -1;
            PlayerVehicle[vid][pVehHouseGarage] = -1;
            PlayerVehicle[vid][pVehInsuranced] = false;

            PlayerVehicle[vid][pVehImpounded] = false;
            PlayerVehicle[vid][pVehImpoundDuration] = 0;
            PlayerVehicle[vid][pVehImpoundFee] = 0;
            PlayerVehicle[vid][pVehImpoundReason][0] = EOS;
            PlayerVehicle[vid][pVehTireLocked] = false;
            
            PlayerVehicle[vid][pVehPos][0] = 991.8807;
            PlayerVehicle[vid][pVehPos][1] = 2472.4053;
            PlayerVehicle[vid][pVehPos][2] = 11.4012;
            PlayerVehicle[vid][pVehPos][3] = 180.2203;
            
            OnPlayerVehicleRespawn(vid);
        }
    }
    new impstr[250];
    mysql_format(g_SQL, impstr, sizeof(impstr), "UPDATE `player_vehicles` SET `PVeh_Impounded` = 0, `PVeh_ImpoundDuration`=0, `PVeh_ImpoundFee`=0, `PVeh_ImpoundReason`='' WHERE `id`=%d", AccountData[playerid][pTempSQLImpoundVID]);
    mysql_pquery(g_SQL, impstr);
    return 1;
}
// Dialog:DIALOG_TEST_A1:
// {
//     if(!response) return SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"You have canceled the theory test for the Driving License.");

//     if(listitem != 2) return SendClientMessage(playerid, -1, "[Teori] Anda memilih jawaban yang salah, anda dinyatakan gagal ujian teori!");

//     Dialog_Show(playerid, DIALOG_TEST_A2, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Department of Motor Vehicles", 
//     "Kompetensi mengemudi dapat diperoleh dengan cara?\n\
//     A. Pendidikan dan pelatihan mengemudi.\n\
//     "GRAY"B. Percobaan mengemudi.\n\
//     C. Belajar sendiri.\n\
//     "GRAY"D. Pilihan A dan C benar.", "Pilih", "Batal");
// }

// Dialog:DIALOG_TEST_A2:
// {
//     if(!response) return SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"You have canceled the theory test for the Driving License.");

//     if(listitem != 3) return SendClientMessage(playerid, -1, "[Teori] Anda memilih jawaban yang salah, anda dinyatakan gagal ujian teori!");

//     Dialog_Show(playerid, DIALOG_TEST_A3, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Department of Motor Vehicles", 
//     "Dalam keadaan tertentu, polisi dapat melakukan tindakan:\n\
//     A. Memberhentikan arus lalu lintas.\n\
//     "GRAY"B. Memerintahkan pemakai jalan untuk jalan terus & mempercepat arus.\n\
//     C. Memperlambat arus & mengubah arah arus.\n\
//     "GRAY"D. Semuanya benar.", "Pilih", "Batal");
// }

// Dialog:DIALOG_TEST_A3:
// {
//     if(!response) return SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"You have canceled the theory test for the Driving License.");

//     if(listitem != 3) return SendClientMessage(playerid, -1, "[Teori] Anda memilih jawaban yang salah, anda dinyatakan gagal ujian teori!");

//     Dialog_Show(playerid, DIALOG_TEST_A4, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Department of Motor Vehicles", 
//     "Golongan rambu lalu lintas terdiri dari:\n\
//     A. 2 golongan, rambu perintah & rambu larangan.\n\
//     "GRAY"B. 3 golongan, rambu peringatan, larangan & perintah.\n\
//     C. 3 golongan, rambu peringatan, larangan & petunjuk.\n\
//     "GRAY"D. 4 golongan, rambu peringatan, larangan, perintah & petunjuk.", "Pilih", "Batal");
// }

// Dialog:DIALOG_TEST_A4:
// {
//     if(!response) return SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"You have canceled the theory test for the Driving License.");

//     if(listitem != 3) return SendClientMessage(playerid, -1, "[Teori] Anda memilih jawaban yang salah, anda dinyatakan gagal ujian teori!");

//     Dialog_Show(playerid, DIALOG_TEST_A5, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Department of Motor Vehicles", 
//     "Alat pengukur kecepatan kendaraan, secara umum menunjukkan:\n\
//     A. Kecepatan rata-rata kendaraan kita.\n\
//     "GRAY"B. Kecepatan maksimal kendaraan kita.\n\
//     C. Kecepatan aktual kendaraan kita pada saat melihat alat tersebut.\n\
//     "GRAY"D. Kecepatan yang diwajibkan sesuai kelas jalan yang dilalui.", "Pilih", "Batal");
// }

// Dialog:DIALOG_TEST_A5:
// {
//     if(!response) return SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"You have canceled the theory test for the Driving License.");

//     if(listitem != 2) return SendClientMessage(playerid, -1, "[Teori] Anda memilih jawaban yang salah, anda dinyatakan gagal ujian teori!");

//     Dialog_Show(playerid, DIALOG_TEST_A6, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Department of Motor Vehicles", 
//     "Apakah fungsi dari tuas transmisi?\n\
//     A. Menambah kecepatan.\n\
//     "GRAY"B. Memperlambat kecepatan.\n\
//     C. Memindahkan gigi transmisi.\n\
//     "GRAY"D. Memberi isyarat kendaraan saat akan berbelok.", "Pilih", "Batal");
// }

// Dialog:DIALOG_TEST_A6:
// {
//     if(!response) return SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"You have canceled the theory test for the Driving License.");

//     if(listitem != 2) return SendClientMessage(playerid, -1, "[Teori] Anda memilih jawaban yang salah, anda dinyatakan gagal ujian teori!");

//     Dialog_Show(playerid, DIALOG_TEST_A7, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Department of Motor Vehicles", 
//     "Mana yang bukan fungsi klakson?\n\
//     A. Meminta kendaraan di depan untuk segera menyingkir.\n\
//     "GRAY"B. Memberi tanda isyarat bahwa kita sedang melintas.\n\
//     C. Sebagai alat untuk memarahi orang lain.\n\
//     "GRAY"D. Sebagai alat atau sinyal darurat.", "Pilih", "Batal");
// }

// Dialog:DIALOG_TEST_A7:
// {
//     if(!response) return SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"You have canceled the theory test for the Driving License.");

//     if(listitem != 2) return SendClientMessage(playerid, -1, "[Teori] Anda memilih jawaban yang salah, anda dinyatakan gagal ujian teori!");

//     Dialog_Show(playerid, DIALOG_TEST_A8, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Department of Motor Vehicles", 
//     "Manakah syarat yang harus dipenuhi untuk mendapatkan Driving License?\n\
//     A. Usia.\n\
//     "GRAY"B. Lulus tes teori dan praktek.\n\
//     C. Persyaratan kesehatan.\n\
//     "GRAY"D. Semuanya benar.", "Pilih", "Batal");
// }

// Dialog:DIALOG_TEST_A8:
// {
//     if(!response) return SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"You have canceled the theory test for the Driving License.");

//     if(listitem != 3) return SendClientMessage(playerid, -1, "[Teori] Anda memilih jawaban yang salah, anda dinyatakan gagal ujian teori!");

//     Dialog_Show(playerid, DIALOG_TEST_A9, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Department of Motor Vehicles", 
//     "Untuk mendepatkan Driving License, calon pengemudi harus?\n\
//     A. Memiliki kompetensi mengemudi.\n\
//     "GRAY"B. Memiliki kendaraan bermotor.\n\
//     C. Memiliki kompetensi permesinan.\n\
//     "GRAY"D. Mengetahui jalan di lingkungannya.", "Pilih", "Batal");
// }

// Dialog:DIALOG_TEST_A9:
// {
//     if(!response) return SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"You have canceled the theory test for the Driving License.");

//     if(listitem != 0) return SendClientMessage(playerid, -1, "[Teori] Anda memilih jawaban yang salah, anda dinyatakan gagal ujian teori!");

//     Dialog_Show(playerid, DIALOG_TEST_A10, DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Department of Motor Vehicles", 
//     "Berapa batas maksimal seseorang untuk mengikuti tes mendapatkan Driving License?\n\
//     A. 3 kali.\n\
//     "GRAY"B. 1 kali.\n\
//     C. 5 kali.\n\
//     "GRAY"D. Tidak ada batasan yang penting memenuhi syarat.", "Pilih", "Batal");
// }

// Dialog:DIALOG_TEST_A10:
// {
//     if(!response) return SendClientMessage(playerid, X11_PALEGREEN4, "[Info] "WHITE"You have canceled the theory test for the Driving License.");

//     if(listitem != 3) return SendClientMessage(playerid, -1, "[Teori] Anda memilih jawaban yang salah, anda dinyatakan gagal ujian teori!");

//     AccountData[playerid][pDMVTheoryPassed] = true;

//     SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Anda berhasil lolos tahap uji teori, keluar dan pergunakanlah salah satu kendaraan DMV.");
//     SendClientMessage(playerid, X11_LIGHTBLUE, "INFO: "WHITE"Driving License akan didapatkan setelah berhasil melewati uji praktek.");
Dialog:MDC_Main(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        SendRPMeAboveHead(playerid, "Log off dari Mobile Data Terminal");
        return 1;
    }

    switch(listitem)
    {
        case 0: //name search
        {
            PlayerPlayNearbySound(playerid, MDC_SELECT);

            static string[512];
            format(string, sizeof(string), "Kepolisian Pahlawan Roleplay\n\
            Mobile Data Terminal (MDT)\n\
            ========================================\n\
            Welcome, %s %s!\n\n\
            Please insert the correct fullname:", GetRankName(playerid), GetPlayerRoleplayName(playerid));
            Dialog_Show(playerid, "MDC_NameSearch", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- MDT Name Search", string, "Insert", "Kembali");
        }
        case 1: //plate search
        {
            PlayerPlayNearbySound(playerid, MDC_SELECT);

            static string[512];
            format(string, sizeof(string), "Kepolisian Pahlawan Roleplay\n\
            Mobile Data Terminal (MDT)\n\
            ========================================\n\
            Welcome, %s %s!\n\n\
            Mohon masukkan plate kendaraan untuk diperiksa:", GetRankName(playerid), GetPlayerRoleplayName(playerid));
            Dialog_Show(playerid, "MDC_PlateSearch", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- MDT Plate Search", string, "Insert", "Kembali");
        }
        case 2: //all points bulletin
        {
            mysql_pquery(g_SQL, "SELECT `id`, `time`, `description`, `issuer`, `suspect` FROM `mdc_warrants` WHERE `id` != 0 ORDER BY `id` ASC LIMIT 100", "MDCAllPointBulletin", "i", playerid);
        }
        case 3: //crime broadcast
        {
            Dialog_Show(playerid, "MDC_Broadcast", DIALOG_STYLE_LIST, "MDT: Crime Broadcast", "Add New Crime Broadcast\nView Crime Broadcast", 
            "Pilih", "Kembali");
        }
        case 4: //roster
        {
            new count = 0;
            static string[1024];
            format(string, sizeof(string), "No\tCallsign\tOfficer in charge\n");
            foreach(new i : Player) if(AccountData[i][pSpawned])
            {
                if(Iter_Contains(Vehicle, PlayerFactionVehicle[i][FACTION_LSPD]) && IsValidDynamic3DTextLabel(FactionVehCallsign[PlayerFactionVehicle[i][FACTION_LSPD]]) && AccountData[i][pFaction] == FACTION_LSPD && !isnull(LSPDPlayerCallsign[i]))
                {
                    count++;
                    format(string, sizeof(string), "%s%d.\t%s\t%s\n", string, count, LSPDPlayerCallsign[i], GetPlayerRoleplayName(i));
                }
            }
            if(count > 0)
            {
                Dialog_Show(playerid, "MDC_Roster", DIALOG_STYLE_TABLIST_HEADERS, "MDT: Roster", string, "Kembali", "");
            }
            else
            {
                Dialog_Show(playerid, "MDC_Roster", DIALOG_STYLE_TABLIST_HEADERS, "MDT: Roster", "No data not found...", "Kembali", "");
            }
        }
    }
    return 1;
}
Dialog:MDC_Roster(playerid, response, listitem, inputtext[])
{
    if(response == 0 || response == 1)
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_Main", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- MDT Dashboard", "Name Search\nPlate Search\nAll Points Bulletin\nCrime Broadcast\nRoster", "Pilih", "Logout");
    }
    return 1;
}
Dialog:MDC_Broadcast(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_Main", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- MDT Dashboard", "Name Search\nPlate Search\nAll Points Bulletin\nCrime Broadcast\nRoster", "Pilih", "Logout");
        return 1;
    }

    switch(listitem)
    {
        case 0: //add new crime broadcast
        {
            PlayerPlayNearbySound(playerid, MDC_SELECT);

            Dialog_Show(playerid, "MDC_AddBroadcast", DIALOG_STYLE_INPUT, "MDT: Add New Crime Broadcast",
            "Mohon masukkan deskripsi crime broadcast yang akan diterbitkan:", "Input", "Kembali");
        }
        case 1: //view crime broadcast
        {
            mysql_pquery(g_SQL, "SELECT `time`, `description`, `issuer` FROM `mdc_broadcasts` WHERE `id` != 0", "MDCViewBroadcasts", "i", playerid);
        }
    }
    return 1;
}
Dialog:MDC_AddBroadcast(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_Broadcast", DIALOG_STYLE_LIST, "MDT: Crime Broadcast", "Add New Crime Broadcast\nView Crime Broadcast", 
        "Pilih", "Kembali");
        return 1;
    }

    if(isnull(inputtext))
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_AddBroadcast", DIALOG_STYLE_INPUT, "MDT: Add New Crime Broadcast",
        "Error: Anda tidak dapat mengosongkan kolom deskripsi crime broadcast!\n\
        Mohon masukkan deskripsi crime broadcast yang akan diterbitkan:", "Input", "Kembali");
        return 1;
    }

    if(strfind(inputtext, "%", true) != -1 || strfind(inputtext, "#", true) != -1) 
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_AddBroadcast", DIALOG_STYLE_INPUT, "MDT: Add New Crime Broadcast",
        "Error: You cannot input percent symbol!\n\
        Mohon masukkan deskripsi crime broadcast yang akan diterbitkan:", "Input", "Kembali");
        return 1;
    }

    static string[268];
    mysql_format(g_SQL, string, sizeof(string), "INSERT INTO `mdc_broadcasts` (`time`, `description`, `issuer`) VALUES ('%e', '%e', '%e')", GetSimpleDate(), inputtext, AccountData[playerid][pName]);
    mysql_pquery(g_SQL, string);

    SendTeamMessage(FACTION_LSPD, X11_SEAGREEN1, "[ CRIME BROADCAST: "YELLOW"%s %s "SEAGREEN1"has announced a new crime broadcast "SEAGREEN1"]", GetRankName(playerid), GetPlayerRoleplayName(playerid), MDC_Data[playerid][Name]);
    SendTeamMessage(FACTION_LSPD, X11_SEAGREEN1, "[ CRIME BROADCAST: "RED"%s "SEAGREEN1"]", inputtext);
    return 1;
}
Dialog:MDC_NameSearch(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_Main", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- MDT Dashboard", "Name Search\nPlate Search\nAll Points Bulletin\nCrime Broadcast\nRoster", "Pilih", "Logout");
        return 1;
    }

    if(isnull(inputtext))
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);

        static string[512];
        format(string, sizeof(string), "Kepolisian Pahlawan Roleplay\n\
        Mobile Data Terminal (MDT)\n\
        ========================================\n\
        Hello, %s %s!\n\n\
        Error: Anda tidak dapat mengosongkan kolom pencarian tersebut!\n\
        Please insert the correct fullname:", GetRankName(playerid), GetPlayerRoleplayName(playerid));
        Dialog_Show(playerid, "MDC_NameSearch", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- MDT Name Search", string, "Insert", "Kembali");
        return 1;
    }

    static string[1224];
    mysql_format(g_SQL, string, sizeof(string), "SELECT `phoneNumber` FROM `player_phones` WHERE `phoneOwnerName` = '%e'", GetPlayerRoleplayNameOffline(inputtext));
    mysql_pquery(g_SQL, string, "MDCPhoneNumberResult", "i", playerid);

    mysql_format(g_SQL, string, sizeof(string), "SELECT `pID`, `Char_Name`, `Char_Birthday`, `Char_Faction`, `Char_FactionRank`, `Char_GVL1Lic`, `Char_GVL1LicTime`, `Char_GVL2Lic`, `Char_GVL2LicTime`, \
    `Char_MBLic`, `Char_MBLicTime`, `Char_BLic`, `Char_BLicTime`, `Char_Air1Lic`, `Char_Air1LicTime`, `Char_Air2Lic`, `Char_Air2LicTime`, `Char_FirearmLic`, `Char_FirearmLicTime`, `Char_HuntingLic`, `Char_HuntingLicTime` FROM `player_characters` WHERE `Char_Name` = '%e'", inputtext);
    mysql_pquery(g_SQL, string, "MDCNameSearchResult", "is", playerid, inputtext);
    return 1;
}
Dialog:MDC_PlateSearch(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_Main", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- MDT Dashboard", "Name Search\nPlate Search\nAll Points Bulletin\nCrime Broadcast\nRoster", "Pilih", "Logout");
        return 1;
    }

    if(isnull(inputtext))
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);

        static string[512];
        format(string, sizeof(string), "Kepolisian Pahlawan Roleplay\n\
        Mobile Data Terminal (MDT)\n\
        ========================================\n\
        Hello, %s %s!\n\n\
        Error: Anda tidak dapat mengosongkan kolom pencarian tersebut!\n\
        Mohon masukkan plate kendaraan untuk diperiksa:", GetRankName(playerid), GetPlayerRoleplayName(playerid));
        Dialog_Show(playerid, "MDC_PlateSearch", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- MDT Plate Search", string, "Insert", "Kembali");
        return 1;
    }

    static string[155];
    mysql_format(g_SQL, string, sizeof(string), "SELECT `PVeh_Owner` FROM `player_vehicles` WHERE `PVeh_Plate` = '%e'", inputtext);
    mysql_pquery(g_SQL, string, "MDCPlateSearchResult", "i", playerid);
    return 1;
}
Dialog:MDC_Found(playerid, response, listitem, inputtext[])
{
    if(response == 0 || response == 1)
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);

        static string[64];
        format(string, sizeof(string), "MDT: %s - Dashboard", MDC_Data[playerid][Name]);
        Dialog_Show(playerid, "MDC_NameDashboard", DIALOG_STYLE_LIST, string, "Personal Information\nRegistered Vehicles\nPersonal Charges\nPersonal Warrants\nArrest Record", "Pilih", "Kembali");
    }
    return 1;
}
Dialog:MDC_APBDetail(playerid, response, listitem, inputtext[])
{
    if(response == 0 || response == 1)
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_Main", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- MDT Dashboard", "Name Search\nPlate Search\nAll Points Bulletin\nCrime Broadcast\nRoster", "Pilih", "Logout");
    }
    return 1;
}
Dialog:MDC_NameDashboard(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_Main", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- MDT Dashboard", "Name Search\nPlate Search\nAll Points Bulletin\nCrime Broadcast\nRoster", "Pilih", "Logout");
        return 1;
    }

    static string[168];
    switch(listitem)
    {
        case 0: //personal information
        {
            static const JOBName[14][] = {
                "Pengangguran",
                "Petani",
                "Penambang",
                "Tukang Ayam",
                "Tukang Minyak",
                "Supir Angkot",
                "Nelayan",
                "Supir Kargo",
                "Porter",
                "Supir Mixer",
                "Tukang Kayu",
                "Pelaut",
                "Peternak",
                "Penjahit"
            };

            static const FacName[13][] = 
            {
                "Warga Pahlawan Roleplay",
                "Kepolisian",
                "Paramedis",
                "Putri Deli Beach Club",
                "Pemerintah",
                "Bennys Automotive",
                "Uber",
                "Pinky Tiger Club",
                "Pewarta",
                "Automax Workshop",
                "Handover Motorworks",
                "Sri Mersing Resto",
                "Texas Chicken"
            };

            static const PutrideliRank[11][] = 
            {
                "N/A",
                "Magang",
                "Junior",
                "Pelayan",
                "Barista",
                "Senior",
                "Marketing",
                "Supervisor",
                "Manager",
                "Chief Officer",
                "Chief Executive"
            };

            static const PemerintahRank[8][] = 
            {
                "N/A",
                "Honorer",
                "Staff Junior",
                "Staff Senior",
                "Kepala Dinas",
                "Sekretaris",
                "W. Gubernur",
                "Gubernur"
            };

            static const LSFDRank[9][] = 
            {
                "N/A",
                "PKL", //1
                "Perawat", //2
                "Dokter", //3
                "Dokter Spesialis", //4
                "Profesor", //5
                "WAKADIR", //6
                "SEKBEN", //7
                "Direktur" //8
            };

            static const BennysRank[7][] = 
            {
                "N/A",

                "PKL", // 1
                "Amatir", //2
                "Ahli", //3
                "Wakil Manager", //4
                "Manager",
                "Boss Bennys"
            };

            static const UberRank[6][] = 
            {
                "N/A",

                "Driver Baru",
                "Junior",
                "Senior",
                "Ast. Boss Uber",
                "Boss Uber"
            };


            static const DBRank[11][] = 
            {
                "N/A",
                "Magang",
                "Junior",
                "Pelayan",
                "Barista",
                "Senior",
                "Marketing",
                "Supervisor",
                "Manager",
                "Chief Officer",
                "Chief Executive"
            };

            static const FoxRank[7][] = 
            {
                "N/A",
                "Jurnalis",
                "Reporter",
                "Editor",
                "Senior",
                "Chief Officer",
                "Chief Executive"
            };

            static const AutomaxRank[7][] = 
            {
                "N/A",

                "PKL", // 1
                "Amatir", //2
                "Ahli", //3
                "Wakil Manager", //4
                "Manager",
                "Boss Automax"
            };
            static const HandoverRank[7][] = 
            {
                "N/A",

                "PKL", // 1
                "Amatir", //2
                "Ahli", //3
                "Wakil Manager", //4
                "Manager",
                "Boss Handover"
            };

            static const PARVRank[11][] = 
            {
                "N/A",
                "Magang",
                "Junior",
                "Pelayan",
                "Barista",
                "Senior",
                "Marketing",
                "Supervisor",
                "Manager",
                "Chief Officer",
	            "Chief Executive"
            };

            static const TexasRank[11][] = 
            {
                "N/A",
                "Magang",
                "Satpam",
                "Junior",
                "Senior",
                "Staff",
                "Marketing",
                "Supervisor",
                "Manager",
                "Chief Officer",
                "Chief Executive"
            };

            static rnnrt[64];

            switch(MDC_Data[playerid][Faction])
            {
                case FACTION_NONE: //None
                {
                    format(rnnrt, sizeof(rnnrt), "N/A");
                }
                case FACTION_LSPD: //polda 
                {
                    format(rnnrt, sizeof(rnnrt), CopRank[MDC_Data[playerid][FactionRank]]);
                }
                case FACTION_LSFD: //IDA 
                {
                    format(rnnrt, sizeof(rnnrt), LSFDRank[MDC_Data[playerid][FactionRank]]);
                }
                case FACTION_PUTRIDELI: //Putri Deli 
                {
                    format(rnnrt, sizeof(rnnrt), PutrideliRank[MDC_Data[playerid][FactionRank]]);
                }
                case FACTION_SAGOV: //pemerintah
                {
                    format(rnnrt, sizeof(rnnrt), PemerintahRank[MDC_Data[playerid][FactionRank]]);
                }
                case FACTION_BENNYS: //bengkel
                {
                    format(rnnrt, sizeof(rnnrt), BennysRank[MDC_Data[playerid][FactionRank]]);
                }
                case FACTION_UBER: //uber
                {
                    format(rnnrt, sizeof(rnnrt), UberRank[MDC_Data[playerid][FactionRank]]);
                }
                case FACTION_DINARBUCKS: //dinarbucks
                {
                    format(rnnrt, sizeof(rnnrt), DBRank[MDC_Data[playerid][FactionRank]]);
                }
                case FACTION_FOX11: //dinarbucks
                {
                    format(rnnrt, sizeof(rnnrt), FoxRank[MDC_Data[playerid][FactionRank]]);
                }
                case FACTION_AUTOMAX: //bengkel
                {
                    format(rnnrt, sizeof(rnnrt), AutomaxRank[MDC_Data[playerid][FactionRank]]);
                }
                case FACTION_HANDOVER: //bengkel
                {
                    format(rnnrt, sizeof(rnnrt), HandoverRank[MDC_Data[playerid][FactionRank]]);
                }
                case FACTION_SRIMERSING: //bengkel
                {
                    format(rnnrt, sizeof(rnnrt), PARVRank[MDC_Data[playerid][FactionRank]]);
                }
                case FACTION_TEXAS:
                {
                    format(rnnrt, sizeof(rnnrt), TexasRank[MDC_Data[playerid][FactionRank]]);
                }
            }

            static mdcnstr2[1777];
            format(mdcnstr2, sizeof(mdcnstr2), ""WHITE"=================================================================\n\n");

            format(mdcnstr2, sizeof(mdcnstr2), "%sName Search Results for: %s\n\n", mdcnstr2, MDC_Data[playerid][Name]);

            format(mdcnstr2, sizeof(mdcnstr2), "%sFull Name: [ %s ]\n", mdcnstr2, MDC_Data[playerid][Name]);
            format(mdcnstr2, sizeof(mdcnstr2), "%sDOB: [ %s ]\n", mdcnstr2, MDC_Data[playerid][Birthday]);
            format(mdcnstr2, sizeof(mdcnstr2), "%sEmployer: [ %s ]\n", mdcnstr2, JOBName[MDC_Data[playerid][Job]]);
            format(mdcnstr2, sizeof(mdcnstr2), "%sFaction: [ %s as %s ]\n\n", mdcnstr2, FacName[MDC_Data[playerid][Faction]], sprintf("%s", rnnrt));

            format(mdcnstr2, sizeof(mdcnstr2), "%sPhone Number(s):\n\
            %s\n\n", mdcnstr2, MDC_Data[playerid][Phone]);

            format(mdcnstr2, sizeof(mdcnstr2), "%sVehicular Operation Licenses:\n\
            General Vehicle License [GVL-1] [%s"WHITE"]\n\
            Large Vehicle License [GVL-2] [%s"WHITE"]\n\
            Motorbike License [MB] [%s"WHITE"]\n\
            Boat License [B] [%s"WHITE"]\n\
            Helicopter License [A1] [%s"WHITE"]\n\
            Plane License [A2] [%s"WHITE"]\n\n", 
            mdcnstr2,
            (gettime() < MDC_Data[playerid][GVL1LicTime]) ? (sprintf(""DARKGREEN"Valid, %s", ReturnDate(MDC_Data[playerid][GVL1LicTime]))) : (""RED"Invalid"),
            (gettime() < MDC_Data[playerid][GVL2LicTime]) ? (sprintf(""DARKGREEN"Valid, %s", ReturnDate(MDC_Data[playerid][GVL2LicTime]))) : (""RED"Invalid"),
            (gettime() < MDC_Data[playerid][MBLicTime]) ? (sprintf(""DARKGREEN"Valid, %s", ReturnDate(MDC_Data[playerid][MBLicTime]))) : (""RED"Invalid"),
            (gettime() < MDC_Data[playerid][BLicTime]) ? (sprintf(""DARKGREEN"Valid, %s", ReturnDate(MDC_Data[playerid][BLicTime]))) : (""RED"Invalid"),
            (gettime() < MDC_Data[playerid][Air1LicTime]) ? (sprintf(""DARKGREEN"Valid, %s", ReturnDate(MDC_Data[playerid][Air1LicTime]))) : (""RED"Invalid"),
            (gettime() < MDC_Data[playerid][Air2LicTime]) ? (sprintf(""DARKGREEN"Valid, %s", ReturnDate(MDC_Data[playerid][Air2LicTime]))) : (""RED"Invalid"));

            format(mdcnstr2, sizeof(mdcnstr2), "%sOther Licenses:\n\
            CCW [%s"WHITE"] HL [%s"WHITE"]\n\n", 
            mdcnstr2,
            (MDC_Data[playerid][FirearmLicTime] != 0) ? (sprintf(""DARKGREEN"Valid, %s", ReturnDate(MDC_Data[playerid][FirearmLicTime]))) : (""RED"Invalid"),
            (MDC_Data[playerid][HuntingLicTime] != 0) ? (sprintf(""DARKGREEN"Valid, %s", ReturnDate(MDC_Data[playerid][HuntingLicTime]))) : (""RED"Invalid"));

            format(mdcnstr2, sizeof(mdcnstr2), "%s"WHITE"=================================================================\n", mdcnstr2);

            PlayerPlayNearbySound(playerid, MDC_SELECT);

            static hdrstr[50];
            format(hdrstr, sizeof(hdrstr), "MDT: %s - Personal Information", MDC_Data[playerid][Name]);
            Dialog_Show(playerid, "MDC_Found", DIALOG_STYLE_MSGBOX, hdrstr, mdcnstr2, "Kembali", "");
        }
        case 1: //registered vehicles
        {
            mysql_format(g_SQL, string, sizeof(string), "SELECT `PVeh_ModelID`, `PVeh_Plate` FROM `player_vehicles` WHERE `PVeh_Owner` = %d", MDC_Data[playerid][pID]);
            mysql_pquery(g_SQL, string, "MDCRegisteredVehicles", "i", playerid);
        }
        case 2: //personal charges
        {
            PlayerPlayNearbySound(playerid, MDC_SELECT);

            Dialog_Show(playerid, "MDC_ChargeMenu", DIALOG_STYLE_LIST, sprintf("MDT: %s - Personal Charges", MDC_Data[playerid][Name]), "Add New Charges\nCheck Active Charges\nCheck Charges History", "Pilih", "Kembali");
        }
        case 3: //personal warrants
        {
            PlayerPlayNearbySound(playerid, MDC_SELECT);

            Dialog_Show(playerid, "MDC_WarrantsMenu", DIALOG_STYLE_LIST, sprintf("MDT: %s - Personal Warrants", MDC_Data[playerid][Name]), "Add New Warrants\nCheck Active Warrants", "Pilih", "Kembali");
        }
        case 4: //arrest record
        {
            mysql_format(g_SQL, string, sizeof(string), "SELECT `id`, `time`, `detentions`, `officer` FROM `mdc_arrestrecords` WHERE `ownerid` = %d", MDC_Data[playerid][pID]);
            mysql_pquery(g_SQL, string, "MDCArrestRecord", "i", playerid); 
        }
    }
    return 1;
}
Dialog:MDC_ChargeMenu(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        static string[64];
        format(string, sizeof(string), "MDT: %s - Dashboard", MDC_Data[playerid][Name]);
        Dialog_Show(playerid, "MDC_NameDashboard", DIALOG_STYLE_LIST, string, "Personal Information\nRegistered Vehicles\nPersonal Charges\nPersonal Warrants\nArrest Record", "Pilih", "Kembali");
        return 1;
    }

    static string[168];
    switch(listitem)
    {
        case 0: //add new charges
        {
            PlayerPlayNearbySound(playerid, MDC_SELECT);

            Dialog_Show(playerid, "MDC_AddCharges", DIALOG_STYLE_INPUT, sprintf("MDT: %s - Add New Charges", MDC_Data[playerid][Name]),
            "Mohon masukkan deskripsi charges yang akan diterbitkan:", "Input", "Kembali");
        }
        case 1: //check active charges
        {
            mysql_format(g_SQL, string, sizeof(string), "SELECT `id`, `time`, `description`, `issuer` FROM `mdc_charges` WHERE `ownerid` = %d and `status` = 1", MDC_Data[playerid][pID]);
            mysql_pquery(g_SQL, string, "MDCCheckActiveCharges", "i", playerid);
        }
        case 2: //check charges history
        {
            MDC_ChargesHistoryPagination[playerid] = 0;
            mysql_format(g_SQL, string, sizeof(string), "SELECT `time`, `description`, `issuer` FROM `mdc_charges` WHERE `ownerid` = %d and `status` = 0", MDC_Data[playerid][pID]);
            mysql_pquery(g_SQL, string, "MDCCheckChargesHistory", "i", playerid);
        }
    }
    return 1;
}
Dialog:MDC_WarrantsMenu(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        static string[64];
        format(string, sizeof(string), "MDT: %s - Dashboard", MDC_Data[playerid][Name]);
        Dialog_Show(playerid, "MDC_NameDashboard", DIALOG_STYLE_LIST, string, "Personal Information\nRegistered Vehicles\nPersonal Charges\nPersonal Warrants\nArrest Record", "Pilih", "Kembali");
        return 1;
    }

    static string[168];
    switch(listitem)
    {
        case 0: //add new warrants
        {
            if(AccountData[playerid][pFactionRank] < 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimum rank KOMPOL dibutuhkan untuk akses menu ini!");

            PlayerPlayNearbySound(playerid, MDC_SELECT);

            Dialog_Show(playerid, "MDC_AddWarrant", DIALOG_STYLE_INPUT, sprintf("MDT: %s - Add New Warrants", MDC_Data[playerid][Name]),
            "Mohon masukkan deskripsi warrants yang akan diterbitkan:", "Input", "Kembali");
        }
        case 1: //check active warrants
        {
            mysql_format(g_SQL, string, sizeof(string), "SELECT `id`, `time`, `description`, `issuer` FROM `mdc_warrants` WHERE `ownerid` = %d", MDC_Data[playerid][pID]);
            mysql_pquery(g_SQL, string, "MDCCheckActiveWarrants", "i", playerid);
        }
    }
    return 1;
}
Dialog:MDC_AddWarrant(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_WarrantsMenu", DIALOG_STYLE_LIST, sprintf("MDT: %s - Personal Warrants", MDC_Data[playerid][Name]), "Add New Warrants\nCheck Active Warrants", "Pilih", "Kembali");
        return 1;
    }

    if(isnull(inputtext))
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_AddWarrant", DIALOG_STYLE_INPUT, sprintf("MDT: %s - Add New Warrants", MDC_Data[playerid][Name]),
        "Error: Anda tidak dapat mengosongkan kolom deskripsi warrants!\n\
        Mohon masukkan deskripsi warrants yang akan diterbitkan:", "Input", "Kembali");
        return 1;
    }

    if(strfind(inputtext, "%", true) != -1 || strfind(inputtext, "#", true) != -1) 
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_AddWarrant", DIALOG_STYLE_INPUT, sprintf("MDT: %s - Add New Warrants", MDC_Data[playerid][Name]),
        "Error: You cannot insert percent symbol!\n\
        Mohon masukkan deskripsi warrants yang akan diterbitkan:", "Input", "Kembali");
        return 1;
    }

    static string[268];
    mysql_format(g_SQL, string, sizeof(string), "INSERT INTO `mdc_warrants` (`ownerid`, `time`, `description`, `issuer`, `suspect`) VALUES (%d, '%e', '%e', '%e', '%e')", MDC_Data[playerid][pID], GetSimpleDate(), inputtext, AccountData[playerid][pName], MDC_Data[playerid][Name]);
    mysql_pquery(g_SQL, string);

    SendTeamMessage(FACTION_LSPD, X11_BLUE, "[ WARRANT: "YELLOW"%s %s "BLUE"has issued a new warrant for "RED"%s "BLUE"]", GetRankName(playerid), GetPlayerRoleplayName(playerid), MDC_Data[playerid][Name]);
    SendTeamMessage(FACTION_LSPD, X11_BLUE, "[ WARRANT: "GREEN"%s "BLUE"]", inputtext);
    return 1;
}
Dialog:MDC_ActWarrants(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_WarrantsMenu", DIALOG_STYLE_LIST, sprintf("MDT: %s - Personal Warrants", MDC_Data[playerid][Name]), "Add New Warrants\nCheck Active Warrants", "Pilih", "Kembali");
        return 1;
    }

    if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih active warrants!");

    AccountData[playerid][pTempValue] = listitem;

    static string[555];
    format(string, sizeof(string), ""YELLOW"Active warrant detail:\n\
    "AQUAMARINE"%s\n\
    "WHITE"Issuer: {0096FF}%s "WHITE"| Issued on: "ORANGE"%s\n\n\
    "WHITE"Apakah anda yakin ingin menghapus active warrant ini?", MDC_ListedData[playerid][listitem][warrantDesc], MDC_ListedData[playerid][listitem][warrantIssuer], MDC_ListedData[playerid][listitem][warrantTime]);
    Dialog_Show(playerid, "MDC_ActWarrantsDelete", DIALOG_STYLE_MSGBOX, sprintf("MDT: %s - Active Warrant Detail", MDC_Data[playerid][Name]), string, "Confirm", "Kembali");
    return 1;
}
Dialog:MDC_ActWarrantsDelete(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        AccountData[playerid][pTempValue] = -1;
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_WarrantsMenu", DIALOG_STYLE_LIST, sprintf("MDT: %s - Personal Warrants", MDC_Data[playerid][Name]), "Add New Warrants\nCheck Active Warrants", "Pilih", "Kembali");
        return 1;
    }

    if(AccountData[playerid][pFactionRank] < 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimum rank KOMPOL dibutuhkan untuk akses menu ini!");

    SendTeamMessage(FACTION_LSPD, X11_YELLOW, "[ WARRANT: {0096FF}%s %s "YELLOW"has removed a warrant from "RED"%s "YELLOW"]", GetRankName(playerid), GetPlayerRoleplayName(playerid), MDC_Data[playerid][Name]);
    SendTeamMessage(FACTION_LSPD, X11_YELLOW, "[ WARRANT: "GREEN"%s "YELLOW"]", MDC_ListedData[playerid][AccountData[playerid][pTempValue]][warrantDesc]);

    static string[144];
    mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `mdc_warrants` WHERE `id` = %d", MDC_ListedData[playerid][AccountData[playerid][pTempValue]][warrantID]);
    mysql_pquery(g_SQL, string);
    return 1;
}
Dialog:MDC_AddCharges(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_ChargeMenu", DIALOG_STYLE_LIST, sprintf("MDT: %s - Personal Charges", MDC_Data[playerid][Name]), "Add New Charges\nCheck Active Charges\nCheck Charges History", "Pilih", "Kembali");
        return 1;
    }

    if(isnull(inputtext))
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_AddCharges", DIALOG_STYLE_INPUT, sprintf("MDT: %s - Add New Charges", MDC_Data[playerid][Name]),
        "Error: Anda tidak dapat mengosongkan kolom deskripsi charge!\n\
        Mohon masukkan deskripsi charges yang akan diterbitkan:", "Input", "Kembali");
        return 1;
    }

    if(strfind(inputtext, "%", true) != -1 || strfind(inputtext, "#", true) != -1) 
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_AddCharges", DIALOG_STYLE_INPUT, sprintf("MDT: %s - Add New Charges", MDC_Data[playerid][Name]),
        "Error: You cannot insert percent symbol!\n\
        Mohon masukkan deskripsi charges yang akan diterbitkan:", "Input", "Kembali");
        return 1;
    }

    static string[512];
    mysql_format(g_SQL, string, sizeof(string), "INSERT INTO `mdc_charges` (`ownerid`, `time`, `description`, `issuer`, `status`, `arrest_report_id`) VALUES (%d, '%e', '%e', '%e', 1, 0)", MDC_Data[playerid][pID], GetSimpleDate(), inputtext, AccountData[playerid][pName]);
    mysql_pquery(g_SQL, string);

    SendTeamMessage(FACTION_LSPD, X11_BLUE, "[ CHARGE: "YELLOW"%s %s "BLUE"has issued a new charge for "RED"%s "BLUE"]", GetRankName(playerid), GetPlayerRoleplayName(playerid), MDC_Data[playerid][Name]);
    SendTeamMessage(FACTION_LSPD, X11_BLUE, "[ CHARGE: "GREEN"%s "BLUE"]", inputtext);
    return 1;
}
Dialog:MDC_AddChargeDelete(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        AccountData[playerid][pTempValue] = -1;
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_ChargeMenu", DIALOG_STYLE_LIST, sprintf("MDT: %s - Personal Charges", MDC_Data[playerid][Name]), "Add New Charges\nCheck Active Charges\nCheck Charges History", "Pilih", "Kembali");
        return 1;
    }

    SendTeamMessage(FACTION_LSPD, X11_YELLOW, "[ CHARGE: {0096FF}%s %s "YELLOW"has removed a charge from "RED"%s "YELLOW"]", GetRankName(playerid), GetPlayerRoleplayName(playerid), MDC_Data[playerid][Name]);
    SendTeamMessage(FACTION_LSPD, X11_YELLOW, "[ CHARGE: "GREEN"%s "YELLOW"]", MDC_ListedData[playerid][AccountData[playerid][pTempValue]][chargeDesc]);

    static string[144];
    mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `mdc_charges` WHERE `id` = %d", MDC_ListedData[playerid][AccountData[playerid][pTempValue]][chargeID]);
    mysql_pquery(g_SQL, string);
    return 1;
}

Dialog:LSPDSetRank(playerid, response, listitem, inputtext[])
{
    if(!response) 
        return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    if(listitem == -1) return 1;
    
    if(!strcmp(inputtext, ">> Selanjutnya", true)) 
    {
        index_pagination[playerid]++;

        new
            rows = TempRows[playerid];

        new 
            total_pages = (rows + MAX_MEMBER_ROWS - 1) / MAX_MEMBER_ROWS;

        new 
            max_page = total_pages - 1; 

        if(index_pagination[playerid] >= max_page) {
            index_pagination[playerid] = max_page;
        }
        Show_LSPDRankManage(playerid);
    }
    else if(!strcmp(inputtext, "<< Sebelumnya", true)) 
    {
        index_pagination[playerid]--;
        if(index_pagination[playerid] <= 0) {
            index_pagination[playerid] = 0;
        }
        Show_LSPDRankManage(playerid);
    }
    else 
    {
        if(AccountData[playerid][pFaction] != FACTION_LSPD) 
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Polisi Pahlawan Roleplay!");
        if(AccountData[playerid][pFactionRank] < 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimum rank KOMPOL untuk akses menu faction!");

        mysql_query(g_SQL, sprintf("SELECT * FROM `player_characters` WHERE `pID` = '%d'", ListedMember[playerid][listitem]));
        new rows = cache_num_rows();
        if(rows)
        {
            cache_get_value_name_int(0, "pID", AccountData[playerid][pTempSQLFactMemberID]);
            cache_get_value_name_int(0, "Char_FactionRank", AccountData[playerid][pTempSQLFactRank]);
            if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFactMemberID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menetapkan rank anda sendiri!");
            if(AccountData[playerid][pTempSQLFactRank] >= AccountData[playerid][pFactionRank]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menetapkan rank rekan yang sejajar/lebih tinggi dari anda!");
            Dialog_Show(playerid, "PolisiSetRankConfirm", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- Manage Rank", 
            "Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. BHARADA\n\
            2. BHARATU\n\
            3. BRIPDA\n\
            4. BRIPTU\n\
            5. BRIGPOL\n\
            6. BRIPKA\n\
            7. AIPDA\n\
            8. AIPTU\n\
            9. IPDA\n\
            10. IPTU\n\
            11. AKP\n\
            12. KOMPOL\n\
            13. AKBP\n\
            14. KOMBESPOL\n\
            15. BRIGJENPOL\n\
            16. IRJENPOL", "Set", "Batal");
        }
    }
    return 1;
}

forward OnArrestCheckCharges(playerid, targetid, const txsrval[]);
public OnArrestCheckCharges(playerid, targetid, const txsrval[])
{
    if(cache_num_rows() > 0)
    {
        static string[268];
        AccountData[targetid][pArrestTime] = strval(txsrval) * 60;
        AccountData[targetid][pArrested] = true;
        
        AccountData[targetid][pCuffed] = false;
        PlayerVoiceData[targetid][pHasRadio] = false;
        Inventory_Remove(targetid, "Smartphone", -1);
        ResetPlayerWeaponsEx(targetid);
        //SendTeamMessage(FACTION_LSPD, 0x9198dfFF, "HQ: "AQUAMARINE"%s have been arrested by %s.", AccountData[targetid][pName], AccountData[playerid][pName]);
        SendClientMessageToAllEx(0x8D8DFFFF, "PENGADILAN: %s telah dipenjarakan oleh %s %s selama %d bulan.", GetPlayerRoleplayName(targetid), GetRankName(playerid), GetPlayerRoleplayName(playerid), AccountData[targetid][pArrestTime]/60);
        SendPlayerToFederal(targetid);

        mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `mdc_warrants` WHERE `ownerid` = %d", AccountData[targetid][pID]);
        mysql_pquery(g_SQL, string);

        mysql_format(g_SQL, string, sizeof(string), "INSERT INTO `mdc_arrestrecords` (`ownerid`, `time`, `detentions`, `officer`) VALUES (%d, '%e', 'Penjara %d bulan', '%e')", AccountData[targetid][pID], GetSimpleDate(), AccountData[targetid][pArrestTime]/60, AccountData[playerid][pName]);
        mysql_pquery(g_SQL, string, "OnArrestRecordInserted", "i", targetid);

        NearestSingle[playerid] = INVALID_PLAYER_ID;
    }
    else
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Orang tersebut tidak memiliki active charges!");
    }
    return 1;
}

forward OnArrestRecordInserted(playerid);
public OnArrestRecordInserted(playerid)
{
    new id = cache_insert_id();

    static string[268];
    mysql_format(g_SQL, string, sizeof(string), "UPDATE `mdc_charges` SET `status` = 0, `arrest_report_id` = %d WHERE `ownerid` = %d AND `status` != 0", id, AccountData[playerid][pID]);
    mysql_pquery(g_SQL, string);
    return 1;
}

forward MDCArrestRecord(playerid);
public MDCArrestRecord(playerid)
{
    new rows = cache_num_rows();
    if(rows)
    {
        PlayerPlayNearbySound(playerid, MDC_SELECT);
        new curr_page = index_pagination[playerid];
        new curr_index = curr_page * MAX_MDC_ROWS;
        new real_i = 0;

        for (new x = 0; x < MAX_MDC_ROWS; x++) {
            MDC_ListedData[playerid][x][arrrecordID] = 0;
        }

        for (new x = curr_index; x < rows && real_i < MAX_MDC_ROWS; x++)
        {
            cache_get_value_index_int(x, 0, MDC_ListedData[playerid][real_i][arrrecordID]);
            cache_get_value_index(x, 1, MDC_ListedData[playerid][real_i][arrrecordTime]);
            cache_get_value_index(x, 2, MDC_ListedData[playerid][real_i][arrrecordDets]);
            cache_get_value_index(x, 3, MDC_ListedData[playerid][real_i][arrrecordOfficer]);
            real_i++;
        }

        new string[1012];
        strcat(string, "Time\tAssigned detentions\tOfficer\n");

        for (new x = 0; x < real_i; x++)
        {
            strcat(string, sprintf("%s\t%s\t{0096FF}%s\n", MDC_ListedData[playerid][x][arrrecordTime], MDC_ListedData[playerid][x][arrrecordDets], MDC_ListedData[playerid][x][arrrecordOfficer]));
        }

        new total_pages = (rows + MAX_MDC_ROWS - 1) / MAX_MDC_ROWS;
        new max_page = total_pages - 1;

        if (curr_page > 0) {
            strcat(string, ""RED"<< Sebelumnya");
            strcat(string, "\n");
        }
        if (curr_page < max_page) {
            strcat(string, ""GREEN">> Selanjutnya");
            strcat(string, "\n");
        }
        Dialog_Show(playerid, "LSPDARRRECORD", DIALOG_STYLE_TABLIST_HEADERS, sprintf("MDT: %s - Arrest Records", MDC_Data[playerid][Name]), string, "Pilih", "Kembali");
    }
    else
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_Found", DIALOG_STYLE_MSGBOX, sprintf("MDT: %s - Arrest Records", MDC_Data[playerid][Name]), "No data found...", "Kembali", "");
    }
    return 1;
}

forward MDCViewBroadcasts(playerid);
public MDCViewBroadcasts(playerid)
{
    new rows = cache_num_rows();
    if(rows)
    {
        PlayerPlayNearbySound(playerid, MDC_SELECT);

        new curr_page = index_pagination[playerid];
        new curr_index = curr_page * MAX_MDC_ROWS;
        new real_i = 0;

        for (new x = 0; x < MAX_MDC_ROWS; x++) {
            MDC_ListedData[playerid][x][broadcastTime] = 0;
        }
        for (new x = curr_index; x < rows && real_i < MAX_MDC_ROWS; x++)
        {
            cache_get_value_index(x, 0, MDC_ListedData[playerid][real_i][broadcastTime]);
            cache_get_value_index(x, 1, MDC_ListedData[playerid][real_i][broadcastDesc]);
            cache_get_value_index(x, 2, MDC_ListedData[playerid][real_i][broadcastIssuer]);
            real_i++;
        }

        new string[1012];
        strcat(string, "Time\tBroadcast description\tAnnounce by\n");
        for (new x = 0; x < real_i; x++)
        {
            strcat(string, sprintf("%s\t%s\t{0096FF}%s\n", MDC_ListedData[playerid][x][broadcastTime], MDC_ListedData[playerid][x][broadcastDesc], MDC_ListedData[playerid][x][broadcastIssuer]));
        }

        new total_pages = (rows + MAX_MDC_ROWS - 1) / MAX_MDC_ROWS;
        new max_page = total_pages - 1;

        if (curr_page > 0) {
            strcat(string, ""RED"<< Sebelumnya");
            strcat(string, "\n");
        }
        if (curr_page < max_page) {
            strcat(string, ""GREEN">> Selanjutnya");
            strcat(string, "\n");
        }

        Dialog_Show(playerid, "LSPDVIEWBRCAST", DIALOG_STYLE_TABLIST_HEADERS, "MDT: Crime Broadcasts", string, "Pilih", "Kembali");
    }
    else
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_APBDetail", DIALOG_STYLE_MSGBOX, "MDT: Crime Broadcasts", "No data found...", "Kembali", "");
    }
    return 1;
}

forward MDCPhoneNumberResult(playerid);
public MDCPhoneNumberResult(playerid)
{
    if(cache_num_rows() < 1)
    {
        MDC_Data[playerid][Phone][0] = EOS;
        return 1;
    }
    else
    {
        cache_get_value_index(0, 0, MDC_Data[playerid][Phone]);
    }
    return 1;
}

forward MDCRegisteredVehicles(playerid);
public MDCRegisteredVehicles(playerid)
{
    new rows = cache_num_rows();
    if(rows > 0)
    {
        PlayerPlayNearbySound(playerid, MDC_SELECT);
        new Plate[64], modelid;
        static string[255];
        format(string, sizeof(string), "Registered vehicle(s) for %s:\n\n", MDC_Data[playerid][Name]);
        for(new x; x < rows; x++)
        {
            cache_get_value_index_int(x, 0, modelid);
            cache_get_value_index(x, 1, Plate);

            format(string, sizeof(string), "%s%d. %s - %s\n", string, x+1, GetVehicleModelName(modelid), Plate);
        }
        Dialog_Show(playerid, "MDC_Found", DIALOG_STYLE_MSGBOX, sprintf("MDT: %s - Registered Vehicles", MDC_Data[playerid][Name]), string, "Kembali", "");
    }
    else
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_Found", DIALOG_STYLE_MSGBOX, sprintf("MDT: %s - Registered Vehicles", MDC_Data[playerid][Name]), "No data found...", "Kembali", "");
    }
    return 1;
}

forward MDCAllPointBulletin(playerid);
public MDCAllPointBulletin(playerid)
{
    new rows = cache_num_rows();
    if(rows)
    {
        PlayerPlayNearbySound(playerid, MDC_SELECT);

        new curr_page = index_pagination[playerid];
        new curr_index = curr_page * MAX_MDC_ROWS;
        new real_i = 0;

        for (new x = 0; x < MAX_MDC_ROWS; x++) {
            MDC_ListedData[playerid][x][warrantID] = EOS;
        }

        for (new x = curr_index; x < rows && real_i < MAX_MDC_ROWS; x++)
        {
            cache_get_value_index_int(x, 0, MDC_ListedData[playerid][real_i][warrantID]);
            cache_get_value_index(x, 1, MDC_ListedData[playerid][real_i][warrantTime]);
            cache_get_value_index(x, 2, MDC_ListedData[playerid][real_i][warrantDesc]);
            cache_get_value_index(x, 3, MDC_ListedData[playerid][real_i][warrantIssuer]);
            cache_get_value_index(x, 4, MDC_ListedData[playerid][real_i][warrantSuspect]);
            real_i++;
        }

        new string[1012];
        strcat(string, "Time\tWarrant description\tIssuer\tSuspect\n");

        for (new x = 0; x < real_i; x++)
        {
            strcat(string, sprintf("%s\t%s\t{0096FF}%s\t"ORANGE"%s\n", MDC_ListedData[playerid][x][warrantTime], MDC_ListedData[playerid][x][warrantDesc], MDC_ListedData[playerid][x][warrantIssuer], MDC_ListedData[playerid][x][warrantSuspect]));
        }

        new total_pages = (rows + MAX_MDC_ROWS - 1) / MAX_MDC_ROWS;
        new max_page = total_pages - 1;

        if (curr_page > 0) {
            strcat(string, ""RED"<< Sebelumnya");
            strcat(string, "\n");
        }
        if (curr_page < max_page) {
            strcat(string, ""GREEN">> Selanjutnya");
            strcat(string, "\n");
        }

        Dialog_Show(playerid, "LSPDMDCAPB", DIALOG_STYLE_TABLIST_HEADERS, "MDT: All Points Bulletin", string, "Pilih", "Kembali");
    }
    else
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_APBDetail", DIALOG_STYLE_MSGBOX, "MDT: All Points Bulletin", "No data found...", "Kembali", "");
    }
    return 1;
}

forward MDCNameSearchResult(playerid);
public MDCNameSearchResult(playerid)
{
    if(cache_num_rows() < 1)
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_NameSearch", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- MDT Name Search", "The name is not found!\nPlease insert the correct fullname:", "Insert", "Kembali");
        return 1;
    }
    else
    {
        cache_get_value_index_int(0, 0, MDC_Data[playerid][pID]);
        cache_get_value_index(0, 1, MDC_Data[playerid][Name]);
        cache_get_value_index(0, 2, MDC_Data[playerid][Birthday]);
        cache_get_value_index_int(0, 3, MDC_Data[playerid][Faction]);
        cache_get_value_index_int(0, 4, MDC_Data[playerid][FactionRank]);
        cache_get_value_index_int(0, 5, MDC_Data[playerid][GVL1Lic]);
        cache_get_value_index_int(0, 6, MDC_Data[playerid][GVL1LicTime]);
        cache_get_value_index_int(0, 7, MDC_Data[playerid][GVL2Lic]);
        cache_get_value_index_int(0, 8, MDC_Data[playerid][GVL2LicTime]);
        cache_get_value_index_int(0, 9, MDC_Data[playerid][MBLic]);
        cache_get_value_index_int(0, 10, MDC_Data[playerid][MBLicTime]);
        cache_get_value_index_int(0, 11, MDC_Data[playerid][BLic]);
        cache_get_value_index_int(0, 12, MDC_Data[playerid][BLicTime]);
        cache_get_value_index_int(0, 13, MDC_Data[playerid][Air1Lic]);
        cache_get_value_index_int(0, 14, MDC_Data[playerid][Air1LicTime]);
        cache_get_value_index_int(0, 15, MDC_Data[playerid][Air2Lic]);
        cache_get_value_index_int(0, 16, MDC_Data[playerid][Air2LicTime]);
        cache_get_value_index_int(0, 17, MDC_Data[playerid][FirearmLic]);
        cache_get_value_index_int(0, 18, MDC_Data[playerid][FirearmLicTime]);
        cache_get_value_index_int(0, 19, MDC_Data[playerid][HuntingLic]);
        cache_get_value_index_int(0, 20, MDC_Data[playerid][HuntingLicTime]);

        PlayerPlayNearbySound(playerid, MDC_SELECT);

        static string[64];
		format(string, sizeof(string), "MDT: %s - Dashboard", MDC_Data[playerid][Name]);
		Dialog_Show(playerid, "MDC_NameDashboard", DIALOG_STYLE_LIST, string, "Personal Information\nRegistered Vehicles\nPersonal Charges\nPersonal Warrants\nArrest Record", "Pilih", "Kembali");
    }
    return 1;
}

forward MDCPlateSearchResult(playerid);
public MDCPlateSearchResult(playerid)
{
    if(cache_num_rows() < 1)
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_PlateSearch", DIALOG_STYLE_INPUT, "{DA9100}Pahlawan Roleplay "WHITE"- MDT Plate Search", "The name is not found!\nPlease insert the correct fullname:", "Insert", "Kembali");
        return 1;
    }
    else
    {
        new rpID = -1;
        cache_get_value_index_int(0, 0, rpID);

        static string[1228];
        mysql_format(g_SQL, string, sizeof(string), "SELECT `phoneNumber` FROM `player_phones` WHERE `phoneOwner` = %d", rpID);
        mysql_pquery(g_SQL, string, "MDCPhoneNumberResult", "i", playerid);

        mysql_format(g_SQL, string, sizeof(string), "SELECT `pID`, `Char_Name`, `Char_Birthday`, `Char_Faction`, `Char_FactionRank`, `Char_GVL1Lic`, `Char_GVL1LicTime`, `Char_GVL2Lic`, `Char_GVL2LicTime`, \
        `Char_MBLic`, `Char_MBLicTime`, `Char_BLic`, `Char_BLicTime`, `Char_Air1Lic`, `Char_Air1LicTime`, `Char_Air2Lic`, `Char_Air2LicTime`, `Char_FirearmLic`, `Char_FirearmLicTime`, `Char_HuntingLic`, `Char_HuntingLicTime` FROM `player_characters` WHERE `pID` = %d", rpID);
        mysql_pquery(g_SQL, string, "MDCNameSearchResult", "i", playerid);
    }
    return 1;
}

forward MDCCheckActiveCharges(playerid);
public MDCCheckActiveCharges(playerid)
{
    new rows = cache_num_rows();
    if(rows > 0)
    {
        PlayerPlayNearbySound(playerid, MDC_SELECT);

        new curr_page = index_pagination[playerid];
        new curr_index = curr_page * MAX_MDC_ROWS;
        new real_i = 0;

        for (new x = 0; x < MAX_MDC_ROWS; x++) {
            MDC_ListedData[playerid][x][chargeID] = 0;
        }

        for (new x = curr_index; x < rows && real_i < MAX_MDC_ROWS; x++)
        {
            cache_get_value_index_int(x, 0, MDC_ListedData[playerid][real_i][chargeID]);
            cache_get_value_index(x, 1, MDC_ListedData[playerid][real_i][chargeTime]);
            cache_get_value_index(x, 2, MDC_ListedData[playerid][real_i][chargeDesc]);
            cache_get_value_index(x, 3, MDC_ListedData[playerid][real_i][chargeIssuer]);
            real_i++;
        }

        new string[1012];
        strcat(string, "Time\tCharge description\tIssuer\tStatus\n");

        for (new x = 0; x < real_i; x++)
        {
            strcat(string, sprintf("%s\t%s\t{0096FF}%s\t"ORANGE"Active\n", MDC_ListedData[playerid][x][chargeTime], MDC_ListedData[playerid][x][chargeDesc], MDC_ListedData[playerid][x][chargeIssuer]));
        }

        new total_pages = (rows + MAX_MDC_ROWS - 1) / MAX_MDC_ROWS;
        new max_page = total_pages - 1;

        if (curr_page > 0) {
            strcat(string, ""RED"<< Sebelumnya");
            strcat(string, "\n");
        }
        if (curr_page < max_page) {
            strcat(string, ""GREEN">> Selanjutnya");
            strcat(string, "\n");
        }

        Dialog_Show(playerid, "LSPDCHECKACTCHARGES", DIALOG_STYLE_TABLIST_HEADERS, sprintf("MDT: %s - Active Charges", MDC_Data[playerid][Name]), string, "Delete", "Kembali");
    }
    else
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_Found", DIALOG_STYLE_MSGBOX, sprintf("MDT: %s - Active Charges", MDC_Data[playerid][Name]), "No data found...", "Kembali", "");
    }
    return 1;
}

forward MDCCheckActiveWarrants(playerid);
public MDCCheckActiveWarrants(playerid)
{
    new rows = cache_num_rows();
    if(rows)
    {
        PlayerPlayNearbySound(playerid, MDC_SELECT);

        new curr_page = index_pagination[playerid];
        new curr_index = curr_page * MAX_MDC_ROWS;
        new real_i = 0;

        // Membersihkan data lama
        for (new x = 0; x < MAX_MDC_ROWS; x++) {
            MDC_ListedData[playerid][x][warrantID] = 0;
        }

        for (new x = curr_index; x < rows && real_i < MAX_MDC_ROWS; x++)
        {
            cache_get_value_index_int(x, 0, MDC_ListedData[playerid][real_i][warrantID]);
            cache_get_value_index(x, 1, MDC_ListedData[playerid][real_i][warrantTime]);
            cache_get_value_index(x, 2, MDC_ListedData[playerid][real_i][warrantDesc]);
            cache_get_value_index(x, 3, MDC_ListedData[playerid][real_i][warrantIssuer]);
            real_i++;
        }

        new string[1012];
        strcat(string, "Time\tWarrant description\tIssuer\tStatus\n");

        for (new x = 0; x < real_i; x++)
        {
            strcat(string, sprintf("%s\t%s\t{0096FF}%s\t"ORANGE"Active\n", MDC_ListedData[playerid][x][warrantTime], MDC_ListedData[playerid][x][warrantDesc], MDC_ListedData[playerid][x][warrantIssuer]));
        }

        new total_pages = (rows + MAX_MDC_ROWS - 1) / MAX_MDC_ROWS;
        new max_page = total_pages - 1;

        if (curr_page > 0) {
            strcat(string, ""RED"<< Sebelumnya");
            strcat(string, "\n");
        }
        if (curr_page < max_page) {
            strcat(string, ""GREEN">> Selanjutnya");
            strcat(string, "\n");
        }

        Dialog_Show(playerid, "LSPDCHECKACTWARRANTS", DIALOG_STYLE_TABLIST_HEADERS, sprintf("MDT: %s - Active Warrants", MDC_Data[playerid][Name]), string, "Delete", "Kembali");
    }
    else
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_Found", DIALOG_STYLE_MSGBOX, sprintf("MDT: %s - Active Warrants", MDC_Data[playerid][Name]), "No data found...", "Kembali", "");
    }
    return 1;
}

forward MDCCheckChargesHistory(playerid);
public MDCCheckChargesHistory(playerid)
{
    new rows = cache_num_rows();
    if(rows > 0)
    {
        PlayerPlayNearbySound(playerid, MDC_SELECT);

        new curr_page = MDC_ChargesHistoryPagination[playerid];
        new curr_index = curr_page * MAX_MDC_ROWS;
        new real_i = 0;

        static time[128], desc[144], issuuer[25];

        for (new x = curr_index; x < rows && real_i < MAX_MDC_ROWS; x++)
        {
            cache_get_value_index(x, 0, time);
            cache_get_value_index(x, 1, desc);
            cache_get_value_index(x, 2, issuuer);
            real_i++;
        }

        new string[1012];
        strcat(string, "Time\tCharge description\tIssuer\tStatus\n");

        for (new x = 0; x < real_i; x++)
        {
            strcat(string, sprintf("%s\t%s\t{0096FF}%s\t"GREEN"Inactive", time, desc, issuuer));
        }

        new total_pages = (rows + MAX_MDC_ROWS - 1) / MAX_MDC_ROWS;
        new max_page = total_pages - 1;

        if (curr_page > 0) {
            strcat(string, ""RED"<< Sebelumnya");
            strcat(string, "\n");
        }
        if (curr_page < max_page) {
            strcat(string, ""GREEN">> Selanjutnya");
            strcat(string, "\n");
        }

        Dialog_Show(playerid, "LSPDCHARGESHISTORY", DIALOG_STYLE_TABLIST_HEADERS, sprintf("MDT: %s - Charges History", MDC_Data[playerid][Name]), string, "Kembali", "");
    }
    else
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_Found", DIALOG_STYLE_MSGBOX, sprintf("MDT: %s - Charges History", MDC_Data[playerid][Name]), "No data found...", "Kembali", "");
    }
    return 1;
}

forward ArrestRecordDetails(playerid, listid);
public ArrestRecordDetails(playerid, listid)
{
    new rows = cache_num_rows();

    if(rows > 0)
    {
        static string[1024];
        format(string, sizeof(string), ""YELLOW"A. Arrest Detail\n\
        "WHITE"Suspect: "RED"%s\n", MDC_Data[playerid][Name]);
        format(string, sizeof(string), "%s"WHITE"Arrested by: "GREEN"%s\n\
        "WHITE"Detentions: "ORANGE"%s\n\
        "YELLOW"B. Charges\n", string, MDC_ListedData[playerid][listid][arrrecordOfficer], MDC_ListedData[playerid][listid][arrrecordDets]);
        
        for(new x; x < rows; x++)
        {
            cache_get_value_index(x, 0, MDC_ListedData[playerid][x][chargeTime]);
            cache_get_value_index(x, 1, MDC_ListedData[playerid][x][chargeDesc]);
            cache_get_value_index(x, 2, MDC_ListedData[playerid][x][chargeIssuer]);
            format(string, sizeof(string), "%s"CYAN"%d. %s\n\
            "WHITE"Issued by: {0096FF}%s "WHITE"| Issued on: "GREEN"%s\n", string, x+1, MDC_ListedData[playerid][x][chargeDesc], MDC_ListedData[playerid][x][chargeIssuer], MDC_ListedData[playerid][x][chargeTime]);
        }
        Dialog_Show(playerid, "MDC_Found", DIALOG_STYLE_MSGBOX, sprintf("MDT: %s - Arrest Record Details", MDC_Data[playerid][Name]), string, "Kembali", "");
    }
    else
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_Found", DIALOG_STYLE_MSGBOX, sprintf("MDT: %s - Arrest Record Details", MDC_Data[playerid][Name]), "No charges data...", "Kembali", "");
    }
    return 1;
}

Dialog:LSPDARRRECORD(playerid, response, listitem, inputtext[])
{
    if (!response)
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        static string[64];
        format(string, sizeof(string), "MDT: %s - Dashboard", MDC_Data[playerid][Name]);
        Dialog_Show(playerid, "MDC_NameDashboard", DIALOG_STYLE_LIST, string, "Personal Information\nRegistered Vehicles\nPersonal Charges\nPersonal Warrants\nArrest Record", "Pilih", "Kembali");
        return 1;
    }

    if (!strcmp(inputtext, ">> Selanjutnya", true)) {
        index_pagination[playerid]++;
        MDCArrestRecord(playerid); 
    }
    else if (!strcmp(inputtext, "<< Sebelumnya", true)) {
        index_pagination[playerid]--;
        if (index_pagination[playerid] < 0) {
            index_pagination[playerid] = 0;
        }
        MDCArrestRecord(playerid);
    }
    else {
        static string[555];
        mysql_format(g_SQL, string, sizeof(string), "SELECT `time`, `description`, `issuer` FROM `mdc_charges` WHERE `ownerid` = %d and `arrest_report_id` = %d", MDC_Data[playerid][pID], MDC_ListedData[playerid][listitem][arrrecordID]);
        mysql_pquery(g_SQL, string, "ArrestRecordDetails", "id", playerid, listitem);
    }
    return 1;
}

Dialog:LSPDVIEWBRCAST(playerid, response, listitem, inputtext[])
{
    if (!response)
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_Main", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- MDT Dashboard", "Name Search\nPlate Search\nAll Points Bulletin\nCrime Broadcast\nRoster", "Pilih", "Logout");
        return 1;
    }

    if (!strcmp(inputtext, ">> Selanjutnya", true)) {
        index_pagination[playerid]++;
        MDCViewBroadcasts(playerid); 
    }
    else if (!strcmp(inputtext, "<< Sebelumnya", true)) {
        index_pagination[playerid]--;
        if (index_pagination[playerid] < 0) {
            index_pagination[playerid] = 0;
        }
        MDCViewBroadcasts(playerid);
    }
    else {
        AccountData[playerid][pTempValue] = listitem;

        static string[555];
        format(string, sizeof(string), ""YELLOW"Broadcast detail:\n\
        "AQUAMARINE"%s\n\
        "WHITE"Announced by: {0096FF}%s "WHITE"| Announced on: "ORANGE"%s", MDC_ListedData[playerid][listitem][broadcastDesc], MDC_ListedData[playerid][listitem][broadcastIssuer], MDC_ListedData[playerid][listitem][broadcastTime]);
        
        PlayerPlayNearbySound(playerid, MDC_SELECT);
        Dialog_Show(playerid, "MDC_APBDetail", DIALOG_STYLE_MSGBOX, "MDT: Broadcast Detail", string, "Kembali", "");
    }
    return 1;
}

Dialog:LSPDCHARGESHISTORY(playerid, response, listitem, inputtext[])
{
    if (!response)
    {
        static string[64];
        format(string, sizeof(string), "MDT: %s - Dashboard", MDC_Data[playerid][Name]);
        Dialog_Show(playerid, "MDC_NameDashboard", DIALOG_STYLE_LIST, string, "Personal Information\nRegistered Vehicles\nPersonal Charges\nPersonal Warrants\nArrest Record", "Pilih", "Kembali");
        return 1;
    }

    if (!strcmp(inputtext, ">> Selanjutnya", true)) {
        index_pagination[playerid]++;
        MDCCheckChargesHistory(playerid); 
    }
    else if (!strcmp(inputtext, "<< Sebelumnya", true)) {
        index_pagination[playerid]--;
        if (index_pagination[playerid] < 0) {
            index_pagination[playerid] = 0;
        }
        MDCCheckChargesHistory(playerid); 
    }
    else {
        static string[64];
        format(string, sizeof(string), "MDT: %s - Dashboard", MDC_Data[playerid][Name]);
        Dialog_Show(playerid, "MDC_NameDashboard", DIALOG_STYLE_LIST, string, "Personal Information\nRegistered Vehicles\nPersonal Charges\nPersonal Warrants\nArrest Record", "Pilih", "Kembali");
    }
    return 1;
}

Dialog:LSPDCHECKACTWARRANTS(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_WarrantsMenu", DIALOG_STYLE_LIST, sprintf("MDT: %s - Personal Warrants", MDC_Data[playerid][Name]), "Add New Warrants\nCheck Active Warrants", "Pilih", "Kembali");
        return 1;
    }

    if (!strcmp(inputtext, ">> Selanjutnya", true)) {
        index_pagination[playerid]++;
        MDCCheckActiveWarrants(playerid); 
    }
    else if (!strcmp(inputtext, "<< Sebelumnya", true)) {
        index_pagination[playerid]--;
        if (index_pagination[playerid] < 0) {
            index_pagination[playerid] = 0;
        }
        MDCCheckActiveWarrants(playerid); 
    }
    else {

        AccountData[playerid][pTempValue] = listitem;

        static string[555];
        format(string, sizeof(string), ""YELLOW"Active warrant detail:\n\
        "AQUAMARINE"%s\n\
        "WHITE"Issuer: {0096FF}%s "WHITE"| Issued on: "ORANGE"%s\n\n\
        "WHITE"Apakah anda yakin ingin menghapus active warrant ini?", MDC_ListedData[playerid][listitem][warrantDesc], MDC_ListedData[playerid][listitem][warrantIssuer], MDC_ListedData[playerid][listitem][warrantTime]);
        Dialog_Show(playerid, "MDC_ActWarrantsDelete", DIALOG_STYLE_MSGBOX, sprintf("MDT: %s - Active Warrant Detail", MDC_Data[playerid][Name]), string, "Confirm", "Kembali");
    }
    return 1;
}

Dialog:LSPDCHECKACTCHARGES(playerid, response, listitem, inputtext[])
{
    if (!response)
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_ChargeMenu", DIALOG_STYLE_LIST, sprintf("MDT: %s - Personal Charges", MDC_Data[playerid][Name]), "Add New Charges\nCheck Active Charges\nCheck Charges History", "Pilih", "Kembali");
        return 1;
    }

    if (!strcmp(inputtext, ">> Selanjutnya", true)) {
        
        index_pagination[playerid]++;
        MDCCheckActiveCharges(playerid);
    }
    else if (!strcmp(inputtext, "<< Sebelumnya", true)) {
        
        index_pagination[playerid]--;
        if (index_pagination[playerid] < 0) {
            index_pagination[playerid] = 0;
        }
        MDCCheckActiveCharges(playerid); 
    }
    else {
        
        AccountData[playerid][pTempValue] = listitem;

        static string[555];
        format(string, sizeof(string), ""YELLOW"Active charge detail:\n\
        "AQUAMARINE"%s\n\
        "WHITE"Issuer: {0096FF}%s "WHITE"| Issued on: "ORANGE"%s\n\n\
        "WHITE"Apakah anda yakin ingin menghapus active charge ini?", MDC_ListedData[playerid][listitem][chargeDesc], MDC_ListedData[playerid][listitem][chargeIssuer], MDC_ListedData[playerid][listitem][chargeTime]);
        Dialog_Show(playerid, "MDC_AddChargeDelete", DIALOG_STYLE_MSGBOX, sprintf("MDT: %s - Active Charge Detail", MDC_Data[playerid][Name]), string, "Confirm", "Kembali");
    }
    return 1;
}

Dialog:LSPDMDCAPB(playerid, response, listitem, inputtext[])
{
    if (!response)
    {
        PlayerPlayNearbySound(playerid, MDC_ERROR);
        Dialog_Show(playerid, "MDC_Main", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- MDT Dashboard", "Name Search\nPlate Search\nAll Points Bulletin\nCrime Broadcast\nRoster", "Pilih", "Logout");
        return 1;
    }

    if (!strcmp(inputtext, ">> Selanjutnya", true)) {

        index_pagination[playerid]++;
        MDCAllPointBulletin(playerid);
    }
    else if (!strcmp(inputtext, "<< Sebelumnya", true)) {
        index_pagination[playerid]--;
        if (index_pagination[playerid] < 0) {
            index_pagination[playerid] = 0;
        }
        MDCAllPointBulletin(playerid);
    }
    else {
        static string[555];
        format(string, sizeof(string), ""YELLOW"Active warrant detail:\n\
        "WHITE"Suspect name: "RED"%s\n\
        "AQUAMARINE"%s\n\
        "WHITE"Issuer: {0096FF}%s "WHITE"| Issued on: "ORANGE"%s", MDC_ListedData[playerid][listitem][warrantSuspect], MDC_ListedData[playerid][listitem][warrantDesc], MDC_ListedData[playerid][listitem][warrantIssuer], MDC_ListedData[playerid][listitem][warrantTime]);
        Dialog_Show(playerid, "MDC_APBDetail", DIALOG_STYLE_MSGBOX, "MDT: All Points Bulletin", string, "Kembali", "");
    }
    return 1;
}

Dialog:LSPDKickMember(playerid, response, listitem, inputtext[])
{
    if (!response)
        return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    if (!strcmp(inputtext, ">> Selanjutnya", true)) {
        index_pagination[playerid]++;
        ShowLSPDKick(playerid);
    }
    else if (!strcmp(inputtext, "<< Sebelumnya", true)) {
        index_pagination[playerid]--;
        if (index_pagination[playerid] < 0) {
            index_pagination[playerid] = 0;
        }
        ShowLSPDKick(playerid);
    }
    else 
    {
        new l_row_pid = ListedMember[playerid][listitem];

        if (AccountData[playerid][pFaction] != FACTION_LSPD)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Pahlawan Roleplay!");

        if(AccountData[playerid][pFactionRank] < 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimum rank KOMPOL untuk akses menu faction!");

        mysql_query(g_SQL, sprintf("SELECT * FROM `player_characters` WHERE `pID` = %d", l_row_pid));
        new rows = cache_num_rows();
        if (rows) 
        {
            new fckname[64], fckrank, fcklastlogin[30], kckstr[225], iscr[128];
            cache_get_value_name(0, "Char_Name", fckname);
            cache_get_value_name_int(0, "Char_FactionRank", fckrank);
            cache_get_value_name(0, "Char_LastLogin", fcklastlogin);

            if (AccountData[playerid][pID] == l_row_pid)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menendang diri sendiri!");

            if (fckrank >= AccountData[playerid][pFactionRank])
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menendang rekan sejajar/lebih tinggi dari anda!");

            static 
                string[168];

            mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `demand_vehicles` WHERE `ownerid` = %d", l_row_pid);
            mysql_pquery(g_SQL, string);

            foreach(new i : Player)
            {
                if(l_row_pid == AccountData[i][pID])
                {
                    for(new x = 0; x < MAX_FACTIONS; x++)
                    {
                        DestroyVehicle(PlayerFactionVehicle[i][x]);
                        PlayerFactionVehicle[i][x] = INVALID_VEHICLE_ID;
                    }
                    LSPDPlayerCallsign[i][0] = EOS;
                    
                    AccountData[i][pFaction] = 0;
                    AccountData[i][pFactionRank] = 0;

                    if(Iter_Contains(LSPDDuty, i))
                        Iter_Remove(LSPDDuty, i);

                    ShowTDN(i, NOTIFICATION_WARNING, "Anda telah ditendang dari Kepolisian Pahlawan Roleplay!");
                    break;
                }
            }

            InsertFactionLog("Kick", sprintf("%s %s - %s", AccountData[playerid][pName], AccountData[playerid][pUCP], fckname), "Kepolisian Pahlawan Roleplay");

            mysql_format(g_SQL, iscr, sizeof(iscr), "UPDATE `player_characters` SET `Char_Faction` = 0, `Char_FactionRank` = 0 WHERE `pID` = %d", l_row_pid);
            mysql_pquery(g_SQL, iscr);

            format(kckstr, sizeof(kckstr), "Anda berhasil mengeluarkan:\n\
            Name: %s\n\
            Rank: %s\n\
            Last Online: %s", fckname, CopRank[fckrank], fcklastlogin);
            Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Kick Faction", kckstr, "Tutup", "");
        }
    }
    return 1;
}