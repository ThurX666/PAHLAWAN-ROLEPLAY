#include <YSI_Coding\y_hooks>

#define MAX_SHOPS 100

enum E_SHOP
{
    shopType,
    shopBizID,
    Float:shopPos[3],
    shopVw,
    shopInt,

    //not save
    STREAMER_TAG_PICKUP:shopPickup,
    STREAMER_TAG_3D_TEXT_LABEL:shopLabel,
    STREAMER_TAG_MAP_ICON:shopIcon
};
new ShopData[MAX_SHOPS][E_SHOP],
    Iterator:Shops<MAX_SHOPS>;
new bool:PlayerShopGlobalIcons[MAX_PLAYERS];

Shop_GetMapIconType(sid)
{
    switch(ShopData[sid][shopType])
    {
        case 1: return 17;
        case 2: return 45;
        case 3: return 48;
        case 4: return 6;
    }
    return 0;
}

Shop_HideGlobalMapIcons(playerid)
{
    for(new sid; sid < MAX_SHOPS; sid++)
    {
        RemovePlayerMapIcon(playerid, sid);
    }
    PlayerShopGlobalIcons[playerid] = false;
    return 1;
}

Shop_ShowGlobalMapIcons(playerid)
{
    new count;
    Shop_HideGlobalMapIcons(playerid);

    foreach(new sid : Shops)
    {
        new markerType = Shop_GetMapIconType(sid);
        if(!markerType) continue;

        SetPlayerMapIcon(playerid, sid, ShopData[sid][shopPos][0], ShopData[sid][shopPos][1], ShopData[sid][shopPos][2], markerType, 0, MAPICON_GLOBAL);
        count++;
    }

    PlayerShopGlobalIcons[playerid] = count > 0;
    return count;
}

Shop_GetByBizID(bizid, ignoreid = -1)
{
    foreach(new sid : Shops)
    {
        if(sid == ignoreid) continue;
        if(ShopData[sid][shopBizID] == bizid)
        {
            return sid;
        }
    }
    return -1;
}

Shop_Nearest(playerid)
{
    foreach(new i : Shops) if (IsPlayerInRangeOfPoint(playerid, 3.0, ShopData[i][shopPos][0], ShopData[i][shopPos][1], ShopData[i][shopPos][2]))
	{
		if (GetPlayerInterior(playerid) == ShopData[i][shopInt] && GetPlayerVirtualWorld(playerid) == ShopData[i][shopVw])
			return i;
	}
	return -1;
}

GetShopNearestFromPlayer(playerid, type)
{
    foreach(new x : Shops)
    {
        if(ShopData[x][shopInt] == 0 && ShopData[x][shopVw] == 0 && ShopData[x][shopType] == type)
        {
            if(IsPlayerInRangeOfPoint(playerid, 600.0, ShopData[x][shopPos][0], ShopData[x][shopPos][1], ShopData[x][shopPos][2]))
            {
                if(DestroyDynamicRaceCP(AccountData[playerid][pGPSCP]))
                    AccountData[playerid][pGPSCP] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;

                AccountData[playerid][pUsingGPS] = true;
                AccountData[playerid][pGPSCP] = CreateDynamicRaceCP(1, ShopData[x][shopPos][0], ShopData[x][shopPos][1], ShopData[x][shopPos][2], ShopData[x][shopPos][0], ShopData[x][shopPos][1], ShopData[x][shopPos][2], 3.5, 0, 0, playerid, 10000.00, -1, 0);
                ShowTDN(playerid, NOTIFICATION_WARNING, "Mohon ikuti checkpoint di map!");
                return 1;
            }
        }
    }
    ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada shop terdekat dari lokasi anda!");
    return 1;
}

