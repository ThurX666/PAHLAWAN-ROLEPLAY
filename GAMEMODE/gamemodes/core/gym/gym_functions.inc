#include <YSI_Coding\y_hooks>

new Text:GYM_UI[2],
    PlayerText:PGYM_UI[MAX_PLAYERS];

CreateGYMTD()
{
    GYM_UI[0] = TextDrawCreate(12.000000, 238.000000, "[Y] ~w~untuk latihan");
	TextDrawFont(GYM_UI[0], 1);
	TextDrawLetterSize(GYM_UI[0], 0.180000, 1.100000);
	TextDrawTextSize(GYM_UI[0], 95.000000, 17.000000);
	TextDrawSetOutline(GYM_UI[0], 1);
	TextDrawSetShadow(GYM_UI[0], 0);
	TextDrawAlignment(GYM_UI[0], 1);
	TextDrawColor(GYM_UI[0], 16711935);
	TextDrawBackgroundColor(GYM_UI[0], 255);
	TextDrawBoxColor(GYM_UI[0], 50);
	TextDrawUseBox(GYM_UI[0], 0);
	TextDrawSetProportional(GYM_UI[0], 1);
	TextDrawSetSelectable(GYM_UI[0], 0);

	GYM_UI[1] = TextDrawCreate(12.000000, 252.000000, "[H] ~w~untuk berhenti");
	TextDrawFont(GYM_UI[1], 1);
	TextDrawLetterSize(GYM_UI[1], 0.180000, 1.100000);
	TextDrawTextSize(GYM_UI[1], 95.000000, 17.000000);
	TextDrawSetOutline(GYM_UI[1], 1);
	TextDrawSetShadow(GYM_UI[1], 0);
	TextDrawAlignment(GYM_UI[1], 1);
	TextDrawColor(GYM_UI[1], 0xFF0000FF);
	TextDrawBackgroundColor(GYM_UI[1], 255);
	TextDrawBoxColor(GYM_UI[1], 50);
	TextDrawUseBox(GYM_UI[1], 0);
	TextDrawSetProportional(GYM_UI[1], 1);
	TextDrawSetSelectable(GYM_UI[1], 0);
}

new Float:__g_GYMFreeWeight[][4] =
{
    {1350.6689,-2031.8840,55.3304,90.2666},
    {1350.6689,-2028.2471,55.3304,90.2666},
    {1378.2278,-2024.0217,55.3204,270.0982},
    {1378.2274,-2020.3333,55.3204,268.8448},
    {2009.2285,-1245.7783,23.9922,90.1004} //taman
};

new Float:__g_GYMYoga[][4] =
{
    {1354.4274,-2031.6053,55.3360,359.3756},
    {1361.1313,-2031.4590,55.3360,359.3756},
    {1367.4861,-2031.2742,55.3360,357.8089},
    {1374.2213,-2031.6552,55.3360,359.0622},
    {1374.1805,-2022.4204,55.3360,178.9173},
    {1367.4633,-2022.3129,55.3360,180.7973},
    {1361.1086,-2022.4602,55.3360,178.6039},
    {1354.4130,-2022.4723,55.3360,179.5438},
    {660.1937,-1869.6359,5.5537,90.2089}, //pantai
    {654.0662,-1869.5908,5.5537,269.4139}, //pantai
    {2013.6942,-1243.4191,24.0159,357.9793}, //taman
    {2013.6475,-1247.0500,24.0159,359.2093} //taman
};

new Float:__g_GYMBike[][4] =
{
    {1358.0973,-2014.3665,55.3304,178.9896},
    {1364.7567,-2014.3439,55.3204,178.6038},
    {1371.3663,-2014.3289,55.3204,180.2429},
    {659.7966,-1863.6427,5.4609,178.9556}, //pantai
    {2012.1633,-1239.8269,23.9882,357.3530}, //taman
    {2009.4625,-1239.9189,23.9882,357.3530} //taman
};

new Float:__g_GYMBarbel[][4] =
{
    {1378.8092,-2028.3668,55.3204,269.7847},
    {1378.8148,-2031.9506,55.3204,269.7847},
    {1350.2273,-2023.8932,55.3304,89.6164},
    {1350.0779,-2020.3157,55.3304,88.6764},
    {653.9803,-1864.8209,5.4609,0.2814}, //pantai
    {2017.8519,-1247.2151,23.9932,269.5948}, //taman
    {2017.8723,-1243.1182,23.9892,270.2216} //taman
};

