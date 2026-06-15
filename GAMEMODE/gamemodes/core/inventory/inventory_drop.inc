#include <YSI_Coding\y_hooks>

#define MAX_DROPPED_ITEMS  1000
#define MAX_LISTED_ITEMS  10

new NearestItems[MAX_PLAYERS][MAX_LISTED_ITEMS];
enum droppedItems
{
	droppedID,
	droppedItem[32],
	droppedPlayer[24],
	droppedModel,
	droppedQuantity,
	Float:droppedPos[3],
	droppedWeapon,
	droppedAmmo,
	droppedInt,
	droppedWorld,
	droppedTime,
	STREAMER_TAG_OBJECT:droppedObject,
	STREAMER_TAG_3D_TEXT_LABEL:droppedText3D
};

new DroppedItems[MAX_DROPPED_ITEMS][droppedItems];

Item_Delete(itemid)
{
    new
	    query[512];

    if (itemid != -1 && DroppedItems[itemid][droppedModel])
	{
        DroppedItems[itemid][droppedModel] = 0;
		DroppedItems[itemid][droppedQuantity] = 0;
	    DroppedItems[itemid][droppedPos][0] = 0.0;
	    DroppedItems[itemid][droppedPos][1] = 0.0;
	    DroppedItems[itemid][droppedPos][2] = 0.0;
	    DroppedItems[itemid][droppedInt] = 0;
	    DroppedItems[itemid][droppedWorld] = 0;
		DroppedItems[itemid][droppedTime] = 0;

		if(DestroyDynamicObject(DroppedItems[itemid][droppedObject]))
			DroppedItems[itemid][droppedObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

		if(DestroyDynamic3DTextLabel(DroppedItems[itemid][droppedText3D]))
			DroppedItems[itemid][droppedText3D] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

	    mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `dropped_items` WHERE `ID` = %d", DroppedItems[itemid][droppedID]);
	    mysql_pquery(g_SQL, query);
	}
	return 1;
}

Item_Nearest(playerid)
{
    for (new i = 0; i != MAX_DROPPED_ITEMS; i ++) if (DroppedItems[i][droppedModel] && IsPlayerInRangeOfPoint(playerid, 1.5, DroppedItems[i][droppedPos][0], DroppedItems[i][droppedPos][1], DroppedItems[i][droppedPos][2]))
	{
	    if (GetPlayerInterior(playerid) == DroppedItems[i][droppedInt] && GetPlayerVirtualWorld(playerid) == DroppedItems[i][droppedWorld])
	        return i;
	}
	return -1;
}

Item_Drop(item[], player[], model, quantity, Float:x, Float:y, Float:z, interior, world, weaponid = 0, ammo = 0) //dicall kedua
{
	new
		ditstr[128],
	    query[300],
		droppedformat,
		droppedweights[32];

	for(new i; i < MAX_DROPPED_ITEMS; i++) if (!DroppedItems[i][droppedModel])
	{
		strcopy(DroppedItems[i][droppedItem], item, 32);
	    strcopy(DroppedItems[i][droppedPlayer], player, 24);

		DroppedItems[i][droppedModel] = model;
		DroppedItems[i][droppedQuantity] = quantity;
		DroppedItems[i][droppedWeapon] = weaponid;
  		DroppedItems[i][droppedAmmo] = ammo;
		DroppedItems[i][droppedPos][0] = x;
		DroppedItems[i][droppedPos][1] = y;
		DroppedItems[i][droppedPos][2] = z;

		DroppedItems[i][droppedInt] = interior;
		DroppedItems[i][droppedWorld] = world;
		
		DroppedItems[i][droppedTime] = gettime() + 1800;
		DroppedItems[i][droppedObject] = CreateDynamicObject(2663, x, y, z, 0.0, 0.0, 0.0, world, interior);
		
		droppedformat = GetItemWeight(DroppedItems[i][droppedItem]) * DroppedItems[i][droppedQuantity];
		strcopy(droppedweights, FormatInventoryDigit(droppedformat));

		format(ditstr, sizeof(ditstr), "%s | %dx | (%s kg)", DroppedItems[i][droppedItem], DroppedItems[i][droppedQuantity], droppedweights);
		DroppedItems[i][droppedText3D] = CreateDynamic3DTextLabel(ditstr, -1, x, y, z + 0.5, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, world, interior, -1, 10.0, -1, 0);

 		mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `dropped_items` (`itemName`, `itemPlayer`, `itemModel`, `itemQuantity`, `itemWeapon`, `itemAmmo`, `itemX`, `itemY`, `itemZ`, `itemInt`, `itemWorld`, `itemTime`) VALUES('%e', '%e', %d, %d, %d, %d, '%.4f', '%.4f', '%.4f', %d, %d, %d)", item, player, model, quantity, weaponid, ammo, x, y, z, interior, world, DroppedItems[i][droppedTime]);
		mysql_pquery(g_SQL, query, "OnDroppedItem", "d", i);
		return i;
	}
	return -1;
}

DropPlayerItem(playerid, itemid, quantity = 1) //dicall pertama
{
	if (itemid == -1 || !InventoryData[playerid][itemid][invExists])
	    return 0;

    new
		Float:x,
  		Float:y,
    	Float:z,
		Float:angle,
		string[32];

	strunpack(string, InventoryData[playerid][itemid][invItem]);

	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, angle);

	ShowItemBox(playerid, string, sprintf("Removed %dx", quantity), InventoryData[playerid][itemid][invModel], 5);
	Item_Drop(string, AccountData[playerid][pName], InventoryData[playerid][itemid][invModel], quantity, x, y, z - 0.75, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
 	Inventory_Remove(playerid, string, quantity);

	if(!strcmp(string, "Hunt Ammo"))
	{
		if(IsPlayerHunting[playerid])
		{
			ResetWeapon(playerid, 34);
			if(PlayerHasItem(playerid, "Hunt Ammo"))
			{
				GivePlayerWeaponEx(playerid, 34, Inventory_Count(playerid, "Hunt Ammo"), WEAPON_TYPE_PLAYER);
			}
		}
	}

	ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, false, false, false, false, 0, true);

	Inventory_Close(playerid);
	return 1;
}

