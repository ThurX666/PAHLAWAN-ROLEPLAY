#include <YSI_Coding\y_hooks>

#define MAX_INVENTORY   20

/*Variables*/
/*Enum*/
enum inventoryData
{
	bool:invExists, //melihat apakah inventory slot tersedia / terisi item
	invID, //id inventory
	invItem[32], //jumlah karakter/nama item
	invModel, //model id item
	invQuantity //jumlah banyaknya satu item
};
new InventoryData[MAX_PLAYERS][MAX_INVENTORY + 1][inventoryData];

enum e_InventoryItems
{
	e_InventoryItem[32], //nama item
	e_InventoryModel, //model item
	e_InventoryWeight //berat per item.
};

new const g_aInventoryItems[][e_InventoryItems] =
{
	{"Ransel", 3026, 300},
	{"Pilox", 365, 300},
	{"Smartphone", 18873, 300},
	{"Elektronik Rusak", 2041, 300},

	{"Alumunium", 2937, 100}, //pawn
	{"Kaca", 1649, 100}, //pawn
	{"Baja", 19772, 100}, //pawn
	{"Karet", 1316, 100}, //pawn
	{"Material", 2972, 50}, //pawn
	
	{"Ayam", 16776, 100},
    {"Ayam Potong", 2804, 100},
	{"Ayam Kemas", 2768, 100},

	{"Kayu", 19793, 100},
    {"Kayu Potong", 831, 100},
    {"Papan", 19433, 100},

	{"Batu", 3930, 200},
    {"Batu Cucian", 2936, 200},
	{"Tembaga", 11748, 100},
    {"Besi", 19809, 100},
    {"Emas", 19941, 100},
    {"Berlian", 19874, 100},

	{"Minyak Bumi", 935, 100},
    {"Minyak Saringan", 3632, 100},
    {"Minyak", 19621, 100},
	
	{"Wool", 1974, 100},
    {"Kain", 11747, 100},
    {"Pakaian", 2399, 100},

    {"Susu", 19570, 100},
    {"Susu Fermentasi", 19569, 100},

    {"Ikan", 1604, 100},
	
	{"Plastik", 1265, 50},
	
	{"Toolkit", 19921, 200},

	{"Kentang", 19638, 100},
	{"Kubis", 19637, 100},
	{"Bawang", 19636, 100},
	{"Tomat", 19636, 100},
	{"Kentang Potong", 19574, 50},
	{"Kubis Potong", 19576, 50},
	{"Bawang Potong", 19575, 50},
	{"Tomat Potong", 19577, 50},
	{"Air", 19570, 100},
	{"Gula", 1279, 100},
	{"Micin", 19573, 100},
	{"Kertas", 19873, 100},

	{"BBQ Delicy", 2663, 200},
	{"Buckshot Special", 2663, 200},
	{"Minang Combo", 2663, 200},
	{"Frenchy Velty", 2663, 200},
	{"Rice Combo", 2663, 200},
	{"Malaya Shine", 2663, 200},
	{"Fresh Solar", 2663, 200},
	{"Softex Flash", 2663, 200},
	{"Purple Sweet", 2663, 200},

    {"Chicken BBQ", 2355, 15},
    {"Donut", 2221, 15},
    {"Nasi Padang", 2219, 15},
    {"Roti Jala", 2355, 15},
    {"French Fries", 2769, 15},
    {"Fried Rice", 2219, 15},
    {"Gulai Ayam", 2355, 15},
    {"Burger", 2880, 15},
    {"Teriyaki", 2355, 15},
    {"Fried Chicken", 2355, 15},
    {"Snack", 19565, 10},
    {"Cereal", 19562, 10},
    
	{"Nasi Uduk", 2769, 15},
    {"Air Mineral", 19570, 15},

    {"Coconut Water", 19564, 10},
    {"Brewed Coffee", 19835, 10},
    {"Jus Timun", 1546, 10},
    {"Sirup Selasih", 1544, 10},
    {"Red Velvet", 1546, 10},
    {"Vanilla Milkshake", 19569, 10},

    {"Coca-Cola", 2647, 10},
    {"Rootbeer", 1546, 10},
    {"Guinness", 1669, 10},

    {"Es Lilin", 19565, 10},
    {"Cola", 2647, 10},
    {"Sprunk", 2601, 10},

	{"Cangkul", 2228, 200},
	{"Bibit Cabai", 2663, 25},
    {"Bibit Tebu", 2663, 25},
    {"Bibit Padi", 2663, 25}, //bibit padi
    {"Bibit Strawberry", 2663, 25}, //
    {"Bibit Jeruk", 2663, 25}, //
    {"Bibit Anggur", 2663, 25}, //b
	{"Cabai", 2253, 55},
    {"Tebu", 855, 55},
    {"Padi", 2247, 55}, //padi
    {"Strawberry", 19577, 55}, //padi
    {"Jeruk", 19574, 55}, //padi
    {"Anggur", 19576, 55}, //padi

    {"Ember", 19468, 55},
    {"Ember Terisi", 1554, 55},

    {"Sampah Makanan", 2840, 85},
    {"Botol", 19570, 55},
	{"Jerigen", 1650, 250},
	{"Linggis", 18634, 200},
	{"Kunci T", 18633, 200},
	{"Alat Hack", 19893, 200},
	{"Obeng", 19627, 200},
	{"Komponen", 2040, 15}, //LAST
	{"Part Mesin", 19917, 100},
	{"Part Body", 1141, 100},
	{"Ban Baru", 1083, 100},
	{"Air Brush", 2752, 100},
	{"Perban", 11736, 100},
	{"Medkit", 11738, 150},
	{"Pil Stres", 1241, 85},
	{"Daun Ganja", 19473, 55},
	{"Marijuana", 1578, 100},

	{"Efedrin", 11748, 55},
	{"Stimulan", 19874, 85},
	{"Sabu Kristal", 2866, 85},
	{"Sabu", 1575, 100},

	{"Sinte", 3027, 100},
	{"Heroin", 1579, 100},
	
	{"Anggur Merah", 1544, 150},
	{"Tuak", 1486, 150},

	{"Kevlar", 19515, 175},
	{"Udud", 19896, 25},
	{"Vape", 19823, 25},
	{"Hunt Ammo", 2358, 150},
	{"Daging", 2806, 200},
	{"Tanduk", 19314, 200},
	{"Kulit", 1828, 200},
	{"Changename Card", 19792, 100},
	{"Disposable Phone", 330, 100},
	{"Skateboard", 19878, 250},
	{"Senter", 18641, 100},
	{"Karung Goni", 2663, 100},

	{"Pancingan", 18632, 75},
	{"Umpan", 1603, 15},
	{"Penyu", 1609, 55},
	{"Hiu", 1608, 80}
};

