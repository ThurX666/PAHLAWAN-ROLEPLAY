enum E_INVENTS
{
    iID,
    Owner,

    //butcher job
    pLivingChicken,
    pSlaughteredChicken,
    pChickenFillet,

    //farmer job
    pRawSalt,
    pChili,
    pTebu,
    pPadi,

    pSalt,
    pSambal,
    pSugar,
    pBeras,

    //lumberjack job
    pWood,
    pCuttedWood,
    pBoard,

    //miner job
    pStone,
    pWashedStone,
    pCopper,
    pIron,
    pGold,
    pDiamond,

    //job oilman
    pRawOil,
    pFilteredOil,
    pGas,

    //tailor job
    pWool,
    pFabric,
    pClothing,

    //fisherman job
    pFish,

    //makanan
    pNasiGoreng,
    pBakso,
    pNasiPecel,
    pNasiUduk,
    pBuburPedas,
    pMieAyam,

    //minuman
    pEsTeh,
    pKopi,
    pAirMineral,
    pCMatcha,

    //sampah
    pTrashFood,
    pBotol
};
new InventData[MAX_PLAYERS][E_INVENTS];


enum E_FISHES
{
    Catfish,
    Octopus,
    Crab,
    Shrimp,
    Tuna,
    Salmon
};
new PlayerFish[MAX_PLAYERS][E_FISHES];

UpdatePlayerInventory(playerid)
{
    new upinvqry[1048];

    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "UPDATE `inventory` SET ");

    //butcher job
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`LivingChicken` = %d, ", upinvqry, InventData[playerid][pLivingChicken]);
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`SlaughteredChicken` = %d, ", upinvqry, InventData[playerid][pSlaughteredChicken]);
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`ChickenFillet` = %d, ", upinvqry, InventData[playerid][pChickenFillet]);

    //farmer job
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`RawSalt` = %d, ", upinvqry, InventData[playerid][pRawSalt]);
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`Chili` = %d, ", upinvqry, InventData[playerid][pChili]);
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`Tebu` = %d, ", upinvqry, InventData[playerid][pTebu]);
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`Padi` = %d, ", upinvqry, InventData[playerid][pPadi]);

    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`Salt` = %d, ", upinvqry, InventData[playerid][pSalt]);
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`Sambal` = %d, ", upinvqry, InventData[playerid][pSambal]);
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`Sugar` = %d, ", upinvqry, InventData[playerid][pSugar]);
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`Beras` = %d, ", upinvqry, InventData[playerid][pBeras]);

    //lumberjack job
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`Wood` = %d, ", upinvqry, InventData[playerid][pWood]);
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`CuttedWood` = %d, ", upinvqry, InventData[playerid][pCuttedWood]);
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`Board` = %d, ", upinvqry, InventData[playerid][pBoard]);

    //miner job
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`Stone` = %d, ", upinvqry, InventData[playerid][pStone]);
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`WashedStone` = %d, ", upinvqry, InventData[playerid][pWashedStone]);
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`Copper` = %d, ", upinvqry, InventData[playerid][pCopper]);
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`Iron` = %d, ", upinvqry, InventData[playerid][pIron]);
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`Gold` = %d, ", upinvqry, InventData[playerid][pGold]);
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`Diamond` = %d, ", upinvqry, InventData[playerid][pDiamond]);

    //tailor job
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`Wool` = %d, ", upinvqry, InventData[playerid][pWool]);
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`Fabric` = %d, ", upinvqry, InventData[playerid][pFabric]);
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`Clothing` = %d, ", upinvqry, InventData[playerid][pClothing]);

    //oilman job
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`RawOil` = %d, ", upinvqry, InventData[playerid][pRawOil]);
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`FilteredOil` = %d, ", upinvqry, InventData[playerid][pFilteredOil]);
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`Gas` = %d, ", upinvqry, InventData[playerid][pGas]);

    //fisherman job
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`Fish` = %d, ", upinvqry, InventData[playerid][pFish]);

    //makanan
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`NasiGoreng` = %d, ", upinvqry, InventData[playerid][pNasiGoreng]);
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`Bakso` = %d, ", upinvqry, InventData[playerid][pBakso]);
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`NasiPecel` = %d, ", upinvqry, InventData[playerid][pNasiPecel]);
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`NasiUduk` = %d, ", upinvqry, InventData[playerid][pNasiUduk]);
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`BuburPedas` = %d, ", upinvqry, InventData[playerid][pBuburPedas]);

    //minuman
	mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`MieAyam` = %d, ", upinvqry, InventData[playerid][pMieAyam]);
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`EsTeh` = %d, ", upinvqry, InventData[playerid][pEsTeh]);
	mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`Kopi` = %d, ", upinvqry, InventData[playerid][pKopi]);
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`AirMineral` = %d, ", upinvqry, InventData[playerid][pAirMineral]);
	mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`CMatcha` = %d, ", upinvqry, InventData[playerid][pCMatcha]);
    
    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`Botol` = %d, ", upinvqry, InventData[playerid][pBottle]);

    mysql_format(g_SQL, upinvqry, sizeof(upinvqry), "%s`TrashFood` = %d WHERE `Owner` = %d", upinvqry, InventData[playerid][pTrashFood], AccountData[playerid][pID]);
    mysql_pquery(g_SQL, upinvqry);
}

