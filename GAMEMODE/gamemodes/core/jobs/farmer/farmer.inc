#include <YSI_Coding\y_hooks>

#define MAX_FARMPLANTS 6000

enum
{
    FARMER_PLANT_NONE,
    FARMER_PLANT_CABAI,
    FARMER_PLANT_TEBU,
    FARMER_PLANT_PADI,
    FARMER_PLANT_STRAWBERRY,
    FARMER_PLANT_JERUK,
    FARMER_PLANT_ANGGUR
};

enum E_FARMERSTUFF
{
    //timer check
    bool:pDuringTakingPlant,
    bool:pDuringPlantingSeed
};
new PlayerFarmerVars[MAX_PLAYERS][E_FARMERSTUFF];

enum E_FRMERPLANTAE
{
    //saved
    Float:Pos[3],
    Type,
    SpawnTimer,

    //not saved
    DeadTimer,
    bool:ReadyHarvest,
    bool:DuringHarvest,
    bool:Watered,
    STREAMER_TAG_OBJECT:FarmerPlantObject,
    STREAMER_TAG_CP:FarmerPlantCP
};
new FarmerPlant[MAX_FARMPLANTS][E_FRMERPLANTAE],
    Iterator:FarmPlants<MAX_FARMPLANTS>;

CheckFarmerTimer(playerid)
{
    if(pTakingPlantTimer[playerid]) return 1;
    if(pProcessChiliTimer[playerid]) return 1;
    if(pProcessRiceTimer[playerid]) return 1;
    if(pPorcessSugarTimer[playerid]) return 1;
    return 0;
}

GetFarmPlantName(type)
{
    static string[34];
    switch(type)
    {
        case FARMER_PLANT_CABAI:
        {
            strcopy(string, "Cabai");
        }
        case FARMER_PLANT_TEBU:
        {
            strcopy(string, "Tebu");
        }
        case FARMER_PLANT_PADI:
        {
            strcopy(string, "Padi");
        }
        case FARMER_PLANT_STRAWBERRY:
        {
            strcopy(string, "Strawberry");
        }
        case FARMER_PLANT_JERUK:
        {
            strcopy(string, "Jeruk");
        }
        case FARMER_PLANT_ANGGUR:
        {
            strcopy(string, "Anggur");
        }
    }
    return string;
}

IsPlayerNearFromPlant(playerid)
{
    foreach(new d : FarmPlants)
    {
        if(IsPlayerInRangeOfPoint(playerid, 2.0, FarmerPlant[d][Pos][0], FarmerPlant[d][Pos][1], FarmerPlant[d][Pos][2]))
        {
            return true;
        }
    }
    return false;
}

IsPlayerNearFarmWell(playerid)
{
    for(new x; x < 6; x++)
    {
        if(IsPlayerInRangeOfPoint(playerid, 2.0, __g_FarmWellPos[x][0], __g_FarmWellPos[x][1], __g_FarmWellPos[x][2]))
        {
            return true;
        }
    }
    return false;
}