/*Function*/
FormatInventoryDigit(amount, const delimiter[2]=",")
{
	#define MAX_Digit_String 16
	new txt[MAX_Digit_String];
	format(txt, MAX_Digit_String, "%d", amount);
	new l = strlen(txt);
	
	if(l == 1) strins(txt, "0,00",l-1);
	else if(l == 2) strins(txt, "0,0", l-2);
	else if(l == 3) strins(txt,"0,",l-3);
	else if(l > 3) strins(txt,delimiter,l-3);
	return txt;
}

GetItemWeight(const item[])
{
    for (new i; i < sizeof(g_aInventoryItems); i ++)
    {
        if(!strcmp(g_aInventoryItems[i][e_InventoryItem], item, true))
        	return g_aInventoryItems[i][e_InventoryWeight];
    }
	return 0;
}

GetTotalWeightString(playerid)
{
	new totalweights, digitresult[32];

	for(new i; i < MAX_INVENTORY; i++)
    {
		if(!InventoryData[playerid][i][invExists])
		{
			continue;
		}
		totalweights += GetItemWeight(InventoryData[playerid][i][invItem]) * Inventory_Count(playerid, InventoryData[playerid][i][invItem]);
	}
	strcopy(digitresult, FormatInventoryDigit(totalweights));
	return digitresult;
}

Float:GetTotalWeightFloat(playerid)
{
	new totalweights, Float:totalweights2;

	for(new i = 0; i < MAX_INVENTORY; i++)
    {
		if(!InventoryData[playerid][i][invExists])
		{
			continue;
		}

		totalweights += GetItemWeight(InventoryData[playerid][i][invItem]) * Inventory_Count(playerid, InventoryData[playerid][i][invItem]);
	}
	totalweights2 = float(totalweights)/1000;
	return totalweights2;
}

