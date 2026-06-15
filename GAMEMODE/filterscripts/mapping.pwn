#define FILTERSCRIPT

#include <a_samp>

#undef MAX_PLAYERS
#define MAX_PLAYERS	500

#include <streamer>

#include <YSI_Data\y_iterate>

#include "./mapping/ext/ext_clothesext.pwn" //done
#include "./mapping/ext/ext_electronic.pwn"
#include "./mapping/ext/ext_fleeca.pwn"
#include "./mapping/ext/ext_carsteal.pwn"
#include "./mapping/ext/ext_supermarket.pwn"
#include "./mapping/ext/ext_cityhall.pwn"
#include "./mapping/ext/ext_kanabisproc.pwn"
#include "./mapping/ext/ext_burgershot.pwn"
#include "./mapping/ext/ext_hospital.pwn"
#include "./mapping/ext/ext_ammunation.pwn"
#include "./mapping/ext/ext_pombensin.pwn"
#include "./mapping/ext/ext_toll.pwn"
#include "./mapping/ext/ext_meth.pwn"
#include "./mapping/ext/ext_shortcut.pwn"
#include "./mapping/ext/ext_sidejob.pwn"
#include "./mapping/ext/ext_lspd.pwn"
//#include "./mapping/ext/ext_watermark.pwn"
#include "./mapping/ext/ext_job.pwn"
#include "./mapping/ext/ext_bennys.pwn"
#include "./mapping/ext/ext_uber.pwn"
#include "./mapping/ext/ext_badside.pwn"
#include "./mapping/ext/ext_modshop.pwn"
#include "./mapping/ext/ext_basement.pwn"
#include "./mapping/ext/ext_garkot.pwn"
#include "./mapping/ext/ext_carnaval.pwn"
#include "./mapping/ext/ext_showroom.pwn"
#include "./mapping/ext/ext_balivibes.pwn"
#include "./mapping/ext/ext_konser.pwn"
#include "./mapping/ext/ext_environment.pwn"

#include "./mapping/int/int_jobcenter.pwn"
#include "./mapping/int/int_jailooc.pwn"

#include "./mapping/int/int_badside.pwn"

#include "./mapping/int/int_house.pwn"
#include "./mapping/int/int_biz.pwn"
#include "./mapping/int/int_blackmarket.pwn"

#include "./mapping/int/int_tambang.pwn"
#include "./mapping/int/int_lspd.pwn"
#include "./mapping/int/int_motel.pwn"
#include "./mapping/int/int_amber.pwn"
#include "./mapping/int/int_rpschool.pwn"
#include "./mapping/int/int_basement.pwn"
#include "./mapping/int/int_casino.pwn"
#include "./mapping/int/int_ikea.pwn"
#include "./mapping/int/int_moneywash.pwn"
#include "./mapping/int/int_airport.pwn"

#include "./mapping/int/int_lobbychar.pwn"

public OnPlayerConnect(playerid)
{
	RemoveVendingMachines(playerid);
	RemoveFleecaBuilding(playerid);
	RemoveSuperMarketBuilding(playerid);
	RemoveClothesBuilding(playerid);
	RemoveWalkotBuilding(playerid);
	RemoveKanabisProcBuilding(playerid);
	RemoveLSPDBuilding(playerid);
	RemoveBurgershotBuilding(playerid);
	RemoveModshopBuilding(playerid);

	RemoveMethBuilding(playerid);

	RemoveJobBuilding(playerid);

	//RemoveBadsideBuilding(playerid);

	RemoveGarkotBuilding(playerid);
	RemoveHospitalBuilding(playerid);
	RemoveCarnavalBuilding(playerid);
	RemoveShowroomBuilding(playerid);

	RemoveBaliVibesBuilding(playerid);

	//handover
	RemoveBuildingForPlayer(playerid, 1412, 215.000, -224.000, 2.023, 0.250);
	RemoveBuildingForPlayer(playerid, 1412, 192.914, -238.977, 1.820, 0.250);
	RemoveBuildingForPlayer(playerid, 1412, 192.813, -244.250, 1.828, 0.250);
	RemoveBuildingForPlayer(playerid, 1412, 192.813, -249.531, 1.828, 0.250);
	RemoveBuildingForPlayer(playerid, 1412, 192.813, -254.804, 1.828, 0.250);
	RemoveBuildingForPlayer(playerid, 1412, 192.813, -263.843, 1.812, 0.250);
	RemoveBuildingForPlayer(playerid, 1412, 192.906, -269.125, 1.843, 0.250);
	RemoveBuildingForPlayer(playerid, 1412, 195.460, -271.820, 1.851, 0.250);
	RemoveBuildingForPlayer(playerid, 1412, 200.742, -271.820, 1.851, 0.250);
	RemoveBuildingForPlayer(playerid, 1412, 209.570, -271.835, 1.851, 0.250);
	RemoveBuildingForPlayer(playerid, 1412, 214.843, -271.820, 1.851, 0.250);
	RemoveBuildingForPlayer(playerid, 1412, 220.125, -271.796, 1.851, 0.250);
	RemoveBuildingForPlayer(playerid, 1412, 222.804, -269.125, 1.851, 0.250);
	RemoveBuildingForPlayer(playerid, 1412, 222.789, -263.851, 1.851, 0.250);
	RemoveBuildingForPlayer(playerid, 1412, 222.796, -258.570, 1.851, 0.250);
	RemoveBuildingForPlayer(playerid, 1412, 222.796, -253.296, 1.851, 0.250);
	RemoveBuildingForPlayer(playerid, 1412, 222.781, -248.022, 1.851, 0.250);
	RemoveBuildingForPlayer(playerid, 1412, 222.804, -238.945, 1.851, 0.250);
	return 1;
}

