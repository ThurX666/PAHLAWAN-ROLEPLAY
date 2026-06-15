#include <YSI_Coding\y_hooks>

#define MAX_ROBBERY 100

enum e_RobberySafeDetails
{
    Float:rsafePos[6],
    rsafeWorld,
    rsafeInterior,

    //not save
    STREAMER_TAG_OBJECT:rsafeObject
};
new RobberyData[MAX_ROBBERY][e_RobberySafeDetails],
    Iterator:Robberies<MAX_ROBBERY>,
    RobberyCountdown[MAX_PLAYERS];

Robbery_Nearest(playerid)
{
    foreach(new i : Robberies) if (IsPlayerInRangeOfPoint(playerid, 3.0, RobberyData[i][rsafePos][0], RobberyData[i][rsafePos][1], RobberyData[i][rsafePos][2]))
	{
		if (GetPlayerInterior(playerid) == RobberyData[i][rsafeInterior] && GetPlayerVirtualWorld(playerid) == RobberyData[i][rsafeWorld])
			return i;
	}
	return -1;
}

Robbery_BeingEdited(rbid)
{
	if(!Iter_Contains(Robberies, rbid)) return 0;
	foreach(new i : Player) if(AccountData[i][EditingRobberyID] == rbid) return 1;
	return 0;
}

Robbery_Save(rbid)
{
    new frmtsvrb[528];
    mysql_format(g_SQL, frmtsvrb, sizeof(frmtsvrb), "UPDATE `robberies` SET `Robbery_X`='%f', `Robbery_Y`='%f', `Robbery_Z`='%f', `Robbery_RX`='%f', `Robbery_RY`='%f', `Robbery_RZ`='%f', `Robbery_World`=%d, `Robbery_Interior`=%d WHERE `ID`=%d",
    RobberyData[rbid][rsafePos][0], RobberyData[rbid][rsafePos][1], RobberyData[rbid][rsafePos][2], RobberyData[rbid][rsafePos][3], RobberyData[rbid][rsafePos][4], RobberyData[rbid][rsafePos][5], RobberyData[rbid][rsafeWorld], RobberyData[rbid][rsafeInterior], rbid);
    mysql_pquery(g_SQL, frmtsvrb);
}

Robbery_Refresh(rbid)
{
    if(rbid != -1)
    {
        SetDynamicObjectPos(RobberyData[rbid][rsafeObject], RobberyData[rbid][rsafePos][0], RobberyData[rbid][rsafePos][1], RobberyData[rbid][rsafePos][2]);
	    SetDynamicObjectRot(RobberyData[rbid][rsafeObject], RobberyData[rbid][rsafePos][3], RobberyData[rbid][rsafePos][4], RobberyData[rbid][rsafePos][5]);
	    Streamer_SetIntData(STREAMER_TYPE_OBJECT, RobberyData[rbid][rsafeObject], E_STREAMER_WORLD_ID, RobberyData[rbid][rsafeWorld]);
	    Streamer_SetIntData(STREAMER_TYPE_OBJECT, RobberyData[rbid][rsafeObject], E_STREAMER_INTERIOR_ID, RobberyData[rbid][rsafeInterior]);
    }
}

Robbery_Rebuild(rbid)
{
    if(rbid != -1)
    {
        if(DestroyDynamicObject(RobberyData[rbid][rsafeObject]))
		    RobberyData[rbid][rsafeObject] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;

        RobberyData[rbid][rsafeObject] = CreateDynamicObject(2332, RobberyData[rbid][rsafePos][0], RobberyData[rbid][rsafePos][1], RobberyData[rbid][rsafePos][2], RobberyData[rbid][rsafePos][3], RobberyData[rbid][rsafePos][4], RobberyData[rbid][rsafePos][5], RobberyData[rbid][rsafeWorld], RobberyData[rbid][rsafeInterior], -1, 30.00, 30.00, -1);
    }
}