Inventory_Clear(playerid)
{
	for(new x; x < MAX_INVENTORY; x++)
	{
	    if(InventoryData[playerid][x][invExists])
	    {
	        InventoryData[playerid][x][invExists] = false;
	        InventoryData[playerid][x][invModel] = 0;
	        InventoryData[playerid][x][invQuantity] = 0;
			InventoryData[playerid][x][invItem][0] = EOS;
		}
	}
	//AccountData[playerid][pBeratItem] = 0.0;
	new invstr[128];
	mysql_format(g_SQL, invstr, sizeof(invstr), "DELETE FROM `inventory` WHERE `Owner_ID` = %d", AccountData[playerid][pID]);
	return mysql_pquery(g_SQL, invstr);
}

Inventory_GetItemID(playerid, const item[])
{
	for(new x; x < MAX_INVENTORY; x++)
	{
	    if(!InventoryData[playerid][x][invExists])
	        continue;

		if(!strcmp(InventoryData[playerid][x][invItem], item)) return x;
	}
	return -1;
}

Inventory_GetFreeID(playerid)
{
	if(Inventory_Items(playerid) >= MAX_INVENTORY)
		return -1;

	for(new x; x < MAX_INVENTORY; x++)
	{
	    if (!InventoryData[playerid][x][invExists])
	        return x;
	}
	return -1;
}

Inventory_Items(playerid)
{
    new count;
    for(new x; x < MAX_INVENTORY; x++) if (InventoryData[playerid][x][invExists]) {
        count++;
	}
	return count;
}

Inventory_Count(playerid, const item[])
{
	new itemid = Inventory_GetItemID(playerid, item);
	if (itemid != -1)
	    return InventoryData[playerid][itemid][invQuantity];
		
	return 0;
}

PlayerHasItem(playerid, const item[])
{
	return (Inventory_GetItemID(playerid, item) != -1);
}

Inventory_Set(playerid, const item[], model, amount)
{
	new itemid = Inventory_GetItemID(playerid, item);
	if (itemid == -1 && amount > 0) //jika item belum ada di inventory dan jumlah lebih dari 0
		Inventory_Add(playerid, item, model, amount);
	else if (amount > 0 && itemid != -1) //jika item sudah ada di inventory dan jumlah lebih dari 0
	    Inventory_SetQuantity(playerid, item, amount);
	else if (amount < 1 && itemid != -1) //jika item sudah ada di inventory dan jumlah di bawah 1 artinya (0, -1, dst)
	    Inventory_Remove(playerid, item, -1);
	return 1;
}

Inventory_SetQuantity(playerid, const item[], quantity)
{
	new
	    itemid = Inventory_GetItemID(playerid, item),
		invstr[1028];

	if(itemid != -1)
	{
	    InventoryData[playerid][itemid][invQuantity] = quantity;

		mysql_format(g_SQL, invstr, sizeof(invstr), "UPDATE `inventory` SET `invent_Quantity` = %d WHERE `Owner_ID` = %d AND `invent_ID` = %d", quantity, AccountData[playerid][pID], InventoryData[playerid][itemid][invID]);
	    mysql_pquery(g_SQL, invstr);
	}
	return 1;
}

Inventory_Show(playerid)
{
	if(!IsPlayerConnected(playerid))
		return 0;
	
    ShowInventoryTD(playerid);

    new Float:jumlahbar;
	for(new index; index < MAX_INVENTORY; index++)
	{
        if(InventoryData[playerid][index][invExists])
		{
		    for (new i; i < sizeof(g_aInventoryItems); i ++) if (!strcmp(g_aInventoryItems[i][e_InventoryItem], InventoryData[playerid][index][invItem], true))
			{
			    PlayerTextDrawSetPreviewModel(playerid, PrevMod[playerid][index], InventoryData[playerid][index][invModel]);
	            PlayerTextDrawShow(playerid, PrevMod[playerid][index]);
	            
	            PlayerTextDrawSetString(playerid, NameItem[playerid][index], sprintf("%s", g_aInventoryItems[i][e_InventoryItem]));
				PlayerTextDrawShow(playerid, NameItem[playerid][index]);

	            PlayerTextDrawSetString(playerid, QuantItem[playerid][index], sprintf("%dx", InventoryData[playerid][index][invQuantity]));
				PlayerTextDrawShow(playerid, QuantItem[playerid][index]);

				TextDrawShowForPlayer(playerid, InventLineTD[index]);
			}
		}
	}
	jumlahbar = GetTotalWeightFloat(playerid) * 132.600006/GetPlayerInventoryWeight(playerid);
	PlayerTextDrawTextSize(playerid, InventWeightTD[playerid][1], jumlahbar, 3.500000);
	PlayerTextDrawShow(playerid, InventWeightTD[playerid][1]);

	PlayerTextDrawSetString(playerid, InventWeightTD[playerid][0], sprintf("%s", GetPlayerRoleplayName(playerid)));
	PlayerTextDrawShow(playerid, InventWeightTD[playerid][0]);

	PlayerTextDrawSetString(playerid, InventWeightTD[playerid][2],sprintf("%s/%d", GetTotalWeightString(playerid), GetPlayerInventoryWeight(playerid)));
	PlayerTextDrawShow(playerid, InventWeightTD[playerid][2]);

	PlayerTextDrawShow(playerid, InventWeightTD[playerid][3]);

	SelectTextDraw(playerid, 0xff91a4cc);
	return 1;
}

