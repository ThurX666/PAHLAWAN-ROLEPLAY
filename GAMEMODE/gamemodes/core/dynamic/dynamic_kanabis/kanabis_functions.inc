#include <YSI_Coding\y_hooks>

#define MAX_KANABIS (50)

enum e_kanabisdetail {
 	kanabisModel,
	Float:kanabisPos[6], 
	kanabisInterior,
	kanabisWorld,

    //not save
	STREAMER_TAG_OBJECT:kanabisObject,
	STREAMER_TAG_AREA:kanabisArea,
	kanabisGrow,
	bool:kanabisTaken
};
new KanabisData[MAX_KANABIS][e_kanabisdetail],
	STREAMER_TAG_AREA:KanabisField,
	STREAMER_TAG_AREA:ProcessMarijuanaArea,
	STREAMER_TAG_AREA:SellingMarijuanaArea,
    Iterator:Kanabises<MAX_KANABIS>;

new Float:KanabisZ2Points[] = {
    1799.3345,-228.8485,
    1780.4225,-225.9110,
    1748.3844,-232.3940,
    1729.6821,-224.2197,
    1750.7434,-188.1803,
    1747.0375,-165.3684,
    1757.9873,-93.33201,
    1778.7031,-94.77251,
    1819.6366,-110.6673,
    1822.5863,-143.5874,
    1813.9341,-175.6411,
    1798.1304,-234.9332
};

task RespawnKanabis[10000]()
{
	foreach(new i : Kanabises)
	{
		if(KanabisData[i][kanabisGrow] != 0 && gettime() > KanabisData[i][kanabisGrow])
		{
			KanabisData[i][kanabisGrow] = 0;

			KanabisData[i][kanabisTaken] = false;

			KanabisData[i][kanabisObject] = CreateDynamicObject(KanabisData[i][kanabisModel], KanabisData[i][kanabisPos][0], KanabisData[i][kanabisPos][1], KanabisData[i][kanabisPos][2], KanabisData[i][kanabisPos][3], KanabisData[i][kanabisPos][4], KanabisData[i][kanabisPos][5], KanabisData[i][kanabisWorld], KanabisData[i][kanabisInterior], -1, 50.0, 50.0, KanabisField);
			KanabisData[i][kanabisArea] = CreateDynamicSphere(KanabisData[i][kanabisPos][0], KanabisData[i][kanabisPos][1], KanabisData[i][kanabisPos][2] + 1.7, 3.5, KanabisData[i][kanabisWorld], KanabisData[i][kanabisInterior], -1);
		}
	}
	return 1;
}


Kanabis_Nearest(playerid)
{
    foreach(new i : Kanabises) if (IsPlayerInRangeOfPoint(playerid, 3.0, KanabisData[i][kanabisPos][0], KanabisData[i][kanabisPos][1], KanabisData[i][kanabisPos][2]) && IsValidDynamicArea(KanabisData[i][kanabisArea]))
	{
		if (GetPlayerInterior(playerid) == KanabisData[i][kanabisInterior] && GetPlayerVirtualWorld(playerid) == KanabisData[i][kanabisWorld])
			return i;
	}
	return -1;
}

Kanabis_Save(kanabisid)
{
	new
	    query[512];
        
	format(query, sizeof(query), "UPDATE kanabis SET kanabisModel = '%d', kanabisX = '%f', kanabisY = '%f', kanabisZ = '%f', kanabisRx = '%f', kanabisRy = '%f', kanabisRz = '%f', kanabisInterior = '%d', kanabisWorld = '%d' WHERE id = '%d'",
        KanabisData[kanabisid][kanabisModel],
        KanabisData[kanabisid][kanabisPos][0],
        KanabisData[kanabisid][kanabisPos][1],
        KanabisData[kanabisid][kanabisPos][2],
        KanabisData[kanabisid][kanabisPos][3],
        KanabisData[kanabisid][kanabisPos][4],
        KanabisData[kanabisid][kanabisPos][5],
        KanabisData[kanabisid][kanabisInterior],
        KanabisData[kanabisid][kanabisWorld],
        kanabisid
	);
	return mysql_pquery(g_SQL, query);
}

