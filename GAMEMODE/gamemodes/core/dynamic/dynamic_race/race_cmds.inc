#include <YSI_Coding\y_hooks>

#define MAX_RACE 1000
#define MAX_PRACE_CP 30

enum e_racedetails
{
    bool:raceStarted,
    bool:raceFinished,
    raceBet,
    raceJointime,
    raceCreatorID,

    STREAMER_TAG_3D_TEXT_LABEL:raceLabel
};
new RaceData[MAX_RACE][e_racedetails];

enum e_racecpsinfo
{
    Float:raceCP[3]
};
new RacePlayerCP[MAX_RACE][MAX_PRACE_CP][e_racecpsinfo],
    Iterator:PRaces<MAX_RACE>;

new bool:RaceCreatorMode[MAX_PLAYERS],
    STREAMER_TAG_RACE_CP:PlayerRaceCP[MAX_PLAYERS],
    RaceCreatorCPIndex[MAX_PLAYERS],
    RaceJoinedID[MAX_PLAYERS],
    RacePlayerStep[MAX_PLAYERS];

GetNearestRaceID(playerid)
{
    foreach(new rc : PRaces) 
    {
        if(RaceData[rc][raceJointime] > 0)
        {
            if(IsPlayerInRangeOfPoint(playerid, 5.55, RacePlayerCP[rc][0][raceCP][0], RacePlayerCP[rc][0][raceCP][1], RacePlayerCP[rc][0][raceCP][2]))
            {
                return rc;
            }
        }
    }
    return -1;
}

