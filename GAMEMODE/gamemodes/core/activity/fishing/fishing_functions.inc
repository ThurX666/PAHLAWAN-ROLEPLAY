#include <YSI_Coding\y_hooks>

new Float:__g_FishingLoc[][3] =
{
    {403.8386,-2088.7981,7.9359},
    {398.7301,-2088.7908,7.9359},
    {396.1581,-2088.7903,7.9359},
    {391.0529,-2088.7981,7.9359},
    {383.4729,-2088.7910,7.9359},
    {374.9562,-2088.7976,7.9359},
    {369.8450,-2088.7976,7.9359},
    {367.2522,-2088.7920,7.9359},
    {362.1185,-2088.7979,7.9359},
    {354.5533,-2088.7915,7.9359},
    {349.9594,-2072.5090,7.9359},
    {349.9337,-2067.2839,7.9359},
    {349.9271,-2064.7588,7.9359},
    {349.9040,-2059.6938,7.9359},
    {349.8698,-2052.0752,7.9359}
};

enum
{
    BUTTON_NONE,
    BUTTON_ALT,
    BUTTON_F,
    BUTTON_H,
    BUTTON_Y,
    BUTTON_N
}

new bool:IsPlayerFishing[MAX_PLAYERS],
    FishingButton[MAX_PLAYERS];

IsPlayerInFishingArea(playerid)
{
    for(new x; x < sizeof(__g_FishingLoc); x++)
    {
        if(IsPlayerInRangeOfPoint(playerid, 3.0, __g_FishingLoc[x][0], __g_FishingLoc[x][1], __g_FishingLoc[x][2]) && GetPlayerVirtualWorld(playerid) == 0 && GetPlayerInterior(playerid) == 0)
        {
            return 1;
        }
    }
    return 0;
}

forward FishingFunc(playerid);
public FishingFunc(playerid)
{
    if(!PlayerHasItem(playerid, "Pancingan"))
    {
        PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
        IsPlayerFishing[playerid] = false;
        ClearAnimations(playerid, true);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        RemovePlayerAttachedObject(playerid, 9);

        FishingButton[playerid] = BUTTON_NONE;
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Pancingan!");
    }

    if(!IsPlayerInFishingArea(playerid))
    {
        PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
        IsPlayerFishing[playerid] = false;
        ClearAnimations(playerid, true);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        RemovePlayerAttachedObject(playerid, 9);

        FishingButton[playerid] = BUTTON_NONE;
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di Fishing Point/Fishing Area!");
    }

    new randbutton = RandomEx(1, 53);
    switch(randbutton)
    {
        case 1.. 9: //BUTTON_ALT
        {
            FishingButton[playerid] = BUTTON_ALT;
            SendClientMessage(playerid, -1, "[i] Umpan anda bergerak, gunakan "YELLOW"'ALT' "WHITE"untuk strike!");
        }
        case 10.. 20: //BUTTON_F
        {
            FishingButton[playerid] = BUTTON_F;
            SendClientMessage(playerid, -1, "[i] Umpan anda bergerak, gunakan "YELLOW"'F' "WHITE"untuk strike!");
        }
        case 21.. 31: //BUTTON_H
        {
            FishingButton[playerid] = BUTTON_H;
            SendClientMessage(playerid, -1, "[i] Umpan anda bergerak, gunakan "YELLOW"'H' "WHITE"untuk strike!");
        }
        case 32.. 42: //BUTTON_Y
        {
            FishingButton[playerid] = BUTTON_Y;
            SendClientMessage(playerid, -1, "[i] Umpan anda bergerak, gunakan "YELLOW"'Y' "WHITE"untuk strike!");
        }
        case 43.. 53: //BUTTON_N
        {
            FishingButton[playerid] = BUTTON_N;
            SendClientMessage(playerid, -1, "[i] Umpan anda bergerak, gunakan "YELLOW"'N' "WHITE"untuk strike!");
        }
    }
    return 1;
}