Shop_Refresh(sid)
{
    if(sid != -1)
    {
        Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, ShopData[sid][shopLabel], ShopData[sid][shopPos][0], ShopData[sid][shopPos][1], ShopData[sid][shopPos][2] + 0.65);
        Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, ShopData[sid][shopLabel], E_STREAMER_WORLD_ID, ShopData[sid][shopVw]);
		Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, ShopData[sid][shopLabel], E_STREAMER_INTERIOR_ID, ShopData[sid][shopInt]);

        Streamer_SetItemPos(STREAMER_TYPE_MAP_ICON, ShopData[sid][shopIcon], ShopData[sid][shopPos][0], ShopData[sid][shopPos][1], ShopData[sid][shopPos][2]);
        Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, ShopData[sid][shopIcon], E_STREAMER_WORLD_ID, ShopData[sid][shopVw]);
		Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, ShopData[sid][shopIcon], E_STREAMER_INTERIOR_ID, ShopData[sid][shopInt]);

        Streamer_SetItemPos(STREAMER_TYPE_PICKUP, ShopData[sid][shopPickup], ShopData[sid][shopPos][0], ShopData[sid][shopPos][1], ShopData[sid][shopPos][2]);
        Streamer_SetIntData(STREAMER_TYPE_PICKUP, ShopData[sid][shopPickup], E_STREAMER_WORLD_ID, ShopData[sid][shopVw]);
		Streamer_SetIntData(STREAMER_TYPE_PICKUP, ShopData[sid][shopPickup], E_STREAMER_INTERIOR_ID, ShopData[sid][shopInt]);

        switch(ShopData[sid][shopType])
        {
            case 1:
            {
                Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, ShopData[sid][shopIcon], E_STREAMER_TYPE, 17);
                Streamer_SetIntData(STREAMER_TYPE_PICKUP, ShopData[sid][shopPickup], E_STREAMER_MODEL_ID, 2992);
            }
            case 2:
            {
                Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, ShopData[sid][shopIcon], E_STREAMER_TYPE, 45);
                Streamer_SetIntData(STREAMER_TYPE_PICKUP, ShopData[sid][shopPickup], E_STREAMER_MODEL_ID, 1275);
            }
            case 3:
            {
                Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, ShopData[sid][shopIcon], E_STREAMER_TYPE, 48);
                Streamer_SetIntData(STREAMER_TYPE_PICKUP, ShopData[sid][shopPickup], E_STREAMER_MODEL_ID, 1277);
            }
            case 4:
            {
                Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, ShopData[sid][shopIcon], E_STREAMER_TYPE, 6);
                Streamer_SetIntData(STREAMER_TYPE_PICKUP, ShopData[sid][shopPickup], E_STREAMER_MODEL_ID, 1242);
            }
        }
    }
}