new g_GYMFreeWeightUsed[sizeof(__g_GYMFreeWeight)],
    g_GYMYogaUsed[sizeof(__g_GYMYoga)],
    g_GYMBikeUsed[sizeof(__g_GYMBike)],
    g_GYMBarbelUsed[sizeof(__g_GYMBarbel)];
new 
    bool:GYM_PlayerUsing[MAX_PLAYERS],
    GYM_PlayerAntiSpam[MAX_PLAYERS],
    GYM_PlayerProgress[MAX_PLAYERS],
    GYM_PlayerType[MAX_PLAYERS],
    GYM_PlayerToolID[MAX_PLAYERS];

g_GYMFreeWeight_Nearest(playerid)
{
    for(new x; x < sizeof(__g_GYMFreeWeight); x++) if (IsPlayerInRangeOfPoint(playerid, 2.0, __g_GYMFreeWeight[x][0], __g_GYMFreeWeight[x][1], __g_GYMFreeWeight[x][2]))
	{
		if (GetPlayerInterior(playerid) == 0 && GetPlayerVirtualWorld(playerid) == 0)
			return x;
	}
	return -1;
}

g_GYMYoga_Nearest(playerid)
{
    for(new x; x < sizeof(__g_GYMYoga); x++) if (IsPlayerInRangeOfPoint(playerid, 2.0, __g_GYMYoga[x][0], __g_GYMYoga[x][1], __g_GYMYoga[x][2]))
	{
		if (GetPlayerInterior(playerid) == 0 && GetPlayerVirtualWorld(playerid) == 0)
			return x;
	}
	return -1;
}
g_GYMBike_Nearest(playerid)
{
    for(new x; x < sizeof(__g_GYMBike); x++) if (IsPlayerInRangeOfPoint(playerid, 2.0, __g_GYMBike[x][0], __g_GYMBike[x][1], __g_GYMBike[x][2]))
	{
		if (GetPlayerInterior(playerid) == 0 && GetPlayerVirtualWorld(playerid) == 0)
			return x;
	}
	return -1;
}

