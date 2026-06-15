YCMD:emsheli(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] != FACTION_LSFD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Paramedis Pahlawan Roleplay!");

    if(!IsPlayerInRangeOfPoint(playerid, 3.0, 1780.3328,-1112.9495,38.1213)) return SEM(playerid, "You aren't at EMS Spawn Heli Point!");

    if(Iter_Contains(Vehicle, JobVehicle[playerid]))
    {
        DestroyVehicle(JobVehicle[playerid]);

        ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mengembalikan helikopter Maverick Paramedis Pahlawan Roleplay.");
    }
    else
    {
        JobVehicle[playerid] = CreateVehicle(487, 1772.9725,-1121.7661,38.2911,88.4195, 3, 3, 60000, false);
        VehicleCore[JobVehicle[playerid]][vCoreFuel] = 1000;
        SetValidVehicleHealth(JobVehicle[playerid], 2000.0); 
        VehicleCore[JobVehicle[playerid]][vMaxHealth] = 2000.0;
        VehicleCore[JobVehicle[playerid]][vIsBodyUpgraded] = true;
        VehicleCore[JobVehicle[playerid]][vIsBodyBroken] = false;
        VehicleCore[JobVehicle[playerid]][vCoreLocked] = false;
        SwitchVehicleEngine(JobVehicle[playerid], true);
        SwitchVehicleDoors(JobVehicle[playerid], false);

        ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah mengeluarkan helikopter Maverick Paramedis Pahlawan Roleplay.");
    }
    return 1;
}