Inventory_Close(playerid)
{
	for(new x; x < 20; x++)
	{
		PlayerTextDrawColor(playerid, BoxItem[playerid][x], 0x00000066);
	}
    PlayerTextDrawSetString(playerid, InventWeightTD[playerid][3], "Ammount");

	CancelSelectTextDraw(playerid);
	
	HideInventoryTD(playerid);

	ShowServerNameTD(playerid);

	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		ShowSpeedoTD(playerid);
		
	ShowHBETD(playerid);

	AccountData[playerid][pSelectItem] = -1;
	AccountData[playerid][pItemQuantity] = 0;
	pShortcutResultShown[playerid] = false;
	return 1;
}

Inventory_Remove(playerid, const item[], quantity = 1)
{
	new
		itemid = Inventory_GetItemID(playerid, item),
		invstr[1028];

	if(itemid != -1)
	{
	    if(InventoryData[playerid][itemid][invQuantity] > 0)
	    {
	        InventoryData[playerid][itemid][invQuantity] -= quantity;
		}
		if(quantity == -1 || InventoryData[playerid][itemid][invQuantity] < 1)
		{
		    InventoryData[playerid][itemid][invExists] = false;
		    InventoryData[playerid][itemid][invModel] = 0;
		    InventoryData[playerid][itemid][invQuantity] = 0;
			InventoryData[playerid][itemid][invItem][0] = EOS;

			mysql_format(g_SQL, invstr, sizeof(invstr), "DELETE FROM `inventory` WHERE `Owner_ID` = %d AND `invent_ID` = %d", AccountData[playerid][pID], InventoryData[playerid][itemid][invID]);
	        mysql_pquery(g_SQL, invstr);
		}
		else if(quantity != -1 && InventoryData[playerid][itemid][invQuantity] > 0)
		{
			mysql_format(g_SQL, invstr, sizeof(invstr), "UPDATE `inventory` SET `invent_Quantity` = `invent_Quantity` - %d WHERE `Owner_ID` = %d AND `invent_ID` = %d", quantity, AccountData[playerid][pID], InventoryData[playerid][itemid][invID]);
            mysql_pquery(g_SQL, invstr);
		}
		return 1;
	}
	return 0;
}

/*
Inventory_UpdateItem(playerid, const item[], quantity, itemid)
{
    new Float:countingtotalweight;
	countingtotalweight = GetTotalWeightFloat(playerid) + float(quantity * GetItemWeight(item))/1000;
    if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda penuh!");

	new invstr[1028];
	mysql_format(g_SQL, invstr, sizeof(invstr), "UPDATE `inventory` SET `invent_Quantity` = `invent_Quantity` + %d WHERE `Owner_ID` = %d AND `invent_ID` = %d", quantity, AccountData[playerid][pID], InventoryData[playerid][itemid][invID]);
	mysql_pquery(g_SQL, invstr);

	InventoryData[playerid][itemid][invQuantity] += quantity;
	return 1;
}
*/

forward OnInventoryAdd(playerid, itemid);
public OnInventoryAdd(playerid, itemid)
{
	InventoryData[playerid][itemid][invID] = cache_insert_id();
	return 1;
}

