#define MAX_ROBBERY 50

new g_MarketRobberyCooldown;

enum e_RobberyDetails
{
    robberySkin,
    Float:robberyPos[4],
    robberyWorld,
    robberyInterior,

    //not save
    bool:robberyHandsup,
    bool:robberyAfraid,
    bool:robberyRobbed,
    robberyAimTime,
    robberyTime,
    STREAMER_TAG_ACTOR:robberyActor,
    STREAMER_TAG_3D_TEXT_LABEL:robberyGlobalLabel,
};
new RobberyData[MAX_ROBBERY][e_RobberyDetails],
    Iterator:Robberies<MAX_ROBBERY>;

Robbery_Nearest(playerid)
{
    foreach(new i : Robberies) if (IsPlayerInRangeOfPoint(playerid, 3.0, RobberyData[i][robberyPos][0], RobberyData[i][robberyPos][1], RobberyData[i][robberyPos][2]) && IsValidDynamicActor(RobberyData[i][robberyActor]))
	{
		if (GetPlayerInterior(playerid) == RobberyData[i][robberyInterior] && GetPlayerVirtualWorld(playerid) == RobberyData[i][robberyWorld])
			return i;
	}
	return -1;
}

Robbery_Save(robberyid)
{
    new rbrstr[522];
    mysql_format(g_SQL, rbrstr, sizeof(rbrstr), "UPDATE `robberies` SET `Robbery_Skin`=%d, `Robbery_X`='%f', `Robbery_Y`='%f', `Robbery_Z`='%f', `Robbery_A`='%f', \
    `Robbery_World`=%d, `Robbery_Interior`=%d WHERE `ID`=%d", RobberyData[robberyid][robberyActor], RobberyData[robberyid][robberyPos][0], RobberyData[robberyid][robberyPos][1], RobberyData[robberyid][robberyPos][2],
    RobberyData[robberyid][robberyPos][3], RobberyData[robberyid][robberyWorld], RobberyData[robberyid][robberyInterior], robberyid);
    return 1;
}

Robbery_Refresh(robberyid)
{
    if(robberyid != -1)
    {
        Streamer_SetIntData(STREAMER_TYPE_ACTOR, RobberyData[robberyid][robberyActor], E_STREAMER_MODEL_ID, RobberyData[robberyid][robberySkin]);

        SetDynamicActorPos(RobberyData[robberyid][robberyActor], RobberyData[robberyid][robberyPos][0], RobberyData[robberyid][robberyPos][1], RobberyData[robberyid][robberyPos][2]);
        SetDynamicActorFacingAngle(RobberyData[robberyid][robberyActor], RobberyData[robberyid][robberyPos][3]);
        SetDynamicActorVirtualWorld(RobberyData[robberyid][robberyActor], RobberyData[robberyid][robberyWorld]);
        Streamer_SetIntData(STREAMER_TYPE_ACTOR, RobberyData[robberyid][robberyActor], E_STREAMER_INTERIOR_ID, RobberyData[robberyid][robberyInterior]);
    }
    return 1;
}

Robbery_Rebuild(robberyid)
{
    if(robberyid != -1)
    {
        RobberyData[robberyid][robberyActor] = CreateDynamicActor(RobberyData[robberyid][robberySkin], RobberyData[robberyid][robberyPos][0], RobberyData[robberyid][robberyPos][1], RobberyData[robberyid][robberyPos][2], RobberyData[robberyid][robberyPos][3], 1, 100.0, RobberyData[robberyid][robberyWorld], RobberyData[robberyid][robberyInterior], -1, 300.00, -1, 0);
        RobberyData[robberyid][robberyRobbed] = false;
        RobberyData[robberyid][robberyHandsup] = false;
        RobberyData[robberyid][robberyAimTime] = -1;
        RobberyData[robberyid][robberyTime] = 0;

        g_MarketRobberyCooldown = 0;
        Robbery_Refresh(robberyid);
    }
    return 1;
}

forward OnRobberyCreated(playerid, robberyid);
public OnRobberyCreated(playerid, robberyid)
{
    Robbery_Save(robberyid);

    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s membuat Robbery dengan ID: %d.", AccountData[playerid][pAdminname], robberyid);
    return 1;
}