FarmPlant_Rebuild(id)
{
	if(id != -1)
	{
		if(DestroyDynamicObject(FarmerPlant[id][FarmerPlantObject]))
		    FarmerPlant[id][FarmerPlantObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

        if(DestroyDynamicCP(FarmerPlant[id][FarmerPlantCP]))
            FarmerPlant[id][FarmerPlantCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
            
		FarmerPlant[id][DuringHarvest] = false;

        switch(FarmerPlant[id][Type])
        {
            case FARMER_PLANT_CABAI:
            {
		        FarmerPlant[id][FarmerPlantObject] = CreateDynamicObject(810, FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2] - 1.5, 0.0, 0.0, 0.0, 0, 0, -1, 50.00, 50.00, -1);
            }
            case FARMER_PLANT_TEBU:
            {
                FarmerPlant[id][FarmerPlantObject] = CreateDynamicObject(806, FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2] - 2.6, 0.0, 0.0, 0.0, 0, 0, -1, 50.00, 50.00, -1);
            }
            case FARMER_PLANT_PADI:
            {
                FarmerPlant[id][FarmerPlantObject] = CreateDynamicObject(861, FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2] - 1.9, 0.0, 0.0, 0.0, 0, 0, -1, 50.00, 50.00, -1);
            }
            case FARMER_PLANT_STRAWBERRY:
            {
		        FarmerPlant[id][FarmerPlantObject] = CreateDynamicObject(810, FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2] - 1.5, 0.0, 0.0, 0.0, 0, 0, -1, 50.00, 50.00, -1);
            }
            case FARMER_PLANT_JERUK:
            {
                FarmerPlant[id][FarmerPlantObject] = CreateDynamicObject(810, FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2] - 2.6, 0.0, 0.0, 0.0, 0, 0, -1, 50.00, 50.00, -1);
            }
            case FARMER_PLANT_ANGGUR:
            {
                FarmerPlant[id][FarmerPlantObject] = CreateDynamicObject(810, FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2] - 1.9, 0.0, 0.0, 0.0, 0, 0, -1, 50.00, 50.00, -1);
            }
        }
		FarmerPlant[id][FarmerPlantCP] = CreateDynamicCP(FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2], 1.5, 0, 0, -1, 0.85, -1, 0);

        if(FarmerPlant[id][SpawnTimer] <= 0)
        {
            FarmerPlant[id][SpawnTimer] = 0;
            FarmerPlant[id][ReadyHarvest] = true;
            FarmerPlant[id][DeadTimer] = 3600;

            MoveDynamicObject(FarmerPlant[id][FarmerPlantObject], FarmerPlant[id][Pos][0], FarmerPlant[id][Pos][1], FarmerPlant[id][Pos][2] - 0.9, 0.30, 0.0, 0.0, 0.0);
        }
    }
	return 1;
}

FarmPlant_Save(id)
{
	new
	    query[512];
        
	format(query, sizeof(query), "UPDATE `farmplants` SET `posX` = '%f', `posY` = '%f', `posZ` = '%f', `plantType` = %d, `spawnTimer` = %d, `watered` = %d WHERE `id` = %d",
        FarmerPlant[id][Pos][0],
        FarmerPlant[id][Pos][1],
        FarmerPlant[id][Pos][2],
        FarmerPlant[id][Type],
        FarmerPlant[id][SpawnTimer],
        FarmerPlant[id][Watered],
        id
	);
	return mysql_pquery(g_SQL, query);
}

forward CooldownFarmPlant(playerid);
public CooldownFarmPlant(playerid)
{
    if(!PlayerFarmerVars[playerid][pDuringPlantingSeed]) return 0;

    PlayerFarmerVars[playerid][pDuringPlantingSeed] = false;
    return 1;
}

forward StopHoldBucket(playerid);
public StopHoldBucket(playerid)
{
    RemovePlayerAttachedObject(playerid, 9);
    return 1;
}

forward OnPlantCreated(playerid, id);
public OnPlantCreated(playerid, id)
{
	FarmPlant_Save(id);
	return 1;
}

forward LoadFarmPlants();
public LoadFarmPlants()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
 		new id;
		for(new i; i < rows; i++)
		{
            cache_get_value_name_int(i, "id", id);
            cache_get_value_name_float(i, "posX", FarmerPlant[id][Pos][0]);
            cache_get_value_name_float(i, "posY", FarmerPlant[id][Pos][1]);
            cache_get_value_name_float(i, "posZ", FarmerPlant[id][Pos][2]);
            cache_get_value_name_int(i, "plantType", FarmerPlant[id][Type]);
            cache_get_value_name_int(i, "spawnTimer", FarmerPlant[id][SpawnTimer]);
            cache_get_value_name_int(i, "watered", FarmerPlant[id][Watered]);
            
			FarmPlant_Rebuild(id);
			Iter_Add(FarmPlants, id);
        }
        printf("[Farm Plants] Jumlah total farm plants yang dimuat: %d.", rows);
	}
	return 1;
}