Inventory_Add(playerid, const item[], model, quantity = 1)
{
	new
		itemid = Inventory_GetItemID(playerid, item),
		invstr[1028];

	if(itemid == -1)
	{
	    itemid = Inventory_GetFreeID(playerid);
	    if(itemid != -1)
	    {
			new Float:countingtotalweight;
			countingtotalweight = GetTotalWeightFloat(playerid) + float(quantity * GetItemWeight(item))/1000;
    		if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Inventory anda penuh, anda tidak menerima item %s!", item));

	        InventoryData[playerid][itemid][invExists] = true;
	        InventoryData[playerid][itemid][invModel] = model;
	        InventoryData[playerid][itemid][invQuantity] = quantity;

			strcopy(InventoryData[playerid][itemid][invItem], item);

			mysql_format(g_SQL, invstr, sizeof(invstr), "INSERT INTO `inventory` (`Owner_ID`, `invent_Item`, `invent_Model`, `invent_Quantity`) VALUES('%d', '%e', '%d', '%d')", AccountData[playerid][pID], item, model, quantity);
			mysql_pquery(g_SQL, invstr, "OnInventoryAdd", "id", playerid, itemid);
		}
		else
		{
			ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah item di inventory sudah mencapai batas maksimal 20!");
		}
	}
	else
	{
		new Float:countingtotalweight;
		countingtotalweight = GetTotalWeightFloat(playerid) + float(quantity * GetItemWeight(item))/1000;
		if(countingtotalweight > GetPlayerInventoryWeight(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Inventory anda penuh, anda tidak menerima item %s!", item));

		mysql_format(g_SQL, invstr, sizeof(invstr), "UPDATE `inventory` SET `invent_Quantity` = `invent_Quantity` + %d WHERE `Owner_ID` = %d AND `invent_ID` = %d", quantity, AccountData[playerid][pID], InventoryData[playerid][itemid][invID]);
		mysql_pquery(g_SQL, invstr);

		InventoryData[playerid][itemid][invQuantity] += quantity;
	}
	return 1;
}

Dialog:InventorySetValue(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");

	if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat mengosongkan kolom ini!");
	if(!IsNumericEx(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Masukkan hanya angka!");
	if(strval(inputtext) < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid!");
	AccountData[playerid][pItemQuantity] = strval(inputtext);
	PlayerTextDrawSetString(playerid, InventWeightTD[playerid][3], inputtext);
	return 1;
}

Dialog:InventoryGive(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada pemain terdekat!");

	new id = NearestUser[playerid][listitem],
		destname[32];

	if(AccountData[playerid][pSelectItem] < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item apapun!");
	if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada pemain terdekat!");
	
	strcopy(destname, InventoryData[playerid][AccountData[playerid][pSelectItem]][invItem]);

	for(new i; i < sizeof(g_aInventoryItems); i ++) if (!strcmp(g_aInventoryItems[i][e_InventoryItem], destname, true))
	{
		if(Inventory_Count(playerid, g_aInventoryItems[i][e_InventoryItem]) < AccountData[playerid][pItemQuantity]) return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Anda tidak memiliki cukup %s!", g_aInventoryItems[i][e_InventoryItem]));
		if(!IsPlayerConnected(id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
		if(!IsPlayerNearPlayer(playerid, id, 3.2)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak dekat dengan anda!");
		// Check before proceeding
		new Float:countingtotalweight;
		countingtotalweight = GetTotalWeightFloat(id) + float(AccountData[playerid][pItemQuantity] * GetItemWeight(g_aInventoryItems[i][e_InventoryItem]))/1000;
		if(countingtotalweight > GetPlayerInventoryWeight(id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory pemain tersebut telah penuh");

		if(!strcmp(g_aInventoryItems[i][e_InventoryItem], "Sampah Makanan")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memberi Sampah Makanan kepada pemain lain!");
		if(!strcmp(g_aInventoryItems[i][e_InventoryItem], "Changename Card")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memberi Changename Card kepada pemain lain!");
		if(!strcmp(g_aInventoryItems[i][e_InventoryItem], "Obeng")) 
		{
			if(PlayerHasItem(id, "Obeng"))
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sudah memiliki Obeng!");
		}
		if(!strcmp(g_aInventoryItems[i][e_InventoryItem], "Cangkul")) 
		{
			if(PlayerHasItem(id, "Cangkul"))
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sudah memiliki Cangkul!");
		}
		
		Inventory_Remove(playerid, g_aInventoryItems[i][e_InventoryItem], AccountData[playerid][pItemQuantity]);
		
		if(!strcmp(g_aInventoryItems[i][e_InventoryItem], "Hunt Ammo"))
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

		if(!strcmp(g_aInventoryItems[i][e_InventoryItem], "Smartphone"))
		{
			new query[128];
			mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `player_phones` WHERE `phoneOwner`=%d", AccountData[id][pID]);
			mysql_pquery(g_SQL, query, "OnPlayerBuySmartphone", "i", id);
		}
		else
		{
			Inventory_Add(id, g_aInventoryItems[i][e_InventoryItem], g_aInventoryItems[i][e_InventoryModel], AccountData[playerid][pItemQuantity]);
		}
		
		ShowItemBox(playerid, sprintf("%s", g_aInventoryItems[i][e_InventoryItem]), sprintf("Removed %dx", AccountData[playerid][pItemQuantity]),  g_aInventoryItems[i][e_InventoryModel], 5);
		ShowItemBox(id, sprintf("%s", g_aInventoryItems[i][e_InventoryItem]), sprintf("Received %dx", AccountData[playerid][pItemQuantity]),  g_aInventoryItems[i][e_InventoryModel], 5);

		AccountData[playerid][pSelectItem] = -1;
		AccountData[playerid][pItemQuantity] = 0;

		for(new x; x < 100; x++)
		{
			NearestUser[playerid][x] = INVALID_PLAYER_ID;
		}

		Inventory_Close(playerid);
	}
	return 1;
}

static bool:ItemValidOrDelete(playerid, slot)
{
    new bool:itemExists = false;
    for(new i = 0; i < sizeof(g_aInventoryItems); i++) 
    {
        // Kalau item-nya ada, ganti itemExists
        if(!strcmp(InventoryData[playerid][slot][invItem], g_aInventoryItems[i][e_InventoryItem], true)) {
            itemExists = true;
            break;
        }
 
        // Nah ini bakal nge-loop terus sampai ketemu si item atau gak sampai
        // size-nya abis. Kenapa? Karena kan si nama item gak selalu ada di
        // index yang lagi di-loop ini, bisa aja di index yang lain.
    }
 
    // Habis nge-loop seluruh index ternyata namanya bener-bener gak ada. Nah
    // di sini deh baru di-delete.
    if(!itemExists) 
    {
        InventoryData[playerid][slot][invExists] = false;
        InventoryData[playerid][slot][invModel] = 0;
        InventoryData[playerid][slot][invQuantity] = 0;
 
        InventoryData[playerid][slot][invItem][0] = EOS;
 
        PlayerTextDrawHide(playerid, PrevMod[playerid][slot]);
        PlayerTextDrawHide(playerid, NameItem[playerid][slot]);
        PlayerTextDrawHide(playerid, QuantItem[playerid][slot]);
 
        TextDrawHideForPlayer(playerid, InventLineTD[slot]);
 
        static invstr[555];
        mysql_format(g_SQL, invstr, sizeof(invstr), "DELETE FROM `inventory` WHERE `Owner_ID` = %d AND `invent_ID` = %d", AccountData[playerid][pID], InventoryData[playerid][slot][invID]);
        mysql_pquery(g_SQL, invstr);
    }
 
    return itemExists;
}

forward LoadPlayerItems(playerid);
public LoadPlayerItems(playerid)
{
    new count = cache_num_rows();
    if(count > 0)
    {
        new totalInvalidItems = 0;
        for(new i; i < count; i++)
        {
            InventoryData[playerid][i][invExists] = true;
 
            cache_get_value_name_int(i, "invent_ID", InventoryData[playerid][i][invID]);
            cache_get_value_name_int(i, "invent_Model", InventoryData[playerid][i][invModel]);
            cache_get_value_name_int(i, "invent_Quantity", InventoryData[playerid][i][invQuantity]);
 
            cache_get_value_name(i, "invent_Item", InventoryData[playerid][i][invItem]);
 
            if(!ItemValidOrDelete(playerid, i)) 
			{
                totalInvalidItems++;
            }
        }
 
        printf("[Player Inventory] Total number of inventory items loaded for %s [DBID: %d]: %d.", AccountData[playerid][pUCP], AccountData[playerid][pID], count - totalInvalidItems);
 
        if(totalInvalidItems) 
		{
            printf("[Player Inventory] Total number of invalid items deleted for %s [DBID: %d]: %d.", AccountData[playerid][pUCP], AccountData[playerid][pID], totalInvalidItems);
        }
    }
    return 1;
}