hook OnGameModeInit()
{
	ProcessMarijuanaArea = CreateDynamicSphere(874.7801,-16.1301,63.1953, 3.5, 0, 0, -1);
	SellingMarijuanaArea = CreateDynamicSphere(-2429.8196,-2784.2107,3.0137, 3.5, 0, 0, -1);

	KanabisField = CreateDynamicPolygon(KanabisZ2Points, -FLOAT_INFINITY, FLOAT_INFINITY, sizeof(KanabisZ2Points), 0, 0, -1);
	return 1;
}

forward LoadKanabis();
public LoadKanabis()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
 		new kanabisid;
		for(new i; i < rows; i++)
		{
            cache_get_value_name_int(i, "id", kanabisid);
            cache_get_value_name_int(i, "kanabisModel", KanabisData[kanabisid][kanabisModel]);
            cache_get_value_name_float(i, "kanabisX", KanabisData[kanabisid][kanabisPos][0]);
            cache_get_value_name_float(i, "kanabisY", KanabisData[kanabisid][kanabisPos][1]);
            cache_get_value_name_float(i, "kanabisZ", KanabisData[kanabisid][kanabisPos][2]);
            cache_get_value_name_float(i, "kanabisRx", KanabisData[kanabisid][kanabisPos][3]);
            cache_get_value_name_float(i, "kanabisRy", KanabisData[kanabisid][kanabisPos][4]);
            cache_get_value_name_float(i, "kanabisRz", KanabisData[kanabisid][kanabisPos][5]);
            cache_get_value_name_int(i, "kanabisInterior", KanabisData[kanabisid][kanabisInterior]);
            cache_get_value_name_int(i, "kanabisWorld", KanabisData[kanabisid][kanabisWorld]);
            
		    KanabisData[kanabisid][kanabisObject] = CreateDynamicObject(KanabisData[kanabisid][kanabisModel], KanabisData[kanabisid][kanabisPos][0], KanabisData[kanabisid][kanabisPos][1], KanabisData[kanabisid][kanabisPos][2], KanabisData[kanabisid][kanabisPos][3], KanabisData[kanabisid][kanabisPos][4], KanabisData[kanabisid][kanabisPos][5], KanabisData[kanabisid][kanabisWorld], KanabisData[kanabisid][kanabisInterior], -1, 50.0, 50.0, KanabisField);
            KanabisData[kanabisid][kanabisArea] = CreateDynamicSphere(KanabisData[kanabisid][kanabisPos][0], KanabisData[kanabisid][kanabisPos][1], KanabisData[i][kanabisPos][2] + 1.7, 3.5, KanabisData[kanabisid][kanabisWorld], KanabisData[kanabisid][kanabisInterior], -1);

			Iter_Add(Kanabises, kanabisid);
        }
        printf("[Dynamic Kanabis] Jumlah total Kanabis yang dimuat: %d.", rows);
	}
}

forward OnKanabisCreated(playerid, kanabisid);
public OnKanabisCreated(playerid, kanabisid)
{
	Kanabis_Save(kanabisid);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s membuat Kanabis dengan ID: %d.", AccountData[playerid][pAdminname], kanabisid);
	return 1;
}

hook OnPlayerEnterDynArea(playerid, areaid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		foreach(new i : Kanabises)
		{
			if(areaid == KanabisData[i][kanabisArea])
			{
				ShowNotifBox(playerid, "Tekan ~y~'Y' ~w~ambil Daun Ganja");
			}
		}

		if(areaid == ProcessMarijuanaArea)
		{
			ShowNotifBox(playerid, "Tekan ~y~'Y' ~w~proses Ganja");
		}

		if(areaid == SellingMarijuanaArea)
		{
			ShowNotifBox(playerid, "Tekan ~y~'Y' ~w~jual Marijuana");
		}
	}
	return 1;
}