RemoveVendingMachines(playerid)
{
	//basement casino
	RemoveBuildingForPlayer(playerid, 625, 556.210, -1500.390, 14.343, 0.250);
	RemoveBuildingForPlayer(playerid, 625, 556.210, -1516.780, 14.343, 0.250);
	RemoveBuildingForPlayer(playerid, 1346, 546.382, -1497.489, 14.804, 0.250);
	RemoveBuildingForPlayer(playerid, 1346, 546.382, -1499.180, 14.804, 0.250);

	//fisher dock SMB
	RemoveBuildingForPlayer(playerid, 1280, 159.335, -1794.589, 3.171, 0.250);

	//shortcut
	RemoveBuildingForPlayer(playerid, 1503, 1749.709, 776.437, 10.210, 0.250);
	RemoveBuildingForPlayer(playerid, 1283, 153.671, -1547.020, 12.140, 0.250);
	RemoveBuildingForPlayer(playerid, 1283, 133.647, -1581.130, 13.578, 0.250);
	RemoveBuildingForPlayer(playerid, 1283, 132.289, -1565.199, 12.125, 0.250);
	RemoveBuildingForPlayer(playerid, 1283, 162.522, -1569.930, 14.312, 0.250);
	RemoveBuildingForPlayer(playerid, 1283, 73.812, -1543.130, 7.531, 0.250);
	RemoveBuildingForPlayer(playerid, 1283, 93.210, -1517.630, 7.085, 0.250);

	RemoveBuildingForPlayer(playerid, 956, 1634.1487,-2238.2810,13.5077, 20.0); //Snack vender @ LS Airport
	RemoveBuildingForPlayer(playerid, 956, 2480.9885,-1958.5117,13.5831, 20.0); //Snack vender @ Sushi Shop in Willowfield
	RemoveBuildingForPlayer(playerid, 955, 1729.7935,-1944.0087,13.5682, 20.0); //Sprunk machine @ Unity Station
	RemoveBuildingForPlayer(playerid, 955, 2060.1099,-1898.4543,13.5538, 20.0); //Sprunk machine opposite Tony's Liqour in Willowfield
	RemoveBuildingForPlayer(playerid, 955, 2325.8708,-1645.9584,14.8270, 20.0); //Sprunk machine @ Ten Green Bottles
	RemoveBuildingForPlayer(playerid, 955, 1153.9130,-1460.8893,15.7969, 20.0); //Sprunk machine @ Market
	RemoveBuildingForPlayer(playerid, 955,1788.3965,-1369.2336,15.7578, 20.0); //Sprunk machine in Downtown Los Santos
	RemoveBuildingForPlayer(playerid, 955, 2352.9939,-1357.1105,24.3984, 20.0); //Sprunk machine @ Liquour shop in East Los Santos
	RemoveBuildingForPlayer(playerid, 1775, 2224.3235,-1153.0692,1025.7969, 20.0); //Sprunk machine @ Jefferson Motel
	RemoveBuildingForPlayer(playerid, 956, 2140.2566,-1161.7568,23.9922, 20.0); //Snack machine @ pick'n'go market in Jefferson
	RemoveBuildingForPlayer(playerid, 956, 2154.1199,-1015.7635,62.8840, 20.0); //Snach machine @ Carniceria El Pueblo in Las Colinas
	RemoveBuildingForPlayer(playerid, 956, 662.5665,-551.4142,16.3359, 20.0); //Snack vender at Dillimore Gas Station
	RemoveBuildingForPlayer(playerid, 955, 200.2010,-107.6401,1.5513, 20.0); //Sprunk machine @ Blueberry Safe House
	RemoveBuildingForPlayer(playerid, 956, 2271.4666,-77.2104,26.5824, 20.0); //Snack machine @ Palomino Creek Library
	RemoveBuildingForPlayer(playerid, 955, 1278.5421,372.1057,19.5547, 20.0); //Sprunk machine @ Papercuts in Montgomery
	RemoveBuildingForPlayer(playerid, 955, 1929.5527,-1772.3136,13.5469, 20.0); //Sprunk machine @ Idlewood Gas Station

	//San Fierro
	RemoveBuildingForPlayer(playerid, 1302, -2419.5835,984.4185,45.2969, 20.0); //Soda machine 1 @ Juniper Hollow Gas Station
	RemoveBuildingForPlayer(playerid, 1209, -2419.5835,984.4185,45.2969, 20.0); //Soda machine 2 @ Juniper Hollow Gas Station
	RemoveBuildingForPlayer(playerid, 956, -2229.2075,287.2937,35.3203, 20.0); //Snack vender @ King's Car Park
	RemoveBuildingForPlayer(playerid, 955, -1349.3947,493.1277,11.1953, 20.0); //Sprunk machine @ SF Aircraft Carrier
	RemoveBuildingForPlayer(playerid, 956, -1349.3947,493.1277,11.1953, 20.0); //Snack vender @ SF Aircraft Carrier
	RemoveBuildingForPlayer(playerid, 955, -1981.6029,142.7232,27.6875, 20.0); //Sprunk machine @ Cranberry Station
	RemoveBuildingForPlayer(playerid, 955, -2119.6245,-422.9411,35.5313, 20.0); //Sprunk machine 1/2 @ SF Stadium
	RemoveBuildingForPlayer(playerid, 955, -2097.3696,-397.5220,35.5313, 20.0); //Sprunk machine 3 @ SF Stadium
	RemoveBuildingForPlayer(playerid, 955, -2068.5593,-397.5223,35.5313, 20.0); //Sprunk machine 3 @ SF Stadium
	RemoveBuildingForPlayer(playerid, 955, -2039.8802,-397.5214,35.5313, 20.0); //Sprunk machine 3 @ SF Stadium
	RemoveBuildingForPlayer(playerid, 955, -2011.1403,-397.5225,35.5313, 20.0); //Sprunk machine 3 @ SF Stadium
	RemoveBuildingForPlayer(playerid, 955, -2005.7861,-490.8688,35.5313, 20.0); //Sprunk machine 3 @ SF Stadium
	RemoveBuildingForPlayer(playerid, 955, -2034.5267,-490.8681,35.5313, 20.0); //Sprunk machine 3 @ SF Stadium
	RemoveBuildingForPlayer(playerid, 955, -2063.1875,-490.8687,35.5313, 20.0); //Sprunk machine 3 @ SF Stadium
	RemoveBuildingForPlayer(playerid, 955, -2091.9780,-490.8684,35.5313, 20.0); //Sprunk machine 3 @ SF Stadium

	//Las Venturas
	RemoveBuildingForPlayer(playerid, 956, -1455.1298,2592.4138,55.8359, 20.0); //Snack vender @ El Quebrados GONE
	RemoveBuildingForPlayer(playerid, 955, -252.9574,2598.9048,62.8582, 20.0); //Sprunk machine @ Las Payasadas GONE
	RemoveBuildingForPlayer(playerid, 956, -252.9574,2598.9048,62.8582, 20.0); //Snack vender @ Las Payasadas GONE
	RemoveBuildingForPlayer(playerid, 956, 1398.7617,2223.3606,11.0234, 20.0); //Snack vender @ Redsands West GONE
	RemoveBuildingForPlayer(playerid, 955, -862.9229,1537.4246,22.5870, 20.0); //Sprunk machine @ The Smokin' Beef Grill in Las Barrancas GONE
	RemoveBuildingForPlayer(playerid, 955, -14.6146,1176.1738,19.5634, 20.0); //Sprunk machine @ Fort Carson GONE
	RemoveBuildingForPlayer(playerid, 956, -75.2839,1227.5978,19.7360, 20.0); //Snack vender @ Fort Carson GONE
	RemoveBuildingForPlayer(playerid, 955, 1519.3328,1055.2075,10.8203, 20.0); //Sprunk machine @ LVA Freight Department GONE
	RemoveBuildingForPlayer(playerid, 956, 1659.5096,1722.1096,10.8281, 20.0); //Snack vender near Binco @ LV Airport GONE
	RemoveBuildingForPlayer(playerid, 955, 2086.5872,2071.4958,11.0579, 20.0); //Sprunk machine @ Sex Shop on The Strip
	RemoveBuildingForPlayer(playerid, 955, 2319.9001,2532.0376,10.8203, 20.0); //Sprunk machine @ Pizza co by Julius Thruway (North)
	RemoveBuildingForPlayer(playerid, 955, 2503.2061,1244.5095,10.8203, 20.0); //Sprunk machine @ Club in the Camels Toe
	RemoveBuildingForPlayer(playerid, 956, 2845.9919,1294.2975,11.3906, 20.0); //Snack vender @ Linden Station
	RemoveBuildingForPlayer(playerid, 956, 2647.699, 1129.660, 10.218, 0.250); //Snack vender @ LV POM BAWAH

	//Interiors: 24/7 and Clubs
	RemoveBuildingForPlayer(playerid, 1775, 496.0843,-23.5310,1000.6797, 20.0); //Sprunk machine 1 @ Club in Camels Toe
	RemoveBuildingForPlayer(playerid, 1775, 501.1219,-2.1968,1000.6797, 20.0); //Sprunk machine 2 @ Club in Camels Toe
	RemoveBuildingForPlayer(playerid, 1776, 501.1219,-2.1968,1000.6797, 20.0); //Snack vender @ Club in Camels Toe
	RemoveBuildingForPlayer(playerid, 1775, -19.2299,-57.0460,1003.5469, 20.0); //Sprunk machine @ Roboi's type 24/7 stores
	RemoveBuildingForPlayer(playerid, 1776, -35.9012,-57.1345,1003.5469, 20.0); //Snack vender @ Roboi's type 24/7 stores
	RemoveBuildingForPlayer(playerid, 1775, -17.0036,-90.9709,1003.5469, 20.0); //Sprunk machine @ Other 24/7 stores
	RemoveBuildingForPlayer(playerid, 1776, -17.0036,-90.9709,1003.5469, 20.0); //Snach vender @ Others 24/7 stores
}