YCMD:makebpjs(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] != FACTION_LSFD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Paramedis Pahlawan Roleplay!");

    static targetid, bpjstype, duration, esxs[512];
    if(sscanf(params, "idd", targetid, bpjstype, duration))
        return SUM(playerid, "/makebpjs [playerid] [class 1 - 3] [expired]");

    if(!IsPlayerInRangeOfPoint(playerid, 4.0, 1722.2932,-1111.4496,24.8906))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di tempat yang seharusnya!");

    if(!IsPlayerConnected(targetid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    if(!AccountData[targetid][pSpawned])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut belum spawn!");

    if(!IsPlayerNearPlayer(playerid, targetid, 2.5)) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada dekat dengan pemain tersebut!");

    if(DocumentInfo[targetid][BPJS])
        return SEM(playerid, "Pemain tersebut sudah memiliki BPJS!");

    if(bpjstype < 1 || bpjstype > 3)
        return SEM(playerid, "Class BPJS invalid! (1 - 3)");

    if(duration < 1 || duration > 14)
        return SEM(playerid, "Expired BPJS invalid (1 - 14 hari)");
    
    DocumentInfo[targetid][BPJS] = true;
    DocumentInfo[targetid][BPJSClass] = bpjstype;
    DocumentInfo[targetid][BPJSDur] = gettime() + (duration * 86400);
    strcopy(DocumentInfo[targetid][BPJSIssuer], GetPlayerRoleplayName(playerid));
    strcopy(DocumentInfo[targetid][BPJSIssuerRank], GetRankName(playerid));
    strcopy(DocumentInfo[targetid][BPJSIssueDate], GetAdvTime());

    mysql_format(g_SQL, esxs, sizeof(esxs), "INSERT INTO `documents` SET `Owner_ID` = %d, `Type` = 1, `BPJS_Class` = %d, `BPJS_Dur` = %d, `BPJS_Issuer` = '%e', `BPJS_IssuerRank` = '%e', `BPJS_IssueDate` = '%e'",
    AccountData[targetid][pID], DocumentInfo[targetid][BPJSClass], DocumentInfo[targetid][BPJSDur], DocumentInfo[targetid][BPJSIssuer], DocumentInfo[targetid][BPJSIssuerRank], DocumentInfo[targetid][BPJSIssueDate]);
    mysql_pquery(g_SQL, esxs);

    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Pembuatan BPJS berhasil dilakukan.");
    ShowTDN(targetid, NOTIFICATION_INFO, "Anda telah diberikan BPJS dari petugas.");
    return 1;
}

YCMD:makesks(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] != FACTION_LSFD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Paramedis Pahlawan Roleplay!");

    if(!IsPlayerInRangeOfPoint(playerid, 4.0, 1722.2932,-1111.4496,24.8906))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di tempat yang seharusnya!");

    static targetid, duration, text[64], esxs[512];
    if(sscanf(params, "ids[64]", targetid, duration, text))
        return SUM(playerid, "/makesks [playerid] [expired] [note]");
    
    if(!IsPlayerConnected(targetid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    if(!AccountData[targetid][pSpawned])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut belum spawn!");

    if(!IsPlayerNearPlayer(playerid, targetid, 2.5)) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada dekat dengan pemain tersebut!");

    if(DocumentInfo[targetid][SKS])
        return SEM(playerid, "Pemain tersebut sudah memiliki SKS!");

    if(duration < 1 || duration > 24)
        return SEM(playerid, "Expired SKS tidak valid (1 - 24 hari)");
    
    DocumentInfo[targetid][SKS] = true;
    DocumentInfo[targetid][SKSDur] = gettime() + (duration * 86400);
    strcopy(DocumentInfo[targetid][SKSText], text);
    strcopy(DocumentInfo[targetid][SKSIssuer], GetPlayerRoleplayName(playerid));
    strcopy(DocumentInfo[targetid][SKSIssuerRank], GetRankName(playerid));
    strcopy(DocumentInfo[targetid][SKSIssueDate], GetAdvTime());

    mysql_format(g_SQL, esxs, sizeof(esxs), "INSERT INTO `documents` SET `Owner_ID` = %d, `Type` = 2, `SKS_Dur` = %d, `SKS_Text` = '%e', `SKS_Issuer` = '%e', `SKS_IssuerRank` = '%e', `SKS_IssueDate` = '%e'",
    AccountData[targetid][pID], DocumentInfo[targetid][SKSDur], DocumentInfo[targetid][SKSText], DocumentInfo[targetid][SKSIssuer], DocumentInfo[targetid][SKSIssuerRank], DocumentInfo[targetid][SKSIssueDate]);
    mysql_pquery(g_SQL, esxs);

    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Pembuatan SKS berhasil dilakukan.");
    ShowTDN(targetid, NOTIFICATION_INFO, "Anda telah diberikan SKS dari petugas.");
    return 1;
}

YCMD:slist(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] != FACTION_LSFD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Paramedis Pahlawan Roleplay!");

    index_pagination[playerid] = 0;
    ShowInjuredList(playerid);
    return 1;
}

Dialog:InjuredList(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

    if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih signal apapun!");

    if (!strcmp(inputtext, ">> Selanjutnya", true))
    {
        index_pagination[playerid]++;
        ShowInjuredList(playerid);
    }
    else if (!strcmp(inputtext, "<< Prev", true))
    {
        index_pagination[playerid]--;
        if (index_pagination[playerid] < 0)
        {
            index_pagination[playerid] = 0;
        }
        ShowInjuredList(playerid);
    }
    else
    {
        static targetid, string[144];
        targetid = PlayerListitem[playerid][listitem];

        if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
        if(!AccountData[targetid][pSpawned]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut belum spawn!");
        if(AccountData[targetid][pDelayKnockdownSignalSent] <= gettime()) return SEM(playerid, "Pemain tersebut sudah tidak mengirim sinyal lagi!");

        new Float:x, Float:y, Float:z;
        GetPlayerPos(targetid, x, y, z);

        if(DestroyDynamicMapIcon(AccountData[playerid][pSignalIcon]))
            AccountData[playerid][pSignalIcon] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;

        AccountData[playerid][pSignalIcon] = CreateDynamicMapIcon(x, y, z, 36, 0, -1, -1, playerid, 10000.00, MAPICON_GLOBAL, -1, 0);

        format(string, sizeof(string), "(Paramedis - %s %s): "WHITE"> Menuju panggilan sinyal darurat atas nama %s di %s <.", GetRankName(playerid), GetPlayerRoleplayName(playerid), GetPlayerRoleplayName(targetid), GetLocation(x, y, z));
        SendClientMessageToAll(0xFF1A1AFF, string);

        ShowTDN(playerid, NOTIFICATION_WARNING, "Mohon ikuti checkpoint di map!");

        SendClientMessageEx(targetid, -1, "Sinyal darurat anda telah direspon oleh petugas Paramedis %s", GetPlayerRoleplayName(playerid));
        AccountData[targetid][pDelayKnockdownSignalSent] = 0;

        for(new d; d < 200; d++)
        {
            PlayerListitem[playerid][d] = INVALID_PLAYER_ID;
        }
    }
    return 1;
}

YCMD:makesp(playerid, params[], help)
{
    if(AccountData[playerid][pFaction] != FACTION_LSFD) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Paramedis Pahlawan Roleplay!");

    if(!IsPlayerInRangeOfPoint(playerid, 4.0, 1722.2932,-1111.4496,24.8906))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di tempat yang seharusnya!");

    static targetid, duration, text[64], esxs[512];
    if(sscanf(params, "ids[64]", targetid, duration, text))
        return SUM(playerid, "/makesp [playerid] [expired] [note]");
    
    if(!IsPlayerConnected(targetid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    if(!AccountData[targetid][pSpawned])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut belum spawn!");

    if(!IsPlayerNearPlayer(playerid, targetid, 2.5)) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada dekat dengan pemain tersebut!");

    if(DocumentInfo[targetid][SP])
        return SEM(playerid, "Pemain tersebut sudah memiliki Surat Psikologi!");

    if(duration < 1 || duration > 24)
        return SEM(playerid, "Expired SP tidak valid (1 - 24 hari)");
    
    DocumentInfo[targetid][SP] = true;
    DocumentInfo[targetid][SPDur] = gettime() + (duration * 86400);
    strcopy(DocumentInfo[targetid][SPText], text);
    strcopy(DocumentInfo[targetid][SPIssuer], GetPlayerRoleplayName(playerid));
    strcopy(DocumentInfo[targetid][SPIssuerRank], GetRankName(playerid));
    strcopy(DocumentInfo[targetid][SPIssueDate], GetAdvTime());

    mysql_format(g_SQL, esxs, sizeof(esxs), "INSERT INTO `documents` SET `Owner_ID` = %d, `Type` = 5, `SP_Dur` = %d, `SP_Text` = '%e', `SP_Issuer` = '%e', `SP_IssuerRank` = '%e', `SP_IssueDate` = '%e'",
    AccountData[targetid][pID], DocumentInfo[targetid][SPDur], DocumentInfo[targetid][SPText], DocumentInfo[targetid][SPIssuer], DocumentInfo[targetid][SPIssuerRank], DocumentInfo[targetid][SPIssueDate]);
    mysql_pquery(g_SQL, esxs);

    ShowTDN(playerid, NOTIFICATION_SUCCESS, "Pembuatan Surat Psikologi (SP) berhasil dilakukan.");
    ShowTDN(targetid, NOTIFICATION_INFO, "Anda telah diberikan Surat Psikologi (SP) dari petugas.");
    return 1;
}