forward LoadRobberies();
public LoadRobberies()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
 		new robberyid;
		for(new i; i < rows; i++)
		{
            cache_get_value_name_int(i, "ID", robberyid);
            cache_get_value_name_int(i, "Robbery_Skin", RobberyData[robberyid][robberySkin]);
            cache_get_value_name_float(i, "Robbery_X", RobberyData[robberyid][robberyPos][0]);
            cache_get_value_name_float(i, "Robbery_Y", RobberyData[robberyid][robberyPos][1]);
            cache_get_value_name_float(i, "Robbery_Z", RobberyData[robberyid][robberyPos][2]);
            cache_get_value_name_float(i, "Robbery_A", RobberyData[robberyid][robberyPos][3]);
            cache_get_value_name_int(i, "Robbery_World", RobberyData[robberyid][robberyWorld]);
            cache_get_value_name_int(i, "Robbery_Interior", RobberyData[robberyid][robberyInterior]);
            
			Robbery_Rebuild(robberyid);
			Iter_Add(Robberies, robberyid);
        }
        printf("[Dynamic Robberies] Jumlah total Robberies yang dimuat: %d.", rows);
	}
}

forward RobbingAnimationAfterReact(robberyid);
public RobbingAnimationAfterReact(robberyid)
{
    ApplyDynamicActorAnimation(RobberyData[robberyid][robberyActor], "SHOP", "SHP_Rob_HandsUp",2.67,0,0,0,0,0);
}

forward RobbingAnimationFinished(robberyid);
public RobbingAnimationFinished(robberyid)
{
    ApplyDynamicActorAnimation(RobberyData[robberyid][robberyActor], "PED", "IDLE_stance", 1.50, 1, 0, 0, 0, 0);
}