hook OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP:checkpointid)
{
    if(AccountData[playerid][pJob] == JOB_FARMER)
    {
        foreach(new d : FarmPlants)
        {
            if(checkpointid == FarmerPlant[d][FarmerPlantCP])
            {
                static string[144];
                if(FarmerPlant[d][Watered])
                {
                    if(FarmerPlant[d][ReadyHarvest])
                    {
                        format(string, sizeof(string), "~y~Tanaman: ~b~%s~n~~g~Siap panen!", GetFarmPlantName(FarmerPlant[d][Type]));
                        ShowPlayerFooter(playerid, string, 35000); 
                    }
                    else
                    {
                        format(string, sizeof(string), "~y~Tanaman: ~b~%s~n~~p~Pertumbuhan: ~b~%02d:%02d", GetFarmPlantName(FarmerPlant[d][Type]), FarmerPlant[d][SpawnTimer]/60, FarmerPlant[d][SpawnTimer]%3600%60);
                        ShowPlayerFooter(playerid, string, 35000); 
                    }
                }
                else
                {
                    format(string, sizeof(string), "~y~Tanaman: ~b~%s~n~~r~Kering belum disiram!", GetFarmPlantName(FarmerPlant[d][Type]));
                    ShowPlayerFooter(playerid, string, 35000); 
                }
                PlayerPlaySound(playerid, SOUND_NOTIF_BOX, 0.0, 0.0, 0.0);
            }
        }
    }
    return 1;
}