Shop_Rebuild(sid)
{
    if(sid != -1)
    {
        ShopData[sid][shopLabel] = CreateDynamic3DTextLabel(sprintf("{00FFFF}[id:%d]\n"GREEN"[Y] "WHITE"untuk akses katalog", sid), 0x00FF00A6, ShopData[sid][shopPos][0], ShopData[sid][shopPos][1], ShopData[sid][shopPos][2] + 0.65, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, ShopData[sid][shopVw], ShopData[sid][shopInt], -1, 10.0, -1, 0);
        
        switch(ShopData[sid][shopType])
        {
            case 1:
            {
                ShopData[sid][shopIcon] = CreateDynamicMapIcon(ShopData[sid][shopPos][0], ShopData[sid][shopPos][1], ShopData[sid][shopPos][2], 17, 0, ShopData[sid][shopVw], ShopData[sid][shopInt], -1, 1000.00, MAPICON_LOCAL, -1, 0);
                ShopData[sid][shopPickup] = CreateDynamicPickup(2992, 23, ShopData[sid][shopPos][0], ShopData[sid][shopPos][1], ShopData[sid][shopPos][2], ShopData[sid][shopVw], ShopData[sid][shopInt], -1, 5.5,-1, 0);
            }
            case 2:
            {
                ShopData[sid][shopIcon] = CreateDynamicMapIcon(ShopData[sid][shopPos][0], ShopData[sid][shopPos][1], ShopData[sid][shopPos][2], 45, 0, ShopData[sid][shopVw], ShopData[sid][shopInt], -1, 1000.00, MAPICON_LOCAL, -1, 0);
                ShopData[sid][shopPickup] = CreateDynamicPickup(1275, 23, ShopData[sid][shopPos][0], ShopData[sid][shopPos][1], ShopData[sid][shopPos][2], ShopData[sid][shopVw], ShopData[sid][shopInt], -1, 5.5,-1, 0);
            }
            case 3:
            {
                ShopData[sid][shopIcon] = CreateDynamicMapIcon(ShopData[sid][shopPos][0], ShopData[sid][shopPos][1], ShopData[sid][shopPos][2], 48, 0, ShopData[sid][shopVw], ShopData[sid][shopInt], -1, 1000.00, MAPICON_LOCAL, -1, 0);
                ShopData[sid][shopPickup] = CreateDynamicPickup(1277, 23, ShopData[sid][shopPos][0], ShopData[sid][shopPos][1], ShopData[sid][shopPos][2], ShopData[sid][shopVw], ShopData[sid][shopInt], -1, 5.5,-1, 0);
            }
            case 4:
            {
                ShopData[sid][shopIcon] = CreateDynamicMapIcon(ShopData[sid][shopPos][0], ShopData[sid][shopPos][1], ShopData[sid][shopPos][2], 6, 0, ShopData[sid][shopVw], ShopData[sid][shopInt], -1, 1000.00, MAPICON_LOCAL, -1, 0);
                ShopData[sid][shopPickup] = CreateDynamicPickup(1242, 23, ShopData[sid][shopPos][0], ShopData[sid][shopPos][1], ShopData[sid][shopPos][2], ShopData[sid][shopVw], ShopData[sid][shopInt], -1, 5.5,-1, 0);
            }
        }
    }
}

Shop_Save(sid)
{
    new dquery[522];
	mysql_format(g_SQL, dquery, sizeof(dquery), "UPDATE `shops` SET `type`=%d, `bizID`=%d, `shopX`='%f', `shopY`='%f', `shopZ`='%f', `shopVw`=%d, `shopInt`=%d WHERE `ID`= %d",
	ShopData[sid][shopType], ShopData[sid][shopBizID], ShopData[sid][shopPos][0], ShopData[sid][shopPos][1], ShopData[sid][shopPos][2], ShopData[sid][shopVw], ShopData[sid][shopInt], sid);
	mysql_pquery(g_SQL, dquery);
}

forward OnShopsCreated(playerid, sid);
public OnShopsCreated(playerid, sid)
{
	Shop_Save(sid);
    SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s membuat shop dengan ID: %d.", AccountData[playerid][pAdminname], sid);
	return 1;
}