forward LoadDropped();
public LoadDropped()
{
	new ditstr[128], droppedformat, droppedweights[32], rows = cache_num_rows();
 	if(rows)
  	{
    	for(new i; i < rows; i++)
		{
		    cache_get_value_name_int(i, "ID", DroppedItems[i][droppedID]);

			cache_get_value_name(i, "itemName", DroppedItems[i][droppedItem]);
			cache_get_value_name(i, "itemPlayer", DroppedItems[i][droppedPlayer]);

			cache_get_value_name_int(i, "itemModel", DroppedItems[i][droppedModel]);
			cache_get_value_name_int(i, "itemQuantity", DroppedItems[i][droppedQuantity]);
			cache_get_value_name_float(i, "itemX", DroppedItems[i][droppedPos][0]);
			cache_get_value_name_float(i, "itemY", DroppedItems[i][droppedPos][1]);
			cache_get_value_name_float(i, "itemZ", DroppedItems[i][droppedPos][2]);
			cache_get_value_name_int(i, "itemInt", DroppedItems[i][droppedInt]);
			cache_get_value_name_int(i, "itemWorld", DroppedItems[i][droppedWorld]);

			cache_get_value_name_int(i, "itemTime", DroppedItems[i][droppedTime]);

			DroppedItems[i][droppedObject] = CreateDynamicObject(2663, DroppedItems[i][droppedPos][0], DroppedItems[i][droppedPos][1], DroppedItems[i][droppedPos][2], 0.0, 0.0, 0.0, DroppedItems[i][droppedWorld], DroppedItems[i][droppedInt]);
			
			droppedformat = GetItemWeight(DroppedItems[i][droppedItem]) * DroppedItems[i][droppedQuantity];
			strcopy(droppedweights, FormatInventoryDigit(droppedformat));

			format(ditstr, sizeof(ditstr), "%s | %dx | (%s kg)", DroppedItems[i][droppedItem], DroppedItems[i][droppedQuantity], droppedweights);
			DroppedItems[i][droppedText3D] = CreateDynamic3DTextLabel(ditstr, -1, DroppedItems[i][droppedPos][0], DroppedItems[i][droppedPos][1], DroppedItems[i][droppedPos][2] + 0.5, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, DroppedItems[i][droppedWorld], DroppedItems[i][droppedInt], -1, 10.0, -1, 0);
		}
		printf("[Dropped Items] Jumlah total Dropped Items yang dimuat: %d.", rows);
	}
	return 1;
}