forward LoadRobberies();
public LoadRobberies()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
 		new rbid;
		for(new i; i < rows; i++)
		{
            cache_get_value_name_int(i, "ID", rbid);
            cache_get_value_name_float(i, "Robbery_X", RobberyData[rbid][rsafePos][0]);
            cache_get_value_name_float(i, "Robbery_Y", RobberyData[rbid][rsafePos][1]);
            cache_get_value_name_float(i, "Robbery_Z", RobberyData[rbid][rsafePos][2]);
            cache_get_value_name_float(i, "Robbery_RX", RobberyData[rbid][rsafePos][3]);
            cache_get_value_name_float(i, "Robbery_RY", RobberyData[rbid][rsafePos][4]);
            cache_get_value_name_float(i, "Robbery_RZ", RobberyData[rbid][rsafePos][5]);
            cache_get_value_name_int(i, "Robbery_World", RobberyData[rbid][rsafeWorld]);
            cache_get_value_name_int(i, "Robbery_Interior", RobberyData[rbid][rsafeInterior]);
            
			Robbery_Rebuild(rbid);
			Iter_Add(Robberies, rbid);
        }
        printf("[Dynamic Robberies] Jumlah total Robberies yang dimuat: %d.", rows);
	}
}

forward OnRobberyCreated(playerid, rbid);
public OnRobberyCreated(playerid, rbid)
{
    Robbery_Save(rbid);

    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s membuat Robbery dengan ID: %d.", AccountData[playerid][pAdminname], rbid);
    return 1;
}

hook OnPlayerEditDynObject(playerid, STREAMER_TAG_OBJECT: objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if(AccountData[playerid][EditingRobberyID] != -1 && Iter_Contains(Robberies, AccountData[playerid][EditingRobberyID]))
	{
		if(response == EDIT_RESPONSE_FINAL)
	    {
	        new rbid = AccountData[playerid][EditingRobberyID];
	        RobberyData[rbid][rsafePos][0] = x;
	        RobberyData[rbid][rsafePos][1] = y;
	        RobberyData[rbid][rsafePos][2] = z;
	        RobberyData[rbid][rsafePos][3] = rx;
	        RobberyData[rbid][rsafePos][4] = ry;
	        RobberyData[rbid][rsafePos][5] = rz;

			SetDynamicObjectPos(objectid, RobberyData[rbid][rsafePos][0], RobberyData[rbid][rsafePos][1], RobberyData[rbid][rsafePos][2]);
	        SetDynamicObjectRot(objectid, RobberyData[rbid][rsafePos][3], RobberyData[rbid][rsafePos][4], RobberyData[rbid][rsafePos][5]);
			
		    Robbery_Save(rbid);
	        AccountData[playerid][EditingRobberyID] = -1;
	    }

	    else if(response == EDIT_RESPONSE_CANCEL)
	    {
	        new rbid = AccountData[playerid][EditingRobberyID];
	        SetDynamicObjectPos(objectid, RobberyData[rbid][rsafePos][0], RobberyData[rbid][rsafePos][1], RobberyData[rbid][rsafePos][2]);
	        SetDynamicObjectRot(objectid, RobberyData[rbid][rsafePos][3], RobberyData[rbid][rsafePos][4], RobberyData[rbid][rsafePos][5]);
	        AccountData[playerid][EditingRobberyID] = -1;
	    }
	}
	return 0;
}