ResetRaceVars(id)
{
    if(id != -1)
    {
        RaceData[id][raceStarted] = false;
        RaceData[id][raceFinished] = false;
        RaceData[id][raceBet] = 0;
        RaceData[id][raceJointime] = 0;

        if(DestroyDynamic3DTextLabel(RaceData[id][raceLabel]))
            RaceData[id][raceLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        RaceData[id][raceCreatorID] = INVALID_PLAYER_ID;

        for(new x; x < MAX_PRACE_CP; x++)
        {
            RacePlayerCP[id][x][raceCP][0] = 0.0;
            RacePlayerCP[id][x][raceCP][1] = 0.0;
            RacePlayerCP[id][x][raceCP][2] = 0.0;
        }
    }
    return 1;
}

YCMD:race(playerid, params[], help)
{
    new type[24], string[128];
    if(sscanf(params, "s[24]S()[128]", type, string)) return SUM(playerid, "/race [name]~n~create, reset, start, join, leave");

    if(AccountData[playerid][pKnockdown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat mengikuti event dalam keadaan pingsan!");
    if(OJailData[playerid][jailed] || AccountData[playerid][pArrested]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat mengikuti event dalam keadaan dipenjara!");

    if(!strcmp(type, "create", true))
    {
        if(RaceCreatorMode[playerid]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang dalam mode pembuatan race!");
        if(RaceJoinedID[playerid] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang berada di dalam balapan!");

        new id = Iter_Free(PRaces), money;
        if(id <= -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Total race di server sudah mencapai maksimal!");

        if(sscanf(string, "d", money))
            return SUM(playerid, "/race [create] [taruhan]");

        if(money < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Race bet tidak dapat kurang dari $1!");

        if(AccountData[playerid][pMoney] < RoundNegativeToPositive(money)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
        
        RaceCreatorMode[playerid] = true;
        RaceCreatorCPIndex[playerid] = -1;
        RaceJoinedID[playerid] = id;
        RacePlayerStep[playerid] = 0;

        RaceData[id][raceBet] = money;
        RaceData[id][raceCreatorID] = playerid;

        SendClientMessage(playerid, -1, "Selamat datang di mode pembuatan race {DA9100}Pahlawan Roleplay!");
        SendClientMessage(playerid, -1, "Anda dapat menggunakan "YELLOW"'/race reset' "WHITE"jikalau ingin reset semua checkpoint yang telah dibuat.");
        SendClientMessage(playerid, -1, "Dalam proses pembuatan checkpoint anda dapaat menekan tombol "YELLOW"H/Klakson "WHITE"untuk menetapkan posisi checkpoint.");
        SendClientMessage(playerid, -1, "Sementara itu, jika dirasa sudah cukup checkpoint. Gunakan "YELLOW"'/race start' "WHITE"untuk memulai balapan.");
        SendClientMessage(playerid, -1, "Sebelum memulai, pastikan anda berada di posisi awal checkpoint pertama!");

        Iter_Add(PRaces, id);
    }
    else if(!strcmp(type, "reset", true))
    {
        if(!RaceCreatorMode[playerid]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang di dalam mode pembuatan race");

        RaceCreatorCPIndex[playerid] = -1;

        new id = RaceJoinedID[playerid];
        if(!Iter_Contains(PRaces, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid race ID!");
        
        for(new x; x < MAX_PRACE_CP; x++)
        {
            RacePlayerCP[id][x][raceCP][0] = 0.0;
            RacePlayerCP[id][x][raceCP][1] = 0.0;
            RacePlayerCP[id][x][raceCP][2] = 0.0;
        }
        SendClientMessage(playerid, -1, "Anda berhasil reset ulang checkpoint balap!");
    }
    else if(!strcmp(type, "start", true))
    {
        new id = RaceJoinedID[playerid], detik;
        if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di dalam race manapun!");
        if(RaceData[id][raceCreatorID] != playerid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan pembuat balapan ini!");
        if(RacePlayerCP[id][0][raceCP][0] == 0.0 && RacePlayerCP[id][0][raceCP][1] == 0.0 && RacePlayerCP[id][0][raceCP][2] == 0.0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Belum ada checkpoint yang ditetapkan!");
        if(RaceData[id][raceStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Balapan telah dimulai!");

        if(sscanf(string, "d", detik))
            return SUM(playerid, "/race [start] [detik join]");

        RaceData[id][raceJointime] = detik;

        if(DestroyDynamic3DTextLabel(RaceData[id][raceLabel]))
            RaceData[id][raceLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        RaceCreatorMode[playerid] = false;
        RaceCreatorCPIndex[playerid] = -1;
        RacePlayerStep[playerid] = 0;

        TakePlayerMoneyEx(playerid, RaceData[id][raceBet]);
        ShowItemBox(playerid, "Cash", sprintf("Removed $%sx", FormatMoney(RaceData[id][raceBet])), 1212, 5);

        format(string, sizeof(string), "Race for "GREEN"$%s "WHITE"starting in "YELLOW"%ds\n"WHITE"Press "GREEN"[H/Klakson] "WHITE"to join", FormatMoney(RaceData[id][raceBet]), RaceData[id][raceJointime]);
        RaceData[id][raceLabel] = CreateDynamic3DTextLabel(string, Y_WHITE, RacePlayerCP[id][0][raceCP][0], RacePlayerCP[id][0][raceCP][1], RacePlayerCP[id][0][raceCP][2], 55.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 55.00, -1, 0);
    }
    else if(!strcmp(type, "join", true))
    {
        if(RaceJoinedID[playerid] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah ikut serta ke dalam sebuah race!");

        new rcid = GetNearestRaceID(playerid);
        if(rcid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di lokasi join race manapun!");

        if(RaceData[rcid][raceStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Balapan ini sudah dimulai!");

        RaceJoinedID[playerid] = rcid;
        RacePlayerStep[playerid] = 0;

        SendClientMessage(playerid, -1, "Anda berhasil ikut serta ke dalam race ini, gunakan "YELLOW"'/race leave' "WHITE"jika ingin keluar!");
    }
    else if(!strcmp(type, "leave", true))
    {
        if(RaceJoinedID[playerid] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak ikut serta ke dalam sebuah race manapun!");

        if(RaceData[RaceJoinedID[playerid]][raceCreatorID] == playerid)
        {
            ResetRaceVars(RaceJoinedID[playerid]);
            Iter_Remove(PRaces, RaceJoinedID[playerid]);

            foreach(new i : Player) if(RaceJoinedID[i] == RaceJoinedID[playerid])
            {
                SendClientMessage(i, -1, "Balap telah dibubarkan karena pembuat memutuskan untuk keluar dari balapan!");

                if(DestroyDynamicRaceCP(PlayerRaceCP[i]))
                    PlayerRaceCP[i] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;
                
                RaceCreatorMode[i] = false;
                RaceJoinedID[i] = -1;
                RaceCreatorCPIndex[i] = -1;
                RacePlayerStep[i] = 0;
            }
        }
        RaceCreatorMode[playerid] = false;
        RaceJoinedID[playerid] = -1;
        RaceCreatorCPIndex[playerid] = -1;
        RacePlayerStep[playerid] = 0;

        ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil keluar dari peserta race tersebut!");
    }
    return 1;
}

task UpdateRaceStatus[1000]() 
{
    foreach(new rc : PRaces)
    {
        if(RaceData[rc][raceJointime] > 0)
        {
            RaceData[rc][raceJointime]--;

            static string[144];
            format(string, sizeof(string), "Race for "GREEN"$%s "WHITE"starting in "YELLOW"%ds\n"WHITE"Press "GREEN"[H/Klakson] "WHITE"to join", FormatMoney(RaceData[rc][raceBet]), RaceData[rc][raceJointime]);
            UpdateDynamic3DTextLabelText(RaceData[rc][raceLabel], Y_WHITE, string);

            if(RaceData[rc][raceJointime] == 0)
            {
                RaceData[rc][raceJointime] = 0;
                RaceData[rc][raceStarted] = true;

                if(DestroyDynamic3DTextLabel(RaceData[rc][raceLabel]))
                    RaceData[rc][raceLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

                foreach(new i : Player) if(RaceJoinedID[i] == rc)
                {
                    if(DestroyDynamicRaceCP(PlayerRaceCP[i]))
                        PlayerRaceCP[i] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

                    PlayerRaceCP[i] = CreateDynamicRaceCP(0, RacePlayerCP[rc][0][raceCP][0], RacePlayerCP[rc][0][raceCP][1], RacePlayerCP[rc][0][raceCP][2], RacePlayerCP[rc][1][raceCP][0],RacePlayerCP[rc][1][raceCP][1], RacePlayerCP[rc][1][raceCP][2], 3.5, -1, -1, i, 10000.00, -1, 0);

                    SendClientMessage(i, -1, "Balapan telah dimulai, ikuti checkpoint yang diberikan!");
                }
            }
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && newkeys & KEY_CROUCH)
    {
        if(RaceCreatorMode[playerid])
        {
            new index, id = RaceJoinedID[playerid];

            RaceCreatorCPIndex[playerid]++;
            index = RaceCreatorCPIndex[playerid]; //start dari 0

            GetVehiclePos(GetPlayerVehicleID(playerid), RacePlayerCP[id][index][raceCP][0], RacePlayerCP[id][index][raceCP][1], RacePlayerCP[id][index][raceCP][2]);

            SendClientMessage(playerid, -1, "Anda berhasil membuat "YELLOW"%d/30 checkpoint balap "WHITE"silakan lanjut apabila berkenan.", index+1); //0 + 1
            SendClientMessage(playerid, -1, "%d | %.2f, %.2f, %.2f", index,  RacePlayerCP[id][index][raceCP][0],  RacePlayerCP[id][index][raceCP][1],  RacePlayerCP[id][index][raceCP][2]);

            if(index >= 29)
            {
                RaceCreatorMode[playerid] = false;
                RaceCreatorCPIndex[playerid] = -1;

                SendClientMessage(playerid, -1, "Anda telah mencapai jumlah maksimal checkpoint dan telah keluar dari mode pembuatan race secara otomatis!");
            }
        }
    }
    return 1;
}

hook OnPlayerEnterDynRaceCP(playerid, STREAMER_TAG_RACE_CP:checkpointid)
{
    if(checkpointid == PlayerRaceCP[playerid] && RaceJoinedID[playerid] > -1 && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
    {
        new rcpid = RacePlayerStep[playerid], id = RaceJoinedID[playerid];

        if(DestroyDynamicRaceCP(PlayerRaceCP[playerid]))
            PlayerRaceCP[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

        //finish
        if(RacePlayerCP[id][rcpid+1][raceCP][0] == 0.0 && RacePlayerCP[id][rcpid+1][raceCP][1] == 0.0 && RacePlayerCP[id][rcpid+1][raceCP][2] == 0.0)
        {
            if(!RaceData[id][raceFinished])
            {
                RaceData[id][raceFinished] = true;

                foreach(new i : Player) if(RaceJoinedID[i] == id)
                {
                    SendClientMessageEx(i, X11_YELLOW, ""RED"%s "WHITE"telah memenangkan "GREEN"$%s "WHITE"karena juara satu pada balapan.", AccountData[playerid][pName], FormatMoney(RaceData[id][raceBet]));
                }
                GivePlayerMoneyEx(playerid, RaceData[id][raceBet]);
                ShowItemBox(playerid, "Cash", sprintf("Received $%sx", FormatMoney(RaceData[id][raceBet])), 1212, 5);
            }
            
            if(RaceData[id][raceCreatorID] == playerid)
            {
                ResetRaceVars(id);
                Iter_Remove(PRaces, id);

                foreach(new i : Player) if(RaceJoinedID[i] == id)
                {
                    SendClientMessage(i, -1, "Balap telah dibubarkan karena pembuat sudah mencapai finish!");

                    if(DestroyDynamicRaceCP(PlayerRaceCP[i]))
                        PlayerRaceCP[i] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;
                    
                    RaceCreatorMode[i] = false;
                    RaceJoinedID[i] = -1;
                    RaceCreatorCPIndex[i] = -1;
                    RacePlayerStep[i] = 0;
                }
            }
            RaceCreatorMode[playerid] = false;
            RaceJoinedID[playerid] = -1;
            RaceCreatorCPIndex[playerid] = -1;
            RacePlayerStep[playerid] = 0;
        }
        else
        {
            RacePlayerStep[playerid]++;

            PlayerRaceCP[playerid] = CreateDynamicRaceCP(0, RacePlayerCP[id][RacePlayerStep[playerid]][raceCP][0], RacePlayerCP[id][RacePlayerStep[playerid]][raceCP][1], RacePlayerCP[id][RacePlayerStep[playerid]][raceCP][2], RacePlayerCP[id][RacePlayerStep[playerid]+1][raceCP][0], RacePlayerCP[id][RacePlayerStep[playerid]+1][raceCP][1], RacePlayerCP[id][RacePlayerStep[playerid]+1][raceCP][2], 3.5, -1, -1, playerid, 10000.00, -1, 0);

            PlayerPlaySound(playerid, SOUND_CHECKPOINT, 0.0, 0.0, 0.0);
        }
    }
    return 1;
}