#include <YSI_Coding\y_hooks>

new g_CargoGetCooldown;

enum E_CARGOSTUFF
{
    CargoType,
    CargoRandom,
    CargoCountdown,
    bool:CargoStarted,
    bool:IsLoadingCargo,
    bool:CargoDetached,

    STREAMER_TAG_3D_TEXT_LABEL:CargoStartLabel,
    STREAMER_TAG_MAP_ICON:CargoStartIcon,
    STREAMER_TAG_RACE_CP:CargoDestCP,
    STREAMER_TAG_RACE_CP:CargoReturnCP
};
new PlayerCargoVars[MAX_PLAYERS][E_CARGOSTUFF];

enum ___g_CargoDestsDetails
{
    Float:CargoDestPos[3],
    CargoTrailer,
    CargoName[64],
    CargoPrice
};

enum __g_PetrolDestsDetails
{
    Float:CargoDestPos[3],
    CargoPrice
};

new g_PetrolDests[][__g_PetrolDestsDetails] =
{
    {{-2405.7683,979.7831,45.9028}, 2000}, //udah
    {{-1683.3212,418.9603,7.7864}, 2000}, //udah
    {{2211.4045,2475.1863,11.4270}, 3500}, //udah
    {{1944.8320,-1770.2030,13.9941}, 3500}, //udah
    {{652.3137,-560.3205,16.9333}, 4000}, //udah
    {{-1326.5215,2689.7131,50.6688}, 4000}, //udah
    {{-1477.6272,1862.3267,33.2410}, 4000}, //udah
    {{1005.0671,-940.2714,42.7593}, 5400} //udah
};

new g_CargoDests[][___g_CargoDestsDetails] =
{
    {{-300.9482,2664.2781,63.3241}, 591, "Ayam Petelor", 3500}, //udah
    {{1601.3813,1845.1252,11.4272}, 435, "Alat Medis", 5400}, //udah
    {{2747.7485,-1997.0367,13.9522}, 591, "Kertas", 3500}, //udah
    {{2198.2817,-2655.9587,14.1525}, 435, "Televisi", 3500}, //udah
    {{251.5552,-69.3397,2.0364}, 435, "Beer & Whiskey", 5400}, //udah
    {{-2382.5854,910.3105,45.9025}, 435, "Pakaian", 2000}, //udah
    {{-1863.1881,1407.9139,7.7926}, 435, "Perlengkapan Pekerja", 2000}, //udah
    {{-108.6874,9.5304,3.7199}, 591, "Alat Perkebunan", 2000}, //udah
    {{-1492.3522,1968.3777,48.7942}, 591, "Buah Kelapa Sawit", 5400}, //udah
    {{-2067.9121,-2357.7285,31.2354}, 591, "Kayu Jati", 5400}, //udah
    {{-585.2427,-497.6519,26.1300}, 435, "Prabot Rumah Tangga", 2000},
    {{2535.3730,2713.6519,11.4264}, 450, "Batu Bara", 3500}, //udah
    {{1080.8950,1923.2223,11.4230}, 435, "Kardus", 3500}, //udah
    {{2817.8276,-1089.4753,31.3437}, 435, "Sabun", 5400}, //udah
    {{2716.2678,755.7529,11.5144}, 591, "Alat Memasak", 5400}, //udah
    {{1328.5126,723.5270,11.5472}, 591, "Sparepart Kendaraan", 3500}, //udah
    {{362.4464,862.6805,20.4063}, 450, "Pasir", 5400}, //udah
    {{-30.2187,-1127.3728,0.6454}, 591, "Alok", 5400}, //udah
    {{290.7721,2540.5742,17.4268}, 435, "Puing Pesawat", 3500}, //udah
    {{1904.0917,956.6699,11.4261}, 435, "Mesin Tembak Ikan", 5400}, //udah
    {{2736.9370,-2556.3965,14.2476}, 435, "Kain Songket Deli", 3500}, //udah
    {{2759.2271,-2362.9143,14.2393}, 435, "Kaos Jegez", 3500}, //udah
    {{2795.1548,-2365.1111,14.2386}, 450, "Tembakau Deli", 3500} //udah
};

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && AccountData[playerid][pJob] == JOB_CARGO)
    {
        if(IsPlayerInRangeOfPoint(playerid, 1.5, -1680.2018,26.4608,3.6853))
        {
            if(IsValidVehicle(JobVehicle[playerid]) || IsValidVehicle(TrailerVehicle[playerid]))
            {
                DestroyVehicle(TrailerVehicle[playerid]);
                DestroyVehicle(JobVehicle[playerid]);

                pLoadCargoTimer[playerid] = false;

                AccountData[playerid][pActivityTime] = 0;
                HideProgressBar(playerid);

                PlayerCargoVars[playerid][IsLoadingCargo] = false;
                PlayerCargoVars[playerid][CargoStarted] = false;
                PlayerCargoVars[playerid][CargoDetached] = false;
                PlayerCargoVars[playerid][CargoType] = 0;

                ResetAllRaceCP(playerid);

                ClearAnimations(playerid, true);
                StopLoopingAnim(playerid);
                SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
                TogglePlayerControllable(playerid, true);

                ShowTDN(playerid, NOTIFICATION_SUCCESS, "Anda berhasil membatalkan pekerjaan dan mengembalikan kendaraannya.");
            }
            else
            {
                Dialog_Show(playerid, "CargoStart", DIALOG_STYLE_LIST, "{DA9100}Pahlawan Roleplay "WHITE"- Pilih Kargo", "Pertamina\n"GRAY"Barang", "Pilih", "Batal");
            }
        }
    }
    return 1;
}