hook OnPlayerShootDynObject(playerid, weaponid, STREAMER_TAG_OBJECT:objectid, Float:x, Float:y, Float:z)
{
    foreach(new rbid : Robberies)
    {
        if(objectid == RobberyData[rbid][rsafeObject])
        {
            if(IsPlayerConnected(playerid) && AccountData[playerid][IsLoggedIn] && AccountData[playerid][pSpawned])
            {
                if(GetPlayerWeaponEx(playerid) >= 22 && GetPlayerWeaponEx(playerid) <= 42)
                {
                    if(AccountData[playerid][pDuringRobbery]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang dalam perampokan, mohon tunggu!");
                    if(GM[ShopRobberyOngoing]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat melakukannya saat ini, ada perampokan warung yang sedang berlangsung!");
                    if(gettime() < GM[ShopRobberyCooldown]) return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Perampokan warung masih dalam cooldown selama %d menit", (GM[ShopRobberyCooldown] - gettime())/60));

                    if(Iter_Count(LSPDDuty) < 4 || Iter_Count(LSFDDuty) < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "4 polisi dan 2 paramedis on duty!");
                    if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mencapai setidaknya level 5 karakter!");
                    
                    GM[ShopRobberyOngoing] = true;
                    RobberyCountdown[playerid] = 600;

                    AccountData[playerid][pDuringRobbery] = true;
                    AccountData[playerid][pInRobberyID] = rbid;

                    ShowRobberyTD(playerid);

                    foreach(new i : Player)
                    {
                        if(AccountData[i][pOnDuty] && AccountData[i][pFaction] == FACTION_LSPD)
                        {
                            ShowFivemNotify(i, "Pahlawan Roleplay~n~BREAKING NEWS", sprintf("Telah terjadi perampokan warung di %s.", GetLocation(RobberyData[rbid][rsafePos][0], RobberyData[rbid][rsafePos][1], RobberyData[rbid][rsafePos][2])), "hud:radar_emmetGun");

                            if(DestroyDynamicMapIcon(AccountData[playerid][pSignalRobberyIcon][i]))
						        AccountData[playerid][pSignalRobberyIcon][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;

                            AccountData[playerid][pSignalRobberyIcon][i] = CreateDynamicMapIcon(RobberyData[rbid][rsafePos][0], RobberyData[rbid][rsafePos][1], RobberyData[rbid][rsafePos][2], 0, 0xFF99A4FF, 0, 0, i, 10000.00, MAPICON_GLOBAL, -1, 0);
                        }
                    }
                    SendClientMessageToAllEx(Y_YELLOW, "[Perampokan] "WHITE"Telah terjadi perampokan warung di %s, warga harap menjauh!", GetLocation(RobberyData[rbid][rsafePos][0], RobberyData[rbid][rsafePos][1], RobberyData[rbid][rsafePos][2]));
                }
            }
        }
    }   
    return 1;
}

ptask RobCountdownUpdate[1000](playerid) 
{
    if(IsPlayerConnected(playerid) && AccountData[playerid][IsLoggedIn] && AccountData[playerid][pSpawned] && AccountData[playerid][pDuringRobbery])
    {
        if(RobberyCountdown[playerid] > 0)
        {
            RobberyCountdown[playerid]--;
            
            PlayerTextDrawSetString(playerid, perampokanTD[playerid], sprintf("Mohon tetap di toko selama %d menit %02d detik", RobberyCountdown[playerid]/60, RobberyCountdown[playerid] % 3600 % 60));

            if(!IsPlayerInRangeOfPoint(playerid, 25.00, RobberyData[AccountData[playerid][pInRobberyID]][rsafePos][0], RobberyData[AccountData[playerid][pInRobberyID]][rsafePos][1], RobberyData[AccountData[playerid][pInRobberyID]][rsafePos][2]))
            {
                GM[ShopRobberyOngoing] = false;
                RobberyCountdown[playerid] = 0;
                GM[ShopRobberyCooldown] = gettime() + 1200;

                AccountData[playerid][pDuringRobbery] = false;
                AccountData[playerid][pInRobberyID] = -1;

                HideRobberyTD(playerid);

                ShowFivemNotify(playerid, "SHOP BURGLARY", "Perampokan toko gagal, anda terlalu jauh dari toko!", "hud:radar_emmetGun", 25);

                foreach(new x : LSPDDuty)
                {
                    if(DestroyDynamicMapIcon(AccountData[playerid][pSignalRobberyIcon][x]))
                        AccountData[playerid][pSignalRobberyIcon][x] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
                }
            }
        }
        else
        {
            GM[ShopRobberyOngoing] = false;
            RobberyCountdown[playerid] = 0;
            GM[ShopRobberyCooldown] = gettime() + 1200;

            AccountData[playerid][pDuringRobbery] = false;
            AccountData[playerid][pInRobberyID] = -1;

            new randcash = RandomEx(16800, 22000);
            GivePlayerDirtyMoney(playerid, randcash);

            ShowItemBox(playerid, "Dirty Money", sprintf("Received $%sx", FormatMoney(randcash)), 1550, 5);

            new randevent = random(100);
            switch(randevent)
            {
                case 80.. 99:
                {
                    Inventory_Add(playerid, "Alat Hack", 19893);
                    ShowItemBox(playerid, "Alat Hack", "Received 1x", 19893, 5);
                }
            }

            ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Anda mendapatkan hasil rampokan sejumlah ~r~+$%s.", FormatMoney(randcash)));

            HideRobberyTD(playerid);

            foreach(new x : LSPDDuty)
            {
                if(DestroyDynamicMapIcon(AccountData[playerid][pSignalRobberyIcon][x]))
                    AccountData[playerid][pSignalRobberyIcon][x] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
        }
    }
    return 1;
}