public OnPlayerDisconnect(playerid, reason)
{
	return 1;
}

public OnFilterScriptExit()
{
	DestroyAllDynamicObjects();
	DestroyAllDynamicPickups();
	DestroyAllDynamicCPs();
	DestroyAllDynamicRaceCPs();
	DestroyAllDynamicMapIcons();
	DestroyAllDynamic3DTextLabels();
	DestroyAllDynamicAreas();
	return 1;
}

public OnFilterScriptInit()
{
	// Config
	//Streamer_MaxItems(STREAMER_TYPE_OBJECT, 990000);
	//Streamer_MaxItems(STREAMER_TYPE_MAP_ICON, 2000);
	//Streamer_MaxItems(STREAMER_TYPE_PICKUP, 2000);

	Streamer_ToggleChunkStream(1);
	Streamer_SetChunkSize(STREAMER_TYPE_OBJECT, 100);
	Streamer_SetTickRate(50);
	
	foreach(new i : Player) if(IsPlayerConnected(i))
	{
		Streamer_DestroyAllVisibleItems(i, 0);
	}
	Streamer_VisibleItems(STREAMER_TYPE_OBJECT, 1000);
	
	//Exterior
	CreateUberExt();

	//CreateWatermarkExt();
	
	CreateCarstealExt();
	CreateFleecaExt();
	CreateElectroExt();
	CreateSuperMarketExt();
	CreateClothesExt();
	CreateWalkotExt();
	CreateKanabisProcExt();
	CreateBurgershotExt();
	CreateBennysExt();
	
	CreateHospitalExt();
	CreateAmmunationExt();
	CreatePomBensinExt();
	CreateSMBToll();
	CreateMethExt();
	CreateShortcutExt();
	CreateSidejobExt();
	CreateLSPDExt();
	CreateJobExt();
	//CreateBadsideExt();
	CreateModshopExt();
	CreateBasementExt();
	CreateGarkotExt();
	CreateCarnavalExt();
	CreateShowroomExt();

	CreateBaliVibesExt();
	CreateKonserExt();

	CreateEnvironmentExt();

	//Interior
	CreateIkeaInt();
	CreateAmberInt();
	CreateJobCenterInt();
	CreateJailOOCInt();

	//CreateBadsideInt();

	CreateHouseStandardInt();
	CreateHouseKontemInt();
	CreateHouseModernInt();
	CreateCustomHouseInt();

	CreateBizInt();
	CreateBlackmarketInt();

	CreateTambangInt();
	CreateLSPDInt();
	CreateMotelInt();
	CreateRPSchoolInt();
	CreateBasementInt();
	CreateCasinoInt();

	CreateMoneywashInt();
	CreateAirportLSInt();

	CreateLobbyCharInt();
	return 1;
}