forward OnDroppedItem(itemid);
public OnDroppedItem(itemid)
{
	if (itemid == -1 || !DroppedItems[itemid][droppedModel])
	    return 0;

	DroppedItems[itemid][droppedID] = cache_insert_id();
	return 1;
}

Dialog:ItemPickup(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		if(listitem == -1 || listitem >= 10) return 1;
		
		new id = NearestItems[playerid][listitem];

		if (id != -1 && DroppedItems[id][droppedModel])
		{
			new Float:countingtotalweight;
			countingtotalweight = GetTotalWeightFloat(playerid) + float(DroppedItems[id][droppedQuantity] * GetItemWeight(DroppedItems[id][droppedItem]))/1000;
			if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_WARNING, "Inventory anda penuh!");

			if(!strcmp(DroppedItems[id][droppedItem], "Obeng")) 
			{
				if(PlayerHasItem(playerid, "Obeng"))
				{
					return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sudah memiliki Obeng!");
				}
				else
				{
					if(DroppedItems[id][droppedQuantity] > 1) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak dapat memegang lebih dari satu Obeng!"); 
				}
			}

			if(!strcmp(DroppedItems[id][droppedItem], "Cangkul")) 
			{
				if(PlayerHasItem(playerid, "Cangkul"))
				{
					return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sudah memiliki Cangkul!");
				}
				else
				{
					if(DroppedItems[id][droppedQuantity] > 1) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak dapat memegang lebih dari satu Cangkul!"); 
				}
			}

			if(!strcmp(DroppedItems[id][droppedItem], "Smartphone"))
			{
				new query[128];
				mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `player_phones` WHERE `phoneOwner`=%d", AccountData[playerid][pID]);
				mysql_pquery(g_SQL, query, "OnPlayerBuySmartphone", "i", playerid);
			}
			else
			{
				Inventory_Add(playerid, DroppedItems[id][droppedItem], DroppedItems[id][droppedModel], DroppedItems[id][droppedQuantity]);
			}
			ApplyAnimation(playerid, "CARRY", "liftup", 4.1, false, false, false, false, 0, true);
			ShowItemBox(playerid, sprintf("%s", DroppedItems[id][droppedItem]), sprintf("Received %dx", DroppedItems[id][droppedQuantity]),  DroppedItems[id][droppedModel], 5);

			SendRPMeAboveHead(playerid, "Mengambil sesuatu di hadapannya.");

			Item_Delete(id);
		}
		else ShowTDN(playerid, NOTIFICATION_WARNING, "Item tersebut sudah tidak ada/diambil!");
	}
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(newkeys & KEY_WALK && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_DUCK)
	{
		new
			count = 0,
			id = Item_Nearest(playerid),
			droppedformat, 
			droppedweights[32],
			string[512],
			lstr[320];

		if (id != -1)
		{
			string = "";

			strcat(string, "Nama Item\tJumlah Item\tBerat Item (kg)\n");

			for (new i = 0; i < MAX_DROPPED_ITEMS; i ++) if (count < MAX_LISTED_ITEMS && DroppedItems[i][droppedModel] && IsPlayerInRangeOfPoint(playerid, 1.5, DroppedItems[i][droppedPos][0], DroppedItems[i][droppedPos][1], DroppedItems[i][droppedPos][2]) && GetPlayerInterior(playerid) == DroppedItems[i][droppedInt] && GetPlayerVirtualWorld(playerid) == DroppedItems[i][droppedWorld]) 
			{
				NearestItems[playerid][count++] = i;

				droppedformat = GetItemWeight(DroppedItems[i][droppedItem]) * DroppedItems[i][droppedQuantity];
				strcopy(droppedweights, FormatInventoryDigit(droppedformat));

				format(lstr, sizeof(lstr), "%s\t%d\t%s kg\n", DroppedItems[i][droppedItem], DroppedItems[i][droppedQuantity], droppedweights);
				strcat(string,lstr,sizeof(string));
			}
			if (count == 1)
			{
				if (id != -1 && DroppedItems[id][droppedModel])
				{
					new Float:countingtotalweight;
					countingtotalweight = GetTotalWeightFloat(playerid) + float(DroppedItems[id][droppedQuantity] * GetItemWeight(DroppedItems[id][droppedItem]))/1000;
					if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_WARNING, "Inventory anda penuh!");

					if(!strcmp(DroppedItems[id][droppedItem], "Obeng")) 
					{
						if(PlayerHasItem(playerid, "Obeng"))
						{
							return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sudah memiliki Obeng!");
						}
						else
						{
							if(DroppedItems[id][droppedQuantity] > 1) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak dapat memegang lebih dari satu Obeng!"); 
						}
					}
					if(!strcmp(DroppedItems[id][droppedItem], "Cangkul")) 
					{
						if(PlayerHasItem(playerid, "Cangkul"))
						{
							return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sudah memiliki Cangkul!");
						}
						else
						{
							if(DroppedItems[id][droppedQuantity] > 1) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak dapat memegang lebih dari satu Cangkul!"); 
						}
					}

					if(!strcmp(DroppedItems[id][droppedItem], "Smartphone"))
					{
						new query[128];
						mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `player_phones` WHERE `phoneOwner`=%d", AccountData[playerid][pID]);
						mysql_pquery(g_SQL, query, "OnPlayerBuySmartphone", "i", playerid);
					}
					else
					{
						Inventory_Add(playerid, DroppedItems[id][droppedItem], DroppedItems[id][droppedModel], DroppedItems[id][droppedQuantity]);
					}

					ApplyAnimation(playerid, "CARRY", "liftup", 4.1, false, false, false, false, 0, true);
					ShowItemBox(playerid, sprintf("%s", DroppedItems[id][droppedItem]), sprintf("Received %dx", DroppedItems[id][droppedQuantity]),  DroppedItems[id][droppedModel], 5);

					SendRPMeAboveHead(playerid, "Mengambil sesuatu di hadapannya.");

					Item_Delete(id);
				}
				else 
				{
					ShowTDN(playerid, NOTIFICATION_WARNING, "Item tersebut sudah tidak ada/diambil!");
				}
			}
			else
			{ 
				Dialog_Show(playerid, "ItemPickup", DIALOG_STYLE_TABLIST_HEADERS, "{DA9100}Pahlawan Roleplay "WHITE"- Ambil Item", string, "Ambil", "Batal");
			}
		}
	}
	return 1;
}

task UpdatingDroppedTime[60000]() 
{
	for(new x; x < MAX_DROPPED_ITEMS; x++)
	{
		if(DroppedItems[x][droppedModel] && DroppedItems[x][droppedTime] > 0 && gettime() > DroppedItems[x][droppedTime])
		{
			Item_Delete(x);
		}
	}
	return 1;
}