Dialog:CargoStart(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;

    if(gettime() < g_CargoGetCooldown) return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Mohon tunggu %d detik", g_CargoGetCooldown - gettime()));
    g_CargoGetCooldown = gettime() + 15;
    switch(listitem)
    {
        case 0: //pertamina
        {
            if(IsValidVehicle(TrailerVehicle[playerid])){
                DestroyVehicle(TrailerVehicle[playerid]);
                TrailerVehicle[playerid] = INVALID_VEHICLE_ID;
            }

            if(IsValidVehicle(JobVehicle[playerid])){
                DestroyVehicle(JobVehicle[playerid]);
                JobVehicle[playerid] = INVALID_VEHICLE_ID;
            }

            ResetAllRaceCP(playerid);

            PlayerCargoVars[playerid][CargoRandom] = random(sizeof(g_PetrolDests));
            TrailerVehicle[playerid] = CreateVehicle(584,-1700.4563,18.1844,4.1443,316.4278,-1,-1, 60000, false);
            SetValidVehicleHealth(TrailerVehicle[playerid], 1000.0); 
            VehicleCore[TrailerVehicle[playerid]][vMaxHealth] = 1000.0;
            JobVehicle[playerid] = CreateVehicle(514,-1700.4563,18.1844,4.1443,316.4278,-1,-1, 60000, false);
            VehicleCore[JobVehicle[playerid]][vCoreFuel] = 50;
            SetValidVehicleHealth(JobVehicle[playerid], 1000.0); 
            VehicleCore[JobVehicle[playerid]][vMaxHealth] = 1000.0;
            VehicleCore[JobVehicle[playerid]][vCoreLocked] = false;
            PutPlayerInVehicleEx(playerid, JobVehicle[playerid], 0);
            SwitchVehicleEngine(JobVehicle[playerid], true);
            SwitchVehicleDoors(JobVehicle[playerid], false);

            AttachTrailerToVehicle(TrailerVehicle[playerid], JobVehicle[playerid]);

            PlayerCargoVars[playerid][IsLoadingCargo] = false;
            PlayerCargoVars[playerid][CargoType] = 1;
            PlayerCargoVars[playerid][CargoStarted] = true;

            PlayerCargoVars[playerid][CargoDestCP] = CreateDynamicRaceCP(1, g_PetrolDests[PlayerCargoVars[playerid][CargoRandom]][CargoDestPos][0], g_PetrolDests[PlayerCargoVars[playerid][CargoRandom]][CargoDestPos][1], g_PetrolDests[PlayerCargoVars[playerid][CargoRandom]][CargoDestPos][2], g_PetrolDests[PlayerCargoVars[playerid][CargoRandom]][CargoDestPos][0], g_PetrolDests[PlayerCargoVars[playerid][CargoRandom]][CargoDestPos][1], g_PetrolDests[PlayerCargoVars[playerid][CargoRandom]][CargoDestPos][2], 5.0, 0, 0, playerid, 6000.00, -1, 0);
            SendClientMessageEx(playerid, -1, "[i] Silakan ikuti tanda untuk mengangkut muatan "YELLOW"Bahan Bakar "WHITE"yang terletak di %s.", GetLocation(g_PetrolDests[PlayerCargoVars[playerid][CargoRandom]][CargoDestPos][0], g_PetrolDests[PlayerCargoVars[playerid][CargoRandom]][CargoDestPos][1], g_PetrolDests[PlayerCargoVars[playerid][CargoRandom]][CargoDestPos][2]));
        }
        case 1: //barang
        {
            if(IsValidVehicle(TrailerVehicle[playerid])){
                DestroyVehicle(TrailerVehicle[playerid]);
                TrailerVehicle[playerid] = INVALID_VEHICLE_ID;
            }

            if(IsValidVehicle(JobVehicle[playerid])){
                DestroyVehicle(JobVehicle[playerid]);
                JobVehicle[playerid] = INVALID_VEHICLE_ID;
            }

            ResetAllRaceCP(playerid);

            PlayerCargoVars[playerid][CargoRandom] = random(sizeof(g_CargoDests));
            TrailerVehicle[playerid] = CreateVehicle(g_CargoDests[PlayerCargoVars[playerid][CargoRandom]][CargoTrailer],-1700.4563,18.1844,4.1443,316.4278,-1,-1, 60000, false);
            SetValidVehicleHealth(TrailerVehicle[playerid], 1000.0); 
            VehicleCore[TrailerVehicle[playerid]][vMaxHealth] = 1000.0;
            JobVehicle[playerid] = CreateVehicle(403,-1700.4563,18.1844,4.1443,316.4278,-1,-1, 60000, false);
            VehicleCore[JobVehicle[playerid]][vCoreFuel] = 50;
            SetValidVehicleHealth(JobVehicle[playerid], 1000.0); 
            VehicleCore[JobVehicle[playerid]][vMaxHealth] = 1000.0;
            VehicleCore[JobVehicle[playerid]][vCoreLocked] = false;
            PutPlayerInVehicleEx(playerid, JobVehicle[playerid], 0);
            SwitchVehicleEngine(JobVehicle[playerid], true);
            SwitchVehicleDoors(JobVehicle[playerid], false);

            AttachTrailerToVehicle(TrailerVehicle[playerid], JobVehicle[playerid]);

            PlayerCargoVars[playerid][IsLoadingCargo] = false;
            PlayerCargoVars[playerid][CargoType] = 2;
            PlayerCargoVars[playerid][CargoStarted] = true;

            PlayerCargoVars[playerid][CargoDestCP] = CreateDynamicRaceCP(1, g_CargoDests[PlayerCargoVars[playerid][CargoRandom]][CargoDestPos][0], g_CargoDests[PlayerCargoVars[playerid][CargoRandom]][CargoDestPos][1], g_CargoDests[PlayerCargoVars[playerid][CargoRandom]][CargoDestPos][2], g_CargoDests[PlayerCargoVars[playerid][CargoRandom]][CargoDestPos][0], g_CargoDests[PlayerCargoVars[playerid][CargoRandom]][CargoDestPos][1], g_CargoDests[PlayerCargoVars[playerid][CargoRandom]][CargoDestPos][2], 5.0, 0, 0, playerid, 6000.00, -1, 0);
            SendClientMessageEx(playerid, -1, "[i] Silakan ikuti tanda untuk mengangkut muatan "YELLOW"%s "WHITE"yang terletak di %s.", g_CargoDests[PlayerCargoVars[playerid][CargoRandom]][CargoName], GetLocation(g_CargoDests[PlayerCargoVars[playerid][CargoRandom]][CargoDestPos][0], g_CargoDests[PlayerCargoVars[playerid][CargoRandom]][CargoDestPos][1], g_CargoDests[PlayerCargoVars[playerid][CargoRandom]][CargoDestPos][2]));
        }
    }
    return 1;
}