g_GYMBarbel_Nearest(playerid)
{
    for(new x; x < sizeof(__g_GYMBarbel); x++) if (IsPlayerInRangeOfPoint(playerid, 2.0, __g_GYMBarbel[x][0], __g_GYMBarbel[x][1], __g_GYMBarbel[x][2]))
	{
		if (GetPlayerInterior(playerid) == 0 && GetPlayerVirtualWorld(playerid) == 0)
			return x;
	}
	return -1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        new id = -1;
        if((id = g_GYMFreeWeight_Nearest(playerid)) != -1)
        {
            if(!GYM_PlayerUsing[playerid])
            {
                if(g_GYMFreeWeightUsed[id]) return SEM(playerid, "Alat GYM tersebut sedang digunakan orang lain!");
                if(AccountData[playerid][pIsSmoking]) return SEM(playerid, "You are currently smoking. Finish it or use '/stopsmoke' to stop!");
		        if(AccountData[playerid][pEatingStep] > 0) return SEM(playerid, "You are currently eating. Finish it or use '/stopeating' to stop!");
		        if(AccountData[playerid][pDrinkingStep] > 0) return SEM(playerid, "You are currently drinking. Finish it or use '/stopdrinking' to stop!");

                SetPlayerPos(playerid, __g_GYMFreeWeight[id][0], __g_GYMFreeWeight[id][1], __g_GYMFreeWeight[id][2]);
                SetPlayerFacingAngle(playerid, __g_GYMFreeWeight[id][3]);

                ApplyAnimation(playerid, "Freeweights", "gym_free_B", 2.33, false, false, false, true, 0, true);
                SetPlayerAttachedObject(playerid, 9, 3071, 6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0,1.0, 0, 0);

                TextDrawShowForPlayer(playerid, GYM_UI[0]);
                TextDrawShowForPlayer(playerid, GYM_UI[1]);
                
                if(IsValidPlayerTextDraw(playerid, PGYM_UI[playerid]))
                {
                    PlayerTextDrawDestroy(playerid, PGYM_UI[playerid]);
                    PGYM_UI[playerid] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
                }

                PGYM_UI[playerid] = CreatePlayerTextDraw(playerid, 12.000000, 225.000000, "0%");
                PlayerTextDrawFont(playerid, PGYM_UI[playerid], 1);
                PlayerTextDrawLetterSize(playerid, PGYM_UI[playerid], 0.180000, 1.100000);
                PlayerTextDrawTextSize(playerid, PGYM_UI[playerid], 42.500000, 17.000000);
                PlayerTextDrawSetOutline(playerid, PGYM_UI[playerid], 1);
                PlayerTextDrawSetShadow(playerid, PGYM_UI[playerid], 0);
                PlayerTextDrawAlignment(playerid, PGYM_UI[playerid], 1);
                PlayerTextDrawColor(playerid, PGYM_UI[playerid], -16776961);
                PlayerTextDrawBackgroundColor(playerid, PGYM_UI[playerid], 255);
                PlayerTextDrawBoxColor(playerid, PGYM_UI[playerid], 50);
                PlayerTextDrawUseBox(playerid, PGYM_UI[playerid], 0);
                PlayerTextDrawSetProportional(playerid, PGYM_UI[playerid], 1);
                PlayerTextDrawSetSelectable(playerid, PGYM_UI[playerid], 0);

                PlayerTextDrawShow(playerid, PGYM_UI[playerid]);

                g_GYMFreeWeightUsed[id] = true;
                GYM_PlayerUsing[playerid] = true;
                GYM_PlayerProgress[playerid] = 0;
                GYM_PlayerType[playerid] = 1;
                GYM_PlayerToolID[playerid] = id;
            }
            else
            {
                if(AccountData[playerid][pIsSmoking]) return SEM(playerid, "You are currently smoking. Finish it or use '/stopsmoke' to stop!");
		        if(AccountData[playerid][pEatingStep] > 0) return SEM(playerid, "You are currently eating. Finish it or use '/stopeating' to stop!");
		        if(AccountData[playerid][pDrinkingStep] > 0) return SEM(playerid, "You are currently drinking. Finish it or use '/stopdrinking' to stop!");

                if (GetTickCount() - GYM_PlayerAntiSpam[playerid] < 666) return 1;

                GYM_PlayerAntiSpam[playerid] = GetTickCount();

                ApplyAnimation(playerid, "Freeweights", "gym_free_B", 2.33, false, false, false, true, 0, true);

                GYM_PlayerProgress[playerid]++;

                static string[64];
                format(string, sizeof(string), "%d%", GYM_PlayerProgress[playerid]);
                PlayerTextDrawSetString(playerid, PGYM_UI[playerid], string);
                PlayerTextDrawColor(playerid, PGYM_UI[playerid], ConvertFloatColor(float(GYM_PlayerProgress[playerid]), X11_WHITE));
                PlayerTextDrawShow(playerid, PGYM_UI[playerid]);

                if(GYM_PlayerProgress[playerid] >= 100)
                {
                    GYM_PlayerUsing[playerid] = false;
                    GYM_PlayerProgress[playerid] = 0;
                    GYM_PlayerType[playerid] = 0;
                    GYM_PlayerToolID[playerid] = -1;

                    if(IsValidPlayerTextDraw(playerid, PGYM_UI[playerid]))
                    {
                        PlayerTextDrawDestroy(playerid, PGYM_UI[playerid]);
                        PGYM_UI[playerid] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
                    }
                    TextDrawHideForPlayer(playerid, GYM_UI[0]);
                    TextDrawHideForPlayer(playerid, GYM_UI[1]);

                    RemovePlayerAttachedObject(playerid, 9);
                    StopRunningAnimation(playerid);
                    
                    if(AccountData[playerid][pVIP] != 2)
                    {
                        AccountData[playerid][pStress] -= 10;
                    }
                    else
                    {
                        AccountData[playerid][pStress] -= 15;
                    }
                    AccountData[playerid][pThirst] -= 2;
                    AccountData[playerid][pHunger] --;
                    g_GYMFreeWeightUsed[id] = false;
                }
            }
        }

        if((id = g_GYMYoga_Nearest(playerid)) != -1)
        {
            if(!GYM_PlayerUsing[playerid])
            {
                if(g_GYMYogaUsed[id]) return SEM(playerid, "Alat GYM tersebut sedang digunakan orang lain!");
                if(AccountData[playerid][pIsSmoking]) return SEM(playerid, "You are currently smoking. Finish it or use '/stopsmoke' to stop!");
		        if(AccountData[playerid][pEatingStep] > 0) return SEM(playerid, "You are currently eating. Finish it or use '/stopeating' to stop!");
		        if(AccountData[playerid][pDrinkingStep] > 0) return SEM(playerid, "You are currently drinking. Finish it or use '/stopdrinking' to stop!");

                SetPlayerPos(playerid, __g_GYMYoga[id][0], __g_GYMYoga[id][1], __g_GYMYoga[id][2]);
                SetPlayerFacingAngle(playerid, __g_GYMYoga[id][3]);

                new rand = random(2);
                if(rand == 1)
                {
                    ApplyAnimation(playerid, "PARK", "Tai_Chi_Loop", 4.1, true, false, false, false, 0, true);
                }
                else
                {
                    ApplyAnimation(playerid, "GYMNASIUM", "GYMshadowbox", 4.0, true, false, false, false, 0, true);
                }

                TextDrawShowForPlayer(playerid, GYM_UI[0]);
                TextDrawShowForPlayer(playerid, GYM_UI[1]);
                
                if(IsValidPlayerTextDraw(playerid, PGYM_UI[playerid]))
                {
                    PlayerTextDrawDestroy(playerid, PGYM_UI[playerid]);
                    PGYM_UI[playerid] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
                }

                PGYM_UI[playerid] = CreatePlayerTextDraw(playerid, 12.000000, 225.000000, "0%");
                PlayerTextDrawFont(playerid, PGYM_UI[playerid], 1);
                PlayerTextDrawLetterSize(playerid, PGYM_UI[playerid], 0.180000, 1.100000);
                PlayerTextDrawTextSize(playerid, PGYM_UI[playerid], 42.500000, 17.000000);
                PlayerTextDrawSetOutline(playerid, PGYM_UI[playerid], 1);
                PlayerTextDrawSetShadow(playerid, PGYM_UI[playerid], 0);
                PlayerTextDrawAlignment(playerid, PGYM_UI[playerid], 1);
                PlayerTextDrawColor(playerid, PGYM_UI[playerid], -16776961);
                PlayerTextDrawBackgroundColor(playerid, PGYM_UI[playerid], 255);
                PlayerTextDrawBoxColor(playerid, PGYM_UI[playerid], 50);
                PlayerTextDrawUseBox(playerid, PGYM_UI[playerid], 0);
                PlayerTextDrawSetProportional(playerid, PGYM_UI[playerid], 1);
                PlayerTextDrawSetSelectable(playerid, PGYM_UI[playerid], 0);

                PlayerTextDrawShow(playerid, PGYM_UI[playerid]);

                g_GYMYogaUsed[id] = true;
                GYM_PlayerUsing[playerid] = true;
                GYM_PlayerProgress[playerid] = 0;
                GYM_PlayerType[playerid] = 2;
                GYM_PlayerToolID[playerid] = id;
            }
            else
            {
                if(AccountData[playerid][pIsSmoking]) return SEM(playerid, "You are currently smoking. Finish it or use '/stopsmoke' to stop!");
		        if(AccountData[playerid][pEatingStep] > 0) return SEM(playerid, "You are currently eating. Finish it or use '/stopeating' to stop!");
		        if(AccountData[playerid][pDrinkingStep] > 0) return SEM(playerid, "You are currently drinking. Finish it or use '/stopdrinking' to stop!");

                if (GetTickCount() - GYM_PlayerAntiSpam[playerid] < 666) return 1;
                
                GYM_PlayerAntiSpam[playerid] = GetTickCount();

                GYM_PlayerProgress[playerid]++;

                static string[64];
                format(string, sizeof(string), "%d%", GYM_PlayerProgress[playerid]);
                PlayerTextDrawSetString(playerid, PGYM_UI[playerid], string);
                PlayerTextDrawColor(playerid, PGYM_UI[playerid], ConvertFloatColor(float(GYM_PlayerProgress[playerid]), X11_WHITE));
                PlayerTextDrawShow(playerid, PGYM_UI[playerid]);

                if(GYM_PlayerProgress[playerid] >= 100)
                {
                    GYM_PlayerUsing[playerid] = false;
                    GYM_PlayerProgress[playerid] = 0;
                    GYM_PlayerType[playerid] = 0;
                    GYM_PlayerToolID[playerid] = -1;

                    if(IsValidPlayerTextDraw(playerid, PGYM_UI[playerid]))
                    {
                        PlayerTextDrawDestroy(playerid, PGYM_UI[playerid]);
                        PGYM_UI[playerid] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
                    }
                    TextDrawHideForPlayer(playerid, GYM_UI[0]);
                    TextDrawHideForPlayer(playerid, GYM_UI[1]);

                    RemovePlayerAttachedObject(playerid, 9);
                    StopRunningAnimation(playerid);
                    
                    if(AccountData[playerid][pVIP] != 2)
                    {
                        AccountData[playerid][pStress] -= 10;
                    }
                    else
                    {
                        AccountData[playerid][pStress] -= 15;
                    }
                    AccountData[playerid][pThirst] -= 2;
                    AccountData[playerid][pHunger] --;
                    g_GYMYogaUsed[id] = false;
                }
            }
        }
        if((id = g_GYMBike_Nearest(playerid)) != -1)
        {
            if(!GYM_PlayerUsing[playerid])
            {
                if(g_GYMBikeUsed[id]) return SEM(playerid, "Alat GYM tersebut sedang digunakan orang lain!");
                if(AccountData[playerid][pIsSmoking]) return SEM(playerid, "You are currently smoking. Finish it or use '/stopsmoke' to stop!");
		        if(AccountData[playerid][pEatingStep] > 0) return SEM(playerid, "You are currently eating. Finish it or use '/stopeating' to stop!");
		        if(AccountData[playerid][pDrinkingStep] > 0) return SEM(playerid, "You are currently drinking. Finish it or use '/stopdrinking' to stop!");
                
                SetPlayerPos(playerid, __g_GYMBike[id][0], __g_GYMBike[id][1], __g_GYMBike[id][2]);
                SetPlayerFacingAngle(playerid, __g_GYMBike[id][3]);

                ApplyAnimation(playerid, "GYMNASIUM", "gym_bike_geton", 1.67, false, false, false, true, 0, true);

                TextDrawShowForPlayer(playerid, GYM_UI[0]);
                TextDrawShowForPlayer(playerid, GYM_UI[1]);
                
                if(IsValidPlayerTextDraw(playerid, PGYM_UI[playerid]))
                {
                    PlayerTextDrawDestroy(playerid, PGYM_UI[playerid]);
                    PGYM_UI[playerid] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
                }

                PGYM_UI[playerid] = CreatePlayerTextDraw(playerid, 12.000000, 225.000000, "0%");
                PlayerTextDrawFont(playerid, PGYM_UI[playerid], 1);
                PlayerTextDrawLetterSize(playerid, PGYM_UI[playerid], 0.180000, 1.100000);
                PlayerTextDrawTextSize(playerid, PGYM_UI[playerid], 42.500000, 17.000000);
                PlayerTextDrawSetOutline(playerid, PGYM_UI[playerid], 1);
                PlayerTextDrawSetShadow(playerid, PGYM_UI[playerid], 0);
                PlayerTextDrawAlignment(playerid, PGYM_UI[playerid], 1);
                PlayerTextDrawColor(playerid, PGYM_UI[playerid], -16776961);
                PlayerTextDrawBackgroundColor(playerid, PGYM_UI[playerid], 255);
                PlayerTextDrawBoxColor(playerid, PGYM_UI[playerid], 50);
                PlayerTextDrawUseBox(playerid, PGYM_UI[playerid], 0);
                PlayerTextDrawSetProportional(playerid, PGYM_UI[playerid], 1);
                PlayerTextDrawSetSelectable(playerid, PGYM_UI[playerid], 0);

                PlayerTextDrawShow(playerid, PGYM_UI[playerid]);

                g_GYMBikeUsed[id] = true;
                GYM_PlayerUsing[playerid] = true;
                GYM_PlayerProgress[playerid] = 0;
                GYM_PlayerType[playerid] = 3;
                GYM_PlayerToolID[playerid] = id;
            }
            else
            {
                if(AccountData[playerid][pIsSmoking]) return SEM(playerid, "You are currently smoking. Finish it or use '/stopsmoke' to stop!");
		        if(AccountData[playerid][pEatingStep] > 0) return SEM(playerid, "You are currently eating. Finish it or use '/stopeating' to stop!");
		        if(AccountData[playerid][pDrinkingStep] > 0) return SEM(playerid, "You are currently drinking. Finish it or use '/stopdrinking' to stop!");

                if (GetTickCount() - GYM_PlayerAntiSpam[playerid] < 666) return 1;

                GYM_PlayerAntiSpam[playerid] = GetTickCount();

                ApplyAnimation(playerid, "GYMNASIUM", "gym_bike_pedal", 0.40, false, false, false, true, 0, true);

                GYM_PlayerProgress[playerid]++;

                static string[64];
                format(string, sizeof(string), "%d%", GYM_PlayerProgress[playerid]);
                PlayerTextDrawSetString(playerid, PGYM_UI[playerid], string);
                PlayerTextDrawColor(playerid, PGYM_UI[playerid], ConvertFloatColor(float(GYM_PlayerProgress[playerid]), X11_WHITE));
                PlayerTextDrawShow(playerid, PGYM_UI[playerid]);

                if(GYM_PlayerProgress[playerid] >= 100)
                {
                    GYM_PlayerUsing[playerid] = false;
                    GYM_PlayerProgress[playerid] = 0;
                    GYM_PlayerType[playerid] = 0;
                    GYM_PlayerToolID[playerid] = -1;

                    if(IsValidPlayerTextDraw(playerid, PGYM_UI[playerid]))
                    {
                        PlayerTextDrawDestroy(playerid, PGYM_UI[playerid]);
                        PGYM_UI[playerid] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
                    }
                    TextDrawHideForPlayer(playerid, GYM_UI[0]);
                    TextDrawHideForPlayer(playerid, GYM_UI[1]);

                    RemovePlayerAttachedObject(playerid, 9);
                    StopRunningAnimation(playerid);
                    
                    if(AccountData[playerid][pVIP] != 2)
                    {
                        AccountData[playerid][pStress] -= 10;
                    }
                    else
                    {
                        AccountData[playerid][pStress] -= 15;
                    }
                    AccountData[playerid][pThirst] -= 2;
                    AccountData[playerid][pHunger] --;
                    g_GYMBikeUsed[id] = false;
                }
            }
        }
        if((id = g_GYMBarbel_Nearest(playerid)) != -1)
        {
            if(!GYM_PlayerUsing[playerid])
            {
                if(g_GYMBarbelUsed[id]) return SEM(playerid, "Alat GYM tersebut sedang digunakan orang lain!");
                if(AccountData[playerid][pIsSmoking]) return SEM(playerid, "You are currently smoking. Finish it or use '/stopsmoke' to stop!");
		        if(AccountData[playerid][pEatingStep] > 0) return SEM(playerid, "You are currently eating. Finish it or use '/stopeating' to stop!");
		        if(AccountData[playerid][pDrinkingStep] > 0) return SEM(playerid, "You are currently drinking. Finish it or use '/stopdrinking' to stop!");

                SetPlayerPos(playerid, __g_GYMBarbel[id][0], __g_GYMBarbel[id][1], __g_GYMBarbel[id][2]);
                SetPlayerFacingAngle(playerid, __g_GYMBarbel[id][3]);

                ApplyAnimation(playerid, "benchpress", "gym_bp_geton", 5.33, false, false, false, true, 0, true);
                SetPlayerAttachedObject(playerid, 9, 2913, 6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0,1.0, 0, 0);

                TextDrawShowForPlayer(playerid, GYM_UI[0]);
                TextDrawShowForPlayer(playerid, GYM_UI[1]);
                
                if(IsValidPlayerTextDraw(playerid, PGYM_UI[playerid]))
                {
                    PlayerTextDrawDestroy(playerid, PGYM_UI[playerid]);
                    PGYM_UI[playerid] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
                }

                PGYM_UI[playerid] = CreatePlayerTextDraw(playerid, 12.000000, 225.000000, "0%");
                PlayerTextDrawFont(playerid, PGYM_UI[playerid], 1);
                PlayerTextDrawLetterSize(playerid, PGYM_UI[playerid], 0.180000, 1.100000);
                PlayerTextDrawTextSize(playerid, PGYM_UI[playerid], 42.500000, 17.000000);
                PlayerTextDrawSetOutline(playerid, PGYM_UI[playerid], 1);
                PlayerTextDrawSetShadow(playerid, PGYM_UI[playerid], 0);
                PlayerTextDrawAlignment(playerid, PGYM_UI[playerid], 1);
                PlayerTextDrawColor(playerid, PGYM_UI[playerid], -16776961);
                PlayerTextDrawBackgroundColor(playerid, PGYM_UI[playerid], 255);
                PlayerTextDrawBoxColor(playerid, PGYM_UI[playerid], 50);
                PlayerTextDrawUseBox(playerid, PGYM_UI[playerid], 0);
                PlayerTextDrawSetProportional(playerid, PGYM_UI[playerid], 1);
                PlayerTextDrawSetSelectable(playerid, PGYM_UI[playerid], 0);

                PlayerTextDrawShow(playerid, PGYM_UI[playerid]);

                g_GYMBarbelUsed[id] = true;
                GYM_PlayerUsing[playerid] = true;
                GYM_PlayerProgress[playerid] = 0;
                GYM_PlayerType[playerid] = 4;
                GYM_PlayerToolID[playerid] = id;
            }
            else
            {
                if(AccountData[playerid][pIsSmoking]) return SEM(playerid, "You are currently smoking. Finish it or use '/stopsmoke' to stop!");
		        if(AccountData[playerid][pEatingStep] > 0) return SEM(playerid, "You are currently eating. Finish it or use '/stopeating' to stop!");
		        if(AccountData[playerid][pDrinkingStep] > 0) return SEM(playerid, "You are currently drinking. Finish it or use '/stopdrinking' to stop!");
                
                if (GetTickCount() - GYM_PlayerAntiSpam[playerid] < 666) return 1;

                GYM_PlayerAntiSpam[playerid] = GetTickCount();

                ApplyAnimation(playerid, "benchpress", "gym_bp_up_B", 2.67, false, false, false, true, 0, true);

                GYM_PlayerProgress[playerid]++;

                static string[64];
                format(string, sizeof(string), "%d%", GYM_PlayerProgress[playerid]);
                PlayerTextDrawSetString(playerid, PGYM_UI[playerid], string);
                PlayerTextDrawColor(playerid, PGYM_UI[playerid], ConvertFloatColor(float(GYM_PlayerProgress[playerid]), X11_WHITE));
                PlayerTextDrawShow(playerid, PGYM_UI[playerid]);

                if(GYM_PlayerProgress[playerid] >= 100)
                {
                    GYM_PlayerUsing[playerid] = false;
                    GYM_PlayerProgress[playerid] = 0;
                    GYM_PlayerType[playerid] = 0;
                    GYM_PlayerToolID[playerid] = -1;

                    if(IsValidPlayerTextDraw(playerid, PGYM_UI[playerid]))
                    {
                        PlayerTextDrawDestroy(playerid, PGYM_UI[playerid]);
                        PGYM_UI[playerid] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
                    }
                    TextDrawHideForPlayer(playerid, GYM_UI[0]);
                    TextDrawHideForPlayer(playerid, GYM_UI[1]);

                    RemovePlayerAttachedObject(playerid, 9);
                    StopRunningAnimation(playerid);
                    
                    if(AccountData[playerid][pVIP] != 2)
                    {
                        AccountData[playerid][pStress] -= 10;
                    }
                    else
                    {
                        AccountData[playerid][pStress] -= 15;
                    }
                    AccountData[playerid][pThirst] -= 2;
                    AccountData[playerid][pHunger] --;
                    g_GYMBarbelUsed[id] = false;
                }
            }
        }
    }
    else if(newkeys & KEY_CTRL_BACK && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && GYM_PlayerUsing[playerid])
    {
        GYM_PlayerUsing[playerid] = false;
        GYM_PlayerProgress[playerid] = 0;

        switch(GYM_PlayerType[playerid])
        {
            case 1:
            {
                g_GYMFreeWeightUsed[GYM_PlayerToolID[playerid]] = false;
            }
            case 2:
            {
                g_GYMYogaUsed[GYM_PlayerToolID[playerid]] = false;
            }
            case 3:
            {
                g_GYMBikeUsed[GYM_PlayerToolID[playerid]] = false;
            }
            case 4:
            {
               g_GYMBarbelUsed[GYM_PlayerToolID[playerid]] = false;
            }
        }
        GYM_PlayerType[playerid] = 0;
        GYM_PlayerToolID[playerid] = -1;

        if(IsValidPlayerTextDraw(playerid, PGYM_UI[playerid]))
        {
            PlayerTextDrawDestroy(playerid, PGYM_UI[playerid]);
            PGYM_UI[playerid] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
        }
        TextDrawHideForPlayer(playerid, GYM_UI[0]);
        TextDrawHideForPlayer(playerid, GYM_UI[1]);

        RemovePlayerAttachedObject(playerid, 9);
        StopRunningAnimation(playerid);
    }
    return 1;
}