forward LoadPlayerInventory(playerid);
public LoadPlayerInventory(playerid)
{
	new loadinvs[522];
	mysql_format(g_SQL, loadinvs, sizeof(loadinvs), "SELECT * FROM `inventory` WHERE `Owner` = %d", AccountData[playerid][pID]);
	mysql_query(g_SQL, loadinvs, true);

    cache_get_value_name_int(0, "Owner", AccountData[playerid][pID]);
    
    //butcher job
    cache_get_value_name_int(0, "LivingChicken", InventData[playerid][pLivingChicken]);
    cache_get_value_name_int(0, "SlaughteredChicken", InventData[playerid][pSlaughteredChicken]);
    cache_get_value_name_int(0, "ChickenFillet", InventData[playerid][pChickenFillet]);
    
    //farmer job
    cache_get_value_name_int(0, "RawSalt", InventData[playerid][pRawSalt]);
    cache_get_value_name_int(0, "Chili", InventData[playerid][pChili]);
    cache_get_value_name_int(0, "Sugarcane", InventData[playerid][pTebu]);
    cache_get_value_name_int(0, "Wheat", InventData[playerid][pPadi]);

    cache_get_value_name_int(0, "Salt", InventData[playerid][pSalt]);
    cache_get_value_name_int(0, "Sauce", InventData[playerid][pSambal]);
    cache_get_value_name_int(0, "Sugar", InventData[playerid][pSugar]);
    cache_get_value_name_int(0, "Rice", InventData[playerid][pBeras]);

    //lumberjack job
    cache_get_value_name_int(0, "Wood", InventData[playerid][pWood]);
    cache_get_value_name_int(0, "CuttedWood", InventData[playerid][pCuttedWood]);
    cache_get_value_name_int(0, "Board", InventData[playerid][pBoard]);
    
    //miner job
    cache_get_value_name_int(0, "Stone", InventData[playerid][pStone]);
    cache_get_value_name_int(0, "WashedStone", InventData[playerid][pWashedStone]);
    cache_get_value_name_int(0, "Tembaga", InventData[playerid][pCopper]);
    cache_get_value_name_int(0, "Iron", InventData[playerid][pIron]);
    cache_get_value_name_int(0, "Gold", InventData[playerid][pGold]);
    cache_get_value_name_int(0, "Diamond", InventData[playerid][pDiamond]);

    //oilman job
    cache_get_value_name_int(0, "RawOil", InventData[playerid][pRawOil]);
    cache_get_value_name_int(0, "FilteredOil", InventData[playerid][pFilteredOil]);
    cache_get_value_name_int(0, "Gas", InventData[playerid][pGas]);

    //tailor job
    cache_get_value_name_int(0, "Wool", InventData[playerid][pWool]);
    cache_get_value_name_int(0, "Fabric", InventData[playerid][pFabric]);
    cache_get_value_name_int(0, "Clothing", InventData[playerid][pClothing]);

    //fisherman job
    cache_get_value_name_int(0, "Fish", InventData[playerid][pFish]);

    //makanan
    cache_get_value_name_int(0, "NasiGoreng", InventData[playerid][pNasiGoreng]);
    cache_get_value_name_int(0, "Bakso", InventData[playerid][pBakso]);
    cache_get_value_name_int(0, "NasiPecel", InventData[playerid][pNasiPecel]);
    cache_get_value_name_int(0, "NasiUduk", InventData[playerid][pNasiUduk]);
    cache_get_value_name_int(0, "BuburPedas", InventData[playerid][pBuburPedas]);
    cache_get_value_name_int(0, "MieAyam", InventData[playerid][pMieAyam]);

    //minuman
    cache_get_value_name_int(0, "EsTeh", InventData[playerid][pEsTeh]);
    cache_get_value_name_int(0, "Kopi", InventData[playerid][pKopi]);
    cache_get_value_name_int(0, "AirMineral", InventData[playerid][pAirMineral]);
    cache_get_value_name_int(0, "CMatcha", InventData[playerid][pCMatcha]);

    cache_get_value_name_int(0, "TrashFood", InventData[playerid][pTrashFood]);

    cache_get_value_name_int(0, "Bottle", InventData[playerid][pBottle]);
    
    printf("[Player Inventory] Memuat player inventory untuk: %s(%d)", AccountData[playerid][pName], playerid);
	return 1;
}