hook OnPlayerLeaveDynamicCP(playerid, STREAMER_TAG_CP:checkpointid)
{
    if(AccountData[playerid][pJob] == JOB_FARMER && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        foreach(new d : FarmPlants)
        {
            if(checkpointid == FarmerPlant[d][FarmerPlantCP])
            {
                HidePlayerFooter(playerid);
            }
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && AccountData[playerid][pJob] == JOB_FARMER)
    {
        foreach(new d : FarmPlants)
        {
            if(IsPlayerInDynamicCP(playerid, FarmerPlant[d][FarmerPlantCP]))
            {
                switch(FarmerPlant[d][Type])
                {
                    case FARMER_PLANT_CABAI:
                    {
                        if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
                        
                        if(FarmerPlant[d][Watered])
                        {
                            if(FarmerPlant[d][ReadyHarvest])
                            {
                                if(GetPlayerWeaponEx(playerid) != 4) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda harus memegang pisau!");
                                if(FarmerPlant[d][DuringHarvest]) return ShowTDN(playerid, NOTIFICATION_WARNING, "Tanaman ini sedang dipanen oleh pemain lain!");
                                if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
                                if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
                                if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

                                SendRPMeAboveHead(playerid, "Memanen cabai dengan bantuan pisau dan kedua tangannya.");

                                AccountData[playerid][pActivityTime] = 1;
                                FarmerPlant[d][DuringHarvest] = true;
                                PlayerFarmerVars[playerid][pDuringTakingPlant] = true;
                                AccountData[playerid][pInPlant] = d;
                                pTakingPlantTimer[playerid] = true;
                                PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMANEN");
                                ShowProgressBar(playerid);

                                OnePlayAnim(playerid, "BOMBER", "BOM_Plant", 4.1, true, false, false, true, false);
                            }
                        }
                        else
                        {
                            if(!PlayerHasItem(playerid, "Ember Terisi")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki ember yang terisi oleh air dari sumur!");
                            if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
                            if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
                            if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

                            AccountData[playerid][pWaterInBucket]--;
                            SendRPMeAboveHead(playerid, "Menyiram tanaman cabai dengan bantuan ember berisi air dan kedua tangannya.");
                            FarmerPlant[d][Watered] = true;

                            ApplyAnimation(playerid, "FLAME", "FLAME_fire", 4.1, false, false, false, false, 0, true);
                            SetPlayerAttachedObject(playerid, 9, 19468, 6, 0.129999, 0.000000, 0.067999, 0.000000, 96.899986, 0.000000, 0.787999, 0.701999, 0.819999);
                            PlayerPlaySound(playerid, 1144, 0, 0, 0);

                            if(AccountData[playerid][pWaterInBucket] <= 0)
                            {
                                Inventory_Remove(playerid, "Ember Terisi");
                                Inventory_Add(playerid, "Ember", 19468);
                                ShowItemBox(playerid, "Ember Terisi", "Removed 1x", 1554, 5);
                                ShowItemBox(playerid, "Ember", "Received 1x", 19468, 6);
                                AccountData[playerid][pWaterInBucket] = 0;
                            }
                            SetTimerEx("StopHoldBucket", 700, false, "i", playerid);
                        }
                    }

                    case FARMER_PLANT_TEBU:
                    {
                        if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
                        
                        if(FarmerPlant[d][Watered])
                        {
                            if(FarmerPlant[d][ReadyHarvest])
                            {
                                if(GetPlayerWeaponEx(playerid) != 4) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda harus memegang pisau!");
                                if(FarmerPlant[d][DuringHarvest]) return ShowTDN(playerid, NOTIFICATION_WARNING, "Tanaman ini sedang dipanen oleh pemain lain!");
                                if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
                                if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
                                if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

                                SendRPMeAboveHead(playerid, "Memanen tebu dengan bantuan pisau dan kedua tangannya.");

                                AccountData[playerid][pActivityTime] = 1;
                                FarmerPlant[d][DuringHarvest] = true;
                                PlayerFarmerVars[playerid][pDuringTakingPlant] = true;
                                AccountData[playerid][pInPlant] = d;
                                pTakingPlantTimer[playerid] = true;
                                PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMANEN");
                                ShowProgressBar(playerid);

                                OnePlayAnim(playerid, "BOMBER", "BOM_Plant", 4.1, true, false, false, true, false);
                            }
                        }
                        else
                        {
                            if(!PlayerHasItem(playerid, "Ember Terisi")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki ember yang terisi oleh air dari sumur!");
                            if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
                            if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
                            if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

                            AccountData[playerid][pWaterInBucket]--;
                            SendRPMeAboveHead(playerid, "Menyiram tanaman tebu dengan bantuan ember berisi air dan kedua tangannya.");
                            FarmerPlant[d][Watered] = true;

                            ApplyAnimation(playerid, "FLAME", "FLAME_fire", 4.1, false, false, false, false, 0, true);
                            SetPlayerAttachedObject(playerid, 9, 19468, 6, 0.129999, 0.000000, 0.067999, 0.000000, 96.899986, 0.000000, 0.787999, 0.701999, 0.819999);
                            PlayerPlaySound(playerid, 1144, 0, 0, 0);

                            if(AccountData[playerid][pWaterInBucket] <= 0)
                            {
                                Inventory_Remove(playerid, "Ember Terisi");
                                Inventory_Add(playerid, "Ember", 19468);
                                ShowItemBox(playerid, "Ember Terisi", "Removed 1x", 1554, 5);
                                ShowItemBox(playerid, "Ember", "Received 1x", 19468, 6);
                                AccountData[playerid][pWaterInBucket] = 0;
                            }
                            SetTimerEx("StopHoldBucket", 700, false, "i", playerid);
                        }
                    }

                    case FARMER_PLANT_PADI:
                    {
                        if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
                        
                        if(FarmerPlant[d][Watered])
                        {
                            if(FarmerPlant[d][ReadyHarvest])
                            {
                                if(GetPlayerWeaponEx(playerid) != 4) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda harus memegang pisau!");
                                if(FarmerPlant[d][DuringHarvest]) return ShowTDN(playerid, NOTIFICATION_WARNING, "Tanaman ini sedang dipanen oleh pemain lain!");
                                if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
                                if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
                                if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");
                                SendRPMeAboveHead(playerid, "Memanen padi dengan bantuan pisau dan kedua tangannya.");

                                AccountData[playerid][pActivityTime] = 1;
                                FarmerPlant[d][DuringHarvest] = true;
                                PlayerFarmerVars[playerid][pDuringTakingPlant] = true;
                                AccountData[playerid][pInPlant] = d;
                                pTakingPlantTimer[playerid] = true;
                                PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMANEN");
                                ShowProgressBar(playerid);

                                OnePlayAnim(playerid, "BOMBER", "BOM_Plant", 4.1, true, false, false, true, false);
                            }
                        }
                        else
                        {
                            if(!PlayerHasItem(playerid, "Ember Terisi")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki ember yang terisi oleh air dari sumur!");
                            if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
                            if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
                            if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

                            AccountData[playerid][pWaterInBucket]--;
                            SendRPMeAboveHead(playerid, "Menyiram tanaman padi dengan bantuan ember berisi air dan kedua tangannya.");
                            FarmerPlant[d][Watered] = true;

                            ApplyAnimation(playerid, "FLAME", "FLAME_fire", 4.1, false, false, false, false, 0, true);
                            SetPlayerAttachedObject(playerid, 9, 19468, 6, 0.129999, 0.000000, 0.067999, 0.000000, 96.899986, 0.000000, 0.787999, 0.701999, 0.819999);
                            PlayerPlaySound(playerid, 1144, 0, 0, 0);

                            if(AccountData[playerid][pWaterInBucket] <= 0)
                            {
                                Inventory_Remove(playerid, "Ember Terisi");
                                Inventory_Add(playerid, "Ember", 19468);
                                ShowItemBox(playerid, "Ember Terisi", "Removed 1x", 1554, 5);
                                ShowItemBox(playerid, "Ember", "Received 1x", 19468, 6);
                                AccountData[playerid][pWaterInBucket] = 0;
                            }

                            SetTimerEx("StopHoldBucket", 700, false, "i", playerid);
                        }
                    }
                    case FARMER_PLANT_STRAWBERRY:
                    {
                        if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
                        
                        if(FarmerPlant[d][Watered])
                        {
                            if(FarmerPlant[d][ReadyHarvest])
                            {
                                if(GetPlayerWeaponEx(playerid) != 4) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda harus memegang pisau!");
                                if(FarmerPlant[d][DuringHarvest]) return ShowTDN(playerid, NOTIFICATION_WARNING, "Tanaman ini sedang dipanen oleh pemain lain!");
                                if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
                                if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
                                if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");
                                SendRPMeAboveHead(playerid, "Memanen strawberry dengan bantuan pisau dan kedua tangannya.");

                                AccountData[playerid][pActivityTime] = 1;
                                FarmerPlant[d][DuringHarvest] = true;
                                PlayerFarmerVars[playerid][pDuringTakingPlant] = true;
                                AccountData[playerid][pInPlant] = d;
                                pTakingPlantTimer[playerid] = true;
                                PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMANEN");
                                ShowProgressBar(playerid);

                                OnePlayAnim(playerid, "BOMBER", "BOM_Plant", 4.1, true, false, false, true, false);
                            }
                        }
                        else
                        {
                            if(!PlayerHasItem(playerid, "Ember Terisi")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki ember yang terisi oleh air dari sumur!");
                            if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
                            if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
                            if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

                            AccountData[playerid][pWaterInBucket]--;
                            SendRPMeAboveHead(playerid, "Menyiram tanaman strawberry dengan bantuan ember berisi air dan kedua tangannya.");
                            FarmerPlant[d][Watered] = true;

                            ApplyAnimation(playerid, "FLAME", "FLAME_fire", 4.1, false, false, false, false, 0, true);
                            SetPlayerAttachedObject(playerid, 9, 19468, 6, 0.129999, 0.000000, 0.067999, 0.000000, 96.899986, 0.000000, 0.787999, 0.701999, 0.819999);
                            PlayerPlaySound(playerid, 1144, 0, 0, 0);

                            if(AccountData[playerid][pWaterInBucket] <= 0)
                            {
                                Inventory_Remove(playerid, "Ember Terisi");
                                Inventory_Add(playerid, "Ember", 19468);
                                ShowItemBox(playerid, "Ember Terisi", "Removed 1x", 1554, 5);
                                ShowItemBox(playerid, "Ember", "Received 1x", 19468, 6);
                                AccountData[playerid][pWaterInBucket] = 0;
                            }

                            SetTimerEx("StopHoldBucket", 700, false, "i", playerid);
                        }
                    }
                    case FARMER_PLANT_JERUK:
                    {
                        if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
                        
                        if(FarmerPlant[d][Watered])
                        {
                            if(FarmerPlant[d][ReadyHarvest])
                            {
                                if(GetPlayerWeaponEx(playerid) != 4) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda harus memegang pisau!");
                                if(FarmerPlant[d][DuringHarvest]) return ShowTDN(playerid, NOTIFICATION_WARNING, "Tanaman ini sedang dipanen oleh pemain lain!");
                                if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
                                if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
                                if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");
                                SendRPMeAboveHead(playerid, "Memanen jeruk dengan bantuan pisau dan kedua tangannya.");

                                AccountData[playerid][pActivityTime] = 1;
                                FarmerPlant[d][DuringHarvest] = true;
                                PlayerFarmerVars[playerid][pDuringTakingPlant] = true;
                                AccountData[playerid][pInPlant] = d;
                                pTakingPlantTimer[playerid] = true;
                                PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMANEN");
                                ShowProgressBar(playerid);

                                OnePlayAnim(playerid, "BOMBER", "BOM_Plant", 4.1, true, false, false, true, false);
                            }
                        }
                        else
                        {
                            if(!PlayerHasItem(playerid, "Ember Terisi")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki ember yang terisi oleh air dari sumur!");
                            if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
                            if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
                            if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

                            AccountData[playerid][pWaterInBucket]--;
                            SendRPMeAboveHead(playerid, "Menyiram tanaman jeruk dengan bantuan ember berisi air dan kedua tangannya.");
                            FarmerPlant[d][Watered] = true;

                            ApplyAnimation(playerid, "FLAME", "FLAME_fire", 4.1, false, false, false, false, 0, true);
                            SetPlayerAttachedObject(playerid, 9, 19468, 6, 0.129999, 0.000000, 0.067999, 0.000000, 96.899986, 0.000000, 0.787999, 0.701999, 0.819999);
                            PlayerPlaySound(playerid, 1144, 0, 0, 0);

                            if(AccountData[playerid][pWaterInBucket] <= 0)
                            {
                                Inventory_Remove(playerid, "Ember Terisi");
                                Inventory_Add(playerid, "Ember", 19468);
                                ShowItemBox(playerid, "Ember Terisi", "Removed 1x", 1554, 5);
                                ShowItemBox(playerid, "Ember", "Received 1x", 19468, 6);
                                AccountData[playerid][pWaterInBucket] = 0;
                            }

                            SetTimerEx("StopHoldBucket", 700, false, "i", playerid);
                        }
                    }
                    case FARMER_PLANT_ANGGUR:
                    {
                        if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
                        
                        if(FarmerPlant[d][Watered])
                        {
                            if(FarmerPlant[d][ReadyHarvest])
                            {
                                if(GetPlayerWeaponEx(playerid) != 4) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda harus memegang pisau!");
                                if(FarmerPlant[d][DuringHarvest]) return ShowTDN(playerid, NOTIFICATION_WARNING, "Tanaman ini sedang dipanen oleh pemain lain!");
                                if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
                                if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
                                if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");
                                SendRPMeAboveHead(playerid, "Memanen anggur dengan bantuan pisau dan kedua tangannya.");

                                AccountData[playerid][pActivityTime] = 1;
                                FarmerPlant[d][DuringHarvest] = true;
                                PlayerFarmerVars[playerid][pDuringTakingPlant] = true;
                                AccountData[playerid][pInPlant] = d;
                                pTakingPlantTimer[playerid] = true;
                                PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMANEN");
                                ShowProgressBar(playerid);

                                OnePlayAnim(playerid, "BOMBER", "BOM_Plant", 4.1, true, false, false, true, false);
                            }
                        }
                        else
                        {
                            if(!PlayerHasItem(playerid, "Ember Terisi")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki ember yang terisi oleh air dari sumur!");
                            if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
                            if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
                            if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

                            AccountData[playerid][pWaterInBucket]--;
                            SendRPMeAboveHead(playerid, "Menyiram tanaman anggur dengan bantuan ember berisi air dan kedua tangannya.");
                            FarmerPlant[d][Watered] = true;

                            ApplyAnimation(playerid, "FLAME", "FLAME_fire", 4.1, false, false, false, false, 0, true);
                            SetPlayerAttachedObject(playerid, 9, 19468, 6, 0.129999, 0.000000, 0.067999, 0.000000, 96.899986, 0.000000, 0.787999, 0.701999, 0.819999);
                            PlayerPlaySound(playerid, 1144, 0, 0, 0);

                            if(AccountData[playerid][pWaterInBucket] <= 0)
                            {
                                Inventory_Remove(playerid, "Ember Terisi");
                                Inventory_Add(playerid, "Ember", 19468);
                                ShowItemBox(playerid, "Ember Terisi", "Removed 1x", 1554, 5);
                                ShowItemBox(playerid, "Ember", "Received 1x", 19468, 6);
                                AccountData[playerid][pWaterInBucket] = 0;
                            }

                            SetTimerEx("StopHoldBucket", 700, false, "i", playerid);
                        }
                    }
                }
            }
        }

        if(IsPlayerNearFarmWell(playerid))
        {
            if(!PlayerHasItem(playerid, "Ember"))
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Ember!");
            
            Inventory_Remove(playerid, "Ember");
            Inventory_Add(playerid, "Ember Terisi", 1554);
            ShowItemBox(playerid, "Ember", "Removed 1x", 19468, 5);
            ShowItemBox(playerid, "Ember Terisi", "Received 1x", 1554, 6);
            AccountData[playerid][pWaterInBucket] = 25;
        }

        if(IsPlayerInRangeOfPoint(playerid, 3.5, -381.9745,-1438.8531,25.7266))
        {
            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
            if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
		    if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
		    if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");
            Dialog_Show(playerid, "JobFarmerBuySeeds", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Toko Bibit",
            "Jenis Bibit\tHarga\n\
            "WHITE"Bibit Cabai\t"GREEN"$40.25\n\
            "WHITE"Bibit Tebu\t"GREEN"$40.25\n\
            "WHITE"Bibit Padi\t"GREEN"$40.25", "Pilih", "Batal");
        }

        else if(IsPlayerInRangeOfPoint(playerid, 3.5, -347.8932,-1046.3129,59.8125))
        {
            if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
            if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
		    if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
		    if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");
            Dialog_Show(playerid, "JobFarmerBuyFSeeds", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Toko Bibit",
            "Jenis Bibit\tHarga\n\
            "WHITE"Bibit Strawberry\t"GREEN"$40.25\n\
            "WHITE"Bibit Jeruk\t"GREEN"$40.25\n\
            "WHITE"Bibit Anggur\t"GREEN"$40.25", "Pilih", "Batal");
        }
    }
    return 1;
}

task RespawnPlantTimer[1000]()
{
	foreach(new d : FarmPlants) if(d != INVALID_ITERATOR_SLOT)
    {
        if(!FarmerPlant[d][ReadyHarvest] && FarmerPlant[d][SpawnTimer] > 0)
        {
            if(FarmerPlant[d][Watered])
            {
                FarmerPlant[d][SpawnTimer]--;

                if(FarmerPlant[d][SpawnTimer] <= 0)
                {
                    FarmerPlant[d][SpawnTimer] = 0;
                    FarmerPlant[d][ReadyHarvest] = true;
                    FarmerPlant[d][DeadTimer] = 3600;

                    MoveDynamicObject(FarmerPlant[d][FarmerPlantObject], FarmerPlant[d][Pos][0], FarmerPlant[d][Pos][1], FarmerPlant[d][Pos][2] - 0.9, 0.30, 0.0, 0.0, 0.0);
                }
            }
        }
    }
    return 1;
}

task ExpiredPlantTimer[1000]()
{
    foreach(new d : FarmPlants) if(d != INVALID_ITERATOR_SLOT)
    {
        if(FarmerPlant[d][ReadyHarvest] && FarmerPlant[d][DeadTimer] > 0)
        {
            FarmerPlant[d][DeadTimer]--;

            if(FarmerPlant[d][DeadTimer] <= 0)
            {
                FarmerPlant[d][DeadTimer] = 0;

                if(DestroyDynamicObject(FarmerPlant[d][FarmerPlantObject]))
                    FarmerPlant[d][FarmerPlantObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

                if(DestroyDynamicCP(FarmerPlant[d][FarmerPlantCP]))
                    FarmerPlant[d][FarmerPlantCP] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                FarmerPlant[d][DuringHarvest] = false;
                FarmerPlant[d][Watered] = false;
                FarmerPlant[d][Pos][0] = 0;
                FarmerPlant[d][Pos][1] = 0;
                FarmerPlant[d][Pos][2] = 0;
                FarmerPlant[d][Type] = FARMER_PLANT_NONE;
                FarmerPlant[d][ReadyHarvest] = false;
                FarmerPlant[d][SpawnTimer] = 0;

                static strgbg[258];
                mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `farmplants` WHERE `id` = %d", d);
                mysql_pquery(g_SQL, strgbg);

                Iter_Remove(FarmPlants, d);
            }
        }
    }
    return 1;
}

YCMD:farmtool(playerid, params[], help)
{
    static string[555];
    format(string, sizeof(string), ""WHITE"Anda memiliki isi ember yang dapat menyiram "YELLOW"%dx tanaman "WHITE"lagi", AccountData[playerid][pWaterInBucket]);
    Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, "{DA9100}Pahlawan Roleplay "WHITE"- Alat Pertanian", string, "Tutup", "");
    return 1;
}