hook OnPlayerLeaveDynArea(playerid, areaid)
{
	foreach(new i : Kanabises)
	{
		if(areaid == KanabisData[i][kanabisArea])
		{
			HideNotifBox(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
		}
	}

	if(areaid == SellingMarijuanaArea)
	{
		HideNotifBox(playerid);
		PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
	}
	return 1;
}

hook OnPlayerEditDynObject(playerid, STREAMER_TAG_OBJECT: objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if(AccountData[playerid][EditingKanabisID] != -1 && Iter_Contains(Kanabises, AccountData[playerid][EditingKanabisID]))
	{
		if(response == EDIT_RESPONSE_FINAL)
	    {
	        new edwid = AccountData[playerid][EditingKanabisID];
	        KanabisData[edwid][kanabisPos][0] = x;
	        KanabisData[edwid][kanabisPos][1] = y;
	        KanabisData[edwid][kanabisPos][2] = z;
	        KanabisData[edwid][kanabisPos][3] = rx;
	        KanabisData[edwid][kanabisPos][4] = ry;
	        KanabisData[edwid][kanabisPos][5] = rz;

	        SetDynamicObjectPos(objectid, KanabisData[edwid][kanabisPos][0], KanabisData[edwid][kanabisPos][1], KanabisData[edwid][kanabisPos][2]);
	        SetDynamicObjectRot(objectid, KanabisData[edwid][kanabisPos][3], KanabisData[edwid][kanabisPos][4], KanabisData[edwid][kanabisPos][5]);
			Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_AREA_ID, KanabisField);

			Streamer_SetItemPos(STREAMER_TYPE_AREA, KanabisData[edwid][kanabisArea], KanabisData[edwid][kanabisPos][0], KanabisData[edwid][kanabisPos][1], KanabisData[edwid][kanabisPos][2]);
		    
			Kanabis_Save(edwid);
	        AccountData[playerid][EditingKanabisID] = -1;
	    }

	    else if(response == EDIT_RESPONSE_CANCEL)
	    {
	        new edwid = AccountData[playerid][EditingKanabisID];
	        SetDynamicObjectPos(objectid, KanabisData[edwid][kanabisPos][0], KanabisData[edwid][kanabisPos][1], KanabisData[edwid][kanabisPos][2]);
	        SetDynamicObjectRot(objectid, KanabisData[edwid][kanabisPos][3], KanabisData[edwid][kanabisPos][4], KanabisData[edwid][kanabisPos][5]);
			Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_AREA_ID, KanabisField);

			Streamer_SetItemPos(STREAMER_TYPE_AREA, KanabisData[edwid][kanabisArea], KanabisData[edwid][kanabisPos][0], KanabisData[edwid][kanabisPos][1], KanabisData[edwid][kanabisPos][2]);
	        
			AccountData[playerid][EditingKanabisID] = -1;
	    }
	}
	return 0;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		foreach(new kanabisid : Kanabises)
		{
			if(IsPlayerInDynamicArea(playerid, KanabisData[kanabisid][kanabisArea]))
			{
				if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

				if(KanabisData[kanabisid][kanabisTaken]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kanabis ini sedang diambil oleh player lain!");

				if(Iter_Count(LSPDDuty) < 4 || Iter_Count(LSFDDuty) < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal 4 polisi dan 2 Paramedis on duty!");
				if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");
				
				KanabisData[kanabisid][kanabisTaken] = true;
				AccountData[playerid][pInCannabis] = kanabisid;
				AccountData[playerid][pActivityTime] = 1;
				pTakingKanabisTimer[playerid] = true;
				PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMANEN");
				ShowProgressBar(playerid);

				OnePlayAnim(playerid, "BOMBER", "BOM_Plant", 4.0, true, false, false, true, false);

				HideNotifBox(playerid);
			}
		}

		if(IsPlayerInDynamicArea(playerid, ProcessMarijuanaArea))
		{
			if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");

			if(Iter_Count(LSPDDuty) < 4 || Iter_Count(LSFDDuty) < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal 4 polisi dan 2 Paramedis on duty!");
			if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");

			if(Inventory_Count(playerid, "Daun Ganja") < 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Daun Ganja! (Min: 3)");
			if(Inventory_Count(playerid, "Plastik") < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki cukup Plastik! (Min: 2)");

			AccountData[playerid][pActivityTime] = 1;
			pProcessKanabisTimer[playerid] = true;
			PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENGOLAH");
			ShowProgressBar(playerid);

			ApplyAnimation(playerid,"BD_FIRE","wash_up",4.1, true, false, false, false, 0, true);

			HideNotifBox(playerid);
		}
		
		if(IsPlayerInDynamicArea(playerid, SellingMarijuanaArea))
		{
			//if(AccountData[playerid][pFamily] < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari any family!");
			if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
			if(Iter_Count(LSPDDuty) < 4 || Iter_Count(LSFDDuty) < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal 4 polisi dan 2 Paramedis on duty!");
			if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");
			if(!PlayerHasItem(playerid, "Marijuana")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Marijuana untuk dijual!");

			if(DestroyDynamicActor(pDrugSellActor[playerid]))
				pDrugSellActor[playerid] = STREAMER_TAG_ACTOR: INVALID_STREAMER_ID;

			if(DestroyDynamicMapIcon(pDrugSellIcon[playerid]))
				pDrugSellIcon[playerid] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;

			if(DestroyDynamic3DTextLabel(pDrugSellLabel[playerid]))
				pDrugSellLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

			pDrugSellStep[playerid] = 1;

			new randskin = RandomEx(1, 311);
			pDrugSellChosen[playerid] = random(sizeof(g_DrugsSellActorPos));
			pDrugSellActor[playerid] = CreateDynamicActor(randskin, g_DrugsSellActorPos[pDrugSellChosen[playerid]][0], g_DrugsSellActorPos[pDrugSellChosen[playerid]][1], g_DrugsSellActorPos[pDrugSellChosen[playerid]][2], g_DrugsSellActorPos[pDrugSellChosen[playerid]][3], 1, 100.0, 0, 0, -1, 300.00, -1, 0);
			pDrugSellIcon[playerid] = CreateDynamicMapIcon(g_DrugsSellActorPos[pDrugSellChosen[playerid]][0], g_DrugsSellActorPos[pDrugSellChosen[playerid]][1], g_DrugsSellActorPos[pDrugSellChosen[playerid]][2], 23, -1, 0, 0, playerid, 155.55, MAPICON_LOCAL, -1, 0);
			pDrugSellLabel[playerid] = CreateDynamic3DTextLabel("[Y] "WHITE"Jual", Y_PAHLAWAN, g_DrugsSellActorPos[pDrugSellChosen[playerid]][0], g_DrugsSellActorPos[pDrugSellChosen[playerid]][1], g_DrugsSellActorPos[pDrugSellChosen[playerid]][2]+0.85, 30.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, playerid, 30.00, -1, 0);

			ShowTDN(playerid, NOTIFICATION_WARNING, "Mohon tanda checkpoint di map!");

			SendTeamMessage(FACTION_LSPD, 0xff4b4bff, "> Penjualan narkoba sedang berlangsung <");

			HideNotifBox(playerid);
		}
		if(pDrugSellStep[playerid] > 0 && IsPlayerInRangeOfPoint(playerid, 3.0, g_DrugsSellActorPos[pDrugSellChosen[playerid]][0], g_DrugsSellActorPos[pDrugSellChosen[playerid]][1], g_DrugsSellActorPos[pDrugSellChosen[playerid]][2]))
		{
			if(!PlayerHasItem(playerid, "Marijuana"))
			{
				pSellingMarijuanaTimer[playerid] = false;
				HideProgressBar(playerid);

				ClearAnimations(playerid, true);
				StopLoopingAnim(playerid);
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
				TogglePlayerControllable(playerid, true);

				AccountData[playerid][pActivityTime] = 0;

				if(DestroyDynamicActor(pDrugSellActor[playerid]))
					pDrugSellActor[playerid] = STREAMER_TAG_ACTOR: INVALID_STREAMER_ID;

				if(DestroyDynamicMapIcon(pDrugSellIcon[playerid]))
					pDrugSellIcon[playerid] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;

				if(DestroyDynamic3DTextLabel(pDrugSellLabel[playerid]))
					pDrugSellLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

				pDrugSellChosen[playerid] = -1;
				pDrugSellStep[playerid] = 0;   
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Marijuana untuk dijual!");
			}
			
			AccountData[playerid][pActivityTime] = 1;
            pSellingMarijuanaTimer[playerid] = true;
			PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MENJUAL");
			ShowProgressBar(playerid);

			ApplyAnimation(playerid, "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0, true);
			ApplyDynamicActorAnimation(pDrugSellActor[playerid], "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0);

			HideNotifBox(playerid);
		}
	}
	return 1;
}