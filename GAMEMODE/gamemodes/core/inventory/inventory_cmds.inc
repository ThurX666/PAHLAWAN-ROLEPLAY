YCMD:asetitem(playerid, params[], help) // Set player item
{
	new
		targetid,
		item[32],
		amount;

	if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

	if(sscanf(params, "ids[32]", targetid, amount, item))
	    return SUM(playerid, "/asetitem [playerid] [amount] [item name]");

	if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

	for(new i = 0; i < sizeof(g_aInventoryItems); i++) if(!strcmp(g_aInventoryItems[i][e_InventoryItem], item, true))
	{
		new Float:countingtotalweight;
		countingtotalweight = GetTotalWeightFloat(targetid) + float(amount * GetItemWeight(g_aInventoryItems[i][e_InventoryItem]))/1000;
		if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_WARNING, "Inventory pemain tersebut telah penuh");

		Inventory_Set(targetid, g_aInventoryItems[i][e_InventoryItem], g_aInventoryItems[i][e_InventoryModel], amount);

		SendClientMessageEx(playerid, 0xFF00FFAA, "[Server] You have set %d %s to %s", amount, g_aInventoryItems[i][e_InventoryItem], AccountData[targetid][pName]);
		
		SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s set %d %s for %s(%d).", AccountData[playerid][pAdminname], amount, g_aInventoryItems[i][e_InventoryItem], AccountData[targetid][pName], targetid);
		return 1;
	}
	ShowTDN(playerid, NOTIFICATION_WARNING, "Nama item tidak valid!");
	return 1;
}

YCMD:agiveitem(playerid, params[], help) // Give item to player
{
	new
		targetid,
		item[32],
		amount;

	if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

	if(sscanf(params, "ids[32]", targetid, amount, item))
	    return SUM(playerid, "/agiveitem [playerid] [amount] [item name]");

	if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

	if(amount < 1) return ShowTDN(playerid, NOTIFICATION_WARNING, "Jumlah tidak boleh kurang dari 1!");

	for (new i = 0; i < sizeof(g_aInventoryItems); i++) if(!strcmp(g_aInventoryItems[i][e_InventoryItem], item, true))
	{
		new Float:countingtotalweight;
		countingtotalweight = GetTotalWeightFloat(targetid) + float(amount * GetItemWeight(g_aInventoryItems[i][e_InventoryItem]))/1000;
		if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_WARNING, "Inventory pemain tersebut telah penuh");
		if(!strcmp(item, "Smartphone", true))
		{
			new query[128];
			mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `player_phones` WHERE `phoneOwner`=%d", AccountData[targetid][pID]);
			mysql_pquery(g_SQL, query, "OnPlayerBuySmartphone", "i", targetid);
		} 
		else
		{
			Inventory_Add(targetid, g_aInventoryItems[i][e_InventoryItem], g_aInventoryItems[i][e_InventoryModel], amount);
		}

		SendClientMessageEx(playerid, 0xFF00FFAA, "[Server] You have give %d %s to %s", amount, g_aInventoryItems[i][e_InventoryItem], AccountData[targetid][pName]);
		SendClientMessageEx(targetid, 0xFF00FFAA, "[Server] You have got %d %s by %s", amount, g_aInventoryItems[i][e_InventoryItem], AccountData[playerid][pUCP]);
		
		SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s gave %d %s to %s(%d).", AccountData[playerid][pAdminname], amount, g_aInventoryItems[i][e_InventoryItem], AccountData[targetid][pName], targetid);
		return 1;
	}
	ShowTDN(playerid, NOTIFICATION_WARNING, "Nama item tidak valid!");
	return 1;
}

YCMD:agiveitemall(playerid, params[], help) // Give item to all players
{
	new
		item[32],
		amount;

	if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

	if(sscanf(params, "ds[32]", amount, item))
	    return SUM(playerid, "/agiveitemall [amount] [item name]");

	if(amount < 1) return ShowTDN(playerid, NOTIFICATION_WARNING, "Jumlah tidak dapat kurang dari 1!");

	new Float:countingtotalweight[MAX_PLAYERS];
	for (new i; i < sizeof(g_aInventoryItems); i++) if(!strcmp(g_aInventoryItems[i][e_InventoryItem], item, true))
	{
		foreach(new x : Player)
		{
			countingtotalweight[x] = GetTotalWeightFloat(x) + float(amount * GetItemWeight(g_aInventoryItems[i][e_InventoryItem]))/1000;
			if(countingtotalweight[x] < 50)
			{
				if(!strcmp(item, "Smartphone", true))
				{
					new query[128];
					mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `player_phones` WHERE `phoneOwner`=%d", AccountData[x][pID]);
					mysql_pquery(g_SQL, query, "OnPlayerBuySmartphone", "i", x);
				} 
				else
				{
					Inventory_Add(x, g_aInventoryItems[i][e_InventoryItem], g_aInventoryItems[i][e_InventoryModel], amount);
				}	
			}
			SendAdm(x, "%s has given %d %s to all players.", AccountData[playerid][pAdminname], amount, item);
		}
		return 1;
	}
	ShowTDN(playerid, NOTIFICATION_WARNING, "Nama item tidak valid!");
	return 1;
}