ptask CheckPlayerGYM[5555](playerid) 
{
    if(AccountData[playerid][pSpawned] && GYM_PlayerUsing[playerid])
    {
        switch(GYM_PlayerType[playerid])
        {
            case 1:
            {
                if(!IsPlayerInRangeOfPoint(playerid, 2.0, __g_GYMFreeWeight[GYM_PlayerToolID[playerid]][0], __g_GYMFreeWeight[GYM_PlayerToolID[playerid]][1], __g_GYMFreeWeight[GYM_PlayerToolID[playerid]][2]))
                {
                    GYM_PlayerUsing[playerid] = false;
                    GYM_PlayerProgress[playerid] = 0;
                    GYM_PlayerType[playerid] = 0;

                    if(IsValidPlayerTextDraw(playerid, PGYM_UI[playerid]))
                    {
                        PlayerTextDrawDestroy(playerid, PGYM_UI[playerid]);
                        PGYM_UI[playerid] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
                    }
                    TextDrawHideForPlayer(playerid, GYM_UI[0]);
                    TextDrawHideForPlayer(playerid, GYM_UI[1]);

                    RemovePlayerAttachedObject(playerid, 9);
                    StopRunningAnimation(playerid);
                    g_GYMFreeWeightUsed[GYM_PlayerToolID[playerid]] = false;

                    GYM_PlayerToolID[playerid] = -1;
                }
            }
            case 2:
            {
                if(!IsPlayerInRangeOfPoint(playerid, 2.0, __g_GYMYoga[GYM_PlayerToolID[playerid]][0], __g_GYMYoga[GYM_PlayerToolID[playerid]][1], __g_GYMYoga[GYM_PlayerToolID[playerid]][2]))
                {
                    GYM_PlayerUsing[playerid] = false;
                    GYM_PlayerProgress[playerid] = 0;
                    GYM_PlayerType[playerid] = 0;

                    if(IsValidPlayerTextDraw(playerid, PGYM_UI[playerid]))
                    {
                        PlayerTextDrawDestroy(playerid, PGYM_UI[playerid]);
                        PGYM_UI[playerid] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
                    }
                    TextDrawHideForPlayer(playerid, GYM_UI[0]);
                    TextDrawHideForPlayer(playerid, GYM_UI[1]);

                    RemovePlayerAttachedObject(playerid, 9);
                    StopRunningAnimation(playerid);
                    g_GYMYogaUsed[GYM_PlayerToolID[playerid]] = false;

                    GYM_PlayerToolID[playerid] = -1;
                }
            }
            case 3:
            {
                if(!IsPlayerInRangeOfPoint(playerid, 2.0, __g_GYMBike[GYM_PlayerToolID[playerid]][0], __g_GYMBike[GYM_PlayerToolID[playerid]][1], __g_GYMBike[GYM_PlayerToolID[playerid]][2]))
                {
                    GYM_PlayerUsing[playerid] = false;
                    GYM_PlayerProgress[playerid] = 0;
                    GYM_PlayerType[playerid] = 0;

                    if(IsValidPlayerTextDraw(playerid, PGYM_UI[playerid]))
                    {
                        PlayerTextDrawDestroy(playerid, PGYM_UI[playerid]);
                        PGYM_UI[playerid] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
                    }
                    TextDrawHideForPlayer(playerid, GYM_UI[0]);
                    TextDrawHideForPlayer(playerid, GYM_UI[1]);

                    RemovePlayerAttachedObject(playerid, 9);
                    StopRunningAnimation(playerid);
                    g_GYMBikeUsed[GYM_PlayerToolID[playerid]] = false;

                    GYM_PlayerToolID[playerid] = -1;
                }
            }
            case 4:
            {
                if(!IsPlayerInRangeOfPoint(playerid, 2.0, __g_GYMBarbel[GYM_PlayerToolID[playerid]][0], __g_GYMBarbel[GYM_PlayerToolID[playerid]][1], __g_GYMBarbel[GYM_PlayerToolID[playerid]][2]))
                {
                    GYM_PlayerUsing[playerid] = false;
                    GYM_PlayerProgress[playerid] = 0;
                    GYM_PlayerType[playerid] = 0;

                    if(IsValidPlayerTextDraw(playerid, PGYM_UI[playerid]))
                    {
                        PlayerTextDrawDestroy(playerid, PGYM_UI[playerid]);
                        PGYM_UI[playerid] = PlayerText: INVALID_PLAYER_TEXT_DRAW;
                    }
                    TextDrawHideForPlayer(playerid, GYM_UI[0]);
                    TextDrawHideForPlayer(playerid, GYM_UI[1]);

                    RemovePlayerAttachedObject(playerid, 9);
                    StopRunningAnimation(playerid);
                    g_GYMBarbelUsed[GYM_PlayerToolID[playerid]] = false;
                    
                    GYM_PlayerToolID[playerid] = -1;
                }
            }
        }
    }
    return 1;
}