#include <YSI_Coding\y_hooks>

#define MAX_DEERS 100

enum e_deerdetails
{
    Float:deerPos[6],
    
    //not save
    STREAMER_TAG_OBJECT:deerObject,
    STREAMER_TAG_3D_TEXT_LABEL:deerLabel,
    bool:deerShoted,
    bool:deerGoingConsf,
    bool:deerConsficated,
    deerRespawnTime
};
new DeerData[MAX_DEERS][e_deerdetails],
    Iterator:Deers<MAX_DEERS>,
    STREAMER_TAG_AREA:HuntingZone;

Deer_Save(deerid)
{
    new dddstr[512];
    mysql_format(g_SQL, dddstr, sizeof(dddstr), "UPDATE `dynamic_deer` SET `X`='%f', `Y`='%f', `Z`='%f', `RX`='%f', `RY`='%f', `RZ`='%f' WHERE `ID`=%d", DeerData[deerid][deerPos][0], DeerData[deerid][deerPos][1], DeerData[deerid][deerPos][2], DeerData[deerid][deerPos][3], DeerData[deerid][deerPos][4], DeerData[deerid][deerPos][5], deerid);
    mysql_pquery(g_SQL, dddstr);
	return 1;
}

Deer_Rebuild(deerid)
{
    if(deerid != -1)
    {
        if(DestroyDynamicObject(DeerData[deerid][deerObject]))
            DeerData[deerid][deerObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

        if(DestroyDynamic3DTextLabel(DeerData[deerid][deerLabel]))
            DeerData[deerid][deerLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        DeerData[deerid][deerObject] = CreateDynamicObject(19315, DeerData[deerid][deerPos][0], DeerData[deerid][deerPos][1], DeerData[deerid][deerPos][2], DeerData[deerid][deerPos][3], DeerData[deerid][deerPos][4], DeerData[deerid][deerPos][5], 0, 0, -1, 200.00, 200.00, HuntingZone);
        DeerData[deerid][deerLabel] = CreateDynamic3DTextLabel("Rusa\n"RED"Tersedia", 0xFFFFFFBF, DeerData[deerid][deerPos][0], DeerData[deerid][deerPos][1], DeerData[deerid][deerPos][2] + 1.0, 5.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 5.00, HuntingZone, 0);
    }
	return 1;
}

Deer_BeingEdited(deerid)
{
	if(!Iter_Contains(Deers, deerid)) return 0;
	foreach(new i : Player) if(AccountData[i][EditingDeerID] == deerid) return 1;
	return 0;
}

Deer_Nearest(playerid)
{
    foreach(new i : Deers) if (IsPlayerInRangeOfPoint(playerid, 3.0, DeerData[i][deerPos][0], DeerData[i][deerPos][1], DeerData[i][deerPos][2]))
	{
		if (GetPlayerInterior(playerid) == 0 && GetPlayerVirtualWorld(playerid) == 0)
			return i;
	}
	return -1;
}

task DeerRespawnTimer[1000]() 
{
    foreach(new deerid : Deers)
    {
        if(deerid != -1)
        {
            if(DeerData[deerid][deerShoted] || DeerData[deerid][deerConsficated])
            {
                if(DeerData[deerid][deerRespawnTime] > 0)
                {
                    DeerData[deerid][deerRespawnTime]--;

                    if(DeerData[deerid][deerConsficated])
                    {
                        new prms[525];
                        format(prms, sizeof(prms), "Rusa\n"RED"Tidak Tersedia\n"WHITE"%02d:%02d", DeerData[deerid][deerRespawnTime]/60%60, DeerData[deerid][deerRespawnTime]%3600%60);
                        UpdateDynamic3DTextLabelText(DeerData[deerid][deerLabel], 0xFFFFFFBF, prms);
                    }
                }
                else
                {
                    DeerData[deerid][deerRespawnTime] = 0;
                    DeerData[deerid][deerShoted] = false;
                    DeerData[deerid][deerConsficated] = false;

                    if(DestroyDynamicObject(DeerData[deerid][deerObject]))
                        DeerData[deerid][deerObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
                    
                    if(DestroyDynamic3DTextLabel(DeerData[deerid][deerLabel]))
                        DeerData[deerid][deerLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

                    DeerData[deerid][deerObject] = CreateDynamicObject(19315, DeerData[deerid][deerPos][0], DeerData[deerid][deerPos][1], DeerData[deerid][deerPos][2], DeerData[deerid][deerPos][3], DeerData[deerid][deerPos][4], DeerData[deerid][deerPos][5], 0, 0, -1, 200.00, 200.00, HuntingZone);
                    DeerData[deerid][deerLabel] = CreateDynamic3DTextLabel("Rusa\n"RED"Tersedia", 0xFFFFFFBF, DeerData[deerid][deerPos][0], DeerData[deerid][deerPos][1], DeerData[deerid][deerPos][2] + 1.0, 5.00, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 5.00, HuntingZone, 0);
                }
            }
        }
    }
	return 1;
}

forward LoadDeers();
public LoadDeers()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
 		new deerid;
		for(new i; i < rows; i++)
		{
            cache_get_value_name_int(i, "ID", deerid);
            cache_get_value_name_float(i, "X", DeerData[deerid][deerPos][0]);
            cache_get_value_name_float(i, "Y", DeerData[deerid][deerPos][1]);
            cache_get_value_name_float(i, "Z", DeerData[deerid][deerPos][2]);
            cache_get_value_name_float(i, "RX", DeerData[deerid][deerPos][3]);
            cache_get_value_name_float(i, "RY", DeerData[deerid][deerPos][4]);
            cache_get_value_name_float(i, "RZ", DeerData[deerid][deerPos][5]);
            
			Deer_Rebuild(deerid);
			Iter_Add(Deers, deerid);
        }
        printf("[Dynamic Deers] Jumlah total Deers yang dimuat: %d.", rows);
	}
	return 1;
}

forward OnDeerCreated(playerid, deerid);
public OnDeerCreated(playerid, deerid)
{
    Deer_Save(deerid);

    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s has created a Deer with ID: %d.", AccountData[playerid][pAdminname], deerid);
    return 1;
}

hook OnGameModeInit()
{
    HuntingZone = CreateDynamicRectangle(-1083.1999282836914, -2746.2003173828125, -339.1999282836914, -2120.2003173828125, 0, 0, -1);
	return 1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(areaid == HuntingZone)
    {
        SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda memasuki zona berburu, gunakan "CMDEA"'/hunt' "WHITE"untuk memasuki mode berburu.");
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(areaid == HuntingZone)
    {
        if(IsPlayerHunting[playerid])
        {
            IsPlayerHunting[playerid] = false;
            ResetWeapon(playerid, 34);
            SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda telah otomatis keluar dari mode berburu karena meninggalkan zona.");
        }
        else
        {
            SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda telah meninggalkan zona berburu.");
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        new deerid = Deer_Nearest(playerid);

        if(deerid != -1)
        {
            if(DeerData[deerid][deerShoted])
            {
                if(!DeerData[deerid][deerConsficated])
                {
                    if(GetPlayerWeaponEx(playerid) != 4) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda harus memegang pisau!");
					if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, mohon tunggu progress bar selesai!");
					if(DeerData[deerid][deerGoingConsf]) return ShowTDN(playerid, NOTIFICATION_WARNING, "Deer ini sedang digunakan oleh player lain!");
                    if(AccountData[playerid][pIsSmoking]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang merokok. Selesaikanlah atau gunakan '/stopsmoke' untuk berhenti!");
		            if(AccountData[playerid][pEatingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang makan. Selesaikanlah atau gunakan '/stopeating' untuk berhenti!");
		            if(AccountData[playerid][pDrinkingStep] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda saat ini sedang minum. Selesaikanlah atau gunakan '/stopdrinking' untuk berhenti!");

					DeerData[deerid][deerGoingConsf] = true;
					AccountData[playerid][pDuringConsficatingMeat] = deerid;
					AccountData[playerid][pActivityTime] = 1;
					pConsfMeatTimer[playerid] = true;
					PlayerTextDrawSetString(playerid, ProgressBar[playerid][1], "MEMOTONG");
					ShowProgressBar(playerid);

					OnePlayAnim(playerid, "BOMBER", "BOM_Plant", 4.0, true, false, false, true, false);
                }
            }
        }
    }
    return 1;
}

hook OnPlayerEditDynObject(playerid, STREAMER_TAG_OBJECT: objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if(AccountData[playerid][EditingDeerID] != -1 && Iter_Contains(Deers, AccountData[playerid][EditingDeerID]))
	{
		if(response == EDIT_RESPONSE_FINAL)
	    {
	        new deerid = AccountData[playerid][EditingDeerID];
	        DeerData[deerid][deerPos][0] = x;
	        DeerData[deerid][deerPos][1] = y;
	        DeerData[deerid][deerPos][2] = z;
	        DeerData[deerid][deerPos][3] = rx;
	        DeerData[deerid][deerPos][4] = ry;
	        DeerData[deerid][deerPos][5] = rz;

			SetDynamicObjectPos(objectid, DeerData[deerid][deerPos][0], DeerData[deerid][deerPos][1], DeerData[deerid][deerPos][2]);
	        SetDynamicObjectRot(objectid, DeerData[deerid][deerPos][3], DeerData[deerid][deerPos][4], DeerData[deerid][deerPos][5]);
			
            Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, DeerData[deerid][deerLabel], DeerData[deerid][deerPos][0], DeerData[deerid][deerPos][1], DeerData[deerid][deerPos][2] + 1.0);
		    
            Deer_Save(deerid);
	        AccountData[playerid][EditingDeerID] = -1;
	    }

	    else if(response == EDIT_RESPONSE_CANCEL)
	    {
	        new deerid = AccountData[playerid][EditingDeerID];
	        SetDynamicObjectPos(objectid, DeerData[deerid][deerPos][0], DeerData[deerid][deerPos][1], DeerData[deerid][deerPos][2]);
	        SetDynamicObjectRot(objectid, DeerData[deerid][deerPos][3], DeerData[deerid][deerPos][4], DeerData[deerid][deerPos][5]);
	        AccountData[playerid][EditingDeerID] = -1;
	    }
	}
	return 0;
}

hook OnPlayerShootDynObject(playerid, weaponid, STREAMER_TAG_OBJECT:objectid, Float:x, Float:y, Float:z)
{
    foreach(new deerid : Deers)
    {
        if(deerid != -1)
        {
            if(objectid == DeerData[deerid][deerObject])
            {
                if(IsPlayerHunting[playerid] && weaponid == 34)
                {
                    if(!DeerData[deerid][deerShoted])
                    {
						new randevent = Random(100);
						switch(randevent)
						{
							case 0.. 89: //aman
							{
								DeerData[deerid][deerShoted] = true;
								DeerData[deerid][deerRespawnTime] = 100;

								Streamer_SetFloatData(STREAMER_TYPE_OBJECT, DeerData[deerid][deerObject], E_STREAMER_R_X, 90);
								//Streamer_SetFloatData(STREAMER_TYPE_OBJECT, DeerData[i][deerObject], E_STREAMER_Z, -0.02);

								UpdateDynamic3DTextLabelText(DeerData[deerid][deerLabel], 0xFFFFFFBF, "Rusa\n"YELLOW"Tertembak\n"WHITE"Tekan "GREEN"Y "WHITE"untuk memotong daging");
							}
							case 90.. 99: //beruang
							{
								DeerData[deerid][deerShoted] = true;
								DeerData[deerid][deerRespawnTime] = 100;

								Streamer_SetFloatData(STREAMER_TYPE_OBJECT, DeerData[deerid][deerObject], E_STREAMER_R_X, 90);
								//Streamer_SetFloatData(STREAMER_TYPE_OBJECT, DeerData[i][deerObject], E_STREAMER_Z, -0.02);

								UpdateDynamic3DTextLabelText(DeerData[deerid][deerLabel], 0xFFFFFFBF, "Rusa\n"YELLOW"Tertembak\n"WHITE"Tekan "GREEN"Y "WHITE"untuk memotong daging");

								static Float:randhealth, Float:currhealth, Float:healthresult, string[144];
								GetPlayerHealth(playerid, currhealth);
								randhealth = RandomFloat(10.0, 20.0, 2);
								healthresult = currhealth-randhealth;
								if(healthresult < 0) healthresult = 0.0;

								format(string, sizeof(string), "[Server] Suara tembakan anda menarik perhatian beruang, dan kamu terkena damage (DMG: %.2f).", randhealth);
								SendClientMessage(playerid, 0xFF00FFAA, string);
								SetPlayerHealthEx(playerid, healthresult);
							}
							case 100: //roger sumatera
							{
								DeerData[deerid][deerShoted] = true;
								DeerData[deerid][deerRespawnTime] = 100;

								Streamer_SetFloatData(STREAMER_TYPE_OBJECT, DeerData[deerid][deerObject], E_STREAMER_R_X, 90);
								//Streamer_SetFloatData(STREAMER_TYPE_OBJECT, DeerData[i][deerObject], E_STREAMER_Z, -0.02);

								UpdateDynamic3DTextLabelText(DeerData[deerid][deerLabel], 0xFFFFFFBF, "Rusa\n"YELLOW"Tertembak\n"WHITE"Tekan "GREEN"Y "WHITE"untuk memotong daging");

								SendClientMessage(playerid, Y_PAHLAWAN, "<!> "WHITE"Anda diserang secara brutal oleh roger sumatera dan pingsan.");
								SetPlayerHealth(playerid, 0.0);
							}
						}
					}
                }
            }
        }
    }
    return 1;
}