forward LoadShops();
public LoadShops()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
   		new sid;
		for(new i; i < rows; i++)
		{
  			cache_get_value_name_int(i, "ID", sid);
		    cache_get_value_name_int(i, "type", ShopData[sid][shopType]);
		    cache_get_value_name_int(i, "bizID", ShopData[sid][shopBizID]);
		    cache_get_value_name_float(i, "shopX", ShopData[sid][shopPos][0]);
		    cache_get_value_name_float(i, "shopY", ShopData[sid][shopPos][1]);
		    cache_get_value_name_float(i, "shopZ", ShopData[sid][shopPos][2]);
		    cache_get_value_name_int(i, "shopVw", ShopData[sid][shopVw]);
		    cache_get_value_name_int(i, "shopInt", ShopData[sid][shopInt]);
			
			Shop_Rebuild(sid);
			Iter_Add(Shops, sid);
	    }
	    printf("[Dynamic Shops] Jumlah total Shops yang dimuat: %d.", rows);
	}
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(!AccountData[playerid][pKnockdown])
		{
            foreach(new sid : Shops)
            {
                if(IsPlayerInRangeOfPoint(playerid, 2.0, ShopData[sid][shopPos][0], ShopData[sid][shopPos][1], ShopData[sid][shopPos][2]))
                {
                    if(ShopData[sid][shopBizID] != -1)
                    {
                        if(!Iter_Contains(Bizes, ShopData[sid][shopBizID])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Bisnis yang terhubung dengan shop ini tidak valid!");

                        PlayerShopBizID[playerid] = ShopData[sid][shopBizID];
                        return Biz_ShowProductMenu(playerid, ShopData[sid][shopBizID]);
                    }

                    switch(ShopData[sid][shopType])
                    {
                        case 1: //minimarket
                        {
                            Dialog_Show(playerid, "ShopCatalog", DIALOG_STYLE_TABLIST_HEADERS, sprintf("{DA9100}Pahlawan Roleplay "WHITE"- 24/7 Shop.%d", sid), 
                            "Nama Item\tHarga\n\
                            Nasi Uduk\t$650\n\
                            "GRAY"Air Mineral\t"GRAY"$650\n\
                            Skateboard\t$870\n\
                            "GRAY"Perban\t"GRAY"$360\n\
                            Udud (12 batang)\t$310\n\
                            "GRAY"Baseball Bat\t"GRAY"$950\n\
                            Knife\t$950\n\
                            "GRAY"Golf Stick\t"GRAY"$950\n\
                            Pool Cue\t$950\n\
                            "GRAY"Hunting Rifle\t"GRAY"$1,200\n\
                            Hunting Ammo (24x)\t$700\n\
                            "GRAY"Obeng\t"GRAY"$620\n\
                            Pilox\t$780\n\
                            "GRAY"Senter\t"GRAY"$520\n\
                            Cangkul\t$500\n\
                            "GRAY"Pancingan\t"GRAY"$980\n\
                            Umpan\t$100\n\
                            "GRAY"Ember\t"GRAY"$500", "Beli", "Batal");
                        }
                        case 2: //clothes
                        {
                            ShowClothesMainMenuTD(playerid);
                        }
                        case 3: //electronic
                        {
                            Dialog_Show(playerid, "ElectronicCatalog", DIALOG_STYLE_TABLIST_HEADERS, sprintf("{DA9100}Pahlawan Roleplay "WHITE"- 24/7 Shop.%d", sid), 
                            "Nama Item\tHarga\n\
                            Arivhone (Smartphone)\t$2,105\n\
                            "GRAY"Radio\t"GRAY"$2,000\n\
                            Earphone\t$1,800\n\
                            "GRAY"Boombox\t"GRAY"$3,690\n\
                            Vape\t$6,300", "Beli", "Batal");
                        }
                        case 4: //ammunation
                        {
                            if(AccountData[playerid][pFirearmLicTime] == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Carry Concealed Weapon License!");
                            
                            Dialog_Show(playerid, "AmmunationCatalog", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Ammunation", 
                            "Nama Item\tPeluru\tHarga\n\
                            Katana\t-\t$46,500\n\
                            "GRAY"Colt 45\t"GRAY"250\t"GRAY"$155,000\n\
                            Silenced Pistol\t250\t$155,000\n\
                            "GRAY"Desert Eagle\t"GRAY"250\t"GRAY"$180,000\n\
                            Shotgun\t350\t$285,000\n\
                            "GRAY"Uzi\t"GRAY"500\t"GRAY"$267,000\n\
                            MP5\t500\t$426,000\n\
                            "GRAY"Tec 9\t"GRAY"500\t"GRAY"$267,000", "Beli", "Batal");
                        }
                    }
                }
            }
        }
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    PlayerShopGlobalIcons[playerid] = false;
    return 1;
}