//new
ptask CheckingPlayerAimRobbery[1000](playerid) 
{
    if(IsPlayerConnected(playerid) && AccountData[playerid][IsLoggedIn] && AccountData[playerid][pSpawned])
    {
        if(!AccountData[playerid][pDuringRobbery])
        {
            foreach(new robberyid : Robberies)
            {
                if(IsPlayerInRangeOfPoint(playerid, 3.0, RobberyData[robberyid][robberyPos][0], RobberyData[robberyid][robberyPos][1], RobberyData[robberyid][robberyPos][2]))
                {
                    if(GetPlayerTargetDynamicActor(playerid) == RobberyData[robberyid][robberyActor]) //jika dia aim ke robbery actor
                    {
                        if(GetPlayerWeaponEx(playerid) >= 22 && GetPlayerWeaponEx(playerid) <= 42)
                        {
                            if(!RobberyData[robberyid][robberyRobbed])
                            {
                                if(!RobberyData[robberyid][robberyHandsup] && !RobberyData[robberyid][robberyAfraid])
                                {
                                    if(g_MarketRobberyCooldown == 0)
                                    {
                                        ApplyDynamicActorAnimation(RobberyData[robberyid][robberyActor], "SHOP", "SHP_Rob_React", 2.67, 0, 0, 0, 0, 0);
                                        SetTimerEx("RobbingAnimationAfterReact", 2670, false, "i", robberyid);

                                        RobberyData[robberyid][robberyHandsup] = true;
                                        RobberyData[robberyid][robberyAimTime] = 0;

                                        AccountData[playerid][pDuringRobbery] = true;
                                        AccountData[playerid][pInRobberyID] = robberyid;

                                        new rbrystr[255];
                                        format(rbrystr, sizeof(rbrystr), ""LIGHTGREEN"Penjaga: "WHITE"Jangan sakiti aku tuan, aku akan memberikanmu uangnya.\n\
                                        "YELLOW"Pengancaman: "WHITE"[%d%%]", RobberyData[robberyid][robberyAimTime]);
                                        AccountData[playerid][pRobberyLabel] = CreateDynamic3DTextLabel(rbrystr, Y_WHITE, RobberyData[robberyid][robberyPos][0], RobberyData[robberyid][robberyPos][1], RobberyData[robberyid][robberyPos][2]+1.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, RobberyData[robberyid][robberyWorld], RobberyData[robberyid][robberyInterior], playerid, 10.0, -1, 0);
                                        Streamer_Update(playerid, STREAMER_TYPE_3D_TEXT_LABEL);
                                    }
                                }
                            }
                            else
                            {
                                ApplyDynamicActorAnimation(RobberyData[robberyid][robberyActor], "SHOP", "SHP_Rob_React", 2.67, 0, 0, 0, 0, 0);
                                SetTimerEx("RobbingAnimationFinished", 2670, false, "i", robberyid);

                                new rbrystr[255];
                                format(rbrystr, sizeof(rbrystr), ""LIGHTGREEN"Penjaga: "WHITE"Tidak! Kumohon jangan lakukan itu, saat ini aku tidak punya uang lagi karena seseorang telah merampok warungku.\n\
                                "YELLOW"Cooldown: "WHITE"%d menit", g_MarketRobberyCooldown/60);
                                AccountData[playerid][pRobberyLabel] = CreateDynamic3DTextLabel(rbrystr, Y_WHITE, RobberyData[robberyid][robberyPos][0], RobberyData[robberyid][robberyPos][1], RobberyData[robberyid][robberyPos][2]+1.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, RobberyData[robberyid][robberyWorld], RobberyData[robberyid][robberyInterior], playerid, 10.0, -1, 0);
                                Streamer_Update(playerid, STREAMER_TYPE_3D_TEXT_LABEL);
                            }
                        }
                    }
                    else
                    {
                        RobberyData[robberyid][robberyHandsup] = false;
                        RobberyData[robberyid][robberyAimTime] = -1;
                        AccountData[playerid][pDuringRobbery] = false;
                        AccountData[playerid][pInRobberyID] = -1;

                        CallLocalFunction("RobbingAnimationFinished", "i", robberyid);

                        if(DestroyDynamic3DTextLabel(AccountData[playerid][pRobberyLabel]))
                        {
                            AccountData[playerid][pRobberyLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
                        }
                    }
                }
            }
        }
    }
    return 1;
}

ptask UpdatingRobberyAimTime[1000](playerid) 
{
    if(IsPlayerConnected(playerid) && AccountData[playerid][IsLoggedIn] && AccountData[playerid][pSpawned] && AccountData[playerid][pDuringRobbery])
    {
        new robberyid = AccountData[playerid][pInRobberyID];

        if(robberyid != -1)
        {
            if(RobberyData[robberyid][robberyHandsup])
            {
                if(IsPlayerInRangeOfPoint(playerid, 3.0, RobberyData[robberyid][robberyPos][0], RobberyData[robberyid][robberyPos][1], RobberyData[robberyid][robberyPos][2]))
                {
                    if(GetPlayerTargetDynamicActor(playerid) == RobberyData[robberyid][robberyActor]) //jika dia aim ke robbery actor
                    {
                        if(GetPlayerWeaponEx(playerid) >= 22 && GetPlayerWeaponEx(playerid) <= 42)
                        {
                            if(!RobberyData[robberyid][robberyAfraid])
                            {
                                if(RobberyData[robberyid][robberyAimTime] >= 0 && RobberyData[robberyid][robberyAimTime] < 100)
                                {
                                    RobberyData[robberyid][robberyAimTime] += 5;

                                    new rbrystr[255];
                                    format(rbrystr, sizeof(rbrystr), ""LIGHTGREEN"Penjaga: "WHITE"Jangan sakiti aku tuan, aku akan memberikanmu uangnya.\n\
                                    "YELLOW"Pengancaman: "WHITE"[%d%%]", RobberyData[robberyid][robberyAimTime]);
                                    UpdateDynamic3DTextLabelText(AccountData[playerid][pRobberyLabel], Y_WHITE, rbrystr);
                                }
                                
                                if(RobberyData[robberyid][robberyAimTime] >= 100)
                                {
                                    RobberyData[robberyid][robberyHandsup] = false;
                                    RobberyData[robberyid][robberyAimTime] = -1;
                                    RobberyData[robberyid][robberyAfraid] = true;
                                    RobberyData[robberyid][robberyTime] = 600;

                                    ShowFivemNotify(playerid, "Pahlawan Roleplay~n~PERAMPOKAN WARUNG", "Telah terjadi perampokan warung di Mulholland Intersection.", "hud:radar_emmetGun", 25);
                                }
                            }
                        }
                    }
                    else
                    {
                        RobberyData[robberyid][robberyHandsup] = false;
                        RobberyData[robberyid][robberyAimTime] = -1;
                        AccountData[playerid][pDuringRobbery] = false;
                        AccountData[playerid][pInRobberyID] = -1;

                        CallLocalFunction("RobbingAnimationFinished", "i", robberyid);

                        if(DestroyDynamic3DTextLabel(AccountData[playerid][pRobberyLabel]))
                        {
                            AccountData[playerid][pRobberyLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
                        }
                    }
                }
                else
                {
                    RobberyData[robberyid][robberyHandsup] = false;
                    RobberyData[robberyid][robberyAimTime] = -1;
                    AccountData[playerid][pDuringRobbery] = false;
                    AccountData[playerid][pInRobberyID] = -1;

                    CallLocalFunction("RobbingAnimationFinished", "i", robberyid);

                    if(DestroyDynamic3DTextLabel(AccountData[playerid][pRobberyLabel]))
                    {
                        AccountData[playerid][pRobberyLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
                    }
                }
            }
        }
    }
    return 1;
}

ptask UpdatingRobberyTime[1000](playerid) 
{
    if(IsPlayerConnected(playerid) && AccountData[playerid][IsLoggedIn] && AccountData[playerid][pSpawned] && AccountData[playerid][pDuringRobbery])
    {
        new robberyid = AccountData[playerid][pInRobberyID];

        if(robberyid != -1)
        {
            if(!RobberyData[robberyid][robberyHandsup])
            {
                if(RobberyData[robberyid][robberyAfraid])
                {
                    if(IsPlayerInRangeOfPoint(playerid, 25.0, RobberyData[robberyid][robberyPos][0], RobberyData[robberyid][robberyPos][1], RobberyData[robberyid][robberyPos][2]))
                    {
                        if(RobberyData[robberyid][robberyTime] > 0)
                        {
                            RobberyData[robberyid][robberyTime]--;

                            new rbrystr[255];
                            format(rbrystr, sizeof(rbrystr), ""LIGHTGREEN"Penjaga: "WHITE"Mohon bersabar aku akan terus berusaha membuka brankas ini.\n\
                            "YELLOW"Perampokan: "WHITE"%02d menit %02d detik", RobberyData[robberyid][robberyTime] / 60 % 60, RobberyData[robberyid][robberyTime] % 3600 % 60);
                            UpdateDynamic3DTextLabelText(AccountData[playerid][pRobberyLabel], Y_WHITE, rbrystr);
                        }
                        else
                        {
                            ApplyDynamicActorAnimation(RobberyData[robberyid][robberyActor], "SHOP", "SHP_Rob_GiveCash",3.83,0,0,0,1,0);
                            SetTimerEx("RobbingAnimationFinished", 3830, false, "i", robberyid);

                            RobberyData[robberyid][robberyAfraid] = false;
                            RobberyData[robberyid][robberyTime] = 0;

                            AccountData[playerid][pDuringRobbery] = false;
                            AccountData[playerid][pInRobberyID] = -1;

                            g_MarketRobberyCooldown = 3600;
                            RobberyData[robberyid][robberyRobbed] = true;

                            new rbrystr[255];
                            foreach(new xid : Robberies)
                            {
                                format(rbrystr, sizeof(rbrystr), ""YELLOW"Cooldown: "WHITE"%d menit %02d detik", g_MarketRobberyCooldown/60, g_MarketRobberyCooldown  % 3600 % 60);
                                RobberyData[xid][robberyGlobalLabel] = CreateDynamic3DTextLabel(rbrystr, Y_WHITE, RobberyData[xid][robberyPos][0], RobberyData[xid][robberyPos][1], RobberyData[xid][robberyPos][2], 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, RobberyData[xid][robberyWorld], RobberyData[xid][robberyInterior], -1, 10.0, -1, 0);
                                Streamer_Update(playerid, STREAMER_TYPE_3D_TEXT_LABEL);
                            }

                            if(DestroyDynamic3DTextLabel(AccountData[playerid][pRobberyLabel]))
                            {
                                AccountData[playerid][pRobberyLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
                            }

                            new randcash = RandomEx(500, 1000);
                            GivePlayerMoneyEx(playerid, randcash);
                        }
                    }
                    else
                    {
                        RobberyData[robberyid][robberyAfraid] = false;
                        RobberyData[robberyid][robberyTime] = 0;
                        AccountData[playerid][pDuringRobbery] = false;
                        AccountData[playerid][pInRobberyID] = -1;

                        CallLocalFunction("RobbingAnimationFinished", "i", robberyid);

                        if(DestroyDynamic3DTextLabel(AccountData[playerid][pRobberyLabel]))
                        {
                            AccountData[playerid][pRobberyLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
                        }
                    }
                }
            }
        }
    }
    return 1;
}

task RobberyCooldownUpdater[1000]() 
{
    foreach(new xid : Robberies)
    {
        if(RobberyData[xid][robberyRobbed])
        {
            if(g_MarketRobberyCooldown > 0)
            {
                g_MarketRobberyCooldown--;
                
                new rbrystr[255];
                format(rbrystr, sizeof(rbrystr), ""YELLOW"Cooldown: "WHITE"%d menit %02d detik", g_MarketRobberyCooldown/60, g_MarketRobberyCooldown  % 3600 % 60);
                UpdateDynamic3DTextLabelText(RobberyData[xid][robberyGlobalLabel], Y_WHITE, rbrystr);
            }
            else
            {
                g_MarketRobberyCooldown = 0;
                RobberyData[xid][robberyRobbed] = false;

                if(DestroyDynamic3DTextLabel(RobberyData[xid][robberyGlobalLabel]))
                {
                    RobberyData[xid][robberyGlobalLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
                }
            }
        }
    }
    return 1;
}