hook OnGameModeInit()
{
    for(new x; x < sizeof(__g_FishingLoc); x++)
    {
        CreateDynamic3DTextLabel("[Y] "WHITE"Mancing", Y_GREEN, __g_FishingLoc[x][0], __g_FishingLoc[x][1], __g_FishingLoc[x][2], 2.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 2.5, -1, 0);
    }

    CreateDynamic3DTextLabel("[Y] "WHITE"Jual Penyu", Y_RED, 2161.5310,-103.1758,2.7500, 2.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 2.5, -1, 0);
    CreateDynamic3DTextLabel("[Y] "WHITE"Jual Hiu", Y_RED, -489.2872,613.1413,1.7813, 2.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 2.5, -1, 0);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(FishingButton[playerid] == BUTTON_NONE)
    {
        if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
        {
            if(IsPlayerInRangeOfPoint(playerid, 3.5, 2161.5310,-103.1758,2.7500))
            {
                if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
                if(Iter_Count(LSPDDuty) < 4 || Iter_Count(LSFDDuty) < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Sabhara On Duty: 4~n~EMS On Duty: 2");
                if(!PlayerHasItem(playerid, "Penyu")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Penyu untuk dijual!");

                AccountData[playerid][pActivityTime] = 1;
                AccountData[playerid][pCountingValue] = Inventory_Count(playerid, "Penyu") + 1;
                pSellingTurtleTimer[playerid] = true;
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "JUAL PENYU");
                ShowProgressBar(playerid);

                SendTeamMessage(FACTION_LSPD, 0xff4b4bff, "> Telah terjadi penjualan penyu <");

                ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, true, false, false, false, 0, true);

                HideNotifBox(playerid);
            }

            if(IsPlayerInRangeOfPoint(playerid, 3.5, -489.2872,613.1413,1.7813))
            {
                if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
                if(Iter_Count(LSPDDuty) < 4 || Iter_Count(LSFDDuty) < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Sabhara On Duty: 4~n~EMS On Duty: 2");
                if(!PlayerHasItem(playerid, "Hiu")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Hiu untuk dijual!");

                AccountData[playerid][pActivityTime] = 1;
                AccountData[playerid][pCountingValue] = Inventory_Count(playerid, "Hiu") + 1;
                pSellingSharkTimer[playerid] = true;
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "JUAL HIU");
                ShowProgressBar(playerid);

                SendTeamMessage(FACTION_LSPD, 0xff4b4bff, "> Telah terjadi penjualan hiu <");

                ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, true, false, false, false, 0, true);

                HideNotifBox(playerid);
            }

            if(IsPlayerInFishingArea(playerid))
            {
                if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
                    return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berjalan kaki!");

                if(!PlayerHasItem(playerid, "Pancingan"))
                    return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki pancingan!");

                if(!PlayerHasItem(playerid, "Umpan"))
                    return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki umpan!");

                if(IsPlayerFishing[playerid])
                    return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang memancing!");

                if(AccountData[playerid][pKnockdown])
                    return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak bisa melakukannya saat ini!");

                new randfishtime = RandomEx(20000, 35000);
                new randevent = Random(101);

                Inventory_Remove(playerid, "Umpan");
                switch(randevent)
                {
                    case 0.. 95: //fishing berhasil
                    {
                        SetTimerEx("FishingFunc", randfishtime, false, "i", playerid);
                        IsPlayerFishing[playerid] = true;
                        ApplyAnimation(playerid, "SWORD", "sword_block", 4.1, 0, 1, 1, 1, 1, 1);
                        SetPlayerAttachedObject(playerid, 9, 18632, 6, 0.00000, 0.00000, 0.00000, 0.00000, 180.00000, 90.00000, 1, 1, 1);
                        SendClientMessage(playerid, -1, "[i] Anda mulai memancing.");
                    }

                    case 96.. 101: //pancingan kecebur
                    {
                        Inventory_Remove(playerid, "Pancingan");
                        SendClientMessage(playerid, -1, "[i] Saat anda ingin melemparkan umpan, pancingan anda ikut terlempar ke air.");
                    }
                }
            }
        }
    }

    if(FishingButton[playerid] == BUTTON_ALT)
    {
        if(newkeys & KEY_WALK && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
        {
            new randresult = Random(115);

            IsPlayerFishing[playerid] = false;
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            RemovePlayerAttachedObject(playerid, 9);

            FishingButton[playerid] = BUTTON_NONE;
            switch(randresult)
            {
                case 0.. 4: //sempak nenek
                {
                    SendClientMessage(playerid, -1, "[i] Zonk, anda mendapatkan "AQUAMARINE"sempak nenek-nenek.");
                }
                case 5.. 9: //kondom bocor
                {
                    SendClientMessage(playerid, -1, "[i] Zonk, anda mendapatkan "AQUAMARINE"kondom bocor.");
                }
                case 10.. 100: //ikan
                {
                    AccountData[playerid][pStress] -= 5;
                    
                    ShowItemBox(playerid, "Ikan", "Received 1x", 19630, 5);
                    Inventory_Add(playerid, "Ikan", 19630);
                    SendClientMessage(playerid, -1, "[i] Anda mendapatkan seekor "AQUAMARINE"Ikan.");
                }
                case 101.. 109: //Penyu
                {
                    AccountData[playerid][pStress] -= 5;
                    
                    ShowItemBox(playerid, "Penyu", "Received 1x", 1609, 5);
                    Inventory_Add(playerid, "Penyu", 1609);
                    SendClientMessage(playerid, -1, "[i] Anda mendapatkan seekor "AQUAMARINE"Penyu.");
                }
                case 110.. 114: //hiu
                {
                    AccountData[playerid][pStress] -= 5;
                    
                    ShowItemBox(playerid, "Hiu", "Received 1x", 1608, 5);
                    Inventory_Add(playerid, "Hiu", 1608);
                    SendClientMessage(playerid, -1, "[i] Anda mendapatkan seekor "AQUAMARINE"Hiu.");
                }
            }
        }
        else if(newkeys != KEY_WALK)
        {
            IsPlayerFishing[playerid] = false;
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            RemovePlayerAttachedObject(playerid, 9);
            FishingButton[playerid] = BUTTON_NONE;
            SendClientMessage(playerid, X11_YELLOW, "[i] Anda salah menekan tombol, ikan anda lepas!");
        }
    }
    if(FishingButton[playerid] == BUTTON_F)
    {
        if(newkeys & KEY_SECONDARY_ATTACK && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
        {
            new randresult = Random(115);

            IsPlayerFishing[playerid] = false;
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            RemovePlayerAttachedObject(playerid, 9);

            FishingButton[playerid] = BUTTON_NONE;
            switch(randresult)
            {
                case 0.. 4: //sempak nenek
                {
                    SendClientMessage(playerid, -1, "[i] Zonk, anda mendapatkan "AQUAMARINE"sempak nenek-nenek.");
                }
                case 5.. 9: //kondom bocor
                {
                    SendClientMessage(playerid, -1, "[i] Zonk, anda mendapatkan "AQUAMARINE"kondom bocor.");
                }
                case 10.. 100: //ikan
                {
                    AccountData[playerid][pStress] -= 5;
                    
                    ShowItemBox(playerid, "Ikan", "Received 1x", 19630, 5);
                    Inventory_Add(playerid, "Ikan", 19630);
                    SendClientMessage(playerid, -1, "[i] Anda mendapatkan seekor "AQUAMARINE"Ikan.");
                }
                case 101.. 109: //Penyu
                {
                    AccountData[playerid][pStress] -= 5;
                    
                    ShowItemBox(playerid, "Penyu", "Received 1x", 1609, 5);
                    Inventory_Add(playerid, "Penyu", 1609);
                    SendClientMessage(playerid, -1, "[i] Anda mendapatkan seekor "AQUAMARINE"Penyu.");
                }
                case 110.. 114: //hiu
                {
                    AccountData[playerid][pStress] -= 5;
                    
                    ShowItemBox(playerid, "Hiu", "Received 1x", 1608, 5);
                    Inventory_Add(playerid, "Hiu", 1608);
                    SendClientMessage(playerid, -1, "[i] Anda mendapatkan seekor "AQUAMARINE"Hiu.");
                }
            }
        }
        else if(newkeys != KEY_SECONDARY_ATTACK)
        {
            IsPlayerFishing[playerid] = false;
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            RemovePlayerAttachedObject(playerid, 9);
            FishingButton[playerid] = BUTTON_NONE;
            SendClientMessage(playerid, X11_YELLOW, "[i] Anda salah menekan tombol, ikan anda lepas!");
        }
    }
    if(FishingButton[playerid] == BUTTON_H)
    {
        if(newkeys & KEY_CTRL_BACK && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
        {
            new randresult = Random(115);

            IsPlayerFishing[playerid] = false;
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            RemovePlayerAttachedObject(playerid, 9);

            FishingButton[playerid] = BUTTON_NONE;
            switch(randresult)
            {
                case 0.. 4: //sempak nenek
                {
                    SendClientMessage(playerid, -1, "[i] Zonk, anda mendapatkan "AQUAMARINE"sempak nenek-nenek.");
                }
                case 5.. 9: //kondom bocor
                {
                    SendClientMessage(playerid, -1, "[i] Zonk, anda mendapatkan "AQUAMARINE"kondom bocor.");
                }
                case 10.. 100: //ikan
                {
                    AccountData[playerid][pStress] -= 5;
                    
                    ShowItemBox(playerid, "Ikan", "Received 1x", 19630, 5);
                    Inventory_Add(playerid, "Ikan", 19630);
                    SendClientMessage(playerid, -1, "[i] Anda mendapatkan seekor "AQUAMARINE"Ikan.");
                }
                case 101.. 109: //Penyu
                {
                    AccountData[playerid][pStress] -= 5;
                    
                    ShowItemBox(playerid, "Penyu", "Received 1x", 1609, 5);
                    Inventory_Add(playerid, "Penyu", 1609);
                    SendClientMessage(playerid, -1, "[i] Anda mendapatkan seekor "AQUAMARINE"Penyu.");
                }
                case 110.. 114: //hiu
                {
                    AccountData[playerid][pStress] -= 5;
                    
                    ShowItemBox(playerid, "Hiu", "Received 1x", 1608, 5);
                    Inventory_Add(playerid, "Hiu", 1608);
                    SendClientMessage(playerid, -1, "[i] Anda mendapatkan seekor "AQUAMARINE"Hiu.");
                }
            }
        }
        else if(newkeys != KEY_CTRL_BACK)
        {
            IsPlayerFishing[playerid] = false;
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            RemovePlayerAttachedObject(playerid, 9);
            FishingButton[playerid] = BUTTON_NONE;
            SendClientMessage(playerid, X11_YELLOW, "[i] Anda salah menekan tombol, ikan anda lepas!");
        }
    }
    if(FishingButton[playerid] == BUTTON_Y)
    {
        if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
        {
            new randresult = Random(115);

            IsPlayerFishing[playerid] = false;
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            RemovePlayerAttachedObject(playerid, 9);

            FishingButton[playerid] = BUTTON_NONE;
            switch(randresult)
            {
                case 0.. 4: //sempak nenek
                {
                    SendClientMessage(playerid, -1, "[i] Zonk, anda mendapatkan "AQUAMARINE"sempak nenek-nenek.");
                }
                case 5.. 9: //kondom bocor
                {
                    SendClientMessage(playerid, -1, "[i] Zonk, anda mendapatkan "AQUAMARINE"kondom bocor.");
                }
                case 10.. 100: //ikan
                {
                    AccountData[playerid][pStress] -= 5;
                    
                    ShowItemBox(playerid, "Ikan", "Received 1x", 19630, 5);
                    Inventory_Add(playerid, "Ikan", 19630);
                    SendClientMessage(playerid, -1, "[i] Anda mendapatkan seekor "AQUAMARINE"Ikan.");
                }
                case 101.. 109: //Penyu
                {
                    AccountData[playerid][pStress] -= 5;
                    
                    ShowItemBox(playerid, "Penyu", "Received 1x", 1609, 5);
                    Inventory_Add(playerid, "Penyu", 1609);
                    SendClientMessage(playerid, -1, "[i] Anda mendapatkan seekor "AQUAMARINE"Penyu.");
                }
                case 110.. 114: //hiu
                {
                    AccountData[playerid][pStress] -= 5;
                    
                    ShowItemBox(playerid, "Hiu", "Received 1x", 1608, 5);
                    Inventory_Add(playerid, "Hiu", 1608);
                    SendClientMessage(playerid, -1, "[i] Anda mendapatkan seekor "AQUAMARINE"Hiu.");
                }
            }
        }
        else if(newkeys != KEY_YES)
        {
            IsPlayerFishing[playerid] = false;
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            RemovePlayerAttachedObject(playerid, 9);
            FishingButton[playerid] = BUTTON_NONE;
            SendClientMessage(playerid, X11_YELLOW, "[i] Anda salah menekan tombol, ikan anda lepas!");
        }
    }
    if(FishingButton[playerid] == BUTTON_N)
    {
        if(newkeys & KEY_NO && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
        {
            new randresult = Random(115);

            IsPlayerFishing[playerid] = false;
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            RemovePlayerAttachedObject(playerid, 9);

            FishingButton[playerid] = BUTTON_NONE;
            switch(randresult)
            {
                case 0.. 4: //sempak nenek
                {
                    SendClientMessage(playerid, -1, "[i] Zonk, anda mendapatkan "AQUAMARINE"sempak nenek-nenek.");
                }
                case 5.. 9: //kondom bocor
                {
                    SendClientMessage(playerid, -1, "[i] Zonk, anda mendapatkan "AQUAMARINE"kondom bocor.");
                }
                case 10.. 100: //ikan
                {
                    AccountData[playerid][pStress] -= 5;
                    
                    ShowItemBox(playerid, "Ikan", "Received 1x", 19630, 5);
                    Inventory_Add(playerid, "Ikan", 19630);
                    SendClientMessage(playerid, -1, "[i] Anda mendapatkan seekor "AQUAMARINE"Ikan.");
                }
                case 101.. 109: //Penyu
                {
                    AccountData[playerid][pStress] -= 5;
                    
                    ShowItemBox(playerid, "Penyu", "Received 1x", 1609, 5);
                    Inventory_Add(playerid, "Penyu", 1609);
                    SendClientMessage(playerid, -1, "[i] Anda mendapatkan seekor "AQUAMARINE"Penyu.");
                }
                case 110.. 114: //hiu
                {
                    AccountData[playerid][pStress] -= 5;
                    
                    ShowItemBox(playerid, "Hiu", "Received 1x", 1608, 5);
                    Inventory_Add(playerid, "Hiu", 1608);
                    SendClientMessage(playerid, -1, "[i] Anda mendapatkan seekor "AQUAMARINE"Hiu.");
                }
            }
        }
        else if(newkeys != KEY_NO)
        {
            IsPlayerFishing[playerid] = false;
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            RemovePlayerAttachedObject(playerid, 9);
            FishingButton[playerid] = BUTTON_NONE;
            SendClientMessage(playerid, X11_YELLOW, "[i] Anda salah menekan tombol, ikan anda lepas!");
        }
    }
    return 1;
}

// enum
// {
//     AREA_TYPE_OCEAN,
//     AREA_TYPE_OCEAN_BOAT,
//     AREA_TYPE_LAKE,
//     AREA_TYPE_RIVER
// };

// enum
// {
//     AREA_DENSITY_LOW,
//     AREA_DENSITY_MEDIUM,
//     AREA_DENSITY_HIGH
// };

// enum _e_fishareadata
// {
//     Float:Pos[3],
//     Type,
//     Density
// };

// new __g_FishingLoc[][_e_fishareadata] =
// {
//     {{403.8386,-2088.7981,7.9359}, AREA_TYPE_OCEAN, AREA_DENSITY_LOW},
//     {{398.7301,-2088.7908,7.9359}, AREA_TYPE_OCEAN, AREA_DENSITY_LOW},
//     {{396.1581,-2088.7903,7.9359}, AREA_TYPE_OCEAN, AREA_DENSITY_LOW},
//     {{391.0529,-2088.7981,7.9359}, AREA_TYPE_OCEAN, AREA_DENSITY_LOW},
//     {{383.4729,-2088.7910,7.9359}, AREA_TYPE_OCEAN, AREA_DENSITY_LOW},
//     {{374.9562,-2088.7976,7.9359}, AREA_TYPE_OCEAN, AREA_DENSITY_LOW},
//     {{369.8450,-2088.7976,7.9359}, AREA_TYPE_OCEAN, AREA_DENSITY_LOW},
//     {{367.2522,-2088.7920,7.9359}, AREA_TYPE_OCEAN, AREA_DENSITY_LOW},
//     {{362.1185,-2088.7979,7.9359}, AREA_TYPE_OCEAN, AREA_DENSITY_LOW},
//     {{354.5533,-2088.7915,7.9359}, AREA_TYPE_OCEAN, AREA_DENSITY_LOW},
//     {{349.9594,-2072.5090,7.9359}, AREA_TYPE_OCEAN, AREA_DENSITY_LOW},
//     {{349.9337,-2067.2839,7.9359}, AREA_TYPE_OCEAN, AREA_DENSITY_LOW},
//     {{349.9271,-2064.7588,7.9359}, AREA_TYPE_OCEAN, AREA_DENSITY_LOW},
//     {{349.9040,-2059.6938,7.9359}, AREA_TYPE_OCEAN, AREA_DENSITY_LOW},
//     {{349.8698,-2052.0752,7.9359}, AREA_TYPE_OCEAN, AREA_DENSITY_LOW},

//     //boat
//     {{-100.6274,-1994.2738,-0.4372}, AREA_TYPE_OCEAN_BOAT, AREA_DENSITY_LOW}, //OCEAN 1
//     {{271.2468,-2139.1038,-0.5089}, AREA_TYPE_OCEAN_BOAT, AREA_DENSITY_LOW}, //OCEAN 2
//     {{415.2737,-2231.6433,-0.4954}, AREA_TYPE_OCEAN_BOAT, AREA_DENSITY_LOW}, //OCEAN 3
//     {{760.4944,-2435.7036,-0.2323}, AREA_TYPE_OCEAN_BOAT, AREA_DENSITY_LOW}, //OCEAN 4
//     {{502.9475,-2873.7485,-0.2706}, AREA_TYPE_OCEAN_BOAT, AREA_DENSITY_LOW}, //OCEAN 5
//     {{56.9209,-1451.0659,-0.4903}, AREA_TYPE_RIVER, AREA_DENSITY_LOW}, //RIVER 1
//     {{64.1360,-1124.0051,-0.5273}, AREA_TYPE_RIVER, AREA_DENSITY_LOW}, //RIVER 2
//     {{-70.2902,-917.2893,-0.4393}, AREA_TYPE_RIVER, AREA_DENSITY_LOW}, //RIVER 3
//     {{-259.5089,-707.6789,-0.5313}, AREA_TYPE_LAKE, AREA_DENSITY_LOW}, //LAKE 1
//     {{-269.4681,-509.4047,-0.3994}, AREA_TYPE_LAKE, AREA_DENSITY_LOW}, //LAAKE 2
//     {{-125.4368,-590.1354,-0.4065}, AREA_TYPE_LAKE, AREA_DENSITY_LOW}, //LAAKE 3
//     {{-701.6027,-330.7644,-0.4477}, AREA_TYPE_RIVER, AREA_DENSITY_LOW}, //RIVER 4
//     {{220.8192,-412.2692,-0.4912}, AREA_TYPE_RIVER, AREA_DENSITY_LOW}, //RIVER 5
//     {{574.1211,-233.6084,-0.4599}, AREA_TYPE_RIVER, AREA_DENSITY_LOW}, //RIVER 6
//     {{1617.6431,-29.7274,-0.4613}, AREA_TYPE_RIVER, AREA_DENSITY_LOW}, //RIVER 7
//     {{1929.7991,-147.6426,-0.4946}, AREA_TYPE_LAKE, AREA_DENSITY_LOW}, //LAKE 4
//     {{2101.1816,-203.3708,-0.4510}, AREA_TYPE_LAKE, AREA_DENSITY_LOW}, //LAKE 5
//     {{2141.9314,153.2683,-0.4814}, AREA_TYPE_RIVER, AREA_DENSITY_LOW} //RIVER 8
// };

// new STREAMER_TAG_AREA:FishingArea[sizeof(__g_FishingLoc)];
// new STREAMER_TAG_MAP_ICON:FishingIcon[MAX_PLAYERS][sizeof(__g_FishingLoc)];

// enum e_PFishDetails
// {
//     Weight,
//     Type
// };
// new PlayerFishes[MAX_PLAYERS][5][e_PFishDetails];

// enum
// {
//     BUTTON_NONE,
//     BUTTON_ALT,
//     BUTTON_F,
//     BUTTON_H,
//     BUTTON_Y,
//     BUTTON_N
// }

// new FishingButton[MAX_PLAYERS];

// IsPlayerInFishZone(playerid)
// {
//     for(new x; x < sizeof(__g_FishingLoc); x++)
//     {
//         if(__g_FishingLoc[x][Type] != AREA_TYPE_OCEAN)
//         {
//             if(IsPlayerInDynamicArea(playerid, FishingArea[x]))
//             {
//                 return true;
//             }
//         }
//     }
//     return false;
// }

// GetPlayerFishingAreaID(playerid)
// {
//     for(new x; x < sizeof(__g_FishingLoc); x++)
//     {
//         if(__g_FishingLoc[x][Type] == AREA_TYPE_OCEAN && IsPlayerInRangeOfPoint(playerid, 3.0, __g_FishingLoc[x][Pos][0], __g_FishingLoc[x][Pos][1], __g_FishingLoc[x][Pos][2]) && GetPlayerVirtualWorld(playerid) == 0 && GetPlayerInterior(playerid) == 0)
//         {
//             return x;
//         }
        
//         if(__g_FishingLoc[x][Type] >= AREA_TYPE_OCEAN_BOAT && IsPlayerInRangeOfPoint(playerid, 65.55, __g_FishingLoc[x][Pos][0], __g_FishingLoc[x][Pos][1], __g_FishingLoc[x][Pos][2]) && GetPlayerVirtualWorld(playerid) == 0 && GetPlayerInterior(playerid) == 0)
//         {
//             return x;
//         }
//     }
//     return -1;
// }

// GetFishTypeName(typefish)
// {
//     new str[64];
//     switch(typefish)
//     {
//         case AREA_TYPE_OCEAN, AREA_TYPE_OCEAN_BOAT:
//         {
//             format(str, sizeof(str), "Ocean");
//         }
//         case AREA_TYPE_LAKE:
//         {
//             format(str, sizeof(str), "Lake");
//         }
//         case AREA_TYPE_RIVER:
//         {
//             format(str, sizeof(str), "River");
//         }
//     }
//     return str;
// }

// forward LoadPlayerFishes(playerid);
// public LoadPlayerFishes(playerid)
// {
//     new rows = cache_num_rows();
// 	if(rows > 0)
// 	{
// 		for(new z; z < rows; z++)
// 		{
//             cache_get_value_name_int(z, "Weight", PlayerFishes[playerid][z][Weight]);
//             cache_get_value_name_int(z, "Type", PlayerFishes[playerid][z][Type]);
//         }
//     }
//     return 1;
// }

// forward FishingFunc(playerid);
// public FishingFunc(playerid)
// {
//     if(!PlayerHasItem(playerid, "Pancingan"))
//     {
//         PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
//         IsPlayerFishing[playerid] = false;
//         ClearAnimations(playerid, true);
//         StopLoopingAnim(playerid);
//         SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
//         RemovePlayerAttachedObject(playerid, 9);

//         FishingButton[playerid] = BUTTON_NONE;
//         return SEM(playerid, "You don't have a Pancingan!");
//     }

//     new x = AccountData[playerid][pInFishingArea];
//     if(!IsPlayerInRangeOfPoint(playerid, 3.0, __g_FishingLoc[x][Pos][0], __g_FishingLoc[x][Pos][1], __g_FishingLoc[x][Pos][2]) && !IsPlayerInFishZone(playerid))
//     {
//         PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
//         IsPlayerFishing[playerid] = false;
//         ClearAnimations(playerid, true);
//         StopLoopingAnim(playerid);
//         SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
//         RemovePlayerAttachedObject(playerid, 9);

//         FishingButton[playerid] = BUTTON_NONE;
//         return SEM(playerid, "You are not at the fishing spot before!");
//     }

//     new randbutton = RandomEx(1, 53);
//     switch(randbutton)
//     {
//         case 1.. 9: //BUTTON_ALT
//         {
//             FishingButton[playerid] = BUTTON_ALT;
//             SendClientMessage(playerid, X11_LIGHTBLUE, "MANCING: "WHITE"Umpan anda bergerak, tekan "YELLOW"'ALT' "WHITE"untuk strike.");
//         }
//         case 10.. 20: //BUTTON_F
//         {
//             FishingButton[playerid] = BUTTON_F;
//             SendClientMessage(playerid, X11_LIGHTBLUE, "MANCING: "WHITE"Umpan anda bergerak, tekan "YELLOW"'F' "WHITE"untuk strike.");
//         }
//         case 21.. 31: //BUTTON_H
//         {
//             FishingButton[playerid] = BUTTON_H;
//             SendClientMessage(playerid, X11_LIGHTBLUE, "MANCING: "WHITE"Umpan anda bergerak, tekan "YELLOW"'H' "WHITE"untuk strike.");
//         }
//         case 32.. 42: //BUTTON_Y
//         {
//             FishingButton[playerid] = BUTTON_Y;
//             SendClientMessage(playerid, X11_LIGHTBLUE, "MANCING: "WHITE"Umpan anda bergerak, tekan "YELLOW"'Y' "WHITE"untuk strike.");
//         }
//         case 43.. 53: //BUTTON_N
//         {
//             FishingButton[playerid] = BUTTON_N;
//             SendClientMessage(playerid, X11_LIGHTBLUE, "MANCING: "WHITE"Umpan anda bergerak, tekan "YELLOW"'N' "WHITE"untuk strike.");
//         }
//     }
//     return 1;
// }

// hook OnGameModeInit()
// {
//     for(new x; x < sizeof(__g_FishingLoc); x++)
//     {
//         if(__g_FishingLoc[x][Type] != AREA_TYPE_OCEAN)
//         {
//             FishingArea[x] = CreateDynamicSphere(__g_FishingLoc[x][Pos][0], __g_FishingLoc[x][Pos][1], __g_FishingLoc[x][Pos][2], 65.55, 0, 0, -1);

//             new rand = random(3);
//             __g_FishingLoc[x][Density] = rand;
//         }
//     }
//     return 1;
// }

// hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
// {
//     if(FishingButton[playerid] == BUTTON_ALT)
//     {
//         if(newkeys & KEY_WALK && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
//         {
//             new randresult = Random(111);

//             IsPlayerFishing[playerid] = false;
//             ClearAnimations(playerid, true);
//             StopLoopingAnim(playerid);
//             SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
//             RemovePlayerAttachedObject(playerid, 9);

//             FishingButton[playerid] = BUTTON_NONE;
//             switch(randresult)
//             {
//                 case 0.. 4: //sempak nenek
//                 {
//                     SendClientMessage(playerid, X11_LIGHTBLUE, "MANCING: "WHITE"Zonk, anda mendapatkan "CYAN"sempak nenek-nenek.");
//                 }
//                 case 5.. 9: //kondom bocor
//                 {
//                     SendClientMessage(playerid, X11_LIGHTBLUE, "MANCING: "WHITE"Zonk, anda mendapatkan "CYAN"kondom bocor.");
//                 }
//                 case 10.. 110: //ikan
//                 {
//                     AccountData[playerid][pStress] -= 2;

//                     ShowItemBox(playerid, "Ikan", "Received 1x", 19630, 5);
//                     GivePlayerFish(playerid, AccountData[playerid][pInFishingArea]);
//                 }
//             }
//         }
//         else if(newkeys != KEY_WALK)
//         {
//             IsPlayerFishing[playerid] = false;
//             ClearAnimations(playerid, true);
//             StopLoopingAnim(playerid);
//             SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
//             RemovePlayerAttachedObject(playerid, 9);
//             FishingButton[playerid] = BUTTON_NONE;
//             SendClientMessage(playerid, -1, "Anda menekan tombol yang salah dan ikan terlepas!");
//         }
//     }
//     if(FishingButton[playerid] == BUTTON_F)
//     {
//         if(newkeys & KEY_SECONDARY_ATTACK && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
//         {
//             new randresult = Random(111);

//             IsPlayerFishing[playerid] = false;
//             ClearAnimations(playerid, true);
//             StopLoopingAnim(playerid);
//             SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
//             RemovePlayerAttachedObject(playerid, 9);

//             FishingButton[playerid] = BUTTON_NONE;
//             switch(randresult)
//             {
//                 case 0.. 4: //sempak nenek
//                 {
//                     SendClientMessage(playerid, X11_LIGHTBLUE, "MANCING: "WHITE"Zonk, anda mendapatkan "CYAN"sempak nenek-nenek.");
//                 }
//                 case 5.. 9: //kondom bocor
//                 {
//                     SendClientMessage(playerid, X11_LIGHTBLUE, "MANCING: "WHITE"Zonk, anda mendapatkan "CYAN"kondom bocor.");
//                 }
//                 case 10.. 110: //ikan
//                 {
//                     AccountData[playerid][pStress] -= 2;

//                     ShowItemBox(playerid, "Ikan", "Received 1x", 19630, 5);
//                     GivePlayerFish(playerid, AccountData[playerid][pInFishingArea]);
//                 }
//             }
//         }
//         else if(newkeys != KEY_SECONDARY_ATTACK)
//         {
//             IsPlayerFishing[playerid] = false;
//             ClearAnimations(playerid, true);
//             StopLoopingAnim(playerid);
//             SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
//             RemovePlayerAttachedObject(playerid, 9);
//             FishingButton[playerid] = BUTTON_NONE;
//             SendClientMessage(playerid, -1, "Anda menekan tombol yang salah dan ikan terlepas!");
//         }
//     }
//     if(FishingButton[playerid] == BUTTON_H)
//     {
//         if(newkeys & KEY_CTRL_BACK && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
//         {
//             new randresult = Random(111);

//             IsPlayerFishing[playerid] = false;
//             ClearAnimations(playerid, true);
//             StopLoopingAnim(playerid);
//             SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
//             RemovePlayerAttachedObject(playerid, 9);

//             FishingButton[playerid] = BUTTON_NONE;
//             switch(randresult)
//             {
//                 case 0.. 4: //sempak nenek
//                 {
//                     SendClientMessage(playerid, X11_LIGHTBLUE, "MANCING: "WHITE"Zonk, anda mendapatkan "CYAN"sempak nenek-nenek.");
//                 }
//                 case 5.. 9: //kondom bocor
//                 {
//                     SendClientMessage(playerid, X11_LIGHTBLUE, "MANCING: "WHITE"Zonk, anda mendapatkan "CYAN"kondom bocor.");
//                 }
//                 case 10.. 110: //ikan
//                 {
//                     AccountData[playerid][pStress] -= 2;

//                     ShowItemBox(playerid, "Ikan", "Received 1x", 19630, 5);
//                     GivePlayerFish(playerid, AccountData[playerid][pInFishingArea]);
//                 }
//             }
//         }
//         else if(newkeys != KEY_CTRL_BACK)
//         {
//             IsPlayerFishing[playerid] = false;
//             ClearAnimations(playerid, true);
//             StopLoopingAnim(playerid);
//             SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
//             RemovePlayerAttachedObject(playerid, 9);
//             FishingButton[playerid] = BUTTON_NONE;
//             SendClientMessage(playerid, -1, "Anda menekan tombol yang salah dan ikan terlepas!");
//         }
//     }
//     if(FishingButton[playerid] == BUTTON_Y)
//     {
//         if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
//         {
//             new randresult = Random(111);

//             IsPlayerFishing[playerid] = false;
//             ClearAnimations(playerid, true);
//             StopLoopingAnim(playerid);
//             SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
//             RemovePlayerAttachedObject(playerid, 9);

//             FishingButton[playerid] = BUTTON_NONE;
//             switch(randresult)
//             {
//                 case 0.. 4: //sempak nenek
//                 {
//                     SendClientMessage(playerid, X11_LIGHTBLUE, "MANCING: "WHITE"Zonk, anda mendapatkan "CYAN"sempak nenek-nenek.");
//                 }
//                 case 5.. 9: //kondom bocor
//                 {
//                     SendClientMessage(playerid, X11_LIGHTBLUE, "FISHING: "WHITE"Zonk, anda mendapatkan "CYAN"kondom bocor.");
//                 }
//                 case 10.. 110: //ikan
//                 {
//                     AccountData[playerid][pStress] -= 2;

//                     ShowItemBox(playerid, "Ikan", "Received 1x", 19630, 5);
//                     GivePlayerFish(playerid, AccountData[playerid][pInFishingArea]);
//                 }
//             }
//         }
//         else if(newkeys != KEY_YES)
//         {
//             IsPlayerFishing[playerid] = false;
//             ClearAnimations(playerid, true);
//             StopLoopingAnim(playerid);
//             SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
//             RemovePlayerAttachedObject(playerid, 9);
//             FishingButton[playerid] = BUTTON_NONE;
//             SendClientMessage(playerid, -1, "Anda menekan tombol yang salah dan ikan terlepas!");
//         }
//     }
//     if(FishingButton[playerid] == BUTTON_N)
//     {
//         if(newkeys & KEY_NO && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
//         {
//             new randresult = Random(111);

//             ClearAnimations(playerid, true);
//             StopLoopingAnim(playerid);
//             SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
//             RemovePlayerAttachedObject(playerid, 9);

//             FishingButton[playerid] = BUTTON_NONE;
//             switch(randresult)
//             {
//                 case 0.. 4: //sempak nenek
//                 {
//                     SendClientMessage(playerid, X11_LIGHTBLUE, "MANCING: "WHITE"Zonk, anda mendapatkan "CYAN"sempak nenek-nenek.");
//                 }
//                 case 5.. 9: //kondom bocor
//                 {
//                     SendClientMessage(playerid, X11_LIGHTBLUE, "MANCING: "WHITE"Zonk, anda mendapatkan "CYAN"kondom bocor.");
//                 }
//                 case 10.. 110: //ikan
//                 {
//                     AccountData[playerid][pStress] -= 2;
                    
//                     ShowItemBox(playerid, "Ikan", "Received 1x", 19630, 5);
//                     GivePlayerFish(playerid, AccountData[playerid][pInFishingArea]);
//                 }
//             }
//             IsPlayerFishing[playerid] = false;
//         }
//         else if(newkeys != KEY_NO)
//         {
//             IsPlayerFishing[playerid] = false;
//             ClearAnimations(playerid, true);
//             StopLoopingAnim(playerid);
//             SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
//             RemovePlayerAttachedObject(playerid, 9);
//             FishingButton[playerid] = BUTTON_NONE;
//             SendClientMessage(playerid, -1, "Anda menekan tombol yang salah dan ikan terlepas!");
//         }
//     }
//     return 1;
// }

// hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
// {
//     if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && IsABoat(SavingVehID[playerid]))
//     {
//         for(new x; x < sizeof(__g_FishingLoc); x++)
//         {
//             if(__g_FishingLoc[x][Type] != AREA_TYPE_OCEAN)
//             {
//                 if(areaid == FishingArea[x])
//                 {
//                     new string[144];

//                     if(__g_FishingLoc[x][Density] == AREA_DENSITY_LOW)
// 					{
//                         format(string, sizeof(string), "~w~Boat Fishing Zone~n~Type: ~b~%s~n~~w~Density: ~r~Low", GetFishTypeName(__g_FishingLoc[x][Type]));
//                     }
//                     if(__g_FishingLoc[x][Density] == AREA_DENSITY_MEDIUM)
// 					{
//                         format(string, sizeof(string), "~w~Boat Fishing Zone~n~Type: ~b~%s~n~~w~Density: ~y~Medium", GetFishTypeName(__g_FishingLoc[x][Type]));
//                     }
//                     if(__g_FishingLoc[x][Density] == AREA_DENSITY_HIGH)
// 					{
//                         format(string, sizeof(string), "~w~Boat Fishing Zone~n~Type: ~b~%s~n~~w~Density: ~g~High", GetFishTypeName(__g_FishingLoc[x][Type]));
//                     }
//                     PlayerTextDrawSetString(playerid, FooterTD[playerid], string);
//                     PlayerTextDrawShow(playerid, FooterTD[playerid]);
//                 }
//             }
//         }
//     }
//     return 1;
// }

// hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
// {
//     for(new x; x < sizeof(__g_FishingLoc); x++)
//     {
//         if(__g_FishingLoc[x][Type] != AREA_TYPE_OCEAN)
//         {
//             if(areaid == FishingArea[x])
//             {
//                 PlayerTextDrawHide(playerid, FooterTD[playerid]);
//             }
//         }
//     }
//     return 1;
// }

// GivePlayerFish(playerid, idfisharea)
// {
//     new randweight;

//     switch(__g_FishingLoc[idfisharea][Type])
//     {
//         case AREA_TYPE_OCEAN:
//         {
//             randweight = RandomEx(10, 20);
//         }
//         case AREA_TYPE_OCEAN_BOAT.. AREA_TYPE_RIVER:
//         {
//             switch(__g_FishingLoc[idfisharea][Density])
//             {
//                 case AREA_DENSITY_LOW:
//                 {
//                     randweight = RandomEx(15, 25);
//                 }
//                 case AREA_DENSITY_MEDIUM:
//                 {
//                     randweight = RandomEx(25, 35);
//                 }
//                 case AREA_DENSITY_HIGH:
//                 {
//                     randweight = RandomEx(35, 45);
//                 }
//             }
//         }
//     }

//     //LV 2 - 3: 225
//     //LV 3 - 4: 360
//     //LV 4 - 5: 525
//     switch(AccountData[playerid][pFishingSkill])
//     {
//         case 2:
//         {
//             randweight += RandomEx(10, 20);
//         }
//         case 3:
//         {
//             randweight += RandomEx(20, 30);
//         }
//         case 4:
//         {
//             randweight += RandomEx(30, 40);
//         }
//         case 5:
//         {
//             randweight += RandomEx(40, 50);
//         }
//     }

//     SendClientMessageEx(playerid, X11_LIGHTBLUE, "MANCING: "WHITE"Anda telah mendapatkan "CYAN"%s Fish, weight: %doz.", GetFishTypeName(__g_FishingLoc[idfisharea][Type]), randweight);

//     for(new x; x < 5; x++)
//     {
//         if(PlayerFishes[playerid][x][Weight] == 0)
//         {
//             PlayerFishes[playerid][x][Weight] = randweight;
//             PlayerFishes[playerid][x][Type] = (__g_FishingLoc[idfisharea][Type] == AREA_TYPE_OCEAN_BOAT) ? (AREA_TYPE_OCEAN) : (__g_FishingLoc[idfisharea][Type]);
//             break;
//         }
//     }

//     new sqlstring[168];
//     mysql_format(g_SQL, sqlstring, sizeof(sqlstring), "INSERT INTO `player_fishes` (`Owner`, `Weight`, `Type`) VALUES (%d, %d, %d)", AccountData[playerid][pID], randweight, (__g_FishingLoc[idfisharea][Type] == AREA_TYPE_OCEAN_BOAT) ? (AREA_TYPE_OCEAN) : (__g_FishingLoc[idfisharea][Type]));
//     mysql_pquery(g_SQL, sqlstring);
    
//     AccountData[playerid][pTempValue2] = -1;
//     return 1;
// }