YCMD:atakeitem(playerid, params[], help) // Forcefully take item from player
{
    new
		targetid,
		item[32],
		amount;
	
	if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

	if(sscanf(params, "ids[32]", targetid, amount, item))
	    return SUM(playerid, "/atakeitem [playerid] [amount] [item name]");

	if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

	if(amount < 1) return ShowTDN(playerid, NOTIFICATION_WARNING, "Jumlah tidak dapat kurang dari 1!");
	
	for(new i = 0; i < sizeof(g_aInventoryItems); i++) if (!strcmp(g_aInventoryItems[i][e_InventoryItem], item, true))
	{
        Inventory_Remove(targetid, g_aInventoryItems[i][e_InventoryItem], amount);

		SendClientMessageEx(playerid, 0xFF00FFAA, "[Server] You have taken %d %s from %s", amount, g_aInventoryItems[i][e_InventoryItem], AccountData[targetid][pName]);
		SendClientMessageEx(targetid, 0xFF00FFAA, "[Server] Your %d %s have been taken by %s", amount, g_aInventoryItems[i][e_InventoryItem], AccountData[playerid][pUCP]);
		
		SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s confiscated %d %s from the inventory of %s(%d).", AccountData[playerid][pAdminname], amount, g_aInventoryItems[i][e_InventoryItem], AccountData[targetid][pName], targetid);
		return 1;
	}
	ShowTDN(playerid, NOTIFICATION_WARNING, "Nama item tidak valid!");
    return 1;
}

YCMD:aremoveitem(playerid, params[], help) // Remove or destroy player's item
{
	new
		targetid,
		item[32];
	
	if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

	if(sscanf(params, "is[32]", targetid, item))
	    return SUM(playerid, "/aremoveitem [playerid] [item name]");

	if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

	for(new i = 0; i < sizeof(g_aInventoryItems); i++) if (!strcmp(g_aInventoryItems[i][e_InventoryItem], item, true))
	{
		if(!PlayerHasItem(targetid, g_aInventoryItems[i][e_InventoryItem])) return ShowTDN(playerid, NOTIFICATION_WARNING, sprintf("That player does not have %s!", g_aInventoryItems[i][e_InventoryItem]));

        Inventory_Remove(targetid, g_aInventoryItems[i][e_InventoryItem], -1);

		SendClientMessageEx(playerid, -1, "Anda telah menghapus "CYAN"%s "WHITE"milik "YELLOW"%s", g_aInventoryItems[i][e_InventoryItem], AccountData[targetid][pName]);
		SendClientMessageEx(targetid, -1, "Semuar "CYAN"%s "WHITE"milikmu telah dihapus oleh "RED"%s", g_aInventoryItems[i][e_InventoryItem], AccountData[playerid][pUCP]);
		
		SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s removed %s from the inventory of %s(%d).", AccountData[playerid][pAdminname], g_aInventoryItems[i][e_InventoryItem], AccountData[targetid][pName], targetid);
		return 1;
	}
	ShowTDN(playerid, NOTIFICATION_WARNING, "Nama item tidak valid!");
	return 1;
}

YCMD:aclearinv(playerid, params[], help) // Reset player's inventory
{
	new
		targetid;
	
	if(AccountData[playerid][pAdmin] < 9) return PermissionError(playerid);

	if(sscanf(params, "i", targetid))
	    return SUM(playerid, "/aclearinv [playerid]");

	if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

	Inventory_Clear(targetid);
	SendClientMessageEx(playerid, 0xFF00FFAA, "[Server] You have reset inventory for %s", AccountData[targetid][pName]);
	SendClientMessageEx(targetid, 0xFF00FFAA, "[Server] Your inventory has been reset by %s", AccountData[playerid][pUCP]);

	SendStaffMessage(Y_LIGHTRED, "AdmCmd: %s reset the entire inventory of %s(%d).", AccountData[playerid][pAdminname], AccountData[targetid][pName], targetid);
	return 1;
}

YCMD:ainv(playerid, params[], help)
{
	new targetid;

	if(AccountData[playerid][pAdmin] < 3)
		return PermissionError(playerid);

	if(sscanf(params, "i", targetid))
	    return SUM(playerid, "/ainv [playerid]");

	if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

	new str[1218], amounts, itemname[32], tss[128];
	format(str, sizeof(str), "Item Name\tQuantity\n");
	mysql_format(g_SQL, tss, sizeof(tss), "SELECT * FROM `inventory` WHERE `Owner_ID`=%d", AccountData[targetid][pID]);
	mysql_query(g_SQL, tss);
	new rows = cache_num_rows();
	if(rows)
	{
		for(new x; x < rows; ++x)
		{
			cache_get_value_name(x, "invent_Item", itemname);
			cache_get_value_name_int(x, "invent_Quantity", amounts);
			format(str, sizeof(str), "%s%s\t%d\n", str, itemname, amounts);
		}
		Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_TABLIST_HEADERS, sprintf("%s (%d)'s Inventory", AccountData[targetid][pName], targetid), str, "Tutup", "");
	}
	else
	{
		Dialog_Show(playerid, "UnusedDialog", DIALOG_STYLE_MSGBOX, sprintf("%s (%d)'s Inventory", AccountData[targetid][pName], targetid), "The player does not have any items!", "Tutup", "");
	}
	return 1;
}