hook OnPlayerEnterDynRaceCP(playerid, STREAMER_TAG_RACE_CP:checkpointid)
{
    if(AccountData[playerid][pJob] == JOB_CARGO && GetPlayerState(playerid) == PLAYER_STATE_DRIVER && IsPlayerInVehicle(playerid, JobVehicle[playerid]))
    {
        if(checkpointid == PlayerCargoVars[playerid][CargoDestCP] && IsPlayerInDynamicRaceCP(playerid, PlayerCargoVars[playerid][CargoDestCP]))
        {
            if(PlayerCargoVars[playerid][CargoStarted])
            {
                if(!PlayerCargoVars[playerid][IsLoadingCargo])
                {
                    if(!IsTrailerAttachedToVehicle(JobVehicle[playerid])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang mengangkut trailer!");
                    if(GetVehicleTrailer(JobVehicle[playerid]) != TrailerVehicle[playerid]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Trailer ini bukan milik anda!");
                    
                    PlayerCargoVars[playerid][IsLoadingCargo] = true;
                    AccountData[playerid][pActivityTime] = 1;
                    TogglePlayerControllable(playerid, false);
                    pLoadCargoTimer[playerid] = true;
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMUAT KARGO");
                    ShowProgressBar(playerid);
                }
            }
        }
        else if(checkpointid == PlayerCargoVars[playerid][CargoReturnCP] && IsPlayerInDynamicRaceCP(playerid, PlayerCargoVars[playerid][CargoReturnCP]))
        {
            if(!PlayerCargoVars[playerid][CargoStarted])
            {
                if(IsValidVehicle(TrailerVehicle[playerid])){
                    DestroyVehicle(TrailerVehicle[playerid]);
                    TrailerVehicle[playerid] = INVALID_VEHICLE_ID;
                }

                if(IsValidVehicle(JobVehicle[playerid])){
                    DestroyVehicle(JobVehicle[playerid]);
                    JobVehicle[playerid] = INVALID_VEHICLE_ID;
                }

                if(PlayerCargoVars[playerid][CargoType] == 2)
                {
                    SendClientMessageEx(playerid, -1, "[i] Anda berhasil ekspor "YELLOW"%s "WHITE"seharga "DARKGREEN"$%s.", g_CargoDests[PlayerCargoVars[playerid][CargoRandom]][CargoName], FormatMoney(g_CargoDests[PlayerCargoVars[playerid][CargoRandom]][CargoPrice]));
                    GivePlayerMoneyEx(playerid, g_CargoDests[PlayerCargoVars[playerid][CargoRandom]][CargoPrice]);
                    ShowItemBox(playerid, "Cash", sprintf("Received $%sx", FormatMoney(g_CargoDests[PlayerCargoVars[playerid][CargoRandom]][CargoPrice])), 1212, 5);
                }
                else
                {
                    SendClientMessageEx(playerid, -1, "[i] Anda berhasil ekspor "YELLOW"Bahan Bakar "WHITE"seharga "DARKGREEN"$%s.", FormatMoney(g_PetrolDests[PlayerCargoVars[playerid][CargoRandom]][CargoPrice]));
                    GivePlayerMoneyEx(playerid, g_PetrolDests[PlayerCargoVars[playerid][CargoRandom]][CargoPrice]);
                    ShowItemBox(playerid, "Cash", sprintf("Received $%sx", FormatMoney(g_PetrolDests[PlayerCargoVars[playerid][CargoRandom]][CargoPrice])), 1212, 5);
                }

                pLoadCargoTimer[playerid] = false;
                AccountData[playerid][pActivityTime] = 0;
                HideProgressBar(playerid);

                PlayerCargoVars[playerid][IsLoadingCargo] = false;
                PlayerCargoVars[playerid][CargoStarted] = false;
                PlayerCargoVars[playerid][CargoDetached] = false;
                PlayerCargoVars[playerid][CargoType] = 0;

                ResetAllRaceCP(playerid);

                ClearAnimations(playerid, true);
                StopLoopingAnim(playerid);
                SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
                TogglePlayerControllable(playerid, true);
            }
        }
    }
    return 1;
}

hook OnPlayerLeaveDynRaceCP(playerid, STREAMER_TAG_RACE_CP:checkpointid)
{
    if(AccountData[playerid][pJob] == JOB_CARGO && GetPlayerState(playerid) == PLAYER_STATE_DRIVER && IsPlayerInVehicle(playerid, JobVehicle[playerid]))
    {
        if(checkpointid == PlayerCargoVars[playerid][CargoDestCP])
        {
            PlayerCargoVars[playerid][IsLoadingCargo] = false;
            pLoadCargoTimer[playerid] = false;
            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            TogglePlayerControllable(playerid, true);
        }
    }
    return 1;
}

ptask CheckingTrailer[1000](playerid) 
{
    if(AccountData[playerid][pJob] == JOB_CARGO && PlayerCargoVars[playerid][CargoType] > 0)
    {
        if(!IsValidVehicle(JobVehicle[playerid]))
        {
            PlayerCargoVars[playerid][CargoCountdown] = 0;

            DestroyVehicle(TrailerVehicle[playerid]);

            JobVehicle[playerid] = INVALID_VEHICLE_ID;

            pLoadCargoTimer[playerid] = false;

            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            PlayerCargoVars[playerid][IsLoadingCargo] = false;
            PlayerCargoVars[playerid][CargoStarted] = false;
            PlayerCargoVars[playerid][CargoDetached] = false;
            PlayerCargoVars[playerid][CargoType] = 0;

            ResetAllRaceCP(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            SendClientMessage(playerid, -1, "[i] Misi kargo anda dinyatakan gagal karena truk anda hilang.");
            return 1;
        }

        if(!IsValidVehicle(TrailerVehicle[playerid])){
            PlayerCargoVars[playerid][CargoCountdown] = 0;

            TrailerVehicle[playerid] = INVALID_VEHICLE_ID;
            DestroyVehicle(JobVehicle[playerid]);

            pLoadCargoTimer[playerid] = false;

            AccountData[playerid][pActivityTime] = 0;
            HideProgressBar(playerid);

            PlayerCargoVars[playerid][IsLoadingCargo] = false;
            PlayerCargoVars[playerid][CargoStarted] = false;
            PlayerCargoVars[playerid][CargoDetached] = false;
            PlayerCargoVars[playerid][CargoType] = 0;

            ResetAllRaceCP(playerid);

            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(playerid, true);

            SendClientMessage(playerid, -1, "[i] Misi kargo anda dinyatakan gagal karena kehilangan trailer.");
            return 1;
        }

        if(IsTrailerAttachedToVehicle(JobVehicle[playerid]) && GetVehicleTrailer(JobVehicle[playerid]) == TrailerVehicle[playerid])
        {
            if(PlayerCargoVars[playerid][CargoDetached])
            {
                PlayerCargoVars[playerid][CargoDetached] = false;
                PlayerCargoVars[playerid][CargoCountdown] = 0;
                return 1;
            }
        }

        if(!PlayerCargoVars[playerid][CargoDetached])
        {
            if(!IsTrailerAttachedToVehicle(JobVehicle[playerid]) && GetVehicleTrailer(JobVehicle[playerid]) != TrailerVehicle[playerid])
            {
                PlayerCargoVars[playerid][CargoDetached] = true;
                PlayerCargoVars[playerid][CargoCountdown] = 30;
                SendClientMessage(playerid, -1, "[i] Trailer kargo terlepas, anda memiliki "RED"30 detik "WHITE"untuk menyatukannya kembali!");
            }
        }
        else
        {
            if(PlayerCargoVars[playerid][CargoCountdown] > 0)
            {
                PlayerCargoVars[playerid][CargoCountdown]--;
                GameTextForPlayer(playerid, sprintf("%d", PlayerCargoVars[playerid][CargoCountdown]), 1000, 4);
            }
            else
            {
                PlayerCargoVars[playerid][CargoCountdown] = 0;

                if(!IsTrailerAttachedToVehicle(JobVehicle[playerid]) && GetVehicleTrailer(JobVehicle[playerid]) != TrailerVehicle[playerid])
                {
                    DestroyVehicle(TrailerVehicle[playerid]);
                    DestroyVehicle(JobVehicle[playerid]);

                    pLoadCargoTimer[playerid] = false;

                    AccountData[playerid][pActivityTime] = 0;
                    HideProgressBar(playerid);

                    PlayerCargoVars[playerid][IsLoadingCargo] = false;
                    PlayerCargoVars[playerid][CargoStarted] = false;
                    PlayerCargoVars[playerid][CargoDetached] = false;
                    PlayerCargoVars[playerid][CargoType] = 0;

                    ResetAllRaceCP(playerid);

                    ClearAnimations(playerid, true);
                    StopLoopingAnim(playerid);
                    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
                    TogglePlayerControllable(playerid, true);

                    SendClientMessage(playerid, -1, "[i] Misi kargo anda dinyatakan gagal karena kehilangan trailer.");
                }
                else
                {
                    PlayerCargoVars[playerid][CargoDetached] = false;
                }
            }
        }
    }
    return 1;
}